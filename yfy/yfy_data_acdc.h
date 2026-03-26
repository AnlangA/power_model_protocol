#pragma once
#include "stdbool.h"
#include "stdint.h"

//电源模块数量
#define YFY_MODULE_NUM (32)
// 组号1~4
#define YFY_GROUP_NUM (32)
// 广播
#define MODULE_BROADCAST_ADDR 0x3f
// 设备号
#define DEVICE_ID 0x0A
// 组设备号
#define GROUP_DEVICE_ID 0x0B
// 监控地址
#define MONITOR_ADDR 0xF0



/**
 * @brief 32位数据组装宏
 * @param error_code 错误码 (3 bits, 0-7)
 * @param device_id 设备号 (4 bits, 0-15)
 * @param cmd 命令号 (6 bits, 0-63)
 * @param dest_addr 目的地址 (8 bits, 0-255)
 * @param src_addr 源地址 (8 bits, 0-255)
 * @return 组装后的32位数据
 * @note 数据格式：[28:26]错误码 [25:22]设备号 [21:16]命令号 [15:8]目的地址 [7:0]源地址
 */
#define YFY_SET_ID(error_code, device_id, cmd, dest_addr, src_addr)                                                                                            \
    ((uint32_t) (((error_code) & 0x07) << 26) | (uint32_t) (((device_id) & 0x0F) << 22) | (uint32_t) (((cmd) & 0x3F) << 16) |                                  \
     (uint32_t) (((dest_addr) & 0xFF) << 8) | (uint32_t) ((src_addr) & 0xFF))

/**
 * @brief 从32位数据中提取错误码
 * @param data 32位数据
 * @return 错误码 (3 bits)
 */
#define YFY_EXTRACT_ERROR_CODE(data) (((data) >> 26) & 0x07)

/**
 * @brief 从32位数据中提取设备号
 * @param data 32位数据
 * @return 设备号 (4 bits)
 */
#define YFY_EXTRACT_DEVICE_ID(data) (((data) >> 22) & 0x0F)

/**
 * @brief 从32位数据中提取命令号
 * @param data 32位数据
 * @return 命令号 (6 bits)
 */
#define YFY_EXTRACT_CMD(data) (((data) >> 16) & 0x3F)

/**
 * @brief 从32位数据中提取目的地址
 * @param data 32位数据
 * @return 目的地址 (8 bits)
 */
#define YFY_EXTRACT_DEST_ADDR(data) (((data) >> 8) & 0xFF)

/**
 * @brief 从32位数据中提取源地址
 * @param data 32位数据
 * @return 源地址 (8 bits)
 */
#define YFY_EXTRACT_SRC_ADDR(data) ((data) & 0xFF)

