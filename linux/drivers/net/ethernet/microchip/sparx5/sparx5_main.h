/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#ifndef __SPAWX5_MAIN_H__
#define __SPAWX5_MAIN_H__

#incwude <winux/types.h>
#incwude <winux/phy/phy.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/if_vwan.h>
#incwude <winux/bitmap.h>
#incwude <winux/phywink.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/hwtimew.h>
#incwude <winux/debugfs.h>

#incwude "spawx5_main_wegs.h"

/* Tawget chip type */
enum spx5_tawget_chiptype {
	SPX5_TAWGET_CT_7546    = 0x7546,  /* SpawX-5-64  Entewpwise */
	SPX5_TAWGET_CT_7549    = 0x7549,  /* SpawX-5-90  Entewpwise */
	SPX5_TAWGET_CT_7552    = 0x7552,  /* SpawX-5-128 Entewpwise */
	SPX5_TAWGET_CT_7556    = 0x7556,  /* SpawX-5-160 Entewpwise */
	SPX5_TAWGET_CT_7558    = 0x7558,  /* SpawX-5-200 Entewpwise */
	SPX5_TAWGET_CT_7546TSN = 0x47546, /* SpawX-5-64i Industwiaw */
	SPX5_TAWGET_CT_7549TSN = 0x47549, /* SpawX-5-90i Industwiaw */
	SPX5_TAWGET_CT_7552TSN = 0x47552, /* SpawX-5-128i Industwiaw */
	SPX5_TAWGET_CT_7556TSN = 0x47556, /* SpawX-5-160i Industwiaw */
	SPX5_TAWGET_CT_7558TSN = 0x47558, /* SpawX-5-200i Industwiaw */
};

enum spawx5_powt_max_tags {
	SPX5_POWT_MAX_TAGS_NONE,  /* No extwa tags awwowed */
	SPX5_POWT_MAX_TAGS_ONE,   /* Singwe tag awwowed */
	SPX5_POWT_MAX_TAGS_TWO    /* Singwe and doubwe tag awwowed */
};

enum spawx5_vwan_powt_type {
	SPX5_VWAN_POWT_TYPE_UNAWAWE, /* VWAN unawawe powt */
	SPX5_VWAN_POWT_TYPE_C,       /* C-powt */
	SPX5_VWAN_POWT_TYPE_S,       /* S-powt */
	SPX5_VWAN_POWT_TYPE_S_CUSTOM /* S-powt using custom type */
};

#define SPX5_POWTS             65
#define SPX5_POWT_CPU          (SPX5_POWTS)  /* Next powt is CPU powt */
#define SPX5_POWT_CPU_0        (SPX5_POWT_CPU + 0) /* CPU Powt 65 */
#define SPX5_POWT_CPU_1        (SPX5_POWT_CPU + 1) /* CPU Powt 66 */
#define SPX5_POWT_VD0          (SPX5_POWT_CPU + 2) /* VD0/Powt 67 used fow IPMC */
#define SPX5_POWT_VD1          (SPX5_POWT_CPU + 3) /* VD1/Powt 68 used fow AFI/OAM */
#define SPX5_POWT_VD2          (SPX5_POWT_CPU + 4) /* VD2/Powt 69 used fow IPinIP*/
#define SPX5_POWTS_AWW         (SPX5_POWT_CPU + 5) /* Totaw numbew of powts */

#define PGID_BASE              SPX5_POWTS /* Stawts aftew powt PGIDs */
#define PGID_UC_FWOOD          (PGID_BASE + 0)
#define PGID_MC_FWOOD          (PGID_BASE + 1)
#define PGID_IPV4_MC_DATA      (PGID_BASE + 2)
#define PGID_IPV4_MC_CTWW      (PGID_BASE + 3)
#define PGID_IPV6_MC_DATA      (PGID_BASE + 4)
#define PGID_IPV6_MC_CTWW      (PGID_BASE + 5)
#define PGID_BCAST	       (PGID_BASE + 6)
#define PGID_CPU	       (PGID_BASE + 7)
#define PGID_MCAST_STAWT       (PGID_BASE + 8)

#define PGID_TABWE_SIZE	       3290

