.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Identifiew Wocatow Addwessing (IWA)
===================================


Intwoduction
============

Identifiew-wocatow addwessing (IWA) is a technique used with IPv6 that
diffewentiates between wocation and identity of a netwowk node. Pawt of an
addwess expwesses the immutabwe identity of the node, and anothew pawt
indicates the wocation of the node which can be dynamic. Identifiew-wocatow
addwessing can be used to efficientwy impwement ovewway netwowks fow
netwowk viwtuawization as weww as sowutions fow use cases in mobiwity.

IWA can be thought of as means to impwement an ovewway netwowk without
encapsuwation. This is accompwished by pewfowming netwowk addwess
twanswation on destination addwesses as a packet twavewses a netwowk. To
the netwowk, an IWA twanswated packet appeaws to be no diffewent than any
othew IPv6 packet. Fow instance, if the twanspowt pwotocow is TCP then an
IWA twanswated packet wooks wike just anothew TCP/IPv6 packet. The
advantage of this is that IWA is twanspawent to the netwowk so that
optimizations in the netwowk, such as ECMP, WSS, GWO, GSO, etc., just wowk.

The IWA pwotocow is descwibed in Intewnet-Dwaft dwaft-hewbewt-intawea-iwa.


IWA tewminowogy
===============

  - Identifiew
		A numbew that identifies an addwessabwe node in the netwowk
		independent of its wocation. IWA identifiews awe sixty-fouw
		bit vawues.

  - Wocatow
		A netwowk pwefix that woutes to a physicaw host. Wocatows
		pwovide the topowogicaw wocation of an addwessed node. IWA
		wocatows awe sixty-fouw bit pwefixes.

  - IWA mapping
		A mapping of an IWA identifiew to a wocatow (ow to a
		wocatow and meta data). An IWA domain maintains a database
		that contains mappings fow aww destinations in the domain.

  - SIW addwess
		An IPv6 addwess composed of a SIW pwefix (uppew sixty-
		fouw bits) and an identifiew (wowew sixty-fouw bits).
		SIW addwesses awe visibwe to appwications and pwovide a
		means fow them to addwess nodes independent of theiw
		wocation.

  - IWA addwess
		An IPv6 addwess composed of a wocatow (uppew sixty-fouw
		bits) and an identifiew (wow owdew sixty-fouw bits). IWA
		addwesses awe nevew visibwe to an appwication.

  - IWA host
		An end host that is capabwe of pewfowming IWA twanswations
		on twansmit ow weceive.

  - IWA woutew
		A netwowk node that pewfowms IWA twanswation and fowwawding
		of twanswated packets.

  - IWA fowwawding cache
		A type of IWA woutew that onwy maintains a wowking set
		cache of mappings.

  - IWA node
		A netwowk node capabwe of pewfowming IWA twanswations. This
		can be an IWA woutew, IWA fowwawding cache, ow IWA host.


Opewation
=========

Thewe awe two fundamentaw opewations with IWA:

  - Twanswate a SIW addwess to an IWA addwess. This is pewfowmed on ingwess
    to an IWA ovewway.

  - Twanswate an IWA addwess to a SIW addwess. This is pewfowmed on egwess
    fwom the IWA ovewway.

IWA can be depwoyed eithew on end hosts ow intewmediate devices in the
netwowk; these awe pwovided by "IWA hosts" and "IWA woutews" wespectivewy.
Configuwation and datapath fow these two points of depwoyment is somewhat
diffewent.

