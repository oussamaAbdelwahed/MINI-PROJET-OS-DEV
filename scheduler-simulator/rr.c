#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include <time.h>

#include "colors.h"

#define TRUE 1
#define FALSE 0

typedef struct Process Process;
typedef struct Queue Queue;
typedef struct Element Element;

typedef int  Boolean;

struct Process {
  char  label[20];
  int startAt;
  int duration;
  int staticDuration;
  int priority;
  int finishesAt;
  int marked;
};

struct Element {
   Process * process;
   Element * next;
};


struct Queue {
  Element * head;
  Element * queue;
};
int nbrProcesses = 0;



Queue * createQueue() {
    Queue * q = (Queue*)malloc(sizeof(*q));
    q->head = NULL;
    q->queue=NULL;

    return q;
}

void showGantSchedDiag(Queue * q,int quantum,Process ** uniqueProc,int nbrProcesses) {
  changeTextColorTo(BOLD_GREEN[0]); 
   printf("\n\n*********DIAGRAMME DE GANT DE L'ORDANNACEMENT SELON ROUND ROBIN QUANTUM [RR] = %d*********\n\n",quantum);
  resetTextColor();
   double averageRotTime=0;
   double averageWaitingTime=0;
   float offset = 0;
   if(q->head==NULL) {
      printf("ERROR\n");
      exit(0);
   }

   while(q->head !=NULL) {
       printf(" %s |",q->head->process->label);
       q->head = q->head->next;
   }


   for(int i=0;i<nbrProcesses;i++) {
      offset = (*(uniqueProc+i))->finishesAt - (*(uniqueProc+i))->startAt;
      averageRotTime += offset;
      averageWaitingTime += (offset - (*(uniqueProc+i))->staticDuration);
   }

   averageRotTime = averageRotTime / nbrProcesses;
   averageWaitingTime = averageWaitingTime / nbrProcesses;
  changeTextColorTo(BLUE[0]); 
   printf("\n\n\n<<<<<<<<<< RAPPORT D'EXECUTION >>>>>>>>>>\n\n");
   printf("\nTemps de rotation moyen = %lf\n",averageRotTime);
   printf("Temps d'attente  moyen = %lf\n",averageWaitingTime);
   printf("\n----------------------------------------------------------------\n");
  resetTextColor(); 

}


void addToQueue(Queue * q,Process * p){
  if(q!=NULL) {
      Element * e = (Element*)malloc(sizeof(*e));
      e->process = p;
      e->next = NULL;
    
      if(q->head==NULL) {
         e->next=NULL;
         q->head = e;
         q->queue=e;
      }else{
         q->queue->next = e;
         q->queue = e;
      }
  }
}

Process*  removeFromQueue(Queue * q) {
    if(q!=NULL && q->head!=NULL) {
        Element * tmp = q->head;
        q->head = q->head->next; 
        return tmp->process;
    }
    return NULL;
}


void adjustProcessRemainingDuration(Process * p,int quantum) {
   p->duration = p->duration - quantum;
}

Boolean isEmpty(Queue q) {
    return (q.head==NULL) ? TRUE : FALSE;
}

void sortTab(Process ** tab,int length) {
   int min=0;
   Process * tmp;
   for(int i=0;i<length;i++){
      min=i;
      for(int j=i+1;j<length;j++){
         if((*(tab+j))->startAt <= (*(tab+min))->startAt) {
            min = j;
         }
      }
     tmp = *(tab+i);
     *(tab+i) = *(tab+min);
     *(tab+min) = tmp;
   }
}

Queue * createInitialQueue(Process **processes,int arrayLength) { 
    Queue * q = createQueue();
    Process * min = *(processes+0);
    Process * tmp;
    int minIndex=0;
    int test=0;
    sortTab(processes,arrayLength);
    for(int i=0;i<arrayLength;i++){
        if((*(processes+i))->startAt==0) {
         test=1;
         addToQueue(q,*(processes+i));
        }
    }
    if(!test) {
       addToQueue(q,*(processes+0));
    }
   return q;
}


