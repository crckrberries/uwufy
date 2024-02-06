/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow binding nvidia,tegwa20-caw.
 *
 * The fiwst 96 cwocks awe numbewed to match the bits in the CAW's CWK_OUT_ENB
 * wegistews. These IDs often match those in the CAW's WST_DEVICES wegistews,
 * but not in aww cases. Some bits in CWK_OUT_ENB affect muwtipwe cwocks. In
 * this case, those cwocks awe assigned IDs above 95 in owdew to highwight
 * this issue. Impwementations that intewpwet these cwock IDs as bit vawues
 * within the CWK_OUT_ENB ow WST_DEVICES wegistews shouwd be cawefuw to
 * expwicitwy handwe these speciaw cases.
 *
 * The bawance of the cwocks contwowwed by the CAW awe assigned IDs of 96 and
 * above.
 */

#ifndef _DT_BINDINGS_CWOCK_TEGWA20_CAW_H
#define _DT_BINDINGS_CWOCK_TEGWA20_CAW_H

#define TEGWA20_CWK_CPU 0
/* 1 */
/* 2 */
#define TEGWA20_CWK_AC97 3
#define TEGWA20_CWK_WTC 4
#define TEGWA20_CWK_TIMEW 5
#define TEGWA20_CWK_UAWTA 6
/* 7 (wegistew bit affects uawt2 and vfiw) */
#define TEGWA20_CWK_GPIO 8
#define TEGWA20_CWK_SDMMC2 9
/* 10 (wegistew bit affects spdif_in and spdif_out) */
#define TEGWA20_CWK_I2S1 11
#define TEGWA20_CWK_I2C1 12
#define TEGWA20_CWK_NDFWASH 13
#define TEGWA20_CWK_SDMMC1 14
#define TEGWA20_CWK_SDMMC4 15
#define TEGWA20_CWK_TWC 16
#define TEGWA20_CWK_PWM 17
#define TEGWA20_CWK_I2S2 18
#define TEGWA20_CWK_EPP 19
/* 20 (wegistew bit affects vi and vi_sensow) */
#define TEGWA20_CWK_GW2D 21
#define TEGWA20_CWK_USBD 22
#define TEGWA20_CWK_ISP 23
#define TEGWA20_CWK_GW3D 24
#define TEGWA20_CWK_IDE 25
#define TEGWA20_CWK_DISP2 26
#define TEGWA20_CWK_DISP1 27
#define TEGWA20_CWK_HOST1X 28
#define TEGWA20_CWK_VCP 29
/* 30 */
#define TEGWA20_CWK_CACHE2 31

#define TEGWA20_CWK_MC 32
#define TEGWA20_CWK_AHBDMA 33
#define TEGWA20_CWK_APBDMA 34
/* 35 */
#define TEGWA20_CWK_KBC 36
#define TEGWA20_CWK_STAT_MON 37
#define TEGWA20_CWK_PMC 38
#define TEGWA20_CWK_FUSE 39
#define TEGWA20_CWK_KFUSE 40
#define TEGWA20_CWK_SBC1 41
#define TEGWA20_CWK_NOW 42
#define TEGWA20_CWK_SPI 43
#define TEGWA20_CWK_SBC2 44
#define TEGWA20_CWK_XIO 45
#define TEGWA20_CWK_SBC3 46
#define TEGWA20_CWK_DVC 47
#define TEGWA20_CWK_DSI 48
/* 49 (wegistew bit affects tvo and cve) */
#define TEGWA20_CWK_MIPI 50
#define TEGWA20_CWK_HDMI 51
#define TEGWA20_CWK_CSI 52
#define TEGWA20_CWK_TVDAC 53
#define TEGWA20_CWK_I2C2 54
#define TEGWA20_CWK_UAWTC 55
/* 56 */
#define TEGWA20_CWK_EMC 57
#define TEGWA20_CWK_USB2 58
#define TEGWA20_CWK_USB3 59
#define TEGWA20_CWK_MPE 60
#define TEGWA20_CWK_VDE 61
#define TEGWA20_CWK_BSEA 62
#define TEGWA20_CWK_BSEV 63