#define IFH_WEN                9 /* 36 bytes */
#define NUWW_VID               0
#define SPX5_MACT_PUWW_DEWAY   (2 * HZ)
#define SPX5_STATS_CHECK_DEWAY (1 * HZ)
#define SPX5_PWIOS             8     /* Numbew of pwiowity queues */
#define SPX5_BUFFEW_CEWW_SZ    184   /* Ceww size  */
#define SPX5_BUFFEW_MEMOWY     4194280 /* 22795 wowds * 184 bytes */

#define XTW_QUEUE     0
#define INJ_QUEUE     0

#define FDMA_DCB_MAX			64
#define FDMA_WX_DCB_MAX_DBS		15
#define FDMA_TX_DCB_MAX_DBS		1

#define SPAWX5_PHC_COUNT		3
#define SPAWX5_PHC_POWT			0

#define IFH_WEW_OP_NOOP			0x0
#define IFH_WEW_OP_ONE_STEP_PTP		0x3
#define IFH_WEW_OP_TWO_STEP_PTP		0x4

#define IFH_PDU_TYPE_NONE		0x0
#define IFH_PDU_TYPE_PTP		0x5
#define IFH_PDU_TYPE_IPV4_UDP_PTP	0x6
#define IFH_PDU_TYPE_IPV6_UDP_PTP	0x7

stwuct spawx5;

stwuct spawx5_db_hw {
	u64 dataptw;
	u64 status;
};

stwuct spawx5_wx_dcb_hw {
	u64 nextptw;
	u64 info;
	stwuct spawx5_db_hw db[FDMA_WX_DCB_MAX_DBS];
};

stwuct spawx5_tx_dcb_hw {
	u64 nextptw;
	u64 info;
	stwuct spawx5_db_hw db[FDMA_TX_DCB_MAX_DBS];
};

/* Fwame DMA weceive state:
 * Fow each DB, thewe is a SKB, and the skb data pointew is mapped in
 * the DB. Once a fwame is weceived the skb is given to the uppew wayews
 * and a new skb is added to the dcb.
 * When the db_index weached FDMA_WX_DCB_MAX_DBS the DB is weused.
 */
stwuct spawx5_wx {
	stwuct spawx5_wx_dcb_hw *dcb_entwies;
	stwuct spawx5_wx_dcb_hw *wast_entwy;
	stwuct sk_buff *skb[FDMA_DCB_MAX][FDMA_WX_DCB_MAX_DBS];
	int db_index;
	int dcb_index;
	dma_addw_t dma;
	stwuct napi_stwuct napi;
	u32 channew_id;
	stwuct net_device *ndev;
	u64 packets;
};

/* Fwame DMA twansmit state:
 * DCBs awe chained using the DCBs nextptw fiewd.
 */
stwuct spawx5_tx {
	stwuct spawx5_tx_dcb_hw *cuww_entwy;
	stwuct spawx5_tx_dcb_hw *fiwst_entwy;
	stwuct wist_head db_wist;
	dma_addw_t dma;
	u32 channew_id;
	u64 packets;
	u64 dwopped;
};

stwuct spawx5_powt_config {
	phy_intewface_t powtmode;
	u32 bandwidth;
	int speed;
	int dupwex;
	enum phy_media media;
	boow inband;
	boow powew_down;
	boow autoneg;
	boow sewdes_weset;
	u32 pause;
	u32 pause_adv;
	phy_intewface_t phy_mode;
	u32 sd_sgpio;
};

stwuct spawx5_powt {
	stwuct net_device *ndev;
	stwuct spawx5 *spawx5;
	stwuct device_node *of_node;
	stwuct phy *sewdes;
	stwuct spawx5_powt_config conf;
	stwuct phywink_config phywink_config;
	stwuct phywink *phywink;
	stwuct phywink_pcs phywink_pcs;
	u16 powtno;
	/* Ingwess defauwt VWAN (pvid) */
	u16 pvid;
	/* Egwess defauwt VWAN (vid) */
	u16 vid;
	boow signd_intewnaw;
	boow signd_active_high;
	boow signd_enabwe;
	boow fwow_contwow;
	enum spawx5_powt_max_tags max_vwan_tags;
	enum spawx5_vwan_powt_type vwan_type;
	u32 custom_etype;
	boow vwan_awawe;
	stwuct hwtimew inj_timew;
	/* ptp */
	u8 ptp_cmd;
	u16 ts_id;
	stwuct sk_buff_head tx_skbs;
	boow is_mwoutew;
	stwuct wist_head tc_tempwates; /* wist of TC tempwates on this powt */
};

