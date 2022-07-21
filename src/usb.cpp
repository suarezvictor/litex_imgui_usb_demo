// This file is Copyright (c) 2021 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause
// Some code adapted from https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.cpp, licensed under GPL 2, (C) Circuits At Home, LTD

//Current command for SoC generation:
//$ ./digilent_arty.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=200e6 --cpu-variant=full --build
//for DVI 800x600@50Hz: 
//$ ./digilent_arty.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=166666666 --cpu-type=vexriscv --cpu-variant=full --build

//GPIO pins for USB
#define DM_P0  12 //D-
#define DP_P0  13 //D+
#define DP_P1  14 //D+
#define DM_P1  15 //D-

//#define DEBUG_ALL
#define USE_IMGUI

//mouse acceleration (seems required for high FPS)
#define MOUSE_ACCEL_FACTOR (0.9/60) //enable mouse acceleration
#define MOUSE_ACCEL_SMOOTH .05 //avoid jumps in speed

#include <stdint.h>
#include <stdio.h>
#include <string.h>
extern "C" {
#include "lite_fb.h"
}
#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_sw.h"
#include "usb_keys.h"
#endif

#define LED_BUILTIN 0
#define PROFILE_NAME "LiteX"

//#include "usb_host.h"
#include "USBHost.hpp"


#ifdef DEBUG_ALL
extern volatile uint8_t received_NRZI_buffer_bytesCnt;
extern uint16_t received_NRZI_buffer[];
#endif

unsigned activity_count = 0;
void my_LedBlinkCB(int on_off)
{
  hal_gpio_set_level(BLINK_GPIO, on_off);
#ifdef DEBUG_ALL
  if(on_off)
  {
    if(received_NRZI_buffer_bytesCnt <= 13) //this is for debugging no-data packets
      /*initStates(-1,-1,-1,-1,-1,-1,-1,-1)*/; //disable all to stop processing
    else
      ++activity_count;
  }
#endif
}

usb_pins_config_t USB_Pins_Config =
{
  DP_P0, DM_P0,
  DP_P1, DM_P1,
  -1, -1,
  -1, -1
};


extern "C" void loop();
extern "C" void setup();
bool do_mouseui_update(int mousex, int mousey, int buttons, int wheel);
bool do_keybui_update(uint8_t modifiers, uint8_t key, bool pressed);
void ui_init();
void do_ui();

void delay(int ms)
{
 int t1 = micros() + ms*1000;
 while(int(micros() - t1) < 0);
}

extern "C" USBMessage usb_msg_queue_buffer[];
USBMessage FAST_DATA usb_msg_queue_buffer[100]; //NOTE: too much data makes things slowers!

void setup()
{
  ui_init();
/*
  for(;;)
  {
    static uint32_t color = 0;
    //quarter frame 25600 times: 68s/60s single/double pixel DMA (about 94FPS-106FPS full frame)
    fb_fillrect(1, 1, FB_WIDTH/2, FB_HEIGHT/2, color);
    color += 0x010101;
    fb_swap_buffers();
  }
 */ 
  printf("USB init...\n");
  USH.init( USB_Pins_Config, usb_msg_queue_buffer, sizeof(usb_msg_queue_buffer)/sizeof(usb_msg_queue_buffer[0]), my_USB_DetectCB, my_USB_PrintCB );
  USH.setActivityBlinker(my_LedBlinkCB);
  printf("USB init done\n");
  //printf("setup done\n");
}

int mousewheel = 0; 

