#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

// #include<ctime>
#include <iostream>
#include <chrono>

using namespace std;
int main(int argc, char *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	int i, byte;
	char send_buf[50], ch_recv[1024];

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) // 创建socket，指定通信协议为AF_UNIX,数据方式SOCK_STREAM
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// 配置server_address
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "/home/yakai/SLAM/orbslam_addsemantic-main/yolov5_RemoveDynamic/detect_speedup_send");
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);

	if (result == -1)
	{
		printf("ensure the server is up\n");
		perror("connect");
		exit(EXIT_FAILURE);
	}

	int k = 1;

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	while (1)
	{
		std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
		sleep(1);				 // 一秒一次
		sprintf(send_buf, "ok"); // 用sprintf事先把消息写到send_buf
		if ((byte = write(sockfd, send_buf, sizeof(send_buf))) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		if ((byte = read(sockfd, &ch_recv, 1000)) == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		// printf("In C++: %s",ch_recv);
		// cout << ch_recv
		cout << "********new*********" << endl;
		string ch_recv_string = ch_recv;
		cout << ch_recv_string << endl;

		memset(send_buf, 0, sizeof(send_buf)); // clear char[]
		memset(ch_recv, 0, sizeof(ch_recv));   // clear char[]
		k = k + 1;

		std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		double ttrack = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
		cout << "per img time is " << ttrack << endl;
	}
	std::chrono::steady_clock::time_point finish = std::chrono::steady_clock::now();
	double ttrack = std::chrono::duration_cast<std::chrono::duration<double>>(start - finish).count();
	cout << "total img time is " << ttrack << endl;
	close(sockfd);

	return 0;
}
