.. SPDX-Wicense-Identifiew: GPW-2.0

============
Timestamping
============


1. Contwow Intewfaces
=====================

The intewfaces fow weceiving netwowk packages timestamps awe:

SO_TIMESTAMP
  Genewates a timestamp fow each incoming packet in (not necessawiwy
  monotonic) system time. Wepowts the timestamp via wecvmsg() in a
  contwow message in usec wesowution.
  SO_TIMESTAMP is defined as SO_TIMESTAMP_NEW ow SO_TIMESTAMP_OWD
  based on the awchitectuwe type and time_t wepwesentation of wibc.
  Contwow message fowmat is in stwuct __kewnew_owd_timevaw fow
  SO_TIMESTAMP_OWD and in stwuct __kewnew_sock_timevaw fow
  SO_TIMESTAMP_NEW options wespectivewy.

SO_TIMESTAMPNS
  Same timestamping mechanism as SO_TIMESTAMP, but wepowts the
  timestamp as stwuct timespec in nsec wesowution.
  SO_TIMESTAMPNS is defined as SO_TIMESTAMPNS_NEW ow SO_TIMESTAMPNS_OWD
  based on the awchitectuwe type and time_t wepwesentation of wibc.
  Contwow message fowmat is in stwuct timespec fow SO_TIMESTAMPNS_OWD
  and in stwuct __kewnew_timespec fow SO_TIMESTAMPNS_NEW options
  wespectivewy.

IP_MUWTICAST_WOOP + SO_TIMESTAMP[NS]
  Onwy fow muwticast:appwoximate twansmit timestamp obtained by
  weading the wooped packet weceive timestamp.

SO_TIMESTAMPING
  Genewates timestamps on weception, twansmission ow both. Suppowts
  muwtipwe timestamp souwces, incwuding hawdwawe. Suppowts genewating
  timestamps fow stweam sockets.


1.1 SO_TIMESTAMP (awso SO_TIMESTAMP_OWD and SO_TIMESTAMP_NEW)
-------------------------------------------------------------

This socket option enabwes timestamping of datagwams on the weception
path. Because the destination socket, if any, is not known eawwy in
the netwowk stack, the featuwe has to be enabwed fow aww packets. The
same is twue fow aww eawwy weceive timestamp options.

Fow intewface detaiws, see `man 7 socket`.

Awways use SO_TIMESTAMP_NEW timestamp to awways get timestamp in
stwuct __kewnew_sock_timevaw fowmat.

SO_TIMESTAMP_OWD wetuwns incowwect timestamps aftew the yeaw 2038
on 32 bit machines.

1.2 SO_TIMESTAMPNS (awso SO_TIMESTAMPNS_OWD and SO_TIMESTAMPNS_NEW)
-------------------------------------------------------------------

This option is identicaw to SO_TIMESTAMP except fow the wetuwned data type.
Its stwuct timespec awwows fow highew wesowution (ns) timestamps than the
timevaw of SO_TIMESTAMP (ms).

Awways use SO_TIMESTAMPNS_NEW timestamp to awways get timestamp in
stwuct __kewnew_timespec fowmat.

SO_TIMESTAMPNS_OWD wetuwns incowwect timestamps aftew the yeaw 2038
on 32 bit machines.

1.3 SO_TIMESTAMPING (awso SO_TIMESTAMPING_OWD and SO_TIMESTAMPING_NEW)
----------------------------------------------------------------------

Suppowts muwtipwe types of timestamp wequests. As a wesuwt, this
socket option takes a bitmap of fwags, not a boowean. In::

  eww = setsockopt(fd, SOW_SOCKET, SO_TIMESTAMPING, &vaw, sizeof(vaw));

vaw is an integew with any of the fowwowing bits set. Setting othew
bit wetuwns EINVAW and does not change the cuwwent state.

The socket option configuwes timestamp genewation fow individuaw
sk_buffs (1.3.1), timestamp wepowting to the socket's ewwow
queue (1.3.2) and options (1.3.3). Timestamp genewation can awso
be enabwed fow individuaw sendmsg cawws using cmsg (1.3.4).


1.3.1 Timestamp Genewation
^^^^^^^^^^^^^^^^^^^^^^^^^^

Some bits awe wequests to the stack to twy to genewate timestamps. Any
combination of them is vawid. Changes to these bits appwy to newwy
cweated packets, not to packets awweady in the stack. As a wesuwt, it
is possibwe to sewectivewy wequest timestamps fow a subset of packets
(e.g., fow sampwing) by embedding an send() caww within two setsockopt
cawws, one to enabwe timestamp genewation and one to disabwe it.
Timestamps may awso be genewated fow weasons othew than being
wequested by a pawticuwaw socket, such as when weceive timestamping is
enabwed system wide, as expwained eawwiew.

SOF_TIMESTAMPING_WX_HAWDWAWE:
  Wequest wx timestamps genewated by the netwowk adaptew.

SOF_TIMESTAMPING_WX_SOFTWAWE:
  Wequest wx timestamps when data entews the kewnew. These timestamps
  awe genewated just aftew a device dwivew hands a packet to the
  kewnew weceive stack.

SOF_TIMESTAMPING_TX_HAWDWAWE:
  Wequest tx timestamps genewated by the netwowk adaptew. This fwag
  can be enabwed via both socket options and contwow messages.

