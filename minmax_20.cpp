#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int min(int x, int y);
int max(int x, int y);

int main(int argc, char** argv) {
  
  int x=54;
  int y=32;
  
  std::cout<<min(x,y)<<std::endl;
  std::cout<<max(x,y)<<std::endl;
  
	return 0;
}

int min(int x, int y){
  if(x<y)
    return x;
    
  return y;  
}

int max(int x, int y){
  if(x>y)
    return x;
    
  return y;  
}
