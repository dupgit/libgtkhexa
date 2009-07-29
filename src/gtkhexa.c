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
 *  Inspired by GtkTextView, GtkDial example, GtkAlignment...
 */

#include "gtkhexa.h"

static void gtk_hexa_class_init(GtkHexaClass *class);
static void gtk_hexa_init(GtkHexa *hexa);
static void gtk_hexa_paint(GtkWidget *widget, GdkRectangle *area);
static gboolean gtk_hexa_expose(GtkWidget *hexa, GdkEventExpose *event);
static void gtk_hexa_finalize(GObject *object);
static void gtk_hexa_destroy(GtkObject *object);
static void gtk_hexa_realize(GtkWidget *widget);
static void gtk_hexa_size_request(GtkWidget *widget, GtkRequisition *requisition);
static void gtk_hexa_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static void gtk_hexa_update (GtkHexa *hexa);
static void gtk_hexa_adjustment_changed(GtkAdjustment *adjustment, gpointer data);
static void gtk_hexa_adjustment_value_changed(GtkAdjustment *adjustment, gpointer data);
static void gtk_hexa_add(GtkContainer *container, GtkWidget *child);

G_DEFINE_TYPE (GtkHexa, gtk_hexa, GTK_TYPE_CONTAINER);

/**
 * Class initialisation
 */
static void gtk_hexa_class_init(GtkHexaClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    GtkObjectClass *object_class = GTK_OBJECT_CLASS(klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    GtkContainerClass *container_class = GTK_CONTAINER_CLASS(klass);
  
	object_class->destroy = gtk_hexa_destroy;
    gobject_class->finalize = gtk_hexa_finalize;

	widget_class = GTK_WIDGET_CLASS(klass);
	
	widget_class->realize = gtk_hexa_realize;
	widget_class->expose_event = gtk_hexa_expose;
	widget_class->size_request = gtk_hexa_size_request; 
	widget_class->size_allocate = gtk_hexa_size_allocate;
	
	container_class->add = gtk_hexa_add;	
}

/**
 * Container Stuff
 */

/**
 * Adds GtkHexa Widget to another one
 * @param container
 * @param child
 * This should add child to container ?
 */
static void gtk_hexa_add(GtkContainer *container, GtkWidget *child)
{
	
}



/**
 * Inits the widget itself
 */
static void gtk_hexa_init(GtkHexa *hexa)
{
	GtkWidget *scroll = NULL;
	GtkWidget *vbox = NULL;
	
	hexa->adjustment = (GtkAdjustment*) gtk_adjustment_new(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	
	vbox = gtk_vbox_new(FALSE, 2);
	scroll = gtk_scrolled_window_new(NULL, NULL);
	 
	gtk_container_add(GTK_CONTAINER(hexa), vbox);
	gtk_box_pack_end(GTK_BOX(vbox), scroll, FALSE, FALSE, 2);
	gtk_widget_show(scroll);
}

static void gtk_hexa_finalize(GObject *object)
{
	 G_OBJECT_CLASS(gtk_hexa_parent_class)->finalize (object);
}

static void gtk_hexa_destroy(GtkObject *object)
{
	  GTK_OBJECT_CLASS(gtk_hexa_parent_class)->destroy (object);
}


/**
 * Adjustement stuff
 */
GtkAdjustment *gtk_hexa_get_adjustment(GtkHexa *hexa)
{
  g_return_val_if_fail(hexa != NULL, NULL);
  g_return_val_if_fail(GTK_IS_HEXA(hexa), NULL);

  return hexa->adjustment;
}

void gtk_hexa_set_update_policy(GtkHexa *hexa, GtkUpdateType policy)
{
  g_return_if_fail(hexa != NULL);
  g_return_if_fail(GTK_IS_HEXA(hexa));

  hexa->policy = policy;
}

void gtk_hexa_set_adjustment (GtkHexa *hexa, GtkAdjustment *adjustment)
{
  g_return_if_fail(hexa != NULL);
  g_return_if_fail(GTK_IS_HEXA (hexa));

  if (hexa->adjustment)
    {
      gtk_signal_disconnect_by_data(GTK_OBJECT (hexa->adjustment), (gpointer) hexa);
      gtk_object_unref(GTK_OBJECT (hexa->adjustment));
    }

  hexa->adjustment = adjustment;
  gtk_object_ref(GTK_OBJECT (hexa->adjustment));

  gtk_signal_connect(GTK_OBJECT(adjustment), "changed", (GtkSignalFunc) gtk_hexa_adjustment_changed, (gpointer) hexa);
  gtk_signal_connect(GTK_OBJECT(adjustment), "value_changed", (GtkSignalFunc) gtk_hexa_adjustment_value_changed, (gpointer) hexa);

  hexa->adjustement_changed = TRUE;

  gtk_hexa_update(hexa);
}

static void gtk_hexa_update (GtkHexa *hexa)
{
  gfloat new_value = 0.0;
  
  g_return_if_fail(hexa != NULL);
  g_return_if_fail(GTK_IS_HEXA(hexa));

  new_value = hexa->adjustment->value;
  
  if (new_value < hexa->adjustment->lower)
    new_value = hexa->adjustment->lower;

  if (new_value > hexa->adjustment->upper)
    new_value = hexa->adjustment->upper;

  if (new_value != hexa->adjustment->value)
    {
      hexa->adjustment->value = new_value;
      gtk_signal_emit_by_name(GTK_OBJECT(hexa->adjustment), "value_changed");
    }

  gtk_widget_draw(GTK_WIDGET(hexa), NULL);
}

static void gtk_hexa_adjustment_changed(GtkAdjustment *adjustment, gpointer data)
{
  GtkHexa *hexa;

  g_return_if_fail(adjustment != NULL);
  g_return_if_fail(data != NULL);

  hexa = GTK_HEXA(data);

  if (hexa->adjustement_changed == TRUE)
	{
		gtk_hexa_update(hexa);
		hexa->adjustement_changed = FALSE;
    }
}

static void gtk_hexa_adjustment_value_changed(GtkAdjustment *adjustment, gpointer data)
{
  GtkHexa *hexa;

  g_return_if_fail(adjustment != NULL);
  g_return_if_fail(data != NULL);

  hexa = GTK_HEXA(data);

  if (hexa->adjustement_changed == TRUE)
    {
      gtk_hexa_update (hexa);
      hexa->adjustement_changed = FALSE;
    }
}

/**
 * Creating the window
 * @param widget : the widget to be realized
 */
static void gtk_hexa_realize(GtkWidget *widget)
{
	GdkWindowAttr attributes;
	gint attributes_mask;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_HEXA(widget));
	
    GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
  
	attributes.x = widget->allocation.x;
	attributes.y = widget->allocation.y;
	attributes.width = widget->allocation.width;
	attributes.height = widget->allocation.height;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.event_mask = GDK_VISIBILITY_NOTIFY_MASK | GDK_EXPOSURE_MASK;
	attributes.visual = gtk_widget_get_visual(widget);
	attributes.colormap = gtk_widget_get_colormap(widget);

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
	
	widget->window = gdk_window_new(gtk_widget_get_parent_window(widget), &attributes, attributes_mask);
	gdk_window_set_user_data(widget->window, widget);
	widget->style = gtk_style_attach(widget->style, widget->window);
    gdk_window_set_background(widget->window, &widget->style->bg[GTK_WIDGET_STATE (widget)]);
}

/**
 * Size negociation
 */
static void gtk_hexa_size_request(GtkWidget *widget, GtkRequisition *requisition)
{
	requisition->width = GTK_HEXA_DEFAULT_WIDTH + GTK_CONTAINER (widget)->border_width * 2;
	requisition->height = GTK_HEXA_DEFAULT_HEIGHT + GTK_CONTAINER (widget)->border_width * 2;
}

/**
 * Size allocation
 */
static void gtk_hexa_size_allocate(GtkWidget *widget, GtkAllocation *allocation)
{
	GtkHexa *hexa;

	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_HEXA(widget));
	g_return_if_fail (allocation != NULL);

	widget->allocation = *allocation;

	if (GTK_WIDGET_REALIZED(widget))
	{
		hexa = GTK_HEXA(widget);
		gdk_window_move_resize(widget->window, allocation->x, allocation->y, allocation->width, allocation->height);	
    }
}

