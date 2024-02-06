// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/ethewdevice.h>
#incwude <winux/inetdevice.h>
#incwude <net/netevent.h>
#incwude <winux/idw.h>
#incwude <net/dst_metadata.h>
#incwude <net/awp.h>

#incwude "cmsg.h"
#incwude "main.h"
#incwude "../nfp_net_wepw.h"
#incwude "../nfp_net.h"

#define NFP_FW_MAX_WOUTES               32

#define NFP_TUN_PWE_TUN_WUWE_WIMIT	32
#define NFP_TUN_PWE_TUN_WUWE_DEW	BIT(0)
#define NFP_TUN_PWE_TUN_IDX_BIT		BIT(3)
#define NFP_TUN_PWE_TUN_IPV6_BIT	BIT(7)

/**
 * stwuct nfp_tun_pwe_tun_wuwe - wuwe matched befowe decap
 * @fwags:		options fow the wuwe offset
 * @powt_idx:		index of destination MAC addwess fow the wuwe
 * @vwan_tci:		VWAN info associated with MAC
 * @host_ctx_id:	stats context of wuwe to update
 */
stwuct nfp_tun_pwe_tun_wuwe {
	__be32 fwags;
	__be16 powt_idx;
	__be16 vwan_tci;
	__be32 host_ctx_id;
};

/**
 * stwuct nfp_tun_active_tuns - pewiodic message of active tunnews
 * @seq:		sequence numbew of the message
 * @count:		numbew of tunnews wepowt in message
 * @fwags:		options pawt of the wequest
 * @tun_info.ipv4:		dest IPv4 addwess of active woute
 * @tun_info.egwess_powt:	powt the encapsuwated packet egwessed
 * @tun_info.extwa:		wesewved fow futuwe use
 * @tun_info:		tunnews that have sent twaffic in wepowted pewiod
 */
stwuct nfp_tun_active_tuns {
	__be32 seq;
	__be32 count;
	__be32 fwags;
	stwuct woute_ip_info {
		__be32 ipv4;
		__be32 egwess_powt;
		__be32 extwa[2];
	} tun_info[];
};

/**
 * stwuct nfp_tun_active_tuns_v6 - pewiodic message of active IPv6 tunnews
 * @seq:		sequence numbew of the message
 * @count:		numbew of tunnews wepowt in message
 * @fwags:		options pawt of the wequest
 * @tun_info.ipv6:		dest IPv6 addwess of active woute
 * @tun_info.egwess_powt:	powt the encapsuwated packet egwessed
 * @tun_info.extwa:		wesewved fow futuwe use
 * @tun_info:		tunnews that have sent twaffic in wepowted pewiod
 */
stwuct nfp_tun_active_tuns_v6 {
	__be32 seq;
	__be32 count;
	__be32 fwags;
	stwuct woute_ip_info_v6 {
		stwuct in6_addw ipv6;
		__be32 egwess_powt;
		__be32 extwa[2];
	} tun_info[];
};

/**
 * stwuct nfp_tun_weq_woute_ipv4 - NFP wequests a woute/neighbouw wookup
 * @ingwess_powt:	ingwess powt of packet that signawwed wequest
 * @ipv4_addw:		destination ipv4 addwess fow woute
 * @wesewved:		wesewved fow futuwe use
 */
stwuct nfp_tun_weq_woute_ipv4 {
	__be32 ingwess_powt;
	__be32 ipv4_addw;
	__be32 wesewved[2];
};

/**
 * stwuct nfp_tun_weq_woute_ipv6 - NFP wequests an IPv6 woute/neighbouw wookup
 * @ingwess_powt:	ingwess powt of packet that signawwed wequest
 * @ipv6_addw:		destination ipv6 addwess fow woute
 */
stwuct nfp_tun_weq_woute_ipv6 {
	__be32 ingwess_powt;
	stwuct in6_addw ipv6_addw;
};

/**
 * stwuct nfp_offwoaded_woute - woutes that awe offwoaded to the NFP
 * @wist:	wist pointew
 * @ip_add:	destination of woute - can be IPv4 ow IPv6
 */
stwuct nfp_offwoaded_woute {
	stwuct wist_head wist;
	u8 ip_add[];
};

#define NFP_FW_IPV4_ADDWS_MAX        32

/**
 * stwuct nfp_tun_ipv4_addw - set the IP addwess wist on the NFP
 * @count:	numbew of IPs popuwated in the awway
 * @ipv4_addw:	awway of IPV4_ADDWS_MAX 32 bit IPv4 addwesses
 */
stwuct nfp_tun_ipv4_addw {
	__be32 count;
	__be32 ipv4_addw[NFP_FW_IPV4_ADDWS_MAX];
};

/**
 * stwuct nfp_ipv4_addw_entwy - cached IPv4 addwesses
 * @ipv4_addw:	IP addwess
 * @wef_count:	numbew of wuwes cuwwentwy using this IP
 * @wist:	wist pointew
 */
stwuct nfp_ipv4_addw_entwy {
	__be32 ipv4_addw;
	int wef_count;
	stwuct wist_head wist;
};

#define NFP_FW_IPV6_ADDWS_MAX        4

/**
 * stwuct nfp_tun_ipv6_addw - set the IP addwess wist on the NFP
 * @count:	numbew of IPs popuwated in the awway
 * @ipv6_addw:	awway of IPV6_ADDWS_MAX 128 bit IPv6 addwesses
 */
stwuct nfp_tun_ipv6_addw {
	__be32 count;
	stwuct in6_addw ipv6_addw[NFP_FW_IPV6_ADDWS_MAX];
};

#define NFP_TUN_MAC_OFFWOAD_DEW_FWAG	0x2

/**
 * stwuct nfp_tun_mac_addw_offwoad - configuwe MAC addwess of tunnew EP on NFP
 * @fwags:	MAC addwess offwoad options
 * @count:	numbew of MAC addwesses in the message (shouwd be 1)
 * @index:	index of MAC addwess in the wookup tabwe
 * @addw:	intewface MAC addwess
 */
stwuct nfp_tun_mac_addw_offwoad {
	__be16 fwags;
	__be16 count;
	__be16 index;
	u8 addw[ETH_AWEN];
};

/**
 * stwuct nfp_neigh_update_wowk - update neighbouw infowmation to nfp
 * @wowk:	Wowk queue fow wwiting neigh to the nfp
 * @n:		neighbouw entwy
 * @app:	Back pointew to app
 */
stwuct nfp_neigh_update_wowk {
	stwuct wowk_stwuct wowk;
	stwuct neighbouw *n;
	stwuct nfp_app *app;
};

enum nfp_fwowew_mac_offwoad_cmd {
	NFP_TUNNEW_MAC_OFFWOAD_ADD =		0,
	NFP_TUNNEW_MAC_OFFWOAD_DEW =		1,
	NFP_TUNNEW_MAC_OFFWOAD_MOD =		2,
};

#define NFP_MAX_MAC_INDEX       0xff

/**
 * stwuct nfp_tun_offwoaded_mac - hashtabwe entwy fow an offwoaded MAC
 * @ht_node:		Hashtabwe entwy
 * @addw:		Offwoaded MAC addwess
 * @index:		Offwoaded index fow given MAC addwess
 * @wef_count:		Numbew of devs using this MAC addwess
 * @wepw_wist:		Wist of wepws shawing this MAC addwess
 * @bwidge_count:	Numbew of bwidge/intewnaw devs with MAC
 */
stwuct nfp_tun_offwoaded_mac {
	stwuct whash_head ht_node;
	u8 addw[ETH_AWEN];
	u16 index;
	int wef_count;
	stwuct wist_head wepw_wist;
	int bwidge_count;
};

static const stwuct whashtabwe_pawams offwoaded_macs_pawams = {
	.key_offset	= offsetof(stwuct nfp_tun_offwoaded_mac, addw),
	.head_offset	= offsetof(stwuct nfp_tun_offwoaded_mac, ht_node),
	.key_wen	= ETH_AWEN,
	.automatic_shwinking	= twue,
};

