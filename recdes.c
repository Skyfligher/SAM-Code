// filename recdes.c
/*
   Description: This program is a recursive descent compiler to
		parse and encode expressions from the following
		context-free grammar:
		PROGRAM  --> begin STMT_LIST end
		STMT_LIST--> STMT_LIST ; STMT | STMT;
           	STMT --> id := EXPR | e
            	EXPR --> EXPR + TERM | EXPR - TERM
		TERM --> TERM * FCTR | TERM (/ or div) FCTR | TERM mod FCTR | FCTR
		EXPO --> FCTR ^ EXPO | FCTR
		FCTR --> id | num | ( EXPR )

  The expressions will be encoded for a hypothetical stack machine with the
  following instructions:

		PUSH  A    -- push the value in A on top of the stack
		ADD       -- add the two values on top of the stack, push result
		SUB       -- subtract     "
		MPY       -- multiply     "
		DIV       -- divide       "
		RVALUE L  -- push the contents of variable L
	    LVALUE L  -- push the address of variable L
	**  POP       -- throw away the top valueon the stack
	    STO       -- the R value on the top of the stack is placed in the L value below it and both are popped
	**  COPY      -- push a copy of the top value on the stack
	    MOD       -- pop the top two values off the stack, compute the modulus and push the result
	    POW       -- pop the top two values and compute the exponential operation, push the result
	    HALT      -- stop execution
*/

#include <stdio.h>  // standard i/o prototypes
#include <string.h> // string function prototypes
#include <ctype.h>  // char function prototypes

// constants
#define END 			'$'
#define MOD 			'%'
#define EQ				'='
#define SEMICOL			';'
#define COL 			':'
#define POWSYM			'^'
#define CARRET          13
#define TAB             9
#define NEWLINE			10
#define PLUSSYM         '+'
#define MINUSSYM        '-'
#define MULTSYM         '*'
#define DIVSYM          '/'
#define OPENPAREN       '('
#define CLOSEPAREN      ')'
#define BLANK           ' '
#define NULLSTRING		""

typedef int boolean;

// function prototypes
void open_data_file(int, char *[]);
void parse(void);
void prgm(void);
void begin(void);
void stmt_list(void);
void stmt(void);
void expr(void);
void term(void);
void expo(void);
void factor(void);
void error(char *);
void scan(void);

//necessary global variables
FILE *infile;
char lookahead[7];

void main(int argc, char *argv[])
{
  open_data_file(argc, argv);
  parse();
  puts("End of Compilation...");
}

void open_data_file(int argc, char *argv[])
{
  /* This function opens the data file containign the expression for this
	execution of the compiler. */
  // local variables
  infile = NULL;
  char *temp;
  if (argc > 1) {
    if ( (infile=fopen(argv[1],"r")) == NULL ) {
	 fprintf(stderr,"Error opening input file:  %s",argv[1]);
    }
  }
  else
    infile = stdin;
} // end open_data_file

void error(char *errstr)
{
  fprintf(stderr,"%s\n", errstr);
} // end error

