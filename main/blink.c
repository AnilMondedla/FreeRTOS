/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//This runs with D2 (Blue LED)
//definitions
#define BLINK_GPIO1 16
#define BLINK_GPIO2 17
#define BLINK_GPIO3 18
#define BLINK_GPIO4 19

//functions used
void blink_task(void *pvParameter);

void app_main()
{
    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 5, NULL);
}

void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */

	// Init the GPIO
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_pad_select_gpio(BLINK_GPIO2);
    gpio_pad_select_gpio(BLINK_GPIO3);
    gpio_pad_select_gpio(BLINK_GPIO4);
    
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO3, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO4, GPIO_MODE_OUTPUT);

    while(1)
    {
        for(int i=0; i<10;i++)
        {
         switch(i)
                  {
                    case 0:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 0);
                             gpio_set_level(BLINK_GPIO3, 0);
                             gpio_set_level(BLINK_GPIO4, 0);
                             vTaskDelay(1000 / portTICK_PERIOD_MS);
                              break;  
                    case 1:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 0);
                             gpio_set_level(BLINK_GPIO3, 0);
                             gpio_set_level(BLINK_GPIO4, 1);
                               vTaskDelay(1000 / portTICK_PERIOD_MS);
                             break;
                    case 2:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 0);
                             gpio_set_level(BLINK_GPIO3, 1);
                             gpio_set_level(BLINK_GPIO4, 0);
                               vTaskDelay(1000 / portTICK_PERIOD_MS); 
                             break;
                    case 3:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 0);
                             gpio_set_level(BLINK_GPIO3, 1);
                             gpio_set_level(BLINK_GPIO4, 1);
                               vTaskDelay(1000 / portTICK_PERIOD_MS);  
                             break; 
                    case 4:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 1);
                             gpio_set_level(BLINK_GPIO3, 0);
                             gpio_set_level(BLINK_GPIO4, 0);
                               vTaskDelay(1000 / portTICK_PERIOD_MS);
                             break;
                    case 5:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 1);
                             gpio_set_level(BLINK_GPIO3, 0);
                             gpio_set_level(BLINK_GPIO4, 1);
                               vTaskDelay(1000 / portTICK_PERIOD_MS);
                             break;
                     case 6: gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 1);
                             gpio_set_level(BLINK_GPIO3, 1);
                             gpio_set_level(BLINK_GPIO4, 0);
                               vTaskDelay(1000 / portTICK_PERIOD_MS); 
                             break;  
                    case 7:  gpio_set_level(BLINK_GPIO1, 0);
                             gpio_set_level(BLINK_GPIO2, 1);
                             gpio_set_level(BLINK_GPIO3, 1);
                             gpio_set_level(BLINK_GPIO4, 1);
                               vTaskDelay(1000 / portTICK_PERIOD_MS);
                             break;
                    case 8:  gpio_set_level(BLINK_GPIO1, 1);
                             gpio_set_level(BLINK_GPIO2, 0);
                             gpio_set_level(BLINK_GPIO3, 0);
                             gpio_set_level(BLINK_GPIO4, 0);
                               vTaskDelay(1000 / portTICK_PERIOD_MS); 
                              break;
                    case 9:  gpio_set_level(BLINK_GPIO1, 1);
                             gpio_set_level(BLINK_GPIO2, 0);
                             gpio_set_level(BLINK_GPIO3, 0);
                             gpio_set_level(BLINK_GPIO4, 1);
                               vTaskDelay(1000 / portTICK_PERIOD_MS);
                              break; 
                    default: break;                                         
                  }        
        
        }
    }

    vTaskDelete(NULL); //Delete this task if it exits from the loop above

}
