#include <node.h>
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

// Called when addon is require'd from JS
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "passNumber", PassNumber);
}

NODE_MODULE(passNumber, Init)  // macro
