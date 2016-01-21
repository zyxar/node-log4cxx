#include "Logger.h"

using namespace v8;

Persistent<Function> Logger::constructor;
Logger::Logger() {}
Logger::~Logger() {}

static Local<String> Stringify(Isolate *isolate, Local<Value> value) {
  if (!value->IsObject()) {
    return value->ToString(isolate);
  }
  Local<Object> JSON = Local<Object>::Cast(
    isolate->GetCurrentContext()->Global()->Get(String::NewFromUtf8(isolate, "JSON")));
  Local<Function> stringify = Local<Function>::Cast(
    JSON->Get(String::NewFromUtf8(isolate, "stringify")));
  Local<Value> object[] = { value };
  return stringify->Call(JSON, 1, object)->ToString(isolate);
} // global.JSON.stringify()

void Logger::Init(Local<Object> exports, Local<Object> module) {
  Isolate *isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Logger"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "trace", Trace);
  NODE_SET_PROTOTYPE_METHOD(tpl, "debug", Debug);
  NODE_SET_PROTOTYPE_METHOD(tpl, "info", Info);
  NODE_SET_PROTOTYPE_METHOD(tpl, "warn", Warn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "error", Error);
  NODE_SET_PROTOTYPE_METHOD(tpl, "fatal", Fatal);

  constructor.Reset(isolate, tpl->GetFunction());
  module->Set(String::NewFromUtf8(isolate, "exports"), tpl->GetFunction());
}

void Logger::New(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    Logger *logger = new Logger();
    std::string logName(*String::Utf8Value(args[0]->ToString(isolate)));
    logger->me = log4cxx::Logger::getLogger(logName);
    logger->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    const int argc = 1;
    Local<Value> argv[argc] = {args[0]};
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Logger::Trace(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (args.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(args.Holder());
#ifdef LOG4CXX_TRACE
  if (!logger->me->isTraceEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getTrace(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
#else
  if (!logger->me->isDebugEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getDebug(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
#endif
}

void Logger::Debug(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (args.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(args.Holder());
  if (!logger->me->isDebugEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getDebug(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Info(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (args.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(args.Holder());
  if (!logger->me->isInfoEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getInfo(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Warn(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (args.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(args.Holder());
  if (!logger->me->isWarnEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getWarn(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Error(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (args.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(args.Holder());
  if (!logger->me->isErrorEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getError(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
}

void Logger::Fatal(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (args.Length() < 1)
    return;
  Logger *logger = ObjectWrap::Unwrap<Logger>(args.Holder());
  if (!logger->me->isFatalEnabled())
    return;
  ::log4cxx::helpers::MessageBuffer oss_;
  int i = 0;
  for (; i < args.Length() - 1; ++i) {
    oss_ << *String::Utf8Value(Stringify(isolate, args[i]));
    oss_ << " ";
  }
  logger->me->forcedLog(
      ::log4cxx::Level::getFatal(),
      oss_.str(oss_ << *String::Utf8Value(Stringify(isolate, args[i]))),
      LOG4CXX_LOCATION);
}