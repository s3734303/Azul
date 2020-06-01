#ifndef __PLAYGAME__H__
#define __PLAYGAME__H__

#include "Types.h"
#include "PlayerBoard.h"
#include <fstream>
#define FACTORY_NUM 6

class PlayGame{
    public:
        PlayGame();
        ~PlayGame();
        void play(bool newGame);
    
        void initialBagfilling();

        void addToBag(vector<tile> &bag);

        void addToBoxLid(vector<tile> brokenTiles);

        void addToFactories();

        void showPlayersBoard(int c);

        template <typename T> 
        friend std::ostream& operator<<(std::ostream& os, const vector<T>& v);
    
        string factoryToString();
        void playerSetup(string player1, string player2);
        void saveGame(string filename);
        bool loadGame(string filename);
        bool f_check();
        void wallTiling();
        void setExtendMode();

    private:
        bool hasWinner;
        bool endGame = false;
        bool s_check = false;
        bool extendMode = false;
        std::vector<tile> bag;
        LinkedList<tile> boxLid{};
        std::vector<std::vector<tile>> factories;
        vector<PlayerBoard> *players;
        int playerNumber;
};


#endif  //!__PLAYGAME__H__
