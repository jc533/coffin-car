#include <SoftwareSerial.h> // 引用「軟體序列埠」程式庫
#include <Servo.h> 
SoftwareSerial BT(3, 2);    // 設定軟體序列埠(接收腳, 傳送腳)
Servo myservo;

char command;      // 接收序列埠值的變數
const byte EA = 6; // 馬達 A 的致能接腳
const byte IA = 7; // 馬達 A 的正反轉接腳

// 設定 PWM 輸出值
const byte speed = 130;

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
void turnLeft(){   
    myservo.write(90)
    myservo.write(45)
}
void turnRight(){     
    myservo.write(90)
    myservo.write(135)
}

void setup(){
    BT.begin(9600); // 啟動軟體序列埠
    myservo.attach(9);
    myservo.write(90);
    pinMode(IA, OUTPUT); // 馬達 A 的致能腳位
    // pinMode(IB, OUTPUT); // 馬達 B 的致能腳位
    stop();              // 先停止馬達
}

void loop(){
    if (BT.available()){
        command = BT.read();

        switch (command){
        case 'w': // 接收到 'w'，前進
            forward();
            break;
        case 'x': // 接收到 'x'，後退
            backward();
            break;
        case 'a': // 接收到 'a'，左轉
            turnLeft();
            break;
        case 'd': // 接收到 'd'，右轉
            turnRight();
            break;
        case 's': // 接收到 's'，停止馬達
            stop();
            break;
        }
    }
}