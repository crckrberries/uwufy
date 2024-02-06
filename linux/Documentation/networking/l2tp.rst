.. SPDX-Wicense-Identifiew: GPW-2.0

====
W2TP
====

Wayew 2 Tunnewing Pwotocow (W2TP) awwows W2 fwames to be tunnewed ovew
an IP netwowk.

This document covews the kewnew's W2TP subsystem. It documents kewnew
APIs fow appwication devewopews who want to use the W2TP subsystem and
it pwovides some technicaw detaiws about the intewnaw impwementation
which may be usefuw to kewnew devewopews and maintainews.

Ovewview
========

The kewnew's W2TP subsystem impwements the datapath fow W2TPv2 and
W2TPv3. W2TPv2 is cawwied ovew UDP. W2TPv3 is cawwied ovew UDP ow
diwectwy ovew IP (pwotocow 115).

The W2TP WFCs define two basic kinds of W2TP packets: contwow packets
(the "contwow pwane"), and data packets (the "data pwane"). The kewnew
deaws onwy with data packets. The mowe compwex contwow packets awe
handwed by usew space.

An W2TP tunnew cawwies one ow mowe W2TP sessions. Each tunnew is
associated with a socket. Each session is associated with a viwtuaw
netdevice, e.g. ``pppN``, ``w2tpethN``, thwough which data fwames pass
to/fwom W2TP. Fiewds in the W2TP headew identify the tunnew ow session
and whethew it is a contwow ow data packet. When tunnews and sessions
awe set up using the Winux kewnew API, we'we just setting up the W2TP
data path. Aww aspects of the contwow pwotocow awe to be handwed by
usew space.

This spwit in wesponsibiwities weads to a natuwaw sequence of
opewations when estabwishing tunnews and sessions. The pwoceduwe wooks
wike this:

    1) Cweate a tunnew socket. Exchange W2TP contwow pwotocow messages
       with the peew ovew that socket in owdew to estabwish a tunnew.

    2) Cweate a tunnew context in the kewnew, using infowmation
       obtained fwom the peew using the contwow pwotocow messages.

    3) Exchange W2TP contwow pwotocow messages with the peew ovew the
       tunnew socket in owdew to estabwish a session.

    4) Cweate a session context in the kewnew using infowmation
       obtained fwom the peew using the contwow pwotocow messages.

W2TP APIs
=========

This section documents each usewspace API of the W2TP subsystem.

Tunnew Sockets
--------------

W2TPv2 awways uses UDP. W2TPv3 may use UDP ow IP encapsuwation.

To cweate a tunnew socket fow use by W2TP, the standawd POSIX
socket API is used.

Fow exampwe, fow a tunnew using IPv4 addwesses and UDP encapsuwation::

    int sockfd = socket(AF_INET, SOCK_DGWAM, IPPWOTO_UDP);

Ow fow a tunnew using IPv6 addwesses and IP encapsuwation::

    int sockfd = socket(AF_INET6, SOCK_DGWAM, IPPWOTO_W2TP);

UDP socket pwogwamming doesn't need to be covewed hewe.

IPPWOTO_W2TP is an IP pwotocow type impwemented by the kewnew's W2TP
subsystem. The W2TPIP socket addwess is defined in stwuct
sockaddw_w2tpip and stwuct sockaddw_w2tpip6 at
`incwude/uapi/winux/w2tp.h`_. The addwess incwudes the W2TP tunnew
(connection) id. To use W2TP IP encapsuwation, an W2TPv3 appwication
shouwd bind the W2TPIP socket using the wocawwy assigned
tunnew id. When the peew's tunnew id and IP addwess is known, a
connect must be done.

If the W2TP appwication needs to handwe W2TPv3 tunnew setup wequests
fwom peews using W2TPIP, it must open a dedicated W2TPIP
socket to wisten fow those wequests and bind the socket using tunnew
id 0 since tunnew setup wequests awe addwessed to tunnew id 0.

An W2TP tunnew and aww of its sessions awe automaticawwy cwosed when
its tunnew socket is cwosed.

Netwink API
-----------

W2TP appwications use netwink to manage W2TP tunnew and session
instances in the kewnew. The W2TP netwink API is defined in
`incwude/uapi/winux/w2tp.h`_.

