#include <bits/stdc++.h>
#include "fibheap.h"
using namespace std;
int main(){
    Fibonacci_heap<int> my_heap;
    int sz=0;
    for (int i=0; i < 5000000; i++){
        int R = rand() % 10;
        if (R <= 3){
            my_heap.insert(rand() % 10000000);
            sz++;
        }
        else if (R == 4){
            my_heap.is_empty();
        }
        else if (R <= 6){
            if (sz){
                my_heap.get_min();
            }
        }
        else{
            if (sz){
                my_heap.extract_min();
                sz--;
            }
        }
    }
    cout << "EVERYTHING IS OK; HEAP SIZE IS " << sz << endl;
    cout << "TIME OF 5 MILLIONS OPERATIONS IS " << (double) clock() / (double) CLOCKS_PER_SEC << " " << "SECONDS";
}
