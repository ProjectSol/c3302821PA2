/*Roots Assignment
*Author: Solomon Scobie
*Student No: 3302821
*Date: 17/05/18
*Description: This program takes input in the form of text files and translates them into arrays to relay details
*about the results of football/soccer matches
*/

// * Calling the necessary libraries, while here I will add that because this was initially written outside of visual
// * studio all of the printf and fprintf statements have both versions written in but stdio.h is commented out
//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#define NUM_TEAMS 32

// Defining the team structure with variables for all the requisite data we wish to store and record
struct Team {
  char name[16];
  char group[2];
  int gPlayed;
  int gWon;
  int gLost;
  int gDrawn;
  int goalFor;
  int goalAgainst;
  int points;
} Team;

struct Team newTeamGeneration();
void getTeamList(struct Team *list);
void printNameGroup(struct Team *teamList);
void pullMatchStats(struct Team *list);
void mainLoop(struct Team *list);


int main(void)
{
  //All the data we will need for sure is pulled and stored into our necessary array here
  struct Team teamList[NUM_TEAMS];
  getTeamList(teamList);
  printNameGroup(teamList);
  pullMatchStats(teamList);
  //Now that we have things defined we can start up our main loop and
  //let the user define which functions of the program they would lke to use
  mainLoop(teamList);
}

void printNameGroup(struct Team *teamList)
{
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    printf("%s ",teamList[i].name);
    printf("%s\n",teamList[i].group);
  }
}

void pullMatchStats(struct Team *list)
{
  FILE *matchList;

  printf("opening the matchlist file\n");
  matchList = fopen("match.dat", "r");
  int teamNum1,teamNum2,score1,score2;
  char tName1[16],tName2[16];
  //if not one the while loop dies
  int loop = 1;

  //When breakOut = 0 we continue with our loop, if it is equal to -1 we break
  //and skip the code to run the check on the next aspect before resetting it to
  //be equal to zero. If it is +1 we breakout and run the next check still
  //resetting to zero
  int breakOut = 0;

  while(loop == 1)
  {
    // Reading the file and storing what we need
    if ( fscanf(matchList, "%s %d %s %d", tName1, &score1, tName2, &score2) == EOF )
    {
      loop = -1;
    }

    if (loop == 1)
    {
      for (int i = 0; i<NUM_TEAMS;i++)
      {
        int compare1 = strcmp(list[i].name, tName1);
        if (compare1 == 0)
        {
          if(score1>=0)
          {
            printf("score1: %d name: %s\n", score1, tName1);
            teamNum1 = i;
            breakOut == 1;
          }
          else
          {
            printf("%s %d %s %d - scores may not be negative, %d\n", tName1, score1, tName2, score2, score1);
            breakOut = -1;
          }
        }
        else
        {
          if (i = NUM_TEAMS-1)
          {
            printf("%d %s %s\n",i,list[i].name,tName1);
            printf("%s %d %s %d - The team name %s does not exist\n", tName1, score1, tName2, score2, tName1);
            breakOut = -1;
          }
        }
        if (breakOut == 1)
        {
          printf("running breakout 1\n");
          breakOut == 0;
          break;
        }
        else
        {
          printf("running breakout 2\n");
          breakOut = -1;
          break;
        }
      }
    }

    /*for (int i = 0; i<NUM_TEAMS;i++)
    {
      int compare2 = strcmp(list[i].name, tName2);
      if (compare2 == 0)
      {
        if(score1>=0)
        {
          printf("score1: %d name: %s\n", score2, tName2);
          teamNum1 = i;
          breakOut == 1;
        }
        else
        {
          printf("%s %d %s %d - scores may not be negative, %d\n", tName1, score1, tName2, score2, score2);
          breakOut = -1;
        }
      }
      else
      {
        if (i = NUM_TEAMS-1)
        {
          printf("%d %s %s",i,list[i].name,tName2);
          printf("%s %d %s %d - The team name %s does not exist\n", tName1, score1, tName2, score2, tName2);
          breakOut = -1;
        }
      }
      if (breakOut == 1)
      {
        list[teamNum1].goalFor += score1;
        list[teamNum2].goalFor += score2;
        list[teamNum1].gPlayed ++;
        list[teamNum2].gPlayed ++;
        if (score1>score2)
        {
          list[teamNum1].gWon ++;
          list[teamNum1].gLost ++;
        }
        else
        {
          list[teamNum2].gWon ++;
          list[teamNum1].gLost ++;
        }
      }
      else
      {
        breakOut = -1;
        break;
      }
    }*/
  }
}

void getTeamList(struct Team *list)
{
  FILE *teamList;

  char tName[16];
  char bracket[2];
  teamList = fopen("team.dat", "r");
  int loop = 0;
  struct Team participatingTeams[NUM_TEAMS];
  int tCounter = 0;
  struct Team newTeam = newTeamGeneration();
  do{

    if ( fscanf(teamList, "%s", tName) == EOF )
		{
			loop = -1;
		}
		if ( fscanf(teamList, "%s", bracket) == EOF )
		{
			loop = -1;
		}


    if (loop != -1)
    {
      strcpy(newTeam.name, tName);
      strcpy(newTeam.group, bracket);
      list[tCounter] = newTeam;
      tCounter++;
    }
  } while(loop != -1);
  fclose(teamList);
}

void mainLoop(struct Team *list)
{
  printf("Now you should put in an acutal main loop hey");
}

struct Team newTeamGeneration()
{
  struct Team newTeam;
  newTeam.gPlayed = 0;
  newTeam.gWon = 0;
  newTeam.gLost = 0;
  newTeam.gDrawn = 0;
  newTeam.goalFor = 0;
  newTeam.goalAgainst = 0;
  newTeam.points = 0;

  return newTeam;
}
