#include <napi.h>
#include <cstring>
#include "./core/core.cpp"
#include "./core/request.h"

using namespace Napi;
using namespace std;

Object sendRequestMiddleman(const CallbackInfo& info) {
  Env env = info.Env();

  Object request = info[0].As<Object>();
  string method, domain, data;

  // Attribute reading
  domain = request.Get("url").As<String>();
  if (request.Has("method")) {
    method = request.Get("method").As<String>();
  } else {
    method = "GET";
  }
  if (request.Has("data")) {
    data = request.Get("data").As<String>();
  } else {
    data = "";
  }

  unordered_map<string, string> response = sendRequest(domain, method, data);

  Object responseObj = Object::New(env);

  unordered_map<string, string>::const_iterator body = response.find("body");
  unordered_map<string, string>::const_iterator headers = response.find("headers");
  
  string vd = body->second;

  responseObj.Set("body", body->second);
  responseObj.Set("headers", headers->second);
  return responseObj;
}

Object Init(Env env, Object exports) {
    return Napi::Function::New(env, sendRequestMiddleman);
}

NODE_API_MODULE(reqless, Init)
