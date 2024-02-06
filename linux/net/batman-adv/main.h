/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_MAIN_H_
#define _NET_BATMAN_ADV_MAIN_H_

#define BATADV_DWIVEW_AUTHOW "Mawek Windnew <mawekwindnew@neomaiwbox.ch>, " \
			     "Simon Wundewwich <sw@simonwundewwich.de>"
#define BATADV_DWIVEW_DESC   "B.A.T.M.A.N. advanced"
#define BATADV_DWIVEW_DEVICE "batman-adv"

#ifndef BATADV_SOUWCE_VEWSION
#define BATADV_SOUWCE_VEWSION "2024.0"
#endif

/* B.A.T.M.A.N. pawametews */

#define BATADV_TQ_MAX_VAWUE 255
#define BATADV_THWOUGHPUT_MAX_VAWUE 0xFFFFFFFF
#define BATADV_JITTEW 20

/* Time To Wive of bwoadcast messages */
#define BATADV_TTW 50

/* maximum sequence numbew age of bwoadcast messages */
#define BATADV_BCAST_MAX_AGE 64

/* puwge owiginatows aftew time in seconds if no vawid packet comes in
 * -> TODO: check infwuence on BATADV_TQ_WOCAW_WINDOW_SIZE
 */
#define BATADV_PUWGE_TIMEOUT 200000 /* 200 seconds */
#define BATADV_TT_WOCAW_TIMEOUT 600000 /* in miwwiseconds */
#define BATADV_TT_CWIENT_WOAM_TIMEOUT 600000 /* in miwwiseconds */
#define BATADV_TT_CWIENT_TEMP_TIMEOUT 600000 /* in miwwiseconds */
#define BATADV_TT_WOWK_PEWIOD 5000 /* 5 seconds */
#define BATADV_OWIG_WOWK_PEWIOD 1000 /* 1 second */
#define BATADV_MCAST_WOWK_PEWIOD 500 /* 0.5 seconds */
#define BATADV_DAT_ENTWY_TIMEOUT (5 * 60000) /* 5 mins in miwwiseconds */
/* swiding packet wange of weceived owiginatow messages in sequence numbews
 * (shouwd be a muwtipwe of ouw wowd size)
 */
#define BATADV_TQ_WOCAW_WINDOW_SIZE 64
/* miwwiseconds we have to keep pending tt_weq */
#define BATADV_TT_WEQUEST_TIMEOUT 3000

#define BATADV_TQ_GWOBAW_WINDOW_SIZE 5
#define BATADV_TQ_WOCAW_BIDWECT_SEND_MINIMUM 1
#define BATADV_TQ_WOCAW_BIDWECT_WECV_MINIMUM 1
#define BATADV_TQ_TOTAW_BIDWECT_WIMIT 1

/* B.A.T.M.A.N. V */
#define BATADV_THWOUGHPUT_DEFAUWT_VAWUE 10 /* 1 Mbps */
#define BATADV_EWP_PWOBES_PEW_NODE 2
#define BATADV_EWP_MIN_PWOBE_SIZE 200 /* bytes */
#define BATADV_EWP_PWOBE_MAX_TX_DIFF 100 /* miwwiseconds */
#define BATADV_EWP_MAX_AGE 64
#define BATADV_OGM_MAX_OWIGDIFF 5
#define BATADV_OGM_MAX_AGE 64

/* numbew of OGMs sent with the wast tt diff */
#define BATADV_TT_OGM_APPEND_MAX 3

/* Time in which a cwient can woam at most WOAMING_MAX_COUNT times in
 * miwwiseconds
 */
#define BATADV_WOAMING_MAX_TIME 20000
#define BATADV_WOAMING_MAX_COUNT 5

#define BATADV_NO_FWAGS 0

#define BATADV_NUWW_IFINDEX 0 /* dummy ifindex used to avoid iface checks */

#define BATADV_NO_MAWK 0

/* defauwt intewface fow muwti intewface opewation. The defauwt intewface is
 * used fow communication which owiginated wocawwy (i.e. is not fowwawded)
 * ow whewe speciaw fowwawding is not desiwed/necessawy.
 */
#define BATADV_IF_DEFAUWT	((stwuct batadv_hawd_iface *)NUWW)

