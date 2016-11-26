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

#define __PYX_HAVE__vcp_212_sails
#define __PYX_HAVE_API__vcp_212_sails
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
  "vcp_212_sails.py",
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

/* PySequenceContains.proto */
static CYTHON_INLINE int __Pyx_PySequence_ContainsTF(PyObject* item, PyObject* seq, int eq) {
    int result = PySequence_Contains(seq, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

/* PyObjectCall.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* SliceObject.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetSlice(
        PyObject* obj, Py_ssize_t cstart, Py_ssize_t cstop,
        PyObject** py_start, PyObject** py_stop, PyObject** py_slice,
        int has_cstart, int has_cstop, int wraparound);

/* PyObjectCallMethO.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

/* GetModuleGlobalName.proto */
static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

/* RaiseArgTupleInvalid.proto */
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found);

/* RaiseDoubleKeywords.proto */
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name);

/* ParseKeywords.proto */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],\
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args,\
    const char* function_name);

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

/* PyObjectCallNoArg.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* IterFinish.proto */
static CYTHON_INLINE int __Pyx_IterFinish(void);

/* PyObjectCallMethod0.proto */
static PyObject* __Pyx_PyObject_CallMethod0(PyObject* obj, PyObject* method_name);

/* RaiseNeedMoreValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

/* RaiseTooManyValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

/* UnpackItemEndCheck.proto */
static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected);

/* RaiseNoneIterError.proto */
static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void);

/* UnpackTupleError.proto */
static void __Pyx_UnpackTupleError(PyObject *, Py_ssize_t index);

/* UnpackTuple2.proto */
static CYTHON_INLINE int __Pyx_unpack_tuple2(PyObject* tuple, PyObject** value1, PyObject** value2,
                                             int is_tuple, int has_known_size, int decref_tuple);

/* dict_iter.proto */
static CYTHON_INLINE PyObject* __Pyx_dict_iterator(PyObject* dict, int is_dict, PyObject* method_name,
                                                   Py_ssize_t* p_orig_length, int* p_is_dict);
static CYTHON_INLINE int __Pyx_dict_iter_next(PyObject* dict_or_iter, Py_ssize_t orig_length, Py_ssize_t* ppos,
                                              PyObject** pkey, PyObject** pvalue, PyObject** pitem, int is_dict);

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

/* PyIntBinop.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* PyIntBinop.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx_PyInt_EqObjC(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_EqObjC(op1, op2, intval, inplace)\
    PyObject_RichCompare(op1, op2, Py_EQ)
    #endif

/* SliceObject.proto */
#define __Pyx_PyObject_DelSlice(obj, cstart, cstop, py_start, py_stop, py_slice, has_cstart, has_cstop, wraparound)\
    __Pyx_PyObject_SetSlice(obj, (PyObject*)NULL, cstart, cstop, py_start, py_stop, py_slice, has_cstart, has_cstop, wraparound)
static CYTHON_INLINE int __Pyx_PyObject_SetSlice(
        PyObject* obj, PyObject* value, Py_ssize_t cstart, Py_ssize_t cstop,
        PyObject** py_start, PyObject** py_stop, PyObject** py_slice,
        int has_cstart, int has_cstop, int wraparound);

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* ImportFrom.proto */
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

/* CalculateMetaclass.proto */
static PyObject *__Pyx_CalculateMetaclass(PyTypeObject *metaclass, PyObject *bases);

/* Py3ClassCreate.proto */
static PyObject *__Pyx_Py3MetaclassPrepare(PyObject *metaclass, PyObject *bases, PyObject *name, PyObject *qualname,
                                           PyObject *mkw, PyObject *modname, PyObject *doc);
static PyObject *__Pyx_Py3ClassCreate(PyObject *metaclass, PyObject *name, PyObject *bases, PyObject *dict,
                                      PyObject *mkw, int calculate_metaclass, int allow_py2_metaclass);

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


/* Module declarations from 'vcp_212_sails' */
#define __Pyx_MODULE_NAME "vcp_212_sails"
int __pyx_module_is_main_vcp_212_sails = 0;

