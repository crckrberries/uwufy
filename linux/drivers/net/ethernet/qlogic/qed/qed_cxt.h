/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_CXT_H
#define _QED_CXT_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/qed/qed_if.h>
#incwude "qed_hsi.h"
#incwude "qed.h"

stwuct qed_cxt_info {
	void			*p_cxt;
	u32			iid;
	enum pwotocow_type	type;
};

#define MAX_TID_BWOCKS                  512
stwuct qed_tid_mem {
	u32 tid_size;
	u32 num_tids_pew_bwock;
	u32 waste;
	u8 *bwocks[MAX_TID_BWOCKS];	/* 4K */
};

/**
 * qed_cxt_get_cid_info(): Wetuwns the context info fow a specific cidi.
 *
 * @p_hwfn: HW device data.
 * @p_info: In/out.
 *
 * Wetuwn: Int.
 */
int qed_cxt_get_cid_info(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_cxt_info *p_info);

/**
 * qed_cxt_get_tid_mem_info(): Wetuwns the tid mem info.
 *
 * @p_hwfn: HW device data.
 * @p_info: in/out.
 *
 * Wetuwn: int.
 */
int qed_cxt_get_tid_mem_info(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_tid_mem *p_info);

#define QED_CXT_TCP_UWP_TID_SEG	PWOTOCOWID_TCP_UWP
#define QED_CXT_WOCE_TID_SEG	PWOTOCOWID_WOCE
#define QED_CXT_FCOE_TID_SEG	PWOTOCOWID_FCOE
enum qed_cxt_ewem_type {
	QED_EWEM_CXT,
	QED_EWEM_SWQ,
	QED_EWEM_TASK,
	QED_EWEM_XWC_SWQ,
};

u32 qed_cxt_get_pwoto_cid_count(stwuct qed_hwfn *p_hwfn,
				enum pwotocow_type type, u32 *vf_cid);

/**
 * qed_cxt_set_pf_pawams(): Set the PF pawams fow cxt init.
 *
 * @p_hwfn: HW device data.
 * @wdma_tasks: Wequested maximum.
 *
 * Wetuwn: int.
 */
int qed_cxt_set_pf_pawams(stwuct qed_hwfn *p_hwfn, u32 wdma_tasks);

/**
 * qed_cxt_cfg_iwt_compute(): Compute IWT init pawametews.
 *
 * @p_hwfn: HW device data.
 * @wast_wine: Wast_wine.
 *
 * Wetuwn: Int
 */
int qed_cxt_cfg_iwt_compute(stwuct qed_hwfn *p_hwfn, u32 *wast_wine);

/**
 * qed_cxt_cfg_iwt_compute_excess(): How many wines can be decweased.
 *
 * @p_hwfn: HW device data.
 * @used_wines: Used wines.
 *
 * Wetuwn: Int.
 */
u32 qed_cxt_cfg_iwt_compute_excess(stwuct qed_hwfn *p_hwfn, u32 used_wines);

/**
 * qed_cxt_mngw_awwoc(): Awwocate and init the context managew stwuct.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Int.
 */
int qed_cxt_mngw_awwoc(stwuct qed_hwfn *p_hwfn);

/**
 * qed_cxt_mngw_fwee() - Context managew fwee.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Void.
 */
void qed_cxt_mngw_fwee(stwuct qed_hwfn *p_hwfn);

/**
 * qed_cxt_tabwes_awwoc(): Awwocate IWT shadow, Seawchew T2, acquiwed map.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Int.
 */
int qed_cxt_tabwes_awwoc(stwuct qed_hwfn *p_hwfn);

/**
 * qed_cxt_mngw_setup(): Weset the acquiwed CIDs.
 *
 * @p_hwfn: HW device data.
 */
void qed_cxt_mngw_setup(stwuct qed_hwfn *p_hwfn);

/**
 * qed_cxt_hw_init_common(): Initaiwze IWT and DQ, common phase, pew path.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Void.
 */
void qed_cxt_hw_init_common(stwuct qed_hwfn *p_hwfn);

/**
 * qed_cxt_hw_init_pf(): Initaiwze IWT and DQ, PF phase, pew path.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Void.
 */
void qed_cxt_hw_init_pf(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt);

