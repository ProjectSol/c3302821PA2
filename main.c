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
#include <ctype.h>
#include <stdlib.h>
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

void printBeginningText();

void getTeamList(struct Team *list);
void pullMatchStats(struct Team *list);
void calcPoints(struct Team *list);

void bubbleSortByGroup(struct Team *list);
void bubbleSortByPerform(struct Team *list);
void bubbleSortByAlpha(struct Team *list);

void outputTeamStandings(struct Team *list);
void outputTeamStandingsReverse(struct Team *list);

void outputGroupStandings(struct Team *list);
void sortByGroup(struct Team *list);

void outputAlphabeticalStandings(struct Team *list);
void sortByAlphabet(struct Team *list);

void outputPerformanceStandings(struct Team *list);
void outputByWorstPerformance(struct Team *list);
void sortByPerformance(struct Team *list);

int main(void)
{
  //All the data we will need for sure is pulled and stored into our necessary array here
  struct Team teamList[NUM_TEAMS];
  printBeginningText();
  getTeamList(teamList);
  pullMatchStats(teamList);
  calcPoints(teamList);
  sortByGroup(teamList);
  outputGroupStandings(teamList);
  sortByAlphabet(teamList);
  outputAlphabeticalStandings(teamList);
  sortByPerformance(teamList);
  outputPerformanceStandings(teamList);
  //outputByWorstPerformance(teamList);
}

void calcPoints(struct Team *list)
{
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    list[i].points = list[i].gWon*3+list[i].gDrawn;
  }
  int loop = 0;
  do{
    printf("\nPlease enter \"y\" to continue enter \"n\" if you would instead like to quit without viewing results\n");
    char pressY[2];
    scanf("%s", &pressY);
    if (pressY == "y")
    {
      loop = -1;
    }
    else if (pressY == "n")
    {
      //Ok but like actually why'd you even run the program then
      exit(0);
    }
  } while (loop != -1);
}

void sortByAlphabet(struct Team *list)
{
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    char ch = list[i].group[0];
    int pos = ch - 'A' + 1;
    list[i].grAsNum = pos;
    //printf("%s %d\n",list[i].name,list[i].grAsNum);
  }
  bubbleSortByAlpha(list);
}

void sortByGroup(struct Team *list)
{
  printf("Ordering teams by group...\n\n");
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    char ch = list[i].group[0];
    int pos = ch - 'A' + 1;
    list[i].grAsNum = pos;
    //printf("%s %d\n",list[i].name,list[i].grAsNum);
  }
  bubbleSortByGroup(list);
}

void sortByPerformance(struct Team *list)
{
  for (int i = 0; i<NUM_TEAMS; i++)
  {
    char ch = list[i].group[0];
    int pos = ch - 'A' + 1;
    list[i].grAsNum = pos;
    //printf("%s %d\n",list[i].name,list[i].grAsNum);
  }
  bubbleSortByPerform(list);
}

int groupBubble(struct Team *list, int k, int j)
{
  int groupPos1 = list[k].grAsNum;
  int groupPos2 = list[j].grAsNum;
  if(abs(groupPos1) > abs(groupPos2))
  {
    //printf("%s %d and %s %d         GROUP SWAP\n",list[k].name,list[k].grAsNum,list[j].name,list[j].grAsNum);
    struct Team temp = list[k];
    list[k] = list[j];
    list[j] = temp;
    return 1;
  }
  else if(groupPos1 == groupPos2)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}
