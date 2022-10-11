
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>


// Conexion a punto de acceso wifi
#define WIFI_SSID "VTR-9479838"
#define WIFI_PASSWORD "t3pzYscJnkwh"

 float smoke0 = 0;
 
// El pin digital donde se conecta el sensor
#define DHTPIN 4
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

String data;

void setup() {
 dht.begin();
  
  pinMode(smoke0, INPUT);
  Serial.begin(9600);
  
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(700);
    Serial.print(".");
  }

  Serial.println ("");
  Serial.println ("Se conectó al wifi!");
  Serial.println(WiFi.localIP());
  
  
}



void loop() {
    
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float g = analogRead(smoke0);
   
 
  
  data ="temperatura="+String(t)+"&humedad="+String(h)+"&gas="+String(g);;
  
 
  
  if (client.connect("proyectosw.cl",80)) { // Preguntamos se si conectó a la IP del servidor 
    Serial.println("se conecto");
    client.println("POST https://proyectosw.cl/backend/setData.php HTTP/1.1"); 
    client.println("Host: proyectosw.cl"); // IP del servidor
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println();
    Serial.println(g);
   
 
    client.print(data); 
  } 

  if (client.connected()) { 
    client.stop();  // Disconectamos del servidor
  }

  delay(1000); // Cada 1 sengundo se envia los datos al servidor

}
