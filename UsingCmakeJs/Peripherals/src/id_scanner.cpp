#include <nan.h>
#include <iostream>
#include <vector>
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

string getStatusMessage(int statusCode, vector<string>& messages) {
    // TODO: error checking here...
    return messages[statusCode];
}

NAN_METHOD(GetStatus) {
        int statusCode = info[0]->IntegerValue();

        Callback *callback = new Callback(info[1].As<Function>());
        vector<string> messages;
        messages.push_back("zero");
        messages.push_back("one");
        messages.push_back("two");
        messages.push_back("three");

        string statusMessageResult = getStatusMessage(statusCode, messages);

        v8::Local<String> returnVal = Nan::New<String>(statusMessageResult).ToLocalChecked();
        info.GetReturnValue().Set(returnVal);
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

        Nan::Set(target,
            New<String>("GetStatus").ToLocalChecked(),
            GetFunction(New<FunctionTemplate>(GetStatus))
            .ToLocalChecked());
}

NODE_MODULE(id_scanner, Init)
