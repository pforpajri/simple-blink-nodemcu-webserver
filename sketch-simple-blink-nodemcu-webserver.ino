#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(80);
 
const char* ssid = "v"; // SSID Sesuaikan
const char* password = "ppppp239"; // Password Sesuaikan
String page = "";
int LEDPin = 16; // Pin Sesuaikan

void setup() {
  pinMode(LEDPin, OUTPUT);

  page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  page += "<style> body{ text-align:center;}  </style>";
  page += "<h1>Simple Blink NodeMCU Web Server</h1><p><button onclick=\"window.location.href=\'nyala\' \">Nyala</button> <button onclick=\"window.location.href=\'mati\' \">Mati</button></p>";
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Tidak Terhubung");
  }
 
  Serial.println("");
  Serial.println("WiFi terhubung ");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Server berjalan...");

  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/nyala", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000);
  });
  server.on("/mati", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server berhasil dijalankan");
}
 
void loop() {
  server.handleClient();
}
