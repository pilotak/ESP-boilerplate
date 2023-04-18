#define DEVICE_NAME "meteo"  // used for MQTT, OTA
#define FW_VERSION "1.0.0"

#define WIFI_SSID "WiFi"
#define WIFI_PASSWORD "password"
#define CONFIG_PORTAL_TIMEOUT 120  // sec

#define MQTT_SERVER "server.com" // or it can be IP ie.: 192.168.1.1
#define MQTT_PORT 1883
#define MQTT_USER "mqttUser"
#define MQTT_PASSWORD "mqttPassword"

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

#define BUTTON_PIN D3
#define LONG_PRESS 1000  // ms

#define SDA_PIN SDA
#define SCL_PIN SCL