void scan(void)
{
/* This procedure is a simple lexical analyzer; it produces the next token from
   the input string each time it is called */
   int ch; int i;


   strcpy(lookahead,NULLSTRING);
   while (BLANK == (ch = getc(infile)) || ch == CARRET || ch == NEWLINE || ch == TAB) // Ignore any blanks
	{/* do nothing */}
   switch (ch) {
   	case END:
   	case MOD:
   	case SEMICOL:
   	case EQ:
   	case POWSYM:
	case PLUSSYM:
	case MINUSSYM:
	case MULTSYM:
	case DIVSYM:
	case OPENPAREN:
	case CLOSEPAREN:
	{ /* note: all operators are 1 character */
	   lookahead[0] = ch;
	   lookahead[1] = '\0';
	   break;
	}
	case COL:
	{
		ch = getc(infile);
	    lookahead[0] = ch;
	    lookahead[1] = EQ;
	    break;
	}
	case 'b':
	{
		lookahead[i++] = ch;
		ch = getc(infile);
		if(ch == 'e'){
		    lookahead[i++] = ch;
		    ch = getc(infile);
		    if(ch == 'g'){
		    	lookahead[i++] = ch;
		    	ch = getc(infile);
		    	if(ch == 'i'){
		    		lookahead[i++] = ch;
		    		ch = getc(infile);
		    		if(ch == 'n'){
		    			strcpy(lookahead,"begin");
		        		break;
		    		}
		    		else{
		    			while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    			{
		   				lookahead[i++] = ch;
		   				ch = getc(infile);
	   					}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    		}
		    	}
		    	else{
		    		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    		{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   				lookahead[i] = '\0';
	   				ungetc(ch,infile);
		            break;
		    	}
		    }
		    else{
		    	while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    		{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    }
		}
		else{
	   		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   			{
		   		lookahead[i++] = ch;
		   		ch = getc(infile);
	   			}
	   			lookahead[i] = '\0';
	   			ungetc(ch,infile);
		        break;
		}
	    break;
	}
	case 'd':
	{
		lookahead[i++] = ch;
		ch = getc(infile);
		if(ch == 'i'){
		    lookahead[i++] = ch;
		    ch = getc(infile);
		    if(ch == 'v'){
		        lookahead[i] = '\0';
		        lookahead[i--] = '\0';
		        ungetc(DIVSYM,infile);
		        scan();
		    }
		    else{
		    	while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    		{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    }
		}
		else{
	   		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   			{
		   		lookahead[i++] = ch;
		   		ch = getc(infile);
	   			}
	   			lookahead[i] = '\0';
	   			ungetc(ch,infile);
		        break;
		}
	    break;
	}
	case 'e':
	{
		lookahead[i++] = ch;
		ch = getc(infile);
		if(ch == 'n'){
		    lookahead[i++] = ch;
		    ch = getc(infile);
		    if(ch == 'd'){
		    	ungetc(END,infile);
				scan();

		    }
		    else{
		    	while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    		{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    }
		}
		else{
	   		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   			{
		   		lookahead[i++] = ch;
		   		ch = getc(infile);
	   			}
	   			lookahead[i] = '\0';
	   			ungetc(ch,infile);
		        break;
		}
	    break;
	}
	case 'm':
	{
		lookahead[i++] = ch;
		ch = getc(infile);
		if(ch == 'o'){
		    lookahead[i++] = ch;
		    ch = getc(infile);
		    if(ch == 'd'){
		        lookahead[i] = '\0';
		        lookahead[i--] = '\0';
		        ungetc(MOD,infile);
		        scan();
		    }
		    else{
		    	while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    		{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    }
		}
		else{
	   		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   			{
		   		lookahead[i++] = ch;
		   		ch = getc(infile);
	   			}
	   			lookahead[i] = '\0';
	   			ungetc(ch,infile);
		        break;
		}
	    break;
	}
	default:
	   { /* identifiers are any sequence of non-delimiters */
	   i = 0;
	   do {
		   lookahead[i++] = ch;
		   ch = getc(infile);
	   } while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) && (ch != 'd') && (ch != 'm') || ((ch >= '0') && (ch <= '9')));
	   	if(ch == 'd'){
	   		lookahead[i++] = ch;
			ch = getc(infile);
			if(ch == 'i'){
		    	lookahead[i++] = ch;
		    	ch = getc(infile);
		    	if(ch == 'v'){
		        	lookahead[i] = '\0';
		        	lookahead[i--] = '\0';
		        	lookahead[i--] = '\0';
		        	lookahead[i--] = '\0';
		        	break;
		    	}
		    	else{
		    		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    			{
		   				lookahead[i++] = ch;
		   				ch = getc(infile);
	   					}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    	}
			}
			else{
	   			while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   				{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   				lookahead[i] = '\0';
	   				ungetc(ch,infile);
		        	break;
	   		}
	   	}
	   	if(ch == 'e'){
	   		lookahead[i++] = ch;
			ch = getc(infile);
			if(ch == 'n'){
		    	lookahead[i++] = ch;
		    	ch = getc(infile);
		    	if(ch == 'd'){
		    		strcpy(lookahead,NULLSTRING);
		    		strcpy(lookahead,"end");
		        	break;
		    	}
		    	else{
		    		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    			{
		   				lookahead[i++] = ch;
		   				ch = getc(infile);
	   					}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    	}
			}
			else{
	   			while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   				{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   				lookahead[i] = '\0';
	   				ungetc(ch,infile);
		        	break;
	   		}
	   	}
	   	if(ch == 'm'){
	   		lookahead[i++] = ch;
			ch = getc(infile);
			if(ch == 'o'){
		    	lookahead[i++] = ch;
		    	ch = getc(infile);
		    	if(ch == 'd'){
		        	lookahead[i] = '\0';
		        	lookahead[i--] = '\0';
		        	lookahead[i--] = '\0';
		        	lookahead[i--] = '\0';
		        	ungetc(MOD,infile);
		        	break;
		    	}
		    	else{
		    		while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		    			{
		   				lookahead[i++] = ch;
		   				ch = getc(infile);
	   					}
	   					lookahead[i] = '\0';
	   					ungetc(ch,infile);
		                break;
		    	}
			}
			else{
	   			while (((toupper(ch) >= 'A') && (toupper(ch) <= 'Z')) || ((ch >= '0') && (ch <= '9')))
	   				{
		   			lookahead[i++] = ch;
		   			ch = getc(infile);
	   				}
	   				lookahead[i] = '\0';
	   				ungetc(ch,infile);
		        	break;
	   		}
	   	}

	   lookahead[i] = '\0';
	   ungetc(ch,infile);
	}
    } // end switch
} /*end scan()*/

void match(char *token)
  /* "Matchmaker, Matchmaker, make me a match ... "  -- Fiddler on the Roof*/
{
    if (strcmp(token,lookahead) == 0)  /* then a match has been made*/
	 scan();          /* get new lookahead */
    else
	 error(strcat(token," expected"));     /* report "TOKEN expected" */
}  /* end match() */



boolean identifier(char *token)
{
  /* checks for a valid identifier -- a sequence of nondelimiters starting
    with a letter  */
       for(int t = 0; t < strlen(token); t++){
    	if((token[t] >= '0') && (token[t] <= '9') || (token[t] >= 'a') && (token[t] <= 'z') || (token[t] >= 'A') && (token[t] <= 'Z')){

    	}
    	else{
    		return 0;
    	}
    }
    return 1;
} /* end identifier() */

boolean num(char *token)
{
  /* checks for a valid num with no letters  */
    for(int t = 0; t < strlen(token); t++){
    	if((token[t] >= '0') && (token[t] <= '9')){

    	}
    	else{
    		return 0;
    	}
    }
    return 1;
} /* end num() */


void emit(char * opcode)
{
   printf("%s\n",opcode);
} /* end emit() */


void fctr()
 /* This procedure handles the assembly of factors */
{
   char s[20] = NULLSTRING;
   char temp[20] = NULLSTRING;
			/* check for a num */
    if( num(lookahead)) {
		strcat(s,"PUSH ");
		emit(strcat(s,lookahead));
		match(lookahead);
    }
    else  	/* check for an identifier */
	if (identifier(lookahead)) {
		strcat(temp,lookahead);
    	match(lookahead);
    	if(lookahead[1] == EQ){
    		strcat(s,"LVALUE ");
    		emit(strcat(s,temp));
    	}
		else{
		strcat(s,"RVALUE ");
		emit(strcat(s,temp));
		}
   	}
   	else
   	if(lookahead[0] == NEWLINE){
   		getc(stdin);
   	}
   	else
   	if(lookahead[0] == SEMICOL){
   		emit("\n");
   	}
   else  /* check for a parenthesized subexpression */
    if( lookahead[0] == OPENPAREN ) {
	 match("(");
	 expr();
	 match(")");
    }
    else
    if(lookahead[0] == END){

    }
    else
	 error("malformed factor error" );


} /* end fctr() */


void expo()
/* This procedure handles the assembly of exponents */
{
    char temp[20] = NULLSTRING;

    fctr(); /* an exponent must begin with a factor */
    /* process the exponent operator */
    while(lookahead[0] == POWSYM){
        strcpy(temp,lookahead);
        match(lookahead);
        expo();
        emit("POW");
    } // end while
} // end expo()


void term()
 /*This procedure handles the assembly of terms */
{
  char temp[20] = NULLSTRING;

   expo(); /* A term must begin with a factor */
   /* Now, process any multiplying operator */
   while ( (lookahead[0] == MULTSYM) || (lookahead[0] == DIVSYM) || (lookahead[0] == MOD)) {
	strcpy(temp,lookahead);
	match(lookahead);
	term();
		if (strcmp(temp,"*") == 0){
	 		emit("MPY");
		}
		else
		if(strcmp(temp,"/") == 0){
	 		emit("DIV");
		}
		else{
			emit("MOD");
		}
   } // end while

}//  end term()


void expr()
{
 /* This procedure handles the assembly of expressions */

  char temp[20] = NULLSTRING;
   term();  /* An expression must begin with a term */
   /* Now, process any adding operators */
   while ((lookahead[0] == PLUSSYM) || (lookahead[0] == MINUSSYM)) {
	strcpy(temp,lookahead);
	match(lookahead);
	expr();
	if(strcmp(temp,"+")==0)
	 emit("ADD");
	else
	 emit("SUB");
    } // end while
} // end expr()


void stmt()
/* This procedure handles the assembly of a statement */
{
    expr(); /* A statement must begin with a factor */
    /* searching for following expression */
   while ((lookahead[0] == COL) || (lookahead[0] == '=')) {
        match(lookahead);
        stmt();
        emit("STO");
    } // end while
} // end stmt()


void stmt_list()
/* This procedure handles the assembly of a statement list */
{

    stmt(); /* A statement_list must begin with a statement */
   while (lookahead[0] == SEMICOL) {
   		//printf("\n");
        match(lookahead);
        stmt_list();
    } // end while
} // end stmt_list()

void begin(){
	if(strcmp(lookahead,"begin") == 0){
		emit("//BEGIN");
		scan();
	}
}
void prgm()
/* This procedure handles the program */
{

	begin();/* A program must begin with a begin */
	while(lookahead[0] != END){
		stmt_list();
		//emit(lookahead);
    	emit("HALT");
    }

} // end prgm()

void parse(void)
{
	scan();
	prgm();
} // end parse()
