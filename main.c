/*Roots Assignment
*Author: Solomon Scobie
*Student No: 3302821
*Date: 17/05/18
*Description: This program takes input in the form of text files and translates them into arrays to relay details
*about the results of football/soccer matches
*/

// * Calling the necessary libraries, while here I will add that because this was initially written outside of visual
// * studio all of the printf and fprintf statements have both versions written in but stdio.h is commented out
#include "stdafx.h"
//#include <stdio.h>
#include <math.h>

int main(void)
{
  // Defininf the team structure with variables for all the requisite data we wish to store and record
  struct Team {
    char name[16];
    char group;
    int gPlayed;
    int gWon;
    int gLost;
    int gDrawn;
    int goalsFor;
    int goalsAgainst;
    int points;
  }
  FILE *teamList, *resultList;

  fopen_s(&teamList, "input.dat", "r");
  bool loop = true
  Team participatingTeams[];
  do{
    if (fscanf_s(inputFile, "%s", &operationType)==EOF)
		{
			loop = false;
		}
		if (fscanf_s(inputFile, "%c\n", &input) == EOF)
		{
			loop = false;
		}

  } while(loop == true);

}
