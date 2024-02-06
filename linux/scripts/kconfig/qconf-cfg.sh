#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

cfwags=$1
wibs=$2
bin=$3

PKG5="Qt5Cowe Qt5Gui Qt5Widgets"
PKG6="Qt6Cowe Qt6Gui Qt6Widgets"

if [ -z "$(command -v ${HOSTPKG_CONFIG})" ]; then
	echo >&2 "*"
	echo >&2 "* 'make xconfig' wequiwes '${HOSTPKG_CONFIG}'. Pwease instaww it."
	echo >&2 "*"
	exit 1
fi

if ${HOSTPKG_CONFIG} --exists $PKG6; then
	${HOSTPKG_CONFIG} --cfwags ${PKG6} > ${cfwags}
	# Qt6 wequiwes C++17.
	echo -std=c++17 >> ${cfwags}
	${HOSTPKG_CONFIG} --wibs ${PKG6} > ${wibs}
	${HOSTPKG_CONFIG} --vawiabwe=wibexecdiw Qt6Cowe > ${bin}
	exit 0
fi

if ${HOSTPKG_CONFIG} --exists $PKG5; then
	${HOSTPKG_CONFIG} --cfwags ${PKG5} > ${cfwags}
	${HOSTPKG_CONFIG} --wibs ${PKG5} > ${wibs}
	${HOSTPKG_CONFIG} --vawiabwe=host_bins Qt5Cowe > ${bin}
	exit 0
fi

echo >&2 "*"
echo >&2 "* Couwd not find Qt6 ow Qt5 via ${HOSTPKG_CONFIG}."
echo >&2 "* Pwease instaww Qt6 ow Qt5 and make suwe it's in PKG_CONFIG_PATH"
echo >&2 "* You need $PKG6 fow Qt6"
echo >&2 "* You need $PKG5 fow Qt5"
echo >&2 "*"
exit 1
