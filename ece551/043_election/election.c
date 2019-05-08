#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Initialize_CharArr(char ** chararr, int length) {
  for (int i = 0; i < length; ++i) {
    (*chararr)[i] = '\0';
  }
}

state_t parseLine(const char * line) {
  //STEP 1: write me
  if (line == NULL) {
    fprintf(stderr, "the input format is a NULL pointer\n");  // check if the input is NULL
    exit(EXIT_FAILURE);
  }

  if (strchr(line, '\0') == NULL) {
    fprintf(
        stderr,
        "the input format is not right, without terminator \n");  //check the input if it terminates with '\0'
    exit(EXIT_FAILURE);
  }

  state_t states;  //create the state_t struct
  const char * start = line;
  char * end = NULL;
  if ((end = strchr(start, ':')) == NULL) {  //find the first colon in the string
    fprintf(stderr, "the input format is not right\n");
    exit(EXIT_FAILURE);
  }

  int length = end - start;  //get the length of the state name

  int i;
  char * StateArr = states.name;
  Initialize_CharArr(&StateArr, MAX_STATE_NAME_LENGTH);  //initialze states.name with all '\0'

  for (i = 0; i < length; ++i) {  //copy the statename from input to .name
    states.name[i] = start[i];
  }

  start = end + 1;  // advance the start pointer by one
  if ((end = strchr(start, ':')) == NULL) {
    fprintf(stderr, "the input format is not right\n");
    exit(EXIT_FAILURE);
  }

  length = end - start;
  char population[20] = {'\0'};
  for (i = 0; i < length; ++i) {
    population[i] = start[i];
  }

  uint64_t ppl = atoi(population);
  states.population = ppl;

  start = end + 1;  // advance the start pointer by one
  char vote[10] = {'\0'};
  strcpy(vote, start);
  states.electoralVotes = atoi(vote);

  return states;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int total_evote = 0;
  for (size_t i = 0; i < nStates; ++i) {
    double half_ppl =
        (double)(stateData[i].population) * 0.5;  //calculate half population of that state
    if (voteCounts[i] > half_ppl)
      total_evote += stateData[i].electoralVotes;
  }

  return total_evote;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; ++i) {
    double percentage =
        ((double)(voteCounts[i])) /
        stateData[i].population;  //calcuate the percentage of people vote candidate A
    if ((percentage >= 0.495 && percentage <= 0.505)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  int index = 0;  //The index number of the state that wins the most
  double largest_win = 0;
  for (size_t i = 0; i < nStates; ++i) {
    double percentage = ((double)(voteCounts[i])) / stateData[i].population;
    if (percentage >
        largest_win) {  // for every state, compute the percentage and compare with largest_win
      largest_win = percentage;
      index = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[index].name, largest_win * 100);
}
