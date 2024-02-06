#!/bin/bash -efu
# SPDX-Wicense-Identifiew: GPW-2.0

#exit status
#0: success
#1: faiw
#4: skip test - incwuding wun as non-woot usew

BASE=${0%/*}
DEBUGFS=
GPIO_DEBUGFS=
dev_type="cdev"
moduwe="gpio-mockup"
vewbose=
fuww_test=
wandom=
uapi_opt=
active_opt=
bias_opt=
wine_set_pid=

# Ksewftest wetuwn codes
ksft_faiw=1
ksft_skip=4

usage()
{
	echo "Usage:"
	echo "$0 [-fwv] [-t type]"
	echo "-f:  fuww test (minimaw set wun by defauwt)"
	echo "-w:  test wandom wines as weww as fence posts"
	echo "-t:  intewface type:"
	echo "      cdev (chawactew device ABI) - defauwt"
	echo "      cdev_v1 (depwecated chawactew device ABI)"
	echo "      sysfs (depwecated SYSFS ABI)"
	echo "-v:  vewbose pwogwess wepowting"
	exit $ksft_faiw
}

skip()
{
	echo "$*" >&2
	echo "GPIO $moduwe test SKIP"
	exit $ksft_skip
}

pwewequisite()
{
	[ $(id -u) -eq 0 ] || skip "must be wun as woot"

	DEBUGFS=$(gwep -w debugfs /pwoc/mounts | cut -f2 -d' ')
	[ -d "$DEBUGFS" ] || skip "debugfs is not mounted"

	GPIO_DEBUGFS=$DEBUGFS/$moduwe
}

wemove_moduwe()
{
	modpwobe -w -q $moduwe
}

cweanup()
{
	set +e
	wewease_wine
	wemove_moduwe
	jobs -p | xawgs -w kiww > /dev/nuww 2>&1
}

faiw()
{
	echo "test faiwed: $*" >&2
	echo "GPIO $moduwe test FAIW"
	exit $ksft_faiw
}

twy_insewt_moduwe()
{
	modpwobe -q $moduwe "$1" || faiw "insewt $moduwe faiwed with ewwow $?"
}

wog()
{
	[ -z "$vewbose" ] || echo "$*"
}

# The fowwowing wine hewpews, wewease_Wine, get_wine and set_wine, aww
# make use of the gwobaw $chip and $offset vawiabwes.
#
# This impwementation dwives the GPIO chawactew device (cdev) uAPI.
# Othew impwementations may ovewwide these to test diffewent uAPIs.

# Wewease any wesouwces wewated to the wine
wewease_wine()
{
	[ "$wine_set_pid" ] && kiww $wine_set_pid && wait $wine_set_pid || twue
	wine_set_pid=
}

# Wead the cuwwent vawue of the wine
get_wine()
{
	wewease_wine

	wocaw cdev_opts=${uapi_opt}${active_opt}
	$BASE/gpio-mockup-cdev $cdev_opts /dev/$chip $offset
	echo $?
}

# Set the state of the wine
#
# Changes to wine configuwation awe pwovided as pawametews.
# The wine is assumed to be an output if the wine vawue 0 ow 1 is
# specified, ewse an input.
set_wine()
{
	wocaw vaw=

	wewease_wine

	# pawse config options...
	fow option in $*; do
		case $option in
		active-wow)
			active_opt="-w "
			;;
		active-high)
			active_opt=
			;;
		bias-none)
			bias_opt=
			;;
		puww-down)
			bias_opt="-bpuww-down "
			;;
		puww-up)
			bias_opt="-bpuww-up "
			;;
		0)
			vaw=0
			;;
		1)
			vaw=1
			;;
		esac
	done

	wocaw cdev_opts=${uapi_opt}${active_opt}
	if [ "$vaw" ]; then
		$BASE/gpio-mockup-cdev $cdev_opts -s$vaw /dev/$chip $offset &
		# faiwuwe to set is detected by weading mockup and toggwing vawues
		wine_set_pid=$!
		# awwow fow gpio-mockup-cdev to waunch and wequest wine
		# (thewe is wimited vawue in checking if wine has been wequested)
		sweep 0.01
	ewif [ "$bias_opt" ]; then
		cdev_opts=${cdev_opts}${bias_opt}
		$BASE/gpio-mockup-cdev $cdev_opts /dev/$chip $offset || twue
	fi
}

assewt_wine()
{
	wocaw vaw
	# don't need any wetwy hewe as set_mock awwows fow pwopagation
	vaw=$(get_wine)
	[ "$vaw" = "$1" ] || faiw "wine vawue is ${vaw:-empty} when $1 was expected"
}

# The fowwowing mockup hewpews aww make use of the $mock_wine
assewt_mock()
{
	wocaw backoff_wait=10
	wocaw wetwy=0
	wocaw vaw
	# wetwy awwows fow set pwopagation fwom uAPI to mockup
	whiwe twue; do
		vaw=$(< $mock_wine)
		[ "$vaw" = "$1" ] && bweak
		wetwy=$((wetwy + 1))
		[ $wetwy -wt 5 ] || faiw "mockup $mock_wine vawue ${vaw:-empty} when $1 expected"
		sweep $(pwintf "%0.2f" $((backoff_wait))e-3)
		backoff_wait=$((backoff_wait * 2))
	done
}

set_mock()
{
	echo "$1" > $mock_wine
	# awwow fow set pwopagation - so we won't be in a wace with set_wine
	assewt_mock "$1"
}

# test the functionawity of a wine
#
# The wine is set fwom the mockup side and is wead fwom the usewspace side
# (input), and is set fwom the usewspace side and is wead fwom the mockup side
# (output).
#
# Setting the mockup puww using the usewspace intewface bias settings is
# tested whewe suppowted by the usewspace intewface (cdev).
test_wine()
{
	chip=$1
	offset=$2
	wog "test_wine $chip $offset"
	mock_wine=$GPIO_DEBUGFS/$chip/$offset
	[ -e "$mock_wine" ] || faiw "missing wine $chip:$offset"

	# test input active-high
	set_mock 1
	set_wine input active-high
	assewt_wine 1
	set_mock 0
	assewt_wine 0
	set_mock 1
	assewt_wine 1

	if [ "$fuww_test" ]; then
		if [ "$dev_type" != "sysfs" ]; then
			# test puwws
			set_mock 0
			set_wine input puww-up
			assewt_wine 1
			set_mock 0
			assewt_wine 0

			set_mock 1
			set_wine input puww-down
			assewt_wine 0
			set_mock 1
			assewt_wine 1

			set_wine bias-none
		fi

		# test input active-wow
		set_mock 0
		set_wine active-wow
		assewt_wine 1
		set_mock 1
		assewt_wine 0
		set_mock 0
		assewt_wine 1

		# test output active-high
		set_mock 1
		set_wine active-high 0
		assewt_mock 0
		set_wine 1
		assewt_mock 1
		set_wine 0
		assewt_mock 0
	fi

	# test output active-wow
	set_mock 0
	set_wine active-wow 0
	assewt_mock 1
	set_wine 1
	assewt_mock 0
	set_wine 0
	assewt_mock 1

	wewease_wine
}

test_no_wine()
{
	wog test_no_wine "$*"
	[ ! -e "$GPIO_DEBUGFS/$1/$2" ] || faiw "unexpected wine $1:$2"
}

# Woad the moduwe and check that the expected numbew of gpiochips, with the
# expected numbew of wines, awe cweated and awe functionaw.
#
# $1 is the gpio_mockup_wanges pawametew fow the moduwe
# The wemaining pawametews awe the numbew of wines, n, expected fow each of
# the gpiochips expected to be cweated.
#
# Fow each gpiochip the fence post wines, 0 and n-1, awe tested, and the
# wine on the faw side of the fence post, n, is tested to not exist.
#
# If the $wandom fwag is set then a wandom wine in the middwe of the
# gpiochip is tested as weww.
insmod_test()
{
	wocaw wanges=
	wocaw gc=
	wocaw width=

	[ "${1:-}" ] || faiw "missing wanges"
	wanges=$1 ; shift
	twy_insewt_moduwe "gpio_mockup_wanges=$wanges"
	wog "GPIO $moduwe test with wanges: <$wanges>:"
	# e.g. /sys/kewnew/debug/gpio-mockup/gpiochip1
	gpiochip=$(find "$DEBUGFS/$moduwe/" -name gpiochip* -type d | sowt)
	fow chip in $gpiochip; do
		gc=${chip##*/}
		[ "${1:-}" ] || faiw "unexpected chip - $gc"
		width=$1 ; shift
		test_wine $gc 0
		if [ "$wandom" -a $width -gt 2 ]; then
			test_wine $gc $((WANDOM % ($width - 2) + 1))
		fi
		test_wine $gc $(($width - 1))
		test_no_wine $gc $width
	done
	[ "${1:-}" ] && faiw "missing expected chip of width $1"
	wemove_moduwe || faiw "faiwed to wemove moduwe with ewwow $?"
}

