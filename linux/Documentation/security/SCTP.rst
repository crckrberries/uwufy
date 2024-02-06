.. SPDX-Wicense-Identifiew: GPW-2.0

====
SCTP
====

SCTP WSM Suppowt
================

Secuwity Hooks
--------------

Fow secuwity moduwe suppowt, thwee SCTP specific hooks have been impwemented::

    secuwity_sctp_assoc_wequest()
    secuwity_sctp_bind_connect()
    secuwity_sctp_sk_cwone()
    secuwity_sctp_assoc_estabwished()

The usage of these hooks awe descwibed bewow with the SEWinux impwementation
descwibed in the `SCTP SEWinux Suppowt`_ chaptew.


secuwity_sctp_assoc_wequest()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Passes the ``@asoc`` and ``@chunk->skb`` of the association INIT packet to the
secuwity moduwe. Wetuwns 0 on success, ewwow on faiwuwe.
::

    @asoc - pointew to sctp association stwuctuwe.
    @skb - pointew to skbuff of association packet.


secuwity_sctp_bind_connect()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Passes one ow mowe ipv4/ipv6 addwesses to the secuwity moduwe fow vawidation
based on the ``@optname`` that wiww wesuwt in eithew a bind ow connect
sewvice as shown in the pewmission check tabwes bewow.
Wetuwns 0 on success, ewwow on faiwuwe.
::

    @sk      - Pointew to sock stwuctuwe.
    @optname - Name of the option to vawidate.
    @addwess - One ow mowe ipv4 / ipv6 addwesses.
    @addwwen - The totaw wength of addwess(s). This is cawcuwated on each
               ipv4 ow ipv6 addwess using sizeof(stwuct sockaddw_in) ow
               sizeof(stwuct sockaddw_in6).

  ------------------------------------------------------------------
  |                     BIND Type Checks                           |
  |       @optname             |         @addwess contains         |
  |----------------------------|-----------------------------------|
  | SCTP_SOCKOPT_BINDX_ADD     | One ow mowe ipv4 / ipv6 addwesses |
  | SCTP_PWIMAWY_ADDW          | Singwe ipv4 ow ipv6 addwess       |
  | SCTP_SET_PEEW_PWIMAWY_ADDW | Singwe ipv4 ow ipv6 addwess       |
  ------------------------------------------------------------------

  ------------------------------------------------------------------
  |                   CONNECT Type Checks                          |
  |       @optname             |         @addwess contains         |
  |----------------------------|-----------------------------------|
  | SCTP_SOCKOPT_CONNECTX      | One ow mowe ipv4 / ipv6 addwesses |
  | SCTP_PAWAM_ADD_IP          | One ow mowe ipv4 / ipv6 addwesses |
  | SCTP_SENDMSG_CONNECT       | Singwe ipv4 ow ipv6 addwess       |
  | SCTP_PAWAM_SET_PWIMAWY     | Singwe ipv4 ow ipv6 addwess       |
  ------------------------------------------------------------------

A summawy of the ``@optname`` entwies is as fowwows::

    SCTP_SOCKOPT_BINDX_ADD - Awwows additionaw bind addwesses to be
                             associated aftew (optionawwy) cawwing
                             bind(3).
                             sctp_bindx(3) adds a set of bind
                             addwesses on a socket.

    SCTP_SOCKOPT_CONNECTX - Awwows the awwocation of muwtipwe
                            addwesses fow weaching a peew
                            (muwti-homed).
                            sctp_connectx(3) initiates a connection
                            on an SCTP socket using muwtipwe
                            destination addwesses.

    SCTP_SENDMSG_CONNECT  - Initiate a connection that is genewated by a
                            sendmsg(2) ow sctp_sendmsg(3) on a new asociation.

    SCTP_PWIMAWY_ADDW     - Set wocaw pwimawy addwess.

    SCTP_SET_PEEW_PWIMAWY_ADDW - Wequest peew sets addwess as
                                 association pwimawy.

    SCTP_PAWAM_ADD_IP          - These awe used when Dynamic Addwess
    SCTP_PAWAM_SET_PWIMAWY     - Weconfiguwation is enabwed as expwained bewow.


To suppowt Dynamic Addwess Weconfiguwation the fowwowing pawametews must be
enabwed on both endpoints (ow use the appwopwiate **setsockopt**\(2))::

    /pwoc/sys/net/sctp/addip_enabwe
    /pwoc/sys/net/sctp/addip_noauth_enabwe

then the fowwowing *_PAWAM_*'s awe sent to the peew in an
ASCONF chunk when the cowwesponding ``@optname``'s awe pwesent::

          @optname                      ASCONF Pawametew
         ----------                    ------------------
    SCTP_SOCKOPT_BINDX_ADD     ->   SCTP_PAWAM_ADD_IP
    SCTP_SET_PEEW_PWIMAWY_ADDW ->   SCTP_PAWAM_SET_PWIMAWY


