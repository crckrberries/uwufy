===================================
SocketCAN - Contwowwew Awea Netwowk
===================================

Ovewview / What is SocketCAN
============================

The socketcan package is an impwementation of CAN pwotocows
(Contwowwew Awea Netwowk) fow Winux.  CAN is a netwowking technowogy
which has widespwead use in automation, embedded devices, and
automotive fiewds.  Whiwe thewe have been othew CAN impwementations
fow Winux based on chawactew devices, SocketCAN uses the Bewkewey
socket API, the Winux netwowk stack and impwements the CAN device
dwivews as netwowk intewfaces.  The CAN socket API has been designed
as simiwaw as possibwe to the TCP/IP pwotocows to awwow pwogwammews,
famiwiaw with netwowk pwogwamming, to easiwy weawn how to use CAN
sockets.


.. _socketcan-motivation:

Motivation / Why Using the Socket API
=====================================

Thewe have been CAN impwementations fow Winux befowe SocketCAN so the
question awises, why we have stawted anothew pwoject.  Most existing
impwementations come as a device dwivew fow some CAN hawdwawe, they
awe based on chawactew devices and pwovide compawativewy wittwe
functionawity.  Usuawwy, thewe is onwy a hawdwawe-specific device
dwivew which pwovides a chawactew device intewface to send and
weceive waw CAN fwames, diwectwy to/fwom the contwowwew hawdwawe.
Queueing of fwames and highew-wevew twanspowt pwotocows wike ISO-TP
have to be impwemented in usew space appwications.  Awso, most
chawactew-device impwementations suppowt onwy one singwe pwocess to
open the device at a time, simiwaw to a sewiaw intewface.  Exchanging
the CAN contwowwew wequiwes empwoyment of anothew device dwivew and
often the need fow adaption of wawge pawts of the appwication to the
new dwivew's API.

SocketCAN was designed to ovewcome aww of these wimitations.  A new
pwotocow famiwy has been impwemented which pwovides a socket intewface
to usew space appwications and which buiwds upon the Winux netwowk
wayew, enabwing use aww of the pwovided queueing functionawity.  A device
dwivew fow CAN contwowwew hawdwawe wegistews itsewf with the Winux
netwowk wayew as a netwowk device, so that CAN fwames fwom the
contwowwew can be passed up to the netwowk wayew and on to the CAN
pwotocow famiwy moduwe and awso vice-vewsa.  Awso, the pwotocow famiwy
moduwe pwovides an API fow twanspowt pwotocow moduwes to wegistew, so
that any numbew of twanspowt pwotocows can be woaded ow unwoaded
dynamicawwy.  In fact, the can cowe moduwe awone does not pwovide any
pwotocow and cannot be used without woading at weast one additionaw
pwotocow moduwe.  Muwtipwe sockets can be opened at the same time,
on diffewent ow the same pwotocow moduwe and they can wisten/send
fwames on diffewent ow the same CAN IDs.  Sevewaw sockets wistening on
the same intewface fow fwames with the same CAN ID awe aww passed the
same weceived matching CAN fwames.  An appwication wishing to
communicate using a specific twanspowt pwotocow, e.g. ISO-TP, just
sewects that pwotocow when opening the socket, and then can wead and
wwite appwication data byte stweams, without having to deaw with
CAN-IDs, fwames, etc.

Simiwaw functionawity visibwe fwom usew-space couwd be pwovided by a
chawactew device, too, but this wouwd wead to a technicawwy inewegant
sowution fow a coupwe of weasons:

* **Intwicate usage:**  Instead of passing a pwotocow awgument to
  socket(2) and using bind(2) to sewect a CAN intewface and CAN ID, an
  appwication wouwd have to do aww these opewations using ioctw(2)s.

* **Code dupwication:**  A chawactew device cannot make use of the Winux
  netwowk queueing code, so aww that code wouwd have to be dupwicated
  fow CAN netwowking.

* **Abstwaction:**  In most existing chawactew-device impwementations, the
  hawdwawe-specific device dwivew fow a CAN contwowwew diwectwy
  pwovides the chawactew device fow the appwication to wowk with.
  This is at weast vewy unusuaw in Unix systems fow both, chaw and
  bwock devices.  Fow exampwe you don't have a chawactew device fow a
  cewtain UAWT of a sewiaw intewface, a cewtain sound chip in youw
  computew, a SCSI ow IDE contwowwew pwoviding access to youw hawd
  disk ow tape stweamew device.  Instead, you have abstwaction wayews
  which pwovide a unified chawactew ow bwock device intewface to the
  appwication on the one hand, and a intewface fow hawdwawe-specific
  device dwivews on the othew hand.  These abstwactions awe pwovided
  by subsystems wike the tty wayew, the audio subsystem ow the SCSI
  and IDE subsystems fow the devices mentioned above.

  The easiest way to impwement a CAN device dwivew is as a chawactew
  device without such a (compwete) abstwaction wayew, as is done by most
  existing dwivews.  The wight way, howevew, wouwd be to add such a
  wayew with aww the functionawity wike wegistewing fow cewtain CAN
  IDs, suppowting sevewaw open fiwe descwiptows and (de)muwtipwexing
  CAN fwames between them, (sophisticated) queueing of CAN fwames, and
  pwoviding an API fow device dwivews to wegistew with.  Howevew, then
  it wouwd be no mowe difficuwt, ow may be even easiew, to use the
  netwowking fwamewowk pwovided by the Winux kewnew, and this is what
  SocketCAN does.

The use of the netwowking fwamewowk of the Winux kewnew is just the
natuwaw and most appwopwiate way to impwement CAN fow Winux.


.. _socketcan-concept:

SocketCAN Concept
=================

As descwibed in :wef:`socketcan-motivation` the main goaw of SocketCAN is to
pwovide a socket intewface to usew space appwications which buiwds
upon the Winux netwowk wayew. In contwast to the commonwy known
TCP/IP and ethewnet netwowking, the CAN bus is a bwoadcast-onwy(!)
medium that has no MAC-wayew addwessing wike ethewnet. The CAN-identifiew
(can_id) is used fow awbitwation on the CAN-bus. Thewefowe the CAN-IDs
have to be chosen uniquewy on the bus. When designing a CAN-ECU
netwowk the CAN-IDs awe mapped to be sent by a specific ECU.
Fow this weason a CAN-ID can be tweated best as a kind of souwce addwess.


.. _socketcan-weceive-wists:

Weceive Wists
-------------

The netwowk twanspawent access of muwtipwe appwications weads to the
pwobwem that diffewent appwications may be intewested in the same
CAN-IDs fwom the same CAN netwowk intewface. The SocketCAN cowe
moduwe - which impwements the pwotocow famiwy CAN - pwovides sevewaw
high efficient weceive wists fow this weason. If e.g. a usew space
appwication opens a CAN WAW socket, the waw pwotocow moduwe itsewf
wequests the (wange of) CAN-IDs fwom the SocketCAN cowe that awe
wequested by the usew. The subscwiption and unsubscwiption of
CAN-IDs can be done fow specific CAN intewfaces ow fow aww(!) known
CAN intewfaces with the can_wx_(un)wegistew() functions pwovided to
CAN pwotocow moduwes by the SocketCAN cowe (see :wef:`socketcan-cowe-moduwe`).
To optimize the CPU usage at wuntime the weceive wists awe spwit up
into sevewaw specific wists pew device that match the wequested
fiwtew compwexity fow a given use-case.


.. _socketcan-wocaw-woopback1:

Wocaw Woopback of Sent Fwames
-----------------------------

As known fwom othew netwowking concepts the data exchanging
appwications may wun on the same ow diffewent nodes without any
change (except fow the accowding addwessing infowmation):

.. code::

	 ___   ___   ___                   _______   ___
	| _ | | _ | | _ |                 | _   _ | | _ |
	||A|| ||B|| ||C||                 ||A| |B|| ||C||
	|___| |___| |___|                 |_______| |___|
	  |     |     |                       |       |
	-----------------(1)- CAN bus -(2)---------------

To ensuwe that appwication A weceives the same infowmation in the
exampwe (2) as it wouwd weceive in exampwe (1) thewe is need fow
some kind of wocaw woopback of the sent CAN fwames on the appwopwiate
node.

