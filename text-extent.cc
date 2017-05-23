#include <node.h>
#include <Windows.h>
#include <string>

namespace textent{
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Number;
    using v8::Value;

	void Render(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		if (args.Length() < 3 || args.Length() > 3) {
			isolate->ThrowException(v8::Exception::TypeError(
				String::NewFromUtf8(isolate, "Wrong number of arguments.")
			));
			return;
		}

		if (!args[0]->IsString() || !args[1]->IsNumber() || !args[2]->IsString()) {
			isolate->ThrowException(v8::Exception::TypeError(
				String::NewFromUtf8(isolate, "Wrong arguments.")
			));
			return;
		}

		v8::String::Utf8Value pFontName(args[0]->ToString());
		int fontLength = args[0]->ToString()->Length();
		double font_size(args[1]->NumberValue());
		v8::String::Utf8Value pSrcString(args[2]->ToString());
		int srcLength = args[2]->ToString()->Length();

		wchar_t fontName[500], srcString[4000];
		MultiByteToWideChar(CP_UTF8, 0, *pFontName, -1, fontName, strlen(*pFontName));
		MultiByteToWideChar(CP_UTF8, 0, *pSrcString, -1, srcString, strlen(*pSrcString));

		HDC hdc = CreateCompatibleDC(NULL);

		HFONT dFont = CreateFontW((int)font_size,
			0, 0, 0, 0, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, /*not important*/
			fontName);

		SelectObject(hdc, dFont); //load font
		
		SIZE result;
		int resultWidth, resultHeight;
		if (GetTextExtentPoint32W(hdc, srcString, srcLength, &result)) {
			resultWidth = result.cx;
			resultHeight = result.cy;
		}
		else {
			isolate->ThrowException(v8::Exception::Error(
				String::NewFromUtf8(isolate, "GetTextExtent Error")
			));
			return;
		}
		
		DeleteObject(dFont); //release font
		DeleteDC(hdc);

		Local<Object> returnobj = Object::New(isolate);
		returnobj->Set(String::NewFromUtf8(isolate, "width"), Number::New(isolate, resultWidth));
		returnobj->Set(String::NewFromUtf8(isolate, "height"), Number::New(isolate, resultHeight));

		args.GetReturnValue().Set(returnobj);
	}

    void init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "render", Render);
    }

    NODE_MODULE(textent, init)
}