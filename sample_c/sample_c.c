#define IO_ADDR 0xFFFFFFFF

void print_s(char* s, int len){
    for(int i = 0; i < len; i++){
        __asm__ volatile (
            "sb %1, 0(%0)"
            :
            : "r" (IO_ADDR), "r" (s[i])
            :
        );
    }
}
void print_d(int d){
    __asm__ volatile (
        "sw %1, 0(%0)"
        :
        : "r" (IO_ADDR), "r" (d)
        :
    );
}

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

    int y[3][3] = {
        {2, 3, 4},
        {5, 6, 7},
        {8, 9, 10}
    };

    int res[3][3] = {0};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            res[i][j] = x[i][j] + y[i][j];
        }
    }

    print_s("x:\n", 3);
    print_matrix(x);
    print_s("y:\n", 3);
    print_matrix(y);
    print_s("x+y:\n", 5);
    print_matrix(res);

    return 0;
}