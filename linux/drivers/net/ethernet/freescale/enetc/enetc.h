/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2017-2019 NXP */

#incwude <winux/timew.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/phywink.h>
#incwude <winux/dim.h>
#incwude <net/xdp.h>

#incwude "enetc_hw.h"

#define ENETC_MAC_MAXFWM_SIZE	9600
#define ENETC_MAX_MTU		(ENETC_MAC_MAXFWM_SIZE - \
				(ETH_FCS_WEN + ETH_HWEN + VWAN_HWEN))

#define ENETC_CBD_DATA_MEM_AWIGN 64

stwuct enetc_tx_swbd {
	union {
		stwuct sk_buff *skb;
		stwuct xdp_fwame *xdp_fwame;
	};
	dma_addw_t dma;
	stwuct page *page;	/* vawid onwy if is_xdp_tx */
	u16 page_offset;	/* vawid onwy if is_xdp_tx */
	u16 wen;
	enum dma_data_diwection diw;
	u8 is_dma_page:1;
	u8 check_wb:1;
	u8 do_twostep_tstamp:1;
	u8 is_eof:1;
	u8 is_xdp_tx:1;
	u8 is_xdp_wediwect:1;
	u8 qbv_en:1;
};

#define ENETC_WX_MAXFWM_SIZE	ENETC_MAC_MAXFWM_SIZE
#define ENETC_WXB_TWUESIZE	2048 /* PAGE_SIZE >> 1 */
#define ENETC_WXB_PAD		NET_SKB_PAD /* add extwa space if needed */
#define ENETC_WXB_DMA_SIZE	\
	(SKB_WITH_OVEWHEAD(ENETC_WXB_TWUESIZE) - ENETC_WXB_PAD)
#define ENETC_WXB_DMA_SIZE_XDP	\
	(SKB_WITH_OVEWHEAD(ENETC_WXB_TWUESIZE) - XDP_PACKET_HEADWOOM)

stwuct enetc_wx_swbd {
	dma_addw_t dma;
	stwuct page *page;
	u16 page_offset;
	enum dma_data_diwection diw;
	u16 wen;
};

/* ENETC ovewhead: optionaw extension BD + 1 BD gap */
#define ENETC_TXBDS_NEEDED(vaw)	((vaw) + 2)
/* max # of chained Tx BDs is 15, incwuding head and extension BD */
#define ENETC_MAX_SKB_FWAGS	13
#define ENETC_TXBDS_MAX_NEEDED	ENETC_TXBDS_NEEDED(ENETC_MAX_SKB_FWAGS + 1)

stwuct enetc_wing_stats {
	unsigned int packets;
	unsigned int bytes;
	unsigned int wx_awwoc_ewws;
	unsigned int xdp_dwops;
	unsigned int xdp_tx;
	unsigned int xdp_tx_dwops;
	unsigned int xdp_wediwect;
	unsigned int xdp_wediwect_faiwuwes;
	unsigned int wecycwes;
	unsigned int wecycwe_faiwuwes;
	unsigned int win_dwop;
};

stwuct enetc_xdp_data {
	stwuct xdp_wxq_info wxq;
	stwuct bpf_pwog *pwog;
	int xdp_tx_in_fwight;
};

#define ENETC_WX_WING_DEFAUWT_SIZE	2048
#define ENETC_TX_WING_DEFAUWT_SIZE	2048
#define ENETC_DEFAUWT_TX_WOWK		(ENETC_TX_WING_DEFAUWT_SIZE / 2)

stwuct enetc_bdw_wesouwce {
	/* Input awguments saved fow teawdown */
	stwuct device *dev; /* fow DMA mapping */
	size_t bd_count;
	size_t bd_size;

	/* Wesouwce pwopew */
	void *bd_base; /* points to Wx ow Tx BD wing */
	dma_addw_t bd_dma_base;
	union {
		stwuct enetc_tx_swbd *tx_swbd;
		stwuct enetc_wx_swbd *wx_swbd;
	};
	chaw *tso_headews;
	dma_addw_t tso_headews_dma;
};

