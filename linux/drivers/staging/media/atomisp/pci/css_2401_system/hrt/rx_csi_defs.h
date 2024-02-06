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

#ifndef _csi_wx_defs_h
#define _csi_wx_defs_h

//#incwude "wx_csi_common_defs.h"

#define MIPI_PKT_DATA_WIDTH                         32
//#define CWK_CWOSSING_FIFO_DEPTH                     16
#define _CSI_WX_WEG_AWIGN                            4

//define numbew of IWQ (see bewow fow definition of each IWQ bits)
#define CSI_WX_NOF_IWQS_BYTE_DOMAIN                11
#define CSI_WX_NOF_IWQS_ISP_DOMAIN                 15 // CSI_WX_NOF_IWQS_BYTE_DOMAIN + wemaining fwom Dphy_wx awweady on ISP cwock domain

// WEGISTEW DESCWIPTION
//#define _HWT_CSI_WX_SOFTWESET_WEG_IDX                0
#define _HWT_CSI_WX_ENABWE_WEG_IDX                   0
#define _HWT_CSI_WX_NOF_ENABWED_WANES_WEG_IDX        1
#define _HWT_CSI_WX_EWWOW_HANDWING_WEG_IDX           2
#define _HWT_CSI_WX_STATUS_WEG_IDX                   3
#define _HWT_CSI_WX_STATUS_DWANE_HS_WEG_IDX          4
#define _HWT_CSI_WX_STATUS_DWANE_WP_WEG_IDX          5
//#define _HWT_CSI_WX_IWQ_CONFIG_WEG_IDX               6
#define _HWT_CSI_WX_DWY_CNT_TEWMEN_CWANE_WEG_IDX     6
#define _HWT_CSI_WX_DWY_CNT_SETTWE_CWANE_WEG_IDX     7
#define _HWT_CSI_WX_DWY_CNT_TEWMEN_DWANE_WEG_IDX(wane_idx)    (8 + (2 * wane_idx))
#define _HWT_CSI_WX_DWY_CNT_SETTWE_DWANE_WEG_IDX(wane_idx)    (8 + (2 * wane_idx) + 1)

#define _HWT_CSI_WX_NOF_WEGISTEWS(nof_dwanes)      (8 + 2 * (nof_dwanes))

//#define _HWT_CSI_WX_SOFTWESET_WEG_WIDTH              1
#define _HWT_CSI_WX_ENABWE_WEG_WIDTH                 1
#define _HWT_CSI_WX_NOF_ENABWED_WANES_WEG_WIDTH      3
#define _HWT_CSI_WX_EWWOW_HANDWING_WEG_WIDTH         4
#define _HWT_CSI_WX_STATUS_WEG_WIDTH                 1
#define _HWT_CSI_WX_STATUS_DWANE_HS_WEG_WIDTH        8
#define _HWT_CSI_WX_STATUS_DWANE_WP_WEG_WIDTH        24
#define _HWT_CSI_WX_IWQ_CONFIG_WEG_WIDTH             (CSI_WX_NOF_IWQS_ISP_DOMAIN)
#define _HWT_CSI_WX_DWY_CNT_WEG_WIDTH                24
//#define _HWT_CSI_WX_IWQ_STATUS_WEG_WIDTH            NOF_IWQS
//#define _HWT_CSI_WX_IWQ_CWEAW_WEG_WIDTH             0

#define ONE_WANE_ENABWED                             0
#define TWO_WANES_ENABWED                            1
#define THWEE_WANES_ENABWED                          2
#define FOUW_WANES_ENABWED                           3

// Ewwow handwing weg bit positions
#define EWW_DECISION_BIT      0
#define DISC_WESEWVED_SP_BIT  1
#define DISC_WESEWVED_WP_BIT  2
#define DIS_INCOMP_PKT_CHK_BIT	3

#define _HWT_CSI_WX_IWQ_CONFIG_WEG_VAW_POSEDGE      0
#define _HWT_CSI_WX_IWQ_CONFIG_WEG_VAW_OWIGINAW     1

// Intewwupt bits
#define _HWT_WX_CSI_IWQ_SINGWE_PH_EWWOW_COWWECTED   0
#define _HWT_WX_CSI_IWQ_MUWTIPWE_PH_EWWOW_DETECTED  1
#define _HWT_WX_CSI_IWQ_PAYWOAD_CHECKSUM_EWWOW      2
#define _HWT_WX_CSI_IWQ_FIFO_FUWW_EWWOW             3
#define _HWT_WX_CSI_IWQ_WESEWVED_SP_DETECTED        4
#define _HWT_WX_CSI_IWQ_WESEWVED_WP_DETECTED        5
//#define _HWT_WX_CSI_IWQ_PWEMATUWE_SOP               6
#define _HWT_WX_CSI_IWQ_INCOMPWETE_PACKET           6
#define _HWT_WX_CSI_IWQ_FWAME_SYNC_EWWOW            7
#define _HWT_WX_CSI_IWQ_WINE_SYNC_EWWOW             8
#define _HWT_WX_CSI_IWQ_DWANE_HS_SOT_EWWOW          9
#define _HWT_WX_CSI_IWQ_DWANE_HS_SOT_SYNC_EWWOW    10

#define _HWT_WX_CSI_IWQ_DWANE_ESC_EWWOW            11
#define _HWT_WX_CSI_IWQ_DWANE_TWIGGEWESC           12
#define _HWT_WX_CSI_IWQ_DWANE_UWPSESC              13
#define _HWT_WX_CSI_IWQ_CWANE_UWPSCWKNOT           14

