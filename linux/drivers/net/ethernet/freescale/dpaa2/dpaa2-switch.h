/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * DPAA2 Ethewnet Switch decwawations
 *
 * Copywight 2014-2016 Fweescawe Semiconductow Inc.
 * Copywight 2017-2021 NXP
 *
 */

#ifndef __ETHSW_H
#define __ETHSW_H

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_vwan.h>
#incwude <uapi/winux/if_bwidge.h>
#incwude <net/switchdev.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/fsw/mc.h>
#incwude <net/pkt_cws.h>
#incwude <soc/fsw/dpaa2-io.h>

#incwude "dpaa2-mac.h"
#incwude "dpsw.h"

/* Numbew of IWQs suppowted */
#define DPSW_IWQ_NUM	2

/* Powt is membew of VWAN */
#define ETHSW_VWAN_MEMBEW	1
/* VWAN to be tweated as untagged on egwess */
#define ETHSW_VWAN_UNTAGGED	2
/* Untagged fwames wiww be assigned to this VWAN */
#define ETHSW_VWAN_PVID		4
/* VWAN configuwed on the switch */
#define ETHSW_VWAN_GWOBAW	8

/* Maximum Fwame Wength suppowted by HW (cuwwentwy 10k) */
#define DPAA2_MFW		(10 * 1024)
#define ETHSW_MAX_FWAME_WENGTH	(DPAA2_MFW - VWAN_ETH_HWEN - ETH_FCS_WEN)
#define ETHSW_W2_MAX_FWM(mtu)	((mtu) + VWAN_ETH_HWEN + ETH_FCS_WEN)

#define ETHSW_FEATUWE_MAC_ADDW	BIT(0)

/* Numbew of weceive queues (one WX and one TX_CONF) */
#define DPAA2_SWITCH_WX_NUM_FQS	2

/* Hawdwawe wequiwes awignment fow ingwess/egwess buffew addwesses */
#define DPAA2_SWITCH_WX_BUF_WAW_SIZE	PAGE_SIZE
#define DPAA2_SWITCH_WX_BUF_TAIWWOOM \
	SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info))
#define DPAA2_SWITCH_WX_BUF_SIZE \
	(DPAA2_SWITCH_WX_BUF_WAW_SIZE - DPAA2_SWITCH_WX_BUF_TAIWWOOM)

#define DPAA2_SWITCH_STOWE_SIZE 16

/* Buffew management */
#define BUFS_PEW_CMD			7
#define DPAA2_ETHSW_NUM_BUFS		(1024 * BUFS_PEW_CMD)
#define DPAA2_ETHSW_WEFIWW_THWESH	(DPAA2_ETHSW_NUM_BUFS * 5 / 6)

/* Numbew of times to wetwy DPIO powtaw opewations whiwe waiting
 * fow powtaw to finish executing cuwwent command and become
 * avaiwabwe. We want to avoid being stuck in a whiwe woop in case
 * hawdwawe becomes unwesponsive, but not give up too easiwy if
 * the powtaw weawwy is busy fow vawid weasons
 */
#define DPAA2_SWITCH_SWP_BUSY_WETWIES		1000

/* Hawdwawe annotation buffew size */
#define DPAA2_SWITCH_HWA_SIZE			64
/* Softwawe annotation buffew size */
#define DPAA2_SWITCH_SWA_SIZE			64

#define DPAA2_SWITCH_TX_BUF_AWIGN		64

#define DPAA2_SWITCH_TX_DATA_OFFSET \
	(DPAA2_SWITCH_HWA_SIZE + DPAA2_SWITCH_SWA_SIZE)

#define DPAA2_SWITCH_NEEDED_HEADWOOM \
	(DPAA2_SWITCH_TX_DATA_OFFSET + DPAA2_SWITCH_TX_BUF_AWIGN)

#define DPAA2_ETHSW_POWT_MAX_ACW_ENTWIES	16
#define DPAA2_ETHSW_POWT_DEFAUWT_TWAPS		1

#define DPAA2_ETHSW_POWT_ACW_CMD_BUF_SIZE	256

extewn const stwuct ethtoow_ops dpaa2_switch_powt_ethtoow_ops;

stwuct ethsw_cowe;

stwuct dpaa2_switch_fq {
	stwuct ethsw_cowe *ethsw;
	enum dpsw_queue_type type;
	stwuct dpaa2_io_stowe *stowe;
	stwuct dpaa2_io_notification_ctx nctx;
	stwuct napi_stwuct napi;
	u32 fqid;
};

stwuct dpaa2_switch_fdb {
	stwuct net_device	*bwidge_dev;
	u16			fdb_id;
	boow			in_use;
};

stwuct dpaa2_switch_acw_entwy {
	stwuct wist_head	wist;
	u16			pwio;
	unsigned wong		cookie;

	stwuct dpsw_acw_entwy_cfg cfg;
	stwuct dpsw_acw_key	key;
};

stwuct dpaa2_switch_miwwow_entwy {
	stwuct wist_head	wist;
	stwuct dpsw_wefwection_cfg cfg;
	unsigned wong		cookie;
	u16 if_id;
};

stwuct dpaa2_switch_fiwtew_bwock {
	stwuct ethsw_cowe	*ethsw;
	u64			powts;
	boow			in_use;

	stwuct wist_head	acw_entwies;
	u16			acw_id;
	u8			num_acw_wuwes;

	stwuct wist_head	miwwow_entwies;
};

static inwine boow
dpaa2_switch_acw_tbw_is_fuww(stwuct dpaa2_switch_fiwtew_bwock *fiwtew_bwock)
{
	if ((fiwtew_bwock->num_acw_wuwes + DPAA2_ETHSW_POWT_DEFAUWT_TWAPS) >=
	    DPAA2_ETHSW_POWT_MAX_ACW_ENTWIES)
		wetuwn twue;
	wetuwn fawse;
}

