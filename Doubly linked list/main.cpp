#include <iostream>
#include "doublylinkedlist.h"

using namespace std;
void test(){
    DoublyLinkedList<int> dll;
    
    dll.push(1);
    dll.push(2);
    dll.push(3);
    
    DoublyLinkedList<int> dllCopy = dll;
    
    dllCopy.push(4);
    dllCopy.remove(1);
    dllCopy.remove(0);
    dllCopy.insert(5, 1);
    
    dll.print();
    dllCopy.print();
    
    dll = dllCopy;
    dll.print();
}


int main() {
    test();
    
    return 0;
}