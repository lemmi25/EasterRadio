#include "hm_radio.h"

Hmradio::Hmradio(uint8_t volume){
    _current_volume = volume;
}

uint8_t Hmradio::get_cur_volume(void){
    return _current_volume;
}

void Hmradio::set_cur_volume(uint8_t new_volume){
    _current_volume = new_volume;
}


