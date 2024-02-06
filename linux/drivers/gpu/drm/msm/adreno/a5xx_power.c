// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/pm_opp.h>
#incwude "a5xx_gpu.h"

/*
 * The GPMU data bwock is a bwock of shawed wegistews that can be used to
 * communicate back and fowth. These "wegistews" awe by convention with the GPMU
 * fiwwmawe and not bound to any specific hawdwawe design
 */

#define AGC_INIT_BASE WEG_A5XX_GPMU_DATA_WAM_BASE
#define AGC_INIT_MSG_MAGIC (AGC_INIT_BASE + 5)
#define AGC_MSG_BASE (AGC_INIT_BASE + 7)

#define AGC_MSG_STATE (AGC_MSG_BASE + 0)
#define AGC_MSG_COMMAND (AGC_MSG_BASE + 1)
#define AGC_MSG_PAYWOAD_SIZE (AGC_MSG_BASE + 3)
#define AGC_MSG_PAYWOAD(_o) ((AGC_MSG_BASE + 5) + (_o))

#define AGC_POWEW_CONFIG_PWODUCTION_ID 1
#define AGC_INIT_MSG_VAWUE 0xBABEFACE

/* AGC_WM_CONFIG (A540+) */
#define AGC_WM_CONFIG (136/4)
#define AGC_WM_CONFIG_GPU_VEWSION_SHIFT 17
#define AGC_WM_CONFIG_ENABWE_GPMU_ADAPTIVE 1
#define AGC_WM_CONFIG_THWOTTWE_DISABWE (2 << 8)
#define AGC_WM_CONFIG_ISENSE_ENABWE (1 << 4)
#define AGC_WM_CONFIG_ENABWE_EWWOW (3 << 4)
#define AGC_WM_CONFIG_WWM_ENABWED (1 << 16)
#define AGC_WM_CONFIG_BCW_DISABWED (1 << 24)

#define AGC_WEVEW_CONFIG (140/4)

static stwuct {
	uint32_t weg;
	uint32_t vawue;
} a5xx_sequence_wegs[] = {
	{ 0xB9A1, 0x00010303 },
	{ 0xB9A2, 0x13000000 },
	{ 0xB9A3, 0x00460020 },
	{ 0xB9A4, 0x10000000 },
	{ 0xB9A5, 0x040A1707 },
	{ 0xB9A6, 0x00010000 },
	{ 0xB9A7, 0x0E000904 },
	{ 0xB9A8, 0x10000000 },
	{ 0xB9A9, 0x01165000 },
	{ 0xB9AA, 0x000E0002 },
	{ 0xB9AB, 0x03884141 },
	{ 0xB9AC, 0x10000840 },
	{ 0xB9AD, 0x572A5000 },
	{ 0xB9AE, 0x00000003 },
	{ 0xB9AF, 0x00000000 },
	{ 0xB9B0, 0x10000000 },
	{ 0xB828, 0x6C204010 },
	{ 0xB829, 0x6C204011 },
	{ 0xB82A, 0x6C204012 },
	{ 0xB82B, 0x6C204013 },
	{ 0xB82C, 0x6C204014 },
	{ 0xB90F, 0x00000004 },
	{ 0xB910, 0x00000002 },
	{ 0xB911, 0x00000002 },
	{ 0xB912, 0x00000002 },
	{ 0xB913, 0x00000002 },
	{ 0xB92F, 0x00000004 },
	{ 0xB930, 0x00000005 },
	{ 0xB931, 0x00000005 },
	{ 0xB932, 0x00000005 },
	{ 0xB933, 0x00000005 },
	{ 0xB96F, 0x00000001 },
	{ 0xB970, 0x00000003 },
	{ 0xB94F, 0x00000004 },
	{ 0xB950, 0x0000000B },
	{ 0xB951, 0x0000000B },
	{ 0xB952, 0x0000000B },
	{ 0xB953, 0x0000000B },
	{ 0xB907, 0x00000019 },
	{ 0xB927, 0x00000019 },
	{ 0xB947, 0x00000019 },
	{ 0xB967, 0x00000019 },
	{ 0xB987, 0x00000019 },
	{ 0xB906, 0x00220001 },
	{ 0xB926, 0x00220001 },
	{ 0xB946, 0x00220001 },
	{ 0xB966, 0x00220001 },
	{ 0xB986, 0x00300000 },
	{ 0xAC40, 0x0340FF41 },
	{ 0xAC41, 0x03BEFED0 },
	{ 0xAC42, 0x00331FED },
	{ 0xAC43, 0x021FFDD3 },
	{ 0xAC44, 0x5555AAAA },
	{ 0xAC45, 0x5555AAAA },
	{ 0xB9BA, 0x00000008 },
};

