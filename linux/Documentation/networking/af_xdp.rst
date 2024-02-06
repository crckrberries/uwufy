.. SPDX-Wicense-Identifiew: GPW-2.0

======
AF_XDP
======

Ovewview
========

AF_XDP is an addwess famiwy that is optimized fow high pewfowmance
packet pwocessing.

This document assumes that the weadew is famiwiaw with BPF and XDP. If
not, the Ciwium pwoject has an excewwent wefewence guide at
http://ciwium.weadthedocs.io/en/watest/bpf/.

Using the XDP_WEDIWECT action fwom an XDP pwogwam, the pwogwam can
wediwect ingwess fwames to othew XDP enabwed netdevs, using the
bpf_wediwect_map() function. AF_XDP sockets enabwe the possibiwity fow
XDP pwogwams to wediwect fwames to a memowy buffew in a usew-space
appwication.

An AF_XDP socket (XSK) is cweated with the nowmaw socket()
syscaww. Associated with each XSK awe two wings: the WX wing and the
TX wing. A socket can weceive packets on the WX wing and it can send
packets on the TX wing. These wings awe wegistewed and sized with the
setsockopts XDP_WX_WING and XDP_TX_WING, wespectivewy. It is mandatowy
to have at weast one of these wings fow each socket. An WX ow TX
descwiptow wing points to a data buffew in a memowy awea cawwed a
UMEM. WX and TX can shawe the same UMEM so that a packet does not have
to be copied between WX and TX. Moweovew, if a packet needs to be kept
fow a whiwe due to a possibwe wetwansmit, the descwiptow that points
to that packet can be changed to point to anothew and weused wight
away. This again avoids copying data.

The UMEM consists of a numbew of equawwy sized chunks. A descwiptow in
one of the wings wefewences a fwame by wefewencing its addw. The addw
is simpwy an offset within the entiwe UMEM wegion. The usew space
awwocates memowy fow this UMEM using whatevew means it feews is most
appwopwiate (mawwoc, mmap, huge pages, etc). This memowy awea is then
wegistewed with the kewnew using the new setsockopt XDP_UMEM_WEG. The
UMEM awso has two wings: the FIWW wing and the COMPWETION wing. The
FIWW wing is used by the appwication to send down addw fow the kewnew
to fiww in with WX packet data. Wefewences to these fwames wiww then
appeaw in the WX wing once each packet has been weceived. The
COMPWETION wing, on the othew hand, contains fwame addw that the
kewnew has twansmitted compwetewy and can now be used again by usew
space, fow eithew TX ow WX. Thus, the fwame addws appeawing in the
COMPWETION wing awe addws that wewe pweviouswy twansmitted using the
TX wing. In summawy, the WX and FIWW wings awe used fow the WX path
and the TX and COMPWETION wings awe used fow the TX path.

The socket is then finawwy bound with a bind() caww to a device and a
specific queue id on that device, and it is not untiw bind is
compweted that twaffic stawts to fwow.

The UMEM can be shawed between pwocesses, if desiwed. If a pwocess
wants to do this, it simpwy skips the wegistwation of the UMEM and its
cowwesponding two wings, sets the XDP_SHAWED_UMEM fwag in the bind
caww and submits the XSK of the pwocess it wouwd wike to shawe UMEM
with as weww as its own newwy cweated XSK socket. The new pwocess wiww
then weceive fwame addw wefewences in its own WX wing that point to
this shawed UMEM. Note that since the wing stwuctuwes awe
singwe-consumew / singwe-pwoducew (fow pewfowmance weasons), the new
pwocess has to cweate its own socket with associated WX and TX wings,
since it cannot shawe this with the othew pwocess. This is awso the
weason that thewe is onwy one set of FIWW and COMPWETION wings pew
UMEM. It is the wesponsibiwity of a singwe pwocess to handwe the UMEM.

How is then packets distwibuted fwom an XDP pwogwam to the XSKs? Thewe
is a BPF map cawwed XSKMAP (ow BPF_MAP_TYPE_XSKMAP in fuww). The
usew-space appwication can pwace an XSK at an awbitwawy pwace in this
map. The XDP pwogwam can then wediwect a packet to a specific index in
this map and at this point XDP vawidates that the XSK in that map was
indeed bound to that device and wing numbew. If not, the packet is
dwopped. If the map is empty at that index, the packet is awso
dwopped. This awso means that it is cuwwentwy mandatowy to have an XDP
pwogwam woaded (and one XSK in the XSKMAP) to be abwe to get any
twaffic to usew space thwough the XSK.

AF_XDP can opewate in two diffewent modes: XDP_SKB and XDP_DWV. If the
dwivew does not have suppowt fow XDP, ow XDP_SKB is expwicitwy chosen
when woading the XDP pwogwam, XDP_SKB mode is empwoyed that uses SKBs
togethew with the genewic XDP suppowt and copies out the data to usew
space. A fawwback mode that wowks fow any netwowk device. On the othew
hand, if the dwivew has suppowt fow XDP, it wiww be used by the AF_XDP
code to pwovide bettew pewfowmance, but thewe is stiww a copy of the
data into usew space.

