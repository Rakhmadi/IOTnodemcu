#include <Arduino.h>
#include<ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const int LED = 13; // GPIO 16
const char* ssid = "HexaTera";
const char* password = "qwertyuiop";


WiFiServer server(80);

void setup()
{
 Serial.begin(115200);
 pinMode(LED, OUTPUT);
 Serial.print("Connecting to the Newtork");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
   delay(500);
   Serial.print(".");
 }
 Serial.println("WiFi connected");
 server.begin();  // Starts the Server
 Serial.println("Server started");

 Serial.print("IP Address of network: ");
 Serial.println(WiFi.localIP());
 Serial.println("/");
}

void loop()
{
 
 WiFiClient client = server.available();
 if (!client)
 {
   return;
 }
 Serial.println("Waiting for new client");
 while(!client.available())
 {
   delay(1);
 }

 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();

 int value = LOW;
 if(request.indexOf("/?LED=ON") != -1)
 {
   digitalWrite(LED, LOW); // Turn ON LED
   value = LOW;
 }
 if(request.indexOf("/?LED=OFF") != -1)
 {
   digitalWrite(LED, HIGH); // Turn OFF LED
   value = HIGH;
 }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *"); 
  client.println();

 client.println("");
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
  client.println("<head>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>");
 client.println("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>");
  client.println("</head>");
   client.println("<body>");
 client.print("LED: ");

 if(value == HIGH)
 {
   client.print("ON");
 }
 else
 {
   client.print("OFF");
 }
 client.println("<br><br>");
 client.println("<a  class='btn btn-primary' href=\"/LED=ON\"\">On</a>");
 client.println("<a  class='btn btn-primary'  href=\"/LED=OFF\"\">Off</a><br />");
  client.println("<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>");
   client.println("<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'</script>");
    client.println("<script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>");
  client.println("</body>");
 client.println("</html>");

 delay(1);
 Serial.println("Client disonnected");
 Serial.println("");
}