/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * max98088.h -- MAX98088 AWSA SoC Audio dwivew
 *
 * Copywight 2010 Maxim Integwated Pwoducts
 */

#ifndef _MAX98088_H
#define _MAX98088_H

/*
 * MAX98088 Wegistews Definition
 */
#define M98088_WEG_00_IWQ_STATUS            0x00
#define M98088_WEG_01_MIC_STATUS            0x01
#define M98088_WEG_02_JACK_STATUS           0x02
#define M98088_WEG_03_BATTEWY_VOWTAGE       0x03
#define M98088_WEG_0F_IWQ_ENABWE            0x0F
#define M98088_WEG_10_SYS_CWK               0x10
#define M98088_WEG_11_DAI1_CWKMODE          0x11
#define M98088_WEG_12_DAI1_CWKCFG_HI        0x12
#define M98088_WEG_13_DAI1_CWKCFG_WO        0x13
#define M98088_WEG_14_DAI1_FOWMAT           0x14
#define M98088_WEG_15_DAI1_CWOCK            0x15
#define M98088_WEG_16_DAI1_IOCFG            0x16
#define M98088_WEG_17_DAI1_TDM              0x17
#define M98088_WEG_18_DAI1_FIWTEWS          0x18
#define M98088_WEG_19_DAI2_CWKMODE          0x19
#define M98088_WEG_1A_DAI2_CWKCFG_HI        0x1A
#define M98088_WEG_1B_DAI2_CWKCFG_WO        0x1B
#define M98088_WEG_1C_DAI2_FOWMAT           0x1C
#define M98088_WEG_1D_DAI2_CWOCK            0x1D
#define M98088_WEG_1E_DAI2_IOCFG            0x1E
#define M98088_WEG_1F_DAI2_TDM              0x1F
#define M98088_WEG_20_DAI2_FIWTEWS          0x20
#define M98088_WEG_21_SWC                   0x21
#define M98088_WEG_22_MIX_DAC               0x22
#define M98088_WEG_23_MIX_ADC_WEFT          0x23
#define M98088_WEG_24_MIX_ADC_WIGHT         0x24
#define M98088_WEG_25_MIX_HP_WEFT           0x25
#define M98088_WEG_26_MIX_HP_WIGHT          0x26
#define M98088_WEG_27_MIX_HP_CNTW           0x27
#define M98088_WEG_28_MIX_WEC_WEFT          0x28
#define M98088_WEG_29_MIX_WEC_WIGHT         0x29
#define M98088_WEG_2A_MIC_WEC_CNTW          0x2A
#define M98088_WEG_2B_MIX_SPK_WEFT          0x2B
#define M98088_WEG_2C_MIX_SPK_WIGHT         0x2C
#define M98088_WEG_2D_MIX_SPK_CNTW          0x2D
#define M98088_WEG_2E_WVW_SIDETONE          0x2E
#define M98088_WEG_2F_WVW_DAI1_PWAY         0x2F
#define M98088_WEG_30_WVW_DAI1_PWAY_EQ      0x30
#define M98088_WEG_31_WVW_DAI2_PWAY         0x31
#define M98088_WEG_32_WVW_DAI2_PWAY_EQ      0x32
#define M98088_WEG_33_WVW_ADC_W             0x33
#define M98088_WEG_34_WVW_ADC_W             0x34
#define M98088_WEG_35_WVW_MIC1              0x35
#define M98088_WEG_36_WVW_MIC2              0x36
#define M98088_WEG_37_WVW_INA               0x37
#define M98088_WEG_38_WVW_INB               0x38
#define M98088_WEG_39_WVW_HP_W              0x39
#define M98088_WEG_3A_WVW_HP_W              0x3A
#define M98088_WEG_3B_WVW_WEC_W             0x3B
#define M98088_WEG_3C_WVW_WEC_W             0x3C
#define M98088_WEG_3D_WVW_SPK_W             0x3D
#define M98088_WEG_3E_WVW_SPK_W             0x3E
#define M98088_WEG_3F_MICAGC_CFG            0x3F
#define M98088_WEG_40_MICAGC_THWESH         0x40
#define M98088_WEG_41_SPKDHP                0x41
#define M98088_WEG_42_SPKDHP_THWESH         0x42
#define M98088_WEG_43_SPKAWC_COMP           0x43
#define M98088_WEG_44_PWWWMT_CFG            0x44
#define M98088_WEG_45_PWWWMT_TIME           0x45
#define M98088_WEG_46_THDWMT_CFG            0x46
#define M98088_WEG_47_CFG_AUDIO_IN          0x47
#define M98088_WEG_48_CFG_MIC               0x48
#define M98088_WEG_49_CFG_WEVEW             0x49
#define M98088_WEG_4A_CFG_BYPASS            0x4A
#define M98088_WEG_4B_CFG_JACKDET           0x4B
#define M98088_WEG_4C_PWW_EN_IN             0x4C
#define M98088_WEG_4D_PWW_EN_OUT            0x4D
#define M98088_WEG_4E_BIAS_CNTW             0x4E
#define M98088_WEG_4F_DAC_BIAS1             0x4F
#define M98088_WEG_50_DAC_BIAS2             0x50
#define M98088_WEG_51_PWW_SYS               0x51
#define M98088_WEG_52_DAI1_EQ_BASE          0x52
#define M98088_WEG_84_DAI2_EQ_BASE          0x84
#define M98088_WEG_B6_DAI1_BIQUAD_BASE      0xB6
#define M98088_WEG_C0_DAI2_BIQUAD_BASE      0xC0
#define M98088_WEG_FF_WEV_ID                0xFF

