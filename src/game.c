#include <X11/Xlib.h>
#include <string.h>

#include "ulog.h"

int main(void)
{
    ulog_setup();

    Display* dpy = XOpenDisplay(NULL);
    if (!dpy)
    {
        log_error("Cannot open display\n");
        return 1;
    }

    int    screen = DefaultScreen(dpy);
    Window root   = RootWindow(dpy, screen);

    unsigned long black = BlackPixel(dpy, screen);
    unsigned long white = WhitePixel(dpy, screen);

    Window win = XCreateSimpleWindow(dpy, root, 100, 100, 400, 200, 1, black, black);

    Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dpy, win, &WM_DELETE_WINDOW, 1);

    XSelectInput(dpy, win, ExposureMask | KeyPressMask | StructureNotifyMask);

    GC gc = XCreateGC(dpy, win, 0, NULL);
    XSetForeground(dpy, gc, white);

    XMapWindow(dpy, win);
    log_info("Showing window on the screen");

    for (;;)
    {
        XEvent ev;
        XNextEvent(dpy, &ev);

        if (ev.type == Expose)
        {
            const char* msg = "Hello, world (X11)!";
            int         x = 50, y = 100;
            XDrawString(dpy, win, gc, x, y, msg, (int)strlen(msg));
        }
        else if (ev.type == KeyPress)
        {
            continue;
        }
        else if (ev.type == ClientMessage)
        {
            if ((Atom)ev.xclient.data.l[0] == WM_DELETE_WINDOW)
                break;
        }
    }

    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}
