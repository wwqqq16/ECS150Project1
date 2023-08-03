# TimeoutExecutor

TimeoutExecutor is a collection of C programs designed to optimize command execution and manage processes effectively. This suite consists of four programs:

1. `timeout.c`

   The `timeout.c` program implements a reliable timeout mechanism for executing other commands. By providing a timeout value (in seconds) and a command with its arguments as input, this program ensures that the command completes its execution within the specified time frame. If the command fails to finish within the given timeout, `timeout.c` will gracefully terminate it, preventing commands from running indefinitely.

2. `sigcatch.c`

   The `sigcatch.c` program serves the purpose of printing the Process ID (PID) of the current process to the console. Though it does not have direct interactions with other programs, it can be utilized in conjunction with them to acquire the PID of a specific process when needed.

3. `linked.c`

   The `linked.c` program plays a crucial role in verifying file relationships on Unix-like systems. It efficiently checks if two specified files are linked, either through hard links or symbolic links, by comparing their inode numbers. This utility ensures that you can avoid duplicate files and maintain an organized file structure. While it does not directly interact with other programs, it can be used as a powerful standalone utility.

4. `timeoutex.c`

   The `timeoutex.c` program is a valuable tool for locating the full path of a given command in the system's `$PATH` environment variable. By returning the full path when the command is found, or the original command name when it is not, `timeoutex.c` eliminates ambiguity when specifying commands without an absolute path. This feature can be utilized in conjunction with `timeout.c`, ensuring that the correct executable is invoked during command execution.

By combining the functionalities of these four programs, you can create a comprehensive utility that:

- Executes commands with a specific timeout, guaranteeing completion within the designated time frame.
- Provides the PID of the current process or any other desired process when combined with `sigcatch.c`.
- Verifies file relationships and prevents duplication with the help of `linked.c`.
- Facilitates precise command execution by locating the full path with `timeoutex.c`, thus avoiding any confusion arising from partial command specifications.

It is a powerful set of tools at your disposal, enabling to enhance command execution and manage processes with utmost efficiency on Unix-like systems.
