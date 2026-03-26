/**
 * @file macro_acdc.h
 * @brief 电源模块协议公共宏定义
 * @details 定义字节序转换、数值限制等公共宏
 *
 * @version 1.0
 */

#pragma once

#include <stdint.h>
#include <string.h>

// ==================== 字节序转换宏 ====================

/**
 * @brief 字节序转换宏（Big Endian -> Little Endian）
 * @param src 源数据指针
 * @param dst 目标数据指针
 * @param bytes 字节数
 * @note 将Big Endian格式数据转换为Little Endian格式
 */
#define CONVERT_ENDIANNESS(src, dst, bytes)                      \
    do {                                                         \
        for (size_t _i = 0; _i < (bytes); _i++) {                \
            (dst)[_i] = (src)[(bytes) - 1 - _i];                 \
        }                                                        \
    } while (0)

// ==================== 模块常量定义 ====================

/** 模块离线超时时间（ms） */
#define MODULE_OFFLINE_TIME_MS       (5000u)

/** 模块最小输出电压阈值（mV）- 用于判断开机状态 */
#define MODULE_MIN_OUTPUT_VOLTAGE_MV (150000u)

/** 模块低压模式阈值（mV）- 高于此值为高压模式 */
#define MODULE_HV_THRESHOLD_MV       (500000u)

/** 模块电压读取间隔（ms） */
#define MODULE_VOLTAGE_QUERY_INTERVAL_MS   (200u)

/** 模块状态查询间隔（ms） */
#define MODULE_STATUS_QUERY_INTERVAL_MS    (1000u)

/** 模块组号查询间隔（ms） */
#define MODULE_GROUP_QUERY_INTERVAL_MS     (2000u)

/** 模块扩展数据查询间隔（ms） */
#define MODULE_EXT_QUERY_INTERVAL_MS       (1500u)

/** 模块在线检查间隔（ms） */
#define MODULE_ONLINE_CHECK_INTERVAL_MS    (1000u)

// ==================== 数值范围宏 ====================

/**
 * @brief 限制数值在指定范围内
 * @param val 待限制的值
 * @param min 最小值
 * @param max 最大值
 */
#define MODULE_CLAMP(val, min, max)                              \
    (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))

/**
 * @brief 检查数值是否在范围内
 * @param val 待检查的值
 * @param min 最小值
 * @param max 最大值
 */
#define MODULE_IN_RANGE(val, min, max)                           \
    (((val) >= (min)) && ((val) <= (max)))

// ==================== 位操作宏 ====================

/**
 * @brief 设置指定位
 * @param val 目标值
 * @param bit 位位置
 */
#define MODULE_SET_BIT(val, bit)    ((val) |= (1U << (bit)))

/**
 * @brief 清除指定位
 * @param val 目标值
 * @param bit 位位置
 */
#define MODULE_CLEAR_BIT(val, bit)  ((val) &= ~(1U << (bit)))

/**
 * @brief 检查指定位是否置位
 * @param val 目标值
 * @param bit 位位置
 * @return 1表示置位，0表示未置位
 */
#define MODULE_CHECK_BIT(val, bit)  (((val) >> (bit)) & 1U)

// ==================== 时间计算宏 ====================

/**
 * @brief 计算时间差（处理溢出）
 * @param current 当前时间
 * @param previous 之前的时间
 * @return 时间差
 */
#define MODULE_TIME_DIFF(current, previous)                      \
    (((current) >= (previous)) ?                                 \
     ((current) - (previous)) :                                  \
     ((UINT32_MAX - (previous)) + (current) + 1U))
