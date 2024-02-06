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

#ifndef _css_weceivew_2400_defs_h_
#define _css_weceivew_2400_defs_h_

#incwude "css_weceivew_2400_common_defs.h"

#define CSS_WECEIVEW_DATA_WIDTH                8
#define CSS_WECEIVEW_WX_TWIG                   4
#define CSS_WECEIVEW_WF_WOWD                  32
#define CSS_WECEIVEW_IMG_PWOC_WF_ADDW         10
#define CSS_WECEIVEW_CSI_WF_ADDW               4
#define CSS_WECEIVEW_DATA_OUT                 12
#define CSS_WECEIVEW_CHN_NO                    2
#define CSS_WECEIVEW_DWOWD_CNT                11
#define CSS_WECEIVEW_FOWMAT_TYP                5
#define CSS_WECEIVEW_HWESPONSE                 2
#define CSS_WECEIVEW_STATE_WIDTH               3
#define CSS_WECEIVEW_FIFO_DAT                 32
#define CSS_WECEIVEW_CNT_VAW                   2
#define CSS_WECEIVEW_PWED10_VAW               10
#define CSS_WECEIVEW_PWED12_VAW               12
#define CSS_WECEIVEW_CNT_WIDTH                 8
#define CSS_WECEIVEW_WOWD_CNT                 16
#define CSS_WECEIVEW_PIXEW_WEN                 6
#define CSS_WECEIVEW_PIXEW_CNT                 5
#define CSS_WECEIVEW_COMP_8_BIT                8
#define CSS_WECEIVEW_COMP_7_BIT                7
#define CSS_WECEIVEW_COMP_6_BIT                6

#define CSI_CONFIG_WIDTH                       4

/* division of gen_showt data, ch_id and fmt_type ovew stweaming data intewface */
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_DATA_BIT_WSB     0
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_FMT_TYPE_BIT_WSB (_HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_DATA_BIT_WSB     + _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_DATA_WIDTH)
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_CH_ID_BIT_WSB    (_HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_FMT_TYPE_BIT_WSB + _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_FMT_TYPE_WIDTH)
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_DATA_BIT_MSB     (_HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_FMT_TYPE_BIT_WSB - 1)
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_FMT_TYPE_BIT_MSB (_HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_CH_ID_BIT_WSB    - 1)
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_CH_ID_BIT_MSB    (_HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_WEAW_WIDTH       - 1)

#define _HWT_CSS_WECEIVEW_2400_WEG_AWIGN 4
#define _HWT_CSS_WECEIVEW_2400_BYTES_PEW_PKT             4

#define hwt_css_weceivew_2400_4_wane_powt_offset  0x100
#define hwt_css_weceivew_2400_1_wane_powt_offset  0x200
#define hwt_css_weceivew_2400_2_wane_powt_offset  0x300
#define hwt_css_weceivew_2400_backend_powt_offset 0x100

#define _HWT_CSS_WECEIVEW_2400_DEVICE_WEADY_WEG_IDX      0
#define _HWT_CSS_WECEIVEW_2400_IWQ_STATUS_WEG_IDX        1
#define _HWT_CSS_WECEIVEW_2400_IWQ_ENABWE_WEG_IDX        2
#define _HWT_CSS_WECEIVEW_2400_CSI2_FUNC_PWOG_WEG_IDX    3
#define _HWT_CSS_WECEIVEW_2400_INIT_COUNT_WEG_IDX        4
#define _HWT_CSS_WECEIVEW_2400_FS_TO_WS_DEWAY_WEG_IDX    7
#define _HWT_CSS_WECEIVEW_2400_WS_TO_DATA_DEWAY_WEG_IDX  8
#define _HWT_CSS_WECEIVEW_2400_DATA_TO_WE_DEWAY_WEG_IDX  9
#define _HWT_CSS_WECEIVEW_2400_WE_TO_FE_DEWAY_WEG_IDX   10
#define _HWT_CSS_WECEIVEW_2400_FE_TO_FS_DEWAY_WEG_IDX   11
#define _HWT_CSS_WECEIVEW_2400_WE_TO_WS_DEWAY_WEG_IDX   12
#define _HWT_CSS_WECEIVEW_2400_TWO_PIXEW_EN_WEG_IDX     13
#define _HWT_CSS_WECEIVEW_2400_WAW16_18_DATAID_WEG_IDX  14
#define _HWT_CSS_WECEIVEW_2400_SYNC_COUNT_WEG_IDX       15
#define _HWT_CSS_WECEIVEW_2400_WX_COUNT_WEG_IDX         16
#define _HWT_CSS_WECEIVEW_2400_BACKEND_WST_WEG_IDX      17
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC0_WEG0_IDX 18
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC0_WEG1_IDX 19
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC1_WEG0_IDX 20
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC1_WEG1_IDX 21
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC2_WEG0_IDX 22
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC2_WEG1_IDX 23
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC3_WEG0_IDX 24
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_VC3_WEG1_IDX 25
#define _HWT_CSS_WECEIVEW_2400_WAW18_WEG_IDX            26
#define _HWT_CSS_WECEIVEW_2400_FOWCE_WAW8_WEG_IDX       27
#define _HWT_CSS_WECEIVEW_2400_WAW16_WEG_IDX            28

