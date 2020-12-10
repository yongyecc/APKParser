#include "parser.h"
#include <iostream>
#include "md5.h"
#include "Crc32.h"



struct oneOpcode
{
    char* stringAddr;
    uint8_t opcode;
};

uint32_t featureBlckLen = 0;
vector<uint8_t> ops;

vector<oneOpcode> func_30B(uint16_t* a1, int a2, parser dex_parser)
{
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
    uint32_t str_size = 0;
    
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
            printf("");
        }
        printf("[%d] %x\n", ops.size(), v8);*/
        
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
                if (!strncmp(s, ".", 1) || !strncmp(s, "", 1))
                {
                    s = 0;            
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
                    //printf("%s\n", s);
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
    printf("\n[*]类方法中提取的操作码数量: 0x%x\n\n", opcode_number);
    for (size_t i = 0; i < opcode_number; i++)
    {
        if (i != 0 && i % 16 == 0)
            printf("\n");
        if (i>=only_op.size())
        {
            break;
        }
        if (only_op[i] < 0x10)
        {
            printf("0%x ", only_op[i]);
            continue;
        }
        printf("%x ", only_op[i]);
    };

    printf("\n[*]字符串总长度: 0x%x\n\n", str_size);
    printf("[*] Opcode MD5:  opcode feature number(字符串总长度 + 3 * 方法中提取的opcode数量) = 0x%x\n\n", str_size + 3*opcode_number);
    /*for (size_t i = 0; i < str_size + 3 * opcode_number; i++)
    {
        if (i != 0 && i % 16 == 0)
            printf("\n");
        if (i >= ops.size())
        {
            printf("00 ");
            ops.push_back('\x0');
            continue;
        }
        if (ops[i]<0x10)
        {
            printf("0%x ", ops[i]);
            continue;

        }
        printf("%x ", ops[i]);
    }*/
    featureBlckLen = 2 * string_number + str_size + opcode_number;
    printf("[*] Opcode Similarity feature number(字符串总长度 + 2*字符串条数 + 提取的操作码数量) = 0x%x\n\n", featureBlckLen);
    for (size_t i = 0; i < (2*string_number + str_size + opcode_number); i++)
    {
        if (i != 0 && i % 16 == 0)
            printf("\n");
        if (i >= ops.size())
        {
            printf("00 ");
            ops.push_back('\x0');
            continue;
        }
        if (ops[i] < 0x10)
        {
            printf("0%x ", ops[i]);
            continue;

        }
        printf("%x ", ops[i]);
    }


    printf("\n");
    
    
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
//                    //printf("[%d][%d]\tDirectMethod code offset == 0\n", i, j);
//                    continue;
//                }
//                char* codeptr = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns;
//                uint32_t codeSize = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns_size * 2;
//                if (codeSize == 0) {
//                    //printf("[%d][%d]\tDirectMethod code size == 0\n", i, j);
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
//                printf("[D][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
//                if (i == 1264) {
//                    printf("ERROR\n");
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
//                    printf("Found it -> %s\n\n\n", md5v.c_str());
//                    exit(0);
//                }
//
//                uint32_t crc = crc32_bitwise(onlyCodePtr, onlyCode.size());
//                printf("\tCRC32 = %X\n\n\n", crc);
//
//
//                //if (crc == crcvalue)
//                //{
//                //    printf("Found it -> %x\n", crcvalue);
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
//                    //printf("[%d][%d]\tVirtual Method code offset == 0\n", i, j);
//                    continue;
//                }
//                char* codeptr = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns;
//                uint32_t codeSize = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns_size * 2;
//                if (codeSize == 0) {
//                    //printf("[%d][%d]\tVirtual Method  code size == 0\n", i, j);
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
//                printf("[V][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
//                if (i == 134 && j == 15)
//                {
//                    printf("ERROR\n");
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
//                    printf("Found it -> %s\n", md5v.c_str());
//                    exit(0);
//                }
//
//                uint32_t crc = crc32_bitwise(onlyCodePtr, onlyCode.size());
//                printf("\tCRC32 = %X\n\n\n", crc);
//
//                //if (crc == crcvalue)
//                //{
//                //    printf("Found it -> %x\n", crcvalue);
//                //    exit(0);
//                //}
//            }
//        }
//        else {
//            printf("[%d]\t 0 Methods\n", i);
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

    vector<vector<uint8_t>> allOpcodeList;
    //opcode+str 转成 MD5列表
    uint32_t cursor = 0;
    
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

  /*  while (cursor < opcodeAndStr.size())
    {
        if (opcodeAndStr[cursor] == 0x1a)
        {
            if (opcodeAndStr[cursor + 1] != 0x00)
            {
                orgin_data[id].push_back(0x1a);
                cursor++;
                id++;
                continue;
            }
            orgin_data[id].push_back(0x1a);
            orgin_data[id].push_back(0x00);
            cursor += 2;
            while (opcodeAndStr[cursor] != 0x00)
            {
                orgin_data[id].push_back(opcodeAndStr[cursor]);
                cursor++;
            }
            orgin_data[id].push_back(0x00);
            cursor++;

            id++;
        }
        else if (opcodeAndStr[cursor] >= 0x6e && opcodeAndStr[cursor] <= 0x78)
        {
            orgin_data[id].push_back(opcodeAndStr[cursor]);
            if (opcodeAndStr[cursor + 1] != 0x00)
            {
                cursor++;
                continue;
            }
            orgin_data[id].push_back(0x00);
            cursor += 2;
            while (opcodeAndStr[cursor] != 0x00)
            {
                orgin_data[id].push_back(opcodeAndStr[cursor]);
                cursor++;
            }
            orgin_data[id].push_back(0x00);
            cursor++;
            id++;
        }
        else
        {
            orgin_data[id].push_back(opcodeAndStr[cursor]);
            cursor++;
        }
    }*/
    map<uint32_t, uint8_t> size_map;
    for (size_t l = 0; l < orgin_data.size(); l++)
    {
        size_map[l] = orgin_data[l].size();
    }

    //map<uint32_t, vector<uint8_t>> un_md5_data;
    //map<uint32_t, uint32_t> unMD5DataSizeMap;
    //cursor = 0;
    //for (size_t k = 0; k < orgin_data.size(); k++)
    //{
    //    if (orgin_data[k].size() == 1 && orgin_data[k][0] == 0x1a)
    //    {
    //        for (size_t cId = 0; cId < 3; cId++)
    //        {
    //            un_md5_data[k].push_back(opcodeAndStr[cursor + cId]);
    //        }
    //        unMD5DataSizeMap[k] = 3;
    //        cursor += 3;
    //    }
    //    else
    //    {
    //        uint32_t s_len = size_map[k];
    //        for (size_t cId = 0; cId < s_len; cId++)
    //        {
    //            if (cursor + cId >= opcodeAndStr.size())
    //            {
    //                un_md5_data[k].push_back(0x00);
    //                continue;
    //            }
    //            un_md5_data[k].push_back(opcodeAndStr[cursor + cId]);
    //        }
    //        unMD5DataSizeMap[k] = s_len;
    //        if (un_md5_data[k].size() != s_len)
    //        {
    //            //结尾处多余的0x00不计入MD5计算内
    //            //unMD5DataSizeMap[k] = un_md5_data[k].size();
    //            for (size_t x = 0; x < (s_len - un_md5_data[k].size()); x++)
    //            {
    //                un_md5_data[k].push_back(0x00);
    //            }
    //        }
    //        cursor += s_len;
    //    }
    //}

    /*vector<string> md5List;
    for (size_t k = 0; k < un_md5_data.size(); k++)
    {
        uint32_t dataSize = unMD5DataSizeMap[k];
        MD5 md5Obj = MD5::MD5();
        char* sPtr = (char*)malloc(dataSize);
        for (size_t cId = 0; cId < dataSize; cId++)
        {
            sPtr[cId] = un_md5_data[k][cId];
        }
        md5Obj.update(sPtr, dataSize);
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
        printf("%s\n", md5Obj.hexdigest().c_str());
    }*/

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
        printf("%s\n", md5Obj.hexdigest().c_str());
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

    printf("\nOpcode and String's bit size of Method is:\t");
    for (size_t i = 0; i < 16; i++)
    {
        printf("%02x", (unsigned char)a2[i]);
    }
    printf("\n\n");

    if (!strncmp(opBitSize, (char*)a2, 16))
    {
        printf("Found it\n");
        exit(0);
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
    printf("\nSimilarity Value is: 0x%X\n\n", simiValue);

    if (simiValue == 9)
    {
        printf("similar value is 9\n");
        exit(0);
    }


}

void printOpSimiValue(parser apk_parser, char* opBitSize)
{
    //遍历每个类方法的opcode
    uint32_t class_size = apk_parser.class_data_list.size();
    for (size_t i = 0; i < class_size; i++)
    {
        if (apk_parser.class_data_list[i].class_data.virtual_methods_size != 0 ||
            apk_parser.class_data_list[i].class_data.direct_methods_size != 0) {
            //travel direct_methods
            for (size_t j = 0; j < apk_parser.class_data_list[i].class_data.direct_methods_size; j++)
            {
                uint32_t codeOff = apk_parser.class_data_list[i].class_data.directmethods_list[j].code_off;
                if (codeOff == 0)
                {
                    //printf("[%d][%d]\tDirectMethod code offset == 0\n", i, j);
                    continue;
                }
                char* codeptr = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns;
                uint32_t codeSize = apk_parser.class_data_list[i].class_data.directmethods_list[j].code.insns_size * 2;
                if (codeSize == 0) {
                    //printf("[%d][%d]\tDirectMethod code size == 0\n", i, j);
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
                printf("\n[D][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);

                if (!strcmp(class_name, "Lcom/atxkj/sdm/a/c;"))
                {
                    printf("");
                }

                vector<oneOpcode> opcodeAndStr = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
                if (opcodeAndStr.size() <24)
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
                    //printf("[%d][%d]\tVirtual Method code offset == 0\n", i, j);
                    continue;
                }
                char* codeptr = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns;
                uint32_t codeSize = apk_parser.class_data_list[i].class_data.virtualmethods_list[j].code.insns_size * 2;
                if (codeSize == 0) {
                    //printf("[%d][%d]\tVirtual Method  code size == 0\n", i, j);
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
                printf("\n[V][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
                if (i == 134 && j == 15)
                {
                    printf("ERROR\n");
                }
                vector<oneOpcode> opcodeAndStr = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
                char* onlyCodePtr = (char*)malloc(opcodeAndStr.size());
                if (opcodeAndStr.size() < 24)
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
            printf("[%d]\t 0 Methods\n", i);
        }
    }
}



int main()
{
	
	
	const char* fp = "d:\\Tools\\Company\\OWL-Android\\samples\\classes.dex";
    //const char* fp = "d:\\Android\\sample\\classes.dex";
    parser apk_parser(fp);

    uint8_t opcode[] = {
        0x07, 0x70, 0x38, 0x09, 0x08, 0x00, 0x38, 0x05, 0x06, 0x00, 0x6E, 0x10, 0xE2, 0x06, 0x05, 0x00,
        0x0C, 0x07, 0x39, 0x0A, 0x04, 0x00, 0x38, 0x0B, 0x06, 0x00, 0x71, 0x40, 0x3D, 0x0F, 0x87, 0xBA,
        0x0C, 0x07, 0x38, 0x0C, 0x06, 0x00, 0x71, 0x10, 0x8A, 0x1D, 0x07, 0x00, 0x0C, 0x07, 0x12, 0x01,
        0x12, 0xF2, 0x6E, 0x10, 0x42, 0x3D, 0x06, 0x00, 0x0A, 0x03, 0x2C, 0x03, 0x23, 0x01, 0x00, 0x00,
        0x29, 0x00, 0x97, 0x00, 0x1A, 0x03, 0xDB, 0x05, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03,
        0x38, 0x03, 0xF8, 0xFF, 0x12, 0x22, 0x29, 0x00, 0x8C, 0x00, 0x1A, 0x03, 0xED, 0x08, 0x6E, 0x20,
        0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0xED, 0xFF, 0x12, 0x32, 0x29, 0x00, 0x81, 0x00,
        0x1A, 0x03, 0x92, 0x06, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0xE2, 0xFF,
        0x12, 0x62, 0x29, 0x00, 0x76, 0x00, 0x1A, 0x03, 0xE5, 0x04, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00,
        0x0A, 0x03, 0x38, 0x03, 0xD7, 0xFF, 0x13, 0x02, 0x09, 0x00, 0x29, 0x00, 0x6A, 0x00, 0x1A, 0x03,
        0x26, 0x0B, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0xCB, 0xFF, 0x12, 0x12,
        0x28, 0x5F, 0x1A, 0x03, 0xEB, 0x1B, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03,
        0xC1, 0xFF, 0x13, 0x02, 0x0D, 0x00, 0x28, 0x54, 0x1A, 0x03, 0x8B, 0x18, 0x6E, 0x20, 0x3D, 0x3D,
        0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0xB6, 0xFF, 0x12, 0x72, 0x28, 0x4A, 0x1A, 0x03, 0x2F, 0x1A,
        0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0xAC, 0xFF, 0x12, 0x42, 0x28, 0x40,
        0x1A, 0x03, 0x01, 0x1A, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0xA2, 0xFF,
        0x13, 0x02, 0x0C, 0x00, 0x28, 0x35, 0x1A, 0x03, 0x25, 0x0B, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00,
        0x0A, 0x03, 0x38, 0x03, 0x97, 0xFF, 0x12, 0x52, 0x28, 0x2B, 0x1A, 0x03, 0xA6, 0x1B, 0x6E, 0x20,
        0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0x8D, 0xFF, 0x12, 0x02, 0x28, 0x21, 0x1A, 0x03,
        0x01, 0x17, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0x83, 0xFF, 0x13, 0x02,
        0x0A, 0x00, 0x28, 0x16, 0x1A, 0x03, 0x95, 0x06, 0x6E, 0x20, 0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03,
        0x38, 0x03, 0x78, 0xFF, 0x13, 0x02, 0x08, 0x00, 0x28, 0x0B, 0x1A, 0x03, 0x8D, 0x18, 0x6E, 0x20,
        0x3D, 0x3D, 0x36, 0x00, 0x0A, 0x03, 0x38, 0x03, 0x6D, 0xFF, 0x13, 0x02, 0x0B, 0x00, 0x2B, 0x02,
        0xC3, 0x00, 0x00, 0x00, 0x6E, 0x40, 0x39, 0x0F, 0x74, 0x86, 0x0C, 0x01, 0x29, 0x00, 0x73, 0x00,
        0x6E, 0x30, 0x38, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06, 0x29, 0x00,
        0x6A, 0x00, 0x6E, 0x30, 0x35, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x61, 0x6E, 0x30, 0x34, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x59, 0x6E, 0x30, 0x32, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x51, 0x6E, 0x30, 0x2B, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x49, 0x6E, 0x30, 0x2E, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x41, 0x6E, 0x30, 0x33, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x39, 0x6E, 0x30, 0x2D, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x31, 0x6E, 0x30, 0x30, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x29, 0x6E, 0x30, 0x36, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x21, 0x6E, 0x30, 0x2F, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x19, 0x6E, 0x30, 0x2C, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x11, 0x6E, 0x30, 0x31, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x28, 0x09, 0x6E, 0x30, 0x37, 0x0F, 0x74, 0x08, 0x0C, 0x01, 0x70, 0x30, 0x3E, 0x0F, 0x14, 0x06,
        0x00, 0x00, 0x39, 0x01, 0x08, 0x00, 0x32, 0x70, 0x06, 0x00, 0x70, 0x40, 0x3C, 0x0F, 0x74, 0x86,
        0x0C, 0x01, 0x38, 0x01, 0x05, 0x00, 0x70, 0x30, 0x2A, 0x0F, 0x14, 0x08, 0x11, 0x01, 0x00, 0x00,
        0x00, 0x02, 0x0E, 0x00, 0x16, 0x31, 0xFB, 0x8B, 0x19, 0xEA, 0x3F, 0xA9, 0x53, 0x58, 0xC5, 0xAF,
        0x92, 0xF9, 0x08, 0xC8, 0x4D, 0xB4, 0x1F, 0xC8, 0x5B, 0x9A, 0xBF, 0xD8, 0xF9, 0x49, 0xBF, 0xEB,
        0xED, 0xA6, 0x46, 0x2E, 0xC6, 0x53, 0xA4, 0x2F, 0x80, 0x52, 0x1B, 0x43, 0xBA, 0xF9, 0x45, 0x54,
        0xC3, 0x07, 0x75, 0x5F, 0x77, 0x76, 0x57, 0x63, 0x52, 0x13, 0x47, 0x77, 0x90, 0x00, 0x00, 0x00,
        0x85, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00,
        0x5B, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
        0x32, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x05, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00,
        0x6A, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00,
        0x4A, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00,
        0x2A, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00,
        0x09, 0x00, 0x00, 0x00

    };

    //func_30B((uint16_t*)opcode, 0x334, apk_parser);

    //遍历每个类中的每个方法，检索出特定CRC值对应的类方法路径

    uint32_t crcvalue = 0xD579505A;
    std::string md5v = "4D5EE4C6A8E34004FED6B291736B5F2B";
    //printSymbolByCrcMD5(apk_parser, crcvalue, md5v);

    char opBitSize[] = { 0x84, 0x48, 0x8B, 0x32, 0x2C, 0x24, 0xBD, 0xA7, 0xE3, 0x2B, 0x48, 0xA0, 0xB8, 0xFA, 0x0F, 0xFC };

    printOpSimiValue(apk_parser, opBitSize);

	return 0;
}