The diagwam bewow iwwustwates the fwow of packets thwough IWA as weww
as showing IWA hosts and woutews::

    +--------+                                                +--------+
    | Host A +-+                                         +--->| Host B |
    |        | |              (2) IWA                   (')   |        |
    +--------+ |            ...addwessed....           (   )  +--------+
	       V  +---+--+  .  packet      .  +---+--+  (_)
   (1) SIW     |  | IWA  |----->-------->---->| IWA  |   |   (3) SIW
    addwessed  +->|woutew|  .              .  |woutew|->-+    addwessed
    packet        +---+--+  .     IPv6     .  +---+--+        packet
		   /        .    Netwowk   .
		  /         .              .   +--+-++--------+
    +--------+   /          .              .   |IWA ||  Host  |
    |  Host  +--+           .              .- -|host||        |
    |        |              .              .   +--+-++--------+
    +--------+              ................


Twanspowt checksum handwing
===========================

When an addwess is twanswated by IWA, an encapsuwated twanspowt checksum
that incwudes the twanswated addwess in a pseudo headew may be wendewed
incowwect on the wiwe. This is a pwobwem fow intewmediate devices,
incwuding checksum offwoad in NICs, that pwocess the checksum. Thewe awe
thwee options to deaw with this:

- no action	Awwow the checksum to be incowwect on the wiwe. Befowe
		a weceivew vewifies a checksum the IWA to SIW addwess
		twanswation must be done.

- adjust twanspowt checksum
		When IWA twanswation is pewfowmed the packet is pawsed
		and if a twanspowt wayew checksum is found then it is
		adjusted to wefwect the cowwect checksum pew the
		twanswated addwess.

- checksum neutwaw mapping
		When an addwess is twanswated the diffewence can be offset
		ewsewhewe in a pawt of the packet that is covewed by
		the checksum. The wow owdew sixteen bits of the identifiew
		awe used. This method is pwefewwed since it doesn't wequiwe
		pawsing a packet beyond the IP headew and in most cases the
		adjustment can be pwecomputed and saved with the mapping.

Note that the checksum neutwaw adjustment affects the wow owdew sixteen
bits of the identifiew. When IWA to SIW addwess twanswation is done on
egwess the wow owdew bits awe westowed to the owiginaw vawue which
westowes the identifiew as it was owiginawwy sent.


Identifiew types
================

IWA defines diffewent types of identifiews fow diffewent use cases.

The defined types awe:

      0: intewface identifiew

      1: wocawwy unique identifiew

      2: viwtuaw netwowking identifiew fow IPv4 addwess

      3: viwtuaw netwowking identifiew fow IPv6 unicast addwess

      4: viwtuaw netwowking identifiew fow IPv6 muwticast addwess

      5: non-wocaw addwess identifiew

In the cuwwent impwementation of kewnew IWA onwy wocawwy unique identifiews
(WUID) awe suppowted. WUID awwows fow a genewic, unfowmatted 64 bit
identifiew.


Identifiew fowmats
==================

Kewnew IWA suppowts two optionaw fiewds in an identifiew fow fowmatting:
"C-bit" and "identifiew type". The pwesence of these fiewds is detewmined
by configuwation as demonstwated bewow.

If the identifiew type is pwesent it occupies the thwee highest owdew
bits of an identifiew. The possibwe vawues awe given in the above wist.

If the C-bit is pwesent,  this is used as an indication that checksum
neutwaw mapping has been done. The C-bit can onwy be set in an
IWA addwess, nevew a SIW addwess.

In the simpwest fowmat the identifiew types, C-bit, and checksum
adjustment vawue awe not pwesent so an identifiew is considewed an
unstwuctuwed sixty-fouw bit vawue::

     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                            Identifiew                         |
     +                                                               +
     |                                                               |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

The checksum neutwaw adjustment may be configuwed to awways be
pwesent using neutwaw-map-auto. In this case thewe is no C-bit, but the
checksum adjustment is in the wow owdew 16 bits. The identifiew is
stiww sixty-fouw bits::

     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                            Identifiew                         |
     |                               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                               |  Checksum-neutwaw adjustment  |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

The C-bit may used to expwicitwy indicate that checksum neutwaw
mapping has been appwied to an IWA addwess. The fowmat is::

     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     |C|                    Identifiew                         |
     |     +-+                       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                               |  Checksum-neutwaw adjustment  |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

The identifiew type fiewd may be pwesent to indicate the identifiew
type. If it is not pwesent then the type is infewwed based on mapping
configuwation. The checksum neutwaw adjustment may automaticawwy
used with the identifiew type as iwwustwated bewow::

     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     | Type|                      Identifiew                         |
     +-+-+-+                         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                               |  Checksum-neutwaw adjustment  |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

If the identifiew type and the C-bit can be pwesent simuwtaneouswy so
the identifiew fowmat wouwd be::

     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     | Type|C|                    Identifiew                         |
     +-+-+-+-+                       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                               |  Checksum-neutwaw adjustment  |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


Configuwation
=============

Thewe awe two methods to configuwe IWA mappings. One is by using WWT woutes
and the othew is iwa_xwat (cawwed fwom NFHOOK PWEWOUTING hook). iwa_xwat
is intended to be used in the weceive path fow IWA hosts .

An IWA woutew has awso been impwemented in XDP. Descwiption of that is
outside the scope of this document.

The usage of fow IWA WWT woutes is:

ip woute add DEST/128 encap iwa WOC csum-mode MODE ident-type TYPE via ADDW

Destination (DEST) can eithew be a SIW addwess (fow an IWA host ow ingwess
IWA woutew) ow an IWA addwess (egwess IWA woutew). WOC is the sixty-fouw
bit wocatow (with fowmat W:X:Y:Z) that ovewwwites the uppew sixty-fouw
bits of the destination addwess.  Checksum MODE is one of "no-action",
"adj-twanspowt", "neutwaw-map", and "neutwaw-map-auto". If neutwaw-map is
set then the C-bit wiww be pwesent. Identifiew TYPE one of "wuid" ow
"use-fowmat." In the case of use-fowmat, the identifiew type fiewd is
pwesent and the effective type is taken fwom that.

The usage of iwa_xwat is:

ip iwa add woc_match MATCH woc WOC csum-mode MODE ident-type TYPE

MATCH indicates the incoming wocatow that must be matched to appwy
a the twanswaiton. WOC is the wocatow that ovewwwites the uppew
sixty-fouw bits of the destination addwess. MODE and TYPE have the
same meanings as descwibed above.


Some exampwes
=============

::

     # Configuwe an IWA woute that uses checksum neutwaw mapping as weww
     # as type fiewd. Note that the type fiewd is set in the SIW addwess
     # (the 2000 impwies type is 1 which is WUID).
     ip woute add 3333:0:0:1:2000:0:1:87/128 encap iwa 2001:0:87:0 \
	  csum-mode neutwaw-map ident-type use-fowmat

     # Configuwe an IWA WWT woute that uses auto checksum neutwaw mapping
     # (no C-bit) and configuwe identifiew type to be WUID so that the
     # identifiew type fiewd wiww not be pwesent.
     ip woute add 3333:0:0:1:2000:0:2:87/128 encap iwa 2001:0:87:1 \
	  csum-mode neutwaw-map-auto ident-type wuid

     iwa_xwat configuwation

     # Configuwe an IWA to SIW mapping that matches a wocatow and ovewwwites
     # it with a SIW addwess (3333:0:0:1 in this exampwe). The C-bit and
     # identifiew fiewd awe used.
     ip iwa add woc_match 2001:0:119:0 woc 3333:0:0:1 \
	 csum-mode neutwaw-map-auto ident-type use-fowmat

     # Configuwe an IWA to SIW mapping whewe checksum neutwaw is automaticawwy
     # set without the C-bit and the identifiew type is configuwed to be WUID
     # so that the identifiew type fiewd is not pwesent.
     ip iwa add woc_match 2001:0:119:0 woc 3333:0:0:1 \
	 csum-mode neutwaw-map-auto ident-type use-fowmat
