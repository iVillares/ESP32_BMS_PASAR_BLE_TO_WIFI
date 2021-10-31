# ESP32_BMS_PASAR_BLE_TO_WIFI
Convertir los datos de Bluetooth de las BMS compatibles a servidor WIFI
BMS compatibles:
JK-B2A24S1
JK-B2A24S2

# Requisitos previos
Es necesario las siguientes librerias.
ArduinoJson
ESPAsyncWebServer ->  https://github.com/me-no-dev/ESPAsyncWebServer
AsyncTCP -> https://github.com/me-no-dev/AsyncTCP
Placa de desarrollo Arduino ESP32 -> se ha utilizado para este proyecto la placa de desarrollo de Heltec Wifi kit 32 -> https://heltec.org/project/wifi-kit-32/
Se ha tenido que modificar el board.txt y añadir las siguientes lineas para que reconozca todo el almacenamiento de memoria ya que en caso contrario da error por falta de almacenamiento.

wifi_kit_32.menu.PartitionScheme.huge_app=Huge APP (3MB No OTA/1MB SPIFFS)
wifi_kit_32.menu.PartitionScheme.huge_app.build.partitions=huge_app
wifi_kit_32.menu.PartitionScheme.huge_app.upload.maximum_size=3145728

Durante el desarrollo de cicho proyecto se ha encontrado diferentes fallos deribado de las librerias de web asincrona ya que se quedaba bloqueadas las conexiónes.
Para resolver dicho evento se fuerza un reinicio de la placa ESP y con esto se consigue un funcionamiento mas duradero.

Las especificaciones de los registros de información y de los valores de celda se han seguindo los datos del siguiente proyecto:
https://github.com/jblance/mpp-solar

El tipo de informacion de celdas es el jk02 ya que ha sido de vital importacia el disponer de dicha información.

![IMG_6611](https://user-images.githubusercontent.com/67223906/139583861-0e8e435f-061e-4fbb-ad72-fddf9bb97183.jpg)

Video Funcionando.

https://user-images.githubusercontent.com/67223906/139584143-389e5ae4-04e6-4d87-9a6d-f0689508247d.mp4

El funcionamiento es muy similar al que se realiza por la app oficial Bluetooth pero con esto se puede consultarlo por wifi.
