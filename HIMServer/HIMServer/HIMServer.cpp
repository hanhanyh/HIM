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
			//	cout << "线程退出" << endl;
			//broadCast(data);
			//sock->write_some(buffer(data));
	    }
		catch (boost::system::system_error error)
		{
			cout << "异常代码：" << error.code() << endl;
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
		//boost bind 调用非静态成员函数 需要在第二个参数传入this(对象的实例)
	 	boost::function<void (boost::shared_ptr<ip::tcp::socket>)> f = boost::bind(&HIMServer::doing,this,boost::placeholders::_1);
		boost::thread t(f,sock);
	}
}

void HIM::HIMServer::startResolvingLoop(boost::shared_ptr<ip::tcp::socket> sock)
{
	char * msgType = 0;//考虑用智能指针
	//当前登录的用户名
	char * currentUserName = new char[1024];//考虑使用智能指针
	memset(currentUserName, '\0', 1024);
	while (true)
	{
		//头部字节数据(留一个\0的位置)
		char chead[5];
		//消息类型
		msgType = new char[50];
		memset(msgType, '\0', 50);

		memset(chead, '\0', 5);
		//已读头部位置
		int  readhead = 0;
		//消息主体大小
		int bodysize = 0;
		//消息主体
		char cbody[2049];
		memset(cbody, '\0', 2049);
		//已读消息主体
		int readbody = 0;

		//读头部(四字节)
		while (readhead <= 3)
		{
			readhead += sock->read_some(buffer(chead + readhead, 1));
		}
		chead[4] = '\0';
		bodysize = atoi(chead);

		if (bodysize > 2048)
		{
			//消息主体太大
		}
		//读消息主体

		std::cout << "数据正在接收" << endl;
		//读主体
		while (readbody <= (bodysize - 1))
		{
			readbody += sock->read_some(buffer(cbody + readbody, 1));
		}
		//把cbody传入JsonStringParser 进行处理
		std::cout << cbody << endl;
		std::cout << "---数据成功接收-" << endl;
		//解析消息类型
		if (this->msgType(cbody, &msgType) == false)
		{
			std::cout << "解析消息类型失败！" << endl;
			sock->close();//这里还需要删除列表
			this->RemoveListItem(sock);
			break;
		}
		std::cout << "消息类型:" << msgType << endl;
		//消息分派
	 	if (strcmp("login", msgType) == 0) //登录操作
		{

		}
		else if (strcmp("p2pmsg", msgType) == 0)//发送消息给好友
		{
			
		}
		else if (strcmp("p2pfriendrequest", msgType) == 0)//好友请求
		{
		
		}
		else if (strcmp("p2pfriendresponse", msgType) == 0)//好友请求应答
		{
		
		}
		else if (strcmp("groupmsg", msgType) == 0)//群消息
		{

		}
		else if (strcmp("groupaddrequest", msgType) == 0)//群请求
		{
		
		}
		else if (strcmp("groupaddresponse", msgType) == 0)//加入
		{

		}
		////复位
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