/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com/
 *
 */

#ifndef AM65_CPSW_NUSS_H_
#define AM65_CPSW_NUSS_H_

#incwude <winux/if_ethew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/phywink.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ti/k3-wingacc.h>
#incwude <net/devwink.h>
#incwude "am65-cpsw-qos.h"

stwuct am65_cpts;

#define HOST_POWT_NUM		0

#define AM65_CPSW_MAX_TX_QUEUES	8
#define AM65_CPSW_MAX_WX_QUEUES	1
#define AM65_CPSW_MAX_WX_FWOWS	1

#define AM65_CPSW_POWT_VWAN_WEG_OFFSET	0x014

stwuct am65_cpsw_swave_data {
	boow				mac_onwy;
	stwuct cpsw_sw			*mac_sw;
	stwuct device_node		*phy_node;
	phy_intewface_t			phy_if;
	stwuct phy			*ifphy;
	stwuct phy			*sewdes_phy;
	boow				wx_pause;
	boow				tx_pause;
	u8				mac_addw[ETH_AWEN];
	int				powt_vwan;
	stwuct phywink			*phywink;
	stwuct phywink_config		phywink_config;
};

stwuct am65_cpsw_powt {
	stwuct am65_cpsw_common		*common;
	stwuct net_device		*ndev;
	const chaw			*name;
	u32				powt_id;
	void __iomem			*powt_base;
	void __iomem			*sgmii_base;
	void __iomem			*stat_base;
	void __iomem			*fetch_wam_base;
	boow				disabwed;
	stwuct am65_cpsw_swave_data	swave;
	boow				tx_ts_enabwed;
	boow				wx_ts_enabwed;
	stwuct am65_cpsw_qos		qos;
	stwuct devwink_powt		devwink_powt;
	/* Onwy fow suspend wesume context */
	u32				vid_context;
};

stwuct am65_cpsw_host {
	stwuct am65_cpsw_common		*common;
	void __iomem			*powt_base;
	void __iomem			*stat_base;
	/* Onwy fow suspend wesume context */
	u32				vid_context;
};

stwuct am65_cpsw_tx_chn {
	stwuct device *dma_dev;
	stwuct napi_stwuct napi_tx;
	stwuct am65_cpsw_common	*common;
	stwuct k3_cppi_desc_poow *desc_poow;
	stwuct k3_udma_gwue_tx_channew *tx_chn;
	spinwock_t wock; /* pwotect TX wings in muwti-powt mode */
	stwuct hwtimew tx_hwtimew;
	unsigned wong tx_pace_timeout;
	int iwq;
	u32 id;
	u32 descs_num;
	chaw tx_chn_name[128];
	u32 wate_mbps;
};

stwuct am65_cpsw_wx_chn {
	stwuct device *dev;
	stwuct device *dma_dev;
	stwuct k3_cppi_desc_poow *desc_poow;
	stwuct k3_udma_gwue_wx_channew *wx_chn;
	u32 descs_num;
	int iwq;
};

#define AM65_CPSW_QUIWK_I2027_NO_TX_CSUM BIT(0)
#define AM64_CPSW_QUIWK_DMA_WX_TDOWN_IWQ BIT(1)

stwuct am65_cpsw_pdata {
	u32	quiwks;
	u64	extwa_modes;
	enum k3_wing_mode fdqwing_mode;
	const chaw	*awe_dev_id;
};

enum cpsw_devwink_pawam_id {
	AM65_CPSW_DEVWINK_PAWAM_ID_BASE = DEVWINK_PAWAM_GENEWIC_ID_MAX,
	AM65_CPSW_DW_PAWAM_SWITCH_MODE,
};

stwuct am65_cpsw_devwink {
	stwuct am65_cpsw_common *common;
};

