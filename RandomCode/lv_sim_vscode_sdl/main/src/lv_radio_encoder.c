/**
 * @file lv_radio_encoder.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../lv_examples/src/lv_examples.h"
#include "lv_radio_encoder.h"
#if LV_EX_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif
#if LV_EX_MOUSEWHEEL
#include "lv_drivers/indev/mousewheel.h"
#endif

#if LV_USE_RADIO_ENCODER

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void selectors_create(lv_obj_t * parent);
static void text_input_create(lv_obj_t * parent);
static void vol_msgbox_create(void);
static void sett_msgbox_create(void);
static void Wifi_msgbox_create(void);

static void focus_cb(lv_group_t * g);
static void vol_msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e);
static void sett_msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e);
static void tv_event_cb(lv_obj_t * ta, lv_event_t e);
static void ta_event_cb(lv_obj_t * ta, lv_event_t e);
static void kb_event_cb(lv_obj_t * kb, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t*  g;
static lv_obj_t * tv;
static lv_obj_t * t1;
static lv_obj_t * t2;
static lv_obj_t * t3;

struct {
    lv_obj_t * btn_vol;
    lv_obj_t * btn_sett;
    lv_obj_t * cb;
    lv_obj_t * slider;
    lv_obj_t * sw;
    lv_obj_t * spinbox;
    lv_obj_t * dropdown;
    lv_obj_t * roller;
    lv_obj_t * list;
}selector_objs;

struct {
    lv_obj_t * ta1;
    lv_obj_t * ta2;
    lv_obj_t * kb;
}textinput_objs;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

LV_EVENT_CB_DECLARE(dd_enc)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
        /*printf("chg\n");*/
    }
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

    tv = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(tv, tv_event_cb);

    t1 = lv_tabview_add_tab(tv, "Selectors");
    //t2 = lv_tabview_add_tab(tv, "Text input");

    lv_group_add_obj(g, tv);

    selectors_create(t1);
    //text_input_create(t2);

    //msgbox_create();
}



static void btn_vol_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {

        vol_msgbox_create();
    }
}

static void btn_sett_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {

        sett_msgbox_create();
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_MID);

   selector_objs.btn_vol = lv_btn_create(parent, NULL);
   lv_obj_set_pos(selector_objs.btn_vol, 10, 10);                            /*Set its position*/
    lv_obj_set_size(selector_objs.btn_vol, 200, 90);                          /*Set its size*/
    lv_obj_set_event_cb(selector_objs.btn_vol, btn_vol_event_cb);                 /*Assign a callback to the button*/

   lv_obj_t * label = lv_label_create(selector_objs.btn_vol, NULL);
   lv_label_set_text(label, "Volume");
   

   selector_objs.btn_sett = lv_btn_create(parent, NULL);
     lv_obj_set_pos(selector_objs.btn_sett, 10, 10);                            /*Set its position*/
    lv_obj_set_size(selector_objs.btn_sett, 200, 90);                          /*Set its size*/
    lv_obj_set_event_cb(selector_objs.btn_sett, btn_sett_event_cb);                 /*Assign a callback to the button*/


   lv_obj_t * label2 = lv_label_create(selector_objs.btn_sett, NULL);
   lv_label_set_text(label2, "Settings");
}


static void text_input_create(lv_obj_t * parent)
{
    textinput_objs.ta1 = lv_textarea_create(parent, NULL);
    lv_obj_set_event_cb(textinput_objs.ta1, ta_event_cb);
    lv_obj_align(textinput_objs.ta1, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 20);
    lv_textarea_set_one_line(textinput_objs.ta1, true);
    lv_textarea_set_cursor_hidden(textinput_objs.ta1, true);
    lv_textarea_set_placeholder_text(textinput_objs.ta1, "Type something");
    lv_textarea_set_text(textinput_objs.ta1, "");

    textinput_objs.ta2 = lv_textarea_create(parent, textinput_objs.ta1);
    lv_obj_align(textinput_objs.ta2, textinput_objs.ta1, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 20);

    textinput_objs.kb = NULL;
}


