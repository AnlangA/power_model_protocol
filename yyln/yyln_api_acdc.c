#include "yyln_data_acdc.h"
#include "stddef.h"

// 内部辅助函数：检查模块地址是否有效
static bool yyln_module_addr_is_available(uint8_t module_addr)
{
    if (module_addr > YYLN_MODULE_NUM)
    {
        return false;
    }
    return true;
}

static bool yyln_group_addr_is_available(uint8_t group_addr)
{
    if (group_addr > YYLN_GROUP_NUM)
    {
        return false;
    }
    return true;
}

/**
 * @brief 模块输出电压设定值
 *
 */
bool yyln_send_write_module_vout_reference(uint8_t module_addr, uint8_t group, uint32_t voltage)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    // 直接传入原始数值，函数内部会自动进行字节序转换
    yyln_send_write_cmd(module_addr, group, yyln_SetData, yyln_VoutReference, voltage);
    return true;
}

/**
 * @brief 模块输出限流点设定值
 *
 */
bool yyln_send_write_module_iout_limit(uint8_t module_addr, uint8_t group, uint32_t current)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    // 直接传入原始数值，函数内部会自动进行字节序转换
    yyln_send_write_cmd(module_addr, group, yyln_SetData, yyln_IoutLimit, current);
    return true;
}

/**
 * @brief 模块开关机
 *
 * @param module_addr 模块地址
 * @param group 组地址
 * @param shutdown 0:开机 1:关机
 */
bool yyln_send_write_module_shutdown_dcdc(uint8_t module_addr, uint8_t group, uint32_t shutdown)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    // 直接传入原始数值，函数内部会自动进行字节序转换
    yyln_send_write_cmd(module_addr, group, yyln_SetData, yyln_ShutDownDCDC, shutdown);
    return true;
}

/**
 * @brief 设置组地址
 *
 */
bool yyln_send_write_group_num(uint8_t module_addr, uint8_t new_group)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    if (!yyln_group_addr_is_available(new_group))
    {
        return false;
    }

    // 直接传入原始数值，函数内部会自动进行字节序转换
    yyln_send_write_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_SetData, yyln_GroupAddress, new_group);
    return true;
}

/**
 * @brief 读取模块组号
 *
 */
bool yyln_send_read_group_num(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_GroupAddress);
    return true;
}

/**
 * @brief 设置模块高低压模块
 *
 */
bool yyln_send_write_module_himode_lomode_selection(uint8_t module_addr, uint8_t group, uint32_t mode)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    // 直接传入原始数值，函数内部会自动进行字节序转换
    yyln_send_write_cmd(module_addr, group, yyln_SetData, yyln_HiMode_LoMode_Selection, mode);
    return true;
}