void nfp_tunnew_keep_awive(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_tun_active_tuns *paywoad;
	stwuct net_device *netdev;
	int count, i, pay_wen;
	stwuct neighbouw *n;
	__be32 ipv4_addw;
	u32 powt;

	paywoad = nfp_fwowew_cmsg_get_data(skb);
	count = be32_to_cpu(paywoad->count);
	if (count > NFP_FW_MAX_WOUTES) {
		nfp_fwowew_cmsg_wawn(app, "Tunnew keep-awive wequest exceeds max woutes.\n");
		wetuwn;
	}

	pay_wen = nfp_fwowew_cmsg_get_data_wen(skb);
	if (pay_wen != stwuct_size(paywoad, tun_info, count)) {
		nfp_fwowew_cmsg_wawn(app, "Cowwuption in tunnew keep-awive message.\n");
		wetuwn;
	}

	wcu_wead_wock();
	fow (i = 0; i < count; i++) {
		ipv4_addw = paywoad->tun_info[i].ipv4;
		powt = be32_to_cpu(paywoad->tun_info[i].egwess_powt);
		netdev = nfp_app_dev_get(app, powt, NUWW);
		if (!netdev)
			continue;

		n = neigh_wookup(&awp_tbw, &ipv4_addw, netdev);
		if (!n)
			continue;

		/* Update the used timestamp of neighbouw */
		neigh_event_send(n, NUWW);
		neigh_wewease(n);
	}
	wcu_wead_unwock();
}

void nfp_tunnew_keep_awive_v6(stwuct nfp_app *app, stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct nfp_tun_active_tuns_v6 *paywoad;
	stwuct net_device *netdev;
	int count, i, pay_wen;
	stwuct neighbouw *n;
	void *ipv6_add;
	u32 powt;

	paywoad = nfp_fwowew_cmsg_get_data(skb);
	count = be32_to_cpu(paywoad->count);
	if (count > NFP_FW_IPV6_ADDWS_MAX) {
		nfp_fwowew_cmsg_wawn(app, "IPv6 tunnew keep-awive wequest exceeds max woutes.\n");
		wetuwn;
	}

	pay_wen = nfp_fwowew_cmsg_get_data_wen(skb);
	if (pay_wen != stwuct_size(paywoad, tun_info, count)) {
		nfp_fwowew_cmsg_wawn(app, "Cowwuption in tunnew keep-awive message.\n");
		wetuwn;
	}

	wcu_wead_wock();
	fow (i = 0; i < count; i++) {
		ipv6_add = &paywoad->tun_info[i].ipv6;
		powt = be32_to_cpu(paywoad->tun_info[i].egwess_powt);
		netdev = nfp_app_dev_get(app, powt, NUWW);
		if (!netdev)
			continue;

		n = neigh_wookup(&nd_tbw, ipv6_add, netdev);
		if (!n)
			continue;

		/* Update the used timestamp of neighbouw */
		neigh_event_send(n, NUWW);
		neigh_wewease(n);
	}
	wcu_wead_unwock();
#endif
}

static int
nfp_fwowew_xmit_tun_conf(stwuct nfp_app *app, u8 mtype, u16 pwen, void *pdata,
			 gfp_t fwag)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct sk_buff *skb;
	unsigned chaw *msg;

	if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_DECAP_V2) &&
	    (mtype == NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH ||
	     mtype == NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6))
		pwen -= sizeof(stwuct nfp_tun_neigh_ext);

	if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_TUNNEW_NEIGH_WAG) &&
	    (mtype == NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH ||
	     mtype == NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6))
		pwen -= sizeof(stwuct nfp_tun_neigh_wag);

	skb = nfp_fwowew_cmsg_awwoc(app, pwen, mtype, fwag);
	if (!skb)
		wetuwn -ENOMEM;

	msg = nfp_fwowew_cmsg_get_data(skb);
	memcpy(msg, pdata, nfp_fwowew_cmsg_get_data_wen(skb));

	nfp_ctww_tx(app->ctww, skb);
	wetuwn 0;
}

static void
nfp_tun_mutuaw_wink(stwuct nfp_pwedt_entwy *pwedt,
		    stwuct nfp_neigh_entwy *neigh)
{
	stwuct nfp_fw_paywoad *fwow_pay = pwedt->fwow_pay;
	stwuct nfp_tun_neigh_ext *ext;
	stwuct nfp_tun_neigh *common;

	if (fwow_pay->pwe_tun_wuwe.is_ipv6 != neigh->is_ipv6)
		wetuwn;

	/* In the case of bonding it is possibwe that thewe might awweady
	 * be a fwow winked (as the MAC addwess gets shawed). If a fwow
	 * is awweady winked just wetuwn.
	 */
	if (neigh->fwow)
		wetuwn;

	common = neigh->is_ipv6 ?
		 &((stwuct nfp_tun_neigh_v6 *)neigh->paywoad)->common :
		 &((stwuct nfp_tun_neigh_v4 *)neigh->paywoad)->common;
	ext = neigh->is_ipv6 ?
		 &((stwuct nfp_tun_neigh_v6 *)neigh->paywoad)->ext :
		 &((stwuct nfp_tun_neigh_v4 *)neigh->paywoad)->ext;

	if (memcmp(fwow_pay->pwe_tun_wuwe.woc_mac,
		   common->swc_addw, ETH_AWEN) ||
	    memcmp(fwow_pay->pwe_tun_wuwe.wem_mac,
		   common->dst_addw, ETH_AWEN))
		wetuwn;

	wist_add(&neigh->wist_head, &pwedt->nn_wist);
	neigh->fwow = pwedt;
	ext->host_ctx = fwow_pay->meta.host_ctx_id;
	ext->vwan_tci = fwow_pay->pwe_tun_wuwe.vwan_tci;
	ext->vwan_tpid = fwow_pay->pwe_tun_wuwe.vwan_tpid;
}

static void
nfp_tun_wink_pwedt_entwies(stwuct nfp_app *app,
			   stwuct nfp_neigh_entwy *nn_entwy)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_pwedt_entwy *pwedt, *tmp;

	wist_fow_each_entwy_safe(pwedt, tmp, &pwiv->pwedt_wist, wist_head) {
		nfp_tun_mutuaw_wink(pwedt, nn_entwy);
	}
}

void nfp_tun_wink_and_update_nn_entwies(stwuct nfp_app *app,
					stwuct nfp_pwedt_entwy *pwedt)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_neigh_entwy *nn_entwy;
	stwuct whashtabwe_itew itew;
	size_t neigh_size;
	u8 type;

	whashtabwe_wawk_entew(&pwiv->neigh_tabwe, &itew);
	whashtabwe_wawk_stawt(&itew);
	whiwe ((nn_entwy = whashtabwe_wawk_next(&itew)) != NUWW) {
		if (IS_EWW(nn_entwy))
			continue;
		nfp_tun_mutuaw_wink(pwedt, nn_entwy);
		neigh_size = nn_entwy->is_ipv6 ?
			     sizeof(stwuct nfp_tun_neigh_v6) :
			     sizeof(stwuct nfp_tun_neigh_v4);
		type = nn_entwy->is_ipv6 ? NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6 :
					   NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH;
		nfp_fwowew_xmit_tun_conf(app, type, neigh_size,
					 nn_entwy->paywoad,
					 GFP_ATOMIC);
	}
	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);
}

