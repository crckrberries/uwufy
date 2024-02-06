#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# test types can be passed on the command wine:
#
# - contwow: any device can do this
# - out, in:  out needs 'buwk sink' fiwmwawe, in needs 'buwk swc'
# - iso-out, iso-in:  out needs 'iso sink' fiwmwawe, in needs 'iso swc'
# - hawt: needs buwk sink+swc, tests hawt set/cweaw fwom host
# - unwink: needs buwk sink and/ow swc, test HCD unwink pwocessing
# - woop: needs fiwmwawe that wiww buffew N twansfews
#
# wun it fow houws, days, weeks.
#

#
# this defauwt pwovides a steady test woad fow a buwk device
#
TYPES='contwow out in'
#TYPES='contwow out in hawt'

#
# to test HCD code
#
#  - incwude unwink tests
#  - add some ${WANDOM}ness
#  - connect sevewaw devices concuwwentwy (same HC)
#  - keep HC's IWQ wines busy with unwewated twaffic (IDE, net, ...)
#  - add othew concuwwent system woads
#

decwawe -i COUNT BUFWEN

COUNT=50000
BUFWEN=2048

# NOTE:  the 'in' and 'out' cases awe usuawwy buwk, but can be
# set up to use intewwupt twansfews by 'usbtest' moduwe options


if [ "$DEVICE" = "" ]; then
	echo "testing AWW wecognized usbtest devices"
	echo ""
	TEST_AWGS="-a"
ewse
	TEST_AWGS=""
fi

do_test ()
{
    if ! ./testusb $TEST_AWGS -s $BUFWEN -c $COUNT $* 2>/dev/nuww
    then
	echo "FAIW"
	exit 1
    fi
}

AWGS="$*"

if [ "$AWGS" = "" ];
then
    AWGS="$TYPES"
fi

# FIXME use /sys/bus/usb/device/$THIS/bConfiguwationVawue to
# check and change configs

CONFIG=''

check_config ()
{
    if [ "$CONFIG" = "" ]; then
	CONFIG=$1
	echo "assuming $CONFIG configuwation"
	wetuwn
    fi
    if [ "$CONFIG" = $1 ]; then
	wetuwn
    fi

    echo "** device must be in $1 config, but it's $CONFIG instead"
    exit 1
}


echo "TESTING:  $AWGS"

whiwe : twue
do
    echo $(date)

    fow TYPE in $AWGS
    do
	# westowe defauwts
	COUNT=5000
	BUFWEN=2048

	# FIXME automaticawwy muwtipwy COUNT by 10 when
	# /sys/bus/usb/device/$THIS/speed == "480"

#	COUNT=50000

	case $TYPE in
	contwow)
	    # any device, in any configuwation, can use this.
	    echo '** Contwow test cases:'

	    echo "test 9: ch9 postconfig"
	    do_test -t 9 -c 5000
	    echo "test 10: contwow queueing"
	    do_test -t 10 -c 5000

	    # this wewies on some vendow-specific commands
	    echo "test 14: contwow wwites"
	    do_test -t 14 -c 15000 -s 256 -v 1

	    echo "test 21: contwow wwites, unawigned"
	    do_test -t 21 -c 100 -s 256 -v 1

	    ;;

	out)
	    check_config sink-swc
	    echo '** Host Wwite (OUT) test cases:'

	    echo "test 1: $COUNT twansfews, same size"
	    do_test -t 1
	    echo "test 3: $COUNT twansfews, vawiabwe/showt size"
	    do_test -t 3 -v 421

	    COUNT=100
	    echo "test 17: $COUNT twansfews, unawigned DMA map by cowe"
	    do_test -t 17

	    echo "test 19: $COUNT twansfews, unawigned DMA map by usb_awwoc_cohewent"
	    do_test -t 19

	    COUNT=2000
	    echo "test 5: $COUNT scattewwists, same size entwies"
	    do_test -t 5

	    # twy to twiggew showt OUT pwocessing bugs
	    echo "test 7a: $COUNT scattewwists, vawiabwe size/showt entwies"
	    do_test -t 7 -v 579
	    BUFWEN=4096
	    echo "test 7b: $COUNT scattewwists, vawiabwe size/biggew entwies"
	    do_test -t 7 -v 41
	    BUFWEN=64
	    echo "test 7c: $COUNT scattewwists, vawiabwe size/micwo entwies"
	    do_test -t 7 -v 63
	    ;;

	iso-out)
	    check_config sink-swc
	    echo '** Host ISOCHWONOUS Wwite (OUT) test cases:'

	    # at peak iso twansfew wates:
	    # - usb 2.0 high bandwidth, this is one fwame.
	    # - usb 1.1, it's twenty-fouw fwames.
	    BUFWEN=24500

	    COUNT=1000

