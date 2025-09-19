CREATE DATABASE IF NOT EXISTS home_automation;
USE home_automation;

CREATE TABLE IF NOT EXISTS sensor_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    sensor_type VARCHAR(50),
    value FLOAT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Example sensor_type values: 'temperature', 'humidity', 'distance'
