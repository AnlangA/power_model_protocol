/**
 * @file module_common.h
 * @brief 电源模块公共辅助函数声明
 * @details 定义公共的字节序转换等辅助函数
 *
 * @version 1.0
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @brief 字节序转换函数（Big Endian -> Little Endian）
 * @param src_data 源数据指针
 * @param dst_data 目标数据指针
 * @param bytes 字节数
 * @note 将Big Endian格式数据转换为Little Endian格式
 */
void module_convert_endianness(const uint8_t *src_data, uint8_t *dst_data, size_t bytes);
