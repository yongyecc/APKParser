
#include "parser.h"
#include <iostream>

int readUnsignedLeb128(uint8_t** pStream)
{
	/* taken from dalvik's libdex/Leb128.h */
	uint8_t* ptr = *pStream;
	int result = *(ptr++);

	if (result > 0x7f) {
		int cur = *(ptr++);
		result = (result & 0x7f) | ((cur & 0x7f) << 7);
		if (cur > 0x7f) {
			cur = *(ptr++);
			result |= (cur & 0x7f) << 14;
			if (cur > 0x7f) {
				cur = *(ptr++);
				result |= (cur & 0x7f) << 21;
				if (cur > 0x7f) {
					/*
					 * Note: We don't check to see if cur is out of
					 * range here, meaning we tolerate garbage in the
					 * high four-order bits.
					 */
					cur = *(ptr++);
					result |= cur << 28;
				}
			}
		}
	}

	*pStream = ptr;
	return result;
}

int uleb128_value(uint8_t* pStream)
{
	uint8_t* ptr = pStream;
	int result = *(ptr++);

	if (result > 0x7f) {
		int cur = *(ptr++);
		result = (result & 0x7f) | ((cur & 0x7f) << 7);
		if (cur > 0x7f) {
			cur = *(ptr++);
			result |= (cur & 0x7f) << 14;
			if (cur > 0x7f) {
				cur = *(ptr++);
				result |= (cur & 0x7f) << 21;
				if (cur > 0x7f) {
					/*
					 * Note: We don't check to see if cur is out of
					 * range here, meaning we tolerate garbage in the
					 * high four-order bits.
					 */
					cur = *(ptr++);
					result |= cur << 28;
				}
			}
		}
	}
	return result;
}

char* parser::get_string_by_id(uint32_t idx)
{
	char* p = NULL;
	p = (char*)parser::string_list[idx];
	return p;
}

parser::dex_method_ids parser::get_method_by_id(uint16_t idx)
{
	return parser::method_list[idx];
}

size_t len_uleb128(unsigned long n)
{
	static unsigned char b[32];
	size_t i;

	i = 0;
	do
	{
		b[i] = n & 0x7F;
		if (n >>= 7)
			b[i] |= 0x80;
	} while (b[i++] & 0x80);
	return i;
}

/*wrote this to avoid dumping the leb128 parsing and grabbing code all over the place ;)*/
void printUnsignedLebValue(
	uint8_t* stringData,
	size_t offset,
	FILE* DexFile) {

	uint8_t* uLebBuff;
	int uLebValue, uLebValueLength;

	fseek(DexFile, offset, SEEK_SET); /*move position to the string in data section*/
	uLebBuff = (uint8_t*)malloc(10 * sizeof(uint8_t));
	fread(uLebBuff, 1, sizeof(uLebBuff), DexFile);

	uLebValue = uleb128_value(uLebBuff);
	uLebValueLength = len_uleb128(uLebValue);
	stringData = (uint8_t*)malloc(uLebValue * sizeof(uint8_t) + 1);

	fseek(DexFile, offset + uLebValueLength, SEEK_SET);
	fread(stringData, 1, uLebValue, DexFile);

	stringData[uLebValue] = '\0';
	printf("%s\n", stringData);
	free(uLebBuff);
}


