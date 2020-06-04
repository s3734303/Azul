//
//  tree.hpp
//  Azul
//
//  Created by Home on 6/1/20.
//  Copyright © 2020 3734303. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp
#include <cassert>
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
        void DeleteNode(Node* root,int key){
            if(root == nullptr) return root;
            if(key > root->key)
                root->right = DeleteNode(root->Right, key);
            else if(key < root->key)
                root->Left = DeleteNode(root->Left, key);
            else{
                if(!root->HasLeft()){
                    Node *t = root->Left;
                    free(root);
                    return t;
                }
                else if(!root->HasRight()){
                    Node *t = root->Right;
                    free(root);
                    return t;
                }
            }
        }
        Node* InsertNode(Node* root,Node* node){
            if(root==nullptr)
                return node;
            if(node->key>root->key)
                root->Right = InsertNode(root->Right,node);
            else
                root->Left = InsertNode(root->Left,node);
            return root;
        }
        
    };
    Node* root;
    int size{0};
    
    public:
    
    Tree()=default;
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
    void remove(int key){
        DeleteNode(root,key);
    }
    
    void insert(const T& value,int key){
        
        root =root->InsertNode(root, new Node(value,key));
        size++;
    }
    T getLargest(){
        Node* header = root;
        while(header->HasRight())
            header=header->Right;
        return header->Data;
    }
    T getSmallest(){
        Node* header = root;
        while(header->HasLeft())
            header=header->Left;
        return header->Data;
    }

};


#endif /* tree_hpp */

