#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

int Nombre_de_tour =0;
int longueur_bretta=2.5;
float diametre_pignon = 0.5;
//***********************************************CONFIG*******************************************//
//---just select segment and matched line number ------------------------------------------------//
String linenumber="MH2/INR-L9";
char server[] = "192.168.8.102";
//--- specify ip address for the device---------------------------------------------------------//
IPAddress ip(192, 168, 8, 99); 
//***********************************************************************************************//
String reponse="";
String Start_Time ="00:00:00";
unsigned long elapsed=0,A_Duration=0;
unsigned long long int start=0;
int i,N_Tour=0, sensor = 18;
float mul_per_r=1;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

//char server[] = "www.google.com";    // name address for Google (using DNS)
TaskHandle_t TASK_Incrimente_Handler,TASK_Test_Handler ,blinkhandler,changestatehandler;
SemaphoreHandle_t  SxBinarySemaphore,RQUBinarySemaphore;

// Set the static IP address to use if the DHCP fails to assign


EthernetClient client;

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TASK_Incrimente( void *pvParameters );
void Starttime( void *pvParameters );
void changestate(void *pvParameters);
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
 Ethernet.begin(mac,ip);
 delay(1000);
pinMode(sensor, INPUT);  
    //Serial.println(Ethernet.localIP());// set pin to input
digitalWrite(sensor, HIGH);
attachInterrupt(digitalPinToInterrupt(sensor), ISRoutine, FALLING);
   
 

  // start the Ethernet connection:
 

  // if you get a connection, report back via serial:
  
  xTaskCreate(
   TASK_Incrimente
    ,  "TASK_Incrimente"   // A name N_Tourust for humans
    ,  255  // This stack size can be checked & adN_Tourusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
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
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &blinkhandler );
//     xTaskCreate(
//  Starttime
//    ,  "Starttime"   // A name just for humans
//    ,  255  // This stack size can be checked & adjusted by reading the Stack Highwater
//    ,  NULL
//    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//    ,  NULL );

xTaskCreate(
    changestate
    ,  "Blink"   // A name just for humans
    ,  500  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &changestatehandler);

   


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


//Ethernet.begin(mac);
//
//vTaskDelay(1000 / portTICK_PERIOD_MS);
 int state=2;
  for (;;) // A Task shall never return or exit.
 {

xSemaphoreTake(RQUBinarySemaphore, portMAX_DELAY);
 // Serial.println("connecting...");
  
if (client.connect(server, 3333)) {
  
    Serial.println("connected");
//Serial.println(elapsed);


   
     client.println("GET /arduino/"+linenumber+"/"+elapsed+"/"+Start_Time+"/"+state+"/"+(String)(N_Tour*mul_per_r)+" HTTP/1.1");
   // client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: 192.168.8.102");
    client.println("Connection: close");
    client.println();

    while(client.available()==0){};
  
       while (client.available()) {
     
    char c = client.read();
    reponse = reponse+c;
   //Serial.print(c);
    
  }
  if(Start_Time=="00:00:00"){
  Start_Time=reponse.substring(46,54);
  }
  reponse="";
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    Ethernet.begin(mac,ip);
     vTaskDelay(3000 / portTICK_PERIOD_MS);
    Serial.println(Ethernet.localIP());
  
  }
    
    
   //vTaskDelay(100 / portTICK_PERIOD_MS);
   //lcd.setCursor(10,1);
  // lcd.print("-")  ;
  
  

  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    //Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    
  }



  
}
}






void TASK_Incrimente(void *pvParameters){


  for(;;){
    //xSemaphoreTake(xSemaphore, -1);
    
    xSemaphoreTake(SxBinarySemaphore, portMAX_DELAY);


N_Tour++;

   Serial.println("interrupted");
   //Serial.println(N_Tour);


    elapsed=millis()- start;
  //digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));  
    Serial.println((String)elapsed +" numéro"+(String)N_Tour);
     A_Duration=A_Duration+elapsed;
  
   start= millis();
  xSemaphoreGive( RQUBinarySemaphore);
   }    
 
  
  }






  void changestate(void *pvParameters){

unsigned long  limit=0;
  for(;;){
  resumehere:
   // vTaskPrioritySet( changestatehandler,3 );
   limit= (millis()-start);
// Serial.println(limit);  

if(limit>120000){

  vTaskSuspend(blinkhandler);

  int state=1;
  int clientstatus=client.connect(server,3333);
 // Serial.println("*******yyy***********");
 // Serial.println(clientstatus);
  if (clientstatus) {
    Serial.println("connected");
    client.println("GET /arduino/"+linenumber+"/"+0+"/"+Start_Time+"/"+state+"/"+(String)(N_Tour*mul_per_r)+" HTTP/1.1");
    client.println("Host: 192.168.8.102");
    client.println("Connection: close");
    client.println();

    while(client.available()==0){};
    while (client.available()) { 
    char c = client.read();
   // reponse = reponse+c;
    Serial.print(c);  
  }
  
  }
   else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    Ethernet.begin(mac,ip);
     vTaskDelay(3000 / portTICK_PERIOD_MS);
    Serial.println(Ethernet.localIP());
    //goto resumehere;
  
  }
    
  

  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    
 };
 start=millis();
  }
 //  vTaskPrioritySet( changestatehandler,2 );
  vTaskResume(blinkhandler);
  
  


  
  }}

















  

  void LCD_CONTROLLER(void *pvParameters){
unsigned long times ;
int millisec , tseconds,tminutes,seconds,theure,Tminutes;
String DisplayTime;
char A_TimeStamp[100];
  for(;;){

times = A_Duration;
  millisec  = times % 1000;
  tseconds = times/1000;//
  tminutes = tseconds / 60;
  Tminutes=tminutes%60;
  seconds = tseconds % 60;
  theure=tminutes/60;
  sprintf(A_TimeStamp, "%02d:%02d:%02d",theure, Tminutes, seconds);
 // DisplayTime = " "+ String(tminutes,DEC) + ":" + String(seconds,DEC) ;//+ ":" + String(millisec,DEC);
  
 


     lcd.backlight();
     lcd.setCursor(0,00);
    lcd.print("L_NUMBER: ");
    lcd.setCursor(10,0);
      lcd.print(linenumber);
     
     lcd.setCursor(0,01);
    lcd.print("ST_Time: ");
    lcd.setCursor(10,01);
        lcd.print(Start_Time);
      //lcd.print((String)elapsed+"" );
      
    lcd.setCursor(0,2);
   lcd.print("N_BRETTE: ")  ;
    lcd.setCursor(10,2);
   lcd.print(N_Tour);
 lcd.setCursor(0,3);
   lcd.print("A_DURAT: ")  ;
    lcd.setCursor(10,3);
   lcd.print(A_TimeStamp);
     
   }    
 
  
  }

  