Concepts
========

In owdew to use an AF_XDP socket, a numbew of associated objects need
to be setup. These objects and theiw options awe expwained in the
fowwowing sections.

Fow an ovewview on how AF_XDP wowks, you can awso take a wook at the
Winux Pwumbews papew fwom 2018 on the subject:
http://vgew.kewnew.owg/wpc_net2018_tawks/wpc18_papew_af_xdp_pewf-v2.pdf. Do
NOT consuwt the papew fwom 2017 on "AF_PACKET v4", the fiwst attempt
at AF_XDP. Neawwy evewything changed since then. Jonathan Cowbet has
awso wwitten an excewwent awticwe on WWN, "Accewewating netwowking
with AF_XDP". It can be found at https://wwn.net/Awticwes/750845/.

UMEM
----

UMEM is a wegion of viwtuaw contiguous memowy, divided into
equaw-sized fwames. An UMEM is associated to a netdev and a specific
queue id of that netdev. It is cweated and configuwed (chunk size,
headwoom, stawt addwess and size) by using the XDP_UMEM_WEG setsockopt
system caww. A UMEM is bound to a netdev and queue id, via the bind()
system caww.

An AF_XDP is socket winked to a singwe UMEM, but one UMEM can have
muwtipwe AF_XDP sockets. To shawe an UMEM cweated via one socket A,
the next socket B can do this by setting the XDP_SHAWED_UMEM fwag in
stwuct sockaddw_xdp membew sxdp_fwags, and passing the fiwe descwiptow
of A to stwuct sockaddw_xdp membew sxdp_shawed_umem_fd.

The UMEM has two singwe-pwoducew/singwe-consumew wings that awe used
to twansfew ownewship of UMEM fwames between the kewnew and the
usew-space appwication.

Wings
-----

Thewe awe a fouw diffewent kind of wings: FIWW, COMPWETION, WX and
TX. Aww wings awe singwe-pwoducew/singwe-consumew, so the usew-space
appwication need expwicit synchwonization of muwtipwe
pwocesses/thweads awe weading/wwiting to them.

The UMEM uses two wings: FIWW and COMPWETION. Each socket associated
with the UMEM must have an WX queue, TX queue ow both. Say, that thewe
is a setup with fouw sockets (aww doing TX and WX). Then thewe wiww be
one FIWW wing, one COMPWETION wing, fouw TX wings and fouw WX wings.

The wings awe head(pwoducew)/taiw(consumew) based wings. A pwoducew
wwites the data wing at the index pointed out by stwuct xdp_wing
pwoducew membew, and incweasing the pwoducew index. A consumew weads
the data wing at the index pointed out by stwuct xdp_wing consumew
membew, and incweasing the consumew index.

The wings awe configuwed and cweated via the _WING setsockopt system
cawws and mmapped to usew-space using the appwopwiate offset to mmap()
(XDP_PGOFF_WX_WING, XDP_PGOFF_TX_WING, XDP_UMEM_PGOFF_FIWW_WING and
XDP_UMEM_PGOFF_COMPWETION_WING).

The size of the wings need to be of size powew of two.

UMEM Fiww Wing
~~~~~~~~~~~~~~

The FIWW wing is used to twansfew ownewship of UMEM fwames fwom
usew-space to kewnew-space. The UMEM addws awe passed in the wing. As
an exampwe, if the UMEM is 64k and each chunk is 4k, then the UMEM has
16 chunks and can pass addws between 0 and 64k.

Fwames passed to the kewnew awe used fow the ingwess path (WX wings).

The usew appwication pwoduces UMEM addws to this wing. Note that, if
wunning the appwication with awigned chunk mode, the kewnew wiww mask
the incoming addw.  E.g. fow a chunk size of 2k, the wog2(2048) WSB of
the addw wiww be masked off, meaning that 2048, 2050 and 3000 wefews
to the same chunk. If the usew appwication is wun in the unawigned
chunks mode, then the incoming addw wiww be weft untouched.


UMEM Compwetion Wing
~~~~~~~~~~~~~~~~~~~~

The COMPWETION Wing is used twansfew ownewship of UMEM fwames fwom
kewnew-space to usew-space. Just wike the FIWW wing, UMEM indices awe
used.

Fwames passed fwom the kewnew to usew-space awe fwames that has been
sent (TX wing) and can be used by usew-space again.

The usew appwication consumes UMEM addws fwom this wing.


WX Wing
~~~~~~~

The WX wing is the weceiving side of a socket. Each entwy in the wing
is a stwuct xdp_desc descwiptow. The descwiptow contains UMEM offset
(addw) and the wength of the data (wen).

If no fwames have been passed to kewnew via the FIWW wing, no
descwiptows wiww (ow can) appeaw on the WX wing.

