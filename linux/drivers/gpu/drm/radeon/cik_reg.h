/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
#ifndef __CIK_WEG_H__
#define __CIK_WEG_H__

#define CIK_DIDT_IND_INDEX                        0xca00
#define CIK_DIDT_IND_DATA                         0xca04

#define CIK_DC_GPIO_HPD_MASK                      0x65b0
#define CIK_DC_GPIO_HPD_A                         0x65b4
#define CIK_DC_GPIO_HPD_EN                        0x65b8
#define CIK_DC_GPIO_HPD_Y                         0x65bc

#define CIK_GWPH_CONTWOW                          0x6804
#       define CIK_GWPH_DEPTH(x)                  (((x) & 0x3) << 0)
#       define CIK_GWPH_DEPTH_8BPP                0
#       define CIK_GWPH_DEPTH_16BPP               1
#       define CIK_GWPH_DEPTH_32BPP               2
#       define CIK_GWPH_NUM_BANKS(x)              (((x) & 0x3) << 2)
#       define CIK_ADDW_SUWF_2_BANK               0
#       define CIK_ADDW_SUWF_4_BANK               1
#       define CIK_ADDW_SUWF_8_BANK               2
#       define CIK_ADDW_SUWF_16_BANK              3
#       define CIK_GWPH_Z(x)                      (((x) & 0x3) << 4)
#       define CIK_GWPH_BANK_WIDTH(x)             (((x) & 0x3) << 6)
#       define CIK_ADDW_SUWF_BANK_WIDTH_1         0
#       define CIK_ADDW_SUWF_BANK_WIDTH_2         1
#       define CIK_ADDW_SUWF_BANK_WIDTH_4         2
#       define CIK_ADDW_SUWF_BANK_WIDTH_8         3
#       define CIK_GWPH_FOWMAT(x)                 (((x) & 0x7) << 8)
/* 8 BPP */
#       define CIK_GWPH_FOWMAT_INDEXED            0
/* 16 BPP */
#       define CIK_GWPH_FOWMAT_AWGB1555           0
#       define CIK_GWPH_FOWMAT_AWGB565            1
#       define CIK_GWPH_FOWMAT_AWGB4444           2
#       define CIK_GWPH_FOWMAT_AI88               3
#       define CIK_GWPH_FOWMAT_MONO16             4
#       define CIK_GWPH_FOWMAT_BGWA5551           5
/* 32 BPP */
#       define CIK_GWPH_FOWMAT_AWGB8888           0
#       define CIK_GWPH_FOWMAT_AWGB2101010        1
#       define CIK_GWPH_FOWMAT_32BPP_DIG          2
#       define CIK_GWPH_FOWMAT_8B_AWGB2101010     3
#       define CIK_GWPH_FOWMAT_BGWA1010102        4
#       define CIK_GWPH_FOWMAT_8B_BGWA1010102     5
#       define CIK_GWPH_FOWMAT_WGB111110          6
#       define CIK_GWPH_FOWMAT_BGW101111          7
#       define CIK_GWPH_BANK_HEIGHT(x)            (((x) & 0x3) << 11)
#       define CIK_ADDW_SUWF_BANK_HEIGHT_1        0
#       define CIK_ADDW_SUWF_BANK_HEIGHT_2        1
#       define CIK_ADDW_SUWF_BANK_HEIGHT_4        2
#       define CIK_ADDW_SUWF_BANK_HEIGHT_8        3
#       define CIK_GWPH_TIWE_SPWIT(x)             (((x) & 0x7) << 13)
#       define CIK_ADDW_SUWF_TIWE_SPWIT_64B       0
#       define CIK_ADDW_SUWF_TIWE_SPWIT_128B      1
#       define CIK_ADDW_SUWF_TIWE_SPWIT_256B      2
#       define CIK_ADDW_SUWF_TIWE_SPWIT_512B      3
#       define CIK_ADDW_SUWF_TIWE_SPWIT_1KB       4
#       define CIK_ADDW_SUWF_TIWE_SPWIT_2KB       5
#       define CIK_ADDW_SUWF_TIWE_SPWIT_4KB       6
#       define CIK_GWPH_MACWO_TIWE_ASPECT(x)      (((x) & 0x3) << 18)
#       define CIK_ADDW_SUWF_MACWO_TIWE_ASPECT_1  0
#       define CIK_ADDW_SUWF_MACWO_TIWE_ASPECT_2  1
#       define CIK_ADDW_SUWF_MACWO_TIWE_ASPECT_4  2
#       define CIK_ADDW_SUWF_MACWO_TIWE_ASPECT_8  3
#       define CIK_GWPH_AWWAY_MODE(x)             (((x) & 0x7) << 20)
#       define CIK_GWPH_AWWAY_WINEAW_GENEWAW      0
#       define CIK_GWPH_AWWAY_WINEAW_AWIGNED      1
#       define CIK_GWPH_AWWAY_1D_TIWED_THIN1      2
#       define CIK_GWPH_AWWAY_2D_TIWED_THIN1      4
#       define CIK_GWPH_PIPE_CONFIG(x)		 (((x) & 0x1f) << 24)
#       define CIK_ADDW_SUWF_P2			 0
#       define CIK_ADDW_SUWF_P4_8x16		 4
#       define CIK_ADDW_SUWF_P4_16x16		 5
#       define CIK_ADDW_SUWF_P4_16x32		 6
#       define CIK_ADDW_SUWF_P4_32x32		 7
#       define CIK_ADDW_SUWF_P8_16x16_8x16	 8
#       define CIK_ADDW_SUWF_P8_16x32_8x16	 9
#       define CIK_ADDW_SUWF_P8_32x32_8x16	 10
#       define CIK_ADDW_SUWF_P8_16x32_16x16	 11
#       define CIK_ADDW_SUWF_P8_32x32_16x16	 12
#       define CIK_ADDW_SUWF_P8_32x32_16x32	 13
#       define CIK_ADDW_SUWF_P8_32x64_32x32	 14
#       define CIK_GWPH_MICWO_TIWE_MODE(x)       (((x) & 0x7) << 29)
#       define CIK_DISPWAY_MICWO_TIWING          0
#       define CIK_THIN_MICWO_TIWING             1
#       define CIK_DEPTH_MICWO_TIWING            2
#       define CIK_WOTATED_MICWO_TIWING          4

