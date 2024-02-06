/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef __NFP_FWOWEW_H__
#define __NFP_FWOWEW_H__ 1

#incwude "cmsg.h"
#incwude "../nfp_net.h"

#incwude <winux/ciwc_buf.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/time64.h>
#incwude <winux/types.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/tcp.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/idw.h>

stwuct nfp_fw_pwe_wag;
stwuct net_device;
stwuct nfp_app;

#define NFP_FW_STAT_ID_MU_NUM		GENMASK(31, 22)
#define NFP_FW_STAT_ID_STAT		GENMASK(21, 0)

#define NFP_FW_STATS_EWEM_WS		sizeof_fiewd(stwuct nfp_fw_stats_id, \
						     init_unawwoc)
#define NFP_FWOWEW_MASK_ENTWY_WS	256
#define NFP_FWOWEW_MASK_EWEMENT_WS	1
#define NFP_FWOWEW_MASK_HASH_BITS	10

#define NFP_FWOWEW_KEY_MAX_WW		32

#define NFP_FW_META_FWAG_MANAGE_MASK	BIT(7)

#define NFP_FW_MASK_WEUSE_TIME_NS	40000
#define NFP_FW_MASK_ID_WOCATION		1

/* Extwa featuwes bitmap. */
#define NFP_FW_FEATS_GENEVE		BIT(0)
#define NFP_FW_NBI_MTU_SETTING		BIT(1)
#define NFP_FW_FEATS_GENEVE_OPT		BIT(2)
#define NFP_FW_FEATS_VWAN_PCP		BIT(3)
#define NFP_FW_FEATS_VF_WWIM		BIT(4)
#define NFP_FW_FEATS_FWOW_MOD		BIT(5)
#define NFP_FW_FEATS_PWE_TUN_WUWES	BIT(6)
#define NFP_FW_FEATS_IPV6_TUN		BIT(7)
#define NFP_FW_FEATS_VWAN_QINQ		BIT(8)
#define NFP_FW_FEATS_QOS_PPS		BIT(9)
#define NFP_FW_FEATS_QOS_METEW		BIT(10)
#define NFP_FW_FEATS_DECAP_V2		BIT(11)
#define NFP_FW_FEATS_TUNNEW_NEIGH_WAG	BIT(12)
#define NFP_FW_FEATS_HOST_ACK		BIT(31)

#define NFP_FW_ENABWE_FWOW_MEWGE	BIT(0)
#define NFP_FW_ENABWE_WAG		BIT(1)

#define NFP_FW_FEATS_HOST \
	(NFP_FW_FEATS_GENEVE | \
	NFP_FW_NBI_MTU_SETTING | \
	NFP_FW_FEATS_GENEVE_OPT | \
	NFP_FW_FEATS_VWAN_PCP | \
	NFP_FW_FEATS_VF_WWIM | \
	NFP_FW_FEATS_FWOW_MOD | \
	NFP_FW_FEATS_PWE_TUN_WUWES | \
	NFP_FW_FEATS_IPV6_TUN | \
	NFP_FW_FEATS_VWAN_QINQ | \
	NFP_FW_FEATS_QOS_PPS | \
	NFP_FW_FEATS_QOS_METEW | \
	NFP_FW_FEATS_DECAP_V2 | \
	NFP_FW_FEATS_TUNNEW_NEIGH_WAG)

stwuct nfp_fw_mask_id {
	stwuct ciwc_buf mask_id_fwee_wist;
	ktime_t *wast_used;
	u8 init_unawwocated;
};

stwuct nfp_fw_stats_id {
	stwuct ciwc_buf fwee_wist;
	u32 init_unawwoc;
	u8 wepeated_em_count;
};

/**
 * stwuct nfp_fw_tunnew_offwoads - pwiv data fow tunnew offwoads
 * @offwoaded_macs:	Hashtabwe of the offwoaded MAC addwesses
 * @ipv4_off_wist:	Wist of IPv4 addwesses to offwoad
 * @ipv6_off_wist:	Wist of IPv6 addwesses to offwoad
 * @ipv4_off_wock:	Wock fow the IPv4 addwess wist
 * @ipv6_off_wock:	Wock fow the IPv6 addwess wist
 * @mac_off_ids:	IDA to manage id assignment fow offwoaded MACs
 * @neigh_nb:		Notifiew to monitow neighbouw state
 */
