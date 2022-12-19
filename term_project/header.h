#ifndef HEADER_H
# define HEADER_H

# include <stdio.h> 
# include <stdlib.h> 
# include <string.h> 
# include <unistd.h> 
# include <fcntl.h> 
# include <termios.h>
# include <pthread.h>
# include <signal.h>	
# include <sys/mman.h>

# define D1 0x01
# define D2 0x02
# define D3 0x04
# define D4 0x08

#define THR 0

typedef struct s_info {
	
	pthread_t	tid[2];
	pid_t		pid[3];

	int		shmem_fd;
	int		seg;
	int		but;
	char 	*shmem;

	int		throttle;
	int		stat_power;
	int		stat_autopilot;
	int		quit;
}	t_info;

/*
//key_button.c
void init_keyboard();
void close_keyboard();
char get_key();
void *key_button();

//segment.c
void *print_throttle()
*/




#endif