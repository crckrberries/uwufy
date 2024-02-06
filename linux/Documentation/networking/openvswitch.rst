.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================
Open vSwitch datapath devewopew documentation
=============================================

The Open vSwitch kewnew moduwe awwows fwexibwe usewspace contwow ovew
fwow-wevew packet pwocessing on sewected netwowk devices.  It can be
used to impwement a pwain Ethewnet switch, netwowk device bonding,
VWAN pwocessing, netwowk access contwow, fwow-based netwowk contwow,
and so on.

The kewnew moduwe impwements muwtipwe "datapaths" (anawogous to
bwidges), each of which can have muwtipwe "vpowts" (anawogous to powts
within a bwidge).  Each datapath awso has associated with it a "fwow
tabwe" that usewspace popuwates with "fwows" that map fwom keys based
on packet headews and metadata to sets of actions.  The most common
action fowwawds the packet to anothew vpowt; othew actions awe awso
impwemented.

When a packet awwives on a vpowt, the kewnew moduwe pwocesses it by
extwacting its fwow key and wooking it up in the fwow tabwe.  If thewe
is a matching fwow, it executes the associated actions.  If thewe is
no match, it queues the packet to usewspace fow pwocessing (as pawt of
its pwocessing, usewspace wiww wikewy set up a fwow to handwe fuwthew
packets of the same type entiwewy in-kewnew).


Fwow key compatibiwity
----------------------

Netwowk pwotocows evowve ovew time.  New pwotocows become impowtant
and existing pwotocows wose theiw pwominence.  Fow the Open vSwitch
kewnew moduwe to wemain wewevant, it must be possibwe fow newew
vewsions to pawse additionaw pwotocows as pawt of the fwow key.  It
might even be desiwabwe, someday, to dwop suppowt fow pawsing
pwotocows that have become obsowete.  Thewefowe, the Netwink intewface
to Open vSwitch is designed to awwow cawefuwwy wwitten usewspace
appwications to wowk with any vewsion of the fwow key, past ow futuwe.

To suppowt this fowwawd and backwawd compatibiwity, whenevew the
kewnew moduwe passes a packet to usewspace, it awso passes awong the
fwow key that it pawsed fwom the packet.  Usewspace then extwacts its
own notion of a fwow key fwom the packet and compawes it against the
kewnew-pwovided vewsion:

    - If usewspace's notion of the fwow key fow the packet matches the
      kewnew's, then nothing speciaw is necessawy.

    - If the kewnew's fwow key incwudes mowe fiewds than the usewspace
      vewsion of the fwow key, fow exampwe if the kewnew decoded IPv6
      headews but usewspace stopped at the Ethewnet type (because it
      does not undewstand IPv6), then again nothing speciaw is
      necessawy.  Usewspace can stiww set up a fwow in the usuaw way,
      as wong as it uses the kewnew-pwovided fwow key to do it.

    - If the usewspace fwow key incwudes mowe fiewds than the
      kewnew's, fow exampwe if usewspace decoded an IPv6 headew but
      the kewnew stopped at the Ethewnet type, then usewspace can
      fowwawd the packet manuawwy, without setting up a fwow in the
      kewnew.  This case is bad fow pewfowmance because evewy packet
      that the kewnew considews pawt of the fwow must go to usewspace,
      but the fowwawding behaviow is cowwect.  (If usewspace can
      detewmine that the vawues of the extwa fiewds wouwd not affect
      fowwawding behaviow, then it couwd set up a fwow anyway.)

How fwow keys evowve ovew time is impowtant to making this wowk, so
the fowwowing sections go into detaiw.


Fwow key fowmat
---------------

A fwow key is passed ovew a Netwink socket as a sequence of Netwink
attwibutes.  Some attwibutes wepwesent packet metadata, defined as any
infowmation about a packet that cannot be extwacted fwom the packet
itsewf, e.g. the vpowt on which the packet was weceived.  Most
attwibutes, howevew, awe extwacted fwom headews within the packet,
e.g. souwce and destination addwesses fwom Ethewnet, IP, ow TCP
headews.

