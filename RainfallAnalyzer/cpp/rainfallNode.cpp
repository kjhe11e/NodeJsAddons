#include <node.h>
#include <v8.h>
#include <uv.h>
#include "rainfall.h"

using namespace v8;

sample unpackSample(Isolate* isolate, const Handle<Object> sampleObject) {
  sample s;
  Handle<Value> dateVal = sampleObject->Get(String::NewFromUtf8(isolate, "date"));
  Handle<Value> rainfallVal = sampleObject->Get(String::NewFromUtf8(isolate, "rainfall"));

  v8::String::Utf8Value utfValue(dateVal);
  s.date = std::string(*utfValue);

  // unpack numeric rainfall amount from V8 value
  s.rainfall = rainfallVal->NumberValue();
  return s;
}

location unpackLocation(Isolate* isolate, const v8::FunctionCallbackInfo<v8::Value> & args) {
  location loc;
  Handle<Object> locObject = Handle<Object>::Cast(args[0]);

  Handle<Value> latValue = locObject->Get(String::NewFromUtf8(isolate, "latitude"));
  Handle<Value> lonValue = locObject->Get(String::NewFromUtf8(isolate, "longitude"));

  loc.latitude = latValue->NumberValue();
  loc.longitude = lonValue->NumberValue();

  Handle<Array> arr = Handle<Array>::Cast(locObject->Get(String::NewFromUtf8(isolate, "samples")));

  int sampleCount = arr->Length();
  for(int i = 0; i < sampleCount; i++) {
    sample s = unpackSample(isolate, Handle<Object>::Cast(arr->Get(i)));
    loc.samples.push_back(s);
  }
  return loc;
}

void AvgRainfall(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  location loc = unpackLocation(isolate, args);
  double avg = avgRainfall(loc);

  Local<Number> returnVal = v8::Number::New(isolate, avg);
  args.GetReturnValue().Set(returnVal);
}

void GetRainfallData(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  location loc = unpackLocation(isolate, args);
  rainResult result = calculateRainStats(loc);

  // create new object on V8 heap
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "mean"),
    Number::New(isolate, result.mean));
  obj->Set(String::NewFromUtf8(isolate, "median"),
    Number::New(isolate, result.median));
  obj->Set(String::NewFromUtf8(isolate, "standardDeviation"),
    Number::New(isolate, result.standardDeviation));
  obj->Set(String::NewFromUtf8(isolate, "n"),
    Number::New(isolate, result.n));

  args.GetReturnValue().Set(obj);   //return the object to JS
}

void Init(Handle<Object> exports, Handle<Object> module) {
  //register our functions here...
  NODE_SET_METHOD(exports, "avgRainfall", AvgRainfall);
  NODE_SET_METHOD(exports, "getRainfallData", GetRainfallData);
}

//macro to associate module name with initialization logic
NODE_MODULE(rainfall, Init)
