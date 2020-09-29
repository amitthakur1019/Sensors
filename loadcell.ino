#include <HX711.h>
#define DOUT  A4
#define CLK  A5
HX711 scale(DOUT,CLK);

float weight; 
float calibration_factor = 440; // for me this value works just perfect 419640 
void setup() {
  Serial.begin(2000000);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}
void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
 // weight = scale.get_units(5); 
  Serial.print(scale.get_units(),0);
 Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
//  Serial.print("Kilogram:");
  //Serial.print( weight); 
  //Serial.print(" Kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
  
}
