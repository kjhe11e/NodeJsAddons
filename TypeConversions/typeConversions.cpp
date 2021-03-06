#include <node.h>
#include <string>
#include <algorithm>
#include <iostream>
using namespace v8;

void PassNumber(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  /*Local<Number> target = args[0]->ToNumber();
  double value = target->NumberValue();*/
  double value = args[0]->NumberValue();
  value += 10;

  Local<Number> returnVal = Number::New(isolate, value);
  args.GetReturnValue().Set(returnVal);
}

void ReverseStr(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if(!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Input must be a string")
    ));
  } else {
    v8::String::Utf8Value s(args[0]);
    std::string str(*s);  //wrap in c++
    std::reverse(str.begin(), str.end());

    Local<String> reversedString = String::NewFromUtf8(isolate, str.c_str());
    args.GetReturnValue().Set(reversedString);
  }
}

void IncrementArray(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Array> arr = Local<Array>::Cast(args[0]);

  for(unsigned int i = 0; i < arr->Length(); i++) {
    double value = arr->Get(i)->NumberValue();
    arr->Set(i, Number::New(isolate, value + 1));
  }
  // Since objects (and arrays) are mutable, these changes will be reflected
  // even if we don't explicitly return
}

// Called when addon is require'd from JS
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "passNumber", PassNumber);
  NODE_SET_METHOD(exports, "reverseStr", ReverseStr);
  NODE_SET_METHOD(exports, "incrementArray", IncrementArray);
}

NODE_MODULE(typeConversions, Init)  // macros
