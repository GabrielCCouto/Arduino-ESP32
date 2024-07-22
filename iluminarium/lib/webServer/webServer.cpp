#include "webServer.h"
#include "effects.h"
#include <ArduinoJson.h>


AsyncWebServer *server;

char SSID_AP[25];
char newID[25];

bool init_wifi_sta(String ssid, String pass)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    int attemps = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        if (attemps > 5)
        {
            printf("Max attemp\n");
            return false;
        }
        delay(1000);
        attemps++;
    }

    Serial.print("WiFi IP: ");
    Serial.println(WiFi.localIP());

    return true;
}

void init_wifi_ap()
{
    WiFi.mode(WIFI_AP);
    if (!WiFi.softAP("Iluminarium"))
    {
        Serial.println("[Wifi] Could not init WiFi AP Network");
    }
}

void configure_setup_server_routes(AsyncWebServer *server)
{
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    { request->send(SPIFFS, "/static/index.html", "text/html", false); });

    server->on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
    { request->send(SPIFFS, "/static/images/icons/favicon.ico", "image/x-icon", false); });

    // Handle the POST request to save credentials
    server->on("/save", HTTP_POST, [](AsyncWebServerRequest *request)
    {
        // Variables to store the credentials
        String wifiName = "";
        String password = "";

        // Get the form data
        if (request->hasParam("wifiName", true))
        {
            wifiName = request->getParam("wifiName", true)->value();
            Serial.printf("SSID: %s\n", wifiName);
        }
        if (request->hasParam("password", true))
        {
            password = request->getParam("password", true)->value();
            Serial.printf("Password: %s\n", password);
        }

        // Respond with a message (you can customize this)
        request->send(200, "text/plain", "Credentials saved: Wi-Fi Name - " + wifiName + ", Password - " + password);
        saveCredentialsToSPIFFS(wifiName, password);
    });
}

void saveCredentialsToSPIFFS(String wifiName, String password)
{
    // Create a JSON object to store the credentials
    StaticJsonDocument<256> jsonDocument;
    jsonDocument["wifiName"] = wifiName;
    jsonDocument["password"] = password;

    // Serialize the JSON object to a string
    String jsonStr;
    serializeJson(jsonDocument, jsonStr);

    // Open the SPIFFS file for writing
    File file = SPIFFS.open("/credentials.json", "w");
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }

    // Write the JSON string to the file
    file.println(jsonStr);
    file.close();
    Serial.println("Credentials saved to SPIFFS");
}

void create_web_server()
{
    server = new AsyncWebServer(80);
    configure_setup_server_routes(server);
    server->begin();
}

void saveConfigCallback ()
{
    Serial.println("Configuração salva");
    network_connected();
}

void readCredentialsFromSPIFFS(String &wifiName, String &password)
{
    // Open the SPIFFS file for reading
    File file = SPIFFS.open("/credentials.json", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    // Read the contents of the file into a string
    String jsonStr = "";
    while (file.available())
    {
        char c = file.read();
        jsonStr += c;
    }
    file.close();

    // Parse the JSON string into a JSON object
    DynamicJsonDocument jsonDocument(256);
    DeserializationError error = deserializeJson(jsonDocument, jsonStr);

    // Check for parsing errors
    if (error)
    {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    // Retrieve the credentials from the JSON object
    wifiName = jsonDocument["wifiName"].as<String>();
    password = jsonDocument["password"].as<String>();
}
