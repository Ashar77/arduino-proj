#define bluetooth Serial
#include <Servo.h>

Servo myServo;

char cmd[100];
int cmdIndex;

void exeCmd() {
  
  if(cmd[0]=='x' && cmd[1]==' ') {
    
    // value starts at cmd[2]
    // atof converts string to float
    
    float val = atof(cmd+2);
    
    val = val/9.8;
    val = val*500;
    
    int servoMicroseconds = 1500+val;
    
    myServo.writeMicroseconds(servoMicroseconds);      
  }   
}

void setup() {
  
  delay(500); // wait for bluetooth module to start

  bluetooth.begin(115200); // Bluetooth default baud is 115200
  
  myServo.attach(4, 1000, 2000);
  
  cmdIndex = 0;
}

void loop() {
  
  if(bluetooth.available()) {


      String val = Serial.readString();
      Serial.println("message is : ");
      Serial.println(val);
    
    char c = (char)bluetooth.read();
    
    if(c=='\n') {
      cmd[cmdIndex] = 0;
      exeCmd();  // execute the command
      cmdIndex = 0; // reset the cmdIndex
    } else {      
      cmd[cmdIndex] = c;
      if(cmdIndex<99) cmdIndex++;
    }
  }
}