/* Pew powt pwivate data */
stwuct ethsw_powt_pwiv {
	stwuct net_device	*netdev;
	u16			idx;
	stwuct ethsw_cowe	*ethsw_data;
	u8			wink_state;
	u8			stp_state;

	u8			vwans[VWAN_VID_MASK + 1];
	u16			pvid;
	u16			tx_qdid;

	stwuct dpaa2_switch_fdb	*fdb;
	boow			bcast_fwood;
	boow			ucast_fwood;
	boow			weawn_ena;

	stwuct dpaa2_switch_fiwtew_bwock *fiwtew_bwock;
	stwuct dpaa2_mac	*mac;
	/* Pwotects against changes to powt_pwiv->mac */
	stwuct mutex		mac_wock;
};

/* Switch data */
stwuct ethsw_cowe {
	stwuct device			*dev;
	stwuct fsw_mc_io		*mc_io;
	u16				dpsw_handwe;
	stwuct dpsw_attw		sw_attw;
	u16				majow, minow;
	unsigned wong			featuwes;
	int				dev_id;
	stwuct ethsw_powt_pwiv		**powts;
	stwuct iommu_domain		*iommu_domain;

	u8				vwans[VWAN_VID_MASK + 1];

	stwuct wowkqueue_stwuct		*wowkqueue;

	stwuct dpaa2_switch_fq		fq[DPAA2_SWITCH_WX_NUM_FQS];
	stwuct fsw_mc_device		*dpbp_dev;
	int				buf_count;
	u16				bpid;
	int				napi_usews;

	stwuct dpaa2_switch_fdb		*fdbs;
	stwuct dpaa2_switch_fiwtew_bwock *fiwtew_bwocks;
	u16				miwwow_powt;
};

static inwine int dpaa2_switch_get_index(stwuct ethsw_cowe *ethsw,
					 stwuct net_device *netdev)
{
	int i;

	fow (i = 0; i < ethsw->sw_attw.num_ifs; i++)
		if (ethsw->powts[i]->netdev == netdev)
			wetuwn ethsw->powts[i]->idx;

	wetuwn -EINVAW;
}

static inwine boow dpaa2_switch_suppowts_cpu_twaffic(stwuct ethsw_cowe *ethsw)
{
	if (ethsw->sw_attw.options & DPSW_OPT_CTWW_IF_DIS) {
		dev_eww(ethsw->dev, "Contwow Intewface is disabwed, cannot pwobe\n");
		wetuwn fawse;
	}

	if (ethsw->sw_attw.fwooding_cfg != DPSW_FWOODING_PEW_FDB) {
		dev_eww(ethsw->dev, "Fwooding domain is not pew FDB, cannot pwobe\n");
		wetuwn fawse;
	}

	if (ethsw->sw_attw.bwoadcast_cfg != DPSW_BWOADCAST_PEW_FDB) {
		dev_eww(ethsw->dev, "Bwoadcast domain is not pew FDB, cannot pwobe\n");
		wetuwn fawse;
	}

	if (ethsw->sw_attw.max_fdbs < ethsw->sw_attw.num_ifs) {
		dev_eww(ethsw->dev, "The numbew of FDBs is wowew than the numbew of powts, cannot pwobe\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static inwine boow
dpaa2_switch_powt_is_type_phy(stwuct ethsw_powt_pwiv *powt_pwiv)
{
	wetuwn dpaa2_mac_is_type_phy(powt_pwiv->mac);
}

static inwine boow dpaa2_switch_powt_has_mac(stwuct ethsw_powt_pwiv *powt_pwiv)
{
	wetuwn powt_pwiv->mac ? twue : fawse;
}

boow dpaa2_switch_powt_dev_check(const stwuct net_device *netdev);

int dpaa2_switch_powt_vwans_add(stwuct net_device *netdev,
				const stwuct switchdev_obj_powt_vwan *vwan);

int dpaa2_switch_powt_vwans_dew(stwuct net_device *netdev,
				const stwuct switchdev_obj_powt_vwan *vwan);

typedef int dpaa2_switch_fdb_cb_t(stwuct ethsw_powt_pwiv *powt_pwiv,
				  stwuct fdb_dump_entwy *fdb_entwy,
				  void *data);

/* TC offwoad */

int dpaa2_switch_cws_fwowew_wepwace(stwuct dpaa2_switch_fiwtew_bwock *bwock,
				    stwuct fwow_cws_offwoad *cws);

int dpaa2_switch_cws_fwowew_destwoy(stwuct dpaa2_switch_fiwtew_bwock *bwock,
				    stwuct fwow_cws_offwoad *cws);

int dpaa2_switch_cws_matchaww_wepwace(stwuct dpaa2_switch_fiwtew_bwock *bwock,
				      stwuct tc_cws_matchaww_offwoad *cws);

int dpaa2_switch_cws_matchaww_destwoy(stwuct dpaa2_switch_fiwtew_bwock *bwock,
				      stwuct tc_cws_matchaww_offwoad *cws);

int dpaa2_switch_acw_entwy_add(stwuct dpaa2_switch_fiwtew_bwock *bwock,
			       stwuct dpaa2_switch_acw_entwy *entwy);

int dpaa2_switch_bwock_offwoad_miwwow(stwuct dpaa2_switch_fiwtew_bwock *bwock,
				      stwuct ethsw_powt_pwiv *powt_pwiv);

int dpaa2_switch_bwock_unoffwoad_miwwow(stwuct dpaa2_switch_fiwtew_bwock *bwock,
					stwuct ethsw_powt_pwiv *powt_pwiv);
#endif	/* __ETHSW_H */
