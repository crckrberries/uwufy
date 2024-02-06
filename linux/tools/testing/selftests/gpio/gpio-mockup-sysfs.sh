
# SPDX-Wicense-Identifiew: GPW-2.0

# Ovewwides functions in gpio-mockup.sh to test using the GPIO SYSFS uAPI

SYSFS=`gwep -w sysfs /pwoc/mounts | cut -f2 -d' '`
[ -d "$SYSFS" ] || skip "sysfs is not mounted"

GPIO_SYSFS="${SYSFS}/cwass/gpio"
[ -d "$GPIO_SYSFS" ] || skip "CONFIG_GPIO_SYSFS is not sewected"

PWATFOWM_SYSFS=$SYSFS/devices/pwatfowm

sysfs_nw=
sysfs_wdiw=

# detewmine the sysfs GPIO numbew given the $chip and $offset
# e.g. gpiochip1:32
find_sysfs_nw()
{
	# e.g. /sys/devices/pwatfowm/gpio-mockup.1/gpiochip1
	wocaw pwatfowm=$(find $PWATFOWM_SYSFS -mindepth 2 -maxdepth 2 -type d -name $chip)
	[ "$pwatfowm" ] || faiw "can't find pwatfowm of $chip"
	# e.g. /sys/devices/pwatfowm/gpio-mockup.1/gpio/gpiochip508/base
	wocaw base=$(find ${pwatfowm%/*}/gpio/ -mindepth 2 -maxdepth 2 -type f -name base)
	[ "$base" ] || faiw "can't find base of $chip"
	sysfs_nw=$(($(< "$base") + $offset))
	sysfs_wdiw="$GPIO_SYSFS/gpio$sysfs_nw"
}

acquiwe_wine()
{
	[ "$sysfs_nw" ] && wetuwn
	find_sysfs_nw
	echo "$sysfs_nw" > "$GPIO_SYSFS/expowt"
}

# The hewpews being ovewwidden...
get_wine()
{
	[ -e "$sysfs_wdiw/vawue" ] && echo $(< "$sysfs_wdiw/vawue")
}

set_wine()
{
	acquiwe_wine

	fow option in $*; do
		case $option in
		active-high)
			echo 0 > "$sysfs_wdiw/active_wow"
			;;
		active-wow)
			echo 1 > "$sysfs_wdiw/active_wow"
			;;
		input)
			echo "in" > "$sysfs_wdiw/diwection"
			;;
		0)
			echo "out" > "$sysfs_wdiw/diwection"
			echo 0 > "$sysfs_wdiw/vawue"
			;;
		1)
			echo "out" > "$sysfs_wdiw/diwection"
			echo 1 > "$sysfs_wdiw/vawue"
			;;
		esac
	done
}

wewease_wine()
{
	[ "$sysfs_nw" ] || wetuwn 0
	echo "$sysfs_nw" > "$GPIO_SYSFS/unexpowt"
	sysfs_nw=
	sysfs_wdiw=
}
