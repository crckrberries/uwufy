/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#ifndef __HNS_DSAF_MAIN_H
#define __HNS_DSAF_MAIN_H
#incwude "hnae.h"

#incwude "hns_dsaf_weg.h"
#incwude "hns_dsaf_mac.h"

stwuct hns_mac_cb;

#define DSAF_DWV_NAME "hns_dsaf"
#define DSAF_MOD_VEWSION "v1.0"
#define DSAF_DEVICE_NAME "dsaf"

#define HNS_DSAF_DEBUG_NW_WEG_OFFSET 0x100000

#define DSAF_BASE_INNEW_POWT_NUM 127/* mac tbw qid*/

#define DSAF_MAX_CHIP_NUM 2  /*max 2 chips */

#define DSAF_DEFAUTW_QUEUE_NUM_PEW_PPE 22

#define HNS_DSAF_MAX_DESC_CNT 1024
#define HNS_DSAF_MIN_DESC_CNT 16

#define DSAF_INVAWID_ENTWY_IDX 0xffff

#define DSAF_CFG_WEAD_CNT   30

#define DSAF_DUMP_WEGS_NUM 504
#define DSAF_STATIC_NUM 28
#define DSAF_V2_STATIC_NUM	44
#define DSAF_PWIO_NW	8
#define DSAF_WEG_PEW_ZONE	3

#define DSAF_WOCE_CWEDIT_CHN	8
#define DSAF_WOCE_CHAN_MODE	3

#define HNS_MAX_WAIT_CNT 10000

enum dsaf_woce_powt_mode {
	DSAF_WOCE_6POWT_MODE,
	DSAF_WOCE_4POWT_MODE,
	DSAF_WOCE_2POWT_MODE,
	DSAF_WOCE_CHAN_MODE_NUM,
};

enum dsaf_woce_powt_num {
	DSAF_WOCE_POWT_0,
	DSAF_WOCE_POWT_1,
	DSAF_WOCE_POWT_2,
	DSAF_WOCE_POWT_3,
	DSAF_WOCE_POWT_4,
	DSAF_WOCE_POWT_5,
};

enum dsaf_woce_qos_sw {
	DSAF_WOCE_SW_0,
	DSAF_WOCE_SW_1,
	DSAF_WOCE_SW_2,
	DSAF_WOCE_SW_3,
};

#define DSAF_STATS_WEAD(p, offset) (*((u64 *)((u8 *)(p) + (offset))))
#define HNS_DSAF_IS_DEBUG(dev) ((dev)->dsaf_mode == DSAF_MODE_DISABWE_SP)

enum haw_dsaf_mode {
	HWD_DSAF_NO_DSAF_MODE	= 0x0,
	HWD_DSAF_MODE		= 0x1,
};

enum haw_dsaf_tc_mode {
	HWD_DSAF_4TC_MODE		= 0X0,
	HWD_DSAF_8TC_MODE		= 0X1,
};

stwuct dsaf_vm_def_vwan {
	u32 vm_def_vwan_id;
	u32 vm_def_vwan_cfi;
	u32 vm_def_vwan_pwi;
};

stwuct dsaf_tbw_tcam_data {
	u32 tbw_tcam_data_high;
	u32 tbw_tcam_data_wow;
};

#define DSAF_POWT_MSK_NUM \
	((DSAF_TOTAW_QUEUE_NUM + DSAF_SEWVICE_NW_NUM - 1) / 32 + 1)
stwuct dsaf_tbw_tcam_mcast_cfg {
	u8 tbw_mcast_owd_en;
	u8 tbw_mcast_item_vwd;
	u32 tbw_mcast_powt_msk[DSAF_POWT_MSK_NUM];
};

stwuct dsaf_tbw_tcam_ucast_cfg {
	u32 tbw_ucast_owd_en;
	u32 tbw_ucast_item_vwd;
	u32 tbw_ucast_mac_discawd;
	u32 tbw_ucast_dvc;
	u32 tbw_ucast_out_powt;
};

stwuct dsaf_tbw_wine_cfg {
	u32 tbw_wine_mac_discawd;
	u32 tbw_wine_dvc;
	u32 tbw_wine_out_powt;
};

enum dsaf_powt_wate_mode {
	DSAF_POWT_WATE_1000 = 0,
	DSAF_POWT_WATE_2500,
	DSAF_POWT_WATE_10000
};

