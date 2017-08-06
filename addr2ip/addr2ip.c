#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>

/*
作用：将网络地址转化为IP
参数：ipbuf是输出缓冲区, host是要转化的域名, maxlen是缓冲区大小
返回值：返回-1是失败，0是成功
*/
int get_ip_from_host(char *ipbuf, const char *host, int maxlen)
{
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	if (inet_aton(host, &sa.sin_addr) == 0) 
	{
		struct hostent *he;
		he = gethostbyname(host);
		if (he == NULL)
			return -1;
		memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
	}
	strncpy(ipbuf, inet_ntoa(sa.sin_addr), maxlen);
	return 0;
}

//测试例子
int main()
{
	char ipbuf[128];
	get_ip_from_host(ipbuf, "www.baidu.com", 128);
	printf("ip: %s\n", ipbuf);
	return 0;
}