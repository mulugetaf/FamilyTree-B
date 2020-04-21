#include "FamilyTree.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;
using namespace family;
/*
findNode function
search node name in the tree and return 
node pointer
*/
Node *findNode(Node *r, string child_name)
{
  string s = "";
  Node *t = new Node(s);
  if (r == NULL)
    return t;

  if (r->name == child_name)
    return r;

  /* then recur on left sutree */
  Node *res1 = findNode(r->mother, child_name);

  if (res1->name == child_name)
    return res1; // node found, no need to look further

  /* node is not found in left, so recur on right subtree */
  Node *res2 = findNode(r->father, child_name);

  return res2;
};
//helpfind

/*
addFather function 
add father to given node name
*if node not exist in the tree will throw exception
*if node allready has a father will throw exception
*/
family::Tree &Tree::addFather(string child, string father)
{
  Node *child_found = findNode(root, child);
  if (child_found->name == "")
  {
    throw std::invalid_argument("child not found");
  }
  else if (child_found->father != NULL)
  {
    throw std::invalid_argument("already has a father");
  }
  else
  {
    child_found->father = new Node(father);
    child_found->father->gender = "male";
    child_found->depth = getLevel(root, child);
    return *this;
  }
};

/*
addMother function 
add mother to given node name
*if node not exist in the tree will throw exception
*if node allready has a mother will throw exception
*/

family::Tree &Tree::addMother(string child, string mother)
{
  Node *child_found = findNode(root, child);
  if (child_found->name == "")
  {
    throw std::invalid_argument("child not found");
  }
  else if (child_found->mother != NULL)
  {
    throw std::invalid_argument("already has a mother");
  }
  else
  {
    child_found->mother = new Node(mother);
    child_found->mother->gender = "female";
    child_found->depth = getLevel(root, child);
    return *this;
  }
};

/*
display
using print2DUtil function to print 
all tree
*/
void family::Tree::display()
{
  print2DUtil(root, 0);
};
/*
print2DUtil
 Function to print binary tree in 2D  
 It does reverse inorder traversal 
 source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
*/
void family::Tree::print2DUtil(Node *root, int space)
{
  // Base case
  if (root == NULL)
    return;

  // Increase distance between levels
  space += 10;

  // Process right child first
  print2DUtil(root->father, space);

  // Print current node after space
  // count
  cout << endl;
  for (int i = 10; i < space; i++)
    cout << " ";
  cout << root->name << "\n";

  // Process left child
  print2DUtil(root->mother, space);
}

/*
  relation
  by givin node name
  search name in the tree and 
  returns - his relation to the root
  if givin name not in the tree
  return - unrelated
*/
string family::Tree::relation(string name)
{
  string father = "father";
  string mother = "mother";
  string grandF = "grandfather";
  string grandM = "grandmother";
  string great = "great";
  string temp = "great";
  Node *ans = findNode(root, name);

  if (ans->name == "")
  {
    return "unrelated";
  }
  int count = getLevel(root, ans->name);
  // cout << ans->name << endl;
  // cout << count << endl;
  // cout << ans->gender << "---" << endl;
  if (count == 0)
  {

    throw std::invalid_argument("unrelated");
  }

  else if (count == 1)
  {
    return "me";
  }
  else if (count == 2)
  {
    if (ans->gender == "male")
    {
      return father;
    }
    else if (ans->gender == "female")
    {
      return mother;
    }
  }
  else if (count == 3)
  {
    if (ans->gender == "male")
    {
      return grandF;
    }
    else if (ans->gender == "female")
    {
      return grandM;
    }
  }

  else if (count > 3)
  {
    while (count != 4)
    {
      temp = temp + "-" + great;
      count--;
    }
    if (ans->gender == "male")
    {
      return temp + "-" + grandF;
    }
    else if (ans->gender == "female")
    {
      return temp + "-" + grandM;
    }
  }
  return "unrelated";
}
/*
  find
  The opposite function
  by givin relation search node in the tree maintains relation
  using helpfind function
  return - node name from the tree that maintains relation.
  throw exception - if there is no node maintains relation. 
 */
string family::Tree::find(string name)
{
  Node *ans = helpfind(root, name);
  if (relation(ans->name) == name)
  {
    return ans->name;
  }
  else
  {
    throw std::invalid_argument(name + " not found in the tree");
  }

  return "";
};
/*
  helpfind
  return - node pointer that maintains givin 
  name relation
  */
Node *family::Tree::helpfind(Node *r, string name)
{
  string s = "";
  Node *t = new Node(s);
  if (r == NULL)
  {
    return t;
  }
  if ((relation(r->name)) == name)
  {
    return r;
  }

  /* then recur on left sutree */
  Node *res1 = helpfind(r->father, name);

  if ((relation(res1->name)) == name)
  {
    return res1; // node found, no need to look further
  }
  /* node is not found in left, so recur on right subtree */
  Node *res2 = helpfind(r->mother, name);

  return res2;
};
/*
  remove
  remove givin node from the tree and
  all parents.
  using deleteTree function to delete all parents.
  throw exception - if there is no node maintains givin name. 
*/
void family::Tree::remove(string name)
{
  Node *toremove = findNode(root, name);
  if (toremove->name == "")
  {
    throw std::invalid_argument(name + " not found in the tree");
  }
  if (toremove->name == root->name)
  {
    throw std::invalid_argument(name + " is root");
  }
  deleteTree(toremove);
};
/*
  deleteTree
  delete node and all parents.
*/
void family::Tree::deleteTree(Node *node)
{
  if (node == NULL)
    return;

  /* first delete both subtrees */
  deleteTree(node->mother);
  deleteTree(node->father);

  /* then delete the node */
  free(node);
};

/* Helper function for getLevel().  
It returns level of the data if data is 
present in tree, otherwise returns 0.*/
int family::Tree::getLevelUtil(Node *root, string name, int level)
{
  if (root == NULL)
    return 0;

  if (root->name == name)
    return level;

  int downlevel = getLevelUtil(root->mother, name, level + 1);
  if (downlevel != 0)
    return downlevel;

  downlevel = getLevelUtil(root->father, name, level + 1);
  return downlevel;
}

/* Returns level of given data value */
int family::Tree::getLevel(Node *node, string data)
{
  return getLevelUtil(node, data, 1);
}
//Node constructor
family::Node::Node(string Node_name)
{
  name = Node_name;
  father = NULL;
  mother = NULL;
};
//defualt Node C‫‪onstructor‬‬
family::Node::Node()
{
  name = nullptr;
  father = nullptr;
  mother = nullptr;
};

// Tree C‫‪onstructor‬‬
family::Tree::Tree(string name)
{
  root = new Node(name);
};
//defualt Tree Constructor
family::Tree::Tree()
{
  root = NULL;
};
