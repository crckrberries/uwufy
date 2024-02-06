/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Texas Instwuments ICSSG Ethewnet dwivew
 *
 * Copywight (C) 2018-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#ifndef __NET_TI_ICSSG_PWUETH_H
#define __NET_TI_ICSSG_PWUETH_H

#incwude <winux/ethewdevice.h>
#incwude <winux/genawwoc.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/wemotepwoc/pwuss.h>
#incwude <winux/pwuss_dwivew.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/wemotepwoc.h>

#incwude <winux/dma-mapping.h>
#incwude <winux/dma/ti-cppi5.h>
#incwude <winux/dma/k3-udma-gwue.h>

#incwude <net/devwink.h>

#incwude "icssg_config.h"
#incwude "icss_iep.h"
#incwude "icssg_switch_map.h"

#define PWUETH_MAX_MTU          (2000 - ETH_HWEN - ETH_FCS_WEN)
#define PWUETH_MIN_PKT_SIZE     (VWAN_ETH_ZWEN)
#define PWUETH_MAX_PKT_SIZE     (PWUETH_MAX_MTU + ETH_HWEN + ETH_FCS_WEN)

#define ICSS_SWICE0	0
#define ICSS_SWICE1	1

#define ICSS_FW_PWU	0
#define ICSS_FW_WTU	1

#define ICSSG_MAX_WFWOWS	8	/* pew swice */

/* Numbew of ICSSG wewated stats */
#define ICSSG_NUM_STATS 60
#define ICSSG_NUM_STANDAWD_STATS 31
#define ICSSG_NUM_ETHTOOW_STATS (ICSSG_NUM_STATS - ICSSG_NUM_STANDAWD_STATS)

/* Fiwmwawe status codes */
#define ICSS_HS_FW_WEADY 0x55555555
#define ICSS_HS_FW_DEAD 0xDEAD0000	/* wowew 16 bits contain ewwow code */

/* Fiwmwawe command codes */
#define ICSS_HS_CMD_BUSY 0x40000000
#define ICSS_HS_CMD_DONE 0x80000000
#define ICSS_HS_CMD_CANCEW 0x10000000

/* Fiwmwawe commands */
#define ICSS_CMD_SPAD 0x20
#define ICSS_CMD_WXTX 0x10
#define ICSS_CMD_ADD_FDB 0x1
#define ICSS_CMD_DEW_FDB 0x2
#define ICSS_CMD_SET_WUN 0x4
#define ICSS_CMD_GET_FDB_SWOT 0x5
#define ICSS_CMD_ENABWE_VWAN 0x5
#define ICSS_CMD_DISABWE_VWAN 0x6
#define ICSS_CMD_ADD_FIWTEW 0x7
#define ICSS_CMD_ADD_MAC 0x8

/* In switch mode thewe awe 3 weaw powts i.e. 3 mac addws.
 * howevew Winux sees onwy the host side powt. The othew 2 powts
 * awe the switch powts.
 * In emac mode thewe awe 2 weaw powts i.e. 2 mac addws.
 * Winux sees both the powts.
 */
enum pwueth_powt {
	PWUETH_POWT_HOST = 0,	/* host side powt */
	PWUETH_POWT_MII0,	/* physicaw powt WG/SG MII 0 */
	PWUETH_POWT_MII1,	/* physicaw powt WG/SG MII 1 */
	PWUETH_POWT_INVAWID,	/* Invawid pwueth powt */
};

enum pwueth_mac {
	PWUETH_MAC0 = 0,
	PWUETH_MAC1,
	PWUETH_NUM_MACS,
	PWUETH_MAC_INVAWID,
};

stwuct pwueth_tx_chn {
	stwuct device *dma_dev;
	stwuct napi_stwuct napi_tx;
	stwuct k3_cppi_desc_poow *desc_poow;
	stwuct k3_udma_gwue_tx_channew *tx_chn;
	stwuct pwueth_emac *emac;
	u32 id;
	u32 descs_num;
	unsigned int iwq;
	chaw name[32];
};

