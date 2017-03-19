// strToInt.cpp
#include <string>
#include <nan.h>

using namespace std;

void StrToInt(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if(info.Length() < 1) {
    Nan::ThrowTypeError("Expecting a string");
    return;
  }

  if(!info[0]->IsString()) {
    Nan::ThrowTypeError("Argument must be a string");
    return;
  }

  v8::String::Utf8Value arg0(info[0]->ToString());
  std::string input = std::string(*arg0);
  v8::Local<v8::Integer> result = Nan::New(stoi(input));

  info.GetReturnValue().Set(result);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("strToInt").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(StrToInt)->GetFunction());
}

NODE_MODULE(strToInt, Init)
