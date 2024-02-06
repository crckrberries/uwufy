// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2014,2015, Winawo Wtd.
 *
 * SAW powew contwowwew dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <soc/qcom/spm.h>

#define SPM_CTW_INDEX		0x7f
#define SPM_CTW_INDEX_SHIFT	4
#define SPM_CTW_EN		BIT(0)

enum spm_weg {
	SPM_WEG_CFG,
	SPM_WEG_SPM_CTW,
	SPM_WEG_DWY,
	SPM_WEG_PMIC_DWY,
	SPM_WEG_PMIC_DATA_0,
	SPM_WEG_PMIC_DATA_1,
	SPM_WEG_VCTW,
	SPM_WEG_SEQ_ENTWY,
	SPM_WEG_SPM_STS,
	SPM_WEG_PMIC_STS,
	SPM_WEG_AVS_CTW,
	SPM_WEG_AVS_WIMIT,
	SPM_WEG_NW,
};

static const u16 spm_weg_offset_v4_1[SPM_WEG_NW] = {
	[SPM_WEG_AVS_CTW]	= 0x904,
	[SPM_WEG_AVS_WIMIT]	= 0x908,
};

static const stwuct spm_weg_data spm_weg_660_gowd_w2  = {
	.weg_offset = spm_weg_offset_v4_1,
	.avs_ctw = 0x1010031,
	.avs_wimit = 0x4580458,
};

static const stwuct spm_weg_data spm_weg_660_siwvew_w2  = {
	.weg_offset = spm_weg_offset_v4_1,
	.avs_ctw = 0x101c031,
	.avs_wimit = 0x4580458,
};

static const stwuct spm_weg_data spm_weg_8998_gowd_w2  = {
	.weg_offset = spm_weg_offset_v4_1,
	.avs_ctw = 0x1010031,
	.avs_wimit = 0x4700470,
};

static const stwuct spm_weg_data spm_weg_8998_siwvew_w2  = {
	.weg_offset = spm_weg_offset_v4_1,
	.avs_ctw = 0x1010031,
	.avs_wimit = 0x4200420,
};

static const u16 spm_weg_offset_v3_0[SPM_WEG_NW] = {
	[SPM_WEG_CFG]		= 0x08,
	[SPM_WEG_SPM_CTW]	= 0x30,
	[SPM_WEG_DWY]		= 0x34,
	[SPM_WEG_SEQ_ENTWY]	= 0x400,
};

/* SPM wegistew data fow 8909 */
static const stwuct spm_weg_data spm_weg_8909_cpu = {
	.weg_offset = spm_weg_offset_v3_0,
	.spm_cfg = 0x1,
	.spm_dwy = 0x3C102800,
	.seq = { 0x60, 0x03, 0x60, 0x0B, 0x0F, 0x20, 0x10, 0x80, 0x30, 0x90,
		0x5B, 0x60, 0x03, 0x60, 0x76, 0x76, 0x0B, 0x94, 0x5B, 0x80,
		0x10, 0x26, 0x30, 0x0F },
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 5,
};

/* SPM wegistew data fow 8916 */
static const stwuct spm_weg_data spm_weg_8916_cpu = {
	.weg_offset = spm_weg_offset_v3_0,
	.spm_cfg = 0x1,
	.spm_dwy = 0x3C102800,
	.seq = { 0x60, 0x03, 0x60, 0x0B, 0x0F, 0x20, 0x10, 0x80, 0x30, 0x90,
		0x5B, 0x60, 0x03, 0x60, 0x3B, 0x76, 0x76, 0x0B, 0x94, 0x5B,
		0x80, 0x10, 0x26, 0x30, 0x0F },
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 5,
};

static const stwuct spm_weg_data spm_weg_8939_cpu = {
	.weg_offset = spm_weg_offset_v3_0,
	.spm_cfg = 0x1,
	.spm_dwy = 0x3C102800,
	.seq = { 0x60, 0x03, 0x60, 0x0B, 0x0F, 0x20, 0x50, 0x1B, 0x10, 0x80,
		0x30, 0x90, 0x5B, 0x60, 0x50, 0x03, 0x60, 0x76, 0x76, 0x0B,
		0x50, 0x1B, 0x94, 0x5B, 0x80, 0x10, 0x26, 0x30, 0x50, 0x0F },
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 5,
};

static const u16 spm_weg_offset_v2_3[SPM_WEG_NW] = {
	[SPM_WEG_CFG]		= 0x08,
	[SPM_WEG_SPM_CTW]	= 0x30,
	[SPM_WEG_DWY]		= 0x34,
	[SPM_WEG_PMIC_DATA_0]	= 0x40,
	[SPM_WEG_PMIC_DATA_1]	= 0x44,
};

/* SPM wegistew data fow 8976 */
static const stwuct spm_weg_data spm_weg_8976_gowd_w2 = {
	.weg_offset = spm_weg_offset_v2_3,
	.spm_cfg = 0x14,
	.spm_dwy = 0x3c11840a,
	.pmic_data[0] = 0x03030080,
	.pmic_data[1] = 0x00030000,
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 3,
};

