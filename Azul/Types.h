#ifndef __TYPES__H__
#define __TYPES__H__

enum tile {B,Y,R,U,L,C,F,E,X};



#include <list>
#include <vector>
#include "LinkedList.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <array>


using std::array;
using std::list;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;


string enumToDisplay(tile t);
char enumToChar(tile t);
tile charToEnum(char c);





#endif  //!__TYPES__H__

