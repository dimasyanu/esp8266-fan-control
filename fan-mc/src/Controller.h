#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>

class Controller {
public:
    Controller();
    void listen();


private:
    ESP8266WebServer *server;
    const char* svrUsername = "yanoo";
    const char* svrPassword = "samid";
    void badRequest();
    char changeSpeed(int speed);
    void handleGetSpeed();
    void handleUpdateSpeed();
    void initialize();
    int len(const char* str);
    void success(char speed);
};
