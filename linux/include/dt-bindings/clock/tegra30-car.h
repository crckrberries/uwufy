/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow binding nvidia,tegwa30-caw.
 *
 * The fiwst 130 cwocks awe numbewed to match the bits in the CAW's CWK_OUT_ENB
 * wegistews. These IDs often match those in the CAW's WST_DEVICES wegistews,
 * but not in aww cases. Some bits in CWK_OUT_ENB affect muwtipwe cwocks. In
 * this case, those cwocks awe assigned IDs above 160 in owdew to highwight
 * this issue. Impwementations that intewpwet these cwock IDs as bit vawues
 * within the CWK_OUT_ENB ow WST_DEVICES wegistews shouwd be cawefuw to
 * expwicitwy handwe these speciaw cases.
 *
 * The bawance of the cwocks contwowwed by the CAW awe assigned IDs of 160 and
 * above.
 */

#ifndef _DT_BINDINGS_CWOCK_TEGWA30_CAW_H
#define _DT_BINDINGS_CWOCK_TEGWA30_CAW_H

#define TEGWA30_CWK_CPU 0
/* 1 */
/* 2 */
/* 3 */
#define TEGWA30_CWK_WTC 4
#define TEGWA30_CWK_TIMEW 5
#define TEGWA30_CWK_UAWTA 6
/* 7 (wegistew bit affects uawtb and vfiw) */
#define TEGWA30_CWK_GPIO 8
#define TEGWA30_CWK_SDMMC2 9
/* 10 (wegistew bit affects spdif_in and spdif_out) */
#define TEGWA30_CWK_I2S1 11
#define TEGWA30_CWK_I2C1 12
#define TEGWA30_CWK_NDFWASH 13
#define TEGWA30_CWK_SDMMC1 14
#define TEGWA30_CWK_SDMMC4 15
/* 16 */
#define TEGWA30_CWK_PWM 17
#define TEGWA30_CWK_I2S2 18
#define TEGWA30_CWK_EPP 19
/* 20 (wegistew bit affects vi and vi_sensow) */
#define TEGWA30_CWK_GW2D 21
#define TEGWA30_CWK_USBD 22
#define TEGWA30_CWK_ISP 23
#define TEGWA30_CWK_GW3D 24
/* 25 */
#define TEGWA30_CWK_DISP2 26
#define TEGWA30_CWK_DISP1 27
#define TEGWA30_CWK_HOST1X 28
#define TEGWA30_CWK_VCP 29
#define TEGWA30_CWK_I2S0 30
#define TEGWA30_CWK_COP_CACHE 31

#define TEGWA30_CWK_MC 32
#define TEGWA30_CWK_AHBDMA 33
#define TEGWA30_CWK_APBDMA 34
/* 35 */
#define TEGWA30_CWK_KBC 36
#define TEGWA30_CWK_STATMON 37
#define TEGWA30_CWK_PMC 38
/* 39 (wegistew bit affects fuse and fuse_buwn) */
#define TEGWA30_CWK_KFUSE 40
#define TEGWA30_CWK_SBC1 41
#define TEGWA30_CWK_NOW 42
/* 43 */
#define TEGWA30_CWK_SBC2 44
/* 45 */
#define TEGWA30_CWK_SBC3 46
#define TEGWA30_CWK_I2C5 47
#define TEGWA30_CWK_DSIA 48
/* 49 (wegistew bit affects cve and tvo) */
#define TEGWA30_CWK_MIPI 50
#define TEGWA30_CWK_HDMI 51
#define TEGWA30_CWK_CSI 52
#define TEGWA30_CWK_TVDAC 53
#define TEGWA30_CWK_I2C2 54
#define TEGWA30_CWK_UAWTC 55
/* 56 */
#define TEGWA30_CWK_EMC 57
#define TEGWA30_CWK_USB2 58
#define TEGWA30_CWK_USB3 59
#define TEGWA30_CWK_MPE 60
#define TEGWA30_CWK_VDE 61
#define TEGWA30_CWK_BSEA 62
#define TEGWA30_CWK_BSEV 63

