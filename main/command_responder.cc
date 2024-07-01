/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "command_responder.h"
#include "motor_control.h"
#include "tensorflow/lite/micro/micro_log.h"
#include <string.h>

static float duty_cycle = 100.0; // Default duty cycle

void RespondToCommand(int32_t current_time, const char* found_command, uint8_t score, bool is_new_command) {
    
    if (is_new_command && score > 50) { // Assume a threshold of 50 for command recognition confidence
        MicroPrintf("Heard %s (%d) @%dms", found_command, score, current_time);
        
        if (strcmp(found_command, "forward") == 0) {
            MicroPrintf("Executing command: FORWARD");
            brushed_motor_forward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cycle);
            brushed_motor_forward(MCPWM_UNIT_0, MCPWM_TIMER_1, duty_cycle);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);

        } else if (strcmp(found_command, "backward") == 0) {
            MicroPrintf("Executing command: BACKWARD");
            brushed_motor_backward(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_cycle);
            brushed_motor_backward(MCPWM_UNIT_0, MCPWM_TIMER_1, duty_cycle);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
        } else if (strcmp(found_command, "left") == 0) {
            MicroPrintf("Executing command: TURN LEFT");
            brushed_motor_turn_left(MCPWM_UNIT_0, duty_cycle);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
        } else if (strcmp(found_command, "right") == 0) {
            MicroPrintf("Executing command: TURN RIGHT");
            brushed_motor_turn_right(MCPWM_UNIT_0, duty_cycle);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
        } else if (strcmp(found_command, "stop") == 0) {
            MicroPrintf("Executing command: STOP");
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
            brushed_motor_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
        } else if (strcmp(found_command, "speed up") == 0) {
            MicroPrintf("Executing command: SPEED UP");
            brushed_motor_speed_up(MCPWM_UNIT_0, MCPWM_TIMER_0, &duty_cycle, 20.0);
            brushed_motor_speed_up(MCPWM_UNIT_0, MCPWM_TIMER_1, &duty_cycle, 20.0);
        } else if (strcmp(found_command, "slow down") == 0) {
            MicroPrintf("Executing command: SLOW DOWN");
            brushed_motor_slow_down(MCPWM_UNIT_0, MCPWM_TIMER_0, &duty_cycle, 20.0);
            brushed_motor_slow_down(MCPWM_UNIT_0, MCPWM_TIMER_1, &duty_cycle, 20.0);
        } else {
            MicroPrintf("Unrecognized command: %s", found_command);
        }
    }
}

