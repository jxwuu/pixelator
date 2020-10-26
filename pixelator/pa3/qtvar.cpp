#include "qtvar.h"

bool qtvar::prunable(Node * root, int tol) {
    /* Your code here! */
    if(tol == 0){
      return false; 
    }
  return root->var < tol; 
}
