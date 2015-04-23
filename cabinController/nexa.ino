// Copyright (c) 2015 geir54

// three pulses
void A() {
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(265);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(275);
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(260);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(270);
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(260);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(1280);
}

// two pulses
void B() {
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(260);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(260);
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(260);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(1280);
}

// one pulse
void C() {
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(260);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(1280);
}

void sendStart() {
  digitalWrite(transmitter, HIGH);
  delayMicroseconds(260);
  digitalWrite(transmitter, LOW);
  delayMicroseconds(2635);

  B();B();C();A();C();B();B();A();C();A();C();A();C();A();B();B();B();C();A();B();B();B();B();B();C();A();B();
}

void setChannel(int k) {
  if (k==1) {
    B();B();B();C();
  }

  if (k==2) {
    B();B();C();B();
  }
}

// Do it three times to make sure
void turnOn(int channel) {
  sendStart();
  C();A(); // trun on
  setChannel(channel);
  delay(100);
  sendStart();
  C();A(); // trun on
  setChannel(channel);
  delay(100);
  sendStart();
  C();A(); // trun on
  setChannel(channel);
}

void turnOff(int channel) {
  sendStart();
  B();B(); // trun off
  setChannel(channel);
  delay(100);
  sendStart();
  B();B(); // trun off
  setChannel(channel);
  delay(100);
  sendStart();
  B();B(); // trun off
  setChannel(channel);
}