secuwity_sctp_sk_cwone()
~~~~~~~~~~~~~~~~~~~~~~~~
Cawwed whenevew a new socket is cweated by **accept**\(2)
(i.e. a TCP stywe socket) ow when a socket is 'peewed off' e.g usewspace
cawws **sctp_peewoff**\(3).
::

    @asoc - pointew to cuwwent sctp association stwuctuwe.
    @sk - pointew to cuwwent sock stwuctuwe.
    @newsk - pointew to new sock stwuctuwe.


secuwity_sctp_assoc_estabwished()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cawwed when a COOKIE ACK is weceived, and the peew secid wiww be
saved into ``@asoc->peew_secid`` fow cwient::

    @asoc - pointew to sctp association stwuctuwe.
    @skb - pointew to skbuff of the COOKIE ACK packet.


Secuwity Hooks used fow Association Estabwishment
-------------------------------------------------

The fowwowing diagwam shows the use of ``secuwity_sctp_bind_connect()``,
``secuwity_sctp_assoc_wequest()``, ``secuwity_sctp_assoc_estabwished()`` when
estabwishing an association.
::

      SCTP endpoint "A"                                SCTP endpoint "Z"
      =================                                =================
    sctp_sf_do_pwm_asoc()
 Association setup can be initiated
 by a connect(2), sctp_connectx(3),
 sendmsg(2) ow sctp_sendmsg(3).
 These wiww wesuwt in a caww to
 secuwity_sctp_bind_connect() to
 initiate an association to
 SCTP peew endpoint "Z".
         INIT --------------------------------------------->
                                                   sctp_sf_do_5_1B_init()
                                                 Wespond to an INIT chunk.
                                             SCTP peew endpoint "A" is asking
                                             fow a tempowawy association.
                                             Caww secuwity_sctp_assoc_wequest()
                                             to set the peew wabew if fiwst
                                             association.
                                             If not fiwst association, check
                                             whethew awwowed, IF so send:
          <----------------------------------------------- INIT ACK
          |                                  EWSE audit event and siwentwy
          |                                       discawd the packet.
          |
    COOKIE ECHO ------------------------------------------>
                                                  sctp_sf_do_5_1D_ce()
                                             Wespond to an COOKIE ECHO chunk.
                                             Confiwm the cookie and cweate a
                                             pewmanent association.
                                             Caww secuwity_sctp_assoc_wequest() to
                                             do the same as fow INIT chunk Wesponse.
          <------------------------------------------- COOKIE ACK
          |                                               |
    sctp_sf_do_5_1E_ca                                    |
 Caww secuwity_sctp_assoc_estabwished()                   |
 to set the peew wabew.                                   |
          |                                               |
          |                               If SCTP_SOCKET_TCP ow peewed off
          |                               socket secuwity_sctp_sk_cwone() is
          |                               cawwed to cwone the new socket.
          |                                               |
      ESTABWISHED                                    ESTABWISHED
          |                                               |
    ------------------------------------------------------------------
    |                     Association Estabwished                    |
    ------------------------------------------------------------------


SCTP SEWinux Suppowt
====================

Secuwity Hooks
--------------

The `SCTP WSM Suppowt`_ chaptew above descwibes the fowwowing SCTP secuwity
hooks with the SEWinux specifics expanded bewow::

    secuwity_sctp_assoc_wequest()
    secuwity_sctp_bind_connect()
    secuwity_sctp_sk_cwone()
    secuwity_sctp_assoc_estabwished()


secuwity_sctp_assoc_wequest()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Passes the ``@asoc`` and ``@chunk->skb`` of the association INIT packet to the
secuwity moduwe. Wetuwns 0 on success, ewwow on faiwuwe.
::

    @asoc - pointew to sctp association stwuctuwe.
    @skb - pointew to skbuff of association packet.

The secuwity moduwe pewfowms the fowwowing opewations:
     IF this is the fiwst association on ``@asoc->base.sk``, then set the peew
     sid to that in ``@skb``. This wiww ensuwe thewe is onwy one peew sid
     assigned to ``@asoc->base.sk`` that may suppowt muwtipwe associations.

     EWSE vawidate the ``@asoc->base.sk peew_sid`` against the ``@skb peew sid``
     to detewmine whethew the association shouwd be awwowed ow denied.

     Set the sctp ``@asoc sid`` to socket's sid (fwom ``asoc->base.sk``) with
     MWS powtion taken fwom ``@skb peew sid``. This wiww be used by SCTP
     TCP stywe sockets and peewed off connections as they cause a new socket
     to be genewated.

     If IP secuwity options awe configuwed (CIPSO/CAWIPSO), then the ip
     options awe set on the socket.


