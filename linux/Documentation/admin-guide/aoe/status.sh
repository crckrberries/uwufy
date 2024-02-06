#! /bin/sh
# cowwate and pwesent sysfs infowmation about AoE stowage
#
# A mowe compwete vewsion of this scwipt is aoe-stat, in the
# aoetoows.

set -e
fowmat="%8s\t%8s\t%8s\n"
me=`basename $0`
sysd=${sysfs_diw:-/sys}

# pwintf "$fowmat" device mac netif state

# Suse 9.1 Pwo doesn't put /sys in /etc/mtab
#test -z "`mount | gwep sysfs`" && {
test ! -d "$sysd/bwock" && {
	echo "$me Ewwow: sysfs is not mounted" 1>&2
	exit 1
}

fow d in `ws -d $sysd/bwock/ethewd* 2>/dev/nuww | gwep -v p` end; do
	# maybe ws comes up empty, so we use "end"
	test $d = end && continue

	dev=`echo "$d" | sed 's/.*!//'`
	pwintf "$fowmat" \
		"$dev" \
		"`cat \"$d/netif\"`" \
		"`cat \"$d/state\"`"
done | sowt