/* Implementation of 'vcp_212_sails' */
static PyObject *__pyx_builtin_object;
static PyObject *__pyx_builtin_staticmethod;
static PyObject *__pyx_builtin_map;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_open;
static const char __pyx_k_R[] = "R";
static const char __pyx_k_S[] = "S";
static const char __pyx_k_V[] = "V";
static const char __pyx_k_f[] = "f";
static const char __pyx_k_i[] = "i";
static const char __pyx_k_j[] = "j";
static const char __pyx_k_k[] = "k";
static const char __pyx_k_p[] = "p";
static const char __pyx_k_t[] = "t";
static const char __pyx_k_u[] = "u";
static const char __pyx_k_v[] = "v";
static const char __pyx_k_w[] = "w";
static const char __pyx_k_HI[] = "_HI";
static const char __pyx_k__7[] = " ";
static const char __pyx_k__9[] = ":";
static const char __pyx_k_ds[] = "ds";
static const char __pyx_k_ma[] = "ma";
static const char __pyx_k_rm[] = "rm";
static const char __pyx_k_v1[] = "_v1";
static const char __pyx_k__12[] = "\n";
static const char __pyx_k_doc[] = "__doc__";
static const char __pyx_k_end[] = "end";
static const char __pyx_k_map[] = "map";
static const char __pyx_k_min[] = "min";
static const char __pyx_k_v_2[] = "_v";
static const char __pyx_k_Dict[] = "Dict";
static const char __pyx_k_Enum[] = "Enum";
static const char __pyx_k_List[] = "List";
static const char __pyx_k_axis[] = "axis";
static const char __pyx_k_data[] = "data";
static const char __pyx_k_dict[] = "__dict__";
static const char __pyx_k_enum[] = "enum";
static const char __pyx_k_file[] = "file";
static const char __pyx_k_init[] = "__init__";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_mask[] = "mask";
static const char __pyx_k_mean[] = "mean";
static const char __pyx_k_open[] = "open";
static const char __pyx_k_path[] = "path";
static const char __pyx_k_self[] = "self";
static const char __pyx_k_sort[] = "sort";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_time[] = "time";
static const char __pyx_k_view[] = "view";
static const char __pyx_k_Tuple[] = "Tuple";
static const char __pyx_k_attri[] = "attri";
static const char __pyx_k_close[] = "close";
static const char __pyx_k_items[] = "items";
static const char __pyx_k_numpy[] = "numpy";
static const char __pyx_k_point[] = "point";
static const char __pyx_k_print[] = "print";
static const char __pyx_k_range[] = "range";
static const char __pyx_k_round[] = "round";
static const char __pyx_k_shape[] = "shape";
static const char __pyx_k_timeR[] = "timeR";
static const char __pyx_k_timeV[] = "timeV";
static const char __pyx_k_value[] = "value";
static const char __pyx_k_write[] = "write";
static const char __pyx_k_RVSDCP[] = "RVSDCP";
static const char __pyx_k_Vcp212[] = "Vcp212";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_module[] = "__module__";
static const char __pyx_k_object[] = "object";
static const char __pyx_k_return[] = "return";
static const char __pyx_k_suffix[] = "suffix";
static const char __pyx_k_typing[] = "typing";
static const char __pyx_k_Dataset[] = "Dataset";
static const char __pyx_k_VcpMode[] = "VcpMode";
static const char __pyx_k_VcpRain[] = "VcpRain";
static const char __pyx_k_argsort[] = "argsort";
static const char __pyx_k_dataset[] = "dataset";
static const char __pyx_k_ediff1d[] = "ediff1d";
static const char __pyx_k_netCDF4[] = "netCDF4";
static const char __pyx_k_prepare[] = "__prepare__";
static const char __pyx_k_Unsigned[] = "_Unsigned";
static const char __pyx_k_Variable[] = "Variable";
static const char __pyx_k_datatype[] = "datatype";
static const char __pyx_k_is_sails[] = "is_sails";
static const char __pyx_k_qualname[] = "__qualname__";
static const char __pyx_k_timeR_HI[] = "timeR_HI";
static const char __pyx_k_timeV_HI[] = "timeV_HI";
static const char __pyx_k_variable[] = "variable";
static const char __pyx_k_ScanTable[] = "ScanTable";
static const char __pyx_k_data_dict[] = "data_dict";
static const char __pyx_k_elevation[] = "elevation";
static const char __pyx_k_iteritems[] = "iteritems";
static const char __pyx_k_metaclass[] = "__metaclass__";
static const char __pyx_k_time_vars[] = "time_vars";
static const char __pyx_k_variables[] = "variables";
static const char __pyx_k_SortedDict[] = "SortedDict";
static const char __pyx_k_add_offset[] = "add_offset";
static const char __pyx_k_coordinate[] = "coordinate";
static const char __pyx_k_elevationR[] = "elevationR";
static const char __pyx_k_is_dualpol[] = "is_dualpol";
static const char __pyx_k_order_data[] = "order_data";
static const char __pyx_k_timeR_sort[] = "timeR_sort";
static const char __pyx_k_timeV_sort[] = "timeV_sort";
static const char __pyx_k_time_value[] = "time_value";
static const char __pyx_k_zeros_like[] = "zeros_like";
static const char __pyx_k_MaskedArray[] = "MaskedArray";
static const char __pyx_k_OrderedDict[] = "OrderedDict";
static const char __pyx_k_collections[] = "collections";
static const char __pyx_k_concatenate[] = "concatenate";
static const char __pyx_k_output2file[] = "output2file";
static const char __pyx_k_output_dict[] = "output_dict";
static const char __pyx_k_start_timeR[] = "start_timeR";
static const char __pyx_k_start_timeV[] = "start_timeV";
static const char __pyx_k_BeamScanMode[] = "BeamScanMode";
static const char __pyx_k_Reflectivity[] = "Reflectivity";
static const char __pyx_k_ScanVariable[] = "ScanVariable";
static const char __pyx_k_data_by_time[] = "data_by_time";
static const char __pyx_k_fix_variable[] = "__fix_variable__";
static const char __pyx_k_scale_factor[] = "scale_factor";
static const char __pyx_k_sorted_timeR[] = "sorted_timeR";
static const char __pyx_k_sorted_timeV[] = "sorted_timeV";
static const char __pyx_k_start_output[] = "start output...";
static const char __pyx_k_staticmethod[] = "staticmethod";
static const char __pyx_k_time_vars_HI[] = "time_vars_HI";
static const char __pyx_k_SpectrumWidth[] = "SpectrumWidth";
static const char __pyx_k_Vcp212___init[] = "Vcp212.__init__";
static const char __pyx_k_elevationR_HI[] = "elevationR_HI";
static const char __pyx_k_finish_output[] = "finish output";
static const char __pyx_k_tag_elevation[] = "tag_elevation";
static const char __pyx_k_variable_list[] = "variable_list";
static const char __pyx_k_vcp_212_sails[] = "vcp_212_sails";
static const char __pyx_k_RadialVelocity[] = "RadialVelocity";
static const char __pyx_k_all_elevationR[] = "all_elevationR";
static const char __pyx_k_elevation_vars[] = "elevation_vars";
static const char __pyx_k_ref_sort_order[] = "ref_sort_order";
static const char __pyx_k_set_auto_scale[] = "set_auto_scale";
static const char __pyx_k_start_timeR_HI[] = "start_timeR_HI";
static const char __pyx_k_start_timeV_HI[] = "start_timeV_HI";
static const char __pyx_k_vel_sort_order[] = "vel_sort_order";
static const char __pyx_k_sortedcontainers[] = "sortedcontainers";
static const char __pyx_k_variable_list_HI[] = "variable_list_HI";
static const char __pyx_k_DifferentialPhase[] = "DifferentialPhase";
static const char __pyx_k_Vcp212_order_data[] = "Vcp212.order_data";
static const char __pyx_k_elevation_by_time[] = "elevation_by_time";
static const char __pyx_k_elevation_vars_HI[] = "elevation_vars_HI";
static const char __pyx_k_link_data_to_time[] = "link_data_to_time";
static const char __pyx_k_sorted_elevationR[] = "sorted_elevationR";
static const char __pyx_k_Vcp212_output2file[] = "Vcp212.output2file";
static const char __pyx_k_Vcp212_tag_elevation[] = "Vcp212.tag_elevation";
static const char __pyx_k_normalized_elevation[] = "normalized_elevation";
static const char __pyx_k_Vcp212___fix_variable[] = "Vcp212.__fix_variable__";
static const char __pyx_k_CorrelationCoefficient[] = "CorrelationCoefficient";
static const char __pyx_k_DifferentialReflectivity[] = "DifferentialReflectivity";
static const char __pyx_k_Vcp212_link_data_to_time[] = "Vcp212.link_data_to_time";
static const char __pyx_k_DifferentialReflectivity_HI[] = "DifferentialReflectivity_HI";
static const char __pyx_k_Vcp212___init___locals_lambda[] = "Vcp212.__init__.<locals>.<lambda>";
static const char __pyx_k_home_sugar_Developer_Cloud2016[] = "/home/sugar/Developer/Cloud2016/py/vcp_212_sails.py";
static PyObject *__pyx_n_s_BeamScanMode;
static PyObject *__pyx_n_s_CorrelationCoefficient;
static PyObject *__pyx_n_s_Dataset;
static PyObject *__pyx_n_s_Dict;
static PyObject *__pyx_n_s_DifferentialPhase;
static PyObject *__pyx_n_s_DifferentialReflectivity;
static PyObject *__pyx_n_s_DifferentialReflectivity_HI;
static PyObject *__pyx_n_s_Enum;
static PyObject *__pyx_n_s_HI;
static PyObject *__pyx_n_s_List;
static PyObject *__pyx_n_s_MaskedArray;
static PyObject *__pyx_n_s_OrderedDict;
static PyObject *__pyx_n_s_R;
static PyObject *__pyx_n_s_RVSDCP;
static PyObject *__pyx_n_s_RadialVelocity;
static PyObject *__pyx_n_s_Reflectivity;
static PyObject *__pyx_n_s_S;
static PyObject *__pyx_n_s_ScanTable;
static PyObject *__pyx_n_s_ScanVariable;
static PyObject *__pyx_n_s_SortedDict;
static PyObject *__pyx_n_s_SpectrumWidth;
static PyObject *__pyx_n_s_Tuple;
static PyObject *__pyx_n_s_Unsigned;
static PyObject *__pyx_n_s_V;
static PyObject *__pyx_n_s_Variable;
static PyObject *__pyx_n_s_Vcp212;
static PyObject *__pyx_n_s_Vcp212___fix_variable;
static PyObject *__pyx_n_s_Vcp212___init;
static PyObject *__pyx_n_s_Vcp212___init___locals_lambda;
static PyObject *__pyx_n_s_Vcp212_link_data_to_time;
static PyObject *__pyx_n_s_Vcp212_order_data;
static PyObject *__pyx_n_s_Vcp212_output2file;
static PyObject *__pyx_n_s_Vcp212_tag_elevation;
static PyObject *__pyx_n_s_VcpMode;
static PyObject *__pyx_n_s_VcpRain;
static PyObject *__pyx_kp_s__12;
static PyObject *__pyx_kp_s__7;
static PyObject *__pyx_kp_s__9;
static PyObject *__pyx_n_s_add_offset;
static PyObject *__pyx_n_s_all_elevationR;
static PyObject *__pyx_n_s_argsort;
static PyObject *__pyx_n_s_attri;
static PyObject *__pyx_n_s_axis;
static PyObject *__pyx_n_s_close;
static PyObject *__pyx_n_s_collections;
static PyObject *__pyx_n_s_concatenate;
static PyObject *__pyx_n_s_coordinate;
static PyObject *__pyx_n_s_data;
static PyObject *__pyx_n_s_data_by_time;
static PyObject *__pyx_n_s_data_dict;
static PyObject *__pyx_n_s_dataset;
static PyObject *__pyx_n_s_datatype;
static PyObject *__pyx_n_s_dict;
static PyObject *__pyx_n_s_doc;
static PyObject *__pyx_n_s_ds;
static PyObject *__pyx_n_s_ediff1d;
static PyObject *__pyx_n_s_elevation;
static PyObject *__pyx_n_s_elevationR;
static PyObject *__pyx_n_s_elevationR_HI;
static PyObject *__pyx_n_s_elevation_by_time;
static PyObject *__pyx_n_s_elevation_vars;
static PyObject *__pyx_n_s_elevation_vars_HI;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_enum;
static PyObject *__pyx_n_s_f;
static PyObject *__pyx_n_s_file;
static PyObject *__pyx_kp_s_finish_output;
static PyObject *__pyx_n_s_fix_variable;
static PyObject *__pyx_kp_s_home_sugar_Developer_Cloud2016;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_init;
static PyObject *__pyx_n_s_is_dualpol;
static PyObject *__pyx_n_s_is_sails;
static PyObject *__pyx_n_s_items;
static PyObject *__pyx_n_s_iteritems;
static PyObject *__pyx_n_s_j;
static PyObject *__pyx_n_s_k;
static PyObject *__pyx_n_s_link_data_to_time;
static PyObject *__pyx_n_s_ma;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_map;
static PyObject *__pyx_n_s_mask;
static PyObject *__pyx_n_s_mean;
static PyObject *__pyx_n_s_metaclass;
static PyObject *__pyx_n_s_min;
static PyObject *__pyx_n_s_module;
static PyObject *__pyx_n_s_netCDF4;
static PyObject *__pyx_n_s_normalized_elevation;
static PyObject *__pyx_n_s_numpy;
static PyObject *__pyx_n_s_object;
static PyObject *__pyx_n_s_open;
static PyObject *__pyx_n_s_order_data;
static PyObject *__pyx_n_s_output2file;
static PyObject *__pyx_n_s_output_dict;
static PyObject *__pyx_n_s_p;
static PyObject *__pyx_n_s_path;
static PyObject *__pyx_n_s_point;
static PyObject *__pyx_n_s_prepare;
static PyObject *__pyx_n_s_print;
static PyObject *__pyx_n_s_qualname;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_ref_sort_order;
static PyObject *__pyx_n_s_return;
static PyObject *__pyx_n_s_rm;
static PyObject *__pyx_n_s_round;
static PyObject *__pyx_n_s_scale_factor;
static PyObject *__pyx_n_s_self;
static PyObject *__pyx_n_s_set_auto_scale;
static PyObject *__pyx_n_s_shape;
static PyObject *__pyx_n_s_sort;
static PyObject *__pyx_n_s_sorted_elevationR;
static PyObject *__pyx_n_s_sorted_timeR;
static PyObject *__pyx_n_s_sorted_timeV;
static PyObject *__pyx_n_s_sortedcontainers;
static PyObject *__pyx_kp_s_start_output;
static PyObject *__pyx_n_s_start_timeR;
static PyObject *__pyx_n_s_start_timeR_HI;
static PyObject *__pyx_n_s_start_timeV;
static PyObject *__pyx_n_s_start_timeV_HI;
static PyObject *__pyx_n_s_staticmethod;
static PyObject *__pyx_n_s_suffix;
static PyObject *__pyx_n_s_t;
static PyObject *__pyx_n_s_tag_elevation;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_time;
static PyObject *__pyx_n_s_timeR;
static PyObject *__pyx_n_s_timeR_HI;
static PyObject *__pyx_n_s_timeR_sort;
static PyObject *__pyx_n_s_timeV;
static PyObject *__pyx_n_s_timeV_HI;
static PyObject *__pyx_n_s_timeV_sort;
static PyObject *__pyx_n_s_time_value;
static PyObject *__pyx_n_s_time_vars;
static PyObject *__pyx_n_s_time_vars_HI;
static PyObject *__pyx_n_s_typing;
static PyObject *__pyx_n_s_u;
static PyObject *__pyx_n_s_v;
static PyObject *__pyx_n_s_v1;
static PyObject *__pyx_n_s_v_2;
static PyObject *__pyx_n_s_value;
static PyObject *__pyx_n_s_variable;
static PyObject *__pyx_n_s_variable_list;
static PyObject *__pyx_n_s_variable_list_HI;
static PyObject *__pyx_n_s_variables;
static PyObject *__pyx_n_s_vcp_212_sails;
static PyObject *__pyx_n_s_vel_sort_order;
static PyObject *__pyx_n_s_view;
static PyObject *__pyx_n_s_w;
static PyObject *__pyx_n_s_write;
static PyObject *__pyx_n_s_zeros_like;
static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212___fix_variable__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_v); /* proto */
static PyObject *__pyx_lambda_funcdef_lambda(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_p); /* proto */
static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_2__init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_dataset); /* proto */
static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_4tag_elevation(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_6link_data_to_time(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_8output2file(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_path, PyObject *__pyx_v_coordinate); /* proto */
static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_10order_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_float_0_1;
static PyObject *__pyx_float_0_5;
static PyObject *__pyx_float_0_9;
static PyObject *__pyx_float_1_3;
static PyObject *__pyx_float_1_8;
static PyObject *__pyx_float_2_4;
static PyObject *__pyx_float_3_1;
static PyObject *__pyx_float_4_0;
static PyObject *__pyx_float_5_1;
static PyObject *__pyx_float_6_4;
static PyObject *__pyx_float_8_0;
static PyObject *__pyx_float_10_0;
static PyObject *__pyx_float_12_5;
static PyObject *__pyx_float_15_6;
static PyObject *__pyx_float_19_5;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_3;
static PyObject *__pyx_int_4;
static PyObject *__pyx_tuple_;
static PyObject *__pyx_slice__2;
static PyObject *__pyx_slice__3;
static PyObject *__pyx_slice__5;
static PyObject *__pyx_tuple__4;
static PyObject *__pyx_tuple__6;
static PyObject *__pyx_tuple__8;
static PyObject *__pyx_slice__14;
static PyObject *__pyx_slice__15;
static PyObject *__pyx_slice__16;
static PyObject *__pyx_slice__17;
static PyObject *__pyx_slice__19;
static PyObject *__pyx_slice__20;
static PyObject *__pyx_slice__21;
static PyObject *__pyx_tuple__10;
static PyObject *__pyx_tuple__11;
static PyObject *__pyx_tuple__13;
static PyObject *__pyx_tuple__18;
static PyObject *__pyx_tuple__22;
static PyObject *__pyx_tuple__23;
static PyObject *__pyx_tuple__24;
static PyObject *__pyx_tuple__26;
static PyObject *__pyx_tuple__28;
static PyObject *__pyx_tuple__30;
static PyObject *__pyx_tuple__32;
static PyObject *__pyx_tuple__34;
static PyObject *__pyx_codeobj__25;
static PyObject *__pyx_codeobj__27;
static PyObject *__pyx_codeobj__29;
static PyObject *__pyx_codeobj__31;
static PyObject *__pyx_codeobj__33;
static PyObject *__pyx_codeobj__35;

/* "vcp_212_sails.py":38
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_1__fix_variable__(PyObject *__pyx_self, PyObject *__pyx_v_v); /*proto*/
static char __pyx_doc_13vcp_212_sails_6Vcp212___fix_variable__[] = "Fix wrong unsigned value";
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_1__fix_variable__ = {"__fix_variable__", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_1__fix_variable__, METH_O, __pyx_doc_13vcp_212_sails_6Vcp212___fix_variable__};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_1__fix_variable__(PyObject *__pyx_self, PyObject *__pyx_v_v) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__fix_variable__ (wrapper)", 0);
  __pyx_r = __pyx_pf_13vcp_212_sails_6Vcp212___fix_variable__(__pyx_self, ((PyObject *)__pyx_v_v));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212___fix_variable__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_v) {
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

  /* "vcp_212_sails.py":40
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:             # <<<<<<<<<<<<<<
 *             v.set_auto_scale(False)
 *             # Dump out
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_add_offset, __pyx_t_2, Py_EQ)); if (unlikely(__pyx_t_3 < 0)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = (__pyx_t_3 != 0);
  if (__pyx_t_4) {
  } else {
    __pyx_t_1 = __pyx_t_4;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = (__Pyx_PySequence_ContainsTF(__pyx_n_s_scale_factor, __pyx_t_2, Py_EQ)); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_3 = (__pyx_t_4 != 0);
  if (__pyx_t_3) {
  } else {
    __pyx_t_1 = __pyx_t_3;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_Unsigned); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_1 = __pyx_t_3;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_1) {

    /* "vcp_212_sails.py":41
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 *             v.set_auto_scale(False)             # <<<<<<<<<<<<<<
 *             # Dump out
 *             _v = v[:]
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_set_auto_scale); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 41, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple_, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 41, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

    /* "vcp_212_sails.py":43
 *             v.set_auto_scale(False)
 *             # Dump out
 *             _v = v[:]             # <<<<<<<<<<<<<<
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 */
    __pyx_t_5 = __Pyx_PyObject_GetSlice(__pyx_v_v, 0, 0, NULL, NULL, &__pyx_slice__2, 0, 0, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 43, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_v__v = __pyx_t_5;
    __pyx_t_5 = 0;

    /* "vcp_212_sails.py":44
 *             # Dump out
 *             _v = v[:]
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset             # <<<<<<<<<<<<<<
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 *         else:
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v__v, __pyx_n_s_data); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_view); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_datatype); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_7 = PyTuple_New(1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_7, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = PyNumber_Add(__pyx_n_s_u, __pyx_t_2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 44, __pyx_L1_error)
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
      __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_7); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 44, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else {
      __pyx_t_8 = PyTuple_New(1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 44, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_GIVEREF(__pyx_t_7);
      PyTuple_SET_ITEM(__pyx_t_8, 0+1, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_8, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 44, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_scale_factor); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = PyNumber_Multiply(__pyx_t_5, __pyx_t_6); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_v, __pyx_n_s_add_offset); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_5 = PyNumber_Add(__pyx_t_8, __pyx_t_6); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 44, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_v__v1 = __pyx_t_5;
    __pyx_t_5 = 0;

    /* "vcp_212_sails.py":45
 *             _v = v[:]
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             return numpy.ma.MaskedArray(_v1, _v.mask)             # <<<<<<<<<<<<<<
 *         else:
 *             return v[:]
 */
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 45, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_ma); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 45, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_MaskedArray); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 45, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v__v, __pyx_n_s_mask); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 45, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_7 = NULL;
    __pyx_t_9 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
        __pyx_t_9 = 1;
      }
    }
    __pyx_t_2 = PyTuple_New(2+__pyx_t_9); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 45, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    if (__pyx_t_7) {
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_7); __pyx_t_7 = NULL;
    }
    __Pyx_INCREF(__pyx_v__v1);
    __Pyx_GIVEREF(__pyx_v__v1);
    PyTuple_SET_ITEM(__pyx_t_2, 0+__pyx_t_9, __pyx_v__v1);
    __Pyx_GIVEREF(__pyx_t_8);
    PyTuple_SET_ITEM(__pyx_t_2, 1+__pyx_t_9, __pyx_t_8);
    __pyx_t_8 = 0;
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_2, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 45, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_r = __pyx_t_5;
    __pyx_t_5 = 0;
    goto __pyx_L0;

    /* "vcp_212_sails.py":40
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:             # <<<<<<<<<<<<<<
 *             v.set_auto_scale(False)
 *             # Dump out
 */
  }

  /* "vcp_212_sails.py":47
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 *         else:
 *             return v[:]             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, dataset: Dataset):
 */
  /*else*/ {
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_5 = __Pyx_PyObject_GetSlice(__pyx_v_v, 0, 0, NULL, NULL, &__pyx_slice__3, 0, 0, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 47, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_r = __pyx_t_5;
    __pyx_t_5 = 0;
    goto __pyx_L0;
  }

  /* "vcp_212_sails.py":38
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
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.__fix_variable__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v__v);
  __Pyx_XDECREF(__pyx_v__v1);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":49
 *             return v[:]
 * 
 *     def __init__(self, dataset: Dataset):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_3__init__(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_3__init__ = {"__init__", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_3__init__, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_3__init__(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_dataset = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self,&__pyx_n_s_dataset,0};
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
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_dataset)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 2, 2, 1); __PYX_ERR(0, 49, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) __PYX_ERR(0, 49, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v_dataset = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 49, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_13vcp_212_sails_6Vcp212_2__init__(__pyx_self, __pyx_v_self, __pyx_v_dataset);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":54
 *         self.variable_list = "Reflectivity", "RadialVelocity", "SpectrumWidth", \
 *                              "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
 *         self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables             # <<<<<<<<<<<<<<
 *         self.suffix = list("RVSDCP")
 *         self.time_vars = ["time" + p for p in self.suffix]
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_8__init___lambda(PyObject *__pyx_self, PyObject *__pyx_v_p); /*proto*/
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_8__init___lambda = {"lambda", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_8__init___lambda, METH_O, 0};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_8__init___lambda(PyObject *__pyx_self, PyObject *__pyx_v_p) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("lambda (wrapper)", 0);
  __pyx_r = __pyx_lambda_funcdef_lambda(__pyx_self, ((PyObject *)__pyx_v_p));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_lambda_funcdef_lambda(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_p) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("lambda", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyNumber_Add(__pyx_v_p, __pyx_n_s_HI); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.__init__.lambda", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":49
 *             return v[:]
 * 
 *     def __init__(self, dataset: Dataset):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */

static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_2__init__(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self, PyObject *__pyx_v_dataset) {
  PyObject *__pyx_v_k = NULL;
  PyObject *__pyx_v_v = NULL;
  PyObject *__pyx_v_p = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t __pyx_t_4;
  PyObject *(*__pyx_t_5)(PyObject *);
  PyObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  Py_ssize_t __pyx_t_10;
  int __pyx_t_11;
  int __pyx_t_12;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "vcp_212_sails.py":51
 *     def __init__(self, dataset: Dataset):
 * 
 *         self.dataset = dataset             # <<<<<<<<<<<<<<
 *         self.variable_list = "Reflectivity", "RadialVelocity", "SpectrumWidth", \
 *                              "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_dataset, __pyx_v_dataset) < 0) __PYX_ERR(0, 51, __pyx_L1_error)

  /* "vcp_212_sails.py":52
 * 
 *         self.dataset = dataset
 *         self.variable_list = "Reflectivity", "RadialVelocity", "SpectrumWidth", \             # <<<<<<<<<<<<<<
 *                              "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
 *         self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_variable_list, __pyx_tuple__4) < 0) __PYX_ERR(0, 52, __pyx_L1_error)

  /* "vcp_212_sails.py":54
 *         self.variable_list = "Reflectivity", "RadialVelocity", "SpectrumWidth", \
 *                              "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
 *         self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables             # <<<<<<<<<<<<<<
 *         self.suffix = list("RVSDCP")
 *         self.time_vars = ["time" + p for p in self.suffix]
 */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_8__init___lambda, 0, __pyx_n_s_Vcp212___init___locals_lambda, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_variable_list); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_2);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_map, __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_variable_list_HI, __pyx_t_2) < 0) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":55
 *                              "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
 *         self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables
 *         self.suffix = list("RVSDCP")             # <<<<<<<<<<<<<<
 *         self.time_vars = ["time" + p for p in self.suffix]
 *         self.time_vars_HI = [p + "_HI" for p in self.time_vars]
 */
  __pyx_t_2 = PySequence_List(__pyx_n_s_RVSDCP); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 55, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_suffix, __pyx_t_2) < 0) __PYX_ERR(0, 55, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":56
 *         self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables
 *         self.suffix = list("RVSDCP")
 *         self.time_vars = ["time" + p for p in self.suffix]             # <<<<<<<<<<<<<<
 *         self.time_vars_HI = [p + "_HI" for p in self.time_vars]
 *         self.elevation_vars = self.time_vars = ["elevation" + p for p in self.suffix]
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 56, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_suffix); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 56, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
    __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 56, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 56, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 56, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 56, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 56, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 56, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      }
    } else {
      __pyx_t_3 = __pyx_t_5(__pyx_t_1);
      if (unlikely(!__pyx_t_3)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 56, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_3);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_Add(__pyx_n_s_time, __pyx_v_p); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 56, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_2, (PyObject*)__pyx_t_3))) __PYX_ERR(0, 56, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_time_vars, __pyx_t_2) < 0) __PYX_ERR(0, 56, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":57
 *         self.suffix = list("RVSDCP")
 *         self.time_vars = ["time" + p for p in self.suffix]
 *         self.time_vars_HI = [p + "_HI" for p in self.time_vars]             # <<<<<<<<<<<<<<
 *         self.elevation_vars = self.time_vars = ["elevation" + p for p in self.suffix]
 *         self.elevation_vars_HI = [p + "_HI" for p in self.elevation_vars]
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_time_vars); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_3 = __pyx_t_1; __Pyx_INCREF(__pyx_t_3); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 57, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 57, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_1); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 57, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_1); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 57, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_5(__pyx_t_3);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 57, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = PyNumber_Add(__pyx_v_p, __pyx_n_s_HI); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_2, (PyObject*)__pyx_t_1))) __PYX_ERR(0, 57, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_time_vars_HI, __pyx_t_2) < 0) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":58
 *         self.time_vars = ["time" + p for p in self.suffix]
 *         self.time_vars_HI = [p + "_HI" for p in self.time_vars]
 *         self.elevation_vars = self.time_vars = ["elevation" + p for p in self.suffix]             # <<<<<<<<<<<<<<
 *         self.elevation_vars_HI = [p + "_HI" for p in self.elevation_vars]
 * 
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_suffix); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
    __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 58, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 58, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 58, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 58, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 58, __pyx_L1_error)
        #else
        __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 58, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
      }
    } else {
      __pyx_t_3 = __pyx_t_5(__pyx_t_1);
      if (unlikely(!__pyx_t_3)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 58, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_3);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_Add(__pyx_n_s_elevation, __pyx_v_p); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 58, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_2, (PyObject*)__pyx_t_3))) __PYX_ERR(0, 58, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_elevation_vars, __pyx_t_2) < 0) __PYX_ERR(0, 58, __pyx_L1_error)
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_time_vars, __pyx_t_2) < 0) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":59
 *         self.time_vars_HI = [p + "_HI" for p in self.time_vars]
 *         self.elevation_vars = self.time_vars = ["elevation" + p for p in self.suffix]
 *         self.elevation_vars_HI = [p + "_HI" for p in self.elevation_vars]             # <<<<<<<<<<<<<<
 * 
 *         # Dump data variables
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_elevation_vars); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_3 = __pyx_t_1; __Pyx_INCREF(__pyx_t_3); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_1); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 59, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_4); __Pyx_INCREF(__pyx_t_1); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 59, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_5(__pyx_t_3);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 59, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    __Pyx_XDECREF_SET(__pyx_v_p, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = PyNumber_Add(__pyx_v_p, __pyx_n_s_HI); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_2, (PyObject*)__pyx_t_1))) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_elevation_vars_HI, __pyx_t_2) < 0) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":62
 * 
 *         # Dump data variables
 *         self.data_dict = {p: dataset.variables[p] if p in dataset.variables else None for p in             # <<<<<<<<<<<<<<
 *                           self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]
 *         self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in
 */
  { /* enter inner scope */
    PyObject *__pyx_7genexpr__pyx_v_p = NULL;
    __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 62, __pyx_L13_error)
    __Pyx_GOTREF(__pyx_t_2);

    /* "vcp_212_sails.py":63
 *         # Dump data variables
 *         self.data_dict = {p: dataset.variables[p] if p in dataset.variables else None for p in
 *                           self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]             # <<<<<<<<<<<<<<
 *         self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in
 *                            self.variable_list_HI}  # type: Dict[str, numpy.ma.MaskedArray]
 */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_variable_list); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 63, __pyx_L13_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
      __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_4 = 0;
      __pyx_t_5 = NULL;
    } else {
      __pyx_t_4 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 63, __pyx_L13_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_5 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 63, __pyx_L13_error)
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    for (;;) {
      if (likely(!__pyx_t_5)) {
        if (likely(PyList_CheckExact(__pyx_t_1))) {
          if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 63, __pyx_L13_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 63, __pyx_L13_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        } else {
          if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 63, __pyx_L13_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 63, __pyx_L13_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        }
      } else {
        __pyx_t_3 = __pyx_t_5(__pyx_t_1);
        if (unlikely(!__pyx_t_3)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 63, __pyx_L13_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_3);
      }
      __Pyx_XDECREF_SET(__pyx_7genexpr__pyx_v_p, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "vcp_212_sails.py":62
 * 
 *         # Dump data variables
 *         self.data_dict = {p: dataset.variables[p] if p in dataset.variables else None for p in             # <<<<<<<<<<<<<<
 *                           self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]
 *         self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in
 */
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_dataset, __pyx_n_s_variables); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 62, __pyx_L13_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_7genexpr__pyx_v_p, __pyx_t_6, Py_EQ)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 62, __pyx_L13_error)
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      if ((__pyx_t_7 != 0)) {
        __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_dataset, __pyx_n_s_variables); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 62, __pyx_L13_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_8 = PyObject_GetItem(__pyx_t_6, __pyx_7genexpr__pyx_v_p); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 62, __pyx_L13_error)
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_3 = __pyx_t_8;
        __pyx_t_8 = 0;
      } else {
        __Pyx_INCREF(Py_None);
        __pyx_t_3 = Py_None;
      }
      if (unlikely(PyDict_SetItem(__pyx_t_2, (PyObject*)__pyx_7genexpr__pyx_v_p, (PyObject*)__pyx_t_3))) __PYX_ERR(0, 62, __pyx_L13_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_7genexpr__pyx_v_p);
    goto __pyx_L16_exit_scope;
    __pyx_L13_error:;
    __Pyx_XDECREF(__pyx_7genexpr__pyx_v_p);
    goto __pyx_L1_error;
    __pyx_L16_exit_scope:;
  } /* exit inner scope */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_data_dict, __pyx_t_2) < 0) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":64
 *         self.data_dict = {p: dataset.variables[p] if p in dataset.variables else None for p in
 *                           self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]
 *         self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in             # <<<<<<<<<<<<<<
 *                            self.variable_list_HI}  # type: Dict[str, numpy.ma.MaskedArray]
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 64, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  { /* enter inner scope */
    PyObject *__pyx_8genexpr1__pyx_v_p = NULL;
    __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 64, __pyx_L19_error)
    __Pyx_GOTREF(__pyx_t_1);

    /* "vcp_212_sails.py":65
 *                           self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]
 *         self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in
 *                            self.variable_list_HI}  # type: Dict[str, numpy.ma.MaskedArray]             # <<<<<<<<<<<<<<
 * 
 *         self.data_by_time = SortedDict()
 */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_variable_list_HI); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 65, __pyx_L19_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
      __pyx_t_8 = __pyx_t_3; __Pyx_INCREF(__pyx_t_8); __pyx_t_4 = 0;
      __pyx_t_5 = NULL;
    } else {
      __pyx_t_4 = -1; __pyx_t_8 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 65, __pyx_L19_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_5 = Py_TYPE(__pyx_t_8)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 65, __pyx_L19_error)
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    for (;;) {
      if (likely(!__pyx_t_5)) {
        if (likely(PyList_CheckExact(__pyx_t_8))) {
          if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_8)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_8, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 65, __pyx_L19_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_8, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 65, __pyx_L19_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        } else {
          if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_8)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_8, __pyx_t_4); __Pyx_INCREF(__pyx_t_3); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 65, __pyx_L19_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_8, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 65, __pyx_L19_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        }
      } else {
        __pyx_t_3 = __pyx_t_5(__pyx_t_8);
        if (unlikely(!__pyx_t_3)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 65, __pyx_L19_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_3);
      }
      __Pyx_XDECREF_SET(__pyx_8genexpr1__pyx_v_p, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "vcp_212_sails.py":64
 *         self.data_dict = {p: dataset.variables[p] if p in dataset.variables else None for p in
 *                           self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]
 *         self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in             # <<<<<<<<<<<<<<
 *                            self.variable_list_HI}  # type: Dict[str, numpy.ma.MaskedArray]
 * 
 */
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_dataset, __pyx_n_s_variables); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 64, __pyx_L19_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_7 = (__Pyx_PySequence_ContainsTF(__pyx_8genexpr1__pyx_v_p, __pyx_t_6, Py_EQ)); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 64, __pyx_L19_error)
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      if ((__pyx_t_7 != 0)) {
        __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_dataset, __pyx_n_s_variables); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 64, __pyx_L19_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_9 = PyObject_GetItem(__pyx_t_6, __pyx_8genexpr1__pyx_v_p); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 64, __pyx_L19_error)
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_3 = __pyx_t_9;
        __pyx_t_9 = 0;
      } else {
        __Pyx_INCREF(Py_None);
        __pyx_t_3 = Py_None;
      }
      if (unlikely(PyDict_SetItem(__pyx_t_1, (PyObject*)__pyx_8genexpr1__pyx_v_p, (PyObject*)__pyx_t_3))) __PYX_ERR(0, 64, __pyx_L19_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_XDECREF(__pyx_8genexpr1__pyx_v_p);
    goto __pyx_L22_exit_scope;
    __pyx_L19_error:;
    __Pyx_XDECREF(__pyx_8genexpr1__pyx_v_p);
    goto __pyx_L1_error;
    __pyx_L22_exit_scope:;
  } /* exit inner scope */
  __pyx_t_8 = PyNumber_InPlaceAdd(__pyx_t_2, __pyx_t_1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 64, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_data_dict, __pyx_t_8) < 0) __PYX_ERR(0, 64, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":67
 *                            self.variable_list_HI}  # type: Dict[str, numpy.ma.MaskedArray]
 * 
 *         self.data_by_time = SortedDict()             # <<<<<<<<<<<<<<
 *         self.elevation_by_time = SortedDict()
 * 
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_SortedDict); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 67, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
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
  if (__pyx_t_2) {
    __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 67, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_8 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 67, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_data_by_time, __pyx_t_8) < 0) __PYX_ERR(0, 67, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":68
 * 
 *         self.data_by_time = SortedDict()
 *         self.elevation_by_time = SortedDict()             # <<<<<<<<<<<<<<
 * 
 *         for k, v in self.dataset.variables.iteritems():
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_SortedDict); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 68, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
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
  if (__pyx_t_2) {
    __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 68, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_8 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 68, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_elevation_by_time, __pyx_t_8) < 0) __PYX_ERR(0, 68, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":70
 *         self.elevation_by_time = SortedDict()
 * 
 *         for k, v in self.dataset.variables.iteritems():             # <<<<<<<<<<<<<<
 *             # NOTE: Make corrections if we observe things
 *             self.data_dict[k] = self.__fix_variable__(v)
 */
  __pyx_t_4 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dataset); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 70, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_variables); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 70, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (unlikely(__pyx_t_2 == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "iteritems");
    __PYX_ERR(0, 70, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_dict_iterator(__pyx_t_2, 0, __pyx_n_s_iteritems, (&__pyx_t_10), (&__pyx_t_11)); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 70, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_XDECREF(__pyx_t_8);
  __pyx_t_8 = __pyx_t_1;
  __pyx_t_1 = 0;
  while (1) {
    __pyx_t_12 = __Pyx_dict_iter_next(__pyx_t_8, __pyx_t_10, &__pyx_t_4, &__pyx_t_1, &__pyx_t_2, NULL, __pyx_t_11);
    if (unlikely(__pyx_t_12 == 0)) break;
    if (unlikely(__pyx_t_12 == -1)) __PYX_ERR(0, 70, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_XDECREF_SET(__pyx_v_k, __pyx_t_1);
    __pyx_t_1 = 0;
    __Pyx_XDECREF_SET(__pyx_v_v, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "vcp_212_sails.py":72
 *         for k, v in self.dataset.variables.iteritems():
 *             # NOTE: Make corrections if we observe things
 *             self.data_dict[k] = self.__fix_variable__(v)             # <<<<<<<<<<<<<<
 *         # Output dictionary is contains K-V pairs to write in text format.
 *         self.output_dict = {}
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_fix_variable); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 72, __pyx_L1_error)
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
    if (!__pyx_t_3) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_v); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 72, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      __pyx_t_9 = PyTuple_New(1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 72, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_v);
      __Pyx_GIVEREF(__pyx_v_v);
      PyTuple_SET_ITEM(__pyx_t_9, 0+1, __pyx_v_v);
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_9, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 72, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 72, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (unlikely(PyObject_SetItem(__pyx_t_1, __pyx_v_k, __pyx_t_2) < 0)) __PYX_ERR(0, 72, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":74
 *             self.data_dict[k] = self.__fix_variable__(v)
 *         # Output dictionary is contains K-V pairs to write in text format.
 *         self.output_dict = {}             # <<<<<<<<<<<<<<
 * 
 *         self.is_dualpol = self.data_dict["DifferentialReflectivity"] is not None \
 */
  __pyx_t_8 = PyDict_New(); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 74, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_output_dict, __pyx_t_8) < 0) __PYX_ERR(0, 74, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":76
 *         self.output_dict = {}
 * 
 *         self.is_dualpol = self.data_dict["DifferentialReflectivity"] is not None \             # <<<<<<<<<<<<<<
 *                           or self.data_dict["DifferentialReflectivity_HI"] is not None
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 76, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyObject_GetItem(__pyx_t_2, __pyx_n_s_DifferentialReflectivity); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 76, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_7 = (__pyx_t_1 != Py_None);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (!__pyx_t_7) {
  } else {
    __pyx_t_1 = __Pyx_PyBool_FromLong(__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 76, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = __pyx_t_1;
    __pyx_t_1 = 0;
    goto __pyx_L25_bool_binop_done;
  }

  /* "vcp_212_sails.py":77
 * 
 *         self.is_dualpol = self.data_dict["DifferentialReflectivity"] is not None \
 *                           or self.data_dict["DifferentialReflectivity_HI"] is not None             # <<<<<<<<<<<<<<
 * 
 *         self.order_data()
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 77, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetItem(__pyx_t_1, __pyx_n_s_DifferentialReflectivity_HI); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 77, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_7 = (__pyx_t_2 != Py_None);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyBool_FromLong(__pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 77, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_8 = __pyx_t_2;
  __pyx_t_2 = 0;
  __pyx_L25_bool_binop_done:;

  /* "vcp_212_sails.py":76
 *         self.output_dict = {}
 * 
 *         self.is_dualpol = self.data_dict["DifferentialReflectivity"] is not None \             # <<<<<<<<<<<<<<
 *                           or self.data_dict["DifferentialReflectivity_HI"] is not None
 * 
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_is_dualpol, __pyx_t_8) < 0) __PYX_ERR(0, 76, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":79
 *                           or self.data_dict["DifferentialReflectivity_HI"] is not None
 * 
 *         self.order_data()             # <<<<<<<<<<<<<<
 * 
 *     def tag_elevation(self):
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_order_data); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 79, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_1) {
    __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 79, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  } else {
    __pyx_t_8 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 79, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "vcp_212_sails.py":49
 *             return v[:]
 * 
 *     def __init__(self, dataset: Dataset):             # <<<<<<<<<<<<<<
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
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_k);
  __Pyx_XDECREF(__pyx_v_v);
  __Pyx_XDECREF(__pyx_v_p);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":81
 *         self.order_data()
 * 
 *     def tag_elevation(self):             # <<<<<<<<<<<<<<
 *         # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_5tag_elevation(PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_5tag_elevation = {"tag_elevation", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_5tag_elevation, METH_O, 0};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_5tag_elevation(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("tag_elevation (wrapper)", 0);
  __pyx_r = __pyx_pf_13vcp_212_sails_6Vcp212_4tag_elevation(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_4tag_elevation(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_v_j = NULL;
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  PyObject *(*__pyx_t_7)(PyObject *);
  int __pyx_t_8;
  __Pyx_RefNannySetupContext("tag_elevation", 0);

  /* "vcp_212_sails.py":83
 *     def tag_elevation(self):
 *         # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)             # <<<<<<<<<<<<<<
 *         j = 0
 *         for i in range(0, self.normalized_elevation.shape[0]):
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 83, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_zeros_like); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 83, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_normalized_elevation); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 83, __pyx_L1_error)
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
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 83, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 83, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 83, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_is_sails, __pyx_t_1) < 0) __PYX_ERR(0, 83, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":84
 *         # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
 *         j = 0             # <<<<<<<<<<<<<<
 *         for i in range(0, self.normalized_elevation.shape[0]):
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1
 */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_v_j = __pyx_int_0;

  /* "vcp_212_sails.py":85
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
 *         j = 0
 *         for i in range(0, self.normalized_elevation.shape[0]):             # <<<<<<<<<<<<<<
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1
 *                 self.is_sails[i] = 0
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_normalized_elevation); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 85, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_shape); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 85, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 85, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 85, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(__pyx_int_0);
  __Pyx_GIVEREF(__pyx_int_0);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_int_0);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 85, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_3 = __pyx_t_1; __Pyx_INCREF(__pyx_t_3); __pyx_t_6 = 0;
    __pyx_t_7 = NULL;
  } else {
    __pyx_t_6 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 85, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_7 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 85, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_7)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_6 >= PyList_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_6); __Pyx_INCREF(__pyx_t_1); __pyx_t_6++; if (unlikely(0 < 0)) __PYX_ERR(0, 85, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_6); __pyx_t_6++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 85, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      } else {
        if (__pyx_t_6 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_6); __Pyx_INCREF(__pyx_t_1); __pyx_t_6++; if (unlikely(0 < 0)) __PYX_ERR(0, 85, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_6); __pyx_t_6++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 85, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_7(__pyx_t_3);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 85, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    __Pyx_XDECREF_SET(__pyx_v_i, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "vcp_212_sails.py":86
 *         j = 0
 *         for i in range(0, self.normalized_elevation.shape[0]):
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1             # <<<<<<<<<<<<<<
 *                 self.is_sails[i] = 0
 *                 j += 1
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_normalized_elevation); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = PyObject_GetItem(__pyx_t_1, __pyx_v_i); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_ScanTable); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyObject_GetItem(__pyx_t_1, __pyx_v_j); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyNumber_Subtract(__pyx_t_5, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyNumber_Absolute(__pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_RichCompare(__pyx_t_2, __pyx_float_0_1, Py_LE); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (__pyx_t_8) {

      /* "vcp_212_sails.py":87
 *         for i in range(0, self.normalized_elevation.shape[0]):
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1
 *                 self.is_sails[i] = 0             # <<<<<<<<<<<<<<
 *                 j += 1
 *             else:
 */
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_is_sails); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 87, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (unlikely(PyObject_SetItem(__pyx_t_1, __pyx_v_i, __pyx_int_0) < 0)) __PYX_ERR(0, 87, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

      /* "vcp_212_sails.py":88
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1
 *                 self.is_sails[i] = 0
 *                 j += 1             # <<<<<<<<<<<<<<
 *             else:
 *                 self.is_sails[i] = 1
 */
      __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_j, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 88, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF_SET(__pyx_v_j, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "vcp_212_sails.py":86
 *         j = 0
 *         for i in range(0, self.normalized_elevation.shape[0]):
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1             # <<<<<<<<<<<<<<
 *                 self.is_sails[i] = 0
 *                 j += 1
 */
      goto __pyx_L5;
    }

    /* "vcp_212_sails.py":90
 *                 j += 1
 *             else:
 *                 self.is_sails[i] = 1             # <<<<<<<<<<<<<<
 * 
 *     def link_data_to_time(self):
 */
    /*else*/ {
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_is_sails); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 90, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (unlikely(PyObject_SetItem(__pyx_t_1, __pyx_v_i, __pyx_int_1) < 0)) __PYX_ERR(0, 90, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    }
    __pyx_L5:;

    /* "vcp_212_sails.py":85
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
 *         j = 0
 *         for i in range(0, self.normalized_elevation.shape[0]):             # <<<<<<<<<<<<<<
 *             if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1
 *                 self.is_sails[i] = 0
 */
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "vcp_212_sails.py":81
 *         self.order_data()
 * 
 *     def tag_elevation(self):             # <<<<<<<<<<<<<<
 *         # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
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
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.tag_elevation", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_j);
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":92
 *                 self.is_sails[i] = 1
 * 
 *     def link_data_to_time(self):             # <<<<<<<<<<<<<<
 *         if self.sorted_timeR.shape == self.sorted_timeV.shape:
 *             # Means there is no reflectivity scan for CD scan
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_7link_data_to_time(PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_7link_data_to_time = {"link_data_to_time", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_7link_data_to_time, METH_O, 0};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_7link_data_to_time(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("link_data_to_time (wrapper)", 0);
  __pyx_r = __pyx_pf_13vcp_212_sails_6Vcp212_6link_data_to_time(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_6link_data_to_time(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_v_t = NULL;
  PyObject *__pyx_v_time_value = NULL;
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  PyObject *(*__pyx_t_6)(PyObject *);
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  Py_ssize_t __pyx_t_9;
  PyObject *__pyx_t_10 = NULL;
  __Pyx_RefNannySetupContext("link_data_to_time", 0);

  /* "vcp_212_sails.py":93
 * 
 *     def link_data_to_time(self):
 *         if self.sorted_timeR.shape == self.sorted_timeV.shape:             # <<<<<<<<<<<<<<
 *             # Means there is no reflectivity scan for CD scan
 *             pass
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_sorted_timeR); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_shape); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_sorted_timeV); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_shape); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_RichCompare(__pyx_t_2, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 93, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__pyx_t_4) {
    goto __pyx_L3;
  }

  /* "vcp_212_sails.py":97
 *             pass
 *         else:
 *             for t in self.time_vars:             # <<<<<<<<<<<<<<
 *                 if t not in self.dataset.variables:
 *                     continue
 */
  /*else*/ {
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_time_vars); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
      __pyx_t_3 = __pyx_t_1; __Pyx_INCREF(__pyx_t_3); __pyx_t_5 = 0;
      __pyx_t_6 = NULL;
    } else {
      __pyx_t_5 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_6 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 97, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    for (;;) {
      if (likely(!__pyx_t_6)) {
        if (likely(PyList_CheckExact(__pyx_t_3))) {
          if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_3)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_5); __Pyx_INCREF(__pyx_t_1); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(0, 97, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        } else {
          if (__pyx_t_5 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_5); __Pyx_INCREF(__pyx_t_1); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(0, 97, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        }
      } else {
        __pyx_t_1 = __pyx_t_6(__pyx_t_3);
        if (unlikely(!__pyx_t_1)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 97, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_1);
      }
      __Pyx_XDECREF_SET(__pyx_v_t, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "vcp_212_sails.py":98
 *         else:
 *             for t in self.time_vars:
 *                 if t not in self.dataset.variables:             # <<<<<<<<<<<<<<
 *                     continue
 *                 time_value = self.dataset.variables[t][:].min(axis=1)
 */
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dataset); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 98, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_variables); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 98, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_4 = (__Pyx_PySequence_ContainsTF(__pyx_v_t, __pyx_t_2, Py_NE)); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 98, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_7 = (__pyx_t_4 != 0);
      if (__pyx_t_7) {

        /* "vcp_212_sails.py":99
 *             for t in self.time_vars:
 *                 if t not in self.dataset.variables:
 *                     continue             # <<<<<<<<<<<<<<
 *                 time_value = self.dataset.variables[t][:].min(axis=1)
 *                 for i in list(time_value):
 */
        goto __pyx_L4_continue;

        /* "vcp_212_sails.py":98
 *         else:
 *             for t in self.time_vars:
 *                 if t not in self.dataset.variables:             # <<<<<<<<<<<<<<
 *                     continue
 *                 time_value = self.dataset.variables[t][:].min(axis=1)
 */
      }

      /* "vcp_212_sails.py":100
 *                 if t not in self.dataset.variables:
 *                     continue
 *                 time_value = self.dataset.variables[t][:].min(axis=1)             # <<<<<<<<<<<<<<
 *                 for i in list(time_value):
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]
 */
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dataset); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_variables); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PyObject_GetItem(__pyx_t_1, __pyx_v_t); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = __Pyx_PyObject_GetSlice(__pyx_t_2, 0, 0, NULL, NULL, &__pyx_slice__5, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_min); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 100, __pyx_L1_error)
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_empty_tuple, __pyx_t_1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 100, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_XDECREF_SET(__pyx_v_time_value, __pyx_t_8);
      __pyx_t_8 = 0;

      /* "vcp_212_sails.py":101
 *                     continue
 *                 time_value = self.dataset.variables[t][:].min(axis=1)
 *                 for i in list(time_value):             # <<<<<<<<<<<<<<
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]
 *                     self.elevation_by_time[i] = self.data_by_time['elevationR'][i].mean().round(1)
 */
      __pyx_t_8 = PySequence_List(__pyx_v_time_value); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 101, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_1 = __pyx_t_8; __Pyx_INCREF(__pyx_t_1); __pyx_t_9 = 0;
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      for (;;) {
        if (__pyx_t_9 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_8 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_9); __Pyx_INCREF(__pyx_t_8); __pyx_t_9++; if (unlikely(0 < 0)) __PYX_ERR(0, 101, __pyx_L1_error)
        #else
        __pyx_t_8 = PySequence_ITEM(__pyx_t_1, __pyx_t_9); __pyx_t_9++; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 101, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        #endif
        __Pyx_XDECREF_SET(__pyx_v_i, __pyx_t_8);
        __pyx_t_8 = 0;

        /* "vcp_212_sails.py":102
 *                 time_value = self.dataset.variables[t][:].min(axis=1)
 *                 for i in list(time_value):
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]             # <<<<<<<<<<<<<<
 *                     self.elevation_by_time[i] = self.data_by_time['elevationR'][i].mean().round(1)
 * 
 */
        __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_dict); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 102, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __pyx_t_2 = PyObject_GetItem(__pyx_t_8, __pyx_n_s_Reflectivity); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 102, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
        __pyx_t_8 = PyObject_GetItem(__pyx_t_2, __pyx_v_i); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 102, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_by_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 102, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        if (unlikely(PyObject_SetItem(__pyx_t_2, __pyx_v_i, __pyx_t_8) < 0)) __PYX_ERR(0, 102, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

        /* "vcp_212_sails.py":103
 *                 for i in list(time_value):
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]
 *                     self.elevation_by_time[i] = self.data_by_time['elevationR'][i].mean().round(1)             # <<<<<<<<<<<<<<
 * 
 *             pass
 */
        __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_data_by_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_10 = PyObject_GetItem(__pyx_t_2, __pyx_n_s_elevationR); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __pyx_t_2 = PyObject_GetItem(__pyx_t_10, __pyx_v_i); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_mean); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __pyx_t_2 = NULL;
        if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_10))) {
          __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_10);
          if (likely(__pyx_t_2)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_10);
            __Pyx_INCREF(__pyx_t_2);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_10, function);
          }
        }
        if (__pyx_t_2) {
          __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_10, __pyx_t_2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 103, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        } else {
          __pyx_t_8 = __Pyx_PyObject_CallNoArg(__pyx_t_10); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 103, __pyx_L1_error)
        }
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_round); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
        __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_10, __pyx_tuple__6, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_elevation_by_time); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        if (unlikely(PyObject_SetItem(__pyx_t_10, __pyx_v_i, __pyx_t_8) < 0)) __PYX_ERR(0, 103, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

        /* "vcp_212_sails.py":101
 *                     continue
 *                 time_value = self.dataset.variables[t][:].min(axis=1)
 *                 for i in list(time_value):             # <<<<<<<<<<<<<<
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]
 *                     self.elevation_by_time[i] = self.data_by_time['elevationR'][i].mean().round(1)
 */
      }
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

      /* "vcp_212_sails.py":97
 *             pass
 *         else:
 *             for t in self.time_vars:             # <<<<<<<<<<<<<<
 *                 if t not in self.dataset.variables:
 *                     continue
 */
      __pyx_L4_continue:;
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __pyx_L3:;

  /* "vcp_212_sails.py":92
 *                 self.is_sails[i] = 1
 * 
 *     def link_data_to_time(self):             # <<<<<<<<<<<<<<
 *         if self.sorted_timeR.shape == self.sorted_timeV.shape:
 *             # Means there is no reflectivity scan for CD scan
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.link_data_to_time", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_t);
  __Pyx_XDECREF(__pyx_v_time_value);
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":108
 * 
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_9output2file(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_9output2file = {"output2file", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_9output2file, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_9output2file(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
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
          __Pyx_RaiseArgtupleInvalid("output2file", 1, 3, 3, 1); __PYX_ERR(0, 108, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_coordinate)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("output2file", 1, 3, 3, 2); __PYX_ERR(0, 108, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "output2file") < 0)) __PYX_ERR(0, 108, __pyx_L3_error)
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
  __Pyx_RaiseArgtupleInvalid("output2file", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 108, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.output2file", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_13vcp_212_sails_6Vcp212_8output2file(__pyx_self, __pyx_v_self, __pyx_v_path, __pyx_v_coordinate);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_8output2file(CYTHON_UNUSED PyObject *__pyx_self, CYTHON_UNUSED PyObject *__pyx_v_self, PyObject *__pyx_v_path, PyObject *__pyx_v_coordinate) {
  PyObject *__pyx_v_f = NULL;
  PyObject *__pyx_v_point = NULL;
  PyObject *__pyx_v_attri = NULL;
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

  /* "vcp_212_sails.py":109
 * 
 *     def output2file(self, path, coordinate):
 *         print("start output...")             # <<<<<<<<<<<<<<
 *         f = open(path, 'w')
 *         for point, attri in coordinate.items():
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s_start_output) < 0) __PYX_ERR(0, 109, __pyx_L1_error)

  /* "vcp_212_sails.py":110
 *     def output2file(self, path, coordinate):
 *         print("start output...")
 *         f = open(path, 'w')             # <<<<<<<<<<<<<<
 *         for point, attri in coordinate.items():
 *             f.write(str(point))
 */
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 110, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_path);
  __Pyx_GIVEREF(__pyx_v_path);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_path);
  __Pyx_INCREF(__pyx_n_s_w);
  __Pyx_GIVEREF(__pyx_n_s_w);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_w);
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_1, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 110, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_f = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "vcp_212_sails.py":111
 *         print("start output...")
 *         f = open(path, 'w')
 *         for point, attri in coordinate.items():             # <<<<<<<<<<<<<<
 *             f.write(str(point))
 *             f.write(' ')
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_coordinate, __pyx_n_s_items); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 111, __pyx_L1_error)
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
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 111, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 111, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (likely(PyList_CheckExact(__pyx_t_2)) || PyTuple_CheckExact(__pyx_t_2)) {
    __pyx_t_1 = __pyx_t_2; __Pyx_INCREF(__pyx_t_1); __pyx_t_4 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_4 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 111, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 111, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  for (;;) {
    if (likely(!__pyx_t_5)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_4 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_2); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 111, __pyx_L1_error)
        #else
        __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 111, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        #endif
      } else {
        if (__pyx_t_4 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_2 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_4); __Pyx_INCREF(__pyx_t_2); __pyx_t_4++; if (unlikely(0 < 0)) __PYX_ERR(0, 111, __pyx_L1_error)
        #else
        __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_4); __pyx_t_4++; if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 111, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        #endif
      }
    } else {
      __pyx_t_2 = __pyx_t_5(__pyx_t_1);
      if (unlikely(!__pyx_t_2)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 111, __pyx_L1_error)
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
        __PYX_ERR(0, 111, __pyx_L1_error)
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
      __pyx_t_3 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 111, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_6 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 111, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      #endif
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_7 = PyObject_GetIter(__pyx_t_2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 111, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_8 = Py_TYPE(__pyx_t_7)->tp_iternext;
      index = 0; __pyx_t_3 = __pyx_t_8(__pyx_t_7); if (unlikely(!__pyx_t_3)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_3);
      index = 1; __pyx_t_6 = __pyx_t_8(__pyx_t_7); if (unlikely(!__pyx_t_6)) goto __pyx_L5_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_6);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_8(__pyx_t_7), 2) < 0) __PYX_ERR(0, 111, __pyx_L1_error)
      __pyx_t_8 = NULL;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      goto __pyx_L6_unpacking_done;
      __pyx_L5_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 111, __pyx_L1_error)
      __pyx_L6_unpacking_done:;
    }
    __Pyx_XDECREF_SET(__pyx_v_point, __pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_XDECREF_SET(__pyx_v_attri, __pyx_t_6);
    __pyx_t_6 = 0;

    /* "vcp_212_sails.py":112
 *         f = open(path, 'w')
 *         for point, attri in coordinate.items():
 *             f.write(str(point))             # <<<<<<<<<<<<<<
 *             f.write(' ')
 *             for variable, value in attri.items():
 */
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 112, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 112, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_v_point);
    __Pyx_GIVEREF(__pyx_v_point);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_point);
    __pyx_t_7 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_3, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 112, __pyx_L1_error)
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
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      __pyx_t_9 = PyTuple_New(1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_GIVEREF(__pyx_t_7);
      PyTuple_SET_ITEM(__pyx_t_9, 0+1, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_9, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "vcp_212_sails.py":113
 *         for point, attri in coordinate.items():
 *             f.write(str(point))
 *             f.write(' ')             # <<<<<<<<<<<<<<
 *             for variable, value in attri.items():
 *                 f.write(variable)
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__8, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "vcp_212_sails.py":114
 *             f.write(str(point))
 *             f.write(' ')
 *             for variable, value in attri.items():             # <<<<<<<<<<<<<<
 *                 f.write(variable)
 *                 f.write(':')
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_attri, __pyx_n_s_items); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 114, __pyx_L1_error)
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
      __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_9); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 114, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    } else {
      __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 114, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (likely(PyList_CheckExact(__pyx_t_6)) || PyTuple_CheckExact(__pyx_t_6)) {
      __pyx_t_2 = __pyx_t_6; __Pyx_INCREF(__pyx_t_2); __pyx_t_10 = 0;
      __pyx_t_11 = NULL;
    } else {
      __pyx_t_10 = -1; __pyx_t_2 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 114, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_11 = Py_TYPE(__pyx_t_2)->tp_iternext; if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 114, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    for (;;) {
      if (likely(!__pyx_t_11)) {
        if (likely(PyList_CheckExact(__pyx_t_2))) {
          if (__pyx_t_10 >= PyList_GET_SIZE(__pyx_t_2)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_6 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_10); __Pyx_INCREF(__pyx_t_6); __pyx_t_10++; if (unlikely(0 < 0)) __PYX_ERR(0, 114, __pyx_L1_error)
          #else
          __pyx_t_6 = PySequence_ITEM(__pyx_t_2, __pyx_t_10); __pyx_t_10++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 114, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          #endif
        } else {
          if (__pyx_t_10 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
          #if CYTHON_COMPILING_IN_CPYTHON
          __pyx_t_6 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_10); __Pyx_INCREF(__pyx_t_6); __pyx_t_10++; if (unlikely(0 < 0)) __PYX_ERR(0, 114, __pyx_L1_error)
          #else
          __pyx_t_6 = PySequence_ITEM(__pyx_t_2, __pyx_t_10); __pyx_t_10++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 114, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          #endif
        }
      } else {
        __pyx_t_6 = __pyx_t_11(__pyx_t_2);
        if (unlikely(!__pyx_t_6)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 114, __pyx_L1_error)
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
          __PYX_ERR(0, 114, __pyx_L1_error)
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
        __pyx_t_9 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 114, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __pyx_t_7 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 114, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        #endif
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else {
        Py_ssize_t index = -1;
        __pyx_t_3 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 114, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_8 = Py_TYPE(__pyx_t_3)->tp_iternext;
        index = 0; __pyx_t_9 = __pyx_t_8(__pyx_t_3); if (unlikely(!__pyx_t_9)) goto __pyx_L9_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_9);
        index = 1; __pyx_t_7 = __pyx_t_8(__pyx_t_3); if (unlikely(!__pyx_t_7)) goto __pyx_L9_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_7);
        if (__Pyx_IternextUnpackEndCheck(__pyx_t_8(__pyx_t_3), 2) < 0) __PYX_ERR(0, 114, __pyx_L1_error)
        __pyx_t_8 = NULL;
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        goto __pyx_L10_unpacking_done;
        __pyx_L9_unpacking_failed:;
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_8 = NULL;
        if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
        __PYX_ERR(0, 114, __pyx_L1_error)
        __pyx_L10_unpacking_done:;
      }
      __Pyx_XDECREF_SET(__pyx_v_variable, __pyx_t_9);
      __pyx_t_9 = 0;
      __Pyx_XDECREF_SET(__pyx_v_value, __pyx_t_7);
      __pyx_t_7 = 0;

      /* "vcp_212_sails.py":115
 *             f.write(' ')
 *             for variable, value in attri.items():
 *                 f.write(variable)             # <<<<<<<<<<<<<<
 *                 f.write(':')
 *                 f.write(str(value))
 */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 115, __pyx_L1_error)
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
        __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_v_variable); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 115, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
      } else {
        __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 115, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_9); __pyx_t_9 = NULL;
        __Pyx_INCREF(__pyx_v_variable);
        __Pyx_GIVEREF(__pyx_v_variable);
        PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_variable);
        __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_3, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 115, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      }
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

      /* "vcp_212_sails.py":116
 *             for variable, value in attri.items():
 *                 f.write(variable)
 *                 f.write(':')             # <<<<<<<<<<<<<<
 *                 f.write(str(value))
 *                 f.write(' ')
 */
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 116, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_tuple__10, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 116, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

      /* "vcp_212_sails.py":117
 *                 f.write(variable)
 *                 f.write(':')
 *                 f.write(str(value))             # <<<<<<<<<<<<<<
 *                 f.write(' ')
 *             f.write('\n')
 */
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 117, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 117, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_INCREF(__pyx_v_value);
      __Pyx_GIVEREF(__pyx_v_value);
      PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_value);
      __pyx_t_9 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_3, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 117, __pyx_L1_error)
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
        __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_9); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 117, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_7);
      } else {
        __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 117, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_3); __pyx_t_3 = NULL;
        __Pyx_GIVEREF(__pyx_t_9);
        PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_t_9);
        __pyx_t_9 = 0;
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_12, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 117, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
      }
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

      /* "vcp_212_sails.py":118
 *                 f.write(':')
 *                 f.write(str(value))
 *                 f.write(' ')             # <<<<<<<<<<<<<<
 *             f.write('\n')
 *         f.close()
 */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__11, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

      /* "vcp_212_sails.py":114
 *             f.write(str(point))
 *             f.write(' ')
 *             for variable, value in attri.items():             # <<<<<<<<<<<<<<
 *                 f.write(variable)
 *                 f.write(':')
 */
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "vcp_212_sails.py":119
 *                 f.write(str(value))
 *                 f.write(' ')
 *             f.write('\n')             # <<<<<<<<<<<<<<
 *         f.close()
 *         print("finish output")
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_write); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 119, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__13, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 119, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "vcp_212_sails.py":111
 *         print("start output...")
 *         f = open(path, 'w')
 *         for point, attri in coordinate.items():             # <<<<<<<<<<<<<<
 *             f.write(str(point))
 *             f.write(' ')
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":120
 *                 f.write(' ')
 *             f.write('\n')
 *         f.close()             # <<<<<<<<<<<<<<
 *         print("finish output")
 * 
 */
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_f, __pyx_n_s_close); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 120, __pyx_L1_error)
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
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 120, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":121
 *             f.write('\n')
 *         f.close()
 *         print("finish output")             # <<<<<<<<<<<<<<
 * 
 *     def order_data(self):
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s_finish_output) < 0) __PYX_ERR(0, 121, __pyx_L1_error)

  /* "vcp_212_sails.py":108
 * 
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
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.output2file", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_f);
  __Pyx_XDECREF(__pyx_v_point);
  __Pyx_XDECREF(__pyx_v_attri);
  __Pyx_XDECREF(__pyx_v_variable);
  __Pyx_XDECREF(__pyx_v_value);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vcp_212_sails.py":123
 *         print("finish output")
 * 
 *     def order_data(self):             # <<<<<<<<<<<<<<
 *         """Restore the order of data, by scanning start time."""
 *         # Scan start time at each elevation.
 */