static lv_obj_t * label2;



static void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        /*Refresh the text*/
        lv_label_set_text_fmt(label2, "%d", lv_slider_get_value(slider));
    }
}


static void vol_msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e)
{
    if(e == LV_EVENT_CLICKED) {
        uint16_t b = lv_msgbox_get_active_btn(msgbox);
        if(b == 0 || b == 1) {
            lv_obj_del(msgbox);
            lv_obj_reset_style_list(lv_layer_top(), LV_OBJ_PART_MAIN);
            lv_obj_set_click(lv_layer_top(), false);
            lv_event_send(tv, LV_EVENT_REFRESH, NULL);
        }
    }
}


static void sett_msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e)
{
    if(e == LV_EVENT_CLICKED) {
        uint16_t b = lv_msgbox_get_active_btn(msgbox);
        if(b == 0){
            /*Refresh the text*/
            lv_label_set_text_fmt(label2, "%d", 1);
            Wifi_msgbox_create();
        }
        else if (b == 1) {
           /*Refresh the text*/
            lv_label_set_text_fmt(label2, "%d", 2);        
        }  
        else
        {
           lv_obj_del(msgbox);
            lv_obj_reset_style_list(lv_layer_top(), LV_OBJ_PART_MAIN);
            lv_obj_set_click(lv_layer_top(), false);
            lv_event_send(tv, LV_EVENT_REFRESH, NULL);
 
        }
    }
}


static void vol_msgbox_create(void)
{

    lv_obj_t * mbox = lv_msgbox_create(lv_layer_top(), NULL);
    lv_msgbox_set_text(mbox, "Volume Setting");
    lv_obj_set_event_cb(mbox, vol_msgbox_event_cb);
    lv_group_add_obj(g, mbox);
    lv_group_focus_obj(mbox);
    #if LV_EX_MOUSEWHEEL
        lv_group_set_editing(g, true);
    #endif
        lv_group_focus_freeze(g, true);

    /* Create a slider in the center of the display */
    lv_obj_t * slider = lv_slider_create(mbox, NULL);
    lv_obj_set_width(slider, 200);                        /*Set the width*/
    lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);    /*Align to the center of the parent (screen)*/
    lv_obj_set_event_cb(slider, slider_event_cb);         /*Assign an event function*/

    /* Create a label below the slider */
    label2 = lv_label_create(mbox, NULL);
    lv_label_set_text(label2, "0");
    lv_obj_set_auto_realign(slider, true);                          /*To keep center alignment when the width of the text changes*/
    lv_obj_align(label2, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);    /*Align below the slider*/

    static const char * btns[] = {"Ok", "Cancel", ""};
    lv_msgbox_add_btns(mbox, btns);
    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_local_bg_opa(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_70);
    lv_obj_set_style_local_bg_color(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_set_click(lv_layer_top(), true);
}

