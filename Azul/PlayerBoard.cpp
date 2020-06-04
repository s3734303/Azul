#include "PlayerBoard.h"

PlayerBoard::PlayerBoard(std::string playerName,bool XtendMode)
{
    if(XtendMode)
        enableXtendMode();
    
    this->playerName = playerName;
    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            wall[i][j]='.';
            pile[i][j]=X;
        }
        for(int k =0;k<=i;k++)
            pile[i][k]=E;
    }
}

PlayerBoard::~PlayerBoard(){
    
}

void PlayerBoard::setScore(int s)
{
    score = s;
}

int PlayerBoard::getfinalScores()
{
    return score;
}

string PlayerBoard::getPlayerName()
{
    return playerName;
}

void PlayerBoard::enableXtendMode()
{
    DIM=6;
    f_size=8;
    floorLineScores.push_back(-4);
    
}


bool PlayerBoard::addToWall(tile tiles, int pileLine)
{
    // If tile matches wallLine tile of blueprint, and space in wall is '.', wall gets char of tile
    bool action =true;
    for(int i=0; i<DIM; i++)
    {
        if(wall[pileLine][i]!='.'){
            for(int k=0;k<DIM;k++)
                if((pileLine+k)%DIM==i && tiles!=enumToChar(static_cast<tile>(k)))
                    action = false;
        }
        
         if (enumToChar(tiles) == blueprint[pileLine][i])
         {
             if (wall[pileLine][i] == '.')
             {
                wall[pileLine][i] = enumToChar(tiles);
                setScore(calcScore(pileLine,i));
             }
             else 
             {
                 cout<<"Cannot place tile on this Line!"<<endl;
             }
             
         }

    }

    setScore(calcFloorLine());
    // checking for endGame
    int wallLineProgress = 0;
    for(int j=0; j<DIM; j++)
    {
        if (wall[pileLine][j] != '.')
        {
            wallLineProgress++;
        }
    }
    if (wallLineProgress ==5)
    {
        return true;
    }
    else
    {
        return false;
    }
   
}


bool PlayerBoard::tilingPhase()
{
    bool endGame = false;
    int row = 0;
    for (int i=0; i<DIM; i++)
    {
        row = 0;
        for (int j = 0; j<DIM; j++)
        {
            if (pile[i][j] != E && pile[i][j] != X)
            {
                row++;
            }

            if (row == i+1)
            {
               endGame= addToWall(pile[i][j],i);
               for(int k=0; k<DIM; k++)
               {
                   if(pile[i][k] != tile::E && pile[i][k] != tile::X)
                   {
                       discarded.insert(discarded.end(), i , pile[i][j]);
                       pile[i][k] = tile::E;
                   }
               }  
            }
        }
    }
    floorLine.erase(std::remove(floorLine.begin(), floorLine.end(), tile::F), floorLine.end());
    return endGame;
}


int PlayerBoard::calcScore(int row, int col)
{
    int colCount = 0;
    int rowCount = 0;
    int totalCount = 0;

     //column scoring
    if (checkforTile(wall[row][col -1 ]))
    {
        colCount += checkDirection(row,col,0,-1);
    }
    if ( checkforTile(wall[row][col +1]))
    {
        
        colCount += checkDirection(row, col,0,1);
    }
    colCount++;

    //row scoring
    if ( checkforTile(wall[row-1][col]))
    {
        
        rowCount += checkDirection(row, col,-1,0);
    }
    if (checkforTile(wall[row+1][col]))
    {
        
        rowCount += checkDirection(row, col,+1,0);
    }
    rowCount++;

    totalCount = rowCount + colCount;

    // if no tiles adjacent to this position
    if (!checkforTile(wall[row][col -1 ]) && !checkforTile(wall[row][col +1 ]) && !checkforTile(wall[row-1][col]) && !checkforTile(wall[row+1][col]))
    {
        totalCount++;
    }
    return totalCount;
   
}

//counts for completed tiles in that direction
int PlayerBoard::checkDirection(int positionY, int positionX,int changeY, int changeX)
{
    int counter = 0;
    bool finished = false;
    int x = positionX;
    int y = positionY;
    while (!finished)
    {
        if(checkforTile(wall[y + changeY][x + changeX]))
        {
            counter++;
            x += changeX;
            y += changeY;
        }
        else 
        {
            finished = true;
        }
    }

    return counter;

}