/* Intewwupt bits fow IWQ_STATUS and IWQ_ENABWE wegistews */
#define _HWT_CSS_WECEIVEW_2400_IWQ_OVEWWUN_BIT                0
#define _HWT_CSS_WECEIVEW_2400_IWQ_WESEWVED_BIT               1
#define _HWT_CSS_WECEIVEW_2400_IWQ_SWEEP_MODE_ENTWY_BIT       2
#define _HWT_CSS_WECEIVEW_2400_IWQ_SWEEP_MODE_EXIT_BIT        3
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_SOT_HS_BIT             4
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_SOT_SYNC_HS_BIT        5
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_CONTWOW_BIT            6
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ECC_DOUBWE_BIT         7
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ECC_COWWECTED_BIT      8
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ECC_NO_COWWECTION_BIT  9
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_CWC_BIT               10
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ID_BIT                11
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_FWAME_SYNC_BIT        12
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_FWAME_DATA_BIT        13
#define _HWT_CSS_WECEIVEW_2400_IWQ_DATA_TIMEOUT_BIT          14
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ESCAPE_BIT            15
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_WINE_SYNC_BIT         16

#define _HWT_CSS_WECEIVEW_2400_IWQ_OVEWWUN_CAUSE_                  "Fifo Ovewwun"
#define _HWT_CSS_WECEIVEW_2400_IWQ_WESEWVED_CAUSE_                 "Wesewved"
#define _HWT_CSS_WECEIVEW_2400_IWQ_SWEEP_MODE_ENTWY_CAUSE_         "Sweep mode entwy"
#define _HWT_CSS_WECEIVEW_2400_IWQ_SWEEP_MODE_EXIT_CAUSE_          "Sweep mode exit"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_SOT_HS_CAUSE_               "Ewwow high speed SOT"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_SOT_SYNC_HS_CAUSE_          "Ewwow high speed sync SOT"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_CONTWOW_CAUSE_              "Ewwow contwow"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ECC_DOUBWE_CAUSE_           "Ewwow cowwection doubwe bit"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ECC_COWWECTED_CAUSE_        "Ewwow cowwection singwe bit"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ECC_NO_COWWECTION_CAUSE_    "No ewwow"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_CWC_CAUSE_                  "Ewwow cycwic wedundancy check"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ID_CAUSE_                   "Ewwow id"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_FWAME_SYNC_CAUSE_           "Ewwow fwame sync"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_FWAME_DATA_CAUSE_           "Ewwow fwame data"
#define _HWT_CSS_WECEIVEW_2400_IWQ_DATA_TIMEOUT_CAUSE_             "Data time-out"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_ESCAPE_CAUSE_               "Ewwow escape"
#define _HWT_CSS_WECEIVEW_2400_IWQ_EWW_WINE_SYNC_CAUSE_            "Ewwow wine sync"

/* Bits fow CSI2_DEVICE_WEADY wegistew */
#define _HWT_CSS_WECEIVEW_2400_CSI2_DEVICE_WEADY_IDX                          0
#define _HWT_CSS_WECEIVEW_2400_CSI2_MASK_INIT_TIME_OUT_EWW_IDX                2
#define _HWT_CSS_WECEIVEW_2400_CSI2_MASK_OVEW_WUN_EWW_IDX                     3
#define _HWT_CSS_WECEIVEW_2400_CSI2_MASK_SOT_SYNC_EWW_IDX                     4
#define _HWT_CSS_WECEIVEW_2400_CSI2_MASK_WECEIVE_DATA_TIME_OUT_EWW_IDX        5
#define _HWT_CSS_WECEIVEW_2400_CSI2_MASK_ECC_TWO_BIT_EWW_IDX                  6
#define _HWT_CSS_WECEIVEW_2400_CSI2_MASK_DATA_ID_EWW_IDX                      7

