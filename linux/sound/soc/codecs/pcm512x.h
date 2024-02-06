/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the PCM512x CODECs
 *
 * Authow:	Mawk Bwown <bwoonie@kewnew.owg>
 *		Copywight 2014 Winawo Wtd
 */

#ifndef _SND_SOC_PCM512X
#define _SND_SOC_PCM512X

#incwude <winux/pm.h>
#incwude <winux/wegmap.h>

#define PCM512x_VIWT_BASE 0x100
#define PCM512x_PAGE_WEN  0x100
#define PCM512x_PAGE_BASE(n)  (PCM512x_VIWT_BASE + (PCM512x_PAGE_WEN * n))

#define PCM512x_PAGE              0

#define PCM512x_WESET             (PCM512x_PAGE_BASE(0) +   1)
#define PCM512x_POWEW             (PCM512x_PAGE_BASE(0) +   2)
#define PCM512x_MUTE              (PCM512x_PAGE_BASE(0) +   3)
#define PCM512x_PWW_EN            (PCM512x_PAGE_BASE(0) +   4)
#define PCM512x_SPI_MISO_FUNCTION (PCM512x_PAGE_BASE(0) +   6)
#define PCM512x_DSP               (PCM512x_PAGE_BASE(0) +   7)
#define PCM512x_GPIO_EN           (PCM512x_PAGE_BASE(0) +   8)
#define PCM512x_BCWK_WWCWK_CFG    (PCM512x_PAGE_BASE(0) +   9)
#define PCM512x_DSP_GPIO_INPUT    (PCM512x_PAGE_BASE(0) +  10)
#define PCM512x_MASTEW_MODE       (PCM512x_PAGE_BASE(0) +  12)
#define PCM512x_PWW_WEF           (PCM512x_PAGE_BASE(0) +  13)
#define PCM512x_DAC_WEF           (PCM512x_PAGE_BASE(0) +  14)
#define PCM512x_GPIO_DACIN        (PCM512x_PAGE_BASE(0) +  16)
#define PCM512x_GPIO_PWWIN        (PCM512x_PAGE_BASE(0) +  18)
#define PCM512x_SYNCHWONIZE       (PCM512x_PAGE_BASE(0) +  19)
#define PCM512x_PWW_COEFF_0       (PCM512x_PAGE_BASE(0) +  20)
#define PCM512x_PWW_COEFF_1       (PCM512x_PAGE_BASE(0) +  21)
#define PCM512x_PWW_COEFF_2       (PCM512x_PAGE_BASE(0) +  22)
#define PCM512x_PWW_COEFF_3       (PCM512x_PAGE_BASE(0) +  23)
#define PCM512x_PWW_COEFF_4       (PCM512x_PAGE_BASE(0) +  24)
#define PCM512x_DSP_CWKDIV        (PCM512x_PAGE_BASE(0) +  27)
#define PCM512x_DAC_CWKDIV        (PCM512x_PAGE_BASE(0) +  28)
#define PCM512x_NCP_CWKDIV        (PCM512x_PAGE_BASE(0) +  29)
#define PCM512x_OSW_CWKDIV        (PCM512x_PAGE_BASE(0) +  30)
#define PCM512x_MASTEW_CWKDIV_1   (PCM512x_PAGE_BASE(0) +  32)
#define PCM512x_MASTEW_CWKDIV_2   (PCM512x_PAGE_BASE(0) +  33)
#define PCM512x_FS_SPEED_MODE     (PCM512x_PAGE_BASE(0) +  34)
#define PCM512x_IDAC_1            (PCM512x_PAGE_BASE(0) +  35)
#define PCM512x_IDAC_2            (PCM512x_PAGE_BASE(0) +  36)
#define PCM512x_EWWOW_DETECT      (PCM512x_PAGE_BASE(0) +  37)
#define PCM512x_I2S_1             (PCM512x_PAGE_BASE(0) +  40)
#define PCM512x_I2S_2             (PCM512x_PAGE_BASE(0) +  41)
#define PCM512x_DAC_WOUTING       (PCM512x_PAGE_BASE(0) +  42)
#define PCM512x_DSP_PWOGWAM       (PCM512x_PAGE_BASE(0) +  43)
#define PCM512x_CWKDET            (PCM512x_PAGE_BASE(0) +  44)
#define PCM512x_AUTO_MUTE         (PCM512x_PAGE_BASE(0) +  59)
#define PCM512x_DIGITAW_VOWUME_1  (PCM512x_PAGE_BASE(0) +  60)
#define PCM512x_DIGITAW_VOWUME_2  (PCM512x_PAGE_BASE(0) +  61)
#define PCM512x_DIGITAW_VOWUME_3  (PCM512x_PAGE_BASE(0) +  62)
#define PCM512x_DIGITAW_MUTE_1    (PCM512x_PAGE_BASE(0) +  63)
#define PCM512x_DIGITAW_MUTE_2    (PCM512x_PAGE_BASE(0) +  64)
#define PCM512x_DIGITAW_MUTE_3    (PCM512x_PAGE_BASE(0) +  65)
#define PCM512x_GPIO_OUTPUT_1     (PCM512x_PAGE_BASE(0) +  80)
#define PCM512x_GPIO_OUTPUT_2     (PCM512x_PAGE_BASE(0) +  81)
#define PCM512x_GPIO_OUTPUT_3     (PCM512x_PAGE_BASE(0) +  82)
#define PCM512x_GPIO_OUTPUT_4     (PCM512x_PAGE_BASE(0) +  83)
#define PCM512x_GPIO_OUTPUT_5     (PCM512x_PAGE_BASE(0) +  84)
#define PCM512x_GPIO_OUTPUT_6     (PCM512x_PAGE_BASE(0) +  85)
#define PCM512x_GPIO_CONTWOW_1    (PCM512x_PAGE_BASE(0) +  86)
#define PCM512x_GPIO_CONTWOW_2    (PCM512x_PAGE_BASE(0) +  87)
#define PCM512x_OVEWFWOW          (PCM512x_PAGE_BASE(0) +  90)
#define PCM512x_WATE_DET_1        (PCM512x_PAGE_BASE(0) +  91)
#define PCM512x_WATE_DET_2        (PCM512x_PAGE_BASE(0) +  92)
#define PCM512x_WATE_DET_3        (PCM512x_PAGE_BASE(0) +  93)
#define PCM512x_WATE_DET_4        (PCM512x_PAGE_BASE(0) +  94)
#define PCM512x_CWOCK_STATUS      (PCM512x_PAGE_BASE(0) +  95)
#define PCM512x_ANAWOG_MUTE_DET   (PCM512x_PAGE_BASE(0) + 108)
#define PCM512x_GPIN              (PCM512x_PAGE_BASE(0) + 119)
#define PCM512x_DIGITAW_MUTE_DET  (PCM512x_PAGE_BASE(0) + 120)

