#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

Player::Player()
{
    setExperience(0);
    setAccuracy(0);
    setInsight(0);
    setDiscoverPoints(0);
}

int Player::getExperience()
{
    return experience_;
}
int Player::getAccuracy()
{
    return accuracy_;
}
int Player::getEfficiency()
{
    return efficiency_;
}
int Player::getInsight()
{
    return insight_;
}
int Player::getDiscoverPoints()
{
    return discoverPoints_;
}
int Player::getPosition()
{
    return currentPos;
}
string Player::getName()
{
    return name_;
}
bool Player::getAdvisor()
{
    return advisor;
}
string Player::getAdvisorName()
{
    return advisorName;
}
int Player::getTrackChoice()
{
    return trackChoice;
}

void Player::setExperience(int _experience)
{
    experience_ = _experience;
}

void Player::setAccuracy(int _accuracy)
{
    accuracy_ = _accuracy;
}
void Player::setEfficiency(int _efficiency)
{
    efficiency_ = _efficiency;
} 

void Player::setInsight(int _insight)
{
    insight_ = _insight;
}

void Player::setDiscoverPoints(int _discoverPoints)
{
    discoverPoints_ = _discoverPoints; 
}
void Player::setPosition(int _currentPos)
{
    currentPos = _currentPos;
}


void Player::readCharacterFile()
{    
    ifstream playableChar("characters.txt");
    if(!playableChar.is_open())
    {
        cout<<"Could not open Characters.txt"<<endl;
    }
    string lines[10];
    int num = 0;
    string test;
    string section;
    string temp;
    string trash;
    getline(playableChar, trash);
    while(getline(playableChar, name[num], '|') && num<10)
    {
        getline(playableChar, temp, '|');
        experience[num] = stoi(temp);

        getline(playableChar, temp, '|');
        accuracy[num] = stoi(temp);

        getline(playableChar, temp, '|');
        efficiency[num] = stoi(temp);

        getline(playableChar, temp, '|');
        insight[num] = stoi(temp);

        getline(playableChar, temp);
        discoverPoints[num] = stoi(temp);

        cout << num +1 << ") " << name[num] << " | Exp: " << experience[num] << " | Accuracy: " << accuracy[num] << " | Efficiency: " << efficiency[num] << " | Insight: " << insight[num] << " | Discovery Points: " << discoverPoints[num] << endl;        
        num++;
    }
    playableChar.close();
   
}
void Player::readRiddleFile()
{
    string line;  
    ifstream riddle("riddles.txt");
    int num = 0;
    string tempStore;
    if(!riddle.is_open())
    {
        cout<<"Could not open riddles.txt"<<endl;
    }
    getline(riddle, line);
    while(getline(riddle, questions[num],'|') && num<30)
    {
        getline(riddle, answers[num]);
        num++;
    }
    riddlesLoaded = num;


    riddle.close();


}
void Player::chooseRandomRiddleFile()
{
    int random = rand() % riddlesLoaded;

    string input;
    cout << "You have landed on a riddle, answer the question correctly to boost your points" <<endl;
    cout << questions[random]<<endl;

    cin >> input;
    if(input == answers[random])
    {
        cout << "Wow, your really good at this" << endl;
        discoverPoints_ += 500;
        cout << "Your updated discovery points are " << discoverPoints_ << " Discover Points" << endl;
    }
    else
    {
        cout << "you did not input the correct answer, you have failed" <<endl;
    }
}
void Player::readRandomEventsFile()
{
    string line;
    ifstream randomEvent("random_events.txt");
    string instructions;
    string skipLine;
    string temp;
    string current;
    int num = 0; 
    if(!randomEvent.is_open())
    {
        cout << "Could not open random_events.txt"<<endl;
    }
    getline(randomEvent, skipLine);
    getline(randomEvent, skipLine);
    while(num < 49 && getline(randomEvent, current, '|'))
    {
        //rfind find the corresponding character in the string, which in my case is the //
        //Check for comments or blank lines
        if(current.rfind("//", 0)==0 || current.empty())
        {
            getline(randomEvent, skipLine);
            continue;
        }
        //If the line above is not a comment, store it
        descriptions[num] = current;
        getline(randomEvent, temp, '|');
        pathType[num] = stoi(temp);
        
        getline(randomEvent, temp, '|');
        advisors[num] = stoi(temp);

        getline(randomEvent, temp);
        discoverPointsEvents[num] = stoi(temp);

        // cout << "Description: " << descriptions[num] << '|';
        // cout << " Path Type: " << pathType[num]<< '|';
        // cout << " Advisor: " << advisors[num]<< '|';
        // cout << " Discovery Points: " << discoverPointsEvents[num] << endl;

        num++;
    }
    
    eventsLoaded = num;
}
//Looks through array of advisors and adds the advisor to this array to show that this advisor has been added
void Player::addAdvisor(int advisorID)
{
    for(int i=0; i<5; i++)
    {
        if(myAdvisors[i] == 0)
        {
            myAdvisors[i] = advisorID;
            return;
        }
    }
}
int Player::chooseRandomEvent(int currentPath)
{
    int random = 0;
    bool foundValidEvent;
    int attempts = 0;
    //bool input = true;

    int halfChance = rand()%2;
    if(halfChance == 0)
    {
        cout<< "--------------------------"<<endl;
        cout << "You hear a noise pass by, it must've been nothing"<<endl;
        return 0;
    }
    while(!foundValidEvent && attempts <100)
    {
        random = rand() % eventsLoaded;
        if(pathType[random]  == 0 || pathType[random] == currentPath)
        {
            foundValidEvent = true;
        }
        attempts++;
    }

    cout << "--------------------------------" << endl;
    cout << "--- Event ---" <<endl;
    cout << descriptions[random]<<endl;
    cout << "This event only corresponds to path " << pathType[random]<<endl;
    if(discoverPointsEvents[random] < 0 && advisors[random] > 0)
    {
        if(hasAdvisor(advisors[random]))
        {
            cout << "Your advisor has saved the day" << endl;
            cout << getAdvisorName(advisors[random]) << "Steps in to prevent you any harm" <<endl; 
            cout << "They bravely prevented the loss of " << abs(discoverPointsEvents[random]) << " Discovery Points" << endl;
            cout << "Net change 0 points " <<endl;


            return 0;
        }
        else
        {
            cout << "Bad Luck: You did not have the right advisor to stop this" << endl;
            cout << "Loss: " << discoverPointsEvents[random] << " Discovery Points" <<endl;
        }
    }
    else
    {
        if(discoverPointsEvents[random] > 0)
        {
            cout << "Nice Work, you gain " << discoverPointsEvents[random] << " Discover Points" << endl;
        }
        else
        {
            cout << "Result: " << discoverPointsEvents[random] << " Discover Points " << endl;
        }
    }
    discoverPoints_ += discoverPointsEvents[random];
    cout << "Current total Score " << discoverPoints_ << endl;
    cout << "----------------------------------------"<<endl;
    return discoverPointsEvents[random];
}

