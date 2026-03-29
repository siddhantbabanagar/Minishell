#include"main.h"
char *external_commands[200];
char *argv[30];
int pid=0;
int status;
extern int last_status;
extern char current_command[30];
int check_command_type(char *command);
void scan_input(char *prompt, char *input_string){
     //requirment
     //1.prompt
     
     signal(SIGINT,signal_handler);
     signal(SIGTSTP,signal_handler);

     extract_external_commands(external_commands);
     while(1){
         printf("%s ",prompt);
         scanf(" %[^\n]",input_string);

        //validate the input_string is PS1 or not
        if(strncmp(input_string,"PS1=",4)==0){
            //input_string is PS1
            //step 1=> validate space is present or not
            //use strstr or strchr
            //validate the 4th index
            //if space is present don't change the prompt
            if(strchr(input_string,' ')){
                printf("Command %s not found\n",input_string);
            }
            else{
             //if space is not present you want to change the prompt
             //use strcpy to copy from 4th index of prompt
                strcpy(prompt, (input_string+4));
            }
        }
        else{
            /*step 2 ==> to get only the first word of our input_string to compair and check what type of command it is.*/
            char *cmd=get_command(input_string);
            //printf("The first word is %s\n",cmd);

            /*step 3 ==> with the cmd we can comapre and check what type of command it is*/
	        int res=check_command_type(cmd);
            //printf("The command is %d\n",res);
            //check command type is built-in or not
            if(res==BUILTIN){
                execute_internal_commands(input_string);
            }
            //check command type is external or not
            else if(res==EXTERNAL){
		        int pipe_flag=0;    
		
                //step 1=>convert 1D array(input_string) to 2D array(argv)
                int len=strlen(input_string);

                char *temp=input_string;
                char *token;
                int i=0;
		        strcpy(current_command, input_string);
                token=strtok(temp," ");
    
                while(token){
                   argv[i++]=token;
                   token=strtok(NULL," ");
                }
                argv[i]=NULL;

		        //step2: validate pipe is present or not
                for(int i=0;argv[i]!=NULL;i++){
		            if(strcmp(argv[i],"|")==0){
		                pipe_flag=1;
			            break;
		            }
		        }
                
                //create child
                pid=fork();
                if(pid==0){
		            signal(SIGINT,SIG_DFL);
	                signal(SIGTSTP,SIG_DFL);	    
		            if(pipe_flag==1){
		                //implement_n_pipe(argv);
			            implement_n_pipe(argv);
		            }
	                else{
		                //to execute external commands
                        execute_external_commands(input_string);
		            }	    
                }
                else if(pid>0){
                    waitpid(pid,&status,WUNTRACED);
                    if (WIFEXITED(status)) {
                        last_status = WEXITSTATUS(status);   // normal exit
                    }
                    else if (WIFSIGNALED(status)) {
                        last_status = 128 + WTERMSIG(status); // killed by signal
                    }
		            pid=0;
                }
            }
	        else if(strcmp(input_string,"jobs")==0){
	            //implement jobs
		        print_list();
	        }
	        else if(strcmp(input_string,"fg")==0){
	            //implement fg
		        Node *temp = delete_at_first();
                if (temp == NULL) {
                    printf("fg: no job\n");
                    return;
                }

                pid = temp->pid;

                kill(pid, SIGCONT);                  // continue job
                waitpid(pid, NULL, WUNTRACED);       // wait in foreground

                free(temp);
                pid = 0;
	        }
	        else if(strcmp(input_string,"bg")==0){
                 //implement bg
		        Node *temp = delete_at_first();
                if (temp == NULL) {
                    printf("bg: no job\n");
                    return;
                }

                kill(temp->pid, SIGCONT);   // resume in background

                free(temp);
            }
        }
    }
}
void extract_external_commands(char **external_commands){
    char ch;
    char buf[50]={'\0'};
    int i=0,j=0;
    //step1==>open the external_commands.txt in read mode
    int fd=open("external_command.txt",O_RDONLY);
    if(fd==-1){
        perror("open:");
        exit(1);
    }
    //step2==>read the commands one by one
    while(read(fd,&ch,1)>0){
        if(ch!='\n'){
            buf[i++]=ch;
        }
        else{
            //step3==>allocate the memory dynamically
            external_commands[j] = calloc(strlen(buf) + 1,sizeof(char));

            //step4==>store the command into 2D array
            strcpy(external_commands[j++], buf);
            external_commands[j]=NULL;

            memset(buf,'\0',50);
            i=0;
        }
    }
    close(fd);
}
int check_command_type(char *command){
    /*builtin commands*/
	char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

    //step1=>check the command is builtin or not
    for(int i=0;builtins[i]!=NULL;i++){
        if(strcmp(command,builtins[i])==0){
            return BUILTIN;
        }
    }
    //step2=> check the command is external or not
    for(int i=0;external_commands[i]!=NULL;i++){
        if(strcmp(command,external_commands[i])==0){
            return EXTERNAL;
        }
    }
    //step3=>check for if the command is not BUILTIN or not EXTERNAL then return NO_COMMAND
    return NO_COMMAND;                   
}
