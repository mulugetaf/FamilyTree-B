#include <string>
#include <iostream>
#include <stdbool.h>
using namespace std;

namespace family
{
class Node
{
public:
    Node(string name);
    Node();
    string name;
    string gender;
    int depth;
    Node *mother;
    Node *father;
};

class Tree
{

public:
    Tree(string name);
    Tree();
    Node *root;
    Node *helpfind(Node *r, string name);
    Tree &addFather(string name1, string name2);
    Tree &addMother(string name1, string name2);
    string relation(string name);
    string find(string name);
    void remove(string name);
    void display();
    void print2DUtil(Node *root, int space);
    void deleteTree(Node *r);
    int getLevelUtil(Node *root, string name, int level);
    int getLevel(Node *node, string data);
};

};