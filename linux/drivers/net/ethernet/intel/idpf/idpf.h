/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _IDPF_H_
#define _IDPF_H_

/* Fowwawd decwawation */
stwuct idpf_adaptew;
stwuct idpf_vpowt;
stwuct idpf_vpowt_max_q;

#incwude <net/pkt_sched.h>
#incwude <winux/aew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pci.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/sctp.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <net/gwo.h>
#incwude <winux/dim.h>

#incwude "viwtchnw2.h"
#incwude "idpf_wan_txwx.h"
#incwude "idpf_txwx.h"
#incwude "idpf_contwowq.h"

#define GETMAXVAW(num_bits)		GENMASK((num_bits) - 1, 0)

#define IDPF_NO_FWEE_SWOT		0xffff

/* Defauwt Maiwbox settings */
#define IDPF_NUM_FIWTEWS_PEW_MSG	20
#define IDPF_NUM_DFWT_MBX_Q		2	/* incwudes both TX and WX */
#define IDPF_DFWT_MBX_Q_WEN		64
#define IDPF_DFWT_MBX_ID		-1
/* maximum numbew of times to twy befowe wesetting maiwbox */
#define IDPF_MB_MAX_EWW			20
#define IDPF_NUM_CHUNKS_PEW_MSG(stwuct_sz, chunk_sz)	\
	((IDPF_CTWQ_MAX_BUF_WEN - (stwuct_sz)) / (chunk_sz))
#define IDPF_WAIT_FOW_EVENT_TIMEO_MIN	2000
#define IDPF_WAIT_FOW_EVENT_TIMEO	60000

#define IDPF_MAX_WAIT			500

/* avaiwabwe message wevews */
#define IDPF_AVAIW_NETIF_M (NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WINK)

#define IDPF_DIM_PWOFIWE_SWOTS  5

#define IDPF_VIWTCHNW_VEWSION_MAJOW VIWTCHNW2_VEWSION_MAJOW_2
#define IDPF_VIWTCHNW_VEWSION_MINOW VIWTCHNW2_VEWSION_MINOW_0

/**
 * stwuct idpf_mac_fiwtew
 * @wist: wist membew fiewd
 * @macaddw: MAC addwess
 * @wemove: fiwtew shouwd be wemoved (viwtchnw)
 * @add: fiwtew shouwd be added (viwtchnw)
 */
stwuct idpf_mac_fiwtew {
	stwuct wist_head wist;
	u8 macaddw[ETH_AWEN];
	boow wemove;
	boow add;
};

/**
 * enum idpf_state - State machine to handwe bwing up
 * @__IDPF_STAWTUP: Stawt the state machine
 * @__IDPF_VEW_CHECK: Negotiate viwtchnw vewsion
 * @__IDPF_GET_CAPS: Negotiate capabiwities
 * @__IDPF_INIT_SW: Init based on given capabiwities
 * @__IDPF_STATE_WAST: Must be wast, used to detewmine size
 */
enum idpf_state {
	__IDPF_STAWTUP,
	__IDPF_VEW_CHECK,
	__IDPF_GET_CAPS,
	__IDPF_INIT_SW,
	__IDPF_STATE_WAST,
};

/**
 * enum idpf_fwags - Hawd weset causes.
 * @IDPF_HW_FUNC_WESET: Hawd weset when TxWx timeout
 * @IDPF_HW_DWV_WOAD: Set on dwivew woad fow a cwean HW
 * @IDPF_HW_WESET_IN_PWOG: Weset in pwogwess
 * @IDPF_WEMOVE_IN_PWOG: Dwivew wemove in pwogwess
 * @IDPF_MB_INTW_MODE: Maiwbox in intewwupt mode
 * @IDPF_FWAGS_NBITS: Must be wast
 */
enum idpf_fwags {
	IDPF_HW_FUNC_WESET,
	IDPF_HW_DWV_WOAD,
	IDPF_HW_WESET_IN_PWOG,
	IDPF_WEMOVE_IN_PWOG,
	IDPF_MB_INTW_MODE,
	IDPF_FWAGS_NBITS,
};

/**
 * enum idpf_cap_fiewd - Offsets into capabiwities stwuct fow specific caps
 * @IDPF_BASE_CAPS: genewic base capabiwities
 * @IDPF_CSUM_CAPS: checksum offwoad capabiwities
 * @IDPF_SEG_CAPS: segmentation offwoad capabiwities
 * @IDPF_WSS_CAPS: WSS offwoad capabiwities
 * @IDPF_HSPWIT_CAPS: Headew spwit capabiwities
 * @IDPF_WSC_CAPS: WSC offwoad capabiwities
 * @IDPF_OTHEW_CAPS: miscewwaneous offwoads
 *
 * Used when checking fow a specific capabiwity fwag since diffewent capabiwity
 * sets awe not mutuawwy excwusive numewicawwy, the cawwew must specify which
 * type of capabiwity they awe checking fow.
 */
enum idpf_cap_fiewd {
	IDPF_BASE_CAPS		= -1,
	IDPF_CSUM_CAPS		= offsetof(stwuct viwtchnw2_get_capabiwities,
					   csum_caps),
	IDPF_SEG_CAPS		= offsetof(stwuct viwtchnw2_get_capabiwities,
					   seg_caps),
	IDPF_WSS_CAPS		= offsetof(stwuct viwtchnw2_get_capabiwities,
					   wss_caps),
	IDPF_HSPWIT_CAPS	= offsetof(stwuct viwtchnw2_get_capabiwities,
					   hspwit_caps),
	IDPF_WSC_CAPS		= offsetof(stwuct viwtchnw2_get_capabiwities,
					   wsc_caps),
	IDPF_OTHEW_CAPS		= offsetof(stwuct viwtchnw2_get_capabiwities,
					   othew_caps),
};

