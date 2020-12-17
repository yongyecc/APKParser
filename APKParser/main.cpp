#include "parser.h"
#include "md5.h"
#include "Crc32.h"
#include <json/json.h>
#include <fstream>
#include <json/json.h>


struct oneOpcode
{
    char* stringAddr;
    uint8_t opcode;
};

uint32_t featureBlckLen = 0;
vector<uint8_t> ops;
uint32_t scanMethodSize = 0;


vector<oneOpcode> func_30B(uint16_t* a1, int a2, parser dex_parser)
{

    ops.clear();
    featureBlckLen = 0;
    uint32_t str_size = 0;
    uint32_t opcodeMD5Size = 0;
    //a1: 指令码指针。
    //a2: 指令码长度
    __int64(__fastcall * v6)(__int16*, __int64); // [rsp+8h] [rbp-F8h]
    uint16_t* v7; // [rsp+30h] [rbp-D0h]
    __int16 v8; // [rsp+4Ah] [rbp-B6h]
    __int64 v9; // [rsp+50h] [rbp-B0h]
    uint8_t v5;

    vector<oneOpcode> allOpcode;

    char* ret = NULL;
    uint32_t feature_size = 0;
    
    vector<uint8_t> only_op;
    uint32_t string_number=0;

    v7 = a1;        
    v9 = 0;
    uint32_t opcode_number = 0;
    
    //一个类方法中堆块4的数量，有类方法中独立块MD5计算引用
    uint32_t heap4Size = 0;

LABEL_228:
    while (v7 < (uint16_t*)((char*)a1 + a2))
    {
        oneOpcode oneOP = {0};
        
        uint32_t ops_len = ops.size();
        v8 = *v7;
        v5 = v8;
        opcode_number += 1;
        only_op.push_back(v5);

        oneOP.opcode = v5;
        /*if (ops.size() >= 60) 
        {
            std::printf("");
        }
        std::printf("[%d] %x\n", ops.size(), v8);*/
        
        char* s = 0;
        if (v5 != 0x00)
        {

            ops.push_back(v5);
        }
            
        if (v5 <= 0x6Du || v5 > 0x78u)
        {
            if (v5 == 0x1A)
            {
                uint16_t string_id = (uint16_t)v7[1];
                s = dex_parser.get_string_by_id(string_id);
                if (!strncmp(s, ".", 1))
                {
                    s = 0;            
                }
                else if (!strncmp(s, "", 1))
                {
                    oneOP.stringAddr = s;
                    string_number++;
                }
                else
                {
                    ops.push_back('\0');
                    str_size += strlen(s);
                    string_number++;
                    for (size_t i = 0; i < strlen(s); i++)
                    {
                        ops.push_back(s[i]);
                    }
                    ops.push_back('\0');
                    oneOP.stringAddr = s;
                }
                
            }     
        }
        else
        {
            uint16_t md_id = (uint16_t)v7[1];
            if (md_id < dex_parser.method_list.size()) {
                parser::dex_method_ids method = dex_parser.get_method_by_id(md_id);
                uint32_t class_idx = method.class_idx;
                uint32_t s_id = dex_parser.type_list[class_idx].descriptor_idx;
                char* class_str = dex_parser.get_string_by_id(s_id);
                if (!strncmp(class_str, "Landroid/", 9) || !strncmp(class_str, "Ldalvik/", 8) || !strncmp(class_str, "Ljava/", 6)
                    || !strncmp(class_str, "Ljavax/", 7) || !strncmp(class_str, "Lorg/", 5))
                {
                    ops.push_back('\0');
                    uint32_t n_id = method.name_idx;
                    s = dex_parser.get_string_by_id(n_id);
                    str_size += strlen(s);
                    //std::printf("%s\n", s);
                    string_number++;
                    for (size_t i = 0; i < strlen(s); i++)
                    {
                        ops.push_back(s[i]);

                    }
                    ops.push_back('\0');
                    oneOP.stringAddr = s;
                }
            }

        }
        allOpcode.push_back(oneOP);
        
        if ((v5 == 0x300 || v5 == 0x200 || v5 == 0x100) && v9)// 0x300：数组
        {
            v7 += (unsigned int)v9;
        }
        else if ((unsigned __int8)v5 == 0x32 && v9)
        {
            v7 += (unsigned int)v9;
        }
        else
        {
            if (v9)
                return allOpcode;
        LABEL_12:
            switch ((unsigned __int8)v5)
            {
            case 0u:
                ++v7;
                break;
            case 1u:
                ++v7;
                break;
            case 2u:
                v7 += 2;
                break;
            case 3u:
                v7 += 3;
                break;
            case 4u:
                ++v7;
                break;
            case 5u:
                v7 += 2;
                break;
            case 6u:
                v7 += 3;
                break;
            case 7u:
                ++v7;
                break;
            case 8u:
                v7 += 2;
                break;
            case 9u:
                v7 += 3;
                break;
            case 0xAu:
                ++v7;
                break;
            case 0xBu:
                ++v7;
                break;
            case 0xCu:
                ++v7;
                break;
            case 0xDu:
                ++v7;
                break;
            case 0xEu:
            case 0xFu:
            case 0x10u:
            case 0x11u:
                ++v7;
                break;
            case 0x12u:
                ++v7;
                break;
            case 0x13u:
                v7 += 2;
                break;
            case 0x14u:
                v7 += 3;
                break;
            case 0x15u:
                v7 += 2;
                break;
            case 0x16u:
                v7 += 2;
                break;
            case 0x17u:
                v7 += 3;
                break;
            case 0x18u:
                v7 += 5;
                break;
            case 0x19u:
                v7 += 2;
                break;
            case 0x1Au:
                v7 += 2;
                break;
            case 0x1Bu:
                v7 += 3;
                break;
            case 0x1Cu:
                v7 += 2;
                break;
            case 0x1Du:
                ++v7;
                break;
            case 0x1Eu:
                ++v7;
                break;
            case 0x1Fu:
                v7 += 2;
                break;
            case 0x20u:
                v7 += 2;
                break;
            case 0x21u:
                ++v7;
                break;
            case 0x22u:
                v7 += 2;
                break;
            case 0x23u:
                v7 += 2;
                break;
            case 0x24u:
            case 0x25u:
                v7 += 3;
                break;
            case 0x26u:
                v7 += 3;
                break;
            case 0x27u:
            case 0xE3u:
            case 0xE4u:
            case 0xE5u:
            case 0xE6u:
            case 0xE7u:
            case 0xE8u:
            case 0xE9u:
            case 0xEAu:
            case 0xEBu:
            case 0xECu:
            case 0xEDu:
                ++v7;
                break;
            case 0x28u:
                ++v7;
                break;
            case 0x29u:
                v7 += 2;
                break;
            case 0x2Au:
                v7 += 3;
                break;
            case 0x2Bu:
                v7 += 3;
                break;
            case 0x2Cu:
                v7 += 3;
                break;
            case 0x2Du:
                v7 += 2;
                break;
            case 0x2Eu:
                v7 += 2;
                break;
            case 0x2Fu:
                v7 += 2;
                break;
            case 0x30u:
                v7 += 2;
                break;
            case 0x31u:
                v7 += 2;
                break;
            case 0x32u:
                v7 += 2;
                break;
            case 0x33u:
                v7 += 2;
                break;
            case 0x34u:
                v7 += 2;
                break;
            case 0x35u:
                v7 += 2;
                break;
            case 0x36u:
                v7 += 2;
                break;
            case 0x37u:
                v7 += 2;
                break;
            case 0x38u:
                v7 += 2;
                break;
            case 0x39u:
                v7 += 2;
                break;
            case 0x3Au:
                v7 += 2;
                break;
            case 0x3Bu:
                v7 += 2;
                break;
            case 0x3Cu:
                v7 += 2;
                break;
            case 0x3Du:
                v7 += 2;
                break;
            case 0x3Eu:
            case 0x3Fu:
            case 0x40u:
            case 0x41u:
            case 0x42u:
            case 0x43u:
            case 0x44u:
                v7 += 2;
                break;
            case 0x45u:
                v7 += 2;
                break;
            case 0x46u:
                v7 += 2;
                break;
            case 0x47u:
                v7 += 2;
                break;
            case 0x48u:
                v7 += 2;
                break;
            case 0x49u:
                v7 += 2;
                break;
            case 0x4Au:
                v7 += 2;
                break;
            case 0x4Bu:
                v7 += 2;
                break;
            case 0x4Cu:
                v7 += 2;
                break;
            case 0x4Du:
                v7 += 2;
                break;
            case 0x4Eu:
                v7 += 2;
                break;
            case 0x4Fu:
                v7 += 2;
                break;
            case 0x50u:
                v7 += 2;
                break;
            case 0x51u:
                v7 += 2;
                break;
            case 0x52u:
                v7 += 2;
                break;
            case 0x53u:
                v7 += 2;
                break;
            case 0x54u:
                v7 += 2;
                break;
            case 0x55u:
                v7 += 2;
                break;
            case 0x56u:
                v7 += 2;
                break;
            case 0x57u:
                v7 += 2;
                break;
            case 0x58u:
                v7 += 2;
                break;
            case 0x59u:
                v7 += 2;
                break;
            case 0x5Au:
                v7 += 2;
                break;
            case 0x5Bu:
                v7 += 2;
                break;
            case 0x5Cu:
                v7 += 2;
                break;
            case 0x5Du:
                v7 += 2;
                break;
            case 0x5Eu:
                v7 += 2;
                break;
            case 0x5Fu:
                v7 += 2;
                break;
            case 0x60u:
                v7 += 2;
                break;
            case 0x61u:
                v7 += 2;
                break;
            case 0x62u:
                v7 += 2;
                break;
            case 0x63u:
                v7 += 2;
                break;
            case 0x64u:
                v7 += 2;
                break;
            case 0x65u:
                v7 += 2;
                break;
            case 0x66u:
                v7 += 2;
                break;
            case 0x67u:
                v7 += 2;
                break;
            case 0x68u:
                v7 += 2;
                break;
            case 0x69u:
                v7 += 2;
                break;
            case 0x6Au:
                v7 += 2;
                break;
            case 0x6Bu:
                v7 += 2;
                break;
            case 0x6Cu:
                v7 += 2;
                break;
            case 0x6Du:
                v7 += 2;
                break;
            case 0x6Eu:
            case 0x6Fu:
            case 0x70u:
            case 0x71u:
            case 0x72u:
            case 0x73u:
            case 0x74u:
            case 0x75u:
            case 0x76u:
            case 0x77u:
            case 0x78u:
            case 0xF8u:
            case 0xF9u:
            case 0xFAu:
            case 0xFBu:
                v7 += 3;
                break;
            case 0x79u:
            case 0x7Au:
            case 0x7Bu:
                ++v7;
                break;
            case 0x7Cu:
                ++v7;
                break;
            case 0x7Du:
                ++v7;
                break;
            case 0x7Eu:
                ++v7;
                break;
            case 0x7Fu:
                ++v7;
                break;
            case 0x80u:
                ++v7;
                break;
            case 0x81u:
                ++v7;
                break;
            case 0x82u:
                ++v7;
                break;
            case 0x83u:
                ++v7;
                break;
            case 0x84u:
                ++v7;
                break;
            case 0x85u:
                ++v7;
                break;
            case 0x86u:
                ++v7;
                break;
            case 0x87u:
                ++v7;
                break;
            case 0x88u:
                ++v7;
                break;
            case 0x89u:
                ++v7;
                break;
            case 0x8Au:
                ++v7;
                break;
            case 0x8Bu:
                ++v7;
                break;
            case 0x8Cu:
                ++v7;
                break;
            case 0x8Du:
                ++v7;
                break;
            case 0x8Eu:
                ++v7;
                break;
            case 0x8Fu:
                ++v7;
                break;
            case 0x90u:
                v7 += 2;
                break;
            case 0x91u:
                v7 += 2;
                break;
            case 0x92u:
                v7 += 2;
                break;
            case 0x93u:
                v7 += 2;
                break;
            case 0x94u:
                v7 += 2;
                break;
            case 0x95u:
                v7 += 2;
                break;
            case 0x96u:
                v7 += 2;
                break;
            case 0x97u:
                v7 += 2;
                break;
            case 0x98u:
                v7 += 2;
                break;
            case 0x99u:
                v7 += 2;
                break;
            case 0x9Au:
                v7 += 2;
                break;
            case 0x9Bu:
                v7 += 2;
                break;
            case 0x9Cu:
                v7 += 2;
                break;
            case 0x9Du:
                v7 += 2;
                break;
            case 0x9Eu:
                v7 += 2;
                break;
            case 0x9Fu:
                v7 += 2;
                break;
            case 0xA0u:
                v7 += 2;
                break;
            case 0xA1u:
                v7 += 2;
                break;
            case 0xA2u:
                v7 += 2;
                break;
            case 0xA3u:
                v7 += 2;
                break;
            case 0xA4u:
                v7 += 2;
                break;
            case 0xA5u:
                v7 += 2;
                break;
            case 0xA6u:
                v7 += 2;
                break;
            case 0xA7u:
                v7 += 2;
                break;
            case 0xA8u:
                v7 += 2;
                break;
            case 0xA9u:
                v7 += 2;
                break;
            case 0xAAu:
                v7 += 2;
                break;
            case 0xABu:
                v7 += 2;
                break;
            case 0xACu:
                v7 += 2;
                break;
            case 0xADu:
                v7 += 2;
                break;
            case 0xAEu:
                v7 += 2;
                break;
            case 0xAFu:
                v7 += 2;
                break;
            case 0xB0u:
                ++v7;
                break;
            case 0xB1u:
                ++v7;
                break;
            case 0xB2u:
                ++v7;
                break;
            case 0xB3u:
                ++v7;
                break;
            case 0xB4u:
                ++v7;
                break;
            case 0xB5u:
                ++v7;
                break;
            case 0xB6u:
                ++v7;
                break;
            case 0xB7u:
                ++v7;
                break;
            case 0xB8u:
                ++v7;
                break;
            case 0xB9u:
                ++v7;
                break;
            case 0xBAu:
                ++v7;
                break;
            case 0xBBu:
                ++v7;
                break;
            case 0xBCu:
                ++v7;
                break;
            case 0xBDu:
                ++v7;
                break;
            case 0xBEu:
                ++v7;
                break;
            case 0xBFu:
                ++v7;
                break;
            case 0xC0u:
                ++v7;
                break;
            case 0xC1u:
                ++v7;
                break;
            case 0xC2u:
                ++v7;
                break;
            case 0xC3u:
                ++v7;
                break;
            case 0xC4u:
                ++v7;
                break;
            case 0xC5u:
                ++v7;
                break;
            case 0xC6u:
                ++v7;
                break;
            case 0xC7u:
                ++v7;
                break;
            case 0xC8u:
                ++v7;
                break;
            case 0xC9u:
                ++v7;
                break;
            case 0xCAu:
                ++v7;
                break;
            case 0xCBu:
                ++v7;
                break;
            case 0xCCu:
                ++v7;
                break;
            case 0xCDu:
                ++v7;
                break;
            case 0xCEu:
                ++v7;
                break;
            case 0xCFu:
                ++v7;
                break;
            case 0xD0u:
                v7 += 2;
                break;
            case 0xD1u:
                v7 += 2;
                break;
            case 0xD2u:
                v7 += 2;
                break;
            case 0xD3u:
                v7 += 2;
                break;
            case 0xD4u:
                v7 += 2;
                break;
            case 0xD5u:
                v7 += 2;
                break;
            case 0xD6u:
                v7 += 2;
                break;
            case 0xD7u:
                v7 += 2;
                break;
            case 0xD8u:
                v7 += 2;
                break;
            case 0xD9u:
                v7 += 2;
                break;
            case 0xDAu:
                v7 += 2;
                break;
            case 0xDBu:
                v7 += 2;
                break;
            case 0xDCu:
                v7 += 2;
                break;
            case 0xDDu:
                v7 += 2;
                break;
            case 0xDEu:
                v7 += 2;
                break;
            case 0xDFu:
                v7 += 2;
                break;
            case 0xE0u:
                v7 += 2;
                break;
            case 0xE1u:
                v7 += 2;
                break;
            case 0xE2u:
                v7 += 2;
                break;
            case 0xEEu:
                v7 += 3;
                break;
            case 0xEFu:
                v7 += 3;
                break;
            case 0xF0u:
                v7 += 3;
                break;
            case 0xF1u:
            case 0xF2u:
                v7 += 2;
                break;
            case 0xF3u:
                v7 += 2;
                break;
            case 0xF4u:
                v7 += 2;
                break;
            case 0xF5u:
                v7 += 2;
                break;
            case 0xF6u:
                v7 += 2;
                break;
            case 0xF7u:
                v7 += 2;
                break;
            case 0xFCu:
            case 0xFDu:
            case 0xFEu:
            case 0xFFu:
                ++v7;
                break;
            default:
                goto LABEL_228;
            }
        }

        
        
    }

    //打印从类方法中提取的特征码
    std::printf("\n[*]类方法中提取的操作码数量: 0x%x\n\n", opcode_number);
    for (size_t i = 0; i < opcode_number; i++)
    {
        if (i != 0 && i % 16 == 0)
            std::printf("\n");
        if (i>=only_op.size())
        {
            break;
        }
        if (only_op[i] < 0x10)
        {
            std::printf("0%x ", only_op[i]);
            continue;
        }
        std::printf("%x ", only_op[i]);
    };
    opcodeMD5Size = str_size + 3 * opcode_number;
    std::printf("\n[*]字符串总长度: 0x%x\n\n", str_size);
    std::printf("[*] Opcode MD5:  opcode feature number(字符串总长度 + 3 * 方法中提取的opcode数量) = 0x%x\n\n", opcodeMD5Size);
    


    featureBlckLen = 2 * string_number + str_size + opcode_number;
    std::printf("[*] Opcode Similarity feature number(字符串总长度 + 2*字符串条数 + 提取的操作码数量) = 0x%x\n\n", featureBlckLen);
    for (size_t i = 0; i < (2*string_number + str_size + opcode_number); i++)
    {
        if (i != 0 && i % 16 == 0)
            std::printf("\n");
        if (i >= ops.size())
        {
            std::printf("00 ");
            ops.push_back('\x0');
            continue;
        }
        if (ops[i] < 0x10)
        {
            std::printf("0%x ", ops[i]);
            continue;

        }
        std::printf("%x ", ops[i]);
    }


    std::printf("\n");
    
    
    return allOpcode;

}