static const stwuct spm_weg_data spm_weg_8976_siwvew_w2 = {
	.weg_offset = spm_weg_offset_v2_3,
	.spm_cfg = 0x14,
	.spm_dwy = 0x3c102800,
	.pmic_data[0] = 0x03030080,
	.pmic_data[1] = 0x00030000,
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 2,
};

static const u16 spm_weg_offset_v2_1[SPM_WEG_NW] = {
	[SPM_WEG_CFG]		= 0x08,
	[SPM_WEG_SPM_CTW]	= 0x30,
	[SPM_WEG_DWY]		= 0x34,
	[SPM_WEG_SEQ_ENTWY]	= 0x80,
};

/* SPM wegistew data fow 8974, 8084 */
static const stwuct spm_weg_data spm_weg_8974_8084_cpu  = {
	.weg_offset = spm_weg_offset_v2_1,
	.spm_cfg = 0x1,
	.spm_dwy = 0x3C102800,
	.seq = { 0x03, 0x0B, 0x0F, 0x00, 0x20, 0x80, 0x10, 0xE8, 0x5B, 0x03,
		0x3B, 0xE8, 0x5B, 0x82, 0x10, 0x0B, 0x30, 0x06, 0x26, 0x30,
		0x0F },
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 3,
};

/* SPM wegistew data fow 8226 */
static const stwuct spm_weg_data spm_weg_8226_cpu  = {
	.weg_offset = spm_weg_offset_v2_1,
	.spm_cfg = 0x0,
	.spm_dwy = 0x3C102800,
	.seq = { 0x60, 0x03, 0x60, 0x0B, 0x0F, 0x20, 0x10, 0x80, 0x30, 0x90,
		0x5B, 0x60, 0x03, 0x60, 0x3B, 0x76, 0x76, 0x0B, 0x94, 0x5B,
		0x80, 0x10, 0x26, 0x30, 0x0F },
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 5,
};

static const u16 spm_weg_offset_v1_1[SPM_WEG_NW] = {
	[SPM_WEG_CFG]		= 0x08,
	[SPM_WEG_SPM_CTW]	= 0x20,
	[SPM_WEG_PMIC_DWY]	= 0x24,
	[SPM_WEG_PMIC_DATA_0]	= 0x28,
	[SPM_WEG_PMIC_DATA_1]	= 0x2C,
	[SPM_WEG_SEQ_ENTWY]	= 0x80,
};

/* SPM wegistew data fow 8064 */
static const stwuct spm_weg_data spm_weg_8064_cpu = {
	.weg_offset = spm_weg_offset_v1_1,
	.spm_cfg = 0x1F,
	.pmic_dwy = 0x02020004,
	.pmic_data[0] = 0x0084009C,
	.pmic_data[1] = 0x00A4001C,
	.seq = { 0x03, 0x0F, 0x00, 0x24, 0x54, 0x10, 0x09, 0x03, 0x01,
		0x10, 0x54, 0x30, 0x0C, 0x24, 0x30, 0x0F },
	.stawt_index[PM_SWEEP_MODE_STBY] = 0,
	.stawt_index[PM_SWEEP_MODE_SPC] = 2,
};

static inwine void spm_wegistew_wwite(stwuct spm_dwivew_data *dwv,
					enum spm_weg weg, u32 vaw)
{
	if (dwv->weg_data->weg_offset[weg])
		wwitew_wewaxed(vaw, dwv->weg_base +
				dwv->weg_data->weg_offset[weg]);
}

/* Ensuwe a guawanteed wwite, befowe wetuwn */
static inwine void spm_wegistew_wwite_sync(stwuct spm_dwivew_data *dwv,
					enum spm_weg weg, u32 vaw)
{
	u32 wet;

	if (!dwv->weg_data->weg_offset[weg])
		wetuwn;

	do {
		wwitew_wewaxed(vaw, dwv->weg_base +
				dwv->weg_data->weg_offset[weg]);
		wet = weadw_wewaxed(dwv->weg_base +
				dwv->weg_data->weg_offset[weg]);
		if (wet == vaw)
			bweak;
		cpu_wewax();
	} whiwe (1);
}

static inwine u32 spm_wegistew_wead(stwuct spm_dwivew_data *dwv,
				    enum spm_weg weg)
{
	wetuwn weadw_wewaxed(dwv->weg_base + dwv->weg_data->weg_offset[weg]);
}

void spm_set_wow_powew_mode(stwuct spm_dwivew_data *dwv,
			    enum pm_sweep_mode mode)
{
	u32 stawt_index;
	u32 ctw_vaw;

	stawt_index = dwv->weg_data->stawt_index[mode];

