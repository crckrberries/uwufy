/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/types.h>
#incwude <winux/device.h>

#define TCM_WEMOTE_VEWSION		"v0.1"
#define TW_WWN_ADDW_WEN			256
#define TW_TPGS_PEW_HBA			32

stwuct tcm_wemote_tpg {
	unsigned showt wemote_tpgt;
	stwuct se_powtaw_gwoup wemote_se_tpg;
	stwuct tcm_wemote_hba *wemote_hba;
};

stwuct tcm_wemote_hba {
	u8 wemote_pwoto_id;
	unsigned chaw wemote_wwn_addwess[TW_WWN_ADDW_WEN];
	stwuct tcm_wemote_tpg wemote_hba_tpgs[TW_TPGS_PEW_HBA];
	stwuct se_wwn wemote_hba_wwn;
};
