#include <Wire.h>
#include <SoftwareSerial.h> // 引用「軟體序列埠」程式庫
#include <Servo.h> 
SoftwareSerial BT(10, 11);    // 設定軟體序列埠(接收腳, 傳送腳)
Servo myservo;
const byte EA = 6; // 馬達 A 的致能接腳
const byte IA = 7; // 馬達 A 的正反轉接腳
int dir = 0;
int index = 0;
// 設定 PWM 輸出值
int speed = 150;
string map = "lrrllrlrx";
const int trigPin = 12; //Trig Pin
const int echoPin = 11; //Echo Pin
long duration, cm;
const int wallDistance = 20;
const int touchDistance = 10;
bool isTouch = 0;

void setup(){
    Serial.begin(9600);       // Serial Port begin
    pinMode(trigPin, OUTPUT); //Define inputs and outputs
    pinMode(echoPin, INPUT);
    Serial.println("ready!");
    myservo.attach(9);
    myservo.write(88);
    pinMode(IA, OUTPUT); // 馬達 A 的致能腳位
    stop();  
}
int distance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH); // 給 Trig 高電位，持續 10微秒
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pinMode(echoPin, INPUT);           // 讀取 echo 的電位
    duration = pulseIn(echoPin, HIGH); // 收到高電位時的時間

    cm = (duration/2)/29.1; // 將時間換算成距離 cm 或 inch
    Serial.print("Distance : ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    return cm;
    //delay(250);
}
bool wait(int waitTime){
    bool isTime = 0;
    time = millis();
    if(time >= waitTime)
        isTime = 1;
    return isTime;
}
void loop(){
    autoPilot()
} 
void autoPilot(){
    if(distance < touchDistance){
        switch (map[++index]){
        case "l":
            turnLeft();
            forward();
            delay(1000);
            break;
        case "r":
            turnRight();
            forward();
            delay(1000);
            break;
        case "x":
            stop();
        }
    }else{
        turnForward();
        forward();
    }
    
}

void stop(){                       // 馬達停止
    analogWrite(EA, 0); // 馬達 A 的 PWM 輸出
}
void forward(){                           // 馬達轉向：前進
    analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
    digitalWrite(IA, HIGH);

}
void backward(){                           // 馬達轉向：後退
    analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
    digitalWrite(IA, LOW);
}
void turnLeft(){   
    switch (dir){
        case 1:
            break;
        default:
            myservo.write(35);
            dir = -1;
    }   
}
void turnRight(){     
    switch (dir){
        case -1:
            break;
        default:
            myservo.write(-35);
            dir = -1;
    } 
}
void turnForward(){     
    switch (dir){
        case 0:
            break;
        default:
            myservo.write(88);
            dir = 0;
    } 
}