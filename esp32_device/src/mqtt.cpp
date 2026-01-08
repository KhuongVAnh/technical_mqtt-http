// #include <WiFi.h>
// #include <PubSubClient.h>

// const char* ssid = "Nhan Home";
// const char* password = "nhanhome";

// // IP MÁY TÍNH (MQTT Broker chạy Docker)
// const char* mqttServer = "192.168.1.221";
// const int mqttPort = 1883;

// WiFiClient espClient;
// PubSubClient client(espClient);

// unsigned long sendInterval = 100; // 1 giây
// unsigned long lastSend = 0;

// int counter = 0;
// const int MAX_SEND = 500;   // 🔴 CHỈ GỬI 300 LẦN
// bool finished = false;     // đánh dấu đã gửi xong

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
// }

// void loop() {
//   if (finished) {
//     // DỪNG HOÀN TOÀN
//     return;
//   }

//   if (!client.connected()) {
//     client.connect("esp32_01");
//   }
//   client.loop();

//   unsigned long now = millis();
//   if (now - lastSend >= sendInterval && counter < MAX_SEND) {
//     lastSend = now;
//     counter++;

//     unsigned long ts = millis();

//     String payload = "{"
//       "\"device_id\":\"esp32_01\","
//       "\"counter\":" + String(counter) + ","
//       "\"ts\":" + String(ts) +
//     "}";

//     client.publish("iot/data", payload.c_str());

//     Serial.print("MQTT publish #");
//     Serial.println(counter);

//     // ✅ GỬI ĐỦ 300 LẦN
//     if (counter >= MAX_SEND) {
//       finished = true;
//       Serial.println("✅ DONE: Sent 100 messages, stop publishing");
//       client.disconnect(); // optional
//     }
//   }
// }
