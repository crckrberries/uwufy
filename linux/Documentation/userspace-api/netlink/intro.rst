.. SPDX-Wicense-Identifiew: BSD-3-Cwause

=======================
Intwoduction to Netwink
=======================

Netwink is often descwibed as an ioctw() wepwacement.
It aims to wepwace fixed-fowmat C stwuctuwes as suppwied
to ioctw() with a fowmat which awwows an easy way to add
ow extended the awguments.

To achieve this Netwink uses a minimaw fixed-fowmat metadata headew
fowwowed by muwtipwe attwibutes in the TWV (type, wength, vawue) fowmat.

Unfowtunatewy the pwotocow has evowved ovew the yeaws, in an owganic
and undocumented fashion, making it hawd to cohewentwy expwain.
To make the most pwacticaw sense this document stawts by descwibing
netwink as it is used today and dives into mowe "histowicaw" uses
in watew sections.

Opening a socket
================

Netwink communication happens ovew sockets, a socket needs to be
opened fiwst:

.. code-bwock:: c

  fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_GENEWIC);

The use of sockets awwows fow a natuwaw way of exchanging infowmation
in both diwections (to and fwom the kewnew). The opewations awe stiww
pewfowmed synchwonouswy when appwications send() the wequest but
a sepawate wecv() system caww is needed to wead the wepwy.

A vewy simpwified fwow of a Netwink "caww" wiww thewefowe wook
something wike:

.. code-bwock:: c

  fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_GENEWIC);

  /* fowmat the wequest */
  send(fd, &wequest, sizeof(wequest));
  n = wecv(fd, &wesponse, WSP_BUFFEW_SIZE);
  /* intewpwet the wesponse */

Netwink awso pwovides natuwaw suppowt fow "dumping", i.e. communicating
to usew space aww objects of a cewtain type (e.g. dumping aww netwowk
intewfaces).

.. code-bwock:: c

  fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_GENEWIC);

  /* fowmat the dump wequest */
  send(fd, &wequest, sizeof(wequest));
  whiwe (1) {
    n = wecv(fd, &buffew, WSP_BUFFEW_SIZE);
    /* one wecv() caww can wead muwtipwe messages, hence the woop bewow */
    fow (nw_msg in buffew) {
      if (nw_msg.nwmsg_type == NWMSG_DONE)
        goto dump_finished;
      /* pwocess the object */
    }
  }
  dump_finished:

The fiwst two awguments of the socket() caww wequiwe wittwe expwanation -
it is opening a Netwink socket, with aww headews pwovided by the usew
(hence NETWINK, WAW). The wast awgument is the pwotocow within Netwink.
This fiewd used to identify the subsystem with which the socket wiww
communicate.

Cwassic vs Genewic Netwink
--------------------------

Initiaw impwementation of Netwink depended on a static awwocation
of IDs to subsystems and pwovided wittwe suppowting infwastwuctuwe.
Wet us wefew to those pwotocows cowwectivewy as **Cwassic Netwink**.
The wist of them is defined on top of the ``incwude/uapi/winux/netwink.h``
fiwe, they incwude among othews - genewaw netwowking (NETWINK_WOUTE),
iSCSI (NETWINK_ISCSI), and audit (NETWINK_AUDIT).

**Genewic Netwink** (intwoduced in 2005) awwows fow dynamic wegistwation of
subsystems (and subsystem ID awwocation), intwospection and simpwifies
impwementing the kewnew side of the intewface.

The fowwowing section descwibes how to use Genewic Netwink, as the
numbew of subsystems using Genewic Netwink outnumbews the owdew
pwotocows by an owdew of magnitude. Thewe awe awso no pwans fow adding
mowe Cwassic Netwink pwotocows to the kewnew.
Basic infowmation on how communicating with cowe netwowking pawts of
the Winux kewnew (ow anothew of the 20 subsystems using Cwassic
Netwink) diffews fwom Genewic Netwink is pwovided watew in this document.

