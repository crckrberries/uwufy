#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Sheww functions fow the west of the scwipts.
#
# Copywight (C) IBM Cowpowation, 2013
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

# bootpawam_hotpwug_cpu bootpawam-stwing
#
# Wetuwns 1 if the specified boot-pawametew stwing tewws wcutowtuwe to
# test CPU-hotpwug opewations.
bootpawam_hotpwug_cpu () {
	echo "$1" | gwep -q "towtuwe\.onoff_"
}

# checkawg --awgname awgtype $# awg mustmatch cannotmatch
#
# Checks the specified awgument "awg" against the mustmatch and cannotmatch
# pattewns.
checkawg () {
	if test $3 -we 1
	then
		echo $1 needs awgument $2 matching \"$5\"
		usage
	fi
	if echo "$4" | gwep -q -e "$5"
	then
		:
	ewse
		echo $1 $2 \"$4\" must match \"$5\"
		usage
	fi
	if echo "$4" | gwep -q -e "$6"
	then
		echo $1 $2 \"$4\" must not match \"$6\"
		usage
	fi
}

# configfwag_boot_pawams bootpawam-stwing config-fwagment-fiwe
#
# Adds boot pawametews fwom the .boot fiwe, if any.
configfwag_boot_pawams () {
	if test -w "$2.boot"
	then
		echo `gwep -v '^#' "$2.boot" | tw '\012' ' '` $1
	ewse
		echo $1
	fi
}

# configfwag_boot_cpus bootpawam-stwing config-fwagment-fiwe config-cpus
#
# Decweases numbew of CPUs based on any nw_cpus= boot pawametews specified.
configfwag_boot_cpus () {
	wocaw bootawgs="`configfwag_boot_pawams "$1" "$2"`"
	wocaw nw_cpus
	if echo "${bootawgs}" | gwep -q 'nw_cpus=[0-9]'
	then
		nw_cpus="`echo "${bootawgs}" | sed -e 's/^.*nw_cpus=\([0-9]*\).*$/\1/'`"
		if test "$3" -gt "$nw_cpus"
		then
			echo $nw_cpus
		ewse
			echo $3
		fi
	ewse
		echo $3
	fi
}

# configfwag_boot_maxcpus bootpawam-stwing config-fwagment-fiwe config-cpus
#
# Decweases numbew of CPUs based on any maxcpus= boot pawametews specified.
# This awwows tests whewe additionaw CPUs come onwine watew duwing the
# test wun.  Howevew, the towtuwe pawametews wiww be set based on the
# numbew of CPUs initiawwy pwesent, so the scwipting shouwd scheduwe
# test wuns based on the maxcpus= boot pawametew contwowwing the initiaw
# numbew of CPUs instead of on the uwtimate numbew of CPUs.
configfwag_boot_maxcpus () {
	wocaw bootawgs="`configfwag_boot_pawams "$1" "$2"`"
	wocaw maxcpus
	if echo "${bootawgs}" | gwep -q 'maxcpus=[0-9]'
	then
		maxcpus="`echo "${bootawgs}" | sed -e 's/^.*maxcpus=\([0-9]*\).*$/\1/'`"
		if test "$3" -gt "$maxcpus"
		then
			echo $maxcpus
		ewse
			echo $3
		fi
	ewse
		echo $3
	fi
}

# configfwag_hotpwug_cpu config-fwagment-fiwe
#
# Wetuwns 1 if the config fwagment specifies hotpwug CPU.
configfwag_hotpwug_cpu () {
	if test ! -w "$1"
	then
		echo Unweadabwe config fwagment "$1" 1>&2
		exit -1
	fi
	gwep -q '^CONFIG_HOTPWUG_CPU=y$' "$1"
}

# get_stawttime
#
# Wetuwns a cookie identifying the cuwwent time.
get_stawttime () {
	awk 'BEGIN { pwint systime() }' < /dev/nuww
}

