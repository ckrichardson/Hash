#include "BSTree.h"


/**
@Brief This is the default constructor
*/

template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree()
{
  root = NULL;
}

/**
@Brief This is the parameterized constructor
*/

template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree( const BSTree<DataType,KeyType>& other )
{
  copy_helper(root, other.root);
}

/**
@Brief this is the overloaded equal operator
*/

template<typename DataType, class KeyType>
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator=( const BSTree<DataType, KeyType>& other)
{
  if(&this == NULL)
  {}
  else
  {
    clear_helper(root);
    copy_helper(root, other.root);
  }


  return (*this);
}

/**
@Brief this is the destructor
*/
template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::~BSTree()
{
  clear_helper(root);
}


/**
@Brief This inserts a new node using a helper
*/
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insert ( const DataType & newDataItem )
{
  insert_helper(root, newDataItem);
}


/**
@Brief Helper for insert
*/

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insert_helper(BSTreeNode *&current, const DataType &newDataItem)
{
  if(current == NULL)
  {
    current = new BSTreeNode(newDataItem, NULL, NULL);
    return;
  }

  if(current->dataItem.getKey() == newDataItem.getKey())
  {
    current->dataItem = newDataItem;
  }
  else if(newDataItem.getKey() < current->dataItem.getKey())
  {
    insert_helper(current->left, newDataItem);
  }
  else if(newDataItem.getKey() > current->dataItem.getKey())
  {
    insert_helper(current->right, newDataItem);
  }
}

/**
@Brief This retrieves a node's data
*/

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
  return retrieve_helper(root, searchKey, searchDataItem);
}


/**
@Brief Helper for retrieve
*/
template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve_helper(BSTreeNode *current, const KeyType& searchKey, DataType& searchDataItem) const
{
  if(current == NULL)
  {
    return false;
  }
  if(current->dataItem.getKey() == searchKey)
  {
    searchDataItem = current->dataItem;
    return true;
  }
  else
  {
    return retrieve_helper(current->left, searchKey, searchDataItem) ||
    retrieve_helper(current->right, searchKey, searchDataItem);

  }
}

/**
@Brief this removes a node
*/

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::remove ( const KeyType & deleteKey )
{
  return remove_helper(root, root, deleteKey);
}


/**
@Brief This is the helper function for remove
*/
template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::remove_helper(BSTreeNode *&current, BSTreeNode *&prior, const KeyType& deleteKey)
{
  if(current == NULL)
    return false;

  if(deleteKey == current->dataItem.getKey())
  {
    if(current->right == NULL)
    {
      if(current != root)
      {
        BSTreeNode* temp = current->left;
        delete current;
        prior->left = temp;
        return true;
      }
      else
      {
        BSTreeNode* temp = current;
        current = current->left;
        delete temp;
        return true;
      }

    }
    if(current->left == NULL)
    {
      if(current != root)
      {
        BSTreeNode* temp = current->right;
        delete current;
        prior->right = temp;
        return true;
      }
      else
      {
        BSTreeNode* temp = current;
        current = current->right;
        delete temp;
        return true;
      }

    }
    BSTreeNode* temp = current;
    temp = temp->left;
    while(temp->right)
      temp = temp->right;
    current->dataItem = temp->dataItem;
    current->dataItem.setKey(temp->dataItem.getKey());
    delete temp;
    temp = NULL;
    return remove_helper(current, current->right, deleteKey);
  }

  return(remove_helper(current->left, current, deleteKey) || remove_helper(current->right, current, deleteKey));




}

/**
@Brief this will write the keys
*/
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys () const{
  writeKeys_helper(root);
  cout << endl;
}

/**
@Brief This is the helper for writeKeys()
*/
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys_helper(BSTreeNode *current) const
{
  if(current == NULL)
    return;
  writeKeys_helper(current->left);
  cout << current->dataItem.getKey() << " ";
  writeKeys_helper(current->right);
  return;
}

/**
@Brief this is the function that clears the tree
*/
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear ()
{
  clear_helper(root);
}

/**
@Brief Checks if tree is Empty
*/

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::isEmpty() const
{
  if(root == NULL)
    return true;
  return false;
}

/**
@Brief Irrelevant garbage
*/

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const
{

}


/**
@Brief Constructor for BSTreeNode
*/
template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
  dataItem = nodeDataItem;
  right = rightPtr;
  left = leftPtr;
}


/**
@Brief Helper for operator= and copy Constructor
*/
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copy_helper(BSTreeNode*& ours, BSTreeNode* theirs)
{
  if(theirs == NULL)
    return;

  ours = new BSTreeNode(theirs->dataItem, NULL, NULL);
  copy_helper(ours->left, theirs->left);
  copy_helper(ours->right, theirs->right);

  return;
}

/**
@Brief function for clear*/
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear_helper(BSTreeNode*& current)
{
  if(current == NULL)
    return;

  clear_helper(current->left);
  clear_helper(current->right);

  delete current;
  current = NULL;

  return;
}

/**
@Brief This shows the structure of the BSTree
*/

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
@Brief This is the helper for the showStructure
*/

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const

// Recursive helper for showStructure.
// Outputs the subtree whose root node is pointed to by p.
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}

/**
@Brief This gets the height of the tree
*/

template<typename DataType, typename KeyType>
int BSTree<DataType, KeyType>::getHeight() const
{
  height_helper(root, 0);
}


/**
@Brief This is the helper for the getHeight()
*/
template<typename DataType, typename KeyType>
int BSTree<DataType, KeyType>::height_helper(BSTreeNode* current, int height) const
{
  if(current == NULL)
  {
    return height;
  }
  else
  {
      return max(height_helper(current->left, height+1), height_helper(current->right, height+1));

  }
}

/**
@Brief This gets the number of nodes in the tree
*/

template<typename DataType, typename KeyType>
int BSTree<DataType, KeyType>::getCount() const
{
  return count_helper(root);
}

/**
@Brief This is the helper for the getCount()
*/
template<typename DataType, typename KeyType>
int BSTree<DataType, KeyType>::count_helper(BSTreeNode* current) const
{
  if(current == NULL)
    return 0;
  else{
    return 1 + count_helper(current->left) + count_helper(current->right);
  }
}
