#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

void mcpwm_example_gpio_initialize();
void brushed_motor_forward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float duty_cycle);
void brushed_motor_backward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float duty_cycle);
void brushed_motor_turn_left(mcpwm_unit_t mcpwm_num, float duty_cycle);
void brushed_motor_turn_right(mcpwm_unit_t mcpwm_num, float duty_cycle);
void brushed_motor_stop(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num);
void brushed_motor_speed_up(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float *duty_cycle, float increment);
void brushed_motor_slow_down(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float *duty_cycle, float decrement);

#endif // MOTOR_CONTROL_H
