/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * gtkhexa.h
 * A GTK+ Widgets that implements an hexadecimal view of a particular
 * file (as GtkHex)
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
#ifndef _GTKHEXA_H_
#define _GTKHEXA_H_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTK_TYPE_HEXA	        (gtk_hexa_get_type ())
#define GTK_HEXA(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_HEXA, GtkHexa))
#define GTK_HEXA_CLASS(obj)	(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_HEXA, GtkHexaClass))
#define IS_GTK_HEXA(obj)	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_HEXA))
#define IS_GTK_HEXA_CLASS(obj)	(G_TYPE_CHECK_CLASS_TYPE ((obj), GTK_TYPE_HEXA))
#define GTK_HEXA_GET_CLASS	(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_HEXA, GtkHexaClass))

typedef struct _GtkHexa		GtkHexa;
typedef struct _GtkHexaClass	GtkHexaClass;

struct _GtkHexa
{
	GtkDrawingArea parent;

	/* < private > */
};

struct _GtkHexaClass
{
	GtkDrawingAreaClass parent_class;
};

GtkWidget *gtk_hexa_new (void);

G_END_DECLS


#endif /* _GTKHEXA_H_ */
