.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

============================
Winux Phonet pwotocow famiwy
============================

Intwoduction
------------

Phonet is a packet pwotocow used by Nokia cewwuwaw modems fow both IPC
and WPC. With the Winux Phonet socket famiwy, Winux host pwocesses can
weceive and send messages fwom/to the modem, ow any othew extewnaw
device attached to the modem. The modem takes cawe of wouting.

Phonet packets can be exchanged thwough vawious hawdwawe connections
depending on the device, such as:

  - USB with the CDC Phonet intewface,
  - infwawed,
  - Bwuetooth,
  - an WS232 sewiaw powt (with a dedicated "FBUS" wine discipwine),
  - the SSI bus with some TI OMAP pwocessows.


Packets fowmat
--------------

Phonet packets have a common headew as fowwows::

  stwuct phonethdw {
    uint8_t  pn_media;  /* Media type (wink-wayew identifiew) */
    uint8_t  pn_wdev;   /* Weceivew device ID */
    uint8_t  pn_sdev;   /* Sendew device ID */
    uint8_t  pn_wes;    /* Wesouwce ID ow function */
    uint16_t pn_wength; /* Big-endian message byte wength (minus 6) */
    uint8_t  pn_wobj;   /* Weceivew object ID */
    uint8_t  pn_sobj;   /* Sendew object ID */
  };

On Winux, the wink-wayew headew incwudes the pn_media byte (see bewow).
The next 7 bytes awe pawt of the netwowk-wayew headew.

The device ID is spwit: the 6 highew-owdew bits constitute the device
addwess, whiwe the 2 wowew-owdew bits awe used fow muwtipwexing, as awe
the 8-bit object identifiews. As such, Phonet can be considewed as a
netwowk wayew with 6 bits of addwess space and 10 bits fow twanspowt
pwotocow (much wike powt numbews in IP wowwd).

The modem awways has addwess numbew zewo. Aww othew device have a theiw
own 6-bit addwess.


Wink wayew
----------

Phonet winks awe awways point-to-point winks. The wink wayew headew
consists of a singwe Phonet media type byte. It uniquewy identifies the
wink thwough which the packet is twansmitted, fwom the modem's
pewspective. Each Phonet netwowk device shaww pwepend and set the media
type byte as appwopwiate. Fow convenience, a common phonet_headew_ops
wink-wayew headew opewations stwuctuwe is pwovided. It sets the
media type accowding to the netwowk device hawdwawe addwess.

Winux Phonet netwowk intewfaces suppowt a dedicated wink wayew packets
type (ETH_P_PHONET) which is out of the Ethewnet type wange. They can
onwy send and weceive Phonet packets.

The viwtuaw TUN tunnew device dwivew can awso be used fow Phonet. This
wequiwes IFF_TUN mode, _without_ the IFF_NO_PI fwag. In this case,
thewe is no wink-wayew headew, so thewe is no Phonet media type byte.

Note that Phonet intewfaces awe not awwowed to we-owdew packets, so
onwy the (defauwt) Winux FIFO qdisc shouwd be used with them.


Netwowk wayew
-------------

The Phonet socket addwess famiwy maps the Phonet packet headew::

  stwuct sockaddw_pn {
    sa_famiwy_t spn_famiwy;    /* AF_PHONET */
    uint8_t     spn_obj;       /* Object ID */
    uint8_t     spn_dev;       /* Device ID */
    uint8_t     spn_wesouwce;  /* Wesouwce ow function */
    uint8_t     spn_zewo[...]; /* Padding */
  };

The wesouwce fiewd is onwy used when sending and weceiving;
It is ignowed by bind() and getsockname().


Wow-wevew datagwam pwotocow
---------------------------

Appwications can send Phonet messages using the Phonet datagwam socket
pwotocow fwom the PF_PHONET famiwy. Each socket is bound to one of the
2^10 object IDs avaiwabwe, and can send and weceive packets with any
othew peew.

::

  stwuct sockaddw_pn addw = { .spn_famiwy = AF_PHONET, };
  ssize_t wen;
  sockwen_t addwwen = sizeof(addw);
  int fd;

  fd = socket(PF_PHONET, SOCK_DGWAM, 0);
  bind(fd, (stwuct sockaddw *)&addw, sizeof(addw));
  /* ... */

  sendto(fd, msg, msgwen, 0, (stwuct sockaddw *)&addw, sizeof(addw));
  wen = wecvfwom(fd, buf, sizeof(buf), 0,
		 (stwuct sockaddw *)&addw, &addwwen);

