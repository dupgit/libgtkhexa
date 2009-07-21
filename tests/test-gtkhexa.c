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
 * main program
 */
int main (int argc, char ** argv)
{
	gboolean exit_value = TRUE;
	GladeXML *xml = NULL;
	exit_value = gtk_init_check(&argc, &argv);
	GtkWidget *HexWidget = NULL;
	GtkWidget *vbox = NULL;

	/** @todo Everything is Ugly here --> will need improvements */
	xml = load_glade_xml_if_it_exists("/media/disk/projets/Fichiers/Heraia/heraia/libgtkhexa/trunk/tests/test-gtkhexa.glade");
	
	ui_connect_signals(xml);
	
	HexWidget = gtk_hexa_new();
	
	vbox = glade_xml_get_widget(xml, "hbox1");
	gtk_box_pack_start(GTK_BOX(vbox), HexWidget, FALSE, FALSE, 2);
	
	gtk_widget_show_all(glade_xml_get_widget(xml, "window1"));
	
	gtk_main();
	
	return exit_value;
}
