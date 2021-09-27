#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

int Nombre_de_tour =0;
int longueur_bretta=2.5;
float diametre_pignon = 0.5;
String linenumber="VW-L1";
unsigned long elapsed=0,start=0,A_Duration=0,D_Duration=0,elapsedA=0,elapsedD=0;
int i,N_Tour=0, sensor = 18;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "192.168.8.102"; 
//char server[] = "www.google.com";    // name address for Google (using DNS)
TaskHandle_t TASK_Incrimente_Handler,TASK_Test_Handler ;
SemaphoreHandle_t  SxBinarySemaphore,RQUBinarySemaphore;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 175, 40, 5);

EthernetClient client;

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TASK_Incrimente( void *pvParameters );
LiquidCrystal_I2C lcd(0x27,20,4);

// the setup function runs once when you press reset or power the board
void setup() {
  SxBinarySemaphore = xSemaphoreCreateBinary();
  RQUBinarySemaphore= xSemaphoreCreateBinary();


  lcd.init();
  lcd.clear();         
  //lcd.backlight();  
   lcd.noBacklight();
  lcd.begin(20, 4);

  // Print a transitory message to the LCD.
 
  // initialize serial communication at 9600 bits per second:
   Serial.begin(115200);

pinMode(LED_BUILTIN, OUTPUT);

pinMode(sensor, INPUT);           // set pin to input
digitalWrite(sensor, HIGH);
attachInterrupt(digitalPinToInterrupt(sensor), ISRoutine, FALLING);
   
 

  // start the Ethernet connection:
 

  // if you get a connection, report back via serial:
  
  xTaskCreate(
   TASK_Incrimente
    ,  "TASK_Incrimente"   // A name N_Tourust for humans
    ,  255  // This stack size can be checked & adN_Tourusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TASK_Incrimente_Handler );
xTaskCreate(
   LCD_CONTROLLER
    ,  "LCD_CONTROLLER"   // A name N_Tourust for humans
    ,  255  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TASK_Test_Handler );

  
  xTaskCreate(
    TaskBlink
    ,  "Blink"   // A name just for humans
    ,  255  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );




   


}//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

 void ISRoutine()
{
  //Function called by the interrupt
  BaseType_t  xHigherPriorityTaskWoken  pdFALSE;
  xSemaphoreGiveFromISR(SxBinarySemaphore, &xHigherPriorityTaskWoken);
 

  // Print a transitory message to the LCD.
 
    
}




void loop()
{
    
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.


{
  (void) pvParameters;


// if (Ethernet.begin(mac) == 0) {
//    Serial.println("Failed to configure Ethernet using DHCP");
//    // no point in carrying on, so do nothing forevermore:
//    // try to congifure using IP address instead of DHCP:
//    Ethernet.begin(mac, ip);
//  }
//  // give the Ethernet shield a second to initialize:


Ethernet.begin(mac);
vTaskDelay(1000 / portTICK_PERIOD_MS);
 
  for (;;) // A Task shall never return or exit.
  {

xSemaphoreTake(RQUBinarySemaphore, portMAX_DELAY);
  Serial.println("connecting...");
if (client.connect(server, 3333)) {
    Serial.println("connected");
    // Make a HTTP request:
     client.println("GET /"+linenumber+"/"+elapsedA+" HTTP/1.1");
   // client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: 192.168.8.103");
    client.println("Connection: close");
    client.println();

    while(client.available()==0){};
  
       while (client.available()) {
     
    char c = client.read();
    Serial.print(c);
  }
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    Ethernet.begin(mac);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
    
    
   //vTaskDelay(100 / portTICK_PERIOD_MS);
   //lcd.setCursor(10,1);
  // lcd.print("-")  ;
  
  

  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    
  }



  
}
}




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void TASK_Incrimente(void *pvParameters){


  for(;;){
    //xSemaphoreTake(xSemaphore, -1);
    
    xSemaphoreTake(SxBinarySemaphore, portMAX_DELAY);


N_Tour++;

   Serial.println("interrupted");
   Serial.println(N_Tour);


    elapsed=millis()- start;
  //digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));  
    Serial.println((String)elapsed +" numéro"+(String)N_Tour);
     
    if(elapsed<(1000*3)){
  elapsedA=elapsed;
  elapsedD=0;
   A_Duration=A_Duration+elapsedA; 
  xSemaphoreGive( RQUBinarySemaphore);
  
}else{elapsedD=elapsed;
       elapsedA=0; 
          D_Duration=D_Duration+elapsedD; 
      
  }
  
   start= millis();
   
 

  
   }    
 
  
  }

  void LCD_CONTROLLER(void *pvParameters){
unsigned long times ;
int millisec , tseconds,tminutes,seconds,theure;
String DisplayTime;
char A_TimeStamp[100], D_TimeStamp[100];

  for(;;){

times = A_Duration;
  millisec  = times % 100;
  tseconds = times/1000;
  tminutes = tseconds / 60;
  seconds = tseconds % 60;
  theure=tminutes/60;
  sprintf(A_TimeStamp, "%02d:%02d:%02d",theure, tminutes, seconds);
 // DisplayTime = " "+ String(tminutes,DEC) + ":" + String(seconds,DEC) ;//+ ":" + String(millisec,DEC);



 vTaskDelay(1000 / portTICK_PERIOD_MS);   
 lcd.clear();
     lcd.setCursor(0,00);
    lcd.print("L_NUMBER: ");
    lcd.setCursor(10,0);
      lcd.print(linenumber);
      
     lcd.setCursor(0,01);
    lcd.print("ELAPSED: ");
    lcd.setCursor(10,01);
       
      lcd.print((String)elapsedA+"" );
      
    lcd.setCursor(0,2);
   lcd.print("N_BRETTE: ")  ;
    lcd.setCursor(10,2);
   lcd.print(N_Tour);
 lcd.setCursor(0,3);
   lcd.print("A_DURAT: ")  ;
    lcd.setCursor(10,3);
   lcd.print(A_TimeStamp);

vTaskDelay(1000 / portTICK_PERIOD_MS);

lcd.clear();
  lcd.setCursor(0,00);
    lcd.print("SERVER: ");
    lcd.setCursor(7,0);
      lcd.print(server);
      
     lcd.setCursor(0,01);
    lcd.print("D_Durat(s):");
    lcd.setCursor(10,01);
       
      lcd.print(D_Duration/1000 );
      
    lcd.setCursor(0,2);
   lcd.print("")  ;
    lcd.setCursor(10,2);
   lcd.print("");
 lcd.setCursor(0,3);
   lcd.print("")  ;
    lcd.setCursor(10,3);
   lcd.print("");
    
   }    
 
  
  }
 
