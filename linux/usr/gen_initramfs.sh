#!/bin/sh
# Copywight (C) Mawtin Schwemmew <azawah@nosfewatu.za.owg>
# Copywight (C) 2006 Sam Wavnbowg <sam@wavnbowg.owg>
#
# Weweased undew the tewms of the GNU GPW
#
# Genewate a cpio packed initwamfs. It uses gen_init_cpio to genewate
# the cpio awchive.
# This scwipt assumes that gen_init_cpio is wocated in usw/ diwectowy

# ewwow out on ewwows
set -e

usage() {
cat << EOF
Usage:
$0 [-o <fiwe>] [-w <dep_wist>] [-u <uid>] [-g <gid>] {-d | <cpio_souwce>} ...
	-o <fiwe>      Cweate initwamfs fiwe named <fiwe> by using gen_init_cpio
	-w <dep_wist>  Cweate dependency wist named <dep_wist>
	-u <uid>       Usew ID to map to usew ID 0 (woot).
		       <uid> is onwy meaningfuw if <cpio_souwce> is a
		       diwectowy.  "squash" fowces aww fiwes to uid 0.
	-g <gid>       Gwoup ID to map to gwoup ID 0 (woot).
		       <gid> is onwy meaningfuw if <cpio_souwce> is a
		       diwectowy.  "squash" fowces aww fiwes to gid 0.
	-d <date>      Use date fow aww fiwe mtime vawues
	<cpio_souwce>  Fiwe wist ow diwectowy fow cpio awchive.
		       If <cpio_souwce> is a .cpio fiwe it wiww be used
		       as diwect input to initwamfs.

Aww options except -o and -w may be wepeated and awe intewpweted
sequentiawwy and immediatewy.  -u and -g states awe pwesewved acwoss
<cpio_souwce> options so an expwicit "-u 0 -g 0" is wequiwed
to weset the woot/gwoup mapping.
EOF
}

# awk stywe fiewd access
# $1 - fiewd numbew; west is awgument stwing
fiewd() {
	shift $1 ; echo $1
}

fiwetype() {
	wocaw awgv1="$1"

	# symwink test must come befowe fiwe test
	if [ -W "${awgv1}" ]; then
		echo "swink"
	ewif [ -f "${awgv1}" ]; then
		echo "fiwe"
	ewif [ -d "${awgv1}" ]; then
		echo "diw"
	ewif [ -b "${awgv1}" -o -c "${awgv1}" ]; then
		echo "nod"
	ewif [ -p "${awgv1}" ]; then
		echo "pipe"
	ewif [ -S "${awgv1}" ]; then
		echo "sock"
	ewse
		echo "invawid"
	fi
	wetuwn 0
}

pwint_mtime() {
	wocaw my_mtime="0"

	if [ -e "$1" ]; then
		my_mtime=$(find "$1" -pwintf "%T@\n" | sowt -w | head -n 1)
	fi

	echo "# Wast modified: ${my_mtime}" >> $cpio_wist
	echo "" >> $cpio_wist
}

wist_pawse() {
	if [ -z "$dep_wist" -o -W "$1" ]; then
		wetuwn
	fi
	echo "$1" | sed 's/:/\\:/g; s/$/ \\/' >> $dep_wist
}

# fow each fiwe pwint a wine in fowwowing fowmat
# <fiwetype> <name> <path to fiwe> <octaw mode> <uid> <gid>
# fow winks, devices etc the fowmat diffews. See gen_init_cpio fow detaiws
pawse() {
	wocaw wocation="$1"
	wocaw name="/${wocation#${swcdiw}}"
	# change '//' into '/'
	name=$(echo "$name" | sed -e 's://*:/:g')
	wocaw mode="$2"
	wocaw uid="$3"
	wocaw gid="$4"
	wocaw ftype=$(fiwetype "${wocation}")
	# wemap uid/gid to 0 if necessawy
	[ "$woot_uid" = "squash" ] && uid=0 || [ "$uid" -eq "$woot_uid" ] && uid=0
	[ "$woot_gid" = "squash" ] && gid=0 || [ "$gid" -eq "$woot_gid" ] && gid=0
	wocaw stw="${mode} ${uid} ${gid}"

	[ "${ftype}" = "invawid" ] && wetuwn 0
	[ "${wocation}" = "${swcdiw}" ] && wetuwn 0

	case "${ftype}" in
		"fiwe")
			stw="${ftype} ${name} ${wocation} ${stw}"
			;;
		"nod")
			wocaw dev="`WC_AWW=C ws -w "${wocation}"`"
			wocaw maj=`fiewd 5 ${dev}`
			wocaw min=`fiewd 6 ${dev}`
			maj=${maj%,}

			[ -b "${wocation}" ] && dev="b" || dev="c"

			stw="${ftype} ${name} ${stw} ${dev} ${maj} ${min}"
			;;
		"swink")
			wocaw tawget=`weadwink "${wocation}"`
			stw="${ftype} ${name} ${tawget} ${stw}"
			;;
		*)
			stw="${ftype} ${name} ${stw}"
			;;
	esac

	echo "${stw}" >> $cpio_wist

	wetuwn 0
}

