#include <iostream>
#include <fstream>
#include <stack>
#include <string>


#define HALT	0
#define PUSH	1
#define RVALUE  2
#define LVALUE	3
#define POP	4
#define STO	5
#define COPY	6
#define ADD    	7
#define SUB     8
#define MPY    	9
#define DIV     10
#define MOD     11
#define NEG	12
#define NOT	13
#define OR      14
#define AND     15
#define EQ      16
#define NE      17
#define GT      18
#define GE      19
#define LT      20
#define LE      21
#define LABEL	22
#define GOTO	23
#define GOFALSE	24
#define GOTRUE	25
#define PRINT	26
#define READ	27
#define GOSUB	28
#define RET	29
#define ORB     30
#define ANDB    31
#define XORB    32
#define SHL	33
#define SHR	34
#define SAR	35




using namespace std;

stack <unsigned int> mainStack;
stack <unsigned int> call;

uint32_t instructions[65536];
uint32_t data[65536];

fstream binf;

string file;
uint32_t buffer;
int PC = 0;
bool STOP = false;
uint16_t opcode;
uint32_t operand;
uint32_t temp1;
uint32_t temp2;
uint32_t rvalue;
uint32_t lvalue;


uint32_t swap(uint32_t source){
    uint32_t b0,b1,b2,b3;
    uint32_t swap;

    b0 = (source & 0x000000ff) << 24u;
    b1 = (source & 0x0000ff00) << 8u;
    b2 = (source & 0x00ff0000) >> 8u;
    b3 = (source & 0xff000000) >> 24u;

    swap = b0 | b1 | b2 | b3;
    return swap;

}


int main(int argc, char *argv[])
{
    file = argv[1];

    binf.open(file,std::fstream::in | std::fstream::binary);

    if(!binf.is_open()){
        cout<<"File error.\n";
        return 0;
    }
    else{
      for(int i = 0;!binf.eof(); i++){
        binf.read(reinterpret_cast<char*>(&buffer), sizeof(uint32_t));
        instructions[i] = swap(buffer);
    }
}
    binf.close();

    while(STOP == false){
        opcode = instructions[PC]>>16;
        operand = instructions[PC] & 32767;

        switch (opcode) {
        case PUSH:
            mainStack.push(operand);
            PC++;
            break;
        case RVALUE:
            mainStack.push(data[operand]);
            PC++;
            break;
        case LVALUE:
            mainStack.push(operand);
            PC++;
            break;
        case POP:
            mainStack.pop();
            PC++;
            break;
        case STO:
            rvalue = mainStack.top();
            mainStack.pop();
            lvalue = mainStack.top();
            mainStack.pop();
            data[lvalue] = rvalue;
            PC++;
            break;
        case COPY:
            mainStack.push(mainStack.top());
            PC++;
            break;
        case ADD:
            temp1 = mainStack.top();
            mainStack.pop();
            temp2 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 + temp2);
            PC++;
            break;
        case SUB:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 - temp2);
            PC++;
            break;
        case MPY:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 * temp2);
            PC++;
            break;
        case DIV:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 / temp2);
            PC++;
            break;
        case MOD:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 % temp2);
            PC++;
            break;
        case NEG:
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 != 0){
                mainStack.push(~temp1 + 1);
            }
            else{
                mainStack.push(0);
            }
            PC++;
            break;
        case NOT:
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(~temp1);
            break;
        case OR:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 || temp2);
            PC++;
            break;
        case AND:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 && temp2);
            PC++;
            break;
        case EQ:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 == temp2){
                mainStack.push(1);
            }
            else{
                mainStack.push(0);
            }
            PC++;
            break;
        case NE:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 == temp2){
                mainStack.push(0);
            }
            else{
                mainStack.push(1);
            }
            PC++;
            break;
        case GT:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 > temp2){
                mainStack.push(1);
            }
            else{
                mainStack.push(0);
            }
            PC++;
            break;
        case GE:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 >= temp2){
                mainStack.push(1);
            }
            else{
                mainStack.push(0);
            }
            PC++;
            break;
        case LT:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 < temp2){
                mainStack.push(1);
            }
            else{
                mainStack.push(0);
            }
            PC++;
            break;
        case LE:
            temp2 = mainStack.top();
            mainStack.pop();
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 <= temp2){
                mainStack.push(1);
            }
            else{
                mainStack.push(0);
            }
            PC++;
            break;
        case LABEL:
            data[operand] = PC;
            PC++;
            break;
        case GOTO:
            PC = data[operand];
            PC++;
            break;
        case GOFALSE:
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 == 0){
                PC = data[operand];
                PC++;
            }
            else{
                PC++;
            }
            break;
        case GOTRUE:
            temp1 = mainStack.top();
            mainStack.pop();
            if(temp1 != 0){
                PC = data[operand];
                PC++;
            }
            else{
                PC++;
            }
            break;
        case PRINT:
            temp1 = mainStack.top();
            mainStack.pop();
            cout<<temp1<<"\n";
            PC++;
            break;
        case READ:
            cin>>temp1;
            mainStack.push(temp1);
            PC++;
            break;
        case GOSUB:
            call.push(PC);
            PC = data[operand];
            PC++;
            break;
        case RET:
            PC = call.top();
            call.pop();
            PC++;
            break;
        case ORB:
            temp1 = mainStack.top();
            mainStack.pop();
            temp2 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 | temp2);
            PC++;
            break;
        case ANDB:
            temp1 = mainStack.top();
            mainStack.pop();
            temp2 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 & temp2);
            PC++;
            break;
        case XORB:
            temp1 = mainStack.top();
            mainStack.pop();
            temp2 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1 ^ temp2);
            PC++;
            break;
        case SHL:
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1<<1);
            PC++;
            break;
        case SHR:
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1/2);
            PC++;
            break;
        case SAR:
            temp1 = mainStack.top();
            mainStack.pop();
            mainStack.push(temp1>>1);
            PC++;
            break;
        case HALT:
            STOP = true;
            break;
        default:
            break;
        }

    }

    cout<<"HALT found program closing.\n";

    return 0;
}
