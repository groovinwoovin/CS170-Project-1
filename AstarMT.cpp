#include "AstarMT.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//vector for the frontier
std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> MTfrontier;
std::vector<Node*> explored_set_MT;
Node* currentNodeMT;

void AstarMT(Node* startnode) {
    //Uniform cost search but bfs style, path costs still 1
    if (startnode->checkIfGoal()) {
        cout << "Start Node is already a goal state!\n";
    }
    //update g_n, no need to add h_n
    startnode->parent = nullptr;
    startnode->setg_n(0);
    startnode->seth_n(calculateMTHeuristic(startnode));
    startnode->createChildren();

    MTfrontier.push(startnode); //Add initial node to frontier

    // POP top, if goal state, end else create children and add those to frontier
    while (!MTfrontier.top()->checkIfGoal()) {
        if (std::find(explored_set_MT.begin(), explored_set_MT.end(), MTfrontier.top()) != explored_set_MT.end()) {
            MTfrontier.pop();
        }
        else {
            currentNodeMT = MTfrontier.top();
            currentNodeMT->createChildren();

            //Set g_n and h_n for children
            if (currentNodeMT->up != nullptr) {
                currentNodeMT->up->setg_n(currentNodeMT->g_n + 1);
                currentNodeMT->up->seth_n(calculateMTHeuristic(currentNodeMT->up));
                currentNodeMT->up->setoutput(currentNodeMT->output + "^ ");
            }
            if (currentNodeMT->down != nullptr) {
                currentNodeMT->down->setg_n(currentNodeMT->g_n + 1);
                currentNodeMT->down->seth_n(calculateMTHeuristic(currentNodeMT->down));
                currentNodeMT->down->setoutput(currentNodeMT->output + "v ");
            }
            if (currentNodeMT->left != nullptr) {
                currentNodeMT->left->setg_n(currentNodeMT->g_n + 1);
                currentNodeMT->left->seth_n(calculateMTHeuristic(currentNodeMT->left));
                currentNodeMT->left->setoutput(currentNodeMT->output + "< ");
            }
            if (currentNodeMT->right != nullptr) {
                currentNodeMT->right->setg_n(currentNodeMT->g_n + 1);
                currentNodeMT->right->seth_n(calculateMTHeuristic(currentNodeMT->right));
                currentNodeMT->right->setoutput(currentNodeMT->output + "> ");
            }

            //add top frontier to explored set and pop
            explored_set_MT.push_back(MTfrontier.top());
            MTfrontier.pop();
            if (currentNodeMT->up != nullptr) {
                MTfrontier.push(currentNodeMT->up);
            }
            if (currentNodeMT->down != nullptr) {
                MTfrontier.push(currentNodeMT->down);
            }
            if (currentNodeMT->left != nullptr) {
                MTfrontier.push(currentNodeMT->left);
            }
            if (currentNodeMT->right != nullptr) {
                MTfrontier.push(currentNodeMT->right);
            }
        }
    }

    std::cout << "Solution is: \n";
    currentNodeMT = MTfrontier.top();
    currentNodeMT->printOutput();
}

int calculateMTHeuristic(Node* node) {
    int heuristicTotal = 0;
    for (int i = 0; i < NODE_BOARD_SIZE_X; ++i) {
        for (int j = 0; j < NODE_BOARD_SIZE_Y; ++j) {
            if (node->board[i][j] != ((i * NODE_BOARD_SIZE_X) + j) + 1) {
                heuristicTotal++;
            }
        }
    }
    return heuristicTotal;
}