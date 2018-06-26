#include"MsgProtocolResolover.h"
#include"cJSON.h"
HIM::MsgProtocolResolover::MsgProtocolResolover(boost::shared_ptr<ip::tcp::socket> sock)
{
	this->msock = sock;
}
HIM::MsgProtocolResolover::~MsgProtocolResolover()
{

}
void HIM::MsgProtocolResolover::startResolvingLoop()
{
	//头部字节数据(留一个\0的位置)
	char chead[5];
	memset(chead, '\0', 5);
	//已读头部位置
	int  readhead = 0;
	//消息主体大小
	int bodysize = 0;
	//消息主体
	char cbody[2049];
	memset(cbody, '\0', 2049);
	//已读消息主体
	int readbody = 0;
	while (true)
	{
		//读头部(四字节)
		while (readhead <= 3)
		{
		    readhead+=	msock->read_some(buffer(chead + readhead, 1));
		}
		chead[5] = '\0';
		bodysize=atoi(chead);
		
		if (bodysize > 2048)
		{
			//消息主体太大
		}
		//读消息主体

		//读头部(四字节)
		while (readbody <= bodysize-1)
		{
			readbody += msock->read_some(buffer(cbody + readbody, 1));
		}
		//把cbody传入JsonStringParser 进行处理
		
		//消息分派
		//复位
		memset(chead, '\0', 5);
		readhead = 0;
		memset(cbody, '\0', 2049);
		break;
	}

}
bool HIM::MsgProtocolResolover::msgType(char * jsonstr, char ** msgtype)
{
	cJSON * root = 0, *typenode;
	int typesize = 0;
	root=cJSON_Parse(jsonstr);
	if (root == 0)return false;
	typenode = cJSON_GetObjectItem(root, "type");
	typesize=strlen(typenode->valuestring)+1;
	*msgtype = new char[typesize];
	strcpy(*msgtype, typenode->valuestring);
	cJSON_Delete(root);
	return true;
}