bool PlayerBoard::checkforTile(char position)
{
    char set[5] = {'R','Y','B','L','U'};
    for (int i= 0; i<5;i++)
    {
        if (position == set[i])
        {
            return true;
        }
    }

    return false;
}


 vector<tile> PlayerBoard::discarded_pile()
 {
     return discarded;  
 }




vector<string> PlayerBoard::display(){
    vector<string> out;
    string display_str;
    string pile_display[DIM][DIM];
    string wall_display[DIM][DIM];

    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            wall_display[i][j]=enumToDisplay(charToEnum(wall[i][j]));
                
        }
    }
    
    char buff[4];
    
    display_str=("Mosiac For " + playerName);
    while(display_str.length()<40) display_str.push_back(' ');
    out.push_back(display_str);
    display_str.clear();
    for(int i =0;i<DIM;i++){
        for(int j =0;j<DIM;j++){
            pile_display[i][j]=enumToDisplay(pile[i][j]);
        }
            
    }
    for(int i =0; i<DIM;i++){
        sprintf(buff, "%d: ",i+1);
        display_str.append(buff);
        for(int j =DIM-1;j>=0;j--){
            display_str.append(pile_display[i][j]);
            display_str.push_back(' ');
        }
        display_str.append("||");
        for(int j =0;j<DIM;j++){
            display_str.push_back(' ');
            display_str.append(wall_display[i][j]);
            display_str.push_back(' ');

        }
        out.push_back(display_str);
        display_str.clear();
    }
//    display_str.append("broken: ");
//    for(tile t : floorLine){
//        display_str.append(enumToDisplay(t));
//        //display_str.push_back(' ');
//    }
//    while(display_str.length()<40) display_str.push_back(' ');
//    out.push_back(display_str);
    
    return out;
}

void PlayerBoard::moveTilesToPiles(vector<tile> picked, int noOfTiles, int pileNo)
{
     tile placeholder[picked.size()];
     std::copy(picked.begin(), picked.end(), placeholder);
     int tilesLeft = noOfTiles;
     
     
        for (int i=0; i<DIM; i++)
        {
                 if (pile[pileNo-1][i] == E && tilesLeft !=0)
                {
                    pile[pileNo-1][i] = placeholder[0];
                    tilesLeft--; //Expected ';' after expression DONE
                }
        }
            

        //put the amount of tiles left into the floor
        for(int j = 1; j<=tilesLeft; j++)
        {
            std::cout<<"Placing left over tile into Floor Line"<<std::endl;
            addToFloor(placeholder[0]);
        }
     
}



bool PlayerBoard::addToPiles(int factory, char color, int pileNumber, vector< vector<tile> > &matrix)
{
    int c = charToEnum(color);
    tile t_color = static_cast<tile>(c);
    std::vector<tile> pickedTiles;

    if(!matrix[factory].empty())
    {
//        for(char c : wall[pileNumber-1]){
//            if(charToEnum(c)==t_color){
//                cout << "Can't put here" << endl;
//                
//                return false;
//            }
//        }
        if(std::find(matrix[factory].begin(), matrix[factory].end(), t_color) != matrix[factory].end())
        {
            std::copy_if(matrix[factory].begin(), matrix[factory].end(), std::back_inserter(pickedTiles), [&](tile t){return t == t_color;});
            matrix[factory].erase(std::remove(matrix[factory].begin(), matrix[factory].end(), t_color), matrix[factory].end());
            int amount = pickedTiles.size();
            if(factory == 0)
            {
                moveTilesToPiles(pickedTiles, amount, pileNumber);
                if(std::find(matrix[factory].begin(), matrix[factory].end(), F) != matrix[factory].end())
                {
                    matrix[0].erase(std::find(matrix[0].begin(),matrix[0].end(),tile::F));
                    floorLine.push_back(tile::F);
                }
                return true;
            }
            else 
            {
                std::copy(matrix[factory].begin(), matrix[factory].end(), std::back_inserter(matrix[0]));
                moveTilesToPiles(pickedTiles, amount, pileNumber);
                matrix[factory].clear();
                return true;
            }
        }
        else
        {
            cout << "tile not found!" << endl;
            return false;
        }
    } 
    else 
    {
        cout << "factory has no tiles!" << endl;
        return false;
    }
        
}


void PlayerBoard::addToFloor(tile tiles)
{
        floorLine.push_back(tiles);
}


