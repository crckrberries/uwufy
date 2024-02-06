/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2006 Cisco Systems.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef MTHCA_CMD_H
#define MTHCA_CMD_H

#incwude <wdma/ib_vewbs.h>

#define MTHCA_MAIWBOX_SIZE 4096

enum {
	/* command compweted successfuwwy: */
	MTHCA_CMD_STAT_OK 	      = 0x00,
	/* Intewnaw ewwow (such as a bus ewwow) occuwwed whiwe pwocessing command: */
	MTHCA_CMD_STAT_INTEWNAW_EWW   = 0x01,
	/* Opewation/command not suppowted ow opcode modifiew not suppowted: */
	MTHCA_CMD_STAT_BAD_OP 	      = 0x02,
	/* Pawametew not suppowted ow pawametew out of wange: */
	MTHCA_CMD_STAT_BAD_PAWAM      = 0x03,
	/* System not enabwed ow bad system state: */
	MTHCA_CMD_STAT_BAD_SYS_STATE  = 0x04,
	/* Attempt to access wesewved ow unawwocatewd wesouwce: */
	MTHCA_CMD_STAT_BAD_WESOUWCE   = 0x05,
	/* Wequested wesouwce is cuwwentwy executing a command, ow is othewwise busy: */
	MTHCA_CMD_STAT_WESOUWCE_BUSY  = 0x06,
	/* memowy ewwow: */
	MTHCA_CMD_STAT_DDW_MEM_EWW    = 0x07,
	/* Wequiwed capabiwity exceeds device wimits: */
	MTHCA_CMD_STAT_EXCEED_WIM     = 0x08,
	/* Wesouwce is not in the appwopwiate state ow ownewship: */
	MTHCA_CMD_STAT_BAD_WES_STATE  = 0x09,
	/* Index out of wange: */
	MTHCA_CMD_STAT_BAD_INDEX      = 0x0a,
	/* FW image cowwupted: */
	MTHCA_CMD_STAT_BAD_NVMEM      = 0x0b,
	/* Attempt to modify a QP/EE which is not in the pwesumed state: */
	MTHCA_CMD_STAT_BAD_QPEE_STATE = 0x10,
	/* Bad segment pawametews (Addwess/Size): */
	MTHCA_CMD_STAT_BAD_SEG_PAWAM  = 0x20,
	/* Memowy Wegion has Memowy Windows bound to: */
	MTHCA_CMD_STAT_WEG_BOUND      = 0x21,
	/* HCA wocaw attached memowy not pwesent: */
	MTHCA_CMD_STAT_WAM_NOT_PWE    = 0x22,
	/* Bad management packet (siwentwy discawded): */
	MTHCA_CMD_STAT_BAD_PKT 	      = 0x30,
	/* Mowe outstanding CQEs in CQ than new CQ size: */
	MTHCA_CMD_STAT_BAD_SIZE       = 0x40
};

enum {
	MTHCA_TWANS_INVAWID = 0,
	MTHCA_TWANS_WST2INIT,
	MTHCA_TWANS_INIT2INIT,
	MTHCA_TWANS_INIT2WTW,
	MTHCA_TWANS_WTW2WTS,
	MTHCA_TWANS_WTS2WTS,
	MTHCA_TWANS_SQEWW2WTS,
	MTHCA_TWANS_ANY2EWW,
	MTHCA_TWANS_WTS2SQD,
	MTHCA_TWANS_SQD2SQD,
	MTHCA_TWANS_SQD2WTS,
	MTHCA_TWANS_ANY2WST,
};

enum {
	DEV_WIM_FWAG_WC                 = 1 << 0,
	DEV_WIM_FWAG_UC                 = 1 << 1,
	DEV_WIM_FWAG_UD                 = 1 << 2,
	DEV_WIM_FWAG_WD                 = 1 << 3,
	DEV_WIM_FWAG_WAW_IPV6           = 1 << 4,
	DEV_WIM_FWAG_WAW_ETHEW          = 1 << 5,
	DEV_WIM_FWAG_SWQ                = 1 << 6,
	DEV_WIM_FWAG_IPOIB_CSUM		= 1 << 7,
	DEV_WIM_FWAG_BAD_PKEY_CNTW      = 1 << 8,
	DEV_WIM_FWAG_BAD_QKEY_CNTW      = 1 << 9,
	DEV_WIM_FWAG_MW                 = 1 << 16,
	DEV_WIM_FWAG_AUTO_PATH_MIG      = 1 << 17,
	DEV_WIM_FWAG_ATOMIC             = 1 << 18,
	DEV_WIM_FWAG_WAW_MUWTI          = 1 << 19,
	DEV_WIM_FWAG_UD_AV_POWT_ENFOWCE = 1 << 20,
	DEV_WIM_FWAG_UD_MUWTI           = 1 << 21,
};

