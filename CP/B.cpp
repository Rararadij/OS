#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv []) {

    int fdCB[2];
    int fdAB[2];
    fdAB[0] = atoi(argv[1]);
    fdCB[0] = atoi(argv[0]);

    int incoming;
    int outcoming;
    while (true) {
        if (read(fdAB[0], &outcoming, sizeof(int)) == -1) {
            cout << "Error with reading in child" << endl;
            return -1;
        }
        if (outcoming == -1) break;
        if (read(fdCB[0], &incoming, sizeof(int)) == -1) {
            cout << "Error with reading in child" << endl;
            return -1;
        }
        cout << "Outcomming symbols: " << outcoming << endl;
        cout << "Incomming symbols: " << incoming << endl;
        cout << endl;
    }


    return 0;
}