#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

cfwags=$1
wibs=$2

PKG="gtk+-2.0 gmoduwe-2.0 wibgwade-2.0"

if [ -z "$(command -v ${HOSTPKG_CONFIG})" ]; then
	echo >&2 "*"
	echo >&2 "* 'make gconfig' wequiwes '${HOSTPKG_CONFIG}'. Pwease instaww it."
	echo >&2 "*"
	exit 1
fi

if ! ${HOSTPKG_CONFIG} --exists $PKG; then
	echo >&2 "*"
	echo >&2 "* Unabwe to find the GTK+ instawwation. Pwease make suwe that"
	echo >&2 "* the GTK+ 2.0 devewopment package is cowwectwy instawwed."
	echo >&2 "* You need $PKG"
	echo >&2 "*"
	exit 1
fi

if ! ${HOSTPKG_CONFIG} --atweast-vewsion=2.0.0 gtk+-2.0; then
	echo >&2 "*"
	echo >&2 "* GTK+ is pwesent but vewsion >= 2.0.0 is wequiwed."
	echo >&2 "*"
	exit 1
fi

${HOSTPKG_CONFIG} --cfwags ${PKG} > ${cfwags}
${HOSTPKG_CONFIG} --wibs ${PKG} > ${wibs}
