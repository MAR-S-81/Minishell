*This project has been created as part of the 42 curriculum by mchesnea and erocha--.*

# Minishell

![Norminette](https://img.shields.io/badge/norminette-passing-success?style=flat-square) ![Score](https://img.shields.io/badge/score-100%2F100-brightgreen?style=flat-square) ![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)

![Image](https://github.com/user-attachments/assets/3fc6bb5d-6b61-45cf-b167-e838825e6c7e)

## Description

The goal of this project is to create a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors. This project is a great introduction to the inner workings of an operating system's command-line interface.

Key concepts learned include:
* **Lexing & Parsing**: Reading, tokenizing, and interpreting the user's command line inputs.
* **Process Creation**: Using `fork`, `execve`, and `waitpid` to execute commands.
* **Pipes & Redirections**: Handling data flow between commands and files (`|`, `<`, `>`, `<<`, `>>`).
* **Environment Variables**: Managing the environment and expanding `$VAR` and `$?`.
* **Signal Handling**: Properly managing keyboard interruptions like bash does.
* **Built-in Commands**: Implementing custom versions of core shell utilities.

**Built-ins implemented:**
* `echo` (with option `-n`)
* `cd` (with only a relative or absolute path)
* `pwd` (with no options)
* `export` (with no options)
* `unset` (with no options)
* `env` (with no options or arguments)
* `exit` (with no options)

## Instructions

### Compilation

You can compile the project using the provided Makefile.

```bash
make
```

## Usage

```bash
./minishell
```

### Signal & Shortcuts

| Key / Action | Effect |
| :--- | :--- |
| **`Ctrl + C`** | Displays a new prompt on a new line |
| **`Ctrl + D`** | Exits the shell (EOF) |
| **`Ctrl + \`** | Does nothing on the prompt (quits the current running process if any) |
