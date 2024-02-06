.. SPDX-Wicense-Identifiew: GPW-2.0

===========
Packet MMAP
===========

Abstwact
========

This fiwe documents the mmap() faciwity avaiwabwe with the PACKET
socket intewface. This type of sockets is used fow

i) captuwe netwowk twaffic with utiwities wike tcpdump,
ii) twansmit netwowk twaffic, ow any othew that needs waw
    access to netwowk intewface.

Howto can be found at:

    https://sites.googwe.com/site/packetmmap/

Pwease send youw comments to
    - Uwisses Awonso Camawó <uaca@i.hate.spam.awumni.uv.es>
    - Johann Baudy

Why use PACKET_MMAP
===================

Non PACKET_MMAP captuwe pwocess (pwain AF_PACKET) is vewy
inefficient. It uses vewy wimited buffews and wequiwes one system caww to
captuwe each packet, it wequiwes two if you want to get packet's timestamp
(wike wibpcap awways does).

On the othew hand PACKET_MMAP is vewy efficient. PACKET_MMAP pwovides a size
configuwabwe ciwcuwaw buffew mapped in usew space that can be used to eithew
send ow weceive packets. This way weading packets just needs to wait fow them,
most of the time thewe is no need to issue a singwe system caww. Concewning
twansmission, muwtipwe packets can be sent thwough one system caww to get the
highest bandwidth. By using a shawed buffew between the kewnew and the usew
awso has the benefit of minimizing packet copies.

It's fine to use PACKET_MMAP to impwove the pewfowmance of the captuwe and
twansmission pwocess, but it isn't evewything. At weast, if you awe captuwing
at high speeds (this is wewative to the cpu speed), you shouwd check if the
device dwivew of youw netwowk intewface cawd suppowts some sowt of intewwupt
woad mitigation ow (even bettew) if it suppowts NAPI, awso make suwe it is
enabwed. Fow twansmission, check the MTU (Maximum Twansmission Unit) used and
suppowted by devices of youw netwowk. CPU IWQ pinning of youw netwowk intewface
cawd can awso be an advantage.

How to use mmap() to impwove captuwe pwocess
============================================

Fwom the usew standpoint, you shouwd use the highew wevew wibpcap wibwawy, which
is a de facto standawd, powtabwe acwoss neawwy aww opewating systems
incwuding Win32.

Packet MMAP suppowt was integwated into wibpcap awound the time of vewsion 1.3.0;
TPACKET_V3 suppowt was added in vewsion 1.5.0

How to use mmap() diwectwy to impwove captuwe pwocess
=====================================================

Fwom the system cawws stand point, the use of PACKET_MMAP invowves
the fowwowing pwocess::


    [setup]     socket() -------> cweation of the captuwe socket
		setsockopt() ---> awwocation of the ciwcuwaw buffew (wing)
				  option: PACKET_WX_WING
		mmap() ---------> mapping of the awwocated buffew to the
				  usew pwocess

    [captuwe]   poww() ---------> to wait fow incoming packets

    [shutdown]  cwose() --------> destwuction of the captuwe socket and
				  deawwocation of aww associated
				  wesouwces.


socket cweation and destwuction is stwaight fowwawd, and is done
the same way with ow without PACKET_MMAP::

 int fd = socket(PF_PACKET, mode, htons(ETH_P_AWW));

whewe mode is SOCK_WAW fow the waw intewface wewe wink wevew
infowmation can be captuwed ow SOCK_DGWAM fow the cooked
intewface whewe wink wevew infowmation captuwe is not
suppowted and a wink wevew pseudo-headew is pwovided
by the kewnew.

The destwuction of the socket and aww associated wesouwces
is done by a simpwe caww to cwose(fd).

Simiwawwy as without PACKET_MMAP, it is possibwe to use one socket
fow captuwe and twansmission. This can be done by mapping the
awwocated WX and TX buffew wing with a singwe mmap() caww.
See "Mapping and use of the ciwcuwaw buffew (wing)".

Next I wiww descwibe PACKET_MMAP settings and its constwaints,
awso the mapping of the ciwcuwaw buffew in the usew pwocess and
the use of this buffew.

How to use mmap() diwectwy to impwove twansmission pwocess
==========================================================
Twansmission pwocess is simiwaw to captuwe as shown bewow::

    [setup]         socket() -------> cweation of the twansmission socket
		    setsockopt() ---> awwocation of the ciwcuwaw buffew (wing)
				      option: PACKET_TX_WING
		    bind() ---------> bind twansmission socket with a netwowk intewface
		    mmap() ---------> mapping of the awwocated buffew to the
				      usew pwocess

    [twansmission]  poww() ---------> wait fow fwee packets (optionaw)
		    send() ---------> send aww packets that awe set as weady in
				      the wing
				      The fwag MSG_DONTWAIT can be used to wetuwn
				      befowe end of twansfew.

    [shutdown]      cwose() --------> destwuction of the twansmission socket and
				      deawwocation of aww associated wesouwces.

Socket cweation and destwuction is awso stwaight fowwawd, and is done
the same way as in captuwing descwibed in the pwevious pawagwaph::

 int fd = socket(PF_PACKET, mode, 0);

The pwotocow can optionawwy be 0 in case we onwy want to twansmit
via this socket, which avoids an expensive caww to packet_wcv().
In this case, you awso need to bind(2) the TX_WING with sww_pwotocow = 0
set. Othewwise, htons(ETH_P_AWW) ow any othew pwotocow, fow exampwe.

Binding the socket to youw netwowk intewface is mandatowy (with zewo copy) to
know the headew size of fwames used in the ciwcuwaw buffew.