parser::parser(const char* apk_fpath)
{
	FILE* fp = fopen(apk_fpath, "rb");
	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buff = (char*)malloc(file_size);
	fread(buff, 1, file_size, fp);



	dex_file* dex;
	char* ptr0 = (char*)malloc(sizeof(dex_file));
	dex = (dex_file*)ptr0;


	// init DEX HEADER
	char* ptr2 = (char*)malloc(0x70);

	dex->header = (dex_header*)ptr2;
	memcpy(dex->header, buff, 0x70);


	// init DEX STRINGS
	uint32_t string_off = dex->header->string_ids_off;
	uint32_t string_size = dex->header->string_ids_size;

	dex_string_ids* string_id_list;
	dex_string_ids string_id_item;

	string_id_list = (dex_string_ids*)malloc(dex->header->string_ids_size * sizeof(string_id_item));
	fseek(fp, dex->header->string_ids_off, SEEK_SET);
	memcpy(string_id_list, buff+string_off, dex->header->string_ids_size * sizeof(string_id_item));

	uint8_t* p = NULL;
	for (size_t i = 0; i < string_size; i++)
	{
		int n =  uleb128_value((uint8_t*)buff+string_id_list[i].string_data_off);
		int n2 = len_uleb128(n);

		fseek(fp, string_id_list[i].string_data_off+n2, SEEK_SET);
		p = (uint8_t*)malloc(n + 1);

		fread(p, 1, n, fp);
		p[n] = '\0';
		parser::string_list.push_back(p);
	}


	//INIT DEX YTPE
	uint32_t type_size = dex->header->type_ids_size;
	uint32_t type_off = dex->header->type_ids_off;
	dex_type_ids* type_id_list;
	dex_type_ids type_id_item;

	type_id_list = (dex_type_ids*)malloc(type_size * (sizeof(type_id_item)));
	fseek(fp, type_off, SEEK_SET);
	memcpy(type_id_list, buff+type_off, type_size * (sizeof(type_id_item)));

	for (size_t i = 0; i < type_size; i++)
	{
		parser::type_list.push_back(type_id_list[i]);
	}


	// INIT DEX METHODS
	uint32_t method_size = dex->header->method_ids_size;
	uint32_t method_off = dex->header->method_ids_off;
	dex_method_ids* method_id_list;
	dex_method_ids method_id_item;

	method_id_list = (dex_method_ids*)malloc(method_size * sizeof(method_id_item));
	fseek(fp, method_off, SEEK_SET);
	memcpy(method_id_list, buff+method_off, method_size * sizeof(method_id_item));

	for (size_t i = 0; i < method_size; i++)
	{
		parser::method_list.push_back(method_id_list[i]);
	}

	// INIT DEX CLASSES
	uint32_t class_size = dex->header->class_ids_size;
	uint32_t class_off = dex->header->class_id_off;

	for (size_t i = 0; i < class_size; i++)
	{
		dex_class_data class_data_it = { 0 };
		//dex_class_def
		memcpy(&class_data_it.class_def, buff + class_off + i*sizeof(dex_class_def), sizeof(dex_class_def));

		if (class_data_it.class_def.class_data_off == 0) {
			parser::class_data_list.push_back(class_data_it);
			continue;
		}
		
		//static_fields_size¡¢instance_fields_size¡¢direct_methods_size¡¢virtual_methods_size
		uint32_t off = 0;
		uint32_t v = 0;
		uint32_t n = 0;
		for (size_t k = 0; k < 4; k++)
		{
			v = uleb128_value((uint8_t*)buff + class_data_it.class_def.class_data_off + off);
			n = len_uleb128(v);
			switch (k)
			{
			case 0:
				class_data_it.class_data.static_fields_size = v;
				break;
			case 1:
				class_data_it.class_data.instance_fields_size = v;
				break;
			case 2:
				class_data_it.class_data.direct_methods_size = v;
				break;
			case 3:
				class_data_it.class_data.virtual_methods_size = v;
				break;
			default:
				printf("ERROR");
				exit(0);
			}
			off += n;
		}
		//static_fields_list
		for (size_t j = 0; j < class_data_it.class_data.static_fields_size; j++)
		{
			encoded_field static_field;
			for (size_t k = 0; k < 2; k++)
			{
				v = uleb128_value((uint8_t*)buff + class_data_it.class_def.class_data_off + off);
				n = len_uleb128(v);
				switch (k)
				{
				case 0:
					static_field.field_idx = v;
					break;
				case 1:
					static_field.access_flags = v;
					break;
				default:
					printf("ERROR");
					exit(0);;
				}
				off += n;
			}

			class_data_it.class_data.static_fields_list.push_back(static_field);
		}
		//instance_fields_list
		for (size_t j = 0; j < class_data_it.class_data.instance_fields_size; j++)
		{
			encoded_field field = { 0 };
			for (size_t k = 0; k < 2; k++)
			{
				v = uleb128_value((uint8_t*)buff + class_data_it.class_def.class_data_off + off);
				n = len_uleb128(v);
				switch (k)
				{
				case 0:
					field.field_idx = v;
					break;
				case 1:
					field.access_flags = v;
					break;
				default:
					printf("ERROR");
					exit(0);;
				}
				off += n;
			}
			
			class_data_it.class_data.instance_fields_list.push_back(field);
		}
		//direct_method
		for (size_t j = 0; j < class_data_it.class_data.direct_methods_size; j++)
		{
			encoded_method direct_method = { 0 };
			for (size_t k = 0; k < 3; k++)
			{
				v = uleb128_value((uint8_t*)buff + class_data_it.class_def.class_data_off + off);
				n = len_uleb128(v);
				switch (k)
				{
				case 0:
					direct_method.method_idx = v;
					break;
				case 1:
					direct_method.access_flags = v;
					break;
				case 2:
					direct_method.code_off = v;
					break;
				default:
					break;
				}
				off += n;
			}
			//code_item
			if (direct_method.code_off != 0) {
				memcpy(&direct_method.code, buff + direct_method.code_off, 0x10);
				char* ins = (char*)malloc(direct_method.code.insns_size * 2);
				memcpy(ins, buff + direct_method.code_off + 0x10, direct_method.code.insns_size * 2);
				direct_method.code.insns = ins;
			}
			class_data_it.class_data.directmethods_list.push_back(direct_method);
		}
		//virtual_method
		for (size_t j = 0; j < class_data_it.class_data.virtual_methods_size; j++)
		{
			encoded_method virtual_method = {0};
			for (size_t k = 0; k < 3; k++)
			{
				v = uleb128_value((uint8_t*)buff + class_data_it.class_def.class_data_off + off);
				n = len_uleb128(v);
				switch (k)
				{
				case 0:
					virtual_method.method_idx = v;
					break;
				case 1:
					virtual_method.access_flags = v;
					break;
				case 2:
					virtual_method.code_off = v;
					break;
				default:
					break;
				}
				off += n;
			}
			//code_item
			if (virtual_method.code_off != 0) {
				virtual_method.code = { 0 };
				memcpy(&virtual_method.code, buff + virtual_method.code_off, 0x10);
				char* ins = (char*)malloc(virtual_method.code.insns_size * 2);
				memcpy(ins, buff + virtual_method.code_off + 0x10, virtual_method.code.insns_size * 2);
				virtual_method.code.insns = ins;
			}
			class_data_it.class_data.virtualmethods_list.push_back(virtual_method);
		}
		//if(i==8){
		//	printf("%d -> compeleted\n", i);
		//}
		//printf("%d -> compeleted\n", i);
		parser::class_data_list.push_back(class_data_it);
	}


	parser::fdex = dex;
	return;
}

char* parser::get_classname_by_id(uint32_t idx) {
	 parser::dex_class_data class_data = parser::class_data_list[idx];
	 char* class_name = parser::get_string_by_id(parser::type_list[class_data.class_def.class_idx].descriptor_idx);
	return class_name;
}





