/**
 * @file module.c
 * @brief 模块管理主文件
 * @details 提供模块初始化、CAN通信、数据查询和处理功能
 *
 * @version 1.0
 */

#include "module.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "can.h"
#include "heartbeat.h"
#include "app.h"
#include "status.h"



QueueHandle_t moduleQueue = NULL;

module_num_info_t module_num_info = {0};

/**
 * @brief CAN发送回调函数
 * @details 通过CAN总线发送电源模块数据
 * @param[in] id CAN消息ID
 * @param[in] pdata 数据指针（8字节）
 * @return bool 发送结果
 * @retval true 发送成功
 * @retval false 发送失败
 */
bool module_data_send(uint32_t id, uint8_t* pdata)
{
    CanMsgTypeDef can_msg;
    can_msg.IDE = CAN_ID_EXTENDED;
    can_msg.ExtId = id;
    can_msg.DLC = 8;
    memcpy(can_msg.Data, pdata, 8);
    //其他配置已经在驱动中设置好了
    if (can_send(ACDC_CAN, &can_msg) == -1)
    {
        return false;
    }
    return true;
}

/**
 * @brief CAN接收回调函数
 * @details 从CAN接收队列中获取电源模块数据
 * @param[out] id CAN消息ID指针
 * @param[out] pdata 数据指针（8字节）
 * @return bool 接收结果
 * @retval true 接收成功
 * @retval false 接收失败或队列为空
 */
bool module_can_recv(uint32_t* id, uint8_t* pdata)
{
    CanMsgTypeDef can_msg;
    //获取队列数据
    if (xQueueReceive(moduleQueue, &can_msg, 0) == pdFAIL)
    {
        return false;
    }
    *id = can_msg.ExtId;
    memcpy(pdata, can_msg.Data, 8);
    return true;
}

/**
 * @brief 英飞源模块查询
 * @details 定时发送指令查询英飞源模块的电压、电流、组号、状态和温度等信息
 *          - 电压、电流：200ms查询一次
 *          - 组号、状态、温度：2000ms查询一次
 *          - 交流输入电压：1000ms查询一次
 */
void yfy_module_query(void);

/**
 * @brief 获取系统时间回调函数
 * @details 获取FreeRTOS系统Tick计数
 * @return uint32_t 系统Tick值
 */
uint32_t module_get_time(void)
{
    return xTaskGetTickCount();
}

/**
 * @brief 电源模块CAN中断回调函数
 * @details 将CAN接收到的数据发送到处理队列
 * @param[in] _name CAN名称
 * @param[in] _flag 标志
 * @param[in] data CAN消息数据指针
 */
void module_can_interrupt_call(CanName _name, uint8_t _flag, CanMsgTypeDef* data)
{
    (void)_name;
    (void)_flag;
    xQueueSendToBackFromISR(moduleQueue, (void*)data, NULL);
}

/**
 * @brief 电源模块初始化
 * @details 初始化电源模块，创建CAN接收队列，配置CAN驱动，初始化模块上下文
 * @param[in] module_num 模块数量
 * @param[in] group_num 组数量
 * @param[in] module_type 模块类型（英飞源或英优能源）
 */
void module_init(uint32_t module_num, uint32_t group_num, module_type_t module_type)
{
    module_num_info.module_num = module_num;
    module_num_info.group_num = group_num;

    //10条缓存
    moduleQueue = xQueueCreate(24, sizeof(CanMsgTypeDef));
    can_asyn_init(ACDC_CAN, 125, module_can_interrupt_call);

    module_context_init(module_type);

    if(module_type == eModuleTypeYfy)
    {
        yfy_module_handle_init(module_data_send, module_can_recv, module_get_time);
    }
    else if(module_type == eModuleTypeYyln)
    {
        yyln_module_handle_init(module_data_send, module_can_recv, module_get_time);
    }

}

/**
 * @brief 英飞源模块查询
 * @details 定时发送指令查询英飞源模块的电压、电流、组号、状态和温度等信息
 *          - 电压、电流：200ms查询一次
 *          - 组号、状态、温度：2000ms查询一次
 *          - 交流输入电压：1000ms查询一次
 */
