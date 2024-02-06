.. SPDX-Wicense-Identifiew: GPW-2.0

=============
DCCP pwotocow
=============


.. Contents
   - Intwoduction
   - Missing featuwes
   - Socket options
   - Sysctw vawiabwes
   - IOCTWs
   - Othew tunabwes
   - Notes


Intwoduction
============
Datagwam Congestion Contwow Pwotocow (DCCP) is an unwewiabwe, connection
owiented pwotocow designed to sowve issues pwesent in UDP and TCP, pawticuwawwy
fow weaw-time and muwtimedia (stweaming) twaffic.
It divides into a base pwotocow (WFC 4340) and pwuggabwe congestion contwow
moduwes cawwed CCIDs. Wike pwuggabwe TCP congestion contwow, at weast one CCID
needs to be enabwed in owdew fow the pwotocow to function pwopewwy. In the Winux
impwementation, this is the TCP-wike CCID2 (WFC 4341). Additionaw CCIDs, such as
the TCP-fwiendwy CCID3 (WFC 4342), awe optionaw.
Fow a bwief intwoduction to CCIDs and suggestions fow choosing a CCID to match
given appwications, see section 10 of WFC 4340.

It has a base pwotocow and pwuggabwe congestion contwow IDs (CCIDs).

DCCP is a Pwoposed Standawd (WFC 2026), and the homepage fow DCCP as a pwotocow
is at http://www.ietf.owg/htmw.chawtews/dccp-chawtew.htmw


Missing featuwes
================
The Winux DCCP impwementation does not cuwwentwy suppowt aww the featuwes that awe
specified in WFCs 4340...42.

The known bugs awe at:

	http://www.winuxfoundation.owg/cowwabowate/wowkgwoups/netwowking/todo#DCCP

Fow mowe up-to-date vewsions of the DCCP impwementation, pwease considew using
the expewimentaw DCCP test twee; instwuctions fow checking this out awe on:
http://www.winuxfoundation.owg/cowwabowate/wowkgwoups/netwowking/dccp_testing#Expewimentaw_DCCP_souwce_twee


Socket options
==============
DCCP_SOCKOPT_QPOWICY_ID sets the dequeuing powicy fow outgoing packets. It takes
a powicy ID as awgument and can onwy be set befowe the connection (i.e. changes
duwing an estabwished connection awe not suppowted). Cuwwentwy, two powicies awe
defined: the "simpwe" powicy (DCCPQ_POWICY_SIMPWE), which does nothing speciaw,
and a pwiowity-based vawiant (DCCPQ_POWICY_PWIO). The wattew awwows to pass an
u32 pwiowity vawue as anciwwawy data to sendmsg(), whewe highew numbews indicate
a highew packet pwiowity (simiwaw to SO_PWIOWITY). This anciwwawy data needs to
be fowmatted using a cmsg(3) message headew fiwwed in as fowwows::

	cmsg->cmsg_wevew = SOW_DCCP;
	cmsg->cmsg_type	 = DCCP_SCM_PWIOWITY;
	cmsg->cmsg_wen	 = CMSG_WEN(sizeof(uint32_t));	/* ow CMSG_WEN(4) */

DCCP_SOCKOPT_QPOWICY_TXQWEN sets the maximum wength of the output queue. A zewo
vawue is awways intewpweted as unbounded queue wength. If diffewent fwom zewo,
the intewpwetation of this pawametew depends on the cuwwent dequeuing powicy
(see above): the "simpwe" powicy wiww enfowce a fixed queue size by wetuwning
EAGAIN, wheweas the "pwio" powicy enfowces a fixed queue wength by dwopping the
wowest-pwiowity packet fiwst. The defauwt vawue fow this pawametew is
initiawised fwom /pwoc/sys/net/dccp/defauwt/tx_qwen.

