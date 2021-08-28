#include <napi.h>
#include <string>
#include <string.h>

using namespace Napi;
using namespace std;

String sendRequest(const CallbackInfo& info) {
  Env env = info.Env();
  string domain = info[0].As<Napi::String>();
  string method = info[1].As<Napi::String>();
  String re = String::New(env, "request made to " + domain + " with method " + method); 
  return re;
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "req"), Function::New(env, sendRequest));
  return exports;
}

NODE_API_MODULE(hello, Init)