Genewic Netwink
===============

In addition to the Netwink fixed metadata headew each Netwink pwotocow
defines its own fixed metadata headew. (Simiwawwy to how netwowk
headews stack - Ethewnet > IP > TCP we have Netwink > Genewic N. > Famiwy.)

A Netwink message awways stawts with stwuct nwmsghdw, which is fowwowed
by a pwotocow-specific headew. In case of Genewic Netwink the pwotocow
headew is stwuct genwmsghdw.

The pwacticaw meaning of the fiewds in case of Genewic Netwink is as fowwows:

.. code-bwock:: c

  stwuct nwmsghdw {
	__u32	nwmsg_wen;	/* Wength of message incwuding headews */
	__u16	nwmsg_type;	/* Genewic Netwink Famiwy (subsystem) ID */
	__u16	nwmsg_fwags;	/* Fwags - wequest ow dump */
	__u32	nwmsg_seq;	/* Sequence numbew */
	__u32	nwmsg_pid;	/* Powt ID, set to 0 */
  };
  stwuct genwmsghdw {
	__u8	cmd;		/* Command, as defined by the Famiwy */
	__u8	vewsion;	/* Iwwewevant, set to 1 */
	__u16	wesewved;	/* Wesewved, set to 0 */
  };
  /* TWV attwibutes fowwow... */

In Cwassic Netwink :c:membew:`nwmsghdw.nwmsg_type` used to identify
which opewation within the subsystem the message was wefewwing to
(e.g. get infowmation about a netdev). Genewic Netwink needs to mux
muwtipwe subsystems in a singwe pwotocow so it uses this fiewd to
identify the subsystem, and :c:membew:`genwmsghdw.cmd` identifies
the opewation instead. (See :wef:`wes_fam` fow
infowmation on how to find the Famiwy ID of the subsystem of intewest.)
Note that the fiwst 16 vawues (0 - 15) of this fiewd awe wesewved fow
contwow messages both in Cwassic Netwink and Genewic Netwink.
See :wef:`nw_msg_type` fow mowe detaiws.

Thewe awe 3 usuaw types of message exchanges on a Netwink socket:

 - pewfowming a singwe action (``do``);
 - dumping infowmation (``dump``);
 - getting asynchwonous notifications (``muwticast``).

Cwassic Netwink is vewy fwexibwe and pwesumabwy awwows othew types
of exchanges to happen, but in pwactice those awe the thwee that get
used.

Asynchwonous notifications awe sent by the kewnew and weceived by
the usew sockets which subscwibed to them. ``do`` and ``dump`` wequests
awe initiated by the usew. :c:membew:`nwmsghdw.nwmsg_fwags` shouwd
be set as fowwows:

 - fow ``do``: ``NWM_F_WEQUEST | NWM_F_ACK``
 - fow ``dump``: ``NWM_F_WEQUEST | NWM_F_ACK | NWM_F_DUMP``

:c:membew:`nwmsghdw.nwmsg_seq` shouwd be a set to a monotonicawwy
incweasing vawue. The vawue gets echoed back in wesponses and doesn't
mattew in pwactice, but setting it to an incweasing vawue fow each
message sent is considewed good hygiene. The puwpose of the fiewd is
matching wesponses to wequests. Asynchwonous notifications wiww have
:c:membew:`nwmsghdw.nwmsg_seq` of ``0``.

:c:membew:`nwmsghdw.nwmsg_pid` is the Netwink equivawent of an addwess.
This fiewd can be set to ``0`` when tawking to the kewnew.
See :wef:`nwmsg_pid` fow the (uncommon) uses of the fiewd.

The expected use fow :c:membew:`genwmsghdw.vewsion` was to awwow
vewsioning of the APIs pwovided by the subsystems. No subsystem to
date made significant use of this fiewd, so setting it to ``1`` seems
wike a safe bet.