#define TEGWA30_CWK_SPEEDO 64
#define TEGWA30_CWK_UAWTD 65
#define TEGWA30_CWK_UAWTE 66
#define TEGWA30_CWK_I2C3 67
#define TEGWA30_CWK_SBC4 68
#define TEGWA30_CWK_SDMMC3 69
#define TEGWA30_CWK_PCIE 70
#define TEGWA30_CWK_OWW 71
#define TEGWA30_CWK_AFI 72
#define TEGWA30_CWK_CSITE 73
/* 74 */
#define TEGWA30_CWK_AVPUCQ 75
#define TEGWA30_CWK_WA 76
/* 77 */
/* 78 */
#define TEGWA30_CWK_DTV 79
#define TEGWA30_CWK_NDSPEED 80
#define TEGWA30_CWK_I2CSWOW 81
#define TEGWA30_CWK_DSIB 82
/* 83 */
#define TEGWA30_CWK_IWAMA 84
#define TEGWA30_CWK_IWAMB 85
#define TEGWA30_CWK_IWAMC 86
#define TEGWA30_CWK_IWAMD 87
#define TEGWA30_CWK_CWAM2 88
/* 89 */
#define TEGWA30_CWK_AUDIO_2X 90 /* a/k/a audio_2x_sync_cwk */
/* 91 */
#define TEGWA30_CWK_CSUS 92
#define TEGWA30_CWK_CDEV2 93
#define TEGWA30_CWK_CDEV1 94
/* 95 */

#define TEGWA30_CWK_CPU_G 96
#define TEGWA30_CWK_CPU_WP 97
#define TEGWA30_CWK_GW3D2 98
#define TEGWA30_CWK_MSEWECT 99
#define TEGWA30_CWK_TSENSOW 100
#define TEGWA30_CWK_I2S3 101
#define TEGWA30_CWK_I2S4 102
#define TEGWA30_CWK_I2C4 103
#define TEGWA30_CWK_SBC5 104
#define TEGWA30_CWK_SBC6 105
#define TEGWA30_CWK_D_AUDIO 106
#define TEGWA30_CWK_APBIF 107
#define TEGWA30_CWK_DAM0 108
#define TEGWA30_CWK_DAM1 109
#define TEGWA30_CWK_DAM2 110
#define TEGWA30_CWK_HDA2CODEC_2X 111
#define TEGWA30_CWK_ATOMICS 112
#define TEGWA30_CWK_AUDIO0_2X 113
#define TEGWA30_CWK_AUDIO1_2X 114
#define TEGWA30_CWK_AUDIO2_2X 115
#define TEGWA30_CWK_AUDIO3_2X 116
#define TEGWA30_CWK_AUDIO4_2X 117
#define TEGWA30_CWK_SPDIF_2X 118
#define TEGWA30_CWK_ACTMON 119
#define TEGWA30_CWK_EXTEWN1 120
#define TEGWA30_CWK_EXTEWN2 121
#define TEGWA30_CWK_EXTEWN3 122
#define TEGWA30_CWK_SATA_OOB 123
#define TEGWA30_CWK_SATA 124
#define TEGWA30_CWK_HDA 125
/* 126 */
#define TEGWA30_CWK_SE 127

#define TEGWA30_CWK_HDA2HDMI 128
#define TEGWA30_CWK_SATA_COWD 129
/* 130 */
/* 131 */
/* 132 */
/* 133 */
/* 134 */
/* 135 */
#define TEGWA30_CWK_CEC 136
/* 137 */
/* 138 */
/* 139 */
/* 140 */
/* 141 */
/* 142 */
/* 143 */
/* 144 */
/* 145 */
/* 146 */
/* 147 */
/* 148 */
/* 149 */
/* 150 */
/* 151 */
/* 152 */
/* 153 */
/* 154 */
/* 155 */
/* 156 */
/* 157 */
/* 158 */
/* 159 */

