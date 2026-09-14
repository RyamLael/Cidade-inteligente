#include <Arduino.h>

#include "Config.h"
#include "drivers/Servo.h"

static ServoDriver servo(PIN_SERVO);

void ServoDebugSetup()
{
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("====================");
    Serial.println("TESTE SERVO");
    Serial.println("====================");

    servo.begin();

    Serial.println("Servo inicializado");
}

void ServoDebugLoop()
{
    Serial.println("Angulo: 5");
    servo.setAngle(5);
    delay(1000);

    Serial.println("Angulo: 45");
    servo.setAngle(45);
    delay(1000);

    Serial.println("Angulo: 90");
    servo.setAngle(90);
    delay(1000);

    Serial.println("Angulo: 135");
    servo.setAngle(135);
    delay(1000);

    Serial.println("Angulo: 180");
    servo.setAngle(180);
    delay(1000);

    Serial.println("Abrindo portão...");
    servo.open();
    delay(2000);

    Serial.println("Fechando o portão...");
    servo.close();
    delay(2000);
}