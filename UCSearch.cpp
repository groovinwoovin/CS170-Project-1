#include "UCSearch.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//vector for the frontier
std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> UCfrontier;
std::vector<Node*> explored_set_UC;

// toggle debugUC if you would like to see the queue size
std::vector<int> queuesizesUC;
bool debugUC = true;
int nodesExpUC = 0;

Node* currentNodeUC;

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

    UCfrontier.push(startnode); //Add initial node to frontier

    if (debugUC) { //debugUC
        queuesizesUC.push_back(UCfrontier.size());
    }

    // POP top, if goal state, end else create children and add those to frontier
    while(!UCfrontier.top()->checkIfGoal()){
        if (std::find(explored_set_UC.begin(), explored_set_UC.end(), UCfrontier.top()) != explored_set_UC.end()) {
            UCfrontier.pop();
        }
        else {
            currentNodeUC = UCfrontier.top();
            currentNodeUC->createChildren();
            
            if (debugUC) {
                nodesExpUC++;
            }

            //Set g_n and h_n for children
            if (currentNodeUC->up != nullptr) {
                currentNodeUC->up->setg_n(currentNodeUC->g_n + 1);
                currentNodeUC->up->seth_n(0);
                currentNodeUC->up->setoutput(currentNodeUC->output + "^ ");
            }
            if (currentNodeUC->down != nullptr) {
                currentNodeUC->down->setg_n(currentNodeUC->g_n + 1);
                currentNodeUC->down->seth_n(0);
                currentNodeUC->down->setoutput(currentNodeUC->output + "v ");
            }
            if (currentNodeUC->left != nullptr) {
                currentNodeUC->left->setg_n(currentNodeUC->g_n + 1);
                currentNodeUC->left->seth_n(0);
                currentNodeUC->left->setoutput(currentNodeUC->output + "< ");
            }
            if (currentNodeUC->right != nullptr) {
                currentNodeUC->right->setg_n(currentNodeUC->g_n + 1);
                currentNodeUC->right->seth_n(0);
                currentNodeUC->right->setoutput(currentNodeUC->output + "> ");
            }

            //add top frontier to explored set and pop
            explored_set_UC.push_back(UCfrontier.top());
            UCfrontier.pop();
            if (currentNodeUC->up != nullptr) {
                UCfrontier.push(currentNodeUC->up);
            }
            if (currentNodeUC->down != nullptr) {
                UCfrontier.push(currentNodeUC->down);
            }
            if (currentNodeUC->left != nullptr) {
                UCfrontier.push(currentNodeUC->left);
            }
            if (currentNodeUC->right != nullptr) {
                UCfrontier.push(currentNodeUC->right);
            }
        }
        if (debugUC) {
            queuesizesUC.push_back(UCfrontier.size());
        }
    }

    std::cout << "Solution is: \n";
    currentNodeUC = UCfrontier.top();
    currentNodeUC->printOutput();

    if (debugUC) {
        cout << "Max number of nodes is: " << *max_element(queuesizesUC.begin(), queuesizesUC.end());
        cout << "\nExpanded nodes is: " << nodesExpUC;
    }
}

