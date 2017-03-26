#include <cmath>
#include <node.h>
using namespace v8;

void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if(args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Expecting 2 arguments (as numbers)")
    ));
    return;
  }

  if(!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Both args must be numbers")
    ));
    return;
  }

  // value created on C++ runtime stack, not in the JS execution context
  double val = args[0]->NumberValue() + args[1]->NumberValue();

  // now create in JS execution context so we can return it
  Local<Number> num = Number::New(isolate, val);
  args.GetReturnValue().Set(num);
}

// Called when addon is require'd from JS
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(cmath, Init)  // macro
