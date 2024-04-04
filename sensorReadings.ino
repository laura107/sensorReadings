#include <M5StickCPlus.h>

#define BUTTON_PIN 37 // Define the button pin

enum SensorReading { WELCOME, GYROSCOPE, ACCELEROMETER, BATTERY }; // pages

SensorReading currentReading = WELCOME; // first page
bool shouldUpdateScreen = true; 

void setup() {
  M5.begin(); 
  M5.Lcd.setRotation(3); 
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) { 
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(50);
    }

    // next page
    currentReading = (SensorReading)((currentReading + 1) % 4);
    shouldUpdateScreen = true; 
    delay(200); 
  }

  if (shouldUpdateScreen) {
    if (currentReading == WELCOME)
      displayWelcomeScreen();
    else
      displaySensorData(); // display sensor reading if button is clicked
    shouldUpdateScreen = false; 
  }

  delay(50); // reduce flickering
}

void displayWelcomeScreen() {
  M5.Lcd.fillScreen(TFT_BLUE); // bg colour
  M5.Lcd.setTextSize(5);
  M5.Lcd.setCursor(10, 20); 
  M5.Lcd.setTextColor(TFT_WHITE); // fg colour
  M5.Lcd.println("Hello!");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 100);
  M5.Lcd.println("Click button");
  M5.Lcd.setCursor(20, 120); 
  M5.Lcd.println("to view data"); 

  // M5.Lcd.drawJpgFile(SD, "/vecLogo.jpg", 0, 0); // Display welcome image from SD card

}

void displaySensorData() {
  M5.Lcd.fillScreen(TFT_BLACK); 
  M5.Lcd.setTextSize(2); 

  if (currentReading == GYROSCOPE) { // gyroscope data
    
    float gx, gy, gz;
    M5.IMU.getGyroData(&gx, &gy, &gz);
  
    // display data
    M5.Lcd.setTextColor(TFT_YELLOW); 
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Gyroscope (deg/s):");
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print("X: ");
    M5.Lcd.print(gx, 2); // 2 decimal places
    M5.Lcd.setCursor(80, 40);
    M5.Lcd.print("Y: ");
    M5.Lcd.print(gy, 2);
    M5.Lcd.setCursor(150, 40);
    M5.Lcd.print("Z: ");
    M5.Lcd.println(gz, 2);
  }

  else if (currentReading == ACCELEROMETER) { // accelerometer data
    float ax, ay, az;
    M5.IMU.getAccelData(&ax, &ay, &az);
  
    // display data
    M5.Lcd.setTextColor(TFT_PINK); 
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Accelerometer (m/s^2):");
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print("X: ");
    M5.Lcd.print(ax, 2); // 2 decimal places
    M5.Lcd.setCursor(80, 40);
    M5.Lcd.print("Y: ");
    M5.Lcd.print(ay, 2);
    M5.Lcd.setCursor(150, 40);
    M5.Lcd.print("Z: ");
    M5.Lcd.println(az, 2);
  }

  else if (currentReading == BATTERY) {// read battery voltage
    float batteryVoltage = M5.Axp.GetBatVoltage();
  
    // display data
    M5.Lcd.setTextColor(TFT_BLUE);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Battery Voltage (V): ");
    M5.Lcd.print(batteryVoltage, 2);
  }
}
