#ifndef __USB_SOFT_HOST_HPP_
#define __USB_SOFT_HOST_HPP_

#ifndef BLINK_GPIO
#define BLINK_GPIO LED_BUILTIN
#endif

#ifdef __cplusplus
extern "C" {
#endif
// include the modified version from Dmitry Samsonov
  #include "usb_host.h"
#ifdef __cplusplus
}
#endif

////////////////////////////////


#ifdef __cplusplus

class USB_SOFT_HOST
{
  public:
    bool init( usb_pins_config_t pconf, USBMessage *qb, size_t qb_size, ondetectcb_t detectCB = Default_USB_DetectCB, printcb_t onDataCB = Default_USB_DataCB, ontick_t onTickCB = nullptr );
    void setPrintCb( printcb_t onDataCB );
    void setOndetectCb( ondetectcb_t onDetectCB );

    void setTaskTicker( ontick_t onTickCB );
    void setActivityBlinker( onledblinkcb_t onActivityCB );
    void setTaskPriority( uint8_t p ) { priority = p; };
    void setTaskCore( uint8_t c ) { core = c; }
    // use those to avoid the pesky "Guru Meditation Error: Core 1 panic'ed (Cache disabled but cached memory region accessed)" error
    // may happen when using SPIFFS, SD or other IRAM driven libraries
    void TimerPause();
    void TimerResume();


  private:
    bool inited = false;
    bool paused = false;
    uint8_t priority = 5;
    uint8_t core = 1;
    bool _init( usb_pins_config_t pconf, USBMessage *qb, size_t qb_size);
    void setUSBMessageCb( onusbmesscb_t onMessageCB );
    static void onUSBMessageDecode(uint8_t src, uint8_t len, uint8_t *data);
    static void (*ticker)();
#ifndef USBHOST_SINGLE_CORE
    static void TimerTask(void *arg);
#endif
};



bool USB_SOFT_HOST::init( usb_pins_config_t pconf, USBMessage *qb, size_t qb_size, ondetectcb_t onDetectCB, printcb_t onDataCB, ontick_t onTickCB )
{
  bool ret = false;
  if( _init( pconf, qb, qb_size ) ) {
#ifndef USBHOST_SINGLE_CORE
#ifdef ESP32
    xTaskCreatePinnedToCore(USB_SOFT_HOST::TimerTask, "USB Soft Host Timer Task", 8192, NULL, priority, NULL, core);
    log_w("USB Soft Host Group timer task is now running on core #%d with priority %d", core, priority);
#else
#warning implement timer task
#endif
#endif
    ret = true;
  }
  setOndetectCb( onDetectCB );
  setPrintCb( onDataCB );
  setUSBMessageCb( onUSBMessageDecode );
  //setMessageReceiver(
  USB_SOFT_HOST::setTaskTicker( onTickCB );
  return ret;
}


bool USB_SOFT_HOST::_init( usb_pins_config_t pconf, USBMessage *qb, size_t qb_size )
{
  if( inited ) return false;

  usbh_init(&pconf, qb, qb_size);
  inited = true;

  return true;
}


void USB_SOFT_HOST::setUSBMessageCb( onusbmesscb_t onMessageCB )
{
  set_usb_mess_cb( onMessageCB );
}


void USB_SOFT_HOST::setPrintCb( printcb_t onDataCB )
{
  set_print_cb( onDataCB );
}



void USB_SOFT_HOST::setOndetectCb( ondetectcb_t onDetectCB )
{
  set_ondetect_cb( onDetectCB );
}



void USB_SOFT_HOST::setTaskTicker( ontick_t onTickCB )
{
  USB_SOFT_HOST::ticker = onTickCB;
}



void USB_SOFT_HOST::setActivityBlinker( onledblinkcb_t onActivityCB )
{
  set_onled_blink_cb( onActivityCB );
}



// called from underlaying C
void USB_SOFT_HOST::onUSBMessageDecode(uint8_t src, uint8_t len, uint8_t *data)
{
  usbh_on_message_decode(src, len, data);
}



void (*USB_SOFT_HOST::ticker)() = nullptr;

/*
void USB_SOFT_HOST::TimerPause()
{
  if( !paused ) {
    log_d("Pausing timer");
    hal_timer_pause(TIMER_0);
    paused = true;
    hal_delay(1);
  } else {
    log_e("Timer already paused!");
  }
}

void USB_SOFT_HOST::TimerResume()
{
  if( paused ) {
    log_d("Resuming timer");
    hal_timer_start(TIMER_0);
    paused = false;
    hal_delay(1);
  } else {
    log_e("Timer already running!");
  }
}
*/

#ifndef USBHOST_SINGLE_CORE
void USB_SOFT_HOST::TimerTask(void *arg)
{
  while (1) {
    struct USBMessage msg;

    #if !defined(USE_NATIVE_GROUP_TIMERS) && defined(TIMER_INTERVAL0_SEC)
      timer_event_t evt;
      xQueueReceive(timer_queue, &evt, portMAX_DELAY);
    #endif
    if( hal_queue_receive(usb_msg_queue, &msg) ) {
      if( printDataCB ) {
        printDataCB( msg.src/4, 32, msg.data, msg.len );
      }
    }

    printState();
    if( ticker ) ticker();
    hal_delay(10);
  }
}
#endif

USB_SOFT_HOST USH;
#endif

#endif
