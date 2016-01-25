#ifndef Logger_h
#define Logger_h

#include <log4cxx/logger.h>
#include <log4cxx/helpers/exception.h>
#include <node.h>
#include <node_object_wrap.h>

class Logger : public node::ObjectWrap {
public:
  static void Init(v8::Local<v8::Object>, v8::Local<v8::Object>);
  log4cxx::LoggerPtr me;

private:
  // construction
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value> &);
  // prototype
  static void Trace(const v8::FunctionCallbackInfo<v8::Value> &);
  static void Debug(const v8::FunctionCallbackInfo<v8::Value> &);
  static void Info(const v8::FunctionCallbackInfo<v8::Value> &);
  static void Warn(const v8::FunctionCallbackInfo<v8::Value> &);
  static void Error(const v8::FunctionCallbackInfo<v8::Value> &);
  static void Fatal(const v8::FunctionCallbackInfo<v8::Value> &);
  static void GetLevel(const v8::FunctionCallbackInfo<v8::Value> &);

  explicit Logger();
  ~Logger();
};

#endif