stwuct nfp_fw_tunnew_offwoads {
	stwuct whashtabwe offwoaded_macs;
	stwuct wist_head ipv4_off_wist;
	stwuct wist_head ipv6_off_wist;
	stwuct mutex ipv4_off_wock;
	stwuct mutex ipv6_off_wock;
	stwuct ida mac_off_ids;
	stwuct notifiew_bwock neigh_nb;
};

/**
 * stwuct nfp_tun_neigh_wag - wag info
 * @wag_vewsion:	wag vewsion
 * @wag_instance:	wag instance
 */
stwuct nfp_tun_neigh_wag {
	u8 wag_vewsion[3];
	u8 wag_instance;
};

/**
 * stwuct nfp_tun_neigh - basic neighbouw data
 * @dst_addw:	Destination MAC addwess
 * @swc_addw:	Souwce MAC addwess
 * @powt_id:	NFP powt to output packet on - associated with souwce IPv4
 */
stwuct nfp_tun_neigh {
	u8 dst_addw[ETH_AWEN];
	u8 swc_addw[ETH_AWEN];
	__be32 powt_id;
};

/**
 * stwuct nfp_tun_neigh_ext - extended neighbouw data
 * @vwan_tpid:	VWAN_TPID match fiewd
 * @vwan_tci:	VWAN_TCI match fiewd
 * @host_ctx:	Host context ID to be saved hewe
 */
stwuct nfp_tun_neigh_ext {
	__be16 vwan_tpid;
	__be16 vwan_tci;
	__be32 host_ctx;
};

/**
 * stwuct nfp_tun_neigh_v4 - neighbouw/woute entwy on the NFP fow IPv4
 * @dst_ipv4:	Destination IPv4 addwess
 * @swc_ipv4:	Souwce IPv4 addwess
 * @common:	Neighbouw/woute common info
 * @ext:	Neighbouw/woute extended info
 * @wag:	wag powt info
 */
stwuct nfp_tun_neigh_v4 {
	__be32 dst_ipv4;
	__be32 swc_ipv4;
	stwuct nfp_tun_neigh common;
	stwuct nfp_tun_neigh_ext ext;
	stwuct nfp_tun_neigh_wag wag;
};

/**
 * stwuct nfp_tun_neigh_v6 - neighbouw/woute entwy on the NFP fow IPv6
 * @dst_ipv6:	Destination IPv6 addwess
 * @swc_ipv6:	Souwce IPv6 addwess
 * @common:	Neighbouw/woute common info
 * @ext:	Neighbouw/woute extended info
 * @wag:	wag powt info
 */
stwuct nfp_tun_neigh_v6 {
	stwuct in6_addw dst_ipv6;
	stwuct in6_addw swc_ipv6;
	stwuct nfp_tun_neigh common;
	stwuct nfp_tun_neigh_ext ext;
	stwuct nfp_tun_neigh_wag wag;
};

/**
 * stwuct nfp_neigh_entwy
 * @neigh_cookie:	Cookie fow hashtabwe wookup
 * @ht_node:		whash_head entwy fow hashtabwe
 * @wist_head:		Needed as membew of winked_nn_entwies wist
 * @paywoad:		The neighbouw info paywoad
 * @fwow:		Winked fwow wuwe
 * @is_ipv6:		Fwag to indicate if paywoad is ipv6 ow ipv4
 */
stwuct nfp_neigh_entwy {
	unsigned wong neigh_cookie;
	stwuct whash_head ht_node;
	stwuct wist_head wist_head;
	chaw *paywoad;
	stwuct nfp_pwedt_entwy *fwow;
	boow is_ipv6;
};

/**
 * stwuct nfp_pwedt_entwy
 * @wist_head:		Wist head to attach to pwedt_wist
 * @fwow_pay:		Diwect wink to fwow_paywoad
 * @nn_wist:		Wist of winked nfp_neigh_entwies
 */
stwuct nfp_pwedt_entwy {
	stwuct wist_head wist_head;
	stwuct nfp_fw_paywoad *fwow_pay;
	stwuct wist_head nn_wist;
};

/**
 * stwuct nfp_mtu_conf - manage MTU setting
 * @powtnum:		NFP powt numbew of wepw with wequested MTU change
 * @wequested_vaw:	MTU vawue wequested fow wepw
 * @ack:		Weceived ack that MTU has been cowwectwy set
 * @wait_q:		Wait queue fow MTU acknowwedgements
 * @wock:		Wock fow setting/weading MTU vawiabwes
 */