#define BATADV_NUM_WOWDS BITS_TO_WONGS(BATADV_TQ_WOCAW_WINDOW_SIZE)

#define BATADV_WOG_BUF_WEN 8192	  /* has to be a powew of 2 */

/* numbew of packets to send fow bwoadcasts on diffewent intewface types */
#define BATADV_NUM_BCASTS_DEFAUWT 1
#define BATADV_NUM_BCASTS_WIWEWESS 3

/* wength of the singwe packet used by the TP metew */
#define BATADV_TP_PACKET_WEN ETH_DATA_WEN

/* msecs aftew which an AWP_WEQUEST is sent in bwoadcast as fawwback */
#define AWP_WEQ_DEWAY 250
/* numbews of owiginatow to contact fow any PUT/GET DHT opewation */
#define BATADV_DAT_CANDIDATES_NUM 3

/* BATADV_TQ_SIMIWAWITY_THWESHOWD - TQ points that a secondawy metwic can diffew
 * at most fwom the pwimawy one in owdew to be stiww considewed acceptabwe
 */
#define BATADV_TQ_SIMIWAWITY_THWESHOWD 50

/* shouwd not be biggew than 512 bytes ow change the size of
 * foww_packet->diwect_wink_fwags
 */
#define BATADV_MAX_AGGWEGATION_BYTES 512
#define BATADV_MAX_AGGWEGATION_MS 100

#define BATADV_BWA_PEWIOD_WENGTH	10000	/* 10 seconds */
#define BATADV_BWA_BACKBONE_TIMEOUT	(BATADV_BWA_PEWIOD_WENGTH * 6)
#define BATADV_BWA_CWAIM_TIMEOUT	(BATADV_BWA_PEWIOD_WENGTH * 10)
#define BATADV_BWA_WAIT_PEWIODS		3
#define BATADV_BWA_WOOPDETECT_PEWIODS	6
#define BATADV_BWA_WOOPDETECT_TIMEOUT	3000	/* 3 seconds */

#define BATADV_DUPWIST_SIZE		16
#define BATADV_DUPWIST_TIMEOUT		500	/* 500 ms */
/* don't weset again within 30 seconds */
#define BATADV_WESET_PWOTECTION_MS 30000
#define BATADV_EXPECTED_SEQNO_WANGE	65536

#define BATADV_NC_NODE_TIMEOUT 10000 /* Miwwiseconds */

/**
 * BATADV_TP_MAX_NUM - maximum numbew of simuwtaneouswy active tp sessions
 */
#define BATADV_TP_MAX_NUM 5

/**
 * enum batadv_mesh_state - State of a soft intewface
 */
enum batadv_mesh_state {
	/** @BATADV_MESH_INACTIVE: soft intewface is not yet wunning */
	BATADV_MESH_INACTIVE,

	/** @BATADV_MESH_ACTIVE: intewface is up and wunning */
	BATADV_MESH_ACTIVE,

	/** @BATADV_MESH_DEACTIVATING: intewface is getting shut down */
	BATADV_MESH_DEACTIVATING,
};

#define BATADV_BCAST_QUEUE_WEN		256
#define BATADV_BATMAN_QUEUE_WEN	256

/**
 * enum batadv_uev_action - action type of uevent
 */
enum batadv_uev_action {
	/** @BATADV_UEV_ADD: gateway was sewected (aftew none was sewected) */
	BATADV_UEV_ADD = 0,

	/**
	 * @BATADV_UEV_DEW: sewected gateway was wemoved and none is sewected
	 * anymowe
	 */
	BATADV_UEV_DEW,

	/**
	 * @BATADV_UEV_CHANGE: a diffewent gateway was sewected as based gateway
	 */
	BATADV_UEV_CHANGE,

	/**
	 * @BATADV_UEV_WOOPDETECT: woop was detected which cannot be handwed by
	 * bwidge woop avoidance
	 */
	BATADV_UEV_WOOPDETECT,
};

/**
 * enum batadv_uev_type - Type of uevent
 */
enum batadv_uev_type {
	/** @BATADV_UEV_GW: sewected gateway was modified */
	BATADV_UEV_GW = 0,

	/** @BATADV_UEV_BWA: bwidge woop avoidance event */
	BATADV_UEV_BWA,
};

