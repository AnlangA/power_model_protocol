# 电源模块协议库 (Power Module Protocol)

本仓库实现了一套面向 AC-DC 电源模块的通用协议驱动库，支持**英飞源（YFY）**和**优优绿能（YYLN）**两种模块品牌，通过统一的抽象接口对外提供电源控制与数据查询能力。

---

## 目录结构

```
power_model_protocol/
├── macro_acdc.h          # 公共宏定义（字节序转换、常量、位操作、时间计算）
├── module_common.h       # 公共辅助函数声明
├── module_common.c       # 公共辅助函数实现（字节序转换）
├── module/               # 模块管理层
│   ├── module.h          # 模块管理头文件（数量信息、初始化与查询接口）
│   ├── module.c          # 模块管理实现
│   ├── module_context.h  # 电源上下文定义（统一抽象接口结构体）
│   └── module_context.c  # 电源上下文初始化实现
├── yfy/                  # 英飞源模块驱动
│   ├── yfy_api_acdc.h/c        # 底层 API（报文收发）
│   ├── yfy_data_acdc.h/c       # 数据层（数据解析与存储）
│   └── yfy_interface_acdc.h/c  # 接口层（对外功能函数）
└── yyln/                 # 优优绿能模块驱动
    ├── yyln_api_acdc.h/c       # 底层 API（报文收发）
    ├── yyln_data_acdc.h/c      # 数据层（数据解析与存储）
    └── yyln_interface_acdc.h/c # 接口层（对外功能函数）
```

---

## 支持的模块类型

| 枚举值            | 模块品牌   | 说明                 |
|-------------------|------------|----------------------|
| `eModuleTypeYfy`  | 英飞源     | YFY AC-DC 电源模块   |
| `eModuleTypeYyln` | 优优绿能   | YYLN AC-DC 电源模块  |

---

## 快速开始

### 1. 初始化

```c
#include "module/module.h"

// 初始化模块管理（模块总数、组总数、模块品牌类型）
module_init(8, 2, eModuleTypeYfy);
```

### 2. 获取电源控制上下文

```c
#include "module/module_context.h"

PowerContext *ctx = power_ctrl();
```

### 3. 控制模块（以组为单位）

```c
// 开机
ctx->group_module_set.power_on(0);

// 关机
ctx->group_module_set.power_off(0);

// 设置输出电压（V）和电流（A），第 4 个参数为该组当前在线模块数量
ctx->group_module_set.voltage_current_output(0, 48.0f, 20.0f, 4, MODULE_NUM);
```

### 4. 查询数据

```c
float voltage = 0.0f, current = 0.0f;

// 查询组输出电压和电流
ctx->group_module_query.voltage_current(0, &voltage, &current, MODULE_NUM);

// 查询模块是否在线
bool online = ctx->single_module_query.is_online(1, MODULE_NUM);

// 查询模块温度
float temp = 0.0f;
ctx->single_module_query.temperature(1, &temp);
```

### 5. 周期性调用数据查询与处理

```c
// 在主循环或定时任务中周期调用
module_data_query();    // 发起数据查询报文
module_data_process();  // 处理接收到的数据
```

---

## 关键常量（macro_acdc.h）

| 宏名                              | 默认值    | 说明                         |
|-----------------------------------|-----------|------------------------------|
| `MODULE_OFFLINE_TIME_MS`          | 5000 ms   | 模块离线超时时间             |
| `MODULE_MIN_OUTPUT_VOLTAGE_MV`    | 150000 mV | 判断开机状态的最低输出电压   |
| `MODULE_HV_THRESHOLD_MV`          | 500000 mV | 高压模式阈值                 |
| `MODULE_VOLTAGE_QUERY_INTERVAL_MS`| 200 ms    | 电压查询间隔                 |
| `MODULE_STATUS_QUERY_INTERVAL_MS` | 1000 ms   | 状态查询间隔                 |
| `MODULE_GROUP_QUERY_INTERVAL_MS`  | 2000 ms   | 组号查询间隔                 |
| `MODULE_EXT_QUERY_INTERVAL_MS`    | 1500 ms   | 扩展数据查询间隔             |
| `MODULE_ONLINE_CHECK_INTERVAL_MS` | 1000 ms   | 在线检查间隔                 |

---

## 统一抽象接口（PowerContext）

`PowerContext` 结构体包含以下五类接口，适配不同模块品牌：

| 接口分类              | 结构体字段             | 主要功能                             |
|-----------------------|------------------------|--------------------------------------|
| 单模块设置            | `single_module_set`    | 开关机、设置电压电流、设置组号       |
| 模块组设置            | `group_module_set`     | 组开关机、组输出电压电流设置         |
| 单模块查询            | `single_module_query`  | 电压电流、温度、在线状态、故障状态   |
| 模块组查询            | `group_module_query`   | 组电压电流、组内模块数量、组状态     |
| 系统查询              | `system_query`         | 系统总电压电流、系统模块数量         |

---

## 版本

v1.0