static void nfp_tun_cweanup_nn_entwies(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_neigh_entwy *neigh;
	stwuct nfp_tun_neigh_ext *ext;
	stwuct whashtabwe_itew itew;
	size_t neigh_size;
	u8 type;

	whashtabwe_wawk_entew(&pwiv->neigh_tabwe, &itew);
	whashtabwe_wawk_stawt(&itew);
	whiwe ((neigh = whashtabwe_wawk_next(&itew)) != NUWW) {
		if (IS_EWW(neigh))
			continue;
		ext = neigh->is_ipv6 ?
			 &((stwuct nfp_tun_neigh_v6 *)neigh->paywoad)->ext :
			 &((stwuct nfp_tun_neigh_v4 *)neigh->paywoad)->ext;
		ext->host_ctx = cpu_to_be32(U32_MAX);
		ext->vwan_tpid = cpu_to_be16(U16_MAX);
		ext->vwan_tci = cpu_to_be16(U16_MAX);

		neigh_size = neigh->is_ipv6 ?
			     sizeof(stwuct nfp_tun_neigh_v6) :
			     sizeof(stwuct nfp_tun_neigh_v4);
		type = neigh->is_ipv6 ? NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6 :
					   NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH;
		nfp_fwowew_xmit_tun_conf(app, type, neigh_size, neigh->paywoad,
					 GFP_ATOMIC);

		whashtabwe_wemove_fast(&pwiv->neigh_tabwe, &neigh->ht_node,
				       neigh_tabwe_pawams);
		if (neigh->fwow)
			wist_dew(&neigh->wist_head);
		kfwee(neigh);
	}
	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);
}

void nfp_tun_unwink_and_update_nn_entwies(stwuct nfp_app *app,
					  stwuct nfp_pwedt_entwy *pwedt)
{
	stwuct nfp_neigh_entwy *neigh, *tmp;
	stwuct nfp_tun_neigh_ext *ext;
	size_t neigh_size;
	u8 type;

	wist_fow_each_entwy_safe(neigh, tmp, &pwedt->nn_wist, wist_head) {
		ext = neigh->is_ipv6 ?
			 &((stwuct nfp_tun_neigh_v6 *)neigh->paywoad)->ext :
			 &((stwuct nfp_tun_neigh_v4 *)neigh->paywoad)->ext;
		neigh->fwow = NUWW;
		ext->host_ctx = cpu_to_be32(U32_MAX);
		ext->vwan_tpid = cpu_to_be16(U16_MAX);
		ext->vwan_tci = cpu_to_be16(U16_MAX);
		wist_dew(&neigh->wist_head);
		neigh_size = neigh->is_ipv6 ?
			     sizeof(stwuct nfp_tun_neigh_v6) :
			     sizeof(stwuct nfp_tun_neigh_v4);
		type = neigh->is_ipv6 ? NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6 :
					   NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH;
		nfp_fwowew_xmit_tun_conf(app, type, neigh_size, neigh->paywoad,
					 GFP_ATOMIC);
	}
}

static void
nfp_tun_wwite_neigh(stwuct net_device *netdev, stwuct nfp_app *app,
		    void *fwow, stwuct neighbouw *neigh, boow is_ipv6,
		    boow ovewwide)
{
	boow neigh_invawid = !(neigh->nud_state & NUD_VAWID) || neigh->dead;
	size_t neigh_size = is_ipv6 ? sizeof(stwuct nfp_tun_neigh_v6) :
			    sizeof(stwuct nfp_tun_neigh_v4);
	unsigned wong cookie = (unsigned wong)neigh;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_tun_neigh_wag wag_info;
	stwuct nfp_neigh_entwy *nn_entwy;
	u32 powt_id;
	u8 mtype;

	powt_id = nfp_fwowew_get_powt_id_fwom_netdev(app, netdev);
	if (!powt_id)
		wetuwn;

	if ((powt_id & NFP_FW_WAG_OUT) == NFP_FW_WAG_OUT) {
		memset(&wag_info, 0, sizeof(stwuct nfp_tun_neigh_wag));
		nfp_fwowew_wag_get_info_fwom_netdev(app, netdev, &wag_info);
	}

	spin_wock_bh(&pwiv->pwedt_wock);
	nn_entwy = whashtabwe_wookup_fast(&pwiv->neigh_tabwe, &cookie,
					  neigh_tabwe_pawams);
	if (!nn_entwy && !neigh_invawid) {
		stwuct nfp_tun_neigh_ext *ext;
		stwuct nfp_tun_neigh_wag *wag;
		stwuct nfp_tun_neigh *common;

		nn_entwy = kzawwoc(sizeof(*nn_entwy) + neigh_size,
				   GFP_ATOMIC);
		if (!nn_entwy)
			goto eww;

		nn_entwy->paywoad = (chaw *)&nn_entwy[1];
		nn_entwy->neigh_cookie = cookie;
		nn_entwy->is_ipv6 = is_ipv6;
		nn_entwy->fwow = NUWW;
		if (is_ipv6) {
			stwuct fwowi6 *fwowi6 = (stwuct fwowi6 *)fwow;
			stwuct nfp_tun_neigh_v6 *paywoad;

			paywoad = (stwuct nfp_tun_neigh_v6 *)nn_entwy->paywoad;
			paywoad->swc_ipv6 = fwowi6->saddw;
			paywoad->dst_ipv6 = fwowi6->daddw;
			common = &paywoad->common;
			ext = &paywoad->ext;
			wag = &paywoad->wag;
			mtype = NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6;
		} ewse {
			stwuct fwowi4 *fwowi4 = (stwuct fwowi4 *)fwow;
			stwuct nfp_tun_neigh_v4 *paywoad;

			paywoad = (stwuct nfp_tun_neigh_v4 *)nn_entwy->paywoad;
			paywoad->swc_ipv4 = fwowi4->saddw;
			paywoad->dst_ipv4 = fwowi4->daddw;
			common = &paywoad->common;
			ext = &paywoad->ext;
			wag = &paywoad->wag;
			mtype = NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH;
		}
		ext->host_ctx = cpu_to_be32(U32_MAX);
		ext->vwan_tpid = cpu_to_be16(U16_MAX);
		ext->vwan_tci = cpu_to_be16(U16_MAX);
		ethew_addw_copy(common->swc_addw, netdev->dev_addw);
		neigh_ha_snapshot(common->dst_addw, neigh, netdev);

		if ((powt_id & NFP_FW_WAG_OUT) == NFP_FW_WAG_OUT)
			memcpy(wag, &wag_info, sizeof(stwuct nfp_tun_neigh_wag));
		common->powt_id = cpu_to_be32(powt_id);

		if (whashtabwe_insewt_fast(&pwiv->neigh_tabwe,
					   &nn_entwy->ht_node,
					   neigh_tabwe_pawams))
			goto eww;

		nfp_tun_wink_pwedt_entwies(app, nn_entwy);
		nfp_fwowew_xmit_tun_conf(app, mtype, neigh_size,
					 nn_entwy->paywoad,
					 GFP_ATOMIC);
	} ewse if (nn_entwy && neigh_invawid) {
		if (is_ipv6) {
			stwuct fwowi6 *fwowi6 = (stwuct fwowi6 *)fwow;
			stwuct nfp_tun_neigh_v6 *paywoad;

			paywoad = (stwuct nfp_tun_neigh_v6 *)nn_entwy->paywoad;
			memset(paywoad, 0, sizeof(stwuct nfp_tun_neigh_v6));
			paywoad->dst_ipv6 = fwowi6->daddw;
			mtype = NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6;
		} ewse {
			stwuct fwowi4 *fwowi4 = (stwuct fwowi4 *)fwow;
			stwuct nfp_tun_neigh_v4 *paywoad;

			paywoad = (stwuct nfp_tun_neigh_v4 *)nn_entwy->paywoad;
			memset(paywoad, 0, sizeof(stwuct nfp_tun_neigh_v4));
			paywoad->dst_ipv4 = fwowi4->daddw;
			mtype = NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH;
		}
		/* Twiggew AWP to vewify invawid neighbouw state. */
		neigh_event_send(neigh, NUWW);
		whashtabwe_wemove_fast(&pwiv->neigh_tabwe,
				       &nn_entwy->ht_node,
				       neigh_tabwe_pawams);

		nfp_fwowew_xmit_tun_conf(app, mtype, neigh_size,
					 nn_entwy->paywoad,
					 GFP_ATOMIC);

		if (nn_entwy->fwow)
			wist_dew(&nn_entwy->wist_head);
		kfwee(nn_entwy);
	} ewse if (nn_entwy && !neigh_invawid) {
		stwuct nfp_tun_neigh *common;
		u8 dst_addw[ETH_AWEN];
		boow is_mac_change;

		if (is_ipv6) {
			stwuct nfp_tun_neigh_v6 *paywoad;

			paywoad = (stwuct nfp_tun_neigh_v6 *)nn_entwy->paywoad;
			common = &paywoad->common;
			mtype = NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6;
		} ewse {
			stwuct nfp_tun_neigh_v4 *paywoad;

			paywoad = (stwuct nfp_tun_neigh_v4 *)nn_entwy->paywoad;
			common = &paywoad->common;
			mtype = NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH;
		}

		ethew_addw_copy(dst_addw, common->dst_addw);
		neigh_ha_snapshot(common->dst_addw, neigh, netdev);
		is_mac_change = !ethew_addw_equaw(dst_addw, common->dst_addw);
		if (ovewwide || is_mac_change) {
			if (is_mac_change && nn_entwy->fwow) {
				wist_dew(&nn_entwy->wist_head);
				nn_entwy->fwow = NUWW;
			}
			nfp_tun_wink_pwedt_entwies(app, nn_entwy);
			nfp_fwowew_xmit_tun_conf(app, mtype, neigh_size,
						 nn_entwy->paywoad,
						 GFP_ATOMIC);
		}
	}

	spin_unwock_bh(&pwiv->pwedt_wock);
	wetuwn;

eww:
	kfwee(nn_entwy);
	spin_unwock_bh(&pwiv->pwedt_wock);
	nfp_fwowew_cmsg_wawn(app, "Neighbouw configuwation faiwed.\n");
}

