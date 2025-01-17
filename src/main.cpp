#include <LLGL/LLGL.h>
#include <LLGL/Utils/VertexFormat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tracer.hpp"
#include "microfacet.hpp"

struct XVertex {
  float   position[3];
  uint8_t color[4];
};

int main(){
  try {
    
    /*
    //LLGL::Initialize();
    LLGL::RenderSystemPtr myRenderer = LLGL::RenderSystem::Load("Metal");
    std::cout << "TEST2" << myRenderer << std::endl;

    // Instantiate a Ray object
    glm::vec3 origin(0.0f, 0.0f, 0.0f);  // Ray origin at (0, 0, 0)
    glm::vec3 direction(1.0f, 1.0f, 1.0f); // Ray direction (1, 1, 1)

    Ray myRay(origin, direction);

    // Verify the Ray's data
    std::cout << "Ray Origin: (" 
              << myRay.origin.x << ", " 
              << myRay.origin.y << ", " 
              << myRay.origin.z << ")" << std::endl;

    std::cout << "Ray Direction (normalized): ("
              << myRay.direction.x << ", " 
              << myRay.direction.y << ", " 
              << myRay.direction.z << ")" << std::endl;

    //LLGL::Shutdown();

    Ray ray(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Intersection hit;
    MicrofacetMaterial material(glm::vec3(1.0f), 1.5f, 0.5f);

    glm::vec3 attenuation;
    Ray scattered;
    

    if (material.scatter(ray, hit, attenuation, scattered)) {
      // render
    }
    */

    ///////////////////////////////

    // Load OS-relevant LLGL render system (Metal/OpenGL)
    /*
    LLGL::RenderSystemPtr renderer;
    #if defined(__APPLE__)
        renderer = LLGL::RenderSystem::Load("Metal");
    #else
        renderer = LLGL::RenderSystem::Load("OpenGL");
    #endif
    if (renderer) {
        std::cout << "Before window def" << std::endl;
    } */

    /*LLGL::RenderSystemPtr renderer;
    for (const char* module : { "Direct3D12", "Direct3D11", "Vulkan", "OpenGL", "Metal" }) {
        LLGL::Report report;
        renderer = LLGL::RenderSystem::Load(module, &report);
        std::cout << renderer << std::endl;
        if (renderer == nullptr) {
            LLGL::Log::Errorf("%s", report.GetText());
        } 
    }
    std::cout << renderer << std::endl; */
    
    LLGL::Report report;
    LLGL::RenderSystemPtr renderer = LLGL::RenderSystem::Load("OpenGL", &report);
    if (renderer == nullptr) {
        std::cout << "NULLPTR" << std::endl;
        std::cout << report.GetText() << std::endl;
    }

    
    /*
    LLGL::RenderSystemDescriptor rendererDesc;
    #if defined(__APPLE__)
        rendererDesc = LLGL::RenderSystemDescriptor("OpenGL");
    #else
        rendererDesc = LLGL::RenderSystemDescriptor("OpenGL");
    #endif
    auto renderer = LLGL::RenderSystem::Load(rendererDesc);
    // TODO handle nullptr renderer*/

    // Swap chain
    LLGL::SwapChainDescriptor swapChainDesc;
    swapChainDesc.resolution = { 1600, 1200 };
    swapChainDesc.fullscreen = false;
    swapChainDesc.samples    = 8;
    LLGL::SwapChain* swapChain = renderer->CreateSwapChain(swapChainDesc);

    if (!swapChain) {
      std::cout << "Failed to create swap chain" << std::endl;
      return -1;
    }

    // Vertex buffer
    /*
    XVertex vertices[3] = {
      XVertex{ {  0.0f,  0.5f }, { 255,   0,   0, 255 } }, // Red
      XVertex{ {  0.5f, -0.5f }, {   0, 255,   0, 255 } }, // Green
      XVertex{ { -0.5f, -0.5f }, {   0,   0, 255, 255 } }, // Blue
    };*/

    XVertex vertices[4] = {
      XVertex{ {  0.0f,  0.5f,  0.0f }, { 255,   0,   0, 255 } }, // Red vertex at the top
      XVertex{ {  0.5f, -0.5f,  0.5f }, {   0, 255,   0, 255 } }, // Green vertex front-right
      XVertex{ { -0.5f, -0.5f,  0.5f }, {   0,   0, 255, 255 } }, // Blue vertex front-left
      XVertex{ {  0.0f, -0.5f, -0.5f }, { 255, 255,   0, 255 } }  // Yellow vertex back
};

    LLGL::VertexFormat vertexFormat;
    vertexFormat.AppendAttribute({ "position", LLGL::Format::RGB32Float  });
    vertexFormat.AppendAttribute({ "color",    LLGL::Format::RGBA8UNorm });

    LLGL::BufferDescriptor bufferDesc;
    bufferDesc.size            = sizeof(vertices);
    bufferDesc.bindFlags       = LLGL::BindFlags::VertexBuffer;
    bufferDesc.vertexAttribs   = vertexFormat.attributes;
    LLGL::Buffer* vertexBuffer = renderer->CreateBuffer(bufferDesc, vertices);

    // Select OS-relevant shaders
    LLGL::ShaderDescriptor VSDesc, FSDesc;
    #if defined(__APPLE__)  // For macOS, load Metal shaders
        /*VSDesc = { LLGL::ShaderType::Vertex,   "shaders/v_shader.metal", "VMain", "1.1" };
        FSDesc = { LLGL::ShaderType::Fragment, "shaders/f_shader.metal", "PMain", "1.1" };*/
        VSDesc = { LLGL::ShaderType::Vertex,   "shaders/Example.vert" };
        FSDesc = { LLGL::ShaderType::Fragment, "shaders/Example.frag" };
    #else  // For non-macOS (e.g., Windows/Linux), load OpenGL shaders
        VSDesc = { LLGL::ShaderType::Vertex,   "shaders/Example.vert" };
        FSDesc = { LLGL::ShaderType::Fragment, "shaders/Example.frag" };
    #endif

    VSDesc.vertex.inputAttribs = vertexFormat.attributes;

    LLGL::Shader* vertexShader   = renderer->CreateShader(VSDesc);
    LLGL::Shader* fragmentShader = renderer->CreateShader(FSDesc);

    LLGL::ShaderDescriptor myVertexShaderDesc;
    myVertexShaderDesc.type                = LLGL::ShaderType::Vertex;
    myVertexShaderDesc.source              = "#version 330\n"
                                       "#ifdef GL_ES\n"
                                       "precision mediump float;\n"
                                       "#endif\n"
                                       "\n"
                                       "in vec3 position;\n"
                                       "in vec4 color;\n"
                                       "out vec4 vertexColor;\n"
                                       "void main() {\n"
                                       "    gl_Position = vec4(position, 1.0);\n"
                                       "    vertexColor = color;\n"
                                       "}\n";
    myVertexShaderDesc.sourceSize          = 0;                                  // Ignored for NUL-terminated sources
    myVertexShaderDesc.sourceType          = LLGL::ShaderSourceType::CodeString; // Source is provided as string in high-level language
    myVertexShaderDesc.entryPoint          = "";                                 // Only required for HLSL/Metal (can be null)
    myVertexShaderDesc.profile             = "";                                 // Only required for HLSL/Metal (can be null)
    myVertexShaderDesc.vertex.inputAttribs = vertexFormat.attributes;          // Vertex input attribnutes (vertex shaders only)
    LLGL::Shader* myVertexShader = renderer->CreateShader(myVertexShaderDesc);

    LLGL::ShaderDescriptor myFragmentShaderDesc;
    myFragmentShaderDesc.type                = LLGL::ShaderType::Fragment;
    myFragmentShaderDesc.source              = "#version 330\n"
                                       "#ifdef GL_ES\n"
                                       "precision mediump float;\n"
                                       "#endif\n"
                                       "in vec4 vertexColor;\n"
                                       "out vec4 fragColor;\n"
                                      "void main() {\n"
                                      "    fragColor = vertexColor;\n"
                                      "}\n";
    myFragmentShaderDesc.sourceSize          = 0;                                  // Ignored for NUL-terminated sources
    myFragmentShaderDesc.sourceType          = LLGL::ShaderSourceType::CodeString; // Source is provided as string in high-level language
    myFragmentShaderDesc.entryPoint          = "";                                 // Only required for HLSL/Metal (can be null)
    myFragmentShaderDesc.profile             = "";                                 // Only required for HLSL/Metal (can be null)
    myFragmentShaderDesc.vertex.inputAttribs = vertexFormat.attributes;          // Vertex input attribnutes (vertex shaders only)
    LLGL::Shader* myFragmentShader = renderer->CreateShader(myFragmentShaderDesc);

    // Test for shader loading errors
    for (LLGL::Shader* shader : { vertexShader, fragmentShader, myVertexShader, myFragmentShader }) {
      if (const LLGL::Report* report = shader->GetReport()) {
          if (report->HasErrors()) {
              LLGL::Log::Errorf("Shader compile errors:\n%s", report->GetText());
              std::cout << report->GetText() << std::endl;
          } else {
              LLGL::Log::Printf("Shader compile warnings:\n%s", report->GetText());
              std::cout << report->GetText() << std::endl;

          }
      }
    }

    // Pipeline
    LLGL::GraphicsPipelineDescriptor pipelineDesc;
    pipelineDesc.vertexShader                  = myVertexShader;
    pipelineDesc.fragmentShader                = myFragmentShader;
    //pipelineDesc.vertexShader                  = vertexShader;
    //pipelineDesc.fragmentShader                = fragmentShader;
    pipelineDesc.renderPass                    = swapChain->GetRenderPass();
    pipelineDesc.rasterizer.multiSampleEnabled = (swapChainDesc.samples > 1);
    pipelineDesc.rasterizer.depthClampEnabled  = true;
    pipelineDesc.depth.testEnabled = true;
    pipelineDesc.depth.writeEnabled = true;
    LLGL::PipelineState* pipeline = renderer->CreatePipelineState(pipelineDesc);

    LLGL::CommandBuffer* cmdBuffer = renderer->CreateCommandBuffer(LLGL::CommandBufferFlags::ImmediateSubmit);

    // Link shader program and check for errors
        if (const LLGL::Report* report = pipeline->GetReport())
        {
            if (report->HasErrors())
            {
                LLGL::Log::Errorf("%s\n", report->GetText());
                std::cout << report->GetText() << std::endl;
            }
        }

    // Cast "Window" from base class "Surface" (only on desktop platforms such as Windows, GNU/Linux, and macOS)
    LLGL::Window& window = LLGL::CastTo<LLGL::Window>(swapChain->GetSurface());

    // Set window title (aka. caption) and show window
    window.SetTitle("Hello Triangle");
    window.Show();

    const float bgColor[4] = { 0.1f, 0.1f, 0.2f, 1.0f };
    cmdBuffer->Clear(LLGL::ClearFlags::Color, bgColor);

    // Process window events (such as user input)
    while (window.ProcessEvents()) {
        /* Render code goes here ... */
        cmdBuffer->Begin();
        {
          cmdBuffer->SetViewport(swapChain->GetResolution());
          
          cmdBuffer->SetVertexBuffer(*vertexBuffer);
          cmdBuffer->BeginRenderPass(*swapChain);
          {
            cmdBuffer->Clear(LLGL::ClearFlags::Color, bgColor);
            

            cmdBuffer->SetPipelineState(*pipeline);
            
            cmdBuffer->Draw(4, 0);
            
          }
          cmdBuffer->EndRenderPass();
        }
        cmdBuffer->End();
        
        swapChain->Present();
    }

  } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

  return 0;
}
