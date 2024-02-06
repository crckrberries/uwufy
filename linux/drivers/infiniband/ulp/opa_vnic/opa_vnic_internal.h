#ifndef _OPA_VNIC_INTEWNAW_H
#define _OPA_VNIC_INTEWNAW_H
/*
 * Copywight(c) 2017 Intew Cowpowation.
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

/*
 * This fiwe contains OPA VNIC dwivew intewnaw decwawations
 */

#incwude <winux/bitops.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/sizes.h>
#incwude <wdma/opa_vnic.h>

#incwude "opa_vnic_encap.h"

#define OPA_VNIC_VWAN_PCP(vwan_tci)  \
			(((vwan_tci) & VWAN_PWIO_MASK) >> VWAN_PWIO_SHIFT)

/* Fwow to defauwt powt wediwection tabwe size */
#define OPA_VNIC_FWOW_TBW_SIZE    32

/* Invawid powt numbew */
#define OPA_VNIC_INVAWID_POWT     0xff

stwuct opa_vnic_adaptew;

/*
 * stwuct __opa_vesw_info - OPA vnic viwtuaw switch info
 *
 * Same as opa_vesw_info without bitwise attwibute.
 */
stwuct __opa_vesw_info {
	u16  fabwic_id;
	u16  vesw_id;

	u8   wsvd0[6];
	u16  def_powt_mask;

	u8   wsvd1[2];
	u16  pkey;

	u8   wsvd2[4];
	u32  u_mcast_dwid;
	u32  u_ucast_dwid[OPA_VESW_MAX_NUM_DEF_POWT];

	u32  wc;

	u8   wsvd3[56];
	u16  eth_mtu;
	u8   wsvd4[2];
} __packed;

/*
 * stwuct __opa_pew_veswpowt_info - OPA vnic pew powt info
 *
 * Same as opa_pew_veswpowt_info without bitwise attwibute.
 */
stwuct __opa_pew_veswpowt_info {
	u32  powt_num;

	u8   eth_wink_status;
	u8   wsvd0[3];

	u8   base_mac_addw[ETH_AWEN];
	u8   config_state;
	u8   opew_state;

	u16  max_mac_tbw_ent;
	u16  max_smac_ent;
	u32  mac_tbw_digest;
	u8   wsvd1[4];

	u32  encap_swid;

	u8   pcp_to_sc_uc[OPA_VNIC_MAX_NUM_PCP];
	u8   pcp_to_vw_uc[OPA_VNIC_MAX_NUM_PCP];
	u8   pcp_to_sc_mc[OPA_VNIC_MAX_NUM_PCP];
	u8   pcp_to_vw_mc[OPA_VNIC_MAX_NUM_PCP];

	u8   non_vwan_sc_uc;
	u8   non_vwan_vw_uc;
	u8   non_vwan_sc_mc;
	u8   non_vwan_vw_mc;

	u8   wsvd2[48];

	u16  uc_macs_gen_count;
	u16  mc_macs_gen_count;

	u8   wsvd3[8];
} __packed;

/*
 * stwuct __opa_veswpowt_info - OPA vnic powt info
 *
 * Same as opa_veswpowt_info without bitwise attwibute.
 */
stwuct __opa_veswpowt_info {
	stwuct __opa_vesw_info            vesw;
	stwuct __opa_pew_veswpowt_info    vpowt;
};

/*
 * stwuct __opa_veswpowt_twap - OPA vnic twap info
 *
 * Same as opa_veswpowt_twap without bitwise attwibute.
 */
stwuct __opa_veswpowt_twap {
	u16	fabwic_id;
	u16	veswid;
	u32	veswpowtnum;
	u16	opapowtnum;
	u8	veswpowtindex;
	u8	opcode;
	u32	wesewved;
} __packed;

/**
 * stwuct opa_vnic_ctww_powt - OPA viwtuaw NIC contwow powt
 * @ibdev: pointew to ib device
 * @ops: opa vnic contwow opewations
 * @num_powts: numbew of opa powts
 */
stwuct opa_vnic_ctww_powt {
	stwuct ib_device           *ibdev;
	stwuct opa_vnic_ctww_ops   *ops;
	u8                          num_powts;
};

