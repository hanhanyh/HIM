#include"HIMServer.h"
#include<iostream>
#include<stdlib.h>
#include<list>
#include<boost\function.hpp>
#include"cJSON.h"
using namespace std;
using namespace boost::asio;
HIM::HIMServer::HIMServer(int port)
{
	this->socketlist = new list<boost::shared_ptr<ip::tcp::socket>>();
	this->mport = new int;
	*(this->mport) = port;
}
HIM::HIMServer::~HIMServer()
{
	delete this->socketlist;
	delete this->mport;
}
void HIM::HIMServer::RemoveListItem(boost::shared_ptr<ip::tcp::socket> ptr)
{
	 
	 boost::mutex::scoped_lock lock(socklistmutex);
	 for (list<boost::shared_ptr<ip::tcp::socket>>::iterator it = socketlist->begin(); it != socketlist->end(); it++)
	 {
		 if (*it == ptr)
		 {
		     socketlist->erase(it);
			 return;
		 }
	}
}
void HIM::HIMServer::doing(boost::shared_ptr<ip::tcp::socket> sock)
{
	{
		boost::mutex::scoped_lock lock(socklistmutex);
		socketlist->push_back(sock);
	}

//	sock->write_some(buffer("hello!"));
	
		try{
			//sock->read_some(buffer(data));
			//cout << data << endl;
		     	this->startResolvingLoop(sock);
			//	cout << "�߳��˳�" << endl;
			//broadCast(data);
			//sock->write_some(buffer(data));
	    }
		catch (boost::system::system_error error)
		{
			cout << "�쳣���룺" << error.code() << endl;
			RemoveListItem(sock);
			return;
		}
 
	
}
 
void HIM::HIMServer::start()
{
	io_service service;
	ip::tcp::endpoint ep(ip::tcp::v4(), *(this->mport));
	ip::tcp::acceptor acc(service, ep);
	while (true)
	{
		boost::shared_ptr<ip::tcp::socket> sock(new ip::tcp::socket(service));
		acc.accept(*sock);
		//boost bind ���÷Ǿ�̬��Ա���� ��Ҫ�ڵڶ�����������this(�����ʵ��)
	 	boost::function<void (boost::shared_ptr<ip::tcp::socket>)> f = boost::bind(&HIMServer::doing,this,boost::placeholders::_1);
		boost::thread t(f,sock);
	}
}

void HIM::HIMServer::startResolvingLoop(boost::shared_ptr<ip::tcp::socket> sock)
{
	char * msgType = 0;//����������ָ��
	//��ǰ��¼���û���
	char * currentUserName = new char[1024];//����ʹ������ָ��
	memset(currentUserName, '\0', 1024);
	while (true)
	{
		//ͷ���ֽ�����(��һ��\0��λ��)
		char chead[5];
		//��Ϣ����
		msgType = new char[50];
		memset(msgType, '\0', 50);

		memset(chead, '\0', 5);
		//�Ѷ�ͷ��λ��
		int  readhead = 0;
		//��Ϣ�����С
		int bodysize = 0;
		//��Ϣ����
		char cbody[2049];
		memset(cbody, '\0', 2049);
		//�Ѷ���Ϣ����
		int readbody = 0;

		//��ͷ��(���ֽ�)
		while (readhead <= 3)
		{
			readhead += sock->read_some(buffer(chead + readhead, 1));
		}
		chead[4] = '\0';
		bodysize = atoi(chead);

		if (bodysize > 2048)
		{
			//��Ϣ����̫��
		}
		//����Ϣ����

		std::cout << "�������ڽ���" << endl;
		//������
		while (readbody <= (bodysize - 1))
		{
			readbody += sock->read_some(buffer(cbody + readbody, 1));
		}
		//��cbody����JsonStringParser ���д���
		std::cout << cbody << endl;
		std::cout << "---���ݳɹ�����-" << endl;
		//������Ϣ����
		if (this->msgType(cbody, &msgType) == false)
		{
			std::cout << "������Ϣ����ʧ�ܣ�" << endl;
			sock->close();//���ﻹ��Ҫɾ���б�
			this->RemoveListItem(sock);
			break;
		}
		std::cout << "��Ϣ����:" << msgType << endl;
		//��Ϣ����
	 	if (strcmp("login", msgType) == 0) //��¼����
		{

		}
		else if (strcmp("p2pmsg", msgType) == 0)//������Ϣ������
		{
			
		}
		else if (strcmp("p2pfriendrequest", msgType) == 0)//��������
		{
		
		}
		else if (strcmp("p2pfriendresponse", msgType) == 0)//��������Ӧ��
		{
		
		}
		else if (strcmp("groupmsg", msgType) == 0)//Ⱥ��Ϣ
		{

		}
		else if (strcmp("groupaddrequest", msgType) == 0)//Ⱥ����
		{
		
		}
		else if (strcmp("groupaddresponse", msgType) == 0)//����
		{

		}
		////��λ
		//memset(chead, '\0', 5);
		//readhead = 0;
		//memset(cbody, '\0', 2049);
		//break;
	}
	delete[] msgType;
	delete[] currentUserName;
}
bool HIM::HIMServer::msgType(char * jsonstr, char ** msgtype)
{
	cJSON * root = 0, *typenode;
	int typesize = 0;
	root = cJSON_Parse(jsonstr);
	if (root == 0)return false;
	typenode = cJSON_GetObjectItem(root, "type");
	if (typenode == 0)return false;
	typesize = strlen(typenode->valuestring) + 1;
	*msgtype = new char[typesize];
	strcpy(*msgtype, typenode->valuestring);
	cJSON_Delete(root);
	return true;
}