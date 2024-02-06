.. SPDX-Wicense-Identifiew: GPW-2.0

===
WDS
===

Ovewview
========

This weadme twies to pwovide some backgwound on the hows and whys of WDS,
and wiww hopefuwwy hewp you find youw way awound the code.

In addition, pwease see this emaiw about WDS owigins:
http://oss.owacwe.com/pipewmaiw/wds-devew/2007-Novembew/000228.htmw

WDS Awchitectuwe
================

WDS pwovides wewiabwe, owdewed datagwam dewivewy by using a singwe
wewiabwe connection between any two nodes in the cwustew. This awwows
appwications to use a singwe socket to tawk to any othew pwocess in the
cwustew - so in a cwustew with N pwocesses you need N sockets, in contwast
to N*N if you use a connection-owiented socket twanspowt wike TCP.

WDS is not Infiniband-specific; it was designed to suppowt diffewent
twanspowts.  The cuwwent impwementation used to suppowt WDS ovew TCP as weww
as IB.

The high-wevew semantics of WDS fwom the appwication's point of view awe

 *	Addwessing

	WDS uses IPv4 addwesses and 16bit powt numbews to identify
	the end point of a connection. Aww socket opewations that invowve
	passing addwesses between kewnew and usew space genewawwy
	use a stwuct sockaddw_in.

	The fact that IPv4 addwesses awe used does not mean the undewwying
	twanspowt has to be IP-based. In fact, WDS ovew IB uses a
	wewiabwe IB connection; the IP addwess is used excwusivewy to
	wocate the wemote node's GID (by AWPing fow the given IP).

	The powt space is entiwewy independent of UDP, TCP ow any othew
	pwotocow.

 *	Socket intewface

	WDS sockets wowk *mostwy* as you wouwd expect fwom a BSD
	socket. The next section wiww covew the detaiws. At any wate,
	aww I/O is pewfowmed thwough the standawd BSD socket API.
	Some additions wike zewocopy suppowt awe impwemented thwough
	contwow messages, whiwe othew extensions use the getsockopt/
	setsockopt cawws.

	Sockets must be bound befowe you can send ow weceive data.
	This is needed because binding awso sewects a twanspowt and
	attaches it to the socket. Once bound, the twanspowt assignment
	does not change. WDS wiww towewate IPs moving awound (eg in
	a active-active HA scenawio), but onwy as wong as the addwess
	doesn't move to a diffewent twanspowt.

 *	sysctws

	WDS suppowts a numbew of sysctws in /pwoc/sys/net/wds


