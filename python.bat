@rem This script invokes the most recently built Python with all arguments
@rem passed through to the interpreter.  This file is generated by the
@rem build process and any changes *will* be thrown away by the next
@rem rebuild.
@rem This is only meant as a convenience for developing CPython
@rem and using it outside of that context is ill-advised.
@echo Running Debug^|x64 interpreter...
@setlocal
@set PYTHONHOME=E:\python\Python-3.8.16\

@"E:\python\Python-3.8.16\PCbuild\amd64\python_d.exe" %*
