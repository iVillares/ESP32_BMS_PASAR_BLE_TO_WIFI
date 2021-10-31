
 String getUptime(byte time[3]){
   char * dev[12];

   double valor=0;
   double daysFloat=0;
   double hoursFloat=0;
   double minutesFloat=0;
   double secondsFloat=0;
   int days=0;
   int hours=0;
   int minutes=0;
   int seconds=0;
   String uptime;

   for (int x=0;x<3;x++){
     valor+=((int)time[x]) * pow(256,x);
   }
    daysFloat = valor / (60 * 60 * 24);
    days = trunc(daysFloat);
    hoursFloat = (daysFloat - days) * 24;
    hours = trunc(hoursFloat);
    minutesFloat = (hoursFloat - hours) * 60;
    minutes = trunc(minutesFloat);
    secondsFloat = (minutesFloat - minutes) * 60;
    seconds = round(secondsFloat);
    uptime = String(days)+"D"+hours+"H"+minutes+"M"+seconds+"S";
    return uptime;

 }
 
String Hex2Str(uint8_t datosHex[], int largo){
     
    String dev="";  
   for(int i = 0; i < largo; i++) {
     if(datosHex[i] < 0x10) {
        dev += '0';
      }

      dev += String(datosHex[i], HEX);
   }
 
    return dev;
}
 String Hex2StrB(byte datosHex[], int largo){
     
    String dev="";  
   for(int i = 0; i < largo; i++) {
     if(datosHex[i] < 0x10) {
       
        dev += '0';
      }

      dev += String(datosHex[i], HEX);
   }
 
    return dev;
}

 String Hex2AsciiStr(String hexString){
  
   String temp = "", sub = "", result;
  char buf[3];
  for(int i = 0; i < hexString.length(); i += 2){
    sub = hexString.substring(i, i+2);
    sub.toCharArray(buf, 3);
    char b = (char)strtol(buf, 0, 16);
    if(b == '\0'){
       
      break;

    }
    temp += b;
  }
  temp += '\0';
  return temp;
}
 String Hex2Ascii(byte cadena[], int largo){
   String temp = "";
  
  for(int i = 0; i < largo; i++){
    if (cadena[i] == 0x0){
      break;
    }
    temp += (char)cadena[i];
  }
  temp += (char)0;
  return temp;
}


 float LittleHex2Float(byte hex[]){
  NumeroHexFloat n;
  for (int i=0; i<4 ;i++){
    n.byte_array[i]=hex[i];
  }
  
  // Serial.println(n.var);
  //Serial.println(Hex2StrB(n.byte_array,4));
   float valor = round(n.var*1000)/1000.0;
  return valor;

}
float LittleHexInt(byte hex[]){
  NumeroHexInt n;
  for (int i=0; i<2 ;i++){
    n.byte_array[i]=hex[i];
  }
  
  // Serial.println(n.var);
  //Serial.println(Hex2StrB(n.byte_array,4));
   float valor = round(n.var*1000)/1000.0;
  return valor;

}
float LittleHexLInt(byte hex[]){
  NumeroHexInt n;
  for (int i=0; i<4 ;i++){
    n.byte_array[i]=hex[i];
  }
  
  // Serial.println(n.var);
  //Serial.println(Hex2StrB(n.byte_array,4));
  float valor = round(n.var*1000)/1000.0;
  return valor;

}
float Little1HexInt(byte hex[]){
  NumeroHexInt n;
  n.byte_array[0]=hex[0];
  n.byte_array[1]= 0; 
 
  // Serial.println(n.var);
  //Serial.println(Hex2StrB(n.byte_array,4));
   float valor = round(n.var*1000)/1000.0;
  return valor;

}
float LittleHexUInt(byte hex[]){
  NumeroHexUInt n;

  for (int i=0; i<2 ;i++){
    n.byte_array[i]=hex[i];
  }
    n.byte_array[3]=0;
    n.byte_array[2]=0;
  

   long valor = n.var;
 
   float dev= n.var * 1.0f;
   float valorx = round(dev*1000)/1000.0;
  return valorx;

}
float LittleHexLUInt(byte hex[]){
  NumeroHexUInt n;

  for (int i=0; i<3 ;i++){
    n.byte_array[i]=hex[i];
  }
 
  

   long valor = n.var;
 
   float dev= n.var * 1.0f;
   float valorx = round(dev*1000)/1000.0;
  return valorx;

}
 void borrarRegistroInformacion(TipoDispositivo tipo){
       for (int i=0;i<600;i++){
              registroInformacionBMS[tipo].tablaCompleta[i]=0;
                
        }
}
 void borrarRegistroCelda(TipoDispositivo tipo){
       for (int i=0;i<300;i++){
              registroInfoCeldaBMS[tipo].tablaCompleta[i]=0;
                
        }
}
