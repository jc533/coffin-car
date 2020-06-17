const int trigPin = 12; //Trig Pin
const int echoPin = 11; //Echo Pin
long duration, cm;
const int In1 = 4;
const int In2 = 5;
const int In3 = 6;      
const int In4 = 7;  
const int wallDistance = 20;
const int touchDistance = 10;
bool isTouch = 0;

void setup(){
    Serial.begin(9600);       // Serial Port begin
    pinMode(trigPin, OUTPUT); //Define inputs and outputs
    pinMode(echoPin, INPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);  
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
    // distance();
    // delay(250);
    // mfront();
    // delay(2000);
    // mstop();
    // delay(500);
    // mback();
    // delay(2000);
    // mstop();
    // delay(500);
} 
// analogWrite(E1Pin, 255);
// analogWrite(E2Pin, 255);
// int potValue = analogRead(A0); // Read potentiometer value
// int pwmOutput = map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
// analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
void autoPilot(){
    time = millis();
    int wtime = millis()+2000;
    int dis = distance();
    while(wait(wtime)){
        if(dis > touchDistance){
            isTouch = 1;
            forward();
        }else if(dis < touchDistance){ 
            isTouch = 1;
        }
        if (isTouch){
            turnLeft();
            forward();
        }                                                                                                                                                                                                                                                                                                                                                 
        
        
    }
}
void stop(){                       // 馬達停止
    analogWrite(EA, 0); // 馬達 A 的 PWM 輸出
    analogWrite(EB, 0); // 馬達 B 的 PWM 輸出
}
void forward(){                           // 馬達轉向：前進
    analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
    digitalWrite(IA, HIGH);
}
void backward(){                           // 馬達轉向：後退
    analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
    digitalWrite(IA, LOW);
}
void turnLeft(){                           // 馬達轉向：左轉
    analogWrite(EB, speed); // 馬達 A 的 PWM 輸出
    digitalWrite(IB, LOW);  // 馬達 A 反轉
}
void turnRight(){                           // 馬達轉向：右轉
    analogWrite(EB, speed); // 馬達 B 的 PWM 輸出
    digitalWrite(IB, HIGH);  // 馬達 B 反轉
}