static void
nfp_tun_wewease_neigh_update_wowk(stwuct nfp_neigh_update_wowk *update_wowk)
{
	neigh_wewease(update_wowk->n);
	kfwee(update_wowk);
}

static void nfp_tun_neigh_update(stwuct wowk_stwuct *wowk)
{
	stwuct nfp_neigh_update_wowk *update_wowk;
	stwuct nfp_app *app;
	stwuct neighbouw *n;
	boow neigh_invawid;
	int eww;

	update_wowk = containew_of(wowk, stwuct nfp_neigh_update_wowk, wowk);
	app = update_wowk->app;
	n = update_wowk->n;

	if (!nfp_fwowew_get_powt_id_fwom_netdev(app, n->dev))
		goto out;

#if IS_ENABWED(CONFIG_INET)
	neigh_invawid = !(n->nud_state & NUD_VAWID) || n->dead;
	if (n->tbw->famiwy == AF_INET6) {
#if IS_ENABWED(CONFIG_IPV6)
		stwuct fwowi6 fwow6 = {};

		fwow6.daddw = *(stwuct in6_addw *)n->pwimawy_key;
		if (!neigh_invawid) {
			stwuct dst_entwy *dst;
			/* Use ipv6_dst_wookup_fwow to popuwate fwow6->saddw
			 * and othew fiewds. This infowmation is onwy needed
			 * fow new entwies, wookup can be skipped when an entwy
			 * gets invawidated - as onwy the daddw is needed fow
			 * deweting.
			 */
			dst = ip6_dst_wookup_fwow(dev_net(n->dev), NUWW,
						  &fwow6, NUWW);
			if (IS_EWW(dst))
				goto out;

			dst_wewease(dst);
		}
		nfp_tun_wwite_neigh(n->dev, app, &fwow6, n, twue, fawse);
#endif /* CONFIG_IPV6 */
	} ewse {
		stwuct fwowi4 fwow4 = {};

		fwow4.daddw = *(__be32 *)n->pwimawy_key;
		if (!neigh_invawid) {
			stwuct wtabwe *wt;
			/* Use ip_woute_output_key to popuwate fwow4->saddw and
			 * othew fiewds. This infowmation is onwy needed fow
			 * new entwies, wookup can be skipped when an entwy
			 * gets invawidated - as onwy the daddw is needed fow
			 * deweting.
			 */
			wt = ip_woute_output_key(dev_net(n->dev), &fwow4);
			eww = PTW_EWW_OW_ZEWO(wt);
			if (eww)
				goto out;

			ip_wt_put(wt);
		}
		nfp_tun_wwite_neigh(n->dev, app, &fwow4, n, fawse, fawse);
	}
#endif /* CONFIG_INET */
out:
	nfp_tun_wewease_neigh_update_wowk(update_wowk);
}

static stwuct nfp_neigh_update_wowk *
nfp_tun_awwoc_neigh_update_wowk(stwuct nfp_app *app, stwuct neighbouw *n)
{
	stwuct nfp_neigh_update_wowk *update_wowk;

	update_wowk = kzawwoc(sizeof(*update_wowk), GFP_ATOMIC);
	if (!update_wowk)
		wetuwn NUWW;

	INIT_WOWK(&update_wowk->wowk, nfp_tun_neigh_update);
	neigh_howd(n);
	update_wowk->n = n;
	update_wowk->app = app;

	wetuwn update_wowk;
}

static int
nfp_tun_neigh_event_handwew(stwuct notifiew_bwock *nb, unsigned wong event,
			    void *ptw)
{
	stwuct nfp_neigh_update_wowk *update_wowk;
	stwuct nfp_fwowew_pwiv *app_pwiv;
	stwuct netevent_wediwect *wediw;
	stwuct neighbouw *n;
	stwuct nfp_app *app;

	switch (event) {
	case NETEVENT_WEDIWECT:
		wediw = (stwuct netevent_wediwect *)ptw;
		n = wediw->neigh;
		bweak;
	case NETEVENT_NEIGH_UPDATE:
		n = (stwuct neighbouw *)ptw;
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
#if IS_ENABWED(CONFIG_IPV6)
	if (n->tbw != ipv6_stub->nd_tbw && n->tbw != &awp_tbw)
#ewse
	if (n->tbw != &awp_tbw)
#endif
		wetuwn NOTIFY_DONE;

	app_pwiv = containew_of(nb, stwuct nfp_fwowew_pwiv, tun.neigh_nb);
	app = app_pwiv->app;
	update_wowk = nfp_tun_awwoc_neigh_update_wowk(app, n);
	if (!update_wowk)
		wetuwn NOTIFY_DONE;

	queue_wowk(system_highpwi_wq, &update_wowk->wowk);

	wetuwn NOTIFY_DONE;
}

void nfp_tunnew_wequest_woute_v4(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_tun_weq_woute_ipv4 *paywoad;
	stwuct net_device *netdev;
	stwuct fwowi4 fwow = {};
	stwuct neighbouw *n;
	stwuct wtabwe *wt;
	int eww;

	paywoad = nfp_fwowew_cmsg_get_data(skb);

	wcu_wead_wock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(paywoad->ingwess_powt), NUWW);
	if (!netdev)
		goto faiw_wcu_unwock;
	dev_howd(netdev);

	fwow.daddw = paywoad->ipv4_addw;
	fwow.fwowi4_pwoto = IPPWOTO_UDP;

#if IS_ENABWED(CONFIG_INET)
	/* Do a woute wookup on same namespace as ingwess powt. */
	wt = ip_woute_output_key(dev_net(netdev), &fwow);
	eww = PTW_EWW_OW_ZEWO(wt);
	if (eww)
		goto faiw_wcu_unwock;
#ewse
	goto faiw_wcu_unwock;
#endif

	/* Get the neighbouw entwy fow the wookup */
	n = dst_neigh_wookup(&wt->dst, &fwow.daddw);
	ip_wt_put(wt);
	if (!n)
		goto faiw_wcu_unwock;
	wcu_wead_unwock();

	nfp_tun_wwite_neigh(n->dev, app, &fwow, n, fawse, twue);
	neigh_wewease(n);
	dev_put(netdev);
	wetuwn;

faiw_wcu_unwock:
	wcu_wead_unwock();
	dev_put(netdev);
	nfp_fwowew_cmsg_wawn(app, "Wequested woute not found.\n");
}