string Player::getAdvisorName(int id)
{
    switch (id)
    {
    case 1: return "Dr. Aliquot";
    break;
    case 2: return "Dr. Assembler";
    break;
    case 3: return "Dr. Pop-Gen";
    break;
    case 4: return "Dr. Bio-Script";
    break;
    case 5: return "Dr. Loci";
    break;
    default: return "Unknown Advisor";
    break;
    }

}
bool Player::hasAdvisor(int ID)
{
    for(int i = 0; i< 5; i++)
    {
        if(myAdvisors[i] == ID)
        {
            return true;
        }
    }
    return false;
}


void Player::printAdvisor()
{
    cout << "your advisor - ";
    bool found = false;
    for(int i =0; i<5; i++)
    {
        int id = myAdvisors[i];
        if(id!=0)
        {
            cout <<" Slot " << (i+1) << ": " << getAdvisorName(id) << " (ID: " << id << ")" << endl;
            found = true;
        }
    }
    if(!found)
    {
        cout<< "no advisors available"<<endl;
    }
}
void Player::storePlayerStats(int i)
{
    if(i < -1 || i > 5)
    {
        cout << "Invalid Player Stats";
    }
    else
    {
    name_ = name[i];
    experience_ = experience[i];
    accuracy_ = accuracy[i];
    efficiency_ = efficiency[i];
    insight_ = insight[i];
    discoverPoints_ = discoverPoints[i];
    cout << name[i] << " | Exp: " << experience[i] << " | Accuracy: " << accuracy[i] << " | Efficiency: " << efficiency[i] << " | Insight: " << insight[i] << " | Discovery Points: " << discoverPoints[i] << endl;        
    }

    
}

