#ifndef CREATION_TIMER_APP_H
#define CREATION_TIMER_APP_H

#include <gtk/gtk.h>
#include <glib-object.h>
#include <stdint.h>
#include <stdio.h>
#include <curl/curl.h>
#include "resources.h"

typedef struct{
    GtkWidget *label;
    unsigned int seconds;
    unsigned int minutes;
    int stop_button_pressed;
} TimerAppData;

void send_time_to_google_sheets(uint8_t minutes, uint8_t seconds);

void tick_second(TimerAppData* data);

static void on_stop_button_clicked (GtkButton *button, gpointer user_data);

static gboolean on_timer_tick(gpointer user_data);

static void on_start_button_clicked (GtkButton *button, gpointer user_data);

static void activate(GtkApplication *app);

#endif