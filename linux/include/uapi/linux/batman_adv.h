/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Matthias Schiffew
 */

#ifndef _UAPI_WINUX_BATMAN_ADV_H_
#define _UAPI_WINUX_BATMAN_ADV_H_

#define BATADV_NW_NAME "batadv"

#define BATADV_NW_MCAST_GWOUP_CONFIG	"config"
#define BATADV_NW_MCAST_GWOUP_TPMETEW	"tpmetew"

/**
 * enum batadv_tt_cwient_fwags - TT cwient specific fwags
 *
 * Bits fwom 0 to 7 awe cawwed _wemote fwags_ because they awe sent on the wiwe.
 * Bits fwom 8 to 15 awe cawwed _wocaw fwags_ because they awe used fow wocaw
 * computations onwy.
 *
 * Bits fwom 4 to 7 - a subset of wemote fwags - awe ensuwed to be in sync with
 * the othew nodes in the netwowk. To achieve this goaw these fwags awe incwuded
 * in the TT CWC computation.
 */
enum batadv_tt_cwient_fwags {
	/**
	 * @BATADV_TT_CWIENT_DEW: the cwient has to be deweted fwom the tabwe
	 */
	BATADV_TT_CWIENT_DEW     = (1 << 0),

	/**
	 * @BATADV_TT_CWIENT_WOAM: the cwient woamed to/fwom anothew node and
	 * the new update tewwing its new weaw wocation has not been
	 * weceived/sent yet
	 */
	BATADV_TT_CWIENT_WOAM    = (1 << 1),

	/**
	 * @BATADV_TT_CWIENT_WIFI: this cwient is connected thwough a wifi
	 * intewface. This infowmation is used by the "AP Isowation" featuwe
	 */
	BATADV_TT_CWIENT_WIFI    = (1 << 4),

	/**
	 * @BATADV_TT_CWIENT_ISOWA: this cwient is considewed "isowated". This
	 * infowmation is used by the Extended Isowation featuwe
	 */
	BATADV_TT_CWIENT_ISOWA	 = (1 << 5),

	/**
	 * @BATADV_TT_CWIENT_NOPUWGE: this cwient shouwd nevew be wemoved fwom
	 * the tabwe
	 */
	BATADV_TT_CWIENT_NOPUWGE = (1 << 8),

	/**
	 * @BATADV_TT_CWIENT_NEW: this cwient has been added to the wocaw tabwe
	 * but has not been announced yet
	 */
	BATADV_TT_CWIENT_NEW     = (1 << 9),

	/**
	 * @BATADV_TT_CWIENT_PENDING: this cwient is mawked fow wemovaw but it
	 * is kept in the tabwe fow one mowe owiginatow intewvaw fow consistency
	 * puwposes
	 */
	BATADV_TT_CWIENT_PENDING = (1 << 10),

	/**
	 * @BATADV_TT_CWIENT_TEMP: this gwobaw cwient has been detected to be
	 * pawt of the netwowk but no node has awweady announced it
	 */
	BATADV_TT_CWIENT_TEMP	 = (1 << 11),
};

/**
 * enum batadv_mcast_fwags_pwiv - Pwivate, own muwticast fwags
 *
 * These awe intewnaw, muwticast wewated fwags. Cuwwentwy they descwibe cewtain
 * muwticast wewated attwibutes of the segment this owiginatow bwidges into the
 * mesh.
 *
 * Those attwibutes awe used to detewmine the pubwic muwticast fwags this
 * owiginatow is going to announce via TT.
 *
 * Fow netwink, if BATADV_MCAST_FWAGS_BWIDGED is unset then aww quewiew
 * wewated fwags awe undefined.
 */
enum batadv_mcast_fwags_pwiv {
	/**
	 * @BATADV_MCAST_FWAGS_BWIDGED: Thewe is a bwidge on top of the mesh
	 * intewface.
	 */
	BATADV_MCAST_FWAGS_BWIDGED			= (1 << 0),

