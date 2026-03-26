/**
 * @file yyln_interface_acdc.c
 * @brief 优优绿能模块接口实现
 * @details 实现优优绿能模块的组管理和数据查询接口
 *
 * @version 1.0
 */

#include "yyln_interface_acdc.h"
#include "yyln_data_acdc.h"


// 模块开机接口
bool yyln_group_power_on(uint32_t group)
{
    return yyln_send_write_module_shutdown_dcdc(YYLN_BROADCAST_ADDR, (uint8_t)(group + 1), 0);
}

// 模块关机接口
bool yyln_group_power_off(uint32_t group)
{
    return yyln_send_write_module_shutdown_dcdc(YYLN_BROADCAST_ADDR, (uint8_t)(group + 1), 1);
}

/**
 * @brief 获取模块组的高低电压模式
 * @param group 组号
 * @param module_num_max 最大模块数量
 * @return uint32_t 模式状态 0=未读到数据 1=只有高压 2=只有低压 3=只有自动高低压 4=混合状态
 * @note 遍历组内所有模块，统计其高低压模式
 */
static uint32_t yyln_group_module_voltage_mode(uint32_t group, uint32_t module_num_max)
{
    uint32_t module_hilo_mode = 0;
    uint32_t high_voltage_count = 0;
    uint32_t low_voltage_count = 0;
    uint32_t auto_voltage_count = 0;
    uint32_t result = 3; // 默认为未稳定状态

    if(module_num_max > YYLN_MODULE_NUM)
    {
        return 0;
    }
    // 遍历所有模块(地址范围1~module_num_max)
    for (uint8_t module_addr = 1; module_addr <= module_num_max; module_addr++)
    {
        // 获取模块组号
        uint32_t module_group;
        if (yyln_get_module_module_group(module_addr, &module_group))
        {
            // 检查模块组号是否匹配
            if (module_group == group)
            {
                // 获取模块高低压模式
                if (yyln_get_module_work_mode(module_addr, &module_hilo_mode))
                {
                    if (module_hilo_mode == YYLN_MOUDLE_HV)
                    {
                        high_voltage_count++;
                    }
                    else if (module_hilo_mode == YYLN_MODULE_LV)
                    {
                        low_voltage_count++;
                    }
                    else if (module_hilo_mode == YYLN_MODULE_HLAUTO)
                    {
                        auto_voltage_count++;
                    }
                }
            }
        }
    }

    // 判断组内模块高低压模式状态
    if(high_voltage_count == 0 && low_voltage_count == 0 && auto_voltage_count == 0)
    {
        //没有读到数据
        result = 0;
    }
    else if (high_voltage_count > 0 && low_voltage_count == 0 && auto_voltage_count == 0)
    {
        // 只有高压模块
        result = 1;
    }
    else if (low_voltage_count > 0 && high_voltage_count == 0 && auto_voltage_count == 0)
    {
        // 只有低压模块
        result = 2;
    }
    else if(auto_voltage_count > 0 && low_voltage_count == 0 && high_voltage_count == 0)
    {
        // 只有自动高低压模块
        result = 3;
    }
    else
    {
        result = 4;
    }

    return result;
}

/**
 * @brief 设置模块组输出电压和电流
 * @param group 组号
 * @param voltage 输出电压(V)
 * @param current 输出电流(A)
 * @param module_numbers 模块数量
 * @param module_num_max 最大模块数量
 * @return true 设置成功, false 设置失败
 * @note 会根据电压大小自动设置高低压模式，如果需要切换模式则返回false
 */
