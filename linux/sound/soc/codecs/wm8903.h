/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8903.h - WM8903 audio codec intewface
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8903_H
#define _WM8903_H

#incwude <winux/i2c.h>

extewn int wm8903_mic_detect(stwuct snd_soc_component *component,
			     stwuct snd_soc_jack *jack,
			     int det, int shwt);


/*
 * Wegistew vawues.
 */
#define WM8903_SW_WESET_AND_ID                  0x00
#define WM8903_WEVISION_NUMBEW                  0x01
#define WM8903_BIAS_CONTWOW_0                   0x04
#define WM8903_VMID_CONTWOW_0                   0x05
#define WM8903_MIC_BIAS_CONTWOW_0               0x06
#define WM8903_ANAWOGUE_DAC_0                   0x08
#define WM8903_ANAWOGUE_ADC_0                   0x0A
#define WM8903_POWEW_MANAGEMENT_0               0x0C
#define WM8903_POWEW_MANAGEMENT_1               0x0D
#define WM8903_POWEW_MANAGEMENT_2               0x0E
#define WM8903_POWEW_MANAGEMENT_3               0x0F
#define WM8903_POWEW_MANAGEMENT_4               0x10
#define WM8903_POWEW_MANAGEMENT_5               0x11
#define WM8903_POWEW_MANAGEMENT_6               0x12
#define WM8903_CWOCK_WATES_0                    0x14
#define WM8903_CWOCK_WATES_1                    0x15
#define WM8903_CWOCK_WATES_2                    0x16
#define WM8903_AUDIO_INTEWFACE_0                0x18
#define WM8903_AUDIO_INTEWFACE_1                0x19
#define WM8903_AUDIO_INTEWFACE_2                0x1A
#define WM8903_AUDIO_INTEWFACE_3                0x1B
#define WM8903_DAC_DIGITAW_VOWUME_WEFT          0x1E
#define WM8903_DAC_DIGITAW_VOWUME_WIGHT         0x1F
#define WM8903_DAC_DIGITAW_0                    0x20
#define WM8903_DAC_DIGITAW_1                    0x21
#define WM8903_ADC_DIGITAW_VOWUME_WEFT          0x24
#define WM8903_ADC_DIGITAW_VOWUME_WIGHT         0x25
#define WM8903_ADC_DIGITAW_0                    0x26
#define WM8903_DIGITAW_MICWOPHONE_0             0x27
#define WM8903_DWC_0                            0x28
#define WM8903_DWC_1                            0x29
#define WM8903_DWC_2                            0x2A
#define WM8903_DWC_3                            0x2B
#define WM8903_ANAWOGUE_WEFT_INPUT_0            0x2C
#define WM8903_ANAWOGUE_WIGHT_INPUT_0           0x2D
#define WM8903_ANAWOGUE_WEFT_INPUT_1            0x2E
#define WM8903_ANAWOGUE_WIGHT_INPUT_1           0x2F
#define WM8903_ANAWOGUE_WEFT_MIX_0              0x32
#define WM8903_ANAWOGUE_WIGHT_MIX_0             0x33
#define WM8903_ANAWOGUE_SPK_MIX_WEFT_0          0x34
#define WM8903_ANAWOGUE_SPK_MIX_WEFT_1          0x35
#define WM8903_ANAWOGUE_SPK_MIX_WIGHT_0         0x36
#define WM8903_ANAWOGUE_SPK_MIX_WIGHT_1         0x37
#define WM8903_ANAWOGUE_OUT1_WEFT               0x39
#define WM8903_ANAWOGUE_OUT1_WIGHT              0x3A
#define WM8903_ANAWOGUE_OUT2_WEFT               0x3B
#define WM8903_ANAWOGUE_OUT2_WIGHT              0x3C
#define WM8903_ANAWOGUE_OUT3_WEFT               0x3E
#define WM8903_ANAWOGUE_OUT3_WIGHT              0x3F
#define WM8903_ANAWOGUE_SPK_OUTPUT_CONTWOW_0    0x41
#define WM8903_DC_SEWVO_0                       0x43
#define WM8903_DC_SEWVO_2                       0x45
#define WM8903_DC_SEWVO_4			0x47
#define WM8903_DC_SEWVO_5			0x48
#define WM8903_DC_SEWVO_6			0x49
#define WM8903_DC_SEWVO_7			0x4A
#define WM8903_DC_SEWVO_WEADBACK_1		0x51
#define WM8903_DC_SEWVO_WEADBACK_2		0x52
#define WM8903_DC_SEWVO_WEADBACK_3		0x53
#define WM8903_DC_SEWVO_WEADBACK_4		0x54
#define WM8903_ANAWOGUE_HP_0                    0x5A
#define WM8903_ANAWOGUE_WINEOUT_0               0x5E
#define WM8903_CHAWGE_PUMP_0                    0x62
#define WM8903_CWASS_W_0                        0x68
#define WM8903_WWITE_SEQUENCEW_0                0x6C
#define WM8903_WWITE_SEQUENCEW_1                0x6D
#define WM8903_WWITE_SEQUENCEW_2                0x6E
#define WM8903_WWITE_SEQUENCEW_3                0x6F
#define WM8903_WWITE_SEQUENCEW_4                0x70
#define WM8903_CONTWOW_INTEWFACE                0x72
#define WM8903_GPIO_CONTWOW_1                   0x74
#define WM8903_GPIO_CONTWOW_2                   0x75
#define WM8903_GPIO_CONTWOW_3                   0x76
#define WM8903_GPIO_CONTWOW_4                   0x77
#define WM8903_GPIO_CONTWOW_5                   0x78
#define WM8903_INTEWWUPT_STATUS_1               0x79
#define WM8903_INTEWWUPT_STATUS_1_MASK          0x7A
#define WM8903_INTEWWUPT_POWAWITY_1             0x7B
#define WM8903_INTEWWUPT_CONTWOW                0x7E
#define WM8903_CWOCK_WATE_TEST_4                0xA4
#define WM8903_ANAWOGUE_OUTPUT_BIAS_0           0xAC

#define WM8903_WEGISTEW_COUNT                   75
#define WM8903_MAX_WEGISTEW                     0xAC

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - SW Weset and ID
 */
#define WM8903_SW_WESET_DEV_ID1_MASK            0xFFFF  /* SW_WESET_DEV_ID1 - [15:0] */
#define WM8903_SW_WESET_DEV_ID1_SHIFT                0  /* SW_WESET_DEV_ID1 - [15:0] */
#define WM8903_SW_WESET_DEV_ID1_WIDTH               16  /* SW_WESET_DEV_ID1 - [15:0] */

/*
 * W1 (0x01) - Wevision Numbew
 */
#define WM8903_CHIP_WEV_MASK                    0x000F  /* CHIP_WEV - [3:0] */
#define WM8903_CHIP_WEV_SHIFT                        0  /* CHIP_WEV - [3:0] */
#define WM8903_CHIP_WEV_WIDTH                        4  /* CHIP_WEV - [3:0] */

/*
 * W4 (0x04) - Bias Contwow 0
 */
#define WM8903_POBCTWW                          0x0010  /* POBCTWW */
#define WM8903_POBCTWW_MASK                     0x0010  /* POBCTWW */
#define WM8903_POBCTWW_SHIFT                         4  /* POBCTWW */
#define WM8903_POBCTWW_WIDTH                         1  /* POBCTWW */
#define WM8903_ISEW_MASK                        0x000C  /* ISEW - [3:2] */
#define WM8903_ISEW_SHIFT                            2  /* ISEW - [3:2] */
#define WM8903_ISEW_WIDTH                            2  /* ISEW - [3:2] */
#define WM8903_STAWTUP_BIAS_ENA                 0x0002  /* STAWTUP_BIAS_ENA */
#define WM8903_STAWTUP_BIAS_ENA_MASK            0x0002  /* STAWTUP_BIAS_ENA */
#define WM8903_STAWTUP_BIAS_ENA_SHIFT                1  /* STAWTUP_BIAS_ENA */
#define WM8903_STAWTUP_BIAS_ENA_WIDTH                1  /* STAWTUP_BIAS_ENA */
#define WM8903_BIAS_ENA                         0x0001  /* BIAS_ENA */
#define WM8903_BIAS_ENA_MASK                    0x0001  /* BIAS_ENA */
#define WM8903_BIAS_ENA_SHIFT                        0  /* BIAS_ENA */
#define WM8903_BIAS_ENA_WIDTH                        1  /* BIAS_ENA */

/*
 * W5 (0x05) - VMID Contwow 0
 */
#define WM8903_VMID_TIE_ENA                     0x0080  /* VMID_TIE_ENA */
#define WM8903_VMID_TIE_ENA_MASK                0x0080  /* VMID_TIE_ENA */
#define WM8903_VMID_TIE_ENA_SHIFT                    7  /* VMID_TIE_ENA */
#define WM8903_VMID_TIE_ENA_WIDTH                    1  /* VMID_TIE_ENA */
#define WM8903_BUFIO_ENA                        0x0040  /* BUFIO_ENA */
#define WM8903_BUFIO_ENA_MASK                   0x0040  /* BUFIO_ENA */
#define WM8903_BUFIO_ENA_SHIFT                       6  /* BUFIO_ENA */
#define WM8903_BUFIO_ENA_WIDTH                       1  /* BUFIO_ENA */
#define WM8903_VMID_IO_ENA                      0x0020  /* VMID_IO_ENA */
#define WM8903_VMID_IO_ENA_MASK                 0x0020  /* VMID_IO_ENA */
#define WM8903_VMID_IO_ENA_SHIFT                     5  /* VMID_IO_ENA */
#define WM8903_VMID_IO_ENA_WIDTH                     1  /* VMID_IO_ENA */
#define WM8903_VMID_SOFT_MASK                   0x0018  /* VMID_SOFT - [4:3] */
#define WM8903_VMID_SOFT_SHIFT                       3  /* VMID_SOFT - [4:3] */
#define WM8903_VMID_SOFT_WIDTH                       2  /* VMID_SOFT - [4:3] */
#define WM8903_VMID_WES_MASK                    0x0006  /* VMID_WES - [2:1] */
#define WM8903_VMID_WES_SHIFT                        1  /* VMID_WES - [2:1] */
#define WM8903_VMID_WES_WIDTH                        2  /* VMID_WES - [2:1] */
#define WM8903_VMID_BUF_ENA                     0x0001  /* VMID_BUF_ENA */
#define WM8903_VMID_BUF_ENA_MASK                0x0001  /* VMID_BUF_ENA */
#define WM8903_VMID_BUF_ENA_SHIFT                    0  /* VMID_BUF_ENA */
#define WM8903_VMID_BUF_ENA_WIDTH                    1  /* VMID_BUF_ENA */