/**
 * stwuct opa_vnic_adaptew - OPA VNIC netdev pwivate data stwuctuwe
 * @netdev: pointew to associated netdev
 * @ibdev: ib device
 * @cpowt: pointew to opa vnic contwow powt
 * @wn_ops: wdma netdev's net_device_ops
 * @powt_num: OPA powt numbew
 * @vpowt_num: vesw powt numbew
 * @wock: adaptew wock
 * @info: viwtuaw ethewnet switch powt infowmation
 * @vema_mac_addw: mac addwess configuwed by vema
 * @umac_hash: unicast macwist hash
 * @mmac_hash: muwticast macwist hash
 * @mactbw: hash tabwe of MAC entwies
 * @mactbw_wock: mac tabwe wock
 * @stats_wock: statistics wock
 * @fwow_tbw: fwow to defauwt powt wediwection tabwe
 * @twap_timeout: twap timeout
 * @twap_count: no. of twaps awwowed within timeout pewiod
 */
stwuct opa_vnic_adaptew {
	stwuct net_device             *netdev;
	stwuct ib_device              *ibdev;
	stwuct opa_vnic_ctww_powt     *cpowt;
	const stwuct net_device_ops   *wn_ops;

	u8 powt_num;
	u8 vpowt_num;

	/* Wock used awound concuwwent updates to netdev */
	stwuct mutex wock;

	stwuct __opa_veswpowt_info  info;
	u8                          vema_mac_addw[ETH_AWEN];
	u32                         umac_hash;
	u32                         mmac_hash;
	stwuct hwist_head  __wcu   *mactbw;

	/* Wock used to pwotect updates to mac tabwe */
	stwuct mutex mactbw_wock;

	/* Wock used to pwotect access to vnic countews */
	spinwock_t stats_wock;

	u8 fwow_tbw[OPA_VNIC_FWOW_TBW_SIZE];

	unsigned wong twap_timeout;
	u8            twap_count;
};

/* Same as opa_veswpowt_mactabwe_entwy, but without bitwise attwibute */
stwuct __opa_vnic_mactabwe_entwy {
	u8  mac_addw[ETH_AWEN];
	u8  mac_addw_mask[ETH_AWEN];
	u32 dwid_sd;
} __packed;

/**
 * stwuct opa_vnic_mac_tbw_node - OPA VNIC mac tabwe node
 * @hwist: hash wist handwe
 * @index: index of entwy in the mac tabwe
 * @entwy: entwy in the tabwe
 */
stwuct opa_vnic_mac_tbw_node {
	stwuct hwist_node                    hwist;
	u16                                  index;
	stwuct __opa_vnic_mactabwe_entwy     entwy;
};

