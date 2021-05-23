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
static lv_obj_t * t1;

static lv_obj_t * win;

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

  tft.init();
  tft.setRotation(3);

  tft.setSwapBytes(true);

  tft.fillScreen(TFT_BLUE);
  tft.pushImage(60, 15, mhWidth, mhHeight, mh); 


  
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


    /*Create a window*/
    win = lv_page_create(lv_scr_act(), NULL);
    //lv_win_set_title(win, "Window title");                        /*Set the title*/
    lv_obj_set_pos(win, LV_DPX(10), LV_DPX(10));
    /*Add control button to the header*/
    //lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);           /*Add close button and use built-in close action*/
    //lv_obj_set_event_cb(close_btn, lv_win_close_event_cb);
    lv_win_add_btn(win, LV_SYMBOL_SETTINGS);        /*Add a setup button*/

    lv_win_set_scrollbar_mode(win, LV_SCRLBAR_MODE_ON);


    //t1 = lv_tabview_add_tab(tv, "Selectors");

    //lv_group_add_obj(g);


    tabview_create(win);

  tv = lv_tabview_create(lv_scr_act(), NULL);

  t1 = lv_tabview_add_tab(tv, "Selectors");

  lv_obj_t * labe;
  labe = lv_label_create(t1, NULL);
  lv_label_set_text(labe, "Short text");

  lv_group_add_obj(g, tv);
  lv_group_add_obj(g, t1);

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


  data->enc_diff = rotary_loop();

  if(get_button_clicked_state()) data->state = LV_INDEV_STATE_PR;
  else data->state = LV_INDEV_STATE_REL;

  return false; /*No buffering now so no more data read*/


  /*
    encoderData* encoderData = get_encoder_data();
    //Serial.print("Read Encoder daata");
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

    return false;*/
}


static void focus_cb(lv_group_t * group)
{
    lv_obj_t * obj = lv_group_get_focused(group);
}