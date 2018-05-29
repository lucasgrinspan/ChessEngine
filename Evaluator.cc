#include"node.h"

void Sum(const v8::FunctionCallbackInfo<v8::Value>& args){
    v8::Isolate* isolate = args.GetIsolate();

    int i = 10;
    auto total = v8::Number::New(isolate, i);

    args.GetReturnValue().Set(total);
}
void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "sum", Sum);
}
NODE_MODULE(Evaluator, Initialize)