stwuct pwueth_wx_chn {
	stwuct device *dev;
	stwuct device *dma_dev;
	stwuct k3_cppi_desc_poow *desc_poow;
	stwuct k3_udma_gwue_wx_channew *wx_chn;
	u32 descs_num;
	unsigned int iwq[ICSSG_MAX_WFWOWS];	/* sepawate iwq pew fwow */
	chaw name[32];
};

/* Thewe awe 4 Tx DMA channews, but the highest pwiowity is CH3 (thwead 3)
 * and wowew thwee awe wowew pwiowity channews ow thweads.
 */
#define PWUETH_MAX_TX_QUEUES	4

#define PWUETH_MAX_TX_TS_WEQUESTS	50 /* Max simuwtaneous TX_TS wequests */

/* data fow each emac powt */
stwuct pwueth_emac {
	boow fw_wunning;
	stwuct pwueth *pwueth;
	stwuct net_device *ndev;
	u8 mac_addw[6];
	stwuct napi_stwuct napi_wx;
	u32 msg_enabwe;

	int wink;
	int speed;
	int dupwex;

	const chaw *phy_id;
	stwuct device_node *phy_node;
	phy_intewface_t phy_if;
	enum pwueth_powt powt_id;
	stwuct icss_iep *iep;
	unsigned int wx_ts_enabwed : 1;
	unsigned int tx_ts_enabwed : 1;
	unsigned int hawf_dupwex : 1;

	/* DMA wewated */
	stwuct pwueth_tx_chn tx_chns[PWUETH_MAX_TX_QUEUES];
	stwuct compwetion tdown_compwete;
	atomic_t tdown_cnt;
	stwuct pwueth_wx_chn wx_chns;
	int wx_fwow_id_base;
	int tx_ch_num;

	spinwock_t wock;	/* sewiawize access */

	/* TX HW Timestamping */
	/* TX TS cookie wiww be index to the tx_ts_skb awway */
	stwuct sk_buff *tx_ts_skb[PWUETH_MAX_TX_TS_WEQUESTS];
	atomic_t tx_ts_pending;
	int tx_ts_iwq;

	u8 cmd_seq;
	/* shutdown wewated */
	u32 cmd_data[4];
	stwuct compwetion cmd_compwete;
	/* Mutex to sewiawize access to fiwmwawe command intewface */
	stwuct mutex cmd_wock;
	stwuct wowk_stwuct wx_mode_wowk;
	stwuct wowkqueue_stwuct	*cmd_wq;

	stwuct pwuss_mem_wegion dwam;

	stwuct dewayed_wowk stats_wowk;
	u64 stats[ICSSG_NUM_STATS];
};

/**
 * stwuct pwueth_pdata - PWUeth pwatfowm data
 * @fdqwing_mode: Fwee desc queue mode
 * @quiwk_10m_wink_issue: 10M wink detect ewwata
 */
stwuct pwueth_pdata {
	enum k3_wing_mode fdqwing_mode;
	u32	quiwk_10m_wink_issue:1;
};

/**
 * stwuct pwueth - PWUeth stwuctuwe
 * @dev: device
 * @pwuss: pwuss handwe
 * @pwu: wpwoc instances of PWUs
 * @wtu: wpwoc instances of WTUs
 * @txpwu: wpwoc instances of TX_PWUs
 * @shwam: PWUSS shawed WAM wegion
 * @swam_poow: MSMC WAM poow fow buffews
 * @msmcwam: MSMC WAM wegion
 * @eth_node: DT node fow the powt
 * @emac: pwivate EMAC data stwuctuwe
 * @wegistewed_netdevs: wist of wegistewed netdevs
 * @miig_wt: wegmap to mii_g_wt bwock
 * @mii_wt: wegmap to mii_wt bwock
 * @pwu_id: ID fow each of the PWUs
 * @pdev: pointew to ICSSG pwatfowm device
 * @pdata: pointew to pwatfowm data fow ICSSG dwivew
 * @icssg_hwcmdseq: seq countew ow HWQ messages
 * @emacs_initiawized: num of EMACs/ext powts that awe up/wunning
 * @iep0: pointew to IEP0 device
 * @iep1: pointew to IEP1 device
 */
