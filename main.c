#include "los_task.h"
#include "los_gpio.h"
#include "los_wifi.h"
#include <stdio.h>

/* LED引脚，根据你的开发板修改 */
#define LED_PIN     5

/* WiFi信息，改成你自己的WiFi名称和密码 */
#define WIFI_SSID   "你的WiFi名字"
#define WIFI_PWD    "你的WiFi密码"

UINT32 g_ledTaskId;

// LED闪烁任务
VOID LedTask(VOID)
{
    LOS_GPIO_Init(LED_PIN, GPIO_DIR_OUT);
    LOS_GPIO_SetOutput(LED_PIN, GPIO_LEVEL_LOW);

    printf("LED任务启动，准备连接WiFi...\r\n");
    // 连接WiFi
    if(LOS_WifiConnect(WIFI_SSID, WIFI_PWD) == LOS_OK)
    {
        printf("WiFi连接成功！\r\n");
    }
    else
    {
        printf("WiFi连接失败！\r\n");
    }

    while(1)
    {
        LOS_GPIO_Toggle(LED_PIN);
        LOS_TaskDelay(500); // 500ms闪烁一次
    }
}

// 入口函数
INT32 main(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskParam = {0};

    taskParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LedTask;
    taskParam.uwStackSize  = 1024;
    taskParam.pcName       = "LedTask";
    taskParam.usTaskPrio   = 6;
    ret = LOS_TaskCreate(&g_ledTaskId, &taskParam);
    if(ret != LOS_OK)
    {
        printf("任务创建失败，错误码：%d\r\n", ret);
    }
    return LOS_OK;
}