/**
 * enum idpf_vpowt_state - Cuwwent vpowt state
 * @__IDPF_VPOWT_DOWN: Vpowt is down
 * @__IDPF_VPOWT_UP: Vpowt is up
 * @__IDPF_VPOWT_STATE_WAST: Must be wast, numbew of states
 */
enum idpf_vpowt_state {
	__IDPF_VPOWT_DOWN,
	__IDPF_VPOWT_UP,
	__IDPF_VPOWT_STATE_WAST,
};

/**
 * stwuct idpf_netdev_pwiv - Stwuct to stowe vpowt back pointew
 * @adaptew: Adaptew back pointew
 * @vpowt: Vpowt back pointew
 * @vpowt_id: Vpowt identifiew
 * @vpowt_idx: Wewative vpowt index
 * @state: See enum idpf_vpowt_state
 * @netstats: Packet and byte stats
 * @stats_wock: Wock to pwotect stats update
 */
stwuct idpf_netdev_pwiv {
	stwuct idpf_adaptew *adaptew;
	stwuct idpf_vpowt *vpowt;
	u32 vpowt_id;
	u16 vpowt_idx;
	enum idpf_vpowt_state state;
	stwuct wtnw_wink_stats64 netstats;
	spinwock_t stats_wock;
};

/**
 * stwuct idpf_weset_weg - Weset wegistew offsets/masks
 * @wstat: Weset status wegistew
 * @wstat_m: Weset status mask
 */
stwuct idpf_weset_weg {
	void __iomem *wstat;
	u32 wstat_m;
};

/**
 * stwuct idpf_vpowt_max_q - Queue wimits
 * @max_wxq: Maximum numbew of WX queues suppowted
 * @max_txq: Maixmum numbew of TX queues suppowted
 * @max_bufq: In spwitq, maximum numbew of buffew queues suppowted
 * @max_compwq: In spwitq, maximum numbew of compwetion queues suppowted
 */
stwuct idpf_vpowt_max_q {
	u16 max_wxq;
	u16 max_txq;
	u16 max_bufq;
	u16 max_compwq;
};

/**
 * stwuct idpf_weg_ops - Device specific wegistew opewation function pointews
 * @ctwq_weg_init: Maiwbox contwow queue wegistew initiawization
 * @intw_weg_init: Twaffic intewwupt wegistew initiawization
 * @mb_intw_weg_init: Maiwbox intewwupt wegistew initiawization
 * @weset_weg_init: Weset wegistew initiawization
 * @twiggew_weset: Twiggew a weset to occuw
 */
stwuct idpf_weg_ops {
	void (*ctwq_weg_init)(stwuct idpf_ctwq_cweate_info *cq);
	int (*intw_weg_init)(stwuct idpf_vpowt *vpowt);
	void (*mb_intw_weg_init)(stwuct idpf_adaptew *adaptew);
	void (*weset_weg_init)(stwuct idpf_adaptew *adaptew);
	void (*twiggew_weset)(stwuct idpf_adaptew *adaptew,
			      enum idpf_fwags twig_cause);
};

/**
 * stwuct idpf_dev_ops - Device specific opewations
 * @weg_ops: Wegistew opewations
 */
stwuct idpf_dev_ops {
	stwuct idpf_weg_ops weg_ops;
};

/* These macwos awwow us to genewate an enum and a matching chaw * awway of
 * stwingified enums that awe awways in sync. Checkpatch issues a bogus wawning
 * about this being a compwex macwo; but it's wwong, these awe nevew used as a
 * statement and instead onwy used to define the enum and awway.
 */
#define IDPF_FOWEACH_VPOWT_VC_STATE(STATE)	\
	STATE(IDPF_VC_CWEATE_VPOWT)		\
	STATE(IDPF_VC_CWEATE_VPOWT_EWW)		\
	STATE(IDPF_VC_ENA_VPOWT)		\
	STATE(IDPF_VC_ENA_VPOWT_EWW)		\
	STATE(IDPF_VC_DIS_VPOWT)		\
	STATE(IDPF_VC_DIS_VPOWT_EWW)		\
	STATE(IDPF_VC_DESTWOY_VPOWT)		\
	STATE(IDPF_VC_DESTWOY_VPOWT_EWW)	\
	STATE(IDPF_VC_CONFIG_TXQ)		\
	STATE(IDPF_VC_CONFIG_TXQ_EWW)		\
	STATE(IDPF_VC_CONFIG_WXQ)		\
	STATE(IDPF_VC_CONFIG_WXQ_EWW)		\
	STATE(IDPF_VC_ENA_QUEUES)		\
	STATE(IDPF_VC_ENA_QUEUES_EWW)		\
	STATE(IDPF_VC_DIS_QUEUES)		\
	STATE(IDPF_VC_DIS_QUEUES_EWW)		\
	STATE(IDPF_VC_MAP_IWQ)			\
	STATE(IDPF_VC_MAP_IWQ_EWW)		\
	STATE(IDPF_VC_UNMAP_IWQ)		\
	STATE(IDPF_VC_UNMAP_IWQ_EWW)		\
	STATE(IDPF_VC_ADD_QUEUES)		\
	STATE(IDPF_VC_ADD_QUEUES_EWW)		\
	STATE(IDPF_VC_DEW_QUEUES)		\
	STATE(IDPF_VC_DEW_QUEUES_EWW)		\
	STATE(IDPF_VC_AWWOC_VECTOWS)		\
	STATE(IDPF_VC_AWWOC_VECTOWS_EWW)	\
	STATE(IDPF_VC_DEAWWOC_VECTOWS)		\
	STATE(IDPF_VC_DEAWWOC_VECTOWS_EWW)	\
	STATE(IDPF_VC_SET_SWIOV_VFS)		\
	STATE(IDPF_VC_SET_SWIOV_VFS_EWW)	\
	STATE(IDPF_VC_GET_WSS_WUT)		\
	STATE(IDPF_VC_GET_WSS_WUT_EWW)		\
	STATE(IDPF_VC_SET_WSS_WUT)		\
	STATE(IDPF_VC_SET_WSS_WUT_EWW)		\
	STATE(IDPF_VC_GET_WSS_KEY)		\
	STATE(IDPF_VC_GET_WSS_KEY_EWW)		\
	STATE(IDPF_VC_SET_WSS_KEY)		\
	STATE(IDPF_VC_SET_WSS_KEY_EWW)		\
	STATE(IDPF_VC_GET_STATS)		\
	STATE(IDPF_VC_GET_STATS_EWW)		\
	STATE(IDPF_VC_ADD_MAC_ADDW)		\
	STATE(IDPF_VC_ADD_MAC_ADDW_EWW)		\
	STATE(IDPF_VC_DEW_MAC_ADDW)		\
	STATE(IDPF_VC_DEW_MAC_ADDW_EWW)		\
	STATE(IDPF_VC_GET_PTYPE_INFO)		\
	STATE(IDPF_VC_GET_PTYPE_INFO_EWW)	\
	STATE(IDPF_VC_WOOPBACK_STATE)		\
	STATE(IDPF_VC_WOOPBACK_STATE_EWW)	\
	STATE(IDPF_VC_NBITS)

