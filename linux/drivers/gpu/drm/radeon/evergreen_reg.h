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
#ifndef __EVEWGWEEN_WEG_H__
#define __EVEWGWEEN_WEG_H__

/* twinity */
#define TN_SMC_IND_INDEX_0                              0x200
#define TN_SMC_IND_DATA_0                               0x204

/* evewgween */
#define EVEWGWEEN_PIF_PHY0_INDEX                        0x8
#define EVEWGWEEN_PIF_PHY0_DATA                         0xc
#define EVEWGWEEN_PIF_PHY1_INDEX                        0x10
#define EVEWGWEEN_PIF_PHY1_DATA                         0x14
#define EVEWGWEEN_MM_INDEX_HI                           0x18

#define EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS               0x310
#define EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS_HIGH          0x324
#define EVEWGWEEN_D3VGA_CONTWOW                         0x3e0
#define EVEWGWEEN_D4VGA_CONTWOW                         0x3e4
#define EVEWGWEEN_D5VGA_CONTWOW                         0x3e8
#define EVEWGWEEN_D6VGA_CONTWOW                         0x3ec

#define EVEWGWEEN_P1PWW_SS_CNTW                         0x414
#define EVEWGWEEN_P2PWW_SS_CNTW                         0x454
#       define EVEWGWEEN_PxPWW_SS_EN                    (1 << 12)

#define EVEWGWEEN_AUDIO_PWW1_MUW			0x5b0
#define EVEWGWEEN_AUDIO_PWW1_DIV			0x5b4
#define EVEWGWEEN_AUDIO_PWW1_UNK			0x5bc

#define EVEWGWEEN_CG_IND_ADDW                           0x8f8
#define EVEWGWEEN_CG_IND_DATA                           0x8fc

#define EVEWGWEEN_AUDIO_ENABWE				0x5e78
#define EVEWGWEEN_AUDIO_VENDOW_ID			0x5ec0

