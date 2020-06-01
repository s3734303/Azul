#include "PlayGame.h"
#include "LinkedList.hpp"
#include <random>
#include <regex> 
#include <cstring>

using namespace std;
PlayGame::PlayGame()
{
}
PlayGame::~PlayGame()
{
}

void PlayGame::playerSetup(string player1, string player2)
{
    player[0] = new PlayerBoard(player1);
    player[1] = new PlayerBoard(player2);    
}


void PlayGame::showPlayersBoard(int x)
{
    cout << factoryToString();
    cout << player[x]->display();
    string input;
    cout << "\n> ";
    getline(cin, input);
    regex r("^turn\\s[012345]\\s[FRYBLU]\\s[12345]");
    regex s("^save");
    regex h("^help");
    if (regex_match(input.begin(), input.end(), r)) 
    {
        regex ws_re("\\s+");

        vector<std::string> usr_in {
        sregex_token_iterator(input.begin(), input.end(), ws_re, -1), {}
        };
        std::vector<char> cstr(usr_in[2].c_str(), usr_in[2].c_str() +usr_in[2].size() + 1);

        int fac_no = stoi(usr_in[1]);
        int tile_c = cstr[0];
        int pile_no = stoi(usr_in[3]);

        player[x]->addToPiles(fac_no, tile_c, pile_no, factories);

    } else if(regex_search(input, s, std::regex_constants::match_continuous))
    {
        saveGame(input.substr(input.find(' ') + 1));
        printf("Game successfully saved!\n");
        s_check = true;
    }
    else if(regex_search(input, h, std::regex_constants::match_continuous)){
        cout<<"usage:"<<endl;
        cout<<"turn <Factory Number> <tile> <storage number>"<< endl;
        cout<<"save game"<<endl;
        cout<<"savegame <filename>"<<endl;
    }
    else 
    {
        cout << "Invalid Input\n"; 
        showPlayersBoard(x);
    }

}


    
void PlayGame::wallTiling()
{
    endGame = player[0]->tilingPhase();
    addToBoxLid(player[0]->discarded_pile());
    player[0]->calcFloorLine();
    addToBoxLid(player[0]->getFloorLine());

    endGame = player[1]->tilingPhase();
    addToBoxLid(player[1]->discarded_pile());
    player[1]->calcFloorLine();
    addToBoxLid(player[1]->getFloorLine());
}

