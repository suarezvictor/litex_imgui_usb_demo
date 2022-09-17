// Copyright (C) 2021-2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include "py/obj.h"
#include "py/objstr.h"

#define EXPERIMENTAL_CYTHON
//TODO Cython:https://github.com/cython/cython/blob/master/Cython/Compiler/Code.py#L1787

#include <stdio.h> //printf
#include "usbhost/usb_host.h" //USB_HID_PROTO_MOUSE, USB_HID_PROTO_KEYBOARD

//TODO: add API header
void dpg_create_context(void);
void dpg_new_frame(float dt);
void dpg_render(void);
void dpg_end_frame(void);
int dpg_hidevent_mouse(int dx, int dy, int buttons, int wheel);
int dpg_hidevent_keyboard(uint8_t modifiers, uint8_t key, int pressed, char inputchar);


STATIC mp_obj_t create_context() {
	dpg_create_context();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(create_context_obj, create_context);

STATIC mp_obj_t new_frame() {
#warning fix the timing issue
	dpg_new_frame(1./60);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(new_frame_obj, new_frame);

STATIC mp_obj_t render() {
	dpg_render();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(render_obj, render);

STATIC mp_obj_t end_frame() {
	dpg_end_frame();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(end_frame_obj, end_frame);

STATIC mp_obj_t on_mouse(mp_obj_t dx, mp_obj_t dy, mp_obj_t buttons/*, mp_obj_t wheel*/) {
	int r = dpg_hidevent_mouse(mp_obj_get_int(dx), mp_obj_get_int(dy), mp_obj_get_int(buttons), 0);
    return MP_OBJ_NEW_SMALL_INT(r);
}
MP_DEFINE_CONST_FUN_OBJ_3(on_mouse_obj, on_mouse);

STATIC mp_obj_t on_keyboard(mp_obj_t modifiers, mp_obj_t key, mp_obj_t pressed/*, mp_obj_t inputchar*/) {
	int r = dpg_hidevent_keyboard(mp_obj_get_int(modifiers), mp_obj_get_int(key), mp_obj_get_int(pressed), 0);
    return MP_OBJ_NEW_SMALL_INT(r);
}
MP_DEFINE_CONST_FUN_OBJ_3(on_keyboard_obj, on_keyboard);

#define CY_IMPL_KW(imp, f) MP_DECLARE_CONST_FUN_OBJ_KW(f##_obj);
#define CY_IMPL_0(imp, f) MP_DECLARE_CONST_FUN_OBJ_0(f##_obj);
#define CY_IMPL_1(imp, f) MP_DECLARE_CONST_FUN_OBJ_1(f##_obj);
#include  "pyimgui_def.inl"

STATIC const mp_rom_map_elem_t dpg_lite_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_dpg_lite) },
    { MP_ROM_QSTR(MP_QSTR_create_context), MP_ROM_PTR(&create_context_obj) },
    { MP_ROM_QSTR(MP_QSTR_new_frame), MP_ROM_PTR(&new_frame_obj) },
    { MP_ROM_QSTR(MP_QSTR_render), MP_ROM_PTR(&render_obj) },
    { MP_ROM_QSTR(MP_QSTR_end_frame), MP_ROM_PTR(&end_frame_obj) },
    { MP_ROM_QSTR(MP_QSTR_on_mouse), MP_ROM_PTR(&on_mouse_obj) },
    { MP_ROM_QSTR(MP_QSTR_on_keyboard), MP_ROM_PTR(&on_keyboard_obj) },
    { MP_ROM_QSTR(MP_QSTR_HID_PROTO_NONE), MP_ROM_INT(USB_HID_PROTO_NONE) },
    { MP_ROM_QSTR(MP_QSTR_HID_PROTO_MOUSE), MP_ROM_INT(USB_HID_PROTO_MOUSE) },
    { MP_ROM_QSTR(MP_QSTR_HID_PROTO_KEYBOARD), MP_ROM_INT(USB_HID_PROTO_KEYBOARD) },

#define CY_IMPL_KW(imp, f) { MP_ROM_QSTR(MP_QSTR_##f), MP_ROM_PTR(&f##_obj) },
#define CY_IMPL_0(imp, f) CY_IMPL_KW(imp, f)
#define CY_IMPL_1(imp, f) CY_IMPL_KW(imp, f)
#include  "pyimgui_def.inl"
};

STATIC MP_DEFINE_CONST_DICT(dpg_lite_module_globals, dpg_lite_module_globals_table);

const mp_obj_module_t mp_module_dpg_lite = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&dpg_lite_module_globals,
};
