#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "driver/gpio.h"

#define push_gpio 0

void task1(void *p){
    while(1){

    }
    vTaskDelete(NULL);
}

void task2(void *p){
    while(1){
        printf("1752392\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task3(void *p){
    unsigned int flag = 0;
    while(1){
        if(gpio_get_level(push_gpio) != 0){
            flag = 0;
            vTaskDelay(18/portTICK_PERIOD_MS);
        }

        if (gpio_get_level(push_gpio) == 0){
            vTaskDelay(27/portTICK_PERIOD_MS);

            if (gpio_get_level(push_gpio) == 0){
                if (flag == 0){
                    printf("ESP32\n");
                    flag = 1;
                }
            }
        }
    }
    vTaskDelete(NULL);
}

void setup_push(void){
    gpio_pad_select_gpio(push_gpio);
    gpio_set_direction(push_gpio, GPIO_MODE_INPUT);
    gpio_set_pull_mode(push_gpio, GPIO_PULLDOWN_ONLY);
}

void app_main()
{
    setup_push();
    //xTaskCreate(&task1, "task1", 1024*1, (void*) 0, tskIDLE_PRIORITY + 0, NULL);
    //xTaskCreate(&task2, "task2", 1024*2, (void*) 0, tskIDLE_PRIORITY + 1, NULL);
    //xTaskCreate(&task3, "task3", 1024*2, (void*) 0, tskIDLE_PRIORITY + 2, NULL);

    xTaskCreatePinnedToCore(&task1, "task1", 1024*1, (void*) 0, tskIDLE_PRIORITY + 0, NULL, 1);
    xTaskCreatePinnedToCore(&task2, "task2", 1024*2, (void*) 0, tskIDLE_PRIORITY + 1, NULL, 1);
    xTaskCreatePinnedToCore(&task3, "task3", 1024*2, (void*) 0, tskIDLE_PRIORITY + 2, NULL, 1);
    //while(1){

    //}
}
