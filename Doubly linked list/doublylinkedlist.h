#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


#include <iostream>
using namespace std;

template<typename T>
struct Node{
T data;
Node* next;
Node* prev;
};

template<typename T>
class DoublyLinkedList{
    public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& x);
    void operator=(const DoublyLinkedList& x);

    
    void push(T data);
    void pop();
    int size() const;
    int print() const;
    int& at(int idx) const;
    
    void insert(T data, int pos);
    void remove(int pos); 
    
    
    private:
    Node<T>* head;
    int numElements;
    
    
    
};

template<typename T>
DoublyLinkedList<T> ::DoublyLinkedList(){
    head = nullptr;
    numElements = 0;
}

template<typename T>
DoublyLinkedList<T> ::~DoublyLinkedList(){
     while(head != nullptr){
        Node<T>* nextElement = head->next;
        delete head;
        head = nextElement;
}
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& x) {
    head = nullptr;
    numElements = 0;

    Node<T>* currentNode = x.head;
    while (currentNode != nullptr) {
        push(currentNode->data);
        currentNode = currentNode->next;
    }
}

template<typename T>
void DoublyLinkedList<T>:: operator=(const DoublyLinkedList& x){

    while(head != nullptr){
        Node<T>* nextElement = head->next;
        delete head;
        head = nextElement;
    }
    
    head = nullptr;
    numElements = 0;
    
    for(int i = 0; i < x.size(); i++){
        push(x.at(i));
    }
}



template<typename T>
void DoublyLinkedList<T>:: push(T data){
    numElements++;
    
    if(head == nullptr){
        head = new Node<T>;
        head->data = data;
        head->prev = nullptr;
        head->next = nullptr;
        return;
    }
    
    Node<T>* currentNode = head;
    while(currentNode->next != nullptr){
        currentNode= currentNode->next;
    }
    currentNode->next = new Node<T>;
    currentNode->next->next=nullptr;
    currentNode->next->prev= currentNode;
    currentNode->next->data = data; 
    
    
    
}

template<typename T>
int DoublyLinkedList<T>:: size() const{
    return numElements;
}

template<typename T>
int& DoublyLinkedList<T>:: at(int idx) const{

    Node<T>* currentNode = head;
    int i = 0;
    while(i<idx){
        i++;
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template<typename T>
int DoublyLinkedList<T>:: print() const{
    int x;
    Node<T>* currentNode = head;
    while(currentNode != nullptr){
        cout<<currentNode->data<<" ";
        currentNode= currentNode->next;
        x++;
    }
    cout<<endl;
    return x; 
}

template<typename T>
void DoublyLinkedList<T>:: pop(){
    if( head == nullptr){
        return;
    }
    
    numElements--;
    if(head->next == nullptr){
        delete head;
        head = nullptr;
        return;
    }
    
    Node<T>* currentNode = head;
    while(currentNode->next != nullptr){
        currentNode= currentNode->next;
    }
    currentNode = currentNode->prev;
    delete currentNode->next;
    currentNode->next = nullptr;
    return;
    
}

template<typename T>
void  DoublyLinkedList<T>:: insert(T data, int pos){
    if(pos == 0){
        Node<T>* temp = new Node<T>();
        temp->data = data;
        temp->next = head;
        head = temp;
        
        numElements++;
        return;
    }
    
    Node<T>* currentNode= head;
    int currentpos = 0;
    
    while ((currentpos+1) < pos){
        currentNode = currentNode->next;
        currentpos++;
    }
    if(currentNode->next == nullptr){
        push(data);
        return;
    }
    
    Node<T>* temp = new Node<T>();
    temp->data = data;
    temp->prev = currentNode;
    temp->next = currentNode->next;
    currentNode->next =temp;
    
    numElements ++;
    
}


template<typename T>
void DoublyLinkedList<T>:: remove(int pos){
    if(pos== 0){
        Node<T>* temp = head->next;
        delete head;
        head = temp;
        numElements--;
        return;
    }
    
    Node<T>* currentNode= head;
    int currentpos = 0;
    
    while ((currentpos+1) < pos){
        currentNode = currentNode->next;
        currentpos++;
    }

    Node<T>* temp = currentNode->next;
    currentNode->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->prev = currentNode;
    }
    delete temp;
    
    numElements --;
} 

#endif