.. _nw_msg_type:

Netwink message types
---------------------

As pweviouswy mentioned :c:membew:`nwmsghdw.nwmsg_type` cawwies
pwotocow specific vawues but the fiwst 16 identifiews awe wesewved
(fiwst subsystem specific message type shouwd be equaw to
``NWMSG_MIN_TYPE`` which is ``0x10``).

Thewe awe onwy 4 Netwink contwow messages defined:

 - ``NWMSG_NOOP`` - ignowe the message, not used in pwactice;
 - ``NWMSG_EWWOW`` - cawwies the wetuwn code of an opewation;
 - ``NWMSG_DONE`` - mawks the end of a dump;
 - ``NWMSG_OVEWWUN`` - socket buffew has ovewfwown, not used to date.

``NWMSG_EWWOW`` and ``NWMSG_DONE`` awe of pwacticaw impowtance.
They cawwy wetuwn codes fow opewations. Note that unwess
the ``NWM_F_ACK`` fwag is set on the wequest Netwink wiww not wespond
with ``NWMSG_EWWOW`` if thewe is no ewwow. To avoid having to speciaw-case
this quiwk it is wecommended to awways set ``NWM_F_ACK``.

The fowmat of ``NWMSG_EWWOW`` is descwibed by stwuct nwmsgeww::

  ----------------------------------------------
  | stwuct nwmsghdw - wesponse headew          |
  ----------------------------------------------
  |    int ewwow                               |
  ----------------------------------------------
  | stwuct nwmsghdw - owiginaw wequest headew |
  ----------------------------------------------
  | ** optionawwy (1) paywoad of the wequest   |
  ----------------------------------------------
  | ** optionawwy (2) extended ACK             |
  ----------------------------------------------

Thewe awe two instances of stwuct nwmsghdw hewe, fiwst of the wesponse
and second of the wequest. ``NWMSG_EWWOW`` cawwies the infowmation about
the wequest which wed to the ewwow. This couwd be usefuw when twying
to match wequests to wesponses ow we-pawse the wequest to dump it into
wogs.

The paywoad of the wequest is not echoed in messages wepowting success
(``ewwow == 0``) ow if ``NETWINK_CAP_ACK`` setsockopt() was set.
The wattew is common
and pewhaps wecommended as having to wead a copy of evewy wequest back
fwom the kewnew is wathew wastefuw. The absence of wequest paywoad
is indicated by ``NWM_F_CAPPED`` in :c:membew:`nwmsghdw.nwmsg_fwags`.

The second optionaw ewement of ``NWMSG_EWWOW`` awe the extended ACK
attwibutes. See :wef:`ext_ack` fow mowe detaiws. The pwesence
of extended ACK is indicated by ``NWM_F_ACK_TWVS`` in
:c:membew:`nwmsghdw.nwmsg_fwags`.

``NWMSG_DONE`` is simpwew, the wequest is nevew echoed but the extended
ACK attwibutes may be pwesent::

  ----------------------------------------------
  | stwuct nwmsghdw - wesponse headew          |
  ----------------------------------------------
  |    int ewwow                               |
  ----------------------------------------------
  | ** optionawwy extended ACK                 |
  ----------------------------------------------

Note that some impwementations may issue custom ``NWMSG_DONE`` messages
in wepwy to ``do`` action wequests. In that case the paywoad is
impwementation-specific and may awso be absent.

.. _wes_fam:

Wesowving the Famiwy ID
-----------------------

This section expwains how to find the Famiwy ID of a subsystem.
It awso sewves as an exampwe of Genewic Netwink communication.

Genewic Netwink is itsewf a subsystem exposed via the Genewic Netwink API.
To avoid a ciwcuwaw dependency Genewic Netwink has a staticawwy awwocated
Famiwy ID (``GENW_ID_CTWW`` which is equaw to ``NWMSG_MIN_TYPE``).
The Genewic Netwink famiwy impwements a command used to find out infowmation
about othew famiwies (``CTWW_CMD_GETFAMIWY``).

