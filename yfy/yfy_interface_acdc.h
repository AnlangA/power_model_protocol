#pragma once

#include "yfy_api_acdc.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief 开启指定分组的所有模块电源
 * @param group 分组号
 * @return true 成功, false 失败(分组号无效)
 */
bool yfy_group_power_on(uint32_t group);

/**
 * @brief 关闭指定分组的所有模块电源
 * @param group 分组号
 * @return true 成功, false 失败(分组号无效)
 */
bool yfy_group_power_off(uint32_t group);

/**
 * @brief 设置指定分组的输出电压和电流
 * @param group 分组号
 * @param volt 输出电压(V)
 * @param current 输出电流(A)
 * @param module_numbers 模块数量(未使用,模块内部自动处理)
 * @return true 成功, false 失败(分组号无效)
 */
bool yfy_group_set_voltage_current(uint32_t group, float volt, float current, uint32_t module_numbers, uint32_t module_num_max);

/**
 * @brief 获取指定分组的输出电压和电流
 * @param group 分组号
 * @param voltage 输出电压指针(V)
 * @param current 输出电流指针(A)
 * @return true 成功, false 失败
 */
bool yfy_group_get_voltage_current(uint32_t group, float* voltage, float* current, uint32_t module_num_max);

/**
 * @brief 获取指定分组的模块数量
 * @param group 分组号
 * @param module_number 模块数量指针
 * @param module_num_max 模块数量
 * @return true 成功, false 失败
 */
bool yfy_group_get_module_number(uint32_t group, uint32_t* module_number, uint32_t module_num_max);

/**
 * @brief 获取分组状态位图接口
 * @param group 分组号
 * @param status_map 状态位图指针
 * @param module_num_max 模块数量
 * @return true 成功, false 失败
 */
bool yfy_group_get_status_map(uint32_t group, uint32_t* status_map, uint32_t module_num_max);

/**
 * @brief 检查指定模块是否在线
 * @param module_addr 模块地址
 * @return true 在线, false 离线或地址无效
 */
bool yfy_module_is_online(uint32_t module_addr, uint32_t module_num_max);

/**
 * @brief 获取模块交流输入电压AB
 * @param module_addr 模块地址
 * @param voltage 电压指针
 * @param module_num_max 模块数量
 * @return true 成功, false 失败
 */
bool yfy_module_get_v_ab(uint32_t module_addr, uint32_t* voltage, uint32_t module_num_max);


bool yfy_single_module_temp(uint32_t module_addr, float* temperature);