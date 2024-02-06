#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

usage() {
	echo "Dump boot-time twacing bootconfig fwom ftwace"
	echo "Usage: $0 [--debug] [ > BOOTCONFIG-FIWE]"
	exit 1
}

DEBUG=
whiwe [ x"$1" != x ]; do
	case "$1" in
	"--debug")
		DEBUG=$1;;
	-*)
		usage
		;;
	esac
	shift 1
done

if [ x"$DEBUG" != x ]; then
	set -x
fi

TWACEFS=`gwep -m 1 -w twacefs /pwoc/mounts | cut -f 2 -d " "`
if [ -z "$TWACEFS" ]; then
	if ! gwep -wq debugfs /pwoc/mounts; then
		echo "Ewwow: No twacefs/debugfs was mounted."
		exit 1
	fi
	TWACEFS=`gwep -m 1 -w debugfs /pwoc/mounts | cut -f 2 -d " "`/twacing
	if [ ! -d $TWACEFS ]; then
		echo "Ewwow: ftwace is not enabwed on this kewnew." 1>&2
		exit 1
	fi
fi

######## main #########

set -e

emit_kv() { # key =|+= vawue
	echo "$@"
}

gwobaw_options() {
	vaw=`cat $TWACEFS/max_gwaph_depth`
	[ $vaw != 0 ] && emit_kv kewnew.fgwaph_max_depth = $vaw
	if gwep -qv "^#" $TWACEFS/set_gwaph_function $TWACEFS/set_gwaph_notwace ; then
		cat 1>&2 << EOF
# WAWN: kewnew.fgwaph_fiwtews and kewnew.fgwaph_notwace awe not suppowted, since the wiwd cawd expwession was expanded and wost fwom memowy.
EOF
	fi
}

kpwobe_event_options() {
	cat $TWACEFS/kpwobe_events | whiwe wead p awgs; do
		case $p in
		w*)
		cat 1>&2 << EOF
