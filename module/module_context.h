#pragma once

#include "string.h"
#include "stdint.h"
#include "yyln_interface_acdc.h"
#include "yfy/yfy_interface_acdc.h"

//单个模块设置
typedef struct{
    //设置开机
    bool (*power_on)(uint32_t module_addr);
    //设置关机
    bool (*power_off)(uint32_t module_addr);
    //设置电压、电流
    bool (*voltage_current)(uint32_t module_addr, float voltage, float current);
    //设置命令分组
    bool (*cmd_group_mode)(uint32_t module_addr);
    //设置组号
    bool (*group_number)(uint32_t module_addr, uint32_t group);
}SingleMouldeSet;

//组设置
typedef struct{
    //设置开机
    bool (*power_on)(uint32_t group);
    //设置关机
    bool (*power_off)(uint32_t group);
    //设置电压、电流。module_numbers用于兼容。
    bool (*voltage_current_output)(uint32_t group, float voltage, float current, uint32_t module_numbers, uint32_t module_num_max);
}GroupMouldeSet;

//单模块数据查询
typedef struct{
    //输出电压、电流
    bool (*voltage_current)(uint32_t module_addr, float* voltage, float* current);
    //允许电流。当前工况下允许的最大输出电流。此数据用于功率分配的判断
    bool (*allow_current)(uint32_t module_addr, float* current);
    //温度
    bool (*temperature)(uint32_t module_addr, float* temperature);
    //开关机状态
    bool (*is_power_on)(uint32_t module_addr);
    //组号
    bool (*group_number)(uint32_t module_addr, uint32_t* group);
    //最大输出电压
    bool (*max_output_voltage)(float* voltage);
    //最大输出电流
    bool (*max_output_current)(float* current);
    //最大输出功率
    bool (*max_output_power)(float* power);
    // 故障
    uint32_t (*status_info)(uint32_t module_addr);
    //离线状态：通讯离线
    bool (*is_online)(uint32_t module_addr, uint32_t module_num_max);
}SingeMoudleQuery;

typedef struct GroupMoudleQuery{
    //输出电压、电流
    bool (*voltage_current)(uint32_t group, float* voltage, float* current, uint32_t module_num_max);
    //模块数量
    bool (*module_number)(uint32_t group, uint32_t* module_number, uint32_t module_num_max);
    //模块组状态
    bool (*group_status)(uint32_t group, uint32_t* status, uint32_t module_num_max);
    //模块输入电压
    bool (*ac_input_voltage)(uint32_t group, uint32_t* voltage, uint32_t module_num_max);
} GroupMoudleQuery;

typedef struct SystemQuery{
    //输出电压、电流
    bool (*voltage_current)(float* voltage, float* current);
    //模块数量
    bool (*module_number)(uint32_t* module_number);
}SystemQuery;

//电源模块面向功率分配的接口
typedef struct{
    char module_name[20];
    SingleMouldeSet single_module_set;
    GroupMouldeSet group_module_set;
    SingeMoudleQuery single_module_query;
    GroupMoudleQuery group_module_query;
    SystemQuery system_query;
}PowerContext;

typedef enum{
    eModuleTypeYfy = 0,
    eModuleTypeYyln,
}module_type_t;

PowerContext* power_ctrl(void);
void module_context_init(module_type_t module_type);
