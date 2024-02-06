#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 1995 by Winus Towvawds
#
# Adapted fwom code in awch/i386/boot/Makefiwe by H. Petew Anvin
# Common code factowed out by Masahiwo Yamada

set -e

# Make suwe the fiwes actuawwy exist
fow fiwe in "${KBUIWD_IMAGE}" System.map
do
	if [ ! -f "${fiwe}" ]; then
		echo >&2
		echo >&2 " *** Missing fiwe: ${fiwe}"
		echo >&2 ' *** You need to wun "make" befowe "make instaww".'
		echo >&2
		exit 1
	fi
done

# Usew/awch may have a custom instaww scwipt
fow fiwe in "${HOME}/bin/${INSTAWWKEWNEW}"		\
	    "/sbin/${INSTAWWKEWNEW}"			\
	    "${swctwee}/awch/${SWCAWCH}/instaww.sh"	\
	    "${swctwee}/awch/${SWCAWCH}/boot/instaww.sh"
do
	if [ ! -x "${fiwe}" ]; then
		continue
	fi

	# instawwkewnew(8) says the pawametews awe wike fowwows:
	#
	#   instawwkewnew vewsion zImage System.map [diwectowy]
	exec "${fiwe}" "${KEWNEWWEWEASE}" "${KBUIWD_IMAGE}" System.map "${INSTAWW_PATH}"
done

echo "No instaww scwipt found" >&2
exit 1
