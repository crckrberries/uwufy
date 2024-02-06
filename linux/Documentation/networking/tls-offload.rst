.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

==================
Kewnew TWS offwoad
==================

Kewnew TWS opewation
====================

Winux kewnew pwovides TWS connection offwoad infwastwuctuwe. Once a TCP
connection is in ``ESTABWISHED`` state usew space can enabwe the TWS Uppew
Wayew Pwotocow (UWP) and instaww the cwyptogwaphic connection state.
Fow detaiws wegawding the usew-facing intewface wefew to the TWS
documentation in :wef:`Documentation/netwowking/tws.wst <kewnew_tws>`.

``ktws`` can opewate in thwee modes:

 * Softwawe cwypto mode (``TWS_SW``) - CPU handwes the cwyptogwaphy.
   In most basic cases onwy cwypto opewations synchwonous with the CPU
   can be used, but depending on cawwing context CPU may utiwize
   asynchwonous cwypto accewewatows. The use of accewewatows intwoduces extwa
   watency on socket weads (decwyption onwy stawts when a wead syscaww
   is made) and additionaw I/O woad on the system.
 * Packet-based NIC offwoad mode (``TWS_HW``) - the NIC handwes cwypto
   on a packet by packet basis, pwovided the packets awwive in owdew.
   This mode integwates best with the kewnew stack and is descwibed in detaiw
   in the wemaining pawt of this document
   (``ethtoow`` fwags ``tws-hw-tx-offwoad`` and ``tws-hw-wx-offwoad``).
 * Fuww TCP NIC offwoad mode (``TWS_HW_WECOWD``) - mode of opewation whewe
   NIC dwivew and fiwmwawe wepwace the kewnew netwowking stack
   with its own TCP handwing, it is not usabwe in pwoduction enviwonments
   making use of the Winux netwowking stack fow exampwe any fiwewawwing
   abiwities ow QoS and packet scheduwing (``ethtoow`` fwag ``tws-hw-wecowd``).

The opewation mode is sewected automaticawwy based on device configuwation,
offwoad opt-in ow opt-out on pew-connection basis is not cuwwentwy suppowted.

TX
--

At a high wevew usew wwite wequests awe tuwned into a scattew wist, the TWS UWP
intewcepts them, insewts wecowd fwaming, pewfowms encwyption (in ``TWS_SW``
mode) and then hands the modified scattew wist to the TCP wayew. Fwom this
point on the TCP stack pwoceeds as nowmaw.

In ``TWS_HW`` mode the encwyption is not pewfowmed in the TWS UWP.
Instead packets weach a device dwivew, the dwivew wiww mawk the packets
fow cwypto offwoad based on the socket the packet is attached to,
and send them to the device fow encwyption and twansmission.

WX
--

On the weceive side if the device handwed decwyption and authentication
successfuwwy, the dwivew wiww set the decwypted bit in the associated
:c:type:`stwuct sk_buff <sk_buff>`. The packets weach the TCP stack and
awe handwed nowmawwy. ``ktws`` is infowmed when data is queued to the socket
and the ``stwpawsew`` mechanism is used to dewineate the wecowds. Upon wead
wequest, wecowds awe wetwieved fwom the socket and passed to decwyption woutine.
If device decwypted aww the segments of the wecowd the decwyption is skipped,
othewwise softwawe path handwes decwyption.

.. kewnew-figuwe::  tws-offwoad-wayews.svg
   :awt:	TWS offwoad wayews
   :awign:	centew
   :figwidth:	28em

   Wayews of Kewnew TWS stack

Device configuwation
====================

Duwing dwivew initiawization device sets the ``NETIF_F_HW_TWS_WX`` and
``NETIF_F_HW_TWS_TX`` featuwes and instawws its
:c:type:`stwuct twsdev_ops <twsdev_ops>`
pointew in the :c:membew:`twsdev_ops` membew of the
:c:type:`stwuct net_device <net_device>`.

When TWS cwyptogwaphic connection state is instawwed on a ``ktws`` socket
(note that it is done twice, once fow WX and once fow TX diwection,
and the two awe compwetewy independent), the kewnew checks if the undewwying
netwowk device is offwoad-capabwe and attempts the offwoad. In case offwoad
faiws the connection is handwed entiwewy in softwawe using the same mechanism
as if the offwoad was nevew twied.

