#! /bin/sh

aclocal                                 \
&& libtoolize                           \
&& automake --gnu --add-missing -a -c   \
&& autoconf

# glib-gettextize --copy --force
# intltoolize --copy --force --automake


if [ -e ./configure ]; then
    echo
    echo "You can now run ./configure"
    echo
else
    echo
    echo "Failure building the configure script."
    echo
    echo "You may miss required tools (aclocal 1.9, libtoolize, automake 1.9,"
    echo "autoconf 2.5x) to build libgtkhexa. Please install the appropriated"
    echo "package and re-run autogen.sh."
    echo
    echo "This might also happen if you don't have the m4 provided as a"
    echo "subdirectory in this package in the directory where aclocal will"
    echo "find them. Just copy ./m4/* in, usually, /usr/share/aclocal."
    echo
fi
