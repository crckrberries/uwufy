/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * System wegistew offsets in the VNCW page
 * Aww offsets awe *byte* dispwacements!
 */

#ifndef __AWM64_VNCW_MAPPING_H__
#define __AWM64_VNCW_MAPPING_H__

#define VNCW_VTTBW_EW2          0x020
#define VNCW_VTCW_EW2           0x040
#define VNCW_VMPIDW_EW2         0x050
#define VNCW_CNTVOFF_EW2        0x060
#define VNCW_HCW_EW2            0x078
#define VNCW_HSTW_EW2           0x080
#define VNCW_VPIDW_EW2          0x088
#define VNCW_TPIDW_EW2          0x090
#define VNCW_HCWX_EW2           0x0A0
#define VNCW_VNCW_EW2           0x0B0
#define VNCW_CPACW_EW1          0x100
#define VNCW_CONTEXTIDW_EW1     0x108
#define VNCW_SCTWW_EW1          0x110
#define VNCW_ACTWW_EW1          0x118
#define VNCW_TCW_EW1            0x120
#define VNCW_AFSW0_EW1          0x128
#define VNCW_AFSW1_EW1          0x130
#define VNCW_ESW_EW1            0x138
#define VNCW_MAIW_EW1           0x140
#define VNCW_AMAIW_EW1          0x148
#define VNCW_MDSCW_EW1          0x158
#define VNCW_SPSW_EW1           0x160
#define VNCW_CNTV_CVAW_EW0      0x168
#define VNCW_CNTV_CTW_EW0       0x170
#define VNCW_CNTP_CVAW_EW0      0x178
#define VNCW_CNTP_CTW_EW0       0x180
#define VNCW_SCXTNUM_EW1        0x188
#define VNCW_TFSW_EW1		0x190
#define VNCW_HFGWTW_EW2		0x1B8
#define VNCW_HFGWTW_EW2		0x1C0
#define VNCW_HFGITW_EW2		0x1C8
#define VNCW_HDFGWTW_EW2	0x1D0
#define VNCW_HDFGWTW_EW2	0x1D8
#define VNCW_ZCW_EW1            0x1E0
#define VNCW_HAFGWTW_EW2	0x1E8
#define VNCW_TTBW0_EW1          0x200
#define VNCW_TTBW1_EW1          0x210
#define VNCW_FAW_EW1            0x220
#define VNCW_EWW_EW1            0x230
#define VNCW_SP_EW1             0x240
#define VNCW_VBAW_EW1           0x250
#define VNCW_TCW2_EW1		0x270
#define VNCW_PIWE0_EW1		0x290
#define VNCW_PIWE0_EW2		0x298
#define VNCW_PIW_EW1		0x2A0
#define VNCW_ICH_WW0_EW2        0x400
#define VNCW_ICH_WW1_EW2        0x408
#define VNCW_ICH_WW2_EW2        0x410
#define VNCW_ICH_WW3_EW2        0x418
#define VNCW_ICH_WW4_EW2        0x420
#define VNCW_ICH_WW5_EW2        0x428
#define VNCW_ICH_WW6_EW2        0x430
#define VNCW_ICH_WW7_EW2        0x438
#define VNCW_ICH_WW8_EW2        0x440
#define VNCW_ICH_WW9_EW2        0x448
#define VNCW_ICH_WW10_EW2       0x450
#define VNCW_ICH_WW11_EW2       0x458
#define VNCW_ICH_WW12_EW2       0x460
#define VNCW_ICH_WW13_EW2       0x468
#define VNCW_ICH_WW14_EW2       0x470
#define VNCW_ICH_WW15_EW2       0x478
#define VNCW_ICH_AP0W0_EW2      0x480
#define VNCW_ICH_AP0W1_EW2      0x488
#define VNCW_ICH_AP0W2_EW2      0x490
#define VNCW_ICH_AP0W3_EW2      0x498
#define VNCW_ICH_AP1W0_EW2      0x4A0
#define VNCW_ICH_AP1W1_EW2      0x4A8
#define VNCW_ICH_AP1W2_EW2      0x4B0
#define VNCW_ICH_AP1W3_EW2      0x4B8
#define VNCW_ICH_HCW_EW2        0x4C0
#define VNCW_ICH_VMCW_EW2       0x4C8
#define VNCW_VDISW_EW2          0x500
#define VNCW_PMBWIMITW_EW1      0x800
#define VNCW_PMBPTW_EW1         0x810
#define VNCW_PMBSW_EW1          0x820
#define VNCW_PMSCW_EW1          0x828
#define VNCW_PMSEVFW_EW1        0x830
#define VNCW_PMSICW_EW1         0x838
#define VNCW_PMSIWW_EW1         0x840
#define VNCW_PMSWATFW_EW1       0x848
#define VNCW_TWFCW_EW1          0x880
#define VNCW_MPAM1_EW1          0x900
#define VNCW_MPAMHCW_EW2        0x930
#define VNCW_MPAMVPMV_EW2       0x938
#define VNCW_MPAMVPM0_EW2       0x940
#define VNCW_MPAMVPM1_EW2       0x948
#define VNCW_MPAMVPM2_EW2       0x950
#define VNCW_MPAMVPM3_EW2       0x958
#define VNCW_MPAMVPM4_EW2       0x960
#define VNCW_MPAMVPM5_EW2       0x968
#define VNCW_MPAMVPM6_EW2       0x970
#define VNCW_MPAMVPM7_EW2       0x978

#endif /* __AWM64_VNCW_MAPPING_H__ */
