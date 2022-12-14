#include "header.h"

static struct termios init_setting, new_setting;
char seg_num[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
char seg_dnum [10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x58, 0x00, 0x10};
t_info info;

void init_keyboard() {
	tcgetattr(STDIN_FILENO, &init_setting);
	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VMIN] = 0;
	new_setting.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_setting) ;
}

void close_keyboard() {
	tcsetattr(0, TCSANOW, &init_setting) ;
}

char get_key() {
	char ch = -1;
	if(read(STDIN_FILENO, &ch, 1) != 1)
		ch = -1;
	return ch;
}

void print_menu() {
	printf("\n---------menu---------\n");
	printf("[q] : program exit\n");
	printf("------------------------\n\n");
}

void exit_program(int code) {

	close_keyboard();

	kill(info.pid[0], SIGINT);
	kill(info.pid[1], SIGINT);

	//pthread_cancel(info.tid[0]);
	pthread_cancel(info.tid[1]);

	munmap(info.shmem, 4);
	close(info.shmem_fd);

	//write(info.seg, 0x0000, 2);
	//close(info.seg)
	//close(info.but)

	exit(code);
}

int init_system() {
	info.shmem_fd = open("shared_memory", O_RDWR|O_CREAT);
	if (info.shmem_fd == -1) {
		printf("failed to open shared memory file\n");
		exit_program(-1);
	}
	ftruncate(info.shmem_fd, 4);
	info.shmem = mmap(0, 4, PROT_READ|PROT_WRITE, MAP_SHARED, info.shmem_fd, 0);
	//info.seg = open("/dev/my_segment", O_RDWR); // if you want read-'O_RDONLY' write= 'O_WRONLY', read&write= 'O_RDWR'
	info.but = open("/dev/my_button", O_RDWR); // if you want read-'O_RDONLY' write= 'O_WRONLY', read&write= 'O_RDWR'

	/*if (info.seg == -1) {
		printf("segment opening was not possible! \n");
		return -1;
	}*/
	if (info.but == -1) {
		printf("button opening was not possible! \n");
		exit_program(-1);
	}
	printf("device opening was successfull! \n");

	info.stat_power = 0;
	info.stat_autopilot = 0;
	info.throttle = 0;
	info.quit = 0;
}

void *print_throttle() {
	unsigned short il, sip, baek, chun;

	while(1) {
		il = (seg_num[info.throttle % 10] << 4) | D4;
		write(info.seg, &il, 2);
		usleep(15);
		write(info.seg, NULL, 2);
		sip = (seg_num[(info.throttle % 100) / 10] << 4) | D3;
		write(info.seg, &sip, 2);
		usleep(15);
		write(info.seg, NULL, 2);
		baek = (seg_num[(info.throttle % 1000) / 100] << 4) | D2;
		write(info.seg, &baek, 2);
		usleep(15);
		write(info.seg, NULL, 2);
		chun = (seg_num[(info.throttle % 10000) / 1000] << 4) | D1;
		write(info.seg, &chun, 2);
		usleep(15);
		write(info.seg, NULL, 2);	
	}
}

void *key_button() {
	char	key;
	char	tmp;

	init_keyboard();

	while(1) {
		//printf("key\n");
		key = get_key();
		if(key == 'q'){
			printf("exiting program. \n");
			info.quit = 1;
			break;
		}

		read(info.but, &tmp, 1);
    	if(info.stat_power == 0 && tmp == 2) {
			printf("pressed button 1\npower on\n");
			info.stat_power = 1;
		}
		else if(info.stat_power == 1 && tmp == 2) {
			printf("pressed button 1\npower off\n");
			info.stat_power = 0;
		}
		else if(info.stat_autopilot == 0 && tmp == 1) {
			printf("pressed button 2\nautopilot on\n");
			info.stat_autopilot = 1;
		}
		else if(info.stat_autopilot == 1 && tmp == 1) {
			printf("pressed button 2\nautopilot off\n");
			info.stat_autopilot = 0;
		}

		usleep(1);
	}
}

int proc_diverge() {

	info.pid[0] = fork();
	if(info.pid[0] == 0) {
		printf("child\n");
		printf("running python %d\n", execl("/usr/bin/python3", "python3", "joystick.py", NULL));
	}
	/*info.pid[1] = fork();
	if(info.pid[1] == 0) {
		execl("TSRdetect.py", NULL);
	}
	if(info.pid[0] == -1 || info.pid[1] == -1)
		exit_program(-1);*/
	return 0;
}

int main(int arg, char **argv)
{
	unsigned short data[4];

	proc_diverge();
	init_system();

	data[0] = (seg_num[1] << 4) | D1;
	data[1] = (seg_num[2] << 4) | D2;
	data[2] = (seg_num[3] << 4) | D3;
	data[3] = (seg_num[4] << 4) | D4;	

	//pthread_create(&info.tid[0], NULL, print_throttle, NULL);
	pthread_create(&info.tid[1], NULL, key_button, NULL);

	print_menu();
	while(1) {
		
		info.throttle = info.shmem[0];

		//printf("info.throttle inpuut by joystick %d\n", info.shmem[0]);
		if(info.quit)
			break;
		usleep(100);
	}

	exit_program(0);
	return 0;
}