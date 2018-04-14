import java.util.*;
import java.io.*;

public class SimpleAsm {
    public static final int HALT = 0;
    public static final int PUSH = 1;
    public static final int RVALUE = 2;
    public static final int LVALUE = 3;
    public static final int POP = 4;
    public static final int ASGN = 5;
    public static final int COPY = 6;
    public static final int ADD = 7;
    public static final int SUB = 8;
    public static final int MPY = 9;
    public static final int DIV = 10;
    public static final int MOD = 11;
    public static final int NEG = 12;
    public static final int NOT = 13;
    public static final int OR = 14;
    public static final int AND = 15;
    public static final int EQ = 16;
    public static final int NE = 17;
    public static final int GT = 18;
    public static final int GE = 19;
    public static final int LT = 20;
    public static final int LE = 21;
    public static final int LABEL = 22;
    public static final int GOTO = 23;
    public static final int GOFALSE = 24;
    public static final int GOTRUE = 25;
    public static final int PRINT = 26;
    public static final int READ = 27;
    public static final int GOSUB = 28;
    public static final int RET = 29;


    public static String[] opcodes = {"HALT", "PUSH", "RVALUE", "LVALUE", "POP", "STO", "COPY", "ADD", "SUB", "MPY",
            "DIV", "MOD", "NEG", "NOT", "OR", "AND", "EQ", "NE", "GT", "GE", "LT", "LE", "LABEL", "GOTO", "GOFALSE",
            "GOTRUE", "PRINT", "READ", "GOSUB", "RET"};

    public static void main(String[] args) throws IOException {
        // get filename
        String filename;
        SymbolTable symTab = new SymbolTable();

        if (args.length != 0) {
            filename = args[0];
        } else {
            filename = "simple.asm";
        }

        // Open file for input
        Scanner infile = new Scanner(new File(filename));

        // pass 1 -- build symbol table
        pass1(infile, symTab);
        infile.close();

        // pass 2 -- assemble
        // reopen source file
        infile = new Scanner(new File(filename));

        // pass 2 -- output binary code
        pass2(infile, symTab);
        infile.close();

        // print symbol table
        dumpSymbolTable(symTab);
        System.out.println("Done");
    }

    public static int lookUpOpcode(String s) {
        for (int i = 0; i < opcodes.length; i++) {
            if (s.equalsIgnoreCase(opcodes[i])) {
                return i;
            }
        }
        System.err.println("\nInvalid opcode:" + s);
        return -1;
    }

    public static void pass1(Scanner infile, SymbolTable tab) {
        // initialize location counter, etc.
        int locationCounter = 0;
        String line;
        Scanner input;
        String lexeme;

        // find start of data section
        do {
            line = infile.nextLine();
            System.out.println(line);
            input = new Scanner(line);
        } while (!input.next().equalsIgnoreCase("Section"));
        if (!input.next().equalsIgnoreCase(".data")) {
            System.err.println("Error:  Missing 'Section .data' directive");
            System.exit(1);
        } else {
            System.out.println("Parsing data section, pass 1");
        }

        // build symbol table from variable declarations
        line = infile.nextLine();
        input = new Scanner(line);

        // data section ends where code section begins
        while (!(lexeme = input.next()).equalsIgnoreCase("Section")) {
            // look for labels (they end with a colon)
            int pos = lexeme.indexOf(':');
            if (pos > 0) {
                lexeme = lexeme.substring(0, pos);
            } else {
                System.err.println("error parsing " + line);
            }
            // insert the lexeme, the type, and its address into the symbol table
            tab.insert(lexeme, "Int", locationCounter);
            locationCounter++;
            line = infile.nextLine();
            input = new Scanner(line);
        }

        // Now, parse the code section, looking for the label directive
        System.out.println("Parsing code section, pass 1");
        locationCounter = 0;
        while (infile.hasNext()) {
            line = infile.nextLine();
            input = new Scanner(line);
            lexeme = input.next();
            // when a label is found, place it and its code offset in the symbol table
            if (lexeme.equalsIgnoreCase("label")) {
                lexeme = input.next();
                tab.insert(lexeme, "Code", locationCounter);
            }
            locationCounter++;
        }
    }

