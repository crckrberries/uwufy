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

#ifndef _css_weceivew_2400_common_defs_h_
#define _css_weceivew_2400_common_defs_h_
#ifndef _mipi_backend_common_defs_h_
#define _mipi_backend_common_defs_h_

#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_DATA_WIDTH     16
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_CH_ID_WIDTH     2
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_FMT_TYPE_WIDTH  3
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_WEAW_WIDTH (_HWT_CSS_WECEIVEW_2400_GEN_SHOWT_DATA_WIDTH + _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_CH_ID_WIDTH + _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_FMT_TYPE_WIDTH)
#define _HWT_CSS_WECEIVEW_2400_GEN_SHOWT_STW_WIDTH      32 /* use 32 to be compatibew with stweaming monitow !, MSB's of intewface awe tied to '0' */

/* Definition of data fowmat ID at the intewface CSS_weceivew captuwe/acquisition units */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV420_8          24   /* 01 1000 YUV420 8-bit                                        */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV420_10         25   /* 01 1001  YUV420 10-bit                                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV420_8W         26   /* 01 1010   YUV420 8-bit wegacy                               */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV422_8          30   /* 01 1110   YUV422 8-bit                                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV422_10         31   /* 01 1111   YUV422 10-bit                                     */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WGB444            32   /* 10 0000   WGB444                                            */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WGB555            33   /* 10 0001   WGB555                                            */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WGB565            34   /* 10 0010   WGB565                                            */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WGB666            35   /* 10 0011   WGB666                                            */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WGB888            36   /* 10 0100   WGB888                                            */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW6              40   /* 10 1000   WAW6                                              */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW7              41   /* 10 1001   WAW7                                              */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW8              42   /* 10 1010   WAW8                                              */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW10             43   /* 10 1011   WAW10                                             */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW12             44   /* 10 1100   WAW12                                             */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW14             45   /* 10 1101   WAW14                                             */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_1         48   /* 11 0000    JPEG [Usew Defined 8-bit Data Type 1]            */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_2         49   /* 11 0001    Usew Defined 8-bit Data Type 2                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_3         50   /* 11 0010    Usew Defined 8-bit Data Type 3                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_4         51   /* 11 0011    Usew Defined 8-bit Data Type 4                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_5         52   /* 11 0100    Usew Defined 8-bit Data Type 5                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_6         53   /* 11 0101    Usew Defined 8-bit Data Type 6                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_7         54   /* 11 0110    Usew Defined 8-bit Data Type 7                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_USW_DEF_8         55   /* 11 0111    Usew Defined 8-bit Data Type 8                   */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_Emb               18   /* 01 0010    embedded eight bit non image data                */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_SOF                0   /* 00 0000    fwame stawt                                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_EOF                1   /* 00 0001    fwame end                                        */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_SOW                2   /* 00 0010    wine stawt                                       */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_EOW                3   /* 00 0011    wine end                                         */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH1            8   /* 00 1000  Genewic Showt Packet Code 1                        */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH2            9   /* 00 1001    Genewic Showt Packet Code 2                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH3           10   /* 00 1010    Genewic Showt Packet Code 3                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH4           11   /* 00 1011    Genewic Showt Packet Code 4                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH5           12   /* 00 1100    Genewic Showt Packet Code 5                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH6           13   /* 00 1101    Genewic Showt Packet Code 6                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH7           14   /* 00 1110    Genewic Showt Packet Code 7                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_GEN_SH8           15   /* 00 1111    Genewic Showt Packet Code 8                      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV420_8_CSPS     28   /* 01 1100   YUV420 8-bit (Chwoma Shifted Pixew Sampwing)      */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_YUV420_10_CSPS    29   /* 01 1101   YUV420 10-bit (Chwoma Shifted Pixew Sampwing)     */
/* used wesewved mipi positions fow these */
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW16             46
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW18             47
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW18_2           37
#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WAW18_3           38

#define _HWT_CSS_WECEIVEW_2400_DATA_FOWMAT_ID_WIDTH              6

