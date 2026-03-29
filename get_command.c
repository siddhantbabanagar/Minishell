#include "main.h"
char *get_command(char *input_string){
     static char command[20];
     //fetch only the first word from input_string
     
     int i=0;
     while(input_string[i]!='\0'){
          if(input_string[i]!=' '){
	       command[i]=input_string[i];
	  }
	  else{
	       break;
	  }
	  i++;
     }
     command[i]='\0';

     return command;
}
