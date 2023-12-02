// Exercise 1
// Stack using Arrays
// Implement the Stack class using an array. The class should contain the constructor, destructor along with the Size(),Push(x) and Pop() operations. 
// Also, demonstrate your implementation by using it in a small program. (You can briefly create a variable and use each operation).

// Question 1
// The stack's operations are somewhat of a subset of the List operations we learned prevously and can be implmented using those operations. 
// Please implement the Push and Pop operations using the List's operations (ie: size(), get(), set(), add(), remove()) 
// (hint: you are always going to be adding or removing at the end of the list.)

#include <iostream>
#include <sstream>

using namespace std;

template <typename T> //, class Alloc = allocator<T>> // out_of_range
class CustomList2{
protected:
    typedef T* iterator; // using iterator = T*;
    T* arr;
    std::size_t size; // Size() returns how many values are in the current list. This value is stored in the size variable.
    std::size_t capacity; // length (capacity in here) as the number of elements that was allocated in memory.
    void resize(std::size_t newCapacity){
        T* newArr = new T[newCapacity];
        for (std::size_t i = 0; i < size; i++){
            newArr[i] = arr[i];
        }
        if (this->arr != nullptr)
            delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        // size = newCapacity;
    }
    T& operator[](const std::size_t index) {
        // if (index == 0 && arr == nullptr){
        //     this->resize(1);
        // }else 
        if (index >= size){
            // throw std::out_of_range("index out of range");
            this->resize(index + 1);
        }
        return arr[index];
    }
public:
    ~CustomList2(){
        if (this->arr != nullptr)
            delete[] this->arr;
    }
    CustomList2(){
        this->arr = nullptr;
        this->size = 0;
        this->capacity = 0;
    }
    CustomList2(const std::size_t capacity){
        this->arr = new T[capacity];
        this->capacity = capacity;
        this->size = 0;
    }

    // for each loop
    iterator begin(){
        return arr;
    }
    iterator end(){
        return arr + size;
    }
    // basic functions
    // Size() returns how many values are in the current list. This value is stored in the size variable.
    const std::size_t Size() const { 
        return size;
    }
    const std::size_t Capacity() const {
        return capacity;
    }
    T& get(const std::size_t index) {
        if (index >= size){
            std::ostringstream oss;
            oss << "get(): index out of range at index: " << index;
            throw std::out_of_range(oss.str());
        }
        return (*this)[index];
    }
//    Question 1
// Another operations that is commonaly used in a List is the Push(x) operation. Where the value x gets added to the end of the list. Please also implement the Push(x) operation in your class and discuss why you decided to implement the function this way. You may implement it using your other implemented operations.
    void Push(T& value){
        (*this)[this->size] = value;
        this->size++;
    }
    void Add(const std::size_t index, T& value){
        size_t finalIndex = index > size ? size : index;
        // cout << "add() finalIndex: " << finalIndex << endl;
        for (std::size_t i = size; i > finalIndex; i--){
            // cout << "move() from " << i -1 << " to " << i << endl;
            (*this)[i] = (*this)[i - 1];
        }

        (*this)[finalIndex] = value;
        size++;
    }

    // Set(i,x) assigns the value x to index i. This value is stored in the list variable. Again we need to check the length of the list to make sure we do not go out of bounds.
    // this function does not resize or expend the array's size
    void Set(const std::size_t index, T& value){
        if (index >= size){
            std::ostringstream oss;
            oss << "set(): index out of range at index: " << index;
            throw std::out_of_range(oss.str());
        }
        (*this)[index] = value;
    }

    // Remove(i) deletes index i and then decrements all values after i down one position in the array. Again we need to assert i to be less than the size.
    void Remove(const std::size_t index){
        if (index >= size){
            std::ostringstream oss;
            oss << "remove(): index out of range at index: " << index;
            throw std::out_of_range(oss.str());
        }
        for (std::size_t i = index; i < size - 1; i++){
            (*this)[i] = (*this)[i + 1];
        }
        size--;
    }
};

template <typename T> 
class Stack {
protected:
    CustomList2<T> list;
public:
    ~Stack(){
    }
    Stack(){
        this->list = CustomList2<T>();
    }
    // Size(),Push(x) and Pop() 
    const std::size_t Size() const { 
        return this->list.Size();
    }
    void Push(T& value){
        this->list.Push(value);
    }
    T& Pop(){
        if (this->list.Size() == 0){
            std::ostringstream oss;
            oss << "Pop(): index out of range: " << this->list.Size() << ", currect size() = " << this->list.Size();
            throw std::out_of_range(oss.str());
        }
        T& value = this->list.get(this->list.Size() - 1);
        this->list.Remove(this->list.Size() - 1);
        return value;
    }
};

int main(const int argc, const char* argv[]){
    Stack<int> stack;
    int testvalue = 99;
    
    cout << "0) check element in the empty list" << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;

    cout << "1.0) Push() the element 99 by push" << endl;
    stack.Push(testvalue = 99);
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "1.1) Push() the element 98 by push" << endl;
    stack.Push(testvalue = 98);
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "1.2) Push() the element 97 by push" << endl;
    stack.Push(testvalue = 97);
    cout << "stack size getSize(): " << stack.Size() << endl;

    cout << "2.0) Pop() the element 97 by pop" << endl;
    cout << "stack Pop(): " << stack.Pop() << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "2.1) Pop() the element 98 by pop" << endl;
    cout << "stack Pop(): " << stack.Pop() << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "2.2) Pop() the element 99 by pop" << endl;
    cout << "stack Pop(): " << stack.Pop() << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;
    try{
        cout << "2.3) Pop() the element by pop (catached by exception): " << endl;
        cout << "stack Pop(): " << stack.Pop() << endl;
        cout << "stack size getSize(): " << stack.Size() << endl;
    }catch (std::out_of_range& e){
        cout << "out_of_range correctly: " << e.what() << endl;
    }

    cout << "3.0) Push() again the element 89" << endl;
    stack.Push(testvalue = 89);
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "3.1) Push() again the element 88" << endl;
    stack.Push(testvalue = 88);
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "3.2) Push() again the element 87" << endl;
    stack.Push(testvalue = 87);
    cout << "stack size getSize(): " << stack.Size() << endl;

    cout << "4.0) Pop() the element 87 by pop" << endl;
    cout << "stack Pop(): " << stack.Pop() << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "4.1) Pop() the element 88 by pop" << endl;
    cout << "stack Pop(): " << stack.Pop() << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;
    cout << "4.2) Pop() the element 89 by pop" << endl;
    cout << "stack Pop(): " << stack.Pop() << endl;
    cout << "stack size getSize(): " << stack.Size() << endl;
    try{
        cout << "4.3) Pop() the element by pop (catached by exception): " << endl;
        cout << "stack Pop(): " << stack.Pop() << endl;
        cout << "stack size getSize(): " << stack.Size() << endl;
    }catch (std::out_of_range& e){
        cout << "out_of_range correctly: " << e.what() << endl;
    }
}