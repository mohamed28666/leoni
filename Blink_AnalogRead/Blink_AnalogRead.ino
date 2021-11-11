#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
const int RESET = 52;
int Nombre_de_tour =0;
int longueur_bretta=2.5,hours=0,minutes=0;
float diametre_pignon = 0.5;
bool sending=0;
//***********************************************CONFIG*******************************************//
//---just select segment and matched line number ------------------------------------------------//
String linenumber="MH2/INR-L9";
const char server[] = "192.168.1.41";
unsigned long heureRAZmin=8.1e+7,heureRAZmax=heureRAZmin+10000 ;//en millisecondes
//--- specify ip address for the device---------------------------------------------------------//
IPAddress ip(192, 168, 1, 156); 
IPAddress ipdefault(0,0,0,0);
IPAddress current(1,1,1,1);

//***********************************************************************************************//
String reponse="";
String Start_Time ="00:00:00",timeSinceUpdate="00:00:00";
unsigned long elapsed=0,A_Duration=0,millis_timeSincelastUpdate=0;
unsigned long long int start=0;
int i,N_Tour=0, sensor = 18;
float mul_per_r=1;
byte mac[] = { 0xAE, 0xAA, 0xAE, 0xDF, 0xFE, 0x1D };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

//char server[] = "www.google.com";    // name address for Google (using DNS)
TaskHandle_t TASK_Incrimente_Handler,TASK_Test_Handler ,blinkhandler,changestatehandler;
SemaphoreHandle_t  SxBinarySemaphore,RQUBinarySemaphore;
byte customChar[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};
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
    digitalWrite(RESET, HIGH); 
 pinMode(RESET, OUTPUT);  
    digitalWrite(RESET, HIGH);   

   Serial.begin(115200);
  lcd.init();
  lcd.clear();         

   //lcd.noBacklight();
    lcd.begin(20, 4);
  lcd.setCursor(7,0);
    lcd.backlight();  
    lcd.print("LEONI");
      lcd.setCursor(3,1);
    lcd.print("IT DEPARTEMENT");
     lcd.setCursor(4,2);
     lcd.print("MENZEL HAYET");
 lcd.setCursor(0,3);
 lcd.print("SVR :"+(String)server);
delay(2000);


 SxBinarySemaphore = xSemaphoreCreateBinary();
  RQUBinarySemaphore= xSemaphoreCreateBinary();
  // Print a transitory message to the LCD.
 
  // initialize serial communication at 9600 bits per second:

lcd.clear();     
delay(1000);
lcd.setCursor(0,1);

lcd.print("Identifying ip...");

initiate_cnx : 
// Ethernet.maintain(); 
 Ethernet.begin(mac,ip);
 delay(2000);
 Serial.println(Ethernet.localIP());
 current =Ethernet.localIP();

 if(Ethernet.localIP()==ipdefault){
  goto initiate_cnx;
 }   
pinMode(LED_BUILTIN, OUTPUT);

  //Serial.println(Ethernet.localIP());
Serial.println((String)Ethernet.localIP()=="0.0.0.0");

 lcd.clear();  
  lcd.setCursor(0,2);
  lcd.print("IP:");
  lcd.setCursor(4,2);
lcd.print( Ethernet.localIP());
delay(4000);
  lcd.clear(); 
 Serial.println(Ethernet.localIP());
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
  