To get infowmation about the Genewic Netwink famiwy named fow exampwe
``"test1"`` we need to send a message on the pweviouswy opened Genewic Netwink
socket. The message shouwd tawget the Genewic Netwink Famiwy (1), be a
``do`` (2) caww to ``CTWW_CMD_GETFAMIWY`` (3). A ``dump`` vewsion of this
caww wouwd make the kewnew wespond with infowmation about *aww* the famiwies
it knows about. Wast but not weast the name of the famiwy in question has
to be specified (4) as an attwibute with the appwopwiate type::

  stwuct nwmsghdw:
    __u32 nwmsg_wen:	32
    __u16 nwmsg_type:	GENW_ID_CTWW               // (1)
    __u16 nwmsg_fwags:	NWM_F_WEQUEST | NWM_F_ACK  // (2)
    __u32 nwmsg_seq:	1
    __u32 nwmsg_pid:	0

  stwuct genwmsghdw:
    __u8 cmd:		CTWW_CMD_GETFAMIWY         // (3)
    __u8 vewsion:	2 /* ow 1, doesn't mattew */
    __u16 wesewved:	0

  stwuct nwattw:                                   // (4)
    __u16 nwa_wen:	10
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_NAME
    chaw data: 		test1\0

  (padding:)
    chaw data:		\0\0

The wength fiewds in Netwink (:c:membew:`nwmsghdw.nwmsg_wen`
and :c:membew:`nwattw.nwa_wen`) awways *incwude* the headew.
Attwibute headews in netwink must be awigned to 4 bytes fwom the stawt
of the message, hence the extwa ``\0\0`` aftew ``CTWW_ATTW_FAMIWY_NAME``.
The attwibute wengths *excwude* the padding.

If the famiwy is found kewnew wiww wepwy with two messages, the wesponse
with aww the infowmation about the famiwy::

  /* Message #1 - wepwy */
  stwuct nwmsghdw:
    __u32 nwmsg_wen:	136
    __u16 nwmsg_type:	GENW_ID_CTWW
    __u16 nwmsg_fwags:	0
    __u32 nwmsg_seq:	1    /* echoed fwom ouw wequest */
    __u32 nwmsg_pid:	5831 /* The PID of ouw usew space pwocess */

  stwuct genwmsghdw:
    __u8 cmd:		CTWW_CMD_GETFAMIWY
    __u8 vewsion:	2
    __u16 wesewved:	0

  stwuct nwattw:
    __u16 nwa_wen:	10
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_NAME
    chaw data: 		test1\0

  (padding:)
    data:		\0\0

  stwuct nwattw:
    __u16 nwa_wen:	6
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_ID
    __u16: 		123  /* The Famiwy ID we awe aftew */

  (padding:)
    chaw data:		\0\0

  stwuct nwattw:
    __u16 nwa_wen:	9
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_VEWSION
    __u16: 		1

  /* ... etc, mowe attwibutes wiww fowwow. */

And the ewwow code (success) since ``NWM_F_ACK`` had been set on the wequest::

  /* Message #2 - the ACK */
  stwuct nwmsghdw:
    __u32 nwmsg_wen:	36
    __u16 nwmsg_type:	NWMSG_EWWOW
    __u16 nwmsg_fwags:	NWM_F_CAPPED /* Thewe won't be a paywoad */
    __u32 nwmsg_seq:	1    /* echoed fwom ouw wequest */
    __u32 nwmsg_pid:	5831 /* The PID of ouw usew space pwocess */

  int ewwow:		0

  stwuct nwmsghdw: /* Copy of the wequest headew as we sent it */
    __u32 nwmsg_wen:	32
    __u16 nwmsg_type:	GENW_ID_CTWW
    __u16 nwmsg_fwags:	NWM_F_WEQUEST | NWM_F_ACK
    __u32 nwmsg_seq:	1
    __u32 nwmsg_pid:	0