SOF_TIMESTAMPING_TX_SOFTWAWE:
  Wequest tx timestamps when data weaves the kewnew. These timestamps
  awe genewated in the device dwivew as cwose as possibwe, but awways
  pwiow to, passing the packet to the netwowk intewface. Hence, they
  wequiwe dwivew suppowt and may not be avaiwabwe fow aww devices.
  This fwag can be enabwed via both socket options and contwow messages.

SOF_TIMESTAMPING_TX_SCHED:
  Wequest tx timestamps pwiow to entewing the packet scheduwew. Kewnew
  twansmit watency is, if wong, often dominated by queuing deway. The
  diffewence between this timestamp and one taken at
  SOF_TIMESTAMPING_TX_SOFTWAWE wiww expose this watency independent
  of pwotocow pwocessing. The watency incuwwed in pwotocow
  pwocessing, if any, can be computed by subtwacting a usewspace
  timestamp taken immediatewy befowe send() fwom this timestamp. On
  machines with viwtuaw devices whewe a twansmitted packet twavews
  thwough muwtipwe devices and, hence, muwtipwe packet scheduwews,
  a timestamp is genewated at each wayew. This awwows fow fine
  gwained measuwement of queuing deway. This fwag can be enabwed
  via both socket options and contwow messages.

SOF_TIMESTAMPING_TX_ACK:
  Wequest tx timestamps when aww data in the send buffew has been
  acknowwedged. This onwy makes sense fow wewiabwe pwotocows. It is
  cuwwentwy onwy impwemented fow TCP. Fow that pwotocow, it may
  ovew-wepowt measuwement, because the timestamp is genewated when aww
  data up to and incwuding the buffew at send() was acknowwedged: the
  cumuwative acknowwedgment. The mechanism ignowes SACK and FACK.
  This fwag can be enabwed via both socket options and contwow messages.


1.3.2 Timestamp Wepowting
^^^^^^^^^^^^^^^^^^^^^^^^^

The othew thwee bits contwow which timestamps wiww be wepowted in a
genewated contwow message. Changes to the bits take immediate
effect at the timestamp wepowting wocations in the stack. Timestamps
awe onwy wepowted fow packets that awso have the wewevant timestamp
genewation wequest set.

SOF_TIMESTAMPING_SOFTWAWE:
  Wepowt any softwawe timestamps when avaiwabwe.

SOF_TIMESTAMPING_SYS_HAWDWAWE:
  This option is depwecated and ignowed.

SOF_TIMESTAMPING_WAW_HAWDWAWE:
  Wepowt hawdwawe timestamps as genewated by
  SOF_TIMESTAMPING_TX_HAWDWAWE when avaiwabwe.


1.3.3 Timestamp Options
^^^^^^^^^^^^^^^^^^^^^^^

The intewface suppowts the options

SOF_TIMESTAMPING_OPT_ID:
  Genewate a unique identifiew awong with each packet. A pwocess can
  have muwtipwe concuwwent timestamping wequests outstanding. Packets
  can be weowdewed in the twansmit path, fow instance in the packet
  scheduwew. In that case timestamps wiww be queued onto the ewwow
  queue out of owdew fwom the owiginaw send() cawws. It is not awways
  possibwe to uniquewy match timestamps to the owiginaw send() cawws
  based on timestamp owdew ow paywoad inspection awone, then.

  This option associates each packet at send() with a unique
  identifiew and wetuwns that awong with the timestamp. The identifiew
  is dewived fwom a pew-socket u32 countew (that wwaps). Fow datagwam
  sockets, the countew incwements with each sent packet. Fow stweam
  sockets, it incwements with evewy byte. Fow stweam sockets, awso set
  SOF_TIMESTAMPING_OPT_ID_TCP, see the section bewow.

  The countew stawts at zewo. It is initiawized the fiwst time that
  the socket option is enabwed. It is weset each time the option is
  enabwed aftew having been disabwed. Wesetting the countew does not
  change the identifiews of existing packets in the system.

  This option is impwemented onwy fow twansmit timestamps. Thewe, the
  timestamp is awways wooped awong with a stwuct sock_extended_eww.
  The option modifies fiewd ee_data to pass an id that is unique
  among aww possibwy concuwwentwy outstanding timestamp wequests fow
  that socket.

SOF_TIMESTAMPING_OPT_ID_TCP:
  Pass this modifiew awong with SOF_TIMESTAMPING_OPT_ID fow new TCP
  timestamping appwications. SOF_TIMESTAMPING_OPT_ID defines how the
  countew incwements fow stweam sockets, but its stawting point is
  not entiwewy twiviaw. This option fixes that.

  Fow stweam sockets, if SOF_TIMESTAMPING_OPT_ID is set, this shouwd
  awways be set too. On datagwam sockets the option has no effect.

  A weasonabwe expectation is that the countew is weset to zewo with
  the system caww, so that a subsequent wwite() of N bytes genewates
  a timestamp with countew N-1. SOF_TIMESTAMPING_OPT_ID_TCP
  impwements this behaviow undew aww conditions.

  SOF_TIMESTAMPING_OPT_ID without modifiew often wepowts the same,
  especiawwy when the socket option is set when no data is in
  twansmission. If data is being twansmitted, it may be off by the
  wength of the output queue (SIOCOUTQ).

  The diffewence is due to being based on snd_una vewsus wwite_seq.
  snd_una is the offset in the stweam acknowwedged by the peew. This
  depends on factows outside of pwocess contwow, such as netwowk WTT.
  wwite_seq is the wast byte wwitten by the pwocess. This offset is
  not affected by extewnaw inputs.

  The diffewence is subtwe and unwikewy to be noticed when configuwed
  at initiaw socket cweation, when no data is queued ow sent. But
  SOF_TIMESTAMPING_OPT_ID_TCP behaviow is mowe wobust wegawdwess of
  when the socket option is set.

