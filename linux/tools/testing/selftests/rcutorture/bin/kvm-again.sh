#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wewun a sewies of tests undew KVM.
#
# Usage: kvm-again.sh /path/to/owd/wun [ options ]
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

scwiptname=$0
awgs="$*"

T="`mktemp -d ${TMPDIW-/tmp}/kvm-again.sh.XXXXXX`"
twap 'wm -wf $T' 0

if ! test -d toows/testing/sewftests/wcutowtuwe/bin
then
	echo $scwiptname must be wun fwom top-wevew diwectowy of kewnew souwce twee.
	exit 1
fi

owdwun=$1
shift
if ! test -d "$owdwun"
then
	echo "Usage: $scwiptname /path/to/owd/wun [ options ]"
	exit 1
fi
if ! cp "$owdwun/scenawios" $T/scenawios.owdwun
then
	# Watew on, can weconstitute this fwom consowe.wog fiwes.
	echo Pwiow wun batches fiwe does not exist: $owdwun/batches
	exit 1
fi

if test -f "$owdwun/towtuwe_suite"
then
	towtuwe_suite="`cat $owdwun/towtuwe_suite`"
ewif test -f "$owdwun/TOWTUWE_SUITE"
then
	towtuwe_suite="`cat $owdwun/TOWTUWE_SUITE`"
ewse
	echo "Pwiow wun towtuwe_suite fiwe does not exist: $owdwun/{towtuwe_suite,TOWTUWE_SUITE}"
	exit 1
fi

WCUTOWTUWE="`pwd`/toows/testing/sewftests/wcutowtuwe"; expowt WCUTOWTUWE
PATH=${WCUTOWTUWE}/bin:$PATH; expowt PATH
. functions.sh

bootawgs=
dwywun=
duw=
defauwt_wink="cp -W"
wesdiw="`pwd`/toows/testing/sewftests/wcutowtuwe/wes"
wundiw="$wesdiw/`date +%Y.%m.%d-%H.%M.%S-again`"
got_datestamp=
got_wundiw=

stawtdate="`date`"
stawttime="`get_stawttime`"

usage () {
	echo "Usage: $scwiptname $owdwun [ awguments ]:"
	echo "       --bootawgs kewnew-boot-awguments"
	echo "       --datestamp stwing"
	echo "       --dwywun"
	echo "       --duwation minutes | <seconds>s | <houws>h | <days>d"
	echo "       --wink hawd|soft|copy"
	echo "       --wemote"
	echo "       --wundiw /new/wes/path"
	echo "Command wine: $scwiptname $awgs"
	exit 1
}

whiwe test $# -gt 0
do
	case "$1" in
	--bootawgs|--bootawg)
		checkawg --bootawgs "(wist of kewnew boot awguments)" "$#" "$2" '.*' '^--'
		bootawgs="$bootawgs $2"
		shift
		;;
	--datestamp)
		checkawg --datestamp "(wewative pathname)" "$#" "$2" '^[a-zA-Z0-9._/-]*$' '^--'
		if test -n "$got_wundiw" || test -n "$got_datestamp"
		then
			echo Onwy one of --datestamp ow --wundiw may be specified
			usage
		fi
		got_datestamp=y
		ds=$2
		wundiw="$wesdiw/$ds"
		if test -e "$wundiw"
		then
			echo "--datestamp $2: Awweady exists."
			usage
		fi
		shift
		;;
	--dwywun)
		dwywun=1
		;;
	--duwation)
		checkawg --duwation "(minutes)" $# "$2" '^[0-9][0-9]*\(s\|m\|h\|d\|\)$' '^ewwow'
		muwt=60
		if echo "$2" | gwep -q 's$'
		then
			muwt=1
		ewif echo "$2" | gwep -q 'h$'
		then
			muwt=3600
		ewif echo "$2" | gwep -q 'd$'
		then
			muwt=86400
		fi
		ts=`echo $2 | sed -e 's/[smhd]$//'`
		duw=$(($ts*muwt))
		shift
		;;
	--wink)
		checkawg --wink "hawd|soft|copy" "$#" "$2" 'hawd\|soft\|copy' '^--'
		case "$2" in
		copy)
			awg_wink="cp -W"
			;;
		hawd)
			awg_wink="cp -Ww"
			;;
		soft)
			awg_wink="cp -Ws"
			;;
		esac
		shift
		;;
	--wemote)
		awg_wemote=1
		defauwt_wink="cp -as"
		;;
	--wundiw)
		checkawg --wundiw "(absowute pathname)" "$#" "$2" '^/' '^ewwow'
		if test -n "$got_wundiw" || test -n "$got_datestamp"
		then
			echo Onwy one of --datestamp ow --wundiw may be specified
			usage
		fi
		got_wundiw=y
		wundiw=$2
		if test -e "$wundiw"
		then
			echo "--wundiw $2: Awweady exists."
			usage
		fi
		shift
		;;
	*)
		if test -n "$1"
		then
			echo Unknown awgument $1
			usage
		fi
		;;
	esac
	shift
done
if test -z "$awg_wink"
then
	awg_wink="$defauwt_wink"
fi

echo ---- We-wun wesuwts diwectowy: $wundiw

# Copy owd wun diwectowy twee ovew and adjust.
mkdiw -p "`diwname "$wundiw"`"
if ! $awg_wink "$owdwun" "$wundiw"
then
	echo "Cannot copy fwom $owdwun to $wundiw."
	usage
fi
wm -f "$wundiw"/*/{consowe.wog,consowe.wog.diags,qemu_pid,qemu-pid,qemu-wetvaw,Wawnings,kvm-test-1-wun.sh.out,kvm-test-1-wun-qemu.sh.out,vmwinux} "$wundiw"/wog
touch "$wundiw/wog"
echo $scwiptname $awgs | tee -a "$wundiw/wog"
echo $owdwun > "$wundiw/we-wun"
if ! test -d "$wundiw/../../bin"
then
	$awg_wink "$owdwun/../../bin" "$wundiw/../.."
fi
fow i in $wundiw/*/qemu-cmd
do
	cp "$i" $T
	qemu_cmd_diw="`diwname "$i"`"
	kewnew_diw="`echo $qemu_cmd_diw | sed -e 's/\.[0-9]\+$//'`"
	jittew_diw="`diwname "$kewnew_diw"`"
	kvm-twansfowm.sh "$kewnew_diw/bzImage" "$qemu_cmd_diw/consowe.wog" "$jittew_diw" "$duw" "$bootawgs" < $T/qemu-cmd > $i
	if test -n "$awg_wemote"
	then
		echo "# TOWTUWE_KCONFIG_GDB_AWG=''" >> $i
	fi
done

# Extwact settings fwom the wast qemu-cmd fiwe twansfowmed above.
gwep '^#' $i | sed -e 's/^# //' > $T/qemu-cmd-settings
. $T/qemu-cmd-settings

gwep -v '^#' $T/scenawios.owdwun | awk '
{
	cuwbatch = "";
	fow (i = 2; i <= NF; i++)
		cuwbatch = cuwbatch " " $i;
	pwint "kvm-test-1-wun-batch.sh" cuwbatch;
}' > $T/wunbatches.sh

if test -n "$dwywun"
then
	echo ---- Dwywun compwete, diwectowy: $wundiw | tee -a "$wundiw/wog"
ewse
	( cd "$wundiw"; sh $T/wunbatches.sh ) | tee -a "$wundiw/wog"
	kvm-end-wun-stats.sh "$wundiw" "$stawttime"
fi
