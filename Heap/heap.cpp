template<typename Key>
Key Heap<Key>::get(int index) const{
    return (*arr.get(index)).key;
}

template<typename Key>
bool Heap<Key>::is_empty() const{
    return (!arr.length());
}

template<typename Key>
void Heap<Key>::Swap(int a, int b){
    if (a==b) return;
    (*arr.get(a)).index = b;
    (*arr.get(b)).index = a;
    arr.Swap(a, b);
}

template<typename Key>
void Heap<Key>::SiftUp(int &this_index){
    while (this_index != 0 && get(this_index) < get((this_index-1)/2)){
        Swap(this_index, (this_index-1)/2);
        this_index=(this_index-1)/2;
    }
}

template<typename Key>
typename
Heap<Key>::Pointer Heap<Key>::insert(Key key) {
    int len = arr.length();
    Element* new_element = new Element(key, len);
    arr.add(new_element);
    int this_index = len;
    SiftUp(this_index);
    Pointer ret(new_element, this);
    return ret;
}

template<typename Key>
Key Heap<Key>::get_min() const{
    int len = arr.length();
    if (len == 0) throw std::runtime_error("request out of range");
    return (*arr.get(0)).key;
}

template<typename Key>
void Heap<Key>::SiftDown(int start){
    int index = start, len = arr.length();
    while (true){
        if (2*index+1 >= len) break;
        if (2*index+2 >= len){
            if (get(index) < get(2*index+1)) break;
            Swap(index, 2*index+1);
            index = 2*index+1;
        }
        else{
            int best_index = 2*index+1;
            if (get(2*index+2) < get(2*index+1)) best_index = 2*index+2;
            if (get(index) < get(best_index)) break;
            Swap(index, best_index);
            index = best_index;
        }
    }
}

template<typename Key>
Key Heap<Key>::extract_min(){
    int len = arr.length();
    if (len == 0) throw std::runtime_error("request out of range");
    Key value = get(0);
    Swap(0, len-1);
    arr.del();
    SiftDown(0);
    return value;
}

template<typename Key>
void Heap<Key>::change(Pointer &ptr, Key key){
    if (ptr.my_heap != this) throw std::runtime_error("invalid pointer");
    Element* this_element = ptr.my_element;
    int index = this_element->index;
    this_element->key = key;
    SiftDown(index);
    SiftUp(index);
}

template<typename Key>
int Heap<Key>::length() const{
    return arr.length();
}

template<typename Key>
void Heap<Key>::Delete(Pointer &ptr){
    if (ptr.my_heap != this) throw std::runtime_error("invalid pointer");
    int len = this->length(), ind = ptr.my_element->index;
    if (!len) throw std::runtime_error("wrong request");
    Swap(ptr.my_element->index, len-1);
    arr.del();
    if (ind == len-1) return;
    SiftDown(ind);
    SiftUp(ind);
}

