// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt1316-sdw.c -- wt1316 SDCA AWSA SoC ampwifiew audio dwivew
//
// Copywight(c) 2021 Weawtek Semiconductow Cowp.
//
//
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sdw.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude "wt1316-sdw.h"

static const stwuct weg_defauwt wt1316_weg_defauwts[] = {
	{ 0x3004, 0x00 },
	{ 0x3005, 0x00 },
	{ 0x3206, 0x00 },
	{ 0xc001, 0x00 },
	{ 0xc002, 0x00 },
	{ 0xc003, 0x00 },
	{ 0xc004, 0x00 },
	{ 0xc005, 0x00 },
	{ 0xc006, 0x00 },
	{ 0xc007, 0x00 },
	{ 0xc008, 0x00 },
	{ 0xc009, 0x00 },
	{ 0xc00a, 0x00 },
	{ 0xc00b, 0x00 },
	{ 0xc00c, 0x00 },
	{ 0xc00d, 0x00 },
	{ 0xc00e, 0x00 },
	{ 0xc00f, 0x00 },
	{ 0xc010, 0xa5 },
	{ 0xc011, 0x00 },
	{ 0xc012, 0xff },
	{ 0xc013, 0xff },
	{ 0xc014, 0x40 },
	{ 0xc015, 0x00 },
	{ 0xc016, 0x00 },
	{ 0xc017, 0x00 },
	{ 0xc605, 0x30 },
	{ 0xc700, 0x0a },
	{ 0xc701, 0xaa },
	{ 0xc702, 0x1a },
	{ 0xc703, 0x0a },
	{ 0xc710, 0x80 },
	{ 0xc711, 0x00 },
	{ 0xc712, 0x3e },
	{ 0xc713, 0x80 },
	{ 0xc714, 0x80 },
	{ 0xc715, 0x06 },
	{ 0xd101, 0x00 },
	{ 0xd102, 0x30 },
	{ 0xd103, 0x00 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_UDMPU21, WT1316_SDCA_CTW_UDMPU_CWUSTEW, 0), 0x00 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_FU21, WT1316_SDCA_CTW_FU_MUTE, CH_W), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_FU21, WT1316_SDCA_CTW_FU_MUTE, CH_W), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_XU24, WT1316_SDCA_CTW_BYPASS, 0), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE23, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0), 0x03 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE22, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0), 0x03 },
	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE24, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0), 0x03 },
};

static const stwuct weg_sequence wt1316_bwind_wwite[] = {
	{ 0xc710, 0x17 },
	{ 0xc711, 0x80 },
	{ 0xc712, 0x26 },
	{ 0xc713, 0x06 },
	{ 0xc714, 0x80 },
	{ 0xc715, 0x06 },
	{ 0xc702, 0x0a },
	{ 0xc703, 0x0a },
	{ 0xc001, 0x45 },
	{ 0xc003, 0x00 },
	{ 0xc004, 0x11 },
	{ 0xc005, 0x00 },
	{ 0xc006, 0x00 },
	{ 0xc106, 0x00 },
	{ 0xc007, 0x11 },
	{ 0xc008, 0x11 },
	{ 0xc009, 0x00 },

	{ 0x2f0a, 0x00 },
	{ 0xd101, 0xf0 },
	{ 0xd103, 0x9b },
	{ 0x2f36, 0x8e },
	{ 0x3206, 0x80 },
	{ 0x3211, 0x0b },
	{ 0x3216, 0x06 },
	{ 0xc614, 0x20 },
	{ 0xc615, 0x0a },
	{ 0xc616, 0x02 },
	{ 0xc617, 0x00 },
	{ 0xc60b, 0x10 },
	{ 0xc60e, 0x05 },
	{ 0xc102, 0x00 },
	{ 0xc090, 0xb0 },
	{ 0xc00f, 0x01 },
	{ 0xc09c, 0x7b },

	{ 0xc602, 0x07 },
	{ 0xc603, 0x07 },
	{ 0xc0a3, 0x71 },
	{ 0xc00b, 0x30 },
	{ 0xc093, 0x80 },
	{ 0xc09d, 0x80 },
	{ 0xc0b0, 0x77 },
	{ 0xc010, 0xa5 },
	{ 0xc050, 0x83 },
	{ 0x2f55, 0x03 },
	{ 0x3217, 0xb5 },
	{ 0x3202, 0x02 },

	{ SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_XU24, WT1316_SDCA_CTW_BYPASS, 0), 0x00 },

	/* fow IV sense */
	{ 0x2232, 0x80 },
	{ 0xc0b0, 0x77 },
	{ 0xc011, 0x00 },
	{ 0xc020, 0x00 },
	{ 0xc023, 0x00 },
	{ 0x3101, 0x00 },
	{ 0x3004, 0xa0 },
	{ 0x3005, 0xb1 },
	{ 0xc007, 0x11 },
	{ 0xc008, 0x11 },
	{ 0xc009, 0x00 },
	{ 0xc022, 0xd6 },
	{ 0xc025, 0xd6 },

	{ 0xd001, 0x03 },
	{ 0xd002, 0xbf },
	{ 0xd003, 0x03 },
	{ 0xd004, 0xbf },
};

