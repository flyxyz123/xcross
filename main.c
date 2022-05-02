// edit source code from: https://github.com/gvalkov/xrectsel
//#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>

//int main (int argc, char *argv[])
int main (void)
{
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
	//printf("%d\n", DisplayWidth(disp, DefaultScreen(disp)));
	//printf("%d\n\n", DisplayHeight(disp, DefaultScreen(disp)));
	// XGetGeometry() maybe better, instead of DisplayHeight() and DisplayWidth()
	XDrawLine(disp, root, gc, rootx, 0, rootx, DisplayHeight(disp, DefaultScreen(disp)));
	XDrawLine(disp, root, gc, 0, rooty, DisplayWidth(disp, DefaultScreen(disp)), rooty);
	//XDrawRectangle(disp, root, gc, 1000, 1000, 1000, 1000);
	XFlush(disp);

    XUngrabPointer(disp, CurrentTime);
    XUngrabKeyboard(disp, CurrentTime);
	//XFreeCursor(disp, cursor);
    XFreeGC(disp, gc);
    XSync(disp, True);

    XCloseDisplay(disp);

	return 0;
}
