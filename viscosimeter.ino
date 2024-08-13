const int MAX_SPEED = 105;
const int SPEED_PIN = 6;
const int FORWARD_PIN = 8;
const int BACKWARD_PIN = 9;

const int ANALOG_X_PIN = A1;

const int ANALOG_MAX = 1024;
const int ANALOG_HALF = ANALOG_MAX / 2;
const int INPUT_THRESOLD = 10;
const int INPUT_RANGE = ANALOG_HALF - INPUT_THRESOLD;
const int FORWARD_THRESOLD  = ANALOG_HALF + INPUT_THRESOLD;
const int BACKWARD_THRESOLD = ANALOG_HALF - INPUT_THRESOLD;


void setup() 
{
    Serial.begin(9600);

    pinMode(SPEED_PIN, OUTPUT);
    pinMode(BACKWARD_PIN, OUTPUT);
    pinMode(FORWARD_PIN, OUTPUT);
}

void loop() 
{

    const int analog_read_x = analogRead(ANALOG_X_PIN);
    double speed_factor = 0.0;

    if(analog_read_x < BACKWARD_THRESOLD)
    {
        digitalWrite(FORWARD_PIN, HIGH);
        digitalWrite(BACKWARD_PIN, LOW);
        speed_factor = ((double) BACKWARD_THRESOLD - analog_read_x) / INPUT_RANGE;
    }
    else if(analog_read_x > FORWARD_THRESOLD)
    {
        digitalWrite(FORWARD_PIN, LOW);
        digitalWrite(BACKWARD_PIN, HIGH);
        speed_factor = ((double) analog_read_x - FORWARD_THRESOLD) / INPUT_RANGE;
    }
    else
    {
        digitalWrite(FORWARD_PIN, LOW);
        digitalWrite(BACKWARD_PIN, LOW);
    }

    Serial.print("Input:");
    Serial.print(analog_read_x);
    Serial.print(",");
    Serial.print("Speed:");
    Serial.println(speed_factor * 1000);

    analogWrite(SPEED_PIN, speed_factor * MAX_SPEED);
}
