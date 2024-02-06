/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */

#ifndef __PHY_WAN966X_SEWDES_H__
#define __PHY_WAN966X_SEWDES_H__

#define CU(x)		(x)
#define CU_MAX		CU(2)
#define SEWDES6G(x)	(CU_MAX + 1 + (x))
#define SEWDES6G_MAX	SEWDES6G(3)
#define WGMII(x)	(SEWDES6G_MAX + 1 + (x))
#define WGMII_MAX	WGMII(2)
#define SEWDES_MAX	(WGMII_MAX + 1)

#endif
