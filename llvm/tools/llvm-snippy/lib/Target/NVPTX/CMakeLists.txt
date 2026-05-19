include_directories(
  ${LLVM_MAIN_SRC_DIR}/lib/Target/NVPTX
  ${LLVM_BINARY_DIR}/lib/Target/NVPTX
)

set(LLVM_TARGET_DEFINITIONS ${PROJECT_SOURCE_DIR}/lib/Target/NVPTX/NVPTX.td)
tablegen(SNIPPY NVPTXGenerated.inc -gen-riscv -I ${PROJECT_SOURCE_DIR}/lib/Target/NVPTX/)
add_public_tablegen_target(SnippyNVPTXTableGen)


set(LLVM_LINK_COMPONENTS
  NVPTX
  Core
  Support
  )

add_llvm_library(LLVMSnippyNVPTX
  DISABLE_LLVM_LINK_LLVM_DYLIB
  STATIC
  Target.cpp

  DEPENDS
    NVPTXCommonTableGen
    SnippyNVPTXTableGen
  )

target_link_libraries(
  LLVMSnippyNVPTX
  PRIVATE LLVMSnippyConfig LLVMSnippySupport LLVMSnippyTarget
  PUBLIC SnippyHeaders
  )

target_include_directories(LLVMSnippyRISCV
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
  )

