#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "YourID";
const char* password = "YourPassWord";

#define led 12
#define buzzer 26

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);

    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<html>");
            client.println("<head><meta content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html { margin: 0px auto; text-align: center;}");
            client.println(".botao_liga { background-color: #00FF00; color: white; padding: 15px 40px; border-radius: 25px;}");
            client.println(".botao_desliga { background-color: #FF0000; color: white; padding: 15px 40px; border-radius: 25px;}");
            client.println(".botao_liga_buzzer { background-color: #00FF00; color: white; padding: 15px 40px; border-radius: 25px;}");
            client.println(".botao_desliga_buzzer { background-color: #FF0000; color: white; padding: 15px 40px; border-radius: 25px;}</style></head>");
            client.println("<body><h1>Web Server com ESP32</h1>");

            client.println("<p><a href=\"/H\"><button class=\"botao_liga\">LIGA LED</button></a></p>");
            client.println("<p><a href=\"/L\"><button class=\"botao_desliga\">DESLIGA LED</button></a></p>");
            client.println("<p><a href=\"/BH\"><button class=\"botao_liga\">LIGA BUZZER</button></a></p>");
            client.println("<p><a href=\"/BL\"><button class=\"botao_desliga\">DESLIGA BUZZER</button></a></p>");
            client.println("<h3>By: GabrielCCouto</h3>");
            client.println("</body></html>");

            //client.print("Click <a href=\"/H\">here</a> LED ON.<br>");
            //client.print("Click <a href=\"/L\">here</a> LED OFF.<br>");
            //client.print("Click <a href=\"/BH\">here</a> Buzzer ON.<br>");
            //client.print("Click <a href=\"/BL\">here</a> Buzzer OFF.<br>");

            client.println();

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);
        }
        if (currentLine.endsWith("GET /BH")) {
          digitalWrite(buzzer, HIGH);
        }
        if (currentLine.endsWith("GET /BL")) {
          digitalWrite(buzzer, LOW); 
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}