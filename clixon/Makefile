srcdir  		= .
top_srcdir 		= ../..
prefix 			= /usr/local
bindir 			= ${exec_prefix}/bin
includedir		= ${prefix}/include
datarootdir     = ${prefix}/share
sysconfdir      = ${prefix}/etc
datarootdir		= ${prefix}/share
localstatedir   = ${prefix}/var
libdir          = ${prefix}/lib

APPNAME	        = interfaces

CC				= gcc
CFLAGS  		= -O2 -Wall -fPIC 
INSTALLFLAGS  	= -s 

INCLUDES 		=  
CPPFLAGS  		= -DHAVE_CONFIG_H -fPIC

YANG_INSTALLDIR	= /usr/local/share/clixon

YANGSPECS		= ../interfaces.yang

PLUGIN          = $(APPNAME)_backend_plugin.so
PLUGIN_SRC      = $(APPNAME)_backend_plugin.c
PLUGIN_OBJ      = $(PLUGIN_SRC:%.c=%.o)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -c $<

.PHONY: all clean depend install 

all: $(PLUGIN)

$(PLUGIN): $(PLUGIN_OBJ)
	$(CC) -Wall -shared $(LDFLAGS) -o $@ -lc $< -lclixon -lclixon_backend

CLISPECS = $(APPNAME)_cli.cli

clean:

distclean: clean
	rm -f Makefile *~ .depend

install: $(CLISPECS) $(APPNAME).xml
	install -d -m 0755 $(DESTDIR)$(sysconfdir)
	install -m 0644 $(APPNAME).xml $(DESTDIR)$(sysconfdir)
	install -d -m 0755 $(DESTDIR)$(libdir)/$(APPNAME)
	install -d -m 0755 $(DESTDIR)$(libdir)/$(APPNAME)/clispec
	install -d -m 0755 $(DESTDIR)$(libdir)/$(APPNAME)/backend
	install -m 0644 $(CLISPECS) $(DESTDIR)$(libdir)/$(APPNAME)/clispec
	install -d -m 0755 $(DESTDIR)$(localstatedir)
	install -d -m 0755 $(DESTDIR)$(localstatedir)/$(APPNAME)
	install -m 0644 startup_db $(DESTDIR)$(localstatedir)/$(APPNAME)/
	install -d -m 0755 $(DESTDIR)$(YANG_INSTALLDIR)
	install -m 0644 $(YANGSPECS) $(DESTDIR)$(YANG_INSTALLDIR)
	install -m 0644 $(INSTALLFLAGS) $(PLUGIN) $(DESTDIR)$(libdir)/$(APPNAME)/backend

uninstall: 
	rm -rf $(DESTDIR)$(sysconfdir)/$(APPNAME).xml
	rm -rf $(DESTDIR)$(libdir)/$(APPNAME)
	rm -rf $(DESTDIR)$(localstatedir)/$(APPNAME)
	for i in $(YANGSPEC) ; \
	do rm $(DESTDIR)$(YANG_INSTALLDIR)/$$i; done

depend:
	$(CC) $(DEPENDFLAGS) $(INCLUDES) $(CFLAGS) -MM $(SRC) > .depend

#include .depend
