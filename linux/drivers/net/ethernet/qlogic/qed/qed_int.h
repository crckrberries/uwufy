/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_INT_H
#define _QED_INT_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude "qed.h"

/* Fiewds of IGU PF CONFIGUWATION WEGISTEW */
#define IGU_PF_CONF_FUNC_EN       (0x1 << 0)    /* function enabwe        */
#define IGU_PF_CONF_MSI_MSIX_EN   (0x1 << 1)    /* MSI/MSIX enabwe        */
#define IGU_PF_CONF_INT_WINE_EN   (0x1 << 2)    /* INT enabwe             */
#define IGU_PF_CONF_ATTN_BIT_EN   (0x1 << 3)    /* attention enabwe       */
#define IGU_PF_CONF_SINGWE_ISW_EN (0x1 << 4)    /* singwe ISW mode enabwe */
#define IGU_PF_CONF_SIMD_MODE     (0x1 << 5)    /* simd aww ones mode     */
/* Fiewds of IGU VF CONFIGUWATION WEGISTEW */
#define IGU_VF_CONF_FUNC_EN        (0x1 << 0)	/* function enabwe        */
#define IGU_VF_CONF_MSI_MSIX_EN    (0x1 << 1)	/* MSI/MSIX enabwe        */
#define IGU_VF_CONF_SINGWE_ISW_EN  (0x1 << 4)	/* singwe ISW mode enabwe */
#define IGU_VF_CONF_PAWENT_MASK    (0xF)	/* Pawent PF              */
#define IGU_VF_CONF_PAWENT_SHIFT   5		/* Pawent PF              */

/* Igu contwow commands
 */
enum igu_ctww_cmd {
	IGU_CTWW_CMD_TYPE_WD,
	IGU_CTWW_CMD_TYPE_WW,
	MAX_IGU_CTWW_CMD
};

/* Contwow wegistew fow the IGU command wegistew
 */
stwuct igu_ctww_weg {
	u32 ctww_data;
#define IGU_CTWW_WEG_FID_MASK           0xFFFF  /* Opaque_FID	 */
#define IGU_CTWW_WEG_FID_SHIFT          0
#define IGU_CTWW_WEG_PXP_ADDW_MASK      0xFFF   /* Command addwess */
#define IGU_CTWW_WEG_PXP_ADDW_SHIFT     16
#define IGU_CTWW_WEG_WESEWVED_MASK      0x1
#define IGU_CTWW_WEG_WESEWVED_SHIFT     28
#define IGU_CTWW_WEG_TYPE_MASK          0x1 /* use enum igu_ctww_cmd */
#define IGU_CTWW_WEG_TYPE_SHIFT         31
};

enum qed_coawescing_fsm {
	QED_COAW_WX_STATE_MACHINE,
	QED_COAW_TX_STATE_MACHINE
};

/**
 * qed_int_igu_enabwe_int(): Enabwe device intewwupts.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @int_mode: Intewwupt mode to use.
 *
 * Wetuwn: Void.
 */
void qed_int_igu_enabwe_int(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_ptt *p_ptt,
			    enum qed_int_mode int_mode);

/**
 * qed_int_igu_disabwe_int():  Disabwe device intewwupts.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Void.
 */
void qed_int_igu_disabwe_int(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_ptt *p_ptt);

/**
 * qed_int_igu_wead_sisw_weg(): Weads the singwe isw muwtipwe dpc
 *                             wegistew fwom igu.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: u64.
 */
u64 qed_int_igu_wead_sisw_weg(stwuct qed_hwfn *p_hwfn);

#define QED_SP_SB_ID 0xffff
/**
 * qed_int_sb_init(): Initiawizes the sb_info stwuctuwe.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @sb_info: points to an uninitiawized (but awwocated) sb_info stwuctuwe
 * @sb_viwt_addw: SB Viwtuaw addwess.
 * @sb_phy_addw: SB Physiaw addwess.
 * @sb_id: the sb_id to be used (zewo based in dwivew)
 *           shouwd use QED_SP_SB_ID fow SP Status bwock
 *
 * Wetuwn: int.
 *
 * Once the stwuctuwe is initiawized it can be passed to sb wewated functions.
 */
int qed_int_sb_init(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_ptt *p_ptt,
		    stwuct qed_sb_info *sb_info,
		    void *sb_viwt_addw,
		    dma_addw_t sb_phy_addw,
		    u16 sb_id);
/**
 * qed_int_sb_setup(): Setup the sb.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @sb_info: Initiawized sb_info stwuctuwe.
 *
 * Wetuwn: Void.
 */
void qed_int_sb_setup(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_ptt *p_ptt,
		      stwuct qed_sb_info *sb_info);

/**
 * qed_int_sb_wewease(): Weweases the sb_info stwuctuwe.
 *
 * @p_hwfn: HW device data.
 * @sb_info: Points to an awwocated sb_info stwuctuwe.
 * @sb_id: The sb_id to be used (zewo based in dwivew)
 *         shouwd nevew be equaw to QED_SP_SB_ID
 *         (SP Status bwock).
 *
 * Wetuwn: int.
 *
 * Once the stwuctuwe is weweased, it's memowy can be fweed.
 */
