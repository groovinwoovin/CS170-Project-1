#ifndef __NODE_H__
#define __NODE_H__
#include <string>

const int NODE_BOARD_SIZE_X = 3;
const int NODE_BOARD_SIZE_Y = 3;

class Node {
public:
    int board[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y];
    int g_n;
    int h_n;
    std::string output;

    //constructors
    Node();

    void setBoard(int array[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y]);
    void setg_n(int g);
    void seth_n(int h);
    void setoutput(std::string input);
    void createChildren();
    void printNode();
    void printOutput();

    bool operator<(const Node& rhs) const;
    bool checkIfGoal();

    Node* parent;

    Node* up;
    Node* down;
    Node* left;
    Node* right;

    //destructors

};

#endif //__NODE_H__