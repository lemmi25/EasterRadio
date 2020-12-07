
#include <radio_display.h>

#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=120, osy=120, omx=120, omy=120, ohx=120, ohy=120;  // Saved H, M, S x & y coords
uint16_t x0=0, x1=0, yy0=0, yy1=0;
uint32_t targetTime = 0;                    // for next 1 second timeout


static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x
uint8_t hh=conv2d(__TIME__), mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);  // Get H, M, S from compile time
//static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x
//uint8_t hh=conv2d(__TIME__), mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);  // Get H, M, S from compile time

boolean initial = 1;

int cur_state = 0;
int cur_substate = 0;
int cur_sub_level = 0;

int cur_menu_state = 10;

void radio_display_init(){

  tft.init();
  tft.setRotation(1);
  //tft.fillScreen(TFT_GREEN);

  //show_menu_1();
  /*
  //tft.fillScreen(TFT_BLACK);
  //tft.fillScreen(TFT_RED);
  
  //tft.fillScreen(TFT_BLU#define TFT_GREY 0x5AEBE);
  //tft.fillScreen(TFT_BLACK);
  tft.fillScreen(TFT_GREY);
  
  tft.setTextColor(TFT_WHITE, TFT_GREY);  // Adding a background colour erases previous text automatically
  
  // Draw clock face
  tft.fillCircle(120, 120, 118, TFT_GREEN);
  tft.fillCircle(120, 120, 110, TFT_BLACK);

  // Draw 12 lines
  for(int i = 0; i<360; i+= 30) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*114+120;
    yy0 = sy*114+120;
    x1 = sx*100+120;
    yy1 = sy*100+120;

    tft.drawLine(x0, yy0, x1, yy1, TFT_GREEN);
  }

  // Draw 60 dots
  for(int i = 0; i<360; i+= 6) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*102+120;
    yy0 = sy*102+120;
    // Draw minute markers
    tft.drawPixel(x0, yy0, TFT_WHITE);
    
    // Draw main quadrant dots
    if(i==0 || i==180) tft.fillCircle(x0, yy0, 2, TFT_WHITE);
    if(i==90 || i==270) tft.fillCircle(x0, yy0, 2, TFT_WHITE);
  }

  tft.fillCircle(120, 121, 3, TFT_WHITE);

  // Draw text at position 120,260 using fonts 4
  // Only font numbers 2,4,6,7 are valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : . - a p m
  // Font 7 is a 7 segment font and only contains characters [space] 0 1 2 3 4 5 6 7 8 9 : .
  tft.drawCentreString("Time flies",120,260,4);

  targetTime = millis() + 1000; 
*/
}


void radio_display_update(int rotary_number)

{
    //Handle Rotation with Encoder for Menu Item Switching
    /*State Machine*/

    Serial.print("cur menu state = ");
    Serial.print(cur_menu_state);
    Serial.print(", rot = ");
    Serial.println(rotary_number);

    bool cw = rotary_number > 0 ? 1:0;

    switch (cur_menu_state)
    {
      case 10:
      {
        if(cw)
        {
          cur_menu_state = 20;
          show_menu_2();
        }
        else
        {
          cur_menu_state = 30;
          show_menu_3(); 
        }
        break;
      }
      case 20:
      {
        if(cw)
        {
          cur_menu_state = 30;
          show_menu_3();
        }
        else
        {
          cur_menu_state = 10;
          show_menu_1();
        }
        break;
      }
      case 30:
      {
        if(cw)
        {
          cur_menu_state = 10;
          show_menu_1();
        }
        else
        {
          cur_menu_state = 20;
          show_menu_2();
        }
        break;
      }
      case 11:
      {
        cur_menu_state = 12;
        show_sub_menu_back();
        break;
      }
      case 12:
      {
        cur_menu_state = 11;
        show_sub_menu_1();
        break;
      }
      case 21:
      {
        cur_menu_state = 22;
        show_sub_menu_back();
        break;
      }
      case 22:
      {
        cur_menu_state = 21;
        show_sub_menu_2();
        break;
      }
    }
}

void radio_display_clicked(){

    //Handle Button Clicked for Menu items --> change menu level

   Serial.println("evaluate button clicked... ");
   
   
  switch (cur_menu_state)
    {
      case 10:
      {
        cur_menu_state = 11;
        show_sub_menu_1();
        break;
      }
      case 20:
      {
        cur_menu_state = 21;
        show_sub_menu_2();

        break;
      }
      case 30:
      {
        break;
      }
      case 11:
      {
        break;
      }
      case 12:
      {
        cur_menu_state = 10;
        show_menu_1();
        break;
      }
      case 21:
      {
        break;
      }
      case 22:
      {
        cur_menu_state = 20;
        show_menu_2();
        break;
      }
    }
}


void show_menu_1(){

  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_GREY);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Test some print formatting functions
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("WELCOME - 1",140,100,4);
  //tft.print("R = "); tft.println(rotary_number);           // Print floating point number
  //tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
  //tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
  //delay(5000);

}

void show_menu_2(){

  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_RED);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Test some print formatting functions
  float fnumber = 123.45;
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("MORITZ - 2",130,100,4);
  //tft.print("R = "); tft.println(fnumber);           // Print floating point number
  //tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
  //tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
  //delay(5000);
    
}


void show_menu_3(){

  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_RED);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Test some print formatting functions
  float fnumber = 123.45;
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_DARKGREEN);    tft.setTextFont(4);
  tft.drawCentreString("SETTINGS - 3",130,100,4);
  //tft.print("R = "); tft.println(fnumber);           // Print floating point number
  //tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
  //tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
  //delay(5000);
    
}





void show_sub_menu_1(){
  tft.fillScreen(TFT_RED);

  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Submenu1",140,100,4);

}

void show_sub_menu_2(){
  tft.fillScreen(TFT_RED);

  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Submenu2",140,100,4);

}

void show_sub_menu_back(){
      tft.fillScreen(TFT_RED);

  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Return",140,100,4);

}



static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

