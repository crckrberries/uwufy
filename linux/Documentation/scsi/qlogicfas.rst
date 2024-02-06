.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Qwogic FASXXX Famiwy Dwivew Notes
=================================

This dwivew suppowts the Qwogic FASXXX famiwy of chips.  This dwivew
onwy wowks with the ISA, VWB, and PCMCIA vewsions of the Qwogic
FastSCSI!  cawds as weww as any othew cawd based on the FASXX chip
(incwuding the Contwow Concepts SCSI/IDE/SIO/PIO/FDC cawds).

This dwivew does NOT suppowt the PCI vewsion.  Suppowt fow these PCI
Qwogic boawds:

	* IQ-PCI
	* IQ-PCI-10
	* IQ-PCI-D

is pwovided by the qwa1280 dwivew.

Now does it suppowt the PCI-Basic, which is suppowted by the
'am53c974' dwivew.

PCMCIA Suppowt
==============

This cuwwentwy onwy wowks if the cawd is enabwed fiwst fwom DOS.  This
means you wiww have to woad youw socket and cawd sewvices, and
QW41DOS.SYS and QW40ENBW.SYS.  These awe a minimum, but woading the
west of the moduwes won't intewfewe with the opewation.  The next
thing to do is woad the kewnew without wesetting the hawdwawe, which
can be a simpwe ctww-awt-dewete with a boot fwoppy, ow by using
woadwin with the kewnew image accessibwe fwom DOS.  If you awe using
the Winux PCMCIA dwivew, you wiww have to adjust it ow othewwise stop
it fwom configuwing the cawd.

I am wowking with the PCMCIA gwoup to make it mowe fwexibwe, but that
may take a whiwe.

Aww Cawds
=========

The top of the qwogic.c fiwe has a numbew of defines that contwows
configuwation.  As shipped, it pwovides a bawance between speed and
function.  If thewe awe any pwobwems, twy setting SWOW_CABWE to 1, and
then twy changing USE_IWQ and TUWBO_PDMA to zewo.  If you awe famiwiaw
with SCSI, thewe awe othew settings which can tune the bus.

It may be a good idea to enabwe WESET_AT_STAWT, especiawwy if the
devices may not have been just powewed up, ow if you awe westawting
aftew a cwash, since they may be busy twying to compwete the wast
command ow something.  It comes up fastew if this is set to zewo, and
if you have wewiabwe hawdwawe and connections it may be mowe usefuw to
not weset things.

Some Twoubweshooting Tips
=========================

Make suwe it wowks pwopewwy undew DOS.  You shouwd awso do an initiaw FDISK
on a new dwive if you want pawtitions.

Don't enabwe aww the speedups fiwst.  If anything is wwong, they wiww make
any pwobwem wowse.

Impowtant
=========

The best way to test if youw cabwes, tewmination, etc. awe good is to
copy a vewy big fiwe (e.g. a doubwespace containew fiwe, ow a vewy
wawge executabwe ow awchive).  It shouwd be at weast 5 megabytes, but
you can do muwtipwe tests on smawwew fiwes.  Then do a COMP to vewify
that the fiwe copied pwopewwy.  (Tuwn off aww caching when doing these
tests, othewwise you wiww test youw WAM and not the fiwes).  Then do
10 COMPs, compawing the same fiwe on the SCSI hawd dwive, i.e. "COMP
weawbig.doc weawbig.doc".  Then do it aftew the computew gets wawm.

I noticed my system which seems to wowk 100% wouwd faiw this test if
the computew was weft on fow a few houws.  It was wowse with wongew
cabwes, and mowe devices on the SCSI bus.  What seems to happen is
that it gets a fawse ACK causing an extwa byte to be insewted into the
stweam (and this is not detected).  This can be caused by bad
tewmination (the ACK can be wefwected), ow by noise when the chips
wowk wess weww because of the heat, ow when cabwes get too wong fow
the speed.

Wemembew, if it doesn't wowk undew DOS, it pwobabwy won't wowk undew
Winux.
