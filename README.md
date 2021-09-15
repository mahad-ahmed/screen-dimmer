# screen-dimmer
A small GTK+ app to control screen brightness in Ubuntu below what your hardware(monitor) allows.
Basically a software filter on your display.

</br>

Change `"DVI-I-1"` from this line `sprintf(str, "xrandr --output DVI-I-1 --brightness %.2f", gtk_range_get_value(slider));` to whatever your connected display is called.
</br>You can use `xrandr | grep " connected " | awk '{ print$1 }'` to list your connected displays to choose from.

I have plans to add this into a list in the app itself in the future.

</br>

### Compile dependencies
- gtk3
- glib

Example compilation command: `` gcc screen-dimmer.c -o screen-dimmer `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0 --cflags glib-2.0 --libs glib-2.0` ``

</br>

### Runtime dependencies
- xrandr
- awk
- gtk
