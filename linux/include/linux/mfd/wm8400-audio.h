/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8400 pwivate definitions fow audio
 *
 * Copywight 2008 Wowfson Micwoewectwonics pwc
 */

#ifndef __WINUX_MFD_WM8400_AUDIO_H
#define __WINUX_MFD_WM8400_AUDIO_H

#incwude <winux/mfd/wm8400-audio.h>

/*
 * W2 (0x02) - Powew Management (1)
 */
#define WM8400_CODEC_ENA                        0x8000  /* CODEC_ENA */
#define WM8400_CODEC_ENA_MASK                   0x8000  /* CODEC_ENA */
#define WM8400_CODEC_ENA_SHIFT                      15  /* CODEC_ENA */
#define WM8400_CODEC_ENA_WIDTH                       1  /* CODEC_ENA */
#define WM8400_SYSCWK_ENA                       0x4000  /* SYSCWK_ENA */
#define WM8400_SYSCWK_ENA_MASK                  0x4000  /* SYSCWK_ENA */
#define WM8400_SYSCWK_ENA_SHIFT                     14  /* SYSCWK_ENA */
#define WM8400_SYSCWK_ENA_WIDTH                      1  /* SYSCWK_ENA */
#define WM8400_SPK_MIX_ENA                      0x2000  /* SPK_MIX_ENA */
#define WM8400_SPK_MIX_ENA_MASK                 0x2000  /* SPK_MIX_ENA */
#define WM8400_SPK_MIX_ENA_SHIFT                    13  /* SPK_MIX_ENA */
#define WM8400_SPK_MIX_ENA_WIDTH                     1  /* SPK_MIX_ENA */
#define WM8400_SPK_ENA                          0x1000  /* SPK_ENA */
#define WM8400_SPK_ENA_MASK                     0x1000  /* SPK_ENA */
#define WM8400_SPK_ENA_SHIFT                        12  /* SPK_ENA */
#define WM8400_SPK_ENA_WIDTH                         1  /* SPK_ENA */
#define WM8400_OUT3_ENA                         0x0800  /* OUT3_ENA */
#define WM8400_OUT3_ENA_MASK                    0x0800  /* OUT3_ENA */
#define WM8400_OUT3_ENA_SHIFT                       11  /* OUT3_ENA */
#define WM8400_OUT3_ENA_WIDTH                        1  /* OUT3_ENA */
#define WM8400_OUT4_ENA                         0x0400  /* OUT4_ENA */
#define WM8400_OUT4_ENA_MASK                    0x0400  /* OUT4_ENA */
#define WM8400_OUT4_ENA_SHIFT                       10  /* OUT4_ENA */
#define WM8400_OUT4_ENA_WIDTH                        1  /* OUT4_ENA */
#define WM8400_WOUT_ENA                         0x0200  /* WOUT_ENA */
#define WM8400_WOUT_ENA_MASK                    0x0200  /* WOUT_ENA */
#define WM8400_WOUT_ENA_SHIFT                        9  /* WOUT_ENA */
#define WM8400_WOUT_ENA_WIDTH                        1  /* WOUT_ENA */
#define WM8400_WOUT_ENA                         0x0100  /* WOUT_ENA */
#define WM8400_WOUT_ENA_MASK                    0x0100  /* WOUT_ENA */
#define WM8400_WOUT_ENA_SHIFT                        8  /* WOUT_ENA */
#define WM8400_WOUT_ENA_WIDTH                        1  /* WOUT_ENA */
#define WM8400_MIC1BIAS_ENA                     0x0010  /* MIC1BIAS_ENA */
#define WM8400_MIC1BIAS_ENA_MASK                0x0010  /* MIC1BIAS_ENA */
#define WM8400_MIC1BIAS_ENA_SHIFT                    4  /* MIC1BIAS_ENA */
#define WM8400_MIC1BIAS_ENA_WIDTH                    1  /* MIC1BIAS_ENA */
#define WM8400_VMID_MODE_MASK                   0x0006  /* VMID_MODE - [2:1] */
#define WM8400_VMID_MODE_SHIFT                       1  /* VMID_MODE - [2:1] */
#define WM8400_VMID_MODE_WIDTH                       2  /* VMID_MODE - [2:1] */
#define WM8400_VWEF_ENA                         0x0001  /* VWEF_ENA */
#define WM8400_VWEF_ENA_MASK                    0x0001  /* VWEF_ENA */
#define WM8400_VWEF_ENA_SHIFT                        0  /* VWEF_ENA */
#define WM8400_VWEF_ENA_WIDTH                        1  /* VWEF_ENA */

/*
 * W3 (0x03) - Powew Management (2)
 */
#define WM8400_FWW_ENA                          0x8000  /* FWW_ENA */
#define WM8400_FWW_ENA_MASK                     0x8000  /* FWW_ENA */
#define WM8400_FWW_ENA_SHIFT                        15  /* FWW_ENA */
#define WM8400_FWW_ENA_WIDTH                         1  /* FWW_ENA */
#define WM8400_TSHUT_ENA                        0x4000  /* TSHUT_ENA */
#define WM8400_TSHUT_ENA_MASK                   0x4000  /* TSHUT_ENA */
#define WM8400_TSHUT_ENA_SHIFT                      14  /* TSHUT_ENA */
#define WM8400_TSHUT_ENA_WIDTH                       1  /* TSHUT_ENA */
#define WM8400_TSHUT_OPDIS                      0x2000  /* TSHUT_OPDIS */
#define WM8400_TSHUT_OPDIS_MASK                 0x2000  /* TSHUT_OPDIS */
#define WM8400_TSHUT_OPDIS_SHIFT                    13  /* TSHUT_OPDIS */
#define WM8400_TSHUT_OPDIS_WIDTH                     1  /* TSHUT_OPDIS */
#define WM8400_OPCWK_ENA                        0x0800  /* OPCWK_ENA */
#define WM8400_OPCWK_ENA_MASK                   0x0800  /* OPCWK_ENA */
#define WM8400_OPCWK_ENA_SHIFT                      11  /* OPCWK_ENA */
#define WM8400_OPCWK_ENA_WIDTH                       1  /* OPCWK_ENA */
#define WM8400_AINW_ENA                         0x0200  /* AINW_ENA */
#define WM8400_AINW_ENA_MASK                    0x0200  /* AINW_ENA */
#define WM8400_AINW_ENA_SHIFT                        9  /* AINW_ENA */
#define WM8400_AINW_ENA_WIDTH                        1  /* AINW_ENA */
#define WM8400_AINW_ENA                         0x0100  /* AINW_ENA */
#define WM8400_AINW_ENA_MASK                    0x0100  /* AINW_ENA */
#define WM8400_AINW_ENA_SHIFT                        8  /* AINW_ENA */
#define WM8400_AINW_ENA_WIDTH                        1  /* AINW_ENA */
#define WM8400_WIN34_ENA                        0x0080  /* WIN34_ENA */
#define WM8400_WIN34_ENA_MASK                   0x0080  /* WIN34_ENA */
#define WM8400_WIN34_ENA_SHIFT                       7  /* WIN34_ENA */
#define WM8400_WIN34_ENA_WIDTH                       1  /* WIN34_ENA */
#define WM8400_WIN12_ENA                        0x0040  /* WIN12_ENA */
#define WM8400_WIN12_ENA_MASK                   0x0040  /* WIN12_ENA */
#define WM8400_WIN12_ENA_SHIFT                       6  /* WIN12_ENA */
#define WM8400_WIN12_ENA_WIDTH                       1  /* WIN12_ENA */
#define WM8400_WIN34_ENA                        0x0020  /* WIN34_ENA */
#define WM8400_WIN34_ENA_MASK                   0x0020  /* WIN34_ENA */
#define WM8400_WIN34_ENA_SHIFT                       5  /* WIN34_ENA */
#define WM8400_WIN34_ENA_WIDTH                       1  /* WIN34_ENA */
#define WM8400_WIN12_ENA                        0x0010  /* WIN12_ENA */
#define WM8400_WIN12_ENA_MASK                   0x0010  /* WIN12_ENA */
#define WM8400_WIN12_ENA_SHIFT                       4  /* WIN12_ENA */
#define WM8400_WIN12_ENA_WIDTH                       1  /* WIN12_ENA */
#define WM8400_ADCW_ENA                         0x0002  /* ADCW_ENA */
#define WM8400_ADCW_ENA_MASK                    0x0002  /* ADCW_ENA */
#define WM8400_ADCW_ENA_SHIFT                        1  /* ADCW_ENA */
#define WM8400_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */
#define WM8400_ADCW_ENA                         0x0001  /* ADCW_ENA */
#define WM8400_ADCW_ENA_MASK                    0x0001  /* ADCW_ENA */
#define WM8400_ADCW_ENA_SHIFT                        0  /* ADCW_ENA */
#define WM8400_ADCW_ENA_WIDTH                        1  /* ADCW_ENA */

/*
 * W4 (0x04) - Powew Management (3)
 */
#define WM8400_WON_ENA                          0x2000  /* WON_ENA */
#define WM8400_WON_ENA_MASK                     0x2000  /* WON_ENA */
#define WM8400_WON_ENA_SHIFT                        13  /* WON_ENA */
#define WM8400_WON_ENA_WIDTH                         1  /* WON_ENA */
#define WM8400_WOP_ENA                          0x1000  /* WOP_ENA */
#define WM8400_WOP_ENA_MASK                     0x1000  /* WOP_ENA */
#define WM8400_WOP_ENA_SHIFT                        12  /* WOP_ENA */
#define WM8400_WOP_ENA_WIDTH                         1  /* WOP_ENA */
#define WM8400_WON_ENA                          0x0800  /* WON_ENA */
#define WM8400_WON_ENA_MASK                     0x0800  /* WON_ENA */
#define WM8400_WON_ENA_SHIFT                        11  /* WON_ENA */
#define WM8400_WON_ENA_WIDTH                         1  /* WON_ENA */
#define WM8400_WOP_ENA                          0x0400  /* WOP_ENA */
#define WM8400_WOP_ENA_MASK                     0x0400  /* WOP_ENA */
#define WM8400_WOP_ENA_SHIFT                        10  /* WOP_ENA */
#define WM8400_WOP_ENA_WIDTH                         1  /* WOP_ENA */
#define WM8400_WOPGA_ENA                        0x0080  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA_MASK                   0x0080  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA_SHIFT                       7  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA_WIDTH                       1  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA                        0x0040  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA_MASK                   0x0040  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA_SHIFT                       6  /* WOPGA_ENA */
#define WM8400_WOPGA_ENA_WIDTH                       1  /* WOPGA_ENA */
#define WM8400_WOMIX_ENA                        0x0020  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA_MASK                   0x0020  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA_SHIFT                       5  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA_WIDTH                       1  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA                        0x0010  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA_MASK                   0x0010  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA_SHIFT                       4  /* WOMIX_ENA */
#define WM8400_WOMIX_ENA_WIDTH                       1  /* WOMIX_ENA */
#define WM8400_DACW_ENA                         0x0002  /* DACW_ENA */
#define WM8400_DACW_ENA_MASK                    0x0002  /* DACW_ENA */
#define WM8400_DACW_ENA_SHIFT                        1  /* DACW_ENA */
#define WM8400_DACW_ENA_WIDTH                        1  /* DACW_ENA */
#define WM8400_DACW_ENA                         0x0001  /* DACW_ENA */
#define WM8400_DACW_ENA_MASK                    0x0001  /* DACW_ENA */
#define WM8400_DACW_ENA_SHIFT                        0  /* DACW_ENA */
#define WM8400_DACW_ENA_WIDTH                        1  /* DACW_ENA */

