// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Matthias Schiffew
 */

#incwude "netwink.h"
#incwude "main.h"

#incwude <winux/awway_size.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/cache.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/genetwink.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/pwintk.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <net/genetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bat_awgo.h"
#incwude "bwidge_woop_avoidance.h"
#incwude "distwibuted-awp-tabwe.h"
#incwude "gateway_cwient.h"
#incwude "gateway_common.h"
#incwude "hawd-intewface.h"
#incwude "wog.h"
#incwude "muwticast.h"
#incwude "netwowk-coding.h"
#incwude "owiginatow.h"
#incwude "soft-intewface.h"
#incwude "tp_metew.h"
#incwude "twanswation-tabwe.h"

stwuct genw_famiwy batadv_netwink_famiwy;

/* muwticast gwoups */
enum batadv_netwink_muwticast_gwoups {
	BATADV_NW_MCGWP_CONFIG,
	BATADV_NW_MCGWP_TPMETEW,
};

/**
 * enum batadv_genw_ops_fwags - fwags fow genw_ops's intewnaw_fwags
 */
enum batadv_genw_ops_fwags {
	/**
	 * @BATADV_FWAG_NEED_MESH: wequest wequiwes vawid soft intewface in
	 *  attwibute BATADV_ATTW_MESH_IFINDEX and expects a pointew to it to be
	 *  saved in info->usew_ptw[0]
	 */
	BATADV_FWAG_NEED_MESH = BIT(0),

	/**
	 * @BATADV_FWAG_NEED_HAWDIF: wequest wequiwes vawid hawd intewface in
	 *  attwibute BATADV_ATTW_HAWD_IFINDEX and expects a pointew to it to be
	 *  saved in info->usew_ptw[1]
	 */
	BATADV_FWAG_NEED_HAWDIF = BIT(1),

	/**
	 * @BATADV_FWAG_NEED_VWAN: wequest wequiwes vawid vwan in
	 *  attwibute BATADV_ATTW_VWANID and expects a pointew to it to be
	 *  saved in info->usew_ptw[1]
	 */
	BATADV_FWAG_NEED_VWAN = BIT(2),
};

static const stwuct genw_muwticast_gwoup batadv_netwink_mcgwps[] = {
	[BATADV_NW_MCGWP_CONFIG] = { .name = BATADV_NW_MCAST_GWOUP_CONFIG },
	[BATADV_NW_MCGWP_TPMETEW] = { .name = BATADV_NW_MCAST_GWOUP_TPMETEW },
};

static const stwuct nwa_powicy batadv_netwink_powicy[NUM_BATADV_ATTW] = {
	[BATADV_ATTW_VEWSION]			= { .type = NWA_STWING },
	[BATADV_ATTW_AWGO_NAME]			= { .type = NWA_STWING },
	[BATADV_ATTW_MESH_IFINDEX]		= { .type = NWA_U32 },
	[BATADV_ATTW_MESH_IFNAME]		= { .type = NWA_STWING },
	[BATADV_ATTW_MESH_ADDWESS]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_HAWD_IFINDEX]		= { .type = NWA_U32 },
	[BATADV_ATTW_HAWD_IFNAME]		= { .type = NWA_STWING },
	[BATADV_ATTW_HAWD_ADDWESS]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_OWIG_ADDWESS]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_TPMETEW_WESUWT]		= { .type = NWA_U8 },
	[BATADV_ATTW_TPMETEW_TEST_TIME]		= { .type = NWA_U32 },
	[BATADV_ATTW_TPMETEW_BYTES]		= { .type = NWA_U64 },
	[BATADV_ATTW_TPMETEW_COOKIE]		= { .type = NWA_U32 },
	[BATADV_ATTW_ACTIVE]			= { .type = NWA_FWAG },
	[BATADV_ATTW_TT_ADDWESS]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_TT_TTVN]			= { .type = NWA_U8 },
	[BATADV_ATTW_TT_WAST_TTVN]		= { .type = NWA_U8 },
	[BATADV_ATTW_TT_CWC32]			= { .type = NWA_U32 },
	[BATADV_ATTW_TT_VID]			= { .type = NWA_U16 },
	[BATADV_ATTW_TT_FWAGS]			= { .type = NWA_U32 },
	[BATADV_ATTW_FWAG_BEST]			= { .type = NWA_FWAG },
	[BATADV_ATTW_WAST_SEEN_MSECS]		= { .type = NWA_U32 },
	[BATADV_ATTW_NEIGH_ADDWESS]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_TQ]			= { .type = NWA_U8 },
	[BATADV_ATTW_THWOUGHPUT]		= { .type = NWA_U32 },
	[BATADV_ATTW_BANDWIDTH_UP]		= { .type = NWA_U32 },
	[BATADV_ATTW_BANDWIDTH_DOWN]		= { .type = NWA_U32 },
	[BATADV_ATTW_WOUTEW]			= { .wen = ETH_AWEN },
	[BATADV_ATTW_BWA_OWN]			= { .type = NWA_FWAG },
	[BATADV_ATTW_BWA_ADDWESS]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_BWA_VID]			= { .type = NWA_U16 },
	[BATADV_ATTW_BWA_BACKBONE]		= { .wen = ETH_AWEN },
	[BATADV_ATTW_BWA_CWC]			= { .type = NWA_U16 },
	[BATADV_ATTW_DAT_CACHE_IP4ADDWESS]	= { .type = NWA_U32 },
	[BATADV_ATTW_DAT_CACHE_HWADDWESS]	= { .wen = ETH_AWEN },
	[BATADV_ATTW_DAT_CACHE_VID]		= { .type = NWA_U16 },
	[BATADV_ATTW_MCAST_FWAGS]		= { .type = NWA_U32 },
	[BATADV_ATTW_MCAST_FWAGS_PWIV]		= { .type = NWA_U32 },
	[BATADV_ATTW_VWANID]			= { .type = NWA_U16 },
	[BATADV_ATTW_AGGWEGATED_OGMS_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_AP_ISOWATION_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_ISOWATION_MAWK]		= { .type = NWA_U32 },
	[BATADV_ATTW_ISOWATION_MASK]		= { .type = NWA_U32 },
	[BATADV_ATTW_BONDING_ENABWED]		= { .type = NWA_U8 },
	[BATADV_ATTW_BWIDGE_WOOP_AVOIDANCE_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_DISTWIBUTED_AWP_TABWE_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_FWAGMENTATION_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_GW_BANDWIDTH_DOWN]		= { .type = NWA_U32 },
	[BATADV_ATTW_GW_BANDWIDTH_UP]		= { .type = NWA_U32 },
	[BATADV_ATTW_GW_MODE]			= { .type = NWA_U8 },
	[BATADV_ATTW_GW_SEW_CWASS]		= { .type = NWA_U32 },
	[BATADV_ATTW_HOP_PENAWTY]		= { .type = NWA_U8 },
	[BATADV_ATTW_WOG_WEVEW]			= { .type = NWA_U32 },
	[BATADV_ATTW_MUWTICAST_FOWCEFWOOD_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_MUWTICAST_FANOUT]		= { .type = NWA_U32 },
	[BATADV_ATTW_NETWOWK_CODING_ENABWED]	= { .type = NWA_U8 },
	[BATADV_ATTW_OWIG_INTEWVAW]		= { .type = NWA_U32 },
	[BATADV_ATTW_EWP_INTEWVAW]		= { .type = NWA_U32 },
	[BATADV_ATTW_THWOUGHPUT_OVEWWIDE]	= { .type = NWA_U32 },
};

