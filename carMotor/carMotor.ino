const int JOY_SW_PIN = PIN_PC0;
const int JOY_VRX_PIN = PIN_PC4;
const int JOY_VRY_PIN = PIN_PC2;

const int DRIVE_A_IN1 = PIN_PB2;
const int DRIVE_A_IN2 = PIN_PB0;
const int DRIVE_B_IN1 = PIN_PB3;
const int DRIVE_B_IN2 = PIN_PB1;

const int SPRAYER_SW = PIN_PD5;

void forwardA() {
  digitalWrite(DRIVE_A_IN1, LOW);
  digitalWrite(DRIVE_A_IN2, HIGH);
}

void forwardB() {
  digitalWrite(DRIVE_B_IN1, LOW);
  digitalWrite(DRIVE_B_IN2, HIGH);
}

void backwardA() {
  digitalWrite(DRIVE_A_IN1, HIGH);
  digitalWrite(DRIVE_A_IN2, LOW);
}

void backwardB() {
  digitalWrite(DRIVE_B_IN1, HIGH);
  digitalWrite(DRIVE_B_IN2, LOW);
}

void stopA() {
  digitalWrite(DRIVE_A_IN1, HIGH);
  digitalWrite(DRIVE_A_IN2, HIGH);
}

void stopB() {
  digitalWrite(DRIVE_B_IN1, HIGH);
  digitalWrite(DRIVE_B_IN2, HIGH);  
}

void setup() {
  // car
  pinMode(DRIVE_A_IN1, OUTPUT);
  pinMode(DRIVE_A_IN2, OUTPUT);
  pinMode(DRIVE_B_IN1, OUTPUT);
  pinMode(DRIVE_B_IN2, OUTPUT);

  // joy
  pinMode(JOY_SW_PIN, INPUT_PULLUP);
  pinMode(JOY_VRX_PIN, INPUT);
  pinMode(JOY_VRY_PIN, INPUT);

  pinMode(SPRAYER_SW, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // IN1, IN3 HIGH D
  // IN1, IN3 LOW R

  int vrx = analogRead(JOY_VRX_PIN);  
  int vry = analogRead(JOY_VRY_PIN);  
  int sw = digitalRead(JOY_SW_PIN);

  if((vrx >= 0) && (vrx < 101) && (vry >= 0) && (vry < 100)) {
    backwardA();
    backwardB();
  } else if((vrx >= 850) && (vrx < 1024) && (vry >= 800) && (vry < 1024)) {
    forwardA();
    forwardB();
  } else if((vrx >= 640) && (vrx < 751) && (vry >= 650) && (vry < 751)) {
    forwardB();
    stopA();
    // ^ right
  } else if((vrx >= 275) && (vrx < 470) && (vry >= 230) && (vry < 346)) {
    forwardA();
    stopB();
    // ^ left
  } else {
    stopA();
    stopB();
  }

  if(!sw) {
    digitalWrite(SPRAYER_SW, LOW);   
  } else {
    digitalWrite(SPRAYER_SW, HIGH);  
  }
  
  Serial.print(vrx);
  Serial.print(" ");
  Serial.print(vry);
  Serial.print(" ");
  Serial.println();
}