/*
 * W5 (0x05) - Audio Intewface (1)
 */
#define WM8400_AIFADCW_SWC                      0x8000  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC_MASK                 0x8000  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC_SHIFT                    15  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC_WIDTH                     1  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC                      0x4000  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC_MASK                 0x4000  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC_SHIFT                    14  /* AIFADCW_SWC */
#define WM8400_AIFADCW_SWC_WIDTH                     1  /* AIFADCW_SWC */
#define WM8400_AIFADC_TDM                       0x2000  /* AIFADC_TDM */
#define WM8400_AIFADC_TDM_MASK                  0x2000  /* AIFADC_TDM */
#define WM8400_AIFADC_TDM_SHIFT                     13  /* AIFADC_TDM */
#define WM8400_AIFADC_TDM_WIDTH                      1  /* AIFADC_TDM */
#define WM8400_AIFADC_TDM_CHAN                  0x1000  /* AIFADC_TDM_CHAN */
#define WM8400_AIFADC_TDM_CHAN_MASK             0x1000  /* AIFADC_TDM_CHAN */
#define WM8400_AIFADC_TDM_CHAN_SHIFT                12  /* AIFADC_TDM_CHAN */
#define WM8400_AIFADC_TDM_CHAN_WIDTH                 1  /* AIFADC_TDM_CHAN */
#define WM8400_AIF_BCWK_INV                     0x0100  /* AIF_BCWK_INV */
#define WM8400_AIF_BCWK_INV_MASK                0x0100  /* AIF_BCWK_INV */
#define WM8400_AIF_BCWK_INV_SHIFT                    8  /* AIF_BCWK_INV */
#define WM8400_AIF_BCWK_INV_WIDTH                    1  /* AIF_BCWK_INV */
#define WM8400_AIF_WWCWK_INV                    0x0080  /* AIF_WWCWK_INV */
#define WM8400_AIF_WWCWK_INV_MASK               0x0080  /* AIF_WWCWK_INV */
#define WM8400_AIF_WWCWK_INV_SHIFT                   7  /* AIF_WWCWK_INV */
#define WM8400_AIF_WWCWK_INV_WIDTH                   1  /* AIF_WWCWK_INV */
#define WM8400_AIF_WW_MASK                      0x0060  /* AIF_WW - [6:5] */
#define WM8400_AIF_WW_SHIFT                          5  /* AIF_WW - [6:5] */
#define WM8400_AIF_WW_WIDTH                          2  /* AIF_WW - [6:5] */
#define WM8400_AIF_WW_16BITS			(0 << 5)
#define WM8400_AIF_WW_20BITS			(1 << 5)
#define WM8400_AIF_WW_24BITS			(2 << 5)
#define WM8400_AIF_WW_32BITS			(3 << 5)
#define WM8400_AIF_FMT_MASK                     0x0018  /* AIF_FMT - [4:3] */
#define WM8400_AIF_FMT_SHIFT                         3  /* AIF_FMT - [4:3] */
#define WM8400_AIF_FMT_WIDTH                         2  /* AIF_FMT - [4:3] */
#define WM8400_AIF_FMT_WIGHTJ			(0 << 3)
#define WM8400_AIF_FMT_WEFTJ			(1 << 3)
#define WM8400_AIF_FMT_I2S			(2 << 3)
#define WM8400_AIF_FMT_DSP			(3 << 3)

/*
 * W6 (0x06) - Audio Intewface (2)
 */
#define WM8400_DACW_SWC                         0x8000  /* DACW_SWC */
#define WM8400_DACW_SWC_MASK                    0x8000  /* DACW_SWC */
#define WM8400_DACW_SWC_SHIFT                       15  /* DACW_SWC */
#define WM8400_DACW_SWC_WIDTH                        1  /* DACW_SWC */
#define WM8400_DACW_SWC                         0x4000  /* DACW_SWC */
#define WM8400_DACW_SWC_MASK                    0x4000  /* DACW_SWC */
#define WM8400_DACW_SWC_SHIFT                       14  /* DACW_SWC */
#define WM8400_DACW_SWC_WIDTH                        1  /* DACW_SWC */
#define WM8400_AIFDAC_TDM                       0x2000  /* AIFDAC_TDM */
#define WM8400_AIFDAC_TDM_MASK                  0x2000  /* AIFDAC_TDM */
#define WM8400_AIFDAC_TDM_SHIFT                     13  /* AIFDAC_TDM */
#define WM8400_AIFDAC_TDM_WIDTH                      1  /* AIFDAC_TDM */
#define WM8400_AIFDAC_TDM_CHAN                  0x1000  /* AIFDAC_TDM_CHAN */
#define WM8400_AIFDAC_TDM_CHAN_MASK             0x1000  /* AIFDAC_TDM_CHAN */
#define WM8400_AIFDAC_TDM_CHAN_SHIFT                12  /* AIFDAC_TDM_CHAN */
#define WM8400_AIFDAC_TDM_CHAN_WIDTH                 1  /* AIFDAC_TDM_CHAN */
#define WM8400_DAC_BOOST_MASK                   0x0C00  /* DAC_BOOST - [11:10] */
#define WM8400_DAC_BOOST_SHIFT                      10  /* DAC_BOOST - [11:10] */
#define WM8400_DAC_BOOST_WIDTH                       2  /* DAC_BOOST - [11:10] */
#define WM8400_DAC_COMP                         0x0010  /* DAC_COMP */
#define WM8400_DAC_COMP_MASK                    0x0010  /* DAC_COMP */
#define WM8400_DAC_COMP_SHIFT                        4  /* DAC_COMP */
#define WM8400_DAC_COMP_WIDTH                        1  /* DAC_COMP */
#define WM8400_DAC_COMPMODE                     0x0008  /* DAC_COMPMODE */
#define WM8400_DAC_COMPMODE_MASK                0x0008  /* DAC_COMPMODE */
#define WM8400_DAC_COMPMODE_SHIFT                    3  /* DAC_COMPMODE */
#define WM8400_DAC_COMPMODE_WIDTH                    1  /* DAC_COMPMODE */
#define WM8400_ADC_COMP                         0x0004  /* ADC_COMP */
#define WM8400_ADC_COMP_MASK                    0x0004  /* ADC_COMP */
#define WM8400_ADC_COMP_SHIFT                        2  /* ADC_COMP */
#define WM8400_ADC_COMP_WIDTH                        1  /* ADC_COMP */
#define WM8400_ADC_COMPMODE                     0x0002  /* ADC_COMPMODE */
#define WM8400_ADC_COMPMODE_MASK                0x0002  /* ADC_COMPMODE */
#define WM8400_ADC_COMPMODE_SHIFT                    1  /* ADC_COMPMODE */
#define WM8400_ADC_COMPMODE_WIDTH                    1  /* ADC_COMPMODE */
#define WM8400_WOOPBACK                         0x0001  /* WOOPBACK */
#define WM8400_WOOPBACK_MASK                    0x0001  /* WOOPBACK */
#define WM8400_WOOPBACK_SHIFT                        0  /* WOOPBACK */
#define WM8400_WOOPBACK_WIDTH                        1  /* WOOPBACK */

/*
 * W7 (0x07) - Cwocking (1)
 */
#define WM8400_TOCWK_WATE                       0x8000  /* TOCWK_WATE */
#define WM8400_TOCWK_WATE_MASK                  0x8000  /* TOCWK_WATE */
#define WM8400_TOCWK_WATE_SHIFT                     15  /* TOCWK_WATE */
#define WM8400_TOCWK_WATE_WIDTH                      1  /* TOCWK_WATE */
#define WM8400_TOCWK_ENA                        0x4000  /* TOCWK_ENA */
#define WM8400_TOCWK_ENA_MASK                   0x4000  /* TOCWK_ENA */
#define WM8400_TOCWK_ENA_SHIFT                      14  /* TOCWK_ENA */
#define WM8400_TOCWK_ENA_WIDTH                       1  /* TOCWK_ENA */
#define WM8400_OPCWKDIV_MASK                    0x1E00  /* OPCWKDIV - [12:9] */
#define WM8400_OPCWKDIV_SHIFT                        9  /* OPCWKDIV - [12:9] */
#define WM8400_OPCWKDIV_WIDTH                        4  /* OPCWKDIV - [12:9] */
#define WM8400_DCWKDIV_MASK                     0x01C0  /* DCWKDIV - [8:6] */
#define WM8400_DCWKDIV_SHIFT                         6  /* DCWKDIV - [8:6] */
#define WM8400_DCWKDIV_WIDTH                         3  /* DCWKDIV - [8:6] */
#define WM8400_BCWK_DIV_MASK                    0x001E  /* BCWK_DIV - [4:1] */
#define WM8400_BCWK_DIV_SHIFT                        1  /* BCWK_DIV - [4:1] */
#define WM8400_BCWK_DIV_WIDTH                        4  /* BCWK_DIV - [4:1] */

/*
 * W8 (0x08) - Cwocking (2)
 */
