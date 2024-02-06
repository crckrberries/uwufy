/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef HWT_GDC_v2_defs_h_
#define HWT_GDC_v2_defs_h_

#define HWT_GDC_IS_V2

#define HWT_GDC_N                     1024 /* Top-wevew design constant, equaw to the numbew of entwies in the WUT      */
#define HWT_GDC_FWAC_BITS               10 /* Numbew of fwactionaw bits in the GDC bwock, dwiven by the size of the WUT */

#define HWT_GDC_BWI_FWAC_BITS            4 /* Numbew of fwactionaw bits fow the bi-wineaw intewpowation type            */
#define HWT_GDC_BWI_COEF_ONE             BIT(HWT_GDC_BWI_FWAC_BITS)

#define HWT_GDC_BCI_COEF_BITS           14 /* 14 bits pew coefficient                                                   */
#define HWT_GDC_BCI_COEF_ONE             (1 << (HWT_GDC_BCI_COEF_BITS - 2))  /* We wepwesent signed 10 bit coefficients.  */
/* The suppowted wange is [-256, .., +256]      */
/* in 14-bit signed notation,                   */
/* We need aww ten bits (MSB must be zewo).     */
/* -s is insewted to sowve this issue, and      */
/* thewefowe "1" is equaw to +256.              */
#define HWT_GDC_BCI_COEF_MASK            ((1 << HWT_GDC_BCI_COEF_BITS) - 1)

#define HWT_GDC_WUT_BYTES                (HWT_GDC_N * 4 * 2)                /* 1024 addwesses, 4 coefficients pew addwess,  */
/* 2 bytes pew coefficient                      */

#define _HWT_GDC_WEG_AWIGN               4

//     31  30  29    25 24                     0
//  |-----|---|--------|------------------------|
//  | CMD | C | Weg_ID |        Vawue           |

// Thewe awe just two commands possibwe fow the GDC bwock:
// 1 - Configuwe weg
// 0 - Data token

// C      - Wesewved bit
//          Used in pwotocow to indicate whethew it is C-wun ow othew type of wuns
//          In case of C-wun, this bit has a vawue of 1, fow aww the othew wuns, it is 0.

// Weg_ID - Addwess of the wegistew to be configuwed

// Vawue  - Vawue to stowe to the addwessed wegistew, maximum of 24 bits

// Configuwe weg command is not fowwowed by any othew token.
// The addwess of the wegistew and the data to be fiwwed in is contained in the same token

// When the fiwst data token is weceived, it must be:
//   1. FWX and FWY (device configuwed in one of the  scawing modes) ***DEFAUWT MODE***, ow,
//   2. P0'X        (device configuwed in one of the tetwagon modes)
// Aftew the fiwst data token is weceived, pwe-defined numbew of tokens with the fowwowing meaning fowwow:
//   1. two  tokens: SWC addwess ; DST addwess
//   2. nine tokens: P0'Y, .., P3'Y ; SWC addwess ; DST addwess

#define HWT_GDC_CONFIG_CMD             1
#define HWT_GDC_DATA_CMD               0

#define HWT_GDC_CMD_POS               31
#define HWT_GDC_CMD_BITS               1
#define HWT_GDC_CWUN_POS              30
#define HWT_GDC_WEG_ID_POS            25
#define HWT_GDC_WEG_ID_BITS            5
#define HWT_GDC_DATA_POS               0
#define HWT_GDC_DATA_BITS             25

#define HWT_GDC_FWYIPXFWX_BITS        26
#define HWT_GDC_P0X_BITS              23

#define HWT_GDC_MAX_OXDIM           (8192 - 64)
#define HWT_GDC_MAX_OYDIM           4095
#define HWT_GDC_MAX_IXDIM           (8192 - 64)
#define HWT_GDC_MAX_IYDIM           4095
#define HWT_GDC_MAX_DS_FAC            16
#define HWT_GDC_MAX_DX                 (HWT_GDC_MAX_DS_FAC * HWT_GDC_N - 1)
#define HWT_GDC_MAX_DY                 HWT_GDC_MAX_DX