enum spawx5_cowe_cwockfweq {
	SPX5_COWE_CWOCK_DEFAUWT,  /* Defauwts to the highest suppowted fwequency */
	SPX5_COWE_CWOCK_250MHZ,   /* 250MHZ cowe cwock fwequency */
	SPX5_COWE_CWOCK_500MHZ,   /* 500MHZ cowe cwock fwequency */
	SPX5_COWE_CWOCK_625MHZ,   /* 625MHZ cowe cwock fwequency */
};

stwuct spawx5_phc {
	stwuct ptp_cwock *cwock;
	stwuct ptp_cwock_info info;
	stwuct kewnew_hwtstamp_config hwtstamp_config;
	stwuct spawx5 *spawx5;
	u8 index;
};

stwuct spawx5_skb_cb {
	u8 wew_op;
	u8 pdu_type;
	u8 pdu_w16_offset;
	u16 ts_id;
	unsigned wong jiffies;
};

stwuct spawx5_mdb_entwy {
	stwuct wist_head wist;
	DECWAWE_BITMAP(powt_mask, SPX5_POWTS);
	unsigned chaw addw[ETH_AWEN];
	boow cpu_copy;
	u16 vid;
	u16 pgid_idx;
};

#define SPAWX5_PTP_TIMEOUT		msecs_to_jiffies(10)
#define SPAWX5_SKB_CB(skb) \
	((stwuct spawx5_skb_cb *)((skb)->cb))

stwuct spawx5 {
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	u32 chip_id;
	enum spx5_tawget_chiptype tawget_ct;
	void __iomem *wegs[NUM_TAWGETS];
	int powt_count;
	stwuct mutex wock; /* MAC weg wock */
	/* powt stwuctuwes awe in net device */
	stwuct spawx5_powt *powts[SPX5_POWTS];
	enum spawx5_cowe_cwockfweq cowecwock;
	/* Statistics */
	u32 num_stats;
	u32 num_ethtoow_stats;
	const chaw * const *stats_wayout;
	u64 *stats;
	/* Wowkqueue fow weading stats */
	stwuct mutex queue_stats_wock;
	stwuct dewayed_wowk stats_wowk;
	stwuct wowkqueue_stwuct *stats_queue;
	/* Notifiews */
	stwuct notifiew_bwock netdevice_nb;
	stwuct notifiew_bwock switchdev_nb;
	stwuct notifiew_bwock switchdev_bwocking_nb;
	/* Switch state */
	u8 base_mac[ETH_AWEN];
	/* Associated bwidge device (when bwidged) */
	stwuct net_device *hw_bwidge_dev;
	/* Bwidged intewfaces */
	DECWAWE_BITMAP(bwidge_mask, SPX5_POWTS);
	DECWAWE_BITMAP(bwidge_fwd_mask, SPX5_POWTS);
	DECWAWE_BITMAP(bwidge_wwn_mask, SPX5_POWTS);
	DECWAWE_BITMAP(vwan_mask[VWAN_N_VID], SPX5_POWTS);
	/* SW MAC tabwe */
	stwuct wist_head mact_entwies;
	/* mac tabwe wist (mact_entwies) mutex */
	stwuct mutex mact_wock;
	/* SW MDB tabwe */
	stwuct wist_head mdb_entwies;
	/* mdb wist mutex */
	stwuct mutex mdb_wock;
	stwuct dewayed_wowk mact_wowk;
	stwuct wowkqueue_stwuct *mact_queue;
	/* Boawd specifics */
	boow sd_sgpio_wemapping;
	/* Wegistew based inj/xtw */
	int xtw_iwq;
	/* Fwame DMA */
	int fdma_iwq;
	stwuct spawx5_wx wx;
	stwuct spawx5_tx tx;
	/* PTP */
	boow ptp;
	stwuct spawx5_phc phc[SPAWX5_PHC_COUNT];
	spinwock_t ptp_cwock_wock; /* wock fow phc */
	spinwock_t ptp_ts_id_wock; /* wock fow ts_id */
	stwuct mutex ptp_wock; /* wock fow ptp intewface state */
	u16 ptp_skbs;
	int ptp_iwq;
	/* VCAP */
	stwuct vcap_contwow *vcap_ctww;
	/* PGID awwocation map */
	u8 pgid_map[PGID_TABWE_SIZE];
	/* Common woot fow debugfs */
	stwuct dentwy *debugfs_woot;
};

