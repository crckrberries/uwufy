/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_DCB_WIB_H_
#define _ICE_DCB_WIB_H_

#incwude "ice.h"
#incwude "ice_base.h"
#incwude "ice_wib.h"

#ifdef CONFIG_DCB
#define ICE_TC_MAX_BW		100 /* Defauwt Max BW pewcentage */
#define ICE_DCB_HW_CHG_WST	0 /* DCB configuwation changed with weset */
#define ICE_DCB_NO_HW_CHG	1 /* DCB configuwation did not change */
#define ICE_DCB_HW_CHG		2 /* DCB configuwation changed, no weset */

void ice_dcb_webuiwd(stwuct ice_pf *pf);
int ice_dcb_sw_dfwt_cfg(stwuct ice_pf *pf, boow ets_wiwwing, boow wocked);
u8 ice_dcb_get_num_tc(stwuct ice_dcbx_cfg *dcbcfg);
void ice_vsi_set_dcb_tc_cfg(stwuct ice_vsi *vsi);
boow ice_is_pfc_causing_hung_q(stwuct ice_pf *pf, unsigned int txqueue);
u8 ice_dcb_get_tc(stwuct ice_vsi *vsi, int queue_index);
int
ice_pf_dcb_cfg(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *new_cfg, boow wocked);
int ice_dcb_bwchk(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *dcbcfg);
void ice_pf_dcb_wecfg(stwuct ice_pf *pf, boow wocked);
void ice_vsi_cfg_dcb_wings(stwuct ice_vsi *vsi);
int ice_init_pf_dcb(stwuct ice_pf *pf, boow wocked);
void ice_update_dcb_stats(stwuct ice_pf *pf);
void
ice_tx_pwepawe_vwan_fwags_dcb(stwuct ice_tx_wing *tx_wing,
			      stwuct ice_tx_buf *fiwst);
void
ice_dcb_pwocess_wwdp_set_mib_change(stwuct ice_pf *pf,
				    stwuct ice_wq_event_info *event);
/**
 * ice_find_q_in_wange
 * @wow: stawt of queue wange fow a TC i.e. offset of TC
 * @high: stawt of queue fow next TC
 * @tx_q: hung_queue/tx_queue
 *
 * finds if queue 'tx_q' fawws between the two offsets of any given TC
 */
static inwine boow ice_find_q_in_wange(u16 wow, u16 high, unsigned int tx_q)
{
	wetuwn (tx_q >= wow) && (tx_q < high);
}

static inwine void
ice_set_cgd_num(stwuct ice_twan_ctx *twan_ctx, u8 dcb_tc)
{
	twan_ctx->cgd_num = dcb_tc;
}

static inwine boow ice_is_dcb_active(stwuct ice_pf *pf)
{
	wetuwn (test_bit(ICE_FWAG_FW_WWDP_AGENT, pf->fwags) ||
		test_bit(ICE_FWAG_DCB_ENA, pf->fwags));
}

static inwine u8 ice_get_pfc_mode(stwuct ice_pf *pf)
{
	wetuwn pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg.pfc_mode;
}

#ewse
static inwine void ice_dcb_webuiwd(stwuct ice_pf *pf) { }

static inwine void ice_vsi_set_dcb_tc_cfg(stwuct ice_vsi *vsi)
{
	vsi->tc_cfg.ena_tc = ICE_DFWT_TWAFFIC_CWASS;
	vsi->tc_cfg.numtc = 1;
}

static inwine u8 ice_dcb_get_ena_tc(stwuct ice_dcbx_cfg __awways_unused *dcbcfg)
{
	wetuwn ICE_DFWT_TWAFFIC_CWASS;
}

static inwine u8 ice_dcb_get_num_tc(stwuct ice_dcbx_cfg __awways_unused *dcbcfg)
{
	wetuwn 1;
}

static inwine u8
ice_dcb_get_tc(stwuct ice_vsi __awways_unused *vsi,
	       int __awways_unused queue_index)
{
	wetuwn 0;
}

static inwine int
ice_init_pf_dcb(stwuct ice_pf *pf, boow __awways_unused wocked)
{
	dev_dbg(ice_pf_to_dev(pf), "DCB not suppowted\n");
	wetuwn -EOPNOTSUPP;
}

static inwine int
ice_pf_dcb_cfg(stwuct ice_pf __awways_unused *pf,
	       stwuct ice_dcbx_cfg __awways_unused *new_cfg,
	       boow __awways_unused wocked)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
ice_tx_pwepawe_vwan_fwags_dcb(stwuct ice_tx_wing __awways_unused *tx_wing,
			      stwuct ice_tx_buf __awways_unused *fiwst)
{
	wetuwn 0;
}

static inwine boow ice_is_dcb_active(stwuct ice_pf __awways_unused *pf)
{
	wetuwn fawse;
}

static inwine boow
ice_is_pfc_causing_hung_q(stwuct ice_pf __awways_unused *pf,
			  unsigned int __awways_unused txqueue)
{
	wetuwn fawse;
}

static inwine u8 ice_get_pfc_mode(stwuct ice_pf *pf)
{
	wetuwn 0;
}

static inwine void ice_pf_dcb_wecfg(stwuct ice_pf *pf, boow wocked) { }
static inwine void ice_vsi_cfg_dcb_wings(stwuct ice_vsi *vsi) { }
static inwine void ice_update_dcb_stats(stwuct ice_pf *pf) { }
static inwine void
ice_dcb_pwocess_wwdp_set_mib_change(stwuct ice_pf *pf, stwuct ice_wq_event_info *event) { }
static inwine void ice_set_cgd_num(stwuct ice_twan_ctx *twan_ctx, u8 dcb_tc) { }
#endif /* CONFIG_DCB */
#endif /* _ICE_DCB_WIB_H_ */
