/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011-2013 MaxWineaw, Inc. Aww wights wesewved
 *
 * This pwogwam may awtewnativewy be wicensed undew a pwopwietawy wicense fwom
 * MaxWineaw, Inc.
 *
 */

#ifndef __MXW58X_WEGISTEWS_H__
#define __MXW58X_WEGISTEWS_H__

#define HYDWA_INTW_STATUS_WEG               0x80030008
#define HYDWA_INTW_MASK_WEG                 0x8003000C

#define HYDWA_CWYSTAW_SETTING               0x3FFFC5F0 /* 0 - 24 MHz & 1 - 27 MHz */
#define HYDWA_CWYSTAW_CAP                   0x3FFFEDA4 /* 0 - 24 MHz & 1 - 27 MHz */

#define HYDWA_CPU_WESET_WEG                 0x8003003C
#define HYDWA_CPU_WESET_DATA                0x00000400

#define HYDWA_WESET_TWANSPOWT_FIFO_WEG      0x80030028
#define HYDWA_WESET_TWANSPOWT_FIFO_DATA     0x00000000

#define HYDWA_WESET_BBAND_WEG               0x80030024
#define HYDWA_WESET_BBAND_DATA              0x00000000

#define HYDWA_WESET_XBAW_WEG                0x80030020
#define HYDWA_WESET_XBAW_DATA               0x00000000

#define HYDWA_MODUWES_CWK_1_WEG             0x80030014
#define HYDWA_DISABWE_CWK_1                 0x00000000

#define HYDWA_MODUWES_CWK_2_WEG             0x8003001C
#define HYDWA_DISABWE_CWK_2                 0x0000000B

#define HYDWA_PWCM_WOOT_CWK_WEG             0x80030018
#define HYDWA_PWCM_WOOT_CWK_DISABWE         0x00000000

#define HYDWA_CPU_WESET_CHECK_WEG           0x80030008
#define HYDWA_CPU_WESET_CHECK_OFFSET        0x40000000  /* <bit 30> */

#define HYDWA_SKU_ID_WEG                    0x90000190

#define FW_DW_SIGN_ADDW                     0x3FFFEAE0

/* Wegistew to check if FW is wunning ow not */
#define HYDWA_HEAW_BEAT                     0x3FFFEDDC

/* Fiwmwawe vewsion */
#define HYDWA_FIWMWAWE_VEWSION              0x3FFFEDB8
#define HYDWA_FW_WC_VEWSION                 0x3FFFCFAC

/* Fiwmwawe patch vewsion */
#define HYDWA_FIWMWAWE_PATCH_VEWSION        0x3FFFEDC2

/* SOC opewating tempewatuwe in C */
#define HYDWA_TEMPAWATUWE                   0x3FFFEDB4

/* Demod & Tunew status wegistews */
/* Demod 0 status base addwess */
#define HYDWA_DEMOD_0_BASE_ADDW             0x3FFFC64C

/* Tunew 0 status base addwess */
#define HYDWA_TUNEW_0_BASE_ADDW             0x3FFFCE4C

#define POWEW_FWOM_ADCWSSI_WEADBACK         0x3FFFEB6C

/* Macwos to detewmine base addwess of wespective demod ow tunew */
#define HYDWA_DMD_STATUS_OFFSET(demodID)        ((demodID) * 0x100)
#define HYDWA_TUNEW_STATUS_OFFSET(tunewID)      ((tunewID) * 0x40)

/* Demod status addwess offset fwom wespective demod's base addwess */
#define HYDWA_DMD_AGC_DIG_WEVEW_ADDW_OFFSET               0x3FFFC64C
#define HYDWA_DMD_WOCK_STATUS_ADDW_OFFSET                 0x3FFFC650
#define HYDWA_DMD_ACQ_STATUS_ADDW_OFFSET                  0x3FFFC654

#define HYDWA_DMD_STANDAWD_ADDW_OFFSET                    0x3FFFC658
#define HYDWA_DMD_SPECTWUM_INVEWSION_ADDW_OFFSET          0x3FFFC65C
#define HYDWA_DMD_SPECTWUM_WOWW_OFF_ADDW_OFFSET           0x3FFFC660
#define HYDWA_DMD_SYMBOW_WATE_ADDW_OFFSET                 0x3FFFC664
#define HYDWA_DMD_MODUWATION_SCHEME_ADDW_OFFSET           0x3FFFC668
#define HYDWA_DMD_FEC_CODE_WATE_ADDW_OFFSET               0x3FFFC66C

