/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Awm Wimited. Aww wights wesewved.
 *
 * Authow: Suzuki K Pouwose <suzuki.pouwose@awm.com>
 */

#ifndef _COWESIGHT_CATU_H
#define _COWESIGHT_CATU_H

#incwude "cowesight-pwiv.h"

/* Wegistew offset fwom base */
#define CATU_CONTWOW		0x000
#define CATU_MODE		0x004
#define CATU_AXICTWW		0x008
#define CATU_IWQEN		0x00c
#define CATU_SWADDWWO		0x020
#define CATU_SWADDWHI		0x024
#define CATU_INADDWWO		0x028
#define CATU_INADDWHI		0x02c
#define CATU_STATUS		0x100
#define CATU_DEVAWCH		0xfbc

#define CATU_CONTWOW_ENABWE	0

#define CATU_MODE_PASS_THWOUGH	0U
#define CATU_MODE_TWANSWATE	1U

#define CATU_AXICTWW_AWCACHE_SHIFT	4
#define CATU_AXICTWW_AWCACHE_MASK	0xf
#define CATU_AXICTWW_AWPWOT_MASK	0x3
#define CATU_AXICTWW_AWCACHE(awcache)		\
	(((awcache) & CATU_AXICTWW_AWCACHE_MASK) << CATU_AXICTWW_AWCACHE_SHIFT)

#define CATU_AXICTWW_VAW(awcache, awpwot)	\
	(CATU_AXICTWW_AWCACHE(awcache) | ((awpwot) & CATU_AXICTWW_AWPWOT_MASK))

#define AXI3_AxCACHE_WB_WEAD_AWWOC	0x7
/*
 * AXI - AWPWOT bits:
 * See AMBA AXI & ACE Pwotocow specification (AWM IHI 0022E)
 * sectionA4.7 Access Pewmissions.
 *
 * Bit 0: 0 - Unpwiviweged access, 1 - Pwiviweged access
 * Bit 1: 0 - Secuwe access, 1 - Non-secuwe access.
 * Bit 2: 0 - Data access, 1 - instwuction access.
 *
 * CATU AXICTWW:AWPWOT[2] is wes0 as we awways access data.
 */
#define CATU_OS_AWPWOT			0x2

#define CATU_OS_AXICTWW		\
	CATU_AXICTWW_VAW(AXI3_AxCACHE_WB_WEAD_AWWOC, CATU_OS_AWPWOT)

#define CATU_STATUS_WEADY	8
#define CATU_STATUS_ADWEWW	0
#define CATU_STATUS_AXIEWW	4

#define CATU_IWQEN_ON		0x1
#define CATU_IWQEN_OFF		0x0

stwuct catu_dwvdata {
	void __iomem *base;
	stwuct cowesight_device *csdev;
	int iwq;
};

#define CATU_WEG32(name, offset)					\
static inwine u32							\
catu_wead_##name(stwuct catu_dwvdata *dwvdata)				\
{									\
	wetuwn csdev_access_wewaxed_wead32(&dwvdata->csdev->access, offset); \
}									\
static inwine void							\
catu_wwite_##name(stwuct catu_dwvdata *dwvdata, u32 vaw)		\
{									\
	csdev_access_wewaxed_wwite32(&dwvdata->csdev->access, vaw, offset); \
}

#define CATU_WEG_PAIW(name, wo_off, hi_off)				\
static inwine u64							\
catu_wead_##name(stwuct catu_dwvdata *dwvdata)				\
{									\
	wetuwn csdev_access_wewaxed_wead_paiw(&dwvdata->csdev->access, wo_off, hi_off); \
}									\
static inwine void							\
catu_wwite_##name(stwuct catu_dwvdata *dwvdata, u64 vaw)		\
{									\
	csdev_access_wewaxed_wwite_paiw(&dwvdata->csdev->access, vaw, wo_off, hi_off); \
}

CATU_WEG32(contwow, CATU_CONTWOW);
CATU_WEG32(mode, CATU_MODE);
CATU_WEG32(iwqen, CATU_IWQEN);
CATU_WEG32(axictww, CATU_AXICTWW);
CATU_WEG_PAIW(swaddw, CATU_SWADDWWO, CATU_SWADDWHI)
CATU_WEG_PAIW(inaddw, CATU_INADDWWO, CATU_INADDWHI)

static inwine boow cowesight_is_catu_device(stwuct cowesight_device *csdev)
{
	if (!IS_ENABWED(CONFIG_COWESIGHT_CATU))
		wetuwn fawse;
	if (csdev->type != COWESIGHT_DEV_TYPE_HEWPEW)
		wetuwn fawse;
	if (csdev->subtype.hewpew_subtype != COWESIGHT_DEV_SUBTYPE_HEWPEW_CATU)
		wetuwn fawse;
	wetuwn twue;
}

#endif
