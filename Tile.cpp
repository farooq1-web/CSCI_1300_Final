#include "Tile.h"

#include <iostream>
using namespace std;

char TileChallenge::getChallengeType()
{
    return challengeType;
}
//Not an important function
char TileChallenge::getColor()
{
    return _color;
}

TileChallenge::TileChallenge()
{
    _color = 'G';
}

//This will generate a strand of random length
string TileChallenge::generateRandomStrand(int length)
{
    char DNA[4] = {'A', 'T', 'G', 'C'};
    string randomStrand = "";
    for(int i = 0; i<length; i++)
    {
        int randomBase = rand() % 4;  
        randomStrand += DNA[randomBase];
    }
    return randomStrand;
}
//This function is used to generate the similarity score
double TileChallenge::strandSimilarity(string strand1, string strand2)
{
    if(strand1.length() != strand2.length())
    {
        //cout << "Your strand did not match the length of the given strand"<<endl;
        return 0.0;
    }
    double totalMatches = 0;
    int totalPositions = strand1.length();
    for(int i =0; i<totalPositions; i++)
    {
        if(strand1[i] == strand2[i])
        {
            totalMatches++;
        }
    }

    double similarity;
    similarity = totalMatches / totalPositions;

    return similarity;
}

int TileChallenge::runStrandSimilarity()
{
    int random = (rand() % 15) + 10;
    string targetDNA = generateRandomStrand(random);

    cout << "DNA Sequencing Challenge"<<endl;
    cout << "Target Strand: " << targetDNA << endl;
    cout << "Length: " << random << endl;
    cout << "You have two options. You may take your chances and have the computer generate a strand or you can manually type the random number of characters" <<endl;
    cout << "This challenge will require you to type the bases in the same corresponding order and with the same length so decide carefully" << endl;
    cout << "1) Auto Synthesize (Luck): Computer will generate a random string" <<endl;
    cout << "2) Manual Entry (Skill): You will type the strand yourself" <<endl;
    
    string decision;
    string playerDNA;
    bool gameState = true;
    while(gameState)
    {
        cin >> decision;
       
        if (decision == "1")
        {
            playerDNA = generateRandomStrand(random);
            cout << "Generated: " << playerDNA << endl;
            gameState = false;
        }

        else if(decision == "2")
        {
            cout << "You may start typing your strand that will match the strand above" <<endl;
            gameState = false;
            cin >> playerDNA;
            

            if(playerDNA.length() != random)
            {
                cout << "The length of your strand did not match the given strand, maybe next time";
                gameState = false;
            }
        }
        else
        {
            cout << "Invalid output, try again"<<endl;
            continue;
        }
        
    }

    //Calculate score
    double score = strandSimilarity(targetDNA, playerDNA);

    if(score == 1.0)
    {
        cout<< "You got a perfect score. Here is 1000 discoveryPoints"<<endl;
        return 1000;
    }
    else if(score >= 0.5)
    {
        cout<< "You were at least half correct. For that I will still give 500 discoveryPoints"<<endl;
        return 500;
    }
    else
    {
        cout << "Your performance was not that well and you got less than half. I will have to take away 500 discoveryPoints"<<endl;
        return -500;
    }

}


int TileChallenge::bestStrandMatch(string input_strand, string target_strand)
{
    char DNA[4] = {'A', 'T', 'G', 'C'};

    //The best index for the strand to start at 
    int bestIndex = -1;
    int maxMatches = -1;

    //check if input strand is empty
    if(input_strand.empty())
    {
        cout << "No input"<<endl;
        return -1;
    }
    //check if input strand length is longer than target strand length
    if(input_strand.length() > target_strand.length())
    {
        cout << "The strand that was generated was too long"<<endl;
        return -1;
    }
   
    for(int i = 0; i<= ((int)target_strand.length() - (int)input_strand.length()); i++)
    {
        int currentMatches = 0;
        for (int j = 0; j < input_strand.length(); j++)
        {
            if(target_strand[i+j] == input_strand[j])
            {
                currentMatches ++;
            }
        }
            
        if(currentMatches > maxMatches)
        {
            maxMatches = currentMatches;
            bestIndex = i;
        }
    }
    return bestIndex;
}