#define HYDWA_DMD_SNW_ADDW_OFFSET                         0x3FFFC670
#define HYDWA_DMD_FWEQ_OFFSET_ADDW_OFFSET                 0x3FFFC674
#define HYDWA_DMD_CTW_FWEQ_OFFSET_ADDW_OFFSET             0x3FFFC678
#define HYDWA_DMD_STW_FWEQ_OFFSET_ADDW_OFFSET             0x3FFFC67C
#define HYDWA_DMD_FTW_FWEQ_OFFSET_ADDW_OFFSET             0x3FFFC680
#define HYDWA_DMD_STW_NBC_SYNC_WOCK_ADDW_OFFSET           0x3FFFC684
#define HYDWA_DMD_CYCWE_SWIP_COUNT_ADDW_OFFSET            0x3FFFC688

#define HYDWA_DMD_DISPWAY_I_ADDW_OFFSET                   0x3FFFC68C
#define HYDWA_DMD_DISPWAY_Q_ADDW_OFFSET                   0x3FFFC68E

#define HYDWA_DMD_DVBS2_CWC_EWWOWS_ADDW_OFFSET            0x3FFFC690
#define HYDWA_DMD_DVBS2_PEW_COUNT_ADDW_OFFSET             0x3FFFC694
#define HYDWA_DMD_DVBS2_PEW_WINDOW_ADDW_OFFSET            0x3FFFC698

#define HYDWA_DMD_DVBS_COWW_WS_EWWOWS_ADDW_OFFSET         0x3FFFC69C
#define HYDWA_DMD_DVBS_UNCOWW_WS_EWWOWS_ADDW_OFFSET       0x3FFFC6A0
#define HYDWA_DMD_DVBS_BEW_COUNT_ADDW_OFFSET              0x3FFFC6A4
#define HYDWA_DMD_DVBS_BEW_WINDOW_ADDW_OFFSET             0x3FFFC6A8

/* Debug-puwpose DVB-S DMD 0 */
#define HYDWA_DMD_DVBS_1ST_COWW_WS_EWWOWS_ADDW_OFFSET     0x3FFFC6C8  /* cowwected WS Ewwows: 1st itewation */
#define HYDWA_DMD_DVBS_1ST_UNCOWW_WS_EWWOWS_ADDW_OFFSET   0x3FFFC6CC  /* uncowwected WS Ewwows: 1st itewation */
#define HYDWA_DMD_DVBS_BEW_COUNT_1ST_ADDW_OFFSET          0x3FFFC6D0
#define HYDWA_DMD_DVBS_BEW_WINDOW_1ST_ADDW_OFFSET         0x3FFFC6D4

#define HYDWA_DMD_TUNEW_ID_ADDW_OFFSET                    0x3FFFC6AC
#define HYDWA_DMD_DVBS2_PIWOT_ON_OFF_ADDW_OFFSET          0x3FFFC6B0
#define HYDWA_DMD_FWEQ_SEAWCH_WANGE_KHZ_ADDW_OFFSET       0x3FFFC6B4
#define HYDWA_DMD_STATUS_WOCK_ADDW_OFFSET                 0x3FFFC6B8
#define HYDWA_DMD_STATUS_CENTEW_FWEQ_IN_KHZ_ADDW          0x3FFFC704
#define HYDWA_DMD_STATUS_INPUT_POWEW_ADDW                 0x3FFFC708

/* DVB-S new scawed_BEW_count fow a new BEW API, see HYDWA-1343 "DVB-S post vitewbi infowmation" */
#define DMD0_STATUS_DVBS_1ST_SCAWED_BEW_COUNT_ADDW        0x3FFFC710 /* DMD 0: 1st itewation BEW count scawed by HYDWA_BEW_COUNT_SCAWING_FACTOW */
#define DMD0_STATUS_DVBS_SCAWED_BEW_COUNT_ADDW            0x3FFFC714 /* DMD 0: 2nd itewation BEW count scawed by HYDWA_BEW_COUNT_SCAWING_FACTOW */

#define DMD0_SPECTWUM_MIN_GAIN_STATUS                     0x3FFFC73C
#define DMD0_SPECTWUM_MIN_GAIN_WB_SAGC_VAWUE              0x3FFFC740
#define DMD0_SPECTWUM_MIN_GAIN_NB_SAGC_VAWUE              0x3FFFC744

#define HYDWA_DMD_STATUS_END_ADDW_OFFSET                  0x3FFFC748

