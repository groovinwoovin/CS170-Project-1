#include "node.h"

#include <iostream>
using namespace std;

Node::Node(){
}

bool Node::operator<(const Node &rhs) const{
    return this->g_n < rhs.g_n;
}

void Node::setBoard(int array[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y]) {
    for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
        for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
            board[i][j] = array[i][j];
        }
    }
}

void Node::setg_n(int g){
    g_n = g;
}

void Node::seth_n(int h){
    h_n = h;
}

void Node::createChildren(){
    //see if up, down, left, right works
    int blank_x;
    int blank_y;
    int temp[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y];

    for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
        for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
            if(board[i][j] == 0){
                blank_x = i;
                blank_y = j;
            }
        }
    }

    //set up tile
    if(blank_x >= 1) {
        for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
            for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
                temp[i][j] = board[i][j];
            }
        }
        temp[blank_x][blank_y] = temp[blank_x - 1][blank_y];
        temp[blank_x - 1][blank_y] = 0;
        this->up = new Node();
        this->up->setBoard(temp);
        this->up->parent = this;
        this->up->setg_n(this->g_n + 1);
        this->up->seth_n(0);
    }
    
    //set down tile
    if(blank_x < NODE_BOARD_SIZE_X - 1) {
        for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
            for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
                temp[i][j] = board[i][j];
            }
        }
        temp[blank_x][blank_y] = temp[blank_x + 1][blank_y];
        temp[blank_x + 1][blank_y] = 0;
        this->down = new Node();
        this->down->setBoard(temp);
        this->down->parent = this;
        this->down->setg_n(0);
    }

    //set left tile
    if(blank_y >= 1) {
        for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
            for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
                temp[i][j] = board[i][j];
            }
        }
        temp[blank_x][blank_y] = temp[blank_x][blank_y - 1];
        temp[blank_x][blank_y - 1] = 0;
        this->left = new Node();
        this->left->setBoard(temp);
        this->left->parent = this;
        this->left->setg_n(0);
    }

    //set right tile
    if(blank_y < NODE_BOARD_SIZE_Y - 1) {
        for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
            for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
                temp[i][j] = board[i][j];
            }
        }
        temp[blank_x][blank_y] = temp[blank_x][blank_y + 1];
        temp[blank_x][blank_y + 1] = 0;
        this->right = new Node();
        this->right->setBoard(temp);
        this->right->parent = this;
        this->right->setg_n(0);
    }
}

void Node::printNode(){
    cout<<"NODE\n";
    if(this != nullptr){
        for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
            for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
                cout<< board[i][j]<< ",";
            }
            cout<< endl;
        }
    }
    else{
        cout<< "EMPTY NODE";
    }
}