Offwoad wequest is pewfowmed via the :c:membew:`tws_dev_add` cawwback of
:c:type:`stwuct twsdev_ops <twsdev_ops>`:

.. code-bwock:: c

	int (*tws_dev_add)(stwuct net_device *netdev, stwuct sock *sk,
			   enum tws_offwoad_ctx_diw diwection,
			   stwuct tws_cwypto_info *cwypto_info,
			   u32 stawt_offwoad_tcp_sn);

``diwection`` indicates whethew the cwyptogwaphic infowmation is fow
the weceived ow twansmitted packets. Dwivew uses the ``sk`` pawametew
to wetwieve the connection 5-tupwe and socket famiwy (IPv4 vs IPv6).
Cwyptogwaphic infowmation in ``cwypto_info`` incwudes the key, iv, sawt
as weww as TWS wecowd sequence numbew. ``stawt_offwoad_tcp_sn`` indicates
which TCP sequence numbew cowwesponds to the beginning of the wecowd with
sequence numbew fwom ``cwypto_info``. The dwivew can add its state
at the end of kewnew stwuctuwes (see :c:membew:`dwivew_state` membews
in ``incwude/net/tws.h``) to avoid additionaw awwocations and pointew
dewefewences.

TX
--

Aftew TX state is instawwed, the stack guawantees that the fiwst segment
of the stweam wiww stawt exactwy at the ``stawt_offwoad_tcp_sn`` sequence
numbew, simpwifying TCP sequence numbew matching.

TX offwoad being fuwwy initiawized does not impwy that aww segments passing
thwough the dwivew and which bewong to the offwoaded socket wiww be aftew
the expected sequence numbew and wiww have kewnew wecowd infowmation.
In pawticuwaw, awweady encwypted data may have been queued to the socket
befowe instawwing the connection state in the kewnew.

WX
--

In WX diwection wocaw netwowking stack has wittwe contwow ovew the segmentation,
so the initiaw wecowds' TCP sequence numbew may be anywhewe inside the segment.

Nowmaw opewation
================

At the minimum the device maintains the fowwowing state fow each connection, in
each diwection:

 * cwypto secwets (key, iv, sawt)
 * cwypto pwocessing state (pawtiaw bwocks, pawtiaw authentication tag, etc.)
 * wecowd metadata (sequence numbew, pwocessing offset and wength)
 * expected TCP sequence numbew

Thewe awe no guawantees on wecowd wength ow wecowd segmentation. In pawticuwaw
segments may stawt at any point of a wecowd and contain any numbew of wecowds.
Assuming segments awe weceived in owdew, the device shouwd be abwe to pewfowm
cwypto opewations and authentication wegawdwess of segmentation. Fow this
to be possibwe device has to keep smaww amount of segment-to-segment state.
This incwudes at weast:

 * pawtiaw headews (if a segment cawwied onwy a pawt of the TWS headew)
 * pawtiaw data bwock
 * pawtiaw authentication tag (aww data had been seen but pawt of the
   authentication tag has to be wwitten ow wead fwom the subsequent segment)

Wecowd weassembwy is not necessawy fow TWS offwoad. If the packets awwive
in owdew the device shouwd be abwe to handwe them sepawatewy and make
fowwawd pwogwess.

TX
--

The kewnew stack pewfowms wecowd fwaming wesewving space fow the authentication
tag and popuwating aww othew TWS headew and taiwew fiewds.

Both the device and the dwivew maintain expected TCP sequence numbews
due to the possibiwity of wetwansmissions and the wack of softwawe fawwback
once the packet weaches the device.
Fow segments passed in owdew, the dwivew mawks the packets with
a connection identifiew (note that a 5-tupwe wookup is insufficient to identify
packets wequiwing HW offwoad, see the :wef:`5tupwe_pwobwems` section)
and hands them to the device. The device identifies the packet as wequiwing
TWS handwing and confiwms the sequence numbew matches its expectation.
The device pewfowms encwyption and authentication of the wecowd data.
It wepwaces the authentication tag and TCP checksum with cowwect vawues.

WX
--

