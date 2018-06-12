 /*
  * File  : DFRobot_SIM7000_HTTP.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example verify TCP connection over a HTTP request
  *         With initialization completed, we use connect(TCP,"www.taobao.com",80) to set TCP connection
  *         Then send a HTTP request to get the HEAD of taobao.com
  *         Thus we finished the TCP send and receive verification
  * Note  : If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;
static char        buff[350];

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    sim7000.begin(mySerial);
    delay(5000);
    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                                                                      //Turn ON SIM7000
        Serial.println("Turn ON !");
    }

    Serial.println("Set baud rate......");
    while(1){
        if(sim7000.setBaudRate(19200)){                                                        //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
            Serial.println("Set baud rate:19200");
            break;
        }else{
            Serial.println("Faile to set baud rate");
            delay(1000);
        }
    }

    Serial.println("Check SIM card......");
    if(sim7000.checkSIMStatus()){                                                              //Check SIM card
        Serial.println("SIM card READY");
        break;
    }else{
        Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7000");
        while(1);
    }

    Serial.println("Set net mode......");
    while(1){
        if(sim7000.setNetMode(NB)){                                                            //Set net mod NB-IOT
            Serial.println("Set NB-IOT mode");
            break;
        }else{
            Serial.println("Fail to set mode");
            delay(1000);
        }
    }

    Serial.println("Get signal quality......");
    signalStrength=sim7000.checkSignalQuality();                                               //Check signal quality from (0-30)
    Serial.print("signalStrength =");
    Serial.println(signalStrength);
    delay(500);

    Serial.println("Attaching service......");
    while(1){
        if(sim7000.attacthService()){                                                          //Open the connection
            Serial.println("Attach service");
            break;
        }else{
            Serial.println("Fail to Attach service");
            delay(1000);
        }
    }

    Serial.println("Connecting......");
    while(1){
        if(sim7000.openNetwork(TCP,"www.taobao.com",80)){                                      //Start Up TCP Connection
            Serial.println("Connect OK");
            break;
        }else{
            Serial.println("Fail to connect");
            delay(1000);
        }
    }

    sim7000.send("HEAD/HTTP/1.1\r\nHost:www.taobao.com\r\nConnection:keep-alive\r\n\r\n");     //Send Data
    dataNum=sim7000.recv(buff,350,0);                                                          //Receive data
    Serial.print("dataNum=");
    Serial.println(dataNum);
    Serial.println(buff);
    delay(500);
    Serial.println("Close connection......");

    while(1){
        if(sim7000.close()){                                                                   //End the connection
            Serial.println("Closed !");
            break;
        }else{
            Serial.println("Fail to close connection");
            delay(1000);
        }
    }
    delay(2000);
    sim7000.turnOFF();                                                                         //Turn OFF SIM7000
}

void loop() {
    delay(1000);
}