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
		//�����б�
		std::list<boost::shared_ptr<ip::tcp::socket>> * socketlist = 0;
		//������
		boost::mutex socklistmutex;
		//�����˿�
		int * mport;
	public:
		HIMServer(int port);
		~HIMServer();
		//����
		void start();
	private:
	
		//ɾ��һ������sock
		void RemoveListItem(boost::shared_ptr<ip::tcp::socket> ptr);
		//���� �ַ�
		void doing(boost::shared_ptr<ip::tcp::socket> sock);
		//��ϢЭ�����ѭ��
		void startResolvingLoop(boost::shared_ptr<ip::tcp::socket> sock);
		 //�ж���Ϣ����
		 bool msgType(char * jsonstr, char ** msgtype);
		
	};
}
#endif