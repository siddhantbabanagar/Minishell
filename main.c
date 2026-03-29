#include "main.h"

char prompt[20]="minishell$";
char current_command[30];
int last_status = 0;

int main(){
    system("clear");
    char input_string[40];
    scan_input(prompt, input_string);
}