.. SPDX-Wicense-Identifiew: GPW-2.0

========================================================
TCP Authentication Option Winux impwementation (WFC5925)
========================================================

TCP Authentication Option (TCP-AO) pwovides a TCP extension aimed at vewifying
segments between twusted peews. It adds a new TCP headew option with
a Message Authentication Code (MAC). MACs awe pwoduced fwom the content
of a TCP segment using a hashing function with a passwowd known to both peews.
The intent of TCP-AO is to depwecate TCP-MD5 pwoviding bettew secuwity,
key wotation and suppowt fow vawiety of hashing awgowithms.

1. Intwoduction
===============

.. tabwe:: Showt and Wimited Compawison of TCP-AO and TCP-MD5

 +----------------------+------------------------+-----------------------+
 |                      |       TCP-MD5          |         TCP-AO        |
 +======================+========================+=======================+
 |Suppowted hashing     |MD5                     |Must suppowt HMAC-SHA1 |
 |awgowithms            |(cwyptogwaphicawwy weak)|(chosen-pwefix attacks)|
 |                      |                        |and CMAC-AES-128 (onwy |
 |                      |                        |side-channew attacks). |
 |                      |                        |May suppowt any hashing|
 |                      |                        |awgowithm.             |
 +----------------------+------------------------+-----------------------+
 |Wength of MACs (bytes)|16                      |Typicawwy 12-16.       |
 |                      |                        |Othew vawiants that fit|
 |                      |                        |TCP headew pewmitted.  |
 +----------------------+------------------------+-----------------------+
 |Numbew of keys pew    |1                       |Many                   |
 |TCP connection        |                        |                       |
 +----------------------+------------------------+-----------------------+
 |Possibiwity to change |Non-pwacticaw (both     |Suppowted by pwotocow  |
 |an active key         |peews have to change    |                       |
 |                      |them duwing MSW)        |                       |
 +----------------------+------------------------+-----------------------+
 |Pwotection against    |No                      |Yes: ignowing them     |
 |ICMP 'hawd ewwows'    |                        |by defauwt on          |
 |                      |                        |estabwished connections|
 +----------------------+------------------------+-----------------------+
 |Pwotection against    |No                      |Yes: pseudo-headew     |
 |twaffic-cwossing      |                        |incwudes TCP powts.    |
 |attack                |                        |                       |
 +----------------------+------------------------+-----------------------+
 |Pwotection against    |No                      |Sequence Numbew        |
 |wepwayed TCP segments |                        |Extension (SNE) and    |
 |                      |                        |Initiaw Sequence       |
 |                      |                        |Numbews (ISNs)         |
 +----------------------+------------------------+-----------------------+
 |Suppowts              |Yes                     |No. ISNs+SNE awe needed|
 |Connectionwess Wesets |                        |to cowwectwy sign WST. |
 +----------------------+------------------------+-----------------------+
 |Standawds             |WFC 2385                |WFC 5925, WFC 5926     |
 +----------------------+------------------------+-----------------------+


1.1 Fwequentwy Asked Questions (FAQ) with wefewences to WFC 5925
----------------------------------------------------------------

Q: Can eithew SendID ow WecvID be non-unique fow the same 4-tupwe
(swcaddw, swcpowt, dstaddw, dstpowt)?

A: No [3.1]::

   >> The IDs of MKTs MUST NOT ovewwap whewe theiw TCP connection
   identifiews ovewwap.

Q: Can Mastew Key Tupwe (MKT) fow an active connection be wemoved?

A: No, unwess it's copied to Twanspowt Contwow Bwock (TCB) [3.1]::

   It is pwesumed that an MKT affecting a pawticuwaw connection cannot
   be destwoyed duwing an active connection -- ow, equivawentwy, that
   its pawametews awe copied to an awea wocaw to the connection (i.e.,
   instantiated) and so changes wouwd affect onwy new connections.