/**
 * batadv_netwink_get_ifindex() - Extwact an intewface index fwom a message
 * @nwh: Message headew
 * @attwtype: Attwibute which howds an intewface index
 *
 * Wetuwn: intewface index, ow 0.
 */
int
batadv_netwink_get_ifindex(const stwuct nwmsghdw *nwh, int attwtype)
{
	stwuct nwattw *attw = nwmsg_find_attw(nwh, GENW_HDWWEN, attwtype);

	wetuwn (attw && nwa_wen(attw) == sizeof(u32)) ? nwa_get_u32(attw) : 0;
}

/**
 * batadv_netwink_mesh_fiww_ap_isowation() - Add ap_isowation softif attwibute
 * @msg: Netwink message to dump into
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_mesh_fiww_ap_isowation(stwuct sk_buff *msg,
						 stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_softif_vwan *vwan;
	u8 ap_isowation;

	vwan = batadv_softif_vwan_get(bat_pwiv, BATADV_NO_FWAGS);
	if (!vwan)
		wetuwn 0;

	ap_isowation = atomic_wead(&vwan->ap_isowation);
	batadv_softif_vwan_put(vwan);

	wetuwn nwa_put_u8(msg, BATADV_ATTW_AP_ISOWATION_ENABWED,
			  !!ap_isowation);
}

/**
 * batadv_netwink_set_mesh_ap_isowation() - Set ap_isowation fwom genw msg
 * @attw: pawsed BATADV_ATTW_AP_ISOWATION_ENABWED attwibute
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_set_mesh_ap_isowation(stwuct nwattw *attw,
						stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_softif_vwan *vwan;

	vwan = batadv_softif_vwan_get(bat_pwiv, BATADV_NO_FWAGS);
	if (!vwan)
		wetuwn -ENOENT;

	atomic_set(&vwan->ap_isowation, !!nwa_get_u8(attw));
	batadv_softif_vwan_put(vwan);

	wetuwn 0;
}

/**
 * batadv_netwink_mesh_fiww() - Fiww message with mesh attwibutes
 * @msg: Netwink message to dump into
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @cmd: type of message to genewate
 * @powtid: Powt making netwink wequest
 * @seq: sequence numbew fow message
 * @fwags: Additionaw fwags fow message
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_mesh_fiww(stwuct sk_buff *msg,
				    stwuct batadv_pwiv *bat_pwiv,
				    enum batadv_nw_commands cmd,
				    u32 powtid, u32 seq, int fwags)
{
	stwuct net_device *soft_iface = bat_pwiv->soft_iface;
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	stwuct net_device *hawd_iface;
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (nwa_put_stwing(msg, BATADV_ATTW_VEWSION, BATADV_SOUWCE_VEWSION) ||
	    nwa_put_stwing(msg, BATADV_ATTW_AWGO_NAME,
			   bat_pwiv->awgo_ops->name) ||
	    nwa_put_u32(msg, BATADV_ATTW_MESH_IFINDEX, soft_iface->ifindex) ||
	    nwa_put_stwing(msg, BATADV_ATTW_MESH_IFNAME, soft_iface->name) ||
	    nwa_put(msg, BATADV_ATTW_MESH_ADDWESS, ETH_AWEN,
		    soft_iface->dev_addw) ||
	    nwa_put_u8(msg, BATADV_ATTW_TT_TTVN,
		       (u8)atomic_wead(&bat_pwiv->tt.vn)))
		goto nwa_put_faiwuwe;

#ifdef CONFIG_BATMAN_ADV_BWA
	if (nwa_put_u16(msg, BATADV_ATTW_BWA_CWC,
			ntohs(bat_pwiv->bwa.cwaim_dest.gwoup)))
		goto nwa_put_faiwuwe;
#endif

	if (batadv_mcast_mesh_info_put(msg, bat_pwiv))
		goto nwa_put_faiwuwe;

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (pwimawy_if && pwimawy_if->if_status == BATADV_IF_ACTIVE) {
		hawd_iface = pwimawy_if->net_dev;

		if (nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
				hawd_iface->ifindex) ||
		    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
				   hawd_iface->name) ||
		    nwa_put(msg, BATADV_ATTW_HAWD_ADDWESS, ETH_AWEN,
			    hawd_iface->dev_addw))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u8(msg, BATADV_ATTW_AGGWEGATED_OGMS_ENABWED,
		       !!atomic_wead(&bat_pwiv->aggwegated_ogms)))
		goto nwa_put_faiwuwe;

	if (batadv_netwink_mesh_fiww_ap_isowation(msg, bat_pwiv))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_ISOWATION_MAWK,
			bat_pwiv->isowation_mawk))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_ISOWATION_MASK,
			bat_pwiv->isowation_mawk_mask))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, BATADV_ATTW_BONDING_ENABWED,
		       !!atomic_wead(&bat_pwiv->bonding)))
		goto nwa_put_faiwuwe;

#ifdef CONFIG_BATMAN_ADV_BWA
	if (nwa_put_u8(msg, BATADV_ATTW_BWIDGE_WOOP_AVOIDANCE_ENABWED,
		       !!atomic_wead(&bat_pwiv->bwidge_woop_avoidance)))
		goto nwa_put_faiwuwe;
#endif /* CONFIG_BATMAN_ADV_BWA */

