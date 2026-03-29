#include "snippy/Target/Target.h"
#include "llvm/Support/YAMLTraits.h"

namespace llvm::snippy {

class PTXConfigInterface : public TargetConfigInterface {
public:
  void mapConfig(yaml::IO &IO) override {
  }

  bool hasConfig() const override { return false; }
};

struct PTXSelfcheckTargetConfig final : public SelfcheckTargetConfigInterface {
  std::unique_ptr<SelfcheckTargetConfigInterface> clone() const override {
    return std::make_unique<PTXSelfcheckTargetConfig>(*this);
  }

  void mapConfig(yaml::IO &IO) override {
    // No-op: No simulator/self-check options for PTX yet.
  }
};


} // namespace llvm::snippy