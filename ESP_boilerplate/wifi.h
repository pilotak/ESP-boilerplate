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
#if defined(DEBUG)
    Serial.println("[WIFI] Connected");
    Serial.print("[WIFI] Local IP: ");
    Serial.println(WiFi.localIP());
#endif

    connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event) {
#if defined(DEBUG)
    Serial.println("[WIFI] Disconnected");
#endif
    mqttReconnectTimer.detach();
}

void wifiSetup() {
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

#if defined(DEBUG)
    Serial.print("[WIFI] Connecting to: ");
    Serial.println(WIFI_SSID);
#endif

    while (WiFi.status() != WL_CONNECTED) {
#if defined(DEBUG)
        Serial.print('.');
#endif
        delay(500);
    }

    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
}
