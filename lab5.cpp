#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

//global variables
int n;
char readbuffer[100];
char msg[100];

//parent function
void do_parent(char msg[], int fd[])
{
    close(fd[0]);
    write(fd[1], msg, sizeof(msg));
    close(fd[1]);
    wait(NULL);
    exit(0);
}

//child function, will recursively subtract n
void do_fork(char msg[], int fd[])
{
    //cout << n << endl;
    pid_t pid;
    pid = fork();
    if (pid == 0 && n > 0)
    {
        n--;
        do_fork(msg, fd);
    }
    if (n == 0 && pid == 0)
    {
        close(fd[1]);
        read(fd[0], readbuffer, 100);
        cout << readbuffer << endl;
        exit(0);
    }
    do_parent(msg, fd);
}

int main(){
    //Accept integer n
    cout << "Input number 1 <= n <= 1000: ";
    cin >> n;
    cin.clear();
    cin.ignore(10000,'\n');
    //Accept a simple message
    cout << "Input message less than or equal to 100 bytes: ";
    cin >> msg;
    cin.clear();
    cin.ignore(10000, '\n');
    //Stores the value n = n -1;
    n = n - 1;
    
    //All those steps are done once.
    int fd[2];
    pipe(fd);
    //Forks a child, writes the message to the pipe, does wait(NULL), does exit(0)
    do_fork(msg, fd);
    
    return 0;
}