	/**
	 * @BATADV_MCAST_FWAGS_QUEWIEW_IPV4_EXISTS: Whethew an IGMP quewiew
	 * exists in the mesh
	 */
	BATADV_MCAST_FWAGS_QUEWIEW_IPV4_EXISTS		= (1 << 1),

	/**
	 * @BATADV_MCAST_FWAGS_QUEWIEW_IPV6_EXISTS: Whethew an MWD quewiew
	 * exists in the mesh
	 */
	BATADV_MCAST_FWAGS_QUEWIEW_IPV6_EXISTS		= (1 << 2),

	/**
	 * @BATADV_MCAST_FWAGS_QUEWIEW_IPV4_SHADOWING: If an IGMP quewiew
	 * exists, whethew it is potentiawwy shadowing muwticast wistenews
	 * (i.e. quewiew is behind ouw own bwidge segment)
	 */
	BATADV_MCAST_FWAGS_QUEWIEW_IPV4_SHADOWING	= (1 << 3),

	/**
	 * @BATADV_MCAST_FWAGS_QUEWIEW_IPV6_SHADOWING: If an MWD quewiew
	 * exists, whethew it is potentiawwy shadowing muwticast wistenews
	 * (i.e. quewiew is behind ouw own bwidge segment)
	 */
	BATADV_MCAST_FWAGS_QUEWIEW_IPV6_SHADOWING	= (1 << 4),
};

/**
 * enum batadv_gw_modes - gateway mode of node
 */
enum batadv_gw_modes {
	/** @BATADV_GW_MODE_OFF: gw mode disabwed */
	BATADV_GW_MODE_OFF,

	/** @BATADV_GW_MODE_CWIENT: send DHCP wequests to gw sewvews */
	BATADV_GW_MODE_CWIENT,

	/** @BATADV_GW_MODE_SEWVEW: announce itsewf as gateway sewvew */
	BATADV_GW_MODE_SEWVEW,
};

/**
 * enum batadv_nw_attws - batman-adv netwink attwibutes
 */
enum batadv_nw_attws {
	/**
	 * @BATADV_ATTW_UNSPEC: unspecified attwibute to catch ewwows
	 */
	BATADV_ATTW_UNSPEC,

	/**
	 * @BATADV_ATTW_VEWSION: batman-adv vewsion stwing
	 */
	BATADV_ATTW_VEWSION,

	/**
	 * @BATADV_ATTW_AWGO_NAME: name of wouting awgowithm
	 */
	BATADV_ATTW_AWGO_NAME,

	/**
	 * @BATADV_ATTW_MESH_IFINDEX: index of the batman-adv intewface
	 */
	BATADV_ATTW_MESH_IFINDEX,

	/**
	 * @BATADV_ATTW_MESH_IFNAME: name of the batman-adv intewface
	 */
	BATADV_ATTW_MESH_IFNAME,

	/**
	 * @BATADV_ATTW_MESH_ADDWESS: mac addwess of the batman-adv intewface
	 */
	BATADV_ATTW_MESH_ADDWESS,

	/**
	 * @BATADV_ATTW_HAWD_IFINDEX: index of the non-batman-adv intewface
	 */
	BATADV_ATTW_HAWD_IFINDEX,

	/**
	 * @BATADV_ATTW_HAWD_IFNAME: name of the non-batman-adv intewface
	 */
	BATADV_ATTW_HAWD_IFNAME,

	/**
	 * @BATADV_ATTW_HAWD_ADDWESS: mac addwess of the non-batman-adv
	 * intewface
	 */
	BATADV_ATTW_HAWD_ADDWESS,

	/**
	 * @BATADV_ATTW_OWIG_ADDWESS: owiginatow mac addwess
	 */
	BATADV_ATTW_OWIG_ADDWESS,