bool yyln_group_set_voltage_current(uint32_t group, float voltage, float current, uint32_t module_numbers, uint32_t module_num_max)
{
    bool flag = true;
    uint32_t per_module_current = 0u;

    if(module_num_max > YYLN_MODULE_NUM)
    {
        return false;
    }

    if(module_numbers < 1)
    {
        per_module_current = (uint32_t)(current * 1000.0f);
    }
    else
    {
        per_module_current = (uint32_t)((current * 1000.0f) / (float)module_numbers);
    }
    uint32_t per_module_voltage = (uint32_t)(voltage * 1000.0f);

    uint32_t group_id = group + 1; //模块组号从1开始计数
    if(per_module_voltage > 500000)
    {
        if((yyln_group_module_voltage_mode(group_id, module_num_max) != YYLN_MOUDLE_HV) & (yyln_group_module_voltage_mode(group_id, module_num_max) != YYLN_MODULE_HLAUTO))
        {
            //关机并设置为高压模式
            yyln_group_power_off(group);
            yyln_send_write_module_himode_lomode_selection(YYLN_BROADCAST_ADDR, (uint8_t)group_id, YYLN_MOUDLE_HV);
            yyln_send_read_module_himode_lomode_selection_set_by_group(group_id);
            return false;
        }
    }
    else
    {
        if((yyln_group_module_voltage_mode(group_id, module_num_max) != YYLN_MODULE_LV) & (yyln_group_module_voltage_mode(group_id, module_num_max) != YYLN_MODULE_HLAUTO))
        {
            //关机并设置为低压模式
            yyln_group_power_off(group);
            yyln_send_write_module_himode_lomode_selection(YYLN_BROADCAST_ADDR, (uint8_t)group_id, YYLN_MODULE_LV);
            yyln_send_read_module_himode_lomode_selection_set_by_group(group_id);
            return false;
        }
    }
    flag = yyln_send_write_module_vout_reference(YYLN_BROADCAST_ADDR, (uint8_t)group_id, per_module_voltage);
    flag &= yyln_send_write_module_iout_limit(YYLN_BROADCAST_ADDR, (uint8_t)group_id, per_module_current);

    //需求电压大于模块最小输出电压，且模块当前输出电压小于150v，则开机
    float voltage_fb = 0.0;
    float current_fb = 0.0;
    yyln_group_get_voltage_current(group, &voltage_fb, &current_fb, module_num_max);
    if((per_module_voltage >= 150000) & (voltage_fb < 150000))
    {
        //需求电压大于模块最小输出电压，但模块输出电压显示模块是关机状态
        yyln_group_power_on(group);
    }
    return flag;
}

/**
 * @brief 读取模块组输出电压和电流
 * @param group 组号
 * @param voltage 输出电压指针(V)
 * @param current 输出电流指针(A)
 * @param module_num_max 最大模块数量
 * @return true 读取成功, false 读取失败
 * @note 电压为组内模块平均电压，电流为组内模块总电流
 */
bool yyln_group_get_voltage_current(uint32_t group, float* voltage, float* current, uint32_t module_num_max)
{
    //对所有模块获取组号。电压为组内模块平均电压，电流为组内模块总电流
    float total_voltage = 0;
    float total_current = 0;
    uint32_t module_count = 0;
    uint32_t module_group;
    uint32_t module_voltage;
    uint32_t module_current;
    bool result = true;

    if(module_num_max > YYLN_MODULE_NUM)
    {
        return false;
    }

    group = group + 1; //模块组号从1开始计数
    // 遍历所有模块(地址范围1~module_num_max)
    for (uint8_t module_addr = 1; module_addr <= module_num_max; module_addr++)
    {
        // 获取模块组号
        if (yyln_get_module_module_group(module_addr, &module_group))
        {
            // 检查模块组号是否匹配
            if (module_group == group)
            {
                // 获取模块电压和电流
                if (yyln_get_module_vout(module_addr, &module_voltage) &&
                    yyln_get_module_iout(module_addr, &module_current))
                {
                    total_voltage += module_voltage;
                    total_current += module_current;
                    module_count++;
                }
            }
        }
    }

    // 计算平均电压和总电流
    if (module_count > 0)
    {
        *voltage = (total_voltage / module_count) / 1000.0f;
        *current = total_current / 1000.0f;
        result = true;
    }
    else
    {
        *voltage = 0;
        *current = 0;
        result = false;
    }

    return result;
}