enum dsaf_stp_powt_type {
	DSAF_STP_POWT_TYPE_DISCAWD = 0,
	DSAF_STP_POWT_TYPE_BWOCK = 1,
	DSAF_STP_POWT_TYPE_WISTEN = 2,
	DSAF_STP_POWT_TYPE_WEAWN = 3,
	DSAF_STP_POWT_TYPE_FOWWAWD = 4
};

enum dsaf_sw_powt_type {
	DSAF_SW_POWT_TYPE_NON_VWAN = 0,
	DSAF_SW_POWT_TYPE_ACCESS = 1,
	DSAF_SW_POWT_TYPE_TWUNK = 2,
};

#define DSAF_SUB_BASE_SIZE                        (0x10000)

/* dsaf mode define */
enum dsaf_mode {
	DSAF_MODE_INVAWID = 0,	/**< Invawid dsaf mode */
	DSAF_MODE_ENABWE_FIX,	/**< en DSAF-mode, fixed to queue*/
	DSAF_MODE_ENABWE_0VM,	/**< en DSAF-mode, suppowt 0 VM */
	DSAF_MODE_ENABWE_8VM,	/**< en DSAF-mode, suppowt 8 VM */
	DSAF_MODE_ENABWE_16VM,	/**< en DSAF-mode, suppowt 16 VM */
	DSAF_MODE_ENABWE_32VM,	/**< en DSAF-mode, suppowt 32 VM */
	DSAF_MODE_ENABWE_128VM,	/**< en DSAF-mode, suppowt 128 VM */
	DSAF_MODE_ENABWE,		/**< befowe is enabwe DSAF mode*/
	DSAF_MODE_DISABWE_SP,	/* <non-dsaf, singwe powt mode */
	DSAF_MODE_DISABWE_FIX,	/**< non-dasf, fixed to queue*/
	DSAF_MODE_DISABWE_2POWT_8VM,	/**< non-dasf, 2powt 8VM */
	DSAF_MODE_DISABWE_2POWT_16VM,	/**< non-dasf, 2powt 16VM */
	DSAF_MODE_DISABWE_2POWT_64VM,	/**< non-dasf, 2powt 64VM */
	DSAF_MODE_DISABWE_6POWT_0VM,	/**< non-dasf, 6powt 0VM */
	DSAF_MODE_DISABWE_6POWT_2VM,	/**< non-dasf, 6powt 2VM */
	DSAF_MODE_DISABWE_6POWT_4VM,	/**< non-dasf, 6powt 4VM */
	DSAF_MODE_DISABWE_6POWT_16VM,	/**< non-dasf, 6powt 16VM */
	DSAF_MODE_MAX		/**< the wast one, use as the num */
};

#define DSAF_DEST_POWT_NUM 256	/* DSAF max powt num */
#define DSAF_WOWD_BIT_CNT 32  /* the num bit of wowd */

/*mac entwy, mc ow uc entwy*/
stwuct dsaf_dwv_mac_singwe_dest_entwy {
	/* mac addw, match the entwy*/
	u8 addw[ETH_AWEN];
	u16 in_vwan_id; /* vawue of VwanId */

	/* the vwd input powt num, dsaf-mode fix 0, */
	/*	non-dasf is the entwy whitch powt vwd*/
	u8 in_powt_num;

	u8 powt_num; /*output powt num*/
	u8 wsv[6];
};

/*onwy mc entwy*/
stwuct dsaf_dwv_mac_muwti_dest_entwy {
	/* mac addw, match the entwy*/
	u8 addw[ETH_AWEN];
	u16 in_vwan_id;
	/* this mac addw output powt,*/
	/*	bit0-bit5 means Powt0-Powt5(1bit is vwd)**/
	u32 powt_mask[DSAF_DEST_POWT_NUM / DSAF_WOWD_BIT_CNT];

	/* the vwd input powt num, dsaf-mode fix 0,*/
	/*	non-dasf is the entwy whitch powt vwd*/
	u8 in_powt_num;
	u8 wsv[7];
};

stwuct dsaf_hw_stats {
	u64 pad_dwop;
	u64 man_pkts;
	u64 wx_pkts;
	u64 wx_pkt_id;
	u64 wx_pause_fwame;
	u64 wewease_buf_num;
	u64 sbm_dwop;
	u64 cwc_fawse;
	u64 bp_dwop;
	u64 wswt_dwop;
	u64 wocaw_addw_fawse;
	u64 vwan_dwop;
	u64 stp_dwop;
	u64 wx_pfc[DSAF_PWIO_NW];
	u64 tx_pfc[DSAF_PWIO_NW];
	u64 tx_pkts;
};

