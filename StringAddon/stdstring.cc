#include "stdstring.h"

v8::Persistent<v8::Function> StdStringWrapper::constructor;

// Constructor
StdStringWrapper::StdStringWrapper(std::string s) {
  s_ = new std::string(s);
}

// Destructor
StdStringWrapper::~StdStringWrapper() {
  delete s_;
}

void StdStringWrapper::Init(v8::Handle<v8::Object> exports) {
  v8::Local<v8::FunctionTemplate> tmpl = v8::FunctionTemplate::New(New);
  tmpl->SetClassName(v8::String::NewSymbol("StdString"));

  tmpl->InstanceTemplate()->SetInternalFieldCount(2); // for add and toString methods
  tmpl->PrototypeTemplate()->Set(v8::String::NewSymbol("add"), v8::FunctionTemplate::New(add)->GetFunction());
  tmpl->PrototypeTemplate()->Set(v8::String::NewSymbol("toString"), v8::FunctionTemplate::New(toString)->GetFunction());

  constructor = v8::Persistent<v8::Function>::New(tmpl->GetFunction());
  exports->Set(v8::String::NewSymbol("StdString"), constructor);
}

v8::Handle<v8::Value> StdStringWrapper::New(const v8::Arguments& args) {
  v8::HandleScope scope;
  if(args.IsConstructCall()) {
    v8::String::Utf8Value str(args[0]->ToString());
    std::string s(*str);
    StdStringWrapper* obj = new StdStringWrapper(s);
    obj->Wrap(args.This());

    return args.This();
  } else {
    const int argc = 1;

    v8::Handle<v8::Value> StdStringWrapper::add(const v8::Arguments& args) {
      return scope.Close(constructor->NewInstance(argc, argv));
    }
  }
}

v8::Handle<v8::Value> StdStringWrapper::add(const v8::Arguments& args) {
  v8::HandleScope scope;

  v8::String::Utf8Value str(args[0]->ToString());
  std::string s(*str);

  StdStringWrapper* obj = ObjectWrap::Unwrap<StdStringWrapper>(args.This());

  obj->s_->append(s);

  return scope.Close(v8::String::New(obj->s_->c_str()));
}

v8::Handle<v8::Value> StdStringWrapper::toString(const v8::Arguments& args) {
  v8::HandleScope scope;

  StdStringWrapper* obj = ObjectWrap::Unwrap<StdStringWrapper>(args.This());

  return scope.Close(v8::String::New(obj->s_->c_str()));
}
