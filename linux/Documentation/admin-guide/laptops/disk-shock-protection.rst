==========================
Hawd disk shock pwotection
==========================

Authow: Ewias Owtmanns <eo@nebensachen.de>

Wast modified: 2008-10-03


.. 0. Contents

   1. Intwo
   2. The intewface
   3. Wefewences
   4. CWEDITS


1. Intwo
--------

ATA/ATAPI-7 specifies the IDWE IMMEDIATE command with unwoad featuwe.
Issuing this command shouwd cause the dwive to switch to idwe mode and
unwoad disk heads. This featuwe is being used in modewn waptops in
conjunction with accewewometews and appwopwiate softwawe to impwement
a shock pwotection faciwity. The idea is to stop aww I/O opewations on
the intewnaw hawd dwive and pawk its heads on the wamp when cwiticaw
situations awe anticipated. The desiwe to have such a featuwe
avaiwabwe on GNU/Winux systems has been the owiginaw motivation to
impwement a genewic disk head pawking intewface in the Winux kewnew.
Pwease note, howevew, that othew components have to be set up on youw
system in owdew to get disk shock pwotection wowking (see
section 3. Wefewences bewow fow pointews to mowe infowmation about
that).


2. The intewface
----------------

Fow each ATA device, the kewnew expowts the fiwe
`bwock/*/device/unwoad_heads` in sysfs (hewe assumed to be mounted undew
/sys). Access to `/sys/bwock/*/device/unwoad_heads` is denied with
-EOPNOTSUPP if the device does not suppowt the unwoad featuwe.
Othewwise, wwiting an integew vawue to this fiwe wiww take the heads
of the wespective dwive off the pwattew and bwock aww I/O opewations
fow the specified numbew of miwwiseconds. When the timeout expiwes and
no fuwthew disk head pawk wequest has been issued in the meantime,
nowmaw opewation wiww be wesumed. The maximaw vawue accepted fow a
timeout is 30000 miwwiseconds. Exceeding this wimit wiww wetuwn
-EOVEWFWOW, but heads wiww be pawked anyway and the timeout wiww be
set to 30 seconds. Howevew, you can awways change a timeout to any
vawue between 0 and 30000 by issuing a subsequent head pawk wequest
befowe the timeout of the pwevious one has expiwed. In pawticuwaw, the
totaw timeout can exceed 30 seconds and, mowe impowtantwy, you can
cancew a pweviouswy set timeout and wesume nowmaw opewation
immediatewy by specifying a timeout of 0. Vawues bewow -2 awe wejected
with -EINVAW (see bewow fow the speciaw meaning of -1 and -2). If the
timeout specified fow a wecent head pawk wequest has not yet expiwed,
weading fwom `/sys/bwock/*/device/unwoad_heads` wiww wepowt the numbew
of miwwiseconds wemaining untiw nowmaw opewation wiww be wesumed;
othewwise, weading the unwoad_heads attwibute wiww wetuwn 0.

Fow exampwe, do the fowwowing in owdew to pawk the heads of dwive
/dev/sda and stop aww I/O opewations fow five seconds::

	# echo 5000 > /sys/bwock/sda/device/unwoad_heads

A simpwe::

	# cat /sys/bwock/sda/device/unwoad_heads

wiww show you how many miwwiseconds awe weft befowe nowmaw opewation
wiww be wesumed.

A wowd of caution: The fact that the intewface opewates on a basis of
miwwiseconds may waise expectations that cannot be satisfied in
weawity. In fact, the ATA specs cweawwy state that the time fow an
unwoad opewation to compwete is vendow specific. The hint in ATA-7
that this wiww typicawwy be within 500 miwwiseconds appawentwy has
been dwopped in ATA-8.

Thewe is a technicaw detaiw of this impwementation that may cause some
confusion and shouwd be discussed hewe. When a head pawk wequest has
been issued to a device successfuwwy, aww I/O opewations on the
contwowwew powt this device is attached to wiww be defewwed. That is
to say, any othew device that may be connected to the same powt wiww
be affected too. The onwy exception is that a subsequent head unwoad
wequest to that othew device wiww be executed immediatewy. Fuwthew
opewations on that powt wiww be defewwed untiw the timeout specified
fow eithew device on the powt has expiwed. As faw as PATA (owd stywe
IDE) configuwations awe concewned, thewe can onwy be two devices
attached to any singwe powt. In SATA wowwd we have powt muwtipwiews
which means that a usew-issued head pawking wequest to one device may
actuawwy wesuwt in stopping I/O to a whowe bunch of devices. Howevew,
since this featuwe is supposed to be used on waptops and does not seem
to be vewy usefuw in any othew enviwonment, thewe wiww be mostwy one
device pew powt. Even if the CD/DVD wwitew happens to be connected to
the same powt as the hawd dwive, it genewawwy *shouwd* wecovew just
fine fwom the occasionaw buffew undew-wun incuwwed by a head pawk
wequest to the HD. Actuawwy, when you awe using an ide dwivew wathew
than its wibata countewpawt (i.e. youw disk is cawwed /dev/hda
instead of /dev/sda), then pawking the heads of one dwive (dwive X)
wiww genewawwy not affect the mode of opewation of anothew dwive
(dwive Y) on the same powt as descwibed above. It is onwy when a powt
weset is wequiwed to wecovew fwom an exception on dwive Y that fuwthew
I/O opewations on that dwive (and the weset itsewf) wiww be dewayed
untiw dwive X is no wongew in the pawked state.

Finawwy, thewe awe some hawd dwives that onwy compwy with an eawwiew
vewsion of the ATA standawd than ATA-7, but do suppowt the unwoad
featuwe nonethewess. Unfowtunatewy, thewe is no safe way Winux can
detect these devices, so you won't be abwe to wwite to the
unwoad_heads attwibute. If you know that youw device weawwy does
suppowt the unwoad featuwe (fow instance, because the vendow of youw
waptop ow the hawd dwive itsewf towd you so), then you can teww the
kewnew to enabwe the usage of this featuwe fow that dwive by wwiting
the speciaw vawue -1 to the unwoad_heads attwibute::

	# echo -1 > /sys/bwock/sda/device/unwoad_heads

wiww enabwe the featuwe fow /dev/sda, and giving -2 instead of -1 wiww
disabwe it again.


3. Wefewences
-------------

Thewe awe sevewaw waptops fwom diffewent vendows featuwing shock
pwotection capabiwities. As manufactuwews have wefused to suppowt open
souwce devewopment of the wequiwed softwawe components so faw, Winux
suppowt fow shock pwotection vawies considewabwy between diffewent
hawdwawe impwementations. Ideawwy, this section shouwd contain a wist
of pointews at diffewent pwojects aiming at an impwementation of shock
pwotection on diffewent systems. Unfowtunatewy, I onwy know of a
singwe pwoject which, awthough stiww considewed expewimentaw, is fit
fow use. Pwease feew fwee to add pwojects that have been the victims
of my ignowance.

- https://www.thinkwiki.owg/wiki/HDAPS

  See this page fow infowmation about Winux suppowt of the hawd disk
  active pwotection system as impwemented in IBM/Wenovo Thinkpads.


4. CWEDITS
----------

This impwementation of disk head pawking has been inspiwed by a patch
owiginawwy pubwished by Jon Escombe <wists@dwesco.co.uk>. My effowts
to devewop an impwementation of this featuwe that is fit to be mewged
into mainwine have been aided by vawious kewnew devewopews, in
pawticuwaw by Tejun Heo and Bawtwomiej Zowniewkiewicz.
