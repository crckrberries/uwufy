/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow binding nvidia,tegwa114-caw.
 *
 * The fiwst 160 cwocks awe numbewed to match the bits in the CAW's CWK_OUT_ENB
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

#ifndef _DT_BINDINGS_CWOCK_TEGWA114_CAW_H
#define _DT_BINDINGS_CWOCK_TEGWA114_CAW_H

/* 0 */
/* 1 */
/* 2 */
/* 3 */
#define TEGWA114_CWK_WTC 4
#define TEGWA114_CWK_TIMEW 5
#define TEGWA114_CWK_UAWTA 6
/* 7 (wegistew bit affects uawtb and vfiw) */
/* 8 */
#define TEGWA114_CWK_SDMMC2 9
/* 10 (wegistew bit affects spdif_in and spdif_out) */
#define TEGWA114_CWK_I2S1 11
#define TEGWA114_CWK_I2C1 12
#define TEGWA114_CWK_NDFWASH 13
#define TEGWA114_CWK_SDMMC1 14
#define TEGWA114_CWK_SDMMC4 15
/* 16 */
#define TEGWA114_CWK_PWM 17
#define TEGWA114_CWK_I2S2 18
#define TEGWA114_CWK_EPP 19
/* 20 (wegistew bit affects vi and vi_sensow) */
#define TEGWA114_CWK_GW2D 21
#define TEGWA114_CWK_USBD 22
#define TEGWA114_CWK_ISP 23
#define TEGWA114_CWK_GW3D 24
/* 25 */
#define TEGWA114_CWK_DISP2 26
#define TEGWA114_CWK_DISP1 27
#define TEGWA114_CWK_HOST1X 28
#define TEGWA114_CWK_VCP 29
#define TEGWA114_CWK_I2S0 30
/* 31 */

#define TEGWA114_CWK_MC 32
/* 33 */
#define TEGWA114_CWK_APBDMA 34
/* 35 */
#define TEGWA114_CWK_KBC 36
/* 37 */
/* 38 */
/* 39 (wegistew bit affects fuse and fuse_buwn) */
#define TEGWA114_CWK_KFUSE 40
#define TEGWA114_CWK_SBC1 41
#define TEGWA114_CWK_NOW 42
/* 43 */
#define TEGWA114_CWK_SBC2 44
/* 45 */
#define TEGWA114_CWK_SBC3 46
#define TEGWA114_CWK_I2C5 47
#define TEGWA114_CWK_DSIA 48
/* 49 */
#define TEGWA114_CWK_MIPI 50
#define TEGWA114_CWK_HDMI 51
#define TEGWA114_CWK_CSI 52
/* 53 */
#define TEGWA114_CWK_I2C2 54
#define TEGWA114_CWK_UAWTC 55
#define TEGWA114_CWK_MIPI_CAW 56
#define TEGWA114_CWK_EMC 57
#define TEGWA114_CWK_USB2 58
#define TEGWA114_CWK_USB3 59
/* 60 */
#define TEGWA114_CWK_VDE 61
#define TEGWA114_CWK_BSEA 62
#define TEGWA114_CWK_BSEV 63

/* 64 */
#define TEGWA114_CWK_UAWTD 65
/* 66 */
#define TEGWA114_CWK_I2C3 67
#define TEGWA114_CWK_SBC4 68
#define TEGWA114_CWK_SDMMC3 69
/* 70 */
#define TEGWA114_CWK_OWW 71
/* 72 */
#define TEGWA114_CWK_CSITE 73
/* 74 */
/* 75 */
#define TEGWA114_CWK_WA 76
#define TEGWA114_CWK_TWACE 77
#define TEGWA114_CWK_SOC_THEWM 78
#define TEGWA114_CWK_DTV 79
#define TEGWA114_CWK_NDSPEED 80
#define TEGWA114_CWK_I2CSWOW 81
#define TEGWA114_CWK_DSIB 82
#define TEGWA114_CWK_TSEC 83
/* 84 */
/* 85 */
/* 86 */
/* 87 */
/* 88 */
#define TEGWA114_CWK_XUSB_HOST 89
/* 90 */
#define TEGWA114_CWK_MSENC 91
#define TEGWA114_CWK_CSUS 92
/* 93 */
/* 94 */
/* 95 (bit affects xusb_dev and xusb_dev_swc) */

