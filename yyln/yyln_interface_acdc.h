/**
 * @file yyln_interface_acdc.h
 * @brief 优优绿能模块接口层头文件
 * @details 定义优优绿能模块的对外接口函数，包括组控制、数据查询等功能
 *
 * @version 1.0
 */

#pragma once
#include "yyln_api_acdc.h"

// ==================== 模块组控制接口 ====================

/**
 * @brief 模块组开机接口
 * @param group 组号
 * @return true 成功, false 失败
 */
bool yyln_group_power_on(uint32_t group);

/**
 * @brief 模块组关机接口
 * @param group 组号
 * @return true 成功, false 失败
 */
bool yyln_group_power_off(uint32_t group);

/**
 * @brief 模块组设置电压电流接口
 * @param group 组号
 * @param voltage 电压(V)
 * @param current 电流(A)
 * @param module_numbers 模块数量
 * @param module_num_max 最大模块数量
 * @return true 成功, false 失败
 */
bool yyln_group_set_voltage_current(uint32_t group, float voltage, float current, uint32_t module_numbers, uint32_t module_num_max);

// ==================== 模块组数据查询接口 ====================

/**
 * @brief 模块组读取输出电压电流接口
 * @param group 组号
 * @param voltage 电压指针(V)
 * @param current 电流指针(A)
 * @param module_num_max 最大模块数量
 * @return true 成功, false 失败
 */
bool yyln_group_get_voltage_current(uint32_t group, float* voltage, float* current, uint32_t module_num_max);

/**
 * @brief 模块组读取状态map接口
 * @param group 组号
 * @param status_map 状态位图指针
 * @param module_num_max 最大模块数量
 * @return true 成功, false 失败
 */
bool yyln_group_get_status_map(uint32_t group, uint32_t* status_map, uint32_t module_num_max);

/**
 * @brief 获取组内模块个数接口
 * @param group 组号
 * @param module_number 模块数量指针
 * @param module_num_max 最大模块数量
 * @return true 成功, false 失败
 */
bool yyln_group_get_module_number(uint32_t group, uint32_t* module_number, uint32_t module_num_max);

/**
 * @brief 获取电源模块输入电压
 * @param module_addr 模块地址
 * @param voltage 电压指针(mV)
 * @param module_num_max 最大模块数量
 * @return true 成功, false 失败
 */
bool yyln_module_get_v_ab(uint32_t module_addr, uint32_t* voltage, uint32_t module_num_max);

/**
 * @brief 电源模块是否在线
 * @param module_addr 模块地址
 * @param module_num_max 最大模块数量
 * @return true 在线, false 离线
 */
bool yyln_module_is_online(uint32_t module_addr, uint32_t module_num_max);

/**
 * @brief 获取单模块温度
 * @param module_addr 模块地址
 * @param temperature 温度指针(°C)
 * @return true 成功, false 失败
 */
bool yyln_single_module_temp(uint32_t module_addr, float* temperature);