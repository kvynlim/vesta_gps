/*
=============GPS TRANSMITTER=============
Pin  4 ~ RX
Pin  3 ~ TX
TinyGPS++ Library Download ~ https://github.com/mikalhart/TinyGPSPlus
*/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define RX_PIN 4
#define TX_PIN 3

//GPS
TinyGPSPlus gps;
unsigned long currentMillis, prevMillis, noGPS;
static const uint16_t maxNoGPS = 2000;

struct package {
    double lat ;
    double lng ;
    double speed;
};

typedef struct package Package;
Package data;

SoftwareSerial GPS_SERIAL(RX_PIN, TX_PIN);

void setup() {
    GPS_SERIAL.begin(9600);
}

void loop() {
    rxGPS();
}

void rxGPS() {
    currentMillis = millis();
    noGPS = currentMillis - prevMillis;
    
    gps.encode(GPS_SERIAL.read());
    
    if (gps.location.isUpdated()) {
        data.lat = gps.location.lat();
        data.lng = gps.location.lng();
        data.speed = gps.speed.mps();
        prevMillis = millis();
    }

    else if (noGPS >= maxNoGPS) {
        data.lat = 0;
        data.lng = 0;
        data.speed = 0;
    }
}
