#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv []) {

    int fdAC[2];
    int fdCA[2];
    int fdCB[2];
    fdAC[0] = atoi(argv[0]);
    fdCA[1] = atoi(argv[1]);
    fdCB[1] = atoi(argv[2]);
    int ans = 0;
    char c;
    int len2 = 0;
    vector <char> my_vec;
    while(read(fdAC[0], &c, sizeof(char))) {
        len2 ++;
        my_vec.push_back(c);
        if (c == '\n') {
            if (write(fdCA[1], &ans, sizeof(int)) == -1) {
                cout << "Error with writing in " << endl;
                return -1;
            }
            for (int i = 0; i < my_vec.size(); i++) {
                cout << my_vec[i];
            }
            my_vec.clear();
            len2 --;
            // cout << endl;
            if (write(fdCB[1], &len2, sizeof(int)) == -1) {
                cout << "Error with writing in child" << endl;
                return -1;
            }
            len2 = 0;
        }
        }


    return 0;
}