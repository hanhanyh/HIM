#include<iostream>
#include<boost\asio.hpp>
using namespace std;
using namespace boost::asio;
int main()
{
	
	
		io_service service;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	boost::system::error_code e;
	ip::tcp::socket sock(service);
	try{
		sock.connect(ep);
	} catch (boost::system::system_error ex)
	{
		cout << "异常代码：" << ex.code() << endl;
	}
	cout << "连接服务器成功！" << endl;
	cout << "请输入要发送的内容：（回车结束）" << endl;
	while (true)
	{
		char head[5];
		int offset = 0;
		int bodysize = 0;
		memset(head, '\0', 5);
		char body[2048];
		char data[3000];
		memset(data, '\0', 3000);
		memset(body, '\0', 2048);
		
	//	sock.read_some(buffer(data));
	//	cout << "收到的数据" << data << endl;
		cin >> body;
		bodysize = strlen(body);
		if (bodysize > 0 && bodysize < 10)
		{
			offset = 3;
		}
		else if (bodysize >= 10 && bodysize < 100)
		{
			offset = 2;
		}
		else if (bodysize >= 100 && bodysize < 1000)
		{
			offset = 1;
		}
		else if (bodysize > 1000)
		{
			offset = 0;
		}
		 
		itoa(bodysize, head+offset, 10);//int to ascii 10进制
		for (int i = 0; i < offset; i++)
		{
			head[i] = '0';
		}
		strcpy(data, head);
		strcpy(data + 4, body);
		sock.write_some(buffer(data,strlen(data)));
	}

	return 0;
}