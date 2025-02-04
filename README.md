## Overview
The **minishell** project is a comprehensive and challenging project that combines numerous concepts learned, such as process management, file descriptor handling, data structures, and memory management. In this project, we implement a simplified version of a shell, deepen our understanding of fundamental operating system functionalities.

This shell will utilize essential system calls like `fork()`, `execve()`, and `pipe()` to manage processes and facilitate inter-process communication. Handling file descriptors correctly is crucial, especially when working with pipes and redirections, ensuring that no file descriptor is left open inadvertently at the end of execution. The project also emphasizes memory management, requiring you to be vigilant against memory leaks, which can be particularly challenging in such a complex application.

### Functionality
The **minishell** project implements a range of functionalities that enable it to operate as a fully-fledged shell environment. Here’s how it works:

- **Tokenization**: The shell begins by breaking down user input into manageable tokens, making it easier to analyze commands and their arguments.

- **Syntax Analysis**: After tokenization, the shell checks for syntax errors, ensuring the command input follows the expected format and rules.

- **Abstract Syntax Tree (AST)**: The shell constructs an AST to represent the structure of commands and operations, providing a clear hierarchy for execution.

- **Command List Creation**: It compiles a list of commands to be executed based on the input and the parsed tokens, allowing for structured execution.

- **Variable Expansion**: The shell expands variables within the commands, substituting them with their corresponding values for correct execution.

- **Environment Variables**: It manages environment variables, enabling users to set and modify their shell environment effectively.

- **Built-in Commands**: The shell supports several built-in commands such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`, allowing users to interact with the shell environment directly.

- **Heredoc**: It implements heredoc functionality, enabling users to provide multi-line input until a specified delimiter is encountered.

- **Redirection**: The shell handles input and output redirection, allowing users to redirect command input/output using operators like `<`, `>`, `<<`, and `>>`.

- **Pipes**: It manages piping between commands, connecting the output of one command to the input of another, enabling complex command sequences.

- **Executable Command Verification**: The shell verifies whether a command is executable or accessible and determines if it is a built-in command.

- **Execution**: Finally, the shell executes the commands in the order determined by the AST, managing process creation and handling signals appropriately.

- **Signal Management**: The shell correctly handles signals like `CTRL+C` and `CTRL+D`, ensuring proper user interaction.

- **Execution Status**: It stores and displays the exit status of executed commands, allowing users to check the success or failure of their commands.

### Bonus Features
As an extension of the basic functionality, the **minishell** project includes bonus features that enhance the shell's capabilities by implementing logical operators `||` and `&&`. 

- **Logical OR (`||`)**: This operator allows users to chain commands such that the second command will only execute if the first command fails (returns a non-zero exit status). For example, in the command `command1 || command2`, `command2` will only run if `command1` does not succeed.

- **Logical AND (`&&`)**: Conversely, the logical AND operator ensures that the second command executes only if the first command is successful (returns a zero exit status). For instance, `command1 && command2` means `command2` will only execute if `command1` completes successfully.

The implementation of these operators required modifications to the command parsing and execution logic. By incorporating these operators, the **minishell** can now provide more powerful command execution capabilities, enabling users to create more complex command sequences directly from the shell prompt. This feature not only enhances usability but also aligns the **minishell** more closely with the behavior of traditional shells like bash.


### External Functions and Libraries
Your implementation will leverage various external functions, including:
- **Input Handling**: `readline`, `rl_clear_history`, `rl_replace_line`, `add_history`
- **Process Management**: `fork`, `wait`, `execve`, `pipe`
- **File Management**: `open`, `close`, `read`, `write`, `dup`, `dup2`
- **Memory Management**: `malloc`, `free`
- **Error Handling**: `strerror`, `perror`

### Usage
To run this minishell, execute a ```make```, following the command:

```bash
./minishell
```

For thorough memory leak checking, you can use the following command with Valgrind:
```
valgrind --leak-check=full --track-fds=yes --suppressions=readline.supp --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' ./minishell
```