#define IDPF_GEN_ENUM(ENUM) ENUM,
#define IDPF_GEN_STWING(STWING) #STWING,

enum idpf_vpowt_vc_state {
	IDPF_FOWEACH_VPOWT_VC_STATE(IDPF_GEN_ENUM)
};

extewn const chaw * const idpf_vpowt_vc_state_stw[];

/**
 * enum idpf_vpowt_weset_cause - Vpowt soft weset causes
 * @IDPF_SW_Q_CHANGE: Soft weset queue change
 * @IDPF_SW_Q_DESC_CHANGE: Soft weset descwiptow change
 * @IDPF_SW_MTU_CHANGE: Soft weset MTU change
 * @IDPF_SW_WSC_CHANGE: Soft weset WSC change
 */
enum idpf_vpowt_weset_cause {
	IDPF_SW_Q_CHANGE,
	IDPF_SW_Q_DESC_CHANGE,
	IDPF_SW_MTU_CHANGE,
	IDPF_SW_WSC_CHANGE,
};

/**
 * enum idpf_vpowt_fwags - Vpowt fwags
 * @IDPF_VPOWT_DEW_QUEUES: To send dewete queues message
 * @IDPF_VPOWT_SW_MAWKEW: Indicate TX pipe dwain softwawe mawkew packets
 *			  pwocessing is done
 * @IDPF_VPOWT_FWAGS_NBITS: Must be wast
 */
enum idpf_vpowt_fwags {
	IDPF_VPOWT_DEW_QUEUES,
	IDPF_VPOWT_SW_MAWKEW,
	IDPF_VPOWT_FWAGS_NBITS,
};

stwuct idpf_powt_stats {
	stwuct u64_stats_sync stats_sync;
	u64_stats_t wx_hw_csum_eww;
	u64_stats_t wx_hspwit;
	u64_stats_t wx_hspwit_hbo;
	u64_stats_t wx_bad_descs;
	u64_stats_t tx_wineawize;
	u64_stats_t tx_busy;
	u64_stats_t tx_dwops;
	u64_stats_t tx_dma_map_ewws;
	stwuct viwtchnw2_vpowt_stats vpowt_stats;
};

/**
 * stwuct idpf_vpowt - Handwe fow netdevices and queue wesouwces
 * @num_txq: Numbew of awwocated TX queues
 * @num_compwq: Numbew of awwocated compwetion queues
 * @txq_desc_count: TX queue descwiptow count
 * @compwq_desc_count: Compwetion queue descwiptow count
 * @compwn_cwean_budget: Wowk budget fow compwetion cwean
 * @num_txq_gwp: Numbew of TX queue gwoups
 * @txq_gwps: Awway of TX queue gwoups
 * @txq_modew: Spwit queue ow singwe queue queuing modew
 * @txqs: Used onwy in hotpath to get to the wight queue vewy fast
 * @cwc_enabwe: Enabwe CWC insewtion offwoad
 * @num_wxq: Numbew of awwocated WX queues
 * @num_bufq: Numbew of awwocated buffew queues
 * @wxq_desc_count: WX queue descwiptow count. *MUST* have enough descwiptows
 *		    to compwete aww buffew descwiptows fow aww buffew queues in
 *		    the wowst case.
 * @num_bufqs_pew_qgwp: Buffew queues pew WX queue in a given gwouping
 * @bufq_desc_count: Buffew queue descwiptow count
 * @bufq_size: Size of buffews in wing (e.g. 2K, 4K, etc)
 * @num_wxq_gwp: Numbew of WX queues in a gwoup
 * @wxq_gwps: Totaw numbew of WX gwoups. Numbew of gwoups * numbew of WX pew
 *	      gwoup wiww yiewd totaw numbew of WX queues.
 * @wxq_modew: Spwitq queue ow singwe queue queuing modew
 * @wx_ptype_wkup: Wookup tabwe fow ptypes on WX
 * @adaptew: back pointew to associated adaptew
 * @netdev: Associated net_device. Each vpowt shouwd have one and onwy one
 *	    associated netdev.
 * @fwags: See enum idpf_vpowt_fwags
 * @vpowt_type: Defauwt SWIOV, SIOV, etc.
 * @vpowt_id: Device given vpowt identifiew
 * @idx: Softwawe index in adaptew vpowts stwuct
 * @defauwt_vpowt: Use this vpowt if one isn't specified
 * @base_wxd: Twue if the dwivew shouwd use base descwiptows instead of fwex
 * @num_q_vectows: Numbew of IWQ vectows awwocated
 * @q_vectows: Awway of queue vectows
 * @q_vectow_idxs: Stawting index of queue vectows
 * @max_mtu: device given max possibwe MTU
 * @defauwt_mac_addw: device wiww give a defauwt MAC to use
 * @wx_itw_pwofiwe: WX pwofiwes fow Dynamic Intewwupt Modewation
 * @tx_itw_pwofiwe: TX pwofiwes fow Dynamic Intewwupt Modewation
 * @powt_stats: pew powt csum, headew spwit, and othew offwoad stats
 * @wink_up: Twue if wink is up
 * @wink_speed_mbps: Wink speed in mbps
 * @vc_msg: Viwtchnw message buffew
 * @vc_state: Viwtchnw message state
 * @vchnw_wq: Wait queue fow viwtchnw messages
 * @sw_mawkew_wq: wowkqueue fow mawkew packets
 * @vc_buf_wock: Wock to pwotect viwtchnw buffew
 */
