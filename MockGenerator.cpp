#include "MockGenerator.hpp"
#include <clang/Frontend/CompilerInstance.h>

bool MockGenerator::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
    beginHeaderGuard();
    genIncludes();
    genMock(dyn_cast<CXXRecordDecl>(*declGroup.begin()));
    endHeaderGuard();
    return true;
}

void MockGenerator::beginHeaderGuard()
{
    outs() << "#ifndef " << headerGuardName << "\n";
    outs() << "#define " << headerGuardName << "\n";
}

void MockGenerator::endHeaderGuard()
{
    outs() << "#endif /* " << headerGuardName << " */";
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
    for (CXXRecordDecl::method_iterator method = classDecl->method_begin(); method != classDecl->method_end(); ++method)
    {
        if (method->isPure())
        {
            genMethodMock(*method);
        }
    }
    outs() << "};\n\n";
}
void MockGenerator::genMethodMock(const CXXMethodDecl* method)
{
    outs() << "    MOCK_METHOD" << method->param_size() << "("
           << method->getNameAsString() << ", "
           << method->getCallResultType().getAsString(printingPolicy) << "(";

    for (CXXMethodDecl::param_const_iterator param = method->param_begin(); param != method->param_end(); ++param)
    {
        if (param != method->param_begin())
            outs() << ", ";
        outs() << (*param)->getType().getAsString(printingPolicy);
    }
    
    outs() << "));\n";
}

std::string MockGenerator::toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), std::ptr_fun<int, int>(&std::toupper));
    return s;
}

