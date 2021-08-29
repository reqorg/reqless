#include <napi.h>
#include <cstring>
#include "./core/core.cpp"
#include "./core/request.h"

using namespace Napi;
using namespace std;

Object sendRequestMiddleman(const CallbackInfo& info) {
  Env env = info.Env();

  Object request = info[0].As<Object>();

  string domain = request.Get("url").As<String>();
  string method = request.Get("method").As<String>();
  if (method.empty()) method = "GET";

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
    return Napi::Function::New(env, sendRequestMiddleman);
}

NODE_API_MODULE(reqless, Init)
