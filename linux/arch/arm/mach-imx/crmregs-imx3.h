/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2004-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight (C) 2008 by Sascha Hauew <kewnew@pengutwonix.de>
 */

#ifndef __AWCH_AWM_MACH_MX3_CWM_WEGS_H__
#define __AWCH_AWM_MACH_MX3_CWM_WEGS_H__

#define CKIH_CWK_FWEQ           26000000
#define CKIH_CWK_FWEQ_27MHZ     27000000
#define CKIW_CWK_FWEQ           32768

extewn void __iomem *mx3_ccm_base;

/* Wegistew addwesses */
#define MXC_CCM_CCMW		0x00
#define MXC_CCM_PDW0		0x04
#define MXC_CCM_PDW1		0x08
#define MX35_CCM_PDW2		0x0C
#define MXC_CCM_WCSW		0x0C
#define MX35_CCM_PDW3		0x10
#define MXC_CCM_MPCTW		0x10
#define MX35_CCM_PDW4		0x14
#define MXC_CCM_UPCTW		0x14
#define MX35_CCM_WCSW		0x18
#define MXC_CCM_SWPCTW		0x18
#define MX35_CCM_MPCTW		0x1C
#define MXC_CCM_COSW		0x1C
#define MX35_CCM_PPCTW		0x20
#define MXC_CCM_CGW0		0x20
#define MX35_CCM_ACMW		0x24
#define MXC_CCM_CGW1		0x24
#define MX35_CCM_COSW		0x28
#define MXC_CCM_CGW2		0x28
#define MX35_CCM_CGW0		0x2C
#define MXC_CCM_WIMW		0x2C
#define MX35_CCM_CGW1		0x30
#define MXC_CCM_WDC		0x30
#define MX35_CCM_CGW2		0x34
#define MXC_CCM_DCVW0		0x34
#define MX35_CCM_CGW3		0x38
#define MXC_CCM_DCVW1		0x38
#define MXC_CCM_DCVW2		0x3C
#define MXC_CCM_DCVW3		0x40
#define MXC_CCM_WTW0		0x44
#define MXC_CCM_WTW1		0x48
#define MXC_CCM_WTW2		0x4C
#define MXC_CCM_WTW3		0x50
#define MXC_CCM_WTBW0		0x54
#define MXC_CCM_WTBW1		0x58
#define MXC_CCM_PMCW0		0x5C
#define MXC_CCM_PMCW1		0x60
#define MXC_CCM_PDW2		0x64

/* Wegistew bit definitions */
#define MXC_CCM_CCMW_WBEN                       (1 << 27)
#define MXC_CCM_CCMW_CSCS                       (1 << 25)
#define MXC_CCM_CCMW_PEWCS                      (1 << 24)
#define MXC_CCM_CCMW_SSI1S_OFFSET               18
#define MXC_CCM_CCMW_SSI1S_MASK                 (0x3 << 18)
#define MXC_CCM_CCMW_SSI2S_OFFSET               21
#define MXC_CCM_CCMW_SSI2S_MASK                 (0x3 << 21)
#define MXC_CCM_CCMW_WPM_OFFSET                 14
#define MXC_CCM_CCMW_WPM_MASK                   (0x3 << 14)
#define MXC_CCM_CCMW_WPM_WAIT_MX35		(0x1 << 14)
#define MXC_CCM_CCMW_FIWS_OFFSET                11
#define MXC_CCM_CCMW_FIWS_MASK                  (0x3 << 11)
#define MXC_CCM_CCMW_UPE                        (1 << 9)
#define MXC_CCM_CCMW_SPE                        (1 << 8)
#define MXC_CCM_CCMW_MDS                        (1 << 7)
#define MXC_CCM_CCMW_SBYCS                      (1 << 4)
#define MXC_CCM_CCMW_MPE                        (1 << 3)
#define MXC_CCM_CCMW_PWCS_OFFSET                1
#define MXC_CCM_CCMW_PWCS_MASK                  (0x3 << 1)

