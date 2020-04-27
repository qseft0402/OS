#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <iostream> 

using namespace std;

int main()
{
    pid_t pid;
    int fd1[2];
    int fd2[2];

    pipe(fd1);
    pipe(fd2);
    pid = fork();

    if (pid > 0) 
    {
	char output[512];
        int i;
        close(fd1[1]); 
        read(fd1[0], output, sizeof(output));
        for(i = 0; i<sizeof(output); i++) {
            if(97<=output[i] && output[i]<=122)
                output[i] -=32 ;
            else if(65<=output[i] && output[i]<=90)
                output[i] +=32 ;
        }
	output[i]='\0';
        write(fd2[1], output, strlen(output) + 1);
       
        wait(NULL); 
        
    }else if (pid == 0){
 	char input[512];
        close(fd1[0]); 
        cout<<"input: ";
	cin.get(input,sizeof(input));
        //cout<<"input: "<< input<<endl;

        write(fd1[1], input, strlen(input) + 1);
        read(fd2[0], input, strlen(input));
        cout<<"output: "<<input<<endl;

    }

    return 0;
}
