#ifndef JSONSTRINGPARSER_H_
#define JSONSTRINGPARSER_H_
namespace HIM{
	class JsonStringParser
	{
	private:
		char * mpJsonStr;
	public:
		//Json���ݽ����� ���캯������jsonstr
		JsonStringParser(const char * jsonstr);
		//����
		~JsonStringParser();
	public:
		//������¼Json���� �������ָ�� �û�����
		bool parseLoginJson(char ** name, char ** password);
	};
}
#endif