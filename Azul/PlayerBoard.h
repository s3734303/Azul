#ifndef __PLAYERBOARD__H__
#define __PLAYERBOARD__H__

#include "Types.h"
class PlayerBoard{
    public:
    //include a copy constructor
    PlayerBoard(std::string playerName);
    ~PlayerBoard();
        
          
        
    //void addToPiles(int factory, char color, int number, vector< vector<tile> > &matrix);
    void addToPiles(int factory, char color, int pileNumber, vector< vector<tile> > &matrix);
       
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
    int floorLineScores[7] = { -1, -1, -2, -2, -2, -3, -3};
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
    Wall wall;
    int DIM = 5;
    
    tile pile[5][5];
    int f_size = 7;
    string playerName;
    std::vector<tile> floorLine;
    vector<tile> discarded;
        
};
class PlayerBoardX : public PlayerBoard{
private:
    typedef char Wall[6][6];
    int DIM = 6;
    int f_size = 8;
    Wall wall;
    int floorLineScores[8] = { -1, -1, -2, -2, -2, -3, -3, -4};
    tile pile[6][6];
};

#endif  //!__PLAYERBOARD__H__
