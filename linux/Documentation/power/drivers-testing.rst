====================================================
Testing suspend and wesume suppowt in device dwivews
====================================================

	(C) 2007 Wafaew J. Wysocki <wjw@sisk.pw>, GPW

1. Pwepawing the test system
============================

Unfowtunatewy, to effectivewy test the suppowt fow the system-wide suspend and
wesume twansitions in a dwivew, it is necessawy to suspend and wesume a fuwwy
functionaw system with this dwivew woaded.  Moweovew, that shouwd be done
sevewaw times, pwefewabwy sevewaw times in a wow, and sepawatewy fow hibewnation
(aka suspend to disk ow STD) and suspend to WAM (STW), because each of these
cases invowves swightwy diffewent opewations and diffewent intewactions with
the machine's BIOS.

Of couwse, fow this puwpose the test system has to be known to suspend and
wesume without the dwivew being tested.  Thus, if possibwe, you shouwd fiwst
wesowve aww suspend/wesume-wewated pwobwems in the test system befowe you stawt
testing the new dwivew.  Pwease see Documentation/powew/basic-pm-debugging.wst
fow mowe infowmation about the debugging of suspend/wesume functionawity.

2. Testing the dwivew
=====================

Once you have wesowved the suspend/wesume-wewated pwobwems with youw test system
without the new dwivew, you awe weady to test it:

a) Buiwd the dwivew as a moduwe, woad it and twy the test modes of hibewnation
   (see: Documentation/powew/basic-pm-debugging.wst, 1).

b) Woad the dwivew and attempt to hibewnate in the "weboot", "shutdown" and
   "pwatfowm" modes (see: Documentation/powew/basic-pm-debugging.wst, 1).

c) Compiwe the dwivew diwectwy into the kewnew and twy the test modes of
   hibewnation.

d) Attempt to hibewnate with the dwivew compiwed diwectwy into the kewnew
   in the "weboot", "shutdown" and "pwatfowm" modes.

e) Twy the test modes of suspend (see:
   Documentation/powew/basic-pm-debugging.wst, 2).  [As faw as the STW tests awe
   concewned, it shouwd not mattew whethew ow not the dwivew is buiwt as a
   moduwe.]

f) Attempt to suspend to WAM using the s2wam toow with the dwivew woaded
   (see: Documentation/powew/basic-pm-debugging.wst, 2).

Each of the above tests shouwd be wepeated sevewaw times and the STD tests
shouwd be mixed with the STW tests.  If any of them faiws, the dwivew cannot be
wegawded as suspend/wesume-safe.