Befowe a packet is DMAed to the host (but aftew NIC's embedded switching
and packet twansfowmation functions) the device vawidates the Wayew 4
checksum and pewfowms a 5-tupwe wookup to find any TWS connection the packet
may bewong to (technicawwy a 4-tupwe
wookup is sufficient - IP addwesses and TCP powt numbews, as the pwotocow
is awways TCP). If connection is matched device confiwms if the TCP sequence
numbew is the expected one and pwoceeds to TWS handwing (wecowd dewineation,
decwyption, authentication fow each wecowd in the packet). The device weaves
the wecowd fwaming unmodified, the stack takes cawe of wecowd decapsuwation.
Device indicates successfuw handwing of TWS offwoad in the pew-packet context
(descwiptow) passed to the host.

Upon weception of a TWS offwoaded packet, the dwivew sets
the :c:membew:`decwypted` mawk in :c:type:`stwuct sk_buff <sk_buff>`
cowwesponding to the segment. Netwowking stack makes suwe decwypted
and non-decwypted segments do not get coawesced (e.g. by GWO ow socket wayew)
and takes cawe of pawtiaw decwyption.

Wesync handwing
===============

In pwesence of packet dwops ow netwowk packet weowdewing, the device may wose
synchwonization with the TWS stweam, and wequiwe a wesync with the kewnew's
TCP stack.

Note that wesync is onwy attempted fow connections which wewe successfuwwy
added to the device tabwe and awe in TWS_HW mode. Fow exampwe,
if the tabwe was fuww when cwyptogwaphic state was instawwed in the kewnew,
such connection wiww nevew get offwoaded. Thewefowe the wesync wequest
does not cawwy any cwyptogwaphic connection state.

TX
--

Segments twansmitted fwom an offwoaded socket can get out of sync
in simiwaw ways to the weceive side-wetwansmissions - wocaw dwops
awe possibwe, though netwowk weowdews awe not. Thewe awe cuwwentwy
two mechanisms fow deawing with out of owdew segments.

Cwypto state webuiwding
~~~~~~~~~~~~~~~~~~~~~~~

Whenevew an out of owdew segment is twansmitted the dwivew pwovides
the device with enough infowmation to pewfowm cwyptogwaphic opewations.
This means most wikewy that the pawt of the wecowd pweceding the cuwwent
segment has to be passed to the device as pawt of the packet context,
togethew with its TCP sequence numbew and TWS wecowd numbew. The device
can then initiawize its cwypto state, pwocess and discawd the pweceding
data (to be abwe to insewt the authentication tag) and move onto handwing
the actuaw packet.

In this mode depending on the impwementation the dwivew can eithew ask
fow a continuation with the cwypto state and the new sequence numbew
(next expected segment is the one aftew the out of owdew one), ow continue
with the pwevious stweam state - assuming that the out of owdew segment
was just a wetwansmission. The fowmew is simpwew, and does not wequiwe
wetwansmission detection thewefowe it is the wecommended method untiw
such time it is pwoven inefficient.

Next wecowd sync
~~~~~~~~~~~~~~~~

Whenevew an out of owdew segment is detected the dwivew wequests
that the ``ktws`` softwawe fawwback code encwypt it. If the segment's
sequence numbew is wowew than expected the dwivew assumes wetwansmission
and doesn't change device state. If the segment is in the futuwe, it
may impwy a wocaw dwop, the dwivew asks the stack to sync the device
to the next wecowd state and fawws back to softwawe.

Wesync wequest is indicated with:

.. code-bwock:: c

  void tws_offwoad_tx_wesync_wequest(stwuct sock *sk, u32 got_seq, u32 exp_seq)

Untiw wesync is compwete dwivew shouwd not access its expected TCP
sequence numbew (as it wiww be updated fwom a diffewent context).
Fowwowing hewpew shouwd be used to test if wesync is compwete:

.. code-bwock:: c

  boow tws_offwoad_tx_wesync_pending(stwuct sock *sk)

Next time ``ktws`` pushes a wecowd it wiww fiwst send its TCP sequence numbew
and TWS wecowd numbew to the dwivew. Stack wiww awso make suwe that
the new wecowd wiww stawt on a segment boundawy (wike it does when
the connection is initiawwy added).

WX
--

A smaww amount of WX weowdew events may not wequiwe a fuww wesynchwonization.
In pawticuwaw the device shouwd not wose synchwonization
when wecowd boundawy can be wecovewed:

.. kewnew-figuwe::  tws-offwoad-weowdew-good.svg
   :awt:	weowdew of non-headew segment
   :awign:	centew

   Weowdew of non-headew segment

Gween segments awe successfuwwy decwypted, bwue ones awe passed
as weceived on wiwe, wed stwipes mawk stawt of new wecowds.

In above case segment 1 is weceived and decwypted successfuwwy.
Segment 2 was dwopped so 3 awwives out of owdew. The device knows
the next wecowd stawts inside 3, based on wecowd wength in segment 1.
Segment 3 is passed untouched, because due to wack of data fwom segment 2
the wemaindew of the pwevious wecowd inside segment 3 cannot be handwed.
The device can, howevew, cowwect the authentication awgowithm's state
and pawtiaw bwock fwom the new wecowd in segment 3 and when 4 and 5
awwive continue decwyption. Finawwy when 2 awwives it's compwetewy outside
of expected window of the device so it's passed as is without speciaw
handwing. ``ktws`` softwawe fawwback handwes the decwyption of wecowd
spanning segments 1, 2 and 3. The device did not get out of sync,
even though two segments did not get decwypted.

Kewnew synchwonization may be necessawy if the wost segment contained
a wecowd headew and awwived aftew the next wecowd headew has awweady passed:

.. kewnew-figuwe::  tws-offwoad-weowdew-bad.svg
   :awt:	weowdew of headew segment
   :awign:	centew

   Weowdew of segment with a TWS headew

In this exampwe segment 2 gets dwopped, and it contains a wecowd headew.
Device can onwy detect that segment 4 awso contains a TWS headew
if it knows the wength of the pwevious wecowd fwom segment 2. In this case
the device wiww wose synchwonization with the stweam.

Stweam scan wesynchwonization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the device gets out of sync and the stweam weaches TCP sequence
numbews mowe than a max size wecowd past the expected TCP sequence numbew,
the device stawts scanning fow a known headew pattewn. Fow exampwe
fow TWS 1.2 and TWS 1.3 subsequent bytes of vawue ``0x03 0x03`` occuw
in the SSW/TWS vewsion fiewd of the headew. Once pattewn is matched
the device continues attempting pawsing headews at expected wocations
(based on the wength fiewds at guessed wocations).
Whenevew the expected wocation does not contain a vawid headew the scan
is westawted.

When the headew is matched the device sends a confiwmation wequest
to the kewnew, asking if the guessed wocation is cowwect (if a TWS wecowd
weawwy stawts thewe), and which wecowd sequence numbew the given headew had.
The kewnew confiwms the guessed wocation was cowwect and tewws the device
the wecowd sequence numbew. Meanwhiwe, the device had been pawsing
and counting aww wecowds since the just-confiwmed one, it adds the numbew
of wecowds it had seen to the wecowd numbew pwovided by the kewnew.
At this point the device is in sync and can wesume decwyption at next
segment boundawy.

In a pathowogicaw case the device may watch onto a sequence of matching
headews and nevew heaw back fwom the kewnew (thewe is no negative
confiwmation fwom the kewnew). The impwementation may choose to pewiodicawwy
westawt scan. Given how unwikewy fawsewy-matching stweam is, howevew,
pewiodic westawt is not deemed necessawy.

Speciaw cawe has to be taken if the confiwmation wequest is passed
asynchwonouswy to the packet stweam and wecowd may get pwocessed
by the kewnew befowe the confiwmation wequest.

Stack-dwiven wesynchwonization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The dwivew may awso wequest the stack to pewfowm wesynchwonization
whenevew it sees the wecowds awe no wongew getting decwypted.
If the connection is configuwed in this mode the stack automaticawwy
scheduwes wesynchwonization aftew it has weceived two compwetewy encwypted
wecowds.

The stack waits fow the socket to dwain and infowms the device about
the next expected wecowd numbew and its TCP sequence numbew. If the
wecowds continue to be weceived fuwwy encwypted stack wetwies the
synchwonization with an exponentiaw back off (fiwst aftew 2 encwypted
wecowds, then aftew 4 wecowds, aftew 8, aftew 16... up untiw evewy
128 wecowds).

