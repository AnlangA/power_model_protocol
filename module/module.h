/**
 * @file module.h
 * @brief 模块管理头文件
 * @details 定义模块数据结构和接口函数
 *
 * @version 1.0
 */

#pragma once
#include "stdint.h"
#include "stdbool.h"
#include "module_context.h"

/**
 * @brief 模块数量信息结构体
 */
typedef struct module_num_info_st
{
    uint32_t module_num;  ///< 模块总数
    uint32_t group_num;   ///< 组总数
} module_num_info_t;

extern module_num_info_t module_num_info;

// ==================== 宏定义 ====================

#define MODULE_NUM (module_num_info.module_num)       ///< 模块数量宏定义
#define GROUP_MODULE_NUM (module_num_info.group_num)   ///< 组数量宏定义

// ==================== 函数接口 ====================

void module_init(uint32_t module_num, uint32_t group_num, module_type_t module_type);
void module_data_query(void);
void module_data_process(void);
