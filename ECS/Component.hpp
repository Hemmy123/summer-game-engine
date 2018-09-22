////========================================
// Class: Component
// Author: Hemmy
// Date: 30/08/2018
// Description:
// Parent class to all Component. The single
// method generates a UUID which all components
// must have.
//
// 
// ========================================

#ifndef Component_hpp
#define Component_hpp
#include <stdio.h>
#include <string>

class Component{
public:
	Component();
	
	std::string getID() const {return m_ID;}
	
private:
	void generateID();
	std::string m_ID;
};
#endif /* Component_hpp */
