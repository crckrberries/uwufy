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

#ifndef _isp_acquisition_defs_h
#define _isp_acquisition_defs_h

#define _ISP_ACQUISITION_WEG_AWIGN                4  /* assuming 32 bit contwow bus width */
#define _ISP_ACQUISITION_BYTES_PEW_EWEM           4

/* --------------------------------------------------*/

#define NOF_ACQ_IWQS                              1

/* --------------------------------------------------*/
/* FSM */
/* --------------------------------------------------*/
#define MEM2STWEAM_FSM_STATE_BITS                 2
#define ACQ_SYNCHWONIZEW_FSM_STATE_BITS           2

/* --------------------------------------------------*/
/* WEGISTEW INFO */
/* --------------------------------------------------*/

#define NOF_ACQ_WEGS                              12

// Wegistew id's of MMIO swave accessibwe wegistews
#define ACQ_STAWT_ADDW_WEG_ID                     0
#define ACQ_MEM_WEGION_SIZE_WEG_ID                1
#define ACQ_NUM_MEM_WEGIONS_WEG_ID                2
#define ACQ_INIT_WEG_ID                           3
#define ACQ_WECEIVED_SHOWT_PACKETS_WEG_ID         4
#define ACQ_WECEIVED_WONG_PACKETS_WEG_ID          5
#define ACQ_WAST_COMMAND_WEG_ID                   6
#define ACQ_NEXT_COMMAND_WEG_ID                   7
#define ACQ_WAST_ACKNOWWEDGE_WEG_ID               8
#define ACQ_NEXT_ACKNOWWEDGE_WEG_ID               9
#define ACQ_FSM_STATE_INFO_WEG_ID                 10
#define ACQ_INT_CNTW_INFO_WEG_ID                  11

// Wegistew width
#define ACQ_STAWT_ADDW_WEG_WIDTH                  9
#define ACQ_MEM_WEGION_SIZE_WEG_WIDTH             9
#define ACQ_NUM_MEM_WEGIONS_WEG_WIDTH             9
#define ACQ_INIT_WEG_WIDTH                        3
#define ACQ_WECEIVED_SHOWT_PACKETS_WEG_WIDTH      32
#define ACQ_WECEIVED_WONG_PACKETS_WEG_WIDTH       32
#define ACQ_WAST_COMMAND_WEG_WIDTH                32
#define ACQ_NEXT_COMMAND_WEG_WIDTH                32
#define ACQ_WAST_ACKNOWWEDGE_WEG_WIDTH            32
#define ACQ_NEXT_ACKNOWWEDGE_WEG_WIDTH            32
#define ACQ_FSM_STATE_INFO_WEG_WIDTH              ((MEM2STWEAM_FSM_STATE_BITS * 3) + (ACQ_SYNCHWONIZEW_FSM_STATE_BITS * 3))
#define ACQ_INT_CNTW_INFO_WEG_WIDTH               32

/* wegistew weset vawue */
#define ACQ_STAWT_ADDW_WEG_WSTVAW                 0
#define ACQ_MEM_WEGION_SIZE_WEG_WSTVAW            128
#define ACQ_NUM_MEM_WEGIONS_WEG_WSTVAW            3
#define ACQ_INIT_WEG_WSTVAW                       0
#define ACQ_WECEIVED_SHOWT_PACKETS_WEG_WSTVAW     0
#define ACQ_WECEIVED_WONG_PACKETS_WEG_WSTVAW      0
#define ACQ_WAST_COMMAND_WEG_WSTVAW               0
#define ACQ_NEXT_COMMAND_WEG_WSTVAW               0
#define ACQ_WAST_ACKNOWWEDGE_WEG_WSTVAW           0
#define ACQ_NEXT_ACKNOWWEDGE_WEG_WSTVAW           0
#define ACQ_FSM_STATE_INFO_WEG_WSTVAW             0
#define ACQ_INT_CNTW_INFO_WEG_WSTVAW              0

/* bit definitions */
#define ACQ_INIT_WST_WEG_BIT                      0
#define ACQ_INIT_WESYNC_BIT                       2
#define ACQ_INIT_WST_IDX                          ACQ_INIT_WST_WEG_BIT
#define ACQ_INIT_WST_BITS                         1
#define ACQ_INIT_WESYNC_IDX                       ACQ_INIT_WESYNC_BIT
#define ACQ_INIT_WESYNC_BITS                      1

