#include "AstarED.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//vector for the frontier
std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> EDfrontier;
std::vector<Node*> explored_set_ED;
Node* currentNodeED;

void AstarED(Node* startnode) {
    //Uniform cost search but bfs style, path costs still 1
    if (startnode->checkIfGoal()) {
        cout << "Start Node is already a goal state!\n";
    }
    //update g_n, no need to add h_n
    startnode->parent = nullptr;
    startnode->setg_n(0);
    startnode->seth_n(calculateEDHeuristic(startnode));
    startnode->createChildren();

    EDfrontier.push(startnode); //Add initial node to frontier

    // POP top, if goal state, end else create children and add those to frontier
    while (!EDfrontier.top()->checkIfGoal()) {
        if (std::find(explored_set_ED.begin(), explored_set_ED.end(), EDfrontier.top()) != explored_set_ED.end()) {
            EDfrontier.pop();
        }
        else {
            currentNodeED = EDfrontier.top();
            currentNodeED->createChildren();

            //Set g_n and h_n for children
            if (currentNodeED->up != nullptr) {
                currentNodeED->up->setg_n(currentNodeED->g_n + 1);
                currentNodeED->up->seth_n(calculateEDHeuristic(currentNodeED->up));
                currentNodeED->up->setoutput(currentNodeED->output + "^ ");
            }
            if (currentNodeED->down != nullptr) {
                currentNodeED->down->setg_n(currentNodeED->g_n + 1);
                currentNodeED->down->seth_n(calculateEDHeuristic(currentNodeED->up));
                currentNodeED->down->setoutput(currentNodeED->output + "v ");
            }
            if (currentNodeED->left != nullptr) {
                currentNodeED->left->setg_n(currentNodeED->g_n + 1);
                currentNodeED->left->seth_n(calculateEDHeuristic(currentNodeED->up));
                currentNodeED->left->setoutput(currentNodeED->output + "< ");
            }
            if (currentNodeED->right != nullptr) {
                currentNodeED->right->setg_n(currentNodeED->g_n + 1);
                currentNodeED->right->seth_n(calculateEDHeuristic(currentNodeED->up));
                currentNodeED->right->setoutput(currentNodeED->output + "> ");
            }

            //add top frontier to explored set and pop
            explored_set_ED.push_back(EDfrontier.top());
            EDfrontier.pop();
            if (currentNodeED->up != nullptr) {
                EDfrontier.push(currentNodeED->up);
            }
            if (currentNodeED->down != nullptr) {
                EDfrontier.push(currentNodeED->down);
            }
            if (currentNodeED->left != nullptr) {
                EDfrontier.push(currentNodeED->left);
            }
            if (currentNodeED->right != nullptr) {
                EDfrontier.push(currentNodeED->right);
            }
        }
    }

    std::cout << "Solution is: \n";
    currentNodeED = EDfrontier.top();
    currentNodeED->printOutput();
}

double calculateEDHeuristic(Node* node) {
    double heuristicTotal = 0.0;
    int x_dist = 0;
    int y_dist = 0;
    for (int i = 0; i < NODE_BOARD_SIZE_X; ++i) {
        for (int j = 0; j < NODE_BOARD_SIZE_Y; ++j) {
            if (node->board != 0 && node->board[i][j] != ((i * NODE_BOARD_SIZE_X) + j) + 1) {
                //get where tile is supposed to be
                x_dist = ((node->board[i][j] - 1) % NODE_BOARD_SIZE_X);
                y_dist = ((node->board[i][j] - 1) / NODE_BOARD_SIZE_X);

                //get how far the tile is from where it should be
                x_dist = abs(x_dist - (j));
                y_dist = abs(y_dist - (i));

                //calculate and add euclidean distance
                heuristicTotal += sqrt((x_dist * x_dist) + (y_dist * y_dist));
            }
        }
    }
    return heuristicTotal;
}