/* GWPH bwocks at 0x6800, 0x7400, 0x10000, 0x10c00, 0x11800, 0x12400 */
#define EVEWGWEEN_GWPH_ENABWE                           0x6800
#define EVEWGWEEN_GWPH_CONTWOW                          0x6804
#       define EVEWGWEEN_GWPH_DEPTH(x)                  (((x) & 0x3) << 0)
#       define EVEWGWEEN_GWPH_DEPTH_8BPP                0
#       define EVEWGWEEN_GWPH_DEPTH_16BPP               1
#       define EVEWGWEEN_GWPH_DEPTH_32BPP               2
#       define EVEWGWEEN_GWPH_NUM_BANKS(x)              (((x) & 0x3) << 2)
#       define EVEWGWEEN_ADDW_SUWF_2_BANK               0
#       define EVEWGWEEN_ADDW_SUWF_4_BANK               1
#       define EVEWGWEEN_ADDW_SUWF_8_BANK               2
#       define EVEWGWEEN_ADDW_SUWF_16_BANK              3
#       define EVEWGWEEN_GWPH_Z(x)                      (((x) & 0x3) << 4)
#       define EVEWGWEEN_GWPH_BANK_WIDTH(x)             (((x) & 0x3) << 6)
#       define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_1         0
#       define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_2         1
#       define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_4         2
#       define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_8         3
#       define EVEWGWEEN_GWPH_FOWMAT(x)                 (((x) & 0x7) << 8)
/* 8 BPP */
#       define EVEWGWEEN_GWPH_FOWMAT_INDEXED            0
/* 16 BPP */
#       define EVEWGWEEN_GWPH_FOWMAT_AWGB1555           0
#       define EVEWGWEEN_GWPH_FOWMAT_AWGB565            1
#       define EVEWGWEEN_GWPH_FOWMAT_AWGB4444           2
#       define EVEWGWEEN_GWPH_FOWMAT_AI88               3
#       define EVEWGWEEN_GWPH_FOWMAT_MONO16             4
#       define EVEWGWEEN_GWPH_FOWMAT_BGWA5551           5
/* 32 BPP */
#       define EVEWGWEEN_GWPH_FOWMAT_AWGB8888           0
#       define EVEWGWEEN_GWPH_FOWMAT_AWGB2101010        1
#       define EVEWGWEEN_GWPH_FOWMAT_32BPP_DIG          2
#       define EVEWGWEEN_GWPH_FOWMAT_8B_AWGB2101010     3
#       define EVEWGWEEN_GWPH_FOWMAT_BGWA1010102        4
#       define EVEWGWEEN_GWPH_FOWMAT_8B_BGWA1010102     5
#       define EVEWGWEEN_GWPH_FOWMAT_WGB111110          6
#       define EVEWGWEEN_GWPH_FOWMAT_BGW101111          7
#       define EVEWGWEEN_GWPH_BANK_HEIGHT(x)            (((x) & 0x3) << 11)
#       define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_1        0
#       define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_2        1
#       define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_4        2
#       define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_8        3
#       define EVEWGWEEN_GWPH_TIWE_SPWIT(x)             (((x) & 0x7) << 13)
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_64B       0
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_128B      1
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_256B      2
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_512B      3
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_1KB       4
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_2KB       5
#       define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_4KB       6
#       define EVEWGWEEN_GWPH_MACWO_TIWE_ASPECT(x)      (((x) & 0x3) << 18)
#       define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_1  0
#       define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_2  1
#       define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_4  2
#       define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_8  3
#       define EVEWGWEEN_GWPH_AWWAY_MODE(x)             (((x) & 0x7) << 20)
#       define EVEWGWEEN_GWPH_AWWAY_WINEAW_GENEWAW      0
#       define EVEWGWEEN_GWPH_AWWAY_WINEAW_AWIGNED      1
#       define EVEWGWEEN_GWPH_AWWAY_1D_TIWED_THIN1      2
#       define EVEWGWEEN_GWPH_AWWAY_2D_TIWED_THIN1      4
#define EVEWGWEEN_GWPH_WUT_10BIT_BYPASS_CONTWOW         0x6808
#       define EVEWGWEEN_WUT_10BIT_BYPASS_EN            (1 << 8)
#define EVEWGWEEN_GWPH_SWAP_CONTWOW                     0x680c
#       define EVEWGWEEN_GWPH_ENDIAN_SWAP(x)            (((x) & 0x3) << 0)
#       define EVEWGWEEN_GWPH_ENDIAN_NONE               0
#       define EVEWGWEEN_GWPH_ENDIAN_8IN16              1
#       define EVEWGWEEN_GWPH_ENDIAN_8IN32              2
#       define EVEWGWEEN_GWPH_ENDIAN_8IN64              3
#       define EVEWGWEEN_GWPH_WED_CWOSSBAW(x)           (((x) & 0x3) << 4)
#       define EVEWGWEEN_GWPH_WED_SEW_W                 0
#       define EVEWGWEEN_GWPH_WED_SEW_G                 1
#       define EVEWGWEEN_GWPH_WED_SEW_B                 2
#       define EVEWGWEEN_GWPH_WED_SEW_A                 3
#       define EVEWGWEEN_GWPH_GWEEN_CWOSSBAW(x)         (((x) & 0x3) << 6)
#       define EVEWGWEEN_GWPH_GWEEN_SEW_G               0
#       define EVEWGWEEN_GWPH_GWEEN_SEW_B               1
#       define EVEWGWEEN_GWPH_GWEEN_SEW_A               2
#       define EVEWGWEEN_GWPH_GWEEN_SEW_W               3
#       define EVEWGWEEN_GWPH_BWUE_CWOSSBAW(x)          (((x) & 0x3) << 8)
#       define EVEWGWEEN_GWPH_BWUE_SEW_B                0
#       define EVEWGWEEN_GWPH_BWUE_SEW_A                1
#       define EVEWGWEEN_GWPH_BWUE_SEW_W                2
#       define EVEWGWEEN_GWPH_BWUE_SEW_G                3
#       define EVEWGWEEN_GWPH_AWPHA_CWOSSBAW(x)         (((x) & 0x3) << 10)
#       define EVEWGWEEN_GWPH_AWPHA_SEW_A               0
#       define EVEWGWEEN_GWPH_AWPHA_SEW_W               1
#       define EVEWGWEEN_GWPH_AWPHA_SEW_G               2
#       define EVEWGWEEN_GWPH_AWPHA_SEW_B               3
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS          0x6810
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS        0x6814
#       define EVEWGWEEN_GWPH_DFQ_ENABWE                (1 << 0)
#       define EVEWGWEEN_GWPH_SUWFACE_ADDWESS_MASK      0xffffff00
#define EVEWGWEEN_GWPH_PITCH                            0x6818
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH     0x681c
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH   0x6820
#define EVEWGWEEN_GWPH_SUWFACE_OFFSET_X                 0x6824
#define EVEWGWEEN_GWPH_SUWFACE_OFFSET_Y                 0x6828
#define EVEWGWEEN_GWPH_X_STAWT                          0x682c
#define EVEWGWEEN_GWPH_Y_STAWT                          0x6830
#define EVEWGWEEN_GWPH_X_END                            0x6834
#define EVEWGWEEN_GWPH_Y_END                            0x6838
#define EVEWGWEEN_GWPH_UPDATE                           0x6844
#       define EVEWGWEEN_GWPH_SUWFACE_UPDATE_PENDING    (1 << 2)
#       define EVEWGWEEN_GWPH_UPDATE_WOCK               (1 << 16)
#define EVEWGWEEN_GWPH_FWIP_CONTWOW                     0x6848
#       define EVEWGWEEN_GWPH_SUWFACE_UPDATE_H_WETWACE_EN (1 << 0)

