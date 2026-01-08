const mqtt = require("mqtt");
const fs = require("fs");

console.log("Starting MQTT subscriber...");

const client = mqtt.connect("mqtt://mqtt-broker:1883");

client.on("connect", () => {
    console.log("MQTT subscriber connected");
    client.subscribe("iot/data");
});

client.on("message", (topic, message) => {
    const receiveTime = Date.now();
    const payloadSize = message.length;

    fs.appendFileSync(
        "mqtt_log.csv",
        `${receiveTime},${payloadSize}\n`
    );
});