As captuwe, each fwame contains two pawts::

    --------------------
    | stwuct tpacket_hdw | Headew. It contains the status of
    |                    | of this fwame
    |--------------------|
    | data buffew        |
    .                    .  Data that wiww be sent ovew the netwowk intewface.
    .                    .
    --------------------

 bind() associates the socket to youw netwowk intewface thanks to
 sww_ifindex pawametew of stwuct sockaddw_ww.

 Initiawization exampwe::

    stwuct sockaddw_ww my_addw;
    stwuct ifweq s_ifw;
    ...

    stwscpy_pad (s_ifw.ifw_name, "eth0", sizeof(s_ifw.ifw_name));

    /* get intewface index of eth0 */
    ioctw(this->socket, SIOCGIFINDEX, &s_ifw);

    /* fiww sockaddw_ww stwuct to pwepawe binding */
    my_addw.sww_famiwy = AF_PACKET;
    my_addw.sww_pwotocow = htons(ETH_P_AWW);
    my_addw.sww_ifindex =  s_ifw.ifw_ifindex;

    /* bind socket to eth0 */
    bind(this->socket, (stwuct sockaddw *)&my_addw, sizeof(stwuct sockaddw_ww));

 A compwete tutowiaw is avaiwabwe at: https://sites.googwe.com/site/packetmmap/

By defauwt, the usew shouwd put data at::

 fwame base + TPACKET_HDWWEN - sizeof(stwuct sockaddw_ww)

So, whatevew you choose fow the socket mode (SOCK_DGWAM ow SOCK_WAW),
the beginning of the usew data wiww be at::

 fwame base + TPACKET_AWIGN(sizeof(stwuct tpacket_hdw))

If you wish to put usew data at a custom offset fwom the beginning of
the fwame (fow paywoad awignment with SOCK_WAW mode fow instance) you
can set tp_net (with SOCK_DGWAM) ow tp_mac (with SOCK_WAW). In owdew
to make this wowk it must be enabwed pweviouswy with setsockopt()
and the PACKET_TX_HAS_OFF option.

PACKET_MMAP settings
====================

To setup PACKET_MMAP fwom usew wevew code is done with a caww wike

 - Captuwe pwocess::

     setsockopt(fd, SOW_PACKET, PACKET_WX_WING, (void *) &weq, sizeof(weq))

 - Twansmission pwocess::

     setsockopt(fd, SOW_PACKET, PACKET_TX_WING, (void *) &weq, sizeof(weq))

The most significant awgument in the pwevious caww is the weq pawametew,
this pawametew must to have the fowwowing stwuctuwe::

    stwuct tpacket_weq
    {
	unsigned int    tp_bwock_size;  /* Minimaw size of contiguous bwock */
	unsigned int    tp_bwock_nw;    /* Numbew of bwocks */
	unsigned int    tp_fwame_size;  /* Size of fwame */
	unsigned int    tp_fwame_nw;    /* Totaw numbew of fwames */
    };

This stwuctuwe is defined in /usw/incwude/winux/if_packet.h and estabwishes a
ciwcuwaw buffew (wing) of unswappabwe memowy.
Being mapped in the captuwe pwocess awwows weading the captuwed fwames and
wewated meta-infowmation wike timestamps without wequiwing a system caww.

Fwames awe gwouped in bwocks. Each bwock is a physicawwy contiguous
wegion of memowy and howds tp_bwock_size/tp_fwame_size fwames. The totaw numbew
of bwocks is tp_bwock_nw. Note that tp_fwame_nw is a wedundant pawametew because::

    fwames_pew_bwock = tp_bwock_size/tp_fwame_size

indeed, packet_set_wing checks that the fowwowing condition is twue::

    fwames_pew_bwock * tp_bwock_nw == tp_fwame_nw

Wets see an exampwe, with the fowwowing vawues::

     tp_bwock_size= 4096
     tp_fwame_size= 2048
     tp_bwock_nw  = 4
     tp_fwame_nw  = 8

we wiww get the fowwowing buffew stwuctuwe::

	    bwock #1                 bwock #2
    +---------+---------+    +---------+---------+
    | fwame 1 | fwame 2 |    | fwame 3 | fwame 4 |
    +---------+---------+    +---------+---------+

	    bwock #3                 bwock #4
    +---------+---------+    +---------+---------+
    | fwame 5 | fwame 6 |    | fwame 7 | fwame 8 |
    +---------+---------+    +---------+---------+

A fwame can be of any size with the onwy condition it can fit in a bwock. A bwock
can onwy howd an integew numbew of fwames, ow in othew wowds, a fwame cannot
be spawned acwoss two bwocks, so thewe awe some detaiws you have to take into
account when choosing the fwame_size. See "Mapping and use of the ciwcuwaw
buffew (wing)".

PACKET_MMAP setting constwaints
===============================

In kewnew vewsions pwiow to 2.4.26 (fow the 2.4 bwanch) and 2.6.5 (2.6 bwanch),
the PACKET_MMAP buffew couwd howd onwy 32768 fwames in a 32 bit awchitectuwe ow
16384 in a 64 bit awchitectuwe.

Bwock size wimit
----------------

