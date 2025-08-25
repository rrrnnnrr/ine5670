// Código gerado pelo Gemini. Falta testar.

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// Configurações da rede Wi-Fi
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";

// Configurações do servidor
const char* serverAddress = "SEU_SERVIDOR.com";
const int serverPort = 80;
const char* serverPath = "/upload_image";

// Pinos dos LEDs
#define LED_VERDE D5
#define LED_AMARELO D6
#define LED_VERMELHO D7

// Pinos da câmera (substitua pelos pinos reais da sua conexão)
// #define CAM_D0 ...
// ...

// Tempo de acionamento do LED (em milissegundos)
const int ledDuration = 4000;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Configura os pinos dos LEDs como saída
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");
}

void loop() {
  // A cada 3 segundos...
  delay(3000);

  // Aqui você deve colocar o código para tirar a foto da câmera OV7670
  // e salvar os dados da imagem em um buffer (byte array)
  // A complexidade desta parte depende da biblioteca da câmera que você está usando
  // Exemplo: byte imageData[IMAGE_SIZE];
  // captureImage(imageData);

  // Se o Wi-Fi estiver conectado, envia a imagem para o servidor
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Conecta-se ao servidor
    http.begin(serverAddress, serverPort, serverPath);
    http.addHeader("Content-Type", "image/jpeg"); // Ou outro tipo de imagem

    Serial.println("Enviando foto para o servidor...");

    // Envia a imagem como requisição POST
    // Substitua 'imageData' pelo seu buffer da imagem
    int httpResponseCode = http.POST((uint8_t*)imageData, IMAGE_SIZE);

    if (httpResponseCode > 0) {
      Serial.print("Código de resposta: ");
      Serial.println(httpResponseCode);

      // Verifica o código de retorno e aciona o LED correspondente
      if (httpResponseCode == 200) {
        Serial.println("Coleta de dados bem-sucedida. Acendendo LED VERDE.");
        digitalWrite(LED_VERDE, HIGH);
        delay(ledDuration);
        digitalWrite(LED_VERDE, LOW);
      } else if (httpResponseCode == 400) {
        Serial.println("Erro: Link inválido. Acendendo LED VERMELHO.");
        digitalWrite(LED_VERMELHO, HIGH);
        delay(ledDuration);
        digitalWrite(LED_VERMELHO, LOW);
      } else if (httpResponseCode == 409) {
        Serial.println("Erro: Compra já coletada. Acendendo LED AMARELO.");
        digitalWrite(LED_AMARELO, HIGH);
        delay(ledDuration);
        digitalWrite(LED_AMARELO, LOW);
      }
      
      // Para qualquer outro código (como 204, 503, 422, etc.), o loop continua
      // sem acender um LED específico, como você mencionou no fluxo

    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
}