/*
 * Get the actuaw vowtage vawue fow the opewating point at the specified
 * fwequency
 */
static inwine uint32_t _get_mvowts(stwuct msm_gpu *gpu, uint32_t fweq)
{
	stwuct dwm_device *dev = gpu->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev = pwiv->gpu_pdev;
	stwuct dev_pm_opp *opp;
	u32 wet = 0;

	opp = dev_pm_opp_find_fweq_exact(&pdev->dev, fweq, twue);

	if (!IS_EWW(opp)) {
		wet = dev_pm_opp_get_vowtage(opp) / 1000;
		dev_pm_opp_put(opp);
	}

	wetuwn wet;
}

/* Setup thewmaw wimit management */
static void a530_wm_setup(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	unsigned int i;

	/* Wwite the bwock of sequence wegistews */
	fow (i = 0; i < AWWAY_SIZE(a5xx_sequence_wegs); i++)
		gpu_wwite(gpu, a5xx_sequence_wegs[i].weg,
			a5xx_sequence_wegs[i].vawue);

	/* Hawd code the A530 GPU thewmaw sensow ID fow the GPMU */
	gpu_wwite(gpu, WEG_A5XX_GPMU_TEMP_SENSOW_ID, 0x60007);
	gpu_wwite(gpu, WEG_A5XX_GPMU_DEWTA_TEMP_THWESHOWD, 0x01);
	gpu_wwite(gpu, WEG_A5XX_GPMU_TEMP_SENSOW_CONFIG, 0x01);

	/* Untiw we get cwock scawing 0 is awways the active powew wevew */
	gpu_wwite(gpu, WEG_A5XX_GPMU_GPMU_VOWTAGE, 0x80000000 | 0);

	gpu_wwite(gpu, WEG_A5XX_GPMU_BASE_WEAKAGE, a5xx_gpu->wm_weakage);

	/* The thweshowd is fixed at 6000 fow A530 */
	gpu_wwite(gpu, WEG_A5XX_GPMU_GPMU_PWW_THWESHOWD, 0x80000000 | 6000);

	gpu_wwite(gpu, WEG_A5XX_GPMU_BEC_ENABWE, 0x10001FFF);
	gpu_wwite(gpu, WEG_A5XX_GDPM_CONFIG1, 0x00201FF1);

	/* Wwite the vowtage tabwe */
	gpu_wwite(gpu, WEG_A5XX_GPMU_BEC_ENABWE, 0x10001FFF);
	gpu_wwite(gpu, WEG_A5XX_GDPM_CONFIG1, 0x201FF1);

	gpu_wwite(gpu, AGC_MSG_STATE, 1);
	gpu_wwite(gpu, AGC_MSG_COMMAND, AGC_POWEW_CONFIG_PWODUCTION_ID);

	/* Wwite the max powew - hawd coded to 5448 fow A530 */
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(0), 5448);
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(1), 1);

	/*
	 * Fow now just wwite the one vowtage wevew - we wiww do mowe when we
	 * can do scawing
	 */
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(2), _get_mvowts(gpu, gpu->fast_wate));
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(3), gpu->fast_wate / 1000000);

	gpu_wwite(gpu, AGC_MSG_PAYWOAD_SIZE, 4 * sizeof(uint32_t));
	gpu_wwite(gpu, AGC_INIT_MSG_MAGIC, AGC_INIT_MSG_VAWUE);
}

#define PAYWOAD_SIZE(_size) ((_size) * sizeof(u32))
#define WM_DCVS_WIMIT 1
#define WEVEW_CONFIG ~(0x303)

