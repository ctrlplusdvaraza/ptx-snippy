//===-- Target.cpp ----------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "snippy/Target/Target.h"
#include "TargetConfig.h"
#include "llvm/MC/TargetRegistry.h"


#include "TargetGenContext.h"

#include "MCTargetDesc/NVPTXMCTargetDesc.h"

#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Target/TargetMachine.h"



#include <vector>

namespace llvm {
namespace snippy {

namespace {

static bool isSystemReg(Register Reg) {
  switch (Reg.id()) {
  case NVPTX::VRFrame32:
  case NVPTX::VRFrame64:
  case NVPTX::VRFrameLocal32:
  case NVPTX::VRFrameLocal64:
  case NVPTX::VRDepot:
    return true;
  default:
    return Reg.id() >= NVPTX::ENVREG0 && Reg.id() <= NVPTX::ENVREG31;
  }
}

class SnippyNVPTXTarget : public SnippyTarget {
public:
  SnippyNVPTXTarget() = default;

  void generateWriteValueSeq(InstructionGenerationContext &IGC, APInt Value,
                             MCRegister DestReg,
                             SmallVectorImpl<MCInst> &Insts) const override {
    llvm::outs() << "[DEBUG] generateWriteValueSeq\n";
    reportUnimplementedError();
  }

  [[noreturn]] void reportUnimplementedError() const {
    snippy::fatal("sorry, NVPTX target is not implemented");
  }

  bool matchesArch(Triple::ArchType Arch) const override;

  std::unique_ptr<IRegisterState>
  createRegisterState(const TargetGenContextInterface &TgtGenCtx,
                      const TargetSubtargetInfo &ST) const override {
    llvm::outs() << "[DEBUG] createRegisterState\n";
    return nullptr;
    // reportUnimplementedError();
  }

  std::unique_ptr<TargetGenContextInterface>
  createTargetContext(LLVMState &State, const Config &Cfg,
                      const TargetSubtargetInfo *STI,
                      const RegPoolWrapper &RP) const override {
    llvm::outs() << "[DEBUG] createTargetContext\n";
    return std::make_unique<NVPTXGeneratorContext>();
    // reportUnimplementedError();
  }

  std::unique_ptr<TargetConfigInterface> createTargetConfig() const override {
    llvm::outs() << "[DEBUG] createTargetConfig\n";
    return std::make_unique<PTXConfigInterface>();
    // reportUnimplementedError();
  }

  void setupGeneratedFunction(Function &F, StringRef EntryPointName,
                              StringRef OriginalName,
                              Function::LinkageTypes Linkage) const override {
    if (OriginalName == EntryPointName &&
        Linkage == Function::ExternalLinkage)
      F.setCallingConv(CallingConv::PTX_Kernel);
  }

  void
  checkInstrTargetDependency(const OpcodeHistogram &H, const OpcodeCache &OpCC,
                             const ProgramConfig &ProgramCfg) const override {
    llvm::outs() << "[DEBUG] checkInstrTargetDependency\n";
    return;
    // reportUnimplementedError();
  }

  bool isModeSwitchInstr(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] isModeSwitchInstr\n";
    return false;
    // reportUnimplementedError();
  }

  bool modeSwitchIsSupport(const SnippyProgramContext &ProgCtx) const override {
    llvm::outs() << "[DEBUG] modeSwitchIsSupport\n";
    return false;
    // reportUnimplementedError();
  }

  bool needToGenerateModeSwitches(
      const SnippyProgramContext &ProgCtx) const override {
    return false;
    llvm::outs() << "[DEBUG] needToGenerateModeSwitches\n";
    // reportUnimplementedError();
  }

  double
  getModeSwitchProbability(const SnippyProgramContext &ProgCtx) const override {
    llvm::outs() << "[DEBUG] getModeSwitchProbability\n";
    reportUnimplementedError();
  }

  void checkTrackingRestrictions(const OpcodeHistogram &H) const override {
    llvm::outs() << "[DEBUG] checkTrackingRestrictions\n";
    reportUnimplementedError();
  }

  Error checkOperandsReinitializationSupported(
      unsigned Opcode, const MCInstrInfo &InstrInfo) const override {
    llvm::outs() << "[DEBUG] checkOperandsReinitializationSupported\n";
    reportUnimplementedError();
  }

  Error checkOperandsReinitializationForbidden(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] checkOperandsReinitializationForbidden\n";
    reportUnimplementedError();
  }

