/**
 * A BLE client example that is rich in capabilities.
 * There is a lot new capabilities implemented.
 * author unknown
 * updated by chegewara
 */


#include <BLEDevice.h>
#include "Definiciones.h"
#include <heltec.h>
#include <WiFi.h>

#include <ArduinoJson.h>


#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

const char* ssid = "WIFI";
const char* password = "PASSWORD";
AsyncWebServer server(80);

AsyncWebSocket ws("/wsbms");

const char* www_username = "user";
const char* www_password = "password";

static BLEAddress direccionServerBMS[2]={BLEAddress("xx:xx:xx:xx:xx:xx"),BLEAddress("xx:xx:xx:xx:xx:xx")}; // BMS1 y BMS2

 TipoDispositivo dispositivoServerBMS_actual=NINGUNO;
 TipoDispositivo dispositivoReconectar=NINGUNO;
 bool isReconectarBLE =false;


static BLEUUID               UUID_DESCRIPTOR("00002902-0000-1000-8000-00805f9b34fb");
static BLEUUID    UUID_NOTIFY_CHARACTERISTIC("0000ffe1-0000-1000-8000-00805f9b34fb"); 
static BLEUUID            UUID_NOTIFY_SERVER("0000ffe0-0000-1000-8000-00805f9b34fb"); 
static BLEUUID      UUID_READ_CHARACTERISTIC("0000ffe3-0000-1000-8000-00805f9b34fb"); 
static BLEUUID     UUID_WRITE_CHARACTERISTIC("0000ffe2-0000-1000-8000-00805f9b34fb"); 
static BLEUUID             UUID_WRITE_SERVER("0000ffe1-0000-1000-8000-00805f9b34fb"); 

static uint8_t datosHabilitarRead[] = { 0x01,0x00 };
static uint8_t datosGetInfo[] =   { 0xaa ,0x55 ,0x90 ,0xeb ,0x97 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x11 };
static uint8_t datosCellInfo[] =  { 0xaa ,0x55 ,0x90 ,0xeb ,0x96 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x10 };
                                
static const int hastaInicioESP=3600;  // 1 hora. cada hora se resetea el esp para limpiar problemas.
static const int tiempoFinalFuncionamientoBMS=1*60; //1 minunos
long tiempoInicioESP=0;
long tiempoInicioFuncionamientoBMS=0;
long tiempoPantallaEnvio=0;

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;
static const int nDispositivos=2;
static byte  datosRespuesta[2][300]={0};

static int  len_datosRespuesta[nDispositivos]={0};

static int tipoRegistroPeticion[nDispositivos]={0};
static RegistroInfo registroInformacionBMS[nDispositivos];
static RegistroCelda registroInfoCeldaBMS[nDispositivos];