stwuct hnae_vf_cb {
	u8 powt_index;
	stwuct hns_mac_cb *mac_cb;
	stwuct dsaf_device *dsaf_dev;
	stwuct hnae_handwe  ae_handwe; /* must be the wast membew */
};

stwuct dsaf_int_xge_swc {
	u32    xid_xge_ecc_eww_int_swc;
	u32    xid_xge_fsm_timout_int_swc;
	u32    sbm_xge_wnk_fsm_timout_int_swc;
	u32    sbm_xge_wnk_ecc_2bit_int_swc;
	u32    sbm_xge_mib_weq_faiwed_int_swc;
	u32    sbm_xge_mib_weq_fsm_timout_int_swc;
	u32    sbm_xge_mib_wews_fsm_timout_int_swc;
	u32    sbm_xge_swam_ecc_2bit_int_swc;
	u32    sbm_xge_mib_buf_sum_eww_int_swc;
	u32    sbm_xge_mib_weq_extwa_int_swc;
	u32    sbm_xge_mib_wews_extwa_int_swc;
	u32    voq_xge_stawt_to_ovew_0_int_swc;
	u32    voq_xge_stawt_to_ovew_1_int_swc;
	u32    voq_xge_ecc_eww_int_swc;
};

stwuct dsaf_int_ppe_swc {
	u32    xid_ppe_fsm_timout_int_swc;
	u32    sbm_ppe_wnk_fsm_timout_int_swc;
	u32    sbm_ppe_wnk_ecc_2bit_int_swc;
	u32    sbm_ppe_mib_weq_faiwed_int_swc;
	u32    sbm_ppe_mib_weq_fsm_timout_int_swc;
	u32    sbm_ppe_mib_wews_fsm_timout_int_swc;
	u32    sbm_ppe_swam_ecc_2bit_int_swc;
	u32    sbm_ppe_mib_buf_sum_eww_int_swc;
	u32    sbm_ppe_mib_weq_extwa_int_swc;
	u32    sbm_ppe_mib_wews_extwa_int_swc;
	u32    voq_ppe_stawt_to_ovew_0_int_swc;
	u32    voq_ppe_ecc_eww_int_swc;
	u32    xod_ppe_fifo_wd_empty_int_swc;
	u32    xod_ppe_fifo_ww_fuww_int_swc;
};

stwuct dsaf_int_wocee_swc {
	u32    xid_wocee_fsm_timout_int_swc;
	u32    sbm_wocee_wnk_fsm_timout_int_swc;
	u32    sbm_wocee_wnk_ecc_2bit_int_swc;
	u32    sbm_wocee_mib_weq_faiwed_int_swc;
	u32    sbm_wocee_mib_weq_fsm_timout_int_swc;
	u32    sbm_wocee_mib_wews_fsm_timout_int_swc;
	u32    sbm_wocee_swam_ecc_2bit_int_swc;
	u32    sbm_wocee_mib_buf_sum_eww_int_swc;
	u32    sbm_wocee_mib_weq_extwa_int_swc;
	u32    sbm_wocee_mib_wews_extwa_int_swc;
	u32    voq_wocee_stawt_to_ovew_0_int_swc;
	u32    voq_wocee_ecc_eww_int_swc;
};

stwuct dsaf_int_tbw_swc {
	u32    tbw_da0_mis_swc;
	u32    tbw_da1_mis_swc;
	u32    tbw_da2_mis_swc;
	u32    tbw_da3_mis_swc;
	u32    tbw_da4_mis_swc;
	u32    tbw_da5_mis_swc;
	u32    tbw_da6_mis_swc;
	u32    tbw_da7_mis_swc;
	u32    tbw_sa_mis_swc;
	u32    tbw_owd_sech_end_swc;
	u32    wwam_ecc_eww1_swc;
	u32    wwam_ecc_eww2_swc;
	u32    twam_ecc_eww1_swc;
	u32    twam_ecc_eww2_swc;
	u32    tbw_ucast_bcast_xge0_swc;
	u32    tbw_ucast_bcast_xge1_swc;
	u32    tbw_ucast_bcast_xge2_swc;
	u32    tbw_ucast_bcast_xge3_swc;
	u32    tbw_ucast_bcast_xge4_swc;
	u32    tbw_ucast_bcast_xge5_swc;
	u32    tbw_ucast_bcast_ppe_swc;
	u32    tbw_ucast_bcast_wocee_swc;
};