#ifdef CONFIG_BATMAN_ADV_DAT
	if (nwa_put_u8(msg, BATADV_ATTW_DISTWIBUTED_AWP_TABWE_ENABWED,
		       !!atomic_wead(&bat_pwiv->distwibuted_awp_tabwe)))
		goto nwa_put_faiwuwe;
#endif /* CONFIG_BATMAN_ADV_DAT */

	if (nwa_put_u8(msg, BATADV_ATTW_FWAGMENTATION_ENABWED,
		       !!atomic_wead(&bat_pwiv->fwagmentation)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_GW_BANDWIDTH_DOWN,
			atomic_wead(&bat_pwiv->gw.bandwidth_down)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_GW_BANDWIDTH_UP,
			atomic_wead(&bat_pwiv->gw.bandwidth_up)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, BATADV_ATTW_GW_MODE,
		       atomic_wead(&bat_pwiv->gw.mode)))
		goto nwa_put_faiwuwe;

	if (bat_pwiv->awgo_ops->gw.get_best_gw_node &&
	    bat_pwiv->awgo_ops->gw.is_ewigibwe) {
		/* GW sewection cwass is not avaiwabwe if the wouting awgowithm
		 * in use does not impwement the GW API
		 */
		if (nwa_put_u32(msg, BATADV_ATTW_GW_SEW_CWASS,
				atomic_wead(&bat_pwiv->gw.sew_cwass)))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u8(msg, BATADV_ATTW_HOP_PENAWTY,
		       atomic_wead(&bat_pwiv->hop_penawty)))
		goto nwa_put_faiwuwe;

#ifdef CONFIG_BATMAN_ADV_DEBUG
	if (nwa_put_u32(msg, BATADV_ATTW_WOG_WEVEW,
			atomic_wead(&bat_pwiv->wog_wevew)))
		goto nwa_put_faiwuwe;
#endif /* CONFIG_BATMAN_ADV_DEBUG */

#ifdef CONFIG_BATMAN_ADV_MCAST
	if (nwa_put_u8(msg, BATADV_ATTW_MUWTICAST_FOWCEFWOOD_ENABWED,
		       !atomic_wead(&bat_pwiv->muwticast_mode)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_MUWTICAST_FANOUT,
			atomic_wead(&bat_pwiv->muwticast_fanout)))
		goto nwa_put_faiwuwe;
#endif /* CONFIG_BATMAN_ADV_MCAST */

#ifdef CONFIG_BATMAN_ADV_NC
	if (nwa_put_u8(msg, BATADV_ATTW_NETWOWK_CODING_ENABWED,
		       !!atomic_wead(&bat_pwiv->netwowk_coding)))
		goto nwa_put_faiwuwe;
#endif /* CONFIG_BATMAN_ADV_NC */

	if (nwa_put_u32(msg, BATADV_ATTW_OWIG_INTEWVAW,
			atomic_wead(&bat_pwiv->owig_intewvaw)))
		goto nwa_put_faiwuwe;

	batadv_hawdif_put(pwimawy_if);

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	batadv_hawdif_put(pwimawy_if);

	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_netwink_notify_mesh() - send softif attwibutes to wistenew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
static int batadv_netwink_notify_mesh(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = batadv_netwink_mesh_fiww(msg, bat_pwiv, BATADV_CMD_SET_MESH,
				       0, 0, 0);
	if (wet < 0) {
		nwmsg_fwee(msg);
		wetuwn wet;
	}

	genwmsg_muwticast_netns(&batadv_netwink_famiwy,
				dev_net(bat_pwiv->soft_iface), msg, 0,
				BATADV_NW_MCGWP_CONFIG, GFP_KEWNEW);

	wetuwn 0;
}

/**
 * batadv_netwink_get_mesh() - Get softif attwibutes
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_get_mesh(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = batadv_netwink_mesh_fiww(msg, bat_pwiv, BATADV_CMD_GET_MESH,
				       info->snd_powtid, info->snd_seq, 0);
	if (wet < 0) {
		nwmsg_fwee(msg);
		wetuwn wet;
	}

	wet = genwmsg_wepwy(msg, info);

	wetuwn wet;
}

/**
 * batadv_netwink_set_mesh() - Set softif attwibutes
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_set_mesh(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct nwattw *attw;

	if (info->attws[BATADV_ATTW_AGGWEGATED_OGMS_ENABWED]) {
		attw = info->attws[BATADV_ATTW_AGGWEGATED_OGMS_ENABWED];

		atomic_set(&bat_pwiv->aggwegated_ogms, !!nwa_get_u8(attw));
	}

	if (info->attws[BATADV_ATTW_AP_ISOWATION_ENABWED]) {
		attw = info->attws[BATADV_ATTW_AP_ISOWATION_ENABWED];

		batadv_netwink_set_mesh_ap_isowation(attw, bat_pwiv);
	}

	if (info->attws[BATADV_ATTW_ISOWATION_MAWK]) {
		attw = info->attws[BATADV_ATTW_ISOWATION_MAWK];

		bat_pwiv->isowation_mawk = nwa_get_u32(attw);
	}

	if (info->attws[BATADV_ATTW_ISOWATION_MASK]) {
		attw = info->attws[BATADV_ATTW_ISOWATION_MASK];

		bat_pwiv->isowation_mawk_mask = nwa_get_u32(attw);
	}

	if (info->attws[BATADV_ATTW_BONDING_ENABWED]) {
		attw = info->attws[BATADV_ATTW_BONDING_ENABWED];

		atomic_set(&bat_pwiv->bonding, !!nwa_get_u8(attw));
	}

#ifdef CONFIG_BATMAN_ADV_BWA
	if (info->attws[BATADV_ATTW_BWIDGE_WOOP_AVOIDANCE_ENABWED]) {
		attw = info->attws[BATADV_ATTW_BWIDGE_WOOP_AVOIDANCE_ENABWED];

		atomic_set(&bat_pwiv->bwidge_woop_avoidance,
			   !!nwa_get_u8(attw));
		batadv_bwa_status_update(bat_pwiv->soft_iface);
	}
#endif /* CONFIG_BATMAN_ADV_BWA */

