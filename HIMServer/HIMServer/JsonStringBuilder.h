#ifndef _JSONSTRINGBUILDER_H_
#define _JSONSTRINGBUILDER_H_
#include"cJSON.h"
#include<string>

namespace HIM{
	class JsonStringBuilder
	{
	public:
		//构造函数
		JsonStringBuilder();
		//析构函数
		~JsonStringBuilder();
		//创建错误json
		std::string buildErrorJson(std::string msg);
		//创建登录结果响应
		std::string buildLoginResponse(bool result =false);
		//创建登录请求Json
		std::string buildLoginRequest(std::string name, std::string pwd);
		//对单个好友发送消息
		std::string Buildsendp2pmsg(std::string sendername, std::string receivername, std::string detail, std::string sendtime);
		//发送好友请求（提出）
		std::string buildp2pfriendrequest(std::string sendername, std::string receivername, std::string detail, std::string sendtime);
		//发送好友请求（应答）
		std::string buildp2pfriendresponse(std::string sendername, std::string receivername, std::string detail, bool result, std::string sendtime);
	private:
		cJSON * root;
	};


}
#endif