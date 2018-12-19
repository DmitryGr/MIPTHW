#include "array.h"
template<typename Key>
class Heap{

    private:
        class Element{
            friend Heap;

            private:
                Element(Key k, int ind){
                    key = k, index=ind;
                }
                Key key;
                int index;
        };
        Array<Element*> arr;
        void SiftDown(int index);
        void SiftUp(int &index);
        Key get(int index) const;
        void Swap(int a, int b);


    public:
        class Pointer{
            friend Heap;

            private:
                Pointer(Element *element, Heap *heap){
                    my_element = element, my_heap = heap;
                }
                Element *my_element;
                Heap *my_heap;

        };
        bool is_empty() const;
        Pointer insert(Key key);
        Key get_min() const;
        Key extract_min();
        void change(Pointer &ptr, Key key);
        int length() const;
        void Delete(Pointer &ptr);
};
#include "heap.cpp"