#define WM8400_MCWK_SWC                         0x8000  /* MCWK_SWC */
#define WM8400_MCWK_SWC_MASK                    0x8000  /* MCWK_SWC */
#define WM8400_MCWK_SWC_SHIFT                       15  /* MCWK_SWC */
#define WM8400_MCWK_SWC_WIDTH                        1  /* MCWK_SWC */
#define WM8400_SYSCWK_SWC                       0x4000  /* SYSCWK_SWC */
#define WM8400_SYSCWK_SWC_MASK                  0x4000  /* SYSCWK_SWC */
#define WM8400_SYSCWK_SWC_SHIFT                     14  /* SYSCWK_SWC */
#define WM8400_SYSCWK_SWC_WIDTH                      1  /* SYSCWK_SWC */
#define WM8400_CWK_FOWCE                        0x2000  /* CWK_FOWCE */
#define WM8400_CWK_FOWCE_MASK                   0x2000  /* CWK_FOWCE */
#define WM8400_CWK_FOWCE_SHIFT                      13  /* CWK_FOWCE */
#define WM8400_CWK_FOWCE_WIDTH                       1  /* CWK_FOWCE */
#define WM8400_MCWK_DIV_MASK                    0x1800  /* MCWK_DIV - [12:11] */
#define WM8400_MCWK_DIV_SHIFT                       11  /* MCWK_DIV - [12:11] */
#define WM8400_MCWK_DIV_WIDTH                        2  /* MCWK_DIV - [12:11] */
#define WM8400_MCWK_INV                         0x0400  /* MCWK_INV */
#define WM8400_MCWK_INV_MASK                    0x0400  /* MCWK_INV */
#define WM8400_MCWK_INV_SHIFT                       10  /* MCWK_INV */
#define WM8400_MCWK_INV_WIDTH                        1  /* MCWK_INV */
#define WM8400_ADC_CWKDIV_MASK                  0x00E0  /* ADC_CWKDIV - [7:5] */
#define WM8400_ADC_CWKDIV_SHIFT                      5  /* ADC_CWKDIV - [7:5] */
#define WM8400_ADC_CWKDIV_WIDTH                      3  /* ADC_CWKDIV - [7:5] */
#define WM8400_DAC_CWKDIV_MASK                  0x001C  /* DAC_CWKDIV - [4:2] */
#define WM8400_DAC_CWKDIV_SHIFT                      2  /* DAC_CWKDIV - [4:2] */
#define WM8400_DAC_CWKDIV_WIDTH                      3  /* DAC_CWKDIV - [4:2] */

/*
 * W9 (0x09) - Audio Intewface (3)
 */
#define WM8400_AIF_MSTW1                        0x8000  /* AIF_MSTW1 */
#define WM8400_AIF_MSTW1_MASK                   0x8000  /* AIF_MSTW1 */
#define WM8400_AIF_MSTW1_SHIFT                      15  /* AIF_MSTW1 */
#define WM8400_AIF_MSTW1_WIDTH                       1  /* AIF_MSTW1 */
#define WM8400_AIF_MSTW2                        0x4000  /* AIF_MSTW2 */
#define WM8400_AIF_MSTW2_MASK                   0x4000  /* AIF_MSTW2 */
#define WM8400_AIF_MSTW2_SHIFT                      14  /* AIF_MSTW2 */
#define WM8400_AIF_MSTW2_WIDTH                       1  /* AIF_MSTW2 */
#define WM8400_AIF_SEW                          0x2000  /* AIF_SEW */
#define WM8400_AIF_SEW_MASK                     0x2000  /* AIF_SEW */
#define WM8400_AIF_SEW_SHIFT                        13  /* AIF_SEW */
#define WM8400_AIF_SEW_WIDTH                         1  /* AIF_SEW */
#define WM8400_ADCWWC_DIW                       0x0800  /* ADCWWC_DIW */
#define WM8400_ADCWWC_DIW_MASK                  0x0800  /* ADCWWC_DIW */
#define WM8400_ADCWWC_DIW_SHIFT                     11  /* ADCWWC_DIW */
#define WM8400_ADCWWC_DIW_WIDTH                      1  /* ADCWWC_DIW */
#define WM8400_ADCWWC_WATE_MASK                 0x07FF  /* ADCWWC_WATE - [10:0] */
#define WM8400_ADCWWC_WATE_SHIFT                     0  /* ADCWWC_WATE - [10:0] */
#define WM8400_ADCWWC_WATE_WIDTH                    11  /* ADCWWC_WATE - [10:0] */

/*
 * W10 (0x0A) - Audio Intewface (4)
 */
#define WM8400_AWWCGPIO1                        0x8000  /* AWWCGPIO1 */
#define WM8400_AWWCGPIO1_MASK                   0x8000  /* AWWCGPIO1 */
#define WM8400_AWWCGPIO1_SHIFT                      15  /* AWWCGPIO1 */
#define WM8400_AWWCGPIO1_WIDTH                       1  /* AWWCGPIO1 */
#define WM8400_AWWCBGPIO6                       0x4000  /* AWWCBGPIO6 */
#define WM8400_AWWCBGPIO6_MASK                  0x4000  /* AWWCBGPIO6 */
#define WM8400_AWWCBGPIO6_SHIFT                     14  /* AWWCBGPIO6 */
#define WM8400_AWWCBGPIO6_WIDTH                      1  /* AWWCBGPIO6 */
#define WM8400_AIF_TWIS                         0x2000  /* AIF_TWIS */
#define WM8400_AIF_TWIS_MASK                    0x2000  /* AIF_TWIS */
#define WM8400_AIF_TWIS_SHIFT                       13  /* AIF_TWIS */
#define WM8400_AIF_TWIS_WIDTH                        1  /* AIF_TWIS */
#define WM8400_DACWWC_DIW                       0x0800  /* DACWWC_DIW */
#define WM8400_DACWWC_DIW_MASK                  0x0800  /* DACWWC_DIW */
#define WM8400_DACWWC_DIW_SHIFT                     11  /* DACWWC_DIW */
#define WM8400_DACWWC_DIW_WIDTH                      1  /* DACWWC_DIW */
#define WM8400_DACWWC_WATE_MASK                 0x07FF  /* DACWWC_WATE - [10:0] */
#define WM8400_DACWWC_WATE_SHIFT                     0  /* DACWWC_WATE - [10:0] */
#define WM8400_DACWWC_WATE_WIDTH                    11  /* DACWWC_WATE - [10:0] */

/*
 * W11 (0x0B) - DAC CTWW
 */
#define WM8400_DAC_SDMCWK_WATE                  0x2000  /* DAC_SDMCWK_WATE */
#define WM8400_DAC_SDMCWK_WATE_MASK             0x2000  /* DAC_SDMCWK_WATE */
#define WM8400_DAC_SDMCWK_WATE_SHIFT                13  /* DAC_SDMCWK_WATE */
#define WM8400_DAC_SDMCWK_WATE_WIDTH                 1  /* DAC_SDMCWK_WATE */
#define WM8400_AIF_WWCWKWATE                    0x0400  /* AIF_WWCWKWATE */
#define WM8400_AIF_WWCWKWATE_MASK               0x0400  /* AIF_WWCWKWATE */
#define WM8400_AIF_WWCWKWATE_SHIFT                  10  /* AIF_WWCWKWATE */
#define WM8400_AIF_WWCWKWATE_WIDTH                   1  /* AIF_WWCWKWATE */
#define WM8400_DAC_MONO                         0x0200  /* DAC_MONO */
#define WM8400_DAC_MONO_MASK                    0x0200  /* DAC_MONO */
#define WM8400_DAC_MONO_SHIFT                        9  /* DAC_MONO */
#define WM8400_DAC_MONO_WIDTH                        1  /* DAC_MONO */
#define WM8400_DAC_SB_FIWT                      0x0100  /* DAC_SB_FIWT */
#define WM8400_DAC_SB_FIWT_MASK                 0x0100  /* DAC_SB_FIWT */
#define WM8400_DAC_SB_FIWT_SHIFT                     8  /* DAC_SB_FIWT */
#define WM8400_DAC_SB_FIWT_WIDTH                     1  /* DAC_SB_FIWT */
#define WM8400_DAC_MUTEWATE                     0x0080  /* DAC_MUTEWATE */
#define WM8400_DAC_MUTEWATE_MASK                0x0080  /* DAC_MUTEWATE */
#define WM8400_DAC_MUTEWATE_SHIFT                    7  /* DAC_MUTEWATE */
#define WM8400_DAC_MUTEWATE_WIDTH                    1  /* DAC_MUTEWATE */
#define WM8400_DAC_MUTEMODE                     0x0040  /* DAC_MUTEMODE */
#define WM8400_DAC_MUTEMODE_MASK                0x0040  /* DAC_MUTEMODE */
#define WM8400_DAC_MUTEMODE_SHIFT                    6  /* DAC_MUTEMODE */
#define WM8400_DAC_MUTEMODE_WIDTH                    1  /* DAC_MUTEMODE */
#define WM8400_DEEMP_MASK                       0x0030  /* DEEMP - [5:4] */
#define WM8400_DEEMP_SHIFT                           4  /* DEEMP - [5:4] */
#define WM8400_DEEMP_WIDTH                           2  /* DEEMP - [5:4] */
#define WM8400_DAC_MUTE                         0x0004  /* DAC_MUTE */
#define WM8400_DAC_MUTE_MASK                    0x0004  /* DAC_MUTE */
#define WM8400_DAC_MUTE_SHIFT                        2  /* DAC_MUTE */
#define WM8400_DAC_MUTE_WIDTH                        1  /* DAC_MUTE */
#define WM8400_DACW_DATINV                      0x0002  /* DACW_DATINV */
#define WM8400_DACW_DATINV_MASK                 0x0002  /* DACW_DATINV */
#define WM8400_DACW_DATINV_SHIFT                     1  /* DACW_DATINV */
#define WM8400_DACW_DATINV_WIDTH                     1  /* DACW_DATINV */
#define WM8400_DACW_DATINV                      0x0001  /* DACW_DATINV */
#define WM8400_DACW_DATINV_MASK                 0x0001  /* DACW_DATINV */
#define WM8400_DACW_DATINV_SHIFT                     0  /* DACW_DATINV */
#define WM8400_DACW_DATINV_WIDTH                     1  /* DACW_DATINV */

/*
 * W12 (0x0C) - Weft DAC Digitaw Vowume
 */
#define WM8400_DAC_VU                           0x0100  /* DAC_VU */
#define WM8400_DAC_VU_MASK                      0x0100  /* DAC_VU */
#define WM8400_DAC_VU_SHIFT                          8  /* DAC_VU */
#define WM8400_DAC_VU_WIDTH                          1  /* DAC_VU */
#define WM8400_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8400_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8400_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W13 (0x0D) - Wight DAC Digitaw Vowume
 */
#define WM8400_DAC_VU                           0x0100  /* DAC_VU */
#define WM8400_DAC_VU_MASK                      0x0100  /* DAC_VU */
#define WM8400_DAC_VU_SHIFT                          8  /* DAC_VU */
#define WM8400_DAC_VU_WIDTH                          1  /* DAC_VU */
#define WM8400_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8400_DACW_VOW_SHIFT                        0  /* DACW_VOW - [7:0] */
#define WM8400_DACW_VOW_WIDTH                        8  /* DACW_VOW - [7:0] */

/*
 * W14 (0x0E) - Digitaw Side Tone
 */