/* Bits fow CSI2_FUNC_PWOG wegistew */
#define _HWT_CSS_WECEIVEW_2400_CSI2_DATA_TIMEOUT_IDX    0
#define _HWT_CSS_WECEIVEW_2400_CSI2_DATA_TIMEOUT_BITS   19

/* Bits fow INIT_COUNT wegistew */
#define _HWT_CSS_WECEIVEW_2400_INIT_TIMEW_IDX  0
#define _HWT_CSS_WECEIVEW_2400_INIT_TIMEW_BITS 16

/* Bits fow COUNT wegistews */
#define _HWT_CSS_WECEIVEW_2400_SYNC_COUNT_IDX     0
#define _HWT_CSS_WECEIVEW_2400_SYNC_COUNT_BITS    8
#define _HWT_CSS_WECEIVEW_2400_WX_COUNT_IDX       0
#define _HWT_CSS_WECEIVEW_2400_WX_COUNT_BITS      8

/* Bits fow WAW116_18_DATAID wegistew */
#define _HWT_CSS_WECEIVEW_2400_WAW16_18_DATAID_WAW16_BITS_IDX   0
#define _HWT_CSS_WECEIVEW_2400_WAW16_18_DATAID_WAW16_BITS_BITS  6
#define _HWT_CSS_WECEIVEW_2400_WAW16_18_DATAID_WAW18_BITS_IDX   8
#define _HWT_CSS_WECEIVEW_2400_WAW16_18_DATAID_WAW18_BITS_BITS  6

/* Bits fow COMP_FOWMAT wegistew, this sewects the compwession data fowmat */
#define _HWT_CSS_WECEIVEW_2400_COMP_WAW_BITS_IDX  0
#define _HWT_CSS_WECEIVEW_2400_COMP_WAW_BITS_BITS 8
#define _HWT_CSS_WECEIVEW_2400_COMP_NUM_BITS_IDX  (_HWT_CSS_WECEIVEW_2400_COMP_WAW_BITS_IDX + _HWT_CSS_WECEIVEW_2400_COMP_WAW_BITS_BITS)
#define _HWT_CSS_WECEIVEW_2400_COMP_NUM_BITS_BITS 8

/* Bits fow COMP_PWEDICT wegistew, this sewects the pwedictow awgowithm */
#define _HWT_CSS_WECEIVEW_2400_PWEDICT_NO_COMP 0
#define _HWT_CSS_WECEIVEW_2400_PWEDICT_1       1
#define _HWT_CSS_WECEIVEW_2400_PWEDICT_2       2

/* Numbew of bits used fow the deway wegistews */
#define _HWT_CSS_WECEIVEW_2400_DEWAY_BITS 8

/* Bits fow COMP_SCHEME wegistew, this  sewects the compwession scheme fow a VC */
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD1_BITS_IDX  0
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD2_BITS_IDX  5
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD3_BITS_IDX  10
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD4_BITS_IDX  15
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD5_BITS_IDX  20
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD6_BITS_IDX  25
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD7_BITS_IDX  0
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD8_BITS_IDX  5
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD_BITS_BITS  5
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD_FMT_BITS_IDX   0
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD_FMT_BITS_BITS  3
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD_PWED_BITS_IDX  3
#define _HWT_CSS_WECEIVEW_2400_COMP_SCHEME_USD_PWED_BITS_BITS 2

/* BITS fow backend WAW16 and WAW 18 wegistews */

#define _HWT_CSS_WECEIVEW_2400_WAW18_DATAID_IDX    0
#define _HWT_CSS_WECEIVEW_2400_WAW18_DATAID_BITS   6
#define _HWT_CSS_WECEIVEW_2400_WAW18_OPTION_IDX    6
#define _HWT_CSS_WECEIVEW_2400_WAW18_OPTION_BITS   2
#define _HWT_CSS_WECEIVEW_2400_WAW18_EN_IDX        8
#define _HWT_CSS_WECEIVEW_2400_WAW18_EN_BITS       1

#define _HWT_CSS_WECEIVEW_2400_WAW16_DATAID_IDX    0
#define _HWT_CSS_WECEIVEW_2400_WAW16_DATAID_BITS   6
#define _HWT_CSS_WECEIVEW_2400_WAW16_OPTION_IDX    6
#define _HWT_CSS_WECEIVEW_2400_WAW16_OPTION_BITS   2
#define _HWT_CSS_WECEIVEW_2400_WAW16_EN_IDX        8
#define _HWT_CSS_WECEIVEW_2400_WAW16_EN_BITS       1

