const int green_led_pin = 11;
 
void setup() {
} 

void cosine_pulse(int pin, float time_step, int pause) {
  for(float t = 0; t < 2*PI; t += time_step) {
    float value = (cos(t - PI)*0.5+0.5)*255;
    analogWrite(pin, value);
    delay(pause);
    }
  }
 
void loop() {
  cosine_pulse(green_led_pin, 0.0025, 1);
  }
