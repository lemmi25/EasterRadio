#include <lvgl.h>
#include <radio_display.h>
#include <radio_encoder.h>

#include <img/mh_radio_img.h>
#include <img/settings_img.h>

#include <hm_radio.h>


#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

static lv_group_t*  g;
static lv_obj_t * tv;

static void focus_cb(lv_group_t * g);

bool my_encoder_read(lv_indev_drv_t * indev, lv_indev_data_t * data);



float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=120, osy=120, omx=120, omy=120, ohx=120, ohy=120;  // Saved H, M, S x & y coords
uint16_t x0=0, x1=0, yy0=0, yy1=0;
uint32_t targetTime = 0;                    // for next 1 second timeout

Hmradio our_radio(50);


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
int32_t vol_x1 = 60;
int32_t vol_x2 = 260;
int32_t vol_y2 = 100;
int32_t vol_y1 = 200;

uint8_t volume_bar_width;

double vol_alpha = 0.0;

void radio_display_encoder(void);
void my_lv_drivers_init(void);
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);


// These two functions make sure that lvgl will work.
void my_lv_drivers_init(){

//Display initialization stuff
  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);
}


/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}





void radio_display_init(){

  //tft.init();
  //tft.setRotation(3);
/*
  tft.setSwapBytes(true);

  tft.fillScreen(TFT_BLUE);
  tft.pushImage(60, 15, mhWidth, mhHeight, mh);

  delay(3000);

  cur_menu_state = 10;
  show_menu_1();*/

  
  lv_init();
  my_lv_drivers_init();
}

  
void lv_radio_encoder(void)
{
    g = lv_group_create();
    lv_group_set_focus_cb(g, focus_cb);

#if LV_EX_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    lv_indev_t * kb_indev = lv_indev_drv_register(&kb_drv);
    lv_indev_set_group(kb_indev, g);
#endif

#if LV_EX_MOUSEWHEEL
    lv_indev_drv_t enc_drv;
    lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read_cb = mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    lv_indev_set_group(enc_indev, g);
#endif

    //my code
  lv_indev_drv_t enc_drv;
  lv_indev_drv_init(&enc_drv); /*Basic initialization*/
  enc_drv.type = LV_INDEV_TYPE_ENCODER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  enc_drv.read_cb = my_encoder_read;
  lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
  lv_indev_set_group(enc_indev, g);

    tv = lv_tabview_create(lv_scr_act(), NULL);


}

void radio_display_update(int rotary_number)
{
    //Handle Rotation with Encoder for Menu Item Switching
    /*State Machine*/
    bool cw = rotary_number < 0 ? 1:0;

    //depending on rotary number, go as many menus further.  
    for (int i = 1; i<abs(rotary_number); i=i+2)
    {
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
          change_volume_bar(cw);
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
  /*
    Serial.print("cur menu state = ");
    Serial.print(cur_menu_state);
    Serial.print(", rot = ");
    Serial.println(rotary_number);*/
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
        cur_menu_state = 20;
        our_radio.set_cur_volume((uint8_t) volume_bar_width/2);
        show_menu_2();
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

void show_display_saver(void){

  tft.fillScreen(TFT_BLACK);
  //tft.pushImage(50, 15, mhWidth, mhHeight, mh);
  tft.drawFloat(89.0, 1, 110, 110);

  tft.drawNumber(our_radio.get_cur_volume(),20, 20, 1);
  tft.drawString("%",60, 20, 1);
}

void show_menu_1(){

  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_WHITE);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Test some print formatting functions
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("1. WELCOME",140,100,4);

}

void show_menu_2(){

  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_WHITE);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Test some print formatting functions
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(3);
  tft.drawCentreString("2. VOLUME",140,100,4);

}


void show_menu_3(){

  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_WHITE);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(3);
  tft.drawCentreString("3. SETTINGS",150,100,4);
  tft.pushImage(150, 150, settWidth, settHeight, settings);

}


void show_sub_menu_1(){
  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Submenu1",140,100,4);

}

void show_sub_menu_2(){
  tft.fillScreen(TFT_WHITE);

  uint8_t cur_volume = our_radio.get_cur_volume();

  Serial.println("Cur Volume:");
  Serial.println(cur_volume);
  volume_bar_width = cur_volume*2;//this is the width of the filled area of the volume triangle. Volume is between 0...100 and the filled area can be between 0...200.

  vol_alpha = atan(double((vol_y2-vol_y1))/double(vol_x2-vol_x1));

  tft.drawTriangle(vol_x1, vol_y1, vol_x2, vol_y1, vol_x2, vol_y2, TFT_BLUE);
  tft.fillTriangle(vol_x1, vol_y1, vol_x1+volume_bar_width, vol_y1, vol_x1+volume_bar_width, vol_y1+tan(vol_alpha)*(volume_bar_width), TFT_BLUE);


  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Volume",140,10,1);
}

void change_volume_bar(bool up)
{
  int32_t i = 20;

  Serial.println("Cur Volume Bar Width:");
  Serial.println(volume_bar_width);
  Serial.println(up);
  if(!up)
  {
    i = i*(-1);
    tft.fillTriangle(vol_x1, vol_y1, vol_x1+volume_bar_width, vol_y1, vol_x1+volume_bar_width, vol_y1+tan(vol_alpha)*(volume_bar_width), TFT_WHITE);
    tft.drawTriangle(vol_x1, vol_y1, vol_x2, vol_y1, vol_x2, vol_y2, TFT_BLUE);
  }
  if(!(volume_bar_width == 0  && i <0) && !(volume_bar_width==200 && i>0)){ //ensure no limit has been reached.
      volume_bar_width +=i; 
      tft.fillTriangle(vol_x1, vol_y1, vol_x1+volume_bar_width, vol_y1, vol_x1+volume_bar_width, vol_y1+tan(vol_alpha)*(volume_bar_width), TFT_BLUE);
  }
}

void show_sub_menu_back(){

  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.drawCentreString("Return",140,100,4);

}



static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}



/* Reading input device (simulated encoder here) */
bool my_encoder_read(lv_indev_drv_t * indev, lv_indev_data_t * data)
{
    encoderData* encoderData = get_encoder_data();
    Serial.print("Read Encoder daata");
    if(encoderData->pushed)
    {
      Serial.println("Clicked, lvgl");
      set_button_clicked_state(false);
      data->state = LV_INDEV_STATE_REL;
        data->key = LV_KEY_ENTER;
        lv_group_send_data(g,data->key);

      encoderData->pushed = false;
    }
    else {
        //data->state = LV_INDEV_STATE_REL;
        
    }
    
    if(encoderData->rotated)
    {
      int encoder_val  = encoderData->roationDelta;
      data->enc_diff = encoder_val;
      Serial.print("Rotated, lvgl:");
      Serial.print(encoder_val);
      encoderData->rotated = false;
      data->key = LV_KEY_NEXT;
    }

    return false;
}


static void focus_cb(lv_group_t * group)
{
    lv_obj_t * obj = lv_group_get_focused(group);
}