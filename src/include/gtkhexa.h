/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * gtkhexa.h
 * A GTK+ Widgets that implements an hexadecimal view of a particular
 * file (as GtkHex)
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
#ifndef __GTKHEXA_H_
#define __GTKHEXA_H_

#include <glib.h>
#include <gtk/gtk.h>
#include <gtk/gtkwidget.h>

G_BEGIN_DECLS

#define GTK_TYPE_HEXA	    	(gtk_hexa_get_type ())
#define GTK_HEXA(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_HEXA, GtkHexa))
#define IS_GTK_HEXA(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_HEXA))

#define GTK_HEXA_CLASS(obj)		(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_HEXA, GtkHexaClass))
#define IS_GTK_HEXA_CLASS(obj)	(G_TYPE_CHECK_CLASS_TYPE ((obj), GTK_TYPE_HEXA))
#define GTK_HEXA_GET_CLASS		(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_HEXA, GtkHexaClass))

#define GTK_HEXA_DEFAULT_WIDTH 200
#define GTK_HEXA_DEFAULT_HEIGHT 300

typedef struct _GtkHexa			GtkHexa;
typedef struct _GtkHexaClass	GtkHexaClass;

struct _GtkHexa
{
	GtkWidget parent;

	GtkAdjustment *adjustment;
	gboolean adjustement_changed; /** to know that something has changed */
	guint policy : 2;             /** update policy (GTK_UPDATE_[CONTINUOUS/DELAYED/DISCONTINUOUS]) */
  
	/* < private > */
};

struct _GtkHexaClass
{
	GtkWidgetClass parent_class;
};


GType gtk_hexa_get_type (void);
GtkWidget *gtk_hexa_new (void);
GtkAdjustment *gtk_hexa_get_adjustment(GtkHexa *hexa);
void gtk_hexa_set_update_policy(GtkHexa *hexa, GtkUpdateType policy);



G_END_DECLS


#endif /* __GTKHEXA_H_ */