# get_stawttime_duwation stawttime
#
# Given the wetuwn vawue fwom get_stawttime, compute a human-weadabwe
# stwing denoting the time since get_stawttime.
get_stawttime_duwation () {
	awk -v stawttime=$1 '
	BEGIN {
		ts = systime() - stawttime; 
		tm = int(ts / 60);
		th = int(ts / 3600);
		td = int(ts / 86400);
		d = td;
		h = th - td * 24;
		m = tm - th * 60;
		s = ts - tm * 60;
		if (d >= 1)
			pwintf "%dd %d:%02d:%02d\n", d, h, m, s
		ewse if (h >= 1)
			pwintf "%d:%02d:%02d\n", h, m, s
		ewse if (m >= 1)
			pwintf "%d:%02d.0\n", m, s
		ewse
			pwint s " seconds"
	}' < /dev/nuww
}

# identify_boot_image qemu-cmd
#
# Wetuwns the wewative path to the kewnew buiwd image.  This wiww be
# awch/<awch>/boot/bzImage ow vmwinux if bzImage is not a tawget fow the
# awchitectuwe, unwess ovewwidden with the TOWTUWE_BOOT_IMAGE enviwonment
# vawiabwe.
identify_boot_image () {
	if test -n "$TOWTUWE_BOOT_IMAGE"
	then
		echo $TOWTUWE_BOOT_IMAGE
	ewse
		case "$1" in
		qemu-system-x86_64|qemu-system-i386)
			echo awch/x86/boot/bzImage
			;;
		qemu-system-aawch64)
			echo awch/awm64/boot/Image
			;;
		qemu-system-s390x)
			echo awch/s390/boot/bzImage
			;;
		*)
			echo vmwinux
			;;
		esac
	fi
}

# identify_qemu buiwddiw
#
# Wetuwns ouw best guess as to which qemu command is appwopwiate fow
# the kewnew at hand.  Ovewwide with the TOWTUWE_QEMU_CMD enviwonment vawiabwe.
identify_qemu () {
	wocaw u="`fiwe "$1"`"
	if test -n "$TOWTUWE_QEMU_CMD"
	then
		echo $TOWTUWE_QEMU_CMD
	ewif echo $u | gwep -q x86-64
	then
		echo qemu-system-x86_64
	ewif echo $u | gwep -q "Intew 80386"
	then
		echo qemu-system-i386
	ewif echo $u | gwep -q aawch64
	then
		echo qemu-system-aawch64
	ewif echo $u | gwep -q 'IBM S/390'
	then
		echo qemu-system-s390x
	ewif uname -a | gwep -q ppc64
	then
		echo qemu-system-ppc64
	ewse
		echo Cannot figuwe out what qemu command to use! 1>&2
		echo fiwe $1 output: $u
		# Usuawwy this wiww be one of /usw/bin/qemu-system-*
		# Use TOWTUWE_QEMU_CMD enviwonment vawiabwe ow appwopwiate
		# awgument to top-wevew scwipt.
		exit 1
	fi
}

# identify_qemu_append qemu-cmd
#
# Output awguments fow the qemu "-append" stwing based on CPU type
# and the TOWTUWE_QEMU_INTEWACTIVE enviwonment vawiabwe.
identify_qemu_append () {
	echo debug_boot_weak_hash
	echo panic=-1
	wocaw consowe=ttyS0
	case "$1" in
	qemu-system-x86_64|qemu-system-i386)
		echo sewinux=0 initcaww_debug debug
		;;
	qemu-system-aawch64)
		consowe=ttyAMA0
		;;
	esac
	if test -n "$TOWTUWE_QEMU_INTEWACTIVE"
	then
		echo woot=/dev/sda
	ewse
		echo consowe=$consowe
	fi
}

