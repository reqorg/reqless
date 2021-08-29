#include <napi.h>
#include <cstring>
#include "../core.cpp"
#include "../request.h"

using namespace Napi;
using namespace std;

Object sendMockRequest(const CallbackInfo& info) {
  Env env = info.Env();

  string domain = info[0].As<Napi::String>();
  string method = info[1].As<Napi::String>();
  unordered_map<string, string> response = sendRequest(domain, method);

  Object responseObj = Object::New(env);

  unordered_map<string, string>::const_iterator body = response.find("body");
  unordered_map<string, string>::const_iterator headers = response.find("headers");
  
  string vd = body->second;

  responseObj.Set("body", body->second);
  responseObj.Set("headers", headers->second);
  return responseObj;
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "req"), Function::New(env, sendMockRequest));
  return exports;
}

NODE_API_MODULE(hello, Init)
