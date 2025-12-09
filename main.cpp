#include <iostream>
#include "Board.h"
#include "Player.h"

using namespace std;



int main()
{
    srand(time(0));
    TileChallenge bio;
    Board b;
    Player p1;
    Player p2;
    bio.strandSimilarity("bob", "tm");
    p1.readRiddleFile();
    p2.readRiddleFile();
    p1.readRandomEventsFile();
    p2.readRandomEventsFile();
    p1.readCharacterFile();
    cout<<"Player 1:"<<endl;
    p1.chooseCharacterName(-1);
    cout<<endl;
    p2.readCharacterFile();
    cout<<"Player 2: "<<endl;
    p2.chooseCharacterName(p1.choice);

    cout<<"choose your game mode"<<endl;
    cout<<" 0: Training Fellowship | 1: Direct Lab Assignment"<<endl;

    cout<<"Choose your game mode player 1"<<endl;
    bool gameMode = false;

    int modeDecision1;

    //Looping my game to ensure a valid game mode is chosen by both characters
    while(!gameMode)
    {
        cin>>modeDecision1;
        if(modeDecision1 > 1 || modeDecision1 <0)
        {
            cout << "Not a valid game mode P1, try again"<<endl;
            continue;
        }
        else
        {
            gameMode = true;
        }
    }
    cout<<"Choose your game mode player 2"<<endl;
    int modeDecision2;
    gameMode = false;

    while(!gameMode)
    {
        cin>>modeDecision2;
        if(modeDecision2 > 1 || modeDecision2 <0)
        {
            cout << "Not a valid game mode P2, try again" <<endl;
            continue;
        }

        else
        {
            gameMode = true;
        }
    }



    b.setGameTrack(modeDecision1, modeDecision2);

    //Might remove these and just use the getter methods directly
    int p1currentDiscoveryPoints = p1.getDiscoverPoints();
    int p1currentExperiencePoints = p1.getExperience();
    int p1currentAccuracyPoints = p1.getAccuracy();
    int p1currentEfficiencyPoints = p1.getEfficiency();
    int p1currentInsightPoints = p1.getInsight();

    int p2currentDiscoveryPoints = p2.getDiscoverPoints();
    int p2currentExperiencePoints = p2.getExperience();
    int p2currentAccuracyPoints = p2.getAccuracy();
    int p2currentEfficiencyPoints = p2.getEfficiency();
    int p2currentInsightPoints = p2.getInsight();
    
    // (P1 and P2 chose the same game mode)
    if (modeDecision1 == modeDecision2) 
    {
        // P1's choice (modeDecision1) is the track index (0: Training Fellowship or 1: Direct Lab Assignment)
        cout << "Player 1 and Player 2 have chosen the same game mode (Mode " << modeDecision1 << ")" << endl;
        b.displayTrack(modeDecision1);

        if(modeDecision1 == 0)
        {
            p1.setDiscoverPoints(p1currentDiscoveryPoints - 500);
            p1.setAccuracy(p1currentAccuracyPoints + 500);
            p1.setEfficiency(p1currentEfficiencyPoints + 500);
            p1.setInsight(p1currentInsightPoints + 1000);
            cout << "P1: Your updated stats with this mode are" << " | Exp: " << p1.getExperience() << " | Accuracy: " << p1.getAccuracy() << " | Efficiency: " << p1.getEfficiency() << " | Insight: " << p1.getInsight() << " | Discovery Points: " << p1.getDiscoverPoints() << endl;      

            p2.setDiscoverPoints(p2currentDiscoveryPoints - 500);
            p2.setAccuracy(p2currentAccuracyPoints + 500);
            p2.setEfficiency(p2currentEfficiencyPoints + 500);
            p2.setInsight(p2currentInsightPoints + 1000);
            cout << "P2: Your updated stats with this mode are" << " | Exp: " << p2.getExperience() << " | Accuracy: " << p2.getAccuracy() << " | Efficiency: " << p2.getEfficiency() << " | Insight: " << p2.getInsight() << " | Discovery Points: " << p2.getDiscoverPoints() << endl;

            p1.advisorList();
            cout<<"Player 1: ";
            p1.chooseAdvisor(-1);
            p1.advisor = true;

            p2.advisorList();
            cout<<"Player 2: ";
            p2.chooseAdvisor(p1.advisorChoice);
            p2.advisor = true;

            p1.trackChoice = 0;
            p2.trackChoice = 0;


        }

        else
        {
            p1.setDiscoverPoints(p1currentDiscoveryPoints + 500);
            p1.setAccuracy(p1currentAccuracyPoints + 200);
            p1.setEfficiency(p1currentEfficiencyPoints + 200);
            p1.setInsight(p1currentInsightPoints + 200);
            cout << "P1: Your updated stats with this mode are" << " | Exp: " << p1.getExperience() << " | Accuracy: " << p1.getAccuracy() << " | Efficiency: " << p1.getEfficiency() << " | Insight: " << p1.getInsight() << " | Discovery Points: " << p1.getDiscoverPoints() << endl; 

            p2.setDiscoverPoints(p2currentDiscoveryPoints + 500);
            p2.setAccuracy(p2currentAccuracyPoints + 200);
            p2.setEfficiency(p2currentEfficiencyPoints + 200);
            p2.setInsight(p2currentInsightPoints + 200);
            cout << "P2: Your updated stats with this mode are" << " | Exp: " << p2.getExperience() << " | Accuracy: " << p2.getAccuracy() << " | Efficiency: " << p2.getEfficiency() << " | Insight: " << p2.getInsight() << " | Discovery Points: " << p2.getDiscoverPoints() << endl;

            p1.advisor = false;
            p2.advisor = false;

            p1.trackChoice = 1;
            p2.trackChoice = 1;
        }


    } 
    // (P1 and P2 chose different modes)
    else 
    {
        // Player 1's display: Use their choice (modeDecision1) as the track index
        if (modeDecision1 == 0) {
            cout << "Player 1 has chosen the Training Fellowship game mode" << endl;
            //cout<< p1.getDiscoverPoints()<<endl;
            p1.setDiscoverPoints(p1currentDiscoveryPoints - 500);
            p1.setAccuracy(p1currentAccuracyPoints + 500);
            p1.setEfficiency(p1currentEfficiencyPoints + 500);
            p1.setInsight(p1currentInsightPoints + 1000);
            cout << "P1: Your updated stats with this mode are" << " | Exp: " << p1.getExperience() << " | Accuracy: " << p1.getAccuracy() << " | Efficiency: " << p1.getEfficiency() << " | Insight: " << p1.getInsight() << " | Discovery Points: " << p1.getDiscoverPoints() << endl; 
            
            p1.advisorList();
            cout<<"Player 1: ";
            p1.chooseAdvisor(-1);
            p1.advisor = true;
            p1.trackChoice = 0;
            //cout<<p1.getDiscoverPoints()<<endl;
        } else {
            cout << "Player 1 has chosen the Direct Lab Assignment game mode" << endl;
            p1.setDiscoverPoints(p1currentDiscoveryPoints + 500);
            p1.setAccuracy(p1currentAccuracyPoints + 200);
            p1.setEfficiency(p1currentEfficiencyPoints + 200);
            p1.setInsight(p1currentInsightPoints + 200);
            cout << "P1: Your updated stats with this mode are" << " | Exp: " << p1.getExperience() << " | Accuracy: " << p1.getAccuracy() << " | Efficiency: " << p1.getEfficiency() << " | Insight: " << p1.getInsight() << " | Discovery Points: " << p1.getDiscoverPoints() << endl; 
            p1.advisor = false;       
            p1.trackChoice = 1;
        }
        cout << endl;
        b.displayTrack(modeDecision1);
        
        cout << endl; // Additional Space between two tracks to Separate them
        
        // Player 2's display: Use their choice (modeDecision2) as the track index
        if (modeDecision2 == 0) {
            cout << "Player 2 has chosen the Training Fellowship game mode" << endl;
            p2.setDiscoverPoints(p2currentDiscoveryPoints - 500);
            p2.setAccuracy(p2currentAccuracyPoints + 500);
            p2.setEfficiency(p2currentEfficiencyPoints + 500);
            p2.setInsight(p2currentInsightPoints + 1000);
            cout << "P2: Your updated stats with this mode are" << " | Exp: " << p2.getExperience() << " | Accuracy: " << p2.getAccuracy() << " | Efficiency: " << p2.getEfficiency() << " | Insight: " << p2.getInsight() << " | Discovery Points: " << p2.getDiscoverPoints() << endl;
            p2.advisorList();
            cout<<"Player 2: ";
            p2.chooseAdvisor(p1.advisorChoice);  
            p2.advisor = true;  
            p2.trackChoice = 0;    

        } else {
            cout << "Player 2 has chosen the Direct Lab Assignment game mode" << endl;
            p2.setDiscoverPoints(p2currentDiscoveryPoints + 500);
            p2.setAccuracy(p2currentAccuracyPoints + 200);
            p2.setEfficiency(p2currentEfficiencyPoints + 200);
            p2.setInsight(p2currentInsightPoints + 200);
            cout << "P2: Your updated stats with this mode are" << " | Exp: " << p2.getExperience() << " | Accuracy: " << p2.getAccuracy() << " | Efficiency: " << p2.getEfficiency() << " | Insight: " << p2.getInsight() << " | Discovery Points: " << p2.getDiscoverPoints() << endl;
            p2.advisor = false;  
            p2.trackChoice = 1;      

        }

        b.displayTrack(modeDecision2);

        
        
    }
    int decision = 0;
    int deepDecision;
    bool gameEnd = false;
    int currentPlayerIndex = 0;
    Player players[] = {p1,p2};
    int playersFinished = 0;
    bool playerFinished[] = {false, false};
    while(!gameEnd)

    {
        //current player, either 1 or 2
        int currentPlayer = currentPlayerIndex + 1;
        bool turn = true;

        if(playerFinished[currentPlayerIndex])
        {
            cout << "player " << currentPlayer << " has completed the game, wait for everyone else to finish"<<endl; 
            turn = false;
        }
        while(turn)
        {
            cout << "It is you turn player " << currentPlayer << endl;

            cout<<"Choose a corresponding number to decide next steps "<<endl;
            cout<<"(1) Review Discover Points"<<endl;
            cout<<"(2) Review Character Name or Review Brief Game Instructions "<< endl;
            cout<<"(3) Display Current Position"<<endl;
            cout<<"(4) Display Advisor"<<endl;
            cout<<"(5) Roll Your Dice and Move Your Character"<<endl;
            
            cin>>decision;

            if(decision < 1 || decision > 6)
            {
                cout << "Not a valid option" << endl;
                continue;
        
            }
            else if(decision == 1)
            {
                cout << "(" << "1" << ")" << "Review Discover Points or" << "(" << "2" << ")" << "Review Trait stats"<<endl;
                cin>>deepDecision;  
                if(deepDecision == 1)
                {
                    cout<<"You have ";
                    cout << players[currentPlayerIndex].getDiscoverPoints()<< " Discovery Points"<<endl;
                    continue;
                }
                else if(deepDecision == 2)
                {
                    cout << "Experience: " << players[currentPlayerIndex].getExperience()<<endl;
                    cout << "Accuracy: " << players[currentPlayerIndex].getAccuracy()<<endl;
                    cout << "Effiiciency: " <<players[currentPlayerIndex].getEfficiency()<<endl;
                    cout << "Insight: " << players[currentPlayerIndex].getInsight()<<endl;
                    continue;
                }
            }
            else if(decision == 2)
            {
                cout << "(" << "1" << ")" << "Check Character Name" << "(" << "2" << ")" << "Guide on navigating the game"<<endl;
                cin>>deepDecision;
                if(deepDecision == 1)
                {
                cout << "Your character name is "<<players[currentPlayerIndex].getName()<<endl;
                continue;
                }
                else if(deepDecision == 2)
                {
                    cout << "--------------------------------------------------"<<endl;
                    cout << "The rules are simple, whenever you are ready type the number 5 to move your character. As you move your character you will"<<endl;
                    cout << "be met with various challenges and occurences with different tiled colors. Player that has the most points at the end of the game will win. " <<endl;
                    cout << "Take your time and work hard on the various challenges that will arise. Good Luck! " <<endl;
                    cout << "---------------------------------------------------"<<endl;
                    continue;
                }
            }
            else if(decision == 3)
            {
                cout << "Here is your current position"<<endl;
                b.displayTrack(players[currentPlayerIndex].getTrackChoice());
                continue;
            }
            else if(decision == 4)
            {
                players[currentPlayerIndex].printAdvisor();
                cout << "You advisor will automatically be used to protect you if they fit the event type" << endl;
            }
            else if(decision == 5)
            {
                
                int diceRoll = (rand()%6) +1;
                cout<<"You rolled a "<<diceRoll<<endl;
                for(int i = 0; i<diceRoll; i++)
                {
                    b.movePlayer(currentPlayerIndex);
                }
                b.displayTrack(players[currentPlayerIndex].getTrackChoice());
                turn = false;
                if(b.getPlayerPosition(currentPlayer - 1) >= 52) //Might change to players[currentPlayerIndex].getPosition() >=52
                {
                    playerFinished[currentPlayerIndex] = true;
                    playersFinished++;
                    cout<< "Player " << currentPlayer << " has completed the game" << endl;
                }

                int newPos = b.getPlayerPosition(currentPlayerIndex);

                Tile currentTile = b.getTile(currentPlayerIndex, b.getPlayerPosition(currentPlayerIndex));
                
                if(currentTile.greenTile() == true)
                {
                    
                    cout << "A random event has been triggered" << endl;
                    int currentPath = players[currentPlayerIndex].getTrackChoice();
                    //int result = players[currentPlayerIndex].chooseRandomEvent(currentPath);
                    players[currentPlayerIndex].chooseRandomEvent(currentPath);
                }
                else if(currentTile.purpleTile() == true)
                {
                    cout << "You found a riddle"<<endl;
                    players[currentPlayerIndex].chooseRandomRiddleFile();
                }
                else if(currentTile.blueTile() == true)
                {
                    int pointsWon = bio.runStrandSimilarity();
                    players[currentPlayerIndex].setDiscoverPoints(players[currentPlayerIndex].getDiscoverPoints() + pointsWon);
                    cout << "Your updated Discovery Points are " << players[currentPlayerIndex].getDiscoverPoints()<<endl;
                }
                else if(currentTile.pinkTile() == true)
                {
                    int playGame = bio.runBestStrandMatch();
                    players[currentPlayerIndex].setDiscoverPoints(players[currentPlayerIndex].getDiscoverPoints() + playGame);
                    cout << "Your updated stats are " << players[currentPlayerIndex].getDiscoverPoints()<< endl; 

                }
                else if(currentTile.redTile() == true)
                {
                    bio.runIdentifyMutations();
                }
                else if(currentTile.brownTile() == true)
                {
                    bio.runTranscribeDNAtoRNA();
                }
                else
                {
                    cout << "All Quite on the track, for now" << endl;
                }
                
                
                turn = false;
            }        
            else if(decision == 6)
            {
                cout << "Are you trying to lost the game, your turn was skipped" <<endl;
                turn = false;
            }    

        }
        if(playersFinished == 2)
        {
            gameEnd = true;
            cout << "All players have finished the game"<<endl;
            cout << "For every 100 in each category, you recieve 1000 discovery points. Most discovery points win"<<endl;
            players[0].setExperience((players[0].getExperience() / 100) * 1000);
            players[0].setAccuracy((players[0].getAccuracy() / 100) * 1000);
            players[0].setEfficiency((players[0].getEfficiency() / 100) * 1000);
            players[0].setInsight((players[0].getInsight() / 100) * 1000);
    
            players[1].setExperience((players[1].getExperience() / 100) * 1000);
            players[1].setAccuracy((players[1].getAccuracy() / 100) * 1000);
            players[1].setEfficiency((players[1].getEfficiency() / 100) * 1000);
            players[1].setInsight((players[1].getInsight() / 100) * 1000);

            players[0].setDiscoverPoints(players[0].getExperience() + players[0].getAccuracy() + players[0].getEfficiency() + players[0].getInsight() + players[0].getDiscoverPoints());
            cout << "Player 1 Final Score: " << players[0].getDiscoverPoints() <<endl;
            players[1].setDiscoverPoints(players[1].getExperience() + players[1].getAccuracy() + players[1].getEfficiency() + players[1].getInsight() + players[1].getDiscoverPoints());
            cout << "Player 2 Final Score: " << players[1].getDiscoverPoints() << endl;

            cout << "---------------------------------------------------------------" << endl;
            if(players[0].getDiscoverPoints() > players[1].getDiscoverPoints())
            {
                cout << "       Winner Winner Chicken Dinner: Player 1      " << endl; 
            }
            else if(players[0].getDiscoverPoints() < players[1].getDiscoverPoints())
            {
                cout << "       Winner Winner Chicken Dinner: Player 2      " <<endl;
            }
            else
            {
                cout << "       It's a Tie      " <<endl;
            }
            cout << "--------------------------------------------------------------" << endl;
        }
        if(!gameEnd)
        {
            currentPlayerIndex = (currentPlayerIndex + 1) % 2;
        }
    }



    return 0;
    
}



