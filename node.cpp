#include "node.h"

#include <iostream>
using namespace std;

Node::Node(){
    for (int i = 0; i < NODE_BOARD_SIZE_X; ++i) {
        for (int j = 0; j < NODE_BOARD_SIZE_Y; ++j) {
            board[i][j] = 0;
        }
    }
    g_n = .0;
    h_n = .0;
    output = "";
    parent = nullptr;
    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    delete parent;
    delete up;
    delete down;
    delete left;
    delete right;
}

bool Node::operator<(const Node &rhs) const{
    return (this->g_n + this->h_n) < (rhs.g_n + rhs.h_n);
}

void Node::setBoard(int array[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y]) {
    for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
        for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
            board[i][j] = array[i][j];
        }
    }
}

void Node::setg_n(double g){
    g_n = g;
}

void Node::seth_n(double h){
    h_n = h;
}

void Node::setoutput(std::string input) {
    output.append(input);
}

void Node::createChildren(){
    //see if up, down, left, right works
    int blank_x;
    int blank_y;
    int temp[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y];

    //fill temp board
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
    }
}

void Node::printNode(){
    cout<<"NODE\n";
    if(this != nullptr){
        for(int i = 0; i < NODE_BOARD_SIZE_X; ++i){
            for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j){
                cout<< board[i][j];
            }
            cout<< endl;
        }
    }
    else{
        cout<< "EMPTY NODE";
    }
}

void Node::printOutput() {
    cout << output;
}

bool Node::checkIfGoal() {
    //node->printNode();
    int tempTile = board[0][0];

    for (int i = 0; i < NODE_BOARD_SIZE_X; ++i) {
        for (int j = 0; j < NODE_BOARD_SIZE_Y; ++j) {
            if (tempTile > board[i][j]) {
                if (i >= NODE_BOARD_SIZE_X - 1 && j >= NODE_BOARD_SIZE_Y - 1) { // implied last tile is 0
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                tempTile = board[i][j];
            }
        }
    }
    return true;
}