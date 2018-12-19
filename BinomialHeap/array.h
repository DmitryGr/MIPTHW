template <typename Key>
class Array{

    private:
        Key* arr;
        int length_of_array;
        int free_ind;

    public:
        Array();
        ~Array();
        void add(Key element);
        void del();
        Key get(int index) const;
        void change(int index, Key element);
        int length() const;
        void Swap(int fi, int si);
        Key back() const;

};

#include "array.cpp"
