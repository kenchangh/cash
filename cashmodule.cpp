#include <Python.h>
#include <iostream>
using namespace std;


int *start_ptr = new int[5000];

int make_hash(const char *c_key) {
  string key(c_key);
  int hash = 0;
  for (string::iterator i = key.begin(), end = key.end();
       i != end; i++) {
    int ascii = *i;
    ascii -= 31; // removes weird symbols
    hash += ascii;
  }
  return hash;
}

static PyObject *set(PyObject *self, PyObject *args) {
  const char *key;
  int value;
  if (!PyArg_ParseTuple(args, "si", &key, &value));
    return NULL;
  }
  const char *key;
  int hash = make_hash(key);
  *(start_ptr + hash) = value;
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *get(PyObject *self, PyObject *args) {
  const char *key;
  if (!PyArg_ParseTuple(args, "s", &key));
    return NULL;
  }
  int hash = make_hash(key);
  return Py_BuildValue("i", *(start_ptr+hash));
}

void remove(string key) {
  int hash = make_hash(key);
  *(start_ptr + hash) = 0;
  return;
}

// Defining the functions
static PyMethodDef module_methods[] = {
  {"set", (PyCFunction)set, METH_VARARGS,
   "Sets an integer"},
  {"get", (PyCFunction)get, METH_VARARGS,
   "Gets an integer"},
  {NULL, NULL, 0, NULL}
};

// Initializing hot_score module with functions
PyMODINIT_FUNC initcash(void) {
  (void) Py_InitModule("cash", module_methods);
}

