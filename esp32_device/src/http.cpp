#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Nhan Home";
const char* password = "nhanhome";

// IP MÁY TÍNH CHẠY DOCKER
const char* serverUrl = "http://192.168.1.221:3000/data";

unsigned long sendInterval = 1000; // 1 giây
unsigned long lastSend = 0;
int counter = 0;
const int MAX_SEND = 100;  // gửi đúng 100 lần

void setup() {
  Serial.begin(9600);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // nếu đã gửi đủ 100 gói thì dừng hẳn
  if (counter >= MAX_SEND) {
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    unsigned long now = millis();

    if (now - lastSend >= sendInterval) {
      lastSend = now;
      counter++;

      HTTPClient http;
      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");

      unsigned long ts = millis();

      String payload = "{"
        "\"device_id\":\"esp32_01\","
        "\"counter\":" + String(counter) + ","
        "\"ts\":" + String(ts) +
      "}";

      int httpCode = http.POST(payload);

      Serial.print("HTTP POST #");
      Serial.print(counter);
      Serial.print(" -> code: ");
      Serial.println(httpCode);

      http.end();
    }
  }

  delay(10);
}
