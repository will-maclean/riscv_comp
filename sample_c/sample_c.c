#include "syscall.h"

void print_matrix(int m[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            print_d(m[i][j]);
            if(j < 2){
                print_s(", ", 2);
            }
        }
        print_s("\n", 1);
    }
}

int main() {
    int x[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    print_matrix(x);

    return 0;
}