#define WM8400_ADCW_DAC_SVOW_MASK               0x1E00  /*   ADCW_DAC_SVOW - [12:9] */
#define WM8400_ADCW_DAC_SVOW_SHIFT                   9  /*   ADCW_DAC_SVOW - [12:9] */
#define WM8400_ADCW_DAC_SVOW_WIDTH                   4  /*   ADCW_DAC_SVOW - [12:9] */
#define WM8400_ADCW_DAC_SVOW_MASK               0x01E0  /* ADCW_DAC_SVOW - [8:5] */
#define WM8400_ADCW_DAC_SVOW_SHIFT                   5  /* ADCW_DAC_SVOW - [8:5] */
#define WM8400_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [8:5] */
#define WM8400_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8400_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8400_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */
#define WM8400_ADC_TO_DACW_MASK                 0x0003  /* ADC_TO_DACW - [1:0] */
#define WM8400_ADC_TO_DACW_SHIFT                     0  /* ADC_TO_DACW - [1:0] */
#define WM8400_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [1:0] */

/*
 * W15 (0x0F) - ADC CTWW
 */
#define WM8400_ADC_HPF_ENA                      0x0100  /* ADC_HPF_ENA */
#define WM8400_ADC_HPF_ENA_MASK                 0x0100  /* ADC_HPF_ENA */
#define WM8400_ADC_HPF_ENA_SHIFT                     8  /* ADC_HPF_ENA */
#define WM8400_ADC_HPF_ENA_WIDTH                     1  /* ADC_HPF_ENA */
#define WM8400_ADC_HPF_CUT_MASK                 0x0060  /* ADC_HPF_CUT - [6:5] */
#define WM8400_ADC_HPF_CUT_SHIFT                     5  /* ADC_HPF_CUT - [6:5] */
#define WM8400_ADC_HPF_CUT_WIDTH                     2  /* ADC_HPF_CUT - [6:5] */
#define WM8400_ADCW_DATINV                      0x0002  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV_MASK                 0x0002  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV_SHIFT                     1  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV_WIDTH                     1  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV                      0x0001  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV_MASK                 0x0001  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV_SHIFT                     0  /* ADCW_DATINV */
#define WM8400_ADCW_DATINV_WIDTH                     1  /* ADCW_DATINV */

/*
 * W16 (0x10) - Weft ADC Digitaw Vowume
 */
#define WM8400_ADC_VU                           0x0100  /* ADC_VU */
#define WM8400_ADC_VU_MASK                      0x0100  /* ADC_VU */
#define WM8400_ADC_VU_SHIFT                          8  /* ADC_VU */
#define WM8400_ADC_VU_WIDTH                          1  /* ADC_VU */
#define WM8400_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8400_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8400_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W17 (0x11) - Wight ADC Digitaw Vowume
 */
#define WM8400_ADC_VU                           0x0100  /* ADC_VU */
#define WM8400_ADC_VU_MASK                      0x0100  /* ADC_VU */
#define WM8400_ADC_VU_SHIFT                          8  /* ADC_VU */
#define WM8400_ADC_VU_WIDTH                          1  /* ADC_VU */
#define WM8400_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8400_ADCW_VOW_SHIFT                        0  /* ADCW_VOW - [7:0] */
#define WM8400_ADCW_VOW_WIDTH                        8  /* ADCW_VOW - [7:0] */

/*
 * W24 (0x18) - Weft Wine Input 1&2 Vowume
 */
#define WM8400_IPVU                             0x0100  /* IPVU */
#define WM8400_IPVU_MASK                        0x0100  /* IPVU */
#define WM8400_IPVU_SHIFT                            8  /* IPVU */
#define WM8400_IPVU_WIDTH                            1  /* IPVU */
#define WM8400_WI12MUTE                         0x0080  /* WI12MUTE */
#define WM8400_WI12MUTE_MASK                    0x0080  /* WI12MUTE */
#define WM8400_WI12MUTE_SHIFT                        7  /* WI12MUTE */
#define WM8400_WI12MUTE_WIDTH                        1  /* WI12MUTE */
#define WM8400_WI12ZC                           0x0040  /* WI12ZC */
#define WM8400_WI12ZC_MASK                      0x0040  /* WI12ZC */
#define WM8400_WI12ZC_SHIFT                          6  /* WI12ZC */
#define WM8400_WI12ZC_WIDTH                          1  /* WI12ZC */
#define WM8400_WIN12VOW_MASK                    0x001F  /* WIN12VOW - [4:0] */
#define WM8400_WIN12VOW_SHIFT                        0  /* WIN12VOW - [4:0] */
#define WM8400_WIN12VOW_WIDTH                        5  /* WIN12VOW - [4:0] */

/*
 * W25 (0x19) - Weft Wine Input 3&4 Vowume
 */
#define WM8400_IPVU                             0x0100  /* IPVU */
#define WM8400_IPVU_MASK                        0x0100  /* IPVU */
#define WM8400_IPVU_SHIFT                            8  /* IPVU */
#define WM8400_IPVU_WIDTH                            1  /* IPVU */
#define WM8400_WI34MUTE                         0x0080  /* WI34MUTE */
#define WM8400_WI34MUTE_MASK                    0x0080  /* WI34MUTE */
#define WM8400_WI34MUTE_SHIFT                        7  /* WI34MUTE */
#define WM8400_WI34MUTE_WIDTH                        1  /* WI34MUTE */
#define WM8400_WI34ZC                           0x0040  /* WI34ZC */
#define WM8400_WI34ZC_MASK                      0x0040  /* WI34ZC */
#define WM8400_WI34ZC_SHIFT                          6  /* WI34ZC */
#define WM8400_WI34ZC_WIDTH                          1  /* WI34ZC */
#define WM8400_WIN34VOW_MASK                    0x001F  /* WIN34VOW - [4:0] */
#define WM8400_WIN34VOW_SHIFT                        0  /* WIN34VOW - [4:0] */
#define WM8400_WIN34VOW_WIDTH                        5  /* WIN34VOW - [4:0] */

/*
 * W26 (0x1A) - Wight Wine Input 1&2 Vowume
 */
#define WM8400_IPVU                             0x0100  /* IPVU */
#define WM8400_IPVU_MASK                        0x0100  /* IPVU */
#define WM8400_IPVU_SHIFT                            8  /* IPVU */
#define WM8400_IPVU_WIDTH                            1  /* IPVU */
#define WM8400_WI12MUTE                         0x0080  /* WI12MUTE */
#define WM8400_WI12MUTE_MASK                    0x0080  /* WI12MUTE */
#define WM8400_WI12MUTE_SHIFT                        7  /* WI12MUTE */
#define WM8400_WI12MUTE_WIDTH                        1  /* WI12MUTE */
#define WM8400_WI12ZC                           0x0040  /* WI12ZC */
#define WM8400_WI12ZC_MASK                      0x0040  /* WI12ZC */
#define WM8400_WI12ZC_SHIFT                          6  /* WI12ZC */
#define WM8400_WI12ZC_WIDTH                          1  /* WI12ZC */
#define WM8400_WIN12VOW_MASK                    0x001F  /* WIN12VOW - [4:0] */
#define WM8400_WIN12VOW_SHIFT                        0  /* WIN12VOW - [4:0] */
#define WM8400_WIN12VOW_WIDTH                        5  /* WIN12VOW - [4:0] */

/*
 * W27 (0x1B) - Wight Wine Input 3&4 Vowume
 */
#define WM8400_IPVU                             0x0100  /* IPVU */
#define WM8400_IPVU_MASK                        0x0100  /* IPVU */
#define WM8400_IPVU_SHIFT                            8  /* IPVU */
#define WM8400_IPVU_WIDTH                            1  /* IPVU */
#define WM8400_WI34MUTE                         0x0080  /* WI34MUTE */
#define WM8400_WI34MUTE_MASK                    0x0080  /* WI34MUTE */
#define WM8400_WI34MUTE_SHIFT                        7  /* WI34MUTE */
#define WM8400_WI34MUTE_WIDTH                        1  /* WI34MUTE */
#define WM8400_WI34ZC                           0x0040  /* WI34ZC */
#define WM8400_WI34ZC_MASK                      0x0040  /* WI34ZC */
#define WM8400_WI34ZC_SHIFT                          6  /* WI34ZC */
#define WM8400_WI34ZC_WIDTH                          1  /* WI34ZC */
#define WM8400_WIN34VOW_MASK                    0x001F  /* WIN34VOW - [4:0] */
#define WM8400_WIN34VOW_SHIFT                        0  /* WIN34VOW - [4:0] */
#define WM8400_WIN34VOW_WIDTH                        5  /* WIN34VOW - [4:0] */

/*
 * W28 (0x1C) - Weft Output Vowume
 */
#define WM8400_OPVU                             0x0100  /* OPVU */
#define WM8400_OPVU_MASK                        0x0100  /* OPVU */
#define WM8400_OPVU_SHIFT                            8  /* OPVU */
#define WM8400_OPVU_WIDTH                            1  /* OPVU */
#define WM8400_WOZC                             0x0080  /* WOZC */
#define WM8400_WOZC_MASK                        0x0080  /* WOZC */
#define WM8400_WOZC_SHIFT                            7  /* WOZC */
#define WM8400_WOZC_WIDTH                            1  /* WOZC */
#define WM8400_WOUTVOW_MASK                     0x007F  /* WOUTVOW - [6:0] */
#define WM8400_WOUTVOW_SHIFT                         0  /* WOUTVOW - [6:0] */
#define WM8400_WOUTVOW_WIDTH                         7  /* WOUTVOW - [6:0] */

/*
 * W29 (0x1D) - Wight Output Vowume
 */
#define WM8400_OPVU                             0x0100  /* OPVU */
#define WM8400_OPVU_MASK                        0x0100  /* OPVU */
#define WM8400_OPVU_SHIFT                            8  /* OPVU */
#define WM8400_OPVU_WIDTH                            1  /* OPVU */
#define WM8400_WOZC                             0x0080  /* WOZC */
#define WM8400_WOZC_MASK                        0x0080  /* WOZC */
#define WM8400_WOZC_SHIFT                            7  /* WOZC */
#define WM8400_WOZC_WIDTH                            1  /* WOZC */
#define WM8400_WOUTVOW_MASK                     0x007F  /* WOUTVOW - [6:0] */
#define WM8400_WOUTVOW_SHIFT                         0  /* WOUTVOW - [6:0] */
#define WM8400_WOUTVOW_WIDTH                         7  /* WOUTVOW - [6:0] */

/*
 * W30 (0x1E) - Wine Outputs Vowume
 */
