// vi:ts=4

// Based on:
// https://registry.platformio.org/libraries/adafruit/DHT%20sensor%20library/examples/DHT_Unified_Sensor/DHT_Unified_Sensor.ino

#include <avr/wdt.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN          2
#define DHTTYPE         DHT22
#define DELAY_MS        1000
#define DELAY_FACTOR    15

DHT_Unified dht(DHTPIN, DHTTYPE);
uint8_t waits = 0;

void setup()
{
    wdt_enable(WDTO_4S);

    Serial.begin(115200);
    dht.begin();
}

void loop()
{
    wdt_reset();
    waits++;

    if (waits <= DELAY_FACTOR) {
        // Delay between measurements
        delay(DELAY_MS);

        // Wait again
        return;
    }

    // Waited often enough
    waits = 0;

    // Get temperature event and print its value
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.print(F("E"));
    } else {
        Serial.print(event.temperature);
    }

    Serial.print(F(";"));

    // Get humidity event and print its value
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.print(F("E"));
    } else {
        Serial.print(event.relative_humidity);
    }

    Serial.print(F("\n"));
}
