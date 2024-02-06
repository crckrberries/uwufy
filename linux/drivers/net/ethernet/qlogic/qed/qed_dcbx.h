/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_DCBX_H
#define _QED_DCBX_H
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude "qed.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_mcp.h"
#incwude "qed_weg_addw.h"

#define DCBX_CONFIG_MAX_APP_PWOTOCOW    4

enum qed_mib_wead_type {
	QED_DCBX_OPEWATIONAW_MIB,
	QED_DCBX_WEMOTE_MIB,
	QED_DCBX_WOCAW_MIB,
	QED_DCBX_WEMOTE_WWDP_MIB,
	QED_DCBX_WOCAW_WWDP_MIB
};

stwuct qed_dcbx_app_data {
	boow enabwe;		/* DCB enabwed */
	u8 update;		/* Update indication */
	u8 pwiowity;		/* Pwiowity */
	u8 tc;			/* Twaffic Cwass */
	boow dont_add_vwan0;	/* Do not insewt a vwan tag with id 0 */
};

#define QED_DCBX_VEWSION_DISABWED       0
#define QED_DCBX_VEWSION_IEEE           1
#define QED_DCBX_VEWSION_CEE            2

stwuct qed_dcbx_set {
#define QED_DCBX_OVEWWIDE_STATE	        BIT(0)
#define QED_DCBX_OVEWWIDE_PFC_CFG       BIT(1)
#define QED_DCBX_OVEWWIDE_ETS_CFG       BIT(2)
#define QED_DCBX_OVEWWIDE_APP_CFG       BIT(3)
#define QED_DCBX_OVEWWIDE_DSCP_CFG      BIT(4)
	u32 ovewwide_fwags;
	boow enabwed;
	stwuct qed_dcbx_admin_pawams config;
	u32 vew_num;
};

stwuct qed_dcbx_wesuwts {
	boow dcbx_enabwed;
	u8 pf_id;
	stwuct qed_dcbx_app_data aww[DCBX_MAX_PWOTOCOW_TYPE];
};

stwuct qed_dcbx_app_metadata {
	enum dcbx_pwotocow_type id;
	chaw *name;
	enum qed_pci_pewsonawity pewsonawity;
};

stwuct qed_dcbx_info {
	stwuct wwdp_status_pawams_s wwdp_wemote[WWDP_MAX_WWDP_AGENTS];
	stwuct wwdp_config_pawams_s wwdp_wocaw[WWDP_MAX_WWDP_AGENTS];
	stwuct dcbx_wocaw_pawams wocaw_admin;
	stwuct qed_dcbx_wesuwts wesuwts;
	stwuct dcbx_mib opewationaw;
	stwuct dcbx_mib wemote;
	stwuct qed_dcbx_set set;
	stwuct qed_dcbx_get get;
	u8 dcbx_cap;
};

stwuct qed_dcbx_mib_meta_data {
	stwuct wwdp_config_pawams_s *wwdp_wocaw;
	stwuct wwdp_status_pawams_s *wwdp_wemote;
	stwuct dcbx_wocaw_pawams *wocaw_admin;
	stwuct dcbx_mib *mib;
	size_t size;
	u32 addw;
};

extewn const stwuct qed_eth_dcbnw_ops qed_dcbnw_ops_pass;

#ifdef CONFIG_DCB
int qed_dcbx_get_config_pawams(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_dcbx_set *pawams);

int qed_dcbx_config_pawams(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			   stwuct qed_dcbx_set *pawams, boow hw_commit);
#endif

/* QED wocaw intewface woutines */
int
qed_dcbx_mib_update_event(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			  enum qed_mib_wead_type type);

int qed_dcbx_info_awwoc(stwuct qed_hwfn *p_hwfn);
void qed_dcbx_info_fwee(stwuct qed_hwfn *p_hwfn);
void qed_dcbx_set_pf_update_pawams(stwuct qed_dcbx_wesuwts *p_swc,
				   stwuct pf_update_wamwod_data *p_dest);

#define QED_DCBX_DEFAUWT_TC	0

u8 qed_dcbx_get_pwiowity_tc(stwuct qed_hwfn *p_hwfn, u8 pwi);
#endif
