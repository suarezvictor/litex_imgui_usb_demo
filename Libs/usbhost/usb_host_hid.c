//HID functions
#include "usb_host.h"

#ifdef USBHOST_ENABLED
#include "usb_keys.h"

//mouse acceleration (seems required for high FPS)
#define MOUSE_ACCEL_FACTOR (0.9/60) //enable mouse acceleration
#define MOUSE_ACCEL_SMOOTH .05 //avoid jumps in speed

#ifdef DEBUG_ALL
#include <string.h> //for memcpy
#include <stdio.h>
extern volatile uint8_t received_NRZI_buffer_bytesCnt;
extern uint16_t received_NRZI_buffer[];
//extern unsigned activity_count = 0;
#endif

hid_protocol_t usbh_hid_poll(float dt)
{
  bool updateui = true;
  hid_protocol_t protocol;
  for(;;)
  {
    hid_event evt;
    protocol = usbh_hid_process(&evt, updateui, dt);
    switch(protocol)
    {
      case USB_HID_PROTO_KEYBOARD:
        if(!usbh_on_hidevent_keyboard) break;
        updateui = usbh_on_hidevent_keyboard(evt.k.modifier, evt.k.key, evt.k.pressed, evt.k.inputchar);
        if(!updateui) continue;
        break;
      case USB_HID_PROTO_MOUSE:
        if(!usbh_on_hidevent_mouse) break;
        updateui = usbh_on_hidevent_mouse(evt.m.x, evt.m.y, evt.m.buttons, evt.m.wheel);
        if(!updateui) continue;
        break;
      case USB_HID_PROTO_NONE:
        break;
    }
    break;
  }
  return protocol;
}

hid_protocol_t usbh_hid_process(hid_event *evt, int prevupdated, float dt)
{
    hid_protocol_t proto = USB_HID_PROTO_NONE;
    
    static int mousewheel = 0;
    if(prevupdated)
    {
      mousewheel = 0; 
    }

    printState(); //FIXME: required to detect HID events
    /*int msgcount = tu_fifo_count(&usb_msg_queue);
    if(msgcount)
      printf("Elements in FIFO: %d\n", msgcount);*/

    static float mouseacell = 0; //FIXME: move statics to event

    USBMessage msg;
    if( hal_queue_receive(usb_msg_queue, &msg) ) //FIXME: move logic
    { 
      int usbNum = msg.src/NUM_USB;
      if( usbh_on_hiddata_log )
      {
#if 1//ndef USBHOST_USE_IMGUI      
        usbh_on_hiddata_log(usbNum, 32, msg.data, msg.len );
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
      keyreport *k = (keyreport*) msg.data;
      static keyreport prev; //should be zero initialized by C runtime
      uint8_t key = HID_KEY_NOKEY;
      for (uint8_t i = 0; i < sizeof(k->scancode); ++i)
      {
        bool pressed = true, released = true;
        if(k->scancode[i] == HID_KEY_ERROR)
        {
          key = HID_KEY_ERROR;
          break;
        }
        for (uint8_t j = 0; j < sizeof(k->scancode); ++j)
        {
          if(k->scancode[i] == prev.scancode[j])
            pressed = false;
          if(prev.scancode[i] == k->scancode[j])
            released = false;
        }
        if(pressed)
          key = k->scancode[i];
        if(released)
           key = prev.scancode[i];

        if(pressed || released)
        {
          char inputchar = '\0';
		  switch(k->modifier)
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
          //updateui = usbh_on_hidevent_keyboard(k->modifier, key, pressed, inputchar) || updateui;
          evt->k.modifier = k->modifier;
          evt->k.key = key;
          evt->k.pressed = pressed;
          evt->k.inputchar = inputchar;
          proto = USB_HID_PROTO_KEYBOARD;
        }
      }
      if(key != HID_KEY_ERROR)
        prev = *k;
      if(key == HID_KEY_NOKEY)
      {
        //updateui = usbh_on_hidevent_keyboard(k.modifier, HID_KEY_NOKEY, false, '\0') || updateui;
        evt->k.modifier = k->modifier;
        evt->k.key = HID_KEY_NOKEY;
        evt->k.pressed = false;
        evt->k.inputchar = '\0';
        proto = USB_HID_PROTO_KEYBOARD;
      }
    }
    else if(ismousepacket)
    {
        //packet decoding in 12-bit values (some mouses reports 8 bit values)
        //see https://forum.pjrc.com/threads/45740-USB-Host-Mouse-Driver
        uint8_t buttons = msg.data[0];
        //assumes  Report Size = 12
        int16_t dx = ((msg.data[2] & 0x0f) << 8) | (msg.data[1] & 0xff); dx <<= 4; dx >>= 4; //sign correction
        int16_t dy = ((msg.data[3] & 0xff) << 4) | ((msg.data[2] >> 4) & 0x0f); dy <<= 4; dy >>= 4; //sign correction
		int16_t wheel = (int8_t) msg.data[4];
		        
        //coordinate update
#ifdef MOUSE_ACCEL_FACTOR
        //cuadratic acceleration
        float mspeed = sqrt(dx*dx+dy*dy)*MOUSE_ACCEL_FACTOR/dt;
        float acc = (1.-MOUSE_ACCEL_SMOOTH)*mouseacell + MOUSE_ACCEL_SMOOTH*mspeed;
        if(acc > mouseacell) mouseacell = acc; //deceleration has priority
        dx += dx*mouseacell;
        dy += dy*mouseacell;
#endif
        mousewheel += wheel;
        //if(usbh_on_hidevent_mouse(x, y, buttons, mousewheel))
        //  break;
        evt->m.x = dx;
        evt->m.y = dy;
        evt->m.buttons = buttons;
        evt->m.wheel = mousewheel;
        proto = USB_HID_PROTO_MOUSE;
    }
  }
  else
  {
     if(mouseacell != 0)
     {
       //printf("max mouse acell %f\n", mouseacell);
       mouseacell = 0; //FIXME: check inactivity time
     }
  }
  return proto;
}

#endif //USBHOST_ENABLED
