// This file is Copyright (c) 2021 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause
// Some code adapted from https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.cpp, licensed under GPL 2, (C) Circuits At Home, LTD

//Current command for SoC generation:
//$ ./gsd_orangecrab.py --timer-uptime --uart-baudrate=960000 --with-pmod-gpio --integrated-sram-size 8192 --cpu-variant=full --build
//$ ./digilent_arty.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=200e6 --cpu-variant=full --build
//for DVI 800x600@50Hz: 
//$ ./digilent_arty.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=166666666 --cpu-type=vexriscv --cpu-variant=full --build


#define USBHOST_USE_IMGUI


#include <stdint.h>
#include <stdio.h>
#include <string.h>
extern "C" {
#include "lite_fb.h"
}
#ifdef USBHOST_USE_IMGUI
#include "imgui.h"
#include "imgui_sw.h"
#endif
#include "usb_keys.h"

#define LED_BUILTIN 0
#define PROFILE_NAME "LiteX"

#include "usb_host.h"

#ifdef USBHOST_ENABLED

#ifdef DEBUG_ALL
extern "C" volatile uint8_t received_NRZI_buffer_bytesCnt;
extern "C" uint16_t received_NRZI_buffer[];
extern unsigned activity_count = 0;
#endif


void usbh_on_activitystatus(int on_off)
{
#ifdef BLINK_GPIO
  hal_gpio_set_level(BLINK_GPIO, on_off);
#endif

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

void usbh_on_hiddata_log(uint8_t usbNum, uint8_t byte_depth, uint8_t* data, uint8_t data_len)
{
  // if( myListenUSBPort != usbNum ) return;
  printf("USB %d in (HID type %d): ", usbNum, hid_types[usbNum]);
  for(int k=0;k<data_len;k++) {
    printf("0x%02x ", data[k] );
  }
  printf("\n");
}


void usbh_on_detect( uint8_t usbNum, void * dev )
{
  sDevDesc *device = (sDevDesc*)dev;
  printf("New device detected on USB#%d\n", usbNum);
  printf("desc.bcdUSB             = 0x%04x\n", device->bcdUSB);
  printf("desc.bDeviceClass       = 0x%02x\n", device->bDeviceClass);
  printf("desc.bDeviceSubClass    = 0x%02x\n", device->bDeviceSubClass);
  printf("desc.bDeviceProtocol    = 0x%02x\n", device->bDeviceProtocol);
  printf("desc.bMaxPacketSize0    = 0x%02x\n", device->bMaxPacketSize0);
  printf("desc.idVendor           = 0x%04x\n", device->idVendor);
  printf("desc.idProduct          = 0x%04x\n", device->idProduct);
  printf("desc.bcdDevice          = 0x%04x\n", device->bcdDevice);
  printf("desc.iManufacturer      = 0x%02x\n", device->iManufacturer);
  printf("desc.iProduct           = 0x%02x\n", device->iProduct);
  printf("desc.iSerialNumber      = 0x%02x\n", device->iSerialNumber);
  printf("desc.bNumConfigurations = 0x%02x\n", device->bNumConfigurations);
  // if( device->iProduct == mySupportedIdProduct && device->iManufacturer == mySupportedManufacturer ) {
  //   myListenUSBPort = usbNum;
  // }
  
  if(usbNum < NUM_USB)
  {
    hid_protocol_t hid_protocol = hid_types[usbNum];
    if(hid_protocol == USB_HID_PROTO_KEYBOARD)
      printf("HID KEYBOARD DETECTED\n");
    if(hid_protocol == USB_HID_PROTO_MOUSE)
      printf("HID MOUSE DETECTED\n");
  }
}
#endif //USBHOST_ENABLED

extern "C" void loop();
extern "C" void setup();
void ui_init();
void do_ui(float dt);

extern "C" void audio_init(void);

static uint64_t t0;
void setup()
{

#if 0
  USBHOST_GPIO->OE = 0x000003FF; //all outputs
  for(int i = 0; ; ++i)
  {
    USBHOST_GPIO->OUT = i;
    printf("GPIO 0x%08X\n", USBHOST_GPIO->IN);
  }
#endif

  ui_init();

#ifdef USBHOST_ENABLED
  static const int DM_P0 = 12; //D-
  static const int DP_P0 = 13; //D+
  static const int DP_P1 = 14; //D+
  static const int DM_P1 = 15; //D-
  usbh_pins_init(DP_P0, DM_P0, DP_P1, DM_P1, USBH_QUEUE_SIZE);
#endif

#ifdef I2S_ENABLED
  audio_init();
#endif
  
  t0 = micros();
  printf("Setup done\n");
}


void loop()
{
  uint64_t t1 = micros();
  float dt = int64_t(t1-t0)*1.e-6;
  t0 = t1;

#ifdef USBHOST_ENABLED
  usbh_hid_poll(dt); //may call events
#endif

#ifndef USBHOST_USE_IMGUI
  {
    static uint32_t color = -1;
    static uint8_t x = 0, y = 0;
  	//printf("fill rect test %d, %d, color 0x%08X\n", x, y, color);

    //quarter frame 25600 times: 68s/60s single/double pixel DMA (about 94FPS-106FPS full frame)
    fb_clear();
    fb_fillrect(x, y, x+FB_WIDTH/2, y+FB_HEIGHT/2, color);
    fb_swap_buffers();

    x += 10; y += 5;
    color -= 0x011843;
  }
#else
  do_ui(dt);
#endif

  static int frame = 0;
  if(!(++frame % 60))
    printf("FPS %.1f\n", 1./dt);
}

#if !defined(TIMER_INTERVAL0_SEC)
#error avoid polling
#else
extern "C" void litex_timer_setup(uint32_t cycles, timer_isr_t handler);
void hal_timer_setup(timer_idx_t timer_num, uint32_t alarm_value, timer_isr_t timer_isr)
{
  //printf("in hal_timer_setup at 0x%p\n", hal_timer_setup);
  litex_timer_setup(alarm_value, timer_isr);
  //hal_delay(50); //DEBUG ONLY: make room to generate some interrupts
}
#endif


#ifdef USBHOST_USE_IMGUI
int usbh_on_hidevent_keyboard(uint8_t modifiers, uint8_t key, int pressed, char inputchar)
{
  ImGuiIO& io = ImGui::GetIO();

  if(key != HID_KEY_NOKEY)
  {
    if(inputchar && pressed)
      io.AddInputCharacter(inputchar);
    io.KeysDown[key] = pressed;
  }

  io.KeyShift = 0 != (modifiers & (HID_LSHIFT_MASK | HID_RSHIFT_MASK));
  io.KeyCtrl  = 0 != (modifiers & (HID_LCTRL_MASK | HID_RCTRL_MASK));
  io.KeyAlt   = 0 != (modifiers & (HID_LALT_MASK | HID_RALT_MASK));
  io.KeySuper = 0 != (modifiers & (HID_LSUPER_MASK | HID_RSUPER_MASK));

  printf("[UI] KEY %s event, key 0x%02x, char '%c', modifiers 0x%02x\n", pressed ? "PRESSED":"RELEASED", key, inputchar, modifiers);
  return true;
}

int usbh_on_hidevent_mouse(int dx, int dy, int buttons, int wheel)
{

  ImGuiIO& io = ImGui::GetIO();

  //TODO: AddMousePosEvent in ImGui v1.88
  io.MousePos.x += dx;
  if(io.MousePos.x < 0) io.MousePos.x = 0;
  if(io.MousePos.x > FB_WIDTH-1) io.MousePos.x = FB_WIDTH-1;
  io.MousePos.y += dy;
  if(io.MousePos.y < 0) io.MousePos.y = 0;
  if(io.MousePos.y > FB_HEIGHT-1) io.MousePos.y = FB_HEIGHT-1;

  io.MouseWheel = wheel; //wheel delta
  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
    io.MouseDown[i] = (buttons >> i) & 1;

  printf("x %f (%+d), y %f (%+d), buttons 0x%02X wheel %d\n", io.MousePos.x, dx, io.MousePos.y, dy, buttons, wheel);
  static uint8_t mousebuttons = 0;
  if(mousebuttons != buttons || wheel != 0)
  {
    mousebuttons = buttons;
    return true;
  }
  //this makes the hid process to continue gathering any pending mouse packets when the event is just movements
  //so the UI is not updated after all packet movements are processed
  //A more responsive UI may want to process all individual movements
  return false;
}

#include "test_ui.cpp"
void do_ui(float dt)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(VIDEO_FRAMEBUFFER_HRES, VIDEO_FRAMEBUFFER_VRES);
    
    //TODO: move button & wheel logic
    ImVec2 p = io.MousePos;
    int mousex = int(p.x), mousey = int(p.y);

    io.DeltaTime = dt;

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

#ifdef USBHOST_USE_IMGUI
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
#if defined(LITEX_SIMULATION) && !defined(IMGUI_FONT_CACHING)
    printf("(this may take a while until all font glyphs are renderd)\n");
#endif
    imgui_sw::bind_imgui_painting();
    imgui_sw::make_style_fast();
#endif
}