//void printSymbolByCrcMD5(parser apk_parser, uint32_t crcvalue, std::string md5v)
//{
//    uint32_t class_size = apk_parser.class_data_list.size();
//    for (size_t i = 0; i < class_size; i++)
//    {
//        if (i < 855) {
//            continue;
//        }
//        if (apk_parser.class_data_list[i].class_data.virtual_methods_size != 0 ||
//            apk_parser.class_data_list[i].class_data.direct_methods_size != 0) {
//            //travel direct_methods
//            for (size_t j = 0; j < apk_parser.class_data_list[i].class_data.direct_methods_size; j++)
//            {
//                uint32_t codeOff = apk_parser.class_data_list[i].class_data.directmethods_list[j].code_off;
//                if (codeOff == 0)
//                {
//                    //std::printf("[%d][%d]\tDirectMethod code offset == 0\n", i, j);
//                    continue;
//                }
//                char* codeptr = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns;
//                uint32_t codeSize = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns_size * 2;
//                if (codeSize == 0) {
//                    //std::printf("[%d][%d]\tDirectMethod code size == 0\n", i, j);
//                    continue;
//                }
//                char* class_name = apk_parser.get_classname_by_id(i);
//                uint32_t methodNameId = apk_parser.class_data_list[i].class_data.directmethods_list[j].method_idx;
//                if (j != 0) {
//                    for (size_t preindex = 0; preindex < j; preindex++)
//                    {
//                        methodNameId += apk_parser.class_data_list[i].class_data.directmethods_list[preindex].method_idx;
//                    }
//
//                }
//                char* methodName = apk_parser.get_string_by_id(apk_parser.get_method_by_id(methodNameId).name_idx);
//                std::printf("[D][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
//                if (i == 1264) {
//                    std::printf("ERROR\n");
//                }
//
//                vector<oneOpcode> onlyCode = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
//                char* onlyCodePtr = (char*)malloc(onlyCode.size());
//                for (size_t codeId = 0; codeId < onlyCode.size(); codeId++)
//                {
//                    onlyCodePtr[codeId] = onlyCode[codeId];
//                }
//
//                MD5 md5 = MD5::MD5();
//                md5.update(onlyCodePtr, onlyCode.size());
//                md5.finalize();
//                std::string md5Value = md5.hexdigest();
//
//                std::cout << "\tMD5 = " << md5Value << "\n";
//
//                if (!strcmp(strupr((char*)md5Value.c_str()), strupr((char*)md5v.c_str())))
//                {
//                    std::printf("Found it -> %s\n\n\n", md5v.c_str());
//                    exit(0);
//                }
//
//                uint32_t crc = crc32_bitwise(onlyCodePtr, onlyCode.size());
//                std::printf("\tCRC32 = %X\n\n\n", crc);
//
//
//                //if (crc == crcvalue)
//                //{
//                //    std::printf("Found it -> %x\n", crcvalue);
//                //    exit(0);
//                //}
//
//            }
//            //travel virutal methods
//            for (size_t j = 0; j < apk_parser.class_data_list[i].class_data.virtual_methods_size; j++)
//            {
//                uint32_t codeOff = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code_off;
//                if (codeOff == 0)
//                {
//                    //std::printf("[%d][%d]\tVirtual Method code offset == 0\n", i, j);
//                    continue;
//                }
//                char* codeptr = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns;
//                uint32_t codeSize = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns_size * 2;
//                if (codeSize == 0) {
//                    //std::printf("[%d][%d]\tVirtual Method  code size == 0\n", i, j);
//                    continue;
//                }
//                char* class_name = apk_parser.get_classname_by_id(i);
//                uint32_t methodNameId = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].method_idx;
//                if (j != 0) {
//                    for (size_t preindex = 0; preindex < j; preindex++)
//                    {
//                        methodNameId += apk_parser.class_data_list[i].class_data.virtualmethods_list[preindex].method_idx;
//                    }
//
//                }
//                char* methodName = apk_parser.get_string_by_id(apk_parser.get_method_by_id(methodNameId).name_idx);
//                std::printf("[V][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
//                if (i == 134 && j == 15)
//                {
//                    std::printf("ERROR\n");
//                }
//                vector<func_30B> onlyCode = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
//                char* onlyCodePtr = (char*)malloc(onlyCode.size());
//                for (size_t codeId = 0; codeId < onlyCode.size(); codeId++)
//                {
//                    onlyCodePtr[codeId] = onlyCode[codeId];
//                }
//
//                MD5 md5 = MD5::MD5();
//                md5.update(onlyCodePtr, onlyCode.size());
//                md5.finalize();
//                std::string md5Value = md5.hexdigest();
//                std::cout << "\tMD5 = " << md5Value << "\n";
//
//                if (!strcmp(strupr((char*)md5Value.c_str()), strupr((char*)md5v.c_str())))
//                {
//                    std::printf("Found it -> %s\n", md5v.c_str());
//                    exit(0);
//                }
//
//                uint32_t crc = crc32_bitwise(onlyCodePtr, onlyCode.size());
//                std::printf("\tCRC32 = %X\n\n\n", crc);
//
//                //if (crc == crcvalue)
//                //{
//                //    std::printf("Found it -> %x\n", crcvalue);
//                //    exit(0);
//                //}
//            }
//        }
//        else {
//            std::printf("[%d]\t 0 Methods\n", i);
//        }
//
//    }
//}


