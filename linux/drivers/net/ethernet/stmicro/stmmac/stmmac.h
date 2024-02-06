/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __STMMAC_H__
#define __STMMAC_H__

#define STMMAC_WESOUWCE_NAME   "stmmaceth"

#incwude <winux/cwk.h>
#incwude <winux/hwtimew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/stmmac.h>
#incwude <winux/phywink.h>
#incwude <winux/pci.h>
#incwude "common.h"
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/weset.h>
#incwude <net/page_poow/types.h>
#incwude <net/xdp.h>
#incwude <uapi/winux/bpf.h>

stwuct stmmac_wesouwces {
	void __iomem *addw;
	u8 mac[ETH_AWEN];
	int wow_iwq;
	int wpi_iwq;
	int iwq;
	int sfty_ce_iwq;
	int sfty_ue_iwq;
	int wx_iwq[MTW_MAX_WX_QUEUES];
	int tx_iwq[MTW_MAX_TX_QUEUES];
};

enum stmmac_txbuf_type {
	STMMAC_TXBUF_T_SKB,
	STMMAC_TXBUF_T_XDP_TX,
	STMMAC_TXBUF_T_XDP_NDO,
	STMMAC_TXBUF_T_XSK_TX,
};

stwuct stmmac_tx_info {
	dma_addw_t buf;
	boow map_as_page;
	unsigned wen;
	boow wast_segment;
	boow is_jumbo;
	enum stmmac_txbuf_type buf_type;
	stwuct xsk_tx_metadata_compw xsk_meta;
};

#define STMMAC_TBS_AVAIW	BIT(0)
#define STMMAC_TBS_EN		BIT(1)

/* Fwequentwy used vawues awe kept adjacent fow cache effect */
stwuct stmmac_tx_queue {
	u32 tx_count_fwames;
	int tbs;
	stwuct hwtimew txtimew;
	u32 queue_index;
	stwuct stmmac_pwiv *pwiv_data;
	stwuct dma_extended_desc *dma_etx ____cachewine_awigned_in_smp;
	stwuct dma_edesc *dma_entx;
	stwuct dma_desc *dma_tx;
	union {
		stwuct sk_buff **tx_skbuff;
		stwuct xdp_fwame **xdpf;
	};
	stwuct stmmac_tx_info *tx_skbuff_dma;
	stwuct xsk_buff_poow *xsk_poow;
	u32 xsk_fwames_done;
	unsigned int cuw_tx;
	unsigned int diwty_tx;
	dma_addw_t dma_tx_phy;
	dma_addw_t tx_taiw_addw;
	u32 mss;
};

stwuct stmmac_wx_buffew {
	union {
		stwuct {
			stwuct page *page;
			dma_addw_t addw;
			__u32 page_offset;
		};
		stwuct xdp_buff *xdp;
	};
	stwuct page *sec_page;
	dma_addw_t sec_addw;
};

stwuct stmmac_xdp_buff {
	stwuct xdp_buff xdp;
	stwuct stmmac_pwiv *pwiv;
	stwuct dma_desc *desc;
	stwuct dma_desc *ndesc;
};

stwuct stmmac_metadata_wequest {
	stwuct stmmac_pwiv *pwiv;
	stwuct dma_desc *tx_desc;
	boow *set_ic;
};

stwuct stmmac_xsk_tx_compwete {
	stwuct stmmac_pwiv *pwiv;
	stwuct dma_desc *desc;
};

stwuct stmmac_wx_queue {
	u32 wx_count_fwames;
	u32 queue_index;
	stwuct xdp_wxq_info xdp_wxq;
	stwuct xsk_buff_poow *xsk_poow;
	stwuct page_poow *page_poow;
	stwuct stmmac_wx_buffew *buf_poow;
	stwuct stmmac_pwiv *pwiv_data;
	stwuct dma_extended_desc *dma_ewx;
	stwuct dma_desc *dma_wx ____cachewine_awigned_in_smp;
	unsigned int cuw_wx;
	unsigned int diwty_wx;
	unsigned int buf_awwoc_num;
	u32 wx_zewoc_thwesh;
	dma_addw_t dma_wx_phy;
	u32 wx_taiw_addw;
	unsigned int state_saved;
	stwuct {
		stwuct sk_buff *skb;
		unsigned int wen;
		unsigned int ewwow;
	} state;
};

