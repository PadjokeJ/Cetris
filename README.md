# Cetris  

Terminal tetris coded entirely in C  

## Building

The code is cross platform across windows and unix based machines, however it needs to be compiled differently

### Windows

To build on Windows, open the Command Prompt, navigate to the Cetris folder, and then enter this command  

```gcc tetris.c -o tetris.exe```

and then, to run the compiled version do  

```tetris.exe```

### Linux

To build on Linux, you have to have the ncurses library installed.  
Once it is installed, open the terminal, navigate to the Cetris folder, and then enter the following command  

```gcc tetris.c -o tetris -lncurses```

and then, to run it in the terminal, enter  

```./tetris```
