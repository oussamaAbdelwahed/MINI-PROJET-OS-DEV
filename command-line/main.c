#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h> 
#include<sys/types.h>

#include "globals.h"
#include "c_cd.h"
#include "c_ls.h"
#include "c_execute.h"
#include "edit_env_vars.h"
#include "c_alias.h"
#include "utils.h"
#include "c_pwd.h"
#include "menu.h"

int isChildProc(int pid) {
  return pid==0 ? 1 : 0;
}

int main(int argc,char * argv[]){
     FILE * profile = bootstrapSelf();
     const char pipeSymbol[2]="|";
     const char separator[2]=" ";
     int testEnter=1;
     while(1) {
      int j=0;
      char * parameters_list[50]={NULL};
      char choice[50];

      show_menu();
      changeTextColorTo(BOLD_RED[0]);
        printf("choisir une commande a executer\n");
      resetTextColor();

      if(argc > 1 && testEnter==1) {
        char * fn = argv[1];
        handleExecutingMySeqCommands(argv[1],profile);
        testEnter=0;
      }else{
        fgets(choice,50,stdin);
        char static_choice[100];
        strcpy(static_choice,choice);
        parameters_list[j] = strtok(choice, separator);
      
        while(parameters_list[j] != NULL) {
          j++;
          parameters_list[j] = strtok(NULL, separator);
        }

        int command_index = commandExists(parameters_list[0],COMMANDS_ARRAY_LENGTH);
        if(command_index==-1){
               if(strchr(static_choice,'|') != NULL) {
                    char * firstPart =NULL;
                    char * secondPart=NULL;
                    firstPart = strtok(static_choice,pipeSymbol);
                    secondPart = strtok(NULL,pipeSymbol);
                     
                    deleteSlashN(secondPart);
                    char ** firstPartParams = getCommandParameters(firstPart,"/bin/");
                    char ** secondPartParams = getCommandParameters(secondPart,"/bin/");
                    int a[2]; 
                    int p = fork();
                    if(isChildProc(p)){ 
                      pipe(a); 
                      int pid = fork();
                      if(isChildProc(pid)) {
                        close(1); 
                        dup(a[1]); 
                        close(a[0]); 
                        execvp(*(firstPartParams+0),firstPartParams);
                      }else{ 
                        close(0); 
                        dup(a[0]); 
                        close(a[1]); 
                        execvp(*(secondPartParams+0),secondPartParams);
                      } 
                    }  
               }else{
                 system(static_choice);
               }     
        }else{
          ExecuteCommandFunction(command_index,parameters_list,profile);
        }
      }
    }
  return 0;
}