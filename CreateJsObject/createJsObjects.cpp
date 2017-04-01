#include <node.h>
using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Object> target = args[0]->ToObject();

  Local<String> xVal = String::NewFromUtf8(isolate, "x");
  Local<String> yVal = String::NewFromUtf8(isolate, "y");
  Local<String> sum = String::NewFromUtf8(isolate, "sum");
  Local<String> prod = String::NewFromUtf8(isolate, "product");

  if(!target->Get(xVal)->IsNumber()) {
    target->Set(xVal, Number::New(isolate, 0));
  }
  if(!target->Get(yVal)->IsNumber()) {
    target->Set(yVal, Number::New(isolate, 0));
  }

  double x = target->Get(xVal)->NumberValue();
  double y = target->Get(yVal)->NumberValue();

  // create new object to return to V8
  Local<Object> obj = Object::New(isolate);
  obj->Set(sum, Number::New(isolate, x+y));
  obj->Set(prod, Number::New(isolate, x*y));

  args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "createObj", CreateObject);
}

NODE_MODULE(createJsObjects, Init)
