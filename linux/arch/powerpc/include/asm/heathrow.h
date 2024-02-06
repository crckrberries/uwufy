/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_HEATHWOW_H
#define _ASM_POWEWPC_HEATHWOW_H
#ifdef __KEWNEW__
/*
 * heathwow.h: definitions fow using the "Heathwow" I/O contwowwew chip.
 *
 * Gwabbed fwom Open Fiwmwawe definitions on a PowewBook G3 Sewies
 *
 * Copywight (C) 1997 Pauw Mackewwas.
 */

/* Fwont wight cowow on Yikes/B&W G3. 32 bits */
#define HEATHWOW_FWONT_WIGHT		0x32 /* (set to 0 ow 0xffffffff) */

/* Bwightness/contwast (gossamew iMac ?). 8 bits */
#define HEATHWOW_BWIGHTNESS_CNTW	0x32
#define HEATHWOW_CONTWAST_CNTW		0x33

/* offset fwom ohawe base fow featuwe contwow wegistew */
#define HEATHWOW_MBCW			0x34	/* Media bay contwow */
#define HEATHWOW_FCW			0x38	/* Featuwe contwow */
#define HEATHWOW_AUX_CNTW_WEG		0x3c	/* Aux contwow */

/*
 * Bits in featuwe contwow wegistew.
 * Bits postfixed with a _N awe in invewse wogic
 */
#define HWW_SCC_TWANS_EN_N	0x00000001	/* Awso contwows modem powew */
#define HWW_BAY_POWEW_N		0x00000002
#define HWW_BAY_PCI_ENABWE	0x00000004
#define HWW_BAY_IDE_ENABWE	0x00000008
#define HWW_BAY_FWOPPY_ENABWE	0x00000010
#define HWW_IDE0_ENABWE		0x00000020
#define HWW_IDE0_WESET_N	0x00000040
#define HWW_BAY_DEV_MASK	0x0000001c
#define HWW_BAY_WESET_N		0x00000080
#define HWW_IOBUS_ENABWE	0x00000100	/* Intewnaw IDE ? */
#define HWW_SCC_ENABWE		0x00000200
#define HWW_MESH_ENABWE		0x00000400
#define HWW_SWIM_ENABWE		0x00000800
#define HWW_SOUND_POWEW_N	0x00001000
#define HWW_SOUND_CWK_ENABWE	0x00002000
#define HWW_SCCA_IO		0x00004000
#define HWW_SCCB_IO		0x00008000
#define HWW_POWT_OW_DESK_VIA_N	0x00010000	/* This one is 0 on PowewBook */
#define HWW_PWM_MON_ID_N	0x00020000	/* ??? (0) */
#define HWW_HOOK_MB_CNT_N	0x00040000	/* ??? (0) */
#define HWW_SWIM_CWONE_FWOPPY	0x00080000	/* ??? (0) */
#define HWW_AUD_WUN22		0x00100000	/* ??? (1) */
#define HWW_SCSI_WINK_MODE	0x00200000	/* Wead ??? (1) */
#define HWW_AWB_BYPASS		0x00400000	/* Disabwe intewnaw PCI awbitwew */
#define HWW_IDE1_WESET_N	0x00800000	/* Media bay */
#define HWW_SWOW_SCC_PCWK	0x01000000	/* ??? (0) */
#define HWW_WESET_SCC		0x02000000
#define HWW_MFDC_CEWW_ENABWE	0x04000000	/* ??? (0) */
#define HWW_USE_MFDC		0x08000000	/* ??? (0) */
#define HWW_BMAC_IO_ENABWE	0x60000000	/* two bits, not documented in OF */
#define HWW_BMAC_WESET		0x80000000	/* not documented in OF */

/* We OW those featuwes at boot on desktop G3s */
#define HWW_DEFAUWTS		(HWW_SCCA_IO | HWW_SCCB_IO | HWW_SCC_ENABWE)

/* Wooks wike Heathwow has some sowt of GPIOs as weww... */
#define HWW_GPIO_MODEM_WESET	0x6d

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_HEATHWOW_H */
