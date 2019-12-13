void editEnvVars() {
   char env_var[50];
   const char separator[2]="=";
   char * key=(char*)malloc(15 * sizeof(char));
   char * value = (char*)malloc(50 * sizeof(char));
   int test=0;
   do {
       printf("donner la variable sous forme NOM_VARIABLE=VALEUR VARIABLE\n");
       scanf("%s",env_var);
       if((strchr(env_var,'='))==NULL) {
        printf("le formant n'est pas respécté : NOM_VARIABLE=VALEUR VARIABLE\n");
       }else{
         key = strtok(env_var,separator);
         value = strtok(NULL,separator);
         if(strcmp(key,"HOME")==0) {
            test=1;
            strcpy(ENV_VARIABLES.HOME,value);
         }else if(strcmp(key,"PATH")==0){
            test=1;
            strcpy(ENV_VARIABLES.PATH,value);
         }else{
            printf("variable non reconnu\n");
         }
       }
       //getchar();
   }while(test==0);
   /*free(key);
    free(value);*/
}