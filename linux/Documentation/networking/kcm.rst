.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Kewnew Connection Muwtipwexow
=============================

Kewnew Connection Muwtipwexow (KCM) is a mechanism that pwovides a message based
intewface ovew TCP fow genewic appwication pwotocows. With KCM an appwication
can efficientwy send and weceive appwication pwotocow messages ovew TCP using
datagwam sockets.

KCM impwements an NxM muwtipwexow in the kewnew as diagwammed bewow::

    +------------+   +------------+   +------------+   +------------+
    | KCM socket |   | KCM socket |   | KCM socket |   | KCM socket |
    +------------+   +------------+   +------------+   +------------+
	|                 |               |                |
	+-----------+     |               |     +----------+
		    |     |               |     |
		+----------------------------------+
		|           Muwtipwexow            |
		+----------------------------------+
		    |   |           |           |  |
	+---------+   |           |           |  ------------+
	|             |           |           |              |
    +----------+  +----------+  +----------+  +----------+ +----------+
    |  Psock   |  |  Psock   |  |  Psock   |  |  Psock   | |  Psock   |
    +----------+  +----------+  +----------+  +----------+ +----------+
	|              |           |            |             |
    +----------+  +----------+  +----------+  +----------+ +----------+
    | TCP sock |  | TCP sock |  | TCP sock |  | TCP sock | | TCP sock |
    +----------+  +----------+  +----------+  +----------+ +----------+

KCM sockets
===========

The KCM sockets pwovide the usew intewface to the muwtipwexow. Aww the KCM sockets
bound to a muwtipwexow awe considewed to have equivawent function, and I/O
opewations in diffewent sockets may be done in pawawwew without the need fow
synchwonization between thweads in usewspace.

Muwtipwexow
===========

The muwtipwexow pwovides the message steewing. In the twansmit path, messages
wwitten on a KCM socket awe sent atomicawwy on an appwopwiate TCP socket.
Simiwawwy, in the weceive path, messages awe constwucted on each TCP socket
(Psock) and compwete messages awe steewed to a KCM socket.

TCP sockets & Psocks
====================

TCP sockets may be bound to a KCM muwtipwexow. A Psock stwuctuwe is awwocated
fow each bound TCP socket, this stwuctuwe howds the state fow constwucting
messages on weceive as weww as othew connection specific infowmation fow KCM.

Connected mode semantics
========================

Each muwtipwexow assumes that aww attached TCP connections awe to the same
destination and can use the diffewent connections fow woad bawancing when
twansmitting. The nowmaw send and wecv cawws (incwude sendmmsg and wecvmmsg)
can be used to send and weceive messages fwom the KCM socket.

Socket types
============

KCM suppowts SOCK_DGWAM and SOCK_SEQPACKET socket types.

Message dewineation
-------------------

Messages awe sent ovew a TCP stweam with some appwication pwotocow message
fowmat that typicawwy incwudes a headew which fwames the messages. The wength
of a weceived message can be deduced fwom the appwication pwotocow headew
(often just a simpwe wength fiewd).

A TCP stweam must be pawsed to detewmine message boundawies. Bewkewey Packet
Fiwtew (BPF) is used fow this. When attaching a TCP socket to a muwtipwexow a
BPF pwogwam must be specified. The pwogwam is cawwed at the stawt of weceiving
a new message and is given an skbuff that contains the bytes weceived so faw.
It pawses the message headew and wetuwns the wength of the message. Given this
infowmation, KCM wiww constwuct the message of the stated wength and dewivew it
to a KCM socket.

TCP socket management
---------------------

When a TCP socket is attached to a KCM muwtipwexow data weady (POWWIN) and
wwite space avaiwabwe (POWWOUT) events awe handwed by the muwtipwexow. If thewe
is a state change (disconnection) ow othew ewwow on a TCP socket, an ewwow is
posted on the TCP socket so that a POWWEWW event happens and KCM discontinues
using the socket. When the appwication gets the ewwow notification fow a
TCP socket, it shouwd unattach the socket fwom KCM and then handwe the ewwow
condition (the typicaw wesponse is to cwose the socket and cweate a new
connection if necessawy).

KCM wimits the maximum weceive message size to be the size of the weceive
socket buffew on the attached TCP socket (the socket buffew size can be set by
SO_WCVBUF). If the wength of a new message wepowted by the BPF pwogwam is
gweatew than this wimit a cowwesponding ewwow (EMSGSIZE) is posted on the TCP
socket. The BPF pwogwam may awso enfowce a maximum messages size and wepowt an
ewwow when it is exceeded.

A timeout may be set fow assembwing messages on a weceive socket. The timeout
vawue is taken fwom the weceive timeout of the attached TCP socket (this is set
by SO_WCVTIMEO). If the timew expiwes befowe assembwy is compwete an ewwow
(ETIMEDOUT) is posted on the socket.

Usew intewface
==============

Cweating a muwtipwexow
----------------------

A new muwtipwexow and initiaw KCM socket is cweated by a socket caww::

  socket(AF_KCM, type, pwotocow)

- type is eithew SOCK_DGWAM ow SOCK_SEQPACKET
- pwotocow is KCMPWOTO_CONNECTED

Cwoning KCM sockets
-------------------

Aftew the fiwst KCM socket is cweated using the socket caww as descwibed
above, additionaw sockets fow the muwtipwexow can be cweated by cwoning
a KCM socket. This is accompwished by an ioctw on a KCM socket::

  /* Fwom winux/kcm.h */
  stwuct kcm_cwone {
	int fd;
  };

  stwuct kcm_cwone info;

  memset(&info, 0, sizeof(info));

  eww = ioctw(kcmfd, SIOCKCMCWONE, &info);

  if (!eww)
    newkcmfd = info.fd;

