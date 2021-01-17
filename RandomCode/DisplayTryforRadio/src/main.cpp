#include <lvgl.h>
#include <TFT_eSPI.h>
#include <radio_encoder.h>
#include <lv_demo_keypad_encoder.h>





int rotary_value; 
bool wasButton_clicked = false;
bool wasRotated = false;

unsigned long timeLastActive;
bool saverOff = true;

void task_encoder(void *parameter);
bool my_encoder_read(lv_indev_drv_t * drv, lv_indev_data_t*data);

static void hal_init(void);

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

void btn_event_cb(lv_obj_t * btn, lv_event_t event);


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

/* Reading input device (simulated encoder here) */
bool read_encoder(lv_indev_drv_t * indev, lv_indev_data_t * data)
{
    static int32_t last_diff = 0;
    int32_t diff = 0; /* Dummy - no movement */
    int btn_state = LV_INDEV_STATE_REL; /* Dummy - no press */

    data->enc_diff = diff - last_diff;;
    data->state = btn_state;

    last_diff = diff;

    return false;
}

void setup()
{

    Serial.begin(57600); /* prepare for possible serial debug */

    lv_init();

      /*Initialize the HAL (display, input devices, tick) for LVGL*/
  //hal_init();
    

#if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

    tft.begin(); /* TFT init */
    tft.setRotation(1); /* Landscape orientation */


    rotary_init();
  timeLastActive = millis();

  xTaskCreate(
      task_encoder,  /* Task function. */
      "TaskEncoder", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */


    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    /*Initialize the display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 320;
    disp_drv.ver_res = 240;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button to the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 100, 50);                          /*Set its size*/
    lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/

    lv_demo_keypad_encoder();
}


void loop()
{

  if(wasRotated == false){
    rotary_value  =  rotary_loop();
    wasRotated = true;
  }
  
  if(wasButton_clicked == false){
    wasButton_clicked = get_button_clicked_state();
  }
    lv_task_handler(); /* let the GUI do its work */
    delay(5);
}

void btn_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked\n");
    }
}


//encoder Task
void task_encoder(void *parameter){
 
  for(;;){

    if(wasButton_clicked)
    {
      //radio_display_clicked();
      wasButton_clicked = false;
      rotary_value = 0;
      set_button_clicked_state(false);
      timeLastActive = millis();
      saverOff = true;
      delay(200);
    }
    else if(wasRotated){
      if(rotary_value){
        Serial.println("Display Update");
        //radio_display_update(rotary_value);
        timeLastActive = millis();
        saverOff = true;
        delay(500);
        rotary_value = 0;
      }
      wasRotated = false;
    }
    vTaskDelay(300);
  }
}


/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics
 * library
 */
static void hal_init(void) {
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  //monitor_init();

  /*Create a display buffer*/
  //static lv_disp_buf_t disp_buf1;
  //static lv_color_t buf1_1[LV_HOR_RES_MAX * 120];
  //lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * 120);

  /*Create a display*/
  /*lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  /*disp_drv.buffer = &disp_buf1;
  disp_drv.flush_cb = monitor_flush;
  lv_disp_drv_register(&disp_drv);*/

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  //mouse_init();
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_ENCODER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv.read_cb = my_encoder_read;
  lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);

  /*Set a cursor for the mouse*/
  //LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  //lv_obj_t * cursor_obj = lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
  //lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  //lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/

  /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
   * how much time were elapsed Create an SDL thread to do this*/
  //SDL_CreateThread(tick_thread, "tick", NULL);

  /* Optional:
   * Create a memory monitor task which prints the memory usage in
   * periodically.*/
  //lv_task_create(memory_monitor, 5000, LV_TASK_PRIO_MID, NULL);
}

