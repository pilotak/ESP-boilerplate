#if defined(ARDUINO_OTA)
void otaSetup() {
    ArduinoOTA.setHostname(DEVICE_NAME);

    ArduinoOTA.onStart([]() {
#if defined(DEBUG)
        Serial.println("[OTA] Starting");
#endif
        ota_in_progess = true;
    });
    ArduinoOTA.onEnd([]() {
#if defined(DEBUG)
        Serial.print("\n\e[0E");  // new line + move to the beginning of the current line
        Serial.println("[OTA] End");
        delay(200);
#endif
    });

#if defined(DEBUG)
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.print("\e[2K");  // clear line
        Serial.print("\e[0E");  // move to the beginning of the current line
        Serial.print("[OTA] Progress: ");
        Serial.print((progress / (total / 100)));
        Serial.print("%");
    });
#endif
    ArduinoOTA.onError([](ota_error_t error) {
        ota_in_progess = false;

#if defined(DEBUG)
        Serial.print("\n\e[0E");  // new line + move to the beginning of the current line
        Serial.print("[OTA] Error: ");
        Serial.println(error);

        if (error == OTA_AUTH_ERROR) {
            Serial.println("[OTA] Auth Failed");

        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("[OTA] Begin Failed");

        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("[OTA] Connect Failed");

        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("[OTA] Receive Failed");

        } else if (error == OTA_END_ERROR) {
            Serial.println("[OTA] End Failed");
        }

#endif
    });


    ArduinoOTA.begin();

}

void otaLoop() {
    ArduinoOTA.handle();
}
#endif

#if defined(HTTP_OTA)
void httpUpdate() {
    char msg[127];
    uint32_t len = 0;
    ota_in_progess = true;
    WiFiClient client;

    ESPhttpUpdate.rebootOnUpdate(false);

#if defined(DEBUG)
    Serial.print("[OTA] Starting HTTP update from: ");
    Serial.println(http_ota_url);
#endif

    t_httpUpdate_return ret = ESPhttpUpdate.update(client, http_ota_url, FW_VERSION);

    switch (ret) {
        case HTTP_UPDATE_FAILED:
            ota_in_progess = false;

            len = snprintf(msg, sizeof(msg), "%s", ESPhttpUpdate.getLastErrorString().c_str());
            mqtt.publish(MQTT_UPGRADE_STATUS_TOPIC, MQTT_QOS, false, msg, len);

#if defined(DEBUG)
            Serial.printf("[OTA] HTTP update failed: (%d): %s\r\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
#endif
            break;

        case HTTP_UPDATE_NO_UPDATES:
            ota_in_progess = false;
            mqtt.publish(MQTT_UPGRADE_STATUS_TOPIC, MQTT_QOS, false, "No updates");

#if defined(DEBUG)
            Serial.println("[OTA] HTTP update: no updates");
#endif
            break;

        case HTTP_UPDATE_OK:
            mqtt.publish(MQTT_UPGRADE_STATUS_TOPIC, MQTT_QOS, false, "OK");

#if defined(DEBUG)
            Serial.println("[OTA] HTTP update: OK");
#endif

            ESP.restart();
            break;
    }
}
#endif