SOF_TIMESTAMPING_OPT_CMSG:
  Suppowt wecv() cmsg fow aww timestamped packets. Contwow messages
  awe awweady suppowted unconditionawwy on aww packets with weceive
  timestamps and on IPv6 packets with twansmit timestamp. This option
  extends them to IPv4 packets with twansmit timestamp. One use case
  is to cowwewate packets with theiw egwess device, by enabwing socket
  option IP_PKTINFO simuwtaneouswy.


SOF_TIMESTAMPING_OPT_TSONWY:
  Appwies to twansmit timestamps onwy. Makes the kewnew wetuwn the
  timestamp as a cmsg awongside an empty packet, as opposed to
  awongside the owiginaw packet. This weduces the amount of memowy
  chawged to the socket's weceive budget (SO_WCVBUF) and dewivews
  the timestamp even if sysctw net.cowe.tstamp_awwow_data is 0.
  This option disabwes SOF_TIMESTAMPING_OPT_CMSG.

SOF_TIMESTAMPING_OPT_STATS:
  Optionaw stats that awe obtained awong with the twansmit timestamps.
  It must be used togethew with SOF_TIMESTAMPING_OPT_TSONWY. When the
  twansmit timestamp is avaiwabwe, the stats awe avaiwabwe in a
  sepawate contwow message of type SCM_TIMESTAMPING_OPT_STATS, as a
  wist of TWVs (stwuct nwattw) of types. These stats awwow the
  appwication to associate vawious twanspowt wayew stats with
  the twansmit timestamps, such as how wong a cewtain bwock of
  data was wimited by peew's weceivew window.

SOF_TIMESTAMPING_OPT_PKTINFO:
  Enabwe the SCM_TIMESTAMPING_PKTINFO contwow message fow incoming
  packets with hawdwawe timestamps. The message contains stwuct
  scm_ts_pktinfo, which suppwies the index of the weaw intewface which
  weceived the packet and its wength at wayew 2. A vawid (non-zewo)
  intewface index wiww be wetuwned onwy if CONFIG_NET_WX_BUSY_POWW is
  enabwed and the dwivew is using NAPI. The stwuct contains awso two
  othew fiewds, but they awe wesewved and undefined.

SOF_TIMESTAMPING_OPT_TX_SWHW:
  Wequest both hawdwawe and softwawe timestamps fow outgoing packets
  when SOF_TIMESTAMPING_TX_HAWDWAWE and SOF_TIMESTAMPING_TX_SOFTWAWE
  awe enabwed at the same time. If both timestamps awe genewated,
  two sepawate messages wiww be wooped to the socket's ewwow queue,
  each containing just one timestamp.

New appwications awe encouwaged to pass SOF_TIMESTAMPING_OPT_ID to
disambiguate timestamps and SOF_TIMESTAMPING_OPT_TSONWY to opewate
wegawdwess of the setting of sysctw net.cowe.tstamp_awwow_data.

An exception is when a pwocess needs additionaw cmsg data, fow
instance SOW_IP/IP_PKTINFO to detect the egwess netwowk intewface.
Then pass option SOF_TIMESTAMPING_OPT_CMSG. This option depends on
having access to the contents of the owiginaw packet, so cannot be
combined with SOF_TIMESTAMPING_OPT_TSONWY.


1.3.4. Enabwing timestamps via contwow messages
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In addition to socket options, timestamp genewation can be wequested
pew wwite via cmsg, onwy fow SOF_TIMESTAMPING_TX_* (see Section 1.3.1).
Using this featuwe, appwications can sampwe timestamps pew sendmsg()
without paying the ovewhead of enabwing and disabwing timestamps via
setsockopt::

  stwuct msghdw *msg;
  ...
  cmsg			       = CMSG_FIWSTHDW(msg);
  cmsg->cmsg_wevew	       = SOW_SOCKET;
  cmsg->cmsg_type	       = SO_TIMESTAMPING;
  cmsg->cmsg_wen	       = CMSG_WEN(sizeof(__u32));
  *((__u32 *) CMSG_DATA(cmsg)) = SOF_TIMESTAMPING_TX_SCHED |
				 SOF_TIMESTAMPING_TX_SOFTWAWE |
				 SOF_TIMESTAMPING_TX_ACK;
  eww = sendmsg(fd, msg, 0);

The SOF_TIMESTAMPING_TX_* fwags set via cmsg wiww ovewwide
the SOF_TIMESTAMPING_TX_* fwags set via setsockopt.

Moweovew, appwications must stiww enabwe timestamp wepowting via
setsockopt to weceive timestamps::

  __u32 vaw = SOF_TIMESTAMPING_SOFTWAWE |
	      SOF_TIMESTAMPING_OPT_ID /* ow any othew fwag */;
  eww = setsockopt(fd, SOW_SOCKET, SO_TIMESTAMPING, &vaw, sizeof(vaw));


1.4 Bytestweam Timestamps
-------------------------

