
#include "stats.h"
#include <cmath> 

//all tests pass 


stats::stats(PNG & im){
    cout<<"intiate stats"<<endl; 

/* Your code here!! */
    int height = im.height(); 
    int width = im.width(); 

    sumRed.clear();
	sumGreen.clear();
	sumBlue.clear();
	sumsqRed.clear();
	sumsqGreen.clear();
	sumsqBlue.clear();
    sumRed.resize(height, vector<long> (width,0));
    sumGreen.resize(height, vector<long> (width,0));
    sumBlue.resize(height, vector<long> (width,0));
    sumsqRed.resize(height, vector<long> (width,0));
    sumsqGreen.resize(height, vector<long> (width,0));
	sumsqBlue.resize(height, vector<long> (width,0));

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            RGBAPixel *px = im.getPixel(x,y);
            if(x == 0 && y == 0){ //intial square 
                sumRed[y][x] = px->r; 
                sumGreen[y][x] = px->g; 
                sumBlue[y][x] = px->b; 
                sumsqRed[y][x] = px->r * px->r; 
                sumsqGreen[y][x] = px->g * px->g; 
                sumsqBlue[y][x] = px->b * px->b; 
            } else if(x == 0 && y > 0 ){ // intial row 
                sumRed[y][x] = px->r + sumRed[y-1][x]; 
                sumGreen[y][x] = px->g + sumGreen[y-1][x]; 
                sumBlue[y][x] = px->b + sumBlue[y-1][x];  
                sumsqRed[y][x] = sumsqRed[y-1][x] + px->r * px->r; 
                sumsqGreen[y][x] = sumsqGreen[y-1][x] + px->g * px->g; 
                sumsqBlue[y][x] = sumsqBlue[y-1][x] + px->b * px->b; 
            } else if(y == 0 && x > 0 ){ //intial column 
                sumRed[y][x] = px->r + sumRed[y][x-1]; 
                sumGreen[y][x] = px->g + sumGreen[y][x-1]; 
                sumBlue[y][x] = px->b + sumBlue[y][x-1];  
                sumsqRed[y][x] = sumsqRed[y][x-1] + px->r * px->r; 
                sumsqGreen[y][x] = sumsqGreen[y][x-1] + px->g * px->g; 
                sumsqBlue[y][x] = sumsqBlue[y][x-1] + px->b * px->b; 
            } else { // the middles 
                sumRed[y][x] = px->r + sumRed[y][x-1] + sumRed[y-1][x] - sumRed[y-1][x-1]; 
                sumGreen[y][x] = px->g + sumGreen[y][x-1] + sumGreen[y-1][x] - sumGreen[y-1][x-1]; 
                sumBlue[y][x] = px->b + sumBlue[y][x-1] + sumBlue[y-1][x] - sumBlue[y-1][x-1];  
                sumsqRed[y][x] = sumsqRed[y][x-1] + sumsqRed[y-1][x] - sumsqRed[y-1][x-1] + px->r * px->r; 
                sumsqGreen[y][x] = sumsqGreen[y][x-1] + sumsqGreen[y-1][x] - sumsqGreen[y-1][x-1] + px->g * px->g; 
                sumsqBlue[y][x] = sumsqBlue[y][x-1] + sumsqBlue[y-1][x] - sumsqBlue[y-1][x-1] + px->b * px->b; 

            }
        }
    }

}

//tests pass
long stats::getSum(char channel, pair<int,int> ul, int dim){
/* Your code here!! */  
    int length = pow(2,dim) - 1; 
    long result;
    switch (channel){
        case 'r':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumRed[ul.second + length][ul.first + length];  
            } else if (ul.first == 0 ){
			    result = sumRed[ul.second + length][ul.first] - sumRed[ul.second - 1][ul.first + length];
            } else if (ul.second == 0){
			    result = sumRed[ul.second + length][ul.first] - sumRed[ul.second][ul.first - 1];
            } else {
                result = sumRed[ul.second + length][ul.first + length] +
                         sumRed[ul.second - 1][ul.first - 1] - 
                         sumRed[ul.second - 1][ul.first + length] - 
                         sumRed[ul.second + length][ul.first - 1]; 
            } 
            break;
        case 'g':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumGreen[ul.second + length][ul.first + length];  
            } else if (ul.first == 0 && ul.second != 0){
			    result = sumGreen[ul.second + length][ul.first] - sumGreen[ul.second - 1][ul.first + length];
            } else if (ul.first != 0 && ul.second == 0){
			    result = sumGreen[ul.second + length][ul.first] - sumGreen[ul.second][ul.first - 1];
            } else {
                result = sumGreen[ul.second + length][ul.first + length] +
                         sumGreen[ul.second - 1][ul.first - 1] - 
                         sumGreen[ul.second - 1][ul.first + length] - 
                         sumGreen[ul.second + length][ul.first - 1]; 
            }  
            break;
        case 'b':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumBlue[ul.second + length][ul.first + length];  
            } else if (ul.first == 0 && ul.second != 0){
			    result = sumBlue[ul.second + length][ul.first] - sumBlue[ul.second - 1][ul.first + length];
            } else if (ul.first != 0 && ul.second == 0){
			    result = sumBlue[ul.second + length][ul.first] - sumBlue[ul.second][ul.first - 1];
            } else {
                result = sumBlue[ul.second + length][ul.first + length] +
                         sumBlue[ul.second - 1][ul.first - 1] - 
                         sumBlue[ul.second - 1][ul.first + length] - 
                         sumBlue[ul.second + length][ul.first - 1]; 
            } 
            break;
        default:
        return 0;
    }
    return result; 
}

