#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {
    int choice=0;
    int stop=0;
    char quantum[10];
    char command[200];
    strcpy(command,"./scheduler-simulator/rr-scheduler ");
    while(!stop) {
        do{
             printf("\n\n\n\n");
             printf("1 : algorithme FIFO\n");
             printf("2 : algorithme RR\n");
             printf("3 : algorithme SRT\n");
             printf("4 : quitter\n");
             printf("\n\n\n*********************************\n");
             printf("choisir le numéro d'algorithme à executer (1,2,3)\n");
             scanf("%d",&choice);
        }while(choice !=1 && choice != 2 && choice !=3 && choice !=4);
        switch (choice) {
                 case 1 : 
                    system("./scheduler-simulator/fcfs-scheduler");
                 break;
                 case 2: 
                     printf("donner le quantum\n");
                     scanf("%s",quantum);
                     for(int i=0;i<strlen(quantum);i++){
                         if(quantum[i]=='\n'){
                             quantum[i]='\0';
                         }
                     }
                     strcat(command,quantum);
                     printf("\n\n");
                     system(command);
                 break;
                 case 3:
                  system("./scheduler-simulator/srt-scheduler");
                 break;
                  case 4:
                     stop=1;
                 break;
        }
    }
}