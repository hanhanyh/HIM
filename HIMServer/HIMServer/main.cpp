#include<iostream>
#include<stdlib.h>
#include<list>
#include<boost\asio.hpp>
#include<boost\function.hpp>
#include<boost\bind.hpp>
#include<boost\thread.hpp>
#include"JsonStringBuilder.h"
#include"HIMServer.h"
#include"JsonStringParser.h"
#include"MsgProtocolResolover.h"
using namespace std;
using namespace boost::asio;
 
int main()
{
	 
   boost::shared_ptr<HIM::HIMServer> server(new HIM::HIMServer(2001));
	server->start();
	//HIM::JsonStringBuilder js;
 //  string s=	js.buildLoginRequest("¹Ô¹Ô", "Ã´Ã´");

	//boost::shared_ptr<HIM::JsonStringParser> parser(new HIM::JsonStringParser(s.data()));
	//char * p = 0, *k = 0;
	//parser->parseLoginJson(&p, &k);
	//cout << p <<":"<< k << endl;;
	
	//
	//HIM::MsgProtocolResolover * pPR = new HIM::MsgProtocolResolover()
	//while (true);
}