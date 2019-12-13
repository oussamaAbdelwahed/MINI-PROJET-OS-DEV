void c_ls(char * argv[]) {
char  generated_command[50] = {"ls "};
    if(argv[1]==NULL) {
        strcat(generated_command,default_path);
        system(generated_command);
    }else{
      int i=1;
      while(argv[i]!=NULL && strcmp(argv[i],"-")!=0) {
        strcat(generated_command," ");
        strcat(generated_command,argv[i++]);
      }
      system(generated_command);
    }
}     