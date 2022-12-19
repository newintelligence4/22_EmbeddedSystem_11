#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h>

static struct termios init_setting, new_setting;
char seg_num[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
char seg_dnum [10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x58, 0x00, 0x10};

#define D1 0x01
#define D2 0x02
#define D3 0x04
#define D4 0x08

void init_keyboard()
{
	tcgetattr(STDIN_FILENO, &init_setting);
	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VMIN] = 0;
	new_setting.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_setting) ;
}
void close_keyboard()
{
	tcsetattr(0, TCSANOW, &init_setting) ;
}

char get_key()
{
	char ch = -1;
	if(read(STDIN_FILENO, &ch, 1) != 1)
		ch = -1;
	return ch;
}

void print_menu()
{
	printf("\n---------menu---------\n");
	printf("[u] : count up\n");
	printf("[d] : count down\n");
	printf("[p] : count setting\n");
	printf("[q] : program exit\n");
	printf("------------------------\n\n");
}

int main(int arg, char **argv)
{
	unsigned short data[4];
	char key;
	int number;
	int delay_time;
	char status;
	char tmp;
	char buff;

	int seg = open("/dev/my_segment", O_RDWR); // if you want read-'O_RDONLY' write= 'O_WRONLY', read&write= 'O_RDWR'
	int but = open("/dev/my_button", O_RDWR); // if you want read-'O_RDONLY' write= 'O_WRONLY', read&write= 'O_RDWR'
	
	if (seg == -1) {
		printf("segment opening was not possible! n");
		return -1;
	}
	if (but == -1) {
		printf("button opening was not possible! n");
		return -1;
	}
	printf("device opening was successfull! \n");
	
	init_keyboard();
	print_menu();
	number = 0;
	status = 3;

	data[0] = (seg_num[1] << 4) | D1;
	data[1] = (seg_num[2] << 4) | D2;
	data[2] = (seg_num[3] << 4) | D3;
	data[3] = (seg_num[4] << 4) | D4;
	
	unsigned short tmpn, il, sip, baek, chun;

	while(1){
		
		il = (seg_num[number % 10] << 4) | D4;
		write(seg, &il, 2);
		usleep(15);
		write(seg, NULL, 2);
		sip = (seg_num[(number % 100) / 10] << 4) | D3;
		write(seg, &sip, 2);
		usleep(15);
		write(seg, NULL, 2);
		baek = (seg_num[(number % 1000) / 100] << 4) | D2;
		write(seg, &baek, 2);
		usleep(15);
		write(seg, NULL, 2);
		chun = (seg_num[(number % 10000) / 1000] << 4) | D1;
		write(seg, &chun, 2);
		usleep(15);
		write(seg, NULL, 2);

		key = get_key();
		if(key == 'q'){
			printf("exiting program. \n");
			break;
		}
		else if(key == 'p'){
			printf("pressed P\n");
			number = 0;
		}
		else if(key == 'u'){
			printf("pressed U\n");
			number++;
			if(number >= 10000)
				number = 0;
		}
		else if(key == 'd'){
			printf("pressed D\n");
			number--;
			if(number < 0)
				number = 9999;
		}

		read(but, &tmp, 1);
        if(status == 3 && tmp == 2) {
			printf("pressed button 1\n");
			status = 2;
			number++;
			if(number >= 10000)
				number = 0;
		}
		else if(status == 3 && tmp == 1) {
			printf("pressed button 2\n");
			status = 1;
			number--;
			if(number < 0)
				number = 9999;
		}
		else if((status == 2 || status == 1)&& tmp == 3)
			status = 3;

        //write(but, &tmp, 1);
	}
	close_keyboard();
	write(seg, 0x0000, 2);
	close(seg);
	return 0;
}