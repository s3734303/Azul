//
//  tree.hpp
//  Azul
//
//  Created by Home on 6/1/20.
//  Copyright © 2020 3734303. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
template <typename T>
class Tree{
    private:
    
    struct Node{
        Node* Left{nullptr};
        Node* Right{nullptr};
        T     Data{};
        int key{0};
        Node() = default;
        explicit Node(const T& data,int key)
        : Data{data},key{key} {}
        bool HasLeft(){
            return Left!=nullptr;
        }
        bool HasRight(){
            return Right!=nullptr;
        }
        
    };
    Node* root;
    int size{0};
    public:
    
    Tree(const T& value,int key){
        root= new Node(value,key);
        size=1;
    };
    ~Tree()
    {
    }
    int Size() const{
        return size;
    }
    int IsEmpty() const {
        return (size==0);
    }
    void Clear(){
        root =nullptr;
    }
     
    void add(const T& value,int key){
        Node* header = root;
        bool run = true;
        while((header->HasLeft() || header->HasRight()) && run) {
            if(key>header->key){
                if(header->HasRight())
                    header = header->Right;
                else{
                    header->Right = new Node(value,key);
                    run = false;
                }
                    
            }
            else{
                if(header->HasLeft())
                    header = header->Left;
                else{
                    header->Left = new Node(value,key);
                    run=false;
                }
                    
            }
        }
        size++;
    }

};


#endif /* tree_hpp */