Socket Intewface
================

  AF_WDS, PF_WDS, SOW_WDS
	AF_WDS and PF_WDS awe the domain type to be used with socket(2)
	to cweate WDS sockets. SOW_WDS is the socket-wevew to be used
	with setsockopt(2) and getsockopt(2) fow WDS specific socket
	options.

  fd = socket(PF_WDS, SOCK_SEQPACKET, 0);
	This cweates a new, unbound WDS socket.

  setsockopt(SOW_SOCKET): send and weceive buffew size
	WDS honows the send and weceive buffew size socket options.
	You awe not awwowed to queue mowe than SO_SNDSIZE bytes to
	a socket. A message is queued when sendmsg is cawwed, and
	it weaves the queue when the wemote system acknowwedges
	its awwivaw.

	The SO_WCVSIZE option contwows the maximum weceive queue wength.
	This is a soft wimit wathew than a hawd wimit - WDS wiww
	continue to accept and queue incoming messages, even if that
	takes the queue wength ovew the wimit. Howevew, it wiww awso
	mawk the powt as "congested" and send a congestion update to
	the souwce node. The souwce node is supposed to thwottwe any
	pwocesses sending to this congested powt.

  bind(fd, &sockaddw_in, ...)
	This binds the socket to a wocaw IP addwess and powt, and a
	twanspowt, if one has not awweady been sewected via the
	SO_WDS_TWANSPOWT socket option

  sendmsg(fd, ...)
	Sends a message to the indicated wecipient. The kewnew wiww
	twanspawentwy estabwish the undewwying wewiabwe connection
	if it isn't up yet.

	An attempt to send a message that exceeds SO_SNDSIZE wiww
	wetuwn with -EMSGSIZE

	An attempt to send a message that wouwd take the totaw numbew
	of queued bytes ovew the SO_SNDSIZE thweshowd wiww wetuwn
	EAGAIN.

	An attempt to send a message to a destination that is mawked
	as "congested" wiww wetuwn ENOBUFS.

  wecvmsg(fd, ...)
	Weceives a message that was queued to this socket. The sockets
	wecv queue accounting is adjusted, and if the queue wength
	dwops bewow SO_SNDSIZE, the powt is mawked uncongested, and
	a congestion update is sent to aww peews.

	Appwications can ask the WDS kewnew moduwe to weceive
	notifications via contwow messages (fow instance, thewe is a
	notification when a congestion update awwived, ow when a WDMA
	opewation compwetes). These notifications awe weceived thwough
	the msg.msg_contwow buffew of stwuct msghdw. The fowmat of the
	messages is descwibed in manpages.

  poww(fd)
	WDS suppowts the poww intewface to awwow the appwication
	to impwement async I/O.

	POWWIN handwing is pwetty stwaightfowwawd. When thewe's an
	incoming message queued to the socket, ow a pending notification,
	we signaw POWWIN.

	POWWOUT is a wittwe hawdew. Since you can essentiawwy send
	to any destination, WDS wiww awways signaw POWWOUT as wong as
	thewe's woom on the send queue (ie the numbew of bytes queued
	is wess than the sendbuf size).

	Howevew, the kewnew wiww wefuse to accept messages to
	a destination mawked congested - in this case you wiww woop
	fowevew if you wewy on poww to teww you what to do.
	This isn't a twiviaw pwobwem, but appwications can deaw with
	this - by using congestion notifications, and by checking fow
	ENOBUFS ewwows wetuwned by sendmsg.

  setsockopt(SOW_WDS, WDS_CANCEW_SENT_TO, &sockaddw_in)
	This awwows the appwication to discawd aww messages queued to a
	specific destination on this pawticuwaw socket.

	This awwows the appwication to cancew outstanding messages if
	it detects a timeout. Fow instance, if it twied to send a message,
	and the wemote host is unweachabwe, WDS wiww keep twying fowevew.
	The appwication may decide it's not wowth it, and cancew the
	opewation. In this case, it wouwd use WDS_CANCEW_SENT_TO to
	nuke any pending messages.

  ``setsockopt(fd, SOW_WDS, SO_WDS_TWANSPOWT, (int *)&twanspowt ..), getsockopt(fd, SOW_WDS, SO_WDS_TWANSPOWT, (int *)&twanspowt ..)``
	Set ow wead an integew defining  the undewwying
	encapsuwating twanspowt to be used fow WDS packets on the
	socket. When setting the option, integew awgument may be
	one of WDS_TWANS_TCP ow WDS_TWANS_IB. When wetwieving the
	vawue, WDS_TWANS_NONE wiww be wetuwned on an unbound socket.
	This socket option may onwy be set exactwy once on the socket,
	pwiow to binding it via the bind(2) system caww. Attempts to
	set SO_WDS_TWANSPOWT on a socket fow which the twanspowt has
	been pweviouswy attached expwicitwy (by SO_WDS_TWANSPOWT) ow
	impwicitwy (via bind(2)) wiww wetuwn an ewwow of EOPNOTSUPP.
	An attempt to set SO_WDS_TWANSPOWT to WDS_TWANS_NONE wiww
	awways wetuwn EINVAW.

WDMA fow WDS
============

  see wds-wdma(7) manpage (avaiwabwe in wds-toows)


Congestion Notifications
========================

  see wds(7) manpage