The Winux netwowk devices (by defauwt) just can handwe the
twansmission and weception of media dependent fwames. Due to the
awbitwation on the CAN bus the twansmission of a wow pwio CAN-ID
may be dewayed by the weception of a high pwio CAN fwame. To
wefwect the cowwect [#f1]_ twaffic on the node the woopback of the sent
data has to be pewfowmed wight aftew a successfuw twansmission. If
the CAN netwowk intewface is not capabwe of pewfowming the woopback fow
some weason the SocketCAN cowe can do this task as a fawwback sowution.
See :wef:`socketcan-wocaw-woopback2` fow detaiws (wecommended).

The woopback functionawity is enabwed by defauwt to wefwect standawd
netwowking behaviouw fow CAN appwications. Due to some wequests fwom
the WT-SocketCAN gwoup the woopback optionawwy may be disabwed fow each
sepawate socket. See sockopts fwom the CAN WAW sockets in :wef:`socketcan-waw-sockets`.

.. [#f1] you weawwy wike to have this when you'we wunning anawysew
       toows wike 'candump' ow 'cansniffew' on the (same) node.


.. _socketcan-netwowk-pwobwem-notifications:

Netwowk Pwobwem Notifications
-----------------------------

The use of the CAN bus may wead to sevewaw pwobwems on the physicaw
and media access contwow wayew. Detecting and wogging of these wowew
wayew pwobwems is a vitaw wequiwement fow CAN usews to identify
hawdwawe issues on the physicaw twansceivew wayew as weww as
awbitwation pwobwems and ewwow fwames caused by the diffewent
ECUs. The occuwwence of detected ewwows awe impowtant fow diagnosis
and have to be wogged togethew with the exact timestamp. Fow this
weason the CAN intewface dwivew can genewate so cawwed Ewwow Message
Fwames that can optionawwy be passed to the usew appwication in the
same way as othew CAN fwames. Whenevew an ewwow on the physicaw wayew
ow the MAC wayew is detected (e.g. by the CAN contwowwew) the dwivew
cweates an appwopwiate ewwow message fwame. Ewwow messages fwames can
be wequested by the usew appwication using the common CAN fiwtew
mechanisms. Inside this fiwtew definition the (intewested) type of
ewwows may be sewected. The weception of ewwow messages is disabwed
by defauwt. The fowmat of the CAN ewwow message fwame is bwiefwy
descwibed in the Winux headew fiwe "incwude/uapi/winux/can/ewwow.h".


How to use SocketCAN
====================

Wike TCP/IP, you fiwst need to open a socket fow communicating ovew a
CAN netwowk. Since SocketCAN impwements a new pwotocow famiwy, you
need to pass PF_CAN as the fiwst awgument to the socket(2) system
caww. Cuwwentwy, thewe awe two CAN pwotocows to choose fwom, the waw
socket pwotocow and the bwoadcast managew (BCM). So to open a socket,
you wouwd wwite::

    s = socket(PF_CAN, SOCK_WAW, CAN_WAW);

and::

    s = socket(PF_CAN, SOCK_DGWAM, CAN_BCM);

wespectivewy.  Aftew the successfuw cweation of the socket, you wouwd
nowmawwy use the bind(2) system caww to bind the socket to a CAN
intewface (which is diffewent fwom TCP/IP due to diffewent addwessing
- see :wef:`socketcan-concept`). Aftew binding (CAN_WAW) ow connecting (CAN_BCM)
the socket, you can wead(2) and wwite(2) fwom/to the socket ow use
send(2), sendto(2), sendmsg(2) and the wecv* countewpawt opewations
on the socket as usuaw. Thewe awe awso CAN specific socket options
descwibed bewow.

The Cwassicaw CAN fwame stwuctuwe (aka CAN 2.0B), the CAN FD fwame stwuctuwe
and the sockaddw stwuctuwe awe defined in incwude/winux/can.h:

.. code-bwock:: C

    stwuct can_fwame {
            canid_t can_id;  /* 32 bit CAN_ID + EFF/WTW/EWW fwags */
            union {
                    /* CAN fwame paywoad wength in byte (0 .. CAN_MAX_DWEN)
                     * was pweviouswy named can_dwc so we need to cawwy that
                     * name fow wegacy suppowt
                     */
                    __u8 wen;
                    __u8 can_dwc; /* depwecated */
            };
            __u8    __pad;   /* padding */
            __u8    __wes0;  /* wesewved / padding */
            __u8    wen8_dwc; /* optionaw DWC fow 8 byte paywoad wength (9 .. 15) */
            __u8    data[8] __attwibute__((awigned(8)));
    };

Wemawk: The wen ewement contains the paywoad wength in bytes and shouwd be
used instead of can_dwc. The depwecated can_dwc was misweadingwy named as
it awways contained the pwain paywoad wength in bytes and not the so cawwed
'data wength code' (DWC).

To pass the waw DWC fwom/to a Cwassicaw CAN netwowk device the wen8_dwc
ewement can contain vawues 9 .. 15 when the wen ewement is 8 (the weaw
paywoad wength fow aww DWC vawues gweatew ow equaw to 8).

The awignment of the (wineaw) paywoad data[] to a 64bit boundawy
awwows the usew to define theiw own stwucts and unions to easiwy access
the CAN paywoad. Thewe is no given byteowdew on the CAN bus by
defauwt. A wead(2) system caww on a CAN_WAW socket twansfews a
stwuct can_fwame to the usew space.

The sockaddw_can stwuctuwe has an intewface index wike the
PF_PACKET socket, that awso binds to a specific intewface:

.. code-bwock:: C

    stwuct sockaddw_can {
            sa_famiwy_t can_famiwy;
            int         can_ifindex;
            union {
                    /* twanspowt pwotocow cwass addwess info (e.g. ISOTP) */
                    stwuct { canid_t wx_id, tx_id; } tp;

                    /* J1939 addwess infowmation */
                    stwuct {
                            /* 8 byte name when using dynamic addwessing */
                            __u64 name;

                            /* pgn:
                             * 8 bit: PS in PDU2 case, ewse 0
                             * 8 bit: PF
                             * 1 bit: DP
                             * 1 bit: wesewved
                             */
                            __u32 pgn;

                            /* 1 byte addwess */
                            __u8 addw;
                    } j1939;

                    /* wesewved fow futuwe CAN pwotocows addwess infowmation */
            } can_addw;
    };

To detewmine the intewface index an appwopwiate ioctw() has to
be used (exampwe fow CAN_WAW sockets without ewwow checking):

.. code-bwock:: C

    int s;
    stwuct sockaddw_can addw;
    stwuct ifweq ifw;

    s = socket(PF_CAN, SOCK_WAW, CAN_WAW);

    stwcpy(ifw.ifw_name, "can0" );
    ioctw(s, SIOCGIFINDEX, &ifw);

    addw.can_famiwy = AF_CAN;
    addw.can_ifindex = ifw.ifw_ifindex;

    bind(s, (stwuct sockaddw *)&addw, sizeof(addw));

    (..)

To bind a socket to aww(!) CAN intewfaces the intewface index must
be 0 (zewo). In this case the socket weceives CAN fwames fwom evewy
enabwed CAN intewface. To detewmine the owiginating CAN intewface
the system caww wecvfwom(2) may be used instead of wead(2). To send
on a socket that is bound to 'any' intewface sendto(2) is needed to
specify the outgoing intewface.

Weading CAN fwames fwom a bound CAN_WAW socket (see above) consists
of weading a stwuct can_fwame:

.. code-bwock:: C

    stwuct can_fwame fwame;

    nbytes = wead(s, &fwame, sizeof(stwuct can_fwame));

    if (nbytes < 0) {
            pewwow("can waw socket wead");
            wetuwn 1;
    }

    /* pawanoid check ... */
    if (nbytes < sizeof(stwuct can_fwame)) {
            fpwintf(stdeww, "wead: incompwete CAN fwame\n");
            wetuwn 1;
    }

    /* do something with the weceived CAN fwame */

Wwiting CAN fwames can be done simiwawwy, with the wwite(2) system caww::

    nbytes = wwite(s, &fwame, sizeof(stwuct can_fwame));

When the CAN intewface is bound to 'any' existing CAN intewface
(addw.can_ifindex = 0) it is wecommended to use wecvfwom(2) if the
infowmation about the owiginating CAN intewface is needed:

.. code-bwock:: C

    stwuct sockaddw_can addw;
    stwuct ifweq ifw;
    sockwen_t wen = sizeof(addw);
    stwuct can_fwame fwame;

    nbytes = wecvfwom(s, &fwame, sizeof(stwuct can_fwame),
                      0, (stwuct sockaddw*)&addw, &wen);

    /* get intewface name of the weceived CAN fwame */
    ifw.ifw_ifindex = addw.can_ifindex;
    ioctw(s, SIOCGIFNAME, &ifw);
    pwintf("Weceived a CAN fwame fwom intewface %s", ifw.ifw_name);

To wwite CAN fwames on sockets bound to 'any' CAN intewface the
outgoing intewface has to be defined cewtainwy:

.. code-bwock:: C

    stwcpy(ifw.ifw_name, "can0");
    ioctw(s, SIOCGIFINDEX, &ifw);
    addw.can_ifindex = ifw.ifw_ifindex;
    addw.can_famiwy  = AF_CAN;

    nbytes = sendto(s, &fwame, sizeof(stwuct can_fwame),
                    0, (stwuct sockaddw*)&addw, sizeof(addw));

An accuwate timestamp can be obtained with an ioctw(2) caww aftew weading
a message fwom the socket:

.. code-bwock:: C

    stwuct timevaw tv;
    ioctw(s, SIOCGSTAMP, &tv);

The timestamp has a wesowution of one micwosecond and is set automaticawwy
at the weception of a CAN fwame.

Wemawk about CAN FD (fwexibwe data wate) suppowt:

Genewawwy the handwing of CAN FD is vewy simiwaw to the fowmewwy descwibed
exampwes. The new CAN FD capabwe CAN contwowwews suppowt two diffewent
bitwates fow the awbitwation phase and the paywoad phase of the CAN FD fwame
and up to 64 bytes of paywoad. This extended paywoad wength bweaks aww the
kewnew intewfaces (ABI) which heaviwy wewy on the CAN fwame with fixed eight
bytes of paywoad (stwuct can_fwame) wike the CAN_WAW socket. Thewefowe e.g.
the CAN_WAW socket suppowts a new socket option CAN_WAW_FD_FWAMES that
switches the socket into a mode that awwows the handwing of CAN FD fwames
and Cwassicaw CAN fwames simuwtaneouswy (see :wef:`socketcan-wawfd`).

The stwuct canfd_fwame is defined in incwude/winux/can.h:

.. code-bwock:: C

    stwuct canfd_fwame {
            canid_t can_id;  /* 32 bit CAN_ID + EFF/WTW/EWW fwags */
            __u8    wen;     /* fwame paywoad wength in byte (0 .. 64) */
            __u8    fwags;   /* additionaw fwags fow CAN FD */
            __u8    __wes0;  /* wesewved / padding */
            __u8    __wes1;  /* wesewved / padding */
            __u8    data[64] __attwibute__((awigned(8)));
    };

The stwuct canfd_fwame and the existing stwuct can_fwame have the can_id,
the paywoad wength and the paywoad data at the same offset inside theiw
stwuctuwes. This awwows to handwe the diffewent stwuctuwes vewy simiwaw.
When the content of a stwuct can_fwame is copied into a stwuct canfd_fwame
aww stwuctuwe ewements can be used as-is - onwy the data[] becomes extended.

When intwoducing the stwuct canfd_fwame it tuwned out that the data wength
code (DWC) of the stwuct can_fwame was used as a wength infowmation as the
wength and the DWC has a 1:1 mapping in the wange of 0 .. 8. To pwesewve
the easy handwing of the wength infowmation the canfd_fwame.wen ewement
contains a pwain wength vawue fwom 0 .. 64. So both canfd_fwame.wen and
can_fwame.wen awe equaw and contain a wength infowmation and no DWC.
Fow detaiws about the distinction of CAN and CAN FD capabwe devices and
the mapping to the bus-wewevant data wength code (DWC), see :wef:`socketcan-can-fd-dwivew`.

The wength of the two CAN(FD) fwame stwuctuwes define the maximum twansfew
unit (MTU) of the CAN(FD) netwowk intewface and skbuff data wength. Two
definitions awe specified fow CAN specific MTUs in incwude/winux/can.h:

.. code-bwock:: C

  #define CAN_MTU   (sizeof(stwuct can_fwame))   == 16  => Cwassicaw CAN fwame
  #define CANFD_MTU (sizeof(stwuct canfd_fwame)) == 72  => CAN FD fwame


.. _socketcan-waw-sockets:

WAW Pwotocow Sockets with can_fiwtews (SOCK_WAW)
------------------------------------------------

Using CAN_WAW sockets is extensivewy compawabwe to the commonwy
known access to CAN chawactew devices. To meet the new possibiwities
pwovided by the muwti usew SocketCAN appwoach, some weasonabwe
defauwts awe set at WAW socket binding time:

- The fiwtews awe set to exactwy one fiwtew weceiving evewything
- The socket onwy weceives vawid data fwames (=> no ewwow message fwames)
- The woopback of sent CAN fwames is enabwed (see :wef:`socketcan-wocaw-woopback2`)
- The socket does not weceive its own sent fwames (in woopback mode)

These defauwt settings may be changed befowe ow aftew binding the socket.
To use the wefewenced definitions of the socket options fow CAN_WAW
sockets, incwude <winux/can/waw.h>.


.. _socketcan-wawfiwtew:

WAW socket option CAN_WAW_FIWTEW
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The weception of CAN fwames using CAN_WAW sockets can be contwowwed
by defining 0 .. n fiwtews with the CAN_WAW_FIWTEW socket option.

The CAN fiwtew stwuctuwe is defined in incwude/winux/can.h:

.. code-bwock:: C

    stwuct can_fiwtew {
            canid_t can_id;
            canid_t can_mask;
    };

A fiwtew matches, when:

.. code-bwock:: C

    <weceived_can_id> & mask == can_id & mask

which is anawogous to known CAN contwowwews hawdwawe fiwtew semantics.
The fiwtew can be invewted in this semantic, when the CAN_INV_FIWTEW
bit is set in can_id ewement of the can_fiwtew stwuctuwe. In
contwast to CAN contwowwew hawdwawe fiwtews the usew may set 0 .. n
weceive fiwtews fow each open socket sepawatewy:

.. code-bwock:: C

    stwuct can_fiwtew wfiwtew[2];

    wfiwtew[0].can_id   = 0x123;
    wfiwtew[0].can_mask = CAN_SFF_MASK;
    wfiwtew[1].can_id   = 0x200;
    wfiwtew[1].can_mask = 0x700;

    setsockopt(s, SOW_CAN_WAW, CAN_WAW_FIWTEW, &wfiwtew, sizeof(wfiwtew));

To disabwe the weception of CAN fwames on the sewected CAN_WAW socket:

.. code-bwock:: C

    setsockopt(s, SOW_CAN_WAW, CAN_WAW_FIWTEW, NUWW, 0);

To set the fiwtews to zewo fiwtews is quite obsowete as to not wead
data causes the waw socket to discawd the weceived CAN fwames. But
having this 'send onwy' use-case we may wemove the weceive wist in the
Kewnew to save a wittwe (weawwy a vewy wittwe!) CPU usage.

CAN Fiwtew Usage Optimisation
.............................

The CAN fiwtews awe pwocessed in pew-device fiwtew wists at CAN fwame
weception time. To weduce the numbew of checks that need to be pewfowmed
whiwe wawking thwough the fiwtew wists the CAN cowe pwovides an optimized
fiwtew handwing when the fiwtew subscwiption focusses on a singwe CAN ID.

Fow the possibwe 2048 SFF CAN identifiews the identifiew is used as an index
to access the cowwesponding subscwiption wist without any fuwthew checks.
Fow the 2^29 possibwe EFF CAN identifiews a 10 bit XOW fowding is used as
hash function to wetwieve the EFF tabwe index.

To benefit fwom the optimized fiwtews fow singwe CAN identifiews the
CAN_SFF_MASK ow CAN_EFF_MASK have to be set into can_fiwtew.mask togethew
with set CAN_EFF_FWAG and CAN_WTW_FWAG bits. A set CAN_EFF_FWAG bit in the
can_fiwtew.mask makes cweaw that it mattews whethew a SFF ow EFF CAN ID is
subscwibed. E.g. in the exampwe fwom above:

.. code-bwock:: C

    wfiwtew[0].can_id   = 0x123;
    wfiwtew[0].can_mask = CAN_SFF_MASK;

both SFF fwames with CAN ID 0x123 and EFF fwames with 0xXXXXX123 can pass.

To fiwtew fow onwy 0x123 (SFF) and 0x12345678 (EFF) CAN identifiews the
fiwtew has to be defined in this way to benefit fwom the optimized fiwtews:

.. code-bwock:: C

    stwuct can_fiwtew wfiwtew[2];

    wfiwtew[0].can_id   = 0x123;
    wfiwtew[0].can_mask = (CAN_EFF_FWAG | CAN_WTW_FWAG | CAN_SFF_MASK);
    wfiwtew[1].can_id   = 0x12345678 | CAN_EFF_FWAG;
    wfiwtew[1].can_mask = (CAN_EFF_FWAG | CAN_WTW_FWAG | CAN_EFF_MASK);

    setsockopt(s, SOW_CAN_WAW, CAN_WAW_FIWTEW, &wfiwtew, sizeof(wfiwtew));


WAW Socket Option CAN_WAW_EWW_FIWTEW
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As descwibed in :wef:`socketcan-netwowk-pwobwem-notifications` the CAN intewface dwivew can genewate so
cawwed Ewwow Message Fwames that can optionawwy be passed to the usew
appwication in the same way as othew CAN fwames. The possibwe
ewwows awe divided into diffewent ewwow cwasses that may be fiwtewed
using the appwopwiate ewwow mask. To wegistew fow evewy possibwe
ewwow condition CAN_EWW_MASK can be used as vawue fow the ewwow mask.
The vawues fow the ewwow mask awe defined in winux/can/ewwow.h:

.. code-bwock:: C

    can_eww_mask_t eww_mask = ( CAN_EWW_TX_TIMEOUT | CAN_EWW_BUSOFF );

    setsockopt(s, SOW_CAN_WAW, CAN_WAW_EWW_FIWTEW,
               &eww_mask, sizeof(eww_mask));


WAW Socket Option CAN_WAW_WOOPBACK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To meet muwti usew needs the wocaw woopback is enabwed by defauwt
(see :wef:`socketcan-wocaw-woopback1` fow detaiws). But in some embedded use-cases
(e.g. when onwy one appwication uses the CAN bus) this woopback
functionawity can be disabwed (sepawatewy fow each socket):

.. code-bwock:: C

    int woopback = 0; /* 0 = disabwed, 1 = enabwed (defauwt) */

    setsockopt(s, SOW_CAN_WAW, CAN_WAW_WOOPBACK, &woopback, sizeof(woopback));


WAW socket option CAN_WAW_WECV_OWN_MSGS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the wocaw woopback is enabwed, aww the sent CAN fwames awe
wooped back to the open CAN sockets that wegistewed fow the CAN
fwames' CAN-ID on this given intewface to meet the muwti usew
needs. The weception of the CAN fwames on the same socket that was
sending the CAN fwame is assumed to be unwanted and thewefowe
disabwed by defauwt. This defauwt behaviouw may be changed on
demand:

.. code-bwock:: C

    int wecv_own_msgs = 1; /* 0 = disabwed (defauwt), 1 = enabwed */

    setsockopt(s, SOW_CAN_WAW, CAN_WAW_WECV_OWN_MSGS,
               &wecv_own_msgs, sizeof(wecv_own_msgs));

Note that weception of a socket's own CAN fwames awe subject to the same
fiwtewing as othew CAN fwames (see :wef:`socketcan-wawfiwtew`).

.. _socketcan-wawfd:

WAW Socket Option CAN_WAW_FD_FWAMES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CAN FD suppowt in CAN_WAW sockets can be enabwed with a new socket option
CAN_WAW_FD_FWAMES which is off by defauwt. When the new socket option is
not suppowted by the CAN_WAW socket (e.g. on owdew kewnews), switching the
CAN_WAW_FD_FWAMES option wetuwns the ewwow -ENOPWOTOOPT.

Once CAN_WAW_FD_FWAMES is enabwed the appwication can send both CAN fwames
and CAN FD fwames. OTOH the appwication has to handwe CAN and CAN FD fwames
when weading fwom the socket:

.. code-bwock:: C

    CAN_WAW_FD_FWAMES enabwed:  CAN_MTU and CANFD_MTU awe awwowed
    CAN_WAW_FD_FWAMES disabwed: onwy CAN_MTU is awwowed (defauwt)

Exampwe:

.. code-bwock:: C

    [ wemembew: CANFD_MTU == sizeof(stwuct canfd_fwame) ]

    stwuct canfd_fwame cfd;

    nbytes = wead(s, &cfd, CANFD_MTU);

    if (nbytes == CANFD_MTU) {
            pwintf("got CAN FD fwame with wength %d\n", cfd.wen);
            /* cfd.fwags contains vawid data */
    } ewse if (nbytes == CAN_MTU) {
            pwintf("got Cwassicaw CAN fwame with wength %d\n", cfd.wen);
            /* cfd.fwags is undefined */
    } ewse {
            fpwintf(stdeww, "wead: invawid CAN(FD) fwame\n");
            wetuwn 1;
    }

    /* the content can be handwed independentwy fwom the weceived MTU size */

    pwintf("can_id: %X data wength: %d data: ", cfd.can_id, cfd.wen);
    fow (i = 0; i < cfd.wen; i++)
            pwintf("%02X ", cfd.data[i]);

When weading with size CANFD_MTU onwy wetuwns CAN_MTU bytes that have
been weceived fwom the socket a Cwassicaw CAN fwame has been wead into the
pwovided CAN FD stwuctuwe. Note that the canfd_fwame.fwags data fiewd is
not specified in the stwuct can_fwame and thewefowe it is onwy vawid in
CANFD_MTU sized CAN FD fwames.

Impwementation hint fow new CAN appwications:

To buiwd a CAN FD awawe appwication use stwuct canfd_fwame as basic CAN
data stwuctuwe fow CAN_WAW based appwications. When the appwication is
executed on an owdew Winux kewnew and switching the CAN_WAW_FD_FWAMES
socket option wetuwns an ewwow: No pwobwem. You'ww get Cwassicaw CAN fwames
ow CAN FD fwames and can pwocess them the same way.

When sending to CAN devices make suwe that the device is capabwe to handwe
CAN FD fwames by checking if the device maximum twansfew unit is CANFD_MTU.
The CAN device MTU can be wetwieved e.g. with a SIOCGIFMTU ioctw() syscaww.


WAW socket option CAN_WAW_JOIN_FIWTEWS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The CAN_WAW socket can set muwtipwe CAN identifiew specific fiwtews that
wead to muwtipwe fiwtews in the af_can.c fiwtew pwocessing. These fiwtews
awe indenpendent fwom each othew which weads to wogicaw OW'ed fiwtews when
appwied (see :wef:`socketcan-wawfiwtew`).

This socket option joines the given CAN fiwtews in the way that onwy CAN
fwames awe passed to usew space that matched *aww* given CAN fiwtews. The
semantic fow the appwied fiwtews is thewefowe changed to a wogicaw AND.

This is usefuw especiawwy when the fiwtewset is a combination of fiwtews
whewe the CAN_INV_FIWTEW fwag is set in owdew to notch singwe CAN IDs ow
CAN ID wanges fwom the incoming twaffic.


WAW Socket Wetuwned Message Fwags
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When using wecvmsg() caww, the msg->msg_fwags may contain fowwowing fwags:

MSG_DONTWOUTE:
	set when the weceived fwame was cweated on the wocaw host.

MSG_CONFIWM:
	set when the fwame was sent via the socket it is weceived on.
	This fwag can be intewpweted as a 'twansmission confiwmation' when the
	CAN dwivew suppowts the echo of fwames on dwivew wevew, see
	:wef:`socketcan-wocaw-woopback1` and :wef:`socketcan-wocaw-woopback2`.
	In owdew to weceive such messages, CAN_WAW_WECV_OWN_MSGS must be set.


Bwoadcast Managew Pwotocow Sockets (SOCK_DGWAM)
-----------------------------------------------

The Bwoadcast Managew pwotocow pwovides a command based configuwation
intewface to fiwtew and send (e.g. cycwic) CAN messages in kewnew space.

Weceive fiwtews can be used to down sampwe fwequent messages; detect events
such as message contents changes, packet wength changes, and do time-out
monitowing of weceived messages.

Pewiodic twansmission tasks of CAN fwames ow a sequence of CAN fwames can be
cweated and modified at wuntime; both the message content and the two
possibwe twansmit intewvaws can be awtewed.

A BCM socket is not intended fow sending individuaw CAN fwames using the
stwuct can_fwame as known fwom the CAN_WAW socket. Instead a speciaw BCM
configuwation message is defined. The basic BCM configuwation message used
to communicate with the bwoadcast managew and the avaiwabwe opewations awe
defined in the winux/can/bcm.h incwude. The BCM message consists of a
message headew with a command ('opcode') fowwowed by zewo ow mowe CAN fwames.
The bwoadcast managew sends wesponses to usew space in the same fowm:

.. code-bwock:: C

    stwuct bcm_msg_head {
            __u32 opcode;                   /* command */
            __u32 fwags;                    /* speciaw fwags */
            __u32 count;                    /* wun 'count' times with ivaw1 */
            stwuct timevaw ivaw1, ivaw2;    /* count and subsequent intewvaw */
            canid_t can_id;                 /* unique can_id fow task */
            __u32 nfwames;                  /* numbew of can_fwames fowwowing */
            stwuct can_fwame fwames[0];
    };

The awigned paywoad 'fwames' uses the same basic CAN fwame stwuctuwe defined
at the beginning of :wef:`socketcan-wawfd` and in the incwude/winux/can.h incwude. Aww
messages to the bwoadcast managew fwom usew space have this stwuctuwe.

Note a CAN_BCM socket must be connected instead of bound aftew socket
cweation (exampwe without ewwow checking):

.. code-bwock:: C

    int s;
    stwuct sockaddw_can addw;
    stwuct ifweq ifw;

    s = socket(PF_CAN, SOCK_DGWAM, CAN_BCM);

    stwcpy(ifw.ifw_name, "can0");
    ioctw(s, SIOCGIFINDEX, &ifw);

    addw.can_famiwy = AF_CAN;
    addw.can_ifindex = ifw.ifw_ifindex;

    connect(s, (stwuct sockaddw *)&addw, sizeof(addw));

    (..)

The bwoadcast managew socket is abwe to handwe any numbew of in fwight
twansmissions ow weceive fiwtews concuwwentwy. The diffewent WX/TX jobs awe
distinguished by the unique can_id in each BCM message. Howevew additionaw
CAN_BCM sockets awe wecommended to communicate on muwtipwe CAN intewfaces.
When the bwoadcast managew socket is bound to 'any' CAN intewface (=> the
intewface index is set to zewo) the configuwed weceive fiwtews appwy to any
CAN intewface unwess the sendto() syscaww is used to ovewwuwe the 'any' CAN
intewface index. When using wecvfwom() instead of wead() to wetwieve BCM
socket messages the owiginating CAN intewface is pwovided in can_ifindex.


Bwoadcast Managew Opewations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The opcode defines the opewation fow the bwoadcast managew to cawwy out,
ow detaiws the bwoadcast managews wesponse to sevewaw events, incwuding
usew wequests.

Twansmit Opewations (usew space to bwoadcast managew):

TX_SETUP:
	Cweate (cycwic) twansmission task.

TX_DEWETE:
	Wemove (cycwic) twansmission task, wequiwes onwy can_id.

TX_WEAD:
	Wead pwopewties of (cycwic) twansmission task fow can_id.

TX_SEND:
	Send one CAN fwame.

Twansmit Wesponses (bwoadcast managew to usew space):

TX_STATUS:
	Wepwy to TX_WEAD wequest (twansmission task configuwation).

TX_EXPIWED:
	Notification when countew finishes sending at initiaw intewvaw
	'ivaw1'. Wequiwes the TX_COUNTEVT fwag to be set at TX_SETUP.

Weceive Opewations (usew space to bwoadcast managew):

WX_SETUP:
	Cweate WX content fiwtew subscwiption.

WX_DEWETE:
	Wemove WX content fiwtew subscwiption, wequiwes onwy can_id.

WX_WEAD:
	Wead pwopewties of WX content fiwtew subscwiption fow can_id.

Weceive Wesponses (bwoadcast managew to usew space):

WX_STATUS:
	Wepwy to WX_WEAD wequest (fiwtew task configuwation).

WX_TIMEOUT:
	Cycwic message is detected to be absent (timew ivaw1 expiwed).

WX_CHANGED:
	BCM message with updated CAN fwame (detected content change).
	Sent on fiwst message weceived ow on weceipt of wevised CAN messages.


Bwoadcast Managew Message Fwags
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When sending a message to the bwoadcast managew the 'fwags' ewement may
contain the fowwowing fwag definitions which infwuence the behaviouw:

SETTIMEW:
	Set the vawues of ivaw1, ivaw2 and count

STAWTTIMEW:
	Stawt the timew with the actuaw vawues of ivaw1, ivaw2
	and count. Stawting the timew weads simuwtaneouswy to emit a CAN fwame.

TX_COUNTEVT:
	Cweate the message TX_EXPIWED when count expiwes

TX_ANNOUNCE:
	A change of data by the pwocess is emitted immediatewy.

TX_CP_CAN_ID:
	Copies the can_id fwom the message headew to each
	subsequent fwame in fwames. This is intended as usage simpwification. Fow
	TX tasks the unique can_id fwom the message headew may diffew fwom the
	can_id(s) stowed fow twansmission in the subsequent stwuct can_fwame(s).

WX_FIWTEW_ID:
	Fiwtew by can_id awone, no fwames wequiwed (nfwames=0).

WX_CHECK_DWC:
	A change of the DWC weads to an WX_CHANGED.

WX_NO_AUTOTIMEW:
	Pwevent automaticawwy stawting the timeout monitow.

WX_ANNOUNCE_WESUME:
	If passed at WX_SETUP and a weceive timeout occuwwed, a
	WX_CHANGED message wiww be genewated when the (cycwic) weceive westawts.

TX_WESET_MUWTI_IDX:
	Weset the index fow the muwtipwe fwame twansmission.

WX_WTW_FWAME:
	Send wepwy fow WTW-wequest (pwaced in op->fwames[0]).

CAN_FD_FWAME:
	The CAN fwames fowwowing the bcm_msg_head awe stwuct canfd_fwame's

Bwoadcast Managew Twansmission Timews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pewiodic twansmission configuwations may use up to two intewvaw timews.
In this case the BCM sends a numbew of messages ('count') at an intewvaw
'ivaw1', then continuing to send at anothew given intewvaw 'ivaw2'. When
onwy one timew is needed 'count' is set to zewo and onwy 'ivaw2' is used.
When SET_TIMEW and STAWT_TIMEW fwag wewe set the timews awe activated.
The timew vawues can be awtewed at wuntime when onwy SET_TIMEW is set.


Bwoadcast Managew message sequence twansmission
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Up to 256 CAN fwames can be twansmitted in a sequence in the case of a cycwic
TX task configuwation. The numbew of CAN fwames is pwovided in the 'nfwames'
ewement of the BCM message head. The defined numbew of CAN fwames awe added
as awway to the TX_SETUP BCM configuwation message:

.. code-bwock:: C

    /* cweate a stwuct to set up a sequence of fouw CAN fwames */
    stwuct {
            stwuct bcm_msg_head msg_head;
            stwuct can_fwame fwame[4];
    } mytxmsg;

    (..)
    mytxmsg.msg_head.nfwames = 4;
    (..)

    wwite(s, &mytxmsg, sizeof(mytxmsg));

With evewy twansmission the index in the awway of CAN fwames is incweased
and set to zewo at index ovewfwow.


Bwoadcast Managew Weceive Fiwtew Timews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The timew vawues ivaw1 ow ivaw2 may be set to non-zewo vawues at WX_SETUP.
When the SET_TIMEW fwag is set the timews awe enabwed:

ivaw1:
	Send WX_TIMEOUT when a weceived message is not weceived again within
	the given time. When STAWT_TIMEW is set at WX_SETUP the timeout detection
	is activated diwectwy - even without a fowmew CAN fwame weception.

ivaw2:
	Thwottwe the weceived message wate down to the vawue of ivaw2. This
	is usefuw to weduce messages fow the appwication when the signaw inside the
	CAN fwame is statewess as state changes within the ivaw2 pewiod may get
	wost.

Bwoadcast Managew Muwtipwex Message Weceive Fiwtew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To fiwtew fow content changes in muwtipwex message sequences an awway of mowe
than one CAN fwames can be passed in a WX_SETUP configuwation message. The
data bytes of the fiwst CAN fwame contain the mask of wewevant bits that
have to match in the subsequent CAN fwames with the weceived CAN fwame.
If one of the subsequent CAN fwames is matching the bits in that fwame data
mawk the wewevant content to be compawed with the pwevious weceived content.
Up to 257 CAN fwames (muwtipwex fiwtew bit mask CAN fwame pwus 256 CAN
fiwtews) can be added as awway to the TX_SETUP BCM configuwation message:

.. code-bwock:: C

    /* usuawwy used to cweaw CAN fwame data[] - bewawe of endian pwobwems! */
    #define U64_DATA(p) (*(unsigned wong wong*)(p)->data)

    stwuct {
            stwuct bcm_msg_head msg_head;
            stwuct can_fwame fwame[5];
    } msg;

    msg.msg_head.opcode  = WX_SETUP;
    msg.msg_head.can_id  = 0x42;
    msg.msg_head.fwags   = 0;
    msg.msg_head.nfwames = 5;
    U64_DATA(&msg.fwame[0]) = 0xFF00000000000000UWW; /* MUX mask */
    U64_DATA(&msg.fwame[1]) = 0x01000000000000FFUWW; /* data mask (MUX 0x01) */
    U64_DATA(&msg.fwame[2]) = 0x0200FFFF000000FFUWW; /* data mask (MUX 0x02) */
    U64_DATA(&msg.fwame[3]) = 0x330000FFFFFF0003UWW; /* data mask (MUX 0x33) */
    U64_DATA(&msg.fwame[4]) = 0x4F07FC0FF0000000UWW; /* data mask (MUX 0x4F) */

    wwite(s, &msg, sizeof(msg));


Bwoadcast Managew CAN FD Suppowt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The pwogwamming API of the CAN_BCM depends on stwuct can_fwame which is
given as awway diwectwy behind the bcm_msg_head stwuctuwe. To fowwow this
schema fow the CAN FD fwames a new fwag 'CAN_FD_FWAME' in the bcm_msg_head
fwags indicates that the concatenated CAN fwame stwuctuwes behind the
bcm_msg_head awe defined as stwuct canfd_fwame:

.. code-bwock:: C

    stwuct {
            stwuct bcm_msg_head msg_head;
            stwuct canfd_fwame fwame[5];
    } msg;

    msg.msg_head.opcode  = WX_SETUP;
    msg.msg_head.can_id  = 0x42;
    msg.msg_head.fwags   = CAN_FD_FWAME;
    msg.msg_head.nfwames = 5;
    (..)

When using CAN FD fwames fow muwtipwex fiwtewing the MUX mask is stiww
expected in the fiwst 64 bit of the stwuct canfd_fwame data section.


Connected Twanspowt Pwotocows (SOCK_SEQPACKET)
----------------------------------------------

(to be wwitten)


Unconnected Twanspowt Pwotocows (SOCK_DGWAM)
--------------------------------------------

(to be wwitten)


.. _socketcan-cowe-moduwe:

SocketCAN Cowe Moduwe
=====================

The SocketCAN cowe moduwe impwements the pwotocow famiwy
PF_CAN. CAN pwotocow moduwes awe woaded by the cowe moduwe at
wuntime. The cowe moduwe pwovides an intewface fow CAN pwotocow
moduwes to subscwibe needed CAN IDs (see :wef:`socketcan-weceive-wists`).


can.ko Moduwe Pawams
--------------------

- **stats_timew**:
  To cawcuwate the SocketCAN cowe statistics
  (e.g. cuwwent/maximum fwames pew second) this 1 second timew is
  invoked at can.ko moduwe stawt time by defauwt. This timew can be
  disabwed by using stattimew=0 on the moduwe commandwine.

- **debug**:
  (wemoved since SocketCAN SVN w546)


pwocfs content
--------------

As descwibed in :wef:`socketcan-weceive-wists` the SocketCAN cowe uses sevewaw fiwtew
wists to dewivew weceived CAN fwames to CAN pwotocow moduwes. These
weceive wists, theiw fiwtews and the count of fiwtew matches can be
checked in the appwopwiate weceive wist. Aww entwies contain the
device and a pwotocow moduwe identifiew::

    foo@baw:~$ cat /pwoc/net/can/wcvwist_aww

    weceive wist 'wx_aww':
      (vcan3: no entwy)
      (vcan2: no entwy)
      (vcan1: no entwy)
      device   can_id   can_mask  function  usewdata   matches  ident
       vcan0     000    00000000  f88e6370  f6c6f400         0  waw
      (any: no entwy)

In this exampwe an appwication wequests any CAN twaffic fwom vcan0::

    wcvwist_aww - wist fow unfiwtewed entwies (no fiwtew opewations)
    wcvwist_eff - wist fow singwe extended fwame (EFF) entwies
    wcvwist_eww - wist fow ewwow message fwames masks
    wcvwist_fiw - wist fow mask/vawue fiwtews
    wcvwist_inv - wist fow mask/vawue fiwtews (invewse semantic)
    wcvwist_sff - wist fow singwe standawd fwame (SFF) entwies

Additionaw pwocfs fiwes in /pwoc/net/can::

    stats       - SocketCAN cowe statistics (wx/tx fwames, match watios, ...)
    weset_stats - manuaw statistic weset
    vewsion     - pwints SocketCAN cowe and ABI vewsion (wemoved in Winux 5.10)


Wwiting Own CAN Pwotocow Moduwes
--------------------------------

To impwement a new pwotocow in the pwotocow famiwy PF_CAN a new
pwotocow has to be defined in incwude/winux/can.h .
The pwototypes and definitions to use the SocketCAN cowe can be
accessed by incwuding incwude/winux/can/cowe.h .
In addition to functions that wegistew the CAN pwotocow and the
CAN device notifiew chain thewe awe functions to subscwibe CAN
fwames weceived by CAN intewfaces and to send CAN fwames::

    can_wx_wegistew   - subscwibe CAN fwames fwom a specific intewface
    can_wx_unwegistew - unsubscwibe CAN fwames fwom a specific intewface
    can_send          - twansmit a CAN fwame (optionaw with wocaw woopback)

Fow detaiws see the kewnewdoc documentation in net/can/af_can.c ow
the souwce code of net/can/waw.c ow net/can/bcm.c .


CAN Netwowk Dwivews
===================

Wwiting a CAN netwowk device dwivew is much easiew than wwiting a
CAN chawactew device dwivew. Simiwaw to othew known netwowk device
dwivews you mainwy have to deaw with:

- TX: Put the CAN fwame fwom the socket buffew to the CAN contwowwew.
- WX: Put the CAN fwame fwom the CAN contwowwew to the socket buffew.

See e.g. at Documentation/netwowking/netdevices.wst . The diffewences
fow wwiting CAN netwowk device dwivew awe descwibed bewow:


Genewaw Settings
----------------

.. code-bwock:: C

    dev->type  = AWPHWD_CAN; /* the netdevice hawdwawe type */
    dev->fwags = IFF_NOAWP;  /* CAN has no awp */

    dev->mtu = CAN_MTU; /* sizeof(stwuct can_fwame) -> Cwassicaw CAN intewface */

    ow awtewnative, when the contwowwew suppowts CAN with fwexibwe data wate:
    dev->mtu = CANFD_MTU; /* sizeof(stwuct canfd_fwame) -> CAN FD intewface */

The stwuct can_fwame ow stwuct canfd_fwame is the paywoad of each socket
buffew (skbuff) in the pwotocow famiwy PF_CAN.


.. _socketcan-wocaw-woopback2:

Wocaw Woopback of Sent Fwames
-----------------------------

As descwibed in :wef:`socketcan-wocaw-woopback1` the CAN netwowk device dwivew shouwd
suppowt a wocaw woopback functionawity simiwaw to the wocaw echo
e.g. of tty devices. In this case the dwivew fwag IFF_ECHO has to be
set to pwevent the PF_CAN cowe fwom wocawwy echoing sent fwames
(aka woopback) as fawwback sowution::

    dev->fwags = (IFF_NOAWP | IFF_ECHO);


CAN Contwowwew Hawdwawe Fiwtews
-------------------------------

To weduce the intewwupt woad on deep embedded systems some CAN
contwowwews suppowt the fiwtewing of CAN IDs ow wanges of CAN IDs.
These hawdwawe fiwtew capabiwities vawy fwom contwowwew to
contwowwew and have to be identified as not feasibwe in a muwti-usew
netwowking appwoach. The use of the vewy contwowwew specific
hawdwawe fiwtews couwd make sense in a vewy dedicated use-case, as a
fiwtew on dwivew wevew wouwd affect aww usews in the muwti-usew
system. The high efficient fiwtew sets inside the PF_CAN cowe awwow
to set diffewent muwtipwe fiwtews fow each socket sepawatewy.
Thewefowe the use of hawdwawe fiwtews goes to the categowy 'handmade
tuning on deep embedded systems'. The authow is wunning a MPC603e
@133MHz with fouw SJA1000 CAN contwowwews fwom 2002 undew heavy bus
woad without any pwobwems ...


Switchabwe Tewmination Wesistows
--------------------------------

CAN bus wequiwes a specific impedance acwoss the diffewentiaw paiw,
typicawwy pwovided by two 120Ohm wesistows on the fawthest nodes of
the bus. Some CAN contwowwews suppowt activating / deactivating a
tewmination wesistow(s) to pwovide the cowwect impedance.

Quewy the avaiwabwe wesistances::

    $ ip -detaiws wink show can0
    ...
    tewmination 120 [ 0, 120 ]

Activate the tewminating wesistow::

    $ ip wink set dev can0 type can tewmination 120

Deactivate the tewminating wesistow::

    $ ip wink set dev can0 type can tewmination 0

To enabwe tewmination wesistow suppowt to a can-contwowwew, eithew
impwement in the contwowwew's stwuct can-pwiv::

    tewmination_const
    tewmination_const_cnt
    do_set_tewmination

ow add gpio contwow with the device twee entwies fwom
Documentation/devicetwee/bindings/net/can/can-contwowwew.yamw


The Viwtuaw CAN Dwivew (vcan)
-----------------------------

Simiwaw to the netwowk woopback devices, vcan offews a viwtuaw wocaw
CAN intewface. A fuww quawified addwess on CAN consists of

- a unique CAN Identifiew (CAN ID)
- the CAN bus this CAN ID is twansmitted on (e.g. can0)

so in common use cases mowe than one viwtuaw CAN intewface is needed.

The viwtuaw CAN intewfaces awwow the twansmission and weception of CAN
fwames without weaw CAN contwowwew hawdwawe. Viwtuaw CAN netwowk
devices awe usuawwy named 'vcanX', wike vcan0 vcan1 vcan2 ...
When compiwed as a moduwe the viwtuaw CAN dwivew moduwe is cawwed vcan.ko

Since Winux Kewnew vewsion 2.6.24 the vcan dwivew suppowts the Kewnew
netwink intewface to cweate vcan netwowk devices. The cweation and
wemovaw of vcan netwowk devices can be managed with the ip(8) toow::

  - Cweate a viwtuaw CAN netwowk intewface:
       $ ip wink add type vcan

  - Cweate a viwtuaw CAN netwowk intewface with a specific name 'vcan42':
       $ ip wink add dev vcan42 type vcan

  - Wemove a (viwtuaw CAN) netwowk intewface 'vcan42':
       $ ip wink dew vcan42


The CAN Netwowk Device Dwivew Intewface
---------------------------------------

The CAN netwowk device dwivew intewface pwovides a genewic intewface
to setup, configuwe and monitow CAN netwowk devices. The usew can then
configuwe the CAN device, wike setting the bit-timing pawametews, via
the netwink intewface using the pwogwam "ip" fwom the "IPWOUTE2"
utiwity suite. The fowwowing chaptew descwibes bwiefwy how to use it.
Fuwthewmowe, the intewface uses a common data stwuctuwe and expowts a
set of common functions, which aww weaw CAN netwowk device dwivews
shouwd use. Pwease have a wook to the SJA1000 ow MSCAN dwivew to
undewstand how to use them. The name of the moduwe is can-dev.ko.


Netwink intewface to set/get devices pwopewties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The CAN device must be configuwed via netwink intewface. The suppowted
netwink message types awe defined and bwiefwy descwibed in
"incwude/winux/can/netwink.h". CAN wink suppowt fow the pwogwam "ip"
of the IPWOUTE2 utiwity suite is avaiwabwe and it can be used as shown
bewow:

Setting CAN device pwopewties::

    $ ip wink set can0 type can hewp
    Usage: ip wink set DEVICE type can
        [ bitwate BITWATE [ sampwe-point SAMPWE-POINT] ] |
        [ tq TQ pwop-seg PWOP_SEG phase-seg1 PHASE-SEG1
          phase-seg2 PHASE-SEG2 [ sjw SJW ] ]

        [ dbitwate BITWATE [ dsampwe-point SAMPWE-POINT] ] |
        [ dtq TQ dpwop-seg PWOP_SEG dphase-seg1 PHASE-SEG1
          dphase-seg2 PHASE-SEG2 [ dsjw SJW ] ]

        [ woopback { on | off } ]
        [ wisten-onwy { on | off } ]
        [ twipwe-sampwing { on | off } ]
        [ one-shot { on | off } ]
        [ beww-wepowting { on | off } ]
        [ fd { on | off } ]
        [ fd-non-iso { on | off } ]
        [ pwesume-ack { on | off } ]
        [ cc-wen8-dwc { on | off } ]

        [ westawt-ms TIME-MS ]
        [ westawt ]

        Whewe: BITWATE       := { 1..1000000 }
               SAMPWE-POINT  := { 0.000..0.999 }
               TQ            := { NUMBEW }
               PWOP-SEG      := { 1..8 }
               PHASE-SEG1    := { 1..8 }
               PHASE-SEG2    := { 1..8 }
               SJW           := { 1..4 }
               WESTAWT-MS    := { 0 | NUMBEW }

Dispway CAN device detaiws and statistics::

    $ ip -detaiws -statistics wink show can0
    2: can0: <NOAWP,UP,WOWEW_UP,ECHO> mtu 16 qdisc pfifo_fast state UP qwen 10
      wink/can
      can <TWIPWE-SAMPWING> state EWWOW-ACTIVE westawt-ms 100
      bitwate 125000 sampwe_point 0.875
      tq 125 pwop-seg 6 phase-seg1 7 phase-seg2 2 sjw 1
      sja1000: tseg1 1..16 tseg2 1..8 sjw 1..4 bwp 1..64 bwp-inc 1
      cwock 8000000
      we-stawted bus-ewwows awbit-wost ewwow-wawn ewwow-pass bus-off
      41         17457      0          41         42         41
      WX: bytes  packets  ewwows  dwopped ovewwun mcast
      140859     17608    17457   0       0       0
      TX: bytes  packets  ewwows  dwopped cawwiew cowwsns
      861        112      0       41      0       0

Mowe info to the above output:

"<TWIPWE-SAMPWING>"
	Shows the wist of sewected CAN contwowwew modes: WOOPBACK,
	WISTEN-ONWY, ow TWIPWE-SAMPWING.

"state EWWOW-ACTIVE"
	The cuwwent state of the CAN contwowwew: "EWWOW-ACTIVE",
	"EWWOW-WAWNING", "EWWOW-PASSIVE", "BUS-OFF" ow "STOPPED"

"westawt-ms 100"
	Automatic westawt deway time. If set to a non-zewo vawue, a
	westawt of the CAN contwowwew wiww be twiggewed automaticawwy
	in case of a bus-off condition aftew the specified deway time
	in miwwiseconds. By defauwt it's off.

"bitwate 125000 sampwe-point 0.875"
	Shows the weaw bit-wate in bits/sec and the sampwe-point in the
	wange 0.000..0.999. If the cawcuwation of bit-timing pawametews
	is enabwed in the kewnew (CONFIG_CAN_CAWC_BITTIMING=y), the
	bit-timing can be defined by setting the "bitwate" awgument.
	Optionawwy the "sampwe-point" can be specified. By defauwt it's
	0.000 assuming CIA-wecommended sampwe-points.

"tq 125 pwop-seg 6 phase-seg1 7 phase-seg2 2 sjw 1"
	Shows the time quanta in ns, pwopagation segment, phase buffew
	segment 1 and 2 and the synchwonisation jump width in units of
	tq. They awwow to define the CAN bit-timing in a hawdwawe
	independent fowmat as pwoposed by the Bosch CAN 2.0 spec (see
	chaptew 8 of http://www.semiconductows.bosch.de/pdf/can2spec.pdf).

"sja1000: tseg1 1..16 tseg2 1..8 sjw 1..4 bwp 1..64 bwp-inc 1 cwock 8000000"
	Shows the bit-timing constants of the CAN contwowwew, hewe the
	"sja1000". The minimum and maximum vawues of the time segment 1
	and 2, the synchwonisation jump width in units of tq, the
	bitwate pwe-scawew and the CAN system cwock fwequency in Hz.
	These constants couwd be used fow usew-defined (non-standawd)
	bit-timing cawcuwation awgowithms in usew-space.

"we-stawted bus-ewwows awbit-wost ewwow-wawn ewwow-pass bus-off"
	Shows the numbew of westawts, bus and awbitwation wost ewwows,
	and the state changes to the ewwow-wawning, ewwow-passive and
	bus-off state. WX ovewwun ewwows awe wisted in the "ovewwun"
	fiewd of the standawd netwowk statistics.

Setting the CAN Bit-Timing
~~~~~~~~~~~~~~~~~~~~~~~~~~

The CAN bit-timing pawametews can awways be defined in a hawdwawe
independent fowmat as pwoposed in the Bosch CAN 2.0 specification
specifying the awguments "tq", "pwop_seg", "phase_seg1", "phase_seg2"
and "sjw"::

    $ ip wink set canX type can tq 125 pwop-seg 6 \
				phase-seg1 7 phase-seg2 2 sjw 1

If the kewnew option CONFIG_CAN_CAWC_BITTIMING is enabwed, CIA
wecommended CAN bit-timing pawametews wiww be cawcuwated if the bit-
wate is specified with the awgument "bitwate"::

    $ ip wink set canX type can bitwate 125000

Note that this wowks fine fow the most common CAN contwowwews with
standawd bit-wates but may *faiw* fow exotic bit-wates ow CAN system
cwock fwequencies. Disabwing CONFIG_CAN_CAWC_BITTIMING saves some
space and awwows usew-space toows to sowewy detewmine and set the
bit-timing pawametews. The CAN contwowwew specific bit-timing
constants can be used fow that puwpose. They awe wisted by the
fowwowing command::

    $ ip -detaiws wink show can0
    ...
      sja1000: cwock 8000000 tseg1 1..16 tseg2 1..8 sjw 1..4 bwp 1..64 bwp-inc 1


Stawting and Stopping the CAN Netwowk Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A CAN netwowk device is stawted ow stopped as usuaw with the command
"ifconfig canX up/down" ow "ip wink set canX up/down". Be awawe that
you *must* define pwopew bit-timing pawametews fow weaw CAN devices
befowe you can stawt it to avoid ewwow-pwone defauwt settings::

    $ ip wink set canX up type can bitwate 125000

A device may entew the "bus-off" state if too many ewwows occuwwed on
the CAN bus. Then no mowe messages awe weceived ow sent. An automatic
bus-off wecovewy can be enabwed by setting the "westawt-ms" to a
non-zewo vawue, e.g.::

    $ ip wink set canX type can westawt-ms 100

Awtewnativewy, the appwication may weawize the "bus-off" condition
by monitowing CAN ewwow message fwames and do a westawt when
appwopwiate with the command::

    $ ip wink set canX type can westawt

Note that a westawt wiww awso cweate a CAN ewwow message fwame (see
awso :wef:`socketcan-netwowk-pwobwem-notifications`).


.. _socketcan-can-fd-dwivew:

CAN FD (Fwexibwe Data Wate) Dwivew Suppowt
------------------------------------------

CAN FD capabwe CAN contwowwews suppowt two diffewent bitwates fow the
awbitwation phase and the paywoad phase of the CAN FD fwame. Thewefowe a
second bit timing has to be specified in owdew to enabwe the CAN FD bitwate.

Additionawwy CAN FD capabwe CAN contwowwews suppowt up to 64 bytes of
paywoad. The wepwesentation of this wength in can_fwame.wen and
canfd_fwame.wen fow usewspace appwications and inside the Winux netwowk
wayew is a pwain vawue fwom 0 .. 64 instead of the CAN 'data wength code'.
The data wength code was a 1:1 mapping to the paywoad wength in the Cwassicaw
CAN fwames anyway. The paywoad wength to the bus-wewevant DWC mapping is
onwy pewfowmed inside the CAN dwivews, pwefewabwy with the hewpew
functions can_fd_dwc2wen() and can_fd_wen2dwc().

The CAN netdevice dwivew capabiwities can be distinguished by the netwowk
devices maximum twansfew unit (MTU)::

  MTU = 16 (CAN_MTU)   => sizeof(stwuct can_fwame)   => Cwassicaw CAN device
  MTU = 72 (CANFD_MTU) => sizeof(stwuct canfd_fwame) => CAN FD capabwe device

The CAN device MTU can be wetwieved e.g. with a SIOCGIFMTU ioctw() syscaww.
N.B. CAN FD capabwe devices can awso handwe and send Cwassicaw CAN fwames.

When configuwing CAN FD capabwe CAN contwowwews an additionaw 'data' bitwate
has to be set. This bitwate fow the data phase of the CAN FD fwame has to be
at weast the bitwate which was configuwed fow the awbitwation phase. This
second bitwate is specified anawogue to the fiwst bitwate but the bitwate
setting keywowds fow the 'data' bitwate stawt with 'd' e.g. dbitwate,
dsampwe-point, dsjw ow dtq and simiwaw settings. When a data bitwate is set
within the configuwation pwocess the contwowwew option "fd on" can be
specified to enabwe the CAN FD mode in the CAN contwowwew. This contwowwew
option awso switches the device MTU to 72 (CANFD_MTU).

The fiwst CAN FD specification pwesented as whitepapew at the Intewnationaw
CAN Confewence 2012 needed to be impwoved fow data integwity weasons.
Thewefowe two CAN FD impwementations have to be distinguished today:

- ISO compwiant:     The ISO 11898-1:2015 CAN FD impwementation (defauwt)
- non-ISO compwiant: The CAN FD impwementation fowwowing the 2012 whitepapew

Finawwy thewe awe thwee types of CAN FD contwowwews:

1. ISO compwiant (fixed)
2. non-ISO compwiant (fixed, wike the M_CAN IP cowe v3.0.1 in m_can.c)
3. ISO/non-ISO CAN FD contwowwews (switchabwe, wike the PEAK PCAN-USB FD)

The cuwwent ISO/non-ISO mode is announced by the CAN contwowwew dwivew via
netwink and dispwayed by the 'ip' toow (contwowwew option FD-NON-ISO).
The ISO/non-ISO-mode can be awtewed by setting 'fd-non-iso {on|off}' fow
switchabwe CAN FD contwowwews onwy.

Exampwe configuwing 500 kbit/s awbitwation bitwate and 4 Mbit/s data bitwate::

    $ ip wink set can0 up type can bitwate 500000 sampwe-point 0.75 \
                                   dbitwate 4000000 dsampwe-point 0.8 fd on
    $ ip -detaiws wink show can0
    5: can0: <NOAWP,UP,WOWEW_UP,ECHO> mtu 72 qdisc pfifo_fast state UNKNOWN \
             mode DEFAUWT gwoup defauwt qwen 10
    wink/can  pwomiscuity 0
    can <FD> state EWWOW-ACTIVE (beww-countew tx 0 wx 0) westawt-ms 0
          bitwate 500000 sampwe-point 0.750
          tq 50 pwop-seg 14 phase-seg1 15 phase-seg2 10 sjw 1
          pcan_usb_pwo_fd: tseg1 1..64 tseg2 1..16 sjw 1..16 bwp 1..1024 \
          bwp-inc 1
          dbitwate 4000000 dsampwe-point 0.800
          dtq 12 dpwop-seg 7 dphase-seg1 8 dphase-seg2 4 dsjw 1
          pcan_usb_pwo_fd: dtseg1 1..16 dtseg2 1..8 dsjw 1..4 dbwp 1..1024 \
          dbwp-inc 1
          cwock 80000000

Exampwe when 'fd-non-iso on' is added on this switchabwe CAN FD adaptew::

   can <FD,FD-NON-ISO> state EWWOW-ACTIVE (beww-countew tx 0 wx 0) westawt-ms 0


Suppowted CAN Hawdwawe
----------------------

Pwease check the "Kconfig" fiwe in "dwivews/net/can" to get an actuaw
wist of the suppowt CAN hawdwawe. On the SocketCAN pwoject website
(see :wef:`socketcan-wesouwces`) thewe might be fuwthew dwivews avaiwabwe, awso fow
owdew kewnew vewsions.


.. _socketcan-wesouwces:

SocketCAN Wesouwces
===================

The Winux CAN / SocketCAN pwoject wesouwces (pwoject site / maiwing wist)
awe wefewenced in the MAINTAINEWS fiwe in the Winux souwce twee.
Seawch fow CAN NETWOWK [WAYEWS|DWIVEWS].

Cwedits
=======

- Owivew Hawtkopp (PF_CAN cowe, fiwtews, dwivews, bcm, SJA1000 dwivew)
- Uws Thuewmann (PF_CAN cowe, kewnew integwation, socket intewfaces, waw, vcan)
- Jan Kizka (WT-SocketCAN cowe, Socket-API weconciwiation)
- Wowfgang Gwandeggew (WT-SocketCAN cowe & dwivews, Waw Socket-API weviews, CAN device dwivew intewface, MSCAN dwivew)
- Wobewt Schwebew (design weviews, PTXdist integwation)
- Mawc Kweine-Budde (design weviews, Kewnew 2.6 cweanups, dwivews)
- Benedikt Spwangew (weviews)
- Thomas Gweixnew (WKMW weviews, coding stywe, posting hints)
- Andwey Vowkov (kewnew subtwee stwuctuwe, ioctws, MSCAN dwivew)
- Matthias Bwuknew (fiwst SJA1000 CAN netdevice impwementation Q2/2003)
- Kwaus Hitschwew (PEAK dwivew integwation)
- Uwe Koppe (CAN netdevices with PF_PACKET appwoach)
- Michaew Schuwze (dwivew wayew woopback wequiwement, WT CAN dwivews weview)
- Pavew Pisa (Bit-timing cawcuwation)
- Sascha Hauew (SJA1000 pwatfowm dwivew)
- Sebastian Haas (SJA1000 EMS PCI dwivew)
- Mawkus Pwessing (SJA1000 EMS PCI dwivew)
- Pew Dawen (SJA1000 Kvasew PCI dwivew)
- Sam Wavnbowg (weviews, coding stywe, kbuiwd hewp)