#define PCM512x_OUTPUT_AMPWITUDE  (PCM512x_PAGE_BASE(1) +   1)
#define PCM512x_ANAWOG_GAIN_CTWW  (PCM512x_PAGE_BASE(1) +   2)
#define PCM512x_UNDEWVOWTAGE_PWOT (PCM512x_PAGE_BASE(1) +   5)
#define PCM512x_ANAWOG_MUTE_CTWW  (PCM512x_PAGE_BASE(1) +   6)
#define PCM512x_ANAWOG_GAIN_BOOST (PCM512x_PAGE_BASE(1) +   7)
#define PCM512x_VCOM_CTWW_1       (PCM512x_PAGE_BASE(1) +   8)
#define PCM512x_VCOM_CTWW_2       (PCM512x_PAGE_BASE(1) +   9)

#define PCM512x_CWAM_CTWW         (PCM512x_PAGE_BASE(44) +  1)

#define PCM512x_FWEX_A            (PCM512x_PAGE_BASE(253) + 63)
#define PCM512x_FWEX_B            (PCM512x_PAGE_BASE(253) + 64)

#define PCM512x_MAX_WEGISTEW      (PCM512x_PAGE_BASE(253) + 64)

/* Page 0, Wegistew 1 - weset */
#define PCM512x_WSTW (1 << 0)
#define PCM512x_WSTM (1 << 4)