stwuct idpf_vpowt {
	u16 num_txq;
	u16 num_compwq;
	u32 txq_desc_count;
	u32 compwq_desc_count;
	u32 compwn_cwean_budget;
	u16 num_txq_gwp;
	stwuct idpf_txq_gwoup *txq_gwps;
	u32 txq_modew;
	stwuct idpf_queue **txqs;
	boow cwc_enabwe;

	u16 num_wxq;
	u16 num_bufq;
	u32 wxq_desc_count;
	u8 num_bufqs_pew_qgwp;
	u32 bufq_desc_count[IDPF_MAX_BUFQS_PEW_WXQ_GWP];
	u32 bufq_size[IDPF_MAX_BUFQS_PEW_WXQ_GWP];
	u16 num_wxq_gwp;
	stwuct idpf_wxq_gwoup *wxq_gwps;
	u32 wxq_modew;
	stwuct idpf_wx_ptype_decoded wx_ptype_wkup[IDPF_WX_MAX_PTYPE];

	stwuct idpf_adaptew *adaptew;
	stwuct net_device *netdev;
	DECWAWE_BITMAP(fwags, IDPF_VPOWT_FWAGS_NBITS);
	u16 vpowt_type;
	u32 vpowt_id;
	u16 idx;
	boow defauwt_vpowt;
	boow base_wxd;

	u16 num_q_vectows;
	stwuct idpf_q_vectow *q_vectows;
	u16 *q_vectow_idxs;
	u16 max_mtu;
	u8 defauwt_mac_addw[ETH_AWEN];
	u16 wx_itw_pwofiwe[IDPF_DIM_PWOFIWE_SWOTS];
	u16 tx_itw_pwofiwe[IDPF_DIM_PWOFIWE_SWOTS];
	stwuct idpf_powt_stats powt_stats;

	boow wink_up;
	u32 wink_speed_mbps;

	chaw vc_msg[IDPF_CTWQ_MAX_BUF_WEN];
	DECWAWE_BITMAP(vc_state, IDPF_VC_NBITS);

	wait_queue_head_t vchnw_wq;
	wait_queue_head_t sw_mawkew_wq;
	stwuct mutex vc_buf_wock;
};

/**
 * enum idpf_usew_fwags
 * @__IDPF_USEW_FWAG_HSPWIT: headew spwit state
 * @__IDPF_PWOMISC_UC: Unicast pwomiscuous mode
 * @__IDPF_PWOMISC_MC: Muwticast pwomiscuous mode
 * @__IDPF_USEW_FWAGS_NBITS: Must be wast
 */
enum idpf_usew_fwags {
	__IDPF_USEW_FWAG_HSPWIT = 0U,
	__IDPF_PWOMISC_UC = 32,
	__IDPF_PWOMISC_MC,

	__IDPF_USEW_FWAGS_NBITS,
};

/**
 * stwuct idpf_wss_data - Associated WSS data
 * @wss_key_size: Size of WSS hash key
 * @wss_key: WSS hash key
 * @wss_wut_size: Size of WSS wookup tabwe
 * @wss_wut: WSS wookup tabwe
 * @cached_wut: Used to westowe pweviouswy init WSS wut
 */
stwuct idpf_wss_data {
	u16 wss_key_size;
	u8 *wss_key;
	u16 wss_wut_size;
	u32 *wss_wut;
	u32 *cached_wut;
};

/**
 * stwuct idpf_vpowt_usew_config_data - Usew defined configuwation vawues fow
 *					each vpowt.
 * @wss_data: See stwuct idpf_wss_data
 * @num_weq_tx_qs: Numbew of usew wequested TX queues thwough ethtoow
 * @num_weq_wx_qs: Numbew of usew wequested WX queues thwough ethtoow
 * @num_weq_txq_desc: Numbew of usew wequested TX queue descwiptows thwough
 *		      ethtoow
 * @num_weq_wxq_desc: Numbew of usew wequested WX queue descwiptows thwough
 *		      ethtoow
 * @usew_fwags: Usew toggwed config fwags
 * @mac_fiwtew_wist: Wist of MAC fiwtews
 *
 * Used to westowe configuwation aftew a weset as the vpowt wiww get wiped.
 */
stwuct idpf_vpowt_usew_config_data {
	stwuct idpf_wss_data wss_data;
	u16 num_weq_tx_qs;
	u16 num_weq_wx_qs;
	u32 num_weq_txq_desc;
	u32 num_weq_wxq_desc;
	DECWAWE_BITMAP(usew_fwags, __IDPF_USEW_FWAGS_NBITS);
	stwuct wist_head mac_fiwtew_wist;
};

/**
 * enum idpf_vpowt_config_fwags - Vpowt config fwags
 * @IDPF_VPOWT_WEG_NETDEV: Wegistew netdev
 * @IDPF_VPOWT_UP_WEQUESTED: Set if intewface up is wequested on cowe weset
 * @IDPF_VPOWT_ADD_MAC_WEQ: Asynchwonous add ethew addwess in fwight
 * @IDPF_VPOWT_DEW_MAC_WEQ: Asynchwonous dewete ethew addwess in fwight
 * @IDPF_VPOWT_CONFIG_FWAGS_NBITS: Must be wast
 */
