#include <stdio.h>
#include <mujs.h>

#ifdef _DEBUG
#pragma comment(lib,"../Debug/libmujs.lib")
#else
#pragma comment(lib,"../Release/libmujs.lib")
#endif // _DEBUG


#define TAG "File"

static void new_File(js_State *J)
{
	FILE *file;

	if (js_isundefined(J, 1)) {
		file = stdin;
	}
	else {
		const char *filename = js_tostring(J, 1);
		file = fopen(filename, "r");
		if (!file)
			js_error(J, "cannot open file: '%s'", filename);
	}

	js_currentfunction(J);
	js_getproperty(J, -1, "prototype");
	js_newuserdata(J, TAG, file,NULL);
}

static void File_prototype_readByte(js_State *J)
{
	FILE *file = js_touserdata(J, 0, TAG);
	js_pushnumber(J, getc(file));
}

static void File_prototype_readLine(js_State *J)
{
	char line[256], *s;
	FILE *file = js_touserdata(J, 0, TAG);
	s = fgets(line, sizeof line, file);
	if (s)
		js_pushstring(J, line);
	else
		js_pushnull(J);
}

static void File_prototype_close(js_State *J)
{
	FILE *file = js_touserdata(J, 0, TAG);
	fclose(file);
	js_pushundefined(J);
}

void initfile(js_State *J)
{
	js_getglobal(J, "Object");
	js_getproperty(J, -1, "prototype");	// File.prototype.[[Prototype]] = Object.prototype
	js_newuserdata(J, TAG, stdin,NULL);		// File.prototype.[[Userdata]] = stdin
	{
		js_newcfunction(J, File_prototype_readByte, "File.prototype.readByte", 0);
		js_defproperty(J, -2, "readByte", JS_DONTENUM);

		js_newcfunction(J, File_prototype_readLine, "File.prototype.readLine", 0);
		js_defproperty(J, -2, "readLine", JS_DONTENUM);

		js_newcfunction(J, File_prototype_close, "File.prototype.close", 0);
		js_defproperty(J, -2, "close", JS_DONTENUM);
	}
	js_newcconstructor(J, new_File, new_File, "File", 1);
	js_defglobal(J, "File", JS_DONTENUM);
}


int main(int argc, char **argv)
{
	js_State *J = js_newstate(NULL, NULL, JS_STRICT);
	initfile(J);

	js_freestate(J);
	return 0;
}