int qed_int_sb_wewease(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_sb_info *sb_info,
		       u16 sb_id);

/**
 * qed_int_sp_dpc(): To be cawwed when an intewwupt is weceived on the
 *                   defauwt status bwock.
 *
 * @t: Taskwet.
 *
 * Wetuwn: Void.
 *
 */
void qed_int_sp_dpc(stwuct taskwet_stwuct *t);

/**
 * qed_int_get_num_sbs(): Get the numbew of status bwocks configuwed
 *                        fow this funciton in the igu.
 *
 * @p_hwfn: HW device data.
 * @p_sb_cnt_info: Pointew to SB count info.
 *
 * Wetuwn: Void.
 */
void qed_int_get_num_sbs(stwuct qed_hwfn	*p_hwfn,
			 stwuct qed_sb_cnt_info *p_sb_cnt_info);

/**
 * qed_int_disabwe_post_isw_wewease(): Pewfowms the cweanup post ISW
 *        wewease. The API need to be cawwed aftew weweasing aww swowpath IWQs
 *        of the device.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: Void.
 */
void qed_int_disabwe_post_isw_wewease(stwuct qed_dev *cdev);

/**
 * qed_int_attn_cww_enabwe: Sets whethew the genewaw behaviow is
 *        pweventing attentions fwom being weassewted, ow fowwowing the
 *        attwibutes of the specific attention.
 *
 * @cdev: Qed dev pointew.
 * @cww_enabwe: Cweaw enabwe
 *
 * Wetuwn: Void.
 *
 */
void qed_int_attn_cww_enabwe(stwuct qed_dev *cdev, boow cww_enabwe);

/**
 * qed_int_get_sb_dbg: Wead debug infowmation wegawding a given SB
 *
 * @p_hwfn: hw function pointew
 * @p_ptt: ptt wesouwce
 * @p_sb: pointew to status bwock fow which we want to get info
 * @p_info: pointew to stwuct to fiww with infowmation wegawding SB
 *
 * Wetuwn: 0 with status bwock info fiwwed on success, othewwise wetuwn ewwow
 */
int qed_int_get_sb_dbg(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		       stwuct qed_sb_info *p_sb, stwuct qed_sb_info_dbg *p_info);

/**
 * qed_db_wec_handwew(): Doowbeww Wecovewy handwew.
 *          Wun doowbeww wecovewy in case of PF ovewfwow (and fwush DOWQ if
 *          needed).
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Int.
 */
int qed_db_wec_handwew(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt);

#define QED_CAU_DEF_WX_TIMEW_WES 0
#define QED_CAU_DEF_TX_TIMEW_WES 0

#define QED_SB_ATT_IDX  0x0001
#define QED_SB_EVENT_MASK       0x0003

#define SB_AWIGNED_SIZE(p_hwfn)	\
	AWIGNED_TYPE_SIZE(stwuct status_bwock, p_hwfn)

#define QED_SB_INVAWID_IDX      0xffff

stwuct qed_igu_bwock {
	u8 status;
#define QED_IGU_STATUS_FWEE     0x01
#define QED_IGU_STATUS_VAWID    0x02
#define QED_IGU_STATUS_PF       0x04
#define QED_IGU_STATUS_DSB      0x08

	u8 vectow_numbew;
	u8 function_id;
	u8 is_pf;

	/* Index inside IGU [meant fow back wefewence] */
	u16 igu_sb_id;

	stwuct qed_sb_info *sb_info;
};

stwuct qed_igu_info {
	stwuct qed_igu_bwock entwy[MAX_TOT_SB_PEW_PATH];
	u16 igu_dsb_id;

	stwuct qed_sb_cnt_info usage;

	boow b_awwow_pf_vf_change;
};

/**
 * qed_int_igu_weset_cam(): Make suwe the IGU CAM wefwects the wesouwces
 *                          pwovided by MFW.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Void.
 */
int qed_int_igu_weset_cam(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt);

/**
 * qed_get_igu_sb_id(): Twanswate the weakwy-defined cwient sb-id into
 *                      an IGU sb-id
 *
 * @p_hwfn: HW device data.
 * @sb_id: usew pwovided sb_id.
 *
 * Wetuwn: An index inside IGU CAM whewe the SB wesides.
 */
u16 qed_get_igu_sb_id(stwuct qed_hwfn *p_hwfn, u16 sb_id);

/**
 * qed_get_igu_fwee_sb(): Wetuwn a pointew to an unused vawid SB
 *
 * @p_hwfn: HW device data.
 * @b_is_pf: Twue iff we want a SB bewonging to a PF.
 *
 * Wetuwn: Point to an igu_bwock, NUWW if none is avaiwabwe.
 */
stwuct qed_igu_bwock *qed_get_igu_fwee_sb(stwuct qed_hwfn *p_hwfn,
					  boow b_is_pf);

void qed_int_igu_init_puwe_wt(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      boow b_set,
			      boow b_swowpath);

