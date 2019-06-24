#define DEVICE_NAME "ESP8266ConfigBase"  // used for MQTT, OTA, AP
#define FW_VERSION "1.0.0"

#define CONFIG_PATH "/config.json"
#define CONFIG_AP_SSID DEVICE_NAME "_config"
#define CONFIG_AP_PASSWORD "StrongPasswordHere"
#define CONFIG_PORTAL_TIMEOUT 120  // sec

#define DEFAULT_MQTT_PORT 1883
#define MQTT_QOS 1
#define MQTT_RETAIN true
#define MQTT_CHECK_INTERVAL 5000
#define MQTT_STATUS_INTERVAL 30000
#define MQTT_STATUS_TOPIC DEVICE_NAME "/status"  // will result ie. DEVICE_NAME/status
#define MQTT_UPGRADE_TOPIC DEVICE_NAME "/upgrade"  // will result ie. DEVICE_NAME/upgrade
#define MQTT_UPGRADE_STATUS_TOPIC DEVICE_NAME "/upgrade/status"  // will result ie. DEVICE_NAME/upgrade/status
#define MQTT_RESTART_TOPIC DEVICE_NAME "/restart"  // will result ie. DEVICE_NAME/restart
#define MQTT_STATUS_ALIVE 1
#define MQTT_STATUS_DEAD 0

#define NOFUSS_CHECK_INTERVAL 3600000  // 1h
#define OTA_PORT 8266  // for local updates