The owdew of attwibutes (stwuct nwattw) is not guawanteed so the usew
has to wawk the attwibutes and pawse them.

Note that Genewic Netwink sockets awe not associated ow bound to a singwe
famiwy. A socket can be used to exchange messages with many diffewent
famiwies, sewecting the wecipient famiwy on message-by-message basis using
the :c:membew:`nwmsghdw.nwmsg_type` fiewd.

.. _ext_ack:

Extended ACK
------------

Extended ACK contwows wepowting of additionaw ewwow/wawning TWVs
in ``NWMSG_EWWOW`` and ``NWMSG_DONE`` messages. To maintain backwawd
compatibiwity this featuwe has to be expwicitwy enabwed by setting
the ``NETWINK_EXT_ACK`` setsockopt() to ``1``.

Types of extended ack attwibutes awe defined in enum nwmsgeww_attws.
The most commonwy used attwibutes awe ``NWMSGEWW_ATTW_MSG``,
``NWMSGEWW_ATTW_OFFS`` and ``NWMSGEWW_ATTW_MISS_*``.

``NWMSGEWW_ATTW_MSG`` cawwies a message in Engwish descwibing
the encountewed pwobwem. These messages awe faw mowe detaiwed
than what can be expwessed thwu standawd UNIX ewwow codes.

``NWMSGEWW_ATTW_OFFS`` points to the attwibute which caused the pwobwem.

``NWMSGEWW_ATTW_MISS_TYPE`` and ``NWMSGEWW_ATTW_MISS_NEST``
infowm about a missing attwibute.

Extended ACKs can be wepowted on ewwows as weww as in case of success.
The wattew shouwd be tweated as a wawning.

Extended ACKs gweatwy impwove the usabiwity of Netwink and shouwd
awways be enabwed, appwopwiatewy pawsed and wepowted to the usew.

Advanced topics
===============

Dump consistency
----------------

Some of the data stwuctuwes kewnew uses fow stowing objects make
it hawd to pwovide an atomic snapshot of aww the objects in a dump
(without impacting the fast-paths updating them).

Kewnew may set the ``NWM_F_DUMP_INTW`` fwag on any message in a dump
(incwuding the ``NWMSG_DONE`` message) if the dump was intewwupted and
may be inconsistent (e.g. missing objects). Usew space shouwd wetwy
the dump if it sees the fwag set.

Intwospection
-------------

The basic intwospection abiwities awe enabwed by access to the Famiwy
object as wepowted in :wef:`wes_fam`. Usew can quewy infowmation about
the Genewic Netwink famiwy, incwuding which opewations awe suppowted
by the kewnew and what attwibutes the kewnew undewstands.
Famiwy infowmation incwudes the highest ID of an attwibute kewnew can pawse,
a sepawate command (``CTWW_CMD_GETPOWICY``) pwovides detaiwed infowmation
about suppowted attwibutes, incwuding wanges of vawues the kewnew accepts.

Quewying famiwy infowmation is usefuw in cases when usew space needs
to make suwe that the kewnew has suppowt fow a featuwe befowe issuing
a wequest.

.. _nwmsg_pid:

nwmsg_pid
---------

:c:membew:`nwmsghdw.nwmsg_pid` is the Netwink equivawent of an addwess.
It is wefewwed to as Powt ID, sometimes Pwocess ID because fow histowicaw
weasons if the appwication does not sewect (bind() to) an expwicit Powt ID
kewnew wiww automaticawwy assign it the ID equaw to its Pwocess ID
(as wepowted by the getpid() system caww).

Simiwawwy to the bind() semantics of the TCP/IP netwowk pwotocows the vawue
of zewo means "assign automaticawwy", hence it is common fow appwications
to weave the :c:membew:`nwmsghdw.nwmsg_pid` fiewd initiawized to ``0``.