string PlayerBoard::toString(){
    string str;
    str.append("#PLAYER_NAME\n");
    str.append(playerName);
    str.append("\n#PLAYER_WALL\n");
    for(int i = 0;i<DIM;i++){
        for(int j = 0;j<DIM;j++){
            str.push_back(wall[i][j]);
        }
    }
    str.append("\n#PLAYER_PILES\n");
    for(int i = 0;i <DIM;i++){
        for(int j = 0;j<=i;j++){
            str.push_back(enumToChar(pile[i][j]));
        }
    }
        
    str.append("\n");
    if(!floorLine.empty()){
        str.append("#PLAYER_FLOORLINE\n");
        for(tile t :floorLine){
            str.push_back(enumToChar(t));
        }
        str.append("\n");
    }
    str.append("#PLAYER_SCORE\n");
    str.append(std::to_string(score));
    str.append("\n#PLAYER_END\n");

    return str;
}

void PlayerBoard::loader(string wall_str,string pile_str,string floor_str){
    for(int i=0;i<DIM;i++){
        for(int j=0;j<DIM;j++){
            wall[i][j] = wall_str.at(i*5 + j);
            if(wall[i][j]!='.'){
                for(int k=0;k<DIM;k++)
                    if((i+k)%DIM==j && wall[i][j]!=enumToChar(static_cast<tile>(k)))
                        throw 5;
            }
            for(tile t : pile[i])
                if(enumToChar(t)==wall[i][j] && wall[i][j]!='.')
                    throw 5;
        }
    }
    int c=0;
    for(int i =0;i<DIM;i++){
        for(int j = 0;j<=i;j++){
            if(j>0 && charToEnum(pile_str.at(c))!=pile[i][j-1] && pile[i][j-1] && charToEnum(pile_str.at(c)) !=E)
                throw 5;
            pile[i][j] = charToEnum(pile_str.at(c));
            c++;
        }
    }
    
    for(char c :floor_str)
        floorLine.push_back(charToEnum(c));
}

//Redefinition of 'calcFloorLine'
int PlayerBoard::calcFloorLine() //Redefinition of 'calcFloorLine' DONE
{
     //floorLine scoring
    int deduction =0;
    for (int i=0; i<this->floorLine.size(); i++) //Member reference type 'PlayerBoard *' is a pointer; did you mean to use '->'?
    {
        deduction += floorLineScores.at(i);
    }

    return deduction;

}

vector<tile> PlayerBoard::getFloorLine()
{
    vector<tile> broken;
    broken =floorLine;
    floorLine.erase(floorLine.begin(),floorLine.end());
    return broken;
}
    

void PlayerBoard::endGameScoring() //Redefinition of 'endGameScoring'DONE
{
    int wallRowProgress = 0;
    int wallColProgress = 0;
    int completedCols =0 ;
    int completedRows = 0;
    int completedColours = 0;
    int r = 0;
    int b = 0;
    int y = 0;
    int u = 0;
    int l = 0;
    std::array<int,5> temp {r,b,y,u,l};
   
    int total = 0;

    //row, columns, and colour checks
    for(int i=0; i<DIM; i++)
    {
        wallRowProgress = 0;
        wallColProgress = 0;
        for(int j=0; j<DIM; j++)
        {
            //row by row checks for completed rows
            if (wall[i][j] != '.')
            {
                wallRowProgress++;
            }
            if (wallRowProgress ==5)
            {
                completedRows++;
            }

            //column by column check for completed columns
            if (wall[j][i] != '.')
            {
                wallColProgress++;
            }
            if (wallRowProgress ==5)
            {
                completedCols++;
            }
            
            //colour checks
            if (wall[i][j] == 'R')
            {
                r++;
            }

            if (wall[i][j] == 'B')
            {
                b++;
            }

            if (wall[i][j] == 'Y')
            {
                y++;
            }

            if (wall[i][j] == 'U')
            {
                u++;
            }

            if (wall[i][j] == 'L')
            {
                l++;
            }
            
        }

    }

    //completed colour Checks
    for(int k=0; k<temp.size();k++) //Member reference base type 'int [5]' is not a structure or union DONE
    {
        if (temp[k] == 5) //Use of undeclared identifier 'arr' DONE
        {
            completedColours++;
        }
    }

    //set final score
    total = (completedRows * 2)+(completedCols * 7)+(completedColours * 10);
    setScore(total);

}


