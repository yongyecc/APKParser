#pragma once

#include <vector>

using namespace std;

class parser
{
	


public:
	//DEX Header
	struct dex_magic
	{
		char dex[3];
		char newline;
		char ver[3];
		char zero;
	};

	struct dex_header
	{
		dex_magic magic;
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
	struct encoded_field
	{
		uint32_t field_idx;
		uint32_t access_flags;
	};

	struct code_item
	{
		uint16_t registers_size;
		uint16_t ins_size;
		uint16_t outs_size;
		uint16_t tries_size;
		uint32_t debug_info_off;
		uint32_t insns_size;
		char* insns;
	};

	struct  encoded_method
	{
		uint32_t method_idx;
		uint32_t access_flags;
		uint32_t code_off;
		code_item code;
	};

	struct class_data_item
	{
		uint32_t static_fields_size;
		uint32_t instance_fields_size;
		uint32_t direct_methods_size;
		uint32_t virtual_methods_size;
		vector<encoded_field> instance_fields_list;
		vector<encoded_field> static_fields_list;
		vector<encoded_method> directmethods_list;
		vector<encoded_method> virtualmethods_list;
	};

	struct dex_class_def
	{
		uint32_t class_idx;
		uint32_t access_flag;
		uint32_t superclass_idx;
		uint32_t interfaces_off;
		uint32_t source_file_idx;
		uint32_t annotations_off;
		uint32_t class_data_off;
		uint32_t static_values_off;
	};

	struct dex_class_data
	{
		dex_class_def class_def;
		class_data_item class_data;
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
		vector<dex_class_def> class_defs;
		vector<dex_map_list> map_list;
	};

public:
	dex_file* fdex;
	parser(const char* fp);
	vector<uint8_t*> string_list;
	vector<dex_method_ids> method_list;
	vector<dex_type_ids> type_list;
	vector<dex_class_def> class_def_list;
	vector<dex_class_data> class_data_list;
	char* get_string_by_id(uint32_t idx);
	parser::dex_method_ids get_method_by_id(uint16_t idx);

};
