void createAlias() {
    char alias[100];
    char choice[49];
    strcpy(alias,"alias ");
    int test=0;
    do{
      printf("donner un alias sous la forme NOM_ALIAS='COMMANDE_SYSTEME'\n");
      fgets(choice,sizeof(choice),stdin);
      if(strchr(choice,'=')==NULL || strchr(choice,'\'')==NULL)  {
       printf("format invalide\n");
      }else{
         test=1;
         strcat(alias,choice);
         printf("alias = %s\n",alias);
         FILE * bashrc = fopen("/home/oussama/.bashrc","a+");
         if(bashrc==NULL) {
           printf("error occured");
         }else{
           fputs(alias,bashrc);
           fclose(bashrc);
         }
       
         
         //system(alias);
      }
    }while(test==0);
}