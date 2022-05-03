#ifndef __NODE_H__
#define __NODE_H__
#include <string>

//Change TOGETHER with main.cpp
const int NODE_BOARD_SIZE_X = 3;
const int NODE_BOARD_SIZE_Y = 3;

class Node {
public:
    int board[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y];
    double g_n;
    double h_n;
    std::string output;

    //constructors
    Node();

    //destructor
    ~Node();

    void setBoard(int array[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y]);
    void setg_n(double g);
    void seth_n(double h);
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
};

#endif //__NODE_H__