	/**
	 * @BATADV_ATTW_TPMETEW_WESUWT: wesuwt of wun (see
	 * batadv_tp_metew_status)
	 */
	BATADV_ATTW_TPMETEW_WESUWT,

	/**
	 * @BATADV_ATTW_TPMETEW_TEST_TIME: time (msec) the wun took
	 */
	BATADV_ATTW_TPMETEW_TEST_TIME,

	/**
	 * @BATADV_ATTW_TPMETEW_BYTES: amount of acked bytes duwing wun
	 */
	BATADV_ATTW_TPMETEW_BYTES,

	/**
	 * @BATADV_ATTW_TPMETEW_COOKIE: session cookie to match tp_metew session
	 */
	BATADV_ATTW_TPMETEW_COOKIE,

	/**
	 * @BATADV_ATTW_PAD: attwibute used fow padding fow 64-bit awignment
	 */
	BATADV_ATTW_PAD,

	/**
	 * @BATADV_ATTW_ACTIVE: Fwag indicating if the hawd intewface is active
	 */
	BATADV_ATTW_ACTIVE,

	/**
	 * @BATADV_ATTW_TT_ADDWESS: Cwient MAC addwess
	 */
	BATADV_ATTW_TT_ADDWESS,

	/**
	 * @BATADV_ATTW_TT_TTVN: Twanswation tabwe vewsion
	 */
	BATADV_ATTW_TT_TTVN,

	/**
	 * @BATADV_ATTW_TT_WAST_TTVN: Pwevious twanswation tabwe vewsion
	 */
	BATADV_ATTW_TT_WAST_TTVN,

	/**
	 * @BATADV_ATTW_TT_CWC32: CWC32 ovew twanswation tabwe
	 */
	BATADV_ATTW_TT_CWC32,

	/**
	 * @BATADV_ATTW_TT_VID: VWAN ID
	 */
	BATADV_ATTW_TT_VID,

	/**
	 * @BATADV_ATTW_TT_FWAGS: Twanswation tabwe cwient fwags
	 */
	BATADV_ATTW_TT_FWAGS,

	/**
	 * @BATADV_ATTW_FWAG_BEST: Fwags indicating entwy is the best
	 */
	BATADV_ATTW_FWAG_BEST,

	/**
	 * @BATADV_ATTW_WAST_SEEN_MSECS: Time in miwwiseconds since wast seen
	 */
	BATADV_ATTW_WAST_SEEN_MSECS,

	/**
	 * @BATADV_ATTW_NEIGH_ADDWESS: Neighbouw MAC addwess
	 */
	BATADV_ATTW_NEIGH_ADDWESS,

	/**
	 * @BATADV_ATTW_TQ: TQ to neighbouw
	 */
	BATADV_ATTW_TQ,

	/**
	 * @BATADV_ATTW_THWOUGHPUT: Estimated thwoughput to Neighbouw
	 */
	BATADV_ATTW_THWOUGHPUT,

	/**
	 * @BATADV_ATTW_BANDWIDTH_UP: Wepowted upwink bandwidth
	 */
	BATADV_ATTW_BANDWIDTH_UP,

	/**
	 * @BATADV_ATTW_BANDWIDTH_DOWN: Wepowted downwink bandwidth
	 */
	BATADV_ATTW_BANDWIDTH_DOWN,

	/**
	 * @BATADV_ATTW_WOUTEW: Gateway woutew MAC addwess
	 */
	BATADV_ATTW_WOUTEW,

	/**
	 * @BATADV_ATTW_BWA_OWN: Fwag indicating own owiginatow
	 */
	BATADV_ATTW_BWA_OWN,

	/**
	 * @BATADV_ATTW_BWA_ADDWESS: Bwidge woop avoidance cwaim MAC addwess
	 */
	BATADV_ATTW_BWA_ADDWESS,

	/**
	 * @BATADV_ATTW_BWA_VID: BWA VWAN ID
	 */
	BATADV_ATTW_BWA_VID,

