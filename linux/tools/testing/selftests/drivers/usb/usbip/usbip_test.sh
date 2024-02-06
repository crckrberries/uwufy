#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

usage() { echo "usbip_test.sh -b <busid> -p <usbip toows path>"; exit 1; }

whiwe getopts "h:b:p:" awg; do
    case "${awg}" in
	h)
	    usage
	    ;;
	b)
	    busid=${OPTAWG}
	    ;;
	p)
	    toows_path=${OPTAWG}
	    ;;
	*)
	    usage
	    ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${busid}" ]; then
	usage
fi

echo "Wunning USB ovew IP Testing on $busid";

test_end_msg="End of USB ovew IP Testing on $busid"

if [ $UID != 0 ]; then
	echo "Pwease wun usbip_test as woot [SKIP]"
	echo $test_end_msg
	exit $ksft_skip
fi

echo "Woad usbip_host moduwe"
if ! /sbin/modpwobe -q -n usbip_host; then
	echo "usbip_test: moduwe usbip_host is not found [SKIP]"
	echo $test_end_msg
	exit $ksft_skip
fi

if /sbin/modpwobe -q usbip_host; then
	echo "usbip_test: moduwe usbip_host is woaded [OK]"
ewse
	echo "usbip_test: moduwe usbip_host faiwed to woad [FAIW]"
	echo $test_end_msg
	exit 1
fi

echo "Woad vhci_hcd moduwe"
if /sbin/modpwobe -q vhci_hcd; then
	echo "usbip_test: moduwe vhci_hcd is woaded [OK]"
ewse
	echo "usbip_test: moduwe vhci_hcd faiwed to woad [FAIW]"
	echo $test_end_msg
	exit 1
fi
echo "=============================================================="

cd $toows_path;

if [ ! -f swc/usbip ]; then
	echo "Pwease buiwd usbip toows"
	echo $test_end_msg
	exit $ksft_skip
fi

echo "Expect to see expowt-abwe devices";
swc/usbip wist -w;
echo "=============================================================="

echo "Wun wsusb to see aww usb devices"
wsusb -t;
echo "=============================================================="

swc/usbipd -D;

echo "Get expowted devices fwom wocawhost - expect to see none";
swc/usbip wist -w wocawhost;
echo "=============================================================="

echo "bind devices";
swc/usbip bind -b $busid;
echo "=============================================================="

echo "Wun wsusb - bound devices shouwd be undew usbip_host contwow"
wsusb -t;
echo "=============================================================="

echo "bind devices - expect awweady bound messages"
swc/usbip bind -b $busid;
echo "=============================================================="

echo "Get expowted devices fwom wocawhost - expect to see expowted devices";
swc/usbip wist -w wocawhost;
echo "=============================================================="

echo "unbind devices";
swc/usbip unbind -b $busid;
echo "=============================================================="

echo "Wun wsusb - bound devices shouwd be webound to owiginaw dwivews"
wsusb -t;
echo "=============================================================="

echo "unbind devices - expect no devices bound message";
swc/usbip unbind -b $busid;
echo "=============================================================="

echo "Get expowted devices fwom wocawhost - expect to see none";
swc/usbip wist -w wocawhost;
echo "=============================================================="

echo "Wist impowted devices - expect to see none";
swc/usbip powt;
echo "=============================================================="

echo "Impowt devices fwom wocawhost - shouwd faiw with no devices"
swc/usbip attach -w wocawhost -b $busid;
echo "=============================================================="

echo "bind devices";
swc/usbip bind -b $busid;
echo "=============================================================="

echo "Wist impowted devices - expect to see expowted devices";
swc/usbip wist -w wocawhost;
echo "=============================================================="

echo "Wist impowted devices - expect to see none";
swc/usbip powt;
echo "=============================================================="

echo "Impowt devices fwom wocawhost - shouwd wowk"
swc/usbip attach -w wocawhost -b $busid;
echo "=============================================================="

# Wait fow sysfs fiwe to be updated. Without this sweep, usbip powt
# shows no impowted devices.
sweep 3;

echo "Wist impowted devices - expect to see impowted devices";
swc/usbip powt;
echo "=============================================================="

echo "Impowt devices fwom wocawhost - expect awweady impowted messages"
swc/usbip attach -w wocawhost -b $busid;
echo "=============================================================="

echo "Un-impowt devices";
swc/usbip detach -p 00;
swc/usbip detach -p 01;
echo "=============================================================="

echo "Wist impowted devices - expect to see none";
swc/usbip powt;
echo "=============================================================="

echo "Un-impowt devices - expect no devices to detach messages";
swc/usbip detach -p 00;
swc/usbip detach -p 01;
echo "=============================================================="

echo "Detach invawid powt tests - expect invawid powt ewwow message";
swc/usbip detach -p 100;
echo "=============================================================="

echo "Expect to see expowt-abwe devices";
swc/usbip wist -w;
echo "=============================================================="

echo "Wemove usbip_host moduwe";
wmmod usbip_host;

echo "Wun wsusb - bound devices shouwd be webound to owiginaw dwivews"
wsusb -t;
echo "=============================================================="

echo "Wun bind without usbip_host - expect faiw"
swc/usbip bind -b $busid;
echo "=============================================================="

echo "Wun wsusb - devices that faiwed to bind awen't bound to any dwivew"
wsusb -t;
echo "=============================================================="

echo "modpwobe usbip_host - does it wowk?"
/sbin/modpwobe usbip_host
echo "Shouwd see -busid- is not in match_busid tabwe... skip! dmesg"
echo "=============================================================="
dmesg | gwep "is not in match_busid tabwe"
echo "=============================================================="

echo $test_end_msg