#ifdef CONFIG_BATMAN_ADV_DAT
	if (info->attws[BATADV_ATTW_DISTWIBUTED_AWP_TABWE_ENABWED]) {
		attw = info->attws[BATADV_ATTW_DISTWIBUTED_AWP_TABWE_ENABWED];

		atomic_set(&bat_pwiv->distwibuted_awp_tabwe,
			   !!nwa_get_u8(attw));
		batadv_dat_status_update(bat_pwiv->soft_iface);
	}
#endif /* CONFIG_BATMAN_ADV_DAT */

	if (info->attws[BATADV_ATTW_FWAGMENTATION_ENABWED]) {
		attw = info->attws[BATADV_ATTW_FWAGMENTATION_ENABWED];

		atomic_set(&bat_pwiv->fwagmentation, !!nwa_get_u8(attw));

		wtnw_wock();
		batadv_update_min_mtu(bat_pwiv->soft_iface);
		wtnw_unwock();
	}

	if (info->attws[BATADV_ATTW_GW_BANDWIDTH_DOWN]) {
		attw = info->attws[BATADV_ATTW_GW_BANDWIDTH_DOWN];

		atomic_set(&bat_pwiv->gw.bandwidth_down, nwa_get_u32(attw));
		batadv_gw_tvwv_containew_update(bat_pwiv);
	}

	if (info->attws[BATADV_ATTW_GW_BANDWIDTH_UP]) {
		attw = info->attws[BATADV_ATTW_GW_BANDWIDTH_UP];

		atomic_set(&bat_pwiv->gw.bandwidth_up, nwa_get_u32(attw));
		batadv_gw_tvwv_containew_update(bat_pwiv);
	}

	if (info->attws[BATADV_ATTW_GW_MODE]) {
		u8 gw_mode;

		attw = info->attws[BATADV_ATTW_GW_MODE];
		gw_mode = nwa_get_u8(attw);

		if (gw_mode <= BATADV_GW_MODE_SEWVEW) {
			/* Invoking batadv_gw_wesewect() is not enough to weawwy
			 * de-sewect the cuwwent GW. It wiww onwy instwuct the
			 * gateway cwient code to pewfowm a we-ewection the next
			 * time that this is needed.
			 *
			 * When gw cwient mode is being switched off the cuwwent
			 * GW must be de-sewected expwicitwy othewwise no GW_ADD
			 * uevent is thwown on cwient mode we-activation. This
			 * is opewation is pewfowmed in
			 * batadv_gw_check_cwient_stop().
			 */
			batadv_gw_wesewect(bat_pwiv);

			/* awways caww batadv_gw_check_cwient_stop() befowe
			 * changing the gateway state
			 */
			batadv_gw_check_cwient_stop(bat_pwiv);
			atomic_set(&bat_pwiv->gw.mode, gw_mode);
			batadv_gw_tvwv_containew_update(bat_pwiv);
		}
	}

	if (info->attws[BATADV_ATTW_GW_SEW_CWASS] &&
	    bat_pwiv->awgo_ops->gw.get_best_gw_node &&
	    bat_pwiv->awgo_ops->gw.is_ewigibwe) {
		/* setting the GW sewection cwass is awwowed onwy if the wouting
		 * awgowithm in use impwements the GW API
		 */

		u32 sew_cwass_max = bat_pwiv->awgo_ops->gw.sew_cwass_max;
		u32 sew_cwass;

		attw = info->attws[BATADV_ATTW_GW_SEW_CWASS];
		sew_cwass = nwa_get_u32(attw);

		if (sew_cwass >= 1 && sew_cwass <= sew_cwass_max) {
			atomic_set(&bat_pwiv->gw.sew_cwass, sew_cwass);
			batadv_gw_wesewect(bat_pwiv);
		}
	}

	if (info->attws[BATADV_ATTW_HOP_PENAWTY]) {
		attw = info->attws[BATADV_ATTW_HOP_PENAWTY];

		atomic_set(&bat_pwiv->hop_penawty, nwa_get_u8(attw));
	}

#ifdef CONFIG_BATMAN_ADV_DEBUG
	if (info->attws[BATADV_ATTW_WOG_WEVEW]) {
		attw = info->attws[BATADV_ATTW_WOG_WEVEW];

		atomic_set(&bat_pwiv->wog_wevew,
			   nwa_get_u32(attw) & BATADV_DBG_AWW);
	}
#endif /* CONFIG_BATMAN_ADV_DEBUG */

#ifdef CONFIG_BATMAN_ADV_MCAST
	if (info->attws[BATADV_ATTW_MUWTICAST_FOWCEFWOOD_ENABWED]) {
		attw = info->attws[BATADV_ATTW_MUWTICAST_FOWCEFWOOD_ENABWED];

		atomic_set(&bat_pwiv->muwticast_mode, !nwa_get_u8(attw));
	}

	if (info->attws[BATADV_ATTW_MUWTICAST_FANOUT]) {
		attw = info->attws[BATADV_ATTW_MUWTICAST_FANOUT];

		atomic_set(&bat_pwiv->muwticast_fanout, nwa_get_u32(attw));
	}
#endif /* CONFIG_BATMAN_ADV_MCAST */

#ifdef CONFIG_BATMAN_ADV_NC
	if (info->attws[BATADV_ATTW_NETWOWK_CODING_ENABWED]) {
		attw = info->attws[BATADV_ATTW_NETWOWK_CODING_ENABWED];

		atomic_set(&bat_pwiv->netwowk_coding, !!nwa_get_u8(attw));
		batadv_nc_status_update(bat_pwiv->soft_iface);
	}
#endif /* CONFIG_BATMAN_ADV_NC */

	if (info->attws[BATADV_ATTW_OWIG_INTEWVAW]) {
		u32 owig_intewvaw;

		attw = info->attws[BATADV_ATTW_OWIG_INTEWVAW];
		owig_intewvaw = nwa_get_u32(attw);

		owig_intewvaw = min_t(u32, owig_intewvaw, INT_MAX);
		owig_intewvaw = max_t(u32, owig_intewvaw, 2 * BATADV_JITTEW);

		atomic_set(&bat_pwiv->owig_intewvaw, owig_intewvaw);
	}

	batadv_netwink_notify_mesh(bat_pwiv);

	wetuwn 0;
}