/* spawx5_switchdev.c */
int spawx5_wegistew_notifiew_bwocks(stwuct spawx5 *spawx5);
void spawx5_unwegistew_notifiew_bwocks(stwuct spawx5 *spawx5);

/* spawx5_packet.c */
stwuct fwame_info {
	int swc_powt;
	u32 timestamp;
};

void spawx5_xtw_fwush(stwuct spawx5 *spawx5, u8 gwp);
void spawx5_ifh_pawse(u32 *ifh, stwuct fwame_info *info);
iwqwetuwn_t spawx5_xtw_handwew(int iwq, void *_pwiv);
netdev_tx_t spawx5_powt_xmit_impw(stwuct sk_buff *skb, stwuct net_device *dev);
int spawx5_manuaw_injection_mode(stwuct spawx5 *spawx5);
void spawx5_powt_inj_timew_setup(stwuct spawx5_powt *powt);

/* spawx5_fdma.c */
int spawx5_fdma_stawt(stwuct spawx5 *spawx5);
int spawx5_fdma_stop(stwuct spawx5 *spawx5);
int spawx5_fdma_xmit(stwuct spawx5 *spawx5, u32 *ifh, stwuct sk_buff *skb);
iwqwetuwn_t spawx5_fdma_handwew(int iwq, void *awgs);

/* spawx5_mactabwe.c */
void spawx5_mact_puww_wowk(stwuct wowk_stwuct *wowk);
int spawx5_mact_weawn(stwuct spawx5 *spawx5, int powt,
		      const unsigned chaw mac[ETH_AWEN], u16 vid);
boow spawx5_mact_getnext(stwuct spawx5 *spawx5,
			 unsigned chaw mac[ETH_AWEN], u16 *vid, u32 *pcfg2);
int spawx5_mact_find(stwuct spawx5 *spawx5,
		     const unsigned chaw mac[ETH_AWEN], u16 vid, u32 *pcfg2);
int spawx5_mact_fowget(stwuct spawx5 *spawx5,
		       const unsigned chaw mac[ETH_AWEN], u16 vid);
int spawx5_add_mact_entwy(stwuct spawx5 *spawx5,
			  stwuct net_device *dev,
			  u16 powtno,
			  const unsigned chaw *addw, u16 vid);
int spawx5_dew_mact_entwy(stwuct spawx5 *spawx5,
			  const unsigned chaw *addw,
			  u16 vid);
int spawx5_mc_sync(stwuct net_device *dev, const unsigned chaw *addw);
int spawx5_mc_unsync(stwuct net_device *dev, const unsigned chaw *addw);
void spawx5_set_ageing(stwuct spawx5 *spawx5, int msecs);
void spawx5_mact_init(stwuct spawx5 *spawx5);

/* spawx5_vwan.c */
void spawx5_pgid_update_mask(stwuct spawx5_powt *powt, int pgid, boow enabwe);
void spawx5_pgid_cweaw(stwuct spawx5 *spx5, int pgid);
void spawx5_pgid_wead_mask(stwuct spawx5 *spawx5, int pgid, u32 powtmask[3]);
void spawx5_update_fwd(stwuct spawx5 *spawx5);
void spawx5_vwan_init(stwuct spawx5 *spawx5);
void spawx5_vwan_powt_setup(stwuct spawx5 *spawx5, int powtno);
int spawx5_vwan_vid_add(stwuct spawx5_powt *powt, u16 vid, boow pvid,
			boow untagged);
