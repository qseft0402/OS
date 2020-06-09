#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


int main(int argc,char *argv[]){
cout<<"argc:"<<argv[1]<<endl;
unsigned long page;
unsigned long offset;SS
unsigned long address=atol(argv[1]);

page = address /4096;
offset=address % 4096;

cout<<"page number="<<page<<endl;
cout<<"offset="<<offset<<endl;

return 0;
}
