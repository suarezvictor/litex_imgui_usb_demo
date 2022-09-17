# Dear ImGui example with mouse and keyboard
# Copyright (C) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>

import litex
import dpg_lite as imgui

hmi = litex.USB_HMI(13,12,14,15) #D+/D- pin pairs
hmi.start()
imgui.create_context()

def process_hmi_input():
  while True:
    evt = hmi.process()
    if evt == hmi.HID_PROTO_NONE:
      return
    if evt == hmi.HID_PROTO_MOUSE:
      dx, dy, buttons, wheel = hmi.dx(), hmi.dy(), hmi.buttons(), hmi.wheel()
      if imgui.on_mouse(dx, dy, buttons):
        return
    if evt == hmi.HID_PROTO_KEYBOARD:
      modifiers, key, pressed, inputchar = hmi.key_modifiers(), hmi.key(), hmi.key_pressed(), hmi.key_char()
      if imgui.on_keyboard(modifiers, key, pressed):
        return

s = "a string"
value = 88
checked = True
while True:
  #get input & setup frame
  process_hmi_input()
  imgui.new_frame()

  #custom UI
  _, _ = imgui.begin("My window", False)
  imgui.text("Hello from ImGui + micropython!")
  changed, s = imgui.input_text("input", s, 20)
  changed, value = imgui.slider_int("slider", value, 0, 100, "%d")
  _, checked = imgui.checkbox("Check", checked)
  imgui.end()

  #render frame
  imgui.render()
  imgui.end_frame()