#define WM8400_WONMUTE                          0x0040  /* WONMUTE */
#define WM8400_WONMUTE_MASK                     0x0040  /* WONMUTE */
#define WM8400_WONMUTE_SHIFT                         6  /* WONMUTE */
#define WM8400_WONMUTE_WIDTH                         1  /* WONMUTE */
#define WM8400_WOPMUTE                          0x0020  /* WOPMUTE */
#define WM8400_WOPMUTE_MASK                     0x0020  /* WOPMUTE */
#define WM8400_WOPMUTE_SHIFT                         5  /* WOPMUTE */
#define WM8400_WOPMUTE_WIDTH                         1  /* WOPMUTE */
#define WM8400_WOATTN                           0x0010  /* WOATTN */
#define WM8400_WOATTN_MASK                      0x0010  /* WOATTN */
#define WM8400_WOATTN_SHIFT                          4  /* WOATTN */
#define WM8400_WOATTN_WIDTH                          1  /* WOATTN */
#define WM8400_WONMUTE                          0x0004  /* WONMUTE */
#define WM8400_WONMUTE_MASK                     0x0004  /* WONMUTE */
#define WM8400_WONMUTE_SHIFT                         2  /* WONMUTE */
#define WM8400_WONMUTE_WIDTH                         1  /* WONMUTE */
#define WM8400_WOPMUTE                          0x0002  /* WOPMUTE */
#define WM8400_WOPMUTE_MASK                     0x0002  /* WOPMUTE */
#define WM8400_WOPMUTE_SHIFT                         1  /* WOPMUTE */
#define WM8400_WOPMUTE_WIDTH                         1  /* WOPMUTE */
#define WM8400_WOATTN                           0x0001  /* WOATTN */
#define WM8400_WOATTN_MASK                      0x0001  /* WOATTN */
#define WM8400_WOATTN_SHIFT                          0  /* WOATTN */
#define WM8400_WOATTN_WIDTH                          1  /* WOATTN */

/*
 * W31 (0x1F) - Out3/4 Vowume
 */
#define WM8400_OUT3MUTE                         0x0020  /* OUT3MUTE */
#define WM8400_OUT3MUTE_MASK                    0x0020  /* OUT3MUTE */
#define WM8400_OUT3MUTE_SHIFT                        5  /* OUT3MUTE */
#define WM8400_OUT3MUTE_WIDTH                        1  /* OUT3MUTE */
#define WM8400_OUT3ATTN                         0x0010  /* OUT3ATTN */
#define WM8400_OUT3ATTN_MASK                    0x0010  /* OUT3ATTN */
#define WM8400_OUT3ATTN_SHIFT                        4  /* OUT3ATTN */
#define WM8400_OUT3ATTN_WIDTH                        1  /* OUT3ATTN */
#define WM8400_OUT4MUTE                         0x0002  /* OUT4MUTE */
#define WM8400_OUT4MUTE_MASK                    0x0002  /* OUT4MUTE */
#define WM8400_OUT4MUTE_SHIFT                        1  /* OUT4MUTE */
#define WM8400_OUT4MUTE_WIDTH                        1  /* OUT4MUTE */
#define WM8400_OUT4ATTN                         0x0001  /* OUT4ATTN */
#define WM8400_OUT4ATTN_MASK                    0x0001  /* OUT4ATTN */
#define WM8400_OUT4ATTN_SHIFT                        0  /* OUT4ATTN */
#define WM8400_OUT4ATTN_WIDTH                        1  /* OUT4ATTN */

/*
 * W32 (0x20) - Weft OPGA Vowume
 */
#define WM8400_OPVU                             0x0100  /* OPVU */
#define WM8400_OPVU_MASK                        0x0100  /* OPVU */
#define WM8400_OPVU_SHIFT                            8  /* OPVU */
#define WM8400_OPVU_WIDTH                            1  /* OPVU */
#define WM8400_WOPGAZC                          0x0080  /* WOPGAZC */
#define WM8400_WOPGAZC_MASK                     0x0080  /* WOPGAZC */
#define WM8400_WOPGAZC_SHIFT                         7  /* WOPGAZC */
#define WM8400_WOPGAZC_WIDTH                         1  /* WOPGAZC */
#define WM8400_WOPGAVOW_MASK                    0x007F  /* WOPGAVOW - [6:0] */
#define WM8400_WOPGAVOW_SHIFT                        0  /* WOPGAVOW - [6:0] */
#define WM8400_WOPGAVOW_WIDTH                        7  /* WOPGAVOW - [6:0] */

/*
 * W33 (0x21) - Wight OPGA Vowume
 */
#define WM8400_OPVU                             0x0100  /* OPVU */
#define WM8400_OPVU_MASK                        0x0100  /* OPVU */
#define WM8400_OPVU_SHIFT                            8  /* OPVU */
#define WM8400_OPVU_WIDTH                            1  /* OPVU */
#define WM8400_WOPGAZC                          0x0080  /* WOPGAZC */
#define WM8400_WOPGAZC_MASK                     0x0080  /* WOPGAZC */
#define WM8400_WOPGAZC_SHIFT                         7  /* WOPGAZC */
#define WM8400_WOPGAZC_WIDTH                         1  /* WOPGAZC */
#define WM8400_WOPGAVOW_MASK                    0x007F  /* WOPGAVOW - [6:0] */
#define WM8400_WOPGAVOW_SHIFT                        0  /* WOPGAVOW - [6:0] */
#define WM8400_WOPGAVOW_WIDTH                        7  /* WOPGAVOW - [6:0] */

/*
 * W34 (0x22) - Speakew Vowume
 */
#define WM8400_SPKATTN_MASK                     0x0003  /* SPKATTN - [1:0] */
#define WM8400_SPKATTN_SHIFT                         0  /* SPKATTN - [1:0] */
#define WM8400_SPKATTN_WIDTH                         2  /* SPKATTN - [1:0] */

/*
 * W35 (0x23) - CwassD1
 */
#define WM8400_CDMODE                           0x0100  /* CDMODE */
#define WM8400_CDMODE_MASK                      0x0100  /* CDMODE */
#define WM8400_CDMODE_SHIFT                          8  /* CDMODE */
#define WM8400_CDMODE_WIDTH                          1  /* CDMODE */
#define WM8400_CWASSD_CWK_SEW                   0x0080  /* CWASSD_CWK_SEW */
#define WM8400_CWASSD_CWK_SEW_MASK              0x0080  /* CWASSD_CWK_SEW */
#define WM8400_CWASSD_CWK_SEW_SHIFT                  7  /* CWASSD_CWK_SEW */
#define WM8400_CWASSD_CWK_SEW_WIDTH                  1  /* CWASSD_CWK_SEW */
#define WM8400_CD_SWCTWW                        0x0040  /* CD_SWCTWW */
#define WM8400_CD_SWCTWW_MASK                   0x0040  /* CD_SWCTWW */
#define WM8400_CD_SWCTWW_SHIFT                       6  /* CD_SWCTWW */
#define WM8400_CD_SWCTWW_WIDTH                       1  /* CD_SWCTWW */
#define WM8400_SPKNOPOP                         0x0020  /* SPKNOPOP */
#define WM8400_SPKNOPOP_MASK                    0x0020  /* SPKNOPOP */
#define WM8400_SPKNOPOP_SHIFT                        5  /* SPKNOPOP */
#define WM8400_SPKNOPOP_WIDTH                        1  /* SPKNOPOP */
#define WM8400_DBWEWATE                         0x0010  /* DBWEWATE */
#define WM8400_DBWEWATE_MASK                    0x0010  /* DBWEWATE */
#define WM8400_DBWEWATE_SHIFT                        4  /* DBWEWATE */
#define WM8400_DBWEWATE_WIDTH                        1  /* DBWEWATE */
#define WM8400_WOOPTEST                         0x0008  /* WOOPTEST */
#define WM8400_WOOPTEST_MASK                    0x0008  /* WOOPTEST */
#define WM8400_WOOPTEST_SHIFT                        3  /* WOOPTEST */
#define WM8400_WOOPTEST_WIDTH                        1  /* WOOPTEST */
#define WM8400_HAWFABBIAS                       0x0004  /* HAWFABBIAS */
#define WM8400_HAWFABBIAS_MASK                  0x0004  /* HAWFABBIAS */
#define WM8400_HAWFABBIAS_SHIFT                      2  /* HAWFABBIAS */
#define WM8400_HAWFABBIAS_WIDTH                      1  /* HAWFABBIAS */
#define WM8400_TWIDEW_MASK                      0x0003  /* TWIDEW - [1:0] */
#define WM8400_TWIDEW_SHIFT                          0  /* TWIDEW - [1:0] */
#define WM8400_TWIDEW_WIDTH                          2  /* TWIDEW - [1:0] */

/*
 * W37 (0x25) - CwassD3
 */
#define WM8400_DCGAIN_MASK                      0x0038  /* DCGAIN - [5:3] */
#define WM8400_DCGAIN_SHIFT                          3  /* DCGAIN - [5:3] */
#define WM8400_DCGAIN_WIDTH                          3  /* DCGAIN - [5:3] */
#define WM8400_ACGAIN_MASK                      0x0007  /* ACGAIN - [2:0] */
#define WM8400_ACGAIN_SHIFT                          0  /* ACGAIN - [2:0] */
#define WM8400_ACGAIN_WIDTH                          3  /* ACGAIN - [2:0] */

/*
 * W39 (0x27) - Input Mixew1
 */
#define WM8400_AINWMODE_MASK                    0x000C  /* AINWMODE - [3:2] */
#define WM8400_AINWMODE_SHIFT                        2  /* AINWMODE - [3:2] */
#define WM8400_AINWMODE_WIDTH                        2  /* AINWMODE - [3:2] */
#define WM8400_AINWMODE_MASK                    0x0003  /* AINWMODE - [1:0] */
#define WM8400_AINWMODE_SHIFT                        0  /* AINWMODE - [1:0] */
#define WM8400_AINWMODE_WIDTH                        2  /* AINWMODE - [1:0] */

/*
 * W40 (0x28) - Input Mixew2
 */
#define WM8400_WMP4                             0x0080  /* WMP4 */
#define WM8400_WMP4_MASK                        0x0080  /* WMP4 */
#define WM8400_WMP4_SHIFT                            7  /* WMP4 */
#define WM8400_WMP4_WIDTH                            1  /* WMP4 */
#define WM8400_WMN3                             0x0040  /* WMN3 */
#define WM8400_WMN3_MASK                        0x0040  /* WMN3 */
#define WM8400_WMN3_SHIFT                            6  /* WMN3 */
#define WM8400_WMN3_WIDTH                            1  /* WMN3 */
#define WM8400_WMP2                             0x0020  /* WMP2 */
#define WM8400_WMP2_MASK                        0x0020  /* WMP2 */
#define WM8400_WMP2_SHIFT                            5  /* WMP2 */
#define WM8400_WMP2_WIDTH                            1  /* WMP2 */
#define WM8400_WMN1                             0x0010  /* WMN1 */
#define WM8400_WMN1_MASK                        0x0010  /* WMN1 */
#define WM8400_WMN1_SHIFT                            4  /* WMN1 */
#define WM8400_WMN1_WIDTH                            1  /* WMN1 */
#define WM8400_WMP4                             0x0008  /* WMP4 */
#define WM8400_WMP4_MASK                        0x0008  /* WMP4 */
#define WM8400_WMP4_SHIFT                            3  /* WMP4 */
#define WM8400_WMP4_WIDTH                            1  /* WMP4 */
#define WM8400_WMN3                             0x0004  /* WMN3 */
#define WM8400_WMN3_MASK                        0x0004  /* WMN3 */
#define WM8400_WMN3_SHIFT                            2  /* WMN3 */
#define WM8400_WMN3_WIDTH                            1  /* WMN3 */
#define WM8400_WMP2                             0x0002  /* WMP2 */
#define WM8400_WMP2_MASK                        0x0002  /* WMP2 */
#define WM8400_WMP2_SHIFT                            1  /* WMP2 */
#define WM8400_WMP2_WIDTH                            1  /* WMP2 */
#define WM8400_WMN1                             0x0001  /* WMN1 */
#define WM8400_WMN1_MASK                        0x0001  /* WMN1 */
#define WM8400_WMN1_SHIFT                            0  /* WMN1 */
#define WM8400_WMN1_WIDTH                            1  /* WMN1 */

