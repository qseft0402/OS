#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <thread>
using namespace std;

#define NUM_THREADS 100
#define MIN_PID 300
#define MAX_PID 5000
#define TRUE 1
#define FALSE 0
struct tab_pid{
	int value_pid;
	int is_avail;
}*pid_obj,tp[NUM_THREADS];
int allocate_map(void)
{
	int k;
	pid_obj=(struct tab_pid *)calloc((MAX_PID-MIN_PID+1),sizeof(struct tab_pid));
	//"if" loop for verification
	if(pid_obj==NULL)
		return -1;
	pid_obj[0].value_pid=MIN_PID;
	pid_obj[0].is_avail=TRUE;
	//"for" loop until "MAX_PID-MIN_PID+1"
	for( k=1;k<MAX_PID-MIN_PID+1;k++)
		{
		pid_obj[k].value_pid=pid_obj[k-1].value_pid+1;
		pid_obj[k].is_avail=TRUE;
	}
	//Returns the value 1
	return 1;
}
//Declare a function
int allocate_pid(void)
{
	//Declare a variables
	int k ;
	//for loop until "MAX_PID-MIN_PID+1"
	for( k=0;k<MAX_PID-MIN_PID+1;k++)
	{
		if(pid_obj[k].is_avail==TRUE)
		{
			pid_obj[k].is_avail=FALSE;
			//Returns the value
			return pid_obj[k].value_pid;
		}	
	}
	//"if" loop
	if(k==MAX_PID-MIN_PID+1)
		//Returns the value -1
		return -1;
}
//Declare a function "release_pid"
void release_pid(int pid){
	pid_obj[pid-MIN_PID].is_avail=TRUE;
}


void *childThread(void *data) {
   struct tab_pid *tp=(struct tab_pid*)data;
   cout<<"creat thread  pid:"<<tp->value_pid<<endl;
   unsigned int sleepT=rand()%5;
   sleep(sleepT);
   release_pid(tp->value_pid);
   cout<<"release pid:"<<tp->value_pid<<endl;
}

int main () {
   pthread_t threads[NUM_THREADS];
   allocate_map();
   int rc;
   int i;
   
   for( i = 0; i < NUM_THREADS; i++ ) {
      int pid=allocate_pid();
      
      tp[i].value_pid=pid;
      
      //cout<<pid_obj->value_pid<<endl;
      rc = pthread_create(&threads[i], NULL, childThread, (void *)&tp[i]);
      
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }

  pthread_exit(NULL);
}