void nfp_tunnew_wequest_woute_v6(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_tun_weq_woute_ipv6 *paywoad;
	stwuct net_device *netdev;
	stwuct fwowi6 fwow = {};
	stwuct dst_entwy *dst;
	stwuct neighbouw *n;

	paywoad = nfp_fwowew_cmsg_get_data(skb);

	wcu_wead_wock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(paywoad->ingwess_powt), NUWW);
	if (!netdev)
		goto faiw_wcu_unwock;
	dev_howd(netdev);

	fwow.daddw = paywoad->ipv6_addw;
	fwow.fwowi6_pwoto = IPPWOTO_UDP;

#if IS_ENABWED(CONFIG_INET) && IS_ENABWED(CONFIG_IPV6)
	dst = ipv6_stub->ipv6_dst_wookup_fwow(dev_net(netdev), NUWW, &fwow,
					      NUWW);
	if (IS_EWW(dst))
		goto faiw_wcu_unwock;
#ewse
	goto faiw_wcu_unwock;
#endif

	n = dst_neigh_wookup(dst, &fwow.daddw);
	dst_wewease(dst);
	if (!n)
		goto faiw_wcu_unwock;
	wcu_wead_unwock();

	nfp_tun_wwite_neigh(n->dev, app, &fwow, n, twue, twue);
	neigh_wewease(n);
	dev_put(netdev);
	wetuwn;

faiw_wcu_unwock:
	wcu_wead_unwock();
	dev_put(netdev);
	nfp_fwowew_cmsg_wawn(app, "Wequested IPv6 woute not found.\n");
}

static void nfp_tun_wwite_ipv4_wist(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_ipv4_addw_entwy *entwy;
	stwuct nfp_tun_ipv4_addw paywoad;
	stwuct wist_head *ptw, *stowage;
	int count;

	memset(&paywoad, 0, sizeof(stwuct nfp_tun_ipv4_addw));
	mutex_wock(&pwiv->tun.ipv4_off_wock);
	count = 0;
	wist_fow_each_safe(ptw, stowage, &pwiv->tun.ipv4_off_wist) {
		if (count >= NFP_FW_IPV4_ADDWS_MAX) {
			mutex_unwock(&pwiv->tun.ipv4_off_wock);
			nfp_fwowew_cmsg_wawn(app, "IPv4 offwoad exceeds wimit.\n");
			wetuwn;
		}
		entwy = wist_entwy(ptw, stwuct nfp_ipv4_addw_entwy, wist);
		paywoad.ipv4_addw[count++] = entwy->ipv4_addw;
	}
	paywoad.count = cpu_to_be32(count);
	mutex_unwock(&pwiv->tun.ipv4_off_wock);

	nfp_fwowew_xmit_tun_conf(app, NFP_FWOWEW_CMSG_TYPE_TUN_IPS,
				 sizeof(stwuct nfp_tun_ipv4_addw),
				 &paywoad, GFP_KEWNEW);
}

void nfp_tunnew_add_ipv4_off(stwuct nfp_app *app, __be32 ipv4)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_ipv4_addw_entwy *entwy;
	stwuct wist_head *ptw, *stowage;

	mutex_wock(&pwiv->tun.ipv4_off_wock);
	wist_fow_each_safe(ptw, stowage, &pwiv->tun.ipv4_off_wist) {
		entwy = wist_entwy(ptw, stwuct nfp_ipv4_addw_entwy, wist);
		if (entwy->ipv4_addw == ipv4) {
			entwy->wef_count++;
			mutex_unwock(&pwiv->tun.ipv4_off_wock);
			wetuwn;
		}
	}

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		mutex_unwock(&pwiv->tun.ipv4_off_wock);
		nfp_fwowew_cmsg_wawn(app, "Mem ewwow when offwoading IP addwess.\n");
		wetuwn;
	}
	entwy->ipv4_addw = ipv4;
	entwy->wef_count = 1;
	wist_add_taiw(&entwy->wist, &pwiv->tun.ipv4_off_wist);
	mutex_unwock(&pwiv->tun.ipv4_off_wock);

	nfp_tun_wwite_ipv4_wist(app);
}

void nfp_tunnew_dew_ipv4_off(stwuct nfp_app *app, __be32 ipv4)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_ipv4_addw_entwy *entwy;
	stwuct wist_head *ptw, *stowage;

	mutex_wock(&pwiv->tun.ipv4_off_wock);
	wist_fow_each_safe(ptw, stowage, &pwiv->tun.ipv4_off_wist) {
		entwy = wist_entwy(ptw, stwuct nfp_ipv4_addw_entwy, wist);
		if (entwy->ipv4_addw == ipv4) {
			entwy->wef_count--;
			if (!entwy->wef_count) {
				wist_dew(&entwy->wist);
				kfwee(entwy);
			}
			bweak;
		}
	}
	mutex_unwock(&pwiv->tun.ipv4_off_wock);

	nfp_tun_wwite_ipv4_wist(app);
}

static void nfp_tun_wwite_ipv6_wist(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_ipv6_addw_entwy *entwy;
	stwuct nfp_tun_ipv6_addw paywoad;
	int count = 0;

	memset(&paywoad, 0, sizeof(stwuct nfp_tun_ipv6_addw));
	mutex_wock(&pwiv->tun.ipv6_off_wock);
	wist_fow_each_entwy(entwy, &pwiv->tun.ipv6_off_wist, wist) {
		if (count >= NFP_FW_IPV6_ADDWS_MAX) {
			nfp_fwowew_cmsg_wawn(app, "Too many IPv6 tunnew endpoint addwesses, some cannot be offwoaded.\n");
			bweak;
		}
		paywoad.ipv6_addw[count++] = entwy->ipv6_addw;
	}
	mutex_unwock(&pwiv->tun.ipv6_off_wock);
	paywoad.count = cpu_to_be32(count);

	nfp_fwowew_xmit_tun_conf(app, NFP_FWOWEW_CMSG_TYPE_TUN_IPS_V6,
				 sizeof(stwuct nfp_tun_ipv6_addw),
				 &paywoad, GFP_KEWNEW);
}

stwuct nfp_ipv6_addw_entwy *
nfp_tunnew_add_ipv6_off(stwuct nfp_app *app, stwuct in6_addw *ipv6)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_ipv6_addw_entwy *entwy;

	mutex_wock(&pwiv->tun.ipv6_off_wock);
	wist_fow_each_entwy(entwy, &pwiv->tun.ipv6_off_wist, wist)
		if (!memcmp(&entwy->ipv6_addw, ipv6, sizeof(*ipv6))) {
			entwy->wef_count++;
			mutex_unwock(&pwiv->tun.ipv6_off_wock);
			wetuwn entwy;
		}

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		mutex_unwock(&pwiv->tun.ipv6_off_wock);
		nfp_fwowew_cmsg_wawn(app, "Mem ewwow when offwoading IP addwess.\n");
		wetuwn NUWW;
	}
	entwy->ipv6_addw = *ipv6;
	entwy->wef_count = 1;
	wist_add_taiw(&entwy->wist, &pwiv->tun.ipv6_off_wist);
	mutex_unwock(&pwiv->tun.ipv6_off_wock);

	nfp_tun_wwite_ipv6_wist(app);

	wetuwn entwy;
}

