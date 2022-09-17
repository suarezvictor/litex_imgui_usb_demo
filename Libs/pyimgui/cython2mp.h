#include <string.h>
extern "C"
{
#include "py/obj.h"
#include "py/objstr.h"
#include "py/gc.h"
#include "py/objtuple.h"
}

#define PY_MAJOR_VERSION 3

#define PyObject_HEAD mp_obj_base_t base;
#define __pyx_atomic_int volatile int //FIXME: use real atomics

#define malloc(x) gc_alloc(x, false)
#define free(x) gc_free(x)
#define PyObject_Malloc malloc
#define PyObject_Free free
#define PyMem_Malloc malloc
#define PyMem_Free free
enum PyMatch { Py_EQ, Py_NE };

typedef void(*PyCFunction)(...);
typedef PyCFunction PyCFunctionWithKeywords;
struct PyMethodDef { const char *name; PyCFunction f; int flags, dummy; };

struct __pyx_CoroutineObject { void *closure; int resume_label; };
#define __Pyx_Generator_New(...) (__pyx_CoroutineObject*) nullptr;
#define __Pyx_Coroutine_ResetAndClearException(x)
#define __Pyx_Coroutine_clear(x)
#define __Pyx_ExceptionSave(...)
#define __Pyx_ErrRestoreWithState(...)
#define __Pyx_ExceptionSwap(...)
struct PyThreadState;

static mp_obj_tuple_t empty_tuple;
static mp_obj_tuple_t* __pyx_empty_tuple = &empty_tuple;

typedef intptr_t Py_intptr_t;

#define METH_NOARGS 1
#define METH_VARARGS 2
#define METH_KEYWORDS 4
#define METH_O 8
#define PyBUF_C_CONTIGUOUS 16
#define PyBUF_ANY_CONTIGUOUS 32
#define PyBUF_F_CONTIGUOUS 64
#define PyBUF_FORMAT 128
#define PyBUF_WRITABLE 256
#define PyBUF_STRIDES 512
#define PyBUF_INDIRECT 1024
#define PyBUF_ND 2048
#define PyBUF_RECORDS 4096
#define PyBUF_RECORDS_RO 8192
#define Py_TPFLAGS_IS_ABSTRACT 16384

#define CYTHON_UNUSED
#define CYTHON_MAYBE_UNUSED_VAR(x) (void)x
#define CYTHON_INLINE inline
#define __PYX_ERR(...) {}
#define unlikely(x) (x)
#define likely(x) (x)
#define __Pyx_GOTREF(...)
#define __Pyx_GIVEREF(...)
#define __Pyx_XDECREF(...)
#define __Pyx_XGIVEREF(...)
#define __Pyx_INCREF(x)
#define __Pyx_DECREF(x)
#define __Pyx_DECREF_SET(a, b)
#define __Pyx_XDECREF_SET(a, b)
#define __Pyx_XGOTREF(...)
#define Py_INCREF(x)
#define Py_DECREF(x)
#define Py_XDECREF(x)
#define __Pyx_SET_REFCNT(o, c)
#define __PYX_XDEC_MEMVIEW(...)
#define __PYX_INC_MEMVIEW(...)
#define __Pyx_AddTraceback(...)
#define __Pyx_RefNannySetupContext(fn, i)
#define __Pyx_RefNannyFinishContext()
#define __Pyx_RefNannyDeclarations
#define __Pyx_TraceDeclarations
#define __Pyx_TraceFrameInit(x) {}
#define __Pyx_TraceCall(...)
#define __Pyx_TraceLine(...) {}
#define __Pyx_TraceReturn(...)
#define __Pyx_CppExn2PyErr()
#define PyErr_Occurred() nullptr
#define PyErr_SetString(...)
#define PyErr_SetNone(x)
#define PyErr_Fetch(...)
#define PyErr_Restore(...)
#define CYTHON_FALLTHROUGH
typedef size_t Py_ssize_t;
#define PyDict_Size(x) mp_obj_dict_len(x)
#define __Pyx_PyDict_GetItemStr(k, s)  mp_map_lookup((mp_map_t*)k, s, MP_MAP_LOOKUP)->value //mp_obj_dict_get(k, s) //map ok if used just to get kw args
struct PyTypeObject
{
  void *(*tp_alloc)(...);
  void *(*tp_new)(...);
  void (*tp_free)(...);
  void *(*tp_iternext)(void *);
  struct { void *(*mp_subscript)(...); } *tp_as_mapping;
  int tp_flags;
} static PyBaseObject_Type;
struct Py_buffer { size_t len, ndim, *shape, *strides, *suboffsets, itemsize; bool readonly; void *buf; char *format; mp_obj_t obj; };
typedef PyTypeObject __Pyx_TypeInfo;
#define Py_TYPE(x) ((PyTypeObject*)(x))

struct PyGetSetDef {const char *name_id; void *(*f)(void *, void *); int (*f2)(void*, void*, void*); char *b; int c; };
typedef int (*visitproc)(...);

