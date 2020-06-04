#ifndef __PLAYERBOARD__H__
#define __PLAYERBOARD__H__

#include "Types.h"
class PlayerBoard{
    public:
    //include a copy constructor
    PlayerBoard(std::string playerName);
    ~PlayerBoard();
        
          
        
    //void addToPiles(int factory, char color, int number, vector< vector<tile> > &matrix);
    bool addToPiles(int factory, char color, int pileNumber, vector< vector<tile> > &matrix);
       
    void addToFloor(tile tiles);

    string toString();

    bool addToWall(tile tiles, int pileLine);

    bool tilingPhase();

    void setScore(int s);
        
    bool hasCompleteRow();

    int colorToEnum(char color);

    void loader(string wall_str,string pile_str,string floor_str);

    void moveTilesToPiles(vector<tile> picked, int noOfTiles, int pileNo);

    int calcScore(int row, int col);

    int calcFloorLine();

    void endGameScoring();

    int checkDirection(int positionY, int positionX,int changeY, int changeX);

    bool checkforTile( char position);

    vector<string>display();

    int getfinalScores();

    string getPlayerName();

    vector<tile> discarded_pile();

    vector<tile> getFloorLine()
    {
        return floorLine;
    }
                

    private:
    typedef char Wall[5][5];
//    typedef char WallX[6][6];
    Wall wall;
//    WallX wallX;
    int floorLineScores[7] = { -1, -1, -2, -2, -2, -3, -3};
//    int floorLineScoresX[8] = { -1, -1, -2, -2, -2, -3, -3, -4};
    // blueprint to set framework for wall (used in pile to wall function)
    char blueprint[5][5]=
    {
            {'B','Y','R','U','L'},
            {'L','B','Y','R','U'},
            {'U','L','B','Y','R'},
            {'R','U','L','B','Y'},
            {'Y','R','U','L','B'},
    };
    int score = 0;
    bool extendMode = false;
    
    int DIM = 5;
//    int DIMX = 6;
    tile pile[5][5];
//    tile pileX[6][6];
    int f_size = 7;
//    int f_sizeX = 8;
    string playerName;
    std::vector<tile> floorLine;
    vector<tile> discarded;
        
};

#endif  //!__PLAYERBOARD__H__