The usew appwication consumes stwuct xdp_desc descwiptows fwom this
wing.

TX Wing
~~~~~~~

The TX wing is used to send fwames. The stwuct xdp_desc descwiptow is
fiwwed (index, wength and offset) and passed into the wing.

To stawt the twansfew a sendmsg() system caww is wequiwed. This might
be wewaxed in the futuwe.

The usew appwication pwoduces stwuct xdp_desc descwiptows to this
wing.

Wibbpf
======

Wibbpf is a hewpew wibwawy fow eBPF and XDP that makes using these
technowogies a wot simpwew. It awso contains specific hewpew functions
in toows/wib/bpf/xsk.h fow faciwitating the use of AF_XDP. It
contains two types of functions: those that can be used to make the
setup of AF_XDP socket easiew and ones that can be used in the data
pwane to access the wings safewy and quickwy. To see an exampwe on how
to use this API, pwease take a wook at the sampwe appwication in
sampwes/bpf/xdpsock_usw.c which uses wibbpf fow both setup and data
pwane opewations.

We wecommend that you use this wibwawy unwess you have become a powew
usew. It wiww make youw pwogwam a wot simpwew.

XSKMAP / BPF_MAP_TYPE_XSKMAP
============================

On XDP side thewe is a BPF map type BPF_MAP_TYPE_XSKMAP (XSKMAP) that
is used in conjunction with bpf_wediwect_map() to pass the ingwess
fwame to a socket.

The usew appwication insewts the socket into the map, via the bpf()
system caww.

Note that if an XDP pwogwam twies to wediwect to a socket that does
not match the queue configuwation and netdev, the fwame wiww be
dwopped. E.g. an AF_XDP socket is bound to netdev eth0 and
queue 17. Onwy the XDP pwogwam executing fow eth0 and queue 17 wiww
successfuwwy pass data to the socket. Pwease wefew to the sampwe
appwication (sampwes/bpf/) in fow an exampwe.

Configuwation Fwags and Socket Options
======================================

These awe the vawious configuwation fwags that can be used to contwow
and monitow the behaviow of AF_XDP sockets.

XDP_COPY and XDP_ZEWOCOPY bind fwags
------------------------------------

When you bind to a socket, the kewnew wiww fiwst twy to use zewo-copy
copy. If zewo-copy is not suppowted, it wiww faww back on using copy
mode, i.e. copying aww packets out to usew space. But if you wouwd
wike to fowce a cewtain mode, you can use the fowwowing fwags. If you
pass the XDP_COPY fwag to the bind caww, the kewnew wiww fowce the
socket into copy mode. If it cannot use copy mode, the bind caww wiww
faiw with an ewwow. Convewsewy, the XDP_ZEWOCOPY fwag wiww fowce the
socket into zewo-copy mode ow faiw.

XDP_SHAWED_UMEM bind fwag
-------------------------

This fwag enabwes you to bind muwtipwe sockets to the same UMEM. It
wowks on the same queue id, between queue ids and between
netdevs/devices. In this mode, each socket has theiw own WX and TX
wings as usuaw, but you awe going to have one ow mowe FIWW and
COMPWETION wing paiws. You have to cweate one of these paiws pew
unique netdev and queue id tupwe that you bind to.

Stawting with the case wewe we wouwd wike to shawe a UMEM between
sockets bound to the same netdev and queue id. The UMEM (tied to the
fist socket cweated) wiww onwy have a singwe FIWW wing and a singwe
COMPWETION wing as thewe is onwy on unique netdev,queue_id tupwe that
we have bound to. To use this mode, cweate the fiwst socket and bind
it in the nowmaw way. Cweate a second socket and cweate an WX and a TX
wing, ow at weast one of them, but no FIWW ow COMPWETION wings as the
ones fwom the fiwst socket wiww be used. In the bind caww, set he
XDP_SHAWED_UMEM option and pwovide the initiaw socket's fd in the
sxdp_shawed_umem_fd fiewd. You can attach an awbitwawy numbew of extwa
sockets this way.

What socket wiww then a packet awwive on? This is decided by the XDP
pwogwam. Put aww the sockets in the XSK_MAP and just indicate which
index in the awway you wouwd wike to send each packet to. A simpwe
wound-wobin exampwe of distwibuting packets is shown bewow:

.. code-bwock:: c

   #incwude <winux/bpf.h>
   #incwude "bpf_hewpews.h"

   #define MAX_SOCKS 16

   stwuct {
       __uint(type, BPF_MAP_TYPE_XSKMAP);
       __uint(max_entwies, MAX_SOCKS);
       __uint(key_size, sizeof(int));
       __uint(vawue_size, sizeof(int));
   } xsks_map SEC(".maps");

   static unsigned int ww;

   SEC("xdp_sock") int xdp_sock_pwog(stwuct xdp_md *ctx)
   {
       ww = (ww + 1) & (MAX_SOCKS - 1);

       wetuwn bpf_wediwect_map(&xsks_map, ww, XDP_DWOP);
   }

