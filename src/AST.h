#ifndef AST_H
#define AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

// Forward declarations of classes used in the AST
class AST;
class Expr;
class Program;
class DeclarationInt;
class DeclarationFloat;
class DeclarationBool;
class DeclarationChar;
class DeclarationString;
class DeclarationArray;
class Array;
class ArrayElement;
class ArrayCalculation;
class Final;
class TernaryOp;
class BinaryOp;
class UnaryOp;
class SignedNumber;
class SignedFloating;
class NegExpr;
class Assignment;
class Logic;
class Comparison;
class LogicalExpr;
class IfStmt;
class WhileStmt;
class elifStmt;
class ForStmt;
class ForeachStmt;
class TryCatchStmt;
class MatchStmt;
class PatternStmt;
class PrintStmt;
class Func;
class Parameter;

// ASTVisitor class defines a visitor pattern to traverse the AST
class ASTVisitor
{
public:
  // Virtual visit functions for each AST node type
  virtual void visit(AST &) {}               // Visit the base AST node
  virtual void visit(Expr &) {}              // Visit the expression node
  virtual void visit(Logic &) {}             // Visit the Logic node
  virtual void visit(Program &) {};          // Visit the group of expressions node
  virtual void visit(Final &) = 0;           // Visit the Final node
  virtual void visit(BinaryOp &) = 0;        // Visit the binary operation node
  virtual void visit(UnaryOp &) = 0;
  virtual void visit(SignedNumber &) = 0;
  virtual void visit(NegExpr &) = 0;
  virtual void visit(Assignment &) = 0;      // Visit the assignment expression node
  virtual void visit(DeclarationInt &) = 0;     // Visit the variable declaration node
  virtual void visit(DeclarationBool &) = 0;     // Visit the variable declaration node
  virtual void visit(Comparison &) = 0;      // Visit the Comparison node
  virtual void visit(LogicalExpr &) = 0;     // Visit the LogicalExpr node
  virtual void visit(IfStmt &) = 0;          // Visit the IfStmt node
  virtual void visit(WhileStmt &) = 0;        // Visit the IterStmt node
  virtual void visit(elifStmt &) = 0;        // Visit the elifStmt node
  virtual void visit(ForStmt &) = 0;
  virtual void visit(PrintStmt &) = 0;
};

// AST class serves as the base class for all AST nodes
class AST
{
public:
  virtual ~AST() {}
  virtual void accept(ASTVisitor &V) = 0;    // Accept a visitor for traversal
};

// Expr class represents an expression in the AST
class Expr : public AST
{
public:
  Expr() {}
};

class Logic : public AST
{
public:
  Logic() {}
};

// Program class represents a group of expressions in the AST
class Program : public AST
{
  using dataVector = llvm::SmallVector<AST *>;

private:
  dataVector data;                          // Stores the list of expressions

public:
  Program(llvm::SmallVector<AST *> data) : data(data) {}
  Program() = default;

  llvm::SmallVector<AST *> getdata() { return data; }

  dataVector::const_iterator begin() { return data.begin(); }

