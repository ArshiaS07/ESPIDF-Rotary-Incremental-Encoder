#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <esp_attr.h>
#include <driver/pulse_cnt.h>

const uint32_t ENCODER_SAMPLE_TIME_US = 8 * 1e5;

const gpio_num_t ENCODER_PIN_PHASE_A = GPIO_NUM_27;
const gpio_num_t ENCODER_PIN_PHASE_B = GPIO_NUM_32;
const uint8_t    ENCODER_PPR         = 200        ;


void app_main(void)
{
	pcnt_unit_handle_t pcnt_unit = NULL;
	pcnt_unit_config_t pcnt_config = {
			.low_limit = -5000,
			.high_limit=  5000
	};
	ESP_ERROR_CHECK(pcnt_new_unit(&pcnt_config, &pcnt_unit));
	pcnt_channel_handle_t pcnt_channel = NULL;
	pcnt_chan_config_t pcnt_chan_confi = {
			.level_gpio_num = ENCODER_PIN_PHASE_B,
			.edge_gpio_num  = ENCODER_PIN_PHASE_A
	};
	ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &pcnt_chan_confi, &pcnt_channel));
	pcnt_channel_set_edge_action(pcnt_channel, PCNT_CHANNEL_EDGE_ACTION_HOLD, PCNT_CHANNEL_EDGE_ACTION_INCREASE);
	pcnt_channel_set_level_action(pcnt_channel, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE);
//	pcnt_unit_stop(pcnt_unit);
//	pcnt_unit_clear_count(pcnt_unit);
	pcnt_unit_enable(pcnt_unit);
	pcnt_unit_start(pcnt_unit);
	int count = 0;
	while(1){
		pcnt_unit_clear_count(pcnt_unit);
		pcnt_unit_start(pcnt_unit);
		esp_rom_delay_us(ENCODER_SAMPLE_TIME_US);
		pcnt_unit_stop(pcnt_unit);
		pcnt_unit_get_count(pcnt_unit, &count);
		double rpm =1.0 * count / ENCODER_PPR / (ENCODER_SAMPLE_TIME_US * 1e-6) * 60.0;
		printf("The rpm is : %0.4f\n", rpm);
		vTaskDelay(pdMS_TO_TICKS(10));
	}



}