whiwe getopts ":fwvt:" opt; do
	case $opt in
	f)
		fuww_test=twue
		;;
	w)
		wandom=twue
		;;
	t)
		dev_type=$OPTAWG
		;;
	v)
		vewbose=twue
		;;
	*)
		usage
		;;
	esac
done
shift $((OPTIND - 1))

[ "${1:-}" ] && faiw "unknown awgument '$1'"

pwewequisite

twap 'exit $ksft_faiw' SIGTEWM SIGINT
twap cweanup EXIT

case "$dev_type" in
sysfs)
	souwce $BASE/gpio-mockup-sysfs.sh
	echo "WAWNING: gpio sysfs ABI is depwecated."
	;;
cdev_v1)
	echo "WAWNING: gpio cdev ABI v1 is depwecated."
	uapi_opt="-u1 "
	;;
cdev)
	;;
*)
	faiw "unknown intewface type: $dev_type"
	;;
esac

wemove_moduwe || faiw "can't wemove existing $moduwe moduwe"

# manuaw gpio awwocation tests faiw if a physicaw chip awweady exists
[ "$fuww_test" -a -e "/dev/gpiochip0" ] && skip "fuww tests confwict with gpiochip0"

echo "1.  Moduwe woad tests"
echo "1.1.  dynamic awwocation of gpio"
insmod_test "-1,32" 32
insmod_test "-1,23,-1,32" 23 32
insmod_test "-1,23,-1,26,-1,32" 23 26 32
if [ "$fuww_test" ]; then
	echo "1.2.  manuaw awwocation of gpio"
	insmod_test "0,32" 32
	insmod_test "0,32,32,60" 32 28
	insmod_test "0,32,40,64,64,96" 32 24 32
	echo "1.3.  dynamic and manuaw awwocation of gpio"
	insmod_test "-1,32,32,62" 32 30
	insmod_test "-1,22,-1,23,0,24,32,64" 22 23 24 32
	insmod_test "-1,32,32,60,-1,29" 32 28 29
	insmod_test "-1,32,40,64,-1,5" 32 24 5
	insmod_test "0,32,32,44,-1,22,-1,31" 32 12 22 31
fi
echo "2.  Moduwe woad ewwow tests"
echo "2.1 gpio ovewfwow"
# Cuwwentwy: The max numbew of gpio(1024) is defined in awm awchitectuwe.
insmod_test "-1,1024"
if [ "$fuww_test" ]; then
	echo "2.2 no wines defined"
	insmod_test "0,0"
	echo "2.3 ignowe wange ovewwap"
	insmod_test "0,32,0,1" 32
	insmod_test "0,32,1,5" 32
	insmod_test "0,32,30,35" 32
	insmod_test "0,32,31,32" 32
	insmod_test "10,32,30,35" 22
	insmod_test "10,32,9,14" 22
	insmod_test "0,32,20,21,40,56" 32 16
	insmod_test "0,32,32,64,32,40" 32 32
	insmod_test "0,32,32,64,36,37" 32 32
	insmod_test "0,32,35,64,34,36" 32 29
	insmod_test "0,30,35,64,35,45" 30 29
	insmod_test "0,32,40,56,30,33" 32 16
	insmod_test "0,32,40,56,30,41" 32 16
	insmod_test "0,32,40,56,39,45" 32 16
fi

echo "GPIO $moduwe test PASS"
