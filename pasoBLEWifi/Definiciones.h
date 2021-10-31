enum TipoDispositivo{
     BMS1=0,
     BMS2=1,
     NINGUNO
};

byte SOR[] = { 0x55, 0xaa, 0xeb, 0x90 };

union NumeroHexFloat {
  //Converting a float to 4 bytes:
  byte byte_array[4];
  float var;
};
union NumeroHexInt {
  //Converting a float to 4 bytes:
  byte byte_array[2];
  int var;
};
union NumeroHexUInt {
  //Converting a float to 4 bytes:
  byte byte_array[4];
  unsigned long var;
};
struct EstructuraRegistroInfo {
  byte header[4];
  byte recordType;
  byte recordCount;
  byte deviceModel[10];      //String modelo
  byte hardwareVersion[10];  //String
  byte softwareVersion[10];  //String
  byte otro[10];
  byte deviceName[16];        //String
  byte devicePassCode[10];    // String
  byte manufacturaDate[14];   //
  byte serialNumber[14];      //
  byte userData[16];          //
  byte settingsPassCode[16];  //
  byte descar[84];
};

/*
struct EstructuraRegistroCeda{
        byte header[4];
        byte recordType;
        byte recordCount;
        byte  volCell1[4];
        byte  volCell2[4];
        byte  volCell3[4];
        byte  volCell4[4];
        byte  volCell5[4];
        byte  volCell6[4];
        byte  volCell7[4];
        byte  volCell8[4];
        byte  volCell9[4];
        byte  volCell10[4];
        byte  volCell11[4];
        byte  volCell12[4];
        byte  volCell13[4];
        byte  volCell14[4];
        byte  volCell15[4];
        byte  volCell16[4];
        byte  volCell17[4];
        byte  volCell18[4];
        byte  volCell19[4];
        byte  volCell20[4];
        byte  volCell21[4];
        byte  volCell22[4];
        byte  volCell23[4];
        byte  volCell24[4];
        byte  resCell1[4];
        byte  resCell2[4];
        byte  resCell3[4];
        byte  resCell4[4];
        byte  resCell5[4];
        byte  resCell6[4];
        byte  resCell7[4];
        byte  resCell8[4];
        byte  resCell9[4];
        byte  resCell10[4];
        byte  resCell11[4];
        byte  resCell12[4];
        byte  resCell13[4];
        byte  resCell14[4];
        byte  resCell15[4];
        byte  resCell16[4];
        byte  resCell17[4];
        byte  resCell18[4];
        byte  resCell19[4];
        byte  resCell20[4];
        byte  resCell21[4];
        byte  resCell22[4];
        byte  resCell23[4];
        byte  resCell24[4];
        byte  resCell25[4];
        byte  AverageCellVol[4];
        byte  DeltaCellVol[4];
        byte descard1[4];
        byte descard2[4];
        byte highestCell;
        byte bajoCell;
        byte flags[2];
        byte descard3[4];
        byte descard4[7];
        byte descard5[4];
        byte descard6[4];
        byte descard7[45];
        byte uptime[3];
        byte descard8[5];
        byte descard9[4];
        byte descard10[1];
        byte checksum;
};
*/

struct EstructuraRegistroCeda {
  byte header[4];
  byte recordType;
  byte recordCount;
  byte volCell1[2];
  byte volCell2[2];
  byte volCell3[2];
  byte volCell4[2];
  byte volCell5[2];
  byte volCell6[2];
  byte volCell7[2];
  byte volCell8[2];
  byte volCell9[2];
  byte volCell10[2];
  byte volCell11[2];
  byte volCell12[2];
  byte volCell13[2];
  byte volCell14[2];
  byte volCell15[2];
  byte volCell16[2];
  byte volCell17[2];
  byte volCell18[2];
  byte volCell19[2];
  byte volCell20[2];
  byte volCell21[2];
  byte volCell22[2];
  byte volCell23[2];
  byte volCell24[2];
  byte discard1[4];
  byte average_cell_vol[2];
  byte delta_cell_vol[2];
  byte current_balancer[2];
  byte resCell1[2];
  byte resCell2[2];
  byte resCell3[2];
  byte resCell4[2];
  byte resCell5[2];
  byte resCell6[2];
  byte resCell7[2];
  byte resCell8[2];
  byte resCell9[2];
  byte resCell10[2];
  byte resCell11[2];
  byte resCell12[2];
  byte resCell13[2];
  byte resCell14[2];
  byte resCell15[2];
  byte resCell16[2];
  byte resCell17[2];
  byte resCell18[2];
  byte resCell19[2];
  byte resCell20[2];
  byte resCell21[2];
  byte resCell22[2];
  byte resCell23[2];
  byte resCell24[2];
  byte discard2[6];
  byte battery_voltage[4];  //unsigne Long
  byte battery_power[4];    // unsignelong
  byte balance_current[4];  //long
  byte battery_t1[2];
  byte battery_t2[2];
  byte MOS_temp[2];

