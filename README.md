# 🐚 42sh – Unix Shell (tcsh clone)

> A functional command-line shell written in C, inspired by `tcsh`, developed as part of the EPITECH curriculum.

---

## 🚀 Project Overview

**42sh** is a custom shell implementation in C that replicates core functionalities of Unix shells like `tcsh`.  
It supports command parsing, execution, redirections, pipelines, environment variables, and built-in commands — all built from scratch without using system shell utilities.

---

## 🛠️ Features

- Prompt and interactive input
- Command parsing with quotes and separators
- Redirections: `>`, `>>`, `<`
- Pipes: `ls | grep foo`
- Environment variable handling (`env`, `set`, `unset`)
- Built-in commands: `cd`, `exit`, `echo`, etc.
- Signal handling (`Ctrl+C`, `Ctrl+D`)
- Error handling and memory management

---

## 💡 Technical Details

- Language: **C**
- System calls: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, etc.
- String parsing and tokenization handled manually
- Custom implementation of environment and built-in command system
- Compliant with POSIX specifications where possible

---

## 📁 Project Structure

```
42sh/
├── src/         # Core source code (parsing, exec, env, builtins)
├── include/     # Header files
├── tests/       # Unit and functional tests
├── Makefile     # Build system
└── README.md    # Project description
```

---

## 🧠 Learning Goals

This project was a deep dive into:

- Unix process and signal management
- Shell architecture and job control
- Low-level I/O and file descriptor manipulation
- Manual memory management in C
- Robust error handling and modular code design

---

## ▶️ Getting Started

```bash
# Clone the repository
git clone https://github.com/yourusername/42sh.git
cd 42sh

# Build the shell
make

# Run it
./42sh
