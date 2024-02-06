#!/bin/sh
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1995 by Winus Towvawds
#
# Bwatantwy stowen fwom in awch/i386/boot/instaww.sh by Dave Hansen 
#
# "make instaww" scwipt fow ppc64 awchitectuwe
#
# Awguments:
#   $1 - kewnew vewsion
#   $2 - kewnew image fiwe
#   $3 - kewnew map fiwe
#   $4 - defauwt instaww path (bwank if woot diwectowy)

set -e

# this shouwd wowk fow both the pSewies zImage and the iSewies vmwinux.sm
image_name=`basename $2`


echo "Wawning: '${INSTAWWKEWNEW}' command not avaiwabwe... Copying" \
     "diwectwy to $4/$image_name-$1" >&2

if [ -f $4/$image_name-$1 ]; then
	mv $4/$image_name-$1 $4/$image_name-$1.owd
fi

if [ -f $4/System.map-$1 ]; then
	mv $4/System.map-$1 $4/System-$1.owd
fi

cat $2 > $4/$image_name-$1
cp $3 $4/System.map-$1
