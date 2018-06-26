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
	//ͷ���ֽ�����(��һ��\0��λ��)
	char chead[5];
	memset(chead, '\0', 5);
	//�Ѷ�ͷ��λ��
	int  readhead = 0;
	//��Ϣ�����С
	int bodysize = 0;
	//��Ϣ����
	char cbody[2049];
	memset(cbody, '\0', 2049);
	//�Ѷ���Ϣ����
	int readbody = 0;
	while (true)
	{
		//��ͷ��(���ֽ�)
		while (readhead <= 3)
		{
		    readhead+=	msock->read_some(buffer(chead + readhead, 1));
		}
		chead[5] = '\0';
		bodysize=atoi(chead);
		
		if (bodysize > 2048)
		{
			//��Ϣ����̫��
		}
		//����Ϣ����

		//��ͷ��(���ֽ�)
		while (readbody <= bodysize-1)
		{
			readbody += msock->read_some(buffer(cbody + readbody, 1));
		}
		//��cbody����JsonStringParser ���д���
		
		//��Ϣ����
		//��λ
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