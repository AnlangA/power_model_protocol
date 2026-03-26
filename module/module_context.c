#include "stdbool.h"
#include "module_context.h"

PowerContext power_context = {0};

PowerContext* power_ctrl(void)
{
    return &power_context;
}

/**
 * @brief yyln
 *
 */
SingeMoudleQuery yyln_single_module_query = {
    //离线状态：通讯离线
    .is_online = yyln_module_is_online,
    .temperature = yyln_single_module_temp,
};

GroupMouldeSet yyln_group_module_set = {
    .power_on = yyln_group_power_on,
    .power_off = yyln_group_power_off,
    .voltage_current_output = yyln_group_set_voltage_current,
};

GroupMoudleQuery yyln_group_module_query = {
    .voltage_current = yyln_group_get_voltage_current,
    .module_number = yyln_group_get_module_number,
    .group_status = yyln_group_get_status_map,
    .ac_input_voltage = yyln_module_get_v_ab,
};


/**
 * @brief yfy
 *
 */
 SingeMoudleQuery yfy_single_module_query = {
     //离线状态：通讯离线
     .is_online = yfy_module_is_online,
     .temperature = yfy_single_module_temp,
 };

 GroupMouldeSet yfy_group_module_set = {
     .power_on = yfy_group_power_on,
     .power_off = yfy_group_power_off,
     .voltage_current_output = yfy_group_set_voltage_current,
 };

 GroupMoudleQuery yfy_group_module_query = {
     .voltage_current = yfy_group_get_voltage_current,
     .module_number = yfy_group_get_module_number,
     .group_status = yfy_group_get_status_map,
     .ac_input_voltage = yfy_module_get_v_ab,
 };

/**
 * @brief 初始化电源模块上下文
 *
 * @param module_type
 */
void module_context_init(module_type_t module_type)
{
    switch (module_type)
    {
        case eModuleTypeYfy:
            strcpy(power_context.module_name, "yfy");
            power_context.group_module_set = yfy_group_module_set;
            power_context.group_module_query = yfy_group_module_query;
            break;
        case eModuleTypeYyln:
            strcpy(power_context.module_name, "yyln");
            power_context.group_module_set = yyln_group_module_set;
            power_context.group_module_query = yyln_group_module_query;
            break;
        
        default:
            break;
    }
}
