#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char APIKEY[] = "huytfrdf765KEYKEYKEYKEYKEYKEYKEYKEYKEY"; // Put here your API key. It's in the dashboard
char CHANNEL[] = "Channel";                               // and here your channel name

char serverName[] = "api.pushetta.com";
boolean lastConnected = false;

int status = WL_IDLE_STATUS;
const char* ssid = "ssid";  //  your network SSID (name)
const char* pass = "password";   // your network password

IPAddress ipMulti (192, 168, 1, 255);

void setup() {
  WiFiClient client;

  Serial.begin(9600);
  
  // setting up Station AP
  WiFi.begin(ssid, pass);

  // Wait for connect to AP
  Serial.print("[Connecting]");
  Serial.print(ssid);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 30) {
      break;
    }
  }
  Serial.println("Connected to wifi");

}

void loop()
{

  Serial.println("Connecting to Pushetta");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect("api.pushetta.com", httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  sendToPushetta(CHANNEL, "Hello world!");
  delay(60000);
}


//Function for sending the request to Pushetta
void sendToPushetta(char channel[], String text) {
  WiFiClient client;
  client.stop();

  if (client.connect(serverName, 80))
  {
    client.print("POST /api/pushes/");
    client.print(channel);
    client.println("/ HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.print("Authorization: Token ");
    client.println(APIKEY);
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(text.length() + 46);
    client.println();
    client.print("{ \"body\" : \"");
    client.print(text);
    client.println("\", \"message_type\" : \"text/plain\" }");
    client.println();
  }
}
