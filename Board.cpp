// Source file calling the header file
#include "Board.h"
// Recall we use this preprocessor directive for rand() and srand()
#include <cstdlib>
// Similarly, we use this one for time() (The seed for random)
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>

#include "Player.h"
using namespace std;


// Each of the following defines a macro
// Essentially nicenames to use instead of the corresponding escape sequence ('\') 
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define RED "\033[48;2;230;10;10m"
#define PURPLE "\033[48;2;128;0;128m"
#define RESET "\033[0m"

using namespace std;

// =========================== Constructor ===========================

Board::Board() {
    // Creates two players
    _player_count = _MAX_PLAYERS;

    // Initialize player's position
    for (int i = 0; i < _player_count; i++) {
        _player_position[i] = 0;
    }

    // Fill both lanes
    initializeBoard();
}

// =========================== Private Member Functions ===========================

void Board::initializeTiles(int player_index) {
    Tile tile;
    int green_count = 0;
    // Recall 52 from header file
    int total_tiles = _BOARD_SIZE;

  
    for (int i = 0; i < total_tiles; i++) {
        // Set the last tile as Orange for the finish line
        if (i == total_tiles - 1) {
            tile.color = 'O';
        } 
        // Set the first tile as Grey for the starting line
        else if (i == 0) {
            tile.color = 'Y';
        } 
        //This color codes the second tile to help label which track it which
        else if (i == 1) { 
            if (player_index == 0) {
                tile.color = 'R'; // First tile after the players tile is Red (Training Fellowship/Mode 0)
            } else {
                tile.color = 'B'; // First tile after the players tile is Blue (Direct Lab Assignment/Mode 1)
            }
        }
        // Hard-coded target of 30 green tiles
        // Probablisitic method to spread out the green tiles randomly
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            tile.color = 'G';
            green_count++;
        }
        // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
        else {
            int color_choice = rand() % 5;
            switch (color_choice) {
                case 0:
                    tile.color = 'B'; // Blue
                    break;
                case 1:
                    tile.color = 'P'; // Pink
                    break;
                case 2:
                    tile.color = 'T'; // Brown
                    break;
                case 3:
                    tile.color = 'R'; // Red
                    break;
                case 4:
                    tile.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane/player 1 or 2
        // Recall i refers to tile 0 to 51
        _tiles[player_index][i] = tile;
    }
}

bool Board::isPlayerOnTile(int player_index, int pos) {
    if (_player_position[player_index] == pos) {
        return true;
    }
    return false;
}

void Board::setGameTrack(int p1_choice, int p2_choice)
{
    //These variables will keep track of which player chose which game mode and thus which player to display
    //0 will mean the player chose track 1 and 1 will mean the player chose track 2
    _p1_decision = p1_choice; 
    _p2_decision = p2_choice;
    if(p1_choice == p2_choice)
    {
        single_track = true;
    }
    else
    {
        single_track = false;
    }
}
void Board::displayTile(int track_index, int pos) {
    string color = "";

    // Using the defined nicenames above
    switch(_tiles[track_index][pos].color) {
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'P': color = PINK; break;
        case 'T': color = BROWN; break;
        case 'R': color = RED; break;
        case 'U': color = PURPLE; break;
    }

  
   //Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

   /*
   Instead of using player index, I am using track index. This is bc if i wrote displayTrack(1) this would display player 2, even if I wanted player one on this track,
   in other words, i couldn't choose the track but rather the player 
   */

   // Start the tile output with the background color and the left border
    cout << color << "|"; 

    // If both players choose the same track, than this if statement will run
    if (!single_track) {
        // Determine which player (P1=0 or P2=1) the track should display
        int playerCheck = -1;
        //If the track index matches the mode player 1 chose, than p1 chose this track and number 1 will be dispalyed
        //In other words if the game mode from displayTrack() is what p1 chose than its 1 that will be displayed
        if (track_index == _p1_decision) { // _p1_track_index is set from the setGameTrack
            playerCheck = 0; //Sets the player to be player 1 as in player 1 owns this track
        //if the track index matches the mode player 2 chose, than p1 chose this track and number 2 will be displayed
        } else if (track_index == _p2_decision) { // Assumes _p2_track_index is set
            playerCheck = 1; 
        }

        // Check P1 
        if (playerCheck == 0 && _player_position[0] == pos) {
            // Print '1' in white, reset foreground, but keep the background color
            cout << "\033[97m" << "1" << "\033[39m" << color; 
        }
        // Check P2
        else if (playerCheck == 1 && _player_position[1] == pos) {
            // Print '2' in black, reset foreground, but keep the background color
            //Need to use "2" and not the (_player_index+1)
            cout << "\033[30m" << "2" << "\033[39m" << color; 
        }
        // Empty tile
        else {
            cout << " "; 
        }
        
    } 
    // Code Logic if both players choose different tracks
    else { 
        // Space 1: Player 1
        //I did not reset because what would happen is the number would print, and than background color would reset printing the remainder in black, giving a visual fade
        //This way, the background color will stay untouched and rather the foreground color will change

        if (_player_position[0] == pos) {
            // Print '1' in white, reset foreground, but keep the background color
            cout << "\033[97m" << "1" << "\033[39m" << color;
        } else {
            cout << " ";
        }
        
        // Space 2: Player 2
        if (_player_position[1] == pos) {
            // Print '2' in black, reset foreground, but keep the background color
            cout << "\033[30m" << "2" << "\033[39m" << color;
        } else {
            cout << " ";
        }
    }
    
    // --- 4. End Tile ---
    // Print the right border and reset all formatting
    cout << "|" << RESET; 
}

// =========================== Public Member Functions ===========================

void Board::initializeBoard() {
    for (int i = 0; i < 2; i++) {
        // This ensures each lane (or each player) has a unique tile distribution
        initializeTiles(i);
    }
}

void Board::displayTrack(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(player_index, i);
    }
    cout<<RESET<< endl;
    //cout << endl;
}

void Board::displayBoard() {
    for (int i = 0; i < 2; i++) {
        displayTrack(i);
        if (i == 0) {
            cout << endl; // Add an extra line between the two lanes
        }
    }
}

bool Board::movePlayer(int player_index) {
    // Increment player position by 1
    _player_position[player_index]++;

    // Player reached last tile
    if (_player_position[player_index] == _BOARD_SIZE - 1) {
        return true;
    }

    return false;
}


int Board::getPlayerPosition(int player_index) const {
    if (player_index >= 0 && player_index <= _player_count) {
        return _player_position[player_index];
    }
    return -1;
}

//-------------------------------Methods I add--------------------------------

//This returns  
Tile Board::getTile(int playerIndex, int position)
{
    if(playerIndex >=0 && playerIndex < 2 && position >= 0 && position < _BOARD_SIZE)
    {
        //Return the tile[the player the tile is checking][the positoin of this character]
        return _tiles[playerIndex][position];
    }
    Tile emptyTile;
    return emptyTile;
}






