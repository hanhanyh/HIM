#ifndef _JSONSTRINGBUILDER_H_
#define _JSONSTRINGBUILDER_H_
#include"cJSON.h"
#include<string>

namespace HIM{
	class JsonStringBuilder
	{
	public:
		//���캯��
		JsonStringBuilder();
		//��������
		~JsonStringBuilder();
		//��������json
		std::string buildErrorJson(std::string msg);
		//������¼�����Ӧ
		std::string buildLoginResponse(bool result =false);
		//������¼����Json
		std::string buildLoginRequest(std::string name, std::string pwd);
		//�Ե������ѷ�����Ϣ
		std::string Buildsendp2pmsg(std::string sendername, std::string receivername, std::string detail, std::string sendtime);
		//���ͺ������������
		std::string buildp2pfriendrequest(std::string sendername, std::string receivername, std::string detail, std::string sendtime);
		//���ͺ�������Ӧ��
		std::string buildp2pfriendresponse(std::string sendername, std::string receivername, std::string detail, bool result, std::string sendtime);
	private:
		cJSON * root;
	};


}
#endif