#include "UCSearch.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//vector for the frontier
std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> frontier;
std::vector<Node*> explored_set;
Node* currentNode;

void UCSearch(Node* startnode){
    //Uniform cost search but bfs style, path costs still 1
    if(startnode->checkIfGoal()) {
        cout<< "Start Node is already a goal state!\n";
    }
    //update g_n, no need to add h_n
    startnode->parent = nullptr;
    startnode->setg_n(0);
    startnode->seth_n(0);
    startnode->createChildren();

    frontier.push(startnode); //Add initial node to frontier

    // POP top, if goal state, end else create children and add those to frontier
    while(!frontier.top()->checkIfGoal()){
        if (std::find(explored_set.begin(), explored_set.end(), frontier.top()) != explored_set.end()) {
            frontier.pop();
        }
        else {
            currentNode = frontier.top();
            currentNode->createChildren();

            //Set g_n and h_n for children
            if (currentNode->up != nullptr) {
                currentNode->up->setg_n(currentNode->g_n + 1);
                currentNode->up->seth_n(0);
                currentNode->up->setoutput(currentNode->output + "^ ");
            }
            if (currentNode->down != nullptr) {
                currentNode->down->setg_n(currentNode->g_n + 1);
                currentNode->down->seth_n(0);
                currentNode->down->setoutput(currentNode->output + "v ");
            }
            if (currentNode->left != nullptr) {
                currentNode->left->setg_n(currentNode->g_n + 1);
                currentNode->left->seth_n(0);
                currentNode->left->setoutput(currentNode->output + "< ");
            }
            if (currentNode->right != nullptr) {
                currentNode->right->setg_n(currentNode->g_n + 1);
                currentNode->right->seth_n(0);
                currentNode->right->setoutput(currentNode->output + "> ");
            }

            //add top frontier to explored set and pop
            explored_set.push_back(frontier.top());
            frontier.pop();
            if (currentNode->up != nullptr) {
                frontier.push(currentNode->up);
            }
            if (currentNode->down != nullptr) {
                frontier.push(currentNode->down);
            }
            if (currentNode->left != nullptr) {
                frontier.push(currentNode->left);
            }
            if (currentNode->right != nullptr) {
                frontier.push(currentNode->right);
            }
        }
    }

    std::cout << "Solution is: \n";
    currentNode = frontier.top();
    currentNode->printOutput();
}

