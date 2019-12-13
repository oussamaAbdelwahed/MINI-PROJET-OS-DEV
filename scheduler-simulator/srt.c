#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include <time.h>
#include"colors.h"

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
     printf("\n\n*********DIAGRAMME DE GANT DE L'ORDANNACEMENT SELON SHORTEST REMAINING TIME [SRT]*********\n\n");
   resetTextColor();
   double averageRotTime=0;
   double averageWaitingTime=0;
   float offset = 0;
   if(q->head==NULL) {
      printf("ERROR\n");
      exit(0);
   }
   char * tmp = NULL;

   while(q->head != NULL) {
      if(tmp ==NULL || strcmp(q->head->process->label,tmp)!=0)
         printf(" %s |",q->head->process->label);

      tmp = q->head->process->label;  
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


void printQueue(Queue q) {
    while(q.head !=NULL) {
       printf("label : %s\n",(q.head)->process->label);
       printf("startAt : %d\n",(q.head)->process->startAt);
       printf("duration : %d\n",(q.head)->process->duration);
       printf("priority : %d\n",(q.head)->process->priority);
       q.head = (q.head)->next;
    }
}

void adjustProcessRemainingDuration(Process * p,int quantum) {
   p->duration = p->duration - quantum;
}


Process * getCorrespondingProcToExec(Process ** procTab,int length,int currentTime) {
     Process * tmp[20];
     int j=0;
     for(int i=0;i<length;i++) 
       if((*(procTab+i))->startAt <=currentTime)
         tmp[j++] = *(procTab+i);
         
     Process * min=tmp[0];
     for(int i=0;i<j;i++) 
         if(tmp[i]->duration < min->duration && tmp[i]->duration > 0) 
           min = tmp[i];

     return  min;
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

int main(int argc,char * argv[]) {
   system("clear");
   changeTextColorTo(BOLD_GREEN[0]);
     printf("Algorithme d'ordannacement SRT (Shortest Remaining Time)\n\n\n");
   resetTextColor();
     int QUANTUM = 1;
     char * qnt;

     if(argc > 1) {
       qnt = argv[1];
       sscanf(qnt,"%d",&QUANTUM); 
     }


     struct timespec tim, tim2;
     tim.tv_sec = 0;
     tim.tv_nsec = 0;
     Process * p = NULL;
     
     int maxProc = 30;
     Queue * gantQueue = createQueue();
     int tabCounter=0;
    
    Process ** procTab = fillProcessTab(maxProc);
 

     Process ** uniqueProc = (Process**)malloc(nbrProcesses * sizeof(*uniqueProc));
     int counter=0;
     int currentTime=0;

     Process * procToExec = getCorrespondingProcToExec(procTab,nbrProcesses,currentTime);
     Process * tmpProc = procToExec;

     while(procToExec->duration>0){
         addToQueue(gantQueue,procToExec);
         if(counter ==0 && procToExec->startAt !=0){
              tim.tv_sec = procToExec->startAt;
              tim.tv_nsec = 0;
              printf("Attente d'arrivée d'un premier processus pour l'executer...\n\n");
              nanosleep(&tim,&tim2);
         }
         if(procToExec == tmpProc) {
           if(counter == 0) {
               printf("Processus ");
               changeTextColorTo(BOLD_RED[1]);
                  printf(" %s ",procToExec->label);
               resetTextColor();
               printf(" est en train de s'executer ...\n");
             
           }
         }else{
             printf("Processus ");
             changeTextColorTo(BOLD_RED[1]);
               printf(" %s ",procToExec->label);
             resetTextColor();
             printf(" est en train de s'executer ...\n");
         }
         tim.tv_sec = 1;
         currentTime+=1;
         tim.tv_nsec = 0;
         nanosleep(&tim,&tim2);
         procToExec->finishesAt = currentTime;
         adjustProcessRemainingDuration(procToExec,1);

         if(procToExec->duration <= 0){
            *(uniqueProc+tabCounter) = procToExec;
            tabCounter++;
         } 
         counter++;
         tmpProc = procToExec;
         procToExec = getCorrespondingProcToExec(procTab,nbrProcesses,currentTime);
     }
     showGantSchedDiag(gantQueue,QUANTUM,uniqueProc,nbrProcesses);
}