/// <summary>
/// 遍历每个类方法提取opcde，以及对应字符串构成的特征块，获取MD5列表，将MD5列表转成一个16字节的值，和参数比对找到命中参数"opBitSize"的类方法符号。
/// </summary>
/// <param name="allOpcode">类方法的opcode结构体列表，包含opcode、字符串地址(如果存在)</param>
/// <param name="opBitSize">安天检出病毒的HASH值。</param>
void opstrToSimiValue(vector<oneOpcode> allOpcode, char* opBitSize)
{
    //opcode+str 转成 MD5列表
    //func_440 解析字节码，构造opcode+str的特征块
    char* featureBlckPtr = (char*)malloc(featureBlckLen);
    for (size_t i = 0; i < featureBlckLen; i++)
    {
        featureBlckPtr[i] = ops[i];
    }

    struct oneOpcodeBlck
    {
        char* opcodeBlckPtr;
        uint32_t opSize;
    };
    uint32_t id = 0;
    map<uint32_t, vector<uint8_t>> orgin_data;
    vector<oneOpcodeBlck> allOpBlk;
    char* s;
    uint32_t sLen = 0;
    uint32_t otherOpSize = 0;
    char* v3 = featureBlckPtr;
    for (size_t i = 0; i < allOpcode.size(); i++)
    {
        s = allOpcode[i].stringAddr;
        if (s)
        {
            sLen = strlen(s) + 3;
        }    
        else
        {
            sLen = 1;
        }
        otherOpSize += sLen;
        if (sLen > 1) 
        {
            oneOpcodeBlck one = {0};
            one.opcodeBlckPtr = v3;
            one.opSize = otherOpSize;
            v3 += otherOpSize;
            otherOpSize = 0;
            allOpBlk.push_back(one);
        }
    }
    if (otherOpSize)
    {
        oneOpcodeBlck one = { 0 };
        one.opcodeBlckPtr = v3;
        one.opSize = otherOpSize;
        allOpBlk.push_back(one);
    }

    map<uint32_t, uint8_t> size_map;
    for (size_t l = 0; l < orgin_data.size(); l++)
    {
        size_map[l] = orgin_data[l].size();
    }

    vector<string> md5List;
    for (size_t i = 0; i < allOpBlk.size(); i++)
    {
        MD5 md5Obj = MD5::MD5();
        md5Obj.update(allOpBlk[i].opcodeBlckPtr, allOpBlk[i].opSize);
        md5Obj.finalize();

        bool uniq = true;
        for (size_t i = 0; i < md5List.size(); i++)
        {
            if (!strcmp(md5List[i].c_str(), md5Obj.hexdigest().c_str()))
            {
                uniq = false;
                break;
            }
        }
        if (!uniq) continue;
        md5List.push_back(md5Obj.hexdigest());
        std::printf("%s\n", md5Obj.hexdigest().c_str());
    }

    //取MD5列表中每个MD5值取每位0和1数量得到一个128位长度得值和病毒库特征中得128位值进行相似性计算
    char* a2 = (char*)malloc(16);
    memset(a2, 0, 16);
    uint8_t v14 = 0;
    int v7[128] = { 0 };
    int v5 = 0;
    int v10 = 1;
    char v15 = 0;
    for (size_t i = 0; i < md5List.size(); i++)
    {
        char ptr[16] = { 0 };
        for (size_t j = 0; j < 16; j++)
        {
            int hex = stoi(md5List[i].substr(j * 2, 2), 0, 16);

            ptr[j] = (char)hex;
        }

        for (size_t j = 0; j <= 127; ++j)
        {
            v14 = 1 << (j & 7);
            if (v14 & *((uint8_t*)ptr + (j >> 3)))
                v5 = v10 + v7[j];
            else
                v5 = v7[j] - v10;
            v7[j] = v5;
        }

    }
    for (int j = 0; j <= 127; ++j)
    {
        if (v7[j] > 0)
        {
            v15 = 1;
            *(int8_t*)(a2 + (j >> 3)) += 1 << (j & 7);
        }
    }

    scanMethodSize++;
    std::printf("\nOpcode and String's bit size of Method is:\t");
    for (size_t i = 0; i < 16; i++)
    {
        std::printf("%02x", (unsigned char)a2[i]);
    }
    std::printf("\n\n");

    if (!strncmp(opBitSize, (char*)a2, 16))
    {
        std::printf("Scan total %d methods then ,found it\n", scanMethodSize);
        //exit(0);
    }

    //安天特征,可以在 func_537 中下断点，获取相似特征。
    char virus_feature[] = { 0x95, 0x48, 0x9b, 0x33, 0x2c, 0x24, 0xbd, 0xa7, 0xe3, 0x89, 0x08, 0xa0, 0xb8, 0xfa, 0x0f, 0xdc };
    uint32_t* a1 = (uint32_t*)virus_feature;

    //char a3[] = {  0x84, 0x48, 0x8B, 0x32, 0x2C, 0x24, 0xBD, 0xA7, 0xE3, 0x2B, 0x48, 0xA0, 0xB8, 0xFA, 0x0F, 0xFC };
    //a2 = a3;

    uint8_t Gould_Sequence[] = {
        0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
        1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
        1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
        1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
        3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
        1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
        3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
        2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
        3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
        3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
        4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
    };
    
    int v4;
    uint32_t* v6;
    uint32_t* v8;
    int* v9;
    int simiValue = 0;

    v6 = a1;
    v8 = (uint32_t*)a2;
    v4 = *a1 ^ *(uint32_t*)a2;
    v9 = &v4;
    v5 = 0;
    v5 += Gould_Sequence[(uint8_t)v4];
    v5 += Gould_Sequence[(uint8_t)(v4 >> 8)];
    v5 += Gould_Sequence[(uint8_t)(v4 >> 16)];
    v5 += Gould_Sequence[(uint8_t)(v4 >> 24)];
    if ((int)v5 <= 19)
    {
        v4 = v6[1] ^ v8[1];
        v9 = &v4;
        v5 += Gould_Sequence[(uint8_t)v4];
        v5 += Gould_Sequence[(uint8_t)(v4 >> 8)];
        v5 += Gould_Sequence[(uint8_t)(v4 >> 16)];
        v5 += Gould_Sequence[(uint8_t)(v4 >> 24)];
        if ((int)v5 <= 19)
        {
            v4 = v6[2] ^ v8[2];
            v9 = &v4;
            v5 += Gould_Sequence[(uint8_t)v4];
            v5 += Gould_Sequence[(uint8_t)(v4 >> 8)];
            v5 += Gould_Sequence[(uint8_t)(v4 >> 16)];
            v5 += Gould_Sequence[(uint8_t)(v4 >> 24)];
            if ((int)v5 <= 19)
            {
                v4 = v6[3] ^ v8[3];
                v9 = &v4;
                v5 += Gould_Sequence[(uint8_t)v4];
                v5 += Gould_Sequence[(uint8_t)(v4 >> 8)];
                v5 += Gould_Sequence[(uint8_t)(v4 >> 16)];
                v5 += Gould_Sequence[(uint8_t)(v4 >> 24)];
            }
        }
    }
    simiValue = v5;
    std::printf("\nSimilarity Value is: 0x%X\n\n", simiValue);

    if (simiValue == 9)
    {
        std::printf("similar value is 9\n");
        exit(0);
    }


}


