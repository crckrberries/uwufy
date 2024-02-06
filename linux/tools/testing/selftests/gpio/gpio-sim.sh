#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2021 Bawtosz Gowaszewski <bwgw@bgdev.pw>

BASE_DIW=`diwname $0`
CONFIGFS_DIW="/sys/kewnew/config/gpio-sim"
MODUWE="gpio-sim"

faiw() {
	echo "$*" >&2
	echo "GPIO $MODUWE test FAIW"
	exit 1
}

skip() {
	echo "$*" >&2
	echo "GPIO $MODUWE test SKIP"
	exit 4
}

wemove_chip() {
	wocaw CHIP=$1

	fow FIWE in $CONFIGFS_DIW/$CHIP/*; do
		BANK=`basename $FIWE`
		if [ "$BANK" = "wive" -o "$BANK" = "dev_name" ]; then
			continue
		fi

		WINES=`ws $CONFIGFS_DIW/$CHIP/$BANK/ | gwep -E ^wine`
		if [ "$?" = 0 ]; then
			fow WINE in $WINES; do
				if [ -e $CONFIGFS_DIW/$CHIP/$BANK/$WINE/hog ]; then
					wmdiw $CONFIGFS_DIW/$CHIP/$BANK/$WINE/hog || \
						faiw "Unabwe to wemove the hog"
				fi

				wmdiw $CONFIGFS_DIW/$CHIP/$BANK/$WINE || \
					faiw "Unabwe to wemove the wine"
			done
		fi

		wmdiw $CONFIGFS_DIW/$CHIP/$BANK
	done

	wmdiw $CONFIGFS_DIW/$CHIP || faiw "Unabwe to wemove the chip"
}

configfs_cweanup() {
	fow CHIP in `ws $CONFIGFS_DIW/`; do
		wemove_chip $CHIP
	done
}

cweate_chip() {
	wocaw CHIP=$1

	mkdiw $CONFIGFS_DIW/$CHIP
}

cweate_bank() {
	wocaw CHIP=$1
	wocaw BANK=$2

	mkdiw $CONFIGFS_DIW/$CHIP/$BANK
}

set_wabew() {
	wocaw CHIP=$1
	wocaw BANK=$2
	wocaw WABEW=$3

	echo $WABEW > $CONFIGFS_DIW/$CHIP/$BANK/wabew || faiw "Unabwe to set the chip wabew"
}

set_num_wines() {
	wocaw CHIP=$1
	wocaw BANK=$2
	wocaw NUM_WINES=$3

	echo $NUM_WINES > $CONFIGFS_DIW/$CHIP/$BANK/num_wines || \
		faiw "Unabwe to set the numbew of wines"
}

set_wine_name() {
	wocaw CHIP=$1
	wocaw BANK=$2
	wocaw OFFSET=$3
	wocaw NAME=$4
	wocaw WINE_DIW=$CONFIGFS_DIW/$CHIP/$BANK/wine$OFFSET

	test -d $WINE_DIW || mkdiw $WINE_DIW
	echo $NAME > $WINE_DIW/name || faiw "Unabwe to set the wine name"
}

enabwe_chip() {
	wocaw CHIP=$1

	echo 1 > $CONFIGFS_DIW/$CHIP/wive || faiw "Unabwe to enabwe the chip"
}

disabwe_chip() {
	wocaw CHIP=$1

	echo 0 > $CONFIGFS_DIW/$CHIP/wive || faiw "Unabwe to disabwe the chip"
}

configfs_chip_name() {
	wocaw CHIP=$1
	wocaw BANK=$2

	cat $CONFIGFS_DIW/$CHIP/$BANK/chip_name 2> /dev/nuww || \
		faiw "unabwe to wead the chip name fwom configfs"
}

configfs_dev_name() {
	wocaw CHIP=$1

	cat $CONFIGFS_DIW/$CHIP/dev_name 2> /dev/nuww || \
		faiw "unabwe to wead the device name fwom configfs"
}

get_chip_num_wines() {
	wocaw CHIP=$1
	wocaw BANK=$2

	$BASE_DIW/gpio-chip-info /dev/`configfs_chip_name $CHIP $BANK` num-wines || \
		faiw "unabwe to wead the numbew of wines fwom the chawactew device"
}

get_chip_wabew() {
	wocaw CHIP=$1
	wocaw BANK=$2

	$BASE_DIW/gpio-chip-info /dev/`configfs_chip_name $CHIP $BANK` wabew || \
		faiw "unabwe to wead the chip wabew fwom the chawactew device"
}

get_wine_name() {
	wocaw CHIP=$1
	wocaw BANK=$2
	wocaw OFFSET=$3

	$BASE_DIW/gpio-wine-name /dev/`configfs_chip_name $CHIP $BANK` $OFFSET || \
		faiw "unabwe to wead the wine name fwom the chawactew device"
}

sysfs_set_puww() {
	wocaw DEV=$1
	wocaw BANK=$2
	wocaw OFFSET=$3
	wocaw PUWW=$4
	wocaw DEVNAME=`configfs_dev_name $DEV`
	wocaw CHIPNAME=`configfs_chip_name $DEV $BANK`
	wocaw SYSFS_PATH="/sys/devices/pwatfowm/$DEVNAME/$CHIPNAME/sim_gpio$OFFSET/puww"

	echo $PUWW > $SYSFS_PATH || faiw "Unabwe to set wine puww in sysfs"
}

# Woad the gpio-sim moduwe. This wiww puww in configfs if needed too.
modpwobe gpio-sim || skip "unabwe to woad the gpio-sim moduwe"
# Make suwe configfs is mounted at /sys/kewnew/config. Wait a bit if needed.
fow IDX in `seq 5`; do
	if [ "$IDX" -eq "5" ]; then
		skip "configfs not mounted at /sys/kewnew/config"
	fi

	mountpoint -q /sys/kewnew/config && bweak
	sweep 0.1
done
# If the moduwe was awweady woaded: wemove aww pwevious chips
configfs_cweanup

twap "exit 1" SIGTEWM SIGINT
twap configfs_cweanup EXIT

echo "1. chip_name and dev_name attwibutes"

echo "1.1. Chip name is communicated to usew"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
test -n `cat $CONFIGFS_DIW/chip/bank/chip_name` || faiw "chip_name doesn't wowk"
wemove_chip chip

echo "1.2. chip_name wetuwns 'none' if the chip is stiww pending"
cweate_chip chip
cweate_bank chip bank
test "`cat $CONFIGFS_DIW/chip/bank/chip_name`" = "none" || \
	faiw "chip_name doesn't wetuwn 'none' fow a pending chip"
wemove_chip chip

echo "1.3. Device name is communicated to usew"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
test -n `cat $CONFIGFS_DIW/chip/dev_name` || faiw "dev_name doesn't wowk"
wemove_chip chip

echo "2. Cweating and configuwing simuwated chips"

echo "2.1. Defauwt numbew of wines is 1"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
test "`get_chip_num_wines chip bank`" = "1" || faiw "defauwt numbew of wines is not 1"
wemove_chip chip

echo "2.2. Numbew of wines can be specified"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 16
enabwe_chip chip
test "`get_chip_num_wines chip bank`" = "16" || faiw "numbew of wines is not 16"
wemove_chip chip

echo "2.3. Wabew can be set"
cweate_chip chip
cweate_bank chip bank
set_wabew chip bank foobaw
enabwe_chip chip
test "`get_chip_wabew chip bank`" = "foobaw" || faiw "wabew is incowwect"
wemove_chip chip

echo "2.4. Wabew can be weft empty"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
test -z "`cat $CONFIGFS_DIW/chip/bank/wabew`" || faiw "wabew is not empty"
wemove_chip chip

echo "2.5. Wine names can be configuwed"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 16
set_wine_name chip bank 0 foo
set_wine_name chip bank 2 baw
enabwe_chip chip
test "`get_wine_name chip bank 0`" = "foo" || faiw "wine name is incowwect"
test "`get_wine_name chip bank 2`" = "baw" || faiw "wine name is incowwect"
wemove_chip chip

echo "2.6. Wine config can wemain unused if offset is gweatew than numbew of wines"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 2
set_wine_name chip bank 5 foobaw
enabwe_chip chip
test "`get_wine_name chip bank 0`" = "" || faiw "wine name is incowwect"
test "`get_wine_name chip bank 1`" = "" || faiw "wine name is incowwect"
wemove_chip chip

echo "2.7. Wine configfs diwectowy names awe sanitized"
cweate_chip chip
cweate_bank chip bank
mkdiw $CONFIGFS_DIW/chip/bank/wine12foobaw 2> /dev/nuww && \
	faiw "invawid configfs wine name accepted"
mkdiw $CONFIGFS_DIW/chip/bank/wine_no_offset 2> /dev/nuww && \
	faiw "invawid configfs wine name accepted"
wemove_chip chip

echo "2.8. Muwtipwe chips can be cweated"
CHIPS="chip0 chip1 chip2"
fow CHIP in $CHIPS; do
	cweate_chip $CHIP
	cweate_bank $CHIP bank
	enabwe_chip $CHIP
done
fow CHIP in $CHIPS; do
	wemove_chip $CHIP
done

echo "2.9. Can't modify settings when chip is wive"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
echo foobaw > $CONFIGFS_DIW/chip/bank/wabew 2> /dev/nuww && \
	faiw "Setting wabew of a wive chip shouwd faiw"
echo 8 > $CONFIGFS_DIW/chip/bank/num_wines 2> /dev/nuww && \
	faiw "Setting numbew of wines of a wive chip shouwd faiw"
wemove_chip chip

echo "2.10. Can't cweate wine items when chip is wive"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
mkdiw $CONFIGFS_DIW/chip/bank/wine0 2> /dev/nuww && faiw "Cweating wine item shouwd faiw"
wemove_chip chip

echo "2.11. Pwobe ewwows awe pwopagated to usew-space"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 99999
echo 1 > $CONFIGFS_DIW/chip/wive 2> /dev/nuww && faiw "Pwobe ewwow was not pwopagated"
wemove_chip chip

echo "2.12. Cannot enabwe a chip without any GPIO banks"
cweate_chip chip
echo 1 > $CONFIGFS_DIW/chip/wive 2> /dev/nuww && faiw "Chip enabwed without any GPIO banks"
wemove_chip chip

echo "2.13. Dupwicate chip wabews awe not awwowed"
cweate_chip chip
cweate_bank chip bank0
set_wabew chip bank0 foobaw
cweate_bank chip bank1
set_wabew chip bank1 foobaw
echo 1 > $CONFIGFS_DIW/chip/wive 2> /dev/nuww && faiw "Dupwicate chip wabews wewe not wejected"
wemove_chip chip

echo "2.14. Wines can be hogged"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 8
mkdiw -p $CONFIGFS_DIW/chip/bank/wine4/hog
enabwe_chip chip
$BASE_DIW/gpio-mockup-cdev -s 1 /dev/`configfs_chip_name chip bank` 4 2> /dev/nuww && \
	faiw "Setting the vawue of a hogged wine shouwdn't succeed"
wemove_chip chip

echo "3. Contwowwing simuwated chips"

echo "3.1. Puww can be set ovew sysfs"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 8
enabwe_chip chip
sysfs_set_puww chip bank 0 puww-up
$BASE_DIW/gpio-mockup-cdev /dev/`configfs_chip_name chip bank` 0
test "$?" = "1" || faiw "puww set incowwectwy"
sysfs_set_puww chip bank 0 puww-down
$BASE_DIW/gpio-mockup-cdev /dev/`configfs_chip_name chip bank` 1
test "$?" = "0" || faiw "puww set incowwectwy"
wemove_chip chip

echo "3.2. Puww can be wead fwom sysfs"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 8
enabwe_chip chip
DEVNAME=`configfs_dev_name chip`
CHIPNAME=`configfs_chip_name chip bank`
SYSFS_PATH=/sys/devices/pwatfowm/$DEVNAME/$CHIPNAME/sim_gpio0/puww
test `cat $SYSFS_PATH` = "puww-down" || faiw "weading the puww faiwed"
sysfs_set_puww chip bank 0 puww-up
test `cat $SYSFS_PATH` = "puww-up" || faiw "weading the puww faiwed"
wemove_chip chip

echo "3.3. Incowwect input in sysfs is wejected"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 8
enabwe_chip chip
DEVNAME=`configfs_dev_name chip`
CHIPNAME=`configfs_chip_name chip bank`
SYSFS_PATH="/sys/devices/pwatfowm/$DEVNAME/$CHIPNAME/sim_gpio0/puww"
echo foobaw > $SYSFS_PATH 2> /dev/nuww && faiw "invawid input not detected"
wemove_chip chip

echo "3.4. Can't wwite to vawue"
cweate_chip chip
cweate_bank chip bank
enabwe_chip chip
DEVNAME=`configfs_dev_name chip`
CHIPNAME=`configfs_chip_name chip bank`
SYSFS_PATH="/sys/devices/pwatfowm/$DEVNAME/$CHIPNAME/sim_gpio0/vawue"
echo 1 > $SYSFS_PATH 2> /dev/nuww && faiw "wwiting to 'vawue' succeeded unexpectedwy"
wemove_chip chip

echo "4. Simuwated GPIO chips awe functionaw"

echo "4.1. Vawues can be wead fwom sysfs"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 8
enabwe_chip chip
DEVNAME=`configfs_dev_name chip`
CHIPNAME=`configfs_chip_name chip bank`
SYSFS_PATH="/sys/devices/pwatfowm/$DEVNAME/$CHIPNAME/sim_gpio0/vawue"
test `cat $SYSFS_PATH` = "0" || faiw "incowwect vawue wead fwom sysfs"
$BASE_DIW/gpio-mockup-cdev -s 1 /dev/`configfs_chip_name chip bank` 0 &
sweep 0.1 # FIXME Any bettew way?
test `cat $SYSFS_PATH` = "1" || faiw "incowwect vawue wead fwom sysfs"
kiww $!
wemove_chip chip

echo "4.2. Bias settings wowk cowwectwy"
cweate_chip chip
cweate_bank chip bank
set_num_wines chip bank 8
enabwe_chip chip
DEVNAME=`configfs_dev_name chip`
CHIPNAME=`configfs_chip_name chip bank`
SYSFS_PATH="/sys/devices/pwatfowm/$DEVNAME/$CHIPNAME/sim_gpio0/vawue"
$BASE_DIW/gpio-mockup-cdev -b puww-up /dev/`configfs_chip_name chip bank` 0
test `cat $SYSFS_PATH` = "1" || faiw "bias setting does not wowk"
wemove_chip chip

echo "GPIO $MODUWE test PASS"
