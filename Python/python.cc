
// exe ��ڵ㣬���Ҫֱ�����У��Ȱ� F:\python\Python-3.8.16\PCbuild\test_python_dll\test_python_dll.cc ��� main �ĳ� mmain���ٰ������ mmain �ĳ� main


#include "Python.h"
#include "pycore_pylifecycle.h"

extern "C" __declspec(dllexport) int wmain(int argc, wchar_t* wargv[]) {
    return Py_Main(argc, wargv);
}

#ifdef MS_WINDOWS
int mmain(int argc, wchar_t **argv)
{
    return wmain(argc, argv);
}
#else
int
main(int argc, char **argv)
{
    return Py_BytesMain(argc, argv);
}
#endif
