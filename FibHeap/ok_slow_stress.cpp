#include <bits/stdc++.h>
#include "fibheap.h"
using namespace std;
bool cmp(pair<int, Fibonacci_heap<int>::Pointer> &a, pair<int, Fibonacci_heap<int>::Pointer> &b){
    return (a.first < b.first);
}
void ext(){
    cout << "WA";
    exit(0);
}
void ok(){
    cout << "OK" << endl;
}
void del(vector<pair<int, Fibonacci_heap<int>::Pointer> > &free_pointers, int ind){
    vector<pair<int, Fibonacci_heap<int>::Pointer> > new_pointers;
    for (int i=0; i < free_pointers.size(); i++) if (i!=ind) new_pointers.push_back(free_pointers[i]);
    free_pointers = new_pointers;
}
int main(){
    Fibonacci_heap<int> my_heap;
    multiset<int> checker;
    vector<pair<int, Fibonacci_heap<int>::Pointer> > free_pointers;
    vector<int> values;
    for (int i=0; i < 5000; i++) values.push_back(i);
    random_shuffle(values.begin(), values.end());
    int cur = 0, new_decreasing = -1;
    for (int i=0; i < 5000; i++){
        sort(free_pointers.begin(), free_pointers.end(), cmp);
        int R = rand() % 10;
        if (R <= 3){
            free_pointers.push_back({values[cur], my_heap.insert(values[cur])});
            checker.insert(values[cur]);
            cur++;
        }
        else if (R == 4){
            bool res = my_heap.is_empty(), real = (!checker.size());
            if (res == real) ok();
            else ext();
        }
        else if (R == 5){
            if (checker.size()){
                int res = my_heap.get_min(), real = (*checker.begin());
                if (res == real) ok();
                else ext();
            }
        }
        else if (R == 6){
            if (checker.size()){
                int res = my_heap.extract_min(), real = (*checker.begin());
                checker.erase(checker.begin());
                del(free_pointers, 0);
            }
        }
        else{
            if (checker.size()){
                int ind = rand() % checker.size();
                checker.erase(checker.find(free_pointers[ind].first));
                checker.insert(new_decreasing);
                my_heap.decrease_key(free_pointers[ind].second, new_decreasing);
                free_pointers[ind].first = new_decreasing;
                new_decreasing--;
            }
        }
    }
    cout << "EVERYTHING IS OK; HEAP SIZE IS " << checker.size() << endl;

}
