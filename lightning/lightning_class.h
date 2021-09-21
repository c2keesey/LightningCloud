#include <Arduino.h>
#include <FastLED.h>

extern CRGB main_S[];
extern CRGB aux_S[];
extern CRGB cross_S[];
extern CRGB small_S[];
extern CRGB *bolts[];
extern uint8_t default_brightness;

class Lightning 
{
    private:
        int num_leds;
        int num_main_leds;
        unsigned long speed; //In LEDs/second
        int current_pos = 0;
        bool done = false;
        int num_forks;
        int *fork_index; //will be in ascending order
        int *fork_lens;
        CRGB *LEDs;
        uint8_t brightness = default_brightness;
        uint8_t hue = 165;
        uint8_t saturation = 255;
    
    public:

        Lightning(int bolt, int num, int *fi, int *fl, int nf, unsigned long sp):
        num_leds(num), num_main_leds(num), fork_index(fi), fork_lens(fl), num_forks(nf), speed(sp)
        {
            for(int i = 0; i < num_forks; i++) {
                num_main_leds = num_main_leds - fork_lens[i];
            }
            LEDs = bolts[bolt];
            
        }

        virtual void Draw()
        {
            unsigned long prev = millis();
            while(current_pos < num_main_leds) {
                if(millis() - prev >= speed) {
                    LEDs[current_pos].setHSV(hue, saturation, brightness);
                    int prev_total = 0;
                    for(int i = 0; i < num_forks; i ++) {
                        if(current_pos >= fork_index[i]) {
                            LEDs[num_main_leds + current_pos + prev_total - fork_index[i]].setHSV(hue, saturation, brightness);
                        }
                        prev_total += fork_lens[i];
                    }
                    current_pos += 1;
                    prev += 50;
                    FastLED.show();
                }
            }
            current_pos = 0;
            done = true;
            Flash();
            Fade();
        }

        int getCurrentPos() {
            return current_pos;
        }

        void Fade() {
            unsigned long prev = millis();
            uint8_t dim = brightness;
            while(dim > 0) {
                if(millis() - prev >= 20) {
                    for(int i = 0; i < num_leds; i++) {
                        LEDs[i] = CHSV(hue, saturation, dim);
                    }
                    FastLED.show();
                    dim = max(dim-1, 0);
                }
            }
        }

        bool isDone() {
            if(done) {
                done = false;
                return !done;
            } else {
                return false;
            }
        }

        void Flash() {
            int flashes = 0;
            int start_brightness = brightness;
            int prev_brightness = brightness;
            brightness += 50;
            unsigned long prev = millis();
            while(flashes < 4) {
                if(millis() - prev >= 30) {
                    for(int i = 0; i < num_leds; i++) {
                        LEDs[i] = CHSV(hue, saturation, brightness);
                    }
                    FastLED.show();
                    flashes += 1;
                    if(prev_brightness < brightness) {
                        prev_brightness = brightness;
                        brightness = start_brightness;
                    } else {
                        brightness += 100;
                    }
                    prev = millis();
                }
            }
            brightness = start_brightness;
        }

        
};
