#include "FamilyTree.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <stdbool.h>
#include <iomanip>
using namespace std;
using namespace family;
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
  Node* child_found = findNode(root, child);
  if (child_found->name == "")
  {
    throw std::invalid_argument("child not found");
  }
  else if (child_found->father != NULL)
  {
    throw std::invalid_argument("father allready inserted");
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
  Node* child_found = findNode(root, child);
  if (child_found->name == "")
  {
    throw std::invalid_argument("child not found");
  }
  else if (child_found->mother != NULL)
  {
    throw std::invalid_argument("mother allready inserted");
  }
  else
  {
    child_found->mother = new Node(mother);
    child_found->mother->gender = "female";
    child_found->depth = getLevel(root, child);
    return *this;
  }
};

//display print all nodes and parent
void family::Tree::display()
{
  inorder(root);
};

//add realtion
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
string family::Tree::find(string name)
{
  Node *ans = helpfind(root, name);
  if (relation(ans->name) == name)
  {
    return ans->name;
  }
  else
  {
    throw std::invalid_argument(name +" not found in the tree");
  }
  
  return "";
};

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
void family::Tree::remove(string name)
{
  Node *toremove = findNode(root, name);
  if(toremove->name == "")
  {
  throw std::invalid_argument(name +" not found in the tree");
  }
  if(toremove->name == root->name){
    throw std::invalid_argument(name +" is root");
  }
  deleteTree(toremove);
};
void family::Tree::deleteTree(Node *node)
{
  if (node == NULL)
    return;

  /* first delete both subtrees */
  deleteTree(node->mother);
  deleteTree(node->father);

  /* then delete the node */
  cout << "\n Deleting node: " << node->name << endl;
  free(node);
};
//Node constructor
family::Node::Node(string Node_name)
{
  name = Node_name;
  father = NULL;
  mother = NULL;
};
//Node
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
//defualt
family::Tree::Tree()
{
  root = NULL;
};
//print all nodes
void ::family::Tree::inorder(Node *p)
{
  if (p != NULL)
  {
    inorder(p->mother);
    cout << p->name << " ";
    inorder(p->father);
  }
  return;
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
/*
int main()
{
  Tree T("Yosef");
  T.addFather("Yosef", "Yaakov")    // Tells the tree that the father of Yosef is Yaakov.
      .addMother("Yosef", "Rachel") // Tells the tree that the mother of Yosef is Rachel.
      .addFather("Yaakov", "Isaac")
      .addMother("Yaakov", "Rivka")
      .addFather("Isaac", "Avraham")
      .addFather("Avraham", "Terah");

  cout << T.relation("Yaakov") << endl;
  cout << T.relation("Rachel") << endl;
  cout << T.relation("Isaac") << endl;
  cout << T.relation("Rivka") << endl;
  cout << T.relation("Avraham") << endl;
  cout << T.relation("Terah") << endl;

  //cout << T.relation("Rachel") << endl;
   //T.remove("Yosef");
   T.remove(" ");
  // cout << T.relation("Yaakov") << endl;
  // cout << T.relation("Rachel") << endl;
  // cout << T.relation("Rivka") << endl;
  // cout << T.relation("Isaac") << endl;
  // cout << T.relation("Avraham") << endl;
  // // cout << T.relation("Terah") << endl;
  // T.remove("Isaac");
  // T.remove("Rivka");
  // T.remove("Avraham");
  // T.remove("Terah");

  // cout << endl;
  // cout << endl;
  // cout << endl;
  // cout << T.find("mother") << endl;
  // cout << T.find("grandfather") << endl;
  // cout << T.find("grandmother") << endl;
  // cout << T.find("great-grandfather") << endl;
  // cout << T.find("great-grandmother") << endl;
  // cout << T.find("great-great-grandfather") << endl;
  // cout << T.find("great-great-great-grandmother") << endl;
  // cout << T.find("great-great-great-grandfather") << endl;
  // cout << T.find("great-great-great-grandfather") << endl;

  return 0;
}
*/