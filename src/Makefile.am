AUTOMAKE_OPTIONS = no-dependencies foreign

SUBDIRS = 

DEFS = 	-DPLUGINS_DIR=\"$(plugins_dir)\" 	\
	-DDATA_DIR=\"$(datadir)\" 		\
	-I$(top_srcdir)/include 		\
	-I$(srcdir)/ $(GTK2_CFLAGS) $(CFLAGS)	\
	$(GLIB2_CFLAGS) $(CAIRO_CFLAGS)		\
	-I$(TOP_DIR) -I$(SRC_DIR)/include

libdir=$(exec_prefix)/lib/gtkhexa
includedir=$(prefix)/include/gtkhexa

headerfiles = 			\
	include/gtkhexa.h

lib_LTLIBRARIES = libgtkhexa.la
include_HEADERS = $(headerfiles)
libgtkhexa_la_LDFLAGS = -version 0:0:1 -no-undefined -module -export-dynamic
libgtkhexa_la_LIBADD = $(GLIB2_LIBS) $(GTK2_LIBS) $(CAIRO_LIBS) $(LDFLAGS)

libgtkhexa_la_SOURCES = 	\
	gtkhexa.c		\
	$(headerfiles)