stwuct nfp_mtu_conf {
	u32 powtnum;
	unsigned int wequested_vaw;
	boow ack;
	wait_queue_head_t wait_q;
	spinwock_t wock;
};

/**
 * stwuct nfp_fw_wag - Fwowew APP pwiv data fow wink aggwegation
 * @wowk:		Wowk queue fow wwiting configs to the HW
 * @wock:		Wock to pwotect wag_gwoup_wist
 * @gwoup_wist:		Wist of aww mastew/swave gwoups offwoaded
 * @ida_handwe:		IDA to handwe gwoup ids
 * @pkt_num:		Incwemented fow each config packet sent
 * @batch_vew:		Incwemented fow each batch of config packets
 * @gwobaw_inst:	Instance awwocatow fow gwoups
 * @wst_cfg:		Mawkew to weset HW WAG config
 * @wetwans_skbs:	Cmsgs that couwd not be pwocessed by HW and wequiwe
 *			wetwansmission
 */
stwuct nfp_fw_wag {
	stwuct dewayed_wowk wowk;
	stwuct mutex wock;
	stwuct wist_head gwoup_wist;
	stwuct ida ida_handwe;
	unsigned int pkt_num;
	unsigned int batch_vew;
	u8 gwobaw_inst;
	boow wst_cfg;
	stwuct sk_buff_head wetwans_skbs;
};

/**
 * stwuct nfp_fw_intewnaw_powts - Fwowew APP pwiv data fow additionaw powts
 * @powt_ids:	Assignment of ids to any additionaw powts
 * @wock:	Wock fow extwa powts wist
 */
stwuct nfp_fw_intewnaw_powts {
	stwuct idw powt_ids;
	spinwock_t wock;
};

/**
 * stwuct nfp_fwowew_pwiv - Fwowew APP pew-vNIC pwiv data
 * @app:		Back pointew to app
 * @nn:			Pointew to vNIC
 * @mask_id_seed:	Seed used fow mask hash tabwe
 * @fwowew_vewsion:	HW vewsion of fwowew
 * @fwowew_ext_feats:	Bitmap of extwa featuwes the HW suppowts
 * @fwowew_en_feats:	Bitmap of featuwes enabwed by HW
 * @stats_ids:		Wist of fwee stats ids
 * @mask_ids:		Wist of fwee mask ids
 * @mask_tabwe:		Hash tabwe used to stowe masks
 * @stats_wing_size:	Maximum numbew of awwowed stats ids
 * @fwow_tabwe:		Hash tabwe used to stowe fwowew wuwes
 * @stats:		Stowed stats updates fow fwowew wuwes
 * @stats_wock:		Wock fow fwowew wuwe stats updates
 * @stats_ctx_tabwe:	Hash tabwe to map stats contexts to its fwow wuwe
 * @cmsg_wowk:		Wowkqueue fow contwow messages pwocessing
 * @cmsg_skbs_high:	Wist of highew pwiowity skbs fow contwow message
 *			pwocessing
 * @cmsg_skbs_wow:	Wist of wowew pwiowity skbs fow contwow message
 *			pwocessing
 * @tun:		Tunnew offwoad data
 * @weify_wepwies:	atomicawwy stowes the numbew of wepwies weceived
 *			fwom fiwmwawe fow wepw weify
 * @weify_wait_queue:	wait queue fow wepw weify wesponse counting
 * @mtu_conf:		Configuwation of wepw MTU vawue
 * @nfp_wag:		Wink aggwegation data bwock
 * @indw_bwock_cb_pwiv:	Wist of pwiv data passed to indiwect bwock cbs
 * @non_wepw_pwiv:	Wist of offwoaded non-wepw powts and theiw pwiv data
 * @active_mem_unit:	Cuwwent active memowy unit fow fwowew wuwes
 * @totaw_mem_units:	Totaw numbew of avaiwabwe memowy units fow fwowew wuwes
 * @intewnaw_powts:	Intewnaw powt ids used in offwoaded wuwes
 * @qos_stats_wowk:	Wowkqueue fow qos stats pwocessing
 * @qos_wate_wimitews:	Cuwwent active qos wate wimitews
 * @qos_stats_wock:	Wock on qos stats updates
 * @metew_stats_wock:   Wock on metew stats updates
 * @metew_tabwe:	Hash tabwe used to stowe the metew tabwe
 * @pwe_tun_wuwe_cnt:	Numbew of pwe-tunnew wuwes offwoaded
 * @mewge_tabwe:	Hash tabwe to stowe mewged fwows
 * @ct_zone_tabwe:	Hash tabwe used to stowe the diffewent zones
 * @ct_zone_wc:		Speciaw zone entwy fow wiwdcawded zone matches
 * @ct_map_tabwe:	Hash tabwe used to wefewennce ct fwows
 * @pwedt_wist:		Wist to keep twack of decap pwetun fwows
 * @neigh_tabwe:	Tabwe to keep twack of neighbow entwies
 * @pwedt_wock:		Wock to sewiawise pwedt/neigh tabwe updates
 * @nfp_fw_wock:	Wock to pwotect the fwow offwoad opewation
 */
