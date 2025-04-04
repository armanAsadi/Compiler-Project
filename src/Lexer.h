#ifndef LEXER_H // conditional compilations(checks whether a macro is not defined)
#define LEXER_H

#include "llvm/ADT/StringRef.h"        // encapsulates a pointer to a C string and its length
#include "llvm/Support/MemoryBuffer.h" // read-only access to a block of memory, filled with the content of a file

class Lexer;

class Token
{
    friend class Lexer; // Lexer can access private and protected members of Token

public:
    enum TokenKind : unsigned short
    {
        eoi,            // end of input
        unknown,        // in case of error at the lexical level
        ident,          // identifier
        number,         // integer literal
        floating,       // float literal
        character,      // char literal
        string,         // string literal
        assign,         // =
        minus_assign,   // -=
        plus_assign,    // +=
        star_assign,    // *=
        slash_assign,   // /=
        mod_assign,     // %=
        eq,             // ==
        neq,            // !=
        gt,             // >
        lt,             // <
        gte,            // >=
        lte,            // <=
        plus_plus,      // ++
        minus_minus,    // --
        arrow,          // ->
        underscore,     // _
        start_comment,  // /*
        end_comment,    // */
        comma,          // ,
        semicolon,      // ;
        plus,           // +
        minus,          // -
        star,           // *
        slash,          // /
        mod,            // %
        exp,            // ^
        l_paren,        // (
        minus_paren,    // -(
        r_paren,        // )
        l_brace,        // {
        r_brace,        // }
        l_bracket,      // [
        r_bracket,      // ]
        KW_int,         // int
        KW_float,       // float
        KW_bool,        // bool
        KW_char,        // char
        KW_string,      // string
        KW_array,       // array
        KW_true,        // true
        KW_false,       // false
        KW_if,          // if
        KW_else,        // else
        KW_match,       // match
        KW_while,       // while
        KW_for,         // for
        KW_foreach,     // foreach
        KW_and,         // and
        KW_or,          // or
        KW_xor,         // xor
        KW_in,          // in
        KW_print,       // print
        KW_concat,      // concat
        KW_pow,         // pow
        KW_abs,         // abs
        KW_length,      // length
        KW_min,         // min
        KW_max,         // max
        KW_index,       // index
        KW_add,         // add
        KW_subtract,    // subtract
        KW_multiply,    // multiply
        KW_divide,      // divide
        KW_try,         // try
        KW_catch,       // catch
        KW_error        // Error
    };

private:
    TokenKind Kind;
    llvm::StringRef Text; // points to the start of the text of the token

public:
    TokenKind getKind() const { return Kind; }
    llvm::StringRef getText() const { return Text; }

    // to test if the token is of a certain kind
    bool is(TokenKind K) const { return Kind == K; }
    bool isOneOf(TokenKind K1, TokenKind K2) const
    {
        return is(K1) || is(K2);
    }
    template <typename... Ts>
    bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks)
        const { return is(K1) || isOneOf(K2, Ks...); }

};

class Lexer
{
    const char *BufferStart; // pointer to the beginning of the input
    const char *BufferPtr;   // pointer to the next unprocessed character

public:
    Lexer(const llvm::StringRef &Buffer)
    {
        BufferStart = Buffer.begin();
        BufferPtr = BufferStart;
    }

    void next(Token &token); // return the next token
    void setBufferPtr(const char* buffer);
    const char* getBuffer(){return BufferPtr;};

private:
    void formToken(Token &Result, const char *TokEnd, Token::TokenKind Kind);
};
#endif