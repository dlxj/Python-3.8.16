# Python-3.8.16 源码编译 dll



```

编译环境 win10 + vs2019

cd Python-3.8.16\PCbuild
./get_externals.bat
	# 安装 

Python-3.8.16\PCbuild\pcbuild.sln
	# 打开解决方案
	
选择python 项目，编译类型为 x64，开始编译

注意：
	编译出来的 dll 和 exe 依赖 Python-3.8.16\Lib 这个目录，里面有各种 python 脚本
	Lib 或者和可执行文件同级目录，或着在它的上级，会一直往上找，找不到就报错了
	

dll 入口, python.c重命名为 python.cc，代码改成下面这样
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


exe 入口，test_python_dll.cc
#include <iostream>

#include "windows.h"
#include <direct.h>

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

void call_node_dll() {
    HINSTANCE   ghDLL = NULL;
    ghDLL = LoadLibrary("D:\\GitHub\\node-14.21.1\\out\\Debug\\node.dll");

    typedef int(_cdecl* FunctionPtr) (int argc, wchar_t* wargv[]);

    FunctionPtr wmain;

    wmain = (FunctionPtr)GetProcAddress(ghDLL, "wmain");

    int argc = 2;

    wchar_t* wargv[] = {
      (wchar_t*)L"C:\\projects\\edge-js\\tools\\build\\node-14.21.1\\out\\Debug\\node2.exe",
      //(wchar_t*)L"C:\\projects\\edge-js\\tools\\build\\node-14.21.1\\out\\Debug\\pmserver\\server.js",
      (wchar_t*)L"D:\\GitHub\\echodict\\pmserver\\server.js"
    };

    wmain(argc, wargv);

    std::cout << "Hello World!\n";
}

void call_python_dll(int argc, char* argv[]) {
    HINSTANCE   ghDLL = NULL;
    //ghDLL = LoadLibrary("E:\\python\\Python-3.8.16\\PCbuild\\amd64\\python38_d.dll");

    //string str = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;

    

    char dll_path[MAX_PATH] = { 0 };
    ::GetModuleFileName(nullptr, dll_path, MAX_PATH);
    ::PathRemoveFileSpec(dll_path);
    ::PathAppend(dll_path, "python38_d.dll");
    
    ghDLL = LoadLibrary(dll_path);

    //ghDLL = LoadLibrary("F:\\python\\Python-3.8.16\\PCbuild\\amd64\\python38_d.dll");

    typedef int(_cdecl* FunctionPtr) (int argc, wchar_t* argv[]);


    FunctionPtr wmain;

    wmain = (FunctionPtr)GetProcAddress(ghDLL, "wmain");

    wchar_t* wargv[] = {
      (wchar_t*)L"C:\\projects\\edge-js\\tools\\build\\node-14.21.1\\out\\Debug\\node2.exe",
      //(wchar_t*)L"C:\\projects\\edge-js\\tools\\build\\node-14.21.1\\out\\Debug\\pmserver\\server.js",
      //(wchar_t*)L"D:\\GitHub\\echodict\\pmserver\\server.js"
    };

    wmain(1, wargv);

    std::cout << "Hello World!\n";
}

int main(int argc, char* argv[])
{
    //call_node_dll();

    call_python_dll(argc, argv);
}


```



