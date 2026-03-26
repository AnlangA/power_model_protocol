/**
 * @file module_common.c
 * @brief 电源模块公共辅助函数实现
 * @details 实现公共的字节序转换等辅助函数
 *
 * @version 1.0
 */

#include "module_common.h"
#include <stddef.h>

/**
 * @brief 字节序转换函数（Big Endian -> Little Endian）
 * @param src_data 源数据指针
 * @param dst_data 目标数据指针
 * @param bytes 字节数
 * @note 将Big Endian格式数据转换为Little Endian格式
 */
void module_convert_endianness(const uint8_t *src_data, uint8_t *dst_data, size_t bytes)
{
    if (src_data == NULL || dst_data == NULL || bytes == 0)
    {
        return;
    }

    for (size_t i = 0; i < bytes; i++)
    {
        dst_data[i] = src_data[bytes - 1 - i];
    }
}