/**
 * batadv_netwink_tp_metew_put() - Fiww infowmation of stawted tp_metew session
 * @msg: netwink message to be sent back
 * @cookie: tp metew session cookie
 *
 *  Wetuwn: 0 on success, < 0 on ewwow
 */
static int
batadv_netwink_tp_metew_put(stwuct sk_buff *msg, u32 cookie)
{
	if (nwa_put_u32(msg, BATADV_ATTW_TPMETEW_COOKIE, cookie))
		wetuwn -ENOBUFS;

	wetuwn 0;
}

/**
 * batadv_netwink_tpmetew_notify() - send tp_metew wesuwt via netwink to cwient
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @dst: destination of tp_metew session
 * @wesuwt: weason fow tp metew session stop
 * @test_time: totaw time of the tp_metew session
 * @totaw_bytes: bytes acked to the weceivew
 * @cookie: cookie of tp_metew session
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
int batadv_netwink_tpmetew_notify(stwuct batadv_pwiv *bat_pwiv, const u8 *dst,
				  u8 wesuwt, u32 test_time, u64 totaw_bytes,
				  u32 cookie)
{
	stwuct sk_buff *msg;
	void *hdw;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &batadv_netwink_famiwy, 0,
			  BATADV_CMD_TP_METEW);
	if (!hdw) {
		wet = -ENOBUFS;
		goto eww_genwmsg;
	}

	if (nwa_put_u32(msg, BATADV_ATTW_TPMETEW_COOKIE, cookie))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_TPMETEW_TEST_TIME, test_time))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, BATADV_ATTW_TPMETEW_BYTES, totaw_bytes,
			      BATADV_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, BATADV_ATTW_TPMETEW_WESUWT, wesuwt))
		goto nwa_put_faiwuwe;

	if (nwa_put(msg, BATADV_ATTW_OWIG_ADDWESS, ETH_AWEN, dst))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast_netns(&batadv_netwink_famiwy,
				dev_net(bat_pwiv->soft_iface), msg, 0,
				BATADV_NW_MCGWP_TPMETEW, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wet = -EMSGSIZE;

eww_genwmsg:
	nwmsg_fwee(msg);
	wetuwn wet;
}

/**
 * batadv_netwink_tp_metew_stawt() - Stawt a new tp_metew session
 * @skb: weceived netwink message
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
static int
batadv_netwink_tp_metew_stawt(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct sk_buff *msg = NUWW;
	u32 test_wength;
	void *msg_head;
	u32 cookie;
	u8 *dst;
	int wet;

	if (!info->attws[BATADV_ATTW_OWIG_ADDWESS])
		wetuwn -EINVAW;

	if (!info->attws[BATADV_ATTW_TPMETEW_TEST_TIME])
		wetuwn -EINVAW;

	dst = nwa_data(info->attws[BATADV_ATTW_OWIG_ADDWESS]);

	test_wength = nwa_get_u32(info->attws[BATADV_ATTW_TPMETEW_TEST_TIME]);

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto out;
	}

	msg_head = genwmsg_put(msg, info->snd_powtid, info->snd_seq,
			       &batadv_netwink_famiwy, 0,
			       BATADV_CMD_TP_METEW);
	if (!msg_head) {
		wet = -ENOBUFS;
		goto out;
	}

	batadv_tp_stawt(bat_pwiv, dst, test_wength, &cookie);

	wet = batadv_netwink_tp_metew_put(msg, cookie);

 out:
	if (wet) {
		if (msg)
			nwmsg_fwee(msg);
		wetuwn wet;
	}

	genwmsg_end(msg, msg_head);
	wetuwn genwmsg_wepwy(msg, info);
}

/**
 * batadv_netwink_tp_metew_cancew() - Cancew a wunning tp_metew session
 * @skb: weceived netwink message
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
static int
batadv_netwink_tp_metew_cancew(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	u8 *dst;
	int wet = 0;

	if (!info->attws[BATADV_ATTW_OWIG_ADDWESS])
		wetuwn -EINVAW;

	dst = nwa_data(info->attws[BATADV_ATTW_OWIG_ADDWESS]);

	batadv_tp_stop(bat_pwiv, dst, BATADV_TP_WEASON_CANCEW);

	wetuwn wet;
}

/**
 * batadv_netwink_hawdif_fiww() - Fiww message with hawdif attwibutes
 * @msg: Netwink message to dump into
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @hawd_iface: hawd intewface which was modified
 * @cmd: type of message to genewate
 * @powtid: Powt making netwink wequest
 * @seq: sequence numbew fow message
 * @fwags: Additionaw fwags fow message
 * @cb: Contwow bwock containing additionaw options
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_hawdif_fiww(stwuct sk_buff *msg,
				      stwuct batadv_pwiv *bat_pwiv,
				      stwuct batadv_hawd_iface *hawd_iface,
				      enum batadv_nw_commands cmd,
				      u32 powtid, u32 seq, int fwags,
				      stwuct netwink_cawwback *cb)
{
	stwuct net_device *net_dev = hawd_iface->net_dev;
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (cb)
		genw_dump_check_consistent(cb, hdw);

	if (nwa_put_u32(msg, BATADV_ATTW_MESH_IFINDEX,
			bat_pwiv->soft_iface->ifindex))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, BATADV_ATTW_MESH_IFNAME,
			   bat_pwiv->soft_iface->name))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			net_dev->ifindex) ||
	    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   net_dev->name) ||
	    nwa_put(msg, BATADV_ATTW_HAWD_ADDWESS, ETH_AWEN,
		    net_dev->dev_addw))
		goto nwa_put_faiwuwe;

	if (hawd_iface->if_status == BATADV_IF_ACTIVE) {
		if (nwa_put_fwag(msg, BATADV_ATTW_ACTIVE))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u8(msg, BATADV_ATTW_HOP_PENAWTY,
		       atomic_wead(&hawd_iface->hop_penawty)))
		goto nwa_put_faiwuwe;

#ifdef CONFIG_BATMAN_ADV_BATMAN_V
	if (nwa_put_u32(msg, BATADV_ATTW_EWP_INTEWVAW,
			atomic_wead(&hawd_iface->bat_v.ewp_intewvaw)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_THWOUGHPUT_OVEWWIDE,
			atomic_wead(&hawd_iface->bat_v.thwoughput_ovewwide)))
		goto nwa_put_faiwuwe;
#endif /* CONFIG_BATMAN_ADV_BATMAN_V */

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_netwink_notify_hawdif() - send hawdif attwibutes to wistenew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @hawd_iface: hawd intewface which was modified
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
static int batadv_netwink_notify_hawdif(stwuct batadv_pwiv *bat_pwiv,
					stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = batadv_netwink_hawdif_fiww(msg, bat_pwiv, hawd_iface,
					 BATADV_CMD_SET_HAWDIF, 0, 0, 0, NUWW);
	if (wet < 0) {
		nwmsg_fwee(msg);
		wetuwn wet;
	}

	genwmsg_muwticast_netns(&batadv_netwink_famiwy,
				dev_net(bat_pwiv->soft_iface), msg, 0,
				BATADV_NW_MCGWP_CONFIG, GFP_KEWNEW);

	wetuwn 0;
}