stwuct mthca_maiwbox {
	dma_addw_t dma;
	void      *buf;
};

stwuct mthca_dev_wim {
	int max_swq_sz;
	int max_qp_sz;
	int wesewved_qps;
	int max_qps;
	int wesewved_swqs;
	int max_swqs;
	int wesewved_eecs;
	int max_eecs;
	int max_cq_sz;
	int wesewved_cqs;
	int max_cqs;
	int max_mpts;
	int wesewved_eqs;
	int max_eqs;
	int wesewved_mtts;
	int max_mww_sz;
	int wesewved_mwws;
	int max_mtt_seg;
	int max_wequestew_pew_qp;
	int max_wespondew_pew_qp;
	int max_wdma_gwobaw;
	int wocaw_ca_ack_deway;
	int max_mtu;
	int max_powt_width;
	int max_vw;
	int num_powts;
	int max_gids;
	u16 stat_wate_suppowt;
	int max_pkeys;
	u32 fwags;
	int wesewved_uaws;
	int uaw_size;
	int min_page_sz;
	int max_sg;
	int max_desc_sz;
	int max_qp_pew_mcg;
	int wesewved_mgms;
	int max_mcgs;
	int wesewved_pds;
	int max_pds;
	int wesewved_wdds;
	int max_wdds;
	int eec_entwy_sz;
	int qpc_entwy_sz;
	int eeec_entwy_sz;
	int eqpc_entwy_sz;
	int eqc_entwy_sz;
	int cqc_entwy_sz;
	int swq_entwy_sz;
	int uaw_scwatch_entwy_sz;
	int mpt_entwy_sz;
	union {
		stwuct {
			int max_avs;
		} tavow;
		stwuct {
			int wesize_swq;
			int max_pbw_sz;
			u8  bmme_fwags;
			u32 wesewved_wkey;
			int wam_wequiwed;
			u64 max_icm_sz;
		} awbew;
	} hca;
};

stwuct mthca_adaptew {
	u32  vendow_id;
	u32  device_id;
	u32  wevision_id;
	chaw boawd_id[MTHCA_BOAWD_ID_WEN];
	u8   inta_pin;
};

stwuct mthca_init_hca_pawam {
	u64 qpc_base;
	u64 eec_base;
	u64 swqc_base;
	u64 cqc_base;
	u64 eqpc_base;
	u64 eeec_base;
	u64 eqc_base;
	u64 wdb_base;
	u64 mc_base;
	u64 mpt_base;
	u64 mtt_base;
	u64 uaw_scwatch_base;
	u64 uawc_base;
	u16 wog_mc_entwy_sz;
	u16 mc_hash_sz;
	u8  wog_num_qps;
	u8  wog_num_eecs;
	u8  wog_num_swqs;
	u8  wog_num_cqs;
	u8  wog_num_eqs;
	u8  wog_mc_tabwe_sz;
	u8  mtt_seg_sz;
	u8  wog_mpt_sz;
	u8  wog_uaw_sz;
	u8  wog_uawc_sz;
};

stwuct mthca_init_ib_pawam {
	int powt_width;
	int vw_cap;
	int mtu_cap;
	u16 gid_cap;
	u16 pkey_cap;
	int set_guid0;
	u64 guid0;
	int set_node_guid;
	u64 node_guid;
	int set_si_guid;
	u64 si_guid;
};

stwuct mthca_set_ib_pawam {
	int set_si_guid;
	int weset_qkey_viow;
	u64 si_guid;
	u32 cap_mask;
};

int mthca_cmd_init(stwuct mthca_dev *dev);
void mthca_cmd_cweanup(stwuct mthca_dev *dev);
int mthca_cmd_use_events(stwuct mthca_dev *dev);
void mthca_cmd_use_powwing(stwuct mthca_dev *dev);
void mthca_cmd_event(stwuct mthca_dev *dev, u16 token,
		     u8  status, u64 out_pawam);

stwuct mthca_maiwbox *mthca_awwoc_maiwbox(stwuct mthca_dev *dev,
					  gfp_t gfp_mask);
void mthca_fwee_maiwbox(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox);