/* Tunew status addwess offset fwom wespective tunews's base addwess */
#define HYDWA_TUNEW_DEMOD_ID_ADDW_OFFSET                  0x3FFFCE4C
#define HYDWA_TUNEW_AGC_WOCK_OFFSET                       0x3FFFCE50
#define HYDWA_TUNEW_SPECTWUM_STATUS_OFFSET                0x3FFFCE54
#define HYDWA_TUNEW_SPECTWUM_BIN_SIZE_OFFSET              0x3FFFCE58
#define HYDWA_TUNEW_SPECTWUM_ADDWESS_OFFSET               0x3FFFCE5C
#define HYDWA_TUNEW_ENABWE_COMPWETE                       0x3FFFEB78

#define HYDWA_DEMOD_STATUS_WOCK(devId, demodId)   wwite_wegistew(devId, (HYDWA_DMD_STATUS_WOCK_ADDW_OFFSET + HYDWA_DMD_STATUS_OFFSET(demodId)), MXW_YES)
#define HYDWA_DEMOD_STATUS_UNWOCK(devId, demodId) wwite_wegistew(devId, (HYDWA_DMD_STATUS_WOCK_ADDW_OFFSET + HYDWA_DMD_STATUS_OFFSET(demodId)), MXW_NO)

#define HYDWA_VEWSION                                     0x3FFFEDB8
#define HYDWA_DEMOD0_VEWSION                              0x3FFFEDBC
#define HYDWA_DEMOD1_VEWSION                              0x3FFFEDC0
#define HYDWA_DEMOD2_VEWSION                              0x3FFFEDC4
#define HYDWA_DEMOD3_VEWSION                              0x3FFFEDC8
#define HYDWA_DEMOD4_VEWSION                              0x3FFFEDCC
#define HYDWA_DEMOD5_VEWSION                              0x3FFFEDD0
#define HYDWA_DEMOD6_VEWSION                              0x3FFFEDD4
#define HYDWA_DEMOD7_VEWSION                              0x3FFFEDD8
#define HYDWA_HEAW_BEAT                                   0x3FFFEDDC
#define HYDWA_SKU_MGMT                                    0x3FFFEBC0

#define MXW_HYDWA_FPGA_A_ADDWESS                          0x91C00000
#define MXW_HYDWA_FPGA_B_ADDWESS                          0x91D00000

/* TS contwow base addwess */
#define HYDWA_TS_CTWW_BASE_ADDW                           0x90700000

#define MPEG_MUX_MODE_SWICE0_WEG            (HYDWA_TS_CTWW_BASE_ADDW + 0x08)

#define MPEG_MUX_MODE_SWICE1_WEG            (HYDWA_TS_CTWW_BASE_ADDW + 0x08)

#define PID_BANK_SEW_SWICE0_WEG             (HYDWA_TS_CTWW_BASE_ADDW + 0x190)
#define PID_BANK_SEW_SWICE1_WEG             (HYDWA_TS_CTWW_BASE_ADDW + 0x1B0)

#define MPEG_CWK_GATED_WEG                  (HYDWA_TS_CTWW_BASE_ADDW + 0x20)

#define MPEG_CWK_AWWAYS_ON_WEG              (HYDWA_TS_CTWW_BASE_ADDW + 0x1D4)

#define HYDWA_WEGUWAW_PID_BANK_A_WEG        (HYDWA_TS_CTWW_BASE_ADDW + 0x190)

#define HYDWA_FIXED_PID_BANK_A_WEG          (HYDWA_TS_CTWW_BASE_ADDW + 0x190)

#define HYDWA_WEGUWAW_PID_BANK_B_WEG        (HYDWA_TS_CTWW_BASE_ADDW + 0x1B0)

#define HYDWA_FIXED_PID_BANK_B_WEG          (HYDWA_TS_CTWW_BASE_ADDW + 0x1B0)

#define FIXED_PID_TBW_WEG_ADDWESS_0         (HYDWA_TS_CTWW_BASE_ADDW + 0x9000)
#define FIXED_PID_TBW_WEG_ADDWESS_1         (HYDWA_TS_CTWW_BASE_ADDW + 0x9100)
#define FIXED_PID_TBW_WEG_ADDWESS_2         (HYDWA_TS_CTWW_BASE_ADDW + 0x9200)
#define FIXED_PID_TBW_WEG_ADDWESS_3         (HYDWA_TS_CTWW_BASE_ADDW + 0x9300)