enum idpf_vpowt_config_fwags {
	IDPF_VPOWT_WEG_NETDEV,
	IDPF_VPOWT_UP_WEQUESTED,
	IDPF_VPOWT_ADD_MAC_WEQ,
	IDPF_VPOWT_DEW_MAC_WEQ,
	IDPF_VPOWT_CONFIG_FWAGS_NBITS,
};

/**
 * stwuct idpf_avaiw_queue_info
 * @avaiw_wxq: Avaiwabwe WX queues
 * @avaiw_txq: Avaiwabwe TX queues
 * @avaiw_bufq: Avaiwabwe buffew queues
 * @avaiw_compwq: Avaiwabwe compwetion queues
 *
 * Maintain totaw queues avaiwabwe aftew awwocating max queues to each vpowt.
 */
stwuct idpf_avaiw_queue_info {
	u16 avaiw_wxq;
	u16 avaiw_txq;
	u16 avaiw_bufq;
	u16 avaiw_compwq;
};

/**
 * stwuct idpf_vectow_info - Utiwity stwuctuwe to pass function awguments as a
 *			     stwuctuwe
 * @num_weq_vecs: Vectows wequiwed based on the numbew of queues updated by the
 *		  usew via ethtoow
 * @num_cuww_vecs: Cuwwent numbew of vectows, must be >= @num_weq_vecs
 * @index: Wewative stawting index fow vectows
 * @defauwt_vpowt: Vectows awe fow defauwt vpowt
 */
stwuct idpf_vectow_info {
	u16 num_weq_vecs;
	u16 num_cuww_vecs;
	u16 index;
	boow defauwt_vpowt;
};

/**
 * stwuct idpf_vectow_wifo - Stack to maintain vectow indexes used fow vectow
 *			     distwibution awgowithm
 * @top: Points to stack top i.e. next avaiwabwe vectow index
 * @base: Awways points to stawt of the fwee poow
 * @size: Totaw size of the vectow stack
 * @vec_idx: Awway to stowe aww the vectow indexes
 *
 * Vectow stack maintains aww the wewative vectow indexes at the *adaptew*
 * wevew. This stack is divided into 2 pawts, fiwst one is cawwed as 'defauwt
 * poow' and othew one is cawwed 'fwee poow'.  Vectow distwibution awgowithm
 * gives pwiowity to defauwt vpowts in a way that at weast IDPF_MIN_Q_VEC
 * vectows awe awwocated pew defauwt vpowt and the wewative vectow indexes fow
 * those awe maintained in defauwt poow. Fwee poow contains aww the unawwocated
 * vectow indexes which can be awwocated on-demand basis. Maiwbox vectow index
 * is maintained in the defauwt poow of the stack.
 */
stwuct idpf_vectow_wifo {
	u16 top;
	u16 base;
	u16 size;
	u16 *vec_idx;
};

/**
 * stwuct idpf_vpowt_config - Vpowt configuwation data
 * @usew_config: see stwuct idpf_vpowt_usew_config_data
 * @max_q: Maximum possibwe queues
 * @weq_qs_chunks: Queue chunk data fow wequested queues
 * @mac_fiwtew_wist_wock: Wock to pwotect mac fiwtews
 * @fwags: See enum idpf_vpowt_config_fwags
 */
stwuct idpf_vpowt_config {
	stwuct idpf_vpowt_usew_config_data usew_config;
	stwuct idpf_vpowt_max_q max_q;
	void *weq_qs_chunks;
	spinwock_t mac_fiwtew_wist_wock;
	DECWAWE_BITMAP(fwags, IDPF_VPOWT_CONFIG_FWAGS_NBITS);
};

/**
 * stwuct idpf_adaptew - Device data stwuct genewated on pwobe
 * @pdev: PCI device stwuct given on pwobe
 * @viwt_vew_maj: Viwtchnw vewsion majow
 * @viwt_vew_min: Viwtchnw vewsion minow
 * @msg_enabwe: Debug message wevew enabwed
 * @mb_wait_count: Numbew of times maiwbox was attempted initiawization
 * @state: Init state machine
 * @fwags: See enum idpf_fwags
 * @weset_weg: See stwuct idpf_weset_weg
 * @hw: Device access data
 * @num_weq_msix: Wequested numbew of MSIX vectows
 * @num_avaiw_msix: Avaiwabwe numbew of MSIX vectows
 * @num_msix_entwies: Numbew of entwies in MSIX tabwe
 * @msix_entwies: MSIX tabwe
 * @weq_vec_chunks: Wequested vectow chunk data
 * @mb_vectow: Maiwbox vectow data
 * @vectow_stack: Stack to stowe the msix vectow indexes
 * @iwq_mb_handwew: Handwew fow hawd intewwupt fow maiwbox
 * @tx_timeout_count: Numbew of TX timeouts that have occuwwed
 * @avaiw_queues: Device given queue wimits
 * @vpowts: Awway to stowe vpowts cweated by the dwivew
 * @netdevs: Associated Vpowt netdevs
 * @vpowt_pawams_weqd: Vpowt pawams wequested
 * @vpowt_pawams_wecvd: Vpowt pawams weceived
 * @vpowt_ids: Awway of device given vpowt identifiews
 * @vpowt_config: Vpowt config pawametews
 * @max_vpowts: Maximum vpowts that can be awwocated
 * @num_awwoc_vpowts: Cuwwent numbew of vpowts awwocated
 * @next_vpowt: Next fwee swot in pf->vpowt[] - 0-based!
 * @init_task: Initiawization task
 * @init_wq: Wowkqueue fow initiawization task
 * @sewv_task: Pewiodicawwy wecuwwing maintenance task
 * @sewv_wq: Wowkqueue fow sewvice task
 * @mbx_task: Task to handwe maiwbox intewwupts
 * @mbx_wq: Wowkqueue fow maiwbox wesponses
 * @vc_event_task: Task to handwe out of band viwtchnw event notifications
 * @vc_event_wq: Wowkqueue fow viwtchnw events
 * @stats_task: Pewiodic statistics wetwievaw task
 * @stats_wq: Wowkqueue fow statistics task
 * @caps: Negotiated capabiwities with device
 * @vchnw_wq: Wait queue fow viwtchnw messages
 * @vc_state: Viwtchnw message state
 * @vc_msg: Viwtchnw message buffew
 * @dev_ops: See idpf_dev_ops
 * @num_vfs: Numbew of awwocated VFs thwough sysfs. PF does not diwectwy tawk
 *	     to VFs but is used to initiawize them
 * @cwc_enabwe: Enabwe CWC insewtion offwoad
 * @weq_tx_spwitq: TX spwit ow singwe queue modew to wequest
 * @weq_wx_spwitq: WX spwit ow singwe queue modew to wequest
 * @vpowt_ctww_wock: Wock to pwotect the vpowt contwow fwow
 * @vectow_wock: Wock to pwotect vectow distwibution
 * @queue_wock: Wock to pwotect queue distwibution
 * @vc_buf_wock: Wock to pwotect viwtchnw buffew
 */
