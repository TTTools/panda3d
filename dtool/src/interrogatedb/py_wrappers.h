/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file py_wrappers.h
 * @author rdb
 * @date 2017-11-26
 */

#ifndef PY_WRAPPERS_H
#define PY_WRAPPERS_H

#include "py_panda.h"

#ifdef HAVE_PYTHON

/**
 * These classes are returned from properties that require a subscript
 * interface, ie. something.children[i] = 3.
 */
struct Dtool_WrapperBase {
  PyObject_HEAD;
  PyObject *_self;
  const char *_name;
};

struct Dtool_SequenceWrapper {
  Dtool_WrapperBase _base;
  lenfunc _len_func;
  ssizeargfunc _getitem_func;
};

struct Dtool_MutableSequenceWrapper {
  Dtool_WrapperBase _base;
  lenfunc _len_func;
  ssizeargfunc _getitem_func;
  ssizeobjargproc _setitem_func;
  PyObject *(*_insert_func)(PyObject *, size_t, PyObject *);
};

struct Dtool_MappingWrapper {
  union {
    Dtool_WrapperBase _base;
    Dtool_SequenceWrapper _keys;
  };
  binaryfunc _getitem_func;
  objobjargproc _setitem_func;
};

struct Dtool_GeneratorWrapper {
  Dtool_WrapperBase _base;
  iternextfunc _iternext_func;
};

inline Dtool_SequenceWrapper *Dtool_NewSequenceWrapper(PyObject *self, const char *name);
inline Dtool_MutableSequenceWrapper *Dtool_NewMutableSequenceWrapper(PyObject *self, const char *name);
inline Dtool_MappingWrapper *Dtool_NewMappingWrapper(PyObject *self, const char *name);
inline Dtool_MappingWrapper *Dtool_NewMutableMappingWrapper(PyObject *self, const char *name);
inline PyObject *Dtool_NewGenerator(PyObject *self, iternextfunc gen_next);
inline PyObject *Dtool_NewStaticProperty(PyTypeObject *obj, const PyGetSetDef *getset);

#include "py_wrappers.I"

#endif  // HAVE_PYTHON

#endif  // PY_WRAPPERS_H
