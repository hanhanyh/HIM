#include"JsonStringBuilder.h"

HIM::JsonStringBuilder::JsonStringBuilder()
{
	this->root = cJSON_CreateObject();
}

HIM::JsonStringBuilder::~JsonStringBuilder()
{
	cJSON_Delete(this->root);
}
std::string HIM::JsonStringBuilder::buildErrorJson(std::string msg)
{
	cJSON  *data, *detail;
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("error"));
	data = cJSON_CreateObject();
	cJSON_AddItemToObject(data,"detail", cJSON_CreateString(msg.data()));
	cJSON_AddItemToObject(root, "data", data);
	return std::string(cJSON_Print(root));
}
std::string HIM::JsonStringBuilder::buildLoginResponse(bool result)
{
	int re = result == true ? 1 : 0;
	cJSON * data, *detail;
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("loginresponse"));
	data = cJSON_CreateObject();
	cJSON_AddItemToObject(data, "result", cJSON_CreateNumber(re));
	cJSON_AddItemToObject(root, "data", data);
	return std::string(cJSON_Print(root));
	
}
std::string HIM::JsonStringBuilder::buildLoginRequest(std::string name, std::string pwd)
{
	cJSON * data;
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("login"));
	data = cJSON_CreateObject();
	cJSON_AddItemToObject(data, "name", cJSON_CreateString(name.data()));
	cJSON_AddItemToObject(data, "password", cJSON_CreateString(pwd.data()));
	cJSON_AddItemToObject(root, "data", data);
	return std::string(cJSON_Print(root));
}
std::string HIM::JsonStringBuilder::Buildsendp2pmsg(std::string sendername, std::string receivername, std::string detail, std::string sendtime)
{
	cJSON * data;
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("p2pmsg"));
	data = cJSON_CreateObject();
	cJSON_AddItemToObject(data, "sendername", cJSON_CreateString(sendername.data()));
	cJSON_AddItemToObject(data, "receivername", cJSON_CreateString(receivername.data()));
	cJSON_AddItemToObject(data, "detail", cJSON_CreateString(detail.data()));
	cJSON_AddItemToObject(data, "sendtime", cJSON_CreateString(sendtime.data()));
	cJSON_AddItemToObject(root, "data", data);
	return std::string(cJSON_Print(root));
}
std::string HIM::JsonStringBuilder::buildp2pfriendrequest(std::string sendername, std::string receivername, std::string detail, std::string sendtime)
{
	return std::string("null");
}
std::string  HIM::JsonStringBuilder::buildp2pfriendresponse(std::string sendername, std::string receivername, std::string detail, bool result, std::string sendtime)
{
	return std::string("null");
}