#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <pthread.h> 
  
#define PORT     0xBAC0 
#define MAXLINE  1500 


int stn=0;

uint8_t bqr_whois[]={
		0x81,0x0a,0x00,0x0c,0x01,0x20,
		0xff,0xff,0x00,0xff,0x10,0x08

};


uint8_t brp_im[]={
		0x81,0x0b,0x00,0x19,0x01,0x20,0xff,0xff,0x00,0xff,0x10,0x00,0xc4,0x02,0x00,0x03,
		0xf1,0x22,0x04,0x00,0x91,0x03,0x22,0x01,0x04
};

uint8_t bqr_rp[]={
	0x81,0x0a,0x00,0x11,0x01,0x04,
	0x00,0x03,0x00,0x0c,0x0c,0x02,
	//0x3f,0xff,0xfe,0x19,0x2c
	//0x00,0x27,0x19,0x19,0x2c
	//0x00,0x03,0xee,0x19,0x2c
	0x00,0x03,0xeb,0x19,0x2c
	//0x00,0x03,0xe8,0x19,0x2c
	//0x00,0x03,0xf0,0x19,0x2c


};

#define DEVICE_IDL   req_read_object_list[14]
#define DEVICE_IDM   req_read_object_list[13]
#define DEVICE_IDH   req_read_object_list[12]



uint8_t req_read_object_list[]={

	0x81,0x0a,0x00,0x11,0x01,0x04,
	0x02,0x75,0x02,0x0c,0x0c,0x02,
	//0x00,0x00,0x0a,0x19,0x4c
	//0x00,0x00,0x08,0x19,0x4c
	0x00,0x00,0x17,0x19,0x4c
	//0x00,0x03,0xee,0x19,0x4c
	//0x00,0x03,0xeb,0x19,0x4c,0x29,0x00


};


uint8_t segment_ack[]={
	0x81,0x0a,0x00,0x0a,0x01,0x00,
	0x40,0x01,0x00,0x01


};

uint8_t is_ready_object_list =0;
uint32_t cnt_object_list =0;

uint8_t array_object_list[1024][4]={0};

uint8_t cmd_object_list[] ={
0x81,0x0a,0x00,0x13,0x01,0x04,0x02,
0x75,0x03,0x0e,0x0c,
0x02,0x81,0x00,0x00,
0x1e,0x09,0x08,0x1f

};

extern int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp);

int sockfd; 
char hname[128]={0};
uint8_t  buffer[MAXLINE]; 
char *hello = "Hello from server"; 
struct sockaddr_in servaddr, cliaddr; 
struct hostent *hent=NULL;


char *sip=NULL;






int8_t cmd_str[1024];




int32_t make_internet_address(int8_t * hostname,int32_t port,struct sockaddr_in *addrp)
{

	struct hostent *hp;

	bzero((void*)addrp,sizeof(struct sockaddr_in));


	hp = gethostbyname(hostname);

	if(hp == NULL)
		return -1;

	bcopy((void*)hp->h_addr,(void*)&addrp->sin_addr,hp->h_length);
	addrp->sin_port = htons(port);
	addrp->sin_family= AF_INET;

	return 0;


}


uint32_t vvcnt=0;
void on_timer(int signum)
{
	signal(SIGALRM,on_timer);
	make_internet_address(sip,PORT,&cliaddr);
	if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
	{
		perror("udp send failed\n");
		exit(EXIT_FAILURE);		
	}
	vvcnt++;


	if(vvcnt == 100)
	{
		vvcnt=0;

		sleep(100);
	}


	//printf("hello timer\n");

}

int set_timer(uint32_t nms)
{

	struct itimerval ts;

	ts.it_interval.tv_sec = nms/1000;
	ts.it_interval.tv_usec = (nms%1000)*1000L;


	ts.it_value.tv_sec = nms/1000;
	ts.it_value.tv_usec = (nms%1000)*1000L;


	return setitimer(ITIMER_REAL,&ts,NULL);
}

//=========================================================================================
//

uint8_t list_array[1024][4]={0};
uint32_t rv_cnt =0;


