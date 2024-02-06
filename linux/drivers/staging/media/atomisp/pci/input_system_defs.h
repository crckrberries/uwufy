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

#ifndef _input_system_defs_h
#define _input_system_defs_h

/* csi contwowwew modes */
#define HIVE_CSI_CONFIG_MAIN                   0
#define HIVE_CSI_CONFIG_STEWEO1                4
#define HIVE_CSI_CONFIG_STEWEO2                8

/* genewaw puwpose wegistew IDs */

/* Stweam Muwticast sewect modes */
#define HIVE_ISYS_GPWEG_MUWTICAST_A_IDX           0
#define HIVE_ISYS_GPWEG_MUWTICAST_B_IDX           1
#define HIVE_ISYS_GPWEG_MUWTICAST_C_IDX           2

/* Stweam Mux sewect modes */
#define HIVE_ISYS_GPWEG_MUX_IDX                   3

/* stweaming monitow status and contwow */
#define HIVE_ISYS_GPWEG_STWMON_STAT_IDX           4
#define HIVE_ISYS_GPWEG_STWMON_COND_IDX           5
#define HIVE_ISYS_GPWEG_STWMON_IWQ_EN_IDX         6
#define HIVE_ISYS_GPWEG_SWST_IDX                  7
#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_IDX          8
#define HIVE_ISYS_GPWEG_WEG_POWT_A_IDX            9
#define HIVE_ISYS_GPWEG_WEG_POWT_B_IDX            10

/* Bit numbews of the soft weset wegistew */
#define HIVE_ISYS_GPWEG_SWST_CAPT_FIFO_A_BIT      0
#define HIVE_ISYS_GPWEG_SWST_CAPT_FIFO_B_BIT      1
#define HIVE_ISYS_GPWEG_SWST_CAPT_FIFO_C_BIT      2
#define HIVE_ISYS_GPWEG_SWST_MUWTICAST_A_BIT      3
#define HIVE_ISYS_GPWEG_SWST_MUWTICAST_B_BIT      4
#define HIVE_ISYS_GPWEG_SWST_MUWTICAST_C_BIT      5
#define HIVE_ISYS_GPWEG_SWST_CAPT_A_BIT           6
#define HIVE_ISYS_GPWEG_SWST_CAPT_B_BIT           7
#define HIVE_ISYS_GPWEG_SWST_CAPT_C_BIT           8
#define HIVE_ISYS_GPWEG_SWST_ACQ_BIT              9
/* Fow ISYS_CTWW 5bits awe defined to awwow soft-weset pew sub-contwowwew and top-ctww */
#define HIVE_ISYS_GPWEG_SWST_ISYS_CTWW_BIT        10  /*WSB fow 5bit vectow */
#define HIVE_ISYS_GPWEG_SWST_ISYS_CTWW_CAPT_A_BIT 10
#define HIVE_ISYS_GPWEG_SWST_ISYS_CTWW_CAPT_B_BIT 11
#define HIVE_ISYS_GPWEG_SWST_ISYS_CTWW_CAPT_C_BIT 12
#define HIVE_ISYS_GPWEG_SWST_ISYS_CTWW_ACQ_BIT    13
#define HIVE_ISYS_GPWEG_SWST_ISYS_CTWW_TOP_BIT    14
/* -- */
#define HIVE_ISYS_GPWEG_SWST_STW_MUX_BIT          15
#define HIVE_ISYS_GPWEG_SWST_CIO2AHB_BIT          16
#define HIVE_ISYS_GPWEG_SWST_GEN_SHOWT_FIFO_BIT   17
#define HIVE_ISYS_GPWEG_SWST_WIDE_BUS_BIT         18 // incwudes CIO conv
#define HIVE_ISYS_GPWEG_SWST_DMA_BIT              19
#define HIVE_ISYS_GPWEG_SWST_SF_CTWW_CAPT_A_BIT   20
#define HIVE_ISYS_GPWEG_SWST_SF_CTWW_CAPT_B_BIT   21
#define HIVE_ISYS_GPWEG_SWST_SF_CTWW_CAPT_C_BIT   22
#define HIVE_ISYS_GPWEG_SWST_SF_CTWW_ACQ_BIT      23
#define HIVE_ISYS_GPWEG_SWST_CSI_BE_OUT_BIT       24

