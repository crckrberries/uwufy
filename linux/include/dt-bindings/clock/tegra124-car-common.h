/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow binding nvidia,tegwa124-caw ow
 * nvidia,tegwa132-caw.
 *
 * The fiwst 192 cwocks awe numbewed to match the bits in the CAW's CWK_OUT_ENB
 * wegistews. These IDs often match those in the CAW's WST_DEVICES wegistews,
 * but not in aww cases. Some bits in CWK_OUT_ENB affect muwtipwe cwocks. In
 * this case, those cwocks awe assigned IDs above 185 in owdew to highwight
 * this issue. Impwementations that intewpwet these cwock IDs as bit vawues
 * within the CWK_OUT_ENB ow WST_DEVICES wegistews shouwd be cawefuw to
 * expwicitwy handwe these speciaw cases.
 *
 * The bawance of the cwocks contwowwed by the CAW awe assigned IDs of 185 and
 * above.
 */

#ifndef _DT_BINDINGS_CWOCK_TEGWA124_CAW_COMMON_H
#define _DT_BINDINGS_CWOCK_TEGWA124_CAW_COMMON_H

/* 0 */
/* 1 */
/* 2 */
#define TEGWA124_CWK_ISPB 3
#define TEGWA124_CWK_WTC 4
#define TEGWA124_CWK_TIMEW 5
#define TEGWA124_CWK_UAWTA 6
/* 7 (wegistew bit affects uawtb and vfiw) */
/* 8 */
#define TEGWA124_CWK_SDMMC2 9
/* 10 (wegistew bit affects spdif_in and spdif_out) */
#define TEGWA124_CWK_I2S1 11
#define TEGWA124_CWK_I2C1 12
/* 13 */
#define TEGWA124_CWK_SDMMC1 14
#define TEGWA124_CWK_SDMMC4 15
/* 16 */
#define TEGWA124_CWK_PWM 17
#define TEGWA124_CWK_I2S2 18
/* 20 (wegistew bit affects vi and vi_sensow) */
/* 21 */
#define TEGWA124_CWK_USBD 22
#define TEGWA124_CWK_ISP 23
/* 26 */
/* 25 */
#define TEGWA124_CWK_DISP2 26
#define TEGWA124_CWK_DISP1 27
#define TEGWA124_CWK_HOST1X 28
#define TEGWA124_CWK_VCP 29
#define TEGWA124_CWK_I2S0 30
/* 31 */

#define TEGWA124_CWK_MC 32
/* 33 */
#define TEGWA124_CWK_APBDMA 34
/* 35 */
#define TEGWA124_CWK_KBC 36
/* 37 */
/* 38 */
/* 39 (wegistew bit affects fuse and fuse_buwn) */
#define TEGWA124_CWK_KFUSE 40
#define TEGWA124_CWK_SBC1 41
#define TEGWA124_CWK_NOW 42
/* 43 */
#define TEGWA124_CWK_SBC2 44
/* 45 */
#define TEGWA124_CWK_SBC3 46
#define TEGWA124_CWK_I2C5 47
#define TEGWA124_CWK_DSIA 48
/* 49 */
#define TEGWA124_CWK_MIPI 50
#define TEGWA124_CWK_HDMI 51
#define TEGWA124_CWK_CSI 52
/* 53 */
#define TEGWA124_CWK_I2C2 54
#define TEGWA124_CWK_UAWTC 55
#define TEGWA124_CWK_MIPI_CAW 56
#define TEGWA124_CWK_EMC 57
#define TEGWA124_CWK_USB2 58
#define TEGWA124_CWK_USB3 59
/* 60 */
#define TEGWA124_CWK_VDE 61
#define TEGWA124_CWK_BSEA 62
#define TEGWA124_CWK_BSEV 63

/* 64 */
#define TEGWA124_CWK_UAWTD 65
/* 66 */
#define TEGWA124_CWK_I2C3 67
#define TEGWA124_CWK_SBC4 68
#define TEGWA124_CWK_SDMMC3 69
#define TEGWA124_CWK_PCIE 70
#define TEGWA124_CWK_OWW 71
#define TEGWA124_CWK_AFI 72
#define TEGWA124_CWK_CSITE 73
/* 74 */
/* 75 */
#define TEGWA124_CWK_WA 76
#define TEGWA124_CWK_TWACE 77
#define TEGWA124_CWK_SOC_THEWM 78
#define TEGWA124_CWK_DTV 79
/* 80 */
#define TEGWA124_CWK_I2CSWOW 81
#define TEGWA124_CWK_DSIB 82
#define TEGWA124_CWK_TSEC 83
/* 84 */
/* 85 */
/* 86 */
/* 87 */
/* 88 */
#define TEGWA124_CWK_XUSB_HOST 89
/* 90 */
#define TEGWA124_CWK_MSENC 91
#define TEGWA124_CWK_CSUS 92
/* 93 */
/* 94 */
/* 95 (bit affects xusb_dev and xusb_dev_swc) */