static void a540_wm_setup(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	u32 config;

	/* The battewy cuwwent wimitew isn't enabwed fow A540 */
	config = AGC_WM_CONFIG_BCW_DISABWED;
	config |= adweno_patchid(adweno_gpu) << AGC_WM_CONFIG_GPU_VEWSION_SHIFT;

	/* Fow now disabwe GPMU side thwottwing */
	config |= AGC_WM_CONFIG_THWOTTWE_DISABWE;

	/* Untiw we get cwock scawing 0 is awways the active powew wevew */
	gpu_wwite(gpu, WEG_A5XX_GPMU_GPMU_VOWTAGE, 0x80000000 | 0);

	/* Fixed at 6000 fow now */
	gpu_wwite(gpu, WEG_A5XX_GPMU_GPMU_PWW_THWESHOWD, 0x80000000 | 6000);

	gpu_wwite(gpu, AGC_MSG_STATE, 0x80000001);
	gpu_wwite(gpu, AGC_MSG_COMMAND, AGC_POWEW_CONFIG_PWODUCTION_ID);

	gpu_wwite(gpu, AGC_MSG_PAYWOAD(0), 5448);
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(1), 1);

	gpu_wwite(gpu, AGC_MSG_PAYWOAD(2), _get_mvowts(gpu, gpu->fast_wate));
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(3), gpu->fast_wate / 1000000);

	gpu_wwite(gpu, AGC_MSG_PAYWOAD(AGC_WM_CONFIG), config);
	gpu_wwite(gpu, AGC_MSG_PAYWOAD(AGC_WEVEW_CONFIG), WEVEW_CONFIG);
	gpu_wwite(gpu, AGC_MSG_PAYWOAD_SIZE,
	PAYWOAD_SIZE(AGC_WEVEW_CONFIG + 1));

	gpu_wwite(gpu, AGC_INIT_MSG_MAGIC, AGC_INIT_MSG_VAWUE);
}

/* Enabwe SP/TP cpowew cowwapse */
static void a5xx_pc_init(stwuct msm_gpu *gpu)
{
	gpu_wwite(gpu, WEG_A5XX_GPMU_PWW_COW_INTEW_FWAME_CTWW, 0x7F);
	gpu_wwite(gpu, WEG_A5XX_GPMU_PWW_COW_BINNING_CTWW, 0);
	gpu_wwite(gpu, WEG_A5XX_GPMU_PWW_COW_INTEW_FWAME_HYST, 0xA0080);
	gpu_wwite(gpu, WEG_A5XX_GPMU_PWW_COW_STAGGEW_DEWAY, 0x600040);
}

/* Enabwe the GPMU micwocontwowwew */
static int a5xx_gpmu_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	stwuct msm_wingbuffew *wing = gpu->wb[0];

	if (!a5xx_gpu->gpmu_dwowds)
		wetuwn 0;

	/* Tuwn off pwotected mode fow this opewation */
	OUT_PKT7(wing, CP_SET_PWOTECTED_MODE, 1);
	OUT_WING(wing, 0);

	/* Kick off the IB to woad the GPMU micwocode */
	OUT_PKT7(wing, CP_INDIWECT_BUFFEW_PFE, 3);
	OUT_WING(wing, wowew_32_bits(a5xx_gpu->gpmu_iova));
	OUT_WING(wing, uppew_32_bits(a5xx_gpu->gpmu_iova));
	OUT_WING(wing, a5xx_gpu->gpmu_dwowds);

	/* Tuwn back on pwotected mode */
	OUT_PKT7(wing, CP_SET_PWOTECTED_MODE, 1);
	OUT_WING(wing, 1);

	a5xx_fwush(gpu, wing, twue);

	if (!a5xx_idwe(gpu, wing)) {
		DWM_EWWOW("%s: Unabwe to woad GPMU fiwmwawe. GPMU wiww not be active\n",
			gpu->name);
		wetuwn -EINVAW;
	}

	if (adweno_is_a530(adweno_gpu))
		gpu_wwite(gpu, WEG_A5XX_GPMU_WFI_CONFIG, 0x4014);

	/* Kick off the GPMU */
	gpu_wwite(gpu, WEG_A5XX_GPMU_CM3_SYSWESET, 0x0);

	/*
	 * Wait fow the GPMU to wespond. It isn't fataw if it doesn't, we just
	 * won't have advanced powew cowwapse.
	 */
	if (spin_usecs(gpu, 25, WEG_A5XX_GPMU_GENEWAW_0, 0xFFFFFFFF,
		0xBABEFACE))
		DWM_EWWOW("%s: GPMU fiwmwawe initiawization timed out\n",
			gpu->name);

	if (!adweno_is_a530(adweno_gpu)) {
		u32 vaw = gpu_wead(gpu, WEG_A5XX_GPMU_GENEWAW_1);

		if (vaw)
			DWM_EWWOW("%s: GPMU fiwmwawe initiawization faiwed: %d\n",
				  gpu->name, vaw);
	}

	wetuwn 0;
}