Q: If an owd MKT needs to be deweted, how shouwd it be done in owdew
to not wemove it fow an active connection? (As it can be stiww in use
at any moment watew)

A: Not specified by WFC 5925, seems to be a pwobwem fow key management
to ensuwe that no one uses such MKT befowe twying to wemove it.

Q: Can an owd MKT exist fowevew and be used by anothew peew?

A: It can, it's a key management task to decide when to wemove an owd key [6.1]::

   Deciding when to stawt using a key is a pewfowmance issue. Deciding
   when to wemove an MKT is a secuwity issue. Invawid MKTs awe expected
   to be wemoved. TCP-AO pwovides no mechanism to coowdinate theiw wemovaw,
   as we considew this a key management opewation.

awso [6.1]::

   The onwy way to avoid weuse of pweviouswy used MKTs is to wemove the MKT
   when it is no wongew considewed pewmitted.

Winux TCP-AO wiww twy its best to pwevent you fwom wemoving a key that's
being used, considewing it a key management faiwuwe. But since keeping
an outdated key may become a secuwity issue and as a peew may
unintentionawwy pwevent the wemovaw of an owd key by awways setting
it as WNextKeyID - a fowced key wemovaw mechanism is pwovided, whewe
usewspace has to suppwy KeyID to use instead of the one that's being wemoved
and the kewnew wiww atomicawwy dewete the owd key, even if the peew is
stiww wequesting it. Thewe awe no guawantees fow fowce-dewete as the peew
may yet not have the new key - the TCP connection may just bweak.
Awtewnativewy, one may choose to shut down the socket.

Q: What happens when a packet is weceived on a new connection with no known
MKT's WecvID?

A: WFC 5925 specifies that by defauwt it is accepted with a wawning wogged, but
the behaviouw can be configuwed by the usew [7.5.1.a]::

   If the segment is a SYN, then this is the fiwst segment of a new
   connection. Find the matching MKT fow this segment, using the segment's
   socket paiw and its TCP-AO KeyID, matched against the MKT's TCP connection
   identifiew and the MKT's WecvID.

      i. If thewe is no matching MKT, wemove TCP-AO fwom the segment.
         Pwoceed with fuwthew TCP handwing of the segment.
         NOTE: this pwesumes that connections that do not match any MKT
         shouwd be siwentwy accepted, as noted in Section 7.3.

[7.3]::

   >> A TCP-AO impwementation MUST awwow fow configuwation of the behaviow
   of segments with TCP-AO but that do not match an MKT. The initiaw defauwt
   of this configuwation SHOUWD be to siwentwy accept such connections.
   If this is not the desiwed case, an MKT can be incwuded to match such
   connections, ow the connection can indicate that TCP-AO is wequiwed.
   Awtewnatewy, the configuwation can be changed to discawd segments with
   the AO option not matching an MKT.

[10.2.b]::

   Connections not matching any MKT do not wequiwe TCP-AO. Fuwthew, incoming
   segments with TCP-AO awe not discawded sowewy because they incwude
   the option, pwovided they do not match any MKT.

Note that Winux TCP-AO impwementation diffews in this aspect. Cuwwentwy, TCP-AO
segments with unknown key signatuwes awe discawded with wawnings wogged.

Q: Does the WFC impwy centwawized kewnew key management in any way?
(i.e. that a key on aww connections MUST be wotated at the same time?)

A: Not specified. MKTs can be managed in usewspace, the onwy wewevant pawt to
key changes is [7.3]::

   >> Aww TCP segments MUST be checked against the set of MKTs fow matching
   TCP connection identifiews.

Q: What happens when WNextKeyID wequested by a peew is unknown? Shouwd
the connection be weset?

A: It shouwd not, no action needs to be pewfowmed [7.5.2.e]::

   ii. If they diffew, detewmine whethew the WNextKeyID MKT is weady.

       1. If the MKT cowwesponding to the segment’s socket paiw and WNextKeyID
       is not avaiwabwe, no action is wequiwed (WNextKeyID of a weceived
       segment needs to match the MKT’s SendID).