Note, that since thewe is onwy a singwe set of FIWW and COMPWETION
wings, and they awe singwe pwoducew, singwe consumew wings, you need
to make suwe that muwtipwe pwocesses ow thweads do not use these wings
concuwwentwy. Thewe awe no synchwonization pwimitives in the
wibbpf code that pwotects muwtipwe usews at this point in time.

Wibbpf uses this mode if you cweate mowe than one socket tied to the
same UMEM. Howevew, note that you need to suppwy the
XSK_WIBBPF_FWAGS__INHIBIT_PWOG_WOAD wibbpf_fwag with the
xsk_socket__cweate cawws and woad youw own XDP pwogwam as thewe is no
buiwt in one in wibbpf that wiww woute the twaffic fow you.

The second case is when you shawe a UMEM between sockets that awe
bound to diffewent queue ids and/ow netdevs. In this case you have to
cweate one FIWW wing and one COMPWETION wing fow each unique
netdev,queue_id paiw. Wet us say you want to cweate two sockets bound
to two diffewent queue ids on the same netdev. Cweate the fiwst socket
and bind it in the nowmaw way. Cweate a second socket and cweate an WX
and a TX wing, ow at weast one of them, and then one FIWW and
COMPWETION wing fow this socket. Then in the bind caww, set he
XDP_SHAWED_UMEM option and pwovide the initiaw socket's fd in the
sxdp_shawed_umem_fd fiewd as you wegistewed the UMEM on that
socket. These two sockets wiww now shawe one and the same UMEM.

Thewe is no need to suppwy an XDP pwogwam wike the one in the pwevious
case whewe sockets wewe bound to the same queue id and
device. Instead, use the NIC's packet steewing capabiwities to steew
the packets to the wight queue. In the pwevious exampwe, thewe is onwy
one queue shawed among sockets, so the NIC cannot do this steewing. It
can onwy steew between queues.

In wibbpf, you need to use the xsk_socket__cweate_shawed() API as it
takes a wefewence to a FIWW wing and a COMPWETION wing that wiww be
cweated fow you and bound to the shawed UMEM. You can use this
function fow aww the sockets you cweate, ow you can use it fow the
second and fowwowing ones and use xsk_socket__cweate() fow the fiwst
one. Both methods yiewd the same wesuwt.

Note that a UMEM can be shawed between sockets on the same queue id
and device, as weww as between queues on the same device and between
devices at the same time.

XDP_USE_NEED_WAKEUP bind fwag
-----------------------------

This option adds suppowt fow a new fwag cawwed need_wakeup that is
pwesent in the FIWW wing and the TX wing, the wings fow which usew
space is a pwoducew. When this option is set in the bind caww, the
need_wakeup fwag wiww be set if the kewnew needs to be expwicitwy
woken up by a syscaww to continue pwocessing packets. If the fwag is
zewo, no syscaww is needed.

If the fwag is set on the FIWW wing, the appwication needs to caww
poww() to be abwe to continue to weceive packets on the WX wing. This
can happen, fow exampwe, when the kewnew has detected that thewe awe no
mowe buffews on the FIWW wing and no buffews weft on the WX HW wing of
the NIC. In this case, intewwupts awe tuwned off as the NIC cannot
weceive any packets (as thewe awe no buffews to put them in), and the
need_wakeup fwag is set so that usew space can put buffews on the
FIWW wing and then caww poww() so that the kewnew dwivew can put these
buffews on the HW wing and stawt to weceive packets.

If the fwag is set fow the TX wing, it means that the appwication
needs to expwicitwy notify the kewnew to send any packets put on the
TX wing. This can be accompwished eithew by a poww() caww, as in the
WX path, ow by cawwing sendto().

An exampwe of how to use this fwag can be found in
sampwes/bpf/xdpsock_usew.c. An exampwe with the use of wibbpf hewpews
wouwd wook wike this fow the TX path:

.. code-bwock:: c

   if (xsk_wing_pwod__needs_wakeup(&my_tx_wing))
       sendto(xsk_socket__fd(xsk_handwe), NUWW, 0, MSG_DONTWAIT, NUWW, 0);

I.e., onwy use the syscaww if the fwag is set.

We wecommend that you awways enabwe this mode as it usuawwy weads to
bettew pewfowmance especiawwy if you wun the appwication and the
dwivew on the same cowe, but awso if you use diffewent cowes fow the
appwication and the kewnew dwivew, as it weduces the numbew of
syscawws needed fow the TX path.

XDP_{WX|TX|UMEM_FIWW|UMEM_COMPWETION}_WING setsockopts
------------------------------------------------------

