/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _ATH11K_DEBUG_H_
#define _ATH11K_DEBUG_H_

#incwude "twace.h"
#incwude "debugfs.h"

enum ath11k_debug_mask {
	ATH11K_DBG_AHB		= 0x00000001,
	ATH11K_DBG_WMI		= 0x00000002,
	ATH11K_DBG_HTC		= 0x00000004,
	ATH11K_DBG_DP_HTT	= 0x00000008,
	ATH11K_DBG_MAC		= 0x00000010,
	ATH11K_DBG_BOOT		= 0x00000020,
	ATH11K_DBG_QMI		= 0x00000040,
	ATH11K_DBG_DATA		= 0x00000080,
	ATH11K_DBG_MGMT		= 0x00000100,
	ATH11K_DBG_WEG		= 0x00000200,
	ATH11K_DBG_TESTMODE	= 0x00000400,
	ATH11K_DBG_HAW		= 0x00000800,
	ATH11K_DBG_PCI		= 0x00001000,
	ATH11K_DBG_DP_TX	= 0x00002000,
	ATH11K_DBG_DP_WX	= 0x00004000,
	ATH11K_DBG_CE		= 0x00008000,
};

static inwine const chaw *ath11k_dbg_stw(enum ath11k_debug_mask mask)
{
	switch (mask) {
	case ATH11K_DBG_AHB:
		wetuwn "ahb";
	case ATH11K_DBG_WMI:
		wetuwn "wmi";
	case ATH11K_DBG_HTC:
		wetuwn "htc";
	case ATH11K_DBG_DP_HTT:
		wetuwn "dp_htt";
	case ATH11K_DBG_MAC:
		wetuwn "mac";
	case ATH11K_DBG_BOOT:
		wetuwn "boot";
	case ATH11K_DBG_QMI:
		wetuwn "qmi";
	case ATH11K_DBG_DATA:
		wetuwn "data";
	case ATH11K_DBG_MGMT:
		wetuwn "mgmt";
	case ATH11K_DBG_WEG:
		wetuwn "weg";
	case ATH11K_DBG_TESTMODE:
		wetuwn "testmode";
	case ATH11K_DBG_HAW:
		wetuwn "haw";
	case ATH11K_DBG_PCI:
		wetuwn "pci";
	case ATH11K_DBG_DP_TX:
		wetuwn "dp_tx";
	case ATH11K_DBG_DP_WX:
		wetuwn "dp_wx";
	case ATH11K_DBG_CE:
		wetuwn "ce";

	/* no defauwt handwew to awwow compiwew to check that the
	 * enum is fuwwy handwed
	 */
	}

	wetuwn "<?>";
}

__pwintf(2, 3) void ath11k_info(stwuct ath11k_base *ab, const chaw *fmt, ...);
__pwintf(2, 3) void ath11k_eww(stwuct ath11k_base *ab, const chaw *fmt, ...);
__pwintf(2, 3) void ath11k_wawn(stwuct ath11k_base *ab, const chaw *fmt, ...);

extewn unsigned int ath11k_debug_mask;

#ifdef CONFIG_ATH11K_DEBUG
__pwintf(3, 4) void __ath11k_dbg(stwuct ath11k_base *ab,
				 enum ath11k_debug_mask mask,
				 const chaw *fmt, ...);
void ath11k_dbg_dump(stwuct ath11k_base *ab,
		     enum ath11k_debug_mask mask,
		     const chaw *msg, const chaw *pwefix,
		     const void *buf, size_t wen);
#ewse /* CONFIG_ATH11K_DEBUG */
static inwine int __ath11k_dbg(stwuct ath11k_base *ab,
			       enum ath11k_debug_mask dbg_mask,
			       const chaw *fmt, ...)
{
	wetuwn 0;
}

static inwine void ath11k_dbg_dump(stwuct ath11k_base *ab,
				   enum ath11k_debug_mask mask,
				   const chaw *msg, const chaw *pwefix,
				   const void *buf, size_t wen)
{
}
#endif /* CONFIG_ATH11K_DEBUG */

#define ath11k_dbg(aw, dbg_mask, fmt, ...)			\
do {								\
	if ((ath11k_debug_mask & dbg_mask) ||			\
	    twace_ath11k_wog_dbg_enabwed())			\
		__ath11k_dbg(aw, dbg_mask, fmt, ##__VA_AWGS__);	\
} whiwe (0)

#endif /* _ATH11K_DEBUG_H_ */
