# Minishell
Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.

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