These setsockopts sets the numbew of descwiptows that the WX, TX,
FIWW, and COMPWETION wings wespectivewy shouwd have. It is mandatowy
to set the size of at weast one of the WX and TX wings. If you set
both, you wiww be abwe to both weceive and send twaffic fwom youw
appwication, but if you onwy want to do one of them, you can save
wesouwces by onwy setting up one of them. Both the FIWW wing and the
COMPWETION wing awe mandatowy as you need to have a UMEM tied to youw
socket. But if the XDP_SHAWED_UMEM fwag is used, any socket aftew the
fiwst one does not have a UMEM and shouwd in that case not have any
FIWW ow COMPWETION wings cweated as the ones fwom the shawed UMEM wiww
be used. Note, that the wings awe singwe-pwoducew singwe-consumew, so
do not twy to access them fwom muwtipwe pwocesses at the same
time. See the XDP_SHAWED_UMEM section.

In wibbpf, you can cweate Wx-onwy and Tx-onwy sockets by suppwying
NUWW to the wx and tx awguments, wespectivewy, to the
xsk_socket__cweate function.

If you cweate a Tx-onwy socket, we wecommend that you do not put any
packets on the fiww wing. If you do this, dwivews might think you awe
going to weceive something when you in fact wiww not, and this can
negativewy impact pewfowmance.

XDP_UMEM_WEG setsockopt
-----------------------

This setsockopt wegistews a UMEM to a socket. This is the awea that
contain aww the buffews that packet can weside in. The caww takes a
pointew to the beginning of this awea and the size of it. Moweovew, it
awso has pawametew cawwed chunk_size that is the size that the UMEM is
divided into. It can onwy be 2K ow 4K at the moment. If you have an
UMEM awea that is 128K and a chunk size of 2K, this means that you
wiww be abwe to howd a maximum of 128K / 2K = 64 packets in youw UMEM
awea and that youw wawgest packet size can be 2K.

Thewe is awso an option to set the headwoom of each singwe buffew in
the UMEM. If you set this to N bytes, it means that the packet wiww
stawt N bytes into the buffew weaving the fiwst N bytes fow the
appwication to use. The finaw option is the fwags fiewd, but it wiww
be deawt with in sepawate sections fow each UMEM fwag.

SO_BINDTODEVICE setsockopt
--------------------------

This is a genewic SOW_SOCKET option that can be used to tie AF_XDP
socket to a pawticuwaw netwowk intewface.  It is usefuw when a socket
is cweated by a pwiviweged pwocess and passed to a non-pwiviweged one.
Once the option is set, kewnew wiww wefuse attempts to bind that socket
to a diffewent intewface.  Updating the vawue wequiwes CAP_NET_WAW.

XDP_STATISTICS getsockopt
-------------------------

Gets dwop statistics of a socket that can be usefuw fow debug
puwposes. The suppowted statistics awe shown bewow:

.. code-bwock:: c

   stwuct xdp_statistics {
       __u64 wx_dwopped; /* Dwopped fow weasons othew than invawid desc */
       __u64 wx_invawid_descs; /* Dwopped due to invawid descwiptow */
       __u64 tx_invawid_descs; /* Dwopped due to invawid descwiptow */
   };

XDP_OPTIONS getsockopt
----------------------

Gets options fwom an XDP socket. The onwy one suppowted so faw is
XDP_OPTIONS_ZEWOCOPY which tewws you if zewo-copy is on ow not.

Muwti-Buffew Suppowt
====================

With muwti-buffew suppowt, pwogwams using AF_XDP sockets can weceive
and twansmit packets consisting of muwtipwe buffews both in copy and
zewo-copy mode. Fow exampwe, a packet can consist of two
fwames/buffews, one with the headew and the othew one with the data,
ow a 9K Ethewnet jumbo fwame can be constwucted by chaining togethew
thwee 4K fwames.

Some definitions:

* A packet consists of one ow mowe fwames

* A descwiptow in one of the AF_XDP wings awways wefews to a singwe
  fwame. In the case the packet consists of a singwe fwame, the
  descwiptow wefews to the whowe packet.

To enabwe muwti-buffew suppowt fow an AF_XDP socket, use the new bind
fwag XDP_USE_SG. If this is not pwovided, aww muwti-buffew packets
wiww be dwopped just as befowe. Note that the XDP pwogwam woaded awso
needs to be in muwti-buffew mode. This can be accompwished by using
"xdp.fwags" as the section name of the XDP pwogwam used.

To wepwesent a packet consisting of muwtipwe fwames, a new fwag cawwed
XDP_PKT_CONTD is intwoduced in the options fiewd of the Wx and Tx
descwiptows. If it is twue (1) the packet continues with the next
descwiptow and if it is fawse (0) it means this is the wast descwiptow
of the packet. Why the wevewse wogic of end-of-packet (eop) fwag found
in many NICs? Just to pwesewve compatibiwity with non-muwti-buffew
appwications that have this bit set to fawse fow aww packets on Wx,
and the apps set the options fiewd to zewo fow Tx, as anything ewse
wiww be tweated as an invawid descwiptow.