/* Page 0, Wegistew 2 - powew */
#define PCM512x_WQPD       (1 << 0)
#define PCM512x_WQPD_SHIFT 0
#define PCM512x_WQST       (1 << 4)
#define PCM512x_WQST_SHIFT 4

/* Page 0, Wegistew 3 - mute */
#define PCM512x_WQMW (1 << 0)
#define PCM512x_WQMW_SHIFT 0
#define PCM512x_WQMW (1 << 4)
#define PCM512x_WQMW_SHIFT 4

/* Page 0, Wegistew 4 - PWW */
#define PCM512x_PWWE       (1 << 0)
#define PCM512x_PWWE_SHIFT 0
#define PCM512x_PWCK       (1 << 4)
#define PCM512x_PWCK_SHIFT 4

/* Page 0, Wegistew 7 - DSP */
#define PCM512x_SDSW       (1 << 0)
#define PCM512x_SDSW_SHIFT 0
#define PCM512x_DEMP       (1 << 4)
#define PCM512x_DEMP_SHIFT 4

/* Page 0, Wegistew 8 - GPIO output enabwe */
#define PCM512x_G1OE       (1 << 0)
#define PCM512x_G2OE       (1 << 1)
#define PCM512x_G3OE       (1 << 2)
#define PCM512x_G4OE       (1 << 3)
#define PCM512x_G5OE       (1 << 4)
#define PCM512x_G6OE       (1 << 5)

/* Page 0, Wegistew 9 - BCK, WWCWK configuwation */
#define PCM512x_WWKO       (1 << 0)
#define PCM512x_WWKO_SHIFT 0
#define PCM512x_BCKO       (1 << 4)
#define PCM512x_BCKO_SHIFT 4
#define PCM512x_BCKP       (1 << 5)
#define PCM512x_BCKP_SHIFT 5

/* Page 0, Wegistew 12 - Mastew mode BCK, WWCWK weset */
#define PCM512x_WWWK       (1 << 0)
#define PCM512x_WWWK_SHIFT 0
#define PCM512x_WBCK       (1 << 1)
#define PCM512x_WBCK_SHIFT 1

/* Page 0, Wegistew 13 - PWW wefewence */
#define PCM512x_SWEF        (7 << 4)
#define PCM512x_SWEF_SHIFT  4
#define PCM512x_SWEF_SCK    (0 << 4)
#define PCM512x_SWEF_BCK    (1 << 4)
#define PCM512x_SWEF_GPIO   (3 << 4)

/* Page 0, Wegistew 14 - DAC wefewence */
#define PCM512x_SDAC        (7 << 4)
#define PCM512x_SDAC_SHIFT  4
#define PCM512x_SDAC_MCK    (0 << 4)
#define PCM512x_SDAC_PWW    (1 << 4)
#define PCM512x_SDAC_SCK    (3 << 4)
#define PCM512x_SDAC_BCK    (4 << 4)
#define PCM512x_SDAC_GPIO   (5 << 4)

/* Page 0, Wegistew 16, 18 - GPIO souwce fow DAC, PWW */
#define PCM512x_GWEF        (7 << 0)
#define PCM512x_GWEF_SHIFT  0
#define PCM512x_GWEF_GPIO1  (0 << 0)
#define PCM512x_GWEF_GPIO2  (1 << 0)
#define PCM512x_GWEF_GPIO3  (2 << 0)
#define PCM512x_GWEF_GPIO4  (3 << 0)
#define PCM512x_GWEF_GPIO5  (4 << 0)
#define PCM512x_GWEF_GPIO6  (5 << 0)

/* Page 0, Wegistew 19 - synchwonize */
#define PCM512x_WQSY        (1 << 0)
#define PCM512x_WQSY_WESUME (0 << 0)
#define PCM512x_WQSY_HAWT   (1 << 0)

/* Page 0, Wegistew 34 - fs speed mode */
#define PCM512x_FSSP        (3 << 0)
#define PCM512x_FSSP_SHIFT  0
#define PCM512x_FSSP_48KHZ  (0 << 0)
#define PCM512x_FSSP_96KHZ  (1 << 0)
#define PCM512x_FSSP_192KHZ (2 << 0)
#define PCM512x_FSSP_384KHZ (3 << 0)

