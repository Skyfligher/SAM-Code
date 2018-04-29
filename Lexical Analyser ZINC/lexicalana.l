/*
 * Jared Rattray Lexical Analyser
*/
%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void insert(char *token, char *lexe, int linecounter);
int test(char *lexe);
void printtable();



int line = 1;
int counter = 0;

char tokens[50][10];
char lexemes[50][10];
int lines[50];


%}
LP          "("
RP          ")"
ASGN        ":="
SC          ";"
COLON       ":"
POWER       "**"
MULT        "*"
DIV         "div"
MOD         "mod"
ADD         "+"
SUB         "-"
EQ          "="
NOTEQ       "<>"
LT          "<"
GT          ">"
GE          ">="
LE          "<="
IF          "if"
THEN        "then"
ELSE        "else"
BEGIN       "begin"
END         "end"
ENDIF       "endif"
ENDWHILE    "endwhile"
WHILE       "while"
LOOP        "loop"
PROGRAM     "program"
VAR         "var"
INT         "integer"
WRITEINT    "writeInt"
READINT     "readInt"

%option noyywrap

%%
[+|-]?[1-9][0-9]*|0  { printf("Number:: %s\n", yytext);}
[A-Z][_A-Z0-9]*      {  printf("Variable:: %s\n", yytext);
    if(test(yytext) == 0)
    {
        char lowerYYtext[strlen(yytext)];
        strcpy(lowerYYtext, yytext);
        insert(lowerYYtext, "ident",line);
    }
}

{ADD}       {insert(yytext, "Adition",line);}
{SUB}       {insert("-", "Subtraction",line);}
{POWER}     {insert("**", "Exponent",line);}
{MULT}      {insert("*", "Multiplier",line);}
{DIV}       {insert("div", "Division",line);}
{MOD}       {insert("mod", "Modulus",line);}

{LP}        {insert("(", "Left Parenthesis",line);}
{RP}        {insert(")", "Right Parenthesis",line);}
{ASGN}      {insert(":=", "Assignment",line);}
{SC}        {insert(";", "Semicolon",line);}
{COLON}     {insert(":", "Colon",line);}
{EQ}        {insert("=", "Equal",line);}
{NOTEQ}     {insert("<>", "Not Equal",line);}
{LT}        {insert("<", "Less Than",line);}
{GT}        {insert(">", "Greater Than",line);}
{GE}        {insert(">=", "Greater Than or Equal",line);}
{LE}        {insert("<=", "Less Than or Equal",line);}

{VAR}       {insert("var", "Variable",line);}
{INT}       {insert("integer", "Integer",line);}
{WRITEINT}  {insert("writeInt", "Write Integer",line);}
{READINT}   {insert("readInt", "Read Integer",line);}

{IF}        {insert("if", "If",line);}
{THEN}      {insert("then", "Then",line);}
{ELSE}      {insert("else", "Else",line);}
{BEGIN}     {insert("begin", "Begin",line);}
{END}       {insert("end", "End",line);}
{ENDIF}     {insert("endif", "EndIf",line);}
{ENDWHILE}  {insert("endwhile", "EndWhile",line);}
{WHILE}     {insert("while", "While",line);}
{LOOP}      {insert("loop", "Loop",line);}
{PROGRAM}   {insert("program", "Program",line);}

"--".*      {printf("Comment:: %s\n", yytext);}
.    	    {}                                             ///Ignore
\n          {line++;}                                      ///Counting lines
%%


int main(int argc, char *argv[])
{
    char file[150];
    if(yyin = fopen(argv[1], "r"))
    {
        printf("Error opening the file. \n");
    }
    else
    {
        printf("Give me the file!\n");
        scanf("%s", file);
        yyin = fopen(file,"r");
    }
    yylex();
    printf("Number of lines:: %d\n", line);
    printtable();
}


void insert(char *token, char *lexe, int line)
{	
    strcpy(tokens[counter], token);
    strcpy(lexemes[counter], lexe);
    lines[counter] = line;
    counter = counter + 1;
}


int test(char *lexe)
{
    int temp;

    for(temp = 0; temp < 50; temp ++)
    {
        if(tokens[temp][0] == lexe[0])
        {
            return 1;
        }
    }
    return 0;
}

void printtable()
{
    int temp1;
    int temp2;
    char point= '\0';

    for(temp1 = 0; temp1 < 50; temp1 = temp1 + 1)
    {
        if( temp1 < counter )
        {
            printf("<\"");
        }
        for(temp2 = 0; temp2 < 10; temp2 = temp2 + 1)
        {
            if(tokens[temp1][temp2] == point)
            {
                continue;
            }
            else
            {
                printf("%c", tokens[temp1][temp2]);
            }
        }
        if( temp1 < counter )
        {
            printf("\",");
            for(temp2 = 0; temp2 < 10; temp2 = temp2 + 1)
            {
                if(lexemes[temp1][temp2] == point)
                {
                    continue;
                }
                else
                {
                    printf("%c", lexemes[temp1][temp2]);
                }
            }
            printf(">");
            printf("\n");
        }
    }
}
