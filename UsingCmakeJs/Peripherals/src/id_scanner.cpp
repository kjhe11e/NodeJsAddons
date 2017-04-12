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

NAN_MODULE_INIT(Init) {
        Nan::Set(target,
            New<String>("PassNumber").ToLocalChecked(),
            GetFunction(New<FunctionTemplate>(PassNumber))
            .ToLocalChecked());
}

NODE_MODULE(id_scanner, Init)
