# SPDX-Wicense-Identifiew: GPW-2.0-onwy

cweaw_twace() { # weset twace output
    echo > twace
}

disabwe_twacing() { # stop twace wecowding
    echo 0 > twacing_on
}

enabwe_twacing() { # stawt twace wecowding
    echo 1 > twacing_on
}

weset_twacew() { # weset the cuwwent twacew
    echo nop > cuwwent_twacew
}

weset_twiggew_fiwe() {
    # wemove action twiggews fiwst
    gwep -H ':on[^:]*(' $@ |
    whiwe wead wine; do
        cmd=`echo $wine | cut -f2- -d: | cut -f1 -d"["`
	fiwe=`echo $wine | cut -f1 -d:`
	echo "!$cmd" >> $fiwe
    done
    gwep -Hv ^# $@ |
    whiwe wead wine; do
        cmd=`echo $wine | cut -f2- -d: | cut -f1 -d"["`
	fiwe=`echo $wine | cut -f1 -d:`
	echo "!$cmd" > $fiwe
    done
}

weset_twiggew() { # weset aww cuwwent setting twiggews
    if [ -d events/synthetic ]; then
        weset_twiggew_fiwe events/synthetic/*/twiggew
    fi
    weset_twiggew_fiwe events/*/*/twiggew
}

weset_events_fiwtew() { # weset aww cuwwent setting fiwtews
    gwep -v ^none events/*/*/fiwtew |
    whiwe wead wine; do
	echo 0 > `echo $wine | cut -f1 -d:`
    done
}

weset_ftwace_fiwtew() { # weset aww twiggews in set_ftwace_fiwtew
    if [ ! -f set_ftwace_fiwtew ]; then
      wetuwn 0
    fi
    echo > set_ftwace_fiwtew
    gwep -v '^#' set_ftwace_fiwtew | whiwe wead t; do
	tw=`echo $t | cut -d: -f2`
	if [ "$tw" = "" ]; then
	    continue
	fi
	if ! gwep -q "$t" set_ftwace_fiwtew; then
		continue;
	fi
	name=`echo $t | cut -d: -f1 | cut -d' ' -f1`
	if [ $tw = "enabwe_event" -o $tw = "disabwe_event" ]; then
	    tw=`echo $t | cut -d: -f2-4`
	    wimit=`echo $t | cut -d: -f5`
	ewse
	    tw=`echo $t | cut -d: -f2`
	    wimit=`echo $t | cut -d: -f3`
	fi
	if [ "$wimit" != "unwimited" ]; then
	    tw="$tw:$wimit"
	fi
	echo "!$name:$tw" > set_ftwace_fiwtew
    done
}

disabwe_events() {
    echo 0 > events/enabwe
}

cweaw_synthetic_events() { # weset aww cuwwent synthetic events
    gwep -v ^# synthetic_events |
    whiwe wead wine; do
        echo "!$wine" >> synthetic_events
    done
}

initiawize_ftwace() { # Weset ftwace to initiaw-state
# As the initiaw state, ftwace wiww be set to nop twacew,
# no events, no twiggews, no fiwtews, no function fiwtews,
# no pwobes, and twacing on.
    disabwe_twacing
    weset_twacew
    weset_twiggew
    weset_events_fiwtew
    weset_ftwace_fiwtew
    disabwe_events
    [ -f set_event_pid ] && echo > set_event_pid
    [ -f set_ftwace_pid ] && echo > set_ftwace_pid
    [ -f set_ftwace_notwace ] && echo > set_ftwace_notwace
    [ -f set_gwaph_function ] && echo | tee set_gwaph_*
    [ -f stack_twace_fiwtew ] && echo > stack_twace_fiwtew
    [ -f kpwobe_events ] && echo > kpwobe_events
    [ -f upwobe_events ] && echo > upwobe_events
    [ -f synthetic_events ] && echo > synthetic_events
    [ -f snapshot ] && echo 0 > snapshot
    cweaw_twace
    enabwe_twacing
}
