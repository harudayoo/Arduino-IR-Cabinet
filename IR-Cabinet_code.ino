#include <SoftwareSerial.h>

// GSM Module pins
SoftwareSerial gsm(3, 2); // RX, TX

// IR Sensor pins for 11 compartments
const int sensorPins[11] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0};

// Compartment labels (kamo na butang ug unsay ilabel ninyo diri kay diri niya kuhaon ang isend sa text)
const char* partNames[11] = {
  "Motherboard",
  "CPU",
  "RAM",
  "GPU",
  "Power Supply",
  "Hard Drive",
  "SSD",
  "CPU Cooler",
  "Case Fans",
  "Cables",
  "Screws/Tools"
};

bool prevState[11];
bool currentState[11];

// SMS cellphone number (example: +639123456789)
String phoneNumber = "+639123456789";

unsigned long lastDebounceTime[11] = {0};
const unsigned long debounceDelay = 2000; // 2 seconds detection bago mutrigger ang sensor

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);
  
  Serial.println("=================================");
  Serial.println("PC Parts Cabinet Security System");
  Serial.println("=================================");
  Serial.println("Initializing...");
  
  for (int i = 0; i < 11; i++) {
    pinMode(sensorPins[i], INPUT);
    prevState[i] = digitalRead(sensorPins[i]);
    currentState[i] = prevState[i];
  }
  
  delay(2000); // Wait for GSM to stabilize
  initGSM();
  
  Serial.println("Sending startup notification...");
  sendSMS("PC Parts Cabinet security system is now ACTIVE. All 11 compartments are being monitored.");
  
  Serial.println("=================================");
  Serial.println("System Ready!");
  Serial.println("Monitoring all compartments...");
  Serial.println("=================================");
}

void loop() {
  for (int i = 0; i < 11; i++) {
    int reading = digitalRead(sensorPins[i]);
    
    if (reading != currentState[i]) {
      lastDebounceTime[i] = millis();
      currentState[i] = reading;
    }
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // If this is a new state change
      if (currentState[i] != prevState[i]) {
        prevState[i] = currentState[i];
        
        // HIGH means pc part detected (either kamot or mismong pc part)
        if (currentState[i] == HIGH) {
          handleAccess(i);
        } else {
          handleClear(i);
        }
      }
    }
  }
  
  delay(100);
}

void handleAccess(int compartment) {
  Serial.println("=================================");
  Serial.print("ALERT! Compartment accessed: #");
  Serial.println(compartment + 1);
  Serial.print("Part Category: ");
  Serial.println(partNames[compartment]);
  Serial.println("=================================");
  
  String message = "ALERT! Compartment ";
  message += String(compartment + 1);
  message += " (";
  message += partNames[compartment];
  message += ") has been accessed. Items may have been removed.";
  
  sendSMS(message);
}

void handleClear(int compartment) {
  Serial.print("Access complete - Compartment ");
  Serial.print(compartment + 1);
  Serial.print(" (");
  Serial.print(partNames[compartment]);
  Serial.println(") - sensor cleared");
  
  // optional lang ni
  /*
  String message = "Compartment ";
  message += String(compartment + 1);
  message += " (";
  message += partNames[compartment];
  message += ") access complete.";
  sendSMS(message);
  */
}

void initGSM() {
  Serial.println("Initializing GSM module...");
  
  // Test AT command
  gsm.println("AT");
  delay(1000);
  readGSMResponse();
  
  // SMS to text mode
  gsm.println("AT+CMGF=1");
  delay(1000);
  readGSMResponse();
  
  // Set SMS parameters
  gsm.println("AT+CNMI=1,2,0,0,0");
  delay(1000);
  readGSMResponse();
  
  // Check signal
  Serial.println("Checking signal strength...");
  gsm.println("AT+CSQ");
  delay(1000);
  readGSMResponse();
  
  Serial.println("GSM module ready!");
}

void sendSMS(String message) {
  Serial.println("Sending SMS...");
  Serial.print("To: ");
  Serial.println(phoneNumber);
  Serial.print("Message: ");
  Serial.println(message);
  
  gsm.println("AT+CMGF=1"); // Text mode
  delay(500);
  
  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");
  delay(1000);
  
  gsm.print(message);
  delay(500);
  
  gsm.write(26); // Ctrl+Z to send SMS
  delay(5000);
  
  readGSMResponse();
  Serial.println("SMS sent successfully!");
}

void readGSMResponse() {
  // Read and display GSM module response
  while (gsm.available()) {
    char c = gsm.read();
    Serial.write(c);
  }
}

// Optional: Function to check battery voltage (if using voltage divider on A1)
// para lang ni siya if gusto nimo i-monitor ang battery voltage
void checkBatteryVoltage() {
  // Connect battery through voltage divider to A1
  // R1 = 10kΩ (to battery), R2 = 10kΩ (to ground)
  
  int rawValue = analogRead(A1);
  float voltage = (rawValue / 1023.0) * 5.0 * 2; // *2 for voltage divider
  
  Serial.print("Battery Voltage: ");
  Serial.print(voltage);
  Serial.println("V");
  
  if (voltage < 11.5) {
    Serial.println("WARNING: Battery voltage low!");
    sendSMS("WARNING: Cabinet system battery is low (" + String(voltage) + "V). Please recharge soon.");
  }
}