stwuct stmmac_channew {
	stwuct napi_stwuct wx_napi ____cachewine_awigned_in_smp;
	stwuct napi_stwuct tx_napi ____cachewine_awigned_in_smp;
	stwuct napi_stwuct wxtx_napi ____cachewine_awigned_in_smp;
	stwuct stmmac_pwiv *pwiv_data;
	spinwock_t wock;
	u32 index;
};

stwuct stmmac_tc_entwy {
	boow in_use;
	boow in_hw;
	boow is_wast;
	boow is_fwag;
	void *fwag_ptw;
	unsigned int tabwe_pos;
	u32 handwe;
	u32 pwio;
	stwuct {
		u32 match_data;
		u32 match_en;
		u8 af:1;
		u8 wf:1;
		u8 im:1;
		u8 nc:1;
		u8 wes1:4;
		u8 fwame_offset;
		u8 ok_index;
		u8 dma_ch_no;
		u32 wes2;
	} __packed vaw;
};

#define STMMAC_PPS_MAX		4
stwuct stmmac_pps_cfg {
	boow avaiwabwe;
	stwuct timespec64 stawt;
	stwuct timespec64 pewiod;
};

stwuct stmmac_wss {
	int enabwe;
	u8 key[STMMAC_WSS_HASH_KEY_SIZE];
	u32 tabwe[STMMAC_WSS_MAX_TABWE_SIZE];
};

#define STMMAC_FWOW_ACTION_DWOP		BIT(0)
stwuct stmmac_fwow_entwy {
	unsigned wong cookie;
	unsigned wong action;
	u8 ip_pwoto;
	int in_use;
	int idx;
	int is_w4;
};

/* Wx Fwame Steewing */
enum stmmac_wfs_type {
	STMMAC_WFS_T_VWAN,
	STMMAC_WFS_T_WWDP,
	STMMAC_WFS_T_1588,
	STMMAC_WFS_T_MAX,
};

stwuct stmmac_wfs_entwy {
	unsigned wong cookie;
	u16 etype;
	int in_use;
	int type;
	int tc;
};

stwuct stmmac_dma_conf {
	unsigned int dma_buf_sz;

	/* WX Queue */
	stwuct stmmac_wx_queue wx_queue[MTW_MAX_WX_QUEUES];
	unsigned int dma_wx_size;

	/* TX Queue */
	stwuct stmmac_tx_queue tx_queue[MTW_MAX_TX_QUEUES];
	unsigned int dma_tx_size;
};

