
# Data Integration & Automation (IoT Project)

This project implements a cost-effective IoT-based home automation system. It integrates **Raspberry Pi, Node-RED, MQTT, ESP8266 microcontrollers, GSM module, and MariaDB** to enable real-time monitoring, control, and predictive analytics.  

## Features
- Real-time monitoring of temperature, humidity, and motion
- SMS alerts using GSM module when temperature exceeds threshold
- Node-RED dashboard for visualization and control
- Data storage in MariaDB for analysis
- Modular design for scalability

## Tech Stack
- **Hardware:** Raspberry Pi 4, ESP8266 NodeMCU, DHT11, Ultrasonic Sensor, GSM SIM800A
- **Software:** Node-RED, MQTT (Mosquitto), MariaDB, Arduino IDE

## System Architecture
![Architecture Diagram](docs/architecture-diagram.jpeg)

## Setup Instructions
### Raspberry Pi
1. Install Raspberry Pi OS (64-bit).
2. Install Node-RED and enable it to run as a service:
   ```bash
   curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
   sudo apt-get install -y nodejs
   sudo npm install -g --unsafe-perm node-red
   sudo systemctl enable nodered.service
   ```
3. Install Mosquitto MQTT broker:
   ```bash
   sudo apt-get install -y mosquitto mosquitto-clients
   sudo systemctl enable mosquitto
   ```
4. Setup MariaDB and import schema:
   ```bash
   mysql -u root -p < raspberry-pi/mariadb-schema.sql
   ```

### ESP8266 Clients
- Flash ESP8266 boards using Arduino IDE.
- Example sketches are in `esp8266/`.

### Node-RED
- Import flow JSON from `node-red-flows/home_automation_flow.json`.
- Access dashboard at:  
  `http://<raspberry-pi-ip>:1880/ui`

## Project Outcomes
- 98% uptime and <500ms latency
- Real-time data visualization and control
- Scalable and low-cost IoT home automation

## Future Enhancements
- Add support for Alexa/Google Assistant
- Implement machine learning for predictive automation
- Energy optimization and advanced security

## License
MIT License
