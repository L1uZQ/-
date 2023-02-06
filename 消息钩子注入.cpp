#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

void SetWindowHookEx_inject()
{
	HWND hwnd = FindWindow(NULL, L"FlappyBird");

	if (hwnd == NULL) cout << "hwnd error" << endl;

	DWORD pid = NULL;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	cout << "pid: " << pid << endl;
	if (tid == NULL) cout << "tid error" << endl;
	cout << "tid: " << tid << endl;


	HMODULE dll = LoadLibraryEx(L"E:\\Code library\\腾讯游戏安全课程\\作业2\\02_test_dll\\x64\\Debug\\02_testdll.dll", NULL, DONT_RESOLVE_DLL_REFERENCES);
	if (dll == NULL) cout << "dll error" << endl;

	HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "test_func");
	if (addr == NULL) cout << "addr error" << endl;

	HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid);
	cout << "addr: " << addr << endl;
	if (handle == NULL) cout << "handle error" << endl;

	PostThreadMessage(tid, WM_NULL, NULL, NULL);

	cout << "按任意键结束消息钩子注入" << endl;
	getchar();

	//卸载dll
	BOOL unhook = UnhookWindowsHookEx(handle);
	if (unhook == FALSE) cout << "unhook error" << endl;

}



int main()
{
	//消息钩子注入
	SetWindowHookEx_inject();
	return 0;
}