const int COMMANDS_ARRAY_LENGTH =7;
const char * commands[]= {"c_ls","c_cd","c_alias","c_pwd","c_set","c_exec_cmd_seq","c_leave"};

typedef struct ENV_VARS ENV_VARS;
struct ENV_VARS {
     char  HOME[52];
     char PATH[52];
};

ENV_VARS ENV_VARIABLES = {"",""};
//char default_path[20]={""};

char * default_path;

 char UNAndHN[50];

char * RED[1]={"\033[0;31m"};
//strcpy(RED,");

char * BOLD_RED[1]={"\033[1;31m"};
//strcpy(BOLD_RED,);

char * GREEN[1]={"\033[0;32m"};
//strcpy(GREEN,);

char * BOLD_GREEN[1]={"\033[1;32m"};

char * BLUE[1] = {"\033[0;34m"};

//strcpy(BOLD_GREEN,"");


