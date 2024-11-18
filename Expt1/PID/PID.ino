const int analogInPin = A1;
const int analogOutPin1 = 12;
const int analogOutPin2 = 10;

int sensorValue = 0;
int outputValue1 = 0;
int outputValue2 = 0;
int initialValue = 0;
int finalValue = 0;
long long int i = 0;
int integral = 0;
int ind = 1;
int prevError = 0;
int error = 0;
int delta = 0;

float kp = 30;
float ki = 0.0001;
float kd = 10;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(analogInPin);
  if(i == 0)
  {
    initialValue = sensorValue;
    
    if(initialValue < 512)
      finalValue = initialValue + 540;
    else
      finalValue = initialValue - 540;
    Serial.println(initialValue);
  }
  
  // pid below
  prevError = error; // update previous error with the previous value of error
  error = finalValue - sensorValue; // calculate the new error
  integral += error; // integral from 0 to current t is just summation
  if(i!=0)
    delta = error - prevError; // differential term

  if(sensorValue < finalValue)
  {
    outputValue1 = 0;
    outputValue2 = min(kp*error + ki*integral + kd*delta, 255);
  }
  
  else
  {
    outputValue1 = min(-kp*error - ki*integral - kd*delta, 255);
    outputValue2 = 0;
  }
  //pid over

  analogWrite(analogOutPin1, outputValue1);
  analogWrite(analogOutPin2, outputValue2);
  if(i < 300)
    Serial.println(sensorValue);

  i++;
