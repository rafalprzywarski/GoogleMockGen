#include "clang/Frontend/FrontendPluginRegistry.h"
#include "MockGenerator.hpp"

using namespace clang;

namespace
{

class GoogleMockGenAction : public PluginASTAction
{
protected:
    ASTConsumer *CreateASTConsumer(CompilerInstance &CI, llvm::StringRef)
    {
        return new MockGenerator(headerPath, className, llvm::outs);
    }

    bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string>& args)
    {
        headerPath = args[0];
        className = args[1];
        return true;
    }

private:

    std::string headerPath;
    std::string className;
};

}

static FrontendPluginRegistry::Add<GoogleMockGenAction> X("GoogleMockGen", "generate GoogleMock mock");
