#include "node.h"

void Node::setBoard(int array[BOARD_SIZE_X][BOARD_SIZE_Y]) {
    for(int i = 0; i < BOARD_SIZE_X; ++i){
        for(int j = 0; j < BOARD_SIZE_Y; ++j){
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
    this->up = new Node();
    this->down = new Node();
    this->left = new Node();
    this->right = new Node();
}