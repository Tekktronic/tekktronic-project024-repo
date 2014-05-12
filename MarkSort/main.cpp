/* 
 * NAME: Ezra Guinmpang
 * DATE: May 12, 2014, 7:58 AM
 * PURPOSE: Create a sorting algorithm: Marksort 
 */

//Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//Global variables and constants

//Function prototypes
void fillAR(int[], int);
void printAR(int[], int, int);
void swap1(int &, int &);
void swap2(int &, int &);
void listSM(int[], int &, int &);
void marksort(int[], int);
//Execution begins HERE
int main(int argc, char** argv){
    srand(static_cast<int>(time(0)));
    const int SIZE = 100;
    int a_Num[SIZE];
    fillAR(a_Num, SIZE);
    printAR(a_Num, SIZE, 10);
    
    return 0;
}
//Function definitions
void fillAR(int num[], int n){
    for(int i = 0; i < n; i++){
        num[i] = (rand() % 90) + 10;
    }
}
void printAR(int num[], int n, int perline){
    for(int i = 0; i < n; i++){
        cout << endl;
        cout << num[i] << " ";
        if(i % perline == (perline - 1)) cout << endl;
    }
}
void swap1(int &num1, int &num2){
    int tmp = num1;
    num1 = num2;
    num2 = tmp;
}
void swap2(int &num1, int &num2){
    int tmp = num1^num1;
    num1 = num1^num2;
    num2 = tmp;
}
void listSM(int num[], int &n, int &pos){
    for(int i = pos+1; i < n; i++){
        //if(num[pos] > num[i]) swap1(num[pos], num[i]);
        if(num[pos] > num[i]) swap2(num[pos], num[i]);
    }
}
void marksort(int num[], int n){
    for(int i = 0; i < n; i++){
        listSM(num, i, n);
    }
}