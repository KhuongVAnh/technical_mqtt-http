const express = require("express");
const fs = require("fs");

const app = express();
app.use(express.json());

app.post("/data", (req, res) => {
  const receiveTime = Date.now();
  const payloadSize = Buffer.byteLength(JSON.stringify(req.body));

  fs.appendFileSync(
    "http_log.csv",
    `${receiveTime},${payloadSize}\n`
  );

  res.sendStatus(200);
});

app.listen(3000, () => {
  console.log("HTTP server running on port 3000");
});