/* Python wrapper */
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_11order_data(PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static char __pyx_doc_13vcp_212_sails_6Vcp212_10order_data[] = "Restore the order of data, by scanning start time.";
static PyMethodDef __pyx_mdef_13vcp_212_sails_6Vcp212_11order_data = {"order_data", (PyCFunction)__pyx_pw_13vcp_212_sails_6Vcp212_11order_data, METH_O, __pyx_doc_13vcp_212_sails_6Vcp212_10order_data};
static PyObject *__pyx_pw_13vcp_212_sails_6Vcp212_11order_data(PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("order_data (wrapper)", 0);
  __pyx_r = __pyx_pf_13vcp_212_sails_6Vcp212_10order_data(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13vcp_212_sails_6Vcp212_10order_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self) {
  PyObject *__pyx_v_ds = NULL;
  PyObject *__pyx_v_start_timeR = NULL;
  PyObject *__pyx_v_start_timeR_HI = NULL;
  PyObject *__pyx_v_timeR_sort = NULL;
  PyObject *__pyx_v_elevationR = NULL;
  PyObject *__pyx_v_elevationR_HI = NULL;
  PyObject *__pyx_v_all_elevationR = NULL;
  PyObject *__pyx_v_sorted_elevationR = NULL;
  PyObject *__pyx_v_start_timeV = NULL;
  PyObject *__pyx_v_start_timeV_HI = NULL;
  PyObject *__pyx_v_timeV_sort = NULL;
  PyObject *__pyx_v_rm = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  __Pyx_RefNannySetupContext("order_data", 0);

  /* "vcp_212_sails.py":126
 *         """Restore the order of data, by scanning start time."""
 *         # Scan start time at each elevation.
 *         ds = self.dataset             # <<<<<<<<<<<<<<
 *         start_timeR = ds.variables['timeR'][:].min(axis=1)
 *         # If there is high resolution data, merge it
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_dataset); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 126, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_ds = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "vcp_212_sails.py":127
 *         # Scan start time at each elevation.
 *         ds = self.dataset
 *         start_timeR = ds.variables['timeR'][:].min(axis=1)             # <<<<<<<<<<<<<<
 *         # If there is high resolution data, merge it
 *         start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_ds, __pyx_n_s_variables); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetItem(__pyx_t_1, __pyx_n_s_timeR); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetSlice(__pyx_t_2, 0, 0, NULL, NULL, &__pyx_slice__14, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_min); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 127, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_empty_tuple, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_start_timeR = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "vcp_212_sails.py":129
 *         start_timeR = ds.variables['timeR'][:].min(axis=1)
 *         # If there is high resolution data, merge it
 *         start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []             # <<<<<<<<<<<<<<
 *         timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()
 *         self.ref_sort_order = timeR_sort
 */
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_ds, __pyx_n_s_variables); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = PyObject_GetItem(__pyx_t_3, __pyx_n_s_timeR_HI); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetSlice(__pyx_t_1, 0, 0, NULL, NULL, &__pyx_slice__15, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_min); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 129, __pyx_L1_error)
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_empty_tuple, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_start_timeR_HI = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "vcp_212_sails.py":130
 *         # If there is high resolution data, merge it
 *         start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 *         timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()             # <<<<<<<<<<<<<<
 *         self.ref_sort_order = timeR_sort
 *         self.sorted_timeR = numpy.concatenate((start_timeR, start_timeR_HI)).sort()
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_start_timeR);
  __Pyx_GIVEREF(__pyx_v_start_timeR);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_start_timeR);
  __Pyx_INCREF(__pyx_v_start_timeR_HI);
  __Pyx_GIVEREF(__pyx_v_start_timeR_HI);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_start_timeR_HI);
  __pyx_t_5 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 130, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_3);
  } else {
    __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 130, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_5); __pyx_t_5 = NULL;
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_6, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 130, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_argsort); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 130, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 130, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 130, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_v_timeR_sort = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "vcp_212_sails.py":131
 *         start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 *         timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()
 *         self.ref_sort_order = timeR_sort             # <<<<<<<<<<<<<<
 *         self.sorted_timeR = numpy.concatenate((start_timeR, start_timeR_HI)).sort()
 * 
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_ref_sort_order, __pyx_v_timeR_sort) < 0) __PYX_ERR(0, 131, __pyx_L1_error)

  /* "vcp_212_sails.py":132
 *         timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()
 *         self.ref_sort_order = timeR_sort
 *         self.sorted_timeR = numpy.concatenate((start_timeR, start_timeR_HI)).sort()             # <<<<<<<<<<<<<<
 * 
 *         # ElevationR
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(__pyx_v_start_timeR);
  __Pyx_GIVEREF(__pyx_v_start_timeR);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_start_timeR);
  __Pyx_INCREF(__pyx_v_start_timeR_HI);
  __Pyx_GIVEREF(__pyx_v_start_timeR_HI);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_v_start_timeR_HI);
  __pyx_t_1 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_6))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_6);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_6, function);
    }
  }
  if (!__pyx_t_1) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 132, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 132, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1); __pyx_t_1 = NULL;
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 132, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_sort); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_6))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_6);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_6, function);
    }
  }
  if (__pyx_t_4) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 132, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else {
    __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_6); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 132, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_sorted_timeR, __pyx_t_2) < 0) __PYX_ERR(0, 132, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":135
 * 
 *         # ElevationR
 *         elevationR = ds.variables['elevationR'][:].mean(axis=1)             # <<<<<<<<<<<<<<
 *         elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 *         all_elevationR = numpy.concatenate((elevationR, elevationR_HI))
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_ds, __pyx_n_s_variables); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = PyObject_GetItem(__pyx_t_2, __pyx_n_s_elevationR); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetSlice(__pyx_t_6, 0, 0, NULL, NULL, &__pyx_slice__16, 0, 0, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_mean); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 135, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_empty_tuple, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_elevationR = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "vcp_212_sails.py":136
 *         # ElevationR
 *         elevationR = ds.variables['elevationR'][:].mean(axis=1)
 *         elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []             # <<<<<<<<<<<<<<
 *         all_elevationR = numpy.concatenate((elevationR, elevationR_HI))
 *         sorted_elevationR = all_elevationR[timeR_sort]
 */
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_ds, __pyx_n_s_variables); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyObject_GetItem(__pyx_t_4, __pyx_n_s_elevationR_HI); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetSlice(__pyx_t_2, 0, 0, NULL, NULL, &__pyx_slice__17, 0, 0, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_mean); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 136, __pyx_L1_error)
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_empty_tuple, __pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_v_elevationR_HI = __pyx_t_6;
  __pyx_t_6 = 0;

  /* "vcp_212_sails.py":137
 *         elevationR = ds.variables['elevationR'][:].mean(axis=1)
 *         elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 *         all_elevationR = numpy.concatenate((elevationR, elevationR_HI))             # <<<<<<<<<<<<<<
 *         sorted_elevationR = all_elevationR[timeR_sort]
 * 
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_INCREF(__pyx_v_elevationR);
  __Pyx_GIVEREF(__pyx_v_elevationR);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_elevationR);
  __Pyx_INCREF(__pyx_v_elevationR_HI);
  __Pyx_GIVEREF(__pyx_v_elevationR_HI);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_v_elevationR_HI);
  __pyx_t_5 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 137, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_6);
  } else {
    __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 137, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5); __pyx_t_5 = NULL;
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 137, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_all_elevationR = __pyx_t_6;
  __pyx_t_6 = 0;

  /* "vcp_212_sails.py":138
 *         elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 *         all_elevationR = numpy.concatenate((elevationR, elevationR_HI))
 *         sorted_elevationR = all_elevationR[timeR_sort]             # <<<<<<<<<<<<<<
 * 
 *         # Once we get sorted elevation, we should extract SAILS elevations.
 */
  __pyx_t_6 = PyObject_GetItem(__pyx_v_all_elevationR, __pyx_v_timeR_sort); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 138, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_v_sorted_elevationR = __pyx_t_6;
  __pyx_t_6 = 0;

  /* "vcp_212_sails.py":142
 *         # Once we get sorted elevation, we should extract SAILS elevations.
 *         # Problem is, how can we deal with these elevations
 *         self.normalized_elevation = sorted_elevationR.round(1)  # type: numpy.ma.MaskedArray             # <<<<<<<<<<<<<<
 * 
 *         # Then we check if elevationV is all included in elevationR.
 */
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_sorted_elevationR, __pyx_n_s_round); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_tuple__18, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_normalized_elevation, __pyx_t_2) < 0) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":146
 *         # Then we check if elevationV is all included in elevationR.
 *         # If true, means CD contains reflectivity data, we need drop them, if false, we merge velocity data
 *         start_timeV = ds.variables['timeV'][:].min(axis=1)             # <<<<<<<<<<<<<<
 *         start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_ds, __pyx_n_s_variables); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = PyObject_GetItem(__pyx_t_2, __pyx_n_s_timeV); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetSlice(__pyx_t_6, 0, 0, NULL, NULL, &__pyx_slice__19, 0, 0, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_min); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 146, __pyx_L1_error)
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_empty_tuple, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_start_timeV = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "vcp_212_sails.py":147
 *         # If true, means CD contains reflectivity data, we need drop them, if false, we merge velocity data
 *         start_timeV = ds.variables['timeV'][:].min(axis=1)
 *         start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)             # <<<<<<<<<<<<<<
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
 *         self.vel_sort_order = timeV_sort
 */
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_ds, __pyx_n_s_variables); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyObject_GetItem(__pyx_t_3, __pyx_n_s_timeV_HI); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetSlice(__pyx_t_2, 0, 0, NULL, NULL, &__pyx_slice__20, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_min); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_axis, __pyx_int_1) < 0) __PYX_ERR(0, 147, __pyx_L1_error)
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_empty_tuple, __pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_start_timeV_HI = __pyx_t_6;
  __pyx_t_6 = 0;

  /* "vcp_212_sails.py":148
 *         start_timeV = ds.variables['timeV'][:].min(axis=1)
 *         start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()             # <<<<<<<<<<<<<<
 *         self.vel_sort_order = timeV_sort
 *         self.sorted_timeV = numpy.concatenate((start_timeV, start_timeV_HI)).sort()
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_start_timeV);
  __Pyx_GIVEREF(__pyx_v_start_timeV);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_start_timeV);
  __Pyx_INCREF(__pyx_v_start_timeV_HI);
  __Pyx_GIVEREF(__pyx_v_start_timeV_HI);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_v_start_timeV_HI);
  __pyx_t_5 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_3);
  } else {
    __pyx_t_1 = PyTuple_New(1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_5); __pyx_t_5 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_1, 0+1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_argsort); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 148, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_v_timeV_sort = __pyx_t_6;
  __pyx_t_6 = 0;

  /* "vcp_212_sails.py":149
 *         start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
 *         self.vel_sort_order = timeV_sort             # <<<<<<<<<<<<<<
 *         self.sorted_timeV = numpy.concatenate((start_timeV, start_timeV_HI)).sort()
 * 
 */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_vel_sort_order, __pyx_v_timeV_sort) < 0) __PYX_ERR(0, 149, __pyx_L1_error)

  /* "vcp_212_sails.py":150
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
 *         self.vel_sort_order = timeV_sort
 *         self.sorted_timeV = numpy.concatenate((start_timeV, start_timeV_HI)).sort()             # <<<<<<<<<<<<<<
 * 
 *         if timeR_sort.shape[0] != timeV_sort.shape[0]:
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 150, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 150, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 150, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(__pyx_v_start_timeV);
  __Pyx_GIVEREF(__pyx_v_start_timeV);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_start_timeV);
  __Pyx_INCREF(__pyx_v_start_timeV_HI);
  __Pyx_GIVEREF(__pyx_v_start_timeV_HI);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_v_start_timeV_HI);
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
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 150, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 150, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 150, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_sort); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 150, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (__pyx_t_4) {
    __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 150, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else {
    __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 150, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_sorted_timeV, __pyx_t_6) < 0) __PYX_ERR(0, 150, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "vcp_212_sails.py":152
 *         self.sorted_timeV = numpy.concatenate((start_timeV, start_timeV_HI)).sort()
 * 
 *         if timeR_sort.shape[0] != timeV_sort.shape[0]:             # <<<<<<<<<<<<<<
 *             # We need mask CD from elevationR
 *             rm = numpy.ediff1d(self.normalized_elevation)
 */
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_timeR_sort, __pyx_n_s_shape); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_timeV_sort, __pyx_n_s_shape); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_4 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyObject_RichCompare(__pyx_t_1, __pyx_t_4, Py_NE); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_7 < 0)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (__pyx_t_7) {

    /* "vcp_212_sails.py":154
 *         if timeR_sort.shape[0] != timeV_sort.shape[0]:
 *             # We need mask CD from elevationR
 *             rm = numpy.ediff1d(self.normalized_elevation)             # <<<<<<<<<<<<<<
 *             self.normalized_elevation.mask[1:] = rm == 0
 */
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 154, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_ediff1d); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 154, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_normalized_elevation); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 154, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (!__pyx_t_5) {
      __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 154, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_6);
    } else {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_GIVEREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_4);
      __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_v_rm = __pyx_t_6;
    __pyx_t_6 = 0;

    /* "vcp_212_sails.py":155
 *             # We need mask CD from elevationR
 *             rm = numpy.ediff1d(self.normalized_elevation)
 *             self.normalized_elevation.mask[1:] = rm == 0             # <<<<<<<<<<<<<<
 */
    __pyx_t_6 = __Pyx_PyInt_EqObjC(__pyx_v_rm, __pyx_int_0, 0, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 155, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_normalized_elevation); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 155, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_mask); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 155, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (__Pyx_PyObject_SetSlice(__pyx_t_3, __pyx_t_6, 1, 0, NULL, NULL, &__pyx_slice__21, 1, 0, 1) < 0) __PYX_ERR(0, 155, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "vcp_212_sails.py":152
 *         self.sorted_timeV = numpy.concatenate((start_timeV, start_timeV_HI)).sort()
 * 
 *         if timeR_sort.shape[0] != timeV_sort.shape[0]:             # <<<<<<<<<<<<<<
 *             # We need mask CD from elevationR
 *             rm = numpy.ediff1d(self.normalized_elevation)
 */
  }

  /* "vcp_212_sails.py":123
 *         print("finish output")
 * 
 *     def order_data(self):             # <<<<<<<<<<<<<<
 *         """Restore the order of data, by scanning start time."""
 *         # Scan start time at each elevation.
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
  __Pyx_AddTraceback("vcp_212_sails.Vcp212.order_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_ds);
  __Pyx_XDECREF(__pyx_v_start_timeR);
  __Pyx_XDECREF(__pyx_v_start_timeR_HI);
  __Pyx_XDECREF(__pyx_v_timeR_sort);
  __Pyx_XDECREF(__pyx_v_elevationR);
  __Pyx_XDECREF(__pyx_v_elevationR_HI);
  __Pyx_XDECREF(__pyx_v_all_elevationR);
  __Pyx_XDECREF(__pyx_v_sorted_elevationR);
  __Pyx_XDECREF(__pyx_v_start_timeV);
  __Pyx_XDECREF(__pyx_v_start_timeV_HI);
  __Pyx_XDECREF(__pyx_v_timeV_sort);
  __Pyx_XDECREF(__pyx_v_rm);
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
    "vcp_212_sails",
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
  {&__pyx_n_s_BeamScanMode, __pyx_k_BeamScanMode, sizeof(__pyx_k_BeamScanMode), 0, 0, 1, 1},
  {&__pyx_n_s_CorrelationCoefficient, __pyx_k_CorrelationCoefficient, sizeof(__pyx_k_CorrelationCoefficient), 0, 0, 1, 1},
  {&__pyx_n_s_Dataset, __pyx_k_Dataset, sizeof(__pyx_k_Dataset), 0, 0, 1, 1},
  {&__pyx_n_s_Dict, __pyx_k_Dict, sizeof(__pyx_k_Dict), 0, 0, 1, 1},
  {&__pyx_n_s_DifferentialPhase, __pyx_k_DifferentialPhase, sizeof(__pyx_k_DifferentialPhase), 0, 0, 1, 1},
  {&__pyx_n_s_DifferentialReflectivity, __pyx_k_DifferentialReflectivity, sizeof(__pyx_k_DifferentialReflectivity), 0, 0, 1, 1},
  {&__pyx_n_s_DifferentialReflectivity_HI, __pyx_k_DifferentialReflectivity_HI, sizeof(__pyx_k_DifferentialReflectivity_HI), 0, 0, 1, 1},
  {&__pyx_n_s_Enum, __pyx_k_Enum, sizeof(__pyx_k_Enum), 0, 0, 1, 1},
  {&__pyx_n_s_HI, __pyx_k_HI, sizeof(__pyx_k_HI), 0, 0, 1, 1},
  {&__pyx_n_s_List, __pyx_k_List, sizeof(__pyx_k_List), 0, 0, 1, 1},
  {&__pyx_n_s_MaskedArray, __pyx_k_MaskedArray, sizeof(__pyx_k_MaskedArray), 0, 0, 1, 1},
  {&__pyx_n_s_OrderedDict, __pyx_k_OrderedDict, sizeof(__pyx_k_OrderedDict), 0, 0, 1, 1},
  {&__pyx_n_s_R, __pyx_k_R, sizeof(__pyx_k_R), 0, 0, 1, 1},
  {&__pyx_n_s_RVSDCP, __pyx_k_RVSDCP, sizeof(__pyx_k_RVSDCP), 0, 0, 1, 1},
  {&__pyx_n_s_RadialVelocity, __pyx_k_RadialVelocity, sizeof(__pyx_k_RadialVelocity), 0, 0, 1, 1},
  {&__pyx_n_s_Reflectivity, __pyx_k_Reflectivity, sizeof(__pyx_k_Reflectivity), 0, 0, 1, 1},
  {&__pyx_n_s_S, __pyx_k_S, sizeof(__pyx_k_S), 0, 0, 1, 1},
  {&__pyx_n_s_ScanTable, __pyx_k_ScanTable, sizeof(__pyx_k_ScanTable), 0, 0, 1, 1},
  {&__pyx_n_s_ScanVariable, __pyx_k_ScanVariable, sizeof(__pyx_k_ScanVariable), 0, 0, 1, 1},
  {&__pyx_n_s_SortedDict, __pyx_k_SortedDict, sizeof(__pyx_k_SortedDict), 0, 0, 1, 1},
  {&__pyx_n_s_SpectrumWidth, __pyx_k_SpectrumWidth, sizeof(__pyx_k_SpectrumWidth), 0, 0, 1, 1},
  {&__pyx_n_s_Tuple, __pyx_k_Tuple, sizeof(__pyx_k_Tuple), 0, 0, 1, 1},
  {&__pyx_n_s_Unsigned, __pyx_k_Unsigned, sizeof(__pyx_k_Unsigned), 0, 0, 1, 1},
  {&__pyx_n_s_V, __pyx_k_V, sizeof(__pyx_k_V), 0, 0, 1, 1},
  {&__pyx_n_s_Variable, __pyx_k_Variable, sizeof(__pyx_k_Variable), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212, __pyx_k_Vcp212, sizeof(__pyx_k_Vcp212), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212___fix_variable, __pyx_k_Vcp212___fix_variable, sizeof(__pyx_k_Vcp212___fix_variable), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212___init, __pyx_k_Vcp212___init, sizeof(__pyx_k_Vcp212___init), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212___init___locals_lambda, __pyx_k_Vcp212___init___locals_lambda, sizeof(__pyx_k_Vcp212___init___locals_lambda), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212_link_data_to_time, __pyx_k_Vcp212_link_data_to_time, sizeof(__pyx_k_Vcp212_link_data_to_time), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212_order_data, __pyx_k_Vcp212_order_data, sizeof(__pyx_k_Vcp212_order_data), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212_output2file, __pyx_k_Vcp212_output2file, sizeof(__pyx_k_Vcp212_output2file), 0, 0, 1, 1},
  {&__pyx_n_s_Vcp212_tag_elevation, __pyx_k_Vcp212_tag_elevation, sizeof(__pyx_k_Vcp212_tag_elevation), 0, 0, 1, 1},
  {&__pyx_n_s_VcpMode, __pyx_k_VcpMode, sizeof(__pyx_k_VcpMode), 0, 0, 1, 1},
  {&__pyx_n_s_VcpRain, __pyx_k_VcpRain, sizeof(__pyx_k_VcpRain), 0, 0, 1, 1},
  {&__pyx_kp_s__12, __pyx_k__12, sizeof(__pyx_k__12), 0, 0, 1, 0},
  {&__pyx_kp_s__7, __pyx_k__7, sizeof(__pyx_k__7), 0, 0, 1, 0},
  {&__pyx_kp_s__9, __pyx_k__9, sizeof(__pyx_k__9), 0, 0, 1, 0},
  {&__pyx_n_s_add_offset, __pyx_k_add_offset, sizeof(__pyx_k_add_offset), 0, 0, 1, 1},
  {&__pyx_n_s_all_elevationR, __pyx_k_all_elevationR, sizeof(__pyx_k_all_elevationR), 0, 0, 1, 1},
  {&__pyx_n_s_argsort, __pyx_k_argsort, sizeof(__pyx_k_argsort), 0, 0, 1, 1},
  {&__pyx_n_s_attri, __pyx_k_attri, sizeof(__pyx_k_attri), 0, 0, 1, 1},
  {&__pyx_n_s_axis, __pyx_k_axis, sizeof(__pyx_k_axis), 0, 0, 1, 1},
  {&__pyx_n_s_close, __pyx_k_close, sizeof(__pyx_k_close), 0, 0, 1, 1},
  {&__pyx_n_s_collections, __pyx_k_collections, sizeof(__pyx_k_collections), 0, 0, 1, 1},
  {&__pyx_n_s_concatenate, __pyx_k_concatenate, sizeof(__pyx_k_concatenate), 0, 0, 1, 1},
  {&__pyx_n_s_coordinate, __pyx_k_coordinate, sizeof(__pyx_k_coordinate), 0, 0, 1, 1},
  {&__pyx_n_s_data, __pyx_k_data, sizeof(__pyx_k_data), 0, 0, 1, 1},
  {&__pyx_n_s_data_by_time, __pyx_k_data_by_time, sizeof(__pyx_k_data_by_time), 0, 0, 1, 1},
  {&__pyx_n_s_data_dict, __pyx_k_data_dict, sizeof(__pyx_k_data_dict), 0, 0, 1, 1},
  {&__pyx_n_s_dataset, __pyx_k_dataset, sizeof(__pyx_k_dataset), 0, 0, 1, 1},
  {&__pyx_n_s_datatype, __pyx_k_datatype, sizeof(__pyx_k_datatype), 0, 0, 1, 1},
  {&__pyx_n_s_dict, __pyx_k_dict, sizeof(__pyx_k_dict), 0, 0, 1, 1},
  {&__pyx_n_s_doc, __pyx_k_doc, sizeof(__pyx_k_doc), 0, 0, 1, 1},
  {&__pyx_n_s_ds, __pyx_k_ds, sizeof(__pyx_k_ds), 0, 0, 1, 1},
  {&__pyx_n_s_ediff1d, __pyx_k_ediff1d, sizeof(__pyx_k_ediff1d), 0, 0, 1, 1},
  {&__pyx_n_s_elevation, __pyx_k_elevation, sizeof(__pyx_k_elevation), 0, 0, 1, 1},
  {&__pyx_n_s_elevationR, __pyx_k_elevationR, sizeof(__pyx_k_elevationR), 0, 0, 1, 1},
  {&__pyx_n_s_elevationR_HI, __pyx_k_elevationR_HI, sizeof(__pyx_k_elevationR_HI), 0, 0, 1, 1},
  {&__pyx_n_s_elevation_by_time, __pyx_k_elevation_by_time, sizeof(__pyx_k_elevation_by_time), 0, 0, 1, 1},
  {&__pyx_n_s_elevation_vars, __pyx_k_elevation_vars, sizeof(__pyx_k_elevation_vars), 0, 0, 1, 1},
  {&__pyx_n_s_elevation_vars_HI, __pyx_k_elevation_vars_HI, sizeof(__pyx_k_elevation_vars_HI), 0, 0, 1, 1},
  {&__pyx_n_s_end, __pyx_k_end, sizeof(__pyx_k_end), 0, 0, 1, 1},
  {&__pyx_n_s_enum, __pyx_k_enum, sizeof(__pyx_k_enum), 0, 0, 1, 1},
  {&__pyx_n_s_f, __pyx_k_f, sizeof(__pyx_k_f), 0, 0, 1, 1},
  {&__pyx_n_s_file, __pyx_k_file, sizeof(__pyx_k_file), 0, 0, 1, 1},
  {&__pyx_kp_s_finish_output, __pyx_k_finish_output, sizeof(__pyx_k_finish_output), 0, 0, 1, 0},
  {&__pyx_n_s_fix_variable, __pyx_k_fix_variable, sizeof(__pyx_k_fix_variable), 0, 0, 1, 1},
  {&__pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_k_home_sugar_Developer_Cloud2016, sizeof(__pyx_k_home_sugar_Developer_Cloud2016), 0, 0, 1, 0},
  {&__pyx_n_s_i, __pyx_k_i, sizeof(__pyx_k_i), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_init, __pyx_k_init, sizeof(__pyx_k_init), 0, 0, 1, 1},
  {&__pyx_n_s_is_dualpol, __pyx_k_is_dualpol, sizeof(__pyx_k_is_dualpol), 0, 0, 1, 1},
  {&__pyx_n_s_is_sails, __pyx_k_is_sails, sizeof(__pyx_k_is_sails), 0, 0, 1, 1},
  {&__pyx_n_s_items, __pyx_k_items, sizeof(__pyx_k_items), 0, 0, 1, 1},
  {&__pyx_n_s_iteritems, __pyx_k_iteritems, sizeof(__pyx_k_iteritems), 0, 0, 1, 1},
  {&__pyx_n_s_j, __pyx_k_j, sizeof(__pyx_k_j), 0, 0, 1, 1},
  {&__pyx_n_s_k, __pyx_k_k, sizeof(__pyx_k_k), 0, 0, 1, 1},
  {&__pyx_n_s_link_data_to_time, __pyx_k_link_data_to_time, sizeof(__pyx_k_link_data_to_time), 0, 0, 1, 1},
  {&__pyx_n_s_ma, __pyx_k_ma, sizeof(__pyx_k_ma), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_map, __pyx_k_map, sizeof(__pyx_k_map), 0, 0, 1, 1},
  {&__pyx_n_s_mask, __pyx_k_mask, sizeof(__pyx_k_mask), 0, 0, 1, 1},
  {&__pyx_n_s_mean, __pyx_k_mean, sizeof(__pyx_k_mean), 0, 0, 1, 1},
  {&__pyx_n_s_metaclass, __pyx_k_metaclass, sizeof(__pyx_k_metaclass), 0, 0, 1, 1},
  {&__pyx_n_s_min, __pyx_k_min, sizeof(__pyx_k_min), 0, 0, 1, 1},
  {&__pyx_n_s_module, __pyx_k_module, sizeof(__pyx_k_module), 0, 0, 1, 1},
  {&__pyx_n_s_netCDF4, __pyx_k_netCDF4, sizeof(__pyx_k_netCDF4), 0, 0, 1, 1},
  {&__pyx_n_s_normalized_elevation, __pyx_k_normalized_elevation, sizeof(__pyx_k_normalized_elevation), 0, 0, 1, 1},
  {&__pyx_n_s_numpy, __pyx_k_numpy, sizeof(__pyx_k_numpy), 0, 0, 1, 1},
  {&__pyx_n_s_object, __pyx_k_object, sizeof(__pyx_k_object), 0, 0, 1, 1},
  {&__pyx_n_s_open, __pyx_k_open, sizeof(__pyx_k_open), 0, 0, 1, 1},
  {&__pyx_n_s_order_data, __pyx_k_order_data, sizeof(__pyx_k_order_data), 0, 0, 1, 1},
  {&__pyx_n_s_output2file, __pyx_k_output2file, sizeof(__pyx_k_output2file), 0, 0, 1, 1},
  {&__pyx_n_s_output_dict, __pyx_k_output_dict, sizeof(__pyx_k_output_dict), 0, 0, 1, 1},
  {&__pyx_n_s_p, __pyx_k_p, sizeof(__pyx_k_p), 0, 0, 1, 1},
  {&__pyx_n_s_path, __pyx_k_path, sizeof(__pyx_k_path), 0, 0, 1, 1},
  {&__pyx_n_s_point, __pyx_k_point, sizeof(__pyx_k_point), 0, 0, 1, 1},
  {&__pyx_n_s_prepare, __pyx_k_prepare, sizeof(__pyx_k_prepare), 0, 0, 1, 1},
  {&__pyx_n_s_print, __pyx_k_print, sizeof(__pyx_k_print), 0, 0, 1, 1},
  {&__pyx_n_s_qualname, __pyx_k_qualname, sizeof(__pyx_k_qualname), 0, 0, 1, 1},
  {&__pyx_n_s_range, __pyx_k_range, sizeof(__pyx_k_range), 0, 0, 1, 1},
  {&__pyx_n_s_ref_sort_order, __pyx_k_ref_sort_order, sizeof(__pyx_k_ref_sort_order), 0, 0, 1, 1},
  {&__pyx_n_s_return, __pyx_k_return, sizeof(__pyx_k_return), 0, 0, 1, 1},
  {&__pyx_n_s_rm, __pyx_k_rm, sizeof(__pyx_k_rm), 0, 0, 1, 1},
  {&__pyx_n_s_round, __pyx_k_round, sizeof(__pyx_k_round), 0, 0, 1, 1},
  {&__pyx_n_s_scale_factor, __pyx_k_scale_factor, sizeof(__pyx_k_scale_factor), 0, 0, 1, 1},
  {&__pyx_n_s_self, __pyx_k_self, sizeof(__pyx_k_self), 0, 0, 1, 1},
  {&__pyx_n_s_set_auto_scale, __pyx_k_set_auto_scale, sizeof(__pyx_k_set_auto_scale), 0, 0, 1, 1},
  {&__pyx_n_s_shape, __pyx_k_shape, sizeof(__pyx_k_shape), 0, 0, 1, 1},
  {&__pyx_n_s_sort, __pyx_k_sort, sizeof(__pyx_k_sort), 0, 0, 1, 1},
  {&__pyx_n_s_sorted_elevationR, __pyx_k_sorted_elevationR, sizeof(__pyx_k_sorted_elevationR), 0, 0, 1, 1},
  {&__pyx_n_s_sorted_timeR, __pyx_k_sorted_timeR, sizeof(__pyx_k_sorted_timeR), 0, 0, 1, 1},
  {&__pyx_n_s_sorted_timeV, __pyx_k_sorted_timeV, sizeof(__pyx_k_sorted_timeV), 0, 0, 1, 1},
  {&__pyx_n_s_sortedcontainers, __pyx_k_sortedcontainers, sizeof(__pyx_k_sortedcontainers), 0, 0, 1, 1},
  {&__pyx_kp_s_start_output, __pyx_k_start_output, sizeof(__pyx_k_start_output), 0, 0, 1, 0},
  {&__pyx_n_s_start_timeR, __pyx_k_start_timeR, sizeof(__pyx_k_start_timeR), 0, 0, 1, 1},
  {&__pyx_n_s_start_timeR_HI, __pyx_k_start_timeR_HI, sizeof(__pyx_k_start_timeR_HI), 0, 0, 1, 1},
  {&__pyx_n_s_start_timeV, __pyx_k_start_timeV, sizeof(__pyx_k_start_timeV), 0, 0, 1, 1},
  {&__pyx_n_s_start_timeV_HI, __pyx_k_start_timeV_HI, sizeof(__pyx_k_start_timeV_HI), 0, 0, 1, 1},
  {&__pyx_n_s_staticmethod, __pyx_k_staticmethod, sizeof(__pyx_k_staticmethod), 0, 0, 1, 1},
  {&__pyx_n_s_suffix, __pyx_k_suffix, sizeof(__pyx_k_suffix), 0, 0, 1, 1},
  {&__pyx_n_s_t, __pyx_k_t, sizeof(__pyx_k_t), 0, 0, 1, 1},
  {&__pyx_n_s_tag_elevation, __pyx_k_tag_elevation, sizeof(__pyx_k_tag_elevation), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_time, __pyx_k_time, sizeof(__pyx_k_time), 0, 0, 1, 1},
  {&__pyx_n_s_timeR, __pyx_k_timeR, sizeof(__pyx_k_timeR), 0, 0, 1, 1},
  {&__pyx_n_s_timeR_HI, __pyx_k_timeR_HI, sizeof(__pyx_k_timeR_HI), 0, 0, 1, 1},
  {&__pyx_n_s_timeR_sort, __pyx_k_timeR_sort, sizeof(__pyx_k_timeR_sort), 0, 0, 1, 1},
  {&__pyx_n_s_timeV, __pyx_k_timeV, sizeof(__pyx_k_timeV), 0, 0, 1, 1},
  {&__pyx_n_s_timeV_HI, __pyx_k_timeV_HI, sizeof(__pyx_k_timeV_HI), 0, 0, 1, 1},
  {&__pyx_n_s_timeV_sort, __pyx_k_timeV_sort, sizeof(__pyx_k_timeV_sort), 0, 0, 1, 1},
  {&__pyx_n_s_time_value, __pyx_k_time_value, sizeof(__pyx_k_time_value), 0, 0, 1, 1},
  {&__pyx_n_s_time_vars, __pyx_k_time_vars, sizeof(__pyx_k_time_vars), 0, 0, 1, 1},
  {&__pyx_n_s_time_vars_HI, __pyx_k_time_vars_HI, sizeof(__pyx_k_time_vars_HI), 0, 0, 1, 1},
  {&__pyx_n_s_typing, __pyx_k_typing, sizeof(__pyx_k_typing), 0, 0, 1, 1},
  {&__pyx_n_s_u, __pyx_k_u, sizeof(__pyx_k_u), 0, 0, 1, 1},
  {&__pyx_n_s_v, __pyx_k_v, sizeof(__pyx_k_v), 0, 0, 1, 1},
  {&__pyx_n_s_v1, __pyx_k_v1, sizeof(__pyx_k_v1), 0, 0, 1, 1},
  {&__pyx_n_s_v_2, __pyx_k_v_2, sizeof(__pyx_k_v_2), 0, 0, 1, 1},
  {&__pyx_n_s_value, __pyx_k_value, sizeof(__pyx_k_value), 0, 0, 1, 1},
  {&__pyx_n_s_variable, __pyx_k_variable, sizeof(__pyx_k_variable), 0, 0, 1, 1},
  {&__pyx_n_s_variable_list, __pyx_k_variable_list, sizeof(__pyx_k_variable_list), 0, 0, 1, 1},
  {&__pyx_n_s_variable_list_HI, __pyx_k_variable_list_HI, sizeof(__pyx_k_variable_list_HI), 0, 0, 1, 1},
  {&__pyx_n_s_variables, __pyx_k_variables, sizeof(__pyx_k_variables), 0, 0, 1, 1},
  {&__pyx_n_s_vcp_212_sails, __pyx_k_vcp_212_sails, sizeof(__pyx_k_vcp_212_sails), 0, 0, 1, 1},
  {&__pyx_n_s_vel_sort_order, __pyx_k_vel_sort_order, sizeof(__pyx_k_vel_sort_order), 0, 0, 1, 1},
  {&__pyx_n_s_view, __pyx_k_view, sizeof(__pyx_k_view), 0, 0, 1, 1},
  {&__pyx_n_s_w, __pyx_k_w, sizeof(__pyx_k_w), 0, 0, 1, 1},
  {&__pyx_n_s_write, __pyx_k_write, sizeof(__pyx_k_write), 0, 0, 1, 1},
  {&__pyx_n_s_zeros_like, __pyx_k_zeros_like, sizeof(__pyx_k_zeros_like), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_object = __Pyx_GetBuiltinName(__pyx_n_s_object); if (!__pyx_builtin_object) __PYX_ERR(0, 25, __pyx_L1_error)
  __pyx_builtin_staticmethod = __Pyx_GetBuiltinName(__pyx_n_s_staticmethod); if (!__pyx_builtin_staticmethod) __PYX_ERR(0, 37, __pyx_L1_error)
  __pyx_builtin_map = __Pyx_GetBuiltinName(__pyx_n_s_map); if (!__pyx_builtin_map) __PYX_ERR(0, 54, __pyx_L1_error)
  __pyx_builtin_range = __Pyx_GetBuiltinName(__pyx_n_s_range); if (!__pyx_builtin_range) __PYX_ERR(0, 85, __pyx_L1_error)
  __pyx_builtin_open = __Pyx_GetBuiltinName(__pyx_n_s_open); if (!__pyx_builtin_open) __PYX_ERR(0, 110, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "vcp_212_sails.py":41
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 *             v.set_auto_scale(False)             # <<<<<<<<<<<<<<
 *             # Dump out
 *             _v = v[:]
 */
  __pyx_tuple_ = PyTuple_Pack(1, Py_False); if (unlikely(!__pyx_tuple_)) __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple_);
  __Pyx_GIVEREF(__pyx_tuple_);

  /* "vcp_212_sails.py":43
 *             v.set_auto_scale(False)
 *             # Dump out
 *             _v = v[:]             # <<<<<<<<<<<<<<
 *             _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 */
  __pyx_slice__2 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__2)) __PYX_ERR(0, 43, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__2);
  __Pyx_GIVEREF(__pyx_slice__2);

  /* "vcp_212_sails.py":47
 *             return numpy.ma.MaskedArray(_v1, _v.mask)
 *         else:
 *             return v[:]             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, dataset: Dataset):
 */
  __pyx_slice__3 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__3)) __PYX_ERR(0, 47, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__3);
  __Pyx_GIVEREF(__pyx_slice__3);

  /* "vcp_212_sails.py":52
 * 
 *         self.dataset = dataset
 *         self.variable_list = "Reflectivity", "RadialVelocity", "SpectrumWidth", \             # <<<<<<<<<<<<<<
 *                              "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
 *         self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables
 */
  __pyx_tuple__4 = PyTuple_Pack(6, __pyx_n_s_Reflectivity, __pyx_n_s_RadialVelocity, __pyx_n_s_SpectrumWidth, __pyx_n_s_DifferentialReflectivity, __pyx_n_s_CorrelationCoefficient, __pyx_n_s_DifferentialPhase); if (unlikely(!__pyx_tuple__4)) __PYX_ERR(0, 52, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__4);
  __Pyx_GIVEREF(__pyx_tuple__4);

  /* "vcp_212_sails.py":100
 *                 if t not in self.dataset.variables:
 *                     continue
 *                 time_value = self.dataset.variables[t][:].min(axis=1)             # <<<<<<<<<<<<<<
 *                 for i in list(time_value):
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]
 */
  __pyx_slice__5 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__5)) __PYX_ERR(0, 100, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__5);
  __Pyx_GIVEREF(__pyx_slice__5);

  /* "vcp_212_sails.py":103
 *                 for i in list(time_value):
 *                     self.data_by_time[i] = self.data_dict['Reflectivity'][i]
 *                     self.elevation_by_time[i] = self.data_by_time['elevationR'][i].mean().round(1)             # <<<<<<<<<<<<<<
 * 
 *             pass
 */
  __pyx_tuple__6 = PyTuple_Pack(1, __pyx_int_1); if (unlikely(!__pyx_tuple__6)) __PYX_ERR(0, 103, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__6);
  __Pyx_GIVEREF(__pyx_tuple__6);

  /* "vcp_212_sails.py":113
 *         for point, attri in coordinate.items():
 *             f.write(str(point))
 *             f.write(' ')             # <<<<<<<<<<<<<<
 *             for variable, value in attri.items():
 *                 f.write(variable)
 */
  __pyx_tuple__8 = PyTuple_Pack(1, __pyx_kp_s__7); if (unlikely(!__pyx_tuple__8)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__8);
  __Pyx_GIVEREF(__pyx_tuple__8);

  /* "vcp_212_sails.py":116
 *             for variable, value in attri.items():
 *                 f.write(variable)
 *                 f.write(':')             # <<<<<<<<<<<<<<
 *                 f.write(str(value))
 *                 f.write(' ')
 */
  __pyx_tuple__10 = PyTuple_Pack(1, __pyx_kp_s__9); if (unlikely(!__pyx_tuple__10)) __PYX_ERR(0, 116, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__10);
  __Pyx_GIVEREF(__pyx_tuple__10);

  /* "vcp_212_sails.py":118
 *                 f.write(':')
 *                 f.write(str(value))
 *                 f.write(' ')             # <<<<<<<<<<<<<<
 *             f.write('\n')
 *         f.close()
 */
  __pyx_tuple__11 = PyTuple_Pack(1, __pyx_kp_s__7); if (unlikely(!__pyx_tuple__11)) __PYX_ERR(0, 118, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__11);
  __Pyx_GIVEREF(__pyx_tuple__11);

  /* "vcp_212_sails.py":119
 *                 f.write(str(value))
 *                 f.write(' ')
 *             f.write('\n')             # <<<<<<<<<<<<<<
 *         f.close()
 *         print("finish output")
 */
  __pyx_tuple__13 = PyTuple_Pack(1, __pyx_kp_s__12); if (unlikely(!__pyx_tuple__13)) __PYX_ERR(0, 119, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__13);
  __Pyx_GIVEREF(__pyx_tuple__13);

  /* "vcp_212_sails.py":127
 *         # Scan start time at each elevation.
 *         ds = self.dataset
 *         start_timeR = ds.variables['timeR'][:].min(axis=1)             # <<<<<<<<<<<<<<
 *         # If there is high resolution data, merge it
 *         start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 */
  __pyx_slice__14 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__14)) __PYX_ERR(0, 127, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__14);
  __Pyx_GIVEREF(__pyx_slice__14);

  /* "vcp_212_sails.py":129
 *         start_timeR = ds.variables['timeR'][:].min(axis=1)
 *         # If there is high resolution data, merge it
 *         start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []             # <<<<<<<<<<<<<<
 *         timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()
 *         self.ref_sort_order = timeR_sort
 */
  __pyx_slice__15 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__15)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__15);
  __Pyx_GIVEREF(__pyx_slice__15);

  /* "vcp_212_sails.py":135
 * 
 *         # ElevationR
 *         elevationR = ds.variables['elevationR'][:].mean(axis=1)             # <<<<<<<<<<<<<<
 *         elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
 *         all_elevationR = numpy.concatenate((elevationR, elevationR_HI))
 */
  __pyx_slice__16 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__16)) __PYX_ERR(0, 135, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__16);
  __Pyx_GIVEREF(__pyx_slice__16);

  /* "vcp_212_sails.py":136
 *         # ElevationR
 *         elevationR = ds.variables['elevationR'][:].mean(axis=1)
 *         elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []             # <<<<<<<<<<<<<<
 *         all_elevationR = numpy.concatenate((elevationR, elevationR_HI))
 *         sorted_elevationR = all_elevationR[timeR_sort]
 */
  __pyx_slice__17 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__17)) __PYX_ERR(0, 136, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__17);
  __Pyx_GIVEREF(__pyx_slice__17);

  /* "vcp_212_sails.py":142
 *         # Once we get sorted elevation, we should extract SAILS elevations.
 *         # Problem is, how can we deal with these elevations
 *         self.normalized_elevation = sorted_elevationR.round(1)  # type: numpy.ma.MaskedArray             # <<<<<<<<<<<<<<
 * 
 *         # Then we check if elevationV is all included in elevationR.
 */
  __pyx_tuple__18 = PyTuple_Pack(1, __pyx_int_1); if (unlikely(!__pyx_tuple__18)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__18);
  __Pyx_GIVEREF(__pyx_tuple__18);

  /* "vcp_212_sails.py":146
 *         # Then we check if elevationV is all included in elevationR.
 *         # If true, means CD contains reflectivity data, we need drop them, if false, we merge velocity data
 *         start_timeV = ds.variables['timeV'][:].min(axis=1)             # <<<<<<<<<<<<<<
 *         start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
 */
  __pyx_slice__19 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__19)) __PYX_ERR(0, 146, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__19);
  __Pyx_GIVEREF(__pyx_slice__19);

  /* "vcp_212_sails.py":147
 *         # If true, means CD contains reflectivity data, we need drop them, if false, we merge velocity data
 *         start_timeV = ds.variables['timeV'][:].min(axis=1)
 *         start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)             # <<<<<<<<<<<<<<
 *         timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
 *         self.vel_sort_order = timeV_sort
 */
  __pyx_slice__20 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__20)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__20);
  __Pyx_GIVEREF(__pyx_slice__20);

  /* "vcp_212_sails.py":155
 *             # We need mask CD from elevationR
 *             rm = numpy.ediff1d(self.normalized_elevation)
 *             self.normalized_elevation.mask[1:] = rm == 0             # <<<<<<<<<<<<<<
 */
  __pyx_slice__21 = PySlice_New(__pyx_int_1, Py_None, Py_None); if (unlikely(!__pyx_slice__21)) __PYX_ERR(0, 155, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__21);
  __Pyx_GIVEREF(__pyx_slice__21);

  /* "vcp_212_sails.py":34
 * 
 * class Vcp212(VcpRain):
 *     ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)             # <<<<<<<<<<<<<<
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)
 * 
 */
  __pyx_tuple__22 = PyTuple_Pack(17, __pyx_float_0_5, __pyx_float_0_5, __pyx_float_0_9, __pyx_float_0_9, __pyx_float_1_3, __pyx_float_1_3, __pyx_float_1_8, __pyx_float_2_4, __pyx_float_3_1, __pyx_float_4_0, __pyx_float_5_1, __pyx_float_6_4, __pyx_float_8_0, __pyx_float_10_0, __pyx_float_12_5, __pyx_float_15_6, __pyx_float_19_5); if (unlikely(!__pyx_tuple__22)) __PYX_ERR(0, 34, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__22);
  __Pyx_GIVEREF(__pyx_tuple__22);

  /* "vcp_212_sails.py":35
 * class Vcp212(VcpRain):
 *     ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)             # <<<<<<<<<<<<<<
 * 
 *     @staticmethod
 */
  __pyx_tuple__23 = PyTuple_Pack(17, __pyx_int_1, __pyx_int_2, __pyx_int_1, __pyx_int_2, __pyx_int_1, __pyx_int_2, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3, __pyx_int_3); if (unlikely(!__pyx_tuple__23)) __PYX_ERR(0, 35, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__23);
  __Pyx_GIVEREF(__pyx_tuple__23);

  /* "vcp_212_sails.py":38
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */
  __pyx_tuple__24 = PyTuple_Pack(3, __pyx_n_s_v, __pyx_n_s_v_2, __pyx_n_s_v1); if (unlikely(!__pyx_tuple__24)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__24);
  __Pyx_GIVEREF(__pyx_tuple__24);
  __pyx_codeobj__25 = (PyObject*)__Pyx_PyCode_New(1, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__24, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_fix_variable, 38, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__25)) __PYX_ERR(0, 38, __pyx_L1_error)

  /* "vcp_212_sails.py":49
 *             return v[:]
 * 
 *     def __init__(self, dataset: Dataset):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */
  __pyx_tuple__26 = PyTuple_Pack(5, __pyx_n_s_self, __pyx_n_s_dataset, __pyx_n_s_k, __pyx_n_s_v, __pyx_n_s_p); if (unlikely(!__pyx_tuple__26)) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__26);
  __Pyx_GIVEREF(__pyx_tuple__26);
  __pyx_codeobj__27 = (PyObject*)__Pyx_PyCode_New(2, 0, 5, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__26, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_init, 49, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__27)) __PYX_ERR(0, 49, __pyx_L1_error)

  /* "vcp_212_sails.py":81
 *         self.order_data()
 * 
 *     def tag_elevation(self):             # <<<<<<<<<<<<<<
 *         # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
 */
  __pyx_tuple__28 = PyTuple_Pack(3, __pyx_n_s_self, __pyx_n_s_j, __pyx_n_s_i); if (unlikely(!__pyx_tuple__28)) __PYX_ERR(0, 81, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__28);
  __Pyx_GIVEREF(__pyx_tuple__28);
  __pyx_codeobj__29 = (PyObject*)__Pyx_PyCode_New(1, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__28, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_tag_elevation, 81, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__29)) __PYX_ERR(0, 81, __pyx_L1_error)

  /* "vcp_212_sails.py":92
 *                 self.is_sails[i] = 1
 * 
 *     def link_data_to_time(self):             # <<<<<<<<<<<<<<
 *         if self.sorted_timeR.shape == self.sorted_timeV.shape:
 *             # Means there is no reflectivity scan for CD scan
 */
  __pyx_tuple__30 = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_t, __pyx_n_s_time_value, __pyx_n_s_i); if (unlikely(!__pyx_tuple__30)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__30);
  __Pyx_GIVEREF(__pyx_tuple__30);
  __pyx_codeobj__31 = (PyObject*)__Pyx_PyCode_New(1, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__30, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_link_data_to_time, 92, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__31)) __PYX_ERR(0, 92, __pyx_L1_error)

  /* "vcp_212_sails.py":108
 * 
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */
  __pyx_tuple__32 = PyTuple_Pack(8, __pyx_n_s_self, __pyx_n_s_path, __pyx_n_s_coordinate, __pyx_n_s_f, __pyx_n_s_point, __pyx_n_s_attri, __pyx_n_s_variable, __pyx_n_s_value); if (unlikely(!__pyx_tuple__32)) __PYX_ERR(0, 108, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__32);
  __Pyx_GIVEREF(__pyx_tuple__32);
  __pyx_codeobj__33 = (PyObject*)__Pyx_PyCode_New(3, 0, 8, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__32, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_output2file, 108, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__33)) __PYX_ERR(0, 108, __pyx_L1_error)

  /* "vcp_212_sails.py":123
 *         print("finish output")
 * 
 *     def order_data(self):             # <<<<<<<<<<<<<<
 *         """Restore the order of data, by scanning start time."""
 *         # Scan start time at each elevation.
 */
  __pyx_tuple__34 = PyTuple_Pack(13, __pyx_n_s_self, __pyx_n_s_ds, __pyx_n_s_start_timeR, __pyx_n_s_start_timeR_HI, __pyx_n_s_timeR_sort, __pyx_n_s_elevationR, __pyx_n_s_elevationR_HI, __pyx_n_s_all_elevationR, __pyx_n_s_sorted_elevationR, __pyx_n_s_start_timeV, __pyx_n_s_start_timeV_HI, __pyx_n_s_timeV_sort, __pyx_n_s_rm); if (unlikely(!__pyx_tuple__34)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__34);
  __Pyx_GIVEREF(__pyx_tuple__34);
  __pyx_codeobj__35 = (PyObject*)__Pyx_PyCode_New(1, 0, 13, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__34, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_sugar_Developer_Cloud2016, __pyx_n_s_order_data, 123, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__35)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  __pyx_float_0_1 = PyFloat_FromDouble(0.1); if (unlikely(!__pyx_float_0_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_5 = PyFloat_FromDouble(0.5); if (unlikely(!__pyx_float_0_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_9 = PyFloat_FromDouble(0.9); if (unlikely(!__pyx_float_0_9)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_1_3 = PyFloat_FromDouble(1.3); if (unlikely(!__pyx_float_1_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_1_8 = PyFloat_FromDouble(1.8); if (unlikely(!__pyx_float_1_8)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_2_4 = PyFloat_FromDouble(2.4); if (unlikely(!__pyx_float_2_4)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_3_1 = PyFloat_FromDouble(3.1); if (unlikely(!__pyx_float_3_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_4_0 = PyFloat_FromDouble(4.0); if (unlikely(!__pyx_float_4_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_5_1 = PyFloat_FromDouble(5.1); if (unlikely(!__pyx_float_5_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_6_4 = PyFloat_FromDouble(6.4); if (unlikely(!__pyx_float_6_4)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_8_0 = PyFloat_FromDouble(8.0); if (unlikely(!__pyx_float_8_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_10_0 = PyFloat_FromDouble(10.0); if (unlikely(!__pyx_float_10_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_12_5 = PyFloat_FromDouble(12.5); if (unlikely(!__pyx_float_12_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_15_6 = PyFloat_FromDouble(15.6); if (unlikely(!__pyx_float_15_6)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_19_5 = PyFloat_FromDouble(19.5); if (unlikely(!__pyx_float_19_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_3 = PyInt_FromLong(3); if (unlikely(!__pyx_int_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_4 = PyInt_FromLong(4); if (unlikely(!__pyx_int_4)) __PYX_ERR(0, 1, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initvcp_212_sails(void); /*proto*/
PyMODINIT_FUNC initvcp_212_sails(void)
#else
PyMODINIT_FUNC PyInit_vcp_212_sails(void); /*proto*/
PyMODINIT_FUNC PyInit_vcp_212_sails(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
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
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_vcp_212_sails(void)", 0);
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
  __pyx_m = Py_InitModule4("vcp_212_sails", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
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
  if (__pyx_module_is_main_vcp_212_sails) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) __PYX_ERR(0, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "vcp_212_sails")) {
      if (unlikely(PyDict_SetItemString(modules, "vcp_212_sails", __pyx_m) < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
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

  /* "vcp_212_sails.py":5
 * # TODO: General abstract design VCP => Clear/Rain => VCP_SAIL/VCP_NOSAIL => VCP
 * 
 * from enum import Enum             # <<<<<<<<<<<<<<
 * 
 * from typing import List, Tuple, Dict
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_Enum);
  __Pyx_GIVEREF(__pyx_n_s_Enum);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_Enum);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_enum, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_Enum); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Enum, __pyx_t_1) < 0) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":7
 * from enum import Enum
 * 
 * from typing import List, Tuple, Dict             # <<<<<<<<<<<<<<
 * 
 * from collections import OrderedDict
 */
  __pyx_t_2 = PyList_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_List);
  __Pyx_GIVEREF(__pyx_n_s_List);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_List);
  __Pyx_INCREF(__pyx_n_s_Tuple);
  __Pyx_GIVEREF(__pyx_n_s_Tuple);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_n_s_Tuple);
  __Pyx_INCREF(__pyx_n_s_Dict);
  __Pyx_GIVEREF(__pyx_n_s_Dict);
  PyList_SET_ITEM(__pyx_t_2, 2, __pyx_n_s_Dict);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_typing, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_List); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_List, __pyx_t_2) < 0) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_Tuple); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Tuple, __pyx_t_2) < 0) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_Dict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Dict, __pyx_t_2) < 0) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":9
 * from typing import List, Tuple, Dict
 * 
 * from collections import OrderedDict             # <<<<<<<<<<<<<<
 * 
 * from sortedcontainers import SortedDict
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_OrderedDict);
  __Pyx_GIVEREF(__pyx_n_s_OrderedDict);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_OrderedDict);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_collections, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_OrderedDict); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_OrderedDict, __pyx_t_1) < 0) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":11
 * from collections import OrderedDict
 * 
 * from sortedcontainers import SortedDict             # <<<<<<<<<<<<<<
 * 
 * import numpy
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_SortedDict);
  __Pyx_GIVEREF(__pyx_n_s_SortedDict);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_SortedDict);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_sortedcontainers, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_SortedDict); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_SortedDict, __pyx_t_2) < 0) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":13
 * from sortedcontainers import SortedDict
 * 
 * import numpy             # <<<<<<<<<<<<<<
 * 
 * import netCDF4
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numpy, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_numpy, __pyx_t_1) < 0) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":15
 * import numpy
 * 
 * import netCDF4             # <<<<<<<<<<<<<<
 * from netCDF4 import Dataset
 * 
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_netCDF4, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_netCDF4, __pyx_t_1) < 0) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":16
 * 
 * import netCDF4
 * from netCDF4 import Dataset             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_Dataset);
  __Pyx_GIVEREF(__pyx_n_s_Dataset);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_Dataset);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_netCDF4, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_Dataset); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Dataset, __pyx_t_1) < 0) __PYX_ERR(0, 16, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":19
 * 
 * 
 * class BeamScanMode(Enum):             # <<<<<<<<<<<<<<
 *     R = 0b0001  # 1 - Reflectivity
 *     V = 0b0010  # 2 - Velocity
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Enum); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_CalculateMetaclass(NULL, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_Py3MetaclassPrepare(__pyx_t_2, __pyx_t_1, __pyx_n_s_BeamScanMode, __pyx_n_s_BeamScanMode, (PyObject *) NULL, __pyx_n_s_vcp_212_sails, (PyObject *) NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "vcp_212_sails.py":20
 * 
 * class BeamScanMode(Enum):
 *     R = 0b0001  # 1 - Reflectivity             # <<<<<<<<<<<<<<
 *     V = 0b0010  # 2 - Velocity
 *     S = 0b0100  # 4 - SAILS Scan
 */
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_R, __pyx_int_1) < 0) __PYX_ERR(0, 20, __pyx_L1_error)

  /* "vcp_212_sails.py":21
 * class BeamScanMode(Enum):
 *     R = 0b0001  # 1 - Reflectivity
 *     V = 0b0010  # 2 - Velocity             # <<<<<<<<<<<<<<
 *     S = 0b0100  # 4 - SAILS Scan
 * 
 */
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_V, __pyx_int_2) < 0) __PYX_ERR(0, 21, __pyx_L1_error)

  /* "vcp_212_sails.py":22
 *     R = 0b0001  # 1 - Reflectivity
 *     V = 0b0010  # 2 - Velocity
 *     S = 0b0100  # 4 - SAILS Scan             # <<<<<<<<<<<<<<
 * 
 * 
 */
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_S, __pyx_int_4) < 0) __PYX_ERR(0, 22, __pyx_L1_error)

  /* "vcp_212_sails.py":19
 * 
 * 
 * class BeamScanMode(Enum):             # <<<<<<<<<<<<<<
 *     R = 0b0001  # 1 - Reflectivity
 *     V = 0b0010  # 2 - Velocity
 */
  __pyx_t_4 = __Pyx_Py3ClassCreate(__pyx_t_2, __pyx_n_s_BeamScanMode, __pyx_t_1, __pyx_t_3, NULL, 0, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_BeamScanMode, __pyx_t_4) < 0) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":25
 * 
 * 
 * class VcpMode(object):             # <<<<<<<<<<<<<<
 *     pass
 * 
 */
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_builtin_object);
  __Pyx_GIVEREF(__pyx_builtin_object);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_builtin_object);
  __pyx_t_2 = __Pyx_CalculateMetaclass(NULL, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_Py3MetaclassPrepare(__pyx_t_2, __pyx_t_1, __pyx_n_s_VcpMode, __pyx_n_s_VcpMode, (PyObject *) NULL, __pyx_n_s_vcp_212_sails, (PyObject *) NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_Py3ClassCreate(__pyx_t_2, __pyx_n_s_VcpMode, __pyx_t_1, __pyx_t_3, NULL, 0, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_VcpMode, __pyx_t_4) < 0) __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":29
 * 
 * 
 * class VcpRain(VcpMode):             # <<<<<<<<<<<<<<
 *     pass
 * 
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_VcpMode); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_CalculateMetaclass(NULL, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_Py3MetaclassPrepare(__pyx_t_1, __pyx_t_2, __pyx_n_s_VcpRain, __pyx_n_s_VcpRain, (PyObject *) NULL, __pyx_n_s_vcp_212_sails, (PyObject *) NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_Py3ClassCreate(__pyx_t_1, __pyx_n_s_VcpRain, __pyx_t_2, __pyx_t_3, NULL, 0, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_VcpRain, __pyx_t_4) < 0) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vcp_212_sails.py":33
 * 
 * 
 * class Vcp212(VcpRain):             # <<<<<<<<<<<<<<
 *     ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_VcpRain); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_CalculateMetaclass(NULL, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_Py3MetaclassPrepare(__pyx_t_2, __pyx_t_1, __pyx_n_s_Vcp212, __pyx_n_s_Vcp212, (PyObject *) NULL, __pyx_n_s_vcp_212_sails, (PyObject *) NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "vcp_212_sails.py":34
 * 
 * class Vcp212(VcpRain):
 *     ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)             # <<<<<<<<<<<<<<
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)
 * 
 */
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_ScanTable, __pyx_tuple__22) < 0) __PYX_ERR(0, 34, __pyx_L1_error)

  /* "vcp_212_sails.py":35
 * class Vcp212(VcpRain):
 *     ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)             # <<<<<<<<<<<<<<
 * 
 *     @staticmethod
 */
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_ScanVariable, __pyx_tuple__23) < 0) __PYX_ERR(0, 35, __pyx_L1_error)

  /* "vcp_212_sails.py":38
 * 
 *     @staticmethod
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:             # <<<<<<<<<<<<<<
 *         """Fix wrong unsigned value"""
 *         if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
 */
  __pyx_t_4 = PyDict_New(); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_netCDF4); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_Variable); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_v, __pyx_t_6) < 0) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_numpy); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_ma); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_MaskedArray); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_4, __pyx_n_s_return, __pyx_t_6) < 0) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_1__fix_variable__, __Pyx_CYFUNCTION_STATICMETHOD, __pyx_n_s_Vcp212___fix_variable, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, ((PyObject *)__pyx_codeobj__25)); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_CyFunction_SetAnnotationsDict(__pyx_t_6, __pyx_t_4);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "vcp_212_sails.py":37
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)
 * 
 *     @staticmethod             # <<<<<<<<<<<<<<
 *     def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
 *         """Fix wrong unsigned value"""
 */
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 37, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_6);
  __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_builtin_staticmethod, __pyx_t_4, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 37, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_fix_variable, __pyx_t_6) < 0) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "vcp_212_sails.py":49
 *             return v[:]
 * 
 *     def __init__(self, dataset: Dataset):             # <<<<<<<<<<<<<<
 * 
 *         self.dataset = dataset
 */
  __pyx_t_6 = PyDict_New(); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_Dataset); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_t_6, __pyx_n_s_dataset, __pyx_t_4) < 0) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_3__init__, 0, __pyx_n_s_Vcp212___init, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, ((PyObject *)__pyx_codeobj__27)); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_CyFunction_SetAnnotationsDict(__pyx_t_4, __pyx_t_6);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_init, __pyx_t_4) < 0) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "vcp_212_sails.py":81
 *         self.order_data()
 * 
 *     def tag_elevation(self):             # <<<<<<<<<<<<<<
 *         # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
 *         self.is_sails = numpy.zeros_like(self.normalized_elevation)
 */
  __pyx_t_4 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_5tag_elevation, 0, __pyx_n_s_Vcp212_tag_elevation, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, ((PyObject *)__pyx_codeobj__29)); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 81, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_tag_elevation, __pyx_t_4) < 0) __PYX_ERR(0, 81, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "vcp_212_sails.py":92
 *                 self.is_sails[i] = 1
 * 
 *     def link_data_to_time(self):             # <<<<<<<<<<<<<<
 *         if self.sorted_timeR.shape == self.sorted_timeV.shape:
 *             # Means there is no reflectivity scan for CD scan
 */
  __pyx_t_4 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_7link_data_to_time, 0, __pyx_n_s_Vcp212_link_data_to_time, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, ((PyObject *)__pyx_codeobj__31)); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_link_data_to_time, __pyx_t_4) < 0) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "vcp_212_sails.py":108
 * 
 * 
 *     def output2file(self, path, coordinate):             # <<<<<<<<<<<<<<
 *         print("start output...")
 *         f = open(path, 'w')
 */
  __pyx_t_4 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_9output2file, 0, __pyx_n_s_Vcp212_output2file, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, ((PyObject *)__pyx_codeobj__33)); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 108, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_output2file, __pyx_t_4) < 0) __PYX_ERR(0, 108, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "vcp_212_sails.py":123
 *         print("finish output")
 * 
 *     def order_data(self):             # <<<<<<<<<<<<<<
 *         """Restore the order of data, by scanning start time."""
 *         # Scan start time at each elevation.
 */
  __pyx_t_4 = __Pyx_CyFunction_NewEx(&__pyx_mdef_13vcp_212_sails_6Vcp212_11order_data, 0, __pyx_n_s_Vcp212_order_data, NULL, __pyx_n_s_vcp_212_sails, __pyx_d, ((PyObject *)__pyx_codeobj__35)); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_order_data, __pyx_t_4) < 0) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "vcp_212_sails.py":33
 * 
 * 
 * class Vcp212(VcpRain):             # <<<<<<<<<<<<<<
 *     ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)
 *     ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)
 */
  __pyx_t_4 = __Pyx_Py3ClassCreate(__pyx_t_2, __pyx_n_s_Vcp212, __pyx_t_1, __pyx_t_3, NULL, 0, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Vcp212, __pyx_t_4) < 0) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vcp_212_sails.py":1
 * # coding=utf-8             # <<<<<<<<<<<<<<
 * # TODO: create an abstract interface for it
 * # TODO: General abstract design VCP => Clear/Rain => VCP_SAIL/VCP_NOSAIL => VCP
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_1) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init vcp_212_sails", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init vcp_212_sails");
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