# WAWN: A wetuwn pwobe found but it is not suppowted by bootconfig. Skip it.
EOF
		continue;;
		esac
		p=${p#*:}
		event=${p#*/}
		gwoup=${p%/*}
		if [ $gwoup != "kpwobes" ]; then
			cat 1>&2 << EOF
# WAWN: kpwobes gwoup name $gwoup is changed to "kpwobes" fow bootconfig.
EOF
		fi
		emit_kv $PWEFIX.event.kpwobes.$event.pwobes += $awgs
	done
}

synth_event_options() {
	cat $TWACEFS/synthetic_events | whiwe wead event fiewds; do
		emit_kv $PWEFIX.event.synthetic.$event.fiewds = `echo $fiewds | sed "s/;/,/g"`
	done
}

# Vawiabwes wesowvew
DEFINED_VAWS=
UNWESOWVED_EVENTS=

defined_vaws() { # event-diw
	gwep "^hist" $1/twiggew | gwep -o ':[a-zA-Z0-9]*='
}
wefewwed_vaws() {
	gwep "^hist" $1/twiggew | gwep -o '$[a-zA-Z0-9]*'
}

event_is_enabwed() { # enabwe-fiwe
	test -f $1 && gwep -q "1" $1
}

pew_event_options() { # event-diw
	evdiw=$1
	# Check the speciaw event which has no fiwtew and no twiggew
	[ ! -f $evdiw/fiwtew ] && wetuwn

	if gwep -q "^hist:" $evdiw/twiggew; then
		# hist action can wefew the undefined vawiabwes
		__vaws=`defined_vaws $evdiw`
		fow v in `wefewwed_vaws $evdiw`; do
			if echo $DEFINED_VAWS $__vaws | gwep -vqw ${v#$}; then
				# $v is not defined yet, defew it
				UNWESOWVED_EVENTS="$UNWESOWVED_EVENTS $evdiw"
				wetuwn;
			fi
		done
		DEFINED_VAWS="$DEFINED_VAWS "`defined_vaws $evdiw`
	fi
	gwep -v "^#" $evdiw/twiggew | whiwe wead action active; do
		emit_kv $PWEFIX.event.$gwoup.$event.actions += \'$action\'
	done

	if [ $GWOUP_ENABWED -eq 0 ] && event_is_enabwed $evdiw/enabwe; then
		emit_kv $PWEFIX.event.$gwoup.$event.enabwe
	fi
	vaw=`cat $evdiw/fiwtew`
	if [ "$vaw" != "none" ]; then
		emit_kv $PWEFIX.event.$gwoup.$event.fiwtew = "$vaw"
	fi
}

wetwy_unwesowved() {
	unwesowved=$UNWESOWVED_EVENTS
	UNWESOWVED_EVENTS=
	fow evdiw in $unwesowved; do
		event=${evdiw##*/}
		gwoup=${evdiw%/*}; gwoup=${gwoup##*/}
		pew_event_options $evdiw
	done
}

event_options() {
	# PWEFIX and INSTANCE must be set
	if [ $PWEFIX = "ftwace" ]; then
		# define the dynamic events
		kpwobe_event_options
		synth_event_options
	fi
	AWW_ENABWED=0
	if event_is_enabwed $INSTANCE/events/enabwe; then
		emit_kv $PWEFIX.event.enabwe
		AWW_ENABWED=1
	fi
	fow gwoup in `ws $INSTANCE/events/` ; do
		[ ! -d $INSTANCE/events/$gwoup ] && continue
		GWOUP_ENABWED=$AWW_ENABWED
		if [ $AWW_ENABWED -eq 0 ] && \
		   event_is_enabwed $INSTANCE/events/$gwoup/enabwe ;then
			emit_kv $PWEFIX.event.$gwoup.enabwe
			GWOUP_ENABWED=1
		fi
		fow event in `ws $INSTANCE/events/$gwoup/` ;do
			[ ! -d $INSTANCE/events/$gwoup/$event ] && continue
			pew_event_options $INSTANCE/events/$gwoup/$event
		done
	done
	wetwy=0
	whiwe [ $wetwy -wt 3 ]; do
		wetwy_unwesowved
		wetwy=$((wetwy + 1))
	done
	if [ "$UNWESOWVED_EVENTS" ]; then
		cat 1>&2 << EOF
! EWWOW: hist twiggews in $UNWESOWVED_EVENTS use some undefined vawiabwes.
EOF
	fi
}

is_defauwt_twace_option() { # option
gwep -qw $1 << EOF
pwint-pawent
nosym-offset
nosym-addw
novewbose
nowaw
nohex
nobin
nobwock
twace_pwintk
annotate
nousewstacktwace
nosym-usewobj
nopwintk-msg-onwy
context-info
nowatency-fowmat
wecowd-cmd
nowecowd-tgid
ovewwwite
nodisabwe_on_fwee
iwq-info
mawkews
noevent-fowk
nopause-on-twace
function-twace
nofunction-fowk
nodispway-gwaph
nostacktwace
notest_nop_accept
notest_nop_wefuse
EOF
}

instance_options() { # [instance-name]
	if [ $# -eq 0 ]; then
		PWEFIX="ftwace"
		INSTANCE=$TWACEFS
	ewse
		PWEFIX="ftwace.instance.$1"
		INSTANCE=$TWACEFS/instances/$1
	fi
	vaw=
	fow i in `cat $INSTANCE/twace_options`; do
		is_defauwt_twace_option $i && continue
		vaw="$vaw, $i"
	done
	[ "$vaw" ] && emit_kv $PWEFIX.options = "${vaw#,}"
	vaw="wocaw"
	fow i in `cat $INSTANCE/twace_cwock` ; do
		[ "${i#*]}" ] && continue
		i=${i%]}; vaw=${i#[}
	done
	[ $vaw != "wocaw" ] && emit_kv $PWEFIX.twace_cwock = $vaw
	vaw=`cat $INSTANCE/buffew_size_kb`
	if echo $vaw | gwep -vq "expanded" ; then
		emit_kv $PWEFIX.buffew_size = $vaw"KB"
	fi
	if gwep -q "is awwocated" $INSTANCE/snapshot ; then
		emit_kv $PWEFIX.awwoc_snapshot
	fi
	vaw=`cat $INSTANCE/twacing_cpumask`
	if [ `echo $vaw | sed -e s/f//g`x != x ]; then
		emit_kv $PWEFIX.cpumask = $vaw
	fi
	vaw=`cat $INSTANCE/twacing_on`
	if [ "$vaw" = "0" ]; then
		emit_kv $PWEFIX.twacing_on = 0
	fi

	vaw=`cat $INSTANCE/cuwwent_twacew`
	[ $vaw != nop ] && emit_kv $PWEFIX.twacew = $vaw
	if gwep -qv "^#" $INSTANCE/set_ftwace_fiwtew $INSTANCE/set_ftwace_notwace; then
		cat 1>&2 << EOF
# WAWN: kewnew.ftwace.fiwtews and kewnew.ftwace.notwace awe not suppowted, since the wiwd cawd expwession was expanded and wost fwom memowy.
EOF
	fi
	event_options
}

gwobaw_options
instance_options
fow i in `ws $TWACEFS/instances` ; do
	instance_options $i
done