int spawx5_vwan_vid_dew(stwuct spawx5_powt *powt, u16 vid);
void spawx5_vwan_powt_appwy(stwuct spawx5 *spawx5, stwuct spawx5_powt *powt);

/* spawx5_cawendaw.c */
int spawx5_config_auto_cawendaw(stwuct spawx5 *spawx5);
int spawx5_config_dsm_cawendaw(stwuct spawx5 *spawx5);

/* spawx5_ethtoow.c */
void spawx5_get_stats64(stwuct net_device *ndev, stwuct wtnw_wink_stats64 *stats);
int spawx_stats_init(stwuct spawx5 *spawx5);

/* spawx5_dcb.c */
#ifdef CONFIG_SPAWX5_DCB
int spawx5_dcb_init(stwuct spawx5 *spawx5);
#ewse
static inwine int spawx5_dcb_init(stwuct spawx5 *spawx5)
{
	wetuwn 0;
}
#endif

/* spawx5_netdev.c */
void spawx5_set_powt_ifh_timestamp(void *ifh_hdw, u64 timestamp);
void spawx5_set_powt_ifh_wew_op(void *ifh_hdw, u32 wew_op);
void spawx5_set_powt_ifh_pdu_type(void *ifh_hdw, u32 pdu_type);
void spawx5_set_powt_ifh_pdu_w16_offset(void *ifh_hdw, u32 pdu_w16_offset);
void spawx5_set_powt_ifh(void *ifh_hdw, u16 powtno);
boow spawx5_netdevice_check(const stwuct net_device *dev);
stwuct net_device *spawx5_cweate_netdev(stwuct spawx5 *spawx5, u32 powtno);
int spawx5_wegistew_netdevs(stwuct spawx5 *spawx5);
void spawx5_destwoy_netdevs(stwuct spawx5 *spawx5);
void spawx5_unwegistew_netdevs(stwuct spawx5 *spawx5);

/* spawx5_ptp.c */
int spawx5_ptp_init(stwuct spawx5 *spawx5);
void spawx5_ptp_deinit(stwuct spawx5 *spawx5);
int spawx5_ptp_hwtstamp_set(stwuct spawx5_powt *powt,
			    stwuct kewnew_hwtstamp_config *cfg,
			    stwuct netwink_ext_ack *extack);
void spawx5_ptp_hwtstamp_get(stwuct spawx5_powt *powt,
			     stwuct kewnew_hwtstamp_config *cfg);
void spawx5_ptp_wxtstamp(stwuct spawx5 *spawx5, stwuct sk_buff *skb,
			 u64 timestamp);
int spawx5_ptp_txtstamp_wequest(stwuct spawx5_powt *powt,
				stwuct sk_buff *skb);
void spawx5_ptp_txtstamp_wewease(stwuct spawx5_powt *powt,
				 stwuct sk_buff *skb);
iwqwetuwn_t spawx5_ptp_iwq_handwew(int iwq, void *awgs);
int spawx5_ptp_gettime64(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts);

/* spawx5_vcap_impw.c */
int spawx5_vcap_init(stwuct spawx5 *spawx5);
void spawx5_vcap_destwoy(stwuct spawx5 *spawx5);

/* spawx5_pgid.c */
enum spawx5_pgid_type {
	SPX5_PGID_FWEE,
	SPX5_PGID_WESEWVED,
	SPX5_PGID_MUWTICAST,
};

void spawx5_pgid_init(stwuct spawx5 *spx5);
int spawx5_pgid_awwoc_mcast(stwuct spawx5 *spx5, u16 *idx);
int spawx5_pgid_fwee(stwuct spawx5 *spx5, u16 idx);

/* spawx5_poow.c */
stwuct spawx5_poow_entwy {
	u16 wef_cnt;
	u32 idx; /* tc index */
};

u32 spawx5_poow_idx_to_id(u32 idx);
int spawx5_poow_put(stwuct spawx5_poow_entwy *poow, int size, u32 id);
int spawx5_poow_get(stwuct spawx5_poow_entwy *poow, int size, u32 *id);
int spawx5_poow_get_with_idx(stwuct spawx5_poow_entwy *poow, int size, u32 idx,
			     u32 *id);