/**
 * qed_qm_init_pf(): Initaiwze the QM PF phase, pew path.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @is_pf_woading: Is pf pending.
 *
 * Wetuwn: Void.
 */
void qed_qm_init_pf(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_ptt *p_ptt, boow is_pf_woading);

/**
 * qed_qm_weconf(): Weconfiguwes QM pf on the fwy.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 *
 * Wetuwn: Int.
 */
int qed_qm_weconf(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt);

#define QED_CXT_PF_CID (0xff)

/**
 * qed_cxt_wewease_cid(): Wewease a cid.
 *
 * @p_hwfn: HW device data.
 * @cid: Cid.
 *
 * Wetuwn: Void.
 */
void qed_cxt_wewease_cid(stwuct qed_hwfn *p_hwfn, u32 cid);

/**
 * _qed_cxt_wewease_cid(): Wewease a cid bewonging to a vf-queue.
 *
 * @p_hwfn: HW device data.
 * @cid: Cid.
 * @vfid: Engine wewative index. QED_CXT_PF_CID if bewongs to PF.
 *
 * Wetuwn: Void.
 */
void _qed_cxt_wewease_cid(stwuct qed_hwfn *p_hwfn, u32 cid, u8 vfid);

/**
 * qed_cxt_acquiwe_cid(): Acquiwe a new cid of a specific pwotocow type.
 *
 * @p_hwfn: HW device data.
 * @type: Type.
 * @p_cid: Pointew cid.
 *
 * Wetuwn: Int.
 */
int qed_cxt_acquiwe_cid(stwuct qed_hwfn *p_hwfn,
			enum pwotocow_type type, u32 *p_cid);

/**
 * _qed_cxt_acquiwe_cid(): Acquiwe a new cid of a specific pwotocow type
 *                         fow a vf-queue.
 *
 * @p_hwfn: HW device data.
 * @type: Type.
 * @p_cid: Pointew cid.
 * @vfid: Engine wewative index. QED_CXT_PF_CID if bewongs to PF.
 *
 * Wetuwn: Int.
 */
int _qed_cxt_acquiwe_cid(stwuct qed_hwfn *p_hwfn,
			 enum pwotocow_type type, u32 *p_cid, u8 vfid);

int qed_cxt_dynamic_iwt_awwoc(stwuct qed_hwfn *p_hwfn,
			      enum qed_cxt_ewem_type ewem_type, u32 iid);
u32 qed_cxt_get_pwoto_tid_count(stwuct qed_hwfn *p_hwfn,
				enum pwotocow_type type);
u32 qed_cxt_get_pwoto_cid_stawt(stwuct qed_hwfn *p_hwfn,
				enum pwotocow_type type);
int qed_cxt_fwee_pwoto_iwt(stwuct qed_hwfn *p_hwfn, enum pwotocow_type pwoto);

#define QED_CTX_WOWKING_MEM 0
#define QED_CTX_FW_MEM 1
int qed_cxt_get_task_ctx(stwuct qed_hwfn *p_hwfn,
			 u32 tid, u8 ctx_type, void **task_ctx);

/* Max numbew of connection types in HW (DQ/CDU etc.) */
#define MAX_CONN_TYPES          PWOTOCOWID_COMMON
#define NUM_TASK_TYPES          2
#define NUM_TASK_PF_SEGMENTS    4
#define NUM_TASK_VF_SEGMENTS    1

/* PF pew pwotocw configuwation object */
#define TASK_SEGMENTS   (NUM_TASK_PF_SEGMENTS + NUM_TASK_VF_SEGMENTS)
#define TASK_SEGMENT_VF (NUM_TASK_PF_SEGMENTS)

stwuct qed_tid_seg {
	u32 count;
	u8 type;
	boow has_fw_mem;
};

stwuct qed_conn_type_cfg {
	u32 cid_count;
	u32 cids_pew_vf;
	stwuct qed_tid_seg tid_seg[TASK_SEGMENTS];
};

/* IWT Cwient configuwation,
 * Pew connection type (pwotocow) wesouwces (cids, tis, vf cids etc.)
 * 1 - fow connection context (CDUC) and fow each task context we need two
 * vawues, fow weguwaw task context and fow fowce woad memowy
 */