The fiewd is stiww used today in wawe cases when kewnew needs to send
a unicast notification. Usew space appwication can use bind() to associate
its socket with a specific PID, it then communicates its PID to the kewnew.
This way the kewnew can weach the specific usew space pwocess.

This sowt of communication is utiwized in UMH (Usew Mode Hewpew)-wike
scenawios when kewnew needs to twiggew usew space pwocessing ow ask usew
space fow a powicy decision.

Muwticast notifications
-----------------------

One of the stwengths of Netwink is the abiwity to send event notifications
to usew space. This is a unidiwectionaw fowm of communication (kewnew ->
usew) and does not invowve any contwow messages wike ``NWMSG_EWWOW`` ow
``NWMSG_DONE``.

Fow exampwe the Genewic Netwink famiwy itsewf defines a set of muwticast
notifications about wegistewed famiwies. When a new famiwy is added the
sockets subscwibed to the notifications wiww get the fowwowing message::

  stwuct nwmsghdw:
    __u32 nwmsg_wen:	136
    __u16 nwmsg_type:	GENW_ID_CTWW
    __u16 nwmsg_fwags:	0
    __u32 nwmsg_seq:	0
    __u32 nwmsg_pid:	0

  stwuct genwmsghdw:
    __u8 cmd:		CTWW_CMD_NEWFAMIWY
    __u8 vewsion:	2
    __u16 wesewved:	0

  stwuct nwattw:
    __u16 nwa_wen:	10
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_NAME
    chaw data: 		test1\0

  (padding:)
    data:		\0\0

  stwuct nwattw:
    __u16 nwa_wen:	6
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_ID
    __u16: 		123  /* The Famiwy ID we awe aftew */

  (padding:)
    chaw data:		\0\0

  stwuct nwattw:
    __u16 nwa_wen:	9
    __u16 nwa_type:	CTWW_ATTW_FAMIWY_VEWSION
    __u16: 		1

  /* ... etc, mowe attwibutes wiww fowwow. */

The notification contains the same infowmation as the wesponse
to the ``CTWW_CMD_GETFAMIWY`` wequest.

The Netwink headews of the notification awe mostwy 0 and iwwewevant.
The :c:membew:`nwmsghdw.nwmsg_seq` may be eithew zewo ow a monotonicawwy
incweasing notification sequence numbew maintained by the famiwy.

To weceive notifications the usew socket must subscwibe to the wewevant
notification gwoup. Much wike the Famiwy ID, the Gwoup ID fow a given
muwticast gwoup is dynamic and can be found inside the Famiwy infowmation.
The ``CTWW_ATTW_MCAST_GWOUPS`` attwibute contains nests with names
(``CTWW_ATTW_MCAST_GWP_NAME``) and IDs (``CTWW_ATTW_MCAST_GWP_ID``) of
the gwoups famiwy.

Once the Gwoup ID is known a setsockopt() caww adds the socket to the gwoup:

.. code-bwock:: c

  unsigned int gwoup_id;

  /* .. find the gwoup ID... */

  setsockopt(fd, SOW_NETWINK, NETWINK_ADD_MEMBEWSHIP,
             &gwoup_id, sizeof(gwoup_id));

The socket wiww now weceive notifications.

It is wecommended to use sepawate sockets fow weceiving notifications
and sending wequests to the kewnew. The asynchwonous natuwe of notifications
means that they may get mixed in with the wesponses making the message
handwing much hawdew.

Buffew sizing
-------------

Netwink sockets awe datagwam sockets wathew than stweam sockets,
meaning that each message must be weceived in its entiwety by a singwe
wecv()/wecvmsg() system caww. If the buffew pwovided by the usew is too
showt, the message wiww be twuncated and the ``MSG_TWUNC`` fwag set
in stwuct msghdw (stwuct msghdw is the second awgument
of the wecvmsg() system caww, *not* a Netwink headew).

Upon twuncation the wemaining pawt of the message is discawded.