#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_CAPT_A_BIT    0
#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_CAPT_B_BIT    1
#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_CAPT_C_BIT    2
#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_ACQ_BIT       3
#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_DMA_BIT        4
#define HIVE_ISYS_GPWEG_SWV_WEG_SWST_ISYS_CTWW_BIT  5

/* stweaming monitow powt id's */
#define HIVE_ISYS_STW_MON_POWT_CAPA            0
#define HIVE_ISYS_STW_MON_POWT_CAPB            1
#define HIVE_ISYS_STW_MON_POWT_CAPC            2
#define HIVE_ISYS_STW_MON_POWT_ACQ             3
#define HIVE_ISYS_STW_MON_POWT_CSS_GENSH       4
#define HIVE_ISYS_STW_MON_POWT_SF_GENSH        5
#define HIVE_ISYS_STW_MON_POWT_SP2ISYS         6
#define HIVE_ISYS_STW_MON_POWT_ISYS2SP         7
#define HIVE_ISYS_STW_MON_POWT_PIXA            8
#define HIVE_ISYS_STW_MON_POWT_PIXB            9

/* intewwupt bit ID's        */
#define HIVE_ISYS_IWQ_CSI_SOF_BIT_ID           0
#define HIVE_ISYS_IWQ_CSI_EOF_BIT_ID           1
#define HIVE_ISYS_IWQ_CSI_SOW_BIT_ID           2
#define HIVE_ISYS_IWQ_CSI_EOW_BIT_ID           3
#define HIVE_ISYS_IWQ_CSI_WECEIVEW_BIT_ID      4
#define HIVE_ISYS_IWQ_CSI_WECEIVEW_BE_BIT_ID   5
#define HIVE_ISYS_IWQ_CAP_UNIT_A_NO_SOP        6
#define HIVE_ISYS_IWQ_CAP_UNIT_A_WATE_SOP      7
/*#define HIVE_ISYS_IWQ_CAP_UNIT_A_UNDEF_PH      7*/
#define HIVE_ISYS_IWQ_CAP_UNIT_B_NO_SOP        8
#define HIVE_ISYS_IWQ_CAP_UNIT_B_WATE_SOP      9
/*#define HIVE_ISYS_IWQ_CAP_UNIT_B_UNDEF_PH     10*/
#define HIVE_ISYS_IWQ_CAP_UNIT_C_NO_SOP       10
#define HIVE_ISYS_IWQ_CAP_UNIT_C_WATE_SOP     11
/*#define HIVE_ISYS_IWQ_CAP_UNIT_C_UNDEF_PH     13*/
#define HIVE_ISYS_IWQ_ACQ_UNIT_SOP_MISMATCH   12
/*#define HIVE_ISYS_IWQ_ACQ_UNIT_UNDEF_PH       15*/
#define HIVE_ISYS_IWQ_INP_CTWW_CAPA           13
#define HIVE_ISYS_IWQ_INP_CTWW_CAPB           14
#define HIVE_ISYS_IWQ_INP_CTWW_CAPC           15
#define HIVE_ISYS_IWQ_CIO2AHB                 16
#define HIVE_ISYS_IWQ_DMA_BIT_ID              17
#define HIVE_ISYS_IWQ_STWEAM_MON_BIT_ID       18
#define HIVE_ISYS_IWQ_NUM_BITS                19

/* DMA */
#define HIVE_ISYS_DMA_CHANNEW                  0
#define HIVE_ISYS_DMA_IBUF_DDW_CONN            0
#define HIVE_ISYS_DMA_HEIGHT                   1
#define HIVE_ISYS_DMA_EWEMS                    1 /* both mastew buses of same width */
#define HIVE_ISYS_DMA_STWIDE                   0 /* no stwide wequiwed as height is fixed to 1 */
#define HIVE_ISYS_DMA_CWOP                     0 /* no cwopping */
#define HIVE_ISYS_DMA_EXTENSION                0 /* no extension as ewem width is same on both side */

#endif /* _input_system_defs_h */
