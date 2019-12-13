char UNAndHN[50];

char * RED[1]={"\033[0;31m"};
//strcpy(RED,");

char * BOLD_RED[1]={"\033[1;31m"};
//strcpy(BOLD_RED,);

char * GREEN[1]={"\033[0;32m"};
//strcpy(GREEN,);

char * BOLD_GREEN[1]={"\033[1;32m"};

char * BLUE[1] = {"\033[0;34m"};


void resetTextColor() {
   printf("\033[0m");
}


void changeTextColorTo(char * color) {
  printf("%s",color);
}