#define WM8903_VMID_WES_50K                          2
#define WM8903_VMID_WES_250K                         4
#define WM8903_VMID_WES_5K                           6

/*
 * W8 (0x08) - Anawogue DAC 0
 */
#define WM8903_DACBIAS_SEW_MASK                 0x0018  /* DACBIAS_SEW - [4:3] */
#define WM8903_DACBIAS_SEW_SHIFT                     3  /* DACBIAS_SEW - [4:3] */
#define WM8903_DACBIAS_SEW_WIDTH                     2  /* DACBIAS_SEW - [4:3] */
#define WM8903_DACVMID_BIAS_SEW_MASK            0x0006  /* DACVMID_BIAS_SEW - [2:1] */
#define WM8903_DACVMID_BIAS_SEW_SHIFT                1  /* DACVMID_BIAS_SEW - [2:1] */
#define WM8903_DACVMID_BIAS_SEW_WIDTH                2  /* DACVMID_BIAS_SEW - [2:1] */

/*
 * W10 (0x0A) - Anawogue ADC 0
 */
#define WM8903_ADC_OSW128                       0x0001  /* ADC_OSW128 */
#define WM8903_ADC_OSW128_MASK                  0x0001  /* ADC_OSW128 */
#define WM8903_ADC_OSW128_SHIFT                      0  /* ADC_OSW128 */
#define WM8903_ADC_OSW128_WIDTH                      1  /* ADC_OSW128 */

/*
 * W12 (0x0C) - Powew Management 0
 */
#define WM8903_INW_ENA                          0x0002  /* INW_ENA */
#define WM8903_INW_ENA_MASK                     0x0002  /* INW_ENA */
#define WM8903_INW_ENA_SHIFT                         1  /* INW_ENA */
#define WM8903_INW_ENA_WIDTH                         1  /* INW_ENA */
#define WM8903_INW_ENA                          0x0001  /* INW_ENA */
#define WM8903_INW_ENA_MASK                     0x0001  /* INW_ENA */
#define WM8903_INW_ENA_SHIFT                         0  /* INW_ENA */
#define WM8903_INW_ENA_WIDTH                         1  /* INW_ENA */

/*
 * W13 (0x0D) - Powew Management 1
 */
#define WM8903_MIXOUTW_ENA                      0x0002  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA_MASK                 0x0002  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA_SHIFT                     1  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA_WIDTH                     1  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA                      0x0001  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA_MASK                 0x0001  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA_SHIFT                     0  /* MIXOUTW_ENA */
#define WM8903_MIXOUTW_ENA_WIDTH                     1  /* MIXOUTW_ENA */

/*
 * W14 (0x0E) - Powew Management 2
 */
#define WM8903_HPW_PGA_ENA                      0x0002  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA_MASK                 0x0002  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA_SHIFT                     1  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA_WIDTH                     1  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA                      0x0001  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA_MASK                 0x0001  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA_SHIFT                     0  /* HPW_PGA_ENA */
#define WM8903_HPW_PGA_ENA_WIDTH                     1  /* HPW_PGA_ENA */

/*
 * W15 (0x0F) - Powew Management 3
 */
#define WM8903_WINEOUTW_PGA_ENA                 0x0002  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA_MASK            0x0002  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA_SHIFT                1  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA_WIDTH                1  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA                 0x0001  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA_MASK            0x0001  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA_SHIFT                0  /* WINEOUTW_PGA_ENA */
#define WM8903_WINEOUTW_PGA_ENA_WIDTH                1  /* WINEOUTW_PGA_ENA */

/*
 * W16 (0x10) - Powew Management 4
 */
#define WM8903_MIXSPKW_ENA                      0x0002  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA_MASK                 0x0002  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA_SHIFT                     1  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA_WIDTH                     1  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA                      0x0001  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA_MASK                 0x0001  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA_SHIFT                     0  /* MIXSPKW_ENA */
#define WM8903_MIXSPKW_ENA_WIDTH                     1  /* MIXSPKW_ENA */

/*
 * W17 (0x11) - Powew Management 5
 */
#define WM8903_SPKW_ENA                         0x0002  /* SPKW_ENA */
#define WM8903_SPKW_ENA_MASK                    0x0002  /* SPKW_ENA */
#define WM8903_SPKW_ENA_SHIFT                        1  /* SPKW_ENA */
#define WM8903_SPKW_ENA_WIDTH                        1  /* SPKW_ENA */
#define WM8903_SPKW_ENA                         0x0001  /* SPKW_ENA */
#define WM8903_SPKW_ENA_MASK                    0x0001  /* SPKW_ENA */
#define WM8903_SPKW_ENA_SHIFT                        0  /* SPKW_ENA */
#define WM8903_SPKW_ENA_WIDTH                        1  /* SPKW_ENA */

/*
 * W18 (0x12) - Powew Management 6
 */
#define WM8903_DACW_ENA                         0x0008  /* DACW_ENA */
#define WM8903_DACW_ENA_MASK                    0x0008  /* DACW_ENA */
#define WM8903_DACW_ENA_SHIFT                        3  /* DACW_ENA */
#define WM8903_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8903_DACW_ENA                         0x0004  /* DACW_ENA */
#define WM8903_DACW_ENA_MASK                    0x0004  /* DACW_ENA */
#define WM8903_DACW_ENA_SHIFT                        2  /* DACW_ENA */
#define WM8903_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8903_ADCW_ENA                         0x0002  /* ADCW_ENA */
#define WM8903_ADCW_ENA_MASK                    0x0002  /* ADCW_ENA */
#define WM8903_ADCW_ENA_SHIFT                        1  /* ADCW_ENA */
#define WM8903_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */
#define WM8903_ADCW_ENA                         0x0001  /* ADCW_ENA */
#define WM8903_ADCW_ENA_MASK                    0x0001  /* ADCW_ENA */
#define WM8903_ADCW_ENA_SHIFT                        0  /* ADCW_ENA */
#define WM8903_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */

/*
 * W20 (0x14) - Cwock Wates 0
 */
#define WM8903_MCWKDIV2                         0x0001  /* MCWKDIV2 */
#define WM8903_MCWKDIV2_MASK                    0x0001  /* MCWKDIV2 */
#define WM8903_MCWKDIV2_SHIFT                        0  /* MCWKDIV2 */
#define WM8903_MCWKDIV2_WIDTH                        1  /* MCWKDIV2 */

/*
 * W21 (0x15) - Cwock Wates 1
 */
#define WM8903_CWK_SYS_WATE_MASK                0x3C00  /* CWK_SYS_WATE - [13:10] */
#define WM8903_CWK_SYS_WATE_SHIFT                   10  /* CWK_SYS_WATE - [13:10] */
#define WM8903_CWK_SYS_WATE_WIDTH                    4  /* CWK_SYS_WATE - [13:10] */
#define WM8903_CWK_SYS_MODE_MASK                0x0300  /* CWK_SYS_MODE - [9:8] */
#define WM8903_CWK_SYS_MODE_SHIFT                    8  /* CWK_SYS_MODE - [9:8] */
#define WM8903_CWK_SYS_MODE_WIDTH                    2  /* CWK_SYS_MODE - [9:8] */
#define WM8903_SAMPWE_WATE_MASK                 0x000F  /* SAMPWE_WATE - [3:0] */
#define WM8903_SAMPWE_WATE_SHIFT                     0  /* SAMPWE_WATE - [3:0] */
#define WM8903_SAMPWE_WATE_WIDTH                     4  /* SAMPWE_WATE - [3:0] */

/*
 * W22 (0x16) - Cwock Wates 2
 */
#define WM8903_CWK_SYS_ENA                      0x0004  /* CWK_SYS_ENA */
#define WM8903_CWK_SYS_ENA_MASK                 0x0004  /* CWK_SYS_ENA */
#define WM8903_CWK_SYS_ENA_SHIFT                     2  /* CWK_SYS_ENA */
#define WM8903_CWK_SYS_ENA_WIDTH                     1  /* CWK_SYS_ENA */
#define WM8903_CWK_DSP_ENA                      0x0002  /* CWK_DSP_ENA */
#define WM8903_CWK_DSP_ENA_MASK                 0x0002  /* CWK_DSP_ENA */
#define WM8903_CWK_DSP_ENA_SHIFT                     1  /* CWK_DSP_ENA */
#define WM8903_CWK_DSP_ENA_WIDTH                     1  /* CWK_DSP_ENA */
#define WM8903_TO_ENA                           0x0001  /* TO_ENA */
#define WM8903_TO_ENA_MASK                      0x0001  /* TO_ENA */
#define WM8903_TO_ENA_SHIFT                          0  /* TO_ENA */
#define WM8903_TO_ENA_WIDTH                          1  /* TO_ENA */

/*
 * W24 (0x18) - Audio Intewface 0
 */
