Creating a README file for your Arduino program on GitHub helps others understand how to use and contribute to your project. Here’s a basic template you can use to get started:

---

# Arduino DHT Sensor Data to Firebase

This Arduino sketch reads temperature and humidity from a DHT11 sensor and sends the data to Firebase Realtime Database.

## Requirements

- Arduino board (e.g., ESP32)
- DHT11 temperature and humidity sensor
- Access to Firebase Realtime Database

## Setup Instructions

1. **Install Libraries:**
   - Make sure you have the following libraries installed in your Arduino IDE:
     - [Firebase ESP32 Client](https://github.com/mobizt/Firebase-ESP32)
     - [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)

2. **Update Wi-Fi Credentials:**
   - Replace `ssid` and `password` in the sketch with your Wi-Fi network credentials.

3. **Firebase Configuration:**
   - Replace `FIREBASE_HOST` with your Firebase Realtime Database URL.
   - Replace `FIREBASE_AUTH` with your Firebase Legacy Authentication token.

4. **Connect DHT Sensor:**
   - Connect your DHT11 sensor to the specified digital pin (`DHTPIN`).

5. **Upload and Run:**
   - Upload the sketch to your Arduino board and open the Serial Monitor to view temperature, humidity, and Firebase interaction logs.

## Firebase Database Structure

- Data is stored under the `/DHT11` node in Firebase with the following structure:
  ```
  /DHT11
      /Humidity: <value>
      /Temperature: <value>
      /HeatIndexC: <value>
      /HeatIndexF: <value>
  ```

## Troubleshooting

- **Sensor Read Failures:** If readings fail, check sensor wiring and connections.
- **Firebase Errors:** Ensure correct Firebase credentials and network connectivity.

## Contributing

- Fork the repository, make your changes, and submit a pull request.
- Report issues or suggestions using GitHub issues.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
# ESP32 Temperature Monitoring with Firebase Integration

This project demonstrates how to monitor temperature and humidity using a DHT11 sensor with an ESP32 board. The sensor readings are sent to Firebase Realtime Database for remote monitoring.

## Components Used

- **ESP32 Development Board**
- **DHT11 Temperature and Humidity Sensor**
- **Firebase Realtime Database**

## Pin Connections

### ESP32 Pinout:

markdown
Copy code
DHT11 Sensor:
---------------------
| DHT11  | ESP32     |
|--------|-----------|
| +      | 3.3V      |
| OUT    | GPIO 4 (D4)|
| -      | GND       |
---------------------

Firebase:
-----------------------------
| Firebase RTDB | ESP32       |
|---------------|-------------|
| VCC           | 3.3V/5V     |
| GND           | GND         |
| SCL           | GPIO 21 (D21)|
| SDA           | GPIO 22 (D22)|
-----------------------------
markdown
Copy code

### Notes:

- **DHT11**: Connect the VCC pin to 3.3V or 5V based on your ESP32 board's voltage, OUT to GPIO 4 (D4), and - to GND.
- **Firebase**: Ensure correct power supply (VCC and GND) and connect SCL to GPIO 21 (D21) and SDA to GPIO 22 (D22) on ESP32.

## Usage

1. **Setup Firebase**:
   - Create a Firebase project and enable Realtime Database.
   - Note down your Firebase project details (FIREBASE_HOST, FIREBASE_AUTH) and replace them in the Arduino sketch.

2. **Upload Code**:
   - Upload the provided Arduino sketch (`esp32temp.ino`) to your ESP32 board using the Arduino IDE.

3. **Monitor Data**:
   - Open the Serial Monitor to view temperature, humidity, and heat index readings.
   - Check Firebase Realtime Database for remote monitoring of sensor data.

## Example Code

```cpp
// Your Arduino code goes here