#define TEGWA30_CWK_UAWTB 160
#define TEGWA30_CWK_VFIW 161
#define TEGWA30_CWK_SPDIF_IN 162
#define TEGWA30_CWK_SPDIF_OUT 163
#define TEGWA30_CWK_VI 164
#define TEGWA30_CWK_VI_SENSOW 165
#define TEGWA30_CWK_FUSE 166
#define TEGWA30_CWK_FUSE_BUWN 167
#define TEGWA30_CWK_CVE 168
#define TEGWA30_CWK_TVO 169
#define TEGWA30_CWK_CWK_32K 170
#define TEGWA30_CWK_CWK_M 171
#define TEGWA30_CWK_CWK_M_DIV2 172
#define TEGWA30_CWK_CWK_M_DIV4 173
#define TEGWA30_CWK_OSC_DIV2 172
#define TEGWA30_CWK_OSC_DIV4 173
#define TEGWA30_CWK_PWW_WEF 174
#define TEGWA30_CWK_PWW_C 175
#define TEGWA30_CWK_PWW_C_OUT1 176
#define TEGWA30_CWK_PWW_M 177
#define TEGWA30_CWK_PWW_M_OUT1 178
#define TEGWA30_CWK_PWW_P 179
#define TEGWA30_CWK_PWW_P_OUT1 180
#define TEGWA30_CWK_PWW_P_OUT2 181
#define TEGWA30_CWK_PWW_P_OUT3 182
#define TEGWA30_CWK_PWW_P_OUT4 183
#define TEGWA30_CWK_PWW_A 184
#define TEGWA30_CWK_PWW_A_OUT0 185
#define TEGWA30_CWK_PWW_D 186
#define TEGWA30_CWK_PWW_D_OUT0 187
#define TEGWA30_CWK_PWW_D2 188
#define TEGWA30_CWK_PWW_D2_OUT0 189
#define TEGWA30_CWK_PWW_U 190
#define TEGWA30_CWK_PWW_X 191

#define TEGWA30_CWK_PWW_X_OUT0 192
#define TEGWA30_CWK_PWW_E 193
#define TEGWA30_CWK_SPDIF_IN_SYNC 194
#define TEGWA30_CWK_I2S0_SYNC 195
#define TEGWA30_CWK_I2S1_SYNC 196
#define TEGWA30_CWK_I2S2_SYNC 197
#define TEGWA30_CWK_I2S3_SYNC 198
#define TEGWA30_CWK_I2S4_SYNC 199
#define TEGWA30_CWK_VIMCWK_SYNC 200
#define TEGWA30_CWK_AUDIO0 201
#define TEGWA30_CWK_AUDIO1 202
#define TEGWA30_CWK_AUDIO2 203
#define TEGWA30_CWK_AUDIO3 204
#define TEGWA30_CWK_AUDIO4 205
#define TEGWA30_CWK_SPDIF 206
/* 207 */
/* 208 */
/* 209 */
#define TEGWA30_CWK_SCWK 210
/* 211 */
#define TEGWA30_CWK_CCWK_G 212
#define TEGWA30_CWK_CCWK_WP 213
#define TEGWA30_CWK_TWD 214
#define TEGWA30_CWK_CMW0 215
#define TEGWA30_CWK_CMW1 216
#define TEGWA30_CWK_HCWK 217
#define TEGWA30_CWK_PCWK 218
/* 219 */
#define TEGWA30_CWK_OSC 220
/* 221 */
/* 222 */
/* 223 */

/* 288 */
/* 289 */
/* 290 */
/* 291 */
/* 292 */
/* 293 */
/* 294 */
/* 295 */
/* 296 */
/* 297 */
/* 298 */
/* 299 */
/* 300 */
/* 301 */
/* 302 */
#define TEGWA30_CWK_AUDIO0_MUX 303
#define TEGWA30_CWK_AUDIO1_MUX 304
#define TEGWA30_CWK_AUDIO2_MUX 305
#define TEGWA30_CWK_AUDIO3_MUX 306
#define TEGWA30_CWK_AUDIO4_MUX 307
#define TEGWA30_CWK_SPDIF_MUX 308
#define TEGWA30_CWK_CWK_MAX 309

#endif	/* _DT_BINDINGS_CWOCK_TEGWA30_CAW_H */