void PlayGame::play(bool newGame)
{
    if(newGame)
    {
        initialBagfilling();
        addToFactories();
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    int counter = 0;
    while(!s_check && !endGame)
    {
        while(!s_check && f_check() != true)
        { 
            if(counter % 2 == 0)
            {
                showPlayersBoard(0);
            }else
            {
                showPlayersBoard(1);
            }
            counter++;
        }
        if(!s_check)
        {
        wallTiling();
        printf("=== END OF ROUND ===\n");
        addToFactories();
        }
    }
    if(!s_check)
    {
    player[0]->endGameScoring();
    player[1]->endGameScoring(); 

    int pA_score = player[0]->getfinalScores();
    int pB_score = player[0]->getfinalScores();
    
    printf("=== GAME OVER ===");

    if(pA_score > pB_score)
    {
        cout << player[0]->getPlayerName() << "Wins the game" << endl;
    }
    else
    {
        cout << player[1]->getPlayerName() << "Wins the game" << endl;
    }
    }
}

string PlayGame::factoryToString(){
    string display_str;
    char buff[5];
    int i=0;
    display_str.append("\nFactories:\n");
    for(std::vector<tile> factory : factories){
        sprintf(buff, "%d:",i);
        display_str.append(buff);
        for(tile t : factory){
            display_str.push_back(' ');
            display_str.push_back(enumToChar(t));
        }
        display_str.append("\n");
        i++;
    }
    
    return display_str;
}
//fill Bag with 100 tiles (20 of each color) and shuffle
void PlayGame::initialBagfilling(){
    for(int i = 0; i < tile::F; i++){
        for(int j=0; j<20; j++){
            bag.push_back(static_cast<tile>(i));
        }
    }
    std::shuffle(bag.begin(), bag.end(), std::mt19937{std::random_device{}()});
}

void PlayGame::addToBag(vector<tile> &bag)
{
    boxLid.getAll(bag);
}


//move tiles from floorline into boxlid
void PlayGame::addToBoxLid(vector<tile> brokenTiles)
{
    for(int i=0; i<brokenTiles.size(); i++)
    {
        boxLid.InsertHead(brokenTiles[i]);
    }
}


//populating factories with tiles from bag
void PlayGame::addToFactories()
{   
    std::vector<tile> factory;
    if(factories.size() == 0)
    {
        for(int i=0; i<6; i++){
            if(i==0)
            {
                factory.push_back(tile::F);
                factories.push_back(factory);
                factory.erase(factory.begin(), factory.end());   
            } 
            else 
            {
                auto it = std::next(bag.begin(), 4);
                std::move(bag.begin(), it, std::back_inserter(factory));
                bag.erase(bag.begin(), it);
                factories.push_back(factory); 
                factory.erase(factory.begin(), factory.end());   
            }
        }
    }
    else 
    {
        for(int i=0; i<6; i++)
        {
            if(i==0)
            {
                factory.push_back(tile::F);
                std::copy(factory.begin(), factory.end(), std::back_inserter(factories[i]));
                factory.erase(factory.begin(), factory.end());   
            } 
            else 
            {
                auto it = std::next(bag.begin(), 4);
                std::move(bag.begin(), it, std::back_inserter(factory));
                bag.erase(bag.begin(), it);
                std::copy(factory.begin(), factory.end(), std::back_inserter(factories[i]));
                factory.erase(factory.begin(), factory.end());  
            }
        }

    }        
         
        
}




template <typename T> 
std::ostream& operator<<(std::ostream& os, const vector<T>& v) 
{ 
    os << "["; 
    for (int i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    os << "]\n"; 
    return os; 
}

void PlayGame::saveGame(string filename)
{
    ofstream NewSave(filename);
    NewSave << player[0]->toString();
    NewSave << player[1]->toString();
    for(vector<tile> factory : factories){
        NewSave << "#FACTORY\n";
        for(tile t :factory)
            NewSave << enumToChar(t);
        NewSave << "\n";
    }
    if(hasWinner)
        NewSave << "#HASWINNER\n";
    if(!bag.empty()){
        NewSave << "#BAG\n";
        for(tile t : bag)
            NewSave<<enumToChar(t);
        NewSave<<"\n";
    }
    if(!boxLid.IsEmpty()){
        NewSave << "#BOXLID\n";
        NewSave << boxLid;
    }
    NewSave.close();
}


bool PlayGame::loadGame(string filename)
{
    string parse;
    string playerName,wall_str,pile_str,floor_str,factory_str,centre_str,bag_str,score_Str,winner_str,boxLid_str;
    vector<tile> *factory;
    int score=0;
    int pn = 0,f=0;
    try{
        if(!(access( filename.c_str(), 0 ) == 0))
            throw 0;
        if(pn>1)
            throw 5;
        ifstream SaveGame(filename);
        while(SaveGame.peek()!=EOF){
            getline(SaveGame, parse);
            if(parse == "#COMMENT"){
                string str;
                getline(SaveGame,str);
                cout<<str<<endl;
            }
            else if(parse == "#PLAYER_NAME")
                getline(SaveGame, playerName);
            else if(parse == "#PLAYER_WALL"){
                getline(SaveGame,wall_str);
                if(wall_str.length()!=25)
                    throw 3;
            }
                
            else if(parse == "#PLAYER_PILES"){
                getline(SaveGame, pile_str);
                if(pile_str.length()!=15)
                    throw 3;
            }
                
            else if (parse == "#PLAYER_FLOORLINE"){
                getline(SaveGame, floor_str);
                if(floor_str.length()>6)
                    throw 3;
                for(char c : floor_str){
                    if(c=='F')
                        f++;
                }
                    
            }
                
            else if(parse == "#PLAYER_SCORE"){
                getline(SaveGame,score_Str);
                for(char c : score_Str)
                    if(!isdigit(c))
                        throw 5;
                score =atoi(score_Str.c_str());
                if(score>100)
                    throw 5;
            }
            else if(parse == "#PLAYER_END"){
                if(playerName.empty() || pile_str.empty() || wall_str.empty())
                    throw 5;
                player[pn] = new PlayerBoard(playerName);
                player[pn]->loader(wall_str, pile_str, floor_str);
                player[pn]->setScore(score);
                playerName.clear();
                pile_str.clear();
                wall_str.clear();
                floor_str.clear();
                pn++;
            }
            else if (parse =="#FACTORY"){
                if(factories.size()<6){
                    factory = new vector<tile>;
                    getline(SaveGame,factory_str);
                    if(factories.size()>1){
                        if(factory_str.length()!=4 && !factory_str.empty())
                            throw 4;
                        for(char c : factory_str){
                            if(c!='F' || factories.size()<1)
                                factory->push_back(charToEnum(c));
                            
                            else    throw 4;
                        }
                    }
                    else{
                        for(char c : factory_str){
                            factory->push_back(charToEnum(c));
                            if(c=='F')
                                f++;
                        }
                    }
                    factories.push_back(*factory);
                }
                else    throw 4;
            }
            else if(parse == "#HASWINNER"){
                if(hasWinner==false)
                hasWinner=true;
                else    throw 2;
            }
                
            else if (parse == "#BAG"){
                getline(SaveGame,bag_str);
                for(char c : bag_str){
                    if(c=='F')  throw 1;
                    bag.push_back(charToEnum(c));
                }
            }
            else if (parse == "#BOXLID"){
                getline(SaveGame,boxLid_str);
                for(char c : boxLid_str){
                    if(c=='F')  throw 1;
                    boxLid.InsertHead(charToEnum(c));
                }
            }
            else    throw 2;
        }
        if(pn!=2)   throw 5;
        if(f!=1)    throw 1;
        SaveGame.close();
        return true;
    }catch(int e){
        if(e==0)
            cout<<"Save file not found."<<endl;
        else
            cout<<"Save file corrupt : ";
        if(e==1)
            cout<<"Illegal tile"<<endl;
        if(e==2)
            cout<<"Illegal tag"<<endl;
        if(e==3)
            cout<<"illegal data length"<<endl;
        if(e==4)
            cout<<"Illegal factory state"<<endl;
        if(e==5)
            cout<<"Illegal player data"<<endl;
    }
    factories.clear();
    boxLid.Clear();
    bag.clear();
    hasWinner=false;
    return false;
}


bool PlayGame::f_check()
{
    int f_check=0;
    for (auto& factory : factories)
    {
        if (factory.empty()) 
        {
            f_check++;
        }
    }
    if(f_check == 6) { return true;}
    else {return false;}
}

