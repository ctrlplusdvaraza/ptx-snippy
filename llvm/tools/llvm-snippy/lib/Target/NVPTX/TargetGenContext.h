#ifndef LLVM_TOOLS_SNIPPY_LIB_NVPTX_GEN_CONTEXT_H
#define LLVM_TOOLS_SNIPPY_LIB_NVPTX_GEN_CONTEXT_H

//===-- TargetGenContext.h --------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// #include "snippy/Generator/Policy.h"
#include "snippy/Target/Target.h"

// #include "RVVUnitConfig.h"

#include <optional>

// #include "RISCVGenerated.h"

namespace llvm {
namespace snippy {


class NVPTXGeneratorContext : public TargetGenContextInterface {
public:

  ~NVPTXGeneratorContext() = default;

  NVPTXGeneratorContext() = default;
};

} // namespace snippy
} // namespace llvm

#endif // LLVM_TOOLS_SNIPPY_LIB_NVPTX_GEN_CONTEXT_H
