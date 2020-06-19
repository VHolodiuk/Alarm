int Pin_tone = 5;
void setup()
{
  pinMode(Pin_tone, OUTPUT);
}
void loop()
{
  tone(Pin_tone, 440, 250);
  delay(250);
  tone(Pin_tone, 165, 250);
  delay(250);
  tone(Pin_tone, 440, 250);
  delay(250);
  delay(250);

  tone(Pin_tone, 440, 250);
  delay(250);
  tone(Pin_tone, 165, 250);
  delay(250);
  tone(Pin_tone, 440, 250);
  delay(250);
  delay(250);

  tone(Pin_tone, 330, 125);
  delay(125);
  tone(Pin_tone, 294, 125);
  delay(125);
  tone(Pin_tone, 262, 125);
  delay(124);
  tone(Pin_tone, 494, 125);
  delay(125);
  tone(Pin_tone, 440, 125);
  delay(125);
  tone(Pin_tone, 494, 125);
  delay(125);
  tone(Pin_tone, 262, 125);
  delay(125);
  tone(Pin_tone, 294, 125);
  delay(125);

  tone(Pin_tone, 330, 250);
  delay(250);
  tone(Pin_tone, 165, 250);
  delay(250);
  tone(Pin_tone, 440, 250);
  delay(250);
  delay(250);
  delay(3000);
}
