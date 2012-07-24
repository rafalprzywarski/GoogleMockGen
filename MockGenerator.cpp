#include "MockGenerator.hpp"
#include <clang/Frontend/CompilerInstance.h>

bool MockGenerator::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
    genIncludes();
    genMock(dyn_cast<CXXRecordDecl>(*declGroup.begin()));
    return true;
}
void MockGenerator::genIncludes()
{
    outs() << "#include \"" << headerPath << "\"\n";
    outs() << "#include <gmock/gmock.h>\n";
    outs() << "\n";
}

void MockGenerator::genMock(const CXXRecordDecl *classDecl)
{
    outs() << "struct " << className << "Mock : " << className << "\n";
    outs() << "{\n";
    genMethodMock(dyn_cast<FunctionDecl>(*classDecl->method_begin()));
    outs() << "};";
}
void MockGenerator::genMethodMock(const FunctionDecl* method)
{
    outs() << "    MOCK_METHOD" << method->param_size() << "(" << method->getNameAsString() << ", " << method->getCallResultType().getAsString() << "());\n";
}