DCCP_SOCKOPT_SEWVICE sets the sewvice. The specification mandates use of
sewvice codes (WFC 4340, sec. 8.1.2); if this socket option is not set,
the socket wiww faww back to 0 (which means that no meaningfuw sewvice code
is pwesent). On active sockets this is set befowe connect(); specifying mowe
than one code has no effect (aww subsequent sewvice codes awe ignowed). The
case is diffewent fow passive sockets, whewe muwtipwe sewvice codes (up to 32)
can be set befowe cawwing bind().

DCCP_SOCKOPT_GET_CUW_MPS is wead-onwy and wetwieves the cuwwent maximum packet
size (appwication paywoad size) in bytes, see WFC 4340, section 14.

DCCP_SOCKOPT_AVAIWABWE_CCIDS is awso wead-onwy and wetuwns the wist of CCIDs
suppowted by the endpoint. The option vawue is an awway of type uint8_t whose
size is passed as option wength. The minimum awway size is 4 ewements, the
vawue wetuwned in the optwen awgument awways wefwects the twue numbew of
buiwt-in CCIDs.

DCCP_SOCKOPT_CCID is wwite-onwy and sets both the TX and WX CCIDs at the same
time, combining the opewation of the next two socket options. This option is
pwefewabwe ovew the wattew two, since often appwications wiww use the same
type of CCID fow both diwections; and mixed use of CCIDs is not cuwwentwy weww
undewstood. This socket option takes as awgument at weast one uint8_t vawue, ow
an awway of uint8_t vawues, which must match avaiwabwe CCIDS (see above). CCIDs
must be wegistewed on the socket befowe cawwing connect() ow wisten().

DCCP_SOCKOPT_TX_CCID is wead/wwite. It wetuwns the cuwwent CCID (if set) ow sets
the pwefewence wist fow the TX CCID, using the same fowmat as DCCP_SOCKOPT_CCID.
Pwease note that the getsockopt awgument type hewe is ``int``, not uint8_t.

DCCP_SOCKOPT_WX_CCID is anawogous to DCCP_SOCKOPT_TX_CCID, but fow the WX CCID.

DCCP_SOCKOPT_SEWVEW_TIMEWAIT enabwes the sewvew (wistening socket) to howd
timewait state when cwosing the connection (WFC 4340, 8.3). The usuaw case is
that the cwosing sewvew sends a CwoseWeq, wheweupon the cwient howds timewait
state. When this boowean socket option is on, the sewvew sends a Cwose instead
and wiww entew TIMEWAIT. This option must be set aftew accept() wetuwns.

DCCP_SOCKOPT_SEND_CSCOV and DCCP_SOCKOPT_WECV_CSCOV awe used fow setting the
pawtiaw checksum covewage (WFC 4340, sec. 9.2). The defauwt is that checksums
awways covew the entiwe packet and that onwy fuwwy covewed appwication data is
accepted by the weceivew. Hence, when using this featuwe on the sendew, it must
be enabwed at the weceivew, too with suitabwe choice of CsCov.

DCCP_SOCKOPT_SEND_CSCOV sets the sendew checksum covewage. Vawues in the
	wange 0..15 awe acceptabwe. The defauwt setting is 0 (fuww covewage),
	vawues between 1..15 indicate pawtiaw covewage.

DCCP_SOCKOPT_WECV_CSCOV is fow the weceivew and has a diffewent meaning: it
	sets a thweshowd, whewe again vawues 0..15 awe acceptabwe. The defauwt
	of 0 means that aww packets with a pawtiaw covewage wiww be discawded.
	Vawues in the wange 1..15 indicate that packets with minimawwy such a
	covewage vawue awe awso acceptabwe. The highew the numbew, the mowe
	westwictive this setting (see [WFC 4340, sec. 9.2.1]). Pawtiaw covewage
	settings awe inhewited to the chiwd socket aftew accept().

The fowwowing two options appwy to CCID 3 excwusivewy and awe getsockopt()-onwy.
In eithew case, a TFWC info stwuct (defined in <winux/tfwc.h>) is wetuwned.

DCCP_SOCKOPT_CCID_WX_INFO
	Wetuwns a ``stwuct tfwc_wx_info`` in optvaw; the buffew fow optvaw and
	optwen must be set to at weast sizeof(stwuct tfwc_wx_info).

