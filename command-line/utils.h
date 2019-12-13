int commandExists(char * needle,int array_length) {
 int i;
 int test=-1;
 char * str_tmp=(char*)malloc(20 * sizeof(char));
 strcpy(str_tmp,"");
 for(i=0;i<array_length;i++) {
   strcpy(str_tmp,*(commands+i));
   strcat(str_tmp,"\n");
   if(strcmp(needle,*(commands+i))==0 || strcmp(needle,str_tmp)==0) {
     return i;
   }
 }
 return test;
} 


char * getUsername() {
  char * username = (char*)malloc(20  *sizeof(char));
  getlogin_r(username,30);

  return username;
}


char * getHostname() {
  char * hostname =(char*)malloc(30 * sizeof(char));
  gethostname(hostname,50);

  return hostname;
}

char * getUserHomeDir() {
  return getenv("HOME"); 
}

void changeTextColorTo(char * color) {
  printf("%s",color);
}

void resetTextColor() {
   printf("\033[0m");
}


char * getHomeEnvVar(FILE * profile) {
  const char separator[2]="=";
  char * key=(char*)malloc(15 * sizeof(char));
  char * value = (char*)malloc(50 * sizeof(char));
  if(profile!=NULL) {
    char * res = (char*)malloc(100 * sizeof(char));
    strcpy(res,"");
    //rewind(profile);
    while(fgets(res,50,profile)!=NULL) {
       key = strtok(res,separator);
       if(strcmp(key,"HOME")==0) {
         value = strtok(NULL,separator);
         return value;
       }
    }
    free(key);
    free(res);
 }
 return NULL;
}

void getEnvVars(FILE * profile) {
   const char separator[2]="=";
  char * key=(char*)malloc(15 * sizeof(char));
  char * value = (char*)malloc(50 * sizeof(char));
  if(profile!=NULL) {
    char * res = (char*)malloc(100 * sizeof(char));
    strcpy(res,"");
    rewind(profile);
    //fseek(profile,0,SEEK_SET);
    while(fgets(res,50,profile)!=NULL) {
       key = strtok(res,separator);
       if(strcmp(key,"HOME")==0) {
         value = strtok(NULL,separator);
         strcpy(ENV_VARIABLES.HOME,value);
       }
       if(strcmp(key,"PATH")==0) {
         value = strtok(NULL,separator);
         strcpy(ENV_VARIABLES.PATH,value);
       }
    }
    free(key);
    free(res);
 }
}

char * getPathEnvVar(FILE * profile) {
  const char separator[2]="=";
  char * key=(char*)malloc(15 * sizeof(char));
  char * value = (char*)malloc(50 * sizeof(char));
  if(profile!=NULL) {
    char * res = (char*)malloc(100 * sizeof(char));
    strcpy(res,"");
    //rewind(profile);
    while(fgets(res,50,profile)!=NULL) {
       key = strtok(res,separator);
       if(strcmp(key,"PATH")==0) {
         value = strtok(NULL,separator);
         return value;
       }
    }
    free(key);
    free(res);
 }
 return NULL;
}



void persistEnvVars(FILE * profile) {
  if(profile!=NULL) {
    rewind(profile);
    char home_concat[55];
    char path_concat[55];
    

    strcpy(home_concat,"");
    strcpy(path_concat,"");

    strcpy(home_concat,"HOME=");
    strcat(home_concat,ENV_VARIABLES.HOME);

    strcpy(path_concat,"PATH=");
    strcat(path_concat,ENV_VARIABLES.PATH);

    profile = freopen("./custom.profile","w",profile);
    fputs(path_concat,profile);
    fputs(home_concat,profile);

    fclose(profile);
  }
}

void ExecuteCommandFunction(int commandIndex,char * params[],FILE * profile) {
    char choice=0;
    char file_name[20];
    char  pwd_content[1000];
    strcpy(pwd_content,"");
    strcpy(file_name,"");
    switch(commandIndex) {
        case 0: 
           c_ls(params);
        break;
        case 1:
          c_cd(params);
        break;
        case 2:
           createAlias();
        break;
        case 3:
           printf("le chemin courant == %s\n",default_path);
        break;
        case 4:
           editEnvVars();
        break;
        case 5:
          printf("donner l nom du ficher qui contient les commandes\n");
          scanf("%s",file_name);
          c_execute(file_name);
        break;
        case 6:
          while(choice != 'O' && choice!='o' && choice!='n' && choice!='N') {
            printf("voulez vous vraiment quittez: O/N\n");
            scanf("%c",&choice);
            if(choice == 'O' || choice == 'o'){
              persistEnvVars(profile);
              exit(0);
            }
            getchar();
          }
        break;
    }
}






FILE * bootstrapSelf() {
  system("clear");
  FILE * profile = fopen("./custom.profile","r+");

  getEnvVars(profile); 
  if(strcmp(ENV_VARIABLES.HOME,"") == 0) {
    changeTextColorTo(BOLD_RED[0]);
      printf("la variable d'environnement HOME n'est pas définie\n");
    resetTextColor();
  }

  if(strcmp(ENV_VARIABLES.PATH,"")==0) {
    changeTextColorTo(BOLD_RED[0]);
      printf("la variable d'environnement PATH n'est pas définie\n");
    resetTextColor();
  }

  default_path = ENV_VARIABLES.HOME;
  
  char * username = getUsername();
  char * hostname= getHostname();

  strcat(UNAndHN,username);
  strcat(UNAndHN,"@");
  strcat(UNAndHN,hostname);
 
  return profile;
}



void deleteSlashN(char * str) {
  char *pos;
    if ((pos=strchr(str, '\n')) != NULL) {
      *pos = '\0';
    }
}


char ** getCommandParameters(char * command,char * pathPrefix) {
  char ** parameters = malloc(20 * sizeof(char));
  const char separator[2]=" ";
  char *token;
  int i=0;
  char * tmp = (char*)malloc(30* sizeof(*tmp));
  char slash='/';
 
   token = strtok(command, separator);
   while( token != NULL ) {
      *(parameters+i++) = token;
      token = strtok(NULL, separator);
   }
  return parameters;
}



void handleExecutingMySeqCommands(char * fileName,FILE* profile) {
  FILE * cmds = fopen(fileName,"r");
  if(cmds!=NULL) {
    char commands[100];
    while(fgets(commands,sizeof(commands),cmds)!=NULL) {}
    int j=0;
    char sep[2]=";";
    char * token;
    const char separator[2]=" ";
    char * parameters_list[50]={NULL};
    char choice[50];
    int command_index =-1;
    char * commandsArray[20]={NULL};

    token = strtok(commands,sep);
    commandsArray[j++] = token;
    while(token!=NULL) {
      token = strtok(NULL,sep);
      commandsArray[j] = token;
      j++;
    }
    int i=0;
    while(commandsArray[i]!=NULL) {
        strcpy(choice,commandsArray[i]);
        j=0;
        parameters_list[j] = strtok(choice, separator);
        while(parameters_list[j] != NULL) {
          j++;
          parameters_list[j] = strtok(NULL, separator);
        }
        command_index = commandExists(parameters_list[0],COMMANDS_ARRAY_LENGTH);
        if(command_index >=0){
          ExecuteCommandFunction(command_index,parameters_list,profile);
        }
        i++;
    }
   }
   fclose(cmds);
}

