// function to try:
//
//thinking of splitting each action or lighting effect up into separate loops

#include <FastLED.h>      //neopixel library
#define NUM_LEDS 12       //number of leds
#define DATA_PIN 16       //pin of led data pin 16 for compact board 2 for nano
const int buttonPin = 26;        //input pin pin 26 for compact board 3 for nano
#define BUTTON_PIN_BITMASK 0x4000000 // 2^26 in hex
//#define FASTLED_SHOW_CORE 0  // -- The core to run FastLED.show()
CRGB leds[NUM_LEDS];
bool button = 0;                 //input pin status
int buzzer = 4;                  //the pin of the active buzzer
#define NOTE_C4  262             //buzzer musical note
int brightness = 0;              //minimum brightness?
int fadeAmount = 0;
int count = 0;                   //for revive function(fastled)
unsigned long currenttime;       //system clock
unsigned long testtime;          //time grabbed for bleedout
unsigned int bleedout = 0;       //time result from (currenttime - testtime)
unsigned int bleedTime = 12000;  //define length of bleedout millis
int reviveTime = 1000;           //define length to revive millis
int reviveDelay = 0;              //actual delay between counting leds
int Delay = 0;                    //mapped value for delay for pulse effect
int b = 0;                        //button press conter for length of press
int revives = 0;


void setup() {

FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
leds[NUM_LEDS] = CRGB::Black;                //all lights off
FastLED.show();                         //all lights off
pinMode (buttonPin, INPUT_PULLUP);
pinMode (buzzer,OUTPUT);
Serial.begin(9600);
esp_sleep_enable_ext0_wakeup(GPIO_NUM_26,0); //1 = High, 0 = Low
//esp_deep_sleep_start(); endless loop

}
void softReset(){            
//asm volatile ("  jmp 0");     //comment out for esp boards
ESP.restart();  // comment out for regular arduino boards
}                             


//------------Bleedout Pulse------------
void bleedoutPulse(){
 
bleedout = currenttime - testtime;
int Delay = map(bleedout, 0, bleedTime, 35, 0);  //pulse increase over time 1 minute
int fadeAmount = map(bleedout, 0, bleedTime, 4, 12);//4, 12

EVERY_N_MILLISECONDS( Delay ) {  //substitutes delay, causing no lag in code
       for(int i = 0; i < NUM_LEDS; i++ ){
       leds[i] = CRGB::Red;  
       leds[i].fadeLightBy(brightness);}
       brightness = brightness + fadeAmount;
       
      // reverse the direction of the fading at the ends of the fade:
      if(brightness == 0 || brightness == 255)
      {
        fadeAmount = -fadeAmount ;
        
      } }}
//------------Bleedout Pulsing------------
      
//------------Revive------------      
void revive(){
reviveDelay = reviveTime/NUM_LEDS;    //division of time between count

      if (button == LOW && b >=53){  //count up for revive
        
        digitalRead(button);
        fadeToBlackBy( leds, NUM_LEDS, 20);   //not required, experimenting with effects
       
          for(int i = 0; i < count; i++ ){
          leds[i] = CRGB::Green;                //all lights on
        }
        EVERY_N_MILLISECONDS( reviveDelay ) {  //substitutes delay, causing no lag in code
        count++;
        }}
      

      if (button == HIGH  && count !=0 && b >=53 ){ // pulse lights backwards
         b = 53;
         for(int i = 0; i < count; i++ ){
          leds[i] = CRGB::Green; 
         }
         EVERY_N_MILLISECONDS( 50 ) {
         count--;
                        //all lights off
//         Serial.println(count);}               
        
      }}
         
      if (button == HIGH && count >= NUM_LEDS){  //revived function
          delay(500);
          count = 0;
         leds[NUM_LEDS] = CRGB::Black;                //all lights off    
         }
         
          if (count > NUM_LEDS && bleedout < bleedTime && b >= 53){
            Serial.print("REVIVED");  
            revives++;
            leds[NUM_LEDS] = CRGB::Black;                //all lights off
            count = 0;                   //for revive function(fastled)
            testtime = 0;          //time grabbed for bleedout
            bleedout = 0;       //time result from (currenttime - testtime)
            Delay = 0;                    //mapped value for delay for pulse effect
            b = 0;  
            reset();
            //softReset();                             //for nano
}}
//------------Revive------------  

void loop() {  

button = digitalRead(buttonPin);
if (b >= 78){
  Serial.print("WIFI START");
  Delay = 300;
  //wifisetup();   //WIFI TEST
  //wifi();   //wifi test
  leds[6] = CRGB::Blue;
  //FastLED.show();
  Delay = 500;
}



//------------Start Sequence------------
if (button == LOW){
  b++;
  digitalRead(buttonPin);}
      
if (button == HIGH && b < 49 && b != 0){   //sleep function while not in use
  b = 0;                                   //resets button incase neusanse hit
  leds[NUM_LEDS] = CRGB::Black;            //all lights off
  //FastLED.show();
  reset();
  Serial.println("Going to sleep now");
  esp_deep_sleep_start();
  }                         //all lights off
if (button == HIGH && b < 49 && b == 0){
  esp_deep_sleep_start();
}
       delay(30);                          // affects attribute "b" counter time
        Serial.print(" b: ");
        Serial.print(b);
        Serial.println();

//------------Start Sequence------------

//------------Bleedout------------
             
 if (b >= 50 && bleedout <= bleedTime){           
    currenttime = millis();
    digitalRead (bleedout);  
    if (b >= 50 && b <= 52 && button == LOW){
        testtime = currenttime;  //locks current time as separate number to use to calculate bleed time
        }
    Serial.print(" bleedout: ");
    Serial.print(bleedout);
    Serial.print(" Delay: ");
    Serial.print(Delay);
    Serial.print(" fadeAmount: ");
    Serial.print(fadeAmount);
    Serial.print(" Brightness: ");
    Serial.print(brightness);
    Serial.println();
    bleedoutPulse();
    revive();
    //FastLED.show();
   }
    


if (brightness >240){
  digitalWrite(buzzer, HIGH);}
  else{
    digitalWrite(buzzer, LOW);}

//------------Bleedout------------  

if (bleedout >= bleedTime && b >= 55 && button == LOW){           
  softReset();
}
FastLED.show();
}

void reset(){
  Serial.print("Dead");
  count = 0;                   //for revive function(fastled)
  testtime = 0;          //time grabbed for bleedout
  bleedout = 0;       //time result from (currenttime - testtime)
  Delay = 0;                    //mapped value for delay for pulse effect
  b = 0; 
  //softReset();          //for nano
  leds[NUM_LEDS] = CRGB::Black;            //all lights off
  FastLED.show();
  delay(500);
  Serial.print(" bleedout: ");
    Serial.print(bleedout);
    Serial.print(" Delay: ");
    Serial.print(Delay);
    Serial.print(" fadeAmount: ");
    Serial.print(fadeAmount);
    Serial.print(" Brightness: ");
    Serial.print(brightness);
    Serial.print("count");
    Serial.print(count);
    Serial.println();
}