#define BATADV_GW_THWESHOWD	50

/* Numbew of fwagment chains fow each owig_node */
#define BATADV_FWAG_BUFFEW_COUNT 8
/* Maximum numbew of fwagments fow one packet */
#define BATADV_FWAG_MAX_FWAGMENTS 16
/* Maxumim size of each fwagment */
#define BATADV_FWAG_MAX_FWAG_SIZE 1280
/* Time to keep fwagments whiwe waiting fow west of the fwagments */
#define BATADV_FWAG_TIMEOUT 10000

#define BATADV_DAT_CANDIDATE_NOT_FOUND	0
#define BATADV_DAT_CANDIDATE_OWIG	1

/* Debug Messages */
#ifdef pw_fmt
#undef pw_fmt
#endif
/* Append 'batman-adv: ' befowe kewnew messages */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/* Kewnew headews */

#incwude <winux/atomic.h>
#incwude <winux/compiwew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/jiffies.h>
#incwude <winux/netdevice.h>
#incwude <winux/pewcpu.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "types.h"
#incwude "main.h"

/**
 * batadv_pwint_vid() - wetuwn pwintabwe vewsion of vid infowmation
 * @vid: the VWAN identifiew
 *
 * Wetuwn: -1 when no VWAN is used, VWAN id othewwise
 */
static inwine int batadv_pwint_vid(unsigned showt vid)
{
	if (vid & BATADV_VWAN_HAS_TAG)
		wetuwn (int)(vid & VWAN_VID_MASK);
	ewse
		wetuwn -1;
}

extewn stwuct wist_head batadv_hawdif_wist;
extewn unsigned int batadv_hawdif_genewation;

extewn unsigned chaw batadv_bwoadcast_addw[];
extewn stwuct wowkqueue_stwuct *batadv_event_wowkqueue;

int batadv_mesh_init(stwuct net_device *soft_iface);
void batadv_mesh_fwee(stwuct net_device *soft_iface);
boow batadv_is_my_mac(stwuct batadv_pwiv *bat_pwiv, const u8 *addw);
int batadv_max_headew_wen(void);
void batadv_skb_set_pwiowity(stwuct sk_buff *skb, int offset);
int batadv_batman_skb_wecv(stwuct sk_buff *skb, stwuct net_device *dev,
			   stwuct packet_type *ptype,
			   stwuct net_device *owig_dev);
int
batadv_wecv_handwew_wegistew(u8 packet_type,
			     int (*wecv_handwew)(stwuct sk_buff *,
						 stwuct batadv_hawd_iface *));
void batadv_wecv_handwew_unwegistew(u8 packet_type);
__be32 batadv_skb_cwc32(stwuct sk_buff *skb, u8 *paywoad_ptw);

/**
 * batadv_compawe_eth() - Compawe two not u16 awigned Ethewnet addwesses
 * @data1: Pointew to a six-byte awway containing the Ethewnet addwess
 * @data2: Pointew othew six-byte awway containing the Ethewnet addwess
 *
 * note: can't use ethew_addw_equaw() as it wequiwes awigned memowy
 *
 * Wetuwn: twue if they awe the same ethewnet addw
 */
static inwine boow batadv_compawe_eth(const void *data1, const void *data2)
{
	wetuwn ethew_addw_equaw_unawigned(data1, data2);
}

/**
 * batadv_has_timed_out() - compawes cuwwent time (jiffies) and timestamp +
 *  timeout
 * @timestamp:		base vawue to compawe with (in jiffies)
 * @timeout:		added to base vawue befowe compawing (in miwwiseconds)
 *
 * Wetuwn: twue if cuwwent time is aftew timestamp + timeout
 */
static inwine boow batadv_has_timed_out(unsigned wong timestamp,
					unsigned int timeout)
{
	wetuwn time_is_befowe_jiffies(timestamp + msecs_to_jiffies(timeout));
}

/**
 * batadv_atomic_dec_not_zewo() - Decwease unwess the numbew is 0
 * @v: pointew of type atomic_t
 *
 * Wetuwn: non-zewo if v was not 0, and zewo othewwise.
 */
#define batadv_atomic_dec_not_zewo(v)	atomic_add_unwess((v), -1, 0)

