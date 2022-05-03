// edit source code from:
// https://github.com/gvalkov/xrectsel

//#include <stdio.h>
#include <X11/Xlib.h>

//int main (int argc, char *argv[])
int main (void)
{
	// useless trash vars
    int int_tmp;
    unsigned int uint_tmp;
	Window window_tmp;

	int rootx=0, rooty=0;

	Display * disp = XOpenDisplay(NULL);
    Screen * scr = ScreenOfDisplay(disp, DefaultScreen(disp));
    Window root = RootWindow(disp, XScreenNumberOfScreen(scr));

    XGCValues gcval;
    gcval.foreground = XWhitePixel(disp, 0);
    gcval.function   = GXxor;
    gcval.background = XBlackPixel(disp, 0);
    gcval.plane_mask = gcval.background ^ gcval.foreground;
    gcval.subwindow_mode = IncludeInferiors;
    GC gc = XCreateGC(disp, root,
                      GCFunction|GCForeground|GCBackground|GCSubwindowMode,
                      &gcval);

	XQueryPointer(disp, root, &window_tmp, &window_tmp, &rootx, &rooty, &int_tmp, &int_tmp, &uint_tmp);
	//printf("pointer coordinates x: %d, y: %d\n", rootx, rooty);
	//printf("screen width: %d, height: %d\n", scr->width, scr->height);
	XDrawLine(disp, root, gc, rootx, 0, rootx, scr->height);
	XDrawLine(disp, root, gc, 0, rooty, scr->width, rooty);

	// not sure if useful
	//XFlush(disp);
    //XFreeGC(disp, gc);
    //XSync(disp, True);

	// man XCloseDisplay says: "Before exiting, you should call XCloseDisplay explicitly so that any pending errors are reported as XCloseDisplay performs a final XSync operation."
    XCloseDisplay(disp);

	return 0;
}
