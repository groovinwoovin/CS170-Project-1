#include "UCSearch.h"
//#include "ASMTHeuristic.h"
//#include "ASEDHeuristic.h"
#include "node.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    int board[BOARD_SIZE_X][BOARD_SIZE_Y];
    string puzzleinput;
    int useroption;

    cout<< "Welcome to 862039652's 8 puzzle solver!\n";
    cout<< "Enter your puzzle, using a zero to represent the blank\n";
    std::getline(cin, puzzleinput);

    //cut up temp and insert into array
    for(int i = 0; i < BOARD_SIZE_X; ++i) {
        for(int j = 0; j < BOARD_SIZE_Y; ++j){
            int index = puzzleinput.find(" ");
            //if(index == string::npos) { return false; }
            board[i][j] = stoi(puzzleinput.substr(0, index));
            puzzleinput = puzzleinput.substr(index + 1);
        }
    }

    cout<< "Enter your choice of algorithm:\n"
        << "1) Uniform Cost Search\n"
        << "2) A* with Misplaced Tile heuristic\n"
        << "3) A* with Euclidian Distance heuristic\n";
    cin>> useroption;

    //generate start node
    Node *startNode = new Node(board);

    switch(useroption){
        case 1:
            cout<< "Running Uniform Cost Search...\n";
            //call function
            UCSearch(startnode);
            break;
        case 2:
            cout<< "Running A* with Misplaced Tile heuristic...\n";
            break;
        case 3:
            cout<< "Running A* with Euclidian Distance heuristic...\n";
            break;
        default:
            cout<< "That was not an option\n"; 
    }

    return 0;   
}
