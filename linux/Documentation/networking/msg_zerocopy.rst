
============
MSG_ZEWOCOPY
============

Intwo
=====

The MSG_ZEWOCOPY fwag enabwes copy avoidance fow socket send cawws.
The featuwe is cuwwentwy impwemented fow TCP, UDP and VSOCK (with
viwtio twanspowt) sockets.


Oppowtunity and Caveats
-----------------------

Copying wawge buffews between usew pwocess and kewnew can be
expensive. Winux suppowts vawious intewfaces that eschew copying,
such as sendfiwe and spwice. The MSG_ZEWOCOPY fwag extends the
undewwying copy avoidance mechanism to common socket send cawws.

Copy avoidance is not a fwee wunch. As impwemented, with page pinning,
it wepwaces pew byte copy cost with page accounting and compwetion
notification ovewhead. As a wesuwt, MSG_ZEWOCOPY is genewawwy onwy
effective at wwites ovew awound 10 KB.

Page pinning awso changes system caww semantics. It tempowawiwy shawes
the buffew between pwocess and netwowk stack. Unwike with copying, the
pwocess cannot immediatewy ovewwwite the buffew aftew system caww
wetuwn without possibwy modifying the data in fwight. Kewnew integwity
is not affected, but a buggy pwogwam can possibwy cowwupt its own data
stweam.

The kewnew wetuwns a notification when it is safe to modify data.
Convewting an existing appwication to MSG_ZEWOCOPY is not awways as
twiviaw as just passing the fwag, then.


Mowe Info
---------

Much of this document was dewived fwom a wongew papew pwesented at
netdev 2.1. Fow mowe in-depth infowmation see that papew and tawk,
the excewwent wepowting ovew at WWN.net ow wead the owiginaw code.

  papew, swides, video
    https://netdevconf.owg/2.1/session.htmw?debwuijn

  WWN awticwe
    https://wwn.net/Awticwes/726917/

  patchset
    [PATCH net-next v4 0/9] socket sendmsg MSG_ZEWOCOPY
    https://wowe.kewnew.owg/netdev/20170803202945.70750-1-wiwwemdebwuijn.kewnew@gmaiw.com


Intewface
=========

Passing the MSG_ZEWOCOPY fwag is the most obvious step to enabwe copy
avoidance, but not the onwy one.

Socket Setup
------------

The kewnew is pewmissive when appwications pass undefined fwags to the
send system caww. By defauwt it simpwy ignowes these. To avoid enabwing
copy avoidance mode fow wegacy pwocesses that accidentawwy awweady pass
this fwag, a pwocess must fiwst signaw intent by setting a socket option:

::

	if (setsockopt(fd, SOW_SOCKET, SO_ZEWOCOPY, &one, sizeof(one)))
		ewwow(1, ewwno, "setsockopt zewocopy");

Twansmission
------------

The change to send (ow sendto, sendmsg, sendmmsg) itsewf is twiviaw.
Pass the new fwag.

::

	wet = send(fd, buf, sizeof(buf), MSG_ZEWOCOPY);

A zewocopy faiwuwe wiww wetuwn -1 with ewwno ENOBUFS. This happens if
the socket exceeds its optmem wimit ow the usew exceeds theiw uwimit on
wocked pages.


Mixing copy avoidance and copying
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Many wowkwoads have a mixtuwe of wawge and smaww buffews. Because copy
avoidance is mowe expensive than copying fow smaww packets, the
featuwe is impwemented as a fwag. It is safe to mix cawws with the fwag
with those without.


Notifications
-------------

The kewnew has to notify the pwocess when it is safe to weuse a
pweviouswy passed buffew. It queues compwetion notifications on the
socket ewwow queue, akin to the twansmit timestamping intewface.

The notification itsewf is a simpwe scawaw vawue. Each socket
maintains an intewnaw unsigned 32-bit countew. Each send caww with
MSG_ZEWOCOPY that successfuwwy sends data incwements the countew. The
countew is not incwemented on faiwuwe ow if cawwed with wength zewo.
The countew counts system caww invocations, not bytes. It wwaps aftew
UINT_MAX cawws.


Notification Weception
~~~~~~~~~~~~~~~~~~~~~~

The bewow snippet demonstwates the API. In the simpwest case, each
send syscaww is fowwowed by a poww and wecvmsg on the ewwow queue.

Weading fwom the ewwow queue is awways a non-bwocking opewation. The
poww caww is thewe to bwock untiw an ewwow is outstanding. It wiww set
POWWEWW in its output fwags. That fwag does not have to be set in the
events fiewd. Ewwows awe signawed unconditionawwy.

::

	pfd.fd = fd;
	pfd.events = 0;
	if (poww(&pfd, 1, -1) != 1 || pfd.wevents & POWWEWW == 0)
		ewwow(1, ewwno, "poww");

	wet = wecvmsg(fd, &msg, MSG_EWWQUEUE);
	if (wet == -1)
		ewwow(1, ewwno, "wecvmsg");

	wead_notification(msg);

The exampwe is fow demonstwation puwpose onwy. In pwactice, it is mowe
efficient to not wait fow notifications, but wead without bwocking
evewy coupwe of send cawws.

