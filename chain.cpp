#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    Node* node = new Node(ndata);
    Node* temp = walk(head_, length_);
    temp->next = node;
    node->next = head_;
    length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    if ((i <= 0 || i > length_) || (j <= 0 || j > length_)) return;

    if (i == j) return;

    if (i > j) {
        int k = i;
        i = j;
        j = k;
    }

    Node* prev1 = walk(head_, i - 1);
    Node* prev2 = walk(head_, j - 1);
    Node* node1 = prev1->next;
    Node* node2 = prev2->next;

    if (j - i == 1) {
        prev1->next = node1->next;
        Node* temp = node2->next;
        prev1->next->next = prev2;
        prev2->next = temp;
    } else {
        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
        temp = prev1->next;
        prev1->next = prev2->next;
        prev2->next = temp;
    }
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    Node* prev = NULL;
    Node* curr = head_;
    while (curr != NULL) {
        Node* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
}

/*
* Modifies the current chain by "rotating" every group of k nodes by one position.
* In every k-node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    if (k <= 1 || k >= length_) {
        return;
    }
    int i = 1;      // does swapping
    int const savek = k;  // saves value of k
    int pos = 0;    // tracks current position
    
    while (pos + k <= length_) { // breaks if subchain exceeds length
        while (k > 1) { // does the swapping for one subchain
            swap(i, i + 1);
            i++;
            k--;
        }
        k = savek;
        pos += savek;
        i = pos + 1;
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    Node* curr = head_->next;

    while(curr != head_) {
        Node* del = curr;
        curr = curr->next;
        delete del;
    }
    delete head_;
    length_ = 0;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    length_ = 0;

    head_ = new Node();
    head_->next = head_;

    // Node* curr = head_;
    Node* otherNode = other.head_->next;

    for (int i = 0; i < other.length_; i++) {
        insertBack(otherNode->data);
        otherNode = otherNode->next;
    }

    height_ = other.height_;
    width_ = other.width_;
}