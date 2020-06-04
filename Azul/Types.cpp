//
//  Types.cpp
//  Azul
//
//  Created by Home on 15/5/20.
//  Copyright © 2020 Home. All rights reserved.
//

#include "Types.h"
char enumToChar(tile t){
    switch (t) {
        case Y: return 'Y';
        case R: return 'R';
        case U: return 'U';
        case L: return 'L';
        case B: return 'B';
        case O: return 'O';
        case F: return 'F';
        case E: return '.';
        case X: return ' ';
        
        
    }
}
tile charToEnum(char c){
    switch(c){
        case 'Y': return Y;
        case 'R': return R;
        case 'U': return U;
        case 'L': return L;
        case 'B': return B;
        case 'O': return O;
        case 'F': return F;
        case '.': return E;
        default: throw 3;
    }
}
string enumToDisplay(tile t){
    switch (t) {
        case Y: return "🟨";
        case R: return "🟥";
        case U: return "⬛️";
        case L: return "🟩";
        case B: return "🟦";
        case O: return "🟧";
        case F: return "1️⃣";
        case E: return "🔲";
        case X: return "🔳";
    }
}
