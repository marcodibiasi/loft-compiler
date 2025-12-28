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
struct Stmt;
struct Decl;
struct Expr;
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
    //vector<unique_ptr<Stmt>> statements;
    // vector<unique_ptr<Decl>> declarations;
    // vector<unique_ptr<Expr>> expressions;
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


// TODO:
// define all the statements 
//  assign expression   obj.var = expression 
//  assign pattern      obj.var > pattern
//  run                 obj:func(value)
//  play track          >> track !value
//
// define all the declarations
//  declare sound       sound name = module_expression 
//  declare track       track name = module_expression
//  declare par         par name = expression 
//  declare pattern     pattern name = pattern
//
// define all the expressions
//  module call         module(expression)
//  pattern             |####|####|
//  variable            * / name
//  array               [*, *]
//  module component    module[*]
//  access array        name[*]