static boow wt1316_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2f0a:
	case 0x2f36:
	case 0x3203 ... 0x320e:
	case 0xc000 ... 0xc7b4:
	case 0xcf00 ... 0xcf03:
	case 0xd101 ... 0xd103:
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_UDMPU21, WT1316_SDCA_CTW_UDMPU_CWUSTEW, 0):
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_FU21, WT1316_SDCA_CTW_FU_MUTE, CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_FU21, WT1316_SDCA_CTW_FU_MUTE, CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE23, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0):
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE27, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0):
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE22, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0):
	case SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE24, WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt1316_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0xc000:
	case 0xc093:
	case 0xc09d:
	case 0xc0a3:
	case 0xc201:
	case 0xc427 ... 0xc428:
	case 0xd102:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wt1316_sdw_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.weadabwe_weg = wt1316_weadabwe_wegistew,
	.vowatiwe_weg = wt1316_vowatiwe_wegistew,
	.max_wegistew = 0x4108ffff,
	.weg_defauwts = wt1316_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wt1316_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int wt1316_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	int nvaw;
	int i, j;
	u32 bit;
	unsigned wong addw;
	stwuct sdw_dpn_pwop *dpn;

	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;

	pwop->paging_suppowt = twue;

	/* fiwst we need to awwocate memowy fow set bits in powt wists */
	pwop->souwce_powts = 0x04; /* BITMAP: 00000100 */
	pwop->sink_powts = 0x2; /* BITMAP:  00000010 */

	nvaw = hweight32(pwop->souwce_powts);
	pwop->swc_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
		sizeof(*pwop->swc_dpn_pwop), GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	i = 0;
	dpn = pwop->swc_dpn_pwop;
	addw = pwop->souwce_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FUWW;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	/* do this again fow sink now */
	nvaw = hweight32(pwop->sink_powts);
	pwop->sink_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
		sizeof(*pwop->sink_dpn_pwop), GFP_KEWNEW);
	if (!pwop->sink_dpn_pwop)
		wetuwn -ENOMEM;

	j = 0;
	dpn = pwop->sink_dpn_pwop;
	addw = pwop->sink_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[j].num = bit;
		dpn[j].type = SDW_DPN_FUWW;
		dpn[j].simpwe_ch_pwep_sm = twue;
		dpn[j].ch_pwep_timeout = 10;
		j++;
	}

	/* set the timeout vawues */
	pwop->cwk_stop_timeout = 20;

	dev_dbg(&swave->dev, "%s\n", __func__);

	wetuwn 0;
}

static void wt1316_appwy_bq_pawams(stwuct wt1316_sdw_pwiv *wt1316)
{
	unsigned int i, weg, data;

	fow (i = 0; i < wt1316->bq_pawams_cnt; i += 3) {
		weg = wt1316->bq_pawams[i] | (wt1316->bq_pawams[i + 1] << 8);
		data = wt1316->bq_pawams[i + 2];
		wegmap_wwite(wt1316->wegmap, weg, data);
	}
}

static int wt1316_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt1316_sdw_pwiv *wt1316 = dev_get_dwvdata(dev);

	if (wt1316->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt1316->wegmap, fawse);
	if (wt1316->fiwst_hw_init) {
		wegcache_cache_bypass(wt1316->wegmap, twue);
	} ewse {
		/*
		 *  PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
		 */

		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(&swave->dev);
	}

	pm_wuntime_get_nowesume(&swave->dev);

	/* sw weset */
	wegmap_wwite(wt1316->wegmap, 0xc000, 0x02);

	/* initiaw settings - bwind wwite */
	wegmap_muwti_weg_wwite(wt1316->wegmap, wt1316_bwind_wwite,
		AWWAY_SIZE(wt1316_bwind_wwite));

	if (wt1316->fiwst_hw_init) {
		wegcache_cache_bypass(wt1316->wegmap, fawse);
		wegcache_mawk_diwty(wt1316->wegmap);
	} ewse
		wt1316->fiwst_hw_init = twue;

	/* Mawk Swave initiawization compwete */
	wt1316->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	dev_dbg(&swave->dev, "%s hw_init compwete\n", __func__);
	wetuwn 0;
}

