//============================================================================
// Name        : solver.cpp
// Author      : Jeremy French
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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


int main() {
	// TODO: Start Timer
 	// Allong the corridor and up the stairs

	// Temp measuer to get some data in.
	//char instring[82] = "12345678912345678912345 7891234567891234567 9123456789123456789 23456789123456789";
	//char instring[] =
	//		"   5  748 59  1  3 4 7 6  94 5 1 37    4 5    86 2 4 55  6 3 2 8  1  53 973  4   ";
	// CITYAM 13/09/2012 tricky
	char instring[82] = "   97 3   7     6     5  2 9  1     45       1 6  8    1   4 87  45    172     3 ";


	int out;
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
	#endif
	out = solve_board(instring);
    #ifdef __MACH__
	ret = clock_get_time(aClock, &bTime);
		         if (ret != KERN_SUCCESS) {
		         // NO timer
		         }

	cout << (bTime.tv_sec - aTime.tv_sec) << " Seconds " << (bTime.tv_nsec - aTime.tv_nsec) << " Nanoseconds ";
	cout << endl;
    #endif

	return 0;
}

