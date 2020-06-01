#include "Menu.h"


Menu::Menu()
{
    play = new PlayGame();
}
Menu::~Menu()
{

}
int Menu::read_input()
{
    int input = -1;
    bool valid= false;
    do
    {
        std::cout << "\nMenu" << std::endl;
        cout << "-----"<< endl;
        cout << "1. New Game" << endl;
        cout << "2. New Game(Xtend Mode)" << endl;
        cout << "3. Load Game" << endl;
        cout << "4. Credits" << endl;
        cout << "5. Quit" << endl;
        cout << endl;

    
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout << "Invalid input; please re-enter." << endl;
        }
    } while (!valid);

    return (input);
}


void Menu::display(){
    cout << "Welcome to Azul!" << endl;
    cout << "-----------------"<< endl;
    
    int input = read_input();
    std::string player1, player2, filename; 
    while(true) 
    {
        if (input == 1)
        {
            printf("Starting a New Game\n");
            printf("Enter a name for player 1\n");
            std::cin >> player1;
            printf("Enter a name for player 2\n");
            std::cin >> player2;
            printf("\n");
            printf("Let’s Play!\n");
            printf("\n");
            printf("=== Start Round ===\n");
            
            play->playerSetup(player1, player2);
            play->play(true);
                
            input = read_input();
        }
        else if (input == 2)
        {
            play->setExtendMode();
            printf("Starting a New Game(Xtend Mode)\n");
            printf("Enter a name for player 1\n");
            std::cin >> player1;
            printf("Enter a name for player 2\n");
            std::cin >> player2;
            printf("\n");
            printf("Let’s Play!\n");
            printf("\n");
            printf("=== Start Round ===\n");
            
            play->playerSetup(player1, player2);
            play->play(true);
                
            input = read_input();
        }

        else if (input == 3)
        {
            cout << "Enter the filename from which to load a game" << "\n";
            std::cin >> filename;
            std::cout << "\n";
            if(play->loadGame(filename))
            {
                cout << "Azul game successfully loaded" << "\n";
                cout << "<game play continues from here>" << "\n";
                play->play(false);
                
            }
            input = read_input();

        }

        else if (input == 4)
        {
            cout << "----------------------------------"
                    "\nName: <Abida Mohammadi>"
                    "\nStudent ID: <s3811920>"
                    "\nEmail: <s3811920@student.rmit.edu.au>"
                    "\n----------------------------------"
                    "\nName: <Oscar Ling>"
                    "\nStudent ID: <s3604409>"
                    "\nEmail: <s3604409@student.rmit.edu.au>"
                    "\n----------------------------------"
                    "\nName: <Shiou-Ping Chu>"
                    "\nStudent ID: <s3734303>"
                    "\nEmail: <s3734303@student.rmit.edu.au>"
                    "\n----------------------------------"<< "\n";
            input = read_input();
                
        }
            
                    
    
        else if (input == 5)
        {
            cout << "Goodbye" << endl;
            exit(EXIT_SUCCESS);
        }
            
    
        else
        {
            if(cin.eof())
            {
                printf("GoodBye");
                exit(EXIT_SUCCESS);
            }
            else
            {
                cout << "Invalid input; please re-enter." << "\n\n";
                input = read_input();
            }
        }
            

    }
    
    
}
