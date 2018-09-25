#include <stdio.h>
#include <mujs.h>

#ifdef _DEBUG
#pragma comment(lib,"../Debug/libmujs.lib")
#else
#pragma comment(lib,"../Release/libmujs.lib")
#endif // _DEBUG

static void printargs(js_State *J)
{
	int this_value = js_tonumber(J, 1);
	int arg1 = js_tonumber(J, 1);
	int arg2 = js_tonumber(J, 2);

	int negative_arg1 = js_tonumber(J, -1);
	int negative_arg2 = js_tonumber(J, -2);
	int negative_this_value = js_tonumber(J, -3);

	printf("this value:%x\n", this_value);
	printf("arg1:%d\n", arg1);
	printf("arg2:%d\n", arg2);
	printf("negative arg1:%d\n", negative_arg1);
	printf("negative arg2:%d\n", negative_arg2);
	printf("negative this value:%x\n", negative_this_value);
}


int main(int argc, char **argv)
{
	js_State *J = js_newstate(NULL, NULL, JS_STRICT);
	js_newcfunction(J, printargs, "printargs", 2);
	js_setglobal(J, "printargs");
	js_dostring(J, "printargs(1,2);");

	js_freestate(J);
	return 0;
}