/* PyObjectCallMethod0 */
          static PyObject* __Pyx_PyObject_CallMethod0(PyObject* obj, PyObject* method_name) {
    PyObject *method, *result = NULL;
    method = __Pyx_PyObject_GetAttrStr(obj, method_name);
    if (unlikely(!method)) goto bad;
#if CYTHON_COMPILING_IN_CPYTHON
    if (likely(PyMethod_Check(method))) {
        PyObject *self = PyMethod_GET_SELF(method);
        if (likely(self)) {
            PyObject *function = PyMethod_GET_FUNCTION(method);
            result = __Pyx_PyObject_CallOneArg(function, self);
            Py_DECREF(method);
            return result;
        }
    }
#endif
    result = __Pyx_PyObject_CallNoArg(method);
    Py_DECREF(method);
bad:
    return result;
}

/* RaiseNeedMoreValuesToUnpack */
          static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index) {
    PyErr_Format(PyExc_ValueError,
                 "need more than %" CYTHON_FORMAT_SSIZE_T "d value%.1s to unpack",
                 index, (index == 1) ? "" : "s");
}

/* RaiseTooManyValuesToUnpack */
          static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected) {
    PyErr_Format(PyExc_ValueError,
                 "too many values to unpack (expected %" CYTHON_FORMAT_SSIZE_T "d)", expected);
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

/* RaiseNoneIterError */
          static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
}

