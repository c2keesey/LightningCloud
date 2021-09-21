#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "lightning_class.h"

#define MAIN 2
#define AUX 3
#define CROSS 5
#define SMALL 4

const int main_num = 95;
const int aux_num = 27;
const int cross_num = 61;
const int small_num = 38;
CRGB main_S[main_num] = {0};
CRGB aux_S[aux_num] = {0};
CRGB cross_S[cross_num] = {0};
CRGB small_S[small_num] = {0};
CRGB *bolts[] = {main_S, aux_S, cross_S, small_S};
uint8_t default_brightness = 100;
int main_fork_i[] = {39, 56, 62, 85};
int main_fork_len[] = {13, 8, 4, 3};
int aux_fork_i[] = {6, 10};
int aux_fork_len[] = {9, 5};
int cross_fork_i[] = {7, 16, 42};
int cross_fork_len[] = {5, 16, 12};
int small_fork_i[] = {9, 16};
int small_fork_len[] = {12, 5};
const unsigned long FREQUENCY = 20;
Lightning main_bolt(0, main_num, main_fork_i, main_fork_len, 4, FREQUENCY);
Lightning aux_bolt(1, aux_num, aux_fork_i, aux_fork_len, 2, FREQUENCY);
Lightning cross_bolt(2, cross_num, cross_fork_i, cross_fork_len, 3, FREQUENCY);
Lightning small_bolt(3, small_num, small_fork_i, small_fork_len, 2, FREQUENCY);
Lightning lightning_array[] = {main_bolt, aux_bolt, cross_bolt, small_bolt};
unsigned long prev_millis;


void setup() {
  pinMode(MAIN, OUTPUT);
  pinMode(AUX, OUTPUT);
  pinMode(CROSS, OUTPUT);
  pinMode(SMALL, OUTPUT);
  FastLED.addLeds<WS2812, MAIN, GRB>(main_S, main_num);
  FastLED.addLeds<WS2812, AUX, GRB>(aux_S, aux_num);
  FastLED.addLeds<WS2812, CROSS, GRB>(cross_S, cross_num);
  FastLED.addLeds<WS2812, SMALL, GRB>(small_S, small_num);
  FastLED.setBrightness(default_brightness);
  FastLED.setMaxPowerInMilliWatts(8000);
  prev_millis = millis();
}


void loop() {
  if(millis() - prev_millis > random(1000, 3000)) {
    lightning_array[random(0,4)].Draw();
    FastLED.clear();
    prev_millis = millis();
  }
}
