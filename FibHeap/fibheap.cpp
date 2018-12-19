template<typename Key>
bool Fibonacci_heap<Key>::is_empty() const{
    return (minimum == nullptr);
}

template<typename Key>
Key Fibonacci_heap<Key>::get_min() const{
    if (minimum == nullptr) throw std::out_of_range("no elements in heap");
    return minimum->key;
}

template<typename Key>
void Fibonacci_heap<Key>::add_righter(Element* cur, Element* new_element){
    Element* old_right_brother = cur->right_brother;
    cur->right_brother = new_element;
    new_element->right_brother = old_right_brother;
    new_element->left_brother = cur;
    old_right_brother->left_brother = new_element;
}

template<typename Key>
void Fibonacci_heap<Key>::add_into_list(Element* new_element){
    add_righter(minimum, new_element);
    if (new_element->key < minimum->key) minimum = new_element;
}

template<typename Key>
void Fibonacci_heap<Key>::add_into_heap(Element* new_element){
    if (minimum == nullptr){
        minimum = new_element;
        minimum->left_brother = minimum;
        minimum->right_brother = minimum;
    }
    else{
        add_into_list(new_element);
    }
}

template<typename Key>
typename
Fibonacci_heap<Key>::Pointer Fibonacci_heap<Key>::insert(Key key){
    Element* new_element = new Element(key);
    add_into_heap(new_element);
    return {new_element};
}

template<typename Key>
typename
Fibonacci_heap<Key>::Element* Fibonacci_heap<Key>::delete_cycle(){
    Element* right_chain_edge = minimum->left_brother;
    right_chain_edge->right_brother = nullptr;
    minimum->left_brother = nullptr;
    return right_chain_edge;
}

template<typename Key>
void Fibonacci_heap<Key>::connect(Element* left_edge, Element* other_chain_right_edge){
    left_edge->left_brother = other_chain_right_edge;
    other_chain_right_edge->right_brother = left_edge;
}

template<typename Key>
void Fibonacci_heap<Key>::merge(Fibonacci_heap<Key> &otherHeap){
    if (otherHeap.is_empty()) return;
    if (is_empty()){
        minimum = otherHeap.minimum;
        otherHeap.minimum = nullptr;
        return;
    }
    Element* our_right_edge = delete_cycle();
    Element* added_right_edge = otherHeap.delete_cycle();
    connect(otherHeap.minimum, our_right_edge);
    connect(minimum, added_right_edge);
    if (otherHeap.minimum->key < minimum->key) minimum = otherHeap.minimum;
    otherHeap.minimum = nullptr;
}

template<typename Key>
void Fibonacci_heap<Key>::cascading_cut(Element* element){
    while (element != nullptr){
        if (!element->mark){
            element->mark = true;
            break;
        }
        Element* father = element->father;
        cut(element);
        element = father;
    }
}

template<typename Key>
void Fibonacci_heap<Key>::delete_from_list(Element* element){
    Element* right_brother = element->right_brother;
    Element* left_brother = element->left_brother;
    left_brother->right_brother = right_brother;
    right_brother->left_brother = left_brother;
}

template<typename Key>
void Fibonacci_heap<Key>::cut(Element *element){
    if (element->father == nullptr) return;
    element->father->degree--;
    if (element->right_brother == element){
        element->father->child = nullptr;
    }
    else{
        Element* some_child = element->right_brother;
        delete_from_list(element);
        element->father->child = some_child;
    }
    element->left_brother = nullptr, element->right_brother = nullptr;
    element->father = nullptr;
    element->mark = false;
    add_into_list(element);
}

template<typename Key>
void Fibonacci_heap<Key>::decrease_key(Pointer ptr, Key key){
    Element* element = ptr.my_element;
    element->key = key;
    if (element->father == nullptr){
        if (element->key < minimum->key) minimum = element;
        return;
    }
    if (element->key > element->father->key) return;
    Element* father = element->father;
    cut(element);
    cascading_cut(father);
}

template<typename Key>
void Fibonacci_heap<Key>::determine_minimum(){
    if (minimum == nullptr) return;
    Key value = minimum->key;
    Element* last = minimum->right_brother;
    Element* minimal = minimum;
    while (last != minimum){
        if (last->key < value){
            value = last->key;
            minimal = last;
        }
        last = last->right_brother;
    }
    minimum = minimal;
}

template<typename Key>
void Fibonacci_heap<Key>::add_into_cell(Array<Element*> &cells, Element* last){
    int degree = last->degree;
    while (cells.length() <= degree) cells.add(nullptr);
    if (cells.get(degree) == nullptr){
        cells.change(degree, last);
        return;
    }
    Element* cur = cells.get(degree);
    if (cur->key > last->key) std::swap(cur, last);
    cur->degree++;
    last->father = cur;
    if (cur->child == nullptr){
        cur->child = last;
        last->right_brother = last, last->left_brother = last;
    }
    else add_righter(cur->child, last);
    cells.change(degree, nullptr);
    add_into_cell(cells, cur);
}

template<typename Key>
void Fibonacci_heap<Key>::consolidate(){
    if (minimum==nullptr) return;
    Array<Element*> cells;
    delete_cycle();
    Element* last = minimum;
    while (last != nullptr){
        Element* nxt = last->right_brother;
        last->left_brother = nullptr, last->right_brother = nullptr;
        add_into_cell(cells, last);
        last = nxt;
    }
    minimum = nullptr;
    for (int i=0; i < cells.length(); i++){
        if (cells.get(i) == nullptr) continue;
        add_into_heap(cells.get(i));
    }
}

template<typename Key>
Key Fibonacci_heap<Key>::extract_min(){
    if (minimum == nullptr) throw std::runtime_error("no elements in heap");
    Key return_value = minimum->key;
    Fibonacci_heap<Key> children;
    if (minimum->child != nullptr){
        Element* start = minimum->child;
        start->father = nullptr;
        Element* last = start->right_brother;
        while (last != start){
            last->father = nullptr;
            last = last->right_brother;
        }
        children.minimum = minimum->child;
        children.determine_minimum();
    }
    minimum->child = nullptr;
    if (minimum->right_brother == minimum){
        minimum = nullptr;
    }
    else{
        Element* R = minimum->right_brother;
        delete_from_list(minimum);
        minimum = R;
    }
    determine_minimum();
    merge(children);
    consolidate();
    return return_value;
}

