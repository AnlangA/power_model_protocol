/**
 * @file yfy_interface_acdc.c
 * @brief 英飞源模块接口实现
 * @details 实现英飞源模块的组管理和数据查询接口
 *
 * @version 1.0
 */

#include "yfy_interface_acdc.h"
#include "yfy_api_acdc.h"
#include "string.h"

/**
 * @brief 开启指定分组的所有模块电源
 * @param group 分组号
 * @return true 成功, false 失败(分组号无效)
 */
bool yfy_group_power_on(uint32_t group)
{
    if(group >= YFY_GROUP_NUM)
    {
        return false;
    }
    yfy_send_write_work_by_group(group + 1, false);
    return true;
}

/**
 * @brief 关闭指定分组的所有模块电源
 * @param group 分组号
 * @return true 成功, false 失败(分组号无效)
 */
bool yfy_group_power_off(uint32_t group)
{
    if(group >= YFY_GROUP_NUM)
    {
        return false;
    }
    yfy_send_write_work_by_group(group + 1, true);
    return true;
}


/**
 * @brief 设置指定分组的输出电压和电流
 * @param group 分组号
 * @param volt 输出电压(V)
 * @param current 输出电流(A)
 * @param module_num_max 模块数量(未使用,模块内部自动处理)
 * @return true 成功, false 失败(分组号无效)
 */
bool yfy_group_set_voltage_current(uint32_t group, float volt, float current, uint32_t module_numbers, uint32_t module_num_max)
{
    //英飞源模块内部会自动除以模块数量，所以这里不需要除以模块数量
    if(group >= YFY_GROUP_NUM)
    {
        return false;
    }
    if(group >= module_num_max)
    {
        return false;
    }
    uint32_t volt_mV = (uint32_t)(volt * 1000);
    uint32_t current_mA = (uint32_t)(current * 1000);
    yfy_send_write_output_all_by_group(group + 1, volt_mV, current_mA);

    //判断需求电压与开关机状态。
    float v_fb = 0;
    float cur_fb = 0;
    yfy_group_get_voltage_current(group, &v_fb, &cur_fb, module_numbers);
    if((volt_mV >= 150000) & (v_fb <= 150))
    {
        yfy_group_power_on(group);
    }else if(volt_mV < 150000)
    {
        yfy_group_power_off(group);
    }
    return true;
}

/**
 * @brief 获取指定分组的输出电压和电流
 * @param group 分组号
 * @param voltage 输出电压指针(V)
 * @param current 输出电流指针(A)
 * @return true 成功, false 失败
 */
bool yfy_group_get_voltage_current(uint32_t group, float* voltage, float* current, uint32_t module_num_max)
{
    if(group > YFY_GROUP_NUM)
    {
        return false;
    }
    if(group > module_num_max)
    {
        return false;
    }
    yfy_group_module_data_t* group_data = get_group_module_data();
    *voltage = group_data->voltage[group];
    *current = group_data->current[group];
    return true;
}

/**
 * @brief 获取模块故障状态位图
 * @param module_addr 模块地址
 * @param module_num_max 最大模块数量
 * @return uint32_t 故障位图，从低位到高位依次表示不同故障，0xFFFFFFFF表示错误
 * @note 各位含义：bit0-输出短路, bit1-模块内部通信故障, bit2-输入或母线异常, bit3-模块休眠等
 */
uint32_t yfy_module_status_info(uint32_t module_addr, uint32_t module_num_max)
{
    if(module_addr > YFY_MODULE_NUM)
    {
        return 0xFFFFFFFF;
    }
    if(module_addr == 0 || module_addr > module_num_max)
    {
        return 0xFFFFFFFF;
    }

    yfy_module_data_t* module_data = get_module_data();

    uint32_t fault_bits = 0;

    //输出短路
    if(module_data->output_short_circuit[module_addr] == 1)
    {
        fault_bits |= (1 << 0);
    }
    //模块内部通信故障
    if(module_data->module_internal_comm_fault[module_addr] == 1)
    {
        fault_bits |= (1 << 1);
    }
    //输入或母线异常
    if(module_data->input_or_bus_abnormal[module_addr] == 1)
    {
        fault_bits |= (1 << 2);
    }
    //模块休眠
    if(module_data->module_sleep[module_addr] == 1)
    {
        fault_bits |= (1 << 3);
    }
    //模块放电异常
    if(module_data->module_discharge_abnormal[module_addr] == 1)
    {
        fault_bits |= (1 << 4);
    }
    //模块故障告警
    if(module_data->module_fault[module_addr] == 1)
    {
        fault_bits |= (1 << 5);
    }
    //模块保护告警
    if(module_data->module_protection[module_addr] == 1)
    {
        fault_bits |= (1 << 6);
    }
    //风扇故障告警
    if(module_data->fan_fault[module_addr] == 1)
    {
        fault_bits |= (1 << 7);
    }
    //过温告警
    if(module_data->over_temp[module_addr] == 1)
    {
        fault_bits |= (1 << 8);
    }
    //输出过压告警
    if(module_data->output_overvoltage[module_addr] == 1)
    {
        fault_bits |= (1 << 9);
    }

    //模块通信中断告警
    if(module_data->module_comm_interrupt[module_addr] == 1)
    {
        fault_bits |= (1 << 10);
    }

    //模块处于限功率
    if(module_data->module_limit_power[module_addr] == 1)
    {
        fault_bits |= (1 << 11);
    }
    //模块ID重复
    if(module_data->module_id_duplicate[module_addr] == 1)
    {
        fault_bits |= (1 << 12);
    }
    //模块严重不均流
    if(module_data->module_severe_unbalanced[module_addr] == 1)
    {
        fault_bits |= (1 << 13);
    }
    //三相输入缺相告警
    if(module_data->three_phase_input_missing[module_addr] == 1)
    {
        fault_bits |= (1 << 14);
    }
    //三相输入不平衡告警
    if(module_data->three_phase_input_unbalanced[module_addr] == 1)
    {
        fault_bits |= (1 << 15);
    }
    //输入欠压告警
    if(module_data->input_undervoltage[module_addr] == 1)
    {
        fault_bits |= (1 << 16);
    }
    //输入过压告警
    if(module_data->input_overvoltage[module_addr] == 1)
    {
        fault_bits |= (1 << 17);
    }

    //模块 PFC 侧处于关机状态
    if(module_data->module_pfc_fault[module_addr] == 1)
    {
//        fault_bits |= (1 << 7);
    }
    //模块 DC 侧处于关机状态
    if(module_data->module_dc_side_off[module_addr] == 1)
    {
//        fault_bits |= (1 << 8);
    }
    //WALK-IN 使能
    if(module_data->walk_in_enable[module_addr] == 1)
    {
//        fault_bits |= (1 << 14);
    }
    return fault_bits;
}