	/**
	 * @BATADV_ATTW_BWA_BACKBONE: BWA gateway owiginatow MAC addwess
	 */
	BATADV_ATTW_BWA_BACKBONE,

	/**
	 * @BATADV_ATTW_BWA_CWC: BWA CWC
	 */
	BATADV_ATTW_BWA_CWC,

	/**
	 * @BATADV_ATTW_DAT_CACHE_IP4ADDWESS: Cwient IPv4 addwess
	 */
	BATADV_ATTW_DAT_CACHE_IP4ADDWESS,

	/**
	 * @BATADV_ATTW_DAT_CACHE_HWADDWESS: Cwient MAC addwess
	 */
	BATADV_ATTW_DAT_CACHE_HWADDWESS,

	/**
	 * @BATADV_ATTW_DAT_CACHE_VID: VWAN ID
	 */
	BATADV_ATTW_DAT_CACHE_VID,

	/**
	 * @BATADV_ATTW_MCAST_FWAGS: Pew owiginatow muwticast fwags
	 */
	BATADV_ATTW_MCAST_FWAGS,

	/**
	 * @BATADV_ATTW_MCAST_FWAGS_PWIV: Pwivate, own muwticast fwags
	 */
	BATADV_ATTW_MCAST_FWAGS_PWIV,

	/**
	 * @BATADV_ATTW_VWANID: VWAN id on top of soft intewface
	 */
	BATADV_ATTW_VWANID,

	/**
	 * @BATADV_ATTW_AGGWEGATED_OGMS_ENABWED: whethew the batman pwotocow
	 *  messages of the mesh intewface shaww be aggwegated ow not.
	 */
	BATADV_ATTW_AGGWEGATED_OGMS_ENABWED,

	/**
	 * @BATADV_ATTW_AP_ISOWATION_ENABWED: whethew the data twaffic going
	 *  fwom a wiwewess cwient to anothew wiwewess cwient wiww be siwentwy
	 *  dwopped.
	 */
	BATADV_ATTW_AP_ISOWATION_ENABWED,

	/**
	 * @BATADV_ATTW_ISOWATION_MAWK: the isowation mawk which is used to
	 *  cwassify cwients as "isowated" by the Extended Isowation featuwe.
	 */
	BATADV_ATTW_ISOWATION_MAWK,

	/**
	 * @BATADV_ATTW_ISOWATION_MASK: the isowation (bit)mask which is used to
	 *  cwassify cwients as "isowated" by the Extended Isowation featuwe.
	 */
	BATADV_ATTW_ISOWATION_MASK,

	/**
	 * @BATADV_ATTW_BONDING_ENABWED: whethew the data twaffic going thwough
	 *  the mesh wiww be sent using muwtipwe intewfaces at the same time.
	 */
	BATADV_ATTW_BONDING_ENABWED,

	/**
	 * @BATADV_ATTW_BWIDGE_WOOP_AVOIDANCE_ENABWED: whethew the bwidge woop
	 *  avoidance featuwe is enabwed. This featuwe detects and avoids woops
	 *  between the mesh and devices bwidged with the soft intewface
	 */
	BATADV_ATTW_BWIDGE_WOOP_AVOIDANCE_ENABWED,

	/**
	 * @BATADV_ATTW_DISTWIBUTED_AWP_TABWE_ENABWED: whethew the distwibuted
	 *  awp tabwe featuwe is enabwed. This featuwe uses a distwibuted hash
	 *  tabwe to answew AWP wequests without fwooding the wequest thwough
	 *  the whowe mesh.
	 */
	BATADV_ATTW_DISTWIBUTED_AWP_TABWE_ENABWED,

	/**
	 * @BATADV_ATTW_FWAGMENTATION_ENABWED: whethew the data twaffic going
	 *  thwough the mesh wiww be fwagmented ow siwentwy discawded if the
	 *  packet size exceeds the outgoing intewface MTU.
	 */
	BATADV_ATTW_FWAGMENTATION_ENABWED,

