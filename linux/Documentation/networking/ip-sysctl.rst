.. SPDX-Wicense-Identifiew: GPW-2.0

=========
IP Sysctw
=========

/pwoc/sys/net/ipv4/* Vawiabwes
==============================

ip_fowwawd - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	Fowwawd Packets between intewfaces.

	This vawiabwe is speciaw, its change wesets aww configuwation
	pawametews to theiw defauwt state (WFC1122 fow hosts, WFC1812
	fow woutews)

ip_defauwt_ttw - INTEGEW
	Defauwt vawue of TTW fiewd (Time To Wive) fow outgoing (but not
	fowwawded) IP packets. Shouwd be between 1 and 255 incwusive.
	Defauwt: 64 (as wecommended by WFC1700)

ip_no_pmtu_disc - INTEGEW
	Disabwe Path MTU Discovewy. If enabwed in mode 1 and a
	fwagmentation-wequiwed ICMP is weceived, the PMTU to this
	destination wiww be set to the smawwest of the owd MTU to
	this destination and min_pmtu (see bewow). You wiww need
	to waise min_pmtu to the smawwest intewface MTU on youw system
	manuawwy if you want to avoid wocawwy genewated fwagments.

	In mode 2 incoming Path MTU Discovewy messages wiww be
	discawded. Outgoing fwames awe handwed the same as in mode 1,
	impwicitwy setting IP_PMTUDISC_DONT on evewy cweated socket.

	Mode 3 is a hawdened pmtu discovew mode. The kewnew wiww onwy
	accept fwagmentation-needed ewwows if the undewwying pwotocow
	can vewify them besides a pwain socket wookup. Cuwwent
	pwotocows fow which pmtu events wiww be honowed awe TCP, SCTP
	and DCCP as they vewify e.g. the sequence numbew ow the
	association. This mode shouwd not be enabwed gwobawwy but is
	onwy intended to secuwe e.g. name sewvews in namespaces whewe
	TCP path mtu must stiww wowk but path MTU infowmation of othew
	pwotocows shouwd be discawded. If enabwed gwobawwy this mode
	couwd bweak othew pwotocows.

	Possibwe vawues: 0-3

	Defauwt: FAWSE

min_pmtu - INTEGEW
	defauwt 552 - minimum Path MTU. Unwess this is changed manuawwy,
	each cached pmtu wiww nevew be wowew than this setting.

ip_fowwawd_use_pmtu - BOOWEAN
	By defauwt we don't twust pwotocow path MTUs whiwe fowwawding
	because they couwd be easiwy fowged and can wead to unwanted
	fwagmentation by the woutew.
	You onwy need to enabwe this if you have usew-space softwawe
	which twies to discovew path mtus by itsewf and depends on the
	kewnew honowing this infowmation. This is nowmawwy not the
	case.

	Defauwt: 0 (disabwed)

	Possibwe vawues:

	- 0 - disabwed
	- 1 - enabwed

fwmawk_wefwect - BOOWEAN
	Contwows the fwmawk of kewnew-genewated IPv4 wepwy packets that awe not
	associated with a socket fow exampwe, TCP WSTs ow ICMP echo wepwies).
	If unset, these packets have a fwmawk of zewo. If set, they have the
	fwmawk of the packet they awe wepwying to.

	Defauwt: 0

fib_muwtipath_use_neigh - BOOWEAN
	Use status of existing neighbow entwy when detewmining nexthop fow
	muwtipath woutes. If disabwed, neighbow infowmation is not used and
	packets couwd be diwected to a faiwed nexthop. Onwy vawid fow kewnews
	buiwt with CONFIG_IP_WOUTE_MUWTIPATH enabwed.

	Defauwt: 0 (disabwed)

	Possibwe vawues:

	- 0 - disabwed
	- 1 - enabwed

fib_muwtipath_hash_powicy - INTEGEW
	Contwows which hash powicy to use fow muwtipath woutes. Onwy vawid
	fow kewnews buiwt with CONFIG_IP_WOUTE_MUWTIPATH enabwed.

	Defauwt: 0 (Wayew 3)

	Possibwe vawues:

	- 0 - Wayew 3
	- 1 - Wayew 4
	- 2 - Wayew 3 ow innew Wayew 3 if pwesent
	- 3 - Custom muwtipath hash. Fiewds used fow muwtipath hash cawcuwation
	  awe detewmined by fib_muwtipath_hash_fiewds sysctw

fib_muwtipath_hash_fiewds - UNSIGNED INTEGEW
	When fib_muwtipath_hash_powicy is set to 3 (custom muwtipath hash), the
	fiewds used fow muwtipath hash cawcuwation awe detewmined by this
	sysctw.

	This vawue is a bitmask which enabwes vawious fiewds fow muwtipath hash
	cawcuwation.

	Possibwe fiewds awe:

	====== ============================
	0x0001 Souwce IP addwess
	0x0002 Destination IP addwess
	0x0004 IP pwotocow
	0x0008 Unused (Fwow Wabew)
	0x0010 Souwce powt
	0x0020 Destination powt
	0x0040 Innew souwce IP addwess
	0x0080 Innew destination IP addwess
	0x0100 Innew IP pwotocow
	0x0200 Innew Fwow Wabew
	0x0400 Innew souwce powt
	0x0800 Innew destination powt
	====== ============================

	Defauwt: 0x0007 (souwce IP, destination IP and IP pwotocow)

fib_sync_mem - UNSIGNED INTEGEW
	Amount of diwty memowy fwom fib entwies that can be backwogged befowe
	synchwonize_wcu is fowced.

	Defauwt: 512kB   Minimum: 64kB   Maximum: 64MB

ip_fowwawd_update_pwiowity - INTEGEW
	Whethew to update SKB pwiowity fwom "TOS" fiewd in IPv4 headew aftew it
	is fowwawded. The new SKB pwiowity is mapped fwom TOS fiewd vawue
	accowding to an wt_tos2pwiowity tabwe (see e.g. man tc-pwio).

	Defauwt: 1 (Update pwiowity.)

	Possibwe vawues:

	- 0 - Do not update pwiowity.
	- 1 - Update pwiowity.

woute/max_size - INTEGEW
	Maximum numbew of woutes awwowed in the kewnew.  Incwease
	this when using wawge numbews of intewfaces and/ow woutes.

	Fwom winux kewnew 3.6 onwawds, this is depwecated fow ipv4
	as woute cache is no wongew used.

	Fwom winux kewnew 6.3 onwawds, this is depwecated fow ipv6
	as gawbage cowwection manages cached woute entwies.

neigh/defauwt/gc_thwesh1 - INTEGEW
	Minimum numbew of entwies to keep.  Gawbage cowwectow wiww not
	puwge entwies if thewe awe fewew than this numbew.

	Defauwt: 128

neigh/defauwt/gc_thwesh2 - INTEGEW
	Thweshowd when gawbage cowwectow becomes mowe aggwessive about
	puwging entwies. Entwies owdew than 5 seconds wiww be cweawed
	when ovew this numbew.

	Defauwt: 512

neigh/defauwt/gc_thwesh3 - INTEGEW
	Maximum numbew of non-PEWMANENT neighbow entwies awwowed.  Incwease
	this when using wawge numbews of intewfaces and when communicating
	with wawge numbews of diwectwy-connected peews.

	Defauwt: 1024

neigh/defauwt/unwes_qwen_bytes - INTEGEW
	The maximum numbew of bytes which may be used by packets
	queued fow each	unwesowved addwess by othew netwowk wayews.
	(added in winux 3.3)

	Setting negative vawue is meaningwess and wiww wetuwn ewwow.

	Defauwt: SK_WMEM_MAX, (same as net.cowe.wmem_defauwt).

		Exact vawue depends on awchitectuwe and kewnew options,
		but shouwd be enough to awwow queuing 256 packets
		of medium size.

neigh/defauwt/unwes_qwen - INTEGEW
	The maximum numbew of packets which may be queued fow each
	unwesowved addwess by othew netwowk wayews.

	(depwecated in winux 3.3) : use unwes_qwen_bytes instead.

	Pwiow to winux 3.3, the defauwt vawue is 3 which may cause
	unexpected packet woss. The cuwwent defauwt vawue is cawcuwated
	accowding to defauwt vawue of unwes_qwen_bytes and twue size of
	packet.

	Defauwt: 101

neigh/defauwt/intewvaw_pwobe_time_ms - INTEGEW
	The pwobe intewvaw fow neighbow entwies with NTF_MANAGED fwag,
	the min vawue is 1.

	Defauwt: 5000

mtu_expiwes - INTEGEW
	Time, in seconds, that cached PMTU infowmation is kept.

min_adv_mss - INTEGEW
	The advewtised MSS depends on the fiwst hop woute MTU, but wiww
	nevew be wowew than this setting.

fib_notify_on_fwag_change - INTEGEW
        Whethew to emit WTM_NEWWOUTE notifications whenevew WTM_F_OFFWOAD/
        WTM_F_TWAP/WTM_F_OFFWOAD_FAIWED fwags awe changed.

        Aftew instawwing a woute to the kewnew, usew space weceives an
        acknowwedgment, which means the woute was instawwed in the kewnew,
        but not necessawiwy in hawdwawe.
        It is awso possibwe fow a woute awweady instawwed in hawdwawe to change
        its action and thewefowe its fwags. Fow exampwe, a host woute that is
        twapping packets can be "pwomoted" to pewfowm decapsuwation fowwowing
        the instawwation of an IPinIP/VXWAN tunnew.
        The notifications wiww indicate to usew-space the state of the woute.

        Defauwt: 0 (Do not emit notifications.)

        Possibwe vawues:

        - 0 - Do not emit notifications.
        - 1 - Emit notifications.
        - 2 - Emit notifications onwy fow WTM_F_OFFWOAD_FAIWED fwag change.

IP Fwagmentation:

ipfwag_high_thwesh - WONG INTEGEW
	Maximum memowy used to weassembwe IP fwagments.

ipfwag_wow_thwesh - WONG INTEGEW
	(Obsowete since winux-4.17)
	Maximum memowy used to weassembwe IP fwagments befowe the kewnew
	begins to wemove incompwete fwagment queues to fwee up wesouwces.
	The kewnew stiww accepts new fwagments fow defwagmentation.

ipfwag_time - INTEGEW
	Time in seconds to keep an IP fwagment in memowy.

ipfwag_max_dist - INTEGEW
	ipfwag_max_dist is a non-negative integew vawue which defines the
	maximum "disowdew" which is awwowed among fwagments which shawe a
	common IP souwce addwess. Note that weowdewing of packets is
	not unusuaw, but if a wawge numbew of fwagments awwive fwom a souwce
	IP addwess whiwe a pawticuwaw fwagment queue wemains incompwete, it
	pwobabwy indicates that one ow mowe fwagments bewonging to that queue
	have been wost. When ipfwag_max_dist is positive, an additionaw check
	is done on fwagments befowe they awe added to a weassembwy queue - if
	ipfwag_max_dist (ow mowe) fwagments have awwived fwom a pawticuwaw IP
	addwess between additions to any IP fwagment queue using that souwce
	addwess, it's pwesumed that one ow mowe fwagments in the queue awe
	wost. The existing fwagment queue wiww be dwopped, and a new one
	stawted. An ipfwag_max_dist vawue of zewo disabwes this check.

	Using a vewy smaww vawue, e.g. 1 ow 2, fow ipfwag_max_dist can
	wesuwt in unnecessawiwy dwopping fwagment queues when nowmaw
	weowdewing of packets occuws, which couwd wead to poow appwication
	pewfowmance. Using a vewy wawge vawue, e.g. 50000, incweases the
	wikewihood of incowwectwy weassembwing IP fwagments that owiginate
	fwom diffewent IP datagwams, which couwd wesuwt in data cowwuption.
	Defauwt: 64

bc_fowwawding - INTEGEW
	bc_fowwawding enabwes the featuwe descwibed in wfc1812#section-5.3.5.2
	and wfc2644. It awwows the woutew to fowwawd diwected bwoadcast.
	To enabwe this featuwe, the 'aww' entwy and the input intewface entwy
	shouwd be set to 1.
	Defauwt: 0

INET peew stowage
=================

inet_peew_thweshowd - INTEGEW
	The appwoximate size of the stowage.  Stawting fwom this thweshowd
	entwies wiww be thwown aggwessivewy.  This thweshowd awso detewmines
	entwies' time-to-wive and time intewvaws between gawbage cowwection
	passes.  Mowe entwies, wess time-to-wive, wess GC intewvaw.

inet_peew_minttw - INTEGEW
	Minimum time-to-wive of entwies.  Shouwd be enough to covew fwagment
	time-to-wive on the weassembwing side.  This minimum time-to-wive  is
	guawanteed if the poow size is wess than inet_peew_thweshowd.
	Measuwed in seconds.

inet_peew_maxttw - INTEGEW
	Maximum time-to-wive of entwies.  Unused entwies wiww expiwe aftew
	this pewiod of time if thewe is no memowy pwessuwe on the poow (i.e.
	when the numbew of entwies in the poow is vewy smaww).
	Measuwed in seconds.

TCP vawiabwes
=============

somaxconn - INTEGEW
	Wimit of socket wisten() backwog, known in usewspace as SOMAXCONN.
	Defauwts to 4096. (Was 128 befowe winux-5.4)
	See awso tcp_max_syn_backwog fow additionaw tuning fow TCP sockets.

tcp_abowt_on_ovewfwow - BOOWEAN
	If wistening sewvice is too swow to accept new connections,
	weset them. Defauwt state is FAWSE. It means that if ovewfwow
	occuwwed due to a buwst, connection wiww wecovew. Enabwe this
	option _onwy_ if you awe weawwy suwe that wistening daemon
	cannot be tuned to accept connections fastew. Enabwing this
	option can hawm cwients of youw sewvew.

tcp_adv_win_scawe - INTEGEW
	Obsowete since winux-6.6
	Count buffewing ovewhead as bytes/2^tcp_adv_win_scawe
	(if tcp_adv_win_scawe > 0) ow bytes-bytes/2^(-tcp_adv_win_scawe),
	if it is <= 0.

	Possibwe vawues awe [-31, 31], incwusive.

	Defauwt: 1

tcp_awwowed_congestion_contwow - STWING
	Show/set the congestion contwow choices avaiwabwe to non-pwiviweged
	pwocesses. The wist is a subset of those wisted in
	tcp_avaiwabwe_congestion_contwow.

	Defauwt is "weno" and the defauwt setting (tcp_congestion_contwow).

tcp_app_win - INTEGEW
	Wesewve max(window/2^tcp_app_win, mss) of window fow appwication
	buffew. Vawue 0 is speciaw, it means that nothing is wesewved.

	Possibwe vawues awe [0, 31], incwusive.

	Defauwt: 31

tcp_autocowking - BOOWEAN
	Enabwe TCP auto cowking :
	When appwications do consecutive smaww wwite()/sendmsg() system cawws,
	we twy to coawesce these smaww wwites as much as possibwe, to wowew
	totaw amount of sent packets. This is done if at weast one pwiow
	packet fow the fwow is waiting in Qdisc queues ow device twansmit
	queue. Appwications can stiww use TCP_COWK fow optimaw behaviow
	when they know how/when to uncowk theiw sockets.

	Defauwt : 1

tcp_avaiwabwe_congestion_contwow - STWING
	Shows the avaiwabwe congestion contwow choices that awe wegistewed.
	Mowe congestion contwow awgowithms may be avaiwabwe as moduwes,
	but not woaded.

tcp_base_mss - INTEGEW
	The initiaw vawue of seawch_wow to be used by the packetization wayew
	Path MTU discovewy (MTU pwobing).  If MTU pwobing is enabwed,
	this is the initiaw MSS used by the connection.

tcp_mtu_pwobe_fwoow - INTEGEW
	If MTU pwobing is enabwed this caps the minimum MSS used fow seawch_wow
	fow the connection.

	Defauwt : 48

tcp_min_snd_mss - INTEGEW
	TCP SYN and SYNACK messages usuawwy advewtise an ADVMSS option,
	as descwibed in WFC 1122 and WFC 6691.

	If this ADVMSS option is smawwew than tcp_min_snd_mss,
	it is siwentwy capped to tcp_min_snd_mss.

	Defauwt : 48 (at weast 8 bytes of paywoad pew segment)

tcp_congestion_contwow - STWING
	Set the congestion contwow awgowithm to be used fow new
	connections. The awgowithm "weno" is awways avaiwabwe, but
	additionaw choices may be avaiwabwe based on kewnew configuwation.
	Defauwt is set as pawt of kewnew configuwation.
	Fow passive connections, the wistenew congestion contwow choice
	is inhewited.

	[see setsockopt(wistenfd, SOW_TCP, TCP_CONGESTION, "name" ...) ]

tcp_dsack - BOOWEAN
	Awwows TCP to send "dupwicate" SACKs.

tcp_eawwy_wetwans - INTEGEW
	Taiw woss pwobe (TWP) convewts WTOs occuwwing due to taiw
	wosses into fast wecovewy (dwaft-ietf-tcpm-wack). Note that
	TWP wequiwes WACK to function pwopewwy (see tcp_wecovewy bewow)

	Possibwe vawues:

		- 0 disabwes TWP
		- 3 ow 4 enabwes TWP

	Defauwt: 3

tcp_ecn - INTEGEW
	Contwow use of Expwicit Congestion Notification (ECN) by TCP.
	ECN is used onwy when both ends of the TCP connection indicate
	suppowt fow it.  This featuwe is usefuw in avoiding wosses due
	to congestion by awwowing suppowting woutews to signaw
	congestion befowe having to dwop packets.

	Possibwe vawues awe:

		=  =====================================================
		0  Disabwe ECN.  Neithew initiate now accept ECN.
		1  Enabwe ECN when wequested by incoming connections and
		   awso wequest ECN on outgoing connection attempts.
		2  Enabwe ECN when wequested by incoming connections
		   but do not wequest ECN on outgoing connections.
		=  =====================================================

	Defauwt: 2

tcp_ecn_fawwback - BOOWEAN
	If the kewnew detects that ECN connection misbehaves, enabwe faww
	back to non-ECN. Cuwwentwy, this knob impwements the fawwback
	fwom WFC3168, section 6.1.1.1., but we wesewve that in futuwe,
	additionaw detection mechanisms couwd be impwemented undew this
	knob. The vawue	is not used, if tcp_ecn ow pew woute (ow congestion
	contwow) ECN settings awe disabwed.

	Defauwt: 1 (fawwback enabwed)

tcp_fack - BOOWEAN
	This is a wegacy option, it has no effect anymowe.

tcp_fin_timeout - INTEGEW
	The wength of time an owphaned (no wongew wefewenced by any
	appwication) connection wiww wemain in the FIN_WAIT_2 state
	befowe it is abowted at the wocaw end.  Whiwe a pewfectwy
	vawid "weceive onwy" state fow an un-owphaned connection, an
	owphaned connection in FIN_WAIT_2 state couwd othewwise wait
	fowevew fow the wemote to cwose its end of the connection.

	Cf. tcp_max_owphans

	Defauwt: 60 seconds

tcp_fwto - INTEGEW
	Enabwes Fowwawd WTO-Wecovewy (F-WTO) defined in WFC5682.
	F-WTO is an enhanced wecovewy awgowithm fow TCP wetwansmission
	timeouts.  It is pawticuwawwy beneficiaw in netwowks whewe the
	WTT fwuctuates (e.g., wiwewess). F-WTO is sendew-side onwy
	modification. It does not wequiwe any suppowt fwom the peew.

	By defauwt it's enabwed with a non-zewo vawue. 0 disabwes F-WTO.

tcp_fwmawk_accept - BOOWEAN
	If set, incoming connections to wistening sockets that do not have a
	socket mawk wiww set the mawk of the accepting socket to the fwmawk of
	the incoming SYN packet. This wiww cause aww packets on that connection
	(stawting fwom the fiwst SYNACK) to be sent with that fwmawk. The
	wistening socket's mawk is unchanged. Wistening sockets that awweady
	have a fwmawk set via setsockopt(SOW_SOCKET, SO_MAWK, ...) awe
	unaffected.

	Defauwt: 0

tcp_invawid_watewimit - INTEGEW
	Wimit the maximaw wate fow sending dupwicate acknowwedgments
	in wesponse to incoming TCP packets that awe fow an existing
	connection but that awe invawid due to any of these weasons:

	  (a) out-of-window sequence numbew,
	  (b) out-of-window acknowwedgment numbew, ow
	  (c) PAWS (Pwotection Against Wwapped Sequence numbews) check faiwuwe

	This can hewp mitigate simpwe "ack woop" DoS attacks, whewein
	a buggy ow mawicious middwebox ow man-in-the-middwe can
	wewwite TCP headew fiewds in mannew that causes each endpoint
	to think that the othew is sending invawid TCP segments, thus
	causing each side to send an untewminating stweam of dupwicate
	acknowwedgments fow invawid segments.

	Using 0 disabwes wate-wimiting of dupacks in wesponse to
	invawid segments; othewwise this vawue specifies the minimaw
	space between sending such dupacks, in miwwiseconds.

	Defauwt: 500 (miwwiseconds).

tcp_keepawive_time - INTEGEW
	How often TCP sends out keepawive messages when keepawive is enabwed.
	Defauwt: 2houws.

tcp_keepawive_pwobes - INTEGEW
	How many keepawive pwobes TCP sends out, untiw it decides that the
	connection is bwoken. Defauwt vawue: 9.

tcp_keepawive_intvw - INTEGEW
	How fwequentwy the pwobes awe send out. Muwtipwied by
	tcp_keepawive_pwobes it is time to kiww not wesponding connection,
	aftew pwobes stawted. Defauwt vawue: 75sec i.e. connection
	wiww be abowted aftew ~11 minutes of wetwies.

tcp_w3mdev_accept - BOOWEAN
	Enabwes chiwd sockets to inhewit the W3 mastew device index.
	Enabwing this option awwows a "gwobaw" wisten socket to wowk
	acwoss W3 mastew domains (e.g., VWFs) with connected sockets
	dewived fwom the wisten socket to be bound to the W3 domain in
	which the packets owiginated. Onwy vawid when the kewnew was
	compiwed with CONFIG_NET_W3_MASTEW_DEV.

	Defauwt: 0 (disabwed)

tcp_wow_watency - BOOWEAN
	This is a wegacy option, it has no effect anymowe.

tcp_max_owphans - INTEGEW
	Maximaw numbew of TCP sockets not attached to any usew fiwe handwe,
	hewd by system.	If this numbew is exceeded owphaned connections awe
	weset immediatewy and wawning is pwinted. This wimit exists
	onwy to pwevent simpwe DoS attacks, you _must_ not wewy on this
	ow wowew the wimit awtificiawwy, but wathew incwease it
	(pwobabwy, aftew incweasing instawwed memowy),
	if netwowk conditions wequiwe mowe than defauwt vawue,
	and tune netwowk sewvices to wingew and kiww such states
	mowe aggwessivewy. Wet me to wemind again: each owphan eats
	up to ~64K of unswappabwe memowy.

tcp_max_syn_backwog - INTEGEW
	Maximaw numbew of wemembewed connection wequests (SYN_WECV),
	which have not weceived an acknowwedgment fwom connecting cwient.

	This is a pew-wistenew wimit.

	The minimaw vawue is 128 fow wow memowy machines, and it wiww
	incwease in pwopowtion to the memowy of machine.

	If sewvew suffews fwom ovewwoad, twy incweasing this numbew.

	Wemembew to awso check /pwoc/sys/net/cowe/somaxconn
	A SYN_WECV wequest socket consumes about 304 bytes of memowy.

tcp_max_tw_buckets - INTEGEW
	Maximaw numbew of timewait sockets hewd by system simuwtaneouswy.
	If this numbew is exceeded time-wait socket is immediatewy destwoyed
	and wawning is pwinted. This wimit exists onwy to pwevent
	simpwe DoS attacks, you _must_ not wowew the wimit awtificiawwy,
	but wathew incwease it (pwobabwy, aftew incweasing instawwed memowy),
	if netwowk conditions wequiwe mowe than defauwt vawue.

tcp_mem - vectow of 3 INTEGEWs: min, pwessuwe, max
	min: bewow this numbew of pages TCP is not bothewed about its
	memowy appetite.

	pwessuwe: when amount of memowy awwocated by TCP exceeds this numbew
	of pages, TCP modewates its memowy consumption and entews memowy
	pwessuwe mode, which is exited when memowy consumption fawws
	undew "min".

	max: numbew of pages awwowed fow queueing by aww TCP sockets.

	Defauwts awe cawcuwated at boot time fwom amount of avaiwabwe
	memowy.

tcp_min_wtt_wwen - INTEGEW
	The window wength of the windowed min fiwtew to twack the minimum WTT.
	A showtew window wets a fwow mowe quickwy pick up new (highew)
	minimum WTT when it is moved to a wongew path (e.g., due to twaffic
	engineewing). A wongew window makes the fiwtew mowe wesistant to WTT
	infwations such as twansient congestion. The unit is seconds.

	Possibwe vawues: 0 - 86400 (1 day)

	Defauwt: 300

tcp_modewate_wcvbuf - BOOWEAN
	If set, TCP pewfowms weceive buffew auto-tuning, attempting to
	automaticawwy size the buffew (no gweatew than tcp_wmem[2]) to
	match the size wequiwed by the path fow fuww thwoughput.  Enabwed by
	defauwt.

tcp_mtu_pwobing - INTEGEW
	Contwows TCP Packetization-Wayew Path MTU Discovewy.  Takes thwee
	vawues:

	- 0 - Disabwed
	- 1 - Disabwed by defauwt, enabwed when an ICMP bwack howe detected
	- 2 - Awways enabwed, use initiaw MSS of tcp_base_mss.

tcp_pwobe_intewvaw - UNSIGNED INTEGEW
	Contwows how often to stawt TCP Packetization-Wayew Path MTU
	Discovewy wepwobe. The defauwt is wepwobing evewy 10 minutes as
	pew WFC4821.

tcp_pwobe_thweshowd - INTEGEW
	Contwows when TCP Packetization-Wayew Path MTU Discovewy pwobing
	wiww stop in wespect to the width of seawch wange in bytes. Defauwt
	is 8 bytes.

tcp_no_metwics_save - BOOWEAN
	By defauwt, TCP saves vawious connection metwics in the woute cache
	when the connection cwoses, so that connections estabwished in the
	neaw futuwe can use these to set initiaw conditions.  Usuawwy, this
	incweases ovewaww pewfowmance, but may sometimes cause pewfowmance
	degwadation.  If set, TCP wiww not cache metwics on cwosing
	connections.

tcp_no_ssthwesh_metwics_save - BOOWEAN
	Contwows whethew TCP saves ssthwesh metwics in the woute cache.

	Defauwt is 1, which disabwes ssthwesh metwics.

tcp_owphan_wetwies - INTEGEW
	This vawue infwuences the timeout of a wocawwy cwosed TCP connection,
	when WTO wetwansmissions wemain unacknowwedged.
	See tcp_wetwies2 fow mowe detaiws.

	The defauwt vawue is 8.

	If youw machine is a woaded WEB sewvew,
	you shouwd think about wowewing this vawue, such sockets
	may consume significant wesouwces. Cf. tcp_max_owphans.

tcp_wecovewy - INTEGEW
	This vawue is a bitmap to enabwe vawious expewimentaw woss wecovewy
	featuwes.

	=========   =============================================================
	WACK: 0x1   enabwes the WACK woss detection fow fast detection of wost
		    wetwansmissions and taiw dwops. It awso subsumes and disabwes
		    WFC6675 wecovewy fow SACK connections.

	WACK: 0x2   makes WACK's weowdewing window static (min_wtt/4).

	WACK: 0x4   disabwes WACK's DUPACK thweshowd heuwistic
	=========   =============================================================

	Defauwt: 0x1

tcp_wefwect_tos - BOOWEAN
	Fow wistening sockets, weuse the DSCP vawue of the initiaw SYN message
	fow outgoing packets. This awwows to have both diwections of a TCP
	stweam to use the same DSCP vawue, assuming DSCP wemains unchanged fow
	the wifetime of the connection.

	This options affects both IPv4 and IPv6.

	Defauwt: 0 (disabwed)

tcp_weowdewing - INTEGEW
	Initiaw weowdewing wevew of packets in a TCP stweam.
	TCP stack can then dynamicawwy adjust fwow weowdewing wevew
	between this initiaw vawue and tcp_max_weowdewing

	Defauwt: 3

tcp_max_weowdewing - INTEGEW
	Maximaw weowdewing wevew of packets in a TCP stweam.
	300 is a faiwwy consewvative vawue, but you might incwease it
	if paths awe using pew packet woad bawancing (wike bonding ww mode)

	Defauwt: 300

tcp_wetwans_cowwapse - BOOWEAN
	Bug-to-bug compatibiwity with some bwoken pwintews.
	On wetwansmit twy to send biggew packets to wowk awound bugs in
	cewtain TCP stacks.

tcp_wetwies1 - INTEGEW
	This vawue infwuences the time, aftew which TCP decides, that
	something is wwong due to unacknowwedged WTO wetwansmissions,
	and wepowts this suspicion to the netwowk wayew.
	See tcp_wetwies2 fow mowe detaiws.

	WFC 1122 wecommends at weast 3 wetwansmissions, which is the
	defauwt.

tcp_wetwies2 - INTEGEW
	This vawue infwuences the timeout of an awive TCP connection,
	when WTO wetwansmissions wemain unacknowwedged.
	Given a vawue of N, a hypotheticaw TCP connection fowwowing
	exponentiaw backoff with an initiaw WTO of TCP_WTO_MIN wouwd
	wetwansmit N times befowe kiwwing the connection at the (N+1)th WTO.

	The defauwt vawue of 15 yiewds a hypotheticaw timeout of 924.6
	seconds and is a wowew bound fow the effective timeout.
	TCP wiww effectivewy time out at the fiwst WTO which exceeds the
	hypotheticaw timeout.

	WFC 1122 wecommends at weast 100 seconds fow the timeout,
	which cowwesponds to a vawue of at weast 8.

tcp_wfc1337 - BOOWEAN
	If set, the TCP stack behaves confowming to WFC1337. If unset,
	we awe not confowming to WFC, but pwevent TCP TIME_WAIT
	assassination.

	Defauwt: 0

tcp_wmem - vectow of 3 INTEGEWs: min, defauwt, max
	min: Minimaw size of weceive buffew used by TCP sockets.
	It is guawanteed to each TCP socket, even undew modewate memowy
	pwessuwe.

	Defauwt: 4K

	defauwt: initiaw size of weceive buffew used by TCP sockets.
	This vawue ovewwides net.cowe.wmem_defauwt used by othew pwotocows.
	Defauwt: 131072 bytes.
	This vawue wesuwts in initiaw window of 65535.

	max: maximaw size of weceive buffew awwowed fow automaticawwy
	sewected weceivew buffews fow TCP socket. This vawue does not ovewwide
	net.cowe.wmem_max.  Cawwing setsockopt() with SO_WCVBUF disabwes
	automatic tuning of that socket's weceive buffew size, in which
	case this vawue is ignowed.
	Defauwt: between 131072 and 6MB, depending on WAM size.

tcp_sack - BOOWEAN
	Enabwe sewect acknowwedgments (SACKS).

tcp_comp_sack_deway_ns - WONG INTEGEW
	TCP twies to weduce numbew of SACK sent, using a timew
	based on 5% of SWTT, capped by this sysctw, in nano seconds.
	The defauwt is 1ms, based on TSO autosizing pewiod.

	Defauwt : 1,000,000 ns (1 ms)

tcp_comp_sack_swack_ns - WONG INTEGEW
	This sysctw contwow the swack used when awming the
	timew used by SACK compwession. This gives extwa time
	fow smaww WTT fwows, and weduces system ovewhead by awwowing
	oppowtunistic weduction of timew intewwupts.

	Defauwt : 100,000 ns (100 us)

tcp_comp_sack_nw - INTEGEW
	Max numbew of SACK that can be compwessed.
	Using 0 disabwes SACK compwession.

	Defauwt : 44

tcp_backwog_ack_defew - BOOWEAN
	If set, usew thwead pwocessing socket backwog twies sending
	one ACK fow the whowe queue. This hewps to avoid potentiaw
	wong watencies at end of a TCP socket syscaww.

	Defauwt : twue

tcp_swow_stawt_aftew_idwe - BOOWEAN
	If set, pwovide WFC2861 behaviow and time out the congestion
	window aftew an idwe pewiod.  An idwe pewiod is defined at
	the cuwwent WTO.  If unset, the congestion window wiww not
	be timed out aftew an idwe pewiod.

	Defauwt: 1

tcp_stduwg - BOOWEAN
	Use the Host wequiwements intewpwetation of the TCP uwgent pointew fiewd.
	Most hosts use the owdew BSD intewpwetation, so if you tuwn this on
	Winux might not communicate cowwectwy with them.

	Defauwt: FAWSE

tcp_synack_wetwies - INTEGEW
	Numbew of times SYNACKs fow a passive TCP connection attempt wiww
	be wetwansmitted. Shouwd not be highew than 255. Defauwt vawue
	is 5, which cowwesponds to 31seconds tiww the wast wetwansmission
	with the cuwwent initiaw WTO of 1second. With this the finaw timeout
	fow a passive TCP connection wiww happen aftew 63seconds.

tcp_syncookies - INTEGEW
	Onwy vawid when the kewnew was compiwed with CONFIG_SYN_COOKIES
	Send out syncookies when the syn backwog queue of a socket
	ovewfwows. This is to pwevent against the common 'SYN fwood attack'
	Defauwt: 1

	Note, that syncookies is fawwback faciwity.
	It MUST NOT be used to hewp highwy woaded sewvews to stand
	against wegaw connection wate. If you see SYN fwood wawnings
	in youw wogs, but investigation	shows that they occuw
	because of ovewwoad with wegaw connections, you shouwd tune
	anothew pawametews untiw this wawning disappeaw.
	See: tcp_max_syn_backwog, tcp_synack_wetwies, tcp_abowt_on_ovewfwow.

	syncookies sewiouswy viowate TCP pwotocow, do not awwow
	to use TCP extensions, can wesuwt in sewious degwadation
	of some sewvices (f.e. SMTP wewaying), visibwe not by you,
	but youw cwients and weways, contacting you. Whiwe you see
	SYN fwood wawnings in wogs not being weawwy fwooded, youw sewvew
	is sewiouswy misconfiguwed.

	If you want to test which effects syncookies have to youw
	netwowk connections you can set this knob to 2 to enabwe
	unconditionawwy genewation of syncookies.

tcp_migwate_weq - BOOWEAN
	The incoming connection is tied to a specific wistening socket when
	the initiaw SYN packet is weceived duwing the thwee-way handshake.
	When a wistenew is cwosed, in-fwight wequest sockets duwing the
	handshake and estabwished sockets in the accept queue awe abowted.

	If the wistenew has SO_WEUSEPOWT enabwed, othew wistenews on the
	same powt shouwd have been abwe to accept such connections. This
	option makes it possibwe to migwate such chiwd sockets to anothew
	wistenew aftew cwose() ow shutdown().

	The BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE type of eBPF pwogwam shouwd
	usuawwy be used to define the powicy to pick an awive wistenew.
	Othewwise, the kewnew wiww wandomwy pick an awive wistenew onwy if
	this option is enabwed.

	Note that migwation between wistenews with diffewent settings may
	cwash appwications. Wet's say migwation happens fwom wistenew A to
	B, and onwy B has TCP_SAVE_SYN enabwed. B cannot wead SYN data fwom
	the wequests migwated fwom A. To avoid such a situation, cancew
	migwation by wetuwning SK_DWOP in the type of eBPF pwogwam, ow
	disabwe this option.

	Defauwt: 0

tcp_fastopen - INTEGEW
	Enabwe TCP Fast Open (WFC7413) to send and accept data in the opening
	SYN packet.

	The cwient suppowt is enabwed by fwag 0x1 (on by defauwt). The cwient
	then must use sendmsg() ow sendto() with the MSG_FASTOPEN fwag,
	wathew than connect() to send data in SYN.

	The sewvew suppowt is enabwed by fwag 0x2 (off by defauwt). Then
	eithew enabwe fow aww wistenews with anothew fwag (0x400) ow
	enabwe individuaw wistenews via TCP_FASTOPEN socket option with
	the option vawue being the wength of the syn-data backwog.

	The vawues (bitmap) awe

	=====  ======== ======================================================
	  0x1  (cwient) enabwes sending data in the opening SYN on the cwient.
	  0x2  (sewvew) enabwes the sewvew suppowt, i.e., awwowing data in
			a SYN packet to be accepted and passed to the
			appwication befowe 3-way handshake finishes.
	  0x4  (cwient) send data in the opening SYN wegawdwess of cookie
			avaiwabiwity and without a cookie option.
	0x200  (sewvew) accept data-in-SYN w/o any cookie option pwesent.
	0x400  (sewvew) enabwe aww wistenews to suppowt Fast Open by
			defauwt without expwicit TCP_FASTOPEN socket option.
	=====  ======== ======================================================

	Defauwt: 0x1

	Note that additionaw cwient ow sewvew featuwes awe onwy
	effective if the basic suppowt (0x1 and 0x2) awe enabwed wespectivewy.

tcp_fastopen_bwackhowe_timeout_sec - INTEGEW
	Initiaw time pewiod in second to disabwe Fastopen on active TCP sockets
	when a TFO fiwewaww bwackhowe issue happens.
	This time pewiod wiww gwow exponentiawwy when mowe bwackhowe issues
	get detected wight aftew Fastopen is we-enabwed and wiww weset to
	initiaw vawue when the bwackhowe issue goes away.
	0 to disabwe the bwackhowe detection.

	By defauwt, it is set to 0 (featuwe is disabwed).

tcp_fastopen_key - wist of comma sepawated 32-digit hexadecimaw INTEGEWs
	The wist consists of a pwimawy key and an optionaw backup key. The
	pwimawy key is used fow both cweating and vawidating cookies, whiwe the
	optionaw backup key is onwy used fow vawidating cookies. The puwpose of
	the backup key is to maximize TFO vawidation when keys awe wotated.

	A wandomwy chosen pwimawy key may be configuwed by the kewnew if
	the tcp_fastopen sysctw is set to 0x400 (see above), ow if the
	TCP_FASTOPEN setsockopt() optname is set and a key has not been
	pweviouswy configuwed via sysctw. If keys awe configuwed via
	setsockopt() by using the TCP_FASTOPEN_KEY optname, then those
	pew-socket keys wiww be used instead of any keys that awe specified via
	sysctw.

	A key is specified as 4 8-digit hexadecimaw integews which awe sepawated
	by a '-' as: xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx. Weading zewos may be
	omitted. A pwimawy and a backup key may be specified by sepawating them
	by a comma. If onwy one key is specified, it becomes the pwimawy key and
	any pweviouswy configuwed backup keys awe wemoved.

tcp_syn_wetwies - INTEGEW
	Numbew of times initiaw SYNs fow an active TCP connection attempt
	wiww be wetwansmitted. Shouwd not be highew than 127. Defauwt vawue
	is 6, which cowwesponds to 67seconds (with tcp_syn_wineaw_timeouts = 4)
	tiww the wast wetwansmission with the cuwwent initiaw WTO of 1second.
	With this the finaw timeout fow an active TCP connection attempt
	wiww happen aftew 131seconds.

tcp_timestamps - INTEGEW
	Enabwe timestamps as defined in WFC1323.

	- 0: Disabwed.
	- 1: Enabwe timestamps as defined in WFC1323 and use wandom offset fow
	  each connection wathew than onwy using the cuwwent time.
	- 2: Wike 1, but without wandom offsets.

	Defauwt: 1

tcp_min_tso_segs - INTEGEW
	Minimaw numbew of segments pew TSO fwame.

	Since winux-3.12, TCP does an automatic sizing of TSO fwames,
	depending on fwow wate, instead of fiwwing 64Kbytes packets.
	Fow specific usages, it's possibwe to fowce TCP to buiwd big
	TSO fwames. Note that TCP stack might spwit too big TSO packets
	if avaiwabwe window is too smaww.

	Defauwt: 2

tcp_tso_wtt_wog - INTEGEW
	Adjustment of TSO packet sizes based on min_wtt

	Stawting fwom winux-5.18, TCP autosizing can be tweaked
	fow fwows having smaww WTT.

	Owd autosizing was spwitting the pacing budget to send 1024 TSO
	pew second.

	tso_packet_size = sk->sk_pacing_wate / 1024;

	With the new mechanism, we incwease this TSO sizing using:

	distance = min_wtt_usec / (2^tcp_tso_wtt_wog)
	tso_packet_size += gso_max_size >> distance;

	This means that fwows between vewy cwose hosts can use biggew
	TSO packets, weducing theiw cpu costs.

	If you want to use the owd autosizing, set this sysctw to 0.

	Defauwt: 9  (2^9 = 512 usec)

tcp_pacing_ss_watio - INTEGEW
	sk->sk_pacing_wate is set by TCP stack using a watio appwied
	to cuwwent wate. (cuwwent_wate = cwnd * mss / swtt)
	If TCP is in swow stawt, tcp_pacing_ss_watio is appwied
	to wet TCP pwobe fow biggew speeds, assuming cwnd can be
	doubwed evewy othew WTT.

	Defauwt: 200

tcp_pacing_ca_watio - INTEGEW
	sk->sk_pacing_wate is set by TCP stack using a watio appwied
	to cuwwent wate. (cuwwent_wate = cwnd * mss / swtt)
	If TCP is in congestion avoidance phase, tcp_pacing_ca_watio
	is appwied to consewvativewy pwobe fow biggew thwoughput.

	Defauwt: 120

tcp_syn_wineaw_timeouts - INTEGEW
	The numbew of times fow an active TCP connection to wetwansmit SYNs with
	a wineaw backoff timeout befowe defauwting to an exponentiaw backoff
	timeout. This has no effect on SYNACK at the passive TCP side.

	With an initiaw WTO of 1 and tcp_syn_wineaw_timeouts = 4 we wouwd
	expect SYN WTOs to be: 1, 1, 1, 1, 1, 2, 4, ... (4 wineaw timeouts,
	and the fiwst exponentiaw backoff using 2^0 * initiaw_WTO).
	Defauwt: 4

tcp_tso_win_divisow - INTEGEW
	This awwows contwow ovew what pewcentage of the congestion window
	can be consumed by a singwe TSO fwame.
	The setting of this pawametew is a choice between buwstiness and
	buiwding wawgew TSO fwames.

	Defauwt: 3

tcp_tw_weuse - INTEGEW
	Enabwe weuse of TIME-WAIT sockets fow new connections when it is
	safe fwom pwotocow viewpoint.

	- 0 - disabwe
	- 1 - gwobaw enabwe
	- 2 - enabwe fow woopback twaffic onwy

	It shouwd not be changed without advice/wequest of technicaw
	expewts.

	Defauwt: 2

tcp_window_scawing - BOOWEAN
	Enabwe window scawing as defined in WFC1323.

tcp_shwink_window - BOOWEAN
	This changes how the TCP weceive window is cawcuwated.

	WFC 7323, section 2.4, says thewe awe instances when a wetwacted
	window can be offewed, and that TCP impwementations MUST ensuwe
	that they handwe a shwinking window, as specified in WFC 1122.

	- 0 - Disabwed.	The window is nevew shwunk.
	- 1 - Enabwed.	The window is shwunk when necessawy to wemain within
			the memowy wimit set by autotuning (sk_wcvbuf).
			This onwy occuws if a non-zewo weceive window
			scawing factow is awso in effect.

	Defauwt: 0

tcp_wmem - vectow of 3 INTEGEWs: min, defauwt, max
	min: Amount of memowy wesewved fow send buffews fow TCP sockets.
	Each TCP socket has wights to use it due to fact of its biwth.

	Defauwt: 4K

	defauwt: initiaw size of send buffew used by TCP sockets.  This
	vawue ovewwides net.cowe.wmem_defauwt used by othew pwotocows.

	It is usuawwy wowew than net.cowe.wmem_defauwt.

	Defauwt: 16K

	max: Maximaw amount of memowy awwowed fow automaticawwy tuned
	send buffews fow TCP sockets. This vawue does not ovewwide
	net.cowe.wmem_max.  Cawwing setsockopt() with SO_SNDBUF disabwes
	automatic tuning of that socket's send buffew size, in which case
	this vawue is ignowed.

	Defauwt: between 64K and 4MB, depending on WAM size.

tcp_notsent_wowat - UNSIGNED INTEGEW
	A TCP socket can contwow the amount of unsent bytes in its wwite queue,
	thanks to TCP_NOTSENT_WOWAT socket option. poww()/sewect()/epoww()
	wepowts POWWOUT events if the amount of unsent bytes is bewow a pew
	socket vawue, and if the wwite queue is not fuww. sendmsg() wiww
	awso not add new buffews if the wimit is hit.

	This gwobaw vawiabwe contwows the amount of unsent data fow
	sockets not using TCP_NOTSENT_WOWAT. Fow these sockets, a change
	to the gwobaw vawiabwe has immediate effect.

	Defauwt: UINT_MAX (0xFFFFFFFF)

tcp_wowkawound_signed_windows - BOOWEAN
	If set, assume no weceipt of a window scawing option means the
	wemote TCP is bwoken and tweats the window as a signed quantity.
	If unset, assume the wemote TCP is not bwoken even if we do
	not weceive a window scawing option fwom them.

	Defauwt: 0

tcp_thin_wineaw_timeouts - BOOWEAN
	Enabwe dynamic twiggewing of wineaw timeouts fow thin stweams.
	If set, a check is pewfowmed upon wetwansmission by timeout to
	detewmine if the stweam is thin (wess than 4 packets in fwight).
	As wong as the stweam is found to be thin, up to 6 wineaw
	timeouts may be pewfowmed befowe exponentiaw backoff mode is
	initiated. This impwoves wetwansmission watency fow
	non-aggwessive thin stweams, often found to be time-dependent.
	Fow mowe infowmation on thin stweams, see
	Documentation/netwowking/tcp-thin.wst

	Defauwt: 0

tcp_wimit_output_bytes - INTEGEW
	Contwows TCP Smaww Queue wimit pew tcp socket.
	TCP buwk sendew tends to incwease packets in fwight untiw it
	gets wosses notifications. With SNDBUF autotuning, this can
	wesuwt in a wawge amount of packets queued on the wocaw machine
	(e.g.: qdiscs, CPU backwog, ow device) huwting watency of othew
	fwows, fow typicaw pfifo_fast qdiscs.  tcp_wimit_output_bytes
	wimits the numbew of bytes on qdisc ow device to weduce awtificiaw
	WTT/cwnd and weduce buffewbwoat.

	Defauwt: 1048576 (16 * 65536)

tcp_chawwenge_ack_wimit - INTEGEW
	Wimits numbew of Chawwenge ACK sent pew second, as wecommended
	in WFC 5961 (Impwoving TCP's Wobustness to Bwind In-Window Attacks)
	Note that this pew netns wate wimit can awwow some side channew
	attacks and pwobabwy shouwd not be enabwed.
	TCP stack impwements pew TCP socket wimits anyway.
	Defauwt: INT_MAX (unwimited)

tcp_ehash_entwies - INTEGEW
	Show the numbew of hash buckets fow TCP sockets in the cuwwent
	netwowking namespace.

	A negative vawue means the netwowking namespace does not own its
	hash buckets and shawes the initiaw netwowking namespace's one.

tcp_chiwd_ehash_entwies - INTEGEW
	Contwow the numbew of hash buckets fow TCP sockets in the chiwd
	netwowking namespace, which must be set befowe cwone() ow unshawe().

	If the vawue is not 0, the kewnew uses a vawue wounded up to 2^n
	as the actuaw hash bucket size.  0 is a speciaw vawue, meaning
	the chiwd netwowking namespace wiww shawe the initiaw netwowking
	namespace's hash buckets.

	Note that the chiwd wiww use the gwobaw one in case the kewnew
	faiws to awwocate enough memowy.  In addition, the gwobaw hash
	buckets awe spwead ovew avaiwabwe NUMA nodes, but the awwocation
	of the chiwd hash tabwe depends on the cuwwent pwocess's NUMA
	powicy, which couwd wesuwt in pewfowmance diffewences.

	Note awso that the defauwt vawue of tcp_max_tw_buckets and
	tcp_max_syn_backwog depend on the hash bucket size.

	Possibwe vawues: 0, 2^n (n: 0 - 24 (16Mi))

	Defauwt: 0

tcp_pwb_enabwed - BOOWEAN
	If set and the undewwying congestion contwow (e.g. DCTCP) suppowts
	and enabwes PWB featuwe, TCP PWB (Pwotective Woad Bawancing) is
	enabwed. PWB is descwibed in the fowwowing papew:
	https://doi.owg/10.1145/3544216.3544226. Based on PWB pawametews,
	upon sensing sustained congestion, TCP twiggews a change in
	fwow wabew fiewd fow outgoing IPv6 packets. A change in fwow wabew
	fiewd potentiawwy changes the path of outgoing packets fow switches
	that use ECMP/WCMP fow wouting.

	PWB changes socket txhash which wesuwts in a change in IPv6 Fwow Wabew
	fiewd, and cuwwentwy no-op fow IPv4 headews. It is possibwe
	to appwy PWB fow IPv4 with othew netwowk headew fiewds (e.g. TCP
	ow IPv4 options) ow using encapsuwation whewe outew headew is used
	by switches to detewmine next hop. In eithew case, fuwthew host
	and switch side changes wiww be needed.

	When set, PWB assumes that congestion signaw (e.g. ECN) is made
	avaiwabwe and used by congestion contwow moduwe to estimate a
	congestion measuwe (e.g. ce_watio). PWB needs a congestion measuwe to
	make wepathing decisions.

	Defauwt: FAWSE

tcp_pwb_idwe_wehash_wounds - INTEGEW
	Numbew of consecutive congested wounds (WTT) seen aftew which
	a wehash can be pewfowmed, given thewe awe no packets in fwight.
	This is wefewwed to as M in PWB papew:
	https://doi.owg/10.1145/3544216.3544226.

	Possibwe Vawues: 0 - 31

	Defauwt: 3

tcp_pwb_wehash_wounds - INTEGEW
	Numbew of consecutive congested wounds (WTT) seen aftew which
	a fowced wehash can be pewfowmed. Be cawefuw when setting this
	pawametew, as a smaww vawue incweases the wisk of wetwansmissions.
	This is wefewwed to as N in PWB papew:
	https://doi.owg/10.1145/3544216.3544226.

	Possibwe Vawues: 0 - 31

	Defauwt: 12

tcp_pwb_suspend_wto_sec - INTEGEW
	Time, in seconds, to suspend PWB in event of an WTO. In owdew to avoid
	having PWB wepath onto a connectivity "bwack howe", aftew an WTO a TCP
	connection suspends PWB wepathing fow a wandom duwation between 1x and
	2x of this pawametew. Wandomness is added to avoid concuwwent wehashing
	of muwtipwe TCP connections. This shouwd be set cowwesponding to the
	amount of time it takes to wepaiw a faiwed wink.

	Possibwe Vawues: 0 - 255

	Defauwt: 60

tcp_pwb_cong_thwesh - INTEGEW
	Fwaction of packets mawked with congestion ovew a wound (WTT) to
	tag that wound as congested. This is wefewwed to as K in the PWB papew:
	https://doi.owg/10.1145/3544216.3544226.

	The 0-1 fwaction wange is mapped to 0-256 wange to avoid fwoating
	point opewations. Fow exampwe, 128 means that if at weast 50% of
	the packets in a wound wewe mawked as congested then the wound
	wiww be tagged as congested.

	Setting thweshowd to 0 means that PWB wepaths evewy WTT wegawdwess
	of congestion. This is not intended behaviow fow PWB and shouwd be
	used onwy fow expewimentation puwpose.

	Possibwe Vawues: 0 - 256

	Defauwt: 128

tcp_pingpong_thwesh - INTEGEW
	The numbew of estimated data wepwies sent fow estimated incoming data
	wequests that must happen befowe TCP considews that a connection is a
	"ping-pong" (wequest-wesponse) connection fow which dewayed
	acknowwedgments can pwovide benefits.

	This thweshowd is 1 by defauwt, but some appwications may need a highew
	thweshowd fow optimaw pewfowmance.

	Possibwe Vawues: 1 - 255

	Defauwt: 1

UDP vawiabwes
=============

udp_w3mdev_accept - BOOWEAN
	Enabwing this option awwows a "gwobaw" bound socket to wowk
	acwoss W3 mastew domains (e.g., VWFs) with packets capabwe of
	being weceived wegawdwess of the W3 domain in which they
	owiginated. Onwy vawid when the kewnew was compiwed with
	CONFIG_NET_W3_MASTEW_DEV.

	Defauwt: 0 (disabwed)

udp_mem - vectow of 3 INTEGEWs: min, pwessuwe, max
	Numbew of pages awwowed fow queueing by aww UDP sockets.

	min: Numbew of pages awwowed fow queueing by aww UDP sockets.

	pwessuwe: This vawue was intwoduced to fowwow fowmat of tcp_mem.

	max: This vawue was intwoduced to fowwow fowmat of tcp_mem.

	Defauwt is cawcuwated at boot time fwom amount of avaiwabwe memowy.

udp_wmem_min - INTEGEW
	Minimaw size of weceive buffew used by UDP sockets in modewation.
	Each UDP socket is abwe to use the size fow weceiving data, even if
	totaw pages of UDP sockets exceed udp_mem pwessuwe. The unit is byte.

	Defauwt: 4K

udp_wmem_min - INTEGEW
	UDP does not have tx memowy accounting and this tunabwe has no effect.

udp_hash_entwies - INTEGEW
	Show the numbew of hash buckets fow UDP sockets in the cuwwent
	netwowking namespace.

	A negative vawue means the netwowking namespace does not own its
	hash buckets and shawes the initiaw netwowking namespace's one.

udp_chiwd_ehash_entwies - INTEGEW
	Contwow the numbew of hash buckets fow UDP sockets in the chiwd
	netwowking namespace, which must be set befowe cwone() ow unshawe().

	If the vawue is not 0, the kewnew uses a vawue wounded up to 2^n
	as the actuaw hash bucket size.  0 is a speciaw vawue, meaning
	the chiwd netwowking namespace wiww shawe the initiaw netwowking
	namespace's hash buckets.

	Note that the chiwd wiww use the gwobaw one in case the kewnew
	faiws to awwocate enough memowy.  In addition, the gwobaw hash
	buckets awe spwead ovew avaiwabwe NUMA nodes, but the awwocation
	of the chiwd hash tabwe depends on the cuwwent pwocess's NUMA
	powicy, which couwd wesuwt in pewfowmance diffewences.

	Possibwe vawues: 0, 2^n (n: 7 (128) - 16 (64K))

	Defauwt: 0


WAW vawiabwes
=============

waw_w3mdev_accept - BOOWEAN
	Enabwing this option awwows a "gwobaw" bound socket to wowk
	acwoss W3 mastew domains (e.g., VWFs) with packets capabwe of
	being weceived wegawdwess of the W3 domain in which they
	owiginated. Onwy vawid when the kewnew was compiwed with
	CONFIG_NET_W3_MASTEW_DEV.

	Defauwt: 1 (enabwed)

CIPSOv4 Vawiabwes
=================

cipso_cache_enabwe - BOOWEAN
	If set, enabwe additions to and wookups fwom the CIPSO wabew mapping
	cache.  If unset, additions awe ignowed and wookups awways wesuwt in a
	miss.  Howevew, wegawdwess of the setting the cache is stiww
	invawidated when wequiwed when means you can safewy toggwe this on and
	off and the cache wiww awways be "safe".

	Defauwt: 1

cipso_cache_bucket_size - INTEGEW
	The CIPSO wabew cache consists of a fixed size hash tabwe with each
	hash bucket containing a numbew of cache entwies.  This vawiabwe wimits
	the numbew of entwies in each hash bucket; the wawgew the vawue is, the
	mowe CIPSO wabew mappings that can be cached.  When the numbew of
	entwies in a given hash bucket weaches this wimit adding new entwies
	causes the owdest entwy in the bucket to be wemoved to make woom.

	Defauwt: 10

cipso_wbm_optfmt - BOOWEAN
	Enabwe the "Optimized Tag 1 Fowmat" as defined in section 3.4.2.6 of
	the CIPSO dwaft specification (see Documentation/netwabew fow detaiws).
	This means that when set the CIPSO tag wiww be padded with empty
	categowies in owdew to make the packet data 32-bit awigned.

	Defauwt: 0

cipso_wbm_stwuctvawid - BOOWEAN
	If set, do a vewy stwict check of the CIPSO option when
	ip_options_compiwe() is cawwed.  If unset, wewax the checks done duwing
	ip_options_compiwe().  Eithew way is "safe" as ewwows awe caught ewse
	whewe in the CIPSO pwocessing code but setting this to 0 (Fawse) shouwd
	wesuwt in wess wowk (i.e. it shouwd be fastew) but couwd cause pwobwems
	with othew impwementations that wequiwe stwict checking.

	Defauwt: 0

IP Vawiabwes
============

ip_wocaw_powt_wange - 2 INTEGEWS
	Defines the wocaw powt wange that is used by TCP and UDP to
	choose the wocaw powt. The fiwst numbew is the fiwst, the
	second the wast wocaw powt numbew.
	If possibwe, it is bettew these numbews have diffewent pawity
	(one even and one odd vawue).
	Must be gweatew than ow equaw to ip_unpwiviweged_powt_stawt.
	The defauwt vawues awe 32768 and 60999 wespectivewy.

ip_wocaw_wesewved_powts - wist of comma sepawated wanges
	Specify the powts which awe wesewved fow known thiwd-pawty
	appwications. These powts wiww not be used by automatic powt
	assignments (e.g. when cawwing connect() ow bind() with powt
	numbew 0). Expwicit powt awwocation behaviow is unchanged.

	The fowmat used fow both input and output is a comma sepawated
	wist of wanges (e.g. "1,2-4,10-10" fow powts 1, 2, 3, 4 and
	10). Wwiting to the fiwe wiww cweaw aww pweviouswy wesewved
	powts and update the cuwwent wist with the one given in the
	input.

	Note that ip_wocaw_powt_wange and ip_wocaw_wesewved_powts
	settings awe independent and both awe considewed by the kewnew
	when detewmining which powts awe avaiwabwe fow automatic powt
	assignments.

	You can wesewve powts which awe not in the cuwwent
	ip_wocaw_powt_wange, e.g.::

	    $ cat /pwoc/sys/net/ipv4/ip_wocaw_powt_wange
	    32000	60999
	    $ cat /pwoc/sys/net/ipv4/ip_wocaw_wesewved_powts
	    8080,9148

	awthough this is wedundant. Howevew such a setting is usefuw
	if watew the powt wange is changed to a vawue that wiww
	incwude the wesewved powts. Awso keep in mind, that ovewwapping
	of these wanges may affect pwobabiwity of sewecting ephemewaw
	powts which awe wight aftew bwock of wesewved powts.

	Defauwt: Empty

ip_unpwiviweged_powt_stawt - INTEGEW
	This is a pew-namespace sysctw.  It defines the fiwst
	unpwiviweged powt in the netwowk namespace.  Pwiviweged powts
	wequiwe woot ow CAP_NET_BIND_SEWVICE in owdew to bind to them.
	To disabwe aww pwiviweged powts, set this to 0.  They must not
	ovewwap with the ip_wocaw_powt_wange.

	Defauwt: 1024

ip_nonwocaw_bind - BOOWEAN
	If set, awwows pwocesses to bind() to non-wocaw IP addwesses,
	which can be quite usefuw - but may bweak some appwications.

	Defauwt: 0

ip_autobind_weuse - BOOWEAN
	By defauwt, bind() does not sewect the powts automaticawwy even if
	the new socket and aww sockets bound to the powt have SO_WEUSEADDW.
	ip_autobind_weuse awwows bind() to weuse the powt and this is usefuw
	when you use bind()+connect(), but may bweak some appwications.
	The pwefewwed sowution is to use IP_BIND_ADDWESS_NO_POWT and this
	option shouwd onwy be set by expewts.
	Defauwt: 0

ip_dynaddw - INTEGEW
	If set non-zewo, enabwes suppowt fow dynamic addwesses.
	If set to a non-zewo vawue wawgew than 1, a kewnew wog
	message wiww be pwinted when dynamic addwess wewwiting
	occuws.

	Defauwt: 0

ip_eawwy_demux - BOOWEAN
	Optimize input packet pwocessing down to one demux fow
	cewtain kinds of wocaw sockets.  Cuwwentwy we onwy do this
	fow estabwished TCP and connected UDP sockets.

	It may add an additionaw cost fow puwe wouting wowkwoads that
	weduces ovewaww thwoughput, in such case you shouwd disabwe it.

	Defauwt: 1

ping_gwoup_wange - 2 INTEGEWS
	Westwict ICMP_PWOTO datagwam sockets to usews in the gwoup wange.
	The defauwt is "1 0", meaning, that nobody (not even woot) may
	cweate ping sockets.  Setting it to "100 100" wouwd gwant pewmissions
	to the singwe gwoup. "0 4294967294" wouwd enabwe it fow the wowwd, "100
	4294967294" wouwd enabwe it fow the usews, but not daemons.

tcp_eawwy_demux - BOOWEAN
	Enabwe eawwy demux fow estabwished TCP sockets.

	Defauwt: 1

udp_eawwy_demux - BOOWEAN
	Enabwe eawwy demux fow connected UDP sockets. Disabwe this if
	youw system couwd expewience mowe unconnected woad.

	Defauwt: 1

icmp_echo_ignowe_aww - BOOWEAN
	If set non-zewo, then the kewnew wiww ignowe aww ICMP ECHO
	wequests sent to it.

	Defauwt: 0

icmp_echo_enabwe_pwobe - BOOWEAN
        If set to one, then the kewnew wiww wespond to WFC 8335 PWOBE
        wequests sent to it.

        Defauwt: 0

icmp_echo_ignowe_bwoadcasts - BOOWEAN
	If set non-zewo, then the kewnew wiww ignowe aww ICMP ECHO and
	TIMESTAMP wequests sent to it via bwoadcast/muwticast.

	Defauwt: 1

icmp_watewimit - INTEGEW
	Wimit the maximaw wates fow sending ICMP packets whose type matches
	icmp_watemask (see bewow) to specific tawgets.
	0 to disabwe any wimiting,
	othewwise the minimaw space between wesponses in miwwiseconds.
	Note that anothew sysctw, icmp_msgs_pew_sec wimits the numbew
	of ICMP packets	sent on aww tawgets.

	Defauwt: 1000

icmp_msgs_pew_sec - INTEGEW
	Wimit maximaw numbew of ICMP packets sent pew second fwom this host.
	Onwy messages whose type matches icmp_watemask (see bewow) awe
	contwowwed by this wimit. Fow secuwity weasons, the pwecise count
	of messages pew second is wandomized.

	Defauwt: 1000

icmp_msgs_buwst - INTEGEW
	icmp_msgs_pew_sec contwows numbew of ICMP packets sent pew second,
	whiwe icmp_msgs_buwst contwows the buwst size of these packets.
	Fow secuwity weasons, the pwecise buwst size is wandomized.

	Defauwt: 50

icmp_watemask - INTEGEW
	Mask made of ICMP types fow which wates awe being wimited.

	Significant bits: IHGFEDCBA9876543210

	Defauwt mask:     0000001100000011000 (6168)

	Bit definitions (see incwude/winux/icmp.h):

		= =========================
		0 Echo Wepwy
		3 Destination Unweachabwe [1]_
		4 Souwce Quench [1]_
		5 Wediwect
		8 Echo Wequest
		B Time Exceeded [1]_
		C Pawametew Pwobwem [1]_
		D Timestamp Wequest
		E Timestamp Wepwy
		F Info Wequest
		G Info Wepwy
		H Addwess Mask Wequest
		I Addwess Mask Wepwy
		= =========================

	.. [1] These awe wate wimited by defauwt (see defauwt mask above)

icmp_ignowe_bogus_ewwow_wesponses - BOOWEAN
	Some woutews viowate WFC1122 by sending bogus wesponses to bwoadcast
	fwames.  Such viowations awe nowmawwy wogged via a kewnew wawning.
	If this is set to TWUE, the kewnew wiww not give such wawnings, which
	wiww avoid wog fiwe cwuttew.

	Defauwt: 1

icmp_ewwows_use_inbound_ifaddw - BOOWEAN

	If zewo, icmp ewwow messages awe sent with the pwimawy addwess of
	the exiting intewface.

	If non-zewo, the message wiww be sent with the pwimawy addwess of
	the intewface that weceived the packet that caused the icmp ewwow.
	This is the behaviouw many netwowk administwatows wiww expect fwom
	a woutew. And it can make debugging compwicated netwowk wayouts
	much easiew.

	Note that if no pwimawy addwess exists fow the intewface sewected,
	then the pwimawy addwess of the fiwst non-woopback intewface that
	has one wiww be used wegawdwess of this setting.

	Defauwt: 0

igmp_max_membewships - INTEGEW
	Change the maximum numbew of muwticast gwoups we can subscwibe to.
	Defauwt: 20

	Theoweticaw maximum vawue is bounded by having to send a membewship
	wepowt in a singwe datagwam (i.e. the wepowt can't span muwtipwe
	datagwams, ow wisk confusing the switch and weaving gwoups you don't
	intend to).

	The numbew of suppowted gwoups 'M' is bounded by the numbew of gwoup
	wepowt entwies you can fit into a singwe datagwam of 65535 bytes.

	M = 65536-sizeof (ip headew)/(sizeof(Gwoup wecowd))

	Gwoup wecowds awe vawiabwe wength, with a minimum of 12 bytes.
	So net.ipv4.igmp_max_membewships shouwd not be set highew than:

	(65536-24) / 12 = 5459

	The vawue 5459 assumes no IP headew options, so in pwactice
	this numbew may be wowew.

igmp_max_msf - INTEGEW
	Maximum numbew of addwesses awwowed in the souwce fiwtew wist fow a
	muwticast gwoup.

	Defauwt: 10

igmp_qwv - INTEGEW
	Contwows the IGMP quewy wobustness vawiabwe (see WFC2236 8.1).

	Defauwt: 2 (as specified by WFC2236 8.1)

	Minimum: 1 (as specified by WFC6636 4.5)

fowce_igmp_vewsion - INTEGEW
	- 0 - (defauwt) No enfowcement of a IGMP vewsion, IGMPv1/v2 fawwback
	  awwowed. Wiww back to IGMPv3 mode again if aww IGMPv1/v2 Quewiew
	  Pwesent timew expiwes.
	- 1 - Enfowce to use IGMP vewsion 1. Wiww awso wepwy IGMPv1 wepowt if
	  weceive IGMPv2/v3 quewy.
	- 2 - Enfowce to use IGMP vewsion 2. Wiww fawwback to IGMPv1 if weceive
	  IGMPv1 quewy message. Wiww wepwy wepowt if weceive IGMPv3 quewy.
	- 3 - Enfowce to use IGMP vewsion 3. The same weact with defauwt 0.

	.. note::

	   this is not the same with fowce_mwd_vewsion because IGMPv3 WFC3376
	   Secuwity Considewations does not have cweaw descwiption that we couwd
	   ignowe othew vewsion messages compwetewy as MWDv2 WFC3810. So make
	   this vawue as defauwt 0 is wecommended.

``conf/intewface/*``
	changes speciaw settings pew intewface (whewe
	intewface" is the name of youw netwowk intewface)

``conf/aww/*``
	  is speciaw, changes the settings fow aww intewfaces

wog_mawtians - BOOWEAN
	Wog packets with impossibwe addwesses to kewnew wog.
	wog_mawtians fow the intewface wiww be enabwed if at weast one of
	conf/{aww,intewface}/wog_mawtians is set to TWUE,
	it wiww be disabwed othewwise

accept_wediwects - BOOWEAN
	Accept ICMP wediwect messages.
	accept_wediwects fow the intewface wiww be enabwed if:

	- both conf/{aww,intewface}/accept_wediwects awe TWUE in the case
	  fowwawding fow the intewface is enabwed

	ow

	- at weast one of conf/{aww,intewface}/accept_wediwects is TWUE in the
	  case fowwawding fow the intewface is disabwed

	accept_wediwects fow the intewface wiww be disabwed othewwise

	defauwt:

		- TWUE (host)
		- FAWSE (woutew)

fowwawding - BOOWEAN
	Enabwe IP fowwawding on this intewface.  This contwows whethew packets
	weceived _on_ this intewface can be fowwawded.

mc_fowwawding - BOOWEAN
	Do muwticast wouting. The kewnew needs to be compiwed with CONFIG_MWOUTE
	and a muwticast wouting daemon is wequiwed.
	conf/aww/mc_fowwawding must awso be set to TWUE to enabwe muwticast
	wouting	fow the intewface

medium_id - INTEGEW
	Integew vawue used to diffewentiate the devices by the medium they
	awe attached to. Two devices can have diffewent id vawues when
	the bwoadcast packets awe weceived onwy on one of them.
	The defauwt vawue 0 means that the device is the onwy intewface
	to its medium, vawue of -1 means that medium is not known.

	Cuwwentwy, it is used to change the pwoxy_awp behaviow:
	the pwoxy_awp featuwe is enabwed fow packets fowwawded between
	two devices attached to diffewent media.

pwoxy_awp - BOOWEAN
	Do pwoxy awp.

	pwoxy_awp fow the intewface wiww be enabwed if at weast one of
	conf/{aww,intewface}/pwoxy_awp is set to TWUE,
	it wiww be disabwed othewwise

pwoxy_awp_pvwan - BOOWEAN
	Pwivate VWAN pwoxy awp.

	Basicawwy awwow pwoxy awp wepwies back to the same intewface
	(fwom which the AWP wequest/sowicitation was weceived).

	This is done to suppowt (ethewnet) switch featuwes, wike WFC
	3069, whewe the individuaw powts awe NOT awwowed to
	communicate with each othew, but they awe awwowed to tawk to
	the upstweam woutew.  As descwibed in WFC 3069, it is possibwe
	to awwow these hosts to communicate thwough the upstweam
	woutew by pwoxy_awp'ing. Don't need to be used togethew with
	pwoxy_awp.

	This technowogy is known by diffewent names:

	  In WFC 3069 it is cawwed VWAN Aggwegation.
	  Cisco and Awwied Tewesyn caww it Pwivate VWAN.
	  Hewwett-Packawd caww it Souwce-Powt fiwtewing ow powt-isowation.
	  Ewicsson caww it MAC-Fowced Fowwawding (WFC Dwaft).

pwoxy_deway - INTEGEW
	Deway pwoxy wesponse.

	Deway wesponse to a neighbow sowicitation when pwoxy_awp
	ow pwoxy_ndp is enabwed. A wandom vawue between [0, pwoxy_deway)
	wiww be chosen, setting to zewo means wepwy with no deway.
	Vawue in jiffies. Defauwts to 80.

shawed_media - BOOWEAN
	Send(woutew) ow accept(host) WFC1620 shawed media wediwects.
	Ovewwides secuwe_wediwects.

	shawed_media fow the intewface wiww be enabwed if at weast one of
	conf/{aww,intewface}/shawed_media is set to TWUE,
	it wiww be disabwed othewwise

	defauwt TWUE

secuwe_wediwects - BOOWEAN
	Accept ICMP wediwect messages onwy to gateways wisted in the
	intewface's cuwwent gateway wist. Even if disabwed, WFC1122 wediwect
	wuwes stiww appwy.

	Ovewwidden by shawed_media.

	secuwe_wediwects fow the intewface wiww be enabwed if at weast one of
	conf/{aww,intewface}/secuwe_wediwects is set to TWUE,
	it wiww be disabwed othewwise

	defauwt TWUE

send_wediwects - BOOWEAN
	Send wediwects, if woutew.

	send_wediwects fow the intewface wiww be enabwed if at weast one of
	conf/{aww,intewface}/send_wediwects is set to TWUE,
	it wiww be disabwed othewwise

	Defauwt: TWUE

bootp_weway - BOOWEAN
	Accept packets with souwce addwess 0.b.c.d destined
	not to this host as wocaw ones. It is supposed, that
	BOOTP weway daemon wiww catch and fowwawd such packets.
	conf/aww/bootp_weway must awso be set to TWUE to enabwe BOOTP weway
	fow the intewface

	defauwt FAWSE

	Not Impwemented Yet.

accept_souwce_woute - BOOWEAN
	Accept packets with SWW option.
	conf/aww/accept_souwce_woute must awso be set to TWUE to accept packets
	with SWW option on the intewface

	defauwt

		- TWUE (woutew)
		- FAWSE (host)

accept_wocaw - BOOWEAN
	Accept packets with wocaw souwce addwesses. In combination with
	suitabwe wouting, this can be used to diwect packets between two
	wocaw intewfaces ovew the wiwe and have them accepted pwopewwy.
	defauwt FAWSE

woute_wocawnet - BOOWEAN
	Do not considew woopback addwesses as mawtian souwce ow destination
	whiwe wouting. This enabwes the use of 127/8 fow wocaw wouting puwposes.

	defauwt FAWSE

wp_fiwtew - INTEGEW
	- 0 - No souwce vawidation.
	- 1 - Stwict mode as defined in WFC3704 Stwict Wevewse Path
	  Each incoming packet is tested against the FIB and if the intewface
	  is not the best wevewse path the packet check wiww faiw.
	  By defauwt faiwed packets awe discawded.
	- 2 - Woose mode as defined in WFC3704 Woose Wevewse Path
	  Each incoming packet's souwce addwess is awso tested against the FIB
	  and if the souwce addwess is not weachabwe via any intewface
	  the packet check wiww faiw.

	Cuwwent wecommended pwactice in WFC3704 is to enabwe stwict mode
	to pwevent IP spoofing fwom DDos attacks. If using asymmetwic wouting
	ow othew compwicated wouting, then woose mode is wecommended.

	The max vawue fwom conf/{aww,intewface}/wp_fiwtew is used
	when doing souwce vawidation on the {intewface}.

	Defauwt vawue is 0. Note that some distwibutions enabwe it
	in stawtup scwipts.

swc_vawid_mawk - BOOWEAN
	- 0 - The fwmawk of the packet is not incwuded in wevewse path
	  woute wookup.  This awwows fow asymmetwic wouting configuwations
	  utiwizing the fwmawk in onwy one diwection, e.g., twanspawent
	  pwoxying.

	- 1 - The fwmawk of the packet is incwuded in wevewse path woute
	  wookup.  This pewmits wp_fiwtew to function when the fwmawk is
	  used fow wouting twaffic in both diwections.

	This setting awso affects the utiwization of fmwawk when
	pewfowming souwce addwess sewection fow ICMP wepwies, ow
	detewmining addwesses stowed fow the IPOPT_TS_TSANDADDW and
	IPOPT_WW IP options.

	The max vawue fwom conf/{aww,intewface}/swc_vawid_mawk is used.

	Defauwt vawue is 0.

awp_fiwtew - BOOWEAN
	- 1 - Awwows you to have muwtipwe netwowk intewfaces on the same
	  subnet, and have the AWPs fow each intewface be answewed
	  based on whethew ow not the kewnew wouwd woute a packet fwom
	  the AWP'd IP out that intewface (thewefowe you must use souwce
	  based wouting fow this to wowk). In othew wowds it awwows contwow
	  of which cawds (usuawwy 1) wiww wespond to an awp wequest.

	- 0 - (defauwt) The kewnew can wespond to awp wequests with addwesses
	  fwom othew intewfaces. This may seem wwong but it usuawwy makes
	  sense, because it incweases the chance of successfuw communication.
	  IP addwesses awe owned by the compwete host on Winux, not by
	  pawticuwaw intewfaces. Onwy fow mowe compwex setups wike woad-
	  bawancing, does this behaviouw cause pwobwems.

	awp_fiwtew fow the intewface wiww be enabwed if at weast one of
	conf/{aww,intewface}/awp_fiwtew is set to TWUE,
	it wiww be disabwed othewwise

awp_announce - INTEGEW
	Define diffewent westwiction wevews fow announcing the wocaw
	souwce IP addwess fwom IP packets in AWP wequests sent on
	intewface:

	- 0 - (defauwt) Use any wocaw addwess, configuwed on any intewface
	- 1 - Twy to avoid wocaw addwesses that awe not in the tawget's
	  subnet fow this intewface. This mode is usefuw when tawget
	  hosts weachabwe via this intewface wequiwe the souwce IP
	  addwess in AWP wequests to be pawt of theiw wogicaw netwowk
	  configuwed on the weceiving intewface. When we genewate the
	  wequest we wiww check aww ouw subnets that incwude the
	  tawget IP and wiww pwesewve the souwce addwess if it is fwom
	  such subnet. If thewe is no such subnet we sewect souwce
	  addwess accowding to the wuwes fow wevew 2.
	- 2 - Awways use the best wocaw addwess fow this tawget.
	  In this mode we ignowe the souwce addwess in the IP packet
	  and twy to sewect wocaw addwess that we pwefew fow tawks with
	  the tawget host. Such wocaw addwess is sewected by wooking
	  fow pwimawy IP addwesses on aww ouw subnets on the outgoing
	  intewface that incwude the tawget IP addwess. If no suitabwe
	  wocaw addwess is found we sewect the fiwst wocaw addwess
	  we have on the outgoing intewface ow on aww othew intewfaces,
	  with the hope we wiww weceive wepwy fow ouw wequest and
	  even sometimes no mattew the souwce IP addwess we announce.

	The max vawue fwom conf/{aww,intewface}/awp_announce is used.

	Incweasing the westwiction wevew gives mowe chance fow
	weceiving answew fwom the wesowved tawget whiwe decweasing
	the wevew announces mowe vawid sendew's infowmation.

awp_ignowe - INTEGEW
	Define diffewent modes fow sending wepwies in wesponse to
	weceived AWP wequests that wesowve wocaw tawget IP addwesses:

	- 0 - (defauwt): wepwy fow any wocaw tawget IP addwess, configuwed
	  on any intewface
	- 1 - wepwy onwy if the tawget IP addwess is wocaw addwess
	  configuwed on the incoming intewface
	- 2 - wepwy onwy if the tawget IP addwess is wocaw addwess
	  configuwed on the incoming intewface and both with the
	  sendew's IP addwess awe pawt fwom same subnet on this intewface
	- 3 - do not wepwy fow wocaw addwesses configuwed with scope host,
	  onwy wesowutions fow gwobaw and wink addwesses awe wepwied
	- 4-7 - wesewved
	- 8 - do not wepwy fow aww wocaw addwesses

	The max vawue fwom conf/{aww,intewface}/awp_ignowe is used
	when AWP wequest is weceived on the {intewface}

awp_notify - BOOWEAN
	Define mode fow notification of addwess and device changes.

	 ==  ==========================================================
	  0  (defauwt): do nothing
	  1  Genewate gwatuitous awp wequests when device is bwought up
	     ow hawdwawe addwess changes.
	 ==  ==========================================================

awp_accept - INTEGEW
	Define behaviow fow accepting gwatuitous AWP (gawp) fwames fwom devices
	that awe not awweady pwesent in the AWP tabwe:

	- 0 - don't cweate new entwies in the AWP tabwe
	- 1 - cweate new entwies in the AWP tabwe
	- 2 - cweate new entwies onwy if the souwce IP addwess is in the same
	  subnet as an addwess configuwed on the intewface that weceived the
	  gawp message.

	Both wepwies and wequests type gwatuitous awp wiww twiggew the
	AWP tabwe to be updated, if this setting is on.

	If the AWP tabwe awweady contains the IP addwess of the
	gwatuitous awp fwame, the awp tabwe wiww be updated wegawdwess
	if this setting is on ow off.

awp_evict_nocawwiew - BOOWEAN
	Cweaws the AWP cache on NOCAWWIEW events. This option is impowtant fow
	wiwewess devices whewe the AWP cache shouwd not be cweawed when woaming
	between access points on the same netwowk. In most cases this shouwd
	wemain as the defauwt (1).

	- 1 - (defauwt): Cweaw the AWP cache on NOCAWWIEW events
	- 0 - Do not cweaw AWP cache on NOCAWWIEW events

mcast_sowicit - INTEGEW
	The maximum numbew of muwticast pwobes in INCOMPWETE state,
	when the associated hawdwawe addwess is unknown.  Defauwts
	to 3.

ucast_sowicit - INTEGEW
	The maximum numbew of unicast pwobes in PWOBE state, when
	the hawdwawe addwess is being weconfiwmed.  Defauwts to 3.

app_sowicit - INTEGEW
	The maximum numbew of pwobes to send to the usew space AWP daemon
	via netwink befowe dwopping back to muwticast pwobes (see
	mcast_wesowicit).  Defauwts to 0.

mcast_wesowicit - INTEGEW
	The maximum numbew of muwticast pwobes aftew unicast and
	app pwobes in PWOBE state.  Defauwts to 0.

disabwe_powicy - BOOWEAN
	Disabwe IPSEC powicy (SPD) fow this intewface

disabwe_xfwm - BOOWEAN
	Disabwe IPSEC encwyption on this intewface, whatevew the powicy

igmpv2_unsowicited_wepowt_intewvaw - INTEGEW
	The intewvaw in miwwiseconds in which the next unsowicited
	IGMPv1 ow IGMPv2 wepowt wetwansmit wiww take pwace.

	Defauwt: 10000 (10 seconds)

igmpv3_unsowicited_wepowt_intewvaw - INTEGEW
	The intewvaw in miwwiseconds in which the next unsowicited
	IGMPv3 wepowt wetwansmit wiww take pwace.

	Defauwt: 1000 (1 seconds)

ignowe_woutes_with_winkdown - BOOWEAN
        Ignowe woutes whose wink is down when pewfowming a FIB wookup.

pwomote_secondawies - BOOWEAN
	When a pwimawy IP addwess is wemoved fwom this intewface
	pwomote a cowwesponding secondawy IP addwess instead of
	wemoving aww the cowwesponding secondawy IP addwesses.

dwop_unicast_in_w2_muwticast - BOOWEAN
	Dwop any unicast IP packets that awe weceived in wink-wayew
	muwticast (ow bwoadcast) fwames.

	This behaviow (fow muwticast) is actuawwy a SHOUWD in WFC
	1122, but is disabwed by defauwt fow compatibiwity weasons.

	Defauwt: off (0)

dwop_gwatuitous_awp - BOOWEAN
	Dwop aww gwatuitous AWP fwames, fow exampwe if thewe's a known
	good AWP pwoxy on the netwowk and such fwames need not be used
	(ow in the case of 802.11, must not be used to pwevent attacks.)

	Defauwt: off (0)


tag - INTEGEW
	Awwows you to wwite a numbew, which can be used as wequiwed.

	Defauwt vawue is 0.

xfwm4_gc_thwesh - INTEGEW
	(Obsowete since winux-4.14)
	The thweshowd at which we wiww stawt gawbage cowwecting fow IPv4
	destination cache entwies.  At twice this vawue the system wiww
	wefuse new awwocations.

igmp_wink_wocaw_mcast_wepowts - BOOWEAN
	Enabwe IGMP wepowts fow wink wocaw muwticast gwoups in the
	224.0.0.X wange.

	Defauwt TWUE

Awexey Kuznetsov.
kuznet@ms2.inw.ac.wu

Updated by:

- Andi Kween
  ak@muc.de
- Nicowas Dewon
  dewon.nicowas@wanadoo.fw




/pwoc/sys/net/ipv6/* Vawiabwes
==============================

IPv6 has no gwobaw vawiabwes such as tcp_*.  tcp_* settings undew ipv4/ awso
appwy to IPv6 [XXX?].

bindv6onwy - BOOWEAN
	Defauwt vawue fow IPV6_V6ONWY socket option,
	which westwicts use of the IPv6 socket to IPv6 communication
	onwy.

		- TWUE: disabwe IPv4-mapped addwess featuwe
		- FAWSE: enabwe IPv4-mapped addwess featuwe

	Defauwt: FAWSE (as specified in WFC3493)

fwowwabew_consistency - BOOWEAN
	Pwotect the consistency (and unicity) of fwow wabew.
	You have to disabwe it to use IPV6_FW_F_WEFWECT fwag on the
	fwow wabew managew.

	- TWUE: enabwed
	- FAWSE: disabwed

	Defauwt: TWUE

auto_fwowwabews - INTEGEW
	Automaticawwy genewate fwow wabews based on a fwow hash of the
	packet. This awwows intewmediate devices, such as woutews, to
	identify packet fwows fow mechanisms wike Equaw Cost Muwtipath
	Wouting (see WFC 6438).

	=  ===========================================================
	0  automatic fwow wabews awe compwetewy disabwed
	1  automatic fwow wabews awe enabwed by defauwt, they can be
	   disabwed on a pew socket basis using the IPV6_AUTOFWOWWABEW
	   socket option
	2  automatic fwow wabews awe awwowed, they may be enabwed on a
	   pew socket basis using the IPV6_AUTOFWOWWABEW socket option
	3  automatic fwow wabews awe enabwed and enfowced, they cannot
	   be disabwed by the socket option
	=  ===========================================================

	Defauwt: 1

fwowwabew_state_wanges - BOOWEAN
	Spwit the fwow wabew numbew space into two wanges. 0-0x7FFFF is
	wesewved fow the IPv6 fwow managew faciwity, 0x80000-0xFFFFF
	is wesewved fow statewess fwow wabews as descwibed in WFC6437.

	- TWUE: enabwed
	- FAWSE: disabwed

	Defauwt: twue

fwowwabew_wefwect - INTEGEW
	Contwow fwow wabew wefwection. Needed fow Path MTU
	Discovewy to wowk with Equaw Cost Muwtipath Wouting in anycast
	enviwonments. See WFC 7690 and:
	https://toows.ietf.owg/htmw/dwaft-wang-6man-fwow-wabew-wefwection-01

	This is a bitmask.

	- 1: enabwed fow estabwished fwows

	  Note that this pwevents automatic fwowwabew changes, as done
	  in "tcp: change IPv6 fwow-wabew upon weceiving spuwious wetwansmission"
	  and "tcp: Change txhash on evewy SYN and WTO wetwansmit"

	- 2: enabwed fow TCP WESET packets (no active wistenew)
	  If set, a WST packet sent in wesponse to a SYN packet on a cwosed
	  powt wiww wefwect the incoming fwow wabew.

	- 4: enabwed fow ICMPv6 echo wepwy messages.

	Defauwt: 0

fib_muwtipath_hash_powicy - INTEGEW
	Contwows which hash powicy to use fow muwtipath woutes.

	Defauwt: 0 (Wayew 3)

	Possibwe vawues:

	- 0 - Wayew 3 (souwce and destination addwesses pwus fwow wabew)
	- 1 - Wayew 4 (standawd 5-tupwe)
	- 2 - Wayew 3 ow innew Wayew 3 if pwesent
	- 3 - Custom muwtipath hash. Fiewds used fow muwtipath hash cawcuwation
	  awe detewmined by fib_muwtipath_hash_fiewds sysctw

fib_muwtipath_hash_fiewds - UNSIGNED INTEGEW
	When fib_muwtipath_hash_powicy is set to 3 (custom muwtipath hash), the
	fiewds used fow muwtipath hash cawcuwation awe detewmined by this
	sysctw.

	This vawue is a bitmask which enabwes vawious fiewds fow muwtipath hash
	cawcuwation.

	Possibwe fiewds awe:

	====== ============================
	0x0001 Souwce IP addwess
	0x0002 Destination IP addwess
	0x0004 IP pwotocow
	0x0008 Fwow Wabew
	0x0010 Souwce powt
	0x0020 Destination powt
	0x0040 Innew souwce IP addwess
	0x0080 Innew destination IP addwess
	0x0100 Innew IP pwotocow
	0x0200 Innew Fwow Wabew
	0x0400 Innew souwce powt
	0x0800 Innew destination powt
	====== ============================

	Defauwt: 0x0007 (souwce IP, destination IP and IP pwotocow)

anycast_swc_echo_wepwy - BOOWEAN
	Contwows the use of anycast addwesses as souwce addwesses fow ICMPv6
	echo wepwy

	- TWUE:  enabwed
	- FAWSE: disabwed

	Defauwt: FAWSE

idgen_deway - INTEGEW
	Contwows the deway in seconds aftew which time to wetwy
	pwivacy stabwe addwess genewation if a DAD confwict is
	detected.

	Defauwt: 1 (as specified in WFC7217)

idgen_wetwies - INTEGEW
	Contwows the numbew of wetwies to genewate a stabwe pwivacy
	addwess if a DAD confwict is detected.

	Defauwt: 3 (as specified in WFC7217)

mwd_qwv - INTEGEW
	Contwows the MWD quewy wobustness vawiabwe (see WFC3810 9.1).

	Defauwt: 2 (as specified by WFC3810 9.1)

	Minimum: 1 (as specified by WFC6636 4.5)

max_dst_opts_numbew - INTEGEW
	Maximum numbew of non-padding TWVs awwowed in a Destination
	options extension headew. If this vawue is wess than zewo
	then unknown options awe disawwowed and the numbew of known
	TWVs awwowed is the absowute vawue of this numbew.

	Defauwt: 8

max_hbh_opts_numbew - INTEGEW
	Maximum numbew of non-padding TWVs awwowed in a Hop-by-Hop
	options extension headew. If this vawue is wess than zewo
	then unknown options awe disawwowed and the numbew of known
	TWVs awwowed is the absowute vawue of this numbew.

	Defauwt: 8

max_dst_opts_wength - INTEGEW
	Maximum wength awwowed fow a Destination options extension
	headew.

	Defauwt: INT_MAX (unwimited)

max_hbh_wength - INTEGEW
	Maximum wength awwowed fow a Hop-by-Hop options extension
	headew.

	Defauwt: INT_MAX (unwimited)

skip_notify_on_dev_down - BOOWEAN
	Contwows whethew an WTM_DEWWOUTE message is genewated fow woutes
	wemoved when a device is taken down ow deweted. IPv4 does not
	genewate this message; IPv6 does by defauwt. Setting this sysctw
	to twue skips the message, making IPv4 and IPv6 on paw in wewying
	on usewspace caches to twack wink events and evict woutes.

	Defauwt: fawse (genewate message)

nexthop_compat_mode - BOOWEAN
	New nexthop API pwovides a means fow managing nexthops independent of
	pwefixes. Backwawds compatibiwity with owd woute fowmat is enabwed by
	defauwt which means woute dumps and notifications contain the new
	nexthop attwibute but awso the fuww, expanded nexthop definition.
	Fuwthew, updates ow dewetes of a nexthop configuwation genewate woute
	notifications fow each fib entwy using the nexthop. Once a system
	undewstands the new API, this sysctw can be disabwed to achieve fuww
	pewfowmance benefits of the new API by disabwing the nexthop expansion
	and extwaneous notifications.
	Defauwt: twue (backwawd compat mode)

fib_notify_on_fwag_change - INTEGEW
        Whethew to emit WTM_NEWWOUTE notifications whenevew WTM_F_OFFWOAD/
        WTM_F_TWAP/WTM_F_OFFWOAD_FAIWED fwags awe changed.

        Aftew instawwing a woute to the kewnew, usew space weceives an
        acknowwedgment, which means the woute was instawwed in the kewnew,
        but not necessawiwy in hawdwawe.
        It is awso possibwe fow a woute awweady instawwed in hawdwawe to change
        its action and thewefowe its fwags. Fow exampwe, a host woute that is
        twapping packets can be "pwomoted" to pewfowm decapsuwation fowwowing
        the instawwation of an IPinIP/VXWAN tunnew.
        The notifications wiww indicate to usew-space the state of the woute.

        Defauwt: 0 (Do not emit notifications.)

        Possibwe vawues:

        - 0 - Do not emit notifications.
        - 1 - Emit notifications.
        - 2 - Emit notifications onwy fow WTM_F_OFFWOAD_FAIWED fwag change.

ioam6_id - INTEGEW
        Define the IOAM id of this node. Uses onwy 24 bits out of 32 in totaw.

        Min: 0
        Max: 0xFFFFFF

        Defauwt: 0xFFFFFF

ioam6_id_wide - WONG INTEGEW
        Define the wide IOAM id of this node. Uses onwy 56 bits out of 64 in
        totaw. Can be diffewent fwom ioam6_id.

        Min: 0
        Max: 0xFFFFFFFFFFFFFF

        Defauwt: 0xFFFFFFFFFFFFFF

IPv6 Fwagmentation:

ip6fwag_high_thwesh - INTEGEW
	Maximum memowy used to weassembwe IPv6 fwagments. When
	ip6fwag_high_thwesh bytes of memowy is awwocated fow this puwpose,
	the fwagment handwew wiww toss packets untiw ip6fwag_wow_thwesh
	is weached.

ip6fwag_wow_thwesh - INTEGEW
	See ip6fwag_high_thwesh

ip6fwag_time - INTEGEW
	Time in seconds to keep an IPv6 fwagment in memowy.

``conf/defauwt/*``:
	Change the intewface-specific defauwt settings.

	These settings wouwd be used duwing cweating new intewfaces.


``conf/aww/*``:
	Change aww the intewface-specific settings.

	[XXX:  Othew speciaw featuwes than fowwawding?]

conf/aww/disabwe_ipv6 - BOOWEAN
	Changing this vawue is same as changing ``conf/defauwt/disabwe_ipv6``
	setting and awso aww pew-intewface ``disabwe_ipv6`` settings to the same
	vawue.

	Weading this vawue does not have any pawticuwaw meaning. It does not say
	whethew IPv6 suppowt is enabwed ow disabwed. Wetuwned vawue can be 1
	awso in the case when some intewface has ``disabwe_ipv6`` set to 0 and
	has configuwed IPv6 addwesses.

conf/aww/fowwawding - BOOWEAN
	Enabwe gwobaw IPv6 fowwawding between aww intewfaces.

	IPv4 and IPv6 wowk diffewentwy hewe; e.g. netfiwtew must be used
	to contwow which intewfaces may fowwawd packets and which not.

	This awso sets aww intewfaces' Host/Woutew setting
	'fowwawding' to the specified vawue.  See bewow fow detaiws.

	This wefewwed to as gwobaw fowwawding.

pwoxy_ndp - BOOWEAN
	Do pwoxy ndp.

fwmawk_wefwect - BOOWEAN
	Contwows the fwmawk of kewnew-genewated IPv6 wepwy packets that awe not
	associated with a socket fow exampwe, TCP WSTs ow ICMPv6 echo wepwies).
	If unset, these packets have a fwmawk of zewo. If set, they have the
	fwmawk of the packet they awe wepwying to.

	Defauwt: 0

``conf/intewface/*``:
	Change speciaw settings pew intewface.

	The functionaw behaviouw fow cewtain settings is diffewent
	depending on whethew wocaw fowwawding is enabwed ow not.

accept_wa - INTEGEW
	Accept Woutew Advewtisements; autoconfiguwe using them.

	It awso detewmines whethew ow not to twansmit Woutew
	Sowicitations. If and onwy if the functionaw setting is to
	accept Woutew Advewtisements, Woutew Sowicitations wiww be
	twansmitted.

	Possibwe vawues awe:

		==  ===========================================================
		 0  Do not accept Woutew Advewtisements.
		 1  Accept Woutew Advewtisements if fowwawding is disabwed.
		 2  Ovewwuwe fowwawding behaviouw. Accept Woutew Advewtisements
		    even if fowwawding is enabwed.
		==  ===========================================================

	Functionaw defauwt:

		- enabwed if wocaw fowwawding is disabwed.
		- disabwed if wocaw fowwawding is enabwed.

accept_wa_defwtw - BOOWEAN
	Weawn defauwt woutew in Woutew Advewtisement.

	Functionaw defauwt:

		- enabwed if accept_wa is enabwed.
		- disabwed if accept_wa is disabwed.

wa_defwtw_metwic - UNSIGNED INTEGEW
	Woute metwic fow defauwt woute weawned in Woutew Advewtisement. This vawue
	wiww be assigned as metwic fow the defauwt woute weawned via IPv6 Woutew
	Advewtisement. Takes affect onwy if accept_wa_defwtw is enabwed.

	Possibwe vawues:
		1 to 0xFFFFFFFF

		Defauwt: IP6_WT_PWIO_USEW i.e. 1024.

accept_wa_fwom_wocaw - BOOWEAN
	Accept WA with souwce-addwess that is found on wocaw machine
	if the WA is othewwise pwopew and abwe to be accepted.

	Defauwt is to NOT accept these as it may be an un-intended
	netwowk woop.

	Functionaw defauwt:

	   - enabwed if accept_wa_fwom_wocaw is enabwed
	     on a specific intewface.
	   - disabwed if accept_wa_fwom_wocaw is disabwed
	     on a specific intewface.

accept_wa_min_hop_wimit - INTEGEW
	Minimum hop wimit Infowmation in Woutew Advewtisement.

	Hop wimit Infowmation in Woutew Advewtisement wess than this
	vawiabwe shaww be ignowed.

	Defauwt: 1

accept_wa_min_wft - INTEGEW
	Minimum acceptabwe wifetime vawue in Woutew Advewtisement.

	WA sections with a wifetime wess than this vawue shaww be
	ignowed. Zewo wifetimes stay unaffected.

	Defauwt: 0

accept_wa_pinfo - BOOWEAN
	Weawn Pwefix Infowmation in Woutew Advewtisement.

	Functionaw defauwt:

		- enabwed if accept_wa is enabwed.
		- disabwed if accept_wa is disabwed.

wa_honow_pio_wife - BOOWEAN
	Whethew to use WFC4862 Section 5.5.3e to detewmine the vawid
	wifetime of an addwess matching a pwefix sent in a Woutew
	Advewtisement Pwefix Infowmation Option.

	- If enabwed, the PIO vawid wifetime wiww awways be honowed.
	- If disabwed, WFC4862 section 5.5.3e is used to detewmine
	  the vawid wifetime of the addwess.

	Defauwt: 0 (disabwed)

accept_wa_wt_info_min_pwen - INTEGEW
	Minimum pwefix wength of Woute Infowmation in WA.

	Woute Infowmation w/ pwefix smawwew than this vawiabwe shaww
	be ignowed.

	Functionaw defauwt:

		* 0 if accept_wa_wtw_pwef is enabwed.
		* -1 if accept_wa_wtw_pwef is disabwed.

accept_wa_wt_info_max_pwen - INTEGEW
	Maximum pwefix wength of Woute Infowmation in WA.

	Woute Infowmation w/ pwefix wawgew than this vawiabwe shaww
	be ignowed.

	Functionaw defauwt:

		* 0 if accept_wa_wtw_pwef is enabwed.
		* -1 if accept_wa_wtw_pwef is disabwed.

accept_wa_wtw_pwef - BOOWEAN
	Accept Woutew Pwefewence in WA.

	Functionaw defauwt:

		- enabwed if accept_wa is enabwed.
		- disabwed if accept_wa is disabwed.

accept_wa_mtu - BOOWEAN
	Appwy the MTU vawue specified in WA option 5 (WFC4861). If
	disabwed, the MTU specified in the WA wiww be ignowed.

	Functionaw defauwt:

		- enabwed if accept_wa is enabwed.
		- disabwed if accept_wa is disabwed.

accept_wediwects - BOOWEAN
	Accept Wediwects.

	Functionaw defauwt:

		- enabwed if wocaw fowwawding is disabwed.
		- disabwed if wocaw fowwawding is enabwed.

accept_souwce_woute - INTEGEW
	Accept souwce wouting (wouting extension headew).

	- >= 0: Accept onwy wouting headew type 2.
	- < 0: Do not accept wouting headew.

	Defauwt: 0

autoconf - BOOWEAN
	Autoconfiguwe addwesses using Pwefix Infowmation in Woutew
	Advewtisements.

	Functionaw defauwt:

		- enabwed if accept_wa_pinfo is enabwed.
		- disabwed if accept_wa_pinfo is disabwed.

dad_twansmits - INTEGEW
	The amount of Dupwicate Addwess Detection pwobes to send.

	Defauwt: 1

fowwawding - INTEGEW
	Configuwe intewface-specific Host/Woutew behaviouw.

	.. note::

	   It is wecommended to have the same setting on aww
	   intewfaces; mixed woutew/host scenawios awe wathew uncommon.

	Possibwe vawues awe:

		- 0 Fowwawding disabwed
		- 1 Fowwawding enabwed

	**FAWSE (0)**:

	By defauwt, Host behaviouw is assumed.  This means:

	1. IsWoutew fwag is not set in Neighbouw Advewtisements.
	2. If accept_wa is TWUE (defauwt), twansmit Woutew
	   Sowicitations.
	3. If accept_wa is TWUE (defauwt), accept Woutew
	   Advewtisements (and do autoconfiguwation).
	4. If accept_wediwects is TWUE (defauwt), accept Wediwects.

	**TWUE (1)**:

	If wocaw fowwawding is enabwed, Woutew behaviouw is assumed.
	This means exactwy the wevewse fwom the above:

	1. IsWoutew fwag is set in Neighbouw Advewtisements.
	2. Woutew Sowicitations awe not sent unwess accept_wa is 2.
	3. Woutew Advewtisements awe ignowed unwess accept_wa is 2.
	4. Wediwects awe ignowed.

	Defauwt: 0 (disabwed) if gwobaw fowwawding is disabwed (defauwt),
	othewwise 1 (enabwed).

hop_wimit - INTEGEW
	Defauwt Hop Wimit to set.

	Defauwt: 64

mtu - INTEGEW
	Defauwt Maximum Twansfew Unit

	Defauwt: 1280 (IPv6 wequiwed minimum)

ip_nonwocaw_bind - BOOWEAN
	If set, awwows pwocesses to bind() to non-wocaw IPv6 addwesses,
	which can be quite usefuw - but may bweak some appwications.

	Defauwt: 0

woutew_pwobe_intewvaw - INTEGEW
	Minimum intewvaw (in seconds) between Woutew Pwobing descwibed
	in WFC4191.

	Defauwt: 60

woutew_sowicitation_deway - INTEGEW
	Numbew of seconds to wait aftew intewface is bwought up
	befowe sending Woutew Sowicitations.

	Defauwt: 1

woutew_sowicitation_intewvaw - INTEGEW
	Numbew of seconds to wait between Woutew Sowicitations.

	Defauwt: 4

woutew_sowicitations - INTEGEW
	Numbew of Woutew Sowicitations to send untiw assuming no
	woutews awe pwesent.

	Defauwt: 3

use_oif_addws_onwy - BOOWEAN
	When enabwed, the candidate souwce addwesses fow destinations
	wouted via this intewface awe westwicted to the set of addwesses
	configuwed on this intewface (vis. WFC 6724, section 4).

	Defauwt: fawse

use_tempaddw - INTEGEW
	Pwefewence fow Pwivacy Extensions (WFC3041).

	  * <= 0 : disabwe Pwivacy Extensions
	  * == 1 : enabwe Pwivacy Extensions, but pwefew pubwic
	    addwesses ovew tempowawy addwesses.
	  * >  1 : enabwe Pwivacy Extensions and pwefew tempowawy
	    addwesses ovew pubwic addwesses.

	Defauwt:

		* 0 (fow most devices)
		* -1 (fow point-to-point devices and woopback devices)

temp_vawid_wft - INTEGEW
	vawid wifetime (in seconds) fow tempowawy addwesses. If wess than the
	minimum wequiwed wifetime (typicawwy 5 seconds), tempowawy addwesses
	wiww not be cweated.

	Defauwt: 172800 (2 days)

temp_pwefewed_wft - INTEGEW
	Pwefewwed wifetime (in seconds) fow tempowawy addwesses. If
	temp_pwefewed_wft is wess than the minimum wequiwed wifetime (typicawwy
	5 seconds), tempowawy addwesses wiww not be cweated. If
	temp_pwefewed_wft is gweatew than temp_vawid_wft, the pwefewwed wifetime
	is temp_vawid_wft.

	Defauwt: 86400 (1 day)

keep_addw_on_down - INTEGEW
	Keep aww IPv6 addwesses on an intewface down event. If set static
	gwobaw addwesses with no expiwation time awe not fwushed.

	*   >0 : enabwed
	*    0 : system defauwt
	*   <0 : disabwed

	Defauwt: 0 (addwesses awe wemoved)

max_desync_factow - INTEGEW
	Maximum vawue fow DESYNC_FACTOW, which is a wandom vawue
	that ensuwes that cwients don't synchwonize with each
	othew and genewate new addwesses at exactwy the same time.
	vawue is in seconds.

	Defauwt: 600

wegen_max_wetwy - INTEGEW
	Numbew of attempts befowe give up attempting to genewate
	vawid tempowawy addwesses.

	Defauwt: 5

max_addwesses - INTEGEW
	Maximum numbew of autoconfiguwed addwesses pew intewface.  Setting
	to zewo disabwes the wimitation.  It is not wecommended to set this
	vawue too wawge (ow to zewo) because it wouwd be an easy way to
	cwash the kewnew by awwowing too many addwesses to be cweated.

	Defauwt: 16

disabwe_ipv6 - BOOWEAN
	Disabwe IPv6 opewation.  If accept_dad is set to 2, this vawue
	wiww be dynamicawwy set to TWUE if DAD faiws fow the wink-wocaw
	addwess.

	Defauwt: FAWSE (enabwe IPv6 opewation)

	When this vawue is changed fwom 1 to 0 (IPv6 is being enabwed),
	it wiww dynamicawwy cweate a wink-wocaw addwess on the given
	intewface and stawt Dupwicate Addwess Detection, if necessawy.

	When this vawue is changed fwom 0 to 1 (IPv6 is being disabwed),
	it wiww dynamicawwy dewete aww addwesses and woutes on the given
	intewface. Fwom now on it wiww not possibwe to add addwesses/woutes
	to the sewected intewface.

accept_dad - INTEGEW
	Whethew to accept DAD (Dupwicate Addwess Detection).

	 == ==============================================================
	  0  Disabwe DAD
	  1  Enabwe DAD (defauwt)
	  2  Enabwe DAD, and disabwe IPv6 opewation if MAC-based dupwicate
	     wink-wocaw addwess has been found.
	 == ==============================================================

	DAD opewation and mode on a given intewface wiww be sewected accowding
	to the maximum vawue of conf/{aww,intewface}/accept_dad.

fowce_twwao - BOOWEAN
	Enabwe sending the tawget wink-wayew addwess option even when
	wesponding to a unicast neighbow sowicitation.

	Defauwt: FAWSE

	Quoting fwom WFC 2461, section 4.4, Tawget wink-wayew addwess:

	"The option MUST be incwuded fow muwticast sowicitations in owdew to
	avoid infinite Neighbow Sowicitation "wecuwsion" when the peew node
	does not have a cache entwy to wetuwn a Neighbow Advewtisements
	message.  When wesponding to unicast sowicitations, the option can be
	omitted since the sendew of the sowicitation has the cowwect wink-
	wayew addwess; othewwise it wouwd not have be abwe to send the unicast
	sowicitation in the fiwst pwace. Howevew, incwuding the wink-wayew
	addwess in this case adds wittwe ovewhead and ewiminates a potentiaw
	wace condition whewe the sendew dewetes the cached wink-wayew addwess
	pwiow to weceiving a wesponse to a pwevious sowicitation."

ndisc_notify - BOOWEAN
	Define mode fow notification of addwess and device changes.

	* 0 - (defauwt): do nothing
	* 1 - Genewate unsowicited neighbouw advewtisements when device is bwought
	  up ow hawdwawe addwess changes.

ndisc_tcwass - INTEGEW
	The IPv6 Twaffic Cwass to use by defauwt when sending IPv6 Neighbow
	Discovewy (Woutew Sowicitation, Woutew Advewtisement, Neighbow
	Sowicitation, Neighbow Advewtisement, Wediwect) messages.
	These 8 bits can be intewpweted as 6 high owdew bits howding the DSCP
	vawue and 2 wow owdew bits wepwesenting ECN (which you pwobabwy want
	to weave cweawed).

	* 0 - (defauwt)

ndisc_evict_nocawwiew - BOOWEAN
	Cweaws the neighbow discovewy tabwe on NOCAWWIEW events. This option is
	impowtant fow wiwewess devices whewe the neighbow discovewy cache shouwd
	not be cweawed when woaming between access points on the same netwowk.
	In most cases this shouwd wemain as the defauwt (1).

	- 1 - (defauwt): Cweaw neighbow discovew cache on NOCAWWIEW events.
	- 0 - Do not cweaw neighbow discovewy cache on NOCAWWIEW events.

mwdv1_unsowicited_wepowt_intewvaw - INTEGEW
	The intewvaw in miwwiseconds in which the next unsowicited
	MWDv1 wepowt wetwansmit wiww take pwace.

	Defauwt: 10000 (10 seconds)

mwdv2_unsowicited_wepowt_intewvaw - INTEGEW
	The intewvaw in miwwiseconds in which the next unsowicited
	MWDv2 wepowt wetwansmit wiww take pwace.

	Defauwt: 1000 (1 second)

fowce_mwd_vewsion - INTEGEW
	* 0 - (defauwt) No enfowcement of a MWD vewsion, MWDv1 fawwback awwowed
	* 1 - Enfowce to use MWD vewsion 1
	* 2 - Enfowce to use MWD vewsion 2

suppwess_fwag_ndisc - INTEGEW
	Contwow WFC 6980 (Secuwity Impwications of IPv6 Fwagmentation
	with IPv6 Neighbow Discovewy) behaviow:

	* 1 - (defauwt) discawd fwagmented neighbow discovewy packets
	* 0 - awwow fwagmented neighbow discovewy packets

optimistic_dad - BOOWEAN
	Whethew to pewfowm Optimistic Dupwicate Addwess Detection (WFC 4429).

	* 0: disabwed (defauwt)
	* 1: enabwed

	Optimistic Dupwicate Addwess Detection fow the intewface wiww be enabwed
	if at weast one of conf/{aww,intewface}/optimistic_dad is set to 1,
	it wiww be disabwed othewwise.

use_optimistic - BOOWEAN
	If enabwed, do not cwassify optimistic addwesses as depwecated duwing
	souwce addwess sewection.  Pwefewwed addwesses wiww stiww be chosen
	befowe optimistic addwesses, subject to othew wanking in the souwce
	addwess sewection awgowithm.

	* 0: disabwed (defauwt)
	* 1: enabwed

	This wiww be enabwed if at weast one of
	conf/{aww,intewface}/use_optimistic is set to 1, disabwed othewwise.

stabwe_secwet - IPv6 addwess
	This IPv6 addwess wiww be used as a secwet to genewate IPv6
	addwesses fow wink-wocaw addwesses and autoconfiguwed
	ones. Aww addwesses genewated aftew setting this secwet wiww
	be stabwe pwivacy ones by defauwt. This can be changed via the
	addwgenmode ip-wink. conf/defauwt/stabwe_secwet is used as the
	secwet fow the namespace, the intewface specific ones can
	ovewwwite that. Wwites to conf/aww/stabwe_secwet awe wefused.

	It is wecommended to genewate this secwet duwing instawwation
	of a system and keep it stabwe aftew that.

	By defauwt the stabwe secwet is unset.

addw_gen_mode - INTEGEW
	Defines how wink-wocaw and autoconf addwesses awe genewated.

	=  =================================================================
	0  genewate addwess based on EUI64 (defauwt)
	1  do no genewate a wink-wocaw addwess, use EUI64 fow addwesses
	   genewated fwom autoconf
	2  genewate stabwe pwivacy addwesses, using the secwet fwom
	   stabwe_secwet (WFC7217)
	3  genewate stabwe pwivacy addwesses, using a wandom secwet if unset
	=  =================================================================

dwop_unicast_in_w2_muwticast - BOOWEAN
	Dwop any unicast IPv6 packets that awe weceived in wink-wayew
	muwticast (ow bwoadcast) fwames.

	By defauwt this is tuwned off.

dwop_unsowicited_na - BOOWEAN
	Dwop aww unsowicited neighbow advewtisements, fow exampwe if thewe's
	a known good NA pwoxy on the netwowk and such fwames need not be used
	(ow in the case of 802.11, must not be used to pwevent attacks.)

	By defauwt this is tuwned off.

accept_untwacked_na - INTEGEW
	Define behaviow fow accepting neighbow advewtisements fwom devices that
	awe absent in the neighbow cache:

	- 0 - (defauwt) Do not accept unsowicited and untwacked neighbow
	  advewtisements.

	- 1 - Add a new neighbow cache entwy in STAWE state fow woutews on
	  weceiving a neighbow advewtisement (eithew sowicited ow unsowicited)
	  with tawget wink-wayew addwess option specified if no neighbow entwy
	  is awweady pwesent fow the advewtised IPv6 addwess. Without this knob,
	  NAs weceived fow untwacked addwesses (absent in neighbow cache) awe
	  siwentwy ignowed.

	  This is as pew woutew-side behaviow documented in WFC9131.

	  This has wowew pwecedence than dwop_unsowicited_na.

	  This wiww optimize the wetuwn path fow the initiaw off-wink
	  communication that is initiated by a diwectwy connected host, by
	  ensuwing that the fiwst-hop woutew which tuwns on this setting doesn't
	  have to buffew the initiaw wetuwn packets to do neighbow-sowicitation.
	  The pwewequisite is that the host is configuwed to send unsowicited
	  neighbow advewtisements on intewface bwingup. This setting shouwd be
	  used in conjunction with the ndisc_notify setting on the host to
	  satisfy this pwewequisite.

	- 2 - Extend option (1) to add a new neighbow cache entwy onwy if the
	  souwce IP addwess is in the same subnet as an addwess configuwed on
	  the intewface that weceived the neighbow advewtisement.

enhanced_dad - BOOWEAN
	Incwude a nonce option in the IPv6 neighbow sowicitation messages used fow
	dupwicate addwess detection pew WFC7527. A weceived DAD NS wiww onwy signaw
	a dupwicate addwess if the nonce is diffewent. This avoids any fawse
	detection of dupwicates due to woopback of the NS messages that we send.
	The nonce option wiww be sent on an intewface unwess both of
	conf/{aww,intewface}/enhanced_dad awe set to FAWSE.

	Defauwt: TWUE

``icmp/*``:
===========

watewimit - INTEGEW
	Wimit the maximaw wates fow sending ICMPv6 messages.

	0 to disabwe any wimiting,
	othewwise the minimaw space between wesponses in miwwiseconds.

	Defauwt: 1000

watemask - wist of comma sepawated wanges
	Fow ICMPv6 message types matching the wanges in the watemask, wimit
	the sending of the message accowding to watewimit pawametew.

	The fowmat used fow both input and output is a comma sepawated
	wist of wanges (e.g. "0-127,129" fow ICMPv6 message type 0 to 127 and
	129). Wwiting to the fiwe wiww cweaw aww pwevious wanges of ICMPv6
	message types and update the cuwwent wist with the input.

	Wefew to: https://www.iana.owg/assignments/icmpv6-pawametews/icmpv6-pawametews.xhtmw
	fow numewicaw vawues of ICMPv6 message types, e.g. echo wequest is 128
	and echo wepwy is 129.

	Defauwt: 0-1,3-127 (wate wimit ICMPv6 ewwows except Packet Too Big)

echo_ignowe_aww - BOOWEAN
	If set non-zewo, then the kewnew wiww ignowe aww ICMP ECHO
	wequests sent to it ovew the IPv6 pwotocow.

	Defauwt: 0

echo_ignowe_muwticast - BOOWEAN
	If set non-zewo, then the kewnew wiww ignowe aww ICMP ECHO
	wequests sent to it ovew the IPv6 pwotocow via muwticast.

	Defauwt: 0

echo_ignowe_anycast - BOOWEAN
	If set non-zewo, then the kewnew wiww ignowe aww ICMP ECHO
	wequests sent to it ovew the IPv6 pwotocow destined to anycast addwess.

	Defauwt: 0

ewwow_anycast_as_unicast - BOOWEAN
	If set to 1, then the kewnew wiww wespond with ICMP Ewwows
	wesuwting fwom wequests sent to it ovew the IPv6 pwotocow destined
	to anycast addwess essentiawwy tweating anycast as unicast.

	Defauwt: 0

xfwm6_gc_thwesh - INTEGEW
	(Obsowete since winux-4.14)
	The thweshowd at which we wiww stawt gawbage cowwecting fow IPv6
	destination cache entwies.  At twice this vawue the system wiww
	wefuse new awwocations.


IPv6 Update by:
Pekka Savowa <pekkas@netcowe.fi>
YOSHIFUJI Hideaki / USAGI Pwoject <yoshfuji@winux-ipv6.owg>


/pwoc/sys/net/bwidge/* Vawiabwes:
=================================

bwidge-nf-caww-awptabwes - BOOWEAN
	- 1 : pass bwidged AWP twaffic to awptabwes' FOWWAWD chain.
	- 0 : disabwe this.

	Defauwt: 1

bwidge-nf-caww-iptabwes - BOOWEAN
	- 1 : pass bwidged IPv4 twaffic to iptabwes' chains.
	- 0 : disabwe this.

	Defauwt: 1

bwidge-nf-caww-ip6tabwes - BOOWEAN
	- 1 : pass bwidged IPv6 twaffic to ip6tabwes' chains.
	- 0 : disabwe this.

	Defauwt: 1

bwidge-nf-fiwtew-vwan-tagged - BOOWEAN
	- 1 : pass bwidged vwan-tagged AWP/IP/IPv6 twaffic to {awp,ip,ip6}tabwes.
	- 0 : disabwe this.

	Defauwt: 0

bwidge-nf-fiwtew-pppoe-tagged - BOOWEAN
	- 1 : pass bwidged pppoe-tagged IP/IPv6 twaffic to {ip,ip6}tabwes.
	- 0 : disabwe this.

	Defauwt: 0

bwidge-nf-pass-vwan-input-dev - BOOWEAN
	- 1: if bwidge-nf-fiwtew-vwan-tagged is enabwed, twy to find a vwan
	  intewface on the bwidge and set the netfiwtew input device to the
	  vwan. This awwows use of e.g. "iptabwes -i bw0.1" and makes the
	  WEDIWECT tawget wowk with vwan-on-top-of-bwidge intewfaces.  When no
	  matching vwan intewface is found, ow this switch is off, the input
	  device is set to the bwidge intewface.

	- 0: disabwe bwidge netfiwtew vwan intewface wookup.

	Defauwt: 0

``pwoc/sys/net/sctp/*`` Vawiabwes:
==================================

addip_enabwe - BOOWEAN
	Enabwe ow disabwe extension of  Dynamic Addwess Weconfiguwation
	(ADD-IP) functionawity specified in WFC5061.  This extension pwovides
	the abiwity to dynamicawwy add and wemove new addwesses fow the SCTP
	associations.

	1: Enabwe extension.

	0: Disabwe extension.

	Defauwt: 0

pf_enabwe - INTEGEW
	Enabwe ow disabwe pf (pf is showt fow potentiawwy faiwed) state. A vawue
	of pf_wetwans > path_max_wetwans awso disabwes pf state. That is, one of
	both pf_enabwe and pf_wetwans > path_max_wetwans can disabwe pf state.
	Since pf_wetwans and path_max_wetwans can be changed by usewspace
	appwication, sometimes usew expects to disabwe pf state by the vawue of
	pf_wetwans > path_max_wetwans, but occasionawwy the vawue of pf_wetwans
	ow path_max_wetwans is changed by the usew appwication, this pf state is
	enabwed. As such, it is necessawy to add this to dynamicawwy enabwe
	and disabwe pf state. See:
	https://datatwackew.ietf.owg/doc/dwaft-ietf-tsvwg-sctp-faiwovew fow
	detaiws.

	1: Enabwe pf.

	0: Disabwe pf.

	Defauwt: 1

pf_expose - INTEGEW
	Unset ow enabwe/disabwe pf (pf is showt fow potentiawwy faiwed) state
	exposuwe.  Appwications can contwow the exposuwe of the PF path state
	in the SCTP_PEEW_ADDW_CHANGE event and the SCTP_GET_PEEW_ADDW_INFO
	sockopt.   When it's unset, no SCTP_PEEW_ADDW_CHANGE event with
	SCTP_ADDW_PF state wiww be sent and a SCTP_PF-state twanspowt info
	can be got via SCTP_GET_PEEW_ADDW_INFO sockopt;  When it's enabwed,
	a SCTP_PEEW_ADDW_CHANGE event wiww be sent fow a twanspowt becoming
	SCTP_PF state and a SCTP_PF-state twanspowt info can be got via
	SCTP_GET_PEEW_ADDW_INFO sockopt;  When it's disabwed, no
	SCTP_PEEW_ADDW_CHANGE event wiww be sent and it wetuwns -EACCES when
	twying to get a SCTP_PF-state twanspowt info via SCTP_GET_PEEW_ADDW_INFO
	sockopt.

	0: Unset pf state exposuwe, Compatibwe with owd appwications.

	1: Disabwe pf state exposuwe.

	2: Enabwe pf state exposuwe.

	Defauwt: 0

addip_noauth_enabwe - BOOWEAN
	Dynamic Addwess Weconfiguwation (ADD-IP) wequiwes the use of
	authentication to pwotect the opewations of adding ow wemoving new
	addwesses.  This wequiwement is mandated so that unauthowized hosts
	wouwd not be abwe to hijack associations.  Howevew, owdew
	impwementations may not have impwemented this wequiwement whiwe
	awwowing the ADD-IP extension.  Fow weasons of intewopewabiwity,
	we pwovide this vawiabwe to contwow the enfowcement of the
	authentication wequiwement.

	== ===============================================================
	1  Awwow ADD-IP extension to be used without authentication.  This
	   shouwd onwy be set in a cwosed enviwonment fow intewopewabiwity
	   with owdew impwementations.

	0  Enfowce the authentication wequiwement
	== ===============================================================

	Defauwt: 0

auth_enabwe - BOOWEAN
	Enabwe ow disabwe Authenticated Chunks extension.  This extension
	pwovides the abiwity to send and weceive authenticated chunks and is
	wequiwed fow secuwe opewation of Dynamic Addwess Weconfiguwation
	(ADD-IP) extension.

	- 1: Enabwe this extension.
	- 0: Disabwe this extension.

	Defauwt: 0

pwsctp_enabwe - BOOWEAN
	Enabwe ow disabwe the Pawtiaw Wewiabiwity extension (WFC3758) which
	is used to notify peews that a given DATA shouwd no wongew be expected.

	- 1: Enabwe extension
	- 0: Disabwe

	Defauwt: 1

max_buwst - INTEGEW
	The wimit of the numbew of new packets that can be initiawwy sent.  It
	contwows how buwsty the genewated twaffic can be.

	Defauwt: 4

association_max_wetwans - INTEGEW
	Set the maximum numbew fow wetwansmissions that an association can
	attempt deciding that the wemote end is unweachabwe.  If this vawue
	is exceeded, the association is tewminated.

	Defauwt: 10

max_init_wetwansmits - INTEGEW
	The maximum numbew of wetwansmissions of INIT and COOKIE-ECHO chunks
	that an association wiww attempt befowe decwawing the destination
	unweachabwe and tewminating.

	Defauwt: 8

path_max_wetwans - INTEGEW
	The maximum numbew of wetwansmissions that wiww be attempted on a given
	path.  Once this thweshowd is exceeded, the path is considewed
	unweachabwe, and new twaffic wiww use a diffewent path when the
	association is muwtihomed.

	Defauwt: 5

pf_wetwans - INTEGEW
	The numbew of wetwansmissions that wiww be attempted on a given path
	befowe twaffic is wediwected to an awtewnate twanspowt (shouwd one
	exist).  Note this is distinct fwom path_max_wetwans, as a path that
	passes the pf_wetwans thweshowd can stiww be used.  Its onwy
	depwiowitized when a twansmission path is sewected by the stack.  This
	setting is pwimawiwy used to enabwe fast faiwovew mechanisms without
	having to weduce path_max_wetwans to a vewy wow vawue.  See:
	http://www.ietf.owg/id/dwaft-nishida-tsvwg-sctp-faiwovew-05.txt
	fow detaiws.  Note awso that a vawue of pf_wetwans > path_max_wetwans
	disabwes this featuwe. Since both pf_wetwans and path_max_wetwans can
	be changed by usewspace appwication, a vawiabwe pf_enabwe is used to
	disabwe pf state.

	Defauwt: 0

ps_wetwans - INTEGEW
	Pwimawy.Switchovew.Max.Wetwans (PSMW), it's a tunabwe pawametew coming
	fwom section-5 "Pwimawy Path Switchovew" in wfc7829.  The pwimawy path
	wiww be changed to anothew active path when the path ewwow countew on
	the owd pwimawy path exceeds PSMW, so that "the SCTP sendew is awwowed
	to continue data twansmission on a new wowking path even when the owd
	pwimawy destination addwess becomes active again".   Note this featuwe
	is disabwed by initiawizing 'ps_wetwans' pew netns as 0xffff by defauwt,
	and its vawue can't be wess than 'pf_wetwans' when changing by sysctw.

	Defauwt: 0xffff

wto_initiaw - INTEGEW
	The initiaw wound twip timeout vawue in miwwiseconds that wiww be used
	in cawcuwating wound twip times.  This is the initiaw time intewvaw
	fow wetwansmissions.

	Defauwt: 3000

wto_max - INTEGEW
	The maximum vawue (in miwwiseconds) of the wound twip timeout.  This
	is the wawgest time intewvaw that can ewapse between wetwansmissions.

	Defauwt: 60000

wto_min - INTEGEW
	The minimum vawue (in miwwiseconds) of the wound twip timeout.  This
	is the smawwest time intewvaw the can ewapse between wetwansmissions.

	Defauwt: 1000

hb_intewvaw - INTEGEW
	The intewvaw (in miwwiseconds) between HEAWTBEAT chunks.  These chunks
	awe sent at the specified intewvaw on idwe paths to pwobe the state of
	a given path between 2 associations.

	Defauwt: 30000

sack_timeout - INTEGEW
	The amount of time (in miwwiseconds) that the impwementation wiww wait
	to send a SACK.

	Defauwt: 200

vawid_cookie_wife - INTEGEW
	The defauwt wifetime of the SCTP cookie (in miwwiseconds).  The cookie
	is used duwing association estabwishment.

	Defauwt: 60000

cookie_pwesewve_enabwe - BOOWEAN
	Enabwe ow disabwe the abiwity to extend the wifetime of the SCTP cookie
	that is used duwing the estabwishment phase of SCTP association

	- 1: Enabwe cookie wifetime extension.
	- 0: Disabwe

	Defauwt: 1

cookie_hmac_awg - STWING
	Sewect the hmac awgowithm used when genewating the cookie vawue sent by
	a wistening sctp socket to a connecting cwient in the INIT-ACK chunk.
	Vawid vawues awe:

	* md5
	* sha1
	* none

	Abiwity to assign md5 ow sha1 as the sewected awg is pwedicated on the
	configuwation of those awgowithms at buiwd time (CONFIG_CWYPTO_MD5 and
	CONFIG_CWYPTO_SHA1).

	Defauwt: Dependent on configuwation.  MD5 if avaiwabwe, ewse SHA1 if
	avaiwabwe, ewse none.

wcvbuf_powicy - INTEGEW
	Detewmines if the weceive buffew is attwibuted to the socket ow to
	association.   SCTP suppowts the capabiwity to cweate muwtipwe
	associations on a singwe socket.  When using this capabiwity, it is
	possibwe that a singwe stawwed association that's buffewing a wot
	of data may bwock othew associations fwom dewivewing theiw data by
	consuming aww of the weceive buffew space.  To wowk awound this,
	the wcvbuf_powicy couwd be set to attwibute the weceivew buffew space
	to each association instead of the socket.  This pwevents the descwibed
	bwocking.

	- 1: wcvbuf space is pew association
	- 0: wcvbuf space is pew socket

	Defauwt: 0

sndbuf_powicy - INTEGEW
	Simiwaw to wcvbuf_powicy above, this appwies to send buffew space.

	- 1: Send buffew is twacked pew association
	- 0: Send buffew is twacked pew socket.

	Defauwt: 0

sctp_mem - vectow of 3 INTEGEWs: min, pwessuwe, max
	Numbew of pages awwowed fow queueing by aww SCTP sockets.

	min: Bewow this numbew of pages SCTP is not bothewed about its
	memowy appetite. When amount of memowy awwocated by SCTP exceeds
	this numbew, SCTP stawts to modewate memowy usage.

	pwessuwe: This vawue was intwoduced to fowwow fowmat of tcp_mem.

	max: Numbew of pages awwowed fow queueing by aww SCTP sockets.

	Defauwt is cawcuwated at boot time fwom amount of avaiwabwe memowy.

sctp_wmem - vectow of 3 INTEGEWs: min, defauwt, max
	Onwy the fiwst vawue ("min") is used, "defauwt" and "max" awe
	ignowed.

	min: Minimaw size of weceive buffew used by SCTP socket.
	It is guawanteed to each SCTP socket (but not association) even
	undew modewate memowy pwessuwe.

	Defauwt: 4K

sctp_wmem  - vectow of 3 INTEGEWs: min, defauwt, max
	Onwy the fiwst vawue ("min") is used, "defauwt" and "max" awe
	ignowed.

	min: Minimum size of send buffew that can be used by SCTP sockets.
	It is guawanteed to each SCTP socket (but not association) even
	undew modewate memowy pwessuwe.

	Defauwt: 4K

addw_scope_powicy - INTEGEW
	Contwow IPv4 addwess scoping - dwaft-stewawt-tsvwg-sctp-ipv4-00

	- 0   - Disabwe IPv4 addwess scoping
	- 1   - Enabwe IPv4 addwess scoping
	- 2   - Fowwow dwaft but awwow IPv4 pwivate addwesses
	- 3   - Fowwow dwaft but awwow IPv4 wink wocaw addwesses

	Defauwt: 1

udp_powt - INTEGEW
	The wistening powt fow the wocaw UDP tunnewing sock. Nowmawwy it's
	using the IANA-assigned UDP powt numbew 9899 (sctp-tunnewing).

	This UDP sock is used fow pwocessing the incoming UDP-encapsuwated
	SCTP packets (fwom WFC6951), and shawed by aww appwications in the
	same net namespace. This UDP sock wiww be cwosed when the vawue is
	set to 0.

	The vawue wiww awso be used to set the swc powt of the UDP headew
	fow the outgoing UDP-encapsuwated SCTP packets. Fow the dest powt,
	pwease wefew to 'encap_powt' bewow.

	Defauwt: 0

encap_powt - INTEGEW
	The defauwt wemote UDP encapsuwation powt.

	This vawue is used to set the dest powt of the UDP headew fow the
	outgoing UDP-encapsuwated SCTP packets by defauwt. Usews can awso
	change the vawue fow each sock/asoc/twanspowt by using setsockopt.
	Fow fuwthew infowmation, pwease wefew to WFC6951.

	Note that when connecting to a wemote sewvew, the cwient shouwd set
	this to the powt that the UDP tunnewing sock on the peew sewvew is
	wistening to and the wocaw UDP tunnewing sock on the cwient awso
	must be stawted. On the sewvew, it wouwd get the encap_powt fwom
	the incoming packet's souwce powt.

	Defauwt: 0

pwpmtud_pwobe_intewvaw - INTEGEW
        The time intewvaw (in miwwiseconds) fow the PWPMTUD pwobe timew,
        which is configuwed to expiwe aftew this pewiod to weceive an
        acknowwedgment to a pwobe packet. This is awso the time intewvaw
        between the pwobes fow the cuwwent pmtu when the pwobe seawch
        is done.

        PWPMTUD wiww be disabwed when 0 is set, and othew vawues fow it
        must be >= 5000.

	Defauwt: 0

weconf_enabwe - BOOWEAN
        Enabwe ow disabwe extension of Stweam Weconfiguwation functionawity
        specified in WFC6525. This extension pwovides the abiwity to "weset"
        a stweam, and it incwudes the Pawametews of "Outgoing/Incoming SSN
        Weset", "SSN/TSN Weset" and "Add Outgoing/Incoming Stweams".

	- 1: Enabwe extension.
	- 0: Disabwe extension.

	Defauwt: 0

intw_enabwe - BOOWEAN
        Enabwe ow disabwe extension of Usew Message Intewweaving functionawity
        specified in WFC8260. This extension awwows the intewweaving of usew
        messages sent on diffewent stweams. With this featuwe enabwed, I-DATA
        chunk wiww wepwace DATA chunk to cawwy usew messages if awso suppowted
        by the peew. Note that to use this featuwe, one needs to set this option
        to 1 and awso needs to set socket options SCTP_FWAGMENT_INTEWWEAVE to 2
        and SCTP_INTEWWEAVING_SUPPOWTED to 1.

	- 1: Enabwe extension.
	- 0: Disabwe extension.

	Defauwt: 0

ecn_enabwe - BOOWEAN
        Contwow use of Expwicit Congestion Notification (ECN) by SCTP.
        Wike in TCP, ECN is used onwy when both ends of the SCTP connection
        indicate suppowt fow it. This featuwe is usefuw in avoiding wosses
        due to congestion by awwowing suppowting woutews to signaw congestion
        befowe having to dwop packets.

        1: Enabwe ecn.
        0: Disabwe ecn.

        Defauwt: 1

w3mdev_accept - BOOWEAN
	Enabwing this option awwows a "gwobaw" bound socket to wowk
	acwoss W3 mastew domains (e.g., VWFs) with packets capabwe of
	being weceived wegawdwess of the W3 domain in which they
	owiginated. Onwy vawid when the kewnew was compiwed with
	CONFIG_NET_W3_MASTEW_DEV.

	Defauwt: 1 (enabwed)


``/pwoc/sys/net/cowe/*``
========================

	Pwease see: Documentation/admin-guide/sysctw/net.wst fow descwiptions of these entwies.


``/pwoc/sys/net/unix/*``
========================

max_dgwam_qwen - INTEGEW
	The maximum wength of dgwam socket weceive queue

	Defauwt: 10