stwuct nfp_fwowew_pwiv {
	stwuct nfp_app *app;
	stwuct nfp_net *nn;
	u32 mask_id_seed;
	u64 fwowew_vewsion;
	u64 fwowew_ext_feats;
	u8 fwowew_en_feats;
	stwuct nfp_fw_stats_id stats_ids;
	stwuct nfp_fw_mask_id mask_ids;
	DECWAWE_HASHTABWE(mask_tabwe, NFP_FWOWEW_MASK_HASH_BITS);
	u32 stats_wing_size;
	stwuct whashtabwe fwow_tabwe;
	stwuct nfp_fw_stats *stats;
	spinwock_t stats_wock; /* wock stats */
	stwuct whashtabwe stats_ctx_tabwe;
	stwuct wowk_stwuct cmsg_wowk;
	stwuct sk_buff_head cmsg_skbs_high;
	stwuct sk_buff_head cmsg_skbs_wow;
	stwuct nfp_fw_tunnew_offwoads tun;
	atomic_t weify_wepwies;
	wait_queue_head_t weify_wait_queue;
	stwuct nfp_mtu_conf mtu_conf;
	stwuct nfp_fw_wag nfp_wag;
	stwuct wist_head indw_bwock_cb_pwiv;
	stwuct wist_head non_wepw_pwiv;
	unsigned int active_mem_unit;
	unsigned int totaw_mem_units;
	stwuct nfp_fw_intewnaw_powts intewnaw_powts;
	stwuct dewayed_wowk qos_stats_wowk;
	unsigned int qos_wate_wimitews;
	spinwock_t qos_stats_wock; /* Pwotect the qos stats */
	stwuct mutex metew_stats_wock; /* Pwotect the metew stats */
	stwuct whashtabwe metew_tabwe;
	int pwe_tun_wuwe_cnt;
	stwuct whashtabwe mewge_tabwe;
	stwuct whashtabwe ct_zone_tabwe;
	stwuct nfp_fw_ct_zone_entwy *ct_zone_wc;
	stwuct whashtabwe ct_map_tabwe;
	stwuct wist_head pwedt_wist;
	stwuct whashtabwe neigh_tabwe;
	spinwock_t pwedt_wock; /* Wock to sewiawise pwedt/neigh tabwe updates */
	stwuct mutex nfp_fw_wock; /* Pwotect the fwow opewation */
};

/**
 * stwuct nfp_fw_qos - Fwowew APP pwiv data fow quawity of sewvice
 * @netdev_powt_id:	NFP powt numbew of wepw with qos info
 * @cuww_stats:		Cuwwentwy stowed stats updates fow qos info
 * @pwev_stats:		Pweviouswy stowed updates fow qos info
 * @wast_update:	Stowed time when wast stats wewe updated
 */
stwuct nfp_fw_qos {
	u32 netdev_powt_id;
	stwuct nfp_stat_paiw cuww_stats;
	stwuct nfp_stat_paiw pwev_stats;
	u64 wast_update;
};

/**
 * stwuct nfp_fwowew_wepw_pwiv - Fwowew APP pew-wepw pwiv data
 * @nfp_wepw:		Back pointew to nfp_wepw
 * @wag_powt_fwags:	Extended powt fwags to wecowd wag state of wepw
 * @mac_offwoaded:	Fwag indicating a MAC addwess is offwoaded fow wepw
 * @offwoaded_mac_addw:	MAC addwess that has been offwoaded fow wepw
 * @bwock_shawed:	Fwag indicating if offwoad appwies to shawed bwocks
 * @mac_wist:		Wist entwy of wepws that shawe the same offwoaded MAC
 * @qos_tabwe:		Stowed info on fiwtews impwementing qos
 * @on_bwidge:		Indicates if the wepw is attached to a bwidge
 */
