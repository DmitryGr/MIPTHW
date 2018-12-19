template<typename Key>
bool Binomial_heap<Key>::is_empty() const{
    return (head == nullptr);
}

template<typename Key>
typename
Binomial_heap<Key>::Element* Binomial_heap<Key>::Union(Element* a, Element* b){
    if (a->key > b->key){
        a->brother = b->brother;
        b->brother = a;
        std::swap(a, b);
    }
    Element* nxt = b->brother;
    a->brother = nxt;
    b->brother = a->child;
    a->degree++;
    b->father = a;
    a->child=b;
    return a;
}

template<typename Key>
void Binomial_heap<Key>::merge(Binomial_heap<Key> &otherHeap){
    Element* first = head;
    Element* second = otherHeap.head;
    head = nullptr;
    Element* last = nullptr;
    while (first != nullptr && second != nullptr){
        if (first->degree < second->degree){
            if (last != nullptr) last->brother = first;
            else head = first;
            last = first;
            first = first->brother;
        }
        else{
            if (last != nullptr) last->brother = second;
            else head = second;
            last = second;
            second = second->brother;
        }
    }
    while (first != nullptr){
        if (last != nullptr) last->brother = first;
        else head = first;
        last = first;
        first = first->brother;
    }
    while (second != nullptr){
        if (last != nullptr) last->brother = second;
        else head = second;
        last = second;
        second = second->brother;
    }
    if (head == nullptr) return;
    last->brother = nullptr;
    otherHeap.head = nullptr;
    last = head;
    head = nullptr;
    Element* old_last = nullptr;
    while (last!=nullptr && last->brother!=nullptr){
        if (last->degree != (last->brother)->degree){
            old_last = last;
            if (head==nullptr) head=last;
            last = last->brother;
            continue;
        }
        if ((last->brother)->brother != nullptr && ((last->brother)->brother)->degree == last->degree){
            old_last = last;
            if (head==nullptr) head=last;
            last = last->brother;
            continue;
        }
        last = Union(last, last->brother);
        if (old_last != nullptr) old_last->brother=last;
    }
    if (head==nullptr) head = last;
    determine_minimum();

}
template<typename Key>
void Binomial_heap<Key>::determine_minimum(){
    if (head==nullptr){
        minimal_root = nullptr;
        return;
    }
    minimal_root = head;
    Element* last = head->brother;
    while (last != nullptr){
        if (minimal_root->key > last->key) minimal_root = last;
        last = last->brother;
    }
}

template<typename Key>
typename
Binomial_heap<Key>::Pointer Binomial_heap<Key>::insert(Key x){
    Element* new_element = new Element(x);
    Binomial_heap new_heap;
    new_heap.add_leftmost_tree(new_element);
    this->merge(new_heap);
    Pointer ptr(new_element);
    return ptr;
}

template<typename Key>
Key Binomial_heap<Key>::get_min() const{
    if (head==nullptr) throw std::runtime_error("no elements in heap");
    return minimal_root->key;
}

template<typename Key>
typename
Binomial_heap<Key>::Element* Binomial_heap<Key>::reverse_children(Element *son){
    Element* nxt_son = son->brother;
    son->father = nullptr;
    Element* leftmost_son = son;
    while (nxt_son != nullptr){
        Element* future_nxt_son = nxt_son->brother;
        nxt_son->brother = son;
        nxt_son->father = nullptr;
        son = nxt_son;
        nxt_son = future_nxt_son;
    }
    leftmost_son->brother = nullptr;
    return son;
}

template<typename Key>
Key Binomial_heap<Key>::extract_min(){
    if (head==nullptr) throw std::runtime_error("no elements in heap");
    Key value = minimal_root->key;
    if (head==minimal_root) head = head->brother;
    else{
        Element* last = head;
        while (last->brother != minimal_root) last = last->brother;
        last->brother = (last->brother)->brother;
    }
    Element* son = minimal_root->child;
    if (son!=nullptr){
        son = reverse_children(son);
        Binomial_heap new_heap;
        new_heap.add_leftmost_tree(son);
        this->merge(new_heap);
    }
    determine_minimum();
    return value;
}

template<typename Key>
void Binomial_heap<Key>::isolate(Element* root){
    if (head == root){
        head = root->brother;
        root->brother = nullptr;
    }
    else{
        Element* last = head;
        while (last->brother != root) last = last->brother;
        last->brother = root->brother;
        root->brother = nullptr;
    }
    determine_minimum();
}

template<typename Key>
void Binomial_heap<Key>::add_leftmost_tree(Element* new_root){
    if (head == nullptr){
        head = new_root;
        determine_minimum();
        return;
    }
    new_root->brother = head;
    head = new_root;
}

template<typename Key>
void Binomial_heap<Key>::Delete(Pointer ptr){
    Element* current = ptr.my_element;
    Array<Element*> ladder;
    while (current != nullptr){
        ladder.add(current);
        current = current->father;
    }
    isolate(ladder.back());
    Binomial_heap<Key> pieces_of_tree;
    while (ladder.length() > 1){
        Element* root = ladder.back();
        Element* left_child = root->child;
        left_child->father = nullptr;
        root->child = left_child->brother;
        root->degree--;
        left_child->brother = nullptr;
        if (left_child == ladder.get(ladder.length() - 2)){
            pieces_of_tree.add_leftmost_tree(root);
            ladder.del();
        }
        else{
            pieces_of_tree.add_leftmost_tree(left_child);
        }
    }
    Binomial_heap with_deleted;
    with_deleted.add_leftmost_tree(ladder.back());
    with_deleted.extract_min();
    with_deleted.merge(pieces_of_tree);
    merge(with_deleted);
}

template<typename Key>
void Binomial_heap<Key>::change(Pointer &ptr, Key key){
    Delete(ptr);
    Pointer false_ptr = insert(key);
    ptr.my_element = false_ptr.my_element;
}
