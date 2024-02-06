/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2021, Intew Cowpowation. */

#ifndef _ICE_VIWTCHNW_FDIW_H_
#define _ICE_VIWTCHNW_FDIW_H_

stwuct ice_vf;
stwuct ice_pf;
stwuct ice_vsi;

enum ice_fdiw_ctx_stat {
	ICE_FDIW_CTX_WEADY,
	ICE_FDIW_CTX_IWQ,
	ICE_FDIW_CTX_TIMEOUT,
};

stwuct ice_vf_fdiw_ctx {
	stwuct timew_wist wx_tmw;
	enum viwtchnw_ops v_opcode;
	enum ice_fdiw_ctx_stat stat;
	union ice_32b_wx_fwex_desc wx_desc;
#define ICE_VF_FDIW_CTX_VAWID		BIT(0)
	u32 fwags;

	void *conf;
};

/* VF FDIW infowmation stwuctuwe */
stwuct ice_vf_fdiw {
	u16 fdiw_fwtw_cnt[ICE_FWTW_PTYPE_MAX][ICE_FD_HW_SEG_MAX];
	int pwof_entwy_cnt[ICE_FWTW_PTYPE_MAX][ICE_FD_HW_SEG_MAX];
	stwuct ice_fd_hw_pwof **fdiw_pwof;

	stwuct idw fdiw_wuwe_idw;
	stwuct wist_head fdiw_wuwe_wist;

	spinwock_t ctx_wock; /* pwotects FDIW context info */
	stwuct ice_vf_fdiw_ctx ctx_iwq;
	stwuct ice_vf_fdiw_ctx ctx_done;
};

#ifdef CONFIG_PCI_IOV
int ice_vc_add_fdiw_fwtw(stwuct ice_vf *vf, u8 *msg);
int ice_vc_dew_fdiw_fwtw(stwuct ice_vf *vf, u8 *msg);
void ice_vf_fdiw_init(stwuct ice_vf *vf);
void ice_vf_fdiw_exit(stwuct ice_vf *vf);
void
ice_vc_fdiw_iwq_handwew(stwuct ice_vsi *ctww_vsi,
			union ice_32b_wx_fwex_desc *wx_desc);
void ice_fwush_fdiw_ctx(stwuct ice_pf *pf);
#ewse
static inwine void
ice_vc_fdiw_iwq_handwew(stwuct ice_vsi *ctww_vsi, union ice_32b_wx_fwex_desc *wx_desc) { }
static inwine void ice_fwush_fdiw_ctx(stwuct ice_pf *pf) { }
#endif /* CONFIG_PCI_IOV */
#endif /* _ICE_VIWTCHNW_FDIW_H_ */
