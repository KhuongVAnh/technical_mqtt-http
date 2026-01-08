// #include <WiFi.h>
// #include <HTTPClient.h>

// // ====== CẤU HÌNH WIFI ======
// const char *ssid = "Nhan Home";
// const char *password = "nhanhome";

// // ====== HTTP SERVER ======
// const char *serverUrl = "http://192.168.1.202:3000/data";

// // ====== MÔ PHỎNG MẠNG KÉM ======
// #define NET_DELAY_MS 200 // delay 200ms
// #define LOSS_RATE 20     // ~5% mất gói (1/20)

// // ====== GỬI DỮ LIỆU ======
// unsigned long sendInterval = 1000; // 1 giây
// unsigned long lastSend = 0;
// int counter = 0;

// void setup()
// {
//     Serial.begin(9600);
//     delay(1000);

//     WiFi.begin(ssid, password);
//     Serial.print("Connecting to WiFi");

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("\nWiFi connected");
//     Serial.print("ESP32 IP: ");
//     Serial.println(WiFi.localIP());

//     randomSeed(esp_random());
// }

// void loop()
// {
//     unsigned long now = millis();

//     if (now - lastSend >= sendInterval)
//     {
//         lastSend = now;
//         counter++;

//         // ====== GIẢ LẬP MẤT GÓI ======
//         if (random(0, LOSS_RATE) == 0)
//         {
//             Serial.print("DROP HTTP #");
//             Serial.println(counter);
//             return; // bỏ qua lần gửi này
//         }

//         // ====== GIẢ LẬP DELAY MẠNG ======
//         delay(NET_DELAY_MS);

//         if (WiFi.status() == WL_CONNECTED)
//         {
//             HTTPClient http;
//             http.begin(serverUrl);
//             http.addHeader("Content-Type", "application/json");

//             unsigned long ts = millis();
//             String payload = "{"
//                              "\"device_id\":\"esp32_01\","
//                              "\"counter\":" +
//                              String(counter) + ","
//                                                "\"ts\":" +
//                              String(ts) +
//                              "}";

//             int httpCode = http.POST(payload);

//             Serial.print("HTTP POST #");
//             Serial.print(counter);
//             Serial.print(" -> code: ");
//             Serial.println(httpCode);

//             http.end();
//         }
//     }
// }