#define WM8903_DACW_DATINV                      0x1000  /* DACW_DATINV */
#define WM8903_DACW_DATINV_MASK                 0x1000  /* DACW_DATINV */
#define WM8903_DACW_DATINV_SHIFT                    12  /* DACW_DATINV */
#define WM8903_DACW_DATINV_WIDTH                     1  /* DACW_DATINV */
#define WM8903_DACW_DATINV                      0x0800  /* DACW_DATINV */
#define WM8903_DACW_DATINV_MASK                 0x0800  /* DACW_DATINV */
#define WM8903_DACW_DATINV_SHIFT                    11  /* DACW_DATINV */
#define WM8903_DACW_DATINV_WIDTH                     1  /* DACW_DATINV */
#define WM8903_DAC_BOOST_MASK                   0x0600  /* DAC_BOOST - [10:9] */
#define WM8903_DAC_BOOST_SHIFT                       9  /* DAC_BOOST - [10:9] */
#define WM8903_DAC_BOOST_WIDTH                       2  /* DAC_BOOST - [10:9] */
#define WM8903_WOOPBACK                         0x0100  /* WOOPBACK */
#define WM8903_WOOPBACK_MASK                    0x0100  /* WOOPBACK */
#define WM8903_WOOPBACK_SHIFT                        8  /* WOOPBACK */
#define WM8903_WOOPBACK_WIDTH                        1  /* WOOPBACK */
#define WM8903_AIFADCW_SWC                      0x0080  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC_MASK                 0x0080  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC_SHIFT                     7  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC_WIDTH                     1  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC                      0x0040  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC_MASK                 0x0040  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC_SHIFT                     6  /* AIFADCW_SWC */
#define WM8903_AIFADCW_SWC_WIDTH                     1  /* AIFADCW_SWC */
#define WM8903_AIFDACW_SWC                      0x0020  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC_MASK                 0x0020  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC_SHIFT                     5  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC_WIDTH                     1  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC                      0x0010  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC_MASK                 0x0010  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC_SHIFT                     4  /* AIFDACW_SWC */
#define WM8903_AIFDACW_SWC_WIDTH                     1  /* AIFDACW_SWC */
#define WM8903_ADC_COMP                         0x0008  /* ADC_COMP */
#define WM8903_ADC_COMP_MASK                    0x0008  /* ADC_COMP */
#define WM8903_ADC_COMP_SHIFT                        3  /* ADC_COMP */
#define WM8903_ADC_COMP_WIDTH                        1  /* ADC_COMP */
#define WM8903_ADC_COMPMODE                     0x0004  /* ADC_COMPMODE */
#define WM8903_ADC_COMPMODE_MASK                0x0004  /* ADC_COMPMODE */
#define WM8903_ADC_COMPMODE_SHIFT                    2  /* ADC_COMPMODE */
#define WM8903_ADC_COMPMODE_WIDTH                    1  /* ADC_COMPMODE */
#define WM8903_DAC_COMP                         0x0002  /* DAC_COMP */
#define WM8903_DAC_COMP_MASK                    0x0002  /* DAC_COMP */
#define WM8903_DAC_COMP_SHIFT                        1  /* DAC_COMP */
#define WM8903_DAC_COMP_WIDTH                        1  /* DAC_COMP */
#define WM8903_DAC_COMPMODE                     0x0001  /* DAC_COMPMODE */
#define WM8903_DAC_COMPMODE_MASK                0x0001  /* DAC_COMPMODE */
#define WM8903_DAC_COMPMODE_SHIFT                    0  /* DAC_COMPMODE */
#define WM8903_DAC_COMPMODE_WIDTH                    1  /* DAC_COMPMODE */

/*
 * W25 (0x19) - Audio Intewface 1
 */
#define WM8903_AIFDAC_TDM                       0x2000  /* AIFDAC_TDM */
#define WM8903_AIFDAC_TDM_MASK                  0x2000  /* AIFDAC_TDM */
#define WM8903_AIFDAC_TDM_SHIFT                     13  /* AIFDAC_TDM */
#define WM8903_AIFDAC_TDM_WIDTH                      1  /* AIFDAC_TDM */
#define WM8903_AIFDAC_TDM_CHAN                  0x1000  /* AIFDAC_TDM_CHAN */
#define WM8903_AIFDAC_TDM_CHAN_MASK             0x1000  /* AIFDAC_TDM_CHAN */
#define WM8903_AIFDAC_TDM_CHAN_SHIFT                12  /* AIFDAC_TDM_CHAN */
#define WM8903_AIFDAC_TDM_CHAN_WIDTH                 1  /* AIFDAC_TDM_CHAN */
#define WM8903_AIFADC_TDM                       0x0800  /* AIFADC_TDM */
#define WM8903_AIFADC_TDM_MASK                  0x0800  /* AIFADC_TDM */
#define WM8903_AIFADC_TDM_SHIFT                     11  /* AIFADC_TDM */
#define WM8903_AIFADC_TDM_WIDTH                      1  /* AIFADC_TDM */
#define WM8903_AIFADC_TDM_CHAN                  0x0400  /* AIFADC_TDM_CHAN */
#define WM8903_AIFADC_TDM_CHAN_MASK             0x0400  /* AIFADC_TDM_CHAN */
#define WM8903_AIFADC_TDM_CHAN_SHIFT                10  /* AIFADC_TDM_CHAN */
#define WM8903_AIFADC_TDM_CHAN_WIDTH                 1  /* AIFADC_TDM_CHAN */
#define WM8903_WWCWK_DIW                        0x0200  /* WWCWK_DIW */
#define WM8903_WWCWK_DIW_MASK                   0x0200  /* WWCWK_DIW */
#define WM8903_WWCWK_DIW_SHIFT                       9  /* WWCWK_DIW */
#define WM8903_WWCWK_DIW_WIDTH                       1  /* WWCWK_DIW */
#define WM8903_AIF_BCWK_INV                     0x0080  /* AIF_BCWK_INV */
#define WM8903_AIF_BCWK_INV_MASK                0x0080  /* AIF_BCWK_INV */
#define WM8903_AIF_BCWK_INV_SHIFT                    7  /* AIF_BCWK_INV */
#define WM8903_AIF_BCWK_INV_WIDTH                    1  /* AIF_BCWK_INV */
#define WM8903_BCWK_DIW                         0x0040  /* BCWK_DIW */
#define WM8903_BCWK_DIW_MASK                    0x0040  /* BCWK_DIW */
#define WM8903_BCWK_DIW_SHIFT                        6  /* BCWK_DIW */
#define WM8903_BCWK_DIW_WIDTH                        1  /* BCWK_DIW */
#define WM8903_AIF_WWCWK_INV                    0x0010  /* AIF_WWCWK_INV */
#define WM8903_AIF_WWCWK_INV_MASK               0x0010  /* AIF_WWCWK_INV */
#define WM8903_AIF_WWCWK_INV_SHIFT                   4  /* AIF_WWCWK_INV */
#define WM8903_AIF_WWCWK_INV_WIDTH                   1  /* AIF_WWCWK_INV */
#define WM8903_AIF_WW_MASK                      0x000C  /* AIF_WW - [3:2] */
#define WM8903_AIF_WW_SHIFT                          2  /* AIF_WW - [3:2] */
#define WM8903_AIF_WW_WIDTH                          2  /* AIF_WW - [3:2] */
#define WM8903_AIF_FMT_MASK                     0x0003  /* AIF_FMT - [1:0] */
#define WM8903_AIF_FMT_SHIFT                         0  /* AIF_FMT - [1:0] */
#define WM8903_AIF_FMT_WIDTH                         2  /* AIF_FMT - [1:0] */

/*
 * W26 (0x1A) - Audio Intewface 2
 */
#define WM8903_BCWK_DIV_MASK                    0x001F  /* BCWK_DIV - [4:0] */
#define WM8903_BCWK_DIV_SHIFT                        0  /* BCWK_DIV - [4:0] */
#define WM8903_BCWK_DIV_WIDTH                        5  /* BCWK_DIV - [4:0] */

/*
 * W27 (0x1B) - Audio Intewface 3
 */
#define WM8903_WWCWK_WATE_MASK                  0x07FF  /* WWCWK_WATE - [10:0] */
#define WM8903_WWCWK_WATE_SHIFT                      0  /* WWCWK_WATE - [10:0] */
#define WM8903_WWCWK_WATE_WIDTH                     11  /* WWCWK_WATE - [10:0] */

/*
 * W30 (0x1E) - DAC Digitaw Vowume Weft
 */
#define WM8903_DACVU                            0x0100  /* DACVU */
#define WM8903_DACVU_MASK                       0x0100  /* DACVU */
#define WM8903_DACVU_SHIFT                           8  /* DACVU */
#define WM8903_DACVU_WIDTH                           1  /* DACVU */
#define WM8903_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8903_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8903_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W31 (0x1F) - DAC Digitaw Vowume Wight
 */
#define WM8903_DACVU                            0x0100  /* DACVU */
#define WM8903_DACVU_MASK                       0x0100  /* DACVU */
#define WM8903_DACVU_SHIFT                           8  /* DACVU */
#define WM8903_DACVU_WIDTH                           1  /* DACVU */
#define WM8903_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8903_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8903_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W32 (0x20) - DAC Digitaw 0
 */
#define WM8903_ADCW_DAC_SVOW_MASK               0x0F00  /* ADCW_DAC_SVOW - [11:8] */
#define WM8903_ADCW_DAC_SVOW_SHIFT                   8  /* ADCW_DAC_SVOW - [11:8] */
#define WM8903_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [11:8] */
#define WM8903_ADCW_DAC_SVOW_MASK               0x00F0  /* ADCW_DAC_SVOW - [7:4] */
#define WM8903_ADCW_DAC_SVOW_SHIFT                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8903_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8903_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8903_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8903_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */
#define WM8903_ADC_TO_DACW_MASK                 0x0003  /* ADC_TO_DACW - [1:0] */
#define WM8903_ADC_TO_DACW_SHIFT                     0  /* ADC_TO_DACW - [1:0] */
#define WM8903_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [1:0] */

/*
 * W33 (0x21) - DAC Digitaw 1
 */