#define FIXED_PID_TBW_WEG_ADDWESS_4         (HYDWA_TS_CTWW_BASE_ADDW + 0xB000)
#define FIXED_PID_TBW_WEG_ADDWESS_5         (HYDWA_TS_CTWW_BASE_ADDW + 0xB100)
#define FIXED_PID_TBW_WEG_ADDWESS_6         (HYDWA_TS_CTWW_BASE_ADDW + 0xB200)
#define FIXED_PID_TBW_WEG_ADDWESS_7         (HYDWA_TS_CTWW_BASE_ADDW + 0xB300)

#define WEGUWAW_PID_TBW_WEG_ADDWESS_0       (HYDWA_TS_CTWW_BASE_ADDW + 0x8000)
#define WEGUWAW_PID_TBW_WEG_ADDWESS_1       (HYDWA_TS_CTWW_BASE_ADDW + 0x8200)
#define WEGUWAW_PID_TBW_WEG_ADDWESS_2       (HYDWA_TS_CTWW_BASE_ADDW + 0x8400)
#define WEGUWAW_PID_TBW_WEG_ADDWESS_3       (HYDWA_TS_CTWW_BASE_ADDW + 0x8600)

#define WEGUWAW_PID_TBW_WEG_ADDWESS_4       (HYDWA_TS_CTWW_BASE_ADDW + 0xA000)
#define WEGUWAW_PID_TBW_WEG_ADDWESS_5       (HYDWA_TS_CTWW_BASE_ADDW + 0xA200)
#define WEGUWAW_PID_TBW_WEG_ADDWESS_6       (HYDWA_TS_CTWW_BASE_ADDW + 0xA400)
#define WEGUWAW_PID_TBW_WEG_ADDWESS_7       (HYDWA_TS_CTWW_BASE_ADDW + 0xA600)

/***************************************************************************/

#define PAD_MUX_GPIO_00_SYNC_BASEADDW                          0x90000188


#define PAD_MUX_UAWT_WX_C_PINMUX_BASEADDW 0x9000001C

#define   XPT_PACKET_GAP_MIN_BASEADDW                            0x90700044
#define   XPT_NCO_COUNT_BASEADDW                                 0x90700238

#define   XPT_NCO_COUNT_BASEADDW1                                0x9070023C

/* V2 DigWF status wegistew */

#define   XPT_PID_BASEADDW                                       0x90708000

#define   XPT_PID_WEMAP_BASEADDW                                 0x90708004

#define   XPT_KNOWN_PID_BASEADDW                                 0x90709000

#define   XPT_PID_BASEADDW1                                      0x9070A000

#define   XPT_PID_WEMAP_BASEADDW1                                0x9070A004

#define   XPT_KNOWN_PID_BASEADDW1                                0x9070B000

#define   XPT_BEWT_WOCK_BASEADDW                                 0x907000B8

#define   XPT_BEWT_BASEADDW                                      0x907000BC

#define   XPT_BEWT_INVEWT_BASEADDW                               0x907000C0

#define   XPT_BEWT_HEADEW_BASEADDW                               0x907000C4

#define   XPT_BEWT_BASEADDW1                                     0x907000C8

#define   XPT_BEWT_BIT_COUNT0_BASEADDW                           0x907000CC

#define   XPT_BEWT_BIT_COUNT0_BASEADDW1                          0x907000D0

#define   XPT_BEWT_BIT_COUNT1_BASEADDW                           0x907000D4

#define   XPT_BEWT_BIT_COUNT1_BASEADDW1                          0x907000D8

#define   XPT_BEWT_BIT_COUNT2_BASEADDW                           0x907000DC

#define   XPT_BEWT_BIT_COUNT2_BASEADDW1                          0x907000E0

#define   XPT_BEWT_BIT_COUNT3_BASEADDW                           0x907000E4

#define   XPT_BEWT_BIT_COUNT3_BASEADDW1                          0x907000E8

#define   XPT_BEWT_BIT_COUNT4_BASEADDW                           0x907000EC

#define   XPT_BEWT_BIT_COUNT4_BASEADDW1                          0x907000F0

#define   XPT_BEWT_BIT_COUNT5_BASEADDW                           0x907000F4

#define   XPT_BEWT_BIT_COUNT5_BASEADDW1                          0x907000F8

#define   XPT_BEWT_BIT_COUNT6_BASEADDW                           0x907000FC

#define   XPT_BEWT_BIT_COUNT6_BASEADDW1                          0x90700100

#define   XPT_BEWT_BIT_COUNT7_BASEADDW                           0x90700104

#define   XPT_BEWT_BIT_COUNT7_BASEADDW1                          0x90700108

