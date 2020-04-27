#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <unistd.h>
#define BUF_SIZE 2048

using namespace std;
int main(void){

	do{
		struct stat ssrc,star;
		string src,tar;
		ssize_t ret_in,ret_out;
		char buffer[BUF_SIZE];
		cout<<"please input source file name:"<<endl;	
		cin>>src;

		int input=open(src.c_str(),O_EXCL);
		if(input==-1){
			cout<<"the file !is not exist!"<<endl;
			cout<<"please retype source file name:"<<endl;
			continue;
		}
		
		cout<<"please input target file name:"<<endl;
		cin>>tar;

		
		int output=open(tar.c_str(),O_RDWR |O_CREAT );
		if(output==-1){
			cout<<"open fail!"<<endl;	
		}


		while((ret_in=read(input,&buffer,BUF_SIZE))>0){
			ret_out=write(output,&buffer,(ssize_t)ret_in);
			if(ret_out != ret_in){
				cout<<"write fail!"<<endl;
						
			}
		}
		if(close(input)==-1) cout<<"input close fail"<<endl;
		if(close(output)==-1) cout<<"output close fail"<<endl;
		chmod(tar.c_str(), S_IRWXU|S_IRWXG|S_IROTH|S_IWOTH);
		break;


	}while(1);

return 0;
}
