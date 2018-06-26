#ifndef JSONSTRINGPARSER_H_
#define JSONSTRINGPARSER_H_
namespace HIM{
	class JsonStringParser
	{
	private:
		char * mpJsonStr;
	public:
		//Json数据解析器 构造函数传入jsonstr
		JsonStringParser(const char * jsonstr);
		//析构
		~JsonStringParser();
	public:
		//解析登录Json数据 传入二级指针 用户返回
		bool parseLoginJson(char ** name, char ** password);
	};
}
#endif