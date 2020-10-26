#include "qtcount.h"
#include <cmath>

bool qtcount::prunable(Node * root, int tol) {
    /* Your code here */ 
    return prunableHelp(root,tol,root->avg); 
}

bool qtcount::prunableHelp(Node *  subroot, int tol, RGBAPixel aavg){
    if(subroot != NULL){
    if(subroot->NW == NULL){
        int dist = ((aavg.r - subroot->avg.r)*(aavg.r - subroot->avg.r) + 
                    (aavg.g - subroot->avg.g)*(aavg.g - subroot->avg.g) + 
                    (aavg.b - subroot->avg.b)*(aavg.b - subroot->avg.b)); 
        if(dist <= tol){
            return true; 
        } else{
            return false;  
        }
    } 
    }

    return (prunableHelp(subroot->NW, tol, aavg) && prunableHelp(subroot->NE, tol, aavg) &&
            prunableHelp(subroot->SE, tol, aavg) && prunableHelp(subroot->SW, tol, aavg));
}