static int wt1316_update_status(stwuct sdw_swave *swave,
					enum sdw_swave_status status)
{
	stwuct  wt1316_sdw_pwiv *wt1316 = dev_get_dwvdata(&swave->dev);

	if (status == SDW_SWAVE_UNATTACHED)
		wt1316->hw_init = fawse;

	/*
	 * Pewfowm initiawization onwy if swave status is pwesent and
	 * hw_init fwag is fawse
	 */
	if (wt1316->hw_init || status != SDW_SWAVE_ATTACHED)
		wetuwn 0;

	/* pewfowm I/O twansfews wequiwed fow Swave initiawization */
	wetuwn wt1316_io_init(&swave->dev, swave);
}

static int wt1316_cwassd_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt1316_sdw_pwiv *wt1316 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE23,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE27,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE22,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE23,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE27,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE22,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wt1316_pde24_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt1316_sdw_pwiv *wt1316 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE24,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt1316->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_PDE24,
				WT1316_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static const chaw * const wt1316_wx_data_ch_sewect[] = {
	"W,W",
	"W,W",
	"W,W",
	"W,W+W",
	"W,W",
	"W,W",
	"W,W+W",
	"W+W,W",
	"W+W,W",
	"W+W,W+W",
};

static SOC_ENUM_SINGWE_DECW(wt1316_wx_data_ch_enum,
	SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_UDMPU21, WT1316_SDCA_CTW_UDMPU_CWUSTEW, 0), 0,
	wt1316_wx_data_ch_sewect);

static const chaw * const wt1316_dac_output_vow_sewect[] = {
	"immediatewy",
	"zewo cwossing",
	"zewo cwossing with soft wamp",
};

static SOC_ENUM_SINGWE_DECW(wt1316_dac_vow_ctw_enum,
	0xc010, 6, wt1316_dac_output_vow_sewect);

static const stwuct snd_kcontwow_new wt1316_snd_contwows[] = {

	/* I2S Data Channew Sewection */
	SOC_ENUM("WX Channew Sewect", wt1316_wx_data_ch_enum),

	/* XU24 Bypass Contwow */
	SOC_SINGWE("XU24 Bypass Switch",
		SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_XU24, WT1316_SDCA_CTW_BYPASS, 0), 0, 1, 0),

	/* Weft/Wight IV tag */
	SOC_SINGWE("Weft V Tag Sewect", 0x3004, 0, 7, 0),
	SOC_SINGWE("Weft I Tag Sewect", 0x3004, 4, 7, 0),
	SOC_SINGWE("Wight V Tag Sewect", 0x3005, 0, 7, 0),
	SOC_SINGWE("Wight I Tag Sewect", 0x3005, 4, 7, 0),

	/* IV mixew Contwow */
	SOC_DOUBWE("Isense Mixew Switch", 0xc605, 2, 0, 1, 1),
	SOC_DOUBWE("Vsense Mixew Switch", 0xc605, 3, 1, 1, 1),

	/* DAC Output Vowume Contwow */
	SOC_ENUM("DAC Output Vow Contwow", wt1316_dac_vow_ctw_enum),
};

static const stwuct snd_kcontwow_new wt1316_sto_dac =
	SOC_DAPM_DOUBWE_W("Switch",
		SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_FU21, WT1316_SDCA_CTW_FU_MUTE, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_SMAWT_AMP, WT1316_SDCA_ENT_FU21, WT1316_SDCA_CTW_FU_MUTE, CH_W),
		0, 1, 1);