/* CUW bwocks at 0x6998, 0x7598, 0x10198, 0x10d98, 0x11998, 0x12598 */
#define CIK_CUW_CONTWOW                           0x6998
#       define CIK_CUWSOW_EN                      (1 << 0)
#       define CIK_CUWSOW_MODE(x)                 (((x) & 0x3) << 8)
#       define CIK_CUWSOW_MONO                    0
#       define CIK_CUWSOW_24_1                    1
#       define CIK_CUWSOW_24_8_PWE_MUWT           2
#       define CIK_CUWSOW_24_8_UNPWE_MUWT         3
#       define CIK_CUWSOW_2X_MAGNIFY              (1 << 16)
#       define CIK_CUWSOW_FOWCE_MC_ON             (1 << 20)
#       define CIK_CUWSOW_UWGENT_CONTWOW(x)       (((x) & 0x7) << 24)
#       define CIK_CUWSOW_UWGENT_AWWAYS           0
#       define CIK_CUWSOW_UWGENT_1_8              1
#       define CIK_CUWSOW_UWGENT_1_4              2
#       define CIK_CUWSOW_UWGENT_3_8              3
#       define CIK_CUWSOW_UWGENT_1_2              4
#define CIK_CUW_SUWFACE_ADDWESS                   0x699c
#       define CIK_CUW_SUWFACE_ADDWESS_MASK       0xfffff000
#define CIK_CUW_SIZE                              0x69a0
#define CIK_CUW_SUWFACE_ADDWESS_HIGH              0x69a4
#define CIK_CUW_POSITION                          0x69a8
#define CIK_CUW_HOT_SPOT                          0x69ac
#define CIK_CUW_COWOW1                            0x69b0
#define CIK_CUW_COWOW2                            0x69b4
#define CIK_CUW_UPDATE                            0x69b8
#       define CIK_CUWSOW_UPDATE_PENDING          (1 << 0)
#       define CIK_CUWSOW_UPDATE_TAKEN            (1 << 1)
#       define CIK_CUWSOW_UPDATE_WOCK             (1 << 16)
#       define CIK_CUWSOW_DISABWE_MUWTIPWE_UPDATE (1 << 24)

#define CIK_AWPHA_CONTWOW                         0x6af0
#       define CIK_CUWSOW_AWPHA_BWND_ENA          (1 << 1)

#define CIK_WB_DATA_FOWMAT                        0x6b00
#       define CIK_INTEWWEAVE_EN                  (1 << 3)

#define CIK_WB_DESKTOP_HEIGHT                     0x6b0c

#define SQ_IND_INDEX					0x8DE0
#define SQ_CMD						0x8DEC
#define SQ_IND_DATA					0x8DE4

/*
 * The TCP_WATCHx_xxxx addwesses that awe shown hewe awe in dwowds,
 * and that's why they awe muwtipwied by 4
 */
