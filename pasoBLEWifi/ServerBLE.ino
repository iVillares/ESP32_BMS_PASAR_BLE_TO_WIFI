bool is_record_start(byte registro[], int largo){
    
  int largoSOR = sizeof(SOR);
  bool dev=false;

  if (largo >= largoSOR){
      dev=true;    
      for (int i=0 ; i<largoSOR;i++){

         if (registro[i]!=SOR[i]){
             dev=false;
             break;
         }
      }            
  }
  return dev;    
}
 bool is_record_correct_type(byte registro[], int largo,TipoDispositivo tipo){
       int largoSOR = sizeof(SOR);
        bool dev=false;
        if (largo >= largoSOR){
             
            if (registro[largoSOR] == tipoRegistroPeticion[tipo]){
                  dev=true;
            }
        }
        return dev;

}
 bool is_record_complete(byte registro[], int largo){
      bool dev=false;
      if (is_record_start(registro,largo)){
          if (largo == 300 || largo == 320){
              dev=true;            
          }
      }
       return dev;         
}
 

 

 void notifyCallbackCaracteristicaWriteBMS1(
    BLERemoteCharacteristic* pBLERemoteCharacteristic,
    uint8_t* pData,
    size_t length,
    bool isNotify) {
   
    for (int i=0; i<length;i++){
             
       datosRespuesta[BMS1][i+len_datosRespuesta[BMS1]]=pData[i];
       

    }
    
    len_datosRespuesta[BMS1]+=length;
   
     if (!is_record_start(datosRespuesta[BMS1],len_datosRespuesta[BMS1])){
            //Serial.println("Not valid start of record - wiping data {self.notificationData}");
            len_datosRespuesta[BMS1]=0;
               

     }else if (is_record_complete(datosRespuesta[BMS1], len_datosRespuesta[BMS1])){
            //Serial.println("record complete");
            registroCompletado(datosRespuesta[BMS1],len_datosRespuesta[BMS1],BMS1);
            len_datosRespuesta[BMS1]=0;
            
     }            

    
}
void notifyCallbackCaracteristicaWriteBMS2(
    BLERemoteCharacteristic* pBLERemoteCharacteristic,
    uint8_t* pData,
    size_t length,
    bool isNotify) {

   
    for (int i=0; i<length;i++){
             
       datosRespuesta[BMS2][i+len_datosRespuesta[BMS2]]=pData[i];
       

    }
    
    len_datosRespuesta[BMS2]+=length;
   
     if (!is_record_start(datosRespuesta[BMS2],len_datosRespuesta[BMS2])){
            //Serial.println("Not valid start of record - wiping data {self.notificationData}");
            len_datosRespuesta[BMS2]=0;
               
        
     }else if (is_record_complete(datosRespuesta[BMS2], len_datosRespuesta[BMS2])){
            //Serial.println("record complete");
            registroCompletado(datosRespuesta[BMS2],len_datosRespuesta[BMS2],BMS2);
            len_datosRespuesta[BMS2]=0;
            
     }            

    
}

 void registroCompletado(byte registro[], int largo,TipoDispositivo tipo){
  
      int len=largo;
      int largoSOR = sizeof(SOR);
      tipoRegistroPeticion[tipo]=(int)registro[largoSOR];
      switch (tipoRegistroPeticion[tipo]){
            case 3:   // si es para pedir informacion BMS
            {
                   if (largo > 216){
                        len=216;
            
                    }
                    borrarRegistroInformacion(tipo);          
                    for (int i=0;i<len;i++){
                        registroInformacionBMS[tipo].tablaCompleta[i]=registro[i];
                
                    }
                    mostrarInformacionBMS(tipo);                    
                    
                     
                      len_datosRespuesta[tipo]=0;                    
                      tipoRegistroPeticion[tipo]=2;
                     
                      poderPedir=true;                                    
                      
                    break;  
                                
            }
            case 2:     // si es para pedir informacion de las Celdas
              {
                   if (largo > 600){
                        len=600;
            
                    }
                  
                                        
                    borrarRegistroCelda(tipo);    
                        
                    for (int i=0;i<len;i++){
                        registroInfoCeldaBMS[tipo].tablaCompleta[i]=registro[i];
                       
                
                    }
                  
                    mostrarInformacionCeldas(tipo);
                    break;
            }
            default:
                  //Serial.println("Mensaje completo de tipo desconocido");            
                 break;
      }     
    


}

class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient) {
        isReconectarBLE=false;
        dispositivoReconectar=NINGUNO;
        //Serial.println("Esta Conectado");
        connected = true;      
    }

    void onDisconnect(BLEClient* pclient) {
        connected = false;
        //Serial.println("Esta Desconectado");
        myDevice=nullptr; 
                 len_datosRespuesta[0]=0;
         len_datosRespuesta[1]=0;

        if (isReconectarBLE){
           dispositivoServerBMS_actual=dispositivoReconectar;
           isReconectarBLE=false;
           dispositivoReconectar=NINGUNO;
           doScan=true;
        }

    }
};