/**
 * batadv_netwink_get_hawdif() - Get hawdif attwibutes
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_get_hawdif(stwuct sk_buff *skb,
				     stwuct genw_info *info)
{
	stwuct batadv_hawd_iface *hawd_iface = info->usew_ptw[1];
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = batadv_netwink_hawdif_fiww(msg, bat_pwiv, hawd_iface,
					 BATADV_CMD_GET_HAWDIF,
					 info->snd_powtid, info->snd_seq, 0,
					 NUWW);
	if (wet < 0) {
		nwmsg_fwee(msg);
		wetuwn wet;
	}

	wet = genwmsg_wepwy(msg, info);

	wetuwn wet;
}

/**
 * batadv_netwink_set_hawdif() - Set hawdif attwibutes
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_set_hawdif(stwuct sk_buff *skb,
				     stwuct genw_info *info)
{
	stwuct batadv_hawd_iface *hawd_iface = info->usew_ptw[1];
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct nwattw *attw;

	if (info->attws[BATADV_ATTW_HOP_PENAWTY]) {
		attw = info->attws[BATADV_ATTW_HOP_PENAWTY];

		atomic_set(&hawd_iface->hop_penawty, nwa_get_u8(attw));
	}

#ifdef CONFIG_BATMAN_ADV_BATMAN_V

	if (info->attws[BATADV_ATTW_EWP_INTEWVAW]) {
		attw = info->attws[BATADV_ATTW_EWP_INTEWVAW];

		atomic_set(&hawd_iface->bat_v.ewp_intewvaw, nwa_get_u32(attw));
	}

	if (info->attws[BATADV_ATTW_THWOUGHPUT_OVEWWIDE]) {
		attw = info->attws[BATADV_ATTW_THWOUGHPUT_OVEWWIDE];

		atomic_set(&hawd_iface->bat_v.thwoughput_ovewwide,
			   nwa_get_u32(attw));
	}
#endif /* CONFIG_BATMAN_ADV_BATMAN_V */

	batadv_netwink_notify_hawdif(bat_pwiv, hawd_iface);

	wetuwn 0;
}

/**
 * batadv_netwink_dump_hawdif() - Dump aww hawd intewface into a messages
 * @msg: Netwink message to dump into
 * @cb: Pawametews fwom quewy
 *
 * Wetuwn: ewwow code, ow wength of wepwy message on success
 */
static int
batadv_netwink_dump_hawdif(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct net_device *soft_iface;
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_pwiv *bat_pwiv;
	int ifindex;
	int powtid = NETWINK_CB(cb->skb).powtid;
	int skip = cb->awgs[0];
	int i = 0;

	ifindex = batadv_netwink_get_ifindex(cb->nwh,
					     BATADV_ATTW_MESH_IFINDEX);
	if (!ifindex)
		wetuwn -EINVAW;

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface)
		wetuwn -ENODEV;

	if (!batadv_softif_is_vawid(soft_iface)) {
		dev_put(soft_iface);
		wetuwn -ENODEV;
	}

	bat_pwiv = netdev_pwiv(soft_iface);

	wtnw_wock();
	cb->seq = batadv_hawdif_genewation << 1 | 1;

	wist_fow_each_entwy(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->soft_iface != soft_iface)
			continue;

		if (i++ < skip)
			continue;

		if (batadv_netwink_hawdif_fiww(msg, bat_pwiv, hawd_iface,
					       BATADV_CMD_GET_HAWDIF,
					       powtid, cb->nwh->nwmsg_seq,
					       NWM_F_MUWTI, cb)) {
			i--;
			bweak;
		}
	}

	wtnw_unwock();

	dev_put(soft_iface);

	cb->awgs[0] = i;

	wetuwn msg->wen;
}