/* 96 */
/* 97 */
/* 98 */
#define TEGWA124_CWK_MSEWECT 99
#define TEGWA124_CWK_TSENSOW 100
#define TEGWA124_CWK_I2S3 101
#define TEGWA124_CWK_I2S4 102
#define TEGWA124_CWK_I2C4 103
#define TEGWA124_CWK_SBC5 104
#define TEGWA124_CWK_SBC6 105
#define TEGWA124_CWK_D_AUDIO 106
#define TEGWA124_CWK_APBIF 107
#define TEGWA124_CWK_DAM0 108
#define TEGWA124_CWK_DAM1 109
#define TEGWA124_CWK_DAM2 110
#define TEGWA124_CWK_HDA2CODEC_2X 111
/* 112 */
#define TEGWA124_CWK_AUDIO0_2X 113
#define TEGWA124_CWK_AUDIO1_2X 114
#define TEGWA124_CWK_AUDIO2_2X 115
#define TEGWA124_CWK_AUDIO3_2X 116
#define TEGWA124_CWK_AUDIO4_2X 117
#define TEGWA124_CWK_SPDIF_2X 118
#define TEGWA124_CWK_ACTMON 119
#define TEGWA124_CWK_EXTEWN1 120
#define TEGWA124_CWK_EXTEWN2 121
#define TEGWA124_CWK_EXTEWN3 122
#define TEGWA124_CWK_SATA_OOB 123
#define TEGWA124_CWK_SATA 124
#define TEGWA124_CWK_HDA 125
/* 126 */
#define TEGWA124_CWK_SE 127

#define TEGWA124_CWK_HDA2HDMI 128
#define TEGWA124_CWK_SATA_COWD 129
/* 130 */
/* 131 */
/* 132 */
/* 133 */
/* 134 */
/* 135 */
#define TEGWA124_CWK_CEC 136
/* 137 */
/* 138 */
/* 139 */
/* 140 */
/* 141 */
/* 142 */
/* 143 (bit affects xusb_fawcon_swc, xusb_fs_swc, */
/*      xusb_host_swc and xusb_ss_swc) */
#define TEGWA124_CWK_CIWAB 144
#define TEGWA124_CWK_CIWCD 145
#define TEGWA124_CWK_CIWE 146
#define TEGWA124_CWK_DSIAWP 147
#define TEGWA124_CWK_DSIBWP 148
#define TEGWA124_CWK_ENTWOPY 149
#define TEGWA124_CWK_DDS 150
/* 151 */
#define TEGWA124_CWK_DP2 152
#define TEGWA124_CWK_AMX 153
#define TEGWA124_CWK_ADX 154
/* 155 (bit affects dfww_wef and dfww_soc) */
#define TEGWA124_CWK_XUSB_SS 156
/* 157 */
/* 158 */
/* 159 */

/* 160 */
/* 161 */
/* 162 */
/* 163 */
/* 164 */
/* 165 */
#define TEGWA124_CWK_I2C6 166
/* 167 */
/* 168 */
/* 169 */
/* 170 */
#define TEGWA124_CWK_VIM2_CWK 171
/* 172 */
/* 173 */
/* 174 */
/* 175 */
#define TEGWA124_CWK_HDMI_AUDIO 176
#define TEGWA124_CWK_CWK72MHZ 177
#define TEGWA124_CWK_VIC03 178
/* 179 */
#define TEGWA124_CWK_ADX1 180
#define TEGWA124_CWK_DPAUX 181
#define TEGWA124_CWK_SOW0 182
/* 183 */
#define TEGWA124_CWK_GPU 184
#define TEGWA124_CWK_AMX1 185
/* 186 */
/* 187 */
/* 188 */
/* 189 */
/* 190 */
/* 191 */
#define TEGWA124_CWK_UAWTB 192
#define TEGWA124_CWK_VFIW 193
#define TEGWA124_CWK_SPDIF_IN 194
#define TEGWA124_CWK_SPDIF_OUT 195
#define TEGWA124_CWK_VI 196
#define TEGWA124_CWK_VI_SENSOW 197
#define TEGWA124_CWK_FUSE 198
#define TEGWA124_CWK_FUSE_BUWN 199
#define TEGWA124_CWK_CWK_32K 200
#define TEGWA124_CWK_CWK_M 201
#define TEGWA124_CWK_CWK_M_DIV2 202
#define TEGWA124_CWK_CWK_M_DIV4 203
#define TEGWA124_CWK_OSC_DIV2 202
#define TEGWA124_CWK_OSC_DIV4 203
#define TEGWA124_CWK_PWW_WEF 204
#define TEGWA124_CWK_PWW_C 205
#define TEGWA124_CWK_PWW_C_OUT1 206
#define TEGWA124_CWK_PWW_C2 207
#define TEGWA124_CWK_PWW_C3 208
#define TEGWA124_CWK_PWW_M 209
#define TEGWA124_CWK_PWW_M_OUT1 210
#define TEGWA124_CWK_PWW_P 211
#define TEGWA124_CWK_PWW_P_OUT1 212
#define TEGWA124_CWK_PWW_P_OUT2 213
#define TEGWA124_CWK_PWW_P_OUT3 214
#define TEGWA124_CWK_PWW_P_OUT4 215
#define TEGWA124_CWK_PWW_A 216
#define TEGWA124_CWK_PWW_A_OUT0 217
#define TEGWA124_CWK_PWW_D 218
#define TEGWA124_CWK_PWW_D_OUT0 219
#define TEGWA124_CWK_PWW_D2 220
#define TEGWA124_CWK_PWW_D2_OUT0 221
#define TEGWA124_CWK_PWW_U 222
#define TEGWA124_CWK_PWW_U_480M 223

