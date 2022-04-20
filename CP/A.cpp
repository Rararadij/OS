#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv []) {
    int fdAC[2];
    int fdCA[2];
    int fdAB[2];
    fdAC[1] = atoi(argv[1]);
    fdCA[0] = atoi(argv[0]);
    fdAB[1] = atoi(argv[2]);
    char c;
    int res;
    int len = 0;
    while ((c = getchar()) != EOF) {
        len ++;
        if (write(fdAC[1], &c, sizeof(char)) == -1) {
            cout << "Error with writing in parent" << endl;
            return -1;
        }
        if (c == '\n') {
            if (read(fdCA[0], &res, sizeof(int)) == -1) {
                cout << "Error with reading in " << endl;
                return -1;
            }
            len --;
            if (write(fdAB[1], &len, sizeof(int)) == -1) {
                cout << "Error with writing in parent" << endl;
                return -1;
            }
            len = 0;
        }
    }
    if (c == EOF) {
        int ex = -1;
        if (write(fdAB[1], &ex, sizeof(int)) == -1) {
            cout << "Error with writing in parent" << endl;
            return -1;
        }
    }


    return 0;
}