void loop()
{
    static uint64_t t0 = micros();
    uint64_t t1 = micros();
    float dt = (t1-t0)*1e-6;
    t0 = t1;

    printState();
    /*int msgcount = tu_fifo_count(&usb_msg_queue);
    if(msgcount)
      printf("Elements in FIFO: %d\n", msgcount);*/

    bool had_mousepacket = false;
    static float mouseaccel = 0;

    struct USBMessage msg;
    while( hal_queue_receive(usb_msg_queue, &msg) ) {
      int usbNum = msg.src/NUM_USB;
      if( printDataCB ) {
#if 1//ndef USE_IMGUI      
        printDataCB(usbNum, 32, msg.data, msg.len );
#endif
      }

#ifdef DEBUG_ALL
  static unsigned prev_count = 0;
  if(activity_count != prev_count && received_NRZI_buffer_bytesCnt > 0)
  {
    prev_count = activity_count;
    int xcount = received_NRZI_buffer_bytesCnt;
    uint16_t buf[256];
    memcpy(buf, received_NRZI_buffer, xcount*sizeof(*buf));
    printf("activity %d, received %d transitions\n", activity_count, xcount);
    uint8_t prev_time = buf[0] & 0xFF;
    for(int i=0; i < xcount; ++i)
    {
      uint8_t pins = buf[i]>>8;
      uint8_t bit_deltat = (buf[i] & 0xFF) - prev_time;
      prev_time = (buf[i] & 0xFF);
      printf("0x%02X %d\n", pins, bit_deltat); 
    }
  }
#endif

      bool iskeybpacket = hid_types[usbNum] == USB_HID_PROTO_KEYBOARD && msg.len >= sizeof(keyreport); // 'a' packet: 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x00 https://wiki.osdev.org/USB_Human_Interface_Devices#Report_format
      bool ismousepacket = hid_types[usbNum] == USB_HID_PROTO_MOUSE && msg.len >= 6;

      if(iskeybpacket)
      {
        keyreport& k = *(keyreport*) msg.data;
        static keyreport prev; //should be zero initialized by C runtime
        bool updateui = false;
        uint8_t key = HID_KEY_NOKEY;
        for (uint8_t i = 0; i < sizeof(k.scancode); ++i)
        {
          bool pressed = true, released = true;
          if(k.scancode[i] == HID_KEY_ERROR)
          {
            key = HID_KEY_ERROR;
            break;
          }
          for (uint8_t j = 0; j < sizeof(k.scancode); ++j)
          {
            if(k.scancode[i] == prev.scancode[j])
              pressed = false;
            if(prev.scancode[i] == k.scancode[j])
              released = false;
          }
          if(pressed)
              key = k.scancode[i];
           if(released)
              key = prev.scancode[i];

          if(pressed || released)
             updateui = do_keybui_update(k.modifier, key, pressed) || updateui;
        }
        if(key == HID_KEY_NOKEY)
          updateui = do_keybui_update(k.modifier, HID_KEY_NOKEY, false) || updateui;
        if(key != HID_KEY_ERROR)
          prev = k;
        if(updateui)
          break;
      }
      else if(ismousepacket)
      {
        had_mousepacket = true;
        static int x = FB_WIDTH/2, y = FB_HEIGHT/2;
        //packet decoding in 12-bit values (some mouses reports 8 bit values)
        //see https://forum.pjrc.com/threads/45740-USB-Host-Mouse-Driver
        uint8_t buttons = msg.data[0];
        int16_t dx = ((msg.data[2] & 0x0f) << 8) | (msg.data[1] & 0xff); dx <<= 4; dx >>= 4; //sign correction
        int16_t dy = ((msg.data[3] & 0xff) << 4) | ((msg.data[2] >> 4) & 0x0f); dy <<= 4; dy >>= 4; //sign correction
		int16_t wheel = (int8_t) msg.data[4];
		        
        //coordinate update
#ifdef MOUSE_ACCEL_FACTOR
        //cuadratic acceleration
        float mspeed = sqrt(dx*dx+dy*dy)*MOUSE_ACCEL_FACTOR/dt;
        float acc = (1.-MOUSE_ACCEL_SMOOTH)*mouseaccel + MOUSE_ACCEL_SMOOTH*mspeed;
        if(acc > mouseaccel) mouseaccel = acc; //deceleration has priority
        x += dx + dx*mouseaccel;
        y += dy + dy*mouseaccel;
#else
        x += dx;
        y += dy;
#endif
        mousewheel += wheel;
        if(x < 0) x = 0;
        if(x >= FB_WIDTH) x = FB_WIDTH-1; 
        if(y < 0) y = 0;
        if(y >= FB_HEIGHT) y = FB_HEIGHT-1;
        if(do_mouseui_update(x, y, buttons, mousewheel))
        {
#if 1//ndef USE_IMGUI         
          printf("x %d (%+d), y %d (%+d), buttons 0x%02X wheel %d (%+d)\n", x, dx, y, dy, buttons, mousewheel, wheel);
#endif
          break;
        }
      }
    }

    if(!had_mousepacket)
      mouseaccel = 0;


    static int frame = 0;
    if(!(++frame % 60))
      printf("FPS %.1f\n", 1./dt);


    do_ui();
    mousewheel = 0; 
}


