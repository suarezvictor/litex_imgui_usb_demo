/*
Taken from https://www.win.tue.nl/~aeb/linux/kbd/scancodes-10.html

4	A 
5	B 
6	C 
7	D 
8	E 
9	F 
10	G 
11	H 
12	I 
13	J 
14	K 
15	L 
16	M 
17	N 
18	O 
19	P 
20	Q 
21	R 
22	S 
23	T 
24	U 
25	V 
26	W 
27	X 
28	Y 
29	Z 
30	1 ! 
31	2 @ 
32	3 # 
33	4 $ 
34	5 % E 
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

#define HID_LSHIFT 0x02
#define HID_RSHIFT 0x20

static const char usb_key_codesPLAIN[]= { "\0\0\0\0abcdefghijklmnopqrtsuvwxyz1234567890\n\e\b\t _\0[]\\\0;'`,./" };
static const char usb_key_codesSHIFT[]= { "\0\0\0\0ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()\n\e\b\t _\0{}|\0:\"~<>?" };

 /*
    io.KeyMap[ImGuiKey_Tab] = VK_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
    io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
    io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
    io.KeyMap[ImGuiKey_Home] = VK_HOME;
    io.KeyMap[ImGuiKey_End] = VK_END;
    io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
    io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
    io.KeyMap[ImGuiKey_Space] = VK_SPACE;
    io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
    io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
    io.KeyMap[ImGuiKey_A] = 'A';
    io.KeyMap[ImGuiKey_C] = 'C';
    io.KeyMap[ImGuiKey_V] = 'V';
    io.KeyMap[ImGuiKey_X] = 'X';
    io.KeyMap[ImGuiKey_Y] = 'Y';
    io.KeyMap[ImGuiKey_Z] = 'Z';
    */
    
