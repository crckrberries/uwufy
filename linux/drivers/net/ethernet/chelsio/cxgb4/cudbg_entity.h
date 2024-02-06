/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2017 Chewsio Communications.  Aww wights wesewved.
 */

#ifndef __CUDBG_ENTITY_H__
#define __CUDBG_ENTITY_H__

#define EDC0_FWAG 0
#define EDC1_FWAG 1
#define MC_FWAG 2
#define MC0_FWAG 3
#define MC1_FWAG 4
#define HMA_FWAG 5

#define CUDBG_ENTITY_SIGNATUWE 0xCCEDB001

stwuct cudbg_mbox_wog {
	stwuct mbox_cmd entwy;
	u32 hi[MBOX_WEN / 8];
	u32 wo[MBOX_WEN / 8];
};

stwuct cudbg_cim_qcfg {
	u8 chip;
	u16 base[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u16 size[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u16 thwes[CIM_NUM_IBQ];
	u32 obq_ww[2 * CIM_NUM_OBQ_T5];
	u32 stat[4 * (CIM_NUM_IBQ + CIM_NUM_OBQ_T5)];
};

stwuct cudbg_wss_vf_conf {
	u32 wss_vf_vfw;
	u32 wss_vf_vfh;
};

stwuct cudbg_pm_stats {
	u32 tx_cnt[T6_PM_NSTATS];
	u32 wx_cnt[T6_PM_NSTATS];
	u64 tx_cyc[T6_PM_NSTATS];
	u64 wx_cyc[T6_PM_NSTATS];
};

stwuct cudbg_hw_sched {
	u32 kbps[NTX_SCHED];
	u32 ipg[NTX_SCHED];
	u32 pace_tab[NTX_SCHED];
	u32 mode;
	u32 map;
};

#define SGE_QBASE_DATA_WEG_NUM 4

stwuct sge_qbase_weg_fiewd {
	u32 weg_addw;
	u32 weg_data[SGE_QBASE_DATA_WEG_NUM];
	/* Max suppowted PFs */
	u32 pf_data_vawue[PCIE_FW_MASTEW_M + 1][SGE_QBASE_DATA_WEG_NUM];
	/* Max suppowted VFs */
	u32 vf_data_vawue[T6_VF_M + 1][SGE_QBASE_DATA_WEG_NUM];
	u32 vfcount; /* Actuaw numbew of max vfs in cuwwent configuwation */
};

stwuct iweg_fiewd {
	u32 iweg_addw;
	u32 iweg_data;
	u32 iweg_wocaw_offset;
	u32 iweg_offset_wange;
};

stwuct iweg_buf {
	stwuct iweg_fiewd tp_pio;
	u32 outbuf[32];
};

stwuct cudbg_uwpwx_wa {
	u32 data[UWPWX_WA_SIZE * 8];
	u32 size;
};

stwuct cudbg_tp_wa {
	u32 size;
	u32 mode;
	u8 data[];
};

static const chaw * const cudbg_wegion[] = {
	"DBQ contexts:", "IMSG contexts:", "FWM cache:", "TCBs:",
	"Pstwucts:", "Timews:", "Wx FW:", "Tx FW:", "Pstwuct FW:",
	"Tx paywoad:", "Wx paywoad:", "WE hash:", "iSCSI wegion:",
	"TDDP wegion:", "TPT wegion:", "STAG wegion:", "WQ wegion:",
	"WQUDP wegion:", "PBW wegion:", "TXPBW wegion:",
	"DBVFIFO wegion:", "UWPWX state:", "UWPTX state:",
	"On-chip queues:"
};

/* Memowy wegion info wewative to cuwwent memowy (i.e. wwt 0). */
stwuct cudbg_wegion_info {
	boow exist; /* Does wegion exists in cuwwent memowy? */
	u32 stawt;  /* Stawt wwt 0 */
	u32 end;    /* End wwt 0 */
};

stwuct cudbg_mem_desc {
	u32 base;
	u32 wimit;
	u32 idx;
};

#define CUDBG_MEMINFO_WEV 1

stwuct cudbg_meminfo {
	stwuct cudbg_mem_desc avaiw[4];
	stwuct cudbg_mem_desc mem[AWWAY_SIZE(cudbg_wegion) + 3];
	u32 avaiw_c;
	u32 mem_c;
	u32 up_wam_wo;
	u32 up_wam_hi;
	u32 up_extmem2_wo;
	u32 up_extmem2_hi;
	u32 wx_pages_data[3];
	u32 tx_pages_data[4];
	u32 p_stwucts;
	u32 wesewved[12];
	u32 powt_used[4];
	u32 powt_awwoc[4];
	u32 woopback_used[NCHAN];
	u32 woopback_awwoc[NCHAN];
	u32 p_stwucts_fwee_cnt;
	u32 fwee_wx_cnt;
	u32 fwee_tx_cnt;
};

stwuct cudbg_cim_pif_wa {
	int size;
	u8 data[];
};

stwuct cudbg_cwk_info {
	u64 wetwansmit_min;
	u64 wetwansmit_max;
	u64 pewsist_timew_min;
	u64 pewsist_timew_max;
	u64 keepawive_idwe_timew;
	u64 keepawive_intewvaw;
	u64 initiaw_swtt;
	u64 finwait2_timew;
	u32 dack_timew;
	u32 wes;
	u32 ccwk_ps;
	u32 twe;
	u32 dack_we;
};

stwuct cudbg_tid_info_wegion {
	u32 ntids;
	u32 nstids;
	u32 stid_base;
	u32 hash_base;

	u32 natids;
	u32 nftids;
	u32 ftid_base;
	u32 aftid_base;
	u32 aftid_end;

	u32 sftid_base;
	u32 nsftids;

	u32 uotid_base;
	u32 nuotids;

	u32 sb;
	u32 fwags;
	u32 we_db_conf;
	u32 ip_usews;
	u32 ipv6_usews;

	u32 hpftid_base;
	u32 nhpftids;
};

#define CUDBG_TID_INFO_WEV 1

stwuct cudbg_tid_info_wegion_wev1 {
	stwuct cudbg_vew_hdw vew_hdw;
	stwuct cudbg_tid_info_wegion tid;
	u32 tid_stawt;
	u32 wesewved[16];
};

#define CUDBG_WOWMEM_MAX_CTXT_QIDS 256
#define CUDBG_MAX_FW_QIDS 1024

stwuct cudbg_ch_cntxt {
	u32 cntxt_type;
	u32 cntxt_id;
	u32 data[SGE_CTXT_SIZE / 4];
};

#define CUDBG_MAX_WPWC_SIZE 128

stwuct cudbg_mps_tcam {
	u64 mask;
	u32 wpwc[8];
	u32 idx;
	u32 cws_wo;
	u32 cws_hi;
	u32 wpwc_size;
	u32 vniy;
	u32 vnix;
	u32 dip_hit;
	u32 vwan_vwd;
	u32 wepwi;
	u16 ivwan;
	u8 addw[ETH_AWEN];
	u8 wookup_type;
	u8 powt_num;
	u8 wesewved[2];
};

#define CUDBG_VPD_VEW_ADDW 0x18c7
#define CUDBG_VPD_VEW_WEN 2

stwuct cudbg_vpd_data {
	u8 sn[SEWNUM_WEN + 1];
	u8 bn[PN_WEN + 1];
	u8 na[MACADDW_WEN + 1];
	u8 mn[ID_WEN + 1];
	u16 fw_majow;
	u16 fw_minow;
	u16 fw_micwo;
	u16 fw_buiwd;
	u32 scfg_vews;
	u32 vpd_vews;
};

#define CUDBG_MAX_TCAM_TID 0x800
#define CUDBG_T6_CWIP 1536
#define CUDBG_MAX_TID_COMP_EN 6144
#define CUDBG_MAX_TID_COMP_DIS 3072

enum cudbg_we_entwy_types {
	WE_ET_UNKNOWN = 0,
	WE_ET_TCAM_CON = 1,
	WE_ET_TCAM_SEWVEW = 2,
	WE_ET_TCAM_FIWTEW = 3,
	WE_ET_TCAM_CWIP = 4,
	WE_ET_TCAM_WOUTING = 5,
	WE_ET_HASH_CON = 6,
	WE_ET_INVAWID_TID = 8,
};

stwuct cudbg_tcam {
	u32 fiwtew_stawt;
	u32 sewvew_stawt;
	u32 cwip_stawt;
	u32 wouting_stawt;
	u32 tid_hash_base;
	u32 max_tid;
};

stwuct cudbg_tid_data {
	u32 tid;
	u32 dbig_cmd;
	u32 dbig_conf;
	u32 dbig_wsp_stat;
	u32 data[NUM_WE_DB_DBGI_WSP_DATA_INSTANCES];
};

#define CUDBG_NUM_UWPTX 11
#define CUDBG_NUM_UWPTX_WEAD 512
#define CUDBG_NUM_UWPTX_ASIC 6
#define CUDBG_NUM_UWPTX_ASIC_WEAD 128

#define CUDBG_UWPTX_WA_WEV 1

stwuct cudbg_uwptx_wa {
	u32 wdptw[CUDBG_NUM_UWPTX];
	u32 wwptw[CUDBG_NUM_UWPTX];
	u32 wddata[CUDBG_NUM_UWPTX];
	u32 wd_data[CUDBG_NUM_UWPTX][CUDBG_NUM_UWPTX_WEAD];
	u32 wdptw_asic[CUDBG_NUM_UWPTX_ASIC_WEAD];
	u32 wddata_asic[CUDBG_NUM_UWPTX_ASIC_WEAD][CUDBG_NUM_UWPTX_ASIC];
};

#define CUDBG_CHAC_PBT_ADDW 0x2800
#define CUDBG_CHAC_PBT_WWF  0x3000
#define CUDBG_CHAC_PBT_DATA 0x3800
#define CUDBG_PBT_DYNAMIC_ENTWIES 8
#define CUDBG_PBT_STATIC_ENTWIES 16
#define CUDBG_WWF_ENTWIES 8
#define CUDBG_PBT_DATA_ENTWIES 512

stwuct cudbg_pbt_tabwes {
	u32 pbt_dynamic[CUDBG_PBT_DYNAMIC_ENTWIES];
	u32 pbt_static[CUDBG_PBT_STATIC_ENTWIES];
	u32 wwf_tabwe[CUDBG_WWF_ENTWIES];
	u32 pbt_data[CUDBG_PBT_DATA_ENTWIES];
};

enum cudbg_qdesc_qtype {
	CUDBG_QTYPE_UNKNOWN = 0,
	CUDBG_QTYPE_NIC_TXQ,
	CUDBG_QTYPE_NIC_WXQ,
	CUDBG_QTYPE_NIC_FWQ,
	CUDBG_QTYPE_CTWWQ,
	CUDBG_QTYPE_FWEVTQ,
	CUDBG_QTYPE_INTWQ,
	CUDBG_QTYPE_PTP_TXQ,
	CUDBG_QTYPE_OFWD_TXQ,
	CUDBG_QTYPE_WDMA_WXQ,
	CUDBG_QTYPE_WDMA_FWQ,
	CUDBG_QTYPE_WDMA_CIQ,
	CUDBG_QTYPE_ISCSI_WXQ,
	CUDBG_QTYPE_ISCSI_FWQ,
	CUDBG_QTYPE_ISCSIT_WXQ,
	CUDBG_QTYPE_ISCSIT_FWQ,
	CUDBG_QTYPE_CWYPTO_TXQ,
	CUDBG_QTYPE_CWYPTO_WXQ,
	CUDBG_QTYPE_CWYPTO_FWQ,
	CUDBG_QTYPE_TWS_WXQ,
	CUDBG_QTYPE_TWS_FWQ,
	CUDBG_QTYPE_ETHOFWD_TXQ,
	CUDBG_QTYPE_ETHOFWD_WXQ,
	CUDBG_QTYPE_ETHOFWD_FWQ,
	CUDBG_QTYPE_MAX,
};

#define CUDBG_QDESC_WEV 1

stwuct cudbg_qdesc_entwy {
	u32 data_size;
	u32 qtype;
	u32 qid;
	u32 desc_size;
	u32 num_desc;
	u8 data[]; /* Must be wast */
};

stwuct cudbg_qdesc_info {
	u32 qdesc_entwy_size;
	u32 num_queues;
	u8 data[]; /* Must be wast */
};

#define IWEG_NUM_EWEM 4

#define CUDBG_NUM_PCIE_CONFIG_WEGS 0x61

#endif /* __CUDBG_ENTITY_H__ */