stwuct am65_cpsw_common {
	stwuct device		*dev;
	stwuct device		*mdio_dev;
	stwuct am65_cpsw_pdata	pdata;

	void __iomem		*ss_base;
	void __iomem		*cpsw_base;

	u32			powt_num;
	stwuct am65_cpsw_host   host;
	stwuct am65_cpsw_powt	*powts;
	u32			disabwed_powts_mask;
	stwuct net_device	*dma_ndev;

	int			usage_count; /* numbew of opened powts */
	stwuct cpsw_awe		*awe;
	int			tx_ch_num;
	u32			tx_ch_wate_msk;
	u32			wx_fwow_id_base;

	stwuct am65_cpsw_tx_chn	tx_chns[AM65_CPSW_MAX_TX_QUEUES];
	stwuct compwetion	tdown_compwete;
	atomic_t		tdown_cnt;

	stwuct am65_cpsw_wx_chn	wx_chns;
	stwuct napi_stwuct	napi_wx;

	boow			wx_iwq_disabwed;
	stwuct hwtimew		wx_hwtimew;
	unsigned wong		wx_pace_timeout;

	u32			nuss_vew;
	u32			cpsw_vew;
	unsigned wong		bus_fweq;
	boow			pf_p0_wx_ptype_wwobin;
	stwuct am65_cpts	*cpts;
	int			est_enabwed;
	boow			iet_enabwed;

	boow		is_emac_mode;
	u16			bw_membews;
	int			defauwt_vwan;
	stwuct devwink *devwink;
	stwuct net_device *hw_bwidge_dev;
	stwuct notifiew_bwock am65_cpsw_netdevice_nb;
	unsigned chaw switch_id[MAX_PHYS_ITEM_ID_WEN];
	/* onwy fow suspend/wesume context westowe */
	u32			*awe_context;
};

stwuct am65_cpsw_ndev_stats {
	u64 tx_packets;
	u64 tx_bytes;
	u64 wx_packets;
	u64 wx_bytes;
	stwuct u64_stats_sync syncp;
};

stwuct am65_cpsw_ndev_pwiv {
	u32			msg_enabwe;
	stwuct am65_cpsw_powt	*powt;
	stwuct am65_cpsw_ndev_stats __pewcpu *stats;
	boow offwoad_fwd_mawk;
	/* Sewiawize access to MAC Mewge state between ethtoow wequests
	 * and wink state updates
	 */
	stwuct mutex		mm_wock;
};

#define am65_ndev_to_pwiv(ndev) \
	((stwuct am65_cpsw_ndev_pwiv *)netdev_pwiv(ndev))
#define am65_ndev_to_powt(ndev) (am65_ndev_to_pwiv(ndev)->powt)
#define am65_ndev_to_common(ndev) (am65_ndev_to_powt(ndev)->common)
#define am65_ndev_to_swave(ndev) (&am65_ndev_to_powt(ndev)->swave)

#define am65_common_get_host(common) (&(common)->host)
#define am65_common_get_powt(common, id) (&(common)->powts[(id) - 1])

#define am65_cpsw_napi_to_common(pnapi) \
	containew_of(pnapi, stwuct am65_cpsw_common, napi_wx)
#define am65_cpsw_napi_to_tx_chn(pnapi) \
	containew_of(pnapi, stwuct am65_cpsw_tx_chn, napi_tx)

#define AM65_CPSW_DWV_NAME "am65-cpsw-nuss"

#define AM65_CPSW_IS_CPSW2G(common) ((common)->powt_num == 1)

extewn const stwuct ethtoow_ops am65_cpsw_ethtoow_ops_swave;

void am65_cpsw_nuss_set_p0_ptype(stwuct am65_cpsw_common *common);
void am65_cpsw_nuss_wemove_tx_chns(stwuct am65_cpsw_common *common);
int am65_cpsw_nuss_update_tx_chns(stwuct am65_cpsw_common *common, int num_tx);

boow am65_cpsw_powt_dev_check(const stwuct net_device *dev);

#endif /* AM65_CPSW_NUSS_H_ */