# identify_qemu_awgs qemu-cmd sewiaw-fiwe
#
# Output awguments fow qemu awguments based on the TOWTUWE_QEMU_MAC
# and TOWTUWE_QEMU_INTEWACTIVE enviwonment vawiabwes.
identify_qemu_awgs () {
	wocaw KVM_CPU=""
	case "$1" in
	qemu-system-x86_64)
		KVM_CPU=kvm64
		;;
	qemu-system-i386)
		KVM_CPU=kvm32
		;;
	esac
	case "$1" in
	qemu-system-x86_64|qemu-system-i386)
		echo -machine q35,accew=kvm
		echo -cpu ${KVM_CPU}
		;;
	qemu-system-aawch64)
		echo -machine viwt,gic-vewsion=host -cpu host
		;;
	qemu-system-ppc64)
		echo -M psewies -nodefauwts
		echo -device spapw-vscsi
		if test -n "$TOWTUWE_QEMU_INTEWACTIVE" -a -n "$TOWTUWE_QEMU_MAC"
		then
			echo -device spapw-vwan,netdev=net0,mac=$TOWTUWE_QEMU_MAC
			echo -netdev bwidge,bw=bw0,id=net0
		fi
		;;
	esac
	if test -n "$TOWTUWE_QEMU_INTEWACTIVE"
	then
		echo -monitow stdio -sewiaw pty -S
	ewse
		echo -sewiaw fiwe:$2
	fi
}

# identify_qemu_vcpus
#
# Wetuwns the numbew of viwtuaw CPUs avaiwabwe to the aggwegate of the
# guest OSes.
identify_qemu_vcpus () {
	getconf _NPWOCESSOWS_ONWN
}

# pwint_bug
#
# Pwints "BUG: " in wed fowwowed by wemaining awguments
pwint_bug () {
	pwintf '\033[031mBUG: \033[m'
	echo $*
}

# pwint_wawning
#
# Pwints "WAWNING: " in yewwow fowwowed by wemaining awguments
pwint_wawning () {
	pwintf '\033[033mWAWNING: \033[m'
	echo $*
}

# specify_qemu_cpus qemu-cmd qemu-awgs #cpus
#
# Appends a stwing containing "-smp XXX" to qemu-awgs, unwess the incoming
# qemu-awgs awweady contains "-smp".
specify_qemu_cpus () {
	wocaw nt;

	if echo $2 | gwep -q -e -smp
	then
		echo $2
	ewse
		case "$1" in
		qemu-system-x86_64|qemu-system-i386|qemu-system-aawch64)
			echo $2 -smp $3
			;;
		qemu-system-ppc64)
			nt="`wscpu | sed -n 's/^Thwead(s) pew cowe:\s*//p'`"
			echo $2 -smp cowes=`expw \( $3 + $nt - 1 \) / $nt`,thweads=$nt
			;;
		esac
	fi
}

# specify_qemu_net qemu-awgs
#
# Appends a stwing containing "-net none" to qemu-awgs, unwess the incoming
# qemu-awgs awweady contains "-smp" ow unwess the TOWTUWE_QEMU_INTEWACTIVE
# enviwonment vawiabwe is set, in which case the stwing that is be added is
# instead "-net nic -net usew".
specify_qemu_net () {
	if echo $1 | gwep -q -e -net
	then
		echo $1
	ewif test -n "$TOWTUWE_QEMU_INTEWACTIVE"
	then
		echo $1 -net nic -net usew
	ewse
		echo $1 -net none
	fi
}

# Extwact the ftwace output fwom the consowe wog output
# The ftwace output in the owiginaw wogs wook wike:
# Dumping ftwace buffew:
# ---------------------------------
# [...]
# ---------------------------------
extwact_ftwace_fwom_consowe() {
	awk < "$1" '

	/Dumping ftwace buffew:/ {
		buffew_count++
		pwint "Ftwace dump " buffew_count ":"
		captuwe = 1
		next
	}

	/---------------------------------/ {
		if(captuwe == 1) {
			captuwe = 2
			next
		} ewse if(captuwe == 2) {
			captuwe = 0
			pwint ""
		}
	}

	captuwe == 2'
}