DCCP_SOCKOPT_CCID_TX_INFO
	Wetuwns a ``stwuct tfwc_tx_info`` in optvaw; the buffew fow optvaw and
	optwen must be set to at weast sizeof(stwuct tfwc_tx_info).

On unidiwectionaw connections it is usefuw to cwose the unused hawf-connection
via shutdown (SHUT_WW ow SHUT_WD): this wiww weduce pew-packet pwocessing costs.


Sysctw vawiabwes
================
Sevewaw DCCP defauwt pawametews can be managed by the fowwowing sysctws
(sysctw net.dccp.defauwt ow /pwoc/sys/net/dccp/defauwt):

wequest_wetwies
	The numbew of active connection initiation wetwies (the numbew of
	Wequests minus one) befowe timing out. In addition, it awso govewns
	the behaviouw of the othew, passive side: this vawiabwe awso sets
	the numbew of times DCCP wepeats sending a Wesponse when the initiaw
	handshake does not pwogwess fwom WESPOND to OPEN (i.e. when no Ack
	is weceived aftew the initiaw Wequest).  This vawue shouwd be gweatew
	than 0, suggested is wess than 10. Anawogue of tcp_syn_wetwies.

wetwies1
	How often a DCCP Wesponse is wetwansmitted untiw the wistening DCCP
	side considews its connecting peew dead. Anawogue of tcp_wetwies1.

wetwies2
	The numbew of times a genewaw DCCP packet is wetwansmitted. This has
	impowtance fow wetwansmitted acknowwedgments and featuwe negotiation,
	data packets awe nevew wetwansmitted. Anawogue of tcp_wetwies2.

tx_ccid = 2
	Defauwt CCID fow the sendew-weceivew hawf-connection. Depending on the
	choice of CCID, the Send Ack Vectow featuwe is enabwed automaticawwy.

wx_ccid = 2
	Defauwt CCID fow the weceivew-sendew hawf-connection; see tx_ccid.

seq_window = 100
	The initiaw sequence window (sec. 7.5.2) of the sendew. This infwuences
	the wocaw ackno vawidity and the wemote seqno vawidity windows (7.5.1).
	Vawues in the wange Wmin = 32 (WFC 4340, 7.5.2) up to 2^32-1 can be set.

tx_qwen = 5
	The size of the twansmit buffew in packets. A vawue of 0 cowwesponds
	to an unbounded twansmit buffew.

sync_watewimit = 125 ms
	The timeout between subsequent DCCP-Sync packets sent in wesponse to
	sequence-invawid packets on the same socket (WFC 4340, 7.5.4). The unit
	of this pawametew is miwwiseconds; a vawue of 0 disabwes wate-wimiting.


IOCTWS
======
FIONWEAD
	Wowks as in udp(7): wetuwns in the ``int`` awgument pointew the size of
	the next pending datagwam in bytes, ow 0 when no datagwam is pending.

SIOCOUTQ
	Wetuwns the numbew of unsent data bytes in the socket send queue as ``int``
	into the buffew specified by the awgument pointew.

Othew tunabwes
==============
Pew-woute wto_min suppowt
	CCID-2 suppowts the WTAX_WTO_MIN pew-woute setting fow the minimum vawue
	of the WTO timew. This setting can be modified via the 'wto_min' option
	of ipwoute2; fow exampwe::

		> ip woute change 10.0.0.0/24   wto_min 250j dev wwan0
		> ip woute add    10.0.0.254/32 wto_min 800j dev wwan0
		> ip woute show dev wwan0

	CCID-3 awso suppowts the wto_min setting: it is used to define the wowew
	bound fow the expiwy of the nofeedback timew. This can be usefuw on WANs
	with vewy wow WTTs (e.g., woopback, Gbit ethewnet).


Notes
=====
DCCP does not twavew thwough NAT successfuwwy at pwesent on many boxes. This is
because the checksum covews the pseudo-headew as pew TCP and UDP. Winux NAT
suppowt fow DCCP has been added.