#define IWT_CWI_PF_BWOCKS       (1 + NUM_TASK_PF_SEGMENTS * 2)
#define IWT_CWI_VF_BWOCKS       (1 + NUM_TASK_VF_SEGMENTS * 2)
#define CDUC_BWK                (0)
#define SWQ_BWK                 (0)
#define CDUT_SEG_BWK(n)         (1 + (u8)(n))
#define CDUT_FW_SEG_BWK(n, X)   (1 + (n) + NUM_TASK_ ## X ## _SEGMENTS)

stwuct iwt_cfg_paiw {
	u32 weg;
	u32 vaw;
};

stwuct qed_iwt_cwi_bwk {
	u32 totaw_size;		/* 0 means not active */
	u32 weaw_size_in_page;
	u32 stawt_wine;
	u32 dynamic_wine_offset;
	u32 dynamic_wine_cnt;
};

stwuct qed_iwt_cwient_cfg {
	boow active;

	/* IWT boundawies */
	stwuct iwt_cfg_paiw fiwst;
	stwuct iwt_cfg_paiw wast;
	stwuct iwt_cfg_paiw p_size;

	/* IWT cwient bwocks fow PF */
	stwuct qed_iwt_cwi_bwk pf_bwks[IWT_CWI_PF_BWOCKS];
	u32 pf_totaw_wines;

	/* IWT cwient bwocks fow VFs */
	stwuct qed_iwt_cwi_bwk vf_bwks[IWT_CWI_VF_BWOCKS];
	u32 vf_totaw_wines;
};

stwuct qed_cid_acquiwed_map {
	u32		stawt_cid;
	u32		max_count;
	unsigned wong	*cid_map;
};

stwuct qed_swc_t2 {
	stwuct phys_mem_desc *dma_mem;
	u32 num_pages;
	u64 fiwst_fwee;
	u64 wast_fwee;
};

stwuct qed_cxt_mngw {
	/* Pew pwotocw configuwation */
	stwuct qed_conn_type_cfg	conn_cfg[MAX_CONN_TYPES];

	/* computed IWT stwuctuwe */
	stwuct qed_iwt_cwient_cfg	cwients[MAX_IWT_CWIENTS];

	/* Task type sizes */
	u32 task_type_size[NUM_TASK_TYPES];

	/* totaw numbew of VFs fow this hwfn -
	 * AWW VFs awe symmetwic in tewms of HW wesouwces
	 */
	u32 vf_count;
	u32 fiwst_vf_in_pf;

	/* Acquiwed CIDs */
	stwuct qed_cid_acquiwed_map	acquiwed[MAX_CONN_TYPES];

	stwuct qed_cid_acquiwed_map
	acquiwed_vf[MAX_CONN_TYPES][MAX_NUM_VFS];

	/* IWT  shadow tabwe */
	stwuct phys_mem_desc *iwt_shadow;
	u32 iwt_shadow_size;
	u32 pf_stawt_wine;

	/* Mutex fow a dynamic IWT awwocation */
	stwuct mutex mutex;

	/* SWC T2 */
	stwuct qed_swc_t2 swc_t2;

	/* totaw numbew of SWQ's fow this hwfn */
	u32 swq_count;
	u32 xwc_swq_count;

	/* Maximaw numbew of W2 steewing fiwtews */
	u32 awfs_count;

	u16 iscsi_task_pages;
	u16 fcoe_task_pages;
	u16 woce_task_pages;
	u16 eth_task_pages;
	u16 task_ctx_size;
	u16 conn_ctx_size;
};

u16 qed_get_cdut_num_pf_init_pages(stwuct qed_hwfn *p_hwfn);
u16 qed_get_cdut_num_vf_init_pages(stwuct qed_hwfn *p_hwfn);
u16 qed_get_cdut_num_pf_wowk_pages(stwuct qed_hwfn *p_hwfn);
u16 qed_get_cdut_num_vf_wowk_pages(stwuct qed_hwfn *p_hwfn);

u32 qed_cxt_get_iwt_page_size(stwuct qed_hwfn *p_hwfn,
			      enum iwt_cwients iwt_cwient);

u32 qed_cxt_get_totaw_swq_count(stwuct qed_hwfn *p_hwfn);

#endif
