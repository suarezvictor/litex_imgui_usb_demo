// Copyright (C) 2021-2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include "py/obj.h"
#include "py/objstr.h"
#include "py/runtime.h"

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

STATIC mp_obj_t on_mouse(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_dx=0, ARG_dy, ARG_buttons, ARG_wheel };
    static const mp_arg_t allowed_args[] = { //bool u_bool;  mp_int_t u_int; mp_obj_t u_obj; mp_rom_obj_t u_rom_obj;
        { MP_QSTR_dx,		MP_ARG_REQUIRED | MP_ARG_INT,	{.u_int = 0} },
        { MP_QSTR_dy,		MP_ARG_REQUIRED | MP_ARG_INT,	{.u_int = 0} },
        { MP_QSTR_buttons,	MP_ARG_REQUIRED | MP_ARG_INT, 	{.u_int = 0} },
        { MP_QSTR_wheel,	MP_ARG_INT, 					{.u_int = 0} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    //printf("dx %d, dy %d, buttons %d, wheel %d\n",
    //	args[ARG_dx].u_int, args[ARG_dy].u_int, args[ARG_buttons].u_int, args[ARG_wheel].u_int);
	int r = dpg_hidevent_mouse(args[ARG_dx].u_int, args[ARG_dy].u_int, args[ARG_buttons].u_int, args[ARG_wheel].u_int);
    return MP_OBJ_NEW_SMALL_INT(r);
}
MP_DEFINE_CONST_FUN_OBJ_KW(on_mouse_obj, 3, on_mouse);

STATIC mp_obj_t on_keyboard(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_modifiers=0, ARG_key, ARG_pressed, ARG_inputchar };
    static const mp_arg_t allowed_args[] = { //bool u_bool;  mp_int_t u_int; mp_obj_t u_obj; mp_rom_obj_t u_rom_obj;
        { MP_QSTR_modifiers,	MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_key,			MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_pressed,		MP_ARG_REQUIRED | MP_ARG_BOOL, {.u_bool = false} },
        { MP_QSTR_inputchar,	MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} }, //MP_ARG_KW_ONLY
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    //printf("modifiers %d, key %d, pressed %d, inputchar %c\n",
    //	args[ARG_modifiers].u_int, args[ARG_key].u_int, args[ARG_pressed].u_bool, (char) args[ARG_inputchar].u_int);
	int r = dpg_hidevent_keyboard(args[ARG_modifiers].u_int, args[ARG_key].u_int, args[ARG_pressed].u_bool, args[ARG_inputchar].u_int);
    return MP_OBJ_NEW_SMALL_INT(r);
}
MP_DEFINE_CONST_FUN_OBJ_KW(on_keyboard_obj, 4, on_keyboard);

#define CY_IMPL_KW(imp, f) MP_DECLARE_CONST_FUN_OBJ_KW(f##_obj);
#define CY_IMPL_0(imp, f) MP_DECLARE_CONST_FUN_OBJ_0(f##_obj);
#define CY_IMPL_1(imp, f) MP_DECLARE_CONST_FUN_OBJ_1(f##_obj);
#include  "pyimgui_def.inl"

STATIC const mp_rom_map_elem_t imgui_lite_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_imgui_lite) },
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

STATIC MP_DEFINE_CONST_DICT(imgui_lite_module_globals, imgui_lite_module_globals_table);

const mp_obj_module_t mp_module_imgui_lite = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&imgui_lite_module_globals,
};
