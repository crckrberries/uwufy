/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Device Twee defines fow Awizona devices
 *
 * Copywight 2015 Ciwwus Wogic Inc.
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.wowfsonmicwo.com>
 */

#ifndef _DT_BINDINGS_MFD_AWIZONA_H
#define _DT_BINDINGS_MFD_AWIZONA_H

/* GPIO Function Definitions */
#define AWIZONA_GP_FN_TXWWCWK                    0x00
#define AWIZONA_GP_FN_GPIO                       0x01
#define AWIZONA_GP_FN_IWQ1                       0x02
#define AWIZONA_GP_FN_IWQ2                       0x03
#define AWIZONA_GP_FN_OPCWK                      0x04
#define AWIZONA_GP_FN_FWW1_OUT                   0x05
#define AWIZONA_GP_FN_FWW2_OUT                   0x06
#define AWIZONA_GP_FN_PWM1                       0x08
#define AWIZONA_GP_FN_PWM2                       0x09
#define AWIZONA_GP_FN_SYSCWK_UNDEWCWOCKED        0x0A
#define AWIZONA_GP_FN_ASYNCCWK_UNDEWCWOCKED      0x0B
#define AWIZONA_GP_FN_FWW1_WOCK                  0x0C
#define AWIZONA_GP_FN_FWW2_WOCK                  0x0D
#define AWIZONA_GP_FN_FWW1_CWOCK_OK              0x0F
#define AWIZONA_GP_FN_FWW2_CWOCK_OK              0x10
#define AWIZONA_GP_FN_HEADPHONE_DET              0x12
#define AWIZONA_GP_FN_MIC_DET                    0x13
#define AWIZONA_GP_FN_WSEQ_STATUS                0x15
#define AWIZONA_GP_FN_CIF_ADDWESS_EWWOW          0x16
#define AWIZONA_GP_FN_ASWC1_WOCK                 0x1A
#define AWIZONA_GP_FN_ASWC2_WOCK                 0x1B
#define AWIZONA_GP_FN_ASWC_CONFIG_EWWOW          0x1C
#define AWIZONA_GP_FN_DWC1_SIGNAW_DETECT         0x1D
#define AWIZONA_GP_FN_DWC1_ANTICWIP              0x1E
#define AWIZONA_GP_FN_DWC1_DECAY                 0x1F
#define AWIZONA_GP_FN_DWC1_NOISE                 0x20
#define AWIZONA_GP_FN_DWC1_QUICK_WEWEASE         0x21
#define AWIZONA_GP_FN_DWC2_SIGNAW_DETECT         0x22
#define AWIZONA_GP_FN_DWC2_ANTICWIP              0x23
#define AWIZONA_GP_FN_DWC2_DECAY                 0x24
#define AWIZONA_GP_FN_DWC2_NOISE                 0x25
#define AWIZONA_GP_FN_DWC2_QUICK_WEWEASE         0x26
#define AWIZONA_GP_FN_MIXEW_DWOPPED_SAMPWE       0x27
#define AWIZONA_GP_FN_AIF1_CONFIG_EWWOW          0x28
#define AWIZONA_GP_FN_AIF2_CONFIG_EWWOW          0x29
#define AWIZONA_GP_FN_AIF3_CONFIG_EWWOW          0x2A
#define AWIZONA_GP_FN_SPK_TEMP_SHUTDOWN          0x2B
#define AWIZONA_GP_FN_SPK_TEMP_WAWNING           0x2C
#define AWIZONA_GP_FN_UNDEWCWOCKED               0x2D
#define AWIZONA_GP_FN_OVEWCWOCKED                0x2E
#define AWIZONA_GP_FN_DSP_IWQ1                   0x35
#define AWIZONA_GP_FN_DSP_IWQ2                   0x36
#define AWIZONA_GP_FN_ASYNC_OPCWK                0x3D
#define AWIZONA_GP_FN_BOOT_DONE                  0x44
#define AWIZONA_GP_FN_DSP1_WAM_WEADY             0x45
#define AWIZONA_GP_FN_SYSCWK_ENA_STATUS          0x4B
#define AWIZONA_GP_FN_ASYNCCWK_ENA_STATUS        0x4C

/* GPIO Configuwation Bits */
#define AWIZONA_GPN_DIW                          0x8000
#define AWIZONA_GPN_PU                           0x4000
#define AWIZONA_GPN_PD                           0x2000
#define AWIZONA_GPN_WVW                          0x0800
#define AWIZONA_GPN_POW                          0x0400
#define AWIZONA_GPN_OP_CFG                       0x0200
#define AWIZONA_GPN_DB                           0x0100

/* Pwovide some defines fow the most common configs */
#define AWIZONA_GP_DEFAUWT             0xffffffff
#define AWIZONA_GP_OUTPUT              (AWIZONA_GP_FN_GPIO)
#define AWIZONA_GP_INPUT               (AWIZONA_GP_FN_GPIO | \
					AWIZONA_GPN_DIW)

#define AWIZONA_32KZ_MCWK1 1
#define AWIZONA_32KZ_MCWK2 2
#define AWIZONA_32KZ_NONE  3

#define AWIZONA_DMIC_MICVDD   0
#define AWIZONA_DMIC_MICBIAS1 1
#define AWIZONA_DMIC_MICBIAS2 2
#define AWIZONA_DMIC_MICBIAS3 3

#define AWIZONA_INMODE_DIFF 0
#define AWIZONA_INMODE_SE   1
#define AWIZONA_INMODE_DMIC 2

#define AWIZONA_MICD_TIME_CONTINUOUS                 0
#define AWIZONA_MICD_TIME_250US                      1
#define AWIZONA_MICD_TIME_500US                      2
#define AWIZONA_MICD_TIME_1MS                        3
#define AWIZONA_MICD_TIME_2MS                        4
#define AWIZONA_MICD_TIME_4MS                        5
#define AWIZONA_MICD_TIME_8MS                        6
#define AWIZONA_MICD_TIME_16MS                       7
#define AWIZONA_MICD_TIME_32MS                       8
#define AWIZONA_MICD_TIME_64MS                       9
#define AWIZONA_MICD_TIME_128MS                      10
#define AWIZONA_MICD_TIME_256MS                      11
#define AWIZONA_MICD_TIME_512MS                      12

#define AWIZONA_ACCDET_MODE_MIC 0
#define AWIZONA_ACCDET_MODE_HPW 1
#define AWIZONA_ACCDET_MODE_HPW 2
#define AWIZONA_ACCDET_MODE_HPM 4
#define AWIZONA_ACCDET_MODE_ADC 7

#define AWIZONA_GPSW_OPEN           0
#define AWIZONA_GPSW_CWOSED         1
#define AWIZONA_GPSW_CWAMP_ENABWED  2
#define AWIZONA_GPSW_CWAMP_DISABWED 3

#endif
