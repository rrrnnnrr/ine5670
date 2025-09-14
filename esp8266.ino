#include <ESP8266WiFi.h>

const char *ssid = "motolm";
const char *password = "aaaaaaaa";

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Programa iniciado.");

  /*
    No futuro aqui serah aberta uma conexao websocket com o servidor para recebimento de mensagens 
    sobre o resultado de escanemantos de QRCode/barcode
  */


  // Conexao dos pins para teste
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);


  WiFi.begin(ssid, password);

  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Teste dos pins
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  delay(10000);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  delay(10000);
}
