/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> // 引用程式庫

SoftwareSerial BT(9, 8); // RX | TX
int val = 0;
// int motorpin = 4;
// int motorpin2 = 6;
const int In1 = 4;
const int In2 = 5;
const int In3 = 6;      
const int In4 = 7; 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
	lcd.begin();
	lcd.backlight();

	// Initialize the serial port at a speed of 9600 baud
	//Serial.begin(9600);

	Serial.begin(38400); // 「序列埠監控視窗」的資料 需要以38400輸出
	Serial.println("BT is ready!");
	BT.begin(9600);

	pinMode(motorpin, OUTPUT);
	pinMode(motorpin2, OUTPUT);
}
void stop(){						// 馬達停止
	analogWrite(EA, 0); // 馬達 A 的 PWM 輸出
	analogWrite(EB, 0); // 馬達 B 的 PWM 輸出
}
void forward(){							// 馬達轉向：前進
	analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
	digitalWrite(IA, HIGH);
	analogWrite(EB, speed); // 馬達 B 的 PWM 輸出
	digitalWrite(IB, HIGH);
}
void backward(){							// 馬達轉向：後退
	analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
	digitalWrite(IA, LOW);
	analogWrite(EB, speed); // 馬達 B 的 PWM 輸出
	digitalWrite(IB, LOW);
}
void turnLeft(){							// 馬達轉向：左轉
	analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
	digitalWrite(IA, LOW);	// 馬達 A 反轉
	analogWrite(EB, speed); // 馬達 B 的 PWM 輸出
	digitalWrite(IB, HIGH);
}
void turnRight(){							// 馬達轉向：右轉
	analogWrite(EA, speed); // 馬達 A 的 PWM 輸出
	digitalWrite(IA, HIGH);
	analogWrite(EB, speed); // 馬達 B 的 PWM 輸出
	digitalWrite(IB, LOW);	// 馬達 B 反轉
}

void loop(){
	if (BT.available()){
		val = BT.read();
		lcd.write(val);
		update(val); // Keep reading from HC-05 and control it
		Serial.print(val);
	}
}

void update(int x){
	switch (x){
	case 97: //a
		forward()
		break;

	case 98: //b
		backward()
		break;

	case 49: //1
		turnLeft()
		break;

	case 50: //2
		turnRight()
		break;

	// case 51: //3
	// 	digitalWrite(motorpin, LOW);
	// 	break;

	// case 52: //4
	// 	digitalWrite(motorpin2, LOW);
	// 	break;

	case 62:				 //change line
		lcd.setCursor(0, 1); // 設定游標位置在第二行行首
		break;

	case 60:		 //delete all
		lcd.clear(); // 設定游標位置在第二行行首
		break;

	case 63:				 //first line
		lcd.setCursor(0, 0); // 設定游標位置在第一行行首
		break;
	}
}