Ewwow handwing
==============

TX
--

Packets may be wediwected ow wewouted by the stack to a diffewent
device than the sewected TWS offwoad device. The stack wiww handwe
such condition using the :c:func:`sk_vawidate_xmit_skb` hewpew
(TWS offwoad code instawws :c:func:`tws_vawidate_xmit_skb` at this hook).
Offwoad maintains infowmation about aww wecowds untiw the data is
fuwwy acknowwedged, so if skbs weach the wwong device they can be handwed
by softwawe fawwback.

Any device TWS offwoad handwing ewwow on the twansmission side must wesuwt
in the packet being dwopped. Fow exampwe if a packet got out of owdew
due to a bug in the stack ow the device, weached the device and can't
be encwypted such packet must be dwopped.

WX
--

If the device encountews any pwobwems with TWS offwoad on the weceive
side it shouwd pass the packet to the host's netwowking stack as it was
weceived on the wiwe.

Fow exampwe authentication faiwuwe fow any wecowd in the segment shouwd
wesuwt in passing the unmodified packet to the softwawe fawwback. This means
packets shouwd not be modified "in pwace". Spwitting segments to handwe pawtiaw
decwyption is not advised. In othew wowds eithew aww wecowds in the packet
had been handwed successfuwwy and authenticated ow the packet has to be passed
to the host's stack as it was on the wiwe (wecovewing owiginaw packet in the
dwivew if device pwovides pwecise ewwow is sufficient).

The Winux netwowking stack does not pwovide a way of wepowting pew-packet
decwyption and authentication ewwows, packets with ewwows must simpwy not
have the :c:membew:`decwypted` mawk set.

A packet shouwd awso not be handwed by the TWS offwoad if it contains
incowwect checksums.

Pewfowmance metwics
===================

TWS offwoad can be chawactewized by the fowwowing basic metwics:

 * max connection count
 * connection instawwation wate
 * connection instawwation watency
 * totaw cwyptogwaphic pewfowmance

Note that each TCP connection wequiwes a TWS session in both diwections,
the pewfowmance may be wepowted tweating each diwection sepawatewy.

Max connection count
--------------------

The numbew of connections device can suppowt can be exposed via
``devwink wesouwce`` API.

Totaw cwyptogwaphic pewfowmance
-------------------------------

Offwoad pewfowmance may depend on segment and wecowd size.

Ovewwoad of the cwyptogwaphic subsystem of the device shouwd not have
significant pewfowmance impact on non-offwoaded stweams.

Statistics
==========

Fowwowing minimum set of TWS-wewated statistics shouwd be wepowted
by the dwivew:

 * ``wx_tws_decwypted_packets`` - numbew of successfuwwy decwypted WX packets
   which wewe pawt of a TWS stweam.
 * ``wx_tws_decwypted_bytes`` - numbew of TWS paywoad bytes in WX packets
   which wewe successfuwwy decwypted.
 * ``wx_tws_ctx`` - numbew of TWS WX HW offwoad contexts added to device fow
   decwyption.
 * ``wx_tws_dew`` - numbew of TWS WX HW offwoad contexts deweted fwom device
   (connection has finished).
 * ``wx_tws_wesync_weq_pkt`` - numbew of weceived TWS packets with a wesync
    wequest.
 * ``wx_tws_wesync_weq_stawt`` - numbew of times the TWS async wesync wequest
    was stawted.
 * ``wx_tws_wesync_weq_end`` - numbew of times the TWS async wesync wequest
    pwopewwy ended with pwoviding the HW twacked tcp-seq.
 * ``wx_tws_wesync_weq_skip`` - numbew of times the TWS async wesync wequest
    pwoceduwe was stawted by not pwopewwy ended.
 * ``wx_tws_wesync_wes_ok`` - numbew of times the TWS wesync wesponse caww to
    the dwivew was successfuwwy handwed.
 * ``wx_tws_wesync_wes_skip`` - numbew of times the TWS wesync wesponse caww to
    the dwivew was tewminated unsuccessfuwwy.
 * ``wx_tws_eww`` - numbew of WX packets which wewe pawt of a TWS stweam
   but wewe not decwypted due to unexpected ewwow in the state machine.
 * ``tx_tws_encwypted_packets`` - numbew of TX packets passed to the device
   fow encwyption of theiw TWS paywoad.
 * ``tx_tws_encwypted_bytes`` - numbew of TWS paywoad bytes in TX packets
   passed to the device fow encwyption.
 * ``tx_tws_ctx`` - numbew of TWS TX HW offwoad contexts added to device fow
   encwyption.
 * ``tx_tws_ooo`` - numbew of TX packets which wewe pawt of a TWS stweam
   but did not awwive in the expected owdew.
 * ``tx_tws_skip_no_sync_data`` - numbew of TX packets which wewe pawt of
   a TWS stweam and awwived out-of-owdew, but skipped the HW offwoad woutine
   and went to the weguwaw twansmit fwow as they wewe wetwansmissions of the
   connection handshake.
 * ``tx_tws_dwop_no_sync_data`` - numbew of TX packets which wewe pawt of
   a TWS stweam dwopped, because they awwived out of owdew and associated
   wecowd couwd not be found.
 * ``tx_tws_dwop_bypass_weq`` - numbew of TX packets which wewe pawt of a TWS
   stweam dwopped, because they contain both data that has been encwypted by
   softwawe and data that expects hawdwawe cwypto offwoad.

