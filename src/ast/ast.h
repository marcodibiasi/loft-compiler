#pragma once
#include <ostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <memory>

using namespace std;

struct ModuleImport;
struct Section;
struct Statement;
struct Declaration;
struct Expression;
struct PatternExpr;
struct ModuleExpr;
struct SoundDecl;
struct TrackDecl;
struct ParDecl;
struct PatternDecl;


// MAIN NODE
struct ASTNode {
    virtual ~ASTNode() = default;
};


// PROGRAM NODE
struct Program : public ASTNode {
    vector<unique_ptr<ModuleImport>> modules;  
    vector<unique_ptr<Section>> sections;
};


// MODULE IMPORT
struct ModuleImport : public ASTNode {
    string name;
};


// SECTIONS
struct Section : public ASTNode {
    string name;
    vector<unique_ptr<Statement>> statements;
    vector<unique_ptr<Declaration>> declarations;
    vector<unique_ptr<Expression>> expressions;
    vector<string> used_sections;
};

struct SoundsSection : public Section {
    vector<SoundDecl> sounds;    
};

struct TrackSection : public Section {
    vector<TrackDecl> tracks;
};

struct PlaySection : public Section {
    PlaySection() {name = "play";} 
}; // Entry point


// Statements
struct Statement : public ASTNode {};

struct AssignExpression : public Statement {
    string obj;
    string var; 
    unique_ptr<Expression> expr;
};

struct AssignPattern : public Statement {
    string obj;
    string var; 
    unique_ptr<PatternExpr> expr;
};

struct RunFunction : public Statement {
    string obj;
    string func;
    string value;
}; 

struct PlayTrack : public Statement {
    string track;
    int bpm; 
};


// Declarations
struct Declaration : public ASTNode {
    string name;
};

struct DeclSound : public Declaration {
    unique_ptr<ModuleExpr> expr;
};

struct DeclTrack : public Declaration {
    unique_ptr<ModuleExpr> expr;
};

struct DeclPar : public Declaration {
    unique_ptr<Expression> expr;
};

struct DeclPattern : public Declaration {
    unique_ptr<PatternExpr> expr;
};


// Expressions 
struct Expression : public ASTNode {
    string name; //can be empty
};

struct PatternExpr : public Expression {
    string pattern;
};

struct ModuleExpr : public Expression {
    string module;
    unique_ptr<Expression> expr;
};

struct VariableExpr : public Expression {
    float value; 
};

struct ArrayExpr : public Expression {
    vector<float> vec;
};

struct AccessComponent : public Expression {
    int index;
};



// STATEMENTS 
//  assign expression           obj.var = expression 
//  assign pattern              obj.var > pattern
//  run                         obj:func(value)
//  play track                  >> track !value
//
//
// DECLARATIONS
//  declare sound               sound name = module_expression 
//  declare track               track name = module_expression
//  declare par                 par name = expression 
//  declare pattern             pattern name = pattern
//
// 
// EXPRESSIONS
//  module call                 module(expression)
//  pattern                     |####|####|
//  variable                    * 
//  array                       [*, *]
//  module / array component    module[*] / array[*]
