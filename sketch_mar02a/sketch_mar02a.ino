
// Variables
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int SENSOR_PIN = 0;

int DISPLAY_TIME = 100; // Milliseconds

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Catch value of potentiometer
  float sensorValue;
  sensorValue = analogRead(SENSOR_PIN);

  lightCode(decodeSensor(sensorValue));
  //delay(10);
  
  //fadeEngine();
}

//MY METHODS

// Constantly fades through RGB color spectrum
void fadeEngine() 
{
  int x;
  for(x=0;x<768;x++) 
  {
    lightCode(x);
    delay(10);
  }
}

// varry lighting based on zones
void lightCode(int colorCode)
{
  int redHue;
  int greenHue;
  int blueHue;

  if (colorCode <= 255)          // zone 1
  {
    redHue = 255 - colorCode;    // red goes from on to off
    greenHue = colorCode;        // green goes from off to on
    blueHue = 0;             // blue is always off
  }
  else if (colorCode <= 511)     // zone 2
  {
    redHue = 0;                     // red is always off
    greenHue = 255 - (colorCode - 256); // green on to off
    blueHue = (colorCode - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redHue = (colorCode - 512);         // red off to on
    greenHue = 0;                   // green is always off
    blueHue = 255 - (colorCode - 512);  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(RED_PIN, redHue);
  analogWrite(BLUE_PIN, blueHue);
  analogWrite(GREEN_PIN, greenHue);
  
}

// Takes in the current potentiometer reading and converts it
// to an int that is in the spectrum of the RGB LED hue.
// Returns that int
int decodeSensor(float sensorVal) 
{
  // First we need a local variable to calculate percentage in
  float percent;
  // And the threshold of our RGB LED
  float RGBThresh = 768;
  float sensorThresh = 1023*1.5;
  

  // Now we convert the sensorValue to a percentage
  percent = sensorVal/sensorThresh;

  // And now return the corresponding RGB Hue
  return (RGBThresh*percent);
  
}