// xTaskCreate(
//  remiseazero
//    ,  "TASK_remiseazero"   // A name N_Tourust for humans
//    ,  255  // This stack size can be checked & adN_Tourusted by reading the Stack Highwater
//    ,  NULL
//    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//    ,  NULL);
//  


  
  xTaskCreate(
    TaskBlink
    ,  "Blink"   // A name just for humans
    ,  255  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    , 2// Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &blinkhandler );
//     xTaskCreate(
//  Starttime
//    ,  "Starttime"   // A name just for humans
//    ,  255  // This stack size can be checked & adjusted by reading the Stack Highwater
//    ,  NULL
//    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//    ,  NULL );
//
xTaskCreate(
    changestate
    ,  "Blink"   // A name just for humans
    ,  500  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &changestatehandler);
 
   xTaskCreate(
   LCD_CONTROLLER
    ,  "LCD_CONTROLLER"   // A name N_Tourust for humans
    ,  255  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TASK_Test_Handler );


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
 // client.connect(server, 3333);

if (client.connect(server, 3333)) {
 
    Serial.println("Request is being sent to host server (^_^)");
//Serial.println(elapsed);


   
     client.println("GET /arduino/"+linenumber+"/"+elapsed+"/"+Start_Time+"/"+state+"/"+(String)(N_Tour*mul_per_r)+" HTTP/1.1");
   // client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: 192.168.8.102");
    client.println("Connection: close");
    client.println();
 // while(client.available()==0){sending =1;NULL;NULL;};
   Serial.println(client.available());
while(client.available()==0){Serial.println("stucked here 1111");};

 // vTaskDelay(300 / portTICK_PERIOD_MS);
   
       while (client.available()) {
     
    char c = client.read();
    reponse = reponse+c;
   //Serial.print(c);
    
  }
  sending=0;
   timeSinceUpdate=reponse.substring(46,54);
    hours=timeSinceUpdate.substring(0,2).toInt();
    minutes=timeSinceUpdate.substring(3,5).toInt();
    millis_timeSincelastUpdate=((minutes*60000) +(hours*3.6*1000000));
   //Serial.println( millis_timeSincelastUpdate);
  //  Serial.println(  timeSinceUpdate);
  if(Start_Time=="00:00:00"){
  Start_Time=reponse.substring(46,54);
  }
  reponse="";
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection to server failed!!! (°_°)");
  //  Ethernet.begin(mac,ip);
    //Serial.println(Ethernet.localIP());
  
  }
    
    
   //vTaskDelay(100 / portTICK_PERIOD_MS);
   //lcd.setCursor(10,1);
  // lcd.print("-")  ;
  
  

  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    //Serial.println();
    Serial.println("Disconnecting from server.");
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
  
   //Serial.println(N_Tour);


    elapsed=millis()- start;
  //digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));  
   Serial.println("Magnetic DETECTED, ELAPSED TIME is "+(String)elapsed +", and NUMBER BRETTE OUT is "+(String)N_Tour);
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
  vTaskDelay(10000 / portTICK_PERIOD_MS);
 
 //Serial.println("only "+(String)(120000-limit)+"ms and the assembly line will be set to PAUSED State");  
 hours=timeSinceUpdate.substring(0,2).toInt();
    minutes=timeSinceUpdate.substring(3,5).toInt();
    millis_timeSincelastUpdate=((minutes*60000) +(hours*3.6*1000000));
   //Serial.println( "only "+ (String)(heureRAZmin -millis_timeSincelastUpdate-millis())+"s for starting shift 1/2");
 
  ////**************************** //
   if( (millis_timeSincelastUpdate+millis())>(heureRAZmin) and  (millis_timeSincelastUpdate+millis())<(heureRAZmax) ){///// to verify ///////
  
    N_Tour=0;
    Start_Time ="00:00:00";
    
    }
//*********************************************///
   Serial.println(  timeSinceUpdate);
if(limit>120000){

  vTaskSuspend(blinkhandler);

  int state=1;
  int clientstatus=client.connect(server,3333);
 // Serial.println("*******yyy***********");
 // Serial.println(clientstatus);
  if (clientstatus) {

    Serial.println("Request is being sent to host server (^_^)");
    client.println("GET /arduino/"+linenumber+"/"+0+"/"+Start_Time+"/"+state+"/"+(String)(N_Tour*mul_per_r)+" HTTP/1.1");
    client.println("Host: 192.168.8.102");
    client.println("Connection: close");
    client.println();

 while(client.available()==0){Serial.println("stucked here");};
    while (client.available()) { 
    char c = client.read();
   // reponse = reponse+c;
    //Serial.print(c);  
  }
  
  }
   else {
    // kf you didn't get a connection to the server:
    Serial.println("connection to server failed!!! (°_°)");
 // Ethernet.begin(mac,ip);

  //   vTaskDelay(3000 / portTICK_PERIOD_MS);
  //  Serial.println(Ethernet.localIP());
    //goto resumehere;
  
  }
    
  

  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server.");
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

// lcd.createChar(0, customChar);
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
   lcd.print("IP:")  ;
    lcd.setCursor(4,3);
   //lcd.print(A_TimeStamp);
 lcd.print( current);
   //  if (sending==1){
   //    lcd.setCursor(20,2);
  // lcd.write((byte)0);
  //    }
   }    
 
  
  }
//void remiseazero(void){
//  String hours,minutes;
//  for(;;){
//   // Serial.println(timeSinceUpdate);
//    hours=timeSinceUpdate.substring(0,2);
//    minutes=timeSinceUpdate.substring(3,5);
//     Serial.println(hours+'-'+minutes);
//    vTaskDelay(1000 / portTICK_PERIOD_MS);
//    }
//  
//  }
  
