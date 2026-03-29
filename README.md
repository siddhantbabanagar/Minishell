# Minishell
## What is Minishell?

A MiniShell (msh) is a simplified version of a Linux command-line shell (like Bash).
It is a program written in C that:
-Takes commands from the user
-Executes them using system calls
-Displays the output

## Why Do We Use MiniShell?

We don’t build MiniShell for daily use — we build it to learn how Linux actually works internally.

## Features

- Custom shell prompt (PS1)
- Execute external commands
- Built-in commands (cd, pwd, exit)
- Background process support (&)
- Job control (fg, bg, jobs)
- Pipe support (ls | wc)

## Tech Stack

- C Programming
- Linux System Calls
- Process Management
- Signal Handling
- Pipes (IPC)

## How the Code Works?
        ┌──────────────┐
        │  User Input  │
        └──────┬───────┘
               ↓
        ┌──────────────┐
        │   Parsing    │
        └──────┬───────┘
               ↓
     ┌────────────────────┐
     │ Built-in Command? │
     └──────┬───────┬─────┘
            │YES    │NO
            ↓       ↓
   ┌────────────┐   ┌────────────┐
   │ Execute    │   │   fork()   │
   │ Directly   │   └────┬───────┘
   └────────────┘        ↓
                   ┌────────────┐
                   │  Child     │
                   │ execvp()   │
                   └────┬───────┘
                        ↓
                   ┌────────────┐
                   │  Parent    │
                   │  wait()    │
                   └────┬───────┘
                        ↓
                 ┌──────────────┐
                 │ Show Prompt  │
                 └──────────────┘

## Key Learnings

- Learned how fork() and exec() work together
- Understood signal handling (Ctrl+C, Ctrl+Z)
- Implemented job control and background processes

## Challenges

- Managing multiple processes with pipes
- Handling signals without crashing the shell
- Parsing user input correctly

## Future Improvements

- Command history
- Auto-complete
- Better UI

## How to Run

```bash
make
./msh