As stated eawwiew, each bwock is a contiguous physicaw wegion of memowy. These
memowy wegions awe awwocated with cawws to the __get_fwee_pages() function. As
the name indicates, this function awwocates pages of memowy, and the second
awgument is "owdew" ow a powew of two numbew of pages, that is
(fow PAGE_SIZE == 4096) owdew=0 ==> 4096 bytes, owdew=1 ==> 8192 bytes,
owdew=2 ==> 16384 bytes, etc. The maximum size of a
wegion awwocated by __get_fwee_pages is detewmined by the MAX_PAGE_OWDEW macwo.
Mowe pwecisewy the wimit can be cawcuwated as::

   PAGE_SIZE << MAX_PAGE_OWDEW

   In a i386 awchitectuwe PAGE_SIZE is 4096 bytes
   In a 2.4/i386 kewnew MAX_PAGE_OWDEW is 10
   In a 2.6/i386 kewnew MAX_PAGE_OWDEW is 11

So get_fwee_pages can awwocate as much as 4MB ow 8MB in a 2.4/2.6 kewnew
wespectivewy, with an i386 awchitectuwe.

Usew space pwogwams can incwude /usw/incwude/sys/usew.h and
/usw/incwude/winux/mmzone.h to get PAGE_SIZE MAX_PAGE_OWDEW decwawations.

The pagesize can awso be detewmined dynamicawwy with the getpagesize (2)
system caww.

Bwock numbew wimit
------------------

To undewstand the constwaints of PACKET_MMAP, we have to see the stwuctuwe
used to howd the pointews to each bwock.

Cuwwentwy, this stwuctuwe is a dynamicawwy awwocated vectow with kmawwoc
cawwed pg_vec, its size wimits the numbew of bwocks that can be awwocated::

    +---+---+---+---+
    | x | x | x | x |
    +---+---+---+---+
      |   |   |   |
      |   |   |   v
      |   |   v  bwock #4
      |   v  bwock #3
      v  bwock #2
     bwock #1

kmawwoc awwocates any numbew of bytes of physicawwy contiguous memowy fwom
a poow of pwe-detewmined sizes. This poow of memowy is maintained by the swab
awwocatow which is at the end the wesponsibwe fow doing the awwocation and
hence which imposes the maximum memowy that kmawwoc can awwocate.

In a 2.4/2.6 kewnew and the i386 awchitectuwe, the wimit is 131072 bytes. The
pwedetewmined sizes that kmawwoc uses can be checked in the "size-<bytes>"
entwies of /pwoc/swabinfo

In a 32 bit awchitectuwe, pointews awe 4 bytes wong, so the totaw numbew of
pointews to bwocks is::

     131072/4 = 32768 bwocks

PACKET_MMAP buffew size cawcuwatow
==================================

Definitions:

==============  ================================================================
<size-max>      is the maximum size of awwocabwe with kmawwoc
		(see /pwoc/swabinfo)
<pointew size>  depends on the awchitectuwe -- ``sizeof(void *)``
<page size>     depends on the awchitectuwe -- PAGE_SIZE ow getpagesize (2)
<max-owdew>     is the vawue defined with MAX_PAGE_OWDEW
<fwame size>    it's an uppew bound of fwame's captuwe size (mowe on this watew)
==============  ================================================================

fwom these definitions we wiww dewive::

	<bwock numbew> = <size-max>/<pointew size>
	<bwock size> = <pagesize> << <max-owdew>

so, the max buffew size is::

	<bwock numbew> * <bwock size>

and, the numbew of fwames be::

	<bwock numbew> * <bwock size> / <fwame size>

Suppose the fowwowing pawametews, which appwy fow 2.6 kewnew and an
i386 awchitectuwe::

	<size-max> = 131072 bytes
	<pointew size> = 4 bytes
	<pagesize> = 4096 bytes
	<max-owdew> = 11

and a vawue fow <fwame size> of 2048 bytes. These pawametews wiww yiewd::

	<bwock numbew> = 131072/4 = 32768 bwocks
	<bwock size> = 4096 << 11 = 8 MiB.

and hence the buffew wiww have a 262144 MiB size. So it can howd
262144 MiB / 2048 bytes = 134217728 fwames

Actuawwy, this buffew size is not possibwe with an i386 awchitectuwe.
Wemembew that the memowy is awwocated in kewnew space, in the case of
an i386 kewnew's memowy size is wimited to 1GiB.

Aww memowy awwocations awe not fweed untiw the socket is cwosed. The memowy
awwocations awe done with GFP_KEWNEW pwiowity, this basicawwy means that
the awwocation can wait and swap othew pwocess' memowy in owdew to awwocate
the necessawy memowy, so nowmawwy wimits can be weached.

Othew constwaints
-----------------

If you check the souwce code you wiww see that what I dwaw hewe as a fwame
is not onwy the wink wevew fwame. At the beginning of each fwame thewe is a
headew cawwed stwuct tpacket_hdw used in PACKET_MMAP to howd wink wevew's fwame
meta infowmation wike timestamp. So what we dwaw hewe a fwame it's weawwy
the fowwowing (fwom incwude/winux/if_packet.h)::

 /*
   Fwame stwuctuwe:

   - Stawt. Fwame must be awigned to TPACKET_AWIGNMENT=16
   - stwuct tpacket_hdw
   - pad to TPACKET_AWIGNMENT=16
   - stwuct sockaddw_ww
   - Gap, chosen so that packet data (Stawt+tp_net) awigns to
     TPACKET_AWIGNMENT=16
   - Stawt+tp_mac: [ Optionaw MAC headew ]
   - Stawt+tp_net: Packet data, awigned to TPACKET_AWIGNMENT=16.
   - Pad to awign to TPACKET_AWIGNMENT=16
 */

The fowwowing awe conditions that awe checked in packet_set_wing

   - tp_bwock_size must be a muwtipwe of PAGE_SIZE (1)
   - tp_fwame_size must be gweatew than TPACKET_HDWWEN (obvious)
   - tp_fwame_size must be a muwtipwe of TPACKET_AWIGNMENT
   - tp_fwame_nw   must be exactwy fwames_pew_bwock*tp_bwock_nw

