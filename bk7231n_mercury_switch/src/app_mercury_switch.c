#include "uni_log.h"
#include "tuya_cloud_wifi_defs.h"
#include "tuya_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uni_thread.h"

#include "app_sercury_switch.h"
#include "tuya_dp_process.h"

#define SERCURY_PORT TY_GPIOA_8
INT_T switch_state;

STATIC VOID_T get_sercury_switch_state_task(VOID_T)
{
    

    while (1) {
        switch_state = tuya_gpio_read(SERCURY_PORT);
        if (switch_state == 1) {
            PR_NOTICE("switch_state == 1");
        } else {
            PR_NOTICE("switch_state == 0");
        }
        hw_report_all_dp_status();
        tuya_hal_system_sleep(1000);
    }
}

VOID_T mercury_switch_init(VOID_T)
{
    tuya_gpio_inout_set(SERCURY_PORT, TRUE);

    tuya_hal_thread_create(NULL, "get value", 512 * 4, TRD_PRIO_4, get_sercury_switch_state_task, NULL);
}
