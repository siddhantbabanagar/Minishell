#include "main.h"
extern char prompt[20];
extern int pid;
extern char current_command[40];

void signal_handler(int sig_num){
     if(sig_num==SIGINT){
	 //child is present or not
	 //printf("The pid=>%d\n",pid);
         if(pid==0){
            //if child is not present		 
	    printf("\n");    
            printf("%s ",prompt);
	    fflush(stdout);	
          }
     }	 
     else if(sig_num==SIGTSTP){
	 //child is not present    
         if(pid==0){
            printf("\n");
            printf("%s ",prompt);
	    fflush(stdout);
	 }
	 else{
            //store the stopped process info into linked list
	    Node *new = malloc(sizeof(Node));
            if (new == NULL)
                return;

            new->pid = pid;
            strcpy(new->command,current_command);   // replace with actual command

            new->link = head;   // point new node to current head
            head = new;         // update head

            pid = 0;            // reset foreground pid
	 } 
  }
}     
