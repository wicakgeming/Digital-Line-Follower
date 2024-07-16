// Define pin numbers
int errsum_max = 22; 
int errsum_min = -22;
int kiriMaju = 6;      // MOTOR KIRI MAJU
int kiriMundur = 5;    // MOTOR KIRI MUNDUR
int kananMaju = 9;     // MOTOR KANAN MAJU
int kananMundur = 10;  // MOTOR KANAN MUNDUR
int pinSwLeftUp = 3;
int pinSwLeftDown = 2;
int pinSwRightUp = 11;
int pinSwRightDown = 12;
int ledLeft = 7;
int ledMid = 13;
int ledRight = 8;
String state;
String start = "Stop";
String kalibrasi = "Stop";
int BluetoothData;
char buff[100];
int counter = 0;

// Sensitivity thresholds
int peka = 900;

// Sensor arrays
int adc_sensor[8], sendat[8], pekax[8],
    sensorMax[8] = {0, 0, 0, 0, 0, 0, 0, 0},
    sensorMin[8] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023},
    robotSpeedRight, robotSpeedLeft,
    robotSpeed = 200,  // SPEED RANGE 0-255
    kp = 20,           // KP
    kd = 10,           // KD
    ki = 0,            // KI
    lastError = 0,
    error = 0,
    x,
    rate,
    sensorBit,
    maxpwm = 250,
    t;