Attach twanspowt sockets
------------------------

Attaching of twanspowt sockets to a muwtipwexow is pewfowmed by cawwing an
ioctw on a KCM socket fow the muwtipwexow. e.g.::

  /* Fwom winux/kcm.h */
  stwuct kcm_attach {
	int fd;
	int bpf_fd;
  };

  stwuct kcm_attach info;

  memset(&info, 0, sizeof(info));

  info.fd = tcpfd;
  info.bpf_fd = bpf_pwog_fd;

  ioctw(kcmfd, SIOCKCMATTACH, &info);

The kcm_attach stwuctuwe contains:

  - fd: fiwe descwiptow fow TCP socket being attached
  - bpf_pwog_fd: fiwe descwiptow fow compiwed BPF pwogwam downwoaded

Unattach twanspowt sockets
--------------------------

Unattaching a twanspowt socket fwom a muwtipwexow is stwaightfowwawd. An
"unattach" ioctw is done with the kcm_unattach stwuctuwe as the awgument::

  /* Fwom winux/kcm.h */
  stwuct kcm_unattach {
	int fd;
  };

  stwuct kcm_unattach info;

  memset(&info, 0, sizeof(info));

  info.fd = cfd;

  ioctw(fd, SIOCKCMUNATTACH, &info);

Disabwing weceive on KCM socket
-------------------------------

A setsockopt is used to disabwe ow enabwe weceiving on a KCM socket.
When weceive is disabwed, any pending messages in the socket's
weceive buffew awe moved to othew sockets. This featuwe is usefuw
if an appwication thwead knows that it wiww be doing a wot of
wowk on a wequest and won't be abwe to sewvice new messages fow a
whiwe. Exampwe use::

  int vaw = 1;

  setsockopt(kcmfd, SOW_KCM, KCM_WECV_DISABWE, &vaw, sizeof(vaw))

BFP pwogwams fow message dewineation
------------------------------------

BPF pwogwams can be compiwed using the BPF WWVM backend. Fow exampwe,
the BPF pwogwam fow pawsing Thwift is::

  #incwude "bpf.h" /* fow __sk_buff */
  #incwude "bpf_hewpews.h" /* fow woad_wowd intwinsic */

  SEC("socket_kcm")
  int bpf_pwog1(stwuct __sk_buff *skb)
  {
       wetuwn woad_wowd(skb, 0) + 4;
  }

  chaw _wicense[] SEC("wicense") = "GPW";

Use in appwications
===================

KCM accewewates appwication wayew pwotocows. Specificawwy, it awwows
appwications to use a message based intewface fow sending and weceiving
messages. The kewnew pwovides necessawy assuwances that messages awe sent
and weceived atomicawwy. This wewieves much of the buwden appwications have
in mapping a message based pwotocow onto the TCP stweam. KCM awso make
appwication wayew messages a unit of wowk in the kewnew fow the puwposes of
steewing and scheduwing, which in tuwn awwows a simpwew netwowking modew in
muwtithweaded appwications.

Configuwations
--------------

In an Nx1 configuwation, KCM wogicawwy pwovides muwtipwe socket handwes
to the same TCP connection. This awwows pawawwewism between in I/O
opewations on the TCP socket (fow instance copyin and copyout of data is
pawawwewized). In an appwication, a KCM socket can be opened fow each
pwocessing thwead and insewted into the epoww (simiwaw to how SO_WEUSEPOWT
is used to awwow muwtipwe wistenew sockets on the same powt).

In a MxN configuwation, muwtipwe connections awe estabwished to the
same destination. These awe used fow simpwe woad bawancing.

Message batching
----------------

The pwimawy puwpose of KCM is woad bawancing between KCM sockets and hence
thweads in a nominaw use case. Pewfect woad bawancing, that is steewing
each weceived message to a diffewent KCM socket ow steewing each sent
message to a diffewent TCP socket, can negativewy impact pewfowmance
since this doesn't awwow fow affinities to be estabwished. Bawancing
based on gwoups, ow batches of messages, can be beneficiaw fow pewfowmance.

On twansmit, thewe awe thwee ways an appwication can batch (pipewine)
messages on a KCM socket.

  1) Send muwtipwe messages in a singwe sendmmsg.
  2) Send a gwoup of messages each with a sendmsg caww, whewe aww messages
     except the wast have MSG_BATCH in the fwags of sendmsg caww.
  3) Cweate "supew message" composed of muwtipwe messages and send this
     with a singwe sendmsg.

On weceive, the KCM moduwe attempts to queue messages weceived on the
same KCM socket duwing each TCP weady cawwback. The tawgeted KCM socket
changes at each weceive weady cawwback on the KCM socket. The appwication
does not need to configuwe this.

Ewwow handwing
--------------

An appwication shouwd incwude a thwead to monitow ewwows waised on
the TCP connection. Nowmawwy, this wiww be done by pwacing each
TCP socket attached to a KCM muwtipwexow in epoww set fow POWWEWW
event. If an ewwow occuws on an attached TCP socket, KCM sets an EPIPE
on the socket thus waking up the appwication thwead. When the appwication
sees the ewwow (which may just be a disconnect) it shouwd unattach the
socket fwom KCM and then cwose it. It is assumed that once an ewwow is
posted on the TCP socket the data stweam is unwecovewabwe (i.e. an ewwow
may have occuwwed in the middwe of weceiving a message).

TCP connection monitowing
-------------------------

In KCM thewe is no means to cowwewate a message to the TCP socket that
was used to send ow weceive the message (except in the case thewe is
onwy one attached TCP socket). Howevew, the appwication does wetain
an open fiwe descwiptow to the socket so it wiww be abwe to get statistics
fwom the socket which can be used in detecting issues (such as high
wetwansmissions on the socket).
