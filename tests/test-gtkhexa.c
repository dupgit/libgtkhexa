/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * test-gtkhexa.c
 *
 *
 * (C) Copyright 2009 Olivier Delhomme
 * e-mail : heraia@delhomme.org
 * URL    : http://heraia.tuxfamily.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or  (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;  without even the implied warranty of
 * MERCHANTABILITY  or  FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
/**
 * @file test-gtkhexa.c
 * gtkhexa test prohram main source file.
 */
/**
 * @author Olivier DELHOMME,
 * @version 0.0.1
 * @date 2009
 */

#include "test-gtkhexa.h"

static GladeXML *load_glade_xml_if_it_exists(gchar *file_to_load);
static void on_quit_activate(GtkWidget *widget, gpointer data);
static gboolean delete_main_window_event(GtkWidget *widget, GdkEvent  *event, gpointer data);

/**
 *  Checks if file_to_load exists and is valid and if possible, loads it
 *  in the xml structure
 * @param file_to_load : a filename of a possibly existing glade file
 * @return returns the GladeXML structure if any, NULL otherwise
 */
static GladeXML *load_glade_xml_if_it_exists(gchar *file_to_load)
{
    struct stat *stat_buf;
    GladeXML *xml = NULL;

    stat_buf = (struct stat *) g_malloc0 (sizeof(struct stat));

    stat(file_to_load, stat_buf);
    if (S_ISREG(stat_buf->st_mode) && stat_buf->st_size>0)
        {
            xml = glade_xml_new(file_to_load, NULL, NULL);
        }
    else
        {
            xml = NULL;
        }

    g_free(stat_buf);

    return xml;
}

/**
 *  Quit, file menu
 * @param widget : the widget that issued the signal
 * @param data : may be NULL
 */
static void on_quit_activate(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

/**
 * When the user destroys or delete the main window
 * @param widget : calling widget
 * @param event : event associated (may be NULL as we don't use this here)
 * @param data :may be NULL
 */
static gboolean delete_main_window_event(GtkWidget *widget, GdkEvent  *event, gpointer data)
{

    on_quit_activate(widget, data);

    return FALSE;
}

/**
 *  Connect the signals at the interface
 */
static void ui_connect_signals(GladeXML *xml)
{
    if (xml != NULL)
    {
        /* Quit, file menu */
        g_signal_connect (G_OBJECT (glade_xml_get_widget(xml, "quit")), "activate", G_CALLBACK (on_quit_activate), NULL);
        g_signal_connect (G_OBJECT (glade_xml_get_widget(xml, "window1")), "delete-event",  G_CALLBACK (delete_main_window_event), NULL);
    }
}


/**
 *  Here we want to init the location list where we might look for
 *  in the future. These can be viewed as default paths
 *  @warning when adding new locations, keep in ming that the list is a
             prepended list in reverse order.
 *  @return a new allocatde GList containing all locations
 */
static GList *init_location_list(void)
{
    gchar *path = NULL;
    const gchar* const *system_data_dirs;
    guint i = 0;
    GList *location_list = NULL;

    /* current path */
    path = g_strdup_printf("%s", g_get_current_dir());
    location_list = g_list_prepend(location_list, path);

    /* System data dirs */
    system_data_dirs = g_get_system_data_dirs();
    i = 0;
    while(system_data_dirs[i] != NULL)
        {
            path = g_strdup_printf("%s%c%s", system_data_dirs[i], G_DIR_SEPARATOR, "heraia");
            location_list = g_list_prepend(location_list, path);
            i++;
        }

    /* System config dirs */
    system_data_dirs = g_get_system_config_dirs();
    i = 0;
    while(system_data_dirs[i] != NULL)
        {
            path = g_strdup_printf("%s%c%s", system_data_dirs[i], G_DIR_SEPARATOR, "heraia");
            location_list = g_list_prepend(location_list, path);
            i++;
        }

    /* the user path */
    path =  g_strdup_printf("%s%c.%s", g_get_home_dir(), G_DIR_SEPARATOR, "heraia");
    location_list = g_list_prepend(location_list, path);

    /* A global user data path */
    path = g_strdup_printf("%s%c%s", g_get_user_data_dir(), G_DIR_SEPARATOR, "heraia");
    location_list = g_list_prepend(location_list, path);

    /* A global config data path */
    path = g_strdup_printf("%s%c%s", g_get_user_config_dir(), G_DIR_SEPARATOR, "heraia");
    location_list = g_list_prepend(location_list, path);

    return location_list;
}


/**
 * @fn GladeXML *load_glade_xml_file(GList *location_list, gchar *filename)
 *  loads the glade xml file ('filename') that describes an interface,
 *  tries all the paths defined in the location_list and put the definition
 *  in the 'xml' variable. A frontend to load_glade_xml_if_it_exists function
 * @param location_list : a Glist containing paths where we might found the file
 * @param filename : glade's file's name that we want to load (possibly)
 * @return returns the GladeXML structure if any, NULL otherwise
 */
GladeXML *load_glade_xml_file(GList *location_list, gchar *filename)
{
    gchar *file_to_load = NULL;
    GList *list = g_list_first(location_list);
    GladeXML *xml = NULL;

    while (list != NULL && xml == NULL)
        {
            file_to_load =  g_build_filename((gchar *) list->data, filename, NULL);

            xml = load_glade_xml_if_it_exists(file_to_load);

            if (xml == NULL)
                {
                    list = list->next;
                }
            g_free(file_to_load);
        }

    return xml;
}


/**
 * main program
 */
int main (int argc, char ** argv)
{
    gboolean exit_value = TRUE;
    GladeXML *xml = NULL;
    exit_value = gtk_init_check(&argc, &argv);
    GtkWidget *HexWidget = NULL;
    GtkWidget *vbox = NULL;
    GList *location = NULL;


    location = init_location_list();
    xml = load_glade_xml_file(location, "test-gtkhexa.glade");

    if (xml != NULL)
        {
            ui_connect_signals(xml);

            HexWidget = gtk_hexa_new();

            vbox = glade_xml_get_widget(xml, "hbox1");
            gtk_box_pack_start(GTK_BOX(vbox), HexWidget, TRUE, TRUE, 2);

            gtk_widget_show_all(glade_xml_get_widget(xml, "window1"));

            gtk_main();
        }
    else
        {
            fprintf(stderr, "Failed to load file test-gtkhexa.glade");
            exit_value = 2;
        }

    return exit_value;
}
