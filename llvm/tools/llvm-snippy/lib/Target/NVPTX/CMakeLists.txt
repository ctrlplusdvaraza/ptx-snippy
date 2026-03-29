include_directories(
  ${LLVM_MAIN_SRC_DIR}/lib/Target/NVPTX
  ${LLVM_BINARY_DIR}/lib/Target/NVPTX
)

set(LLVM_LINK_COMPONENTS
  NVPTX
  Core
  Support
  )

add_llvm_library(LLVMSnippyNVPTX
  DISABLE_LLVM_LINK_LLVM_DYLIB
  STATIC
  Target.cpp

  # DEPENDS
  # intrinsics_gen
  # X86CommonTableGen
  )

# target_link_libraries(LLVMSnippyNVPTX PRIVATE
#   LLVMSnippyConfig LLVMSnippySupport LLVMSnippyTarget)
