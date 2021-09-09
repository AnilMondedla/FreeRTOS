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
#include <WiFi.h>

void Back();
void Forward();
void Right();
void Left();
void Stop();
//This runs with D2 (Blue LED)
//definitions
#define Motor_L_F 16
#define Motor_L_B 17
#define Motor_R_F 18
#define Motor_R_B 19

//functions used
void blink_task(void *pvParameter);

void app_main()
{
    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 5, NULL);
    xTaskCreate(&WiFi, "WiFi_task", 2048, NULL, 5, NULL);
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
    gpio_pad_select_gpio(Motor_L_F);
    gpio_pad_select_gpio(Motor_L_B);
    gpio_pad_select_gpio(Motor_R_F);
    gpio_pad_select_gpio(Motor_R_B);
    
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(Motor_L_F, GPIO_MODE_OUTPUT);
    gpio_set_direction(Motor_L_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(Motor_R_F, GPIO_MODE_OUTPUT);
    gpio_set_direction(Motor_R_B, GPIO_MODE_OUTPUT);

    while(1)
    {
       Forward();
       vTaskDelay(1000 / portTICK_PERIOD_MS);
       Back();
       vTaskDelay(1000 / portTICK_PERIOD_MS);
       Right();
       vTaskDelay(1000 / portTICK_PERIOD_MS);
       Left();
       vTaskDelay(1000 / portTICK_PERIOD_MS);
       Stop();
       vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL); //Delete this task if it exits from the loop above

}
void WiFi_task(void *pvParameter)
{
  String  ClientRequest;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}
WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Anil","987654321oiuytrewq");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
vTaskDelete(NULL);
}

void Back(){
  // Run Left Motor In Forward Direction
   gpio_set_level(Motor_L_F, 1);
   gpio_set_level(Motor_L_B, 0);

  //Run Right Motor in Forward Direction
   gpio_set_level(Motor_R_F, 1);
   gpio_set_level(Motor_R_B, 0);
  
  }

void Right(){
  //Stop Right Motor
   gpio_set_level(Motor_R_F, 0);
   gpio_set_level(Motor_R_B, 1);

  //Run Left Motor in Forward Direction
   gpio_set_level(Motor_L_F, 1);
   gpio_set_level(Motor_L_B, 0);
  
  }

void Left(){
 
   gpio_set_level(Motor_L_F, 0);
  gpio_set_level(Motor_L_B, 1);

  
   gpio_set_level(Motor_R_F, 1);
   gpio_set_level(Motor_R_B, 0);
  
  }

void Forward(){
  // Run Left Motor In Forward Direction
   gpio_set_level(Motor_L_F, 0);
   gpio_set_level(Motor_L_B, 1);

  //Run Right Motor in Forward Direction
   gpio_set_level(Motor_R_F, 0);
   gpio_set_level(Motor_R_B, 1);
  
  }

void Stop(){
  // Run Left Motor In Forward Direction
   gpio_set_level(Motor_L_F, 0);
   gpio_set_level(Motor_L_B, 0);

  //Run Right Motor in Forward Direction
   gpio_set_level(Motor_R_F, 0);
   gpio_set_level(Motor_R_B, 0);
  
  }