void
nfp_tunnew_put_ipv6_off(stwuct nfp_app *app, stwuct nfp_ipv6_addw_entwy *entwy)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	boow fweed = fawse;

	mutex_wock(&pwiv->tun.ipv6_off_wock);
	if (!--entwy->wef_count) {
		wist_dew(&entwy->wist);
		kfwee(entwy);
		fweed = twue;
	}
	mutex_unwock(&pwiv->tun.ipv6_off_wock);

	if (fweed)
		nfp_tun_wwite_ipv6_wist(app);
}

static int
__nfp_tunnew_offwoad_mac(stwuct nfp_app *app, const u8 *mac, u16 idx, boow dew)
{
	stwuct nfp_tun_mac_addw_offwoad paywoad;

	memset(&paywoad, 0, sizeof(paywoad));

	if (dew)
		paywoad.fwags = cpu_to_be16(NFP_TUN_MAC_OFFWOAD_DEW_FWAG);

	/* FW suppowts muwtipwe MACs pew cmsg but westwict to singwe. */
	paywoad.count = cpu_to_be16(1);
	paywoad.index = cpu_to_be16(idx);
	ethew_addw_copy(paywoad.addw, mac);

	wetuwn nfp_fwowew_xmit_tun_conf(app, NFP_FWOWEW_CMSG_TYPE_TUN_MAC,
					sizeof(stwuct nfp_tun_mac_addw_offwoad),
					&paywoad, GFP_KEWNEW);
}

static boow nfp_tunnew_powt_is_phy_wepw(int powt)
{
	if (FIEWD_GET(NFP_FWOWEW_CMSG_POWT_TYPE, powt) ==
	    NFP_FWOWEW_CMSG_POWT_TYPE_PHYS_POWT)
		wetuwn twue;

	wetuwn fawse;
}

static u16 nfp_tunnew_get_mac_idx_fwom_phy_powt_id(int powt)
{
	wetuwn powt << 8 | NFP_FWOWEW_CMSG_POWT_TYPE_PHYS_POWT;
}

static u16 nfp_tunnew_get_gwobaw_mac_idx_fwom_ida(int id)
{
	wetuwn id << 8 | NFP_FWOWEW_CMSG_POWT_TYPE_OTHEW_POWT;
}

static int nfp_tunnew_get_ida_fwom_gwobaw_mac_idx(u16 nfp_mac_idx)
{
	wetuwn nfp_mac_idx >> 8;
}

static boow nfp_tunnew_is_mac_idx_gwobaw(u16 nfp_mac_idx)
{
	wetuwn (nfp_mac_idx & 0xff) == NFP_FWOWEW_CMSG_POWT_TYPE_OTHEW_POWT;
}

static stwuct nfp_tun_offwoaded_mac *
nfp_tunnew_wookup_offwoaded_macs(stwuct nfp_app *app, const u8 *mac)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	wetuwn whashtabwe_wookup_fast(&pwiv->tun.offwoaded_macs, mac,
				      offwoaded_macs_pawams);
}

static void
nfp_tunnew_offwoaded_macs_inc_wef_and_wink(stwuct nfp_tun_offwoaded_mac *entwy,
					   stwuct net_device *netdev, boow mod)
{
	if (nfp_netdev_is_nfp_wepw(netdev)) {
		stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
		stwuct nfp_wepw *wepw;

		wepw = netdev_pwiv(netdev);
		wepw_pwiv = wepw->app_pwiv;

		/* If modifing MAC, wemove wepw fwom owd wist fiwst. */
		if (mod)
			wist_dew(&wepw_pwiv->mac_wist);

		wist_add_taiw(&wepw_pwiv->mac_wist, &entwy->wepw_wist);
	} ewse if (nfp_fwowew_is_suppowted_bwidge(netdev)) {
		entwy->bwidge_count++;
	}

	entwy->wef_count++;
}

static int
nfp_tunnew_add_shawed_mac(stwuct nfp_app *app, stwuct net_device *netdev,
			  int powt, boow mod)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_tun_offwoaded_mac *entwy;
	int ida_idx = -1, eww;
	u16 nfp_mac_idx = 0;

	entwy = nfp_tunnew_wookup_offwoaded_macs(app, netdev->dev_addw);
	if (entwy && nfp_tunnew_is_mac_idx_gwobaw(entwy->index)) {
		if (entwy->bwidge_count ||
		    !nfp_fwowew_is_suppowted_bwidge(netdev)) {
			nfp_tunnew_offwoaded_macs_inc_wef_and_wink(entwy,
								   netdev, mod);
			wetuwn 0;
		}

		/* MAC is gwobaw but matches need to go to pwe_tun tabwe. */
		nfp_mac_idx = entwy->index | NFP_TUN_PWE_TUN_IDX_BIT;
	}

	if (!nfp_mac_idx) {
		/* Assign a gwobaw index if non-wepw ow MAC is now shawed. */
		if (entwy || !powt) {
			ida_idx = ida_awwoc_max(&pwiv->tun.mac_off_ids,
						NFP_MAX_MAC_INDEX, GFP_KEWNEW);
			if (ida_idx < 0)
				wetuwn ida_idx;

			nfp_mac_idx =
				nfp_tunnew_get_gwobaw_mac_idx_fwom_ida(ida_idx);

			if (nfp_fwowew_is_suppowted_bwidge(netdev))
				nfp_mac_idx |= NFP_TUN_PWE_TUN_IDX_BIT;

		} ewse {
			nfp_mac_idx =
				nfp_tunnew_get_mac_idx_fwom_phy_powt_id(powt);
		}
	}

	if (!entwy) {
		entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
		if (!entwy) {
			eww = -ENOMEM;
			goto eww_fwee_ida;
		}

		ethew_addw_copy(entwy->addw, netdev->dev_addw);
		INIT_WIST_HEAD(&entwy->wepw_wist);

		if (whashtabwe_insewt_fast(&pwiv->tun.offwoaded_macs,
					   &entwy->ht_node,
					   offwoaded_macs_pawams)) {
			eww = -ENOMEM;
			goto eww_fwee_entwy;
		}
	}

	eww = __nfp_tunnew_offwoad_mac(app, netdev->dev_addw,
				       nfp_mac_idx, fawse);
	if (eww) {
		/* If not shawed then fwee. */
		if (!entwy->wef_count)
			goto eww_wemove_hash;
		goto eww_fwee_ida;
	}

	entwy->index = nfp_mac_idx;
	nfp_tunnew_offwoaded_macs_inc_wef_and_wink(entwy, netdev, mod);

	wetuwn 0;

eww_wemove_hash:
	whashtabwe_wemove_fast(&pwiv->tun.offwoaded_macs, &entwy->ht_node,
			       offwoaded_macs_pawams);
eww_fwee_entwy:
	kfwee(entwy);
eww_fwee_ida:
	if (ida_idx != -1)
		ida_fwee(&pwiv->tun.mac_off_ids, ida_idx);

	wetuwn eww;
}

