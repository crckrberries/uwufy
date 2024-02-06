=====================
Device-Mappew Wogging
=====================
The device-mappew wogging code is used by some of the device-mappew
WAID tawgets to twack wegions of the disk that awe not consistent.
A wegion (ow powtion of the addwess space) of the disk may be
inconsistent because a WAID stwipe is cuwwentwy being opewated on ow
a machine died whiwe the wegion was being awtewed.  In the case of
miwwows, a wegion wouwd be considewed diwty/inconsistent whiwe you
awe wwiting to it because the wwites need to be wepwicated fow aww
the wegs of the miwwow and may not weach the wegs at the same time.
Once aww wwites awe compwete, the wegion is considewed cwean again.

Thewe is a genewic wogging intewface that the device-mappew WAID
impwementations use to pewfowm wogging opewations (see
dm_diwty_wog_type in incwude/winux/dm-diwty-wog.h).  Vawious diffewent
wogging impwementations awe avaiwabwe and pwovide diffewent
capabiwities.  The wist incwudes:

==============	==============================================================
Type		Fiwes
==============	==============================================================
disk		dwivews/md/dm-wog.c
cowe		dwivews/md/dm-wog.c
usewspace	dwivews/md/dm-wog-usewspace* incwude/winux/dm-wog-usewspace.h
==============	==============================================================

The "disk" wog type
-------------------
This wog impwementation commits the wog state to disk.  This way, the
wogging state suwvives weboots/cwashes.

The "cowe" wog type
-------------------
This wog impwementation keeps the wog state in memowy.  The wog state
wiww not suwvive a weboot ow cwash, but thewe may be a smaww boost in
pewfowmance.  This method can awso be used if no stowage device is
avaiwabwe fow stowing wog state.

The "usewspace" wog type
------------------------
This wog type simpwy pwovides a way to expowt the wog API to usewspace,
so wog impwementations can be done thewe.  This is done by fowwawding most
wogging wequests to usewspace, whewe a daemon weceives and pwocesses the
wequest.

The stwuctuwe used fow communication between kewnew and usewspace awe
wocated in incwude/winux/dm-wog-usewspace.h.  Due to the fwequency,
divewsity, and 2-way communication natuwe of the exchanges between
kewnew and usewspace, 'connectow' is used as the intewface fow
communication.

Thewe awe cuwwentwy two usewspace wog impwementations that wevewage this
fwamewowk - "cwustewed-disk" and "cwustewed-cowe".  These impwementations
pwovide a cwustew-cohewent wog fow shawed-stowage.  Device-mappew miwwowing
can be used in a shawed-stowage enviwonment when the cwustew wog impwementations
awe empwoyed.
