#include <node.h>
using namespace v8;

void CallThis(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Function> cb = Local<Function>::Cast(args[0]);

  //the Call method accepts three parameters:
  // 1) Receiver - JS object that 'this' will be bound to when the JS
  // callback is invoked. Setting to null will just set 'this' to whatever
  // the default is within the JS code
  // 2) Number of Args - number of params to pass to callback when executed
  // 3) Arguments - null in this case, but can pass an array of Local<Value> objects
  cb->Call(Null(isolate), 0, nullptr);
  return;   //undefined is returned to JS
}

void CallThisWithThis(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Function> cb = Local<Function>::Cast(args[0]);

  //create an array with only the argument passed in (i.e. the message)
  Local<Value> argv[1] = {args[1]};
  cb->Call(Null(isolate), 1, argv);
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(exports, "callThis", CallThis);
  NODE_SET_METHOD(exports, "callThisWithThis", CallThisWithThis);
}

NODE_MODULE(callbackWithParams, Init)   //macro