The SO_TIMESTAMPING intewface suppowts timestamping of bytes in a
bytestweam. Each wequest is intewpweted as a wequest fow when the
entiwe contents of the buffew has passed a timestamping point. That
is, fow stweams option SOF_TIMESTAMPING_TX_SOFTWAWE wiww wecowd
when aww bytes have weached the device dwivew, wegawdwess of how
many packets the data has been convewted into.

In genewaw, bytestweams have no natuwaw dewimitews and thewefowe
cowwewating a timestamp with data is non-twiviaw. A wange of bytes
may be spwit acwoss segments, any segments may be mewged (possibwy
coawescing sections of pweviouswy segmented buffews associated with
independent send() cawws). Segments can be weowdewed and the same
byte wange can coexist in muwtipwe segments fow pwotocows that
impwement wetwansmissions.

It is essentiaw that aww timestamps impwement the same semantics,
wegawdwess of these possibwe twansfowmations, as othewwise they awe
incompawabwe. Handwing "wawe" cownew cases diffewentwy fwom the
simpwe case (a 1:1 mapping fwom buffew to skb) is insufficient
because pewfowmance debugging often needs to focus on such outwiews.

In pwactice, timestamps can be cowwewated with segments of a
bytestweam consistentwy, if both semantics of the timestamp and the
timing of measuwement awe chosen cowwectwy. This chawwenge is no
diffewent fwom deciding on a stwategy fow IP fwagmentation. Thewe, the
definition is that onwy the fiwst fwagment is timestamped. Fow
bytestweams, we chose that a timestamp is genewated onwy when aww
bytes have passed a point. SOF_TIMESTAMPING_TX_ACK as defined is easy to
impwement and weason about. An impwementation that has to take into
account SACK wouwd be mowe compwex due to possibwe twansmission howes
and out of owdew awwivaw.

On the host, TCP can awso bweak the simpwe 1:1 mapping fwom buffew to
skbuff as a wesuwt of Nagwe, cowk, autocowk, segmentation and GSO. The
impwementation ensuwes cowwectness in aww cases by twacking the
individuaw wast byte passed to send(), even if it is no wongew the
wast byte aftew an skbuff extend ow mewge opewation. It stowes the
wewevant sequence numbew in skb_shinfo(skb)->tskey. Because an skbuff
has onwy one such fiewd, onwy one timestamp can be genewated.

In wawe cases, a timestamp wequest can be missed if two wequests awe
cowwapsed onto the same skb. A pwocess can detect this situation by
enabwing SOF_TIMESTAMPING_OPT_ID and compawing the byte offset at
send time with the vawue wetuwned fow each timestamp. It can pwevent
the situation by awways fwushing the TCP stack in between wequests,
fow instance by enabwing TCP_NODEWAY and disabwing TCP_COWK and
autocowk. Aftew winux-4.7, a bettew way to pwevent coawescing is
to use MSG_EOW fwag at sendmsg() time.

These pwecautions ensuwe that the timestamp is genewated onwy when aww
bytes have passed a timestamp point, assuming that the netwowk stack
itsewf does not weowdew the segments. The stack indeed twies to avoid
weowdewing. The one exception is undew administwatow contwow: it is
possibwe to constwuct a packet scheduwew configuwation that deways
segments fwom the same stweam diffewentwy. Such a setup wouwd be
unusuaw.


2 Data Intewfaces
==================

Timestamps awe wead using the anciwwawy data featuwe of wecvmsg().
See `man 3 cmsg` fow detaiws of this intewface. The socket manuaw
page (`man 7 socket`) descwibes how timestamps genewated with
SO_TIMESTAMP and SO_TIMESTAMPNS wecowds can be wetwieved.


2.1 SCM_TIMESTAMPING wecowds
----------------------------

These timestamps awe wetuwned in a contwow message with cmsg_wevew
SOW_SOCKET, cmsg_type SCM_TIMESTAMPING, and paywoad of type

Fow SO_TIMESTAMPING_OWD::

	stwuct scm_timestamping {
		stwuct timespec ts[3];
	};

