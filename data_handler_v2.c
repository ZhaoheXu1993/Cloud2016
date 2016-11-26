#define PY_SSIZE_T_CLEAN
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03020000)
    #error Cython requires Python 2.6+ or Python 3.2+.
#else
#define CYTHON_ABI "0_24_1"
#include <stddef.h>
#ifndef offsetof
  #define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
  #define CYTHON_COMPILING_IN_PYPY 1
  #define CYTHON_COMPILING_IN_CPYTHON 0
#else
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_CPYTHON 1
#endif
#if !defined(CYTHON_USE_PYLONG_INTERNALS) && CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x02070000
  #define CYTHON_USE_PYLONG_INTERNALS 1
#endif
#if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
  #undef SHIFT
  #undef BASE
  #undef MASK
#endif
#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
  #define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyType_Type
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ?\
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : PyUnicode_GET_SIZE(u)))
#else
  #define CYTHON_PEP393_ENABLED 0
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_SIZE(u))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ?\
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
  #define PyByteArray_Check(obj)  PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Format)
  #define PyObject_Format(obj, fmt)  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
  #define PyObject_Malloc(s)   PyMem_Malloc(s)
  #define PyObject_Free(p)     PyMem_Free(p)
  #define PyObject_Realloc(p)  PyMem_Realloc(p)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
  #define PyObject_ASCII(o)            PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#if PY_VERSION_HEX >= 0x030500B1
#define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
#define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
#elif CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
typedef struct {
    unaryfunc am_await;
    unaryfunc am_aiter;
    unaryfunc am_anext;
} __Pyx_PyAsyncMethodsStruct;
#define __Pyx_PyType_AsAsync(obj) ((__Pyx_PyAsyncMethodsStruct*) (Py_TYPE(obj)->tp_reserved))
#else
#define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#define __Pyx_void_to_None(void_result) ((void)(void_result), Py_INCREF(Py_None), Py_None)

#ifndef CYTHON_INLINE
  #if defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
  #define _USE_MATH_DEFINES
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#if defined(__CYGWIN__) && defined(_LDBL_EQ_DBL)
#define __Pyx_truncl trunc
#else
#define __Pyx_truncl truncl
#endif


#define __PYX_ERR(f_index, lineno, Ln_error) \
{ \
  __pyx_filename = __pyx_f[f_index]; __pyx_lineno = lineno; __pyx_clineno = __LINE__; goto Ln_error; \
}

#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#define __PYX_HAVE__data_handler_v2
#define __PYX_HAVE_API__data_handler_v2
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif

#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
typedef struct {PyObject **p; const char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (\
    (sizeof(type) < sizeof(Py_ssize_t))  ||\
    (sizeof(type) > sizeof(Py_ssize_t) &&\
          likely(v < (type)PY_SSIZE_T_MAX ||\
                 v == (type)PY_SSIZE_T_MAX)  &&\
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||\
                                v == (type)PY_SSIZE_T_MIN)))  ||\
    (sizeof(type) == sizeof(Py_ssize_t) &&\
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||\
                               v == (type)PY_SSIZE_T_MAX)))  )
#if defined (__cplusplus) && __cplusplus >= 201103L
    #include <cstdlib>
    #define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) labs(value)
#elif defined (_MSC_VER) && defined (_M_X64)
    #define __Pyx_sst_abs(value) _abs64(value)
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define __Pyx_sst_abs(value) llabs(value)
#elif defined (__GNUC__)
    #define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
    #define __Pyx_sst_abs(value) ((value<0) ? -value : value)
#endif
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? __Pyx_NewRef(Py_True) : __Pyx_NewRef(Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_COMPILING_IN_CPYTHON
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "data_handler_v2.py",
};

/*--- Type declarations ---*/

/* --- Runtime support code (head) --- */
/* Refnanny.proto */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          if (acquire_gil) {\
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
              PyGILState_Release(__pyx_gilstate_save);\
          } else {\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext()\
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_XDECREF(tmp);\
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_DECREF(tmp);\
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

/* PyObjectGetAttrStr.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

/* GetBuiltinName.proto */
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

/* RaiseArgTupleInvalid.proto */
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found);

/* RaiseDoubleKeywords.proto */
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name);

/* ParseKeywords.proto */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],\
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args,\
    const char* function_name);

/* PyIntBinop.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* SliceObject.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetSlice(
        PyObject* obj, Py_ssize_t cstart, Py_ssize_t cstop,
        PyObject** py_start, PyObject** py_stop, PyObject** py_slice,
        int has_cstart, int has_cstop, int wraparound);

/* GetModuleGlobalName.proto */
static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

/* PyObjectCall.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* PyObjectCallMethO.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

/* GetItemInt.proto */
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) :\
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) :\
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

/* PyThreadStateGet.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyThreadState_declare  PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign  __pyx_tstate = PyThreadState_GET();
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#endif

/* SaveResetException.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_ExceptionSave(type, value, tb)  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb)  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb)   PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb)  PyErr_SetExcInfo(type, value, tb)
#endif

/* GetException.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_GetException(type, value, tb)  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* PyObjectSetAttrStr.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyObject_DelAttrStr(o,n) __Pyx_PyObject_SetAttrStr(o,n,NULL)
static CYTHON_INLINE int __Pyx_PyObject_SetAttrStr(PyObject* obj, PyObject* attr_name, PyObject* value) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_setattro))
        return tp->tp_setattro(obj, attr_name, value);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_setattr))
        return tp->tp_setattr(obj, PyString_AS_STRING(attr_name), value);
#endif
    return PyObject_SetAttr(obj, attr_name, value);
}
#else
#define __Pyx_PyObject_DelAttrStr(o,n)   PyObject_DelAttr(o,n)
#define __Pyx_PyObject_SetAttrStr(o,n,v) PyObject_SetAttr(o,n,v)
#endif

/* PyObjectCallNoArg.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* ListCompAppend.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE int __Pyx_ListComp_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len)) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        Py_SIZE(list) = len+1;
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_ListComp_Append(L,x) PyList_Append(L,x)
#endif

/* PySequenceContains.proto */
static CYTHON_INLINE int __Pyx_PySequence_ContainsTF(PyObject* item, PyObject* seq, int eq) {
    int result = PySequence_Contains(seq, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

/* PyErrExceptionMatches.proto */
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyErr_ExceptionMatches(err) __Pyx_PyErr_ExceptionMatchesInState(__pyx_tstate, err)
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err);
#else
#define __Pyx_PyErr_ExceptionMatches(err)  PyErr_ExceptionMatches(err)
#endif

/* RaiseTooManyValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

/* RaiseNeedMoreValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

/* IterFinish.proto */
static CYTHON_INLINE int __Pyx_IterFinish(void);

/* UnpackItemEndCheck.proto */
static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected);

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* ImportFrom.proto */
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

/* FetchCommonType.proto */
static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type);

/* CythonFunction.proto */
#define __Pyx_CyFunction_USED 1
#include <structmember.h>
#define __Pyx_CYFUNCTION_STATICMETHOD  0x01
#define __Pyx_CYFUNCTION_CLASSMETHOD   0x02
#define __Pyx_CYFUNCTION_CCLASS        0x04
#define __Pyx_CyFunction_GetClosure(f)\
    (((__pyx_CyFunctionObject *) (f))->func_closure)
#define __Pyx_CyFunction_GetClassObj(f)\
    (((__pyx_CyFunctionObject *) (f))->func_classobj)
#define __Pyx_CyFunction_Defaults(type, f)\
    ((type *)(((__pyx_CyFunctionObject *) (f))->defaults))
#define __Pyx_CyFunction_SetDefaultsGetter(f, g)\
    ((__pyx_CyFunctionObject *) (f))->defaults_getter = (g)
typedef struct {
    PyCFunctionObject func;
#if PY_VERSION_HEX < 0x030500A0
    PyObject *func_weakreflist;
#endif
    PyObject *func_dict;
    PyObject *func_name;
    PyObject *func_qualname;
    PyObject *func_doc;
    PyObject *func_globals;
    PyObject *func_code;
    PyObject *func_closure;
    PyObject *func_classobj;
    void *defaults;
    int defaults_pyobjects;
    int flags;
    PyObject *defaults_tuple;
    PyObject *defaults_kwdict;
    PyObject *(*defaults_getter)(PyObject *);
    PyObject *func_annotations;
} __pyx_CyFunctionObject;
static PyTypeObject *__pyx_CyFunctionType = 0;
#define __Pyx_CyFunction_NewEx(ml, flags, qualname, self, module, globals, code)\
    __Pyx_CyFunction_New(__pyx_CyFunctionType, ml, flags, qualname, self, module, globals, code)
static PyObject *__Pyx_CyFunction_New(PyTypeObject *, PyMethodDef *ml,
                                      int flags, PyObject* qualname,
                                      PyObject *self,
                                      PyObject *module, PyObject *globals,
                                      PyObject* code);
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *m,
                                                         size_t size,
                                                         int pyobjects);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *m,
                                                            PyObject *tuple);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *m,
                                                             PyObject *dict);
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *m,
                                                              PyObject *dict);
static int __pyx_CyFunction_init(void);

/* CalculateMetaclass.proto */
static PyObject *__Pyx_CalculateMetaclass(PyTypeObject *metaclass, PyObject *bases);

/* Py3ClassCreate.proto */
static PyObject *__Pyx_Py3MetaclassPrepare(PyObject *metaclass, PyObject *bases, PyObject *name, PyObject *qualname,
                                           PyObject *mkw, PyObject *modname, PyObject *doc);
static PyObject *__Pyx_Py3ClassCreate(PyObject *metaclass, PyObject *name, PyObject *bases, PyObject *dict,
                                      PyObject *mkw, int calculate_metaclass, int allow_py2_metaclass);

/* IncludeStringH.proto */
#include <string.h>

/* BytesEquals.proto */
static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals);

/* UnicodeEquals.proto */
static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals);

/* StrEquals.proto */
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyString_Equals __Pyx_PyUnicode_Equals
#else
#define __Pyx_PyString_Equals __Pyx_PyBytes_Equals
#endif

/* CodeObjectCache.proto */
typedef struct {
    PyCodeObject* code_object;
    int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

/* AddTraceback.proto */
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

/* Print.proto */
static int __Pyx_Print(PyObject*, PyObject *, int);
#if CYTHON_COMPILING_IN_PYPY || PY_MAJOR_VERSION >= 3
static PyObject* __pyx_print = 0;
static PyObject* __pyx_print_kwargs = 0;
#endif

/* PrintOne.proto */
static int __Pyx_PrintOne(PyObject* stream, PyObject *o);

/* CIntFromPy.proto */
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

/* CheckBinaryVersion.proto */
static int __Pyx_check_binary_version(void);

/* InitStrings.proto */
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);


/* Module declarations from 'data_handler_v2' */
#define __Pyx_MODULE_NAME "data_handler_v2"
int __pyx_module_is_main_data_handler_v2 = 0;

/* Implementation of 'data_handler_v2' */
static PyObject *__pyx_builtin_object;
static PyObject *__pyx_builtin_staticmethod;
static PyObject *__pyx_builtin_round;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_KeyError;
static PyObject *__pyx_builtin_zip;
static PyObject *__pyx_builtin_open;
static const char __pyx_k_R[] = "R";
static const char __pyx_k_a[] = "a";
static const char __pyx_k_e[] = "e";
static const char __pyx_k_f[] = "f";
static const char __pyx_k_i[] = "i";
static const char __pyx_k_j[] = "j";
static const char __pyx_k_k[] = "k";
static const char __pyx_k_p[] = "p";
static const char __pyx_k_r[] = "r";
static const char __pyx_k_s[] = "s";
static const char __pyx_k_t[] = "t";
static const char __pyx_k_u[] = "u";
static const char __pyx_k_v[] = "v";
static const char __pyx_k_w[] = "w";
static const char __pyx_k_HI[] = "_HI";
static const char __pyx_k_VV[] = "VV";
static const char __pyx_k_ad[] = "ad";
static const char __pyx_k_b1[] = "b1";
static const char __pyx_k_ds[] = "ds";
static const char __pyx_k_f4[] = "f4";
static const char __pyx_k_ma[] = "ma";
static const char __pyx_k_pp[] = "pp";
static const char __pyx_k_v1[] = "_v1";
static const char __pyx_k__13[] = "";
static const char __pyx_k__23[] = " ";
static const char __pyx_k__25[] = ":";
static const char __pyx_k__28[] = "\n";
static const char __pyx_k_all[] = "all";
static const char __pyx_k_doc[] = "__doc__";
static const char __pyx_k_end[] = "end";
static const char __pyx_k_f_d[] = "%f - %d";
static const char __pyx_k_jit[] = "jit";
static const char __pyx_k_min[] = "min";
static const char __pyx_k_v_2[] = "_v";
static const char __pyx_k_var[] = "var";
static const char __pyx_k_zip[] = "zip";
static const char __pyx_k_Dict[] = "Dict";
static const char __pyx_k_List[] = "List";
static const char __pyx_k_RDCP[] = "RDCP";
static const char __pyx_k_args[] = "args";
static const char __pyx_k_attr[] = "attr";
static const char __pyx_k_axis[] = "axis";
static const char __pyx_k_data[] = "data";
static const char __pyx_k_dict[] = "__dict__";
static const char __pyx_k_dump[] = "__dump";
static const char __pyx_k_file[] = "file";
static const char __pyx_k_fill[] = "fill";
static const char __pyx_k_info[] = "info";
static const char __pyx_k_init[] = "__init__";
static const char __pyx_k_json[] = "json";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_mask[] = "mask";
static const char __pyx_k_mean[] = "mean";
static const char __pyx_k_mode[] = "mode";
static const char __pyx_k_name[] = "name";
static const char __pyx_k_open[] = "open";
static const char __pyx_k_path[] = "path";
static const char __pyx_k_self[] = "self";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_time[] = "time";
static const char __pyx_k_view[] = "view";
static const char __pyx_k_DEBUG[] = "DEBUG";
static const char __pyx_k_Tuple[] = "Tuple";
static const char __pyx_k_close[] = "close";
static const char __pyx_k_debug[] = "debug";
static const char __pyx_k_dtype[] = "dtype";
static const char __pyx_k_empty[] = "empty";
static const char __pyx_k_items[] = "items";
static const char __pyx_k_level[] = "level";
static const char __pyx_k_numba[] = "numba";
static const char __pyx_k_numpy[] = "numpy";
static const char __pyx_k_point[] = "point";
static const char __pyx_k_print[] = "print";
static const char __pyx_k_range[] = "range";
static const char __pyx_k_round[] = "round";
static const char __pyx_k_s_d_d[] = "%s - %d - %d";
static const char __pyx_k_shape[] = "shape";
static const char __pyx_k_value[] = "value";
static const char __pyx_k_write[] = "write";
static const char __pyx_k_zeros[] = "zeros";
static const char __pyx_k_RVVDCP[] = "RVVDCP";
static const char __pyx_k_id_var[] = "id_var";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_kwargs[] = "kwargs";
static const char __pyx_k_legacy[] = "legacy";
static const char __pyx_k_module[] = "__module__";
static const char __pyx_k_name_2[] = "__name__";
static const char __pyx_k_object[] = "object";
static const char __pyx_k_pprint[] = "pprint";
static const char __pyx_k_reduce[] = "reduce";
static const char __pyx_k_return[] = "return";
static const char __pyx_k_size_y[] = "size_y";
static const char __pyx_k_size_z[] = "size_z";
static const char __pyx_k_typing[] = "typing";
static const char __pyx_k_values[] = "values";
static const char __pyx_k_var_hi[] = "var_hi";
static const char __pyx_k_Dataset[] = "Dataset";
static const char __pyx_k_azimuth[] = "azimuth";
static const char __pyx_k_dataset[] = "dataset";
static const char __pyx_k_dualpol[] = "dualpol";
static const char __pyx_k_ediff1d[] = "ediff1d";
static const char __pyx_k_logging[] = "logging";
static const char __pyx_k_netCDF4[] = "netCDF4";
static const char __pyx_k_numexpr[] = "numexpr";
static const char __pyx_k_prepare[] = "__prepare__";
static const char __pyx_k_warning[] = "warning";
static const char __pyx_k_KeyError[] = "KeyError";
static const char __pyx_k_Unsigned[] = "_Unsigned";
static const char __pyx_k_Variable[] = "Variable";
static const char __pyx_k_VcpTable[] = "VcpTable";
static const char __pyx_k_az_index[] = "az_index";
static const char __pyx_k_datatype[] = "datatype";
static const char __pyx_k_datetime[] = "datetime";
static const char __pyx_k_nopython[] = "nopython";
static const char __pyx_k_num2date[] = "num2date";
static const char __pyx_k_numpy_ma[] = "numpy.ma";
static const char __pyx_k_qualname[] = "__qualname__";
static const char __pyx_k_time_var[] = "time_var";
static const char __pyx_k_var_dump[] = "var_dump";
static const char __pyx_k_variable[] = "variable";
static const char __pyx_k_vcp_mode[] = "vcp_mode";
static const char __pyx_k_EchoTop5Z[] = "EchoTop5Z";
static const char __pyx_k_data_dict[] = "data_dict";
static const char __pyx_k_dump_dict[] = "dump_dict";
static const char __pyx_k_elevation[] = "elevation";
static const char __pyx_k_fill_data[] = "fill_data";
static const char __pyx_k_functools[] = "functools";
static const char __pyx_k_is_filled[] = "is_filled";
static const char __pyx_k_mask_data[] = "mask_data";
static const char __pyx_k_metaclass[] = "__metaclass__";
static const char __pyx_k_timedelta[] = "timedelta";
static const char __pyx_k_var_names[] = "var_names";
static const char __pyx_k_variables[] = "variables";
static const char __pyx_k_EchoTop10Z[] = "EchoTop10Z";
static const char __pyx_k_EchoTop20Z[] = "EchoTop20Z";
static const char __pyx_k_SortedDict[] = "SortedDict";
static const char __pyx_k_add_offset[] = "add_offset";
static const char __pyx_k_coordinate[] = "coordinate";
static const char __pyx_k_dump_array[] = "dump_array";
static const char __pyx_k_elevationR[] = "elevationR";
static const char __pyx_k_elevationV[] = "elevationV";
static const char __pyx_k_first_pass[] = "first_pass";
static const char __pyx_k_gate_array[] = "gate_array";
static const char __pyx_k_logical_or[] = "logical_or";
static const char __pyx_k_total_mask[] = "total_mask";
static const char __pyx_k_var_suffix[] = "var_suffix";
static const char __pyx_k_MaskedArray[] = "MaskedArray";
static const char __pyx_k_OrderedDict[] = "OrderedDict";
static const char __pyx_k_RadarNetcdf[] = "RadarNetcdf";
static const char __pyx_k_array_shape[] = "array_shape";
static const char __pyx_k_basicConfig[] = "basicConfig";
static const char __pyx_k_beams_count[] = "beams_count";
static const char __pyx_k_dump_target[] = "dump_target";
static const char __pyx_k_gates_count[] = "gates_count";
static const char __pyx_k_legacy_mode[] = "legacy_mode";
static const char __pyx_k_logical_not[] = "logical_not";
static const char __pyx_k_output2file[] = "output2file";
static const char __pyx_k_time_var_hi[] = "time_var_hi";
static const char __pyx_k_Reflectivity[] = "Reflectivity";
static const char __pyx_k_az_downscale[] = "az_downscale";
static const char __pyx_k_fix_variable[] = "__fix_variable__";
static const char __pyx_k_scale_factor[] = "scale_factor";
static const char __pyx_k_start_output[] = "start output...";
static const char __pyx_k_staticmethod[] = "staticmethod";
static const char __pyx_k_SpectrumWidth[] = "SpectrumWidth";
static const char __pyx_k_all_var_names[] = "all_var_names";
static const char __pyx_k_azimuth_array[] = "azimuth_array";
static const char __pyx_k_elevationR_HI[] = "elevationR_HI";
static const char __pyx_k_elevationV_HI[] = "elevationV_HI";
static const char __pyx_k_fill_data_jit[] = "fill_data_jit";
static const char __pyx_k_filling_table[] = "filling_table";
static const char __pyx_k_finish_output[] = "finish output";
static const char __pyx_k_ref_var_names[] = "ref_var_names";
static const char __pyx_k_time_var_dump[] = "time_var_dump";
static const char __pyx_k_vel_var_names[] = "vel_var_names";
static const char __pyx_k_RadialVelocity[] = "RadialVelocity";
static const char __pyx_k_all_var_suffix[] = "all_var_suffix";
static const char __pyx_k_dump_var_names[] = "dump_var_names";
static const char __pyx_k_ref_var_suffix[] = "ref_var_suffix";
static const char __pyx_k_set_auto_scale[] = "set_auto_scale";
static const char __pyx_k_time_data_dict[] = "time_data_dict";
static const char __pyx_k_vel_var_suffix[] = "vel_var_suffix";
static const char __pyx_k_data_handler_v2[] = "data_handler_v2";
static const char __pyx_k_elevation_index[] = "elevation_index";
static const char __pyx_k_fill_data_nojit[] = "fill_data_nojit";
static const char __pyx_k_scan_start_time[] = "scan_start_time";
static const char __pyx_k_sortedcontainers[] = "sortedcontainers";
static const char __pyx_k_DifferentialPhase[] = "DifferentialPhase";
static const char __pyx_k_RadarNetcdf__dump[] = "_RadarNetcdf__dump";
static const char __pyx_k_dump_data_by_time[] = "dump_data_by_time";
static const char __pyx_k_RadarNetcdf___dump[] = "RadarNetcdf.__dump";
static const char __pyx_k_RadarNetcdf___init[] = "RadarNetcdf.__init__";
static const char __pyx_k_extended_data_dict[] = "extended_data_dict";
static const char __pyx_k_fill_data_function[] = "fill_data_function";
static const char __pyx_k_fill_data_internal[] = "__fill_data_internal";
static const char __pyx_k_Reflectivity_Avg1x5[] = "Reflectivity_Avg1x5";
static const char __pyx_k_Reflectivity_Avg3x3[] = "Reflectivity_Avg3x3";
static const char __pyx_k_Reflectivity_Std1x5[] = "Reflectivity_Std1x5";
static const char __pyx_k_Reflectivity_Std3x3[] = "Reflectivity_Std3x3";
static const char __pyx_k_Dumping_variable_s_s[] = "Dumping variable: %s - %s";
static const char __pyx_k_find_elevation_index[] = "find_elevation_index";
static const char __pyx_k_Fix_unsigned_variable[] = "Fix unsigned variable:";
static const char __pyx_k_RadarNetcdf_fill_data[] = "RadarNetcdf.fill_data";
static const char __pyx_k_RadarNetcdf_is_filled[] = "RadarNetcdf.is_filled";
static const char __pyx_k_RadarNetcdf_mask_data[] = "RadarNetcdf.mask_data";
static const char __pyx_k_VolumeCoveragePattern[] = "VolumeCoveragePattern";
static const char __pyx_k_CorrelationCoefficient[] = "CorrelationCoefficient";
static const char __pyx_k_RadarNetcdf_first_pass[] = "RadarNetcdf.first_pass";
static const char __pyx_k_RadarNetcdf_output2file[] = "RadarNetcdf.output2file";
static const char __pyx_k_DifferentialReflectivity[] = "DifferentialReflectivity";
static const char __pyx_k_DifferentialReflectivity_2[] = "DifferentialReflectivity_";
static const char __pyx_k_RadarNetcdf___fix_variable[] = "RadarNetcdf.__fix_variable__";
static const char __pyx_k_Failed_to_run_JIT_functions[] = "Failed to run JIT functions";
static const char __pyx_k_RadarNetcdf_dump_data_by_time[] = "RadarNetcdf.dump_data_by_time";
static const char __pyx_k_home_sugar_Developer_Cloud2016[] = "/home/sugar/Developer/Cloud2016/py/data_handler_v2.py";
static const char __pyx_k_RadarNetcdf__fill_data_internal[] = "_RadarNetcdf__fill_data_internal";
static const char __pyx_k_Failed_to_run_JITed_fill_data_fu[] = "Failed to run JITed fill_data function: CS";
static const char __pyx_k_RadarNetcdf___fill_data_internal[] = "RadarNetcdf.__fill_data_internal";
static const char __pyx_k_home_sugar_Developer_Cloud2016_2[] = "/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc";
static const char __pyx_k_Failed_to_run_JITed_fill_data_fu_2[] = "Failed to run JITed fill_data function: CD";
static const char __pyx_k_Failed_to_run_JITed_fill_data_fu_3[] = "Failed to run JITed fill_data function: Mixed";
static PyObject *__pyx_n_s_CorrelationCoefficient;
static PyObject *__pyx_n_s_DEBUG;
static PyObject *__pyx_n_s_Dataset;
static PyObject *__pyx_n_s_Dict;
static PyObject *__pyx_n_s_DifferentialPhase;
static PyObject *__pyx_n_s_DifferentialReflectivity;
static PyObject *__pyx_n_s_DifferentialReflectivity_2;
static PyObject *__pyx_kp_s_Dumping_variable_s_s;
static PyObject *__pyx_n_s_EchoTop10Z;
static PyObject *__pyx_n_s_EchoTop20Z;
static PyObject *__pyx_n_s_EchoTop5Z;
static PyObject *__pyx_kp_s_Failed_to_run_JIT_functions;
static PyObject *__pyx_kp_s_Failed_to_run_JITed_fill_data_fu;
static PyObject *__pyx_kp_s_Failed_to_run_JITed_fill_data_fu_2;
static PyObject *__pyx_kp_s_Failed_to_run_JITed_fill_data_fu_3;
static PyObject *__pyx_kp_s_Fix_unsigned_variable;
static PyObject *__pyx_n_s_HI;
static PyObject *__pyx_n_s_KeyError;
static PyObject *__pyx_n_s_List;
static PyObject *__pyx_n_s_MaskedArray;
static PyObject *__pyx_n_s_OrderedDict;
static PyObject *__pyx_n_s_R;
static PyObject *__pyx_n_s_RDCP;
static PyObject *__pyx_n_s_RVVDCP;
static PyObject *__pyx_n_s_RadarNetcdf;
static PyObject *__pyx_n_s_RadarNetcdf___dump;
static PyObject *__pyx_n_s_RadarNetcdf___fill_data_internal;
static PyObject *__pyx_n_s_RadarNetcdf___fix_variable;
static PyObject *__pyx_n_s_RadarNetcdf___init;
static PyObject *__pyx_n_s_RadarNetcdf__dump;
static PyObject *__pyx_n_s_RadarNetcdf__fill_data_internal;
static PyObject *__pyx_n_s_RadarNetcdf_dump_data_by_time;
static PyObject *__pyx_n_s_RadarNetcdf_fill_data;
static PyObject *__pyx_n_s_RadarNetcdf_first_pass;
static PyObject *__pyx_n_s_RadarNetcdf_is_filled;
static PyObject *__pyx_n_s_RadarNetcdf_mask_data;
static PyObject *__pyx_n_s_RadarNetcdf_output2file;
static PyObject *__pyx_n_s_RadialVelocity;
static PyObject *__pyx_n_s_Reflectivity;
static PyObject *__pyx_n_s_Reflectivity_Avg1x5;
static PyObject *__pyx_n_s_Reflectivity_Avg3x3;
static PyObject *__pyx_n_s_Reflectivity_Std1x5;
static PyObject *__pyx_n_s_Reflectivity_Std3x3;
static PyObject *__pyx_n_s_SortedDict;
static PyObject *__pyx_n_s_SpectrumWidth;
static PyObject *__pyx_n_s_Tuple;
static PyObject *__pyx_n_s_Unsigned;
static PyObject *__pyx_n_s_VV;
static PyObject *__pyx_n_s_Variable;
static PyObject *__pyx_n_s_VcpTable;
static PyObject *__pyx_n_s_VolumeCoveragePattern;
static PyObject *__pyx_kp_s__13;
static PyObject *__pyx_kp_s__23;
static PyObject *__pyx_kp_s__25;
static PyObject *__pyx_kp_s__28;
static PyObject *__pyx_n_s_a;
static PyObject *__pyx_n_s_ad;
static PyObject *__pyx_n_s_add_offset;
static PyObject *__pyx_n_s_all;
static PyObject *__pyx_n_s_all_var_names;
static PyObject *__pyx_n_s_all_var_suffix;
static PyObject *__pyx_n_s_args;
static PyObject *__pyx_n_s_array_shape;
static PyObject *__pyx_n_s_attr;
static PyObject *__pyx_n_s_axis;
static PyObject *__pyx_n_s_az_downscale;
static PyObject *__pyx_n_s_az_index;
static PyObject *__pyx_n_s_azimuth;
static PyObject *__pyx_n_s_azimuth_array;
static PyObject *__pyx_n_s_b1;
static PyObject *__pyx_n_s_basicConfig;
static PyObject *__pyx_n_s_beams_count;
static PyObject *__pyx_n_s_close;
static PyObject *__pyx_n_s_coordinate;
static PyObject *__pyx_n_s_data;
static PyObject *__pyx_n_s_data_dict;
static PyObject *__pyx_n_s_data_handler_v2;
static PyObject *__pyx_n_s_dataset;
static PyObject *__pyx_n_s_datatype;
static PyObject *__pyx_n_s_datetime;
static PyObject *__pyx_n_s_debug;
static PyObject *__pyx_n_s_dict;
static PyObject *__pyx_n_s_doc;
static PyObject *__pyx_n_s_ds;
static PyObject *__pyx_n_s_dtype;
static PyObject *__pyx_n_s_dualpol;
static PyObject *__pyx_n_s_dump;
static PyObject *__pyx_n_s_dump_array;
static PyObject *__pyx_n_s_dump_data_by_time;
static PyObject *__pyx_n_s_dump_dict;
static PyObject *__pyx_n_s_dump_target;
static PyObject *__pyx_n_s_dump_var_names;
static PyObject *__pyx_n_s_e;
static PyObject *__pyx_n_s_ediff1d;
static PyObject *__pyx_n_s_elevation;
static PyObject *__pyx_n_s_elevationR;
static PyObject *__pyx_n_s_elevationR_HI;
static PyObject *__pyx_n_s_elevationV;
static PyObject *__pyx_n_s_elevationV_HI;
static PyObject *__pyx_n_s_elevation_index;
static PyObject *__pyx_n_s_empty;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_extended_data_dict;
static PyObject *__pyx_n_s_f;
static PyObject *__pyx_n_s_f4;
static PyObject *__pyx_kp_s_f_d;
static PyObject *__pyx_n_s_file;
static PyObject *__pyx_n_s_fill;
static PyObject *__pyx_n_s_fill_data;
static PyObject *__pyx_n_s_fill_data_function;
static PyObject *__pyx_n_s_fill_data_internal;
static PyObject *__pyx_n_s_fill_data_jit;
static PyObject *__pyx_n_s_fill_data_nojit;
static PyObject *__pyx_n_s_filling_table;
static PyObject *__pyx_n_s_find_elevation_index;
static PyObject *__pyx_kp_s_finish_output;
static PyObject *__pyx_n_s_first_pass;
static PyObject *__pyx_n_s_fix_variable;
static PyObject *__pyx_n_s_functools;
static PyObject *__pyx_n_s_gate_array;
static PyObject *__pyx_n_s_gates_count;
static PyObject *__pyx_kp_s_home_sugar_Developer_Cloud2016;
static PyObject *__pyx_kp_s_home_sugar_Developer_Cloud2016_2;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_n_s_id_var;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_info;
static PyObject *__pyx_n_s_init;
static PyObject *__pyx_n_s_is_filled;
static PyObject *__pyx_n_s_items;
static PyObject *__pyx_n_s_j;
static PyObject *__pyx_n_s_jit;
static PyObject *__pyx_n_s_json;
static PyObject *__pyx_n_s_k;
static PyObject *__pyx_n_s_kwargs;
static PyObject *__pyx_n_s_legacy;
static PyObject *__pyx_n_s_legacy_mode;
static PyObject *__pyx_n_s_level;
static PyObject *__pyx_n_s_logging;
static PyObject *__pyx_n_s_logical_not;
static PyObject *__pyx_n_s_logical_or;
static PyObject *__pyx_n_s_ma;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_mask;
static PyObject *__pyx_n_s_mask_data;
static PyObject *__pyx_n_s_mean;
static PyObject *__pyx_n_s_metaclass;
static PyObject *__pyx_n_s_min;
static PyObject *__pyx_n_s_mode;
static PyObject *__pyx_n_s_module;
static PyObject *__pyx_n_s_name;
static PyObject *__pyx_n_s_name_2;
static PyObject *__pyx_n_s_netCDF4;
static PyObject *__pyx_n_s_nopython;
static PyObject *__pyx_n_s_num2date;
static PyObject *__pyx_n_s_numba;
static PyObject *__pyx_n_s_numexpr;
static PyObject *__pyx_n_s_numpy;
static PyObject *__pyx_n_s_numpy_ma;
static PyObject *__pyx_n_s_object;
static PyObject *__pyx_n_s_open;
static PyObject *__pyx_n_s_output2file;
static PyObject *__pyx_n_s_p;
static PyObject *__pyx_n_s_path;
static PyObject *__pyx_n_s_point;
static PyObject *__pyx_n_s_pp;
static PyObject *__pyx_n_s_pprint;
static PyObject *__pyx_n_s_prepare;
static PyObject *__pyx_n_s_print;
static PyObject *__pyx_n_s_qualname;
static PyObject *__pyx_n_s_r;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_reduce;
static PyObject *__pyx_n_s_ref_var_names;
static PyObject *__pyx_n_s_ref_var_suffix;
static PyObject *__pyx_n_s_return;
static PyObject *__pyx_n_s_round;
static PyObject *__pyx_n_s_s;
static PyObject *__pyx_kp_s_s_d_d;
static PyObject *__pyx_n_s_scale_factor;
static PyObject *__pyx_n_s_scan_start_time;
static PyObject *__pyx_n_s_self;
static PyObject *__pyx_n_s_set_auto_scale;
static PyObject *__pyx_n_s_shape;
static PyObject *__pyx_n_s_size_y;
static PyObject *__pyx_n_s_size_z;
static PyObject *__pyx_n_s_sortedcontainers;
static PyObject *__pyx_kp_s_start_output;
static PyObject *__pyx_n_s_staticmethod;
static PyObject *__pyx_n_s_t;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_time;
static PyObject *__pyx_n_s_time_data_dict;
static PyObject *__pyx_n_s_time_var;
static PyObject *__pyx_n_s_time_var_dump;
static PyObject *__pyx_n_s_time_var_hi;
static PyObject *__pyx_n_s_timedelta;
static PyObject *__pyx_n_s_total_mask;
static PyObject *__pyx_n_s_typing;
static PyObject *__pyx_n_s_u;
static PyObject *__pyx_n_s_v;
static PyObject *__pyx_n_s_v1;
static PyObject *__pyx_n_s_v_2;
static PyObject *__pyx_n_s_value;
static PyObject *__pyx_n_s_values;
static PyObject *__pyx_n_s_var;
static PyObject *__pyx_n_s_var_dump;
static PyObject *__pyx_n_s_var_hi;
static PyObject *__pyx_n_s_var_names;
static PyObject *__pyx_n_s_var_suffix;
static PyObject *__pyx_n_s_variable;
static PyObject *__pyx_n_s_variables;
static PyObject *__pyx_n_s_vcp_mode;
static PyObject *__pyx_n_s_vel_var_names;
static PyObject *__pyx_n_s_vel_var_suffix;
static PyObject *__pyx_n_s_view;
static PyObject *__pyx_n_s_w;
static PyObject *__pyx_n_s_warning;
static PyObject *__pyx_n_s_write;
static PyObject *__pyx_n_s_zeros;
static PyObject *__pyx_n_s_zip;
static PyObject *__pyx_pf_15data_handler_v2_find_elevation_index(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_vcp_mode, PyObject *__pyx_v_e); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_2fill_data_jit(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_gate_array, PyObject *__pyx_v_azimuth_array, PyObject *__pyx_v_dump_array, PyObject *__pyx_v_elevation_index, PyObject *__pyx_v_size_y, PyObject *__pyx_v_size_z); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_4fill_data_nojit(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_gate_array, PyObject *__pyx_v_azimuth_array, PyObject *__pyx_v_dump_array, PyObject *__pyx_v_elevation_index, PyObject *__pyx_v_size_y, PyObject *__pyx_v_size_z); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_6fill_data_function(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_gate_array, PyObject *__pyx_v_azimuth_array, PyObject *__pyx_v_dump_array, PyObject *__pyx_v_elevation_index, PyObject *__pyx_v_size_y, PyObject *__pyx_v_size_z); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_dataset, PyObject *__pyx_v_legacy, PyObject *__pyx_v_dualpol); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_2is_filled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_4__dump(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_var, PyObject *__pyx_v_time_var, PyObject *__pyx_v_dump_dict); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_6dump_data_by_time(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_dump_var_names, PyObject *__pyx_v_dump_target); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_8__fix_variable__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_v); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_10first_pass(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_12__fill_data_internal(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_i, PyObject *__pyx_v_id_var, PyObject *__pyx_v_var_names, PyObject *__pyx_v_var_suffix); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_14fill_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v_args, CYTHON_UNUSED PyObject *__pyx_v_kwargs); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_16mask_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_18output2file(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_path, PyObject *__pyx_v_coordinate); /* proto */
static PyObject *__pyx_float_0_2;
static PyObject *__pyx_float_0_5;
static PyObject *__pyx_float_0_7;
static PyObject *__pyx_float_0_9;
static PyObject *__pyx_float_1_3;
static PyObject *__pyx_float_1_5;
static PyObject *__pyx_float_1_8;
static PyObject *__pyx_float_2_4;
static PyObject *__pyx_float_3_1;
static PyObject *__pyx_float_3_4;
static PyObject *__pyx_float_4_0;
static PyObject *__pyx_float_4_3;
static PyObject *__pyx_float_5_1;
static PyObject *__pyx_float_5_3;
static PyObject *__pyx_float_6_0;
static PyObject *__pyx_float_6_2;
static PyObject *__pyx_float_6_4;
static PyObject *__pyx_float_7_5;
static PyObject *__pyx_float_8_0;
static PyObject *__pyx_float_8_7;
static PyObject *__pyx_float_9_9;
static PyObject *__pyx_float_10_0;
static PyObject *__pyx_float_12_0;
static PyObject *__pyx_float_12_5;
static PyObject *__pyx_float_14_0;
static PyObject *__pyx_float_14_6;
static PyObject *__pyx_float_15_6;
static PyObject *__pyx_float_16_7;
static PyObject *__pyx_float_19_5;
static PyObject *__pyx_float_neg_0_2;
static PyObject *__pyx_float_neg_99990_0;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_11;
static PyObject *__pyx_int_12;
static PyObject *__pyx_int_21;
static PyObject *__pyx_int_121;
static PyObject *__pyx_int_211;
static PyObject *__pyx_int_212;
static PyObject *__pyx_int_221;
static PyObject *__pyx_int_230;
static PyObject *__pyx_int_360;
static PyObject *__pyx_int_720;
static PyObject *__pyx_int_920;
static PyObject *__pyx_int_neg_1;
static PyObject *__pyx_slice_;
static PyObject *__pyx_slice__2;
static PyObject *__pyx_slice__3;
static PyObject *__pyx_slice__4;
static PyObject *__pyx_slice__5;
static PyObject *__pyx_slice__6;
static PyObject *__pyx_slice__7;
static PyObject *__pyx_slice__8;
static PyObject *__pyx_slice__9;
static PyObject *__pyx_slice__10;
static PyObject *__pyx_slice__14;
static PyObject *__pyx_slice__15;
static PyObject *__pyx_slice__18;
static PyObject *__pyx_slice__19;
static PyObject *__pyx_tuple__11;
static PyObject *__pyx_tuple__12;
static PyObject *__pyx_tuple__16;
static PyObject *__pyx_tuple__17;
static PyObject *__pyx_tuple__20;
static PyObject *__pyx_tuple__21;
static PyObject *__pyx_tuple__22;
static PyObject *__pyx_tuple__24;
static PyObject *__pyx_tuple__26;
static PyObject *__pyx_tuple__27;
static PyObject *__pyx_tuple__29;
static PyObject *__pyx_tuple__30;
static PyObject *__pyx_tuple__32;
static PyObject *__pyx_tuple__34;
static PyObject *__pyx_tuple__36;
static PyObject *__pyx_tuple__38;
static PyObject *__pyx_tuple__39;
static PyObject *__pyx_tuple__40;
static PyObject *__pyx_tuple__41;
static PyObject *__pyx_tuple__42;
static PyObject *__pyx_tuple__43;
static PyObject *__pyx_tuple__44;
static PyObject *__pyx_tuple__45;
static PyObject *__pyx_tuple__47;
static PyObject *__pyx_tuple__48;
static PyObject *__pyx_tuple__50;
static PyObject *__pyx_tuple__52;
static PyObject *__pyx_tuple__54;
static PyObject *__pyx_tuple__56;
static PyObject *__pyx_tuple__58;
static PyObject *__pyx_tuple__60;
static PyObject *__pyx_tuple__62;
static PyObject *__pyx_tuple__64;
static PyObject *__pyx_tuple__66;
static PyObject *__pyx_codeobj__31;
static PyObject *__pyx_codeobj__33;
static PyObject *__pyx_codeobj__35;
static PyObject *__pyx_codeobj__37;
static PyObject *__pyx_codeobj__46;
static PyObject *__pyx_codeobj__49;
static PyObject *__pyx_codeobj__51;
static PyObject *__pyx_codeobj__53;
static PyObject *__pyx_codeobj__55;
static PyObject *__pyx_codeobj__57;
static PyObject *__pyx_codeobj__59;
static PyObject *__pyx_codeobj__61;
static PyObject *__pyx_codeobj__63;
static PyObject *__pyx_codeobj__65;

/* "data_handler_v2.py":30
 * 
 * @jit(nopython=True)
 * def find_elevation_index(vcp_mode, e):             # <<<<<<<<<<<<<<
 *     j = 0
 *     for i in vcp_mode:
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_1find_elevation_index(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_1find_elevation_index = {"find_elevation_index", (PyCFunction)__pyx_pw_15data_handler_v2_1find_elevation_index, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_1find_elevation_index(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_vcp_mode = 0;
  PyObject *__pyx_v_e = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("find_elevation_index (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_vcp_mode,&__pyx_n_s_e,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_vcp_mode)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_e)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("find_elevation_index", 1, 2, 2, 1); __PYX_ERR(0, 30, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "find_elevation_index") < 0)) __PYX_ERR(0, 30, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_vcp_mode = values[0];
    __pyx_v_e = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("find_elevation_index", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 30, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.find_elevation_index", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_find_elevation_index(__pyx_self, __pyx_v_vcp_mode, __pyx_v_e);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_find_elevation_index(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_vcp_mode, PyObject *__pyx_v_e) {
  PyObject *__pyx_v_j = NULL;
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *(*__pyx_t_3)(PyObject *);
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  __Pyx_RefNannySetupContext("find_elevation_index", 0);

  /* "data_handler_v2.py":31
 * @jit(nopython=True)
 * def find_elevation_index(vcp_mode, e):
 *     j = 0             # <<<<<<<<<<<<<<
 *     for i in vcp_mode:
 *         if -0.2 < e - i < 0.2:
 */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_v_j = __pyx_int_0;

  /* "data_handler_v2.py":32
 * def find_elevation_index(vcp_mode, e):
 *     j = 0
 *     for i in vcp_mode:             # <<<<<<<<<<<<<<
 *         if -0.2 < e - i < 0.2:
 *             return j
 */
  if (likely(PyList_CheckExact(__pyx_v_vcp_mode)) || PyTuple_CheckExact(__pyx_v_vcp_mode)) {
    __pyx_t_1 = __pyx_v_vcp_mode; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
    __pyx_t_3 = NULL;
  } else {
    __pyx_t_2 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_v_vcp_mode); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 32, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 32, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_3)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_4 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(0, 32, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 32, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      } else {
        if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(0, 32, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 32, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      }
    } else {
      __pyx_t_4 = __pyx_t_3(__pyx_t_1);
      if (unlikely(!__pyx_t_4)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 32, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_4);
    }
    __Pyx_XDECREF_SET(__pyx_v_i, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "data_handler_v2.py":33
 *     j = 0
 *     for i in vcp_mode:
 *         if -0.2 < e - i < 0.2:             # <<<<<<<<<<<<<<
 *             return j
 *         j += 1
 */
    __pyx_t_4 = PyNumber_Subtract(__pyx_v_e, __pyx_v_i); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 33, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyObject_RichCompare(__pyx_float_neg_0_2, __pyx_t_4, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 33, __pyx_L1_error)
    if (__Pyx_PyObject_IsTrue(__pyx_t_5)) {
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = PyObject_RichCompare(__pyx_t_4, __pyx_float_0_2, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 33, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 33, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (__pyx_t_6) {

      /* "data_handler_v2.py":34
 *     for i in vcp_mode:
 *         if -0.2 < e - i < 0.2:
 *             return j             # <<<<<<<<<<<<<<
 *         j += 1
 * 
 */
      __Pyx_XDECREF(__pyx_r);
      __Pyx_INCREF(__pyx_v_j);
      __pyx_r = __pyx_v_j;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      goto __pyx_L0;

      /* "data_handler_v2.py":33
 *     j = 0
 *     for i in vcp_mode:
 *         if -0.2 < e - i < 0.2:             # <<<<<<<<<<<<<<
 *             return j
 *         j += 1
 */
    }

    /* "data_handler_v2.py":35
 *         if -0.2 < e - i < 0.2:
 *             return j
 *         j += 1             # <<<<<<<<<<<<<<
 * 
 * @jit(nopython=True)
 */
    __pyx_t_5 = __Pyx_PyInt_AddObjC(__pyx_v_j, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 35, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF_SET(__pyx_v_j, __pyx_t_5);
    __pyx_t_5 = 0;

    /* "data_handler_v2.py":32
 * def find_elevation_index(vcp_mode, e):
 *     j = 0
 *     for i in vcp_mode:             # <<<<<<<<<<<<<<
 *         if -0.2 < e - i < 0.2:
 *             return j
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":30
 * 
 * @jit(nopython=True)
 * def find_elevation_index(vcp_mode, e):             # <<<<<<<<<<<<<<
 *     j = 0
 *     for i in vcp_mode:
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("data_handler_v2.find_elevation_index", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_j);
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":38
 * 
 * @jit(nopython=True)
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_3fill_data_jit(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_3fill_data_jit = {"fill_data_jit", (PyCFunction)__pyx_pw_15data_handler_v2_3fill_data_jit, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_3fill_data_jit(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_gate_array = 0;
  PyObject *__pyx_v_azimuth_array = 0;
  PyObject *__pyx_v_dump_array = 0;
  PyObject *__pyx_v_elevation_index = 0;
  PyObject *__pyx_v_size_y = 0;
  PyObject *__pyx_v_size_z = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("fill_data_jit (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_gate_array,&__pyx_n_s_azimuth_array,&__pyx_n_s_dump_array,&__pyx_n_s_elevation_index,&__pyx_n_s_size_y,&__pyx_n_s_size_z,0};
    PyObject* values[6] = {0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_gate_array)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_azimuth_array)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_jit", 1, 6, 6, 1); __PYX_ERR(0, 38, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dump_array)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_jit", 1, 6, 6, 2); __PYX_ERR(0, 38, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_elevation_index)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_jit", 1, 6, 6, 3); __PYX_ERR(0, 38, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_size_y)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_jit", 1, 6, 6, 4); __PYX_ERR(0, 38, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_size_z)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_jit", 1, 6, 6, 5); __PYX_ERR(0, 38, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "fill_data_jit") < 0)) __PYX_ERR(0, 38, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 6) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
    }
    __pyx_v_gate_array = values[0];
    __pyx_v_azimuth_array = values[1];
    __pyx_v_dump_array = values[2];
    __pyx_v_elevation_index = values[3];
    __pyx_v_size_y = values[4];
    __pyx_v_size_z = values[5];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("fill_data_jit", 1, 6, 6, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 38, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.fill_data_jit", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_2fill_data_jit(__pyx_self, __pyx_v_gate_array, __pyx_v_azimuth_array, __pyx_v_dump_array, __pyx_v_elevation_index, __pyx_v_size_y, __pyx_v_size_z);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_2fill_data_jit(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_gate_array, PyObject *__pyx_v_azimuth_array, PyObject *__pyx_v_dump_array, PyObject *__pyx_v_elevation_index, PyObject *__pyx_v_size_y, PyObject *__pyx_v_size_z) {
  PyObject *__pyx_v_r = NULL;
  PyObject *__pyx_v_a = NULL;
  PyObject *__pyx_v_ad = NULL;
  PyObject *__pyx_v_az_downscale = NULL;
  PyObject *__pyx_v_k = NULL;
  PyObject *__pyx_v_az_index = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  Py_ssize_t __pyx_t_7;
  PyObject *(*__pyx_t_8)(PyObject *);
  __Pyx_RefNannySetupContext("fill_data_jit", 0);

  /* "data_handler_v2.py":39
 * @jit(nopython=True)
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]             # <<<<<<<<<<<<<<
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 */
  __pyx_t_1 = PySlice_New(Py_None, __pyx_v_size_y, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __Pyx_INCREF(__pyx_slice_);
  __Pyx_GIVEREF(__pyx_slice_);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_slice_);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetItem(__pyx_v_gate_array, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_r = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":40
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]             # <<<<<<<<<<<<<<
 *     # Determine azimuthal resolution
 *     ad = a[1:] - a[:-1]
 */
  __pyx_t_1 = __Pyx_PyObject_GetSlice(__pyx_v_azimuth_array, 0, 0, NULL, &__pyx_v_size_y, NULL, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_a = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":42
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 *     ad = a[1:] - a[:-1]             # <<<<<<<<<<<<<<
 *     # This is a slow way to determine if it is truly high resolution.
 *     # Well, maybe not necessary as we patched netcdf jar.
 */
  __pyx_t_1 = __Pyx_PyObject_GetSlice(__pyx_v_a, 1, 0, NULL, NULL, &__pyx_slice__2, 1, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetSlice(__pyx_v_a, 0, -1L, NULL, NULL, &__pyx_slice__3, 0, 1, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyNumber_Subtract(__pyx_t_1, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_ad = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "data_handler_v2.py":46
 *     # Well, maybe not necessary as we patched netcdf jar.
 *     # TODO: Remove this, only relies on "_HI" or not.
 *     az_downscale = round(numpy.mean(ad[ad > 0]),1) > 0.7             # <<<<<<<<<<<<<<
 *     # As long as it is not legacy, we expand it to 720
 *     # Then we fill the shape
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_mean); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_RichCompare(__pyx_v_ad, __pyx_int_0, Py_GT); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 46, __pyx_L1_error)
  __pyx_t_4 = PyObject_GetItem(__pyx_v_ad, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 46, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_3);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 46, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_5, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 46, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_3);
  __Pyx_INCREF(__pyx_int_1);
  __Pyx_GIVEREF(__pyx_int_1);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_int_1);
  __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_round, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_RichCompare(__pyx_t_3, __pyx_float_0_7, Py_GT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_az_downscale = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":49
 *     # As long as it is not legacy, we expand it to 720
 *     # Then we fill the shape
 *     if az_downscale:             # <<<<<<<<<<<<<<
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 */
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_v_az_downscale); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 49, __pyx_L1_error)
  if (__pyx_t_6) {

    /* "data_handler_v2.py":50
 *     # Then we fill the shape
 *     if az_downscale:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_r, __pyx_n_s_shape); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 50, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 50, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 50, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 50, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
      __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
    } else {
      __pyx_t_7 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 50, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_8 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 50, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    for (;;) {
      if (likely(!__pyx_t_8)) {
        if (likely(PyList_CheckExact(__pyx_t_1))) {
          if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 50, __pyx_L1_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 50, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        } else {
          if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 50, __pyx_L1_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 50, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        }
      } else {
        __pyx_t_3 = __pyx_t_8(__pyx_t_1);
        if (unlikely(!__pyx_t_3)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 50, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_3);
      }
      __Pyx_XDECREF_SET(__pyx_v_k, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "data_handler_v2.py":51
 *     if az_downscale:
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 */
      __pyx_t_3 = PyObject_GetItem(__pyx_v_a, __pyx_v_k); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 51, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyNumber_Multiply(__pyx_t_3, __pyx_int_2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 51, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_PyNumber_Int(__pyx_t_5); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 51, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_XDECREF_SET(__pyx_v_az_index, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "data_handler_v2.py":52
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 */
      __pyx_t_3 = PySlice_New(Py_None, __pyx_v_size_z, Py_None); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_5 = PyTuple_New(2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_v_k);
      __Pyx_GIVEREF(__pyx_v_k);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_v_k);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_3 = PyObject_GetItem(__pyx_v_r, __pyx_t_5); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_5 = PyNumber_Remainder(__pyx_v_az_index, __pyx_v_size_y); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_4 = PyTuple_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_5);
      __Pyx_INCREF(__pyx_slice__4);
      __Pyx_GIVEREF(__pyx_slice__4);
      PyTuple_SET_ITEM(__pyx_t_4, 2, __pyx_slice__4);
      __pyx_t_5 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_dump_array, __pyx_t_4, __pyx_t_3) < 0)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

      /* "data_handler_v2.py":53
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *     else:
 *         for k in range(r.shape[0]):
 */
      __pyx_t_3 = PySlice_New(Py_None, __pyx_v_size_z, Py_None); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_v_k);
      __Pyx_GIVEREF(__pyx_v_k);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_k);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_3 = PyObject_GetItem(__pyx_v_r, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = __Pyx_PyInt_AddObjC(__pyx_v_az_index, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_5 = PyNumber_Remainder(__pyx_t_4, __pyx_v_size_y); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = PyTuple_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_5);
      __Pyx_INCREF(__pyx_slice__5);
      __Pyx_GIVEREF(__pyx_slice__5);
      PyTuple_SET_ITEM(__pyx_t_4, 2, __pyx_slice__5);
      __pyx_t_5 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_dump_array, __pyx_t_4, __pyx_t_3) < 0)) __PYX_ERR(0, 53, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

      /* "data_handler_v2.py":50
 *     # Then we fill the shape
 *     if az_downscale:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "data_handler_v2.py":49
 *     # As long as it is not legacy, we expand it to 720
 *     # Then we fill the shape
 *     if az_downscale:             # <<<<<<<<<<<<<<
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 */
    goto __pyx_L3;
  }

  /* "data_handler_v2.py":55
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
  /*else*/ {
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_r, __pyx_n_s_shape); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 55, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 55, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 55, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 55, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
      __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
    } else {
      __pyx_t_7 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_8 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 55, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    for (;;) {
      if (likely(!__pyx_t_8)) {
        if (likely(PyList_CheckExact(__pyx_t_1))) {
          if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 55, __pyx_L1_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 55, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        } else {
          if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 55, __pyx_L1_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 55, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        }
      } else {
        __pyx_t_3 = __pyx_t_8(__pyx_t_1);
        if (unlikely(!__pyx_t_3)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 55, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_3);
      }
      __Pyx_XDECREF_SET(__pyx_v_k, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "data_handler_v2.py":56
 *     else:
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *     pass
 */
      __pyx_t_3 = PyObject_GetItem(__pyx_v_a, __pyx_v_k); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 56, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyNumber_Multiply(__pyx_t_3, __pyx_int_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 56, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_PyNumber_Int(__pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 56, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_XDECREF_SET(__pyx_v_az_index, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "data_handler_v2.py":57
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *     pass
 * 
 */
      __pyx_t_3 = PySlice_New(Py_None, __pyx_v_size_z, Py_None); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_v_k);
      __Pyx_GIVEREF(__pyx_v_k);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_k);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_3 = PyObject_GetItem(__pyx_v_r, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = PyNumber_Remainder(__pyx_v_az_index, __pyx_v_size_y); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_4);
      __Pyx_INCREF(__pyx_slice__6);
      __Pyx_GIVEREF(__pyx_slice__6);
      PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_slice__6);
      __pyx_t_4 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_dump_array, __pyx_t_5, __pyx_t_3) < 0)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

      /* "data_handler_v2.py":55
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __pyx_L3:;

  /* "data_handler_v2.py":38
 * 
 * @jit(nopython=True)
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("data_handler_v2.fill_data_jit", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_r);
  __Pyx_XDECREF(__pyx_v_a);
  __Pyx_XDECREF(__pyx_v_ad);
  __Pyx_XDECREF(__pyx_v_az_downscale);
  __Pyx_XDECREF(__pyx_v_k);
  __Pyx_XDECREF(__pyx_v_az_index);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":61
 * 
 * 
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_5fill_data_nojit(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_5fill_data_nojit = {"fill_data_nojit", (PyCFunction)__pyx_pw_15data_handler_v2_5fill_data_nojit, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_5fill_data_nojit(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_gate_array = 0;
  PyObject *__pyx_v_azimuth_array = 0;
  PyObject *__pyx_v_dump_array = 0;
  PyObject *__pyx_v_elevation_index = 0;
  PyObject *__pyx_v_size_y = 0;
  PyObject *__pyx_v_size_z = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("fill_data_nojit (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_gate_array,&__pyx_n_s_azimuth_array,&__pyx_n_s_dump_array,&__pyx_n_s_elevation_index,&__pyx_n_s_size_y,&__pyx_n_s_size_z,0};
    PyObject* values[6] = {0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_gate_array)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_azimuth_array)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_nojit", 1, 6, 6, 1); __PYX_ERR(0, 61, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dump_array)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_nojit", 1, 6, 6, 2); __PYX_ERR(0, 61, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_elevation_index)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_nojit", 1, 6, 6, 3); __PYX_ERR(0, 61, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_size_y)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_nojit", 1, 6, 6, 4); __PYX_ERR(0, 61, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_size_z)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_nojit", 1, 6, 6, 5); __PYX_ERR(0, 61, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "fill_data_nojit") < 0)) __PYX_ERR(0, 61, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 6) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
    }
    __pyx_v_gate_array = values[0];
    __pyx_v_azimuth_array = values[1];
    __pyx_v_dump_array = values[2];
    __pyx_v_elevation_index = values[3];
    __pyx_v_size_y = values[4];
    __pyx_v_size_z = values[5];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("fill_data_nojit", 1, 6, 6, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 61, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.fill_data_nojit", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_4fill_data_nojit(__pyx_self, __pyx_v_gate_array, __pyx_v_azimuth_array, __pyx_v_dump_array, __pyx_v_elevation_index, __pyx_v_size_y, __pyx_v_size_z);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_4fill_data_nojit(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_gate_array, PyObject *__pyx_v_azimuth_array, PyObject *__pyx_v_dump_array, PyObject *__pyx_v_elevation_index, PyObject *__pyx_v_size_y, PyObject *__pyx_v_size_z) {
  PyObject *__pyx_v_r = NULL;
  PyObject *__pyx_v_a = NULL;
  PyObject *__pyx_v_ad = NULL;
  PyObject *__pyx_v_az_downscale = NULL;
  PyObject *__pyx_v_k = NULL;
  PyObject *__pyx_v_az_index = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  Py_ssize_t __pyx_t_7;
  PyObject *(*__pyx_t_8)(PyObject *);
  __Pyx_RefNannySetupContext("fill_data_nojit", 0);

  /* "data_handler_v2.py":62
 * 
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]             # <<<<<<<<<<<<<<
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 */
  __pyx_t_1 = PySlice_New(Py_None, __pyx_v_size_y, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __Pyx_INCREF(__pyx_slice__7);
  __Pyx_GIVEREF(__pyx_slice__7);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_slice__7);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetItem(__pyx_v_gate_array, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_r = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":63
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]             # <<<<<<<<<<<<<<
 *     # Determine azimuthal resolution
 *     ad = numpy.ediff1d(a)
 */
  __pyx_t_1 = __Pyx_PyObject_GetSlice(__pyx_v_azimuth_array, 0, 0, NULL, &__pyx_v_size_y, NULL, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 63, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_a = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":65
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 *     ad = numpy.ediff1d(a)             # <<<<<<<<<<<<<<
 *     # This is a slow way to determine if it is truly high resolution.
 *     # Well, maybe not necessary as we patched netcdf jar.
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 65, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_ediff1d); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 65, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_a); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 65, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 65, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2); __pyx_t_2 = NULL;
    __Pyx_INCREF(__pyx_v_a);
    __Pyx_GIVEREF(__pyx_v_a);
    PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_v_a);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 65, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_ad = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":69
 *     # Well, maybe not necessary as we patched netcdf jar.
 *     # TODO: Remove this, only relies on "_HI" or not.
 *     az_downscale = round(numpy.mean(ad[ad > 0])) > 0.7             # <<<<<<<<<<<<<<
 *     # As long as it is not legacy, we expand it to 720
 *     # Then we fill the shape
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 69, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_mean); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 69, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_RichCompare(__pyx_v_ad, __pyx_int_0, Py_GT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 69, __pyx_L1_error)
  __pyx_t_2 = PyObject_GetItem(__pyx_v_ad, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 69, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 69, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 69, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3); __pyx_t_3 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 69, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 69, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_round, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 69, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyObject_RichCompare(__pyx_t_1, __pyx_float_0_7, Py_GT); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 69, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_az_downscale = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "data_handler_v2.py":72
 *     # As long as it is not legacy, we expand it to 720
 *     # Then we fill the shape
 *     if az_downscale:             # <<<<<<<<<<<<<<
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 */
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_v_az_downscale); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 72, __pyx_L1_error)
  if (__pyx_t_6) {

    /* "data_handler_v2.py":73
 *     # Then we fill the shape
 *     if az_downscale:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_r, __pyx_n_s_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 73, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_4, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 73, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 73, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 73, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
      __pyx_t_4 = __pyx_t_1; __Pyx_INCREF(__pyx_t_4); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
    } else {
      __pyx_t_7 = -1; __pyx_t_4 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 73, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = Py_TYPE(__pyx_t_4)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 73, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    for (;;) {
      if (likely(!__pyx_t_8)) {
        if (likely(PyList_CheckExact(__pyx_t_4))) {
          if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_4)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_1 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 73, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_4, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        } else {
          if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 73, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_4, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        }
      } else {
        __pyx_t_1 = __pyx_t_8(__pyx_t_4);
        if (unlikely(!__pyx_t_1)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 73, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_1);
      }
      __Pyx_XDECREF_SET(__pyx_v_k, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "data_handler_v2.py":74
 *     if az_downscale:
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 */
      __pyx_t_1 = PyObject_GetItem(__pyx_v_a, __pyx_v_k); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 74, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_5 = PyNumber_Multiply(__pyx_t_1, __pyx_int_2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 74, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = __Pyx_PyNumber_Int(__pyx_t_5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 74, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_XDECREF_SET(__pyx_v_az_index, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "data_handler_v2.py":75
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 */
      __pyx_t_1 = PySlice_New(Py_None, __pyx_v_size_z, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 75, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_5 = PyTuple_New(2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 75, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_v_k);
      __Pyx_GIVEREF(__pyx_v_k);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_v_k);
      __Pyx_GIVEREF(__pyx_t_1);
      PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_1);
      __pyx_t_1 = 0;
      __pyx_t_1 = PyObject_GetItem(__pyx_v_r, __pyx_t_5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 75, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_5 = PyNumber_Remainder(__pyx_v_az_index, __pyx_v_size_y); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 75, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_2 = PyTuple_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 75, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_5);
      __Pyx_INCREF(__pyx_slice__8);
      __Pyx_GIVEREF(__pyx_slice__8);
      PyTuple_SET_ITEM(__pyx_t_2, 2, __pyx_slice__8);
      __pyx_t_5 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_dump_array, __pyx_t_2, __pyx_t_1) < 0)) __PYX_ERR(0, 75, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

      /* "data_handler_v2.py":76
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *     else:
 *         for k in range(r.shape[0]):
 */
      __pyx_t_1 = PySlice_New(Py_None, __pyx_v_size_z, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_v_k);
      __Pyx_GIVEREF(__pyx_v_k);
      PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_k);
      __Pyx_GIVEREF(__pyx_t_1);
      PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_1);
      __pyx_t_1 = 0;
      __pyx_t_1 = PyObject_GetItem(__pyx_v_r, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = __Pyx_PyInt_AddObjC(__pyx_v_az_index, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_5 = PyNumber_Remainder(__pyx_t_2, __pyx_v_size_y); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyTuple_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_5);
      __Pyx_INCREF(__pyx_slice__9);
      __Pyx_GIVEREF(__pyx_slice__9);
      PyTuple_SET_ITEM(__pyx_t_2, 2, __pyx_slice__9);
      __pyx_t_5 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_dump_array, __pyx_t_2, __pyx_t_1) < 0)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

      /* "data_handler_v2.py":73
 *     # Then we fill the shape
 *     if az_downscale:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

    /* "data_handler_v2.py":72
 *     # As long as it is not legacy, we expand it to 720
 *     # Then we fill the shape
 *     if az_downscale:             # <<<<<<<<<<<<<<
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 */
    goto __pyx_L3;
  }

  /* "data_handler_v2.py":78
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
  /*else*/ {
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_r, __pyx_n_s_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_4, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
      __pyx_t_4 = __pyx_t_1; __Pyx_INCREF(__pyx_t_4); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
    } else {
      __pyx_t_7 = -1; __pyx_t_4 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 78, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = Py_TYPE(__pyx_t_4)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 78, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    for (;;) {
      if (likely(!__pyx_t_8)) {
        if (likely(PyList_CheckExact(__pyx_t_4))) {
          if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_4)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_1 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 78, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_4, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        } else {
          if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 78, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_4, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        }
      } else {
        __pyx_t_1 = __pyx_t_8(__pyx_t_4);
        if (unlikely(!__pyx_t_1)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 78, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_1);
      }
      __Pyx_XDECREF_SET(__pyx_v_k, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "data_handler_v2.py":79
 *     else:
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 * 
 */
      __pyx_t_1 = PyObject_GetItem(__pyx_v_a, __pyx_v_k); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 79, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_2 = PyNumber_Multiply(__pyx_t_1, __pyx_int_2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 79, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = __Pyx_PyNumber_Int(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 79, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_XDECREF_SET(__pyx_v_az_index, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "data_handler_v2.py":80
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 */
      __pyx_t_1 = PySlice_New(Py_None, __pyx_v_size_z, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 80, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 80, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_v_k);
      __Pyx_GIVEREF(__pyx_v_k);
      PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_k);
      __Pyx_GIVEREF(__pyx_t_1);
      PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_1);
      __pyx_t_1 = 0;
      __pyx_t_1 = PyObject_GetItem(__pyx_v_r, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 80, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyNumber_Remainder(__pyx_v_az_index, __pyx_v_size_y); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 80, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 80, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_2);
      __Pyx_INCREF(__pyx_slice__10);
      __Pyx_GIVEREF(__pyx_slice__10);
      PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_slice__10);
      __pyx_t_2 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_dump_array, __pyx_t_5, __pyx_t_1) < 0)) __PYX_ERR(0, 80, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

      /* "data_handler_v2.py":78
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 *         for k in range(r.shape[0]):             # <<<<<<<<<<<<<<
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 */
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __pyx_L3:;

  /* "data_handler_v2.py":61
 * 
 * 
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("data_handler_v2.fill_data_nojit", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_r);
  __Pyx_XDECREF(__pyx_v_a);
  __Pyx_XDECREF(__pyx_v_ad);
  __Pyx_XDECREF(__pyx_v_az_downscale);
  __Pyx_XDECREF(__pyx_v_k);
  __Pyx_XDECREF(__pyx_v_az_index);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":82
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     try:
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_7fill_data_function(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_7fill_data_function = {"fill_data_function", (PyCFunction)__pyx_pw_15data_handler_v2_7fill_data_function, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_7fill_data_function(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_gate_array = 0;
  PyObject *__pyx_v_azimuth_array = 0;
  PyObject *__pyx_v_dump_array = 0;
  PyObject *__pyx_v_elevation_index = 0;
  PyObject *__pyx_v_size_y = 0;
  PyObject *__pyx_v_size_z = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("fill_data_function (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_gate_array,&__pyx_n_s_azimuth_array,&__pyx_n_s_dump_array,&__pyx_n_s_elevation_index,&__pyx_n_s_size_y,&__pyx_n_s_size_z,0};
    PyObject* values[6] = {0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_gate_array)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_azimuth_array)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_function", 1, 6, 6, 1); __PYX_ERR(0, 82, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dump_array)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_function", 1, 6, 6, 2); __PYX_ERR(0, 82, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_elevation_index)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_function", 1, 6, 6, 3); __PYX_ERR(0, 82, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_size_y)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_function", 1, 6, 6, 4); __PYX_ERR(0, 82, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_size_z)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("fill_data_function", 1, 6, 6, 5); __PYX_ERR(0, 82, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "fill_data_function") < 0)) __PYX_ERR(0, 82, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 6) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
    }
    __pyx_v_gate_array = values[0];
    __pyx_v_azimuth_array = values[1];
    __pyx_v_dump_array = values[2];
    __pyx_v_elevation_index = values[3];
    __pyx_v_size_y = values[4];
    __pyx_v_size_z = values[5];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("fill_data_function", 1, 6, 6, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 82, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.fill_data_function", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_6fill_data_function(__pyx_self, __pyx_v_gate_array, __pyx_v_azimuth_array, __pyx_v_dump_array, __pyx_v_elevation_index, __pyx_v_size_y, __pyx_v_size_z);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_6fill_data_function(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_gate_array, PyObject *__pyx_v_azimuth_array, PyObject *__pyx_v_dump_array, PyObject *__pyx_v_elevation_index, PyObject *__pyx_v_size_y, PyObject *__pyx_v_size_z) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  Py_ssize_t __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  __Pyx_RefNannySetupContext("fill_data_function", 0);

  /* "data_handler_v2.py":83
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     try:             # <<<<<<<<<<<<<<
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 *     except:
 */
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
    /*try:*/ {

      /* "data_handler_v2.py":84
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     try:
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)             # <<<<<<<<<<<<<<
 *     except:
 *         logging.warning("Failed to run JIT functions")
 */
      __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_fill_data_jit); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 84, __pyx_L3_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_6 = NULL;
      __pyx_t_7 = 0;
      if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_5))) {
        __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_5);
        if (likely(__pyx_t_6)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
          __Pyx_INCREF(__pyx_t_6);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_5, function);
          __pyx_t_7 = 1;
        }
      }
      __pyx_t_8 = PyTuple_New(6+__pyx_t_7); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 84, __pyx_L3_error)
      __Pyx_GOTREF(__pyx_t_8);
      if (__pyx_t_6) {
        __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_6); __pyx_t_6 = NULL;
      }
      __Pyx_INCREF(__pyx_v_gate_array);
      __Pyx_GIVEREF(__pyx_v_gate_array);
      PyTuple_SET_ITEM(__pyx_t_8, 0+__pyx_t_7, __pyx_v_gate_array);
      __Pyx_INCREF(__pyx_v_azimuth_array);
      __Pyx_GIVEREF(__pyx_v_azimuth_array);
      PyTuple_SET_ITEM(__pyx_t_8, 1+__pyx_t_7, __pyx_v_azimuth_array);
      __Pyx_INCREF(__pyx_v_dump_array);
      __Pyx_GIVEREF(__pyx_v_dump_array);
      PyTuple_SET_ITEM(__pyx_t_8, 2+__pyx_t_7, __pyx_v_dump_array);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_8, 3+__pyx_t_7, __pyx_v_elevation_index);
      __Pyx_INCREF(__pyx_v_size_y);
      __Pyx_GIVEREF(__pyx_v_size_y);
      PyTuple_SET_ITEM(__pyx_t_8, 4+__pyx_t_7, __pyx_v_size_y);
      __Pyx_INCREF(__pyx_v_size_z);
      __Pyx_GIVEREF(__pyx_v_size_z);
      PyTuple_SET_ITEM(__pyx_t_8, 5+__pyx_t_7, __pyx_v_size_z);
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_8, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 84, __pyx_L3_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

      /* "data_handler_v2.py":83
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     try:             # <<<<<<<<<<<<<<
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 *     except:
 */
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L10_try_end;
    __pyx_L3_error:;
    __Pyx_PyThreadState_assign
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;

    /* "data_handler_v2.py":85
 *     try:
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 *     except:             # <<<<<<<<<<<<<<
 *         logging.warning("Failed to run JIT functions")
 *         fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 */
    /*except:*/ {
      __Pyx_AddTraceback("data_handler_v2.fill_data_function", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_4, &__pyx_t_5, &__pyx_t_8) < 0) __PYX_ERR(0, 85, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_8);

      /* "data_handler_v2.py":86
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 *     except:
 *         logging.warning("Failed to run JIT functions")             # <<<<<<<<<<<<<<
 *         fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 * 
 */
      __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 86, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_warning); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 86, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_tuple__11, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 86, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

      /* "data_handler_v2.py":87
 *     except:
 *         logging.warning("Failed to run JIT functions")
 *         fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)             # <<<<<<<<<<<<<<
 * 
 * 
 */
      __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_fill_data_nojit); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 87, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_10 = NULL;
      __pyx_t_7 = 0;
      if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_9))) {
        __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_9);
        if (likely(__pyx_t_10)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
          __Pyx_INCREF(__pyx_t_10);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_9, function);
          __pyx_t_7 = 1;
        }
      }
      __pyx_t_11 = PyTuple_New(6+__pyx_t_7); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 87, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_11);
      if (__pyx_t_10) {
        __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_10); __pyx_t_10 = NULL;
      }
      __Pyx_INCREF(__pyx_v_gate_array);
      __Pyx_GIVEREF(__pyx_v_gate_array);
      PyTuple_SET_ITEM(__pyx_t_11, 0+__pyx_t_7, __pyx_v_gate_array);
      __Pyx_INCREF(__pyx_v_azimuth_array);
      __Pyx_GIVEREF(__pyx_v_azimuth_array);
      PyTuple_SET_ITEM(__pyx_t_11, 1+__pyx_t_7, __pyx_v_azimuth_array);
      __Pyx_INCREF(__pyx_v_dump_array);
      __Pyx_GIVEREF(__pyx_v_dump_array);
      PyTuple_SET_ITEM(__pyx_t_11, 2+__pyx_t_7, __pyx_v_dump_array);
      __Pyx_INCREF(__pyx_v_elevation_index);
      __Pyx_GIVEREF(__pyx_v_elevation_index);
      PyTuple_SET_ITEM(__pyx_t_11, 3+__pyx_t_7, __pyx_v_elevation_index);
      __Pyx_INCREF(__pyx_v_size_y);
      __Pyx_GIVEREF(__pyx_v_size_y);
      PyTuple_SET_ITEM(__pyx_t_11, 4+__pyx_t_7, __pyx_v_size_y);
      __Pyx_INCREF(__pyx_v_size_z);
      __Pyx_GIVEREF(__pyx_v_size_z);
      PyTuple_SET_ITEM(__pyx_t_11, 5+__pyx_t_7, __pyx_v_size_z);
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_11, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      goto __pyx_L4_exception_handled;
    }
    __pyx_L5_except_error:;

    /* "data_handler_v2.py":83
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     try:             # <<<<<<<<<<<<<<
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 *     except:
 */
    __Pyx_PyThreadState_assign
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L4_exception_handled:;
    __Pyx_PyThreadState_assign
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    __pyx_L10_try_end:;
  }

  /* "data_handler_v2.py":82
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     try:
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_AddTraceback("data_handler_v2.fill_data_function", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":112
 *     vel_var_suffix = list("VV")
 * 
 *     def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_1__init__(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_1__init__ = {"__init__", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_1__init__, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_1__init__(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_dataset = 0;
  PyObject *__pyx_v_legacy = 0;
  PyObject *__pyx_v_dualpol = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,&__pyx_n_s_dataset,&__pyx_n_s_legacy,&__pyx_n_s_dualpol,0};
    PyObject* values[4] = {0,0,0,0};
    values[2] = ((PyObject *)((PyObject *)Py_False));
    values[3] = ((PyObject *)((PyObject *)Py_True));
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dataset)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 0, 2, 4, 1); __PYX_ERR(0, 112, __pyx_L3_error)
        }
        case  2:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_legacy);
          if (value) { values[2] = value; kw_args--; }
        }
        case  3:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dualpol);
          if (value) { values[3] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) __PYX_ERR(0, 112, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_self = values[0];
    __pyx_v_dataset = values[1];
    __pyx_v_legacy = values[2];
    __pyx_v_dualpol = values[3];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 0, 2, 4, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 112, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf___init__(__pyx_self, __pyx_v_self, __pyx_v_dataset, __pyx_v_legacy, __pyx_v_dualpol);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf___init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_dataset, PyObject *__pyx_v_legacy, PyObject *__pyx_v_dualpol) {
  PyObject *__pyx_v_p = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  Py_ssize_t __pyx_t_7;
  PyObject *(*__pyx_t_8)(PyObject *);
  PyObject *__pyx_t_9 = NULL;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "data_handler_v2.py":114
 *     def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):
 * 
 *         self.dataset = dataset             # <<<<<<<<<<<<<<
 *         self.legacy_mode = legacy
 *         self.dualpol = dualpol
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_dataset, __pyx_v_dataset) < 0) __PYX_ERR(0, 114, __pyx_L1_error)

  /* "data_handler_v2.py":115
 * 
 *         self.dataset = dataset
 *         self.legacy_mode = legacy             # <<<<<<<<<<<<<<
 *         self.dualpol = dualpol
 * 
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_legacy_mode, __pyx_v_legacy) < 0) __PYX_ERR(0, 115, __pyx_L1_error)

  /* "data_handler_v2.py":116
 *         self.dataset = dataset
 *         self.legacy_mode = legacy
 *         self.dualpol = dualpol             # <<<<<<<<<<<<<<
 * 
 *         self.vcp_mode = self.VcpTable[self.dataset.VolumeCoveragePattern]
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_dualpol, __pyx_v_dualpol) < 0) __PYX_ERR(0, 116, __pyx_L1_error)

  /* "data_handler_v2.py":118
 *         self.dualpol = dualpol
 * 
 *         self.vcp_mode = self.VcpTable[self.dataset.VolumeCoveragePattern]             # <<<<<<<<<<<<<<
 * 
 *         logging.info(self.vcp_mode)
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_VcpTable); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 118, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dataset); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 118, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_VolumeCoveragePattern); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 118, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetItem(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 118, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode, __pyx_t_2) < 0) __PYX_ERR(0, 118, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":120
 *         self.vcp_mode = self.VcpTable[self.dataset.VolumeCoveragePattern]
 * 
 *         logging.info(self.vcp_mode)             # <<<<<<<<<<<<<<
 * 
 *         self.beams_count = 360 if self.legacy_mode else 720
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 120, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_info); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 120, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 120, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":122
 *         logging.info(self.vcp_mode)
 * 
 *         self.beams_count = 360 if self.legacy_mode else 720             # <<<<<<<<<<<<<<
 *         self.gates_count = 230 if self.legacy_mode else 920
 *         self.array_shape = (len(self.vcp_mode), self.beams_count, self.gates_count)
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_legacy_mode); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_6) {
    __Pyx_INCREF(__pyx_int_360);
    __pyx_t_2 = __pyx_int_360;
  } else {
    __Pyx_INCREF(__pyx_int_720);
    __pyx_t_2 = __pyx_int_720;
  }
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_beams_count, __pyx_t_2) < 0) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":123
 * 
 *         self.beams_count = 360 if self.legacy_mode else 720
 *         self.gates_count = 230 if self.legacy_mode else 920             # <<<<<<<<<<<<<<
 *         self.array_shape = (len(self.vcp_mode), self.beams_count, self.gates_count)
 * 
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_legacy_mode); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_6) {
    __Pyx_INCREF(__pyx_int_230);
    __pyx_t_2 = __pyx_int_230;
  } else {
    __Pyx_INCREF(__pyx_int_920);
    __pyx_t_2 = __pyx_int_920;
  }
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_gates_count, __pyx_t_2) < 0) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":124
 *         self.beams_count = 360 if self.legacy_mode else 720
 *         self.gates_count = 230 if self.legacy_mode else 920
 *         self.array_shape = (len(self.vcp_mode), self.beams_count, self.gates_count)             # <<<<<<<<<<<<<<
 * 
 *         # Copy entire data from netCDF file to memory
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_7 = PyObject_Length(__pyx_t_2); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_beams_count); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_gates_count); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_t_5);
  __pyx_t_2 = 0;
  __pyx_t_1 = 0;
  __pyx_t_5 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_array_shape, __pyx_t_3) < 0) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":128
 *         # Copy entire data from netCDF file to memory
 *         self.data_dict = {
 *             "Reflectivity": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "RadialVelocity": numpy.empty(self.array_shape, dtype='f4'),
 *             "SpectrumWidth": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_empty); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_Reflectivity, __pyx_t_4) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":129
 *         self.data_dict = {
 *             "Reflectivity": numpy.empty(self.array_shape, dtype='f4'),
 *             "RadialVelocity": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "SpectrumWidth": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialReflectivity": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_empty); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 129, __pyx_L1_error)
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_RadialVelocity, __pyx_t_1) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":130
 *             "Reflectivity": numpy.empty(self.array_shape, dtype='f4'),
 *             "RadialVelocity": numpy.empty(self.array_shape, dtype='f4'),
 *             "SpectrumWidth": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "DifferentialReflectivity": numpy.empty(self.array_shape, dtype='f4'),
 *             "CorrelationCoefficient": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_empty); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 130, __pyx_L1_error)
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_2, __pyx_t_1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_SpectrumWidth, __pyx_t_5) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":131
 *             "RadialVelocity": numpy.empty(self.array_shape, dtype='f4'),
 *             "SpectrumWidth": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialReflectivity": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "CorrelationCoefficient": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialPhase": numpy.empty(self.array_shape, dtype='f4')
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_empty); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 131, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_DifferentialReflectivity, __pyx_t_4) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":132
 *             "SpectrumWidth": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialReflectivity": numpy.empty(self.array_shape, dtype='f4'),
 *             "CorrelationCoefficient": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "DifferentialPhase": numpy.empty(self.array_shape, dtype='f4')
 *         }  # type: Dict[str, numpy.ndarray]
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_empty); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 132, __pyx_L1_error)
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_CorrelationCoefficient, __pyx_t_1) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":133
 *             "DifferentialReflectivity": numpy.empty(self.array_shape, dtype='f4'),
 *             "CorrelationCoefficient": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialPhase": numpy.empty(self.array_shape, dtype='f4')             # <<<<<<<<<<<<<<
 *         }  # type: Dict[str, numpy.ndarray]
 *         # Fill data
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_empty); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 133, __pyx_L1_error)
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_2, __pyx_t_1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 133, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_DifferentialPhase, __pyx_t_5) < 0) __PYX_ERR(0, 128, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":127
 * 
 *         # Copy entire data from netCDF file to memory
 *         self.data_dict = {             # <<<<<<<<<<<<<<
 *             "Reflectivity": numpy.empty(self.array_shape, dtype='f4'),
 *             "RadialVelocity": numpy.empty(self.array_shape, dtype='f4'),
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_data_dict, __pyx_t_3) < 0) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":136
 *         }  # type: Dict[str, numpy.ndarray]
 *         # Fill data
 *         for p in self.data_dict.values():             # <<<<<<<<<<<<<<
 *             p.fill(-99990.0)
 * 
 */
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_values); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (__pyx_t_5) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_5); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 136, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  } else {
    __pyx_t_3 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 136, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
    __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 136, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 136, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 136, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 136, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 136, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 136, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      }
    } else {
      __pyx_t_3 = __pyx_t_8(__pyx_t_1);
      if (unlikely(!__pyx_t_3)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 136, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_3);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "data_handler_v2.py":137
 *         # Fill data
 *         for p in self.data_dict.values():
 *             p.fill(-99990.0)             # <<<<<<<<<<<<<<
 * 
 *         self.extended_data_dict = {
 */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_p, __pyx_n_s_fill); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 137, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__12, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 137, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

    /* "data_handler_v2.py":136
 *         }  # type: Dict[str, numpy.ndarray]
 *         # Fill data
 *         for p in self.data_dict.values():             # <<<<<<<<<<<<<<
 *             p.fill(-99990.0)
 * 
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":140
 * 
 *         self.extended_data_dict = {
 *             "EchoTop5Z": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "EchoTop10Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "EchoTop20Z": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_empty); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_EchoTop5Z, __pyx_t_4) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":141
 *         self.extended_data_dict = {
 *             "EchoTop5Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "EchoTop10Z": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "EchoTop20Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Avg3x3": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_empty); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 141, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_EchoTop10Z, __pyx_t_3) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":142
 *             "EchoTop5Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "EchoTop10Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "EchoTop20Z": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "Reflectivity_Avg3x3": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Std3x3": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_empty); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 142, __pyx_L1_error)
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_EchoTop20Z, __pyx_t_5) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":143
 *             "EchoTop10Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "EchoTop20Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Avg3x3": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "Reflectivity_Std3x3": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Avg1x5": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_empty); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 143, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Reflectivity_Avg3x3, __pyx_t_4) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":144
 *             "EchoTop20Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Avg3x3": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Std3x3": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "Reflectivity_Avg1x5": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Std1x5": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_empty); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 144, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Reflectivity_Std3x3, __pyx_t_3) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":145
 *             "Reflectivity_Avg3x3": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Std3x3": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Avg1x5": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "Reflectivity_Std1x5": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialReflectivity_": numpy.empty(self.array_shape, dtype='f4'),
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_empty); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 145, __pyx_L1_error)
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Reflectivity_Avg1x5, __pyx_t_5) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":146
 *             "Reflectivity_Std3x3": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Avg1x5": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Std1x5": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "DifferentialReflectivity_": numpy.empty(self.array_shape, dtype='f4'),
 *             "": None
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_empty); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 146, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Reflectivity_Std1x5, __pyx_t_4) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":147
 *             "Reflectivity_Avg1x5": numpy.empty(self.array_shape, dtype='f4'),
 *             "Reflectivity_Std1x5": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialReflectivity_": numpy.empty(self.array_shape, dtype='f4'),             # <<<<<<<<<<<<<<
 *             "": None
 *         }
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_empty); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_array_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_dtype, __pyx_n_s_f4) < 0) __PYX_ERR(0, 147, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_DifferentialReflectivity_2, __pyx_t_3) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":148
 *             "Reflectivity_Std1x5": numpy.empty(self.array_shape, dtype='f4'),
 *             "DifferentialReflectivity_": numpy.empty(self.array_shape, dtype='f4'),
 *             "": None             # <<<<<<<<<<<<<<
 *         }
 * 
 */
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s__13, Py_None) < 0) __PYX_ERR(0, 140, __pyx_L1_error)

  /* "data_handler_v2.py":139
 *             p.fill(-99990.0)
 * 
 *         self.extended_data_dict = {             # <<<<<<<<<<<<<<
 *             "EchoTop5Z": numpy.empty(self.array_shape, dtype='f4'),
 *             "EchoTop10Z": numpy.empty(self.array_shape, dtype='f4'),
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_extended_data_dict, __pyx_t_1) < 0) __PYX_ERR(0, 139, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":154
 * 
 *         # Filling status, ensure everything is filled!
 *         self.filling_table = numpy.zeros((len(self.vcp_mode), len(self.data_dict)), dtype='b1')             # <<<<<<<<<<<<<<
 * 
 *         self.time_data_dict = OrderedDict()  # type: Dict[int, Dict[str, numpy.ma.MaskedArray]
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_zeros); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_7 = PyObject_Length(__pyx_t_1); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_7 = PyObject_Length(__pyx_t_4); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_4);
  __pyx_t_1 = 0;
  __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_dtype, __pyx_n_s_b1) < 0) __PYX_ERR(0, 154, __pyx_L1_error)
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_4, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_filling_table, __pyx_t_1) < 0) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":156
 *         self.filling_table = numpy.zeros((len(self.vcp_mode), len(self.data_dict)), dtype='b1')
 * 
 *         self.time_data_dict = OrderedDict()  # type: Dict[int, Dict[str, numpy.ma.MaskedArray]             # <<<<<<<<<<<<<<
 *         self.dump_data_by_time(self.all_var_names, self.time_data_dict)
 *         self.dump_data_by_time(["elevation" + p for p in self.all_var_suffix], self.time_data_dict)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_OrderedDict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 156, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_4) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 156, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 156, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_time_data_dict, __pyx_t_1) < 0) __PYX_ERR(0, 156, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":157
 * 
 *         self.time_data_dict = OrderedDict()  # type: Dict[int, Dict[str, numpy.ma.MaskedArray]
 *         self.dump_data_by_time(self.all_var_names, self.time_data_dict)             # <<<<<<<<<<<<<<
 *         self.dump_data_by_time(["elevation" + p for p in self.all_var_suffix], self.time_data_dict)
 *         self.dump_data_by_time(["azimuth" + p for p in self.all_var_suffix], self.time_data_dict)
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dump_data_by_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_names); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_time_data_dict); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = NULL;
  __pyx_t_7 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_7 = 1;
    }
  }
  __pyx_t_9 = PyTuple_New(2+__pyx_t_7); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  if (__pyx_t_5) {
    __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_5); __pyx_t_5 = NULL;
  }
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_7, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_7, __pyx_t_3);
  __pyx_t_4 = 0;
  __pyx_t_3 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":158
 *         self.time_data_dict = OrderedDict()  # type: Dict[int, Dict[str, numpy.ma.MaskedArray]
 *         self.dump_data_by_time(self.all_var_names, self.time_data_dict)
 *         self.dump_data_by_time(["elevation" + p for p in self.all_var_suffix], self.time_data_dict)             # <<<<<<<<<<<<<<
 *         self.dump_data_by_time(["azimuth" + p for p in self.all_var_suffix], self.time_data_dict)
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dump_data_by_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 158, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_9 = PyList_New(0); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 158, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_suffix); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 158, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
    __pyx_t_4 = __pyx_t_3; __Pyx_INCREF(__pyx_t_4); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_4 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 158, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_8 = Py_TYPE(__pyx_t_4)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 158, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_4))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_4)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 158, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_4, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 158, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 158, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_4, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 158, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      }
    } else {
      __pyx_t_3 = __pyx_t_8(__pyx_t_4);
      if (unlikely(!__pyx_t_3)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 158, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_3);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_Add(__pyx_n_s_elevation, __pyx_v_p); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 158, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_9, (PyObject*)__pyx_t_3))) __PYX_ERR(0, 158, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_time_data_dict); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 158, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_3 = NULL;
  __pyx_t_7 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_7 = 1;
    }
  }
  __pyx_t_5 = PyTuple_New(2+__pyx_t_7); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 158, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (__pyx_t_3) {
    __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3); __pyx_t_3 = NULL;
  }
  __Pyx_GIVEREF(__pyx_t_9);
  PyTuple_SET_ITEM(__pyx_t_5, 0+__pyx_t_7, __pyx_t_9);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_5, 1+__pyx_t_7, __pyx_t_4);
  __pyx_t_9 = 0;
  __pyx_t_4 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 158, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":159
 *         self.dump_data_by_time(self.all_var_names, self.time_data_dict)
 *         self.dump_data_by_time(["elevation" + p for p in self.all_var_suffix], self.time_data_dict)
 *         self.dump_data_by_time(["azimuth" + p for p in self.all_var_suffix], self.time_data_dict)             # <<<<<<<<<<<<<<
 * 
 *         self.fill_data(first_pass=True)
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dump_data_by_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = PyList_New(0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_suffix); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (likely(PyList_CheckExact(__pyx_t_4)) || PyTuple_CheckExact(__pyx_t_4)) {
    __pyx_t_9 = __pyx_t_4; __Pyx_INCREF(__pyx_t_9); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_9 = PyObject_GetIter(__pyx_t_4); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 159, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_8 = Py_TYPE(__pyx_t_9)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 159, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_9))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_9)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_4 = PyList_GET_ITEM(__pyx_t_9, __pyx_t_7); __Pyx_INCREF(__pyx_t_4); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 159, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_9, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 159, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_9)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_9, __pyx_t_7); __Pyx_INCREF(__pyx_t_4); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 159, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_9, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 159, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      }
    } else {
      __pyx_t_4 = __pyx_t_8(__pyx_t_9);
      if (unlikely(!__pyx_t_4)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 159, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_4);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = PyNumber_Add(__pyx_n_s_azimuth, __pyx_v_p); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 159, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_5, (PyObject*)__pyx_t_4))) __PYX_ERR(0, 159, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_time_data_dict); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __pyx_t_4 = NULL;
  __pyx_t_7 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_7 = 1;
    }
  }
  __pyx_t_3 = PyTuple_New(2+__pyx_t_7); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (__pyx_t_4) {
    __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_4); __pyx_t_4 = NULL;
  }
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_7, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_9);
  PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_7, __pyx_t_9);
  __pyx_t_5 = 0;
  __pyx_t_9 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":161
 *         self.dump_data_by_time(["azimuth" + p for p in self.all_var_suffix], self.time_data_dict)
 * 
 *         self.fill_data(first_pass=True)             # <<<<<<<<<<<<<<
 * 
 *     def is_filled(self):
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_fill_data); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_first_pass, Py_True) < 0) __PYX_ERR(0, 161, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_empty_tuple, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":112
 *     vel_var_suffix = list("VV")
 * 
 *     def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_p);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":163
 *         self.fill_data(first_pass=True)
 * 
 *     def is_filled(self):             # <<<<<<<<<<<<<<
 *         # All filled means all is True
 *         return numpy.all(numpy.logical_not(self.filling_table))  # type: bool
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_3is_filled(PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_3is_filled = {"is_filled", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_3is_filled, METH_O, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_3is_filled(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("is_filled (wrapper)", 0);
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_2is_filled(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_2is_filled(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  __Pyx_RefNannySetupContext("is_filled", 0);

  /* "data_handler_v2.py":165
 *     def is_filled(self):
 *         # All filled means all is True
 *         return numpy.all(numpy.logical_not(self.filling_table))  # type: bool             # <<<<<<<<<<<<<<
 * 
 *     # Dump helper function
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 165, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_all); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 165, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 165, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_logical_not); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 165, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_filling_table); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 165, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_6 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_6)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_6);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
    }
  }
  if (!__pyx_t_6) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_6); __pyx_t_6 = NULL;
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_7, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5); __pyx_t_5 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_7, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "data_handler_v2.py":163
 *         self.fill_data(first_pass=True)
 * 
 *     def is_filled(self):             # <<<<<<<<<<<<<<
 *         # All filled means all is True
 *         return numpy.all(numpy.logical_not(self.filling_table))  # type: bool
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.is_filled", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":168
 * 
 *     # Dump helper function
 *     def __dump(self, var, time_var, dump_dict):             # <<<<<<<<<<<<<<
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_5__dump(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_5__dump = {"__dump", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_5__dump, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_5__dump(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_var = 0;
  PyObject *__pyx_v_time_var = 0;
  PyObject *__pyx_v_dump_dict = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dump (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,&__pyx_n_s_var,&__pyx_n_s_time_var,&__pyx_n_s_dump_dict,0};
    PyObject* values[4] = {0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_var)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__dump", 1, 4, 4, 1); __PYX_ERR(0, 168, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_time_var)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__dump", 1, 4, 4, 2); __PYX_ERR(0, 168, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dump_dict)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__dump", 1, 4, 4, 3); __PYX_ERR(0, 168, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__dump") < 0)) __PYX_ERR(0, 168, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 4) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
    }
    __pyx_v_self = values[0];
    __pyx_v_var = values[1];
    __pyx_v_time_var = values[2];
    __pyx_v_dump_dict = values[3];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__dump", 1, 4, 4, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 168, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__dump", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_4__dump(__pyx_self, __pyx_v_self, __pyx_v_var, __pyx_v_time_var, __pyx_v_dump_dict);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_4__dump(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_var, PyObject *__pyx_v_time_var, PyObject *__pyx_v_dump_dict) {
  PyObject *__pyx_v_time_var_dump = NULL;
  PyObject *__pyx_v_var_dump = NULL;
  PyObject *__pyx_v_scan_start_time = NULL;
  PyObject *__pyx_v_t = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  Py_ssize_t __pyx_t_9;
  PyObject *(*__pyx_t_10)(PyObject *);
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  int __pyx_t_15;
  PyObject *__pyx_t_16 = NULL;
  PyObject *__pyx_t_17 = NULL;
  PyObject *__pyx_t_18 = NULL;
  __Pyx_RefNannySetupContext("__dump", 0);

  /* "data_handler_v2.py":169
 *     # Dump helper function
 *     def __dump(self, var, time_var, dump_dict):
 *         if time_var not in ds.variables or var not in ds.variables:             # <<<<<<<<<<<<<<
 *             return
 *         time_var_dump = ds.variables[time_var][:]
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_ds); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 169, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_variables); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 169, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = (__Pyx_PySequence_ContainsTF(__pyx_v_time_var, __pyx_t_3, Py_NE)); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 169, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_5 = (__pyx_t_4 != 0);
  if (!__pyx_t_5) {
  } else {
    __pyx_t_1 = __pyx_t_5;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_ds); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 169, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_variables); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 169, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_5 = (__Pyx_PySequence_ContainsTF(__pyx_v_var, __pyx_t_2, Py_NE)); if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 169, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = (__pyx_t_5 != 0);
  __pyx_t_1 = __pyx_t_4;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_1) {

    /* "data_handler_v2.py":170
 *     def __dump(self, var, time_var, dump_dict):
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return             # <<<<<<<<<<<<<<
 *         time_var_dump = ds.variables[time_var][:]
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])
 */
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;

    /* "data_handler_v2.py":169
 *     # Dump helper function
 *     def __dump(self, var, time_var, dump_dict):
 *         if time_var not in ds.variables or var not in ds.variables:             # <<<<<<<<<<<<<<
 *             return
 *         time_var_dump = ds.variables[time_var][:]
 */
  }

  /* "data_handler_v2.py":171
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return
 *         time_var_dump = ds.variables[time_var][:]             # <<<<<<<<<<<<<<
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_ds); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 171, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_variables); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 171, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_GetItem(__pyx_t_3, __pyx_v_time_var); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 171, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetSlice(__pyx_t_2, 0, 0, NULL, NULL, &__pyx_slice__14, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 171, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_time_var_dump = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "data_handler_v2.py":172
 *             return
 *         time_var_dump = ds.variables[time_var][:]
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])             # <<<<<<<<<<<<<<
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
 *         scan_start_time = time_var_dump.min(axis=1)
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_fix_variable); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dataset); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_variables); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyObject_GetItem(__pyx_t_7, __pyx_v_var); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_7 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_7)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_7) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
  } else {
    __pyx_t_8 = PyTuple_New(1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_7); __pyx_t_7 = NULL;
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_8, 0+1, __pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_8, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_var_dump = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "data_handler_v2.py":173
 *         time_var_dump = ds.variables[time_var][:]
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data             # <<<<<<<<<<<<<<
 *         scan_start_time = time_var_dump.min(axis=1)
 *         for t in range(scan_start_time.shape[0]):
 */
  #ifndef CYTHON_WITHOUT_ASSERTIONS
  if (unlikely(!Py_OptimizeFlag)) {
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_time_var_dump, __pyx_n_s_min); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 173, __pyx_L1_error)
    __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_empty_tuple, __pyx_t_2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_data); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = PyObject_GetItem(__pyx_v_time_var_dump, __pyx_tuple__16); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_data); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = PyObject_RichCompare(__pyx_t_2, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_8); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_t_8); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    if (unlikely(!__pyx_t_1)) {
      PyErr_SetNone(PyExc_AssertionError);
      __PYX_ERR(0, 173, __pyx_L1_error)
    }
  }
  #endif

  /* "data_handler_v2.py":174
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
 *         scan_start_time = time_var_dump.min(axis=1)             # <<<<<<<<<<<<<<
 *         for t in range(scan_start_time.shape[0]):
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 */
  __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_time_var_dump, __pyx_n_s_min); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 174, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 174, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 174, __pyx_L1_error)
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_empty_tuple, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 174, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_scan_start_time = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "data_handler_v2.py":175
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
 *         scan_start_time = time_var_dump.min(axis=1)
 *         for t in range(scan_start_time.shape[0]):             # <<<<<<<<<<<<<<
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 *             try:
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_scan_start_time, __pyx_n_s_shape); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 175, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_2, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 175, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 175, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 175, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
    __pyx_t_2 = __pyx_t_3; __Pyx_INCREF(__pyx_t_2); __pyx_t_9 = 0;
    __pyx_t_10 = NULL;
  } else {
    __pyx_t_9 = -1; __pyx_t_2 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 175, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_10 = Py_TYPE(__pyx_t_2)->tp_iternext; if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 175, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  for (;;) {
    if (likely(!__pyx_t_10)) {
      if (likely(PyList_CheckExact(__pyx_t_2))) {
        if (__pyx_t_9 >= PyList_GET_SIZE(__pyx_t_2)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_9); __Pyx_INCREF(__pyx_t_3); __pyx_t_9++; if (unlikely(0 < 0)) __PYX_ERR(0, 175, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_2, __pyx_t_9); __pyx_t_9++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 175, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      } else {
        if (__pyx_t_9 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_9); __Pyx_INCREF(__pyx_t_3); __pyx_t_9++; if (unlikely(0 < 0)) __PYX_ERR(0, 175, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_2, __pyx_t_9); __pyx_t_9++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 175, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      }
    } else {
      __pyx_t_3 = __pyx_t_10(__pyx_t_2);
      if (unlikely(!__pyx_t_3)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 175, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_3);
    }
    __Pyx_XDECREF_SET(__pyx_v_t, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "data_handler_v2.py":176
 *         scan_start_time = time_var_dump.min(axis=1)
 *         for t in range(scan_start_time.shape[0]):
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))             # <<<<<<<<<<<<<<
 *             try:
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]
 */
    __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 176, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_debug); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 176, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = PyObject_GetItem(__pyx_v_scan_start_time, __pyx_v_t); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 176, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_7 = PyTuple_New(3); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 176, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_INCREF(__pyx_v_var);
    __Pyx_GIVEREF(__pyx_v_var);
    PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_v_var);
    __Pyx_INCREF(__pyx_v_t);
    __Pyx_GIVEREF(__pyx_v_t);
    PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_v_t);
    __Pyx_GIVEREF(__pyx_t_8);
    PyTuple_SET_ITEM(__pyx_t_7, 2, __pyx_t_8);
    __pyx_t_8 = 0;
    __pyx_t_8 = __Pyx_PyString_Format(__pyx_kp_s_s_d_d, __pyx_t_7); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 176, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (!__pyx_t_7) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 176, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else {
      __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 176, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_7); __pyx_t_7 = NULL;
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_11, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 176, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "data_handler_v2.py":177
 *         for t in range(scan_start_time.shape[0]):
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 *             try:             # <<<<<<<<<<<<<<
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]
 *             except KeyError:
 */
    {
      __Pyx_PyThreadState_declare
      __Pyx_PyThreadState_assign
      __Pyx_ExceptionSave(&__pyx_t_12, &__pyx_t_13, &__pyx_t_14);
      __Pyx_XGOTREF(__pyx_t_12);
      __Pyx_XGOTREF(__pyx_t_13);
      __Pyx_XGOTREF(__pyx_t_14);
      /*try:*/ {

        /* "data_handler_v2.py":178
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 *             try:
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]             # <<<<<<<<<<<<<<
 *             except KeyError:
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})
 */
        __pyx_t_3 = PyObject_GetItem(__pyx_v_var_dump, __pyx_v_t); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 178, __pyx_L8_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_6 = PyObject_GetItem(__pyx_v_scan_start_time, __pyx_v_t); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 178, __pyx_L8_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_11 = PyObject_GetItem(__pyx_v_dump_dict, __pyx_t_6); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 178, __pyx_L8_error)
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        if (unlikely(PyObject_SetItem(__pyx_t_11, __pyx_v_var, __pyx_t_3) < 0)) __PYX_ERR(0, 178, __pyx_L8_error)
        __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

        /* "data_handler_v2.py":177
 *         for t in range(scan_start_time.shape[0]):
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 *             try:             # <<<<<<<<<<<<<<
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]
 *             except KeyError:
 */
      }
      __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
      __Pyx_XDECREF(__pyx_t_13); __pyx_t_13 = 0;
      __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
      goto __pyx_L15_try_end;
      __pyx_L8_error:;
      __Pyx_PyThreadState_assign
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
      __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;

      /* "data_handler_v2.py":179
 *             try:
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]
 *             except KeyError:             # <<<<<<<<<<<<<<
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})
 * 
 */
      __pyx_t_15 = __Pyx_PyErr_ExceptionMatches(__pyx_builtin_KeyError);
      if (__pyx_t_15) {
        __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__dump", __pyx_clineno, __pyx_lineno, __pyx_filename);
        if (__Pyx_GetException(&__pyx_t_3, &__pyx_t_11, &__pyx_t_6) < 0) __PYX_ERR(0, 179, __pyx_L10_except_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_GOTREF(__pyx_t_6);

        /* "data_handler_v2.py":180
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]
 *             except KeyError:
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})             # <<<<<<<<<<<<<<
 * 
 *     def dump_data_by_time(self, dump_var_names, dump_target):
 */
        __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_OrderedDict); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 180, __pyx_L10_except_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_16 = PyDict_New(); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 180, __pyx_L10_except_error)
        __Pyx_GOTREF(__pyx_t_16);
        __pyx_t_17 = PyObject_GetItem(__pyx_v_var_dump, __pyx_v_t); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 180, __pyx_L10_except_error)
        __Pyx_GOTREF(__pyx_t_17);
        if (PyDict_SetItem(__pyx_t_16, __pyx_v_var, __pyx_t_17) < 0) __PYX_ERR(0, 180, __pyx_L10_except_error)
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        __pyx_t_17 = NULL;
        if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_7))) {
          __pyx_t_17 = PyMethod_GET_SELF(__pyx_t_7);
          if (likely(__pyx_t_17)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
            __Pyx_INCREF(__pyx_t_17);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_7, function);
          }
        }
        if (!__pyx_t_17) {
          __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_16); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 180, __pyx_L10_except_error)
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __Pyx_GOTREF(__pyx_t_8);
        } else {
          __pyx_t_18 = PyTuple_New(1+1); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 180, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __Pyx_GIVEREF(__pyx_t_17); PyTuple_SET_ITEM(__pyx_t_18, 0, __pyx_t_17); __pyx_t_17 = NULL;
          __Pyx_GIVEREF(__pyx_t_16);
          PyTuple_SET_ITEM(__pyx_t_18, 0+1, __pyx_t_16);
          __pyx_t_16 = 0;
          __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_18, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 180, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
        }
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
        __pyx_t_7 = PyObject_GetItem(__pyx_v_scan_start_time, __pyx_v_t); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 180, __pyx_L10_except_error)
        __Pyx_GOTREF(__pyx_t_7);
        if (unlikely(PyObject_SetItem(__pyx_v_dump_dict, __pyx_t_7, __pyx_t_8) < 0)) __PYX_ERR(0, 180, __pyx_L10_except_error)
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        goto __pyx_L9_exception_handled;
      }
      goto __pyx_L10_except_error;
      __pyx_L10_except_error:;

      /* "data_handler_v2.py":177
 *         for t in range(scan_start_time.shape[0]):
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 *             try:             # <<<<<<<<<<<<<<
 *                 dump_dict[scan_start_time[t]][var] = var_dump[t]
 *             except KeyError:
 */
      __Pyx_PyThreadState_assign
      __Pyx_XGIVEREF(__pyx_t_12);
      __Pyx_XGIVEREF(__pyx_t_13);
      __Pyx_XGIVEREF(__pyx_t_14);
      __Pyx_ExceptionReset(__pyx_t_12, __pyx_t_13, __pyx_t_14);
      goto __pyx_L1_error;
      __pyx_L9_exception_handled:;
      __Pyx_PyThreadState_assign
      __Pyx_XGIVEREF(__pyx_t_12);
      __Pyx_XGIVEREF(__pyx_t_13);
      __Pyx_XGIVEREF(__pyx_t_14);
      __Pyx_ExceptionReset(__pyx_t_12, __pyx_t_13, __pyx_t_14);
      __pyx_L15_try_end:;
    }

    /* "data_handler_v2.py":175
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
 *         scan_start_time = time_var_dump.min(axis=1)
 *         for t in range(scan_start_time.shape[0]):             # <<<<<<<<<<<<<<
 *             logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
 *             try:
 */
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":168
 * 
 *     # Dump helper function
 *     def __dump(self, var, time_var, dump_dict):             # <<<<<<<<<<<<<<
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_XDECREF(__pyx_t_16);
  __Pyx_XDECREF(__pyx_t_17);
  __Pyx_XDECREF(__pyx_t_18);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__dump", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_time_var_dump);
  __Pyx_XDECREF(__pyx_v_var_dump);
  __Pyx_XDECREF(__pyx_v_scan_start_time);
  __Pyx_XDECREF(__pyx_v_t);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":182
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})
 * 
 *     def dump_data_by_time(self, dump_var_names, dump_target):             # <<<<<<<<<<<<<<
 *         assert len(dump_var_names) == len(self.all_var_suffix)
 *         for i in range(len(dump_var_names)):
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_7dump_data_by_time(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_7dump_data_by_time = {"dump_data_by_time", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_7dump_data_by_time, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_7dump_data_by_time(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_dump_var_names = 0;
  PyObject *__pyx_v_dump_target = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("dump_data_by_time (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,&__pyx_n_s_dump_var_names,&__pyx_n_s_dump_target,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dump_var_names)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("dump_data_by_time", 1, 3, 3, 1); __PYX_ERR(0, 182, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dump_target)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("dump_data_by_time", 1, 3, 3, 2); __PYX_ERR(0, 182, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "dump_data_by_time") < 0)) __PYX_ERR(0, 182, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v_self = values[0];
    __pyx_v_dump_var_names = values[1];
    __pyx_v_dump_target = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("dump_data_by_time", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 182, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.dump_data_by_time", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_6dump_data_by_time(__pyx_self, __pyx_v_self, __pyx_v_dump_var_names, __pyx_v_dump_target);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_6dump_data_by_time(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_dump_var_names, PyObject *__pyx_v_dump_target) {
  Py_ssize_t __pyx_v_i;
  PyObject *__pyx_v_var = NULL;
  PyObject *__pyx_v_time_var = NULL;
  PyObject *__pyx_v_var_hi = NULL;
  PyObject *__pyx_v_time_var_hi = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  __Pyx_RefNannySetupContext("dump_data_by_time", 0);

  /* "data_handler_v2.py":183
 * 
 *     def dump_data_by_time(self, dump_var_names, dump_target):
 *         assert len(dump_var_names) == len(self.all_var_suffix)             # <<<<<<<<<<<<<<
 *         for i in range(len(dump_var_names)):
 *             # Dump general variables
 */
  #ifndef CYTHON_WITHOUT_ASSERTIONS
  if (unlikely(!Py_OptimizeFlag)) {
    __pyx_t_1 = PyObject_Length(__pyx_v_dump_var_names); if (unlikely(__pyx_t_1 == -1)) __PYX_ERR(0, 183, __pyx_L1_error)
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_suffix); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 183, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyObject_Length(__pyx_t_2); if (unlikely(__pyx_t_3 == -1)) __PYX_ERR(0, 183, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (unlikely(!((__pyx_t_1 == __pyx_t_3) != 0))) {
      PyErr_SetNone(PyExc_AssertionError);
      __PYX_ERR(0, 183, __pyx_L1_error)
    }
  }
  #endif

  /* "data_handler_v2.py":184
 *     def dump_data_by_time(self, dump_var_names, dump_target):
 *         assert len(dump_var_names) == len(self.all_var_suffix)
 *         for i in range(len(dump_var_names)):             # <<<<<<<<<<<<<<
 *             # Dump general variables
 *             var = dump_var_names[i]
 */
  __pyx_t_3 = PyObject_Length(__pyx_v_dump_var_names); if (unlikely(__pyx_t_3 == -1)) __PYX_ERR(0, 184, __pyx_L1_error)
  for (__pyx_t_1 = 0; __pyx_t_1 < __pyx_t_3; __pyx_t_1+=1) {
    __pyx_v_i = __pyx_t_1;

    /* "data_handler_v2.py":186
 *         for i in range(len(dump_var_names)):
 *             # Dump general variables
 *             var = dump_var_names[i]             # <<<<<<<<<<<<<<
 *             time_var = "time" + self.all_var_suffix[i]
 *             self.__dump(var, time_var, dump_target)
 */
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_v_dump_var_names, __pyx_v_i, Py_ssize_t, 1, PyInt_FromSsize_t, 0, 1, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 186, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_XDECREF_SET(__pyx_v_var, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "data_handler_v2.py":187
 *             # Dump general variables
 *             var = dump_var_names[i]
 *             time_var = "time" + self.all_var_suffix[i]             # <<<<<<<<<<<<<<
 *             self.__dump(var, time_var, dump_target)
 *             # Dump high_resolution variables
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_suffix); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = __Pyx_GetItemInt(__pyx_t_2, __pyx_v_i, Py_ssize_t, 1, PyInt_FromSsize_t, 0, 1, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyNumber_Add(__pyx_n_s_time, __pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_XDECREF_SET(__pyx_v_time_var, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "data_handler_v2.py":188
 *             var = dump_var_names[i]
 *             time_var = "time" + self.all_var_suffix[i]
 *             self.__dump(var, time_var, dump_target)             # <<<<<<<<<<<<<<
 *             # Dump high_resolution variables
 *             var_hi = var + "_HI"
 */
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_RadarNetcdf__dump); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 188, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = NULL;
    __pyx_t_6 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_6 = 1;
      }
    }
    __pyx_t_7 = PyTuple_New(3+__pyx_t_6); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 188, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (__pyx_t_5) {
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5); __pyx_t_5 = NULL;
    }
    __Pyx_INCREF(__pyx_v_var);
    __Pyx_GIVEREF(__pyx_v_var);
    PyTuple_SET_ITEM(__pyx_t_7, 0+__pyx_t_6, __pyx_v_var);
    __Pyx_INCREF(__pyx_v_time_var);
    __Pyx_GIVEREF(__pyx_v_time_var);
    PyTuple_SET_ITEM(__pyx_t_7, 1+__pyx_t_6, __pyx_v_time_var);
    __Pyx_INCREF(__pyx_v_dump_target);
    __Pyx_GIVEREF(__pyx_v_dump_target);
    PyTuple_SET_ITEM(__pyx_t_7, 2+__pyx_t_6, __pyx_v_dump_target);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_7, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 188, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "data_handler_v2.py":190
 *             self.__dump(var, time_var, dump_target)
 *             # Dump high_resolution variables
 *             var_hi = var + "_HI"             # <<<<<<<<<<<<<<
 *             time_var_hi = time_var + "_HI"
 *             self.__dump(var_hi, time_var_hi, dump_target)
 */
    __pyx_t_2 = PyNumber_Add(__pyx_v_var, __pyx_n_s_HI); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 190, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_XDECREF_SET(__pyx_v_var_hi, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "data_handler_v2.py":191
 *             # Dump high_resolution variables
 *             var_hi = var + "_HI"
 *             time_var_hi = time_var + "_HI"             # <<<<<<<<<<<<<<
 *             self.__dump(var_hi, time_var_hi, dump_target)
 * 
 */
    __pyx_t_2 = PyNumber_Add(__pyx_v_time_var, __pyx_n_s_HI); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 191, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_XDECREF_SET(__pyx_v_time_var_hi, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "data_handler_v2.py":192
 *             var_hi = var + "_HI"
 *             time_var_hi = time_var + "_HI"
 *             self.__dump(var_hi, time_var_hi, dump_target)             # <<<<<<<<<<<<<<
 * 
 *     @staticmethod
 */
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_RadarNetcdf__dump); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 192, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_7 = NULL;
    __pyx_t_6 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_6 = 1;
      }
    }
    __pyx_t_5 = PyTuple_New(3+__pyx_t_6); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 192, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (__pyx_t_7) {
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_7); __pyx_t_7 = NULL;
    }
    __Pyx_INCREF(__pyx_v_var_hi);
    __Pyx_GIVEREF(__pyx_v_var_hi);
    PyTuple_SET_ITEM(__pyx_t_5, 0+__pyx_t_6, __pyx_v_var_hi);
    __Pyx_INCREF(__pyx_v_time_var_hi);
    __Pyx_GIVEREF(__pyx_v_time_var_hi);
    PyTuple_SET_ITEM(__pyx_t_5, 1+__pyx_t_6, __pyx_v_time_var_hi);
    __Pyx_INCREF(__pyx_v_dump_target);
    __Pyx_GIVEREF(__pyx_v_dump_target);
    PyTuple_SET_ITEM(__pyx_t_5, 2+__pyx_t_6, __pyx_v_dump_target);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 192, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }

  /* "data_handler_v2.py":182
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})
 * 
 *     def dump_data_by_time(self, dump_var_names, dump_target):             # <<<<<<<<<<<<<<
 *         assert len(dump_var_names) == len(self.all_var_suffix)
 *         for i in range(len(dump_var_names)):
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.dump_data_by_time", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_var);
  __Pyx_XDECREF(__pyx_v_time_var);
  __Pyx_XDECREF(__pyx_v_var_hi);
  __Pyx_XDECREF(__pyx_v_time_var_hi);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":195
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_9__fix_variable__(PyObject *__pyx_self, PyObject *__pyx_v_v); /*proto*/
static char __pyx_doc_15data_handler_v2_11RadarNetcdf_8__fix_variable__[] = "Fix wrong unsigned value";
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_9__fix_variable__ = {"__fix_variable__", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_9__fix_variable__, METH_O, __pyx_doc_15data_handler_v2_11RadarNetcdf_8__fix_variable__};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_9__fix_variable__(PyObject *__pyx_self, PyObject *__pyx_v_v) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__fix_variable__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_8__fix_variable__(__pyx_self, ((PyObject *)__pyx_v_v));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_8__fix_variable__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_v) {
  PyObject *__pyx_v__v = NULL;
  PyObject *__pyx_v__v1 = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  Py_ssize_t __pyx_t_9;
  __Pyx_RefNannySetupContext("__fix_variable__", 0);

  /* "data_handler_v2.py":197
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:             # <<<<<<<<<<<<<<
 *             v.set_auto_scale(False)
 *             # Dump out
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_add_offset, __pyx_t_2, Py_EQ)); if (unlikely(__pyx_t_3 < 0)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = (__pyx_t_3 != 0);
  if (__pyx_t_4) {
  } else {
    __pyx_t_1 = __pyx_t_4;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_scale_factor, __pyx_t_2, Py_EQ)); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_3 = (__pyx_t_4 != 0);
  if (__pyx_t_3) {
  } else {
    __pyx_t_1 = __pyx_t_3;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_Unsigned); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_1 = __pyx_t_3;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_1) {

    /* "data_handler_v2.py":198
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 *             v.set_auto_scale(False)             # <<<<<<<<<<<<<<
 *             # Dump out
 *             _v = v[:]
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_set_auto_scale); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 198, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__17, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 198, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

    /* "data_handler_v2.py":200
 *             v.set_auto_scale(False)
 *             # Dump out
 *             _v = v[:]             # <<<<<<<<<<<<<<
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             logging.info("Fix unsigned variable:" + v.name)
 */
    __pyx_t_5 = __Pyx_PyObject_GetSlice(__pyx_v_v, 0, 0, NULL, NULL, &__pyx_slice__18, 0, 0, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 200, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_v__v = __pyx_t_5;
    __pyx_t_5 = 0;

    /* "data_handler_v2.py":201
 *             # Dump out
 *             _v = v[:]
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset             # <<<<<<<<<<<<<<
 *             logging.info("Fix unsigned variable:" + v.name)
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v__v, __pyx_n_s_data); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_view); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_datatype); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_7 = PyTuple_New(1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_7, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = PyNumber_Add(__pyx_n_s_u, __pyx_t_2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_7); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else {
      __pyx_t_8 = PyTuple_New(1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_GIVEREF(__pyx_t_7);
      PyTuple_SET_ITEM(__pyx_t_8, 0+1, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_8, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_scale_factor); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = PyNumber_Multiply(__pyx_t_5, __pyx_t_6); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_add_offset); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_5 = PyNumber_Add(__pyx_t_8, __pyx_t_6); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_v__v1 = __pyx_t_5;
    __pyx_t_5 = 0;

    /* "data_handler_v2.py":202
 *             _v = v[:]
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             logging.info("Fix unsigned variable:" + v.name)             # <<<<<<<<<<<<<<
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 *         else:
 */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_info); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_name); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = PyNumber_Add(__pyx_kp_s_Fix_unsigned_variable, __pyx_t_6); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_8))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_8);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_8);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_8, function);
      }
    }
    if (!__pyx_t_6) {
      __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_8, __pyx_t_7); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else {
      __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_6); __pyx_t_6 = NULL;
      __Pyx_GIVEREF(__pyx_t_7);
      PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_t_2, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

    /* "data_handler_v2.py":203
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             logging.info("Fix unsigned variable:" + v.name)
 *             return numpy.ma.MaskedArray(_v1, _v.mask)             # <<<<<<<<<<<<<<
 *         else:
 *             return v[:]
 */
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_ma); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_MaskedArray); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v__v, __pyx_n_s_mask); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_7 = NULL;
    __pyx_t_9 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_8))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_8);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_8);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_8, function);
        __pyx_t_9 = 1;
      }
    }
    __pyx_t_6 = PyTuple_New(2+__pyx_t_9); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    if (__pyx_t_7) {
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_7); __pyx_t_7 = NULL;
    }
    __Pyx_INCREF(__pyx_v__v1);
    __Pyx_GIVEREF(__pyx_v__v1);
    PyTuple_SET_ITEM(__pyx_t_6, 0+__pyx_t_9, __pyx_v__v1);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_6, 1+__pyx_t_9, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_t_6, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_r = __pyx_t_5;
    __pyx_t_5 = 0;
    goto __pyx_L0;

    /* "data_handler_v2.py":197
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:             # <<<<<<<<<<<<<<
 *             v.set_auto_scale(False)
 *             # Dump out
 */
  }

  /* "data_handler_v2.py":205
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 *         else:
 *             return v[:]             # <<<<<<<<<<<<<<
 * 
 *     def first_pass(self):
 */
  /*else*/ {
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_5 = __Pyx_PyObject_GetSlice(__pyx_v_v, 0, 0, NULL, NULL, &__pyx_slice__19, 0, 0, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 205, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_r = __pyx_t_5;
    __pyx_t_5 = 0;
    goto __pyx_L0;
  }

  /* "data_handler_v2.py":195
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__fix_variable__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v__v);
  __Pyx_XDECREF(__pyx_v__v1);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":207
 *             return v[:]
 * 
 *     def first_pass(self):             # <<<<<<<<<<<<<<
 *         pass
 * 
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_11first_pass(PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_11first_pass = {"first_pass", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_11first_pass, METH_O, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_11first_pass(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("first_pass (wrapper)", 0);
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_10first_pass(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_10first_pass(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("first_pass", 0);

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":211
 * 
 *     @jit
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):             # <<<<<<<<<<<<<<
 *         mode = "_HI" if id_var + "_HI" in i else ""
 *         elevation = i[id_var + mode].mean()
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_13__fill_data_internal(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_13__fill_data_internal = {"__fill_data_internal", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_13__fill_data_internal, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_13__fill_data_internal(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_i = 0;
  PyObject *__pyx_v_id_var = 0;
  PyObject *__pyx_v_var_names = 0;
  PyObject *__pyx_v_var_suffix = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__fill_data_internal (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,&__pyx_n_s_i,&__pyx_n_s_id_var,&__pyx_n_s_var_names,&__pyx_n_s_var_suffix,0};
    PyObject* values[5] = {0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_i)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__fill_data_internal", 1, 5, 5, 1); __PYX_ERR(0, 211, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_id_var)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__fill_data_internal", 1, 5, 5, 2); __PYX_ERR(0, 211, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_var_names)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__fill_data_internal", 1, 5, 5, 3); __PYX_ERR(0, 211, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_var_suffix)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__fill_data_internal", 1, 5, 5, 4); __PYX_ERR(0, 211, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__fill_data_internal") < 0)) __PYX_ERR(0, 211, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 5) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
    }
    __pyx_v_self = values[0];
    __pyx_v_i = values[1];
    __pyx_v_id_var = values[2];
    __pyx_v_var_names = values[3];
    __pyx_v_var_suffix = values[4];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__fill_data_internal", 1, 5, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 211, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__fill_data_internal", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_12__fill_data_internal(__pyx_self, __pyx_v_self, __pyx_v_i, __pyx_v_id_var, __pyx_v_var_names, __pyx_v_var_suffix);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_12__fill_data_internal(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_i, PyObject *__pyx_v_id_var, PyObject *__pyx_v_var_names, PyObject *__pyx_v_var_suffix) {
  PyObject *__pyx_v_mode = NULL;
  PyObject *__pyx_v_elevation = NULL;
  PyObject *__pyx_v_elevation_index = NULL;
  PyObject *__pyx_v_j = NULL;
  PyObject *__pyx_v_s = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *(*__pyx_t_8)(PyObject *);
  PyObject *(*__pyx_t_9)(PyObject *);
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  Py_ssize_t __pyx_t_14;
  PyObject *__pyx_t_15 = NULL;
  __Pyx_RefNannySetupContext("__fill_data_internal", 0);

  /* "data_handler_v2.py":212
 *     @jit
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):
 *         mode = "_HI" if id_var + "_HI" in i else ""             # <<<<<<<<<<<<<<
 *         elevation = i[id_var + mode].mean()
 *         elevation_index = find_elevation_index(self.vcp_mode, elevation)
 */
  __pyx_t_2 = PyNumber_Add(__pyx_v_id_var, __pyx_n_s_HI); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 212, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = (__Pyx_PySequence_ContainsTF(__pyx_t_2, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_3 < 0)) __PYX_ERR(0, 212, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if ((__pyx_t_3 != 0)) {
    __Pyx_INCREF(__pyx_n_s_HI);
    __pyx_t_1 = __pyx_n_s_HI;
  } else {
    __Pyx_INCREF(__pyx_kp_s__13);
    __pyx_t_1 = __pyx_kp_s__13;
  }
  __pyx_v_mode = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":213
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):
 *         mode = "_HI" if id_var + "_HI" in i else ""
 *         elevation = i[id_var + mode].mean()             # <<<<<<<<<<<<<<
 *         elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *         logging.info("%f - %d" % (elevation, elevation_index))
 */
  __pyx_t_2 = PyNumber_Add(__pyx_v_id_var, __pyx_v_mode); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 213, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = PyObject_GetItem(__pyx_v_i, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 213, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_mean); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 213, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_4) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 213, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 213, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_elevation = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":214
 *         mode = "_HI" if id_var + "_HI" in i else ""
 *         elevation = i[id_var + mode].mean()
 *         elevation_index = find_elevation_index(self.vcp_mode, elevation)             # <<<<<<<<<<<<<<
 *         logging.info("%f - %d" % (elevation, elevation_index))
 *         for j, s in zip(var_names, var_suffix):
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_find_elevation_index); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = NULL;
  __pyx_t_6 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_6 = 1;
    }
  }
  __pyx_t_7 = PyTuple_New(2+__pyx_t_6); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  if (__pyx_t_5) {
    __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5); __pyx_t_5 = NULL;
  }
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_7, 0+__pyx_t_6, __pyx_t_4);
  __Pyx_INCREF(__pyx_v_elevation);
  __Pyx_GIVEREF(__pyx_v_elevation);
  PyTuple_SET_ITEM(__pyx_t_7, 1+__pyx_t_6, __pyx_v_elevation);
  __pyx_t_4 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_7, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_elevation_index = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":215
 *         elevation = i[id_var + mode].mean()
 *         elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *         logging.info("%f - %d" % (elevation, elevation_index))             # <<<<<<<<<<<<<<
 *         for j, s in zip(var_names, var_suffix):
 *             logging.debug("Dumping variable: %s - %s" % (j, s))
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_info); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_elevation);
  __Pyx_GIVEREF(__pyx_v_elevation);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_elevation);
  __Pyx_INCREF(__pyx_v_elevation_index);
  __Pyx_GIVEREF(__pyx_v_elevation_index);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_v_elevation_index);
  __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_f_d, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_7))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_7);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_7, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":216
 *         elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *         logging.info("%f - %d" % (elevation, elevation_index))
 *         for j, s in zip(var_names, var_suffix):             # <<<<<<<<<<<<<<
 *             logging.debug("Dumping variable: %s - %s" % (j, s))
 *             fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_var_names);
  __Pyx_GIVEREF(__pyx_v_var_names);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_var_names);
  __Pyx_INCREF(__pyx_v_var_suffix);
  __Pyx_GIVEREF(__pyx_v_var_suffix);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_var_suffix);
  __pyx_t_7 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_1, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (likely(PyList_CheckExact(__pyx_t_7)) || PyTuple_CheckExact(__pyx_t_7)) {
    __pyx_t_1 = __pyx_t_7; __Pyx_INCREF(__pyx_t_1); __pyx_t_6 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_6 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 216, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 216, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_6 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_7 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_6); __Pyx_INCREF(__pyx_t_7); __pyx_t_6++; if (unlikely(0 < 0)) __PYX_ERR(0, 216, __pyx_L1_error)
        #else
        __pyx_t_7 = PySequence_ITEM(__pyx_t_1, __pyx_t_6); __pyx_t_6++; if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 216, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        #endif
      } else {
        if (__pyx_t_6 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_7 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_6); __Pyx_INCREF(__pyx_t_7); __pyx_t_6++; if (unlikely(0 < 0)) __PYX_ERR(0, 216, __pyx_L1_error)
        #else
        __pyx_t_7 = PySequence_ITEM(__pyx_t_1, __pyx_t_6); __pyx_t_6++; if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 216, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        #endif
      }
    } else {
      __pyx_t_7 = __pyx_t_8(__pyx_t_1);
      if (unlikely(!__pyx_t_7)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 216, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_7);
    }
    if ((likely(PyTuple_CheckExact(__pyx_t_7))) || (PyList_CheckExact(__pyx_t_7))) {
      PyObject* sequence = __pyx_t_7;
      #if CYTHON_COMPILING_IN_CPYTHON
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 216, __pyx_L1_error)
      }
      #if CYTHON_COMPILING_IN_CPYTHON
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_4 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_4 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_4);
      #else
      __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_4 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_2 = PyObject_GetIter(__pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __pyx_t_9 = Py_TYPE(__pyx_t_2)->tp_iternext;
      index = 0; __pyx_t_5 = __pyx_t_9(__pyx_t_2); if (unlikely(!__pyx_t_5)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_5);
      index = 1; __pyx_t_4 = __pyx_t_9(__pyx_t_2); if (unlikely(!__pyx_t_4)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_4);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_9(__pyx_t_2), 2) < 0) __PYX_ERR(0, 216, __pyx_L1_error)
      __pyx_t_9 = NULL;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      goto __pyx_L6_unpacking_done;
      __pyx_L5_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_9 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 216, __pyx_L1_error)
      __pyx_L6_unpacking_done:;
    }
    __Pyx_XDECREF_SET(__pyx_v_j, __pyx_t_5);
    __pyx_t_5 = 0;
    __Pyx_XDECREF_SET(__pyx_v_s, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "data_handler_v2.py":217
 *         logging.info("%f - %d" % (elevation, elevation_index))
 *         for j, s in zip(var_names, var_suffix):
 *             logging.debug("Dumping variable: %s - %s" % (j, s))             # <<<<<<<<<<<<<<
 *             fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                self.beams_count, self.gates_count)
 */
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_debug); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_INCREF(__pyx_v_j);
    __Pyx_GIVEREF(__pyx_v_j);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_j);
    __Pyx_INCREF(__pyx_v_s);
    __Pyx_GIVEREF(__pyx_v_s);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_v_s);
    __pyx_t_2 = __Pyx_PyString_Format(__pyx_kp_s_Dumping_variable_s_s, __pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 217, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else {
      __pyx_t_10 = PyTuple_New(1+1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 217, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_10, 0+1, __pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_10, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 217, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    }
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

    /* "data_handler_v2.py":218
 *         for j, s in zip(var_names, var_suffix):
 *             logging.debug("Dumping variable: %s - %s" % (j, s))
 *             fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,             # <<<<<<<<<<<<<<
 *                                self.beams_count, self.gates_count)
 * 
 */
    __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_fill_data_function); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_10 = PyNumber_Add(__pyx_v_j, __pyx_v_mode); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_2 = PyObject_GetItem(__pyx_v_i, __pyx_t_10); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __pyx_t_10 = PyNumber_Add(__pyx_n_s_azimuth, __pyx_v_s); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_4 = PyNumber_Add(__pyx_t_10, __pyx_v_mode); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __pyx_t_10 = PyObject_GetItem(__pyx_v_i, __pyx_t_4); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_11 = PyObject_GetItem(__pyx_t_4, __pyx_v_j); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

    /* "data_handler_v2.py":219
 *             logging.debug("Dumping variable: %s - %s" % (j, s))
 *             fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                self.beams_count, self.gates_count)             # <<<<<<<<<<<<<<
 * 
 *     def fill_data(self, *args, **kwargs):
 */
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_beams_count); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 219, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_gates_count); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 219, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __pyx_t_13 = NULL;
    __pyx_t_14 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_13 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_13)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_13);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
        __pyx_t_14 = 1;
      }
    }
    __pyx_t_15 = PyTuple_New(6+__pyx_t_14); if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_15);
    if (__pyx_t_13) {
      __Pyx_GIVEREF(__pyx_t_13); PyTuple_SET_ITEM(__pyx_t_15, 0, __pyx_t_13); __pyx_t_13 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_15, 0+__pyx_t_14, __pyx_t_2);
    __Pyx_GIVEREF(__pyx_t_10);
    PyTuple_SET_ITEM(__pyx_t_15, 1+__pyx_t_14, __pyx_t_10);
    __Pyx_GIVEREF(__pyx_t_11);
    PyTuple_SET_ITEM(__pyx_t_15, 2+__pyx_t_14, __pyx_t_11);
    __Pyx_INCREF(__pyx_v_elevation_index);
    __Pyx_GIVEREF(__pyx_v_elevation_index);
    PyTuple_SET_ITEM(__pyx_t_15, 3+__pyx_t_14, __pyx_v_elevation_index);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_15, 4+__pyx_t_14, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_12);
    PyTuple_SET_ITEM(__pyx_t_15, 5+__pyx_t_14, __pyx_t_12);
    __pyx_t_2 = 0;
    __pyx_t_10 = 0;
    __pyx_t_11 = 0;
    __pyx_t_4 = 0;
    __pyx_t_12 = 0;
    __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_15, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_15); __pyx_t_15 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

    /* "data_handler_v2.py":216
 *         elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *         logging.info("%f - %d" % (elevation, elevation_index))
 *         for j, s in zip(var_names, var_suffix):             # <<<<<<<<<<<<<<
 *             logging.debug("Dumping variable: %s - %s" % (j, s))
 *             fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":211
 * 
 *     @jit
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):             # <<<<<<<<<<<<<<
 *         mode = "_HI" if id_var + "_HI" in i else ""
 *         elevation = i[id_var + mode].mean()
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_XDECREF(__pyx_t_12);
  __Pyx_XDECREF(__pyx_t_13);
  __Pyx_XDECREF(__pyx_t_15);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.__fill_data_internal", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_mode);
  __Pyx_XDECREF(__pyx_v_elevation);
  __Pyx_XDECREF(__pyx_v_elevation_index);
  __Pyx_XDECREF(__pyx_v_j);
  __Pyx_XDECREF(__pyx_v_s);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":221
 *                                self.beams_count, self.gates_count)
 * 
 *     def fill_data(self, *args, **kwargs):             # <<<<<<<<<<<<<<
 * 
 *         for i in self.time_data_dict.values():
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_15fill_data(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_15fill_data = {"fill_data", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_15fill_data, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_15fill_data(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  CYTHON_UNUSED PyObject *__pyx_v_args = 0;
  CYTHON_UNUSED PyObject *__pyx_v_kwargs = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("fill_data (wrapper)", 0);
  __pyx_v_kwargs = PyDict_New(); if (unlikely(!__pyx_v_kwargs)) return NULL;
  __Pyx_GOTREF(__pyx_v_kwargs);
  if (PyTuple_GET_SIZE(__pyx_args) > 1) {
    __pyx_v_args = PyTuple_GetSlice(__pyx_args, 1, PyTuple_GET_SIZE(__pyx_args));
    if (unlikely(!__pyx_v_args)) {
      __Pyx_DECREF(__pyx_v_kwargs); __pyx_v_kwargs = 0;
      __Pyx_RefNannyFinishContext();
      return NULL;
    }
    __Pyx_GOTREF(__pyx_v_args);
  } else {
    __pyx_v_args = __pyx_empty_tuple; __Pyx_INCREF(__pyx_empty_tuple);
  }
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,0};
    PyObject* values[1] = {0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        default:
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
      }
      if (unlikely(kw_args > 0)) {
        const Py_ssize_t used_pos_args = (pos_args < 1) ? pos_args : 1;
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, __pyx_v_kwargs, values, used_pos_args, "fill_data") < 0)) __PYX_ERR(0, 221, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) < 1) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
    }
    __pyx_v_self = values[0];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("fill_data", 0, 1, 1, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 221, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_DECREF(__pyx_v_args); __pyx_v_args = 0;
  __Pyx_DECREF(__pyx_v_kwargs); __pyx_v_kwargs = 0;
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.fill_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_14fill_data(__pyx_self, __pyx_v_self, __pyx_v_args, __pyx_v_kwargs);

  /* function exit code */
  __Pyx_XDECREF(__pyx_v_args);
  __Pyx_XDECREF(__pyx_v_kwargs);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_14fill_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v_args, CYTHON_UNUSED PyObject *__pyx_v_kwargs) {
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_v_mode = NULL;
  PyObject *__pyx_v_elevation = NULL;
  PyObject *__pyx_v_elevation_index = NULL;
  PyObject *__pyx_v_j = NULL;
  PyObject *__pyx_v_s = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t __pyx_t_4;
  PyObject *(*__pyx_t_5)(PyObject *);
  int __pyx_t_6;
  int __pyx_t_7;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  Py_ssize_t __pyx_t_15;
  PyObject *__pyx_t_16 = NULL;
  PyObject *__pyx_t_17 = NULL;
  PyObject *__pyx_t_18 = NULL;
  PyObject *(*__pyx_t_19)(PyObject *);
  PyObject *(*__pyx_t_20)(PyObject *);
  PyObject *__pyx_t_21 = NULL;
  PyObject *__pyx_t_22 = NULL;
  PyObject *__pyx_t_23 = NULL;
  PyObject *__pyx_t_24 = NULL;
  Py_ssize_t __pyx_t_25;
  PyObject *__pyx_t_26 = NULL;
  __Pyx_RefNannySetupContext("fill_data", 0);

  /* "data_handler_v2.py":223
 *     def fill_data(self, *args, **kwargs):
 * 
 *         for i in self.time_data_dict.values():             # <<<<<<<<<<<<<<
 *             # There are several cases:
 *             # Case 1: CS case, only reflectivity related variable will be here
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_time_data_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 223, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_values); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 223, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 223, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_3 = __pyx_t_1; __Pyx_INCREF(__pyx_t_3); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 223, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_1); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 223, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 223, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_1); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 223, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 223, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_5(__pyx_t_3);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 223, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    __Pyx_XDECREF_SET(__pyx_v_i, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "data_handler_v2.py":226
 *             # There are several cases:
 *             # Case 1: CS case, only reflectivity related variable will be here
 *             if 'elevationV' not in i and 'elevationV_HI' not in i:             # <<<<<<<<<<<<<<
 *                 try:
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 */
    __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV, __pyx_v_i, Py_NE)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 226, __pyx_L1_error)
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (__pyx_t_8) {
    } else {
      __pyx_t_6 = __pyx_t_8;
      goto __pyx_L6_bool_binop_done;
    }
    __pyx_t_8 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV_HI, __pyx_v_i, Py_NE)); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 226, __pyx_L1_error)
    __pyx_t_7 = (__pyx_t_8 != 0);
    __pyx_t_6 = __pyx_t_7;
    __pyx_L6_bool_binop_done:;
    if (__pyx_t_6) {

      /* "data_handler_v2.py":227
 *             # Case 1: CS case, only reflectivity related variable will be here
 *             if 'elevationV' not in i and 'elevationV_HI' not in i:
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 *                 except:
 */
      {
        __Pyx_PyThreadState_declare
        __Pyx_PyThreadState_assign
        __Pyx_ExceptionSave(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
        __Pyx_XGOTREF(__pyx_t_9);
        __Pyx_XGOTREF(__pyx_t_10);
        __Pyx_XGOTREF(__pyx_t_11);
        /*try:*/ {

          /* "data_handler_v2.py":228
 *             if 'elevationV' not in i and 'elevationV_HI' not in i:
 *                 try:
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)             # <<<<<<<<<<<<<<
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CS")
 */
          __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_RadarNetcdf__fill_data_internal); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 228, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_2);
          __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_ref_var_names); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 228, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_12);
          __pyx_t_13 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_ref_var_suffix); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 228, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_13);
          __pyx_t_14 = NULL;
          __pyx_t_15 = 0;
          if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
            __pyx_t_14 = PyMethod_GET_SELF(__pyx_t_2);
            if (likely(__pyx_t_14)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
              __Pyx_INCREF(__pyx_t_14);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_2, function);
              __pyx_t_15 = 1;
            }
          }
          __pyx_t_16 = PyTuple_New(4+__pyx_t_15); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 228, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_16);
          if (__pyx_t_14) {
            __Pyx_GIVEREF(__pyx_t_14); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_14); __pyx_t_14 = NULL;
          }
          __Pyx_INCREF(__pyx_v_i);
          __Pyx_GIVEREF(__pyx_v_i);
          PyTuple_SET_ITEM(__pyx_t_16, 0+__pyx_t_15, __pyx_v_i);
          __Pyx_INCREF(__pyx_n_s_elevationR);
          __Pyx_GIVEREF(__pyx_n_s_elevationR);
          PyTuple_SET_ITEM(__pyx_t_16, 1+__pyx_t_15, __pyx_n_s_elevationR);
          __Pyx_GIVEREF(__pyx_t_12);
          PyTuple_SET_ITEM(__pyx_t_16, 2+__pyx_t_15, __pyx_t_12);
          __Pyx_GIVEREF(__pyx_t_13);
          PyTuple_SET_ITEM(__pyx_t_16, 3+__pyx_t_15, __pyx_t_13);
          __pyx_t_12 = 0;
          __pyx_t_13 = 0;
          __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_16, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 228, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

          /* "data_handler_v2.py":227
 *             # Case 1: CS case, only reflectivity related variable will be here
 *             if 'elevationV' not in i and 'elevationV_HI' not in i:
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 *                 except:
 */
        }
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        goto __pyx_L15_try_end;
        __pyx_L8_error:;
        __Pyx_PyThreadState_assign
        __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
        __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
        __Pyx_XDECREF(__pyx_t_13); __pyx_t_13 = 0;
        __Pyx_XDECREF(__pyx_t_16); __pyx_t_16 = 0;
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;

        /* "data_handler_v2.py":229
 *                 try:
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 *                 except:             # <<<<<<<<<<<<<<
 *                     logging.warning("Failed to run JITed fill_data function: CS")
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 */
        /*except:*/ {
          __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.fill_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
          if (__Pyx_GetException(&__pyx_t_1, &__pyx_t_2, &__pyx_t_16) < 0) __PYX_ERR(0, 229, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_GOTREF(__pyx_t_16);

          /* "data_handler_v2.py":230
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CS")             # <<<<<<<<<<<<<<
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()
 */
          __pyx_t_13 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 230, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_13);
          __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_t_13, __pyx_n_s_warning); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 230, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_12);
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
          __pyx_t_13 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_tuple__20, NULL); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 230, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_13);
          __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;

          /* "data_handler_v2.py":231
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CS")
 *                     mode = "_HI" if 'elevationR_HI' in i else ""             # <<<<<<<<<<<<<<
 *                     elevation = i["elevationR" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 */
          __pyx_t_6 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationR_HI, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 231, __pyx_L10_except_error)
          if ((__pyx_t_6 != 0)) {
            __Pyx_INCREF(__pyx_n_s_HI);
            __pyx_t_13 = __pyx_n_s_HI;
          } else {
            __Pyx_INCREF(__pyx_kp_s__13);
            __pyx_t_13 = __pyx_kp_s__13;
          }
          __Pyx_XDECREF_SET(__pyx_v_mode, __pyx_t_13);
          __pyx_t_13 = 0;

          /* "data_handler_v2.py":232
 *                     logging.warning("Failed to run JITed fill_data function: CS")
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()             # <<<<<<<<<<<<<<
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 */
          __pyx_t_12 = PyNumber_Add(__pyx_n_s_elevationR, __pyx_v_mode); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 232, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_12);
          __pyx_t_14 = PyObject_GetItem(__pyx_v_i, __pyx_t_12); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 232, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_14);
          __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_t_14, __pyx_n_s_mean); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 232, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_12);
          __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
          __pyx_t_14 = NULL;
          if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_12))) {
            __pyx_t_14 = PyMethod_GET_SELF(__pyx_t_12);
            if (likely(__pyx_t_14)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
              __Pyx_INCREF(__pyx_t_14);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_12, function);
            }
          }
          if (__pyx_t_14) {
            __pyx_t_13 = __Pyx_PyObject_CallOneArg(__pyx_t_12, __pyx_t_14); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 232, __pyx_L10_except_error)
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
          } else {
            __pyx_t_13 = __Pyx_PyObject_CallNoArg(__pyx_t_12); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 232, __pyx_L10_except_error)
          }
          __Pyx_GOTREF(__pyx_t_13);
          __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          __Pyx_XDECREF_SET(__pyx_v_elevation, __pyx_t_13);
          __pyx_t_13 = 0;

          /* "data_handler_v2.py":233
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)             # <<<<<<<<<<<<<<
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.ref_var_names, self.ref_var_suffix):
 */
          __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_find_elevation_index); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 233, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_12);
          __pyx_t_14 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 233, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_14);
          __pyx_t_17 = NULL;
          __pyx_t_15 = 0;
          if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_12))) {
            __pyx_t_17 = PyMethod_GET_SELF(__pyx_t_12);
            if (likely(__pyx_t_17)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
              __Pyx_INCREF(__pyx_t_17);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_12, function);
              __pyx_t_15 = 1;
            }
          }
          __pyx_t_18 = PyTuple_New(2+__pyx_t_15); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 233, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          if (__pyx_t_17) {
            __Pyx_GIVEREF(__pyx_t_17); PyTuple_SET_ITEM(__pyx_t_18, 0, __pyx_t_17); __pyx_t_17 = NULL;
          }
          __Pyx_GIVEREF(__pyx_t_14);
          PyTuple_SET_ITEM(__pyx_t_18, 0+__pyx_t_15, __pyx_t_14);
          __Pyx_INCREF(__pyx_v_elevation);
          __Pyx_GIVEREF(__pyx_v_elevation);
          PyTuple_SET_ITEM(__pyx_t_18, 1+__pyx_t_15, __pyx_v_elevation);
          __pyx_t_14 = 0;
          __pyx_t_13 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_18, NULL); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 233, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_13);
          __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
          __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          __Pyx_XDECREF_SET(__pyx_v_elevation_index, __pyx_t_13);
          __pyx_t_13 = 0;

          /* "data_handler_v2.py":234
 *                     elevation = i["elevationR" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))             # <<<<<<<<<<<<<<
 *                     for j, s in zip(self.ref_var_names, self.ref_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 */
          __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 234, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_12);
          __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_t_12, __pyx_n_s_info); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 234, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          __pyx_t_12 = PyTuple_New(2); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 234, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_12);
          __Pyx_INCREF(__pyx_v_elevation);
          __Pyx_GIVEREF(__pyx_v_elevation);
          PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_v_elevation);
          __Pyx_INCREF(__pyx_v_elevation_index);
          __Pyx_GIVEREF(__pyx_v_elevation_index);
          PyTuple_SET_ITEM(__pyx_t_12, 1, __pyx_v_elevation_index);
          __pyx_t_14 = __Pyx_PyString_Format(__pyx_kp_s_f_d, __pyx_t_12); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 234, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_14);
          __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          __pyx_t_12 = NULL;
          if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_18))) {
            __pyx_t_12 = PyMethod_GET_SELF(__pyx_t_18);
            if (likely(__pyx_t_12)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_18);
              __Pyx_INCREF(__pyx_t_12);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_18, function);
            }
          }
          if (!__pyx_t_12) {
            __pyx_t_13 = __Pyx_PyObject_CallOneArg(__pyx_t_18, __pyx_t_14); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 234, __pyx_L10_except_error)
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            __Pyx_GOTREF(__pyx_t_13);
          } else {
            __pyx_t_17 = PyTuple_New(1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 234, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_GIVEREF(__pyx_t_12); PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_12); __pyx_t_12 = NULL;
            __Pyx_GIVEREF(__pyx_t_14);
            PyTuple_SET_ITEM(__pyx_t_17, 0+1, __pyx_t_14);
            __pyx_t_14 = 0;
            __pyx_t_13 = __Pyx_PyObject_Call(__pyx_t_18, __pyx_t_17, NULL); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 234, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_13);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          }
          __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;

          /* "data_handler_v2.py":235
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.ref_var_names, self.ref_var_suffix):             # <<<<<<<<<<<<<<
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
          __pyx_t_13 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_ref_var_names); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 235, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_13);
          __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_ref_var_suffix); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 235, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __pyx_t_17 = PyTuple_New(2); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 235, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_GIVEREF(__pyx_t_13);
          PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_13);
          __Pyx_GIVEREF(__pyx_t_18);
          PyTuple_SET_ITEM(__pyx_t_17, 1, __pyx_t_18);
          __pyx_t_13 = 0;
          __pyx_t_18 = 0;
          __pyx_t_18 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_17, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 235, __pyx_L10_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          if (likely(PyList_CheckExact(__pyx_t_18)) || PyTuple_CheckExact(__pyx_t_18)) {
            __pyx_t_17 = __pyx_t_18; __Pyx_INCREF(__pyx_t_17); __pyx_t_15 = 0;
            __pyx_t_19 = NULL;
          } else {
            __pyx_t_15 = -1; __pyx_t_17 = PyObject_GetIter(__pyx_t_18); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 235, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_17);
            __pyx_t_19 = Py_TYPE(__pyx_t_17)->tp_iternext; if (unlikely(!__pyx_t_19)) __PYX_ERR(0, 235, __pyx_L10_except_error)
          }
          __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
          for (;;) {
            if (likely(!__pyx_t_19)) {
              if (likely(PyList_CheckExact(__pyx_t_17))) {
                if (__pyx_t_15 >= PyList_GET_SIZE(__pyx_t_17)) break;
                #if CYTHON_COMPILING_IN_CPYTHON
                __pyx_t_18 = PyList_GET_ITEM(__pyx_t_17, __pyx_t_15); __Pyx_INCREF(__pyx_t_18); __pyx_t_15++; if (unlikely(0 < 0)) __PYX_ERR(0, 235, __pyx_L10_except_error)
                #else
                __pyx_t_18 = PySequence_ITEM(__pyx_t_17, __pyx_t_15); __pyx_t_15++; if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 235, __pyx_L10_except_error)
                __Pyx_GOTREF(__pyx_t_18);
                #endif
              } else {
                if (__pyx_t_15 >= PyTuple_GET_SIZE(__pyx_t_17)) break;
                #if CYTHON_COMPILING_IN_CPYTHON
                __pyx_t_18 = PyTuple_GET_ITEM(__pyx_t_17, __pyx_t_15); __Pyx_INCREF(__pyx_t_18); __pyx_t_15++; if (unlikely(0 < 0)) __PYX_ERR(0, 235, __pyx_L10_except_error)
                #else
                __pyx_t_18 = PySequence_ITEM(__pyx_t_17, __pyx_t_15); __pyx_t_15++; if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 235, __pyx_L10_except_error)
                __Pyx_GOTREF(__pyx_t_18);
                #endif
              }
            } else {
              __pyx_t_18 = __pyx_t_19(__pyx_t_17);
              if (unlikely(!__pyx_t_18)) {
                PyObject* exc_type = PyErr_Occurred();
                if (exc_type) {
                  if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
                  else __PYX_ERR(0, 235, __pyx_L10_except_error)
                }
                break;
              }
              __Pyx_GOTREF(__pyx_t_18);
            }
            if ((likely(PyTuple_CheckExact(__pyx_t_18))) || (PyList_CheckExact(__pyx_t_18))) {
              PyObject* sequence = __pyx_t_18;
              #if CYTHON_COMPILING_IN_CPYTHON
              Py_ssize_t size = Py_SIZE(sequence);
              #else
              Py_ssize_t size = PySequence_Size(sequence);
              #endif
              if (unlikely(size != 2)) {
                if (size > 2) __Pyx_RaiseTooManyValuesError(2);
                else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
                __PYX_ERR(0, 235, __pyx_L10_except_error)
              }
              #if CYTHON_COMPILING_IN_CPYTHON
              if (likely(PyTuple_CheckExact(sequence))) {
                __pyx_t_13 = PyTuple_GET_ITEM(sequence, 0); 
                __pyx_t_14 = PyTuple_GET_ITEM(sequence, 1); 
              } else {
                __pyx_t_13 = PyList_GET_ITEM(sequence, 0); 
                __pyx_t_14 = PyList_GET_ITEM(sequence, 1); 
              }
              __Pyx_INCREF(__pyx_t_13);
              __Pyx_INCREF(__pyx_t_14);
              #else
              __pyx_t_13 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 235, __pyx_L10_except_error)
              __Pyx_GOTREF(__pyx_t_13);
              __pyx_t_14 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 235, __pyx_L10_except_error)
              __Pyx_GOTREF(__pyx_t_14);
              #endif
              __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            } else {
              Py_ssize_t index = -1;
              __pyx_t_12 = PyObject_GetIter(__pyx_t_18); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 235, __pyx_L10_except_error)
              __Pyx_GOTREF(__pyx_t_12);
              __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
              __pyx_t_20 = Py_TYPE(__pyx_t_12)->tp_iternext;
              index = 0; __pyx_t_13 = __pyx_t_20(__pyx_t_12); if (unlikely(!__pyx_t_13)) goto __pyx_L20_unpacking_failed;
              __Pyx_GOTREF(__pyx_t_13);
              index = 1; __pyx_t_14 = __pyx_t_20(__pyx_t_12); if (unlikely(!__pyx_t_14)) goto __pyx_L20_unpacking_failed;
              __Pyx_GOTREF(__pyx_t_14);
              if (__Pyx_IternextUnpackEndCheck(__pyx_t_20(__pyx_t_12), 2) < 0) __PYX_ERR(0, 235, __pyx_L10_except_error)
              __pyx_t_20 = NULL;
              __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
              goto __pyx_L21_unpacking_done;
              __pyx_L20_unpacking_failed:;
              __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
              __pyx_t_20 = NULL;
              if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
              __PYX_ERR(0, 235, __pyx_L10_except_error)
              __pyx_L21_unpacking_done:;
            }
            __Pyx_XDECREF_SET(__pyx_v_j, __pyx_t_13);
            __pyx_t_13 = 0;
            __Pyx_XDECREF_SET(__pyx_v_s, __pyx_t_14);
            __pyx_t_14 = 0;

            /* "data_handler_v2.py":236
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.ref_var_names, self.ref_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))             # <<<<<<<<<<<<<<
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                         self.beams_count, self.gates_count)
 */
            __pyx_t_14 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 236, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __pyx_t_13 = __Pyx_PyObject_GetAttrStr(__pyx_t_14, __pyx_n_s_debug); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 236, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_13);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            __pyx_t_14 = PyTuple_New(2); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 236, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __Pyx_INCREF(__pyx_v_j);
            __Pyx_GIVEREF(__pyx_v_j);
            PyTuple_SET_ITEM(__pyx_t_14, 0, __pyx_v_j);
            __Pyx_INCREF(__pyx_v_s);
            __Pyx_GIVEREF(__pyx_v_s);
            PyTuple_SET_ITEM(__pyx_t_14, 1, __pyx_v_s);
            __pyx_t_12 = __Pyx_PyString_Format(__pyx_kp_s_Dumping_variable_s_s, __pyx_t_14); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 236, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_12);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            __pyx_t_14 = NULL;
            if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_13))) {
              __pyx_t_14 = PyMethod_GET_SELF(__pyx_t_13);
              if (likely(__pyx_t_14)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_13);
                __Pyx_INCREF(__pyx_t_14);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_13, function);
              }
            }
            if (!__pyx_t_14) {
              __pyx_t_18 = __Pyx_PyObject_CallOneArg(__pyx_t_13, __pyx_t_12); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 236, __pyx_L10_except_error)
              __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
              __Pyx_GOTREF(__pyx_t_18);
            } else {
              __pyx_t_21 = PyTuple_New(1+1); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 236, __pyx_L10_except_error)
              __Pyx_GOTREF(__pyx_t_21);
              __Pyx_GIVEREF(__pyx_t_14); PyTuple_SET_ITEM(__pyx_t_21, 0, __pyx_t_14); __pyx_t_14 = NULL;
              __Pyx_GIVEREF(__pyx_t_12);
              PyTuple_SET_ITEM(__pyx_t_21, 0+1, __pyx_t_12);
              __pyx_t_12 = 0;
              __pyx_t_18 = __Pyx_PyObject_Call(__pyx_t_13, __pyx_t_21, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 236, __pyx_L10_except_error)
              __Pyx_GOTREF(__pyx_t_18);
              __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
            }
            __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

            /* "data_handler_v2.py":237
 *                     for j, s in zip(self.ref_var_names, self.ref_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,             # <<<<<<<<<<<<<<
 *                                         self.beams_count, self.gates_count)
 *                         pass
 */
            __pyx_t_13 = __Pyx_GetModuleGlobalName(__pyx_n_s_fill_data_function); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_13);
            __pyx_t_21 = PyNumber_Add(__pyx_v_j, __pyx_v_mode); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_21);
            __pyx_t_12 = PyObject_GetItem(__pyx_v_i, __pyx_t_21); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_12);
            __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
            __pyx_t_21 = PyNumber_Add(__pyx_n_s_azimuth, __pyx_v_s); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_21);
            __pyx_t_14 = PyNumber_Add(__pyx_t_21, __pyx_v_mode); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
            __pyx_t_21 = PyObject_GetItem(__pyx_v_i, __pyx_t_14); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_21);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            __pyx_t_14 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __pyx_t_22 = PyObject_GetItem(__pyx_t_14, __pyx_v_j); if (unlikely(!__pyx_t_22)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_22);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;

            /* "data_handler_v2.py":238
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                         self.beams_count, self.gates_count)             # <<<<<<<<<<<<<<
 *                         pass
 *             # CD pulses: we only use Doppler Velocity
 */
            __pyx_t_14 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_beams_count); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 238, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __pyx_t_23 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_gates_count); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 238, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __pyx_t_24 = NULL;
            __pyx_t_25 = 0;
            if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_13))) {
              __pyx_t_24 = PyMethod_GET_SELF(__pyx_t_13);
              if (likely(__pyx_t_24)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_13);
                __Pyx_INCREF(__pyx_t_24);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_13, function);
                __pyx_t_25 = 1;
              }
            }
            __pyx_t_26 = PyTuple_New(6+__pyx_t_25); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_26);
            if (__pyx_t_24) {
              __Pyx_GIVEREF(__pyx_t_24); PyTuple_SET_ITEM(__pyx_t_26, 0, __pyx_t_24); __pyx_t_24 = NULL;
            }
            __Pyx_GIVEREF(__pyx_t_12);
            PyTuple_SET_ITEM(__pyx_t_26, 0+__pyx_t_25, __pyx_t_12);
            __Pyx_GIVEREF(__pyx_t_21);
            PyTuple_SET_ITEM(__pyx_t_26, 1+__pyx_t_25, __pyx_t_21);
            __Pyx_GIVEREF(__pyx_t_22);
            PyTuple_SET_ITEM(__pyx_t_26, 2+__pyx_t_25, __pyx_t_22);
            __Pyx_INCREF(__pyx_v_elevation_index);
            __Pyx_GIVEREF(__pyx_v_elevation_index);
            PyTuple_SET_ITEM(__pyx_t_26, 3+__pyx_t_25, __pyx_v_elevation_index);
            __Pyx_GIVEREF(__pyx_t_14);
            PyTuple_SET_ITEM(__pyx_t_26, 4+__pyx_t_25, __pyx_t_14);
            __Pyx_GIVEREF(__pyx_t_23);
            PyTuple_SET_ITEM(__pyx_t_26, 5+__pyx_t_25, __pyx_t_23);
            __pyx_t_12 = 0;
            __pyx_t_21 = 0;
            __pyx_t_22 = 0;
            __pyx_t_14 = 0;
            __pyx_t_23 = 0;
            __pyx_t_18 = __Pyx_PyObject_Call(__pyx_t_13, __pyx_t_26, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 237, __pyx_L10_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
            __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

            /* "data_handler_v2.py":235
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.ref_var_names, self.ref_var_suffix):             # <<<<<<<<<<<<<<
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
          }
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          goto __pyx_L9_exception_handled;
        }
        __pyx_L10_except_error:;

        /* "data_handler_v2.py":227
 *             # Case 1: CS case, only reflectivity related variable will be here
 *             if 'elevationV' not in i and 'elevationV_HI' not in i:
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 *                 except:
 */
        __Pyx_PyThreadState_assign
        __Pyx_XGIVEREF(__pyx_t_9);
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_ExceptionReset(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        goto __pyx_L1_error;
        __pyx_L9_exception_handled:;
        __Pyx_PyThreadState_assign
        __Pyx_XGIVEREF(__pyx_t_9);
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_ExceptionReset(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        __pyx_L15_try_end:;
      }

      /* "data_handler_v2.py":226
 *             # There are several cases:
 *             # Case 1: CS case, only reflectivity related variable will be here
 *             if 'elevationV' not in i and 'elevationV_HI' not in i:             # <<<<<<<<<<<<<<
 *                 try:
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 */
      goto __pyx_L5;
    }

    /* "data_handler_v2.py":241
 *                         pass
 *             # CD pulses: we only use Doppler Velocity
 *             elif (('elevationV' in i or 'elevationV_HI' in i) and ('elevationR' not in i and 'elevationR_HI' not in i)) \             # <<<<<<<<<<<<<<
 *                     or (('elevationV' in i or 'elevationV_HI' in i) and
 *                             ('elevationR' in i or 'elevationR_HI' in i) and
 */
    __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 241, __pyx_L1_error)
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (!__pyx_t_8) {
    } else {
      goto __pyx_L24_next_and;
    }
    __pyx_t_8 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV_HI, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 241, __pyx_L1_error)
    __pyx_t_7 = (__pyx_t_8 != 0);
    if (!__pyx_t_7) {
      goto __pyx_L23_next_or;
    } else {
    }
    __pyx_L24_next_and:;
    __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationR, __pyx_v_i, Py_NE)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 241, __pyx_L1_error)
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (!__pyx_t_8) {
      goto __pyx_L23_next_or;
    } else {
    }
    __pyx_t_8 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationR_HI, __pyx_v_i, Py_NE)); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 241, __pyx_L1_error)
    __pyx_t_7 = (__pyx_t_8 != 0);
    if (!__pyx_t_7) {
    } else {
      __pyx_t_6 = __pyx_t_7;
      goto __pyx_L22_bool_binop_done;
    }
    __pyx_L23_next_or:;

    /* "data_handler_v2.py":242
 *             # CD pulses: we only use Doppler Velocity
 *             elif (('elevationV' in i or 'elevationV_HI' in i) and ('elevationR' not in i and 'elevationR_HI' not in i)) \
 *                     or (('elevationV' in i or 'elevationV_HI' in i) and             # <<<<<<<<<<<<<<
 *                             ('elevationR' in i or 'elevationR_HI' in i) and
 *                             ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)
 */
    __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 242, __pyx_L1_error)
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (!__pyx_t_8) {
    } else {
      goto __pyx_L27_next_and;
    }
    __pyx_t_8 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV_HI, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 242, __pyx_L1_error)
    __pyx_t_7 = (__pyx_t_8 != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_6 = __pyx_t_7;
      goto __pyx_L22_bool_binop_done;
    }
    __pyx_L27_next_and:;

    /* "data_handler_v2.py":243
 *             elif (('elevationV' in i or 'elevationV_HI' in i) and ('elevationR' not in i and 'elevationR_HI' not in i)) \
 *                     or (('elevationV' in i or 'elevationV_HI' in i) and
 *                             ('elevationR' in i or 'elevationR_HI' in i) and             # <<<<<<<<<<<<<<
 *                             ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)
 *                         ):
 */
    __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationR, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 243, __pyx_L1_error)
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (!__pyx_t_8) {
    } else {
      goto __pyx_L29_next_and;
    }
    __pyx_t_8 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationR_HI, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 243, __pyx_L1_error)
    __pyx_t_7 = (__pyx_t_8 != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_6 = __pyx_t_7;
      goto __pyx_L22_bool_binop_done;
    }
    __pyx_L29_next_and:;

    /* "data_handler_v2.py":244
 *                     or (('elevationV' in i or 'elevationV_HI' in i) and
 *                             ('elevationR' in i or 'elevationR_HI' in i) and
 *                             ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)             # <<<<<<<<<<<<<<
 *                         ):
 *                 try:
 */
    __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_DifferentialReflectivity, __pyx_v_i, Py_NE)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 244, __pyx_L1_error)
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (__pyx_t_8) {
    } else {
      __pyx_t_6 = __pyx_t_8;
      goto __pyx_L22_bool_binop_done;
    }
    __pyx_t_8 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_DifferentialReflectivity, __pyx_v_i, Py_NE)); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 244, __pyx_L1_error)
    __pyx_t_7 = (__pyx_t_8 != 0);
    __pyx_t_6 = __pyx_t_7;
    __pyx_L22_bool_binop_done:;

    /* "data_handler_v2.py":241
 *                         pass
 *             # CD pulses: we only use Doppler Velocity
 *             elif (('elevationV' in i or 'elevationV_HI' in i) and ('elevationR' not in i and 'elevationR_HI' not in i)) \             # <<<<<<<<<<<<<<
 *                     or (('elevationV' in i or 'elevationV_HI' in i) and
 *                             ('elevationR' in i or 'elevationR_HI' in i) and
 */
    if (__pyx_t_6) {

      /* "data_handler_v2.py":246
 *                             ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)
 *                         ):
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
 *                 except:
 */
      {
        __Pyx_PyThreadState_declare
        __Pyx_PyThreadState_assign
        __Pyx_ExceptionSave(&__pyx_t_11, &__pyx_t_10, &__pyx_t_9);
        __Pyx_XGOTREF(__pyx_t_11);
        __Pyx_XGOTREF(__pyx_t_10);
        __Pyx_XGOTREF(__pyx_t_9);
        /*try:*/ {

          /* "data_handler_v2.py":247
 *                         ):
 *                 try:
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)             # <<<<<<<<<<<<<<
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CD")
 */
          __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_RadarNetcdf__fill_data_internal); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 247, __pyx_L32_error)
          __Pyx_GOTREF(__pyx_t_2);
          __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vel_var_names); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 247, __pyx_L32_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_17 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vel_var_suffix); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 247, __pyx_L32_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_18 = NULL;
          __pyx_t_15 = 0;
          if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
            __pyx_t_18 = PyMethod_GET_SELF(__pyx_t_2);
            if (likely(__pyx_t_18)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
              __Pyx_INCREF(__pyx_t_18);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_2, function);
              __pyx_t_15 = 1;
            }
          }
          __pyx_t_13 = PyTuple_New(4+__pyx_t_15); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 247, __pyx_L32_error)
          __Pyx_GOTREF(__pyx_t_13);
          if (__pyx_t_18) {
            __Pyx_GIVEREF(__pyx_t_18); PyTuple_SET_ITEM(__pyx_t_13, 0, __pyx_t_18); __pyx_t_18 = NULL;
          }
          __Pyx_INCREF(__pyx_v_i);
          __Pyx_GIVEREF(__pyx_v_i);
          PyTuple_SET_ITEM(__pyx_t_13, 0+__pyx_t_15, __pyx_v_i);
          __Pyx_INCREF(__pyx_n_s_elevationV);
          __Pyx_GIVEREF(__pyx_n_s_elevationV);
          PyTuple_SET_ITEM(__pyx_t_13, 1+__pyx_t_15, __pyx_n_s_elevationV);
          __Pyx_GIVEREF(__pyx_t_1);
          PyTuple_SET_ITEM(__pyx_t_13, 2+__pyx_t_15, __pyx_t_1);
          __Pyx_GIVEREF(__pyx_t_17);
          PyTuple_SET_ITEM(__pyx_t_13, 3+__pyx_t_15, __pyx_t_17);
          __pyx_t_1 = 0;
          __pyx_t_17 = 0;
          __pyx_t_16 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_13, NULL); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 247, __pyx_L32_error)
          __Pyx_GOTREF(__pyx_t_16);
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;

          /* "data_handler_v2.py":246
 *                             ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)
 *                         ):
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
 *                 except:
 */
        }
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        goto __pyx_L39_try_end;
        __pyx_L32_error:;
        __Pyx_PyThreadState_assign
        __Pyx_XDECREF(__pyx_t_24); __pyx_t_24 = 0;
        __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
        __Pyx_XDECREF(__pyx_t_21); __pyx_t_21 = 0;
        __Pyx_XDECREF(__pyx_t_22); __pyx_t_22 = 0;
        __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
        __Pyx_XDECREF(__pyx_t_23); __pyx_t_23 = 0;
        __Pyx_XDECREF(__pyx_t_26); __pyx_t_26 = 0;
        __Pyx_XDECREF(__pyx_t_18); __pyx_t_18 = 0;
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
        __Pyx_XDECREF(__pyx_t_13); __pyx_t_13 = 0;
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_XDECREF(__pyx_t_16); __pyx_t_16 = 0;

        /* "data_handler_v2.py":248
 *                 try:
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
 *                 except:             # <<<<<<<<<<<<<<
 *                     logging.warning("Failed to run JITed fill_data function: CD")
 *                     mode = "_HI" if 'elevationV_HI' in i else ""
 */
        /*except:*/ {
          __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.fill_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
          if (__Pyx_GetException(&__pyx_t_16, &__pyx_t_2, &__pyx_t_13) < 0) __PYX_ERR(0, 248, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_GOTREF(__pyx_t_13);

          /* "data_handler_v2.py":249
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CD")             # <<<<<<<<<<<<<<
 *                     mode = "_HI" if 'elevationV_HI' in i else ""
 *                     elevation = i["elevationV" + mode].mean()
 */
          __pyx_t_17 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 249, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_17, __pyx_n_s_warning); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 249, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __pyx_t_17 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__21, NULL); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 249, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

          /* "data_handler_v2.py":250
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CD")
 *                     mode = "_HI" if 'elevationV_HI' in i else ""             # <<<<<<<<<<<<<<
 *                     elevation = i["elevationV" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 */
          __pyx_t_6 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationV_HI, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 250, __pyx_L34_except_error)
          if ((__pyx_t_6 != 0)) {
            __Pyx_INCREF(__pyx_n_s_HI);
            __pyx_t_17 = __pyx_n_s_HI;
          } else {
            __Pyx_INCREF(__pyx_kp_s__13);
            __pyx_t_17 = __pyx_kp_s__13;
          }
          __Pyx_XDECREF_SET(__pyx_v_mode, __pyx_t_17);
          __pyx_t_17 = 0;

          /* "data_handler_v2.py":251
 *                     logging.warning("Failed to run JITed fill_data function: CD")
 *                     mode = "_HI" if 'elevationV_HI' in i else ""
 *                     elevation = i["elevationV" + mode].mean()             # <<<<<<<<<<<<<<
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 */
          __pyx_t_1 = PyNumber_Add(__pyx_n_s_elevationV, __pyx_v_mode); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 251, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_18 = PyObject_GetItem(__pyx_v_i, __pyx_t_1); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 251, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_18, __pyx_n_s_mean); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 251, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
          __pyx_t_18 = NULL;
          if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_1))) {
            __pyx_t_18 = PyMethod_GET_SELF(__pyx_t_1);
            if (likely(__pyx_t_18)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
              __Pyx_INCREF(__pyx_t_18);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_1, function);
            }
          }
          if (__pyx_t_18) {
            __pyx_t_17 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_18); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 251, __pyx_L34_except_error)
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
          } else {
            __pyx_t_17 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 251, __pyx_L34_except_error)
          }
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_XDECREF_SET(__pyx_v_elevation, __pyx_t_17);
          __pyx_t_17 = 0;

          /* "data_handler_v2.py":252
 *                     mode = "_HI" if 'elevationV_HI' in i else ""
 *                     elevation = i["elevationV" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)             # <<<<<<<<<<<<<<
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.vel_var_names, self.vel_var_suffix):
 */
          __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_find_elevation_index); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 252, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 252, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __pyx_t_26 = NULL;
          __pyx_t_15 = 0;
          if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_1))) {
            __pyx_t_26 = PyMethod_GET_SELF(__pyx_t_1);
            if (likely(__pyx_t_26)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
              __Pyx_INCREF(__pyx_t_26);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_1, function);
              __pyx_t_15 = 1;
            }
          }
          __pyx_t_23 = PyTuple_New(2+__pyx_t_15); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 252, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          if (__pyx_t_26) {
            __Pyx_GIVEREF(__pyx_t_26); PyTuple_SET_ITEM(__pyx_t_23, 0, __pyx_t_26); __pyx_t_26 = NULL;
          }
          __Pyx_GIVEREF(__pyx_t_18);
          PyTuple_SET_ITEM(__pyx_t_23, 0+__pyx_t_15, __pyx_t_18);
          __Pyx_INCREF(__pyx_v_elevation);
          __Pyx_GIVEREF(__pyx_v_elevation);
          PyTuple_SET_ITEM(__pyx_t_23, 1+__pyx_t_15, __pyx_v_elevation);
          __pyx_t_18 = 0;
          __pyx_t_17 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_23, NULL); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 252, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_XDECREF_SET(__pyx_v_elevation_index, __pyx_t_17);
          __pyx_t_17 = 0;

          /* "data_handler_v2.py":253
 *                     elevation = i["elevationV" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))             # <<<<<<<<<<<<<<
 *                     for j, s in zip(self.vel_var_names, self.vel_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 */
          __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 253, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_23 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_info); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 253, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 253, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_INCREF(__pyx_v_elevation);
          __Pyx_GIVEREF(__pyx_v_elevation);
          PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_elevation);
          __Pyx_INCREF(__pyx_v_elevation_index);
          __Pyx_GIVEREF(__pyx_v_elevation_index);
          PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_elevation_index);
          __pyx_t_18 = __Pyx_PyString_Format(__pyx_kp_s_f_d, __pyx_t_1); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 253, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_18);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = NULL;
          if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_23))) {
            __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_23);
            if (likely(__pyx_t_1)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_23);
              __Pyx_INCREF(__pyx_t_1);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_23, function);
            }
          }
          if (!__pyx_t_1) {
            __pyx_t_17 = __Pyx_PyObject_CallOneArg(__pyx_t_23, __pyx_t_18); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 253, __pyx_L34_except_error)
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            __Pyx_GOTREF(__pyx_t_17);
          } else {
            __pyx_t_26 = PyTuple_New(1+1); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 253, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_26);
            __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_26, 0, __pyx_t_1); __pyx_t_1 = NULL;
            __Pyx_GIVEREF(__pyx_t_18);
            PyTuple_SET_ITEM(__pyx_t_26, 0+1, __pyx_t_18);
            __pyx_t_18 = 0;
            __pyx_t_17 = __Pyx_PyObject_Call(__pyx_t_23, __pyx_t_26, NULL); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 253, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
          }
          __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

          /* "data_handler_v2.py":254
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.vel_var_names, self.vel_var_suffix):             # <<<<<<<<<<<<<<
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
          __pyx_t_17 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vel_var_names); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 254, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_23 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vel_var_suffix); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 254, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          __pyx_t_26 = PyTuple_New(2); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 254, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_26);
          __Pyx_GIVEREF(__pyx_t_17);
          PyTuple_SET_ITEM(__pyx_t_26, 0, __pyx_t_17);
          __Pyx_GIVEREF(__pyx_t_23);
          PyTuple_SET_ITEM(__pyx_t_26, 1, __pyx_t_23);
          __pyx_t_17 = 0;
          __pyx_t_23 = 0;
          __pyx_t_23 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_26, NULL); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 254, __pyx_L34_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
          if (likely(PyList_CheckExact(__pyx_t_23)) || PyTuple_CheckExact(__pyx_t_23)) {
            __pyx_t_26 = __pyx_t_23; __Pyx_INCREF(__pyx_t_26); __pyx_t_15 = 0;
            __pyx_t_19 = NULL;
          } else {
            __pyx_t_15 = -1; __pyx_t_26 = PyObject_GetIter(__pyx_t_23); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 254, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_26);
            __pyx_t_19 = Py_TYPE(__pyx_t_26)->tp_iternext; if (unlikely(!__pyx_t_19)) __PYX_ERR(0, 254, __pyx_L34_except_error)
          }
          __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
          for (;;) {
            if (likely(!__pyx_t_19)) {
              if (likely(PyList_CheckExact(__pyx_t_26))) {
                if (__pyx_t_15 >= PyList_GET_SIZE(__pyx_t_26)) break;
                #if CYTHON_COMPILING_IN_CPYTHON
                __pyx_t_23 = PyList_GET_ITEM(__pyx_t_26, __pyx_t_15); __Pyx_INCREF(__pyx_t_23); __pyx_t_15++; if (unlikely(0 < 0)) __PYX_ERR(0, 254, __pyx_L34_except_error)
                #else
                __pyx_t_23 = PySequence_ITEM(__pyx_t_26, __pyx_t_15); __pyx_t_15++; if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 254, __pyx_L34_except_error)
                __Pyx_GOTREF(__pyx_t_23);
                #endif
              } else {
                if (__pyx_t_15 >= PyTuple_GET_SIZE(__pyx_t_26)) break;
                #if CYTHON_COMPILING_IN_CPYTHON
                __pyx_t_23 = PyTuple_GET_ITEM(__pyx_t_26, __pyx_t_15); __Pyx_INCREF(__pyx_t_23); __pyx_t_15++; if (unlikely(0 < 0)) __PYX_ERR(0, 254, __pyx_L34_except_error)
                #else
                __pyx_t_23 = PySequence_ITEM(__pyx_t_26, __pyx_t_15); __pyx_t_15++; if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 254, __pyx_L34_except_error)
                __Pyx_GOTREF(__pyx_t_23);
                #endif
              }
            } else {
              __pyx_t_23 = __pyx_t_19(__pyx_t_26);
              if (unlikely(!__pyx_t_23)) {
                PyObject* exc_type = PyErr_Occurred();
                if (exc_type) {
                  if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
                  else __PYX_ERR(0, 254, __pyx_L34_except_error)
                }
                break;
              }
              __Pyx_GOTREF(__pyx_t_23);
            }
            if ((likely(PyTuple_CheckExact(__pyx_t_23))) || (PyList_CheckExact(__pyx_t_23))) {
              PyObject* sequence = __pyx_t_23;
              #if CYTHON_COMPILING_IN_CPYTHON
              Py_ssize_t size = Py_SIZE(sequence);
              #else
              Py_ssize_t size = PySequence_Size(sequence);
              #endif
              if (unlikely(size != 2)) {
                if (size > 2) __Pyx_RaiseTooManyValuesError(2);
                else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
                __PYX_ERR(0, 254, __pyx_L34_except_error)
              }
              #if CYTHON_COMPILING_IN_CPYTHON
              if (likely(PyTuple_CheckExact(sequence))) {
                __pyx_t_17 = PyTuple_GET_ITEM(sequence, 0); 
                __pyx_t_18 = PyTuple_GET_ITEM(sequence, 1); 
              } else {
                __pyx_t_17 = PyList_GET_ITEM(sequence, 0); 
                __pyx_t_18 = PyList_GET_ITEM(sequence, 1); 
              }
              __Pyx_INCREF(__pyx_t_17);
              __Pyx_INCREF(__pyx_t_18);
              #else
              __pyx_t_17 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 254, __pyx_L34_except_error)
              __Pyx_GOTREF(__pyx_t_17);
              __pyx_t_18 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 254, __pyx_L34_except_error)
              __Pyx_GOTREF(__pyx_t_18);
              #endif
              __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
            } else {
              Py_ssize_t index = -1;
              __pyx_t_1 = PyObject_GetIter(__pyx_t_23); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 254, __pyx_L34_except_error)
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
              __pyx_t_20 = Py_TYPE(__pyx_t_1)->tp_iternext;
              index = 0; __pyx_t_17 = __pyx_t_20(__pyx_t_1); if (unlikely(!__pyx_t_17)) goto __pyx_L44_unpacking_failed;
              __Pyx_GOTREF(__pyx_t_17);
              index = 1; __pyx_t_18 = __pyx_t_20(__pyx_t_1); if (unlikely(!__pyx_t_18)) goto __pyx_L44_unpacking_failed;
              __Pyx_GOTREF(__pyx_t_18);
              if (__Pyx_IternextUnpackEndCheck(__pyx_t_20(__pyx_t_1), 2) < 0) __PYX_ERR(0, 254, __pyx_L34_except_error)
              __pyx_t_20 = NULL;
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L45_unpacking_done;
              __pyx_L44_unpacking_failed:;
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_20 = NULL;
              if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
              __PYX_ERR(0, 254, __pyx_L34_except_error)
              __pyx_L45_unpacking_done:;
            }
            __Pyx_XDECREF_SET(__pyx_v_j, __pyx_t_17);
            __pyx_t_17 = 0;
            __Pyx_XDECREF_SET(__pyx_v_s, __pyx_t_18);
            __pyx_t_18 = 0;

            /* "data_handler_v2.py":255
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.vel_var_names, self.vel_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))             # <<<<<<<<<<<<<<
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                         self.beams_count, self.gates_count)
 */
            __pyx_t_18 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 255, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __pyx_t_17 = __Pyx_PyObject_GetAttrStr(__pyx_t_18, __pyx_n_s_debug); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 255, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            __pyx_t_18 = PyTuple_New(2); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 255, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __Pyx_INCREF(__pyx_v_j);
            __Pyx_GIVEREF(__pyx_v_j);
            PyTuple_SET_ITEM(__pyx_t_18, 0, __pyx_v_j);
            __Pyx_INCREF(__pyx_v_s);
            __Pyx_GIVEREF(__pyx_v_s);
            PyTuple_SET_ITEM(__pyx_t_18, 1, __pyx_v_s);
            __pyx_t_1 = __Pyx_PyString_Format(__pyx_kp_s_Dumping_variable_s_s, __pyx_t_18); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 255, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            __pyx_t_18 = NULL;
            if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_17))) {
              __pyx_t_18 = PyMethod_GET_SELF(__pyx_t_17);
              if (likely(__pyx_t_18)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_17);
                __Pyx_INCREF(__pyx_t_18);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_17, function);
              }
            }
            if (!__pyx_t_18) {
              __pyx_t_23 = __Pyx_PyObject_CallOneArg(__pyx_t_17, __pyx_t_1); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 255, __pyx_L34_except_error)
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __Pyx_GOTREF(__pyx_t_23);
            } else {
              __pyx_t_14 = PyTuple_New(1+1); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 255, __pyx_L34_except_error)
              __Pyx_GOTREF(__pyx_t_14);
              __Pyx_GIVEREF(__pyx_t_18); PyTuple_SET_ITEM(__pyx_t_14, 0, __pyx_t_18); __pyx_t_18 = NULL;
              __Pyx_GIVEREF(__pyx_t_1);
              PyTuple_SET_ITEM(__pyx_t_14, 0+1, __pyx_t_1);
              __pyx_t_1 = 0;
              __pyx_t_23 = __Pyx_PyObject_Call(__pyx_t_17, __pyx_t_14, NULL); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 255, __pyx_L34_except_error)
              __Pyx_GOTREF(__pyx_t_23);
              __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            }
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;

            /* "data_handler_v2.py":256
 *                     for j, s in zip(self.vel_var_names, self.vel_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,             # <<<<<<<<<<<<<<
 *                                         self.beams_count, self.gates_count)
 *                         pass
 */
            __pyx_t_17 = __Pyx_GetModuleGlobalName(__pyx_n_s_fill_data_function); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_17);
            __pyx_t_14 = PyNumber_Add(__pyx_v_j, __pyx_v_mode); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __pyx_t_1 = PyObject_GetItem(__pyx_v_i, __pyx_t_14); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            __pyx_t_14 = PyNumber_Add(__pyx_n_s_azimuth, __pyx_v_s); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __pyx_t_18 = PyNumber_Add(__pyx_t_14, __pyx_v_mode); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
            __pyx_t_14 = PyObject_GetItem(__pyx_v_i, __pyx_t_18); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __pyx_t_22 = PyObject_GetItem(__pyx_t_18, __pyx_v_j); if (unlikely(!__pyx_t_22)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_22);
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

            /* "data_handler_v2.py":257
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                         self.beams_count, self.gates_count)             # <<<<<<<<<<<<<<
 *                         pass
 *             # Normal case, all variables will be gathered in one scan
 */
            __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_beams_count); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 257, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __pyx_t_21 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_gates_count); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 257, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_21);
            __pyx_t_12 = NULL;
            __pyx_t_25 = 0;
            if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_17))) {
              __pyx_t_12 = PyMethod_GET_SELF(__pyx_t_17);
              if (likely(__pyx_t_12)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_17);
                __Pyx_INCREF(__pyx_t_12);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_17, function);
                __pyx_t_25 = 1;
              }
            }
            __pyx_t_24 = PyTuple_New(6+__pyx_t_25); if (unlikely(!__pyx_t_24)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_24);
            if (__pyx_t_12) {
              __Pyx_GIVEREF(__pyx_t_12); PyTuple_SET_ITEM(__pyx_t_24, 0, __pyx_t_12); __pyx_t_12 = NULL;
            }
            __Pyx_GIVEREF(__pyx_t_1);
            PyTuple_SET_ITEM(__pyx_t_24, 0+__pyx_t_25, __pyx_t_1);
            __Pyx_GIVEREF(__pyx_t_14);
            PyTuple_SET_ITEM(__pyx_t_24, 1+__pyx_t_25, __pyx_t_14);
            __Pyx_GIVEREF(__pyx_t_22);
            PyTuple_SET_ITEM(__pyx_t_24, 2+__pyx_t_25, __pyx_t_22);
            __Pyx_INCREF(__pyx_v_elevation_index);
            __Pyx_GIVEREF(__pyx_v_elevation_index);
            PyTuple_SET_ITEM(__pyx_t_24, 3+__pyx_t_25, __pyx_v_elevation_index);
            __Pyx_GIVEREF(__pyx_t_18);
            PyTuple_SET_ITEM(__pyx_t_24, 4+__pyx_t_25, __pyx_t_18);
            __Pyx_GIVEREF(__pyx_t_21);
            PyTuple_SET_ITEM(__pyx_t_24, 5+__pyx_t_25, __pyx_t_21);
            __pyx_t_1 = 0;
            __pyx_t_14 = 0;
            __pyx_t_22 = 0;
            __pyx_t_18 = 0;
            __pyx_t_21 = 0;
            __pyx_t_23 = __Pyx_PyObject_Call(__pyx_t_17, __pyx_t_24, NULL); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 256, __pyx_L34_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __Pyx_DECREF(__pyx_t_24); __pyx_t_24 = 0;
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;

            /* "data_handler_v2.py":254
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.vel_var_names, self.vel_var_suffix):             # <<<<<<<<<<<<<<
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
          }
          __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
          goto __pyx_L33_exception_handled;
        }
        __pyx_L34_except_error:;

        /* "data_handler_v2.py":246
 *                             ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)
 *                         ):
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
 *                 except:
 */
        __Pyx_PyThreadState_assign
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_9);
        __Pyx_ExceptionReset(__pyx_t_11, __pyx_t_10, __pyx_t_9);
        goto __pyx_L1_error;
        __pyx_L33_exception_handled:;
        __Pyx_PyThreadState_assign
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_9);
        __Pyx_ExceptionReset(__pyx_t_11, __pyx_t_10, __pyx_t_9);
        __pyx_L39_try_end:;
      }

      /* "data_handler_v2.py":241
 *                         pass
 *             # CD pulses: we only use Doppler Velocity
 *             elif (('elevationV' in i or 'elevationV_HI' in i) and ('elevationR' not in i and 'elevationR_HI' not in i)) \             # <<<<<<<<<<<<<<
 *                     or (('elevationV' in i or 'elevationV_HI' in i) and
 *                             ('elevationR' in i or 'elevationR_HI' in i) and
 */
      goto __pyx_L5;
    }

    /* "data_handler_v2.py":261
 *             # Normal case, all variables will be gathered in one scan
 *             else:
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
 *                 except:
 */
    /*else*/ {
      {
        __Pyx_PyThreadState_declare
        __Pyx_PyThreadState_assign
        __Pyx_ExceptionSave(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
        __Pyx_XGOTREF(__pyx_t_9);
        __Pyx_XGOTREF(__pyx_t_10);
        __Pyx_XGOTREF(__pyx_t_11);
        /*try:*/ {

          /* "data_handler_v2.py":262
 *             else:
 *                 try:
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)             # <<<<<<<<<<<<<<
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: Mixed")
 */
          __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_RadarNetcdf__fill_data_internal); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 262, __pyx_L46_error)
          __Pyx_GOTREF(__pyx_t_2);
          __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_names); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 262, __pyx_L46_error)
          __Pyx_GOTREF(__pyx_t_16);
          __pyx_t_26 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_suffix); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 262, __pyx_L46_error)
          __Pyx_GOTREF(__pyx_t_26);
          __pyx_t_23 = NULL;
          __pyx_t_15 = 0;
          if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
            __pyx_t_23 = PyMethod_GET_SELF(__pyx_t_2);
            if (likely(__pyx_t_23)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
              __Pyx_INCREF(__pyx_t_23);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_2, function);
              __pyx_t_15 = 1;
            }
          }
          __pyx_t_17 = PyTuple_New(4+__pyx_t_15); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 262, __pyx_L46_error)
          __Pyx_GOTREF(__pyx_t_17);
          if (__pyx_t_23) {
            __Pyx_GIVEREF(__pyx_t_23); PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_23); __pyx_t_23 = NULL;
          }
          __Pyx_INCREF(__pyx_v_i);
          __Pyx_GIVEREF(__pyx_v_i);
          PyTuple_SET_ITEM(__pyx_t_17, 0+__pyx_t_15, __pyx_v_i);
          __Pyx_INCREF(__pyx_n_s_elevationR);
          __Pyx_GIVEREF(__pyx_n_s_elevationR);
          PyTuple_SET_ITEM(__pyx_t_17, 1+__pyx_t_15, __pyx_n_s_elevationR);
          __Pyx_GIVEREF(__pyx_t_16);
          PyTuple_SET_ITEM(__pyx_t_17, 2+__pyx_t_15, __pyx_t_16);
          __Pyx_GIVEREF(__pyx_t_26);
          PyTuple_SET_ITEM(__pyx_t_17, 3+__pyx_t_15, __pyx_t_26);
          __pyx_t_16 = 0;
          __pyx_t_26 = 0;
          __pyx_t_13 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_17, NULL); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 262, __pyx_L46_error)
          __Pyx_GOTREF(__pyx_t_13);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;

          /* "data_handler_v2.py":261
 *             # Normal case, all variables will be gathered in one scan
 *             else:
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
 *                 except:
 */
        }
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        goto __pyx_L53_try_end;
        __pyx_L46_error:;
        __Pyx_PyThreadState_assign
        __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
        __Pyx_XDECREF(__pyx_t_22); __pyx_t_22 = 0;
        __Pyx_XDECREF(__pyx_t_18); __pyx_t_18 = 0;
        __Pyx_XDECREF(__pyx_t_21); __pyx_t_21 = 0;
        __Pyx_XDECREF(__pyx_t_24); __pyx_t_24 = 0;
        __Pyx_XDECREF(__pyx_t_23); __pyx_t_23 = 0;
        __Pyx_XDECREF(__pyx_t_16); __pyx_t_16 = 0;
        __Pyx_XDECREF(__pyx_t_26); __pyx_t_26 = 0;
        __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_XDECREF(__pyx_t_13); __pyx_t_13 = 0;

        /* "data_handler_v2.py":263
 *                 try:
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
 *                 except:             # <<<<<<<<<<<<<<
 *                     logging.warning("Failed to run JITed fill_data function: Mixed")
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 */
        /*except:*/ {
          __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.fill_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
          if (__Pyx_GetException(&__pyx_t_13, &__pyx_t_2, &__pyx_t_17) < 0) __PYX_ERR(0, 263, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_13);
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_GOTREF(__pyx_t_17);

          /* "data_handler_v2.py":264
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: Mixed")             # <<<<<<<<<<<<<<
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()
 */
          __pyx_t_26 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 264, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_26);
          __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_t_26, __pyx_n_s_warning); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 264, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
          __pyx_t_26 = __Pyx_PyObject_Call(__pyx_t_16, __pyx_tuple__22, NULL); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 264, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_26);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;

          /* "data_handler_v2.py":265
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: Mixed")
 *                     mode = "_HI" if 'elevationR_HI' in i else ""             # <<<<<<<<<<<<<<
 *                     elevation = i["elevationR" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 */
          __pyx_t_6 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_elevationR_HI, __pyx_v_i, Py_EQ)); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 265, __pyx_L48_except_error)
          if ((__pyx_t_6 != 0)) {
            __Pyx_INCREF(__pyx_n_s_HI);
            __pyx_t_26 = __pyx_n_s_HI;
          } else {
            __Pyx_INCREF(__pyx_kp_s__13);
            __pyx_t_26 = __pyx_kp_s__13;
          }
          __Pyx_XDECREF_SET(__pyx_v_mode, __pyx_t_26);
          __pyx_t_26 = 0;

          /* "data_handler_v2.py":266
 *                     logging.warning("Failed to run JITed fill_data function: Mixed")
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()             # <<<<<<<<<<<<<<
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 */
          __pyx_t_16 = PyNumber_Add(__pyx_n_s_elevationR, __pyx_v_mode); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 266, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __pyx_t_23 = PyObject_GetItem(__pyx_v_i, __pyx_t_16); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 266, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_t_23, __pyx_n_s_mean); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 266, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
          __pyx_t_23 = NULL;
          if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_16))) {
            __pyx_t_23 = PyMethod_GET_SELF(__pyx_t_16);
            if (likely(__pyx_t_23)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_16);
              __Pyx_INCREF(__pyx_t_23);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_16, function);
            }
          }
          if (__pyx_t_23) {
            __pyx_t_26 = __Pyx_PyObject_CallOneArg(__pyx_t_16, __pyx_t_23); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 266, __pyx_L48_except_error)
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
          } else {
            __pyx_t_26 = __Pyx_PyObject_CallNoArg(__pyx_t_16); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 266, __pyx_L48_except_error)
          }
          __Pyx_GOTREF(__pyx_t_26);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __Pyx_XDECREF_SET(__pyx_v_elevation, __pyx_t_26);
          __pyx_t_26 = 0;

          /* "data_handler_v2.py":267
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)             # <<<<<<<<<<<<<<
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.all_var_names, self.all_var_suffix):
 */
          __pyx_t_16 = __Pyx_GetModuleGlobalName(__pyx_n_s_find_elevation_index); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 267, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __pyx_t_23 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_vcp_mode); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 267, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          __pyx_t_24 = NULL;
          __pyx_t_15 = 0;
          if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_16))) {
            __pyx_t_24 = PyMethod_GET_SELF(__pyx_t_16);
            if (likely(__pyx_t_24)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_16);
              __Pyx_INCREF(__pyx_t_24);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_16, function);
              __pyx_t_15 = 1;
            }
          }
          __pyx_t_21 = PyTuple_New(2+__pyx_t_15); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 267, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_21);
          if (__pyx_t_24) {
            __Pyx_GIVEREF(__pyx_t_24); PyTuple_SET_ITEM(__pyx_t_21, 0, __pyx_t_24); __pyx_t_24 = NULL;
          }
          __Pyx_GIVEREF(__pyx_t_23);
          PyTuple_SET_ITEM(__pyx_t_21, 0+__pyx_t_15, __pyx_t_23);
          __Pyx_INCREF(__pyx_v_elevation);
          __Pyx_GIVEREF(__pyx_v_elevation);
          PyTuple_SET_ITEM(__pyx_t_21, 1+__pyx_t_15, __pyx_v_elevation);
          __pyx_t_23 = 0;
          __pyx_t_26 = __Pyx_PyObject_Call(__pyx_t_16, __pyx_t_21, NULL); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 267, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_26);
          __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __Pyx_XDECREF_SET(__pyx_v_elevation_index, __pyx_t_26);
          __pyx_t_26 = 0;

          /* "data_handler_v2.py":268
 *                     elevation = i["elevationR" + mode].mean()
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))             # <<<<<<<<<<<<<<
 *                     for j, s in zip(self.all_var_names, self.all_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 */
          __pyx_t_16 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 268, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __pyx_t_21 = __Pyx_PyObject_GetAttrStr(__pyx_t_16, __pyx_n_s_info); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 268, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_21);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __pyx_t_16 = PyTuple_New(2); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 268, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __Pyx_INCREF(__pyx_v_elevation);
          __Pyx_GIVEREF(__pyx_v_elevation);
          PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_v_elevation);
          __Pyx_INCREF(__pyx_v_elevation_index);
          __Pyx_GIVEREF(__pyx_v_elevation_index);
          PyTuple_SET_ITEM(__pyx_t_16, 1, __pyx_v_elevation_index);
          __pyx_t_23 = __Pyx_PyString_Format(__pyx_kp_s_f_d, __pyx_t_16); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 268, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_23);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          __pyx_t_16 = NULL;
          if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_21))) {
            __pyx_t_16 = PyMethod_GET_SELF(__pyx_t_21);
            if (likely(__pyx_t_16)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_21);
              __Pyx_INCREF(__pyx_t_16);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_21, function);
            }
          }
          if (!__pyx_t_16) {
            __pyx_t_26 = __Pyx_PyObject_CallOneArg(__pyx_t_21, __pyx_t_23); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 268, __pyx_L48_except_error)
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
            __Pyx_GOTREF(__pyx_t_26);
          } else {
            __pyx_t_24 = PyTuple_New(1+1); if (unlikely(!__pyx_t_24)) __PYX_ERR(0, 268, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_24);
            __Pyx_GIVEREF(__pyx_t_16); PyTuple_SET_ITEM(__pyx_t_24, 0, __pyx_t_16); __pyx_t_16 = NULL;
            __Pyx_GIVEREF(__pyx_t_23);
            PyTuple_SET_ITEM(__pyx_t_24, 0+1, __pyx_t_23);
            __pyx_t_23 = 0;
            __pyx_t_26 = __Pyx_PyObject_Call(__pyx_t_21, __pyx_t_24, NULL); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 268, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_26);
            __Pyx_DECREF(__pyx_t_24); __pyx_t_24 = 0;
          }
          __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
          __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;

          /* "data_handler_v2.py":269
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.all_var_names, self.all_var_suffix):             # <<<<<<<<<<<<<<
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
          __pyx_t_26 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_names); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 269, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_26);
          __pyx_t_21 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_all_var_suffix); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 269, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_21);
          __pyx_t_24 = PyTuple_New(2); if (unlikely(!__pyx_t_24)) __PYX_ERR(0, 269, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_24);
          __Pyx_GIVEREF(__pyx_t_26);
          PyTuple_SET_ITEM(__pyx_t_24, 0, __pyx_t_26);
          __Pyx_GIVEREF(__pyx_t_21);
          PyTuple_SET_ITEM(__pyx_t_24, 1, __pyx_t_21);
          __pyx_t_26 = 0;
          __pyx_t_21 = 0;
          __pyx_t_21 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_24, NULL); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 269, __pyx_L48_except_error)
          __Pyx_GOTREF(__pyx_t_21);
          __Pyx_DECREF(__pyx_t_24); __pyx_t_24 = 0;
          if (likely(PyList_CheckExact(__pyx_t_21)) || PyTuple_CheckExact(__pyx_t_21)) {
            __pyx_t_24 = __pyx_t_21; __Pyx_INCREF(__pyx_t_24); __pyx_t_15 = 0;
            __pyx_t_19 = NULL;
          } else {
            __pyx_t_15 = -1; __pyx_t_24 = PyObject_GetIter(__pyx_t_21); if (unlikely(!__pyx_t_24)) __PYX_ERR(0, 269, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_24);
            __pyx_t_19 = Py_TYPE(__pyx_t_24)->tp_iternext; if (unlikely(!__pyx_t_19)) __PYX_ERR(0, 269, __pyx_L48_except_error)
          }
          __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
          for (;;) {
            if (likely(!__pyx_t_19)) {
              if (likely(PyList_CheckExact(__pyx_t_24))) {
                if (__pyx_t_15 >= PyList_GET_SIZE(__pyx_t_24)) break;
                #if CYTHON_COMPILING_IN_CPYTHON
                __pyx_t_21 = PyList_GET_ITEM(__pyx_t_24, __pyx_t_15); __Pyx_INCREF(__pyx_t_21); __pyx_t_15++; if (unlikely(0 < 0)) __PYX_ERR(0, 269, __pyx_L48_except_error)
                #else
                __pyx_t_21 = PySequence_ITEM(__pyx_t_24, __pyx_t_15); __pyx_t_15++; if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 269, __pyx_L48_except_error)
                __Pyx_GOTREF(__pyx_t_21);
                #endif
              } else {
                if (__pyx_t_15 >= PyTuple_GET_SIZE(__pyx_t_24)) break;
                #if CYTHON_COMPILING_IN_CPYTHON
                __pyx_t_21 = PyTuple_GET_ITEM(__pyx_t_24, __pyx_t_15); __Pyx_INCREF(__pyx_t_21); __pyx_t_15++; if (unlikely(0 < 0)) __PYX_ERR(0, 269, __pyx_L48_except_error)
                #else
                __pyx_t_21 = PySequence_ITEM(__pyx_t_24, __pyx_t_15); __pyx_t_15++; if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 269, __pyx_L48_except_error)
                __Pyx_GOTREF(__pyx_t_21);
                #endif
              }
            } else {
              __pyx_t_21 = __pyx_t_19(__pyx_t_24);
              if (unlikely(!__pyx_t_21)) {
                PyObject* exc_type = PyErr_Occurred();
                if (exc_type) {
                  if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
                  else __PYX_ERR(0, 269, __pyx_L48_except_error)
                }
                break;
              }
              __Pyx_GOTREF(__pyx_t_21);
            }
            if ((likely(PyTuple_CheckExact(__pyx_t_21))) || (PyList_CheckExact(__pyx_t_21))) {
              PyObject* sequence = __pyx_t_21;
              #if CYTHON_COMPILING_IN_CPYTHON
              Py_ssize_t size = Py_SIZE(sequence);
              #else
              Py_ssize_t size = PySequence_Size(sequence);
              #endif
              if (unlikely(size != 2)) {
                if (size > 2) __Pyx_RaiseTooManyValuesError(2);
                else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
                __PYX_ERR(0, 269, __pyx_L48_except_error)
              }
              #if CYTHON_COMPILING_IN_CPYTHON
              if (likely(PyTuple_CheckExact(sequence))) {
                __pyx_t_26 = PyTuple_GET_ITEM(sequence, 0); 
                __pyx_t_23 = PyTuple_GET_ITEM(sequence, 1); 
              } else {
                __pyx_t_26 = PyList_GET_ITEM(sequence, 0); 
                __pyx_t_23 = PyList_GET_ITEM(sequence, 1); 
              }
              __Pyx_INCREF(__pyx_t_26);
              __Pyx_INCREF(__pyx_t_23);
              #else
              __pyx_t_26 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 269, __pyx_L48_except_error)
              __Pyx_GOTREF(__pyx_t_26);
              __pyx_t_23 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 269, __pyx_L48_except_error)
              __Pyx_GOTREF(__pyx_t_23);
              #endif
              __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
            } else {
              Py_ssize_t index = -1;
              __pyx_t_16 = PyObject_GetIter(__pyx_t_21); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 269, __pyx_L48_except_error)
              __Pyx_GOTREF(__pyx_t_16);
              __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
              __pyx_t_20 = Py_TYPE(__pyx_t_16)->tp_iternext;
              index = 0; __pyx_t_26 = __pyx_t_20(__pyx_t_16); if (unlikely(!__pyx_t_26)) goto __pyx_L58_unpacking_failed;
              __Pyx_GOTREF(__pyx_t_26);
              index = 1; __pyx_t_23 = __pyx_t_20(__pyx_t_16); if (unlikely(!__pyx_t_23)) goto __pyx_L58_unpacking_failed;
              __Pyx_GOTREF(__pyx_t_23);
              if (__Pyx_IternextUnpackEndCheck(__pyx_t_20(__pyx_t_16), 2) < 0) __PYX_ERR(0, 269, __pyx_L48_except_error)
              __pyx_t_20 = NULL;
              __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
              goto __pyx_L59_unpacking_done;
              __pyx_L58_unpacking_failed:;
              __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
              __pyx_t_20 = NULL;
              if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
              __PYX_ERR(0, 269, __pyx_L48_except_error)
              __pyx_L59_unpacking_done:;
            }
            __Pyx_XDECREF_SET(__pyx_v_j, __pyx_t_26);
            __pyx_t_26 = 0;
            __Pyx_XDECREF_SET(__pyx_v_s, __pyx_t_23);
            __pyx_t_23 = 0;

            /* "data_handler_v2.py":270
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.all_var_names, self.all_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))             # <<<<<<<<<<<<<<
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                         self.beams_count, self.gates_count)
 */
            __pyx_t_23 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 270, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __pyx_t_26 = __Pyx_PyObject_GetAttrStr(__pyx_t_23, __pyx_n_s_debug); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 270, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_26);
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
            __pyx_t_23 = PyTuple_New(2); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 270, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __Pyx_INCREF(__pyx_v_j);
            __Pyx_GIVEREF(__pyx_v_j);
            PyTuple_SET_ITEM(__pyx_t_23, 0, __pyx_v_j);
            __Pyx_INCREF(__pyx_v_s);
            __Pyx_GIVEREF(__pyx_v_s);
            PyTuple_SET_ITEM(__pyx_t_23, 1, __pyx_v_s);
            __pyx_t_16 = __Pyx_PyString_Format(__pyx_kp_s_Dumping_variable_s_s, __pyx_t_23); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 270, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_16);
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
            __pyx_t_23 = NULL;
            if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_26))) {
              __pyx_t_23 = PyMethod_GET_SELF(__pyx_t_26);
              if (likely(__pyx_t_23)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_26);
                __Pyx_INCREF(__pyx_t_23);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_26, function);
              }
            }
            if (!__pyx_t_23) {
              __pyx_t_21 = __Pyx_PyObject_CallOneArg(__pyx_t_26, __pyx_t_16); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 270, __pyx_L48_except_error)
              __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
              __Pyx_GOTREF(__pyx_t_21);
            } else {
              __pyx_t_18 = PyTuple_New(1+1); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 270, __pyx_L48_except_error)
              __Pyx_GOTREF(__pyx_t_18);
              __Pyx_GIVEREF(__pyx_t_23); PyTuple_SET_ITEM(__pyx_t_18, 0, __pyx_t_23); __pyx_t_23 = NULL;
              __Pyx_GIVEREF(__pyx_t_16);
              PyTuple_SET_ITEM(__pyx_t_18, 0+1, __pyx_t_16);
              __pyx_t_16 = 0;
              __pyx_t_21 = __Pyx_PyObject_Call(__pyx_t_26, __pyx_t_18, NULL); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 270, __pyx_L48_except_error)
              __Pyx_GOTREF(__pyx_t_21);
              __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            }
            __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
            __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;

            /* "data_handler_v2.py":271
 *                     for j, s in zip(self.all_var_names, self.all_var_suffix):
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,             # <<<<<<<<<<<<<<
 *                                         self.beams_count, self.gates_count)
 *                         pass
 */
            __pyx_t_26 = __Pyx_GetModuleGlobalName(__pyx_n_s_fill_data_function); if (unlikely(!__pyx_t_26)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_26);
            __pyx_t_18 = PyNumber_Add(__pyx_v_j, __pyx_v_mode); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __pyx_t_16 = PyObject_GetItem(__pyx_v_i, __pyx_t_18); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_16);
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            __pyx_t_18 = PyNumber_Add(__pyx_n_s_azimuth, __pyx_v_s); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __pyx_t_23 = PyNumber_Add(__pyx_t_18, __pyx_v_mode); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
            __pyx_t_18 = PyObject_GetItem(__pyx_v_i, __pyx_t_23); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_18);
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;
            __pyx_t_23 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __pyx_t_22 = PyObject_GetItem(__pyx_t_23, __pyx_v_j); if (unlikely(!__pyx_t_22)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_22);
            __Pyx_DECREF(__pyx_t_23); __pyx_t_23 = 0;

            /* "data_handler_v2.py":272
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 *                                         self.beams_count, self.gates_count)             # <<<<<<<<<<<<<<
 *                         pass
 *         pass
 */
            __pyx_t_23 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_beams_count); if (unlikely(!__pyx_t_23)) __PYX_ERR(0, 272, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_23);
            __pyx_t_14 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_gates_count); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 272, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_14);
            __pyx_t_1 = NULL;
            __pyx_t_25 = 0;
            if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_26))) {
              __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_26);
              if (likely(__pyx_t_1)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_26);
                __Pyx_INCREF(__pyx_t_1);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_26, function);
                __pyx_t_25 = 1;
              }
            }
            __pyx_t_12 = PyTuple_New(6+__pyx_t_25); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_12);
            if (__pyx_t_1) {
              __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_1); __pyx_t_1 = NULL;
            }
            __Pyx_GIVEREF(__pyx_t_16);
            PyTuple_SET_ITEM(__pyx_t_12, 0+__pyx_t_25, __pyx_t_16);
            __Pyx_GIVEREF(__pyx_t_18);
            PyTuple_SET_ITEM(__pyx_t_12, 1+__pyx_t_25, __pyx_t_18);
            __Pyx_GIVEREF(__pyx_t_22);
            PyTuple_SET_ITEM(__pyx_t_12, 2+__pyx_t_25, __pyx_t_22);
            __Pyx_INCREF(__pyx_v_elevation_index);
            __Pyx_GIVEREF(__pyx_v_elevation_index);
            PyTuple_SET_ITEM(__pyx_t_12, 3+__pyx_t_25, __pyx_v_elevation_index);
            __Pyx_GIVEREF(__pyx_t_23);
            PyTuple_SET_ITEM(__pyx_t_12, 4+__pyx_t_25, __pyx_t_23);
            __Pyx_GIVEREF(__pyx_t_14);
            PyTuple_SET_ITEM(__pyx_t_12, 5+__pyx_t_25, __pyx_t_14);
            __pyx_t_16 = 0;
            __pyx_t_18 = 0;
            __pyx_t_22 = 0;
            __pyx_t_23 = 0;
            __pyx_t_14 = 0;
            __pyx_t_21 = __Pyx_PyObject_Call(__pyx_t_26, __pyx_t_12, NULL); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 271, __pyx_L48_except_error)
            __Pyx_GOTREF(__pyx_t_21);
            __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
            __Pyx_DECREF(__pyx_t_26); __pyx_t_26 = 0;
            __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;

            /* "data_handler_v2.py":269
 *                     elevation_index = find_elevation_index(self.vcp_mode, elevation)
 *                     logging.info("%f - %d" % (elevation, elevation_index))
 *                     for j, s in zip(self.all_var_names, self.all_var_suffix):             # <<<<<<<<<<<<<<
 *                         logging.debug("Dumping variable: %s - %s" % (j, s))
 *                         fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
 */
          }
          __Pyx_DECREF(__pyx_t_24); __pyx_t_24 = 0;
          __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          goto __pyx_L47_exception_handled;
        }
        __pyx_L48_except_error:;

        /* "data_handler_v2.py":261
 *             # Normal case, all variables will be gathered in one scan
 *             else:
 *                 try:             # <<<<<<<<<<<<<<
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
 *                 except:
 */
        __Pyx_PyThreadState_assign
        __Pyx_XGIVEREF(__pyx_t_9);
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_ExceptionReset(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        goto __pyx_L1_error;
        __pyx_L47_exception_handled:;
        __Pyx_PyThreadState_assign
        __Pyx_XGIVEREF(__pyx_t_9);
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_ExceptionReset(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        __pyx_L53_try_end:;
      }
    }
    __pyx_L5:;

    /* "data_handler_v2.py":223
 *     def fill_data(self, *args, **kwargs):
 * 
 *         for i in self.time_data_dict.values():             # <<<<<<<<<<<<<<
 *             # There are several cases:
 *             # Case 1: CS case, only reflectivity related variable will be here
 */
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":221
 *                                self.beams_count, self.gates_count)
 * 
 *     def fill_data(self, *args, **kwargs):             # <<<<<<<<<<<<<<
 * 
 *         for i in self.time_data_dict.values():
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_12);
  __Pyx_XDECREF(__pyx_t_13);
  __Pyx_XDECREF(__pyx_t_14);
  __Pyx_XDECREF(__pyx_t_16);
  __Pyx_XDECREF(__pyx_t_17);
  __Pyx_XDECREF(__pyx_t_18);
  __Pyx_XDECREF(__pyx_t_21);
  __Pyx_XDECREF(__pyx_t_22);
  __Pyx_XDECREF(__pyx_t_23);
  __Pyx_XDECREF(__pyx_t_24);
  __Pyx_XDECREF(__pyx_t_26);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.fill_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XDECREF(__pyx_v_mode);
  __Pyx_XDECREF(__pyx_v_elevation);
  __Pyx_XDECREF(__pyx_v_elevation_index);
  __Pyx_XDECREF(__pyx_v_j);
  __Pyx_XDECREF(__pyx_v_s);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":276
 *         pass
 * 
 *     def mask_data(self):             # <<<<<<<<<<<<<<
 *         # Create a mask to remove all invalid data from reflectivity scan.
 *         total_mask = reduce(numpy.ma.logical_or,
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_17mask_data(PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_17mask_data = {"mask_data", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_17mask_data, METH_O, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_17mask_data(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("mask_data (wrapper)", 0);
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_16mask_data(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_16mask_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_v_total_mask = NULL;
  PyObject *__pyx_v_v = NULL;
  CYTHON_UNUSED PyObject *__pyx_v_k = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  Py_ssize_t __pyx_t_7;
  PyObject *(*__pyx_t_8)(PyObject *);
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyObject *(*__pyx_t_12)(PyObject *);
  __Pyx_RefNannySetupContext("mask_data", 0);

  /* "data_handler_v2.py":278
 *     def mask_data(self):
 *         # Create a mask to remove all invalid data from reflectivity scan.
 *         total_mask = reduce(numpy.ma.logical_or,             # <<<<<<<<<<<<<<
 *                             tuple([v.mask for k, v in self.data_dict]))
 *         # Update mask
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_reduce); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 278, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 278, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_ma); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 278, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_logical_or); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 278, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":279
 *         # Create a mask to remove all invalid data from reflectivity scan.
 *         total_mask = reduce(numpy.ma.logical_or,
 *                             tuple([v.mask for k, v in self.data_dict]))             # <<<<<<<<<<<<<<
 *         # Update mask
 *         for v in self.data_dict.values():
 */
  __pyx_t_4 = PyList_New(0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 279, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 279, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (likely(PyList_CheckExact(__pyx_t_5)) || PyTuple_CheckExact(__pyx_t_5)) {
    __pyx_t_6 = __pyx_t_5; __Pyx_INCREF(__pyx_t_6); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_6 = PyObject_GetIter(__pyx_t_5); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 279, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = Py_TYPE(__pyx_t_6)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 279, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_6))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_6)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_5 = PyList_GET_ITEM(__pyx_t_6, __pyx_t_7); __Pyx_INCREF(__pyx_t_5); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 279, __pyx_L1_error)
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_6, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 279, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_6)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_5 = PyTuple_GET_ITEM(__pyx_t_6, __pyx_t_7); __Pyx_INCREF(__pyx_t_5); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 279, __pyx_L1_error)
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_6, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 279, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        #endif
      }
    } else {
      __pyx_t_5 = __pyx_t_8(__pyx_t_6);
      if (unlikely(!__pyx_t_5)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 279, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_5);
    }
    if ((likely(PyTuple_CheckExact(__pyx_t_5))) || (PyList_CheckExact(__pyx_t_5))) {
      PyObject* sequence = __pyx_t_5;
      #if CYTHON_COMPILING_IN_CPYTHON
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 279, __pyx_L1_error)
      }
      #if CYTHON_COMPILING_IN_CPYTHON
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_9 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_10 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_9 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_10 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_10);
      #else
      __pyx_t_9 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 279, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_10 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 279, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      #endif
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_11 = PyObject_GetIter(__pyx_t_5); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 279, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_12 = Py_TYPE(__pyx_t_11)->tp_iternext;
      index = 0; __pyx_t_9 = __pyx_t_12(__pyx_t_11); if (unlikely(!__pyx_t_9)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_9);
      index = 1; __pyx_t_10 = __pyx_t_12(__pyx_t_11); if (unlikely(!__pyx_t_10)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_10);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_12(__pyx_t_11), 2) < 0) __PYX_ERR(0, 279, __pyx_L1_error)
      __pyx_t_12 = NULL;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      goto __pyx_L6_unpacking_done;
      __pyx_L5_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      __pyx_t_12 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 279, __pyx_L1_error)
      __pyx_L6_unpacking_done:;
    }
    __Pyx_XDECREF_SET(__pyx_v_k, __pyx_t_9);
    __pyx_t_9 = 0;
    __Pyx_XDECREF_SET(__pyx_v_v, __pyx_t_10);
    __pyx_t_10 = 0;
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_mask); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 279, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_4, (PyObject*)__pyx_t_5))) __PYX_ERR(0, 279, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyList_AsTuple(((PyObject*)__pyx_t_4)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 279, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  __pyx_t_7 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_7 = 1;
    }
  }
  __pyx_t_5 = PyTuple_New(2+__pyx_t_7); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 278, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (__pyx_t_4) {
    __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
  }
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 0+__pyx_t_7, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_5, 1+__pyx_t_7, __pyx_t_6);
  __pyx_t_3 = 0;
  __pyx_t_6 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 278, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_total_mask = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "data_handler_v2.py":281
 *                             tuple([v.mask for k, v in self.data_dict]))
 *         # Update mask
 *         for v in self.data_dict.values():             # <<<<<<<<<<<<<<
 *             v.mask = total_mask
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 281, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_values); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 281, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
    }
  }
  if (__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 281, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 281, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_5 = __pyx_t_1; __Pyx_INCREF(__pyx_t_5); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_5 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 281, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_8 = Py_TYPE(__pyx_t_5)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 281, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_5))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_5)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_5, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 281, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_5, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 281, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_5)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_5, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 281, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_5, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 281, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_8(__pyx_t_5);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 281, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    __Pyx_XDECREF_SET(__pyx_v_v, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "data_handler_v2.py":282
 *         # Update mask
 *         for v in self.data_dict.values():
 *             v.mask = total_mask             # <<<<<<<<<<<<<<
 * 
 *     def output2file(self, path, coordinate):
 */
    if (__Pyx_PyObject_SetAttrStr(__pyx_v_v, __pyx_n_s_mask, __pyx_v_total_mask) < 0) __PYX_ERR(0, 282, __pyx_L1_error)

    /* "data_handler_v2.py":281
 *                             tuple([v.mask for k, v in self.data_dict]))
 *         # Update mask
 *         for v in self.data_dict.values():             # <<<<<<<<<<<<<<
 *             v.mask = total_mask
 * 
 */
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":276
 *         pass
 * 
 *     def mask_data(self):             # <<<<<<<<<<<<<<
 *         # Create a mask to remove all invalid data from reflectivity scan.
 *         total_mask = reduce(numpy.ma.logical_or,
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.mask_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_total_mask);
  __Pyx_XDECREF(__pyx_v_v);
  __Pyx_XDECREF(__pyx_v_k);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "data_handler_v2.py":284
 *             v.mask = total_mask
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */

/* Python wrapper */
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_19output2file(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_15data_handler_v2_11RadarNetcdf_19output2file = {"output2file", (PyCFunction)__pyx_pw_15data_handler_v2_11RadarNetcdf_19output2file, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15data_handler_v2_11RadarNetcdf_19output2file(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  CYTHON_UNUSED PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_path = 0;
  PyObject *__pyx_v_coordinate = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("output2file (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,&__pyx_n_s_path,&__pyx_n_s_coordinate,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_path)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("output2file", 1, 3, 3, 1); __PYX_ERR(0, 284, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_coordinate)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("output2file", 1, 3, 3, 2); __PYX_ERR(0, 284, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "output2file") < 0)) __PYX_ERR(0, 284, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v_self = values[0];
    __pyx_v_path = values[1];
    __pyx_v_coordinate = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("output2file", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 284, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.output2file", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15data_handler_v2_11RadarNetcdf_18output2file(__pyx_self, __pyx_v_self, __pyx_v_path, __pyx_v_coordinate);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15data_handler_v2_11RadarNetcdf_18output2file(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_path, PyObject *__pyx_v_coordinate) {
  PyObject *__pyx_v_f = NULL;
  PyObject *__pyx_v_point = NULL;
  PyObject *__pyx_v_attr = NULL;
  PyObject *__pyx_v_variable = NULL;
  PyObject *__pyx_v_value = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t __pyx_t_4;
  PyObject *(*__pyx_t_5)(PyObject *);
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *(*__pyx_t_8)(PyObject *);
  PyObject *__pyx_t_9 = NULL;
  Py_ssize_t __pyx_t_10;
  PyObject *(*__pyx_t_11)(PyObject *);
  PyObject *__pyx_t_12 = NULL;
  __Pyx_RefNannySetupContext("output2file", 0);

  /* "data_handler_v2.py":285
 * 
 *     def output2file(self, path, coordinate):
 *         print("start output...")             # <<<<<<<<<<<<<<
 *         f = open(path, 'w')
 *         for point, attr in coordinate.items():
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s_start_output) < 0) __PYX_ERR(0, 285, __pyx_L1_error)

  /* "data_handler_v2.py":286
 *     def output2file(self, path, coordinate):
 *         print("start output...")
 *         f = open(path, 'w')             # <<<<<<<<<<<<<<
 *         for point, attr in coordinate.items():
 *             f.write(str(point))
 */
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 286, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_path);
  __Pyx_GIVEREF(__pyx_v_path);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_path);
  __Pyx_INCREF(__pyx_n_s_w);
  __Pyx_GIVEREF(__pyx_n_s_w);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_w);
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_1, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 286, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_f = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "data_handler_v2.py":287
 *         print("start output...")
 *         f = open(path, 'w')
 *         for point, attr in coordinate.items():             # <<<<<<<<<<<<<<
 *             f.write(str(point))
 *             f.write(' ')
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_coordinate, __pyx_n_s_items); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 287, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 287, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 287, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (likely(PyList_CheckExact(__pyx_t_2)) || PyTuple_CheckExact(__pyx_t_2)) {
    __pyx_t_1 = __pyx_t_2; __Pyx_INCREF(__pyx_t_1); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 287, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 287, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_2); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 287, __pyx_L1_error)
        #else
        __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 287, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_2 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_2); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 287, __pyx_L1_error)
        #else
        __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 287, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        #endif
      }
    } else {
      __pyx_t_2 = __pyx_t_5(__pyx_t_1);
      if (unlikely(!__pyx_t_2)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 287, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_2);
    }
    if ((likely(PyTuple_CheckExact(__pyx_t_2))) || (PyList_CheckExact(__pyx_t_2))) {
      PyObject* sequence = __pyx_t_2;
      #if CYTHON_COMPILING_IN_CPYTHON
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 287, __pyx_L1_error)
      }
      #if CYTHON_COMPILING_IN_CPYTHON
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_3 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_6 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_3 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_6 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_6);
      #else
      __pyx_t_3 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 287, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_6 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 287, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      #endif
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_7 = PyObject_GetIter(__pyx_t_2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 287, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_8 = Py_TYPE(__pyx_t_7)->tp_iternext;
      index = 0; __pyx_t_3 = __pyx_t_8(__pyx_t_7); if (unlikely(!__pyx_t_3)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_3);
      index = 1; __pyx_t_6 = __pyx_t_8(__pyx_t_7); if (unlikely(!__pyx_t_6)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_6);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_8(__pyx_t_7), 2) < 0) __PYX_ERR(0, 287, __pyx_L1_error)
      __pyx_t_8 = NULL;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      goto __pyx_L6_unpacking_done;
      __pyx_L5_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 287, __pyx_L1_error)
      __pyx_L6_unpacking_done:;
    }
    __Pyx_XDECREF_SET(__pyx_v_point, __pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_XDECREF_SET(__pyx_v_attr, __pyx_t_6);
    __pyx_t_6 = 0;

    /* "data_handler_v2.py":288
 *         f = open(path, 'w')
 *         for point, attr in coordinate.items():
 *             f.write(str(point))             # <<<<<<<<<<<<<<
 *             f.write(' ')
 *             for variable, value in attr.items():
 */
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_v_point);
    __Pyx_GIVEREF(__pyx_v_point);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_point);
    __pyx_t_7 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_3, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (!__pyx_t_3) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 288, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      __pyx_t_9 = PyTuple_New(1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 288, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_GIVEREF(__pyx_t_7);
      PyTuple_SET_ITEM(__pyx_t_9, 0+1, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_9, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 288, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "data_handler_v2.py":289
 *         for point, attr in coordinate.items():
 *             f.write(str(point))
 *             f.write(' ')             # <<<<<<<<<<<<<<
 *             for variable, value in attr.items():
 *                 f.write(variable)
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 289, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__24, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 289, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "data_handler_v2.py":290
 *             f.write(str(point))
 *             f.write(' ')
 *             for variable, value in attr.items():             # <<<<<<<<<<<<<<
 *                 f.write(variable)
 *                 f.write(':')
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_attr, __pyx_n_s_items); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_9 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (__pyx_t_9) {
      __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_9); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    } else {
      __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (likely(PyList_CheckExact(__pyx_t_6)) || PyTuple_CheckExact(__pyx_t_6)) {
      __pyx_t_2 = __pyx_t_6; __Pyx_INCREF(__pyx_t_2); __pyx_t_10 = 0;
      __pyx_t_11 = NULL;
    } else {
      __pyx_t_10 = -1; __pyx_t_2 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 290, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_11 = Py_TYPE(__pyx_t_2)->tp_iternext; if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 290, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    for (;;) {
      if (likely(!__pyx_t_11)) {
        if (likely(PyList_CheckExact(__pyx_t_2))) {
          if (__pyx_t_10 >= PyList_GET_SIZE(__pyx_t_2)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_6 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_10); __Pyx_INCREF(__pyx_t_6); __pyx_t_10++; if (unlikely(0 < 0)) __PYX_ERR(0, 290, __pyx_L1_error)
          #else
          __pyx_t_6 = PySequence_ITEM(__pyx_t_2, __pyx_t_10); __pyx_t_10++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          #endif
        } else {
          if (__pyx_t_10 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_6 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_10); __Pyx_INCREF(__pyx_t_6); __pyx_t_10++; if (unlikely(0 < 0)) __PYX_ERR(0, 290, __pyx_L1_error)
          #else
          __pyx_t_6 = PySequence_ITEM(__pyx_t_2, __pyx_t_10); __pyx_t_10++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          #endif
        }
      } else {
        __pyx_t_6 = __pyx_t_11(__pyx_t_2);
        if (unlikely(!__pyx_t_6)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 290, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_6);
      }
      if ((likely(PyTuple_CheckExact(__pyx_t_6))) || (PyList_CheckExact(__pyx_t_6))) {
        PyObject* sequence = __pyx_t_6;
        #if CYTHON_COMPILING_IN_CPYTHON
        Py_ssize_t size = Py_SIZE(sequence);
        #else
        Py_ssize_t size = PySequence_Size(sequence);
        #endif
        if (unlikely(size != 2)) {
          if (size > 2) __Pyx_RaiseTooManyValuesError(2);
          else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
          __PYX_ERR(0, 290, __pyx_L1_error)
        }
        #if CYTHON_COMPILING_IN_CPYTHON
        if (likely(PyTuple_CheckExact(sequence))) {
          __pyx_t_9 = PyTuple_GET_ITEM(sequence, 0); 
          __pyx_t_7 = PyTuple_GET_ITEM(sequence, 1); 
        } else {
          __pyx_t_9 = PyList_GET_ITEM(sequence, 0); 
          __pyx_t_7 = PyList_GET_ITEM(sequence, 1); 
        }
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(__pyx_t_7);
        #else
        __pyx_t_9 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 290, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __pyx_t_7 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 290, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        #endif
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else {
        Py_ssize_t index = -1;
        __pyx_t_3 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 290, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_8 = Py_TYPE(__pyx_t_3)->tp_iternext;
        index = 0; __pyx_t_9 = __pyx_t_8(__pyx_t_3); if (unlikely(!__pyx_t_9)) goto __pyx_L9_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_9);
        index = 1; __pyx_t_7 = __pyx_t_8(__pyx_t_3); if (unlikely(!__pyx_t_7)) goto __pyx_L9_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_7);
        if (__Pyx_IternextUnpackEndCheck(__pyx_t_8(__pyx_t_3), 2) < 0) __PYX_ERR(0, 290, __pyx_L1_error)
        __pyx_t_8 = NULL;
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        goto __pyx_L10_unpacking_done;
        __pyx_L9_unpacking_failed:;
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_8 = NULL;
        if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
        __PYX_ERR(0, 290, __pyx_L1_error)
        __pyx_L10_unpacking_done:;
      }
      __Pyx_XDECREF_SET(__pyx_v_variable, __pyx_t_9);
      __pyx_t_9 = 0;
      __Pyx_XDECREF_SET(__pyx_v_value, __pyx_t_7);
      __pyx_t_7 = 0;

      /* "data_handler_v2.py":291
 *             f.write(' ')
 *             for variable, value in attr.items():
 *                 f.write(variable)             # <<<<<<<<<<<<<<
 *                 f.write(':')
 *                 f.write(str(value))
 */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 291, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_9 = NULL;
      if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_7))) {
        __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_7);
        if (likely(__pyx_t_9)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
          __Pyx_INCREF(__pyx_t_9);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_7, function);
        }
      }
      if (!__pyx_t_9) {
        __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_v_variable); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 291, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
      } else {
        __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 291, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_9); __pyx_t_9 = NULL;
        __Pyx_INCREF(__pyx_v_variable);
        __Pyx_GIVEREF(__pyx_v_variable);
        PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_variable);
        __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_3, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 291, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      }
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

      /* "data_handler_v2.py":292
 *             for variable, value in attr.items():
 *                 f.write(variable)
 *                 f.write(':')             # <<<<<<<<<<<<<<
 *                 f.write(str(value))
 *                 f.write(' ')
 */
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 292, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_tuple__26, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 292, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

      /* "data_handler_v2.py":293
 *                 f.write(variable)
 *                 f.write(':')
 *                 f.write(str(value))             # <<<<<<<<<<<<<<
 *                 f.write(' ')
 *             f.write('\n')
 */
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 293, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 293, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_INCREF(__pyx_v_value);
      __Pyx_GIVEREF(__pyx_v_value);
      PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_value);
      __pyx_t_9 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_3, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 293, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = NULL;
      if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_6))) {
        __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_6);
        if (likely(__pyx_t_3)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
          __Pyx_INCREF(__pyx_t_3);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_6, function);
        }
      }
      if (!__pyx_t_3) {
        __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_9); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 293, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_7);
      } else {
        __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 293, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_3); __pyx_t_3 = NULL;
        __Pyx_GIVEREF(__pyx_t_9);
        PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_t_9);
        __pyx_t_9 = 0;
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_12, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 293, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
      }
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

      /* "data_handler_v2.py":294
 *                 f.write(':')
 *                 f.write(str(value))
 *                 f.write(' ')             # <<<<<<<<<<<<<<
 *             f.write('\n')
 *         f.close()
 */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 294, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__27, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 294, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

      /* "data_handler_v2.py":290
 *             f.write(str(point))
 *             f.write(' ')
 *             for variable, value in attr.items():             # <<<<<<<<<<<<<<
 *                 f.write(variable)
 *                 f.write(':')
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "data_handler_v2.py":295
 *                 f.write(str(value))
 *                 f.write(' ')
 *             f.write('\n')             # <<<<<<<<<<<<<<
 *         f.close()
 *         print("finish output")
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 295, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__29, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 295, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "data_handler_v2.py":287
 *         print("start output...")
 *         f = open(path, 'w')
 *         for point, attr in coordinate.items():             # <<<<<<<<<<<<<<
 *             f.write(str(point))
 *             f.write(' ')
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":296
 *                 f.write(' ')
 *             f.write('\n')
 *         f.close()             # <<<<<<<<<<<<<<
 *         print("finish output")
 * 
 */
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_close); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 296, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_2 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_6))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_6);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_6, function);
    }
  }
  if (__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 296, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 296, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":297
 *             f.write('\n')
 *         f.close()
 *         print("finish output")             # <<<<<<<<<<<<<<
 * 
 * 
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s_finish_output) < 0) __PYX_ERR(0, 297, __pyx_L1_error)

  /* "data_handler_v2.py":284
 *             v.mask = total_mask
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_12);
  __Pyx_AddTraceback("data_handler_v2.RadarNetcdf.output2file", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_f);
  __Pyx_XDECREF(__pyx_v_point);
  __Pyx_XDECREF(__pyx_v_attr);
  __Pyx_XDECREF(__pyx_v_variable);
  __Pyx_XDECREF(__pyx_v_value);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    "data_handler_v2",
    0, /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_n_s_CorrelationCoefficient, __pyx_k_CorrelationCoefficient, sizeof(__pyx_k_CorrelationCoefficient), 0, 0, 1, 1},
  {&__pyx_n_s_DEBUG, __pyx_k_DEBUG, sizeof(__pyx_k_DEBUG), 0, 0, 1, 1},
  {&__pyx_n_s_Dataset, __pyx_k_Dataset, sizeof(__pyx_k_Dataset), 0, 0, 1, 1},
  {&__pyx_n_s_Dict, __pyx_k_Dict, sizeof(__pyx_k_Dict), 0, 0, 1, 1},
  {&__pyx_n_s_DifferentialPhase, __pyx_k_DifferentialPhase, sizeof(__pyx_k_DifferentialPhase), 0, 0, 1, 1},
  {&__pyx_n_s_DifferentialReflectivity, __pyx_k_DifferentialReflectivity, sizeof(__pyx_k_DifferentialReflectivity), 0, 0, 1, 1},
  {&__pyx_n_s_DifferentialReflectivity_2, __pyx_k_DifferentialReflectivity_2, sizeof(__pyx_k_DifferentialReflectivity_2), 0, 0, 1, 1},
  {&__pyx_kp_s_Dumping_variable_s_s, __pyx_k_Dumping_variable_s_s, sizeof(__pyx_k_Dumping_variable_s_s), 0, 0, 1, 0},
  {&__pyx_n_s_EchoTop10Z, __pyx_k_EchoTop10Z, sizeof(__pyx_k_EchoTop10Z), 0, 0, 1, 1},
  {&__pyx_n_s_EchoTop20Z, __pyx_k_EchoTop20Z, sizeof(__pyx_k_EchoTop20Z), 0, 0, 1, 1},
  {&__pyx_n_s_EchoTop5Z, __pyx_k_EchoTop5Z, sizeof(__pyx_k_EchoTop5Z), 0, 0, 1, 1},
  {&__pyx_kp_s_Failed_to_run_JIT_functions, __pyx_k_Failed_to_run_JIT_functions, sizeof(__pyx_k_Failed_to_run_JIT_functions), 0, 0, 1, 0},
  {&__pyx_kp_s_Failed_to_run_JITed_fill_data_fu, __pyx_k_Failed_to_run_JITed_fill_data_fu, sizeof(__pyx_k_Failed_to_run_JITed_fill_data_fu), 0, 0, 1, 0},
  {&__pyx_kp_s_Failed_to_run_JITed_fill_data_fu_2, __pyx_k_Failed_to_run_JITed_fill_data_fu_2, sizeof(__pyx_k_Failed_to_run_JITed_fill_data_fu_2), 0, 0, 1, 0},
  {&__pyx_kp_s_Failed_to_run_JITed_fill_data_fu_3, __pyx_k_Failed_to_run_JITed_fill_data_fu_3, sizeof(__pyx_k_Failed_to_run_JITed_fill_data_fu_3), 0, 0, 1, 0},
  {&__pyx_kp_s_Fix_unsigned_variable, __pyx_k_Fix_unsigned_variable, sizeof(__pyx_k_Fix_unsigned_variable), 0, 0, 1, 0},
  {&__pyx_n_s_HI, __pyx_k_HI, sizeof(__pyx_k_HI), 0, 0, 1, 1},
  {&__pyx_n_s_KeyError, __pyx_k_KeyError, sizeof(__pyx_k_KeyError), 0, 0, 1, 1},
  {&__pyx_n_s_List, __pyx_k_List, sizeof(__pyx_k_List), 0, 0, 1, 1},
  {&__pyx_n_s_MaskedArray, __pyx_k_MaskedArray, sizeof(__pyx_k_MaskedArray), 0, 0, 1, 1},
  {&__pyx_n_s_OrderedDict, __pyx_k_OrderedDict, sizeof(__pyx_k_OrderedDict), 0, 0, 1, 1},
  {&__pyx_n_s_R, __pyx_k_R, sizeof(__pyx_k_R), 0, 0, 1, 1},
  {&__pyx_n_s_RDCP, __pyx_k_RDCP, sizeof(__pyx_k_RDCP), 0, 0, 1, 1},
  {&__pyx_n_s_RVVDCP, __pyx_k_RVVDCP, sizeof(__pyx_k_RVVDCP), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf, __pyx_k_RadarNetcdf, sizeof(__pyx_k_RadarNetcdf), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf___dump, __pyx_k_RadarNetcdf___dump, sizeof(__pyx_k_RadarNetcdf___dump), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf___fill_data_internal, __pyx_k_RadarNetcdf___fill_data_internal, sizeof(__pyx_k_RadarNetcdf___fill_data_internal), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf___fix_variable, __pyx_k_RadarNetcdf___fix_variable, sizeof(__pyx_k_RadarNetcdf___fix_variable), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf___init, __pyx_k_RadarNetcdf___init, sizeof(__pyx_k_RadarNetcdf___init), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf__dump, __pyx_k_RadarNetcdf__dump, sizeof(__pyx_k_RadarNetcdf__dump), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf__fill_data_internal, __pyx_k_RadarNetcdf__fill_data_internal, sizeof(__pyx_k_RadarNetcdf__fill_data_internal), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf_dump_data_by_time, __pyx_k_RadarNetcdf_dump_data_by_time, sizeof(__pyx_k_RadarNetcdf_dump_data_by_time), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf_fill_data, __pyx_k_RadarNetcdf_fill_data, sizeof(__pyx_k_RadarNetcdf_fill_data), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf_first_pass, __pyx_k_RadarNetcdf_first_pass, sizeof(__pyx_k_RadarNetcdf_first_pass), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf_is_filled, __pyx_k_RadarNetcdf_is_filled, sizeof(__pyx_k_RadarNetcdf_is_filled), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf_mask_data, __pyx_k_RadarNetcdf_mask_data, sizeof(__pyx_k_RadarNetcdf_mask_data), 0, 0, 1, 1},
  {&__pyx_n_s_RadarNetcdf_output2file, __pyx_k_RadarNetcdf_output2file, sizeof(__pyx_k_RadarNetcdf_output2file), 0, 0, 1, 1},
  {&__pyx_n_s_RadialVelocity, __pyx_k_RadialVelocity, sizeof(__pyx_k_RadialVelocity), 0, 0, 1, 1},
  {&__pyx_n_s_Reflectivity, __pyx_k_Reflectivity, sizeof(__pyx_k_Reflectivity), 0, 0, 1, 1},
  {&__pyx_n_s_Reflectivity_Avg1x5, __pyx_k_Reflectivity_Avg1x5, sizeof(__pyx_k_Reflectivity_Avg1x5), 0, 0, 1, 1},
  {&__pyx_n_s_Reflectivity_Avg3x3, __pyx_k_Reflectivity_Avg3x3, sizeof(__pyx_k_Reflectivity_Avg3x3), 0, 0, 1, 1},
  {&__pyx_n_s_Reflectivity_Std1x5, __pyx_k_Reflectivity_Std1x5, sizeof(__pyx_k_Reflectivity_Std1x5), 0, 0, 1, 1},
  {&__pyx_n_s_Reflectivity_Std3x3, __pyx_k_Reflectivity_Std3x3, sizeof(__pyx_k_Reflectivity_Std3x3), 0, 0, 1, 1},
  {&__pyx_n_s_SortedDict, __pyx_k_SortedDict, sizeof(__pyx_k_SortedDict), 0, 0, 1, 1},
  {&__pyx_n_s_SpectrumWidth, __pyx_k_SpectrumWidth, sizeof(__pyx_k_SpectrumWidth), 0, 0, 1, 1},
  {&__pyx_n_s_Tuple, __pyx_k_Tuple, sizeof(__pyx_k_Tuple), 0, 0, 1, 1},
  {&__pyx_n_s_Unsigned, __pyx_k_Unsigned, sizeof(__pyx_k_Unsigned), 0, 0, 1, 1},
  {&__pyx_n_s_VV, __pyx_k_VV, sizeof(__pyx_k_VV), 0, 0, 1, 1},
  {&__pyx_n_s_Variable, __pyx_k_Variable, sizeof(__pyx_k_Variable), 0, 0, 1, 1},
  {&__pyx_n_s_VcpTable, __pyx_k_VcpTable, sizeof(__pyx_k_VcpTable), 0, 0, 1, 1},
  {&__pyx_n_s_VolumeCoveragePattern, __pyx_k_VolumeCoveragePattern, sizeof(__pyx_k_VolumeCoveragePattern), 0, 0, 1, 1},
  {&__pyx_kp_s__13, __pyx_k__13, sizeof(__pyx_k__13), 0, 0, 1, 0},
  {&__pyx_kp_s__23, __pyx_k__23, sizeof(__pyx_k__23), 0, 0, 1, 0},
  {&__pyx_kp_s__25, __pyx_k__25, sizeof(__pyx_k__25), 0, 0, 1, 0},
  {&__pyx_kp_s__28, __pyx_k__28, sizeof(__pyx_k__28), 0, 0, 1, 0},
  {&__pyx_n_s_a, __pyx_k_a, sizeof(__pyx_k_a), 0, 0, 1, 1},
  {&__pyx_n_s_ad, __pyx_k_ad, sizeof(__pyx_k_ad), 0, 0, 1, 1},
  {&__pyx_n_s_add_offset, __pyx_k_add_offset, sizeof(__pyx_k_add_offset), 0, 0, 1, 1},
  {&__pyx_n_s_all, __pyx_k_all, sizeof(__pyx_k_all), 0, 0, 1, 1},
  {&__pyx_n_s_all_var_names, __pyx_k_all_var_names, sizeof(__pyx_k_all_var_names), 0, 0, 1, 1},
  {&__pyx_n_s_all_var_suffix, __pyx_k_all_var_suffix, sizeof(__pyx_k_all_var_suffix), 0, 0, 1, 1},
  {&__pyx_n_s_args, __pyx_k_args, sizeof(__pyx_k_args), 0, 0, 1, 1},
  {&__pyx_n_s_array_shape, __pyx_k_array_shape, sizeof(__pyx_k_array_shape), 0, 0, 1, 1},
  {&__pyx_n_s_attr, __pyx_k_attr, sizeof(__pyx_k_attr), 0, 0, 1, 1},
  {&__pyx_n_s_axis, __pyx_k_axis, sizeof(__pyx_k_axis), 0, 0, 1, 1},
  {&__pyx_n_s_az_downscale, __pyx_k_az_downscale, sizeof(__pyx_k_az_downscale), 0, 0, 1, 1},
  {&__pyx_n_s_az_index, __pyx_k_az_index, sizeof(__pyx_k_az_index), 0, 0, 1, 1},
  {&__pyx_n_s_azimuth, __pyx_k_azimuth, sizeof(__pyx_k_azimuth), 0, 0, 1, 1},
  {&__pyx_n_s_azimuth_array, __pyx_k_azimuth_array, sizeof(__pyx_k_azimuth_array), 0, 0, 1, 1},
  {&__pyx_n_s_b1, __pyx_k_b1, sizeof(__pyx_k_b1), 0, 0, 1, 1},
  {&__pyx_n_s_basicConfig, __pyx_k_basicConfig, sizeof(__pyx_k_basicConfig), 0, 0, 1, 1},
  {&__pyx_n_s_beams_count, __pyx_k_beams_count, sizeof(__pyx_k_beams_count), 0, 0, 1, 1},
  {&__pyx_n_s_close, __pyx_k_close, sizeof(__pyx_k_close), 0, 0, 1, 1},
  {&__pyx_n_s_coordinate, __pyx_k_coordinate, sizeof(__pyx_k_coordinate), 0, 0, 1, 1},
  {&__pyx_n_s_data, __pyx_k_data, sizeof(__pyx_k_data), 0, 0, 1, 1},
  {&__pyx_n_s_data_dict, __pyx_k_data_dict, sizeof(__pyx_k_data_dict), 0, 0, 1, 1},
  {&__pyx_n_s_data_handler_v2, __pyx_k_data_handler_v2, sizeof(__pyx_k_data_handler_v2), 0, 0, 1, 1},
  {&__pyx_n_s_dataset, __pyx_k_dataset, sizeof(__pyx_k_dataset), 0, 0, 1, 1},
  {&__pyx_n_s_datatype, __pyx_k_datatype, sizeof(__pyx_k_datatype), 0, 0, 1, 1},
  {&__pyx_n_s_datetime, __pyx_k_datetime, sizeof(__pyx_k_datetime), 0, 0, 1, 1},
  {&__pyx_n_s_debug, __pyx_k_debug, sizeof(__pyx_k_debug), 0, 0, 1, 1},
  {&__pyx_n_s_dict, __pyx_k_dict, sizeof(__pyx_k_dict), 0, 0, 1, 1},
  {&__pyx_n_s_doc, __pyx_k_doc, sizeof(__pyx_k_doc), 0, 0, 1, 1},
  {&__pyx_n_s_ds, __pyx_k_ds, sizeof(__pyx_k_ds), 0, 0, 1, 1},
  {&__pyx_n_s_dtype, __pyx_k_dtype, sizeof(__pyx_k_dtype), 0, 0, 1, 1},
  {&__pyx_n_s_dualpol, __pyx_k_dualpol, sizeof(__pyx_k_dualpol), 0, 0, 1, 1},
  {&__pyx_n_s_dump, __pyx_k_dump, sizeof(__pyx_k_dump), 0, 0, 1, 1},
  {&__pyx_n_s_dump_array, __pyx_k_dump_array, sizeof(__pyx_k_dump_array), 0, 0, 1, 1},
  {&__pyx_n_s_dump_data_by_time, __pyx_k_dump_data_by_time, sizeof(__pyx_k_dump_data_by_time), 0, 0, 1, 1},
  {&__pyx_n_s_dump_dict, __pyx_k_dump_dict, sizeof(__pyx_k_dump_dict), 0, 0, 1, 1},
  {&__pyx_n_s_dump_target, __pyx_k_dump_target, sizeof(__pyx_k_dump_target), 0, 0, 1, 1},
  {&__pyx_n_s_dump_var_names, __pyx_k_dump_var_names, sizeof(__pyx_k_dump_var_names), 0, 0, 1, 1},
  {&__pyx_n_s_e, __pyx_k_e, sizeof(__pyx_k_e), 0, 0, 1, 1},
  {&__pyx_n_s_ediff1d, __pyx_k_ediff1d, sizeof(__pyx_k_ediff1d), 0, 0, 1, 1},
  {&__pyx_n_s_elevation, __pyx_k_elevation, sizeof(__pyx_k_elevation), 0, 0, 1, 1},
  {&__pyx_n_s_elevationR, __pyx_k_elevationR, sizeof(__pyx_k_elevationR), 0, 0, 1, 1},
  {&__pyx_n_s_elevationR_HI, __pyx_k_elevationR_HI, sizeof(__pyx_k_elevationR_HI), 0, 0, 1, 1},
  {&__pyx_n_s_elevationV, __pyx_k_elevationV, sizeof(__pyx_k_elevationV), 0, 0, 1, 1},
  {&__pyx_n_s_elevationV_HI, __pyx_k_elevationV_HI, sizeof(__pyx_k_elevationV_HI), 0, 0, 1, 1},
  {&__pyx_n_s_elevation_index, __pyx_k_elevation_index, sizeof(__pyx_k_elevation_index), 0, 0, 1, 1},
  {&__pyx_n_s_empty, __pyx_k_empty, sizeof(__pyx_k_empty), 0, 0, 1, 1},
  {&__pyx_n_s_end, __pyx_k_end, sizeof(__pyx_k_end), 0, 0, 1, 1},
  {&__pyx_n_s_extended_data_dict, __pyx_k_extended_data_dict, sizeof(__pyx_k_extended_data_dict), 0, 0, 1, 1},
  {&__pyx_n_s_f, __pyx_k_f, sizeof(__pyx_k_f), 0, 0, 1, 1},
  {&__pyx_n_s_f4, __pyx_k_f4, sizeof(__pyx_k_f4), 0, 0, 1, 1},
  {&__pyx_kp_s_f_d, __pyx_k_f_d, sizeof(__pyx_k_f_d), 0, 0, 1, 0},
  {&__pyx_n_s_file, __pyx_k_file, sizeof(__pyx_k_file), 0, 0, 1, 1},
  {&__pyx_n_s_fill, __pyx_k_fill, sizeof(__pyx_k_fill), 0, 0, 1, 1},
  {&__pyx_n_s_fill_data, __pyx_k_fill_data, sizeof(__pyx_k_fill_data), 0, 0, 1, 1},
  {&__pyx_n_s_fill_data_function, __pyx_k_fill_data_function, sizeof(__pyx_k_fill_data_function), 0, 0, 1, 1},
  {&__pyx_n_s_fill_data_internal, __pyx_k_fill_data_internal, sizeof(__pyx_k_fill_data_internal), 0, 0, 1, 1},
  {&__pyx_n_s_fill_data_jit, __pyx_k_fill_data_jit, sizeof(__pyx_k_fill_data_jit), 0, 0, 1, 1},
  {&__pyx_n_s_fill_data_nojit, __pyx_k_fill_data_nojit, sizeof(__pyx_k_fill_data_nojit), 0, 0, 1, 1},
  {&__pyx_n_s_filling_table, __pyx_k_filling_table, sizeof(__pyx_k_filling_table), 0, 0, 1, 1},
  {&__pyx_n_s_find_elevation_index, __pyx_k_find_elevation_index, sizeof(__pyx_k_find_elevation_index), 0, 0, 1, 1},
  {&__pyx_kp_s_finish_output, __pyx_k_finish_output, sizeof(__pyx_k_finish_output), 0, 0, 1, 0},
  {&__pyx_n_s_first_pass, __pyx_k_first_pass, sizeof(__pyx_k_first_pass), 0, 0, 1, 1},
  {&__pyx_n_s_fix_variable, __pyx_k_fix_variable, sizeof(__pyx_k_fix_variable), 0, 0, 1, 1},
  {&__pyx_n_s_functools, __pyx_k_functools, sizeof(__pyx_k_functools), 0, 0, 1, 1},
  {&__pyx_n_s_gate_array, __pyx_k_gate_array, sizeof(__pyx_k_gate_array), 0, 0, 1, 1},
  {&__pyx_n_s_gates_count, __pyx_k_gates_count, sizeof(__pyx_k_gates_count), 0, 0, 1, 1},
  {&__pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_k_home_sugar_Developer_Cloud2016, sizeof(__pyx_k_home_sugar_Developer_Cloud2016), 0, 0, 1, 0},
  {&__pyx_kp_s_home_sugar_Developer_Cloud2016_2, __pyx_k_home_sugar_Developer_Cloud2016_2, sizeof(__pyx_k_home_sugar_Developer_Cloud2016_2), 0, 0, 1, 0},
  {&__pyx_n_s_i, __pyx_k_i, sizeof(__pyx_k_i), 0, 0, 1, 1},
  {&__pyx_n_s_id_var, __pyx_k_id_var, sizeof(__pyx_k_id_var), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_info, __pyx_k_info, sizeof(__pyx_k_info), 0, 0, 1, 1},
  {&__pyx_n_s_init, __pyx_k_init, sizeof(__pyx_k_init), 0, 0, 1, 1},
  {&__pyx_n_s_is_filled, __pyx_k_is_filled, sizeof(__pyx_k_is_filled), 0, 0, 1, 1},
  {&__pyx_n_s_items, __pyx_k_items, sizeof(__pyx_k_items), 0, 0, 1, 1},
  {&__pyx_n_s_j, __pyx_k_j, sizeof(__pyx_k_j), 0, 0, 1, 1},
  {&__pyx_n_s_jit, __pyx_k_jit, sizeof(__pyx_k_jit), 0, 0, 1, 1},
  {&__pyx_n_s_json, __pyx_k_json, sizeof(__pyx_k_json), 0, 0, 1, 1},
  {&__pyx_n_s_k, __pyx_k_k, sizeof(__pyx_k_k), 0, 0, 1, 1},
  {&__pyx_n_s_kwargs, __pyx_k_kwargs, sizeof(__pyx_k_kwargs), 0, 0, 1, 1},
  {&__pyx_n_s_legacy, __pyx_k_legacy, sizeof(__pyx_k_legacy), 0, 0, 1, 1},
  {&__pyx_n_s_legacy_mode, __pyx_k_legacy_mode, sizeof(__pyx_k_legacy_mode), 0, 0, 1, 1},
  {&__pyx_n_s_level, __pyx_k_level, sizeof(__pyx_k_level), 0, 0, 1, 1},
  {&__pyx_n_s_logging, __pyx_k_logging, sizeof(__pyx_k_logging), 0, 0, 1, 1},
  {&__pyx_n_s_logical_not, __pyx_k_logical_not, sizeof(__pyx_k_logical_not), 0, 0, 1, 1},
  {&__pyx_n_s_logical_or, __pyx_k_logical_or, sizeof(__pyx_k_logical_or), 0, 0, 1, 1},
  {&__pyx_n_s_ma, __pyx_k_ma, sizeof(__pyx_k_ma), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_mask, __pyx_k_mask, sizeof(__pyx_k_mask), 0, 0, 1, 1},
  {&__pyx_n_s_mask_data, __pyx_k_mask_data, sizeof(__pyx_k_mask_data), 0, 0, 1, 1},
  {&__pyx_n_s_mean, __pyx_k_mean, sizeof(__pyx_k_mean), 0, 0, 1, 1},
  {&__pyx_n_s_metaclass, __pyx_k_metaclass, sizeof(__pyx_k_metaclass), 0, 0, 1, 1},
  {&__pyx_n_s_min, __pyx_k_min, sizeof(__pyx_k_min), 0, 0, 1, 1},
  {&__pyx_n_s_mode, __pyx_k_mode, sizeof(__pyx_k_mode), 0, 0, 1, 1},
  {&__pyx_n_s_module, __pyx_k_module, sizeof(__pyx_k_module), 0, 0, 1, 1},
  {&__pyx_n_s_name, __pyx_k_name, sizeof(__pyx_k_name), 0, 0, 1, 1},
  {&__pyx_n_s_name_2, __pyx_k_name_2, sizeof(__pyx_k_name_2), 0, 0, 1, 1},
  {&__pyx_n_s_netCDF4, __pyx_k_netCDF4, sizeof(__pyx_k_netCDF4), 0, 0, 1, 1},
  {&__pyx_n_s_nopython, __pyx_k_nopython, sizeof(__pyx_k_nopython), 0, 0, 1, 1},
  {&__pyx_n_s_num2date, __pyx_k_num2date, sizeof(__pyx_k_num2date), 0, 0, 1, 1},
  {&__pyx_n_s_numba, __pyx_k_numba, sizeof(__pyx_k_numba), 0, 0, 1, 1},
  {&__pyx_n_s_numexpr, __pyx_k_numexpr, sizeof(__pyx_k_numexpr), 0, 0, 1, 1},
  {&__pyx_n_s_numpy, __pyx_k_numpy, sizeof(__pyx_k_numpy), 0, 0, 1, 1},
  {&__pyx_n_s_numpy_ma, __pyx_k_numpy_ma, sizeof(__pyx_k_numpy_ma), 0, 0, 1, 1},
  {&__pyx_n_s_object, __pyx_k_object, sizeof(__pyx_k_object), 0, 0, 1, 1},
  {&__pyx_n_s_open, __pyx_k_open, sizeof(__pyx_k_open), 0, 0, 1, 1},
  {&__pyx_n_s_output2file, __pyx_k_output2file, sizeof(__pyx_k_output2file), 0, 0, 1, 1},
  {&__pyx_n_s_p, __pyx_k_p, sizeof(__pyx_k_p), 0, 0, 1, 1},
  {&__pyx_n_s_path, __pyx_k_path, sizeof(__pyx_k_path), 0, 0, 1, 1},
  {&__pyx_n_s_point, __pyx_k_point, sizeof(__pyx_k_point), 0, 0, 1, 1},
  {&__pyx_n_s_pp, __pyx_k_pp, sizeof(__pyx_k_pp), 0, 0, 1, 1},
  {&__pyx_n_s_pprint, __pyx_k_pprint, sizeof(__pyx_k_pprint), 0, 0, 1, 1},
  {&__pyx_n_s_prepare, __pyx_k_prepare, sizeof(__pyx_k_prepare), 0, 0, 1, 1},
  {&__pyx_n_s_print, __pyx_k_print, sizeof(__pyx_k_print), 0, 0, 1, 1},
  {&__pyx_n_s_qualname, __pyx_k_qualname, sizeof(__pyx_k_qualname), 0, 0, 1, 1},
  {&__pyx_n_s_r, __pyx_k_r, sizeof(__pyx_k_r), 0, 0, 1, 1},
  {&__pyx_n_s_range, __pyx_k_range, sizeof(__pyx_k_range), 0, 0, 1, 1},
  {&__pyx_n_s_reduce, __pyx_k_reduce, sizeof(__pyx_k_reduce), 0, 0, 1, 1},
  {&__pyx_n_s_ref_var_names, __pyx_k_ref_var_names, sizeof(__pyx_k_ref_var_names), 0, 0, 1, 1},
  {&__pyx_n_s_ref_var_suffix, __pyx_k_ref_var_suffix, sizeof(__pyx_k_ref_var_suffix), 0, 0, 1, 1},
  {&__pyx_n_s_return, __pyx_k_return, sizeof(__pyx_k_return), 0, 0, 1, 1},
  {&__pyx_n_s_round, __pyx_k_round, sizeof(__pyx_k_round), 0, 0, 1, 1},
  {&__pyx_n_s_s, __pyx_k_s, sizeof(__pyx_k_s), 0, 0, 1, 1},
  {&__pyx_kp_s_s_d_d, __pyx_k_s_d_d, sizeof(__pyx_k_s_d_d), 0, 0, 1, 0},
  {&__pyx_n_s_scale_factor, __pyx_k_scale_factor, sizeof(__pyx_k_scale_factor), 0, 0, 1, 1},
  {&__pyx_n_s_scan_start_time, __pyx_k_scan_start_time, sizeof(__pyx_k_scan_start_time), 0, 0, 1, 1},
  {&__pyx_n_s_self, __pyx_k_self, sizeof(__pyx_k_self), 0, 0, 1, 1},
  {&__pyx_n_s_set_auto_scale, __pyx_k_set_auto_scale, sizeof(__pyx_k_set_auto_scale), 0, 0, 1, 1},
  {&__pyx_n_s_shape, __pyx_k_shape, sizeof(__pyx_k_shape), 0, 0, 1, 1},
  {&__pyx_n_s_size_y, __pyx_k_size_y, sizeof(__pyx_k_size_y), 0, 0, 1, 1},
  {&__pyx_n_s_size_z, __pyx_k_size_z, sizeof(__pyx_k_size_z), 0, 0, 1, 1},
  {&__pyx_n_s_sortedcontainers, __pyx_k_sortedcontainers, sizeof(__pyx_k_sortedcontainers), 0, 0, 1, 1},
  {&__pyx_kp_s_start_output, __pyx_k_start_output, sizeof(__pyx_k_start_output), 0, 0, 1, 0},
  {&__pyx_n_s_staticmethod, __pyx_k_staticmethod, sizeof(__pyx_k_staticmethod), 0, 0, 1, 1},
  {&__pyx_n_s_t, __pyx_k_t, sizeof(__pyx_k_t), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_time, __pyx_k_time, sizeof(__pyx_k_time), 0, 0, 1, 1},
  {&__pyx_n_s_time_data_dict, __pyx_k_time_data_dict, sizeof(__pyx_k_time_data_dict), 0, 0, 1, 1},
  {&__pyx_n_s_time_var, __pyx_k_time_var, sizeof(__pyx_k_time_var), 0, 0, 1, 1},
  {&__pyx_n_s_time_var_dump, __pyx_k_time_var_dump, sizeof(__pyx_k_time_var_dump), 0, 0, 1, 1},
  {&__pyx_n_s_time_var_hi, __pyx_k_time_var_hi, sizeof(__pyx_k_time_var_hi), 0, 0, 1, 1},
  {&__pyx_n_s_timedelta, __pyx_k_timedelta, sizeof(__pyx_k_timedelta), 0, 0, 1, 1},
  {&__pyx_n_s_total_mask, __pyx_k_total_mask, sizeof(__pyx_k_total_mask), 0, 0, 1, 1},
  {&__pyx_n_s_typing, __pyx_k_typing, sizeof(__pyx_k_typing), 0, 0, 1, 1},
  {&__pyx_n_s_u, __pyx_k_u, sizeof(__pyx_k_u), 0, 0, 1, 1},
  {&__pyx_n_s_v, __pyx_k_v, sizeof(__pyx_k_v), 0, 0, 1, 1},
  {&__pyx_n_s_v1, __pyx_k_v1, sizeof(__pyx_k_v1), 0, 0, 1, 1},
  {&__pyx_n_s_v_2, __pyx_k_v_2, sizeof(__pyx_k_v_2), 0, 0, 1, 1},
  {&__pyx_n_s_value, __pyx_k_value, sizeof(__pyx_k_value), 0, 0, 1, 1},
  {&__pyx_n_s_values, __pyx_k_values, sizeof(__pyx_k_values), 0, 0, 1, 1},
  {&__pyx_n_s_var, __pyx_k_var, sizeof(__pyx_k_var), 0, 0, 1, 1},
  {&__pyx_n_s_var_dump, __pyx_k_var_dump, sizeof(__pyx_k_var_dump), 0, 0, 1, 1},
  {&__pyx_n_s_var_hi, __pyx_k_var_hi, sizeof(__pyx_k_var_hi), 0, 0, 1, 1},
  {&__pyx_n_s_var_names, __pyx_k_var_names, sizeof(__pyx_k_var_names), 0, 0, 1, 1},
  {&__pyx_n_s_var_suffix, __pyx_k_var_suffix, sizeof(__pyx_k_var_suffix), 0, 0, 1, 1},
  {&__pyx_n_s_variable, __pyx_k_variable, sizeof(__pyx_k_variable), 0, 0, 1, 1},
  {&__pyx_n_s_variables, __pyx_k_variables, sizeof(__pyx_k_variables), 0, 0, 1, 1},
  {&__pyx_n_s_vcp_mode, __pyx_k_vcp_mode, sizeof(__pyx_k_vcp_mode), 0, 0, 1, 1},
  {&__pyx_n_s_vel_var_names, __pyx_k_vel_var_names, sizeof(__pyx_k_vel_var_names), 0, 0, 1, 1},
  {&__pyx_n_s_vel_var_suffix, __pyx_k_vel_var_suffix, sizeof(__pyx_k_vel_var_suffix), 0, 0, 1, 1},
  {&__pyx_n_s_view, __pyx_k_view, sizeof(__pyx_k_view), 0, 0, 1, 1},
  {&__pyx_n_s_w, __pyx_k_w, sizeof(__pyx_k_w), 0, 0, 1, 1},
  {&__pyx_n_s_warning, __pyx_k_warning, sizeof(__pyx_k_warning), 0, 0, 1, 1},
  {&__pyx_n_s_write, __pyx_k_write, sizeof(__pyx_k_write), 0, 0, 1, 1},
  {&__pyx_n_s_zeros, __pyx_k_zeros, sizeof(__pyx_k_zeros), 0, 0, 1, 1},
  {&__pyx_n_s_zip, __pyx_k_zip, sizeof(__pyx_k_zip), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_object = __Pyx_GetBuiltinName(__pyx_n_s_object); if (!__pyx_builtin_object) __PYX_ERR(0, 90, __pyx_L1_error)
  __pyx_builtin_staticmethod = __Pyx_GetBuiltinName(__pyx_n_s_staticmethod); if (!__pyx_builtin_staticmethod) __PYX_ERR(0, 194, __pyx_L1_error)
  __pyx_builtin_round = __Pyx_GetBuiltinName(__pyx_n_s_round); if (!__pyx_builtin_round) __PYX_ERR(0, 46, __pyx_L1_error)
  __pyx_builtin_range = __Pyx_GetBuiltinName(__pyx_n_s_range); if (!__pyx_builtin_range) __PYX_ERR(0, 50, __pyx_L1_error)
  __pyx_builtin_KeyError = __Pyx_GetBuiltinName(__pyx_n_s_KeyError); if (!__pyx_builtin_KeyError) __PYX_ERR(0, 179, __pyx_L1_error)
  __pyx_builtin_zip = __Pyx_GetBuiltinName(__pyx_n_s_zip); if (!__pyx_builtin_zip) __PYX_ERR(0, 216, __pyx_L1_error)
  __pyx_builtin_open = __Pyx_GetBuiltinName(__pyx_n_s_open); if (!__pyx_builtin_open) __PYX_ERR(0, 286, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "data_handler_v2.py":39
 * @jit(nopython=True)
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]             # <<<<<<<<<<<<<<
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 */
  __pyx_slice_ = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice_)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice_);
  __Pyx_GIVEREF(__pyx_slice_);

  /* "data_handler_v2.py":42
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 *     ad = a[1:] - a[:-1]             # <<<<<<<<<<<<<<
 *     # This is a slow way to determine if it is truly high resolution.
 *     # Well, maybe not necessary as we patched netcdf jar.
 */
  __pyx_slice__2 = PySlice_New(__pyx_int_1, Py_None, Py_None); if (unlikely(!__pyx_slice__2)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__2);
  __Pyx_GIVEREF(__pyx_slice__2);
  __pyx_slice__3 = PySlice_New(Py_None, __pyx_int_neg_1, Py_None); if (unlikely(!__pyx_slice__3)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__3);
  __Pyx_GIVEREF(__pyx_slice__3);

  /* "data_handler_v2.py":52
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 */
  __pyx_slice__4 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__4)) __PYX_ERR(0, 52, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__4);
  __Pyx_GIVEREF(__pyx_slice__4);

  /* "data_handler_v2.py":53
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *     else:
 *         for k in range(r.shape[0]):
 */
  __pyx_slice__5 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__5)) __PYX_ERR(0, 53, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__5);
  __Pyx_GIVEREF(__pyx_slice__5);

  /* "data_handler_v2.py":57
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *     pass
 * 
 */
  __pyx_slice__6 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__6)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__6);
  __Pyx_GIVEREF(__pyx_slice__6);

  /* "data_handler_v2.py":62
 * 
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]             # <<<<<<<<<<<<<<
 *     a = azimuth_array[:size_y]
 *     # Determine azimuthal resolution
 */
  __pyx_slice__7 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__7)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__7);
  __Pyx_GIVEREF(__pyx_slice__7);

  /* "data_handler_v2.py":75
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
 *     else:
 */
  __pyx_slice__8 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__8)) __PYX_ERR(0, 75, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__8);
  __Pyx_GIVEREF(__pyx_slice__8);

  /* "data_handler_v2.py":76
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 *             dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 *     else:
 *         for k in range(r.shape[0]):
 */
  __pyx_slice__9 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__9)) __PYX_ERR(0, 76, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__9);
  __Pyx_GIVEREF(__pyx_slice__9);

  /* "data_handler_v2.py":80
 *         for k in range(r.shape[0]):
 *             az_index = int(a[k] * 2)
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]             # <<<<<<<<<<<<<<
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 */
  __pyx_slice__10 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__10)) __PYX_ERR(0, 80, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__10);
  __Pyx_GIVEREF(__pyx_slice__10);

  /* "data_handler_v2.py":86
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 *     except:
 *         logging.warning("Failed to run JIT functions")             # <<<<<<<<<<<<<<
 *         fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 * 
 */
  __pyx_tuple__11 = PyTuple_Pack(1, __pyx_kp_s_Failed_to_run_JIT_functions); if (unlikely(!__pyx_tuple__11)) __PYX_ERR(0, 86, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__11);
  __Pyx_GIVEREF(__pyx_tuple__11);

  /* "data_handler_v2.py":137
 *         # Fill data
 *         for p in self.data_dict.values():
 *             p.fill(-99990.0)             # <<<<<<<<<<<<<<
 * 
 *         self.extended_data_dict = {
 */
  __pyx_tuple__12 = PyTuple_Pack(1, __pyx_float_neg_99990_0); if (unlikely(!__pyx_tuple__12)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__12);
  __Pyx_GIVEREF(__pyx_tuple__12);

  /* "data_handler_v2.py":171
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return
 *         time_var_dump = ds.variables[time_var][:]             # <<<<<<<<<<<<<<
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
 */
  __pyx_slice__14 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__14)) __PYX_ERR(0, 171, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__14);
  __Pyx_GIVEREF(__pyx_slice__14);

  /* "data_handler_v2.py":173
 *         time_var_dump = ds.variables[time_var][:]
 *         var_dump = self.__fix_variable__(self.dataset.variables[var])
 *         assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data             # <<<<<<<<<<<<<<
 *         scan_start_time = time_var_dump.min(axis=1)
 *         for t in range(scan_start_time.shape[0]):
 */
  __pyx_slice__15 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__15)) __PYX_ERR(0, 173, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__15);
  __Pyx_GIVEREF(__pyx_slice__15);
  __pyx_tuple__16 = PyTuple_Pack(2, __pyx_slice__15, __pyx_int_0); if (unlikely(!__pyx_tuple__16)) __PYX_ERR(0, 173, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__16);
  __Pyx_GIVEREF(__pyx_tuple__16);

  /* "data_handler_v2.py":198
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 *             v.set_auto_scale(False)             # <<<<<<<<<<<<<<
 *             # Dump out
 *             _v = v[:]
 */
  __pyx_tuple__17 = PyTuple_Pack(1, Py_False); if (unlikely(!__pyx_tuple__17)) __PYX_ERR(0, 198, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__17);
  __Pyx_GIVEREF(__pyx_tuple__17);

  /* "data_handler_v2.py":200
 *             v.set_auto_scale(False)
 *             # Dump out
 *             _v = v[:]             # <<<<<<<<<<<<<<
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             logging.info("Fix unsigned variable:" + v.name)
 */
  __pyx_slice__18 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__18)) __PYX_ERR(0, 200, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__18);
  __Pyx_GIVEREF(__pyx_slice__18);

  /* "data_handler_v2.py":205
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 *         else:
 *             return v[:]             # <<<<<<<<<<<<<<
 * 
 *     def first_pass(self):
 */
  __pyx_slice__19 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__19)) __PYX_ERR(0, 205, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__19);
  __Pyx_GIVEREF(__pyx_slice__19);

  /* "data_handler_v2.py":230
 *                     self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CS")             # <<<<<<<<<<<<<<
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()
 */
  __pyx_tuple__20 = PyTuple_Pack(1, __pyx_kp_s_Failed_to_run_JITed_fill_data_fu); if (unlikely(!__pyx_tuple__20)) __PYX_ERR(0, 230, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__20);
  __Pyx_GIVEREF(__pyx_tuple__20);

  /* "data_handler_v2.py":249
 *                     self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: CD")             # <<<<<<<<<<<<<<
 *                     mode = "_HI" if 'elevationV_HI' in i else ""
 *                     elevation = i["elevationV" + mode].mean()
 */
  __pyx_tuple__21 = PyTuple_Pack(1, __pyx_kp_s_Failed_to_run_JITed_fill_data_fu_2); if (unlikely(!__pyx_tuple__21)) __PYX_ERR(0, 249, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__21);
  __Pyx_GIVEREF(__pyx_tuple__21);

  /* "data_handler_v2.py":264
 *                     self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
 *                 except:
 *                     logging.warning("Failed to run JITed fill_data function: Mixed")             # <<<<<<<<<<<<<<
 *                     mode = "_HI" if 'elevationR_HI' in i else ""
 *                     elevation = i["elevationR" + mode].mean()
 */
  __pyx_tuple__22 = PyTuple_Pack(1, __pyx_kp_s_Failed_to_run_JITed_fill_data_fu_3); if (unlikely(!__pyx_tuple__22)) __PYX_ERR(0, 264, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__22);
  __Pyx_GIVEREF(__pyx_tuple__22);

  /* "data_handler_v2.py":289
 *         for point, attr in coordinate.items():
 *             f.write(str(point))
 *             f.write(' ')             # <<<<<<<<<<<<<<
 *             for variable, value in attr.items():
 *                 f.write(variable)
 */
  __pyx_tuple__24 = PyTuple_Pack(1, __pyx_kp_s__23); if (unlikely(!__pyx_tuple__24)) __PYX_ERR(0, 289, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__24);
  __Pyx_GIVEREF(__pyx_tuple__24);

  /* "data_handler_v2.py":292
 *             for variable, value in attr.items():
 *                 f.write(variable)
 *                 f.write(':')             # <<<<<<<<<<<<<<
 *                 f.write(str(value))
 *                 f.write(' ')
 */
  __pyx_tuple__26 = PyTuple_Pack(1, __pyx_kp_s__25); if (unlikely(!__pyx_tuple__26)) __PYX_ERR(0, 292, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__26);
  __Pyx_GIVEREF(__pyx_tuple__26);

  /* "data_handler_v2.py":294
 *                 f.write(':')
 *                 f.write(str(value))
 *                 f.write(' ')             # <<<<<<<<<<<<<<
 *             f.write('\n')
 *         f.close()
 */
  __pyx_tuple__27 = PyTuple_Pack(1, __pyx_kp_s__23); if (unlikely(!__pyx_tuple__27)) __PYX_ERR(0, 294, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__27);
  __Pyx_GIVEREF(__pyx_tuple__27);

  /* "data_handler_v2.py":295
 *                 f.write(str(value))
 *                 f.write(' ')
 *             f.write('\n')             # <<<<<<<<<<<<<<
 *         f.close()
 *         print("finish output")
 */
  __pyx_tuple__29 = PyTuple_Pack(1, __pyx_kp_s__28); if (unlikely(!__pyx_tuple__29)) __PYX_ERR(0, 295, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__29);
  __Pyx_GIVEREF(__pyx_tuple__29);

  /* "data_handler_v2.py":30
 * 
 * @jit(nopython=True)
 * def find_elevation_index(vcp_mode, e):             # <<<<<<<<<<<<<<
 *     j = 0
 *     for i in vcp_mode:
 */
  __pyx_tuple__30 = PyTuple_Pack(4, __pyx_n_s_vcp_mode, __pyx_n_s_e, __pyx_n_s_j, __pyx_n_s_i); if (unlikely(!__pyx_tuple__30)) __PYX_ERR(0, 30, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__30);
  __Pyx_GIVEREF(__pyx_tuple__30);
  __pyx_codeobj__31 = (PyObject*)__Pyx_PyCode_New(2, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__30, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_find_elevation_index, 30, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__31)) __PYX_ERR(0, 30, __pyx_L1_error)

  /* "data_handler_v2.py":38
 * 
 * @jit(nopython=True)
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */
  __pyx_tuple__32 = PyTuple_Pack(12, __pyx_n_s_gate_array, __pyx_n_s_azimuth_array, __pyx_n_s_dump_array, __pyx_n_s_elevation_index, __pyx_n_s_size_y, __pyx_n_s_size_z, __pyx_n_s_r, __pyx_n_s_a, __pyx_n_s_ad, __pyx_n_s_az_downscale, __pyx_n_s_k, __pyx_n_s_az_index); if (unlikely(!__pyx_tuple__32)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__32);
  __Pyx_GIVEREF(__pyx_tuple__32);
  __pyx_codeobj__33 = (PyObject*)__Pyx_PyCode_New(6, 0, 12, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__32, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fill_data_jit, 38, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__33)) __PYX_ERR(0, 38, __pyx_L1_error)

  /* "data_handler_v2.py":61
 * 
 * 
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */
  __pyx_tuple__34 = PyTuple_Pack(12, __pyx_n_s_gate_array, __pyx_n_s_azimuth_array, __pyx_n_s_dump_array, __pyx_n_s_elevation_index, __pyx_n_s_size_y, __pyx_n_s_size_z, __pyx_n_s_r, __pyx_n_s_a, __pyx_n_s_ad, __pyx_n_s_az_downscale, __pyx_n_s_k, __pyx_n_s_az_index); if (unlikely(!__pyx_tuple__34)) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__34);
  __Pyx_GIVEREF(__pyx_tuple__34);
  __pyx_codeobj__35 = (PyObject*)__Pyx_PyCode_New(6, 0, 12, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__34, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fill_data_nojit, 61, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__35)) __PYX_ERR(0, 61, __pyx_L1_error)

  /* "data_handler_v2.py":82
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     try:
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 */
  __pyx_tuple__36 = PyTuple_Pack(6, __pyx_n_s_gate_array, __pyx_n_s_azimuth_array, __pyx_n_s_dump_array, __pyx_n_s_elevation_index, __pyx_n_s_size_y, __pyx_n_s_size_z); if (unlikely(!__pyx_tuple__36)) __PYX_ERR(0, 82, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__36);
  __Pyx_GIVEREF(__pyx_tuple__36);
  __pyx_codeobj__37 = (PyObject*)__Pyx_PyCode_New(6, 0, 6, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__36, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fill_data_function, 82, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__37)) __PYX_ERR(0, 82, __pyx_L1_error)

  /* "data_handler_v2.py":93
 * 
 *     VcpTable = {
 *         11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),             # <<<<<<<<<<<<<<
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 */
  __pyx_tuple__38 = PyTuple_Pack(14, __pyx_float_0_5, __pyx_float_1_5, __pyx_float_2_4, __pyx_float_3_4, __pyx_float_4_3, __pyx_float_5_3, __pyx_float_6_2, __pyx_float_7_5, __pyx_float_8_7, __pyx_float_10_0, __pyx_float_12_0, __pyx_float_14_0, __pyx_float_16_7, __pyx_float_19_5); if (unlikely(!__pyx_tuple__38)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__38);
  __Pyx_GIVEREF(__pyx_tuple__38);

  /* "data_handler_v2.py":94
 *     VcpTable = {
 *         11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),             # <<<<<<<<<<<<<<
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 */
  __pyx_tuple__39 = PyTuple_Pack(14, __pyx_float_0_5, __pyx_float_1_5, __pyx_float_2_4, __pyx_float_3_4, __pyx_float_4_3, __pyx_float_5_3, __pyx_float_6_2, __pyx_float_7_5, __pyx_float_8_7, __pyx_float_10_0, __pyx_float_12_0, __pyx_float_14_0, __pyx_float_16_7, __pyx_float_19_5); if (unlikely(!__pyx_tuple__39)) __PYX_ERR(0, 94, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__39);
  __Pyx_GIVEREF(__pyx_tuple__39);

  /* "data_handler_v2.py":95
 *         11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),             # <<<<<<<<<<<<<<
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 */
  __pyx_tuple__40 = PyTuple_Pack(14, __pyx_float_0_5, __pyx_float_0_9, __pyx_float_1_3, __pyx_float_1_8, __pyx_float_2_4, __pyx_float_3_1, __pyx_float_4_0, __pyx_float_5_1, __pyx_float_6_4, __pyx_float_8_0, __pyx_float_10_0, __pyx_float_12_5, __pyx_float_15_6, __pyx_float_19_5); if (unlikely(!__pyx_tuple__40)) __PYX_ERR(0, 95, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__40);
  __Pyx_GIVEREF(__pyx_tuple__40);

  /* "data_handler_v2.py":96
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),             # <<<<<<<<<<<<<<
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 */
  __pyx_tuple__41 = PyTuple_Pack(14, __pyx_float_0_5, __pyx_float_0_9, __pyx_float_1_3, __pyx_float_1_8, __pyx_float_2_4, __pyx_float_3_1, __pyx_float_4_0, __pyx_float_5_1, __pyx_float_6_4, __pyx_float_8_0, __pyx_float_10_0, __pyx_float_12_5, __pyx_float_15_6, __pyx_float_19_5); if (unlikely(!__pyx_tuple__41)) __PYX_ERR(0, 96, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__41);
  __Pyx_GIVEREF(__pyx_tuple__41);

  /* "data_handler_v2.py":97
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),             # <<<<<<<<<<<<<<
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)
 */
  __pyx_tuple__42 = PyTuple_Pack(9, __pyx_float_0_5, __pyx_float_1_5, __pyx_float_2_4, __pyx_float_3_4, __pyx_float_4_3, __pyx_float_6_0, __pyx_float_9_9, __pyx_float_14_6, __pyx_float_19_5); if (unlikely(!__pyx_tuple__42)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__42);
  __Pyx_GIVEREF(__pyx_tuple__42);

  /* "data_handler_v2.py":98
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),             # <<<<<<<<<<<<<<
 *         221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)
 *     }
 */
  __pyx_tuple__43 = PyTuple_Pack(9, __pyx_float_0_5, __pyx_float_1_5, __pyx_float_2_4, __pyx_float_3_4, __pyx_float_4_3, __pyx_float_6_0, __pyx_float_9_9, __pyx_float_14_6, __pyx_float_19_5); if (unlikely(!__pyx_tuple__43)) __PYX_ERR(0, 98, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__43);
  __Pyx_GIVEREF(__pyx_tuple__43);

  /* "data_handler_v2.py":99
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)             # <<<<<<<<<<<<<<
 *     }
 * 
 */
  __pyx_tuple__44 = PyTuple_Pack(9, __pyx_float_0_5, __pyx_float_1_5, __pyx_float_2_4, __pyx_float_3_4, __pyx_float_4_3, __pyx_float_6_0, __pyx_float_9_9, __pyx_float_14_6, __pyx_float_19_5); if (unlikely(!__pyx_tuple__44)) __PYX_ERR(0, 99, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__44);
  __Pyx_GIVEREF(__pyx_tuple__44);

  /* "data_handler_v2.py":112
 *     vel_var_suffix = list("VV")
 * 
 *     def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */
  __pyx_tuple__45 = PyTuple_Pack(5, __pyx_n_s_self, __pyx_n_s_dataset, __pyx_n_s_legacy, __pyx_n_s_dualpol, __pyx_n_s_p); if (unlikely(!__pyx_tuple__45)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__45);
  __Pyx_GIVEREF(__pyx_tuple__45);
  __pyx_codeobj__46 = (PyObject*)__Pyx_PyCode_New(4, 0, 5, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__45, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_init, 112, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__46)) __PYX_ERR(0, 112, __pyx_L1_error)
  __pyx_tuple__47 = PyTuple_Pack(2, ((PyObject *)Py_False), ((PyObject *)Py_True)); if (unlikely(!__pyx_tuple__47)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__47);
  __Pyx_GIVEREF(__pyx_tuple__47);

  /* "data_handler_v2.py":163
 *         self.fill_data(first_pass=True)
 * 
 *     def is_filled(self):             # <<<<<<<<<<<<<<
 *         # All filled means all is True
 *         return numpy.all(numpy.logical_not(self.filling_table))  # type: bool
 */
  __pyx_tuple__48 = PyTuple_Pack(1, __pyx_n_s_self); if (unlikely(!__pyx_tuple__48)) __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__48);
  __Pyx_GIVEREF(__pyx_tuple__48);
  __pyx_codeobj__49 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__48, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_is_filled, 163, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__49)) __PYX_ERR(0, 163, __pyx_L1_error)

  /* "data_handler_v2.py":168
 * 
 *     # Dump helper function
 *     def __dump(self, var, time_var, dump_dict):             # <<<<<<<<<<<<<<
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return
 */
  __pyx_tuple__50 = PyTuple_Pack(8, __pyx_n_s_self, __pyx_n_s_var, __pyx_n_s_time_var, __pyx_n_s_dump_dict, __pyx_n_s_time_var_dump, __pyx_n_s_var_dump, __pyx_n_s_scan_start_time, __pyx_n_s_t); if (unlikely(!__pyx_tuple__50)) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__50);
  __Pyx_GIVEREF(__pyx_tuple__50);
  __pyx_codeobj__51 = (PyObject*)__Pyx_PyCode_New(4, 0, 8, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__50, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_dump, 168, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__51)) __PYX_ERR(0, 168, __pyx_L1_error)

  /* "data_handler_v2.py":182
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})
 * 
 *     def dump_data_by_time(self, dump_var_names, dump_target):             # <<<<<<<<<<<<<<
 *         assert len(dump_var_names) == len(self.all_var_suffix)
 *         for i in range(len(dump_var_names)):
 */
  __pyx_tuple__52 = PyTuple_Pack(8, __pyx_n_s_self, __pyx_n_s_dump_var_names, __pyx_n_s_dump_target, __pyx_n_s_i, __pyx_n_s_var, __pyx_n_s_time_var, __pyx_n_s_var_hi, __pyx_n_s_time_var_hi); if (unlikely(!__pyx_tuple__52)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__52);
  __Pyx_GIVEREF(__pyx_tuple__52);
  __pyx_codeobj__53 = (PyObject*)__Pyx_PyCode_New(3, 0, 8, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__52, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_dump_data_by_time, 182, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__53)) __PYX_ERR(0, 182, __pyx_L1_error)

  /* "data_handler_v2.py":195
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */
  __pyx_tuple__54 = PyTuple_Pack(3, __pyx_n_s_v, __pyx_n_s_v_2, __pyx_n_s_v1); if (unlikely(!__pyx_tuple__54)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__54);
  __Pyx_GIVEREF(__pyx_tuple__54);
  __pyx_codeobj__55 = (PyObject*)__Pyx_PyCode_New(1, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__54, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fix_variable, 195, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__55)) __PYX_ERR(0, 195, __pyx_L1_error)

  /* "data_handler_v2.py":207
 *             return v[:]
 * 
 *     def first_pass(self):             # <<<<<<<<<<<<<<
 *         pass
 * 
 */
  __pyx_tuple__56 = PyTuple_Pack(1, __pyx_n_s_self); if (unlikely(!__pyx_tuple__56)) __PYX_ERR(0, 207, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__56);
  __Pyx_GIVEREF(__pyx_tuple__56);
  __pyx_codeobj__57 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__56, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_first_pass, 207, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__57)) __PYX_ERR(0, 207, __pyx_L1_error)

  /* "data_handler_v2.py":211
 * 
 *     @jit
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):             # <<<<<<<<<<<<<<
 *         mode = "_HI" if id_var + "_HI" in i else ""
 *         elevation = i[id_var + mode].mean()
 */
  __pyx_tuple__58 = PyTuple_Pack(10, __pyx_n_s_self, __pyx_n_s_i, __pyx_n_s_id_var, __pyx_n_s_var_names, __pyx_n_s_var_suffix, __pyx_n_s_mode, __pyx_n_s_elevation, __pyx_n_s_elevation_index, __pyx_n_s_j, __pyx_n_s_s); if (unlikely(!__pyx_tuple__58)) __PYX_ERR(0, 211, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__58);
  __Pyx_GIVEREF(__pyx_tuple__58);
  __pyx_codeobj__59 = (PyObject*)__Pyx_PyCode_New(5, 0, 10, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__58, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fill_data_internal, 211, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__59)) __PYX_ERR(0, 211, __pyx_L1_error)

  /* "data_handler_v2.py":221
 *                                self.beams_count, self.gates_count)
 * 
 *     def fill_data(self, *args, **kwargs):             # <<<<<<<<<<<<<<
 * 
 *         for i in self.time_data_dict.values():
 */
  __pyx_tuple__60 = PyTuple_Pack(9, __pyx_n_s_self, __pyx_n_s_args, __pyx_n_s_kwargs, __pyx_n_s_i, __pyx_n_s_mode, __pyx_n_s_elevation, __pyx_n_s_elevation_index, __pyx_n_s_j, __pyx_n_s_s); if (unlikely(!__pyx_tuple__60)) __PYX_ERR(0, 221, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__60);
  __Pyx_GIVEREF(__pyx_tuple__60);
  __pyx_codeobj__61 = (PyObject*)__Pyx_PyCode_New(1, 0, 9, 0, CO_VARARGS|CO_VARKEYWORDS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__60, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fill_data, 221, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__61)) __PYX_ERR(0, 221, __pyx_L1_error)

  /* "data_handler_v2.py":276
 *         pass
 * 
 *     def mask_data(self):             # <<<<<<<<<<<<<<
 *         # Create a mask to remove all invalid data from reflectivity scan.
 *         total_mask = reduce(numpy.ma.logical_or,
 */
  __pyx_tuple__62 = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_total_mask, __pyx_n_s_v, __pyx_n_s_k); if (unlikely(!__pyx_tuple__62)) __PYX_ERR(0, 276, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__62);
  __Pyx_GIVEREF(__pyx_tuple__62);
  __pyx_codeobj__63 = (PyObject*)__Pyx_PyCode_New(1, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__62, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_mask_data, 276, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__63)) __PYX_ERR(0, 276, __pyx_L1_error)

  /* "data_handler_v2.py":284
 *             v.mask = total_mask
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */
  __pyx_tuple__64 = PyTuple_Pack(8, __pyx_n_s_self, __pyx_n_s_path, __pyx_n_s_coordinate, __pyx_n_s_f, __pyx_n_s_point, __pyx_n_s_attr, __pyx_n_s_variable, __pyx_n_s_value); if (unlikely(!__pyx_tuple__64)) __PYX_ERR(0, 284, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__64);
  __Pyx_GIVEREF(__pyx_tuple__64);
  __pyx_codeobj__65 = (PyObject*)__Pyx_PyCode_New(3, 0, 8, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__64, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_output2file, 284, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__65)) __PYX_ERR(0, 284, __pyx_L1_error)

  /* "data_handler_v2.py":301
 * 
 * if __name__ == "__main__":
 *     ds = Dataset('/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc', 'r')             # <<<<<<<<<<<<<<
 *     R = RadarNetcdf(ds)
 */
  __pyx_tuple__66 = PyTuple_Pack(2, __pyx_kp_s_home_sugar_Developer_Cloud2016_2, __pyx_n_s_r); if (unlikely(!__pyx_tuple__66)) __PYX_ERR(0, 301, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__66);
  __Pyx_GIVEREF(__pyx_tuple__66);
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  __pyx_float_0_2 = PyFloat_FromDouble(0.2); if (unlikely(!__pyx_float_0_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_5 = PyFloat_FromDouble(0.5); if (unlikely(!__pyx_float_0_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_7 = PyFloat_FromDouble(0.7); if (unlikely(!__pyx_float_0_7)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_9 = PyFloat_FromDouble(0.9); if (unlikely(!__pyx_float_0_9)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_1_3 = PyFloat_FromDouble(1.3); if (unlikely(!__pyx_float_1_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_1_5 = PyFloat_FromDouble(1.5); if (unlikely(!__pyx_float_1_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_1_8 = PyFloat_FromDouble(1.8); if (unlikely(!__pyx_float_1_8)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_2_4 = PyFloat_FromDouble(2.4); if (unlikely(!__pyx_float_2_4)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_3_1 = PyFloat_FromDouble(3.1); if (unlikely(!__pyx_float_3_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_3_4 = PyFloat_FromDouble(3.4); if (unlikely(!__pyx_float_3_4)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_4_0 = PyFloat_FromDouble(4.0); if (unlikely(!__pyx_float_4_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_4_3 = PyFloat_FromDouble(4.3); if (unlikely(!__pyx_float_4_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_5_1 = PyFloat_FromDouble(5.1); if (unlikely(!__pyx_float_5_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_5_3 = PyFloat_FromDouble(5.3); if (unlikely(!__pyx_float_5_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_6_0 = PyFloat_FromDouble(6.0); if (unlikely(!__pyx_float_6_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_6_2 = PyFloat_FromDouble(6.2); if (unlikely(!__pyx_float_6_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_6_4 = PyFloat_FromDouble(6.4); if (unlikely(!__pyx_float_6_4)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_7_5 = PyFloat_FromDouble(7.5); if (unlikely(!__pyx_float_7_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_8_0 = PyFloat_FromDouble(8.0); if (unlikely(!__pyx_float_8_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_8_7 = PyFloat_FromDouble(8.7); if (unlikely(!__pyx_float_8_7)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_9_9 = PyFloat_FromDouble(9.9); if (unlikely(!__pyx_float_9_9)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_10_0 = PyFloat_FromDouble(10.0); if (unlikely(!__pyx_float_10_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_12_0 = PyFloat_FromDouble(12.0); if (unlikely(!__pyx_float_12_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_12_5 = PyFloat_FromDouble(12.5); if (unlikely(!__pyx_float_12_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_14_0 = PyFloat_FromDouble(14.0); if (unlikely(!__pyx_float_14_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_14_6 = PyFloat_FromDouble(14.6); if (unlikely(!__pyx_float_14_6)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_15_6 = PyFloat_FromDouble(15.6); if (unlikely(!__pyx_float_15_6)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_16_7 = PyFloat_FromDouble(16.7); if (unlikely(!__pyx_float_16_7)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_19_5 = PyFloat_FromDouble(19.5); if (unlikely(!__pyx_float_19_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_neg_0_2 = PyFloat_FromDouble(-0.2); if (unlikely(!__pyx_float_neg_0_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_neg_99990_0 = PyFloat_FromDouble(-99990.0); if (unlikely(!__pyx_float_neg_99990_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_11 = PyInt_FromLong(11); if (unlikely(!__pyx_int_11)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_12 = PyInt_FromLong(12); if (unlikely(!__pyx_int_12)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_21 = PyInt_FromLong(21); if (unlikely(!__pyx_int_21)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_121 = PyInt_FromLong(121); if (unlikely(!__pyx_int_121)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_211 = PyInt_FromLong(211); if (unlikely(!__pyx_int_211)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_212 = PyInt_FromLong(212); if (unlikely(!__pyx_int_212)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_221 = PyInt_FromLong(221); if (unlikely(!__pyx_int_221)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_230 = PyInt_FromLong(230); if (unlikely(!__pyx_int_230)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_360 = PyInt_FromLong(360); if (unlikely(!__pyx_int_360)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_720 = PyInt_FromLong(720); if (unlikely(!__pyx_int_720)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_920 = PyInt_FromLong(920); if (unlikely(!__pyx_int_920)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_neg_1 = PyInt_FromLong(-1); if (unlikely(!__pyx_int_neg_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initdata_handler_v2(void); /*proto*/
PyMODINIT_FUNC initdata_handler_v2(void)
#else
PyMODINIT_FUNC PyInit_data_handler_v2(void); /*proto*/
PyMODINIT_FUNC PyInit_data_handler_v2(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_t_9;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_data_handler_v2(void)", 0);
  if (__Pyx_check_binary_version() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_unicode = PyUnicode_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_unicode)) __PYX_ERR(0, 1, __pyx_L1_error)
  #ifdef __Pyx_CyFunction_USED
  if (__pyx_CyFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Coroutine_USED
  if (__pyx_Coroutine_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_StopAsyncIteration_USED
  if (__pyx_StopAsyncIteration_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("data_handler_v2", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) __PYX_ERR(0, 1, __pyx_L1_error)
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  /*--- Initialize various global constants etc. ---*/
  if (__Pyx_InitGlobals() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  if (__pyx_module_is_main_data_handler_v2) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) __PYX_ERR(0, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "data_handler_v2")) {
      if (unlikely(PyDict_SetItemString(modules, "data_handler_v2", __pyx_m) < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
    }
  }
  #endif
  /*--- Builtin init code ---*/
  if (__Pyx_InitCachedBuiltins() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Constants init code ---*/
  if (__Pyx_InitCachedConstants() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Global init code ---*/
  /*--- Variable export code ---*/
  /*--- Function export code ---*/
  /*--- Type init code ---*/
  /*--- Type import code ---*/
  /*--- Variable import code ---*/
  /*--- Function import code ---*/
  /*--- Execution code ---*/
  #if defined(__Pyx_Generator_USED) || defined(__Pyx_Coroutine_USED)
  if (__Pyx_patch_abc() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif

  /* "data_handler_v2.py":2
 * # coding=utf-8
 * import time             # <<<<<<<<<<<<<<
 * from datetime import datetime, timedelta
 * 
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_time, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_time, __pyx_t_1) < 0) __PYX_ERR(0, 2, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":3
 * # coding=utf-8
 * import time
 * from datetime import datetime, timedelta             # <<<<<<<<<<<<<<
 * 
 * from numba import jit
 */
  __pyx_t_1 = PyList_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_datetime);
  __Pyx_GIVEREF(__pyx_n_s_datetime);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_datetime);
  __Pyx_INCREF(__pyx_n_s_timedelta);
  __Pyx_GIVEREF(__pyx_n_s_timedelta);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_timedelta);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_datetime, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_datetime); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_datetime, __pyx_t_1) < 0) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_timedelta); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_timedelta, __pyx_t_1) < 0) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":5
 * from datetime import datetime, timedelta
 * 
 * from numba import jit             # <<<<<<<<<<<<<<
 * from sortedcontainers import SortedDict as OrderedDict
 * 
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_jit);
  __Pyx_GIVEREF(__pyx_n_s_jit);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_jit);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numba, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_jit); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_jit, __pyx_t_2) < 0) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":6
 * 
 * from numba import jit
 * from sortedcontainers import SortedDict as OrderedDict             # <<<<<<<<<<<<<<
 * 
 * from functools import reduce
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_SortedDict);
  __Pyx_GIVEREF(__pyx_n_s_SortedDict);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_SortedDict);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_sortedcontainers, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_SortedDict); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_OrderedDict, __pyx_t_1) < 0) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":8
 * from sortedcontainers import SortedDict as OrderedDict
 * 
 * from functools import reduce             # <<<<<<<<<<<<<<
 * 
 * import logging
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_reduce);
  __Pyx_GIVEREF(__pyx_n_s_reduce);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_reduce);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_functools, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_reduce); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_reduce, __pyx_t_2) < 0) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":10
 * from functools import reduce
 * 
 * import logging             # <<<<<<<<<<<<<<
 * 
 * logging.basicConfig(level=logging.DEBUG)
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_logging, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_logging, __pyx_t_1) < 0) __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":12
 * import logging
 * 
 * logging.basicConfig(level=logging.DEBUG)             # <<<<<<<<<<<<<<
 * 
 * import json
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_basicConfig); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_logging); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_DEBUG); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_level, __pyx_t_4) < 0) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_empty_tuple, __pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":14
 * logging.basicConfig(level=logging.DEBUG)
 * 
 * import json             # <<<<<<<<<<<<<<
 * 
 * from pprint import pprint as pp
 */
  __pyx_t_4 = __Pyx_Import(__pyx_n_s_json, 0, -1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_json, __pyx_t_4) < 0) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":16
 * import json
 * 
 * from pprint import pprint as pp             # <<<<<<<<<<<<<<
 * 
 * import numpy
 */
  __pyx_t_4 = PyList_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_INCREF(__pyx_n_s_pprint);
  __Pyx_GIVEREF(__pyx_n_s_pprint);
  PyList_SET_ITEM(__pyx_t_4, 0, __pyx_n_s_pprint);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_pprint, __pyx_t_4, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_pprint); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_pp, __pyx_t_4) < 0) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":18
 * from pprint import pprint as pp
 * 
 * import numpy             # <<<<<<<<<<<<<<
 * import numpy.ma
 * 
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numpy, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_numpy, __pyx_t_1) < 0) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":19
 * 
 * import numpy
 * import numpy.ma             # <<<<<<<<<<<<<<
 * 
 * import numexpr
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numpy_ma, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_numpy, __pyx_t_1) < 0) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":21
 * import numpy.ma
 * 
 * import numexpr             # <<<<<<<<<<<<<<
 * 
 * import netCDF4
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numexpr, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_numexpr, __pyx_t_1) < 0) __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":23
 * import numexpr
 * 
 * import netCDF4             # <<<<<<<<<<<<<<
 * from netCDF4 import Dataset, num2date
 * 
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_netCDF4, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 23, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_netCDF4, __pyx_t_1) < 0) __PYX_ERR(0, 23, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":24
 * 
 * import netCDF4
 * from netCDF4 import Dataset, num2date             # <<<<<<<<<<<<<<
 * 
 * from typing import List, Dict, Tuple
 */
  __pyx_t_1 = PyList_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_Dataset);
  __Pyx_GIVEREF(__pyx_n_s_Dataset);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_Dataset);
  __Pyx_INCREF(__pyx_n_s_num2date);
  __Pyx_GIVEREF(__pyx_n_s_num2date);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_num2date);
  __pyx_t_4 = __Pyx_Import(__pyx_n_s_netCDF4, __pyx_t_1, -1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_4, __pyx_n_s_Dataset); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Dataset, __pyx_t_1) < 0) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_4, __pyx_n_s_num2date); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_num2date, __pyx_t_1) < 0) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "data_handler_v2.py":26
 * from netCDF4 import Dataset, num2date
 * 
 * from typing import List, Dict, Tuple             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_4 = PyList_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_INCREF(__pyx_n_s_List);
  __Pyx_GIVEREF(__pyx_n_s_List);
  PyList_SET_ITEM(__pyx_t_4, 0, __pyx_n_s_List);
  __Pyx_INCREF(__pyx_n_s_Dict);
  __Pyx_GIVEREF(__pyx_n_s_Dict);
  PyList_SET_ITEM(__pyx_t_4, 1, __pyx_n_s_Dict);
  __Pyx_INCREF(__pyx_n_s_Tuple);
  __Pyx_GIVEREF(__pyx_n_s_Tuple);
  PyList_SET_ITEM(__pyx_t_4, 2, __pyx_n_s_Tuple);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_typing, __pyx_t_4, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_List); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_List, __pyx_t_4) < 0) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_Dict); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Dict, __pyx_t_4) < 0) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_Tuple); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Tuple, __pyx_t_4) < 0) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":29
 * 
 * 
 * @jit(nopython=True)             # <<<<<<<<<<<<<<
 * def find_elevation_index(vcp_mode, e):
 *     j = 0
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_jit); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_nopython, Py_True) < 0) __PYX_ERR(0, 29, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_empty_tuple, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "data_handler_v2.py":30
 * 
 * @jit(nopython=True)
 * def find_elevation_index(vcp_mode, e):             # <<<<<<<<<<<<<<
 *     j = 0
 *     for i in vcp_mode:
 */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_1find_elevation_index, 0, __pyx_n_s_find_elevation_index, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__31)); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 30, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 29, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 29, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 29, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_find_elevation_index, __pyx_t_1) < 0) __PYX_ERR(0, 30, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":37
 *         j += 1
 * 
 * @jit(nopython=True)             # <<<<<<<<<<<<<<
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
 *     r = gate_array[:size_y, :]
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_jit); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 37, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 37, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_nopython, Py_True) < 0) __PYX_ERR(0, 37, __pyx_L1_error)
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_empty_tuple, __pyx_t_5); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 37, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":38
 * 
 * @jit(nopython=True)
 * def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */
  __pyx_t_5 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_3fill_data_jit, 0, __pyx_n_s_fill_data_jit, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__33)); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3); __pyx_t_3 = NULL;
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_t_5);
    __pyx_t_5 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_fill_data_jit, __pyx_t_1) < 0) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":61
 * 
 * 
 * def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     r = gate_array[:size_y, :]
 *     a = azimuth_array[:size_y]
 */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_5fill_data_nojit, 0, __pyx_n_s_fill_data_nojit, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__35)); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_fill_data_nojit, __pyx_t_1) < 0) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":82
 *             dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
 * 
 * def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):             # <<<<<<<<<<<<<<
 *     try:
 *         fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
 */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_7fill_data_function, 0, __pyx_n_s_fill_data_function, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__37)); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 82, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_fill_data_function, __pyx_t_1) < 0) __PYX_ERR(0, 82, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":90
 * 
 * 
 * class RadarNetcdf(object):             # <<<<<<<<<<<<<<
 * 
 *     VcpTable = {
 */
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 90, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_builtin_object);
  __Pyx_GIVEREF(__pyx_builtin_object);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_builtin_object);
  __pyx_t_2 = __Pyx_CalculateMetaclass(NULL, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 90, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_Py3MetaclassPrepare(__pyx_t_2, __pyx_t_1, __pyx_n_s_RadarNetcdf, __pyx_n_s_RadarNetcdf, (PyObject *) NULL, __pyx_n_s_data_handler_v2, (PyObject *) NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 90, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);

  /* "data_handler_v2.py":93
 * 
 *     VcpTable = {
 *         11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),             # <<<<<<<<<<<<<<
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 */
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_11, __pyx_tuple__38) < 0) __PYX_ERR(0, 93, __pyx_L1_error)

  /* "data_handler_v2.py":94
 *     VcpTable = {
 *         11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),             # <<<<<<<<<<<<<<
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 */
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_211, __pyx_tuple__39) < 0) __PYX_ERR(0, 93, __pyx_L1_error)

  /* "data_handler_v2.py":95
 *         11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),             # <<<<<<<<<<<<<<
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 */
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_12, __pyx_tuple__40) < 0) __PYX_ERR(0, 93, __pyx_L1_error)

  /* "data_handler_v2.py":96
 *         211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),             # <<<<<<<<<<<<<<
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 */
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_212, __pyx_tuple__41) < 0) __PYX_ERR(0, 93, __pyx_L1_error)

  /* "data_handler_v2.py":97
 *         12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),             # <<<<<<<<<<<<<<
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)
 */
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_21, __pyx_tuple__42) < 0) __PYX_ERR(0, 93, __pyx_L1_error)

  /* "data_handler_v2.py":98
 *         212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),             # <<<<<<<<<<<<<<
 *         221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)
 *     }
 */
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_121, __pyx_tuple__43) < 0) __PYX_ERR(0, 93, __pyx_L1_error)

  /* "data_handler_v2.py":99
 *         21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
 *         221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)             # <<<<<<<<<<<<<<
 *     }
 * 
 */
  if (PyDict_SetItem(__pyx_t_5, __pyx_int_221, __pyx_tuple__44) < 0) __PYX_ERR(0, 93, __pyx_L1_error)
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_VcpTable, __pyx_t_5) < 0) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":102
 *     }
 * 
 *     all_var_names = ["Reflectivity",             # <<<<<<<<<<<<<<
 *                      "RadialVelocity", "SpectrumWidth",
 *                      "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
 */
  __pyx_t_5 = PyList_New(6); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 102, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_INCREF(__pyx_n_s_Reflectivity);
  __Pyx_GIVEREF(__pyx_n_s_Reflectivity);
  PyList_SET_ITEM(__pyx_t_5, 0, __pyx_n_s_Reflectivity);
  __Pyx_INCREF(__pyx_n_s_RadialVelocity);
  __Pyx_GIVEREF(__pyx_n_s_RadialVelocity);
  PyList_SET_ITEM(__pyx_t_5, 1, __pyx_n_s_RadialVelocity);
  __Pyx_INCREF(__pyx_n_s_SpectrumWidth);
  __Pyx_GIVEREF(__pyx_n_s_SpectrumWidth);
  PyList_SET_ITEM(__pyx_t_5, 2, __pyx_n_s_SpectrumWidth);
  __Pyx_INCREF(__pyx_n_s_DifferentialReflectivity);
  __Pyx_GIVEREF(__pyx_n_s_DifferentialReflectivity);
  PyList_SET_ITEM(__pyx_t_5, 3, __pyx_n_s_DifferentialReflectivity);
  __Pyx_INCREF(__pyx_n_s_CorrelationCoefficient);
  __Pyx_GIVEREF(__pyx_n_s_CorrelationCoefficient);
  PyList_SET_ITEM(__pyx_t_5, 4, __pyx_n_s_CorrelationCoefficient);
  __Pyx_INCREF(__pyx_n_s_DifferentialPhase);
  __Pyx_GIVEREF(__pyx_n_s_DifferentialPhase);
  PyList_SET_ITEM(__pyx_t_5, 5, __pyx_n_s_DifferentialPhase);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_all_var_names, __pyx_t_5) < 0) __PYX_ERR(0, 102, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":105
 *                      "RadialVelocity", "SpectrumWidth",
 *                      "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
 *     ref_var_names = ["Reflectivity", "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]             # <<<<<<<<<<<<<<
 *     vel_var_names = ["RadialVelocity", "SpectrumWidth"]
 * 
 */
  __pyx_t_5 = PyList_New(4); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_INCREF(__pyx_n_s_Reflectivity);
  __Pyx_GIVEREF(__pyx_n_s_Reflectivity);
  PyList_SET_ITEM(__pyx_t_5, 0, __pyx_n_s_Reflectivity);
  __Pyx_INCREF(__pyx_n_s_DifferentialReflectivity);
  __Pyx_GIVEREF(__pyx_n_s_DifferentialReflectivity);
  PyList_SET_ITEM(__pyx_t_5, 1, __pyx_n_s_DifferentialReflectivity);
  __Pyx_INCREF(__pyx_n_s_CorrelationCoefficient);
  __Pyx_GIVEREF(__pyx_n_s_CorrelationCoefficient);
  PyList_SET_ITEM(__pyx_t_5, 2, __pyx_n_s_CorrelationCoefficient);
  __Pyx_INCREF(__pyx_n_s_DifferentialPhase);
  __Pyx_GIVEREF(__pyx_n_s_DifferentialPhase);
  PyList_SET_ITEM(__pyx_t_5, 3, __pyx_n_s_DifferentialPhase);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_ref_var_names, __pyx_t_5) < 0) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":106
 *                      "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
 *     ref_var_names = ["Reflectivity", "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
 *     vel_var_names = ["RadialVelocity", "SpectrumWidth"]             # <<<<<<<<<<<<<<
 * 
 *     all_var_suffix = list("RVVDCP")
 */
  __pyx_t_5 = PyList_New(2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_INCREF(__pyx_n_s_RadialVelocity);
  __Pyx_GIVEREF(__pyx_n_s_RadialVelocity);
  PyList_SET_ITEM(__pyx_t_5, 0, __pyx_n_s_RadialVelocity);
  __Pyx_INCREF(__pyx_n_s_SpectrumWidth);
  __Pyx_GIVEREF(__pyx_n_s_SpectrumWidth);
  PyList_SET_ITEM(__pyx_t_5, 1, __pyx_n_s_SpectrumWidth);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_vel_var_names, __pyx_t_5) < 0) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":108
 *     vel_var_names = ["RadialVelocity", "SpectrumWidth"]
 * 
 *     all_var_suffix = list("RVVDCP")             # <<<<<<<<<<<<<<
 *     ref_var_suffix = list("RDCP")
 *     vel_var_suffix = list("VV")
 */
  __pyx_t_5 = PySequence_List(__pyx_n_s_RVVDCP); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 108, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_all_var_suffix, __pyx_t_5) < 0) __PYX_ERR(0, 108, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":109
 * 
 *     all_var_suffix = list("RVVDCP")
 *     ref_var_suffix = list("RDCP")             # <<<<<<<<<<<<<<
 *     vel_var_suffix = list("VV")
 * 
 */
  __pyx_t_5 = PySequence_List(__pyx_n_s_RDCP); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 109, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_ref_var_suffix, __pyx_t_5) < 0) __PYX_ERR(0, 109, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":110
 *     all_var_suffix = list("RVVDCP")
 *     ref_var_suffix = list("RDCP")
 *     vel_var_suffix = list("VV")             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):
 */
  __pyx_t_5 = PySequence_List(__pyx_n_s_VV); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 110, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_vel_var_suffix, __pyx_t_5) < 0) __PYX_ERR(0, 110, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "data_handler_v2.py":112
 *     vel_var_suffix = list("VV")
 * 
 *     def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */
  __pyx_t_5 = PyDict_New(); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_Dataset); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dataset, __pyx_t_3) < 0) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_legacy, ((PyObject*)&PyBool_Type)) < 0) __PYX_ERR(0, 112, __pyx_L1_error)
  if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_dualpol, ((PyObject*)&PyBool_Type)) < 0) __PYX_ERR(0, 112, __pyx_L1_error)
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_1__init__, 0, __pyx_n_s_RadarNetcdf___init, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__46)); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_CyFunction_SetDefaultsTuple(__pyx_t_3, __pyx_tuple__47);
  __Pyx_CyFunction_SetAnnotationsDict(__pyx_t_3, __pyx_t_5);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_init, __pyx_t_3) < 0) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":163
 *         self.fill_data(first_pass=True)
 * 
 *     def is_filled(self):             # <<<<<<<<<<<<<<
 *         # All filled means all is True
 *         return numpy.all(numpy.logical_not(self.filling_table))  # type: bool
 */
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_3is_filled, 0, __pyx_n_s_RadarNetcdf_is_filled, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__49)); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_is_filled, __pyx_t_3) < 0) __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":168
 * 
 *     # Dump helper function
 *     def __dump(self, var, time_var, dump_dict):             # <<<<<<<<<<<<<<
 *         if time_var not in ds.variables or var not in ds.variables:
 *             return
 */
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_5__dump, 0, __pyx_n_s_RadarNetcdf___dump, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__51)); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_RadarNetcdf__dump, __pyx_t_3) < 0) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":182
 *                 dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})
 * 
 *     def dump_data_by_time(self, dump_var_names, dump_target):             # <<<<<<<<<<<<<<
 *         assert len(dump_var_names) == len(self.all_var_suffix)
 *         for i in range(len(dump_var_names)):
 */
  __pyx_t_3 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_7dump_data_by_time, 0, __pyx_n_s_RadarNetcdf_dump_data_by_time, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__53)); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_dump_data_by_time, __pyx_t_3) < 0) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":195
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_netCDF4); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_Variable); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_v, __pyx_t_6) < 0) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_ma); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_MaskedArray); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_return, __pyx_t_6) < 0) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_9__fix_variable__, __Pyx_CYFUNCTION_STATICMETHOD, __pyx_n_s_RadarNetcdf___fix_variable, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__55)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_CyFunction_SetAnnotationsDict(__pyx_t_6, __pyx_t_3);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "data_handler_v2.py":194
 *             self.__dump(var_hi, time_var_hi, dump_target)
 * 
 *     @staticmethod             # <<<<<<<<<<<<<<
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
 *         """Fix wrong unsigned value"""
 */
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_6);
  __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_builtin_staticmethod, __pyx_t_3, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_fix_variable, __pyx_t_6) < 0) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "data_handler_v2.py":207
 *             return v[:]
 * 
 *     def first_pass(self):             # <<<<<<<<<<<<<<
 *         pass
 * 
 */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_11first_pass, 0, __pyx_n_s_RadarNetcdf_first_pass, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__57)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 207, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_first_pass, __pyx_t_6) < 0) __PYX_ERR(0, 207, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "data_handler_v2.py":210
 *         pass
 * 
 *     @jit             # <<<<<<<<<<<<<<
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):
 *         mode = "_HI" if id_var + "_HI" in i else ""
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_jit); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 210, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "data_handler_v2.py":211
 * 
 *     @jit
 *     def __fill_data_internal(self, i, id_var, var_names, var_suffix):             # <<<<<<<<<<<<<<
 *         mode = "_HI" if id_var + "_HI" in i else ""
 *         elevation = i[id_var + mode].mean()
 */
  __pyx_t_5 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_13__fill_data_internal, 0, __pyx_n_s_RadarNetcdf___fill_data_internal, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__59)); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 211, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_7 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_7)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_7) {
    __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_5); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 210, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_6);
  } else {
    __pyx_t_8 = PyTuple_New(1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 210, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_7); __pyx_t_7 = NULL;
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_8, 0+1, __pyx_t_5);
    __pyx_t_5 = 0;
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_8, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 210, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_RadarNetcdf__fill_data_internal, __pyx_t_6) < 0) __PYX_ERR(0, 211, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "data_handler_v2.py":221
 *                                self.beams_count, self.gates_count)
 * 
 *     def fill_data(self, *args, **kwargs):             # <<<<<<<<<<<<<<
 * 
 *         for i in self.time_data_dict.values():
 */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_15fill_data, 0, __pyx_n_s_RadarNetcdf_fill_data, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__61)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 221, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_fill_data, __pyx_t_6) < 0) __PYX_ERR(0, 221, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "data_handler_v2.py":276
 *         pass
 * 
 *     def mask_data(self):             # <<<<<<<<<<<<<<
 *         # Create a mask to remove all invalid data from reflectivity scan.
 *         total_mask = reduce(numpy.ma.logical_or,
 */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_17mask_data, 0, __pyx_n_s_RadarNetcdf_mask_data, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__63)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 276, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_mask_data, __pyx_t_6) < 0) __PYX_ERR(0, 276, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "data_handler_v2.py":284
 *             v.mask = total_mask
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_15data_handler_v2_11RadarNetcdf_19output2file, 0, __pyx_n_s_RadarNetcdf_output2file, NULL, __pyx_n_s_data_handler_v2, __pyx_d, ((PyObject *)__pyx_codeobj__65)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 284, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_4, __pyx_n_s_output2file, __pyx_t_6) < 0) __PYX_ERR(0, 284, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "data_handler_v2.py":90
 * 
 * 
 * class RadarNetcdf(object):             # <<<<<<<<<<<<<<
 * 
 *     VcpTable = {
 */
  __pyx_t_6 = __Pyx_Py3ClassCreate(__pyx_t_2, __pyx_n_s_RadarNetcdf, __pyx_t_1, __pyx_t_4, NULL, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 90, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_RadarNetcdf, __pyx_t_6) < 0) __PYX_ERR(0, 90, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "data_handler_v2.py":300
 * 
 * 
 * if __name__ == "__main__":             # <<<<<<<<<<<<<<
 *     ds = Dataset('/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc', 'r')
 *     R = RadarNetcdf(ds)
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_name_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 300, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_9 = (__Pyx_PyString_Equals(__pyx_t_1, __pyx_n_s_main, Py_EQ)); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 300, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_9) {

    /* "data_handler_v2.py":301
 * 
 * if __name__ == "__main__":
 *     ds = Dataset('/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc', 'r')             # <<<<<<<<<<<<<<
 *     R = RadarNetcdf(ds)
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_Dataset); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 301, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__66, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 301, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_ds, __pyx_t_2) < 0) __PYX_ERR(0, 301, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "data_handler_v2.py":302
 * if __name__ == "__main__":
 *     ds = Dataset('/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc', 'r')
 *     R = RadarNetcdf(ds)             # <<<<<<<<<<<<<<
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_RadarNetcdf); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_ds); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 302, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_6 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (!__pyx_t_6) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_6); __pyx_t_6 = NULL;
      __Pyx_GIVEREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_4);
      __pyx_t_4 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_R, __pyx_t_2) < 0) __PYX_ERR(0, 302, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "data_handler_v2.py":300
 * 
 * 
 * if __name__ == "__main__":             # <<<<<<<<<<<<<<
 *     ds = Dataset('/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc', 'r')
 *     R = RadarNetcdf(ds)
 */
  }

  /* "data_handler_v2.py":1
 * # coding=utf-8             # <<<<<<<<<<<<<<
 * import time
 * from datetime import datetime, timedelta
 */
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_2) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init data_handler_v2", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init data_handler_v2");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}

/* --- Runtime support code --- */
/* Refnanny */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

/* GetBuiltinName */
static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

/* RaiseArgTupleInvalid */
static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%.200s() takes %.8s %" CYTHON_FORMAT_SSIZE_T "d positional argument%.1s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}

/* RaiseDoubleKeywords */
static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}

/* ParseKeywords */
static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_CheckExact(key)) || likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (PyUnicode_GET_SIZE(**name) != PyUnicode_GET_SIZE(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (PyUnicode_GET_SIZE(**argname) != PyUnicode_GET_SIZE(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%.200s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%.200s() got an unexpected keyword argument '%.200s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}

/* PyIntBinop */
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        const long b = intval;
        long x;
        long a = PyInt_AS_LONG(op1);
            x = (long)((unsigned long)a + b);
            if (likely((x^a) >= 0 || (x^b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_add(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS && PY_MAJOR_VERSION >= 3
    if (likely(PyLong_CheckExact(op1))) {
        const long b = intval;
        long a, x;
        const PY_LONG_LONG llb = intval;
        PY_LONG_LONG lla, llx;
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            a = likely(size) ? digits[0] : 0;
            if (size == -1) a = -a;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
                    }
                default: return PyLong_Type.tp_as_number->nb_add(op1, op2);
            }
        }
                x = a + b;
            return PyLong_FromLong(x);
        long_long:
                llx = lla + llb;
            return PyLong_FromLongLong(llx);
    }
    #endif
    if (PyFloat_CheckExact(op1)) {
        const long b = intval;
        double a = PyFloat_AS_DOUBLE(op1);
            double result;
            PyFPE_START_PROTECT("add", return NULL)
            result = ((double)a) + (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
}
#endif

/* SliceObject */
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetSlice(PyObject* obj,
        Py_ssize_t cstart, Py_ssize_t cstop,
        PyObject** _py_start, PyObject** _py_stop, PyObject** _py_slice,
        int has_cstart, int has_cstop, CYTHON_UNUSED int wraparound) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyMappingMethods* mp;
#if PY_MAJOR_VERSION < 3
    PySequenceMethods* ms = Py_TYPE(obj)->tp_as_sequence;
    if (likely(ms && ms->sq_slice)) {
        if (!has_cstart) {
            if (_py_start && (*_py_start != Py_None)) {
                cstart = __Pyx_PyIndex_AsSsize_t(*_py_start);
                if ((cstart == (Py_ssize_t)-1) && PyErr_Occurred()) goto bad;
            } else
                cstart = 0;
        }
        if (!has_cstop) {
            if (_py_stop && (*_py_stop != Py_None)) {
                cstop = __Pyx_PyIndex_AsSsize_t(*_py_stop);
                if ((cstop == (Py_ssize_t)-1) && PyErr_Occurred()) goto bad;
            } else
                cstop = PY_SSIZE_T_MAX;
        }
        if (wraparound && unlikely((cstart < 0) | (cstop < 0)) && likely(ms->sq_length)) {
            Py_ssize_t l = ms->sq_length(obj);
            if (likely(l >= 0)) {
                if (cstop < 0) {
                    cstop += l;
                    if (cstop < 0) cstop = 0;
                }
                if (cstart < 0) {
                    cstart += l;
                    if (cstart < 0) cstart = 0;
                }
            } else {
                if (!PyErr_ExceptionMatches(PyExc_OverflowError))
                    goto bad;
                PyErr_Clear();
            }
        }
        return ms->sq_slice(obj, cstart, cstop);
    }
#endif
    mp = Py_TYPE(obj)->tp_as_mapping;
    if (likely(mp && mp->mp_subscript))
#endif
    {
        PyObject* result;
        PyObject *py_slice, *py_start, *py_stop;
        if (_py_slice) {
            py_slice = *_py_slice;
        } else {
            PyObject* owned_start = NULL;
            PyObject* owned_stop = NULL;
            if (_py_start) {
                py_start = *_py_start;
            } else {
                if (has_cstart) {
                    owned_start = py_start = PyInt_FromSsize_t(cstart);
                    if (unlikely(!py_start)) goto bad;
                } else
                    py_start = Py_None;
            }
            if (_py_stop) {
                py_stop = *_py_stop;
            } else {
                if (has_cstop) {
                    owned_stop = py_stop = PyInt_FromSsize_t(cstop);
                    if (unlikely(!py_stop)) {
                        Py_XDECREF(owned_start);
                        goto bad;
                    }
                } else
                    py_stop = Py_None;
            }
            py_slice = PySlice_New(py_start, py_stop, Py_None);
            Py_XDECREF(owned_start);
            Py_XDECREF(owned_stop);
            if (unlikely(!py_slice)) goto bad;
        }
#if CYTHON_COMPILING_IN_CPYTHON
        result = mp->mp_subscript(obj, py_slice);
#else
        result = PyObject_GetItem(obj, py_slice);
#endif
        if (!_py_slice) {
            Py_DECREF(py_slice);
        }
        return result;
    }
    PyErr_Format(PyExc_TypeError,
        "'%.200s' object is unsliceable", Py_TYPE(obj)->tp_name);
bad:
    return NULL;
}

/* GetModuleGlobalName */
static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
    PyObject *result;
#if CYTHON_COMPILING_IN_CPYTHON
    result = PyDict_GetItem(__pyx_d, name);
    if (likely(result)) {
        Py_INCREF(result);
    } else {
#else
    result = PyObject_GetItem(__pyx_d, name);
    if (!result) {
        PyErr_Clear();
#endif
        result = __Pyx_GetBuiltinName(name);
    }
    return result;
}

/* PyObjectCall */
  #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCallMethO */
  #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg) {
    PyObject *self, *result;
    PyCFunction cfunc;
    cfunc = PyCFunction_GET_FUNCTION(func);
    self = PyCFunction_GET_SELF(func);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = cfunc(self, arg);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCallOneArg */
  #if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_New(1);
    if (unlikely(!args)) return NULL;
    Py_INCREF(arg);
    PyTuple_SET_ITEM(args, 0, arg);
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
            return __Pyx_PyObject_CallMethO(func, arg);
        }
    }
    return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_Pack(1, arg);
    if (unlikely(!args)) return NULL;
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
#endif

/* GetItemInt */
    static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (wraparound & unlikely(i < 0)) i += PyList_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (wraparound & unlikely(i < 0)) i += PyTuple_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i, int is_list,
                                                     CYTHON_NCP_UNUSED int wraparound,
                                                     CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely((n >= 0) & (n < PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (!PyErr_ExceptionMatches(PyExc_OverflowError))
                        return NULL;
                    PyErr_Clear();
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

/* SaveResetException */
    #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
}
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
#endif

/* GetException */
    #if CYTHON_COMPILING_IN_CPYTHON
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb) {
#endif
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_COMPILING_IN_CPYTHON
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (local_tb) {
        if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
            goto bad;
    }
    #endif
    Py_XINCREF(local_tb);
    Py_XINCREF(local_type);
    Py_XINCREF(local_value);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_COMPILING_IN_CPYTHON
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

/* PyObjectCallNoArg */
      #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func) {
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
            return __Pyx_PyObject_CallMethO(func, NULL);
        }
    }
    return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

/* PyErrExceptionMatches */
        #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err) {
    PyObject *exc_type = tstate->curexc_type;
    if (exc_type == err) return 1;
    if (unlikely(!exc_type)) return 0;
    return PyErr_GivenExceptionMatches(exc_type, err);
}
#endif

/* RaiseTooManyValuesToUnpack */
        static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected) {
    PyErr_Format(PyExc_ValueError,
                 "too many values to unpack (expected %" CYTHON_FORMAT_SSIZE_T "d)", expected);
}

/* RaiseNeedMoreValuesToUnpack */
        static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index) {
    PyErr_Format(PyExc_ValueError,
                 "need more than %" CYTHON_FORMAT_SSIZE_T "d value%.1s to unpack",
                 index, (index == 1) ? "" : "s");
}

/* IterFinish */
        static CYTHON_INLINE int __Pyx_IterFinish(void) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    PyObject* exc_type = tstate->curexc_type;
    if (unlikely(exc_type)) {
        if (likely(exc_type == PyExc_StopIteration) || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)) {
            PyObject *exc_value, *exc_tb;
            exc_value = tstate->curexc_value;
            exc_tb = tstate->curexc_traceback;
            tstate->curexc_type = 0;
            tstate->curexc_value = 0;
            tstate->curexc_traceback = 0;
            Py_DECREF(exc_type);
            Py_XDECREF(exc_value);
            Py_XDECREF(exc_tb);
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#else
    if (unlikely(PyErr_Occurred())) {
        if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) {
            PyErr_Clear();
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#endif
}

/* UnpackItemEndCheck */
        static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected) {
    if (unlikely(retval)) {
        Py_DECREF(retval);
        __Pyx_RaiseTooManyValuesError(expected);
        return -1;
    } else {
        return __Pyx_IterFinish();
    }
    return 0;
}

/* Import */
        static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_VERSION_HEX < 0x03030000
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                #if PY_VERSION_HEX < 0x03030000
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                #else
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                #endif
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_VERSION_HEX < 0x03030000
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_VERSION_HEX < 0x03030000
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

/* ImportFrom */
        static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

/* FetchCommonType */
        static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type) {
    PyObject* fake_module;
    PyTypeObject* cached_type = NULL;
    fake_module = PyImport_AddModule((char*) "_cython_" CYTHON_ABI);
    if (!fake_module) return NULL;
    Py_INCREF(fake_module);
    cached_type = (PyTypeObject*) PyObject_GetAttrString(fake_module, type->tp_name);
    if (cached_type) {
        if (!PyType_Check((PyObject*)cached_type)) {
            PyErr_Format(PyExc_TypeError,
                "Shared Cython type %.200s is not a type object",
                type->tp_name);
            goto bad;
        }
        if (cached_type->tp_basicsize != type->tp_basicsize) {
            PyErr_Format(PyExc_TypeError,
                "Shared Cython type %.200s has the wrong size, try recompiling",
                type->tp_name);
            goto bad;
        }
    } else {
        if (!PyErr_ExceptionMatches(PyExc_AttributeError)) goto bad;
        PyErr_Clear();
        if (PyType_Ready(type) < 0) goto bad;
        if (PyObject_SetAttrString(fake_module, type->tp_name, (PyObject*) type) < 0)
            goto bad;
        Py_INCREF(type);
        cached_type = type;
    }
done:
    Py_DECREF(fake_module);
    return cached_type;
bad:
    Py_XDECREF(cached_type);
    cached_type = NULL;
    goto done;
}

/* CythonFunction */
        static PyObject *
__Pyx_CyFunction_get_doc(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *closure)
{
    if (unlikely(op->func_doc == NULL)) {
        if (op->func.m_ml->ml_doc) {
#if PY_MAJOR_VERSION >= 3
            op->func_doc = PyUnicode_FromString(op->func.m_ml->ml_doc);
#else
            op->func_doc = PyString_FromString(op->func.m_ml->ml_doc);
#endif
            if (unlikely(op->func_doc == NULL))
                return NULL;
        } else {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }
    Py_INCREF(op->func_doc);
    return op->func_doc;
}
static int
__Pyx_CyFunction_set_doc(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp = op->func_doc;
    if (value == NULL) {
        value = Py_None;
    }
    Py_INCREF(value);
    op->func_doc = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_name(__pyx_CyFunctionObject *op)
{
    if (unlikely(op->func_name == NULL)) {
#if PY_MAJOR_VERSION >= 3
        op->func_name = PyUnicode_InternFromString(op->func.m_ml->ml_name);
#else
        op->func_name = PyString_InternFromString(op->func.m_ml->ml_name);
#endif
        if (unlikely(op->func_name == NULL))
            return NULL;
    }
    Py_INCREF(op->func_name);
    return op->func_name;
}
static int
__Pyx_CyFunction_set_name(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (unlikely(value == NULL || !PyUnicode_Check(value))) {
#else
    if (unlikely(value == NULL || !PyString_Check(value))) {
#endif
        PyErr_SetString(PyExc_TypeError,
                        "__name__ must be set to a string object");
        return -1;
    }
    tmp = op->func_name;
    Py_INCREF(value);
    op->func_name = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_qualname(__pyx_CyFunctionObject *op)
{
    Py_INCREF(op->func_qualname);
    return op->func_qualname;
}
static int
__Pyx_CyFunction_set_qualname(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (unlikely(value == NULL || !PyUnicode_Check(value))) {
#else
    if (unlikely(value == NULL || !PyString_Check(value))) {
#endif
        PyErr_SetString(PyExc_TypeError,
                        "__qualname__ must be set to a string object");
        return -1;
    }
    tmp = op->func_qualname;
    Py_INCREF(value);
    op->func_qualname = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_self(__pyx_CyFunctionObject *m, CYTHON_UNUSED void *closure)
{
    PyObject *self;
    self = m->func_closure;
    if (self == NULL)
        self = Py_None;
    Py_INCREF(self);
    return self;
}
static PyObject *
__Pyx_CyFunction_get_dict(__pyx_CyFunctionObject *op)
{
    if (unlikely(op->func_dict == NULL)) {
        op->func_dict = PyDict_New();
        if (unlikely(op->func_dict == NULL))
            return NULL;
    }
    Py_INCREF(op->func_dict);
    return op->func_dict;
}
static int
__Pyx_CyFunction_set_dict(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
    if (unlikely(value == NULL)) {
        PyErr_SetString(PyExc_TypeError,
               "function's dictionary may not be deleted");
        return -1;
    }
    if (unlikely(!PyDict_Check(value))) {
        PyErr_SetString(PyExc_TypeError,
               "setting function's dictionary to a non-dict");
        return -1;
    }
    tmp = op->func_dict;
    Py_INCREF(value);
    op->func_dict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_globals(__pyx_CyFunctionObject *op)
{
    Py_INCREF(op->func_globals);
    return op->func_globals;
}
static PyObject *
__Pyx_CyFunction_get_closure(CYTHON_UNUSED __pyx_CyFunctionObject *op)
{
    Py_INCREF(Py_None);
    return Py_None;
}
static PyObject *
__Pyx_CyFunction_get_code(__pyx_CyFunctionObject *op)
{
    PyObject* result = (op->func_code) ? op->func_code : Py_None;
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_init_defaults(__pyx_CyFunctionObject *op) {
    int result = 0;
    PyObject *res = op->defaults_getter((PyObject *) op);
    if (unlikely(!res))
        return -1;
    #if CYTHON_COMPILING_IN_CPYTHON
    op->defaults_tuple = PyTuple_GET_ITEM(res, 0);
    Py_INCREF(op->defaults_tuple);
    op->defaults_kwdict = PyTuple_GET_ITEM(res, 1);
    Py_INCREF(op->defaults_kwdict);
    #else
    op->defaults_tuple = PySequence_ITEM(res, 0);
    if (unlikely(!op->defaults_tuple)) result = -1;
    else {
        op->defaults_kwdict = PySequence_ITEM(res, 1);
        if (unlikely(!op->defaults_kwdict)) result = -1;
    }
    #endif
    Py_DECREF(res);
    return result;
}
static int
__Pyx_CyFunction_set_defaults(__pyx_CyFunctionObject *op, PyObject* value) {
    PyObject* tmp;
    if (!value) {
        value = Py_None;
    } else if (value != Py_None && !PyTuple_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__defaults__ must be set to a tuple object");
        return -1;
    }
    Py_INCREF(value);
    tmp = op->defaults_tuple;
    op->defaults_tuple = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_defaults(__pyx_CyFunctionObject *op) {
    PyObject* result = op->defaults_tuple;
    if (unlikely(!result)) {
        if (op->defaults_getter) {
            if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
            result = op->defaults_tuple;
        } else {
            result = Py_None;
        }
    }
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_set_kwdefaults(__pyx_CyFunctionObject *op, PyObject* value) {
    PyObject* tmp;
    if (!value) {
        value = Py_None;
    } else if (value != Py_None && !PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__kwdefaults__ must be set to a dict object");
        return -1;
    }
    Py_INCREF(value);
    tmp = op->defaults_kwdict;
    op->defaults_kwdict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_kwdefaults(__pyx_CyFunctionObject *op) {
    PyObject* result = op->defaults_kwdict;
    if (unlikely(!result)) {
        if (op->defaults_getter) {
            if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
            result = op->defaults_kwdict;
        } else {
            result = Py_None;
        }
    }
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_set_annotations(__pyx_CyFunctionObject *op, PyObject* value) {
    PyObject* tmp;
    if (!value || value == Py_None) {
        value = NULL;
    } else if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__annotations__ must be set to a dict object");
        return -1;
    }
    Py_XINCREF(value);
    tmp = op->func_annotations;
    op->func_annotations = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_annotations(__pyx_CyFunctionObject *op) {
    PyObject* result = op->func_annotations;
    if (unlikely(!result)) {
        result = PyDict_New();
        if (unlikely(!result)) return NULL;
        op->func_annotations = result;
    }
    Py_INCREF(result);
    return result;
}
static PyGetSetDef __pyx_CyFunction_getsets[] = {
    {(char *) "func_doc", (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "__doc__",  (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "func_name", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__name__", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__qualname__", (getter)__Pyx_CyFunction_get_qualname, (setter)__Pyx_CyFunction_set_qualname, 0, 0},
    {(char *) "__self__", (getter)__Pyx_CyFunction_get_self, 0, 0, 0},
    {(char *) "func_dict", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "__dict__", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "func_globals", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "__globals__", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "func_closure", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "__closure__", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "func_code", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "__code__", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "func_defaults", (getter)__Pyx_CyFunction_get_defaults, (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *) "__defaults__", (getter)__Pyx_CyFunction_get_defaults, (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *) "__kwdefaults__", (getter)__Pyx_CyFunction_get_kwdefaults, (setter)__Pyx_CyFunction_set_kwdefaults, 0, 0},
    {(char *) "__annotations__", (getter)__Pyx_CyFunction_get_annotations, (setter)__Pyx_CyFunction_set_annotations, 0, 0},
    {0, 0, 0, 0, 0}
};
static PyMemberDef __pyx_CyFunction_members[] = {
    {(char *) "__module__", T_OBJECT, offsetof(__pyx_CyFunctionObject, func.m_module), PY_WRITE_RESTRICTED, 0},
    {0, 0, 0,  0, 0}
};
static PyObject *
__Pyx_CyFunction_reduce(__pyx_CyFunctionObject *m, CYTHON_UNUSED PyObject *args)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromString(m->func.m_ml->ml_name);
#else
    return PyString_FromString(m->func.m_ml->ml_name);
#endif
}
static PyMethodDef __pyx_CyFunction_methods[] = {
    {"__reduce__", (PyCFunction)__Pyx_CyFunction_reduce, METH_VARARGS, 0},
    {0, 0, 0, 0}
};
#if PY_VERSION_HEX < 0x030500A0
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func_weakreflist)
#else
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func.m_weakreflist)
#endif
static PyObject *__Pyx_CyFunction_New(PyTypeObject *type, PyMethodDef *ml, int flags, PyObject* qualname,
                                      PyObject *closure, PyObject *module, PyObject* globals, PyObject* code) {
    __pyx_CyFunctionObject *op = PyObject_GC_New(__pyx_CyFunctionObject, type);
    if (op == NULL)
        return NULL;
    op->flags = flags;
    __Pyx_CyFunction_weakreflist(op) = NULL;
    op->func.m_ml = ml;
    op->func.m_self = (PyObject *) op;
    Py_XINCREF(closure);
    op->func_closure = closure;
    Py_XINCREF(module);
    op->func.m_module = module;
    op->func_dict = NULL;
    op->func_name = NULL;
    Py_INCREF(qualname);
    op->func_qualname = qualname;
    op->func_doc = NULL;
    op->func_classobj = NULL;
    op->func_globals = globals;
    Py_INCREF(op->func_globals);
    Py_XINCREF(code);
    op->func_code = code;
    op->defaults_pyobjects = 0;
    op->defaults = NULL;
    op->defaults_tuple = NULL;
    op->defaults_kwdict = NULL;
    op->defaults_getter = NULL;
    op->func_annotations = NULL;
    PyObject_GC_Track(op);
    return (PyObject *) op;
}
static int
__Pyx_CyFunction_clear(__pyx_CyFunctionObject *m)
{
    Py_CLEAR(m->func_closure);
    Py_CLEAR(m->func.m_module);
    Py_CLEAR(m->func_dict);
    Py_CLEAR(m->func_name);
    Py_CLEAR(m->func_qualname);
    Py_CLEAR(m->func_doc);
    Py_CLEAR(m->func_globals);
    Py_CLEAR(m->func_code);
    Py_CLEAR(m->func_classobj);
    Py_CLEAR(m->defaults_tuple);
    Py_CLEAR(m->defaults_kwdict);
    Py_CLEAR(m->func_annotations);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_XDECREF(pydefaults[i]);
        PyObject_Free(m->defaults);
        m->defaults = NULL;
    }
    return 0;
}
static void __Pyx_CyFunction_dealloc(__pyx_CyFunctionObject *m)
{
    PyObject_GC_UnTrack(m);
    if (__Pyx_CyFunction_weakreflist(m) != NULL)
        PyObject_ClearWeakRefs((PyObject *) m);
    __Pyx_CyFunction_clear(m);
    PyObject_GC_Del(m);
}
static int __Pyx_CyFunction_traverse(__pyx_CyFunctionObject *m, visitproc visit, void *arg)
{
    Py_VISIT(m->func_closure);
    Py_VISIT(m->func.m_module);
    Py_VISIT(m->func_dict);
    Py_VISIT(m->func_name);
    Py_VISIT(m->func_qualname);
    Py_VISIT(m->func_doc);
    Py_VISIT(m->func_globals);
    Py_VISIT(m->func_code);
    Py_VISIT(m->func_classobj);
    Py_VISIT(m->defaults_tuple);
    Py_VISIT(m->defaults_kwdict);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_VISIT(pydefaults[i]);
    }
    return 0;
}
static PyObject *__Pyx_CyFunction_descr_get(PyObject *func, PyObject *obj, PyObject *type)
{
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    if (m->flags & __Pyx_CYFUNCTION_STATICMETHOD) {
        Py_INCREF(func);
        return func;
    }
    if (m->flags & __Pyx_CYFUNCTION_CLASSMETHOD) {
        if (type == NULL)
            type = (PyObject *)(Py_TYPE(obj));
        return __Pyx_PyMethod_New(func, type, (PyObject *)(Py_TYPE(type)));
    }
    if (obj == Py_None)
        obj = NULL;
    return __Pyx_PyMethod_New(func, obj, type);
}
static PyObject*
__Pyx_CyFunction_repr(__pyx_CyFunctionObject *op)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromFormat("<cyfunction %U at %p>",
                                op->func_qualname, (void *)op);
#else
    return PyString_FromFormat("<cyfunction %s at %p>",
                               PyString_AsString(op->func_qualname), (void *)op);
#endif
}
#if CYTHON_COMPILING_IN_PYPY
static PyObject * __Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyCFunctionObject* f = (PyCFunctionObject*)func;
    PyCFunction meth = f->m_ml->ml_meth;
    PyObject *self = f->m_self;
    Py_ssize_t size;
    switch (f->m_ml->ml_flags & (METH_VARARGS | METH_KEYWORDS | METH_NOARGS | METH_O)) {
    case METH_VARARGS:
        if (likely(kw == NULL || PyDict_Size(kw) == 0))
            return (*meth)(self, arg);
        break;
    case METH_VARARGS | METH_KEYWORDS:
        return (*(PyCFunctionWithKeywords)meth)(self, arg, kw);
    case METH_NOARGS:
        if (likely(kw == NULL || PyDict_Size(kw) == 0)) {
            size = PyTuple_GET_SIZE(arg);
            if (likely(size == 0))
                return (*meth)(self, NULL);
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes no arguments (%" CYTHON_FORMAT_SSIZE_T "d given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    case METH_O:
        if (likely(kw == NULL || PyDict_Size(kw) == 0)) {
            size = PyTuple_GET_SIZE(arg);
            if (likely(size == 1)) {
                PyObject *result, *arg0 = PySequence_ITEM(arg, 0);
                if (unlikely(!arg0)) return NULL;
                result = (*meth)(self, arg0);
                Py_DECREF(arg0);
                return result;
            }
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes exactly one argument (%" CYTHON_FORMAT_SSIZE_T "d given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    default:
        PyErr_SetString(PyExc_SystemError, "Bad call flags in "
                        "__Pyx_CyFunction_Call. METH_OLDARGS is no "
                        "longer supported!");
        return NULL;
    }
    PyErr_Format(PyExc_TypeError, "%.200s() takes no keyword arguments",
                 f->m_ml->ml_name);
    return NULL;
}
#else
static PyObject * __Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
	return PyCFunction_Call(func, arg, kw);
}
#endif
static PyTypeObject __pyx_CyFunctionType_type = {
    PyVarObject_HEAD_INIT(0, 0)
    "cython_function_or_method",
    sizeof(__pyx_CyFunctionObject),
    0,
    (destructor) __Pyx_CyFunction_dealloc,
    0,
    0,
    0,
#if PY_MAJOR_VERSION < 3
    0,
#else
    0,
#endif
    (reprfunc) __Pyx_CyFunction_repr,
    0,
    0,
    0,
    0,
    __Pyx_CyFunction_Call,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
    0,
    (traverseproc) __Pyx_CyFunction_traverse,
    (inquiry) __Pyx_CyFunction_clear,
    0,
#if PY_VERSION_HEX < 0x030500A0
    offsetof(__pyx_CyFunctionObject, func_weakreflist),
#else
    offsetof(PyCFunctionObject, m_weakreflist),
#endif
    0,
    0,
    __pyx_CyFunction_methods,
    __pyx_CyFunction_members,
    __pyx_CyFunction_getsets,
    0,
    0,
    __Pyx_CyFunction_descr_get,
    0,
    offsetof(__pyx_CyFunctionObject, func_dict),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
#if PY_VERSION_HEX >= 0x030400a1
    0,
#endif
};
static int __pyx_CyFunction_init(void) {
#if !CYTHON_COMPILING_IN_PYPY
    __pyx_CyFunctionType_type.tp_call = PyCFunction_Call;
#endif
    __pyx_CyFunctionType = __Pyx_FetchCommonType(&__pyx_CyFunctionType_type);
    if (__pyx_CyFunctionType == NULL) {
        return -1;
    }
    return 0;
}
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *func, size_t size, int pyobjects) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults = PyObject_Malloc(size);
    if (!m->defaults)
        return PyErr_NoMemory();
    memset(m->defaults, 0, size);
    m->defaults_pyobjects = pyobjects;
    return m->defaults;
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *func, PyObject *tuple) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_tuple = tuple;
    Py_INCREF(tuple);
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *func, PyObject *dict) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_kwdict = dict;
    Py_INCREF(dict);
}
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *func, PyObject *dict) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->func_annotations = dict;
    Py_INCREF(dict);
}

/* CalculateMetaclass */
            static PyObject *__Pyx_CalculateMetaclass(PyTypeObject *metaclass, PyObject *bases) {
    Py_ssize_t i, nbases = PyTuple_GET_SIZE(bases);
    for (i=0; i < nbases; i++) {
        PyTypeObject *tmptype;
        PyObject *tmp = PyTuple_GET_ITEM(bases, i);
        tmptype = Py_TYPE(tmp);
#if PY_MAJOR_VERSION < 3
        if (tmptype == &PyClass_Type)
            continue;
#endif
        if (!metaclass) {
            metaclass = tmptype;
            continue;
        }
        if (PyType_IsSubtype(metaclass, tmptype))
            continue;
        if (PyType_IsSubtype(tmptype, metaclass)) {
            metaclass = tmptype;
            continue;
        }
        PyErr_SetString(PyExc_TypeError,
                        "metaclass conflict: "
                        "the metaclass of a derived class "
                        "must be a (non-strict) subclass "
                        "of the metaclasses of all its bases");
        return NULL;
    }
    if (!metaclass) {
#if PY_MAJOR_VERSION < 3
        metaclass = &PyClass_Type;
#else
        metaclass = &PyType_Type;
#endif
    }
    Py_INCREF((PyObject*) metaclass);
    return (PyObject*) metaclass;
}

/* Py3ClassCreate */
            static PyObject *__Pyx_Py3MetaclassPrepare(PyObject *metaclass, PyObject *bases, PyObject *name,
                                           PyObject *qualname, PyObject *mkw, PyObject *modname, PyObject *doc) {
    PyObject *ns;
    if (metaclass) {
        PyObject *prep = __Pyx_PyObject_GetAttrStr(metaclass, __pyx_n_s_prepare);
        if (prep) {
            PyObject *pargs = PyTuple_Pack(2, name, bases);
            if (unlikely(!pargs)) {
                Py_DECREF(prep);
                return NULL;
            }
            ns = PyObject_Call(prep, pargs, mkw);
            Py_DECREF(prep);
            Py_DECREF(pargs);
        } else {
            if (unlikely(!PyErr_ExceptionMatches(PyExc_AttributeError)))
                return NULL;
            PyErr_Clear();
            ns = PyDict_New();
        }
    } else {
        ns = PyDict_New();
    }
    if (unlikely(!ns))
        return NULL;
    if (unlikely(PyObject_SetItem(ns, __pyx_n_s_module, modname) < 0)) goto bad;
    if (unlikely(PyObject_SetItem(ns, __pyx_n_s_qualname, qualname) < 0)) goto bad;
    if (unlikely(doc && PyObject_SetItem(ns, __pyx_n_s_doc, doc) < 0)) goto bad;
    return ns;
bad:
    Py_DECREF(ns);
    return NULL;
}
static PyObject *__Pyx_Py3ClassCreate(PyObject *metaclass, PyObject *name, PyObject *bases,
                                      PyObject *dict, PyObject *mkw,
                                      int calculate_metaclass, int allow_py2_metaclass) {
    PyObject *result, *margs;
    PyObject *owned_metaclass = NULL;
    if (allow_py2_metaclass) {
        owned_metaclass = PyObject_GetItem(dict, __pyx_n_s_metaclass);
        if (owned_metaclass) {
            metaclass = owned_metaclass;
        } else if (likely(PyErr_ExceptionMatches(PyExc_KeyError))) {
            PyErr_Clear();
        } else {
            return NULL;
        }
    }
    if (calculate_metaclass && (!metaclass || PyType_Check(metaclass))) {
        metaclass = __Pyx_CalculateMetaclass((PyTypeObject*) metaclass, bases);
        Py_XDECREF(owned_metaclass);
        if (unlikely(!metaclass))
            return NULL;
        owned_metaclass = metaclass;
    }
    margs = PyTuple_Pack(3, name, bases, dict);
    if (unlikely(!margs)) {
        result = NULL;
    } else {
        result = PyObject_Call(metaclass, margs, mkw);
        Py_DECREF(margs);
    }
    Py_XDECREF(owned_metaclass);
    return result;
}

/* BytesEquals */
            static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
    if (s1 == s2) {
        return (equals == Py_EQ);
    } else if (PyBytes_CheckExact(s1) & PyBytes_CheckExact(s2)) {
        const char *ps1, *ps2;
        Py_ssize_t length = PyBytes_GET_SIZE(s1);
        if (length != PyBytes_GET_SIZE(s2))
            return (equals == Py_NE);
        ps1 = PyBytes_AS_STRING(s1);
        ps2 = PyBytes_AS_STRING(s2);
        if (ps1[0] != ps2[0]) {
            return (equals == Py_NE);
        } else if (length == 1) {
            return (equals == Py_EQ);
        } else {
            int result = memcmp(ps1, ps2, (size_t)length);
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & PyBytes_CheckExact(s2)) {
        return (equals == Py_NE);
    } else if ((s2 == Py_None) & PyBytes_CheckExact(s1)) {
        return (equals == Py_NE);
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
#endif
}

/* UnicodeEquals */
            static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
#if PY_MAJOR_VERSION < 3
    PyObject* owned_ref = NULL;
#endif
    int s1_is_unicode, s2_is_unicode;
    if (s1 == s2) {
        goto return_eq;
    }
    s1_is_unicode = PyUnicode_CheckExact(s1);
    s2_is_unicode = PyUnicode_CheckExact(s2);
#if PY_MAJOR_VERSION < 3
    if ((s1_is_unicode & (!s2_is_unicode)) && PyString_CheckExact(s2)) {
        owned_ref = PyUnicode_FromObject(s2);
        if (unlikely(!owned_ref))
            return -1;
        s2 = owned_ref;
        s2_is_unicode = 1;
    } else if ((s2_is_unicode & (!s1_is_unicode)) && PyString_CheckExact(s1)) {
        owned_ref = PyUnicode_FromObject(s1);
        if (unlikely(!owned_ref))
            return -1;
        s1 = owned_ref;
        s1_is_unicode = 1;
    } else if (((!s2_is_unicode) & (!s1_is_unicode))) {
        return __Pyx_PyBytes_Equals(s1, s2, equals);
    }
#endif
    if (s1_is_unicode & s2_is_unicode) {
        Py_ssize_t length;
        int kind;
        void *data1, *data2;
        if (unlikely(__Pyx_PyUnicode_READY(s1) < 0) || unlikely(__Pyx_PyUnicode_READY(s2) < 0))
            return -1;
        length = __Pyx_PyUnicode_GET_LENGTH(s1);
        if (length != __Pyx_PyUnicode_GET_LENGTH(s2)) {
            goto return_ne;
        }
        kind = __Pyx_PyUnicode_KIND(s1);
        if (kind != __Pyx_PyUnicode_KIND(s2)) {
            goto return_ne;
        }
        data1 = __Pyx_PyUnicode_DATA(s1);
        data2 = __Pyx_PyUnicode_DATA(s2);
        if (__Pyx_PyUnicode_READ(kind, data1, 0) != __Pyx_PyUnicode_READ(kind, data2, 0)) {
            goto return_ne;
        } else if (length == 1) {
            goto return_eq;
        } else {
            int result = memcmp(data1, data2, (size_t)(length * kind));
            #if PY_MAJOR_VERSION < 3
            Py_XDECREF(owned_ref);
            #endif
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & s2_is_unicode) {
        goto return_ne;
    } else if ((s2 == Py_None) & s1_is_unicode) {
        goto return_ne;
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
return_eq:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_EQ);
return_ne:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_NE);
#endif
}

/* CodeObjectCache */
            static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = start + (end - start) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, (size_t)new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

/* AddTraceback */
            #include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        PyThreadState_GET(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        __pyx_d,      /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = py_line;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

/* CIntToPy */
            static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
    const long neg_one = (long) -1, const_zero = (long) 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
        } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

/* Print */
            #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static PyObject *__Pyx_GetStdout(void) {
    PyObject *f = PySys_GetObject((char *)"stdout");
    if (!f) {
        PyErr_SetString(PyExc_RuntimeError, "lost sys.stdout");
    }
    return f;
}
static int __Pyx_Print(PyObject* f, PyObject *arg_tuple, int newline) {
    int i;
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    for (i=0; i < PyTuple_GET_SIZE(arg_tuple); i++) {
        PyObject* v;
        if (PyFile_SoftSpace(f, 1)) {
            if (PyFile_WriteString(" ", f) < 0)
                goto error;
        }
        v = PyTuple_GET_ITEM(arg_tuple, i);
        if (PyFile_WriteObject(v, f, Py_PRINT_RAW) < 0)
            goto error;
        if (PyString_Check(v)) {
            char *s = PyString_AsString(v);
            Py_ssize_t len = PyString_Size(v);
            if (len > 0) {
                switch (s[len-1]) {
                    case ' ': break;
                    case '\f': case '\r': case '\n': case '\t': case '\v':
                        PyFile_SoftSpace(f, 0);
                        break;
                    default:  break;
                }
            }
        }
    }
    if (newline) {
        if (PyFile_WriteString("\n", f) < 0)
            goto error;
        PyFile_SoftSpace(f, 0);
    }
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
}
#else
static int __Pyx_Print(PyObject* stream, PyObject *arg_tuple, int newline) {
    PyObject* kwargs = 0;
    PyObject* result = 0;
    PyObject* end_string;
    if (unlikely(!__pyx_print)) {
        __pyx_print = PyObject_GetAttr(__pyx_b, __pyx_n_s_print);
        if (!__pyx_print)
            return -1;
    }
    if (stream) {
        kwargs = PyDict_New();
        if (unlikely(!kwargs))
            return -1;
        if (unlikely(PyDict_SetItem(kwargs, __pyx_n_s_file, stream) < 0))
            goto bad;
        if (!newline) {
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                goto bad;
            if (PyDict_SetItem(kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                goto bad;
            }
            Py_DECREF(end_string);
        }
    } else if (!newline) {
        if (unlikely(!__pyx_print_kwargs)) {
            __pyx_print_kwargs = PyDict_New();
            if (unlikely(!__pyx_print_kwargs))
                return -1;
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                return -1;
            if (PyDict_SetItem(__pyx_print_kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                return -1;
            }
            Py_DECREF(end_string);
        }
        kwargs = __pyx_print_kwargs;
    }
    result = PyObject_Call(__pyx_print, arg_tuple, kwargs);
    if (unlikely(kwargs) && (kwargs != __pyx_print_kwargs))
        Py_DECREF(kwargs);
    if (!result)
        return -1;
    Py_DECREF(result);
    return 0;
bad:
    if (kwargs != __pyx_print_kwargs)
        Py_XDECREF(kwargs);
    return -1;
}
#endif

/* PrintOne */
            #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static int __Pyx_PrintOne(PyObject* f, PyObject *o) {
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    if (PyFile_SoftSpace(f, 0)) {
        if (PyFile_WriteString(" ", f) < 0)
            goto error;
    }
    if (PyFile_WriteObject(o, f, Py_PRINT_RAW) < 0)
        goto error;
    if (PyFile_WriteString("\n", f) < 0)
        goto error;
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
    /* the line below is just to avoid C compiler
     * warnings about unused functions */
    return __Pyx_Print(f, NULL, 0);
}
#else
static int __Pyx_PrintOne(PyObject* stream, PyObject *o) {
    int res;
    PyObject* arg_tuple = PyTuple_Pack(1, o);
    if (unlikely(!arg_tuple))
        return -1;
    res = __Pyx_Print(stream, arg_tuple, 1);
    Py_DECREF(arg_tuple);
    return res;
}
#endif

/* CIntFromPyVerify */
            #define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 0)
#define __PYX_VERIFY_RETURN_INT_EXC(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 1)
#define __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, exc)\
    {\
        func_type value = func_value;\
        if (sizeof(target_type) < sizeof(func_type)) {\
            if (unlikely(value != (func_type) (target_type) value)) {\
                func_type zero = 0;\
                if (exc && unlikely(value == (func_type)-1 && PyErr_Occurred()))\
                    return (target_type) -1;\
                if (is_unsigned && unlikely(value < zero))\
                    goto raise_neg_overflow;\
                else\
                    goto raise_overflow;\
            }\
        }\
        return (target_type) value;\
    }

/* CIntFromPy */
            static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
    const long neg_one = (long) -1, const_zero = (long) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, digits[0])
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 2 * PyLong_SHIFT) {
                            return (long) (((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 3 * PyLong_SHIFT) {
                            return (long) (((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 4 * PyLong_SHIFT) {
                            return (long) (((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (long) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned long, PyLong_AsUnsignedLong(x))
            } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(long) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) ((((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) ((((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) ((((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, long, PyLong_AsLong(x))
            } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, PY_LONG_LONG, PyLong_AsLongLong(x))
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

/* CIntFromPy */
            static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
    const int neg_one = (int) -1, const_zero = (int) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, digits[0])
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 2 * PyLong_SHIFT) {
                            return (int) (((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 3 * PyLong_SHIFT) {
                            return (int) (((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 4 * PyLong_SHIFT) {
                            return (int) (((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned long, PyLong_AsUnsignedLong(x))
            } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(int) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) ((((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) ((((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) ((((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, long, PyLong_AsLong(x))
            } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, PY_LONG_LONG, PyLong_AsLongLong(x))
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

/* CheckBinaryVersion */
            static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

/* InitStrings */
            static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if CYTHON_COMPILING_IN_CPYTHON && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else
        if (__Pyx_PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else
        return PyUnicode_AsUTF8AndSize(o, length);
#endif
#endif
    } else
#endif
#if (!CYTHON_COMPILING_IN_PYPY) || (defined(PyByteArray_AS_STRING) && defined(PyByteArray_GET_SIZE))
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x) {
  PyNumberMethods *m;
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return __Pyx_NewRef(x);
  m = Py_TYPE(x)->tp_as_number;
#if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b))) {
    if (sizeof(Py_ssize_t) >= sizeof(long))
        return PyInt_AS_LONG(b);
    else
        return PyInt_AsSsize_t(x);
  }
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_USE_PYLONG_INTERNALS
    const digit* digits = ((PyLongObject*)b)->ob_digit;
    const Py_ssize_t size = Py_SIZE(b);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
        ival = likely(size) ? digits[0] : 0;
        if (size == -1) ival = -ival;
        return ival;
    } else {
      switch (size) {
         case 2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
      }
    }
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif /* Py_PYTHON_H */
