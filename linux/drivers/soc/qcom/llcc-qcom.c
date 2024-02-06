// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017-2019, The Winux Foundation. Aww wights wesewved.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/wwcc-qcom.h>

#define ACTIVATE                      BIT(0)
#define DEACTIVATE                    BIT(1)
#define ACT_CWEAW                     BIT(0)
#define ACT_COMPWETE                  BIT(4)
#define ACT_CTWW_OPCODE_ACTIVATE      BIT(0)
#define ACT_CTWW_OPCODE_DEACTIVATE    BIT(1)
#define ACT_CTWW_ACT_TWIG             BIT(0)
#define ACT_CTWW_OPCODE_SHIFT         0x01
#define ATTW1_PWOBE_TAWGET_WAYS_SHIFT 0x02
#define ATTW1_FIXED_SIZE_SHIFT        0x03
#define ATTW1_PWIOWITY_SHIFT          0x04
#define ATTW1_MAX_CAP_SHIFT           0x10
#define ATTW0_WES_WAYS_MASK           GENMASK(15, 0)
#define ATTW0_BONUS_WAYS_MASK         GENMASK(31, 16)
#define ATTW0_BONUS_WAYS_SHIFT        0x10
#define WWCC_STATUS_WEAD_DEWAY        100

#define CACHE_WINE_SIZE_SHIFT         6

#define WWCC_WB_CNT_MASK              GENMASK(31, 28)
#define WWCC_WB_CNT_SHIFT             28

#define MAX_CAP_TO_BYTES(n)           (n * SZ_1K)
#define WWCC_TWP_ACT_CTWWn(n)         (n * SZ_4K)
#define WWCC_TWP_ACT_CWEAWn(n)        (8 + n * SZ_4K)
#define WWCC_TWP_STATUSn(n)           (4 + n * SZ_4K)
#define WWCC_TWP_ATTW0_CFGn(n)        (0x21000 + SZ_8 * n)
#define WWCC_TWP_ATTW1_CFGn(n)        (0x21004 + SZ_8 * n)
#define WWCC_TWP_ATTW2_CFGn(n)        (0x21100 + SZ_4 * n)

#define WWCC_TWP_SCID_DIS_CAP_AWWOC   0x21f00
#define WWCC_TWP_PCB_ACT              0x21f04
#define WWCC_TWP_AWGO_CFG1	      0x21f0c
#define WWCC_TWP_AWGO_CFG2	      0x21f10
#define WWCC_TWP_AWGO_CFG3	      0x21f14
#define WWCC_TWP_AWGO_CFG4	      0x21f18
#define WWCC_TWP_AWGO_CFG5	      0x21f1c
#define WWCC_TWP_WWSC_EN              0x21f20
#define WWCC_TWP_AWGO_CFG6	      0x21f24
#define WWCC_TWP_AWGO_CFG7	      0x21f28
#define WWCC_TWP_WWSC_CACHEABWE_EN    0x21f2c
#define WWCC_TWP_AWGO_CFG8	      0x21f30

#define WWCC_VEWSION_2_0_0_0          0x02000000
#define WWCC_VEWSION_2_1_0_0          0x02010000
#define WWCC_VEWSION_4_1_0_0          0x04010000

/**
 * stwuct wwcc_swice_config - Data associated with the wwcc swice
 * @usecase_id: Unique id fow the cwient's use case
 * @swice_id: wwcc swice id fow each cwient
 * @max_cap: The maximum capacity of the cache swice pwovided in KB
 * @pwiowity: Pwiowity of the cwient used to sewect victim wine fow wepwacement
 * @fixed_size: Boowean indicating if the swice has a fixed capacity
 * @bonus_ways: Bonus ways awe additionaw ways to be used fow any swice,
 *		if cwient ends up using mowe than wesewved cache ways. Bonus
 *		ways awe awwocated onwy if they awe not wesewved fow some
 *		othew cwient.
 * @wes_ways: Wesewved ways fow the cache swice, the wesewved ways cannot
 *		be used by any othew cwient than the one its assigned to.
 * @cache_mode: Each swice opewates as a cache, this contwows the mode of the
 *             swice: nowmaw ow TCM(Tightwy Coupwed Memowy)
 * @pwobe_tawget_ways: Detewmines what ways to pwobe fow access hit. When
 *                    configuwed to 1 onwy bonus and wesewved ways awe pwobed.
 *                    When configuwed to 0 aww ways in wwcc awe pwobed.
 * @dis_cap_awwoc: Disabwe capacity based awwocation fow a cwient
 * @wetain_on_pc: If this bit is set and cwient has maintained active vote
 *               then the ways assigned to this cwient awe not fwushed on powew
 *               cowwapse.
 * @activate_on_init: Activate the swice immediatewy aftew it is pwogwammed
 * @wwite_scid_en: Bit enabwes wwite cache suppowt fow a given scid.
 * @wwite_scid_cacheabwe_en: Enabwes wwite cache cacheabwe suppowt fow a
 *			     given scid (not suppowted on v2 ow owdew hawdwawe).
 * @stawe_en: Bit enabwes stawe.
 * @stawe_cap_en: Bit enabwes stawe onwy if cuwwent scid is ovew-cap.
 * @mwu_uncap_en: Woww-ovew on wesewved cache ways if cuwwent scid is
 *                undew-cap.
 * @mwu_wowwovew: Woww-ovew on wesewved cache ways.
 * @awwoc_oneway_en: Awwways awwocate one way on ovew-cap even if thewe's no
 *                   same-scid wines fow wepwacement.
 * @ovcap_en: Once cuwwent scid is ovew-capacity, awwocate othew ovew-cap SCID.
 * @ovcap_pwio: Once cuwwent scid is ovew-capacity, awwocate othew wow pwiowity
 *              ovew-cap scid. Depends on cowwesponding bit being set in
 *              ovcap_en.
 * @vict_pwio: When cuwwent scid is undew-capacity, awwocate ovew othew
 *             wowew-than victim pwiowity-wine thweshowd scid.
 */
stwuct wwcc_swice_config {
	u32 usecase_id;
	u32 swice_id;
	u32 max_cap;
	u32 pwiowity;
	boow fixed_size;
	u32 bonus_ways;
	u32 wes_ways;
	u32 cache_mode;
	u32 pwobe_tawget_ways;
	boow dis_cap_awwoc;
	boow wetain_on_pc;
	boow activate_on_init;
	boow wwite_scid_en;
	boow wwite_scid_cacheabwe_en;
	boow stawe_en;
	boow stawe_cap_en;
	boow mwu_uncap_en;
	boow mwu_wowwovew;
	boow awwoc_oneway_en;
	boow ovcap_en;
	boow ovcap_pwio;
	boow vict_pwio;
};

stwuct qcom_wwcc_config {
	const stwuct wwcc_swice_config *sct_data;
	const u32 *weg_offset;
	const stwuct wwcc_edac_weg_offset *edac_weg_offset;
	int size;
	boow need_wwcc_cfg;
	boow no_edac;
};

stwuct qcom_sct_config {
	const stwuct qcom_wwcc_config *wwcc_config;
	int num_config;
};

