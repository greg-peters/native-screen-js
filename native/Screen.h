#ifndef SCREEN_H
#define SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif
 
/*****************************************************************************/
napi_status _getDisplayInfo(napi_env env, napi_value* display); 
napi_status setNumberProperty(napi_env env,napi_value* object,uint32_t value,const char* name);
napi_status createObject(napi_env env,napi_value* object);

#ifdef __cplusplus
}
#endif

#endif // SCREEN_H