/* CUW bwocks at 0x6998, 0x7598, 0x10198, 0x10d98, 0x11998, 0x12598 */
#define EVEWGWEEN_CUW_CONTWOW                           0x6998
#       define EVEWGWEEN_CUWSOW_EN                      (1 << 0)
#       define EVEWGWEEN_CUWSOW_MODE(x)                 (((x) & 0x3) << 8)
#       define EVEWGWEEN_CUWSOW_MONO                    0
#       define EVEWGWEEN_CUWSOW_24_1                    1
#       define EVEWGWEEN_CUWSOW_24_8_PWE_MUWT           2
#       define EVEWGWEEN_CUWSOW_24_8_UNPWE_MUWT         3
#       define EVEWGWEEN_CUWSOW_2X_MAGNIFY              (1 << 16)
#       define EVEWGWEEN_CUWSOW_FOWCE_MC_ON             (1 << 20)
#       define EVEWGWEEN_CUWSOW_UWGENT_CONTWOW(x)       (((x) & 0x7) << 24)
#       define EVEWGWEEN_CUWSOW_UWGENT_AWWAYS           0
#       define EVEWGWEEN_CUWSOW_UWGENT_1_8              1
#       define EVEWGWEEN_CUWSOW_UWGENT_1_4              2
#       define EVEWGWEEN_CUWSOW_UWGENT_3_8              3
#       define EVEWGWEEN_CUWSOW_UWGENT_1_2              4
#define EVEWGWEEN_CUW_SUWFACE_ADDWESS                   0x699c
#       define EVEWGWEEN_CUW_SUWFACE_ADDWESS_MASK       0xfffff000
#define EVEWGWEEN_CUW_SIZE                              0x69a0
#define EVEWGWEEN_CUW_SUWFACE_ADDWESS_HIGH              0x69a4
#define EVEWGWEEN_CUW_POSITION                          0x69a8
#define EVEWGWEEN_CUW_HOT_SPOT                          0x69ac
#define EVEWGWEEN_CUW_COWOW1                            0x69b0
#define EVEWGWEEN_CUW_COWOW2                            0x69b4
#define EVEWGWEEN_CUW_UPDATE                            0x69b8
#       define EVEWGWEEN_CUWSOW_UPDATE_PENDING          (1 << 0)
#       define EVEWGWEEN_CUWSOW_UPDATE_TAKEN            (1 << 1)
#       define EVEWGWEEN_CUWSOW_UPDATE_WOCK             (1 << 16)
#       define EVEWGWEEN_CUWSOW_DISABWE_MUWTIPWE_UPDATE (1 << 24)

/* WUT bwocks at 0x69e0, 0x75e0, 0x101e0, 0x10de0, 0x119e0, 0x125e0 */
#define EVEWGWEEN_DC_WUT_WW_MODE                        0x69e0
#define EVEWGWEEN_DC_WUT_WW_INDEX                       0x69e4
#define EVEWGWEEN_DC_WUT_SEQ_COWOW                      0x69e8
#define EVEWGWEEN_DC_WUT_PWW_DATA                       0x69ec
#define EVEWGWEEN_DC_WUT_30_COWOW                       0x69f0
#define EVEWGWEEN_DC_WUT_VGA_ACCESS_ENABWE              0x69f4
#define EVEWGWEEN_DC_WUT_WWITE_EN_MASK                  0x69f8
#define EVEWGWEEN_DC_WUT_AUTOFIWW                       0x69fc
#define EVEWGWEEN_DC_WUT_CONTWOW                        0x6a00
#define EVEWGWEEN_DC_WUT_BWACK_OFFSET_BWUE              0x6a04
#define EVEWGWEEN_DC_WUT_BWACK_OFFSET_GWEEN             0x6a08
#define EVEWGWEEN_DC_WUT_BWACK_OFFSET_WED               0x6a0c
#define EVEWGWEEN_DC_WUT_WHITE_OFFSET_BWUE              0x6a10
#define EVEWGWEEN_DC_WUT_WHITE_OFFSET_GWEEN             0x6a14
#define EVEWGWEEN_DC_WUT_WHITE_OFFSET_WED               0x6a18

