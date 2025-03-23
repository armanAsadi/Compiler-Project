#include "Lexer.h"
#include "llvm/Support/raw_ostream.h"

// classifying characters
namespace charinfo
{
    // ignore whitespaces
    LLVM_READNONE inline bool isWhitespace(char c)
    {
        return c == ' ' || c == '\t' || c == '\f' || c == '\v' ||
               c == '\r' || c == '\n';
    }

    LLVM_READNONE inline bool isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    LLVM_READNONE inline bool isLetter(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    LLVM_READNONE inline bool isSpecialCharacter(char c)
    {
        return c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '!' || c == '>' || c == '<' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' || c == '%' || c == '^' || c == '_' || c == '\'' || c == '\"';
    }
}

void Lexer::next(Token &token) {
    while (*BufferPtr && charinfo::isWhitespace(*BufferPtr)) {
        ++BufferPtr;
    }
    // make sure we didn't reach the end of input
    if (!*BufferPtr) {
        token.Kind = Token::eoi;
        return;
    }
    // collect characters and check for keywords or ident
    if (charinfo::isLetter(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isLetter(*end) || charinfo::isDigit(*end) || *end == '_')
            ++end;
        llvm::StringRef Name(BufferPtr, end - BufferPtr);
        Token::TokenKind kind;
        if (Name == "int")
            kind = Token::KW_int;
        else if (Name == "float")
            kind = Token::KW_float;
        else if (Name == "bool")
            kind = Token::KW_bool;
        else if(Name == "char")
            kind = Token::KW_char;
        else if(Name == "string")
            kind = Token::KW_string;
        else if(Name == "array")
            kind = Token::KW_array;
        else if (Name == "print")
            kind = Token::KW_print;
        else if (Name == "concat")
            kind = Token::KW_concat;
        else if (Name == "pow")
            kind = Token::KW_pow;
        else if (Name == "abs")
            kind = Token::KW_abs;
        else if (Name == "length")
            kind = Token::KW_length;
        else if (Name == "min")
            kind = Token::KW_min;
        else if (Name == "max")
            kind = Token::KW_max;
        else if (Name == "index")
            kind = Token::KW_index;
        else if (Name == "add")
            kind = Token::KW_add;
        else if (Name == "subtract")
            kind = Token::KW_subtract;
        else if (Name == "multiply")
            kind = Token::KW_multiply;
        else if (Name == "divide")
            kind = Token::KW_divide;
        else if (Name == "while")
            kind = Token::KW_while;
        else if (Name == "for")
            kind = Token::KW_for;
        else if (Name == "foreach")
            kind = Token::KW_foreach;
        else if (Name == "if")
            kind = Token::KW_if;
        else if (Name == "else")
            kind = Token::KW_else;
        else if (Name == "match")
            kind = Token::KW_match;
        else if (Name == "true")
            kind = Token::KW_true;
        else if (Name == "false")
            kind = Token::KW_false;
        else if (Name == "and")
            kind = Token::KW_and;
        else if (Name == "or")
            kind = Token::KW_or;
        else if (Name == "xor")
            kind = Token::KW_xor;
        else if (Name == "in")
            kind = Token::KW_in;
        else if (Name == "try")
            kind = Token::KW_try;
        else if (Name == "catch")
            kind = Token::KW_catch;
        else if (Name == "Error")
            kind = Token::KW_error;     
        else
            kind = Token::ident;
        // generate the token
        formToken(token, end, kind);
        return;
    } else if (charinfo::isDigit(*BufferPtr)) { // check for numbers(integer or floating)
        const char *end = BufferPtr + 1;
        while (charinfo::isDigit(*end))
            ++end;

        if (*end != '.'){
            formToken(token, end, Token::number);
            return;
        }

        ++end;
        if (!charinfo::isDigit(*end)){
            formToken(token, end, Token::unknown);
            return;
        }

        while (charinfo::isDigit(*end))
            ++end;

        formToken(token, end, Token::floating);
        return;
    } else if (charinfo::isSpecialCharacter(*BufferPtr)) {
        const char *endWithOneLetter = BufferPtr + 1;
        const char *endWithTwoLetter = BufferPtr + 2;
        const char *end;
        llvm::StringRef NameWithOneLetter(BufferPtr, endWithOneLetter - BufferPtr);
        llvm::StringRef NameWithTwoLetter(BufferPtr, endWithTwoLetter - BufferPtr);
        Token::TokenKind kind;
        bool isFound = false;
        if (NameWithTwoLetter == "=="){
            kind = Token::eq;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithOneLetter == "=") {
            kind = Token::assign;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithTwoLetter == "!="){
            kind = Token::neq;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "-("){
            kind = Token::minus_paren;
            isFound = true;
            end = endWithTwoLetter;
        }else if (NameWithTwoLetter == "+="){
            kind = Token::plus_assign;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "-="){
            kind = Token::minus_assign;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "*="){
            kind = Token::star_assign;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "%="){
            kind = Token::mod_assign;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "*/"){
            kind = Token::end_comment;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "/="){
            kind = Token::slash_assign;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "/*"){
            kind = Token::start_comment;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == ">="){
            kind = Token::gte;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "<="){
            kind = Token::lte;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "++"){
            kind = Token::plus_plus;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "--"){
            kind = Token::minus_minus;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "->"){
            kind = Token::arrow;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithTwoLetter == "_"){
            kind = Token::underscore;
            isFound = true;
            end = endWithTwoLetter;
        } else if (NameWithOneLetter == "+"){
            kind = Token::plus;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "-"){
            kind = Token::minus;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "*"){
            kind = Token::star;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "/"){
            kind = Token::slash;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "+"){
            kind = Token::plus;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == ">"){
            kind = Token::gt;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "<"){
            kind = Token::lt;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "("){
            kind = Token::l_paren;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == ")"){
            kind = Token::r_paren;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "{"){
            kind = Token::l_brace;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "}"){
            kind = Token::r_brace;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "["){
            kind = Token::l_bracket;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "]"){
            kind = Token::r_bracket;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == ";"){
            kind = Token::semicolon;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == ","){
            kind = Token::comma;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "%"){
            kind = Token::mod;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "^"){
            kind = Token::exp;
            isFound = true;
            end = endWithOneLetter;
        } else if (NameWithOneLetter == "\'"){  // check for char literal
            
            end = endWithOneLetter;
            if(*end)
                ++end;

            if (*end == '\''){
                kind = Token::character;
                isFound = true;
                ++end;
            }

        } else if (NameWithOneLetter == "\""){  // check for string literal
            
            end = endWithOneLetter;
            while (*end && *end != '\"')
                ++end;

            if (*end){
                kind = Token::string;
                isFound = true;
                ++end;
            }

        }
        
        // generate the token
        if (isFound) formToken(token, end, kind);
        else formToken(token, BufferPtr + 1, Token::unknown);
        return;
    } else {
        formToken(token, BufferPtr + 1, Token::unknown); 
        return;         
    }
    return;
}

void Lexer::setBufferPtr(const char *buffer){
    BufferPtr = buffer;
}

void Lexer::formToken(Token &Tok, const char *TokEnd,
                      Token::TokenKind Kind)
{
    Tok.Kind = Kind;
    Tok.Text = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
    BufferPtr = TokEnd;
}