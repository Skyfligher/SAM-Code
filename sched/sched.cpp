#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;


struct process
{
    int letter;
    int priority;
    int arrive;
    int cpu;
    int finish;
   /* process(int p, int a, int c,int l){
        priority = p;
        arrive = a;
        cpu = c;
        letter = l;
    }*/
    bool operator < (const process p)const{
        return this->priority < p.priority;
    }
};


void findinsert();
void checkRR();
std::priority_queue<process> pq;
ifstream infile;
bool EoQ = false;
bool RR;
int count = 0;
int tot;
int quantum;
process insert[100];
int results[500];




int main(int argc, char *argv[])
{
  infile.open(argv[1]);
  if(!infile.good()){
      fprintf(stderr,"Error opening input file ");
      return 0;
  }
  cout <<"What should the quantum be?\n";
  cin >> quantum;
  infile >> tot;

  int a;
  int p;
  int c;
  for(int i = 0; i<tot; i++){
    infile >> a >> p >> c;
    insert[i] = {i,9-p,a,c};
  }

    int tempnum;
  while(!EoQ){
      findinsert();
      checkRR();
      while(RR){
          for(int i = 0; i < quantum && (pq.top().cpu - (i+1) != 0); i++){
              tempnum = i;
              results[count] = pq.top().letter;
              count++;
              findinsert();
              checkRR();
                if(!RR){
                    process temp = pq.top();
                    pq.pop();
                    temp.cpu = temp.cpu - (i+1);
                    pq.push(temp);
                    goto a;
                }

          }
          if(pq.top().cpu - (tempnum+1) == 0){
              insert[(pq.top().letter)-1].finish = count;
              pq.pop();
          }
          else{
              process temp = pq.top();
              pq.pop();
              temp.cpu = temp.cpu - quantum;
              pq.push(temp);
          }

      }
      a:
      results[count] = pq.top().letter;
      count++;
      process temp = pq.top();
      pq.pop();
      temp.cpu = temp.cpu - 1;
      if(temp.cpu != 0){
          pq.push(temp);
      }
      else{
          insert[(temp.letter)-1].finish = count;
      }

  }

  for(int i = 0; results[i]; i++){
      cout << results[i] << '\t';
  }
  for(int i = 0; i< tot; i++){
      cout << "Process: " << i<<" Turnaround = " << (insert[i].finish - insert[i].arrive) << "\n";
  }


}

void findinsert(){
    for(int i = 0; i<tot; i++){
        if(insert[i].arrive == count){
            pq.push(insert[i]);
        }
    }
}

void checkRR(){
    std::priority_queue<process> temp = pq;
    int temp1 = temp.top().priority;
    temp.pop();
    int temp2 = temp.top().priority;
    if(temp1 == temp2){
        RR = true;
    }
    else{
        RR = false;
    }

}

