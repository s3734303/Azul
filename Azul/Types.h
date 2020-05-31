#ifndef __TYPES__H__
#define __TYPES__H__

enum tile {B,Y,R,U,L,F,E,X};
#define DIM 5
#define p_size 15
#define f_size 7
typedef char Wall[DIM][DIM];


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



char enumToChar(tile t);
tile charToEnum(char c);





#endif  //!__TYPES__H__

