#pragma once
#include "stdbool.h"
#include "yfy_data_acdc.h"

// ========== 第一类：读取单个模块数据的函数 ==========
// 基本数据读取
bool yfy_get_module_voltage(uint8_t module_addr, float* voltage);
bool yfy_get_module_current(uint8_t module_addr, float* current);
bool yfy_get_module_group(uint8_t module_addr, uint8_t* group);
bool yfy_get_module_temp(uint8_t module_addr, int8_t* temp);

// 模块状态表2读取
bool yfy_get_module_limit_power(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_id_duplicate(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_severe_unbalanced(uint8_t module_addr, uint8_t* status);
bool yfy_get_three_phase_input_missing(uint8_t module_addr, uint8_t* status);
bool yfy_get_three_phase_input_unbalanced(uint8_t module_addr, uint8_t* status);
bool yfy_get_input_undervoltage(uint8_t module_addr, uint8_t* status);
bool yfy_get_input_overvoltage(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_pfc_fault(uint8_t module_addr, uint8_t* status);

// 模块状态表1读取
bool yfy_get_module_dc_side_off(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_fault(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_protection(uint8_t module_addr, uint8_t* status);
bool yfy_get_fan_fault(uint8_t module_addr, uint8_t* status);
bool yfy_get_over_temp(uint8_t module_addr, uint8_t* status);
bool yfy_get_output_overvoltage(uint8_t module_addr, uint8_t* status);
bool yfy_get_walk_in_enable(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_comm_interrupt(uint8_t module_addr, uint8_t* status);

// 模块状态表0读取
bool yfy_get_output_short_circuit(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_internal_comm_fault(uint8_t module_addr, uint8_t* status);
bool yfy_get_input_or_bus_abnormal(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_sleep(uint8_t module_addr, uint8_t* status);
bool yfy_get_module_discharge_abnormal(uint8_t module_addr, uint8_t* status);

// 交流输入电压读取
bool yfy_get_ac_input_voltage_ab(uint8_t module_addr, uint16_t* voltage);
bool yfy_get_ac_input_voltage_bc(uint8_t module_addr, uint16_t* voltage);
bool yfy_get_ac_input_voltage_ca(uint8_t module_addr, uint16_t* voltage);

// 最大最小值读取
bool yfy_get_max_voltage(uint8_t module_addr, uint16_t* voltage);
bool yfy_get_min_voltage(uint8_t module_addr, uint16_t* voltage);
bool yfy_get_max_current(uint8_t module_addr, uint16_t* current);
bool yfy_get_max_power(uint8_t module_addr, uint16_t* power);

// 其他参数读取
bool yfy_get_external_voltage(uint8_t module_addr, uint16_t* voltage);
bool yfy_get_max_output_current(uint8_t module_addr, uint16_t* current);
bool yfy_get_module_addr_mode(uint8_t module_addr, uint8_t* addr_mode);

// ========== 第二类：读取模块组数据的函数 ==========
bool yfy_get_group_voltage(uint8_t group_num, float* voltage);
bool yfy_get_group_current(uint8_t group_num, float* current);
bool yfy_get_group_module_num(uint8_t group_num, uint8_t* module_num);

// ========== 第三类：读取系统数据的函数 ==========
bool yfy_get_sys_voltage(float* voltage);
bool yfy_get_sys_current(float* current);
bool yfy_get_sys_module_num(uint8_t* module_num);

// ========== 发送读取命令的函数 ==========
void yfy_send_read_sys_output(void);
void yfy_send_read_sys_module_num(void);
void yfy_send_read_group_output(uint8_t module_addr);
void yfy_send_read_group_module_num(uint8_t module_addr);
void yfy_send_read_single_output(uint8_t module_addr);
void yfy_send_read_single_output_by_group(uint8_t group_num);
void yfy_send_read_single_info_1(uint8_t module_addr);
void yfy_send_read_single_info_1_by_group(uint8_t group_num);
void yfy_send_read_single_info_2(uint8_t module_addr);
void yfy_send_read_single_info_2_by_group(uint8_t group_num);
void yfy_send_read_single_info_3(uint8_t module_addr);
void yfy_send_read_single_info_3_by_group(uint8_t group_num);
void yfy_send_read_single_info_4(uint8_t module_addr);
void yfy_send_read_single_info_4_by_group(uint8_t group_num);
void yfy_send_read_single_info_5(uint8_t module_addr);
void yfy_send_read_single_info_5_by_group(uint8_t group_num);

// ========== 发送设置命令的函数 ==========
void yfy_send_write_sys_WalkIn(bool enable);
void yfy_send_write_WalkIn_by_group(uint8_t group_num, bool enable);
void yfy_send_write_single_WalkIn(uint8_t module_addr, bool enable);
void yfy_send_write_sys_green_led_blink(bool enable);
void yfy_send_write_green_led_blink_by_group(uint8_t group_num, bool enable);
void yfy_send_write_single_green_led_blink(uint8_t module_addr, bool enable);
void yfy_send_write_sys_group_num(uint8_t group_num);
void yfy_send_write_group_num_by_group(uint8_t group_num, uint8_t new_group_num);
void yfy_send_write_single_group_num(uint8_t module_addr, uint8_t group_num);
void yfy_send_write_sys_sleep(bool enable);
void yfy_send_write_sleep_by_group(uint8_t group_num, bool enable);
void yfy_send_write_single_sleep(uint8_t module_addr, bool enable);
void yfy_send_write_sys_work(bool enable);
void yfy_send_write_work_by_group(uint8_t group_num, bool enable);
void yfy_send_write_single_work(uint8_t module_addr, bool enable);
void yfy_send_write_sys_output_all(uint32_t volt, uint32_t current);
void yfy_send_write_output_all_by_group(uint8_t group_num, uint32_t volt, uint32_t current);
void yfy_send_write_sys_output(uint32_t volt, uint32_t current);
void yfy_send_write_output_by_group(uint8_t group_num, uint32_t volt, uint32_t current);
void yfy_send_write_single_output(uint8_t module_addr, uint32_t volt, uint32_t current);
void yfy_send_write_sys_addr_model(uint8_t model);
void yfy_send_write_addr_model_by_group(uint8_t group_num, uint8_t model);
void yfy_send_write_single_addr_model(uint8_t module_addr, uint8_t model);

bool yfy_module_online(uint8_t module_addr);
void yfy_module_check(void);
bool yfy_module_ok(void);