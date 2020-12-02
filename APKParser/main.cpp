#include "parser.h"
#include <iostream>
#include "md5.h"
#include "Crc32.h"


vector<uint8_t> func_30B(uint16_t* a1, int a2, parser dex_parser)
{
    //a1: 指令码指针。
    //a2: 指令码长度
    __int64(__fastcall * v6)(__int16*, __int64); // [rsp+8h] [rbp-F8h]
    uint16_t* v7; // [rsp+30h] [rbp-D0h]
    __int16 v8; // [rsp+4Ah] [rbp-B6h]
    __int64 v9; // [rsp+50h] [rbp-B0h]
    uint8_t v5;


    char* ret = NULL;
    uint32_t feature_size = 0;
    vector<uint8_t> ops;
    vector<uint8_t> only_op;

    v7 = a1;        
    v9 = 0;
    uint32_t opcode_number = 0;
    uint32_t str_size = 0;
LABEL_228:
    while (v7 < (uint16_t*)((char*)a1 + a2))
    {
        uint32_t ops_len = ops.size();
        v8 = *v7;
        v5 = v8;
        opcode_number += 1;

        if (ops.size() >= 60) {
            printf("");
        }
        printf("[%d] %x\n", ops.size(), v8);
        
        char* s = 0;
        if (v5 != 0x00)
        {

            ops.push_back(v5);
            only_op.push_back(v5);
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
                    for (size_t i = 0; i < strlen(s); i++)
                    {
                        ops.push_back(s[i]);
                    }
                    ops.push_back('\0');
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
                    for (size_t i = 0; i < strlen(s); i++)
                    {
                        ops.push_back(s[i]);
                    }
                    ops.push_back('\0');
                }
            }

        }

        
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
                return ops;
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
    //printf("[*]类方法中提取的操作码数量: 0x%x\n\n", opcode_number);
    //for (size_t i = 0; i < opcode_number; i++)
    //{
    //    if (i != 0 && i % 16 == 0)
    //        printf("\n");
    //    if (i>=only_op.size())
    //    {
    //        break;
    //    }
    //    if (only_op[i] < 0x10)
    //    {
    //        printf("0%x ", only_op[i]);
    //        continue;
    //    }
    //    printf("%x ", only_op[i]);
    //};

    printf("\n[*]字符串总长度: 0x%x\n\n", str_size);
    printf("[*]opcode feature number(字符串总长度 + 3 * 方法中提取的opcode数量) = 0x%x\n\n", str_size + 3*opcode_number);
    for (size_t i = 0; i < str_size + 3 * opcode_number; i++)
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
    }
    printf("\n");

    
    return ops;

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

    uint32_t class_size = apk_parser.class_data_list.size();
    for (size_t i = 0; i < class_size; i++)
    {
        if (i < 855) {
            continue;
        }
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
                printf("[D][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
                if (i == 1264) {
                    printf("ERROR\n");
                }
                
                vector<uint8_t> onlyCode = func_30B((uint16_t*)codeptr, codeSize, apk_parser);
                char* onlyCodePtr = (char*)malloc(onlyCode.size());
                for (size_t codeId = 0; codeId < onlyCode.size(); codeId++)
                {
                    onlyCodePtr[codeId] = onlyCode[codeId];
                }

                MD5 md5 = MD5::MD5();
                md5.update(onlyCodePtr, onlyCode.size());
                md5.finalize();
                std::string md5Value =  md5.hexdigest();

                std::cout << "\tMD5 = " << md5Value << "\n";

                if (!strcmp(strupr((char*)md5Value.c_str()), strupr((char*)md5v.c_str())))
                {
                    printf("Found it -> %s\n\n\n", md5v.c_str());
                    exit(0);
                }

                uint32_t crc = crc32_bitwise(onlyCodePtr, onlyCode.size());
                printf("\tCRC32 = %X\n\n\n", crc);

                
                //if (crc == crcvalue)
                //{
                //    printf("Found it -> %x\n", crcvalue);
                //    exit(0);
                //}

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
                printf("[V][%d][%d]\tSymbol: %s -> %s\n", i, j, class_name, methodName);
                if (i == 134 && j == 15)
                {
                    printf("ERROR\n");
                }
                vector<uint8_t> onlyCode =  func_30B((uint16_t*)codeptr, codeSize, apk_parser);
                char* onlyCodePtr = (char*)malloc(onlyCode.size());
                for (size_t codeId = 0; codeId < onlyCode.size(); codeId++)
                {
                    onlyCodePtr[codeId] = onlyCode[codeId];
                }

                MD5 md5 = MD5::MD5();
                md5.update(onlyCodePtr, onlyCode.size());
                md5.finalize();
                std::string md5Value = md5.hexdigest();
                std::cout << "\tMD5 = " << md5Value << "\n";
                
                if (!strcmp(strupr((char*)md5Value.c_str()), strupr((char*)md5v.c_str())))
                {
                    printf("Found it -> %s\n", md5v.c_str());
                    exit(0);
                }
                
                uint32_t crc = crc32_bitwise(onlyCodePtr, onlyCode.size());
                printf("\tCRC32 = %X\n\n\n", crc);

                //if (crc == crcvalue)
                //{
                //    printf("Found it -> %x\n", crcvalue);
                //    exit(0);
                //}
            }
        }
        else {
            printf("[%d]\t 0 Methods\n", i);
        }
    }
	return 0;
}