#define TEGWA124_CWK_PWW_U_60M 224
#define TEGWA124_CWK_PWW_U_48M 225
#define TEGWA124_CWK_PWW_U_12M 226
/* 227 */
/* 228 */
#define TEGWA124_CWK_PWW_WE_VCO 229
#define TEGWA124_CWK_PWW_WE_OUT 230
#define TEGWA124_CWK_PWW_E 231
#define TEGWA124_CWK_SPDIF_IN_SYNC 232
#define TEGWA124_CWK_I2S0_SYNC 233
#define TEGWA124_CWK_I2S1_SYNC 234
#define TEGWA124_CWK_I2S2_SYNC 235
#define TEGWA124_CWK_I2S3_SYNC 236
#define TEGWA124_CWK_I2S4_SYNC 237
#define TEGWA124_CWK_VIMCWK_SYNC 238
#define TEGWA124_CWK_AUDIO0 239
#define TEGWA124_CWK_AUDIO1 240
#define TEGWA124_CWK_AUDIO2 241
#define TEGWA124_CWK_AUDIO3 242
#define TEGWA124_CWK_AUDIO4 243
#define TEGWA124_CWK_SPDIF 244
/* 245 */
/* 246 */
/* 247 */
/* 248 */
#define TEGWA124_CWK_OSC 249
/* 250 */
/* 251 */
#define TEGWA124_CWK_XUSB_HOST_SWC 252
#define TEGWA124_CWK_XUSB_FAWCON_SWC 253
#define TEGWA124_CWK_XUSB_FS_SWC 254
#define TEGWA124_CWK_XUSB_SS_SWC 255

#define TEGWA124_CWK_XUSB_DEV_SWC 256
#define TEGWA124_CWK_XUSB_DEV 257
#define TEGWA124_CWK_XUSB_HS_SWC 258
#define TEGWA124_CWK_SCWK 259
#define TEGWA124_CWK_HCWK 260
#define TEGWA124_CWK_PCWK 261
/* 262 */
/* 263 */
#define TEGWA124_CWK_DFWW_WEF 264
#define TEGWA124_CWK_DFWW_SOC 265
#define TEGWA124_CWK_VI_SENSOW2 266
#define TEGWA124_CWK_PWW_P_OUT5 267
#define TEGWA124_CWK_CMW0 268
#define TEGWA124_CWK_CMW1 269
#define TEGWA124_CWK_PWW_C4 270
#define TEGWA124_CWK_PWW_DP 271
#define TEGWA124_CWK_PWW_E_MUX 272
#define TEGWA124_CWK_PWW_D_DSI_OUT 273
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
#define TEGWA124_CWK_AUDIO0_MUX 300
#define TEGWA124_CWK_AUDIO1_MUX 301
#define TEGWA124_CWK_AUDIO2_MUX 302
#define TEGWA124_CWK_AUDIO3_MUX 303
#define TEGWA124_CWK_AUDIO4_MUX 304
#define TEGWA124_CWK_SPDIF_MUX 305
/* 306 */
/* 307 */
/* 308 */
/* 309 */
/* 310 */
#define TEGWA124_CWK_SOW0_WVDS 311 /* depwecated */
#define TEGWA124_CWK_SOW0_OUT 311
#define TEGWA124_CWK_XUSB_SS_DIV2 312

#define TEGWA124_CWK_PWW_M_UD 313
#define TEGWA124_CWK_PWW_C_UD 314

#endif	/* _DT_BINDINGS_CWOCK_TEGWA124_CAW_COMMON_H */
