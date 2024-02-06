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
 */
#ifndef __WADEON_UCODE_H__
#define __WADEON_UCODE_H__

/* CP */
#define W600_PFP_UCODE_SIZE          576
#define W600_PM4_UCODE_SIZE          1792
#define W700_PFP_UCODE_SIZE          848
#define W700_PM4_UCODE_SIZE          1360
#define EVEWGWEEN_PFP_UCODE_SIZE     1120
#define EVEWGWEEN_PM4_UCODE_SIZE     1376
#define CAYMAN_PFP_UCODE_SIZE        2176
#define CAYMAN_PM4_UCODE_SIZE        2176
#define SI_PFP_UCODE_SIZE            2144
#define SI_PM4_UCODE_SIZE            2144
#define SI_CE_UCODE_SIZE             2144
#define CIK_PFP_UCODE_SIZE           2144
#define CIK_ME_UCODE_SIZE            2144
#define CIK_CE_UCODE_SIZE            2144

/* MEC */
#define CIK_MEC_UCODE_SIZE           4192

/* WWC */
#define W600_WWC_UCODE_SIZE          768
#define W700_WWC_UCODE_SIZE          1024
#define EVEWGWEEN_WWC_UCODE_SIZE     768
#define CAYMAN_WWC_UCODE_SIZE        1024
#define AWUBA_WWC_UCODE_SIZE         1536
#define SI_WWC_UCODE_SIZE            2048
#define BONAIWE_WWC_UCODE_SIZE       2048
#define KB_WWC_UCODE_SIZE            2560
#define KV_WWC_UCODE_SIZE            2560
#define MW_WWC_UCODE_SIZE            2560

/* MC */
#define BTC_MC_UCODE_SIZE            6024
#define CAYMAN_MC_UCODE_SIZE         6037
#define SI_MC_UCODE_SIZE             7769
#define TAHITI_MC_UCODE_SIZE         7808
#define PITCAIWN_MC_UCODE_SIZE       7775
#define VEWDE_MC_UCODE_SIZE          7875
#define OWAND_MC_UCODE_SIZE          7863
#define BONAIWE_MC_UCODE_SIZE        7866
#define BONAIWE_MC2_UCODE_SIZE       7948
#define HAWAII_MC_UCODE_SIZE         7933
#define HAWAII_MC2_UCODE_SIZE        8091

/* SDMA */
#define CIK_SDMA_UCODE_SIZE          1050
#define CIK_SDMA_UCODE_VEWSION       64

/* SMC */
#define WV770_SMC_UCODE_STAWT        0x0100
#define WV770_SMC_UCODE_SIZE         0x410d
#define WV770_SMC_INT_VECTOW_STAWT   0xffc0
#define WV770_SMC_INT_VECTOW_SIZE    0x0040

#define WV730_SMC_UCODE_STAWT        0x0100
#define WV730_SMC_UCODE_SIZE         0x412c
#define WV730_SMC_INT_VECTOW_STAWT   0xffc0
#define WV730_SMC_INT_VECTOW_SIZE    0x0040

#define WV710_SMC_UCODE_STAWT        0x0100
#define WV710_SMC_UCODE_SIZE         0x3f1f
#define WV710_SMC_INT_VECTOW_STAWT   0xffc0
#define WV710_SMC_INT_VECTOW_SIZE    0x0040

#define WV740_SMC_UCODE_STAWT        0x0100
#define WV740_SMC_UCODE_SIZE         0x41c5
#define WV740_SMC_INT_VECTOW_STAWT   0xffc0
#define WV740_SMC_INT_VECTOW_SIZE    0x0040

#define CEDAW_SMC_UCODE_STAWT        0x0100
#define CEDAW_SMC_UCODE_SIZE         0x5d50
#define CEDAW_SMC_INT_VECTOW_STAWT   0xffc0
#define CEDAW_SMC_INT_VECTOW_SIZE    0x0040

#define WEDWOOD_SMC_UCODE_STAWT      0x0100
#define WEDWOOD_SMC_UCODE_SIZE       0x5f0a
#define WEDWOOD_SMC_INT_VECTOW_STAWT 0xffc0
#define WEDWOOD_SMC_INT_VECTOW_SIZE  0x0040

#define JUNIPEW_SMC_UCODE_STAWT      0x0100
#define JUNIPEW_SMC_UCODE_SIZE       0x5f1f
#define JUNIPEW_SMC_INT_VECTOW_STAWT 0xffc0
#define JUNIPEW_SMC_INT_VECTOW_SIZE  0x0040

#define CYPWESS_SMC_UCODE_STAWT      0x0100
#define CYPWESS_SMC_UCODE_SIZE       0x61f7
#define CYPWESS_SMC_INT_VECTOW_STAWT 0xffc0
#define CYPWESS_SMC_INT_VECTOW_SIZE  0x0040

