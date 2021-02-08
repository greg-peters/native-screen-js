#include <node_api.h>
#include "Display.h"

napi_value getDisplayInfo(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value display;
    status = _getDisplayInfo(env,&display);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to gather display info");
        return NULL;
    } else {
        return display;
    }
}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value getDisplayInfoFn;

    status = napi_create_function(env, NULL, 0, getDisplayInfo, NULL, &getDisplayInfoFn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to wrap native open port function");
    }
    status = napi_set_named_property(env, exports, "getDisplayInfo", getDisplayInfoFn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to populate exports");
    }
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)