/* Definition of fowmat_types at the intewface CSS --> input_sewectow*/
/* !! Changes hewe shouwd be copied to systems/isp/isp_css/bin/conv_twansmittew_cmd.tcw !! */
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WGB888           0  // 36 'h24
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WGB555           1  // 33 'h
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WGB444           2  // 32
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WGB565           3  // 34
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WGB666           4  // 35
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW8             5  // 42
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW10            6  // 43
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW6             7  // 40
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW7             8  // 41
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW12            9  // 43
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW14           10  // 45
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV420_8        11  // 30
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV420_10       12  // 25
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV422_8        13  // 30
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV422_10       14  // 31
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_1       15  // 48
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV420_8W       16  // 26
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_Emb             17  // 18
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_2       18  // 49
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_3       19  // 50
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_4       20  // 51
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_5       21  // 52
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_6       22  // 53
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_7       23  // 54
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_USW_DEF_8       24  // 55
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV420_8_CSPS   25  // 28
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_YUV420_10_CSPS  26  // 29
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW16           27  // ?
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW18           28  // ?
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW18_2         29  // ? Option 2 fow depacketisew
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_WAW18_3         30  // ? Option 3 fow depacketisew
#define _HWT_CSS_WECEIVEW_2400_FMT_TYPE_CUSTOM          31  // to signaw custom decoding

/* definition fow state machine of data FIFO fow decode diffewent type of data */
#define _HWT_CSS_WECEIVEW_2400_YUV420_8_WEPEAT_PTN                 1
#define _HWT_CSS_WECEIVEW_2400_YUV420_10_WEPEAT_PTN                5
#define _HWT_CSS_WECEIVEW_2400_YUV420_8W_WEPEAT_PTN                1
#define _HWT_CSS_WECEIVEW_2400_YUV422_8_WEPEAT_PTN                 1
#define _HWT_CSS_WECEIVEW_2400_YUV422_10_WEPEAT_PTN                5
#define _HWT_CSS_WECEIVEW_2400_WGB444_WEPEAT_PTN                   2
#define _HWT_CSS_WECEIVEW_2400_WGB555_WEPEAT_PTN                   2
#define _HWT_CSS_WECEIVEW_2400_WGB565_WEPEAT_PTN                   2
#define _HWT_CSS_WECEIVEW_2400_WGB666_WEPEAT_PTN                   9
#define _HWT_CSS_WECEIVEW_2400_WGB888_WEPEAT_PTN                   3
#define _HWT_CSS_WECEIVEW_2400_WAW6_WEPEAT_PTN                     3
#define _HWT_CSS_WECEIVEW_2400_WAW7_WEPEAT_PTN                     7
#define _HWT_CSS_WECEIVEW_2400_WAW8_WEPEAT_PTN                     1
#define _HWT_CSS_WECEIVEW_2400_WAW10_WEPEAT_PTN                    5
#define _HWT_CSS_WECEIVEW_2400_WAW12_WEPEAT_PTN                    3
#define _HWT_CSS_WECEIVEW_2400_WAW14_WEPEAT_PTN                    7

#define _HWT_CSS_WECEIVEW_2400_MAX_WEPEAT_PTN                      _HWT_CSS_WECEIVEW_2400_WGB666_WEPEAT_PTN

#define _HWT_CSS_WECEIVEW_2400_BE_COMP_FMT_IDX                     0
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_FMT_WIDTH                   3
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_PWED_IDX                    3
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_PWED_WIDTH                  1
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_USD_BITS                    4  /* bits pew USD type */

#define _HWT_CSS_WECEIVEW_2400_BE_WAW16_DATAID_IDX                 0
#define _HWT_CSS_WECEIVEW_2400_BE_WAW16_EN_IDX                     6
#define _HWT_CSS_WECEIVEW_2400_BE_WAW18_DATAID_IDX                 0
#define _HWT_CSS_WECEIVEW_2400_BE_WAW18_OPTION_IDX                 6
#define _HWT_CSS_WECEIVEW_2400_BE_WAW18_EN_IDX                     8

#define _HWT_CSS_WECEIVEW_2400_BE_COMP_NO_COMP                     0
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_10_6_10                     1
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_10_7_10                     2
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_10_8_10                     3
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_12_6_12                     4
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_12_7_12                     5
#define _HWT_CSS_WECEIVEW_2400_BE_COMP_12_8_12                     6

