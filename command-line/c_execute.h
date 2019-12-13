void c_execute(char * path) {
    char c;
    //while((c=getchar())!=EOF) {}
    FILE * commands_sequence = fopen(path,"r");
    if(commands_sequence!=NULL) {
    char commands[100];
    strcpy(commands,"");
    while(fgets(commands,100,commands_sequence)!=NULL) {

    }
    system(commands);
    getchar();
    fclose(commands_sequence);
    }else{
        printf("fichier de commande non existant\n");
        c = getchar();
        /*while(c!=' ') {
            c = getchar();
        }*/
    }
}