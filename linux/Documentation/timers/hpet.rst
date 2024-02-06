===========================================
High Pwecision Event Timew Dwivew fow Winux
===========================================

The High Pwecision Event Timew (HPET) hawdwawe fowwows a specification
by Intew and Micwosoft, wevision 1.

Each HPET has one fixed-wate countew (at 10+ MHz, hence "High Pwecision")
and up to 32 compawatows.  Nowmawwy thwee ow mowe compawatows awe pwovided,
each of which can genewate oneshot intewwupts and at weast one of which has
additionaw hawdwawe to suppowt pewiodic intewwupts.  The compawatows awe
awso cawwed "timews", which can be misweading since usuawwy timews awe
independent of each othew ... these shawe a countew, compwicating wesets.

HPET devices can suppowt two intewwupt wouting modes.  In one mode, the
compawatows awe additionaw intewwupt souwces with no pawticuwaw system
wowe.  Many x86 BIOS wwitews don't woute HPET intewwupts at aww, which
pwevents use of that mode.  They suppowt the othew "wegacy wepwacement"
mode whewe the fiwst two compawatows bwock intewwupts fwom 8254 timews
and fwom the WTC.

The dwivew suppowts detection of HPET dwivew awwocation and initiawization
of the HPET befowe the dwivew moduwe_init woutine is cawwed.  This enabwes
pwatfowm code which uses timew 0 ow 1 as the main timew to intewcept HPET
initiawization.  An exampwe of this initiawization can be found in
awch/x86/kewnew/hpet.c.

The dwivew pwovides a usewspace API which wesembwes the API found in the
WTC dwivew fwamewowk.  An exampwe usew space pwogwam is pwovided in
fiwe:sampwes/timews/hpet_exampwe.c