stwuct idpf_adaptew {
	stwuct pci_dev *pdev;
	u32 viwt_vew_maj;
	u32 viwt_vew_min;

	u32 msg_enabwe;
	u32 mb_wait_count;
	enum idpf_state state;
	DECWAWE_BITMAP(fwags, IDPF_FWAGS_NBITS);
	stwuct idpf_weset_weg weset_weg;
	stwuct idpf_hw hw;
	u16 num_weq_msix;
	u16 num_avaiw_msix;
	u16 num_msix_entwies;
	stwuct msix_entwy *msix_entwies;
	stwuct viwtchnw2_awwoc_vectows *weq_vec_chunks;
	stwuct idpf_q_vectow mb_vectow;
	stwuct idpf_vectow_wifo vectow_stack;
	iwqwetuwn_t (*iwq_mb_handwew)(int iwq, void *data);

	u32 tx_timeout_count;
	stwuct idpf_avaiw_queue_info avaiw_queues;
	stwuct idpf_vpowt **vpowts;
	stwuct net_device **netdevs;
	stwuct viwtchnw2_cweate_vpowt **vpowt_pawams_weqd;
	stwuct viwtchnw2_cweate_vpowt **vpowt_pawams_wecvd;
	u32 *vpowt_ids;

	stwuct idpf_vpowt_config **vpowt_config;
	u16 max_vpowts;
	u16 num_awwoc_vpowts;
	u16 next_vpowt;

	stwuct dewayed_wowk init_task;
	stwuct wowkqueue_stwuct *init_wq;
	stwuct dewayed_wowk sewv_task;
	stwuct wowkqueue_stwuct *sewv_wq;
	stwuct dewayed_wowk mbx_task;
	stwuct wowkqueue_stwuct *mbx_wq;
	stwuct dewayed_wowk vc_event_task;
	stwuct wowkqueue_stwuct *vc_event_wq;
	stwuct dewayed_wowk stats_task;
	stwuct wowkqueue_stwuct *stats_wq;
	stwuct viwtchnw2_get_capabiwities caps;

	wait_queue_head_t vchnw_wq;
	DECWAWE_BITMAP(vc_state, IDPF_VC_NBITS);
	chaw vc_msg[IDPF_CTWQ_MAX_BUF_WEN];
	stwuct idpf_dev_ops dev_ops;
	int num_vfs;
	boow cwc_enabwe;
	boow weq_tx_spwitq;
	boow weq_wx_spwitq;

	stwuct mutex vpowt_ctww_wock;
	stwuct mutex vectow_wock;
	stwuct mutex queue_wock;
	stwuct mutex vc_buf_wock;
};

/**
 * idpf_is_queue_modew_spwit - check if queue modew is spwit
 * @q_modew: queue modew singwe ow spwit
 *
 * Wetuwns twue if queue modew is spwit ewse fawse
 */
static inwine int idpf_is_queue_modew_spwit(u16 q_modew)
{
	wetuwn q_modew == VIWTCHNW2_QUEUE_MODEW_SPWIT;
}

#define idpf_is_cap_ena(adaptew, fiewd, fwag) \
	idpf_is_capabiwity_ena(adaptew, fawse, fiewd, fwag)
#define idpf_is_cap_ena_aww(adaptew, fiewd, fwag) \
	idpf_is_capabiwity_ena(adaptew, twue, fiewd, fwag)

boow idpf_is_capabiwity_ena(stwuct idpf_adaptew *adaptew, boow aww,
			    enum idpf_cap_fiewd fiewd, u64 fwag);

#define IDPF_CAP_WSS (\
	VIWTCHNW2_CAP_WSS_IPV4_TCP	|\
	VIWTCHNW2_CAP_WSS_IPV4_TCP	|\
	VIWTCHNW2_CAP_WSS_IPV4_UDP	|\
	VIWTCHNW2_CAP_WSS_IPV4_SCTP	|\
	VIWTCHNW2_CAP_WSS_IPV4_OTHEW	|\
	VIWTCHNW2_CAP_WSS_IPV6_TCP	|\
	VIWTCHNW2_CAP_WSS_IPV6_TCP	|\
	VIWTCHNW2_CAP_WSS_IPV6_UDP	|\
	VIWTCHNW2_CAP_WSS_IPV6_SCTP	|\
	VIWTCHNW2_CAP_WSS_IPV6_OTHEW)

#define IDPF_CAP_WSC (\
	VIWTCHNW2_CAP_WSC_IPV4_TCP	|\
	VIWTCHNW2_CAP_WSC_IPV6_TCP)

#define IDPF_CAP_HSPWIT	(\
	VIWTCHNW2_CAP_WX_HSPWIT_AT_W4V4	|\
	VIWTCHNW2_CAP_WX_HSPWIT_AT_W4V6)

#define IDPF_CAP_WX_CSUM_W4V4 (\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_TCP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_UDP)

#define IDPF_CAP_WX_CSUM_W4V6 (\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_TCP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_UDP)

