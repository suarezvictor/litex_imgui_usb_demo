#include <stdio.h>
#include "cython2mp.h"
#include "imgui.h"

//////////////////////
#define ImGuiStyleVar_Count_ ImGuiStyleVar_COUNT
#warning this is a hack to use same a different imgui.h version than in the cpython source
#define DisplayVisibleMin DisplaySize
#define DisplayVisibleMax DisplaySize
#define ConfigResizeWindowsFromEdges \
        ConfigWindowsResizeFromEdges
#define GetOverlayDrawList GetWindowDrawList
#define SetScrollHere SetScrollHereY
#define TextAnsi TextV
#define TextAnsiColored TextColored
//////////////////////

#define __pyx_f_4core__from_bytes(x) (x)
#define __pyx_f_4core__bytes(x) (x)
#define __Pyx_PyInt_As_ImU32(x) (ImU32) mp_obj_get_int(x)
#define __Pyx_PyInt_From_ImU32(x) __Pyx_PyInt_From_int(x)
#define __Pyx_PyInt_As_ImGuiWindowFlags(x) (ImGuiWindowFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiInputTextFlags(x) (ImGuiInputTextFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiID(x) (ImGuiID) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiCol(x) (ImGuiCol) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiCond(x) (ImGuiCond) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiTreeNodeFlags(x) (ImGuiTreeNodeFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiDir(x) (ImGuiDir) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiHoveredFlags(x) (ImGuiHoveredFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiMouseCursor(x) (ImGuiMouseCursor) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiStyleVar(x) (ImGuiStyleVar) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiDragDropFlags(x) (ImGuiDragDropFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiBackendFlags(x) (ImGuiBackendFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImGuiConfigFlags(x) (ImGuiConfigFlags) mp_obj_get_int(x)
#define __Pyx_PyInt_As_ImWchar(x) (ImWchar) mp_obj_get_int(x)


#warning copy object
#define __Pyx_decode_c_string(s, ...) ((mp_obj_t)s)

static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}

static int __pyx_memviewslice_is_contig(const __Pyx_memviewslice mvs, char order, int ndim);
static __Pyx_memviewslice __pyx_memoryview_copy_new_contig(const __Pyx_memviewslice *from_mvs,
                                 const char *mode, int ndim,
                                 size_t sizeof_dtype, int contig_flag,
                                 int dtype_is_object);
static int __pyx_slices_overlap(__Pyx_memviewslice *slice1,
                                __Pyx_memviewslice *slice2,
                                int ndim, size_t itemsize);
                                 
#define __Pyx_ParseOptionalKeywords(...) 0
#warning implement __Pyx_ParseOptionalKeywords