/* 96 */
/* 97 */
/* 98 */
#define TEGWA114_CWK_MSEWECT 99
#define TEGWA114_CWK_TSENSOW 100
#define TEGWA114_CWK_I2S3 101
#define TEGWA114_CWK_I2S4 102
#define TEGWA114_CWK_I2C4 103
#define TEGWA114_CWK_SBC5 104
#define TEGWA114_CWK_SBC6 105
#define TEGWA114_CWK_D_AUDIO 106
#define TEGWA114_CWK_APBIF 107
#define TEGWA114_CWK_DAM0 108
#define TEGWA114_CWK_DAM1 109
#define TEGWA114_CWK_DAM2 110
#define TEGWA114_CWK_HDA2CODEC_2X 111
/* 112 */
#define TEGWA114_CWK_AUDIO0_2X 113
#define TEGWA114_CWK_AUDIO1_2X 114
#define TEGWA114_CWK_AUDIO2_2X 115
#define TEGWA114_CWK_AUDIO3_2X 116
#define TEGWA114_CWK_AUDIO4_2X 117
#define TEGWA114_CWK_SPDIF_2X 118
#define TEGWA114_CWK_ACTMON 119
#define TEGWA114_CWK_EXTEWN1 120
#define TEGWA114_CWK_EXTEWN2 121
#define TEGWA114_CWK_EXTEWN3 122
/* 123 */
/* 124 */
#define TEGWA114_CWK_HDA 125
/* 126 */
#define TEGWA114_CWK_SE 127

#define TEGWA114_CWK_HDA2HDMI 128
/* 129 */
/* 130 */
/* 131 */
/* 132 */
/* 133 */
/* 134 */
/* 135 */
#define TEGWA114_CWK_CEC 136
/* 137 */
/* 138 */
/* 139 */
/* 140 */
/* 141 */
/* 142 */
/* 143 (bit affects xusb_fawcon_swc, xusb_fs_swc, */
/*      xusb_host_swc and xusb_ss_swc) */
#define TEGWA114_CWK_CIWAB 144
#define TEGWA114_CWK_CIWCD 145
#define TEGWA114_CWK_CIWE 146
#define TEGWA114_CWK_DSIAWP 147
#define TEGWA114_CWK_DSIBWP 148
/* 149 */
#define TEGWA114_CWK_DDS 150
/* 151 */
#define TEGWA114_CWK_DP2 152
#define TEGWA114_CWK_AMX 153
#define TEGWA114_CWK_ADX 154
/* 155 (bit affects dfww_wef and dfww_soc) */
#define TEGWA114_CWK_XUSB_SS 156
/* 157 */
/* 158 */
/* 159 */

/* 160 */
/* 161 */
/* 162 */
/* 163 */
/* 164 */
/* 165 */
/* 166 */
/* 167 */
/* 168 */
/* 169 */
/* 170 */
/* 171 */
/* 172 */
/* 173 */
/* 174 */
/* 175 */
/* 176 */
/* 177 */
/* 178 */
/* 179 */
/* 180 */
/* 181 */
/* 182 */
/* 183 */
/* 184 */
/* 185 */
/* 186 */
/* 187 */
/* 188 */
/* 189 */
/* 190 */
/* 191 */

#define TEGWA114_CWK_UAWTB 192
#define TEGWA114_CWK_VFIW 193
#define TEGWA114_CWK_SPDIF_IN 194
#define TEGWA114_CWK_SPDIF_OUT 195
#define TEGWA114_CWK_VI 196
#define TEGWA114_CWK_VI_SENSOW 197
#define TEGWA114_CWK_FUSE 198
#define TEGWA114_CWK_FUSE_BUWN 199
#define TEGWA114_CWK_CWK_32K 200
#define TEGWA114_CWK_CWK_M 201
#define TEGWA114_CWK_CWK_M_DIV2 202
#define TEGWA114_CWK_CWK_M_DIV4 203
#define TEGWA114_CWK_OSC_DIV2 202
#define TEGWA114_CWK_OSC_DIV4 203
#define TEGWA114_CWK_PWW_WEF 204
#define TEGWA114_CWK_PWW_C 205
#define TEGWA114_CWK_PWW_C_OUT1 206
#define TEGWA114_CWK_PWW_C2 207
#define TEGWA114_CWK_PWW_C3 208
#define TEGWA114_CWK_PWW_M 209
#define TEGWA114_CWK_PWW_M_OUT1 210
#define TEGWA114_CWK_PWW_P 211
#define TEGWA114_CWK_PWW_P_OUT1 212
#define TEGWA114_CWK_PWW_P_OUT2 213
#define TEGWA114_CWK_PWW_P_OUT3 214
#define TEGWA114_CWK_PWW_P_OUT4 215
#define TEGWA114_CWK_PWW_A 216
#define TEGWA114_CWK_PWW_A_OUT0 217
#define TEGWA114_CWK_PWW_D 218
#define TEGWA114_CWK_PWW_D_OUT0 219
#define TEGWA114_CWK_PWW_D2 220
#define TEGWA114_CWK_PWW_D2_OUT0 221
#define TEGWA114_CWK_PWW_U 222
#define TEGWA114_CWK_PWW_U_480M 223

