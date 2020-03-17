/**
  * SO, 2016
  * Lab #4
  *
  * Task #5, lin
  *
  * Avoid creating zombies using signals
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

#define TIMEOUT		20


/*
 * configure signal handler
 */
static void set_signals(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	/* TODO - ignore SIGCHLD */

	sa.sa_handler = SIG_IGN;
	sigaction(SIGCHLD, &sa, NULL);

}

int main(void)
{
	pid_t pid;

	/* TODO - create child process without waiting */
	if (fork() == 0){
		return 0;
	}
	/* TODO - sleep */
	sleep(100);
	return 1;
}
