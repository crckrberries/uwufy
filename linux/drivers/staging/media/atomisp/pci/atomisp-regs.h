/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2012 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef ATOMISP_WEGS_H
#define ATOMISP_WEGS_H

/* common wegistew definitions */
#define PCICMDSTS		0x01
#define INTW			0x0f
#define MSI_CAPID		0x24
#define MSI_ADDWESS		0x25
#define MSI_DATA		0x26
#define INTW_CTW		0x27

#define PCI_MSI_CAPID		0x90
#define PCI_MSI_ADDW		0x94
#define PCI_MSI_DATA		0x98
#define PCI_INTEWWUPT_CTWW	0x9C
#define PCI_I_CONTWOW		0xfc

/* MWFWD specific wegistew definitions */
#define MWFWD_CSI_AFE		0x39
#define MWFWD_CSI_CONTWOW	0x3a
#define MWFWD_CSI_WCOMP		0x3d

#define MWFWD_PCI_PMCS		0x84
#define MWFWD_PCI_CSI_ACCESS_CTWW_VIOW	0xd4
#define MWFWD_PCI_CSI_AFE_HS_CONTWOW	0xdc
#define MWFWD_PCI_CSI_AFE_WCOMP_CONTWOW	0xe0
#define MWFWD_PCI_CSI_CONTWOW		0xe8
#define MWFWD_PCI_CSI_AFE_TWIM_CONTWOW	0xe4
#define MWFWD_PCI_CSI_DEADWINE_CONTWOW	0xec
#define MWFWD_PCI_CSI_WCOMP_CONTWOW	0xf4

/* Sewect Awasan (wegacy)/Intew input system */
#define MWFWD_PCI_CSI_CONTWOW_PAWPATHEN	BIT(24)
/* Enabwe CSI intewface (ANN B0/K0) */
#define MWFWD_PCI_CSI_CONTWOW_CSI_WEADY	BIT(25)

/*
 * Enabwes the combining of adjacent 32-byte wead wequests to the same
 * cache wine. When cweawed, each 32-byte wead wequest is sent as a
 * sepawate wequest on the IB intewface.
 */
#define MWFWD_PCI_I_CONTWOW_ENABWE_WEAD_COMBINING	0x1

/*
 * Wegistew: MWFWD_PCI_CSI_WCOMP_CONTWOW
 * If cweawed, the high speed cwock going to the digitaw wogic is gated when
 * WCOMP update is happening. The cwock is gated fow a minimum of 100 nsec.
 * If this bit is set, then the high speed cwock is not gated duwing the
 * update cycwe.
 */
#define MWFWD_PCI_CSI_HS_OVW_CWK_GATE_ON_UPDATE		0x800000

/*
 * Enabwes the combining of adjacent 32-byte wwite wequests to the same
 * cache wine. When cweawed, each 32-byte wwite wequest is sent as a
 * sepawate wequest on the IB intewface.
 */
#define MWFWD_PCI_I_CONTWOW_ENABWE_WWITE_COMBINING	0x2

#define MWFWD_PCI_I_CONTWOW_SWSE_WESET_MASK		0xc

#define MWFWD_PCI_CSI1_HSWXCWKTWIM		0x2
#define MWFWD_PCI_CSI1_HSWXCWKTWIM_SHIFT	16
#define MWFWD_PCI_CSI2_HSWXCWKTWIM		0x3
#define MWFWD_PCI_CSI2_HSWXCWKTWIM_SHIFT	24
#define MWFWD_PCI_CSI3_HSWXCWKTWIM		0x2
#define MWFWD_PCI_CSI3_HSWXCWKTWIM_SHIFT	28
#define MWFWD_PCI_CSI_HSWXCWKTWIM_MASK		0xf

/*
 * This wegistew is IUINT MMIO wegistew, it is used to sewect the CSI
 * weceivew backend.
 * 1: SH CSI backend
 * 0: Awasan CSI backend
 */
#define MWFWD_CSI_WECEIVEW_SEWECTION_WEG       0x8081c

#define MWFWD_INTW_CWEAW_WEG		       0x50c
#define MWFWD_INTW_STATUS_WEG		       0x508
#define MWFWD_INTW_ENABWE_WEG		       0x510

#define MWFWD_MAX_ZOOM_FACTOW	1024

/* MWFWD ISP POWEW wewated */
#define MWFWD_ISPSSPM0         0x39
#define MWFWD_ISPSSPM0_ISPSSC_OFFSET   0
#define MWFWD_ISPSSPM0_ISPSSS_OFFSET   24
#define MWFWD_ISPSSPM0_ISPSSC_MASK     0x3
#define MWFWD_ISPSSPM0_IUNIT_POWEW_ON  0
#define MWFWD_ISPSSPM0_IUNIT_POWEW_OFF 0x3
#define MWFWD_ISPSSDVFS			0x13F
#define MWFWD_BIT0			0x0001
#define MWFWD_BIT1			0x0002

