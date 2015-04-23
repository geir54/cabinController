// Copyright (c) 2015 geir54

int transmitter = 10;
String pin = "";

// Array of approved telephone numbers
#define nrSize  1
String approvedNrs[] = {};

String data; // Allocate some space for the string
char inChar;
boolean msgNext = false; // The next string will be a text message
String askedFor; // The message we are asking for

  // Turn on GSM module
void turnModuleOn() {
  digitalWrite(4, HIGH);
  delay(2200);
  digitalWrite(4, LOW);
  delay(4000); // give it a chance to power up
  Serial.println("AT+CPIN="+pin); // send the pin
}

void setup() {
  pinMode(4, OUTPUT); // GSM PWR
  pinMode(5, OUTPUT);digitalWrite(5, HIGH); // extra 5v pin
  pinMode(6, INPUT); // RI
  pinMode(13, OUTPUT); // test led

  pinMode(transmitter, OUTPUT); // transmitter

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  turnModuleOn();
}

void checkString() {
  // The body of the text msg, all the commands will be listed here
  if (msgNext) {
      if (data.substring(0,6).equals("Ovn pa")) {
        delay(1000);
        turnOn(1);
      }

      if (data.substring(0,6).equals("Ovn av")) {
        delay(1000);
        turnOff(1);
      }

      // delete the msg
      Serial.println("AT+CMGD="+askedFor);
      msgNext = false;
      return;
  }

  if (data.substring(0,9).equals("SMS Ready")) {
    Serial.println("AT+CMGF=1"); // set text mode
  }

  // new message recived
  if (data.substring(0,12).equals("+CMTI: \"SM\",")) {
    String i = data.substring(12,13);
    askedFor = i; // The message we are asking for
    Serial.println("AT+CMGR="+i); // Aske for the message
  }

  if (data.substring(0,7).equals("+CMGR: ")) { // A message
    // Only accept msg if it's from the right number. If not just delete
    String nr = data.substring(24,32);
    boolean approved=false;
    for (int i=0; i < nrSize; i++) {
      if (approvedNrs[i] == nr) approved = true;
    }

    if (approved) {
      msgNext = true;
    }
      else
    {
      Serial.println("AT+CMGD="+askedFor); // delete the one we askedFor
    }
  }
}

// Loop and wait for data
void loop() {
  if (digitalRead(6) == LOW) { // If RI goes low the module has turned of
    delay(200); // wait and check again
    if (digitalRead(6) == LOW) turnModuleOn(); // turn it back on
  }

  while (Serial.available() > 0) {
    inChar = Serial.read();
    if (inChar == '\n') {
      checkString();
      data="";
    }
      else
    {
      data += inChar;
    }
  }
}