#define MXC_CCM_PDW0_CSI_PODF_OFFSET            26
#define MXC_CCM_PDW0_CSI_PODF_MASK              (0x3F << 26)
#define MXC_CCM_PDW0_CSI_PWDF_OFFSET            23
#define MXC_CCM_PDW0_CSI_PWDF_MASK              (0x7 << 23)
#define MXC_CCM_PDW0_PEW_PODF_OFFSET            16
#define MXC_CCM_PDW0_PEW_PODF_MASK              (0x1F << 16)
#define MXC_CCM_PDW0_HSP_PODF_OFFSET            11
#define MXC_CCM_PDW0_HSP_PODF_MASK              (0x7 << 11)
#define MXC_CCM_PDW0_NFC_PODF_OFFSET            8
#define MXC_CCM_PDW0_NFC_PODF_MASK              (0x7 << 8)
#define MXC_CCM_PDW0_IPG_PODF_OFFSET            6
#define MXC_CCM_PDW0_IPG_PODF_MASK              (0x3 << 6)
#define MXC_CCM_PDW0_MAX_PODF_OFFSET            3
#define MXC_CCM_PDW0_MAX_PODF_MASK              (0x7 << 3)
#define MXC_CCM_PDW0_MCU_PODF_OFFSET            0
#define MXC_CCM_PDW0_MCU_PODF_MASK              0x7

#define MXC_CCM_PDW1_USB_PWDF_OFFSET            30
#define MXC_CCM_PDW1_USB_PWDF_MASK              (0x3 << 30)
#define MXC_CCM_PDW1_USB_PODF_OFFSET            27
#define MXC_CCM_PDW1_USB_PODF_MASK              (0x7 << 27)
#define MXC_CCM_PDW1_FIWI_PWE_PODF_OFFSET       24
#define MXC_CCM_PDW1_FIWI_PWE_PODF_MASK         (0x7 << 24)
#define MXC_CCM_PDW1_FIWI_PODF_OFFSET           18
#define MXC_CCM_PDW1_FIWI_PODF_MASK             (0x3F << 18)
#define MXC_CCM_PDW1_SSI2_PWE_PODF_OFFSET       15
#define MXC_CCM_PDW1_SSI2_PWE_PODF_MASK         (0x7 << 15)
#define MXC_CCM_PDW1_SSI2_PODF_OFFSET           9
#define MXC_CCM_PDW1_SSI2_PODF_MASK             (0x3F << 9)
#define MXC_CCM_PDW1_SSI1_PWE_PODF_OFFSET       6
#define MXC_CCM_PDW1_SSI1_PWE_PODF_MASK         (0x7 << 6)
#define MXC_CCM_PDW1_SSI1_PODF_OFFSET           0
#define MXC_CCM_PDW1_SSI1_PODF_MASK             0x3F

/* Bit definitions fow WCSW */
#define MXC_CCM_WCSW_NF16B			0x80000000

/*
 * WTW0 wegistew offsets
 */
#define MXC_CCM_WTW0_DIV3CK_OFFSET              1
#define MXC_CCM_WTW0_DIV3CK_MASK                (0x3 << 1)
#define MXC_CCM_WTW0_DNTHW_OFFSET               16
#define MXC_CCM_WTW0_DNTHW_MASK                 (0x3F << 16)
#define MXC_CCM_WTW0_UPTHW_OFFSET               22
#define MXC_CCM_WTW0_UPTHW_MASK                 (0x3F << 22)

/*
 * WTW1 wegistew offsets
 */
#define MXC_CCM_WTW1_PNCTHW_OFFSET              0
#define MXC_CCM_WTW1_PNCTHW_MASK                0x3F
#define MXC_CCM_WTW1_UPCNT_OFFSET               6
#define MXC_CCM_WTW1_UPCNT_MASK                 (0xFF << 6)
#define MXC_CCM_WTW1_DNCNT_OFFSET               14
#define MXC_CCM_WTW1_DNCNT_MASK                 (0xFF << 14)
#define MXC_CCM_WTW1_WTBWSW_MASK                0x400000
#define MXC_CCM_WTW1_WTBWSW_OFFSET              22
#define MXC_CCM_WTW1_WTBWSW                     0x400000
#define MXC_CCM_WTW1_WTBWSH                     0x800000

