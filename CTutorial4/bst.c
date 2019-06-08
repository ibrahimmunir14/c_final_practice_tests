#include <stdio.h>
#include <stdlib.h>

typedef struct _BSTNode BSTNode;

struct _BSTNode{
 int key;
 BSTNode* left;
 BSTNode* right;
};

void printBST(BSTNode* node, int level, char type);
BSTNode * findmin(BSTNode* node);
BSTNode * findmax(BSTNode* node);
BSTNode * insert(int key, BSTNode* node);
BSTNode* delete(int key, BSTNode* node);
void freeBST(BSTNode* node);
BSTNode* findkey(int key, BSTNode* node);

int main(void) {
  BSTNode* root = insert(5,NULL);
  insert(3,root);
  insert(7,root);
  insert(1,root);
  insert(4,root);
  insert(9,root);
  insert(10,root);
  printBST(root,1,'I');
  BSTNode *test = findkey(7,root);
  printf("The node is %d\n",test->key);

  printf("\n\nDeleting leaf 10\n");
  delete(10, root);
  printBST(root,1,'I');

  printf("\n\nDeleting 7\n");
  delete(7, root);
  printBST(root,1,'I');

  printf("\n\nDeleting 3\n");
  delete(3, root);
  printBST(root,1,'I');

  printf("\n\nDeleting root 5\n");
  delete(5, root);
  printBST(root,1,'I');

  freeBST(root);
  return EXIT_SUCCESS;
}

void printBST(BSTNode* node, int level, char type) {
  int count;
  if (node==NULL) {return;}
  for (count=0; count<=level; count++) { printf(" "); }
  printf("->(%c) %d\n", type, node->key);
  printBST(node->left, level+1, 'L');
  printBST(node->right, level+1, 'R');
}

BSTNode* findmin(BSTNode* node) {
  if(node==NULL) {return NULL;}
  if(node->left == NULL) {return node;}
  return findmin(node->left);
}

BSTNode* findmax(BSTNode* node) {
  if(node==NULL) {return NULL;}
  if(node->right ==NULL) {return node;}
  return findmax(node->right);
}

BSTNode* findkey(int key, BSTNode* node) {
  if(node == NULL) {
    return NULL;
  }
  else if(node->key == key){
    return node;
  }else if(key < node->key){
    node = findkey(key,node->left);
  }else if(key > node->key){
    node = findkey(key,node->right);
  }
  return node;
}

BSTNode* insert(int key, BSTNode* node) {
  if( node == NULL ){
    node = malloc( sizeof( BSTNode ) );
    if( node == NULL ){
      perror( "malloc" ); exit(1);
    }
    else{
      node->key = key;
      node->left = node->right = NULL;
    }
  }
  else if( key < node->key )
    node->left = insert(key, node->left );
  else if( key > node->key )
    node->right = insert(key, node->right );
  return node;
}

// BSTNode* delete(int key, BSTNode* node) {
//   if(node->left == NULL && node->right == NULL){
//     free(node);
//   } else if (node->left != NULL && node->right == NULL) {
//   } else if (node->left == NULL && node->right != NULL) {
//   } else {
//     findmin(node->right);
//   }
//   return node;
// }

void freeBST(BSTNode* node){
  if(node==NULL) return;
  freeBST(node->left);
  freeBST(node->right);
  free(node);
}

// Question 2
BSTNode* delete(int key, BSTNode* node) {
  if (key < node->key) { // go to left subtree
    if (node->left == NULL) return node;
    node->left = delete(key, node->left);
    return node;
  } else if (key > node -> key) { // go to right subtree
    if (node->right == NULL) return node;
    node->right = delete(key, node->right);
    return node;
  } else { // found the key at this node
    if (node->left == NULL && node->right == NULL) { // is leaf
      return NULL;
    } else if (node->left == NULL && node->right != NULL) { // has right subtree only
      BSTNode* right = node->right;
      free(node);
      return right;
    } else if (node->left != NULL && node->right == NULL) { // has left subtree only
      BSTNode* left = node->left;
      free(node);
      return left;
    } else { // has left and right subtree
      BSTNode* rightMin = findmin(node->right);
      node->key = rightMin->key;
      node->right = delete(node->key, node->right);
      return node;
    }
  }
}