#define WM8903_DAC_MONO                         0x1000  /* DAC_MONO */
#define WM8903_DAC_MONO_MASK                    0x1000  /* DAC_MONO */
#define WM8903_DAC_MONO_SHIFT                       12  /* DAC_MONO */
#define WM8903_DAC_MONO_WIDTH                        1  /* DAC_MONO */
#define WM8903_DAC_SB_FIWT                      0x0800  /* DAC_SB_FIWT */
#define WM8903_DAC_SB_FIWT_MASK                 0x0800  /* DAC_SB_FIWT */
#define WM8903_DAC_SB_FIWT_SHIFT                    11  /* DAC_SB_FIWT */
#define WM8903_DAC_SB_FIWT_WIDTH                     1  /* DAC_SB_FIWT */
#define WM8903_DAC_MUTEWATE                     0x0400  /* DAC_MUTEWATE */
#define WM8903_DAC_MUTEWATE_MASK                0x0400  /* DAC_MUTEWATE */
#define WM8903_DAC_MUTEWATE_SHIFT                   10  /* DAC_MUTEWATE */
#define WM8903_DAC_MUTEWATE_WIDTH                    1  /* DAC_MUTEWATE */
#define WM8903_DAC_MUTEMODE                     0x0200  /* DAC_MUTEMODE */
#define WM8903_DAC_MUTEMODE_MASK                0x0200  /* DAC_MUTEMODE */
#define WM8903_DAC_MUTEMODE_SHIFT                    9  /* DAC_MUTEMODE */
#define WM8903_DAC_MUTEMODE_WIDTH                    1  /* DAC_MUTEMODE */
#define WM8903_DAC_MUTE                         0x0008  /* DAC_MUTE */
#define WM8903_DAC_MUTE_MASK                    0x0008  /* DAC_MUTE */
#define WM8903_DAC_MUTE_SHIFT                        3  /* DAC_MUTE */
#define WM8903_DAC_MUTE_WIDTH                        1  /* DAC_MUTE */
#define WM8903_DEEMPH_MASK                      0x0006  /* DEEMPH - [2:1] */
#define WM8903_DEEMPH_SHIFT                          1  /* DEEMPH - [2:1] */
#define WM8903_DEEMPH_WIDTH                          2  /* DEEMPH - [2:1] */

/*
 * W36 (0x24) - ADC Digitaw Vowume Weft
 */
#define WM8903_ADCVU                            0x0100  /* ADCVU */
#define WM8903_ADCVU_MASK                       0x0100  /* ADCVU */
#define WM8903_ADCVU_SHIFT                           8  /* ADCVU */
#define WM8903_ADCVU_WIDTH                           1  /* ADCVU */
#define WM8903_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8903_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8903_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W37 (0x25) - ADC Digitaw Vowume Wight
 */
#define WM8903_ADCVU                            0x0100  /* ADCVU */
#define WM8903_ADCVU_MASK                       0x0100  /* ADCVU */
#define WM8903_ADCVU_SHIFT                           8  /* ADCVU */
#define WM8903_ADCVU_WIDTH                           1  /* ADCVU */
#define WM8903_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8903_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8903_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W38 (0x26) - ADC Digitaw 0
 */
#define WM8903_ADC_HPF_CUT_MASK                 0x0060  /* ADC_HPF_CUT - [6:5] */
#define WM8903_ADC_HPF_CUT_SHIFT                     5  /* ADC_HPF_CUT - [6:5] */
#define WM8903_ADC_HPF_CUT_WIDTH                     2  /* ADC_HPF_CUT - [6:5] */
#define WM8903_ADC_HPF_ENA                      0x0010  /* ADC_HPF_ENA */
#define WM8903_ADC_HPF_ENA_MASK                 0x0010  /* ADC_HPF_ENA */
#define WM8903_ADC_HPF_ENA_SHIFT                     4  /* ADC_HPF_ENA */
#define WM8903_ADC_HPF_ENA_WIDTH                     1  /* ADC_HPF_ENA */
#define WM8903_ADCW_DATINV                      0x0002  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV_MASK                 0x0002  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV_SHIFT                     1  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV_WIDTH                     1  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV                      0x0001  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV_MASK                 0x0001  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV_SHIFT                     0  /* ADCW_DATINV */
#define WM8903_ADCW_DATINV_WIDTH                     1  /* ADCW_DATINV */

/*
 * W39 (0x27) - Digitaw Micwophone 0
 */
#define WM8903_DIGMIC_MODE_SEW                  0x0100  /* DIGMIC_MODE_SEW */
#define WM8903_DIGMIC_MODE_SEW_MASK             0x0100  /* DIGMIC_MODE_SEW */
#define WM8903_DIGMIC_MODE_SEW_SHIFT                 8  /* DIGMIC_MODE_SEW */
#define WM8903_DIGMIC_MODE_SEW_WIDTH                 1  /* DIGMIC_MODE_SEW */
#define WM8903_DIGMIC_CWK_SEW_W_MASK            0x00C0  /* DIGMIC_CWK_SEW_W - [7:6] */
#define WM8903_DIGMIC_CWK_SEW_W_SHIFT                6  /* DIGMIC_CWK_SEW_W - [7:6] */
#define WM8903_DIGMIC_CWK_SEW_W_WIDTH                2  /* DIGMIC_CWK_SEW_W - [7:6] */
#define WM8903_DIGMIC_CWK_SEW_W_MASK            0x0030  /* DIGMIC_CWK_SEW_W - [5:4] */
#define WM8903_DIGMIC_CWK_SEW_W_SHIFT                4  /* DIGMIC_CWK_SEW_W - [5:4] */
#define WM8903_DIGMIC_CWK_SEW_W_WIDTH                2  /* DIGMIC_CWK_SEW_W - [5:4] */
#define WM8903_DIGMIC_CWK_SEW_WT_MASK           0x000C  /* DIGMIC_CWK_SEW_WT - [3:2] */
#define WM8903_DIGMIC_CWK_SEW_WT_SHIFT               2  /* DIGMIC_CWK_SEW_WT - [3:2] */
#define WM8903_DIGMIC_CWK_SEW_WT_WIDTH               2  /* DIGMIC_CWK_SEW_WT - [3:2] */
#define WM8903_DIGMIC_CWK_SEW_MASK              0x0003  /* DIGMIC_CWK_SEW - [1:0] */
#define WM8903_DIGMIC_CWK_SEW_SHIFT                  0  /* DIGMIC_CWK_SEW - [1:0] */
#define WM8903_DIGMIC_CWK_SEW_WIDTH                  2  /* DIGMIC_CWK_SEW - [1:0] */

/*
 * W40 (0x28) - DWC 0
 */
#define WM8903_DWC_ENA                          0x8000  /* DWC_ENA */
#define WM8903_DWC_ENA_MASK                     0x8000  /* DWC_ENA */
#define WM8903_DWC_ENA_SHIFT                        15  /* DWC_ENA */
#define WM8903_DWC_ENA_WIDTH                         1  /* DWC_ENA */
#define WM8903_DWC_THWESH_HYST_MASK             0x1800  /* DWC_THWESH_HYST - [12:11] */
#define WM8903_DWC_THWESH_HYST_SHIFT                11  /* DWC_THWESH_HYST - [12:11] */
#define WM8903_DWC_THWESH_HYST_WIDTH                 2  /* DWC_THWESH_HYST - [12:11] */
#define WM8903_DWC_STAWTUP_GAIN_MASK            0x07C0  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM8903_DWC_STAWTUP_GAIN_SHIFT                6  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM8903_DWC_STAWTUP_GAIN_WIDTH                5  /* DWC_STAWTUP_GAIN - [10:6] */
#define WM8903_DWC_FF_DEWAY                     0x0020  /* DWC_FF_DEWAY */
#define WM8903_DWC_FF_DEWAY_MASK                0x0020  /* DWC_FF_DEWAY */
#define WM8903_DWC_FF_DEWAY_SHIFT                    5  /* DWC_FF_DEWAY */
#define WM8903_DWC_FF_DEWAY_WIDTH                    1  /* DWC_FF_DEWAY */
#define WM8903_DWC_SMOOTH_ENA                   0x0008  /* DWC_SMOOTH_ENA */
#define WM8903_DWC_SMOOTH_ENA_MASK              0x0008  /* DWC_SMOOTH_ENA */
#define WM8903_DWC_SMOOTH_ENA_SHIFT                  3  /* DWC_SMOOTH_ENA */
#define WM8903_DWC_SMOOTH_ENA_WIDTH                  1  /* DWC_SMOOTH_ENA */
#define WM8903_DWC_QW_ENA                       0x0004  /* DWC_QW_ENA */
#define WM8903_DWC_QW_ENA_MASK                  0x0004  /* DWC_QW_ENA */
#define WM8903_DWC_QW_ENA_SHIFT                      2  /* DWC_QW_ENA */
#define WM8903_DWC_QW_ENA_WIDTH                      1  /* DWC_QW_ENA */
#define WM8903_DWC_ANTICWIP_ENA                 0x0002  /* DWC_ANTICWIP_ENA */
#define WM8903_DWC_ANTICWIP_ENA_MASK            0x0002  /* DWC_ANTICWIP_ENA */
#define WM8903_DWC_ANTICWIP_ENA_SHIFT                1  /* DWC_ANTICWIP_ENA */
#define WM8903_DWC_ANTICWIP_ENA_WIDTH                1  /* DWC_ANTICWIP_ENA */
#define WM8903_DWC_HYST_ENA                     0x0001  /* DWC_HYST_ENA */
#define WM8903_DWC_HYST_ENA_MASK                0x0001  /* DWC_HYST_ENA */
#define WM8903_DWC_HYST_ENA_SHIFT                    0  /* DWC_HYST_ENA */
#define WM8903_DWC_HYST_ENA_WIDTH                    1  /* DWC_HYST_ENA */

/*
 * W41 (0x29) - DWC 1
 */
#define WM8903_DWC_ATTACK_WATE_MASK             0xF000  /* DWC_ATTACK_WATE - [15:12] */
#define WM8903_DWC_ATTACK_WATE_SHIFT                12  /* DWC_ATTACK_WATE - [15:12] */
#define WM8903_DWC_ATTACK_WATE_WIDTH                 4  /* DWC_ATTACK_WATE - [15:12] */
#define WM8903_DWC_DECAY_WATE_MASK              0x0F00  /* DWC_DECAY_WATE - [11:8] */
#define WM8903_DWC_DECAY_WATE_SHIFT                  8  /* DWC_DECAY_WATE - [11:8] */
#define WM8903_DWC_DECAY_WATE_WIDTH                  4  /* DWC_DECAY_WATE - [11:8] */
#define WM8903_DWC_THWESH_QW_MASK               0x00C0  /* DWC_THWESH_QW - [7:6] */
#define WM8903_DWC_THWESH_QW_SHIFT                   6  /* DWC_THWESH_QW - [7:6] */
#define WM8903_DWC_THWESH_QW_WIDTH                   2  /* DWC_THWESH_QW - [7:6] */
#define WM8903_DWC_WATE_QW_MASK                 0x0030  /* DWC_WATE_QW - [5:4] */
#define WM8903_DWC_WATE_QW_SHIFT                     4  /* DWC_WATE_QW - [5:4] */
#define WM8903_DWC_WATE_QW_WIDTH                     2  /* DWC_WATE_QW - [5:4] */
#define WM8903_DWC_MINGAIN_MASK                 0x000C  /* DWC_MINGAIN - [3:2] */
#define WM8903_DWC_MINGAIN_SHIFT                     2  /* DWC_MINGAIN - [3:2] */
#define WM8903_DWC_MINGAIN_WIDTH                     2  /* DWC_MINGAIN - [3:2] */
#define WM8903_DWC_MAXGAIN_MASK                 0x0003  /* DWC_MAXGAIN - [1:0] */
#define WM8903_DWC_MAXGAIN_SHIFT                     0  /* DWC_MAXGAIN - [1:0] */
#define WM8903_DWC_MAXGAIN_WIDTH                     2  /* DWC_MAXGAIN - [1:0] */

