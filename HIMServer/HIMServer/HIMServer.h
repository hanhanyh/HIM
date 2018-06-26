#ifndef _HIMSERVER_H_
#define _HIMSERVER_H_
#include<boost\asio.hpp>
#include<boost\function.hpp>
#include<boost\bind.hpp>
#include<boost\thread.hpp>

using namespace boost::asio;
namespace HIM{
	 
	class HIMServer{
	private:
		//在线列表
		std::list<boost::shared_ptr<ip::tcp::socket>> * socketlist = 0;
		//互斥锁
		boost::mutex socklistmutex;
		//监听端口
		int * mport;
	public:
		HIMServer(int port);
		~HIMServer();
		//开启
		void start();
	private:
	
		//删除一个在线sock
		void RemoveListItem(boost::shared_ptr<ip::tcp::socket> ptr);
		//运行 分发
		void doing(boost::shared_ptr<ip::tcp::socket> sock);
		//消息协议解析循环
		void startResolvingLoop(boost::shared_ptr<ip::tcp::socket> sock);
		 //判断消息类型
		 bool msgType(char * jsonstr, char ** msgtype);
		
	};
}
#endif