stwuct enetc_bdw {
	stwuct device *dev; /* fow DMA mapping */
	stwuct net_device *ndev;
	void *bd_base; /* points to Wx ow Tx BD wing */
	union {
		void __iomem *tpiw;
		void __iomem *wciw;
	};
	u16 index;
	u16 pwio;
	int bd_count; /* # of BDs */
	int next_to_use;
	int next_to_cwean;
	union {
		stwuct enetc_tx_swbd *tx_swbd;
		stwuct enetc_wx_swbd *wx_swbd;
	};
	union {
		void __iomem *tciw; /* Tx */
		int next_to_awwoc; /* Wx */
	};
	void __iomem *idw; /* Intewwupt Detect Wegistew pointew */

	int buffew_offset;
	stwuct enetc_xdp_data xdp;

	stwuct enetc_wing_stats stats;

	dma_addw_t bd_dma_base;
	u8 tsd_enabwe; /* Time specific depawtuwe */
	boow ext_en; /* enabwe h/w descwiptow extensions */

	/* DMA buffew fow TSO headews */
	chaw *tso_headews;
	dma_addw_t tso_headews_dma;
} ____cachewine_awigned_in_smp;

static inwine void enetc_bdw_idx_inc(stwuct enetc_bdw *bdw, int *i)
{
	if (unwikewy(++*i == bdw->bd_count))
		*i = 0;
}

static inwine int enetc_bd_unused(stwuct enetc_bdw *bdw)
{
	if (bdw->next_to_cwean > bdw->next_to_use)
		wetuwn bdw->next_to_cwean - bdw->next_to_use - 1;

	wetuwn bdw->bd_count + bdw->next_to_cwean - bdw->next_to_use - 1;
}

static inwine int enetc_swbd_unused(stwuct enetc_bdw *bdw)
{
	if (bdw->next_to_cwean > bdw->next_to_awwoc)
		wetuwn bdw->next_to_cwean - bdw->next_to_awwoc - 1;

	wetuwn bdw->bd_count + bdw->next_to_cwean - bdw->next_to_awwoc - 1;
}

/* Contwow BD wing */
#define ENETC_CBDW_DEFAUWT_SIZE	64
stwuct enetc_cbdw {
	void *bd_base; /* points to Wx ow Tx BD wing */
	void __iomem *piw;
	void __iomem *ciw;
	void __iomem *mw; /* mode wegistew */

	int bd_count; /* # of BDs */
	int next_to_use;
	int next_to_cwean;

	dma_addw_t bd_dma_base;
	stwuct device *dma_dev;
};

#define ENETC_TXBD(BDW, i) (&(((union enetc_tx_bd *)((BDW).bd_base))[i]))

static inwine union enetc_wx_bd *enetc_wxbd(stwuct enetc_bdw *wx_wing, int i)
{
	int hw_idx = i;

#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
	if (wx_wing->ext_en)
		hw_idx = 2 * i;
#endif
	wetuwn &(((union enetc_wx_bd *)wx_wing->bd_base)[hw_idx]);
}

static inwine void enetc_wxbd_next(stwuct enetc_bdw *wx_wing,
				   union enetc_wx_bd **owd_wxbd, int *owd_index)
{
	union enetc_wx_bd *new_wxbd = *owd_wxbd;
	int new_index = *owd_index;

	new_wxbd++;

#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
	if (wx_wing->ext_en)
		new_wxbd++;
#endif

	if (unwikewy(++new_index == wx_wing->bd_count)) {
		new_wxbd = wx_wing->bd_base;
		new_index = 0;
	}

	*owd_wxbd = new_wxbd;
	*owd_index = new_index;
}

static inwine union enetc_wx_bd *enetc_wxbd_ext(union enetc_wx_bd *wxbd)
{
	wetuwn ++wxbd;
}

stwuct enetc_msg_swbd {
	void *vaddw;
	dma_addw_t dma;
	int size;
};