int errsum = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Bluetooth Aktif silakan tekan 1 atau 0 kedipan LED..");
  
  // Define pin modes
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(kiriMaju, OUTPUT);
  pinMode(kiriMundur, OUTPUT);
  pinMode(kananMaju, OUTPUT);
  pinMode(kananMundur, OUTPUT);
  pinMode(pinSwLeftUp, INPUT_PULLUP);
  pinMode(pinSwLeftDown, INPUT_PULLUP);
  pinMode(pinSwRightUp, INPUT_PULLUP);
  pinMode(pinSwRightDown, INPUT_PULLUP);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledMid, OUTPUT);
  pinMode(ledRight, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    BluetoothData = Serial.read();
    if (BluetoothData == '1') {  // jika nomor 1 ditekan ....
      digitalWrite(ledLeft, 1);
      digitalWrite(ledMid, 1);
      digitalWrite(ledRight, 1);
      Serial.println("LED Menyala D13 HIDUP ! ");
      state = "linefollower";
    }
    if (BluetoothData == '0') {  // jika angka 0 ditekan ....
      digitalWrite(ledLeft, 0);
      digitalWrite(ledMid, 0);
      digitalWrite(ledRight, 0);
      Serial.println("LED Menyala D13 Mati ! ");
      state = "off";
      robotSpeedLeft = 0;
      robotSpeedRight = 0;
      setMotor(robotSpeedLeft, robotSpeedRight);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Berhenti");
      kalibrasi = "stop";
      start = "stop";
    }
    if (BluetoothData == 'w') {  // jika angka w ditekan ....
      robotSpeedLeft = 200;
      robotSpeedRight = 150;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Maju");
    }
        if (BluetoothData == 'W') {  // jika angka w ditekan ....
      robotSpeedLeft = 0;
      robotSpeedRight = 0;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Maju");
    }
    if (BluetoothData == 'a') {  // jika angka a ditekan ....
      robotSpeedLeft = 200;
      robotSpeedRight = -150;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Kiri");
    }
        if (BluetoothData == 'A') {  // jika angka a ditekan ....
      robotSpeedLeft = 0;
      robotSpeedRight = 0;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Kiri");
    }
    if (BluetoothData == 'd') {  // jika angka d ditekan ....
      robotSpeedLeft = -200;
      robotSpeedRight = 150;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Kanan");
    }
        if (BluetoothData == 'D') {  // jika angka d ditekan ....
      robotSpeedLeft = 0;
      robotSpeedRight = 0;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Kanan");
    }
    if (BluetoothData == 's') {  // jika angka s ditekan ....
      robotSpeedLeft = -200;
      robotSpeedRight = -150;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Mundur");
    }
        if (BluetoothData == 'S') {  // jika angka s ditekan ....
      robotSpeedLeft = 0;
      robotSpeedRight = 0;
      setMotor(robotSpeedLeft, robotSpeedRight);
      delay(40);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
      Serial.println("Mundur");
    }
    if (BluetoothData == 'c') {  // jika angka c ditekan ....
      digitalWrite(ledLeft, 1);
      digitalWrite(ledMid, 1);
      digitalWrite(ledRight, 1);
      Serial.println("Kalibrasi");
      state = "Kalibrasi";
      robotSpeedLeft = 0;
      robotSpeedRight = 0;
      setMotor(robotSpeedLeft, robotSpeedRight);
      Serial.print(robotSpeedLeft);
      Serial.print(" ");
      Serial.print(robotSpeedRight);
      Serial.print(" ");
    }
    if (BluetoothData == 'P') {  // jika angka p ditekan ....
      kp += 1;                   // KP
    }
    if (BluetoothData == 'p') {  // jika angka p ditekan ....
      kp -= 1;                   // KP
    }
    if (BluetoothData == 'Z') {  // jika angka Z ditekan ....
      kd += 1;                   // KD
    }
    if (BluetoothData == 'z') {  // jika angka z ditekan ....
      kd -= 1;                   // KD
    }
    if (BluetoothData == 'I') {  // jika angka Z ditekan ....
      ki += 1;                   // Ki
    }
    if (BluetoothData == 'i') {  // jika angka i ditekan ....
      ki -= 1;                   // Ki
    }
    if (BluetoothData == 'b') {  // jika angka b ditekan ....
      robotSpeed = 255;          // speed
    }
    if (BluetoothData == 'v') {  // jika angka v ditekan ....
      robotSpeed = 100;          // speed
    }
    if (BluetoothData == '+') {  // jika angka M ditekan ....
      robotSpeed += 5;           // speed
      if (robotSpeed >= 255) {
        robotSpeed = 255;
      }
    }
    if (BluetoothData == '-') {  // jika angka m ditekan ....
      robotSpeed -= 5;           // speed
      if (robotSpeed <= 0) {
        robotSpeed = 0;
      }
    }
  }
  
  if (state == "linefollower") {
    start = "high";
    kalibrasi = "stop";
  }
  if (state == "Kalibrasi") {
    kalibrasi = "mulai";
    start = "stop";
  }

  if (digitalRead(pinSwLeftUp) == LOW) {
    start = "high";
    kalibrasi = "stop";
  }

  if (digitalRead(pinSwLeftDown) == LOW) {
    kalibrasi = "mulai";
    start = "stop";
  }

  if (start == "high") {
    follow_line();  // menjalankan fungsi mengikuti garis
  }

  if (kalibrasi == "mulai") {
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
    kalibrasistart();  // menjalankan fungsi kalibrasi
    digitalWrite(ledMid, HIGH);
    delay(100);
    digitalWrite(ledMid, LOW);
    delay(100);
  }
}

void kalibrasistart() {
  adc_sensor[0] = analogRead(A3);
  adc_sensor[1] = analogRead(A2);
  adc_sensor[2] = analogRead(A1);
  adc_sensor[3] = analogRead(A0);
  adc_sensor[4] = analogRead(A7);
  adc_sensor[5] = analogRead(A6);
  adc_sensor[6] = analogRead(A5);
  adc_sensor[7] = analogRead(A4);
  delay(10);
  for (x = 7; x >= 0; x--) {
    if (adc_sensor[x] > sensorMax[x]) {
      sensorMax[x] = adc_sensor[x];
    }

    if (adc_sensor[x] < sensorMin[x]) {
      sensorMin[x] = adc_sensor[x];
    }
    pekax[x] = (sensorMax[x] + sensorMin[x]) / 2;
  }

  sprintf(buff, "Sensor Max : %3d %3d %3d %3d %3d %3d %3d %3d", sensorMax[7], sensorMax[6], sensorMax[5], sensorMax[4], sensorMax[3], sensorMax[2], sensorMax[1], sensorMax[0]);
  Serial.print(buff);
  sprintf(buff, " Nilai Tengah : %3d %3d %3d %3d %3d %3d %3d %3d", pekax[7], pekax[6], pekax[5], pekax[4], pekax[3], pekax[2], pekax[1], pekax[0]);
  Serial.print(buff);
  sprintf(buff, " Sensor Min : %3d %3d %3d %3d %3d %3d %3d %3d", sensorMin[7], sensorMin[6], sensorMin[5], sensorMin[4], sensorMin[3], sensorMin[2], sensorMin[1], sensorMin[0]);
  Serial.println(buff);
}

