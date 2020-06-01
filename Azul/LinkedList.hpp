#ifndef LINKEDLIST_HPP_INCLUDED
#define LINKEDLIST_HPP_INCLUDED

#include <cassert>    // For assert()
#include <ostream>    // For printing to ostream
#include "Types.h"

template <typename T>
class LinkedList {
    private:
  
    struct Node {
        Node* Previous{nullptr};
        Node* Next{nullptr};
        T     Data{};
        friend class LinkedList;

        // Create a default empty node
        Node() = default;

        // Create a node storing input data
        explicit Node(const T& data)
        : Data{data} {}

        // Create a node storing input data, and pointing to another node
        Node(const T& data, Node* next)
        : Data{data}, Next{next} {}


    };

    Node* m_head{nullptr};
    int   m_count{0};

    // Ban copy
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;


    public:

    typedef Node* Position;

    LinkedList() = default;

    ~LinkedList() {
        Clear();
    }

    int Count() const {
        return m_count;
    }

    bool IsEmpty() const {
        return (m_count == 0);
    }

    void Clear() {
        while (! IsEmpty()) {
          RemoveHead();
        }
    }
 
  void InsertHead(const T& value) {
    Node* node = new Node{value};

    // Replace current head with new node
      node->Next = m_head;
//      node->Next->Previous=node;
      m_head = node;
      ++m_count;
  }

  void RemoveHead() {
    // It's invalid to attempt to remove head from an empty list
    assert(! IsEmpty());

    // Save pointer to head's next node, before removing current head;
    // basically, head's next node will become the *new* head
    Node* newHead = m_head->Next;
    
    // Remove current head
    delete m_head;

    // Update head, pointing to the node that followed the old head
    m_head = newHead;

    --m_count;
  }

  T ElementAt(Position node) {
    assert(! IsEmpty());
    assert(node != nullptr);    

    return node->Data;
  }

  void InsertAfter(Position node, const T& value) {
    assert(node != nullptr);

    Node* newNode = new Node{value};
    
    // This new node is inserted between 'node' and 'node->Next'
    newNode->Next = node->Next;
    node->Next = newNode;

    ++m_count;
  }

  void RemoveAfter(Position node) {
    assert(! IsEmpty());
    assert(node != nullptr);

    Node* obsoleteNode = node->Next;
    node->Next = obsoleteNode->Next;

    delete obsoleteNode;

    --m_count;
  }

  Position Find(const T& value) {
    if (IsEmpty()) {
      return nullptr;
    }

    // Linear search
    Node* node = m_head;
    while (node != nullptr) {
      // Compare current node's data with the search value
      if (node->Data == value) {
        // Found!
        return node;
      }

      // Move forward to the next node in the list
      node = node->Next;
    }

    // After traversing the whole list, no matching element was found
    return nullptr;
  }

  friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
    if (list.IsEmpty()) {
      os << "[ Empty List ]";
      return os;
    }
    


    // For each node:
    Node* node = list.m_head;
    while (node != nullptr) {
      // Print data stored in current node
      os << node->Data;

      // Move forward to the next node
      node = node->Next;
    }
    return os;
  }

  void getAll(std::vector<tile> &bag)
  {
    Node* current = m_head;
    int i = 0;
    while (i != Count())
    {
        bag.push_back(current -> Data);
        current = current->Next;
        i++;
    }
    
  }
 
};

#endif