void *read_udp(void *arg_r)
{


	int n=0;
	int len=0; 
	uint32_t bid=0;
	uint32_t acnt=0;
	uint32_t bcnt=0;
	uint32_t ccnt=0;
	uint32_t vcnt=0;


	len = sizeof(cliaddr);  //len is value/resuslt 


	FILE *fp;
	fp = fopen("object-list.log","w");


	if(fp == NULL)
	{

		printf("failed open object-list.log");
		exit(EXIT_FAILURE);

	}




	while(1)
	{
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, &len); 
		//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, sizeof(struct sockaddr)); 

#if 0
		//		printf("==========rec len is %d\n",n);

		printf("rec data is \r\n");
		for(int i=0;i<n;i++)
		{

			printf("0x%02x ",buffer[i]);

			if((i + 1)%8 == 0)
				printf("\r\n");

		}

		printf("\r\n");

#endif


		//printf("==========rec len is %d\n",n);
		//printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));




		//printf("\n==rec len is %d\n",n);


		if(buffer[12]== 0xc4 && buffer[13] == 0x02)
		{
			bid=(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]);


			if(bid == 4194302)
			{
				acnt++;
				printf("I am %d\t%d\n",bid,acnt);
			}

			if(bid == 12)
			{
				bcnt++;
				printf("I am %d\t%d\n",bid,bcnt);
			}
			if(bid == 1000)
			{
				ccnt++;
				printf("I am %d\t%d\n",bid,ccnt);
			}


			printf("I am %d\n",bid);
			bid=0;

		}

		if(buffer[10]== 0x10 && buffer[11] == 0x08)
		{

			//printf("I am 5006\n");
		}

		if(strcmp(buffer,"whois\n") == 0)
		{

			//printf("I am: %d\n",1009);
			//printf("%s\r\n","world");
			//write(pfd[1],ts,strlen(ts));
		}


		if(buffer[16] == 0x3e  && buffer[27]==0x3f)
		{
			vcnt++;

			printf("%c%c%c%c%c%c%c\t%d\n",buffer[20],buffer[21],buffer[22],buffer[23],buffer[24],buffer[25],buffer[26],vcnt);
		}

		int moffset =0;
		//int foffset =18;
		int foffset =23;
		if(buffer[4]== 0x01  && buffer[5]==0x04)
		{

			printf("******rec object list\n");
			printf("result saved to object-list.log\n");
			while(foffset < n)
			{
				printf("Command is %x %x %x %x ",buffer[foffset],buffer[foffset+1],buffer[foffset+2],buffer[foffset+3]);

				array_object_list[cnt_object_list][0]= buffer[foffset + 0];
				array_object_list[cnt_object_list][1]= buffer[foffset + 1];
				array_object_list[cnt_object_list][2]= buffer[foffset + 2];
				array_object_list[cnt_object_list][3]= buffer[foffset + 3];


				foffset +=5;
				cnt_object_list ++;

				printf("No of cnt_object_list:  %d\n",cnt_object_list);

			}

		//	if(is_ready_object_list == 0)
			{
				if((stn = sendto(sockfd,segment_ack,sizeof(segment_ack),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
				{
					perror("udp send failed\n");
					exit(EXIT_FAILURE);		
				}
			}

			is_ready_object_list ++;












#if 0
			if((stn = sendto(sockfd,segment_ack,sizeof(segment_ack),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}
#endif


		}

		if(buffer[4]== 0x01  && buffer[5]==0x00)// receive results of object lists
		{


			rv_cnt++;
			printf("result is %02x %02x %02x %02x %02x  cnt is %d\n",buffer[6],buffer[10],buffer[11],buffer[12],buffer[13],rv_cnt);



			fprintf(fp,"result is %02x %02x %02x %02x %02x\n",buffer[6],buffer[10],buffer[11],buffer[12],buffer[13]);
			fflush(fp);



		}

		if(strcmp(buffer,"tx-quit\n") == 0)
		{
			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}





		memset(buffer,0,sizeof(buffer));
		//		sleep(1);
	}

}


uint8_t cmd_buf[128]={0};

void *write_udp(void *arg_w)
{

	int nrcmd=0;
	int fd;
	int m=0;
	make_internet_address(sip,PORT,&cliaddr);
	fd = open("udp-fifo",O_RDONLY | O_NONBLOCK);

	while(1)
	{



		//nrcmd = read(fd,cmd_buf,sizeof(cmd_buf));
		nrcmd = read(fd,cmd_buf,PIPE_BUF);

		//printf("====== nrcmd is %d\n",nrcmd);
		//printf("cmd_buf is %s\n",cmd_buf);
		//
		//
		if(nrcmd == 0)
		{
			//	sleep(1);
		}


		if(strcmp(cmd_buf,"send rv\n") == 0)
		{


			if((stn = sendto(sockfd,bqr_rp,sizeof(bqr_rp),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			//	printf("-------send rv\n");
			m++;
#if 0
			if(m>100)
				exit(0);
#endif
			//	sleep(3);

		}


		if(strcmp(cmd_buf,"send rol\n") == 0)
		{


			if((stn = sendto(sockfd,req_read_object_list,sizeof(req_read_object_list),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
			{
				perror("udp send failed\n");
				exit(EXIT_FAILURE);		
			}

			printf("-------send rol\n");


		}


		if(is_ready_object_list  )
		{

			uint32_t icnt=0;
			for(icnt=0;icnt <= cnt_object_list;icnt++)
			{



				cmd_object_list[11] = array_object_list[icnt][0];
				cmd_object_list[12] = array_object_list[icnt][1];
				cmd_object_list[13] = array_object_list[icnt][2];
				cmd_object_list[14] = array_object_list[icnt][3];




				if((stn = sendto(sockfd,cmd_object_list,sizeof(cmd_object_list),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
				{
					perror("udp send failed\n");
					exit(EXIT_FAILURE);		
				}
			//	printf("icnt is %d\n",icnt);
				sleep(1);
				//usleep(50000);

			}

			is_ready_object_list = 0;

		}


		memset(cmd_buf,0,sizeof(cmd_buf));
		//sleep(1);

	}

}


//=========================================================================================

int main(int argc, char* argv[])
{    


	if(argc <3)
	{

		printf("err:parameters\n");
		exit(EXIT_FAILURE);
	}

	sip = argv[2];
	uint32_t temp_id = atoi(argv[3]);
	DEVICE_IDL= temp_id & 0x000000ff;
	DEVICE_IDM= (temp_id & 0x0000ff00)>>8;
	DEVICE_IDH= (temp_id & 0x00ff0000)>>16;

	gethostname(hname,sizeof(hname));
	hent = gethostbyname(hname);

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 


	int optval =1;
	//setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST|SO_REUSEADDR,&optval,sizeof(int));

	struct timeval timeout;
	timeout.tv_sec = 6;
	timeout.tv_usec = 0;
	//setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 


	const char localip[]="192.168.2.10";

	// Filling server information 
	servaddr.sin_family    = AF_INET; // IPv4 
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	//servaddr.sin_addr.s_addr = inet_addr(localip); 
	servaddr.sin_port = htons(PORT); 
	//servaddr.sin_port = PORT; 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 


#if 0
	set_timer(atoi(argv[1]));
	signal(SIGALRM,on_timer);
#endif

	memset(buffer,0,sizeof(buffer));

	pthread_t thread_id_read;
	pthread_t thread_id_write;
	pthread_create(&thread_id_read,NULL,read_udp,NULL);
	pthread_create(&thread_id_write,NULL,write_udp,NULL);



	pthread_join(thread_id_read,NULL);
	pthread_join(thread_id_write,NULL);


	printf("after thread\r\n");


	exit(0);


	//==================================================================================================================
#if 0
	int fpid;
	int n=0;
	fpid = fork();
	if(fpid == -1)
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if(fpid == 0)
	{

		//execl("./myudp-tx.exe","myudp-tx.exe",(char*)0);
#if 1
		struct timespec tp;
		tp.tv_sec =0;
		tp.tv_nsec =500000;
		int cnt=0;	
		make_internet_address(sip,PORT,&cliaddr);
		//make_internet_address("192.168.2.22",PORT,&cliaddr);
		//

#if 0
		if((stn = sendto(sockfd,req_read_object_list,sizeof(req_read_object_list),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))) == -1)
		{
			perror("udp send failed\n");
			exit(EXIT_FAILURE);		
		}

		sleep(300);
#endif

		sleep(3);

		printf("start sending\n");
		set_timer(atoi(argv[1]));
		signal(SIGALRM,on_timer);
		while(1);
#endif

	}


#endif
	//============================================================================================================================================








	//===========================================================================================================================================
#if 0
	char *ts="hello";
	int xmcnt=0;
	int rcnt=0;
	uint32_t bid=0;
	uint32_t acnt=0;
	uint32_t bcnt=0;
	uint32_t ccnt=0;
	uint32_t vcnt=0;
	while(1)
	{
#if 1
		rcnt = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, &len); 
		//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  0, ( struct sockaddr *) &cliaddr, sizeof(struct sockaddr)); 

		printf("\n==ip %s\n",(char*)inet_ntoa(cliaddr.sin_addr));
		printf("\n==rec len is %d\n",rcnt);


		if(buffer[12]== 0xc4 && buffer[13] == 0x02)
		{
			bid=(uint32_t)(buffer[14]<<16|buffer[15]<<8|buffer[16]);


			if(bid == 4194302)
			{
				acnt++;
				printf("I am %d\t%d\n",bid,acnt);
			}

			if(bid == 12)
			{
				bcnt++;
				printf("I am %d\t%d\n",bid,bcnt);
			}
			if(bid == 1000)
			{
				ccnt++;
				printf("I am %d\t%d\n",bid,ccnt);
			}


			printf("I am %d\n",bid);
			bid=0;

		}
#endif

		if(buffer[10]== 0x10 && buffer[11] == 0x08)
		{

			//printf("I am 5006\n");
		}

		if(strcmp(buffer,"whois\n") == 0)
		{

			//printf("I am: %d\n",1009);
			//printf("%s\r\n","world");
			//write(pfd[1],ts,strlen(ts));
		}


		if(buffer[16] == 0x3e  && buffer[27]==0x3f)
		{
			vcnt++;

			printf("%c%c%c%c%c%c%c\t%d\n",buffer[20],buffer[21],buffer[22],buffer[23],buffer[24],buffer[25],buffer[26],vcnt);
		}


		if(strcmp(buffer,"tx-quit\n") == 0)
		{
			printf("good-bye\n");
			exit(EXIT_SUCCESS);		

		}





		memset(buffer,0,sizeof(buffer));
		//	sleep(1);
	}

#endif
//======================================================================================================================================










}
