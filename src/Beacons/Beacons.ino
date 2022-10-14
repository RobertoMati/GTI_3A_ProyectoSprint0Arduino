

#include <bluefruit.h>

// ----------------------------------------------------
// setup()
// ----------------------------------------------------

/**
 * @file Beacons.ino
 * @pre  Antes de realizar alguna acción, lee el archivo README que se encuentra en la carpeta del proyecto.
 * @author Roberto Matilla Augustinus (robertomatillaaugustinus@gmail.com)
 * @brief  Este programa permite enviar beacons con la Sparkfun nRF52840 Mini.
 * @version 0.1
 * @date 13-10-2022
 * @copyright Copyright (c) 2022
 */
void setup() {
   /*
   @brief  Esta función (setup) se encarga de poder inicializar el dispositivo y el envío de beacons.
  */
   //-------------------------------------------------------------
   Serial.begin(115200);
   //Mientras no se abra el Serial no se ejecuta el programa. Se puede eliminar esta línea.
   while ( !Serial ) delay(10);
   Serial.println("-----------------------------------------------\n");
   Serial.println(" Iniciamos la operación de envío de iBeacons  ");
   Serial.println("-----------------------------------------------\n");
   //-------------------------------------------------------------



   //-------------------------------------------------------------
   //Inicializamos el módule Bluefruit nRF52
   Serial.println("Iniciamos el módule Bluefruit nRF52");
   Bluefruit.begin();
   //-------------------------------------------------------------



   //-------------------------------------------------------------
   // Elegimos el nombre del dispositivo
   Serial.println("Nombro al dispositivo como GTI-3ARoberto" );
   Bluefruit.setName("GTI-3ARoberto");
   Bluefruit.ScanResponse.addName();
   //-------------------------------------------------------------
   
   
   
   //-------------------------------------------------------------
   // Llamamos a la función que envía el iBeacon
   ComienzoEnvioBeacons();
   Serial.println("\nAdvertising");
   //-------------------------------------------------------------
}
// ----------------------------------------------------
// Fin setup()
// ----------------------------------------------------
 

// -----------------------------------------------------------------------------------------


// ----------------------------------------------------
// Función ComienzoEnvioBeacons() 
// ----------------------------------------------------

/*
* @brief Esta función (ComienzoEnvioBeacons) se encarga de poder enviar el iBeacon.
  La función tiene el siguiente formato:
   - Se crea un objeto de tipo BLEBeacon.
   - Se configura el UUID del iBeacon.
   - Se configura el Major y el Minor.
   - Se configura el RSSI.
   - Se configura el intervalo de envío.
   - Se inicia el envío del iBeacon.

* La función tiene el siguiente diseño: ComienzoEnvioBeacons ----->
*/
void ComienzoEnvioBeacons() {

   //-------------------------------------------------------------
   Serial.println( " ComienzoEnvioBeacons() " );
   Serial.println( " Bluefruit.Advertising.stop(); ");
   //Detenemos la publicidad. Se inicia al final de la función
   Bluefruit.Advertising.stop();
   //-------------------------------------------------------------



   //-------------------------------------------------------------
   // Paquete de publicidad
   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
   Bluefruit.Advertising.addTxPower();
   //-------------------------------------------------------------
   


   //-------------------------------------------------------------
   // Incluimos el nombre del dispositivo
   Serial.println( " Bluefruit.Advertising.addName(); " );
   Bluefruit.Advertising.addName();
   //-------------------------------------------------------------



   //-------------------------------------------------------------
   Serial.println( " Bluefruit.Advertising.setBeacon( elBeacon ); ");

   //-------------------------------------------------------------
   //Creamos el identificador del iBeacon
   uint8_t beaconUUID[16] = {'E', 'P', 'S', 'G', '-', 'R', 'O', 'B','E', 'R', 'T', 'O', '-', 'P', 'R', 'O' };
    /* Creamos el iBeacon. Este consta de 4 partes: 
       1. Identificador del iBeacon
       2. Major
       3. Minor
       4. Potencia de transmisión (TxPower)
   */
   BLEBeacon elBeacon( beaconUUID, 12, 33, 73 );
   elBeacon.setManufacturer( 0x004c ); // Apple ID
   // Se añade el iBeacon al paquete de publicidad
   Bluefruit.Advertising.setBeacon( elBeacon );
   //-------------------------------------------------------------
   


   //-------------------------------------------------------------
   //Iniciamos la publicidad
   Bluefruit.Advertising.restartOnDisconnect(true);
   Bluefruit.Advertising.setInterval(32, 244);    // En unidad de 0.625 ms
   Bluefruit.Advertising.setFastTimeout(30);      // Número de segundos en modo rápido
   Bluefruit.Advertising.start(0);                // 0 = No parar de transmitir después de un número de segundos
   Serial.println( " Bluefruit.Advertising.start(0);" );
   //-------------------------------------------------------------
}
// ----------------------------------------------------
// Fin Función ComienzoEnvioBeacons()
// ----------------------------------------------------
 


// ----------------------------------------------------
// Proceso loop()
// ----------------------------------------------------

/*
* @brief  Esta función (loop) se inicia un contador.
*/namespace Loop {
    //Iniciamos el contador a 0
   int cont = 0;
};

/*
* @brief  Esta función (loop) se encarga contar las veces que se ha producido la transmisión del iBeacon.
*/
void loop() {
   
   //-------------------------------------------------------------
   using namespace Loop;
   //-------------------------------------------------------------

   //-------------------------------------------------------------
   // Vamos aumentando el contador
   cont++;
   //Añadimos un retardo de 1 segundo
   delay(1000);
   Serial.print( " ** loop cont=" );
   Serial.println( cont );
   //-------------------------------------------------------------
} 
// ----------------------------------------------------
// Fin Proceso loop()
// ----------------------------------------------------