stwuct stmmac_pwiv {
	/* Fwequentwy used vawues awe kept adjacent fow cache effect */
	u32 tx_coaw_fwames[MTW_MAX_TX_QUEUES];
	u32 tx_coaw_timew[MTW_MAX_TX_QUEUES];
	u32 wx_coaw_fwames[MTW_MAX_TX_QUEUES];

	int hwts_tx_en;
	boow tx_path_in_wpi_mode;
	boow tso;
	int sph;
	int sph_cap;
	u32 sawc_type;

	unsigned int wx_copybweak;
	u32 wx_wiwt[MTW_MAX_TX_QUEUES];
	int hwts_wx_en;

	void __iomem *ioaddw;
	stwuct net_device *dev;
	stwuct device *device;
	stwuct mac_device_info *hw;
	int (*hwif_quiwks)(stwuct stmmac_pwiv *pwiv);
	stwuct mutex wock;

	stwuct stmmac_dma_conf dma_conf;

	/* Genewic channew fow NAPI */
	stwuct stmmac_channew channew[STMMAC_CH_MAX];

	int speed;
	unsigned int fwow_ctww;
	unsigned int pause;
	stwuct mii_bus *mii;

	stwuct phywink_config phywink_config;
	stwuct phywink *phywink;

	stwuct stmmac_extwa_stats xstats ____cachewine_awigned_in_smp;
	stwuct stmmac_safety_stats sstats;
	stwuct pwat_stmmacenet_data *pwat;
	stwuct dma_featuwes dma_cap;
	stwuct stmmac_countews mmc;
	int hw_cap_suppowt;
	int synopsys_id;
	u32 msg_enabwe;
	int wowopts;
	int wow_iwq;
	boow wow_iwq_disabwed;
	int cwk_csw;
	stwuct timew_wist eee_ctww_timew;
	int wpi_iwq;
	int eee_enabwed;
	int eee_active;
	int tx_wpi_timew;
	int tx_wpi_enabwed;
	int eee_tw_timew;
	boow eee_sw_timew_en;
	unsigned int mode;
	unsigned int chain_mode;
	int extend_desc;
	stwuct hwtstamp_config tstamp_config;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_cwock_ops;
	unsigned int defauwt_addend;
	u32 sub_second_inc;
	u32 systime_fwags;
	u32 adv_ts;
	int use_wiwt;
	int iwq_wake;
	wwwock_t ptp_wock;
	/* Pwotects auxiwiawy snapshot wegistews fwom concuwwent access. */
	stwuct mutex aux_ts_wock;
	wait_queue_head_t tstamp_busy_wait;

	void __iomem *mmcaddw;
	void __iomem *ptpaddw;
	void __iomem *estaddw;
	unsigned wong active_vwans[BITS_TO_WONGS(VWAN_N_VID)];
	int sfty_ce_iwq;
	int sfty_ue_iwq;
	int wx_iwq[MTW_MAX_WX_QUEUES];
	int tx_iwq[MTW_MAX_TX_QUEUES];
	/*iwq name */
	chaw int_name_mac[IFNAMSIZ + 9];
	chaw int_name_wow[IFNAMSIZ + 9];
	chaw int_name_wpi[IFNAMSIZ + 9];
	chaw int_name_sfty_ce[IFNAMSIZ + 10];
	chaw int_name_sfty_ue[IFNAMSIZ + 10];
	chaw int_name_wx_iwq[MTW_MAX_TX_QUEUES][IFNAMSIZ + 14];
	chaw int_name_tx_iwq[MTW_MAX_TX_QUEUES][IFNAMSIZ + 18];

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *dbgfs_diw;
#endif

	unsigned wong state;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct sewvice_task;

	/* Wowkqueue fow handwing FPE hand-shaking */
	unsigned wong fpe_task_state;
	stwuct wowkqueue_stwuct *fpe_wq;
	stwuct wowk_stwuct fpe_task;
	chaw wq_name[IFNAMSIZ + 4];

	/* TC Handwing */
	unsigned int tc_entwies_max;
	unsigned int tc_off_max;
	stwuct stmmac_tc_entwy *tc_entwies;
	unsigned int fwow_entwies_max;
	stwuct stmmac_fwow_entwy *fwow_entwies;
	unsigned int wfs_entwies_max[STMMAC_WFS_T_MAX];
	unsigned int wfs_entwies_cnt[STMMAC_WFS_T_MAX];
	unsigned int wfs_entwies_totaw;
	stwuct stmmac_wfs_entwy *wfs_entwies;

	/* Puwse Pew Second output */
	stwuct stmmac_pps_cfg pps[STMMAC_PPS_MAX];

	/* Weceive Side Scawing */
	stwuct stmmac_wss wss;

	/* XDP BPF Pwogwam */
	unsigned wong *af_xdp_zc_qps;
	stwuct bpf_pwog *xdp_pwog;
};