int pointsBubble(struct Team *list, int k, int j)
{
  int points1 = list[k].points;
  int points2 = list[j].points;
  if(points1 < points2)
  {
    //printf("%s %d and %s %d         POINTS SWAP\n",list[k].name,list[k].points,list[j].name,list[j].points);
    struct Team temp = list[k];
    list[k] = list[j];
    list[j] = temp;
    return 1;
  }
  else if(points1 == points2)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int differenceBubble(struct Team *list, int k, int j)
{
  int goalDifference1 = list[k].goalFor-list[k].goalAgainst;
  int goalDifference2 = list[j].goalFor-list[j].goalAgainst;
  if(goalDifference1 < goalDifference2)
  {
    //printf("%s %d and %s %d:      GOAL DIFFERENCE SWAP\n",list[k].name,goalDifference1,list[j].name,goalDifference2);
    struct Team temp = list[k];
    list[k] = list[j];
    list[j] = temp;
    return 1;
  }
  else if (goalDifference1 == goalDifference2)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int goalsBubble(struct Team *list, int k, int j)
{
  int goals1 = list[k].goalFor;
  int goals2 = list[j].goalFor;
  if(goals1 < goals2)
  {
    //printf("%s %d and %s %d:      GOAL TOTAL SWAP\n",list[k].name,goals1,list[j].name,goals2);
    struct Team temp = list[k];
    list[k] = list[j];
    list[j] = temp;
    return 1;
  }
  else if(goals1 == goals2)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int alphabetBubble(struct Team *list, int k, int j)
{
  if(strcmp(list[j].name,list[k].name) < 0)
  {
    //printf("%s and %s:     ALPHABETICAL SWAP\n",list[k].name,list[j].name);
    struct Team temp = list[k];
    list[k] = list[j];
    list[j] = temp;
    return 1;
  }
  else if(strcmp(list[k].name,list[j].name) == 0)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}


void bubbleSortByPerform(struct Team *list)
{
}

void bubbleSortByAlpha(struct Team *list)
{
  // now tf is a special variable named after true and false which is a bit of a misnomer but I'm rambling
  // If tf is 1 then the program executed successfully, and did swap the two inputed positions
  // If tf is 0 the variables being compared were equal to each other and thus no action was taken
  // If tf is -1 then nothing occured as both variables were in the correct position.
  int tf;
  int	j, i,	k;
  int arraySize = NUM_TEAMS;
  for(i	=	0;	i	<	arraySize;	i++)
  {
    for(k	=	0;	k	<	arraySize-1;	k++)
    {
      tf = 1;
      int j  = k+1;
      tf = alphabetBubble(list,k,j);

      if(tf == 0)
      {
        tf = pointsBubble(list,k,j);

        if(tf == 0)
        {
          tf = differenceBubble(list,k,j);

          if(tf == 0)
          {
            tf = goalsBubble(list,k,j);
          }
        }
      }
    }
  }
}

void bubbleSortByGroup(struct Team *list)
{
  // now tf is a special variable named after true and false which is a bit of a misnomer but I'm rambling
  // If tf is 1 then the program executed successfully, and did swap the two inputed positions
  // If tf is 0 the variables being compared were equal to each other and thus no action was taken
  // If tf is -1 then nothing occured as both variables were in the correct position.
  int tf;
  int	j, i,	k;
  int arraySize = NUM_TEAMS;
  for(i	=	0;	i	<	arraySize;	i++)
  {
    for(k	=	0;	k	<	arraySize-1;	k++)
    {
      tf = 1;
      int j  = k+1;
      tf = groupBubble(list, k, j);

      if(tf == 0)
      {
        tf = pointsBubble(list,k,j);

        if(tf == 0)
        {
          tf = differenceBubble(list,k,j);

          if(tf == 0)
          {
            tf = goalsBubble(list,k,j);

            if(tf == 0)
            {
              tf = alphabetBubble(list,k,j);
            }
          }
        }
      }
    }
  }
}

void outputAlphabeticalStandings(struct Team *list)
{
  printf("\n");
  outputTeamStandings(list);
}

void outputGroupStandings(struct Team *list)
{
  printf("\n");
  outputTeamStandings(list);
}

void outputPerformanceStandings(struct Team *list)
{
  printf("\n");
  outputTeamStandings(list);
}

void outputByWorstPerformance(struct Team *list)
{
  outputTeamStandingsReverse(list);
}

void outputTeamStandings(struct Team *list)
{
  char initialGroup[2] = "_";
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
      printf("| %-13s | %-13s | %-13s | %-13s | %-13s |\n","Games Lost","Goals For", "Goals Against", "Goal Diff", "Points");

        printf("| %-5s | %-16s | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d |\n",t.group,t.name,t.gPlayed,t.gWon,t.gDrawn,t.gLost,t.goalFor,t.goalAgainst,t.goalFor-t.goalAgainst,t.points);
    }
    else
    {
      printf("| %-5s | %-16s | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d |\n","",t.name,t.gPlayed,t.gWon,t.gDrawn,t.gLost,t.goalFor,t.goalAgainst,t.goalFor-t.goalAgainst,t.points);
    }
  }
}

void outputTeamStandingsReverse(struct Team *list)
{
  char initialGroup[2] = "_";
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
      printf("| %-13s | %-13s | %-13s | %-13s | %-13s |\n","Games Lost","Goals For", "Goals Against", "Goal Diff", "Points");

        printf("| %-5s | %-16s | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d |\n",t.group,t.name,t.gPlayed,t.gWon,t.gDrawn,t.gLost,t.goalFor,t.goalAgainst,t.goalFor-t.goalAgainst,t.points);
    }
    else
    {
      printf("| %-5s | %-16s | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d | %-13d |\n","",t.name,t.gPlayed,t.gWon,t.gDrawn,t.gLost,t.goalFor,t.goalAgainst,t.goalFor-t.goalAgainst,t.points);
    }
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
        list[teamNum1].goalAgainst += score2;
        list[teamNum2].goalFor += score2;
        list[teamNum2].goalAgainst += score1;
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

void printBeginningText()
{
  printf("FIFA World Cup – Russia 2018\nProgram	Developed	by Solomon Scobie\nStudent Number c3302821\nComputer Lab Wednesday 9 am - 12 pm");
}
