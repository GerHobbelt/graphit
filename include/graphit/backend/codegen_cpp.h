//
// Created by Yunming Zhang on 2/14/17.
//

#ifndef GRAPHIT_CODEGEN_C_H
#define GRAPHIT_CODEGEN_C_H

#include <graphit/midend/mir.h>
#include <graphit/midend/mir_visitor.h>
#include <graphit/midend/mir_context.h>
#include <iostream>
#include <sstream>

namespace graphit {
    class CodeGenCPP : mir::MIRVisitor{
    public:
        CodeGenCPP(std::ostream &oss) : oss(oss), indentLevel(0) {

        }

        int genCPP(MIRContext* mir_context);

    protected:

        virtual void visit(mir::FuncDecl::Ptr);
        //virtual void visit(mir::VarExpr::Ptr);
        virtual void visit(mir::AddExpr::Ptr);
        virtual void visit(mir::SubExpr::Ptr);
        virtual void visit(mir::IntLiteral::Ptr);
        virtual void visit(mir::VarDecl::Ptr);
        virtual void visit(mir::ScalarType::Ptr scalar_type);

        void indent() { ++indentLevel; }
        void dedent() { --indentLevel; }
        void printIndent() { oss << std::string(2 * indentLevel, ' '); }
        void printBeginIndent() { oss << std::string(2 * indentLevel, ' ') << "{" ; }
        void printEndIndent() { oss << std::string(2 * indentLevel, ' ') << "}"; }
        std::ostream &oss;
        unsigned      indentLevel;
    };
}

#endif //GRAPHIT_CODEGEN_C_H