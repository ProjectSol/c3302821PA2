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
  int grAsNum;
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
void outputTeamStandings(struct Team *list);
void sortByGroup(struct Team *list);
void bubbleSortByGroups(struct Team *list, const int arraySize);



int main(void)
{
  //All the data we will need for sure is pulled and stored into our necessary array here
  struct Team teamList[NUM_TEAMS];
  getTeamList(teamList);
  pullMatchStats(teamList);
  sortByGroup(teamList);
  //Now that we have things defined we can start up our main loop and
  //let the user define which functions of the program they would lke to use
  outputTeamStandings(teamList);
}

void sortByGroup(struct Team *list)
{
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    char ch = list[i].group[0];
    int pos = ch - 'A' + 1;
    list[i].grAsNum = pos;
    printf("%s %d\n",list[i].name,list[i].grAsNum);
  }
  bubbleSortByGroups(list, NUM_TEAMS);
}

void bubbleSortByGroups(struct Team *list, const int arraySize)
{
int	i,	k;
  for(i	=	0;	i	<	arraySize;	i++)
  {
    for(k	=	0;	k	<	arraySize-1;	k++)
    {
      if(abs(list[k].grAsNum) > abs(list[k+1].grAsNum))
      {
        printf("Swapping entries %d and %d",k,i);
        struct Team temp = list[k];
        list[k] = list[i];
        list[i] = temp;
      }
    }
  }
}

void outputTeamStandings(struct Team *list)
{
  char initialGroup[2] = "-";
  //Split for neatness and also doing this for some reason fixed a bug I was having so...
  printf("| Group | %-16s | %-13s | %-13s | %-13s ","Name","Games Played", "Games Won","Games Drawn");
  printf("| %-13s | %-13s | %-13s | %-13s |\n","Games Lost","Goals For", "Goals Against","Points");
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    list[i].points = list[i].gWon*3+list[i].gDrawn;
    struct Team t = list[i];
    if (strcmp(initialGroup,list[i].group)!=0)
    {
      strcpy(initialGroup, list[i].group);
      //Split for neatness and also doing this for some reason fixed a bug I was having so...
      printf("\n| Group | %-16s | %-13s | %-13s | %-13s ","Name","Games Played", "Games Won","Games Drawn");
      printf("| %-13s | %-13s | %-13s | %-13s |\n","Games Lost","Goals For", "Goals Against","Points");

        printf("| %-5s | %-16s | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d |\n",t.group,t.name,t.gPlayed,t.gWon,t.gDrawn,t.gLost,t.goalFor,t.goalAgainst,t.points);
    }
    else
    {
      printf("| %-5s | %-16s | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d |\n","",t.name,t.gPlayed,t.gWon,t.gDrawn,t.gLost,t.goalFor,t.goalAgainst,t.points);
    }
  }
}

void printNameGroup(struct Team *teamList)
{
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    printf("%s\n",teamList[i].name);
    printf("%s\n",teamList[i].group);
    printf("%d\n",teamList[i].goalFor);
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
  int counter = 0;
  while(loop == 1)
  {

    // Reading the file and storing what we need
    if ( fscanf(matchList, "%s %d %s %d", tName1, &score1, tName2, &score2) == EOF )
    {
      printf("End of file has been reached after %d loops\n");
      loop = -1;
    }
    counter ++;

    /*
     * Alright so this was unnecessarily complex but it works just fine, we've got three nested loops
     * and they're all essential to this method working.
     * The first loop is based on the variable loop, original I know, that is merely
     * a check to ensure that we did not reach the end of file before entering into
     * our checks and editing of the team win loss data. The next iterates through twice so
     * that we check both the first and second teams setting our current score and current name
     * accordingly. The third is what acutally loops through each of the existing team names to
     * check that the teams being input actually exist. Towards the end we have a breakout routine
     * all this does is check if we've reached the end of the existing teams or if we found the
     * correct team then moves on to check whether we should update the data and if we should it does.
     */
    if (loop == 1)
    {
      for (int k = 0; k<2; k++)
      {
        char currName[16], altName[16];
        int currScore, altScore;

        if (k == 0)
        {
          currScore = score1;
          strcpy(currName, tName1);
          altScore = score2;
          strcpy(altName, tName2);
        }
        else
        {
          currScore = score2;
          strcpy(currName, tName2);
          altScore = score1;
          strcpy(altName, tName1);
        }

        //printf("%s\n", currName);
        for (int i = 0; i<NUM_TEAMS;i++)
        {
          int compare1 = strcmp(list[i].name, currName);
          if (compare1 == 0)
          {
            if(currScore>=0)
            {
              //printf("%d %s %s\n",i,list[i].name,currName);
              //printf("Great Success!! score: %d name: %s\n", currScore, currName);
              if (k == 0)
              {
                teamNum1 = i;
              }
              else
              {
                teamNum2 = i;
              }
              breakOut = 1;
            }
            else
            {
              //printf("%d %s %s\n",i,list[i].name,currName);
              printf("%s %d %s %d - scores may not be negative, %s\n", tName1, score1, tName2, score2, currName);
              breakOut = -1;
            }
          }
          else
          {
            //printf("%d %s %s\n",i,list[i].name,currName);
            if (i == NUM_TEAMS-1)
            {
              printf("%s %d %s %d - The team name %s does not exist\n", tName1, score1, tName2, score2, currName);
              breakOut = -1;
            }
          }
          if (breakOut == 1)
          {
            //printf("running breakout 1\n");
            breakOut = 0;
            break;
          }
          else if (breakOut == -1)
          {
            //printf("running breakout -1\n");
            break;
          }
        }
        if (breakOut == -1)
        {
          //  printf("breakout -1 part 2");
          break;
        }
      }
      //Once we're out of the first for loop we're checking to see if we should
      //update the data or not and if yes we do that thing.
      if (breakOut != -1)
      {
        list[teamNum1].goalFor += score1;
        list[teamNum2].goalFor += score2;
        list[teamNum1].gPlayed ++;
        list[teamNum2].gPlayed ++;
        if (score1>score2)
        {
          list[teamNum1].gWon ++;
          list[teamNum2].gLost ++;
        }
        else if (score2>score1)
        {
          list[teamNum2].gWon ++;
          list[teamNum1].gLost ++;
        }
        else
        {
          list[teamNum2].gDrawn ++;
          list[teamNum1].gDrawn ++;
        }
        //printf("Values were changed for %s and %s\n", tName1, tName2);
      }
      else
      {
        //printf("No values were changed for %s and %s\n", tName1, tName2);
        breakOut = 0;
      }
    }
  }
  fclose(matchList);
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