/**
 * @brief 读取模块输出电压
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_vout(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Vout);
    return true;
}

/**
 * @brief 按组读取模块输出电压
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_vout_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Vout);
    return true;
}

/**
 * @brief 读取模块输出电流
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_iout(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Iout_slow);
    return true;
}

/**
 * @brief 按组读取模块输出电流
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_iout_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Iout_slow);
    return true;
}

/**
 * @brief 读取模块电压设定值
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_vout_reference(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_VoutReference);
    return true;
}

/**
 * @brief 按组读取模块电压设定值
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_vout_reference_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_VoutReference);
    return true;
}

/**
 * @brief 读取模块输出限流点设定值
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_iout_limit(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_IoutLimit);
    return true;
}

/**
 * @brief 按组读取模块输出限流点设定值
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_iout_limit_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_IoutLimit);
    return true;
}

/**
 * @brief 读取模块序列号
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_sn(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_ReadSN);
    return true;
}

/**
 * @brief 按组读取模块序列号
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_sn_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_ReadSN);
    return true;
}

/**
 * @brief 读取模块状态
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_module_status(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_ModuleStatus);
    return true;
}

/**
 * @brief 按组读取模块状态
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_module_status_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_ModuleStatus);
    return true;
}

/**
 * @brief 读取模块AB相间电压
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_ab_voltage(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Vab);
    return true;
}

/**
 * @brief 按组读取模块AB相间电压
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_ab_voltage_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Vab);
    return true;
}

/**
 * @brief 读取模块BC相间电压
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_bc_voltage(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Vbc);
    return true;
}

/**
 * @brief 按组读取模块BC相间电压
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_bc_voltage_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Vbc);
    return true;
}

/**
 * @brief 读取模块CA相间电压
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_ca_voltage(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Vca);
    return true;
}

/**
 * @brief 按组读取模块CA相间电压
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_ca_voltage_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Vca);
    return true;
}

/**
 * @brief 读取模块进风口温度
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_air_intake_temperature(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Tin);
    return true;
}

/**
 * @brief 按组读取模块进风口温度
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_air_intake_temperature_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Tin);
    return true;
}

/**
 * @brief 读取模块高低压模式设定状态
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_module_himode_lomode_set_selection(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_HiMode_LoMode_Status);
    return true;
}

/**
 * @brief 按组读取模块高低压模式设定状态
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_module_himode_lomode_selection_set_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_HiMode_LoMode_Status);
    return true;
}

/**
 * @brief 读取模块实际高低压模式状态
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_module_himode_lomode_selection(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_TrueHiLo_Status);
    return true;
}

/**
 * @brief 按组读取模块实际高低压模式状态
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_module_himode_lomode_selection_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_TrueHiLo_Status);
    return true;
}

/**
 * @brief 读取模块输出电流能力
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_current_capability(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_CurrentCapability);
    return true;
}

/**
 * @brief 按组读取模块输出电流能力
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_current_capability_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_CurrentCapability);
    return true;
}

/**
 * @brief 读取模块输出电流和功率能力
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_current_and_capability(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_CurrentAndCapability);
    return true;
}

/**
 * @brief 按组读取模块输出电流和功率能力
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_current_and_capability_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_CurrentAndCapability);
    return true;
}

// 1. uint32_t vout[YYLN_MODULE_NUM] - 模块输出电压 mV

/**
 * @brief 读取模块PFC热点温度
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_pfc_temperature(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Tpfc1);
    return true;
}

/**
 * @brief 按组读取模块PFC热点温度
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_pfc_temperature_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Tpfc1);
    return true;
}

/**
 * @brief 读取模块DCDC热点温度
 * @param module_addr 模块地址
 * @return bool 操作结果
 */
bool yyln_send_read_dcdc_temperature(uint8_t module_addr)
{
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_send_read_cmd(module_addr, YYLN_BROADCAST_ADDR, yyln_ReadData, yyln_Tdcdc2);
    return true;
}

/**
 * @brief 按组读取模块DCDC热点温度
 * @param group 组号
 * @return bool 操作结果
 */
bool yyln_send_read_dcdc_temperature_by_group(uint8_t group)
{
    if (!yyln_group_addr_is_available(group))
    {
        return false;
    }

    yyln_send_read_cmd(YYLN_BROADCAST_ADDR, group, yyln_ReadData, yyln_Tdcdc2);
    return true;
}
/**
 * @brief 读取指定模块的输出电压
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param voltage 输出电压值指针，单位：mV (毫伏)
 * @return bool 操作结果
 * @note 读取模块的实时输出电压
 */
