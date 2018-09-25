#include <stdio.h>
#include <mujs.h>

#ifdef _DEBUG
#pragma comment(lib,"../Debug/libmujs.lib")
#else
#pragma comment(lib,"../Release/libmujs.lib")
#endif // _DEBUG

int main(int argc, char **argv)
{
	char line[256];
	int ret;
	// 不抛出异常
	//js_State *J = js_newstate(NULL, NULL, 0);
	// 抛出异常错误
	js_State *J = js_newstate(NULL, NULL, JS_STRICT);
	//printf("JS_STRICT:%d\n", JS_STRICT);
	while (fgets(line, sizeof(line), stdin))
	{
		ret = js_dostring(J, line);
		//printf("dostring ret:%d\n", ret);
	}
	js_freestate(J);

	return 0;
}