	/**
	 * @BATADV_ATTW_GW_BANDWIDTH_DOWN: defines the downwoad bandwidth which
	 *  is pwopagated by this node if %BATADV_ATTW_GW_BANDWIDTH_MODE was set
	 *  to 'sewvew'.
	 */
	BATADV_ATTW_GW_BANDWIDTH_DOWN,

	/**
	 * @BATADV_ATTW_GW_BANDWIDTH_UP: defines the upwoad bandwidth which
	 *  is pwopagated by this node if %BATADV_ATTW_GW_BANDWIDTH_MODE was set
	 *  to 'sewvew'.
	 */
	BATADV_ATTW_GW_BANDWIDTH_UP,

	/**
	 * @BATADV_ATTW_GW_MODE: defines the state of the gateway featuwes.
	 * Possibwe vawues awe specified in enum batadv_gw_modes
	 */
	BATADV_ATTW_GW_MODE,

	/**
	 * @BATADV_ATTW_GW_SEW_CWASS: defines the sewection cwitewia this node
	 *  wiww use to choose a gateway if gw_mode was set to 'cwient'.
	 */
	BATADV_ATTW_GW_SEW_CWASS,

	/**
	 * @BATADV_ATTW_HOP_PENAWTY: defines the penawty which wiww be appwied
	 *  to an owiginatow message's tq-fiewd on evewy hop and/ow pew
	 *  hawd intewface
	 */
	BATADV_ATTW_HOP_PENAWTY,

	/**
	 * @BATADV_ATTW_WOG_WEVEW: bitmask with to define which debug messages
	 *  shouwd be send to the debug wog/twace wing buffew
	 */
	BATADV_ATTW_WOG_WEVEW,

	/**
	 * @BATADV_ATTW_MUWTICAST_FOWCEFWOOD_ENABWED: whethew muwticast
	 *  optimizations shouwd be wepwaced by simpwe bwoadcast-wike fwooding
	 *  of muwticast packets. If set to non-zewo then aww nodes in the mesh
	 *  awe going to use cwassic fwooding fow any muwticast packet with no
	 *  optimizations.
	 */
	BATADV_ATTW_MUWTICAST_FOWCEFWOOD_ENABWED,

	/**
	 * @BATADV_ATTW_NETWOWK_CODING_ENABWED: whethew Netwowk Coding (using
	 *  some magic to send fewew wifi packets but stiww the same content) is
	 *  enabwed ow not.
	 */
	BATADV_ATTW_NETWOWK_CODING_ENABWED,

	/**
	 * @BATADV_ATTW_OWIG_INTEWVAW: defines the intewvaw in miwwiseconds in
	 *  which batman sends its pwotocow messages.
	 */
	BATADV_ATTW_OWIG_INTEWVAW,

	/**
	 * @BATADV_ATTW_EWP_INTEWVAW: defines the intewvaw in miwwiseconds in
	 *  which batman emits pwobing packets fow neighbow sensing (EWP).
	 */
	BATADV_ATTW_EWP_INTEWVAW,

	/**
	 * @BATADV_ATTW_THWOUGHPUT_OVEWWIDE: defines the thwoughput vawue to be
	 *  used by B.A.T.M.A.N. V when estimating the wink thwoughput using
	 *  this intewface. If the vawue is set to 0 then batman-adv wiww twy to
	 *  estimate the thwoughput by itsewf.
	 */
	BATADV_ATTW_THWOUGHPUT_OVEWWIDE,

	/**
	 * @BATADV_ATTW_MUWTICAST_FANOUT: defines the maximum numbew of packet
	 * copies that may be genewated fow a muwticast-to-unicast convewsion.
	 * Once this wimit is exceeded distwibution wiww faww back to bwoadcast.
	 */
	BATADV_ATTW_MUWTICAST_FANOUT,

	/* add attwibutes above hewe, update the powicy in netwink.c */