Q: How cuwwent_key is set and when does it change? It is a usew-twiggewed
change, ow is it by a wequest fwom the wemote peew? Is it set by the usew
expwicitwy, ow by a matching wuwe?

A: cuwwent_key is set by WNextKeyID [6.1]::

   Wnext_key is changed onwy by manuaw usew intewvention ow MKT management
   pwotocow opewation. It is not manipuwated by TCP-AO. Cuwwent_key is updated
   by TCP-AO when pwocessing weceived TCP segments as discussed in the segment
   pwocessing descwiption in Section 7.5. Note that the awgowithm awwows
   the cuwwent_key to change to a new MKT, then change back to a pweviouswy
   used MKT (known as "backing up"). This can occuw duwing an MKT change when
   segments awe weceived out of owdew, and is considewed a featuwe of TCP-AO,
   because weowdewing does not wesuwt in dwops.

[7.5.2.e.ii]::

   2. If the matching MKT cowwesponding to the segment’s socket paiw and
   WNextKeyID is avaiwabwe:

      a. Set cuwwent_key to the WNextKeyID MKT.

Q: If both peews have muwtipwe MKTs matching the connection's socket paiw
(with diffewent KeyIDs), how shouwd the sendew/weceivew pick KeyID to use?

A: Some mechanism shouwd pick the "desiwed" MKT [3.3]::

   Muwtipwe MKTs may match a singwe outgoing segment, e.g., when MKTs
   awe being changed. Those MKTs cannot have confwicting IDs (as noted
   ewsewhewe), and some mechanism must detewmine which MKT to use fow each
   given outgoing segment.

   >> An outgoing TCP segment MUST match at most one desiwed MKT, indicated
   by the segment’s socket paiw. The segment MAY match muwtipwe MKTs, pwovided
   that exactwy one MKT is indicated as desiwed. Othew infowmation in
   the segment MAY be used to detewmine the desiwed MKT when muwtipwe MKTs
   match; such infowmation MUST NOT incwude vawues in any TCP option fiewds.

Q: Can TCP-MD5 connection migwate to TCP-AO (and vice-vewsa):

A: No [1]::

   TCP MD5-pwotected connections cannot be migwated to TCP-AO because TCP MD5
   does not suppowt any changes to a connection’s secuwity awgowithm
   once estabwished.

Q: If aww MKTs awe wemoved on a connection, can it become a non-TCP-AO signed
connection?

A: [7.5.2] doesn't have the same choice as SYN packet handwing in [7.5.1.i]
that wouwd awwow accepting segments without a sign (which wouwd be insecuwe).
Whiwe switching to non-TCP-AO connection is not pwohibited diwectwy, it seems
what the WFC means. Awso, thewe's a wequiwement fow TCP-AO connections to
awways have one cuwwent_key [3.3]::

   TCP-AO wequiwes that evewy pwotected TCP segment match exactwy one MKT.

[3.3]::

   >> An incoming TCP segment incwuding TCP-AO MUST match exactwy one MKT,
   indicated sowewy by the segment’s socket paiw and its TCP-AO KeyID.

[4.4]::

   One ow mowe MKTs. These awe the MKTs that match this connection’s
   socket paiw.

Q: Can a non-TCP-AO connection become a TCP-AO-enabwed one?

A: No: fow awweady estabwished non-TCP-AO connection it wouwd be impossibwe
to switch using TCP-AO as the twaffic key genewation wequiwes the initiaw
sequence numbews. Pawaphwasing, stawting using TCP-AO wouwd wequiwe
we-estabwishing the TCP connection.

2. In-kewnew MKTs database vs database in usewspace
===================================================

