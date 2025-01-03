# MUSHU README

## Motivation

This project is for me to learn modern C++ and use cmake.

## Project and Scope

The scope of the project will be to make a kernel that supports multiple processes and threads and CPUs. 
The kernel is a single user operating system with protection levels and no virtul memory.

### Shell

An inescapable kernel thread. This thread writes to VGA memory which displays stuff to the screen.

The shell has the following functionality:

1. Starting and killing programs
2. Printing information about running programs
3. Can read out-buffers of programs
3. Gives option about whether to cleanup out-buffers after programs exit (useful if programs run briefly and exits)

### Scheduler

Goal is a round robin with disabled timer interrupts whenever allocated PCBs < available CPUs.

### Systemcalls

1. Printf to process out buffer (can be read by shell thread)
2. Getchar that reads from the process IO buffers
3. Process EXEC and EXIT
4. Thread creation and destruction (when main thread exits, the program also exits)
5. MMAP/MUNMAP/BREAK

### Out of memory

Basically crash the kernel and print to screen no memory and turn off interrupts.

### Hardware Support

No embedded hardware support. 

### Filesystem

Basically no filesystem. The launch image contains programs that I can launch.

### Basic Library for MushuOS

1. Synchronization
2. Memory Allocator
3. Non-syscall library functionality copied from somewhere...