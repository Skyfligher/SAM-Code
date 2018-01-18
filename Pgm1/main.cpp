#include <gclose.h>
#include <string>

string file;
string results;

const static int size1  = 9;
const static int size2 = 7;

gclose<int,size1> main1;
gclose<int,size2> main2;

using namespace std;

int main()
{

    for(int i = 0; i< 4; i++){
        cout<<"Give the text file name.\n";
        cin>>file;
        cout<<"Give the name for the results file.\n";
        cin>>results;

        if(i<1){
            main1.read(file);
            main1.warsh();
            main1.print(results);
        }
        else{
            main2.read(file);
            main2.warsh();
            main2.print(results);
        }
    }
    return 0;
}