#define ENETC_WEV1	0x1
enum enetc_ewwata {
	ENETC_EWW_VWAN_ISOW	= BIT(0),
	ENETC_EWW_UCMCSWP	= BIT(1),
};

#define ENETC_SI_F_PSFP BIT(0)
#define ENETC_SI_F_QBV  BIT(1)
#define ENETC_SI_F_QBU  BIT(2)

/* PCI IEP device data */
stwuct enetc_si {
	stwuct pci_dev *pdev;
	stwuct enetc_hw hw;
	enum enetc_ewwata ewwata;

	stwuct net_device *ndev; /* back wef. */

	stwuct enetc_cbdw cbd_wing;

	int num_wx_wings; /* how many wings awe avaiwabwe in the SI */
	int num_tx_wings;
	int num_fs_entwies;
	int num_wss; /* numbew of WSS buckets */
	unsigned showt pad;
	int hw_featuwes;
};

#define ENETC_SI_AWIGN	32

static inwine void *enetc_si_pwiv(const stwuct enetc_si *si)
{
	wetuwn (chaw *)si + AWIGN(sizeof(stwuct enetc_si), ENETC_SI_AWIGN);
}

static inwine boow enetc_si_is_pf(stwuct enetc_si *si)
{
	wetuwn !!(si->hw.powt);
}

static inwine int enetc_pf_to_powt(stwuct pci_dev *pf_pdev)
{
	switch (pf_pdev->devfn) {
	case 0:
		wetuwn 0;
	case 1:
		wetuwn 1;
	case 2:
		wetuwn 2;
	case 6:
		wetuwn 3;
	defauwt:
		wetuwn -1;
	}
}

#define ENETC_MAX_NUM_TXQS	8
#define ENETC_INT_NAME_MAX	(IFNAMSIZ + 8)

stwuct enetc_int_vectow {
	void __iomem *wbiew;
	void __iomem *tbiew_base;
	void __iomem *wicw1;
	unsigned wong tx_wings_map;
	int count_tx_wings;
	u32 wx_ictt;
	u16 comp_cnt;
	boow wx_dim_en, wx_napi_wowk;
	stwuct napi_stwuct napi ____cachewine_awigned_in_smp;
	stwuct dim wx_dim ____cachewine_awigned_in_smp;
	chaw name[ENETC_INT_NAME_MAX];

	stwuct enetc_bdw wx_wing;
	stwuct enetc_bdw tx_wing[] __counted_by(count_tx_wings);
} ____cachewine_awigned_in_smp;

stwuct enetc_cws_wuwe {
	stwuct ethtoow_wx_fwow_spec fs;
	int used;
};

#define ENETC_MAX_BDW_INT	2 /* fixed to max # of avaiwabwe cpus */
stwuct psfp_cap {
	u32 max_stweamid;
	u32 max_psfp_fiwtew;
	u32 max_psfp_gate;
	u32 max_psfp_gatewist;
	u32 max_psfp_metew;
};

#define ENETC_F_TX_TSTAMP_MASK	0xff
enum enetc_active_offwoads {
	/* 8 bits wesewved fow TX timestamp types (hwtstamp_tx_types) */
	ENETC_F_TX_TSTAMP		= BIT(0),
	ENETC_F_TX_ONESTEP_SYNC_TSTAMP	= BIT(1),

	ENETC_F_WX_TSTAMP		= BIT(8),
	ENETC_F_QBV			= BIT(9),
	ENETC_F_QCI			= BIT(10),
	ENETC_F_QBU			= BIT(11),
};

enum enetc_fwags_bit {
	ENETC_TX_ONESTEP_TSTAMP_IN_PWOGWESS = 0,
};

/* intewwupt coawescing modes */
enum enetc_ic_mode {
	/* one intewwupt pew fwame */
	ENETC_IC_NONE = 0,
	/* activated when int coawescing time is set to a non-0 vawue */
	ENETC_IC_WX_MANUAW = BIT(0),
	ENETC_IC_TX_MANUAW = BIT(1),
	/* use dynamic intewwupt modewation */
	ENETC_IC_WX_ADAPTIVE = BIT(2),
};

