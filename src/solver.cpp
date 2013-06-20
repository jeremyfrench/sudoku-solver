//============================================================================
// Name        : solver.cpp
// Author      : Jeremy French
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// Allong the corridor and up the stairs

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "solver_libs.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
using namespace std;

timespec diff(timespec start, timespec end);

int main() {
   string instring;
   int out;
   int counter = 0;
   int solved_counter = 0;
   #ifdef __MACH__
	  kern_return_t ret;
	  clock_serv_t aClock;
	  mach_timespec_t aTime,bTime;

	 ret = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK,
	&aClock);
	         if (ret != KERN_SUCCESS) {
	                 fprintf(stderr, "host_get_clock_service() failed: %s\n",
	mach_error_string(ret));
	                 abort();
	         }
	         ret = clock_get_time(aClock, &aTime);
	         if (ret != KERN_SUCCESS) {
	         // NO timer
	         }
    #elif defined(__linux__)
	  timespec time1, time2;
	  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	#endif
	setup_solver();
	while (getline(cin,instring)) {
      const char * inchars;
      inchars= instring.c_str();
      counter++;
      //TODO: standard format for out strings
	  out = solve_board(inchars);
	  if (out) {
		  solved_counter++;
	  }
	}
	cout << "Solved " << solved_counter << " of " << counter <<" boards" << endl;
	#ifdef __MACH__
	ret = clock_get_time(aClock, &bTime);
		         if (ret != KERN_SUCCESS) {
		         // NO timer
		         }
// TODO: pad or format number
    cout << (bTime.tv_sec - aTime.tv_sec) << " Seconds ";
	if(bTime.tv_sec - aTime.tv_sec >= 1) {
		cout << (1000000000 + bTime.tv_nsec - aTime.tv_nsec) << " Nanoseconds ";
	}
	else {
		cout << (bTime.tv_nsec - aTime.tv_nsec) << " Nanoseconds ";
	}

	cout << endl;
    #elif defined(__linux__)
	  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
          cout << "in  " <<diff(time1,time2).tv_sec<<":"<<diff(time1,time2).tv_nsec<< " seconds" << endl;
    #endif
	return 0;
}

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