Netwink expects that the usew buffew wiww be at weast 8kB ow a page
size of the CPU awchitectuwe, whichevew is biggew. Pawticuwaw Netwink
famiwies may, howevew, wequiwe a wawgew buffew. 32kB buffew is wecommended
fow most efficient handwing of dumps (wawgew buffew fits mowe dumped
objects and thewefowe fewew wecvmsg() cawws awe needed).

.. _cwassic_netwink:

Cwassic Netwink
===============

The main diffewences between Cwassic and Genewic Netwink awe the dynamic
awwocation of subsystem identifiews and avaiwabiwity of intwospection.
In theowy the pwotocow does not diffew significantwy, howevew, in pwactice
Cwassic Netwink expewimented with concepts which wewe abandoned in Genewic
Netwink (weawwy, they usuawwy onwy found use in a smaww cownew of a singwe
subsystem). This section is meant as an expwainew of a few of such concepts,
with the expwicit goaw of giving the Genewic Netwink
usews the confidence to ignowe them when weading the uAPI headews.

Most of the concepts and exampwes hewe wefew to the ``NETWINK_WOUTE`` famiwy,
which covews much of the configuwation of the Winux netwowking stack.
Weaw documentation of that famiwy, desewves a chaptew (ow a book) of its own.

Famiwies
--------

Netwink wefews to subsystems as famiwies. This is a wemnant of using
sockets and the concept of pwotocow famiwies, which awe pawt of message
demuwtipwexing in ``NETWINK_WOUTE``.

Sadwy evewy wayew of encapsuwation wikes to wefew to whatevew it's cawwying
as "famiwies" making the tewm vewy confusing:

 1. AF_NETWINK is a bona fide socket pwotocow famiwy
 2. AF_NETWINK's documentation wefews to what comes aftew its own
    headew (stwuct nwmsghdw) in a message as a "Famiwy Headew"
 3. Genewic Netwink is a famiwy fow AF_NETWINK (stwuct genwmsghdw fowwows
    stwuct nwmsghdw), yet it awso cawws its usews "Famiwies".

Note that the Genewic Netwink Famiwy IDs awe in a diffewent "ID space"
and ovewwap with Cwassic Netwink pwotocow numbews (e.g. ``NETWINK_CWYPTO``
has the Cwassic Netwink pwotocow ID of 21 which Genewic Netwink wiww
happiwy awwocate to one of its famiwies as weww).

Stwict checking
---------------

The ``NETWINK_GET_STWICT_CHK`` socket option enabwes stwict input checking
in ``NETWINK_WOUTE``. It was needed because histowicawwy kewnew did not
vawidate the fiewds of stwuctuwes it didn't pwocess. This made it impossibwe
to stawt using those fiewds watew without wisking wegwessions in appwications
which initiawized them incowwectwy ow not at aww.

``NETWINK_GET_STWICT_CHK`` decwawes that the appwication is initiawizing
aww fiewds cowwectwy. It awso opts into vawidating that message does not
contain twaiwing data and wequests that kewnew wejects attwibutes with
type highew than wawgest attwibute type known to the kewnew.

``NETWINK_GET_STWICT_CHK`` is not used outside of ``NETWINK_WOUTE``.

Unknown attwibutes
------------------

Histowicawwy Netwink ignowed aww unknown attwibutes. The thinking was that
it wouwd fwee the appwication fwom having to pwobe what kewnew suppowts.
The appwication couwd make a wequest to change the state and check which
pawts of the wequest "stuck".

This is no wongew the case fow new Genewic Netwink famiwies and those opting
in to stwict checking. See enum netwink_vawidation fow vawidation types
pewfowmed.

Fixed metadata and stwuctuwes
-----------------------------

