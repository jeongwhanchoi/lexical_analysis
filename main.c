#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tokens.h"

struct tokenType scanner();
void lexicalError(int n);
int superLetter(char ch);
int superLetterOrDigit(char ch);
int getIntNum(char firstCharacter);
int hexValue(char ch);

char id[ID_LENGTH];

int main(int argc, char** argv){
    struct tokenType token;


    do{
        token = scanner();

        switch (token.number){
            case tident:
                printf(" --> token number: %d(identifier), identifier name: %s\n", token.number, token.value.id);
                break;
            case tnumber:
                printf(" --> token number: %d(integer value),value: %d\n", token.number, token.value.num);
                break;
            default:
                printf(" --> token number: %d\n", token.number);
        }
        printf("\n");
    } while (token.number != teof);

    return 0;
}

struct tokenType scanner(void){
    struct tokenType token;
    int i, index;
    char ch, id[ID_LENGTH];

    token.number = tnull;

    do{
        while(isspace(ch = getchar())){
        }
        printf("%c", ch);

        if(superLetter(ch)){
            i = 0;
            do {
                if(i < ID_LENGTH) id[i++] = ch;
                ch = getchar();
                printf("%c", ch);
            } while(superLetterOrDigit(ch));

            if(i >= ID_LENGTH) lexicalError(1);

            id[i] = '\0';
            ungetc(ch, stdin);

            for(index = 0 ; index < NO_KEYWORDS ; index++){
                if(!strcmp(id, keyword[index])) break;
            }

            if(index < NO_KEYWORDS){
                token.number = tnum[index];
                token.value.num = 0;
            }
            else{
                token.number = tident;
                strcpy(token.value.id, id);
            }
        }
        else if(isdigit(ch)){
            token.number = tnumber;
            token.value.num = getIntNum(ch);
        }
        else{
            switch(ch){
                case '/' :
                    ch = getchar();
                    if(ch == '*'){
                        do{
                            while(ch != '*'){
                                ch = getchar();
                            }
                            ch = getchar();
                        } while(ch != '/');
                    }
                    else if(ch == '/'){
                        while(getchar() != '\n');
                    }
                    else if(ch == '='){
                        token.number = tdivAssign;
                    }
                    else{
                        token.number = tdiv;
                        ungetc(ch, stdin);
                    }
                    break;

                case '!' :
                    ch = getchar();
                    if(ch == '='){
                        token.number = tnotequ;
                    }
                    else{
                        token.number = tnot;
                        ungetc(ch, stdin);
                    }
                    break;

                case '%' :
                    ch = getchar();
                    if(ch == '='){
                        token.number = tmodAssign;
                    }
                    else{
                        token.number = tmod;
                        ungetc(ch, stdin);
                    }
                    break;

                case '&' :
                    ch = getchar();
                    if(ch == '&'){
                        token.number = tand;
                    }
                    else{
                        lexicalError(2);
                        ungetc(ch, stdin);
                    }
                    break;

                case '*' :
                    ch = getchar();
                    if(ch == '='){
                        token.number = tmulAssign;
                    }
                    else{
                        token.number = tmul;
                        ungetc(ch, stdin);
                    }
                    break;

                case '+' :
                    ch = getchar();
                    if(ch == '+'){
                        token.number = tinc;
                    }
                    else if(ch == '='){
                        token.number = taddAssign;
                    }
                    else{
                        token.number = tplus;
                        ungetc(ch, stdin);
                    }
                    break;

                case '-' :
                    ch = getchar();
                    if(ch == '-'){
                        token.number = tdec;
                    }
                    else if(ch == '='){
                        token.number = tsubAssign;
                    }
                    else{
                        token.number = tminus;
                        ungetc(ch, stdin);
                    }
                    break;

                case '<' :
                    ch = getchar();
                    if(ch == '='){
                        token.number = tlesse;
                    }
                    else{
                        token.number = tless;
                        ungetc(ch, stdin);
                    }
                    break;

                case '=' :
                    ch = getchar();
                    if(ch == '='){
                        token.number = tequal;
                    }
                    else{
                        token.number = tassign;
                        ungetc(ch, stdin);
                    }
                    break;

                case '>' :
                    ch = getchar();
                    if(ch == '='){
                        token.number = tgreate;
                    }
                    else{
                        token.number = tgreat;
                        ungetc(ch, stdin);
                    }
                    break;

                case '|' :
                    ch = getchar();
                    if(ch == '|'){
                        token.number = tor;
                    }
                    else{
                        lexicalError(3);
                        ungetc(ch, stdin);
                    }
                    break;

                case '(' : token.number = tlparen;		break;
                case ')' : token.number = trparen;		break;
                case ',' : token.number = tcomma;		break;
                case ';' : token.number = tsemicolon;	break;
                case '[' : token.number = tlbracket;	break;
                case ']' : token.number = trbracket;	break;
                case '{' : token.number = tlbrace;		break;
                case '}' : token.number = trbrace;		break;
                case EOF : token.number = teof;			break;

                default : {
                    printf("Current character : %c", ch);
                    lexicalError(4);
                    break;
                }
            }
        }
    } while(token.number == tnull);

    return token;
}

void lexicalError(int n){
    printf(" *** Lexical Error : ");
    switch (n) {
        case 1:
            printf("an identifier length must be less than 12.\n");
            break;
        case 2:
            printf("next character must be &.\n");
            break;
        case 3:
            printf("next character must be |.\n");
            break;
        case 4:
            printf("invalid character!!!.\n");
            break;
    }
}


// checks if ch is alphabet or underscore(_)
int superLetter(char ch){
    if (isalpha(ch) || ch == '_')
        return 1;
    else
        return 0;
}


// checks if ch is alphanumeric or underscore
int superLetterOrDigit(char ch){
    // isalnum(int c) checks if the passed character is alphanumeric
    if (isalnum(ch) || ch == '_')
        return 1;
    else
        return 0;
}

int getIntNum(char firstCharacter){
    int num = 0;
    int value;
    char ch;

    if(firstCharacter != '0'){
        ch = firstCharacter;
        do {
            num = 10 * num + (int)(ch - '0');
            ch = getchar();
        } while(isdigit(ch));
    }
    else{
        ch = getchar();
        if((ch >= '0') && (ch <= '7')){
            do {
                num = 8 * num + (int)(ch - '0');
                ch = getchar();
            } while((ch >= '0') && (ch <= '7'));
        }
        else if((ch == 'x') || (ch == 'X')){
            while((value = hexValue(ch = getchar())) != -1){
                num = 16 * num + value;
            }
        }
        else{
            num = 0;
        }
    }
    ungetc(ch, stdin);
    return num;
}

int hexValue(char ch){
    switch(ch){
        case '0' : case '1' : case '2' : case '3' : case '4' :
        case '5' : case '6' : case '7' : case '8' : case '9' :
            return (ch - '0');
        case 'A' : case 'B' : case 'C' : case 'D' : case 'E' : case 'F' :
            return (ch - 'A' + 10);
        case 'a' : case 'b' : case 'c' : case 'd' : case 'e' : case 'f' :
            return (ch - 'a' + 10);
        default : return -1;
    }
}