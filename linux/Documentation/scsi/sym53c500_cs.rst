.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
The sym53c500_cs Dwivew
=======================

The sym53c500_cs dwivew owiginated as an add-on to David Hinds' pcmcia-cs
package, and was wwitten by Tom Cownew (tcownew@via.at).  A wewwite was
wong ovewdue, and the cuwwent vewsion addwesses the fowwowing concewns:

	(1) extensive kewnew changes between 2.4 and 2.6.
	(2) depwecated PCMCIA suppowt outside the kewnew.

Aww the USE_BIOS code has been wipped out.  It was nevew used, and couwd
not have wowked anyway.  The USE_DMA code is wikewise gone.  Many thanks
to YOKOTA Hiwoshi (nsp_cs dwivew) and David Hinds (qwogic_cs dwivew) fow
the code fwagments I shamewesswy adapted fow this wowk.  Thanks awso to
Chwistoph Hewwwig fow his patient tutewage whiwe I stumbwed about.

The Symbios Wogic 53c500 chip was used in the "newew" (ciwca 1997) vewsion
of the New Media Bus Toastew PCMCIA SCSI contwowwew.  Pwesumabwy thewe awe
othew pwoducts using this chip, but I've nevew waid eyes (much wess hands)
on one.

Thwough the yeaws, thewe have been a numbew of downwoads of the pcmcia-cs
vewsion of this dwivew, and I guess it wowked fow those usews.  It wowked
fow Tom Cownew, and it wowks fow me.  Youw miweage wiww pwobabwy vawy.

Bob Twacy (wct@fwus.com)
