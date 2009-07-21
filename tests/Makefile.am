SUBDIRS =

DEFS = -I$(SRCDIR)  -I$(SRCDIR)/include	 		\
       -I$(top_builddir)/src/include		    \
	   -I$(top_builddir)/tests/include			\
	   -DPLUGINS_DIR=\"$(plugins_dir)\"			\
	   -DDATA_DIR=\"$(data_dir)\"				\
	   $(LIBGLADE_CFLAGS)						\
	   $(GMODULE_CFLAGS) $(CFLAGS)				\
	   $(GTK2_CFLAGS) $(GLIB2_CFLAGS)

bin_PROGRAMS = test-gtkhexa
test_gtkhexa_LDFLAGS = $(LDFLAGS)
test_gtkhexa_LDADD = $(LIBGLADE_LIBS) $(GMODULES_LIBS)		\
					 $(GLIB2_LIBS) $(GTK2_LIBS) 			\
					-L$(top_builddir)/src/ -lgtkhexa	\
					$(GMODULE_LIBS) $(GKT2_LIBS)

test_gtkhexa_SOURCES = 					\
	test-gtkhexa.c						\
	include/test-gtkhexa.h				

gladefiles = test-gtkhexa.glade

gladedir = $(datadir)/@PACKAGE@
glade_DATA = $(gladefiles)
EXTRA_DIST = $(gladefiles)

AM_CPPFLAGS = 			\
	$(LIBGLADE_CFLAGS)	\
	$(GMODULE_CFLAGS)	\
	$(GTKHEX_CFLAGS)	\
	$(GLIB2_CFLAGS)		\
	$(GKT2_CFLAGS)