  byte discard4[4];
  byte discard4_1[1];
  byte percent_remain[1];
  byte capacity_remain[4];   //
  byte nominal_capacity[4];   // battery capacity
  byte cycle_count[4];
  byte cycle_capacity[4];
  
  byte descard12[2];
  byte descard13[2];
  byte uptime[3];

  byte descard15[2];
  byte descard16[2];
  byte descard17[2];
  byte descard6[12];
  byte descard18[2];
  byte descard19[2];
  byte descard20[2];
  byte current_change[2];
  byte current_discharge[2];
  byte descard23[2];
  byte descard24[2];
  byte descard25[2];
  byte descard26[2];
  byte descard27[2];
  byte descard28[2];
  byte descard29[2];
  byte descard30[93];
};
union RegistroCelda {



  byte tablaCompleta[300];
  EstructuraRegistroCeda registro;
};
union RegistroInfo {
  byte tablaCompleta[804];
  EstructuraRegistroInfo registro;
};

const char paginaHTML[] PROGMEM = R"rawliteral(
  
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {font-family: Arial; font-size: 12px;
background: #000000;
}

/* Style the tab */
.tab {
  overflow: hidden;
  border: 1px solid #ccc;
  background-color: #000000;
  
}

/* Style the buttons inside the tab */
.tab button {
  background-color: inherit;
  float: left;
  border: none;
  outline: none;
  cursor: pointer;
  padding: 14px 16px;
  transition: 0.3s;
  font-size: 17px;
    color: #ffffff;
}

/* Change background color of buttons on hover */
.tab button:hover {
  background-color: #000000;
  
 
}

/* Create an active/current tablink class */
.tab button.active {
  background-color: #ccc;
    color: #007000;
  
}

/* Style the tab content */
.tabcontent {
  display: none;
  padding: 6px 12px;
  border: 1px solid #ccc;
  border-top: none;
  color: #ffffff;
}

table{
	width:100%; 
	border-collapse:collapse;
}
td{
	border:2px solid black;
}
</style>
</head>
<body>



<div class="tab">
  <button class="tablinks" onclick="openBMS(event, 'BMS1')" id="defaultOpen">BMS1</button>
  <button class="tablinks" onclick="openBMS(event, 'BMS2')" id="defaultOpen2">BMS2</button>
  
</div>

<div id="BMS1" class="tabcontent">

<table>
        <td style="text-align:right">Estado: </td>
        <td style="text-align:left; color:#00f000"><span id="bms1_activo"></span></td>
        <td style="text-align:right">Time: </td>
        <td style="text-align:left; color:#00f0f0"><span id="bms1_time"></span></td
</table>

<table>

<!-- <caption style=" color:#00f0f0">Time: <span id="bms1_time"></span></caption> -->

    <tr>

        <td style="text-align:right">Change:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_change"></span></td>
        <td style="text-align:right">Discharge:</td>
        <td style="text-align:left; color:#00f000" ><span id="bms1_discharge"></span></td>
        <td style="text-align:right">Balance:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_balance"></span></td>
    </tr>
  
</table>
<table>
    <tr>
        
        <td style="text-align:center; color:#00f000;font-size:200%"><span id="bms1_total_vol"></span>&#32;V</td>
        
        <td style="text-align:center; color:#00f000;font-size:200%"><span id="bms1_total_amp"></span>&#32;A</td>

    </tr>
  