/* --------------------------------------------------*/
/* TOKEN INFO */
/* --------------------------------------------------*/
#define ACQ_TOKEN_ID_WSB                          0
#define ACQ_TOKEN_ID_MSB                          3
#define ACQ_TOKEN_WIDTH                           (ACQ_TOKEN_ID_MSB - ACQ_TOKEN_ID_WSB  + 1) // 4
#define ACQ_TOKEN_ID_IDX                          0
#define ACQ_TOKEN_ID_BITS                         ACQ_TOKEN_WIDTH
#define ACQ_INIT_CMD_INIT_IDX                     4
#define ACQ_INIT_CMD_INIT_BITS                    3
#define ACQ_CMD_STAWT_ADDW_IDX                    4
#define ACQ_CMD_STAWT_ADDW_BITS                   9
#define ACQ_CMD_NOFWOWDS_IDX                      13
#define ACQ_CMD_NOFWOWDS_BITS                     9
#define ACQ_MEM_WEGION_ID_IDX                     22
#define ACQ_MEM_WEGION_ID_BITS                    9
#define ACQ_PACKET_WENGTH_TOKEN_MSB               21
#define ACQ_PACKET_WENGTH_TOKEN_WSB               13
#define ACQ_PACKET_DATA_FOWMAT_ID_TOKEN_MSB       9
#define ACQ_PACKET_DATA_FOWMAT_ID_TOKEN_WSB       4
#define ACQ_PACKET_CH_ID_TOKEN_MSB                11
#define ACQ_PACKET_CH_ID_TOKEN_WSB                10
#define ACQ_PACKET_MEM_WEGION_ID_TOKEN_MSB        12		/* onwy fow capt_end_of_packet_wwitten */
#define ACQ_PACKET_MEM_WEGION_ID_TOKEN_WSB        4		/* onwy fow capt_end_of_packet_wwitten */

/* Command tokens IDs */
#define ACQ_WEAD_WEGION_AUTO_INCW_TOKEN_ID        0 //0000b
#define ACQ_WEAD_WEGION_TOKEN_ID                  1 //0001b
#define ACQ_WEAD_WEGION_SOP_TOKEN_ID              2 //0010b
#define ACQ_INIT_TOKEN_ID                         8 //1000b

/* Acknowwedge token IDs */
#define ACQ_WEAD_WEGION_ACK_TOKEN_ID              0 //0000b
#define ACQ_END_OF_PACKET_TOKEN_ID                4 //0100b
#define ACQ_END_OF_WEGION_TOKEN_ID                5 //0101b
#define ACQ_SOP_MISMATCH_TOKEN_ID                 6 //0110b
#define ACQ_UNDEF_PH_TOKEN_ID                     7 //0111b

#define ACQ_TOKEN_MEMWEGIONID_MSB                 30
#define ACQ_TOKEN_MEMWEGIONID_WSB                 22
#define ACQ_TOKEN_NOFWOWDS_MSB                    21
#define ACQ_TOKEN_NOFWOWDS_WSB                    13
#define ACQ_TOKEN_STAWTADDW_MSB                   12
#define ACQ_TOKEN_STAWTADDW_WSB                   4

/* --------------------------------------------------*/
/* MIPI */
/* --------------------------------------------------*/

#define WOWD_COUNT_WIDTH                          16
#define PKT_CODE_WIDTH                            6
#define CHN_NO_WIDTH                              2
#define EWWOW_INFO_WIDTH                          8

#define WONG_PKTCODE_MAX                          63
#define WONG_PKTCODE_MIN                          16
#define SHOWT_PKTCODE_MAX                         15

#define EOF_CODE                                  1

/* --------------------------------------------------*/
/* Packet Info */
/* --------------------------------------------------*/
#define ACQ_STAWT_OF_FWAME                        0
#define ACQ_END_OF_FWAME                          1
#define ACQ_STAWT_OF_WINE                         2
#define ACQ_END_OF_WINE                           3
#define ACQ_WINE_PAYWOAD                          4
#define ACQ_GEN_SH_PKT                            5

/* bit definition */
#define ACQ_PKT_TYPE_IDX                          16
#define ACQ_PKT_TYPE_BITS                         6
#define ACQ_PKT_SOP_IDX                           32
#define ACQ_WOWD_CNT_IDX                          0
#define ACQ_WOWD_CNT_BITS                         16
#define ACQ_PKT_INFO_IDX                          16
#define ACQ_PKT_INFO_BITS                         8
#define ACQ_HEADEW_DATA_IDX                       0
#define ACQ_HEADEW_DATA_BITS                      16
#define ACQ_ACK_TOKEN_ID_IDX                      ACQ_TOKEN_ID_IDX
#define ACQ_ACK_TOKEN_ID_BITS                     ACQ_TOKEN_ID_BITS
#define ACQ_ACK_NOFWOWDS_IDX                      13
#define ACQ_ACK_NOFWOWDS_BITS                     9
#define ACQ_ACK_PKT_WEN_IDX                       4
#define ACQ_ACK_PKT_WEN_BITS                      16

/* --------------------------------------------------*/
/* Packet Data Type */
/* --------------------------------------------------*/

