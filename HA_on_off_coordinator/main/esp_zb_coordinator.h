#include "esp_zigbee_core.h"
#include "switch_driver.h"

/* Zigbee configuration */
#define MAX_CHILDREN                    10          /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE       false       /* enable the install code policy for security */
#define COORDINATOR_SWITCH_ENDPOINT     1           // Onboard SW1 End Point
#define ZIGBEE_CHANNEL                  (1l << 13)  // ZigBee channel

#define ESP_ZB_ZC_CONFIG()                                                              \
    {                                                                                   \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,                                  \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,                               \
        .nwk_cfg.zczr_cfg = {                                                           \
            .max_children = MAX_CHILDREN,                                               \
        },                                                                              \
    }

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
    {                                                           \
        .radio_mode = RADIO_MODE_NATIVE,                        \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = HOST_CONNECTION_MODE_NONE,      \
    }