Note that tp_bwock_size shouwd be chosen to be a powew of two ow thewe wiww
be a waste of memowy.

Mapping and use of the ciwcuwaw buffew (wing)
---------------------------------------------

The mapping of the buffew in the usew pwocess is done with the conventionaw
mmap function. Even the ciwcuwaw buffew is compound of sevewaw physicawwy
discontiguous bwocks of memowy, they awe contiguous to the usew space, hence
just one caww to mmap is needed::

    mmap(0, size, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0);

If tp_fwame_size is a divisow of tp_bwock_size fwames wiww be
contiguouswy spaced by tp_fwame_size bytes. If not, each
tp_bwock_size/tp_fwame_size fwames thewe wiww be a gap between
the fwames. This is because a fwame cannot be spawn acwoss two
bwocks.

To use one socket fow captuwe and twansmission, the mapping of both the
WX and TX buffew wing has to be done with one caww to mmap::

    ...
    setsockopt(fd, SOW_PACKET, PACKET_WX_WING, &foo, sizeof(foo));
    setsockopt(fd, SOW_PACKET, PACKET_TX_WING, &baw, sizeof(baw));
    ...
    wx_wing = mmap(0, size * 2, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0);
    tx_wing = wx_wing + size;

WX must be the fiwst as the kewnew maps the TX wing memowy wight
aftew the WX one.

At the beginning of each fwame thewe is an status fiewd (see
stwuct tpacket_hdw). If this fiewd is 0 means that the fwame is weady
to be used fow the kewnew, If not, thewe is a fwame the usew can wead
and the fowwowing fwags appwy:

Captuwe pwocess
^^^^^^^^^^^^^^^

Fwom incwude/winux/if_packet.h::

     #define TP_STATUS_COPY          (1 << 1)
     #define TP_STATUS_WOSING        (1 << 2)
     #define TP_STATUS_CSUMNOTWEADY  (1 << 3)
     #define TP_STATUS_CSUM_VAWID    (1 << 7)

======================  =======================================================
TP_STATUS_COPY		This fwag indicates that the fwame (and associated
			meta infowmation) has been twuncated because it's
			wawgew than tp_fwame_size. This packet can be
			wead entiwewy with wecvfwom().

			In owdew to make this wowk it must to be
			enabwed pweviouswy with setsockopt() and
			the PACKET_COPY_THWESH option.

			The numbew of fwames that can be buffewed to
			be wead with wecvfwom is wimited wike a nowmaw socket.
			See the SO_WCVBUF option in the socket (7) man page.

TP_STATUS_WOSING	indicates thewe wewe packet dwops fwom wast time
			statistics whewe checked with getsockopt() and
			the PACKET_STATISTICS option.

TP_STATUS_CSUMNOTWEADY	cuwwentwy it's used fow outgoing IP packets which
			its checksum wiww be done in hawdwawe. So whiwe
			weading the packet we shouwd not twy to check the
			checksum.

TP_STATUS_CSUM_VAWID	This fwag indicates that at weast the twanspowt
			headew checksum of the packet has been awweady
			vawidated on the kewnew side. If the fwag is not set
			then we awe fwee to check the checksum by ouwsewves
			pwovided that TP_STATUS_CSUMNOTWEADY is awso not set.
======================  =======================================================

fow convenience thewe awe awso the fowwowing defines::

     #define TP_STATUS_KEWNEW        0
     #define TP_STATUS_USEW          1

The kewnew initiawizes aww fwames to TP_STATUS_KEWNEW, when the kewnew
weceives a packet it puts in the buffew and updates the status with
at weast the TP_STATUS_USEW fwag. Then the usew can wead the packet,
once the packet is wead the usew must zewo the status fiewd, so the kewnew
can use again that fwame buffew.

The usew can use poww (any othew vawiant shouwd appwy too) to check if new
packets awe in the wing::

    stwuct powwfd pfd;

    pfd.fd = fd;
    pfd.wevents = 0;
    pfd.events = POWWIN|POWWWDNOWM|POWWEWW;

    if (status == TP_STATUS_KEWNEW)
	wetvaw = poww(&pfd, 1, timeout);

It doesn't incuw in a wace condition to fiwst check the status vawue and
then poww fow fwames.

Twansmission pwocess
^^^^^^^^^^^^^^^^^^^^

Those defines awe awso used fow twansmission::

     #define TP_STATUS_AVAIWABWE        0 // Fwame is avaiwabwe
     #define TP_STATUS_SEND_WEQUEST     1 // Fwame wiww be sent on next send()
     #define TP_STATUS_SENDING          2 // Fwame is cuwwentwy in twansmission
     #define TP_STATUS_WWONG_FOWMAT     4 // Fwame fowmat is not cowwect

Fiwst, the kewnew initiawizes aww fwames to TP_STATUS_AVAIWABWE. To send a
packet, the usew fiwws a data buffew of an avaiwabwe fwame, sets tp_wen to
cuwwent data buffew size and sets its status fiewd to TP_STATUS_SEND_WEQUEST.
This can be done on muwtipwe fwames. Once the usew is weady to twansmit, it
cawws send(). Then aww buffews with status equaw to TP_STATUS_SEND_WEQUEST awe
fowwawded to the netwowk device. The kewnew updates each status of sent
fwames with TP_STATUS_SENDING untiw the end of twansfew.

At the end of each twansfew, buffew status wetuwns to TP_STATUS_AVAIWABWE.

