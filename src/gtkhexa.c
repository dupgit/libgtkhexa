/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * gtkhexa.c
 * 
 * 
 * (C) Copyright 2007-2009 Olivier Delhomme
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
/** @file gtkhexa.c
 *  Heavly inspired by GtkTextView
 */

#include "gtkhexa.h"

G_DEFINE_TYPE (GtkHexa, gtk_hexa, GTK_TYPE_WIDGET);

static void gtk_hexa_class_init(GtkHexaClass *class);
static void gtk_hexa_init(GtkHexa *hexa);
static void gtk_hexa_paint(GtkWidget *widget);
static gboolean gtk_hexa_expose(GtkWidget *hexa, GdkEventExpose *event);
static void gtk_hexa_finalize(GObject *object);
static void gtk_hexa_destroy(GtkObject *object);
static void gtk_hexa_realize(GtkWidget *widget);
static void gtk_hexa_size_request(GtkWidget *widget, GtkRequisition *requisition);
static void gtk_hexa_size_allocate(GtkWidget *widget, GtkAllocation *allocation);


/**
 * Class initialisation
 */
static void gtk_hexa_class_init(GtkHexaClass *class)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (class);
    GtkObjectClass *object_class = GTK_OBJECT_CLASS (class);
	GtkWidgetClass *widget_class = NULL;

	object_class->destroy = gtk_hexa_destroy;
    gobject_class->finalize = gtk_hexa_finalize;

	widget_class = GTK_WIDGET_CLASS (class);
	widget_class->expose_event = gtk_hexa_expose;
	widget_class->realize = gtk_hexa_realize;
	widget_class->size_request = gtk_hexa_size_request;
	widget_class->size_allocate = gtk_hexa_size_allocate;
}

/**
 * Inits the widget itself
 */
static void gtk_hexa_init(GtkHexa *hexa)
{
}

static void gtk_hexa_finalize(GObject *object)
{
	 G_OBJECT_CLASS (gtk_hexa_parent_class)->finalize (object);
}

static void gtk_hexa_destroy(GtkObject *object)
{
	  GTK_OBJECT_CLASS (gtk_hexa_parent_class)->destroy (object);
}

static void gtk_hexa_realize(GtkWidget *widget)
{
	GdkWindowAttr attributes;
	gint attributes_mask;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (IS_GTK_HEXA(widget));

	GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
  
	attributes.x = widget->allocation.x;
	attributes.y = widget->allocation.y;
	attributes.width = widget->allocation.width;
	attributes.height = widget->allocation.height;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;
	attributes.visual = gtk_widget_get_visual(widget);
	attributes.colormap = gtk_widget_get_colormap(widget);

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
	
	widget->window = gdk_window_new(gtk_widget_get_parent_window(widget), &attributes, attributes_mask);
	widget->style = gtk_style_attach(widget->style, widget->window);

	gdk_window_set_user_data(widget->window, widget);
	gtk_style_set_background(widget->style, widget->window, GTK_STATE_ACTIVE);
  
}

/**
 * Size negociation
 */
static void gtk_hexa_size_request(GtkWidget *widget, GtkRequisition *requisition)
{
	requisition->width = GTK_HEXA_DEFAULT_WIDTH;
	requisition->height = GTK_HEXA_DEFAULT_HEIGHT;
}

/**
 * Size allocation
 */
static void gtk_hexa_size_allocate(GtkWidget *widget, GtkAllocation *allocation)
{
	GtkHexa *hex;

	g_return_if_fail (widget != NULL);
	g_return_if_fail (IS_GTK_HEXA(widget));
	g_return_if_fail (allocation != NULL);

	widget->allocation = *allocation;
	
	if (GTK_WIDGET_REALIZED(widget))
	{
		hex = GTK_HEXA(widget);
		gdk_window_move_resize(widget->window, allocation->x, allocation->y, allocation->width, allocation->height);
    }
	
}

/**
 * Draws the widget
 */
static void gtk_hexa_paint(GtkWidget *widget)
{
	gdk_window_clear_area(widget->window, 0, 0, widget->allocation.width, widget->allocation.height);
	
}

/**
 * Called when things needs to be redrawn
 */
static gboolean gtk_hexa_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (IS_GTK_HEXA (widget), FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	
	if (event->count > 0)
	{
		return FALSE;
	}
	else
	{
		gtk_hexa_paint(widget);
	
		return FALSE;
	}
}


GtkWidget *gtk_hexa_new (void)
{
	return g_object_new (GTK_TYPE_HEXA, NULL);
}