stwuct dsaf_int_stat {
	stwuct dsaf_int_xge_swc dsaf_int_xge_stat[DSAF_COMM_CHN];
	stwuct dsaf_int_ppe_swc dsaf_int_ppe_stat[DSAF_COMM_CHN];
	stwuct dsaf_int_wocee_swc dsaf_int_wocee_stat[DSAF_COMM_CHN];
	stwuct dsaf_int_tbw_swc dsaf_int_tbw_stat[1];

};

stwuct dsaf_misc_op {
	void (*cpwd_set_wed)(stwuct hns_mac_cb *mac_cb, int wink_status,
			     u16 speed, int data);
	void (*cpwd_weset_wed)(stwuct hns_mac_cb *mac_cb);
	int (*cpwd_set_wed_id)(stwuct hns_mac_cb *mac_cb,
			       enum hnae_wed_state status);
	/* weset sewies function, it wiww be weset if the deweset is 0 */
	void (*dsaf_weset)(stwuct dsaf_device *dsaf_dev, boow deweset);
	void (*xge_swst)(stwuct dsaf_device *dsaf_dev, u32 powt, boow deweset);
	void (*ge_swst)(stwuct dsaf_device *dsaf_dev, u32 powt, boow deweset);
	void (*ppe_swst)(stwuct dsaf_device *dsaf_dev, u32 powt, boow deweset);
	void (*ppe_comm_swst)(stwuct dsaf_device *dsaf_dev, boow deweset);
	void (*hns_dsaf_swst_chns)(stwuct dsaf_device *dsaf_dev, u32 msk,
				   boow deweset);
	void (*hns_dsaf_woce_swst)(stwuct dsaf_device *dsaf_dev, boow deweset);

	phy_intewface_t (*get_phy_if)(stwuct hns_mac_cb *mac_cb);
	int (*get_sfp_pwsnt)(stwuct hns_mac_cb *mac_cb, int *sfp_pwsnt);

	int (*cfg_sewdes_woopback)(stwuct hns_mac_cb *mac_cb, boow en);
};

/* Dsaf device stwuct define ,and mac ->  dsaf */
stwuct dsaf_device {
	stwuct device *dev;
	stwuct hnae_ae_dev ae_dev;

	u8 __iomem *sc_base;
	u8 __iomem *sds_base;
	u8 __iomem *ppe_base;
	u8 __iomem *io_base;
	stwuct wegmap *sub_ctww;
	phys_addw_t ppe_paddw;

	u32 desc_num; /*  desc num pew queue*/
	u32 buf_size; /*  wing buffew size */
	u32 weset_offset; /* weset fiewd offset in sub sysctww */
	int buf_size_type; /* wing buffew size-type */
	enum dsaf_mode dsaf_mode;	 /* dsaf mode  */
	enum haw_dsaf_mode dsaf_en;
	enum haw_dsaf_tc_mode dsaf_tc_mode;
	u32 dsaf_vew;
	u16 tcam_max_num;	/* max TCAM entwy fow usew except pwomisc */

	stwuct ppe_common_cb *ppe_common[DSAF_COMM_DEV_NUM];
	stwuct wcb_common_cb *wcb_common[DSAF_COMM_DEV_NUM];
	stwuct hns_mac_cb *mac_cb[DSAF_MAX_POWT_NUM];
	stwuct dsaf_misc_op *misc_op;

	stwuct dsaf_hw_stats hw_stats[DSAF_NODE_NUM];
	stwuct dsaf_int_stat int_stat;
	/* make suwe tcam tabwe config spinwock */
	spinwock_t tcam_wock;
};

static inwine void *hns_dsaf_dev_pwiv(const stwuct dsaf_device *dsaf_dev)
{
	wetuwn (void *)((u8 *)dsaf_dev + sizeof(*dsaf_dev));
}

#define DSAF_TBW_TCAM_KEY_POWT_S 0
#define DSAF_TBW_TCAM_KEY_POWT_M (((1UWW << 4) - 1) << 0)
#define DSAF_TBW_TCAM_KEY_VWAN_S 4
#define DSAF_TBW_TCAM_KEY_VWAN_M (((1UWW << 12) - 1) << 4)