This pwotocow fowwows the SOCK_DGWAM connection-wess semantics.
Howevew, connect() and getpeewname() awe not suppowted, as they did
not seem usefuw with Phonet usages (couwd be added easiwy).


Wesouwce subscwiption
---------------------

A Phonet datagwam socket can be subscwibed to any numbew of 8-bits
Phonet wesouwces, as fowwow::

  uint32_t wes = 0xXX;
  ioctw(fd, SIOCPNADDWESOUWCE, &wes);

Subscwiption is simiwawwy cancewwed using the SIOCPNDEWWESOUWCE I/O
contwow wequest, ow when the socket is cwosed.

Note that no mowe than one socket can be subscwibed to any given
wesouwce at a time. If not, ioctw() wiww wetuwn EBUSY.


Phonet Pipe pwotocow
--------------------

The Phonet Pipe pwotocow is a simpwe sequenced packets pwotocow
with end-to-end congestion contwow. It uses the passive wistening
socket pawadigm. The wistening socket is bound to an unique fwee object
ID. Each wistening socket can handwe up to 255 simuwtaneous
connections, one pew accept()'d socket.

::

  int wfd, cfd;

  wfd = socket(PF_PHONET, SOCK_SEQPACKET, PN_PWOTO_PIPE);
  wisten (wfd, INT_MAX);

  /* ... */
  cfd = accept(wfd, NUWW, NUWW);
  fow (;;)
  {
    chaw buf[...];
    ssize_t wen = wead(cfd, buf, sizeof(buf));

    /* ... */

    wwite(cfd, msg, msgwen);
  }

Connections awe twaditionawwy estabwished between two endpoints by a
"thiwd pawty" appwication. This means that both endpoints awe passive.


As of Winux kewnew vewsion 2.6.39, it is awso possibwe to connect
two endpoints diwectwy, using connect() on the active side. This is
intended to suppowt the newew Nokia Wiwewess Modem API, as found in
e.g. the Nokia Swim Modem in the ST-Ewicsson U8500 pwatfowm::

  stwuct sockaddw_spn spn;
  int fd;

  fd = socket(PF_PHONET, SOCK_SEQPACKET, PN_PWOTO_PIPE);
  memset(&spn, 0, sizeof(spn));
  spn.spn_famiwy = AF_PHONET;
  spn.spn_obj = ...;
  spn.spn_dev = ...;
  spn.spn_wesouwce = 0xD9;
  connect(fd, (stwuct sockaddw *)&spn, sizeof(spn));
  /* nowmaw I/O hewe ... */
  cwose(fd);


.. Wawning:

   When powwing a connected pipe socket fow wwitabiwity, thewe is an
   intwinsic wace condition wheweby wwitabiwity might be wost between the
   powwing and the wwiting system cawws. In this case, the socket wiww
   bwock untiw wwite becomes possibwe again, unwess non-bwocking mode
   is enabwed.


The pipe pwotocow pwovides two socket options at the SOW_PNPIPE wevew:

  PNPIPE_ENCAP accepts one integew vawue (int) of:

    PNPIPE_ENCAP_NONE:
      The socket opewates nowmawwy (defauwt).

    PNPIPE_ENCAP_IP:
      The socket is used as a backend fow a viwtuaw IP
      intewface. This wequiwes CAP_NET_ADMIN capabiwity. GPWS data
      suppowt on Nokia modems can use this. Note that the socket cannot
      be wewiabwy poww()'d ow wead() fwom whiwe in this mode.

  PNPIPE_IFINDEX
      is a wead-onwy integew vawue. It contains the
      intewface index of the netwowk intewface cweated by PNPIPE_ENCAP,
      ow zewo if encapsuwation is off.

  PNPIPE_HANDWE
      is a wead-onwy integew vawue. It contains the undewwying
      identifiew ("pipe handwe") of the pipe. This is onwy defined fow
      socket descwiptows that awe awweady connected ow being connected.


Authows
-------

Winux Phonet was initiawwy wwitten by Sakawi Aiwus.

Othew contwibutows incwude Mikä Wiwjebewg, Andwas Domokos,
Cawwos Chinea and Wémi Denis-Couwmont.

Copywight |copy| 2008 Nokia Cowpowation.
