int potPins[] = { 0, 1 };
int vals[] = { 0, 0 };
int potCount = 2;
int tolerance = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.println("Done");
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < potCount; i++) {
    int newVal = analogRead(potPins[i]);
    if (abs(newVal-vals[i]) > tolerance) {
      vals[i] = newVal;
      Serial.println(String(potPins[i]) + ":" + String(vals[i]));
    }
  }
  
}
