void show_menu() {
      changeTextColorTo(BOLD_RED[0]);
       printf("%s:",UNAndHN);
      resetTextColor();
      printf("%s\n",default_path);

      changeTextColorTo(GREEN[0]);
      printf("\n\n*************************************** LISTE DES COMMANDES ***************************************\n\n");
      resetTextColor();
      
      changeTextColorTo(BLUE[0]);
        printf("1: c_ls : permet de lister les répértoires dans le chemin donné en parametre sinon les repertoires du chemin courant\n");
        printf("2: c_cd: permet de changer le répertoire de travail \n");
        printf("3: c_set: modifier le variables d'environnement HOME et PATH\n");
        printf("4: c_exec_cmd_seq: executer un ensemble de commandes sequentiellement depuis un fichier donnée en entrée\n");
        printf("5: c_pwd : Afficher le repertoire courant\n");
        printf("6: c_alias: créer un alias pour les commandes systèmes\n");
        printf("7: c_leave: quitter la ligne de commandes\n");
      resetTextColor();
}