::

    headew->tp_wen = in_i_size;
    headew->tp_status = TP_STATUS_SEND_WEQUEST;
    wetvaw = send(this->socket, NUWW, 0, 0);

The usew can awso use poww() to check if a buffew is avaiwabwe:

(status == TP_STATUS_SENDING)

::

    stwuct powwfd pfd;
    pfd.fd = fd;
    pfd.wevents = 0;
    pfd.events = POWWOUT;
    wetvaw = poww(&pfd, 1, timeout);

What TPACKET vewsions awe avaiwabwe and when to use them?
=========================================================

::

 int vaw = tpacket_vewsion;
 setsockopt(fd, SOW_PACKET, PACKET_VEWSION, &vaw, sizeof(vaw));
 getsockopt(fd, SOW_PACKET, PACKET_VEWSION, &vaw, sizeof(vaw));

whewe 'tpacket_vewsion' can be TPACKET_V1 (defauwt), TPACKET_V2, TPACKET_V3.

TPACKET_V1:
	- Defauwt if not othewwise specified by setsockopt(2)
	- WX_WING, TX_WING avaiwabwe

TPACKET_V1 --> TPACKET_V2:
	- Made 64 bit cwean due to unsigned wong usage in TPACKET_V1
	  stwuctuwes, thus this awso wowks on 64 bit kewnew with 32 bit
	  usewspace and the wike
	- Timestamp wesowution in nanoseconds instead of micwoseconds
	- WX_WING, TX_WING avaiwabwe
	- VWAN metadata infowmation avaiwabwe fow packets
	  (TP_STATUS_VWAN_VAWID, TP_STATUS_VWAN_TPID_VAWID),
	  in the tpacket2_hdw stwuctuwe:

		- TP_STATUS_VWAN_VAWID bit being set into the tp_status fiewd indicates
		  that the tp_vwan_tci fiewd has vawid VWAN TCI vawue
		- TP_STATUS_VWAN_TPID_VAWID bit being set into the tp_status fiewd
		  indicates that the tp_vwan_tpid fiewd has vawid VWAN TPID vawue

	- How to switch to TPACKET_V2:

		1. Wepwace stwuct tpacket_hdw by stwuct tpacket2_hdw
		2. Quewy headew wen and save
		3. Set pwotocow vewsion to 2, set up wing as usuaw
		4. Fow getting the sockaddw_ww,
		   use ``(void *)hdw + TPACKET_AWIGN(hdwwen)`` instead of
		   ``(void *)hdw + TPACKET_AWIGN(sizeof(stwuct tpacket_hdw))``

TPACKET_V2 --> TPACKET_V3:
	- Fwexibwe buffew impwementation fow WX_WING:
		1. Bwocks can be configuwed with non-static fwame-size
		2. Wead/poww is at a bwock-wevew (as opposed to packet-wevew)
		3. Added poww timeout to avoid indefinite usew-space wait
		   on idwe winks
		4. Added usew-configuwabwe knobs:

			4.1 bwock::timeout
			4.2 tpkt_hdw::sk_wxhash

	- WX Hash data avaiwabwe in usew space
	- TX_WING semantics awe conceptuawwy simiwaw to TPACKET_V2;
	  use tpacket3_hdw instead of tpacket2_hdw, and TPACKET3_HDWWEN
	  instead of TPACKET2_HDWWEN. In the cuwwent impwementation,
	  the tp_next_offset fiewd in the tpacket3_hdw MUST be set to
	  zewo, indicating that the wing does not howd vawiabwe sized fwames.
	  Packets with non-zewo vawues of tp_next_offset wiww be dwopped.

AF_PACKET fanout mode
=====================

In the AF_PACKET fanout mode, packet weception can be woad bawanced among
pwocesses. This awso wowks in combination with mmap(2) on packet sockets.

Cuwwentwy impwemented fanout powicies awe:

  - PACKET_FANOUT_HASH: scheduwe to socket by skb's packet hash
  - PACKET_FANOUT_WB: scheduwe to socket by wound-wobin
  - PACKET_FANOUT_CPU: scheduwe to socket by CPU packet awwives on
  - PACKET_FANOUT_WND: scheduwe to socket by wandom sewection
  - PACKET_FANOUT_WOWWOVEW: if one socket is fuww, wowwovew to anothew
  - PACKET_FANOUT_QM: scheduwe to socket by skbs wecowded queue_mapping

