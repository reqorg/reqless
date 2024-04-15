#include "core/core.cpp"
#include "core/request.h"
#include <cstring>
#include <napi.h>
#include <sstream>

using namespace Napi;
using namespace std;

Object sendRequestMiddleman(const CallbackInfo &info) {
  // setup environment
  Env env = info.Env();

  // reqless request --> obj
  Object request = info[0].As<Object>();

  string method = "GET", domain, data = "";

  // Attribute reading
  domain = request.Get("url").As<String>();

  if (domain.back() != '/')
    domain.append("/");

  if (request.Has("method")) {
    method = request.Get("method").As<String>();
  }

  if (request.Has("data")) {
    data = request.Get("data").As<String>();
  }

  unordered_map<string, string> response = sendRequest(domain, method, data);

  Object responseObj = Object::New(env);

  unordered_map<string, string>::const_iterator body = response.find("body");
  unordered_map<string, string>::const_iterator headers =
      response.find("headers");

  responseObj.Set("body", body->second);
  responseObj.Set("headers", headers->second);
  return responseObj;
}

Object Init(Env env, Object exports) {
  return Napi::Function::New(env, sendRequestMiddleman);
}

NODE_API_MODULE(reqless, Init)