void printOpSimiValue(parser apk_parser, char* opBitSize)
{
    //遍历每个类方法的opcode
    uint32_t class_size = apk_parser.class_data_list.size();
    for (size_t i = 0; i < class_size; i++)
    {
        ops.clear();
        featureBlckLen = 0;

        if (apk_parser.class_data_list[i].class_data.virtual_methods_size != 0 ||
            apk_parser.class_data_list[i].class_data.direct_methods_size != 0) {
            //travel direct_methods
            for (size_t j = 0; j < apk_parser.class_data_list[i].class_data.direct_methods_size; j++)
            {
                uint32_t codeOff = apk_parser.class_data_list[i].class_data.directmethods_list[j].code_off;
                if (codeOff == 0)
                {
                    //std::printf("[%d][%d]\tDirectMethod code offset == 0\n", i, j);
                    continue;
                }
                char* codeptr = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns;
                uint32_t codeSize = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns_size * 2;
                if (codeSize == 0) {
                    //std::printf("[%d][%d]\tDirectMethod code size == 0\n", i, j);
                    continue;
                }
                char* class_name = apk_parser.get_classname_by_id(i);
                uint32_t methodNameId = apk_parser.class_data_list[i].class_data.directmethods_list[j].method_idx;
                if (j != 0) {
                    for (size_t preindex = 0; preindex < j; preindex++)
                    {
                        methodNameId += apk_parser.class_data_list[i].class_data.directmethods_list[preindex].method_idx;
                    }

                }
                char* methodName = apk_parser.get_string_by_id(apk_parser.get_method_by_id(methodNameId).name_idx);
                std::printf("\n[D][%d][%d]\tSymbol: %s -> %s\n[opcodeSize=0x%x]\n", i, j, class_name, methodName, codeSize);

                if (!strcmp(class_name, "Lcom/atxkj/sdm/a/c;"))
                {
                    std::printf("");
                }

                vector<oneOpcode> opcodeAndStr = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
                if (codeSize <0x17)
                {
                    continue;
                }

                /*char* onlyCodePtr = (char*)malloc(opcodeAndStr.size());
                for (size_t codeId = 0; codeId < opcodeAndStr.size(); codeId++)
                {
                    onlyCodePtr[codeId] = opcodeAndStr[codeId];
                }*/


                opstrToSimiValue(opcodeAndStr, opBitSize);

            }
            //travel virutal methods
            for (size_t j = 0; j < apk_parser.class_data_list[i].class_data.virtual_methods_size; j++)
            {
                uint32_t codeOff = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code_off;
                if (codeOff == 0)
                {
                    //std::printf("[%d][%d]\tVirtual Method code offset == 0\n", i, j);
                    continue;
                }
                char* codeptr = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns;
                uint32_t codeSize = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns_size * 2;
                if (codeSize == 0) {
                    //std::printf("[%d][%d]\tVirtual Method  code size == 0\n", i, j);
                    continue;
                }
                char* class_name = apk_parser.get_classname_by_id(i);
                uint32_t methodNameId = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].method_idx;
                if (j != 0) {
                    for (size_t preindex = 0; preindex < j; preindex++)
                    {
                        methodNameId += apk_parser.class_data_list[i].class_data.virtualmethods_list[preindex].method_idx;
                    }

                }
                char* methodName = apk_parser.get_string_by_id(apk_parser.get_method_by_id(methodNameId).name_idx);
                std::printf("\n[V][%d][%d]\tSymbol: %s -> %s\n[opcodeSize=0x%x]\n", i, j, class_name, methodName, codeSize);
                if (i == 2 && j == 3)
                {
                    std::printf("ERROR\n");
                }
                vector<oneOpcode> opcodeAndStr = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
                char* onlyCodePtr = (char*)malloc(opcodeAndStr.size());
                if (codeSize < 0x17)
                {
                    continue;
                }
                /*for (size_t codeId = 0; codeId < opcodeAndStr.size(); codeId++)
                {
                    onlyCodePtr[codeId] = opcodeAndStr[codeId];
                }*/

                opstrToSimiValue(opcodeAndStr, opBitSize);
            }
        }
        else {
            std::printf("[%d]\t 0 Methods\n", i);
        }
    }
}


