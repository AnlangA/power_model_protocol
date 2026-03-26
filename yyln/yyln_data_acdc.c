#include "yyln_data_acdc.h"
#include "string.h"
#include "macro_acdc.h"
#include <stdint.h>

// 静态函数声明
static bool yyln_data_parse(uint32_t id, uint8_t* pdata);
static bool yyln_data_unpack(yyln_message_type_e message_type, yyln_message_cmd_e message_cmd, yyln_message_cmd127_sub_cmd_e sub_cmd, uint8_t module_addr, uint8_t* pdata);
static void yyln_data_store(uint8_t byte_start, uint8_t byte_end, uint8_t bit_start, uint8_t bit_end, uint8_t addr, uint8_t* pdata, void* pstore_data);


#define MODULE_OFFLINE_TIME 5000 // 模块离线超时时间(ms)

yyln_module_online_info_t yyln_module_online_info[YYLN_MODULE_NUM] = {0};

// 模块数据
yyln_module_data_t yyln_moudle_data = {0};

yyln_single_module_info_t yyln_single_module_info[] = {
    {.message_type = yyln_SetDataResponse,
     .message_cmd = yyln_VoutReference,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.v_set[0]},
    {.message_type = yyln_SetDataResponse,
     .message_cmd = yyln_IoutLimit,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.i_set[0]},
    {.message_type = yyln_SetDataResponse,
     .message_cmd = yyln_GroupAddress,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.module_group[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Vout,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.vout[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Iout_slow,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.iout[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_VoutReference,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.v_set[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_IoutLimit,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.i_set[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ReadSN,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.sn[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 1,
     .pdata = &yyln_moudle_data.ac_overVoltage[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 1,
     .bit_end = 2,
     .pdata = &yyln_moudle_data.ac_underVoltage[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 2,
     .bit_end = 3,
     .pdata = &yyln_moudle_data.ac_overVoltageClose[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 3,
     .bit_end = 4,
     .pdata = &yyln_moudle_data.pfcBus_overVoltage[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 4,
     .bit_end = 5,
     .pdata = &yyln_moudle_data.pfcBus_underVoltage[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 5,
     .bit_end = 6,
     .pdata = &yyln_moudle_data.pfcBus_unbalance[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 6,
     .bit_end = 7,
     .pdata = &yyln_moudle_data.dc_overVoltage[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 7,
     .bit_end = 8,
     .pdata = &yyln_moudle_data.dc_overVoltageClose[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 8,
     .bit_end = 9,
     .pdata = &yyln_moudle_data.dc_underVoltage[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 9,
     .bit_end = 10,
     .pdata = &yyln_moudle_data.fan_stop[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 11,
     .bit_end = 12,
     .pdata = &yyln_moudle_data.fan_driverFaild[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 12,
     .bit_end = 13,
     .pdata = &yyln_moudle_data.overTemple[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 13,
     .bit_end = 14,
     .pdata = &yyln_moudle_data.underTempl[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 14,
     .bit_end = 15,
     .pdata = &yyln_moudle_data.pfc_overTempleProtection[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 15,
     .bit_end = 16,
     .pdata = &yyln_moudle_data.relay_faild[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 16,
     .bit_end = 17,
     .pdata = &yyln_moudle_data.dc_overTempleProtection[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 18,
     .bit_end = 19,
     .pdata = &yyln_moudle_data.dcdc_pfc_comFaild[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 20,
     .bit_end = 21,
     .pdata = &yyln_moudle_data.pfc_faild[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 21,
     .bit_end = 22,
     .pdata = &yyln_moudle_data.dcdc_faile[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 25,
     .bit_end = 26,
     .pdata = &yyln_moudle_data.dcdc_noWork[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 26,
     .bit_end = 28,
     .pdata = &yyln_moudle_data.outState[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 28,
     .bit_end = 29,
     .pdata = &yyln_moudle_data.dc_voltageUnbalance[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 29,
     .bit_end = 30,
     .pdata = &yyln_moudle_data.same_sn[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_ModuleStatus,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 31,
     .bit_end = 32,
     .pdata = &yyln_moudle_data.bleeder_circuitFailure[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Vab,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.v_ab[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Vbc,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.v_bc[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Vca,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.v_ca[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Tin,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.air_intake_temple[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_GroupAddress,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.module_group[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_HiMode_LoMode_Status,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.work_mode[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_CurrentCapability,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.module_max_curr[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_CurrentAndCapability,
     .byte_start = 4u,
     .byte_end = 6u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.iout1[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_CurrentAndCapability,
     .byte_start = 6u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.module_max_curr1[0]},
    {.message_type = yyln_ReadDataResponse,
     .message_cmd = yyln_Tpfc1,
     .byte_start = 4u,
     .byte_end = 8u,
     .bit_start = 0,
     .bit_end = 0,
     .pdata = &yyln_moudle_data.pfcTemp[0]},
     {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_Tdcdc2,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.dcdcTemp[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_BatteryVoltage,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.batteryVoltage[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_PowerFactor,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.powerFactor[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_DcSoftwareVersion,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.dcSoftwareVersion[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_PfcSoftwareVersion,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.pfcSoftwareVersion[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_TrueHiLo_Status,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.trueHiLo_Status[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_CommandType127,
        .sub_cmd = yyln_cmd127_BidirectionalModeSet,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.bidirectionalStatus[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_CommandType127,
        .sub_cmd = yyln_cmd127_BidirectionalModeStatus,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.dischargeCurrentLimitSetValue[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_CommandType127,
        .sub_cmd = yyln_cmd127_IDcDischargeLimit,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.dischargeCurrentLimitSetValue[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_CommandType127,
        .sub_cmd = yyln_cmd127_IDcDischarge,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.dischargeCurrent[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_CommandType127,
        .sub_cmd = yyln_cmd127_IDcDischargeFast,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.dischargeCurrentFast[0]},
    {
        .message_type = yyln_ReadDataResponse,
        .message_cmd = yyln_CommandType127,
        .sub_cmd = yyln_cmd127_DischargeOffGridParalleEnable,
        .byte_start = 4u,
        .byte_end = 8u,
        .bit_start = 0,
        .bit_end = 0,
        .pdata = &yyln_moudle_data.offGridParallelEnable[0]},
};

yyln_module_handle_t yyln_module_handle = {0};

yyln_module_handle_t* yyln_module_handle_get(void)
{
    return &yyln_module_handle;
}

void yyln_module_handle_init(bool (*send)(uint32_t id, uint8_t* pdata), bool (*recv)(uint32_t* id, uint8_t* pdata), uint32_t (*time)(void))
{
    yyln_module_handle.recv = recv;
    yyln_module_handle.send = send;
    yyln_module_handle.time = time;
}

/**
 * @file yyln_data_acdc.c
 * @brief 优优绿能模块数据管理实现
 * @details 实现优优绿能模块的数据解析、存储、在线检测等功能
 * @author [作者名]
 * @date [日期]
 * @version 1.0
 */

/**
 * @brief YYLN协议接收数据主任务
 * @details 处理接收到的CAN消息，解析数据并更新模块信息
 */
void yyln_process_data(void)
{
    yyln_module_handle_t* handle = yyln_module_handle_get();
    if (handle->recv == NULL)
    {
        return;
    }

    uint32_t id = 0;
    uint8_t pdata[8] = {0};

    // 模块在线状态检查
    yyln_module_online_check();

    // 处理接收到的数据包，最多处理10个
    for (int max_handle_count = 24; max_handle_count > 0; max_handle_count--)
    {
        if (handle->recv(&id, pdata))
        {
            yyln_data_parse(id, pdata);
        }
        else
        {
            break;
        }
    }
}

/**
 * @brief 解析收到的YYLN协议数据
 * @param id CAN ID
 * @param pdata 数据指针
 * @return 解析是否成功
 */
static bool yyln_data_parse(uint32_t id, uint8_t* pdata)
{
    // 从CAN ID中提取字段
    uint8_t protocol = YYLN_EXTRACT_PROTOCOL(id);
    uint8_t module_addr = YYLN_EXTRACT_MODULE_ADDR(id);
    uint8_t index = module_addr - 1; // 数组索引从0开始，模块地址从1开始
    // 检查协议号是否正确
    if (protocol != 0x01)
    {
        return false;
    }

    // 检查模块地址范围
    if (module_addr > YYLN_MODULE_NUM)
    {
        return false;
    }

    // 从数据包中提取消息类型、命令和子命令（当命令为127时有效）
    yyln_message_type_e message_type = (yyln_message_type_e) (pdata[0] & 0x0F);
    yyln_message_cmd_e message_cmd = (yyln_message_cmd_e) pdata[1];
    // 仅当命令为 127(yyln_CommandType127) 时，pdata[2..3] 为 sub_cmd（u16）
    yyln_message_cmd127_sub_cmd_e sub_cmd = (yyln_message_cmd127_sub_cmd_e)0;
    if (message_cmd == yyln_CommandType127) {
        uint16_t sub16 = 0;
        memcpy(&sub16, pdata + 2, sizeof(sub16));
        sub_cmd = (yyln_message_cmd127_sub_cmd_e) sub16;
    }

    // 只有收到模块的响应消息才更新在线状态（不包括发送的命令）
    // 模块地址0表示广播，不记录在线状态；有效模块地址从1开始
    if (module_addr > 0 && module_addr <= YYLN_MODULE_NUM)
    {
        yyln_module_handle_t* handle = yyln_module_handle_get();

        yyln_module_online_info[index].last_online_time = handle->time();
        yyln_module_online_info[index].is_online = true;
    }

    // 如果是模块状态命令，额外保存4~7字节为完整状态值
    if (message_cmd == yyln_ModuleStatus)
    {
        uint8_t temp_data[4];
        CONVERT_ENDIANNESS(pdata + 4, temp_data, 4);
        memcpy(&yyln_moudle_data.status[index], temp_data, 4);
    }

    // 解包数据
    return yyln_data_unpack(message_type, message_cmd, sub_cmd, module_addr, pdata);
}

/**
 * @brief 解包YYLN协议数据到对应的数据结构
 * @param message_type 消息类型
 * @param message_cmd 消息命令
 * @param module_addr 模块地址
 * @param pdata 数据指针
 * @return 解包是否成功
 */
static bool yyln_data_unpack(yyln_message_type_e message_type, yyln_message_cmd_e message_cmd, yyln_message_cmd127_sub_cmd_e sub_cmd, uint8_t module_addr, uint8_t* pdata)
{
    uint8_t start_parse = 1;
    uint8_t on_parse = 2;
    uint8_t end_parse = 3;
    uint8_t parse_state = start_parse;

    // 遍历单模块信息表，查找匹配的消息类型、命令（以及必要时的子命令）
    for (uint8_t i = 0; i < sizeof(yyln_single_module_info) / sizeof(yyln_single_module_info[0]); i++)
    {
        bool match = false;

        // 基本匹配：消息类型和命令必须匹配
        if (yyln_single_module_info[i].message_type == message_type &&
            yyln_single_module_info[i].message_cmd == message_cmd)
        {
            // 如果是 CommandType127，还需要匹配 sub_cmd
            if (message_cmd == yyln_CommandType127)
            {
                if (yyln_single_module_info[i].sub_cmd == sub_cmd)
                {
                    match = true;
                }
            }
            else
            {
                // 非 CommandType127 的命令，不需要匹配 sub_cmd
                match = true;
            }
        }

        if (match)
        {
            // 找到匹配项，存储数据
            yyln_data_store(yyln_single_module_info[i].byte_start, yyln_single_module_info[i].byte_end, yyln_single_module_info[i].bit_start,
                            yyln_single_module_info[i].bit_end, module_addr, pdata, yyln_single_module_info[i].pdata);

            if (parse_state == start_parse)
            {
                parse_state = on_parse;
            }
        }
        else if (parse_state == on_parse)
        {
            // 已经处理完所有匹配项
            parse_state = end_parse;
            break;
        }
    }

    if (parse_state == end_parse)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief 存储数据到指定位置
 * @param byte_start 起始字节位置
 * @param byte_end 结束字节位置
 * @param bit_start 起始位位置
 * @param bit_end 结束位位置
 * @param addr 模块地址
 * @param pdata 源数据指针
 * @param pstore_data 目标存储指针
 */
static void yyln_data_store(uint8_t byte_start, uint8_t byte_end, uint8_t bit_start, uint8_t bit_end, uint8_t addr, uint8_t* pdata, void* pstore_data)
{
    if (bit_end != bit_start)
    {
        // 位域数据处理。只有yyln_ModuleStatus会触发这个分支
        uint8_t temp_data[4];
        uint32_t data = 0;
        CONVERT_ENDIANNESS(pdata + 4, temp_data, 4);
        memcpy(&data, temp_data, 4);
        uint8_t bit_mask = (1 << (bit_end - bit_start)) - 1;
        uint8_t need_data = (uint8_t)((data >> bit_start) & bit_mask);
        ((uint8_t*) pstore_data)[addr - 1] = need_data;
    }
    else
    {
        // 多字节数据处理
        uint8_t bytes = byte_end - byte_start;
        //模块地址从1开始
        uint8_t* p_data = (uint8_t*) pstore_data + ((addr - 1) * bytes);

        // 当字节数大于1时，进行字节序转换（Big Endian -> Little Endian）
        if (bytes > 1)
        {
            // 创建临时缓冲区进行字节序转换（最大支持8字节）
            uint8_t temp_data[8];
            CONVERT_ENDIANNESS(pdata + byte_start, temp_data, bytes);
            memcpy(p_data, temp_data, bytes);
        }
        else
        {
            // 单字节数据不需要转换
            memcpy(p_data, pdata + byte_start, bytes);
        }
    }
}

/**
 * @brief 检查模块在线状态超时
 * @note 此函数只负责检查已在线模块是否超时离线，不负责更新在线状态
 *       在线状态的更新只在接收到模块响应消息时进行
 */
void yyln_module_online_check(void)
{
    static uint32_t last_check_time = 0;
    yyln_module_handle_t* handle = yyln_module_handle_get();

    if (handle->time == NULL)
    {
        return;
    }

    uint32_t current_time = handle->time();
    uint32_t check_interval_diff;

    // 计算距离上次检查的时间差（处理溢出）
    if (current_time >= last_check_time)
    {
        check_interval_diff = current_time - last_check_time;
    }
    else
    {
        // 处理32位时间溢出
        check_interval_diff = (UINT32_MAX - last_check_time) + current_time + 1;
    }

    // 每1000ms执行一次超时检查
    if (check_interval_diff >= 1000)
    {
        last_check_time = current_time;

        // 只检查已标记为在线的模块是否超时
        for (uint8_t i = 0; i < YYLN_MODULE_NUM; i++)
        {
            if (yyln_module_online_info[i].is_online)
            {
                uint32_t last_time = yyln_module_online_info[i].last_online_time;
                uint32_t time_diff;

                // 处理32位时间溢出情况
                if (current_time >= last_time)
                {
                    // 正常情况：当前时间大于等于上次在线时间
                    time_diff = current_time - last_time;
                }
                else
                {
                    // 溢出情况：当前时间小于上次在线时间（时间戳已溢出）
                    // 计算跨越溢出点的时间差
                    time_diff = (UINT32_MAX - last_time) + current_time + 1;
                }

                // 检查是否超过离线超时时间，如果超时则标记为离线
                if (time_diff >= MODULE_OFFLINE_TIME)
                {
                    yyln_module_online_info[i].is_online = false;
                }
            }
        }
    }
}

/**
 * @brief 获取模块数据指针
 * @return 模块数据指针
 */
yyln_module_data_t* yyln_get_module_data(void)
{
    return &yyln_moudle_data;
}

/**
 * @brief 获取模块在线信息指针
 * @return 模块在线信息指针
 */
bool yyln_get_module_online_info(uint8_t module_addr)
{
    if((module_addr == 0) | (module_addr > YYLN_MODULE_NUM))
    {
        return false;
    }

    if(yyln_module_online_info[module_addr -1].is_online)
    {
        return true;
    }
    else
    {
        return false;
    }
}



/**
 * @brief 发送YYLN协议读取命令
 * @param module_addr 模块地址
 * @param message_type 消息类型
 * @param message_cmd 消息命令
 */
void yyln_send_read_cmd(uint8_t module_addr, uint8_t group, yyln_message_type_e message_type, yyln_message_cmd_e message_cmd)
{
    // 组装CAN ID
    uint32_t can_id = YYLN_SET_ID(0x01, YYLN_MONITOR_ADDR, module_addr, 0u, 0u);

    // 获取发送句柄
    yyln_module_handle_t* handle = yyln_module_handle_get();

    uint8_t send_data[8] = {0};
    // group站7:4,message_type站3:0
    send_data[0] = (group << 4) | (message_type & 0x0F);
    send_data[1] = (uint8_t) message_cmd;

    // 检查发送函数是否已初始化
    if (handle != NULL && handle->send != NULL)
    {
        // 调用发送函数
        handle->send(can_id, send_data);
    }
}

/**
 * @brief 发送YYLN协议写入命令
 * @param module_addr 模块地址
 * @param group 组地址
 * @param message_type 消息类型
 * @param message_cmd 消息命令
 * @param data 用户数据（32位，本地字节序）
 * @note 数据包格式：
 *       byte0: group(7:4) | message_type(3:0)
 *       byte1: 消息命令
 *       byte2-3: 保留（0x00）
 *       byte4-7: 用户数据（自动转换为Big Endian格式）
 * @example 设置5000mV: data = 5000
 */
void yyln_send_write_cmd(uint8_t module_addr, uint8_t group, yyln_message_type_e message_type, yyln_message_cmd_e message_cmd, uint32_t data)
{
    // 组装CAN ID
    uint32_t can_id = YYLN_SET_ID(0x01, YYLN_MONITOR_ADDR, module_addr, 0u, 0u);

    // 获取发送句柄
    yyln_module_handle_t* handle = yyln_module_handle_get();

    uint8_t send_data[8] = {0};
    // group站7:4,message_type站3:0
    send_data[0] = (group << 4) | (message_type & 0x0F);
    send_data[1] = (uint8_t) message_cmd;
    // byte2和byte3保留为0
    send_data[2] = 0x00;
    send_data[3] = 0x00;

    // 将32位数据转换为Big Endian格式并复制到byte4~byte7
    // 使用字节序转换宏将本地字节序转换为Big Endian（高位在低字节）
    uint8_t temp_data[4];
    CONVERT_ENDIANNESS((uint8_t*) &data, temp_data, 4);
    memcpy(&send_data[4], temp_data, 4);

    // 检查发送函数是否已初始化
    if (handle != NULL && handle->send != NULL)
    {
        // 调用发送函数
        handle->send(can_id, send_data);
    }
}
