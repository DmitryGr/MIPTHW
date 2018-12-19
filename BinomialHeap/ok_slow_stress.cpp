#include <bits/stdc++.h>
#include "binheap.h"
using namespace std;
bool cmp(pair<int, Binomial_heap<int>::Pointer> &a, pair<int, Binomial_heap<int>::Pointer> &b){
    return (a.first < b.first);
}
void ext(){
    cout << "WA";
    exit(0);
}
void ok(){
    cout << "OK" << endl;
}
void del(vector<pair<int, Binomial_heap<int>::Pointer> > &free_pointers, int ind){
    vector<pair<int, Binomial_heap<int>::Pointer> > new_pointers;
    for (int i=0; i < free_pointers.size(); i++) if (i!=ind) new_pointers.push_back(free_pointers[i]);
    free_pointers = new_pointers;
}
int main(){
    Binomial_heap<int> my_heap;
    multiset<int> checker;
    vector<pair<int, Binomial_heap<int>::Pointer> > free_pointers;
    vector<int> values;
    for (int i=0; i < 5000; i++) values.push_back(i);
    random_shuffle(values.begin(), values.end());
    int cur = 0;
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
        else if (R <= 8){
            if (checker.size()){
                int ind = rand() % checker.size();
                checker.erase(checker.find(free_pointers[ind].first));
                checker.insert(values[cur]);
                my_heap.change(free_pointers[ind].second, values[cur]);
                free_pointers[ind].first = values[cur];
                cur++;
            }
        }
        else{
            int ind = rand() % checker.size();
            checker.erase(checker.find(free_pointers[ind].first));
            my_heap.Delete(free_pointers[ind].second);
            del(free_pointers, ind);
        }
    }
    cout << "EVERYTHING IS OK; HEAP SIZE IS " << checker.size() << endl;

}