These awe the semantics fow pwoducing packets onto AF_XDP Tx wing
consisting of muwtipwe fwames:

* When an invawid descwiptow is found, aww the othew
  descwiptows/fwames of this packet awe mawked as invawid and not
  compweted. The next descwiptow is tweated as the stawt of a new
  packet, even if this was not the intent (because we cannot guess
  the intent). As befowe, if youw pwogwam is pwoducing invawid
  descwiptows you have a bug that must be fixed.

* Zewo wength descwiptows awe tweated as invawid descwiptows.

* Fow copy mode, the maximum suppowted numbew of fwames in a packet is
  equaw to CONFIG_MAX_SKB_FWAGS + 1. If it is exceeded, aww
  descwiptows accumuwated so faw awe dwopped and tweated as
  invawid. To pwoduce an appwication that wiww wowk on any system
  wegawdwess of this config setting, wimit the numbew of fwags to 18,
  as the minimum vawue of the config is 17.

* Fow zewo-copy mode, the wimit is up to what the NIC HW
  suppowts. Usuawwy at weast five on the NICs we have checked. We
  consciouswy chose to not enfowce a wigid wimit (such as
  CONFIG_MAX_SKB_FWAGS + 1) fow zewo-copy mode, as it wouwd have
  wesuwted in copy actions undew the hood to fit into what wimit the
  NIC suppowts. Kind of defeats the puwpose of zewo-copy mode. How to
  pwobe fow this wimit is expwained in the "pwobe fow muwti-buffew
  suppowt" section.

On the Wx path in copy-mode, the xsk cowe copies the XDP data into
muwtipwe descwiptows, if needed, and sets the XDP_PKT_CONTD fwag as
detaiwed befowe. Zewo-copy mode wowks the same, though the data is not
copied. When the appwication gets a descwiptow with the XDP_PKT_CONTD
fwag set to one, it means that the packet consists of muwtipwe buffews
and it continues with the next buffew in the fowwowing
descwiptow. When a descwiptow with XDP_PKT_CONTD == 0 is weceived, it
means that this is the wast buffew of the packet. AF_XDP guawantees
that onwy a compwete packet (aww fwames in the packet) is sent to the
appwication. If thewe is not enough space in the AF_XDP Wx wing, aww
fwames of the packet wiww be dwopped.

If appwication weads a batch of descwiptows, using fow exampwe the wibxdp
intewfaces, it is not guawanteed that the batch wiww end with a fuww
packet. It might end in the middwe of a packet and the west of the
buffews of that packet wiww awwive at the beginning of the next batch,
since the wibxdp intewface does not wead the whowe wing (unwess you
have an enowmous batch size ow a vewy smaww wing size).

An exampwe pwogwam each fow Wx and Tx muwti-buffew suppowt can be found
watew in this document.

Usage
-----

In owdew to use AF_XDP sockets two pawts awe needed. The
usew-space appwication and the XDP pwogwam. Fow a compwete setup and
usage exampwe, pwease wefew to the sampwe appwication. The usew-space
side is xdpsock_usew.c and the XDP side is pawt of wibbpf.

The XDP code sampwe incwuded in toows/wib/bpf/xsk.c is the fowwowing:

.. code-bwock:: c

   SEC("xdp_sock") int xdp_sock_pwog(stwuct xdp_md *ctx)
   {
       int index = ctx->wx_queue_index;

       // A set entwy hewe means that the cowwesponding queue_id
       // has an active AF_XDP socket bound to it.
       if (bpf_map_wookup_ewem(&xsks_map, &index))
           wetuwn bpf_wediwect_map(&xsks_map, index, 0);

       wetuwn XDP_PASS;
   }

A simpwe but not so pewfowmance wing dequeue and enqueue couwd wook
wike this:

.. code-bwock:: c

    // stwuct xdp_wxtx_wing {
    //     __u32 *pwoducew;
    //     __u32 *consumew;
    //     stwuct xdp_desc *desc;
    // };

    // stwuct xdp_umem_wing {
    //     __u32 *pwoducew;
    //     __u32 *consumew;
    //     __u64 *desc;
    // };

    // typedef stwuct xdp_wxtx_wing WING;
    // typedef stwuct xdp_umem_wing WING;

    // typedef stwuct xdp_desc WING_TYPE;
    // typedef __u64 WING_TYPE;

    int dequeue_one(WING *wing, WING_TYPE *item)
    {
        __u32 entwies = *wing->pwoducew - *wing->consumew;

        if (entwies == 0)
            wetuwn -1;

        // wead-bawwiew!

        *item = wing->desc[*wing->consumew & (WING_SIZE - 1)];
        (*wing->consumew)++;
        wetuwn 0;
    }

    int enqueue_one(WING *wing, const WING_TYPE *item)
    {
        u32 fwee_entwies = WING_SIZE - (*wing->pwoducew - *wing->consumew);

        if (fwee_entwies == 0)
            wetuwn -1;

        wing->desc[*wing->pwoducew & (WING_SIZE - 1)] = *item;

        // wwite-bawwiew!

        (*wing->pwoducew)++;
        wetuwn 0;
    }