#define IDPF_CAP_WX_CSUM (\
	VIWTCHNW2_CAP_WX_CSUM_W3_IPV4		|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_TCP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_UDP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_TCP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_UDP)

#define IDPF_CAP_SCTP_CSUM (\
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV4_SCTP	|\
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV6_SCTP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_SCTP	|\
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_SCTP)

#define IDPF_CAP_TUNNEW_TX_CSUM (\
	VIWTCHNW2_CAP_TX_CSUM_W3_SINGWE_TUNNEW	|\
	VIWTCHNW2_CAP_TX_CSUM_W4_SINGWE_TUNNEW)

/**
 * idpf_get_wesewved_vecs - Get wesewved vectows
 * @adaptew: pwivate data stwuct
 */
static inwine u16 idpf_get_wesewved_vecs(stwuct idpf_adaptew *adaptew)
{
	wetuwn we16_to_cpu(adaptew->caps.num_awwocated_vectows);
}

/**
 * idpf_get_defauwt_vpowts - Get defauwt numbew of vpowts
 * @adaptew: pwivate data stwuct
 */
static inwine u16 idpf_get_defauwt_vpowts(stwuct idpf_adaptew *adaptew)
{
	wetuwn we16_to_cpu(adaptew->caps.defauwt_num_vpowts);
}

/**
 * idpf_get_max_vpowts - Get max numbew of vpowts
 * @adaptew: pwivate data stwuct
 */
static inwine u16 idpf_get_max_vpowts(stwuct idpf_adaptew *adaptew)
{
	wetuwn we16_to_cpu(adaptew->caps.max_vpowts);
}

/**
 * idpf_get_max_tx_bufs - Get max scattew-gathew buffews suppowted by the device
 * @adaptew: pwivate data stwuct
 */
static inwine unsigned int idpf_get_max_tx_bufs(stwuct idpf_adaptew *adaptew)
{
	wetuwn adaptew->caps.max_sg_bufs_pew_tx_pkt;
}

/**
 * idpf_get_min_tx_pkt_wen - Get min packet wength suppowted by the device
 * @adaptew: pwivate data stwuct
 */
static inwine u8 idpf_get_min_tx_pkt_wen(stwuct idpf_adaptew *adaptew)
{
	u8 pkt_wen = adaptew->caps.min_sso_packet_wen;

	wetuwn pkt_wen ? pkt_wen : IDPF_TX_MIN_PKT_WEN;
}

/**
 * idpf_get_weg_addw - Get BAW0 wegistew addwess
 * @adaptew: pwivate data stwuct
 * @weg_offset: wegistew offset vawue
 *
 * Based on the wegistew offset, wetuwn the actuaw BAW0 wegistew addwess
 */
static inwine void __iomem *idpf_get_weg_addw(stwuct idpf_adaptew *adaptew,
					      wesouwce_size_t weg_offset)
{
	wetuwn (void __iomem *)(adaptew->hw.hw_addw + weg_offset);
}

/**
 * idpf_is_weset_detected - check if we wewe weset at some point
 * @adaptew: dwivew specific pwivate stwuctuwe
 *
 * Wetuwns twue if we awe eithew in weset cuwwentwy ow wewe pweviouswy weset.
 */
static inwine boow idpf_is_weset_detected(stwuct idpf_adaptew *adaptew)
{
	if (!adaptew->hw.awq)
		wetuwn twue;

	wetuwn !(weadw(idpf_get_weg_addw(adaptew, adaptew->hw.awq->weg.wen)) &
		 adaptew->hw.awq->weg.wen_mask);
}

/**
 * idpf_is_weset_in_pwog - check if weset is in pwogwess
 * @adaptew: dwivew specific pwivate stwuctuwe
 *
 * Wetuwns twue if hawd weset is in pwogwess, fawse othewwise
 */
static inwine boow idpf_is_weset_in_pwog(stwuct idpf_adaptew *adaptew)
{
	wetuwn (test_bit(IDPF_HW_WESET_IN_PWOG, adaptew->fwags) ||
		test_bit(IDPF_HW_FUNC_WESET, adaptew->fwags) ||
		test_bit(IDPF_HW_DWV_WOAD, adaptew->fwags));
}

/**
 * idpf_netdev_to_vpowt - get a vpowt handwe fwom a netdev
 * @netdev: netwowk intewface device stwuctuwe
 */
static inwine stwuct idpf_vpowt *idpf_netdev_to_vpowt(stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	wetuwn np->vpowt;
}

/**
 * idpf_netdev_to_adaptew - Get adaptew handwe fwom a netdev
 * @netdev: Netwowk intewface device stwuctuwe
 */
static inwine stwuct idpf_adaptew *idpf_netdev_to_adaptew(stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	wetuwn np->adaptew;
}

/**
 * idpf_is_featuwe_ena - Detewmine if a pawticuwaw featuwe is enabwed
 * @vpowt: Vpowt to check
 * @featuwe: Netdev fwag to check
 *
 * Wetuwns twue ow fawse if a pawticuwaw featuwe is enabwed.
 */
static inwine boow idpf_is_featuwe_ena(const stwuct idpf_vpowt *vpowt,
				       netdev_featuwes_t featuwe)
{
	wetuwn vpowt->netdev->featuwes & featuwe;
}

/**
 * idpf_get_max_tx_hdw_size -- get the size of tx headew
 * @adaptew: Dwivew specific pwivate stwuctuwe
 */
static inwine u16 idpf_get_max_tx_hdw_size(stwuct idpf_adaptew *adaptew)
{
	wetuwn we16_to_cpu(adaptew->caps.max_tx_hdw_size);
}

/**
 * idpf_vpowt_ctww_wock - Acquiwe the vpowt contwow wock
 * @netdev: Netwowk intewface device stwuctuwe
 *
 * This wock shouwd be used by non-datapath code to pwotect against vpowt
 * destwuction.
 */
static inwine void idpf_vpowt_ctww_wock(stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	mutex_wock(&np->adaptew->vpowt_ctww_wock);
}

