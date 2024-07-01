#include "motor_control.h"
#include <stdio.h>

#define MAX_DUTY_CYCLE 100.0
#define MIN_DUTY_CYCLE 0.0

void mcpwm_example_gpio_initialize() {
    printf("Initializing mcpwm gpio...\n");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 41);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, 42);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, 39);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, 40);
}

void brushed_motor_forward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float duty_cycle) {
    mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_B);
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void brushed_motor_backward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float duty_cycle) {
    mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_A);
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_B, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
}

void brushed_motor_turn_left(mcpwm_unit_t mcpwm_num, float duty_cycle) {
    mcpwm_set_duty(mcpwm_num, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle * 0.5);
    mcpwm_set_duty(mcpwm_num, MCPWM_TIMER_1, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    mcpwm_set_duty_type(mcpwm_num, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void brushed_motor_turn_right(mcpwm_unit_t mcpwm_num, float duty_cycle) {
    mcpwm_set_duty(mcpwm_num, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty(mcpwm_num, MCPWM_TIMER_1, MCPWM_OPR_A, duty_cycle * 0.5);
    mcpwm_set_duty_type(mcpwm_num, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    mcpwm_set_duty_type(mcpwm_num, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void brushed_motor_stop(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num) {
    mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_A);
    mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_B);
}

void brushed_motor_speed_up(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float *duty_cycle, float increment) {
    *duty_cycle = (*duty_cycle + increment) > MAX_DUTY_CYCLE ? MAX_DUTY_CYCLE : *duty_cycle + increment;
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, *duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

void brushed_motor_slow_down(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num, float *duty_cycle, float decrement) {
    *duty_cycle = (*duty_cycle - decrement) < MIN_DUTY_CYCLE ? MIN_DUTY_CYCLE : *duty_cycle - decrement;
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, *duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}
