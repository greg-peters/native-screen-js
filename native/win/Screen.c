#include <node_api.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "windows.h"
#include "winuser.h"
#include "../Screen.h"

napi_value screens;
napi_env gEnv;
uint32_t screenIdx = 0;

uint32_t getRotation();

BOOL CALLBACK EnumMonitorsCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM param)
{
    MONITORINFOEX iMonitor;
    iMonitor.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor,(LPMONITORINFO) &iMonitor);

    //use EnumDisplaySettingsExW  to get extra display information

    napi_value screen;
    createObject(gEnv,&screen);

    uint32_t x = iMonitor.rcMonitor.left;
    uint32_t y = iMonitor.rcMonitor.top;
    uint32_t width = iMonitor.rcMonitor.right - iMonitor.rcMonitor.left;
    uint32_t height = iMonitor.rcMonitor.bottom - iMonitor.rcMonitor.top;
    uint32_t builtIn = x == 0 && y == 0?1:0;
    uint32_t mainDisplay = iMonitor.dwFlags == MONITORINFOF_PRIMARY;
    

   // setNumberProperty(env,&screen,0,"modelNumber"); //add model number
    setNumberProperty(gEnv,&screen,builtIn,"isBuiltIn");
    setNumberProperty(gEnv,&screen,mainDisplay,"isMainDisplay");
    setNumberProperty(gEnv,&screen,width,"width");
    setNumberProperty(gEnv,&screen,height,"height");
    setNumberProperty(gEnv,&screen,x,"x");
    setNumberProperty(gEnv,&screen,y,"y");
    setNumberProperty(gEnv,&screen,getRotation(),"rotation");
    napi_set_element(gEnv,screens,screenIdx++,screen);
    return TRUE;
}

uint32_t getRotation() {
   DEVMODE devmode;
   //DEVMODE structure
   ZeroMemory(&devmode, sizeof(DEVMODE));
   devmode.dmSize = sizeof(DEVMODE);
   devmode.dmFields = DM_DISPLAYORIENTATION;

   //Check display orientation
   EnumDisplaySettingsEx(NULL, ENUM_CURRENT_SETTINGS, &devmode, EDS_RAWMODE); 
   if(devmode.dmDisplayOrientation==DMDO_DEFAULT) {
       return 0;
   }
   if(devmode.dmDisplayOrientation==DMDO_90) {
       return 90;
   }
   if(devmode.dmDisplayOrientation==DMDO_180) {
       return 180;
   }
   if(devmode.dmDisplayOrientation==DMDO_270) {
       return 270;
   }
   return 0; //unable to determine
}


napi_status _getDisplayInfo(napi_env env,napi_value* display) {
    gEnv = env;
    screenIdx = 0; //reset
    napi_status status = napi_create_object(env,display);
    uint32_t screenCount = GetSystemMetrics(SM_CMONITORS);
    setNumberProperty(env,display,screenCount,"displayCount");

    status = napi_create_array_with_length(env, screenCount, &screens);
    if(status != napi_ok) {
        napi_throw_error(env,NULL,"Unable to create native NodeJS array for screens");
        return status;
    }

    EnumDisplayMonitors(NULL, NULL, &EnumMonitorsCallback, 0);

    status = napi_set_named_property(env, *display, "screens", screens);
    if(status != napi_ok) {
        napi_throw_error(env,NULL,"Unable to set JS 'screens' property name");
        return status;
    }
    return napi_ok;
}

napi_status createObject(napi_env env,napi_value* obj) {
    napi_status status = napi_create_object(env,obj);
    if(status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to create native NodeJS object");
    }
    return status;
}

napi_status setNumberProperty(napi_env env,napi_value* obj,uint32_t value,const char* name) {
    napi_value js_value;
    //convert to JS value
    napi_status status = napi_create_int32(env,value,&js_value);
    if(status != napi_ok) {
        napi_throw_error(env,NULL,"Unable to create int32 for JS property");
        return status;
    }
    //create JS property in object and set it's value
    status = napi_set_named_property(env, *obj, name, js_value);
    if(status != napi_ok) {
        napi_throw_error(env,NULL,strcpy("Unable to set JS property name: ",name));
        return status;
    }
    return status;
}
