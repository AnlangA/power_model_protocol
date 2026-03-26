#pragma once
#include "stdbool.h"
#include "yyln_data_acdc.h"
#include <stdint.h>

// 写入命令接口
bool yyln_send_write_module_vout_reference(uint8_t module_addr, uint8_t group, uint32_t voltage);
bool yyln_send_write_module_iout_limit(uint8_t module_addr, uint8_t group, uint32_t current);
bool yyln_send_write_module_shutdown_dcdc(uint8_t module_addr, uint8_t group, uint32_t shutdown);
bool yyln_send_write_group_num(uint8_t module_addr, uint8_t new_group);
bool yyln_send_write_module_himode_lomode_selection(uint8_t module_addr, uint8_t group, uint32_t mode);

// 读取命令接口
bool yyln_send_read_vout(uint8_t module_addr);
bool yyln_send_read_vout_by_group(uint8_t group);
bool yyln_send_read_iout(uint8_t module_addr);
bool yyln_send_read_iout_by_group(uint8_t group);
bool yyln_send_read_vout_reference(uint8_t module_addr);
bool yyln_send_read_vout_reference_by_group(uint8_t group);
bool yyln_send_read_iout_limit(uint8_t module_addr);
bool yyln_send_read_iout_limit_by_group(uint8_t group);
bool yyln_send_read_group_num(uint8_t module_addr);
bool yyln_send_read_sn(uint8_t module_addr);
bool yyln_send_read_sn_by_group(uint8_t group);
bool yyln_send_read_module_status(uint8_t module_addr);
bool yyln_send_read_module_status_by_group(uint8_t group);
bool yyln_send_read_ab_voltage(uint8_t module_addr);
bool yyln_send_read_ab_voltage_by_group(uint8_t group);
bool yyln_send_read_bc_voltage(uint8_t module_addr);
bool yyln_send_read_bc_voltage_by_group(uint8_t group);
bool yyln_send_read_ca_voltage(uint8_t module_addr);
bool yyln_send_read_ca_voltage_by_group(uint8_t group);
bool yyln_send_read_air_intake_temperature(uint8_t module_addr);
bool yyln_send_read_air_intake_temperature_by_group(uint8_t group);
bool yyln_send_read_module_himode_lomode_set_selection(uint8_t module_addr);
bool yyln_send_read_module_himode_lomode_selection_set_by_group(uint8_t group);
bool yyln_send_read_module_himode_lomode_selection(uint8_t module_addr);
bool yyln_send_read_module_himode_lomode_selection_by_group(uint8_t group);
bool yyln_send_read_current_capability(uint8_t module_addr);
bool yyln_send_read_current_capability_by_group(uint8_t group);
bool yyln_send_read_current_and_capability(uint8_t module_addr);
bool yyln_send_read_current_and_capability_by_group(uint8_t group);
bool yyln_send_read_pfc_temperature(uint8_t module_addr);
bool yyln_send_read_pfc_temperature_by_group(uint8_t group);
bool yyln_send_read_dcdc_temperature(uint8_t module_addr);
bool yyln_send_read_dcdc_temperature_by_group(uint8_t group);

// 数据获取接口
bool yyln_get_module_vout(uint8_t module_addr, uint32_t* voltage);
bool yyln_get_module_iout(uint8_t module_addr, uint32_t* current);
bool yyln_get_module_v_set(uint8_t module_addr, uint32_t* voltage_set);
bool yyln_get_module_i_set(uint8_t module_addr, uint32_t* current_limit);
bool yyln_get_module_sn(uint8_t module_addr, uint32_t* serial_number);
bool yyln_get_module_ac_overVoltage(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_ac_underVoltage(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_ac_overVoltageClose(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_pfcBus_overVoltage(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_pfcBus_underVoltage(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_pfcBus_unbalance(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dc_overVoltage(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dc_overVoltageClose(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dc_underVoltage(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_fan_stop(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_fan_driverFaild(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_overTemple(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_underTempl(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_pfc_overTempleProtection(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_relay_faild(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dc_overTempleProtection(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dcdc_pfc_comFaild(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_pfc_faild(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dcdc_faile(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dcdc_noWork(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_outState(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_dc_voltageUnbalance(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_same_sn(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_bleeder_circuitFailure(uint8_t module_addr, uint8_t* status);
bool yyln_get_module_v_ab(uint8_t module_addr, uint32_t* voltage);
bool yyln_get_module_v_bc(uint8_t module_addr, uint32_t* voltage);
bool yyln_get_module_v_ca(uint8_t module_addr, uint32_t* voltage);
bool yyln_get_module_air_intake_temple(uint8_t module_addr, uint32_t* temperature);
bool yyln_get_module_module_group(uint8_t module_addr, uint32_t* group);
bool yyln_get_module_work_mode(uint8_t module_addr, uint32_t* work_mode);
bool yyln_get_module_trueHiLo_Status(uint8_t module_addr, uint32_t* work_mode);
bool yyln_get_module_module_max_curr(uint8_t module_addr, uint32_t* max_current);
bool yyln_get_module_iout1(uint8_t module_addr, uint32_t* current);
bool yyln_get_module_module_max_curr1(uint8_t module_addr, uint32_t* power_capability);
bool yyln_get_module_pfc_temp(uint8_t module_addr, uint32_t* temperature);
bool yyln_get_module_dcdc_temp(uint8_t module_addr, uint32_t* temperature);
bool yyln_get_module_status_map(uint8_t module_addr, uint32_t* status_map);

void yyln_module_check(void);
bool yyln_module_ok(void);