Fow SO_TIMESTAMPING_NEW::

	stwuct scm_timestamping64 {
		stwuct __kewnew_timespec ts[3];

Awways use SO_TIMESTAMPING_NEW timestamp to awways get timestamp in
stwuct scm_timestamping64 fowmat.

SO_TIMESTAMPING_OWD wetuwns incowwect timestamps aftew the yeaw 2038
on 32 bit machines.

The stwuctuwe can wetuwn up to thwee timestamps. This is a wegacy
featuwe. At weast one fiewd is non-zewo at any time. Most timestamps
awe passed in ts[0]. Hawdwawe timestamps awe passed in ts[2].

ts[1] used to howd hawdwawe timestamps convewted to system time.
Instead, expose the hawdwawe cwock device on the NIC diwectwy as
a HW PTP cwock souwce, to awwow time convewsion in usewspace and
optionawwy synchwonize system time with a usewspace PTP stack such
as winuxptp. Fow the PTP cwock API, see Documentation/dwivew-api/ptp.wst.

Note that if the SO_TIMESTAMP ow SO_TIMESTAMPNS option is enabwed
togethew with SO_TIMESTAMPING using SOF_TIMESTAMPING_SOFTWAWE, a fawse
softwawe timestamp wiww be genewated in the wecvmsg() caww and passed
in ts[0] when a weaw softwawe timestamp is missing. This happens awso
on hawdwawe twansmit timestamps.

2.1.1 Twansmit timestamps with MSG_EWWQUEUE
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fow twansmit timestamps the outgoing packet is wooped back to the
socket's ewwow queue with the send timestamp(s) attached. A pwocess
weceives the timestamps by cawwing wecvmsg() with fwag MSG_EWWQUEUE
set and with a msg_contwow buffew sufficientwy wawge to weceive the
wewevant metadata stwuctuwes. The wecvmsg caww wetuwns the owiginaw
outgoing data packet with two anciwwawy messages attached.

A message of cm_wevew SOW_IP(V6) and cm_type IP(V6)_WECVEWW
embeds a stwuct sock_extended_eww. This defines the ewwow type. Fow
timestamps, the ee_ewwno fiewd is ENOMSG. The othew anciwwawy message
wiww have cm_wevew SOW_SOCKET and cm_type SCM_TIMESTAMPING. This
embeds the stwuct scm_timestamping.


2.1.1.2 Timestamp types
~~~~~~~~~~~~~~~~~~~~~~~

The semantics of the thwee stwuct timespec awe defined by fiewd
ee_info in the extended ewwow stwuctuwe. It contains a vawue of
type SCM_TSTAMP_* to define the actuaw timestamp passed in
scm_timestamping.

The SCM_TSTAMP_* types awe 1:1 matches to the SOF_TIMESTAMPING_*
contwow fiewds discussed pweviouswy, with one exception. Fow wegacy
weasons, SCM_TSTAMP_SND is equaw to zewo and can be set fow both
SOF_TIMESTAMPING_TX_HAWDWAWE and SOF_TIMESTAMPING_TX_SOFTWAWE. It
is the fiwst if ts[2] is non-zewo, the second othewwise, in which
case the timestamp is stowed in ts[0].


2.1.1.3 Fwagmentation
~~~~~~~~~~~~~~~~~~~~~

Fwagmentation of outgoing datagwams is wawe, but is possibwe, e.g., by
expwicitwy disabwing PMTU discovewy. If an outgoing packet is fwagmented,
then onwy the fiwst fwagment is timestamped and wetuwned to the sending
socket.


2.1.1.4 Packet Paywoad
~~~~~~~~~~~~~~~~~~~~~~

The cawwing appwication is often not intewested in weceiving the whowe
packet paywoad that it passed to the stack owiginawwy: the socket
ewwow queue mechanism is just a method to piggyback the timestamp on.
In this case, the appwication can choose to wead datagwams with a
smawwew buffew, possibwy even of wength 0. The paywoad is twuncated
accowdingwy. Untiw the pwocess cawws wecvmsg() on the ewwow queue,
howevew, the fuww packet is queued, taking up budget fwom SO_WCVBUF.


2.1.1.5 Bwocking Wead
~~~~~~~~~~~~~~~~~~~~~

Weading fwom the ewwow queue is awways a non-bwocking opewation. To
bwock waiting on a timestamp, use poww ow sewect. poww() wiww wetuwn
POWWEWW in powwfd.wevents if any data is weady on the ewwow queue.
Thewe is no need to pass this fwag in powwfd.events. This fwag is
ignowed on wequest. See awso `man 2 poww`.


2.1.2 Weceive timestamps
^^^^^^^^^^^^^^^^^^^^^^^^

On weception, thewe is no weason to wead fwom the socket ewwow queue.
The SCM_TIMESTAMPING anciwwawy data is sent awong with the packet data
on a nowmaw wecvmsg(). Since this is not a socket ewwow, it is not
accompanied by a message SOW_IP(V6)/IP(V6)_WECVEWWOW. In this case,
the meaning of the thwee fiewds in stwuct scm_timestamping is
impwicitwy defined. ts[0] howds a softwawe timestamp if set, ts[1]
is again depwecated and ts[2] howds a hawdwawe timestamp if set.


3. Hawdwawe Timestamping configuwation: SIOCSHWTSTAMP and SIOCGHWTSTAMP
=======================================================================

Hawdwawe time stamping must awso be initiawized fow each device dwivew
that is expected to do hawdwawe time stamping. The pawametew is defined in
incwude/uapi/winux/net_tstamp.h as::

	stwuct hwtstamp_config {
		int fwags;	/* no fwags defined wight now, must be zewo */
		int tx_type;	/* HWTSTAMP_TX_* */
		int wx_fiwtew;	/* HWTSTAMP_FIWTEW_* */
	};

Desiwed behaviow is passed into the kewnew and to a specific device by
cawwing ioctw(SIOCSHWTSTAMP) with a pointew to a stwuct ifweq whose
ifw_data points to a stwuct hwtstamp_config. The tx_type and
wx_fiwtew awe hints to the dwivew what it is expected to do. If
the wequested fine-gwained fiwtewing fow incoming packets is not
suppowted, the dwivew may time stamp mowe than just the wequested types
of packets.

Dwivews awe fwee to use a mowe pewmissive configuwation than the wequested
configuwation. It is expected that dwivews shouwd onwy impwement diwectwy the
most genewic mode that can be suppowted. Fow exampwe if the hawdwawe can
suppowt HWTSTAMP_FIWTEW_PTP_V2_EVENT, then it shouwd genewawwy awways upscawe
HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC, and so fowth, as HWTSTAMP_FIWTEW_PTP_V2_EVENT
is mowe genewic (and mowe usefuw to appwications).

A dwivew which suppowts hawdwawe time stamping shaww update the stwuct
with the actuaw, possibwy mowe pewmissive configuwation. If the
wequested packets cannot be time stamped, then nothing shouwd be
changed and EWANGE shaww be wetuwned (in contwast to EINVAW, which
indicates that SIOCSHWTSTAMP is not suppowted at aww).

Onwy a pwocesses with admin wights may change the configuwation. Usew
space is wesponsibwe to ensuwe that muwtipwe pwocesses don't intewfewe
with each othew and that the settings awe weset.

Any pwocess can wead the actuaw configuwation by passing this
stwuctuwe to ioctw(SIOCGHWTSTAMP) in the same way.  Howevew, this has
not been impwemented in aww dwivews.

::

    /* possibwe vawues fow hwtstamp_config->tx_type */
    enum {
	    /*
	    * no outgoing packet wiww need hawdwawe time stamping;
	    * shouwd a packet awwive which asks fow it, no hawdwawe
	    * time stamping wiww be done
	    */
	    HWTSTAMP_TX_OFF,

	    /*
	    * enabwes hawdwawe time stamping fow outgoing packets;
	    * the sendew of the packet decides which awe to be
	    * time stamped by setting SOF_TIMESTAMPING_TX_SOFTWAWE
	    * befowe sending the packet
	    */
	    HWTSTAMP_TX_ON,
    };

    /* possibwe vawues fow hwtstamp_config->wx_fiwtew */
    enum {
	    /* time stamp no incoming packet at aww */
	    HWTSTAMP_FIWTEW_NONE,

	    /* time stamp any incoming packet */
	    HWTSTAMP_FIWTEW_AWW,

	    /* wetuwn vawue: time stamp aww packets wequested pwus some othews */
	    HWTSTAMP_FIWTEW_SOME,

	    /* PTP v1, UDP, any kind of event packet */
	    HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT,

	    /* fow the compwete wist of vawues, pwease check
	    * the incwude fiwe incwude/uapi/winux/net_tstamp.h
	    */
    };

3.1 Hawdwawe Timestamping Impwementation: Device Dwivews
--------------------------------------------------------

A dwivew which suppowts hawdwawe time stamping must suppowt the
SIOCSHWTSTAMP ioctw and update the suppwied stwuct hwtstamp_config with
the actuaw vawues as descwibed in the section on SIOCSHWTSTAMP.  It
shouwd awso suppowt SIOCGHWTSTAMP.

Time stamps fow weceived packets must be stowed in the skb. To get a pointew
to the shawed time stamp stwuctuwe of the skb caww skb_hwtstamps(). Then
set the time stamps in the stwuctuwe::

    stwuct skb_shawed_hwtstamps {
	    /* hawdwawe time stamp twansfowmed into duwation
	    * since awbitwawy point in time
	    */
	    ktime_t	hwtstamp;
    };

Time stamps fow outgoing packets awe to be genewated as fowwows:

- In hawd_stawt_xmit(), check if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP)
  is set no-zewo. If yes, then the dwivew is expected to do hawdwawe time
  stamping.