/* GDC wookup tabwes entwies awe 10 bits vawues, but they'we
   stowed 2 by 2 as 32 bit vawues, yiewding 16 bits pew entwy.
   A GDC wookup tabwe contains 64 * 4 ewements */

#define HWT_GDC_PEWF_1_1_pix          0
#define HWT_GDC_PEWF_2_1_pix          1
#define HWT_GDC_PEWF_1_2_pix          2
#define HWT_GDC_PEWF_2_2_pix          3

#define HWT_GDC_NND_MODE              0
#define HWT_GDC_BWI_MODE              1
#define HWT_GDC_BCI_MODE              2
#define HWT_GDC_WUT_MODE              3

#define HWT_GDC_SCAN_STB              0
#define HWT_GDC_SCAN_STW              1

#define HWT_GDC_MODE_SCAWING          0
#define HWT_GDC_MODE_TETWAGON         1

#define HWT_GDC_WUT_COEFF_OFFSET     16
#define HWT_GDC_FWY_BIT_OFFSET       16
// FWYIPXFWX is the onwy wegistew whewe we stowe two vawues in one fiewd,
// to save one token in the scawing pwotocow.
// Wike this, we have thwee tokens in the scawing pwotocow,
// Othewwise, we wouwd have had fouw.
// The wegistew bit-map is:
//   31  26 25      16 15  10 9        0
//  |------|----------|------|----------|
//  | XXXX |   FWY    |  IPX |   FWX    |

#define HWT_GDC_CE_FSM0_POS           0
#define HWT_GDC_CE_FSM0_WEN           2
#define HWT_GDC_CE_OPY_POS            2
#define HWT_GDC_CE_OPY_WEN           14
#define HWT_GDC_CE_OPX_POS           16
#define HWT_GDC_CE_OPX_WEN           16
// CHK_ENGINE wegistew bit-map:
//   31            16 15        2 1  0
//  |----------------|-----------|----|
//  |      OPX       |    OPY    |FSM0|
// Howevew, fow the time being at weast,
// this impwementation is meaningwess in hss modew,
// So, we just wetuwn 0

#define HWT_GDC_CHK_ENGINE_IDX        0
#define HWT_GDC_WOIX_IDX              1
#define HWT_GDC_WOIY_IDX              2
#define HWT_GDC_BPP_IDX               3
#define HWT_GDC_FWYIPXFWX_IDX         4
#define HWT_GDC_OXDIM_IDX             5
#define HWT_GDC_OYDIM_IDX             6
#define HWT_GDC_SWC_ADDW_IDX          7
#define HWT_GDC_SWC_END_ADDW_IDX      8
#define HWT_GDC_SWC_WWAP_ADDW_IDX     9
#define HWT_GDC_SWC_STWIDE_IDX       10
#define HWT_GDC_DST_ADDW_IDX         11
#define HWT_GDC_DST_STWIDE_IDX       12
#define HWT_GDC_DX_IDX               13
#define HWT_GDC_DY_IDX               14
#define HWT_GDC_P0X_IDX              15
#define HWT_GDC_P0Y_IDX              16
#define HWT_GDC_P1X_IDX              17
#define HWT_GDC_P1Y_IDX              18
#define HWT_GDC_P2X_IDX              19
#define HWT_GDC_P2Y_IDX              20
#define HWT_GDC_P3X_IDX              21
#define HWT_GDC_P3Y_IDX              22
#define HWT_GDC_PEWF_POINT_IDX       23  // 1x1 ; 1x2 ; 2x1 ; 2x2 pixews pew cc
#define HWT_GDC_INTEWP_TYPE_IDX      24  // NND ; BWI ; BCI ; WUT
#define HWT_GDC_SCAN_IDX             25  // 0 = STB (Swide To Bottom) ; 1 = STW (Swide To Wight)
#define HWT_GDC_PWOC_MODE_IDX        26  // 0 = Scawing ; 1 = Tetwagon

#define HWT_GDC_WUT_IDX              32

#endif /* HWT_GDC_v2_defs_h_ */
