#ifndef __MENU__H__
#define __MENU__H__

#include "Types.h"
#include "PlayGame.h"

class Menu{
    public:
        Menu();
        ~Menu();
        void display();
        int  read_input();
        bool FileExists(const std::string &Filename);

    private:
        PlayGame *play;

};

#endif //!__MENU__H__