#define Py_None mp_const_none
#define Py_True mp_const_true
#define Py_False mp_const_false
#define PyBytes_Type mp_type_bytes
#define __Pyx_void_to_None(x) Py_None

#define __pyx_builtin_Ellipsis nullptr

#define try if(true)
#define catch(...) else

#define PyObject void //mp_obj_t is void *
#define __Pyx_ArgTypeTest(...) true
#warning implement__Pyx_ArgTypeTest

#define __Pyx_RaiseArgtupleInvalid(...)
#warning implement __Pyx_RaiseArgtupleInvalid

#define __Pyx_PyInt_As_int(x) mp_obj_get_int(x)
#define __Pyx_PyInt_As_size_t __Pyx_PyInt_As_int
#define __pyx_PyFloat_AsFloat(x) mp_obj_get_float(x)
#define __pyx_PyFloat_AsDouble __pyx_PyFloat_AsFloat
#define __Pyx_PyObject_AsDouble __pyx_PyFloat_AsDouble
#define __Pyx_PyBool_FromLong(x) mp_obj_new_bool(x)
#define __Pyx_PyInt_As_unsigned_int __Pyx_PyInt_As_size_t
#define __Pyx_PyInt_As_long __Pyx_PyInt_As_int
#define __Pyx_PyInt_From_int(x) MP_OBJ_NEW_SMALL_INT(x)
#define __Pyx_PyInt_FromSize_t __Pyx_PyInt_From_int
#define __Pyx_PyInt_From_unsigned_int __Pyx_PyInt_FromSize_t
#define __Pyx_PyInt_From_long __Pyx_PyInt_From_int
#define       PyInt_FromSsize_t __Pyx_PyInt_From_int
#define PyFloat_FromDouble(x) nullptr

#define PyTuple_New(n) mp_obj_new_tuple(n, nullptr)
#define PyTuple_Check(x) 0
#define PyTuple_SET_ITEM(t, i, v) ((mp_obj_tuple_t *)t)->items[i]=(v)
#define PyTuple_GET_ITEM(t, i) ((mp_obj_tuple_t *)t)->items[i]
#define PyTuple_GET_SIZE(t) ((mp_obj_tuple_t *)t)->len
#define PyTuple_CheckExact(x) true
#define PyList_CheckExact(x) true
#define PyList_Check(x) 0
#define PyList_New(n) mp_obj_new_list(n, nullptr)
#define PyList_SET_ITEM(...)
#define PyBytes_GET_SIZE(...) 0
#define __Pyx_GetItemInt_Tuple(...) nullptr
#define __Pyx_NewRef(x) x
#define Py_NotImplemented nullptr

struct __pyx_memoryview_obj;
struct __Pyx_memviewslice {
  struct __pyx_memoryview_obj *memview;
  char *data;
  Py_ssize_t shape[8];
  Py_ssize_t strides[8];
  Py_ssize_t suboffsets[8];
};
typedef void *PyThread_type_lock;

static inline size_t PyList_GET_SIZE(mp_obj_t v) { size_t len; mp_obj_list_get(v, &len, nullptr); return len; }

static inline const char *__Pyx_PyBytes_AsString(mp_obj_t value)
{
  GET_STR_DATA_LEN(value, s_value, value_len);
  return (const char *) s_value;
}

#define __Pyx_PyObject_AsString __Pyx_PyBytes_AsString

static inline char *__Pyx_PyBytes_AsWritableString(mp_obj_t value)
{
  GET_STR_DATA_LEN(value, s_value, value_len);
  return (char *) s_value;
}

static inline mp_obj_t __Pyx_PyBytes_FromStringAndSize(const char *str, size_t size)
{
  return mp_obj_new_str(str, size);
}

#define __Pyx_PyBytes_FromString(s) __Pyx_PyBytes_FromStringAndSize((s), strlen(s))
#define __Pyx_PyString_Format(...) nullptr
#define PyString_Check(x) 0
#define PyInt_Check(x) 0
#define PyLong_Check(x) 0
#define PyBytes_Check(x) 0
#define PySlice_Check(x) 0
#define PyIndex_Check(x) 0

#define PyObject_IsTrue(v) mp_obj_is_true(v)
#define PyObject_IsFalse(v) mp_obj_is_false(v)

#define __Pyx_TypeTest(o, t) false
#define __Pyx_PyObject_CallNoArg(x) nullptr
#define __Pyx_PyObject_CallOneArg(a, b) nullptr
#define __Pyx_PyObject_GetAttrStr(a, b) nullptr
#define __Pyx_GetAttr(...) nullptr
#define __Pyx_GetAttr3(...) nullptr

#define CYTHON_UNPACK_METHODS false
#define PyMethod_Check(x) true
#define PyMethod_GET_SELF(x) (x)
#define PyMethod_GET_FUNCTION(x) (x)

#define UNARY_NEG_WOULD_OVERFLOW(x) true