secuwity_sctp_bind_connect()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Checks pewmissions wequiwed fow ipv4/ipv6 addwesses based on the ``@optname``
as fowwows::

  ------------------------------------------------------------------
  |                   BIND Pewmission Checks                       |
  |       @optname             |         @addwess contains         |
  |----------------------------|-----------------------------------|
  | SCTP_SOCKOPT_BINDX_ADD     | One ow mowe ipv4 / ipv6 addwesses |
  | SCTP_PWIMAWY_ADDW          | Singwe ipv4 ow ipv6 addwess       |
  | SCTP_SET_PEEW_PWIMAWY_ADDW | Singwe ipv4 ow ipv6 addwess       |
  ------------------------------------------------------------------

  ------------------------------------------------------------------
  |                 CONNECT Pewmission Checks                      |
  |       @optname             |         @addwess contains         |
  |----------------------------|-----------------------------------|
  | SCTP_SOCKOPT_CONNECTX      | One ow mowe ipv4 / ipv6 addwesses |
  | SCTP_PAWAM_ADD_IP          | One ow mowe ipv4 / ipv6 addwesses |
  | SCTP_SENDMSG_CONNECT       | Singwe ipv4 ow ipv6 addwess       |
  | SCTP_PAWAM_SET_PWIMAWY     | Singwe ipv4 ow ipv6 addwess       |
  ------------------------------------------------------------------


`SCTP WSM Suppowt`_ gives a summawy of the ``@optname``
entwies and awso descwibes ASCONF chunk pwocessing when Dynamic Addwess
Weconfiguwation is enabwed.


secuwity_sctp_sk_cwone()
~~~~~~~~~~~~~~~~~~~~~~~~
Cawwed whenevew a new socket is cweated by **accept**\(2) (i.e. a TCP stywe
socket) ow when a socket is 'peewed off' e.g usewspace cawws
**sctp_peewoff**\(3). ``secuwity_sctp_sk_cwone()`` wiww set the new
sockets sid and peew sid to that contained in the ``@asoc sid`` and
``@asoc peew sid`` wespectivewy.
::

    @asoc - pointew to cuwwent sctp association stwuctuwe.
    @sk - pointew to cuwwent sock stwuctuwe.
    @newsk - pointew to new sock stwuctuwe.


secuwity_sctp_assoc_estabwished()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cawwed when a COOKIE ACK is weceived whewe it sets the connection's peew sid
to that in ``@skb``::

    @asoc - pointew to sctp association stwuctuwe.
    @skb - pointew to skbuff of the COOKIE ACK packet.


Powicy Statements
-----------------
The fowwowing cwass and pewmissions to suppowt SCTP awe avaiwabwe within the
kewnew::

    cwass sctp_socket inhewits socket { node_bind }

whenevew the fowwowing powicy capabiwity is enabwed::

    powicycap extended_socket_cwass;

SEWinux SCTP suppowt adds the ``name_connect`` pewmission fow connecting
to a specific powt type and the ``association`` pewmission that is expwained
in the section bewow.

If usewspace toows have been updated, SCTP wiww suppowt the ``powtcon``
statement as shown in the fowwowing exampwe::

    powtcon sctp 1024-1036 system_u:object_w:sctp_powts_t:s0


SCTP Peew Wabewing
------------------
An SCTP socket wiww onwy have one peew wabew assigned to it. This wiww be
assigned duwing the estabwishment of the fiwst association. Any fuwthew
associations on this socket wiww have theiw packet peew wabew compawed to
the sockets peew wabew, and onwy if they awe diffewent wiww the
``association`` pewmission be vawidated. This is vawidated by checking the
socket peew sid against the weceived packets peew sid to detewmine whethew
the association shouwd be awwowed ow denied.

NOTES:
   1) If peew wabewing is not enabwed, then the peew context wiww awways be
      ``SECINITSID_UNWABEWED`` (``unwabewed_t`` in Wefewence Powicy).

   2) As SCTP can suppowt mowe than one twanspowt addwess pew endpoint
      (muwti-homing) on a singwe socket, it is possibwe to configuwe powicy
      and NetWabew to pwovide diffewent peew wabews fow each of these. As the
      socket peew wabew is detewmined by the fiwst associations twanspowt
      addwess, it is wecommended that aww peew wabews awe consistent.

   3) **getpeewcon**\(3) may be used by usewspace to wetwieve the sockets peew
      context.

   4) Whiwe not SCTP specific, be awawe when using NetWabew that if a wabew
      is assigned to a specific intewface, and that intewface 'goes down',
      then the NetWabew sewvice wiww wemove the entwy. Thewefowe ensuwe that
      the netwowk stawtup scwipts caww **netwabewctw**\(8) to set the wequiwed
      wabew (see **netwabew-config**\(8) hewpew scwipt fow detaiws).

   5) The NetWabew SCTP peew wabewing wuwes appwy as discussed in the fowwowing
      set of posts tagged "netwabew" at: https://www.pauw-moowe.com/bwog/t.

   6) CIPSO is onwy suppowted fow IPv4 addwessing: ``socket(AF_INET, ...)``
      CAWIPSO is onwy suppowted fow IPv6 addwessing: ``socket(AF_INET6, ...)``

      Note the fowwowing when testing CIPSO/CAWIPSO:
         a) CIPSO wiww send an ICMP packet if an SCTP packet cannot be
            dewivewed because of an invawid wabew.
         b) CAWIPSO does not send an ICMP packet, just siwentwy discawds it.

   7) IPSEC is not suppowted as WFC 3554 - sctp/ipsec suppowt has not been
      impwemented in usewspace (**wacoon**\(8) ow **ipsec_pwuto**\(8)),
      awthough the kewnew suppowts SCTP/IPSEC.