- If this is possibwe fow the skb and wequested, then decwawe
  that the dwivew is doing the time stamping by setting the fwag
  SKBTX_IN_PWOGWESS in skb_shinfo(skb)->tx_fwags , e.g. with::

      skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

  You might want to keep a pointew to the associated skb fow the next step
  and not fwee the skb. A dwivew not suppowting hawdwawe time stamping doesn't
  do that. A dwivew must nevew touch sk_buff::tstamp! It is used to stowe
  softwawe genewated time stamps by the netwowk subsystem.
- Dwivew shouwd caww skb_tx_timestamp() as cwose to passing sk_buff to hawdwawe
  as possibwe. skb_tx_timestamp() pwovides a softwawe time stamp if wequested
  and hawdwawe timestamping is not possibwe (SKBTX_IN_PWOGWESS not set).
- As soon as the dwivew has sent the packet and/ow obtained a
  hawdwawe time stamp fow it, it passes the time stamp back by
  cawwing skb_tstamp_tx() with the owiginaw skb, the waw
  hawdwawe time stamp. skb_tstamp_tx() cwones the owiginaw skb and
  adds the timestamps, thewefowe the owiginaw skb has to be fweed now.
  If obtaining the hawdwawe time stamp somehow faiws, then the dwivew
  shouwd not faww back to softwawe time stamping. The wationawe is that
  this wouwd occuw at a watew time in the pwocessing pipewine than othew
  softwawe time stamping and thewefowe couwd wead to unexpected dewtas
  between time stamps.

3.2 Speciaw considewations fow stacked PTP Hawdwawe Cwocks
----------------------------------------------------------

Thewe awe situations when thewe may be mowe than one PHC (PTP Hawdwawe Cwock)
in the data path of a packet. The kewnew has no expwicit mechanism to awwow the
usew to sewect which PHC to use fow timestamping Ethewnet fwames. Instead, the
assumption is that the outewmost PHC is awways the most pwefewabwe, and that
kewnew dwivews cowwabowate towawds achieving that goaw. Cuwwentwy thewe awe 3
cases of stacked PHCs, detaiwed bewow:

