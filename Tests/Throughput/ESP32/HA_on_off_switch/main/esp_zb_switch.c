/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee HA_on_off_switch Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "string.h"
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "esp_zb_switch.h"
#include "driver/gpio.h"
#include "esp_private/esp_clk.h"
#include "esp_timer.h"
#include "zboss_api.h"

#include "esp_pm.h"

#define ZIGBEE_STACK_INITIALIZED_SIGNAL_PIN 2
#define FORMED_NETWORK_SIGNAL_PIN 3
#define DEVICE_FOUND_SIGNAL_PIN 4
#define DEVICE_INIT_AFTER_RESET 5

#define TIMEOUT_MS 500
#define REPORT_INTERVAL_MS (5 * 60 * 1000) // 5 minutes

uint16_t target_short_addr = 0x0000; // The short address of the light bulb device to control
bool END_DEVICE_DISCOVERD = false;
uint32_t packets_sent = 0;
uint32_t packets_attemped = 0;
uint32_t packets_received = 0;
static uint32_t packets_lost = 0;

static uint32_t last_sent_tsn = 0;
static bool waiting_for_response = false;

static esp_timer_handle_t timeout_timer;
static esp_timer_handle_t report_timer;

static void send_toggle_command(void);
#if defined ZB_ED_ROLE
#error Define ZB_COORDINATOR_ROLE in idf.py menuconfig to compile light switch source code.
#endif
typedef struct light_bulb_device_params_s {
    esp_zb_ieee_addr_t ieee_addr;
    uint8_t  endpoint;
    uint16_t short_addr;
} light_bulb_device_params_t;

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

esp_zb_zcl_on_off_cmd_t cmd_req = {0};

static void esp_zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    if (button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        /* implemented light switch toggle functionality */
        //esp_zb_zcl_on_off_cmd_t cmd_req;
        cmd_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = target_short_addr;
        cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        cmd_req.on_off_cmd_id = ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
        
        ESP_EARLY_LOGI(TAG, "Send 'on_off toggle' command");
        esp_zb_zcl_on_off_cmd_req(&cmd_req);
    }
}

static void on_timeout(void* arg)
{
    if (waiting_for_response) {
        ESP_LOGW(TAG, "Timeout: Nu s-a primit raspuns pentru TSN %d", last_sent_tsn);
        packets_lost++;
        waiting_for_response = false;

        // Poți decide dacă retrimiți aici sau aștepți conexiunea
        send_toggle_command();  // Retrimite comanda
    }
}

static void start_timeout_timer()
{
    esp_timer_start_once(timeout_timer, TIMEOUT_MS * 1000); // µs
}

static void stop_timeout_timer()
{
    esp_timer_stop(timeout_timer);
}

static void init_timeout_timer()
{
    const esp_timer_create_args_t timer_args = {
        .callback = &on_timeout,
        .name = "tsn_timeout"
    };
    esp_timer_create(&timer_args, &timeout_timer);
}

// === Raport la fiecare 5 minute ===
static void report_stats(void* arg)
{
    ESP_LOGI(TAG, "== RAPORT 5 MINUTE ==");
    ESP_LOGI(TAG, "Trimise: %lu, Recepționate: %lu, Pierdute: %lu",
             packets_sent, packets_received, packets_lost);
}

static void init_report_timer()
{
    const esp_timer_create_args_t timer_args = {
        .callback = &report_stats,
        .name = "report_5min"
    };
    esp_timer_create(&timer_args, &report_timer);
    esp_timer_start_periodic(report_timer, REPORT_INTERVAL_MS * 1000); // µs
}

static void send_toggle_command(void)
{
    packets_attemped++;

    cmd_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = target_short_addr;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    cmd_req.on_off_cmd_id = ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
    uint32_t tsn = esp_zb_zcl_on_off_cmd_req(&cmd_req);
    if (tsn > 0 && END_DEVICE_DISCOVERD) {
        packets_sent++;
        last_sent_tsn = tsn;
        waiting_for_response = true;
        start_timeout_timer();
        //ESP_LOGI(TAG, "Sent message");
    }
}

void my_zcl_send_status_cb(const esp_zb_zcl_command_send_status_message_t *status_info)
{
    if (status_info->status == ESP_OK && END_DEVICE_DISCOVERD)
    {
        //ESP_LOGI("ZCL_CB", "Comanda trimisă cu succes. TSN: %d", status_info->tsn);
        packets_received++;
        waiting_for_response = false;
        stop_timeout_timer();
        send_toggle_command();
        //ESP_LOGI(TAG, "Pachete trimise: %lu, Pachete primite: %lu, Pachete pierdute: %lu",
        //     packets_sent, packets_received, lost);
    } else {
        ESP_LOGW(TAG, "Eroare la trimitere! Cod: 0x%x", status_info->status);
    }

    /*ESP_LOGI(TAG, "De la EP %d -> către EP %d (addr 0x%04X)",
             status_info->src_endpoint,
             status_info->dst_endpoint,
             3);
   */
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

static void bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Bound successfully!");
        if (user_ctx) {
            light_bulb_device_params_t *light = (light_bulb_device_params_t *)user_ctx;
            cmd_req.zcl_basic_cmd.dst_endpoint = light->endpoint;
            ESP_LOGI(TAG, "The light originating from address(0x%x) on endpoint(%d)", light->short_addr, light->endpoint);
            END_DEVICE_DISCOVERD = true;
            init_timeout_timer();
            init_report_timer();
            send_toggle_command();

            free(light);
        }
    }
}

