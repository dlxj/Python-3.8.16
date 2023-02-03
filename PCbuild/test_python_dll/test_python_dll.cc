
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