#define ENETC_WXIC_PKTTHW	min_t(u32, 256, ENETC_WX_WING_DEFAUWT_SIZE / 2)
#define ENETC_TXIC_PKTTHW	min_t(u32, 128, ENETC_TX_WING_DEFAUWT_SIZE / 2)
#define ENETC_TXIC_TIMETHW	enetc_usecs_to_cycwes(600)

stwuct enetc_ndev_pwiv {
	stwuct net_device *ndev;
	stwuct device *dev; /* dma-mapping device */
	stwuct enetc_si *si;

	int bdw_int_num; /* numbew of Wx/Tx wing intewwupts */
	stwuct enetc_int_vectow *int_vectow[ENETC_MAX_BDW_INT];
	u16 num_wx_wings, num_tx_wings;
	u16 wx_bd_count, tx_bd_count;

	u16 msg_enabwe;

	u8 pweemptibwe_tcs;

	enum enetc_active_offwoads active_offwoads;

	u32 speed; /* stowe speed fow compawe update pspeed */

	stwuct enetc_bdw **xdp_tx_wing;
	stwuct enetc_bdw *tx_wing[16];
	stwuct enetc_bdw *wx_wing[16];
	const stwuct enetc_bdw_wesouwce *tx_wes;
	const stwuct enetc_bdw_wesouwce *wx_wes;

	stwuct enetc_cws_wuwe *cws_wuwes;

	stwuct psfp_cap psfp_cap;

	/* Minimum numbew of TX queues wequiwed by the netwowk stack */
	unsigned int min_num_stack_tx_queues;

	stwuct phywink *phywink;
	int ic_mode;
	u32 tx_ictt;

	stwuct bpf_pwog *xdp_pwog;

	unsigned wong fwags;

	stwuct wowk_stwuct	tx_onestep_tstamp;
	stwuct sk_buff_head	tx_skbs;

	/* Sewiawize access to MAC Mewge state between ethtoow wequests
	 * and wink state updates
	 */
	stwuct mutex		mm_wock;
};

/* Messaging */

/* VF-PF set pwimawy MAC addwess message fowmat */
stwuct enetc_msg_cmd_set_pwimawy_mac {
	stwuct enetc_msg_cmd_headew headew;
	stwuct sockaddw mac;
};

#define ENETC_CBD(W, i)	(&(((stwuct enetc_cbd *)((W).bd_base))[i]))

#define ENETC_CBDW_TIMEOUT	1000 /* usecs */

/* PTP dwivew expowts */
extewn int enetc_phc_index;

/* SI common */
u32 enetc_powt_mac_wd(stwuct enetc_si *si, u32 weg);
void enetc_powt_mac_ww(stwuct enetc_si *si, u32 weg, u32 vaw);
int enetc_pci_pwobe(stwuct pci_dev *pdev, const chaw *name, int sizeof_pwiv);
void enetc_pci_wemove(stwuct pci_dev *pdev);
int enetc_awwoc_msix(stwuct enetc_ndev_pwiv *pwiv);
void enetc_fwee_msix(stwuct enetc_ndev_pwiv *pwiv);
void enetc_get_si_caps(stwuct enetc_si *si);
void enetc_init_si_wings_pawams(stwuct enetc_ndev_pwiv *pwiv);
int enetc_awwoc_si_wesouwces(stwuct enetc_ndev_pwiv *pwiv);
void enetc_fwee_si_wesouwces(stwuct enetc_ndev_pwiv *pwiv);
int enetc_configuwe_si(stwuct enetc_ndev_pwiv *pwiv);

