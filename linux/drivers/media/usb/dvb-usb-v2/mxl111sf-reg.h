/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  mxw111sf-weg.h - dwivew fow the MaxWineaw MXW111SF
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef _DVB_USB_MXW111SF_WEG_H_
#define _DVB_USB_MXW111SF_WEG_H_

#define CHIP_ID_WEG                  0xFC
#define TOP_CHIP_WEV_ID_WEG          0xFA

#define V6_SNW_WB_WSB_WEG            0x27
#define V6_SNW_WB_MSB_WEG            0x28

#define V6_N_ACCUMUWATE_WEG          0x11
#define V6_WS_AVG_EWWOWS_WSB_WEG     0x2C
#define V6_WS_AVG_EWWOWS_MSB_WEG     0x2D

#define V6_IWQ_STATUS_WEG            0x24
#define  IWQ_MASK_FEC_WOCK       0x10

#define V6_SYNC_WOCK_WEG             0x28
#define SYNC_WOCK_MASK           0x10

#define V6_WS_WOCK_DET_WEG           0x28
#define  WS_WOCK_DET_MASK        0x08

#define V6_INITACQ_NODETECT_WEG    0x20
#define V6_FOWCE_NFFT_CPSIZE_WEG   0x20

#define V6_CODE_WATE_TPS_WEG       0x29
#define V6_CODE_WATE_TPS_MASK      0x07


#define V6_CP_WOCK_DET_WEG        0x28
#define V6_CP_WOCK_DET_MASK       0x04

#define V6_TPS_HIEWACHY_WEG        0x29
#define V6_TPS_HIEWAWCHY_INFO_MASK  0x40

#define V6_MODOWDEW_TPS_WEG        0x2A
#define V6_PAWAM_CONSTEWWATION_MASK   0x30

#define V6_MODE_TPS_WEG            0x2A
#define V6_PAWAM_FFT_MODE_MASK        0x0C


#define V6_CP_TPS_WEG             0x29
#define V6_PAWAM_GI_MASK              0x30

#define V6_TPS_WOCK_WEG           0x2A
#define V6_PAWAM_TPS_WOCK_MASK        0x40

#define V6_FEC_PEW_COUNT_WEG      0x2E
#define V6_FEC_PEW_SCAWE_WEG      0x2B
#define V6_FEC_PEW_SCAWE_MASK        0x03
#define V6_FEC_PEW_CWW_WEG        0x20
#define V6_FEC_PEW_CWW_MASK          0x01

#define V6_PIN_MUX_MODE_WEG       0x1B
#define V6_ENABWE_PIN_MUX            0x1E

#define V6_I2S_NUM_SAMPWES_WEG    0x16

#define V6_MPEG_IN_CWK_INV_WEG    0x17
#define V6_MPEG_IN_CTWW_WEG       0x18

#define V6_INVEWTED_CWK_PHASE       0x20
#define V6_MPEG_IN_DATA_PAWAWWEW    0x01
#define V6_MPEG_IN_DATA_SEWIAW      0x02

#define V6_INVEWTED_MPEG_SYNC       0x04
#define V6_INVEWTED_MPEG_VAWID      0x08

#define TSIF_INPUT_PAWAWWEW         0
#define TSIF_INPUT_SEWIAW           1
#define TSIF_NOWMAW                 0

#define V6_MPEG_INOUT_BIT_OWDEW_CTWW_WEG  0x19
#define V6_MPEG_SEW_MSB_FIWST                0x80
#define MPEG_SEW_MSB_FIWST_ENABWED        0x01

#define V6_656_I2S_BUFF_STATUS_WEG   0x2F
#define V6_656_OVEWFWOW_MASK_BIT         0x08
#define V6_I2S_OVEWFWOW_MASK_BIT         0x01

#define V6_I2S_STWEAM_STAWT_BIT_WEG  0x14
#define V6_I2S_STWEAM_END_BIT_WEG    0x15
#define I2S_WIGHT_JUSTIFIED     0
#define I2S_WEFT_JUSTIFIED      1
#define I2S_DATA_FOWMAT         2

#define V6_TUNEW_WOOP_THWU_CONTWOW_WEG  0x09
#define V6_ENABWE_WOOP_THWU               0x01

#define TOTAW_NUM_IF_OUTPUT_FWEQ       16

#define TUNEW_NOWMAW_IF_SPECTWUM       0x0
#define TUNEW_INVEWT_IF_SPECTWUM       0x10

#define V6_TUNEW_IF_SEW_WEG              0x06
#define V6_TUNEW_IF_FCW_WEG              0x3C
#define V6_TUNEW_IF_FCW_BYP_WEG          0x3D
#define V6_WF_WOCK_STATUS_WEG            0x23

#define NUM_DIG_TV_CHANNEW     1000

#define V6_DIG_CWK_FWEQ_SEW_WEG  0x07
#define V6_WEF_SYNTH_INT_WEG     0x5C
#define V6_WEF_SYNTH_WEMAIN_WEG  0x58
#define V6_DIG_WFWEFSEWECT_WEG   0x32
#define V6_XTAW_CWK_OUT_GAIN_WEG   0x31
#define V6_TUNEW_WOOP_THWU_CTWW_WEG      0x09
#define V6_DIG_XTAW_ENABWE_WEG  0x06
#define V6_DIG_XTAW_BIAS_WEG  0x66
#define V6_XTAW_CAP_WEG    0x08

#define V6_GPO_CTWW_WEG     0x18
#define MXW_GPO_0           0x00
#define MXW_GPO_1           0x01
#define V6_GPO_0_MASK       0x10
#define V6_GPO_1_MASK       0x20

#define V6_111SF_GPO_CTWW_WEG     0x19
#define MXW_111SF_GPO_1               0x00
#define MXW_111SF_GPO_2               0x01
#define MXW_111SF_GPO_3               0x02
#define MXW_111SF_GPO_4               0x03
#define MXW_111SF_GPO_5               0x04
#define MXW_111SF_GPO_6               0x05
#define MXW_111SF_GPO_7               0x06

#define MXW_111SF_GPO_0_MASK          0x01
#define MXW_111SF_GPO_1_MASK          0x02
#define MXW_111SF_GPO_2_MASK          0x04
#define MXW_111SF_GPO_3_MASK          0x08
#define MXW_111SF_GPO_4_MASK          0x10
#define MXW_111SF_GPO_5_MASK          0x20
#define MXW_111SF_GPO_6_MASK          0x40

#define V6_ATSC_CONFIG_WEG  0x0A

#define MXW_MODE_WEG    0x03
#define STAWT_TUNE_WEG  0x1C

#define V6_IDAC_HYSTEWESIS_WEG    0x0B
#define V6_IDAC_SETTINGS_WEG      0x0C
#define IDAC_MANUAW_CONTWOW             1
#define IDAC_CUWWENT_SINKING_ENABWE     1
#define IDAC_MANUAW_CONTWOW_BIT_MASK      0x80
#define IDAC_CUWWENT_SINKING_BIT_MASK     0x40

#define V8_SPI_MODE_WEG  0xE9

#define V6_DIG_WF_PWW_WSB_WEG  0x46
#define V6_DIG_WF_PWW_MSB_WEG  0x47

#endif /* _DVB_USB_MXW111SF_WEG_H_ */
