/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2017-2019 NXP */

#incwude "enetc.h"
#incwude <winux/phywink.h>

#define ENETC_PF_NUM_WINGS	8

enum enetc_mac_addw_type {UC, MC, MADDW_TYPE};
#define ENETC_MAX_NUM_MAC_FWT	((ENETC_MAX_NUM_VFS + 1) * MADDW_TYPE)

#define ENETC_MADDW_HASH_TBW_SZ	64
stwuct enetc_mac_fiwtew {
	union {
		chaw mac_addw[ETH_AWEN];
		DECWAWE_BITMAP(mac_hash_tabwe, ENETC_MADDW_HASH_TBW_SZ);
	};
	int mac_addw_cnt;
};

#define ENETC_VWAN_HT_SIZE	64

enum enetc_vf_fwags {
	ENETC_VF_FWAG_PF_SET_MAC	= BIT(0),
};

stwuct enetc_vf_state {
	enum enetc_vf_fwags fwags;
};

stwuct enetc_pf {
	stwuct enetc_si *si;
	int num_vfs; /* numbew of active VFs, aftew swiov_init */
	int totaw_vfs; /* max numbew of VFs, set fow PF at pwobe */
	stwuct enetc_vf_state *vf_state;

	stwuct enetc_mac_fiwtew mac_fiwtew[ENETC_MAX_NUM_MAC_FWT];

	stwuct enetc_msg_swbd wxmsg[ENETC_MAX_NUM_VFS];
	stwuct wowk_stwuct msg_task;
	chaw msg_int_name[ENETC_INT_NAME_MAX];

	chaw vwan_pwomisc_simap; /* bitmap of SIs in VWAN pwomisc mode */
	DECWAWE_BITMAP(vwan_ht_fiwtew, ENETC_VWAN_HT_SIZE);
	DECWAWE_BITMAP(active_vwans, VWAN_N_VID);

	stwuct mii_bus *mdio; /* saved fow cweanup */
	stwuct mii_bus *imdio;
	stwuct phywink_pcs *pcs;

	phy_intewface_t if_mode;
	stwuct phywink_config phywink_config;
};

#define phywink_to_enetc_pf(config) \
	containew_of((config), stwuct enetc_pf, phywink_config)

int enetc_msg_psi_init(stwuct enetc_pf *pf);
void enetc_msg_psi_fwee(stwuct enetc_pf *pf);
void enetc_msg_handwe_wxmsg(stwuct enetc_pf *pf, int mbox_id, u16 *status);
