#ifndef MOCKGENERATOR_HPP
#define MOCKGENERATOR_HPP

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/AST.h>
#include <clang/AST/DeclCXX.h>
#include <boost/function.hpp>

using namespace clang;

class MockGenerator : public clang::ASTConsumer
{
public:
    MockGenerator(std::string headerPath, std::string className, boost::function<llvm::raw_ostream&()> outs)
        : headerPath(headerPath), className(className), outs(outs), printingPolicy(getPrintingPolicy()) { }
    virtual bool HandleTopLevelDecl(clang::DeclGroupRef decl);
private:

    std::string headerPath;
    std::string className;
    boost::function<llvm::raw_ostream&()> outs;
    PrintingPolicy printingPolicy;

    void genIncludes();
    void genMock(const CXXRecordDecl *classDecl);
    void genMethodMock(const CXXMethodDecl* method);
    static PrintingPolicy getPrintingPolicy()
    {
        LangOptions lo;
        lo.CPlusPlus = true;
        lo.Bool = true;
        return PrintingPolicy(lo);
    }
};

#endif // MOCKGENERATOR_HPP
