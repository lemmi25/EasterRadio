#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library



void radio_display_init(void);
void radio_display_update(int rotary_number);
void radio_display_clicked(void);

void show_display_saver(void);

void show_menu_1(void);
void show_menu_2(void);
void show_menu_3(void);

void show_sub_menu_1(void);

void show_sub_menu_2(void);

void show_sub_menu_back(void);

void change_volume_bar(bool up);