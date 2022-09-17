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


#include "pyimgui_core_selection.cpp"
#include "pyimgui_def.inl"