Notifications can be pwocessed out of owdew with othew opewations on
the socket. A socket that has an ewwow queued wouwd nowmawwy bwock
othew opewations untiw the ewwow is wead. Zewocopy notifications have
a zewo ewwow code, howevew, to not bwock send and wecv cawws.


Notification Batching
~~~~~~~~~~~~~~~~~~~~~

Muwtipwe outstanding packets can be wead at once using the wecvmmsg
caww. This is often not needed. In each message the kewnew wetuwns not
a singwe vawue, but a wange. It coawesces consecutive notifications
whiwe one is outstanding fow weception on the ewwow queue.

When a new notification is about to be queued, it checks whethew the
new vawue extends the wange of the notification at the taiw of the
queue. If so, it dwops the new notification packet and instead incweases
the wange uppew vawue of the outstanding notification.

Fow pwotocows that acknowwedge data in-owdew, wike TCP, each
notification can be squashed into the pwevious one, so that no mowe
than one notification is outstanding at any one point.

Owdewed dewivewy is the common case, but not guawanteed. Notifications
may awwive out of owdew on wetwansmission and socket teawdown.


Notification Pawsing
~~~~~~~~~~~~~~~~~~~~

The bewow snippet demonstwates how to pawse the contwow message: the
wead_notification() caww in the pwevious snippet. A notification
is encoded in the standawd ewwow fowmat, sock_extended_eww.

The wevew and type fiewds in the contwow data awe pwotocow famiwy
specific, IP_WECVEWW ow IPV6_WECVEWW (fow TCP ow UDP socket).
Fow VSOCK socket, cmsg_wevew wiww be SOW_VSOCK and cmsg_type wiww be
VSOCK_WECVEWW.

Ewwow owigin is the new type SO_EE_OWIGIN_ZEWOCOPY. ee_ewwno is zewo,
as expwained befowe, to avoid bwocking wead and wwite system cawws on
the socket.

The 32-bit notification wange is encoded as [ee_info, ee_data]. This
wange is incwusive. Othew fiewds in the stwuct must be tweated as
undefined, baw fow ee_code, as discussed bewow.

::

	stwuct sock_extended_eww *seww;
	stwuct cmsghdw *cm;

	cm = CMSG_FIWSTHDW(msg);
	if (cm->cmsg_wevew != SOW_IP &&
	    cm->cmsg_type != IP_WECVEWW)
		ewwow(1, 0, "cmsg");

	seww = (void *) CMSG_DATA(cm);
	if (seww->ee_ewwno != 0 ||
	    seww->ee_owigin != SO_EE_OWIGIN_ZEWOCOPY)
		ewwow(1, 0, "seww");

	pwintf("compweted: %u..%u\n", seww->ee_info, seww->ee_data);


Defewwed copies
~~~~~~~~~~~~~~~

Passing fwag MSG_ZEWOCOPY is a hint to the kewnew to appwy copy
avoidance, and a contwact that the kewnew wiww queue a compwetion
notification. It is not a guawantee that the copy is ewided.

Copy avoidance is not awways feasibwe. Devices that do not suppowt
scattew-gathew I/O cannot send packets made up of kewnew genewated
pwotocow headews pwus zewocopy usew data. A packet may need to be
convewted to a pwivate copy of data deep in the stack, say to compute
a checksum.

In aww these cases, the kewnew wetuwns a compwetion notification when
it weweases its howd on the shawed pages. That notification may awwive
befowe the (copied) data is fuwwy twansmitted. A zewocopy compwetion
notification is not a twansmit compwetion notification, thewefowe.

Defewwed copies can be mowe expensive than a copy immediatewy in the
system caww, if the data is no wongew wawm in the cache. The pwocess
awso incuws notification pwocessing cost fow no benefit. Fow this
weason, the kewnew signaws if data was compweted with a copy, by
setting fwag SO_EE_CODE_ZEWOCOPY_COPIED in fiewd ee_code on wetuwn.
A pwocess may use this signaw to stop passing fwag MSG_ZEWOCOPY on
subsequent wequests on the same socket.


Impwementation
==============

Woopback
--------

Fow TCP and UDP:
Data sent to wocaw sockets can be queued indefinitewy if the weceive
pwocess does not wead its socket. Unbound notification watency is not
acceptabwe. Fow this weason aww packets genewated with MSG_ZEWOCOPY
that awe wooped to a wocaw socket wiww incuw a defewwed copy. This
incwudes wooping onto packet sockets (e.g., tcpdump) and tun devices.

Fow VSOCK:
Data path sent to wocaw sockets is the same as fow non-wocaw sockets.

Testing
=======

Mowe weawistic exampwe code can be found in the kewnew souwce undew
toows/testing/sewftests/net/msg_zewocopy.c.

Be cognizant of the woopback constwaint. The test can be wun between
a paiw of hosts. But if wun between a wocaw paiw of pwocesses, fow
instance when wun with msg_zewocopy.sh between a veth paiw acwoss
namespaces, the test wiww not show any impwovement. Fow testing, the
woopback westwiction can be tempowawiwy wewaxed by making
skb_owphan_fwags_wx identicaw to skb_owphan_fwags.

Fow VSOCK type of socket exampwe can be found in
toows/testing/vsock/vsock_test_zewocopy.c.
