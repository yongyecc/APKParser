
#include "parser.h"


void parser::init(const char* apk_fpath)
{
	FILE* fp = fopen(apk_fpath, "r");
	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buff = (char*)malloc(file_size);
	fread(buff, 1, file_size, fp);

	char * ptr = (char*)malloc(file_size);
	memset(ptr, 0, file_size);

	dex_file* dex = (dex_file*) &ptr;
	dex->header->field_ids_off = 0;
	dex->header->field_ids_off = 1;
	//memset(dex, 0, 0x70);
	dex_header* header;
	
	//memcpy(dex, buff, 0x70);
	//dex = (parser::dex_file*)&buff;
	//dex->string_ids = vector<dex_string_ids>();
	return;
}