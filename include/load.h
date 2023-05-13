// wifi.h
#include <ESPAsync_WiFiManager_Lite.h>
#include "./params.h"
#include <ArduinoJson.h>

ESPAsync_WiFiManager_Lite *wifiManager;

#if defined(ESP8266)
    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiDisconnectHandler;
#else
    #include <WiFi.h>
#endif

// mqtt.h
#include <AsyncMqttClient.h>
#include <Ticker.h>

AsyncMqttClient mqtt;
Ticker mqttReconnectTimer;
char will[40] = {0}; // has to be global variable
char will_topic[64] = {0}; // has to be global variable

void connectToMqtt();

// ota.h
#if defined(HTTP_OTA)
    #if defined(ESP8266)
        #include <ESP8266httpUpdate.h>
        #include <ESP8266HTTPClient.h>
        #define updater ESPhttpUpdate
    #else
        #include <HTTPClient.h>
        #include <HTTPUpdate.h>
        #define updater httpUpdate
    #endif
    bool do_http_update = false;
    char http_ota_url[100];

    void httpOtaUpdate();
#endif

#if defined(ARDUINO_OTA)
    #include <ArduinoOTA.h>
    bool ota_in_progess = false;
#endif

// button.h
#include <JC_Button.h>
Button button(BUTTON_PIN);
