#include<stdio.h>
#include<iostream>

//�ļ�����ͷ�ļ�
#include<sys/types.h>
#include<sys/stat.h>

//����ͨ����Ҫ��ͷ�ļ��Ϳ��ļ�
#include<WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
//�궨���ӡ������Ϣ
//���������ǣ�[��������-�к�]�ַ������ݣ���ʾ��ǰ�������Ƶ�Ԥ����꣬��ʾ��ǰ���������кŵ�Ԥ�����
//"%"��ʽ���ַ�����"#str"ƴ��
#define PRINTF(str) printf("[%s-%d]"#str"=%s\n",__func__,__LINE__,str);
//��������
void error_die(const char* str) {
	perror(str);
	exit(1);
}

/*�����������ʼ�����������̣�
	1������ͨ�ų�ʼ��
	2�������׽���
	3�������׽������ԣ��˿ڿɸ���
	4�����׽��ֺ������ַ
	5����̬����˿ں�
	6��������������*/
int startup(unsigned short *port/*�û�ѡ��˿ڲ���*/) {
	WSADATA data;
//1,2
	int ret=WSAStartup(
		MAKEWORD(1,1),//Э��汾
		&data);
	if (ret) {
		error_die("WSAStartup");
	}
	int server_socket = socket(PF_INET,//�׽�������
		//1.�����׽�������������������ͨ��
		//2.�ļ��׽�������ͬһ������ͬ����ͨ��
		SOCK_STREAM,//������
		IPPROTO_TCP);//TCPЭ��
	if (server_socket == -1) {
		//�׽��ִ���ʧ�ܣ��������
		error_die("socket");
	}
//3
	int opt = 1;
	ret=setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,
		(const char FAR*) & opt, sizeof(opt));
	//�׽��������������𣬶˿��Ƿ��ã�����������������С
	if (ret == -1) {
		error_die("setsockopt");
	}
//���÷������˵������ַ
	struct sockaddr_in server_addr;//����ip��ַ��˿ں�
	memset(&server_addr, 0, sizeof(server_addr));//���ڴ���ָ����������ָ����
	server_addr.sin_family = AF_INET;//ʹ��UDP/TCP
	server_addr.sin_port = htons(*port);//�������ֽ�˳��ת��Ϊ�����ֽ�˳�򣨴�С��ͳһ��
	server_addr.sin_addr.s_addr = INADDR_ANY;//ip��ַ

//4
	ret = bind(server_socket, 
		(const struct sockaddr FAR *)&server_addr,sizeof(server_addr));
	if (ret < 0) {
		error_die("bind");
	}
//5
	int nameLen = sizeof(server_addr);
	if (*port == 0)/*��δָ���˿�*/ {
		if (getsockname(server_socket,
			(struct sockaddr FAR*) & server_addr,
			&nameLen) < 0)/*�˿ںŷ������server_addr*/ {
			error_die("getsockname");
		}
		*port = server_addr.sin_port;
	}
//6
	if (listen(server_socket, 5/*���г�5~20*/)/*listen �������ڽ��׽�������Ϊ����ģʽ��
		�Ա���ܴ���������������ĵڶ������� backlog ָ����δ������Ӷ��е���󳤶ȡ�
		������а�������Щ�Ѿ����ﵫ��δ�� accept ������������������*/ < 0) {
		error_die("listen");
	}
	return server_socket;
}

//�����û�������߳�
/*�����������վ���̣�
	1������get�����������ҳ��������
	2������������Ӧ�������ͱ�������ҳ
	3������������յ�����ҳ�����ٴη���get�����������ҳ�е�ͼƬ��JS��CSS���ļ�
	4������������Ӧ�������ͱ�������Դ
	5���û�����ҳ����д���ݣ�����ύ������POST����
	6����������POST���󽻸�CGI����
	7��CGI���ʹ������
	8�������������������POST�������Ӧ��*/
//��/����վ��������ԴĿ¼�µ�index.html

//��ָ���ͻ����׽���sock����ȡһ�����ݣ����浽buff�У�����ʵ�ʶ�ȡ���ļ�����
int get_line(int sock, char* buff, int size) {
//����\r\n(ATP)/&#x0a���н���
	char c= 0;//�洢��ȡ���ַ�
	int i = 0;//���ٻ�����λ��
	while (i < size - 1&& c != '\n'/*Խ������Ϸ����*/) {
		int n = recv(sock, &c, 1, 0);//��ȡһ���ַ�
		if (n > 0) {
			if (c == '\r') {
				n=recv(sock, &c, 1, MSG_PEEK);//peek��һ���ַ�
				if (n > 0 && c == '\n') {
					recv(sock, &c, 1, 0);
				}
				else {
					c = '\n';
				}
			}
			buff[i++] = c;
		}//��ȡ�ɹ�
		else {
			c = '\n';
		}//��ȡʧ��
	}
	buff[i] = 0;//������ĩβ������ֹ��'\0'
	return i;
}

void unimplement(int client) {
	PRINTF("POST");
}

void not_found(int client) {
	//����404��Ӧ
	char buff[1024];
	strcpy(buff, "HTTP/1.0 404 FOUND\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Server: ALICIAHttpd/0.1\r\n");//����������
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Content-type:text/html\n");//�����ı�����
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "\r\n");
	send(client, buff, strlen(buff), 0);
	//����404��ҳ����

	sprintf(buff,
		"<HTML>                                   \
		<TITLE>Not Found</TITLE>                  \
		<BODY>                                    \
		<H2>The resource is unavailable.</H2>     \
		<img src=\"404.jpg\" />                   \
		</BODY>                                   \
		</HTML>");
	send(client, buff, sizeof(buff), 0);
}