  std::function<bool(unsigned)>
  generateModeChangeAndGetFilter(InstructionGenerationContext &IGC,
                                 MDNode *MetadataMark) const override {
    llvm::outs() << "[DEBUG] generateModeChangeAndGetFilter\n";
    reportUnimplementedError();
  }

  std::vector<Register>
  getRegsForSelfcheck(const MachineInstr &MI,
                      InstructionGenerationContext &IGC) const override {
    llvm::outs() << "[DEBUG] getRegsForSelfcheck\n";
    reportUnimplementedError();
  }

  std::unique_ptr<SelfcheckTargetConfigInterface>
  createSelfcheckTargetConfig() const override {
    llvm::outs() << "[DEBUG] createSelfcheckTargetConfig\n";
    return std::make_unique<PTXSelfcheckTargetConfig>();
    // reportUnimplementedError();
  }

  std::string
  validateSelfcheckConfig(const SelfcheckConfig &SelfcheckCfg,
                          const OpcodeHistogram &Histogram) const override {
    llvm::outs() << "[DEBUG] validateSelfcheckConfig\n";
    reportUnimplementedError();
  }

  void generateRegsInit(InstructionGenerationContext &IGC,
                        const IRegisterState &R) const override {
    llvm::outs() << "[DEBUG] generateRegsInit\n";
    reportUnimplementedError();
  }

  unsigned getFPRegsCount(const TargetSubtargetInfo &ST) const override {
    llvm::outs() << "[DEBUG] getFPRegsCount\n";
    return 32; // temp value
    // reportUnimplementedError();
  }

  bool requiresCustomGeneration(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] requiresCustomGeneration\n";
    return false;
    // reportUnimplementedError();
  }