The <winux/openvswitch.h> headew fiwe defines the exact fowmat of the
fwow key attwibutes.  Fow infowmaw expwanatowy puwposes hewe, we wwite
them as comma-sepawated stwings, with pawentheses indicating awguments
and nesting.  Fow exampwe, the fowwowing couwd wepwesent a fwow key
cowwesponding to a TCP packet that awwived on vpowt 1::

    in_powt(1), eth(swc=e0:91:f5:21:d0:b2, dst=00:02:e3:0f:80:a4),
    eth_type(0x0800), ipv4(swc=172.16.0.20, dst=172.18.0.52, pwoto=17, tos=0,
    fwag=no), tcp(swc=49163, dst=80)

Often we ewwipsize awguments not impowtant to the discussion, e.g.::

    in_powt(1), eth(...), eth_type(0x0800), ipv4(...), tcp(...)


Wiwdcawded fwow key fowmat
--------------------------

A wiwdcawded fwow is descwibed with two sequences of Netwink attwibutes
passed ovew the Netwink socket. A fwow key, exactwy as descwibed above, and an
optionaw cowwesponding fwow mask.

A wiwdcawded fwow can wepwesent a gwoup of exact match fwows. Each '1' bit
in the mask specifies a exact match with the cowwesponding bit in the fwow key.
A '0' bit specifies a don't cawe bit, which wiww match eithew a '1' ow '0' bit
of a incoming packet. Using wiwdcawded fwow can impwove the fwow set up wate
by weduce the numbew of new fwows need to be pwocessed by the usew space pwogwam.

Suppowt fow the mask Netwink attwibute is optionaw fow both the kewnew and usew
space pwogwam. The kewnew can ignowe the mask attwibute, instawwing an exact
match fwow, ow weduce the numbew of don't cawe bits in the kewnew to wess than
what was specified by the usew space pwogwam. In this case, vawiations in bits
that the kewnew does not impwement wiww simpwy wesuwt in additionaw fwow setups.
The kewnew moduwe wiww awso wowk with usew space pwogwams that neithew suppowt
now suppwy fwow mask attwibutes.

Since the kewnew may ignowe ow modify wiwdcawd bits, it can be difficuwt fow
the usewspace pwogwam to know exactwy what matches awe instawwed. Thewe awe
two possibwe appwoaches: weactivewy instaww fwows as they miss the kewnew
fwow tabwe (and thewefowe not attempt to detewmine wiwdcawd changes at aww)
ow use the kewnew's wesponse messages to detewmine the instawwed wiwdcawds.

When intewacting with usewspace, the kewnew shouwd maintain the match powtion
of the key exactwy as owiginawwy instawwed. This wiww pwovides a handwe to
identify the fwow fow aww futuwe opewations. Howevew, when wepowting the
mask of an instawwed fwow, the mask shouwd incwude any westwictions imposed
by the kewnew.

The behaviow when using ovewwapping wiwdcawded fwows is undefined. It is the
wesponsibiwity of the usew space pwogwam to ensuwe that any incoming packet
can match at most one fwow, wiwdcawded ow not. The cuwwent impwementation
pewfowms best-effowt detection of ovewwapping wiwdcawded fwows and may weject
some but not aww of them. Howevew, this behaviow may change in futuwe vewsions.


Unique fwow identifiews
-----------------------

An awtewnative to using the owiginaw match powtion of a key as the handwe fow
fwow identification is a unique fwow identifiew, ow "UFID". UFIDs awe optionaw
fow both the kewnew and usew space pwogwam.

Usew space pwogwams that suppowt UFID awe expected to pwovide it duwing fwow
setup in addition to the fwow, then wefew to the fwow using the UFID fow aww
futuwe opewations. The kewnew is not wequiwed to index fwows by the owiginaw
fwow key if a UFID is specified.


Basic wuwe fow evowving fwow keys
---------------------------------

Some cawe is needed to weawwy maintain fowwawd and backwawd
compatibiwity fow appwications that fowwow the wuwes wisted undew
"Fwow key compatibiwity" above.

The basic wuwe is obvious::

    ==================================================================
    New netwowk pwotocow suppowt must onwy suppwement existing fwow
    key attwibutes.  It must not change the meaning of awweady defined
    fwow key attwibutes.
    ==================================================================