</table>
<table>
    <tr>
        <td style="text-align:right"></span> Battery Power:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_batterypower"></span>&#32;W</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Remain Battery:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_remainbattery"></span>%</td>
    </tr>
     <tr>
        <td style="text-align:right">Battery Capacity:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_batterycapacity"></span>&#32;AH</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Remain Capacity:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_remaincapacity"></span>&#32;AH</td>
    </tr>
      <tr>
        <td style="text-align:right">Cycle Capacity:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_cyclecapacity"></span></span>&#32;AH</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Cycle Count:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_cyclecount"></span></td>
    </tr>
      <tr>
        <td style="text-align:right">Ave. Cell Vol:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_avecellvol"></span></span>&#32;V</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Delta Cell Vol:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_deltacellvol"></span></span>&#32;V</td>
    </tr>
      <tr>
        <td style="text-align:right">Balance Cur:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_balancecur"></span></span>&#32;A</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >MOS temp:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_mostemp"></span></span>&ordm;C</td>
    </tr>
      <tr>
        <td style="text-align:right">Battery T1:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_batteryt1"></span>&ordm;C</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Battery T2:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_batteryt2"></span>&ordm;C</td>
    </tr>
</table>
</br>
<table>
    <caption style=" color:#00f0f0">Cells Voltage</caption>
    <tr>
        <td style="text-align:right">01:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol01"></span>&#32;V</td>
        <td style="text-align:right" >09:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol09"></span>&#32;V</td>     
        <td style="text-align:right" >17:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol17"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">02:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol02"></span>&#32;V</td>
        <td style="text-align:right" >10:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol10"></span>&#32;V</td>     
        <td style="text-align:right" >18:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol18"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">03:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol03"></span>&#32;V</td>
        <td style="text-align:right" >11:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol11"></span>&#32;V</td>     
        <td style="text-align:right" >19:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol19"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">04:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol04"></span>&#32;V</td>
        <td style="text-align:right" >12:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol12"></span>&#32;V</td>     
        <td style="text-align:right" >20:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol20"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">05:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol05"></span>&#32;V</td>
        <td style="text-align:right" >13:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol13"></span>&#32;V</td>     
        <td style="text-align:right" >21:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol21"></span>&#32;V</td>
    </tr>
    <tr>
        <td style="text-align:right">06:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol06"></span>&#32;V</td>
        <td style="text-align:right" >14:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol14"></span>&#32;V</td>     
        <td style="text-align:right" >22:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol22"></span>&#32;V</td>
    </tr>
    <tr>
        <td style="text-align:right">07:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol07"></span>&#32;V</td>
        <td style="text-align:right" >15:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol15"></span>&#32;V</td>     
        <td style="text-align:right" >23:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol23"></span>&#32;V</td>
    </tr>
    <tr>
        <td style="text-align:right">08:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol08"></span>&#32;V</td>
        <td style="text-align:right" >16:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol16"></span>&#32;V</td>     
        <td style="text-align:right" >24:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_vol24"></span>&#32;V</td>
    </tr>
    


</table>
</br>
<table>
    <caption style=" color:#00f0f0">Cells Wire Resistance</caption>
    <tr>
        <td style="text-align:right">01:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res01"></span></td>
        <td style="text-align:right" >09:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res09"></span></td>     
        <td style="text-align:right" >17:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res17"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">02:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res02"></span></td>
        <td style="text-align:right" >10:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res10"></span></td>     
        <td style="text-align:right" >18:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res18"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">03:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res03"></span></td>
        <td style="text-align:right" >11:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res11"></span></td>     
        <td style="text-align:right" >19:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res19"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">04:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res04"></span></td>
        <td style="text-align:right" >12:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res12"></span></td>     
        <td style="text-align:right" >20:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res20"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">05:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res05"></span></td>
        <td style="text-align:right" >13:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res13"></span></td>     
        <td style="text-align:right" >21:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res21"></span></td>
    </tr>
    <tr>
        <td style="text-align:right">06:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res06"></span></td>
        <td style="text-align:right" >14:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res14"></span></td>     
        <td style="text-align:right" >22:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res22"></span></td>
    </tr>
    <tr>
        <td style="text-align:right">07:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res07"></span></td>
        <td style="text-align:right" >15:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res15"></span></td>     
        <td style="text-align:right" >23:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res23"></span></td>
    </tr>
    <tr>
        <td style="text-align:right">08:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res08"></span></td>
        <td style="text-align:right" >16:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res16"></span></td>     
        <td style="text-align:right" >24:</td>
        <td style="text-align:left; color:#00f000"><span id="bms1_res24"></span></td>
    </tr>
    