//tests pass
long stats::getSumSq(char channel, pair<int,int> ul, int dim){
/* Your code here!! */
    int length = pow(2,dim) - 1; 
    long result;
      switch (channel){
        case 'r':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumsqRed[ul.second + length][ul.first + length];  
            } else if (ul.first == 0 && ul.second != 0){
			    result = sumsqRed[ul.second + length][ul.first] - sumsqRed[ul.second - 1][ul.first + length];
            } else if (ul.first != 0 && ul.second == 0){
			    result = sumsqRed[ul.second + length][ul.first] - sumsqRed[ul.second][ul.first - 1];
            } else {
                result = sumsqRed[ul.second + length][ul.first + length] +
                         sumsqRed[ul.second - 1][ul.first - 1] - 
                         sumsqRed[ul.second - 1][ul.first + length] - 
                         sumsqRed[ul.second + length][ul.first - 1]; 
            } 
            break;
        case 'g':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumsqGreen[ul.second + length][ul.first + length];  
            } else if (ul.first == 0 && ul.second != 0){
			    result = sumsqGreen[ul.second + length][ul.first] - sumsqGreen[ul.second - 1][ul.first + length];
            } else if (ul.first != 0 && ul.second == 0){
			    result = sumsqGreen[ul.second + length][ul.first] - sumsqGreen[ul.second][ul.first - 1];
            } else {
                result = sumsqGreen[ul.second + length][ul.first + length] +
                         sumsqGreen[ul.second - 1][ul.first - 1] - 
                         sumsqGreen[ul.second - 1][ul.first + length] - 
                         sumsqGreen[ul.second + length][ul.first - 1]; 
            }  
            break;
        case 'b':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumsqBlue[ul.second + length][ul.first + length];  
            } else if (ul.first == 0 && ul.second != 0){
			    result = sumsqBlue[ul.second + length][ul.first] - sumsqBlue[ul.second - 1][ul.first + length];
            } else if (ul.first != 0 && ul.second == 0){
			    result = sumsqBlue[ul.second + length][ul.first] - sumsqBlue[ul.second][ul.first - 1];
            } else {
                result = sumsqBlue[ul.second + length][ul.first + length] +
                         sumsqBlue[ul.second - 1][ul.first - 1] - 
                         sumsqBlue[ul.second - 1][ul.first + length] - 
                         sumsqBlue[ul.second + length][ul.first - 1]; 
            } 
            break;
        default:
        return NULL;
    }
    return result; 
}

//tests pass 
long stats::rectArea(int dim) {
/* Your code here!! */
    long result = pow(2,dim); 
    result *= result; 
    return result; 
}


//tests pass 
// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int dim){
/* Your code here!! */
//getSumsq - getSum^2/Area
    double a = getSum('r', ul, dim);
    double b = getSum('g', ul, dim);
    double c = getSum('b', ul, dim);
    double x = getSumSq('r', ul, dim); 
    double y = getSumSq('g', ul, dim); 
    double z = getSumSq('b', ul, dim); 
    
    double result; 
    double area = rectArea(dim); 

    result = x + y + z - (a*a)/area - b*b/area - c*c/area; 
    return result; 

}
		
//tests pass 
RGBAPixel stats::getAvg(pair<int,int> ul, int dim){
/* Your code here!! */
    int r = getSum('r', ul, dim) / rectArea(dim); 
    int g = getSum('g', ul, dim) / rectArea(dim); 
    int b = getSum('b', ul, dim) / rectArea(dim); 
    return RGBAPixel(r,g,b); 
}
