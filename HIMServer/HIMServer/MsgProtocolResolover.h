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
		//��ͻ������ӵ��׽��� ���ü�������ָ��
		boost::shared_ptr<ip::tcp::socket> msock;
		//�ж���Ϣ����
		bool msgType(char * jsonstr, char ** msgtype);
	public:
		//��ϢЭ�������
		MsgProtocolResolover(boost::shared_ptr<ip::tcp::socket> sock);
		~MsgProtocolResolover();
	public:
		//��ʼ����ѭ��
	    void 	startResolvingLoop();
	};
}
#endif