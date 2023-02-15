


## ℹ️ About the Project
---

we have implemented a shell in c programming language on linux which creates a child process and invoking commands are written and executed interactively and in batch. Also Accept, analyze, forks, run, then wait are how ssh works.

---

<details>
  <summary><b>Compilation instructions</b></summary>
  
  ### Step-by-step instructions for setting up salease
  
  1. Run the program using  **gcc** 
  2. the previous step would create a exutable file **./testoutputK** 
  3. now run the executable to get into myshell
  3. by default it would an interactive mode; now enter any linux command to run.
  4. For batch mode use the batch.txt file as **./testoutput batch.txt**


</details>

---

## sample test output 

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



## Screenshots