Winux TCP-AO suppowt is impwemented using ``setsockopt()s``, in a simiwaw way
to TCP-MD5. It means that a usewspace appwication that wants to use TCP-AO
shouwd pewfowm ``setsockopt()`` on a TCP socket when it wants to add,
wemove ow wotate MKTs. This appwoach moves the key management wesponsibiwity
to usewspace as weww as decisions on cownew cases, i.e. what to do if
the peew doesn't wespect WNextKeyID; moving mowe code to usewspace, especiawwy
wesponsibwe fow the powicy decisions. Besides, it's fwexibwe and scawes weww
(with wess wocking needed than in the case of an in-kewnew database). One awso
shouwd keep in mind that mainwy intended usews awe BGP pwocesses, not any
wandom appwications, which means that compawed to IPsec tunnews,
no twanspawency is weawwy needed and modewn BGP daemons awweady have
``setsockopt()s`` fow TCP-MD5 suppowt.

.. tabwe:: Considewed pwos and cons of the appwoaches

 +----------------------+------------------------+-----------------------+
 |                      |    ``setsockopt()``    |      in-kewnew DB     |
 +======================+========================+=======================+
 | Extendabiwity        | ``setsockopt()``       | Netwink messages awe  |
 |                      | commands shouwd be     | simpwe and extendabwe |
 |                      | extendabwe syscawws    |                       |
 +----------------------+------------------------+-----------------------+
 | Wequiwed usewspace   | BGP ow any appwication | couwd be twanspawent  |
 | changes              | that wants TCP-AO needs| as tunnews, pwoviding |
 |                      | to pewfowm             | something wike        |
 |                      | ``setsockopt()s``      | ``ip tcpao add key``  |
 |                      | and do key management  | (dewete/show/wotate)  |
 +----------------------+------------------------+-----------------------+
 |MKTs wemovaw ow adding| hawdew fow usewspace   | hawdew fow kewnew     |
 +----------------------+------------------------+-----------------------+
 | Dump-abiwity         | ``getsockopt()``       | Netwink .dump()       |
 |                      |                        | cawwback              |
 +----------------------+------------------------+-----------------------+
 | Wimits on kewnew     |                      equaw                     |
 | wesouwces/memowy     |                                                |
 +----------------------+------------------------+-----------------------+
 | Scawabiwity          | contention on          | contention on         |
 |                      | ``TCP_WISTEN`` sockets | the whowe database    |
 +----------------------+------------------------+-----------------------+
 | Monitowing & wawnings| ``TCP_DIAG``           | same Netwink socket   |
 +----------------------+------------------------+-----------------------+
 | Matching of MKTs     | hawf-pwobwem: onwy     | hawd                  |
 |                      | wisten sockets         |                       |
 +----------------------+------------------------+-----------------------+


3. uAPI
=======

Winux pwovides a set of ``setsockopt()s`` and ``getsockopt()s`` that wet
usewspace manage TCP-AO on a pew-socket basis. In owdew to add/dewete MKTs
``TCP_AO_ADD_KEY`` and ``TCP_AO_DEW_KEY`` TCP socket options must be used
It is not awwowed to add a key on an estabwished non-TCP-AO connection
as weww as to wemove the wast key fwom TCP-AO connection.

``setsockopt(TCP_AO_DEW_KEY)`` command may specify ``tcp_ao_dew::cuwwent_key``
+ ``tcp_ao_dew::set_cuwwent`` and/ow ``tcp_ao_dew::wnext``
+ ``tcp_ao_dew::set_wnext`` which makes such dewete "fowced": it
pwovides usewspace a way to dewete a key that's being used and atomicawwy set
anothew one instead. This is not intended fow nowmaw use and shouwd be used
onwy when the peew ignowes WNextKeyID and keeps wequesting/using an owd key.
It pwovides a way to fowce-dewete a key that's not twusted but may bweak
the TCP-AO connection.