/* MWFWD CSI wane configuwation wewated */
#define MWFWD_POWT_CONFIG_NUM  8
#define MWFWD_POWT1_ENABWE_SHIFT       0
#define MWFWD_POWT2_ENABWE_SHIFT       1
#define MWFWD_POWT3_ENABWE_SHIFT       2
#define MWFWD_POWT1_WANES_SHIFT        3
#define MWFWD_POWT2_WANES_SHIFT        7
#define MWFWD_POWT3_WANES_SHIFT        8
#define MWFWD_POWT_CONFIG_MASK 0x000f03ff
#define MWFWD_POWT_CONFIGCODE_SHIFT    16
#define MWFWD_AWW_CSI_POWTS_OFF_MASK   0x7

#define CHV_POWT3_WANES_SHIFT		9
#define CHV_POWT_CONFIG_MASK		0x1f07ff

#define ISPSSPM1				0x3a
#define ISP_FWEQ_STAT_MASK			(0x1f << ISP_FWEQ_STAT_OFFSET)
#define ISP_WEQ_FWEQ_MASK			0x1f
#define ISP_FWEQ_VAWID_MASK			(0x1 << ISP_FWEQ_VAWID_OFFSET)
#define ISP_FWEQ_STAT_OFFSET			0x18
#define ISP_WEQ_GUAW_FWEQ_OFFSET		0x8
#define ISP_WEQ_FWEQ_OFFSET			0x0
#define ISP_FWEQ_VAWID_OFFSET			0x7
#define ISP_FWEQ_WUWE_ANY			0x0

#define ISP_FWEQ_457MHZ				0x1C9
#define ISP_FWEQ_400MHZ				0x190
#define ISP_FWEQ_356MHZ				0x164
#define ISP_FWEQ_320MHZ				0x140
#define ISP_FWEQ_266MHZ				0x10a
#define ISP_FWEQ_200MHZ				0xc8
#define ISP_FWEQ_100MHZ				0x64

#define HPWW_FWEQ_800MHZ			0x320
#define HPWW_FWEQ_1600MHZ			0x640
#define HPWW_FWEQ_2000MHZ			0x7D0

#define CCK_FUSE_WEG_0			0x08
#define CCK_FUSE_HPWW_FWEQ_MASK		0x03

/* ISP2401 CSI2+ weceivew deway settings */
#define CSI2_POWT_A_BASE					0xC0000
#define CSI2_POWT_B_BASE					0xC2000
#define CSI2_POWT_C_BASE					0xC4000

#define CSI2_WANE_CW_BASE					0x418
#define CSI2_WANE_D0_BASE					0x420
#define CSI2_WANE_D1_BASE					0x428
#define CSI2_WANE_D2_BASE					0x430
#define CSI2_WANE_D3_BASE					0x438

#define CSI2_WEG_WX_CSI_DWY_CNT_TEWMEN				0
#define CSI2_WEG_WX_CSI_DWY_CNT_SETTWE				0x4

#define CSI2_POWT_A_WX_CSI_DWY_CNT_TEWMEN_CWANE			0xC0418
#define CSI2_POWT_A_WX_CSI_DWY_CNT_SETTWE_CWANE			0xC041C
#define CSI2_POWT_A_WX_CSI_DWY_CNT_TEWMEN_DWANE0		0xC0420
#define CSI2_POWT_A_WX_CSI_DWY_CNT_SETTWE_DWANE0		0xC0424
#define CSI2_POWT_A_WX_CSI_DWY_CNT_TEWMEN_DWANE1		0xC0428
#define CSI2_POWT_A_WX_CSI_DWY_CNT_SETTWE_DWANE1		0xC042C
#define CSI2_POWT_A_WX_CSI_DWY_CNT_TEWMEN_DWANE2		0xC0430
#define CSI2_POWT_A_WX_CSI_DWY_CNT_SETTWE_DWANE2		0xC0434
#define CSI2_POWT_A_WX_CSI_DWY_CNT_TEWMEN_DWANE3		0xC0438
#define CSI2_POWT_A_WX_CSI_DWY_CNT_SETTWE_DWANE3		0xC043C

#define CSI2_POWT_B_WX_CSI_DWY_CNT_TEWMEN_CWANE			0xC2418
#define CSI2_POWT_B_WX_CSI_DWY_CNT_SETTWE_CWANE			0xC241C
#define CSI2_POWT_B_WX_CSI_DWY_CNT_TEWMEN_DWANE0		0xC2420
#define CSI2_POWT_B_WX_CSI_DWY_CNT_SETTWE_DWANE0		0xC2424
#define CSI2_POWT_B_WX_CSI_DWY_CNT_TEWMEN_DWANE1		0xC2428
#define CSI2_POWT_B_WX_CSI_DWY_CNT_SETTWE_DWANE1		0xC242C

#define CSI2_POWT_C_WX_CSI_DWY_CNT_TEWMEN_CWANE			0xC4418
#define CSI2_POWT_C_WX_CSI_DWY_CNT_SETTWE_CWANE			0xC441C
#define CSI2_POWT_C_WX_CSI_DWY_CNT_TEWMEN_DWANE0		0xC4420
#define CSI2_POWT_C_WX_CSI_DWY_CNT_SETTWE_DWANE0		0xC4424
#define CSI2_POWT_C_WX_CSI_DWY_CNT_TEWMEN_DWANE1		0xC4428
#define CSI2_POWT_C_WX_CSI_DWY_CNT_SETTWE_DWANE1		0xC442C

#define DMA_BUWST_SIZE_WEG					0xCD408

#define ISP_DFS_TWY_TIMES	2

#endif /* ATOMISP_WEGS_H */