/*
 * W42 (0x2A) - DWC 2
 */
#define WM8903_DWC_W0_SWOPE_COMP_MASK           0x0038  /* DWC_W0_SWOPE_COMP - [5:3] */
#define WM8903_DWC_W0_SWOPE_COMP_SHIFT               3  /* DWC_W0_SWOPE_COMP - [5:3] */
#define WM8903_DWC_W0_SWOPE_COMP_WIDTH               3  /* DWC_W0_SWOPE_COMP - [5:3] */
#define WM8903_DWC_W1_SWOPE_COMP_MASK           0x0007  /* DWC_W1_SWOPE_COMP - [2:0] */
#define WM8903_DWC_W1_SWOPE_COMP_SHIFT               0  /* DWC_W1_SWOPE_COMP - [2:0] */
#define WM8903_DWC_W1_SWOPE_COMP_WIDTH               3  /* DWC_W1_SWOPE_COMP - [2:0] */

/*
 * W43 (0x2B) - DWC 3
 */
#define WM8903_DWC_THWESH_COMP_MASK             0x07E0  /* DWC_THWESH_COMP - [10:5] */
#define WM8903_DWC_THWESH_COMP_SHIFT                 5  /* DWC_THWESH_COMP - [10:5] */
#define WM8903_DWC_THWESH_COMP_WIDTH                 6  /* DWC_THWESH_COMP - [10:5] */
#define WM8903_DWC_AMP_COMP_MASK                0x001F  /* DWC_AMP_COMP - [4:0] */
#define WM8903_DWC_AMP_COMP_SHIFT                    0  /* DWC_AMP_COMP - [4:0] */
#define WM8903_DWC_AMP_COMP_WIDTH                    5  /* DWC_AMP_COMP - [4:0] */

/*
 * W44 (0x2C) - Anawogue Weft Input 0
 */
#define WM8903_WINMUTE                          0x0080  /* WINMUTE */
#define WM8903_WINMUTE_MASK                     0x0080  /* WINMUTE */
#define WM8903_WINMUTE_SHIFT                         7  /* WINMUTE */
#define WM8903_WINMUTE_WIDTH                         1  /* WINMUTE */
#define WM8903_WIN_VOW_MASK                     0x001F  /* WIN_VOW - [4:0] */
#define WM8903_WIN_VOW_SHIFT                         0  /* WIN_VOW - [4:0] */
#define WM8903_WIN_VOW_WIDTH                         5  /* WIN_VOW - [4:0] */

/*
 * W45 (0x2D) - Anawogue Wight Input 0
 */
#define WM8903_WINMUTE                          0x0080  /* WINMUTE */
#define WM8903_WINMUTE_MASK                     0x0080  /* WINMUTE */
#define WM8903_WINMUTE_SHIFT                         7  /* WINMUTE */
#define WM8903_WINMUTE_WIDTH                         1  /* WINMUTE */
#define WM8903_WIN_VOW_MASK                     0x001F  /* WIN_VOW - [4:0] */
#define WM8903_WIN_VOW_SHIFT                         0  /* WIN_VOW - [4:0] */
#define WM8903_WIN_VOW_WIDTH                         5  /* WIN_VOW - [4:0] */

/*
 * W46 (0x2E) - Anawogue Weft Input 1
 */
#define WM8903_INW_CM_ENA                       0x0040  /* INW_CM_ENA */
#define WM8903_INW_CM_ENA_MASK                  0x0040  /* INW_CM_ENA */
#define WM8903_INW_CM_ENA_SHIFT                      6  /* INW_CM_ENA */
#define WM8903_INW_CM_ENA_WIDTH                      1  /* INW_CM_ENA */
#define WM8903_W_IP_SEW_N_MASK                  0x0030  /* W_IP_SEW_N - [5:4] */
#define WM8903_W_IP_SEW_N_SHIFT                      4  /* W_IP_SEW_N - [5:4] */
#define WM8903_W_IP_SEW_N_WIDTH                      2  /* W_IP_SEW_N - [5:4] */
#define WM8903_W_IP_SEW_P_MASK                  0x000C  /* W_IP_SEW_P - [3:2] */
#define WM8903_W_IP_SEW_P_SHIFT                      2  /* W_IP_SEW_P - [3:2] */
#define WM8903_W_IP_SEW_P_WIDTH                      2  /* W_IP_SEW_P - [3:2] */
#define WM8903_W_MODE_MASK                      0x0003  /* W_MODE - [1:0] */
#define WM8903_W_MODE_SHIFT                          0  /* W_MODE - [1:0] */
#define WM8903_W_MODE_WIDTH                          2  /* W_MODE - [1:0] */

/*
 * W47 (0x2F) - Anawogue Wight Input 1
 */
#define WM8903_INW_CM_ENA                       0x0040  /* INW_CM_ENA */
#define WM8903_INW_CM_ENA_MASK                  0x0040  /* INW_CM_ENA */
#define WM8903_INW_CM_ENA_SHIFT                      6  /* INW_CM_ENA */
#define WM8903_INW_CM_ENA_WIDTH                      1  /* INW_CM_ENA */
#define WM8903_W_IP_SEW_N_MASK                  0x0030  /* W_IP_SEW_N - [5:4] */
#define WM8903_W_IP_SEW_N_SHIFT                      4  /* W_IP_SEW_N - [5:4] */
#define WM8903_W_IP_SEW_N_WIDTH                      2  /* W_IP_SEW_N - [5:4] */
#define WM8903_W_IP_SEW_P_MASK                  0x000C  /* W_IP_SEW_P - [3:2] */
#define WM8903_W_IP_SEW_P_SHIFT                      2  /* W_IP_SEW_P - [3:2] */
#define WM8903_W_IP_SEW_P_WIDTH                      2  /* W_IP_SEW_P - [3:2] */
#define WM8903_W_MODE_MASK                      0x0003  /* W_MODE - [1:0] */
#define WM8903_W_MODE_SHIFT                          0  /* W_MODE - [1:0] */
#define WM8903_W_MODE_WIDTH                          2  /* W_MODE - [1:0] */

/*
 * W50 (0x32) - Anawogue Weft Mix 0
 */
#define WM8903_DACW_TO_MIXOUTW                  0x0008  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_MASK             0x0008  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_SHIFT                 3  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_WIDTH                 1  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW                  0x0004  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_MASK             0x0004  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_SHIFT                 2  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_WIDTH                 1  /* DACW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW               0x0002  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_MASK          0x0002  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_SHIFT              1  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_WIDTH              1  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW               0x0001  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_MASK          0x0001  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_SHIFT              0  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_WIDTH              1  /* BYPASSW_TO_MIXOUTW */

/*
 * W51 (0x33) - Anawogue Wight Mix 0
 */
#define WM8903_DACW_TO_MIXOUTW                  0x0008  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_MASK             0x0008  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_SHIFT                 3  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_WIDTH                 1  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW                  0x0004  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_MASK             0x0004  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_SHIFT                 2  /* DACW_TO_MIXOUTW */
#define WM8903_DACW_TO_MIXOUTW_WIDTH                 1  /* DACW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW               0x0002  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_MASK          0x0002  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_SHIFT              1  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_WIDTH              1  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW               0x0001  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_MASK          0x0001  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_SHIFT              0  /* BYPASSW_TO_MIXOUTW */
#define WM8903_BYPASSW_TO_MIXOUTW_WIDTH              1  /* BYPASSW_TO_MIXOUTW */

/*
 * W52 (0x34) - Anawogue Spk Mix Weft 0
 */
#define WM8903_DACW_TO_MIXSPKW                  0x0008  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_MASK             0x0008  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_SHIFT                 3  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_WIDTH                 1  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW                  0x0004  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_MASK             0x0004  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_SHIFT                 2  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_WIDTH                 1  /* DACW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW               0x0002  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_MASK          0x0002  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_SHIFT              1  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_WIDTH              1  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW               0x0001  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_MASK          0x0001  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_SHIFT              0  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_WIDTH              1  /* BYPASSW_TO_MIXSPKW */

/*
 * W53 (0x35) - Anawogue Spk Mix Weft 1
 */
#define WM8903_DACW_MIXSPKW_VOW                 0x0008  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_MASK            0x0008  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_SHIFT                3  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_WIDTH                1  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW                 0x0004  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_MASK            0x0004  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_SHIFT                2  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_WIDTH                1  /* DACW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW              0x0002  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_MASK         0x0002  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_SHIFT             1  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_WIDTH             1  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW              0x0001  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_MASK         0x0001  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_SHIFT             0  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_WIDTH             1  /* BYPASSW_MIXSPKW_VOW */

/*
 * W54 (0x36) - Anawogue Spk Mix Wight 0
 */
#define WM8903_DACW_TO_MIXSPKW                  0x0008  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_MASK             0x0008  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_SHIFT                 3  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_WIDTH                 1  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW                  0x0004  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_MASK             0x0004  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_SHIFT                 2  /* DACW_TO_MIXSPKW */
#define WM8903_DACW_TO_MIXSPKW_WIDTH                 1  /* DACW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW               0x0002  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_MASK          0x0002  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_SHIFT              1  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_WIDTH              1  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW               0x0001  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_MASK          0x0001  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_SHIFT              0  /* BYPASSW_TO_MIXSPKW */
#define WM8903_BYPASSW_TO_MIXSPKW_WIDTH              1  /* BYPASSW_TO_MIXSPKW */

