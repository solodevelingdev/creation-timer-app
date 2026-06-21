#include <gtk/gtk.h>
#include <glib-object.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    GtkWidget *label;
    unsigned int seconds;
    unsigned int minutes;
    int stop_button_pressed;
} TimerAppData;

void tick_second(TimerAppData* data){

    data->seconds++;

    if(data->seconds >= 60){
        data->seconds = 0;
        data->minutes++;
    }
}

static void
on_stop_button_clicked (GtkButton *button, gpointer user_data)
{
    TimerAppData *data = (TimerAppData *)user_data;

    data->stop_button_pressed=1;
    data->minutes = 0;
    data->seconds = 0;

    char timer_text[8];
    printf("Resetting timer clock\n");
    snprintf(timer_text, sizeof(timer_text), "%02u:%02u", data->minutes, data->seconds);
    gtk_label_set_text (GTK_LABEL (data->label), timer_text);  
}

static gboolean on_timer_tick(gpointer user_data){
    TimerAppData *data = (TimerAppData *)user_data;
    
    
    if(data->stop_button_pressed){
        return G_SOURCE_REMOVE; // 0 (Stops the timer)
    }

    char timer_text[8];
    tick_second(data);
    printf("1 second has passed\n");
    snprintf(timer_text, sizeof(timer_text), "%02u:%02u", data->minutes, data->seconds);
    gtk_label_set_text (GTK_LABEL (data->label), timer_text);  

    return G_SOURCE_CONTINUE;
}

static void
on_start_button_clicked (GtkButton *button, gpointer user_data)
{
    TimerAppData *data = (TimerAppData *)user_data;

    data->stop_button_pressed = 0;

    printf("Button clicked\n");
    printf("Tick-tack\n");

    g_timeout_add(1000, on_timer_tick , data);
    
}

static void activate(GtkApplication *app) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *timer_label;
    GtkWidget *start_button;
    GtkWidget *stop_button;

    TimerAppData *timer_app_data = g_new (TimerAppData, 1);;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK4 on macOS");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Defines the CSS targeting the 'window' node
    const char *css = "window { background-color: red; }";

    // Creates the CSS Provider and load the string (found in GtkCssProvider docs)
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_string (provider, css);
    
    // Create a horizontal box layout for the whole application
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
    gtk_window_set_child (GTK_WINDOW (window), box);
    // TimerData initialization
    timer_app_data->seconds = 0;
    timer_app_data->minutes = 0;
    timer_app_data->stop_button_pressed=0;
    char timer_text[8];
    snprintf(timer_text, sizeof(timer_text), "%02u:%02u", timer_app_data->minutes, timer_app_data->seconds);
    timer_app_data->label = gtk_label_new (timer_text);
    gtk_box_append (GTK_BOX (box), timer_app_data->label);
    printf("timer data and label instantiated\n");
    // Buttons
    // Start Button
    start_button = gtk_button_new_with_label ("Start");
    gtk_box_append (GTK_BOX (box), start_button);    
    // Stop Button
    stop_button = gtk_button_new_with_label ("Stop");
    gtk_box_append (GTK_BOX (box), stop_button);
    // Gets the display and add the provider
    GdkDisplay *display = gdk_display_get_default ();
    gtk_style_context_add_provider_for_display (
        display,
        GTK_STYLE_PROVIDER (provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    // Connect buttons click event to our update function
    g_signal_connect (start_button, "clicked", G_CALLBACK (on_start_button_clicked), timer_app_data);
    g_signal_connect (stop_button, "clicked", G_CALLBACK (on_stop_button_clicked), timer_app_data);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.GtkApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
