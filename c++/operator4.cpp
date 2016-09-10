#include <iostream>
class Love{ 
	public: 
    	int str; 
    	int agi; 
    	int intel;      
    	Love(): str(0), agi(0) , intel(0){} 
    	Love(int a , int b ,int c): str(a), agi(b) , intel(c){};   
		inline Love& operator+=(const Love &test) const; 
}; 
inline  Love& Love::operator+=(const Love &test) const
{ 
	str += test.str; 
	agi += test.agi; 
	intel += test.intel; 
	return *this; 
} 

int main(){ 
    Love boy;
	Love girl(10,20,30); 
    boy += girl; 
	
    std::cout << boy.str << boy.agi << boy.intel << std::endl; 
    return 0; 
} 
