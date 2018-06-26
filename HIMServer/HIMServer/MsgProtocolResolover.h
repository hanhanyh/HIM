#ifndef MSGPROTOCOLRESOLOVER_H_
#define MSGPROTOCOLRESOLOVER_H_
#include<boost\asio.hpp>
#include<boost\shared_ptr.hpp>
using namespace  boost::asio;
namespace HIM
{
	class MsgProtocolResolover
	{
	private :
		//与客户端连接的套接字 引用计数智能指针
		boost::shared_ptr<ip::tcp::socket> msock;
		//判断消息类型
		bool msgType(char * jsonstr, char ** msgtype);
	public:
		//消息协议解析器
		MsgProtocolResolover(boost::shared_ptr<ip::tcp::socket> sock);
		~MsgProtocolResolover();
	public:
		//开始解析循环
	    void 	startResolvingLoop();
	};
}
#endif