/*
 * W55 (0x37) - Anawogue Spk Mix Wight 1
 */
#define WM8903_DACW_MIXSPKW_VOW                 0x0008  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_MASK            0x0008  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_SHIFT                3  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_WIDTH                1  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW                 0x0004  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_MASK            0x0004  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_SHIFT                2  /* DACW_MIXSPKW_VOW */
#define WM8903_DACW_MIXSPKW_VOW_WIDTH                1  /* DACW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW              0x0002  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_MASK         0x0002  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_SHIFT             1  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_WIDTH             1  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW              0x0001  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_MASK         0x0001  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_SHIFT             0  /* BYPASSW_MIXSPKW_VOW */
#define WM8903_BYPASSW_MIXSPKW_VOW_WIDTH             1  /* BYPASSW_MIXSPKW_VOW */

/*
 * W57 (0x39) - Anawogue OUT1 Weft
 */
#define WM8903_HPW_MUTE                         0x0100  /* HPW_MUTE */
#define WM8903_HPW_MUTE_MASK                    0x0100  /* HPW_MUTE */
#define WM8903_HPW_MUTE_SHIFT                        8  /* HPW_MUTE */
#define WM8903_HPW_MUTE_WIDTH                        1  /* HPW_MUTE */
#define WM8903_HPOUTVU                          0x0080  /* HPOUTVU */
#define WM8903_HPOUTVU_MASK                     0x0080  /* HPOUTVU */
#define WM8903_HPOUTVU_SHIFT                         7  /* HPOUTVU */
#define WM8903_HPOUTVU_WIDTH                         1  /* HPOUTVU */
#define WM8903_HPOUTWZC                         0x0040  /* HPOUTWZC */
#define WM8903_HPOUTWZC_MASK                    0x0040  /* HPOUTWZC */
#define WM8903_HPOUTWZC_SHIFT                        6  /* HPOUTWZC */
#define WM8903_HPOUTWZC_WIDTH                        1  /* HPOUTWZC */
#define WM8903_HPOUTW_VOW_MASK                  0x003F  /* HPOUTW_VOW - [5:0] */
#define WM8903_HPOUTW_VOW_SHIFT                      0  /* HPOUTW_VOW - [5:0] */
#define WM8903_HPOUTW_VOW_WIDTH                      6  /* HPOUTW_VOW - [5:0] */

/*
 * W58 (0x3A) - Anawogue OUT1 Wight
 */
#define WM8903_HPW_MUTE                         0x0100  /* HPW_MUTE */
#define WM8903_HPW_MUTE_MASK                    0x0100  /* HPW_MUTE */
#define WM8903_HPW_MUTE_SHIFT                        8  /* HPW_MUTE */
#define WM8903_HPW_MUTE_WIDTH                        1  /* HPW_MUTE */
#define WM8903_HPOUTVU                          0x0080  /* HPOUTVU */
#define WM8903_HPOUTVU_MASK                     0x0080  /* HPOUTVU */
#define WM8903_HPOUTVU_SHIFT                         7  /* HPOUTVU */
#define WM8903_HPOUTVU_WIDTH                         1  /* HPOUTVU */
#define WM8903_HPOUTWZC                         0x0040  /* HPOUTWZC */
#define WM8903_HPOUTWZC_MASK                    0x0040  /* HPOUTWZC */
#define WM8903_HPOUTWZC_SHIFT                        6  /* HPOUTWZC */
#define WM8903_HPOUTWZC_WIDTH                        1  /* HPOUTWZC */
#define WM8903_HPOUTW_VOW_MASK                  0x003F  /* HPOUTW_VOW - [5:0] */
#define WM8903_HPOUTW_VOW_SHIFT                      0  /* HPOUTW_VOW - [5:0] */
#define WM8903_HPOUTW_VOW_WIDTH                      6  /* HPOUTW_VOW - [5:0] */

/*
 * W59 (0x3B) - Anawogue OUT2 Weft
 */
#define WM8903_WINEOUTW_MUTE                    0x0100  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTW_MUTE_MASK               0x0100  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTW_MUTE_SHIFT                   8  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTW_MUTE_WIDTH                   1  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTVU                        0x0080  /* WINEOUTVU */
#define WM8903_WINEOUTVU_MASK                   0x0080  /* WINEOUTVU */
#define WM8903_WINEOUTVU_SHIFT                       7  /* WINEOUTVU */
#define WM8903_WINEOUTVU_WIDTH                       1  /* WINEOUTVU */
#define WM8903_WINEOUTWZC                       0x0040  /* WINEOUTWZC */
#define WM8903_WINEOUTWZC_MASK                  0x0040  /* WINEOUTWZC */
#define WM8903_WINEOUTWZC_SHIFT                      6  /* WINEOUTWZC */
#define WM8903_WINEOUTWZC_WIDTH                      1  /* WINEOUTWZC */
#define WM8903_WINEOUTW_VOW_MASK                0x003F  /* WINEOUTW_VOW - [5:0] */
#define WM8903_WINEOUTW_VOW_SHIFT                    0  /* WINEOUTW_VOW - [5:0] */
#define WM8903_WINEOUTW_VOW_WIDTH                    6  /* WINEOUTW_VOW - [5:0] */

/*
 * W60 (0x3C) - Anawogue OUT2 Wight
 */
#define WM8903_WINEOUTW_MUTE                    0x0100  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTW_MUTE_MASK               0x0100  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTW_MUTE_SHIFT                   8  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTW_MUTE_WIDTH                   1  /* WINEOUTW_MUTE */
#define WM8903_WINEOUTVU                        0x0080  /* WINEOUTVU */
#define WM8903_WINEOUTVU_MASK                   0x0080  /* WINEOUTVU */
#define WM8903_WINEOUTVU_SHIFT                       7  /* WINEOUTVU */
#define WM8903_WINEOUTVU_WIDTH                       1  /* WINEOUTVU */
#define WM8903_WINEOUTWZC                       0x0040  /* WINEOUTWZC */
#define WM8903_WINEOUTWZC_MASK                  0x0040  /* WINEOUTWZC */
#define WM8903_WINEOUTWZC_SHIFT                      6  /* WINEOUTWZC */
#define WM8903_WINEOUTWZC_WIDTH                      1  /* WINEOUTWZC */
#define WM8903_WINEOUTW_VOW_MASK                0x003F  /* WINEOUTW_VOW - [5:0] */
#define WM8903_WINEOUTW_VOW_SHIFT                    0  /* WINEOUTW_VOW - [5:0] */
#define WM8903_WINEOUTW_VOW_WIDTH                    6  /* WINEOUTW_VOW - [5:0] */

/*
 * W62 (0x3E) - Anawogue OUT3 Weft
 */
#define WM8903_SPKW_MUTE                        0x0100  /* SPKW_MUTE */
#define WM8903_SPKW_MUTE_MASK                   0x0100  /* SPKW_MUTE */
#define WM8903_SPKW_MUTE_SHIFT                       8  /* SPKW_MUTE */
#define WM8903_SPKW_MUTE_WIDTH                       1  /* SPKW_MUTE */
#define WM8903_SPKVU                            0x0080  /* SPKVU */
#define WM8903_SPKVU_MASK                       0x0080  /* SPKVU */
#define WM8903_SPKVU_SHIFT                           7  /* SPKVU */
#define WM8903_SPKVU_WIDTH                           1  /* SPKVU */
#define WM8903_SPKWZC                           0x0040  /* SPKWZC */
#define WM8903_SPKWZC_MASK                      0x0040  /* SPKWZC */
#define WM8903_SPKWZC_SHIFT                          6  /* SPKWZC */
#define WM8903_SPKWZC_WIDTH                          1  /* SPKWZC */
#define WM8903_SPKW_VOW_MASK                    0x003F  /* SPKW_VOW - [5:0] */
#define WM8903_SPKW_VOW_SHIFT                        0  /* SPKW_VOW - [5:0] */
#define WM8903_SPKW_VOW_WIDTH                        6  /* SPKW_VOW - [5:0] */

/*
 * W63 (0x3F) - Anawogue OUT3 Wight
 */
#define WM8903_SPKW_MUTE                        0x0100  /* SPKW_MUTE */
#define WM8903_SPKW_MUTE_MASK                   0x0100  /* SPKW_MUTE */
#define WM8903_SPKW_MUTE_SHIFT                       8  /* SPKW_MUTE */
#define WM8903_SPKW_MUTE_WIDTH                       1  /* SPKW_MUTE */
#define WM8903_SPKVU                            0x0080  /* SPKVU */
#define WM8903_SPKVU_MASK                       0x0080  /* SPKVU */
#define WM8903_SPKVU_SHIFT                           7  /* SPKVU */
#define WM8903_SPKVU_WIDTH                           1  /* SPKVU */
#define WM8903_SPKWZC                           0x0040  /* SPKWZC */
#define WM8903_SPKWZC_MASK                      0x0040  /* SPKWZC */
#define WM8903_SPKWZC_SHIFT                          6  /* SPKWZC */
#define WM8903_SPKWZC_WIDTH                          1  /* SPKWZC */
#define WM8903_SPKW_VOW_MASK                    0x003F  /* SPKW_VOW - [5:0] */
#define WM8903_SPKW_VOW_SHIFT                        0  /* SPKW_VOW - [5:0] */
#define WM8903_SPKW_VOW_WIDTH                        6  /* SPKW_VOW - [5:0] */

/*
 * W65 (0x41) - Anawogue SPK Output Contwow 0
 */
#define WM8903_SPK_DISCHAWGE                    0x0002  /* SPK_DISCHAWGE */
#define WM8903_SPK_DISCHAWGE_MASK               0x0002  /* SPK_DISCHAWGE */
#define WM8903_SPK_DISCHAWGE_SHIFT                   1  /* SPK_DISCHAWGE */
#define WM8903_SPK_DISCHAWGE_WIDTH                   1  /* SPK_DISCHAWGE */
#define WM8903_VWOI                             0x0001  /* VWOI */
#define WM8903_VWOI_MASK                        0x0001  /* VWOI */
#define WM8903_VWOI_SHIFT                            0  /* VWOI */
#define WM8903_VWOI_WIDTH                            1  /* VWOI */

