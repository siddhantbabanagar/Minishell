#include "main.h"

extern int status;

void execute_internal_commands(char *input_string){
    /*printf("Hii I am from the internal_command file\n");              
    printf("The input string is %s\n",input_string);*/

    //step1=>compare and check your input_string is exit or not
    if(strcmp(input_string,"exit")==0){
        exit(1);
    }
    //step2=>compare and check your input_string is pwd or not
    if(strcmp(input_string,"pwd")==0){
        char str[100];
        getcwd(str,100);
        printf("%s\n",str);
    }
    //step3=>compare and check your input_string is cd or not
    if(strncmp(input_string,"cd",2)==0){
        chdir(&input_string[3]);
    }
    //step4=>compare and check your input_string is echo or not
    if(strncmp(input_string,"echo",4)==0){
        //step4.1=>compare and check your input_string is echo $SHELL or not 
        if(strncmp(&input_string[5],"$SHELL",6)==0){
            printf("%s \n",getenv("SHELL"));
        }
        //step4.2=>compare and check your input_string is echo $? or not 
        else if(strncmp(&input_string[5],"$?",2)==0){
            printf("%d\n", last_status);
        }
        //step4.2=>compare and check your input_string is echo $$ or not 
        else if(strncmp(&input_string[5],"$$",2)==0){
            printf("%d \n",getpid());
        }
        
    }
}
