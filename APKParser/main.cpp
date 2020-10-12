#include "parser.h"



int main()
{
	
	parser apk_parser;
	const char* fp = "d:\\Android\\sample\\classes.dex";
	
	apk_parser.init(fp);
	return 0;
}