void readSensor() {
  adc_sensor[0] = analogRead(A3);
  adc_sensor[1] = analogRead(A2);
  adc_sensor[2] = analogRead(A1);
  adc_sensor[3] = analogRead(A0);
  adc_sensor[4] = analogRead(A7);
  adc_sensor[5] = analogRead(A6);
  adc_sensor[6] = analogRead(A5);
  adc_sensor[7] = analogRead(A4);
  delay(10);
  for (x = 7; x >= 0; x--) {
    if (adc_sensor[x] > pekax[x]) {
      sendat[x] = 1;
    } else {
      sendat[x] = 0;
    }
  }

  sensorBit = 0;
  for (x = 0; x <= 7; x++) {
    sensorBit += sendat[x] * (1 << x);
  }

  setMotor(robotSpeedLeft, robotSpeedRight);
  if (counter == 5) {
    sprintf(buff, "kp %d kd %d ki %d speed %d er %d Left %d Right %d", kp, kd, ki, robotSpeed, error, robotSpeedLeft, robotSpeedRight);
    Serial.println(buff);
    counter = 0;
  }
  counter += 1;
}

void pv() {
  switch (sensorBit) {
    case 0b10000000: error = -6; break;
    case 0b11000000: error = -5; break;
    case 0b01000000: error = -4; break;
    case 0b01100000: error = -4; break;
    case 0b00100000: error = -2; break;
    case 0b00110000: error = -1; break;
    case 0b00010000: error = 0; break;
    case 0b00011000: error = 0; break;
    case 0b00001000: error = 0; break;
    case 0b00001100: error = 1; break;
    case 0b00000100: error = 2; break;
    case 0b00000110: error = 4; break;
    case 0b00000010: error = 4; break;
    case 0b00000011: error = 5; break;
    case 0b00000001: error = 6; break;

    default: error = lastError; break;
  }
}

void follow_line() {
  readSensor();
  pv();

  if (error < -2) {
    digitalWrite(ledLeft, 0);
    digitalWrite(ledMid, 0);
    digitalWrite(ledRight, 1);
  } else if (error > 2) {
    digitalWrite(ledLeft, 1);
    digitalWrite(ledMid, 0);
    digitalWrite(ledRight, 0);
  } else {
    digitalWrite(ledLeft, 0);
    digitalWrite(ledMid, 1);
    digitalWrite(ledRight, 0);
  }
  rate = error - lastError;
  lastError = error;
  errsum += error;

  if (errsum > errsum_max) errsum = errsum_max;
  if (errsum < errsum_min) errsum = errsum_min;

  int moveControl = (kp * error) + (rate * kd) + (ki * errsum);

  robotSpeedRight = robotSpeed - moveControl;
  robotSpeedLeft = robotSpeed + moveControl;

  setMotor(robotSpeedLeft, robotSpeedRight);
}

void setMotor(int pwmLeft, int pwmRight) {
  if (pwmLeft > maxpwm) {
    pwmLeft = maxpwm;
  } else if (pwmLeft < -maxpwm) {
    pwmLeft = -maxpwm;
  }
  if (pwmLeft < 0) {
    pwmLeft *= -1;
    analogWrite(kiriMundur, pwmLeft);
    analogWrite(kiriMaju, 0);
  } else {
    analogWrite(kiriMundur, 0);
    analogWrite(kiriMaju, pwmLeft);
  }

  if (pwmRight > maxpwm) {
    pwmRight = maxpwm;
  } else if (pwmRight < -maxpwm) {
    pwmRight = -maxpwm;
  }
  if (pwmRight < 0) {
    pwmRight *= -1;
    analogWrite(kananMundur, pwmRight);
    analogWrite(kananMaju, 0);
  } else {
    analogWrite(kananMundur, 0);
    analogWrite(kananMaju, pwmRight);
  }
}