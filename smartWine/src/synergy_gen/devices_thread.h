/* generated thread header file - do not edit */
#ifndef DEVICES_THREAD_H_
#define DEVICES_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
void devices_thread_entry(void);
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
#include "r_sci_i2c.h"
#include "r_i2c_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t ze_timer2;
#ifdef ZE_Timer_Callback
#define TIMER_ON_GPT_CALLBACK_USED_ze_timer2 (0)
#else
#define TIMER_ON_GPT_CALLBACK_USED_ze_timer2 (1)
#endif
#if TIMER_ON_GPT_CALLBACK_USED_ze_timer2
void ZE_Timer_Callback(timer_callback_args_t * p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
#ifdef NULL
#define ADC_CALLBACK_USED_g_adc0 (0)
#else
#define ADC_CALLBACK_USED_g_adc0 (1)
#endif
#if ADC_CALLBACK_USED_g_adc0
void NULL(adc_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer1;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer0;
/** UART on SCI Instance. */
extern const uart_instance_t arduino_uart;
#ifdef NULL
#else
extern void NULL(uint32_t channel, uint32_t level);
#endif
#ifdef user_uart_callback
#define UART_ON_SCI_UART_CALLBACK_USED_arduino_uart (0)
#else
#define UART_ON_SCI_UART_CALLBACK_USED_arduino_uart (1)
#endif
#if UART_ON_SCI_UART_CALLBACK_USED_arduino_uart
void user_uart_callback(uart_callback_args_t * p_args);
#endif
extern const i2c_cfg_t arduino_i2c_cfg;
/** I2C on SCI Instance. */
extern const i2c_master_instance_t arduino_i2c;
#ifdef NULL
#define I2C_ON_SCI_CALLBACK_USED_arduino_i2c (0)
#else
#define I2C_ON_SCI_CALLBACK_USED_arduino_i2c (1)
#endif
#if I2C_ON_SCI_CALLBACK_USED_arduino_i2c
void NULL(i2c_callback_args_t * p_args);
#endif
extern const i2c_cfg_t pmodB_cfg;
/** I2C on SCI Instance. */
extern const i2c_master_instance_t pmodB;
#ifdef NULL
#define I2C_ON_SCI_CALLBACK_USED_pmodB (0)
#else
#define I2C_ON_SCI_CALLBACK_USED_pmodB (1)
#endif
#if I2C_ON_SCI_CALLBACK_USED_pmodB
void NULL(i2c_callback_args_t * p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* DEVICES_THREAD_H_ */