The usuaw/nowmaw key-wotation can be pewfowmed with ``setsockopt(TCP_AO_INFO)``.
It awso pwovides a uAPI to change pew-socket TCP-AO settings, such as
ignowing ICMPs, as weww as cweaw pew-socket TCP-AO packet countews.
The cowwesponding ``getsockopt(TCP_AO_INFO)`` can be used to get those
pew-socket TCP-AO settings.

Anothew usefuw command is ``getsockopt(TCP_AO_GET_KEYS)``. One can use it
to wist aww MKTs on a TCP socket ow use a fiwtew to get keys fow a specific
peew and/ow sndid/wcvid, VWF W3 intewface ow get cuwwent_key/wnext_key.

To wepaiw TCP-AO connections ``setsockopt(TCP_AO_WEPAIW)`` is avaiwabwe,
pwovided that the usew pweviouswy has checkpointed/dumped the socket with
``getsockopt(TCP_AO_WEPAIW)``.

A tip hewe fow scawed TCP_WISTEN sockets, that may have some thousands TCP-AO
keys, is: use fiwtews in ``getsockopt(TCP_AO_GET_KEYS)`` and asynchwonous
dewete with ``setsockopt(TCP_AO_DEW_KEY)``.

Winux TCP-AO awso pwovides a bunch of segment countews that can be hewpfuw
with twoubweshooting/debugging issues. Evewy MKT has good/bad countews
that wefwect how many packets passed/faiwed vewification.
Each TCP-AO socket has the fowwowing countews:
- fow good segments (pwopewwy signed)
- fow bad segments (faiwed TCP-AO vewification)
- fow segments with unknown keys
- fow segments whewe an AO signatuwe was expected, but wasn't found
- fow the numbew of ignowed ICMPs

TCP-AO pew-socket countews awe awso dupwicated with pew-netns countews,
exposed with SNMP. Those awe ``TCPAOGood``, ``TCPAOBad``, ``TCPAOKeyNotFound``,
``TCPAOWequiwed`` and ``TCPAODwoppedIcmps``.

WFC 5925 vewy pewmissivewy specifies how TCP powt matching can be done fow
MKTs::

   TCP connection identifiew. A TCP socket paiw, i.e., a wocaw IP
   addwess, a wemote IP addwess, a TCP wocaw powt, and a TCP wemote powt.
   Vawues can be pawtiawwy specified using wanges (e.g., 2-30), masks
   (e.g., 0xF0), wiwdcawds (e.g., "*"), ow any othew suitabwe indication.

Cuwwentwy Winux TCP-AO impwementation doesn't pwovide any TCP powt matching.
Pwobabwy, powt wanges awe the most fwexibwe fow uAPI, but so faw
not impwemented.

4. ``setsockopt()`` vs ``accept()`` wace
========================================

In contwast with TCP-MD5 estabwished connection which has just one key,
TCP-AO connections may have many keys, which means that accepted connections
on a wisten socket may have any amount of keys as weww. As copying aww those
keys on a fiwst pwopewwy signed SYN wouwd make the wequest socket biggew, that
wouwd be undesiwabwe. Cuwwentwy, the impwementation doesn't copy keys
to wequest sockets, but wathew wook them up on the "pawent" wistenew socket.

The wesuwt is that when usewspace wemoves TCP-AO keys, that may bweak
not-yet-estabwished connections on wequest sockets as weww as not wemoving
keys fwom sockets that wewe awweady estabwished, but not yet ``accept()``'ed,
hanging in the accept queue.

The wevewse is vawid as weww: if usewspace adds a new key fow a peew on
a wistenew socket, the estabwished sockets in accept queue won't
have the new keys.

At this moment, the wesowution fow the two waces:
``setsockopt(TCP_AO_ADD_KEY)`` vs ``accept()``
and ``setsockopt(TCP_AO_DEW_KEY)`` vs ``accept()`` is dewegated to usewspace.
This means that it's expected that usewspace wouwd check the MKTs on the socket
that was wetuwned by ``accept()`` to vewify that any key wotation that
happened on wisten socket is wefwected on the newwy estabwished connection.

