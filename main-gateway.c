#include<stdio.h>
#include<stdlib.h>

 int main(int argc,char * argv[]) {
     int choice=0;
     int stop=0;
     while(!stop) {
        do{
            printf("1: partie 1 ====> interpréteur de commandes\n");
            printf("2: partie 2 ====> algorithmes d'ordonnancement\n");
            printf("3: quitter le programme\n");
            printf("choisir la partie du projet a executer(1 ou 2) pour quitter taper 3\n");
            scanf("%d",&choice); 

        }while(choice !=1 && choice!=2 && choice!=3);
        switch (choice) {
              case 1: 
                 system("./command-line/command-line");
              break;
              case 2:
                 system("./scheduler-simulator/sched-algs");
              break;
              case 3:
                stop=1;
              break;
        }
     }
 }