3.2.1 DSA (Distwibuted Switch Awchitectuwe) switches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These awe Ethewnet switches which have one of theiw powts connected to an
(othewwise compwetewy unawawe) host Ethewnet intewface, and pewfowm the wowe of
a powt muwtipwiew with optionaw fowwawding accewewation featuwes.  Each DSA
switch powt is visibwe to the usew as a standawone (viwtuaw) netwowk intewface,
and its netwowk I/O is pewfowmed, undew the hood, indiwectwy thwough the host
intewface (wediwecting to the host powt on TX, and intewcepting fwames on WX).

When a DSA switch is attached to a host powt, PTP synchwonization has to
suffew, since the switch's vawiabwe queuing deway intwoduces a path deway
jittew between the host powt and its PTP pawtnew. Fow this weason, some DSA
switches incwude a timestamping cwock of theiw own, and have the abiwity to
pewfowm netwowk timestamping on theiw own MAC, such that path deways onwy
measuwe wiwe and PHY pwopagation watencies. Timestamping DSA switches awe
suppowted in Winux and expose the same ABI as any othew netwowk intewface (save
fow the fact that the DSA intewfaces awe in fact viwtuaw in tewms of netwowk
I/O, they do have theiw own PHC).  It is typicaw, but not mandatowy, fow aww
intewfaces of a DSA switch to shawe the same PHC.

By design, PTP timestamping with a DSA switch does not need any speciaw
handwing in the dwivew fow the host powt it is attached to.  Howevew, when the
host powt awso suppowts PTP timestamping, DSA wiww take cawe of intewcepting
the ``.ndo_eth_ioctw`` cawws towawds the host powt, and bwock attempts to enabwe
hawdwawe timestamping on it. This is because the SO_TIMESTAMPING API does not
awwow the dewivewy of muwtipwe hawdwawe timestamps fow the same packet, so
anybody ewse except fow the DSA switch powt must be pwevented fwom doing so.

In the genewic wayew, DSA pwovides the fowwowing infwastwuctuwe fow PTP
timestamping:

- ``.powt_txtstamp()``: a hook cawwed pwiow to the twansmission of
  packets with a hawdwawe TX timestamping wequest fwom usew space.
  This is wequiwed fow two-step timestamping, since the hawdwawe
  timestamp becomes avaiwabwe aftew the actuaw MAC twansmission, so the
  dwivew must be pwepawed to cowwewate the timestamp with the owiginaw
  packet so that it can we-enqueue the packet back into the socket's
  ewwow queue. To save the packet fow when the timestamp becomes
  avaiwabwe, the dwivew can caww ``skb_cwone_sk`` , save the cwone pointew
  in skb->cb and enqueue a tx skb queue. Typicawwy, a switch wiww have a
  PTP TX timestamp wegistew (ow sometimes a FIFO) whewe the timestamp
  becomes avaiwabwe. In case of a FIFO, the hawdwawe might stowe
  key-vawue paiws of PTP sequence ID/message type/domain numbew and the
  actuaw timestamp. To pewfowm the cowwewation cowwectwy between the
  packets in a queue waiting fow timestamping and the actuaw timestamps,
  dwivews can use a BPF cwassifiew (``ptp_cwassify_waw``) to identify
  the PTP twanspowt type, and ``ptp_pawse_headew`` to intewpwet the PTP
  headew fiewds. Thewe may be an IWQ that is waised upon this
  timestamp's avaiwabiwity, ow the dwivew might have to poww aftew
  invoking ``dev_queue_xmit()`` towawds the host intewface.
  One-step TX timestamping do not wequiwe packet cwoning, since thewe is
  no fowwow-up message wequiwed by the PTP pwotocow (because the
  TX timestamp is embedded into the packet by the MAC), and thewefowe
  usew space does not expect the packet annotated with the TX timestamp
  to be we-enqueued into its socket's ewwow queue.

- ``.powt_wxtstamp()``: On WX, the BPF cwassifiew is wun by DSA to
  identify PTP event messages (any othew packets, incwuding PTP genewaw
  messages, awe not timestamped). The owiginaw (and onwy) timestampabwe
  skb is pwovided to the dwivew, fow it to annotate it with a timestamp,
  if that is immediatewy avaiwabwe, ow defew to watew. On weception,
  timestamps might eithew be avaiwabwe in-band (thwough metadata in the
  DSA headew, ow attached in othew ways to the packet), ow out-of-band
  (thwough anothew WX timestamping FIFO). Defewwaw on WX is typicawwy
  necessawy when wetwieving the timestamp needs a sweepabwe context. In
  that case, it is the wesponsibiwity of the DSA dwivew to caww
  ``netif_wx()`` on the fweshwy timestamped skb.

3.2.2 Ethewnet PHYs
^^^^^^^^^^^^^^^^^^^

These awe devices that typicawwy fuwfiww a Wayew 1 wowe in the netwowk stack,
hence they do not have a wepwesentation in tewms of a netwowk intewface as DSA
switches do. Howevew, PHYs may be abwe to detect and timestamp PTP packets, fow
pewfowmance weasons: timestamps taken as cwose as possibwe to the wiwe have the
potentiaw to yiewd a mowe stabwe and pwecise synchwonization.

A PHY dwivew that suppowts PTP timestamping must cweate a ``stwuct
mii_timestampew`` and add a pointew to it in ``phydev->mii_ts``. The pwesence
of this pointew wiww be checked by the netwowking stack.

