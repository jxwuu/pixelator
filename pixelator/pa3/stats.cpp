
#include "stats.h"
#include <cmath> 

//all tests pass 


stats::stats(PNG & im){
    // cout<<"intiate stats"<<endl; 

/* Your code here!! */
    int width = im.width(); 
    int height = im.height(); 
    sumRed.resize(width, vector<long> (height,0));
    sumGreen.resize(width, vector<long> (height,0));
    sumBlue.resize(width, vector<long> (height,0));
    sumsqRed.resize(width, vector<long> (height,0));
    sumsqGreen.resize(width, vector<long> (height,0));
	sumsqBlue.resize(width, vector<long> (height,0));

    for(int y = 0; y < width; y++){
        for(int x = 0; x < height; x++){
            RGBAPixel *px = im.getPixel(y,x);
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
            } else if (y > 0 && x > 0){ // the middles 
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
    long result = 0;
    switch (channel){
        case 'r':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumRed[ul.first + length][ul.second + length];  
            } else if (ul.second == 0 && ul.first > 0){
			    result = sumRed[ul.first + length][ul.second + length] - sumRed[ul.first - 1][ul.second + length];
            } else if (ul.first == 0 && ul.second > 0){
			    result = sumRed[ul.first + length][ul.second+length] - sumRed[ul.first + length ][ul.second - 1];
            } else if(ul.first > 0 && ul.second > 0){
                result = sumRed[ul.first + length][ul.second + length] +
                         sumRed[ul.first - 1][ul.second - 1] - 
                         sumRed[ul.first - 1][ul.second + length] - 
                         sumRed[ul.first + length][ul.second - 1]; 
            } 
            break;
        case 'g':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumGreen[ul.first + length][ul.second + length];  
            } else if (ul.second == 0 && ul.first > 0 ){
			    result = sumGreen[ul.first + length][ul.second + length] - sumGreen[ul.first - 1][ul.second + length];
            } else if (ul.first == 0 && ul.second > 0 ){
			    result = sumGreen[ul.first + length][ul.second+length] - sumGreen[ul.first + length ][ul.second - 1];
            } else if (ul.first > 0 && ul.second > 0) {
                result = sumGreen[ul.first + length][ul.second + length] +
                         sumGreen[ul.first - 1][ul.second - 1] - 
                         sumGreen[ul.first - 1][ul.second + length] - 
                         sumGreen[ul.first + length][ul.second - 1]; 
            }  
            break;
        case 'b':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumBlue[ul.first + length][ul.second + length];  
            } else if (ul.second == 0 && ul.first > 0 ){
			    result = sumBlue[ul.first + length][ul.second + length] - sumBlue[ul.first - 1][ul.second + length];
            } else if (ul.first == 0 && ul.second > 0){
			    result = sumBlue[ul.first + length][ul.second+length] - sumBlue[ul.first + length ][ul.second - 1];
            } else if (ul.first > 0 && ul.second > 0){
                result = sumBlue[ul.first + length][ul.second + length] +
                         sumBlue[ul.first - 1][ul.second - 1] - 
                         sumBlue[ul.first - 1][ul.second + length] - 
                         sumBlue[ul.first + length][ul.second - 1]; 
            } 
            break;
    }
    return result; 
}

//tests pass
long stats::getSumSq(char channel, pair<int,int> ul, int dim){
/* Your code here!! */
    int length = pow(2,dim) - 1; 
    long result = 0;
      switch (channel){
        case 'r':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumsqRed[ul.first + length][ul.second + length];  
            } else if (ul.first > 0 && ul.second == 0){
			    result = sumsqRed[ul.first + length][ul.second + length] - sumsqRed[ul.first - 1][ul.second + length];
            } else if (ul.first == 0 && ul.second > 0){
			    result = sumsqRed[ul.first + length][ul.second + length] - sumsqRed[ul.first + length][ul.second - 1];
            } else if (ul.first > 0 && ul.second > 0){
                result = sumsqRed[ul.first + length][ul.second + length] +
                         sumsqRed[ul.first - 1][ul.second - 1] - 
                         sumsqRed[ul.first - 1][ul.second + length] - 
                         sumsqRed[ul.first + length][ul.second - 1]; 
            } 
            break;
        case 'g':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumsqGreen[ul.first + length][ul.second + length];  
            } else if (ul.first > 0 && ul.second == 0){
			    result = sumsqGreen[ul.first + length][ul.second + length] - sumsqGreen[ul.first - 1][ul.second + length];
            } else if (ul.first == 0 && ul.second > 0){
			    result = sumsqGreen[ul.first + length][ul.second + length] - sumsqGreen[ul.first + length][ul.second - 1];
            } else if (ul.first > 0 && ul.second > 0){
                result = sumsqGreen[ul.first + length][ul.second + length] +
                         sumsqGreen[ul.first - 1][ul.second - 1] - 
                         sumsqGreen[ul.first - 1][ul.second + length] - 
                         sumsqGreen[ul.first + length][ul.second - 1]; 
            }  
            break;
        case 'b':
            if(ul.first == 0 && ul.second == 0 ) {
                result = sumsqBlue[ul.first + length][ul.second + length];  
            } else if (ul.first > 0 && ul.second == 0){
			    result = sumsqBlue[ul.first + length][ul.second + length] - sumsqBlue[ul.first - 1][ul.second + length];
            } else if (ul.first == 0 && ul.second > 0){
			    result = sumsqBlue[ul.first + length][ul.second + length] - sumsqBlue[ul.first + length][ul.second - 1];
            } else if (ul.first > 0 && ul.second > 0){
                result = sumsqBlue[ul.first + length][ul.second + length] +
                         sumsqBlue[ul.first - 1][ul.second - 1] - 
                         sumsqBlue[ul.first - 1][ul.second + length] - 
                         sumsqBlue[ul.first + length][ul.second - 1]; 
            } 
            break;
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
