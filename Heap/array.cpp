template<typename Key>
Array<Key>::Array(){
    arr = new Key[12];
    length_of_array = 12;
    free_ind = 0;
}

template<typename Key>
Array<Key>::~Array(){
    delete[] arr;
}

template<typename Key>
void Array<Key>::add(Key element){
    if (free_ind == length_of_array){
        Key* new_arr = new Key[2*length_of_array];
        for (int i=0; i < length_of_array; i++) new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
        length_of_array = length_of_array*2;
    }
    arr[free_ind] = element;
    ++free_ind;
}

template<typename Key>
void Array<Key>::del(){
    if (free_ind == 0) throw std::runtime_error("deletion from empty list");
    else free_ind--;
}
using namespace std;
template<typename Key>
Key Array<Key>::get(int index) const{
    if (index < 0 || index >= free_ind) throw std::runtime_error("request out of range");
    return arr[index];
}

template<typename Key>
void Array<Key>::change(int index, Key element){
    if (index < 0 || index >= free_ind) throw std::runtime_error("request out of range");
    arr[index] = element;
}

template<typename Key>
int Array<Key>::length() const{
    return free_ind;
}

template<typename Key>
void Array<Key>::Swap(int fi, int si){
    if (fi >= si){
        std::swap(fi, si);
    }
    if (fi < 0 || si >= free_ind) throw std::runtime_error("request out of range");
    std::swap(arr[fi], arr[si]);
}
