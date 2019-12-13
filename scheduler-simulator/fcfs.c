#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
struct pr {
    int indice ;
    int pi ;
    int ri ;
    int prio ;
}; typedef struct pr prs ;
int numberOfLignes = 0;

void AffichageDyn(prs Tab[],int n)
{
    int i ;
    for (i=0;i<n;i++)
    {
        printf("PID%d works for %d\n",Tab[i].indice,Tab[i].ri);
        sleep(Tab[i].ri);
    }
}
void AfficherTab(prs Tab[], int n)
{
    int i ;
    for(i=0;i<n;i++) {
     printf("Pros Numero %d ,Pi = %d , Ri= %d \n",Tab[i].indice,Tab[i].pi,Tab[i].ri);
     }
}
void Ordononcement_Pi ( prs Tab[], int n)
{
    int i , mini , j ;
    prs x ;
    for (i = 0 ; i < n-1 ; i++) {
        mini = i ;
        for (j = i+1 ; j< n ; j++)
        
            if (Tab[j].pi < Tab[mini].pi)
            mini = j;
            x = Tab[i];
            Tab[i]=Tab[mini] ;
            Tab[mini]=x;
    }
    for(i=0 ; i<n ; i++)
    {
        printf("(P%d) : for %d | ",Tab[i].indice,(Tab+i)->ri);
    }
    printf("\n");
}
void main(){
    system("clear");
    prs Tab[20];
    int j;
    int i=-1;
    const char virgule[2] = ";";
    int num ;
    char file_path[100];
    char proc[100];
    char * p ;

    FILE * processus ;

    /*initialize table to -1 */
    for(j=0;j<10;j++) {
        Tab[j].indice = -1 ;
        Tab[j].pi = -1 ;
        Tab[j].ri = -1 ; 
        Tab[j].prio = -1 ;
    }
    /* end */
    /*printf("donner le nom du fichier qui contient la commande \n");
    scanf("%s",file_path);*/
    processus=fopen("processus_infos.csv","r");
        if(processus!=NULL) {
            strcpy(proc,"");
            while(fgets(proc,100,processus)!=NULL){
                numberOfLignes++;
                /*printf("%s",proc);*/ 
                p = strtok(proc, virgule);
                      i++;
                      while( p != NULL ) {
                        if (Tab[i].indice == -1)
                            {
                              Tab[i].indice = atoi(p);
                            }
                        else if (Tab[i].pi == -1)
                            {   
                            Tab[i].pi = atoi(p);
                            }
                        else if(Tab[i].ri == -1) {
                            Tab[i].ri = atoi(p);
                            }
                        else 
                        {
                            Tab[i].prio = atoi(p);
                        }
                        /*printf("%d\n", atoi(p) );*/
                        p = strtok(NULL, virgule);
                    }
                
            }
            
            Ordononcement_Pi(Tab,numberOfLignes);
            AffichageDyn(Tab,numberOfLignes);
            fclose(processus);

        }
        else 
        {
           printf("fichier du liste des processus non existant\n");
        }

    }