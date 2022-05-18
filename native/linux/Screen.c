#include <node_api.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int countDisplays(Display* display) {
    return XScreenCount(display);
}

int getMainDisplay(Display* display) {
    return XDefaultScreen(display);
}

int getScreenDepth(Display* display,Screen* screen) {
    return DefaultDepthOfScreen(screen);
}

int getWidthOfScreen(Display* display,Screen* screen) {
    return WidthOfScreen(screen);
}

int getHeightOfScreen(Display* display,Screen* screen) {
    return HeightOfScreen(screen);
}

int getY(Display* display,Window window) {
    int rx,ry;
    //window = XRootWindow(display,window);
    Window junkwin;
    XWindowAttributes attrib;
    if(XGetWindowAttributes(display,window,&attrib)) {
       (void) XTranslateCoordinates (display, window, attrib.root, -attrib.border_width,-attrib.border_width,&rx, &ry, &junkwin);
       return ry;
    }
    return -1;
}

int getX(Display* display,Window window) {
    int rx,ry;
    //window = XRootWindow(display,window);
    Window junkwin;
    XWindowAttributes attrib;
    if(XGetWindowAttributes(display,window,&attrib)) {
       (void) XTranslateCoordinates (display, window, attrib.root, -attrib.border_width,-attrib.border_width,&rx, &ry, &junkwin);
       return rx;
    }
    return -1;
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

napi_status _getDisplayInfo(napi_env env,napi_value* display) {
    napi_status status = napi_create_object(env,display);
    Display *d = XOpenDisplay(NULL);
    Window w = RootWindow(d,0);
    int screenCount = countDisplays(d);
    setNumberProperty(env,display,screenCount,"displayCount");

    napi_value screens;
    status = napi_create_array_with_length(env, screenCount, &screens);
    if(status != napi_ok) {
        napi_throw_error(env,NULL,"Unable to create native NodeJS array for screens");
        return status;
    }

    napi_value screen;
    createObject(env,&screen);

    int x = getX(d,w);
    int y = getY(d,w);
    int width = getWidthOfScreen(d,ScreenOfDisplay(d,0));
    int height = getHeightOfScreen(d,ScreenOfDisplay(d,0));
    int builtIn = 1;
    int mainDisplay = 1;
    

   // setNumberProperty(env,&screen,0,"modelNumber"); //add model number
    setNumberProperty(env,&screen,builtIn,"isBuiltIn");
    setNumberProperty(env,&screen,mainDisplay,"isMainDisplay");
    setNumberProperty(env,&screen,width,"width");
    setNumberProperty(env,&screen,height,"height");
    setNumberProperty(env,&screen,x,"x");
    setNumberProperty(env,&screen,y,"y");
    //setNumberProperty(env,&screen,getRotation(),"rotation");
    napi_set_element(env,screens,0,screen);

    status = napi_set_named_property(env, *display, "screens", screens);
    if(status != napi_ok) {
        napi_throw_error(env,NULL,"Unable to set JS 'screens' property name");
        return status;
    }
    return napi_ok;
}