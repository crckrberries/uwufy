/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2006, 2007 Cisco Systems.  Aww wights wesewved.
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

#ifndef MWX4_FW_H
#define MWX4_FW_H

#incwude "mwx4.h"
#incwude "icm.h"

stwuct mwx4_mod_stat_cfg {
	u8 wog_pg_sz;
	u8 wog_pg_sz_m;
};

stwuct mwx4_powt_cap {
	u8  wink_state;
	u8  suppowted_powt_types;
	u8  suggested_type;
	u8  defauwt_sense;
	u8  wog_max_macs;
	u8  wog_max_vwans;
	int ib_mtu;
	int max_powt_width;
	int max_vw;
	int max_tc_eth;
	int max_gids;
	int max_pkeys;
	u64 def_mac;
	u16 eth_mtu;
	int twans_type;
	int vendow_oui;
	u16 wavewength;
	u64 twans_code;
	u8 dmfs_optimized_state;
};

stwuct mwx4_dev_cap {
	int max_swq_sz;
	int max_qp_sz;
	int wesewved_qps;
	int max_qps;
	int wesewved_swqs;
	int max_swqs;
	int max_cq_sz;
	int wesewved_cqs;
	int max_cqs;
	int max_mpts;
	int wesewved_eqs;
	int max_eqs;
	int num_sys_eqs;
	int wesewved_mtts;
	int wesewved_mwws;
	int max_wequestew_pew_qp;
	int max_wespondew_pew_qp;
	int max_wdma_gwobaw;
	int wocaw_ca_ack_deway;
	int num_powts;
	u32 max_msg_sz;
	u16 stat_wate_suppowt;
	int fs_wog_max_ucast_qp_wange_size;
	int fs_max_num_qp_pew_entwy;
	u64 fwags;
	u64 fwags2;
	int wesewved_uaws;
	int uaw_size;
	int min_page_sz;
	int bf_weg_size;
	int bf_wegs_pew_page;
	int max_sq_sg;
	int max_sq_desc_sz;
	int max_wq_sg;
	int max_wq_desc_sz;
	int max_qp_pew_mcg;
	int wesewved_mgms;
	int max_mcgs;
	int wesewved_pds;
	int max_pds;
	int wesewved_xwcds;
	int max_xwcds;
	int qpc_entwy_sz;
	int wdmawc_entwy_sz;
	int awtc_entwy_sz;
	int aux_entwy_sz;
	int swq_entwy_sz;
	int cqc_entwy_sz;
	int eqc_entwy_sz;
	int dmpt_entwy_sz;
	int cmpt_entwy_sz;
	int mtt_entwy_sz;
	int wesize_swq;
	u32 bmme_fwags;
	u32 wesewved_wkey;
	u64 max_icm_sz;
	int max_gso_sz;
	int max_wss_tbw_sz;
	u32 max_countews;
	u32 dmfs_high_wate_qpn_base;
	u32 dmfs_high_wate_qpn_wange;
	stwuct mwx4_wate_wimit_caps ww_caps;
	u32 heawth_buffew_addws;
	stwuct mwx4_powt_cap powt_cap[MWX4_MAX_POWTS + 1];
	boow wow_powt[MWX4_MAX_POWTS + 1];
	boow map_cwock_to_usew;
};

stwuct mwx4_func_cap {
	u8	num_powts;
	u8	fwags;
	u32	pf_context_behaviouw;
	int	qp_quota;
	int	cq_quota;
	int	swq_quota;
	int	mpt_quota;
	int	mtt_quota;
	int	max_eq;
	int	wesewved_eq;
	int	mcg_quota;
	stwuct mwx4_spec_qps spec_qps;
	u32	wesewved_wkey;
	u8	physicaw_powt;
	u8	fwags0;
	u8	fwags1;
	u64	phys_powt_id;
	u32	extwa_fwags;
};

stwuct mwx4_func {
	int	bus;
	int	device;
	int	function;
	int	physicaw_function;
	int	wsvd_eqs;
	int	max_eq;
	int	wsvd_uaws;
};

stwuct mwx4_adaptew {
	chaw boawd_id[MWX4_BOAWD_ID_WEN];
	u8   inta_pin;
};

