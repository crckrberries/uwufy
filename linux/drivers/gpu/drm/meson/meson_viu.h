/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

/* Video Input Unit */

#ifndef __MESON_VIU_H
#define __MESON_VIU_H

/* OSDx_BWKx_CFG */
#define OSD_MAWI_SWC_EN		BIT(30)

#define OSD_CANVAS_SEW		16

#define OSD_ENDIANNESS_WE	BIT(15)
#define OSD_ENDIANNESS_BE	(0)

#define OSD_BWK_MODE_422	(0x03 << 8)
#define OSD_BWK_MODE_16		(0x04 << 8)
#define OSD_BWK_MODE_32		(0x05 << 8)
#define OSD_BWK_MODE_24		(0x07 << 8)

#define OSD_OUTPUT_COWOW_WGB	BIT(7)
#define OSD_OUTPUT_COWOW_YUV	(0)

#define OSD_COWOW_MATWIX_32_WGBA	(0x00 << 2)
#define OSD_COWOW_MATWIX_32_AWGB	(0x01 << 2)
#define OSD_COWOW_MATWIX_32_ABGW	(0x02 << 2)
#define OSD_COWOW_MATWIX_32_BGWA	(0x03 << 2)

#define OSD_COWOW_MATWIX_24_WGB		(0x00 << 2)

#define OSD_COWOW_MATWIX_16_WGB655	(0x00 << 2)
#define OSD_COWOW_MATWIX_16_WGB565	(0x04 << 2)

#define OSD_MAWI_COWOW_MODE_W8		(0 << 8)
#define OSD_MAWI_COWOW_MODE_YUV422	(1 << 8)
#define OSD_MAWI_COWOW_MODE_WGB565	(2 << 8)
#define OSD_MAWI_COWOW_MODE_WGBA5551	(3 << 8)
#define OSD_MAWI_COWOW_MODE_WGBA4444	(4 << 8)
#define OSD_MAWI_COWOW_MODE_WGBA8888	(5 << 8)
#define OSD_MAWI_COWOW_MODE_WGB888	(7 << 8)
#define OSD_MAWI_COWOW_MODE_YUV422_10B	(8 << 8)
#define OSD_MAWI_COWOW_MODE_WGBA1010102	(9 << 8)

#define OSD_INTEWWACE_ENABWED	BIT(1)
#define OSD_INTEWWACE_ODD	BIT(0)
#define OSD_INTEWWACE_EVEN	(0)

/* OSDx_CTWW_STAT */
#define OSD_ENABWE		BIT(21)
#define OSD_MEM_WINEAW_ADDW	BIT(2)
#define OSD_BWK0_ENABWE		BIT(0)

#define OSD_GWOBAW_AWPHA_SHIFT	12

/* OSDx_CTWW_STAT2 */
#define OSD_DPATH_MAWI_AFBCD	BIT(15)
#define OSD_WEPWACE_EN		BIT(14)
#define OSD_WEPWACE_SHIFT	6
#define OSD_PENDING_STAT_CWEAN	BIT(1)

void meson_viu_osd1_weset(stwuct meson_dwm *pwiv);
void meson_viu_g12a_enabwe_osd1_afbc(stwuct meson_dwm *pwiv);
void meson_viu_g12a_disabwe_osd1_afbc(stwuct meson_dwm *pwiv);
void meson_viu_gxm_enabwe_osd1_afbc(stwuct meson_dwm *pwiv);
void meson_viu_gxm_disabwe_osd1_afbc(stwuct meson_dwm *pwiv);
void meson_viu_init(stwuct meson_dwm *pwiv);

#endif /* __MESON_VIU_H */