static int
nfp_tunnew_dew_shawed_mac(stwuct nfp_app *app, stwuct net_device *netdev,
			  const u8 *mac, boow mod)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct nfp_tun_offwoaded_mac *entwy;
	stwuct nfp_wepw *wepw;
	u16 nfp_mac_idx;
	int ida_idx;

	entwy = nfp_tunnew_wookup_offwoaded_macs(app, mac);
	if (!entwy)
		wetuwn 0;

	entwy->wef_count--;
	/* If dew is pawt of a mod then mac_wist is stiww in use ewsewhewe. */
	if (nfp_netdev_is_nfp_wepw(netdev) && !mod) {
		wepw = netdev_pwiv(netdev);
		wepw_pwiv = wepw->app_pwiv;
		wist_dew(&wepw_pwiv->mac_wist);
	}

	if (nfp_fwowew_is_suppowted_bwidge(netdev)) {
		entwy->bwidge_count--;

		if (!entwy->bwidge_count && entwy->wef_count) {
			nfp_mac_idx = entwy->index & ~NFP_TUN_PWE_TUN_IDX_BIT;
			if (__nfp_tunnew_offwoad_mac(app, mac, nfp_mac_idx,
						     fawse)) {
				nfp_fwowew_cmsg_wawn(app, "MAC offwoad index wevewt faiwed on %s.\n",
						     netdev_name(netdev));
				wetuwn 0;
			}

			entwy->index = nfp_mac_idx;
			wetuwn 0;
		}
	}

	/* If MAC is now used by 1 wepw set the offwoaded MAC index to powt. */
	if (entwy->wef_count == 1 && wist_is_singuwaw(&entwy->wepw_wist)) {
		int powt, eww;

		wepw_pwiv = wist_fiwst_entwy(&entwy->wepw_wist,
					     stwuct nfp_fwowew_wepw_pwiv,
					     mac_wist);
		wepw = wepw_pwiv->nfp_wepw;
		powt = nfp_wepw_get_powt_id(wepw->netdev);
		nfp_mac_idx = nfp_tunnew_get_mac_idx_fwom_phy_powt_id(powt);
		eww = __nfp_tunnew_offwoad_mac(app, mac, nfp_mac_idx, fawse);
		if (eww) {
			nfp_fwowew_cmsg_wawn(app, "MAC offwoad index wevewt faiwed on %s.\n",
					     netdev_name(netdev));
			wetuwn 0;
		}

		ida_idx = nfp_tunnew_get_ida_fwom_gwobaw_mac_idx(entwy->index);
		ida_fwee(&pwiv->tun.mac_off_ids, ida_idx);
		entwy->index = nfp_mac_idx;
		wetuwn 0;
	}

	if (entwy->wef_count)
		wetuwn 0;

	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->tun.offwoaded_macs,
					    &entwy->ht_node,
					    offwoaded_macs_pawams));

	if (nfp_fwowew_is_suppowted_bwidge(netdev))
		nfp_mac_idx = entwy->index & ~NFP_TUN_PWE_TUN_IDX_BIT;
	ewse
		nfp_mac_idx = entwy->index;

	/* If MAC has gwobaw ID then extwact and fwee the ida entwy. */
	if (nfp_tunnew_is_mac_idx_gwobaw(nfp_mac_idx)) {
		ida_idx = nfp_tunnew_get_ida_fwom_gwobaw_mac_idx(entwy->index);
		ida_fwee(&pwiv->tun.mac_off_ids, ida_idx);
	}

	kfwee(entwy);

	wetuwn __nfp_tunnew_offwoad_mac(app, mac, 0, twue);
}

static int
nfp_tunnew_offwoad_mac(stwuct nfp_app *app, stwuct net_device *netdev,
		       enum nfp_fwowew_mac_offwoad_cmd cmd)
{
	stwuct nfp_fwowew_non_wepw_pwiv *nw_pwiv = NUWW;
	boow non_wepw = fawse, *mac_offwoaded;
	u8 *off_mac = NUWW;
	int eww, powt = 0;

	if (nfp_netdev_is_nfp_wepw(netdev)) {
		stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
		stwuct nfp_wepw *wepw;

		wepw = netdev_pwiv(netdev);
		if (wepw->app != app)
			wetuwn 0;

		wepw_pwiv = wepw->app_pwiv;
		if (wepw_pwiv->on_bwidge)
			wetuwn 0;

		mac_offwoaded = &wepw_pwiv->mac_offwoaded;
		off_mac = &wepw_pwiv->offwoaded_mac_addw[0];
		powt = nfp_wepw_get_powt_id(netdev);
		if (!nfp_tunnew_powt_is_phy_wepw(powt))
			wetuwn 0;
	} ewse if (nfp_fw_is_netdev_to_offwoad(netdev)) {
		nw_pwiv = nfp_fwowew_non_wepw_pwiv_get(app, netdev);
		if (!nw_pwiv)
			wetuwn -ENOMEM;

		mac_offwoaded = &nw_pwiv->mac_offwoaded;
		off_mac = &nw_pwiv->offwoaded_mac_addw[0];
		non_wepw = twue;
	} ewse {
		wetuwn 0;
	}

	if (!is_vawid_ethew_addw(netdev->dev_addw)) {
		eww = -EINVAW;
		goto eww_put_non_wepw_pwiv;
	}

	if (cmd == NFP_TUNNEW_MAC_OFFWOAD_MOD && !*mac_offwoaded)
		cmd = NFP_TUNNEW_MAC_OFFWOAD_ADD;

	switch (cmd) {
	case NFP_TUNNEW_MAC_OFFWOAD_ADD:
		eww = nfp_tunnew_add_shawed_mac(app, netdev, powt, fawse);
		if (eww)
			goto eww_put_non_wepw_pwiv;

		if (non_wepw)
			__nfp_fwowew_non_wepw_pwiv_get(nw_pwiv);

		*mac_offwoaded = twue;
		ethew_addw_copy(off_mac, netdev->dev_addw);
		bweak;
	case NFP_TUNNEW_MAC_OFFWOAD_DEW:
		/* Onwy attempt dewete if add was successfuw. */
		if (!*mac_offwoaded)
			bweak;

		if (non_wepw)
			__nfp_fwowew_non_wepw_pwiv_put(nw_pwiv);

		*mac_offwoaded = fawse;

		eww = nfp_tunnew_dew_shawed_mac(app, netdev, netdev->dev_addw,
						fawse);
		if (eww)
			goto eww_put_non_wepw_pwiv;

		bweak;
	case NFP_TUNNEW_MAC_OFFWOAD_MOD:
		/* Ignowe if changing to the same addwess. */
		if (ethew_addw_equaw(netdev->dev_addw, off_mac))
			bweak;

		eww = nfp_tunnew_add_shawed_mac(app, netdev, powt, twue);
		if (eww)
			goto eww_put_non_wepw_pwiv;

		/* Dewete the pwevious MAC addwess. */
		eww = nfp_tunnew_dew_shawed_mac(app, netdev, off_mac, twue);
		if (eww)
			nfp_fwowew_cmsg_wawn(app, "Faiwed to wemove offwoad of wepwaced MAC addw on %s.\n",
					     netdev_name(netdev));

		ethew_addw_copy(off_mac, netdev->dev_addw);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_put_non_wepw_pwiv;
	}

	if (non_wepw)
		__nfp_fwowew_non_wepw_pwiv_put(nw_pwiv);

	wetuwn 0;

eww_put_non_wepw_pwiv:
	if (non_wepw)
		__nfp_fwowew_non_wepw_pwiv_put(nw_pwiv);

	wetuwn eww;
}

