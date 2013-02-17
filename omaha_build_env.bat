@echo off
rem -- Set all environment variables used by Hammer and Omaha. --
set OMAHA_NET_DIR=%WINDIR%\Microsoft.NET\Framework\v2.0.50727
set OMAHA_WTL_DIR=%ProgramFiles%\WTL\include
set OMAHA_WIX_DIR=%ProgramFiles%\Windows Installer XML v3.5\bin
set OMAHA_VISTASDK_DIR=%ProgramFiles%\Microsoft SDKs\Windows\v6.1
set OMAHA_PSEXEC_DIR=%ProgramFiles%\PSTools
set OMAHA_PYTHON_DIR=C:\Python244
set SCONS_DIR=%OMAHA_PYTHON_DIR%\Lib\site-packages\scons-1.3.1
set SCT_DIR=C:\swtoolkit
rem -- Add Visual Studio and Python to our path, and set VC env variables. --
call "%ProgramFiles%\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"
path %OMAHA_PYTHON_DIR%;%PATH%
rem -- Add ATLServer headers to the Visual C++ include path. --
set INCLUDE=%INCLUDE%C:\atlserver\include;