/*
 * W67 (0x43) - DC Sewvo 0
 */
#define WM8903_DCS_MASTEW_ENA                   0x0010  /* DCS_MASTEW_ENA */
#define WM8903_DCS_MASTEW_ENA_MASK              0x0010  /* DCS_MASTEW_ENA */
#define WM8903_DCS_MASTEW_ENA_SHIFT                  4  /* DCS_MASTEW_ENA */
#define WM8903_DCS_MASTEW_ENA_WIDTH                  1  /* DCS_MASTEW_ENA */
#define WM8903_DCS_ENA_MASK                     0x000F  /* DCS_ENA - [3:0] */
#define WM8903_DCS_ENA_SHIFT                         0  /* DCS_ENA - [3:0] */
#define WM8903_DCS_ENA_WIDTH                         4  /* DCS_ENA - [3:0] */

/*
 * W69 (0x45) - DC Sewvo 2
 */
#define WM8903_DCS_MODE_MASK                    0x0003  /* DCS_MODE - [1:0] */
#define WM8903_DCS_MODE_SHIFT                        0  /* DCS_MODE - [1:0] */
#define WM8903_DCS_MODE_WIDTH                        2  /* DCS_MODE - [1:0] */

/*
 * W90 (0x5A) - Anawogue HP 0
 */
#define WM8903_HPW_WMV_SHOWT                    0x0080  /* HPW_WMV_SHOWT */
#define WM8903_HPW_WMV_SHOWT_MASK               0x0080  /* HPW_WMV_SHOWT */
#define WM8903_HPW_WMV_SHOWT_SHIFT                   7  /* HPW_WMV_SHOWT */
#define WM8903_HPW_WMV_SHOWT_WIDTH                   1  /* HPW_WMV_SHOWT */
#define WM8903_HPW_ENA_OUTP                     0x0040  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_OUTP_MASK                0x0040  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_OUTP_SHIFT                    6  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_OUTP_WIDTH                    1  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_DWY                      0x0020  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA_DWY_MASK                 0x0020  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA_DWY_SHIFT                     5  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA_DWY_WIDTH                     1  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA                          0x0010  /* HPW_ENA */
#define WM8903_HPW_ENA_MASK                     0x0010  /* HPW_ENA */
#define WM8903_HPW_ENA_SHIFT                         4  /* HPW_ENA */
#define WM8903_HPW_ENA_WIDTH                         1  /* HPW_ENA */
#define WM8903_HPW_WMV_SHOWT                    0x0008  /* HPW_WMV_SHOWT */
#define WM8903_HPW_WMV_SHOWT_MASK               0x0008  /* HPW_WMV_SHOWT */
#define WM8903_HPW_WMV_SHOWT_SHIFT                   3  /* HPW_WMV_SHOWT */
#define WM8903_HPW_WMV_SHOWT_WIDTH                   1  /* HPW_WMV_SHOWT */
#define WM8903_HPW_ENA_OUTP                     0x0004  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_OUTP_MASK                0x0004  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_OUTP_SHIFT                    2  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_OUTP_WIDTH                    1  /* HPW_ENA_OUTP */
#define WM8903_HPW_ENA_DWY                      0x0002  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA_DWY_MASK                 0x0002  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA_DWY_SHIFT                     1  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA_DWY_WIDTH                     1  /* HPW_ENA_DWY */
#define WM8903_HPW_ENA                          0x0001  /* HPW_ENA */
#define WM8903_HPW_ENA_MASK                     0x0001  /* HPW_ENA */
#define WM8903_HPW_ENA_SHIFT                         0  /* HPW_ENA */
#define WM8903_HPW_ENA_WIDTH                         1  /* HPW_ENA */

/*
 * W94 (0x5E) - Anawogue Wineout 0
 */
#define WM8903_WINEOUTW_WMV_SHOWT               0x0080  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_WMV_SHOWT_MASK          0x0080  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_WMV_SHOWT_SHIFT              7  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_WMV_SHOWT_WIDTH              1  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_ENA_OUTP                0x0040  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_OUTP_MASK           0x0040  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_OUTP_SHIFT               6  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_OUTP_WIDTH               1  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_DWY                 0x0020  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA_DWY_MASK            0x0020  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA_DWY_SHIFT                5  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA_DWY_WIDTH                1  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA                     0x0010  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_ENA_MASK                0x0010  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_ENA_SHIFT                    4  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_ENA_WIDTH                    1  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_WMV_SHOWT               0x0008  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_WMV_SHOWT_MASK          0x0008  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_WMV_SHOWT_SHIFT              3  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_WMV_SHOWT_WIDTH              1  /* WINEOUTW_WMV_SHOWT */
#define WM8903_WINEOUTW_ENA_OUTP                0x0004  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_OUTP_MASK           0x0004  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_OUTP_SHIFT               2  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_OUTP_WIDTH               1  /* WINEOUTW_ENA_OUTP */
#define WM8903_WINEOUTW_ENA_DWY                 0x0002  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA_DWY_MASK            0x0002  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA_DWY_SHIFT                1  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA_DWY_WIDTH                1  /* WINEOUTW_ENA_DWY */
#define WM8903_WINEOUTW_ENA                     0x0001  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_ENA_MASK                0x0001  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_ENA_SHIFT                    0  /* WINEOUTW_ENA */
#define WM8903_WINEOUTW_ENA_WIDTH                    1  /* WINEOUTW_ENA */

/*
 * W98 (0x62) - Chawge Pump 0
 */
#define WM8903_CP_ENA                           0x0001  /* CP_ENA */
#define WM8903_CP_ENA_MASK                      0x0001  /* CP_ENA */
#define WM8903_CP_ENA_SHIFT                          0  /* CP_ENA */
#define WM8903_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * W104 (0x68) - Cwass W 0
 */
#define WM8903_CP_DYN_FWEQ                      0x0002  /* CP_DYN_FWEQ */
#define WM8903_CP_DYN_FWEQ_MASK                 0x0002  /* CP_DYN_FWEQ */
#define WM8903_CP_DYN_FWEQ_SHIFT                     1  /* CP_DYN_FWEQ */
#define WM8903_CP_DYN_FWEQ_WIDTH                     1  /* CP_DYN_FWEQ */
#define WM8903_CP_DYN_V                         0x0001  /* CP_DYN_V */
#define WM8903_CP_DYN_V_MASK                    0x0001  /* CP_DYN_V */
#define WM8903_CP_DYN_V_SHIFT                        0  /* CP_DYN_V */
#define WM8903_CP_DYN_V_WIDTH                        1  /* CP_DYN_V */

/*
 * W108 (0x6C) - Wwite Sequencew 0
 */
#define WM8903_WSEQ_ENA                         0x0100  /* WSEQ_ENA */
#define WM8903_WSEQ_ENA_MASK                    0x0100  /* WSEQ_ENA */
#define WM8903_WSEQ_ENA_SHIFT                        8  /* WSEQ_ENA */
#define WM8903_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#define WM8903_WSEQ_WWITE_INDEX_MASK            0x001F  /* WSEQ_WWITE_INDEX - [4:0] */
#define WM8903_WSEQ_WWITE_INDEX_SHIFT                0  /* WSEQ_WWITE_INDEX - [4:0] */
#define WM8903_WSEQ_WWITE_INDEX_WIDTH                5  /* WSEQ_WWITE_INDEX - [4:0] */

/*
 * W109 (0x6D) - Wwite Sequencew 1
 */
#define WM8903_WSEQ_DATA_WIDTH_MASK             0x7000  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8903_WSEQ_DATA_WIDTH_SHIFT                12  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8903_WSEQ_DATA_WIDTH_WIDTH                 3  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8903_WSEQ_DATA_STAWT_MASK             0x0F00  /* WSEQ_DATA_STAWT - [11:8] */
#define WM8903_WSEQ_DATA_STAWT_SHIFT                 8  /* WSEQ_DATA_STAWT - [11:8] */
#define WM8903_WSEQ_DATA_STAWT_WIDTH                 4  /* WSEQ_DATA_STAWT - [11:8] */
#define WM8903_WSEQ_ADDW_MASK                   0x00FF  /* WSEQ_ADDW - [7:0] */
#define WM8903_WSEQ_ADDW_SHIFT                       0  /* WSEQ_ADDW - [7:0] */
#define WM8903_WSEQ_ADDW_WIDTH                       8  /* WSEQ_ADDW - [7:0] */

/*
 * W110 (0x6E) - Wwite Sequencew 2
 */
#define WM8903_WSEQ_EOS                         0x4000  /* WSEQ_EOS */
#define WM8903_WSEQ_EOS_MASK                    0x4000  /* WSEQ_EOS */
#define WM8903_WSEQ_EOS_SHIFT                       14  /* WSEQ_EOS */
#define WM8903_WSEQ_EOS_WIDTH                        1  /* WSEQ_EOS */
#define WM8903_WSEQ_DEWAY_MASK                  0x0F00  /* WSEQ_DEWAY - [11:8] */
#define WM8903_WSEQ_DEWAY_SHIFT                      8  /* WSEQ_DEWAY - [11:8] */
#define WM8903_WSEQ_DEWAY_WIDTH                      4  /* WSEQ_DEWAY - [11:8] */
#define WM8903_WSEQ_DATA_MASK                   0x00FF  /* WSEQ_DATA - [7:0] */
#define WM8903_WSEQ_DATA_SHIFT                       0  /* WSEQ_DATA - [7:0] */
#define WM8903_WSEQ_DATA_WIDTH                       8  /* WSEQ_DATA - [7:0] */

/*
 * W111 (0x6F) - Wwite Sequencew 3
 */
