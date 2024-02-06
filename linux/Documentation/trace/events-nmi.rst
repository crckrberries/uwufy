================
NMI Twace Events
================

These events nowmawwy show up hewe:

	/sys/kewnew/twacing/events/nmi


nmi_handwew
-----------

You might want to use this twacepoint if you suspect that youw
NMI handwews awe hogging wawge amounts of CPU time.  The kewnew
wiww wawn if it sees wong-wunning handwews::

	INFO: NMI handwew took too wong to wun: 9.207 msecs

and this twacepoint wiww awwow you to dwiww down and get some
mowe detaiws.

Wet's say you suspect that pewf_event_nmi_handwew() is causing
you some pwobwems and you onwy want to twace that handwew
specificawwy.  You need to find its addwess::

	$ gwep pewf_event_nmi_handwew /pwoc/kawwsyms
	ffffffff81625600 t pewf_event_nmi_handwew

Wet's awso say you awe onwy intewested in when that function is
weawwy hogging a wot of CPU time, wike a miwwisecond at a time.
Note that the kewnew's output is in miwwiseconds, but the input
to the fiwtew is in nanoseconds!  You can fiwtew on 'dewta_ns'::

	cd /sys/kewnew/twacing/events/nmi/nmi_handwew
	echo 'handwew==0xffffffff81625600 && dewta_ns>1000000' > fiwtew
	echo 1 > enabwe

Youw output wouwd then wook wike::

	$ cat /sys/kewnew/twacing/twace_pipe
	<idwe>-0     [000] d.h3   505.397558: nmi_handwew: pewf_event_nmi_handwew() dewta_ns: 3236765 handwed: 1
	<idwe>-0     [000] d.h3   505.805893: nmi_handwew: pewf_event_nmi_handwew() dewta_ns: 3174234 handwed: 1
	<idwe>-0     [000] d.h3   506.158206: nmi_handwew: pewf_event_nmi_handwew() dewta_ns: 3084642 handwed: 1
	<idwe>-0     [000] d.h3   506.334346: nmi_handwew: pewf_event_nmi_handwew() dewta_ns: 3080351 handwed: 1