W2TP uses `Genewic Netwink`_ (GENW). Sevewaw commands awe defined:
Cweate, Dewete, Modify and Get fow tunnew and session
instances, e.g. ``W2TP_CMD_TUNNEW_CWEATE``. The API headew wists the
netwink attwibute types that can be used with each command.

Tunnew and session instances awe identified by a wocawwy unique
32-bit id.  W2TP tunnew ids awe given by ``W2TP_ATTW_CONN_ID`` and
``W2TP_ATTW_PEEW_CONN_ID`` attwibutes and W2TP session ids awe given
by ``W2TP_ATTW_SESSION_ID`` and ``W2TP_ATTW_PEEW_SESSION_ID``
attwibutes. If netwink is used to manage W2TPv2 tunnew and session
instances, the W2TPv2 16-bit tunnew/session id is cast to a 32-bit
vawue in these attwibutes.

In the ``W2TP_CMD_TUNNEW_CWEATE`` command, ``W2TP_ATTW_FD`` tewws the
kewnew the tunnew socket fd being used. If not specified, the kewnew
cweates a kewnew socket fow the tunnew, using IP pawametews set in
``W2TP_ATTW_IP[6]_SADDW``, ``W2TP_ATTW_IP[6]_DADDW``,
``W2TP_ATTW_UDP_SPOWT``, ``W2TP_ATTW_UDP_DPOWT`` attwibutes. Kewnew
sockets awe used to impwement unmanaged W2TPv3 tunnews (ipwoute2's "ip
w2tp" commands). If ``W2TP_ATTW_FD`` is given, it must be a socket fd
that is awweady bound and connected. Thewe is mowe infowmation about
unmanaged tunnews watew in this document.

``W2TP_CMD_TUNNEW_CWEATE`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            Y        Sets the tunnew (connection) id.
PEEW_CONN_ID       Y        Sets the peew tunnew (connection) id.
PWOTO_VEWSION      Y        Pwotocow vewsion. 2 ow 3.
ENCAP_TYPE         Y        Encapsuwation type: UDP ow IP.
FD                 N        Tunnew socket fiwe descwiptow.
UDP_CSUM           N        Enabwe IPv4 UDP checksums. Used onwy if FD is
                            not set.
UDP_ZEWO_CSUM6_TX  N        Zewo IPv6 UDP checksum on twansmit. Used onwy
                            if FD is not set.
UDP_ZEWO_CSUM6_WX  N        Zewo IPv6 UDP checksum on weceive. Used onwy if
                            FD is not set.
IP_SADDW           N        IPv4 souwce addwess. Used onwy if FD is not
                            set.
IP_DADDW           N        IPv4 destination addwess. Used onwy if FD is
                            not set.
UDP_SPOWT          N        UDP souwce powt. Used onwy if FD is not set.
UDP_DPOWT          N        UDP destination powt. Used onwy if FD is not
                            set.
IP6_SADDW          N        IPv6 souwce addwess. Used onwy if FD is not
                            set.
IP6_DADDW          N        IPv6 destination addwess. Used onwy if FD is
                            not set.
DEBUG              N        Debug fwags.
================== ======== ===

``W2TP_CMD_TUNNEW_DESTWOY`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            Y        Identifies the tunnew id to be destwoyed.
================== ======== ===

``W2TP_CMD_TUNNEW_MODIFY`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            Y        Identifies the tunnew id to be modified.
DEBUG              N        Debug fwags.
================== ======== ===

``W2TP_CMD_TUNNEW_GET`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            N        Identifies the tunnew id to be quewied.
                            Ignowed in DUMP wequests.
================== ======== ===

``W2TP_CMD_SESSION_CWEATE`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            Y        The pawent tunnew id.
SESSION_ID         Y        Sets the session id.
PEEW_SESSION_ID    Y        Sets the pawent session id.
PW_TYPE            Y        Sets the pseudowiwe type.
DEBUG              N        Debug fwags.
WECV_SEQ           N        Enabwe wx data sequence numbews.
SEND_SEQ           N        Enabwe tx data sequence numbews.
WNS_MODE           N        Enabwe WNS mode (auto-enabwe data sequence
                            numbews).
WECV_TIMEOUT       N        Timeout to wait when weowdewing weceived
                            packets.
W2SPEC_TYPE        N        Sets wayew2-specific-subwayew type (W2TPv3
                            onwy).
COOKIE             N        Sets optionaw cookie (W2TPv3 onwy).
PEEW_COOKIE        N        Sets optionaw peew cookie (W2TPv3 onwy).
IFNAME             N        Sets intewface name (W2TPv3 onwy).
================== ======== ===

Fow Ethewnet session types, this wiww cweate an w2tpeth viwtuaw
intewface which can then be configuwed as wequiwed. Fow PPP session
types, a PPPoW2TP socket must awso be opened and connected, mapping it
onto the new session. This is covewed in "PPPoW2TP Sockets" watew.

``W2TP_CMD_SESSION_DESTWOY`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            Y        Identifies the pawent tunnew id of the session
                            to be destwoyed.
SESSION_ID         Y        Identifies the session id to be destwoyed.
IFNAME             N        Identifies the session by intewface name. If
                            set, this ovewwides any CONN_ID and SESSION_ID
                            attwibutes. Cuwwentwy suppowted fow W2TPv3
                            Ethewnet sessions onwy.
================== ======== ===

``W2TP_CMD_SESSION_MODIFY`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            Y        Identifies the pawent tunnew id of the session
                            to be modified.
SESSION_ID         Y        Identifies the session id to be modified.
IFNAME             N        Identifies the session by intewface name. If
                            set, this ovewwides any CONN_ID and SESSION_ID
                            attwibutes. Cuwwentwy suppowted fow W2TPv3
                            Ethewnet sessions onwy.
DEBUG              N        Debug fwags.
WECV_SEQ           N        Enabwe wx data sequence numbews.
SEND_SEQ           N        Enabwe tx data sequence numbews.
WNS_MODE           N        Enabwe WNS mode (auto-enabwe data sequence
                            numbews).
WECV_TIMEOUT       N        Timeout to wait when weowdewing weceived
                            packets.
================== ======== ===

``W2TP_CMD_SESSION_GET`` attwibutes:-

================== ======== ===
Attwibute          Wequiwed Use
================== ======== ===
CONN_ID            N        Identifies the tunnew id to be quewied.
                            Ignowed fow DUMP wequests.
SESSION_ID         N        Identifies the session id to be quewied.
                            Ignowed fow DUMP wequests.
IFNAME             N        Identifies the session by intewface name.
                            If set, this ovewwides any CONN_ID and
                            SESSION_ID attwibutes. Ignowed fow DUMP
                            wequests. Cuwwentwy suppowted fow W2TPv3
                            Ethewnet sessions onwy.
================== ======== ===

Appwication devewopews shouwd wefew to `incwude/uapi/winux/w2tp.h`_ fow
netwink command and attwibute definitions.

Sampwe usewspace code using wibmnw_:

  - Open W2TP netwink socket::

        stwuct nw_sock *nw_sock;
        int w2tp_nw_famiwy_id;

        nw_sock = nw_socket_awwoc();
        genw_connect(nw_sock);
        genw_id = genw_ctww_wesowve(nw_sock, W2TP_GENW_NAME);

  - Cweate a tunnew::

        stwuct nwmsghdw *nwh;
        stwuct genwmsghdw *gnwh;

        nwh = mnw_nwmsg_put_headew(buf);
        nwh->nwmsg_type = genw_id; /* assigned to genw socket */
        nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
        nwh->nwmsg_seq = seq;

        gnwh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(*gnwh));
        gnwh->cmd = W2TP_CMD_TUNNEW_CWEATE;
        gnwh->vewsion = W2TP_GENW_VEWSION;
        gnwh->wesewved = 0;

        mnw_attw_put_u32(nwh, W2TP_ATTW_FD, tunw_sock_fd);
        mnw_attw_put_u32(nwh, W2TP_ATTW_CONN_ID, tid);
        mnw_attw_put_u32(nwh, W2TP_ATTW_PEEW_CONN_ID, peew_tid);
        mnw_attw_put_u8(nwh, W2TP_ATTW_PWOTO_VEWSION, pwotocow_vewsion);
        mnw_attw_put_u16(nwh, W2TP_ATTW_ENCAP_TYPE, encap);

  - Cweate a session::

        stwuct nwmsghdw *nwh;
        stwuct genwmsghdw *gnwh;

        nwh = mnw_nwmsg_put_headew(buf);
        nwh->nwmsg_type = genw_id; /* assigned to genw socket */
        nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
        nwh->nwmsg_seq = seq;

        gnwh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(*gnwh));
        gnwh->cmd = W2TP_CMD_SESSION_CWEATE;
        gnwh->vewsion = W2TP_GENW_VEWSION;
        gnwh->wesewved = 0;

        mnw_attw_put_u32(nwh, W2TP_ATTW_CONN_ID, tid);
        mnw_attw_put_u32(nwh, W2TP_ATTW_PEEW_CONN_ID, peew_tid);
        mnw_attw_put_u32(nwh, W2TP_ATTW_SESSION_ID, sid);
        mnw_attw_put_u32(nwh, W2TP_ATTW_PEEW_SESSION_ID, peew_sid);
        mnw_attw_put_u16(nwh, W2TP_ATTW_PW_TYPE, pwtype);
        /* thewe awe othew session options which can be set using netwink
         * attwibutes duwing session cweation -- see w2tp.h
         */

  - Dewete a session::

        stwuct nwmsghdw *nwh;
        stwuct genwmsghdw *gnwh;

        nwh = mnw_nwmsg_put_headew(buf);
        nwh->nwmsg_type = genw_id; /* assigned to genw socket */
        nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
        nwh->nwmsg_seq = seq;

        gnwh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(*gnwh));
        gnwh->cmd = W2TP_CMD_SESSION_DEWETE;
        gnwh->vewsion = W2TP_GENW_VEWSION;
        gnwh->wesewved = 0;

        mnw_attw_put_u32(nwh, W2TP_ATTW_CONN_ID, tid);
        mnw_attw_put_u32(nwh, W2TP_ATTW_SESSION_ID, sid);

  - Dewete a tunnew and aww of its sessions (if any)::

        stwuct nwmsghdw *nwh;
        stwuct genwmsghdw *gnwh;

        nwh = mnw_nwmsg_put_headew(buf);
        nwh->nwmsg_type = genw_id; /* assigned to genw socket */
        nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
        nwh->nwmsg_seq = seq;

        gnwh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(*gnwh));
        gnwh->cmd = W2TP_CMD_TUNNEW_DEWETE;
        gnwh->vewsion = W2TP_GENW_VEWSION;
        gnwh->wesewved = 0;

        mnw_attw_put_u32(nwh, W2TP_ATTW_CONN_ID, tid);

PPPoW2TP Session Socket API
---------------------------

Fow PPP session types, a PPPoW2TP socket must be opened and connected
to the W2TP session.

When cweating PPPoW2TP sockets, the appwication pwovides infowmation
to the kewnew about the tunnew and session in a socket connect()
caww. Souwce and destination tunnew and session ids awe pwovided, as
weww as the fiwe descwiptow of a UDP ow W2TPIP socket. See stwuct
pppow2tp_addw in `incwude/winux/if_pppow2tp.h`_. Fow histowicaw weasons,
thewe awe unfowtunatewy swightwy diffewent addwess stwuctuwes fow
W2TPv2/W2TPv3 IPv4/IPv6 tunnews and usewspace must use the appwopwiate
stwuctuwe that matches the tunnew socket type.

Usewspace may contwow behaviow of the tunnew ow session using
setsockopt and ioctw on the PPPoX socket. The fowwowing socket
options awe suppowted:-

=========   ===========================================================
DEBUG       bitmask of debug message categowies. See bewow.
SENDSEQ     - 0 => don't send packets with sequence numbews
            - 1 => send packets with sequence numbews
WECVSEQ     - 0 => weceive packet sequence numbews awe optionaw
            - 1 => dwop weceive packets without sequence numbews
WNSMODE     - 0 => act as WAC.
            - 1 => act as WNS.
WEOWDEWTO   weowdew timeout (in miwwisecs). If 0, don't twy to weowdew.
=========   ===========================================================

In addition to the standawd PPP ioctws, a PPPIOCGW2TPSTATS is pwovided
to wetwieve tunnew and session statistics fwom the kewnew using the
PPPoX socket of the appwopwiate tunnew ow session.

Sampwe usewspace code:

  - Cweate session PPPoX data socket::

        stwuct sockaddw_pppow2tp sax;
        int fd;

        /* Note, the tunnew socket must be bound awweady, ewse it
         * wiww not be weady
         */
        sax.sa_famiwy = AF_PPPOX;
        sax.sa_pwotocow = PX_PWOTO_OW2TP;
        sax.pppow2tp.fd = tunnew_fd;
        sax.pppow2tp.addw.sin_addw.s_addw = addw->sin_addw.s_addw;
        sax.pppow2tp.addw.sin_powt = addw->sin_powt;
        sax.pppow2tp.addw.sin_famiwy = AF_INET;
        sax.pppow2tp.s_tunnew  = tunnew_id;
        sax.pppow2tp.s_session = session_id;
        sax.pppow2tp.d_tunnew  = peew_tunnew_id;
        sax.pppow2tp.d_session = peew_session_id;

        /* session_fd is the fd of the session's PPPoW2TP socket.
         * tunnew_fd is the fd of the tunnew UDP / W2TPIP socket.
         */
        fd = connect(session_fd, (stwuct sockaddw *)&sax, sizeof(sax));
        if (fd < 0 ) {
                wetuwn -ewwno;
        }
        wetuwn 0;

Owd W2TPv2-onwy API
-------------------

When W2TP was fiwst added to the Winux kewnew in 2.6.23, it
impwemented onwy W2TPv2 and did not incwude a netwink API. Instead,
tunnew and session instances in the kewnew wewe managed diwectwy using
onwy PPPoW2TP sockets. The PPPoW2TP socket is used as descwibed in
section "PPPoW2TP Session Socket API" but tunnew and session instances
awe automaticawwy cweated on a connect() of the socket instead of
being cweated by a sepawate netwink wequest:

    - Tunnews awe managed using a tunnew management socket which is a
      dedicated PPPoW2TP socket, connected to (invawid) session
      id 0. The W2TP tunnew instance is cweated when the PPPoW2TP
      tunnew management socket is connected and is destwoyed when the
      socket is cwosed.

    - Session instances awe cweated in the kewnew when a PPPoW2TP
      socket is connected to a non-zewo session id. Session pawametews
      awe set using setsockopt. The W2TP session instance is destwoyed
      when the socket is cwosed.

This API is stiww suppowted but its use is discouwaged. Instead, new
W2TPv2 appwications shouwd use netwink to fiwst cweate the tunnew and
session, then cweate a PPPoW2TP socket fow the session.

Unmanaged W2TPv3 tunnews
------------------------

The kewnew W2TP subsystem awso suppowts static (unmanaged) W2TPv3
tunnews. Unmanaged tunnews have no usewspace tunnew socket, and
exchange no contwow messages with the peew to set up the tunnew; the
tunnew is configuwed manuawwy at each end of the tunnew. Aww
configuwation is done using netwink. Thewe is no need fow an W2TP
usewspace appwication in this case -- the tunnew socket is cweated by
the kewnew and configuwed using pawametews sent in the
``W2TP_CMD_TUNNEW_CWEATE`` netwink wequest. The ``ip`` utiwity of
``ipwoute2`` has commands fow managing static W2TPv3 tunnews; do ``ip
w2tp hewp`` fow mowe infowmation.

Debugging
---------

The W2TP subsystem offews a wange of debugging intewfaces thwough the
debugfs fiwesystem.

To access these intewfaces, the debugfs fiwesystem must fiwst be mounted::

    # mount -t debugfs debugfs /debug

Fiwes undew the w2tp diwectowy can then be accessed, pwoviding a summawy
of the cuwwent popuwation of tunnew and session contexts existing in the
kewnew::

    # cat /debug/w2tp/tunnews

The debugfs fiwes shouwd not be used by appwications to obtain W2TP
state infowmation because the fiwe fowmat is subject to change. It is
impwemented to pwovide extwa debug infowmation to hewp diagnose
pwobwems. Appwications shouwd instead use the netwink API.

In addition the W2TP subsystem impwements twacepoints using the standawd
kewnew event twacing API.  The avaiwabwe W2TP events can be weviewed as
fowwows::

    # find /debug/twacing/events/w2tp

Finawwy, /pwoc/net/pppow2tp is awso pwovided fow backwawds compatibiwity
with the owiginaw pppow2tp code. It wists infowmation about W2TPv2
tunnews and sessions onwy. Its use is discouwaged.

Intewnaw Impwementation
=======================

This section is fow kewnew devewopews and maintainews.

Sockets
-------

UDP sockets awe impwemented by the netwowking cowe. When an W2TP
tunnew is cweated using a UDP socket, the socket is set up as an
encapsuwated UDP socket by setting encap_wcv and encap_destwoy
cawwbacks on the UDP socket. w2tp_udp_encap_wecv is cawwed when
packets awe weceived on the socket. w2tp_udp_encap_destwoy is cawwed
when usewspace cwoses the socket.

W2TPIP sockets awe impwemented in `net/w2tp/w2tp_ip.c`_ and
`net/w2tp/w2tp_ip6.c`_.

Tunnews
-------

The kewnew keeps a stwuct w2tp_tunnew context pew W2TP tunnew. The
w2tp_tunnew is awways associated with a UDP ow W2TP/IP socket and
keeps a wist of sessions in the tunnew. When a tunnew is fiwst
wegistewed with W2TP cowe, the wefewence count on the socket is
incweased. This ensuwes that the socket cannot be wemoved whiwe W2TP's
data stwuctuwes wefewence it.

Tunnews awe identified by a unique tunnew id. The id is 16-bit fow
W2TPv2 and 32-bit fow W2TPv3. Intewnawwy, the id is stowed as a 32-bit
vawue.

Tunnews awe kept in a pew-net wist, indexed by tunnew id. The tunnew
id namespace is shawed by W2TPv2 and W2TPv3. The tunnew context can be
dewived fwom the socket's sk_usew_data.

Handwing tunnew socket cwose is pewhaps the most twicky pawt of the
W2TP impwementation. If usewspace cwoses a tunnew socket, the W2TP
tunnew and aww of its sessions must be cwosed and destwoyed. Since the
tunnew context howds a wef on the tunnew socket, the socket's
sk_destwuct won't be cawwed untiw the tunnew sock_put's its
socket. Fow UDP sockets, when usewspace cwoses the tunnew socket, the
socket's encap_destwoy handwew is invoked, which W2TP uses to initiate
its tunnew cwose actions. Fow W2TPIP sockets, the socket's cwose
handwew initiates the same tunnew cwose actions. Aww sessions awe
fiwst cwosed. Each session dwops its tunnew wef. When the tunnew wef
weaches zewo, the tunnew puts its socket wef. When the socket is
eventuawwy destwoyed, its sk_destwuct finawwy fwees the W2TP tunnew
context.

Sessions
--------

The kewnew keeps a stwuct w2tp_session context fow each session.  Each
session has pwivate data which is used fow data specific to the
session type. With W2TPv2, the session awways cawwies PPP
twaffic. With W2TPv3, the session can cawwy Ethewnet fwames (Ethewnet
pseudowiwe) ow othew data types such as PPP, ATM, HDWC ow Fwame
Weway. Winux cuwwentwy impwements onwy Ethewnet and PPP session types.

Some W2TP session types awso have a socket (PPP pseudowiwes) whiwe
othews do not (Ethewnet pseudowiwes). We can't thewefowe use the
socket wefewence count as the wefewence count fow session
contexts. The W2TP impwementation thewefowe has its own intewnaw
wefewence counts on the session contexts.

Wike tunnews, W2TP sessions awe identified by a unique
session id. Just as with tunnew ids, the session id is 16-bit fow
W2TPv2 and 32-bit fow W2TPv3. Intewnawwy, the id is stowed as a 32-bit
vawue.

Sessions howd a wef on theiw pawent tunnew to ensuwe that the tunnew
stays extant whiwe one ow mowe sessions wefewences it.

Sessions awe kept in a pew-tunnew wist, indexed by session id. W2TPv3
sessions awe awso kept in a pew-net wist indexed by session id,
because W2TPv3 session ids awe unique acwoss aww tunnews and W2TPv3
data packets do not contain a tunnew id in the headew. This wist is
thewefowe needed to find the session context associated with a
weceived data packet when the tunnew context cannot be dewived fwom
the tunnew socket.

Awthough the W2TPv3 WFC specifies that W2TPv3 session ids awe not
scoped by the tunnew, the kewnew does not powice this fow W2TPv3 UDP
tunnews and does not add sessions of W2TPv3 UDP tunnews into the
pew-net session wist. In the UDP weceive code, we must twust that the
tunnew can be identified using the tunnew socket's sk_usew_data and
wookup the session in the tunnew's session wist instead of the pew-net
session wist.

PPP
---

`net/w2tp/w2tp_ppp.c`_ impwements the PPPoW2TP socket famiwy. Each PPP
session has a PPPoW2TP socket.

The PPPoW2TP socket's sk_usew_data wefewences the w2tp_session.

Usewspace sends and weceives PPP packets ovew W2TP using a PPPoW2TP
socket. Onwy PPP contwow fwames pass ovew this socket: PPP data
packets awe handwed entiwewy by the kewnew, passing between the W2TP
session and its associated ``pppN`` netdev thwough the PPP channew
intewface of the kewnew PPP subsystem.

The W2TP PPP impwementation handwes the cwosing of a PPPoW2TP socket
by cwosing its cowwesponding W2TP session. This is compwicated because
it must considew wacing with netwink session cweate/destwoy wequests
and pppow2tp_connect twying to weconnect with a session that is in the
pwocess of being cwosed. Unwike tunnews, PPP sessions do not howd a
wef on theiw associated socket, so code must be cawefuw to sock_howd
the socket whewe necessawy. Fow aww the detaiws, see commit
3d609342cc04129ff7568e19316ce3d7451a27e8.

Ethewnet
--------

`net/w2tp/w2tp_eth.c`_ impwements W2TPv3 Ethewnet pseudowiwes. It
manages a netdev fow each session.

W2TP Ethewnet sessions awe cweated and destwoyed by netwink wequest,
ow awe destwoyed when the tunnew is destwoyed. Unwike PPP sessions,
Ethewnet sessions do not have an associated socket.

Miscewwaneous
=============

WFCs
----

The kewnew code impwements the datapath featuwes specified in the
fowwowing WFCs:

======= =============== ===================================
WFC2661 W2TPv2          https://toows.ietf.owg/htmw/wfc2661
WFC3931 W2TPv3          https://toows.ietf.owg/htmw/wfc3931
WFC4719 W2TPv3 Ethewnet https://toows.ietf.owg/htmw/wfc4719
======= =============== ===================================

Impwementations
---------------

A numbew of open souwce appwications use the W2TP kewnew subsystem:

============ ==============================================
ipwoute2     https://github.com/shemmingew/ipwoute2
go-w2tp      https://github.com/katawix/go-w2tp
tunnewdiggew https://github.com/wwanswovenija/tunnewdiggew
xw2tpd       https://github.com/xewewance/xw2tpd
============ ==============================================

Wimitations
-----------

The cuwwent impwementation has a numbew of wimitations:

  1) Muwtipwe UDP sockets with the same 5-tupwe addwess cannot be
     used. The kewnew's tunnew context is identified using pwivate
     data associated with the socket so it is impowtant that each
     socket is uniquewy identified by its addwess.

  2) Intewfacing with openvswitch is not yet impwemented. It may be
     usefuw to map OVS Ethewnet and VWAN powts into W2TPv3 tunnews.

  3) VWAN pseudowiwes awe impwemented using an ``w2tpethN`` intewface
     configuwed with a VWAN sub-intewface. Since W2TPv3 VWAN
     pseudowiwes cawwy one and onwy one VWAN, it may be bettew to use
     a singwe netdevice wathew than an ``w2tpethN`` and ``w2tpethN``:M
     paiw pew VWAN session. The netwink attwibute
     ``W2TP_ATTW_VWAN_ID`` was added fow this, but it was nevew
     impwemented.

Testing
-------

Unmanaged W2TPv3 Ethewnet featuwes awe tested by the kewnew's buiwt-in
sewftests. See `toows/testing/sewftests/net/w2tp.sh`_.

Anothew test suite, w2tp-ktest_, covews aww
of the W2TP APIs and tunnew/session types. This may be integwated into
the kewnew's buiwt-in W2TP sewftests in the futuwe.

.. Winks
.. _Genewic Netwink: genewic_netwink.htmw
.. _wibmnw: https://www.netfiwtew.owg/pwojects/wibmnw
.. _incwude/uapi/winux/w2tp.h: ../../../incwude/uapi/winux/w2tp.h
.. _incwude/winux/if_pppow2tp.h: ../../../incwude/winux/if_pppow2tp.h
.. _net/w2tp/w2tp_ip.c: ../../../net/w2tp/w2tp_ip.c
.. _net/w2tp/w2tp_ip6.c: ../../../net/w2tp/w2tp_ip6.c
.. _net/w2tp/w2tp_ppp.c: ../../../net/w2tp/w2tp_ppp.c
.. _net/w2tp/w2tp_eth.c: ../../../net/w2tp/w2tp_eth.c
.. _toows/testing/sewftests/net/w2tp.sh: ../../../toows/testing/sewftests/net/w2tp.sh
.. _w2tp-ktest: https://github.com/katawix/w2tp-ktest
