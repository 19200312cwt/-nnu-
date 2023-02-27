C4996	'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. 
大概就是一些函数可能会导致溢出，不安全，想让我们替换成sprintf_s....这些安全的函数。（中间增加buffer长度的参数）


"int __cdecl invoke_main(void)" (?invoke_main@@YAHXZ) 中引用了该符号 winsock1 D:\Ccode\winsock1\winsock1\MSVCRTD.lib(exe_main.obj) 1
果是windows程序，那么WinMain是入口函数，在VS2017中新建项目为“win32项目”
如果是dos控制台程序，那么main是入口函数，在VS2017中新建项目为“win32控制台应用程序”


#pragma comment(lib,"ws2_32.lib")