#if !defined(TIMER_INTERVAL0_SEC)
#error avoid polling
#else
extern "C" void litex_timer_setup(uint32_t cycles, timer_isr_t handler);
void hal_timer_setup(timer_idx_t timer_num, uint32_t alarm_value, timer_isr_t timer_isr)
{
  printf("in hal_timer_setup at 0x%p\n", hal_timer_setup);
  litex_timer_setup(alarm_value, timer_isr);
  //delay(50); //DEBUG ONLY: make room to generate some interrupts
}
#endif


#ifdef USE_IMGUI
bool do_keybui_update(uint8_t modifiers, uint8_t key, bool pressed)
{
  ImGuiIO& io = ImGui::GetIO();

  char inputchar = '\0';
  if(key != HID_KEY_NOKEY)
  {
    switch(modifiers)
    {
      case 0: //add plain character only if no modifiers are set
        if(key < sizeof(usb_key_codesPLAIN))
          inputchar = usb_key_codesPLAIN[key];
        break;
      case HID_LSHIFT_MASK: //add shifted character only if no other modifiers are present
      case HID_RSHIFT_MASK:
      case HID_LSHIFT_MASK | HID_RSHIFT_MASK:
        if(key < sizeof(usb_key_codesSHIFT))
          inputchar = usb_key_codesSHIFT[key];
        break;
    }
    if(inputchar && pressed)
      io.AddInputCharacter(inputchar);
    io.KeysDown[key] = pressed;
  }

  io.KeyShift = 0 != (modifiers & (HID_LSHIFT_MASK | HID_RSHIFT_MASK));
  io.KeyCtrl  = 0 != (modifiers & (HID_LCTRL_MASK | HID_RCTRL_MASK));
  io.KeyAlt   = 0 != (modifiers & (HID_LALT_MASK | HID_RALT_MASK));
  io.KeySuper = 0 != (modifiers & (HID_LSUPER_MASK | HID_RSUPER_MASK));

  printf("KEY %s event, key 0x%02x, char '%c', modifiers 0x%02x\n", pressed ? "PRESSED":"RELEASED", key, inputchar, modifiers);
  return true;
}

uint8_t mousebuttons = 0;
bool do_mouseui_update(int mousex, int mousey, int buttons, int wheel)
{
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos = ImVec2((float)mousex, (float)mousey); //TODO: AddMousePosEvent in ImGui v1.88
  //mousebuttons |= buttons; //this is for auto release
  if(mousebuttons != buttons)
  {
    mousebuttons = buttons;
    return true; //notify on change
  }
  return false;
}

