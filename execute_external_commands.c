#include"main.h"
extern char *argv[30];
void execute_external_commands(char *input_string){
    int res=execvp(argv[0],argv);

    if(res==-1){
       perror("execvp");
       exit(1);
    }
}