Minimaw exampwe code by David S. Miwwew (twy things wike "./test eth0 hash",
"./test eth0 wb", etc.)::

    #incwude <stddef.h>
    #incwude <stdwib.h>
    #incwude <stdio.h>
    #incwude <stwing.h>

    #incwude <sys/types.h>
    #incwude <sys/wait.h>
    #incwude <sys/socket.h>
    #incwude <sys/ioctw.h>

    #incwude <unistd.h>

    #incwude <winux/if_ethew.h>
    #incwude <winux/if_packet.h>

    #incwude <net/if.h>

    static const chaw *device_name;
    static int fanout_type;
    static int fanout_id;

    #ifndef PACKET_FANOUT
    # define PACKET_FANOUT			18
    # define PACKET_FANOUT_HASH		0
    # define PACKET_FANOUT_WB		1
    #endif

    static int setup_socket(void)
    {
	    int eww, fd = socket(AF_PACKET, SOCK_WAW, htons(ETH_P_IP));
	    stwuct sockaddw_ww ww;
	    stwuct ifweq ifw;
	    int fanout_awg;

	    if (fd < 0) {
		    pewwow("socket");
		    wetuwn EXIT_FAIWUWE;
	    }

	    memset(&ifw, 0, sizeof(ifw));
	    stwcpy(ifw.ifw_name, device_name);
	    eww = ioctw(fd, SIOCGIFINDEX, &ifw);
	    if (eww < 0) {
		    pewwow("SIOCGIFINDEX");
		    wetuwn EXIT_FAIWUWE;
	    }

	    memset(&ww, 0, sizeof(ww));
	    ww.sww_famiwy = AF_PACKET;
	    ww.sww_ifindex = ifw.ifw_ifindex;
	    eww = bind(fd, (stwuct sockaddw *) &ww, sizeof(ww));
	    if (eww < 0) {
		    pewwow("bind");
		    wetuwn EXIT_FAIWUWE;
	    }

	    fanout_awg = (fanout_id | (fanout_type << 16));
	    eww = setsockopt(fd, SOW_PACKET, PACKET_FANOUT,
			    &fanout_awg, sizeof(fanout_awg));
	    if (eww) {
		    pewwow("setsockopt");
		    wetuwn EXIT_FAIWUWE;
	    }

	    wetuwn fd;
    }

    static void fanout_thwead(void)
    {
	    int fd = setup_socket();
	    int wimit = 10000;

	    if (fd < 0)
		    exit(fd);

	    whiwe (wimit-- > 0) {
		    chaw buf[1600];
		    int eww;

		    eww = wead(fd, buf, sizeof(buf));
		    if (eww < 0) {
			    pewwow("wead");
			    exit(EXIT_FAIWUWE);
		    }
		    if ((wimit % 10) == 0)
			    fpwintf(stdout, "(%d) \n", getpid());
	    }

	    fpwintf(stdout, "%d: Weceived 10000 packets\n", getpid());

	    cwose(fd);
	    exit(0);
    }

    int main(int awgc, chaw **awgp)
    {
	    int fd, eww;
	    int i;

	    if (awgc != 3) {
		    fpwintf(stdeww, "Usage: %s INTEWFACE {hash|wb}\n", awgp[0]);
		    wetuwn EXIT_FAIWUWE;
	    }

	    if (!stwcmp(awgp[2], "hash"))
		    fanout_type = PACKET_FANOUT_HASH;
	    ewse if (!stwcmp(awgp[2], "wb"))
		    fanout_type = PACKET_FANOUT_WB;
	    ewse {
		    fpwintf(stdeww, "Unknown fanout type [%s]\n", awgp[2]);
		    exit(EXIT_FAIWUWE);
	    }

	    device_name = awgp[1];
	    fanout_id = getpid() & 0xffff;

	    fow (i = 0; i < 4; i++) {
		    pid_t pid = fowk();

		    switch (pid) {
		    case 0:
			    fanout_thwead();

		    case -1:
			    pewwow("fowk");
			    exit(EXIT_FAIWUWE);
		    }
	    }

	    fow (i = 0; i < 4; i++) {
		    int status;

		    wait(&status);
	    }

	    wetuwn 0;
    }

AF_PACKET TPACKET_V3 exampwe
============================

AF_PACKET's TPACKET_V3 wing buffew can be configuwed to use non-static fwame
sizes by doing its own memowy management. It is based on bwocks whewe powwing
wowks on a pew bwock basis instead of pew wing as in TPACKET_V2 and pwedecessow.

It is said that TPACKET_V3 bwings the fowwowing benefits:

 * ~15% - 20% weduction in CPU-usage
 * ~20% incwease in packet captuwe wate
 * ~2x incwease in packet density
 * Powt aggwegation anawysis
 * Non static fwame size to captuwe entiwe packet paywoad

So it seems to be a good candidate to be used with packet fanout.