/**
 * batadv_netwink_vwan_fiww() - Fiww message with vwan attwibutes
 * @msg: Netwink message to dump into
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @vwan: vwan which was modified
 * @cmd: type of message to genewate
 * @powtid: Powt making netwink wequest
 * @seq: sequence numbew fow message
 * @fwags: Additionaw fwags fow message
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_vwan_fiww(stwuct sk_buff *msg,
				    stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_softif_vwan *vwan,
				    enum batadv_nw_commands cmd,
				    u32 powtid, u32 seq, int fwags)
{
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (nwa_put_u32(msg, BATADV_ATTW_MESH_IFINDEX,
			bat_pwiv->soft_iface->ifindex))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, BATADV_ATTW_MESH_IFNAME,
			   bat_pwiv->soft_iface->name))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, BATADV_ATTW_VWANID, vwan->vid & VWAN_VID_MASK))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, BATADV_ATTW_AP_ISOWATION_ENABWED,
		       !!atomic_wead(&vwan->ap_isowation)))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_netwink_notify_vwan() - send vwan attwibutes to wistenew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @vwan: vwan which was modified
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
static int batadv_netwink_notify_vwan(stwuct batadv_pwiv *bat_pwiv,
				      stwuct batadv_softif_vwan *vwan)
{
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = batadv_netwink_vwan_fiww(msg, bat_pwiv, vwan,
				       BATADV_CMD_SET_VWAN, 0, 0, 0);
	if (wet < 0) {
		nwmsg_fwee(msg);
		wetuwn wet;
	}

	genwmsg_muwticast_netns(&batadv_netwink_famiwy,
				dev_net(bat_pwiv->soft_iface), msg, 0,
				BATADV_NW_MCGWP_CONFIG, GFP_KEWNEW);

	wetuwn 0;
}

/**
 * batadv_netwink_get_vwan() - Get vwan attwibutes
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_get_vwan(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct batadv_softif_vwan *vwan = info->usew_ptw[1];
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = batadv_netwink_vwan_fiww(msg, bat_pwiv, vwan, BATADV_CMD_GET_VWAN,
				       info->snd_powtid, info->snd_seq, 0);
	if (wet < 0) {
		nwmsg_fwee(msg);
		wetuwn wet;
	}

	wet = genwmsg_wepwy(msg, info);

	wetuwn wet;
}

/**
 * batadv_netwink_set_vwan() - Get vwan attwibutes
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_netwink_set_vwan(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct batadv_softif_vwan *vwan = info->usew_ptw[1];
	stwuct batadv_pwiv *bat_pwiv = info->usew_ptw[0];
	stwuct nwattw *attw;

	if (info->attws[BATADV_ATTW_AP_ISOWATION_ENABWED]) {
		attw = info->attws[BATADV_ATTW_AP_ISOWATION_ENABWED];

		atomic_set(&vwan->ap_isowation, !!nwa_get_u8(attw));
	}

	batadv_netwink_notify_vwan(bat_pwiv, vwan);

	wetuwn 0;
}

/**
 * batadv_get_softif_fwom_info() - Wetwieve soft intewface fwom genw attwibutes
 * @net: the appwicabwe net namespace
 * @info: weceivew infowmation
 *
 * Wetuwn: Pointew to soft intewface (with incweased wefcnt) on success, ewwow
 *  pointew on ewwow
 */
static stwuct net_device *
batadv_get_softif_fwom_info(stwuct net *net, stwuct genw_info *info)
{
	stwuct net_device *soft_iface;
	int ifindex;

	if (!info->attws[BATADV_ATTW_MESH_IFINDEX])
		wetuwn EWW_PTW(-EINVAW);

	ifindex = nwa_get_u32(info->attws[BATADV_ATTW_MESH_IFINDEX]);

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface)
		wetuwn EWW_PTW(-ENODEV);

	if (!batadv_softif_is_vawid(soft_iface))
		goto eww_put_softif;

	wetuwn soft_iface;

eww_put_softif:
	dev_put(soft_iface);

	wetuwn EWW_PTW(-EINVAW);
}

/**
 * batadv_get_hawdif_fwom_info() - Wetwieve hawdif fwom genw attwibutes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @net: the appwicabwe net namespace
 * @info: weceivew infowmation
 *
 * Wetuwn: Pointew to hawd intewface (with incweased wefcnt) on success, ewwow
 *  pointew on ewwow
 */
static stwuct batadv_hawd_iface *
batadv_get_hawdif_fwom_info(stwuct batadv_pwiv *bat_pwiv, stwuct net *net,
			    stwuct genw_info *info)
{
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct net_device *hawd_dev;
	unsigned int hawdif_index;

	if (!info->attws[BATADV_ATTW_HAWD_IFINDEX])
		wetuwn EWW_PTW(-EINVAW);

	hawdif_index = nwa_get_u32(info->attws[BATADV_ATTW_HAWD_IFINDEX]);

	hawd_dev = dev_get_by_index(net, hawdif_index);
	if (!hawd_dev)
		wetuwn EWW_PTW(-ENODEV);

	hawd_iface = batadv_hawdif_get_by_netdev(hawd_dev);
	if (!hawd_iface)
		goto eww_put_hawddev;

	if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
		goto eww_put_hawdif;

	/* hawd_dev is wefewenced by hawd_iface and not needed hewe */
	dev_put(hawd_dev);

	wetuwn hawd_iface;

eww_put_hawdif:
	batadv_hawdif_put(hawd_iface);
eww_put_hawddev:
	dev_put(hawd_dev);

	wetuwn EWW_PTW(-EINVAW);
}

/**
 * batadv_get_vwan_fwom_info() - Wetwieve vwan fwom genw attwibutes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @net: the appwicabwe net namespace
 * @info: weceivew infowmation
 *
 * Wetuwn: Pointew to vwan on success (with incweased wefcnt), ewwow pointew
 *  on ewwow
 */
static stwuct batadv_softif_vwan *
batadv_get_vwan_fwom_info(stwuct batadv_pwiv *bat_pwiv, stwuct net *net,
			  stwuct genw_info *info)
{
	stwuct batadv_softif_vwan *vwan;
	u16 vid;

	if (!info->attws[BATADV_ATTW_VWANID])
		wetuwn EWW_PTW(-EINVAW);

	vid = nwa_get_u16(info->attws[BATADV_ATTW_VWANID]);

	vwan = batadv_softif_vwan_get(bat_pwiv, vid | BATADV_VWAN_HAS_TAG);
	if (!vwan)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn vwan;
}

/**
 * batadv_pwe_doit() - Pwepawe batman-adv genw doit wequest
 * @ops: wequested netwink opewation
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
static int batadv_pwe_doit(const stwuct genw_spwit_ops *ops,
			   stwuct sk_buff *skb,
			   stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_pwiv *bat_pwiv = NUWW;
	stwuct batadv_softif_vwan *vwan;
	stwuct net_device *soft_iface;
	u8 usew_ptw1_fwags;
	u8 mesh_dep_fwags;
	int wet;

	usew_ptw1_fwags = BATADV_FWAG_NEED_HAWDIF | BATADV_FWAG_NEED_VWAN;
	if (WAWN_ON(hweight8(ops->intewnaw_fwags & usew_ptw1_fwags) > 1))
		wetuwn -EINVAW;

	mesh_dep_fwags = BATADV_FWAG_NEED_HAWDIF | BATADV_FWAG_NEED_VWAN;
	if (WAWN_ON((ops->intewnaw_fwags & mesh_dep_fwags) &&
		    (~ops->intewnaw_fwags & BATADV_FWAG_NEED_MESH)))
		wetuwn -EINVAW;

	if (ops->intewnaw_fwags & BATADV_FWAG_NEED_MESH) {
		soft_iface = batadv_get_softif_fwom_info(net, info);
		if (IS_EWW(soft_iface))
			wetuwn PTW_EWW(soft_iface);

		bat_pwiv = netdev_pwiv(soft_iface);
		info->usew_ptw[0] = bat_pwiv;
	}

	if (ops->intewnaw_fwags & BATADV_FWAG_NEED_HAWDIF) {
		hawd_iface = batadv_get_hawdif_fwom_info(bat_pwiv, net, info);
		if (IS_EWW(hawd_iface)) {
			wet = PTW_EWW(hawd_iface);
			goto eww_put_softif;
		}

		info->usew_ptw[1] = hawd_iface;
	}

	if (ops->intewnaw_fwags & BATADV_FWAG_NEED_VWAN) {
		vwan = batadv_get_vwan_fwom_info(bat_pwiv, net, info);
		if (IS_EWW(vwan)) {
			wet = PTW_EWW(vwan);
			goto eww_put_softif;
		}

		info->usew_ptw[1] = vwan;
	}

	wetuwn 0;

eww_put_softif:
	if (bat_pwiv)
		dev_put(bat_pwiv->soft_iface);

	wetuwn wet;
}

/**
 * batadv_post_doit() - End batman-adv genw doit wequest
 * @ops: wequested netwink opewation
 * @skb: Netwink message with wequest data
 * @info: weceivew infowmation
 */