</table>
</br>
</div>

<div id="BMS2" class="tabcontent">

<table>
        <td style="text-align:right">Estado: </td>
        <td style="text-align:left; color:#00f000"><span id="bms2_activo"></span></td>
        <td style="text-align:right">Time: </td>
        <td style="text-align:left; color:#00f0f0"><span id="bms2_time"></span></td
</table>

<table>
<!-- <caption style=" color:#00f0f0">Time: <span id="bms2_time"></span></caption> -->
    
    <tr>

        <td style="text-align:right">Change:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_change"></span></td>
        <td style="text-align:right">Discharge:</td>
        <td style="text-align:left; color:#00f000" ><span id="bms2_discharge"></span></td>
        <td style="text-align:right">Balance:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_balance"></span></td>
    </tr>
  
</table>
<table>
    <tr>
        
        <td style="text-align:center; color:#00f000;font-size:200%"><span id="bms2_total_vol"></span>&#32;V</td>
        
        <td style="text-align:center; color:#00f000;font-size:200%"><span id="bms2_total_amp"></span>&#32;A</td>

    </tr>
  
</table>
<table>
    <tr>
        <td style="text-align:right">Battery Power:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_batterypower"></span>&#32;W</td>
        <td style="text-align:right; width:10%"></td>      
        <td style="text-align:right" >Remain Battery:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_remainbattery"></span>%</td>
    </tr>
     <tr>
        <td style="text-align:right">Battery Capacity:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_batterycapacity"></span>&#32;AH</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Remain Capacity:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_remaincapacity"></span>&#32;AH</td>
    </tr>
      <tr>
        <td style="text-align:right">Cycle Capacity:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_cyclecapacity"></span>&#32;AH</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Cycle Count:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_cyclecount"></span></td>
    </tr>
      <tr>
        <td style="text-align:right">Ave. Cell Vol:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_avecellvol"></span>&#32;V</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Delta Cell Vol:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_deltacellvol"></span>&#32;V</td>
    </tr>
      <tr>
        <td style="text-align:right">Balance Cur:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_balancecur"></span>&#32;A</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >MOS temp:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_mostemp"></span>&deg;C</td>
    </tr>
      <tr>
        <td style="text-align:right">Battery T1:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_batteryt1"></span>&deg;C</td>
        <td style="text-align:right; width:0%"></td>      
        <td style="text-align:right" >Battery T2:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_batteryt2"></span>&deg;C</td>
    </tr>
</table>
</br>
<table>
    <caption style=" color:#00f0f0">Cells Voltage</caption>
    <tr>
        <td style="text-align:right">01:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol01"></span>&#32;V</td>
        <td style="text-align:right" >09:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol09"></span>&#32;V</td>     
        <td style="text-align:right" >17:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol17"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">02:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol02"></span>&#32;V</td>
        <td style="text-align:right" >10:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol10"></span>&#32;V</td>     
        <td style="text-align:right" >18:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol18"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">03:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol03"></span>&#32;V</td>
        <td style="text-align:right" >11:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol11"></span>&#32;V</td>     
        <td style="text-align:right" >19:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol19"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">04:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol04"></span>&#32;V</td>
        <td style="text-align:right" >12:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol12"></span>&#32;V</td>     
        <td style="text-align:right" >20:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol20"></span>&#32;V</td>
    </tr>
        <tr>
        <td style="text-align:right">05:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol05"></span>&#32;V</td>
        <td style="text-align:right" >13:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol13"></span>&#32;V</td>     
        <td style="text-align:right" >21:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol21"></span>&#32;V</td>
    </tr>
    <tr>
        <td style="text-align:right">06:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol06"></span>&#32;V</td>
        <td style="text-align:right" >14:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol14"></span>&#32;V</td>     
        <td style="text-align:right" >22:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol22"></span>&#32;V</td>
    </tr>
    <tr>
        <td style="text-align:right">07:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol07"></span>&#32;V</td>
        <td style="text-align:right" >15:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol15"></span>&#32;V</td>     
        <td style="text-align:right" >23:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol23"></span>&#32;V</td>
    </tr>
    <tr>
        <td style="text-align:right">08:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol08"></span>&#32;V</td>
        <td style="text-align:right" >16:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol16"></span>&#32;V</td>     
        <td style="text-align:right" >24:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_vol24"></span>&#32;V</td>
    </tr>
    