typedef struct yfy_module_data_t
{
    float voltage[YFY_MODULE_NUM]; // 模块电压
    float current[YFY_MODULE_NUM]; // 模块电流
    uint8_t group[YFY_MODULE_NUM]; // 模块组号
    int8_t temp[YFY_MODULE_NUM];   // 模块温度

    // 模块状态表2
    uint8_t module_limit_power[YFY_MODULE_NUM];           // 限功率
    uint8_t module_id_duplicate[YFY_MODULE_NUM];          // 模块ID重复
    uint8_t module_severe_unbalanced[YFY_MODULE_NUM];     // 模块严重不均流
    uint8_t three_phase_input_missing[YFY_MODULE_NUM];    // 三相输入缺相告警
    uint8_t three_phase_input_unbalanced[YFY_MODULE_NUM]; // 三相输入不平衡告警
    uint8_t input_undervoltage[YFY_MODULE_NUM];           // 输入欠压告警
    uint8_t input_overvoltage[YFY_MODULE_NUM];            // 输入过压告警
    uint8_t module_pfc_fault[YFY_MODULE_NUM];             // 模块PFC侧处于关机状态

    // 模块状态表1
    uint8_t module_dc_side_off[YFY_MODULE_NUM];  // 模块 DC 侧处于关机状态
    uint8_t module_fault[YFY_MODULE_NUM];          // 模块故障告警
    uint8_t module_protection[YFY_MODULE_NUM];     // 模块保护告警
    uint8_t fan_fault[YFY_MODULE_NUM];             // 风扇故障告警
    uint8_t over_temp[YFY_MODULE_NUM];             // 过温告警
    uint8_t output_overvoltage[YFY_MODULE_NUM];    // 输出过压告警
    uint8_t walk_in_enable[YFY_MODULE_NUM];        // WALK-IN 使能
    uint8_t module_comm_interrupt[YFY_MODULE_NUM]; // 模块通信中断告警

    // 模块状态表0
    uint8_t output_short_circuit[YFY_MODULE_NUM];       // 输出短路
    uint8_t module_internal_comm_fault[YFY_MODULE_NUM]; // 模块内部通信故障
    uint8_t input_or_bus_abnormal[YFY_MODULE_NUM];      // 输入或母线异常
    uint8_t module_sleep[YFY_MODULE_NUM];               // 模块休眠
    uint8_t module_discharge_abnormal[YFY_MODULE_NUM];  // 模块放电异常

    uint16_t ac_input_voltage_ab[YFY_MODULE_NUM]; // 交流输入电压AB相电压
    uint16_t ac_input_voltage_bc[YFY_MODULE_NUM]; // 交流输入电压BC相电压
    uint16_t ac_input_voltage_ca[YFY_MODULE_NUM]; // 交流输入电压CA相电压

    uint16_t max_voltage[YFY_MODULE_NUM]; // 最大电压
    uint16_t min_voltage[YFY_MODULE_NUM]; // 最小电压
    uint16_t max_current[YFY_MODULE_NUM]; // 最大电流
    uint16_t max_power[YFY_MODULE_NUM];   // 最大功率

    uint16_t external_voltage[YFY_MODULE_NUM];   // 外部电压
    uint16_t max_output_current[YFY_MODULE_NUM]; // 当前最大输出电流

    // 设置命令回复中的部分数据与读取重合，不进行处理。无用数据不处理。
    uint8_t addr_modeL[YFY_MODULE_NUM]; // 模块地址模式
} yfy_module_data_t;

typedef struct yfy_group_module_data_t
{
    float voltage[YFY_GROUP_NUM];      // 组电压
    float current[YFY_GROUP_NUM];      // 组电流
    uint8_t module_num[YFY_GROUP_NUM]; // 组内模块数量
} yfy_group_module_data_t;

typedef struct yfy_sys_module_data_t
{
    float voltage;      // 系统电压
    float current;      // 系统电流
    uint8_t module_num; // 系统模块数量
} yfy_sys_module_data_t;

typedef struct yfy_module_info_t
{
    uint16_t cmd;
    uint16_t byte_start;
    uint16_t byte_end;
    uint16_t bit_start;
    uint16_t bit_end;
    void* pdata;
} yfy_module_info_t;

typedef struct yfy_group_module_info_t
{
    uint16_t cmd;
    uint16_t byte_start;
    uint16_t byte_end;
    uint16_t bit_start;
    uint16_t bit_end;
    void* pdata;
} yfy_group_module_info_t;

typedef struct yfy_sys_module_inf_t
{
    uint16_t cmd;
    uint16_t byte_start;
    uint16_t byte_end;
    uint16_t bit_start;
    uint16_t bit_end;
    void* pdata;
} yfy_sys_module_inf_t;

#define MODULE_OFFLINE_TIME 5000

typedef struct yfy_set_moduole_inf_t
{
    uint16_t cmd;
    uint16_t byte_start;
    uint16_t byte_end;
} yfy_set_moduole_inf_t;

typedef enum yfy_module_info_type_t
{
    eModuleInfo,
    eGroupModuleInfo,
    eSysModuleInfo,
} yfy_module_info_type_t;

typedef struct yfy_module_online_info_t
{
    uint32_t last_online_time;
    bool is_online;
} yfy_module_online_info_t;

typedef struct yfy_module_handle_t
{
    bool (*send)(uint32_t id, uint8_t* pdata);
    bool (*recv)(uint32_t* id, uint8_t* pdata);
    uint32_t (*time)(void);
} yfy_module_handle_t;

void yfy_module_handle_init(bool (*send)(uint32_t id, uint8_t* pdata), bool (*recv)(uint32_t* id, uint8_t* pdata), uint32_t (*time)(void));

yfy_module_handle_t* yfy_module_handle_get(void);

void yfy_process_data(void);

yfy_module_online_info_t* get_module_online_info(void);

yfy_module_data_t* get_module_data(void);

yfy_group_module_data_t* get_group_module_data(void);

yfy_sys_module_data_t* get_sys_module_data(void);
