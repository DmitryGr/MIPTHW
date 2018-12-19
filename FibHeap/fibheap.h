#include "array.h"
template<typename Key>
class Fibonacci_heap{

    private:
        class Element{
            friend Fibonacci_heap;
            private:
                Element(Key init_key){
                    key = init_key;
                    father = nullptr, left_brother = nullptr, right_brother = nullptr, child = nullptr;
                    degree = 0;
                    mark = false;
                }
                Key key;
                Element* father;
                Element* left_brother;
                Element* right_brother;
                Element* child;
                int degree;
                bool mark;
        };
        Element* minimum;
        Element* delete_cycle();
        void connect(Element* right_edge, Element *other_chain_left_edge);
        void cut(Element *element);
        void cascading_cut(Element* element);
        void add_into_list(Element *new_element);
        void delete_from_list(Element* element);
        void determine_minimum();
        void consolidate();
        void add_into_heap(Element* new_element);
        void add_righter(Element* start, Element* new_element);
        void add_into_cell(Array<Element*> &cells, Element* last);

    public:

        Fibonacci_heap(){
            minimum = nullptr;
        }

        class Pointer{
            friend Fibonacci_heap;
            private:

                Pointer(Element *element){
                    my_element = element;
                }
                Element* my_element;
        };

        bool is_empty() const;
        Key get_min() const;
        Pointer insert(Key key);
        void merge(Fibonacci_heap<Key> &otherHeap);
        void decrease_key(Pointer ptr, Key key);
        Key extract_min();
        void print();
};
#include "fibheap.cpp"