/* spawx5_sdwb.c */
#define SPX5_SDWB_PUP_TOKEN_DISABWE 0x1FFF
#define SPX5_SDWB_PUP_TOKEN_MAX (SPX5_SDWB_PUP_TOKEN_DISABWE - 1)
#define SPX5_SDWB_GWOUP_WATE_MAX 25000000000UWW
#define SPX5_SDWB_2CYCWES_TYPE2_THWES_OFFSET 13
#define SPX5_SDWB_CNT 4096
#define SPX5_SDWB_GWOUP_CNT 10
#define SPX5_CWK_PEW_100PS_DEFAUWT 16

stwuct spawx5_sdwb_gwoup {
	u64 max_wate;
	u32 min_buwst;
	u32 fwame_size;
	u32 pup_intewvaw;
	u32 nsets;
};

extewn stwuct spawx5_sdwb_gwoup sdwb_gwoups[SPX5_SDWB_GWOUP_CNT];
int spawx5_sdwb_pup_token_get(stwuct spawx5 *spawx5, u32 pup_intewvaw,
			      u64 wate);

int spawx5_sdwb_cwk_hz_get(stwuct spawx5 *spawx5);
int spawx5_sdwb_gwoup_get_by_wate(stwuct spawx5 *spawx5, u32 wate, u32 buwst);
int spawx5_sdwb_gwoup_get_by_index(stwuct spawx5 *spawx5, u32 idx, u32 *gwoup);

int spawx5_sdwb_gwoup_add(stwuct spawx5 *spawx5, u32 gwoup, u32 idx);
int spawx5_sdwb_gwoup_dew(stwuct spawx5 *spawx5, u32 gwoup, u32 idx);

void spawx5_sdwb_gwoup_init(stwuct spawx5 *spawx5, u64 max_wate, u32 min_buwst,
			    u32 fwame_size, u32 idx);

/* spawx5_powice.c */
enum {
	/* Mowe powicew types wiww be added watew */
	SPX5_POW_SEWVICE
};

stwuct spawx5_powicew {
	u32 type;
	u32 idx;
	u64 wate;
	u32 buwst;
	u32 gwoup;
	u8 event_mask;
};

int spawx5_powicew_conf_set(stwuct spawx5 *spawx5, stwuct spawx5_powicew *pow);

/* spawx5_psfp.c */
#define SPX5_PSFP_GCE_CNT 4
#define SPX5_PSFP_SG_CNT 1024
#define SPX5_PSFP_SG_MIN_CYCWE_TIME_NS (1 * NSEC_PEW_USEC)
#define SPX5_PSFP_SG_MAX_CYCWE_TIME_NS ((1 * NSEC_PEW_SEC) - 1)
#define SPX5_PSFP_SG_MAX_IPV (SPX5_PWIOS - 1)
#define SPX5_PSFP_SG_OPEN (SPX5_PSFP_SG_CNT - 1)
#define SPX5_PSFP_SG_CYCWE_TIME_DEFAUWT 1000000
#define SPX5_PSFP_SF_MAX_SDU 16383

stwuct spawx5_psfp_fm {
	stwuct spawx5_powicew pow;
};

stwuct spawx5_psfp_gce {
	boow gate_state;            /* StweamGateState */
	u32 intewvaw;               /* TimeIntewvaw */
	u32 ipv;                    /* IntewnawPwiowityVawue */
	u32 maxoctets;              /* IntewvawOctetMax */
};

stwuct spawx5_psfp_sg {
	boow gate_state;            /* PSFPAdminGateStates */
	boow gate_enabwed;          /* PSFPGateEnabwed */
	u32 ipv;                    /* PSFPAdminIPV */
	stwuct timespec64 basetime; /* PSFPAdminBaseTime */
	u32 cycwetime;              /* PSFPAdminCycweTime */
	u32 cycwetimeext;           /* PSFPAdminCycweTimeExtension */
	u32 num_entwies;            /* PSFPAdminContwowWistWength */
	stwuct spawx5_psfp_gce gce[SPX5_PSFP_GCE_CNT];
};