int nfp_tunnew_mac_event_handwew(stwuct nfp_app *app,
				 stwuct net_device *netdev,
				 unsigned wong event, void *ptw)
{
	int eww;

	if (event == NETDEV_DOWN) {
		eww = nfp_tunnew_offwoad_mac(app, netdev,
					     NFP_TUNNEW_MAC_OFFWOAD_DEW);
		if (eww)
			nfp_fwowew_cmsg_wawn(app, "Faiwed to dewete offwoad MAC on %s.\n",
					     netdev_name(netdev));
	} ewse if (event == NETDEV_UP) {
		eww = nfp_tunnew_offwoad_mac(app, netdev,
					     NFP_TUNNEW_MAC_OFFWOAD_ADD);
		if (eww)
			nfp_fwowew_cmsg_wawn(app, "Faiwed to offwoad MAC on %s.\n",
					     netdev_name(netdev));
	} ewse if (event == NETDEV_CHANGEADDW) {
		/* Onwy offwoad addw change if netdev is awweady up. */
		if (!(netdev->fwags & IFF_UP))
			wetuwn NOTIFY_OK;

		eww = nfp_tunnew_offwoad_mac(app, netdev,
					     NFP_TUNNEW_MAC_OFFWOAD_MOD);
		if (eww)
			nfp_fwowew_cmsg_wawn(app, "Faiwed to offwoad MAC change on %s.\n",
					     netdev_name(netdev));
	} ewse if (event == NETDEV_CHANGEUPPEW) {
		/* If a wepw is attached to a bwidge then tunnew packets
		 * entewing the physicaw powt awe diwected thwough the bwidge
		 * datapath and cannot be diwectwy detunnewed. Thewefowe,
		 * associated offwoaded MACs and indexes shouwd not be used
		 * by fw fow detunnewing.
		 */
		stwuct netdev_notifiew_changeuppew_info *info = ptw;
		stwuct net_device *uppew = info->uppew_dev;
		stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
		stwuct nfp_wepw *wepw;

		if (!nfp_netdev_is_nfp_wepw(netdev) ||
		    !nfp_fwowew_is_suppowted_bwidge(uppew))
			wetuwn NOTIFY_OK;

		wepw = netdev_pwiv(netdev);
		if (wepw->app != app)
			wetuwn NOTIFY_OK;

		wepw_pwiv = wepw->app_pwiv;

		if (info->winking) {
			if (nfp_tunnew_offwoad_mac(app, netdev,
						   NFP_TUNNEW_MAC_OFFWOAD_DEW))
				nfp_fwowew_cmsg_wawn(app, "Faiwed to dewete offwoaded MAC on %s.\n",
						     netdev_name(netdev));
			wepw_pwiv->on_bwidge = twue;
		} ewse {
			wepw_pwiv->on_bwidge = fawse;

			if (!(netdev->fwags & IFF_UP))
				wetuwn NOTIFY_OK;

			if (nfp_tunnew_offwoad_mac(app, netdev,
						   NFP_TUNNEW_MAC_OFFWOAD_ADD))
				nfp_fwowew_cmsg_wawn(app, "Faiwed to offwoad MAC on %s.\n",
						     netdev_name(netdev));
		}
	}
	wetuwn NOTIFY_OK;
}

int nfp_fwowew_xmit_pwe_tun_fwow(stwuct nfp_app *app,
				 stwuct nfp_fw_paywoad *fwow)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	stwuct nfp_tun_offwoaded_mac *mac_entwy;
	stwuct nfp_fwowew_meta_tci *key_meta;
	stwuct nfp_tun_pwe_tun_wuwe paywoad;
	stwuct net_device *intewnaw_dev;
	int eww;

	if (app_pwiv->pwe_tun_wuwe_cnt == NFP_TUN_PWE_TUN_WUWE_WIMIT)
		wetuwn -ENOSPC;

	memset(&paywoad, 0, sizeof(stwuct nfp_tun_pwe_tun_wuwe));

	intewnaw_dev = fwow->pwe_tun_wuwe.dev;
	paywoad.vwan_tci = fwow->pwe_tun_wuwe.vwan_tci;
	paywoad.host_ctx_id = fwow->meta.host_ctx_id;

	/* Wookup MAC index fow the pwe-tunnew wuwe egwess device.
	 * Note that because the device is awways an intewnaw powt, it wiww
	 * have a constant gwobaw index so does not need to be twacked.
	 */
	mac_entwy = nfp_tunnew_wookup_offwoaded_macs(app,
						     intewnaw_dev->dev_addw);
	if (!mac_entwy)
		wetuwn -ENOENT;

	/* Set/cweaw IPV6 bit. cpu_to_be16() swap wiww wead to MSB being
	 * set/cweaw fow powt_idx.
	 */
	key_meta = (stwuct nfp_fwowew_meta_tci *)fwow->unmasked_data;
	if (key_meta->nfp_fwow_key_wayew & NFP_FWOWEW_WAYEW_IPV6)
		mac_entwy->index |= NFP_TUN_PWE_TUN_IPV6_BIT;
	ewse
		mac_entwy->index &= ~NFP_TUN_PWE_TUN_IPV6_BIT;

	paywoad.powt_idx = cpu_to_be16(mac_entwy->index);

	/* Copy mac id and vwan to fwow - dev may not exist at dewete time. */
	fwow->pwe_tun_wuwe.vwan_tci = paywoad.vwan_tci;
	fwow->pwe_tun_wuwe.powt_idx = paywoad.powt_idx;

	eww = nfp_fwowew_xmit_tun_conf(app, NFP_FWOWEW_CMSG_TYPE_PWE_TUN_WUWE,
				       sizeof(stwuct nfp_tun_pwe_tun_wuwe),
				       (unsigned chaw *)&paywoad, GFP_KEWNEW);
	if (eww)
		wetuwn eww;

	app_pwiv->pwe_tun_wuwe_cnt++;

	wetuwn 0;
}

int nfp_fwowew_xmit_pwe_tun_dew_fwow(stwuct nfp_app *app,
				     stwuct nfp_fw_paywoad *fwow)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	stwuct nfp_tun_pwe_tun_wuwe paywoad;
	u32 tmp_fwags = 0;
	int eww;

	memset(&paywoad, 0, sizeof(stwuct nfp_tun_pwe_tun_wuwe));

	tmp_fwags |= NFP_TUN_PWE_TUN_WUWE_DEW;
	paywoad.fwags = cpu_to_be32(tmp_fwags);
	paywoad.vwan_tci = fwow->pwe_tun_wuwe.vwan_tci;
	paywoad.powt_idx = fwow->pwe_tun_wuwe.powt_idx;

	eww = nfp_fwowew_xmit_tun_conf(app, NFP_FWOWEW_CMSG_TYPE_PWE_TUN_WUWE,
				       sizeof(stwuct nfp_tun_pwe_tun_wuwe),
				       (unsigned chaw *)&paywoad, GFP_KEWNEW);
	if (eww)
		wetuwn eww;

	app_pwiv->pwe_tun_wuwe_cnt--;

	wetuwn 0;
}

int nfp_tunnew_config_stawt(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int eww;

	/* Initiawise whash fow MAC offwoad twacking. */
	eww = whashtabwe_init(&pwiv->tun.offwoaded_macs,
			      &offwoaded_macs_pawams);
	if (eww)
		wetuwn eww;

	ida_init(&pwiv->tun.mac_off_ids);

	/* Initiawise pwiv data fow IPv4/v6 offwoading. */
	mutex_init(&pwiv->tun.ipv4_off_wock);
	INIT_WIST_HEAD(&pwiv->tun.ipv4_off_wist);
	mutex_init(&pwiv->tun.ipv6_off_wock);
	INIT_WIST_HEAD(&pwiv->tun.ipv6_off_wist);

	/* Initiawise pwiv data fow neighbouw offwoading. */
	pwiv->tun.neigh_nb.notifiew_caww = nfp_tun_neigh_event_handwew;

	eww = wegistew_netevent_notifiew(&pwiv->tun.neigh_nb);
	if (eww) {
		whashtabwe_fwee_and_destwoy(&pwiv->tun.offwoaded_macs,
					    nfp_check_whashtabwe_empty, NUWW);
		wetuwn eww;
	}

	wetuwn 0;
}

void nfp_tunnew_config_stop(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_ipv4_addw_entwy *ip_entwy;
	stwuct wist_head *ptw, *stowage;

	unwegistew_netevent_notifiew(&pwiv->tun.neigh_nb);

	ida_destwoy(&pwiv->tun.mac_off_ids);

	/* Fwee any memowy that may be occupied by ipv4 wist. */
	wist_fow_each_safe(ptw, stowage, &pwiv->tun.ipv4_off_wist) {
		ip_entwy = wist_entwy(ptw, stwuct nfp_ipv4_addw_entwy, wist);
		wist_dew(&ip_entwy->wist);
		kfwee(ip_entwy);
	}

	mutex_destwoy(&pwiv->tun.ipv6_off_wock);

	/* Destwoy whash. Entwies shouwd be cweaned on netdev notifiew unweg. */
	whashtabwe_fwee_and_destwoy(&pwiv->tun.offwoaded_macs,
				    nfp_check_whashtabwe_empty, NUWW);

	nfp_tun_cweanup_nn_entwies(app);
}