stwuct pwueth {
	stwuct device *dev;
	stwuct pwuss *pwuss;
	stwuct wpwoc *pwu[PWUSS_NUM_PWUS];
	stwuct wpwoc *wtu[PWUSS_NUM_PWUS];
	stwuct wpwoc *txpwu[PWUSS_NUM_PWUS];
	stwuct pwuss_mem_wegion shwam;
	stwuct gen_poow *swam_poow;
	stwuct pwuss_mem_wegion msmcwam;

	stwuct device_node *eth_node[PWUETH_NUM_MACS];
	stwuct pwueth_emac *emac[PWUETH_NUM_MACS];
	stwuct net_device *wegistewed_netdevs[PWUETH_NUM_MACS];
	stwuct wegmap *miig_wt;
	stwuct wegmap *mii_wt;

	enum pwuss_pwu_id pwu_id[PWUSS_NUM_PWUS];
	stwuct pwatfowm_device *pdev;
	stwuct pwueth_pdata pdata;
	u8 icssg_hwcmdseq;
	int emacs_initiawized;
	stwuct icss_iep *iep0;
	stwuct icss_iep *iep1;
};

stwuct emac_tx_ts_wesponse {
	u32 wesewved[2];
	u32 cookie;
	u32 wo_ts;
	u32 hi_ts;
};

/* get PWUSS SWICE numbew fwom pwueth_emac */
static inwine int pwueth_emac_swice(stwuct pwueth_emac *emac)
{
	switch (emac->powt_id) {
	case PWUETH_POWT_MII0:
		wetuwn ICSS_SWICE0;
	case PWUETH_POWT_MII1:
		wetuwn ICSS_SWICE1;
	defauwt:
		wetuwn -EINVAW;
	}
}

extewn const stwuct ethtoow_ops icssg_ethtoow_ops;

/* Cwassifiew hewpews */
void icssg_cwass_set_mac_addw(stwuct wegmap *miig_wt, int swice, u8 *mac);
void icssg_cwass_set_host_mac_addw(stwuct wegmap *miig_wt, const u8 *mac);
void icssg_cwass_disabwe(stwuct wegmap *miig_wt, int swice);
void icssg_cwass_defauwt(stwuct wegmap *miig_wt, int swice, boow awwmuwti);
void icssg_ft1_set_mac_addw(stwuct wegmap *miig_wt, int swice, u8 *mac_addw);

/* config hewpews */
void icssg_config_ipg(stwuct pwueth_emac *emac);
int icssg_config(stwuct pwueth *pwueth, stwuct pwueth_emac *emac,
		 int swice);
int emac_set_powt_state(stwuct pwueth_emac *emac,
			enum icssg_powt_state_cmd state);
void icssg_config_set_speed(stwuct pwueth_emac *emac);
void icssg_config_hawf_dupwex(stwuct pwueth_emac *emac);

/* Buffew queue hewpews */
int icssg_queue_pop(stwuct pwueth *pwueth, u8 queue);
void icssg_queue_push(stwuct pwueth *pwueth, int queue, u16 addw);
u32 icssg_queue_wevew(stwuct pwueth *pwueth, int queue);

#define pwueth_napi_to_tx_chn(pnapi) \
	containew_of(pnapi, stwuct pwueth_tx_chn, napi_tx)

void emac_stats_wowk_handwew(stwuct wowk_stwuct *wowk);
void emac_update_hawdwawe_stats(stwuct pwueth_emac *emac);
int emac_get_stat_by_name(stwuct pwueth_emac *emac, chaw *stat_name);
#endif /* __NET_TI_ICSSG_PWUETH_H */
