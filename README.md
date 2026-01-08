# 📡 MQTT vs HTTP Performance Evaluation in IoT

> **So sánh hiệu năng giữa MQTT và HTTP trong truyền thông IoT sử dụng ESP32 và Docker**

---

## 📌 1. Giới thiệu

Dự án này được xây dựng nhằm **đánh giá và so sánh hiệu năng** của hai giao thức truyền thông phổ biến trong Internet of Things (IoT): **HTTP** và **MQTT**.

Hệ thống sử dụng **ESP32** làm thiết bị IoT gửi dữ liệu, trong khi các thành phần backend được triển khai trên **máy tính Windows** thông qua **Docker** để giả lập môi trường Linux. Công cụ **NetEm** được sử dụng để mô phỏng các điều kiện mạng bất lợi.

Các chỉ số đánh giá chính:
- 📦 Tỷ lệ mất gói (Packet Loss)
- ⏱️ Độ trễ (Delay)
- 📉 Độ ổn định (Jitter)
- 🚀 Throughput
- 🌐 Overhead và mức sử dụng băng thông trên mỗi bản tin

---

## 🧱 2. Kiến trúc hệ thống

**Thành phần chính**:

- 🟦 **ESP32**: thiết bị IoT gửi dữ liệu định kỳ
- 🟧 **HTTP Server (Node.js)**: nhận HTTP POST và ghi log
- 🟩 **MQTT Broker (Mosquitto)**: trung gian truyền thông MQTT
- 🟪 **MQTT Subscriber (Node.js)**: nhận dữ liệu MQTT và ghi log
- 🐳 **Docker**: giả lập môi trường Linux và hỗ trợ NetEm

**Kịch bản thí nghiệm**:
- **Baseline**: mạng lý tưởng
- **Bad network**: mạng có độ trễ và mất gói (NetEm)

---

## 📂 3. Cấu trúc thư mục

```text
MQTT&HTTP/
│
├── esp32_device/
│   └── Source code ESP32 (HTTP & MQTT)
│
├── http-server/
│   ├── Dockerfile
│   ├── server.js
│   ├── http_baseline.csv
│   ├── http_bad.csv
│   └── esp32_bad_log.csv
│
├── mqtt-broker/
│   └── config/
│       └── mosquitto.conf
│
├── mqtt-subscriber/
│   ├── Dockerfile
│   ├── sub.js
│   ├── mqtt_baseline.csv
│   ├── mqtt_bad.csv
│   └── mqtt_bad_log.csv
│
└── README.md
```

## 🔧 4. Yêu cầu hệ thống

- 🖥️ **Windows 10 / 11**
- 🐳 **Docker Desktop**
- 📡 **ESP32**
- 🛠️ **Arduino IDE** hoặc **PlatformIO**

---

## ▶️ 5. Hướng dẫn triển khai

### 5.1. Tạo Docker network
```bash
docker network create iot-net
```

### 5.2. Chạy MQTT Broker
```bash
docker run -d \
  --name mqtt-broker \
  --network iot-net \
  -p 1883:1883 \
  eclipse-mosquitto
```
### 5.3. Chạy HTTP Server
```bash
docker build -t http-server ./http-server
```
Run container:

```bash
docker run -d \
  --name http-server \
  --network iot-net \
  -p 3000:3000 \
  http-server
```
### 5.4. Chạy MQTT Subscriber
Build image:

bash
docker build -t mqtt-subscriber ./mqtt-subscriber
Run container:

bash
docker run -d \
  --name mqtt-subscriber \
  --network iot-net \
  mqtt-subscriber
🌐 6. Mô phỏng mạng kém (NetEm)
Ví dụ cấu hình độ trễ 100ms và mất gói 5%:

bash
docker exec -it http-server \
  tc qdisc add dev eth0 root netem delay 100ms loss 5%
Gỡ cấu hình sau khi hoàn tất:

bash
docker exec -it http-server \
  tc qdisc del dev eth0 root
Có thể áp dụng tương tự cho mqtt-broker hoặc mqtt-subscriber.

📊 7. Thu thập & phân tích dữ liệu
Log được ghi tại phía nhận

Định dạng: CSV

Mỗi file tương ứng với 1 giao thức + 1 kịch bản

Danh sách file log
text
http_baseline.csv
http_bad.csv
mqtt_baseline.csv
mqtt_bad.csv
Mục đích sử dụng log
Tính delay & jitter

Tính throughput

Đánh giá tỷ lệ mất gói

Phân tích overhead băng thông

🔍 8. Ghi chú kỹ thuật
HTTP
Mô hình request–response

Mỗi bản tin phát sinh nhiều gói TCP:

Handshake

Response

Teardown

MQTT (QoS 0)
Kết nối duy trì

Mỗi bản tin chỉ gồm:

1 gói PUBLISH

1 gói ACK TCP

➡️ MQTT sử dụng băng thông hiệu quả hơn HTTP trong IoT.

🎯 9. Mục đích sử dụng
📘 Báo cáo kỹ thuật (technical writing and presentation)

🔬 Thí nghiệm so sánh giao thức

🚀 Nền tảng nghiên cứu mở rộng

👤 10. Thông tin
Tác giả: Khương Việt Anh – 20235257

Năm thực hiện: 2025
