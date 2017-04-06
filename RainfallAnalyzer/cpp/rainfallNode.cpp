#include <node.h>
#include <v8.h>
#include <algorithm>
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

location unpackLocation(Isolate* isolate, const Handle<Object> locationObj) {
  location loc;
  //Handle<Object> locObject = Handle<Object>::Cast(args[0]);

  Handle<Value> latValue = locationObj->Get(String::NewFromUtf8(isolate, "latitude"));
  Handle<Value> lonValue = locationObj->Get(String::NewFromUtf8(isolate, "longitude"));

  loc.latitude = latValue->NumberValue();
  loc.longitude = lonValue->NumberValue();

  Handle<Array> arr = Handle<Array>::Cast(locationObj->Get(String::NewFromUtf8(isolate, "samples")));

  int sampleCount = arr->Length();
  for(int i = 0; i < sampleCount; i++) {
    sample s = unpackSample(isolate, Handle<Object>::Cast(arr->Get(i)));
    loc.samples.push_back(s);
  }
  return loc;
}

void packRainResult(v8::Isolate* isolate, v8::Local<v8::Object>& target, rainResult & result) {
  target->Set(String::NewFromUtf8(isolate, "mean"), Number::New(isolate, result.mean));
  target->Set(String::NewFromUtf8(isolate, "median"), Number::New(isolate, result.median));
  target->Set(String::NewFromUtf8(isolate, "standardDeviation"), Number::New(isolate, result.standardDeviation));
  target->Set(String::NewFromUtf8(isolate, "n"), Number::New(isolate, result.n));
}

void AvgRainfall(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  //location loc = unpackLocation(isolate, args);
  Handle<Object> locObject = Handle<Object>::Cast(args[0]);
  location loc = unpackLocation(isolate, locObject);
  double avg = avgRainfall(loc);

  Local<Number> returnVal = v8::Number::New(isolate, avg);
  args.GetReturnValue().Set(returnVal);
}

void GetSingleLocationRainfallData(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Handle<Object> locObject = Handle<Object>::Cast(args[0]);
  location loc = unpackLocation(isolate, locObject);
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

void GetAllRainfallData(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();
  std::vector<location> locations;
  std::vector<rainResult> results;

  Local<Array> input = Local<Array>::Cast(args[0]);
  unsigned int numLocations = input->Length();
  for(unsigned int i = 0; i < numLocations; i++) {
    locations.push_back(unpackLocation(isolate, Local<Object>::Cast(input->Get(i))));
  }

  results.resize(locations.size());
  std::transform(
    locations.begin(),
    locations.end(),
    results.begin(),
    calculateRainStats
  );

  //convert rainResults into Objects for return
  Local<Array> resultList = Array::New(isolate);
  for(unsigned int i = 0; i < results.size(); i++) {
    Local<Object> result = Object::New(isolate);
    packRainResult(isolate, result, results[i]);
    resultList->Set(i, result);
  }

  //return the list
  args.GetReturnValue().Set(resultList);
}

void Init(Handle<Object> exports, Handle<Object> module) {
  //register our functions here...
  NODE_SET_METHOD(exports, "avgRainfall", AvgRainfall);
  NODE_SET_METHOD(exports, "getSingleLocationRainfallData", GetSingleLocationRainfallData);
  NODE_SET_METHOD(exports, "getAllRainfallData", GetAllRainfallData);
}

//macro to associate module name with initialization logic
NODE_MODULE(rainfall, Init)