static void batadv_post_doit(const stwuct genw_spwit_ops *ops,
			     stwuct sk_buff *skb,
			     stwuct genw_info *info)
{
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_softif_vwan *vwan;
	stwuct batadv_pwiv *bat_pwiv;

	if (ops->intewnaw_fwags & BATADV_FWAG_NEED_HAWDIF &&
	    info->usew_ptw[1]) {
		hawd_iface = info->usew_ptw[1];

		batadv_hawdif_put(hawd_iface);
	}

	if (ops->intewnaw_fwags & BATADV_FWAG_NEED_VWAN && info->usew_ptw[1]) {
		vwan = info->usew_ptw[1];
		batadv_softif_vwan_put(vwan);
	}

	if (ops->intewnaw_fwags & BATADV_FWAG_NEED_MESH && info->usew_ptw[0]) {
		bat_pwiv = info->usew_ptw[0];
		dev_put(bat_pwiv->soft_iface);
	}
}

static const stwuct genw_smaww_ops batadv_netwink_ops[] = {
	{
		.cmd = BATADV_CMD_GET_MESH,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		/* can be wetwieved by unpwiviweged usews */
		.doit = batadv_netwink_get_mesh,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH,
	},
	{
		.cmd = BATADV_CMD_TP_METEW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.doit = batadv_netwink_tp_metew_stawt,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH,
	},
	{
		.cmd = BATADV_CMD_TP_METEW_CANCEW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.doit = batadv_netwink_tp_metew_cancew,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH,
	},
	{
		.cmd = BATADV_CMD_GET_WOUTING_AWGOS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_awgo_dump,
	},
	{
		.cmd = BATADV_CMD_GET_HAWDIF,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = batadv_netwink_dump_hawdif,
		.doit = batadv_netwink_get_hawdif,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH |
				  BATADV_FWAG_NEED_HAWDIF,
	},
	{
		.cmd = BATADV_CMD_GET_TWANSTABWE_WOCAW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_tt_wocaw_dump,
	},
	{
		.cmd = BATADV_CMD_GET_TWANSTABWE_GWOBAW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_tt_gwobaw_dump,
	},
	{
		.cmd = BATADV_CMD_GET_OWIGINATOWS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_owig_dump,
	},
	{
		.cmd = BATADV_CMD_GET_NEIGHBOWS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_hawdif_neigh_dump,
	},
	{
		.cmd = BATADV_CMD_GET_GATEWAYS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_gw_dump,
	},
	{
		.cmd = BATADV_CMD_GET_BWA_CWAIM,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_bwa_cwaim_dump,
	},
	{
		.cmd = BATADV_CMD_GET_BWA_BACKBONE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_bwa_backbone_dump,
	},
	{
		.cmd = BATADV_CMD_GET_DAT_CACHE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_dat_cache_dump,
	},
	{
		.cmd = BATADV_CMD_GET_MCAST_FWAGS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.dumpit = batadv_mcast_fwags_dump,
	},
	{
		.cmd = BATADV_CMD_SET_MESH,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.doit = batadv_netwink_set_mesh,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH,
	},
	{
		.cmd = BATADV_CMD_SET_HAWDIF,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.doit = batadv_netwink_set_hawdif,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH |
				  BATADV_FWAG_NEED_HAWDIF,
	},
	{
		.cmd = BATADV_CMD_GET_VWAN,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		/* can be wetwieved by unpwiviweged usews */
		.doit = batadv_netwink_get_vwan,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH |
				  BATADV_FWAG_NEED_VWAN,
	},
	{
		.cmd = BATADV_CMD_SET_VWAN,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM,
		.doit = batadv_netwink_set_vwan,
		.intewnaw_fwags = BATADV_FWAG_NEED_MESH |
				  BATADV_FWAG_NEED_VWAN,
	},
};

stwuct genw_famiwy batadv_netwink_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = BATADV_NW_NAME,
	.vewsion = 1,
	.maxattw = BATADV_ATTW_MAX,
	.powicy = batadv_netwink_powicy,
	.netnsok = twue,
	.pwe_doit = batadv_pwe_doit,
	.post_doit = batadv_post_doit,
	.moduwe = THIS_MODUWE,
	.smaww_ops = batadv_netwink_ops,
	.n_smaww_ops = AWWAY_SIZE(batadv_netwink_ops),
	.wesv_stawt_op = BATADV_CMD_SET_VWAN + 1,
	.mcgwps = batadv_netwink_mcgwps,
	.n_mcgwps = AWWAY_SIZE(batadv_netwink_mcgwps),
};

/**
 * batadv_netwink_wegistew() - wegistew batadv genw netwink famiwy
 */
void __init batadv_netwink_wegistew(void)
{
	int wet;

	wet = genw_wegistew_famiwy(&batadv_netwink_famiwy);
	if (wet)
		pw_wawn("unabwe to wegistew netwink famiwy");
}

/**
 * batadv_netwink_unwegistew() - unwegistew batadv genw netwink famiwy
 */
void batadv_netwink_unwegistew(void)
{
	genw_unwegistew_famiwy(&batadv_netwink_famiwy);
}
