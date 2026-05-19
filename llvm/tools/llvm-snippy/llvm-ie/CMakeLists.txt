add_subdirectory(TableGen)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(lib)

set(LLVM_LINK_COMPONENTS
  Support
  )

add_llvm_tool(llvm-ie
  DISABLE_LLVM_LINK_LLVM_DYLIB
  main.cpp
)

set(LLVM_INSTRUCTION_ENUMERATOR_RISCV_PLUGINS)
foreach(t ${LLVM_INSTRUCTION_ENUMERATOR_TARGETS})
  string(STRIP ${t} t)
  list(APPEND LLVM_INSTRUCTION_ENUMERATOR_RISCV_PLUGINS "LLVMInstructionEnumeratorRISCV${t}")
endforeach()

target_link_libraries(llvm-ie PRIVATE
  -Wl,--start-group
  LLVMInstructionEnumeratorRISCV
  LLVMInstructionEnumerator
  ${LLVM_INSTRUCTION_ENUMERATOR_PLUGINS}
  -Wl,--end-group
)
