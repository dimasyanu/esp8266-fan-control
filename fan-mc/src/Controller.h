#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>

class Controller {
public:
    Controller();
    void listen();


private:
    ESP8266WebServer *server;
    char fanSpeed = '0';
    const char* svrUsername = "yanoo";
    const char* svrPassword = "samid";
    const char* webAppHtml = "<!DOCTYPE html><html lang=\"en\">  <head>    <meta charset=\"UTF-8\">    <link rel=\"icon\" href=\"https://yanoo.id/media/fan/favicon.png\">    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">    <title>Home Fan</title>    <script type=\"module\" crossorigin src=\"https://yanoo.id/media/fan/assets/index.min.js\"></script>    <link rel=\"stylesheet\" crossorigin href=\"https://yanoo.id/media/fan/assets/index.min.css\"/>  </head>  <body>    <div id=\"app\"></div>  </body></html>";
    void badRequest(String message);
    void badRequest(const char* message);
    char changeSpeed(int speed);
    void handleGetSpeed();
    void handleWebApp();
    void handleNotFound();
    void handleUpdateSpeed();
    void initialize();
    int len(const char* str);
    void success(char speed);
};
