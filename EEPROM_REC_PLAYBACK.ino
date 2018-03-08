#include < EEPROM.h >
int addr = 0;
int address = 0;
byte value; // unknown!
int theState; // variable to store button state
int lastState; // variable to store last button state
long previousMillis = 0; // not needed? variable to store last time LED was updated
long startTime; // start time
long elapsedTime; // elapsed time
int mmode = 0; //Needs to NOT be a pin assignment. just a variable!
int ldr = 0;
int penmotor = 6;
int modeswitch = 3;
int testswitch = 2;
int lastSense = 0;
int sensing;
int thresheld = 970;
int switchie;
void setup() {
  pinMode(ldr, INPUT);
  pinMode(penmotor, OUTPUT);
  pinMode(modeswitch, INPUT);
  pinMode(testswitch, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("Threshold = ");
  Serial.println(thresheld);

}
void loop() {
  switchie = digitalRead(modeswitch);

  sensing = analogRead(ldr);
  /Serial.print("LDR = ");
  //Serial.println(sensing);
  if ((switchie == HIGH)) {}
  if (((sensing > thresheld || sensing < 56) && sensing != lastSense) && (switchie == HIGH) && (mmode != 2)) //swapped threshold greater than for this due to non analog input.
  {
    digitalWrite(penmotor, HIGH);
    elapsedTime = millis() - startTime;
    int scanned = elapsedTime;
    EEPROM.write(addr, scanned);
    addr = addr + 1;
    Serial.print("Adr =");
    Serial.println(addr);
    Serial.print("scanned =");
    Serial.println(scanned);
    startTime = millis();
    delay(5);
    lastSense = sensing;
    if (addr == EEPROM.length()) {
      addr = 0;
      mmode = 2; //stop when done
      digitalWrite(penmotor, LOW);
    }
    delay(100);
  }
  if (digitalRead(testswitch) == LOW) {

    int timing = EEPROM.read(address);
    digitalWrite(penmotor, HIGH);
    delay(timing);
    Serial.print("Address =");
    Serial.print(address);
    Serial.print("   Data =");
    Serial.println(timing);
    digitalWrite(penmotor, LOW);
    address = address + 1;
    delay(timing);
    Serial.print("Address =");
    Serial.print(address);
    Serial.print("   Data =");
    Serial.println(timing);
  } else {
    address = 0;
  }
  if (address > 10) {
    address = 0;
    mmode = 3; //stop when done.
  }
} else {
  //do nothing 
}
}
