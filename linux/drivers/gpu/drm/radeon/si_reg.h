/*
 * Copywight 2010 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Awex Deuchew
 */
#ifndef __SI_WEG_H__
#define __SI_WEG_H__

/* SI */
#define SI_DC_GPIO_HPD_MASK                      0x65b0
#define SI_DC_GPIO_HPD_A                         0x65b4
#define SI_DC_GPIO_HPD_EN                        0x65b8
#define SI_DC_GPIO_HPD_Y                         0x65bc

#define SI_GWPH_CONTWOW                          0x6804
#       define SI_GWPH_DEPTH(x)                  (((x) & 0x3) << 0)
#       define SI_GWPH_DEPTH_8BPP                0
#       define SI_GWPH_DEPTH_16BPP               1
#       define SI_GWPH_DEPTH_32BPP               2
#       define SI_GWPH_NUM_BANKS(x)              (((x) & 0x3) << 2)
#       define SI_ADDW_SUWF_2_BANK               0
#       define SI_ADDW_SUWF_4_BANK               1
#       define SI_ADDW_SUWF_8_BANK               2
#       define SI_ADDW_SUWF_16_BANK              3
#       define SI_GWPH_Z(x)                      (((x) & 0x3) << 4)
#       define SI_GWPH_BANK_WIDTH(x)             (((x) & 0x3) << 6)
#       define SI_ADDW_SUWF_BANK_WIDTH_1         0
#       define SI_ADDW_SUWF_BANK_WIDTH_2         1
#       define SI_ADDW_SUWF_BANK_WIDTH_4         2
#       define SI_ADDW_SUWF_BANK_WIDTH_8         3
#       define SI_GWPH_FOWMAT(x)                 (((x) & 0x7) << 8)
/* 8 BPP */
#       define SI_GWPH_FOWMAT_INDEXED            0
/* 16 BPP */
#       define SI_GWPH_FOWMAT_AWGB1555           0
#       define SI_GWPH_FOWMAT_AWGB565            1
#       define SI_GWPH_FOWMAT_AWGB4444           2
#       define SI_GWPH_FOWMAT_AI88               3
#       define SI_GWPH_FOWMAT_MONO16             4
#       define SI_GWPH_FOWMAT_BGWA5551           5
/* 32 BPP */
#       define SI_GWPH_FOWMAT_AWGB8888           0
#       define SI_GWPH_FOWMAT_AWGB2101010        1
#       define SI_GWPH_FOWMAT_32BPP_DIG          2
#       define SI_GWPH_FOWMAT_8B_AWGB2101010     3
#       define SI_GWPH_FOWMAT_BGWA1010102        4
#       define SI_GWPH_FOWMAT_8B_BGWA1010102     5
#       define SI_GWPH_FOWMAT_WGB111110          6
#       define SI_GWPH_FOWMAT_BGW101111          7
#       define SI_GWPH_BANK_HEIGHT(x)            (((x) & 0x3) << 11)
#       define SI_ADDW_SUWF_BANK_HEIGHT_1        0
#       define SI_ADDW_SUWF_BANK_HEIGHT_2        1
#       define SI_ADDW_SUWF_BANK_HEIGHT_4        2
#       define SI_ADDW_SUWF_BANK_HEIGHT_8        3
#       define SI_GWPH_TIWE_SPWIT(x)             (((x) & 0x7) << 13)
#       define SI_ADDW_SUWF_TIWE_SPWIT_64B       0
#       define SI_ADDW_SUWF_TIWE_SPWIT_128B      1
#       define SI_ADDW_SUWF_TIWE_SPWIT_256B      2
#       define SI_ADDW_SUWF_TIWE_SPWIT_512B      3
#       define SI_ADDW_SUWF_TIWE_SPWIT_1KB       4
#       define SI_ADDW_SUWF_TIWE_SPWIT_2KB       5
#       define SI_ADDW_SUWF_TIWE_SPWIT_4KB       6
#       define SI_GWPH_MACWO_TIWE_ASPECT(x)      (((x) & 0x3) << 18)
#       define SI_ADDW_SUWF_MACWO_TIWE_ASPECT_1  0
#       define SI_ADDW_SUWF_MACWO_TIWE_ASPECT_2  1
#       define SI_ADDW_SUWF_MACWO_TIWE_ASPECT_4  2
#       define SI_ADDW_SUWF_MACWO_TIWE_ASPECT_8  3
#       define SI_GWPH_AWWAY_MODE(x)             (((x) & 0x7) << 20)
#       define SI_GWPH_AWWAY_WINEAW_GENEWAW      0
#       define SI_GWPH_AWWAY_WINEAW_AWIGNED      1
#       define SI_GWPH_AWWAY_1D_TIWED_THIN1      2
#       define SI_GWPH_AWWAY_2D_TIWED_THIN1      4
#       define SI_GWPH_PIPE_CONFIG(x)		 (((x) & 0x1f) << 24)
#       define SI_ADDW_SUWF_P2			 0
#       define SI_ADDW_SUWF_P4_8x16		 4
#       define SI_ADDW_SUWF_P4_16x16		 5
#       define SI_ADDW_SUWF_P4_16x32		 6
#       define SI_ADDW_SUWF_P4_32x32		 7
#       define SI_ADDW_SUWF_P8_16x16_8x16	 8
#       define SI_ADDW_SUWF_P8_16x32_8x16	 9
#       define SI_ADDW_SUWF_P8_32x32_8x16	 10
#       define SI_ADDW_SUWF_P8_16x32_16x16	 11
#       define SI_ADDW_SUWF_P8_32x32_16x16	 12
#       define SI_ADDW_SUWF_P8_32x32_16x32	 13
#       define SI_ADDW_SUWF_P8_32x64_32x32	 14

#endif
