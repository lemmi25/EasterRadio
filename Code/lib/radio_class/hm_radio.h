#include <Arduino.h>

#ifndef HM_RADIO_H


class Hmradio{

    public:
        Hmradio(uint8_t volume);
        
        uint8_t get_cur_volume(void);
        void set_cur_volume(uint8_t new_volume);
        float get_cur_frequency(void);
        void set_cur_frequency(float new_freq);

    private:
        uint8_t _current_volume;   //Current Volume set by user
        float _current_frequence; //Current radio channel set by potentiometer

};


#endif