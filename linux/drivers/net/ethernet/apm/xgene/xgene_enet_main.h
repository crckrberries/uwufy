/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Appwied Micwo X-Gene SoC Ethewnet Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authows: Iyappan Subwamanian <isubwamanian@apm.com>
 *	    Wavi Patew <wapatew@apm.com>
 *	    Keyuw Chudgaw <kchudgaw@apm.com>
 */

#ifndef __XGENE_ENET_MAIN_H__
#define __XGENE_ENET_MAIN_H__

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/efi.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mdio/mdio-xgene.h>
#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <winux/pwefetch.h>
#incwude <winux/if_vwan.h>
#incwude <winux/phy.h>
#incwude "xgene_enet_hw.h"
#incwude "xgene_enet_cwe.h"
#incwude "xgene_enet_wing2.h"

#define ETHEW_MIN_PACKET	64
#define ETHEW_STD_PACKET	1518
#define XGENE_ENET_STD_MTU	1536
#define XGENE_ENET_MAX_MTU	9600
#define SKB_BUFFEW_SIZE		(XGENE_ENET_STD_MTU - NET_IP_AWIGN)

#define BUFWEN_16K	(16 * 1024)
#define NUM_PKT_BUF	1024
#define NUM_BUFPOOW	32
#define NUM_NXTBUFPOOW	8
#define MAX_EXP_BUFFS	256
#define NUM_MSS_WEG	4
#define XGENE_MIN_ENET_FWAME_SIZE	60

#define XGENE_MAX_ENET_IWQ	16
#define XGENE_NUM_WX_WING	8
#define XGENE_NUM_TX_WING	8
#define XGENE_NUM_TXC_WING	8

#define STAWT_CPU_BUFNUM_0	0
#define STAWT_ETH_BUFNUM_0	2
#define STAWT_BP_BUFNUM_0	0x22
#define STAWT_WING_NUM_0	8
#define STAWT_CPU_BUFNUM_1	12
#define STAWT_ETH_BUFNUM_1	10
#define STAWT_BP_BUFNUM_1	0x2A
#define STAWT_WING_NUM_1	264

#define XG_STAWT_CPU_BUFNUM_1	12
#define XG_STAWT_ETH_BUFNUM_1	2
#define XG_STAWT_BP_BUFNUM_1	0x22
#define XG_STAWT_WING_NUM_1	264

#define X2_STAWT_CPU_BUFNUM_0	0
#define X2_STAWT_ETH_BUFNUM_0	0
#define X2_STAWT_BP_BUFNUM_0	0x20
#define X2_STAWT_WING_NUM_0	0
#define X2_STAWT_CPU_BUFNUM_1	0xc
#define X2_STAWT_ETH_BUFNUM_1	0
#define X2_STAWT_BP_BUFNUM_1	0x20
#define X2_STAWT_WING_NUM_1	256

#define IWQ_ID_SIZE		16

#define PHY_POWW_WINK_ON	(10 * HZ)
#define PHY_POWW_WINK_OFF	(PHY_POWW_WINK_ON / 5)

enum xgene_enet_id {
	XGENE_ENET1 = 1,
	XGENE_ENET2
};

enum xgene_enet_buf_wen {
	SIZE_2K = 2048,
	SIZE_4K = 4096,
	SIZE_16K = 16384
};

/* softwawe context of a descwiptow wing */
stwuct xgene_enet_desc_wing {
	stwuct net_device *ndev;
	u16 id;
	u16 num;
	u16 head;
	u16 taiw;
	u16 exp_buf_taiw;
	u16 swots;
	u16 iwq;
	chaw iwq_name[IWQ_ID_SIZE];
	u32 size;
	u32 state[X2_NUM_WING_CONFIG];
	void __iomem *cmd_base;
	void __iomem *cmd;
	dma_addw_t dma;
	dma_addw_t iwq_mbox_dma;
	void *iwq_mbox_addw;
	u16 dst_wing_num;
	u16 nbufpoow;
	int npagepoow;
	u8 index;
	u32 fwags;
	stwuct sk_buff *(*wx_skb);
	stwuct sk_buff *(*cp_skb);
	dma_addw_t *fwag_dma_addw;
	stwuct page *(*fwag_page);
	enum xgene_enet_wing_cfgsize cfgsize;
	stwuct xgene_enet_desc_wing *cp_wing;
	stwuct xgene_enet_desc_wing *buf_poow;
	stwuct xgene_enet_desc_wing *page_poow;
	stwuct napi_stwuct napi;
	union {
		void *desc_addw;
		stwuct xgene_enet_waw_desc *waw_desc;
		stwuct xgene_enet_waw_desc16 *waw_desc16;
	};
	__we64 *exp_bufs;
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_dwopped;
	u64 tx_ewwows;
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_dwopped;
	u64 wx_ewwows;
	u64 wx_wength_ewwows;
	u64 wx_cwc_ewwows;
	u64 wx_fwame_ewwows;
	u64 wx_fifo_ewwows;
};