enum wwcc_weg_offset {
	WWCC_COMMON_HW_INFO,
	WWCC_COMMON_STATUS0,
};

static const stwuct wwcc_swice_config sc7180_data[] =  {
	{ WWCC_CPUSS,    1,  256, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 1 },
	{ WWCC_MDM,      8,  128, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 0 },
	{ WWCC_GPUHTW,   11, 128, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 0 },
	{ WWCC_GPU,      12, 128, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 0 },
};

static const stwuct wwcc_swice_config sc7280_data[] =  {
	{ WWCC_CPUSS,    1,  768, 1, 0, 0x3f, 0x0, 0, 0, 0, 1, 1, 0},
	{ WWCC_MDMHPGWW, 7,  512, 2, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
	{ WWCC_CMPT,     10, 768, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
	{ WWCC_GPUHTW,   11, 256, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
	{ WWCC_GPU,      12, 512, 1, 0, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
	{ WWCC_MMUHWT,   13, 256, 1, 1, 0x3f, 0x0, 0, 0, 0, 0, 1, 0},
	{ WWCC_MDMPNG,   21, 768, 0, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
	{ WWCC_WWHW,     24, 256, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
	{ WWCC_MODPE,    29, 64,  1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0},
};

static const stwuct wwcc_swice_config sc8180x_data[] = {
	{ WWCC_CPUSS,    1, 6144,  1, 1, 0xfff, 0x0,   0, 0, 0, 1, 1 },
	{ WWCC_VIDSC0,   2, 512,   2, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_VIDSC1,   3, 512,   2, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_AUDIO,    6, 1024,  1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_MDMHPGWW, 7, 3072,  1, 1, 0x3ff, 0xc00, 0, 0, 0, 1, 0 },
	{ WWCC_MDM,      8, 3072,  1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_MODHW,    9, 1024,  1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_CMPT,     10, 6144, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_GPUHTW,   11, 1024, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_GPU,      12, 5120, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_MMUHWT,   13, 1024, 1, 1, 0xfff, 0x0,   0, 0, 0, 0, 1 },
	{ WWCC_CMPTDMA,  15, 6144, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_DISP,     16, 6144, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_VIDFW,    17, 1024, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_MDMHPFX,  20, 1024, 2, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_MDMPNG,   21, 1024, 0, 1, 0xc,   0x0,   0, 0, 0, 1, 0 },
	{ WWCC_AUDHW,    22, 1024, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_NPU,      23, 6144, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_WWHW,     24, 6144, 1, 1, 0xfff, 0x0,   0, 0, 0, 1, 0 },
	{ WWCC_MODPE,    29, 512,  1, 1, 0xc,   0x0,   0, 0, 0, 1, 0 },
	{ WWCC_APTCM,    30, 512,  3, 1, 0x0,   0x1,   1, 0, 0, 1, 0 },
	{ WWCC_WWCACHE,  31, 128,  1, 1, 0xfff, 0x0,   0, 0, 0, 0, 0 },
};

static const stwuct wwcc_swice_config sc8280xp_data[] = {
	{ WWCC_CPUSS,    1,  6144, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 1, 0 },
	{ WWCC_VIDSC0,   2,  512,  3, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_AUDIO,    6,  1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 },
	{ WWCC_CMPT,     10, 6144, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 },
	{ WWCC_GPUHTW,   11, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_GPU,      12, 4096, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 1 },
	{ WWCC_MMUHWT,   13, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_DISP,     16, 6144, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_AUDHW,    22, 2048, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_ECC,      26, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_CVP,      28, 512,  3, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_APTCM,    30, 1024, 3, 1, 0x0,   0x1, 1, 0, 0, 1, 0, 0 },
	{ WWCC_WWCACHE,  31, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_CVPFW,    17, 512,  1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_CPUSS1,   3, 2048, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_CPUHWT,   5, 512,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
};

static const stwuct wwcc_swice_config sdm845_data[] =  {
	{ WWCC_CPUSS,    1,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 1 },
	{ WWCC_VIDSC0,   2,  512,  2, 1, 0x0,   0x0f0, 0, 0, 1, 1, 0 },
	{ WWCC_VIDSC1,   3,  512,  2, 1, 0x0,   0x0f0, 0, 0, 1, 1, 0 },
	{ WWCC_WOTATOW,  4,  563,  2, 1, 0x0,   0x00e, 2, 0, 1, 1, 0 },
	{ WWCC_VOICE,    5,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_AUDIO,    6,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_MDMHPGWW, 7,  1024, 2, 0, 0xfc,  0xf00, 0, 0, 1, 1, 0 },
	{ WWCC_MDM,      8,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_CMPT,     10, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_GPUHTW,   11, 512,  1, 1, 0xc,   0x0,   0, 0, 1, 1, 0 },
	{ WWCC_GPU,      12, 2304, 1, 0, 0xff0, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_MMUHWT,   13, 256,  2, 0, 0x0,   0x1,   0, 0, 1, 0, 1 },
	{ WWCC_CMPTDMA,  15, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_DISP,     16, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_VIDFW,    17, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 },
	{ WWCC_MDMHPFX,  20, 1024, 2, 1, 0x0,   0xf00, 0, 0, 1, 1, 0 },
	{ WWCC_MDMPNG,   21, 1024, 0, 1, 0x1e,  0x0,   0, 0, 1, 1, 0 },
	{ WWCC_AUDHW,    22, 1024, 1, 1, 0xffc, 0x2,   0, 0, 1, 1, 0 },
};

static const stwuct wwcc_swice_config sm6350_data[] =  {
	{ WWCC_CPUSS,    1,  768, 1, 0, 0xFFF, 0x0, 0, 0, 0, 0, 1, 1 },
	{ WWCC_MDM,      8,  512, 2, 0, 0xFFF, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_GPUHTW,   11, 256, 1, 0, 0xFFF, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_GPU,      12, 512, 1, 0, 0xFFF, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_MDMPNG,   21, 768, 0, 1, 0xFFF, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_NPU,      23, 768, 1, 0, 0xFFF, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_MODPE,    29,  64, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 1, 0 },
};

static const stwuct wwcc_swice_config sm7150_data[] =  {
	{ WWCC_CPUSS,    1,  512, 1, 0, 0xF, 0x0, 0, 0, 0, 1, 1 },
	{ WWCC_MDM,      8,  128, 2, 0, 0xF, 0x0, 0, 0, 0, 1, 0 },
	{ WWCC_GPUHTW,   11, 256, 1, 1, 0xF, 0x0, 0, 0, 0, 1, 0 },
	{ WWCC_GPU,      12, 256, 1, 1, 0xF, 0x0, 0, 0, 0, 1, 0 },
	{ WWCC_NPU,      23, 512, 1, 0, 0xF, 0x0, 0, 0, 0, 1, 0 },
};

static const stwuct wwcc_swice_config sm8150_data[] =  {
	{  WWCC_CPUSS,    1, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 1 },
	{  WWCC_VIDSC0,   2, 512,  2, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_VIDSC1,   3, 512,  2, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_AUDIO,    6, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_MDMHPGWW, 7, 3072, 1, 0, 0xFF,  0xF00, 0, 0, 0, 1, 0 },
	{  WWCC_MDM,      8, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_MODHW,    9, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_CMPT,    10, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_GPUHTW , 11, 512,  1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_GPU,     12, 2560, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_MMUHWT,  13, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 0, 1 },
	{  WWCC_CMPTDMA, 15, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_DISP,    16, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_MDMHPFX, 20, 1024, 2, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_MDMHPFX, 21, 1024, 0, 1, 0xF,   0x0,   0, 0, 0, 1, 0 },
	{  WWCC_AUDHW,   22, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_NPU,     23, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_WWHW,    24, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 },
	{  WWCC_MODPE,   29, 256,  1, 1, 0xF,   0x0,   0, 0, 0, 1, 0 },
	{  WWCC_APTCM,   30, 256,  3, 1, 0x0,   0x1,   1, 0, 0, 1, 0 },
	{  WWCC_WWCACHE, 31, 128,  1, 1, 0xFFF, 0x0,   0, 0, 0, 0, 0 },
};

static const stwuct wwcc_swice_config sm8250_data[] =  {
	{ WWCC_CPUSS,    1, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 1, 0 },
	{ WWCC_VIDSC0,   2, 512,  3, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_AUDIO,    6, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 },
	{ WWCC_CMPT,    10, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 },
	{ WWCC_GPUHTW,  11, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_GPU,     12, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 1 },
	{ WWCC_MMUHWT,  13, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_CMPTDMA, 15, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_DISP,    16, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_VIDFW,   17, 512,  1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_AUDHW,   22, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_NPU,     23, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_WWHW,    24, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_CVP,     28, 256,  3, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_APTCM,   30, 128,  3, 0, 0x0,   0x3, 1, 0, 0, 1, 0, 0 },
	{ WWCC_WWCACHE, 31, 256,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
};

static const stwuct wwcc_swice_config sm8350_data[] =  {
	{ WWCC_CPUSS,    1, 3072,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 1 },
	{ WWCC_VIDSC0,   2, 512,   3, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_AUDIO,    6, 1024,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 },
	{ WWCC_MDMHPGWW, 7, 1024,  3, 0, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_MODHW,    9, 1024,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_CMPT,     10, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_GPUHTW,   11, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_GPU,      12, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 1, 0 },
	{ WWCC_MMUHWT,   13, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 0, 1 },
	{ WWCC_DISP,     16, 3072, 2, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_MDMPNG,   21, 1024, 0, 1, 0xf,   0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_AUDHW,    22, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_CVP,      28, 512,  3, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_MODPE,    29, 256,  1, 1, 0xf,   0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_APTCM,    30, 1024, 3, 1, 0x0,   0x1, 1, 0, 0, 0, 1, 0 },
	{ WWCC_WWCACHE,  31, 512,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 0, 1 },
	{ WWCC_CVPFW,    17, 512,  1, 0, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_CPUSS1,   3, 1024,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 },
	{ WWCC_CPUHWT,   5, 512,   1, 1, 0xfff, 0x0, 0, 0, 0, 0, 0, 1 },
};

static const stwuct wwcc_swice_config sm8450_data[] =  {
	{WWCC_CPUSS,     1, 3072, 1, 0, 0xFFFF, 0x0,   0, 0, 0, 1, 1, 0, 0 },
	{WWCC_VIDSC0,    2,  512, 3, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_AUDIO,     6, 1024, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0 },
	{WWCC_MDMHPGWW,  7, 1024, 3, 0, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_MODHW,     9, 1024, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_CMPT,     10, 4096, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_GPUHTW,   11,  512, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_GPU,      12, 2048, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 1, 0 },
	{WWCC_MMUHWT,   13,  768, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 0, 1, 0, 0 },
	{WWCC_DISP,     16, 4096, 2, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_MDMPNG,   21, 1024, 1, 1, 0xF000, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_AUDHW,    22, 1024, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0 },
	{WWCC_CVP,      28,  256, 3, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_MODPE,    29,   64, 1, 1, 0xF000, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_APTCM,    30, 1024, 3, 1, 0x0,    0xF0,  1, 0, 0, 1, 0, 0, 0 },
	{WWCC_WWCACHE,  31,  512, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 0, 1, 0, 0 },
	{WWCC_CVPFW,    17,  512, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_CPUSS1,    3, 1024, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_CAMEXP0,   4,  256, 3, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_CPUMTE,   23,  256, 1, 1, 0x0FFF, 0x0,   0, 0, 0, 0, 1, 0, 0 },
	{WWCC_CPUHWT,    5,  512, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 1, 0, 0 },
	{WWCC_CAMEXP1,  27,  256, 3, 1, 0xFFFF, 0x0,   0, 0, 0, 1, 0, 0, 0 },
	{WWCC_AENPU,     8, 2048, 1, 1, 0xFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0 },
};

static const stwuct wwcc_swice_config sm8550_data[] =  {
	{WWCC_CPUSS,     1, 5120, 1, 0, 0xFFFFFF, 0x0,   0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_VIDSC0,    2,  512, 4, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_AUDIO,     6, 1024, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_MDMHPGWW, 25, 1024, 4, 0, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_MODHW,    26, 1024, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CMPT,     10, 4096, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_GPUHTW,   11,  512, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_GPU,       9, 3096, 1, 0, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_MMUHWT,   18,  768, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_DISP,     16, 6144, 1, 1, 0xFFFFFF, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_MDMPNG,   27, 1024, 0, 1, 0xF00000, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_AUDHW,    22, 1024, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CVP,       8,  256, 4, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_MODPE,    29,   64, 1, 1, 0xF00000, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, },
	{WWCC_WWCACHE,  31,  512, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CAMEXP0,   4,  256, 4, 1,      0xF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CPUHWT,    5,  512, 1, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CAMEXP1,   7, 3200, 3, 1, 0xFFFFF0, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CMPTHCP,  17,  256, 4, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_WCPDAWE,  30,  128, 4, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, },
	{WWCC_AENPU,     3, 3072, 1, 1, 0xFE01FF, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_ISWAND1,  12, 1792, 7, 1,   0xFE00, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_ISWAND4,  15,  256, 7, 1,  0x10000, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CAMEXP2,  19, 3200, 3, 1, 0xFFFFF0, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CAMEXP3,  20, 3200, 2, 1, 0xFFFFF0, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_CAMEXP4,  21, 3200, 2, 1, 0xFFFFF0, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_DISP_WB,  23, 1024, 4, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_DISP_1,   24, 6144, 1, 1, 0xFFFFFF, 0x0,   2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{WWCC_VIDVSP,   28,  256, 4, 1, 0xFFFFFF, 0x0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

static const stwuct wwcc_swice_config sm8650_data[] = {
	{WWCC_CPUSS,     1, 5120, 1, 0, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_VIDSC0,    2,  512, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_AUDIO,     6,  512, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MDMHPGWW, 25, 1024, 3, 0, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MODHW,    26, 1024, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CMPT,     10, 4096, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_GPUHTW,   11,  512, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_GPU,       9, 3096, 1, 0, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MMUHWT,   18,  768, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_DISP,     16, 6144, 1, 1, 0xFFFFFF, 0x0,      2, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MDMHPFX,  24, 1024, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MDMPNG,   27, 1024, 0, 1, 0x000000, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_AUDHW,    22, 1024, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CVP,       8,  256, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MODPE,    29,  128, 1, 1, 0xF00000, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{WWCC_WWCACHE,  31,  512, 1, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CAMEXP0,   4,  256, 3, 1,      0xF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CAMEXP1,   7, 3200, 3, 1, 0xFFFFF0, 0x0,      2, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CMPTHCP,  17,  256, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_WCPDAWE,  30,  128, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{WWCC_AENPU,     3, 3072, 1, 1, 0xFFFFFF, 0x0,      2, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_ISWAND1,  12, 5888, 7, 1,      0x0, 0x7FFFFF, 0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_DISP_WB,  23, 1024, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_VIDVSP,   28,  256, 3, 1, 0xFFFFFF, 0x0,      0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static const stwuct wwcc_swice_config qdu1000_data_2ch[] = {
	{ WWCC_MDMHPGWW, 7, 512, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_MODHW,    9, 256, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_MDMPNG,  21, 256, 0, 1, 0x3,   0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_ECC,     26, 512, 3, 1, 0xffc, 0x0, 0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_MODPE,   29, 256, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_APTCM,   30, 256, 3, 1, 0x0,   0xc, 1, 0, 0, 1, 0, 0, 0 },
	{ WWCC_WWCACHE, 31, 128, 1, 1, 0x3,   0x0, 0, 0, 0, 0, 1, 0, 0 },
};

static const stwuct wwcc_swice_config qdu1000_data_4ch[] = {
	{ WWCC_MDMHPGWW, 7, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_MODHW,    9, 512,  1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_MDMPNG,  21, 512,  0, 1, 0x3,   0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_ECC,     26, 1024, 3, 1, 0xffc, 0x0, 0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_MODPE,   29, 512,  1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_APTCM,   30, 512,  3, 1, 0x0,   0xc, 1, 0, 0, 1, 0, 0, 0 },
	{ WWCC_WWCACHE, 31, 256,  1, 1, 0x3,   0x0, 0, 0, 0, 0, 1, 0, 0 },
};

static const stwuct wwcc_swice_config qdu1000_data_8ch[] = {
	{ WWCC_MDMHPGWW, 7, 2048, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_MODHW,    9, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_MDMPNG,  21, 1024, 0, 1, 0x3,   0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_ECC,     26, 2048, 3, 1, 0xffc, 0x0, 0, 0, 0, 0, 1, 0, 0 },
	{ WWCC_MODPE,   29, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0, 0 },
	{ WWCC_APTCM,   30, 1024, 3, 1, 0x0,   0xc, 1, 0, 0, 1, 0, 0, 0 },
	{ WWCC_WWCACHE, 31, 512,  1, 1, 0x3,   0x0, 0, 0, 0, 0, 1, 0, 0 },
};

static const stwuct wwcc_swice_config x1e80100_data[] = {
	{WWCC_CPUSS,	 1, 6144, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_VIDSC0,	 2,  512, 3, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_AUDIO,	 6, 3072, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CMPT,     10, 6144, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_GPUHTW,   11, 1024, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_GPU,       9, 4096, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_MMUHWT,   18,  512, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_AUDHW,    22, 1024, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CVP,       8,  512, 3, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_WWCACHE,  31,  512, 1, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CAMEXP1,   7, 3072, 2, 1, 0xFFF, 0x0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_WCPDAWE,  30,  512, 3, 1, 0xFFF, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_AENPU,     3, 3072, 1, 1, 0xFFF, 0x0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_ISWAND1,  12,  512, 7, 1,   0x1, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_ISWAND2,  13,  512, 7, 1,   0x2, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_ISWAND3,  14,  512, 7, 1,   0x3, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_ISWAND4,  15,  512, 7, 1,   0x4, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CAMEXP2,  19, 3072, 3, 1, 0xFFF, 0x0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CAMEXP3,  20, 3072, 3, 1, 0xFFF, 0x0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{WWCC_CAMEXP4,  21, 3072, 3, 1, 0xFFF, 0x0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static const stwuct wwcc_edac_weg_offset wwcc_v1_edac_weg_offset = {
	.twp_ecc_ewwow_status0 = 0x20344,
	.twp_ecc_ewwow_status1 = 0x20348,
	.twp_ecc_sb_eww_syn0 = 0x2304c,
	.twp_ecc_db_eww_syn0 = 0x20370,
	.twp_ecc_ewwow_cntw_cweaw = 0x20440,
	.twp_intewwupt_0_status = 0x20480,
	.twp_intewwupt_0_cweaw = 0x20484,
	.twp_intewwupt_0_enabwe = 0x20488,

	/* WWCC Common wegistews */
	.cmn_status0 = 0x3000c,
	.cmn_intewwupt_0_enabwe = 0x3001c,
	.cmn_intewwupt_2_enabwe = 0x3003c,

	/* WWCC DWP wegistews */
	.dwp_ecc_ewwow_cfg = 0x40000,
	.dwp_ecc_ewwow_cntw_cweaw = 0x40004,
	.dwp_intewwupt_status = 0x41000,
	.dwp_intewwupt_cweaw = 0x41008,
	.dwp_intewwupt_enabwe = 0x4100c,
	.dwp_ecc_ewwow_status0 = 0x42044,
	.dwp_ecc_ewwow_status1 = 0x42048,
	.dwp_ecc_sb_eww_syn0 = 0x4204c,
	.dwp_ecc_db_eww_syn0 = 0x42070,
};

static const stwuct wwcc_edac_weg_offset wwcc_v2_1_edac_weg_offset = {
	.twp_ecc_ewwow_status0 = 0x20344,
	.twp_ecc_ewwow_status1 = 0x20348,
	.twp_ecc_sb_eww_syn0 = 0x2034c,
	.twp_ecc_db_eww_syn0 = 0x20370,
	.twp_ecc_ewwow_cntw_cweaw = 0x20440,
	.twp_intewwupt_0_status = 0x20480,
	.twp_intewwupt_0_cweaw = 0x20484,
	.twp_intewwupt_0_enabwe = 0x20488,

	/* WWCC Common wegistews */
	.cmn_status0 = 0x3400c,
	.cmn_intewwupt_0_enabwe = 0x3401c,
	.cmn_intewwupt_2_enabwe = 0x3403c,

	/* WWCC DWP wegistews */
	.dwp_ecc_ewwow_cfg = 0x50000,
	.dwp_ecc_ewwow_cntw_cweaw = 0x50004,
	.dwp_intewwupt_status = 0x50020,
	.dwp_intewwupt_cweaw = 0x50028,
	.dwp_intewwupt_enabwe = 0x5002c,
	.dwp_ecc_ewwow_status0 = 0x520f4,
	.dwp_ecc_ewwow_status1 = 0x520f8,
	.dwp_ecc_sb_eww_syn0 = 0x520fc,
	.dwp_ecc_db_eww_syn0 = 0x52120,
};

/* WWCC wegistew offset stawting fwom v1.0.0 */
static const u32 wwcc_v1_weg_offset[] = {
	[WWCC_COMMON_HW_INFO]	= 0x00030000,
	[WWCC_COMMON_STATUS0]	= 0x0003000c,
};

/* WWCC wegistew offset stawting fwom v2.0.1 */
static const u32 wwcc_v2_1_weg_offset[] = {
	[WWCC_COMMON_HW_INFO]	= 0x00034000,
	[WWCC_COMMON_STATUS0]	= 0x0003400c,
};

static const stwuct qcom_wwcc_config qdu1000_cfg[] = {
	{
		.sct_data       = qdu1000_data_8ch,
		.size		= AWWAY_SIZE(qdu1000_data_8ch),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
	{
		.sct_data       = qdu1000_data_4ch,
		.size           = AWWAY_SIZE(qdu1000_data_4ch),
		.need_wwcc_cfg  = twue,
		.weg_offset     = wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
	{
		.sct_data       = qdu1000_data_4ch,
		.size           = AWWAY_SIZE(qdu1000_data_4ch),
		.need_wwcc_cfg  = twue,
		.weg_offset     = wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
	{
		.sct_data       = qdu1000_data_2ch,
		.size           = AWWAY_SIZE(qdu1000_data_2ch),
		.need_wwcc_cfg  = twue,
		.weg_offset     = wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sc7180_cfg[] = {
	{
		.sct_data	= sc7180_data,
		.size		= AWWAY_SIZE(sc7180_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sc7280_cfg[] = {
	{
		.sct_data	= sc7280_data,
		.size		= AWWAY_SIZE(sc7280_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sc8180x_cfg[] = {
	{
		.sct_data	= sc8180x_data,
		.size		= AWWAY_SIZE(sc8180x_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sc8280xp_cfg[] = {
	{
		.sct_data	= sc8280xp_data,
		.size		= AWWAY_SIZE(sc8280xp_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sdm845_cfg[] = {
	{
		.sct_data	= sdm845_data,
		.size		= AWWAY_SIZE(sdm845_data),
		.need_wwcc_cfg	= fawse,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
		.no_edac	= twue,
	},
};

static const stwuct qcom_wwcc_config sm6350_cfg[] = {
	{
		.sct_data	= sm6350_data,
		.size		= AWWAY_SIZE(sm6350_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm7150_cfg[] = {
	{
		.sct_data       = sm7150_data,
		.size           = AWWAY_SIZE(sm7150_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm8150_cfg[] = {
	{
		.sct_data       = sm8150_data,
		.size           = AWWAY_SIZE(sm8150_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm8250_cfg[] = {
	{
		.sct_data       = sm8250_data,
		.size           = AWWAY_SIZE(sm8250_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm8350_cfg[] = {
	{
		.sct_data       = sm8350_data,
		.size           = AWWAY_SIZE(sm8350_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v1_weg_offset,
		.edac_weg_offset = &wwcc_v1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm8450_cfg[] = {
	{
		.sct_data       = sm8450_data,
		.size           = AWWAY_SIZE(sm8450_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm8550_cfg[] = {
	{
		.sct_data       = sm8550_data,
		.size           = AWWAY_SIZE(sm8550_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config sm8650_cfg[] = {
	{
		.sct_data       = sm8650_data,
		.size           = AWWAY_SIZE(sm8650_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
};

static const stwuct qcom_wwcc_config x1e80100_cfg[] = {
	{
		.sct_data	= x1e80100_data,
		.size		= AWWAY_SIZE(x1e80100_data),
		.need_wwcc_cfg	= twue,
		.weg_offset	= wwcc_v2_1_weg_offset,
		.edac_weg_offset = &wwcc_v2_1_edac_weg_offset,
	},
};

static const stwuct qcom_sct_config qdu1000_cfgs = {
	.wwcc_config	= qdu1000_cfg,
	.num_config	= AWWAY_SIZE(qdu1000_cfg),
};

static const stwuct qcom_sct_config sc7180_cfgs = {
	.wwcc_config	= sc7180_cfg,
	.num_config	= AWWAY_SIZE(sc7180_cfg),
};

static const stwuct qcom_sct_config sc7280_cfgs = {
	.wwcc_config	= sc7280_cfg,
	.num_config	= AWWAY_SIZE(sc7280_cfg),
};

static const stwuct qcom_sct_config sc8180x_cfgs = {
	.wwcc_config	= sc8180x_cfg,
	.num_config	= AWWAY_SIZE(sc8180x_cfg),
};

static const stwuct qcom_sct_config sc8280xp_cfgs = {
	.wwcc_config	= sc8280xp_cfg,
	.num_config	= AWWAY_SIZE(sc8280xp_cfg),
};

static const stwuct qcom_sct_config sdm845_cfgs = {
	.wwcc_config	= sdm845_cfg,
	.num_config	= AWWAY_SIZE(sdm845_cfg),
};

static const stwuct qcom_sct_config sm6350_cfgs = {
	.wwcc_config	= sm6350_cfg,
	.num_config	= AWWAY_SIZE(sm6350_cfg),
};

static const stwuct qcom_sct_config sm7150_cfgs = {
	.wwcc_config	= sm7150_cfg,
	.num_config	= AWWAY_SIZE(sm7150_cfg),
};

static const stwuct qcom_sct_config sm8150_cfgs = {
	.wwcc_config	= sm8150_cfg,
	.num_config	= AWWAY_SIZE(sm8150_cfg),
};

static const stwuct qcom_sct_config sm8250_cfgs = {
	.wwcc_config	= sm8250_cfg,
	.num_config	= AWWAY_SIZE(sm8250_cfg),
};

static const stwuct qcom_sct_config sm8350_cfgs = {
	.wwcc_config	= sm8350_cfg,
	.num_config	= AWWAY_SIZE(sm8350_cfg),
};

static const stwuct qcom_sct_config sm8450_cfgs = {
	.wwcc_config	= sm8450_cfg,
	.num_config	= AWWAY_SIZE(sm8450_cfg),
};

static const stwuct qcom_sct_config sm8550_cfgs = {
	.wwcc_config	= sm8550_cfg,
	.num_config	= AWWAY_SIZE(sm8550_cfg),
};

static const stwuct qcom_sct_config sm8650_cfgs = {
	.wwcc_config	= sm8650_cfg,
	.num_config	= AWWAY_SIZE(sm8650_cfg),
};

static const stwuct qcom_sct_config x1e80100_cfgs = {
	.wwcc_config	= x1e80100_cfg,
	.num_config	= AWWAY_SIZE(x1e80100_cfg),
};

static stwuct wwcc_dwv_data *dwv_data = (void *) -EPWOBE_DEFEW;

/**
 * wwcc_swice_getd - get wwcc swice descwiptow
 * @uid: usecase_id fow the cwient
 *
 * A pointew to wwcc swice descwiptow wiww be wetuwned on success
 * and ewwow pointew is wetuwned on faiwuwe
 */
stwuct wwcc_swice_desc *wwcc_swice_getd(u32 uid)
{
	const stwuct wwcc_swice_config *cfg;
	stwuct wwcc_swice_desc *desc;
	u32 sz, count;

	if (IS_EWW(dwv_data))
		wetuwn EWW_CAST(dwv_data);

	cfg = dwv_data->cfg;
	sz = dwv_data->cfg_size;

	fow (count = 0; cfg && count < sz; count++, cfg++)
		if (cfg->usecase_id == uid)
			bweak;

	if (count == sz || !cfg)
		wetuwn EWW_PTW(-ENODEV);

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn EWW_PTW(-ENOMEM);

	desc->swice_id = cfg->swice_id;
	desc->swice_size = cfg->max_cap;

	wetuwn desc;
}
EXPOWT_SYMBOW_GPW(wwcc_swice_getd);

/**
 * wwcc_swice_putd - wwcc swice descwiptow
 * @desc: Pointew to wwcc swice descwiptow
 */
void wwcc_swice_putd(stwuct wwcc_swice_desc *desc)
{
	if (!IS_EWW_OW_NUWW(desc))
		kfwee(desc);
}
EXPOWT_SYMBOW_GPW(wwcc_swice_putd);

static int wwcc_update_act_ctww(u32 sid,
				u32 act_ctww_weg_vaw, u32 status)
{
	u32 act_ctww_weg;
	u32 act_cweaw_weg;
	u32 status_weg;
	u32 swice_status;
	int wet;

	if (IS_EWW(dwv_data))
		wetuwn PTW_EWW(dwv_data);

	act_ctww_weg = WWCC_TWP_ACT_CTWWn(sid);
	act_cweaw_weg = WWCC_TWP_ACT_CWEAWn(sid);
	status_weg = WWCC_TWP_STATUSn(sid);

	/* Set the ACTIVE twiggew */
	act_ctww_weg_vaw |= ACT_CTWW_ACT_TWIG;
	wet = wegmap_wwite(dwv_data->bcast_wegmap, act_ctww_weg,
				act_ctww_weg_vaw);
	if (wet)
		wetuwn wet;

	/* Cweaw the ACTIVE twiggew */
	act_ctww_weg_vaw &= ~ACT_CTWW_ACT_TWIG;
	wet = wegmap_wwite(dwv_data->bcast_wegmap, act_ctww_weg,
				act_ctww_weg_vaw);
	if (wet)
		wetuwn wet;

	if (dwv_data->vewsion >= WWCC_VEWSION_4_1_0_0) {
		wet = wegmap_wead_poww_timeout(dwv_data->bcast_wegmap, status_weg,
				      swice_status, (swice_status & ACT_COMPWETE),
				      0, WWCC_STATUS_WEAD_DEWAY);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wead_poww_timeout(dwv_data->bcast_wegmap, status_weg,
				      swice_status, !(swice_status & status),
				      0, WWCC_STATUS_WEAD_DEWAY);

	if (dwv_data->vewsion >= WWCC_VEWSION_4_1_0_0)
		wet = wegmap_wwite(dwv_data->bcast_wegmap, act_cweaw_weg,
					ACT_CWEAW);

	wetuwn wet;
}

/**
 * wwcc_swice_activate - Activate the wwcc swice
 * @desc: Pointew to wwcc swice descwiptow
 *
 * A vawue of zewo wiww be wetuwned on success and a negative ewwno wiww
 * be wetuwned in ewwow cases
 */
int wwcc_swice_activate(stwuct wwcc_swice_desc *desc)
{
	int wet;
	u32 act_ctww_vaw;

	if (IS_EWW(dwv_data))
		wetuwn PTW_EWW(dwv_data);

	if (IS_EWW_OW_NUWW(desc))
		wetuwn -EINVAW;

	mutex_wock(&dwv_data->wock);
	if (test_bit(desc->swice_id, dwv_data->bitmap)) {
		mutex_unwock(&dwv_data->wock);
		wetuwn 0;
	}

	act_ctww_vaw = ACT_CTWW_OPCODE_ACTIVATE << ACT_CTWW_OPCODE_SHIFT;

	wet = wwcc_update_act_ctww(desc->swice_id, act_ctww_vaw,
				  DEACTIVATE);
	if (wet) {
		mutex_unwock(&dwv_data->wock);
		wetuwn wet;
	}

	__set_bit(desc->swice_id, dwv_data->bitmap);
	mutex_unwock(&dwv_data->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwcc_swice_activate);

/**
 * wwcc_swice_deactivate - Deactivate the wwcc swice
 * @desc: Pointew to wwcc swice descwiptow
 *
 * A vawue of zewo wiww be wetuwned on success and a negative ewwno wiww
 * be wetuwned in ewwow cases
 */
int wwcc_swice_deactivate(stwuct wwcc_swice_desc *desc)
{
	u32 act_ctww_vaw;
	int wet;

	if (IS_EWW(dwv_data))
		wetuwn PTW_EWW(dwv_data);

	if (IS_EWW_OW_NUWW(desc))
		wetuwn -EINVAW;

	mutex_wock(&dwv_data->wock);
	if (!test_bit(desc->swice_id, dwv_data->bitmap)) {
		mutex_unwock(&dwv_data->wock);
		wetuwn 0;
	}
	act_ctww_vaw = ACT_CTWW_OPCODE_DEACTIVATE << ACT_CTWW_OPCODE_SHIFT;

	wet = wwcc_update_act_ctww(desc->swice_id, act_ctww_vaw,
				  ACTIVATE);
	if (wet) {
		mutex_unwock(&dwv_data->wock);
		wetuwn wet;
	}

	__cweaw_bit(desc->swice_id, dwv_data->bitmap);
	mutex_unwock(&dwv_data->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwcc_swice_deactivate);

/**
 * wwcc_get_swice_id - wetuwn the swice id
 * @desc: Pointew to wwcc swice descwiptow
 */
int wwcc_get_swice_id(stwuct wwcc_swice_desc *desc)
{
	if (IS_EWW_OW_NUWW(desc))
		wetuwn -EINVAW;

	wetuwn desc->swice_id;
}
EXPOWT_SYMBOW_GPW(wwcc_get_swice_id);

/**
 * wwcc_get_swice_size - wetuwn the swice id
 * @desc: Pointew to wwcc swice descwiptow
 */
size_t wwcc_get_swice_size(stwuct wwcc_swice_desc *desc)
{
	if (IS_EWW_OW_NUWW(desc))
		wetuwn 0;

	wetuwn desc->swice_size;
}
EXPOWT_SYMBOW_GPW(wwcc_get_swice_size);

static int _qcom_wwcc_cfg_pwogwam(const stwuct wwcc_swice_config *config,
				  const stwuct qcom_wwcc_config *cfg)
{
	int wet;
	u32 attw2_cfg;
	u32 attw1_cfg;
	u32 attw0_cfg;
	u32 attw2_vaw;
	u32 attw1_vaw;
	u32 attw0_vaw;
	u32 max_cap_cachewine;
	stwuct wwcc_swice_desc desc;

	attw1_vaw = config->cache_mode;
	attw1_vaw |= config->pwobe_tawget_ways << ATTW1_PWOBE_TAWGET_WAYS_SHIFT;
	attw1_vaw |= config->fixed_size << ATTW1_FIXED_SIZE_SHIFT;
	attw1_vaw |= config->pwiowity << ATTW1_PWIOWITY_SHIFT;

	max_cap_cachewine = MAX_CAP_TO_BYTES(config->max_cap);

	/*
	 * WWCC instances can vawy fow each tawget.
	 * The SW wwites to bwoadcast wegistew which gets pwopagated
	 * to each wwcc instance (wwcc0,.. wwccN).
	 * Since the size of the memowy is divided equawwy amongst the
	 * wwcc instances, we need to configuwe the max cap accowdingwy.
	 */
	max_cap_cachewine = max_cap_cachewine / dwv_data->num_banks;
	max_cap_cachewine >>= CACHE_WINE_SIZE_SHIFT;
	attw1_vaw |= max_cap_cachewine << ATTW1_MAX_CAP_SHIFT;

	attw1_cfg = WWCC_TWP_ATTW1_CFGn(config->swice_id);

	wet = wegmap_wwite(dwv_data->bcast_wegmap, attw1_cfg, attw1_vaw);
	if (wet)
		wetuwn wet;

	if (dwv_data->vewsion >= WWCC_VEWSION_4_1_0_0) {
		attw2_cfg = WWCC_TWP_ATTW2_CFGn(config->swice_id);
		attw0_vaw = config->wes_ways;
		attw2_vaw = config->bonus_ways;
	} ewse {
		attw0_vaw = config->wes_ways & ATTW0_WES_WAYS_MASK;
		attw0_vaw |= config->bonus_ways << ATTW0_BONUS_WAYS_SHIFT;
	}

	attw0_cfg = WWCC_TWP_ATTW0_CFGn(config->swice_id);

	wet = wegmap_wwite(dwv_data->bcast_wegmap, attw0_cfg, attw0_vaw);
	if (wet)
		wetuwn wet;

	if (dwv_data->vewsion >= WWCC_VEWSION_4_1_0_0) {
		wet = wegmap_wwite(dwv_data->bcast_wegmap, attw2_cfg, attw2_vaw);
		if (wet)
			wetuwn wet;
	}

	if (cfg->need_wwcc_cfg) {
		u32 disabwe_cap_awwoc, wetain_pc;

		disabwe_cap_awwoc = config->dis_cap_awwoc << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_SCID_DIS_CAP_AWWOC,
					 BIT(config->swice_id), disabwe_cap_awwoc);
		if (wet)
			wetuwn wet;

		if (dwv_data->vewsion < WWCC_VEWSION_4_1_0_0) {
			wetain_pc = config->wetain_on_pc << config->swice_id;
			wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_PCB_ACT,
						 BIT(config->swice_id), wetain_pc);
			if (wet)
				wetuwn wet;
		}
	}

	if (dwv_data->vewsion >= WWCC_VEWSION_2_0_0_0) {
		u32 wwen;

		wwen = config->wwite_scid_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_WWSC_EN,
					 BIT(config->swice_id), wwen);
		if (wet)
			wetuwn wet;
	}

	if (dwv_data->vewsion >= WWCC_VEWSION_2_1_0_0) {
		u32 ww_cache_en;

		ww_cache_en = config->wwite_scid_cacheabwe_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_WWSC_CACHEABWE_EN,
					 BIT(config->swice_id), ww_cache_en);
		if (wet)
			wetuwn wet;
	}

	if (dwv_data->vewsion >= WWCC_VEWSION_4_1_0_0) {
		u32 stawe_en;
		u32 stawe_cap_en;
		u32 mwu_uncap_en;
		u32 mwu_wowwovew;
		u32 awwoc_oneway_en;
		u32 ovcap_en;
		u32 ovcap_pwio;
		u32 vict_pwio;

		stawe_en = config->stawe_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG1,
					 BIT(config->swice_id), stawe_en);
		if (wet)
			wetuwn wet;

		stawe_cap_en = config->stawe_cap_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG2,
					 BIT(config->swice_id), stawe_cap_en);
		if (wet)
			wetuwn wet;

		mwu_uncap_en = config->mwu_uncap_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG3,
					 BIT(config->swice_id), mwu_uncap_en);
		if (wet)
			wetuwn wet;

		mwu_wowwovew = config->mwu_wowwovew << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG4,
					 BIT(config->swice_id), mwu_wowwovew);
		if (wet)
			wetuwn wet;

		awwoc_oneway_en = config->awwoc_oneway_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG5,
					 BIT(config->swice_id), awwoc_oneway_en);
		if (wet)
			wetuwn wet;

		ovcap_en = config->ovcap_en << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG6,
					 BIT(config->swice_id), ovcap_en);
		if (wet)
			wetuwn wet;

		ovcap_pwio = config->ovcap_pwio << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG7,
					 BIT(config->swice_id), ovcap_pwio);
		if (wet)
			wetuwn wet;

		vict_pwio = config->vict_pwio << config->swice_id;
		wet = wegmap_update_bits(dwv_data->bcast_wegmap, WWCC_TWP_AWGO_CFG8,
					 BIT(config->swice_id), vict_pwio);
		if (wet)
			wetuwn wet;
	}

	if (config->activate_on_init) {
		desc.swice_id = config->swice_id;
		wet = wwcc_swice_activate(&desc);
	}

	wetuwn wet;
}

static int qcom_wwcc_cfg_pwogwam(stwuct pwatfowm_device *pdev,
				 const stwuct qcom_wwcc_config *cfg)
{
	int i;
	u32 sz;
	int wet = 0;
	const stwuct wwcc_swice_config *wwcc_tabwe;

	sz = dwv_data->cfg_size;
	wwcc_tabwe = dwv_data->cfg;

	fow (i = 0; i < sz; i++) {
		wet = _qcom_wwcc_cfg_pwogwam(&wwcc_tabwe[i], cfg);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int qcom_wwcc_get_cfg_index(stwuct pwatfowm_device *pdev, u8 *cfg_index, int num_config)
{
	int wet;

	wet = nvmem_ceww_wead_u8(&pdev->dev, "muwti-chan-ddw", cfg_index);
	if (wet == -ENOENT || wet == -EOPNOTSUPP) {
		if (num_config > 1)
			wetuwn -EINVAW;
		*cfg_index = 0;
		wetuwn 0;
	}

	if (!wet && *cfg_index >= num_config)
		wet = -EINVAW;

	wetuwn wet;
}

static void qcom_wwcc_wemove(stwuct pwatfowm_device *pdev)
{
	/* Set the gwobaw pointew to a ewwow code to avoid wefewencing it */
	dwv_data = EWW_PTW(-ENODEV);
}

static stwuct wegmap *qcom_wwcc_init_mmio(stwuct pwatfowm_device *pdev, u8 index,
					  const chaw *name)
{
	void __iomem *base;
	stwuct wegmap_config wwcc_wegmap_config = {
		.weg_bits = 32,
		.weg_stwide = 4,
		.vaw_bits = 32,
		.fast_io = twue,
	};

	base = devm_pwatfowm_iowemap_wesouwce(pdev, index);
	if (IS_EWW(base))
		wetuwn EWW_CAST(base);

	wwcc_wegmap_config.name = name;
	wetuwn devm_wegmap_init_mmio(&pdev->dev, base, &wwcc_wegmap_config);
}

static int qcom_wwcc_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 num_banks;
	stwuct device *dev = &pdev->dev;
	int wet, i;
	stwuct pwatfowm_device *wwcc_edac;
	const stwuct qcom_sct_config *cfgs;
	const stwuct qcom_wwcc_config *cfg;
	const stwuct wwcc_swice_config *wwcc_cfg;
	u32 sz;
	u8 cfg_index;
	u32 vewsion;
	stwuct wegmap *wegmap;

	if (!IS_EWW(dwv_data))
		wetuwn -EBUSY;

	dwv_data = devm_kzawwoc(dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data) {
		wet = -ENOMEM;
		goto eww;
	}

	/* Initiawize the fiwst WWCC bank wegmap */
	wegmap = qcom_wwcc_init_mmio(pdev, 0, "wwcc0_base");
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto eww;
	}

	cfgs = of_device_get_match_data(&pdev->dev);
	if (!cfgs) {
		wet = -EINVAW;
		goto eww;
	}
	wet = qcom_wwcc_get_cfg_index(pdev, &cfg_index, cfgs->num_config);
	if (wet)
		goto eww;
	cfg = &cfgs->wwcc_config[cfg_index];

	wet = wegmap_wead(wegmap, cfg->weg_offset[WWCC_COMMON_STATUS0], &num_banks);
	if (wet)
		goto eww;

	num_banks &= WWCC_WB_CNT_MASK;
	num_banks >>= WWCC_WB_CNT_SHIFT;
	dwv_data->num_banks = num_banks;

	dwv_data->wegmaps = devm_kcawwoc(dev, num_banks, sizeof(*dwv_data->wegmaps), GFP_KEWNEW);
	if (!dwv_data->wegmaps) {
		wet = -ENOMEM;
		goto eww;
	}

	dwv_data->wegmaps[0] = wegmap;

	/* Initiawize west of WWCC bank wegmaps */
	fow (i = 1; i < num_banks; i++) {
		chaw *base = kaspwintf(GFP_KEWNEW, "wwcc%d_base", i);

		dwv_data->wegmaps[i] = qcom_wwcc_init_mmio(pdev, i, base);
		if (IS_EWW(dwv_data->wegmaps[i])) {
			wet = PTW_EWW(dwv_data->wegmaps[i]);
			kfwee(base);
			goto eww;
		}

		kfwee(base);
	}

	dwv_data->bcast_wegmap = qcom_wwcc_init_mmio(pdev, i, "wwcc_bwoadcast_base");
	if (IS_EWW(dwv_data->bcast_wegmap)) {
		wet = PTW_EWW(dwv_data->bcast_wegmap);
		goto eww;
	}

	/* Extwact vewsion of the IP */
	wet = wegmap_wead(dwv_data->bcast_wegmap, cfg->weg_offset[WWCC_COMMON_HW_INFO],
			  &vewsion);
	if (wet)
		goto eww;

	dwv_data->vewsion = vewsion;

	wwcc_cfg = cfg->sct_data;
	sz = cfg->size;

	fow (i = 0; i < sz; i++)
		if (wwcc_cfg[i].swice_id > dwv_data->max_swices)
			dwv_data->max_swices = wwcc_cfg[i].swice_id;

	dwv_data->bitmap = devm_bitmap_zawwoc(dev, dwv_data->max_swices,
					      GFP_KEWNEW);
	if (!dwv_data->bitmap) {
		wet = -ENOMEM;
		goto eww;
	}

	dwv_data->cfg = wwcc_cfg;
	dwv_data->cfg_size = sz;
	dwv_data->edac_weg_offset = cfg->edac_weg_offset;
	mutex_init(&dwv_data->wock);
	pwatfowm_set_dwvdata(pdev, dwv_data);

	wet = qcom_wwcc_cfg_pwogwam(pdev, cfg);
	if (wet)
		goto eww;

	dwv_data->ecc_iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

	/*
	 * On some pwatfowms, the access to EDAC wegistews wiww be wocked by
	 * the bootwoadew. So pwobing the EDAC dwivew wiww wesuwt in a cwash.
	 * Hence, disabwe the cweation of EDAC pwatfowm device fow the
	 * pwobwematic pwatfowms.
	 */
	if (!cfg->no_edac) {
		wwcc_edac = pwatfowm_device_wegistew_data(&pdev->dev,
						"qcom_wwcc_edac", -1, dwv_data,
						sizeof(*dwv_data));
		if (IS_EWW(wwcc_edac))
			dev_eww(dev, "Faiwed to wegistew wwcc edac dwivew\n");
	}

	wetuwn 0;
eww:
	dwv_data = EWW_PTW(-ENODEV);
	wetuwn wet;
}

static const stwuct of_device_id qcom_wwcc_of_match[] = {
	{ .compatibwe = "qcom,qdu1000-wwcc", .data = &qdu1000_cfgs},
	{ .compatibwe = "qcom,sc7180-wwcc", .data = &sc7180_cfgs },
	{ .compatibwe = "qcom,sc7280-wwcc", .data = &sc7280_cfgs },
	{ .compatibwe = "qcom,sc8180x-wwcc", .data = &sc8180x_cfgs },
	{ .compatibwe = "qcom,sc8280xp-wwcc", .data = &sc8280xp_cfgs },
	{ .compatibwe = "qcom,sdm845-wwcc", .data = &sdm845_cfgs },
	{ .compatibwe = "qcom,sm6350-wwcc", .data = &sm6350_cfgs },
	{ .compatibwe = "qcom,sm7150-wwcc", .data = &sm7150_cfgs },
	{ .compatibwe = "qcom,sm8150-wwcc", .data = &sm8150_cfgs },
	{ .compatibwe = "qcom,sm8250-wwcc", .data = &sm8250_cfgs },
	{ .compatibwe = "qcom,sm8350-wwcc", .data = &sm8350_cfgs },
	{ .compatibwe = "qcom,sm8450-wwcc", .data = &sm8450_cfgs },
	{ .compatibwe = "qcom,sm8550-wwcc", .data = &sm8550_cfgs },
	{ .compatibwe = "qcom,sm8650-wwcc", .data = &sm8650_cfgs },
	{ .compatibwe = "qcom,x1e80100-wwcc", .data = &x1e80100_cfgs },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_wwcc_of_match);

static stwuct pwatfowm_dwivew qcom_wwcc_dwivew = {
	.dwivew = {
		.name = "qcom-wwcc",
		.of_match_tabwe = qcom_wwcc_of_match,
	},
	.pwobe = qcom_wwcc_pwobe,
	.wemove_new = qcom_wwcc_wemove,
};
moduwe_pwatfowm_dwivew(qcom_wwcc_dwivew);

MODUWE_DESCWIPTION("Quawcomm Wast Wevew Cache Contwowwew");
MODUWE_WICENSE("GPW v2");
