#import <node_api.h>
#import <Cocoa/Cocoa.h>
#import "../Display.h"

napi_status _getDisplayInfo(napi_env env,napi_value* display) {
    napi_status status = napi_create_object(env,display);
    if(status != napi_ok) {
        napi_throw_error(env, nil, "Unable to create native NodeJS object");
        return status;
    }
    uint32_t screenCount;
    CGGetOnlineDisplayList(INT_MAX, nil, &screenCount); //get number of online screens and store in screenCount
    setNumberProperty(env,display,screenCount,"displayCount");

    CGDirectDisplayID screenList[screenCount];
    CGGetOnlineDisplayList(INT_MAX, screenList, &screenCount);
    napi_value screens;
    status = napi_create_array_with_length(env, screenCount, &screens);
    if(status != napi_ok) {
        napi_throw_error(env,nil,"Unable to create native NodeJS array for screens");
        return status;
    }
    for (int i = 0; i < (int)screenCount; i++) {
        napi_value screen;
        createObject(env,&screen);
        CGDirectDisplayID curScreen = screenList[i];
        setNumberProperty(env,&screen,CGDisplayModelNumber(curScreen),"modelNumber");
        setNumberProperty(env,&screen,CGDisplayIsBuiltin(curScreen),"isBuiltIn");
        setNumberProperty(env,&screen,CGDisplayIsMain(curScreen),"isMainDisplay");
        setNumberProperty(env,&screen,(int)CGDisplayPixelsWide(curScreen),"width");
        setNumberProperty(env,&screen,(int)CGDisplayPixelsHigh(curScreen),"height");
        setNumberProperty(env,&screen,(int)CGDisplayBounds(curScreen).origin.x,"x");
        setNumberProperty(env,&screen,(int)CGDisplayBounds(curScreen).origin.y,"y");
        setNumberProperty(env,&screen,(double)CGDisplayRotation(curScreen),"rotation");
        napi_set_element(env,screens,i,screen);
    }

    status = napi_set_named_property(env, *display, "screens", screens);
    if(status != napi_ok) {
        napi_throw_error(env,nil,"Unable to set JS 'screens' property name");
        return status;
    }
    return napi_ok;
}

napi_status createObject(napi_env env,napi_value* obj) {
    napi_status status = napi_create_object(env,obj);
    if(status != napi_ok) {
        napi_throw_error(env, nil, "Unable to create native NodeJS object");
    }
    return status;
}

napi_status setNumberProperty(napi_env env,napi_value* obj,uint32_t value,const char* name) {
    napi_value js_value;
    //convert to JS value
    napi_status status = napi_create_int32(env,value,&js_value);
    if(status != napi_ok) {
        napi_throw_error(env,nil,"Unable to create int32 for JS property");
        return status;
    }
    //create JS property in object and set it's value
    status = napi_set_named_property(env, *obj, name, js_value);
    if(status != napi_ok) {
        napi_throw_error(env,nil,strcpy("Unable to set JS property name: ",name));
        return status;
    }
    return status;
}