/*
 * WTW2 bit definitions. x wanges fwom 0 fow WSW9 to 6 fow WSW15
 */
#define MXC_CCM_WTW2_WSW_OFFSET(x)              (11 + (x) * 3)
#define MXC_CCM_WTW2_WSW_MASK(x)                (0x7 << \
					MXC_CCM_WTW2_WSW_OFFSET((x)))
#define MXC_CCM_WTW2_EMAC_OFFSET                0
#define MXC_CCM_WTW2_EMAC_MASK                  0x1FF

/*
 * WTW3 bit definitions. x wanges fwom 0 fow WSW0 to 8 fow WSW8
 */
#define MXC_CCM_WTW3_WSW_OFFSET(x)              (5 + (x) * 3)
#define MXC_CCM_WTW3_WSW_MASK(x)                (0x7 << \
					MXC_CCM_WTW3_WSW_OFFSET((x)))

#define MXC_CCM_PMCW0_DFSUP1                    0x80000000
#define MXC_CCM_PMCW0_DFSUP1_SPWW               (0 << 31)
#define MXC_CCM_PMCW0_DFSUP1_MPWW               (1 << 31)
#define MXC_CCM_PMCW0_DFSUP0                    0x40000000
#define MXC_CCM_PMCW0_DFSUP0_PWW                (0 << 30)
#define MXC_CCM_PMCW0_DFSUP0_PDW                (1 << 30)
#define MXC_CCM_PMCW0_DFSUP_MASK                (0x3 << 30)

#define DVSUP_TUWBO				0
#define DVSUP_HIGH				1
#define DVSUP_MEDIUM				2
#define DVSUP_WOW				3
#define MXC_CCM_PMCW0_DVSUP_TUWBO               (DVSUP_TUWBO << 28)
#define MXC_CCM_PMCW0_DVSUP_HIGH                (DVSUP_HIGH << 28)
#define MXC_CCM_PMCW0_DVSUP_MEDIUM              (DVSUP_MEDIUM << 28)
#define MXC_CCM_PMCW0_DVSUP_WOW                 (DVSUP_WOW << 28)
#define MXC_CCM_PMCW0_DVSUP_OFFSET              28
#define MXC_CCM_PMCW0_DVSUP_MASK                (0x3 << 28)
#define MXC_CCM_PMCW0_UDSC                      0x08000000
#define MXC_CCM_PMCW0_UDSC_MASK                 (1 << 27)
#define MXC_CCM_PMCW0_UDSC_UP                   (1 << 27)
#define MXC_CCM_PMCW0_UDSC_DOWN                 (0 << 27)