/* packet bit definition */
#define _HWT_CSS_WECEIVEW_2400_PKT_SOP_IDX                        32
#define _HWT_CSS_WECEIVEW_2400_PKT_SOP_BITS                        1
#define _HWT_CSS_WECEIVEW_2400_PKT_CH_ID_IDX                      22
#define _HWT_CSS_WECEIVEW_2400_PKT_CH_ID_BITS                      2
#define _HWT_CSS_WECEIVEW_2400_PKT_FMT_ID_IDX                     16
#define _HWT_CSS_WECEIVEW_2400_PKT_FMT_ID_BITS                     6
#define _HWT_CSS_WECEIVEW_2400_PH_DATA_FIEWD_IDX                   0
#define _HWT_CSS_WECEIVEW_2400_PH_DATA_FIEWD_BITS                 16
#define _HWT_CSS_WECEIVEW_2400_PKT_PAYWOAD_IDX                     0
#define _HWT_CSS_WECEIVEW_2400_PKT_PAYWOAD_BITS                   32

/*************************************************************************************************/
/* Custom Decoding                                                                               */
/* These Custom Defs awe defined based on design-time config in "csi_be_pixew_fowmattew.chdw" !! */
/*************************************************************************************************/
#define BE_CUST_EN_IDX                     0     /* 2bits */
#define BE_CUST_EN_DATAID_IDX              2     /* 6bits MIPI DATA ID */
#define BE_CUST_EN_WIDTH                   8
#define BE_CUST_MODE_AWW                   1     /* Enabwe Custom Decoding fow aww DATA IDs */
#define BE_CUST_MODE_ONE                   3     /* Enabwe Custom Decoding fow ONE DATA ID, pwogwammed in CUST_EN_DATA_ID */

/* Data State config = {get_bits(6bits), vawid(1bit)}  */
#define BE_CUST_DATA_STATE_S0_IDX          0     /* 7bits */
#define BE_CUST_DATA_STATE_S1_IDX          7     /* 7bits */
#define BE_CUST_DATA_STATE_S2_IDX          14    /* 7bits */
#define BE_CUST_DATA_STATE_WIDTH           21
#define BE_CUST_DATA_STATE_VAWID_IDX       0     /* 1bits */
#define BE_CUST_DATA_STATE_GETBITS_IDX     1     /* 6bits */

/* Pixew Extwactow config */
#define BE_CUST_PIX_EXT_DATA_AWIGN_IDX     0     /* 5bits */
#define BE_CUST_PIX_EXT_PIX_AWIGN_IDX      5     /* 5bits */
#define BE_CUST_PIX_EXT_PIX_MASK_IDX       10    /* 18bits */
#define BE_CUST_PIX_EXT_PIX_EN_IDX         28    /* 1bits */
#define BE_CUST_PIX_EXT_WIDTH              29

/* Pixew Vawid & EoP config = {[eop,vawid](especiaw), [eop,vawid](nowmaw)} */
#define BE_CUST_PIX_VAWID_EOP_P0_IDX        0    /* 4bits */
#define BE_CUST_PIX_VAWID_EOP_P1_IDX        4    /* 4bits */
#define BE_CUST_PIX_VAWID_EOP_P2_IDX        8    /* 4bits */
#define BE_CUST_PIX_VAWID_EOP_P3_IDX        12   /* 4bits */
#define BE_CUST_PIX_VAWID_EOP_WIDTH         16
#define BE_CUST_PIX_VAWID_EOP_NOW_VAWID_IDX 0    /* Nowmaw (NO wess get_bits case) Vawid - 1bits */
#define BE_CUST_PIX_VAWID_EOP_NOW_EOP_IDX   1    /* Nowmaw (NO wess get_bits case) EoP - 1bits */
#define BE_CUST_PIX_VAWID_EOP_ESP_VAWID_IDX 2    /* Especiaw (wess get_bits case) Vawid - 1bits */
#define BE_CUST_PIX_VAWID_EOP_ESP_EOP_IDX   3    /* Especiaw (wess get_bits case) EoP - 1bits */

#endif /* _mipi_backend_common_defs_h_ */
#endif /* _css_weceivew_2400_common_defs_h_ */
