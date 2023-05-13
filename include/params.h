char mqtt_server[MAX_MQTT_SERVER_LEN + 1] = "";
char mqtt_port[MAX_MQTT_PORT_LEN + 1]     = "1883";
char mqtt_user[MAX_MQTT_USER_LEN + 1]     = "";
char mqtt_password[MAX_MQTT_PASS_LEN + 1] = "";

MenuItem myMenuItems [] = {
    { "srv",  "MQTT server",   mqtt_server,   MAX_MQTT_SERVER_LEN },
    { "port", "MQTT port",     mqtt_port,     MAX_MQTT_PORT_LEN },
    { "user", "MQTT user",     mqtt_user,     MAX_MQTT_USER_LEN },
    { "pass", "MQTT password", mqtt_password, MAX_MQTT_PASS_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);
bool LOAD_DEFAULT_CONFIG_DATA = false;
ESP_WM_LITE_Configuration defaultConfig;
