/*
 * Arduino eta joystickarekin pausuz pausuko motorraren norabide eta abiadura kontrola
 * Doako software batetik hartuta
 * https://simple-circuit.com/
 */
 
// Arduinoa pausuz pausuko motorraren barnean sartzen da
#include <Stepper.h>
 
// Pausu kopurua definitu
#define STEPS 32
 
// Pausuz pausuko motorraren pinak definitu
#define IN1  12
#define IN2  11
#define IN3  10
#define IN4   9
 
// Liburutegia pausuz pausu hasi
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
 
// Joystick-aren irteera arduino A0-ri konektatuta dago
#define joystick  A0
int led1 = 4; // LED-era konektatuta dago pin-a
int led2 = 5; // LED-era konektatuta dago pin-a
 
void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT); // Irteera gisa deklaratu LED-a
  pinMode(led2, OUTPUT); // Irteera gisa deklaratu LED-a
}
 
void loop()
{
  // Potentziometroaren balio analogikoa irakurri
  int val = analogRead(joystick);
  Serial.print("X ardatza:   ");
  Serial.println(val);
 
  // Joystick-a erdian badago ===> motorra geldiarazi
  if(  (val > 500) && (val < 523) )
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    digitalWrite (led1, LOW);
    digitalWrite (led2, LOW);
  }
 
  else
  {
    // Motorra lehenengo norabidean mugitu
    while (val >= 523)
    {
      // 5 eta 500 bira/min bitarteko abiadura mapeatu
      int speed_ = map(val, 523, 1023, 5, 500);
      // Motorraren abiadura ezarri
      stepper.setSpeed(speed_);
 
      // Motorra mugitu (1 step)
      stepper.step(1);
 
      val = analogRead(joystick);
       Serial.print("X ardatza:   ");
       Serial.println(val);

       digitalWrite (led1, HIGH);
}

    // Motorra beste norabidean mugitu
    while (val <= 500)
    {
      // 5 eta 500 bira/min bitarteko abiadura mapeatu
      int speed_ = map(val, 500, 0, 5, 500);
      // Motorraren abiadura ezarri
      stepper.setSpeed(speed_);
 
      // Motorra mugitu (1 step)
      stepper.step(-1);
 
      val = analogRead(joystick);
     Serial.print("X ardatza:   ");
     Serial.println(val);

     digitalWrite (led2, HIGH);
    }
 
  }
 
}