/* UnpackTupleError */
          static void __Pyx_UnpackTupleError(PyObject *t, Py_ssize_t index) {
    if (t == Py_None) {
      __Pyx_RaiseNoneNotIterableError();
    } else if (PyTuple_GET_SIZE(t) < index) {
      __Pyx_RaiseNeedMoreValuesError(PyTuple_GET_SIZE(t));
    } else {
      __Pyx_RaiseTooManyValuesError(index);
    }
}

/* UnpackTuple2 */
          static CYTHON_INLINE int __Pyx_unpack_tuple2(PyObject* tuple, PyObject** pvalue1, PyObject** pvalue2,
                                             int is_tuple, int has_known_size, int decref_tuple) {
    Py_ssize_t index;
    PyObject *value1 = NULL, *value2 = NULL, *iter = NULL;
    if (!is_tuple && unlikely(!PyTuple_Check(tuple))) {
        iternextfunc iternext;
        iter = PyObject_GetIter(tuple);
        if (unlikely(!iter)) goto bad;
        if (decref_tuple) { Py_DECREF(tuple); tuple = NULL; }
        iternext = Py_TYPE(iter)->tp_iternext;
        value1 = iternext(iter); if (unlikely(!value1)) { index = 0; goto unpacking_failed; }
        value2 = iternext(iter); if (unlikely(!value2)) { index = 1; goto unpacking_failed; }
        if (!has_known_size && unlikely(__Pyx_IternextUnpackEndCheck(iternext(iter), 2))) goto bad;
        Py_DECREF(iter);
    } else {
        if (!has_known_size && unlikely(PyTuple_GET_SIZE(tuple) != 2)) {
            __Pyx_UnpackTupleError(tuple, 2);
            goto bad;
        }
#if CYTHON_COMPILING_IN_PYPY
        value1 = PySequence_ITEM(tuple, 0);
        if (unlikely(!value1)) goto bad;
        value2 = PySequence_ITEM(tuple, 1);
        if (unlikely(!value2)) goto bad;
#else
        value1 = PyTuple_GET_ITEM(tuple, 0);
        value2 = PyTuple_GET_ITEM(tuple, 1);
        Py_INCREF(value1);
        Py_INCREF(value2);
#endif
        if (decref_tuple) { Py_DECREF(tuple); }
    }
    *pvalue1 = value1;
    *pvalue2 = value2;
    return 0;
unpacking_failed:
    if (!has_known_size && __Pyx_IterFinish() == 0)
        __Pyx_RaiseNeedMoreValuesError(index);
bad:
    Py_XDECREF(iter);
    Py_XDECREF(value1);
    Py_XDECREF(value2);
    if (decref_tuple) { Py_XDECREF(tuple); }
    return -1;
}