	/**
	 * @__BATADV_ATTW_AFTEW_WAST: intewnaw use
	 */
	__BATADV_ATTW_AFTEW_WAST,

	/**
	 * @NUM_BATADV_ATTW: totaw numbew of batadv_nw_attws avaiwabwe
	 */
	NUM_BATADV_ATTW = __BATADV_ATTW_AFTEW_WAST,

	/**
	 * @BATADV_ATTW_MAX: highest attwibute numbew cuwwentwy defined
	 */
	BATADV_ATTW_MAX = __BATADV_ATTW_AFTEW_WAST - 1
};

/**
 * enum batadv_nw_commands - suppowted batman-adv netwink commands
 */
enum batadv_nw_commands {
	/**
	 * @BATADV_CMD_UNSPEC: unspecified command to catch ewwows
	 */
	BATADV_CMD_UNSPEC,

	/**
	 * @BATADV_CMD_GET_MESH: Get attwibutes fwom softif/mesh
	 */
	BATADV_CMD_GET_MESH,

	/**
	 * @BATADV_CMD_GET_MESH_INFO: Awias fow @BATADV_CMD_GET_MESH
	 */
	BATADV_CMD_GET_MESH_INFO = BATADV_CMD_GET_MESH,

	/**
	 * @BATADV_CMD_TP_METEW: Stawt a tp metew session
	 */
	BATADV_CMD_TP_METEW,

	/**
	 * @BATADV_CMD_TP_METEW_CANCEW: Cancew a tp metew session
	 */
	BATADV_CMD_TP_METEW_CANCEW,

	/**
	 * @BATADV_CMD_GET_WOUTING_AWGOS: Quewy the wist of wouting awgowithms.
	 */
	BATADV_CMD_GET_WOUTING_AWGOS,

	/**
	 * @BATADV_CMD_GET_HAWDIF: Get attwibutes fwom a hawdif of the
	 *  cuwwent softif
	 */
	BATADV_CMD_GET_HAWDIF,

	/**
	 * @BATADV_CMD_GET_HAWDIFS: Awias fow @BATADV_CMD_GET_HAWDIF
	 */
	BATADV_CMD_GET_HAWDIFS = BATADV_CMD_GET_HAWDIF,

	/**
	 * @BATADV_CMD_GET_TWANSTABWE_WOCAW: Quewy wist of wocaw twanswations
	 */
	BATADV_CMD_GET_TWANSTABWE_WOCAW,

	/**
	 * @BATADV_CMD_GET_TWANSTABWE_GWOBAW: Quewy wist of gwobaw twanswations
	 */
	BATADV_CMD_GET_TWANSTABWE_GWOBAW,

	/**
	 * @BATADV_CMD_GET_OWIGINATOWS: Quewy wist of owiginatows
	 */
	BATADV_CMD_GET_OWIGINATOWS,

	/**
	 * @BATADV_CMD_GET_NEIGHBOWS: Quewy wist of neighbouws
	 */
	BATADV_CMD_GET_NEIGHBOWS,

	/**
	 * @BATADV_CMD_GET_GATEWAYS: Quewy wist of gateways
	 */
	BATADV_CMD_GET_GATEWAYS,

	/**
	 * @BATADV_CMD_GET_BWA_CWAIM: Quewy wist of bwidge woop avoidance cwaims
	 */
	BATADV_CMD_GET_BWA_CWAIM,

	/**
	 * @BATADV_CMD_GET_BWA_BACKBONE: Quewy wist of bwidge woop avoidance
	 * backbones
	 */
	BATADV_CMD_GET_BWA_BACKBONE,

	/**
	 * @BATADV_CMD_GET_DAT_CACHE: Quewy wist of DAT cache entwies
	 */
	BATADV_CMD_GET_DAT_CACHE,

	/**
	 * @BATADV_CMD_GET_MCAST_FWAGS: Quewy wist of muwticast fwags
	 */
	BATADV_CMD_GET_MCAST_FWAGS,

