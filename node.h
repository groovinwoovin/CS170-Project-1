#ifndef __NODE_H__
#define __NODE_H__

const int NODE_BOARD_SIZE_X = 3;
const int NODE_BOARD_SIZE_Y = 3;

class Node {
public:
    int board[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y];
    int g_n;
    int h_n;

    Node();

    void setBoard(int array[NODE_BOARD_SIZE_X][NODE_BOARD_SIZE_Y]);
    void setg_n(int g);
    void seth_n(int h);
    void createChildren();
    void printNode();

    bool operator<(const Node& rhs) const;

    Node* parent;

    Node* up;
    Node* down;
    Node* left;
    Node* right;
};

#endif //__NODE_H__