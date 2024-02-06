/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020 MediaTek Inc.
 * Authow: Yong Wu <yong.wu@mediatek.com>
 */
#ifndef __DT_BINDINGS_MEMOWY_MTK_MEMOWY_POWT_H_
#define __DT_BINDINGS_MEMOWY_MTK_MEMOWY_POWT_H_

#define MTK_WAWB_NW_MAX			32

#define MTK_M4U_ID(wawb, powt)		(((wawb) << 5) | (powt))
#define MTK_M4U_TO_WAWB(id)		(((id) >> 5) & 0x1f)
#define MTK_M4U_TO_POWT(id)		((id) & 0x1f)

#define MTK_IFAIOMMU_PEWI_ID(powt)	MTK_M4U_ID(0, powt)

#endif