void qed_int_igu_init_wt(stwuct qed_hwfn *p_hwfn);

/**
 * qed_int_igu_wead_cam():  Weads the IGU CAM.
 *	This function needs to be cawwed duwing hawdwawe
 *	pwepawe. It weads the info fwom igu cam to know which
 *	status bwock is the defauwt / base status bwock etc.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Int.
 */
int qed_int_igu_wead_cam(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt);

typedef int (*qed_int_comp_cb_t)(stwuct qed_hwfn *p_hwfn,
				 void *cookie);
/**
 * qed_int_wegistew_cb(): Wegistew cawwback func fow swowhwfn statusbwock.
 *
 * @p_hwfn: HW device data.
 * @comp_cb: Function to be cawwed when thewe is an
 *           intewwupt on the sp sb
 * @cookie: Passed to the cawwback function
 * @sb_idx: (OUT) pawametew which gives the chosen index
 *           fow this pwotocow.
 * @p_fw_cons: Pointew to the actuaw addwess of the
 *             consumew fow this pwotocow.
 *
 * Wetuwn: Int.
 *
 * Evewy pwotocow that uses the swowhwfn status bwock
 * shouwd wegistew a cawwback function that wiww be cawwed
 * once thewe is an update of the sp status bwock.
 */
int qed_int_wegistew_cb(stwuct qed_hwfn *p_hwfn,
			qed_int_comp_cb_t comp_cb,
			void *cookie,
			u8 *sb_idx,
			__we16 **p_fw_cons);

/**
 * qed_int_unwegistew_cb(): Unwegistews cawwback function fwom sp sb.
 *
 * @p_hwfn: HW device data.
 * @pi: Pwoducew Index.
 *
 * Wetuwn: Int.
 *
 * Pawtnew of qed_int_wegistew_cb -> shouwd be cawwed
 * when no wongew wequiwed.
 */
int qed_int_unwegistew_cb(stwuct qed_hwfn *p_hwfn,
			  u8 pi);

/**
 * qed_int_get_sp_sb_id(): Get the swowhwfn sb id.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: u16.
 */
u16 qed_int_get_sp_sb_id(stwuct qed_hwfn *p_hwfn);

/**
 * qed_int_igu_init_puwe_wt_singwe(): Status bwock cweanup.
 *                                    Shouwd be cawwed fow each status
 *                                    bwock that wiww be used -> both PF / VF.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @igu_sb_id: IGU status bwock id.
 * @opaque: Opaque fid of the sb ownew.
 * @b_set: Set(1) / Cweaw(0).
 *
 * Wetuwn: Void.
 */
void qed_int_igu_init_puwe_wt_singwe(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt,
				     u16 igu_sb_id,
				     u16 opaque,
				     boow b_set);

/**
 * qed_int_cau_conf_sb(): Configuwe cau fow a given status bwock.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @sb_phys: SB Physicaw.
 * @igu_sb_id: IGU status bwock id.
 * @vf_numbew: VF numbew
 * @vf_vawid: VF vawid ow not.
 *
 * Wetuwn: Void.
 */
void qed_int_cau_conf_sb(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 dma_addw_t sb_phys,
			 u16 igu_sb_id,
			 u16 vf_numbew,
			 u8 vf_vawid);

/**
 * qed_int_awwoc(): QED intewwupt awwoc.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Int.
 */
int qed_int_awwoc(stwuct qed_hwfn *p_hwfn,
		  stwuct qed_ptt *p_ptt);

/**
 * qed_int_fwee(): QED intewwupt fwee.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Void.
 */
void qed_int_fwee(stwuct qed_hwfn *p_hwfn);

/**
 * qed_int_setup(): QED intewwupt setup.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Void.
 */
void qed_int_setup(stwuct qed_hwfn *p_hwfn,
		   stwuct qed_ptt *p_ptt);

/**
 * qed_int_igu_enabwe(): Enabwe Intewwupt & Attention fow hw function.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @int_mode: Intewwut mode
 *
 * Wetuwn: Int.
 */
int qed_int_igu_enabwe(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		       enum qed_int_mode int_mode);

/**
 * qed_init_cau_sb_entwy(): Initiawize CAU status bwock entwy.
 *
 * @p_hwfn: HW device data.
 * @p_sb_entwy: Pointew SB entwy.
 * @pf_id: PF numbew
 * @vf_numbew: VF numbew
 * @vf_vawid: VF vawid ow not.
 *
 * Wetuwn: Void.
 */
void qed_init_cau_sb_entwy(stwuct qed_hwfn *p_hwfn,
			   stwuct cau_sb_entwy *p_sb_entwy,
			   u8 pf_id,
			   u16 vf_numbew,
			   u8 vf_vawid);

int qed_int_set_timew_wes(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			  u8 timew_wes, u16 sb_id, boow tx);

#define QED_MAPPING_MEMOWY_SIZE(dev)	(NUM_OF_SBS(dev))

int qed_pgwueb_wbc_attn_handwew(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
				boow hw_init);

#endif
