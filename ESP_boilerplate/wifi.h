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

void onWifiConnect(const WiFiEventStationModeGotIP &event) {
#if defined(DEBUG_ENABLED)
    Serial.println("[WIFI] Connected");
    Serial.print("[WIFI] Local IP: ");
    Serial.println(WiFi.localIP());
#endif

    connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event) {
#if defined(DEBUG_ENABLED)
    Serial.println("[WIFI] Disconnected");
#endif
    mqttReconnectTimer.detach();
}

void wifiSetup() {
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);

    String AP_SSID = CONFIG_PORTAL_SSID;
    String AP_PWD  = CONFIG_PORTAL_PWD;

    wifiManager->setConfigPortal(AP_SSID, AP_PWD);
    wifiManager->begin();

    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
}
