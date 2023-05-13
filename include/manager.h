uint8_t getRSSIasQuality(int RSSI) {
    uint8_t quality = 0;

    if (RSSI <= -100) {
        quality = 0;

    } else if (RSSI >= -50) {
        quality = 100;

    } else {
        quality = 2 * (RSSI + 100);
    }

    return quality;
}

void onWifiConnect() {
#if defined(DEBUG_ENABLED)
    Serial.println("[WIFI] Connected");
    Serial.print("[WIFI] Local IP: ");
    Serial.println(WiFi.localIP());
#endif

    connectToMqtt();
}

void onWifiDisconnect() {
#if defined(DEBUG_ENABLED)
    Serial.println("[WIFI] Disconnected");
#endif
    mqttReconnectTimer.detach();
}

void wifiSetup() {
#if defined(ESP8266)
    wifiConnectHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP & event) {
        onWifiConnect();
    });
#else
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info){
        onWifiConnect();
    }, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
#endif

    String AP_SSID = CONFIG_PORTAL_SSID;
    String AP_PWD  = CONFIG_PORTAL_PWD;

    wifiManager->setConfigPortal(AP_SSID, AP_PWD);
    wifiManager->begin();

#if defined(ESP8266)
    wifiDisconnectHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected & event) {
        onWifiDisconnect();
    });
#else
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info){
        onWifiDisconnect();
    }, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
#endif
}