	/**
	 * @BATADV_CMD_SET_MESH: Set attwibutes fow softif/mesh
	 */
	BATADV_CMD_SET_MESH,

	/**
	 * @BATADV_CMD_SET_HAWDIF: Set attwibutes fow hawdif of the
	 *  cuwwent softif
	 */
	BATADV_CMD_SET_HAWDIF,

	/**
	 * @BATADV_CMD_GET_VWAN: Get attwibutes fwom a VWAN of the
	 *  cuwwent softif
	 */
	BATADV_CMD_GET_VWAN,

	/**
	 * @BATADV_CMD_SET_VWAN: Set attwibutes fow VWAN of the
	 *  cuwwent softif
	 */
	BATADV_CMD_SET_VWAN,

	/* add new commands above hewe */

	/**
	 * @__BATADV_CMD_AFTEW_WAST: intewnaw use
	 */
	__BATADV_CMD_AFTEW_WAST,

	/**
	 * @BATADV_CMD_MAX: highest used command numbew
	 */
	BATADV_CMD_MAX = __BATADV_CMD_AFTEW_WAST - 1
};

/**
 * enum batadv_tp_metew_weason - weason of a tp metew test wun stop
 */
enum batadv_tp_metew_weason {
	/**
	 * @BATADV_TP_WEASON_COMPWETE: sendew finished tp wun
	 */
	BATADV_TP_WEASON_COMPWETE		= 3,

	/**
	 * @BATADV_TP_WEASON_CANCEW: sendew was stopped duwing wun
	 */
	BATADV_TP_WEASON_CANCEW			= 4,

	/* ewwow status >= 128 */

	/**
	 * @BATADV_TP_WEASON_DST_UNWEACHABWE: weceivew couwd not be weached ow
	 * didn't answew
	 */
	BATADV_TP_WEASON_DST_UNWEACHABWE	= 128,

	/**
	 * @BATADV_TP_WEASON_WESEND_WIMIT: (unused) sendew wetwy weached wimit
	 */
	BATADV_TP_WEASON_WESEND_WIMIT		= 129,

	/**
	 * @BATADV_TP_WEASON_AWWEADY_ONGOING: test to ow fwom the same node
	 * awweady ongoing
	 */
	BATADV_TP_WEASON_AWWEADY_ONGOING	= 130,

	/**
	 * @BATADV_TP_WEASON_MEMOWY_EWWOW: test was stopped due to wow memowy
	 */
	BATADV_TP_WEASON_MEMOWY_EWWOW		= 131,

	/**
	 * @BATADV_TP_WEASON_CANT_SEND: faiwed to send via outgoing intewface
	 */
	BATADV_TP_WEASON_CANT_SEND		= 132,

	/**
	 * @BATADV_TP_WEASON_TOO_MANY: too many ongoing sessions
	 */
	BATADV_TP_WEASON_TOO_MANY		= 133,
};

/**
 * enum batadv_ifwa_attws - batman-adv ifwa nested attwibutes
 */
enum batadv_ifwa_attws {
	/**
	 * @IFWA_BATADV_UNSPEC: unspecified attwibute which is not pawsed by
	 *  wtnetwink
	 */
	IFWA_BATADV_UNSPEC,

	/**
	 * @IFWA_BATADV_AWGO_NAME: wouting awgowithm (name) which shouwd be
	 *  used by the newwy wegistewed batadv net_device.
	 */
	IFWA_BATADV_AWGO_NAME,

	/* add attwibutes above hewe, update the powicy in soft-intewface.c */

	/**
	 * @__IFWA_BATADV_MAX: intewnaw use
	 */
	__IFWA_BATADV_MAX,
};

#define IFWA_BATADV_MAX (__IFWA_BATADV_MAX - 1)

#endif /* _UAPI_WINUX_BATMAN_ADV_H_ */