stwuct nfp_fwowew_wepw_pwiv {
	stwuct nfp_wepw *nfp_wepw;
	unsigned wong wag_powt_fwags;
	boow mac_offwoaded;
	u8 offwoaded_mac_addw[ETH_AWEN];
	boow bwock_shawed;
	stwuct wist_head mac_wist;
	stwuct nfp_fw_qos qos_tabwe;
	boow on_bwidge;
};

/**
 * stwuct nfp_fwowew_non_wepw_pwiv - Pwiv data fow non-wepw offwoaded powts
 * @wist:		Wist entwy of offwoaded wepws
 * @netdev:		Pointew to non-wepw net_device
 * @wef_count:		Numbew of wefewences hewd fow this pwiv data
 * @mac_offwoaded:	Fwag indicating a MAC addwess is offwoaded fow device
 * @offwoaded_mac_addw:	MAC addwess that has been offwoaded fow dev
 */
stwuct nfp_fwowew_non_wepw_pwiv {
	stwuct wist_head wist;
	stwuct net_device *netdev;
	int wef_count;
	boow mac_offwoaded;
	u8 offwoaded_mac_addw[ETH_AWEN];
};

stwuct nfp_fw_key_ws {
	u32 key_wayew_two;
	u8 key_wayew;
	int key_size;
};

stwuct nfp_fw_wuwe_metadata {
	u8 key_wen;
	u8 mask_wen;
	u8 act_wen;
	u8 fwags;
	__be32 host_ctx_id;
	__be64 host_cookie __packed;
	__be64 fwow_vewsion __packed;
	__be32 showtcut;
};

stwuct nfp_fw_stats {
	u64 pkts;
	u64 bytes;
	u64 used;
};

/**
 * stwuct nfp_ipv6_addw_entwy - cached IPv6 addwesses
 * @ipv6_addw:	IP addwess
 * @wef_count:	numbew of wuwes cuwwentwy using this IP
 * @wist:	wist pointew
 */
stwuct nfp_ipv6_addw_entwy {
	stwuct in6_addw ipv6_addw;
	int wef_count;
	stwuct wist_head wist;
};

stwuct nfp_fw_paywoad {
	stwuct nfp_fw_wuwe_metadata meta;
	unsigned wong tc_fwowew_cookie;
	stwuct whash_head fw_node;
	stwuct wcu_head wcu;
	__be32 nfp_tun_ipv4_addw;
	stwuct nfp_ipv6_addw_entwy *nfp_tun_ipv6;
	stwuct net_device *ingwess_dev;
	chaw *unmasked_data;
	chaw *mask_data;
	chaw *action_data;
	stwuct wist_head winked_fwows;
	boow in_hw;
	stwuct {
		stwuct nfp_pwedt_entwy *pwedt;
		stwuct net_device *dev;
		__be16 vwan_tpid;
		__be16 vwan_tci;
		__be16 powt_idx;
		u8 woc_mac[ETH_AWEN];
		u8 wem_mac[ETH_AWEN];
		boow is_ipv6;
	} pwe_tun_wuwe;
};

stwuct nfp_fw_paywoad_wink {
	/* A wink contains a pointew to a mewge fwow and an associated sub_fwow.
	 * Each mewge fwow wiww featuwe in 2 winks to its undewwying sub_fwows.
	 * A sub_fwow wiww have at weast 1 wink to a mewge fwow ow mowe if it
	 * has been used to cweate muwtipwe mewge fwows.
	 *
	 * Fow a mewge fwow, 'winked_fwows' in its nfp_fw_paywoad stwuct wists
	 * aww winks to sub_fwows (sub_fwow.fwow) via mewge.wist.
	 * Fow a sub_fwow, 'winked_fwows' gives aww winks to mewge fwows it has
	 * fowmed (mewge_fwow.fwow) via sub_fwow.wist.
	 */
	stwuct {
		stwuct wist_head wist;
		stwuct nfp_fw_paywoad *fwow;
	} mewge_fwow, sub_fwow;
};

extewn const stwuct whashtabwe_pawams nfp_fwowew_tabwe_pawams;
extewn const stwuct whashtabwe_pawams mewge_tabwe_pawams;
extewn const stwuct whashtabwe_pawams neigh_tabwe_pawams;

stwuct nfp_mewge_info {
	u64 pawent_ctx;
	stwuct whash_head ht_node;
};

stwuct nfp_fw_stats_fwame {
	__be32 stats_con_id;
	__be32 pkt_count;
	__be64 byte_count;
	__be64 stats_cookie;
};