#include "test_ui.cpp"
void do_ui()
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(VIDEO_FRAMEBUFFER_HRES, VIDEO_FRAMEBUFFER_VRES);
    ImVec2 p = io.MousePos;
    int mousex = int(p.x), mousey = int(p.y);
    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
        io.MouseDown[i] = (mousebuttons >> i) & 1;
    io.MouseWheel = mousewheel;
    mousewheel = 0;

    static int n = 0;
    static uint64_t t0 = micros();
    uint64_t t1 = micros();
    io.DeltaTime = (t1-t0)*1e-6;
    t0 = t1;

    ImGui::NewFrame();
    uint32_t bgcolor = do_test_ui();
    ImGui::Render();

    imgui_sw::paint_imgui((uint32_t*)fb_base,VIDEO_FRAMEBUFFER_HRES,VIDEO_FRAMEBUFFER_VRES);

    //draw the mouse pointer as a cross
    fb_set_cliprect(0, 0, VIDEO_FRAMEBUFFER_HRES-1, VIDEO_FRAMEBUFFER_VRES-1);
    fb_line(mousex-5, mousey, mousex+6, mousey, IM_COL32(0, 255, 0, 0));
    fb_line(mousex, mousey-5, mousex, mousey+6, IM_COL32(0, 255, 0, 0));

    fb_swap_buffers();
    fb_fillrect(0, 0, VIDEO_FRAMEBUFFER_HRES-1, VIDEO_FRAMEBUFFER_VRES-1, bgcolor);
    //fb_clear();
}

size_t alloc_total = 0;
static void *custom_malloc(size_t size, void* user_data)
{
  IM_UNUSED(user_data);
  size_t *ptr = (size_t *) malloc(size+sizeof(size_t));
  if(!ptr) return ptr;
  *ptr++ = size;
  alloc_total += size;
  //printf("alloc: 0x%p, size %d, total %d\n", ptr, size, alloc_total);
  return ptr;
}

static void custom_free(void* ptr, void* user_data)
{
  IM_UNUSED(user_data);
  if(!ptr) return;
  size_t *ptra = (size_t*)ptr;
  size_t size = *(--ptra);
  alloc_total -= size;
  //printf("free: 0x%p, size %d, total %d\n", ptr, size, alloc_total);
  free(ptra);
}

void ui_init()
{
  fb_init();
  fb_set_dual_buffering(1);

    printf("Initializing ImGui at %dx%d...\n", VIDEO_FRAMEBUFFER_HRES, VIDEO_FRAMEBUFFER_VRES);
    IMGUI_CHECKVERSION();
    ImGui::SetAllocatorFunctions(custom_malloc, custom_free, nullptr);
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //io.MouseDrawCursor = true; //makes things hang up
    //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   // We can honor GetMouseCursor() values (optional)

    for(uint8_t key = 0; key < HID_KEY_MAX; ++key)
    {
      ImGuiKey imkey = scan2imguikey(key);
      if(imkey != IMGUIKEY_NONE)
      {
        //printf("key 0x%02x -> imkey %d\n", key, imkey);
        io.KeyMap[imkey] = key; //setup keymap
      }
    }

    imgui_sw::bind_imgui_painting();
    imgui_sw::make_style_fast();

    printf("Starting ImGui...\n");
}

void* operator new(size_t size) {
   void *p = ImGui::MemAlloc(size);
   return p;
}

void operator delete(void *p) {
   return ImGui::MemFree(p);
}
#else
bool do_mouseui_update(int mousex, int mousey, int buttons, int wheel)
{
  static int lastx = FB_WIDTH/2, lasty = FB_HEIGHT/2;
  uint32_t color = 0;
  //fancy color select algorithm
  if(buttons & 1) color ^= 0x4080FF;
  if(buttons & 2) color ^= 0x80FF40;
  if(buttons && mousey < lasty) color = ~color;
        
  fb_fillrect(lastx < mousex ? lastx : mousex, lasty < mousey ? lasty : mousey,
    lastx < mousex ? mousex : lastx, lasty < mousey ? mousey : lasty,
    color);

  lastx = mousex; lasty = mousey;
  return true; //process all mouse events
}

void do_ui()
{
  //delay(500);
}

void ui_init()
{
  fb_init();
  printf("Dummy UI init...\n");
  delay(1000);
  printf("Dummy UI done\n");
}



void* operator new(size_t size) {
   return malloc(size);
}

void operator delete(void *p) {
   free(p);
}

#endif
//TODO: refactor code for this kind of general functions
void* operator new[](size_t size ) { return operator new(size); }
void operator delete[]( void* ptr ) { return operator delete(ptr); }

