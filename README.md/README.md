# Usando Python com C

Primeiro em um arquivo C, importei o header `#include <Python.c>`(Se você estiver usando o VSCODE ele vai reclamar, mas vc pode arrumar usando a lampadazinha que aparece quando vc clica no error),logo após criei a seguinte função:
```c
PyMODINIT_FUNC PyInit_from_c()
{
    return PyModule_Create(&from_c);
}
```
Ela é a função inicializadora(tipo o main do C). O nome da função é obrigatoriamente ter o `PyInit_` e dps o nome do modulo que você quiser.Essa função vai retorna tudo iremos criar, como funções, nome do modulo, documentação, etc...
<br>
No [arquivo](https://github.com/RonanzinDev/Python_C_Extension/blob/main/Makefile) Makefile, eu ja deixei uma instruções prontas pra poder compilar o codigo em C.
```Makefile
run:
	gcc --share from_c.c -o  from_c.so -I /usr/include/python3.10
```
A opção `--share` é pra dizer ao compilador que o arquivo a ser gerado tem que ser uma biblioteca compartilhada, depois o nome do nosso arquivo C(que no meu caso é from_c.c)
,o nome de arquivo de saida que vai ser gerado(tem que ter o `.so` no final), e o -I que serve para dizer que estamos incluindo uma biblioteca externa(`<Python.h>`) no nosso codigo em C(Eu acho que é pra isso que serve kkkkkk).
<br>

Segundo definimos uma struct como essa:
```c
static struct PyModuleDef from_c = {
    PyModuleDef_HEAD_INIT,
    "__name__", // aqui vai o nome do module, vc pode mudar
    "__doc__",  // aqui vai a documentação, vc pode mudar
    -1,
    methods, // Aqui vai os metodos que criamos no arquivo
};
```
É ela que vai retorna tudo sobre o arquivo, como nome,documentação, e metodos.
<br>
Terceiro uma struct com os metodos e o detalhe sobre os mesmos.
```c
static PyMethodDef methods[] = {
    {"add", // o nome da função
     add, // a função em si
     METH_VARARGS, // Falando que ela contem argumentos
     "Adds two numbers"}, // Documentando a função
    {NULL, NULL, 0, NULL}, // Aparentemente isso é obrigatorio, segundo a documentação
};
```c
<br>

E por ultimo nossa função de adição:
```c
PyObject *add(PyObject *self, PyObject *args)
{
    double x;
    double y;
    // fazendo o parse para double
    PyArg_ParseTuple(args, "dd", &x, &y); // primeiro 'd' é double e o segundo tbm. Ou seja, estamos convertendo para dois `doubles` os argumentos que estamos recebendo
    return PyFloat_FromDouble(x + y); // Fazendo o casting
}
```
<br>

Agora é só chamar em um arquivo `.py`:
```python
import from_c # ou tbm pode ser from from_c import add
print(add(1,2))
```
E o resultado vai ser `3.0`
