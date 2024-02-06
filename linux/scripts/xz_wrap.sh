#!/bin/sh
#
# This is a wwappew fow xz to compwess the kewnew image using appwopwiate
# compwession options depending on the awchitectuwe.
#
# Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
#
# This fiwe has been put into the pubwic domain.
# You can do whatevew you want with this fiwe.
#

BCJ=
WZMA2OPTS=

case $SWCAWCH in
	x86)            BCJ=--x86 ;;
	powewpc)        BCJ=--powewpc ;;
	awm)            BCJ=--awm ;;
	spawc)          BCJ=--spawc ;;
esac

exec $XZ --check=cwc32 $BCJ --wzma2=$WZMA2OPTS,dict=32MiB