/**
 * @brief 读取模块组状态映射表
 * @param group 组号
 * @param status_map 状态映射表指针
 * @param module_num_max 最大模块数量
 * @return true 读取成功, false 读取失败
 * @note 获取所有同组模块的状态map，进行或操作
 */
bool yyln_group_get_status_map(uint32_t group, uint32_t* status_map, uint32_t module_num_max)
{
    //获取所有同组的模块的map，进行或操作
    uint32_t combined_status_map = 0;
    uint32_t module_group;
    uint32_t module_status_map;
    bool result = false;
    bool found_modules = false;

    if(module_num_max > YYLN_MODULE_NUM)
    {
        return false;
    }

    group = group + 1; //模块组号从1开始计数
    // 遍历所有模块(地址范围1~module_num_max)
    for (uint8_t module_addr = 1; module_addr <= module_num_max; module_addr++)
    {
        // 获取模块组号
        if (yyln_get_module_module_group(module_addr, &module_group))
        {
            // 检查模块组号是否匹配
            if (module_group == group)
            {
                // 获取模块状态map
                if (yyln_get_module_status_map(module_addr, &module_status_map))
                {
                    combined_status_map |= module_status_map;
                    found_modules = true;
                    result = true;
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
 * @brief 获取组内正常模块个数
 * @param group 组号
 * @param module_number 模块数量指针
 * @param module_num_max 最大模块数量
 * @return true 获取成功, false 获取失败
 * @note 统计指定组号内无故障且在线的模块个数
 */
bool yyln_group_get_module_number(uint32_t group, uint32_t* module_number, uint32_t module_num_max)
{
    //统计指定组号内的模块个数
    uint32_t count = 0;
    uint32_t module_group;

    if(module_num_max > YYLN_MODULE_NUM)
    {
        return false;
    }

    group = group + 1; //模块组号从1开始计数
    // 遍历所有模块(地址范围1~module_num_max)
    for (uint8_t module_addr = 1; module_addr <= module_num_max; module_addr++)
    {
        // 获取模块组号
        if (yyln_get_module_module_group(module_addr, &module_group))
        {
            uint32_t module_status_map;
            yyln_get_module_status_map(module_addr, &module_status_map);
            //判断模块是否故障
            if((module_status_map & 0xB035FBFF) != 0)
            {
                continue;
            }

            if(yyln_get_module_online_info(module_addr) == false)
            {
                continue;
            }

            // 检查模块组号是否匹配
            if (module_group == group)
            {
                count++;
            }
        }
    }

    *module_number = count;
    return (count > 0);
}

/**
 * @brief 读取模块AB相间电压
 * @param module_addr 模块地址
 * @param voltage 电压值指针(mV)
 * @param module_num_max 最大模块数量
 * @return true 读取成功, false 读取失败
 */
bool yyln_module_get_v_ab(uint32_t module_addr, uint32_t* voltage, uint32_t module_num_max)
{
    if(module_num_max > YYLN_MODULE_NUM)
    {
        return false;
    }

    if(module_addr == 0 || module_addr > module_num_max)
    {
        return false;
    }
    yyln_get_module_v_ab(module_addr, voltage);

    return true;
}

/**
 * @brief 检查模块是否在线
 * @param module_addr 模块地址
 * @param module_num_max 最大模块数量
 * @return true 在线, false 离线或地址无效
 */
bool yyln_module_is_online(uint32_t module_addr, uint32_t module_num_max)
{
    if(module_num_max > YYLN_MODULE_NUM)
    {
        return false;
    }

    if(module_addr == 0 || module_addr > module_num_max)
    {
        return false;
    }

    return yyln_get_module_online_info(module_addr);
}


bool yyln_single_module_temp(uint32_t module_addr, float* temperature)
{

    uint32_t temp = 0;
    yyln_get_module_dcdc_temp(module_addr, &temp);
    *temperature = (float)temp / 1000;
    return true;
}