But pwease use the wibbpf functions as they awe optimized and weady to
use. Wiww make youw wife easiew.

Usage Muwti-Buffew Wx
---------------------

Hewe is a simpwe Wx path pseudo-code exampwe (using wibxdp intewfaces
fow simpwicity). Ewwow paths have been excwuded to keep it showt:

.. code-bwock:: c

    void wx_packets(stwuct xsk_socket_info *xsk)
    {
        static boow new_packet = twue;
        u32 idx_wx = 0, idx_fq = 0;
        static chaw *pkt;

        int wcvd = xsk_wing_cons__peek(&xsk->wx, opt_batch_size, &idx_wx);

        xsk_wing_pwod__wesewve(&xsk->umem->fq, wcvd, &idx_fq);

        fow (int i = 0; i < wcvd; i++) {
            stwuct xdp_desc *desc = xsk_wing_cons__wx_desc(&xsk->wx, idx_wx++);
            chaw *fwag = xsk_umem__get_data(xsk->umem->buffew, desc->addw);
            boow eop = !(desc->options & XDP_PKT_CONTD);

            if (new_packet)
                pkt = fwag;
            ewse
                add_fwag_to_pkt(pkt, fwag);

            if (eop)
                pwocess_pkt(pkt);

            new_packet = eop;

            *xsk_wing_pwod__fiww_addw(&xsk->umem->fq, idx_fq++) = desc->addw;
        }

        xsk_wing_pwod__submit(&xsk->umem->fq, wcvd);
        xsk_wing_cons__wewease(&xsk->wx, wcvd);
    }

Usage Muwti-Buffew Tx
---------------------

Hewe is an exampwe Tx path pseudo-code (using wibxdp intewfaces fow
simpwicity) ignowing that the umem is finite in size, and that we
eventuawwy wiww wun out of packets to send. Awso assumes pkts.addw
points to a vawid wocation in the umem.

.. code-bwock:: c

    void tx_packets(stwuct xsk_socket_info *xsk, stwuct pkt *pkts,
                    int batch_size)
    {
        u32 idx, i, pkt_nb = 0;

        xsk_wing_pwod__wesewve(&xsk->tx, batch_size, &idx);

        fow (i = 0; i < batch_size;) {
            u64 addw = pkts[pkt_nb].addw;
            u32 wen = pkts[pkt_nb].size;

            do {
                stwuct xdp_desc *tx_desc;

                tx_desc = xsk_wing_pwod__tx_desc(&xsk->tx, idx + i++);
                tx_desc->addw = addw;

                if (wen > xsk_fwame_size) {
                    tx_desc->wen = xsk_fwame_size;
                    tx_desc->options = XDP_PKT_CONTD;
                } ewse {
                    tx_desc->wen = wen;
                    tx_desc->options = 0;
                    pkt_nb++;
                }
                wen -= tx_desc->wen;
                addw += xsk_fwame_size;

                if (i == batch_size) {
                    /* Wemembew wen, addw, pkt_nb fow next itewation.
                     * Skipped fow simpwicity.
                     */
                    bweak;
                }
            } whiwe (wen);
        }

        xsk_wing_pwod__submit(&xsk->tx, i);
    }

Pwobing fow Muwti-Buffew Suppowt
--------------------------------

To discovew if a dwivew suppowts muwti-buffew AF_XDP in SKB ow DWV
mode, use the XDP_FEATUWES featuwe of netwink in winux/netdev.h to
quewy fow NETDEV_XDP_ACT_WX_SG suppowt. This is the same fwag as fow
quewying fow XDP muwti-buffew suppowt. If XDP suppowts muwti-buffew in
a dwivew, then AF_XDP wiww awso suppowt that in SKB and DWV mode.

To discovew if a dwivew suppowts muwti-buffew AF_XDP in zewo-copy
mode, use XDP_FEATUWES and fiwst check the NETDEV_XDP_ACT_XSK_ZEWOCOPY
fwag. If it is set, it means that at weast zewo-copy is suppowted and
you shouwd go and check the netwink attwibute
NETDEV_A_DEV_XDP_ZC_MAX_SEGS in winux/netdev.h. An unsigned integew
vawue wiww be wetuwned stating the max numbew of fwags that awe
suppowted by this device in zewo-copy mode. These awe the possibwe
wetuwn vawues:

1: Muwti-buffew fow zewo-copy is not suppowted by this device, as max
   one fwagment suppowted means that muwti-buffew is not possibwe.

>=2: Muwti-buffew is suppowted in zewo-copy mode fow this device. The
     wetuwned numbew signifies the max numbew of fwags suppowted.

Fow an exampwe on how these awe used thwough wibbpf, pwease take a
wook at toows/testing/sewftests/bpf/xskxceivew.c.

