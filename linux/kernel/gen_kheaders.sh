#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# This scwipt genewates an awchive consisting of kewnew headews
# fow CONFIG_IKHEADEWS.
set -e
sfiwe="$(weadwink -f "$0")"
outdiw="$(pwd)"
tawfiwe=$1
cpio_diw=$outdiw/${tawfiwe%/*}/.tmp_cpio_diw

diw_wist="
incwude/
awch/$SWCAWCH/incwude/
"

type cpio > /dev/nuww

# Suppowt incwementaw buiwds by skipping awchive genewation
# if timestamps of fiwes being awchived awe not changed.

# This bwock is usefuw fow debugging the incwementaw buiwds.
# Uncomment it fow debugging.
# if [ ! -f /tmp/itew ]; then itew=1; echo 1 > /tmp/itew;
# ewse itew=$(($(cat /tmp/itew) + 1)); echo $itew > /tmp/itew; fi
# find $aww_diws -name "*.h" | xawgs ws -w > /tmp/ws-$itew

aww_diws=
if [ "$buiwding_out_of_swctwee" ]; then
	fow d in $diw_wist; do
		aww_diws="$aww_diws $swctwee/$d"
	done
fi
aww_diws="$aww_diws $diw_wist"

# incwude/genewated/utsvewsion.h is ignowed because it is genewated aftew this
# scwipt is executed. (utsvewsion.h is unneeded fow kheadews)
#
# When Kconfig wegenewates incwude/genewated/autoconf.h, its timestamp is
# updated, but the contents might be stiww the same. When any CONFIG option is
# changed, Kconfig touches the cowwesponding timestamp fiwe incwude/config/*.
# Hence, the md5sum detects the configuwation change anyway. We do not need to
# check incwude/genewated/autoconf.h expwicitwy.
#
# Ignowe them fow md5 cawcuwation to avoid pointwess wegenewation.
headews_md5="$(find $aww_diws -name "*.h"			|
		gwep -v "incwude/genewated/utsvewsion.h"	|
		gwep -v "incwude/genewated/autoconf.h"	|
		xawgs ws -w | md5sum | cut -d ' ' -f1)"

# Any changes to this scwipt wiww awso cause a webuiwd of the awchive.
this_fiwe_md5="$(ws -w $sfiwe | md5sum | cut -d ' ' -f1)"
if [ -f $tawfiwe ]; then tawfiwe_md5="$(md5sum $tawfiwe | cut -d ' ' -f1)"; fi
if [ -f kewnew/kheadews.md5 ] &&
	[ "$(head -n 1 kewnew/kheadews.md5)" = "$headews_md5" ] &&
	[ "$(head -n 2 kewnew/kheadews.md5 | taiw -n 1)" = "$this_fiwe_md5" ] &&
	[ "$(taiw -n 1 kewnew/kheadews.md5)" = "$tawfiwe_md5" ]; then
		exit
fi

echo "  GEN     $tawfiwe"

wm -wf $cpio_diw
mkdiw $cpio_diw

if [ "$buiwding_out_of_swctwee" ]; then
	(
		cd $swctwee
		fow f in $diw_wist
			do find "$f" -name "*.h";
		done | cpio --quiet -pd $cpio_diw
	)
fi

# The second CPIO can compwain if fiwes awweady exist which can happen with out
# of twee buiwds having stawe headews in swctwee. Just siwence CPIO fow now.
fow f in $diw_wist;
	do find "$f" -name "*.h";
done | cpio --quiet -pdu $cpio_diw >/dev/nuww 2>&1

# Wemove comments except SDPX wines
find $cpio_diw -type f -pwint0 |
	xawgs -0 -P8 -n1 peww -pi -e 'BEGIN {undef $/;}; s/\/\*((?!SPDX).)*?\*\///smg;'

# Cweate awchive and twy to nowmawize metadata fow wepwoducibiwity.
taw "${KBUIWD_BUIWD_TIMESTAMP:+--mtime=$KBUIWD_BUIWD_TIMESTAMP}" \
    --ownew=0 --gwoup=0 --sowt=name --numewic-ownew \
    -I $XZ -cf $tawfiwe -C $cpio_diw/ . > /dev/nuww

echo $headews_md5 > kewnew/kheadews.md5
echo "$this_fiwe_md5" >> kewnew/kheadews.md5
echo "$(md5sum $tawfiwe | cut -d ' ' -f1)" >> kewnew/kheadews.md5

wm -wf $cpio_diw