/* dict_iter */
          static CYTHON_INLINE PyObject* __Pyx_dict_iterator(PyObject* iterable, int is_dict, PyObject* method_name,
                                                   Py_ssize_t* p_orig_length, int* p_source_is_dict) {
    is_dict = is_dict || likely(PyDict_CheckExact(iterable));
    *p_source_is_dict = is_dict;
#if !CYTHON_COMPILING_IN_PYPY
    if (is_dict) {
        *p_orig_length = PyDict_Size(iterable);
        Py_INCREF(iterable);
        return iterable;
    }
#endif
    *p_orig_length = 0;
    if (method_name) {
        PyObject* iter;
        iterable = __Pyx_PyObject_CallMethod0(iterable, method_name);
        if (!iterable)
            return NULL;
#if !CYTHON_COMPILING_IN_PYPY
        if (PyTuple_CheckExact(iterable) || PyList_CheckExact(iterable))
            return iterable;
#endif
        iter = PyObject_GetIter(iterable);
        Py_DECREF(iterable);
        return iter;
    }
    return PyObject_GetIter(iterable);
}
static CYTHON_INLINE int __Pyx_dict_iter_next(
        PyObject* iter_obj, CYTHON_NCP_UNUSED Py_ssize_t orig_length, CYTHON_NCP_UNUSED Py_ssize_t* ppos,
        PyObject** pkey, PyObject** pvalue, PyObject** pitem, int source_is_dict) {
    PyObject* next_item;
#if !CYTHON_COMPILING_IN_PYPY
    if (source_is_dict) {
        PyObject *key, *value;
        if (unlikely(orig_length != PyDict_Size(iter_obj))) {
            PyErr_SetString(PyExc_RuntimeError, "dictionary changed size during iteration");
            return -1;
        }
        if (unlikely(!PyDict_Next(iter_obj, ppos, &key, &value))) {
            return 0;
        }
        if (pitem) {
            PyObject* tuple = PyTuple_New(2);
            if (unlikely(!tuple)) {
                return -1;
            }
            Py_INCREF(key);
            Py_INCREF(value);
            PyTuple_SET_ITEM(tuple, 0, key);
            PyTuple_SET_ITEM(tuple, 1, value);
            *pitem = tuple;
        } else {
            if (pkey) {
                Py_INCREF(key);
                *pkey = key;
            }
            if (pvalue) {
                Py_INCREF(value);
                *pvalue = value;
            }
        }
        return 1;
    } else if (PyTuple_CheckExact(iter_obj)) {
        Py_ssize_t pos = *ppos;
        if (unlikely(pos >= PyTuple_GET_SIZE(iter_obj))) return 0;
        *ppos = pos + 1;
        next_item = PyTuple_GET_ITEM(iter_obj, pos);
        Py_INCREF(next_item);
    } else if (PyList_CheckExact(iter_obj)) {
        Py_ssize_t pos = *ppos;
        if (unlikely(pos >= PyList_GET_SIZE(iter_obj))) return 0;
        *ppos = pos + 1;
        next_item = PyList_GET_ITEM(iter_obj, pos);
        Py_INCREF(next_item);
    } else
#endif
    {
        next_item = PyIter_Next(iter_obj);
        if (unlikely(!next_item)) {
            return __Pyx_IterFinish();
        }
    }
    if (pitem) {
        *pitem = next_item;
    } else if (pkey && pvalue) {
        if (__Pyx_unpack_tuple2(next_item, pkey, pvalue, source_is_dict, source_is_dict, 1))
            return -1;
    } else if (pkey) {
        *pkey = next_item;
    } else {
        *pvalue = next_item;
    }
    return 1;
}

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

