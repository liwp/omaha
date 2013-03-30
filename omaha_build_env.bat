@echo off
rem -- Set all environment variables used by Hammer and Omaha. --
set OMAHA_NET_DIR=%WINDIR%\Microsoft.NET\Framework\v2.0.50727
set OMAHA_PSEXEC_DIR=C:\Work\PSTools
set OMAHA_PYTHON_DIR=C:\Python24
set OMAHA_VISTASDK_DIR=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A
set OMAHA_WIX_DIR=C:\Program Files (x86)\Windows Installer XML v3.5\bin
set OMAHA_WTL_DIR=C:\Work\WTL81_9127\Include
set SCONS_DIR=%OMAHA_PYTHON_DIR%\Lib\site-packages\scons-1.3.1
set SCT_DIR=C:\Work\swtoolkit

rem -- Add Visual Studio and Python to our path, and set VC env variables. --
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat"
path %OMAHA_PYTHON_DIR%;%PATH%
rem -- Add ATLServer headers to the Visual C++ include path. --
set INCLUDE=C:\ATL_Server\include;%INCLUDE%
rem -- Disable the hostname / AD name test
set OMAHA_TEST_BUILD_SYSTEM=1