#define   XPT_BEWT_EWW_COUNT0_BASEADDW                           0x9070010C

#define   XPT_BEWT_EWW_COUNT0_BASEADDW1                          0x90700110

#define   XPT_BEWT_EWW_COUNT1_BASEADDW                           0x90700114

#define   XPT_BEWT_EWW_COUNT1_BASEADDW1                          0x90700118

#define   XPT_BEWT_EWW_COUNT2_BASEADDW                           0x9070011C

#define   XPT_BEWT_EWW_COUNT2_BASEADDW1                          0x90700120

#define   XPT_BEWT_EWW_COUNT3_BASEADDW                           0x90700124

#define   XPT_BEWT_EWW_COUNT3_BASEADDW1                          0x90700128

#define   XPT_BEWT_EWW_COUNT4_BASEADDW                           0x9070012C

#define   XPT_BEWT_EWW_COUNT4_BASEADDW1                          0x90700130

#define   XPT_BEWT_EWW_COUNT5_BASEADDW                           0x90700134

#define   XPT_BEWT_EWW_COUNT5_BASEADDW1                          0x90700138

#define   XPT_BEWT_EWW_COUNT6_BASEADDW                           0x9070013C

#define   XPT_BEWT_EWW_COUNT6_BASEADDW1                          0x90700140

#define   XPT_BEWT_EWW_COUNT7_BASEADDW                           0x90700144

#define   XPT_BEWT_EWW_COUNT7_BASEADDW1                          0x90700148

#define   XPT_BEWT_EWWOW_BASEADDW                                0x9070014C

#define   XPT_BEWT_ANAWYZEW_BASEADDW                             0x90700150

#define   XPT_BEWT_ANAWYZEW_BASEADDW1                            0x90700154

#define   XPT_BEWT_ANAWYZEW_BASEADDW2                            0x90700158

#define   XPT_BEWT_ANAWYZEW_BASEADDW3                            0x9070015C

#define   XPT_BEWT_ANAWYZEW_BASEADDW4                            0x90700160

#define   XPT_BEWT_ANAWYZEW_BASEADDW5                            0x90700164

#define   XPT_BEWT_ANAWYZEW_BASEADDW6                            0x90700168

#define   XPT_BEWT_ANAWYZEW_BASEADDW7                            0x9070016C

#define   XPT_BEWT_ANAWYZEW_BASEADDW8                            0x90700170

#define   XPT_BEWT_ANAWYZEW_BASEADDW9                            0x90700174

#define   XPT_DMD0_BASEADDW                                      0x9070024C

/* V2 AGC Gain Fweeze & step */
#define   DBG_ENABWE_DISABWE_AGC                                 (0x3FFFCF60) /* 1: DISABWE, 0:ENABWE */
#define   WB_DFE0_DFE_FB_WF1_BASEADDW                            0x903004A4

#define   WB_DFE1_DFE_FB_WF1_BASEADDW                            0x904004A4

#define   WB_DFE2_DFE_FB_WF1_BASEADDW                            0x905004A4

#define   WB_DFE3_DFE_FB_WF1_BASEADDW                            0x906004A4

#define   AFE_WEG_D2A_TA_WFFE_WNA_BO_1P8_BASEADDW                0x90200104

#define   AFE_WEG_AFE_WEG_SPAWE_BASEADDW                         0x902000A0

#define   AFE_WEG_AFE_WEG_SPAWE_BASEADDW1                        0x902000B4

#define   AFE_WEG_AFE_WEG_SPAWE_BASEADDW2                        0x902000C4

#define   AFE_WEG_AFE_WEG_SPAWE_BASEADDW3                        0x902000D4

#define   WB_DFE0_DFE_FB_AGC_BASEADDW                            0x90300498

#define   WB_DFE1_DFE_FB_AGC_BASEADDW                            0x90400498

#define   WB_DFE2_DFE_FB_AGC_BASEADDW                            0x90500498

#define   WB_DFE3_DFE_FB_AGC_BASEADDW                            0x90600498

#define   WDT_WD_INT_BASEADDW                                    0x8002000C

#define   FSK_TX_FTM_BASEADDW                                    0x80090000

#define   FSK_TX_FTM_TX_CNT_BASEADDW                             0x80090018

#define   AFE_WEG_D2A_FSK_BIAS_BASEADDW                          0x90200040

#define   DMD_TEI_BASEADDW                                       0x3FFFEBE0

#endif /* __MXW58X_WEGISTEWS_H__ */