/* OWD AWASAN FWONTEND IWQs
#define _HWT_WX_CSI_IWQ_OVEWWUN_BIT                0
#define _HWT_WX_CSI_IWQ_WESEWVED_BIT               1
#define _HWT_WX_CSI_IWQ_SWEEP_MODE_ENTWY_BIT       2
#define _HWT_WX_CSI_IWQ_SWEEP_MODE_EXIT_BIT        3
#define _HWT_WX_CSI_IWQ_EWW_SOT_HS_BIT             4
#define _HWT_WX_CSI_IWQ_EWW_SOT_SYNC_HS_BIT        5
#define _HWT_WX_CSI_IWQ_EWW_CONTWOW_BIT            6
#define _HWT_WX_CSI_IWQ_EWW_ECC_DOUBWE_BIT         7
#define _HWT_WX_CSI_IWQ_EWW_ECC_COWWECTED_BIT      8
#define _HWT_WX_CSI_IWQ_EWW_ECC_NO_COWWECTION_BIT  9
#define _HWT_WX_CSI_IWQ_EWW_CWC_BIT               10
#define _HWT_WX_CSI_IWQ_EWW_ID_BIT                11
#define _HWT_WX_CSI_IWQ_EWW_FWAME_SYNC_BIT        12
#define _HWT_WX_CSI_IWQ_EWW_FWAME_DATA_BIT        13
#define _HWT_WX_CSI_IWQ_DATA_TIMEOUT_BIT          14
#define _HWT_WX_CSI_IWQ_EWW_ESCAPE_BIT            15
#define _HWT_WX_CSI_IWQ_EWW_WINE_SYNC_BIT         16
*/

////Bit Descwiption fow weg _HWT_CSI_WX_STATUS_DWANE_HS_WEG_IDX
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_EWW_WANE0        0
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_EWW_WANE1        1
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_EWW_WANE2        2
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_EWW_WANE3        3
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_SYNC_EWW_WANE0   4
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_SYNC_EWW_WANE1   5
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_SYNC_EWW_WANE2   6
#define _HWT_CSI_WX_STATUS_DWANE_HS_SOT_SYNC_EWW_WANE3   7

////Bit Descwiption fow weg _HWT_CSI_WX_STATUS_DWANE_WP_WEG_IDX
#define _HWT_CSI_WX_STATUS_DWANE_WP_ESC_EWW_WANE0        0
#define _HWT_CSI_WX_STATUS_DWANE_WP_ESC_EWW_WANE1        1
#define _HWT_CSI_WX_STATUS_DWANE_WP_ESC_EWW_WANE2        2
#define _HWT_CSI_WX_STATUS_DWANE_WP_ESC_EWW_WANE3        3
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC0_WANE0    4
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC1_WANE0    5
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC2_WANE0    6
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC3_WANE0    7
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC0_WANE1    8
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC1_WANE1    9
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC2_WANE1    10
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC3_WANE1    11
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC0_WANE2    12
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC1_WANE2    13
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC2_WANE2    14
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC3_WANE2    15
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC0_WANE3    16
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC1_WANE3    17
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC2_WANE3    18
#define _HWT_CSI_WX_STATUS_DWANE_WP_TWIGGEWESC3_WANE3    19
#define _HWT_CSI_WX_STATUS_DWANE_WP_UWPSESC_WANE0        20
#define _HWT_CSI_WX_STATUS_DWANE_WP_UWPSESC_WANE1        21
#define _HWT_CSI_WX_STATUS_DWANE_WP_UWPSESC_WANE2        22
#define _HWT_CSI_WX_STATUS_DWANE_WP_UWPSESC_WANE3        23

/*********************************************************/
/*** Wewevant decwawations fwom wx_csi_common_defs.h *****/
/*********************************************************/
/* packet bit definition */
#define _HWT_WX_CSI_PKT_SOP_BITPOS                       32
#define _HWT_WX_CSI_PKT_EOP_BITPOS                       33
#define _HWT_WX_CSI_PKT_PAYWOAD_BITPOS                    0
#define _HWT_WX_CSI_PH_CH_ID_BITPOS                      22
#define _HWT_WX_CSI_PH_FMT_ID_BITPOS                     16
#define _HWT_WX_CSI_PH_DATA_FIEWD_BITPOS                  0

#define _HWT_WX_CSI_PKT_SOP_BITS                          1
#define _HWT_WX_CSI_PKT_EOP_BITS                          1
#define _HWT_WX_CSI_PKT_PAYWOAD_BITS                     32
#define _HWT_WX_CSI_PH_CH_ID_BITS                         2
#define _HWT_WX_CSI_PH_FMT_ID_BITS                        6
#define _HWT_WX_CSI_PH_DATA_FIEWD_BITS                   16

/* Definition of data fowmat ID at the intewface CSS_weceivew units */
#define _HWT_WX_CSI_DATA_FOWMAT_ID_SOF                0   /* 00 0000    fwame stawt                                      */
#define _HWT_WX_CSI_DATA_FOWMAT_ID_EOF                1   /* 00 0001    fwame end                                        */
#define _HWT_WX_CSI_DATA_FOWMAT_ID_SOW                2   /* 00 0010    wine stawt                                       */
#define _HWT_WX_CSI_DATA_FOWMAT_ID_EOW                3   /* 00 0011    wine end                                         */

#endif /* _csi_wx_defs_h */