void Player::chooseCharacterName(int check)
{
    bool characterState = false;
    int checkPlayer = check;
    int decision = 0;
    
    while(!characterState)
    {
        cout<<"Choose your character now with the corresponding number: ";
        cin>>decision;
        if(checkPlayer == decision)
        {
            cout<<"This player has already been chosen, try again"<<endl;
            continue;
        }
        if(decision < 1 || decision > 5)
        {
            cout<<"Invalid number, not a character option"<<endl;
            //This will bring the code back to the top of the while statement
            continue;
        }
        else
        {
            characterState = true;
        }
    }
    switch (decision)
    {
    case 1 : cout<<"You chose Dr. Leo "<<endl;
    storePlayerStats(decision -1);
    break;
    case 2: cout<<"You chose Dr.Helix"<<endl;
    storePlayerStats(decision-1);
    break;
    case 3: cout<< "You chose Dr. Panthera"<<endl;
    storePlayerStats(decision-1);
    break;
    case 4: cout<< "You chose Dr.Adenine"<<endl;
    storePlayerStats(decision-1);
    break;
    case 5: cout<< "You chose Dr. K-mer"<<endl;
    storePlayerStats(decision-1);
    break;
    default: cout<<"This is an invalid choice, not a character"<<endl;
    break;
    }


    choice = decision;

}
void Player::advisorList()
{
    cout<<"Since you chose the training fellowship, you will be able to choose an adivsor to help you along your journey" << endl;
    cout<<"1. Dr. Aliquot - A master of the wet lab, assisting in avoiding contamination" <<endl;
    cout<<"2. Dr. Assembler - An expert who helps improve efficiency and streamlines pipelines" <<endl;
    cout<<"3. Dr. Pop-Gen - A genetics specialist with insight for identifying rare genetic variants" << endl; 
    cout<<"4. Dr. Bio-Script - The genius behind the data analysis, helps debug code" <<endl;
    cout<<"5. Dr. Loci - Your biggest supporter assisting you in learning the equipment" << endl;
}
void Player::chooseAdvisor(int person)
{
    bool advisorState = false;
    int decision = 0;
    int personChoice = person;

    while(!advisorState)
    {
        cout<<"choose your advisor  (1-5): "<<endl;
        cin >> decision;
        if(decision < 1 || decision > 5)
        {
            cout << "Invalid advisor. Choose a number from 1 to 5"<<endl;
            continue;
        }
        if(personChoice == decision)
        {
            cout<<"This advisor has already been chosen, try again"<<endl;
            continue;
        }
        else
        {
            advisorState = true;
        }
    }
    addAdvisor(decision);

    switch (decision)
    {
    case 1: cout<< "You chose Dr. Aliquot: A master of the wet lab, assisting in avoiding contamination" << endl;
    advisorName = "Dr. Aliquot: A master of the wet lab, assisting in avoiding contamination";
    break;
    case 2: cout<<"You chose Dr. Assembler: An expert who helps improve efficiency and streamlines pipelines" <<endl;
    advisorName = "Dr. Assembler: An expert who helps improve efficiency and streamlines pipelines";
    break;
    case 3: cout<<"You chose Dr. Pop-Gen: A genetics specialist with insight for identifying rare genetic variants" << endl; 
    advisorName = "Dr. Pop-Gen: A genetics specialist with insight for identifying rare genetic variants";
    break;
    case 4: cout<<"You chose Dr. Bio-Script: The genius behind the data analysis, helps debug code" << endl;
    advisorName = "Dr. Bio-Script: The genius behind the data analysis, helps debug code";
    break;
    case 5: cout<<"You chose Dr. Loci: Your biggest supporter assisting you in learning the equipment" << endl;
    advisorName = "Dr. Loci: Your biggest supporter assisting you in learning the equipment";
    break;
    default: cout << "You chose an invalid advisor, choose again" <<endl;
    break;
    }

    advisorChoice = decision;

}