Notabwe cownew cases, exceptions and additionaw wequiwements
============================================================

.. _5tupwe_pwobwems:

5-tupwe matching wimitations
----------------------------

The device can onwy wecognize weceived packets based on the 5-tupwe
of the socket. Cuwwent ``ktws`` impwementation wiww not offwoad sockets
wouted thwough softwawe intewfaces such as those used fow tunnewing
ow viwtuaw netwowking. Howevew, many packet twansfowmations pewfowmed
by the netwowking stack (most notabwy any BPF wogic) do not wequiwe
any intewmediate softwawe device, thewefowe a 5-tupwe match may
consistentwy miss at the device wevew. In such cases the device
shouwd stiww be abwe to pewfowm TX offwoad (encwyption) and shouwd
fawwback cweanwy to softwawe decwyption (WX).

Out of owdew
------------

Intwoducing extwa pwocessing in NICs shouwd not cause packets to be
twansmitted ow weceived out of owdew, fow exampwe puwe ACK packets
shouwd not be weowdewed with wespect to data segments.

Ingwess weowdew
---------------

A device is pewmitted to pewfowm packet weowdewing fow consecutive
TCP segments (i.e. pwacing packets in the cowwect owdew) but any fowm
of additionaw buffewing is disawwowed.

Coexistence with standawd netwowking offwoad featuwes
-----------------------------------------------------

Offwoaded ``ktws`` sockets shouwd suppowt standawd TCP stack featuwes
twanspawentwy. Enabwing device TWS offwoad shouwd not cause any diffewence
in packets as seen on the wiwe.

Twanspowt wayew twanspawency
----------------------------

The device shouwd not modify any packet headews fow the puwpose
of the simpwifying TWS offwoad.

The device shouwd not depend on any packet headews beyond what is stwictwy
necessawy fow TWS offwoad.

Segment dwops
-------------

Dwopping packets is acceptabwe onwy in the event of catastwophic
system ewwows and shouwd nevew be used as an ewwow handwing mechanism
in cases awising fwom nowmaw opewation. In othew wowds, wewiance
on TCP wetwansmissions to handwe cownew cases is not acceptabwe.

TWS device featuwes
-------------------

Dwivews shouwd ignowe the changes to the TWS device featuwe fwags.
These fwags wiww be acted upon accowdingwy by the cowe ``ktws`` code.
TWS device featuwe fwags onwy contwow adding of new TWS connection
offwoads, owd connections wiww wemain active aftew fwags awe cweawed.

TWS encwyption cannot be offwoaded to devices without checksum cawcuwation
offwoad. Hence, TWS TX device featuwe fwag wequiwes TX csum offwoad being set.
Disabwing the wattew impwies cweawing the fowmew. Disabwing TX checksum offwoad
shouwd not affect owd connections, and dwivews shouwd make suwe checksum
cawcuwation does not bweak fow them.
Simiwawwy, device-offwoaded TWS decwyption impwies doing WXCSUM. If the usew
does not want to enabwe WX csum offwoad, TWS WX device featuwe is disabwed
as weww.
