#include <nan.h>
#include <iostream>
#include "id_scanner.h"

using namespace std;
using namespace Nan;
using namespace v8;

// method implementations here
NAN_METHOD(PassNumber) {
        double value = info[0]->NumberValue();

        Local<Number> returnVal = Nan::New(value);
        info.GetReturnValue().Set(returnVal);
}

NAN_METHOD(PassString) {
        v8::String::Utf8Value val(info[0]->ToString());
        std::string str(*val);
        str = str + " test";

        info.GetReturnValue().Set(
            Nan::New<String>(str.c_str()).ToLocalChecked());
}

NAN_MODULE_INIT(Init) {
        Nan::Set(target,
            New<String>("PassNumber").ToLocalChecked(),
            GetFunction(New<FunctionTemplate>(PassNumber))
            .ToLocalChecked());

        Nan::Set(target,
            New<String>("PassString").ToLocalChecked(),
            GetFunction(New<FunctionTemplate>(PassString))
            .ToLocalChecked());
}

NODE_MODULE(id_scanner, Init)
