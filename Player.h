#include <iostream>

using namespace std;

class Player
{
    private:
    string name_;
    int experience_;
    int accuracy_;
    int efficiency_;
    int insight_;
    int discoverPoints_;

    string name[10];
    string questions[30];
    string answers[30];

    string descriptions[50];

    int pathType[50];
    int advisors[50];
    int discoverPointsEvents[50];
    int eventsLoaded = 0;
    int riddlesLoaded = 0;



    int experience[10];
    int accuracy[10];
    int efficiency[10];
    int insight[10];
    int discoverPoints[10];

    int track_gameMode;
    int currentPos;
    int myAdvisors[5] = {0,0,0,0,0};

    public:
    int choice;
    //Might not need these anymore or can change later
    int advisorChoice;
    bool advisor;

    string advisorName;
    int trackChoice;

    string getName();
    string getAdvisorName();
    int getExperience();
    int getAccuracy();
    int getEfficiency();
    int getInsight();
    int getDiscoverPoints();
    int getPosition();
    bool getAdvisor();
    int getTrackChoice();
    bool hasAdvisor(int);

    string getAdvisorName(int);
    void printAdvisor();


    void chooseCharacterName(int);
    void chooseGameMode(int);
    void readCharacterFile();
    void readRiddleFile();
    void readRandomEventsFile();
    int chooseRandomEvent(int);
    void chooseAdvisor(int);
    void advisorList();
    void addAdvisor(int);
    void chooseRandomRiddleFile();

    

    void setExperience(int);
    void setAccuracy(int);
    void setInsight(int);
    void setDiscoverPoints(int);
    void setEfficiency(int);
    void setPosition(int);

    Player();

    void storePlayerStats(int);
};