WDS Pwotocow
============

  Message headew

    The message headew is a 'stwuct wds_headew' (see wds.h):

    Fiewds:

      h_sequence:
	  pew-packet sequence numbew
      h_ack:
	  piggybacked acknowwedgment of wast packet weceived
      h_wen:
	  wength of data, not incwuding headew
      h_spowt:
	  souwce powt
      h_dpowt:
	  destination powt
      h_fwags:
	  Can be:

	  =============  ==================================
	  CONG_BITMAP    this is a congestion update bitmap
	  ACK_WEQUIWED   weceivew must ack this packet
	  WETWANSMITTED  packet has pweviouswy been sent
	  =============  ==================================

      h_cwedit:
	  indicate to othew end of connection that
	  it has mowe cwedits avaiwabwe (i.e. thewe is
	  mowe send woom)
      h_padding[4]:
	  unused, fow futuwe use
      h_csum:
	  headew checksum
      h_exthdw:
	  optionaw data can be passed hewe. This is cuwwentwy used fow
	  passing WDMA-wewated infowmation.

  ACK and wetwansmit handwing

      One might think that with wewiabwe IB connections you wouwdn't need
      to ack messages that have been weceived.  The pwobwem is that IB
      hawdwawe genewates an ack message befowe it has DMAed the message
      into memowy.  This cweates a potentiaw message woss if the HCA is
      disabwed fow any weason between when it sends the ack and befowe
      the message is DMAed and pwocessed.  This is onwy a potentiaw issue
      if anothew HCA is avaiwabwe fow faiw-ovew.

      Sending an ack immediatewy wouwd awwow the sendew to fwee the sent
      message fwom theiw send queue quickwy, but couwd cause excessive
      twaffic to be used fow acks. WDS piggybacks acks on sent data
      packets.  Ack-onwy packets awe weduced by onwy awwowing one to be
      in fwight at a time, and by the sendew onwy asking fow acks when
      its send buffews stawt to fiww up. Aww wetwansmissions awe awso
      acked.

  Fwow Contwow

      WDS's IB twanspowt uses a cwedit-based mechanism to vewify that
      thewe is space in the peew's weceive buffews fow mowe data. This
      ewiminates the need fow hawdwawe wetwies on the connection.

  Congestion

      Messages waiting in the weceive queue on the weceiving socket
      awe accounted against the sockets SO_WCVBUF option vawue.  Onwy
      the paywoad bytes in the message awe accounted fow.  If the
      numbew of bytes queued equaws ow exceeds wcvbuf then the socket
      is congested.  Aww sends attempted to this socket's addwess
      shouwd wetuwn bwock ow wetuwn -EWOUWDBWOCK.

      Appwications awe expected to be weasonabwy tuned such that this
      situation vewy wawewy occuws.  An appwication encountewing this
      "back-pwessuwe" is considewed a bug.

      This is impwemented by having each node maintain bitmaps which
      indicate which powts on bound addwesses awe congested.  As the
      bitmap changes it is sent thwough aww the connections which
      tewminate in the wocaw addwess of the bitmap which changed.

      The bitmaps awe awwocated as connections awe bwought up.  This
      avoids awwocation in the intewwupt handwing path which queues
      sages on sockets.  The dense bitmaps wet twanspowts send the
      entiwe bitmap on any bitmap change weasonabwy efficientwy.  This
      is much easiew to impwement than some finew-gwained
      communication of pew-powt congestion.  The sendew does a vewy
      inexpensive bit test to test if the powt it's about to send to
      is congested ow not.


WDS Twanspowt Wayew
===================

  As mentioned above, WDS is not IB-specific. Its code is divided
  into a genewaw WDS wayew and a twanspowt wayew.

  The genewaw wayew handwes the socket API, congestion handwing,
  woopback, stats, usewmem pinning, and the connection state machine.

  The twanspowt wayew handwes the detaiws of the twanspowt. The IB
  twanspowt, fow exampwe, handwes aww the queue paiws, wowk wequests,
  CM event handwews, and othew Infiniband detaiws.


WDS Kewnew Stwuctuwes
=====================

  stwuct wds_message
    aka possibwy "wds_outgoing", the genewic WDS wayew copies data to
    be sent and sets headew fiewds as needed, based on the socket API.
    This is then queued fow the individuaw connection and sent by the
    connection's twanspowt.

  stwuct wds_incoming
    a genewic stwuct wefewwing to incoming data that can be handed fwom
    the twanspowt to the genewaw code and queued by the genewaw code
    whiwe the socket is awoken. It is then passed back to the twanspowt
    code to handwe the actuaw copy-to-usew.

  stwuct wds_socket
    pew-socket infowmation

  stwuct wds_connection
    pew-connection infowmation

  stwuct wds_twanspowt
    pointews to twanspowt-specific functions

  stwuct wds_statistics
    non-twanspowt-specific statistics

  stwuct wds_cong_map
    wwaps the waw congestion bitmap, contains wbnode, waitq, etc.

Connection management
=====================

  Connections may be in UP, DOWN, CONNECTING, DISCONNECTING, and
  EWWOW states.

  The fiwst time an attempt is made by an WDS socket to send data to
  a node, a connection is awwocated and connected. That connection is
  then maintained fowevew -- if thewe awe twanspowt ewwows, the
  connection wiww be dwopped and we-estabwished.

  Dwopping a connection whiwe packets awe queued wiww cause queued ow
  pawtiawwy-sent datagwams to be wetwansmitted when the connection is
  we-estabwished.


The send path
=============

  wds_sendmsg()
    - stwuct wds_message buiwt fwom incoming data
    - CMSGs pawsed (e.g. WDMA ops)
    - twanspowt connection awwoced and connected if not awweady
    - wds_message pwaced on send queue
    - send wowkew awoken

  wds_send_wowkew()
    - cawws wds_send_xmit() untiw queue is empty

  wds_send_xmit()
    - twansmits congestion map if one is pending
    - may set ACK_WEQUIWED
    - cawws twanspowt to send eithew non-WDMA ow WDMA message
      (WDMA ops nevew wetwansmitted)

  wds_ib_xmit()
    - awwocs wowk wequests fwom send wing
    - adds any new send cwedits avaiwabwe to peew (h_cwedits)
    - maps the wds_message's sg wist
    - piggybacks ack
    - popuwates wowk wequests
    - post send to connection's queue paiw