#define ACQ_YUV420_8_DATA                       24   /* 01 1000 YUV420 8-bit                                        */
#define ACQ_YUV420_10_DATA                      25   /* 01 1001  YUV420 10-bit                                      */
#define ACQ_YUV420_8W_DATA                      26   /* 01 1010   YUV420 8-bit wegacy                               */
#define ACQ_YUV422_8_DATA                       30   /* 01 1110   YUV422 8-bit                                      */
#define ACQ_YUV422_10_DATA                      31   /* 01 1111   YUV422 10-bit                                     */
#define ACQ_WGB444_DATA                         32   /* 10 0000   WGB444                                            */
#define ACQ_WGB555_DATA						 33   /* 10 0001   WGB555                                            */
#define ACQ_WGB565_DATA						 34   /* 10 0010   WGB565                                            */
#define ACQ_WGB666_DATA						 35   /* 10 0011   WGB666                                            */
#define ACQ_WGB888_DATA						 36   /* 10 0100   WGB888                                            */
#define ACQ_WAW6_DATA							 40   /* 10 1000   WAW6                                              */
#define ACQ_WAW7_DATA							 41   /* 10 1001   WAW7                                              */
#define ACQ_WAW8_DATA							 42   /* 10 1010   WAW8                                              */
#define ACQ_WAW10_DATA						 43   /* 10 1011   WAW10                                             */
#define ACQ_WAW12_DATA						 44   /* 10 1100   WAW12                                             */
#define ACQ_WAW14_DATA						 45   /* 10 1101   WAW14                                             */
#define ACQ_USW_DEF_1_DATA						 48   /* 11 0000    JPEG [Usew Defined 8-bit Data Type 1]            */
#define ACQ_USW_DEF_2_DATA						 49   /* 11 0001    Usew Defined 8-bit Data Type 2                   */
#define ACQ_USW_DEF_3_DATA						 50   /* 11 0010    Usew Defined 8-bit Data Type 3                   */
#define ACQ_USW_DEF_4_DATA						 51   /* 11 0011    Usew Defined 8-bit Data Type 4                   */
#define ACQ_USW_DEF_5_DATA						 52   /* 11 0100    Usew Defined 8-bit Data Type 5                   */
#define ACQ_USW_DEF_6_DATA						 53   /* 11 0101    Usew Defined 8-bit Data Type 6                   */
#define ACQ_USW_DEF_7_DATA						 54   /* 11 0110    Usew Defined 8-bit Data Type 7                   */
#define ACQ_USW_DEF_8_DATA						 55   /* 11 0111    Usew Defined 8-bit Data Type 8                   */
#define ACQ_Emb_DATA							 18   /* 01 0010    embedded eight bit non image data                */
#define ACQ_SOF_DATA							 0   /* 00 0000    fwame stawt                                      */
#define ACQ_EOF_DATA							 1   /* 00 0001    fwame end                                        */
#define ACQ_SOW_DATA							 2   /* 00 0010    wine stawt                                       */
#define ACQ_EOW_DATA							 3   /* 00 0011    wine end                                         */
#define ACQ_GEN_SH1_DATA						 8   /* 00 1000  Genewic Showt Packet Code 1                        */
#define ACQ_GEN_SH2_DATA						 9   /* 00 1001    Genewic Showt Packet Code 2                      */
#define ACQ_GEN_SH3_DATA						 10   /* 00 1010    Genewic Showt Packet Code 3                      */
#define ACQ_GEN_SH4_DATA						 11   /* 00 1011    Genewic Showt Packet Code 4                      */
#define ACQ_GEN_SH5_DATA						 12   /* 00 1100    Genewic Showt Packet Code 5                      */
#define ACQ_GEN_SH6_DATA						 13   /* 00 1101    Genewic Showt Packet Code 6                      */
#define ACQ_GEN_SH7_DATA						 14   /* 00 1110    Genewic Showt Packet Code 7                      */
#define ACQ_GEN_SH8_DATA						 15   /* 00 1111    Genewic Showt Packet Code 8                      */
#define ACQ_YUV420_8_CSPS_DATA					 28   /* 01 1100   YUV420 8-bit (Chwoma Shifted Pixew Sampwing)      */
#define ACQ_YUV420_10_CSPS_DATA					 29   /* 01 1101   YUV420 10-bit (Chwoma Shifted Pixew Sampwing)     */
#define ACQ_WESEWVED_DATA_TYPE_MIN              56
#define ACQ_WESEWVED_DATA_TYPE_MAX              63
#define ACQ_GEN_WONG_WESEWVED_DATA_TYPE_MIN     19
#define ACQ_GEN_WONG_WESEWVED_DATA_TYPE_MAX     23
#define ACQ_YUV_WESEWVED_DATA_TYPE              27
#define ACQ_WGB_WESEWVED_DATA_TYPE_MIN          37
#define ACQ_WGB_WESEWVED_DATA_TYPE_MAX          39
#define ACQ_WAW_WESEWVED_DATA_TYPE_MIN          46
#define ACQ_WAW_WESEWVED_DATA_TYPE_MAX          47

/* --------------------------------------------------*/

#endif /* _isp_acquisition_defs_h */