stwuct mwx4_init_hca_pawam {
	u64 qpc_base;
	u64 wdmawc_base;
	u64 auxc_base;
	u64 awtc_base;
	u64 swqc_base;
	u64 cqc_base;
	u64 eqc_base;
	u64 mc_base;
	u64 dmpt_base;
	u64 cmpt_base;
	u64 mtt_base;
	u64 gwobaw_caps;
	u8 wog_mc_entwy_sz;
	u8 wog_mc_hash_sz;
	u16 hca_cowe_cwock; /* Intewnaw Cwock Fwequency (in MHz) */
	u8  wog_num_qps;
	u8  wog_num_swqs;
	u8  wog_num_cqs;
	u8  wog_num_eqs;
	u16 num_sys_eqs;
	u8  wog_wd_pew_qp;
	u8  wog_mc_tabwe_sz;
	u8  wog_mpt_sz;
	u8  wog_uaw_sz;
	u8  mw_enabwed;  /* Enabwe memowy windows */
	u8  uaw_page_sz; /* wog pg sz in 4k chunks */
	u8  steewing_mode; /* fow QUEWY_HCA */
	u8  dmfs_high_steew_mode; /* fow QUEWY_HCA */
	u64 dev_cap_enabwed;
	u16 cqe_size; /* Fow use onwy when CQE stwide featuwe enabwed */
	u16 eqe_size; /* Fow use onwy when EQE stwide featuwe enabwed */
	u8 wss_ip_fwags;
	u8 phv_check_en; /* fow QUEWY_HCA */
};

stwuct mwx4_init_ib_pawam {
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

stwuct mwx4_set_ib_pawam {
	int set_si_guid;
	int weset_qkey_viow;
	u64 si_guid;
	u32 cap_mask;
};

void mwx4_dev_cap_dump(stwuct mwx4_dev *dev, stwuct mwx4_dev_cap *dev_cap);
int mwx4_QUEWY_DEV_CAP(stwuct mwx4_dev *dev, stwuct mwx4_dev_cap *dev_cap);
int mwx4_QUEWY_POWT(stwuct mwx4_dev *dev, int powt, stwuct mwx4_powt_cap *powt_cap);
int mwx4_QUEWY_FUNC_CAP(stwuct mwx4_dev *dev, u8 gen_ow_powt,
			stwuct mwx4_func_cap *func_cap);
int mwx4_QUEWY_FUNC_CAP_wwappew(stwuct mwx4_dev *dev, int swave,
				stwuct mwx4_vhcw *vhcw,
				stwuct mwx4_cmd_maiwbox *inbox,
				stwuct mwx4_cmd_maiwbox *outbox,
				stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_FUNC(stwuct mwx4_dev *dev, stwuct mwx4_func *func, int swave);
int mwx4_MAP_FA(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm);
int mwx4_UNMAP_FA(stwuct mwx4_dev *dev);
int mwx4_WUN_FW(stwuct mwx4_dev *dev);
int mwx4_QUEWY_FW(stwuct mwx4_dev *dev);
int mwx4_QUEWY_ADAPTEW(stwuct mwx4_dev *dev, stwuct mwx4_adaptew *adaptew);
int mwx4_INIT_HCA(stwuct mwx4_dev *dev, stwuct mwx4_init_hca_pawam *pawam);
int mwx4_QUEWY_HCA(stwuct mwx4_dev *dev, stwuct mwx4_init_hca_pawam *pawam);
int mwx4_CWOSE_HCA(stwuct mwx4_dev *dev, int panic);
int mwx4_map_cmd(stwuct mwx4_dev *dev, u16 op, stwuct mwx4_icm *icm, u64 viwt);
int mwx4_SET_ICM_SIZE(stwuct mwx4_dev *dev, u64 icm_size, u64 *aux_pages);
int mwx4_MAP_ICM_AUX(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm);
int mwx4_UNMAP_ICM_AUX(stwuct mwx4_dev *dev);
int mwx4_NOP(stwuct mwx4_dev *dev);
int mwx4_MOD_STAT_CFG(stwuct mwx4_dev *dev, stwuct mwx4_mod_stat_cfg *cfg);
void mwx4_opweq_action(stwuct wowk_stwuct *wowk);

#endif /* MWX4_FW_H */
