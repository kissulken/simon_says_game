#include <TrueRandom.h>
#define start_led 3
#define start_button 6
#define led_count 3
#define buzzer 13
#define level 20
bool done;
int current_level = 3;
int herz[led_count];
int sequence[level];

void setup()
{
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    for (int i = 0; i < led_count; i++)
    {
        pinMode(i + start_led, OUTPUT);
        pinMode(i + start_button, INPUT);
        herz[i] = i * 100 + 200;
    }
    new_game();
}

void loop()
{
    show_seq();
    user_input();
}

void new_game()
{
    for (int i = 0; i < level; i++)
    {
        sequence[i] = TrueRandom.random(0, led_count);
        Serial.println(sequence[i]);
    }
}

void show_seq()
{
    for (int i = 0; i < current_level; i++)
    {
        digitalWrite(sequence[i] + start_led, HIGH);
        signals(sequence[i]);
        delay(500);
        digitalWrite(sequence[i] + start_led, LOW);
        noTone(buzzer);
    }
    done = false;
}

void user_input()
{
    int current_position = 0;
    while (done == false)
    {
        for (int i = 0; i < led_count; i++)
        {
            if (digitalRead(i + start_button))
            {
                if (i == sequence[current_position])
                {
                    current_position++;
                    signals(i);
                    if (current_position == current_level)
                    {
                        done = true;
                        victory();
                    }
                }
                else
                {
                    lose();
                    done = true;
                }
            }
        }
    }
}

void signals(int pos)
{
    digitalWrite(pos + start_led, HIGH);
    tone(buzzer, herz[pos]);
    delay(500);
    digitalWrite(pos + start_led, LOW);
    noTone(buzzer);
}

void victory()
{
    current_level++;
    for (int i = 0; i < led_count; i++)
    {
        digitalWrite(i + start_led, HIGH);
        delay(50);
    }
    tone(buzzer, 500);
    delay(150);
    tone(buzzer, 600);
    delay(150);
    tone(buzzer, 700);
    delay(150);
    noTone(buzzer);
    delay(500);
    for (int i = 0; i < led_count; i++)
    {
        digitalWrite(i + start_led, LOW);
    }
}

void lose()
{
    current_level = 3;
    for (int i = 0; i < led_count; i++)
    {
        digitalWrite(i + start_led, HIGH);
    }
    tone(buzzer, 100);
    delay(100);
    tone(buzzer, 200);
    delay(200);
    noTone(buzzer);
    delay(300);
    for (int i = 0; i < led_count; i++)
    {
        digitalWrite(i + start_led, LOW);
    }
    new_game();
}