#define PyBIN_OP(a,b,op) nullptr
#define PyINPLACE(a,b,op) nullptr
#define PyNumber_Multiply(a, b) PyBIN_OP(a,b,*)
#define PyNumber_Add(a, b) PyBIN_OP(a,b,+)
#define PyNumber_And(a, b) PyBIN_OP(a,b,&)
#define PyNumber_InPlaceAdd(a,b) PyINPLACE(a,b,+=)
#define PyNumber_InPlaceMultiply(a,b) PyINPLACE(a,b,*=)
#define __Pyx_div_Py_ssize_t(a,b) 0
#define __Pyx_div_long(a,b) 0

#define __Pyx_PyString_Equals(...) -1
#define __Pyx_PyUnicode_Equals(...) -1
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#define PyThread_allocate_lock() 0
#define PyThread_free_lock(x)

#define PySequence_ITEM(a, b) nullptr
#define __Pyx_PyErr_GivenExceptionMatches(...) false
#define __Pyx_PyErr_ExceptionMatches(...) false
#define PyErr_Clear()
#define __Pyx_ErrFetch(...)
#define __Pyx_ErrRestore(...)
#define __Pyx_GetException(...) -1
#define __Pyx_ExceptionReset(...)
#define PyErr_NoMemory(...)

#define PyObject_GetIter(x) nullptr
#define __Pyx_GetItemInt(...) nullptr
#define __Pyx_GetItemInt_List(...) nullptr
#define __Pyx_PyIndex_AsSsize_t __Pyx_PyInt_As_size_t
#define PyExc_StopIteration nullptr
#define __Pyx_PyObject_GetItem(...) nullptr
#define __Pyx_ListComp_Append(...) -1
#define __Pyx_PyList_Append(...) -1
#define __Pyx_CheckKeywordStrings(...) true
#define __Pyx_PyDict_NewPresized(...) nullptr
#define __Pyx_PyDict_GetItem(...) nullptr
#define __Pyx_dict_iterator(...) nullptr
#define __Pyx_dict_iter_next(...) 0
#define PyDict_SetItem(...) -1
#define PyObject_RichCompare(...) nullptr
#define __Pyx_SetItemInt(...) -1
#define __Pyx_PyObject_Dict_GetItem(...) nullptr
#define PyObject_SetItem(...) nullptr

#define __Pyx_PyObject_Call(...) nullptr
#define __Pyx_PyObject_Call2Args(...) nullptr
#define __Pyx_PyString_FormatSafe(...) nullptr
#define __Pyx_PySequence_ContainsTF(...) 0
#define __Pyx_PyDict_ContainsTF(...) 0
#define __Pyx_PyObject_AsWritableString(x) nullptr
#define PyString_CheckExact(...) true
#define PyBytes_CheckExact(...) true
#define __Pyx_TypeCheck(o,t) false
#define PyErr_Format(...) true
#define __Pyx_WriteUnraisable(...)
#define __Pyx_GetModuleGlobalName(...)
#define __Pyx_PyCallable_Check(...) -1
#define __Pyx_PyString_Join(...) nullptr
#define PyObject_Length(x) -1
#define __Pyx_PySequence_SIZE(x) 0
#define __Pyx_Import(...) nullptr
#define __Pyx_ImportFrom(...) nullptr

#define __Pyx_Raise(...)
#define __Pyx_RaiseTooManyValuesError(...)
#define __Pyx_RaiseNeedMoreValuesError(...)
#define __Pyx_RaiseNoneNotIterableError(...)
#define __Pyx_RaiseUnboundLocalError(...)

#define __Pyx_CyFunction_Defaults(t, s) ((t*)s)
#define __Pyx_IternextUnpackEndCheck(...) -1
#define __Pyx_IterFinish() 0
#define __Pyx_pretend_to_initialize(...)
#define __Pyx_RaiseBufferIndexError(...)
#define __Pyx_GetBuffer(...) -1
#define __Pyx_ReleaseBuffer(x)
#define __Pyx_PySequence_Tuple(...) nullptr
#define PyBytes_AS_STRING(x) nullptr
#define PyList_AsTuple(x) nullptr
#define __Pyx_PyList_Extend(...) false
#define __Pyx_PyInt_AddObjC(...) nullptr
#define __pyx_builtin_ValueError nullptr
#define Py_OptimizeFlag false
#define PyUnicode_Format(...) nullptr
#define __Pyx_HasAttr(...) 0
#define PyObject_GC_UnTrack(x)
#define Py_CLEAR(x)

#define __pyx_builtin_IndexError nullptr
#define __pyx_builtin_MemoryError nullptr

#define strdup strdup_local
static char *strdup(const char *s)
{
  size_t len = strlen(s)+1;
  char *r = (char*) malloc(len);
  if(r)
    memcpy(r, s, len);
  return r;
}

template<class T>
struct __Pyx_FakeReference
{
  T *__ptr;
  __Pyx_FakeReference() : __ptr(nullptr) {}
  __Pyx_FakeReference(const T& x) { __ptr = (T*) &x; }
  T* operator -> () { return __ptr; }
  T* operator&() { return __ptr; }
  operator T&() { return *__ptr; }
};