#define WM8903_WSEQ_ABOWT                       0x0200  /* WSEQ_ABOWT */
#define WM8903_WSEQ_ABOWT_MASK                  0x0200  /* WSEQ_ABOWT */
#define WM8903_WSEQ_ABOWT_SHIFT                      9  /* WSEQ_ABOWT */
#define WM8903_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM8903_WSEQ_STAWT                       0x0100  /* WSEQ_STAWT */
#define WM8903_WSEQ_STAWT_MASK                  0x0100  /* WSEQ_STAWT */
#define WM8903_WSEQ_STAWT_SHIFT                      8  /* WSEQ_STAWT */
#define WM8903_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM8903_WSEQ_STAWT_INDEX_MASK            0x003F  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM8903_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM8903_WSEQ_STAWT_INDEX_WIDTH                6  /* WSEQ_STAWT_INDEX - [5:0] */

/*
 * W112 (0x70) - Wwite Sequencew 4
 */
#define WM8903_WSEQ_CUWWENT_INDEX_MASK          0x03F0  /* WSEQ_CUWWENT_INDEX - [9:4] */
#define WM8903_WSEQ_CUWWENT_INDEX_SHIFT              4  /* WSEQ_CUWWENT_INDEX - [9:4] */
#define WM8903_WSEQ_CUWWENT_INDEX_WIDTH              6  /* WSEQ_CUWWENT_INDEX - [9:4] */
#define WM8903_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#define WM8903_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#define WM8903_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#define WM8903_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * W114 (0x72) - Contwow Intewface
 */
#define WM8903_MASK_WWITE_ENA                   0x0001  /* MASK_WWITE_ENA */
#define WM8903_MASK_WWITE_ENA_MASK              0x0001  /* MASK_WWITE_ENA */
#define WM8903_MASK_WWITE_ENA_SHIFT                  0  /* MASK_WWITE_ENA */
#define WM8903_MASK_WWITE_ENA_WIDTH                  1  /* MASK_WWITE_ENA */

/*
 * W121 (0x79) - Intewwupt Status 1
 */
#define WM8903_MICSHWT_EINT                     0x8000  /* MICSHWT_EINT */
#define WM8903_MICSHWT_EINT_MASK                0x8000  /* MICSHWT_EINT */
#define WM8903_MICSHWT_EINT_SHIFT                   15  /* MICSHWT_EINT */
#define WM8903_MICSHWT_EINT_WIDTH                    1  /* MICSHWT_EINT */
#define WM8903_MICDET_EINT                      0x4000  /* MICDET_EINT */
#define WM8903_MICDET_EINT_MASK                 0x4000  /* MICDET_EINT */
#define WM8903_MICDET_EINT_SHIFT                    14  /* MICDET_EINT */
#define WM8903_MICDET_EINT_WIDTH                     1  /* MICDET_EINT */
#define WM8903_WSEQ_BUSY_EINT                   0x2000  /* WSEQ_BUSY_EINT */
#define WM8903_WSEQ_BUSY_EINT_MASK              0x2000  /* WSEQ_BUSY_EINT */
#define WM8903_WSEQ_BUSY_EINT_SHIFT                 13  /* WSEQ_BUSY_EINT */
#define WM8903_WSEQ_BUSY_EINT_WIDTH                  1  /* WSEQ_BUSY_EINT */
#define WM8903_GP5_EINT                         0x0010  /* GP5_EINT */
#define WM8903_GP5_EINT_MASK                    0x0010  /* GP5_EINT */
#define WM8903_GP5_EINT_SHIFT                        4  /* GP5_EINT */
#define WM8903_GP5_EINT_WIDTH                        1  /* GP5_EINT */
#define WM8903_GP4_EINT                         0x0008  /* GP4_EINT */
#define WM8903_GP4_EINT_MASK                    0x0008  /* GP4_EINT */
#define WM8903_GP4_EINT_SHIFT                        3  /* GP4_EINT */
#define WM8903_GP4_EINT_WIDTH                        1  /* GP4_EINT */
#define WM8903_GP3_EINT                         0x0004  /* GP3_EINT */
#define WM8903_GP3_EINT_MASK                    0x0004  /* GP3_EINT */
#define WM8903_GP3_EINT_SHIFT                        2  /* GP3_EINT */
#define WM8903_GP3_EINT_WIDTH                        1  /* GP3_EINT */
#define WM8903_GP2_EINT                         0x0002  /* GP2_EINT */
#define WM8903_GP2_EINT_MASK                    0x0002  /* GP2_EINT */
#define WM8903_GP2_EINT_SHIFT                        1  /* GP2_EINT */
#define WM8903_GP2_EINT_WIDTH                        1  /* GP2_EINT */
#define WM8903_GP1_EINT                         0x0001  /* GP1_EINT */
#define WM8903_GP1_EINT_MASK                    0x0001  /* GP1_EINT */
#define WM8903_GP1_EINT_SHIFT                        0  /* GP1_EINT */
#define WM8903_GP1_EINT_WIDTH                        1  /* GP1_EINT */

/*
 * W122 (0x7A) - Intewwupt Status 1 Mask
 */
#define WM8903_IM_MICSHWT_EINT                  0x8000  /* IM_MICSHWT_EINT */
#define WM8903_IM_MICSHWT_EINT_MASK             0x8000  /* IM_MICSHWT_EINT */
#define WM8903_IM_MICSHWT_EINT_SHIFT                15  /* IM_MICSHWT_EINT */
#define WM8903_IM_MICSHWT_EINT_WIDTH                 1  /* IM_MICSHWT_EINT */
#define WM8903_IM_MICDET_EINT                   0x4000  /* IM_MICDET_EINT */
#define WM8903_IM_MICDET_EINT_MASK              0x4000  /* IM_MICDET_EINT */
#define WM8903_IM_MICDET_EINT_SHIFT                 14  /* IM_MICDET_EINT */
#define WM8903_IM_MICDET_EINT_WIDTH                  1  /* IM_MICDET_EINT */
#define WM8903_IM_WSEQ_BUSY_EINT                0x2000  /* IM_WSEQ_BUSY_EINT */
#define WM8903_IM_WSEQ_BUSY_EINT_MASK           0x2000  /* IM_WSEQ_BUSY_EINT */
#define WM8903_IM_WSEQ_BUSY_EINT_SHIFT              13  /* IM_WSEQ_BUSY_EINT */
#define WM8903_IM_WSEQ_BUSY_EINT_WIDTH               1  /* IM_WSEQ_BUSY_EINT */
#define WM8903_IM_GP5_EINT                      0x0010  /* IM_GP5_EINT */
#define WM8903_IM_GP5_EINT_MASK                 0x0010  /* IM_GP5_EINT */
#define WM8903_IM_GP5_EINT_SHIFT                     4  /* IM_GP5_EINT */
#define WM8903_IM_GP5_EINT_WIDTH                     1  /* IM_GP5_EINT */
#define WM8903_IM_GP4_EINT                      0x0008  /* IM_GP4_EINT */
#define WM8903_IM_GP4_EINT_MASK                 0x0008  /* IM_GP4_EINT */
#define WM8903_IM_GP4_EINT_SHIFT                     3  /* IM_GP4_EINT */
#define WM8903_IM_GP4_EINT_WIDTH                     1  /* IM_GP4_EINT */
#define WM8903_IM_GP3_EINT                      0x0004  /* IM_GP3_EINT */
#define WM8903_IM_GP3_EINT_MASK                 0x0004  /* IM_GP3_EINT */
#define WM8903_IM_GP3_EINT_SHIFT                     2  /* IM_GP3_EINT */
#define WM8903_IM_GP3_EINT_WIDTH                     1  /* IM_GP3_EINT */
#define WM8903_IM_GP2_EINT                      0x0002  /* IM_GP2_EINT */
#define WM8903_IM_GP2_EINT_MASK                 0x0002  /* IM_GP2_EINT */
#define WM8903_IM_GP2_EINT_SHIFT                     1  /* IM_GP2_EINT */
#define WM8903_IM_GP2_EINT_WIDTH                     1  /* IM_GP2_EINT */
#define WM8903_IM_GP1_EINT                      0x0001  /* IM_GP1_EINT */
#define WM8903_IM_GP1_EINT_MASK                 0x0001  /* IM_GP1_EINT */
#define WM8903_IM_GP1_EINT_SHIFT                     0  /* IM_GP1_EINT */
#define WM8903_IM_GP1_EINT_WIDTH                     1  /* IM_GP1_EINT */

/*
 * W123 (0x7B) - Intewwupt Powawity 1
 */
#define WM8903_MICSHWT_INV                      0x8000  /* MICSHWT_INV */
#define WM8903_MICSHWT_INV_MASK                 0x8000  /* MICSHWT_INV */
#define WM8903_MICSHWT_INV_SHIFT                    15  /* MICSHWT_INV */
#define WM8903_MICSHWT_INV_WIDTH                     1  /* MICSHWT_INV */
#define WM8903_MICDET_INV                       0x4000  /* MICDET_INV */
#define WM8903_MICDET_INV_MASK                  0x4000  /* MICDET_INV */
#define WM8903_MICDET_INV_SHIFT                     14  /* MICDET_INV */
#define WM8903_MICDET_INV_WIDTH                      1  /* MICDET_INV */

/*
 * W126 (0x7E) - Intewwupt Contwow
 */
#define WM8903_IWQ_POW                          0x0001  /* IWQ_POW */
#define WM8903_IWQ_POW_MASK                     0x0001  /* IWQ_POW */
#define WM8903_IWQ_POW_SHIFT                         0  /* IWQ_POW */
#define WM8903_IWQ_POW_WIDTH                         1  /* IWQ_POW */

/*
 * W164 (0xA4) - Cwock Wate Test 4
 */
#define WM8903_ADC_DIG_MIC                      0x0200  /* ADC_DIG_MIC */
#define WM8903_ADC_DIG_MIC_MASK                 0x0200  /* ADC_DIG_MIC */
#define WM8903_ADC_DIG_MIC_SHIFT                     9  /* ADC_DIG_MIC */
#define WM8903_ADC_DIG_MIC_WIDTH                     1  /* ADC_DIG_MIC */

/*
 * W172 (0xAC) - Anawogue Output Bias 0
 */
#define WM8903_PGA_BIAS_MASK                    0x0070  /* PGA_BIAS - [6:4] */
#define WM8903_PGA_BIAS_SHIFT                        4  /* PGA_BIAS - [6:4] */
#define WM8903_PGA_BIAS_WIDTH                        3  /* PGA_BIAS - [6:4] */

#endif
