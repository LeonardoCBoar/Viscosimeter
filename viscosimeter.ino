const int ECHO_PIN = A1;
const int TRIGGER_PIN = 13;
const double SOUND_SPEED = 0.034029;

const int SPEED_PIN = 6;
const int FORWARD_PIN = 8;
const int BACKWARD_PIN = 9;
const int ANALOG_X_PIN = A0;

const int MOTOR_SPEED = 55;

const int START_BUTTON = 2;
const double HEIGHT_DIFF = 1.5;


void setup() 
{
    Serial.begin(9600);

    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(SPEED_PIN, OUTPUT);
    pinMode(BACKWARD_PIN, OUTPUT);
    pinMode(FORWARD_PIN, OUTPUT);

    pinMode(START_BUTTON, INPUT_PULLUP);
}

double measure_distance()
{
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    return pulseIn(ECHO_PIN, HIGH)/2 * SOUND_SPEED;
}

void start_motor()
{
  digitalWrite(FORWARD_PIN, HIGH);
  digitalWrite(BACKWARD_PIN, LOW);
  analogWrite(SPEED_PIN, MOTOR_SPEED);
}

void stop_motor()
{
    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(BACKWARD_PIN, LOW);
    analogWrite(0, MOTOR_SPEED);
}

void loop() 
{

    if ((digitalRead(START_BUTTON)) == 0) 
    {
        const double start_distance = measure_distance();
        const unsigned long start_time = millis();
        start_motor();

        Serial.print(start_distance);
        Serial.println("cm");

        while(1)
        {
          delay(500);
          const double current_distance = measure_distance();
          const unsigned long current_time = millis();
          Serial.print("Distance:");
          Serial.print(current_distance);
          Serial.print(",Time:");
          Serial.println(current_time);
          if(current_distance <= start_distance - HEIGHT_DIFF)
          {
            stop_motor();
            Serial.println("finished");
            Serial.print("elapsed time: ");
            Serial.print((double)(current_time - start_time) / 1000.0);
            Serial.println("s");
            Serial.print("Moved distance: ");
            Serial.print(current_distance - start_distance);
            Serial.println("cm");
            break;
          }
        }
    }
}
