/**
  * SO, 2016
  * Lab #4
  *
  * Task #6, lin
  *
  * Timers usage
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <signal.h>
#include <sys/time.h>

#include "utils.h"

#define TIMEOUT		2

#include <unistd.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

struct sigaction sa;

/*
 * SIGALRM handler - called when the timer expires
 */

static void handler(int sig, siginfo_t *si, void *uc)
{
           printf("%d\n", sig);
           //print_siginfo(si);
           signal(sig, SIG_IGN);
}

static void timer_handler(int signo)
{
	time_t curr_time;

	/* TODO - print time */
	time_t rawtime;

  	time (&rawtime);
  	printf ("The current local time is: %s", ctime (&rawtime));
}

/*
 * set signal handlers
 */
static void set_signals(void)
{
	struct sigaction sa;
	int rc;

	memset(&sa, 0, sizeof(sa));

	/* TODO - set handler for SIGALRM */
	sa.sa_handler = SIGALRM;
	sigaction(SIGALRM, &sa, NULL);
}

/*
 * configure timer to generate SIGALRM when fired
 * the timer expires at every TIMEOUT seconds
 */
static void set_timer(void)
{
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	int rc;
	sigset_t mask;
	
	// Resource: http://manpages.ubuntu.com/manpages/cosmic/man2/timer_create.2.html
	
	/* TODO - Create the timer */
	
	   sa.sa_flags = SA_SIGINFO;
	   // Pentru 2 de la bonus 
	   sa.sa_sigaction = handler; 
	   //unde handler e o functie
           sigemptyset(&sa.sa_mask);
           sigaction(SIG, &sa, NULL);
           
	   sigemptyset(&mask);
           sigaddset(&mask, SIG);
           sigprocmask(SIG_SETMASK, &mask, NULL);

           /* Create the timer */

           sev.sigev_notify = SIGEV_SIGNAL;
           sev.sigev_signo = SIG;
           sev.sigev_value.sival_ptr = &timerid;
           timer_create(CLOCKID, &sev, &timerid);

           printf("timer ID is 0x%lx\n", (long) timerid);

	/* TODO - Start the timer */
	   long freq_nanosecs = 1000000000000000000000;
	   its.it_value.tv_sec = freq_nanosecs / 1000000000;
           its.it_value.tv_nsec = freq_nanosecs % 1000000000;
           its.it_interval.tv_sec = its.it_value.tv_sec;
           its.it_interval.tv_nsec = its.it_value.tv_nsec;

           timer_settime(timerid, 0, &its, NULL);
}

/*
 * use sigsuspend for waiting signals
 */
static void wait_for_signal(void)
{
	sigset_t old_mask;
	//int rc;

	/* TODO - wait for signal using sigsuspend */
	sigfillset(&old_mask);
	sigdelset(&old_mask, SIGALRM);
	sigdelset(&old_mask, SIGINT);
	sigsuspend(&old_mask);

}

int main(void)
{
	set_signals();	/* configure handler for  SIGALRM */
	set_timer();   /* create and start timer */

	while (1)
		wait_for_signal();

	return 0;
}