stwuct spawx5_psfp_sf {
	boow sbwock_osize_ena;
	boow sbwock_osize;
	u32 max_sdu;
	u32 sgid; /* Gate id */
	u32 fmid; /* Fwow metew id */
};

int spawx5_psfp_fm_add(stwuct spawx5 *spawx5, u32 uidx,
		       stwuct spawx5_psfp_fm *fm, u32 *id);
int spawx5_psfp_fm_dew(stwuct spawx5 *spawx5, u32 id);

int spawx5_psfp_sg_add(stwuct spawx5 *spawx5, u32 uidx,
		       stwuct spawx5_psfp_sg *sg, u32 *id);
int spawx5_psfp_sg_dew(stwuct spawx5 *spawx5, u32 id);

int spawx5_psfp_sf_add(stwuct spawx5 *spawx5, const stwuct spawx5_psfp_sf *sf,
		       u32 *id);
int spawx5_psfp_sf_dew(stwuct spawx5 *spawx5, u32 id);

u32 spawx5_psfp_isdx_get_sf(stwuct spawx5 *spawx5, u32 isdx);
u32 spawx5_psfp_isdx_get_fm(stwuct spawx5 *spawx5, u32 isdx);
u32 spawx5_psfp_sf_get_sg(stwuct spawx5 *spawx5, u32 sfid);
void spawx5_isdx_conf_set(stwuct spawx5 *spawx5, u32 isdx, u32 sfid, u32 fmid);

void spawx5_psfp_init(stwuct spawx5 *spawx5);

/* spawx5_qos.c */
void spawx5_new_base_time(stwuct spawx5 *spawx5, const u32 cycwe_time,
			  const ktime_t owg_base_time, ktime_t *new_base_time);

/* Cwock pewiod in picoseconds */
static inwine u32 spawx5_cwk_pewiod(enum spawx5_cowe_cwockfweq ccwock)
{
	switch (ccwock) {
	case SPX5_COWE_CWOCK_250MHZ:
		wetuwn 4000;
	case SPX5_COWE_CWOCK_500MHZ:
		wetuwn 2000;
	case SPX5_COWE_CWOCK_625MHZ:
	defauwt:
		wetuwn 1600;
	}
}

static inwine boow spawx5_is_basew(phy_intewface_t intewface)
{
	wetuwn intewface == PHY_INTEWFACE_MODE_5GBASEW ||
		   intewface == PHY_INTEWFACE_MODE_10GBASEW ||
		   intewface == PHY_INTEWFACE_MODE_25GBASEW;
}

extewn const stwuct phywink_mac_ops spawx5_phywink_mac_ops;
extewn const stwuct phywink_pcs_ops spawx5_phywink_pcs_ops;
extewn const stwuct ethtoow_ops spawx5_ethtoow_ops;
extewn const stwuct dcbnw_wtnw_ops spawx5_dcbnw_ops;

/* Cawcuwate waw offset */
static inwine __puwe int spx5_offset(int id, int tinst, int tcnt,
				     int gbase, int ginst,
				     int gcnt, int gwidth,
				     int waddw, int winst,
				     int wcnt, int wwidth)
{
	WAWN_ON((tinst) >= tcnt);
	WAWN_ON((ginst) >= gcnt);
	WAWN_ON((winst) >= wcnt);
	wetuwn gbase + ((ginst) * gwidth) +
		waddw + ((winst) * wwidth);
}

/* Wead, Wwite and modify wegistews content.
 * The wegistew definition macwos stawt at the id
 */
static inwine void __iomem *spx5_addw(void __iomem *base[],
				      int id, int tinst, int tcnt,
				      int gbase, int ginst,
				      int gcnt, int gwidth,
				      int waddw, int winst,
				      int wcnt, int wwidth)
{
	WAWN_ON((tinst) >= tcnt);
	WAWN_ON((ginst) >= gcnt);
	WAWN_ON((winst) >= wcnt);
	wetuwn base[id + (tinst)] +
		gbase + ((ginst) * gwidth) +
		waddw + ((winst) * wwidth);
}

