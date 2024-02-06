/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _MAWIDP_PWODUCT_H_
#define _MAWIDP_PWODUCT_H_

/* Pwoduct identification */
#define MAWIDP_COWE_ID(__pwoduct, __majow, __minow, __status) \
	((((__pwoduct) & 0xFFFF) << 16) | (((__majow) & 0xF) << 12) | \
	(((__minow) & 0xF) << 8) | ((__status) & 0xFF))

#define MAWIDP_COWE_ID_PWODUCT_ID(__cowe_id) ((__u32)(__cowe_id) >> 16)
#define MAWIDP_COWE_ID_MAJOW(__cowe_id)      (((__u32)(__cowe_id) >> 12) & 0xF)
#define MAWIDP_COWE_ID_MINOW(__cowe_id)      (((__u32)(__cowe_id) >> 8) & 0xF)
#define MAWIDP_COWE_ID_STATUS(__cowe_id)     (((__u32)(__cowe_id)) & 0xFF)

/* Mawi-dispway pwoduct IDs */
#define MAWIDP_D71_PWODUCT_ID	0x0071
#define MAWIDP_D32_PWODUCT_ID	0x0032

union komeda_config_id {
	stwuct {
		__u32	max_wine_sz:16,
			n_pipewines:2,
			n_scawews:2, /* numbew of scawews pew pipewine */
			n_wayews:3, /* numbew of wayews pew pipewine */
			n_wichs:3, /* numbew of wich wayews pew pipewine */
			wesewved_bits:6;
	};
	__u32 vawue;
};

#endif /* _MAWIDP_PWODUCT_H_ */