/**
 * Draws the widget
 * @param widget : the widget itself
 * @param area represents the part that must be redrawned
 */
static void gtk_hexa_paint(GtkWidget *widget, GdkRectangle *area)
{			

	gint num_bytes_size = 0;
	gint hexa_view_size = 0;
	gint char_view_size = 0;
	
/*	
	num_bytes_size = (gint) ((widget->allocation.width-10) * 0.10);
	hexa_view_size = (gint) ((widget->allocation.width-10) * 0.70);
	char_view_size = (gint) ((widget->allocation.width-10) * 0.30);
	
	gtk_paint_box(widget->style, widget->window, GTK_STATE_NORMAL, GTK_SHADOW_OUT, area, widget, NULL, 0, 0, num_bytes_size, widget->allocation.height);
	gtk_paint_box(widget->style, widget->window, GTK_STATE_NORMAL, GTK_SHADOW_OUT, area, widget, NULL, num_bytes_size + 5, 0, hexa_view_size, widget->allocation.height);	
	gtk_paint_box(widget->style, widget->window, GTK_STATE_NORMAL, GTK_SHADOW_OUT, area, widget, NULL, num_bytes_size + hexa_view_size + 10, 0, char_view_size, widget->allocation.height);	
 */
}

/**
 * Called when things needs to be redrawn
 */
static gboolean gtk_hexa_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_HEXA (widget), FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	
	if (event->count > 0)
	{
		return FALSE;
	}
	else
	{
		gtk_hexa_paint(widget, &event->area);
	
		return FALSE;
	}
}


GtkWidget *gtk_hexa_new (void)
{
	return g_object_new (GTK_TYPE_HEXA, NULL);
}
