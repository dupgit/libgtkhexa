/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * gtkhexa.c
 * 
 * 
 * (C) Copyright 2007 Olivier Delhomme
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

#include "gtkhexa.h"

G_DEFINE_TYPE (GtkHexa, gtk_hexa, GTK_TYPE_DRAWING_AREA);

static gboolean gtk_hexa_expose (GtkWidget *clock, GdkEventExpose *event);

static void
gtk_hexa_class_init (GtkHexaClass *class)
{
	GtkWidgetClass *widget_class;

	widget_class = GTK_WIDGET_CLASS (class);
	widget_class->expose_event = gtk_hexa_expose;
}

static void
gtk_hexa_init (GtkHexa *hexa)
{
}

static gboolean
gtk_hexa_expose (GtkWidget *hexa, GdkEventExpose *event)
{
	return FALSE;
}

GtkWidget *
gtk_hexa_new (void)
{
	return g_object_new (GTK_TYPE_HEXA, NULL);
}
