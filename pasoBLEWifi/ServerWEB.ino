
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
   
   ws.cleanupClients();   
    if (strcmp((char*)data, "BMS1") == 0) {
        conectarDispositivoBLE(BMS1);
           
        // bms1
    }else {
      //bms2
       conectarDispositivoBLE(BMS2);
      
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      //Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      //Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void setup_SERVER() {
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //delay(2000);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Connect Failed! Rebooting...");
    delay(60000);
    ESP.restart();
  }
  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.onNotFound(handleNotFound);
  
  server.on("/bms",HTTP_GET,mostrarPaginaWEB);  
  server.on("/",HTTP_GET,mostrarPaginaWEB);  
    server.on("/reset",HTTP_GET,resetearESP);  

  
  //Serial.println();
  //Serial.print("Open http://");
  //Serial.print(WiFi.localIP());
  //Serial.println("/ in your browser to see it working");
  mensajePantalla("Conectado:",WiFi.localIP().toString(),"");
  
   ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.begin();
}
void mostrarPaginaWEB(AsyncWebServerRequest *request) 
{
    if (!request->authenticate(www_username, www_password))
    {
      return request->requestAuthentication();
    }
    request->send_P(200, "text/html", paginaHTML);
}
void resetearESP(AsyncWebServerRequest *request) 
{
    if (!request->authenticate(www_username, www_password))
    {
      return request->requestAuthentication();
    }
    ESP.restart();
}

void handleNotFound(AsyncWebServerRequest *request) 
{
   request->send(109, "text/plain", "");
}
void loop_SERVER() {
  
}
