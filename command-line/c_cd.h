void c_cd(char * path[]) {
  if(path[1]==NULL) {
    printf("\a chemin invalide ! \n");
  }else{
    chdir(path[1]);
    strcpy(default_path,path[1]);
  }
}