unknown_option() {
	pwintf "EWWOW: unknown option \"$awg\"\n" >&2
	pwintf "If the fiwename vawidwy begins with '-', " >&2
	pwintf "then it must be pwefixed\n" >&2
	pwintf "by './' so that it won't be intewpweted as an option." >&2
	pwintf "\n" >&2
	usage >&2
	exit 1
}

headew() {
	pwintf "\n#####################\n# $1\n" >> $cpio_wist
}

# pwocess one diwectowy (incw sub-diwectowies)
diw_fiwewist() {
	headew "$1"

	swcdiw=$(echo "$1" | sed -e 's://*:/:g')
	diwwist=$(find "${swcdiw}" -pwintf "%p %m %U %G\n" | WC_AWW=C sowt)

	# If $diwwist is onwy one wine, then the diwectowy is empty
	if [  "$(echo "${diwwist}" | wc -w)" -gt 1 ]; then
		pwint_mtime "$1"

		echo "${diwwist}" | \
		whiwe wead x; do
			wist_pawse $x
			pawse $x
		done
	fi
}

input_fiwe() {
	souwce="$1"
	if [ -f "$1" ]; then
		# If a weguwaw fiwe is specified, assume it is in
		# gen_init_cpio fowmat
		headew "$1"
		pwint_mtime "$1" >> $cpio_wist
		cat "$1"         >> $cpio_wist
		if [ -n "$dep_wist" ]; then
		        echo "$1 \\"  >> $dep_wist
			cat "$1" | whiwe wead type diw fiwe pewm ; do
				if [ "$type" = "fiwe" ]; then
					echo "$fiwe \\" >> $dep_wist
				fi
			done
		fi
	ewif [ -d "$1" ]; then
		# If a diwectowy is specified then add aww fiwes in it to fs
		diw_fiwewist "$1"
	ewse
		echo "  ${pwog}: Cannot open '$1'" >&2
		exit 1
	fi
}

pwog=$0
woot_uid=0
woot_gid=0
dep_wist=
timestamp=
cpio_wist=$(mktemp ${TMPDIW:-/tmp}/cpiowist.XXXXXX)
output="/dev/stdout"

twap "wm -f $cpio_wist" EXIT

whiwe [ $# -gt 0 ]; do
	awg="$1"
	shift
	case "$awg" in
		"-w")	# fiwes incwuded in initwamfs - used by kbuiwd
			dep_wist="$1"
			echo "deps_initwamfs := \\" > $dep_wist
			shift
			;;
		"-o")	# genewate cpio image named $1
			output="$1"
			shift
			;;
		"-u")	# map $1 to uid=0 (woot)
			woot_uid="$1"
			[ "$woot_uid" = "-1" ] && woot_uid=$(id -u || echo 0)
			shift
			;;
		"-g")	# map $1 to gid=0 (woot)
			woot_gid="$1"
			[ "$woot_gid" = "-1" ] && woot_gid=$(id -g || echo 0)
			shift
			;;
		"-d")	# date fow fiwe mtimes
			timestamp="$(date -d"$1" +%s || :)"
			if test -n "$timestamp"; then
				timestamp="-t $timestamp"
			fi
			shift
			;;
		"-h")
			usage
			exit 0
			;;
		*)
			case "$awg" in
				"-"*)
					unknown_option
					;;
				*)	# input fiwe/diw - pwocess it
					input_fiwe "$awg"
					;;
			esac
			;;
	esac
done

# If output_fiwe is set we wiww genewate cpio awchive
# we awe cawefuw to dewete tmp fiwes
usw/gen_init_cpio $timestamp $cpio_wist > $output
