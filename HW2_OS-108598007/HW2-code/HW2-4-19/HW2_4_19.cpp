#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define NUM_THREADS 2
pthread_t threads[NUM_THREADS];
int n=0;
bool run=false;
int i=0;
bool isPrime(int num) 
{ 
    // Corner case 
    if (num <= 1) 
        return false; 
  
    // Check from 2 to n-1 
    for (int i = 2; i < num; i++) 
        if (num % i == 0) // 0->1
            return false; 
  
    return true; 
} 
void *printOutput(void *threadid){
	long tid;
	tid = (long)threadid;
	while(true){
		if(run){
			cout<<"threadid"<<tid<<" print prime number:"<<i<<endl;
			run=false;
		}
		if(i==2){
			cout<<"threadid"<<tid<<" break"<<endl;		
			break;
		}
	}
	pthread_exit(NULL);
}
void printAllPrime(long tid){
   for(i=n;i>2;i--){
	n=i;
	if(isPrime(i)){
		cout<<"treadid"<<tid<<" found prime number:"<<i<<endl;
		run=true;
		sleep(0.1);
	}
   }
}

void *childPrint(void *threadid) {
   sleep(0.5);
   long tid;
   tid = (long)threadid;
   printAllPrime(tid);
   pthread_exit(NULL);
}

int main () {
	
	cout<<"pls input the number:";
	cin>>n;
	int rc1,rc2;
	
	   
	rc1 = pthread_create(&threads[0], NULL, childPrint, (void *)0);
	if (rc1) {
	 cout << "Error:unable to create thread," << rc1 << endl;
	 exit(-1);
	}
   	rc2 = pthread_create(&threads[1], NULL, printOutput, (void *)1);
	if (rc2) {
	 cout << "Error:unable to create thread," << rc2 << endl;
	 exit(-1);
	}
	pthread_exit(NULL);
}