</table>
</br>
<table>
    <caption style=" color:#00f0f0">Cells Wire Resistance</caption>
    <tr>
        <td style="text-align:right">01:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res01"></span></td>
        <td style="text-align:right" >09:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res09"></span></td>     
        <td style="text-align:right" >17:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res17"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">02:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res02"></span></td>
        <td style="text-align:right" >10:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res10"></span></td>     
        <td style="text-align:right" >18:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res18"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">03:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res03"></span></td>
        <td style="text-align:right" >11:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res11"></span></td>     
        <td style="text-align:right" >19:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res19"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">04:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res04"></span></td>
        <td style="text-align:right" >12:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res12"></span></td>     
        <td style="text-align:right" >20:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res20"></span></td>
    </tr>
        <tr>
        <td style="text-align:right">05:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res05"></span></td>
        <td style="text-align:right" >13:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res13"></span></td>     
        <td style="text-align:right" >21:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res21"></span></td>
    </tr>
    <tr>
        <td style="text-align:right">06:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res06"></span></td>
        <td style="text-align:right" >14:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res14"></span></td>     
        <td style="text-align:right" >22:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res22"></span></td>
    </tr>
    <tr>
        <td style="text-align:right">07:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res07"></span></td>
        <td style="text-align:right" >15:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res15"></span></td>     
        <td style="text-align:right" >23:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res23"></span></td>
    </tr>
    <tr>
        <td style="text-align:right">08:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res08"></span></td>
        <td style="text-align:right" >16:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res16"></span></td>     
        <td style="text-align:right" >24:</td>
        <td style="text-align:left; color:#00f000"><span id="bms2_res24"></span></td>
    </tr>
    


</table>
</br>


</div>



<script>

// Get the element with id="defaultOpen" and click on it


