#include <stdio.h>
#include <mujs.h>

#ifdef _DEBUG
#pragma comment(lib,"../Debug/libmujs.lib")
#else
#pragma comment(lib,"../Release/libmujs.lib")
#endif // _DEBUG


// JSº¯Êý
static void jsB_print(js_State *J)
{
	int i, top = js_gettop(J);
	for (i = 1; i < top; ++i)
	{
		const char *s = js_tostring(J, i);
		if (i > 1) putchar(' ');
		fputs(s, stdout);
	}
	putchar('\n');
	js_pushundefined(J);
}

static int call_callback(js_State *J, const char *arg1, int arg2)
{
	int result;
	int i;
	js_pushnumber(J, 100);

	/* Find the function to call. */
	js_getglobal(J, "my_callback");

	i = js_tonumber(J, -2); // 1
	printf("i:%d\n", i);

	/* Push arguments to function. */
	js_pushnull(J); /* the 'this' object to use */
	js_pushstring(J, arg1);
	js_pushnumber(J, arg2);

	i = js_tonumber(J, -5); // 2
	printf("i:%d\n", i);

	/* Call function and check for exceptions. */
	if (js_pcall(J, 2)) {
		fprintf(stderr, "an exception occurred in the javascript callback\n");
		js_pop(J, 1);
		return -1;
	}

	i = js_tonumber(J, -2); // 3
	printf("i:%d\n", i);

	/* Retrieve return value. */
	result = js_tonumber(J, -1);
	js_pop(J, 1);

	i = js_tonumber(J, -1); // 4
	printf("i:%d\n", i);
	return result;
}


// callback.js
char *pJsData = "function my_callback(arg1, arg2)\
				{print(arg1);\
				return (arg2 + 2);}";

void main(void)
{
	js_State * J = js_newstate(NULL, NULL, JS_STRICT);
	//js_dofile(J, "callback.js");
	js_dostring(J, pJsData);

	js_newcfunction(J, jsB_print, "print", 0);
	js_setglobal(J, "print");

	int ret = call_callback(J, "Hello world!", 100);

	printf("ret:%d\n", ret);
}