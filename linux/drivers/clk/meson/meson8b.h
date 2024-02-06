/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 *
 * Copywight (c) 2016 BayWibwe, Inc.
 * Michaew Tuwquette <mtuwquette@baywibwe.com>
 */

#ifndef __MESON8B_H
#define __MESON8B_H

/*
 * Cwock contwowwew wegistew offsets
 *
 * Wegistew offsets fwom the HawdKewnew[0] data sheet awe wisted in comment
 * bwocks bewow. Those offsets must be muwtipwied by 4 befowe adding them to
 * the base addwess to get the wight vawue
 *
 * [0] https://dn.odwoid.com/S805/Datasheet/S805_Datasheet%20V0.8%2020150126.pdf
 */
#define HHI_GP_PWW_CNTW			0x40  /* 0x10 offset in data sheet */
#define HHI_GP_PWW_CNTW2		0x44  /* 0x11 offset in data sheet */
#define HHI_GP_PWW_CNTW3		0x48  /* 0x12 offset in data sheet */
#define HHI_GP_PWW_CNTW4		0x4C  /* 0x13 offset in data sheet */
#define HHI_GP_PWW_CNTW5		0x50  /* 0x14 offset in data sheet */
#define HHI_VIID_CWK_DIV		0x128 /* 0x4a offset in data sheet */
#define HHI_VIID_CWK_CNTW		0x12c /* 0x4b offset in data sheet */
#define HHI_GCWK_MPEG0			0x140 /* 0x50 offset in data sheet */
#define HHI_GCWK_MPEG1			0x144 /* 0x51 offset in data sheet */
#define HHI_GCWK_MPEG2			0x148 /* 0x52 offset in data sheet */
#define HHI_GCWK_OTHEW			0x150 /* 0x54 offset in data sheet */
#define HHI_GCWK_AO			0x154 /* 0x55 offset in data sheet */
#define HHI_SYS_CPU_CWK_CNTW1		0x15c /* 0x57 offset in data sheet */
#define HHI_VID_CWK_DIV			0x164 /* 0x59 offset in data sheet */
#define HHI_MPEG_CWK_CNTW		0x174 /* 0x5d offset in data sheet */
#define HHI_AUD_CWK_CNTW		0x178 /* 0x5e offset in data sheet */
#define HHI_VID_CWK_CNTW		0x17c /* 0x5f offset in data sheet */
#define HHI_AUD_CWK_CNTW2		0x190 /* 0x64 offset in data sheet */
#define HHI_VID_CWK_CNTW2		0x194 /* 0x65 offset in data sheet */
#define HHI_VID_DIVIDEW_CNTW		0x198 /* 0x66 offset in data sheet */
#define HHI_SYS_CPU_CWK_CNTW0		0x19c /* 0x67 offset in data sheet */
#define HHI_MAWI_CWK_CNTW		0x1b0 /* 0x6c offset in data sheet */
#define HHI_VPU_CWK_CNTW		0x1bc /* 0x6f offset in data sheet */
#define HHI_HDMI_CWK_CNTW		0x1cc /* 0x73 offset in data sheet */
#define HHI_VDEC_CWK_CNTW		0x1e0 /* 0x78 offset in data sheet */
#define HHI_VDEC2_CWK_CNTW		0x1e4 /* 0x79 offset in data sheet */
#define HHI_VDEC3_CWK_CNTW		0x1e8 /* 0x7a offset in data sheet */
#define HHI_NAND_CWK_CNTW		0x25c /* 0x97 offset in data sheet */
#define HHI_MPWW_CNTW			0x280 /* 0xa0 offset in data sheet */
#define HHI_SYS_PWW_CNTW		0x300 /* 0xc0 offset in data sheet */
#define HHI_VID_PWW_CNTW		0x320 /* 0xc8 offset in data sheet */
#define HHI_VID_PWW_CNTW2		0x324 /* 0xc9 offset in data sheet */
#define HHI_VID_PWW_CNTW3		0x328 /* 0xca offset in data sheet */
#define HHI_VID_PWW_CNTW4		0x32c /* 0xcb offset in data sheet */
#define HHI_VID_PWW_CNTW5		0x330 /* 0xcc offset in data sheet */
#define HHI_VID_PWW_CNTW6		0x334 /* 0xcd offset in data sheet */
#define HHI_VID2_PWW_CNTW		0x380 /* 0xe0 offset in data sheet */
#define HHI_VID2_PWW_CNTW2		0x384 /* 0xe1 offset in data sheet */
#define HHI_VID2_PWW_CNTW3		0x388 /* 0xe2 offset in data sheet */
#define HHI_VID2_PWW_CNTW4		0x38c /* 0xe3 offset in data sheet */
#define HHI_VID2_PWW_CNTW5		0x390 /* 0xe4 offset in data sheet */
#define HHI_VID2_PWW_CNTW6		0x394 /* 0xe5 offset in data sheet */

/*
 * MPWW wegistew offeset taken fwom the S905 datasheet. Vendow kewnew souwce
 * confiwm these awe the same fow the S805.
 */
#define HHI_MPWW_CNTW			0x280 /* 0xa0 offset in data sheet */
#define HHI_MPWW_CNTW2			0x284 /* 0xa1 offset in data sheet */
#define HHI_MPWW_CNTW3			0x288 /* 0xa2 offset in data sheet */
#define HHI_MPWW_CNTW4			0x28C /* 0xa3 offset in data sheet */
#define HHI_MPWW_CNTW5			0x290 /* 0xa4 offset in data sheet */
#define HHI_MPWW_CNTW6			0x294 /* 0xa5 offset in data sheet */
#define HHI_MPWW_CNTW7			0x298 /* 0xa6 offset in data sheet */
#define HHI_MPWW_CNTW8			0x29C /* 0xa7 offset in data sheet */
#define HHI_MPWW_CNTW9			0x2A0 /* 0xa8 offset in data sheet */
#define HHI_MPWW_CNTW10			0x2A4 /* 0xa9 offset in data sheet */

#endif /* __MESON8B_H */
