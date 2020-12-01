#pragma once

#include <vector>

using namespace std;

class parser
{
	


public:
	//DEX Header
	struct dex_header
	{
		struct dex_magic
		{
			char dex[3];
			char newline;
			char ver[3];
			char zero;
		};
		uint32_t checksum;
		char signature[20];
		uint32_t file_size;
		uint32_t header_size;
		uint32_t endian_tag;
		uint32_t link_size;
		uint32_t link_off;
		uint32_t map_off;

		uint32_t string_ids_size;
		uint32_t string_ids_off;

		uint32_t type_ids_size;
		uint32_t type_ids_off;

		uint32_t proto_ids_size;
		uint32_t proto_ids_off;

		uint32_t field_ids_size;
		uint32_t field_ids_off;

		uint32_t method_ids_size;
		uint32_t method_ids_off;

		uint32_t class_ids_size;
		uint32_t class_id_off;

		uint32_t data_size;
		uint32_t data_off;
	};


	//DEX STRINGS节区
	struct string_data
	{
		vector<char> utf16_size;
		vector<char> data;
	};

	struct dex_string_ids
	{
		uint32_t string_data_off;
		//string_data str_data;
	};


	//DEX TYPE节区
	struct dex_type_ids
	{
		uint32_t descriptor_idx;
	};


	//DEX PROTO节区
	struct dex_proto_ids
	{
		uint32_t shorty_idx;
		uint32_t return_type_idx;
		uint32_t parameters_off;
	};


	//DEX FIELDS节区
	struct dex_field_ids
	{
		uint16_t class_idx;
		uint16_t type_idx;
		uint16_t name_idx;
	};


	// DEX METHOD节区
	struct dex_method_ids
	{
		uint16_t class_idx;
		uint16_t proto_idx;
		uint32_t name_idx;
	};


	//DEX CLASS节区
	struct dex_class_defs
	{
		uint32_t class_idx;
		uint32_t access_flag;
		uint32_t superclass_idx;
		uint32_t interfaces_off;
		uint32_t source_file_idx;
		uint32_t annotations_off;
		uint32_t class_data_off;
		
		char cls_data[0x20];
	};


	//DEX MAP节区
	struct name_item_list
	{
		uint16_t type;
		uint16_t unused;
		uint32_t size;
		uint32_t offset;
	};

	struct dex_map_list
	{
		uint32_t size;
		vector<name_item_list> map_item;
	};


	struct dex_file
	{
		dex_header* header;
		vector<dex_string_ids> string_ids;
		vector<dex_type_ids> type_ids;
		vector<dex_proto_ids> proto_ids;
		vector<dex_field_ids> field_ids;
		vector<dex_method_ids> method_ids;
		vector<dex_class_defs> class_defs;
		vector<dex_map_list> map_list;
	};

public:
	dex_file* fdex;
	parser(const char* fp);
	vector<uint8_t*> string_list;
	vector<dex_method_ids> method_list;
	vector<dex_type_ids> type_list;

	char* get_string_by_id(uint32_t idx);
	parser::dex_method_ids get_method_by_id(uint16_t idx);

};