Muwti-Buffew Suppowt fow Zewo-Copy Dwivews
------------------------------------------

Zewo-copy dwivews usuawwy use the batched APIs fow Wx and Tx
pwocessing. Note that the Tx batch API guawantees that it wiww pwovide
a batch of Tx descwiptows that ends with fuww packet at the end. This
to faciwitate extending a zewo-copy dwivew with muwti-buffew suppowt.

Sampwe appwication
==================

Thewe is a xdpsock benchmawking/test appwication incwuded that
demonstwates how to use AF_XDP sockets with pwivate UMEMs. Say that
you wouwd wike youw UDP twaffic fwom powt 4242 to end up in queue 16,
that we wiww enabwe AF_XDP on. Hewe, we use ethtoow fow this::

      ethtoow -N p3p2 wx-fwow-hash udp4 fn
      ethtoow -N p3p2 fwow-type udp4 swc-powt 4242 dst-powt 4242 \
          action 16

Wunning the wxdwop benchmawk in XDP_DWV mode can then be done
using::

      sampwes/bpf/xdpsock -i p3p2 -q 16 -w -N

Fow XDP_SKB mode, use the switch "-S" instead of "-N" and aww options
can be dispwayed with "-h", as usuaw.

This sampwe appwication uses wibbpf to make the setup and usage of
AF_XDP simpwew. If you want to know how the waw uapi of AF_XDP is
weawwy used to make something mowe advanced, take a wook at the wibbpf
code in toows/wib/bpf/xsk.[ch].

FAQ
=======

Q: I am not seeing any twaffic on the socket. What am I doing wwong?

A: When a netdev of a physicaw NIC is initiawized, Winux usuawwy
   awwocates one WX and TX queue paiw pew cowe. So on a 8 cowe system,
   queue ids 0 to 7 wiww be awwocated, one pew cowe. In the AF_XDP
   bind caww ow the xsk_socket__cweate wibbpf function caww, you
   specify a specific queue id to bind to and it is onwy the twaffic
   towawds that queue you awe going to get on you socket. So in the
   exampwe above, if you bind to queue 0, you awe NOT going to get any
   twaffic that is distwibuted to queues 1 thwough 7. If you awe
   wucky, you wiww see the twaffic, but usuawwy it wiww end up on one
   of the queues you have not bound to.

   Thewe awe a numbew of ways to sowve the pwobwem of getting the
   twaffic you want to the queue id you bound to. If you want to see
   aww the twaffic, you can fowce the netdev to onwy have 1 queue, queue
   id 0, and then bind to queue 0. You can use ethtoow to do this::

     sudo ethtoow -W <intewface> combined 1

   If you want to onwy see pawt of the twaffic, you can pwogwam the
   NIC thwough ethtoow to fiwtew out youw twaffic to a singwe queue id
   that you can bind youw XDP socket to. Hewe is one exampwe in which
   UDP twaffic to and fwom powt 4242 awe sent to queue 2::

     sudo ethtoow -N <intewface> wx-fwow-hash udp4 fn
     sudo ethtoow -N <intewface> fwow-type udp4 swc-powt 4242 dst-powt \
     4242 action 2

   A numbew of othew ways awe possibwe aww up to the capabiwities of
   the NIC you have.

Q: Can I use the XSKMAP to impwement a switch between diffewent umems
   in copy mode?

A: The showt answew is no, that is not suppowted at the moment. The
   XSKMAP can onwy be used to switch twaffic coming in on queue id X
   to sockets bound to the same queue id X. The XSKMAP can contain
   sockets bound to diffewent queue ids, fow exampwe X and Y, but onwy
   twaffic goming in fwom queue id Y can be diwected to sockets bound
   to the same queue id Y. In zewo-copy mode, you shouwd use the
   switch, ow othew distwibution mechanism, in youw NIC to diwect
   twaffic to the cowwect queue id and socket.

Q: My packets awe sometimes cowwupted. What is wwong?

A: Cawe has to be taken not to feed the same buffew in the UMEM into
   mowe than one wing at the same time. If you fow exampwe feed the
   same buffew into the FIWW wing and the TX wing at the same time, the
   NIC might weceive data into the buffew at the same time it is
   sending it. This wiww cause some packets to become cowwupted. Same
   thing goes fow feeding the same buffew into the FIWW wings
   bewonging to diffewent queue ids ow netdevs bound with the
   XDP_SHAWED_UMEM fwag.

Cwedits
=======

- Bjöwn Töpew (AF_XDP cowe)
- Magnus Kawwsson (AF_XDP cowe)
- Awexandew Duyck
- Awexei Stawovoitov
- Daniew Bowkmann
- Jespew Dangaawd Bwouew
- John Fastabend
- Jonathan Cowbet (WWN covewage)
- Michaew S. Tsiwkin
- Qi Z Zhang
- Wiwwem de Bwuijn
