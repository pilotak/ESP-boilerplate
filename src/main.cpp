/*
MIT License
Copyright (c) 2023 Pavel Slama
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Arduino.h>
#include "const.h"
#include "load.h"
#include "manager.h"
#include "mqtt.h"
#include "ota.h"
#include "button.h"

// include here all required files

void setup() {
#if defined(DEBUG_ENABLED) || defined(DEBUG_ESP_PORT)
    Serial.begin(115200);
    Serial.println();
#endif

    buttonSetup();
    wifiManager = new ESPAsync_WiFiManager_Lite();
    mqttSetup();
    wifiSetup();

#if defined(ARDUINO_OTA)
    otaSetup();
#endif

    // call here custom setup, ie. of sensors
}

void loop() {
    wifiManager->run();

#if defined(ARDUINO_OTA)
    otaLoop();
#endif

#if defined(ARDUINO_OTA)

    if (!ota_in_progess) {
#endif
        buttonLoop();

        if (WiFi.isConnected()) {
            mqttLoop();

            // call here custom loop, ie. of sensors
        }

#if defined(ARDUINO_OTA)
    }

#endif

#if defined(HTTP_OTA)

    if (do_http_update) {
        do_http_update = false;
        httpOtaUpdate();
    }

#endif
}
