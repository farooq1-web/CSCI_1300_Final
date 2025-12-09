#include <cstdlib>
#include <iostream>
#include <string>

using namespace std; 
struct Tile {
    char color;


    bool greenTile()
    {
        if(color == 'G')
        {
            return true;
        }
        return false;
    }
    bool blueTile()
    {
        if(color == 'B')
        {
            return true;
        }
        return false;
    }
    bool purpleTile()
    {
        if(color == 'U')
        {
            return true;
        }
        return false;
    }

    bool pinkTile()
    {
        if(color == 'P')
        {
            return true;
        }
        return false;
    }

    bool redTile()
    {
        if(color == 'R')
        {
            return true;
        }
        return false;
    }

    bool brownTile()
    {
        if(color == 'T')
        {
            return true;
        }
        return false;
    }

};


class TileChallenge
{
    private:
    char _color;
    char challengeType;
   
    public:
    TileChallenge();
    char getChallengeType();
    char getColor();
    string generateRandomStrand(int);
    string generateFixedStrand(int);
    double strandSimilarity(string, string);
    int runStrandSimilarity();

    int bestStrandMatch(string, string);
    int runBestStrandMatch();
    
    void identifyMutations (string input_strand, string target_strand);
    void runIdentifyMutations();
    void transcribeDNAtoRNA(string);
    void runTranscribeDNAtoRNA();
};