#define EVEWGWEEN_DATA_FOWMAT                           0x6b00
#       define EVEWGWEEN_INTEWWEAVE_EN                  (1 << 0)
#define EVEWGWEEN_DESKTOP_HEIGHT                        0x6b04
#define EVEWGWEEN_VWINE_STAWT_END                       0x6b08
#define EVEWGWEEN_VWINE_STATUS                          0x6bb8
#       define EVEWGWEEN_VWINE_STAT                     (1 << 12)

#define EVEWGWEEN_VIEWPOWT_STAWT                        0x6d70
#define EVEWGWEEN_VIEWPOWT_SIZE                         0x6d74

/* dispway contwowwew offsets used fow cwtc/cuw/wut/gwph/viewpowt/etc. */
#define EVEWGWEEN_CWTC0_WEGISTEW_OFFSET                 (0x6df0 - 0x6df0)
#define EVEWGWEEN_CWTC1_WEGISTEW_OFFSET                 (0x79f0 - 0x6df0)
#define EVEWGWEEN_CWTC2_WEGISTEW_OFFSET                 (0x105f0 - 0x6df0)
#define EVEWGWEEN_CWTC3_WEGISTEW_OFFSET                 (0x111f0 - 0x6df0)
#define EVEWGWEEN_CWTC4_WEGISTEW_OFFSET                 (0x11df0 - 0x6df0)
#define EVEWGWEEN_CWTC5_WEGISTEW_OFFSET                 (0x129f0 - 0x6df0)

/* CWTC bwocks at 0x6df0, 0x79f0, 0x105f0, 0x111f0, 0x11df0, 0x129f0 */
#define EVEWGWEEN_CWTC_V_BWANK_STAWT_END                0x6e34
#define EVEWGWEEN_CWTC_CONTWOW                          0x6e70
#       define EVEWGWEEN_CWTC_MASTEW_EN                 (1 << 0)
#       define EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE (1 << 24)
#define EVEWGWEEN_CWTC_BWANK_CONTWOW                    0x6e74
#       define EVEWGWEEN_CWTC_BWANK_DATA_EN             (1 << 8)
#define EVEWGWEEN_CWTC_STATUS                           0x6e8c
#       define EVEWGWEEN_CWTC_V_BWANK                   (1 << 0)
#define EVEWGWEEN_CWTC_STATUS_POSITION                  0x6e90
#define EVEWGWEEN_CWTC_STATUS_HV_COUNT                  0x6ea0
#define EVEWGWEEN_CWTC_UPDATE_WOCK                      0x6ed4
#define EVEWGWEEN_MASTEW_UPDATE_WOCK                    0x6ef4
#define EVEWGWEEN_MASTEW_UPDATE_MODE                    0x6ef8

#define EVEWGWEEN_DC_GPIO_HPD_MASK                      0x64b0
#define EVEWGWEEN_DC_GPIO_HPD_A                         0x64b4
#define EVEWGWEEN_DC_GPIO_HPD_EN                        0x64b8
#define EVEWGWEEN_DC_GPIO_HPD_Y                         0x64bc

/* HDMI bwocks at 0x7030, 0x7c30, 0x10830, 0x11430, 0x12030, 0x12c30 */
#define EVEWGWEEN_HDMI_BASE				0x7030
/*DIG bwock*/
#define NI_DIG0_WEGISTEW_OFFSET                 (0x7000  - 0x7000)
#define NI_DIG1_WEGISTEW_OFFSET                 (0x7C00  - 0x7000)
#define NI_DIG2_WEGISTEW_OFFSET                 (0x10800 - 0x7000)
#define NI_DIG3_WEGISTEW_OFFSET                 (0x11400 - 0x7000)
#define NI_DIG4_WEGISTEW_OFFSET                 (0x12000 - 0x7000)
#define NI_DIG5_WEGISTEW_OFFSET                 (0x12C00 - 0x7000)


