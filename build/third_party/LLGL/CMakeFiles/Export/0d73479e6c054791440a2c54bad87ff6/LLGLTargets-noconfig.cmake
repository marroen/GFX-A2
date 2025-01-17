#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LLGL::LLGL" for configuration ""
set_property(TARGET LLGL::LLGL APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LLGL::LLGL PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libLLGL.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libLLGL.dylib"
  )

list(APPEND _cmake_import_check_targets LLGL::LLGL )
list(APPEND _cmake_import_check_files_for_LLGL::LLGL "${_IMPORT_PREFIX}/lib/libLLGL.dylib" )

# Import target "LLGL::LLGL_Null" for configuration ""
set_property(TARGET LLGL::LLGL_Null APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LLGL::LLGL_Null PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libLLGL_Null.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libLLGL_Null.dylib"
  )

list(APPEND _cmake_import_check_targets LLGL::LLGL_Null )
list(APPEND _cmake_import_check_files_for_LLGL::LLGL_Null "${_IMPORT_PREFIX}/lib/libLLGL_Null.dylib" )

# Import target "LLGL::LLGL_OpenGL" for configuration ""
set_property(TARGET LLGL::LLGL_OpenGL APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LLGL::LLGL_OpenGL PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libLLGL_OpenGL.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libLLGL_OpenGL.dylib"
  )

list(APPEND _cmake_import_check_targets LLGL::LLGL_OpenGL )
list(APPEND _cmake_import_check_files_for_LLGL::LLGL_OpenGL "${_IMPORT_PREFIX}/lib/libLLGL_OpenGL.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
