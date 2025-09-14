#include "esp_camera.h"
#include <WiFi.h>

const char *ssid = "motolm";
const char *password = "aaaaaaaa";

#define PWDN_GPIO_NUM  32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  0
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27

#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    21
#define Y4_GPIO_NUM    19
#define Y3_GPIO_NUM    18
#define Y2_GPIO_NUM    5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // Configuracoes da camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  config.frame_size = FRAMESIZE_XGA;
  config.jpeg_quality = 15; 
  config.fb_count = 1;     
  config.grab_mode = CAMERA_GRAB_LATEST;

  // Inicializa a câmera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("A inicialização da câmera falhou com o erro: 0x%x\n", err);
    Serial.println("Tentando reiniciar o dispositivo...");
    delay(1000);
    ESP.restart();
  }

  Serial.println("Câmera conectada.");

  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
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
  // Captura um frame
  camera_fb_t *fb = esp_camera_fb_get();

  if (!fb) {
    Serial.println("Captura de camera falhou.");
    return;
  }
  
  // dados da imagem disponiveis em in fb->buf
  // o tamanho da imagem em fb->len
  Serial.printf("Imagem capturada, tamanho: %u bytes\n", fb->len);

  /*
    No futuro serah realizada ao servidor web uma requisicao POST contendo o conteudo do qrcode/barcode da ultima foto tirada
    1. Escanear imagem
    2. Se tiver sido possivel escanear qrcode/barcvode (not null), enviar o conteudo para o servidor
    3. Se nao, continua
  */

  // liberacao do buffer de frame
  esp_camera_fb_return(fb);

  delay(5000);
}
