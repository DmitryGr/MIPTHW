#include "array.h"
template<typename Key>
class Binomial_heap{

    private:

        class Element{
            friend Binomial_heap;
            private:
                Element(Key k){
                    key = k, father=nullptr, brother=nullptr, child=nullptr, degree=1;
                }
                Key key;
                Element* father;
                Element* brother;
                Element* child;
                int degree;

        };
        Element* head;
        Element* minimal_root;
        Element* Union(Element *a, Element *b);
        void determine_minimum();
        Element* reverse_children(Element *son);
        void isolate(Element* root);
        void add_leftmost_tree(Element *new_root);

    public:

        Binomial_heap(){
            head = nullptr;
        }

        class Pointer{
            friend Binomial_heap;
            private:

                Pointer(Element *element){
                    my_element = element;
                }
                Element *my_element;

        };

        bool is_empty() const;
        void merge(Binomial_heap &otherHeap);
        Pointer insert(Key x);
        Key get_min() const;
        Key extract_min();
        void Delete(Pointer ptr);
        void change(Pointer &ptr, Key key);
};
#include "binheap.cpp"