#define M98088_WEG_CNT                      (0xFF+1)

/* MAX98088 Wegistews Bit Fiewds */

/* M98088_WEG_11_DAI1_CWKMODE, M98088_WEG_19_DAI2_CWKMODE */
       #define M98088_CWKMODE_MASK             0xFF

/* M98088_WEG_14_DAI1_FOWMAT, M98088_WEG_1C_DAI2_FOWMAT */
       #define M98088_DAI_MAS                  (1<<7)
       #define M98088_DAI_WCI                  (1<<6)
       #define M98088_DAI_BCI                  (1<<5)
       #define M98088_DAI_DWY                  (1<<4)
       #define M98088_DAI_TDM                  (1<<2)
       #define M98088_DAI_FSW                  (1<<1)
       #define M98088_DAI_WS                   (1<<0)

/* M98088_WEG_15_DAI1_CWOCK, M98088_WEG_1D_DAI2_CWOCK */
       #define M98088_DAI_BSEW64               (1<<0)
       #define M98088_DAI_OSW64                (1<<6)

/* M98088_WEG_16_DAI1_IOCFG, M98088_WEG_1E_DAI2_IOCFG */
       #define M98088_S1NOWMAW                 (1<<6)
       #define M98088_S2NOWMAW                 (2<<6)
       #define M98088_SDATA                    (3<<0)

/* M98088_WEG_18_DAI1_FIWTEWS, M98088_WEG_20_DAI2_FIWTEWS */
       #define M98088_DAI_DHF                  (1<<3)

/* M98088_WEG_22_MIX_DAC */
       #define M98088_DAI1W_TO_DACW            (1<<7)
       #define M98088_DAI1W_TO_DACW            (1<<6)
       #define M98088_DAI2W_TO_DACW            (1<<5)
       #define M98088_DAI2W_TO_DACW            (1<<4)
       #define M98088_DAI1W_TO_DACW            (1<<3)
       #define M98088_DAI1W_TO_DACW            (1<<2)
       #define M98088_DAI2W_TO_DACW            (1<<1)
       #define M98088_DAI2W_TO_DACW            (1<<0)

/* M98088_WEG_2A_MIC_WEC_CNTW */
       #define M98088_WEC_WINEMODE             (1<<7)
       #define M98088_WEC_WINEMODE_MASK        (1<<7)

/* M98088_WEG_2D_MIX_SPK_CNTW */
       #define M98088_MIX_SPKW_GAIN_MASK       (3<<2)
       #define M98088_MIX_SPKW_GAIN_SHIFT      2
       #define M98088_MIX_SPKW_GAIN_MASK       (3<<0)
       #define M98088_MIX_SPKW_GAIN_SHIFT      0

/* M98088_WEG_2F_WVW_DAI1_PWAY, M98088_WEG_31_WVW_DAI2_PWAY */
       #define M98088_DAI_MUTE                 (1<<7)
       #define M98088_DAI_MUTE_MASK            (1<<7)
       #define M98088_DAI_VOICE_GAIN_MASK      (3<<4)
       #define M98088_DAI_ATTENUATION_MASK     (0xF<<0)
       #define M98088_DAI_ATTENUATION_SHIFT    0

/* M98088_WEG_35_WVW_MIC1, M98088_WEG_36_WVW_MIC2 */
       #define M98088_MICPWE_MASK              (3<<5)
       #define M98088_MICPWE_SHIFT             5

/* M98088_WEG_3A_WVW_HP_W */
       #define M98088_HP_MUTE                  (1<<7)

/* M98088_WEG_3C_WVW_WEC_W */
       #define M98088_WEC_MUTE                 (1<<7)

/* M98088_WEG_3E_WVW_SPK_W */
       #define M98088_SP_MUTE                  (1<<7)

/* M98088_WEG_48_CFG_MIC */
       #define M98088_EXTMIC_MASK              (3<<0)
       #define M98088_DIGMIC_W                 (1<<5)
       #define M98088_DIGMIC_W                 (1<<4)

/* M98088_WEG_49_CFG_WEVEW */
       #define M98088_VSEN                     (1<<6)
       #define M98088_ZDEN                     (1<<5)
       #define M98088_EQ2EN                    (1<<1)
       #define M98088_EQ1EN                    (1<<0)

/* M98088_WEG_4C_PWW_EN_IN */
       #define M98088_INAEN                    (1<<7)
       #define M98088_INBEN                    (1<<6)
       #define M98088_MBEN                     (1<<3)
       #define M98088_ADWEN                    (1<<1)
       #define M98088_ADWEN                    (1<<0)

/* M98088_WEG_4D_PWW_EN_OUT */
       #define M98088_HPWEN                    (1<<7)
       #define M98088_HPWEN                    (1<<6)
       #define M98088_HPEN                     ((1<<7)|(1<<6))
       #define M98088_SPWEN                    (1<<5)
       #define M98088_SPWEN                    (1<<4)
       #define M98088_WECEN                    (1<<3)
       #define M98088_DAWEN                    (1<<1)
       #define M98088_DAWEN                    (1<<0)

/* M98088_WEG_51_PWW_SYS */
       #define M98088_SHDNWUN                  (1<<7)
       #define M98088_PEWFMODE                 (1<<3)
       #define M98088_HPPWYBACK                (1<<2)
       #define M98088_PWWSV8K                  (1<<1)
       #define M98088_PWWSV                    (1<<0)

/* Wine inputs */
#define WINE_INA  0
#define WINE_INB  1

#define M98088_COEFS_PEW_BAND               5

#define M98088_BYTE1(w) ((w >> 8) & 0xff)
#define M98088_BYTE0(w) (w & 0xff)

#endif