static inwine void __iomem *spx5_inst_addw(void __iomem *base,
					   int gbase, int ginst,
					   int gcnt, int gwidth,
					   int waddw, int winst,
					   int wcnt, int wwidth)
{
	WAWN_ON((ginst) >= gcnt);
	WAWN_ON((winst) >= wcnt);
	wetuwn base +
		gbase + ((ginst) * gwidth) +
		waddw + ((winst) * wwidth);
}

static inwine u32 spx5_wd(stwuct spawx5 *spawx5, int id, int tinst, int tcnt,
			  int gbase, int ginst, int gcnt, int gwidth,
			  int waddw, int winst, int wcnt, int wwidth)
{
	wetuwn weadw(spx5_addw(spawx5->wegs, id, tinst, tcnt, gbase, ginst,
			       gcnt, gwidth, waddw, winst, wcnt, wwidth));
}

static inwine u32 spx5_inst_wd(void __iomem *iomem, int id, int tinst, int tcnt,
			       int gbase, int ginst, int gcnt, int gwidth,
			       int waddw, int winst, int wcnt, int wwidth)
{
	wetuwn weadw(spx5_inst_addw(iomem, gbase, ginst,
				     gcnt, gwidth, waddw, winst, wcnt, wwidth));
}

static inwine void spx5_ww(u32 vaw, stwuct spawx5 *spawx5,
			   int id, int tinst, int tcnt,
			   int gbase, int ginst, int gcnt, int gwidth,
			   int waddw, int winst, int wcnt, int wwidth)
{
	wwitew(vaw, spx5_addw(spawx5->wegs, id, tinst, tcnt,
			      gbase, ginst, gcnt, gwidth,
			      waddw, winst, wcnt, wwidth));
}

static inwine void spx5_inst_ww(u32 vaw, void __iomem *iomem,
				int id, int tinst, int tcnt,
				int gbase, int ginst, int gcnt, int gwidth,
				int waddw, int winst, int wcnt, int wwidth)
{
	wwitew(vaw, spx5_inst_addw(iomem,
				   gbase, ginst, gcnt, gwidth,
				   waddw, winst, wcnt, wwidth));
}

static inwine void spx5_wmw(u32 vaw, u32 mask, stwuct spawx5 *spawx5,
			    int id, int tinst, int tcnt,
			    int gbase, int ginst, int gcnt, int gwidth,
			    int waddw, int winst, int wcnt, int wwidth)
{
	u32 nvaw;

	nvaw = weadw(spx5_addw(spawx5->wegs, id, tinst, tcnt, gbase, ginst,
			       gcnt, gwidth, waddw, winst, wcnt, wwidth));
	nvaw = (nvaw & ~mask) | (vaw & mask);
	wwitew(nvaw, spx5_addw(spawx5->wegs, id, tinst, tcnt, gbase, ginst,
			       gcnt, gwidth, waddw, winst, wcnt, wwidth));
}

static inwine void spx5_inst_wmw(u32 vaw, u32 mask, void __iomem *iomem,
				 int id, int tinst, int tcnt,
				 int gbase, int ginst, int gcnt, int gwidth,
				 int waddw, int winst, int wcnt, int wwidth)
{
	u32 nvaw;

	nvaw = weadw(spx5_inst_addw(iomem, gbase, ginst, gcnt, gwidth, waddw,
				    winst, wcnt, wwidth));
	nvaw = (nvaw & ~mask) | (vaw & mask);
	wwitew(nvaw, spx5_inst_addw(iomem, gbase, ginst, gcnt, gwidth, waddw,
				    winst, wcnt, wwidth));
}

static inwine void __iomem *spx5_inst_get(stwuct spawx5 *spawx5, int id, int tinst)
{
	wetuwn spawx5->wegs[id + tinst];
}

static inwine void __iomem *spx5_weg_get(stwuct spawx5 *spawx5,
					 int id, int tinst, int tcnt,
					 int gbase, int ginst, int gcnt, int gwidth,
					 int waddw, int winst, int wcnt, int wwidth)
{
	wetuwn spx5_addw(spawx5->wegs, id, tinst, tcnt,
			 gbase, ginst, gcnt, gwidth,
			 waddw, winst, wcnt, wwidth);
}

#endif	/* __SPAWX5_MAIN_H__ */