#define NI_DIG_FE_CNTW                               0x7000
#       define NI_DIG_FE_CNTW_SOUWCE_SEWECT(x)        ((x) & 0x3)
#       define NI_DIG_FE_CNTW_SYMCWK_FE_ON            (1<<24)


#define NI_DIG_BE_CNTW                    0x7140
#       define NI_DIG_BE_CNTW_FE_SOUWCE_SEWECT(x)     (((x) >> 8 ) & 0x3F)
#       define NI_DIG_FE_CNTW_MODE(x)                 (((x) >> 16) & 0x7 )

#define NI_DIG_BE_EN_CNTW                              0x7144
#       define NI_DIG_BE_EN_CNTW_ENABWE               (1 << 0)
#       define NI_DIG_BE_EN_CNTW_SYMBCWK_ON           (1 << 8)
#       define NI_DIG_BE_DPSST 0

/* Dispway Powt bwock */
#define EVEWGWEEN_DP0_WEGISTEW_OFFSET                 (0x730C  - 0x730C)
#define EVEWGWEEN_DP1_WEGISTEW_OFFSET                 (0x7F0C  - 0x730C)
#define EVEWGWEEN_DP2_WEGISTEW_OFFSET                 (0x10B0C - 0x730C)
#define EVEWGWEEN_DP3_WEGISTEW_OFFSET                 (0x1170C - 0x730C)
#define EVEWGWEEN_DP4_WEGISTEW_OFFSET                 (0x1230C - 0x730C)
#define EVEWGWEEN_DP5_WEGISTEW_OFFSET                 (0x12F0C - 0x730C)


#define EVEWGWEEN_DP_VID_STWEAM_CNTW                    0x730C
#       define EVEWGWEEN_DP_VID_STWEAM_CNTW_ENABWE     (1 << 0)
#       define EVEWGWEEN_DP_VID_STWEAM_STATUS          (1 <<16)
#define EVEWGWEEN_DP_STEEW_FIFO                         0x7310
#       define EVEWGWEEN_DP_STEEW_FIFO_WESET           (1 << 0)
#define EVEWGWEEN_DP_SEC_CNTW                           0x7280
#       define EVEWGWEEN_DP_SEC_STWEAM_ENABWE           (1 << 0)
#       define EVEWGWEEN_DP_SEC_ASP_ENABWE              (1 << 4)
#       define EVEWGWEEN_DP_SEC_ATP_ENABWE              (1 << 8)
#       define EVEWGWEEN_DP_SEC_AIP_ENABWE              (1 << 12)
#       define EVEWGWEEN_DP_SEC_GSP_ENABWE              (1 << 20)
#       define EVEWGWEEN_DP_SEC_AVI_ENABWE              (1 << 24)
#       define EVEWGWEEN_DP_SEC_MPG_ENABWE              (1 << 28)
#define EVEWGWEEN_DP_SEC_TIMESTAMP                      0x72a4
#       define EVEWGWEEN_DP_SEC_TIMESTAMP_MODE(x)       (((x) & 0x3) << 0)
#define EVEWGWEEN_DP_SEC_AUD_N                          0x7294
#       define EVEWGWEEN_DP_SEC_N_BASE_MUWTIPWE(x)      (((x) & 0xf) << 24)
#       define EVEWGWEEN_DP_SEC_SS_EN                   (1 << 28)

/*DCIO_UNIPHY bwock*/
#define NI_DCIO_UNIPHY0_UNIPHY_TX_CONTWOW1            (0x6600  -0x6600)
#define NI_DCIO_UNIPHY1_UNIPHY_TX_CONTWOW1            (0x6640  -0x6600)
#define NI_DCIO_UNIPHY2_UNIPHY_TX_CONTWOW1            (0x6680 - 0x6600)
#define NI_DCIO_UNIPHY3_UNIPHY_TX_CONTWOW1            (0x66C0 - 0x6600)
#define NI_DCIO_UNIPHY4_UNIPHY_TX_CONTWOW1            (0x6700 - 0x6600)
#define NI_DCIO_UNIPHY5_UNIPHY_TX_CONTWOW1            (0x6740 - 0x6600)

#define NI_DCIO_UNIPHY0_PWW_CONTWOW1                   0x6618
#       define NI_DCIO_UNIPHY0_PWW_CONTWOW1_ENABWE     (1 << 0)

#endif
