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

lv_obj_t *tileview;
static lv_obj_t * win;


struct {
    lv_obj_t * tile_vol;
    lv_obj_t * tile_sett;
    lv_obj_t * tile_wifi;
}tile_objs;

LV_IMG_DECLARE(wifi_sign);
LV_IMG_DECLARE(volume_sign);

static void focus_cb(lv_group_t * g);
static void tv_event_cb(lv_obj_t * tv, lv_event_t e);

static void tileview_create(lv_obj_t * parent);

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
    //lv_group_set_focus_cb(g, focus_cb);

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


  tileview_create(win);


}



static void btn_vol_event_cb(lv_obj_t * btn, lv_event_t event)
{

    Serial.println("Im in vol event!");
    Serial.println(event);
    if(event == LV_EVENT_KEY) {

        //vol_msgbox_create();
    }
}

static void btn_sett_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_KEY) {

        //sett_msgbox_create();
    }
}


static void tileview_create(lv_obj_t * parent)
{

    static lv_point_t valid_pos[] = {{0,0}, {1, 0}, {2,0}};
    tileview = lv_tileview_create(lv_scr_act(), NULL);
    lv_tileview_set_valid_positions(tileview, valid_pos, 3);
    lv_tileview_set_edge_flash(tileview, true);

    lv_page_set_scrlbar_mode(tileview, LV_SCROLLBAR_MODE_ON);
    lv_tileview_set_tile_act(tileview, 0, 0, LV_ANIM_ON);
    
    //lv_group_add_obj(g, tileview);
    //lv_obj_set_event_cb(tileview, tv_event_cb);

    tile_objs.tile_vol = lv_obj_create(tileview, NULL);
    lv_obj_set_size(tile_objs.tile_vol, 100, 100);
    lv_obj_align(tile_objs.tile_vol, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    lv_tileview_add_element(tileview, tile_objs.tile_vol);
    //lv_obj_set_event_cb(tile_objs.tile_vol, btn_vol_event_cb);

    /* Now create the actual image */
    lv_obj_t * img3 = lv_img_create(tile_objs.tile_vol, NULL);
    lv_img_set_src(img3, &volume_sign);
    //lv_obj_set_size(img3, 300, 300);   
    lv_obj_align(img3, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_pivot(img3, 50, 50); 

    lv_group_add_obj(g, tile_objs.tile_vol);
/*
    lv_anim_t a3;
    lv_anim_init(&a3);
    lv_anim_set_var(&a3, img3);
    lv_anim_set_exec_cb(&a3, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a3, 140, 150);
    lv_anim_set_playback_time(&a3, 500);
    lv_anim_set_repeat_count(&a3, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a3);

*/
    tile_objs.tile_sett = lv_obj_create(tileview, NULL);
    lv_obj_set_size(tile_objs.tile_sett, 100, 100);
    lv_obj_align(tile_objs.tile_sett,  tile_objs.tile_vol, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_tileview_add_element(tileview, tile_objs.tile_sett);
    lv_obj_set_event_cb(tile_objs.tile_sett, btn_sett_event_cb); 

    /*Tile2: just a label*/
    //label = lv_label_create(btn_sett, NULL);
    /*
    lv_label_set_text(label, "Settings");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);*/

    /* Now create the actual image */
    // lv_obj_t * img = lv_img_create(tile_objs.tile_sett, NULL);
    // lv_img_set_src(img, &img_cogwheel_argb);
    // lv_obj_align(img, NULL, LV_ALIGN_CENTfER, 0, 0);
    // lv_img_set_pivot(img, 50, 50);    /*Rotate around the top left corner*/

    lv_group_add_obj(g, tile_objs.tile_sett);
/*
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_angle);
    lv_anim_set_values(&a, 0, 3600);
    lv_anim_set_time(&a, 8000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);*/
/*
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a, 128, 256);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_start(&a);*/

   
    tile_objs.tile_wifi = lv_obj_create(tileview, NULL);
    lv_obj_set_size(tile_objs.tile_wifi, 100, 100);
    lv_obj_align(tile_objs.tile_wifi, tile_objs.tile_sett, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_tileview_add_element(tileview, tile_objs.tile_wifi);

    /* Now create the actual image */
    lv_obj_t * img2 = lv_img_create(tile_objs.tile_wifi, NULL);
    lv_img_set_src(img2, &wifi_sign);
    lv_obj_align(img2, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_pivot(img2, 50, 50);    /*Rotate around the top left corner*/

    lv_group_add_obj(g, tile_objs.tile_wifi);
/*
    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, img2);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a2, 232, 248);
    lv_anim_set_playback_time(&a2, 500);
    lv_anim_set_repeat_count(&a2, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a2);

*/

    
    /*
   selector_objs.btn_vol = lv_btn_create(parent, NULL);
   lv_obj_set_pos(selector_objs.btn_vol, 10, 10);                            //Set its position
    lv_obj_set_size(selector_objs.btn_vol, 200, 90);                          //Set its size
    lv_obj_set_event_cb(selector_objs.btn_vol, btn_vol_event_cb);             //Assign a callback to the button

   lv_obj_t * label = lv_label_create(selector_objs.btn_vol, NULL);
   lv_label_set_text(label, "Volume");
   

    selector_objs.btn_sett = lv_btn_create(parent, NULL);
    lv_obj_set_pos(selector_objs.btn_sett, 10, 10);                            //Set its position
    lv_obj_set_size(selector_objs.btn_sett, 200, 90);                          //Set its size
    lv_obj_set_event_cb(selector_objs.btn_sett, btn_sett_event_cb);            //Assign a callback to the button


   lv_obj_t * label2 = lv_label_create(selector_objs.btn_sett, NULL);
   lv_label_set_text(label2, "Settings");*/

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


    static int old_enc_val = 0;
    int encoderd = rotary_loop();

    //Serial.print("Read Encoder daata");
    if(get_button_clicked_state())
    {
      Serial.println("Clicked, lvgl");
      set_button_clicked_state(false);
      data->state = LV_INDEV_STATE_REL;
        data->key = LV_KEY_ENTER;
        lv_group_send_data(g,data->key);
    }
    else {
        //data->state = LV_INDEV_STATE_REL;
    }
    
    if(encoderd)
    {
      // int encoder_val  = encoderData->roationDelta;
      data->enc_diff = encoderd-old_enc_val;
      Serial.print("Rotated, lvgl:");
      Serial.print(encoderd);
    
      if((encoderd-old_enc_val) > 0){
        Serial.println("left");
        //data->key = LV_KEY_NEXT;
        
      }
      else 
      {
        Serial.println("right");
        //data->key = LV_KEY_PREV;
      }

      old_enc_val = encoderd;
        //data->key = LV_KEY_NEXT;
    }

    return false;
}
/*


void tv_event_cb(lv_obj_t * tv, lv_event_t e)
{
    Serial.println("tv event fist");
    lv_coord_t x, y;
    lv_tileview_get_tile_act(tileview, &x, &y);

    if(e == LV_EVENT_VALUE_CHANGED || e == LV_EVENT_REFRESH) {
      Serial.println("tv event");

    }

}

static void focus_cb(lv_group_t * group)
{
    lv_obj_t * obj = lv_group_get_focused(group);
    if(obj != tileview) {
      lv_coord_t x, y;
      lv_tileview_get_tile_act(tileview, &x, &y);
        switch(x) {
        case 0:
            //lv_page_focus(tileview, tile_objs.tile_sett, LV_ANIM_ON);
            //erial.println("fist tile");
            break;
        case 1:
            //lv_page_focus(tileview, tile_objs.tile_vol, LV_ANIM_ON);
            //Serial.println("2nd tile");
            break;
        case 2:
            //lv_page_focus(tileview, tile_objs.tile_wifi, LV_ANIM_ON);
            //Serial.println("3rd tile");
            break;
        }
    }
}

*/