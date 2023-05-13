#define FW_VERSION "1.0.0"

#define CONFIG_PORTAL_SSID "your_customized_ssid"
#define CONFIG_PORTAL_PWD  "your_customized_pwd"

#define MAX_MQTT_SERVER_LEN 48
#define MAX_MQTT_PORT_LEN   5
#define MAX_MQTT_USER_LEN   32
#define MAX_MQTT_PASS_LEN   32

#define MQTT_QOS 1
#define MQTT_RETAIN true
#define MQTT_STATUS_INTERVAL 20000 //ms
#define MQTT_STATUS_TOPIC  "status"  // will result ie. DEVICE_NAME/status
#define MQTT_RESTART_TOPIC "restart"  // will result ie. DEVICE_NAME/restart
#define MQTT_UPGRADE_TOPIC "upgrade"  // will result ie. DEVICE_NAME/upgrade
#define MQTT_UPGRADE_STATUS_TOPIC "status"  // will result ie. DEVICE_NAME/MQTT_UPGRADE_TOPIC/status
#define MQTT_STATUS_ALIVE 1
#define MQTT_STATUS_DEAD 0

#define BUTTON_PIN 3
#define LONG_PRESS 1000  // ms
