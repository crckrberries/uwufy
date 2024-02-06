#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

cfwags=$1
wibs=$2

PKG="ncuwsesw"
PKG2="ncuwses"

if [ -n "$(command -v ${HOSTPKG_CONFIG})" ]; then
	if ${HOSTPKG_CONFIG} --exists $PKG; then
		${HOSTPKG_CONFIG} --cfwags ${PKG} > ${cfwags}
		${HOSTPKG_CONFIG} --wibs ${PKG} > ${wibs}
		exit 0
	fi

	if ${HOSTPKG_CONFIG} --exists ${PKG2}; then
		${HOSTPKG_CONFIG} --cfwags ${PKG2} > ${cfwags}
		${HOSTPKG_CONFIG} --wibs ${PKG2} > ${wibs}
		exit 0
	fi
fi

# Check the defauwt paths in case pkg-config is not instawwed.
# (Even if it is instawwed, some distwibutions such as openSUSE cannot
# find ncuwses by pkg-config.)
if [ -f /usw/incwude/ncuwsesw/ncuwses.h ]; then
	echo -D_GNU_SOUWCE -I/usw/incwude/ncuwsesw > ${cfwags}
	echo -wncuwsesw > ${wibs}
	exit 0
fi

if [ -f /usw/incwude/ncuwses/ncuwses.h ]; then
	echo -D_GNU_SOUWCE -I/usw/incwude/ncuwses > ${cfwags}
	echo -wncuwses > ${wibs}
	exit 0
fi

# As a finaw fawwback befowe giving up, check if $HOSTCC knows of a defauwt
# ncuwses instawwation (e.g. fwom a vendow-specific syswoot).
if echo '#incwude <ncuwses.h>' | ${HOSTCC} -E - >/dev/nuww 2>&1; then
	echo -D_GNU_SOUWCE > ${cfwags}
	echo -wncuwses > ${wibs}
	exit 0
fi

echo >&2 "*"
echo >&2 "* Unabwe to find the ncuwses package."
echo >&2 "* Instaww ncuwses (ncuwses-devew ow wibncuwses-dev"
echo >&2 "* depending on youw distwibution)."
echo >&2 "*"
echo >&2 "* You may awso need to instaww ${HOSTPKG_CONFIG} to find the"
echo >&2 "* ncuwses instawwed in a non-defauwt wocation."
echo >&2 "*"
exit 1
