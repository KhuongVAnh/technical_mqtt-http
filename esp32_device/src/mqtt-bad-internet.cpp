// #include <WiFi.h>
// #include <PubSubClient.h>

// // ====== WIFI ======
// const char* ssid = "Nhan Home";
// const char* password = "nhanhome";

// // IP MÁY TÍNH (MQTT Broker chạy Docker)
// const char* mqttServer = "192.168.1.202";
// const int mqttPort = 1883;

// // ====== MÔ PHỎNG MẠNG KÉM ======
// #define NET_DELAY_MS 200     // delay 200ms
// #define LOSS_RATE 20         // ~5% mất gói (1/20)

// // ====== MQTT CLIENT ======
// WiFiClient espClient;
// PubSubClient client(espClient);

// // ====== GỬI DỮ LIỆU ======
// unsigned long sendInterval = 1000; // 1 giây
// unsigned long lastSend = 0;
// int counter = 0;

// void setup() {
//   Serial.begin(9600);
//   delay(1000);

//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi");

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("\nWiFi connected");
//   Serial.print("ESP32 IP: ");
//   Serial.println(WiFi.localIP());

//   client.setServer(mqttServer, mqttPort);

//   Serial.print("Connecting to MQTT broker");
//   while (!client.connected()) {
//     if (client.connect("esp32_01")) {
//       Serial.println("\nMQTT connected");
//     } else {
//       Serial.print(".");
//       delay(1000);
//     }
//   }

//   randomSeed(esp_random());
// }

// void loop() {
//   if (!client.connected()) {
//     client.connect("esp32_01");
//   }
//   client.loop();

//   unsigned long now = millis();
//   if (now - lastSend >= sendInterval) {
//     lastSend = now;
//     counter++;

//     // ====== GIẢ LẬP MẤT GÓI ======
//     if (random(0, LOSS_RATE) == 0) {
//       Serial.print("DROP MQTT #");
//       Serial.println(counter);
//       return;
//     }

//     // ====== GIẢ LẬP DELAY MẠNG ======
//     delay(NET_DELAY_MS);

//     unsigned long ts = millis();
//     String payload = "{"
//       "\"device_id\":\"esp32_01\","
//       "\"counter\":" + String(counter) + ","
//       "\"ts\":" + String(ts) +
//     "}";

//     client.publish("iot/data", payload.c_str());

//     Serial.print("MQTT publish #");
//     Serial.println(counter);
//   }
// }
