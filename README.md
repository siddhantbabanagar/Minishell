# Minishell
Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.

About the Project

The Mini Shell (msh) is a lightweight command-line interpreter that mimics basic functionalities of a Unix shell.

While building this, I focused on learning system-level programming concepts like:

Process creation (fork)
Program execution (exec)
Signal handling
Inter-process communication (pipes)
Job control

Features
Interactive Shell
Displays a custom prompt (msh>)
Supports user-defined prompt using PS1

Command Execution
Executes external Linux commands
Uses fork() + execvp()
Parent waits for child process

Built-in Commands
cd → Change directory
pwd → Show current directory
exit → Exit shell

Special Variables
echo $? → Exit status of last command
echo $$ → PID of shell
echo $SHELL → Path of shell executable

Signal Handling
Ctrl + C → Interrupt foreground process
Ctrl + Z → Stop process (SIGTSTP)

Background & Job Control
Run processes in background using &
jobs → List background jobs
fg → Bring job to foreground
bg → Resume stopped job in background

Pipes Support
Supports multiple pipes

Example:

ls -l | grep txt | wc -l
🛠️ Tech Stack
Language: C
Platform: Linux
Concepts Used:
System Calls
Process Management
Signals
Pipes (IPC)
File Descriptors

📂 Project Structure
mini-shell/
│
├── src/        # Source files
├── include/    # Header files
├── docs/       # Design notes
├── Makefile
└── README.md

▶️ How to Run
make
./msh