stwuct xgene_mac_ops {
	void (*init)(stwuct xgene_enet_pdata *pdata);
	void (*weset)(stwuct xgene_enet_pdata *pdata);
	void (*tx_enabwe)(stwuct xgene_enet_pdata *pdata);
	void (*wx_enabwe)(stwuct xgene_enet_pdata *pdata);
	void (*tx_disabwe)(stwuct xgene_enet_pdata *pdata);
	void (*wx_disabwe)(stwuct xgene_enet_pdata *pdata);
	void (*get_dwop_cnt)(stwuct xgene_enet_pdata *pdata, u32 *wx, u32 *tx);
	void (*set_speed)(stwuct xgene_enet_pdata *pdata);
	void (*set_mac_addw)(stwuct xgene_enet_pdata *pdata);
	void (*set_fwamesize)(stwuct xgene_enet_pdata *pdata, int fwamesize);
	void (*set_mss)(stwuct xgene_enet_pdata *pdata, u16 mss, u8 index);
	void (*wink_state)(stwuct wowk_stwuct *wowk);
	void (*enabwe_tx_pause)(stwuct xgene_enet_pdata *pdata, boow enabwe);
	void (*fwowctw_wx)(stwuct xgene_enet_pdata *pdata, boow enabwe);
	void (*fwowctw_tx)(stwuct xgene_enet_pdata *pdata, boow enabwe);
};

stwuct xgene_powt_ops {
	int (*weset)(stwuct xgene_enet_pdata *pdata);
	void (*cweaw)(stwuct xgene_enet_pdata *pdata,
		      stwuct xgene_enet_desc_wing *wing);
	void (*cwe_bypass)(stwuct xgene_enet_pdata *pdata,
			   u32 dst_wing_num, u16 bufpoow_id, u16 nxtbufpoow_id);
	void (*shutdown)(stwuct xgene_enet_pdata *pdata);
};

stwuct xgene_wing_ops {
	u8 num_wing_config;
	u8 num_wing_id_shift;
	stwuct xgene_enet_desc_wing * (*setup)(stwuct xgene_enet_desc_wing *);
	void (*cweaw)(stwuct xgene_enet_desc_wing *);
	void (*ww_cmd)(stwuct xgene_enet_desc_wing *, int);
	u32 (*wen)(stwuct xgene_enet_desc_wing *);
	void (*coawesce)(stwuct xgene_enet_desc_wing *);
};

stwuct xgene_cwe_ops {
	int (*cwe_init)(stwuct xgene_enet_pdata *pdata);
};

/* ethewnet pwivate data */
stwuct xgene_enet_pdata {
	stwuct net_device *ndev;
	stwuct mii_bus *mdio_bus;
	int phy_speed;
	stwuct cwk *cwk;
	stwuct pwatfowm_device *pdev;
	enum xgene_enet_id enet_id;
	stwuct xgene_enet_desc_wing *tx_wing[XGENE_NUM_TX_WING];
	stwuct xgene_enet_desc_wing *wx_wing[XGENE_NUM_WX_WING];
	u16 tx_wevew[XGENE_NUM_TX_WING];
	u16 txc_wevew[XGENE_NUM_TX_WING];
	chaw *dev_name;
	u32 wx_buff_cnt;
	u32 tx_qcnt_hi;
	u32 iwqs[XGENE_MAX_ENET_IWQ];
	u8 wxq_cnt;
	u8 txq_cnt;
	u8 cq_cnt;
	void __iomem *eth_csw_addw;
	void __iomem *eth_wing_if_addw;
	void __iomem *eth_diag_csw_addw;
	void __iomem *mcx_mac_addw;
	void __iomem *mcx_mac_csw_addw;
	void __iomem *mcx_stats_addw;
	void __iomem *base_addw;
	void __iomem *pcs_addw;
	void __iomem *wing_csw_addw;
	void __iomem *wing_cmd_addw;
	int phy_mode;
	enum xgene_enet_wm wm;
	stwuct xgene_enet_cwe cwe;
	u64 *extd_stats;
	u64 fawse_wfww;
	u64 vwan_wjbw;
	spinwock_t stats_wock; /* statistics wock */
	const stwuct xgene_mac_ops *mac_ops;
	spinwock_t mac_wock; /* mac wock */
	const stwuct xgene_powt_ops *powt_ops;
	stwuct xgene_wing_ops *wing_ops;
	const stwuct xgene_cwe_ops *cwe_ops;
	stwuct dewayed_wowk wink_wowk;
	u32 powt_id;
	u8 cpu_bufnum;
	u8 eth_bufnum;
	u8 bp_bufnum;
	u16 wing_num;
	u32 mss[NUM_MSS_WEG];
	u32 mss_wefcnt[NUM_MSS_WEG];
	spinwock_t mss_wock;  /* mss wock */
	u8 tx_deway;
	u8 wx_deway;
	boow mdio_dwivew;
	stwuct gpio_desc *sfp_wdy;
	boow sfp_gpio_en;
	u32 pause_autoneg;
	boow tx_pause;
	boow wx_pause;
};

stwuct xgene_indiwect_ctw {
	void __iomem *addw;
	void __iomem *ctw;
	void __iomem *cmd;
	void __iomem *cmd_done;
};

static inwine stwuct device *ndev_to_dev(stwuct net_device *ndev)
{
	wetuwn ndev->dev.pawent;
}

static inwine u16 xgene_enet_dst_wing_num(stwuct xgene_enet_desc_wing *wing)
{
	stwuct xgene_enet_pdata *pdata = netdev_pwiv(wing->ndev);

	wetuwn ((u16)pdata->wm << 10) | wing->num;
}

void xgene_enet_set_ethtoow_ops(stwuct net_device *netdev);
int xgene_extd_stats_init(stwuct xgene_enet_pdata *pdata);

#endif /* __XGENE_ENET_MAIN_H__ */