void yfy_module_query(void)
{
    static uint32_t voltage_current_timestamp = 0;
    static uint32_t group_num_timestamp = 0;
    static uint32_t status_timestamp = 0;
    static uint32_t group_data_module_num_timestamp = 0;
    static uint32_t group_data_out_volt_current_timestamp = 0;
    uint32_t current_time = xTaskGetTickCount();

    // 发送指令，查询模块输出电压、输出电流 - 200ms运行一次
    if ((current_time - voltage_current_timestamp) >= pdMS_TO_TICKS(200))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yfy_send_read_group_output(i + 1);
        }
        voltage_current_timestamp = current_time;
    }

    // 发送指令，查询模块组号、状态表1-3、温度 - 2000ms运行一次
    if ((current_time - group_num_timestamp) >= pdMS_TO_TICKS(2000))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yfy_send_read_single_info_1_by_group(i + 1);
        }
        group_num_timestamp = current_time;
    }

    // 发送指令，查询交流输入电压AB、BC、CA - 1000ms运行一次
    if ((current_time - status_timestamp) >= pdMS_TO_TICKS(1000))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yfy_send_read_single_info_2_by_group(i + 1);
        }
        status_timestamp = current_time;
    }

    // 发送指令，查询模块组内的模块数量
    if ((current_time - group_data_module_num_timestamp) >= pdMS_TO_TICKS(1500))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yfy_send_read_group_module_num(i + 1);
        }
        group_data_module_num_timestamp = current_time;
    }

    // 发送指令，查询模块组内的电压电流输出
    if ((current_time - group_data_out_volt_current_timestamp) >= pdMS_TO_TICKS(1500))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yfy_send_read_group_output(i + 1);
        }
        group_data_out_volt_current_timestamp = current_time;
    }
}

/**
 * @brief 优优绿能模块查询
 * @details 定时发送指令查询优优绿能模块的电压、电流、组号、状态和温度等信息
 *          - 电压、电流：200ms查询一次
 *          - 组号、交流输入电压：2000ms查询一次
 *          - 模块状态：1000ms查询一次
 */
void yyln_module_query(void)
{
    static uint32_t voltage_current_timestamp = 0;
    static uint32_t group_num_timestamp = 0;
    static uint32_t status_timestamp = 0;
    uint32_t current_time = xTaskGetTickCount();

    // 发送指令，查询模块输出电压、输出电流 - 80ms运行一次
    if ((current_time - voltage_current_timestamp) >= pdMS_TO_TICKS(200))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yyln_send_read_vout_by_group(i + 1);
            yyln_send_read_iout_by_group(i + 1);
        }
        voltage_current_timestamp = current_time;
    }

    // 发送指令，查询模块组号 - 2000ms运行一次
    if ((current_time - group_num_timestamp) >= pdMS_TO_TICKS(2000))
    {
        for(uint8_t i = 0; i < MODULE_NUM; i++)
        {
            yyln_send_read_group_num(i + 1);
            yyln_send_read_ab_voltage(i + 1);
        }
        group_num_timestamp = current_time;
    }

    // 发送指令，查询模块状态表 - 1000ms运行一次
    if ((current_time - status_timestamp) >= pdMS_TO_TICKS(1000))
    {
        for(uint8_t i = 0; i < GROUP_MODULE_NUM; i++)
        {
            yyln_send_read_module_status_by_group(i + 1);
        }
        status_timestamp = current_time;
    }
}

void module_data_process(void)
{
    PowerContext* p = power_ctrl();
    if(strcmp(p->module_name, "yfy") == 0)
    {
        yfy_process_data();
    }
    else
    {
        yyln_process_data();
    }
}

void module_data_query(void)
{
    PowerContext* p = power_ctrl();
    if(strcmp(p->module_name, "yfy") == 0)
    {
        yfy_module_query();
    }
    else
    {
        yyln_module_query();
    }
}
