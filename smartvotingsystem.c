#include <Adafruit_Fingerprint.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
int button1=A0;
int button2=A1;
int button3=A2;
 int sum=0,count=0,total=0; int grandtotal;
// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600); 
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
    if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  lcd.begin(16,2);
  lcd.println("place ur finger");
 
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);
 
  if(finger.fingerID==1||finger.fingerID==2||finger.fingerID==3||finger.fingerID==4||finger.fingerID==5||finger.fingerID==6||finger.fingerID==7||finger.fingerID==8||finger.fingerID==9||finger.fingerID==10)
  {vote();
   
 }
if(finger.fingerID==11)
{
  Serial.print("Party1 : ");
  Serial.println(sum);
  Serial.print("Party2 : ");
  Serial.println(count);
  Serial.print("Party3 : ");
  Serial.println(total);
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("TPV :");
   lcd.print(grandtotal);
   lcd.setCursor(8,0);
   lcd.print("P1:");
   lcd.print(sum);
   lcd.setCursor(0,1);
   lcd.print("P2:");
   lcd.print(count);
   lcd.setCursor(7,1);
   lcd.print("P3:");
   lcd.print(total);
  }
 
  //don't ned to run this at full speed.
}
void vote()
 
 { int i,j,k;
 
 
  i=digitalRead(button1);
  j=digitalRead(button2);
  k=digitalRead(button3);

  if (finger.verifyPassword()){
 
if(i==1){
   Serial.print("voted for party ");
 sum=sum+1;
     grandtotal=sum+count+total;
 Serial.print("PARTY1:");
// Serial.println(sum);
  Serial.print("Grandtotal");
   Serial.println(grandtotal);finger.fingerID=0;
   lcd.clear();
   lcd.print("place ur finger");
 }
 
  if(j==1){
   Serial.print("voted for party ");
 count=count+1;
     grandtotal=sum+count+total;
 Serial.print("PARTY2:");
 //Serial.println(count);
  Serial.print("Grandtotal");
   Serial.println(grandtotal);finger.fingerID=0;
   lcd.clear();
   lcd.print("place ur finger");}
 
   if(k==1)
   {
   Serial.print("voted for party ");
   total=total+1;
       grandtotal=sum+count+total;
   Serial.print("PARTY3:");
   //Serial.println(total);
    Serial.print("Grandtotal");
     Serial.println(grandtotal);
     finger.fingerID=0;lcd.clear();
   lcd.print("place ur finger");}}}
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
 
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }  
 
  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);

  return finger.fingerID;
 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
 
  // found a match!
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  delay(1000);
  digitalWrite(12,LOW);
  Serial.print("Found ID #");
  Serial.println(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);
Serial.print("press the button once");
lcd.clear();
lcd.print("press the button once");
  return finger.fingerID;
}
