
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
#include <cmath>
using namespace std;


// Node constructor, given.
quadtree::Node::Node(pair<int,int> ul, int d,RGBAPixel a, double v)
	:upLeft(ul),dim(d),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

// quadtree destructor, given.
quadtree::~quadtree() {
	clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree & other) {
	copy(other);
}
// quadtree assignment operator, given.
quadtree & quadtree::operator=(const quadtree & rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}


quadtree::quadtree(PNG & imIn) {
        /* Your code here! */
		// cout<<"qqtree"<<endl; 
		int width = imIn.width();
		if(imIn.width()>imIn.height()){
			width = imIn.height(); 
		}
		stats s(imIn); 
		pair<int,int> ul = make_pair(0,0); 
		int dim = log2(width); 
		edge = pow(2,dim); 
		root = buildTree(s, ul, dim); 
        // int c = (pow(4,(log2(edge) + 1.0))-1.0)/(4.0 -1); 
        // cout <<c; 

}


quadtree::Node * quadtree::buildTree(stats & s, pair<int,int> & ul, int dim) {
        /* Your code here! */
    
		RGBAPixel a = s.getAvg(ul, dim); 
		Node* node = new Node(ul, dim, a, s.getVar(ul, dim));
        if(dim<0){
            return node; 
        }
		int x = ul.first; 
		int y = ul.second; 
		int new_dim = dim - 1; 
		int length = pow(2, new_dim) ; 
        // b++; 
        // cout<<b; 
        // cout<<"    "; 
		
		pair<int,int> NW_ul; 
		pair<int,int> NE_ul; 
		pair<int,int> SE_ul; 
		pair<int,int> SW_ul; 

		if(new_dim >= 0){
			NW_ul = make_pair(x , y );
			NE_ul = make_pair(x + length, y );
			SE_ul = make_pair(x + length , y + length);
			SW_ul = make_pair(x , y + length);
			node->NW = buildTree(s, NW_ul, new_dim); 
			node->NE = buildTree(s, NE_ul, new_dim); 
			node->SE = buildTree(s, SE_ul, new_dim); 
			node->SW = buildTree(s, SW_ul, new_dim); 
		}
		return node; 
}


PNG quadtree::render() {
        /* Your code here! */
		// cout<<"render"<<endl; 
		PNG pic(edge, edge); 
		renderHelp(pic, root); 
		return pic; 
}

void quadtree::renderHelp(PNG &png, Node* subroot){

	if(subroot->NW == NULL){
		int x = subroot->upLeft.first; 
		int y = subroot->upLeft.second; 

		int length = pow(2, subroot->dim); 
		int endx = x + length; 
		int endy = y + length; 
		for(int i = x; i<endx; i++){
			for(int j = y; j<endy; j++){
				*png.getPixel(i,j) = subroot->avg;  
			}
		}
	} else {
		renderHelp(png, subroot->NW); 
		renderHelp(png, subroot->NE); 
		renderHelp(png, subroot->SE); 
		renderHelp(png, subroot->SW); 
	} 
			
}

int quadtree::idealPrune(int leaves){
        /* Your code here! */
	int tol = 1; 
	while(pruneSize(tol) > leaves){
		tol ++; 
	}
	return tol; 

}

int quadtree::pruneSize(int tol){
        /* Your code here! */
	return pruneSizeHelp(root,tol); 
}

int quadtree::pruneSizeHelp(Node* subroot, int tol){
	if(subroot->NW == NULL){
		return 1; 
	}
	if(prunable(subroot,tol)){
		return 1; 
	} 
	return pruneSizeHelp(subroot->NW,tol) + pruneSizeHelp(subroot->NE,tol) + 
			pruneSizeHelp(subroot->SE,tol) + pruneSizeHelp(subroot->SW,tol); 
}

void quadtree::prune(int tol){
        /* Your code here! */

		pruneHelp(tol, root); 
}

void quadtree::pruneHelp(int tol, Node* subroot){
	if(subroot == NULL){
		return;  
	}
		if(prunable(subroot,tol)){
			clearHelp(subroot->NW); 
			clearHelp(subroot->NE);  
			clearHelp(subroot->SE); 
			clearHelp(subroot->SW);
		}
	pruneHelp(tol,subroot->NW);
	pruneHelp(tol,subroot->NE);
	pruneHelp(tol,subroot->SE);
	pruneHelp(tol,subroot->SW);
}

void quadtree::clear() {
/* your code here */
// cout<<"clear"<<endl; 
	clearHelp(root); 
}

void quadtree::clearHelp(Node* & subroot){
	if(subroot == NULL){
		delete subroot; 
		return; 
	}
		clearHelp(subroot->NW);
		clearHelp(subroot->NE);
		clearHelp(subroot->SE);
		clearHelp(subroot->SW);
		delete subroot;
		subroot = NULL;   
}

void quadtree::copy(const quadtree & orig){
	// cout<<"copy"<<endl; 
/* your code here */
	root = nodeCopy(orig.root); 
	edge = pow(2,orig.root->dim); 
}

quadtree::Node* quadtree:: nodeCopy(Node* subroot){
	if(subroot == NULL){
		return NULL; 
	}

	Node* insert = new Node(subroot->upLeft, subroot->dim, subroot->avg, subroot->var); 
	insert->NW = nodeCopy(subroot->NW); 
	insert->NE = nodeCopy(subroot->NE); 
	insert->SE = nodeCopy(subroot->SE); 
	insert->SW = nodeCopy(subroot->SW); 
	return insert;
} 