bool yyln_get_module_vout(uint8_t module_addr, uint32_t* voltage)
{
    if (voltage == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *voltage = module_data->vout[module_addr - 1];
    return true;
}

// 2. uint32_t iout[YYLN_MODULE_NUM] - 模块输出电流 mA
/**
 * @brief 读取指定模块的输出电流
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param current 输出电流值指针，单位：mA (毫安)
 * @return bool 操作结果
 * @note 读取模块的实时输出电流
 */
bool yyln_get_module_iout(uint8_t module_addr, uint32_t* current)
{
    if (current == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *current = module_data->iout[module_addr - 1];
    return true;
}

// 3. uint32_t v_set[YYLN_MODULE_NUM] - 模块输出电压设定值 mV
/**
 * @brief 读取指定模块的电压设定值
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param voltage_set 电压设定值指针，单位：mV (毫伏)
 * @return bool 操作结果
 * @note 读取模块当前的电压设定值
 */
bool yyln_get_module_v_set(uint8_t module_addr, uint32_t* voltage_set)
{
    if (voltage_set == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *voltage_set = module_data->v_set[module_addr - 1];
    return true;
}

// 4. uint32_t i_set[YYLN_MODULE_NUM] - 模块输出限流点设定值 mA
/**
 * @brief 读取指定模块的电流限制设定值
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param current_limit 电流限制设定值指针，单位：mA (毫安)
 * @return bool 操作结果
 * @note 读取模块当前的电流限制设定值
 */
bool yyln_get_module_i_set(uint8_t module_addr, uint32_t* current_limit)
{
    if (current_limit == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *current_limit = module_data->i_set[module_addr - 1];
    return true;
}

// 5. uint32_t sn[YYLN_MODULE_NUM] - 模块序列号的低 32 位
/**
 * @brief 读取指定模块的序列号
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param serial_number 序列号指针（低32位）
 * @return bool 操作结果
 * @note 读取模块的序列号低32位
 */
bool yyln_get_module_sn(uint8_t module_addr, uint32_t* serial_number)
{
    if (serial_number == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *serial_number = module_data->sn[module_addr - 1];
    return true;
}

// 6. uint8_t ac_overVoltage[YYLN_MODULE_NUM] - 交流过压
/**
 * @brief 读取模块交流过压状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=交流过压
 * @return bool 操作结果
 * @note 检测交流输入电压是否超过正常工作范围
 */
bool yyln_get_module_ac_overVoltage(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->ac_overVoltage[module_addr - 1];
    return true;
}

// 7. uint8_t ac_underVoltage[YYLN_MODULE_NUM] - 交流欠压
/**
 * @brief 读取模块交流欠压状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=交流欠压
 * @return bool 操作结果
 * @note 检测交流输入电压是否低于正常工作范围
 */
bool yyln_get_module_ac_underVoltage(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->ac_underVoltage[module_addr - 1];
    return true;
}

// 8. uint8_t ac_overVoltageClose[YYLN_MODULE_NUM] - 交流过压脱离(交流过压ss关机)
/**
 * @brief 读取模块交流过压脱离状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=交流过压脱离
 * @return bool 操作结果
 * @note 检测交流过压脱离(交流过压关机)状态
 */
bool yyln_get_module_ac_overVoltageClose(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->ac_overVoltageClose[module_addr - 1];
    return true;
}

// 9. uint8_t pfcBus_overVoltage[YYLN_MODULE_NUM] - PFC 母线过压
/**
 * @brief 读取模块PFC母线过压状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=PFC母线过压
 * @return bool 操作结果
 * @note 检测PFC母线电压是否过高
 */
bool yyln_get_module_pfcBus_overVoltage(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->pfcBus_overVoltage[module_addr - 1];
    return true;
}

// 10. uint8_t pfcBus_underVoltage[YYLN_MODULE_NUM] - PFC 母线欠压
/**
 * @brief 读取模块PFC母线欠压状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=PFC母线欠压
 * @return bool 操作结果
 * @note 检测PFC母线电压是否过低
 */
bool yyln_get_module_pfcBus_underVoltage(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->pfcBus_underVoltage[module_addr - 1];
    return true;
}

// 11. uint8_t pfcBus_unbalance[YYLN_MODULE_NUM] - PFC 母线不平衡
/**
 * @brief 读取模块PFC母线不平衡状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=PFC母线不平衡
 * @return bool 操作结果
 * @note 检测PFC母线电压是否不平衡
 */
bool yyln_get_module_pfcBus_unbalance(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->pfcBus_unbalance[module_addr - 1];
    return true;
}

// 12. uint8_t dc_overVoltage[YYLN_MODULE_NUM] - 直流输出过压
/**
 * @brief 读取模块直流输出过压状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=直流输出过压
 * @return bool 操作结果
 * @note 检测直流输出电压是否超过设定的安全范围
 */
bool yyln_get_module_dc_overVoltage(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dc_overVoltage[module_addr - 1];
    return true;
}

// 13. uint8_t dc_overVoltageClose[YYLN_MODULE_NUM] - 直流过压关机
/**
 * @brief 读取模块直流过压关机状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=直流过压关机
 * @return bool 操作结果
 * @note 检测直流过压关机状态
 */
bool yyln_get_module_dc_overVoltageClose(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dc_overVoltageClose[module_addr - 1];
    return true;
}

// 14. uint8_t dc_underVoltage[YYLN_MODULE_NUM] - 直流输出欠压
/**
 * @brief 读取模块直流输出欠压状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=直流输出欠压
 * @return bool 操作结果
 * @note 检测直流输出电压是否低于设定范围
 */
bool yyln_get_module_dc_underVoltage(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dc_underVoltage[module_addr - 1];
    return true;
}

// 15. uint8_t fan_stop[YYLN_MODULE_NUM] - 风扇不运行
/**
 * @brief 读取模块风扇停止状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=风扇停止
 * @return bool 操作结果
 * @note 检测散热风扇是否停止运行
 */
bool yyln_get_module_fan_stop(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->fan_stop[module_addr - 1];
    return true;
}

// 16. uint8_t fan_driverFaild[YYLN_MODULE_NUM] - 风扇驱动电路损坏
/**
 * @brief 读取模块风扇驱动电路故障状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=风扇驱动电路故障
 * @return bool 操作结果
 * @note 检测风扇驱动电路是否损坏
 */
bool yyln_get_module_fan_driverFaild(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->fan_driverFaild[module_addr - 1];
    return true;
}

// 17. uint8_t overTemple[YYLN_MODULE_NUM] - 环境过温
/**
 * @brief 读取模块环境过温状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=环境过温
 * @return bool 操作结果
 * @note 检测模块环境温度是否过高
 */
bool yyln_get_module_overTemple(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->overTemple[module_addr - 1];
    return true;
}

// 18. uint8_t underTempl[YYLN_MODULE_NUM] - 环境温度过低
/**
 * @brief 读取模块环境温度过低状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=环境温度过低
 * @return bool 操作结果
 * @note 检测环境温度是否过低
 */
bool yyln_get_module_underTempl(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->underTempl[module_addr - 1];
    return true;
}

// 19. uint8_t pfc_overTempleProtection[YYLN_MODULE_NUM] - PFC 过温保护 1
/**
 * @brief 读取模块PFC过温保护状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=PFC过温保护
 * @return bool 操作结果
 * @note 检测PFC过温保护是否激活
 */
bool yyln_get_module_pfc_overTempleProtection(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->pfc_overTempleProtection[module_addr - 1];
    return true;
}

// 20. uint8_t relay_faild[YYLN_MODULE_NUM] - 输出继电器故障
/**
 * @brief 读取模块输出继电器故障状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=输出继电器故障
 * @return bool 操作结果
 * @note 检测输出继电器是否故障
 */
bool yyln_get_module_relay_faild(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->relay_faild[module_addr - 1];
    return true;
}

// 21. uint8_t dc_overTempleProtection[YYLN_MODULE_NUM] - DC 过温保护 1
/**
 * @brief 读取模块DC过温保护状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=DC过温保护
 * @return bool 操作结果
 * @note 检测DC过温保护是否激活
 */
bool yyln_get_module_dc_overTempleProtection(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dc_overTempleProtection[module_addr - 1];
    return true;
}

// 22. uint8_t dcdc_pfc_comFaild[YYLN_MODULE_NUM] - PFC 与 DCDC 通信故障
/**
 * @brief 读取模块PFC与DCDC通信故障状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=PFC与DCDC通信故障
 * @return bool 操作结果
 * @note 检测PFC与DCDC之间的通信是否故障
 */
bool yyln_get_module_dcdc_pfc_comFaild(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dcdc_pfc_comFaild[module_addr - 1];
    return true;
}

// 23. uint8_t pfc_faild[YYLN_MODULE_NUM] - PFC 故障
/**
 * @brief 读取模块PFC故障状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=PFC故障
 * @return bool 操作结果
 * @note 检测PFC电路是否故障
 */
bool yyln_get_module_pfc_faild(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->pfc_faild[module_addr - 1];
    return true;
}

// 24. uint8_t dcdc_faile[YYLN_MODULE_NUM] - DCDC 故障
/**
 * @brief 读取模块DCDC故障状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=DCDC故障
 * @return bool 操作结果
 * @note 检测DCDC电路是否故障
 */
bool yyln_get_module_dcdc_faile(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dcdc_faile[module_addr - 1];
    return true;
}

// 25. uint8_t dcdc_noWork[YYLN_MODULE_NUM] - DCDC 不运行
/**
 * @brief 读取模块DCDC不运行状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=DCDC不运行
 * @return bool 操作结果
 * @note 检测DCDC是否不运行
 */
bool yyln_get_module_dcdc_noWork(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dcdc_noWork[module_addr - 1];
    return true;
}

// 26. uint8_t outState[YYLN_MODULE_NUM] - 输出环路状态
/**
 * @brief 读取模块输出环路状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针
 * @return bool 操作结果
 * @note 读取输出环路状态
 */
bool yyln_get_module_outState(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->outState[module_addr - 1];
    return true;
}

// 27. uint8_t dc_voltageUnbalance[YYLN_MODULE_NUM] - DC 输出电压不平衡
/**
 * @brief 读取模块DC输出电压不平衡状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=DC输出电压不平衡
 * @return bool 操作结果
 * @note 检测DC输出电压是否不平衡
 */
bool yyln_get_module_dc_voltageUnbalance(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->dc_voltageUnbalance[module_addr - 1];
    return true;
}

// 28. uint8_t same_sn[YYLN_MODULE_NUM] - 发现相同序列号的模块
/**
 * @brief 读取模块相同序列号状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=发现相同序列号的模块
 * @return bool 操作结果
 * @note 检测是否发现相同序列号的模块
 */
bool yyln_get_module_same_sn(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->same_sn[module_addr - 1];
    return true;
}

// 29. uint8_t bleeder_circuitFailure[YYLN_MODULE_NUM] - 泄放电路异常
/**
 * @brief 读取模块泄放电路异常状态
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status 状态值指针，0=正常，1=泄放电路异常
 * @return bool 操作结果
 * @note 检测泄放电路是否异常
 */
bool yyln_get_module_bleeder_circuitFailure(uint8_t module_addr, uint8_t* status)
{
    if (status == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status = module_data->bleeder_circuitFailure[module_addr - 1];
    return true;
}

// 30. uint32_t v_ab[YYLN_MODULE_NUM] - 线电压 AB mV
/**
 * @brief 读取交流输入AB相间电压
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param voltage 电压值指针，单位：mV (毫伏)
 * @return bool 操作结果
 * @note 读取三相交流输入中A相与B相之间的线电压
 */
bool yyln_get_module_v_ab(uint8_t module_addr, uint32_t* voltage)
{
    if (voltage == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *voltage = module_data->v_ab[module_addr - 1];
    return true;
}

// 31. uint32_t v_bc[YYLN_MODULE_NUM] - 线电压 BC mV
/**
 * @brief 读取交流输入BC相间电压
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param voltage 电压值指针，单位：mV (毫伏)
 * @return bool 操作结果
 * @note 读取三相交流输入中B相与C相之间的线电压
 */
bool yyln_get_module_v_bc(uint8_t module_addr, uint32_t* voltage)
{
    if (voltage == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *voltage = module_data->v_bc[module_addr - 1];
    return true;
}

// 32. uint32_t v_ca[YYLN_MODULE_NUM] - 线电压 CA mV
/**
 * @brief 读取交流输入CA相间电压
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param voltage 电压值指针，单位：mV (毫伏)
 * @return bool 操作结果
 * @note 读取三相交流输入中C相与A相之间的线电压
 */
bool yyln_get_module_v_ca(uint8_t module_addr, uint32_t* voltage)
{
    if (voltage == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *voltage = module_data->v_ca[module_addr - 1];
    return true;
}

// 33. uint32_t air_intake_temple[YYLN_MODULE_NUM] - 进风口温度 毫度
/**
 * @brief 读取模块进风口温度
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param temperature 温度值指针，单位：毫度 (0.001°C)
 * @return bool 操作结果
 * @note 读取模块进风口温度，用于温度监控
 */
bool yyln_get_module_air_intake_temple(uint8_t module_addr, uint32_t* temperature)
{
    if (temperature == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *temperature = module_data->air_intake_temple[module_addr - 1];
    return true;
}

// 34. uint32_t module_group[YYLN_MODULE_NUM] - 模块组号
/**
 * @brief 读取指定模块的组号
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param group 组号指针
 * @return bool 操作结果
 * @note 读取模块当前配置的组号
 */
bool yyln_get_module_module_group(uint8_t module_addr, uint32_t* group)
{
    if (group == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *group = module_data->module_group[module_addr - 1];
    return true;
}

// 35. uint32_t work_mode[YYLN_MODULE_NUM] - 读取模块实际的高低压档位状态（1：1000V 2：500V ）
/**
 * @brief 读取模块工作模式
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param work_mode 工作模式指针，1=1000V高压模式，2=500V低压模式
 * @return bool 操作结果
 * @note 读取模块实际的高低压档位状态
 */
bool yyln_get_module_work_mode(uint8_t module_addr, uint32_t* work_mode)
{
    if (work_mode == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *work_mode = module_data->work_mode[module_addr - 1];
    return true;
}

bool yyln_get_module_trueHiLo_Status(uint8_t module_addr, uint32_t* work_mode)
{
    if (work_mode == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *work_mode = module_data->trueHiLo_Status[module_addr - 1];
    return true;
}

// 36. uint32_t module_max_curr[YYLN_MODULE_NUM] - 读取模块输出电流能力 单位：mA
/**
 * @brief 读取模块最大输出电流能力
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param max_current 最大电流能力指针，单位：mA (毫安)
 * @return bool 操作结果
 * @note 读取模块输出电流能力
 */
bool yyln_get_module_module_max_curr(uint8_t module_addr, uint32_t* max_current)
{
    if (max_current == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *max_current = module_data->module_max_curr[module_addr - 1];
    return true;
}

// 37. uint32_t iout1[YYLN_MODULE_NUM] - 读取模块输出电流 单位：0.1A
/**
 * @brief 读取模块输出电流（0.1A单位）
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param current 电流值指针，单位：0.1A
 * @return bool 操作结果
 * @note 读取模块输出电流，精度为0.1A
 */
bool yyln_get_module_iout1(uint8_t module_addr, uint32_t* current)
{
    if (current == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *current = module_data->iout1[module_addr - 1];
    return true;
}

// 38. uint32_t module_max_curr1[YYLN_MODULE_NUM] - 读取模块输出功率能力 单位：0.1A
/**
 * @brief 读取模块输出功率能力
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param power_capability 功率能力指针，单位：0.1A
 * @return bool 操作结果
 * @note 读取模块输出功率能力
 */
bool yyln_get_module_module_max_curr1(uint8_t module_addr, uint32_t* power_capability)
{
    if (power_capability == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *power_capability = module_data->module_max_curr1[module_addr - 1];
    return true;
}

/**
 * @brief 读取模块PFC热点温度
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param temperature 温度值指针，单位：毫度 (0.001°C)
 * @return bool 操作结果
 * @note 读取模块PFC热点温度，用于温度监控
 */
bool yyln_get_module_pfc_temp(uint8_t module_addr, uint32_t* temperature)
{
    if (temperature == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *temperature = module_data->pfcTemp[module_addr - 1];
    return true;
}

/**
 * @brief 读取模块DCDC热点温度
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param temperature 温度值指针，单位：毫度 (0.001°C)
 * @return bool 操作结果
 * @note 读取模块DCDC热点温度，用于温度监控
 */
bool yyln_get_module_dcdc_temp(uint8_t module_addr, uint32_t* temperature)
{
    if (temperature == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *temperature = module_data->dcdcTemp[module_addr - 1];
    return true;
}

/**
 * @brief 读取模块状态映射表
 * @param module_addr 模块地址 (1 ~ YYLN_MODULE_NUM)
 * @param status_map 状态映射表指针
 * @return bool 操作结果
 * @note 读取模块的完整状态映射表
 */
bool yyln_get_module_status_map(uint8_t module_addr, uint32_t* status_map)
{
    if (status_map == NULL)
    {
        return false;
    }
    if (!yyln_module_addr_is_available(module_addr))
    {
        return false;
    }

    yyln_module_data_t* module_data = yyln_get_module_data();
    *status_map = module_data->status[module_addr - 1];
    return true;
}

/**
 * @brief 模块检查
 * @note 发送读取模块电流能力命令，用于检测模块是否正常工作
 */
void yyln_module_check(void)
{
    yyln_send_read_current_capability(1);
}

/**
 * @brief 检查模块是否正常工作
 * @return bool 操作结果
 * @retval true 模块正常工作
 * @retval false 模块未正常工作
 */
bool yyln_module_ok(void)
{
    uint32_t current = 0;
    yyln_get_module_module_max_curr(1, &current);
    if (current > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
