#include"JsonStringParser.h"
#include<string>
#include<stdlib.h>
#include"cJSON.h"
#include<iostream>
HIM::JsonStringParser::JsonStringParser(const char * jsonstr)
{
	int strl = 0;
	 strl=strlen(jsonstr);
	 this->mpJsonStr = new char[strl+1];
	 strcpy(this->mpJsonStr, jsonstr);
}
HIM::JsonStringParser::~JsonStringParser()
{
	//std::cout<< "Îö¹¹" << std::endl;
	delete[] this->mpJsonStr;
}
bool HIM::JsonStringParser::parseLoginJson(  char ** name, char ** password)
{
	cJSON * root = 0, *type = 0, *data = 0, *jsonname=0, *jsonpwd=0;
	int namelen = 0, pwdlen = 0;
 	root=cJSON_Parse(this->mpJsonStr);
	if (root == 0)return false;
	  type=cJSON_GetObjectItem(root, "type");
	  if (type == 0)return false;
	  data = cJSON_GetObjectItem(root, "data");
	  if (data == 0)return false;
	  jsonname = cJSON_GetObjectItem(data, "name");
	  if (0 == jsonname)return false;
	  jsonpwd = cJSON_GetObjectItem(data, "password");
	  if (0 == jsonpwd)return false;
	  // std::cout << jsonname->valuestring << ":" << jsonpwd->valuestring << std::endl;
	  namelen = strlen(jsonname->valuestring);
	  pwdlen = strlen(jsonpwd->valuestring);
	  *name = new char[namelen + 1];
	  *password = new char[pwdlen + 1];
	  strcpy(*name, jsonname->valuestring);
	  strcpy(*password, jsonpwd->valuestring);
	  cJSON_Delete(root);
	return true;
}