static PyObject *__pyx_kp_s_3f;
static PyObject *__pyx_kp_s_6f;
static PyObject *__pyx_n_s_ALWAYS;
static PyObject *__pyx_n_s_APPEARING;
static PyObject *__pyx_n_s_ASCII;
static PyObject *__pyx_n_s_BACKEND_HAS_GAMEPAD;
static PyObject *__pyx_n_s_BACKEND_HAS_MOUSE_CURSORS;
static PyObject *__pyx_n_s_BACKEND_HAS_SET_MOUSE_POS;
static PyObject *__pyx_kp_s_Buffer_view_does_not_expose_stri;
static PyObject *__pyx_n_s_COLOR_BORDER;
static PyObject *__pyx_n_s_COLOR_BORDER_SHADOW;
static PyObject *__pyx_n_s_COLOR_BUTTON;
static PyObject *__pyx_n_s_COLOR_BUTTON_ACTIVE;
static PyObject *__pyx_n_s_COLOR_BUTTON_HOVERED;
static PyObject *__pyx_n_s_COLOR_CHECK_MARK;
static PyObject *__pyx_n_s_COLOR_CHILD_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_COUNT;
static PyObject *__pyx_n_s_COLOR_DRAG_DROP_TARGET;
static PyObject *__pyx_n_s_COLOR_EDIT_ALPHA_BAR;
static PyObject *__pyx_n_s_COLOR_EDIT_ALPHA_PREVIEW;
static PyObject *__pyx_n_s_COLOR_EDIT_ALPHA_PREVIEW_HALF;
static PyObject *__pyx_n_s_COLOR_EDIT_DATA_TYPE_MASK;
static PyObject *__pyx_n_s_COLOR_EDIT_FLOAT;
static PyObject *__pyx_n_s_COLOR_EDIT_HDR;
static PyObject *__pyx_n_s_COLOR_EDIT_HEX;
static PyObject *__pyx_n_s_COLOR_EDIT_HSV;
static PyObject *__pyx_n_s_COLOR_EDIT_INPUTS_MASK;
static PyObject *__pyx_n_s_COLOR_EDIT_NONE;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_ALPHA;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_DRAG_DROP;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_INPUTS;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_LABEL;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_OPTIONS;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_PICKER;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_SIDE_PREVIEW;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_SMALL_PREVIEW;
static PyObject *__pyx_n_s_COLOR_EDIT_NO_TOOLTIP;
static PyObject *__pyx_n_s_COLOR_EDIT_OPTIONS_DEFAULT;
static PyObject *__pyx_n_s_COLOR_EDIT_PICKER_HUE_BAR;
static PyObject *__pyx_n_s_COLOR_EDIT_PICKER_HUE_WHEEL;
static PyObject *__pyx_n_s_COLOR_EDIT_PICKER_MASK;
static PyObject *__pyx_n_s_COLOR_EDIT_RGB;
static PyObject *__pyx_n_s_COLOR_EDIT_UINT8;
static PyObject *__pyx_n_s_COLOR_FRAME_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_FRAME_BACKGROUND_ACTIVE;
static PyObject *__pyx_n_s_COLOR_FRAME_BACKGROUND_HOVERED;
static PyObject *__pyx_n_s_COLOR_HEADER;
static PyObject *__pyx_n_s_COLOR_HEADER_ACTIVE;
static PyObject *__pyx_n_s_COLOR_HEADER_HOVERED;
static PyObject *__pyx_n_s_COLOR_MENUBAR_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_MODAL_WINDOW_DIM_BACKGROUN;
static PyObject *__pyx_n_s_COLOR_NAV_HIGHLIGHT;
static PyObject *__pyx_n_s_COLOR_NAV_WINDOWING_DIM_BACKGROU;
static PyObject *__pyx_n_s_COLOR_NAV_WINDOWING_HIGHLIGHT;
static PyObject *__pyx_n_s_COLOR_PLOT_HISTOGRAM;
static PyObject *__pyx_n_s_COLOR_PLOT_HISTOGRAM_HOVERED;
static PyObject *__pyx_n_s_COLOR_PLOT_LINES;
static PyObject *__pyx_n_s_COLOR_PLOT_LINES_HOVERED;
static PyObject *__pyx_n_s_COLOR_POPUP_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_RESIZE_GRIP;
static PyObject *__pyx_n_s_COLOR_RESIZE_GRIP_ACTIVE;
static PyObject *__pyx_n_s_COLOR_RESIZE_GRIP_HOVERED;
static PyObject *__pyx_n_s_COLOR_SCROLLBAR_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_SCROLLBAR_GRAB;
static PyObject *__pyx_n_s_COLOR_SCROLLBAR_GRAB_ACTIVE;
static PyObject *__pyx_n_s_COLOR_SCROLLBAR_GRAB_HOVERED;
static PyObject *__pyx_n_s_COLOR_SEPARATOR;
static PyObject *__pyx_n_s_COLOR_SEPARATOR_ACTIVE;
static PyObject *__pyx_n_s_COLOR_SEPARATOR_HOVERED;
static PyObject *__pyx_n_s_COLOR_SLIDER_GRAB;
static PyObject *__pyx_n_s_COLOR_SLIDER_GRAB_ACTIVE;
static PyObject *__pyx_n_s_COLOR_TEXT;
static PyObject *__pyx_n_s_COLOR_TEXT_DISABLED;
static PyObject *__pyx_n_s_COLOR_TEXT_SELECTED_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_TITLE_BACKGROUND;
static PyObject *__pyx_n_s_COLOR_TITLE_BACKGROUND_ACTIVE;
static PyObject *__pyx_n_s_COLOR_TITLE_BACKGROUND_COLLAPSED;
static PyObject *__pyx_n_s_COLOR_WINDOW_BACKGROUND;
static PyObject *__pyx_n_s_COMBO_HEIGHT_LARGE;
static PyObject *__pyx_n_s_COMBO_HEIGHT_LARGEST;
static PyObject *__pyx_n_s_COMBO_HEIGHT_MASK;
static PyObject *__pyx_n_s_COMBO_HEIGHT_REGULAR;
static PyObject *__pyx_n_s_COMBO_HEIGHT_SMALL;
static PyObject *__pyx_n_s_COMBO_NO_ARROW_BUTTON;
static PyObject *__pyx_n_s_COMBO_NO_PREVIEW;
static PyObject *__pyx_n_s_COMBO_POPUP_ALIGN_LEFT;
static PyObject *__pyx_n_s_CONFIG_IS_RGB;
static PyObject *__pyx_n_s_CONFIG_IS_TOUCH_SCREEN;
static PyObject *__pyx_n_s_CONFIG_NAV_ENABLE_GAMEPAD;
static PyObject *__pyx_n_s_CONFIG_NAV_ENABLE_KEYBOARD;
static PyObject *__pyx_n_s_CONFIG_NAV_ENABLE_SET_MOUSE_POS;
static PyObject *__pyx_n_s_CONFIG_NAV_NO_CAPTURE_KEYBOARD;
static PyObject *__pyx_n_s_CONFIG_NO_MOUSE;
static PyObject *__pyx_n_s_CONFIG_NO_MOUSE_CURSOR_CHANGE;
static PyObject *__pyx_kp_s_Can_only_create_a_buffer_that_is;
static PyObject *__pyx_kp_s_Cannot_assign_to_read_only_memor;
static PyObject *__pyx_kp_s_Cannot_create_writable_memory_vi;
static PyObject *__pyx_kp_s_Cannot_index_with_type_s;
static PyObject *__pyx_n_s_Colors;
static PyObject *__pyx_kp_s_Context_invalid_None_or_destroye;
static PyObject *__pyx_n_s_DIRECTION_DOWN;
static PyObject *__pyx_n_s_DIRECTION_LEFT;
static PyObject *__pyx_n_s_DIRECTION_NONE;
static PyObject *__pyx_n_s_DIRECTION_RIGHT;
static PyObject *__pyx_n_s_DIRECTION_UP;
static PyObject *__pyx_n_s_DRAG_DROP_ACCEPT_BEFORE_DELIVERY;
static PyObject *__pyx_n_s_DRAG_DROP_ACCEPT_NO_DRAW_DEFAULT;
static PyObject *__pyx_n_s_DRAG_DROP_ACCEPT_NO_PREVIEW_TOOL;
static PyObject *__pyx_n_s_DRAG_DROP_ACCEPT_PEEK_ONLY;
static PyObject *__pyx_n_s_DRAG_DROP_SOURCE_ALLOW_NULL_ID;
static PyObject *__pyx_n_s_DRAG_DROP_SOURCE_AUTO_EXPIRE_PAY;
static PyObject *__pyx_n_s_DRAG_DROP_SOURCE_EXTERN;
static PyObject *__pyx_n_s_DRAG_DROP_SOURCE_NO_DISABLE_HOVE;
static PyObject *__pyx_n_s_DRAG_DROP_SOURCE_NO_HOLD_TO_OPEN;
static PyObject *__pyx_n_s_DRAG_DROP_SOURCE_NO_PREVIEW_TOOL;
static PyObject *__pyx_kp_s_Direction_wasn_t_specified;
static PyObject *__pyx_n_s_DrawCmd;
static PyObject *__pyx_n_s_DrawData;
static PyObject *__pyx_n_s_DrawList;
static PyObject *__pyx_n_s_Ellipsis;
static PyObject *__pyx_kp_s_Empty_shape_tuple_for_cython_arr;
static PyObject *__pyx_kp_s_Expected_at_least_d_argument_s_g;
static PyObject *__pyx_n_s_FIRST_USE_EVER;
static PyObject *__pyx_n_s_FOCUS_ANY_WINDOW;
static PyObject *__pyx_n_s_FOCUS_CHILD_WINDOWS;
static PyObject *__pyx_n_s_FOCUS_ROOT_AND_CHILD_WINDOWS;
static PyObject *__pyx_n_s_FOCUS_ROOT_WINDOW;
static PyObject *__pyx_n_s_Font;
static PyObject *__pyx_n_s_FontAtlas;
static PyObject *__pyx_kp_s_Function_call_with_ambiguous_arg;
static PyObject *__pyx_n_s_GuiStyle;
static PyObject *__pyx_n_s_HOVERED_ALLOW_WHEN_BLOCKED_BY_AC;
static PyObject *__pyx_n_s_HOVERED_ALLOW_WHEN_BLOCKED_BY_PO;
static PyObject *__pyx_n_s_HOVERED_ALLOW_WHEN_OVERLAPPED;
static PyObject *__pyx_n_s_HOVERED_ANY_WINDOW;
static PyObject *__pyx_n_s_HOVERED_CHILD_WINDOWS;
static PyObject *__pyx_n_s_HOVERED_NONE;
static PyObject *__pyx_n_s_HOVERED_RECT_ONLY;
static PyObject *__pyx_n_s_HOVERED_ROOT_AND_CHILD_WINDOWS;
static PyObject *__pyx_n_s_HOVERED_ROOT_WINDOW;
static PyObject *__pyx_n_s_INPUT_TEXT_ALLOW_TAB_INPUT;
static PyObject *__pyx_n_s_INPUT_TEXT_ALWAYS_INSERT_MODE;
static PyObject *__pyx_n_s_INPUT_TEXT_AUTO_SELECT_ALL;
static PyObject *__pyx_n_s_INPUT_TEXT_CALLBACK_ALWAYS;
static PyObject *__pyx_n_s_INPUT_TEXT_CALLBACK_CHAR_FILTER;
static PyObject *__pyx_n_s_INPUT_TEXT_CALLBACK_COMPLETION;
static PyObject *__pyx_n_s_INPUT_TEXT_CALLBACK_HISTORY;
static PyObject *__pyx_n_s_INPUT_TEXT_CHARS_DECIMAL;
static PyObject *__pyx_n_s_INPUT_TEXT_CHARS_HEXADECIMAL;
static PyObject *__pyx_n_s_INPUT_TEXT_CHARS_NO_BLANK;
static PyObject *__pyx_n_s_INPUT_TEXT_CHARS_UPPERCASE;
static PyObject *__pyx_n_s_INPUT_TEXT_CTRL_ENTER_FOR_NEW_LI;
static PyObject *__pyx_n_s_INPUT_TEXT_ENTER_RETURNS_TRUE;
static PyObject *__pyx_n_s_INPUT_TEXT_NO_HORIZONTAL_SCROLL;
static PyObject *__pyx_n_s_INPUT_TEXT_NO_UNDO_REDO;
static PyObject *__pyx_n_s_INPUT_TEXT_PASSWORD;
static PyObject *__pyx_n_s_INPUT_TEXT_READ_ONLY;
static PyObject *__pyx_n_s_IO;
static PyObject *__pyx_n_s_ImGuiContext;
static PyObject *__pyx_n_s_ImGuiError;
static PyObject *__pyx_n_s_ImGuiID;
static PyObject *__pyx_n_s_ImportError;
static PyObject *__pyx_kp_s_Improperly_initialized_use_imgui;
static PyObject *__pyx_kp_s_Incompatible_checksums_s_vs_0xb0;
static PyObject *__pyx_n_s_IndexError;
static PyObject *__pyx_kp_s_Indirect_dimensions_not_supporte;
static PyObject *__pyx_kp_s_Invalid_mode_expected_c_or_fortr;
static PyObject *__pyx_kp_s_Invalid_shape_in_axis_d_d;
static PyObject *__pyx_n_s_KEY_A;
static PyObject *__pyx_n_s_KEY_BACKSPACE;
static PyObject *__pyx_n_s_KEY_C;
static PyObject *__pyx_n_s_KEY_DELETE;
static PyObject *__pyx_n_s_KEY_DOWN_ARROW;
static PyObject *__pyx_n_s_KEY_END;
static PyObject *__pyx_n_s_KEY_ENTER;
static PyObject *__pyx_n_s_KEY_ESCAPE;
static PyObject *__pyx_n_s_KEY_HOME;
static PyObject *__pyx_n_s_KEY_INSERT;
static PyObject *__pyx_n_s_KEY_LEFT_ARROW;
static PyObject *__pyx_n_s_KEY_PAGE_DOWN;
static PyObject *__pyx_n_s_KEY_PAGE_UP;
static PyObject *__pyx_n_s_KEY_RIGHT_ARROW;
static PyObject *__pyx_n_s_KEY_SPACE;
static PyObject *__pyx_n_s_KEY_TAB;
static PyObject *__pyx_n_s_KEY_UP_ARROW;
static PyObject *__pyx_n_s_KEY_V;
static PyObject *__pyx_n_s_KEY_X;
static PyObject *__pyx_n_s_KEY_Y;
static PyObject *__pyx_n_s_KEY_Z;
static PyObject *__pyx_n_s_MOUSE_CURSOR_ARROW;
static PyObject *__pyx_n_s_MOUSE_CURSOR_HAND;
static PyObject *__pyx_n_s_MOUSE_CURSOR_NONE;
static PyObject *__pyx_n_s_MOUSE_CURSOR_RESIZE_ALL;
static PyObject *__pyx_n_s_MOUSE_CURSOR_RESIZE_EW;
static PyObject *__pyx_n_s_MOUSE_CURSOR_RESIZE_NESW;
static PyObject *__pyx_n_s_MOUSE_CURSOR_RESIZE_NS;
static PyObject *__pyx_n_s_MOUSE_CURSOR_RESIZE_NWSE;
static PyObject *__pyx_n_s_MOUSE_CURSOR_TEXT_INPUT;
static PyObject *__pyx_n_s_MemoryError;
static PyObject *__pyx_kp_s_MemoryView_of_r_at_0x_x;
static PyObject *__pyx_kp_s_MemoryView_of_r_object;
static PyObject *__pyx_kp_s_No_matching_signature_found;
static PyObject *__pyx_n_b_O;
static PyObject *__pyx_n_s_ONCE;
static PyObject *__pyx_kp_s_Out_of_bounds_on_buffer_access_a;
static PyObject *__pyx_n_s_PickleError;
static PyObject *__pyx_n_s_RuntimeError;
static PyObject *__pyx_n_s_SELECTABLE_ALLOW_DOUBLE_CLICK;
static PyObject *__pyx_n_s_SELECTABLE_DONT_CLOSE_POPUPS;
static PyObject *__pyx_n_s_SELECTABLE_SPAN_ALL_COLUMNS;
static PyObject *__pyx_n_s_STYLE_ALPHA;
static PyObject *__pyx_n_s_STYLE_BUTTON_TEXT_ALIGN;
static PyObject *__pyx_n_s_STYLE_CHILD_BORDERSIZE;
static PyObject *__pyx_n_s_STYLE_CHILD_ROUNDING;
static PyObject *__pyx_n_s_STYLE_FRAME_BORDERSIZE;
static PyObject *__pyx_n_s_STYLE_FRAME_PADDING;
static PyObject *__pyx_n_s_STYLE_FRAME_ROUNDING;
static PyObject *__pyx_n_s_STYLE_GRAB_MIN_SIZE;
static PyObject *__pyx_n_s_STYLE_GRAB_ROUNDING;
static PyObject *__pyx_n_s_STYLE_INDENT_SPACING;
static PyObject *__pyx_n_s_STYLE_ITEM_INNER_SPACING;
static PyObject *__pyx_n_s_STYLE_ITEM_SPACING;
static PyObject *__pyx_n_s_STYLE_POPUP_BORDERSIZE;
static PyObject *__pyx_n_s_STYLE_POPUP_ROUNDING;
static PyObject *__pyx_n_s_STYLE_SCROLLBAR_ROUNDING;
static PyObject *__pyx_n_s_STYLE_SCROLLBAR_SIZE;
static PyObject *__pyx_n_s_STYLE_WINDOW_BORDERSIZE;
static PyObject *__pyx_n_s_STYLE_WINDOW_MIN_SIZE;
static PyObject *__pyx_n_s_STYLE_WINDOW_PADDING;
static PyObject *__pyx_n_s_STYLE_WINDOW_ROUNDING;
static PyObject *__pyx_n_s_STYLE_WINDOW_TITLE_ALIGN;
static PyObject *__pyx_n_s_StaticGlyphRanges;
static PyObject *__pyx_kp_s_Style_value_must_be_float_or_two;
static PyObject *__pyx_n_s_TREE_NODE_ALLOW_ITEM_OVERLAP;
static PyObject *__pyx_n_s_TREE_NODE_BULLET;
static PyObject *__pyx_n_s_TREE_NODE_COLLAPSING_HEADER;
static PyObject *__pyx_n_s_TREE_NODE_DEFAULT_OPEN;
static PyObject *__pyx_n_s_TREE_NODE_FRAMED;
static PyObject *__pyx_n_s_TREE_NODE_FRAME_PADDING;
static PyObject *__pyx_n_s_TREE_NODE_LEAF;
static PyObject *__pyx_n_s_TREE_NODE_NO_AUTO_OPEN_ON_LOG;
static PyObject *__pyx_n_s_TREE_NODE_NO_TREE_PUSH_ON_OPEN;
static PyObject *__pyx_n_s_TREE_NODE_OPEN_ON_ARROW;
static PyObject *__pyx_n_s_TREE_NODE_OPEN_ON_DOUBLE_CLICK;
static PyObject *__pyx_n_s_TREE_NODE_SELECTED;
static PyObject *__pyx_n_s_TypeError;
static PyObject *__pyx_kp_s_Unable_to_convert_item_to_object;
static PyObject *__pyx_kp_s_Unknown_style_variable;
static PyObject *__pyx_kp_s_Unsufficient_style_info_variable;
static PyObject *__pyx_n_s_ValueError;
static PyObject *__pyx_n_s_Vec2;
static PyObject *__pyx_n_s_Vec4;
static PyObject *__pyx_n_s_View_MemoryView;
static PyObject *__pyx_n_s_WINDOW_ALWAYS_AUTO_RESIZE;
static PyObject *__pyx_n_s_WINDOW_ALWAYS_HORIZONTAL_SCROLLB;
static PyObject *__pyx_n_s_WINDOW_ALWAYS_USE_WINDOW_PADDING;
static PyObject *__pyx_n_s_WINDOW_ALWAYS_VERTICAL_SCROLLBAR;
static PyObject *__pyx_n_s_WINDOW_HORIZONTAL_SCROLLING_BAR;
static PyObject *__pyx_n_s_WINDOW_MENU_BAR;
static PyObject *__pyx_n_s_WINDOW_NO_BRING_TO_FRONT_ON_FOCU;
static PyObject *__pyx_n_s_WINDOW_NO_COLLAPSE;
static PyObject *__pyx_n_s_WINDOW_NO_FOCUS_ON_APPEARING;
static PyObject *__pyx_n_s_WINDOW_NO_INPUTS;
static PyObject *__pyx_n_s_WINDOW_NO_MOVE;
static PyObject *__pyx_n_s_WINDOW_NO_NAV;
static PyObject *__pyx_n_s_WINDOW_NO_NAV_FOCUS;
static PyObject *__pyx_n_s_WINDOW_NO_NAV_INPUTS;
static PyObject *__pyx_n_s_WINDOW_NO_RESIZE;
static PyObject *__pyx_n_s_WINDOW_NO_SAVED_SETTINGS;
static PyObject *__pyx_n_s_WINDOW_NO_SCROLLBAR;
static PyObject *__pyx_n_s_WINDOW_NO_SCROLL_WITH_MOUSE;
static PyObject *__pyx_n_s_WINDOW_NO_TITLE_BAR;
static PyObject *__pyx_kp_s__32;
static PyObject *__pyx_kp_s__33;
static PyObject *__pyx_kp_s__34;
static PyObject *__pyx_kp_s__50;
static PyObject *__pyx_n_s_a;
static PyObject *__pyx_n_s_accept_drag_drop_payload;
static PyObject *__pyx_n_s_active;
static PyObject *__pyx_n_s_align_text_to_frame_padding;
static PyObject *__pyx_n_s_allocate_buffer;
static PyObject *__pyx_n_s_alpha;
static PyObject *__pyx_n_s_alpha_mul;
static PyObject *__pyx_n_s_also_over_items;
static PyObject *__pyx_n_s_ansifeed_text_ansi;
static PyObject *__pyx_n_s_ansifeed_text_ansi_colored;
static PyObject *__pyx_n_s_args;
static PyObject *__pyx_n_s_arrow_button;
static PyObject *__pyx_n_s_b;
static PyObject *__pyx_n_s_base;
static PyObject *__pyx_n_s_begin;
static PyObject *__pyx_n_s_begin_child;
static PyObject *__pyx_n_s_begin_drag_drop_source;
static PyObject *__pyx_n_s_begin_drag_drop_target;
static PyObject *__pyx_n_s_begin_group;
static PyObject *__pyx_n_s_begin_main_menu_bar;
static PyObject *__pyx_n_s_begin_menu;
static PyObject *__pyx_n_s_begin_menu_bar;
static PyObject *__pyx_n_s_begin_popup;
static PyObject *__pyx_n_s_begin_popup_context_item;
static PyObject *__pyx_n_s_begin_popup_context_window;
static PyObject *__pyx_n_s_begin_popup_modal;
static PyObject *__pyx_n_s_begin_tooltip;
static PyObject *__pyx_n_s_border;
static PyObject *__pyx_n_s_border_color;
static PyObject *__pyx_n_s_buffer_length;
static PyObject *__pyx_n_s_bullet;
static PyObject *__pyx_n_s_bullet_text;
static PyObject *__pyx_n_s_button;
static PyObject *__pyx_n_s_c;
static PyObject *__pyx_n_u_c;
static PyObject *__pyx_n_s_c_string;
static PyObject *__pyx_n_s_center_y_ratio;
static PyObject *__pyx_n_s_centre_x;
static PyObject *__pyx_n_s_centre_y;
static PyObject *__pyx_n_s_change_speed;
static PyObject *__pyx_n_s_changed;
static PyObject *__pyx_n_s_checkbox;
static PyObject *__pyx_n_s_checkbox_flags;
static PyObject *__pyx_n_s_class;
static PyObject *__pyx_n_s_clicked;
static PyObject *__pyx_n_s_cline_in_traceback;
static PyObject *__pyx_n_s_clip;
static PyObject *__pyx_n_s_closable;
static PyObject *__pyx_n_s_close;
static PyObject *__pyx_n_s_close_current_popup;
static PyObject *__pyx_n_s_closed;
static PyObject *__pyx_n_s_col;
static PyObject *__pyx_n_s_collapsed;
static PyObject *__pyx_n_s_collapsing_header;
static PyObject *__pyx_n_s_collections;
static PyObject *__pyx_n_s_color_button;
static PyObject *__pyx_n_s_color_edit3;
static PyObject *__pyx_n_s_color_edit4;
static PyObject *__pyx_n_s_column_index;
static PyObject *__pyx_n_s_columns;
static PyObject *__pyx_n_s_combo;
static PyObject *__pyx_n_s_condition;
static PyObject *__pyx_n_s_contextlib;
static PyObject *__pyx_n_s_contextmanager;
static PyObject *__pyx_kp_s_contiguous_and_direct;
static PyObject *__pyx_kp_s_contiguous_and_indirect;
static PyObject *__pyx_n_s_core;
static PyObject *__pyx_kp_s_core_pyx;
static PyObject *__pyx_n_s_count;
static PyObject *__pyx_n_s_create;
static PyObject *__pyx_n_s_create_context;
static PyObject *__pyx_n_s_ctx;
static PyObject *__pyx_n_s_current;
static PyObject *__pyx_kp_s_d;
static PyObject *__pyx_n_s_data;
static PyObject *__pyx_n_s_decode;
static PyObject *__pyx_n_s_defaults;
static PyObject *__pyx_n_s_desc_id;
static PyObject *__pyx_n_s_destroy_context;
static PyObject *__pyx_n_s_dict;
static PyObject *__pyx_n_s_direction;
static PyObject *__pyx_n_s_drag_float;
static PyObject *__pyx_n_s_drag_float2;
static PyObject *__pyx_n_s_drag_float3;
static PyObject *__pyx_n_s_drag_float4;
static PyObject *__pyx_n_s_drag_int;
static PyObject *__pyx_n_s_drag_int2;
static PyObject *__pyx_n_s_drag_int3;
static PyObject *__pyx_n_s_drag_int4;
static PyObject *__pyx_n_s_dst;
static PyObject *__pyx_n_s_dtype_is_object;
static PyObject *__pyx_n_s_dummy;
static PyObject *__pyx_n_s_enabled;
static PyObject *__pyx_n_s_encode;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_end_child;
static PyObject *__pyx_n_s_end_drag_drop_source;
static PyObject *__pyx_n_s_end_drag_drop_target;
static PyObject *__pyx_n_s_end_frame;
static PyObject *__pyx_n_s_end_group;
static PyObject *__pyx_n_s_end_main_menu_bar;
static PyObject *__pyx_n_s_end_menu;
static PyObject *__pyx_n_s_end_menu_bar;
static PyObject *__pyx_n_s_end_popup;
static PyObject *__pyx_n_s_end_tooltip;
static PyObject *__pyx_n_s_end_x;
static PyObject *__pyx_n_s_end_y;
static PyObject *__pyx_n_s_enumerate;
static PyObject *__pyx_n_s_error;
static PyObject *__pyx_n_s_errors;
static PyObject *__pyx_kp_s_f;
static PyObject *__pyx_n_s_filename;
static PyObject *__pyx_n_s_fillvalue;
static PyObject *__pyx_n_s_flags;
static PyObject *__pyx_n_s_flags_value;
static PyObject *__pyx_n_s_font;
static PyObject *__pyx_n_s_format;
static PyObject *__pyx_n_s_fortran;
static PyObject *__pyx_n_u_fortran;
static PyObject *__pyx_n_s_fraction;
static PyObject *__pyx_n_s_frame_padding;
static PyObject *__pyx_kp_s_func_is_not_a_callable_s;
static PyObject *__pyx_n_s_g;
static PyObject *__pyx_n_s_get_clipboard_text_fn;
static PyObject *__pyx_n_s_get_column_index;
static PyObject *__pyx_n_s_get_column_offset;
static PyObject *__pyx_n_s_get_column_width;
static PyObject *__pyx_n_s_get_columns_count;
static PyObject *__pyx_n_s_get_content_region_available;
static PyObject *__pyx_n_s_get_content_region_available_wid;
static PyObject *__pyx_n_s_get_content_region_max;
static PyObject *__pyx_n_s_get_current_context;
static PyObject *__pyx_n_s_get_cursor_pos;
static PyObject *__pyx_n_s_get_cursor_pos_x;
static PyObject *__pyx_n_s_get_cursor_pos_y;
static PyObject *__pyx_n_s_get_cursor_position;
static PyObject *__pyx_n_s_get_cursor_screen_pos;
static PyObject *__pyx_n_s_get_cursor_screen_position;
static PyObject *__pyx_n_s_get_cursor_start_pos;
static PyObject *__pyx_n_s_get_cursor_start_position;
static PyObject *__pyx_n_s_get_draw_data;
static PyObject *__pyx_n_s_get_frame_height;
static PyObject *__pyx_n_s_get_frame_height_with_spacing;
static PyObject *__pyx_n_s_get_io;
static PyObject *__pyx_n_s_get_item_rect_max;
static PyObject *__pyx_n_s_get_item_rect_min;
static PyObject *__pyx_n_s_get_item_rect_size;
static PyObject *__pyx_n_s_get_key_index;
static PyObject *__pyx_n_s_get_mouse_cursor;
static PyObject *__pyx_n_s_get_mouse_drag_delta;
static PyObject *__pyx_n_s_get_mouse_pos;
static PyObject *__pyx_n_s_get_mouse_position;
static PyObject *__pyx_n_s_get_overlay_draw_list;
static PyObject *__pyx_n_s_get_scroll_max_x;
static PyObject *__pyx_n_s_get_scroll_max_y;
static PyObject *__pyx_n_s_get_scroll_x;
static PyObject *__pyx_n_s_get_scroll_y;
static PyObject *__pyx_n_s_get_style;
static PyObject *__pyx_n_s_get_style_color_name;
static PyObject *__pyx_n_s_get_text_line_height;
static PyObject *__pyx_n_s_get_text_line_height_with_spacin;
static PyObject *__pyx_n_s_get_time;
static PyObject *__pyx_n_s_get_version;
static PyObject *__pyx_n_s_get_window_content_region_max;
static PyObject *__pyx_n_s_get_window_content_region_min;
static PyObject *__pyx_n_s_get_window_content_region_width;
static PyObject *__pyx_n_s_get_window_draw_list;
static PyObject *__pyx_n_s_get_window_height;
static PyObject *__pyx_n_s_get_window_position;
static PyObject *__pyx_n_s_get_window_size;
static PyObject *__pyx_n_s_get_window_width;
static PyObject *__pyx_n_s_getstate;
static PyObject *__pyx_n_s_glyph_ranges;
static PyObject *__pyx_kp_s_got_differing_extents_in_dimensi;
static PyObject *__pyx_n_s_graph_size;
static PyObject *__pyx_n_s_gui_style;
static PyObject *__pyx_n_s_height;
static PyObject *__pyx_n_s_height_in_items;
static PyObject *__pyx_n_s_hide_text_after_double_hash;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_n_s_id;
static PyObject *__pyx_n_s_identifier;
static PyObject *__pyx_n_s_idx;
static PyObject *__pyx_n_s_ignore;
static PyObject *__pyx_n_s_image;
static PyObject *__pyx_n_s_image_button;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_in_items;
static PyObject *__pyx_n_s_indent;
static PyObject *__pyx_n_s_index;
static PyObject *__pyx_n_s_inout_color;
static PyObject *__pyx_n_s_inout_current;
static PyObject *__pyx_n_s_inout_flags;
static PyObject *__pyx_n_s_inout_opened;
static PyObject *__pyx_n_s_inout_selected;
static PyObject *__pyx_n_s_inout_state;
static PyObject *__pyx_n_s_inout_text;
static PyObject *__pyx_n_s_inout_value;
static PyObject *__pyx_n_s_inout_values;
static PyObject *__pyx_n_s_inout_visible;
static PyObject *__pyx_n_s_input_double;
static PyObject *__pyx_n_s_input_float;
static PyObject *__pyx_n_s_input_float2;
static PyObject *__pyx_n_s_input_float3;
static PyObject *__pyx_n_s_input_float4;
static PyObject *__pyx_n_s_input_int;
static PyObject *__pyx_n_s_input_int2;
static PyObject *__pyx_n_s_input_int3;
static PyObject *__pyx_n_s_input_int4;
static PyObject *__pyx_n_s_input_text;
static PyObject *__pyx_n_s_input_text_multiline;
static PyObject *__pyx_n_s_invisible_button;
static PyObject *__pyx_n_s_io_clipboard;
static PyObject *__pyx_n_s_is_any_item_active;
static PyObject *__pyx_n_s_is_any_item_focused;
static PyObject *__pyx_n_s_is_any_item_hovered;
static PyObject *__pyx_n_s_is_item_active;
static PyObject *__pyx_n_s_is_item_clicked;
static PyObject *__pyx_n_s_is_item_focused;
static PyObject *__pyx_n_s_is_item_hovered;
static PyObject *__pyx_n_s_is_item_visible;
static PyObject *__pyx_n_s_is_key_down;
static PyObject *__pyx_n_s_is_key_pressed;
static PyObject *__pyx_n_s_is_mouse_clicked;
static PyObject *__pyx_n_s_is_mouse_double_clicked;
static PyObject *__pyx_n_s_is_mouse_down;
static PyObject *__pyx_n_s_is_mouse_dragging;
static PyObject *__pyx_n_s_is_mouse_hovering_rect;
static PyObject *__pyx_n_s_is_mouse_released;
static PyObject *__pyx_n_s_is_rect_visible;
static PyObject *__pyx_n_s_is_window_appearing;
static PyObject *__pyx_n_s_is_window_collapsed;
static PyObject *__pyx_n_s_is_window_focused;
static PyObject *__pyx_n_s_is_window_hovered;
static PyObject *__pyx_n_s_item;
static PyObject *__pyx_n_s_items;
static PyObject *__pyx_n_s_itemsize;
static PyObject *__pyx_kp_s_itemsize_0_for_cython_array;
static PyObject *__pyx_n_s_iterator;
static PyObject *__pyx_n_s_itertools;
static PyObject *__pyx_n_s_izip_longest;
static PyObject *__pyx_n_s_join;
static PyObject *__pyx_n_s_key;
static PyObject *__pyx_n_s_key_index;
static PyObject *__pyx_n_s_kwargs;
static PyObject *__pyx_n_s_label;
static PyObject *__pyx_n_s_label_text;
static PyObject *__pyx_n_s_listbox;
static PyObject *__pyx_n_s_listbox_footer;
static PyObject *__pyx_n_s_listbox_header;
static PyObject *__pyx_n_s_local_pos;
static PyObject *__pyx_n_s_lock_threshold;
static PyObject *__pyx_n_s_lower_right_x;
static PyObject *__pyx_n_s_lower_right_y;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_max_value;
static PyObject *__pyx_n_s_memview;
static PyObject *__pyx_n_s_menu_item;
static PyObject *__pyx_n_s_min_value;
static PyObject *__pyx_n_s_mode;
static PyObject *__pyx_n_s_mouse_button;
static PyObject *__pyx_n_s_mouse_cursor_type;
static PyObject *__pyx_n_s_name;
static PyObject *__pyx_n_s_name_2;
static PyObject *__pyx_n_s_namedtuple;
static PyObject *__pyx_n_s_ndim;
static PyObject *__pyx_n_s_new;
static PyObject *__pyx_n_s_new_frame;
static PyObject *__pyx_n_s_new_line;
static PyObject *__pyx_n_s_next_column;
static PyObject *__pyx_kp_s_no_default___reduce___due_to_non;
static PyObject *__pyx_n_s_num_segments;
static PyObject *__pyx_n_s_numpy;
static PyObject *__pyx_n_s_obj;
static PyObject *__pyx_n_s_offset;
static PyObject *__pyx_n_s_offset_x;
static PyObject *__pyx_n_s_open_popup;
static PyObject *__pyx_n_s_opened;
static PyObject *__pyx_n_s_output;
static PyObject *__pyx_n_s_overlay;
static PyObject *__pyx_n_s_overlay_text;
static PyObject *__pyx_n_s_overlay_text_b;
static PyObject *__pyx_n_s_overlay_text_ptr;
static PyObject *__pyx_n_s_pack;
static PyObject *__pyx_kp_s_pair_param_must_be_length_of_2;
static PyObject *__pyx_n_s_payload;
static PyObject *__pyx_n_s_pickle;
static PyObject *__pyx_n_s_pivot_x;
static PyObject *__pyx_n_s_pivot_y;
static PyObject *__pyx_n_s_plot_histogram;
static PyObject *__pyx_n_s_plot_lines;
static PyObject *__pyx_n_s_points;
static PyObject *__pyx_n_s_pop_font;
static PyObject *__pyx_n_s_pop_id;
static PyObject *__pyx_n_s_pop_text_wrap_pos;
static PyObject *__pyx_n_s_pop_text_wrap_position;
static PyObject *__pyx_n_s_pos_x;
static PyObject *__pyx_n_s_pos_y;
static PyObject *__pyx_n_s_position;
static PyObject *__pyx_n_s_power;
static PyObject *__pyx_n_s_progress_bar;
static PyObject *__pyx_n_s_ptr;
static PyObject *__pyx_n_s_push_font;
static PyObject *__pyx_n_s_push_id;
static PyObject *__pyx_n_s_push_text_wrap_pos;
static PyObject *__pyx_n_s_push_text_wrap_position;
static PyObject *__pyx_n_s_py_colored;
static PyObject *__pyx_n_s_py_font;
static PyObject *__pyx_n_s_py_index_buffer_index_size;
static PyObject *__pyx_n_s_py_istyled;
static PyObject *__pyx_n_s_py_scoped;
static PyObject *__pyx_n_s_py_string;
static PyObject *__pyx_n_s_py_styled;
static PyObject *__pyx_n_s_py_vertex_buffer_vertex_col_off;
static PyObject *__pyx_n_s_py_vertex_buffer_vertex_pos_off;
static PyObject *__pyx_n_s_py_vertex_buffer_vertex_size;
static PyObject *__pyx_n_s_py_vertex_buffer_vertex_uv_offs;
static PyObject *__pyx_n_s_pyx_PickleError;
static PyObject *__pyx_n_s_pyx_checksum;
static PyObject *__pyx_n_s_pyx_getbuffer;
static PyObject *__pyx_n_s_pyx_result;
static PyObject *__pyx_n_s_pyx_state;
static PyObject *__pyx_n_s_pyx_type;
static PyObject *__pyx_n_s_pyx_unpickle_Enum;
static PyObject *__pyx_n_s_pyx_vtable;
static PyObject *__pyx_kp_s_quadruple_param_must_be_length_o;
static PyObject *__pyx_n_s_r;
static PyObject *__pyx_n_s_r_max_x;
static PyObject *__pyx_n_s_r_max_y;
static PyObject *__pyx_n_s_r_min_x;
static PyObject *__pyx_n_s_r_min_y;
static PyObject *__pyx_n_s_radio_button;
static PyObject *__pyx_n_s_radius;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_reduce;
static PyObject *__pyx_n_s_reduce_cython;
static PyObject *__pyx_n_s_reduce_ex;
static PyObject *__pyx_n_s_render;
static PyObject *__pyx_n_s_repeat;
static PyObject *__pyx_n_s_require_pointer;
static PyObject *__pyx_n_s_reset_mouse_drag_delta;
static PyObject *__pyx_n_s_rounding;
static PyObject *__pyx_n_s_rounding_corners_flags;
static PyObject *__pyx_kp_s_s_improperly_initialized;
static PyObject *__pyx_n_s_same_line;
static PyObject *__pyx_n_s_scale;
static PyObject *__pyx_n_s_scale_max;
static PyObject *__pyx_n_s_scale_min;
static PyObject *__pyx_n_s_screen_pos;
static PyObject *__pyx_n_s_scroll_x;
static PyObject *__pyx_n_s_scroll_y;
static PyObject *__pyx_n_s_selectable;
static PyObject *__pyx_n_s_selected;
static PyObject *__pyx_kp_s_self__ptr_cannot_be_converted_to;
static PyObject *__pyx_kp_s_self_ranges_ptr_cannot_be_conver;
static PyObject *__pyx_n_s_send;
static PyObject *__pyx_n_s_separator;
static PyObject *__pyx_n_s_set_clipboard_text_fn;
static PyObject *__pyx_n_s_set_column_offset;
static PyObject *__pyx_n_s_set_column_width;
static PyObject *__pyx_n_s_set_current_context;
static PyObject *__pyx_n_s_set_cursor_pos;
static PyObject *__pyx_n_s_set_cursor_pos_x;
static PyObject *__pyx_n_s_set_cursor_pos_y;
static PyObject *__pyx_n_s_set_cursor_position;
static PyObject *__pyx_n_s_set_cursor_screen_pos;
static PyObject *__pyx_n_s_set_cursor_screen_position;
static PyObject *__pyx_n_s_set_drag_drop_payload;
static PyObject *__pyx_n_s_set_item_allow_overlap;
static PyObject *__pyx_n_s_set_item_default_focus;
static PyObject *__pyx_n_s_set_keyboard_focus_here;
static PyObject *__pyx_n_s_set_mouse_cursor;
static PyObject *__pyx_n_s_set_next_window_bg_alpha;
static PyObject *__pyx_n_s_set_next_window_collapsed;
static PyObject *__pyx_n_s_set_next_window_content_size;
static PyObject *__pyx_n_s_set_next_window_focus;
static PyObject *__pyx_n_s_set_next_window_position;
static PyObject *__pyx_n_s_set_next_window_size;
static PyObject *__pyx_n_s_set_scroll_from_pos_y;
static PyObject *__pyx_n_s_set_scroll_here;
static PyObject *__pyx_n_s_set_scroll_x;
static PyObject *__pyx_n_s_set_scroll_y;
static PyObject *__pyx_n_s_set_tooltip;
static PyObject *__pyx_n_s_set_window_collapsed;
static PyObject *__pyx_n_s_set_window_collapsed_labeled;
static PyObject *__pyx_n_s_set_window_focus;
static PyObject *__pyx_n_s_set_window_focus_labeled;
static PyObject *__pyx_n_s_set_window_font_scale;
static PyObject *__pyx_n_s_set_window_position;
static PyObject *__pyx_n_s_set_window_position_labeled;
static PyObject *__pyx_n_s_set_window_size;
static PyObject *__pyx_n_s_set_window_size_named;
static PyObject *__pyx_n_s_setstate;
static PyObject *__pyx_n_s_setstate_cython;
static PyObject *__pyx_n_s_shape;
static PyObject *__pyx_n_s_shared_font_atlas;
static PyObject *__pyx_n_s_shortcut;
static PyObject *__pyx_n_s_show_alpha;
static PyObject *__pyx_n_s_show_demo_window;
static PyObject *__pyx_n_s_show_font_selector;
static PyObject *__pyx_n_s_show_metrics_window;
static PyObject *__pyx_n_s_show_style_editor;
static PyObject *__pyx_n_s_show_style_selector;
static PyObject *__pyx_n_s_show_test_window;
static PyObject *__pyx_n_s_show_user_guide;
static PyObject *__pyx_n_s_signatures;
static PyObject *__pyx_n_s_size;
static PyObject *__pyx_n_s_size_height;
static PyObject *__pyx_n_s_size_pixels;
static PyObject *__pyx_n_s_size_width;
static PyObject *__pyx_n_s_slider_angle;
static PyObject *__pyx_n_s_slider_float;
static PyObject *__pyx_n_s_slider_float2;
static PyObject *__pyx_n_s_slider_float3;
static PyObject *__pyx_n_s_slider_float4;
static PyObject *__pyx_n_s_slider_int;
static PyObject *__pyx_n_s_slider_int2;
static PyObject *__pyx_n_s_slider_int3;
static PyObject *__pyx_n_s_slider_int4;
static PyObject *__pyx_n_s_small_button;
static PyObject *__pyx_n_s_spacing;
static PyObject *__pyx_n_s_split;
static PyObject *__pyx_n_s_start;
static PyObject *__pyx_n_s_start_x;
static PyObject *__pyx_n_s_start_y;
static PyObject *__pyx_n_s_state;
static PyObject *__pyx_n_s_staticmethod;
static PyObject *__pyx_n_s_step;
static PyObject *__pyx_n_s_step_fast;
static PyObject *__pyx_n_s_stop;
static PyObject *__pyx_n_s_str;
static PyObject *__pyx_n_s_str_id;
static PyObject *__pyx_n_s_stride;
static PyObject *__pyx_kp_s_strided_and_direct;
static PyObject *__pyx_kp_s_strided_and_direct_or_indirect;
static PyObject *__pyx_kp_s_strided_and_indirect;
static PyObject *__pyx_kp_s_stringsource;
static PyObject *__pyx_n_s_strip;
static PyObject *__pyx_n_s_struct;
static PyObject *__pyx_n_s_style;
static PyObject *__pyx_n_s_style_colors_classic;
static PyObject *__pyx_n_s_style_colors_dark;
static PyObject *__pyx_n_s_style_colors_light;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_text;
static PyObject *__pyx_n_s_text_colored;
static PyObject *__pyx_n_s_text_disabled;
static PyObject *__pyx_n_s_text_unformatted;
static PyObject *__pyx_n_s_text_wrapped;
static PyObject *__pyx_n_s_texture_id;
static PyObject *__pyx_n_s_thickness;
static PyObject *__pyx_n_s_throw;
static PyObject *__pyx_n_s_tint_color;
static PyObject *__pyx_n_s_title;
static PyObject *__pyx_n_s_tree_node;
static PyObject *__pyx_n_s_tree_pop;
static PyObject *__pyx_n_s_type;
static PyObject *__pyx_kp_s_unable_to_allocate_array_data;
static PyObject *__pyx_kp_s_unable_to_allocate_shape_and_str;
static PyObject *__pyx_n_s_unindent;
static PyObject *__pyx_n_s_unpack;
static PyObject *__pyx_n_s_update;
static PyObject *__pyx_n_s_upper_left_x;
static PyObject *__pyx_n_s_upper_left_y;
static PyObject *__pyx_kp_s_utf_8;
static PyObject *__pyx_n_s_uv0;
static PyObject *__pyx_n_s_uv1;
static PyObject *__pyx_n_s_uv_a;
static PyObject *__pyx_n_s_uv_b;
static PyObject *__pyx_n_s_v_slider_float;
static PyObject *__pyx_n_s_v_slider_int;
static PyObject *__pyx_n_s_val;
static PyObject *__pyx_n_s_value;
static PyObject *__pyx_n_s_value0;
static PyObject *__pyx_n_s_value1;
static PyObject *__pyx_n_s_value2;
static PyObject *__pyx_n_s_value3;
static PyObject *__pyx_n_s_values;
static PyObject *__pyx_n_s_values_count;
static PyObject *__pyx_n_s_values_offset;
static PyObject *__pyx_n_s_var;
static PyObject *__pyx_n_s_variable;
static PyObject *__pyx_n_s_variables_and_values;
static PyObject *__pyx_n_s_visible;
static PyObject *__pyx_n_s_w;
static PyObject *__pyx_n_s_warn;
static PyObject *__pyx_n_s_warnings;
static PyObject *__pyx_n_s_width;
static PyObject *__pyx_n_s_wrap_pos_x;
static PyObject *__pyx_n_s_wrap_width;
static PyObject *__pyx_n_s_x;
static PyObject *__pyx_n_s_xrange;
static PyObject *__pyx_n_s_y;
static PyObject *__pyx_n_s_z;
static PyObject *__pyx_n_s_zip_longest;
static PyObject *__pyx_pf_4core_13_ImGuiContext___eq__(struct __pyx_obj_4core__ImGuiContext *__pyx_v_self, struct __pyx_obj_4core__ImGuiContext *__pyx_v_other); /* proto */
static PyObject *__pyx_pf_4core_13_ImGuiContext_2__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__ImGuiContext *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_13_ImGuiContext_4__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__ImGuiContext *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_4core_8_DrawCmd_10texture_id___get__(struct __pyx_obj_4core__DrawCmd *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8_DrawCmd_9clip_rect___get__(struct __pyx_obj_4core__DrawCmd *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8_DrawCmd_10elem_count___get__(struct __pyx_obj_4core__DrawCmd *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8_DrawCmd___reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__DrawCmd *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8_DrawCmd_2__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__DrawCmd *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_15cmd_buffer_size___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_15cmd_buffer_data___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_15vtx_buffer_size___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_15vtx_buffer_data___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_15idx_buffer_size___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_15idx_buffer_data___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_add_line(struct __pyx_obj_4core__DrawList *__pyx_v_self, float __pyx_v_start_x, float __pyx_v_start_y, float __pyx_v_end_x, float __pyx_v_end_y, ImU32 __pyx_v_col, float __pyx_v_thickness); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_2add_rect(struct __pyx_obj_4core__DrawList *__pyx_v_self, float __pyx_v_upper_left_x, float __pyx_v_upper_left_y, float __pyx_v_lower_right_x, float __pyx_v_lower_right_y, ImU32 __pyx_v_col, float __pyx_v_rounding, ImGuiWindowFlags __pyx_v_rounding_corners_flags, float __pyx_v_thickness); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_4add_rect_filled(struct __pyx_obj_4core__DrawList *__pyx_v_self, float __pyx_v_upper_left_x, float __pyx_v_upper_left_y, float __pyx_v_lower_right_x, float __pyx_v_lower_right_y, ImU32 __pyx_v_col, float __pyx_v_rounding, ImGuiWindowFlags __pyx_v_rounding_corners_flags); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_6add_circle(struct __pyx_obj_4core__DrawList *__pyx_v_self, float __pyx_v_centre_x, float __pyx_v_centre_y, float __pyx_v_radius, ImU32 __pyx_v_col, int __pyx_v_num_segments, float __pyx_v_thickness); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_8add_circle_filled(struct __pyx_obj_4core__DrawList *__pyx_v_self, float __pyx_v_centre_x, float __pyx_v_centre_y, float __pyx_v_radius, ImU32 __pyx_v_col, ImU32 __pyx_v_num_segments); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_10add_text(struct __pyx_obj_4core__DrawList *__pyx_v_self, float __pyx_v_pos_x, float __pyx_v_pos_y, ImU32 __pyx_v_col, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_12add_image(struct __pyx_obj_4core__DrawList *__pyx_v_self, PyObject *__pyx_v_texture_id, PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_uv_a, PyObject *__pyx_v_uv_b, ImU32 __pyx_v_col); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_14add_polyline(struct __pyx_obj_4core__DrawList *__pyx_v_self, PyObject *__pyx_v_points, ImU32 __pyx_v_col, bool __pyx_v_closed, float __pyx_v_thickness); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_16channels_split(struct __pyx_obj_4core__DrawList *__pyx_v_self, int __pyx_v_channels_count); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_18channels_set_current(struct __pyx_obj_4core__DrawList *__pyx_v_self, int __pyx_v_idx); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_20channels_merge(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_8commands___get__(struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_22__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__DrawList *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawList_24__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__DrawList *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_pf_4core_7_Colors___cinit__(struct __pyx_obj_4core__Colors *__pyx_v_self); /* proto */
static int __pyx_pf_4core_7_Colors_2__init__(struct __pyx_obj_4core__Colors *__pyx_v_self, struct __pyx_obj_4core_GuiStyle *__pyx_v_gui_style); /* proto */
static PyObject *__pyx_pf_4core_7_Colors_4__getitem__(struct __pyx_obj_4core__Colors *__pyx_v_self, ImGuiCol __pyx_v_variable); /* proto */
static int __pyx_pf_4core_7_Colors_6__setitem__(struct __pyx_obj_4core__Colors *__pyx_v_self, ImGuiCol __pyx_v_variable, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_7_Colors_8__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__Colors *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_7_Colors_10__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__Colors *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_pf_4core_8GuiStyle___cinit__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static void __pyx_pf_4core_8GuiStyle_2__dealloc__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_4__eq__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, struct __pyx_obj_4core_GuiStyle *__pyx_v_other); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_6create(void); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_5alpha___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_5alpha_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_14window_padding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_14window_padding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_15window_min_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_15window_min_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_15window_rounding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_15window_rounding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_18window_border_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_18window_border_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_14child_rounding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_14child_rounding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_17child_border_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_17child_border_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_14popup_rounding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_14popup_rounding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_17popup_border_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_17popup_border_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_18window_title_align___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_18window_title_align_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_13frame_padding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_13frame_padding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_14frame_rounding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_14frame_rounding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_17frame_border_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_17frame_border_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_12item_spacing___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_12item_spacing_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_18item_inner_spacing___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_18item_inner_spacing_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_19touch_extra_padding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_19touch_extra_padding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_14indent_spacing___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_14indent_spacing_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_19columns_min_spacing___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_19columns_min_spacing_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_14scrollbar_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_14scrollbar_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_18scrollbar_rounding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_18scrollbar_rounding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_13grab_min_size___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_13grab_min_size_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_13grab_rounding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_13grab_rounding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_17button_text_align___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_17button_text_align_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_22display_window_padding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_22display_window_padding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_25display_safe_area_padding___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_25display_safe_area_padding_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_18mouse_cursor_scale___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_18mouse_cursor_scale_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_18anti_aliased_lines___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_18anti_aliased_lines_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_17anti_aliased_fill___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_17anti_aliased_fill_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_28curve_tessellation_tolerance___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static int __pyx_pf_4core_8GuiStyle_28curve_tessellation_tolerance_2__set__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_8color(struct __pyx_obj_4core_GuiStyle *__pyx_v_self, ImGuiCol __pyx_v_variable); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_6colors___get__(struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_10__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core_GuiStyle *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_8GuiStyle_12__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core_GuiStyle *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_pf_4core_9_DrawData___init__(CYTHON_UNUSED struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_2_require_pointer(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_4deindex_all_buffers(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_6scale_clip_rects(struct __pyx_obj_4core__DrawData *__pyx_v_self, PyObject *__pyx_v_width, PyObject *__pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_5valid___get__(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_9cmd_count___get__(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_15total_vtx_count___get__(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_15total_idx_count___get__(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_14commands_lists___get__(struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_8__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__DrawData *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_9_DrawData_10__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__DrawData *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_4core_18_StaticGlyphRanges___reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__StaticGlyphRanges *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_18_StaticGlyphRanges_2__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__StaticGlyphRanges *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_4core_5_Font___reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__Font *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_5_Font_2__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__Font *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_pf_4core_10_FontAtlas___init__(CYTHON_UNUSED struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_2_require_pointer(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_4add_font_default(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_6add_font_from_file_ttf(struct __pyx_obj_4core__FontAtlas *__pyx_v_self, PyObject *__pyx_v_filename, float __pyx_v_size_pixels, struct __pyx_obj_4core__StaticGlyphRanges *__pyx_v_glyph_ranges); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_8clear_tex_data(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_10clear_input_data(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_12clear_fonts(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_14clear(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_16get_glyph_ranges_default(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_18get_glyph_ranges_korean(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_20get_glyph_ranges_japanese(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_22get_glyph_ranges_chinese_full(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_24get_glyph_ranges_chinese(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_26get_glyph_ranges_cyrillic(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_28get_glyph_ranges_latin(CYTHON_UNUSED struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_30get_tex_data_as_alpha8(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_32get_tex_data_as_rgba32(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_10texture_id___get__(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static int __pyx_pf_4core_10_FontAtlas_10texture_id_2__set__(struct __pyx_obj_4core__FontAtlas *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_13texture_width___get__(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_14texture_height___get__(struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_34__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__FontAtlas *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_10_FontAtlas_36__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__FontAtlas *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_pf_4core_3_IO___init__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_12config_flags___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_12config_flags_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, ImGuiConfigFlags __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_13backend_flags___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_13backend_flags_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, ImGuiBackendFlags __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_12display_size___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_12display_size_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_10delta_time___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_10delta_time_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_time); /* proto */
static PyObject *__pyx_pf_4core_3_IO_15ini_saving_rate___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_15ini_saving_rate_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_13log_file_name___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_13log_file_name_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, char *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_13ini_file_name___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_13ini_file_name_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, char *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_23mouse_double_click_time___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_23mouse_double_click_time_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_31mouse_double_click_max_distance___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_31mouse_double_click_max_distance_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_20mouse_drag_threshold___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_20mouse_drag_threshold_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_7key_map___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_16key_repeat_delay___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_16key_repeat_delay_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_15key_repeat_rate___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_15key_repeat_rate_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_5fonts___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_17font_global_scale___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_17font_global_scale_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_23font_allow_user_scaling___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_23font_allow_user_scaling_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_16display_fb_scale___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_16display_fb_scale_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_19display_visible_min___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_19display_visible_min_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_19display_visible_max___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_19display_visible_max_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_24config_mac_osx_behaviors___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_24config_mac_osx_behaviors_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_19config_cursor_blink___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_19config_cursor_blink_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_32config_resize_windows_from_edges___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_32config_resize_windows_from_edges_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_21get_clipboard_text_fn___get__(CYTHON_UNUSED struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_21get_clipboard_text_fn_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_func); /* proto */
static PyObject *__pyx_pf_4core_3_IO_21set_clipboard_text_fn___get__(CYTHON_UNUSED struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_21set_clipboard_text_fn_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_func); /* proto */
static PyObject *__pyx_pf_4core_3_IO_9mouse_pos___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_9mouse_pos_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_10mouse_down___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_11mouse_wheel___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_11mouse_wheel_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_22mouse_wheel_horizontal___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_22mouse_wheel_horizontal_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, float __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_17mouse_draw_cursor___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_17mouse_draw_cursor_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_8key_ctrl___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_8key_ctrl_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_9key_shift___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_9key_shift_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_7key_alt___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_7key_alt_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_9key_super___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static int __pyx_pf_4core_3_IO_9key_super_2__set__(struct __pyx_obj_4core__IO *__pyx_v_self, bool __pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_3_IO_9keys_down___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_2add_input_character(struct __pyx_obj_4core__IO *__pyx_v_self, ImWchar __pyx_v_c); /* proto */
static PyObject *__pyx_pf_4core_3_IO_4add_input_characters_utf8(struct __pyx_obj_4core__IO *__pyx_v_self, PyObject *__pyx_v_utf8_chars); /* proto */
static PyObject *__pyx_pf_4core_3_IO_6clear_input_characters(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_18want_capture_mouse___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_21want_capture_keyboard___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_15want_text_input___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_18want_set_mouse_pos___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_21want_save_ini_setting___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_10nav_active___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_11nav_visible___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_9framerate___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_23metrics_render_vertices___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_22metrics_active_windows___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_11mouse_delta___get__(struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_8__reduce_cython__(CYTHON_UNUSED struct __pyx_obj_4core__IO *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_4core_3_IO_10__setstate_cython__(CYTHON_UNUSED struct __pyx_obj_4core__IO *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_4core_get_io(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_2get_style(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_4new_frame(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_6end_frame(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_8render(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_10show_user_guide(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_12get_version(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_14style_colors_dark(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core_GuiStyle *__pyx_v_dst); /* proto */
static PyObject *__pyx_pf_4core_16style_colors_classic(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core_GuiStyle *__pyx_v_dst); /* proto */
static PyObject *__pyx_pf_4core_18style_colors_light(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core_GuiStyle *__pyx_v_dst); /* proto */
static PyObject *__pyx_pf_4core_20show_style_editor(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core_GuiStyle *__pyx_v_style); /* proto */
static PyObject *__pyx_pf_4core_22show_demo_window(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_closable); /* proto */
static PyObject *__pyx_pf_4core_24show_test_window(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_26show_metrics_window(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_closable); /* proto */
static PyObject *__pyx_pf_4core_28show_style_selector(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label); /* proto */
static PyObject *__pyx_pf_4core_30show_font_selector(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label); /* proto */
static PyObject *__pyx_pf_4core_32begin(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_closable, ImGuiWindowFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_34get_draw_data(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_36end(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_38begin_child(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_signatures, PyObject *__pyx_v_args, PyObject *__pyx_v_kwargs, CYTHON_UNUSED PyObject *__pyx_v_defaults); /* proto */
static PyObject *__pyx_pf_4core_507__defaults__(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_497begin_child(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_width, float __pyx_v_height, bool __pyx_v_border, ImGuiWindowFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_509__defaults__(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_499begin_child(CYTHON_UNUSED PyObject *__pyx_self, ImGuiID __pyx_v_label, float __pyx_v_width, float __pyx_v_height, bool __pyx_v_border, ImGuiWindowFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_40end_child(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_42get_content_region_max(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_44get_content_region_available(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_46get_content_region_available_width(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_48get_window_content_region_min(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_50get_window_content_region_max(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_52get_window_content_region_width(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_54set_window_focus(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_56set_window_focus_labeled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label); /* proto */
static PyObject *__pyx_pf_4core_58set_window_size(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_width, float __pyx_v_height, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_60set_window_size_named(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_width, float __pyx_v_height, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_62get_scroll_x(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_64get_scroll_y(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_66get_scroll_max_x(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_68get_scroll_max_y(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_70set_scroll_x(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_scroll_x); /* proto */
static PyObject *__pyx_pf_4core_72set_scroll_y(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_scroll_y); /* proto */
static PyObject *__pyx_pf_4core_74set_window_font_scale(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_scale); /* proto */
static PyObject *__pyx_pf_4core_76set_next_window_collapsed(CYTHON_UNUSED PyObject *__pyx_self, bool __pyx_v_collapsed, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_78set_next_window_focus(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_80set_next_window_bg_alpha(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_alpha); /* proto */
static PyObject *__pyx_pf_4core_82get_window_draw_list(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_84get_overlay_draw_list(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_86get_window_position(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_88get_window_size(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_90get_window_width(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_92get_window_height(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_94set_next_window_position(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_x, float __pyx_v_y, ImGuiCond __pyx_v_condition, float __pyx_v_pivot_x, float __pyx_v_pivot_y); /* proto */
static PyObject *__pyx_pf_4core_96set_next_window_size(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_width, float __pyx_v_height, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_98set_next_window_content_size(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_width, float __pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_100set_window_position(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_x, float __pyx_v_y, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_102set_window_position_labeled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_x, float __pyx_v_y, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_104set_window_collapsed(CYTHON_UNUSED PyObject *__pyx_self, bool __pyx_v_collapsed, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_106set_window_collapsed_labeled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, bool __pyx_v_collapsed, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_108is_window_collapsed(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_110is_window_appearing(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_112tree_node(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text, ImGuiTreeNodeFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_114tree_pop(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_116collapsing_header(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text, PyObject *__pyx_v_visible, ImGuiTreeNodeFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_118selectable(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_selected, ImGuiTreeNodeFlags __pyx_v_flags, PyObject *__pyx_v_width, PyObject *__pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_120listbox(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_current, PyObject *__pyx_v_items, int __pyx_v_height_in_items); /* proto */
static PyObject *__pyx_pf_4core_122listbox_header(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_width, PyObject *__pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_124listbox_footer(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_126set_tooltip(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_128begin_tooltip(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_130end_tooltip(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_132begin_main_menu_bar(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_134end_main_menu_bar(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_136begin_menu_bar(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_138end_menu_bar(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_140begin_menu(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_enabled); /* proto */
static PyObject *__pyx_pf_4core_142end_menu(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_144menu_item(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_shortcut, bool __pyx_v_selected, PyObject *__pyx_v_enabled); /* proto */
static PyObject *__pyx_pf_4core_146open_popup(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label); /* proto */
static PyObject *__pyx_pf_4core_148begin_popup(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, ImGuiWindowFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_150begin_popup_modal(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_title, PyObject *__pyx_v_visible, ImGuiWindowFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_152begin_popup_context_item(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_mouse_button); /* proto */
static PyObject *__pyx_pf_4core_154begin_popup_context_window(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, bool __pyx_v_also_over_items, int __pyx_v_mouse_button); /* proto */
static PyObject *__pyx_pf_4core_156end_popup(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_158close_current_popup(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_160text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_162text_colored(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, float __pyx_v_a); /* proto */
static PyObject *__pyx_pf_4core_164text_disabled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_166text_wrapped(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_168label_text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_170text_unformatted(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_172bullet(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_174bullet_text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_176button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_width, PyObject *__pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_178small_button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label); /* proto */
static PyObject *__pyx_pf_4core_180arrow_button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, ImGuiDir __pyx_v_direction); /* proto */
static PyObject *__pyx_pf_4core_182invisible_button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_identifier, PyObject *__pyx_v_width, PyObject *__pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_184color_button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_desc_id, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, PyObject *__pyx_v_a, PyObject *__pyx_v_flags, float __pyx_v_width, float __pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_186image_button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_texture_id, float __pyx_v_width, float __pyx_v_height, PyObject *__pyx_v_uv0, PyObject *__pyx_v_uv1, PyObject *__pyx_v_tint_color, PyObject *__pyx_v_border_color, int __pyx_v_frame_padding); /* proto */
static PyObject *__pyx_pf_4core_188image(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_texture_id, float __pyx_v_width, float __pyx_v_height, PyObject *__pyx_v_uv0, PyObject *__pyx_v_uv1, PyObject *__pyx_v_tint_color, PyObject *__pyx_v_border_color); /* proto */
static PyObject *__pyx_pf_4core_190checkbox(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, bool __pyx_v_state); /* proto */
static PyObject *__pyx_pf_4core_192checkbox_flags(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, unsigned int __pyx_v_flags, unsigned int __pyx_v_flags_value); /* proto */
static PyObject *__pyx_pf_4core_194radio_button(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, bool __pyx_v_active); /* proto */
static PyObject *__pyx_pf_4core_196combo(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_current, PyObject *__pyx_v_items, int __pyx_v_height_in_items); /* proto */
static PyObject *__pyx_pf_4core_198color_edit3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, PyObject *__pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_200color_edit4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, float __pyx_v_a, bool __pyx_v_show_alpha, PyObject *__pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_202drag_float(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value, float __pyx_v_change_speed, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_204drag_float2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_change_speed, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_206drag_float3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_value2, float __pyx_v_change_speed, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_208drag_float4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_value2, float __pyx_v_value3, float __pyx_v_change_speed, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_210drag_int(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value, float __pyx_v_change_speed, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_212drag_int2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, float __pyx_v_change_speed, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_214drag_int3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_value2, float __pyx_v_change_speed, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_216drag_int4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_value2, int __pyx_v_value3, float __pyx_v_change_speed, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_218input_text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_value, int __pyx_v_buffer_length, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_220input_text_multiline(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_value, int __pyx_v_buffer_length, float __pyx_v_width, float __pyx_v_height, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_222input_float(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value, float __pyx_v_step, float __pyx_v_step_fast, PyObject *__pyx_v_format, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_224input_float2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, PyObject *__pyx_v_format, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_226input_float3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_value2, PyObject *__pyx_v_format, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_228input_float4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_value2, float __pyx_v_value3, PyObject *__pyx_v_format, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_230input_int(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value, int __pyx_v_step, int __pyx_v_step_fast, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_232input_int2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_234input_int3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_value2, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_236input_int4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_value2, int __pyx_v_value3, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_238input_double(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, double __pyx_v_value, double __pyx_v_step, double __pyx_v_step_fast, PyObject *__pyx_v_format, ImGuiInputTextFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_240slider_angle(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value, float __pyx_v_min_value, float __pyx_v_max_value); /* proto */
static PyObject *__pyx_pf_4core_242slider_float(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_244slider_float2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_246slider_float3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_value2, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_248slider_float4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_value0, float __pyx_v_value1, float __pyx_v_value2, float __pyx_v_value3, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_250slider_int(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_252slider_int2(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_254slider_int3(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_value2, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_256slider_int4(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value0, int __pyx_v_value1, int __pyx_v_value2, int __pyx_v_value3, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
static PyObject *__pyx_pf_4core_258v_slider_float(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_width, float __pyx_v_height, float __pyx_v_value, float __pyx_v_min_value, float __pyx_v_max_value, PyObject *__pyx_v_format, float __pyx_v_power); /* proto */
static PyObject *__pyx_pf_4core_260v_slider_int(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, float __pyx_v_width, float __pyx_v_height, int __pyx_v_value, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format); /* proto */
#if 0
static PyObject *__pyx_pf_4core_262plot_lines(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, __Pyx_memviewslice __pyx_v_values, int __pyx_v_values_count, int __pyx_v_values_offset, PyObject *__pyx_v_overlay_text, float __pyx_v_scale_min, float __pyx_v_scale_max, PyObject *__pyx_v_graph_size, int __pyx_v_stride); /* proto */
static PyObject *__pyx_pf_4core_264plot_histogram(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, __Pyx_memviewslice __pyx_v_values, int __pyx_v_values_count, int __pyx_v_values_offset, PyObject *__pyx_v_overlay_text, float __pyx_v_scale_min, float __pyx_v_scale_max, PyObject *__pyx_v_graph_size, int __pyx_v_stride); /* proto */
static PyObject *__pyx_pf_4core_266progress_bar(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_fraction, PyObject *__pyx_v_size, PyObject *__pyx_v_overlay); /* proto */
#endif
static PyObject *__pyx_pf_4core_268set_item_default_focus(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_270set_keyboard_focus_here(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_offset); /* proto */
static PyObject *__pyx_pf_4core_272is_item_hovered(CYTHON_UNUSED PyObject *__pyx_self, ImGuiHoveredFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_274is_item_focused(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_276is_item_active(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_278is_item_clicked(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_mouse_button); /* proto */
static PyObject *__pyx_pf_4core_280is_item_visible(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_282is_any_item_hovered(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_284is_any_item_active(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_286is_any_item_focused(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_288get_item_rect_min(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_290get_item_rect_max(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_292get_item_rect_size(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_294set_item_allow_overlap(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_296is_window_hovered(CYTHON_UNUSED PyObject *__pyx_self, ImGuiHoveredFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_298is_window_focused(CYTHON_UNUSED PyObject *__pyx_self, ImGuiHoveredFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_300is_rect_visible(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_size_width, float __pyx_v_size_height); /* proto */
static PyObject *__pyx_pf_4core_302get_style_color_name(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_index); /* proto */
static PyObject *__pyx_pf_4core_304get_time(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_306get_key_index(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_key); /* proto */
static PyObject *__pyx_pf_4core_308is_key_pressed(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_key_index, bool __pyx_v_repeat); /* proto */
static PyObject *__pyx_pf_4core_310is_key_down(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_key_index); /* proto */
static PyObject *__pyx_pf_4core_312is_mouse_hovering_rect(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_r_min_x, float __pyx_v_r_min_y, float __pyx_v_r_max_x, float __pyx_v_r_max_y, bool __pyx_v_clip); /* proto */
static PyObject *__pyx_pf_4core_314is_mouse_double_clicked(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button); /* proto */
static PyObject *__pyx_pf_4core_316is_mouse_clicked(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button, bool __pyx_v_repeat); /* proto */
static PyObject *__pyx_pf_4core_318is_mouse_released(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button); /* proto */
static PyObject *__pyx_pf_4core_320is_mouse_down(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button); /* proto */
static PyObject *__pyx_pf_4core_322is_mouse_dragging(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button, float __pyx_v_lock_threshold); /* proto */
static PyObject *__pyx_pf_4core_324get_mouse_drag_delta(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button, float __pyx_v_lock_threshold); /* proto */
static PyObject *__pyx_pf_4core_326get_mouse_pos(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_328reset_mouse_drag_delta(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_button); /* proto */
static PyObject *__pyx_pf_4core_330get_mouse_cursor(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_332set_mouse_cursor(CYTHON_UNUSED PyObject *__pyx_self, ImGuiMouseCursor __pyx_v_mouse_cursor_type); /* proto */
static PyObject *__pyx_pf_4core_334set_scroll_here(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_center_y_ratio); /* proto */
static PyObject *__pyx_pf_4core_336set_scroll_from_pos_y(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_pos_y, float __pyx_v_center_y_ratio); /* proto */
static PyObject *__pyx_pf_4core_338push_font(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core__Font *__pyx_v_font); /* proto */
static PyObject *__pyx_pf_4core_340pop_font(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_342calc_text_size(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text, bool __pyx_v_hide_text_after_double_hash, float __pyx_v_wrap_width); /* proto */
static PyObject *__pyx_pf_4core_344push_style_var(CYTHON_UNUSED PyObject *__pyx_self, ImGuiStyleVar __pyx_v_variable, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_346push_style_color(CYTHON_UNUSED PyObject *__pyx_self, ImGuiCol __pyx_v_variable, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, float __pyx_v_a); /* proto */
static PyObject *__pyx_pf_4core_348pop_style_var(CYTHON_UNUSED PyObject *__pyx_self, unsigned int __pyx_v_count); /* proto */
static PyObject *__pyx_pf_4core_350get_font_size(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_352get_style_color_vec_4(CYTHON_UNUSED PyObject *__pyx_self, ImGuiCol __pyx_v_idx); /* proto */
static PyObject *__pyx_pf_4core_354get_font_tex_uv_white_pixel(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_356get_color_u32_idx(CYTHON_UNUSED PyObject *__pyx_self, ImGuiCol __pyx_v_idx, float __pyx_v_alpha_mul); /* proto */
static PyObject *__pyx_pf_4core_358get_color_u32_rgba(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, float __pyx_v_a); /* proto */
static PyObject *__pyx_pf_4core_360get_color_u32(CYTHON_UNUSED PyObject *__pyx_self, ImU32 __pyx_v_col); /* proto */
static PyObject *__pyx_pf_4core_362push_item_width(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_item_width); /* proto */
static PyObject *__pyx_pf_4core_364pop_item_width(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_366calculate_item_width(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_368push_text_wrap_pos(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_wrap_pos_x); /* proto */
static PyObject *__pyx_pf_4core_370pop_text_wrap_pos(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_372push_allow_keyboard_focus(CYTHON_UNUSED PyObject *__pyx_self, bool __pyx_v_allow_focus); /* proto */
static PyObject *__pyx_pf_4core_374pop_allow_keyboard_focus(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_376push_button_repeat(CYTHON_UNUSED PyObject *__pyx_self, bool __pyx_v_repeat); /* proto */
static PyObject *__pyx_pf_4core_378pop_button_repeat(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_380pop_style_color(CYTHON_UNUSED PyObject *__pyx_self, unsigned int __pyx_v_count); /* proto */
static PyObject *__pyx_pf_4core_382separator(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_384same_line(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_position, float __pyx_v_spacing); /* proto */
static PyObject *__pyx_pf_4core_386new_line(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_388spacing(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_390dummy(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_width, PyObject *__pyx_v_height); /* proto */
static PyObject *__pyx_pf_4core_392indent(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_width); /* proto */
static PyObject *__pyx_pf_4core_394unindent(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_width); /* proto */
static PyObject *__pyx_pf_4core_396columns(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_count, PyObject *__pyx_v_identifier, bool __pyx_v_border); /* proto */
static PyObject *__pyx_pf_4core_398next_column(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_400get_column_index(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_402get_column_offset(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_column_index); /* proto */
static PyObject *__pyx_pf_4core_404set_column_offset(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_column_index, float __pyx_v_offset_x); /* proto */
static PyObject *__pyx_pf_4core_406get_column_width(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_column_index); /* proto */
static PyObject *__pyx_pf_4core_408set_column_width(CYTHON_UNUSED PyObject *__pyx_self, int __pyx_v_column_index, float __pyx_v_width); /* proto */
static PyObject *__pyx_pf_4core_410get_columns_count(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_412begin_drag_drop_source(CYTHON_UNUSED PyObject *__pyx_self, ImGuiDragDropFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_414set_drag_drop_payload(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_type, PyObject *__pyx_v_data, ImGuiCond __pyx_v_condition); /* proto */
static PyObject *__pyx_pf_4core_416end_drag_drop_source(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_418begin_drag_drop_target(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_420accept_drag_drop_payload(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_type, ImGuiDragDropFlags __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_4core_422end_drag_drop_target(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_424begin_group(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_426end_group(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_428get_cursor_pos(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_430get_cursor_pos_x(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_432get_cursor_pos_y(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_434set_cursor_pos(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_local_pos); /* proto */
static PyObject *__pyx_pf_4core_436set_cursor_pos_x(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_x); /* proto */
static PyObject *__pyx_pf_4core_438set_cursor_pos_y(CYTHON_UNUSED PyObject *__pyx_self, float __pyx_v_y); /* proto */
static PyObject *__pyx_pf_4core_440get_cursor_start_pos(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_442get_cursor_screen_pos(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_444set_cursor_screen_pos(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_screen_pos); /* proto */
static PyObject *__pyx_pf_4core_446align_text_to_frame_padding(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_448get_text_line_height(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_450get_text_line_height_with_spacing(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_452get_frame_height(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_454get_frame_height_with_spacing(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_456create_context(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core__FontAtlas *__pyx_v_shared_font_atlas); /* proto */
static PyObject *__pyx_pf_4core_458destroy_context(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core__ImGuiContext *__pyx_v_ctx); /* proto */
static PyObject *__pyx_pf_4core_460get_current_context(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_462set_current_context(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core__ImGuiContext *__pyx_v_ctx); /* proto */
static PyObject *__pyx_pf_4core_464push_id(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_str_id); /* proto */
static PyObject *__pyx_pf_4core_466pop_id(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_468_ansifeed_text_ansi(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text); /* proto */
static PyObject *__pyx_pf_4core_470_ansifeed_text_ansi_colored(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, float __pyx_v_a); /* proto */
static PyObject *__pyx_pf_4core_472_py_font(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_4core__Font *__pyx_v_font); /* proto */
static PyObject *__pyx_pf_4core_475_py_styled(CYTHON_UNUSED PyObject *__pyx_self, ImGuiStyleVar __pyx_v_variable, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_4core_478_py_colored(CYTHON_UNUSED PyObject *__pyx_self, ImGuiCol __pyx_v_variable, float __pyx_v_r, float __pyx_v_g, float __pyx_v_b, float __pyx_v_a); /* proto */
static PyObject *__pyx_pf_4core_481_py_istyled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_variables_and_values); /* proto */
static PyObject *__pyx_pf_4core_484_py_scoped(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_str_id); /* proto */
static PyObject *__pyx_pf_4core_487_py_vertex_buffer_vertex_pos_offset(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_489_py_vertex_buffer_vertex_uv_offset(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_491_py_vertex_buffer_vertex_col_offset(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_493_py_vertex_buffer_vertex_size(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4core_495_py_index_buffer_index_size(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array___cinit__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_shape, Py_ssize_t __pyx_v_itemsize, PyObject *__pyx_v_format, PyObject *__pyx_v_mode, int __pyx_v_allocate_buffer); /* proto */
static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array_2__getbuffer__(struct __pyx_array_obj *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags); /* proto */
static void __pyx_array___pyx_pf_15View_dot_MemoryView_5array_4__dealloc__(struct __pyx_array_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_5array_7memview___get__(struct __pyx_array_obj *__pyx_v_self); /* proto */
static Py_ssize_t __pyx_array___pyx_pf_15View_dot_MemoryView_5array_6__len__(struct __pyx_array_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_array___pyx_pf_15View_dot_MemoryView_5array_8__getattr__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_attr); /* proto */
static PyObject *__pyx_array___pyx_pf_15View_dot_MemoryView_5array_10__getitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item); /* proto */
static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array_12__setitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf___pyx_array___reduce_cython__(CYTHON_UNUSED struct __pyx_array_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_array_2__setstate_cython__(CYTHON_UNUSED struct __pyx_array_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum___init__(struct __pyx_MemviewEnum_obj *__pyx_v_self, PyObject *__pyx_v_name); /* proto */
static PyObject *__pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum_2__repr__(struct __pyx_MemviewEnum_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_MemviewEnum___reduce_cython__(struct __pyx_MemviewEnum_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_MemviewEnum_2__setstate_cython__(struct __pyx_MemviewEnum_obj *__pyx_v_self, PyObject *__pyx_v___pyx_state); /* proto */
static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview___cinit__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_obj, int __pyx_v_flags, int __pyx_v_dtype_is_object); /* proto */
static void __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_2__dealloc__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_4__getitem__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index); /* proto */
static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_6__setitem__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value); /* proto */
static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_8__getbuffer__(struct __pyx_memoryview_obj *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_1T___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4base___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_5shape___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_7strides___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_10suboffsets___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4ndim___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_8itemsize___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_6nbytes___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4size___get__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static Py_ssize_t __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_10__len__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_12__repr__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_14__str__(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_16is_c_contig(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_18is_f_contig(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_20copy(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_22copy_fortran(struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_memoryview___reduce_cython__(CYTHON_UNUSED struct __pyx_memoryview_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_memoryview_2__setstate_cython__(CYTHON_UNUSED struct __pyx_memoryview_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static void __pyx_memoryviewslice___pyx_pf_15View_dot_MemoryView_16_memoryviewslice___dealloc__(struct __pyx_memoryviewslice_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView_16_memoryviewslice_4base___get__(struct __pyx_memoryviewslice_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_memoryviewslice___reduce_cython__(CYTHON_UNUSED struct __pyx_memoryviewslice_obj *__pyx_v_self); /* proto */
static PyObject *__pyx_pf___pyx_memoryviewslice_2__setstate_cython__(CYTHON_UNUSED struct __pyx_memoryviewslice_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_pf_15View_dot_MemoryView___pyx_unpickle_Enum(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state); /* proto */
static PyObject *__pyx_tp_new_4core__Font(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__ImGuiContext(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__DrawCmd(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__DrawList(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__Colors(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core_GuiStyle(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__DrawData(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__StaticGlyphRanges(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__FontAtlas(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core__IO(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core___pyx_scope_struct___py_font(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core___pyx_scope_struct_1__py_styled(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core___pyx_scope_struct_2__py_colored(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core___pyx_scope_struct_3__py_istyled(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_4core___pyx_scope_struct_4__py_scoped(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_array(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_Enum(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_memoryview(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new__memoryviewslice(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/

#if 1
#include "pyimgui_core_selection.cpp"
#else
static PyObject *__pyx_pw_4core_33begin(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_4core_33begin = {"begin", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_4core_33begin, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_4core_33begin(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_label = 0;
  PyObject *__pyx_v_closable = 0;
  ImGuiWindowFlags __pyx_v_flags;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("begin (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_label,&__pyx_n_s_closable,&__pyx_n_s_flags,0};
    PyObject* values[3] = {0,0,0};
    values[1] = ((PyObject *)Py_False);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_label)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_closable);
          if (value) { values[1] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_flags);
          if (value) { values[2] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "begin") < 0)) __PYX_ERR(0, 2103, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_label = ((PyObject*)values[0]);
    __pyx_v_closable = values[1];
    if (values[2]) {
      __pyx_v_flags = __Pyx_PyInt_As_ImGuiWindowFlags(values[2]); if (unlikely((__pyx_v_flags == ((ImGuiWindowFlags)-1)) && PyErr_Occurred())) __PYX_ERR(0, 2103, __pyx_L3_error)
    } else {
      __pyx_v_flags = ((ImGuiWindowFlags)0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("begin", 0, 1, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 2103, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("core.begin", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_label), (&PyString_Type), 1, "label", 1))) __PYX_ERR(0, 2103, __pyx_L1_error)
  __pyx_r = __pyx_pf_4core_32begin(__pyx_self, __pyx_v_label, __pyx_v_closable, __pyx_v_flags);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4core_32begin(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_closable, ImGuiWindowFlags __pyx_v_flags) {
  bool __pyx_v_opened;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  char const *__pyx_t_2;
  bool *__pyx_t_3;
  int __pyx_t_4;
  bool __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("begin", 0);

  /* "core.pyx":2131
 *         )
 *     """
 *     cdef cimgui.bool opened = True             # <<<<<<<<<<<<<<
 * 
 *     return cimgui.Begin(_bytes(label), &opened if closable else NULL, flags), opened
 */
  __pyx_v_opened = 1;

  /* "core.pyx":2133
 *     cdef cimgui.bool opened = True
 * 
 *     return cimgui.Begin(_bytes(label), &opened if closable else NULL, flags), opened             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __pyx_f_4core__bytes(__pyx_v_label); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 2133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(0, 2133, __pyx_L1_error)
  }
  __pyx_t_2 = __Pyx_PyBytes_AsString(__pyx_t_1); if (unlikely((!__pyx_t_2) && PyErr_Occurred())) __PYX_ERR(0, 2133, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_v_closable); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 2133, __pyx_L1_error)
  if (__pyx_t_4) {
    __pyx_t_3 = (&__pyx_v_opened);
  } else {
    __pyx_t_3 = NULL;
  }
  try {
    __pyx_t_5 = ImGui::Begin(__pyx_t_2, __pyx_t_3, __pyx_v_flags);
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 2133, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyBool_FromLong(__pyx_t_5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 2133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_6 = __Pyx_PyBool_FromLong(__pyx_v_opened); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 2133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_7 = PyTuple_New(2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 2133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_t_6);
  __pyx_t_1 = 0;
  __pyx_t_6 = 0;
  __pyx_r = __pyx_t_7;
  __pyx_t_7 = 0;
  goto __pyx_L0;

  /* "core.pyx":2103
 * 
 * 
 * def begin(str label, closable=False, cimgui.ImGuiWindowFlags flags=0):             # <<<<<<<<<<<<<<
 *     """Begin a window.
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("core.begin", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pw_4core_37end(PyObject *__pyx_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_4core_37end = {"end", (PyCFunction)__pyx_pw_4core_37end, METH_NOARGS, 0};
static PyObject *__pyx_pw_4core_37end(PyObject *__pyx_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("end (wrapper)", 0);
  __pyx_r = __pyx_pf_4core_36end(__pyx_self);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4core_36end(CYTHON_UNUSED PyObject *__pyx_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("end", 0);

  /* "core.pyx":2160
 *         void End()
 *     """
 *     cimgui.End()             # <<<<<<<<<<<<<<
 * 
 * 
 */
  try {
    ImGui::End();
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 2160, __pyx_L1_error)
  }

  /* "core.pyx":2151
 * 
 * 
 * def end():             # <<<<<<<<<<<<<<
 *     """End a window.
 * 
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("core.end", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pw_4core_219input_text(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_4core_219input_text = {"input_text", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_4core_219input_text, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_4core_219input_text(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_label = 0;
  PyObject *__pyx_v_value = 0;
  int __pyx_v_buffer_length;
  ImGuiInputTextFlags __pyx_v_flags;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("input_text (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_label,&__pyx_n_s_value,&__pyx_n_s_buffer_length,&__pyx_n_s_flags,0};
    PyObject* values[4] = {0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_label)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_value)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("input_text", 0, 3, 4, 1); __PYX_ERR(0, 4900, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_buffer_length)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("input_text", 0, 3, 4, 2); __PYX_ERR(0, 4900, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_flags);
          if (value) { values[3] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "input_text") < 0)) __PYX_ERR(0, 4900, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_label = ((PyObject*)values[0]);
    __pyx_v_value = ((PyObject*)values[1]);
    __pyx_v_buffer_length = __Pyx_PyInt_As_int(values[2]); if (unlikely((__pyx_v_buffer_length == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 4903, __pyx_L3_error)
    if (values[3]) {
      __pyx_v_flags = __Pyx_PyInt_As_ImGuiInputTextFlags(values[3]); if (unlikely((__pyx_v_flags == ((ImGuiInputTextFlags)-1)) && PyErr_Occurred())) __PYX_ERR(0, 4904, __pyx_L3_error)
    } else {
      __pyx_v_flags = ((ImGuiInputTextFlags)0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("input_text", 0, 3, 4, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 4900, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("core.input_text", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_label), (&PyString_Type), 1, "label", 1))) __PYX_ERR(0, 4901, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_value), (&PyString_Type), 1, "value", 1))) __PYX_ERR(0, 4902, __pyx_L1_error)
  __pyx_r = __pyx_pf_4core_218input_text(__pyx_self, __pyx_v_label, __pyx_v_value, __pyx_v_buffer_length, __pyx_v_flags);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4core_218input_text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, PyObject *__pyx_v_value, int __pyx_v_buffer_length, ImGuiInputTextFlags __pyx_v_flags) {
  char *__pyx_v_inout_text;
  bool __pyx_v_changed;
  PyObject *__pyx_v_output = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  char const *__pyx_t_2;
  char const *__pyx_t_3;
  bool __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("input_text", 0);

  /* "core.pyx":4949
 *     """
 *     # todo: pymalloc
 *     cdef char* inout_text = <char*>malloc(buffer_length * sizeof(char))             # <<<<<<<<<<<<<<
 *     # todo: take special care of terminating char
 *     strncpy(inout_text, _bytes(value), buffer_length)
 */
  __pyx_v_inout_text = ((char *)malloc((__pyx_v_buffer_length * (sizeof(char)))));

  /* "core.pyx":4951
 *     cdef char* inout_text = <char*>malloc(buffer_length * sizeof(char))
 *     # todo: take special care of terminating char
 *     strncpy(inout_text, _bytes(value), buffer_length)             # <<<<<<<<<<<<<<
 * 
 *     changed = cimgui.InputText(
 */
  __pyx_t_1 = __pyx_f_4core__bytes(__pyx_v_value); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 4951, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(0, 4951, __pyx_L1_error)
  }
  __pyx_t_2 = __Pyx_PyBytes_AsString(__pyx_t_1); if (unlikely((!__pyx_t_2) && PyErr_Occurred())) __PYX_ERR(0, 4951, __pyx_L1_error)
  (void)(strncpy(__pyx_v_inout_text, __pyx_t_2, __pyx_v_buffer_length));
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "core.pyx":4954
 * 
 *     changed = cimgui.InputText(
 *         _bytes(label), inout_text, buffer_length, flags, NULL, NULL             # <<<<<<<<<<<<<<
 *     )
 *     output = _from_bytes(inout_text)
 */
  __pyx_t_1 = __pyx_f_4core__bytes(__pyx_v_label); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 4954, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(0, 4954, __pyx_L1_error)
  }
  __pyx_t_3 = __Pyx_PyBytes_AsString(__pyx_t_1); if (unlikely((!__pyx_t_3) && PyErr_Occurred())) __PYX_ERR(0, 4954, __pyx_L1_error)

  /* "core.pyx":4953
 *     strncpy(inout_text, _bytes(value), buffer_length)
 * 
 *     changed = cimgui.InputText(             # <<<<<<<<<<<<<<
 *         _bytes(label), inout_text, buffer_length, flags, NULL, NULL
 *     )
 */
  try {
    __pyx_t_4 = ImGui::InputText(__pyx_t_3, __pyx_v_inout_text, __pyx_v_buffer_length, __pyx_v_flags, NULL, NULL);
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 4953, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_changed = __pyx_t_4;

  /* "core.pyx":4956
 *         _bytes(label), inout_text, buffer_length, flags, NULL, NULL
 *     )
 *     output = _from_bytes(inout_text)             # <<<<<<<<<<<<<<
 * 
 *     free(inout_text)
 */
  __pyx_t_1 = __Pyx_PyBytes_FromString(__pyx_v_inout_text); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 4956, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_5 = __pyx_f_4core__from_bytes(((PyObject*)__pyx_t_1)); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 4956, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_output = __pyx_t_5;
  __pyx_t_5 = 0;

  /* "core.pyx":4958
 *     output = _from_bytes(inout_text)
 * 
 *     free(inout_text)             # <<<<<<<<<<<<<<
 *     return changed, output
 * 
 */
  free(__pyx_v_inout_text);

  /* "core.pyx":4959
 * 
 *     free(inout_text)
 *     return changed, output             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_5 = __Pyx_PyBool_FromLong(__pyx_v_changed); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 4959, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 4959, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_5);
  __Pyx_INCREF(__pyx_v_output);
  __Pyx_GIVEREF(__pyx_v_output);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_output);
  __pyx_t_5 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "core.pyx":4900
 * 
 * 
 * def input_text(             # <<<<<<<<<<<<<<
 *     str label,
 *     str value,
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("core.input_text", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_output);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pw_4core_161text(PyObject *__pyx_self, PyObject *__pyx_v_text); /*proto*/
static PyMethodDef __pyx_mdef_4core_161text = {"text", (PyCFunction)__pyx_pw_4core_161text, METH_O, 0};
static PyObject *__pyx_pw_4core_161text(PyObject *__pyx_self, PyObject *__pyx_v_text) {
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("text (wrapper)", 0);
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_text), (&PyString_Type), 1, "text", 1))) __PYX_ERR(0, 3714, __pyx_L1_error)
  __pyx_r = __pyx_pf_4core_160text(__pyx_self, ((PyObject*)__pyx_v_text));

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}


static PyObject *__pyx_pf_4core_160text(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_text) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  char *__pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("text", 0);

  /* "core.pyx":3733
 *     """
 *     # note: "%s" required for safety and to favor of Python string formating
 *     cimgui.Text("%s", _bytes(text))             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_1 = __pyx_f_4core__bytes(__pyx_v_text); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3733, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(0, 3733, __pyx_L1_error)
  }
  __pyx_t_2 = __Pyx_PyBytes_AsWritableString(__pyx_t_1); if (unlikely((!__pyx_t_2) && PyErr_Occurred())) __PYX_ERR(0, 3733, __pyx_L1_error)
  try {
    ImGui::Text(((char const *)"%s"), __pyx_t_2);
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 3733, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "core.pyx":3714
 * 
 * 
 * def text(str text):             # <<<<<<<<<<<<<<
 *     """Add text to current widget stack.
 * 
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("core.text", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pw_4core_251slider_int(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_4core_251slider_int = {"slider_int", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_4core_251slider_int, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_4core_251slider_int(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_label = 0;
  int __pyx_v_value;
  int __pyx_v_min_value;
  int __pyx_v_max_value;
  PyObject *__pyx_v_format = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("slider_int (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_label,&__pyx_n_s_value,&__pyx_n_s_min_value,&__pyx_n_s_max_value,&__pyx_n_s_format,0};
    PyObject* values[5] = {0,0,0,0,0};
    values[4] = ((PyObject*)__pyx_kp_s_f);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_label)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_value)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("slider_int", 0, 4, 5, 1); __PYX_ERR(0, 5729, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_value)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("slider_int", 0, 4, 5, 2); __PYX_ERR(0, 5729, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (likely((values[3] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_max_value)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("slider_int", 0, 4, 5, 3); __PYX_ERR(0, 5729, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_format);
          if (value) { values[4] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "slider_int") < 0)) __PYX_ERR(0, 5729, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_label = ((PyObject*)values[0]);
    __pyx_v_value = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_value == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 5731, __pyx_L3_error)
    __pyx_v_min_value = __Pyx_PyInt_As_int(values[2]); if (unlikely((__pyx_v_min_value == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 5732, __pyx_L3_error)
    __pyx_v_max_value = __Pyx_PyInt_As_int(values[3]); if (unlikely((__pyx_v_max_value == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 5733, __pyx_L3_error)
    __pyx_v_format = ((PyObject*)values[4]);
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("slider_int", 0, 4, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 5729, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("core.slider_int", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_label), (&PyString_Type), 1, "label", 1))) __PYX_ERR(0, 5730, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_format), (&PyString_Type), 1, "format", 1))) __PYX_ERR(0, 5734, __pyx_L1_error)
  __pyx_r = __pyx_pf_4core_250slider_int(__pyx_self, __pyx_v_label, __pyx_v_value, __pyx_v_min_value, __pyx_v_max_value, __pyx_v_format);

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4core_250slider_int(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_label, int __pyx_v_value, int __pyx_v_min_value, int __pyx_v_max_value, PyObject *__pyx_v_format) {
  int __pyx_v_inout_value;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  char const *__pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  char const *__pyx_t_4;
  bool __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("slider_int", 0);

  /* "core.pyx":5776
 *         )
 *     """
 *     cdef int inout_value = value             # <<<<<<<<<<<<<<
 *     return cimgui.SliderInt(
 *         _bytes(label), <int*>&inout_value,
 */
  __pyx_v_inout_value = __pyx_v_value;

  /* "core.pyx":5777
 *     """
 *     cdef int inout_value = value
 *     return cimgui.SliderInt(             # <<<<<<<<<<<<<<
 *         _bytes(label), <int*>&inout_value,
 *         min_value, max_value, _bytes(format)
 */
  __Pyx_XDECREF(__pyx_r);

  /* "core.pyx":5778
 *     cdef int inout_value = value
 *     return cimgui.SliderInt(
 *         _bytes(label), <int*>&inout_value,             # <<<<<<<<<<<<<<
 *         min_value, max_value, _bytes(format)
 *     ), inout_value
 */
  __pyx_t_1 = __pyx_f_4core__bytes(__pyx_v_label); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5778, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(__pyx_t_1 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(0, 5778, __pyx_L1_error)
  }
  __pyx_t_2 = __Pyx_PyBytes_AsString(__pyx_t_1); if (unlikely((!__pyx_t_2) && PyErr_Occurred())) __PYX_ERR(0, 5778, __pyx_L1_error)

  /* "core.pyx":5779
 *     return cimgui.SliderInt(
 *         _bytes(label), <int*>&inout_value,
 *         min_value, max_value, _bytes(format)             # <<<<<<<<<<<<<<
 *     ), inout_value
 * 
 */
  __pyx_t_3 = __pyx_f_4core__bytes(__pyx_v_format); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 5779, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (unlikely(__pyx_t_3 == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(0, 5779, __pyx_L1_error)
  }
  __pyx_t_4 = __Pyx_PyBytes_AsString(__pyx_t_3); if (unlikely((!__pyx_t_4) && PyErr_Occurred())) __PYX_ERR(0, 5779, __pyx_L1_error)

  /* "core.pyx":5777
 *     """
 *     cdef int inout_value = value
 *     return cimgui.SliderInt(             # <<<<<<<<<<<<<<
 *         _bytes(label), <int*>&inout_value,
 *         min_value, max_value, _bytes(format)
 */
  try {
    __pyx_t_5 = ImGui::SliderInt(__pyx_t_2, ((int *)(&__pyx_v_inout_value)), __pyx_v_min_value, __pyx_v_max_value, __pyx_t_4);
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 5777, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyBool_FromLong(__pyx_t_5); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 5777, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "core.pyx":5780
 *         _bytes(label), <int*>&inout_value,
 *         min_value, max_value, _bytes(format)
 *     ), inout_value             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_inout_value); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5780, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);

  /* "core.pyx":5777
 *     """
 *     cdef int inout_value = value
 *     return cimgui.SliderInt(             # <<<<<<<<<<<<<<
 *         _bytes(label), <int*>&inout_value,
 *         min_value, max_value, _bytes(format)
 */
  __pyx_t_6 = PyTuple_New(2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 5777, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_1);
  __pyx_t_3 = 0;
  __pyx_t_1 = 0;
  __pyx_r = __pyx_t_6;
  __pyx_t_6 = 0;
  goto __pyx_L0;

  /* "core.pyx":5729
 * 
 * 
 * def slider_int(             # <<<<<<<<<<<<<<
 *     str label,
 *     int value,
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("core.slider_int", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
#endif



#define CY_IMPL_KW(imp, f) \
STATIC mp_obj_t f(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) { \
  mp_obj_t imp##f(mp_obj_t, mp_obj_t, mp_obj_t); \
  return imp##f(NULL, mp_obj_new_tuple(n_args, pos_args), kw_args); } \
  mp_obj_fun_builtin_var_t f##_obj = {{&mp_type_fun_builtin_var}, MP_OBJ_FUN_MAKE_SIG(0, MP_OBJ_FUN_ARGS_MAX, true), (mp_fun_var_t) f};

#define CY_IMPL_0(imp, f) \
STATIC mp_obj_t f() { \
  mp_obj_t imp##f(mp_obj_t, mp_obj_t); \
  return imp##f(NULL, NULL); } \
  mp_obj_fun_builtin_fixed_t f##_obj = {{&mp_type_fun_builtin_0}, f};

#define CY_IMPL_1(imp, f) \
STATIC mp_obj_t f(mp_obj_t arg) { \
  mp_obj_t imp##f(mp_obj_t, mp_obj_t); \
  return imp##f(NULL, arg); } \
  mp_obj_fun_builtin_fixed_t f##_obj = {{&mp_type_fun_builtin_1}, (mp_fun_0_t) f};


extern "C"
{
#include "py/obj.h"
#include "py/objstr.h"
#include "pyimgui_def.inl"
}

