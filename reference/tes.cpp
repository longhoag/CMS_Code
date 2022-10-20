#include<iostream>

int main() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(i > 4) {
                cout << "i loop" << endl;
                if(j > 3) {
                    cout << "j loop" << endl;
                    break;
                }
            }
        }
    }
}