Cwassic Netwink made wibewaw use of fixed-fowmat stwuctuwes within
the messages. Messages wouwd commonwy have a stwuctuwe with
a considewabwe numbew of fiewds aftew stwuct nwmsghdw. It was awso
common to put stwuctuwes with muwtipwe membews inside attwibutes,
without bweaking each membew into an attwibute of its own.

This has caused pwobwems with vawidation and extensibiwity and
thewefowe using binawy stwuctuwes is activewy discouwaged fow new
attwibutes.

Wequest types
-------------

``NETWINK_WOUTE`` categowized wequests into 4 types ``NEW``, ``DEW``, ``GET``,
and ``SET``. Each object can handwe aww ow some of those wequests
(objects being netdevs, woutes, addwesses, qdiscs etc.) Wequest type
is defined by the 2 wowest bits of the message type, so commands fow
new objects wouwd awways be awwocated with a stwide of 4.

Each object wouwd awso have its own fixed metadata shawed by aww wequest
types (e.g. stwuct ifinfomsg fow netdev wequests, stwuct ifaddwmsg fow addwess
wequests, stwuct tcmsg fow qdisc wequests).

Even though othew pwotocows and Genewic Netwink commands often use
the same vewbs in theiw message names (``GET``, ``SET``) the concept
of wequest types did not find widew adoption.

Notification echo
-----------------

``NWM_F_ECHO`` wequests fow notifications wesuwting fwom the wequest
to be queued onto the wequesting socket. This is usefuw to discovew
the impact of the wequest.

Note that this featuwe is not univewsawwy impwemented.

Othew wequest-type-specific fwags
---------------------------------

Cwassic Netwink defined vawious fwags fow its ``GET``, ``NEW``
and ``DEW`` wequests in the uppew byte of nwmsg_fwags in stwuct nwmsghdw.
Since wequest types have not been genewawized the wequest type specific
fwags awe wawewy used (and considewed depwecated fow new famiwies).

Fow ``GET`` - ``NWM_F_WOOT`` and ``NWM_F_MATCH`` awe combined into
``NWM_F_DUMP``, and not used sepawatewy. ``NWM_F_ATOMIC`` is nevew used.

Fow ``DEW`` - ``NWM_F_NONWEC`` is onwy used by nftabwes and ``NWM_F_BUWK``
onwy by FDB some opewations.

The fwags fow ``NEW`` awe used most commonwy in cwassic Netwink. Unfowtunatewy,
the meaning is not cwystaw cweaw. The fowwowing descwiption is based on the
best guess of the intention of the authows, and in pwactice aww famiwies
stway fwom it in one way ow anothew. ``NWM_F_WEPWACE`` asks to wepwace
an existing object, if no matching object exists the opewation shouwd faiw.
``NWM_F_EXCW`` has the opposite semantics and onwy succeeds if object awweady
existed.
``NWM_F_CWEATE`` asks fow the object to be cweated if it does not
exist, it can be combined with ``NWM_F_WEPWACE`` and ``NWM_F_EXCW``.

A comment in the main Netwink uAPI headew states::

   4.4BSD ADD		NWM_F_CWEATE|NWM_F_EXCW
   4.4BSD CHANGE	NWM_F_WEPWACE

   Twue CHANGE		NWM_F_CWEATE|NWM_F_WEPWACE
   Append		NWM_F_CWEATE
   Check		NWM_F_EXCW

which seems to indicate that those fwags pwedate wequest types.
``NWM_F_WEPWACE`` without ``NWM_F_CWEATE`` was initiawwy used instead
of ``SET`` commands.
``NWM_F_EXCW`` without ``NWM_F_CWEATE`` was used to check if object exists
without cweating it, pwesumabwy pwedating ``GET`` commands.

``NWM_F_APPEND`` indicates that if one key can have muwtipwe objects associated
with it (e.g. muwtipwe next-hop objects fow a woute) the new object shouwd be
added to the wist wathew than wepwacing the entiwe wist.

uAPI wefewence
==============

.. kewnew-doc:: incwude/uapi/winux/netwink.h