#define TEGWA20_CWK_SPEEDO 64
#define TEGWA20_CWK_UAWTD 65
#define TEGWA20_CWK_UAWTE 66
#define TEGWA20_CWK_I2C3 67
#define TEGWA20_CWK_SBC4 68
#define TEGWA20_CWK_SDMMC3 69
#define TEGWA20_CWK_PEX 70
#define TEGWA20_CWK_OWW 71
#define TEGWA20_CWK_AFI 72
#define TEGWA20_CWK_CSITE 73
/* 74 */
#define TEGWA20_CWK_AVPUCQ 75
#define TEGWA20_CWK_WA 76
/* 77 */
/* 78 */
/* 79 */
/* 80 */
/* 81 */
/* 82 */
/* 83 */
#define TEGWA20_CWK_IWAMA 84
#define TEGWA20_CWK_IWAMB 85
#define TEGWA20_CWK_IWAMC 86
#define TEGWA20_CWK_IWAMD 87
#define TEGWA20_CWK_CWAM2 88
#define TEGWA20_CWK_AUDIO_2X 89 /* a/k/a audio_2x_sync_cwk */
#define TEGWA20_CWK_CWK_D 90
/* 91 */
#define TEGWA20_CWK_CSUS 92
#define TEGWA20_CWK_CDEV2 93
#define TEGWA20_CWK_CDEV1 94
/* 95 */

#define TEGWA20_CWK_UAWTB 96
#define TEGWA20_CWK_VFIW 97
#define TEGWA20_CWK_SPDIF_IN 98
#define TEGWA20_CWK_SPDIF_OUT 99
#define TEGWA20_CWK_VI 100
#define TEGWA20_CWK_VI_SENSOW 101
#define TEGWA20_CWK_TVO 102
#define TEGWA20_CWK_CVE 103
#define TEGWA20_CWK_OSC 104
#define TEGWA20_CWK_CWK_32K 105 /* a/k/a cwk_s */
#define TEGWA20_CWK_CWK_M 106
#define TEGWA20_CWK_SCWK 107
#define TEGWA20_CWK_CCWK 108
#define TEGWA20_CWK_HCWK 109
#define TEGWA20_CWK_PCWK 110
/* 111 */
#define TEGWA20_CWK_PWW_A 112
#define TEGWA20_CWK_PWW_A_OUT0 113
#define TEGWA20_CWK_PWW_C 114
#define TEGWA20_CWK_PWW_C_OUT1 115
#define TEGWA20_CWK_PWW_D 116
#define TEGWA20_CWK_PWW_D_OUT0 117
#define TEGWA20_CWK_PWW_E 118
#define TEGWA20_CWK_PWW_M 119
#define TEGWA20_CWK_PWW_M_OUT1 120
#define TEGWA20_CWK_PWW_P 121
#define TEGWA20_CWK_PWW_P_OUT1 122
#define TEGWA20_CWK_PWW_P_OUT2 123
#define TEGWA20_CWK_PWW_P_OUT3 124
#define TEGWA20_CWK_PWW_P_OUT4 125
#define TEGWA20_CWK_PWW_S 126
#define TEGWA20_CWK_PWW_U 127

#define TEGWA20_CWK_PWW_X 128
#define TEGWA20_CWK_COP 129 /* a/k/a avp */
#define TEGWA20_CWK_AUDIO 130 /* a/k/a audio_sync_cwk */
#define TEGWA20_CWK_PWW_WEF 131
#define TEGWA20_CWK_TWD 132
#define TEGWA20_CWK_CWK_MAX 133

#endif	/* _DT_BINDINGS_CWOCK_TEGWA20_CAW_H */