static void user_find_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Found light");
        esp_zb_zdo_bind_req_param_t bind_req;
        light_bulb_device_params_t *light = (light_bulb_device_params_t *)malloc(sizeof(light_bulb_device_params_t));
        light->endpoint = endpoint;
        light->short_addr = addr;
        esp_zb_ieee_address_by_short(light->short_addr, light->ieee_addr);
        esp_zb_get_long_address(bind_req.src_address);
        bind_req.src_endp = HA_ONOFF_SWITCH_ENDPOINT;
        bind_req.cluster_id = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF;
        bind_req.dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        memcpy(bind_req.dst_address_u.addr_long, light->ieee_addr, sizeof(esp_zb_ieee_addr_t));
        bind_req.dst_endp = endpoint;
        bind_req.req_dst_addr = esp_zb_get_short_address();
        ESP_LOGI(TAG, "Try to bind On/Off");
        esp_zb_zdo_device_bind_req(&bind_req, bind_cb, (void *)light);
    }
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack initialized");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
		//uint8_t txPower = 10;
		esp_zb_set_tx_power(20);
        int8_t returnedPower = 255;
        esp_zb_get_tx_power(&returnedPower);
		ESP_LOGI(TAG, "TX Power is: %d", returnedPower);
        uint8_t channel = 0;
        channel = esp_zb_get_current_channel();
        ESP_LOGI(TAG, "Channel is: %d", channel);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            //ESP_LOGI(TAG, "Device started up in %s factory-reset mode", esp_zb_bdb_is_factory_new() ? "" : "non");
            if (esp_zb_bdb_is_factory_new()) {
                //ESP_LOGI(TAG, "Start network formation");
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
            } else {
                ESP_LOGI(TAG, "Device rebooted");
                esp_zb_bdb_open_network(180);
                gpio_set_level(DEVICE_INIT_AFTER_RESET, 1);
            }
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            //ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d, Short Address: 0x%04hx)",
            //         extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
            //         extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
            //         esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
            gpio_set_level(FORMED_NETWORK_SIGNAL_PIN, 1);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %s)", esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        esp_zb_zdo_match_desc_req_param_t  cmd_req;
        target_short_addr = dev_annce_params->device_short_addr;
        cmd_req.dst_nwk_addr = dev_annce_params->device_short_addr;
        cmd_req.addr_of_interest = dev_annce_params->device_short_addr;
        esp_zb_zdo_find_on_off_light(&cmd_req, user_find_cb, NULL);
        gpio_set_level(DEVICE_FOUND_SIGNAL_PIN, 1);
        break;
    case ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
        if (err_status == ESP_OK) {
            if (*(uint8_t *)esp_zb_app_signal_get_params(p_sg_p)) {
                //ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", esp_zb_get_pan_id(), *(uint8_t *)esp_zb_app_signal_get_params(p_sg_p));
            } else {
                //ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", esp_zb_get_pan_id());
            }
        }
        break;
    default:
        //ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type, esp_err_to_name(err_status));
        break;
    }
}

static void esp_zb_task(void *pvParameters)
{
    gpio_set_level(ZIGBEE_STACK_INITIALIZED_SIGNAL_PIN, 1);
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    esp_zb_secur_network_key_set((uint8_t *)ZIGBEE_DEFAULT_KEY);
    esp_zb_set_pan_id(PAN_ID);
    esp_zb_on_off_switch_cfg_t switch_cfg = ESP_ZB_DEFAULT_ON_OFF_SWITCH_CONFIG();
    esp_zb_ep_list_t *esp_zb_on_off_switch_ep = esp_zb_on_off_switch_ep_create(HA_ONOFF_SWITCH_ENDPOINT, &switch_cfg);
    esp_zb_device_register(esp_zb_on_off_switch_ep);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    esp_zb_zcl_command_send_status_handler_register(my_zcl_send_status_cb);
    ESP_ERROR_CHECK(zb_zcl_register_cb(esp_zb_on_off_switch_ep, my_zcl_send_status_cb));
    ESP_ERROR_CHECK(esp_zb_start(false));
    //esp_zb_scheduler_alarm(send_toggle_command, NULL, DELAY_BETWEEN_TOGGLE_COMMANDS_MS);
    while (true) {
        esp_zb_main_loop_iteration();
    }
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ZIGBEE_STACK_INITIALIZED_SIGNAL_PIN) 
                        | (1 << FORMED_NETWORK_SIGNAL_PIN) 
                        | (1 << DEVICE_FOUND_SIGNAL_PIN) 
                        | (1 << 5),
        .mode = GPIO_MODE_OUTPUT,
    };

    // Get the frequency of the RC_FAST_CLK (internal 8 MHz RC oscillator)
    uint32_t freq_hz = esp_clk_cpu_freq();
    ESP_LOGI("CPU_FREQ", "CPU frequency: %lu Hz", (unsigned long)freq_hz);

    gpio_config(&io_conf);
    gpio_set_level(FORMED_NETWORK_SIGNAL_PIN, 0);
    gpio_set_level(DEVICE_FOUND_SIGNAL_PIN, 0);
    gpio_set_level(DEVICE_INIT_AFTER_RESET, 0);
    gpio_set_level(5, 0);
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    //switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), esp_zb_buttons_handler);
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
