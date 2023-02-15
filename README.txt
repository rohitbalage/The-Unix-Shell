# group members

Group9

1: Rohit Balage (2831115)



# project description

we have implemented a shell in c programming language on linux which creates a child process and invoking commands are written and executed interactively and in batch. Also Accept, analyze, forks, run, then wait are how ssh works.

## Compilation instructions

```
$ make
```

## Execution

```
$ ./myShell
```

## sample test run

rohit@rrb:~/Downloads/group9_p1$ gcc myShell.c -o testoutput
rohit@rrb:~/Downloads/group9_p1$ ./testoutput

PS1=group_p1myShell> touch sample.txt
myShell> ./myShell sample.txt
myShell: : No such file or directory
myShell> ./testoutput sample.txt

PS1=group_p1Received Script. Opening sample.txt
File Opened. Parsing. Parsed commands displayed first.
touch FileCreatedWithBatchMode.txt
myShell> touch batch.txt
myShell> ./myShell batch.txt
myShell: : No such file or directory
myShell> ./testoutput batch.txt

PS1=group_p1Received Script. Opening batch.txt
File Opened. Parsing. Parsed commands displayed first.
touch fileWithBatch.txt
myShell> exit

