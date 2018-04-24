/*
AUTOR: F.J.Maestre
*/


#define pingPin 8
#define piezpPin 4
#define Pecho 6
#define Ptrig 7

void setup() {
  
  Serial.begin(9600);   // initialize serial communication on 9600 baudios
  pinMode(Pecho, INPUT);
  pinMode(Ptrig, OUTPUT);
  pinMode(13, 1);       // Define pin 13 like OUTPUT to turn on the led
}

void loop() {
  // Initialization of some variables
  long duration, distance, pause;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);

  // The same pin is used to read the signal from the PING)))
  // A HIGH pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
//  pinMode(pingPin, INPUT);
  duration = pulseIn(Pecho, HIGH);

  // convert the time into a distance
  //use this line to get the distance on Cm
  distance = microsecondsToCentimeters(duration);
  //use this line to get the distance on inches
  // distance = microsecondsToInches(duration);

  // Time the sensor will be sounding 
  pause = distance * 10;
  if (pause > 700){
    pause = 700;
  }

  if (distance >= 500 || distance <= 0){  // distance max limit 
    Serial.println("---");                  
  }
  else {
    Serial.print(distance);          // send distance to serial port
    Serial.println("cm");            // change to inches if you need
    digitalWrite(13, 0);             // turn down the led

    digitalWrite(piezpPin, HIGH);    // Active piezo sensor
    delay(pause);                    // during pause ms
  }
  
   if (distance <= 10 && distance >= 1){
    digitalWrite(13, 1);                 // turn on the led if distance is nearer than 10 cm
    Serial.println("Alarm....");     // send "Alarm...." to serial port

//    digitalWrite(piezpPin, HIGH);       // Active piezo sensor
//    delay(pause);                       // during pause ms
  }
  
//  digitalWrite(piezpPin, LOW);          //desactivate piezo sensor
  delay(400);                           // Repetition system time
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