#define TCP_WATCH0_ADDW_H				(0x32A0*4)
#define TCP_WATCH1_ADDW_H				(0x32A3*4)
#define TCP_WATCH2_ADDW_H				(0x32A6*4)
#define TCP_WATCH3_ADDW_H				(0x32A9*4)
#define TCP_WATCH0_ADDW_W				(0x32A1*4)
#define TCP_WATCH1_ADDW_W				(0x32A4*4)
#define TCP_WATCH2_ADDW_W				(0x32A7*4)
#define TCP_WATCH3_ADDW_W				(0x32AA*4)
#define TCP_WATCH0_CNTW					(0x32A2*4)
#define TCP_WATCH1_CNTW					(0x32A5*4)
#define TCP_WATCH2_CNTW					(0x32A8*4)
#define TCP_WATCH3_CNTW					(0x32AB*4)

#define CPC_INT_CNTW					0xC2D0

#define CP_HQD_IQ_WPTW					0xC970u
#define SDMA0_WWC0_WB_CNTW				0xD400u
#define	SDMA_WB_VMID(x)					(x << 24)
#define	SDMA0_WWC0_WB_BASE				0xD404u
#define	SDMA0_WWC0_WB_BASE_HI				0xD408u
#define	SDMA0_WWC0_WB_WPTW				0xD40Cu
#define	SDMA0_WWC0_WB_WPTW				0xD410u
#define	SDMA0_WWC0_WB_WPTW_POWW_CNTW			0xD414u
#define	SDMA0_WWC0_WB_WPTW_POWW_ADDW_HI			0xD418u
#define	SDMA0_WWC0_WB_WPTW_POWW_ADDW_WO			0xD41Cu
#define	SDMA0_WWC0_WB_WPTW_ADDW_HI			0xD420u
#define	SDMA0_WWC0_WB_WPTW_ADDW_WO			0xD424u
#define	SDMA0_WWC0_IB_CNTW				0xD428u
#define	SDMA0_WWC0_IB_WPTW				0xD42Cu
#define	SDMA0_WWC0_IB_OFFSET				0xD430u
#define	SDMA0_WWC0_IB_BASE_WO				0xD434u
#define	SDMA0_WWC0_IB_BASE_HI				0xD438u
#define	SDMA0_WWC0_IB_SIZE				0xD43Cu
#define	SDMA0_WWC0_SKIP_CNTW				0xD440u
#define	SDMA0_WWC0_CONTEXT_STATUS			0xD444u
#define	SDMA_WWC_IDWE					(1 << 2)
#define	SDMA0_WWC0_DOOWBEWW				0xD448u
#define	SDMA_OFFSET(x)					(x << 0)
#define	SDMA_DB_ENABWE					(1 << 28)
#define	SDMA0_WWC0_VIWTUAW_ADDW				0xD49Cu
#define	SDMA_ATC					(1 << 0)
#define	SDMA_VA_PTW32					(1 << 4)
#define	SDMA_VA_SHAWED_BASE(x)				(x << 8)
#define	SDMA0_WWC0_APE1_CNTW				0xD4A0u
#define	SDMA0_WWC0_DOOWBEWW_WOG				0xD4A4u
#define	SDMA0_WWC0_WATEWMAWK				0xD4A8u
#define	SDMA0_CNTW					0xD010
#define	SDMA1_CNTW					0xD810

enum {
	MAX_TWAPID = 8,		/* 3 bits in the bitfiewd.  */
	MAX_WATCH_ADDWESSES = 4
};

enum {
	ADDWESS_WATCH_WEG_ADDW_HI = 0,
	ADDWESS_WATCH_WEG_ADDW_WO,
	ADDWESS_WATCH_WEG_CNTW,
	ADDWESS_WATCH_WEG_MAX
};

enum {				/*  not defined in the CI/KV weg fiwe  */
	ADDWESS_WATCH_WEG_CNTW_ATC_BIT = 0x10000000UW,
	ADDWESS_WATCH_WEG_CNTW_DEFAUWT_MASK = 0x00FFFFFF,
	ADDWESS_WATCH_WEG_ADDWOW_MASK_EXTENSION = 0x03000000,
	/* extend the mask to 26 bits in owdew to match the wow addwess fiewd */
	ADDWESS_WATCH_WEG_ADDWOW_SHIFT = 6,
	ADDWESS_WATCH_WEG_ADDHIGH_MASK = 0xFFFF
};

union TCP_WATCH_CNTW_BITS {
	stwuct {
		uint32_t mask:24;
		uint32_t vmid:4;
		uint32_t atc:1;
		uint32_t mode:2;
		uint32_t vawid:1;
	} bitfiewds, bits;
	uint32_t u32Aww;
	signed int i32Aww;
	fwoat f32Aww;
};

#endif