void* operator new(size_t size) {
   void *p = ImGui::MemAlloc(size);
   return p;
}

void operator delete(void *p) {
   return ImGui::MemFree(p);
}
#else
int usbh_on_hidevent_mouse(int dx, int dy, int buttons, int wheel)
{
  static int lastx = FB_WIDTH/2, lasty = FB_HEIGHT/2;
  uint32_t color = 0;
  //fancy color select algorithm
  if(buttons & 1) color ^= 0x4080FF;
  if(buttons & 2) color ^= 0x80FF40;
  if(buttons && dy < 0) color = ~color;
  
  int x0 = lastx, y0 = lasty;
  lastx += dx; if(lastx < 0) lastx = 0; else if(lastx > FB_WIDTH-1) lastx = FB_WIDTH-1;
  lasty += dy; if(lasty < 0) lasty = 0; else if(lasty > FB_HEIGHT-1) lasty = FB_HEIGHT-1;
  int x1 = lastx, y1 = lasty;

  fb_fillrect(
    x0 < x1 ? x0 : x1,
    y0 < y1 ? y0 : y1,
    x1 > x0 ? x1 : x0,
    y1 > y0 ? y1 : y0,
    color
    );

  printf("x %d (%+d), y %d (%+d), buttons 0x%02X wheel %d\n", lastx, dx, lasty, dy, buttons, wheel);
  
  return true; //process all mouse events
}

int usbh_on_hidevent_keyboard(uint8_t modifiers, uint8_t key, int pressed, char inputchar)
{
  printf("[NO UI] KEY %s event, key 0x%02x, char '%c', modifiers 0x%02x\n", pressed ? "PRESSED":"RELEASED", key, inputchar, modifiers);
  return true;
}

void do_ui(float dt)
{
  hal_delay(1000/200); //limit FPS
}

void ui_init()
{
  fb_init();
  printf("Dummy UI init...\n");
  hal_delay(200);
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
void operator delete[]( void* ptr ) { operator delete(ptr); }

