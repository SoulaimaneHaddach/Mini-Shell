# Mini-Shell

A small Unix shell written in C from scratch, built to understand how Unix shells work internally.

## Features

- Execute external commands through `$PATH`
- Command arguments
- Built-in commands:
  - `cd`
  - `pwd`
  - `exit`
- Environment variable expansion:
  - `$HOME`
  - `$USER`
  - `$PATH`
- Output redirection:
  - `>`
- Supports commands such as:
  - `ls`
  - `cat`
  - `echo`

## Project Structure

```text
Mini-Shell/
├── Makefile
├── README.md
├── include/
│   └── shell.h
└── src/
    ├── main.c
    ├── parser.c
    ├── builtins.c
    ├── utils.c
    └── redirections.c
```

## Built With

- C
- GCC
- Linux / WSL
- Makefile
- Unix system calls

Built from scratch as a learning project to understand processes, `fork()`, `execve()`, file descriptors, environment variables, and shell behavior.