const char* getheadtype(const char* filename) {
	const char* ret = "text/html";
	const char* p = strrchr(filename, '.');
	if (!p)return ret;

	p++;
	if (!strcmp(p, "css"))ret = "text/css";
	else if (!strcmp(p, "jpg"))ret = "image/jpeg";
	else if (!strcmp(p, "png"))ret = "image/png";
	else if (!strcmp(p, "js"))ret = "application/x-javascript";
	return ret;
}

void headers(int client,const char*type) {
	char buff[1024];
	strcpy(buff, "HTTP/1.0 200 OK\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Server: ALICIAHttpd/0.1\r\n");//����������
	send(client, buff, strlen(buff), 0);

	char buf[1024];
	sprintf(buf, "Content-type:%s\r\n",type);//�����ı�����
	send(client, buf, strlen(buf), 0);

	strcpy(buff, "\r\n");
	send(client, buff, strlen(buff), 0);
}

void cat(int client, FILE*resource) {
	char buff[4096];
	int count = 0;
	while (1) {
		int ret = fread(buff, sizeof(char), sizeof(buff), resource);//����
		if (ret <= 0) {
			break;
		}
		send(client, buff, ret, 0);
		count += ret;
	}
	std::cout << "������" << count << "�ֽڸ������" << std::endl;
	
}

void server_file(int client, const char* filename) {
	int numchars = 1;
	char buff[1024];
	//���������ݰ�ʣ�����ݶ�ȡ���
	while (numchars > 0 && _stricmp(buff, "\n")) {
		numchars = get_line(client, buff, sizeof(buff));
		PRINTF(buff);
	}
	FILE* resource = NULL;
	if (strcmp(filename, "htdocs/index.html") == 0) {
		resource = fopen(filename, "r");
	}
	else {
		resource = fopen(filename, "rb");
	}
	//�������ļ�����
	if (resource == NULL) {
		not_found(client);
	}
	else {
		//��ʽ������Դ��������
		
		headers(client,getheadtype(filename));

		//�����������Դ��Ϣ
		cat(client,resource);

		std::cout << "��Դ���ͳɹ�" << std::endl;
	}
	fclose(resource);
}

DWORD WINAPI accept_request(LPVOID arg) {
	char buff[1024];
	int client = (SOCKET)arg;//�ͻ��׽���
	//��ȡһ������
	int numchars = get_line(client,buff,sizeof(buff));
	PRINTF(buff);//[accept_request-53]buff="EGT..."
	//0x015ffad8 "GET / HTTP/1.1\n"
	//��ⷽ��
	char method[255];
	int j = 0,i=0;
	while (!isspace(buff[j])&&i<sizeof(method)-1) {
		method[i++] = buff[j++];
	}
	method[i] = 0;//��ֹ
	PRINTF(method);
	//������󷽷��������Ƿ�֧��
	if (_stricmp(method, "GET") && _stricmp(method, "POST")) {
		unimplement(client);
		return 0;
	}

	//������Դ�ļ�·��
	char url[255];//���
	i = 0;
	while (isspace(buff[j]) && j< sizeof(buff)) j++;//�������ַ�

	while (!isspace(buff[j]) && i < sizeof(url) - 1) {
		url[i++] = buff[j++];
	}
	url[i] = 0;
	PRINTF(url);

	char path[512] = "";
	sprintf_s(path, "htdocs%s", url);//����ʽ��������д��һ���ַ�������
	if (path[strlen(path) - 1] == '/') {
		strcat_s(path, "index.html");//ƴ��
	}
	PRINTF(path);

	//�ж�·�����ļ�����Ŀ¼
	struct stat status;
	if (stat(path, &status) == -1) {
		while (numchars > 0 && _stricmp(buff, "\n")) {
			numchars = get_line(client, buff, sizeof(buff));
		}
		not_found(client);
	}
	else {
		if ((status.st_mode & S_IFMT) == S_IFDIR) {
			strcat_s(path, "/index.html");
		}
		server_file(client, path);
	}

	closesocket(client);//�ر�ʹ������׽���

	return 0;
}

int main(void) {
	unsigned short port = 80;
	int server_sock= startup(&port);
	std::cout << "httpd�����Ѿ����������ڼ���" << port << "�˿�";

	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	while (1) {
		int client_sock = accept(server_sock,
			(struct sockaddr FAR*) & client_addr,
			&client_addr_len);//�ȴ������ʣ�����ʽ�ȴ������ҷ���һ���µ��׽���
		if (client_sock == -1) {
			error_die("accpet");
		}
		//ʹ��client_sock���û����з���
		//Ϊ�����ڷ����ڼ�����ȴ��¸��û��������߳̽��
		//ע�⸴ϰ�����̡����̡߳�����

		DWORD threadId = 0;
		CreateThread(0, 0, accept_request/*ָ���̺߳�����ָ�롣�߳�����ʱ��ִ�иú�����*/,
			(void*)client_sock/*���ݸ��̺߳����Ĳ���*/, 0, &threadId);
	}
	closesocket(server_sock);
	return 0;
}