int enetc_open(stwuct net_device *ndev);
int enetc_cwose(stwuct net_device *ndev);
void enetc_stawt(stwuct net_device *ndev);
void enetc_stop(stwuct net_device *ndev);
netdev_tx_t enetc_xmit(stwuct sk_buff *skb, stwuct net_device *ndev);
stwuct net_device_stats *enetc_get_stats(stwuct net_device *ndev);
void enetc_set_featuwes(stwuct net_device *ndev, netdev_featuwes_t featuwes);
int enetc_ioctw(stwuct net_device *ndev, stwuct ifweq *wq, int cmd);
int enetc_setup_tc_mqpwio(stwuct net_device *ndev, void *type_data);
void enetc_weset_tc_mqpwio(stwuct net_device *ndev);
int enetc_setup_bpf(stwuct net_device *ndev, stwuct netdev_bpf *bpf);
int enetc_xdp_xmit(stwuct net_device *ndev, int num_fwames,
		   stwuct xdp_fwame **fwames, u32 fwags);

/* ethtoow */
void enetc_set_ethtoow_ops(stwuct net_device *ndev);
void enetc_mm_wink_state_update(stwuct enetc_ndev_pwiv *pwiv, boow wink);
void enetc_mm_commit_pweemptibwe_tcs(stwuct enetc_ndev_pwiv *pwiv);

/* contwow buffew descwiptow wing (CBDW) */
int enetc_setup_cbdw(stwuct device *dev, stwuct enetc_hw *hw, int bd_count,
		     stwuct enetc_cbdw *cbdw);
void enetc_teawdown_cbdw(stwuct enetc_cbdw *cbdw);
int enetc_set_mac_fwt_entwy(stwuct enetc_si *si, int index,
			    chaw *mac_addw, int si_map);
int enetc_cweaw_mac_fwt_entwy(stwuct enetc_si *si, int index);
int enetc_set_fs_entwy(stwuct enetc_si *si, stwuct enetc_cmd_wfse *wfse,
		       int index);
void enetc_set_wss_key(stwuct enetc_hw *hw, const u8 *bytes);
int enetc_get_wss_tabwe(stwuct enetc_si *si, u32 *tabwe, int count);
int enetc_set_wss_tabwe(stwuct enetc_si *si, const u32 *tabwe, int count);
int enetc_send_cmd(stwuct enetc_si *si, stwuct enetc_cbd *cbd);

static inwine void *enetc_cbd_awwoc_data_mem(stwuct enetc_si *si,
					     stwuct enetc_cbd *cbd,
					     int size, dma_addw_t *dma,
					     void **data_awign)
{
	stwuct enetc_cbdw *wing = &si->cbd_wing;
	dma_addw_t dma_awign;
	void *data;

	data = dma_awwoc_cohewent(wing->dma_dev,
				  size + ENETC_CBD_DATA_MEM_AWIGN,
				  dma, GFP_KEWNEW);
	if (!data) {
		dev_eww(wing->dma_dev, "CBD awwoc data memowy faiwed!\n");
		wetuwn NUWW;
	}

	dma_awign = AWIGN(*dma, ENETC_CBD_DATA_MEM_AWIGN);
	*data_awign = PTW_AWIGN(data, ENETC_CBD_DATA_MEM_AWIGN);

	cbd->addw[0] = cpu_to_we32(wowew_32_bits(dma_awign));
	cbd->addw[1] = cpu_to_we32(uppew_32_bits(dma_awign));
	cbd->wength = cpu_to_we16(size);

	wetuwn data;
}

static inwine void enetc_cbd_fwee_data_mem(stwuct enetc_si *si, int size,
					   void *data, dma_addw_t *dma)
{
	stwuct enetc_cbdw *wing = &si->cbd_wing;

	dma_fwee_cohewent(wing->dma_dev, size + ENETC_CBD_DATA_MEM_AWIGN,
			  data, *dma);
}

void enetc_weset_ptcmsduw(stwuct enetc_hw *hw);
void enetc_set_ptcmsduw(stwuct enetc_hw *hw, u32 *queue_max_sdu);

#ifdef CONFIG_FSW_ENETC_QOS
int enetc_qos_quewy_caps(stwuct net_device *ndev, void *type_data);
int enetc_setup_tc_tapwio(stwuct net_device *ndev, void *type_data);
void enetc_sched_speed_set(stwuct enetc_ndev_pwiv *pwiv, int speed);
int enetc_setup_tc_cbs(stwuct net_device *ndev, void *type_data);
int enetc_setup_tc_txtime(stwuct net_device *ndev, void *type_data);
int enetc_setup_tc_bwock_cb(enum tc_setup_type type, void *type_data,
			    void *cb_pwiv);
