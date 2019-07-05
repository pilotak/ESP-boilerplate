#if defined(NTP_SUPPORT)
void processNtpEvent(NTPSyncEvent_t ntpEvent) {
    if (ntpEvent == timeSyncd) {
        time_t last_time = NTP.getLastNTPSync();
#if defined(HAS_RTC)
        RTC.set(last_time);

        if (NTP.getInterval() > 0 && RTC.get() >= last_time) {
#if defined(DEBUG)
            Serial.println("[TIME] RTC is working, using as deafult sync provider");
#endif
            NTP.setInterval(0);
            setSyncProvider(RTC.get);
            setSyncInterval(TIME_SYNC_INTERVAL);
        }

#endif
#if defined(DEBUG)
        Serial.print("[TIME] Got new NTP time: ");
        Serial.println(NTP.getTimeDateString(last_time));
#endif
    }
}
#endif

#if defined(DEBUG) && defined(HAS_RTC)
void printDigits(int digits) {
    if (digits < 10) {
        Serial.print('0');
    }

    Serial.print(digits);
}
#endif

void setupTime() {
#if defined(HAS_RTC)
    bool rtc_set = true;
    Wire.begin(SDA_pin, SCL_pin);
    setSyncProvider(RTC.get);
    setSyncInterval(TIME_SYNC_INTERVAL);

    if (timeStatus() != timeSet) {
#if defined(DEBUG)
        Serial.println("[TIME] Unable to sync with the RTC");
#endif

#if defined(NTP_SUPPORT)
#if defined(DEBUG)
        Serial.println("[TIME] Fallback to NTP sync");
#endif
        setSyncProvider(NULL);
        setSyncInterval(0);
        NTP.setInterval(TIME_SYNC_INTERVAL);
        rtc_set = false;
#else

        while (1) {}

#endif

    } else {
        current_time = myTZ.toLocal(now(), &tcr);

#if defined(DEBUG)
        Serial.print("[TIME] System time synchronized - ");
        Serial.print(hour());
        Serial.print(":");
        printDigits(minute());
        Serial.print(":");
        printDigits(second());
        Serial.print(" ");
        printDigits(day());
        Serial.print("/");
        printDigits(month());
        Serial.print("/");
        Serial.print(year());
        Serial.println();
#endif
    }

#endif

#if defined(NTP_SUPPORT)
    NTP.onNTPSyncEvent([](NTPSyncEvent_t event) {
        ntpEvent = event;
        trigger_ntp_event = true;
    });

#if defined(HAS_RTC)
    NTP.setInterval(rtc_set ? 0 : TIME_SYNC_INTERVAL);
#else
    NTP.setInterval(TIME_SYNC_INTERVAL);
#endif

    NTP.begin(NTP_SERVER_NAME);
#endif
}

void timeLoop() {
#if defined(NTP_SUPPORT)

    if (trigger_ntp_event) {
        trigger_ntp_event = false;
        processNtpEvent(ntpEvent);
    }

#endif
}
