//
// Created by Hassan W. ElDessouki on 05/11/2025.
//

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
};

class LinkedList {
    private:
        Node *head;         // memory address of the List Head

    public:
        LinkedList() {
            head = nullptr;     // initialize head as null
        }

        void insertNode(int val) {
            Node *newNode = new Node;           //
            newNode->data = val;                // create new node with the value to be inserted

            if (head == nullptr) {              // in the case that head is a null, initialize list by storing memory address of the node as the head
                head = newNode;
                head->next = head;
                head->prev = head;
            } else {
                newNode->prev = head->prev;         //
                newNode->next = head;               //
                head->prev->next = newNode;         //
                head->prev = newNode;               //

                // DEBUG
                // cout << "newNode address is" <<  newNode << endl;
                // cout << "head address is" <<  head << endl;
                // cout << "next of head address is" <<  head->next << endl;
                // cout << "prev of head address is" <<  head->prev << endl;
                // cout << "next of newNode address is" <<  newNode->next << endl;
                // cout << "prev of newNode address is" <<  newNode->prev << endl;
            }
        }

        void deleteNode(int val) {
            // if head is null, print message to user that the list is empty
            if (head == nullptr) {
                cout << "List is empty!" << endl;
                return;
            }

            // check if head is the node to delete
            if (head->data == val) {                // if so, then the next node after the head becomes the new head
                Node *newHead = head->next;         // first store the memory address of the next node
                newHead->prev = head->prev;         // set the previous of the newHead to be the last node
                head->prev->next = newHead;         // set the next of the last node in the list to the newHead
                delete head;                        // then delete the current head
                head = newHead;                     // then set the head as the memory address of the next node
                return;
            }

            // otherwise, serarch for the node by traversing it
            Node *currentNode = head;
            Node *toDeleteNode = nullptr;

            do {
                if (currentNode->data == val) {
                    toDeleteNode = currentNode;
                }
                currentNode = currentNode->next;
            } while (currentNode != head);
            if (toDeleteNode == nullptr) {
                cout << "Node with value " << val << " does not exist" << endl;
            } else {
                toDeleteNode->prev->next = toDeleteNode->next;
                toDeleteNode->next->prev = toDeleteNode->prev;
                delete toDeleteNode;
            }
        }

        void print() {
            // if head is null, print message to user that the list is empty
            if (head == nullptr) {
                cout << "List is empty!" << endl;
                return;
            }

            // otherwise, traverse through the list and print the values until the end of the list
            Node *currentNode = head;
            do {
                cout << currentNode->data;
                currentNode = currentNode->next;
                if (currentNode != head) {
                    cout << "<->";              // this is so that we do not get an extra <-> at the end of the text :-)
                }
            } while (currentNode != head);
            cout << endl;
        }
        void printReverse() {
            // if head is null, print message to user that the list is empty
            if (head == nullptr) {
                cout << "List is empty!" << endl;
                return;
            }

            // otherwise, traverse through the list and print the values until the end of the list
            Node *tail = head->prev;
            Node *currentNode = tail;
            do {
                cout << currentNode->data;
                currentNode = currentNode->prev;
                if (currentNode != tail) {
                    cout << " ";              // this is so that we do not get an extra SPACE "or <->" at the end of the text :-)
                }
            } while (currentNode != tail);
            cout << endl;
        }
};

int main() {
    int valArray[5];                    // initate array of 5 nodes
    LinkedList list;                    // initiate circular doubly linked list
    cin >> valArray[0] >> valArray[1] >> valArray[2] >> valArray[3] >> valArray[4];
    for (int i = 0; i < 5; i++) {
        list.insertNode(valArray[i]);   // insert each value into the list respectively
    }
    list.deleteNode(valArray[1]);       // remove the second node (delete by Value)
    list.printReverse();                // reverse the linked list as an output

    return 0;
}