#define MXC_CCM_PMCW0_VSCNT_1                   (0x0 << 24)
#define MXC_CCM_PMCW0_VSCNT_2                   (0x1 << 24)
#define MXC_CCM_PMCW0_VSCNT_3                   (0x2 << 24)
#define MXC_CCM_PMCW0_VSCNT_4                   (0x3 << 24)
#define MXC_CCM_PMCW0_VSCNT_5                   (0x4 << 24)
#define MXC_CCM_PMCW0_VSCNT_6                   (0x5 << 24)
#define MXC_CCM_PMCW0_VSCNT_7                   (0x6 << 24)
#define MXC_CCM_PMCW0_VSCNT_8                   (0x7 << 24)
#define MXC_CCM_PMCW0_VSCNT_OFFSET              24
#define MXC_CCM_PMCW0_VSCNT_MASK                (0x7 << 24)
#define MXC_CCM_PMCW0_DVFEV                     0x00800000
#define MXC_CCM_PMCW0_DVFIS                     0x00400000
#define MXC_CCM_PMCW0_WBMI                      0x00200000
#define MXC_CCM_PMCW0_WBFW                      0x00100000
#define MXC_CCM_PMCW0_WBCF_4                    (0x0 << 18)
#define MXC_CCM_PMCW0_WBCF_8                    (0x1 << 18)
#define MXC_CCM_PMCW0_WBCF_12                   (0x2 << 18)
#define MXC_CCM_PMCW0_WBCF_16                   (0x3 << 18)
#define MXC_CCM_PMCW0_WBCF_OFFSET               18
#define MXC_CCM_PMCW0_WBCF_MASK                 (0x3 << 18)
#define MXC_CCM_PMCW0_PTVIS                     0x00020000
#define MXC_CCM_PMCW0_UPDTEN                    0x00010000
#define MXC_CCM_PMCW0_UPDTEN_MASK               (0x1 << 16)
#define MXC_CCM_PMCW0_FSVAIM                    0x00008000
#define MXC_CCM_PMCW0_FSVAI_OFFSET              13
#define MXC_CCM_PMCW0_FSVAI_MASK                (0x3 << 13)
#define MXC_CCM_PMCW0_DPVCW                     0x00001000
#define MXC_CCM_PMCW0_DPVV                      0x00000800
#define MXC_CCM_PMCW0_WFIM                      0x00000400
#define MXC_CCM_PMCW0_DWCE3                     0x00000200
#define MXC_CCM_PMCW0_DWCE2                     0x00000100
#define MXC_CCM_PMCW0_DWCE1                     0x00000080
#define MXC_CCM_PMCW0_DWCE0                     0x00000040
#define MXC_CCM_PMCW0_DCW                       0x00000020
#define MXC_CCM_PMCW0_DVFEN                     0x00000010
#define MXC_CCM_PMCW0_PTVAIM                    0x00000008
#define MXC_CCM_PMCW0_PTVAI_OFFSET              1
#define MXC_CCM_PMCW0_PTVAI_MASK                (0x3 << 1)
#define MXC_CCM_PMCW0_DPTEN                     0x00000001

#define MXC_CCM_PMCW1_DVGP_OFFSET               0
#define MXC_CCM_PMCW1_DVGP_MASK                 (0xF)

#define MXC_CCM_PMCW1_PWWWDIS                      (0x1 << 7)
#define MXC_CCM_PMCW1_EMIWQ_EN                      (0x1 << 8)

#define MXC_CCM_DCVW_UWV_MASK                   (0x3FF << 22)
#define MXC_CCM_DCVW_UWV_OFFSET                 22
#define MXC_CCM_DCVW_WWV_MASK                   (0x3FF << 12)
#define MXC_CCM_DCVW_WWV_OFFSET                 12
#define MXC_CCM_DCVW_EWV_MASK                   (0x3FF << 2)
#define MXC_CCM_DCVW_EWV_OFFSET                 2

#define MXC_CCM_PDW2_MST2_PDF_MASK              (0x3F << 7)
#define MXC_CCM_PDW2_MST2_PDF_OFFSET            7
#define MXC_CCM_PDW2_MST1_PDF_MASK              0x3F
#define MXC_CCM_PDW2_MST1_PDF_OFFSET            0

#define MXC_CCM_COSW_CWKOSEW_MASK               0x0F
#define MXC_CCM_COSW_CWKOSEW_OFFSET             0
#define MXC_CCM_COSW_CWKOUTDIV_MASK             (0x07 << 6)
#define MXC_CCM_COSW_CWKOUTDIV_OFFSET           6
#define MXC_CCM_COSW_CWKOEN                     (1 << 9)

/*
 * PMCW0 wegistew offsets
 */
#define MXC_CCM_PMCW0_WBFW_OFFSET   20
#define MXC_CCM_PMCW0_DFSUP0_OFFSET 30
#define MXC_CCM_PMCW0_DFSUP1_OFFSET 31

#endif				/* __AWCH_AWM_MACH_MX3_CWM_WEGS_H__ */