//***********************************************
 var gateway = `ws://${window.location.hostname}/wsbms`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(e) {
      // aqui va todo el codigo de actualizacion de la pagina web
      console.log("ws", e.data);
  var obj = JSON.parse(e.data);
  try{
  document.getElementById("bms1_time").innerHTML = obj.bms1.timex;
   
   if (obj.bms1.dispositivoactivo){
       document.getElementById("bms1_activo").innerHTML="<p style=\"color:#00f000;\">Conectado</p>";
      
   }else{
      document.getElementById("bms1_activo").innerHTML="<p style=\"color:red;\">Desconectado</p>";
   }
  document.getElementById("bms1_change").innerHTML = obj.bms1.change;
  document.getElementById("bms1_discharge").innerHTML = obj.bms1.discharge;
  document.getElementById("bms1_balance").innerHTML = obj.bms1.balance;
  document.getElementById("bms1_total_vol").innerHTML = round2(obj.bms1.total_vol);
  document.getElementById("bms1_total_amp").innerHTML = round2(obj.bms1.total_amp);
  document.getElementById("bms1_batterypower").innerHTML = round1(obj.bms1.batterypower);
  document.getElementById("bms1_remainbattery").innerHTML = round(obj.bms1.remainbattery);
  document.getElementById("bms1_batterycapacity").innerHTML = round1(obj.bms1.batterycapacity);
  document.getElementById("bms1_remaincapacity").innerHTML = round1(obj.bms1.capacityremain);
  
  document.getElementById("bms1_cyclecapacity").innerHTML = round1(obj.bms1.cyclecapacity);
  document.getElementById("bms1_cyclecount").innerHTML = round(obj.bms1.cyclecount);
  document.getElementById("bms1_avecellvol").innerHTML = round(obj.bms1.avecellvol);
  document.getElementById("bms1_deltacellvol").innerHTML = round(obj.bms1.deltacellvol);
  document.getElementById("bms1_balancecur").innerHTML = round(obj.bms1.balancecur);
  document.getElementById("bms1_mostemp").innerHTML = round(obj.bms1.mostemp);
  document.getElementById("bms1_batteryt1").innerHTML = round(obj.bms1.batteryt1);
  document.getElementById("bms1_batteryt2").innerHTML = round(obj.bms1.batteryt2);
  document.getElementById("bms1_vol01").innerHTML = round(obj.bms1.vol01);
  document.getElementById("bms1_vol02").innerHTML = round(obj.bms1.vol02);
  document.getElementById("bms1_vol03").innerHTML = round(obj.bms1.vol03);
  document.getElementById("bms1_vol04").innerHTML = round(obj.bms1.vol04);
  document.getElementById("bms1_vol05").innerHTML = round(obj.bms1.vol05);
  document.getElementById("bms1_vol06").innerHTML = round(obj.bms1.vol06);
  document.getElementById("bms1_vol07").innerHTML = round(obj.bms1.vol07);
  document.getElementById("bms1_vol08").innerHTML = round(obj.bms1.vol08);
  document.getElementById("bms1_vol09").innerHTML = round(obj.bms1.vol09);
  document.getElementById("bms1_vol10").innerHTML = round(obj.bms1.vol10);
  document.getElementById("bms1_vol11").innerHTML = round(obj.bms1.vol11);
  document.getElementById("bms1_vol12").innerHTML = round(obj.bms1.vol12);
  document.getElementById("bms1_vol13").innerHTML = round(obj.bms1.vol13);
  document.getElementById("bms1_vol14").innerHTML = round(obj.bms1.vol14);
  document.getElementById("bms1_vol15").innerHTML = round(obj.bms1.vol15);
  document.getElementById("bms1_vol16").innerHTML = round(obj.bms1.vol16);
  document.getElementById("bms1_vol17").innerHTML = round(obj.bms1.vol17);
  document.getElementById("bms1_vol18").innerHTML = round(obj.bms1.vol18);
  document.getElementById("bms1_vol19").innerHTML = round(obj.bms1.vol19);
  document.getElementById("bms1_vol20").innerHTML = round(obj.bms1.vol20);
  document.getElementById("bms1_vol21").innerHTML = round(obj.bms1.vol21);
  document.getElementById("bms1_vol22").innerHTML = round(obj.bms1.vol22);
  document.getElementById("bms1_vol23").innerHTML = round(obj.bms1.vol23);
  document.getElementById("bms1_vol24").innerHTML = round(obj.bms1.vol24);
  document.getElementById("bms1_res01").innerHTML = round(obj.bms1.res01);
  document.getElementById("bms1_res02").innerHTML = round(obj.bms1.res02);
  document.getElementById("bms1_res03").innerHTML = round(obj.bms1.res03);
  document.getElementById("bms1_res04").innerHTML = round(obj.bms1.res04);
  document.getElementById("bms1_res05").innerHTML = round(obj.bms1.res05);
  document.getElementById("bms1_res06").innerHTML = round(obj.bms1.res06);
  document.getElementById("bms1_res07").innerHTML = round(obj.bms1.res07);
  document.getElementById("bms1_res08").innerHTML = round(obj.bms1.res08);
  document.getElementById("bms1_res09").innerHTML = round(obj.bms1.res09);
  document.getElementById("bms1_res10").innerHTML = round(obj.bms1.res10);
  document.getElementById("bms1_res11").innerHTML = round(obj.bms1.res11);
  document.getElementById("bms1_res12").innerHTML = round(obj.bms1.res12);
  document.getElementById("bms1_res13").innerHTML = round(obj.bms1.res13);
  document.getElementById("bms1_res14").innerHTML = round(obj.bms1.res14);
  document.getElementById("bms1_res15").innerHTML = round(obj.bms1.res15);
  document.getElementById("bms1_res16").innerHTML = round(obj.bms1.res16);
  document.getElementById("bms1_res17").innerHTML = round(obj.bms1.res17);
  document.getElementById("bms1_res18").innerHTML = round(obj.bms1.res18);
  document.getElementById("bms1_res19").innerHTML = round(obj.bms1.res19);
  document.getElementById("bms1_res20").innerHTML = round(obj.bms1.res20);
  document.getElementById("bms1_res21").innerHTML = round(obj.bms1.res21);
  document.getElementById("bms1_res22").innerHTML = round(obj.bms1.res22);
  document.getElementById("bms1_res23").innerHTML = round(obj.bms1.res23);
  document.getElementById("bms1_res24").innerHTML = round(obj.bms1.res24);
  }catch( error) {
    console.error(error);
  // expected output: ReferenceError: nonExistentFunction is not defined
  // Note - error messages will vary depending on browser
}

  //
  try{
   document.getElementById("bms2_time").innerHTML = obj.bms2.timex;
  
   if (obj.bms2.dispositivoactivo){
       document.getElementById("bms2_activo").innerHTML="<p style=\"color:#00f000;\">Conectado</p>";
      
   }else{
      document.getElementById("bms2_activo").innerHTML="<p style=\"color:red;\">Desconectado</p>";
   }
   
  document.getElementById("bms2_change").innerHTML = obj.bms2.change;
  document.getElementById("bms2_discharge").innerHTML = obj.bms2.discharge;
  document.getElementById("bms2_balance").innerHTML = obj.bms2.balance;
  document.getElementById("bms2_total_vol").innerHTML = round2(obj.bms2.total_vol);
  document.getElementById("bms2_total_amp").innerHTML = round2(obj.bms2.total_amp);
  document.getElementById("bms2_batterypower").innerHTML = round1(obj.bms2.batterypower);
  document.getElementById("bms2_remainbattery").innerHTML = round1(obj.bms2.remainbattery);
  document.getElementById("bms2_batterycapacity").innerHTML = round1(obj.bms2.batterycapacity);
  document.getElementById("bms2_remaincapacity").innerHTML = round1(obj.bms2.capacityremain);
  document.getElementById("bms2_cyclecapacity").innerHTML = round1(obj.bms2.cyclecapacity);
  document.getElementById("bms2_cyclecount").innerHTML = round(obj.bms2.cyclecount);
  document.getElementById("bms2_avecellvol").innerHTML = round(obj.bms2.avecellvol);
  document.getElementById("bms2_deltacellvol").innerHTML = round(obj.bms2.deltacellvol);
  document.getElementById("bms2_balancecur").innerHTML = round(obj.bms2.balancecur);
  document.getElementById("bms2_mostemp").innerHTML = round(obj.bms2.mostemp);
  document.getElementById("bms2_batteryt1").innerHTML = round(obj.bms2.batteryt1);
  document.getElementById("bms2_batteryt2").innerHTML = round(obj.bms2.batteryt2);
  document.getElementById("bms2_vol01").innerHTML = round(obj.bms2.vol01);
  document.getElementById("bms2_vol02").innerHTML = round(obj.bms2.vol02);
  document.getElementById("bms2_vol03").innerHTML = round(obj.bms2.vol03);
  document.getElementById("bms2_vol04").innerHTML = round(obj.bms2.vol04);
  document.getElementById("bms2_vol05").innerHTML = round(obj.bms2.vol05);
  document.getElementById("bms2_vol06").innerHTML = round(obj.bms2.vol06);
  document.getElementById("bms2_vol07").innerHTML = round(obj.bms2.vol07);
  document.getElementById("bms2_vol08").innerHTML = round(obj.bms2.vol08);
  document.getElementById("bms2_vol09").innerHTML = round(obj.bms2.vol09);
  document.getElementById("bms2_vol10").innerHTML = round(obj.bms2.vol10);
  document.getElementById("bms2_vol11").innerHTML = round(obj.bms2.vol11);
  document.getElementById("bms2_vol12").innerHTML = round(obj.bms2.vol12);
  document.getElementById("bms2_vol13").innerHTML = round(obj.bms2.vol13);
  document.getElementById("bms2_vol14").innerHTML = round(obj.bms2.vol14);
  document.getElementById("bms2_vol15").innerHTML = round(obj.bms2.vol15);
  document.getElementById("bms2_vol16").innerHTML = round(obj.bms2.vol16);
  document.getElementById("bms2_vol17").innerHTML = round(obj.bms2.vol17);
  document.getElementById("bms2_vol18").innerHTML = round(obj.bms2.vol18);
  document.getElementById("bms2_vol19").innerHTML = round(obj.bms2.vol19);
  document.getElementById("bms2_vol20").innerHTML = round(obj.bms2.vol20);
  document.getElementById("bms2_vol21").innerHTML = round(obj.bms2.vol21);
  document.getElementById("bms2_vol22").innerHTML = round(obj.bms2.vol22);
  document.getElementById("bms2_vol23").innerHTML = round(obj.bms2.vol23);
  document.getElementById("bms2_vol24").innerHTML = round(obj.bms2.vol24);
  document.getElementById("bms2_res01").innerHTML = round(obj.bms2.res01);
  document.getElementById("bms2_res02").innerHTML = round(obj.bms2.res02);
  document.getElementById("bms2_res03").innerHTML = round(obj.bms2.res03);
  document.getElementById("bms2_res04").innerHTML = round(obj.bms2.res04);
  document.getElementById("bms2_res05").innerHTML = round(obj.bms2.res05);
  document.getElementById("bms2_res06").innerHTML = round(obj.bms2.res06);
  document.getElementById("bms2_res07").innerHTML = round(obj.bms2.res07);
  document.getElementById("bms2_res08").innerHTML = round(obj.bms2.res08);
  document.getElementById("bms2_res09").innerHTML = round(obj.bms2.res09);
  document.getElementById("bms2_res10").innerHTML = round(obj.bms2.res10);
  document.getElementById("bms2_res11").innerHTML = round(obj.bms2.res11);
  document.getElementById("bms2_res12").innerHTML = round(obj.bms2.res12);
  document.getElementById("bms2_res13").innerHTML = round(obj.bms2.res13);
  document.getElementById("bms2_res14").innerHTML = round(obj.bms2.res14);
  document.getElementById("bms2_res15").innerHTML = round(obj.bms2.res15);
  document.getElementById("bms2_res16").innerHTML = round(obj.bms2.res16);
  document.getElementById("bms2_res17").innerHTML = round(obj.bms2.res17);
  document.getElementById("bms2_res18").innerHTML = round(obj.bms2.res18);
  document.getElementById("bms2_res19").innerHTML = round(obj.bms2.res19);
  document.getElementById("bms2_res20").innerHTML = round(obj.bms2.res20);
  document.getElementById("bms2_res21").innerHTML = round(obj.bms2.res21);
  document.getElementById("bms2_res22").innerHTML = round(obj.bms2.res22);
  document.getElementById("bms2_res23").innerHTML = round(obj.bms2.res23);
  document.getElementById("bms2_res24").innerHTML = round(obj.bms2.res24);
   }catch( error) {
    console.error(error);
  // expected output: ReferenceError: nonExistentFunction is not defined
  // Note - error messages will vary depending on browser
}
  }
  function onLoad(event) {
    initWebSocket();
    document.getElementById("defaultOpen").click();
    setTimeout(pasarEvento, 2000);
    
  }
//***********************************************

function round(num) {
    var m = Number((Math.abs(num) * 1000).toPrecision(15));
    return Math.round(m) / 1000 * Math.sign(num);
}
function round1(num) {
    var m = Number((Math.abs(num) * 10).toPrecision(15));
    return Math.round(m) / 10 * Math.sign(num);
}
function round2(num) {
    var m = Number((Math.abs(num) * 100).toPrecision(15));
    return Math.round(m) / 100 * Math.sign(num);
}
function pasarEvento(){
  
  websocket.send("BMS1");
}
function openBMS(evt, nombreBMS) {
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablinks");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" active", "");
  }
  console.log("ws", nombreBMS);
  try{
  websocket.send(nombreBMS);
  }catch(error){

  }
  document.getElementById(nombreBMS).style.display = "block";
  evt.currentTarget.className += " active";
}

</script>
   
</body>
</html> 

)rawliteral";
