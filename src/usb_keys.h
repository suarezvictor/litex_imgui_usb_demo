#ifndef _USB_KEYS_H_
#define _USB_KEYS_H_
/*
Key map sources:
https://www.win.tue.nl/~aeb/linux/kbd/scancodes-10.html
https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2 (Public Domain)
*/

/*
4	A 
29	Z 
30	1 ! 
31	2 @ 
32	3 # 
33	4 $ 
34	5 %
35	6 ^ 
36	7 & 
37	8 * 
38	9 ( 
39	0 ) 
40	Enter 
41	Esc 
42	Backspace 
43	Tab 
44	space 
45	- _ 
46	Err:520
47	[ { 
48	] } 
49	\ | 
50	non-US-1 
51	; : 
52	' " 
53	` ~ 
54	, < 
55	. > 
56	/ ? 
57	CapsLock 
58	F1 
59	F2 
60	F3 
61	F4 
62	F5 
63	F6 
64	F7 
65	F8 
66	F9 
67	F10 
68	F11 
69	F12 
70	PrtScr 
71	ScrollLock 
72	Pause 
73	Insert 
74	Home 
75	PgUp 
76	Delete 
77	End 
78	PgDn 
79	Right 
80	Left 
81	Down 
82	Up 
83	NumLock 
84	KP-/ 
85	KP-* 
86	KP-- 
87	KP-+ 
88	KP-Enter 
89	KP-1 / End 
90	KP-2 / Down 
91	KP-3 / PgDn 
92	KP-4 / Left 
93	KP-5 
94	KP-6 / Right 
95	KP-7 / Home 
96	KP-8 / Up 
97	KP-9 / PgUp 
98	KP-0 / Ins 
99	KP-. / Del 
*/

#define HID_LCTRL_MASK		0x01
#define HID_LSHIFT_MASK		0x02
#define HID_LALT_MASK		0x04
#define HID_LSUPER_MASK		0x08
#define HID_RCTRL_MASK		0x10
#define HID_RALT_MASK		0x40
#define HID_RSHIFT_MASK		0x20
#define HID_RSUPER_MASK		0x80

#define HID_KEY_NOKEY		0
#define HID_KEY_A			4
#define HID_KEY_Z			(HID_KEY_A+'Z'-'A') 

#define HID_KEY_ENTER		0x28 // Keyboard Return (ENTER)
#define HID_KEY_ESC			0x29 // Keyboard ESCAPE
#define HID_KEY_BACKSPACE	0x2a // Keyboard DELETE (Backspace)
#define HID_KEY_TAB			0x2b // Keyboard Tab
#define HID_KEY_SPACE		0x2c // Keyboard Spacebar

#define HID_KEY_INSERT		0x49 // Keyboard Insert
#define HID_KEY_HOME		0x4a // Keyboard Home
#define HID_KEY_PAGEUP		0x4b // Keyboard Page Up
#define HID_KEY_DELETE		0x4c // Keyboard Delete Forward
#define HID_KEY_END			0x4d // Keyboard End
#define HID_KEY_PAGEDOWN	0x4e // Keyboard Page Down
#define HID_KEY_RIGHT		0x4f // Keyboard Right Arrow
#define HID_KEY_LEFT		0x50 // Keyboard Left Arrow
#define HID_KEY_DOWN		0x51 // Keyboard Down Arrow
#define HID_KEY_UP			0x52 // Keyboard Up Arrow

#define HID_KEY_KPENTER     0x58 // Keypad ENTER

#define HID_KEY_ERROR		1
#define HID_KEY_MAX			0x80

static const char usb_key_codesPLAIN[]= { "\0\0\0\0abcdefghijklmnopqrstuvwxyz1234567890\n\e\b\t _\0[]\\\0;'`,./" };
static const char usb_key_codesSHIFT[]= { "\0\0\0\0ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()\n\e\b\t _\0{}|\0:\"~<>?" };

struct keyreport {
  union {
    struct { //USB format matches ImGuiModFlags_Ctrl, etc
       uint8_t lctrl :1; 
       uint8_t lshift :1;
       uint8_t lalt :1;
       uint8_t lsuper :1;
       uint8_t rctrl :1;
       uint8_t rshift :1;
       uint8_t ralt :1;
       uint8_t rsuper :1;
    };
    uint8_t modifier;
  };
  uint8_t :8; //reserved
  uint8_t scancode[6];
};

#define IMGUIKEY_NONE ImGuiKey_COUNT //TODO: fix for v.188

static ImGuiKey scan2imguikey(uint8_t scancode)
{
  switch(scancode)
  {
    case HID_KEY_TAB:		return ImGuiKey_Tab;
    case HID_KEY_LEFT:		return ImGuiKey_LeftArrow;
    case HID_KEY_RIGHT: 	return ImGuiKey_RightArrow;
    case HID_KEY_UP: 		return ImGuiKey_UpArrow;
    case HID_KEY_DOWN: 		return ImGuiKey_DownArrow;
    case HID_KEY_PAGEUP:	return ImGuiKey_PageUp;
    case HID_KEY_PAGEDOWN:	return ImGuiKey_PageDown;
    case HID_KEY_HOME:		return ImGuiKey_Home;
    case HID_KEY_END:		return ImGuiKey_End;
    case HID_KEY_INSERT:	return ImGuiKey_Insert;
    case HID_KEY_DELETE:	return ImGuiKey_Delete;
    case HID_KEY_BACKSPACE:	return ImGuiKey_Backspace;
    case HID_KEY_ESC:		return ImGuiKey_Escape;
    case HID_KEY_ENTER:
    case HID_KEY_KPENTER:	return ImGuiKey_Enter;
  }

  switch(scancode-HID_KEY_A+'A')
  {
    case 'A': return ImGuiKey_A; // for text edit CTRL+A: select all
    case 'C': return ImGuiKey_C; // for text edit CTRL+C: copy
    case 'V': return ImGuiKey_V; // for text edit CTRL+V: paste
    case 'X': return ImGuiKey_X; // for text edit CTRL+X: cut
    case 'Y': return ImGuiKey_Y; // for text edit CTRL+Y: redo
    case 'Z': return ImGuiKey_Z; // for text edit CTRL+Z: undo
  }
  
  return IMGUIKEY_NONE;
}
    
#endif // _USB_KEYS_H_

