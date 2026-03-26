/**
 * @file module_context.h
 * @brief 电源模块上下文定义
 * @details 定义电源模块的统一接口结构体和上下文管理
 *
 * @version 1.0
 */

#pragma once

#include "string.h"
#include "stdint.h"
#include "yyln_interface_acdc.h"
#include "yfy/yfy_interface_acdc.h"

// ==================== 单模块设置结构体 ====================

/**
 * @brief 单模块设置接口结构体
 */
typedef struct {
    bool (*power_on)(uint32_t module_addr);                                  ///< 设置开机
    bool (*power_off)(uint32_t module_addr);                                 ///< 设置关机
    bool (*voltage_current)(uint32_t module_addr, float voltage, float current); ///< 设置电压、电流
    bool (*cmd_group_mode)(uint32_t module_addr);                            ///< 设置命令分组
    bool (*group_number)(uint32_t module_addr, uint32_t group);              ///< 设置组号
} SingleMouldeSet;

// ==================== 组设置结构体 ====================

/**
 * @brief 模块组设置接口结构体
 */
typedef struct {
    bool (*power_on)(uint32_t group);                                        ///< 设置开机
    bool (*power_off)(uint32_t group);                                       ///< 设置关机
    bool (*voltage_current_output)(uint32_t group, float voltage, float current, uint32_t module_numbers, uint32_t module_num_max); ///< 设置电压、电流
} GroupMouldeSet;

// ==================== 单模块查询结构体 ====================

/**
 * @brief 单模块数据查询接口结构体
 */
typedef struct {
    bool (*voltage_current)(uint32_t module_addr, float* voltage, float* current); ///< 输出电压、电流
    bool (*allow_current)(uint32_t module_addr, float* current);              ///< 允许电流（当前工况下允许的最大输出电流）
    bool (*temperature)(uint32_t module_addr, float* temperature);            ///< 温度
    bool (*is_power_on)(uint32_t module_addr);                                ///< 开关机状态
    bool (*group_number)(uint32_t module_addr, uint32_t* group);              ///< 组号
    bool (*max_output_voltage)(float* voltage);                               ///< 最大输出电压
    bool (*max_output_current)(float* current);                               ///< 最大输出电流
    bool (*max_output_power)(float* power);                                   ///< 最大输出功率
    uint32_t (*status_info)(uint32_t module_addr);                            ///< 故障状态
    bool (*is_online)(uint32_t module_addr, uint32_t module_num_max);         ///< 离线状态：通讯离线
} SingeMoudleQuery;

// ==================== 组查询结构体 ====================

/**
 * @brief 模块组数据查询接口结构体
 */
typedef struct GroupMoudleQuery {
    bool (*voltage_current)(uint32_t group, float* voltage, float* current, uint32_t module_num_max); ///< 输出电压、电流
    bool (*module_number)(uint32_t group, uint32_t* module_number, uint32_t module_num_max);          ///< 模块数量
    bool (*group_status)(uint32_t group, uint32_t* status, uint32_t module_num_max);                  ///< 模块组状态
    bool (*ac_input_voltage)(uint32_t group, uint32_t* voltage, uint32_t module_num_max);             ///< 模块输入电压
} GroupMoudleQuery;

// ==================== 系统查询结构体 ====================

/**
 * @brief 系统级数据查询接口结构体
 */
typedef struct SystemQuery {
    bool (*voltage_current)(float* voltage, float* current);                  ///< 输出电压、电流
    bool (*module_number)(uint32_t* module_number);                          ///< 模块数量
} SystemQuery;

// ==================== 电源上下文结构体 ====================

/**
 * @brief 电源模块面向功率分配的统一接口结构体
 */
typedef struct {
    char module_name[20];            ///< 模块名称
    SingleMouldeSet single_module_set;   ///< 单模块设置接口
    GroupMouldeSet group_module_set;     ///< 组设置接口
    SingeMoudleQuery single_module_query; ///< 单模块查询接口
    GroupMoudleQuery group_module_query;  ///< 组查询接口
    SystemQuery system_query;            ///< 系统查询接口
} PowerContext;

// ==================== 模块类型枚举 ====================

/**
 * @brief 电源模块类型枚举
 */
typedef enum {
    eModuleTypeYfy = 0,   ///< 英飞源模块
    eModuleTypeYyln,      ///< 优优绿能模块
} module_type_t;

// ==================== 函数声明 ====================

/**
 * @brief 获取电源控制上下文指针
 * @return PowerContext* 电源上下文指针
 */
PowerContext* power_ctrl(void);

/**
 * @brief 初始化模块上下文
 * @param module_type 模块类型
 */
void module_context_init(module_type_t module_type);
