//
// Created by Jeongwhan Choi on 2019/11/14.
//

#ifndef LEXICAL_ANALYSIS_TOKENS_H
#define LEXICAL_ANALYSIS_TOKENS_H


#define NO_KEYWORDS	7
#define ID_LENGTH	12

// tsymbol type, represents the token number;
enum tsymbol {
    // special symbols
    tnull = -1,
    tnot,			// 0
    tnotequ,
    tmod,
    tmodAssign,
    tident,
    tnumber,
    tand,
    tlparen,
    trparen,
    tmul,
    tmulAssign,		// 10
    tplus,
    tinc,
    taddAssign,
    tcomma,
    tminus,
    tdec,
    tsubAssign,
    tdiv,
    tdivAssign,
    tsemicolon,		// 20
    tless,
    tlesse,
    tassign,
    tequal,
    tgreat,
    tgreate,
    tlbracket,
    trbracket,
    teof,

    // keword symbols
    tconst,			// 30
    telse,
    tif,
    tint,
    treturn,
    tvoid,
    twhile,
    tlbrace,
    tor,
    trbrace
};


// tokenType struct
struct tokenType {
    int number;			// token number;
    union {
        char id[ID_LENGTH];
        int num;
    } value;
};


// keyword table
char *keyword[NO_KEYWORDS] = {
        "const",
        "else",
        "if",
        "int",
        "return",
        "void",
        "while"
};

// keoword token number
enum tsymbol tnum[NO_KEYWORDS] = {
        tconst,
        telse,
        tif,
        tint,
        treturn,
        tvoid,
        twhile
};

#endif //LEXICAL_ANALYSIS_TOKENS_H