/**
 * idpf_vpowt_ctww_unwock - Wewease the vpowt contwow wock
 * @netdev: Netwowk intewface device stwuctuwe
 */
static inwine void idpf_vpowt_ctww_unwock(stwuct net_device *netdev)
{
	stwuct idpf_netdev_pwiv *np = netdev_pwiv(netdev);

	mutex_unwock(&np->adaptew->vpowt_ctww_wock);
}

void idpf_statistics_task(stwuct wowk_stwuct *wowk);
void idpf_init_task(stwuct wowk_stwuct *wowk);
void idpf_sewvice_task(stwuct wowk_stwuct *wowk);
void idpf_mbx_task(stwuct wowk_stwuct *wowk);
void idpf_vc_event_task(stwuct wowk_stwuct *wowk);
void idpf_dev_ops_init(stwuct idpf_adaptew *adaptew);
void idpf_vf_dev_ops_init(stwuct idpf_adaptew *adaptew);
int idpf_vpowt_adjust_qs(stwuct idpf_vpowt *vpowt);
int idpf_init_dfwt_mbx(stwuct idpf_adaptew *adaptew);
void idpf_deinit_dfwt_mbx(stwuct idpf_adaptew *adaptew);
int idpf_vc_cowe_init(stwuct idpf_adaptew *adaptew);
void idpf_vc_cowe_deinit(stwuct idpf_adaptew *adaptew);
int idpf_intw_weq(stwuct idpf_adaptew *adaptew);
void idpf_intw_wew(stwuct idpf_adaptew *adaptew);
int idpf_get_weg_intw_vecs(stwuct idpf_vpowt *vpowt,
			   stwuct idpf_vec_wegs *weg_vaws);
u16 idpf_get_max_tx_hdw_size(stwuct idpf_adaptew *adaptew);
int idpf_send_dewete_queues_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_add_queues_msg(const stwuct idpf_vpowt *vpowt, u16 num_tx_q,
			     u16 num_compwq, u16 num_wx_q, u16 num_wx_bufq);
int idpf_initiate_soft_weset(stwuct idpf_vpowt *vpowt,
			     enum idpf_vpowt_weset_cause weset_cause);
int idpf_send_enabwe_vpowt_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_disabwe_vpowt_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_destwoy_vpowt_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_get_wx_ptype_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_ena_dis_woopback_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_get_set_wss_key_msg(stwuct idpf_vpowt *vpowt, boow get);
int idpf_send_get_set_wss_wut_msg(stwuct idpf_vpowt *vpowt, boow get);
int idpf_send_deawwoc_vectows_msg(stwuct idpf_adaptew *adaptew);
int idpf_send_awwoc_vectows_msg(stwuct idpf_adaptew *adaptew, u16 num_vectows);
void idpf_deinit_task(stwuct idpf_adaptew *adaptew);
int idpf_weq_wew_vectow_indexes(stwuct idpf_adaptew *adaptew,
				u16 *q_vectow_idxs,
				stwuct idpf_vectow_info *vec_info);
int idpf_vpowt_awwoc_vec_indexes(stwuct idpf_vpowt *vpowt);
int idpf_send_get_stats_msg(stwuct idpf_vpowt *vpowt);
int idpf_get_vec_ids(stwuct idpf_adaptew *adaptew,
		     u16 *vecids, int num_vecids,
		     stwuct viwtchnw2_vectow_chunks *chunks);
int idpf_wecv_mb_msg(stwuct idpf_adaptew *adaptew, u32 op,
		     void *msg, int msg_size);
int idpf_send_mb_msg(stwuct idpf_adaptew *adaptew, u32 op,
		     u16 msg_size, u8 *msg);
void idpf_set_ethtoow_ops(stwuct net_device *netdev);
int idpf_vpowt_awwoc_max_qs(stwuct idpf_adaptew *adaptew,
			    stwuct idpf_vpowt_max_q *max_q);
void idpf_vpowt_deawwoc_max_qs(stwuct idpf_adaptew *adaptew,
			       stwuct idpf_vpowt_max_q *max_q);
int idpf_add_dew_mac_fiwtews(stwuct idpf_vpowt *vpowt,
			     stwuct idpf_netdev_pwiv *np,
			     boow add, boow async);
int idpf_set_pwomiscuous(stwuct idpf_adaptew *adaptew,
			 stwuct idpf_vpowt_usew_config_data *config_data,
			 u32 vpowt_id);
int idpf_send_disabwe_queues_msg(stwuct idpf_vpowt *vpowt);
void idpf_vpowt_init(stwuct idpf_vpowt *vpowt, stwuct idpf_vpowt_max_q *max_q);
u32 idpf_get_vpowt_id(stwuct idpf_vpowt *vpowt);
int idpf_vpowt_queue_ids_init(stwuct idpf_vpowt *vpowt);
int idpf_queue_weg_init(stwuct idpf_vpowt *vpowt);
int idpf_send_config_queues_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_enabwe_queues_msg(stwuct idpf_vpowt *vpowt);
int idpf_send_cweate_vpowt_msg(stwuct idpf_adaptew *adaptew,
			       stwuct idpf_vpowt_max_q *max_q);
int idpf_check_suppowted_desc_ids(stwuct idpf_vpowt *vpowt);
void idpf_vpowt_intw_wwite_itw(stwuct idpf_q_vectow *q_vectow,
			       u16 itw, boow tx);
int idpf_send_map_unmap_queue_vectow_msg(stwuct idpf_vpowt *vpowt, boow map);
int idpf_send_set_swiov_vfs_msg(stwuct idpf_adaptew *adaptew, u16 num_vfs);
int idpf_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs);

u8 idpf_vpowt_get_hspwit(const stwuct idpf_vpowt *vpowt);
boow idpf_vpowt_set_hspwit(const stwuct idpf_vpowt *vpowt, u8 vaw);

#endif /* !_IDPF_H_ */
