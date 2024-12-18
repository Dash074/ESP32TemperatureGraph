// HTML content with Chart.js
const char htmlContent[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Temperature Monitor</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>
  <h1>Real-Time Temperature Graph</h1>
  <canvas id="tempChart" width="400" height="200"></canvas>
  <script>
    const ctx = document.getElementById('tempChart').getContext('2d');
    const tempChart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [], // Time labels
        datasets: [{
          label: 'Temperature (°C)',
          data: [],
          borderColor: 'rgb(75, 192, 192)',
          tension: 0.1
        }]
      }
    });

    const ws = new WebSocket('ws://' + window.location.host + '/ws');

    ws.onmessage = function(event) {
      const json = JSON.parse(event.data);
      const time = new Date().toLocaleTimeString();
      tempChart.data.labels.push(time);
      tempChart.data.datasets[0].data.push(json.temperature);

      if (tempChart.data.labels.length > 20) {
        tempChart.data.labels.shift();
        tempChart.data.datasets[0].data.shift();
      }

      tempChart.update();
    };
  </script>
</body>
</html>
)rawliteral";

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// WiFi credentials
const char* ssid = "realnigga";
const char* password = "meow3000";

// LM35 sensor pin
const int LM35_PIN = 36; // Use an ADC pin (e.g., GPIO34)

// Web server and WebSocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Function to read temperature from LM35
float readTemperature() {
  int adcValue = analogRead(LM35_PIN); // Read analog value
  float voltage = adcValue * (3.3 / 4095.0); // Convert ADC value to voltage
  float temperature = voltage * 100.0; // Convert voltage to Celsius (LM35: 10mV/°C)
  return temperature;
}

// Function to handle WebSocket events
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  }
}

// Function to send temperature data via WebSocket
void sendTemperature() {
  float temperature = readTemperature();
  String json = "{\"temperature\":" + String(temperature) + "}";
  ws.textAll(json);
}

void setup() {
  Serial.begin(115200);
  pinMode(LM35_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the IP address after connecting to WiFi
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print the local IP address

  // Serve WebSocket
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  // Serve HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", htmlContent);
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  sendTemperature();
  delay(1000); // Update every second
}
