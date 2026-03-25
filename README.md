*This project has been created as part of the 42 curriculum by mchesnea.*

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

## Resources

### AI Usage
During the development of this project, Artificial Intelligence was used strictly as a learning assistant and debugging tool, in accordance with the school's guidelines. Specifically, AI helped with:
* Understanding complex concepts such as Abstract Syntax Trees (AST) and lexing/parsing logic.
* Explaining the nuances of specific C functions (e.g., `execve`, `dup2`, `tcsetattr`, `sigaction`).
* Troubleshooting segmentation faults, memory leaks, and tricky file descriptor edge cases.

*Note: All core logic, implementation, and code architecture were independently written.*

### Sources
Here are some of the key resources that helped me build this shell:
* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - The ultimate guide to understanding how bash behaves.
* [GNU C Library](https://www.gnu.org/software/libc/manual/html_node/index.html) - For documentation on signals, terminal I/O, and processes.
