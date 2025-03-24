#include "Parser.h"


// main point is that the whole input has been consumed
Program *Parser::parse()
{
    Program *Res = parseProgram();
    return Res;
}

Program *Parser::parseProgram()
{
    llvm::SmallVector<AST *> data;
    
    while (!Tok.is(Token::eoi))
    {
        switch (Tok.getKind())
        {
        case Token::KW_int: {
            DeclarationInt *d_int;
            d_int = parseIntDec();
            if (d_int)
                data.push_back(d_int);
            else
                goto _error;
                
            break;
        }
        case Token::KW_float: {
            DeclarationFloat *d_float;
            d_float = parseFloatDec();
            if (d_float)
                data.push_back(d_float);
            else
                goto _error;
                
            break;
        }
        case Token::KW_bool: {
            DeclarationBool *d_bool;
            d_bool = parseBoolDec();
            if (d_bool)
                data.push_back(d_bool);
            else
                goto _error;

            break;
        }
        case Token::KW_char: {
            DeclarationChar *d_char;
            d_char = parseCharDec();
            if (d_char)
                data.push_back(d_char);
            else
                goto _error;

            break;
        }
        case Token::KW_string: {
            DeclarationString *d_string;
            d_string = parseStringDec();
            if (d_string)
                data.push_back(d_string);
            else
                goto _error;

            break;
        }
        case Token::KW_array: {
            DeclarationArray *d_array;
            d_array = parseArrayDec();
            if (d_array)
                data.push_back(d_array);
            else
                goto _error;

            break;
        }
        case Token::ident: {
            Token prev_token = Tok;
            const char* prev_buffer = Lex.getBuffer();
            UnaryOp *u;
            u = parseUnary();
            if (Tok.is(Token::semicolon))
            {
                if (u)
                {
                    data.push_back(u);
                    break;
                }
                else{
                    goto _error;
                    
                }
            }
            else
            {
                if (u)
                {
                    goto _error;
                }
                else{
                    Tok = prev_token;
                    Lex.setBufferPtr(prev_buffer);
                }
            }
            
            Assignment *a_int;
            Assignment *a_bool;
            Assignment *a_char;
            Assignment *a_string;
            prev_token = Tok;
            prev_buffer = Lex.getBuffer();

            a_char = parseCharAssign();

            if (a_char){
                data.push_back(a_char);
                break;
            }

            Tok = prev_token;
            Lex.setBufferPtr(prev_buffer);

            a_string = parseStringAssign();

            if (a_string){
                data.push_back(a_string);
                break;
            }

            Tok = prev_token;
            Lex.setBufferPtr(prev_buffer);

            a_bool = parseBoolAssign();

            if (a_bool){
                data.push_back(a_bool);
                break;
            }

            Tok = prev_token;
            Lex.setBufferPtr(prev_buffer);

            a_int = parseIntAssign();
            
            if (a_int){
                data.push_back(a_int);
                break;
            }
            else{
                goto _error;
            }
    
        }
        case Token::KW_if: {
            IfStmt *i;
            i = parseIf();
            if (i)
                data.push_back(i);
            else
                goto _error;
            
            break;
        }
        case Token::KW_while: {
            WhileStmt *w;
            w = parseWhile();
            if (w)
                data.push_back(w);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_for: {
            ForStmt *f;
            f = parseFor();
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_foreach: {
            ForeachStmt *fe;
            fe = parseForeach();
            if (fe)
                data.push_back(fe);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_try: {
            TryCatchStmt *tc;
            tc = parseTryCatch();
            if (tc)
                data.push_back(tc);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_match: {
            MatchStmt *m;
            m = parseMatch();
            if (m)
                data.push_back(m);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_print: {
            PrintStmt *p;
            p = parsePrint();
            if (p)
                data.push_back(p);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_concat: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_pow: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_abs: {
            Func *f;
            f = parseFunc(1);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_length: {
            Func *f;
            f = parseFunc();
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_min: {
            Func *f;
            f = parseFunc();
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_max: {
            Func *f;
            f = parseFunc();
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_index: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_add: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_subtract: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_multiply: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_divide: {
            Func *f;
            f = parseFunc(2);
            if (f)
                data.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::start_comment: {
            parseComment();
            if (!Tok.is(Token::end_comment))
                goto _error;
            break;
        }
        default: {
            llvm::errs() << "error1\n";
            error();

            goto _error;
            break;
        }
        }
        advance();
        
    }
    return new Program(data);
_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

DeclarationInt *Parser::parseIntDec()
{
    Expr *E = nullptr;
    llvm::SmallVector<llvm::StringRef> Vars;
    llvm::SmallVector<Expr *> Values;
    
    if (expect(Token::KW_int)){
        goto _error;
    }
    advance();
    
    if (expect(Token::ident)){
        goto _error;
    }

    Vars.push_back(Tok.getText());
    advance();

    if (Tok.is(Token::assign))
    {
        advance();
        E = parseExpr();
        if(E){
            Values.push_back(E);
        }
        else{
            goto _error;
        }
    }
    else
    {
        Values.push_back(new Final(Final::Number, llvm::StringRef("0")));
    }
    
    
    while (Tok.is(Token::comma))
    {
        advance();
        if (expect(Token::ident)){
            goto _error;
        }
            
        Vars.push_back(Tok.getText());
        advance();

        if(Tok.is(Token::assign)){
            advance();
            E = parseExpr();
            if(E){
                Values.push_back(E);
            }
            else{
                goto _error;
            }
        }
        else{
            Values.push_back(new Final(Final::Number, llvm::StringRef("0")));
        }
    }

    if (expect(Token::semicolon)){
        goto _error;
    }


    return new DeclarationInt(Vars, Values);
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

DeclarationFloat *Parser::parseFloatDec()
{
    Expr *E = nullptr;
    llvm::SmallVector<llvm::StringRef> Vars;
    llvm::SmallVector<Expr *> Values;
    
    if (expect(Token::KW_float)){
        goto _error;
    }
    advance();
    
    if (expect(Token::ident)){
        goto _error;
    }

    Vars.push_back(Tok.getText());
    advance();

    if (Tok.is(Token::assign))
    {
        advance();
        E = parseExpr();
        if(E){
            Values.push_back(E);
        }
        else{
            goto _error;
        }
    }
    else
    {
        Values.push_back(new Final(Final::Floating, llvm::StringRef("0.0f")));
    }
    
    
    while (Tok.is(Token::comma))
    {
        advance();
        if (expect(Token::ident)){
            goto _error;
        }
            
        Vars.push_back(Tok.getText());
        advance();

        if(Tok.is(Token::assign)){
            advance();
            E = parseExpr();
            if(E){
                Values.push_back(E);
            }
            else{
                goto _error;
            }
        }
        else{
            Values.push_back(new Final(Final::Floating, llvm::StringRef("0.0f")));
        }
    }

    if (expect(Token::semicolon)){
        goto _error;
    }


    return new DeclarationFloat(Vars, Values);
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

DeclarationBool *Parser::parseBoolDec()
{
    Logic *L = nullptr;
    llvm::SmallVector<llvm::StringRef> Vars;
    llvm::SmallVector<Logic *> Values;
    
    if (expect(Token::KW_bool)){
        goto _error;
    }
    advance();
    
    if (expect(Token::ident)){
        goto _error;
    }

    Vars.push_back(Tok.getText());
    advance();

    if (Tok.is(Token::assign))
    {
        advance();
        L = parseLogic();
        if(L){
            Values.push_back(L);
        }
        else{
            goto _error;
        }
    }
    else
    {
        Values.push_back(new Comparison(nullptr, nullptr, Comparison::False));
    }
    
    
    while (Tok.is(Token::comma))
    {
        advance();
        if (expect(Token::ident)){
            goto _error;
        }
            
        Vars.push_back(Tok.getText());
        advance();

        if(Tok.is(Token::assign)){
            advance();
            L = parseLogic();
            if(L){
                Values.push_back(L);
            }
            else{
                goto _error;
            }
        }
        else{
            Values.push_back(new Comparison(nullptr, nullptr, Comparison::False));
        }
    }

    if (expect(Token::semicolon)){
        goto _error;
    }
    return new DeclarationBool(Vars, Values);
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

DeclarationChar* Parser::parseCharDec(){
    llvm::SmallVector<llvm::StringRef> Vars;
    llvm::SmallVector<llvm::StringRef> Values;
    
    if (expect(Token::KW_char)){
        goto _error;
    }
    advance();
    
    if (expect(Token::ident)){
        goto _error;
    }

    Vars.push_back(Tok.getText());
    advance();

    if (Tok.is(Token::assign))
    {
        advance();
        if(Tok.is(Token::character)){
            Values.push_back(Tok.getText());
            advance();
        }
        else{
            goto _error;
        }
    }
    else
    {
        Values.push_back(llvm::StringRef("\u0000"));
    }
    
    
    while (Tok.is(Token::comma))
    {
        advance();
        if (expect(Token::ident)){
            goto _error;
        }
            
        Vars.push_back(Tok.getText());
        advance();

        if (Tok.is(Token::assign))
        {
            advance();
            if(Tok.is(Token::character)){
                Values.push_back(Tok.getText());
                advance();
            }
            else{
                goto _error;
            }
        }
        else
        {
            Values.push_back(llvm::StringRef("\u0000"));
        }
    }

    if (expect(Token::semicolon)){
        goto _error;
    }
    return new DeclarationChar(Vars, Values);
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

DeclarationString* Parser::parseStringDec(){
    llvm::SmallVector<llvm::StringRef> Vars;
    llvm::SmallVector<llvm::StringRef> Values;
    
    if (expect(Token::KW_string)){
        goto _error;
    }
    advance();
    
    if (expect(Token::ident)){
        goto _error;
    }

    Vars.push_back(Tok.getText());
    advance();

    if (Tok.is(Token::assign))
    {
        advance();
        if(Tok.is(Token::string)){
            Values.push_back(Tok.getText());
            advance();
        }
        else{
            goto _error;
        }
    }
    else
    {
        Values.push_back(llvm::StringRef("nullptr"));
    }
    
    
    while (Tok.is(Token::comma))
    {
        advance();
        if (expect(Token::ident)){
            goto _error;
        }
            
        Vars.push_back(Tok.getText());
        advance();

        if (Tok.is(Token::assign))
        {
            advance();
            if(Tok.is(Token::string)){
                Values.push_back(Tok.getText());
                advance();
            }
            else{
                goto _error;
            }
        }
        else
        {
            Values.push_back(llvm::StringRef("nullptr"));
        }
    }

    if (expect(Token::semicolon)){
        goto _error;
    }
    return new DeclarationString(Vars, Values);
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

DeclarationArray *Parser::parseArrayDec()
{
    Array *A = nullptr;
    llvm::SmallVector<llvm::StringRef> Vars;
    llvm::SmallVector<Array *> Values;
    
    if (expect(Token::KW_array)){
        goto _error;
    }
    advance();
    
    if (expect(Token::ident)){
        goto _error;
    }

    Vars.push_back(Tok.getText());
    advance();

    if (Tok.is(Token::assign))
    {
        advance();
        A = parseArray();
        if(A){
            Values.push_back(A);
        }
        else{
            goto _error;
        }
    }
    else
    {
        Values.push_back(nullptr);
    }
    
    
    while (Tok.is(Token::comma))
    {
        advance();
        if (expect(Token::ident)){
            goto _error;
        }
            
        Vars.push_back(Tok.getText());
        advance();

        if(Tok.is(Token::assign)){
            advance();
            A = parseArray();
            if(A){
                Values.push_back(A);
            }
            else{
                goto _error;
            }
        }
        else{
            Values.push_back(nullptr);
        }
    }

    if (expect(Token::semicolon)){
        goto _error;
    }


    return new DeclarationArray(Vars, Values);
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Assignment *Parser::parseBoolAssign()
{
    Final *F = nullptr;
    Assignment::AssignKind AK;
    Logic *L = nullptr;

    F = (Final *)(parseFinal());
    if (F == nullptr)
    {
        goto _error;
    }
    
    if (Tok.is(Token::assign))
    {
        AK = Assignment::Assign;
        advance();
        L = parseLogic();   // check if expr is logical

        if(L)
        {
            if (!Tok.is(Token::semicolon))
            {
                goto _error;
            }
            return new Assignment(F, nullptr, AK, L, llvm::StringRef(), llvm::StringRef());
        }
        else
            goto _error;
    }
    else
    {
        goto _error;
    }
    
_error:
        while (Tok.getKind() != Token::eoi)
            advance();
        return nullptr;
    
}

Assignment *Parser::parseIntAssign()
{
    Expr *E = nullptr;
    Final *F = nullptr;
    Assignment::AssignKind AK;
    F = (Final *)(parseFinal());
    if (F == nullptr)
    {
        goto _error;
    }
    
    if (Tok.is(Token::assign))
    {
        AK = Assignment::Assign;
    }
    else if (Tok.is(Token::plus_assign))
    {
        AK = Assignment::Plus_assign;
    }
    else if (Tok.is(Token::minus_assign))
    {
        AK = Assignment::Minus_assign;
    }
    else if (Tok.is(Token::star_assign))
    {
        AK = Assignment::Star_assign;
    }
    else if (Tok.is(Token::slash_assign))
    {
        AK = Assignment::Slash_assign;
    }
    else
    {
        goto _error;
    }
    advance();
    E = parseExpr();    // check for mathematical expr
    if(E){
        return new Assignment(F, E, AK, nullptr, llvm::StringRef(), llvm::StringRef());
    }
    else{
        goto _error;
    }

_error:
        while (Tok.getKind() != Token::eoi)
            advance();
        return nullptr;
}

Assignment *Parser::parseCharAssign(){
    Final *F = nullptr;
    llvm::StringRef value;
    F = (Final *)(parseFinal());

    if (F == nullptr){
        goto _error;
    }

    if (expect(Token::assign)){
        goto _error;
    }
    advance();

    if (expect(Token::character)){
        goto _error;
    }
    value = Tok.getText();
    advance();

    if (expect(Token::semicolon)){
        goto _error;
    }

    return new Assignment(F, nullptr, Assignment::Assign, nullptr, value, llvm::StringRef());

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;    
}

Assignment *Parser::parseStringAssign(){
    Final *F = nullptr;
    llvm::StringRef value;
    F = (Final *)(parseFinal());

    if (F == nullptr){
        goto _error;
    }

    if (expect(Token::assign)){
        goto _error;
    }
    advance();

    if (expect(Token::string)){
        goto _error;
    }
    value = Tok.getText();
    advance();

    if (expect(Token::semicolon)){
        goto _error;
    }

    return new Assignment(F, nullptr, Assignment::Assign, nullptr, llvm::StringRef(), value);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;    
}


UnaryOp *Parser::parseUnary()
{
    UnaryOp* Res = nullptr;
    llvm::StringRef var;

    if (expect(Token::ident)){
        goto _error;
    }

    var = Tok.getText();
    advance();

    if (Tok.getKind() == Token::plus_plus){
        Res = new UnaryOp(UnaryOp::Plus_plus, var);
    }
    else if(Tok.getKind() == Token::minus_minus){
        Res = new UnaryOp(UnaryOp::Minus_minus, var);
    }
    else{
        goto _error;
    }

    advance();

    return Res;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}
Expr *Parser::parseExpr()
{
    Expr *Left = parseTerm();

    if (Left == nullptr)
    {
        goto _error;
    }
    
    while (Tok.isOneOf(Token::plus, Token::minus))
    {
        BinaryOp::Operator Op;
        if (Tok.is(Token::plus))
            Op = BinaryOp::Plus;
        else if (Tok.is(Token::minus))
            Op = BinaryOp::Minus;
        else {
            llvm::errs() << "error2\n";
            error();

            goto _error;
        }
        advance();
        Expr *Right = parseTerm();
        if (Right == nullptr)
        {
            goto _error;
        }
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Expr *Parser::parseTerm()
{
    Expr *Left = parseFactor();
    if (Left == nullptr)
    {
        goto _error;
    }
    while (Tok.isOneOf(Token::star, Token::mod, Token::slash))
    {
        BinaryOp::Operator Op;
        if (Tok.is(Token::star))
            Op = BinaryOp::Mul;
        else if (Tok.is(Token::slash))
            Op = BinaryOp::Div;
        else if (Tok.is(Token::mod))
            Op = BinaryOp::Mod;
        else {
            llvm::errs() << "error3\n";
            error();

            goto _error;
        }
        advance();
        Expr *Right = parseFactor();
        if (Right == nullptr)
        {
            goto _error;
        }
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Expr *Parser::parseFactor()
{
    Expr *Left = parseFinal();
    if (Left == nullptr)
    {
        goto _error;
    }
    while (Tok.is(Token::exp))
    {
        BinaryOp::Operator Op;
        if (Tok.is(Token::exp))
            Op = BinaryOp::Exp;
        else {
            llvm::errs() << "error4\n";
            error();
            goto _error;
        }
        advance();
        Expr *Right = parseFactor();
        if (Right == nullptr)
        {
            goto _error;
        }
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Expr *Parser::parseFinal()
{
    Expr *Res = nullptr;
    switch (Tok.getKind())
    {
    case Token::number:{
        Res = new Final(Final::Number, Tok.getText());
        advance();
        break;
    }
    case Token::floating:{
        Res = new Final(Final::Floating, Tok.getText());
        advance();
        break;
    }
    case Token::ident: {
        Res = new Final(Final::Ident, Tok.getText());
        Token prev_tok = Tok;
        const char* prev_buffer = Lex.getBuffer();
        Expr* u = parseUnary();
        if(u)
            return u;
        else{
            Tok = prev_tok;
            Lex.setBufferPtr(prev_buffer);
            advance();
        }
        break;
    }
    case Token::plus:{
        advance();
        if(Tok.getKind() == Token::number){
            Res = new SignedNumber(SignedNumber::Plus, Tok.getText());
            advance();
            break;
        }
        else if(Tok.getKind() == Token::floating){
            Res = new SignedFloating(SignedFloating::Plus, Tok.getText());
            advance();
            break;
        }
        goto _error;
    }

    case Token::minus:{
        advance();
        if (Tok.getKind() == Token::number){
            Res = new SignedNumber(SignedNumber::Minus, Tok.getText());
            advance();
            break;
        }
        else if(Tok.getKind() == Token::floating){
            Res = new SignedFloating(SignedFloating::Minus, Tok.getText());
            advance();
            break;
        }
        goto _error;
    }
    case Token::minus_paren:{
        advance();
        Expr *math_expr = parseExpr();
        if(math_expr == nullptr)
            goto _error;
        Res = new NegExpr(math_expr);
        if (!consume(Token::r_paren))
            break;
        
        goto _error;

    }
    case Token::l_paren:{
        advance();
        Res = parseExpr();
        if(Res == nullptr){
            goto _error;
        }
        if (!consume(Token::r_paren))
            break;
        
    }
    default:{
        llvm::errs() << "error5\n";
        error();
        goto _error;
    }
    }
    return Res;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Array* Parser::parseArray(){
    Token::TokenKind kind;
    llvm::SmallVector<llvm::StringRef> Values;

    if (expect(Token::l_bracket)){
        goto _error;
    }
    advance();

    if (Tok.isOneOf(Token::number, Token::floating, Token::character, 
        Token::string, Token::KW_true, Token::KW_false)){

            Values.push_back(Tok.getText());
            kind = Tok.getKind();
            advance();

    }
    else{
        goto _error;
    }

    while (Tok.is(Token::comma)){
        
        advance();
        if (Tok.getKind() == kind){
            Values.push_back(Tok.getText());
            advance();
            continue;
        }
        else if ((kind == Token::KW_true || kind == Token::KW_false) && Tok.isOneOf(Token::KW_true, Token::KW_false)){
            Values.push_back(Tok.getText());
            advance();
            continue;
        }
        else if ((kind == Token::number && Tok.is(Token::floating)) || (kind == Token::floating && Tok.is(Token::number))){
            kind = Token::floating;
            Values.push_back(Tok.getText());
            advance();
            continue;
        }

        goto _error;

    }

    if (expect(Token::r_bracket)){
        goto _error;
    }
    advance();

    switch (kind){
        case Token::number: return new Array(Array::Int, Values);
        case Token::floating: return new Array(Array::Float, Values);
        case Token::KW_true: return new Array(Array::Bool, Values); 
        case Token::KW_false: return new Array(Array::Bool, Values); 
        case Token::character: return new Array(Array::Char, Values); 
        case Token::string: return new Array(Array::String, Values); 
    }

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}


Logic *Parser::parseComparison()
{
    Logic *Res = nullptr;
    Final *Ident = nullptr;
    Expr *Left = nullptr;
    Expr *Right = nullptr;
    Token prev_Tok;
    const char* prev_buffer;
    if (Tok.is(Token::l_paren)) {
        advance();
        Res = parseLogic();
        if (Res == nullptr)
        {
            goto _error;
        }
        if (consume(Token::r_paren))
            goto _error;
    }
    else {
        if(Tok.is(Token::KW_true)){
            Res = new Comparison(nullptr, nullptr, Comparison::True);
            advance();
            return Res;
        }
        else if(Tok.is(Token::KW_false)){
            Res = new Comparison(nullptr, nullptr, Comparison::False);
            advance();
            return Res;
        }
        else if(Tok.is(Token::ident)){
            Ident = new Final(Final::Ident, Tok.getText());
        }
        prev_Tok = Tok;
        prev_buffer = Lex.getBuffer();
        Left = parseExpr();
        if(Left == nullptr)
            goto _error;
        

        Comparison::Operator Op;
            if (Tok.is(Token::eq))
                Op = Comparison::Equal;
            else if (Tok.is(Token::neq))
                Op = Comparison::Not_equal;
            else if (Tok.is(Token::gt))
                Op = Comparison::Greater;
            else if (Tok.is(Token::lt))
                Op = Comparison::Less;
            else if (Tok.is(Token::gte))
                Op = Comparison::Greater_equal;
            else if (Tok.is(Token::lte))
                Op = Comparison::Less_equal;    
            else {
                if (Ident){
                    Tok = prev_Tok;
                    Lex.setBufferPtr(prev_buffer);
                    Res = new Comparison(Ident, nullptr, Comparison::Ident);
                    advance();
                    return Res;
                }
                goto _error;
            }
            advance();
            Right = parseExpr();
            if (Right == nullptr)
            {
                goto _error;
            }
            
            Res = new Comparison(Left, Right, Op);
    }
    
    return Res;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Logic *Parser::parseLogic()
{
    Logic *Left = parseComparison();
    Logic *Right;
    
    if (Left == nullptr)
    {
        goto _error;
    }
    while (Tok.isOneOf(Token::KW_and, Token::KW_or))
    {
        LogicalExpr::Operator Op;
        if (Tok.is(Token::KW_and))
            Op = LogicalExpr::And;
        else if (Tok.is(Token::KW_or))
            Op = LogicalExpr::Or;
        else {
            llvm::errs() << "error6\n";
            error();

            goto _error;
        }
        advance();
        Right = parseComparison();
        if (Right == nullptr)
        {
            goto _error;
        }
        Left = new LogicalExpr(Left, Right, Op);
    }
    return Left;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

IfStmt *Parser::parseIf()
{
    llvm::SmallVector<AST *> ifStmts;
    llvm::SmallVector<AST *> elseStmts;
    llvm::SmallVector<elifStmt *> elifStmts;
    llvm::SmallVector<AST *> Stmts;
    Logic *Cond = nullptr;
    Token prev_token_if;
    const char* prev_buffer_if;
    Token prev_token_elif;
    const char* prev_buffer_elif;
    bool hasElif = false;
    bool hasElse = false;


    if (expect(Token::KW_if)){
        goto _error;
    }

    advance();

    if (expect(Token::l_paren)){
        goto _error;
    }

    advance();

    Cond = parseLogic();
    if (Cond == nullptr)
    {
        goto _error;
    }

    if (expect(Token::r_paren)){
        goto _error;
    }
        
    advance();

    if (expect(Token::l_brace)){
        goto _error;
    }

    advance();
    
    ifStmts = getBody();
        
    if(ifStmts.empty())
        goto _error;
    
    prev_token_if = Tok;
    prev_buffer_if = Lex.getBuffer();
    
    advance();

    while (true)
    {
        if (Tok.is(Token::KW_else))
        {
            advance();
            if (Tok.is(Token::KW_if))
            {
                hasElif = true;
                advance();
                
                if (expect(Token::l_paren)){
                    goto _error;
                }

                advance();

                Logic *Cond = parseLogic();

                if (Cond == nullptr)
                {
                    goto _error;
                }

                if (expect(Token::r_paren)){
                    goto _error;
                }

                advance();

                if (expect(Token::l_brace)){
                    goto _error;
                }

                advance();

                Stmts = getBody();
                prev_token_elif = Tok;
                prev_buffer_elif = Lex.getBuffer();
                
                if(!Stmts.empty())
                    advance();
                else
                    goto _error;
                
                elifStmt *elif = new elifStmt(Cond, Stmts);
                elifStmts.push_back(elif);
            }
            else
            {
                hasElse = true;

                if (expect(Token::l_brace)){
                    goto _error;
                }

                advance();

                elseStmts = getBody();
                
                if(elseStmts.empty())
                    goto _error;

                break;
            }
        }
        else
            break;
    }

    if(hasElif && !hasElse){
        Tok = prev_token_elif;
        Lex.setBufferPtr(prev_buffer_elif);
    }
    else if(!hasElif && !hasElse){
        Tok = prev_token_if;
        Lex.setBufferPtr(prev_buffer_if);
    }
        
    return new IfStmt(Cond, ifStmts, elseStmts, elifStmts);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}



PrintStmt *Parser::parsePrint()
{
    Expr* E = nullptr;
    Logic* L = nullptr;

    if (expect(Token::KW_print)){
        goto _error;
    }
    advance();
    if (expect(Token::l_paren)){
        goto _error;
    }
    advance();

    E = parseExpr();

    if (!E){
        goto _error;
    }

    if (expect(Token::r_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::semicolon)){
        goto _error;
    }

    return new PrintStmt(E, nullptr, llvm::StringRef("x"));

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

Func* Parser::parseFunc(int argumentCount){
    Func::FuncType type;
    Parameter *param1 = nullptr;
    Parameter *param2 = nullptr;

    switch (Tok.getKind())
    {
    case Token::KW_abs:
        type = Func::Abs;
        break;

    case Token::KW_length:
        type = Func::Length;
        break;

    case Token::KW_min:
        type = Func::Min;
        break;

    case Token::KW_max:
        type = Func::Max;
        break;

    case Token::KW_concat:
        type = Func::Concat;
        break;
    
    case Token::KW_pow:
        type = Func::Pow;
        break;

    case Token::KW_index:
        type = Func::Index;
        break;

    case Token::KW_add:
        type = Func::Add;
        break;

    case Token::KW_subtract:
        type = Func::Subtract;
        break;

    case Token::KW_multiply:
        type = Func::Multiply;
        break;

    case Token::KW_divide:
        type = Func::Divide;
        break;
    
    default:
        goto _error;
    }

    advance();

    if (expect(Token::l_paren)){
        goto _error;
    }

    advance();

    switch (Tok.getKind())
    {
    case Token::ident:
        param1 = new Parameter(Parameter::Ident, Tok.getText());
        break;

    case Token::number:
        param1 = new Parameter(Parameter::Int, Tok.getText(), Parameter::Plus);
        break;

    case Token::floating:
        param1 = new Parameter(Parameter::Float, Tok.getText(), Parameter::Plus);
        break;

    case Token::string:
        param1 = new Parameter(Parameter::String, Tok.getText());
        break;

    case Token::plus: {
        
        advance();
        if (Tok.is(Token::number)){
            param1 = new Parameter(Parameter::Int, Tok.getText(), Parameter::Plus);
            break;
        }
        else if (Tok.is(Token::floating)){
            param1 = new Parameter(Parameter::Float, Tok.getText(), Parameter::Plus);
            break;
        }

        goto _error;

    }

    case Token::minus: {
        
        advance();
        if (Tok.is(Token::number)){
            param1 = new Parameter(Parameter::Int, Tok.getText(), Parameter::Minus);
            break;
        }
        else if (Tok.is(Token::floating)){
            param1 = new Parameter(Parameter::Float, Tok.getText(), Parameter::Minus);
            break;
        }

        goto _error;

    }
    
    default:
        goto _error;
    }

    advance();

    if (argumentCount == 2){

        if (expect(Token::comma)){
            goto _error;
        }

        advance();

        switch (Tok.getKind())
        {
        case Token::ident:
            param2 = new Parameter(Parameter::Ident, Tok.getText());
            break;

        case Token::number:
            param2 = new Parameter(Parameter::Int, Tok.getText(), Parameter::Plus);
            break;

        case Token::floating:
            param2 = new Parameter(Parameter::Float, Tok.getText(), Parameter::Plus);
            break;

        case Token::string:
            param2 = new Parameter(Parameter::String, Tok.getText());
            break;

        case Token::plus: {
        
            advance();
            if (Tok.is(Token::number)){
                param2 = new Parameter(Parameter::Int, Tok.getText(), Parameter::Plus);
                break;
            }
            else if (Tok.is(Token::floating)){
                param2 = new Parameter(Parameter::Float, Tok.getText(), Parameter::Plus);
                break;
            }

            goto _error;

        }

        case Token::minus: {
        
            advance();
            if (Tok.is(Token::number)){
                param2 = new Parameter(Parameter::Int, Tok.getText(), Parameter::Minus);
                break;
            }
            else if (Tok.is(Token::floating)){
                param2 = new Parameter(Parameter::Float, Tok.getText(), Parameter::Minus);
                break;
            }

            goto _error;

        }
        
        default:
            goto _error;
        }

        advance();
    }

    if (expect(Token::r_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::semicolon)){
        goto _error;
    }

    return new Func(type, param1, param2);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

WhileStmt *Parser::parseWhile()
{
    llvm::SmallVector<AST *> Body;
    Logic *Cond = nullptr;

    if (expect(Token::KW_while)){
        goto _error;
    }
        
    advance();

    if(expect(Token::l_paren)){
        goto _error;
    }

    advance();

    Cond = parseLogic();
    if (Cond == nullptr)
    {
        goto _error;
    }
    if(expect(Token::r_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::l_brace)){
        goto _error;
    }

    advance();

    Body = getBody();
    if(Body.empty())
        goto _error;
        

    return new WhileStmt(Cond, Body);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

ForStmt *Parser::parseFor()
{
    Assignment *First = nullptr;
    Logic *Second = nullptr;
    Assignment *ThirdAssign = nullptr;
    UnaryOp *ThirdUnary = nullptr;
    llvm::SmallVector<AST *> Body;
    Token prev_token;
    const char* prev_buffer;

    if (expect(Token::KW_for)){
        goto _error;
    }
        
    advance();

    if(expect(Token::l_paren)){
        goto _error;
    }

    advance();

    First = parseIntAssign();

    if (First == nullptr)
        goto _error;
        
    if (First->getAssignKind() != Assignment::Assign)    // The first part can only have a '=' sign
        goto _error;

    if(expect(Token::semicolon)){
        goto _error;
    }

    advance();

    Second = parseLogic();

    if (Second == nullptr)
        goto _error;
        
    if(expect(Token::semicolon)){
        goto _error;
    }

    advance();

    prev_token = Tok;
    prev_buffer = Lex.getBuffer();

    ThirdAssign = parseIntAssign();

    if (ThirdAssign == nullptr){
        Tok = prev_token;
        Lex.setBufferPtr(prev_buffer);

        ThirdUnary = parseUnary();
        if (ThirdUnary == nullptr){
            goto _error;
        }

    }
    else{
        if(ThirdAssign->getAssignKind() == Assignment::Assign)   // The third part cannot have only '=' sign
            goto _error;
    }


    if(expect(Token::r_paren)){
        goto _error;
    }

    advance();

    if(expect(Token::l_brace)){
        goto _error;
    }

    advance();

    Body = getBody();

    if (Body.empty())
        goto _error;

    return new ForStmt(First, Second, ThirdAssign, ThirdUnary, Body);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;  

}

ForeachStmt* Parser::parseForeach(){
    llvm::StringRef Left;
    llvm::StringRef Right;
    llvm::SmallVector<AST *> Body;
    
    if (expect(Token::KW_foreach)){
        goto _error;
    }

    advance();

    if (expect(Token::l_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::ident)){
        goto _error;
    }

    Left = Tok.getText();
    advance();

    if (expect(Token::KW_in)){
        goto _error;
    }

    advance();

    if (expect(Token::ident)){
        goto _error;
    }

    Right = Tok.getText();
    advance();

    if (expect(Token::r_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::l_brace)){
        goto _error;
    }

    advance();

    Body = getBody();

    if (Body.empty())
        goto _error; 

    return new ForeachStmt(Left, Right, Body);   

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;   
}


TryCatchStmt* Parser::parseTryCatch(){
    llvm::StringRef Error;
    llvm::SmallVector<AST *> TryBody;
    llvm::SmallVector<AST *> CatchBody;
    
    if (expect(Token::KW_try)){
        goto _error;
    }

    advance();

    if (expect(Token::l_brace)){
        goto _error;
    }

    advance();

    TryBody = getBody();
    if (TryBody.empty())
        goto _error;

    advance(); 

    if (expect(Token::KW_catch)){
        goto _error;
    }

    advance();

    if (expect(Token::l_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::KW_error)){
        goto _error;
    }

    advance();
    

    if (expect(Token::ident)){
        goto _error;
    }

    Error = Tok.getText();
    advance();

    if (expect(Token::r_paren)){
        goto _error;
    }

    advance();

    if (expect(Token::l_brace)){
        goto _error;
    }

    advance();

    CatchBody = getBody();
    if (CatchBody.empty())
        goto _error; 

    return new TryCatchStmt(Error, TryBody, CatchBody);     

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

MatchStmt* Parser::parseMatch(){
  llvm::StringRef Ident;
  llvm::SmallVector<PatternStmt *> Patterns;

  if (expect(Token::KW_match)){
    goto _error;
  }

  advance();

  if (expect(Token::ident)){
    goto _error;
  }

  Ident = Tok.getText();
  advance();

  if (expect(Token::l_brace)){
    goto _error;
  }

  do
  {

    advance();
    if (Tok.is(Token::r_brace))
        break;
    
    PatternStmt *P = nullptr;
    P = parsePattern();
    
    if(P){
        Patterns.push_back(P);
    }
    else{
        goto _error;
    }

    if (Tok.is(Token::r_brace))
        break;
    if (expect(Token::comma))
        goto _error;
    
  } while(true);

  return new MatchStmt(Ident, Patterns);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;    
}

PatternStmt* Parser::parsePattern(){
    llvm::StringRef Value;
    PatternStmt::DataType ValueType;
    AST *stmt;
    
    switch (Tok.getKind())
    {
    case Token::number:
        ValueType = PatternStmt::Int;
        break;

    case Token::floating:
        ValueType = PatternStmt::Float;
        break;

    case Token::character:
        ValueType = PatternStmt::Char;
        break;

    case Token::string:
        ValueType = PatternStmt::String;
        break;

    case Token::underscore:
        ValueType = PatternStmt::Default;
        break;
    
    default:
        goto _error;
    }

    Value = Tok.getText();
    advance();

    if (expect(Token::arrow)){
        goto _error;
    }

    advance();

    stmt = parseStmt();
    if (!stmt)
        goto _error; 

    return new PatternStmt(Value, ValueType, stmt);

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}

void Parser::parseComment()
{
    if (expect(Token::start_comment)) {
        goto _error;
    }
    advance();

    while (!Tok.isOneOf(Token::end_comment, Token::eoi)) advance();

    return;
_error: 
    while (Tok.getKind() != Token::eoi)
        advance();
}

llvm::SmallVector<AST *> Parser::getBody(bool patternBody)
{
    llvm::SmallVector<AST *> body;
    while (!Tok.is(Token::r_brace))
    {
        switch (Tok.getKind())
        {
        
        case Token::ident:{
            Token prev_token = Tok;
            const char* prev_buffer = Lex.getBuffer();
            UnaryOp *u;
            u = parseUnary();
            if (Tok.is(Token::semicolon))
            {
                if (u)
                {
                    body.push_back(u);
                    break;
                }
                else{

                    goto _error;
                }
                    
            }
            else
            {
                if (u)
                {

                    goto _error;
                }
                else{
                    Tok = prev_token;
                    Lex.setBufferPtr(prev_buffer);
                }
                    
            }

            
            Assignment *a_int;
            Assignment *a_bool;
            prev_token = Tok;
            prev_buffer = Lex.getBuffer();

            a_bool = parseBoolAssign();

            if (a_bool){
                body.push_back(a_bool);
                break;
            }
            Tok = prev_token;
            Lex.setBufferPtr(prev_buffer);

            a_int = parseIntAssign();
            if (a_int)
                body.push_back(a_int);
            else
                goto _error;
            if (!Tok.is(Token::semicolon))
            {
                goto _error;
            }

            break;
        }
        case Token::KW_if: {
            IfStmt *i;
            i = parseIf();
            if (i)
                body.push_back(i);
            else
                goto _error;
            
            break;
        }
        case Token::KW_while:{
            WhileStmt *w;
            w = parseWhile();
            if (w)
                body.push_back(w);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_for:{
            ForStmt *f;
            f = parseFor();
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_foreach: {
            ForeachStmt *fe;
            fe = parseForeach();
            if (fe)
                body.push_back(fe);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_try: {
            TryCatchStmt *tc;
            tc = parseTryCatch();
            if (tc)
                body.push_back(tc);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_match: {
            MatchStmt *m;
            m = parseMatch();
            if (m)
                body.push_back(m);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_print: {
            PrintStmt *p;
            p = parsePrint();
            if (p)
                body.push_back(p);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_concat: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_pow: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_abs: {
            Func *f;
            f = parseFunc(1);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_length: {
            Func *f;
            f = parseFunc();
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_min: {
            Func *f;
            f = parseFunc();
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_max: {
            Func *f;
            f = parseFunc();
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_index: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_add: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_subtract: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_multiply: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::KW_divide: {
            Func *f;
            f = parseFunc(2);
            if (f)
                body.push_back(f);
            else {
                goto _error;
            }
            break;
        }
        case Token::start_comment: {
            parseComment();
            if (!Tok.is(Token::end_comment))
                goto _error;
            break;
        }
        default:{
            llvm::errs() << "error7\n";
            error();

            goto _error;
            break;
        }
        }
        advance();

    }
    if(Tok.is(Token::r_brace)){
        return body;
    }

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return body;

}

AST* Parser::parseStmt(){
    AST *S = nullptr;

    switch (Tok.getKind())
    {
        
    case Token::ident:{
        Token prev_token = Tok;
        const char* prev_buffer = Lex.getBuffer();
        UnaryOp *u;
        u = parseUnary();
        if (Tok.is(Token::semicolon))
        {
            if (u)
            {
                S = u;
                break;
            }
            else{

                goto _error;
            }
                
        }
        else
        {
            if (u)
            {

                goto _error;
            }
            else{
                Tok = prev_token;
                Lex.setBufferPtr(prev_buffer);
            }
                
        }

        
        Assignment *a_int;
        Assignment *a_bool;
        prev_token = Tok;
        prev_buffer = Lex.getBuffer();

        a_bool = parseBoolAssign();

        if (a_bool){
            S = a_bool;
            break;
        }
        Tok = prev_token;
        Lex.setBufferPtr(prev_buffer);

        a_int = parseIntAssign();
        if (a_int)
            S = a_int;
        else
            goto _error;
        if (!Tok.is(Token::semicolon))
        {
            goto _error;
        }

        break;
    }
    case Token::KW_if: {
        IfStmt *i;
        i = parseIf();
        if (i)
            S = i;
        else
            goto _error;
        
        break;
    }
    case Token::KW_while:{
        WhileStmt *w;
        w = parseWhile();
        if (w)
            S = w;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_for:{
        ForStmt *f;
        f = parseFor();
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_foreach: {
        ForeachStmt *fe;
        fe = parseForeach();
        if (fe)
            S = fe;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_try: {
        TryCatchStmt *tc;
        tc = parseTryCatch();
        if (tc)
            S = tc;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_match: {
        MatchStmt *m;
        m = parseMatch();
        if (m)
            S = m;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_print: {
        PrintStmt *p;
        p = parsePrint();
        if (p)
            S = p;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_concat: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_pow: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_abs: {
        Func *f;
        f = parseFunc(1);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_length: {
        Func *f;
        f = parseFunc();
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_min: {
        Func *f;
        f = parseFunc();
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_max: {
        Func *f;
        f = parseFunc();
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_index: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_add: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_subtract: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_multiply: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::KW_divide: {
        Func *f;
        f = parseFunc(2);
        if (f)
            S = f;
        else {
            goto _error;
        }
        break;
    }
    case Token::start_comment: {
        parseComment();
        if (!Tok.is(Token::end_comment))
            goto _error;
        break;
    }
    default:{
        llvm::errs() << "error7\n";
        error();

        goto _error;
        break;
    }
    }

    advance();

    return S;

_error:
    while (Tok.getKind() != Token::eoi)
        advance();
    return nullptr;
}
