/*my udp server*/

#include "main.h"
#include "lwip.h"
#include "sockets.h"
#include "cmsis_os.h"
#include <string.h>
#include "led.h"

#if defined(USE_UPD_SERVER)
#define PORTNUM 5678UL
#endif
#if (USE_UPD_SERVER_PRINTF == 1)
#include <stdio.h>
#define UPD_SERVER_PRINTF(...) do { printf("[upd_server.c: %s: %d]: ",__func__, __LINE__);printf(__VA_ARGS__); } while (0)
#else
#define UPD_SERVER_PRINTF(...)
#endif

static struct sockaddr_in serv_addr, client_addr;
static int socket_fd;
static uint16_t nport;

#define UPD_BUFF_SIZE 256

static int updServerInit(void)
{
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd == -1) {
		UPD_SERVER_PRINTF("socket() error\n");

		return -1;
	}

	nport = PORTNUM;
	nport = htons((uint16_t)nport);

	bzero(&serv_addr, sizeof(serv_addr));//!!

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = nport;

	if(bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1) {
		UPD_SERVER_PRINTF("bind() error\n");
		close(socket_fd);
		return -1;
	}


	UPD_SERVER_PRINTF("Server is ready\n");

	return 0;
}

void StartUpdServerTask(void const * argument)
{


	osDelay(5000);// wait 5 sec to init lwip stack

	if(updServerInit() < 0) {
		UPD_SERVER_PRINTF("updSocketServerInit() error\n");
		osThreadTerminate(NULL);
		return;
	}

 int fdsize=socket_fd + 1;
	for(;;)
	{

		fd_set rset;

	    FD_ZERO(&rset);
	    FD_SET(socket_fd, &rset);
	    select(fdsize, &rset, NULL, NULL, NULL);

		  bzero(&client_addr, sizeof(client_addr));


		  if (FD_ISSET(socket_fd, &rset)) {
		  	    	memset(&client_addr, 0, sizeof(client_addr));

		  			char buffer[256];
		  			memset(buffer, 0, 256);
		  			socklen_t socklen = sizeof(client_addr);

		  			recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &socklen);

		  			char answer[256] = { 0 };

		  			 comandreader(buffer,answer);

		  			sendto(socket_fd, answer, strlen(answer), 0, (struct sockaddr *)&client_addr, socklen);
		  	    }

		  }



}

