# Arduino MQTT RF Transmitter

This Arduino project utilizes an ESP8266 module to connect to Wi-Fi and an MQTT broker, allowing you to transmit data wirelessly using an RCSwitch transmitter.

For example this can be used whenever a button is pressed from another device, we can automate lights or doorbells over 433mhz.

## Prerequisites

To run this project, you will need the following:

- Arduino board and 433mhz transmitter
- Wi-Fi network with credentials (SSID and password)
- MQTT broker server with configuration details (server address, port, user, and password)

## Wiring Diagram

| NodeMCU | 433MHz Transmitter |
|---------|--------------------|
| D2      | Data Pin           |
| 3.3v    | VCC                |
| GND     | GND                |

## Installation

1. Clone or download this repository.

2. Open the Arduino IDE and install the following libraries:
   - `ESP8266WiFi`
   - `PubSubClient`
   - `RCSwitch`

3. Connect your Arduino board with the ESP8266 module to your computer.

4. Open the Arduino sketch file (`arduino_mqtt_rf_transmitter.ino`) in the Arduino IDE.

5. Modify the following variables in the sketch to match your Wi-Fi and MQTT settings:
   - `ssid`: Your Wi-Fi network SSID
   - `password`: Your Wi-Fi network password
   - `mqttServer`: Your MQTT broker server address
   - `mqttPort`: MQTT broker port (usually 1883)
   - `mqttUser`: MQTT username (if applicable)
   - `mqttPassword`: MQTT password (if applicable)
   - `mqttTopic`: MQTT topic to subscribe and transmit on
   - `transmitterPin`: The pin connected to the RF transmitter (D2 by default)
   - `transmitterProtocol`: Protocol used by the RF transmitter
   - `transmitterPulseLength`: Pulse length for the RF transmitter
   - `transmissionData`: Data to be transmitted wirelessly
   - `transmissionLength`: Length of the transmission data

6. Upload the sketch to your Arduino board.

7. Open the Serial Monitor to view the debug output and verify the Wi-Fi and MQTT connections.

8. Once connected, sending an MQTT message to the subscribed topic (`mqttTopic`) will trigger the transmission of data using the RCSwitch transmitter.

## License

This project is licensed under the [MIT License](LICENSE).
