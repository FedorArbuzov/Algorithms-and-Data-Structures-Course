//
// Created by user on 28.11.2016.
//
/*
 * Define Node Class for HR
 */
class Node
{
public:
    int a;
    char c;
    Node *left, *right;

    Node(){left=right= nullptr;}

    Node(Node *L, Node *R)
    {  left =  L;
        right = R;
        a = L->a + R->a;  }
};
/*
 * End Node Class for HR
 */