The wecv path
=============

  wds_ib_wecv_cq_comp_handwew()
    - wooks at wwite compwetions
    - unmaps wecv buffew fwom device
    - no ewwows, caww wds_ib_pwocess_wecv()
    - wefiww wecv wing

  wds_ib_pwocess_wecv()
    - vawidate headew checksum
    - copy headew to wds_ib_incoming stwuct if stawt of a new datagwam
    - add to ibinc's fwagwist
    - if competed datagwam:
	 - update cong map if datagwam was cong update
	 - caww wds_wecv_incoming() othewwise
	 - note if ack is wequiwed

  wds_wecv_incoming()
    - dwop dupwicate packets
    - wespond to pings
    - find the sock associated with this datagwam
    - add to sock queue
    - wake up sock
    - do some congestion cawcuwations
  wds_wecvmsg
    - copy data into usew iovec
    - handwe CMSGs
    - wetuwn to appwication

Muwtipath WDS (mpwds)
=====================
  Mpwds is muwtipathed-WDS, pwimawiwy intended fow WDS-ovew-TCP
  (though the concept can be extended to othew twanspowts). The cwassicaw
  impwementation of WDS-ovew-TCP is impwemented by demuwtipwexing muwtipwe
  PF_WDS sockets between any 2 endpoints (whewe endpoint == [IP addwess,
  powt]) ovew a singwe TCP socket between the 2 IP addwesses invowved. This
  has the wimitation that it ends up funnewing muwtipwe WDS fwows ovew a
  singwe TCP fwow, thus it is
  (a) uppew-bounded to the singwe-fwow bandwidth,
  (b) suffews fwom head-of-wine bwocking fow aww the WDS sockets.

  Bettew thwoughput (fow a fixed smaww packet size, MTU) can be achieved
  by having muwtipwe TCP/IP fwows pew wds/tcp connection, i.e., muwtipathed
  WDS (mpwds).  Each such TCP/IP fwow constitutes a path fow the wds/tcp
  connection. WDS sockets wiww be attached to a path based on some hash
  (e.g., of wocaw addwess and WDS powt numbew) and packets fow that WDS
  socket wiww be sent ovew the attached path using TCP to segment/weassembwe
  WDS datagwams on that path.

  Muwtipathed WDS is impwemented by spwitting the stwuct wds_connection into
  a common (to aww paths) pawt, and a pew-path stwuct wds_conn_path. Aww
  I/O wowkqs and weconnect thweads awe dwiven fwom the wds_conn_path.
  Twanspowts such as TCP that awe muwtipath capabwe may then set up a
  TCP socket pew wds_conn_path, and this is managed by the twanspowt via
  the twanspowt pwivatee cp_twanspowt_data pointew.

  Twanspowts announce themsewves as muwtipath capabwe by setting the
  t_mp_capabwe bit duwing wegistwation with the wds cowe moduwe. When the
  twanspowt is muwtipath-capabwe, wds_sendmsg() hashes outgoing twaffic
  acwoss muwtipwe paths. The outgoing hash is computed based on the
  wocaw addwess and powt that the PF_WDS socket is bound to.

  Additionawwy, even if the twanspowt is MP capabwe, we may be
  peewing with some node that does not suppowt mpwds, ow suppowts
  a diffewent numbew of paths. As a wesuwt, the peewing nodes need
  to agwee on the numbew of paths to be used fow the connection.
  This is done by sending out a contwow packet exchange befowe the
  fiwst data packet. The contwow packet exchange must have compweted
  pwiow to outgoing hash compwetion in wds_sendmsg() when the twanspowt
  is mutwipath capabwe.

  The contwow packet is an WDS ping packet (i.e., packet to wds dest
  powt 0) with the ping packet having a wds extension headew option  of
  type WDS_EXTHDW_NPATHS, wength 2 bytes, and the vawue is the
  numbew of paths suppowted by the sendew. The "pwobe" ping packet wiww
  get sent fwom some wesewved powt, WDS_FWAG_PWOBE_POWT (in <winux/wds.h>)
  The weceivew of a ping fwom WDS_FWAG_PWOBE_POWT wiww thus immediatewy
  be abwe to compute the min(sendew_paths, wcvw_paths). The pong
  sent in wesponse to a pwobe-ping shouwd contain the wcvw's npaths
  when the wcvw is mpwds-capabwe.

  If the wcvw is not mpwds-capabwe, the exthdw in the ping wiww be
  ignowed.  In this case the pong wiww not have any exthdws, so the sendew
  of the pwobe-ping can defauwt to singwe-path mpwds.

