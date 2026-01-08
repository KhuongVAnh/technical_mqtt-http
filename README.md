MQTT vs HTTP Performance Evaluation in IoT
So sánh hiệu năng giữa MQTT và HTTP trong truyền thông IoT sử dụng ESP32 và Docker
==========================================================================

1. GIỚI THIỆU
-------------
Dự án này được xây dựng nhằm đánh giá và so sánh hiệu năng của hai giao thức
truyền thông phổ biến trong Internet of Things (IoT): HTTP và MQTT.

Hệ thống sử dụng ESP32 làm thiết bị IoT gửi dữ liệu. Các thành phần backend
được triển khai trên máy tính Windows thông qua Docker để giả lập môi trường
Linux. Công cụ NetEm được sử dụng để mô phỏng các điều kiện mạng bất lợi.

Các chỉ số đánh giá:
- Packet Loss (Tỷ lệ mất gói)
- Delay (Độ trễ)
- Jitter (Độ ổn định)
- Throughput (Lưu lượng truyền)
- Overhead và mức sử dụng băng thông trên mỗi bản tin


2. KIẾN TRÚC HỆ THỐNG
--------------------
Thành phần chính:
- ESP32: Thiết bị IoT gửi dữ liệu định kỳ
- HTTP Server (Node.js): Nhận HTTP POST và ghi log
- MQTT Broker (Mosquitto): Trung gian truyền thông MQTT
- MQTT Subscriber (Node.js): Nhận dữ liệu MQTT và ghi log
- Docker: Giả lập môi trường Linux và hỗ trợ NetEm

Kịch bản thí nghiệm:
- Baseline: Mạng lý tưởng
- Bad Network: Mạng có độ trễ và mất gói (NetEm)


3. CẤU TRÚC THƯ MỤC
------------------
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
└── README.txt


4. YÊU CẦU HỆ THỐNG
------------------
- Windows 10 / 11
- Docker Desktop
- ESP32
- Arduino IDE hoặc PlatformIO


5. HƯỚNG DẪN TRIỂN KHAI
----------------------

5.1. Tạo Docker network
docker network create iot-net

5.2. Chạy MQTT Broker
docker run -d \
  --name mqtt-broker \
  --network iot-net \
  -p 1883:1883 \
  eclipse-mosquitto

5.3. Chạy HTTP Server
Build image:
docker build -t http-server ./http-server

Run container:
docker run -d \
  --name http-server \
  --network iot-net \
  -p 3000:3000 \
  http-server

5.4. Chạy MQTT Subscriber
Build image:
docker build -t mqtt-subscriber ./mqtt-subscriber

Run container:
docker run -d \
  --name mqtt-subscriber \
  --network iot-net \
  mqtt-subscriber


6. MÔ PHỎNG MẠNG KÉM (NETEM)
---------------------------
Ví dụ cấu hình độ trễ 100ms và mất gói 5%:
docker exec -it http-server \
  tc qdisc add dev eth0 root netem delay 100ms loss 5%

Gỡ cấu hình sau khi hoàn tất:
docker exec -it http-server \
  tc qdisc del dev eth0 root

Có thể áp dụng tương tự cho mqtt-broker hoặc mqtt-subscriber.


7. THU THẬP & PHÂN TÍCH DỮ LIỆU
-------------------------------
Log được ghi tại phía nhận.
Định dạng file: CSV.

Danh sách file log:
- http_baseline.csv
- http_bad.csv
- mqtt_baseline.csv
- mqtt_bad.csv

Mục đích phân tích:
- Tính delay và jitter
- Tính throughput
- Đánh giá tỷ lệ mất gói
- Phân tích overhead băng thông


8. GHI CHÚ KỸ THUẬT
------------------
HTTP:
- Mô hình request – response
- Mỗi bản tin phát sinh nhiều gói TCP:
  + Handshake
  + Response
  + Teardown

MQTT (QoS 0):
- Kết nối duy trì liên tục
- Mỗi bản tin chỉ gồm:
  + 1 gói PUBLISH
  + 1 gói ACK TCP

=> MQTT sử dụng băng thông hiệu quả hơn HTTP trong IoT.


9. MỤC ĐÍCH SỬ DỤNG
------------------
- Báo cáo kỹ thuật
- Thí nghiệm so sánh giao thức
- Nền tảng nghiên cứu mở rộng


10. THÔNG TIN
-------------
Tác giả: Khương Việt Anh – 20235257
Năm thực hiện: 2025
