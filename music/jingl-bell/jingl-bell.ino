int Pin_tone = 5;
void setup()
{
pinMode(Pin_tone, OUTPUT);
}
void midi()
{
tone(Pin_tone, 700, 300);
delay(600);
tone(Pin_tone, 700, 300);
delay(600);
tone(Pin_tone, 780, 150);
delay(300);
tone(Pin_tone, 700, 150);
delay(300);
tone(Pin_tone, 625, 450);
delay(600);
tone(Pin_tone, 590, 150);
delay(300);
tone(Pin_tone, 520, 150);
delay(300);
tone(Pin_tone, 460, 450);
delay(600);
tone(Pin_tone, 350, 450);
delay(600);
delay(600);
tone(Pin_tone, 350, 450);
delay(600);
tone(Pin_tone, 460, 450);
delay(600);
tone(Pin_tone, 520, 150);
delay(300);
tone(Pin_tone, 590, 150);
delay(300);
tone(Pin_tone, 625, 450);
delay(600);
tone(Pin_tone, 590, 150);
delay(300);
tone(Pin_tone, 520, 150);
delay(300);
tone(Pin_tone, 700, 1350);
delay(1800);
tone(Pin_tone, 700, 300);
delay(600);
tone(Pin_tone, 700, 300);
delay(600);
tone(Pin_tone, 780, 150);
delay(300);
tone(Pin_tone, 700, 150);
delay(300);
tone(Pin_tone, 625, 450);
delay(600);
tone(Pin_tone, 590, 150);
delay(300);
tone(Pin_tone, 520, 150);
delay(300);
tone(Pin_tone, 460, 450);
delay(600);
tone(Pin_tone, 350, 450);
delay(600);
delay(600);
tone(Pin_tone, 350, 450);
delay(600);
tone(Pin_tone, 625, 450);
delay(600);
tone(Pin_tone, 590, 150);
delay(300);
tone(Pin_tone, 520, 150);
delay(300);
tone(Pin_tone, 700, 450);
delay(600);
tone(Pin_tone, 590, 150);
delay(300);
tone(Pin_tone, 520, 150);
delay(300);
tone(Pin_tone, 460, 1350);
delay(5000);
}

void loop() {
    // Play midi
    midi();
}
