#include <iostream>
using namespace std;

class MyVector {
public:
    // 1. Default constructor
MyVector(){
    data = nullptr;
    next = 0;
    this-> sz = sz;
}
    // 2. Constructor that takes in size
    MyVector(int sz) : sz(sz), next(0) {
        if (sz > 0) {
            data = new int[sz];
        } else {
            data = nullptr;
        }
    }

    // 3. Copy constructor
MyVector(const MyVector& v) {
    sz = v.sz;
    next = v.next;
    if (sz > 0) {
        data = new int[sz];
        for (int i = 0; i < next; i++) {
            data[i] = v.data[i];
        }
    } else {
        data = nullptr;
    }
}

    // 4. Push back
    void push_back(int ele) {
        if (next >= sz) {
            resize(sz > 0 ? 2 * sz : 1);
        }
        data[next++] = ele;
    }

    // 5. Insert
    void insert(int i, int ele) {
        if (i >= 0 && i < next) {
            data[i] = ele;
        }
    }

    // 6. Read i-th element
    int at(int i){
    return data[i];
    }

    // 7. Overload operator[]
    int operator[](int i) {
        return data[i];
    }

    // 8. Erase
    void erase(int i) {
        if (i < 0 || i >= next) {
            cout << "erase out of bounds" << endl;
            return;
        }
        for (int j = i; j < next - 1; ++j) {
            data[j] = data[j + 1];
        }
        --next;
    }

    // 9. Size
    int size() const {
        return next;
    }

    // 10. True or false empty
   bool empty(){
    if (sz == 0){
        return true;
    }
    else{
        return false;
    }
   }

    // 11. Destructor
    ~MyVector() {
        delete[] data;
    }

    // 12. Assignment operator (completes rule of three)
    MyVector& operator=(const MyVector& v) {
        if (this != &v) {  // Self-assignment check
            delete[] data;

            sz = v.sz;
            next = v.next;
            if (sz > 0) {
                data = new int[sz];
                for (int i = 0; i < next; ++i) {
                    data[i] = v.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    // 13. Print for testing
    void print() const {
        for (int i = 0; i < next; ++i) {  // Note the use of next instead of sz
            cout << data[i] << " ";
        }
        cout << endl;
    }

private:
    int* data;
    int next;
    int sz;

    // Helper function to resize the array
    void resize(int new_sz) {
        int* new_data = new int[new_sz];
        for (int i = 0; i < next; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        sz = new_sz;
    }
};

int main() {
    MyVector<int> v1(3);
    v1.push_back(0);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    
    v1.insert(2, 9);
    v1.insert(10, 9);
    cout << v1.at(1) << endl;  // should be 1
    cout << v1[4] << endl;     // should be 4
    cout << v1[10] << endl;    // should be 0
    v1.print();                // should be 0 1 9 3 4 
    
    v1.erase(2);
    v1.erase(10);  // should output: erase out of bounds
    v1.print();    // should be 0 1 3 4 

    cout << v1.size() << endl;  // should be 4
    MyVector<int> v2;
    cout << v2.empty() << " and " << v1.empty() << endl;  // should be 1 and 0. 1 for true 0 for false
    
    cout << "Additional checks" << endl;
    // Additional checks provided by chat gpt
    MyVector<int> v3(v1);  // Testing copy constructor
    v3.print();            // Should be 0 1 3 4 

    MyVector<int> v4 = v1;  // Testing assignment operator
    v4.print();             // Should be 0 1 3 4 

    v1.push_back(5);
    v3.push_back(6);
    v4.push_back(7);

    v1.print();  // Should be 0 1 3 4 5
    v3.print();  // Should be 0 1 3 4 6
    v4.print();  // Should be 0 1 3 4 7

    return 0;
}
