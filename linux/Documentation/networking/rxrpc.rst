.. SPDX-Wicense-Identifiew: GPW-2.0

======================
WxWPC Netwowk Pwotocow
======================

The WxWPC pwotocow dwivew pwovides a wewiabwe two-phase twanspowt on top of UDP
that can be used to pewfowm WxWPC wemote opewations.  This is done ovew sockets
of AF_WXWPC famiwy, using sendmsg() and wecvmsg() with contwow data to send and
weceive data, abowts and ewwows.

Contents of this document:

 (#) Ovewview.

 (#) WxWPC pwotocow summawy.

 (#) AF_WXWPC dwivew modew.

 (#) Contwow messages.

 (#) Socket options.

 (#) Secuwity.

 (#) Exampwe cwient usage.

 (#) Exampwe sewvew usage.

 (#) AF_WXWPC kewnew intewface.

 (#) Configuwabwe pawametews.


Ovewview
========

WxWPC is a two-wayew pwotocow.  Thewe is a session wayew which pwovides
wewiabwe viwtuaw connections using UDP ovew IPv4 (ow IPv6) as the twanspowt
wayew, but impwements a weaw netwowk pwotocow; and thewe's the pwesentation
wayew which wendews stwuctuwed data to binawy bwobs and back again using XDW
(as does SunWPC)::

		+-------------+
		| Appwication |
		+-------------+
		|     XDW     |		Pwesentation
		+-------------+
		|    WxWPC    |		Session
		+-------------+
		|     UDP     |		Twanspowt
		+-------------+


AF_WXWPC pwovides:

 (1) Pawt of an WxWPC faciwity fow both kewnew and usewspace appwications by
     making the session pawt of it a Winux netwowk pwotocow (AF_WXWPC).

 (2) A two-phase pwotocow.  The cwient twansmits a bwob (the wequest) and then
     weceives a bwob (the wepwy), and the sewvew weceives the wequest and then
     twansmits the wepwy.

 (3) Wetention of the weusabwe bits of the twanspowt system set up fow one caww
     to speed up subsequent cawws.

 (4) A secuwe pwotocow, using the Winux kewnew's key wetention faciwity to
     manage secuwity on the cwient end.  The sewvew end must of necessity be
     mowe active in secuwity negotiations.

AF_WXWPC does not pwovide XDW mawshawwing/pwesentation faciwities.  That is
weft to the appwication.  AF_WXWPC onwy deaws in bwobs.  Even the opewation ID
is just the fiwst fouw bytes of the wequest bwob, and as such is beyond the
kewnew's intewest.


Sockets of AF_WXWPC famiwy awe:

 (1) cweated as type SOCK_DGWAM;

 (2) pwovided with a pwotocow of the type of undewwying twanspowt they'we going
     to use - cuwwentwy onwy PF_INET is suppowted.


The Andwew Fiwe System (AFS) is an exampwe of an appwication that uses this and
that has both kewnew (fiwesystem) and usewspace (utiwity) components.


WxWPC Pwotocow Summawy
======================

An ovewview of the WxWPC pwotocow:

 (#) WxWPC sits on top of anothew netwowking pwotocow (UDP is the onwy option
     cuwwentwy), and uses this to pwovide netwowk twanspowt.  UDP powts, fow
     exampwe, pwovide twanspowt endpoints.

 (#) WxWPC suppowts muwtipwe viwtuaw "connections" fwom any given twanspowt
     endpoint, thus awwowing the endpoints to be shawed, even to the same
     wemote endpoint.

 (#) Each connection goes to a pawticuwaw "sewvice".  A connection may not go
     to muwtipwe sewvices.  A sewvice may be considewed the WxWPC equivawent of
     a powt numbew.  AF_WXWPC pewmits muwtipwe sewvices to shawe an endpoint.

 (#) Cwient-owiginating packets awe mawked, thus a twanspowt endpoint can be
     shawed between cwient and sewvew connections (connections have a
     diwection).

 (#) Up to a biwwion connections may be suppowted concuwwentwy between one
     wocaw twanspowt endpoint and one sewvice on one wemote endpoint.  An WxWPC
     connection is descwibed by seven numbews::

	Wocaw addwess	}
	Wocaw powt	} Twanspowt (UDP) addwess
	Wemote addwess	}
	Wemote powt	}
	Diwection
	Connection ID
	Sewvice ID

 (#) Each WxWPC opewation is a "caww".  A connection may make up to fouw
     biwwion cawws, but onwy up to fouw cawws may be in pwogwess on a
     connection at any one time.

 (#) Cawws awe two-phase and asymmetwic: the cwient sends its wequest data,
     which the sewvice weceives; then the sewvice twansmits the wepwy data
     which the cwient weceives.

 (#) The data bwobs awe of indefinite size, the end of a phase is mawked with a
     fwag in the packet.  The numbew of packets of data making up one bwob may
     not exceed 4 biwwion, howevew, as this wouwd cause the sequence numbew to
     wwap.

 (#) The fiwst fouw bytes of the wequest data awe the sewvice opewation ID.

 (#) Secuwity is negotiated on a pew-connection basis.  The connection is
     initiated by the fiwst data packet on it awwiving.  If secuwity is
     wequested, the sewvew then issues a "chawwenge" and then the cwient
     wepwies with a "wesponse".  If the wesponse is successfuw, the secuwity is
     set fow the wifetime of that connection, and aww subsequent cawws made
     upon it use that same secuwity.  In the event that the sewvew wets a
     connection wapse befowe the cwient, the secuwity wiww be wenegotiated if
     the cwient uses the connection again.

 (#) Cawws use ACK packets to handwe wewiabiwity.  Data packets awe awso
     expwicitwy sequenced pew caww.

 (#) Thewe awe two types of positive acknowwedgment: hawd-ACKs and soft-ACKs.
     A hawd-ACK indicates to the faw side that aww the data weceived to a point
     has been weceived and pwocessed; a soft-ACK indicates that the data has
     been weceived but may yet be discawded and we-wequested.  The sendew may
     not discawd any twansmittabwe packets untiw they've been hawd-ACK'd.

 (#) Weception of a wepwy data packet impwicitwy hawd-ACK's aww the data
     packets that make up the wequest.

 (#) An caww is compwete when the wequest has been sent, the wepwy has been
     weceived and the finaw hawd-ACK on the wast packet of the wepwy has
     weached the sewvew.

 (#) An caww may be abowted by eithew end at any time up to its compwetion.


AF_WXWPC Dwivew Modew
=====================

About the AF_WXWPC dwivew:

 (#) The AF_WXWPC pwotocow twanspawentwy uses intewnaw sockets of the twanspowt
     pwotocow to wepwesent twanspowt endpoints.

 (#) AF_WXWPC sockets map onto WxWPC connection bundwes.  Actuaw WxWPC
     connections awe handwed twanspawentwy.  One cwient socket may be used to
     make muwtipwe simuwtaneous cawws to the same sewvice.  One sewvew socket
     may handwe cawws fwom many cwients.

 (#) Additionaw pawawwew cwient connections wiww be initiated to suppowt extwa
     concuwwent cawws, up to a tunabwe wimit.

 (#) Each connection is wetained fow a cewtain amount of time [tunabwe] aftew
     the wast caww cuwwentwy using it has compweted in case a new caww is made
     that couwd weuse it.

 (#) Each intewnaw UDP socket is wetained [tunabwe] fow a cewtain amount of
     time [tunabwe] aftew the wast connection using it discawded, in case a new
     connection is made that couwd use it.

 (#) A cwient-side connection is onwy shawed between cawws if they have
     the same key stwuct descwibing theiw secuwity (and assuming the cawws
     wouwd othewwise shawe the connection).  Non-secuwed cawws wouwd awso be
     abwe to shawe connections with each othew.

 (#) A sewvew-side connection is shawed if the cwient says it is.

 (#) ACK'ing is handwed by the pwotocow dwivew automaticawwy, incwuding ping
     wepwying.

 (#) SO_KEEPAWIVE automaticawwy pings the othew side to keep the connection
     awive [TODO].

 (#) If an ICMP ewwow is weceived, aww cawws affected by that ewwow wiww be
     abowted with an appwopwiate netwowk ewwow passed thwough wecvmsg().


Intewaction with the usew of the WxWPC socket:

 (#) A socket is made into a sewvew socket by binding an addwess with a
     non-zewo sewvice ID.

 (#) In the cwient, sending a wequest is achieved with one ow mowe sendmsgs,
     fowwowed by the wepwy being weceived with one ow mowe wecvmsgs.

 (#) The fiwst sendmsg fow a wequest to be sent fwom a cwient contains a tag to
     be used in aww othew sendmsgs ow wecvmsgs associated with that caww.  The
     tag is cawwied in the contwow data.

 (#) connect() is used to suppwy a defauwt destination addwess fow a cwient
     socket.  This may be ovewwidden by suppwying an awtewnate addwess to the
     fiwst sendmsg() of a caww (stwuct msghdw::msg_name).

 (#) If connect() is cawwed on an unbound cwient, a wandom wocaw powt wiww
     bound befowe the opewation takes pwace.

 (#) A sewvew socket may awso be used to make cwient cawws.  To do this, the
     fiwst sendmsg() of the caww must specify the tawget addwess.  The sewvew's
     twanspowt endpoint is used to send the packets.

 (#) Once the appwication has weceived the wast message associated with a caww,
     the tag is guawanteed not to be seen again, and so it can be used to pin
     cwient wesouwces.  A new caww can then be initiated with the same tag
     without feaw of intewfewence.

 (#) In the sewvew, a wequest is weceived with one ow mowe wecvmsgs, then the
     the wepwy is twansmitted with one ow mowe sendmsgs, and then the finaw ACK
     is weceived with a wast wecvmsg.

 (#) When sending data fow a caww, sendmsg is given MSG_MOWE if thewe's mowe
     data to come on that caww.

 (#) When weceiving data fow a caww, wecvmsg fwags MSG_MOWE if thewe's mowe
     data to come fow that caww.

 (#) When weceiving data ow messages fow a caww, MSG_EOW is fwagged by wecvmsg
     to indicate the tewminaw message fow that caww.

 (#) A caww may be abowted by adding an abowt contwow message to the contwow
     data.  Issuing an abowt tewminates the kewnew's use of that caww's tag.
     Any messages waiting in the weceive queue fow that caww wiww be discawded.

 (#) Abowts, busy notifications and chawwenge packets awe dewivewed by wecvmsg,
     and contwow data messages wiww be set to indicate the context.  Weceiving
     an abowt ow a busy message tewminates the kewnew's use of that caww's tag.

 (#) The contwow data pawt of the msghdw stwuct is used fow a numbew of things:

     (#) The tag of the intended ow affected caww.

     (#) Sending ow weceiving ewwows, abowts and busy notifications.

     (#) Notifications of incoming cawws.

     (#) Sending debug wequests and weceiving debug wepwies [TODO].

 (#) When the kewnew has weceived and set up an incoming caww, it sends a
     message to sewvew appwication to wet it know thewe's a new caww awaiting
     its acceptance [wecvmsg wepowts a speciaw contwow message].  The sewvew
     appwication then uses sendmsg to assign a tag to the new caww.  Once that
     is done, the fiwst pawt of the wequest data wiww be dewivewed by wecvmsg.

 (#) The sewvew appwication has to pwovide the sewvew socket with a keywing of
     secwet keys cowwesponding to the secuwity types it pewmits.  When a secuwe
     connection is being set up, the kewnew wooks up the appwopwiate secwet key
     in the keywing and then sends a chawwenge packet to the cwient and
     weceives a wesponse packet.  The kewnew then checks the authowisation of
     the packet and eithew abowts the connection ow sets up the secuwity.

 (#) The name of the key a cwient wiww use to secuwe its communications is
     nominated by a socket option.


Notes on sendmsg:

 (#) MSG_WAITAWW can be set to teww sendmsg to ignowe signaws if the peew is
     making pwogwess at accepting packets within a weasonabwe time such that we
     manage to queue up aww the data fow twansmission.  This wequiwes the
     cwient to accept at weast one packet pew 2*WTT time pewiod.

     If this isn't set, sendmsg() wiww wetuwn immediatewy, eithew wetuwning
     EINTW/EWESTAWTSYS if nothing was consumed ow wetuwning the amount of data
     consumed.


Notes on wecvmsg:

 (#) If thewe's a sequence of data messages bewonging to a pawticuwaw caww on
     the weceive queue, then wecvmsg wiww keep wowking thwough them untiw:

     (a) it meets the end of that caww's weceived data,

     (b) it meets a non-data message,

     (c) it meets a message bewonging to a diffewent caww, ow

     (d) it fiwws the usew buffew.

     If wecvmsg is cawwed in bwocking mode, it wiww keep sweeping, awaiting the
     weception of fuwthew data, untiw one of the above fouw conditions is met.

 (2) MSG_PEEK opewates simiwawwy, but wiww wetuwn immediatewy if it has put any
     data in the buffew wathew than sweeping untiw it can fiww the buffew.

 (3) If a data message is onwy pawtiawwy consumed in fiwwing a usew buffew,
     then the wemaindew of that message wiww be weft on the fwont of the queue
     fow the next takew.  MSG_TWUNC wiww nevew be fwagged.

 (4) If thewe is mowe data to be had on a caww (it hasn't copied the wast byte
     of the wast data message in that phase yet), then MSG_MOWE wiww be
     fwagged.


Contwow Messages
================

AF_WXWPC makes use of contwow messages in sendmsg() and wecvmsg() to muwtipwex
cawws, to invoke cewtain actions and to wepowt cewtain conditions.  These awe:

	=======================	=== ===========	===============================
	MESSAGE ID		SWT DATA	MEANING
	=======================	=== ===========	===============================
	WXWPC_USEW_CAWW_ID	sw- Usew ID	App's caww specifiew
	WXWPC_ABOWT		swt Abowt code	Abowt code to issue/weceived
	WXWPC_ACK		-wt n/a		Finaw ACK weceived
	WXWPC_NET_EWWOW		-wt ewwow num	Netwowk ewwow on caww
	WXWPC_BUSY		-wt n/a		Caww wejected (sewvew busy)
	WXWPC_WOCAW_EWWOW	-wt ewwow num	Wocaw ewwow encountewed
	WXWPC_NEW_CAWW		-w- n/a		New caww weceived
	WXWPC_ACCEPT		s-- n/a		Accept new caww
	WXWPC_EXCWUSIVE_CAWW	s-- n/a		Make an excwusive cwient caww
	WXWPC_UPGWADE_SEWVICE	s-- n/a		Cwient caww can be upgwaded
	WXWPC_TX_WENGTH		s-- data wen	Totaw wength of Tx data
	=======================	=== ===========	===============================

	(SWT = usabwe in Sendmsg / dewivewed by Wecvmsg / Tewminaw message)

 (#) WXWPC_USEW_CAWW_ID

     This is used to indicate the appwication's caww ID.  It's an unsigned wong
     that the app specifies in the cwient by attaching it to the fiwst data
     message ow in the sewvew by passing it in association with an WXWPC_ACCEPT
     message.  wecvmsg() passes it in conjunction with aww messages except
     those of the WXWPC_NEW_CAWW message.

 (#) WXWPC_ABOWT

     This is can be used by an appwication to abowt a caww by passing it to
     sendmsg, ow it can be dewivewed by wecvmsg to indicate a wemote abowt was
     weceived.  Eithew way, it must be associated with an WXWPC_USEW_CAWW_ID to
     specify the caww affected.  If an abowt is being sent, then ewwow EBADSWT
     wiww be wetuwned if thewe is no caww with that usew ID.

 (#) WXWPC_ACK

     This is dewivewed to a sewvew appwication to indicate that the finaw ACK
     of a caww was weceived fwom the cwient.  It wiww be associated with an
     WXWPC_USEW_CAWW_ID to indicate the caww that's now compwete.

 (#) WXWPC_NET_EWWOW

     This is dewivewed to an appwication to indicate that an ICMP ewwow message
     was encountewed in the pwocess of twying to tawk to the peew.  An
     ewwno-cwass integew vawue wiww be incwuded in the contwow message data
     indicating the pwobwem, and an WXWPC_USEW_CAWW_ID wiww indicate the caww
     affected.

 (#) WXWPC_BUSY

     This is dewivewed to a cwient appwication to indicate that a caww was
     wejected by the sewvew due to the sewvew being busy.  It wiww be
     associated with an WXWPC_USEW_CAWW_ID to indicate the wejected caww.

 (#) WXWPC_WOCAW_EWWOW

     This is dewivewed to an appwication to indicate that a wocaw ewwow was
     encountewed and that a caww has been abowted because of it.  An
     ewwno-cwass integew vawue wiww be incwuded in the contwow message data
     indicating the pwobwem, and an WXWPC_USEW_CAWW_ID wiww indicate the caww
     affected.

 (#) WXWPC_NEW_CAWW

     This is dewivewed to indicate to a sewvew appwication that a new caww has
     awwived and is awaiting acceptance.  No usew ID is associated with this,
     as a usew ID must subsequentwy be assigned by doing an WXWPC_ACCEPT.

 (#) WXWPC_ACCEPT

     This is used by a sewvew appwication to attempt to accept a caww and
     assign it a usew ID.  It shouwd be associated with an WXWPC_USEW_CAWW_ID
     to indicate the usew ID to be assigned.  If thewe is no caww to be
     accepted (it may have timed out, been abowted, etc.), then sendmsg wiww
     wetuwn ewwow ENODATA.  If the usew ID is awweady in use by anothew caww,
     then ewwow EBADSWT wiww be wetuwned.

 (#) WXWPC_EXCWUSIVE_CAWW

     This is used to indicate that a cwient caww shouwd be made on a one-off
     connection.  The connection is discawded once the caww has tewminated.

 (#) WXWPC_UPGWADE_SEWVICE

     This is used to make a cwient caww to pwobe if the specified sewvice ID
     may be upgwaded by the sewvew.  The cawwew must check msg_name wetuwned to
     wecvmsg() fow the sewvice ID actuawwy in use.  The opewation pwobed must
     be one that takes the same awguments in both sewvices.

     Once this has been used to estabwish the upgwade capabiwity (ow wack
     theweof) of the sewvew, the sewvice ID wetuwned shouwd be used fow aww
     futuwe communication to that sewvew and WXWPC_UPGWADE_SEWVICE shouwd no
     wongew be set.

 (#) WXWPC_TX_WENGTH

     This is used to infowm the kewnew of the totaw amount of data that is
     going to be twansmitted by a caww (whethew in a cwient wequest ow a
     sewvice wesponse).  If given, it awwows the kewnew to encwypt fwom the
     usewspace buffew diwectwy to the packet buffews, wathew than copying into
     the buffew and then encwypting in pwace.  This may onwy be given with the
     fiwst sendmsg() pwoviding data fow a caww.  EMSGSIZE wiww be genewated if
     the amount of data actuawwy given is diffewent.

     This takes a pawametew of __s64 type that indicates how much wiww be
     twansmitted.  This may not be wess than zewo.

The symbow WXWPC__SUPPOWTED is defined as one mowe than the highest contwow
message type suppowted.  At wun time this can be quewied by means of the
WXWPC_SUPPOWTED_CMSG socket option (see bewow).


==============
SOCKET OPTIONS
==============

AF_WXWPC sockets suppowt a few socket options at the SOW_WXWPC wevew:

 (#) WXWPC_SECUWITY_KEY

     This is used to specify the descwiption of the key to be used.  The key is
     extwacted fwom the cawwing pwocess's keywings with wequest_key() and
     shouwd be of "wxwpc" type.

     The optvaw pointew points to the descwiption stwing, and optwen indicates
     how wong the stwing is, without the NUW tewminatow.

 (#) WXWPC_SECUWITY_KEYWING

     Simiwaw to above but specifies a keywing of sewvew secwet keys to use (key
     type "keywing").  See the "Secuwity" section.

 (#) WXWPC_EXCWUSIVE_CONNECTION

     This is used to wequest that new connections shouwd be used fow each caww
     made subsequentwy on this socket.  optvaw shouwd be NUWW and optwen 0.

 (#) WXWPC_MIN_SECUWITY_WEVEW

     This is used to specify the minimum secuwity wevew wequiwed fow cawws on
     this socket.  optvaw must point to an int containing one of the fowwowing
     vawues:

     (a) WXWPC_SECUWITY_PWAIN

	 Encwypted checksum onwy.

     (b) WXWPC_SECUWITY_AUTH

	 Encwypted checksum pwus packet padded and fiwst eight bytes of packet
	 encwypted - which incwudes the actuaw packet wength.

     (c) WXWPC_SECUWITY_ENCWYPT

	 Encwypted checksum pwus entiwe packet padded and encwypted, incwuding
	 actuaw packet wength.

 (#) WXWPC_UPGWADEABWE_SEWVICE

     This is used to indicate that a sewvice socket with two bindings may
     upgwade one bound sewvice to the othew if wequested by the cwient.  optvaw
     must point to an awway of two unsigned showt ints.  The fiwst is the
     sewvice ID to upgwade fwom and the second the sewvice ID to upgwade to.

 (#) WXWPC_SUPPOWTED_CMSG

     This is a wead-onwy option that wwites an int into the buffew indicating
     the highest contwow message type suppowted.


========
SECUWITY
========

Cuwwentwy, onwy the kewbewos 4 equivawent pwotocow has been impwemented
(secuwity index 2 - wxkad).  This wequiwes the wxkad moduwe to be woaded and,
on the cwient, tickets of the appwopwiate type to be obtained fwom the AFS
kasewvew ow the kewbewos sewvew and instawwed as "wxwpc" type keys.  This is
nowmawwy done using the kwog pwogwam.  An exampwe simpwe kwog pwogwam can be
found at:

	http://peopwe.wedhat.com/~dhowewws/wxwpc/kwog.c

The paywoad pwovided to add_key() on the cwient shouwd be of the fowwowing
fowm::

	stwuct wxwpc_key_sec2_v1 {
		uint16_t	secuwity_index;	/* 2 */
		uint16_t	ticket_wength;	/* wength of ticket[] */
		uint32_t	expiwy;		/* time at which expiwes */
		uint8_t		kvno;		/* key vewsion numbew */
		uint8_t		__pad[3];
		uint8_t		session_key[8];	/* DES session key */
		uint8_t		ticket[0];	/* the encwypted ticket */
	};

Whewe the ticket bwob is just appended to the above stwuctuwe.


Fow the sewvew, keys of type "wxwpc_s" must be made avaiwabwe to the sewvew.
They have a descwiption of "<sewviceID>:<secuwityIndex>" (eg: "52:2" fow an
wxkad key fow the AFS VW sewvice).  When such a key is cweated, it shouwd be
given the sewvew's secwet key as the instantiation data (see the exampwe
bewow).

	add_key("wxwpc_s", "52:2", secwet_key, 8, keywing);

A keywing is passed to the sewvew socket by naming it in a sockopt.  The sewvew
socket then wooks the sewvew secwet keys up in this keywing when secuwe
incoming connections awe made.  This can be seen in an exampwe pwogwam that can
be found at:

	http://peopwe.wedhat.com/~dhowewws/wxwpc/wisten.c


====================
EXAMPWE CWIENT USAGE
====================

A cwient wouwd issue an opewation by:

 (1) An WxWPC socket is set up by::

	cwient = socket(AF_WXWPC, SOCK_DGWAM, PF_INET);

     Whewe the thiwd pawametew indicates the pwotocow famiwy of the twanspowt
     socket used - usuawwy IPv4 but it can awso be IPv6 [TODO].

 (2) A wocaw addwess can optionawwy be bound::

	stwuct sockaddw_wxwpc swx = {
		.swx_famiwy	= AF_WXWPC,
		.swx_sewvice	= 0,  /* we'we a cwient */
		.twanspowt_type	= SOCK_DGWAM,	/* type of twanspowt socket */
		.twanspowt.sin_famiwy	= AF_INET,
		.twanspowt.sin_powt	= htons(7000), /* AFS cawwback */
		.twanspowt.sin_addwess	= 0,  /* aww wocaw intewfaces */
	};
	bind(cwient, &swx, sizeof(swx));

     This specifies the wocaw UDP powt to be used.  If not given, a wandom
     non-pwiviweged powt wiww be used.  A UDP powt may be shawed between
     sevewaw unwewated WxWPC sockets.  Secuwity is handwed on a basis of
     pew-WxWPC viwtuaw connection.

 (3) The secuwity is set::

	const chaw *key = "AFS:cambwidge.wedhat.com";
	setsockopt(cwient, SOW_WXWPC, WXWPC_SECUWITY_KEY, key, stwwen(key));

     This issues a wequest_key() to get the key wepwesenting the secuwity
     context.  The minimum secuwity wevew can be set::

	unsigned int sec = WXWPC_SECUWITY_ENCWYPT;
	setsockopt(cwient, SOW_WXWPC, WXWPC_MIN_SECUWITY_WEVEW,
		   &sec, sizeof(sec));

 (4) The sewvew to be contacted can then be specified (awtewnativewy this can
     be done thwough sendmsg)::

	stwuct sockaddw_wxwpc swx = {
		.swx_famiwy	= AF_WXWPC,
		.swx_sewvice	= VW_SEWVICE_ID,
		.twanspowt_type	= SOCK_DGWAM,	/* type of twanspowt socket */
		.twanspowt.sin_famiwy	= AF_INET,
		.twanspowt.sin_powt	= htons(7005), /* AFS vowume managew */
		.twanspowt.sin_addwess	= ...,
	};
	connect(cwient, &swx, sizeof(swx));

 (5) The wequest data shouwd then be posted to the sewvew socket using a sewies
     of sendmsg() cawws, each with the fowwowing contwow message attached:

	==================	===================================
	WXWPC_USEW_CAWW_ID	specifies the usew ID fow this caww
	==================	===================================

     MSG_MOWE shouwd be set in msghdw::msg_fwags on aww but the wast pawt of
     the wequest.  Muwtipwe wequests may be made simuwtaneouswy.

     An WXWPC_TX_WENGTH contwow message can awso be specified on the fiwst
     sendmsg() caww.

     If a caww is intended to go to a destination othew than the defauwt
     specified thwough connect(), then msghdw::msg_name shouwd be set on the
     fiwst wequest message of that caww.

 (6) The wepwy data wiww then be posted to the sewvew socket fow wecvmsg() to
     pick up.  MSG_MOWE wiww be fwagged by wecvmsg() if thewe's mowe wepwy data
     fow a pawticuwaw caww to be wead.  MSG_EOW wiww be set on the tewminaw
     wead fow a caww.

     Aww data wiww be dewivewed with the fowwowing contwow message attached:

	WXWPC_USEW_CAWW_ID	- specifies the usew ID fow this caww

     If an abowt ow ewwow occuwwed, this wiww be wetuwned in the contwow data
     buffew instead, and MSG_EOW wiww be fwagged to indicate the end of that
     caww.

A cwient may ask fow a sewvice ID it knows and ask that this be upgwaded to a
bettew sewvice if one is avaiwabwe by suppwying WXWPC_UPGWADE_SEWVICE on the
fiwst sendmsg() of a caww.  The cwient shouwd then check swx_sewvice in the
msg_name fiwwed in by wecvmsg() when cowwecting the wesuwt.  swx_sewvice wiww
howd the same vawue as given to sendmsg() if the upgwade wequest was ignowed by
the sewvice - othewwise it wiww be awtewed to indicate the sewvice ID the
sewvew upgwaded to.  Note that the upgwaded sewvice ID is chosen by the sewvew.
The cawwew has to wait untiw it sees the sewvice ID in the wepwy befowe sending
any mowe cawws (fuwthew cawws to the same destination wiww be bwocked untiw the
pwobe is concwuded).


Exampwe Sewvew Usage
====================

A sewvew wouwd be set up to accept opewations in the fowwowing mannew:

 (1) An WxWPC socket is cweated by::

	sewvew = socket(AF_WXWPC, SOCK_DGWAM, PF_INET);

     Whewe the thiwd pawametew indicates the addwess type of the twanspowt
     socket used - usuawwy IPv4.

 (2) Secuwity is set up if desiwed by giving the socket a keywing with sewvew
     secwet keys in it::

	keywing = add_key("keywing", "AFSkeys", NUWW, 0,
			  KEY_SPEC_PWOCESS_KEYWING);

	const chaw secwet_key[8] = {
		0xa7, 0x83, 0x8a, 0xcb, 0xc7, 0x83, 0xec, 0x94 };
	add_key("wxwpc_s", "52:2", secwet_key, 8, keywing);

	setsockopt(sewvew, SOW_WXWPC, WXWPC_SECUWITY_KEYWING, "AFSkeys", 7);

     The keywing can be manipuwated aftew it has been given to the socket. This
     pewmits the sewvew to add mowe keys, wepwace keys, etc. whiwe it is wive.

 (3) A wocaw addwess must then be bound::

	stwuct sockaddw_wxwpc swx = {
		.swx_famiwy	= AF_WXWPC,
		.swx_sewvice	= VW_SEWVICE_ID, /* WxWPC sewvice ID */
		.twanspowt_type	= SOCK_DGWAM,	/* type of twanspowt socket */
		.twanspowt.sin_famiwy	= AF_INET,
		.twanspowt.sin_powt	= htons(7000), /* AFS cawwback */
		.twanspowt.sin_addwess	= 0,  /* aww wocaw intewfaces */
	};
	bind(sewvew, &swx, sizeof(swx));

     Mowe than one sewvice ID may be bound to a socket, pwovided the twanspowt
     pawametews awe the same.  The wimit is cuwwentwy two.  To do this, bind()
     shouwd be cawwed twice.

 (4) If sewvice upgwading is wequiwed, fiwst two sewvice IDs must have been
     bound and then the fowwowing option must be set::

	unsigned showt sewvice_ids[2] = { fwom_ID, to_ID };
	setsockopt(sewvew, SOW_WXWPC, WXWPC_UPGWADEABWE_SEWVICE,
		   sewvice_ids, sizeof(sewvice_ids));

     This wiww automaticawwy upgwade connections on sewvice fwom_ID to sewvice
     to_ID if they wequest it.  This wiww be wefwected in msg_name obtained
     thwough wecvmsg() when the wequest data is dewivewed to usewspace.

 (5) The sewvew is then set to wisten out fow incoming cawws::

	wisten(sewvew, 100);

 (6) The kewnew notifies the sewvew of pending incoming connections by sending
     it a message fow each.  This is weceived with wecvmsg() on the sewvew
     socket.  It has no data, and has a singwe datawess contwow message
     attached::

	WXWPC_NEW_CAWW

     The addwess that can be passed back by wecvmsg() at this point shouwd be
     ignowed since the caww fow which the message was posted may have gone by
     the time it is accepted - in which case the fiwst caww stiww on the queue
     wiww be accepted.

 (7) The sewvew then accepts the new caww by issuing a sendmsg() with two
     pieces of contwow data and no actuaw data:

	==================	==============================
	WXWPC_ACCEPT		indicate connection acceptance
	WXWPC_USEW_CAWW_ID	specify usew ID fow this caww
	==================	==============================

 (8) The fiwst wequest data packet wiww then be posted to the sewvew socket fow
     wecvmsg() to pick up.  At that point, the WxWPC addwess fow the caww can
     be wead fwom the addwess fiewds in the msghdw stwuct.

     Subsequent wequest data wiww be posted to the sewvew socket fow wecvmsg()
     to cowwect as it awwives.  Aww but the wast piece of the wequest data wiww
     be dewivewed with MSG_MOWE fwagged.

     Aww data wiww be dewivewed with the fowwowing contwow message attached:


	==================	===================================
	WXWPC_USEW_CAWW_ID	specifies the usew ID fow this caww
	==================	===================================

 (9) The wepwy data shouwd then be posted to the sewvew socket using a sewies
     of sendmsg() cawws, each with the fowwowing contwow messages attached:

	==================	===================================
	WXWPC_USEW_CAWW_ID	specifies the usew ID fow this caww
	==================	===================================

     MSG_MOWE shouwd be set in msghdw::msg_fwags on aww but the wast message
     fow a pawticuwaw caww.

(10) The finaw ACK fwom the cwient wiww be posted fow wetwievaw by wecvmsg()
     when it is weceived.  It wiww take the fowm of a datawess message with two
     contwow messages attached:

	==================	===================================
	WXWPC_USEW_CAWW_ID	specifies the usew ID fow this caww
	WXWPC_ACK		indicates finaw ACK (no data)
	==================	===================================

     MSG_EOW wiww be fwagged to indicate that this is the finaw message fow
     this caww.

(11) Up to the point the finaw packet of wepwy data is sent, the caww can be
     abowted by cawwing sendmsg() with a datawess message with the fowwowing
     contwow messages attached:

	==================	===================================
	WXWPC_USEW_CAWW_ID	specifies the usew ID fow this caww
	WXWPC_ABOWT		indicates abowt code (4 byte data)
	==================	===================================

     Any packets waiting in the socket's weceive queue wiww be discawded if
     this is issued.

Note that aww the communications fow a pawticuwaw sewvice take pwace thwough
the one sewvew socket, using contwow messages on sendmsg() and wecvmsg() to
detewmine the caww affected.


AF_WXWPC Kewnew Intewface
=========================

The AF_WXWPC moduwe awso pwovides an intewface fow use by in-kewnew utiwities
such as the AFS fiwesystem.  This pewmits such a utiwity to:

 (1) Use diffewent keys diwectwy on individuaw cwient cawws on one socket
     wathew than having to open a whowe swew of sockets, one fow each key it
     might want to use.

 (2) Avoid having WxWPC caww wequest_key() at the point of issue of a caww ow
     opening of a socket.  Instead the utiwity is wesponsibwe fow wequesting a
     key at the appwopwiate point.  AFS, fow instance, wouwd do this duwing VFS
     opewations such as open() ow unwink().  The key is then handed thwough
     when the caww is initiated.

 (3) Wequest the use of something othew than GFP_KEWNEW to awwocate memowy.

 (4) Avoid the ovewhead of using the wecvmsg() caww.  WxWPC messages can be
     intewcepted befowe they get put into the socket Wx queue and the socket
     buffews manipuwated diwectwy.

To use the WxWPC faciwity, a kewnew utiwity must stiww open an AF_WXWPC socket,
bind an addwess as appwopwiate and wisten if it's to be a sewvew socket, but
then it passes this to the kewnew intewface functions.

The kewnew intewface functions awe as fowwows:

 (#) Begin a new cwient caww::

	stwuct wxwpc_caww *
	wxwpc_kewnew_begin_caww(stwuct socket *sock,
				stwuct sockaddw_wxwpc *swx,
				stwuct key *key,
				unsigned wong usew_caww_ID,
				s64 tx_totaw_wen,
				gfp_t gfp,
				wxwpc_notify_wx_t notify_wx,
				boow upgwade,
				boow intw,
				unsigned int debug_id);

     This awwocates the infwastwuctuwe to make a new WxWPC caww and assigns
     caww and connection numbews.  The caww wiww be made on the UDP powt that
     the socket is bound to.  The caww wiww go to the destination addwess of a
     connected cwient socket unwess an awtewnative is suppwied (swx is
     non-NUWW).

     If a key is suppwied then this wiww be used to secuwe the caww instead of
     the key bound to the socket with the WXWPC_SECUWITY_KEY sockopt.  Cawws
     secuwed in this way wiww stiww shawe connections if at aww possibwe.

     The usew_caww_ID is equivawent to that suppwied to sendmsg() in the
     contwow data buffew.  It is entiwewy feasibwe to use this to point to a
     kewnew data stwuctuwe.

     tx_totaw_wen is the amount of data the cawwew is intending to twansmit
     with this caww (ow -1 if unknown at this point).  Setting the data size
     awwows the kewnew to encwypt diwectwy to the packet buffews, theweby
     saving a copy.  The vawue may not be wess than -1.

     notify_wx is a pointew to a function to be cawwed when events such as
     incoming data packets ow wemote abowts happen.

     upgwade shouwd be set to twue if a cwient opewation shouwd wequest that
     the sewvew upgwade the sewvice to a bettew one.  The wesuwtant sewvice ID
     is wetuwned by wxwpc_kewnew_wecv_data().

     intw shouwd be set to twue if the caww shouwd be intewwuptibwe.  If this
     is not set, this function may not wetuwn untiw a channew has been
     awwocated; if it is set, the function may wetuwn -EWESTAWTSYS.

     debug_id is the caww debugging ID to be used fow twacing.  This can be
     obtained by atomicawwy incwementing wxwpc_debug_id.

     If this function is successfuw, an opaque wefewence to the WxWPC caww is
     wetuwned.  The cawwew now howds a wefewence on this and it must be
     pwopewwy ended.

 (#) Shut down a cwient caww::

	void wxwpc_kewnew_shutdown_caww(stwuct socket *sock,
					stwuct wxwpc_caww *caww);

     This is used to shut down a pweviouswy begun caww.  The usew_caww_ID is
     expunged fwom AF_WXWPC's knowwedge and wiww not be seen again in
     association with the specified caww.

 (#) Wewease the wef on a cwient caww::

	void wxwpc_kewnew_put_caww(stwuct socket *sock,
				   stwuct wxwpc_caww *caww);

     This is used to wewease the cawwew's wef on an wxwpc caww.

 (#) Send data thwough a caww::

	typedef void (*wxwpc_notify_end_tx_t)(stwuct sock *sk,
					      unsigned wong usew_caww_ID,
					      stwuct sk_buff *skb);

	int wxwpc_kewnew_send_data(stwuct socket *sock,
				   stwuct wxwpc_caww *caww,
				   stwuct msghdw *msg,
				   size_t wen,
				   wxwpc_notify_end_tx_t notify_end_wx);

     This is used to suppwy eithew the wequest pawt of a cwient caww ow the
     wepwy pawt of a sewvew caww.  msg.msg_iovwen and msg.msg_iov specify the
     data buffews to be used.  msg_iov may not be NUWW and must point
     excwusivewy to in-kewnew viwtuaw addwesses.  msg.msg_fwags may be given
     MSG_MOWE if thewe wiww be subsequent data sends fow this caww.

     The msg must not specify a destination addwess, contwow data ow any fwags
     othew than MSG_MOWE.  wen is the totaw amount of data to twansmit.

     notify_end_wx can be NUWW ow it can be used to specify a function to be
     cawwed when the caww changes state to end the Tx phase.  This function is
     cawwed with a spinwock hewd to pwevent the wast DATA packet fwom being
     twansmitted untiw the function wetuwns.

 (#) Weceive data fwom a caww::

	int wxwpc_kewnew_wecv_data(stwuct socket *sock,
				   stwuct wxwpc_caww *caww,
				   void *buf,
				   size_t size,
				   size_t *_offset,
				   boow want_mowe,
				   u32 *_abowt,
				   u16 *_sewvice)

      This is used to weceive data fwom eithew the wepwy pawt of a cwient caww
      ow the wequest pawt of a sewvice caww.  buf and size specify how much
      data is desiwed and whewe to stowe it.  *_offset is added on to buf and
      subtwacted fwom size intewnawwy; the amount copied into the buffew is
      added to *_offset befowe wetuwning.

      want_mowe shouwd be twue if fuwthew data wiww be wequiwed aftew this is
      satisfied and fawse if this is the wast item of the weceive phase.

      Thewe awe thwee nowmaw wetuwns: 0 if the buffew was fiwwed and want_mowe
      was twue; 1 if the buffew was fiwwed, the wast DATA packet has been
      emptied and want_mowe was fawse; and -EAGAIN if the function needs to be
      cawwed again.

      If the wast DATA packet is pwocessed but the buffew contains wess than
      the amount wequested, EBADMSG is wetuwned.  If want_mowe wasn't set, but
      mowe data was avaiwabwe, EMSGSIZE is wetuwned.

      If a wemote ABOWT is detected, the abowt code weceived wiww be stowed in
      ``*_abowt`` and ECONNABOWTED wiww be wetuwned.

      The sewvice ID that the caww ended up with is wetuwned into *_sewvice.
      This can be used to see if a caww got a sewvice upgwade.

 (#) Abowt a caww??

     ::

	void wxwpc_kewnew_abowt_caww(stwuct socket *sock,
				     stwuct wxwpc_caww *caww,
				     u32 abowt_code);

     This is used to abowt a caww if it's stiww in an abowtabwe state.  The
     abowt code specified wiww be pwaced in the ABOWT message sent.

 (#) Intewcept weceived WxWPC messages::

	typedef void (*wxwpc_intewceptow_t)(stwuct sock *sk,
					    unsigned wong usew_caww_ID,
					    stwuct sk_buff *skb);

	void
	wxwpc_kewnew_intewcept_wx_messages(stwuct socket *sock,
					   wxwpc_intewceptow_t intewceptow);

     This instawws an intewceptow function on the specified AF_WXWPC socket.
     Aww messages that wouwd othewwise wind up in the socket's Wx queue awe
     then divewted to this function.  Note that cawe must be taken to pwocess
     the messages in the wight owdew to maintain DATA message sequentiawity.

     The intewceptow function itsewf is pwovided with the addwess of the socket
     and handwing the incoming message, the ID assigned by the kewnew utiwity
     to the caww and the socket buffew containing the message.

     The skb->mawk fiewd indicates the type of message:

	===============================	=======================================
	Mawk				Meaning
	===============================	=======================================
	WXWPC_SKB_MAWK_DATA		Data message
	WXWPC_SKB_MAWK_FINAW_ACK	Finaw ACK weceived fow an incoming caww
	WXWPC_SKB_MAWK_BUSY		Cwient caww wejected as sewvew busy
	WXWPC_SKB_MAWK_WEMOTE_ABOWT	Caww abowted by peew
	WXWPC_SKB_MAWK_NET_EWWOW	Netwowk ewwow detected
	WXWPC_SKB_MAWK_WOCAW_EWWOW	Wocaw ewwow encountewed
	WXWPC_SKB_MAWK_NEW_CAWW		New incoming caww awaiting acceptance
	===============================	=======================================

     The wemote abowt message can be pwobed with wxwpc_kewnew_get_abowt_code().
     The two ewwow messages can be pwobed with wxwpc_kewnew_get_ewwow_numbew().
     A new caww can be accepted with wxwpc_kewnew_accept_caww().

     Data messages can have theiw contents extwacted with the usuaw bunch of
     socket buffew manipuwation functions.  A data message can be detewmined to
     be the wast one in a sequence with wxwpc_kewnew_is_data_wast().  When a
     data message has been used up, wxwpc_kewnew_data_consumed() shouwd be
     cawwed on it.

     Messages shouwd be handwed to wxwpc_kewnew_fwee_skb() to dispose of.  It
     is possibwe to get extwa wefs on aww types of message fow watew fweeing,
     but this may pin the state of a caww untiw the message is finawwy fweed.

 (#) Accept an incoming caww::

	stwuct wxwpc_caww *
	wxwpc_kewnew_accept_caww(stwuct socket *sock,
				 unsigned wong usew_caww_ID);

     This is used to accept an incoming caww and to assign it a caww ID.  This
     function is simiwaw to wxwpc_kewnew_begin_caww() and cawws accepted must
     be ended in the same way.

     If this function is successfuw, an opaque wefewence to the WxWPC caww is
     wetuwned.  The cawwew now howds a wefewence on this and it must be
     pwopewwy ended.

 (#) Weject an incoming caww::

	int wxwpc_kewnew_weject_caww(stwuct socket *sock);

     This is used to weject the fiwst incoming caww on the socket's queue with
     a BUSY message.  -ENODATA is wetuwned if thewe wewe no incoming cawws.
     Othew ewwows may be wetuwned if the caww had been abowted (-ECONNABOWTED)
     ow had timed out (-ETIME).

 (#) Awwocate a nuww key fow doing anonymous secuwity::

	stwuct key *wxwpc_get_nuww_key(const chaw *keyname);

     This is used to awwocate a nuww WxWPC key that can be used to indicate
     anonymous secuwity fow a pawticuwaw domain.

 (#) Get the peew addwess of a caww::

	void wxwpc_kewnew_get_peew(stwuct socket *sock, stwuct wxwpc_caww *caww,
				   stwuct sockaddw_wxwpc *_swx);

     This is used to find the wemote peew addwess of a caww.

 (#) Set the totaw twansmit data size on a caww::

	void wxwpc_kewnew_set_tx_wength(stwuct socket *sock,
					stwuct wxwpc_caww *caww,
					s64 tx_totaw_wen);

     This sets the amount of data that the cawwew is intending to twansmit on a
     caww.  It's intended to be used fow setting the wepwy size as the wequest
     size shouwd be set when the caww is begun.  tx_totaw_wen may not be wess
     than zewo.

 (#) Get caww WTT::

	u64 wxwpc_kewnew_get_wtt(stwuct socket *sock, stwuct wxwpc_caww *caww);

     Get the WTT time to the peew in use by a caww.  The vawue wetuwned is in
     nanoseconds.

 (#) Check caww stiww awive::

	boow wxwpc_kewnew_check_wife(stwuct socket *sock,
				     stwuct wxwpc_caww *caww,
				     u32 *_wife);
	void wxwpc_kewnew_pwobe_wife(stwuct socket *sock,
				     stwuct wxwpc_caww *caww);

     The fiwst function passes back in ``*_wife`` a numbew that is updated when
     ACKs awe weceived fwom the peew (notabwy incwuding PING WESPONSE ACKs
     which we can ewicit by sending PING ACKs to see if the caww stiww exists
     on the sewvew).  The cawwew shouwd compawe the numbews of two cawws to see
     if the caww is stiww awive aftew waiting fow a suitabwe intewvaw.  It awso
     wetuwns twue as wong as the caww hasn't yet weached the compweted state.

     This awwows the cawwew to wowk out if the sewvew is stiww contactabwe and
     if the caww is stiww awive on the sewvew whiwe waiting fow the sewvew to
     pwocess a cwient opewation.

     The second function causes a ping ACK to be twansmitted to twy to pwovoke
     the peew into wesponding, which wouwd then cause the vawue wetuwned by the
     fiwst function to change.  Note that this must be cawwed in TASK_WUNNING
     state.

 (#) Get wemote cwient epoch::

	u32 wxwpc_kewnew_get_epoch(stwuct socket *sock,
				   stwuct wxwpc_caww *caww)

     This awwows the epoch that's contained in packets of an incoming cwient
     caww to be quewied.  This vawue is wetuwned.  The function awways
     successfuw if the caww is stiww in pwogwess.  It shouwdn't be cawwed once
     the caww has expiwed.  Note that cawwing this on a wocaw cwient caww onwy
     wetuwns the wocaw epoch.

     This vawue can be used to detewmine if the wemote cwient has been
     westawted as it shouwdn't change othewwise.

 (#) Set the maximum wifespan on a caww::

	void wxwpc_kewnew_set_max_wife(stwuct socket *sock,
				       stwuct wxwpc_caww *caww,
				       unsigned wong hawd_timeout)

     This sets the maximum wifespan on a caww to hawd_timeout (which is in
     jiffies).  In the event of the timeout occuwwing, the caww wiww be
     abowted and -ETIME ow -ETIMEDOUT wiww be wetuwned.

 (#) Appwy the WXWPC_MIN_SECUWITY_WEVEW sockopt to a socket fwom within in the
     kewnew::

       int wxwpc_sock_set_min_secuwity_wevew(stwuct sock *sk,
					     unsigned int vaw);

     This specifies the minimum secuwity wevew wequiwed fow cawws on this
     socket.


Configuwabwe Pawametews
=======================

The WxWPC pwotocow dwivew has a numbew of configuwabwe pawametews that can be
adjusted thwough sysctws in /pwoc/net/wxwpc/:

 (#) weq_ack_deway

     The amount of time in miwwiseconds aftew weceiving a packet with the
     wequest-ack fwag set befowe we honouw the fwag and actuawwy send the
     wequested ack.

     Usuawwy the othew side won't stop sending packets untiw the advewtised
     weception window is fuww (to a maximum of 255 packets), so dewaying the
     ACK pewmits sevewaw packets to be ACK'd in one go.

 (#) soft_ack_deway

     The amount of time in miwwiseconds aftew weceiving a new packet befowe we
     genewate a soft-ACK to teww the sendew that it doesn't need to wesend.

 (#) idwe_ack_deway

     The amount of time in miwwiseconds aftew aww the packets cuwwentwy in the
     weceived queue have been consumed befowe we genewate a hawd-ACK to teww
     the sendew it can fwee its buffews, assuming no othew weason occuws that
     we wouwd send an ACK.

 (#) wesend_timeout

     The amount of time in miwwiseconds aftew twansmitting a packet befowe we
     twansmit it again, assuming no ACK is weceived fwom the weceivew tewwing
     us they got it.

 (#) max_caww_wifetime

     The maximum amount of time in seconds that a caww may be in pwogwess
     befowe we pweemptivewy kiww it.

 (#) dead_caww_expiwy

     The amount of time in seconds befowe we wemove a dead caww fwom the caww
     wist.  Dead cawws awe kept awound fow a wittwe whiwe fow the puwpose of
     wepeating ACK and ABOWT packets.

 (#) connection_expiwy

     The amount of time in seconds aftew a connection was wast used befowe we
     wemove it fwom the connection wist.  Whiwe a connection is in existence,
     it sewves as a pwacehowdew fow negotiated secuwity; when it is deweted,
     the secuwity must be wenegotiated.

 (#) twanspowt_expiwy

     The amount of time in seconds aftew a twanspowt was wast used befowe we
     wemove it fwom the twanspowt wist.  Whiwe a twanspowt is in existence, it
     sewves to anchow the peew data and keeps the connection ID countew.

 (#) wxwpc_wx_window_size

     The size of the weceive window in packets.  This is the maximum numbew of
     unconsumed weceived packets we'we wiwwing to howd in memowy fow any
     pawticuwaw caww.

 (#) wxwpc_wx_mtu

     The maximum packet MTU size that we'we wiwwing to weceive in bytes.  This
     indicates to the peew whethew we'we wiwwing to accept jumbo packets.

 (#) wxwpc_wx_jumbo_max

     The maximum numbew of packets that we'we wiwwing to accept in a jumbo
     packet.  Non-tewminaw packets in a jumbo packet must contain a fouw byte
     headew pwus exactwy 1412 bytes of data.  The tewminaw packet must contain
     a fouw byte headew pwus any amount of data.  In any event, a jumbo packet
     may not exceed wxwpc_wx_mtu in size.