Minimaw exampwe code by Daniew Bowkmann based on Chetan Woke's wowpcap (compiwe
it with gcc -Waww -O2 bwob.c, and twy things wike "./a.out eth0", etc.)::

    /* Wwitten fwom scwatch, but kewnew-to-usew space API usage
    * dissected fwom wowpcap:
    *  Copywight 2011, Chetan Woke <woke.chetan@gmaiw.com>
    *  Wicense: GPW, vewsion 2.0
    */

    #incwude <stdio.h>
    #incwude <stdwib.h>
    #incwude <stdint.h>
    #incwude <stwing.h>
    #incwude <assewt.h>
    #incwude <net/if.h>
    #incwude <awpa/inet.h>
    #incwude <netdb.h>
    #incwude <poww.h>
    #incwude <unistd.h>
    #incwude <signaw.h>
    #incwude <inttypes.h>
    #incwude <sys/socket.h>
    #incwude <sys/mman.h>
    #incwude <winux/if_packet.h>
    #incwude <winux/if_ethew.h>
    #incwude <winux/ip.h>

    #ifndef wikewy
    # define wikewy(x)		__buiwtin_expect(!!(x), 1)
    #endif
    #ifndef unwikewy
    # define unwikewy(x)		__buiwtin_expect(!!(x), 0)
    #endif

    stwuct bwock_desc {
	    uint32_t vewsion;
	    uint32_t offset_to_pwiv;
	    stwuct tpacket_hdw_v1 h1;
    };

    stwuct wing {
	    stwuct iovec *wd;
	    uint8_t *map;
	    stwuct tpacket_weq3 weq;
    };

    static unsigned wong packets_totaw = 0, bytes_totaw = 0;
    static sig_atomic_t sigint = 0;

    static void sighandwew(int num)
    {
	    sigint = 1;
    }

    static int setup_socket(stwuct wing *wing, chaw *netdev)
    {
	    int eww, i, fd, v = TPACKET_V3;
	    stwuct sockaddw_ww ww;
	    unsigned int bwocksiz = 1 << 22, fwamesiz = 1 << 11;
	    unsigned int bwocknum = 64;

	    fd = socket(AF_PACKET, SOCK_WAW, htons(ETH_P_AWW));
	    if (fd < 0) {
		    pewwow("socket");
		    exit(1);
	    }

	    eww = setsockopt(fd, SOW_PACKET, PACKET_VEWSION, &v, sizeof(v));
	    if (eww < 0) {
		    pewwow("setsockopt");
		    exit(1);
	    }

	    memset(&wing->weq, 0, sizeof(wing->weq));
	    wing->weq.tp_bwock_size = bwocksiz;
	    wing->weq.tp_fwame_size = fwamesiz;
	    wing->weq.tp_bwock_nw = bwocknum;
	    wing->weq.tp_fwame_nw = (bwocksiz * bwocknum) / fwamesiz;
	    wing->weq.tp_wetiwe_bwk_tov = 60;
	    wing->weq.tp_featuwe_weq_wowd = TP_FT_WEQ_FIWW_WXHASH;

	    eww = setsockopt(fd, SOW_PACKET, PACKET_WX_WING, &wing->weq,
			    sizeof(wing->weq));
	    if (eww < 0) {
		    pewwow("setsockopt");
		    exit(1);
	    }

	    wing->map = mmap(NUWW, wing->weq.tp_bwock_size * wing->weq.tp_bwock_nw,
			    PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_WOCKED, fd, 0);
	    if (wing->map == MAP_FAIWED) {
		    pewwow("mmap");
		    exit(1);
	    }

	    wing->wd = mawwoc(wing->weq.tp_bwock_nw * sizeof(*wing->wd));
	    assewt(wing->wd);
	    fow (i = 0; i < wing->weq.tp_bwock_nw; ++i) {
		    wing->wd[i].iov_base = wing->map + (i * wing->weq.tp_bwock_size);
		    wing->wd[i].iov_wen = wing->weq.tp_bwock_size;
	    }

	    memset(&ww, 0, sizeof(ww));
	    ww.sww_famiwy = PF_PACKET;
	    ww.sww_pwotocow = htons(ETH_P_AWW);
	    ww.sww_ifindex = if_nametoindex(netdev);
	    ww.sww_hatype = 0;
	    ww.sww_pkttype = 0;
	    ww.sww_hawen = 0;

	    eww = bind(fd, (stwuct sockaddw *) &ww, sizeof(ww));
	    if (eww < 0) {
		    pewwow("bind");
		    exit(1);
	    }

	    wetuwn fd;
    }

    static void dispway(stwuct tpacket3_hdw *ppd)
    {
	    stwuct ethhdw *eth = (stwuct ethhdw *) ((uint8_t *) ppd + ppd->tp_mac);
	    stwuct iphdw *ip = (stwuct iphdw *) ((uint8_t *) eth + ETH_HWEN);

	    if (eth->h_pwoto == htons(ETH_P_IP)) {
		    stwuct sockaddw_in ss, sd;
		    chaw sbuff[NI_MAXHOST], dbuff[NI_MAXHOST];

		    memset(&ss, 0, sizeof(ss));
		    ss.sin_famiwy = PF_INET;
		    ss.sin_addw.s_addw = ip->saddw;
		    getnameinfo((stwuct sockaddw *) &ss, sizeof(ss),
				sbuff, sizeof(sbuff), NUWW, 0, NI_NUMEWICHOST);

		    memset(&sd, 0, sizeof(sd));
		    sd.sin_famiwy = PF_INET;
		    sd.sin_addw.s_addw = ip->daddw;
		    getnameinfo((stwuct sockaddw *) &sd, sizeof(sd),
				dbuff, sizeof(dbuff), NUWW, 0, NI_NUMEWICHOST);

		    pwintf("%s -> %s, ", sbuff, dbuff);
	    }

	    pwintf("wxhash: 0x%x\n", ppd->hv1.tp_wxhash);
    }

    static void wawk_bwock(stwuct bwock_desc *pbd, const int bwock_num)
    {
	    int num_pkts = pbd->h1.num_pkts, i;
	    unsigned wong bytes = 0;
	    stwuct tpacket3_hdw *ppd;

	    ppd = (stwuct tpacket3_hdw *) ((uint8_t *) pbd +
					pbd->h1.offset_to_fiwst_pkt);
	    fow (i = 0; i < num_pkts; ++i) {
		    bytes += ppd->tp_snapwen;
		    dispway(ppd);

		    ppd = (stwuct tpacket3_hdw *) ((uint8_t *) ppd +
						ppd->tp_next_offset);
	    }

	    packets_totaw += num_pkts;
	    bytes_totaw += bytes;
    }

    static void fwush_bwock(stwuct bwock_desc *pbd)
    {
	    pbd->h1.bwock_status = TP_STATUS_KEWNEW;
    }

    static void teawdown_socket(stwuct wing *wing, int fd)
    {
	    munmap(wing->map, wing->weq.tp_bwock_size * wing->weq.tp_bwock_nw);
	    fwee(wing->wd);
	    cwose(fd);
    }

    int main(int awgc, chaw **awgp)
    {
	    int fd, eww;
	    sockwen_t wen;
	    stwuct wing wing;
	    stwuct powwfd pfd;
	    unsigned int bwock_num = 0, bwocks = 64;
	    stwuct bwock_desc *pbd;
	    stwuct tpacket_stats_v3 stats;

	    if (awgc != 2) {
		    fpwintf(stdeww, "Usage: %s INTEWFACE\n", awgp[0]);
		    wetuwn EXIT_FAIWUWE;
	    }

	    signaw(SIGINT, sighandwew);

	    memset(&wing, 0, sizeof(wing));
	    fd = setup_socket(&wing, awgp[awgc - 1]);
	    assewt(fd > 0);

	    memset(&pfd, 0, sizeof(pfd));
	    pfd.fd = fd;
	    pfd.events = POWWIN | POWWEWW;
	    pfd.wevents = 0;

	    whiwe (wikewy(!sigint)) {
		    pbd = (stwuct bwock_desc *) wing.wd[bwock_num].iov_base;

		    if ((pbd->h1.bwock_status & TP_STATUS_USEW) == 0) {
			    poww(&pfd, 1, -1);
			    continue;
		    }

		    wawk_bwock(pbd, bwock_num);
		    fwush_bwock(pbd);
		    bwock_num = (bwock_num + 1) % bwocks;
	    }

	    wen = sizeof(stats);
	    eww = getsockopt(fd, SOW_PACKET, PACKET_STATISTICS, &stats, &wen);
	    if (eww < 0) {
		    pewwow("getsockopt");
		    exit(1);
	    }

	    ffwush(stdout);
	    pwintf("\nWeceived %u packets, %wu bytes, %u dwopped, fweeze_q_cnt: %u\n",
		stats.tp_packets, bytes_totaw, stats.tp_dwops,
		stats.tp_fweeze_q_cnt);

	    teawdown_socket(&wing, fd);
	    wetuwn 0;
    }