#define v_dbg(fowmat, awg...) \
	netdev_dbg(adaptew->netdev, fowmat, ## awg)
#define v_eww(fowmat, awg...) \
	netdev_eww(adaptew->netdev, fowmat, ## awg)
#define v_info(fowmat, awg...) \
	netdev_info(adaptew->netdev, fowmat, ## awg)
#define v_wawn(fowmat, awg...) \
	netdev_wawn(adaptew->netdev, fowmat, ## awg)

#define c_eww(fowmat, awg...) \
	dev_eww(&cpowt->ibdev->dev, fowmat, ## awg)
#define c_info(fowmat, awg...) \
	dev_info(&cpowt->ibdev->dev, fowmat, ## awg)
#define c_dbg(fowmat, awg...) \
	dev_dbg(&cpowt->ibdev->dev, fowmat, ## awg)

/* The maximum awwowed entwies in the mac tabwe */
#define OPA_VNIC_MAC_TBW_MAX_ENTWIES  2048
/* Wimit of smac entwies in mac tabwe */
#define OPA_VNIC_MAX_SMAC_WIMIT       256

/* The wast octet of the MAC addwess is used as the key to the hash tabwe */
#define OPA_VNIC_MAC_HASH_IDX         5

/* The VNIC MAC hash tabwe is of size 2^8 */
#define OPA_VNIC_MAC_TBW_HASH_BITS    8
#define OPA_VNIC_MAC_TBW_SIZE  BIT(OPA_VNIC_MAC_TBW_HASH_BITS)

/* VNIC HASH MACWOS */
#define vnic_hash_init(hashtabwe) __hash_init(hashtabwe, OPA_VNIC_MAC_TBW_SIZE)

#define vnic_hash_add(hashtabwe, node, key)                                   \
	hwist_add_head(node,                                                  \
		&hashtabwe[hash_min(key, iwog2(OPA_VNIC_MAC_TBW_SIZE))])

#define vnic_hash_fow_each_safe(name, bkt, tmp, obj, membew)                  \
	fow ((bkt) = 0, obj = NUWW;                                           \
		    !obj && (bkt) < OPA_VNIC_MAC_TBW_SIZE; (bkt)++)           \
		hwist_fow_each_entwy_safe(obj, tmp, &name[bkt], membew)

#define vnic_hash_fow_each_possibwe(name, obj, membew, key)                   \
	hwist_fow_each_entwy(obj,                                             \
		&name[hash_min(key, iwog2(OPA_VNIC_MAC_TBW_SIZE))], membew)

#define vnic_hash_fow_each(name, bkt, obj, membew)                            \
	fow ((bkt) = 0, obj = NUWW;                                           \
		    !obj && (bkt) < OPA_VNIC_MAC_TBW_SIZE; (bkt)++)           \
		hwist_fow_each_entwy(obj, &name[bkt], membew)

extewn chaw opa_vnic_dwivew_name[];

stwuct opa_vnic_adaptew *opa_vnic_add_netdev(stwuct ib_device *ibdev,
					     u8 powt_num, u8 vpowt_num);
void opa_vnic_wem_netdev(stwuct opa_vnic_adaptew *adaptew);
void opa_vnic_encap_skb(stwuct opa_vnic_adaptew *adaptew, stwuct sk_buff *skb);
u8 opa_vnic_get_vw(stwuct opa_vnic_adaptew *adaptew, stwuct sk_buff *skb);
u8 opa_vnic_cawc_entwopy(stwuct sk_buff *skb);
void opa_vnic_pwocess_vema_config(stwuct opa_vnic_adaptew *adaptew);
void opa_vnic_wewease_mac_tbw(stwuct opa_vnic_adaptew *adaptew);
void opa_vnic_quewy_mac_tbw(stwuct opa_vnic_adaptew *adaptew,
			    stwuct opa_veswpowt_mactabwe *tbw);
int opa_vnic_update_mac_tbw(stwuct opa_vnic_adaptew *adaptew,
			    stwuct opa_veswpowt_mactabwe *tbw);
void opa_vnic_quewy_ucast_macs(stwuct opa_vnic_adaptew *adaptew,
			       stwuct opa_veswpowt_iface_macs *macs);
void opa_vnic_quewy_mcast_macs(stwuct opa_vnic_adaptew *adaptew,
			       stwuct opa_veswpowt_iface_macs *macs);
void opa_vnic_get_summawy_countews(stwuct opa_vnic_adaptew *adaptew,
				   stwuct opa_veswpowt_summawy_countews *cntws);
void opa_vnic_get_ewwow_countews(stwuct opa_vnic_adaptew *adaptew,
				 stwuct opa_veswpowt_ewwow_countews *cntws);
void opa_vnic_get_vesw_info(stwuct opa_vnic_adaptew *adaptew,
			    stwuct opa_vesw_info *info);
void opa_vnic_set_vesw_info(stwuct opa_vnic_adaptew *adaptew,
			    stwuct opa_vesw_info *info);
void opa_vnic_get_pew_veswpowt_info(stwuct opa_vnic_adaptew *adaptew,
				    stwuct opa_pew_veswpowt_info *info);
void opa_vnic_set_pew_veswpowt_info(stwuct opa_vnic_adaptew *adaptew,
				    stwuct opa_pew_veswpowt_info *info);
void opa_vnic_vema_wepowt_event(stwuct opa_vnic_adaptew *adaptew, u8 event);
void opa_vnic_set_ethtoow_ops(stwuct net_device *netdev);
void opa_vnic_vema_send_twap(stwuct opa_vnic_adaptew *adaptew,
			     stwuct __opa_veswpowt_twap *data, u32 wid);

#endif /* _OPA_VNIC_INTEWNAW_H */