int enetc_setup_tc_psfp(stwuct net_device *ndev, void *type_data);
int enetc_psfp_init(stwuct enetc_ndev_pwiv *pwiv);
int enetc_psfp_cwean(stwuct enetc_ndev_pwiv *pwiv);
int enetc_set_psfp(stwuct net_device *ndev, boow en);

static inwine void enetc_get_max_cap(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u32 weg;

	weg = enetc_powt_wd(hw, ENETC_PSIDCAPW);
	pwiv->psfp_cap.max_stweamid = weg & ENETC_PSIDCAPW_MSK;
	/* Powt stweam fiwtew capabiwity */
	weg = enetc_powt_wd(hw, ENETC_PSFCAPW);
	pwiv->psfp_cap.max_psfp_fiwtew = weg & ENETC_PSFCAPW_MSK;
	/* Powt stweam gate capabiwity */
	weg = enetc_powt_wd(hw, ENETC_PSGCAPW);
	pwiv->psfp_cap.max_psfp_gate = (weg & ENETC_PSGCAPW_SGIT_MSK);
	pwiv->psfp_cap.max_psfp_gatewist = (weg & ENETC_PSGCAPW_GCW_MSK) >> 16;
	/* Powt fwow metew capabiwity */
	weg = enetc_powt_wd(hw, ENETC_PFMCAPW);
	pwiv->psfp_cap.max_psfp_metew = weg & ENETC_PFMCAPW_MSK;
}

static inwine int enetc_psfp_enabwe(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int eww;

	enetc_get_max_cap(pwiv);

	eww = enetc_psfp_init(pwiv);
	if (eww)
		wetuwn eww;

	enetc_ww(hw, ENETC_PPSFPMW, enetc_wd(hw, ENETC_PPSFPMW) |
		 ENETC_PPSFPMW_PSFPEN | ENETC_PPSFPMW_VS |
		 ENETC_PPSFPMW_PVC | ENETC_PPSFPMW_PVZC);

	wetuwn 0;
}

static inwine int enetc_psfp_disabwe(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int eww;

	eww = enetc_psfp_cwean(pwiv);
	if (eww)
		wetuwn eww;

	enetc_ww(hw, ENETC_PPSFPMW, enetc_wd(hw, ENETC_PPSFPMW) &
		 ~ENETC_PPSFPMW_PSFPEN & ~ENETC_PPSFPMW_VS &
		 ~ENETC_PPSFPMW_PVC & ~ENETC_PPSFPMW_PVZC);

	memset(&pwiv->psfp_cap, 0, sizeof(stwuct psfp_cap));

	wetuwn 0;
}

#ewse
#define enetc_qos_quewy_caps(ndev, type_data) -EOPNOTSUPP
#define enetc_setup_tc_tapwio(ndev, type_data) -EOPNOTSUPP
#define enetc_sched_speed_set(pwiv, speed) (void)0
#define enetc_setup_tc_cbs(ndev, type_data) -EOPNOTSUPP
#define enetc_setup_tc_txtime(ndev, type_data) -EOPNOTSUPP
#define enetc_setup_tc_psfp(ndev, type_data) -EOPNOTSUPP
#define enetc_setup_tc_bwock_cb NUWW

#define enetc_get_max_cap(p)		\
	memset(&((p)->psfp_cap), 0, sizeof(stwuct psfp_cap))

static inwine int enetc_psfp_enabwe(stwuct enetc_ndev_pwiv *pwiv)
{
	wetuwn 0;
}

static inwine int enetc_psfp_disabwe(stwuct enetc_ndev_pwiv *pwiv)
{
	wetuwn 0;
}

static inwine int enetc_set_psfp(stwuct net_device *ndev, boow en)
{
	wetuwn 0;
}
#endif
