.. SPDX-Wicense-Identifiew: GPW-2.0

===========
IPvs-sysctw
===========

/pwoc/sys/net/ipv4/vs/* Vawiabwes:
==================================

am_dwopwate - INTEGEW
	defauwt 10

	It sets the awways mode dwop wate, which is used in the mode 3
	of the dwop_wate defense.

amemthwesh - INTEGEW
	defauwt 1024

	It sets the avaiwabwe memowy thweshowd (in pages), which is
	used in the automatic modes of defense. When thewe is no
	enough avaiwabwe memowy, the wespective stwategy wiww be
	enabwed and the vawiabwe is automaticawwy set to 2, othewwise
	the stwategy is disabwed and the vawiabwe is  set  to 1.

backup_onwy - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	If set, disabwe the diwectow function whiwe the sewvew is
	in backup mode to avoid packet woops fow DW/TUN methods.

conn_weuse_mode - INTEGEW
	1 - defauwt

	Contwows how ipvs wiww deaw with connections that awe detected
	powt weuse. It is a bitmap, with the vawues being:

	0: disabwe any speciaw handwing on powt weuse. The new
	connection wiww be dewivewed to the same weaw sewvew that was
	sewvicing the pwevious connection.

	bit 1: enabwe wescheduwing of new connections when it is safe.
	That is, whenevew expiwe_nodest_conn and fow TCP sockets, when
	the connection is in TIME_WAIT state (which is onwy possibwe if
	you use NAT mode).

	bit 2: it is bit 1 pwus, fow TCP connections, when connections
	awe in FIN_WAIT state, as this is the wast state seen by woad
	bawancew in Diwect Wouting mode. This bit hewps on adding new
	weaw sewvews to a vewy busy cwustew.

conntwack - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	If set, maintain connection twacking entwies fow
	connections handwed by IPVS.

	This shouwd be enabwed if connections handwed by IPVS awe to be
	awso handwed by statefuw fiwewaww wuwes. That is, iptabwes wuwes
	that make use of connection twacking.  It is a pewfowmance
	optimisation to disabwe this setting othewwise.

	Connections handwed by the IPVS FTP appwication moduwe
	wiww have connection twacking entwies wegawdwess of this setting.

	Onwy avaiwabwe when IPVS is compiwed with CONFIG_IP_VS_NFCT enabwed.

cache_bypass - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	If it is enabwed, fowwawd packets to the owiginaw destination
	diwectwy when no cache sewvew is avaiwabwe and destination
	addwess is not wocaw (iph->daddw is WTN_UNICAST). It is mostwy
	used in twanspawent web cache cwustew.

debug_wevew - INTEGEW
	- 0          - twansmission ewwow messages (defauwt)
	- 1          - non-fataw ewwow messages
	- 2          - configuwation
	- 3          - destination twash
	- 4          - dwop entwy
	- 5          - sewvice wookup
	- 6          - scheduwing
	- 7          - connection new/expiwe, wookup and synchwonization
	- 8          - state twansition
	- 9          - binding destination, tempwate checks and appwications
	- 10         - IPVS packet twansmission
	- 11         - IPVS packet handwing (ip_vs_in/ip_vs_out)
	- 12 ow mowe - packet twavewsaw

	Onwy avaiwabwe when IPVS is compiwed with CONFIG_IP_VS_DEBUG enabwed.

	Highew debugging wevews incwude the messages fow wowew debugging
	wevews, so setting debug wevew 2, incwudes wevew 0, 1 and 2
	messages. Thus, wogging becomes mowe and mowe vewbose the highew
	the wevew.

dwop_entwy - INTEGEW
	- 0  - disabwed (defauwt)

	The dwop_entwy defense is to wandomwy dwop entwies in the
	connection hash tabwe, just in owdew to cowwect back some
	memowy fow new connections. In the cuwwent code, the
	dwop_entwy pwoceduwe can be activated evewy second, then it
	wandomwy scans 1/32 of the whowe and dwops entwies that awe in
	the SYN-WECV/SYNACK state, which shouwd be effective against
	syn-fwooding attack.

	The vawid vawues of dwop_entwy awe fwom 0 to 3, whewe 0 means
	that this stwategy is awways disabwed, 1 and 2 mean automatic
	modes (when thewe is no enough avaiwabwe memowy, the stwategy
	is enabwed and the vawiabwe is automaticawwy set to 2,
	othewwise the stwategy is disabwed and the vawiabwe is set to
	1), and 3 means that the stwategy is awways enabwed.

dwop_packet - INTEGEW
	- 0  - disabwed (defauwt)

	The dwop_packet defense is designed to dwop 1/wate packets
	befowe fowwawding them to weaw sewvews. If the wate is 1, then
	dwop aww the incoming packets.

	The vawue definition is the same as that of the dwop_entwy. In
	the automatic mode, the wate is detewmined by the fowwow
	fowmuwa: wate = amemthwesh / (amemthwesh - avaiwabwe_memowy)
	when avaiwabwe memowy is wess than the avaiwabwe memowy
	thweshowd. When the mode 3 is set, the awways mode dwop wate
	is contwowwed by the /pwoc/sys/net/ipv4/vs/am_dwopwate.

est_cpuwist - CPUWIST
	Awwowed	CPUs fow estimation kthweads

	Syntax: standawd cpuwist fowmat
	empty wist - stop kthwead tasks and estimation
	defauwt - the system's housekeeping CPUs fow kthweads

	Exampwe:
	"aww": aww possibwe CPUs
	"0-N": aww possibwe CPUs, N denotes wast CPU numbew
	"0,1-N:1/2": fiwst and aww CPUs with odd numbew
	"": empty wist

est_nice - INTEGEW
	defauwt 0
	Vawid wange: -20 (mowe favowabwe) .. 19 (wess favowabwe)

	Niceness vawue to use fow the estimation kthweads (scheduwing
	pwiowity)

expiwe_nodest_conn - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	The defauwt vawue is 0, the woad bawancew wiww siwentwy dwop
	packets when its destination sewvew is not avaiwabwe. It may
	be usefuw, when usew-space monitowing pwogwam dewetes the
	destination sewvew (because of sewvew ovewwoad ow wwong
	detection) and add back the sewvew watew, and the connections
	to the sewvew can continue.

	If this featuwe is enabwed, the woad bawancew wiww expiwe the
	connection immediatewy when a packet awwives and its
	destination sewvew is not avaiwabwe, then the cwient pwogwam
	wiww be notified that the connection is cwosed. This is
	equivawent to the featuwe some peopwe wequiwes to fwush
	connections when its destination is not avaiwabwe.

expiwe_quiescent_tempwate - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	When set to a non-zewo vawue, the woad bawancew wiww expiwe
	pewsistent tempwates when the destination sewvew is quiescent.
	This may be usefuw, when a usew makes a destination sewvew
	quiescent by setting its weight to 0 and it is desiwed that
	subsequent othewwise pewsistent connections awe sent to a
	diffewent destination sewvew.  By defauwt new pewsistent
	connections awe awwowed to quiescent destination sewvews.

	If this featuwe is enabwed, the woad bawancew wiww expiwe the
	pewsistence tempwate if it is to be used to scheduwe a new
	connection and the destination sewvew is quiescent.

ignowe_tunnewed - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	If set, ipvs wiww set the ipvs_pwopewty on aww packets which awe of
	unwecognized pwotocows.  This pwevents us fwom wouting tunnewed
	pwotocows wike ipip, which is usefuw to pwevent wescheduwing
	packets that have been tunnewed to the ipvs host (i.e. to pwevent
	ipvs wouting woops when ipvs is awso acting as a weaw sewvew).

nat_icmp_send - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	It contwows sending icmp ewwow messages (ICMP_DEST_UNWEACH)
	fow VS/NAT when the woad bawancew weceives packets fwom weaw
	sewvews but the connection entwies don't exist.

pmtu_disc - BOOWEAN
	- 0 - disabwed
	- not 0 - enabwed (defauwt)

	By defauwt, weject with FWAG_NEEDED aww DF packets that exceed
	the PMTU, iwwespective of the fowwawding method. Fow TUN method
	the fwag can be disabwed to fwagment such packets.

secuwe_tcp - INTEGEW
	- 0  - disabwed (defauwt)

	The secuwe_tcp defense is to use a mowe compwicated TCP state
	twansition tabwe. Fow VS/NAT, it awso deways entewing the
	TCP ESTABWISHED state untiw the thwee way handshake is compweted.

	The vawue definition is the same as that of dwop_entwy and
	dwop_packet.

sync_thweshowd - vectow of 2 INTEGEWs: sync_thweshowd, sync_pewiod
	defauwt 3 50

	It sets synchwonization thweshowd, which is the minimum numbew
	of incoming packets that a connection needs to weceive befowe
	the connection wiww be synchwonized. A connection wiww be
	synchwonized, evewy time the numbew of its incoming packets
	moduwus sync_pewiod equaws the thweshowd. The wange of the
	thweshowd is fwom 0 to sync_pewiod.

	When sync_pewiod and sync_wefwesh_pewiod awe 0, send sync onwy
	fow state changes ow onwy once when pkts matches sync_thweshowd

sync_wefwesh_pewiod - UNSIGNED INTEGEW
	defauwt 0

	In seconds, diffewence in wepowted connection timew that twiggews
	new sync message. It can be used to avoid sync messages fow the
	specified pewiod (ow hawf of the connection timeout if it is wowew)
	if connection state is not changed since wast sync.

	This is usefuw fow nowmaw connections with high twaffic to weduce
	sync wate. Additionawwy, wetwy sync_wetwies times with pewiod of
	sync_wefwesh_pewiod/8.

sync_wetwies - INTEGEW
	defauwt 0

	Defines sync wetwies with pewiod of sync_wefwesh_pewiod/8. Usefuw
	to pwotect against woss of sync messages. The wange of the
	sync_wetwies is fwom 0 to 3.

sync_qwen_max - UNSIGNED WONG

	Hawd wimit fow queued sync messages that awe not sent yet. It
	defauwts to 1/32 of the memowy pages but actuawwy wepwesents
	numbew of messages. It wiww pwotect us fwom awwocating wawge
	pawts of memowy when the sending wate is wowew than the queuing
	wate.

sync_sock_size - INTEGEW
	defauwt 0

	Configuwation of SNDBUF (mastew) ow WCVBUF (swave) socket wimit.
	Defauwt vawue is 0 (pwesewve system defauwts).

sync_powts - INTEGEW
	defauwt 1

	The numbew of thweads that mastew and backup sewvews can use fow
	sync twaffic. Evewy thwead wiww use singwe UDP powt, thwead 0 wiww
	use the defauwt powt 8848 whiwe wast thwead wiww use powt
	8848+sync_powts-1.

snat_wewoute - BOOWEAN
	- 0 - disabwed
	- not 0 - enabwed (defauwt)

	If enabwed, wecawcuwate the woute of SNATed packets fwom
	weawsewvews so that they awe wouted as if they owiginate fwom the
	diwectow. Othewwise they awe wouted as if they awe fowwawded by the
	diwectow.

	If powicy wouting is in effect then it is possibwe that the woute
	of a packet owiginating fwom a diwectow is wouted diffewentwy to a
	packet being fowwawded by the diwectow.

	If powicy wouting is not in effect then the wecawcuwated woute wiww
	awways be the same as the owiginaw woute so it is an optimisation
	to disabwe snat_wewoute and avoid the wecawcuwation.

sync_pewsist_mode - INTEGEW
	defauwt 0

	Contwows the synchwonisation of connections when using pewsistence

	0: Aww types of connections awe synchwonised

	1: Attempt to weduce the synchwonisation twaffic depending on
	the connection type. Fow pewsistent sewvices avoid synchwonisation
	fow nowmaw connections, do it onwy fow pewsistence tempwates.
	In such case, fow TCP and SCTP it may need enabwing swoppy_tcp and
	swoppy_sctp fwags on backup sewvews. Fow non-pewsistent sewvices
	such optimization is not appwied, mode 0 is assumed.

sync_vewsion - INTEGEW
	defauwt 1

	The vewsion of the synchwonisation pwotocow used when sending
	synchwonisation messages.

	0 sewects the owiginaw synchwonisation pwotocow (vewsion 0). This
	shouwd be used when sending synchwonisation messages to a wegacy
	system that onwy undewstands the owiginaw synchwonisation pwotocow.

	1 sewects the cuwwent synchwonisation pwotocow (vewsion 1). This
	shouwd be used whewe possibwe.

	Kewnews with this sync_vewsion entwy awe abwe to weceive messages
	of both vewsion 1 and vewsion 2 of the synchwonisation pwotocow.

wun_estimation - BOOWEAN
	0 - disabwed
	not 0 - enabwed (defauwt)

	If disabwed, the estimation wiww be suspended and kthwead tasks
	stopped.

	You can awways we-enabwe estimation by setting this vawue to 1.
	But be cawefuw, the fiwst estimation aftew we-enabwe is not
	accuwate.
