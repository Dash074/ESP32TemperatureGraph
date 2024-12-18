
# ESP32 Temperature Monitor with Real-Time Graph

This project demonstrates how to monitor the temperature using an LM35 sensor connected to an ESP32 and display the real-time temperature data on a webpage using FastAPI and WebSocket. The temperature data is visualized using a line graph created with Chart.js.

## Features

- **Real-Time Temperature Monitoring**: Collects data from the LM35 temperature sensor and sends it to a client via WebSocket.
- **Web Interface**: Displays the real-time temperature data on a graph using Chart.js.
- **WebSocket Communication**: Uses WebSocket to stream temperature data continuously.
  
## Components

- **ESP32**: Microcontroller to read temperature data and serve the webpage.
- **LM35 Temperature Sensor**: Analog temperature sensor to measure the temperature in Celsius.
- **Chart.js**: JavaScript library to plot the temperature data on a real-time graph.
- **WebSocket**: Used for real-time communication between the ESP32 and the browser.

## Requirements

- **Hardware**:
  - ESP32 Development Board
  - LM35 Temperature Sensor
  - Jumper wires

- **Software**:
  - Arduino IDE (for ESP32 programming)
  - ESPAsyncWebServer Library (for handling web requests)
  - WiFi.h (for Wi-Fi connectivity)
  - Chart.js (for plotting the graph in the web interface)

## Installation

### 1. **Set Up the Hardware**:

- Connect the LM35 sensor to the ESP32:
  - **LM35 VCC** → **3.3V (or 5V)** on ESP32
  - **LM35 GND** → **GND** on ESP32
  - **LM35 Output Pin** → **GPIO36 (ADC pin)** on ESP32

### 2. **Upload the Code to the ESP32**:

1. Open the Arduino IDE and install the **ESP32** board if you haven't already. Follow [this guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) to install ESP32 board support.
   
2. Install the following libraries in the Arduino IDE:
   - **ESPAsyncWebServer**
   - **AsyncTCP**
   
   You can install these libraries by going to **Sketch > Include Library > Manage Libraries** and searching for them.

3. Copy the provided code into the Arduino IDE and upload it to the ESP32.

### 3. **Configure Wi-Fi Credentials**:

Edit the following section of the code to add your Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 4. **Monitor the Serial Output**:

Open the **Serial Monitor** in the Arduino IDE and set the baud rate to **115200**. After uploading the code, the ESP32 will attempt to connect to your Wi-Fi network. Once connected, it will print the IP address of the ESP32:

```
Connecting to WiFi...
Connected to WiFi
IP Address: 192.168.x.x
```

### 5. **Access the Web Interface**:

- Open a web browser on a device connected to the same Wi-Fi network as the ESP32.
- In the browser's address bar, enter the IP address printed in the Serial Monitor:
  ```
  http://192.168.x.x
  ```
- The temperature graph should be displayed on the webpage.

  ![unnamed (1)](https://github.com/user-attachments/assets/604128b0-0a48-429d-ad58-0884c312549f)

- If everything works you will see the graph updating in real-time!

## How It Works

- The ESP32 reads the temperature from the LM35 sensor every second.
- It sends the temperature data to the client (browser) via WebSocket.
- The client receives the temperature data and updates the real-time graph on the webpage using **Chart.js**.
- The graph is updated every second with the latest temperature reading.

## Troubleshooting

- **Can't access the website**: Make sure both your ESP32 and the device you're using to access the website are connected to the same Wi-Fi network.
- **Serial Monitor shows "Connecting to WiFi..."**: Ensure that the Wi-Fi credentials are correct.
- **IP address not appearing in Serial Monitor**: Check if the ESP32 is correctly powered and the Wi-Fi network is stable.
- If you are seeing weird hieroglyphics ( ex: �XO1�� ) check the baud rate of your code and serial monitor and adjust accordingly.