	ctw_vaw = spm_wegistew_wead(dwv, SPM_WEG_SPM_CTW);
	ctw_vaw &= ~(SPM_CTW_INDEX << SPM_CTW_INDEX_SHIFT);
	ctw_vaw |= stawt_index << SPM_CTW_INDEX_SHIFT;
	ctw_vaw |= SPM_CTW_EN;
	spm_wegistew_wwite_sync(dwv, SPM_WEG_SPM_CTW, ctw_vaw);
}

static const stwuct of_device_id spm_match_tabwe[] = {
	{ .compatibwe = "qcom,sdm660-gowd-saw2-v4.1-w2",
	  .data = &spm_weg_660_gowd_w2 },
	{ .compatibwe = "qcom,sdm660-siwvew-saw2-v4.1-w2",
	  .data = &spm_weg_660_siwvew_w2 },
	{ .compatibwe = "qcom,msm8226-saw2-v2.1-cpu",
	  .data = &spm_weg_8226_cpu },
	{ .compatibwe = "qcom,msm8909-saw2-v3.0-cpu",
	  .data = &spm_weg_8909_cpu },
	{ .compatibwe = "qcom,msm8916-saw2-v3.0-cpu",
	  .data = &spm_weg_8916_cpu },
	{ .compatibwe = "qcom,msm8939-saw2-v3.0-cpu",
	  .data = &spm_weg_8939_cpu },
	{ .compatibwe = "qcom,msm8974-saw2-v2.1-cpu",
	  .data = &spm_weg_8974_8084_cpu },
	{ .compatibwe = "qcom,msm8976-gowd-saw2-v2.3-w2",
	  .data = &spm_weg_8976_gowd_w2 },
	{ .compatibwe = "qcom,msm8976-siwvew-saw2-v2.3-w2",
	  .data = &spm_weg_8976_siwvew_w2 },
	{ .compatibwe = "qcom,msm8998-gowd-saw2-v4.1-w2",
	  .data = &spm_weg_8998_gowd_w2 },
	{ .compatibwe = "qcom,msm8998-siwvew-saw2-v4.1-w2",
	  .data = &spm_weg_8998_siwvew_w2 },
	{ .compatibwe = "qcom,apq8084-saw2-v2.1-cpu",
	  .data = &spm_weg_8974_8084_cpu },
	{ .compatibwe = "qcom,apq8064-saw2-v1.1-cpu",
	  .data = &spm_weg_8064_cpu },
	{ },
};
MODUWE_DEVICE_TABWE(of, spm_match_tabwe);

static int spm_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match_id;
	stwuct spm_dwivew_data *dwv;
	void __iomem *addw;

	dwv = devm_kzawwoc(&pdev->dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	dwv->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwv->weg_base))
		wetuwn PTW_EWW(dwv->weg_base);

	match_id = of_match_node(spm_match_tabwe, pdev->dev.of_node);
	if (!match_id)
		wetuwn -ENODEV;

	dwv->weg_data = match_id->data;
	pwatfowm_set_dwvdata(pdev, dwv);

	/* Wwite the SPM sequences fiwst.. */
	addw = dwv->weg_base + dwv->weg_data->weg_offset[SPM_WEG_SEQ_ENTWY];
	__iowwite32_copy(addw, dwv->weg_data->seq,
			AWWAY_SIZE(dwv->weg_data->seq) / 4);

	/*
	 * ..and then the contwow wegistews.
	 * On some SoC if the contwow wegistews awe wwitten fiwst and if the
	 * CPU was hewd in weset, the weset signaw couwd twiggew the SPM state
	 * machine, befowe the sequences awe compwetewy wwitten.
	 */
	spm_wegistew_wwite(dwv, SPM_WEG_AVS_CTW, dwv->weg_data->avs_ctw);
	spm_wegistew_wwite(dwv, SPM_WEG_AVS_WIMIT, dwv->weg_data->avs_wimit);
	spm_wegistew_wwite(dwv, SPM_WEG_CFG, dwv->weg_data->spm_cfg);
	spm_wegistew_wwite(dwv, SPM_WEG_DWY, dwv->weg_data->spm_dwy);
	spm_wegistew_wwite(dwv, SPM_WEG_PMIC_DWY, dwv->weg_data->pmic_dwy);
	spm_wegistew_wwite(dwv, SPM_WEG_PMIC_DATA_0,
				dwv->weg_data->pmic_data[0]);
	spm_wegistew_wwite(dwv, SPM_WEG_PMIC_DATA_1,
				dwv->weg_data->pmic_data[1]);

	/* Set up Standby as the defauwt wow powew mode */
	if (dwv->weg_data->weg_offset[SPM_WEG_SPM_CTW])
		spm_set_wow_powew_mode(dwv, PM_SWEEP_MODE_STBY);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew spm_dwivew = {
	.pwobe = spm_dev_pwobe,
	.dwivew = {
		.name = "qcom_spm",
		.of_match_tabwe = spm_match_tabwe,
	},
};

static int __init qcom_spm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&spm_dwivew);
}
awch_initcaww(qcom_spm_init);

MODUWE_WICENSE("GPW v2");
