#include <node.h>
using namespace v8;

void CallThis(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Function> cb = Local<Function>::Cast(args[0]);
  cb->Call(Null(isolate), 0, nullptr);
  return;   //undefined is returned to JS
}

//called when function is require'd in JS
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "callThis", CallThis);
}

NODE_MODULE(callback, Init)   //macro
