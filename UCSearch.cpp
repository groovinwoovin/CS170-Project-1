#include "UCSearch.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//vector for the frontier
std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> frontier;
Node* currentNode;

void UCSearch(Node* startnode){
    //Uniform cost search but bfs style, path costs still 1
    if(checkIfGoal(startnode)) {
        cout<< "Start Node is already a goal state!\n";
    }
    //update g_n, no need to add h_n
    startnode->parent = nullptr;
    startnode->setg_n(0);
    startnode->seth_n(0);
    startnode->createChildren();

    frontier.push(startnode);

    while(!checkIfGoal(frontier.top())){
        currentNode = frontier.top();
        currentNode->createChildren();
        frontier.pop();
        if(currentNode->up != nullptr){
            frontier.push(currentNode->up);
        }
        if(currentNode->down != nullptr){
            frontier.push(currentNode->down);
        }
        if(currentNode->left != nullptr){
            frontier.push(currentNode->left);
        }
        if(currentNode->right != nullptr){
            frontier.push(currentNode->right);
        }
    }

    currentNode = frontier.top();
    while(currentNode->parent != nullptr){
        currentNode->printNode();
        currentNode = currentNode->parent;
    }

    
    //go through frontier in order
    
    //check if goal state
    //if goal state, print goal state
    //if not goal state, create children and traverse the node


    //set currentnode to startnode
    //add currentnode to frontier
    //while solution isnt found
    //pop frontier, add to explored
    //create children, add to frontier
}

bool checkIfGoal(Node* node) {
    //node->printNode();
    int tempTile = node->board[0][0];

    for(int i = 0; i < NODE_BOARD_SIZE_X; ++i) {
        for(int j = 0; j < NODE_BOARD_SIZE_Y; ++j) {
            if(tempTile > node->board[i][j]) {
                if(i >= NODE_BOARD_SIZE_X - 1 && j >= NODE_BOARD_SIZE_Y - 1) { // implied last tile is 0
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                tempTile = node->board[i][j];
            }
        }
    }
    return true;
}