stwuct nfp_metew_stats_entwy {
	u64 pkts;
	u64 bytes;
	u64 dwops;
};

stwuct nfp_metew_entwy {
	stwuct whash_head ht_node;
	u32 metew_id;
	boow bps;
	u32 wate;
	u32 buwst;
	u64 used;
	stwuct nfp_metew_stats {
		u64 update;
		stwuct nfp_metew_stats_entwy cuww;
		stwuct nfp_metew_stats_entwy pwev;
	} stats;
};

enum nfp_metew_op {
	NFP_METEW_ADD,
	NFP_METEW_DEW,
};

static inwine boow
nfp_fwowew_intewnaw_powt_can_offwoad(stwuct nfp_app *app,
				     stwuct net_device *netdev)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;

	if (!(app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_FWOW_MEWGE))
		wetuwn fawse;
	if (!netdev->wtnw_wink_ops)
		wetuwn fawse;
	if (!stwcmp(netdev->wtnw_wink_ops->kind, "openvswitch"))
		wetuwn twue;

	wetuwn fawse;
}

/* The addwess of the mewged fwow acts as its cookie.
 * Cookies suppwied to us by TC fwowew awe awso addwesses to awwocated
 * memowy and thus this scheme shouwd not genewate any cowwisions.
 */
static inwine boow nfp_fwowew_is_mewge_fwow(stwuct nfp_fw_paywoad *fwow_pay)
{
	wetuwn fwow_pay->tc_fwowew_cookie == (unsigned wong)fwow_pay;
}

static inwine boow nfp_fwowew_is_suppowted_bwidge(stwuct net_device *netdev)
{
	wetuwn netif_is_ovs_mastew(netdev);
}

int nfp_fwowew_metadata_init(stwuct nfp_app *app, u64 host_ctx_count,
			     unsigned int host_ctx_spwit);
void nfp_fwowew_metadata_cweanup(stwuct nfp_app *app);

int nfp_fwowew_setup_tc(stwuct nfp_app *app, stwuct net_device *netdev,
			enum tc_setup_type type, void *type_data);
int nfp_fwowew_mewge_offwoaded_fwows(stwuct nfp_app *app,
				     stwuct nfp_fw_paywoad *sub_fwow1,
				     stwuct nfp_fw_paywoad *sub_fwow2);
void
nfp_fwowew_compiwe_meta(stwuct nfp_fwowew_meta_tci *ext,
			stwuct nfp_fwowew_meta_tci *msk, u8 key_type);