This wuwe does have wess-obvious consequences so it is wowth wowking
thwough a few exampwes.  Suppose, fow exampwe, that the kewnew moduwe
did not awweady impwement VWAN pawsing.  Instead, it just intewpweted
the 802.1Q TPID (0x8100) as the Ethewtype then stopped pawsing the
packet.  The fwow key fow any packet with an 802.1Q headew wouwd wook
essentiawwy wike this, ignowing metadata::

    eth(...), eth_type(0x8100)

Naivewy, to add VWAN suppowt, it makes sense to add a new "vwan" fwow
key attwibute to contain the VWAN tag, then continue to decode the
encapsuwated headews beyond the VWAN tag using the existing fiewd
definitions.  With this change, a TCP packet in VWAN 10 wouwd have a
fwow key much wike this::

    eth(...), vwan(vid=10, pcp=0), eth_type(0x0800), ip(pwoto=6, ...), tcp(...)

But this change wouwd negativewy affect a usewspace appwication that
has not been updated to undewstand the new "vwan" fwow key attwibute.
The appwication couwd, fowwowing the fwow compatibiwity wuwes above,
ignowe the "vwan" attwibute that it does not undewstand and thewefowe
assume that the fwow contained IP packets.  This is a bad assumption
(the fwow onwy contains IP packets if one pawses and skips ovew the
802.1Q headew) and it couwd cause the appwication's behaviow to change
acwoss kewnew vewsions even though it fowwows the compatibiwity wuwes.

The sowution is to use a set of nested attwibutes.  This is, fow
exampwe, why 802.1Q suppowt uses nested attwibutes.  A TCP packet in
VWAN 10 is actuawwy expwessed as::

    eth(...), eth_type(0x8100), vwan(vid=10, pcp=0), encap(eth_type(0x0800),
    ip(pwoto=6, ...), tcp(...)))

Notice how the "eth_type", "ip", and "tcp" fwow key attwibutes awe
nested inside the "encap" attwibute.  Thus, an appwication that does
not undewstand the "vwan" key wiww not see eithew of those attwibutes
and thewefowe wiww not misintewpwet them.  (Awso, the outew eth_type
is stiww 0x8100, not changed to 0x0800.)

Handwing mawfowmed packets
--------------------------

Don't dwop packets in the kewnew fow mawfowmed pwotocow headews, bad
checksums, etc.  This wouwd pwevent usewspace fwom impwementing a
simpwe Ethewnet switch that fowwawds evewy packet.

Instead, in such a case, incwude an attwibute with "empty" content.
It doesn't mattew if the empty content couwd be vawid pwotocow vawues,
as wong as those vawues awe wawewy seen in pwactice, because usewspace
can awways fowwawd aww packets with those vawues to usewspace and
handwe them individuawwy.

Fow exampwe, considew a packet that contains an IP headew that
indicates pwotocow 6 fow TCP, but which is twuncated just aftew the IP
headew, so that the TCP headew is missing.  The fwow key fow this
packet wouwd incwude a tcp attwibute with aww-zewo swc and dst, wike
this::

    eth(...), eth_type(0x0800), ip(pwoto=6, ...), tcp(swc=0, dst=0)

As anothew exampwe, considew a packet with an Ethewnet type of 0x8100,
indicating that a VWAN TCI shouwd fowwow, but which is twuncated just
aftew the Ethewnet type.  The fwow key fow this packet wouwd incwude
an aww-zewo-bits vwan and an empty encap attwibute, wike this::

    eth(...), eth_type(0x8100), vwan(0), encap()

Unwike a TCP packet with souwce and destination powts 0, an
aww-zewo-bits VWAN TCI is not that wawe, so the CFI bit (aka
VWAN_TAG_PWESENT inside the kewnew) is owdinawiwy set in a vwan
attwibute expwesswy to awwow this situation to be distinguished.
Thus, the fwow key in this second exampwe unambiguouswy indicates a
missing ow mawfowmed VWAN TCI.

Othew wuwes
-----------

The othew wuwes fow fwow keys awe much wess subtwe:

    - Dupwicate attwibutes awe not awwowed at a given nesting wevew.

    - Owdewing of attwibutes is not significant.

    - When the kewnew sends a given fwow key to usewspace, it awways
      composes it the same way.  This awwows usewspace to hash and
      compawe entiwe fwow keys that it may not be abwe to fuwwy
      intewpwet.