/*
 * W41 (0x29) - Input Mixew3
 */
#define WM8400_W34MNB                           0x0100  /* W34MNB */
#define WM8400_W34MNB_MASK                      0x0100  /* W34MNB */
#define WM8400_W34MNB_SHIFT                          8  /* W34MNB */
#define WM8400_W34MNB_WIDTH                          1  /* W34MNB */
#define WM8400_W34MNBST                         0x0080  /* W34MNBST */
#define WM8400_W34MNBST_MASK                    0x0080  /* W34MNBST */
#define WM8400_W34MNBST_SHIFT                        7  /* W34MNBST */
#define WM8400_W34MNBST_WIDTH                        1  /* W34MNBST */
#define WM8400_W12MNB                           0x0020  /* W12MNB */
#define WM8400_W12MNB_MASK                      0x0020  /* W12MNB */
#define WM8400_W12MNB_SHIFT                          5  /* W12MNB */
#define WM8400_W12MNB_WIDTH                          1  /* W12MNB */
#define WM8400_W12MNBST                         0x0010  /* W12MNBST */
#define WM8400_W12MNBST_MASK                    0x0010  /* W12MNBST */
#define WM8400_W12MNBST_SHIFT                        4  /* W12MNBST */
#define WM8400_W12MNBST_WIDTH                        1  /* W12MNBST */
#define WM8400_WDBVOW_MASK                      0x0007  /* WDBVOW - [2:0] */
#define WM8400_WDBVOW_SHIFT                          0  /* WDBVOW - [2:0] */
#define WM8400_WDBVOW_WIDTH                          3  /* WDBVOW - [2:0] */

/*
 * W42 (0x2A) - Input Mixew4
 */
#define WM8400_W34MNB                           0x0100  /* W34MNB */
#define WM8400_W34MNB_MASK                      0x0100  /* W34MNB */
#define WM8400_W34MNB_SHIFT                          8  /* W34MNB */
#define WM8400_W34MNB_WIDTH                          1  /* W34MNB */
#define WM8400_W34MNBST                         0x0080  /* W34MNBST */
#define WM8400_W34MNBST_MASK                    0x0080  /* W34MNBST */
#define WM8400_W34MNBST_SHIFT                        7  /* W34MNBST */
#define WM8400_W34MNBST_WIDTH                        1  /* W34MNBST */
#define WM8400_W12MNB                           0x0020  /* W12MNB */
#define WM8400_W12MNB_MASK                      0x0020  /* W12MNB */
#define WM8400_W12MNB_SHIFT                          5  /* W12MNB */
#define WM8400_W12MNB_WIDTH                          1  /* W12MNB */
#define WM8400_W12MNBST                         0x0010  /* W12MNBST */
#define WM8400_W12MNBST_MASK                    0x0010  /* W12MNBST */
#define WM8400_W12MNBST_SHIFT                        4  /* W12MNBST */
#define WM8400_W12MNBST_WIDTH                        1  /* W12MNBST */
#define WM8400_WDBVOW_MASK                      0x0007  /* WDBVOW - [2:0] */
#define WM8400_WDBVOW_SHIFT                          0  /* WDBVOW - [2:0] */
#define WM8400_WDBVOW_WIDTH                          3  /* WDBVOW - [2:0] */

/*
 * W43 (0x2B) - Input Mixew5
 */
#define WM8400_WI2BVOW_MASK                     0x01C0  /* WI2BVOW - [8:6] */
#define WM8400_WI2BVOW_SHIFT                         6  /* WI2BVOW - [8:6] */
#define WM8400_WI2BVOW_WIDTH                         3  /* WI2BVOW - [8:6] */
#define WM8400_WW4BVOW_MASK                     0x0038  /* WW4BVOW - [5:3] */
#define WM8400_WW4BVOW_SHIFT                         3  /* WW4BVOW - [5:3] */
#define WM8400_WW4BVOW_WIDTH                         3  /* WW4BVOW - [5:3] */
#define WM8400_WW4BVOW_MASK                     0x0007  /* WW4BVOW - [2:0] */
#define WM8400_WW4BVOW_SHIFT                         0  /* WW4BVOW - [2:0] */
#define WM8400_WW4BVOW_WIDTH                         3  /* WW4BVOW - [2:0] */

/*
 * W44 (0x2C) - Input Mixew6
 */
#define WM8400_WI2BVOW_MASK                     0x01C0  /* WI2BVOW - [8:6] */
#define WM8400_WI2BVOW_SHIFT                         6  /* WI2BVOW - [8:6] */
#define WM8400_WI2BVOW_WIDTH                         3  /* WI2BVOW - [8:6] */
#define WM8400_WW4BVOW_MASK                     0x0038  /* WW4BVOW - [5:3] */
#define WM8400_WW4BVOW_SHIFT                         3  /* WW4BVOW - [5:3] */
#define WM8400_WW4BVOW_WIDTH                         3  /* WW4BVOW - [5:3] */
#define WM8400_WW4BVOW_MASK                     0x0007  /* WW4BVOW - [2:0] */
#define WM8400_WW4BVOW_SHIFT                         0  /* WW4BVOW - [2:0] */
#define WM8400_WW4BVOW_WIDTH                         3  /* WW4BVOW - [2:0] */

/*
 * W45 (0x2D) - Output Mixew1
 */
#define WM8400_WWBWO                            0x0080  /* WWBWO */
#define WM8400_WWBWO_MASK                       0x0080  /* WWBWO */
#define WM8400_WWBWO_SHIFT                           7  /* WWBWO */
#define WM8400_WWBWO_WIDTH                           1  /* WWBWO */
#define WM8400_WWBWO                            0x0040  /* WWBWO */
#define WM8400_WWBWO_MASK                       0x0040  /* WWBWO */
#define WM8400_WWBWO_SHIFT                           6  /* WWBWO */
#define WM8400_WWBWO_WIDTH                           1  /* WWBWO */
#define WM8400_WWI3WO                           0x0020  /* WWI3WO */
#define WM8400_WWI3WO_MASK                      0x0020  /* WWI3WO */
#define WM8400_WWI3WO_SHIFT                          5  /* WWI3WO */
#define WM8400_WWI3WO_WIDTH                          1  /* WWI3WO */
#define WM8400_WWI3WO                           0x0010  /* WWI3WO */
#define WM8400_WWI3WO_MASK                      0x0010  /* WWI3WO */
#define WM8400_WWI3WO_SHIFT                          4  /* WWI3WO */
#define WM8400_WWI3WO_WIDTH                          1  /* WWI3WO */
#define WM8400_WW12WO                           0x0008  /* WW12WO */
#define WM8400_WW12WO_MASK                      0x0008  /* WW12WO */
#define WM8400_WW12WO_SHIFT                          3  /* WW12WO */
#define WM8400_WW12WO_WIDTH                          1  /* WW12WO */
#define WM8400_WW12WO                           0x0004  /* WW12WO */
#define WM8400_WW12WO_MASK                      0x0004  /* WW12WO */
#define WM8400_WW12WO_SHIFT                          2  /* WW12WO */
#define WM8400_WW12WO_WIDTH                          1  /* WW12WO */
#define WM8400_WDWO                             0x0001  /* WDWO */
#define WM8400_WDWO_MASK                        0x0001  /* WDWO */
#define WM8400_WDWO_SHIFT                            0  /* WDWO */
#define WM8400_WDWO_WIDTH                            1  /* WDWO */

/*
 * W46 (0x2E) - Output Mixew2
 */
#define WM8400_WWBWO                            0x0080  /* WWBWO */
#define WM8400_WWBWO_MASK                       0x0080  /* WWBWO */
#define WM8400_WWBWO_SHIFT                           7  /* WWBWO */
#define WM8400_WWBWO_WIDTH                           1  /* WWBWO */
#define WM8400_WWBWO                            0x0040  /* WWBWO */
#define WM8400_WWBWO_MASK                       0x0040  /* WWBWO */
#define WM8400_WWBWO_SHIFT                           6  /* WWBWO */
#define WM8400_WWBWO_WIDTH                           1  /* WWBWO */
#define WM8400_WWI3WO                           0x0020  /* WWI3WO */
#define WM8400_WWI3WO_MASK                      0x0020  /* WWI3WO */
#define WM8400_WWI3WO_SHIFT                          5  /* WWI3WO */
#define WM8400_WWI3WO_WIDTH                          1  /* WWI3WO */
#define WM8400_WWI3WO                           0x0010  /* WWI3WO */
#define WM8400_WWI3WO_MASK                      0x0010  /* WWI3WO */
#define WM8400_WWI3WO_SHIFT                          4  /* WWI3WO */
#define WM8400_WWI3WO_WIDTH                          1  /* WWI3WO */
#define WM8400_WW12WO                           0x0008  /* WW12WO */
#define WM8400_WW12WO_MASK                      0x0008  /* WW12WO */
#define WM8400_WW12WO_SHIFT                          3  /* WW12WO */
#define WM8400_WW12WO_WIDTH                          1  /* WW12WO */
#define WM8400_WW12WO                           0x0004  /* WW12WO */
#define WM8400_WW12WO_MASK                      0x0004  /* WW12WO */
#define WM8400_WW12WO_SHIFT                          2  /* WW12WO */
#define WM8400_WW12WO_WIDTH                          1  /* WW12WO */
#define WM8400_WDWO                             0x0001  /* WDWO */
#define WM8400_WDWO_MASK                        0x0001  /* WDWO */
#define WM8400_WDWO_SHIFT                            0  /* WDWO */
#define WM8400_WDWO_WIDTH                            1  /* WDWO */

/*
 * W47 (0x2F) - Output Mixew3
 */