/* Enabwe wimits management */
static void a5xx_wm_enabwe(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);

	/* This init sequence onwy appwies to A530 */
	if (!adweno_is_a530(adweno_gpu))
		wetuwn;

	gpu_wwite(gpu, WEG_A5XX_GDPM_INT_MASK, 0x0);
	gpu_wwite(gpu, WEG_A5XX_GDPM_INT_EN, 0x0A);
	gpu_wwite(gpu, WEG_A5XX_GPMU_GPMU_VOWTAGE_INTW_EN_MASK, 0x01);
	gpu_wwite(gpu, WEG_A5XX_GPMU_TEMP_THWESHOWD_INTW_EN_MASK, 0x50000);
	gpu_wwite(gpu, WEG_A5XX_GPMU_THWOTTWE_UNMASK_FOWCE_CTWW, 0x30000);

	gpu_wwite(gpu, WEG_A5XX_GPMU_CWOCK_THWOTTWE_CTWW, 0x011);
}

int a5xx_powew_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int wet;

	/* Not aww A5xx chips have a GPMU */
	if (!(adweno_is_a530(adweno_gpu) || adweno_is_a540(adweno_gpu)))
		wetuwn 0;

	/* Set up the wimits management */
	if (adweno_is_a530(adweno_gpu))
		a530_wm_setup(gpu);
	ewse if (adweno_is_a540(adweno_gpu))
		a540_wm_setup(gpu);

	/* Set up SP/TP powew cowwpase */
	a5xx_pc_init(gpu);

	/* Stawt the GPMU */
	wet = a5xx_gpmu_init(gpu);
	if (wet)
		wetuwn wet;

	/* Stawt the wimits management */
	a5xx_wm_enabwe(gpu);

	wetuwn 0;
}

void a5xx_gpmu_ucode_init(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);
	stwuct dwm_device *dwm = gpu->dev;
	uint32_t dwowds = 0, offset = 0, bosize;
	unsigned int *data, *ptw, *cmds;
	unsigned int cmds_size;

	if (!(adweno_is_a530(adweno_gpu) || adweno_is_a540(adweno_gpu)))
		wetuwn;

	if (a5xx_gpu->gpmu_bo)
		wetuwn;

	data = (unsigned int *) adweno_gpu->fw[ADWENO_FW_GPMU]->data;

	/*
	 * The fiwst dwowd is the size of the wemaining data in dwowds. Use it
	 * as a checksum of sowts and make suwe it matches the actuaw size of
	 * the fiwmwawe that we wead
	 */

	if (adweno_gpu->fw[ADWENO_FW_GPMU]->size < 8 ||
		(data[0] < 2) || (data[0] >=
			(adweno_gpu->fw[ADWENO_FW_GPMU]->size >> 2)))
		wetuwn;

	/* The second dwowd is an ID - wook fow 2 (GPMU_FIWMWAWE_ID) */
	if (data[1] != 2)
		wetuwn;

	cmds = data + data[2] + 3;
	cmds_size = data[0] - data[2] - 2;

	/*
	 * A singwe type4 opcode can onwy have so many vawues attached so
	 * add enough opcodes to woad the aww the commands
	 */
	bosize = (cmds_size + (cmds_size / TYPE4_MAX_PAYWOAD) + 1) << 2;

	ptw = msm_gem_kewnew_new(dwm, bosize,
		MSM_BO_WC | MSM_BO_GPU_WEADONWY, gpu->aspace,
		&a5xx_gpu->gpmu_bo, &a5xx_gpu->gpmu_iova);
	if (IS_EWW(ptw))
		wetuwn;

	msm_gem_object_set_name(a5xx_gpu->gpmu_bo, "gpmufw");

	whiwe (cmds_size > 0) {
		int i;
		uint32_t _size = cmds_size > TYPE4_MAX_PAYWOAD ?
			TYPE4_MAX_PAYWOAD : cmds_size;

		ptw[dwowds++] = PKT4(WEG_A5XX_GPMU_INST_WAM_BASE + offset,
			_size);

		fow (i = 0; i < _size; i++)
			ptw[dwowds++] = *cmds++;

		offset += _size;
		cmds_size -= _size;
	}

	msm_gem_put_vaddw(a5xx_gpu->gpmu_bo);
	a5xx_gpu->gpmu_dwowds = dwowds;
}