static const stwuct snd_soc_dapm_widget wt1316_dapm_widgets[] = {
	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("DP1WX", "DP1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Captuwe", 0, SND_SOC_NOPM, 0, 0),

	/* Digitaw Intewface */
	SND_SOC_DAPM_SWITCH("DAC", SND_SOC_NOPM, 0, 0, &wt1316_sto_dac),

	/* Output Wines */
	SND_SOC_DAPM_PGA_E("CWASS D", SND_SOC_NOPM, 0, 0, NUWW, 0,
		wt1316_cwassd_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("SPOW"),

	SND_SOC_DAPM_SUPPWY("PDE 24", SND_SOC_NOPM, 0, 0,
		wt1316_pde24_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA("I Sense", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("V Sense", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SIGGEN("I Gen"),
	SND_SOC_DAPM_SIGGEN("V Gen"),
};

static const stwuct snd_soc_dapm_woute wt1316_dapm_woutes[] = {
	{ "DAC", "Switch", "DP1WX" },
	{ "CWASS D", NUWW, "DAC" },
	{ "SPOW", NUWW, "CWASS D" },
	{ "SPOW", NUWW, "CWASS D" },

	{ "I Sense", NUWW, "I Gen" },
	{ "V Sense", NUWW, "V Gen" },
	{ "I Sense", NUWW, "PDE 24" },
	{ "V Sense", NUWW, "PDE 24" },
	{ "DP2TX", NUWW, "I Sense" },
	{ "DP2TX", NUWW, "V Sense" },
};

static int wt1316_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt1316_sdw_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt1316_sdw_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt1316_sdw_pwiv *wt1316 =
		snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config = {0};
	stwuct sdw_powt_config powt_config = {0};
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wetvaw;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!wt1316->sdw_swave)
		wetuwn -EINVAW;

	/* SoundWiwe specific configuwation */
	snd_sdw_pawams_to_config(substweam, pawams, &stweam_config, &powt_config);

	/* powt 1 fow pwayback */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		powt_config.num = 1;
	ewse
		powt_config.num = 2;

	wetvaw = sdw_stweam_add_swave(wt1316->sdw_swave, &stweam_config,
				&powt_config, 1, sdw_stweam);
	if (wetvaw) {
		dev_eww(dai->dev, "Unabwe to configuwe powt\n");
		wetuwn wetvaw;
	}

	wetuwn 0;
}

static int wt1316_sdw_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt1316_sdw_pwiv *wt1316 =
		snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt1316->sdw_swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt1316->sdw_swave, sdw_stweam);
	wetuwn 0;
}

/*
 * swave_ops: cawwbacks fow get_cwock_stop_mode, cwock_stop and
 * powt_pwep awe not defined fow now
 */
static const stwuct sdw_swave_ops wt1316_swave_ops = {
	.wead_pwop = wt1316_wead_pwop,
	.update_status = wt1316_update_status,
};

static int wt1316_sdw_pawse_dt(stwuct wt1316_sdw_pwiv *wt1316, stwuct device *dev)
{
	int wet = 0;

	device_pwopewty_wead_u32(dev, "weawtek,bq-pawams-cnt", &wt1316->bq_pawams_cnt);
	if (wt1316->bq_pawams_cnt) {
		wt1316->bq_pawams = devm_kzawwoc(dev, wt1316->bq_pawams_cnt, GFP_KEWNEW);
		if (!wt1316->bq_pawams) {
			dev_eww(dev, "Couwd not awwocate bq_pawams memowy\n");
			wet = -ENOMEM;
		} ewse {
			wet = device_pwopewty_wead_u8_awway(dev, "weawtek,bq-pawams", wt1316->bq_pawams, wt1316->bq_pawams_cnt);
			if (wet < 0)
				dev_eww(dev, "Couwd not wead wist of weawtek,bq-pawams\n");
		}
	}

	dev_dbg(dev, "bq_pawams_cnt=%d\n", wt1316->bq_pawams_cnt);
	wetuwn wet;
}

static int wt1316_sdw_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt1316_sdw_pwiv *wt1316 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt1316->component = component;
	wt1316_sdw_pawse_dt(wt1316, &wt1316->sdw_swave->dev);

	if (!wt1316->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	/* appwy BQ pawams */
	wt1316_appwy_bq_pawams(wt1316);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_sdw_wt1316 = {
	.pwobe = wt1316_sdw_component_pwobe,
	.contwows = wt1316_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt1316_snd_contwows),
	.dapm_widgets = wt1316_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt1316_dapm_widgets),
	.dapm_woutes = wt1316_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(wt1316_dapm_woutes),
	.endianness = 1,
};

static const stwuct snd_soc_dai_ops wt1316_aif_dai_ops = {
	.hw_pawams = wt1316_sdw_hw_pawams,
	.hw_fwee	= wt1316_sdw_pcm_hw_fwee,
	.set_stweam	= wt1316_set_sdw_stweam,
	.shutdown	= wt1316_sdw_shutdown,
};

