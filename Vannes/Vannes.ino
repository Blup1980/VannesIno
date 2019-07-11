//********************************************************************************************
//                                                                                           *
// AB&T Tecnologie Informatiche - Ivrea Italy                                                *
// http://www.bausano.net                                                                    *
// https://www.ethercat.org/en/products/791FFAA126AD43859920EA64384AD4FD.htm                 *
//                                                                                           *  
//********************************************************************************************   
 
//********************************************************************************************    
//                                                                                           *
// This software is distributed as an example, "AS IS", in the hope that it could            *
// be useful, WITHOUT ANY WARRANTY of any kind, express or implied, included, but            *
// not limited,  to the warranties of merchantability, fitness for a particular              *
// purpose, and non infringiment. In no event shall the authors be liable for any            *    
// claim, damages or other liability, arising from, or in connection with this software.     *
//                                                                                           *
//******************************************************************************************** 



//---- AB&T EasyCAT shield --- V.2_0------------------------------------------------------------------------------
//---- Multi I/O EtherCAT slave application example -------------------------------------------------------------  


#define CUSTOM                      // Custom mode
#include "EtherCarConfigurator.h"
#include "EasyCAT.h"                // EasyCAT library
#include <Servo.h>

#include <SPI.h>                    // SPI library - The EasyCAT shield is connected to the SPI bus

EasyCAT EASYCAT;                    // EasyCAT istantiation 
                                    // For this application we must use the
                                    // default SPI chip select = pin 9   (check your board setting!)

                                    // For others applications the constructor allow    
                                    // us to choose the chip select pin: 
                                                                      
                                    // for EasyCAT board REV_A we can choose between:
                                    // 8, 9, 10 
                                    //  
                                    // for EasyCAT board REV_B we can choose between:
                                    // 8, 9, 10, A5, 6, 7           



Servo myservo;



//---- pins declaration ------------------------------------------------------------------------------


const int Pwm0 = 3;                 // PWM declaration

const int BitIn0 = 2;              // Digital inputs declaration
const int BitIn1 = 4;              //
const int BitIn2 = 5;              // 
const int BitIn3 = 6;              // 
const int BitIn4 = 7;              //
const int BitIn5 = 8;              //
const int BitIn6 = 10;              // 
const int BitIn7 = 11;              // 
const int BitIn8 = 12;              //

const int LedRed = 13;              // HALT/RUN led pins declaration  


//---- global variables ---------------------------------------------------------------------------

unsigned long Millis, PreviousMillis = 0;

unsigned char EcatState;
unsigned char N_Cycles = 0;
bool Blink = true;



//---- setup ---------------------------------------------------------------------------------------
 
void setup()
{

  myservo.attach(3);  
  

  pinMode(BitIn0, INPUT_PULLUP);                                  // Digital inputs setting
  pinMode(BitIn1, INPUT_PULLUP);                                  // 
  pinMode(BitIn2, INPUT_PULLUP);                                  //
  pinMode(BitIn3, INPUT_PULLUP);                                  //
  pinMode(BitIn4, INPUT_PULLUP);                                  // 
  pinMode(BitIn5, INPUT_PULLUP);                                  //
  pinMode(BitIn6, INPUT_PULLUP);                                  //
  pinMode(BitIn7, INPUT_PULLUP);                                  //
  pinMode(BitIn8, INPUT_PULLUP);                                  // 

  pinMode(LedRed, OUTPUT);                                        // HALT/RUN led pins setting
                                                                  //
  digitalWrite (LedRed, LOW);                                     //
                                                                  //---- initialize the EasyCAT board -----
                                                                  
  if (EASYCAT.Init() == true)                                     // Initialization
  {                                                               // succesfully completed

    
  }                                                               //
  
  else                                                            // Initialization failed   
  {                                                               // The EasyCAT board was not recognized
                                                                  // with the red led blinking fast
    while(1)                                                      //
    {                                                             //   
      digitalWrite (LedRed, LOW);                                 // 
      delay(10);                                                 //   
      digitalWrite (LedRed, HIGH);                                //  
      delay(100);                                                 // 
    }                                                             // 
  }    

  PreviousMillis = millis();  
}


//---- main loop ----------------------------------------------------------------------------------------
 
void loop()                                             // In the main loop we must call ciclically the 
{                                                       // EasyCAT task and our application
                                                        //
                                                        // This allows the bidirectional exachange of the data
                                                        // between the EtherCAT master and our application
                                                        //
                                                        // The EasyCAT cycle and the Master cycle are asynchronous
                                                        //   

  EcatState = EASYCAT.MainTask();                       // execute the EasyCAT task
  
  Application();                                        // user applications
}


//---- user application ------------------------------------------------------------------------------

void Application ()                                   // Here we manage the I/O resources of the Arduino Mega board                                 

{
  UWORD Analog;

  unsigned char i;
  unsigned char Temp, Val;

  Millis = millis();                                    // For this application we choose a cycle time of 50 mS
  if (Millis - PreviousMillis >= 50)                    // 
  {                                                     // 
    PreviousMillis = Millis;                            //
  
                                                        //------- 16 digital inputs -----------------------------------------------
                                                        //
    EASYCAT.BufferIn.Cust.SW0 = digitalRead(BitIn0);
    EASYCAT.BufferIn.Cust.SW1 = digitalRead(BitIn1);
    EASYCAT.BufferIn.Cust.SW2 = digitalRead(BitIn2);
    EASYCAT.BufferIn.Cust.SW3 = digitalRead(BitIn3);
    EASYCAT.BufferIn.Cust.SW4 = digitalRead(BitIn4);
    EASYCAT.BufferIn.Cust.SW5 = digitalRead(BitIn5);
    EASYCAT.BufferIn.Cust.SW6 = digitalRead(BitIn6);
    EASYCAT.BufferIn.Cust.SW7 = digitalRead(BitIn7);
    EASYCAT.BufferIn.Cust.SW8 = digitalRead(BitIn8);


                                                        //------- servo outputs -------------------------------------------------
    myservo.write(EASYCAT.BufferOut.Cust.PWM);
  
  
                                                        //------ HALT/RUN visualization ---------------------------------------
  
    if (EcatState == 0x08)                              // If the EasyCAT is in Operational State
    {                                                   // and the communication is running
      {                                                 //
        digitalWrite(LedRed, LOW);                      // we switch on the green led
      }                                                 //
    }
  
    else                                                // Otherwise we blink the red led 
    {                                                   //                                                 
      if (N_Cycles++ > 4)                               //
      {                                                 //
        N_Cycles = 0;                                   //  
        if (Blink)                                      //
        {                                               //
          digitalWrite(LedRed, HIGH);                   //
          Blink = false;                                //
        }                                               //  
        else                                            //  
        {                                               //
          digitalWrite(LedRed, LOW);                    //
          Blink = true;                                 //
        }                                               //
      }                                                 //
    }                                                   //
  }                                                     //    
}                                                       //