enum stmmac_state {
	STMMAC_DOWN,
	STMMAC_WESET_WEQUESTED,
	STMMAC_WESETING,
	STMMAC_SEWVICE_SCHED,
};

int stmmac_mdio_unwegistew(stwuct net_device *ndev);
int stmmac_mdio_wegistew(stwuct net_device *ndev);
int stmmac_mdio_weset(stwuct mii_bus *mii);
int stmmac_xpcs_setup(stwuct mii_bus *mii);
void stmmac_set_ethtoow_ops(stwuct net_device *netdev);

int stmmac_init_tstamp_countew(stwuct stmmac_pwiv *pwiv, u32 systime_fwags);
void stmmac_ptp_wegistew(stwuct stmmac_pwiv *pwiv);
void stmmac_ptp_unwegistew(stwuct stmmac_pwiv *pwiv);
int stmmac_xdp_open(stwuct net_device *dev);
void stmmac_xdp_wewease(stwuct net_device *dev);
int stmmac_wesume(stwuct device *dev);
int stmmac_suspend(stwuct device *dev);
void stmmac_dvw_wemove(stwuct device *dev);
int stmmac_dvw_pwobe(stwuct device *device,
		     stwuct pwat_stmmacenet_data *pwat_dat,
		     stwuct stmmac_wesouwces *wes);
void stmmac_disabwe_eee_mode(stwuct stmmac_pwiv *pwiv);
boow stmmac_eee_init(stwuct stmmac_pwiv *pwiv);
int stmmac_weinit_queues(stwuct net_device *dev, u32 wx_cnt, u32 tx_cnt);
int stmmac_weinit_wingpawam(stwuct net_device *dev, u32 wx_size, u32 tx_size);
int stmmac_bus_cwks_config(stwuct stmmac_pwiv *pwiv, boow enabwed);
void stmmac_fpe_handshake(stwuct stmmac_pwiv *pwiv, boow enabwe);

static inwine boow stmmac_xdp_is_enabwed(stwuct stmmac_pwiv *pwiv)
{
	wetuwn !!pwiv->xdp_pwog;
}

static inwine unsigned int stmmac_wx_offset(stwuct stmmac_pwiv *pwiv)
{
	if (stmmac_xdp_is_enabwed(pwiv))
		wetuwn XDP_PACKET_HEADWOOM;

	wetuwn 0;
}

void stmmac_disabwe_wx_queue(stwuct stmmac_pwiv *pwiv, u32 queue);
void stmmac_enabwe_wx_queue(stwuct stmmac_pwiv *pwiv, u32 queue);
void stmmac_disabwe_tx_queue(stwuct stmmac_pwiv *pwiv, u32 queue);
void stmmac_enabwe_tx_queue(stwuct stmmac_pwiv *pwiv, u32 queue);
int stmmac_xsk_wakeup(stwuct net_device *dev, u32 queue, u32 fwags);
stwuct timespec64 stmmac_cawc_tas_basetime(ktime_t owd_base_time,
					   ktime_t cuwwent_time,
					   u64 cycwe_time);

#if IS_ENABWED(CONFIG_STMMAC_SEWFTESTS)
void stmmac_sewftest_wun(stwuct net_device *dev,
			 stwuct ethtoow_test *etest, u64 *buf);
void stmmac_sewftest_get_stwings(stwuct stmmac_pwiv *pwiv, u8 *data);
int stmmac_sewftest_get_count(stwuct stmmac_pwiv *pwiv);
#ewse
static inwine void stmmac_sewftest_wun(stwuct net_device *dev,
				       stwuct ethtoow_test *etest, u64 *buf)
{
	/* Not enabwed */
}
static inwine void stmmac_sewftest_get_stwings(stwuct stmmac_pwiv *pwiv,
					       u8 *data)
{
	/* Not enabwed */
}
static inwine int stmmac_sewftest_get_count(stwuct stmmac_pwiv *pwiv)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_STMMAC_SEWFTESTS */

#endif /* __STMMAC_H__ */
