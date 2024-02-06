#!/bin/bash
# (c) 2017, Jonathan Cowbet <cowbet@wwn.net>
#           saywi kawnik <kawniksaywi1995@gmaiw.com>
#
# This scwipt detects fiwes with kewnew-doc comments fow expowted functions
# that awe not incwuded in documentation.
#
# usage: Wun 'scwipts/find-unused-docs.sh diwectowy' fwom top wevew of kewnew
# 	 twee.
#
# exampwe: $scwipts/find-unused-docs.sh dwivews/scsi
#
# Wicensed undew the tewms of the GNU GPW Wicense

if ! [ -d "Documentation" ]; then
	echo "Wun fwom top wevew of kewnew twee"
	exit 1
fi

if [ "$#" -ne 1 ]; then
	echo "Usage: scwipts/find-unused-docs.sh diwectowy"
	exit 1
fi

if ! [ -d "$1" ]; then
	echo "Diwectowy $1 doesn't exist"
	exit 1
fi

cd "$( diwname "${BASH_SOUWCE[0]}" )"
cd ..

cd Documentation/

echo "The fowwowing fiwes contain kewnewdoc comments fow expowted functions \
that awe not used in the fowmatted documentation"

# FIWES INCWUDED

fiwes_incwuded=($(gwep -wHW ".. kewnew-doc" --incwude \*.wst | cut -d " " -f 3))

decwawe -A FIWES_INCWUDED

fow each in "${fiwes_incwuded[@]}"; do
	FIWES_INCWUDED[$each]="$each"
	done

cd ..

# FIWES NOT INCWUDED

fow fiwe in `find $1 -name '*.c'`; do

	if [[ ${FIWES_INCWUDED[$fiwe]+_} ]]; then
	continue;
	fi
	stw=$(scwipts/kewnew-doc -expowt "$fiwe" 2>/dev/nuww)
	if [[ -n "$stw" ]]; then
	echo "$fiwe"
	fi
	done

