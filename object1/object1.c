/*
	JS结构体转换为C接头体
*/

#include <stdio.h>
#include <mujs.h>

#ifdef _DEBUG
#pragma comment(lib,"../Debug/libmujs.lib")
#else
#pragma comment(lib,"../Release/libmujs.lib")
#endif // _DEBUG


struct T
{
	int foo;
	unsigned char bar;
};

int main(void)
{
	js_State *J = js_newstate(NULL, NULL, JS_STRICT);
	// t = {foo:42, bar:12};
	js_newobject(J);
	{
		js_pushnumber(J, 42);
		js_setproperty(J, -2, "foo");
		js_pushnumber(J, 12);
		js_setproperty(J, -2, "bar");
	}
	js_setglobal(J, "t");

	struct T t;
	js_getglobal(J, "t"); // 找到t并将object压栈
	js_getproperty(J, -1, "foo"); // 此时t在栈顶，得到foo后再将foo的值压栈
	js_getproperty(J, -2, "bar"); // 此时t已经下沉一次，所以idx为-2
	t.foo = js_tonumber(J, -2);
	t.bar = js_tonumber(J, -1);

	t.foo = 0;
	t.bar = 0;

	t.foo = js_tonumber(J, -2);
	t.bar = js_tonumber(J, -1);

	printf("t.foo:%d, t.bar:%d\n", t.foo, t.bar);
	return 0;
}