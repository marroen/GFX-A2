#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LLGL::LLGL" for configuration "Debug"
set_property(TARGET LLGL::LLGL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LLGL::LLGL PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libLLGLD.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libLLGLD.dylib"
  )

list(APPEND _cmake_import_check_targets LLGL::LLGL )
list(APPEND _cmake_import_check_files_for_LLGL::LLGL "${_IMPORT_PREFIX}/lib/libLLGLD.dylib" )

# Import target "LLGL::LLGL_Null" for configuration "Debug"
set_property(TARGET LLGL::LLGL_Null APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LLGL::LLGL_Null PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libLLGL_NullD.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libLLGL_NullD.dylib"
  )

list(APPEND _cmake_import_check_targets LLGL::LLGL_Null )
list(APPEND _cmake_import_check_files_for_LLGL::LLGL_Null "${_IMPORT_PREFIX}/lib/libLLGL_NullD.dylib" )

# Import target "LLGL::LLGL_OpenGL" for configuration "Debug"
set_property(TARGET LLGL::LLGL_OpenGL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LLGL::LLGL_OpenGL PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libLLGL_OpenGLD.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libLLGL_OpenGLD.dylib"
  )

list(APPEND _cmake_import_check_targets LLGL::LLGL_OpenGL )
list(APPEND _cmake_import_check_files_for_LLGL::LLGL_OpenGL "${_IMPORT_PREFIX}/lib/libLLGL_OpenGLD.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
