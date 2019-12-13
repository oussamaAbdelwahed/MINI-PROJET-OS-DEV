#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void executeSysCommand(char * path) {
  char * cmdPrefix[] = {"/bin/ls"};
  char * args[]={cmdPrefix[0],"-l",path,NULL};
  

  execve(cmdPrefix[0],args,NULL);
}

int main(int argc,char * argv[]) {
    if(argc==1) {
       executeSysCommand(argv[1]);
    }else{
      printf("param 1 is %s",argv[1]);
    }   
}