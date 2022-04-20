#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;

int main() {

    int fdAC[2];
    int fdCA[2];
    int fdCB[2];
    int fdAB[2];
    if (pipe(fdAC) < 0 || pipe(fdCA) < 0 || pipe(fdCB) < 0 || pipe(fdAB) < 0) {
        cout << "Error with pipe" << endl;
        exit(-1);
    }

    int pid = fork();

    if (pid < 0) {
        cout << "Error with fork" << endl;
        exit(-1);
    } else if (pid == 0) { // Child process (C)
        execl("C", to_string(fdAC[0]).c_str(), 
                    to_string(fdCA[1]).c_str(),
                    to_string(fdCB[1]).c_str(), 
                    NULL);


    } else { 

        int pid2 = fork();

        if (pid2 < 0) {
            cout << "Error eith fork" << endl;
            exit(-1);
        }
        else if (pid2 == 0) { // Child process (B)
            execl("B", to_string(fdCB[0]).c_str(),
                        to_string(fdAB[0]).c_str(), NULL);

        } else { // Parent process (A)
            execl("A", to_string(fdCA[0]).c_str(), 
                        to_string(fdAC[1]).c_str(),  
                        to_string(fdAB[1]).c_str(), NULL);
        }
    }


    return 0;
}