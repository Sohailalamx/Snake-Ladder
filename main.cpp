#include<bits/stdc++.h>
using namespace std;

class Game; // Forward declaration of game class

class Player {
    bool started;
    bool completed;
    string name;
    int currentPosition;
    int totalSnakeBites;
    int totalLadder;
    int rank;

  public:
    Player() {
        this -> started = false;
        this -> completed = false;
        // this -> name = name;
        this -> currentPosition = 0;
        this -> totalSnakeBites = 0;
        this -> totalLadder = 0;
    }

    void start() {
        this -> started = true;
    }

    void finish() {
        this -> completed = true;
    }

    // void position_update(const int &diceValue, const game &g) {
    //     this -> currentPosition += diceValue;
    //     // // currentPosition > 100 case can be checked here !!!!!!!!!
    //     if(g.snakes.find(currentPosition) != g.snakes.end())
    //     {
    //         this -> totalSnakeBites++;
    //         cout << "   Snake bites at " << currentPosition << " !!! 😞" << endl;
    //         this -> currentPosition = g.snakes.at(currentPosition);
    //     }
    //     else if(g.ladders.find(currentPosition) != g.ladders.end())
    //     {
    //         this -> totalLadder++;
    //         cout << "   You got a ladder at " << currentPosition << " !!! 😁" << endl;
    //         this -> currentPosition = g.ladders.at(currentPosition);
    //     }
    //     cout << "   Now position: " << currentPosition << endl;
    // }

    friend class Game;
};

class Game {
    string gameStartedAt;
    string gameEndedAt;
    int numOfPlayers;
    int position;
    vector<Player> players;
    int remainingPlayers;
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;

  public:
    Game() {
        cout << endl << "**************************** SNAKE & LADDER **************************" << endl;
        cout << endl << " !!! How many Players ::  ";
        cin >> numOfPlayers;
        remainingPlayers = numOfPlayers;

        while(numOfPlayers < 1)
        {
            cout << " !! Oooops you need atleast 1 player" << endl;
            cout << "  !! Number of player ::  " << endl;
            cin >> numOfPlayers;
        }

        players.resize(numOfPlayers);


        // Snakes and Ladders defined
        snakes = {{16, 6}, {47, 26}, {49, 11}, {56, 53}, {62, 19}, {64, 60}, {87, 24}, {93, 73}, {95, 75}, {98, 78}};
        ladders = {{4, 14}, {9, 31}, {21, 42}, {28, 84}, {36, 44}, {51, 67}, {71, 91}, {80, 96}};
        
        // Player names
        cout << endl;
        for(int i = 0; i < numOfPlayers; i++)
        {
            cout << " !! Enter Player " << i + 1 << " name ::  ";
            string name;
            cin >> name;
            players[i].name = name;
        }

        this -> position = 1;

        cout << " !! Game Started !! " << endl << endl;
        cout << "*******************************************************" << endl << endl;
        
        // Current time of game start
        {
            time_t t = time(NULL);
            tm* timePtr = localtime(&t);
            this -> gameStartedAt = asctime(timePtr);
        }

        cout << " !! Game Started at ::  " << gameStartedAt << endl << endl;

        play();
    }


    // Function to start and continue the game until all players finish
    void play() {
        int playerIndex = 0;
        
        while (true) // each loop is a turn of a player
        {
            if(remainingPlayers == 0) // if all players finished the game
            {
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << endl;
                cout << " !! Game Over !! " << endl;


                // Current time of game end
                {
                    time_t t = time(NULL);
                    tm* timePtr = localtime(&t);
                    this -> gameEndedAt = asctime(timePtr);
                }

                cout << " !! Game Ended at ::  " << gameEndedAt << endl << endl;

                cout << " !! Final Result !! " << endl << endl;
                cout << " !! Name :: Rank :: Total Snake Bites :: Total Ladder Climbs !! " << endl << endl;

                for(int i = 0; i < numOfPlayers; i++)
                {
                    cout << " !! " << players[i].name << " :: " << players[i].rank << " :: " << players[i].totalSnakeBites << " :: " << players[i].totalLadder << " !! " << endl;
                }

                cout << endl;
                cout << "--------------------------------------------------------------------------------" << endl;

                break;
            }

            if(players[playerIndex].completed)  // if player already finished the game next player turn
            {
                playerIndex = (playerIndex + 1) % numOfPlayers;
                continue;
            }

            // Normal turn of a non finished player
            cout << " !! " << players[playerIndex].name << " turn ::  ";
            cout << " !! Press any key to roll the dice ::  ";
            char ch;
            cin >> ch;
            
            int diceValue = diceRoll();
            cout << " !! Dice Value ::  " << diceValue << endl;

            if(players[playerIndex].started == false)
            {
                if(diceValue == 1)
                {
                    players[playerIndex].start();
                    cout << " !! " << players[playerIndex].name << " started the game !! " << endl;
                    // players[playerIndex].position_update(diceValue, *this);
                    players[playerIndex].currentPosition = 1;
                    cout << " !! " << players[playerIndex].name << " position :: " << players[playerIndex].currentPosition << endl;

                }
                else
                {
                    cout << " !! " << players[playerIndex].name << " need 1 to start the game !! " << endl;
                }
            }
            else
            {
                // players[playerIndex].position_update(diceValue, *this);
                players[playerIndex].currentPosition += diceValue;
                if(players[playerIndex].currentPosition == 100)
                {
                    players[playerIndex].rank = position;
                    position++;
                    cout << " !! " << players[playerIndex].name << " Finished the game !! Rank :: " << players[playerIndex].rank << endl;
                    players[playerIndex].finish();
                    remainingPlayers--;
                }

                else if(players[playerIndex].currentPosition > 100)
                {
                    players[playerIndex].currentPosition -= diceValue;
                    cout << " !! " << players[playerIndex].name << " need " << 100 - players[playerIndex].currentPosition << " to finish the game !! " << endl;
                }

                // Snake
                else if(snakes.find(players[playerIndex].currentPosition) != snakes.end())
                {
                    players[playerIndex].totalSnakeBites++;
                    cout << " !! Snake bites at " << players[playerIndex].currentPosition << " !!!  :(" << endl;
                    players[playerIndex].currentPosition = snakes[players[playerIndex].currentPosition];
                }

                // Ladder
                else if(ladders.find(players[playerIndex].currentPosition) != ladders.end())
                {
                    players[playerIndex].totalLadder++;
                    cout << " !! You got a ladder at " << players[playerIndex].currentPosition << " !!! ^ _ ^" << endl;
                    players[playerIndex].currentPosition = ladders[players[playerIndex].currentPosition];
                }

                 cout << " !! " << players[playerIndex].name << " position :: " << players[playerIndex].currentPosition << endl;
            }

            playerIndex = (playerIndex + 1) % numOfPlayers;
            cout << endl << endl;
        }
        
    }


    // Function to generate random number between 1 to 6
    int diceRoll() {
        int random = rand() % 6 + 1;
        return random;
    }
};


int main() {

    Game g;
    return 0;
}


