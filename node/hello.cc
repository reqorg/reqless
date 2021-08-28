#include <napi.h>
#include <string>
#include <string.h>
#include "../request.h"

using namespace Napi;
using namespace std;

String sendMockRequest(const CallbackInfo& info) {
  Env env = info.Env();
  string domain = info[0].As<Napi::String>();
  string method = info[1].As<Napi::String>();
  string response = sendRequest(domain, method);
  String re = String::New(env, "aaa"); 
  return re;
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "req"), Function::New(env, sendMockRequest));
  return exports;
}

NODE_API_MODULE(hello, Init)