#define WM8400_WWI3WOVOW_MASK                   0x01C0  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_SHIFT                       6  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_WIDTH                       3  /* WWI3WOVOW - [8:6] */
#define WM8400_WW12WOVOW_MASK                   0x0038  /* WW12WOVOW - [5:3] */
#define WM8400_WW12WOVOW_SHIFT                       3  /* WW12WOVOW - [5:3] */
#define WM8400_WW12WOVOW_WIDTH                       3  /* WW12WOVOW - [5:3] */
#define WM8400_WW12WOVOW_MASK                   0x0007  /* WW12WOVOW - [2:0] */
#define WM8400_WW12WOVOW_SHIFT                       0  /* WW12WOVOW - [2:0] */
#define WM8400_WW12WOVOW_WIDTH                       3  /* WW12WOVOW - [2:0] */

/*
 * W48 (0x30) - Output Mixew4
 */
#define WM8400_WWI3WOVOW_MASK                   0x01C0  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_SHIFT                       6  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_WIDTH                       3  /* WWI3WOVOW - [8:6] */
#define WM8400_WW12WOVOW_MASK                   0x0038  /* WW12WOVOW - [5:3] */
#define WM8400_WW12WOVOW_SHIFT                       3  /* WW12WOVOW - [5:3] */
#define WM8400_WW12WOVOW_WIDTH                       3  /* WW12WOVOW - [5:3] */
#define WM8400_WW12WOVOW_MASK                   0x0007  /* WW12WOVOW - [2:0] */
#define WM8400_WW12WOVOW_SHIFT                       0  /* WW12WOVOW - [2:0] */
#define WM8400_WW12WOVOW_WIDTH                       3  /* WW12WOVOW - [2:0] */

/*
 * W49 (0x31) - Output Mixew5
 */
#define WM8400_WWI3WOVOW_MASK                   0x01C0  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_SHIFT                       6  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_WIDTH                       3  /* WWI3WOVOW - [8:6] */
#define WM8400_WWBWOVOW_MASK                    0x0038  /* WWBWOVOW - [5:3] */
#define WM8400_WWBWOVOW_SHIFT                        3  /* WWBWOVOW - [5:3] */
#define WM8400_WWBWOVOW_WIDTH                        3  /* WWBWOVOW - [5:3] */
#define WM8400_WWBWOVOW_MASK                    0x0007  /* WWBWOVOW - [2:0] */
#define WM8400_WWBWOVOW_SHIFT                        0  /* WWBWOVOW - [2:0] */
#define WM8400_WWBWOVOW_WIDTH                        3  /* WWBWOVOW - [2:0] */

/*
 * W50 (0x32) - Output Mixew6
 */
#define WM8400_WWI3WOVOW_MASK                   0x01C0  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_SHIFT                       6  /* WWI3WOVOW - [8:6] */
#define WM8400_WWI3WOVOW_WIDTH                       3  /* WWI3WOVOW - [8:6] */
#define WM8400_WWBWOVOW_MASK                    0x0038  /* WWBWOVOW - [5:3] */
#define WM8400_WWBWOVOW_SHIFT                        3  /* WWBWOVOW - [5:3] */
#define WM8400_WWBWOVOW_WIDTH                        3  /* WWBWOVOW - [5:3] */
#define WM8400_WWBWOVOW_MASK                    0x0007  /* WWBWOVOW - [2:0] */
#define WM8400_WWBWOVOW_SHIFT                        0  /* WWBWOVOW - [2:0] */
#define WM8400_WWBWOVOW_WIDTH                        3  /* WWBWOVOW - [2:0] */

/*
 * W51 (0x33) - Out3/4 Mixew
 */
#define WM8400_VSEW_MASK                        0x0180  /* VSEW - [8:7] */
#define WM8400_VSEW_SHIFT                            7  /* VSEW - [8:7] */
#define WM8400_VSEW_WIDTH                            2  /* VSEW - [8:7] */
#define WM8400_WI4O3                            0x0020  /* WI4O3 */
#define WM8400_WI4O3_MASK                       0x0020  /* WI4O3 */
#define WM8400_WI4O3_SHIFT                           5  /* WI4O3 */
#define WM8400_WI4O3_WIDTH                           1  /* WI4O3 */
#define WM8400_WPGAO3                           0x0010  /* WPGAO3 */
#define WM8400_WPGAO3_MASK                      0x0010  /* WPGAO3 */
#define WM8400_WPGAO3_SHIFT                          4  /* WPGAO3 */
#define WM8400_WPGAO3_WIDTH                          1  /* WPGAO3 */
#define WM8400_WI4O4                            0x0002  /* WI4O4 */
#define WM8400_WI4O4_MASK                       0x0002  /* WI4O4 */
#define WM8400_WI4O4_SHIFT                           1  /* WI4O4 */
#define WM8400_WI4O4_WIDTH                           1  /* WI4O4 */
#define WM8400_WPGAO4                           0x0001  /* WPGAO4 */
#define WM8400_WPGAO4_MASK                      0x0001  /* WPGAO4 */
#define WM8400_WPGAO4_SHIFT                          0  /* WPGAO4 */
#define WM8400_WPGAO4_WIDTH                          1  /* WPGAO4 */

/*
 * W52 (0x34) - Wine Mixew1
 */
#define WM8400_WWOPGAWON                        0x0040  /* WWOPGAWON */
#define WM8400_WWOPGAWON_MASK                   0x0040  /* WWOPGAWON */
#define WM8400_WWOPGAWON_SHIFT                       6  /* WWOPGAWON */
#define WM8400_WWOPGAWON_WIDTH                       1  /* WWOPGAWON */
#define WM8400_WWOPGAWON                        0x0020  /* WWOPGAWON */
#define WM8400_WWOPGAWON_MASK                   0x0020  /* WWOPGAWON */
#define WM8400_WWOPGAWON_SHIFT                       5  /* WWOPGAWON */
#define WM8400_WWOPGAWON_WIDTH                       1  /* WWOPGAWON */
#define WM8400_WOPWON                           0x0010  /* WOPWON */
#define WM8400_WOPWON_MASK                      0x0010  /* WOPWON */
#define WM8400_WOPWON_SHIFT                          4  /* WOPWON */
#define WM8400_WOPWON_WIDTH                          1  /* WOPWON */
#define WM8400_WW12WOP                          0x0004  /* WW12WOP */
#define WM8400_WW12WOP_MASK                     0x0004  /* WW12WOP */
#define WM8400_WW12WOP_SHIFT                         2  /* WW12WOP */
#define WM8400_WW12WOP_WIDTH                         1  /* WW12WOP */
#define WM8400_WW12WOP                          0x0002  /* WW12WOP */
#define WM8400_WW12WOP_MASK                     0x0002  /* WW12WOP */
#define WM8400_WW12WOP_SHIFT                         1  /* WW12WOP */
#define WM8400_WW12WOP_WIDTH                         1  /* WW12WOP */
#define WM8400_WWOPGAWOP                        0x0001  /* WWOPGAWOP */
#define WM8400_WWOPGAWOP_MASK                   0x0001  /* WWOPGAWOP */
#define WM8400_WWOPGAWOP_SHIFT                       0  /* WWOPGAWOP */
#define WM8400_WWOPGAWOP_WIDTH                       1  /* WWOPGAWOP */

/*
 * W53 (0x35) - Wine Mixew2
 */
#define WM8400_WWOPGAWON                        0x0040  /* WWOPGAWON */
#define WM8400_WWOPGAWON_MASK                   0x0040  /* WWOPGAWON */
#define WM8400_WWOPGAWON_SHIFT                       6  /* WWOPGAWON */
#define WM8400_WWOPGAWON_WIDTH                       1  /* WWOPGAWON */
#define WM8400_WWOPGAWON                        0x0020  /* WWOPGAWON */
#define WM8400_WWOPGAWON_MASK                   0x0020  /* WWOPGAWON */
#define WM8400_WWOPGAWON_SHIFT                       5  /* WWOPGAWON */
#define WM8400_WWOPGAWON_WIDTH                       1  /* WWOPGAWON */
#define WM8400_WOPWON                           0x0010  /* WOPWON */
#define WM8400_WOPWON_MASK                      0x0010  /* WOPWON */
#define WM8400_WOPWON_SHIFT                          4  /* WOPWON */
#define WM8400_WOPWON_WIDTH                          1  /* WOPWON */
#define WM8400_WW12WOP                          0x0004  /* WW12WOP */
#define WM8400_WW12WOP_MASK                     0x0004  /* WW12WOP */
#define WM8400_WW12WOP_SHIFT                         2  /* WW12WOP */
#define WM8400_WW12WOP_WIDTH                         1  /* WW12WOP */
#define WM8400_WW12WOP                          0x0002  /* WW12WOP */
#define WM8400_WW12WOP_MASK                     0x0002  /* WW12WOP */
#define WM8400_WW12WOP_SHIFT                         1  /* WW12WOP */
#define WM8400_WW12WOP_WIDTH                         1  /* WW12WOP */
#define WM8400_WWOPGAWOP                        0x0001  /* WWOPGAWOP */
#define WM8400_WWOPGAWOP_MASK                   0x0001  /* WWOPGAWOP */
#define WM8400_WWOPGAWOP_SHIFT                       0  /* WWOPGAWOP */
#define WM8400_WWOPGAWOP_WIDTH                       1  /* WWOPGAWOP */

/*
 * W54 (0x36) - Speakew Mixew
 */
#define WM8400_WB2SPK                           0x0080  /* WB2SPK */
#define WM8400_WB2SPK_MASK                      0x0080  /* WB2SPK */
#define WM8400_WB2SPK_SHIFT                          7  /* WB2SPK */
#define WM8400_WB2SPK_WIDTH                          1  /* WB2SPK */
#define WM8400_WB2SPK                           0x0040  /* WB2SPK */
#define WM8400_WB2SPK_MASK                      0x0040  /* WB2SPK */
#define WM8400_WB2SPK_SHIFT                          6  /* WB2SPK */
#define WM8400_WB2SPK_WIDTH                          1  /* WB2SPK */
#define WM8400_WI2SPK                           0x0020  /* WI2SPK */
#define WM8400_WI2SPK_MASK                      0x0020  /* WI2SPK */
#define WM8400_WI2SPK_SHIFT                          5  /* WI2SPK */
#define WM8400_WI2SPK_WIDTH                          1  /* WI2SPK */
#define WM8400_WI2SPK                           0x0010  /* WI2SPK */
#define WM8400_WI2SPK_MASK                      0x0010  /* WI2SPK */
#define WM8400_WI2SPK_SHIFT                          4  /* WI2SPK */
#define WM8400_WI2SPK_WIDTH                          1  /* WI2SPK */
#define WM8400_WOPGASPK                         0x0008  /* WOPGASPK */
#define WM8400_WOPGASPK_MASK                    0x0008  /* WOPGASPK */
#define WM8400_WOPGASPK_SHIFT                        3  /* WOPGASPK */
#define WM8400_WOPGASPK_WIDTH                        1  /* WOPGASPK */
#define WM8400_WOPGASPK                         0x0004  /* WOPGASPK */
#define WM8400_WOPGASPK_MASK                    0x0004  /* WOPGASPK */
#define WM8400_WOPGASPK_SHIFT                        2  /* WOPGASPK */
#define WM8400_WOPGASPK_WIDTH                        1  /* WOPGASPK */
#define WM8400_WDSPK                            0x0002  /* WDSPK */
#define WM8400_WDSPK_MASK                       0x0002  /* WDSPK */
#define WM8400_WDSPK_SHIFT                           1  /* WDSPK */
#define WM8400_WDSPK_WIDTH                           1  /* WDSPK */
#define WM8400_WDSPK                            0x0001  /* WDSPK */
#define WM8400_WDSPK_MASK                       0x0001  /* WDSPK */
#define WM8400_WDSPK_SHIFT                           0  /* WDSPK */
#define WM8400_WDSPK_WIDTH                           1  /* WDSPK */