Process ** fillProcessTab(int nbrProc) {
   FILE * file = fopen("processus_infos.csv","r");
   char str[100];
   char separator[2]={";"};
   char token[30];
   int i=0;
   char * label= (char*)malloc(10 * sizeof(char));
   char * s1=(char*)malloc(10 * sizeof(char));
   char * s2=(char*)malloc(10 * sizeof(char));
   char * s3=(char*)malloc(10 * sizeof(char));
   if(file!=NULL){
      Process  ** resTab = malloc(nbrProc * sizeof(*resTab));
      while(fgets(str,sizeof(str),file)!=NULL){
         nbrProcesses++;
         Process * p=(Process*)malloc(sizeof(*p));
         p->marked = 0;
         p->finishesAt= 0;
         
         label = strtok(str,separator);
         s1 = strtok(NULL,separator);
         
         s2 = strtok(NULL,separator);
     
         s3 = strtok(NULL,separator);
         sscanf(label,"%s",p->label);
         sscanf(s1,"%d",&p->startAt);
         sscanf(s2,"%d",&p->duration);
         sscanf(s2,"%d",&p->staticDuration);
         sscanf(s3,"%d",&p->priority);
         *(resTab+i) = p;
         i=i+1;
      }
      fclose(file);
      return resTab;
   }
   fclose(file);
   return NULL;
}

void adjustQueue(Process ** procTab,Queue * q,int currentTime) {
    for(int i=1;i<nbrProcesses;i++){
        if((*(procTab+i))->startAt <= currentTime && (*(procTab+i))->marked==0) {
         addToQueue(q,*(procTab+i));
         (*(procTab+i))->marked=1;
        }
    }
}

int main(int argc,char * argv[]) {
    system("clear");
    int QUANTUM = 0;
    char * qnt;
    if(argc > 1) {
       qnt = argv[1];
       sscanf(qnt,"%d",&QUANTUM);
     }else{
        changeTextColorTo(BOLD_RED[0]);
         printf("\a vous devrez passer le quantum en parametre au programme sous la forme(./nom_du_programme valeur_du_quantum)\n");
        resetTextColor();
        exit(0);
     }

     changeTextColorTo(BOLD_GREEN[0]);
       printf("Algorithme d'ordannacement RR (Round Robin) quatum = %s\n\n\n",qnt);
     resetTextColor();
     

     struct timespec tim, tim2;
     tim.tv_sec = 0;
     tim.tv_nsec = 0;
     Process * p = NULL;
     
     int maxProc = 30;
     Queue * gantQueue = createQueue();
     int tabCounter=0;
    
    Process ** procTab = fillProcessTab(maxProc);
    Queue * q = createInitialQueue(procTab,nbrProcesses);

     Process ** uniqueProc = (Process**)malloc(nbrProcesses * sizeof(*uniqueProc));
     int counter=0;
     int currentTime=0;

     while(!isEmpty(*q)){
         p = removeFromQueue(q); 
         addToQueue(gantQueue,p);
         if(counter ==0 && p->startAt !=0){
              tim.tv_sec = p->startAt;
              tim.tv_nsec = 0;
              printf("Attente d'arrivée d'un premier processus pour l'executer.....\n\n");
              nanosleep(&tim,&tim2);
         }
         printf("Processus ");
         changeTextColorTo(BOLD_RED[1]);
           printf("%s ",p->label);
         resetTextColor();
         printf(" est en train de consommer son quantum ...\n");
         
         tim.tv_sec =  (p->duration < QUANTUM && p->duration > 0) ? p->duration : QUANTUM;
         currentTime+=(int)tim.tv_sec ;
         tim.tv_nsec = 0;
         nanosleep(&tim,&tim2);
         p->finishesAt = currentTime;
         adjustProcessRemainingDuration(p,QUANTUM);
         adjustQueue(procTab,q,currentTime);

         if(p->duration > 0){
            addToQueue(q,p);
         }else{
            *(uniqueProc+tabCounter) = p;
            tabCounter++;
         } 
         counter++;
     }
     showGantSchedDiag(gantQueue,QUANTUM,uniqueProc,nbrProcesses);
}