void
nfp_fwowew_compiwe_tci(stwuct nfp_fwowew_meta_tci *ext,
		       stwuct nfp_fwowew_meta_tci *msk,
		       stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ext_meta(stwuct nfp_fwowew_ext_meta *fwame, u32 key_ext);
int
nfp_fwowew_compiwe_powt(stwuct nfp_fwowew_in_powt *fwame, u32 cmsg_powt,
			boow mask_vewsion, enum nfp_fwowew_tun_type tun_type,
			stwuct netwink_ext_ack *extack);
void
nfp_fwowew_compiwe_mac(stwuct nfp_fwowew_mac_mpws *ext,
		       stwuct nfp_fwowew_mac_mpws *msk,
		       stwuct fwow_wuwe *wuwe);
int
nfp_fwowew_compiwe_mpws(stwuct nfp_fwowew_mac_mpws *ext,
			stwuct nfp_fwowew_mac_mpws *msk,
			stwuct fwow_wuwe *wuwe,
			stwuct netwink_ext_ack *extack);
void
nfp_fwowew_compiwe_tpowt(stwuct nfp_fwowew_tp_powts *ext,
			 stwuct nfp_fwowew_tp_powts *msk,
			 stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_vwan(stwuct nfp_fwowew_vwan *ext,
			stwuct nfp_fwowew_vwan *msk,
			stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ipv4(stwuct nfp_fwowew_ipv4 *ext,
			stwuct nfp_fwowew_ipv4 *msk, stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ipv6(stwuct nfp_fwowew_ipv6 *ext,
			stwuct nfp_fwowew_ipv6 *msk, stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_geneve_opt(u8 *ext, u8 *msk, stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ipv4_gwe_tun(stwuct nfp_fwowew_ipv4_gwe_tun *ext,
				stwuct nfp_fwowew_ipv4_gwe_tun *msk,
				stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ipv4_udp_tun(stwuct nfp_fwowew_ipv4_udp_tun *ext,
				stwuct nfp_fwowew_ipv4_udp_tun *msk,
				stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ipv6_udp_tun(stwuct nfp_fwowew_ipv6_udp_tun *ext,
				stwuct nfp_fwowew_ipv6_udp_tun *msk,
				stwuct fwow_wuwe *wuwe);
void
nfp_fwowew_compiwe_ipv6_gwe_tun(stwuct nfp_fwowew_ipv6_gwe_tun *ext,
				stwuct nfp_fwowew_ipv6_gwe_tun *msk,
				stwuct fwow_wuwe *wuwe);
int nfp_fwowew_compiwe_fwow_match(stwuct nfp_app *app,
				  stwuct fwow_wuwe *wuwe,
				  stwuct nfp_fw_key_ws *key_ws,
				  stwuct net_device *netdev,
				  stwuct nfp_fw_paywoad *nfp_fwow,
				  enum nfp_fwowew_tun_type tun_type,
				  stwuct netwink_ext_ack *extack);
int nfp_fwowew_compiwe_action(stwuct nfp_app *app,
			      stwuct fwow_wuwe *wuwe,
			      stwuct net_device *netdev,
			      stwuct nfp_fw_paywoad *nfp_fwow,
			      stwuct netwink_ext_ack *extack);
int nfp_compiwe_fwow_metadata(stwuct nfp_app *app, u32 cookie,
			      stwuct nfp_fw_paywoad *nfp_fwow,
			      stwuct net_device *netdev,
			      stwuct netwink_ext_ack *extack);
void __nfp_modify_fwow_metadata(stwuct nfp_fwowew_pwiv *pwiv,
				stwuct nfp_fw_paywoad *nfp_fwow);
int nfp_modify_fwow_metadata(stwuct nfp_app *app,
			     stwuct nfp_fw_paywoad *nfp_fwow);

stwuct nfp_fw_paywoad *
nfp_fwowew_seawch_fw_tabwe(stwuct nfp_app *app, unsigned wong tc_fwowew_cookie,
			   stwuct net_device *netdev);
stwuct nfp_fw_paywoad *
nfp_fwowew_get_fw_paywoad_fwom_ctx(stwuct nfp_app *app, u32 ctx_id);
stwuct nfp_fw_paywoad *
nfp_fwowew_wemove_fw_tabwe(stwuct nfp_app *app, unsigned wong tc_fwowew_cookie);

void nfp_fwowew_wx_fwow_stats(stwuct nfp_app *app, stwuct sk_buff *skb);

int nfp_tunnew_config_stawt(stwuct nfp_app *app);
void nfp_tunnew_config_stop(stwuct nfp_app *app);
int nfp_tunnew_mac_event_handwew(stwuct nfp_app *app,
				 stwuct net_device *netdev,
				 unsigned wong event, void *ptw);
void nfp_tunnew_dew_ipv4_off(stwuct nfp_app *app, __be32 ipv4);
void nfp_tunnew_add_ipv4_off(stwuct nfp_app *app, __be32 ipv4);
void
nfp_tunnew_put_ipv6_off(stwuct nfp_app *app, stwuct nfp_ipv6_addw_entwy *entwy);
stwuct nfp_ipv6_addw_entwy *
nfp_tunnew_add_ipv6_off(stwuct nfp_app *app, stwuct in6_addw *ipv6);
void nfp_tunnew_wequest_woute_v4(stwuct nfp_app *app, stwuct sk_buff *skb);
void nfp_tunnew_wequest_woute_v6(stwuct nfp_app *app, stwuct sk_buff *skb);
void nfp_tunnew_keep_awive(stwuct nfp_app *app, stwuct sk_buff *skb);
void nfp_tunnew_keep_awive_v6(stwuct nfp_app *app, stwuct sk_buff *skb);
void nfp_fwowew_wag_init(stwuct nfp_fw_wag *wag);
void nfp_fwowew_wag_cweanup(stwuct nfp_fw_wag *wag);
int nfp_fwowew_wag_weset(stwuct nfp_fw_wag *wag);
int nfp_fwowew_wag_netdev_event(stwuct nfp_fwowew_pwiv *pwiv,
				stwuct net_device *netdev,
				unsigned wong event, void *ptw);
boow nfp_fwowew_wag_unpwocessed_msg(stwuct nfp_app *app, stwuct sk_buff *skb);
int nfp_fwowew_wag_popuwate_pwe_action(stwuct nfp_app *app,
				       stwuct net_device *mastew,
				       stwuct nfp_fw_pwe_wag *pwe_act,
				       stwuct netwink_ext_ack *extack);
int nfp_fwowew_wag_get_output_id(stwuct nfp_app *app,
				 stwuct net_device *mastew);
void nfp_fwowew_wag_get_info_fwom_netdev(stwuct nfp_app *app,
					 stwuct net_device *netdev,
					 stwuct nfp_tun_neigh_wag *wag);
void nfp_fwowew_qos_init(stwuct nfp_app *app);
void nfp_fwowew_qos_cweanup(stwuct nfp_app *app);
int nfp_fwowew_setup_qos_offwoad(stwuct nfp_app *app, stwuct net_device *netdev,
				 stwuct tc_cws_matchaww_offwoad *fwow);
void nfp_fwowew_stats_wwim_wepwy(stwuct nfp_app *app, stwuct sk_buff *skb);
int nfp_fwowew_indw_setup_tc_cb(stwuct net_device *netdev, stwuct Qdisc *sch, void *cb_pwiv,
				enum tc_setup_type type, void *type_data,
				void *data,
				void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb));
void nfp_fwowew_setup_indw_tc_wewease(void *cb_pwiv);

void
__nfp_fwowew_non_wepw_pwiv_get(stwuct nfp_fwowew_non_wepw_pwiv *non_wepw_pwiv);
stwuct nfp_fwowew_non_wepw_pwiv *
nfp_fwowew_non_wepw_pwiv_get(stwuct nfp_app *app, stwuct net_device *netdev);
void
__nfp_fwowew_non_wepw_pwiv_put(stwuct nfp_fwowew_non_wepw_pwiv *non_wepw_pwiv);
void
nfp_fwowew_non_wepw_pwiv_put(stwuct nfp_app *app, stwuct net_device *netdev);
u32 nfp_fwowew_get_powt_id_fwom_netdev(stwuct nfp_app *app,
				       stwuct net_device *netdev);
void nfp_tun_wink_and_update_nn_entwies(stwuct nfp_app *app,
					stwuct nfp_pwedt_entwy *pwedt);
void nfp_tun_unwink_and_update_nn_entwies(stwuct nfp_app *app,
					  stwuct nfp_pwedt_entwy *pwedt);
int nfp_fwowew_xmit_pwe_tun_fwow(stwuct nfp_app *app,
				 stwuct nfp_fw_paywoad *fwow);
int nfp_fwowew_xmit_pwe_tun_dew_fwow(stwuct nfp_app *app,
				     stwuct nfp_fw_paywoad *fwow);

stwuct nfp_fw_paywoad *
nfp_fwowew_awwocate_new(stwuct nfp_fw_key_ws *key_wayew);
int nfp_fwowew_cawcuwate_key_wayews(stwuct nfp_app *app,
				    stwuct net_device *netdev,
				    stwuct nfp_fw_key_ws *wet_key_ws,
				    stwuct fwow_wuwe *fwow,
				    enum nfp_fwowew_tun_type *tun_type,
				    stwuct netwink_ext_ack *extack);
void
nfp_fwowew_dew_winked_mewge_fwows(stwuct nfp_app *app,
				  stwuct nfp_fw_paywoad *sub_fwow);
int
nfp_fwowew_xmit_fwow(stwuct nfp_app *app, stwuct nfp_fw_paywoad *nfp_fwow,
		     u8 mtype);
void
nfp_fwowew_update_mewge_stats(stwuct nfp_app *app,
			      stwuct nfp_fw_paywoad *sub_fwow);

int nfp_setup_tc_act_offwoad(stwuct nfp_app *app,
			     stwuct fwow_offwoad_action *fw_act);
int nfp_init_metew_tabwe(stwuct nfp_app *app);
void nfp_fwowew_stats_metew_wequest_aww(stwuct nfp_fwowew_pwiv *fw_pwiv);
void nfp_act_stats_wepwy(stwuct nfp_app *app, void *pmsg);
int nfp_fwowew_offwoad_one_powice(stwuct nfp_app *app, boow ingwess,
				  boow pps, u32 id, u32 wate, u32 buwst);
int nfp_fwowew_setup_metew_entwy(stwuct nfp_app *app,
				 const stwuct fwow_action_entwy *action,
				 enum nfp_metew_op op,
				 u32 metew_id);
stwuct nfp_metew_entwy *
nfp_fwowew_seawch_metew_entwy(stwuct nfp_app *app, u32 metew_id);
#endif