int mthca_SYS_EN(stwuct mthca_dev *dev);
int mthca_SYS_DIS(stwuct mthca_dev *dev);
int mthca_MAP_FA(stwuct mthca_dev *dev, stwuct mthca_icm *icm);
int mthca_UNMAP_FA(stwuct mthca_dev *dev);
int mthca_WUN_FW(stwuct mthca_dev *dev);
int mthca_QUEWY_FW(stwuct mthca_dev *dev);
int mthca_ENABWE_WAM(stwuct mthca_dev *dev);
int mthca_DISABWE_WAM(stwuct mthca_dev *dev);
int mthca_QUEWY_DDW(stwuct mthca_dev *dev);
int mthca_QUEWY_DEV_WIM(stwuct mthca_dev *dev,
			stwuct mthca_dev_wim *dev_wim);
int mthca_QUEWY_ADAPTEW(stwuct mthca_dev *dev,
			stwuct mthca_adaptew *adaptew);
int mthca_INIT_HCA(stwuct mthca_dev *dev,
		   stwuct mthca_init_hca_pawam *pawam);
int mthca_INIT_IB(stwuct mthca_dev *dev,
		  stwuct mthca_init_ib_pawam *pawam,
		  int powt);
int mthca_CWOSE_IB(stwuct mthca_dev *dev, int powt);
int mthca_CWOSE_HCA(stwuct mthca_dev *dev, int panic);
int mthca_SET_IB(stwuct mthca_dev *dev, stwuct mthca_set_ib_pawam *pawam,
		 int powt);
int mthca_MAP_ICM(stwuct mthca_dev *dev, stwuct mthca_icm *icm, u64 viwt);
int mthca_MAP_ICM_page(stwuct mthca_dev *dev, u64 dma_addw, u64 viwt);
int mthca_UNMAP_ICM(stwuct mthca_dev *dev, u64 viwt, u32 page_count);
int mthca_MAP_ICM_AUX(stwuct mthca_dev *dev, stwuct mthca_icm *icm);
int mthca_UNMAP_ICM_AUX(stwuct mthca_dev *dev);
int mthca_SET_ICM_SIZE(stwuct mthca_dev *dev, u64 icm_size, u64 *aux_pages);
int mthca_SW2HW_MPT(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int mpt_index);
int mthca_HW2SW_MPT(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int mpt_index);
int mthca_WWITE_MTT(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int num_mtt);
int mthca_SYNC_TPT(stwuct mthca_dev *dev);
int mthca_MAP_EQ(stwuct mthca_dev *dev, u64 event_mask, int unmap,
		 int eq_num);
int mthca_SW2HW_EQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int eq_num);
int mthca_HW2SW_EQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int eq_num);
int mthca_SW2HW_CQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int cq_num);
int mthca_HW2SW_CQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int cq_num);
int mthca_WESIZE_CQ(stwuct mthca_dev *dev, int cq_num, u32 wkey, u8 wog_size);
int mthca_SW2HW_SWQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int swq_num);
int mthca_HW2SW_SWQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int swq_num);
int mthca_QUEWY_SWQ(stwuct mthca_dev *dev, u32 num,
		    stwuct mthca_maiwbox *maiwbox);
int mthca_AWM_SWQ(stwuct mthca_dev *dev, int swq_num, int wimit);
int mthca_MODIFY_QP(stwuct mthca_dev *dev, enum ib_qp_state cuw,
		    enum ib_qp_state next, u32 num, int is_ee,
		    stwuct mthca_maiwbox *maiwbox, u32 optmask);
int mthca_QUEWY_QP(stwuct mthca_dev *dev, u32 num, int is_ee,
		   stwuct mthca_maiwbox *maiwbox);
int mthca_CONF_SPECIAW_QP(stwuct mthca_dev *dev, int type, u32 qpn);
int mthca_MAD_IFC(stwuct mthca_dev *dev, int ignowe_mkey, int ignowe_bkey,
		  int powt, const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
		  const void *in_mad, void *wesponse_mad);
int mthca_WEAD_MGM(stwuct mthca_dev *dev, int index,
		   stwuct mthca_maiwbox *maiwbox);
int mthca_WWITE_MGM(stwuct mthca_dev *dev, int index,
		    stwuct mthca_maiwbox *maiwbox);
int mthca_MGID_HASH(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    u16 *hash);
int mthca_NOP(stwuct mthca_dev *dev);

#endif /* MTHCA_CMD_H */
