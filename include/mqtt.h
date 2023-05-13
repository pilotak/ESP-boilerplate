void sendStatus() {
    if (mqtt.connected()) {
        StaticJsonDocument < JSON_OBJECT_SIZE(4) > json;
        char message[140] = {0};
        char topic[64] = {0};

        json["status"] = MQTT_STATUS_ALIVE;
        json["ip"] = WiFi.localIP().toString();
        json["signal"] = getRSSIasQuality(WiFi.RSSI());
        json["fw_ver"] = FW_VERSION;

        uint32_t len = serializeJson(json, message, sizeof(message));

#if defined(DEBUG_ENABLED)
        Serial.println("[MQTT] Sending status data:");
        serializeJsonPretty(json, Serial);
        Serial.println();
#endif

        snprintf(topic, sizeof(topic), "%s/%s", wifiManager->getBoardName().c_str(), MQTT_STATUS_TOPIC);
        mqtt.publish(topic, MQTT_QOS, MQTT_RETAIN, message, len);
    }
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index,
                   size_t total) {

    char *lastSlash = strrchr(topic, '/');
    char *cmd = lastSlash + 1;

#if defined(DEBUG_ENABLED)
    Serial.print("[MQTT] Message arrived \"/");
    Serial.print(cmd);
    Serial.print("\" (");
    Serial.print(len);
    Serial.print("): ");

    for (uint16_t i = 0; i < len; i++) {
        Serial.print(static_cast<char>(payload[i]));
    }

    Serial.println();
#endif


    if (cmd != nullptr && strcmp(cmd, MQTT_UPGRADE_TOPIC) == 0) {
#if defined(HTTP_OTA)

        char topic[64] = {0};
        snprintf(topic, sizeof(topic), "%s/%s/%s", wifiManager->getBoardName().c_str(), MQTT_UPGRADE_TOPIC,
                 MQTT_UPGRADE_STATUS_TOPIC);

        if (len > sizeof(http_ota_url)) {
            mqtt.publish(topic, MQTT_QOS, false, "URL too long");

        } else if (len == 0) {
            mqtt.publish(topic, MQTT_QOS, false, "No URL");

        } else {
            memset(http_ota_url, 0, sizeof(http_ota_url));
            memcpy(http_ota_url, payload, len);
            do_http_update = true;
        }

#endif

    } else if (cmd != nullptr && strcmp(cmd, MQTT_RESTART_TOPIC) == 0) {
        ESP.restart();
    }
}

void connectToMqtt() {
#if defined(DEBUG_ENABLED)
    Serial.println("[MQTT] Connecting...");
#endif

    mqtt.connect();
}

void onMqttConnect(bool sessionPresent) {
#if defined(DEBUG_ENABLED)
    Serial.println("[MQTT] Connected");
#endif

    char topic[64] = {0};

    // restart
    snprintf(topic, sizeof(topic), "%s/%s", wifiManager->getBoardName().c_str(), MQTT_RESTART_TOPIC);
    mqtt.subscribe(topic, MQTT_QOS);

#if defined(HTTP_OTA)
    // upgrade
    snprintf(topic, sizeof(topic), "%s/%s", wifiManager->getBoardName().c_str(), MQTT_UPGRADE_TOPIC);
    mqtt.subscribe(topic, MQTT_QOS);
#endif

    sendStatus();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
#if defined(DEBUG_ENABLED)

    if ((int8_t)reason != 0) {
        Serial.print("[MQTT] Disconnected, rc=");
        Serial.println((int8_t)reason);
    }

#endif
#if defined(ARDUINO_OTA)

    if (!ota_in_progess) {
#endif

        if (WiFi.isConnected()) {
            mqttReconnectTimer.once(2, connectToMqtt);
        }

#if defined(ARDUINO_OTA)
    }

#endif
}

void mqttSetup() {
#if defined(DEBUG_ENABLED)
    Serial.println("[MQTT] Setup");
#endif
    uint16_t port = atoi(mqtt_port);

    IPAddress ip;

    if (ip.fromString(mqtt_server)) {  // check if server is IP address or hostname
        mqtt.setServer(ip, port);

    } else {
        mqtt.setServer(mqtt_server, port);
    }

    // will
    snprintf(will, sizeof(will), "{\"status\":%i}", MQTT_STATUS_DEAD);
    snprintf(will_topic, sizeof(will_topic), "%s/%s", wifiManager->getBoardName().c_str(), MQTT_STATUS_TOPIC);
    mqtt.setWill(will_topic, MQTT_QOS, MQTT_RETAIN, will, strlen(will));

    mqtt.setCredentials(mqtt_user, mqtt_password);
    mqtt.setKeepAlive((MQTT_STATUS_INTERVAL / 1000) + 2);  // converts ms->s + 2 sec extra, in case we have a delay
    mqtt.onConnect(onMqttConnect);
    mqtt.onDisconnect(onMqttDisconnect);
    mqtt.onMessage(onMqttMessage);
}

void mqttLoop() {
    static uint32_t last_status = 0;
#if defined(ARDUINO_OTA)

    if (!ota_in_progess) {
#endif

        if ((millis() - last_status) >= MQTT_STATUS_INTERVAL) {
            last_status = millis();

            sendStatus();
        }

#if defined(ARDUINO_OTA)
    }

#endif
}
