#include "hashtable.h"

hashTable::hashTable(){

}

void hashTable::linadd(string temp){
    hashes++;
    if(hashes <= 128){
    key = temp;
    probes = 1;
    this->hash();
    if(table[inithash][0] == ""){
        table[inithash][0] = key;
        table[inithash][1] = to_string(inithash);
        table[inithash][2] = "1";
        return;
    }
    else{
        probes = 0;
        int current;
        for(int i = inithash; table[i][0] != ""; i++){
            if(i <= 127){
                probes++;
                current = i;
            }
            else{
                i = -1;
                probes++;
                current = i;
            }
        }
        probes++;
        current++;
        table[current][0] = key;
        table[current][1] = to_string(inithash);
        table[current][2] = to_string(probes);
    }

}
    else{
        cout<<"Overflow";
        return;
    }
}

void hashTable::linsearch(string temp){
    key = temp;
    probes = 1;
    this->hash();
    if(table[inithash][0] == temp){
        cout<<table[inithash][0]<<"\t"<<table[inithash][1]<<"\t"<<table[inithash][2]<<"\t"<<inithash<<"\n";
        return;
    }
    else{
        probes = 0;
        int current;
        for(int i = inithash; table[i][0] != temp; i++){
            if(i <= 127){
                probes++;
                current = i;
            }
            else{
                i = -1;
                probes++;
                current = i;
            }
        }
        probes++;
        current++;
        cout<<table[current][0]<<"\t"<<table[current][1]<<"\t"<<table[current][2]<<"\t"<<current<<"\n";
        return;
    }
}

void hashTable::randadd(string temp){
    hashes++;
    if(hashes <= 128){
        key = temp;
        probes = 1;
        this->hash();
        if(table[inithash][0] == ""){
            table[inithash][0] = key;
            table[inithash][1] = to_string(inithash);
            table[inithash][2] = "1";
        }
        else{
            int casetype = 1;
            int current = inithash;
            int r = 1;
            probes = 1;
            while(table[current][0] != ""){
                probes++;
                r = (r*5) % 512;
                current = (r/4);
                if(r == 1){
                    casetype = 2;
                    break;
                }
            }
            switch (casetype) {
            case 1:
                    table[current][0] = key;
                    table[current][1] = to_string(inithash);
                    table[current][2] = to_string(probes);
                break;
            case 2:
                if(table[0][0] == ""){
                    table[0][0] = key;
                    table[0][1] = to_string(inithash);
                    table[0][2] = to_string(probes);
                }
                else{
                    table[127][0] = key;
                    table[127][1] = to_string(inithash);
                    table[127][2] = to_string(probes);
                }
                break;
            }
        }

    }

}

void hashTable::randsearch(string temp){
    key = temp;
    probes = 1;
    this->hash();
    if(table[inithash][0] == temp){
        cout<<table[inithash][0]<<"\t"<<table[inithash][1]<<"\t"<<table[inithash][2]<<"\t"<<inithash<<"\n";
    }
    else{
        int casetype = 1;
        int current = inithash;
        int r = 1;
        probes = 1;
        while(table[current][0] != temp){
            probes++;
            r = (r*5) % 512;
            current = (r/4);
            if(r == 1){
                casetype = 2;
                break;
            }
        }
        switch (casetype) {
        case 1:
                cout<<table[current][0]<<"\t"<<table[current][1]<<"\t"<<table[current][2]<<"\t"<<current<<"\t"<<"\n";
            break;
        case 2:
            if(table[0][0] == temp){
                cout<<table[0][0]<<"\t"<<table[0][1]<<"t"<<table[0][2]<<"\t"<<"0"<<"\n";
            }
            else{
                cout<<table[127][0]<<"\t"<<table[127][1]<<"\t"<<table[127][2]<<"t"<<"128"<<"\n";
            }
            break;
        }
    }
}

void hashTable::hash(){
    if(key.length()>=7){
        char buffer1[] = {key.at(0),key.at(1)};
        char buffer2[] = {key.at(5),key.at(6)};
        //cout<<buffer1[0]<<buffer1[1]<<" ";
        //cout<<buffer2[0]<<buffer2[1]<<"\n";
        unsigned long final1 = buffer1[0];
        unsigned long final2 = buffer2[0];
        final1 = final1<<8;
        final1 = final1|buffer1[1];
        final2 = final2<<8;
        final2 = final2|buffer2[1];
        //cout<<final1<<" "<<final2<<"\n";
        char fifteen;
        if(key.length() >= 15){
            fifteen = key.at(14);
            inithash = ((final1 + final2 + 101 + fifteen) % 128)-1;
            //cout<<fifteen<<"\n";
        }
        else{
            inithash = ((final1 + final2 + 101) % 128)-1;
        }
    }
    else if(key.length() == 6){
        char buffer1[] = {key.at(0),key.at(1)};
        char buffer2 = key.at(5);
        //cout<<buffer1[0]<<buffer1[1]<<" ";
        //cout<<buffer2<<"\n";
        unsigned long final1 = buffer1[0];
        unsigned long final2 = buffer2;
        final1 = final1<<8;
        final1 = final1|buffer1[1];
        final2 = final2<<8;
        //cout<<final1<<" "<<final2<<"\n";
        inithash = ((final1 + final2 + 101) % 128)-1;
    }
    else{
        char buffer1[] = {key.at(0),key.at(1)};
        //cout<<buffer1[0]<<buffer1[1]<<"\n";
        unsigned long final1 = buffer1[0];
        final1 = final1<<8;
        final1 = final1|buffer1[1];
        //cout<<final1<<"\n";
        inithash = ((final1 + 101) % 128)-1;
    }

}

void hashTable::print(){
    for(int i = 0; i<128; i++){
        if(table[i][0] != ""){
            cout<<table[i][0]<<"\t"<<table[i][1]<<"\t"<<table[i][2]<<"\t"<<i<<"\n";
        }
    }
    return;
}
