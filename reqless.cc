#include <napi.h>
#include <cstring>
#include <sstream>
#include "./core/core.cpp"
#include "./core/request.h"

using namespace Napi;
using namespace std;

Object parseHeaders(Env env, const string headers) {
  Object headersObj = Object::New(env);
  
  string result;
  istringstream iss(headers);

  const string delimiter = ": ";
  for (string line; getline(iss, line); ) {
      string key = line.substr(0, line.find(delimiter));
      line.erase(0, line.find(delimiter) + delimiter.length());
      string value = line.substr(0, line.find(delimiter));
      value.erase(value.find("\r"), 1);
      headersObj.Set(key, value);
  }
  return headersObj;
}

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

  Object headersObj = parseHeaders(env, headers->second);

  responseObj.Set("body", body->second);
  responseObj.Set("headers", headersObj);
  return responseObj;
}

Object Init(Env env, Object exports) {
    return Napi::Function::New(env, sendRequestMiddleman);
}

NODE_API_MODULE(reqless, Init)