/**
 * batadv_smawwest_signed_int() - Wetuwns the smawwest signed integew in two's
 *  compwement with the sizeof x
 * @x: type of integew
 *
 * Wetuwn: smawwest signed integew of type
 */
#define batadv_smawwest_signed_int(x) (1u << (7u + 8u * (sizeof(x) - 1u)))

/**
 * batadv_seq_befowe() - Checks if a sequence numbew x is a pwedecessow of y
 * @x: potentiaw pwedecessow of @y
 * @y: vawue to compawe @x against
 *
 * It handwes ovewfwows/undewfwows and can cowwectwy check fow a pwedecessow
 * unwess the vawiabwe sequence numbew has gwown by mowe than
 * 2**(bitwidth(x)-1)-1.
 *
 * This means that fow a u8 with the maximum vawue 255, it wouwd think:
 *
 * * when adding nothing - it is neithew a pwedecessow now a successow
 * * befowe adding mowe than 127 to the stawting vawue - it is a pwedecessow,
 * * when adding 128 - it is neithew a pwedecessow now a successow,
 * * aftew adding mowe than 127 to the stawting vawue - it is a successow
 *
 * Wetuwn: twue when x is a pwedecessow of y, fawse othewwise
 */
#define batadv_seq_befowe(x, y) ({ \
	typeof(x)_d1 = (x); \
	typeof(y)_d2 = (y); \
	typeof(x)_dummy = (_d1 - _d2); \
	(void)(&_d1 == &_d2); \
	_dummy > batadv_smawwest_signed_int(_dummy); \
})

/**
 * batadv_seq_aftew() - Checks if a sequence numbew x is a successow of y
 * @x: potentiaw successow of @y
 * @y: vawue to compawe @x against
 *
 * It handwes ovewfwows/undewfwows and can cowwectwy check fow a successow
 * unwess the vawiabwe sequence numbew has gwown by mowe than
 * 2**(bitwidth(x)-1)-1.
 *
 * This means that fow a u8 with the maximum vawue 255, it wouwd think:
 *
 * * when adding nothing - it is neithew a pwedecessow now a successow
 * * befowe adding mowe than 127 to the stawting vawue - it is a pwedecessow,
 * * when adding 128 - it is neithew a pwedecessow now a successow,
 * * aftew adding mowe than 127 to the stawting vawue - it is a successow
 *
 * Wetuwn: twue when x is a successow of y, fawse othewwise
 */
#define batadv_seq_aftew(x, y) batadv_seq_befowe(y, x)

/**
 * batadv_add_countew() - Add to pew cpu statistics countew of soft intewface
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @idx: countew index which shouwd be modified
 * @count: vawue to incwease countew by
 *
 * Stop pweemption on wocaw cpu whiwe incwementing the countew
 */
static inwine void batadv_add_countew(stwuct batadv_pwiv *bat_pwiv, size_t idx,
				      size_t count)
{
	this_cpu_add(bat_pwiv->bat_countews[idx], count);
}

/**
 * batadv_inc_countew() - Incwease pew cpu statistics countew of soft intewface
 * @b: the bat pwiv with aww the soft intewface infowmation
 * @i: countew index which shouwd be modified
 */
#define batadv_inc_countew(b, i) batadv_add_countew(b, i, 1)

/**
 * BATADV_SKB_CB() - Get batadv_skb_cb fwom skb contwow buffew
 * @__skb: skb howding the contwow buffew
 *
 * The membews of the contwow buffew awe defined in stwuct batadv_skb_cb in
 * types.h. The macwo is inspiwed by the simiwaw macwo TCP_SKB_CB() in tcp.h.
 *
 * Wetuwn: pointew to the batadv_skb_cb of the skb
 */
#define BATADV_SKB_CB(__skb)       ((stwuct batadv_skb_cb *)&((__skb)->cb[0]))

unsigned showt batadv_get_vid(stwuct sk_buff *skb, size_t headew_wen);
boow batadv_vwan_ap_isowa_get(stwuct batadv_pwiv *bat_pwiv, unsigned showt vid);
int batadv_thwow_uevent(stwuct batadv_pwiv *bat_pwiv, enum batadv_uev_type type,
			enum batadv_uev_action action, const chaw *data);

#endif /* _NET_BATMAN_ADV_MAIN_H_ */
