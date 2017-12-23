/*----------------------------------------------------------------------------*/
/*--  LZSS coding for Nintendo GBA/DS                                       --*/
/*--  Copyright (C) 2011 CUE                                                --*/
/*--  Copyright (C) 2017 Dorkmaster Flek                                    --*/
/*--                                                                        --*/
/*--  This program is free software: you can redistribute it and/or modify  --*/
/*--  it under the terms of the GNU General Public License as published by  --*/
/*--  the Free Software Foundation, either version 3 of the License, or     --*/
/*--  (at your option) any later version.                                   --*/
/*--                                                                        --*/
/*--  This program is distributed in the hope that it will be useful,       --*/
/*--  but WITHOUT ANY WARRANTY; without even the implied warranty of        --*/
/*--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          --*/
/*--  GNU General Public License for more details.                          --*/
/*--                                                                        --*/
/*--  You should have received a copy of the GNU General Public License     --*/
/*--  along with this program. If not, see <http://www.gnu.org/licenses/>.  --*/
/*----------------------------------------------------------------------------*/

#include <Python.h>
#include "nlzss.h"

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

static PyObject *pynlzss_error;

/* -- private functions -- */

static PyObject *pynlzss_encode_decode_file(PyObject *m, PyObject *args,
					   PyObject *kw, int encode);

/* ----------------------------------------------------------------------------
 * module methods
 */

static PyObject *pynlzss_encode_file(PyObject *m, PyObject *args, PyObject *kw)
{
	return pynlzss_encode_decode_file(m, args, kw, 1);
}

static PyObject *pynlzss_decode_file(PyObject *m, PyObject *args, PyObject *kw)
{
	return pynlzss_encode_decode_file(m, args, kw, 0);
}

static PyMethodDef pynlzss_methods[] = {
	{ "encode_file", (PyCFunction)pynlzss_encode_file,
	  METH_VARARGS | METH_KEYWORDS,
	  "Encode an original file using LZSS into another one." },
	{ "decode_file", (PyCFunction)pynlzss_decode_file,
	  METH_VARARGS | METH_KEYWORDS,
	  "Decode a LZSS compressed file into another original one." },
	{ NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef pynlzss = {
        PyModuleDef_HEAD_INIT,
        "nlzss",      /* name of module */
        "",          /* module documentation, may be NULL */
        -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        pynlzss_methods
    };
#endif

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_nlzss(void)
#else
PyMODINIT_FUNC initnlzss(void)
#endif
{
    PyObject *m;

#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&pynlzss);
#else
    m = Py_InitModule("nlzss", pynlzss_methods);
#endif

    if (m == NULL)
#if PY_MAJOR_VERSION >= 3
        return m;
#else
        return;
#endif

    pynlzss_error = PyErr_NewException("nlzss.error", NULL, NULL);
    Py_INCREF(pynlzss_error);
    PyModule_AddObject(m, "error", pynlzss_error);

#if PY_MAJOR_VERSION >= 3
    return m;
#endif
}

/* -----------------------------------------------------------------------------
 * private functions
 */

static PyObject *pynlzss_encode_decode_file(PyObject *m, PyObject *args, PyObject *kw, int encode)
{
	static char *pynlzss_kwlist[] = {"in_path", "out_path", NULL };
	char *in_path;
	char *out_path;

	int stat;

	if (!PyArg_ParseTupleAndKeywords(args, kw, "ss", pynlzss_kwlist, &in_path, &out_path))
		return NULL;

	if (encode)
		stat = LZS_Encode(in_path, out_path);
	else
		stat = LZS_Decode(in_path, out_path);

	if (stat) {
		PyErr_SetString(pynlzss_error, "Failed to process LZSS file");
		return NULL;
	}

	Py_RETURN_NONE;
}