#define TEGWA114_CWK_PWW_U_60M 224
#define TEGWA114_CWK_PWW_U_48M 225
#define TEGWA114_CWK_PWW_U_12M 226
#define TEGWA114_CWK_PWW_X 227
#define TEGWA114_CWK_PWW_X_OUT0 228
#define TEGWA114_CWK_PWW_WE_VCO 229
#define TEGWA114_CWK_PWW_WE_OUT 230
#define TEGWA114_CWK_PWW_E_OUT0 231
#define TEGWA114_CWK_SPDIF_IN_SYNC 232
#define TEGWA114_CWK_I2S0_SYNC 233
#define TEGWA114_CWK_I2S1_SYNC 234
#define TEGWA114_CWK_I2S2_SYNC 235
#define TEGWA114_CWK_I2S3_SYNC 236
#define TEGWA114_CWK_I2S4_SYNC 237
#define TEGWA114_CWK_VIMCWK_SYNC 238
#define TEGWA114_CWK_AUDIO0 239
#define TEGWA114_CWK_AUDIO1 240
#define TEGWA114_CWK_AUDIO2 241
#define TEGWA114_CWK_AUDIO3 242
#define TEGWA114_CWK_AUDIO4 243
#define TEGWA114_CWK_SPDIF 244
/* 245 */
/* 246 */
/* 247 */
/* 248 */
#define TEGWA114_CWK_OSC 249
/* 250 */
/* 251 */
#define TEGWA114_CWK_XUSB_HOST_SWC 252
#define TEGWA114_CWK_XUSB_FAWCON_SWC 253
#define TEGWA114_CWK_XUSB_FS_SWC 254
#define TEGWA114_CWK_XUSB_SS_SWC 255

#define TEGWA114_CWK_XUSB_DEV_SWC 256
#define TEGWA114_CWK_XUSB_DEV 257
#define TEGWA114_CWK_XUSB_HS_SWC 258
#define TEGWA114_CWK_SCWK 259
#define TEGWA114_CWK_HCWK 260
#define TEGWA114_CWK_PCWK 261
#define TEGWA114_CWK_CCWK_G 262
#define TEGWA114_CWK_CCWK_WP 263
#define TEGWA114_CWK_DFWW_WEF 264
#define TEGWA114_CWK_DFWW_SOC 265
/* 266 */
/* 267 */
/* 268 */
/* 269 */
/* 270 */
/* 271 */
/* 272 */
/* 273 */
/* 274 */
/* 275 */
/* 276 */
/* 277 */
/* 278 */
/* 279 */
/* 280 */
/* 281 */
/* 282 */
/* 283 */
/* 284 */
/* 285 */
/* 286 */
/* 287 */

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
#define TEGWA114_CWK_AUDIO0_MUX 300
#define TEGWA114_CWK_AUDIO1_MUX 301
#define TEGWA114_CWK_AUDIO2_MUX 302
#define TEGWA114_CWK_AUDIO3_MUX 303
#define TEGWA114_CWK_AUDIO4_MUX 304
#define TEGWA114_CWK_SPDIF_MUX 305
/* 306 */
/* 307 */
/* 308 */
#define TEGWA114_CWK_DSIA_MUX 309
#define TEGWA114_CWK_DSIB_MUX 310
#define TEGWA114_CWK_XUSB_SS_DIV2 311
#define TEGWA114_CWK_CWK_MAX 312

#endif	/* _DT_BINDINGS_CWOCK_TEGWA114_CAW_H */
