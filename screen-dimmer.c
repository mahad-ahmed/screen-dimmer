#include <gtk/gtk.h>
#include <stdlib.h>

// Callback function for when the slider value is changed
static void on_value_changed(GtkRange *slider, gfloat data) {
    char str[50];
    // You can use the following command to list your connected displays: xrandr | grep " connected " | awk '{ print$1 }'
    // If you're feeling productive, you can use popen and display a list of monitors to choose from in this app
    // Change DVI-I-1 in the string to whatever display you want to control
    sprintf(str, "xrandr --output DVI-I-1 --brightness %.2f", gtk_range_get_value(slider));
    system(str);
}

// Application start callback
static void on_app_activate(GApplication *app, gpointer data) {
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    
    GtkWidget* slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.1, 1.0, 0.01);
    
    /* Try to get the current brightness and set it as initial slider value */
    char output[16];
    FILE *fp = popen("xrandr --verbose | awk '/Brightness/ { print $2; exit }'", "r");
    if(fp != NULL) {
        while(fgets(output, sizeof(output), fp) != NULL) {
            double current = strtod(output, NULL);
            if(current <= 0 || current > 1.0) {
                current = 0.1;
            }
            gtk_range_set_value((GtkRange*) slider, current);
        }
        
        pclose(fp);
    }
    
    g_signal_connect(slider, "value-changed", G_CALLBACK(on_value_changed), NULL);
    gtk_container_add(GTK_CONTAINER(window), slider);
    
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new(
        "com.atompunkapps.ScreenDimmer", 
        G_APPLICATION_FLAGS_NONE
    );
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // deallocate the application object
    g_object_unref(app);
    return status;
}
