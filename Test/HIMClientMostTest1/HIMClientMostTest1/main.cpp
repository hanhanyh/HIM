#include<iostream>
#include<boost\asio.hpp>
#include<boost\bind.hpp>
#include<boost\function.hpp>
#include<boost\thread.hpp>
using namespace std;
using namespace boost::asio;
void connect();
int main()
{
	boost::function0<void> f = boost::bind(connect);
	for (int i = 0; i < 10240;i++)
	{
		boost::thread t(f);
		t.detach();
	}
	system("pause");
	return 0;
}
void connect()
{
	io_service service;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	boost::system::error_code e;
	ip::tcp::socket sock(service);
	try{
		sock.connect(ep);
	}
	catch (boost::system::system_error ex)
	{
		cout << "�쳣���룺" << ex.code() << endl;
	}
	cout << "���ӷ������ɹ���" << endl;
	cout << "������Ҫ���͵����ݣ����س�������" << endl;
	while (true)
	{
		char data[512];
		memset(data, '\0', 512);
		//	sock.read_some(buffer(data));
		///	cout << "�յ�������" << data << endl;
		//	cin >> data;
		sock.write_some(buffer("Test11111111"));
	}
}