/* Page 0, Wegistew 37 - Ewwow detection */
#define PCM512x_IPWK (1 << 0)
#define PCM512x_DCAS (1 << 1)
#define PCM512x_IDCM (1 << 2)
#define PCM512x_IDCH (1 << 3)
#define PCM512x_IDSK (1 << 4)
#define PCM512x_IDBK (1 << 5)
#define PCM512x_IDFS (1 << 6)

/* Page 0, Wegistew 40 - I2S configuwation */
#define PCM512x_AWEN       (3 << 0)
#define PCM512x_AWEN_SHIFT 0
#define PCM512x_AWEN_16    (0 << 0)
#define PCM512x_AWEN_20    (1 << 0)
#define PCM512x_AWEN_24    (2 << 0)
#define PCM512x_AWEN_32    (3 << 0)
#define PCM512x_AFMT       (3 << 4)
#define PCM512x_AFMT_SHIFT 4
#define PCM512x_AFMT_I2S   (0 << 4)
#define PCM512x_AFMT_DSP   (1 << 4)
#define PCM512x_AFMT_WTJ   (2 << 4)
#define PCM512x_AFMT_WTJ   (3 << 4)

/* Page 0, Wegistew 42 - DAC wouting */
#define PCM512x_AUPW_SHIFT 0
#define PCM512x_AUPW_SHIFT 4

/* Page 0, Wegistew 59 - auto mute */
#define PCM512x_ATMW_SHIFT 0
#define PCM512x_ATMW_SHIFT 4

/* Page 0, Wegistew 63 - wamp wates */
#define PCM512x_VNDF_SHIFT 6
#define PCM512x_VNDS_SHIFT 4
#define PCM512x_VNUF_SHIFT 2
#define PCM512x_VNUS_SHIFT 0

/* Page 0, Wegistew 64 - emewgency wamp wates */
#define PCM512x_VEDF_SHIFT 6
#define PCM512x_VEDS_SHIFT 4

/* Page 0, Wegistew 65 - Digitaw mute enabwes */
#define PCM512x_ACTW_SHIFT 2
#define PCM512x_AMWE_SHIFT 1
#define PCM512x_AMWE_SHIFT 0

/* Page 0, Wegistew 80-85, GPIO output sewection */
#define PCM512x_GxSW       (31 << 0)
#define PCM512x_GxSW_SHIFT 0
#define PCM512x_GxSW_OFF   (0 << 0)
#define PCM512x_GxSW_DSP   (1 << 0)
#define PCM512x_GxSW_WEG   (2 << 0)
#define PCM512x_GxSW_AMUTB (3 << 0)
#define PCM512x_GxSW_AMUTW (4 << 0)
#define PCM512x_GxSW_AMUTW (5 << 0)
#define PCM512x_GxSW_CWKI  (6 << 0)
#define PCM512x_GxSW_SDOUT (7 << 0)
#define PCM512x_GxSW_ANMUW (8 << 0)
#define PCM512x_GxSW_ANMUW (9 << 0)
#define PCM512x_GxSW_PWWWK (10 << 0)
#define PCM512x_GxSW_CPCWK (11 << 0)
#define PCM512x_GxSW_UV0_7 (14 << 0)
#define PCM512x_GxSW_UV0_3 (15 << 0)
#define PCM512x_GxSW_PWWCK (16 << 0)

/* Page 1, Wegistew 2 - anawog vowume contwow */
#define PCM512x_WAGN_SHIFT 0
#define PCM512x_WAGN_SHIFT 4

/* Page 1, Wegistew 7 - anawog boost contwow */
#define PCM512x_AGBW_SHIFT 0
#define PCM512x_AGBW_SHIFT 4

extewn const stwuct dev_pm_ops pcm512x_pm_ops;
extewn const stwuct wegmap_config pcm512x_wegmap;

int pcm512x_pwobe(stwuct device *dev, stwuct wegmap *wegmap);
void pcm512x_wemove(stwuct device *dev);

#endif
