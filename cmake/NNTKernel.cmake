
SET (NNT_BUILD_KERNEL 1 CACHE BOOL "build for kernel")

MACRO (source file)
  LIST (APPEND CURRENT_SOURCES ${file})
ENDMACRO ()

MACRO (sourcesub file)
  LIST (APPEND CURRENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${file})
ENDMACRO ()

MACRO (NNT_USE_HEADERS)
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}")
ENDMACRO ()

MACRO (NNT_USE_LIBHEADERS)
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/Classes")
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/Classes/Core")
ENDMACRO ()

SET (NNT_ARCH 32)
IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET (NNT_ARCH 64)
ENDIF ()

# set build rules.
SET (NNT_KERNEL_C_PREPROCESSORS -DLIBNNT -DKERNELNNT)
SET (NNT_KERNELAPP_C_PREPROCESSORS -DKERNELNNT)
SET (NNT_KERNEL_C_FLAGS "-fno-common -fno-omit-frame-pointer -mno-aes -mno-avx -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -msoft-float -fno-asynchronous-unwind-tables -fstack-protector -Qunused-arguments -fstack-protector -fno-exceptions -fno-rtti -fno-cxa-atexit -nostdinc++  -Wall")

MACRO (NNT_KERNEL_CFLAGS)
  SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${NNT_KERNEL_C_FLAGS}") 
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NNT_KERNEL_C_FLAGS}")
ENDMACRO ()
