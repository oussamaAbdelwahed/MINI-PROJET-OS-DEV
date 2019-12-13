
void c_pwd(){
    char  pwd_content[100];
    getcwd(pwd_content,sizeof(pwd_content));
    changeTextColorTo(GREEN[0]);
    printf("le chemin courant =====> %s\n",pwd_content);

    resetTextColor();

}