  bool
  canBeGeneratedAsCommonInstr(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] canBeGeneratedAsCommonInstr\n";
    return true;
    // reportUnimplementedError();
  }

  void generateCustomInst(
      const MCInstrDesc &InstrDesc,
      planning::InstructionGenerationContext &InstrGenCtx) const override {
    llvm::outs() << "[DEBUG] generateCustomInst\n";
    reportUnimplementedError();
  }
  void instructionPostProcess(InstructionGenerationContext &IGC,
                              MachineInstr &MI) const override {
    llvm::outs() << "[DEBUG] instructionPostProcess\n";
    return; 
    // reportUnimplementedError();
  }

  MachineInstr *generateFinalInst(InstructionGenerationContext &IGC,
                                          unsigned LastInstr) const override {
    llvm::outs() << "[DEBUG] generateFinalInst\n";
    reportUnimplementedError();
  }

  std::vector<std::string> getCallerSavedRegGroups() const override {
    llvm::outs() << "[DEBUG] getCallerSavedRegGroups\n";
    return {};
    // reportUnimplementedError();
  }

  std::vector<std::string> getCallerSavedLiveRegGroups() const override {
    llvm::outs() << "[DEBUG] getCallerSavedLiveRegGroups\n";
    return {};
    // reportUnimplementedError();
  }

  std::vector<MCRegister>
  getCallerSavedRegs(const MachineFunction &MF,
                     ArrayRef<std::string> RegGroups) const override {
    llvm::outs() << "[DEBUG] getCallerSavedRegs\n";
    return {};
    // reportUnimplementedError();
  }

  std::vector<MCRegister>
  getRegsPreservedByABI(const MCSubtargetInfo &SubTgt) const override {
    llvm::outs() << "[DEBUG] getRegsPreservedByABI\n";
    return {};
    // reportUnimplementedError();
  }

  const MCRegisterClass &
  getRegClass(const InstructionGenerationContext &IGC,
              unsigned OperandRegClassID, unsigned OpIndex, unsigned Opcode,
              const MCRegisterInfo &RegInfo) const override {
    return RegInfo.getRegClass(OperandRegClassID);
  }

  const MCRegisterClass &
  getRegClassSuitableForSP(const MCRegisterInfo &RI) const override {
    // PTX ISA is virtual ISA without stack in common meaning
    // I decided to create temporary `Int64RegsRegClassID` stub for MVP]
    llvm::outs() << "[DEBUG] getRegClassSuitableForSP\n";
    return RI.getRegClass(NVPTX::B64RegClassID);
    // reportUnimplementedError();
  }

  std::function<bool(MCRegister)>
  filterSuitableRegsForStackPointer() const override {
    // PTX ISA has not special stack register
    llvm::outs() << "[DEBUG] filterSuitableRegsForStackPointer\n";
    return [](auto Reg) {
      return false;
    };
    // reportUnimplementedError();
  }

  // needed in static llvm::MCRegister llvm::getRealStackPointer
  // fail after warning: (seed-not-specified) no instructions seed specified...
  MCRegister getStackPointer() const override {
    // Return an invalid register to signify no hardware SP exists in PTX
    llvm::outs() << "[DEBUG] getStackPointer\n";
    return MCRegister();
    // reportUnimplementedError(); 
  }
  
  
  MCRegister getReturnAddress() const override { 
    // return address is not implemented yet 
    // return MCRegister()
    llvm::outs() << "[DEBUG] getReturnAddress\n";
    reportUnimplementedError(); 
  }

  bool isRegClassSupported(MCRegister Reg) const override {
    llvm::outs() << "[DEBUG] isRegClassSupported\n";
    reportUnimplementedError();
  }

  void generateSpillToStack(
      InstructionGenerationContext &IGC, MCRegister Reg, MCRegister SP,
      SnippyMetadata MetadataMark = SnippyMetadata::Support) const override {
    llvm::outs() << "[DEBUG] generateSpillToStack\n";
    reportUnimplementedError();
  }

  void generateReloadFromStack(
      InstructionGenerationContext &IGC, MCRegister Reg, MCRegister SP,
      SnippyMetadata MetadataMark = SnippyMetadata::Support) const override {
    llvm::outs() << "[DEBUG] generateReloadFromStack\n";
    reportUnimplementedError();
  }

  void generatePopNoReload(InstructionGenerationContext &IGC,
                           MCRegister Reg) const override {
    llvm::outs() << "[DEBUG] generatePopNoReload\n";
    reportUnimplementedError();
  }

  unsigned getRegBitWidth(MCRegister Reg,
                          InstructionGenerationContext &IGC) const override {
    llvm::outs() << "[DEBUG] getRegBitWidth\n";
    reportUnimplementedError();
  }

  MCRegister regIndexToMCReg(InstructionGenerationContext &IGC, unsigned RegIdx,
                             RegStorageType Storage) const override {
    llvm::outs() << "[DEBUG] regIndexToMCReg\n";
    reportUnimplementedError();
  }

  RegStorageType regToStorage(Register Reg) const override {
    llvm::outs() << "[DEBUG] regToStorage\n";
    reportUnimplementedError();
  }

  unsigned regToIndex(Register Reg) const override {
    llvm::outs() << "[DEBUG] regToIndex\n";
    reportUnimplementedError();
  }

  unsigned getNumRegs(RegStorageType Storage,
                      const TargetSubtargetInfo &SubTgt) const override {
    llvm::outs() << "[DEBUG] getNumRegs\n";
    return 32;
    // reportUnimplementedError();
  }

  unsigned
  getSpillSizeInBytes(MCRegister Reg, SnippyProgramContext &ProgCtx,
                      const TargetSubtargetInfo &SubTgt) const override {
    llvm::outs() << "[DEBUG] getSpillSizeInBytes\n";
    reportUnimplementedError();
  }

  unsigned getSpillAlignmentInBytes(MCRegister Reg,
                                    const LLVMState &State) const override {
    llvm::outs() << "[DEBUG] getSpillAlignmentInBytes\n";
    reportUnimplementedError();
  }

  MachineInstr *
  generateMemoryBarrier(InstructionGenerationContext &IGC) const override {
    llvm::outs() << "[DEBUG] generateMemoryBarrier\n";
    reportUnimplementedError();
  }

  MachineInstr *generateCall(InstructionGenerationContext &IGC,
                             const Function &Target,
                             MDNode *MetadataMark) const override {
    llvm::outs() << "[DEBUG] generateCall\n";
    reportUnimplementedError();
  }

  MachineInstr *generateCall(InstructionGenerationContext &IGC,
                             const Function &Target, MDNode *MetadataMark,
                             unsigned PreferredCallOpCode) const override {
    llvm::outs() << "[DEBUG] generateCall (with Opcode)\n";
    reportUnimplementedError();
  }

  MachineInstr *generateTailCall(InstructionGenerationContext &IGC,
                                 const Function &Target) const override {
    llvm::outs() << "[DEBUG] generateTailCall\n";
    reportUnimplementedError();
  }

  MachineInstr *
  generateReturn(InstructionGenerationContext &IGC) const override {
    llvm::outs() << "[DEBUG] generateReturn\n";
    reportUnimplementedError();
  }

  MachineInstr *generateNop(InstructionGenerationContext &IGC) const override {
    llvm::outs() << "[DEBUG] generateNop\n";
    reportUnimplementedError();
  }

  unsigned getTransformSequenceLength(InstructionGenerationContext &IGC,
                                      APInt OldValue, APInt NewValue,
                                      MCRegister Register) const override {
    llvm::outs() << "[DEBUG] getTransformSequenceLength\n";
    reportUnimplementedError();
  }
  void transformValueInReg(InstructionGenerationContext &IGC, APInt OldValue,
                           APInt NewValue, MCRegister Register) const override {
    llvm::outs() << "[DEBUG] transformValueInReg\n";
    reportUnimplementedError();
  }

  void loadEffectiveAddressInReg(InstructionGenerationContext &IGC,
                                 MCRegister Register, uint64_t BaseAddr,
                                 uint64_t Stride,
                                 MCRegister IndexReg) const override {
    llvm::outs() << "[DEBUG] loadEffectiveAddressInReg\n";
    reportUnimplementedError();
  }

  size_t getNumImmOperands(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] getNumImmOperands\n";
    reportUnimplementedError();
  }

  MachineOperand generateMemoryRelatedImmediate(
      const MCInstrDesc &InstrDesc, unsigned OperandIdx,
      const StridedImmediate &StridedImm, const SnippyProgramContext &ProgCtx,
      const CommonPolicyConfig &Cfg,
      ArrayRef<MachineOperand> PregeneratedOperands,
      MemAddr Addr) const override {
    llvm::outs() << "[DEBUG] generateMemoryRelatedImmediate\n";
    reportUnimplementedError();
  }

  MachineOperand
  generateTargetOperand(const MCInstrDesc &InstrDesc, unsigned OperandIdx,
                        const StridedImmediate &StridedImm,
                        const SnippyProgramContext &ProgCtx,
                        const CommonPolicyConfig &Cfg) const override {
    llvm::outs() << "[DEBUG] generateTargetOperand\n";
    reportUnimplementedError();
  }

  unsigned getMaxInstrSize() const override { 
    llvm::outs() << "[DEBUG] getMaxInstrSize\n";
    return 8;
    // reportUnimplementedError(); 
  }

  std::set<unsigned>
  getPossibleInstrsSize(const TargetSubtargetInfo &STI) const override {
    llvm::outs() << "[DEBUG] getPossibleInstrsSize\n";
    return { 8 };
  
    // reportUnimplementedError();
  }

  bool isMultipleReg(Register Reg, const MCRegisterInfo &RI) const override {
    llvm::outs() << "[DEBUG] isMultipleReg\n";
    reportUnimplementedError();
  }

  bool isPhysRegClass(unsigned RegClassID,
                      const MCRegisterInfo &RI) const override {
    llvm::outs() << "[DEBUG] isPhysRegClass\n";
    return false;
    // reportUnimplementedError();
  }

  Register getFirstPhysReg(Register Reg,
                           const MCRegisterInfo &RI) const override {
    llvm::outs() << "[DEBUG] getFirstPhysReg\n";
    reportUnimplementedError();
  }

  void
  getSubregsInclusive(Register Reg, const MCRegisterInfo &RI,
                      SmallVectorImpl<Register> &OutPhysRegs) const override {
    llvm::outs() << "[DEBUG] getSubregsInclusive\n";
    
    OutPhysRegs.push_back(Reg);

    for (MCSubRegIterator SubRegs(Reg, &RI); SubRegs.isValid(); ++SubRegs) {
      Register S = *SubRegs;
      if (!is_contained(OutPhysRegs, S))
        OutPhysRegs.push_back(S);
    }

    // reportUnimplementedError();
  }

  void
  getPhysRegsFromUnit(Register RegUnit, const MCRegisterInfo &RI,
                      SmallVectorImpl<Register> &OutPhysRegs) const override {
    llvm::outs() << "[DEBUG] getPhysRegsFromUnit\n";
    OutPhysRegs.clear();
    return;
    // reportUnimplementedError();
  }

  void getPhysRegsWithoutOverlaps(
      Register RegUnit, const MCRegisterInfo &RI,
      SmallVectorImpl<Register> &OutPhysRegs) const override {
    llvm::outs() << "[DEBUG] getPhysRegsWithoutOverlaps\n";
    reportUnimplementedError();
  }

  unsigned getMaxBranchDstMod(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] getMaxBranchDstMod\n";
    reportUnimplementedError();
  }

  MachineBasicBlock *
  getBranchDestination(const MachineInstr &Branch) const override {
    llvm::outs() << "[DEBUG] getBranchDestination\n";
    reportUnimplementedError();
  }

  bool branchNeedsVerification(const MachineInstr &Branch) const override {
    llvm::outs() << "[DEBUG] branchNeedsVerification\n";
    reportUnimplementedError();
  }

  MachineBasicBlock *generateBranch(InstructionGenerationContext &IGC,
                                    const MCInstrDesc &InstrDesc,
                                    MachineBasicBlock *Dst) const override {
    llvm::outs() << "[DEBUG] generateBranch\n";
    reportUnimplementedError();
  }

  MachineInstr &insertIndirectJump(InstructionGenerationContext &IGC,
                                   MachineBasicBlock &TBB,
                                   unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] insertIndirectJump\n";
    reportUnimplementedError();
  }

  bool relaxBranch(MachineInstr &Branch, unsigned Distance,
                   SnippyProgramContext &ProgCtx) const override {
    llvm::outs() << "[DEBUG] relaxBranch\n";
    reportUnimplementedError();
  }

  void insertFallbackBranch(MachineBasicBlock &From, MachineBasicBlock &To,
                            const LLVMState &State) const override {
    llvm::outs() << "[DEBUG] insertFallbackBranch\n";
    reportUnimplementedError();
  }

  bool replaceBranchDest(MachineInstr &Branch,
                         MachineBasicBlock &NewDestMBB) const override {
    llvm::outs() << "[DEBUG] replaceBranchDest\n";
    reportUnimplementedError();
  }

  bool replaceBranchDest(MachineBasicBlock &BranchMBB,
                         MachineBasicBlock &OldDestMBB,
                         MachineBasicBlock &NewDestMBB) const override {
    llvm::outs() << "[DEBUG] replaceBranchDest (overload)\n";
    reportUnimplementedError();
  }

  void addTargetSpecificPasses(PassManagerWrapper &PM) const override {
    llvm::outs() << "[DEBUG] addTargetSpecificPasses\n";
    return;
    // reportUnimplementedError();
  }

  void addTargetLegalizationPasses(PassManagerWrapper &PM) const override {
    llvm::outs() << "[DEBUG] addTargetLegalizationPasses\n";
    return;
    // reportUnimplementedError();
  }

  bool is64Bit(const TargetMachine &TM) const override {
    llvm::outs() << "[DEBUG] is64Bit\n";
    reportUnimplementedError();
  }

  bool isSelfcheckAllowed(const SnippyProgramContext &ProgCtx,
                          const SelfcheckConfig &SelfcheckCfg,
                          const MachineInstr &MI) const override {
    llvm::outs() << "[DEBUG] isSelfcheckAllowed\n";
    reportUnimplementedError();
  }

  bool isAtomicMemInstr(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] isAtomicMemInstr\n";
    reportUnimplementedError();
  }

  bool isVectorInstr(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] isVectorInstr\n";
    reportUnimplementedError();
  }

  void getEncodedMCInstr(const MachineInstr *MI, const MCCodeEmitter &MCCE,
                         AsmPrinter &AP, const MCSubtargetInfo &STI,
                         SmallVector<char> &OutBuf) const override {
    llvm::outs() << "[DEBUG] getEncodedMCInstr\n";
    reportUnimplementedError();
  }

  SmallVector<unsigned>
  getImmutableRegs(const MCRegisterClass &MCRegClass) const override {
    llvm::outs() << "[DEBUG] getImmutableRegs\n";
    reportUnimplementedError();
  }

  const MCRegisterClass &
  getMCRegClassForBranch(SnippyProgramContext &ProgCtx,
                         const MachineInstr &Instr) const override {
    llvm::outs() << "[DEBUG] getMCRegClassForBranch\n";
    reportUnimplementedError();
  }

  MachineInstr &
  updateLoopBranch(MachineInstr &Branch, const MCInstrDesc &InstrDesc,
                   ArrayRef<Register> ReservedRegs) const override {
    llvm::outs() << "[DEBUG] updateLoopBranch\n";
    reportUnimplementedError();
  }

  unsigned
  getNumRegsForLoopBranch(const MCInstrDesc &BranchDesc) const override {
    llvm::outs() << "[DEBUG] getNumRegsForLoopBranch\n";
    reportUnimplementedError();
  }

  unsigned getLoopOverhead() const override { 
    llvm::outs() << "[DEBUG] getLoopOverhead\n";
    reportUnimplementedError(); 
  }

  unsigned getInstrSize(const MachineInstr &Inst,
                        LLVMState &State) const override {
    // PTX - virtual isa
    llvm::outs() << "[DEBUG] getInstrSize\n";
    return 8;
   
    // reportUnimplementedError();
  }

  LoopType getLoopType(MachineInstr &Branch) const override {
    llvm::outs() << "[DEBUG] getLoopType\n";
    reportUnimplementedError();
  }

  LoopCounterInitResult insertLoopInit(InstructionGenerationContext &IGC,
                                       MachineInstr &Branch,
                                       const Branchegram &Branches,
                                       ArrayRef<Register> ReservedRegs,
                                       unsigned NIter) const override {
    llvm::outs() << "[DEBUG] insertLoopInit\n";
    reportUnimplementedError();
  }

  LoopCounterInsertionResult insertLoopCounter(
      InstructionGenerationContext &IGC, MachineInstr &Branch,
      ArrayRef<Register> ReservedRegs, unsigned NIter,
      RegToValueType &ExitingValues,
      const LoopCounterInitResult &CounterInitInfo) const override {
    llvm::outs() << "[DEBUG] insertLoopCounter\n";
    reportUnimplementedError();
  }

  void initializeTargetPasses() const override {
    llvm::outs() << "[DEBUG] initializeTargetPasses\n";
    return;
    // reportUnimplementedError();
  }

  unsigned countAddrsToGenerate(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] countAddrsToGenerate\n";
    return 0;
    // reportUnimplementedError();
  }

  std::pair<AddressParts, MemAddresses>
  breakDownAddr(InstructionGenerationContext &IGC, AddressInfo AddrInfo,
                const MCInstrDesc &InstrDesc,
                MutableArrayRef<planning::PreselectedOpInfo> Preselected,
                unsigned AddrIdx,
                std::optional<MemAddr> MainPart) const override {
    llvm::outs() << "[DEBUG] breakDownAddr\n";
    reportUnimplementedError();
  }

  unsigned getWriteValueSequenceLength(InstructionGenerationContext &IGC,
                                       APInt Value,
                                       MCRegister Register) const override {
    llvm::outs() << "[DEBUG] getWriteValueSequenceLength\n";
    reportUnimplementedError();
  }
  void writeValueToReg(InstructionGenerationContext &IGC, APInt Value,
                       unsigned DstReg) const override {
    llvm::outs() << "[DEBUG] writeValueToReg\n";
    reportUnimplementedError();
  }
  void writeValueToCSR(InstructionGenerationContext &IGC, APInt Value,
                       unsigned DstReg) const override {
    llvm::outs() << "[DEBUG] writeValueToCSR\n";
    reportUnimplementedError();
  }

  void copyRegToReg(InstructionGenerationContext &IGC, MCRegister Rs,
                    MCRegister Rd) const override {
    llvm::outs() << "[DEBUG] copyRegToReg\n";
    reportUnimplementedError();
  }

  MachineInstr *loadSymbolAddress(InstructionGenerationContext &IGC,
                                  unsigned DestReg,
                                  const GlobalValue *Target) const override {
    llvm::outs() << "[DEBUG] loadSymbolAddress\n";
    reportUnimplementedError();
  }

  void loadRegFromAddr(
      InstructionGenerationContext &IGC, uint64_t Addr, MCRegister Reg,
      SnippyMetadata MetadataMark = SnippyMetadata::Support) const override {
    llvm::outs() << "[DEBUG] loadRegFromAddr\n";
    reportUnimplementedError();
  }

  void loadRegFromAddrInReg(
      InstructionGenerationContext &IGC, MCRegister AddrReg, MCRegister Reg,
      SnippyMetadata MetadataMark = SnippyMetadata::Support) const override {
    llvm::outs() << "[DEBUG] loadRegFromAddrInReg\n";
    reportUnimplementedError();
  }

  MCRegister
  getTmpRegisterForCheckSumSelfcheck(InstructionGenerationContext &IGC,
                                     const RegPoolWrapper &RP) const override {
    llvm::outs() << "[DEBUG] getTmpRegisterForCheckSumSelfcheck\n";
    reportUnimplementedError();
  }

  MCRegister generateInitRegisterValueForCheckSumSelfcheck(
      InstructionGenerationContext &IGC, MachineBasicBlock::iterator Ins,
      const RegPoolWrapper &RP, MCRegister Reg) const override {
    llvm::outs() << "[DEBUG] generateInitRegisterValueForCheckSumSelfcheck\n";
    reportUnimplementedError();
  }

  void generateRegMove(MachineBasicBlock &MBB, MachineBasicBlock::iterator Ins,
                       LLVMContext &Context, const MCInstrInfo &InstrInfo,
                       MCRegister SrcReg, MCRegister DstReg) const override {
    llvm::outs() << "[DEBUG] generateRegMove\n";
    reportUnimplementedError();
  }
  void generateCheckSumForSelfcheck(
      InstructionGenerationContext &IGC, MCRegister DstReg, MCRegister SrcReg,
      std::optional<MCRegister> TmpReg) const override {
    llvm::outs() << "[DEBUG] generateCheckSumForSelfcheck\n";
    reportUnimplementedError();
  }

  void generateCheckForCheckSumSelfcheck(InstructionGenerationContext &IGC,
                                         MCRegister AccReg,
                                         MCRegister RefReg) const override {
    llvm::outs() << "[DEBUG] generateCheckForCheckSumSelfcheck\n";
    reportUnimplementedError();
  }

  void storeRegToAddr(InstructionGenerationContext &IGC, uint64_t Addr,
                      MCRegister Reg, unsigned BytesToWrite) const override {
    llvm::outs() << "[DEBUG] storeRegToAddr\n";
    reportUnimplementedError();
  }

  void storeValueToAddr(InstructionGenerationContext &IGC, uint64_t Addr,
                        APInt Value) const override {
    llvm::outs() << "[DEBUG] storeValueToAddr\n";
    reportUnimplementedError();
  }

  void preselectAccessSizeOperand(
      InstructionGenerationContext &IGC, const MCInstrDesc &InstrDesc,
      MutableArrayRef<planning::PreselectedOpInfo> Preselected) const override {
    llvm::outs() << "[DEBUG] preselectAccessSizeOperand\n";
    reportUnimplementedError();
  }

  AddressGenInfo selectAddrGenInfoForInstr(
      const SnippyProgramContext &ProgCtx, unsigned Opcode,
      const MachineBasicBlock &MBB,
      ArrayRef<planning::PreselectedOpInfo> Preselected = {}) const override {
    llvm::outs() << "[DEBUG] selectAddrGenInfoForInstr\n";
    reportUnimplementedError();
  }

  void excludeFromMemRegsForInstr(
      const MCInstrDesc &Instr, const MCRegisterInfo &RI,
      SmallVectorImpl<Register> &Regs,
      std::optional<MemAddr> Addr = std::nullopt,
      const CommonPolicyConfig *Cfg = nullptr) const override {
    llvm::outs() << "[DEBUG] excludeFromMemRegsForInstr\n";
    reportUnimplementedError();
  }

  std::vector<Register> excludeRegsForOperand(InstructionGenerationContext &IGC,
                                              const MCRegisterClass &RC,
                                              const MCInstrDesc &InstrDesc,
                                              unsigned Operand) const override {
    llvm::outs() << "[DEBUG] excludeRegsForOperand\n";
    std::vector<Register> Excluded;
    for (auto Reg : RC)
      if (isSystemReg(Reg))
        Excluded.push_back(Reg);
    return Excluded;
  }

  std::vector<Register> includeRegs(unsigned Opcode,
                                    const MCRegisterClass &RC) const override {
    llvm::outs() << "[DEBUG] includeRegs\n";
    
    // B1RegClassID = 0,
    // B16RegClassID = 1,
    // SpecialRegsRegClassID = 2,
    // B32RegClassID = 3,
    // B32_and_SpecialRegsRegClassID = 4,
    // B64RegClassID = 5,
    // B128RegClassID = 6,
    return {};

    // reportUnimplementedError();
  }

  void reserveRegsIfNeeded(InstructionGenerationContext &IGC, unsigned Opcode,
                           bool isDst, bool isMem,
                           Register Reg) const override {
    llvm::outs() << "[DEBUG] reserveRegsIfNeeded\n";
    // reportUnimplementedError();
  }

  const TargetRegisterClass &getAddrRegClass() const override {
    llvm::outs() << "[DEBUG] getAddrRegClass\n";
    reportUnimplementedError();
  }

  unsigned getAddrRegLen(const TargetMachine &TM) const override {
    llvm::outs() << "[DEBUG] getAddrRegLen\n";
    reportUnimplementedError();
  }

  bool canUseInBurstMode(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] canUseInBurstMode\n";
    reportUnimplementedError();
  }

  bool canInitializeOperand(const MCInstrDesc &InstrDesc, unsigned OpIndex,
                            const LLVMState &State) const override {
    llvm::outs() << "[DEBUG] canInitializeOperand\n";
    reportUnimplementedError();
  }

  bool shouldPreselectOperandInBurstMode(const MCInstrDesc &InstrDesc,
                                         unsigned OpIdx) const override {
    llvm::outs() << "[DEBUG] shouldPreselectOperandInBurstMode\n";
    reportUnimplementedError();
  }

  StridedImmediate getImmOffsetRangeForMemAccessInst(
      const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] getImmOffsetRangeForMemAccessInst\n";
    reportUnimplementedError();
  }

  unsigned getImmOffsetAlignmentForMemAccessInst(
      const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] getImmOffsetAlignmentForMemAccessInst\n";
    reportUnimplementedError();
  }

  size_t getAccessSize(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] getAccessSize\n";
    reportUnimplementedError();
  }

  bool isCall(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] isCall\n";
    return false;
    // reportUnimplementedError(); 
  }
  bool isSPRelative(unsigned Opcode) const override {
    llvm::outs() << "[DEBUG] isSPRelative\n";
    return false;
    // reportUnimplementedError();
  }

  std::vector<OpcodeHistogramEntry>
  getPolicyOverrides(const SnippyProgramContext &ProgCtx,
                     const MachineBasicBlock &MBB) const override {
    llvm::outs() << "[DEBUG] getPolicyOverrides\n";
    reportUnimplementedError();
  }

  std::vector<MCRegister> getGlobalStateRegs() const override {
    llvm::outs() << "[DEBUG] getGlobalStateRegs\n";
    reportUnimplementedError();
  }

  bool canProduceNaN(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] canProduceNaN\n";
    return false;
    // reportUnimplementedError();
  }

  std::optional<std::pair<MCRegister, const MCRegisterClass *>>
  tryGetNaNRegisterAndClass(InstructionGenerationContext &InstrGenCtx,
                            MCRegister Reg) const override {
    llvm::outs() << "[DEBUG] tryGetNaNRegisterAndClass\n";
    reportUnimplementedError();
  }

  bool isFloatingPoint(MCRegister Reg) const override {
    llvm::outs() << "[DEBUG] isFloatingPoint (Reg)\n";
    return false;
    // reportUnimplementedError();
  }

  bool isFloatingPoint(const MCInstrDesc &InstrDesc) const override {
    llvm::outs() << "[DEBUG] isFloatingPoint (InstrDesc)\n";
    return false;
    // reportUnimplementedError();
  }

  std::unique_ptr<AsmPrinter>
  createAsmPrinter(TargetMachine &TM,
                   std::unique_ptr<MCStreamer> Streamer) const override {
    llvm::outs() << "[DEBUG] createAsmPrinter\n";
    const Target &T = TM.getTarget();
  
    // This looks up the built-in NVPTXAsmPrinter in the global registry
    auto *AP = T.createAsmPrinter(TM, std::move(Streamer));
    
    if (!AP) {
      // If it returns null, the NVPTX AsmPrinter wasn't initialized
      snippy::fatal("Error: Built-in NVPTX AsmPrinter not found. "
                    "Did you call LLVMInitializeNVPTXAsmPrinter()?");
    }
    
    return std::unique_ptr<AsmPrinter>(AP);
    // reportUnimplementedError();
  }

  uint8_t getCodeAlignment(const TargetSubtargetInfo &STI) const override {
    llvm::outs() << "[DEBUG] getCodeAlignment\n";
    reportUnimplementedError();
  }

  MachineBasicBlock::iterator generateJump(MachineBasicBlock &MBB,
                                           MachineBasicBlock::iterator Ins,
                                           MachineBasicBlock &TBB,
                                           LLVMState &State) const override {
    llvm::outs() << "[DEBUG] generateJump\n";
    reportUnimplementedError();
  }

  void addAsmPrinterFlags(MachineInstr &MI) const override {}
}; // namespace

bool SnippyNVPTXTarget::matchesArch(Triple::ArchType Arch) const {
  return Arch == Triple::nvptx || Arch == Triple::nvptx64;
}

} // namespace

static SnippyTarget *getTheNVPTXSnippyTarget() {
  static SnippyNVPTXTarget Target;
  return &Target;
}

void InitializeNVPTXSnippyTarget() {
  SnippyTarget::registerTarget(getTheNVPTXSnippyTarget());
}

} // namespace snippy
} // namespace llvm
