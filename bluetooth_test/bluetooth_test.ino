#include <Wire.h>
#include <SoftwareSerial.h> // 引用「軟體序列埠」程式庫
#include <Servo.h> 
SoftwareSerial BT(10, 11);    // 設定軟體序列埠(接收腳, 傳送腳)
Servo myservo;

char command;      // 接收序列埠值的變數
const byte EA = 6; // 馬達 A 的致能接腳
const byte IA = 7; // 馬達 A 的正反轉接腳
int dir = 0;

// 設定 PWM 輸出值
const byte speed = 150;

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

void setup(){
    BT.begin(9600); // 啟動軟體序列埠
    Serial.begin(38400); // 「序列埠監控視窗」的資料 需要以38400輸出
    Serial.println("BT is ready!");
    myservo.attach(9);
    myservo.write(88);
    pinMode(IA, OUTPUT); // 馬達 A 的致能腳位
    // pinMode(IB, OUTPUT); // 馬達 B 的致能腳位
    stop();              // 先停止馬達
}

void loop(){
//    Serial.print("test");
//    Serial.println(BT.available());
    if (BT.available()){
        command = BT.read();
        Serial.print(command);
        switch (command){
        case 'w': // 接收到 'w'，前進
            forward();
            break;
        case 's': // 接收到 's'，後退
            backward();
            break;
        case 'a': // 接收到 'a'，左轉
            turnLeft();
            break;
        case 'd': // 接收到 'd'，右轉
            turnRight();
            break;
        case 'x': // 接收到 'x'，停止馬達
            stop();
            break;
        }
        case 'k':
            turnForward();
            break;
        }
        case 'p':
            speed = 255;
            break;
        }
        case 'q': // 接收到 'x'，停止馬達
            speed = 150;
            break;
        }
    }
}
