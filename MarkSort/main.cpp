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
void marksort(int[], int);
//Execution begins HERE
int main(int argc, char** argv){
    //declare variables
    srand(static_cast<int>(time(0)));
    const int SIZE = 100;
    int a_Num[SIZE];
    //fill the array with 2-digit random numbers
    fillAR(a_Num, SIZE);
    //print the arrat
    printAR(a_Num, SIZE, 10);
    //sort the array
    marksort(a_Num, SIZE);
    //print the array
    printAR(a_Num, SIZE, 10);
    //Execution ends HERE
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
        cout << num[i] << " ";
        if(i % perline == (perline - 1)) cout << endl;
    }
    cout << endl;
}
void marksort(int num[], int n){
    for(int i = 0; i < n - 1; i++){
        int pos = i;
        for(int ctr = pos+1; ctr < n; ctr++ ){
            if(num[pos] > num[ctr]){
                num[pos] = num[pos]^num[ctr];
                num[ctr] = num[pos]^num[ctr];
                num[pos] = num[pos]^num[ctr];
            }
        }
    }
}