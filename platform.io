; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:m5stick-c]
platform = espressif32
board = m5stick-c
framework = arduino
board_build.mcu = esp32
lib_deps = 
	https://github.com/m5stack/M5StickC-Plus.git
	fastled/FastLED@^3.5.0
	me-no-dev/ESP Async WebServer@^1.2.3
	bblanchon/ArduinoJson@^6.20.0
board_build.f_cpu = 240000000L
monitor_speed = 115200