int TileChallenge::runBestStrandMatch()
{
    int random = (rand() % 6) + 4;
    int randomNum = random + (rand() % 11) + 6;
    cout << "-----------------------------------"<<endl;
    cout << "Unequal Length Similarity challenge"<<endl;

    cout<< "In this challenge, you will need to input the ";
    cout << "best startng index where the two strand will generate the best similarity score"<<endl;

    int decision = 0;
    string playerDNA = generateRandomStrand(random);
    string targetDNA = generateRandomStrand(randomNum);
    bool gameState = true;
    int bestIndex = bestStrandMatch(playerDNA, targetDNA);
    cout << "Here is the strand that was generated" <<endl;
    cout << targetDNA << endl;
    cout << "Here is the strand that you are trying to match to the best of your ability"<<endl;
    cout << playerDNA << endl;
    while(gameState)
    {
        cout<<"Go ahead and and find which starting index you think would lead to the best results" <<endl;
        cin >> decision;
        if(cin.fail())
        {
            cin.clear(); //clear error
            cin.ignore(10000, '\n'); //skip the problematic input
            cout << "Invalid input type, please enter a number"<<endl;
            continue;
        }
        if(decision == bestIndex)
        {
            cout << "Nice, you guessed the most optimal location for the similarity score to be the greatest.";
            return 1000;
            gameState = false;
        }
        else if(decision < bestIndex)
        {
            cout << "not quite" << endl; 
            cout << "The correct answer was " << bestIndex << ". You lose 500 discovery points" << endl;
            gameState = false;
            return -500;
        }
        else
        {
            cout << "Your index answer was too high"<<endl;
            cout << "The correct answer was " << bestIndex << ". You lose 500 discovery points" << endl;
            gameState = false;
            return -500;
        }
    }
    return 0;
}

void TileChallenge::identifyMutations(string input_strand, string target_strand)
{
    bool inputLonger = false;
    string shorterStrand;
    string longerStrand;
    if(input_strand.length() <= target_strand.length())
    {
        shorterStrand = input_strand;
        longerStrand = target_strand;
        inputLonger = false;
    }
    else
    {
        longerStrand = input_strand;
        shorterStrand = target_strand;
        inputLonger = true;
    }
    int startIndex = bestStrandMatch(shorterStrand, longerStrand);


    cout << "----------------Mutation Identification--------------" <<endl;
    cout << "This will output all mutations based on two different DNA strands including: Substitution, Insertion, and Deletion"<<endl;


    cout << "Input DNA strand: " << input_strand <<endl;
    cout << "Target DNA strand: "<< target_strand<<endl;
    cout << "Mutation Allignment: " << startIndex << endl;
    for(int i = 0; i < longerStrand.length(); i++)
    {

        if(i-startIndex >= 0 && i-startIndex < shorterStrand.length())
        {
            if (longerStrand[i] != shorterStrand[i-startIndex])
            {
                cout << "Substitution detected at " << (i+1) << ": " << longerStrand[i] << "!= "<< shorterStrand[i-startIndex] <<endl;
            }
            
        }
        else
        {
            if(inputLonger)
            {
                cout << "Deletion at position" << (i+1) << ": " << longerStrand[i] << " is deleted from target strand " <<endl; 
            }
            else
            {
                cout << "Insertion at position" << (i+1) << ": " <<longerStrand[i] << " is inserted in target strand"<<endl;
            }
        }
   
    }
    cout << endl;
}

void TileChallenge::runIdentifyMutations()
{
    int rand1 = (rand() % 10) +5;
    int rand2 = (rand()%10) +5;
    string input = generateRandomStrand(rand1);
    string target = generateRandomStrand(rand2);
    identifyMutations(input, target);
}

void TileChallenge::transcribeDNAtoRNA(string strand)
{
    //int random = (rand() % 5) +5;    
    //string dnaStrand = generateRandomStrand(random);
    string rnaStrand = strand;
    

    for(int i = 0; i<strand.length(); i++)
    {
        if(strand[i] == 'T')
        {
            rnaStrand[i] = 'U';
        }
    }

    cout<< "You have landed on the tile that will transcribe our DNA to RNA. In other words it will convert every T, with U (not exactly DNA to RNA but hey it works) "<<endl;
    cout << "DNA: Our DNA strand that was generated was " << strand << endl;
    cout<< "RNA: The RNA strand that results from this is " << rnaStrand << endl;

}

void TileChallenge::runTranscribeDNAtoRNA()
{
    int randomDNA = (rand() % 10) +5;
    string random = generateRandomStrand(randomDNA);
    transcribeDNAtoRNA(random);
}