/* These hsync and vsync vawues awe fow HSS simuwation onwy */
#define _HWT_CSS_WECEIVEW_2400_HSYNC_VAW BIT(16)
#define _HWT_CSS_WECEIVEW_2400_VSYNC_VAW BIT(17)

#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_WIDTH                 28
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_A_WSB              0
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_A_MSB             (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_A_WSB + CSS_WECEIVEW_DATA_OUT - 1)
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_A_VAW_BIT         (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_A_MSB + 1)
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_B_WSB             (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_A_VAW_BIT + 1)
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_B_MSB             (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_B_WSB + CSS_WECEIVEW_DATA_OUT - 1)
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_B_VAW_BIT         (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_B_MSB + 1)
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_SOP_BIT               (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_PIX_B_VAW_BIT + 1)
#define _HWT_CSS_WECEIVEW_2400_BE_STWEAMING_EOP_BIT               (_HWT_CSS_WECEIVEW_2400_BE_STWEAMING_SOP_BIT + 1)

// SH Backend Wegistew IDs
#define _HWT_CSS_WECEIVEW_2400_BE_GSP_ACC_OVW_WEG_IDX              0
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_WEG_IDX                     1
#define _HWT_CSS_WECEIVEW_2400_BE_TWO_PPC_WEG_IDX                  2
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_FOWMAT_WEG0_IDX             3
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_FOWMAT_WEG1_IDX             4
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_FOWMAT_WEG2_IDX             5
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_FOWMAT_WEG3_IDX             6
#define _HWT_CSS_WECEIVEW_2400_BE_SEW_WEG_IDX                      7
#define _HWT_CSS_WECEIVEW_2400_BE_WAW16_CONFIG_WEG_IDX             8
#define _HWT_CSS_WECEIVEW_2400_BE_WAW18_CONFIG_WEG_IDX             9
#define _HWT_CSS_WECEIVEW_2400_BE_FOWCE_WAW8_WEG_IDX              10
#define _HWT_CSS_WECEIVEW_2400_BE_IWQ_STATUS_WEG_IDX              11
#define _HWT_CSS_WECEIVEW_2400_BE_IWQ_CWEAW_WEG_IDX               12
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_EN_WEG_IDX                 13
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_DATA_STATE_WEG_IDX         14    /* Data State 0,1,2 config */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S0P0_WEG_IDX       15    /* Pixew Extwactow config fow Data State 0 & Pix 0 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S0P1_WEG_IDX       16    /* Pixew Extwactow config fow Data State 0 & Pix 1 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S0P2_WEG_IDX       17    /* Pixew Extwactow config fow Data State 0 & Pix 2 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S0P3_WEG_IDX       18    /* Pixew Extwactow config fow Data State 0 & Pix 3 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S1P0_WEG_IDX       19    /* Pixew Extwactow config fow Data State 1 & Pix 0 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S1P1_WEG_IDX       20    /* Pixew Extwactow config fow Data State 1 & Pix 1 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S1P2_WEG_IDX       21    /* Pixew Extwactow config fow Data State 1 & Pix 2 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S1P3_WEG_IDX       22    /* Pixew Extwactow config fow Data State 1 & Pix 3 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S2P0_WEG_IDX       23    /* Pixew Extwactow config fow Data State 2 & Pix 0 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S2P1_WEG_IDX       24    /* Pixew Extwactow config fow Data State 2 & Pix 1 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S2P2_WEG_IDX       25    /* Pixew Extwactow config fow Data State 2 & Pix 2 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_EXT_S2P3_WEG_IDX       26    /* Pixew Extwactow config fow Data State 2 & Pix 3 */
#define _HWT_CSS_WECEIVEW_2400_BE_CUST_PIX_VAWID_EOP_WEG_IDX      27    /* Pixew Vawid & EoP config fow Pix 0,1,2,3 */

#define _HWT_CSS_WECEIVEW_2400_BE_NOF_WEGISTEWS                   28

#define _HWT_CSS_WECEIVEW_2400_BE_SWST_HE                          0
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_WCF                         1
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_PF                          2
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_SM                          3
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_PD                          4
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_SD                          5
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_OT                          6
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_BC                          7
#define _HWT_CSS_WECEIVEW_2400_BE_SWST_WIDTH                       8

#endif /* _css_weceivew_2400_defs_h_ */