static void sett_msgbox_create(void)
{

    lv_obj_t * mbox = lv_msgbox_create(lv_layer_top(), NULL);
    lv_msgbox_set_text(mbox, "Settings");
    lv_obj_set_event_cb(mbox, sett_msgbox_event_cb);
    lv_group_add_obj(g, mbox);
    lv_group_focus_obj(mbox);
    #if LV_EX_MOUSEWHEEL
        lv_group_set_editing(g, true);
    #endif
        lv_group_focus_freeze(g, true);

    label2 = lv_label_create(mbox, NULL);
    lv_label_set_text(label2, "0");

    static const char * btns[] = {"WIFI", "THEME", "Cancel", ""};
    lv_msgbox_add_btns(mbox, btns);
    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_local_bg_opa(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_70);
    lv_obj_set_style_local_bg_color(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_set_click(lv_layer_top(), true);
}



static void Wifi_msgbox_create(void)
{

    
    lv_obj_t * mbox = lv_win_create(lv_layer_top(), NULL);
    //lv_msgbox_set_text(mbox, "Wifi");
    lv_obj_set_event_cb(mbox, sett_msgbox_event_cb);
    lv_group_add_obj(g, mbox);
    lv_group_focus_obj(mbox);
    #if LV_EX_MOUSEWHEEL
        lv_group_set_editing(g, true);
    #endif
        lv_group_focus_freeze(g, true);

    label2 = lv_label_create(mbox, NULL);
    lv_label_set_text(label2, "0");

    lv_table_create(lv_layer_top(), NULL);
    text_input_create(lv_layer_top());
/*
    static const char * btns[] = {"WIFI", "THEME", "Cancel", ""};
    lv_msgbox_add_btns(mbox, btns);
    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);*/

    lv_obj_set_style_local_bg_opa(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_70);
    lv_obj_set_style_local_bg_color(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_set_click(lv_layer_top(), true);
}

static void focus_cb(lv_group_t * group)
{
    lv_obj_t * obj = lv_group_get_focused(group);
    if(obj != tv) {
        uint16_t tab = lv_tabview_get_tab_act(tv);
        switch(tab) {
        case 0:
            lv_page_focus(t1, obj, LV_ANIM_ON);
            break;
        case 1:
            lv_page_focus(t2, obj, LV_ANIM_ON);
            break;
        case 2:
            lv_page_focus(t3, obj, LV_ANIM_ON);
            break;
        }
    }
}

static void tv_event_cb(lv_obj_t * ta, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED || e == LV_EVENT_REFRESH) {
        lv_group_remove_all_objs(g);

        uint16_t tab = lv_tabview_get_tab_act(tv);
        size_t size = 0;
        lv_obj_t ** objs = NULL;
        if(tab == 0) {
            size = sizeof(selector_objs);
            objs = (lv_obj_t**) &selector_objs;
        }
        else if(tab == 1) {
            size = sizeof(textinput_objs);
            objs = (lv_obj_t**) &textinput_objs;
        }

        lv_group_add_obj(g, tv);

        uint32_t i;
        for(i = 0; i < size / sizeof(lv_obj_t *); i++) {
            if(objs[i] == NULL) continue;
            lv_group_add_obj(g, objs[i]);
        }

    }

}

static void ta_event_cb(lv_obj_t * ta, lv_event_t e)
{
    /*Create a virtual keyboard for the encoders*/
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    if(e == LV_EVENT_FOCUSED) {
        lv_textarea_set_cursor_hidden(ta, false);
        if(lv_group_get_editing(g)) {
            if(textinput_objs.kb == NULL) {
                textinput_objs.kb = lv_keyboard_create(lv_scr_act(), NULL);
                lv_group_add_obj(g, textinput_objs.kb);
                lv_obj_set_event_cb(textinput_objs.kb, kb_event_cb);
                lv_obj_set_height(tv, LV_VER_RES - lv_obj_get_height(textinput_objs.kb));
            }

            lv_keyboard_set_textarea(textinput_objs.kb, ta);
            lv_group_focus_obj(textinput_objs.kb);
            lv_group_set_editing(g, true);
            lv_page_focus(t2, lv_textarea_get_label(ta), LV_ANIM_ON);
        }
    }
    else if(e == LV_EVENT_DEFOCUSED) {
        if(indev_type == LV_INDEV_TYPE_ENCODER) {
            if(textinput_objs.kb == NULL) {
                lv_textarea_set_cursor_hidden(ta, true);
            }
        } else {
            lv_textarea_set_cursor_hidden(ta, true);
        }
    }
}

static void kb_event_cb(lv_obj_t * kb, lv_event_t e)
{
    lv_keyboard_def_event_cb(kb, e);

    if(e == LV_EVENT_APPLY || e == LV_EVENT_CANCEL) {
        lv_group_focus_obj(lv_keyboard_get_textarea(kb));
        lv_obj_del(kb);
        textinput_objs.kb = NULL;
        lv_obj_set_height(tv, LV_VER_RES);
    }
}

#endif
