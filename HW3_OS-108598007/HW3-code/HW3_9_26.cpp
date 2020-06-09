#include<iostream>
#include<deque>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
void fifo(int frameSize,int n){
	int pages[n];
	srand (time(NULL));

	for(int i=0;i<n;i++){
		pages[i]=rand()%10+1;
		//std::cout<<pages[i]<<std::endl;
	}
	
    	std::deque<int> pageFrames;
    	int pageFault = 0;
    	for(int i=0; i < n;i++){
        	bool check = false;
        	for(std::deque<int>::iterator it = pageFrames.begin();it!=pageFrames.end();it++){
        	    if(*it == pages[i])
        	        check = true;
        	}
        	if(check == false){
        	    pageFault++;
        	    if(pageFrames.size() != frameSize)
        	        pageFrames.push_back(pages[i]);
            	else{
                	pageFrames.pop_front();
                	pageFrames.push_back(pages[i]);
            	}   
        	}
    	}
    std::cout << "FIFO-page-faults: " << pageFault << std::endl;
}

int main(){
	int n=30;
	std::cout<<"n:"<<n<<std::endl;
	fifo(4,n);


}
