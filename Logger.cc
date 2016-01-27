#include "Logger.h"

using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Function;
using v8::Handle;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::TryCatch;
using v8::Value;

Persistent<Function> Logger::constructor;
Logger::Logger() {}
Logger::~Logger() {}

static Local<String> Stringify(Isolate *isolate, Handle<Value> value) {
  if (!value->IsObject()) {
    return value->ToString(isolate);
  }
  Local<Object> JSON =
      Local<Object>::Cast(isolate->GetCurrentContext()->Global()->Get(
          String::NewFromUtf8(isolate, "JSON")));
  Local<Function> stringify = Local<Function>::Cast(
      JSON->Get(String::NewFromUtf8(isolate, "stringify")));
  Local<Value> object[] = {value};
  TryCatch try_catch;
  auto ret = stringify->Call(JSON, 1, object);
  if (try_catch.HasCaught()) {
    return value->ToString(isolate);
  }
  return ret->ToString();
} // global.JSON.stringify()

void Logger::Init(Handle<Object> exports, Handle<Object> module) {
  Isolate *isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Log4cxx"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "trace", Trace);
  NODE_SET_PROTOTYPE_METHOD(tpl, "debug", Debug);
  NODE_SET_PROTOTYPE_METHOD(tpl, "info", Info);
  NODE_SET_PROTOTYPE_METHOD(tpl, "warn", Warn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "error", Error);
  NODE_SET_PROTOTYPE_METHOD(tpl, "fatal", Fatal);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getLevel", GetLevel);

  constructor.Reset(isolate, tpl->GetFunction());
  module->Set(String::NewFromUtf8(isolate, "exports"), tpl->GetFunction());
}

void Logger::New(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  if (arguments.IsConstructCall()) {
    Logger *logger = new Logger();
    std::string logName(*String::Utf8Value(arguments[0]->ToString(isolate)));
    logger->me = log4cxx::Logger::getLogger(logName);
    logger->Wrap(arguments.This());
    arguments.GetReturnValue().Set(arguments.This());
  } else {
    Local<Value> argv[] = {arguments[0]};
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    arguments.GetReturnValue().Set(cons->NewInstance(1, argv));
  }
}

void Logger::Trace(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  arguments.GetReturnValue().Set(arguments.This());
  if (arguments.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(arguments.Holder());
#ifdef LOG4CXX_TRACE
  if (!logger->me->isTraceEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getTrace(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
#else
  if (!logger->me->isDebugEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getDebug(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
#endif
}

void Logger::Debug(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  arguments.GetReturnValue().Set(arguments.This());
  if (arguments.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(arguments.Holder());
  if (!logger->me->isDebugEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getDebug(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Info(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  arguments.GetReturnValue().Set(arguments.This());
  if (arguments.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(arguments.Holder());
  if (!logger->me->isInfoEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getInfo(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Warn(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  arguments.GetReturnValue().Set(arguments.This());
  if (arguments.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(arguments.Holder());
  if (!logger->me->isWarnEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getWarn(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Error(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  arguments.GetReturnValue().Set(arguments.This());
  if (arguments.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(arguments.Holder());
  if (!logger->me->isErrorEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getError(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Fatal(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  arguments.GetReturnValue().Set(arguments.This());
  if (arguments.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(arguments.Holder());
  if (!logger->me->isFatalEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < arguments.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getFatal(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, arguments[i]))),
      LOG4CXX_LOCATION);
}

void Logger::GetLevel(const FunctionCallbackInfo<Value> &arguments) {
  Isolate *isolate = arguments.GetIsolate();
  auto p = ObjectWrap::Unwrap<Logger>(arguments.Holder())->me;
  while (p->getLevel() == nullptr && p != log4cxx::Logger::getRootLogger()) {
    p = p->getParent();
  }
  arguments.GetReturnValue().Set(
      String::NewFromUtf8(isolate, p->getLevel()->toString().c_str()));
}

NODE_MODULE(Logger, Logger::Init)