bool poderPedir=false;
BLEClient* pClient;

 




 void mostrarInformacionBMS(TipoDispositivo tipo){
  //return;  
  /*
  Serial.println();
  Serial.println("Informacion BMS");
  Serial.println("-------------------------------");
  Serial.println();
  //mensajePantalla("Informacion", Hex2Ascii(registroInformacionBMS[tipo].registro.deviceModel,9), Hex2Ascii(registroInformacionBMS[tipo].registro.serialNumber,13));
  Serial.print("Nombre: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.deviceName,16));
  Serial.print("Modelo: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.deviceModel,10));//
  Serial.print("Numero Serie: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.serialNumber,14));//
   Serial.print("Version hardware: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.hardwareVersion,10));//
   Serial.print("Version Software: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.softwareVersion,10));//
   Serial.print("devicePassCode: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.devicePassCode,10));//
   Serial.print("settingsPassCode: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.settingsPassCode,16));//
    Serial.print("manufacturaDate: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.manufacturaDate,16));//
    Serial.print("userData: ");
  Serial.println(Hex2Ascii(registroInformacionBMS[tipo].registro.userData,16));//
  */
}

 DynamicJsonDocument pasarInfoCellJSON(RegistroCelda registroCelda,TipoDispositivo tipo,TipoDispositivo activo){
   DynamicJsonDocument dev(2048);
  
   dev["timex"]=getUptime(registroCelda.registro.uptime);
   dev["dispositivoactivo"]=tipo==activo;
   dev["change"]="on";
   dev["discharge"]="on";
   dev["balance"]="on";
   dev["total_vol"]=LittleHexUInt(registroCelda.registro.battery_voltage)/1000;
   dev["total_amp"]=LittleHexLInt(registroCelda.registro.balance_current)/1000;
   dev["remainbattery"]=Little1HexInt(registroCelda.registro.percent_remain);
   dev["batterypower"]=LittleHexLUInt(registroCelda.registro.battery_power)/1000;
    dev["batterycapacity"]=LittleHexLUInt(registroCelda.registro.nominal_capacity)/1000;
    dev["capacityremain"]=LittleHexLUInt(registroCelda.registro.capacity_remain)/1000;
    dev["cyclecapacity"]=LittleHexLUInt(registroCelda.registro.cycle_capacity)/1000;
    dev["cyclecount"]=LittleHexUInt(registroCelda.registro.cycle_count);    
    dev["avecellvol"]=LittleHexUInt(registroCelda.registro.average_cell_vol)/1000;
    dev["deltacellvol"]=LittleHexUInt(registroCelda.registro.delta_cell_vol)/1000;
    dev["balancecur"]=LittleHexUInt(registroCelda.registro.current_balancer)/1000;
    dev["mostemp"]=LittleHexUInt(registroCelda.registro.MOS_temp)/10;
    dev["batteryt1"]=LittleHexUInt(registroCelda.registro.battery_t1)/10;
    dev["batteryt2"]=LittleHexUInt(registroCelda.registro.battery_t2)/10;
    dev["vol01"]=LittleHexUInt(registroCelda.registro.volCell1)/1000;
    dev["vol02"]=LittleHexUInt(registroCelda.registro.volCell2)/1000;
    dev["vol03"]=LittleHexUInt(registroCelda.registro.volCell3)/1000;
    dev["vol04"]=LittleHexUInt(registroCelda.registro.volCell4)/1000;
    dev["vol05"]=LittleHexUInt(registroCelda.registro.volCell5)/1000;
    dev["vol06"]=LittleHexUInt(registroCelda.registro.volCell6)/1000;
    dev["vol07"]=LittleHexUInt(registroCelda.registro.volCell7)/1000;
    dev["vol08"]=LittleHexUInt(registroCelda.registro.volCell8)/1000;
    dev["vol09"]=LittleHexUInt(registroCelda.registro.volCell9)/1000;
    dev["vol10"]=LittleHexUInt(registroCelda.registro.volCell10)/1000;
    dev["vol11"]=LittleHexUInt(registroCelda.registro.volCell11)/1000;
    dev["vol12"]=LittleHexUInt(registroCelda.registro.volCell12)/1000;
    dev["vol13"]=LittleHexUInt(registroCelda.registro.volCell13)/1000;
    dev["vol14"]=LittleHexUInt(registroCelda.registro.volCell14)/1000;
    dev["vol15"]=LittleHexUInt(registroCelda.registro.volCell15)/1000;
    dev["vol16"]=LittleHexUInt(registroCelda.registro.volCell16)/1000;
    dev["vol17"]=LittleHexUInt(registroCelda.registro.volCell17)/1000;
    dev["vol18"]=LittleHexUInt(registroCelda.registro.volCell18)/1000;
    dev["vol19"]=LittleHexUInt(registroCelda.registro.volCell19)/1000;
    dev["vol20"]=LittleHexUInt(registroCelda.registro.volCell20)/1000;
    dev["vol21"]=LittleHexUInt(registroCelda.registro.volCell21)/1000;
    dev["vol22"]=LittleHexUInt(registroCelda.registro.volCell22)/1000;
    dev["vol23"]=LittleHexUInt(registroCelda.registro.volCell23)/1000;
    dev["vol24"]=LittleHexUInt(registroCelda.registro.volCell24)/1000;
    dev["res01"]=LittleHexUInt(registroCelda.registro.resCell1)/1000;
    dev["res02"]=LittleHexUInt(registroCelda.registro.resCell2)/1000;
    dev["res03"]=LittleHexUInt(registroCelda.registro.resCell3)/1000;
    dev["res04"]=LittleHexUInt(registroCelda.registro.resCell4)/1000;
    dev["res05"]=LittleHexUInt(registroCelda.registro.resCell5)/1000;
    dev["res06"]=LittleHexUInt(registroCelda.registro.resCell6)/1000;
    dev["res07"]=LittleHexUInt(registroCelda.registro.resCell7)/1000;
    dev["res08"]=LittleHexUInt(registroCelda.registro.resCell8)/1000;
    dev["res09"]=LittleHexUInt(registroCelda.registro.resCell9)/1000;
    dev["res10"]=LittleHexUInt(registroCelda.registro.resCell10)/1000;
    dev["res11"]=LittleHexUInt(registroCelda.registro.resCell11)/1000;
    dev["res12"]=LittleHexUInt(registroCelda.registro.resCell12)/1000;
    dev["res13"]=LittleHexUInt(registroCelda.registro.resCell13)/1000;
    dev["res14"]=LittleHexUInt(registroCelda.registro.resCell14)/1000;
    dev["res15"]=LittleHexUInt(registroCelda.registro.resCell15)/1000;
    dev["res16"]=LittleHexUInt(registroCelda.registro.resCell16)/1000;
    dev["res17"]=LittleHexUInt(registroCelda.registro.resCell17)/1000;
    dev["res18"]=LittleHexUInt(registroCelda.registro.resCell18)/1000;
    dev["res19"]=LittleHexUInt(registroCelda.registro.resCell19)/1000;
    dev["res20"]=LittleHexUInt(registroCelda.registro.resCell20)/1000;
    dev["res21"]=LittleHexUInt(registroCelda.registro.resCell21)/1000;
    dev["res22"]=LittleHexUInt(registroCelda.registro.resCell22)/1000;
    dev["res23"]=LittleHexUInt(registroCelda.registro.resCell23)/1000;
    dev["res24"]=LittleHexUInt(registroCelda.registro.resCell24)/1000;
    
    

   // Serial.println(JSON.stringify(dev));
     return (dev);
 }

 void mostrarInformacionCeldas(TipoDispositivo tipo){
  // mensajePantalla("Celdas Voltaje", String(LittleHexUInt(registroInfoCeldaBMS[tipo].registro.battery_voltage)/1000), String(LittleHexLInt(registroInfoCeldaBMS[tipo].registro.balance_current)/1000));
  
  /*
  Serial.println();
  Serial.println("Informacion Celdas");
  Serial.println("-------------------------------");
  Serial.println();
  Serial.println("Voltajes");
  Serial.print("Celda1: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell1));
  Serial.print("Celda2: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell2));
  Serial.print("Celda3: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell3));
  Serial.print("Celda4: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell4));
  Serial.print("Celda5: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell5));
  Serial.print("Celda6: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell6));
  Serial.print("Celda7: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell7));
  Serial.print("Celda8: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell8));
  Serial.print("Celda9: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell9));
  Serial.print("Celda10: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell10));
  Serial.print("Celda11: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell11));
  Serial.print("Celda12: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell12));
  Serial.print("Celda13: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell13));
  Serial.print("Celda14: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell14));
  Serial.print("Celda15: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell15));
  Serial.print("Celda16: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell16));
  Serial.print("Celda17: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell17));
  Serial.print("Celda18: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell18));
  Serial.print("Celda19: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell19));
  Serial.print("Celda20: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell20));
  Serial.print("Celda21: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell21));
  Serial.print("Celda22: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell22));
  Serial.print("Celda23: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell23));
  Serial.print("Celda24: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.volCell24));
  Serial.print("Resi1: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.resCell1));
  Serial.print("Resi2: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.resCell2));
  Serial.print("Resi3: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.resCell3));
  Serial.print("Resi4: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.resCell4));
  Serial.println("----------------------------");
  Serial.println("");
  Serial.print("temp Cell 1: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.battery_t1));  
  Serial.print("temp Cell 2: ");
  Serial.println(LittleHexInt(registroInfoCeldaBMS[tipo].registro.battery_t2));
  */
  enviarDatosActualizados(tipo);
}
void enviarDatosActualizados(TipoDispositivo tipo){

     DynamicJsonDocument doc(4100);
    // Serial.print("memoria: ");
    // Serial.println(ESP.getMaxAllocHeap());     
     doc["bms1"]=pasarInfoCellJSON(registroInfoCeldaBMS[BMS1],BMS1,tipo);
     doc["bms2"]=pasarInfoCellJSON(registroInfoCeldaBMS[BMS2],BMS2,tipo); 
     

    String texto;
    serializeJson(doc, texto);
    ws.textAll(texto);




}

void cargarDatosCellBMS(byte cadena[], int largo, TipoDispositivo tipo){
  
       
   // Serial.println(largo);
    
    for (int i=0;i<largo;i++){
       
        registroInfoCeldaBMS[tipo].tablaCompleta[i]=cadena[i];
    }
  

}



void mensajePantalla(String titulo, String mensaje,String otro){

      Heltec.display->clear();

   Heltec.display->drawString(0, 0, titulo.c_str());

  Heltec.display->drawString(0, 14, mensaje.c_str());
 
  Heltec.display->drawString(0, 28, otro.c_str());
   
  Heltec.display->display();
 
}


void setup(){

  Serial.begin(115200);
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);


    Heltec.display->setFont(ArialMT_Plain_16);
 
    setup_SERVER();
    setup_BLE();
    tiempoInicioESP=(millis() / 1000);
  
}
void loop(){
  loop_SERVER();
  loop_BLE();
   if (((millis() / 1000)-tiempoInicioESP) > hastaInicioESP){
           ESP.restart();
             

        }

}
