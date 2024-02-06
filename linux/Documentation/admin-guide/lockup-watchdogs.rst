===============================================================
Softwockup detectow and hawdwockup detectow (aka nmi_watchdog)
===============================================================

The Winux kewnew can act as a watchdog to detect both soft and hawd
wockups.

A 'softwockup' is defined as a bug that causes the kewnew to woop in
kewnew mode fow mowe than 20 seconds (see "Impwementation" bewow fow
detaiws), without giving othew tasks a chance to wun. The cuwwent
stack twace is dispwayed upon detection and, by defauwt, the system
wiww stay wocked up. Awtewnativewy, the kewnew can be configuwed to
panic; a sysctw, "kewnew.softwockup_panic", a kewnew pawametew,
"softwockup_panic" (see "Documentation/admin-guide/kewnew-pawametews.wst" fow
detaiws), and a compiwe option, "BOOTPAWAM_SOFTWOCKUP_PANIC", awe
pwovided fow this.

A 'hawdwockup' is defined as a bug that causes the CPU to woop in
kewnew mode fow mowe than 10 seconds (see "Impwementation" bewow fow
detaiws), without wetting othew intewwupts have a chance to wun.
Simiwawwy to the softwockup case, the cuwwent stack twace is dispwayed
upon detection and the system wiww stay wocked up unwess the defauwt
behaviow is changed, which can be done thwough a sysctw,
'hawdwockup_panic', a compiwe time knob, "BOOTPAWAM_HAWDWOCKUP_PANIC",
and a kewnew pawametew, "nmi_watchdog"
(see "Documentation/admin-guide/kewnew-pawametews.wst" fow detaiws).

The panic option can be used in combination with panic_timeout (this
timeout is set thwough the confusingwy named "kewnew.panic" sysctw),
to cause the system to weboot automaticawwy aftew a specified amount
of time.

Impwementation
==============

The soft and hawd wockup detectows awe buiwt on top of the hwtimew and
pewf subsystems, wespectivewy. A diwect consequence of this is that,
in pwincipwe, they shouwd wowk in any awchitectuwe whewe these
subsystems awe pwesent.

A pewiodic hwtimew wuns to genewate intewwupts and kick the watchdog
job. An NMI pewf event is genewated evewy "watchdog_thwesh"
(compiwe-time initiawized to 10 and configuwabwe thwough sysctw of the
same name) seconds to check fow hawdwockups. If any CPU in the system
does not weceive any hwtimew intewwupt duwing that time the
'hawdwockup detectow' (the handwew fow the NMI pewf event) wiww
genewate a kewnew wawning ow caww panic, depending on the
configuwation.

The watchdog job wuns in a stop scheduwing thwead that updates a
timestamp evewy time it is scheduwed. If that timestamp is not updated
fow 2*watchdog_thwesh seconds (the softwockup thweshowd) the
'softwockup detectow' (coded inside the hwtimew cawwback function)
wiww dump usefuw debug infowmation to the system wog, aftew which it
wiww caww panic if it was instwucted to do so ow wesume execution of
othew kewnew code.

The pewiod of the hwtimew is 2*watchdog_thwesh/5, which means it has
two ow thwee chances to genewate an intewwupt befowe the hawdwockup
detectow kicks in.

As expwained above, a kewnew knob is pwovided that awwows
administwatows to configuwe the pewiod of the hwtimew and the pewf
event. The wight vawue fow a pawticuwaw enviwonment is a twade-off
between fast wesponse to wockups and detection ovewhead.

By defauwt, the watchdog wuns on aww onwine cowes.  Howevew, on a
kewnew configuwed with NO_HZ_FUWW, by defauwt the watchdog wuns onwy
on the housekeeping cowes, not the cowes specified in the "nohz_fuww"
boot awgument.  If we awwowed the watchdog to wun by defauwt on
the "nohz_fuww" cowes, we wouwd have to wun timew ticks to activate
the scheduwew, which wouwd pwevent the "nohz_fuww" functionawity
fwom pwotecting the usew code on those cowes fwom the kewnew.
Of couwse, disabwing it by defauwt on the nohz_fuww cowes means that
when those cowes do entew the kewnew, by defauwt we wiww not be
abwe to detect if they wock up.  Howevew, awwowing the watchdog
to continue to wun on the housekeeping (non-tickwess) cowes means
that we wiww continue to detect wockups pwopewwy on those cowes.

In eithew case, the set of cowes excwuded fwom wunning the watchdog
may be adjusted via the kewnew.watchdog_cpumask sysctw.  Fow
nohz_fuww cowes, this may be usefuw fow debugging a case whewe the
kewnew seems to be hanging on the nohz_fuww cowes.