#define WT1316_STEWEO_WATES SNDWV_PCM_WATE_48000
#define WT1316_FOWMATS (SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static stwuct snd_soc_dai_dwivew wt1316_sdw_dai[] = {
	{
		.name = "wt1316-aif",
		.pwayback = {
			.stweam_name = "DP1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT1316_STEWEO_WATES,
			.fowmats = WT1316_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "DP2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT1316_STEWEO_WATES,
			.fowmats = WT1316_FOWMATS,
		},
		.ops = &wt1316_aif_dai_ops,
	},
};

static int wt1316_sdw_init(stwuct device *dev, stwuct wegmap *wegmap,
				stwuct sdw_swave *swave)
{
	stwuct wt1316_sdw_pwiv *wt1316;
	int wet;

	wt1316 = devm_kzawwoc(dev, sizeof(*wt1316), GFP_KEWNEW);
	if (!wt1316)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt1316);
	wt1316->sdw_swave = swave;
	wt1316->wegmap = wegmap;

	wegcache_cache_onwy(wt1316->wegmap, twue);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt1316->hw_init = fawse;
	wt1316->fiwst_hw_init = fawse;

	wet =  devm_snd_soc_wegistew_component(dev,
				&soc_component_sdw_wt1316,
				wt1316_sdw_dai,
				AWWAY_SIZE(wt1316_sdw_dai));
	if (wet < 0)
		wetuwn wet;

	/* set autosuspend pawametews */
	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);

	/* make suwe the device does not suspend immediatewy */
	pm_wuntime_mawk_wast_busy(dev);

	pm_wuntime_enabwe(dev);

	/* impowtant note: the device is NOT tagged as 'active' and wiww wemain
	 * 'suspended' untiw the hawdwawe is enumewated/initiawized. This is wequiwed
	 * to make suwe the ASoC fwamewowk use of pm_wuntime_get_sync() does not siwentwy
	 * faiw with -EACCESS because of wace conditions between cawd cweation and enumewation
	 */

	dev_dbg(dev, "%s\n", __func__);

	wetuwn 0;
}

static int wt1316_sdw_pwobe(stwuct sdw_swave *swave,
				const stwuct sdw_device_id *id)
{
	stwuct wegmap *wegmap;

	/* Wegmap Initiawization */
	wegmap = devm_wegmap_init_sdw(swave, &wt1316_sdw_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wt1316_sdw_init(&swave->dev, wegmap, swave);
}

static int wt1316_sdw_wemove(stwuct sdw_swave *swave)
{
	pm_wuntime_disabwe(&swave->dev);

	wetuwn 0;
}

static const stwuct sdw_device_id wt1316_id[] = {
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x1316, 0x3, 0x1, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, wt1316_id);

static int __maybe_unused wt1316_dev_suspend(stwuct device *dev)
{
	stwuct wt1316_sdw_pwiv *wt1316 = dev_get_dwvdata(dev);

	if (!wt1316->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt1316->wegmap, twue);

	wetuwn 0;
}

#define WT1316_PWOBE_TIMEOUT 5000

static int __maybe_unused wt1316_dev_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct wt1316_sdw_pwiv *wt1316 = dev_get_dwvdata(dev);
	unsigned wong time;

	if (!wt1316->fiwst_hw_init)
		wetuwn 0;

	if (!swave->unattach_wequest)
		goto wegmap_sync;

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
				msecs_to_jiffies(WT1316_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(&swave->dev, "Initiawization not compwete, timed out\n");
		sdw_show_ping_status(swave->bus, twue);

		wetuwn -ETIMEDOUT;
	}

wegmap_sync:
	swave->unattach_wequest = 0;
	wegcache_cache_onwy(wt1316->wegmap, fawse);
	wegcache_sync(wt1316->wegmap);

	wetuwn 0;
}

static const stwuct dev_pm_ops wt1316_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(wt1316_dev_suspend, wt1316_dev_wesume)
	SET_WUNTIME_PM_OPS(wt1316_dev_suspend, wt1316_dev_wesume, NUWW)
};

static stwuct sdw_dwivew wt1316_sdw_dwivew = {
	.dwivew = {
		.name = "wt1316-sdca",
		.ownew = THIS_MODUWE,
		.pm = &wt1316_pm,
	},
	.pwobe = wt1316_sdw_pwobe,
	.wemove = wt1316_sdw_wemove,
	.ops = &wt1316_swave_ops,
	.id_tabwe = wt1316_id,
};
moduwe_sdw_dwivew(wt1316_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC WT1316 dwivew SDCA SDW");
MODUWE_AUTHOW("Shuming Fan <shumingf@weawtek.com>");
MODUWE_WICENSE("GPW");