    // generate the code
    public static void pass2(Scanner infile, SymbolTable tab) throws IOException {
        // initialize location counter, etc.
        int locationCounter = 0;
        String line;
        Scanner input;
        String lexeme;
        int symTabPtr;
        SymbolTableEntry entry;
        final int NULL = -1;
        // find start of next section
        do {
            line = infile.nextLine();
            input = new Scanner(line);

        } while (!input.next().equalsIgnoreCase("Section"));
        if (!input.next().equalsIgnoreCase(".data")) {
            System.err.println("Error:  Missing 'Section .data' directive");
            System.exit(1);
        } else {
            System.out.println("Parsing data section, pass 2");
        }
        line = infile.nextLine();
        input = new Scanner(line);

        while (!(lexeme = input.next()).equalsIgnoreCase("Section")) {
            // data section has been processed in previous pass, so skip this
            line = infile.nextLine();
            input = new Scanner(line);
        }

        // Now, let's generate some code
        System.out.println("Parsing code section, pass 2");
        locationCounter = 0;
        int empty = 0;

        FileOutputStream fos = new FileOutputStream("simple.bin");

        // while not end of file keep parsing
        while (infile.hasNext()) {
            line = infile.nextLine();
            input = new Scanner(line);
            lexeme = input.next();
            int ptr;
            //	lookup opcode and generate appropriate instructions
            int opcode = lookUpOpcode(lexeme);
            switch (opcode) {
                case HALT:
                    insertCode(locationCounter, HALT);
                    try {
                        fos.write(HALT);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case PUSH:
                    lexeme = input.next();
                    insertCode(locationCounter, PUSH, Integer.parseInt(lexeme));
                    try {
                        fos.write(PUSH);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(Integer.parseInt(lexeme));
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case RVALUE:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, RVALUE, tab.get(ptr).getAddress());
                    try {

                        fos.write(RVALUE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case LVALUE:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, LVALUE, tab.get(ptr).getAddress());
                    try {
                        fos.write(LVALUE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case POP:
                    insertCode(locationCounter, POP);
                    try {
                        fos.write(POP);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case ASGN:
                    insertCode(locationCounter, ASGN);
                    try {
                        fos.write(ASGN);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case COPY:
                    insertCode(locationCounter, COPY);
                    try {
                        fos.write(COPY);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case ADD:
                    insertCode(locationCounter, ADD);
                    try {
                        fos.write(ADD);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case SUB:
                    insertCode(locationCounter, SUB);
                    try {
                        fos.write(SUB);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case MPY:
                    insertCode(locationCounter, MPY);
                    try {
                        fos.write(MPY);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case DIV:
                    insertCode(locationCounter, DIV);
                    try {
                        fos.write(DIV);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case MOD:
                    insertCode(locationCounter, MOD);
                    try {
                        fos.write(MOD);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case NEG:
                    insertCode(locationCounter, NEG);
                    try {
                        fos.write(NEG);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case NOT:
                    insertCode(locationCounter, NOT);
                    try {
                        fos.write(NOT);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case OR:
                    insertCode(locationCounter, OR);
                    try {
                        fos.write(OR);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case AND:
                    insertCode(locationCounter, AND);
                    try {
                        fos.write(AND);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case EQ:
                    insertCode(locationCounter, EQ);
                    try {
                        fos.write(EQ);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case NE:
                    insertCode(locationCounter, NE);
                    try {
                        fos.write(NE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case GT:
                    insertCode(locationCounter, GT);
                    try {
                        fos.write(GT);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case GE:
                    insertCode(locationCounter, GE);
                    try {
                        fos.write(GE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case LT:
                    insertCode(locationCounter, LT);
                    try {
                        fos.write(LT);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case LE:
                    insertCode(locationCounter, LE);
                    try {
                        fos.write(LE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case LABEL:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, LABEL, tab.get(ptr).getAddress());
                    try {
                        fos.write(LABEL);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case GOTO:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, GOTO, tab.get(ptr).getAddress());
                    try {
                        fos.write(GOTO);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case GOFALSE:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, GOFALSE, tab.get(ptr).getAddress());
                    try {
                        fos.write(GOFALSE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case GOTRUE:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, GOTRUE, tab.get(ptr).getAddress());
                    try {
                        fos.write(GOTRUE);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case PRINT:
                    insertCode(locationCounter, PRINT);
                    try {
                        fos.write(PRINT);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case READ:
                    insertCode(locationCounter, READ);
                    try {
                        fos.write(READ);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case GOSUB:
                    lexeme = input.next();
                    ptr = tab.lookup(lexeme);
                    insertCode(locationCounter, GOSUB, tab.get(ptr).getAddress());
                    try {
                        fos.write(GOSUB);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(tab.get(ptr).getAddress());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case RET:
                    insertCode(locationCounter, RET);
                    try {
                        fos.write(RET);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        fos.write(empty);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;

                default:
                    System.err.println("Unimplemented opcode:  " + opcode);
                    System.exit(opcode);
            }
            locationCounter++;
        }

    }

    public static void insertCode(int loc, int opcode, int operand) {
        System.out.println(loc + ":\t" + opcode + "\t" + operand);

    }

    public static void insertCode(int loc, int opcode) {
        insertCode(loc, opcode, 0);
    }

    public static void dumpSymbolTable(SymbolTable tab) {
        System.out.println("\nlexeme \ttype \taddress");
        System.out.println("-----------------------------------------");
        for (int i = 0; i < tab.size(); i++) {
            System.out.println(tab.get(i).lexeme +"\t\t"+tab.get(i).type + "\t\t" + tab.get(i).address);
        }
    }


    public static class SymbolTable{    //Symbol table using linked list of table entries
        List<SymbolTableEntry> table = new LinkedList<SymbolTableEntry>();  //Linked List for the Symbol table
        public SymbolTableEntry get(int num){
            return table.get(num);
        }

        public int lookup(String temp){      //Compare the lexeme in each table entry to the lexeme given
            int i = 0;
            while(i < table.size()){
                if(!table.get(i).lexeme.equals(temp)){
                    i++;
                }
                else{

                    break;
                }
            }//end while loop
            return i;
        }

        public int size(){      //Simple returning of table size
            return table.size();
        }

        public void insert(String lexeme, String type, int location){//Adding entry into the Symboltable, using entries counter

            table.add(new SymbolTableEntry(lexeme,type,location));
        }
    }

    public static class SymbolTableEntry{   //Entries are the structures within the symbol table
        String lexeme;
        String type;
        int address;
        SymbolTableEntry(String l, String t, int a){    //Constructor
            lexeme = l;
            type = t;
            address = a;
        }
        public int getAddress(){    //returns the address of a table entry
            return address;
        }
    }

}