  dataVector::const_iterator end() { return data.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Declaration class represents a variable declaration with an initializer in the AST
class DeclarationInt : public Program
{
  using VarVector = llvm::SmallVector<llvm::StringRef>;
  using ValueVector = llvm::SmallVector<Expr *>;
  VarVector Vars;                           // Stores the list of variables
  ValueVector Values;                       // Stores the list of initializers

public:
  // Declaration(llvm::SmallVector<llvm::StringRef> Vars, Expr *E) : Vars(Vars), E(E) {}
  DeclarationInt(llvm::SmallVector<llvm::StringRef> Vars, llvm::SmallVector<Expr *> Values) : Vars(Vars), Values(Values) {}

  VarVector::const_iterator varBegin() { return Vars.begin(); }

  VarVector::const_iterator varEnd() { return Vars.end(); }

  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Declaration class represents a variable declaration with an initializer in the AST
class DeclarationFloat : public Program
{
  using VarVector = llvm::SmallVector<llvm::StringRef>;
  using ValueVector = llvm::SmallVector<Expr *>;
  VarVector Vars;                           // Stores the list of variables
  ValueVector Values;                       // Stores the list of initializers

public:
  // Declaration(llvm::SmallVector<llvm::StringRef> Vars, Expr *E) : Vars(Vars), E(E) {}
  DeclarationFloat(llvm::SmallVector<llvm::StringRef> Vars, llvm::SmallVector<Expr *> Values) : Vars(Vars), Values(Values) {}

  VarVector::const_iterator varBegin() { return Vars.begin(); }

  VarVector::const_iterator varEnd() { return Vars.end(); }

  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Declaration class represents a variable declaration with an initializer in the AST
class DeclarationBool : public Program
{
  using VarVector = llvm::SmallVector<llvm::StringRef>;
  using ValueVector = llvm::SmallVector<Logic *>;
  VarVector Vars;                           // Stores the list of variables
  ValueVector Values;                       // Stores the list of initializers

public:
  // Declaration(llvm::SmallVector<llvm::StringRef> Vars, Expr *E) : Vars(Vars), E(E) {}
  DeclarationBool(llvm::SmallVector<llvm::StringRef> Vars, llvm::SmallVector<Logic *> Values) : Vars(Vars), Values(Values) {}

  VarVector::const_iterator varBegin() { return Vars.begin(); }

  VarVector::const_iterator varEnd() { return Vars.end(); }

  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Declaration class represents a variable declaration with an initializer in the AST
class DeclarationChar : public Program
{
  using VarVector = llvm::SmallVector<llvm::StringRef>;
  using ValueVector = llvm::SmallVector<llvm::StringRef>;
  VarVector Vars;                           // Stores the list of variables
  ValueVector Values;                       // Stores the list of initializers

public:
  // Declaration(llvm::SmallVector<llvm::StringRef> Vars, Expr *E) : Vars(Vars), E(E) {}
  DeclarationChar(llvm::SmallVector<llvm::StringRef> Vars, llvm::SmallVector<llvm::StringRef> Values) : Vars(Vars), Values(Values) {}

  VarVector::const_iterator varBegin() { return Vars.begin(); }

  VarVector::const_iterator varEnd() { return Vars.end(); }

  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Declaration class represents a variable declaration with an initializer in the AST
class DeclarationString : public Program
{
  using VarVector = llvm::SmallVector<llvm::StringRef>;
  using ValueVector = llvm::SmallVector<llvm::StringRef>;
  VarVector Vars;                           // Stores the list of variables
  ValueVector Values;                       // Stores the list of initializers

public:
  // Declaration(llvm::SmallVector<llvm::StringRef> Vars, Expr *E) : Vars(Vars), E(E) {}
  DeclarationString(llvm::SmallVector<llvm::StringRef> Vars, llvm::SmallVector<llvm::StringRef> Values) : Vars(Vars), Values(Values) {}

  VarVector::const_iterator varBegin() { return Vars.begin(); }

  VarVector::const_iterator varEnd() { return Vars.end(); }

  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class DeclarationArray : public Program
{
  using VarVector = llvm::SmallVector<llvm::StringRef>;
  using ValueVector = llvm::SmallVector<Array *>;
  VarVector Vars;                           // Stores the list of variables
  ValueVector Values;                       // Stores the list of initializers

public:
  DeclarationArray(llvm::SmallVector<llvm::StringRef> Vars, llvm::SmallVector<Array *> Values) : Vars(Vars), Values(Values) {}

  VarVector::const_iterator varBegin() { return Vars.begin(); }

  VarVector::const_iterator varEnd() { return Vars.end(); }

  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class Array : public AST
{
public:
  enum DataType
  {
    Int,
    Float,
    Bool,
    Char,
    String,
    Unknown
  };

private:
  using ValueVector = llvm::SmallVector<llvm::StringRef>;
  ValueVector Values;
  DataType Type;
  ArrayCalculation *arrayCalc;

public:
  Array(DataType Type, llvm::SmallVector<llvm::StringRef> Values, ArrayCalculation *arrayCalc) : Type(Type), Values(Values), arrayCalc(arrayCalc) {}

  DataType getType() { return Type; }
  
  ValueVector::const_iterator valBegin() { return Values.begin(); }

  ValueVector::const_iterator valEnd() { return Values.end(); }

  ArrayCalculation *getarrayCalc() { return arrayCalc; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class ArrayElement : public AST
{
private:
  llvm::StringRef var;
  llvm::StringRef index;

public:
  ArrayElement(llvm::StringRef var, llvm::StringRef index) : var(var), index(index) {}

  llvm::StringRef getVar() { return var; }

  llvm::StringRef getIndex() { return index; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class ArrayCalculation : public AST
{
  public:
  enum NumType{
    Int,
    Float
  };

  enum NumSign{
    Pos,
    Neg
  };

  enum Operator{
    Plus,
    Minus,
    Mul,
    Div
  };


private:
  llvm::StringRef ident;
  llvm::StringRef number;
  NumType numberType;
  NumSign numberSign;
  Operator op;

public:
  ArrayCalculation(llvm::StringRef ident, llvm::StringRef number, NumType numberType, NumSign numberSign, Operator op) : ident(ident), number(number), numberType(numberType), numberSign(numberSign), op(op) {}

  llvm::StringRef getIdent() { return ident; }

  llvm::StringRef getNumber() { return number; }

  NumType getNumberType() { return numberType; }

  NumSign getNumberSign() { return numberSign; }

  Operator getOp() { return op; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};



// Final class represents a Final in the AST (either an identifier or a number or true or false)
class Final : public Expr
{
public:
  enum ValueKind
  {
    Ident,
    Number,
    Floating,
    Char,
  };

private:
  ValueKind Kind;                            // Stores the kind of Final (identifier or number or true or false)
  llvm::StringRef Val;                       // Stores the value of the Final

public:
  Final(ValueKind Kind, llvm::StringRef Val) : Kind(Kind), Val(Val) {}

  ValueKind getKind() { return Kind; }

  llvm::StringRef getVal() { return Val; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class TernaryOp : public AST
{
private:
  Logic *Cond;
  Expr *LeftExpr;
  Expr *RightExpr;
  llvm::StringRef LeftChar;
  llvm::StringRef RightChar;
  llvm::StringRef LeftString;
  llvm::StringRef RightString;
  
public:
  TernaryOp(Logic *Cond, Expr *LeftExpr, Expr *RightExpr, llvm::StringRef LeftChar, llvm::StringRef RightChar, llvm::StringRef LeftString, llvm::StringRef RightString) : Cond(Cond), LeftExpr(LeftExpr), RightExpr(RightExpr), LeftChar(LeftChar), RightChar(RightChar), LeftString(LeftString), RightString(RightString) {} 

  Logic *getCond() { return Cond; }

  Expr *getLeftExpr() { return LeftExpr; }

  Expr *getRightExpr() { return RightExpr; }

  llvm::StringRef getLeftChar() { return LeftChar; }

  llvm::StringRef getRightChar() { return RightChar; }

  llvm::StringRef getLeftString() { return LeftString; }

  llvm::StringRef getRightString() { return RightString; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};


// BinaryOp class represents a binary operation in the AST (plus, minus, multiplication, division)
class BinaryOp : public Expr
{
public:
  enum Operator
  {
    Plus,
    Minus,
    Mul,
    Div,
    Mod,
    Exp
  };

private:
  Expr *Left;                               // Left-hand side expression
  Expr *Right;                              // Right-hand side expression
  Operator Op;                              // Operator of the binary operation

public:
  BinaryOp(Operator Op, Expr *L, Expr *R) : Op(Op), Left(L), Right(R) {}

  Expr *getLeft() { return Left; }

  Expr *getRight() { return Right; }

  Operator getOperator() { return Op; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// naryOp class represents a unary operation in the AST (plus plus, minus minus)
class UnaryOp : public Expr
{
public:
  enum Operator
  {
    Plus_plus,
    Minus_minus
  };

private:
  llvm::StringRef Ident;
  Operator Op;
  ArrayElement *AE;                              // Operator of the unary operation

public:
  UnaryOp(Operator Op, llvm::StringRef I, ArrayElement* AE) : Op(Op), Ident(I), AE(AE) {}

  llvm::StringRef getIdent() { return Ident; }

  Operator getOperator() { return Op; }

  ArrayElement* getAE() { return AE; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class SignedNumber : public Expr
{
public:
  enum Sign
  {
    Plus,
    Minus
  };

private:
  llvm::StringRef Value;                              
  Sign s;                              

public:
  SignedNumber(Sign S, llvm::StringRef V) : s(S), Value(V) {}

  llvm::StringRef getValue() { return Value; }

  Sign getSign() { return s; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class SignedFloating : public Expr
{
public:
  enum Sign
  {
    Plus,
    Minus
  };

private:
  llvm::StringRef Value;                              
  Sign s;                              

public:
  SignedFloating(Sign S, llvm::StringRef V) : s(S), Value(V) {}

  llvm::StringRef getValue() { return Value; }

  Sign getSign() { return s; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class NegExpr : public Expr
{

private:
  Expr *expr;                              

public:
  NegExpr(Expr *E) : expr(E) {}

  Expr *getExpr() { return expr; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Assignment class represents an assignment expression in the AST
class Assignment : public Program
{
  public:
  enum AssignKind
  {
    Assign,         // =
    Minus_assign,   // -=
    Plus_assign,    // +=
    Star_assign,    // *=
    Slash_assign,   // /=
};
private:
  Final *Left;                            // Left-hand side Final (identifier)
  Expr *RightExpr;                        // Right-hand side expression
  Logic *RightLogicExpr;                  // Right-hand side logical expression
  llvm::StringRef RightChar;              // Right-hand side char literal
  llvm::StringRef RightString;            // Right-hand side string literal
  Array *RightArray;                      // Right-hand side array literal
  TernaryOp *ternaryOp;                   // Right-hand side ternary operation
  AssignKind AK;                          // Kind of assignment

public:
  Assignment(Final *L, Expr *RE, AssignKind AK, Logic *RL, llvm::StringRef RC, llvm::StringRef RS, Array *RA, TernaryOp *ternaryOp) : Left(L), RightExpr(RE), AK(AK), RightLogicExpr(RL), RightChar(RC), RightString(RS), RightArray(RA), ternaryOp(ternaryOp) {}

  Final *getLeft() { return Left; }

  Expr *getRightExpr() { return RightExpr; }

  Logic *getRightLogic() { return RightLogicExpr; }

  llvm::StringRef getRightChar() { return RightChar; }

  llvm::StringRef getRightString() { return RightString; }

  Array *getRightArray() { return RightArray; }

  TernaryOp *getTernaryOp() { return ternaryOp; }

  AssignKind getAssignKind() { return AK; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// Comparison class represents a comparison expression in the AST
class Comparison : public Logic
{
  public:
  enum Operator
  {
    Equal,          // ==
    Not_equal,      // !=
    Greater,        // >
    Less,           // <
    Greater_equal,  // >=
    Less_equal,     // <=
    True,           //CHECK???
    False,
    Ident           // only one boolean ident
  };
    
private:
  Expr *Left;                                // Left-hand side expression
  Expr *Right;                               // Right-hand side expression
  Operator Op;                               // Kind of assignment

public:
  Comparison(Expr *L, Expr *R, Operator Op) : Left(L), Right(R), Op(Op) {}

  Expr *getLeft() { return Left; }

  Expr *getRight() { return Right; }

  Operator getOperator() { return Op; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

// LogicalExpr class represents a logical expression in the AST
class LogicalExpr : public Logic
{
  public:
  enum Operator
  {
    And,          // &&
    Or,           // ||
  };

private:
  Logic *Left;                                // Left-hand side expression
  Logic *Right;                               // Right-hand side expression
  Operator Op;                                // Kind of assignment

public:
  LogicalExpr(Logic *L, Logic *R, Operator Op) : Left(L), Right(R), Op(Op) {}

  Logic *getLeft() { return Left; }

  Logic *getRight() { return Right; }

  Operator getOperator() { return Op; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class elifStmt : public Program
{
  using Stmts = llvm::SmallVector<AST *>;

private:
  Stmts S;
  Logic *Cond;

public:
  elifStmt(Logic *Cond, llvm::SmallVector<AST *> S) : Cond(Cond), S(S) {}

  Logic *getCond() { return Cond; }

  Stmts::const_iterator begin() { return S.begin(); }

  Stmts::const_iterator end() { return S.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }

};

class IfStmt : public Program
{
using BodyVector = llvm::SmallVector<AST *>;
using elifVector = llvm::SmallVector<elifStmt *>;

private:
  BodyVector ifStmts;
  elifVector elifStmts;
  BodyVector elseStmts;
  Logic *Cond;

public:
  IfStmt(Logic *Cond, llvm::SmallVector<AST *> ifStmts, llvm::SmallVector<AST *> elseStmts, llvm::SmallVector<elifStmt *> elifStmts) : Cond(Cond), ifStmts(ifStmts), elseStmts(elseStmts), elifStmts(elifStmts) {}

  Logic *getCond() { return Cond; }

  BodyVector::const_iterator begin() { return ifStmts.begin(); }

  BodyVector::const_iterator end() { return ifStmts.end(); }

  BodyVector::const_iterator beginElse() { return elseStmts.begin(); }

  BodyVector::const_iterator endElse() { return elseStmts.end(); }

  elifVector::const_iterator beginElif() { return elifStmts.begin(); }

  elifVector::const_iterator endElif() { return elifStmts.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class WhileStmt : public Program
{
using BodyVector = llvm::SmallVector<AST *>;
BodyVector Body;

private:
  Logic *Cond;

public:
  WhileStmt(Logic *Cond, llvm::SmallVector<AST *> Body) : Cond(Cond), Body(Body) {}

  Logic *getCond() { return Cond; }

  BodyVector::const_iterator begin() { return Body.begin(); }

  BodyVector::const_iterator end() { return Body.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};


class ForStmt : public Program
{
using BodyVector = llvm::SmallVector<AST *>;
BodyVector Body;

private:
  DeclarationInt *FirstIntDec;
  DeclarationFloat *FirstFloatDec;
  Logic *Second;
  Assignment *ThirdAssign;
  UnaryOp *ThirdUnary;


public:
  ForStmt(DeclarationInt *FirstIntDec, DeclarationFloat *FirstFloatDec, Logic *Second, Assignment *ThirdAssign, UnaryOp* ThirdUnary, llvm::SmallVector<AST *> Body) : FirstIntDec(FirstIntDec), FirstFloatDec(FirstFloatDec), Second(Second), ThirdAssign(ThirdAssign), ThirdUnary(ThirdUnary), Body(Body) {}

  DeclarationInt *getFirstIntDec() { return FirstIntDec; }

  DeclarationFloat *getFirstFloatDec() { return FirstFloatDec; }

  Logic *getSecond() { return Second; }

  Assignment *getThirdAssign() { return ThirdAssign; }

  UnaryOp *getThirdUnary() { return ThirdUnary; }

  BodyVector::const_iterator begin() { return Body.begin(); }

  BodyVector::const_iterator end() { return Body.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class ForeachStmt : public Program{
  using BodyVector = llvm::SmallVector<AST *>;
  BodyVector Body;

private:
  llvm::StringRef Left;
  llvm::StringRef Right;

public:
  ForeachStmt(llvm::StringRef Left, llvm::StringRef Right, llvm::SmallVector<AST *> Body) : Left(Left), Right(Right), Body(Body) {}

  llvm::StringRef getLeft() { return Left; }

  llvm::StringRef getRight() { return Right; }

  BodyVector::const_iterator begin() { return Body.begin(); }
  
  BodyVector::const_iterator end() { return Body.end(); }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }  
};

class TryCatchStmt : public Program
{
  using BodyVector = llvm::SmallVector<AST *>;
  BodyVector TryBody;
  BodyVector CatchBody;

private:
  llvm::StringRef Error;

public:
  TryCatchStmt(llvm::StringRef Error, BodyVector TryBody, BodyVector CatchBody) : Error(Error), TryBody(TryBody), CatchBody(CatchBody) {}

  llvm::StringRef getError() { return Error; }

  BodyVector getTryBody() { return TryBody; }

  BodyVector getCatchBody() { return CatchBody; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  } 
};

class MatchStmt : public Program
{
private:
  llvm::StringRef Ident;
  llvm::SmallVector<PatternStmt *> Patterns;

public:
  MatchStmt(llvm::StringRef I, llvm::SmallVector<PatternStmt *> P) : Ident(I), Patterns(P) {}

  llvm::StringRef getIdent() { return Ident; }

  llvm::SmallVector<PatternStmt *> getPatterns() { return Patterns; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};


class PatternStmt : public Program
{
  public:
  enum DataType{
    Int,
    Float,
    Char,
    String,
    Default
  };

private:
  DataType ValueType;
  llvm::StringRef Value;
  AST *stmt;

public:
  PatternStmt(llvm::StringRef Value, DataType ValueType, AST *stmt=nullptr) : Value(Value), ValueType(ValueType), stmt(stmt) {}

  llvm::StringRef getValue() { return Value; }

  DataType getValueType() { return ValueType; }

  AST* getStmt() { return stmt; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};


class PrintStmt : public Program
{
private:
  Expr *ExprParam;
  Logic *LogicExprParam;
  Func *FuncParam;
  llvm::StringRef Var;
  
public:
  PrintStmt(Expr *EP, Logic *LEP, Func *FP, llvm::StringRef Var) : ExprParam(EP), LogicExprParam(LEP), FuncParam(FP), Var(Var) {}

  Expr* getExprParam() { return ExprParam; }

  Logic* getLogicExprParam() { return LogicExprParam; }

  Func* getFuncParam() { return FuncParam; }

  llvm::StringRef getVar() { return Var; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class Func : public Program
{
  public:
  enum FuncType{
    Concat,
    Pow,
    Abs,
    Length,
    Min,
    Max,
    Index,
    Add,
    Subtract,
    Multiply,
    Divide
  };

private:
  FuncType type;
  Parameter *param1;
  Parameter *param2;

public:
  Func(FuncType type, Parameter *param1, Parameter *param2) : type(type), param1(param1), param2(param2) {}

  FuncType getType() { return type; }

  Parameter* getParam1() { return param1; }

  Parameter* getParam2() { return param2; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

class Parameter : public AST
{
  public:
  enum ParamType{
    Ident,
    Int,
    Float,
    String
  };

  enum ParamSign{
    Plus,
    Minus,
    None
  };

private:
  ParamSign sign;
  ParamType type;
  llvm::StringRef value;
  
public:
  Parameter(ParamType type, llvm::StringRef value, ParamSign sign=ParamSign::None) : type(type), value(value), sign(sign) {}

  ParamType getType() { return type; }

  llvm::StringRef getValue() { return value; }

  ParamSign getSign() { return sign; }

  virtual void accept(ASTVisitor &V) override
  {
    V.visit(*this);
  }
};

#endif
