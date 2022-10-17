#include <Python.h>
#include <stdio.h>

PyObject *add(PyObject *self, PyObject *args)
{
    double x;
    double y;
    // fazendo o parse para double
    PyArg_ParseTuple(args, "dd", &x, &y); // primeiro i ´e integer, o segundo tbm
    return PyFloat_FromDouble(x + y);
}

// nossos metédos ficam aqui
static PyMethodDef methods[] = {
    {"add",
     add,
     METH_VARARGS,
     "Adds two numbers"},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef from_c = {
    PyModuleDef_HEAD_INIT,
    "__name__", // aqui vai o nome do module, vc pode mudar
    "__doc__",  // aqui vai a documentação, vc pode mudar
    -1,
    methods,
};

PyMODINIT_FUNC PyInit_from_c()
{
    return PyModule_Create(&from_c);
}