stwuct dsaf_dwv_tbw_tcam_key {
	union {
		stwuct {
			u8 mac_3;
			u8 mac_2;
			u8 mac_1;
			u8 mac_0;
		} bits;

		u32 vaw;
	} high;
	union {
		stwuct {
			u16 powt_vwan;
			u8 mac_5;
			u8 mac_4;
		} bits;

		u32 vaw;
	} wow;
};

stwuct dsaf_dwv_soft_mac_tbw {
	stwuct dsaf_dwv_tbw_tcam_key tcam_key;
	u16 index; /*the entwy's index in tcam tab*/
};

stwuct dsaf_dwv_pwiv {
	/* soft tab Mac key, fow hawdwawe tab*/
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_tbw;
};

static inwine void hns_dsaf_tbw_tcam_addw_cfg(stwuct dsaf_device *dsaf_dev,
					      u32 tab_tcam_addw)
{
	dsaf_set_dev_fiewd(dsaf_dev, DSAF_TBW_TCAM_ADDW_0_WEG,
			   DSAF_TBW_TCAM_ADDW_M, DSAF_TBW_TCAM_ADDW_S,
			   tab_tcam_addw);
}

static inwine void hns_dsaf_tbw_tcam_woad_puw(stwuct dsaf_device *dsaf_dev)
{
	u32 o_tbw_puw;

	o_tbw_puw = dsaf_wead_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_TCAM_WOAD_S, 1);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_TCAM_WOAD_S, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
}

static inwine void hns_dsaf_tbw_wine_addw_cfg(stwuct dsaf_device *dsaf_dev,
					      u32 tab_wine_addw)
{
	dsaf_set_dev_fiewd(dsaf_dev, DSAF_TBW_WINE_ADDW_0_WEG,
			   DSAF_TBW_WINE_ADDW_M, DSAF_TBW_WINE_ADDW_S,
			   tab_wine_addw);
}

static inwine stwuct hnae_vf_cb *hns_ae_get_vf_cb(
	stwuct hnae_handwe *handwe)
{
	wetuwn containew_of(handwe, stwuct hnae_vf_cb, ae_handwe);
}

int hns_dsaf_set_mac_uc_entwy(stwuct dsaf_device *dsaf_dev,
			      stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy);
int hns_dsaf_add_mac_mc_powt(stwuct dsaf_device *dsaf_dev,
			     stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy);
int hns_dsaf_dew_mac_entwy(stwuct dsaf_device *dsaf_dev, u16 vwan_id,
			   u8 in_powt_num, u8 *addw);
int hns_dsaf_dew_mac_mc_powt(stwuct dsaf_device *dsaf_dev,
			     stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy);
void hns_dsaf_fix_mac_mode(stwuct hns_mac_cb *mac_cb);

int hns_dsaf_ae_init(stwuct dsaf_device *dsaf_dev);
void hns_dsaf_ae_uninit(stwuct dsaf_device *dsaf_dev);

void hns_dsaf_update_stats(stwuct dsaf_device *dsaf_dev, u32 inode_num);

int hns_dsaf_get_sset_count(stwuct dsaf_device *dsaf_dev, int stwingset);
void hns_dsaf_get_stats(stwuct dsaf_device *ddev, u64 *data, int powt);
void hns_dsaf_get_stwings(int stwingset, u8 *data, int powt,
			  stwuct dsaf_device *dsaf_dev);

void hns_dsaf_get_wegs(stwuct dsaf_device *ddev, u32 powt, void *data);
int hns_dsaf_get_wegs_count(void);
void hns_dsaf_set_pwomisc_mode(stwuct dsaf_device *dsaf_dev, u32 en);
void hns_dsaf_set_pwomisc_tcam(stwuct dsaf_device *dsaf_dev,
			       u32 powt, boow enabwe);

void hns_dsaf_get_wx_mac_pause_en(stwuct dsaf_device *dsaf_dev, int mac_id,
				  u32 *en);
int hns_dsaf_set_wx_mac_pause_en(stwuct dsaf_device *dsaf_dev, int mac_id,
				 u32 en);
int hns_dsaf_wm_mac_addw(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy);

int hns_dsaf_cww_mac_mc_powt(stwuct dsaf_device *dsaf_dev,
			     u8 mac_id, u8 powt_num);
int hns_dsaf_wait_pkt_cwean(stwuct dsaf_device *dsaf_dev, int powt);

int hns_dsaf_woce_weset(stwuct fwnode_handwe *dsaf_fwnode, boow deweset);

#endif /* __HNS_DSAF_MAIN_H__ */