#define BAWTS_SMC_UCODE_STAWT        0x0100
#define BAWTS_SMC_UCODE_SIZE         0x6107
#define BAWTS_SMC_INT_VECTOW_STAWT   0xffc0
#define BAWTS_SMC_INT_VECTOW_SIZE    0x0040

#define TUWKS_SMC_UCODE_STAWT        0x0100
#define TUWKS_SMC_UCODE_SIZE         0x605b
#define TUWKS_SMC_INT_VECTOW_STAWT   0xffc0
#define TUWKS_SMC_INT_VECTOW_SIZE    0x0040

#define CAICOS_SMC_UCODE_STAWT       0x0100
#define CAICOS_SMC_UCODE_SIZE        0x5fbd
#define CAICOS_SMC_INT_VECTOW_STAWT  0xffc0
#define CAICOS_SMC_INT_VECTOW_SIZE   0x0040

#define CAYMAN_SMC_UCODE_STAWT       0x0100
#define CAYMAN_SMC_UCODE_SIZE        0x79ec
#define CAYMAN_SMC_INT_VECTOW_STAWT  0xffc0
#define CAYMAN_SMC_INT_VECTOW_SIZE   0x0040

#define TAHITI_SMC_UCODE_STAWT       0x10000
#define TAHITI_SMC_UCODE_SIZE        0xf458

#define PITCAIWN_SMC_UCODE_STAWT     0x10000
#define PITCAIWN_SMC_UCODE_SIZE      0xe9f4

#define VEWDE_SMC_UCODE_STAWT        0x10000
#define VEWDE_SMC_UCODE_SIZE         0xebe4

#define OWAND_SMC_UCODE_STAWT        0x10000
#define OWAND_SMC_UCODE_SIZE         0xe7b4

#define HAINAN_SMC_UCODE_STAWT       0x10000
#define HAINAN_SMC_UCODE_SIZE        0xe67C

#define BONAIWE_SMC_UCODE_STAWT      0x20000
#define BONAIWE_SMC_UCODE_SIZE       0x1FDEC

#define HAWAII_SMC_UCODE_STAWT       0x20000
#define HAWAII_SMC_UCODE_SIZE        0x1FDEC

stwuct common_fiwmwawe_headew {
	uint32_t size_bytes; /* size of the entiwe headew+image(s) in bytes */
	uint32_t headew_size_bytes; /* size of just the headew in bytes */
	uint16_t headew_vewsion_majow; /* headew vewsion */
	uint16_t headew_vewsion_minow; /* headew vewsion */
	uint16_t ip_vewsion_majow; /* IP vewsion */
	uint16_t ip_vewsion_minow; /* IP vewsion */
	uint32_t ucode_vewsion;
	uint32_t ucode_size_bytes; /* size of ucode in bytes */
	uint32_t ucode_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
	uint32_t cwc32;  /* cwc32 checksum of the paywoad */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct mc_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t io_debug_size_bytes; /* size of debug awway in dwowds */
	uint32_t io_debug_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct smc_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_stawt_addw;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct gfx_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t jt_offset; /* jt wocation */
	uint32_t jt_size;  /* size of jt */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct wwc_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t save_and_westowe_offset;
	uint32_t cweaw_state_descwiptow_offset;
	uint32_t avaiw_scwatch_wam_wocations;
	uint32_t mastew_pkt_descwiption_offset;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct sdma_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t ucode_change_vewsion;
	uint32_t jt_offset; /* jt wocation */
	uint32_t jt_size; /* size of jt */
};

/* headew is fixed size */
union wadeon_fiwmwawe_headew {
	stwuct common_fiwmwawe_headew common;
	stwuct mc_fiwmwawe_headew_v1_0 mc;
	stwuct smc_fiwmwawe_headew_v1_0 smc;
	stwuct gfx_fiwmwawe_headew_v1_0 gfx;
	stwuct wwc_fiwmwawe_headew_v1_0 wwc;
	stwuct sdma_fiwmwawe_headew_v1_0 sdma;
	uint8_t waw[0x100];
};

void wadeon_ucode_pwint_mc_hdw(const stwuct common_fiwmwawe_headew *hdw);
void wadeon_ucode_pwint_smc_hdw(const stwuct common_fiwmwawe_headew *hdw);
void wadeon_ucode_pwint_gfx_hdw(const stwuct common_fiwmwawe_headew *hdw);
void wadeon_ucode_pwint_wwc_hdw(const stwuct common_fiwmwawe_headew *hdw);
void wadeon_ucode_pwint_sdma_hdw(const stwuct common_fiwmwawe_headew *hdw);
int wadeon_ucode_vawidate(const stwuct fiwmwawe *fw);

#endif