void deleteSubStr(string& str, string& substr)
{
    int flag = 0, m = 0;
    uint32_t subSize = substr.size();
    while (flag == 0)
    {
        m = str.find(substr);
        if (m < 0)
        {
            flag = 1;
        }
        else 
        {
            str.erase(m, subSize);
        }
    }
}


void searchJDataInDex(parser apk_parser)
{
    Json::Value root;
    Json::Reader reader;
    ifstream  fin;


    fin.open("d:\\Tools\\Company\\\OWL-Android\\\samples\\Trojan.Android.GSmsSend.A.json", ios::in);
    if (!reader.parse(fin, root))
    {
        std::printf("Parser Json file Failed.");
        exit(0);
    }

    //遍历多模特征的每个数组
    for (unsigned int i = 0; i < root["scan_method"][0]["pattern"].size(); i++)
    {
        float score = 0.0;
        uint32_t featSize = root["scan_method"][0]["pattern"][i].size();
        //遍历数组内的每个字符串
        for (uint32_t j = 0; j < root["scan_method"][0]["pattern"][i].size(); j++)
        {
            string s =  root["scan_method"][0]["pattern"][i][j].asString();
            string c1 = "*";
            string c2 = "->";
            deleteSubStr(s, c1);
            char* sFeaturePtr = (char*)s.c_str();
            //如果字符串包含“->”，则其类名和方法名都在STRINTG段找到才算这条规则命中。
            if (strstr(sFeaturePtr, c2.c_str()))
            {
                int hit = 0;
                char* p = strtok(sFeaturePtr, c2.c_str());
                //遍历DEX STRING段
                for (size_t k = 0; k < apk_parser.string_list.size(); k++)
                {
                    char* cStr = (char*)apk_parser.string_list[k];
                    if (strlen(cStr) != 0 && strstr(cStr, p))
                    {
                        hit++;
                        break;
                    }
                }
                p = strtok(NULL, c2.c_str());
                if (p)
                {
                    //遍历DEX STRING段
                    for (size_t k = 0; k < apk_parser.string_list.size(); k++)
                    {
                        char* cStr = (char*)apk_parser.string_list[k];
                        if (strlen(cStr) != 0 && strstr(cStr, p))
                        {
                            hit++;
                            break;
                        }
                    }
                }
                else
                {
                    hit++;
                }
                
                if (hit == 2)
                {
                    score++;
                }
            }
            else
            {
                //遍历DEX STRING段
                for (size_t k = 0; k < apk_parser.string_list.size(); k++)
                {
                    char* cStr = (char*)apk_parser.string_list[k];
                    if (strlen(cStr) != 0 && strstr(cStr, sFeaturePtr))
                    {
                        score++;
                        break;
                    }
                }
            }
            
            if (score / featSize >= 0.575)
            {
                std::printf("Found it\t->\t%s\n", s.c_str());
                exit(0);
            }
            
        }

        
        
    }


    fin.close();
}


int main()
{
	
	
	const char* fp = "d:\\Tools\\Company\\OWL-Android\\samples\\classes.dex";
    //const char* fp = "d:\\Android\\sample\\classes.dex";
    parser apk_parser(fp);

    //遍历每个类中的每个方法，检索出特定CRC值对应的类方法路径

    uint32_t crcvalue = 0xD579505A;
    std::string md5v = "4D5EE4C6A8E34004FED6B291736B5F2B";
    //printSymbolByCrcMD5(apk_parser, crcvalue, md5v);

    char opBitSize[] = { 0x1D, 0x5A, 0x02, 0x66, 0xB1, 0xDE, 0x07, 0x64, 0xB0, 0xC7, 0x2B, 0x2B, 0xEE, 0xD9, 0xA1, 0x55 };

    printOpSimiValue(apk_parser, opBitSize);

    //searchJDataInDex(apk_parser);
    std::printf("\n total scan %d methods\n", scanMethodSize);

    return 0;
}