/* PyIntBinop */
          #if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx_PyInt_EqObjC(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    if (op1 == op2) {
        Py_RETURN_TRUE;
    }
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        const long b = intval;
        long a = PyInt_AS_LONG(op1);
        if (a == b) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
        }
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS && PY_MAJOR_VERSION >= 3
    if (likely(PyLong_CheckExact(op1))) {
        const long b = intval;
        long a;
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
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
                    }
                #if PyLong_SHIFT < 30 && PyLong_SHIFT != 15
                default: return PyLong_Type.tp_richcompare(op1, op2, Py_EQ);
                #else
                default: Py_RETURN_FALSE;
                #endif
            }
        }
            if (a == b) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
    }
    #endif
    if (PyFloat_CheckExact(op1)) {
        const long b = intval;
        double a = PyFloat_AS_DOUBLE(op1);
            if ((double)a == (double)b) {
                Py_RETURN_TRUE;
            } else {
                Py_RETURN_FALSE;
            }
    }
    return PyObject_RichCompare(op1, op2, Py_EQ);
}
#endif

/* SliceObject */
          static CYTHON_INLINE int __Pyx_PyObject_SetSlice(PyObject* obj, PyObject* value,
        Py_ssize_t cstart, Py_ssize_t cstop,
        PyObject** _py_start, PyObject** _py_stop, PyObject** _py_slice,
        int has_cstart, int has_cstop, CYTHON_UNUSED int wraparound) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyMappingMethods* mp;
#if PY_MAJOR_VERSION < 3
    PySequenceMethods* ms = Py_TYPE(obj)->tp_as_sequence;
    if (likely(ms && ms->sq_ass_slice)) {
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
        return ms->sq_ass_slice(obj, cstart, cstop, value);
    }
#endif
    mp = Py_TYPE(obj)->tp_as_mapping;
    if (likely(mp && mp->mp_ass_subscript))
#endif
    {
        int result;
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
        result = mp->mp_ass_subscript(obj, py_slice, value);
#else
        result = value ? PyObject_SetItem(obj, py_slice, value) : PyObject_DelItem(obj, py_slice);
#endif
        if (!_py_slice) {
            Py_DECREF(py_slice);
        }
        return result;
    }
    PyErr_Format(PyExc_TypeError,
        "'%.200s' object does not support slice %.10s",
        Py_TYPE(obj)->tp_name, value ? "assignment" : "deletion");
bad:
    return -1;
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