/**
 * @brief 检查指定模块是否在线
 * @param module_addr 模块地址
 * @param module_num_max 模块数量
 * @return true 在线, false 离线或地址无效
 */
/**
 * @brief 检查指定模块是否在线
 * @param module_addr 模块地址
 * @param module_num_max 模块数量
 * @return true 在线, false 离线或地址无效
 */
bool yfy_module_is_online(uint32_t module_addr, uint32_t module_num_max)
{
    if(module_addr == 0 || module_addr > module_num_max)
    {
        return false;
    }
    if(module_addr > YFY_MODULE_NUM)
    {
        return false;
    }
    return yfy_module_online((uint8_t)module_addr);
}

/**
 * @brief 获取模块组状态映射表
 * @param group 组号
 * @param status_map 状态映射表指针
 * @param module_num_max 最大模块数量
 * @return true 获取成功, false 获取失败
 * @note 获取所有同组在线模块的故障map，进行或操作
 */
bool yfy_group_get_status_map(uint32_t group, uint32_t* status_map, uint32_t module_num_max)
{
    //获取所有同组的模块的map，进行或操作
    uint32_t combined_status_map = 0;
    uint8_t module_group;
    uint32_t module_status_map;
    bool result = false;
    bool found_modules = false;

    if(group >= YFY_GROUP_NUM)
    {
        return false;
    }

    group = group + 1; //模块组号从1开始计数
    // 遍历所有模块(地址范围1~module_num_max)
    for (uint8_t module_addr = 1; module_addr <= module_num_max; module_addr++)
    {
        // 检查模块是否在线
        if(yfy_module_is_online(module_addr, module_num_max))
        {
            // 获取模块组号
            if (yfy_get_module_group(module_addr, &module_group))
            {
                // 检查模块组号是否匹配
                if (module_group == group)
                {
                    // 获取模块状态map
                    module_status_map = yfy_module_status_info(module_addr, module_num_max);
                    if (module_status_map != 0xFFFFFFFF)
                    {
                        combined_status_map |= module_status_map;
                        found_modules = true;
                        result = true;
                    }
                }
            }
        }
    }

    // 如果没有找到匹配的模块，返回0和false
    if (!found_modules)
    {
        *status_map = 0;
        result = false;
    }
    else
    {
        *status_map = combined_status_map;
    }

    return result;
}

/**
 * @brief 获取组内模块个数
 * @param group 组号
 * @param module_number 模块数量指针
 * @param module_num_max 最大模块数量
 * @return true 获取成功, false 获取失败
 */
bool yfy_group_get_module_number(uint32_t group, uint32_t* module_number, uint32_t module_num_max)
{
    if(group > YFY_GROUP_NUM)
    {
        return false;
    }
    if(group > module_num_max)
    {
        return false;
    }
    yfy_group_module_data_t* group_data = get_group_module_data();
    *module_number = group_data->module_num[group];
    return true;
}

/**
 * @brief 读取模块AB相间电压
 * @param module_addr 模块地址
 * @param voltage 电压值指针(mV)
 * @param module_num_max 最大模块数量
 * @return true 读取成功, false 读取失败
 */
bool yfy_module_get_v_ab(uint32_t module_addr, uint32_t* voltage, uint32_t module_num_max)
{
    if(module_addr > YFY_GROUP_NUM)
    {
        return false;
    }
    if(module_addr == 0 || module_addr > module_num_max)
    {
        return false;
    }
    uint16_t voltage_16;
    bool ret = yfy_get_ac_input_voltage_ab((uint8_t)module_addr, &voltage_16);
    //转换为v
    *voltage = (uint32_t)(voltage_16 * 100);
    return ret;
}

bool yfy_single_module_temp(uint32_t module_addr, float* temperature)
{

    int8_t temp = 0;
    yfy_get_module_temp(module_addr, &temp);
    *temperature = (float)temp;
    return true;
}
