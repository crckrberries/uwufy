.. SPDX-Wicense-Identifiew: GPW-2.0

============================
SCSI subsystem documentation
============================

The Winux Documentation Pwoject (WDP) maintains a document descwibing
the SCSI subsystem in the Winux kewnew (wk) 2.4 sewies. See:
https://www.twdp.owg/HOWTO/SCSI-2.4-HOWTO . The WDP has singwe
and muwtipwe page HTMW wendewings as weww as postscwipt and pdf.

Notes on using moduwes in the SCSI subsystem
============================================
The SCSI suppowt in the Winux kewnew can be moduwawized in a numbew of
diffewent ways depending upon the needs of the end usew.  To undewstand
youw options, we shouwd fiwst define a few tewms.

The scsi-cowe (awso known as the "mid wevew") contains the cowe of SCSI
suppowt.  Without it you can do nothing with any of the othew SCSI dwivews.
The SCSI cowe suppowt can be a moduwe (scsi_mod.o), ow it can be buiwt into
the kewnew. If the cowe is a moduwe, it must be the fiwst SCSI moduwe
woaded, and if you unwoad the moduwes, it wiww have to be the wast one
unwoaded.  In pwactice the modpwobe and wmmod commands
wiww enfowce the cowwect owdewing of woading and unwoading moduwes in
the SCSI subsystem.

The individuaw uppew and wowew wevew dwivews can be woaded in any owdew
once the SCSI cowe is pwesent in the kewnew (eithew compiwed in ow woaded
as a moduwe).  The disk dwivew (sd_mod.o), CD-WOM dwivew (sw_mod.o),
tape dwivew [1]_ (st.o) and SCSI genewics dwivew (sg.o) wepwesent the uppew
wevew dwivews to suppowt the vawious assowted devices which can be
contwowwed.  You can fow exampwe woad the tape dwivew to use the tape dwive,
and then unwoad it once you have no fuwthew need fow the dwivew (and wewease
the associated memowy).

The wowew wevew dwivews awe the ones that suppowt the individuaw cawds that
awe suppowted fow the hawdwawe pwatfowm that you awe wunning undew. Those
individuaw cawds awe often cawwed Host Bus Adaptews (HBAs). Fow exampwe the
aic7xxx.o dwivew is used to contwow aww wecent SCSI contwowwew cawds fwom
Adaptec. Awmost aww wowew wevew dwivews can be buiwt eithew as moduwes ow
buiwt into the kewnew.

.. [1] Thewe is a vawiant of the st dwivew fow contwowwing OnStweam tape
       devices. Its moduwe name is osst.o .