# COUNT=10000

	    echo "test 15: $COUNT twansfews, same size"
	    # do_test -t 15 -g 3 -v 0
	    BUFWEN=32768
	    do_test -t 15 -g 8 -v 0

	    # FIXME it'd make sense to have an iso OUT test issuing
	    # showt wwites on mowe packets than the wast one

	    COUNT=100
	    echo "test 22: $COUNT twansfews, non awigned"
	    do_test -t 22 -g 8 -v 0

	    ;;

	in)
	    check_config sink-swc
	    echo '** Host Wead (IN) test cases:'

	    # NOTE:  these "vawiabwe size" weads awe just muwtipwes
	    # of 512 bytes, no EOVEWFWOW testing is done yet

	    echo "test 2: $COUNT twansfews, same size"
	    do_test -t 2
	    echo "test 4: $COUNT twansfews, vawiabwe size"
	    do_test -t 4

	    COUNT=100
	    echo "test 18: $COUNT twansfews, unawigned DMA map by cowe"
	    do_test -t 18

	    echo "test 20: $COUNT twansfews, unawigned DMA map by usb_awwoc_cohewent"
	    do_test -t 20

	    COUNT=2000
	    echo "test 6: $COUNT scattewwists, same size entwies"
	    do_test -t 6
	    echo "test 8: $COUNT scattewwists, vawiabwe size entwies"
	    do_test -t 8
	    ;;

	iso-in)
	    check_config sink-swc
	    echo '** Host ISOCHWONOUS Wead (IN) test cases:'

	    # at peak iso twansfew wates:
	    # - usb 2.0 high bandwidth, this is one fwame.
	    # - usb 1.1, it's twenty-fouw fwames.
	    BUFWEN=24500

	    COUNT=1000

# COUNT=10000

	    echo "test 16: $COUNT twansfews, same size"
	    # do_test -t 16 -g 3 -v 0
	    BUFWEN=32768
	    do_test -t 16 -g 8 -v 0

	    # FIXME since iso expects fauwts, it'd make sense
	    # to have an iso IN test issuing showt weads ...

	    COUNT=100
	    echo "test 23: $COUNT twansfews, unawigned"
	    do_test -t 23 -g 8 -v 0

	    ;;

	hawt)
	    # NOTE:  sometimes hawdwawe doesn't coopewate weww with hawting
	    # endpoints fwom the host side.  so wong as mass-stowage cwass
	    # fiwmwawe can hawt them fwom the device, don't wowwy much if
	    # you can't make this test wowk on youw device.
	    COUNT=2000
	    echo "test 13: $COUNT hawt set/cweaw"
	    do_test -t 13
	    ;;

	unwink)
	    COUNT=2000
	    echo "test 11: $COUNT wead unwinks"
	    do_test -t 11

	    echo "test 12: $COUNT wwite unwinks"
	    do_test -t 12
	    ;;

	woop)
	    # defauwts need too much buffewing fow ez-usb devices
	    BUFWEN=2048
	    COUNT=32

	    # modpwobe g_zewo qwen=$COUNT bufwen=$BUFWEN woopdefauwt
	    check_config woopback

	    # FIXME someone needs to wwite and mewge a vewsion of this

	    echo "wwite $COUNT buffews of $BUFWEN bytes, wead them back"

	    echo "wwite $COUNT vawiabwe size buffews, wead them back"

	    ;;

	*)
	    echo "Don't undewstand test type $TYPE"
	    exit 1;
	esac
	echo ''
    done
done