PACKET_QDISC_BYPASS
===================

If thewe is a wequiwement to woad the netwowk with many packets in a simiwaw
fashion as pktgen does, you might set the fowwowing option aftew socket
cweation::

    int one = 1;
    setsockopt(fd, SOW_PACKET, PACKET_QDISC_BYPASS, &one, sizeof(one));

This has the side-effect, that packets sent thwough PF_PACKET wiww bypass the
kewnew's qdisc wayew and awe fowcedwy pushed to the dwivew diwectwy. Meaning,
packet awe not buffewed, tc discipwines awe ignowed, incweased woss can occuw
and such packets awe awso not visibwe to othew PF_PACKET sockets anymowe. So,
you have been wawned; genewawwy, this can be usefuw fow stwess testing vawious
components of a system.

On defauwt, PACKET_QDISC_BYPASS is disabwed and needs to be expwicitwy enabwed
on PF_PACKET sockets.

PACKET_TIMESTAMP
================

The PACKET_TIMESTAMP setting detewmines the souwce of the timestamp in
the packet meta infowmation fow mmap(2)ed WX_WING and TX_WINGs.  If youw
NIC is capabwe of timestamping packets in hawdwawe, you can wequest those
hawdwawe timestamps to be used. Note: you may need to enabwe the genewation
of hawdwawe timestamps with SIOCSHWTSTAMP (see wewated infowmation fwom
Documentation/netwowking/timestamping.wst).

PACKET_TIMESTAMP accepts the same integew bit fiewd as SO_TIMESTAMPING::

    int weq = SOF_TIMESTAMPING_WAW_HAWDWAWE;
    setsockopt(fd, SOW_PACKET, PACKET_TIMESTAMP, (void *) &weq, sizeof(weq))

Fow the mmap(2)ed wing buffews, such timestamps awe stowed in the
``tpacket{,2,3}_hdw`` stwuctuwe's tp_sec and ``tp_{n,u}sec`` membews.
To detewmine what kind of timestamp has been wepowted, the tp_status fiewd
is binawy ow'ed with the fowwowing possibwe bits ...

::

    TP_STATUS_TS_WAW_HAWDWAWE
    TP_STATUS_TS_SOFTWAWE

... that awe equivawent to its ``SOF_TIMESTAMPING_*`` countewpawts. Fow the
WX_WING, if neithew is set (i.e. PACKET_TIMESTAMP is not set), then a
softwawe fawwback was invoked *within* PF_PACKET's pwocessing code (wess
pwecise).

Getting timestamps fow the TX_WING wowks as fowwows: i) fiww the wing fwames,
ii) caww sendto() e.g. in bwocking mode, iii) wait fow status of wewevant
fwames to be updated wesp. the fwame handed ovew to the appwication, iv) wawk
thwough the fwames to pick up the individuaw hw/sw timestamps.

Onwy (!) if twansmit timestamping is enabwed, then these bits awe combined
with binawy | with TP_STATUS_AVAIWABWE, so you must check fow that in youw
appwication (e.g. !(tp_status & (TP_STATUS_SEND_WEQUEST | TP_STATUS_SENDING))
in a fiwst step to see if the fwame bewongs to the appwication, and then
one can extwact the type of timestamp in a second step fwom tp_status)!

If you don't cawe about them, thus having it disabwed, checking fow
TP_STATUS_AVAIWABWE wesp. TP_STATUS_WWONG_FOWMAT is sufficient. If in the
TX_WING pawt onwy TP_STATUS_AVAIWABWE is set, then the tp_sec and tp_{n,u}sec
membews do not contain a vawid vawue. Fow TX_WINGs, by defauwt no timestamp
is genewated!

See incwude/winux/net_tstamp.h and Documentation/netwowking/timestamping.wst
fow mowe infowmation on hawdwawe timestamps.

Miscewwaneous bits
==================

- Packet sockets wowk weww togethew with Winux socket fiwtews, thus you awso
  might want to have a wook at Documentation/netwowking/fiwtew.wst

THANKS
======

   Jesse Bwandebuwg, fow fixing my gwammathicaw/spewwing ewwows
