#include "termirend.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN 60
#define CALC_MLSEC ((ulli) tv.tv_sec * 1000 + (ulli) tv.tv_usec / 1000)

typedef unsigned long long int ulli;
// --------------------------------------------------
//                     Variables
// --------------------------------------------------

static time_t last_time_reload;

struct timeval tv;
ulli last_time_mlsec;


// --------------------------------------------------
//                     Functions
// --------------------------------------------------

// A wait function with error checking
int wait_ec(int delay) {
  // Returns -1 if error
  // Returns  1 if NO error

  // Delay secure bottom limit
  if (delay < 2) { delay = 2; }

  // Initial time set
  last_time_reload = time(NULL);

  // Error check
  if (last_time_reload == -1) { return -1; }

  // Delay cycle
  while (time(NULL) - last_time_reload < delay) {
    if (time(NULL) - last_time_reload >= delay) {
      last_time_reload = time(NULL);
      break;
    }
  }

  system("cls");

  return 1;
}

// A wait function without error checking
void wait(int fps) {
  // Delay secure bottom limit
  // if (delay < 2) { delay = 2; }
  MIN / fps * 1000

  // Initial time set
  last_time_reload = time(NULL);
  gettimeofday(&tv, NULL);
  last_time_mlsec = CALC_MLSEC;

  // Delay cycle
  while (CALC_MLSEC - last_time_mlsec < delay) {
    if (CALC_MLSEC - last_time_reload >= delay) {
      last_time_mlsec = CALC_MLSEC;
      printf("\n%lu", last_time_mlsec);
      break;
    }
  }

  system("cls");
}