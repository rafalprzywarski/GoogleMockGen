#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

namespace
{

class GoogleMockGenAction : public PluginASTAction
{
protected:
    ASTConsumer *CreateASTConsumer(CompilerInstance &CI, llvm::StringRef)
    {
        return 0;
    }

    bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string>& args)
    {
        llvm::outs() << "#include \"Interface1.hpp\"\n#include <gmock/gmock.h>\nstruct Interface1Mock : Interface1 { MOCK_METHOD0(f, void()); };";
        return true;
    }
};

}

static FrontendPluginRegistry::Add<GoogleMockGenAction> X("GoogleMockGen", "generate GoogleMock mock");