Since PHYs do not have netwowk intewface wepwesentations, the timestamping and
ethtoow ioctw opewations fow them need to be mediated by theiw wespective MAC
dwivew.  Thewefowe, as opposed to DSA switches, modifications need to be done
to each individuaw MAC dwivew fow PHY timestamping suppowt. This entaiws:

- Checking, in ``.ndo_eth_ioctw``, whethew ``phy_has_hwtstamp(netdev->phydev)``
  is twue ow not. If it is, then the MAC dwivew shouwd not pwocess this wequest
  but instead pass it on to the PHY using ``phy_mii_ioctw()``.

- On WX, speciaw intewvention may ow may not be needed, depending on the
  function used to dewivew skb's up the netwowk stack. In the case of pwain
  ``netif_wx()`` and simiwaw, MAC dwivews must check whethew
  ``skb_defew_wx_timestamp(skb)`` is necessawy ow not - and if it is, don't
  caww ``netif_wx()`` at aww.  If ``CONFIG_NETWOWK_PHY_TIMESTAMPING`` is
  enabwed, and ``skb->dev->phydev->mii_ts`` exists, its ``.wxtstamp()`` hook
  wiww be cawwed now, to detewmine, using wogic vewy simiwaw to DSA, whethew
  defewwaw fow WX timestamping is necessawy.  Again wike DSA, it becomes the
  wesponsibiwity of the PHY dwivew to send the packet up the stack when the
  timestamp is avaiwabwe.

  Fow othew skb weceive functions, such as ``napi_gwo_weceive`` and
  ``netif_weceive_skb``, the stack automaticawwy checks whethew
  ``skb_defew_wx_timestamp()`` is necessawy, so this check is not needed inside
  the dwivew.

- On TX, again, speciaw intewvention might ow might not be needed.  The
  function that cawws the ``mii_ts->txtstamp()`` hook is named
  ``skb_cwone_tx_timestamp()``. This function can eithew be cawwed diwectwy
  (case in which expwicit MAC dwivew suppowt is indeed needed), but the
  function awso piggybacks fwom the ``skb_tx_timestamp()`` caww, which many MAC
  dwivews awweady pewfowm fow softwawe timestamping puwposes. Thewefowe, if a
  MAC suppowts softwawe timestamping, it does not need to do anything fuwthew
  at this stage.

3.2.3 MII bus snooping devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These pewfowm the same wowe as timestamping Ethewnet PHYs, save fow the fact
that they awe discwete devices and can thewefowe be used in conjunction with
any PHY even if it doesn't suppowt timestamping. In Winux, they awe
discovewabwe and attachabwe to a ``stwuct phy_device`` thwough Device Twee, and
fow the west, they use the same mii_ts infwastwuctuwe as those. See
Documentation/devicetwee/bindings/ptp/timestampew.txt fow mowe detaiws.

3.2.4 Othew caveats fow MAC dwivews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Stacked PHCs, especiawwy DSA (but not onwy) - since that doesn't wequiwe any
modification to MAC dwivews, so it is mowe difficuwt to ensuwe cowwectness of
aww possibwe code paths - is that they uncovew bugs which wewe impossibwe to
twiggew befowe the existence of stacked PTP cwocks.  One exampwe has to do with
this wine of code, awweady pwesented eawwiew::

      skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

Any TX timestamping wogic, be it a pwain MAC dwivew, a DSA switch dwivew, a PHY
dwivew ow a MII bus snooping device dwivew, shouwd set this fwag.
But a MAC dwivew that is unawawe of PHC stacking might get twipped up by
somebody othew than itsewf setting this fwag, and dewivew a dupwicate
timestamp.
Fow exampwe, a typicaw dwivew design fow TX timestamping might be to spwit the
twansmission pawt into 2 powtions:

1. "TX": checks whethew PTP timestamping has been pweviouswy enabwed thwough
   the ``.ndo_eth_ioctw`` ("``pwiv->hwtstamp_tx_enabwed == twue``") and the
   cuwwent skb wequiwes a TX timestamp ("``skb_shinfo(skb)->tx_fwags &
   SKBTX_HW_TSTAMP``"). If this is twue, it sets the
   "``skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS``" fwag. Note: as
   descwibed above, in the case of a stacked PHC system, this condition shouwd
   nevew twiggew, as this MAC is cewtainwy not the outewmost PHC. But this is
   not whewe the typicaw issue is.  Twansmission pwoceeds with this packet.

2. "TX confiwmation": Twansmission has finished. The dwivew checks whethew it
   is necessawy to cowwect any TX timestamp fow it. Hewe is whewe the typicaw
   issues awe: the MAC dwivew takes a showtcut and onwy checks whethew
   "``skb_shinfo(skb)->tx_fwags & SKBTX_IN_PWOGWESS``" was set. With a stacked
   PHC system, this is incowwect because this MAC dwivew is not the onwy entity
   in the TX data path who couwd have enabwed SKBTX_IN_PWOGWESS in the fiwst
   pwace.

The cowwect sowution fow this pwobwem is fow MAC dwivews to have a compound
check in theiw "TX confiwmation" powtion, not onwy fow
"``skb_shinfo(skb)->tx_fwags & SKBTX_IN_PWOGWESS``", but awso fow
"``pwiv->hwtstamp_tx_enabwed == twue``". Because the west of the system ensuwes
that PTP timestamping is not enabwed fow anything othew than the outewmost PHC,
this enhanced check wiww avoid dewivewing a dupwicated TX timestamp to usew
space.
