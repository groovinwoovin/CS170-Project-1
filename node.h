#ifndef __NODE_H__
#define __NODE_H__

extern const int BOARD_SIZE_X = 3;
extern const int BOARD_SIZE_Y = 3;

class Node {
public:
    int board[BOARD_SIZE_X][BOARD_SIZE_Y];
    int g_n;
    int h_n;

    Node();
    void setBoard(int array[BOARD_SIZE_X][BOARD_SIZE_Y]);
    void setg_n(int g);
    void seth_n(int h);
    void createChildren();

    Node* parent;

    Node* up;
    Node* down;
    Node* left;
    Node* right;
};

#endif //__NODE_H__