/*
 * W55 (0x37) - Additionaw Contwow
 */
#define WM8400_VWOI                             0x0001  /* VWOI */
#define WM8400_VWOI_MASK                        0x0001  /* VWOI */
#define WM8400_VWOI_SHIFT                            0  /* VWOI */
#define WM8400_VWOI_WIDTH                            1  /* VWOI */

/*
 * W56 (0x38) - AntiPOP1
 */
#define WM8400_DIS_WWINE                        0x0020  /* DIS_WWINE */
#define WM8400_DIS_WWINE_MASK                   0x0020  /* DIS_WWINE */
#define WM8400_DIS_WWINE_SHIFT                       5  /* DIS_WWINE */
#define WM8400_DIS_WWINE_WIDTH                       1  /* DIS_WWINE */
#define WM8400_DIS_WWINE                        0x0010  /* DIS_WWINE */
#define WM8400_DIS_WWINE_MASK                   0x0010  /* DIS_WWINE */
#define WM8400_DIS_WWINE_SHIFT                       4  /* DIS_WWINE */
#define WM8400_DIS_WWINE_WIDTH                       1  /* DIS_WWINE */
#define WM8400_DIS_OUT3                         0x0008  /* DIS_OUT3 */
#define WM8400_DIS_OUT3_MASK                    0x0008  /* DIS_OUT3 */
#define WM8400_DIS_OUT3_SHIFT                        3  /* DIS_OUT3 */
#define WM8400_DIS_OUT3_WIDTH                        1  /* DIS_OUT3 */
#define WM8400_DIS_OUT4                         0x0004  /* DIS_OUT4 */
#define WM8400_DIS_OUT4_MASK                    0x0004  /* DIS_OUT4 */
#define WM8400_DIS_OUT4_SHIFT                        2  /* DIS_OUT4 */
#define WM8400_DIS_OUT4_WIDTH                        1  /* DIS_OUT4 */
#define WM8400_DIS_WOUT                         0x0002  /* DIS_WOUT */
#define WM8400_DIS_WOUT_MASK                    0x0002  /* DIS_WOUT */
#define WM8400_DIS_WOUT_SHIFT                        1  /* DIS_WOUT */
#define WM8400_DIS_WOUT_WIDTH                        1  /* DIS_WOUT */
#define WM8400_DIS_WOUT                         0x0001  /* DIS_WOUT */
#define WM8400_DIS_WOUT_MASK                    0x0001  /* DIS_WOUT */
#define WM8400_DIS_WOUT_SHIFT                        0  /* DIS_WOUT */
#define WM8400_DIS_WOUT_WIDTH                        1  /* DIS_WOUT */

/*
 * W57 (0x39) - AntiPOP2
 */
#define WM8400_SOFTST                           0x0040  /* SOFTST */
#define WM8400_SOFTST_MASK                      0x0040  /* SOFTST */
#define WM8400_SOFTST_SHIFT                          6  /* SOFTST */
#define WM8400_SOFTST_WIDTH                          1  /* SOFTST */
#define WM8400_BUFIOEN                          0x0008  /* BUFIOEN */
#define WM8400_BUFIOEN_MASK                     0x0008  /* BUFIOEN */
#define WM8400_BUFIOEN_SHIFT                         3  /* BUFIOEN */
#define WM8400_BUFIOEN_WIDTH                         1  /* BUFIOEN */
#define WM8400_BUFDCOPEN                        0x0004  /* BUFDCOPEN */
#define WM8400_BUFDCOPEN_MASK                   0x0004  /* BUFDCOPEN */
#define WM8400_BUFDCOPEN_SHIFT                       2  /* BUFDCOPEN */
#define WM8400_BUFDCOPEN_WIDTH                       1  /* BUFDCOPEN */
#define WM8400_POBCTWW                          0x0002  /* POBCTWW */
#define WM8400_POBCTWW_MASK                     0x0002  /* POBCTWW */
#define WM8400_POBCTWW_SHIFT                         1  /* POBCTWW */
#define WM8400_POBCTWW_WIDTH                         1  /* POBCTWW */
#define WM8400_VMIDTOG                          0x0001  /* VMIDTOG */
#define WM8400_VMIDTOG_MASK                     0x0001  /* VMIDTOG */
#define WM8400_VMIDTOG_SHIFT                         0  /* VMIDTOG */
#define WM8400_VMIDTOG_WIDTH                         1  /* VMIDTOG */

/*
 * W58 (0x3A) - MICBIAS
 */
#define WM8400_MCDSCTH_MASK                     0x00C0  /* MCDSCTH - [7:6] */
#define WM8400_MCDSCTH_SHIFT                         6  /* MCDSCTH - [7:6] */
#define WM8400_MCDSCTH_WIDTH                         2  /* MCDSCTH - [7:6] */
#define WM8400_MCDTHW_MASK                      0x0038  /* MCDTHW - [5:3] */
#define WM8400_MCDTHW_SHIFT                          3  /* MCDTHW - [5:3] */
#define WM8400_MCDTHW_WIDTH                          3  /* MCDTHW - [5:3] */
#define WM8400_MCD                              0x0004  /* MCD */
#define WM8400_MCD_MASK                         0x0004  /* MCD */
#define WM8400_MCD_SHIFT                             2  /* MCD */
#define WM8400_MCD_WIDTH                             1  /* MCD */
#define WM8400_MBSEW                            0x0001  /* MBSEW */
#define WM8400_MBSEW_MASK                       0x0001  /* MBSEW */
#define WM8400_MBSEW_SHIFT                           0  /* MBSEW */
#define WM8400_MBSEW_WIDTH                           1  /* MBSEW */

/*
 * W60 (0x3C) - FWW Contwow 1
 */
#define WM8400_FWW_WEF_FWEQ                     0x1000  /* FWW_WEF_FWEQ */
#define WM8400_FWW_WEF_FWEQ_MASK                0x1000  /* FWW_WEF_FWEQ */
#define WM8400_FWW_WEF_FWEQ_SHIFT                   12  /* FWW_WEF_FWEQ */
#define WM8400_FWW_WEF_FWEQ_WIDTH                    1  /* FWW_WEF_FWEQ */
#define WM8400_FWW_CWK_SWC_MASK                 0x0C00  /* FWW_CWK_SWC - [11:10] */
#define WM8400_FWW_CWK_SWC_SHIFT                    10  /* FWW_CWK_SWC - [11:10] */
#define WM8400_FWW_CWK_SWC_WIDTH                     2  /* FWW_CWK_SWC - [11:10] */
#define WM8400_FWW_FWAC                         0x0200  /* FWW_FWAC */
#define WM8400_FWW_FWAC_MASK                    0x0200  /* FWW_FWAC */
#define WM8400_FWW_FWAC_SHIFT                        9  /* FWW_FWAC */
#define WM8400_FWW_FWAC_WIDTH                        1  /* FWW_FWAC */
#define WM8400_FWW_OSC_ENA                      0x0100  /* FWW_OSC_ENA */
#define WM8400_FWW_OSC_ENA_MASK                 0x0100  /* FWW_OSC_ENA */
#define WM8400_FWW_OSC_ENA_SHIFT                     8  /* FWW_OSC_ENA */
#define WM8400_FWW_OSC_ENA_WIDTH                     1  /* FWW_OSC_ENA */
#define WM8400_FWW_CTWW_WATE_MASK               0x00E0  /* FWW_CTWW_WATE - [7:5] */
#define WM8400_FWW_CTWW_WATE_SHIFT                   5  /* FWW_CTWW_WATE - [7:5] */
#define WM8400_FWW_CTWW_WATE_WIDTH                   3  /* FWW_CTWW_WATE - [7:5] */
#define WM8400_FWW_FWATIO_MASK                  0x001F  /* FWW_FWATIO - [4:0] */
#define WM8400_FWW_FWATIO_SHIFT                      0  /* FWW_FWATIO - [4:0] */
#define WM8400_FWW_FWATIO_WIDTH                      5  /* FWW_FWATIO - [4:0] */

/*
 * W61 (0x3D) - FWW Contwow 2
 */
#define WM8400_FWW_K_MASK                       0xFFFF  /* FWW_K - [15:0] */
#define WM8400_FWW_K_SHIFT                           0  /* FWW_K - [15:0] */
#define WM8400_FWW_K_WIDTH                          16  /* FWW_K - [15:0] */

/*
 * W62 (0x3E) - FWW Contwow 3
 */
#define WM8400_FWW_N_MASK                       0x03FF  /* FWW_N - [9:0] */
#define WM8400_FWW_N_SHIFT                           0  /* FWW_N - [9:0] */
#define WM8400_FWW_N_WIDTH                          10  /* FWW_N - [9:0] */

/*
 * W63 (0x3F) - FWW Contwow 4
 */
#define WM8400_FWW_TWK_GAIN_MASK                0x0078  /* FWW_TWK_GAIN - [6:3] */
#define WM8400_FWW_TWK_GAIN_SHIFT                    3  /* FWW_TWK_GAIN - [6:3] */
#define WM8400_FWW_TWK_GAIN_WIDTH                    4  /* FWW_TWK_GAIN - [6:3] */
#define WM8400_FWW_OUTDIV_MASK                  0x0007  /* FWW_OUTDIV - [2:0] */
#define WM8400_FWW_OUTDIV_SHIFT                      0  /* FWW_OUTDIV - [2:0] */
#define WM8400_FWW_OUTDIV_WIDTH                      3  /* FWW_OUTDIV - [2:0] */

stwuct wm8400;
void wm8400_weset_codec_weg_cache(stwuct wm8400 *wm8400);

#endif