void enableBLE_I(TipoDispositivo tipo){
  
  BLERemoteService* servicio;
  BLERemoteCharacteristic* caracteristica;  
  BLERemoteDescriptor* descriptor;  
  BLEUUID str;
  if (myDevice !=nullptr){
    servicio = pClient->getService(UUID_NOTIFY_SERVER);
    if (servicio == nullptr){
       
        return;       
    }
   
    byte dato[]={1,0};
    int  largo=sizeof(dato);

    caracteristica = servicio->getCharacteristic(UUID_NOTIFY_CHARACTERISTIC);
    if (caracteristica == nullptr){
       return;
    }
     
    if ( caracteristica != nullptr ){
        if (!caracteristica->canNotify()){
            
             //Serial.println("No se puede registrar para notificaciones");
             return;
        }else{
          switch (tipo){
              case BMS1:
                  caracteristica->registerForNotify( notifyCallbackCaracteristicaWriteBMS1);
                  break;
              case BMS2:
                  caracteristica->registerForNotify( notifyCallbackCaracteristicaWriteBMS2);
                  break;
          }
          
        }
    
        
       
        // descubrimiento de descriptores         
        auto a =caracteristica->getDescriptors();
        auto it = a->begin();
        
        while(it != a->end())
    {
    
        
               it++;
    }

                
         descriptor = caracteristica->getDescriptor(UUID_DESCRIPTOR);
        
        if (descriptor == nullptr){
            //Serial.println("No se puede coger el descriptor ");
            return;
        }
        
        descriptor->writeValue(dato,sizeof(dato));  
  
        
        auto caracteristicap= servicio->getCharacteristic(UUID_READ_CHARACTERISTIC); //UUID_WRITE_CHARACTERISTIC);//UUID_READ_CHARACTERISTIC);    
        if (caracteristicap==nullptr){
          //Serial.println("no existe caracteristica y pruebo con la write");
          caracteristicap= servicio->getCharacteristic(UUID_WRITE_CHARACTERISTIC);
        }
        caracteristicap->writeValue(dato,sizeof(dato));   
   
        tipoRegistroPeticion[tipo]=3;
        caracteristicap->writeValue(datosGetInfo,sizeof(datosGetInfo));         
        
        //Serial.println("habilitado");   
         int tiempoI   = millis()/1000;
         while ((millis()/1000)-tiempoI <2){}
   
        //Serial.println("Pedir informacion celdas");
        tipoRegistroPeticion[tipo]=2;
        caracteristicap->writeValue(datosCellInfo,sizeof(datosCellInfo));         
        tiempoI   = millis()/1000;
         while ((millis()/1000)-tiempoI <2){}
                      
            
        
    }        

  }
}
 
 bool conectarBLE(){
    pClient = BLEDevice::createClient();
    pClient->setClientCallbacks(new MyClientCallback());
    
    bool estaConectado=pClient->connect(myDevice);
    connected = true;
    doConnect=false;
    doScan=false;
    return estaConectado;
  
}

/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    /**
      * Called for each advertising BLE server.
      */
    void onResult(BLEAdvertisedDevice advertisedDevice) {
     
        if (dispositivoServerBMS_actual!=NINGUNO){
        BLEAddress direccionBMS=direccionServerBMS[dispositivoServerBMS_actual];
        // We have found a device, let us now see if it contains the service we are looking for.
        if (advertisedDevice.haveServiceUUID() && advertisedDevice.getAddress().equals(direccionBMS)) {

            BLEDevice::getScan()->stop();
            myDevice = new BLEAdvertisedDevice(advertisedDevice);
            doConnect = true;
            doScan = false;

        }

        } // Found our server
    } // onResult
}; // MyAdvertisedDeviceCallbacks

void setup_BLE() {
    
    //Serial.println("Starting Arduino BLE Client application...");
    BLEDevice::init("");
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setInterval(1349);
    pBLEScan->setWindow(449);
    pBLEScan->setActiveScan(true);

   

    

    
    
} // End of setup.
// This is the Arduino main loop function.
void desconectarDispositivoBLE(bool reconectar, TipoDispositivo aReconectar=NINGUNO){
         len_datosRespuesta[0]=0;
         len_datosRespuesta[1]=0;
         isReconectarBLE=reconectar;
         dispositivoReconectar=aReconectar;
         if (pClient!=nullptr){
              pClient->disconnect();
           }
           ESP.restart();
             

}
void conectarDispositivoBLE(TipoDispositivo dispositivo){
     if (pClient!=nullptr){
              desconectarDispositivoBLE(true,dispositivo);
     }else{
           dispositivoServerBMS_actual=dispositivo;
           isReconectarBLE=false;
           dispositivoReconectar=NINGUNO;
           doScan=true;
     }
}

void loop_BLE() {


    if (doConnect == true) {
        if (conectarBLE()) {
            tiempoInicioFuncionamientoBMS=(millis() / 1000);
        
           
           enableBLE_I(dispositivoServerBMS_actual);        
                   
        }
        else {
            //Serial.println("We have failed to connect to the server; there is nothin more we will do.");
        }
        doConnect = false;
    }

    if (connected) {
        
        if (((millis() / 1000)-tiempoInicioFuncionamientoBMS) > tiempoFinalFuncionamientoBMS){
           desconectarDispositivoBLE(false);
             

        }
    }
    else if (doScan) {
      doScan=false;
       
       
       BLEDevice::getScan()->start(15,false);  
       
    }

    
} // End of loop

  
