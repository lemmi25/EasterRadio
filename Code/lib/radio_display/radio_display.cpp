
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


//Volume Triangle Bar
int32_t vol_x1 = 100;
int32_t vol_x2 = 250;
int32_t vol_y2 = 100;
int32_t vol_y1 = 200;

double vol_alpha = 0.0;


void radio_display_init(){

  tft.init();
  tft.setRotation(1);

  cur_menu_state = 10;
  show_menu_1();
}


void radio_display_update(int rotary_number)

{
    //Handle Rotation with Encoder for Menu Item Switching
    /*State Machine*/



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
        //cur_menu_state = 22;
        
        if(cw)
        {
         change_volume_bar(true);
        }
        else
        {
          change_volume_bar(false);
        }
        //show_sub_menu_back();
        break;
      }
      case 22:
      {
        cur_menu_state = 21;
        show_sub_menu_2();
        break;
      }
    }

    Serial.print("cur menu state = ");
    Serial.print(cur_menu_state);
    Serial.print(", rot = ");
    Serial.println(rotary_number);
}

void radio_display_clicked(){

    //Handle Button Clicked for Menu items --> change menu level

  Serial.println("evaluate button clicked... ");
  Serial.print("cur menu state = ");
  Serial.print(cur_menu_state);
   
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
      default: break;
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
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("VOLUME - 2",140,100,4);
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

   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("SETTINGS - 3",150,100,4);
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


  vol_alpha = atan(double((vol_y2-vol_y1))/double(vol_x2-vol_x1));

  tft.drawTriangle(vol_x1, vol_y1, vol_x2, vol_y1, vol_x2, vol_y2, TFT_BLUE);

  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Volume",140,10,1);

}



void change_volume_bar(bool up)
{
  static double cur_volume_x = 75.0;
  int32_t i = 5;

  Serial.println(up);
  if(!up)
  {
    i = i*(-1);
    tft.fillTriangle(vol_x1, vol_y1, vol_x1+cur_volume_x, vol_y1, vol_x1+cur_volume_x, vol_y1+tan(vol_alpha)*(cur_volume_x), TFT_RED);
    tft.drawTriangle(vol_x1, vol_y1, vol_x2, vol_y1, vol_x2, vol_y2, TFT_BLUE);
  }

  cur_volume_x +=i; 
  tft.fillTriangle(vol_x1, vol_y1, vol_x1+cur_volume_x, vol_y1, vol_x1+cur_volume_x, vol_y1+tan(vol_alpha)*(cur_volume_x), TFT_BLUE);

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

