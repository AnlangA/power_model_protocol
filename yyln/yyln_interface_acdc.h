#pragma once
#include "yyln_api_acdc.h"

// 模块组开机接口
bool yyln_group_power_on(uint32_t group);

// 模块组关机接口
bool yyln_group_power_off(uint32_t group);

// 模块组设置电压电流接口
bool yyln_group_set_voltage_current(uint32_t group, float voltage, float current, uint32_t module_numbers, uint32_t module_num_max);

// 模块组读取输出电压电流接口
bool yyln_group_get_voltage_current(uint32_t group, float* voltage, float* current, uint32_t module_num_max);

// 模块组读取状态map接口
bool yyln_group_get_status_map(uint32_t group, uint32_t* status_map, uint32_t module_num_max);

// 获取组内模块个数接口
bool yyln_group_get_module_number(uint32_t group, uint32_t* module_number, uint32_t module_num_max);

// 获取电源模块输入电压
bool yyln_module_get_v_ab(uint32_t module_addr, uint32_t* voltage, uint32_t module_num_max);

// 电源模块是否在线
bool yyln_module_is_online(uint32_t module_addr, uint32_t module_num_max);

bool yyln_single_module_temp(uint32_t module_addr, float* temperature);