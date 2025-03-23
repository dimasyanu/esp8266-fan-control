#include <Controller.h>

Controller::Controller()
{
    this->server = new ESP8266WebServer(80);
    this->initialize();
}

/// @brief Routing configuration
void Controller::initialize()
{
    this->server->onNotFound([this] { this->handleNotFound(); });

    this->server->on("/",
        HTTPMethod::HTTP_GET,
        [this] { this->handleWebApp(); }
    );

    this->server->on("/api/speed",
        HTTPMethod::HTTP_GET,
        [this] { this->handleGetSpeed(); }
    );

    this->server->on("/api/speed",
        HTTPMethod::HTTP_POST,
        [this]() { this->handleUpdateSpeed(); }
    );

    this->server->begin();
}

void Controller::listen()
{
    this->server->handleClient();
}

void Controller::badRequest(String message) {
    this->badRequest(message.c_str());
}

/// @brief Send bad request response
void Controller::badRequest(const char* message) {
    digitalWrite(LED_BUILTIN, HIGH);
    this->server->send(400, "application/json", "{\"success\":false, \"message\":\"" + String(message) + "\"}");
    this->server->client().stop();
    delay(5000);
    digitalWrite(LED_BUILTIN, LOW);
}

/// @brief Send success response
/// @param speed 
void Controller::success(char speed) {
    char respBody[256];
    sprintf(respBody, "{\"success\":true,\"speed\":\"%c\"}", speed);
    this->server->send(200, "application/json", respBody);
    this->server->client().stop();
}

/// @brief Change speed of the fan
/// @param speed 
/// @return Speed of the fan after changed
char Controller::changeSpeed(int speed) {
    for (int i = 0; i < speed; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
    }

    return speed + '0';
}

/// @brief Handle get speed request
void Controller::handleGetSpeed()
{
    this->success(this->fanSpeed);
}

void Controller::handleWebApp()
{
    this->server->send(200, "text/html", this->webAppHtml);
}

/// @brief Handle not found request
void Controller::handleNotFound()
{
    this->server->send(404, "text/plain", "Not found");
}

/// @brief Handle update speed request
void Controller::handleUpdateSpeed()
{
    const char* username = this->server->arg("username").c_str();
    const char* password = this->server->arg("password").c_str();
    const char* speed = this->server->arg("speed").c_str();

    int speedLen = this->len(speed);

    if (strcmp(username, this->svrUsername) != 0 || strcmp(password, this->svrPassword) != 0 || speedLen != 1) {
        Serial.printf("Invalid username or password! (%s:%s, %s)\n", username, password, speed);
        Serial.printf("speed: %i\n", speedLen);
        this->badRequest(String("Invalid username or password! ") + String(username) + ":" + String(password));
        return;
    }

    char speedChar = speed[0];
    const std::vector<char> availableSpeeds { '0', '1', '2', '3' };
    if (std::find(availableSpeeds.begin(), availableSpeeds.end(), speedChar) >= availableSpeeds.end()) {
        Serial.printf("Invalid speed! (%c)", speedChar);
        this->badRequest("Invalid speed!");
        return;
    }

    this->fanSpeed = this->changeSpeed(speedChar - '0');

    this->success(this->fanSpeed);
    Serial.printf("Current speed: %c\n", this->fanSpeed);
}

/// @brief Get length of the const char*
/// @param chars 
/// @return 
int Controller::len(const char* chars) {
    int c = 0;
    while(chars[c] != '\0') c++;
    return c;
}