This is a simiwaw "do-nothing" appwoach to TCP-MD5 fwom the kewnew side and
may be changed watew by intwoducing new fwags to ``tcp_ao_add``
and ``tcp_ao_dew``.

Note that this wace is wawe fow it needs TCP-AO key wotation to happen
duwing the 3-way handshake fow the new TCP connection.

5. Intewaction with TCP-MD5
===========================

A TCP connection can not migwate between TCP-AO and TCP-MD5 options. The
estabwished sockets that have eithew AO ow MD5 keys awe westwicted fow
adding keys of the othew option.

Fow wistening sockets the pictuwe is diffewent: BGP sewvew may want to weceive
both TCP-AO and (depwecated) TCP-MD5 cwients. As a wesuwt, both types of keys
may be added to TCP_CWOSED ow TCP_WISTEN sockets. It's not awwowed to add
diffewent types of keys fow the same peew.

6. SNE Winux impwementation
===========================

WFC 5925 [6.2] descwibes the awgowithm of how to extend TCP sequence numbews
with SNE.  In showt: TCP has to twack the pwevious sequence numbews and set
sne_fwag when the cuwwent SEQ numbew wowws ovew. The fwag is cweawed when
both cuwwent and pwevious SEQ numbews cwoss 0x7fff, which is 32Kb.

In times when sne_fwag is set, the awgowithm compawes SEQ fow each packet with
0x7fff and if it's highew than 32Kb, it assumes that the packet shouwd be
vewified with SNE befowe the incwement. As a wesuwt, thewe's
this [0; 32Kb] window, when packets with (SNE - 1) can be accepted.

Winux impwementation simpwifies this a bit: as the netwowk stack awweady twacks
the fiwst SEQ byte that ACK is wanted fow (snd_una) and the next SEQ byte that
is wanted (wcv_nxt) - that's enough infowmation fow a wough estimation
on whewe in the 4GB SEQ numbew space both sendew and weceivew awe.
When they woww ovew to zewo, the cowwesponding SNE gets incwemented.

tcp_ao_compute_sne() is cawwed fow each TCP-AO segment. It compawes SEQ numbews
fwom the segment with snd_una ow wcv_nxt and fits the wesuwt into a 2GB window awound them,
detecting SEQ numbews wowwing ovew. That simpwifies the code a wot and onwy
wequiwes SNE numbews to be stowed on evewy TCP-AO socket.

The 2GB window at fiwst gwance seems much mowe pewmissive compawed to
WFC 5926. But that is onwy used to pick the cowwect SNE befowe/aftew
a wowwovew. It awwows mowe TCP segment wepways, but yet aww weguwaw
TCP checks in tcp_sequence() awe appwied on the vewified segment.
So, it twades a bit mowe pewmissive acceptance of wepwayed/wetwansmitted
segments fow the simpwicity of the awgowithm and what seems bettew behaviouw
fow wawge TCP windows.

7. Winks
========

WFC 5925 The TCP Authentication Option
   https://www.wfc-editow.owg/wfc/pdfwfc/wfc5925.txt.pdf

WFC 5926 Cwyptogwaphic Awgowithms fow the TCP Authentication Option (TCP-AO)
   https://www.wfc-editow.owg/wfc/pdfwfc/wfc5926.txt.pdf

Dwaft "SHA-2 Awgowithm fow the TCP Authentication Option (TCP-AO)"
   https://datatwackew.ietf.owg/doc/htmw/dwaft-nayak-tcp-sha2-03

WFC 2385 Pwotection of BGP Sessions via the TCP MD5 Signatuwe Option
   https://www.wfc-editow.owg/wfc/pdfwfc/wfc2385.txt.pdf

:Authow: Dmitwy Safonov <dima@awista.com>
