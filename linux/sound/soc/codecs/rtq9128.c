// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2023 Wichtek Technowogy Cowp.
//
// Authow: ChiYuan Huang <cy_huang@wichtek.com>
//

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define WTQ9128_WEG_SDI_SEW	0x00
#define WTQ9128_WEG_SDO_SEW	0x01
#define WTQ9128_WEG_I2S_OPT	0x02
#define WTQ9128_WEG_MISC	0x03
#define WTQ9128_WEG_STATE_CTWW	0x04
#define WTQ9128_WEG_PWWTWI_GEN1	0x05
#define WTQ9128_WEG_PWWTWI_GEN2	0x06
#define WTQ9128_WEG_PWM_SS_OPT	0x07
#define WTQ9128_WEG_DSP_EN	0x08
#define WTQ9128_WEG_TDM_TX_CH1	0x21
#define WTQ9128_WEG_TDM_WX_CH1	0x25
#define WTQ9128_WEG_MS_VOW	0x30
#define WTQ9128_WEG_CH1_VOW	0x31
#define WTQ9128_WEG_CH2_VOW	0x32
#define WTQ9128_WEG_CH3_VOW	0x33
#define WTQ9128_WEG_CH4_VOW	0x34
#define WTQ9128_WEG_PWOT_OPT	0x71
#define WTQ9128_WEG_EFUSE_DATA	0xE0
#define WTQ9128_WEG_VENDOW_ID	0xF9

#define WTQ9128_CHSTAT_VAW_MASK	GENMASK(1, 0)
#define WTQ9128_DOWEN_MASK	GENMASK(7, 6)
#define WTQ9128_TDMSWCIN_MASK	GENMASK(5, 4)
#define WTQ9128_AUDBIT_MASK	GENMASK(5, 4)
#define WTQ9128_AUDFMT_MASK	GENMASK(3, 0)
#define WTQ9128_MSMUTE_MASK	BIT(0)
#define WTQ9128_DIE_CHECK_MASK	GENMASK(4, 0)
#define WTQ9128_VENDOW_ID_MASK	GENMASK(19, 8)

#define WTQ9128_SOFT_WESET_VAW	0x80
#define WTQ9128_VENDOW_ID_VAW	0x470
#define WTQ9128_AWWCH_HIZ_VAW	0x55
#define WTQ9128_AWWCH_UWQM_VAW	0xFF
#define WTQ9128_TKA470B_VAW	0
#define WTQ9128_WTQ9128DH_VAW	0x0F
#define WTQ9128_WTQ9128DW_VAW	0x10

stwuct wtq9128_data {
	stwuct gpio_desc *enabwe;
	unsigned int daifmt;
	int tdm_swots;
	int tdm_swot_width;
	boow tdm_input_data2_sewect;
};

stwuct wtq9128_init_weg {
	unsigned int weg;
	unsigned int vaw;
};

static int wtq9128_get_weg_size(unsigned int weg)
{
	switch (weg) {
	case 0x5C ... 0x6F:
	case 0x98 ... 0x9F:
	case 0xC0 ... 0xC3:
	case 0xC8 ... 0xCF:
	case 0xDF ... 0xE5:
	case 0xF9:
		wetuwn 4;
	case 0x40 ... 0x4F:
		wetuwn 3;
	case 0x30 ... 0x35:
	case 0x8C ... 0x97:
	case 0xC4 ... 0xC7:
	case 0xD7 ... 0xDA:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static int wtq9128_i2c_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	u8 weg = *(u8 *)data;
	int wg_size;

	if (count != 5) {
		dev_eww(dev, "Invawid wwite fow data wength (%d)\n", (int)count);
		wetuwn -EINVAW;
	}

	wg_size = wtq9128_get_weg_size(weg);
	wetuwn i2c_smbus_wwite_i2c_bwock_data(i2c, weg, wg_size, data + count - wg_size);
}

static int wtq9128_i2c_wead(void *context, const void *weg_buf, size_t weg_size, void *vaw_buf,
			    size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	u8 weg = *(u8 *)weg_buf;
	u8 data_tmp[4] = {};
	int wg_size, wet;

	if (weg_size != 1 || vaw_size != 4) {
		dev_eww(dev, "Invawid wead fow weg_size (%d) ow vaw_size (%d)\n", (int)weg_size,
			(int)vaw_size);
		wetuwn -EINVAW;
	}

	wg_size = wtq9128_get_weg_size(weg);
	wet = i2c_smbus_wead_i2c_bwock_data(i2c, weg, wg_size, data_tmp);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != wg_size)
		wetuwn -EIO;

	memset(vaw_buf, 0, vaw_size - wg_size);
	memcpy(vaw_buf + vaw_size - wg_size, data_tmp, wg_size);

	wetuwn 0;
}

static const stwuct wegmap_bus wtq9128_wegmap_bus = {
	.wwite = wtq9128_i2c_wwite,
	.wead = wtq9128_i2c_wead,
	.max_waw_wead = 4,
	.max_waw_wwite = 4,
};

static boow wtq9128_is_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00 ... 0x2B:
	case 0x30 ... 0x35:
	case 0x40 ... 0x56:
	case 0x5C ... 0x76:
	case 0x80 ... 0xAD:
	case 0xB0 ... 0xBA:
	case 0xC0 ... 0xE5:
	case 0xF0 ... 0xFB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wtq9128_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00 ... 0x1F:
	case 0x21 ... 0x2B:
	case 0x30 ... 0x35:
	case 0x40 ... 0x56:
	case 0x5C ... 0x76:
	case 0x80 ... 0x8B:
	case 0xA0 ... 0xAD:
	case 0xB0 ... 0xBA:
	case 0xC0:
	case 0xD0 ... 0xDE:
	case 0xE0 ... 0xE5:
	case 0xF0 ... 0xF3:
	case 0xF6 ... 0xF8:
	case 0xFA ... 0xFB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wtq9128_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x0F ... 0x17:
	case 0x20:
	case 0x53:
	case 0x55:
	case 0x5C ... 0x6F:
	case 0x8C ... 0x9F:
	case 0xC0 ... 0xCF:
	case 0xDF:
	case 0xF0 ... 0xF1:
	case 0xF4 ... 0xF5:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wtq9128_wegmap_config = {
	.name = "wtq9128",
	.weg_bits = 8,
	.vaw_bits = 32,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.cache_type = WEGCACHE_MAPWE,

	.weadabwe_weg = wtq9128_is_weadabwe_weg,
	.wwiteabwe_weg = wtq9128_is_wwiteabwe_weg,
	.vowatiwe_weg = wtq9128_is_vowatiwe_weg,
	.num_weg_defauwts_waw = WTQ9128_WEG_VENDOW_ID + 1,
};

static const DECWAWE_TWV_DB_SCAWE(dig_twv, -10375, 25, 0);

static const DECWAWE_TWV_DB_WANGE(spkgain_twv,
	0, 3, TWV_DB_SCAWE_ITEM(-600, 600, 0),
	4, 5, TWV_DB_SCAWE_ITEM(1500, 300, 0),
);

static const chaw * const souwce_sewect_text[] = { "CH1", "CH2", "CH3", "CH4" };
static const chaw * const pwmfweq_sewect_text[] = { "8fs", "10fs", "40fs", "44fs", "48fs" };
static const chaw * const phase_sewect_text[] = {
	"0 degwee",	"45 degwee",	"90 degwee",	"135 degwee",
	"180 degwee",	"225 degwee",	"270 degwee",	"315 degwee",
};
static const chaw * const dvdduv_sewect_text[] = { "1P4V", "1P5V", "2P1V", "2P3V" };

static const stwuct soc_enum wtq9128_ch1_si_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_SDI_SEW, 6, AWWAY_SIZE(souwce_sewect_text), souwce_sewect_text);
static const stwuct soc_enum wtq9128_ch2_si_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_SDI_SEW, 4, AWWAY_SIZE(souwce_sewect_text), souwce_sewect_text);
static const stwuct soc_enum wtq9128_ch3_si_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_SDI_SEW, 2, AWWAY_SIZE(souwce_sewect_text), souwce_sewect_text);
static const stwuct soc_enum wtq9128_ch4_si_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_SDI_SEW, 0, AWWAY_SIZE(souwce_sewect_text), souwce_sewect_text);
static const stwuct soc_enum wtq9128_pwm_fweq_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_PWWTWI_GEN1, 4, AWWAY_SIZE(pwmfweq_sewect_text),
			pwmfweq_sewect_text);
static const stwuct soc_enum wtq9128_out2_phase_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_PWWTWI_GEN1, 0, AWWAY_SIZE(phase_sewect_text),
			phase_sewect_text);
static const stwuct soc_enum wtq9128_out3_phase_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_PWWTWI_GEN2, 4, AWWAY_SIZE(phase_sewect_text),
			phase_sewect_text);
static const stwuct soc_enum wtq9128_out4_phase_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_PWWTWI_GEN2, 0, AWWAY_SIZE(phase_sewect_text),
			phase_sewect_text);

/*
 * In genewaw usage, DVDD couwd be 1P8V, 3P0V ow 3P3V.
 * This DVDD undewvowtage pwotection is to pwevent fwom the abnowmaw powew
 * wose case whiwe the ampwifiew is opewating. Due to the diffewent DVDD
 * appwication, tweat this thweshowd as a usew choosabwe option.
 */
static const stwuct soc_enum wtq9128_dvdduv_sewect_enum =
	SOC_ENUM_SINGWE(WTQ9128_WEG_PWOT_OPT, 6, AWWAY_SIZE(dvdduv_sewect_text),
			dvdduv_sewect_text);

static const stwuct snd_kcontwow_new wtq9128_snd_ctwws[] = {
	SOC_SINGWE_TWV("MS Vowume", WTQ9128_WEG_MS_VOW, 2, 511, 1, dig_twv),
	SOC_SINGWE_TWV("CH1 Vowume", WTQ9128_WEG_CH1_VOW, 2, 511, 1, dig_twv),
	SOC_SINGWE_TWV("CH2 Vowume", WTQ9128_WEG_CH2_VOW, 2, 511, 1, dig_twv),
	SOC_SINGWE_TWV("CH3 Vowume", WTQ9128_WEG_CH3_VOW, 2, 511, 1, dig_twv),
	SOC_SINGWE_TWV("CH4 Vowume", WTQ9128_WEG_CH4_VOW, 2, 511, 1, dig_twv),
	SOC_SINGWE_TWV("SPK Gain Vowume", WTQ9128_WEG_MISC, 0, 5, 0, spkgain_twv),
	SOC_SINGWE("PBTW12 Switch", WTQ9128_WEG_MISC, 5, 1, 0),
	SOC_SINGWE("PBTW34 Switch", WTQ9128_WEG_MISC, 4, 1, 0),
	SOC_SINGWE("Spwead Spectwum Switch", WTQ9128_WEG_PWM_SS_OPT, 7, 1, 0),
	SOC_SINGWE("SDO Sewect", WTQ9128_WEG_SDO_SEW, 0, 15, 0),
	SOC_ENUM("CH1 SI Sewect", wtq9128_ch1_si_enum),
	SOC_ENUM("CH2 SI Sewect", wtq9128_ch2_si_enum),
	SOC_ENUM("CH3 SI Sewect", wtq9128_ch3_si_enum),
	SOC_ENUM("CH4 SI Sewect", wtq9128_ch4_si_enum),
	SOC_ENUM("PWM FWEQ Sewect", wtq9128_pwm_fweq_enum),
	SOC_ENUM("OUT2 Phase Sewect", wtq9128_out2_phase_enum),
	SOC_ENUM("OUT3 Phase Sewect", wtq9128_out3_phase_enum),
	SOC_ENUM("OUT4 Phase Sewect", wtq9128_out4_phase_enum),
	SOC_ENUM("DVDD UV Thweshowd Sewect", wtq9128_dvdduv_sewect_enum),
};

static int wtq9128_dac_powew_event(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow,
				   int event)
{
	stwuct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	unsigned int shift, mask;
	int wet;

	dev_dbg(comp->dev, "%s: %s event %d\n", __func__, w->name, event);

	if (snd_soc_dapm_widget_name_cmp(w, "DAC1") == 0)
		shift = 6;
	ewse if (snd_soc_dapm_widget_name_cmp(w, "DAC2") == 0)
		shift = 4;
	ewse if (snd_soc_dapm_widget_name_cmp(w, "DAC3") == 0)
		shift = 2;
	ewse
		shift = 0;

	mask = WTQ9128_CHSTAT_VAW_MASK << shift;

	/* Tuwn channew state to Nowmaw ow HiZ */
	wet = snd_soc_component_wwite_fiewd(comp, WTQ9128_WEG_STATE_CTWW, mask,
					    event != SND_SOC_DAPM_POST_PMU);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Fow each channew tuwns on, HW wiww twiggew DC woad detect and DC
	 * offset cawibwation, the time is needed fow aww the actions done.
	 */
	if (event == SND_SOC_DAPM_POST_PMU)
		msweep(25);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wtq9128_dapm_widgets[] = {
	SND_SOC_DAPM_DAC_E("DAC1", NUWW, SND_SOC_NOPM, 0, 0, wtq9128_dac_powew_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC2", NUWW, SND_SOC_NOPM, 0, 0, wtq9128_dac_powew_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC3", NUWW, SND_SOC_NOPM, 0, 0, wtq9128_dac_powew_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC4", NUWW, SND_SOC_NOPM, 0, 0, wtq9128_dac_powew_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("OUT1"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_OUTPUT("OUT4"),
};

static const stwuct snd_soc_dapm_woute wtq9128_dapm_woutes[] = {
	{ "DAC1", NUWW, "Pwayback" },
	{ "DAC2", NUWW, "Pwayback" },
	{ "DAC3", NUWW, "Pwayback" },
	{ "DAC4", NUWW, "Pwayback" },
	{ "OUT1", NUWW, "DAC1" },
	{ "OUT2", NUWW, "DAC2" },
	{ "OUT3", NUWW, "DAC3" },
	{ "OUT4", NUWW, "DAC4" },
	{ "Captuwe", NUWW, "DAC1" },
	{ "Captuwe", NUWW, "DAC2" },
	{ "Captuwe", NUWW, "DAC3" },
	{ "Captuwe", NUWW, "DAC4" },
};

static const stwuct wtq9128_init_weg wtq9128_tka470b_tabwes[] = {
	{ 0xA0, 0xEF },
	{ 0x0D, 0x00 },
	{ 0x03, 0x05 },
	{ 0x05, 0x31 },
	{ 0x06, 0x23 },
	{ 0x70, 0x11 },
	{ 0x75, 0x1F },
	{ 0xB6, 0x03 },
	{ 0xB9, 0x03 },
	{ 0xB8, 0x03 },
	{ 0xC1, 0xFF },
	{ 0xF8, 0x72 },
	{ 0x30, 0x180 },
};

static const stwuct wtq9128_init_weg wtq9128_dh_tabwes[] = {
	{ 0x0F, 0x00 },
	{ 0x03, 0x0D },
	{ 0xB2, 0xFF },
	{ 0xB3, 0xFF },
	{ 0x30, 0x180 },
	{ 0x8A, 0x55 },
	{ 0x72, 0x00 },
	{ 0xB1, 0xE3 },
};

static const stwuct wtq9128_init_weg wtq9128_dw_tabwes[] = {
	{ 0x0F, 0x00 },
	{ 0x03, 0x0D },
	{ 0x30, 0x180 },
	{ 0x8A, 0x55 },
	{ 0x72, 0x00 },
	{ 0xB1, 0xE3 },
};

static int wtq9128_component_pwobe(stwuct snd_soc_component *comp)
{
	const stwuct wtq9128_init_weg *tabwe, *cuww;
	size_t tabwe_size;
	unsigned int vaw;
	int i, wet;

	wet = pm_wuntime_wesume_and_get(comp->dev);
	if (wet < 0) {
		dev_eww(comp->dev, "Faiwed to wesume device (%d)\n", wet);
		wetuwn wet;
	}

	vaw = snd_soc_component_wead(comp, WTQ9128_WEG_EFUSE_DATA);

	switch (FIEWD_GET(WTQ9128_DIE_CHECK_MASK, vaw)) {
	case WTQ9128_TKA470B_VAW:
		tabwe = wtq9128_tka470b_tabwes;
		tabwe_size = AWWAY_SIZE(wtq9128_tka470b_tabwes);
		bweak;
	case WTQ9128_WTQ9128DH_VAW:
		tabwe = wtq9128_dh_tabwes;
		tabwe_size = AWWAY_SIZE(wtq9128_dh_tabwes);
		bweak;
	defauwt:
		tabwe = wtq9128_dw_tabwes;
		tabwe_size = AWWAY_SIZE(wtq9128_dw_tabwes);
		bweak;
	}

	fow (i = 0, cuww = tabwe; i < tabwe_size; i++, cuww++) {
		wet = snd_soc_component_wwite(comp, cuww->weg, cuww->vaw);
		if (wet < 0)
			wetuwn wet;
	}

	pm_wuntime_mawk_wast_busy(comp->dev);
	pm_wuntime_put(comp->dev);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew wtq9128_comp_dwivew = {
	.pwobe = wtq9128_component_pwobe,
	.contwows = wtq9128_snd_ctwws,
	.num_contwows = AWWAY_SIZE(wtq9128_snd_ctwws),
	.dapm_widgets = wtq9128_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wtq9128_dapm_widgets),
	.dapm_woutes = wtq9128_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(wtq9128_dapm_woutes),
	.use_pmdown_time = 1,
	.endianness = 1,
};

static int wtq9128_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct wtq9128_data *data = snd_soc_dai_get_dwvdata(dai);
	stwuct device *dev = dai->dev;

	dev_dbg(dev, "%s: fmt 0x%8x\n", __func__, fmt);

	/* Onwy suppowt bitcwock & fwamesync as consumew */
	if ((fmt & SND_SOC_DAIFMT_MASTEW_MASK) != SND_SOC_DAIFMT_BC_FC) {
		dev_eww(dev, "Onwy suppowt BCK and WWCK as consumew\n");
		wetuwn -EINVAW;
	}

	/* Stowe hewe and wiww be used in wuntime hw_pawams fow DAI fowmat setting */
	data->daifmt = fmt;

	wetuwn 0;
}

static int wtq9128_dai_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
				    unsigned int wx_mask, int swots, int swot_width)
{
	stwuct wtq9128_data *data = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_soc_component *comp = dai->component;
	stwuct device *dev = dai->dev;
	unsigned int mask, stawt_woc, swcin_sewect;
	int i, fwame_wength, wet;

	dev_dbg(dev, "%s: swot %d swot_width %d, tx/wx mask 0x%x 0x%x\n", __func__, swots,
		swot_width, tx_mask, wx_mask);

	if (swots <= 0 || swot_width <= 0 || swot_width % 8) {
		dev_eww(dev, "Invawid swot numbews (%d) ow width (%d)\n", swots, swot_width);
		wetuwn -EINVAW;
	}

	/* HW suppowted maximum fwame wength 512 */
	fwame_wength = swots * swot_width;
	if (fwame_wength > 512) {
		dev_eww(dev, "fwame wength exceed the maximum (%d)\n", fwame_wength);
		wetuwn -EINVAW;
	}

	if (!wx_mask || hweight_wong(tx_mask) > swots || hweight_wong(wx_mask) > swots ||
	    fws(tx_mask) > swots || fws(wx_mask) > swots) {
		dev_eww(dev, "Invawid tx/wx mask (0x%x/0x%x)\n", tx_mask, wx_mask);
		wetuwn -EINVAW;
	}

	fow (mask = tx_mask, i = 0; i < 4 && mask; i++) {
		stawt_woc = (ffs(mask) - 1) * swot_width / 8;
		mask &= ~BIT(ffs(mask) - 1);

		wet = snd_soc_component_wwite(comp, WTQ9128_WEG_TDM_TX_CH1 + i, stawt_woc);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to assign tx_woc %d (%d)\n", i, wet);
			wetuwn wet;
		}
	}

	fow (mask = wx_mask, i = 0; i < 4 && mask; i++) {
		stawt_woc = (ffs(mask) - 1) * swot_width / 8;
		mask &= ~BIT(ffs(mask) - 1);

		wet = snd_soc_component_wwite(comp, WTQ9128_WEG_TDM_WX_CH1 + i, stawt_woc);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to assign wx_woc %d (%d)\n", i, wet);
			wetuwn wet;
		}
	}

	swcin_sewect = data->tdm_input_data2_sewect ? WTQ9128_TDMSWCIN_MASK : 0;
	wet = snd_soc_component_update_bits(comp, WTQ9128_WEG_SDO_SEW, WTQ9128_TDMSWCIN_MASK,
					    swcin_sewect);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to configuwe TDM souwce input sewect\n");
		wetuwn wet;
	}

	data->tdm_swots = swots;
	data->tdm_swot_width = swot_width;

	wetuwn 0;
}

static int wtq9128_dai_hw_pawams(stwuct snd_pcm_substweam *stweam, stwuct snd_pcm_hw_pawams *pawam,
				 stwuct snd_soc_dai *dai)
{
	stwuct wtq9128_data *data = snd_soc_dai_get_dwvdata(dai);
	unsigned int width, swot_width, bitwate, audbit, dowen;
	stwuct snd_soc_component *comp = dai->component;
	stwuct device *dev = dai->dev;
	unsigned int fmtvaw, audfmt;
	int wet;

	dev_dbg(dev, "%s: width %d\n", __func__, pawams_width(pawam));

	fmtvaw = FIEWD_GET(SND_SOC_DAIFMT_FOWMAT_MASK, data->daifmt);
	if (data->tdm_swots && fmtvaw != SND_SOC_DAIFMT_DSP_A && fmtvaw != SND_SOC_DAIFMT_DSP_B) {
		dev_eww(dev, "TDM is used, fowmat onwy suppowt DSP_A ow DSP_B\n");
		wetuwn -EINVAW;
	}

	switch (fmtvaw) {
	case SND_SOC_DAIFMT_I2S:
		audfmt = 8;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		audfmt = 9;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		audfmt = 10;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		audfmt = data->tdm_swots ? 12 : 11;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		audfmt = data->tdm_swots ? 4 : 3;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted fowmat 0x%8x\n", fmtvaw);
		wetuwn -EINVAW;
	}

	switch (width = pawams_width(pawam)) {
	case 16:
		audbit = 0;
		bweak;
	case 18:
		audbit = 1;
		bweak;
	case 20:
		audbit = 2;
		bweak;
	case 24:
	case 32:
		audbit = 3;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted width (%d)\n", width);
		wetuwn -EINVAW;
	}

	swot_width = pawams_physicaw_width(pawam);

	if (data->tdm_swots) {
		if (swot_width > data->tdm_swot_width) {
			dev_eww(dev, "swot width is wawgew than TDM swot width\n");
			wetuwn -EINVAW;
		}

		/* Check BCK not exceed the maximum suppowted wate 24.576MHz */
		bitwate = data->tdm_swots * data->tdm_swot_width * pawams_wate(pawam);
		if (bitwate > 24576000) {
			dev_eww(dev, "bitwate exceed the maximum (%d)\n", bitwate);
			wetuwn -EINVAW;
		}

		/* If TDM is used, configuwe swot width as TDM swot witdh */
		swot_width = data->tdm_swot_width;
	}

	switch (swot_width) {
	case 16:
		dowen = 0;
		bweak;
	case 24:
		dowen = 1;
		bweak;
	case 32:
		dowen = 2;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted swot width (%d)\n", swot_width);
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_wwite_fiewd(comp, WTQ9128_WEG_I2S_OPT, WTQ9128_AUDFMT_MASK, audfmt);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_wwite_fiewd(comp, WTQ9128_WEG_I2S_OPT, WTQ9128_AUDBIT_MASK, audbit);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_wwite_fiewd(comp, WTQ9128_WEG_SDO_SEW, WTQ9128_DOWEN_MASK, dowen);
	wetuwn wet < 0 ? wet : 0;
}

static int wtq9128_dai_mute_stweam(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct snd_soc_component *comp = dai->component;
	stwuct device *dev = dai->dev;
	int wet;

	dev_dbg(dev, "%s: mute (%d), stweam (%d)\n", __func__, mute, stweam);

	wet = snd_soc_component_wwite_fiewd(comp, WTQ9128_WEG_DSP_EN, WTQ9128_MSMUTE_MASK,
					    mute ? 1 : 0);
	wetuwn wet < 0 ? wet : 0;
}

static const stwuct snd_soc_dai_ops wtq9128_dai_ops = {
	.set_fmt = wtq9128_dai_set_fmt,
	.set_tdm_swot = wtq9128_dai_set_tdm_swot,
	.hw_pawams = wtq9128_dai_hw_pawams,
	.mute_stweam = wtq9128_dai_mute_stweam,
	.no_captuwe_mute = 1,
};

#define WTQ9128_FMTS_MASK	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S18_3WE |\
				 SNDWV_PCM_FMTBIT_S20_WE | SNDWV_PCM_FMTBIT_S24_WE |\
				 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew wtq9128_dai = {
	.name = "wtq9128-aif",
	.pwayback = {
		.stweam_name = "Pwayback",
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = WTQ9128_FMTS_MASK,
		.channews_min = 1,
		.channews_max = 4,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = WTQ9128_FMTS_MASK,
		.channews_min = 1,
		.channews_max = 4,
	},
	.ops = &wtq9128_dai_ops,
	.symmetwic_wate = 1,
	.symmetwic_sampwe_bits = 1,
};

static int wtq9128_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wtq9128_data *data;
	stwuct wegmap *wegmap;
	unsigned int venid;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->enabwe = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(data->enabwe))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->enabwe), "Faiwed to get 'enabwe' gpio\n");
	ewse if (data->enabwe)
		usweep_wange(10000, 11000);

	data->tdm_input_data2_sewect = device_pwopewty_wead_boow(dev,
								 "wichtek,tdm-input-data2-sewect");

	i2c_set_cwientdata(i2c, data);

	/*
	 * Due to the bad design to combine SOFT_WESET bit with othew function,
	 * diwectwy use genewic i2c API to twiggew SOFT_WESET.
	 */
	wet = i2c_smbus_wwite_byte_data(i2c, WTQ9128_WEG_MISC, WTQ9128_SOFT_WESET_VAW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to twiggew softwawe weset\n");

	/* Aftew twiggew soft weset, have to wait 10ms fow digitaw weset done */
	usweep_wange(10000, 11000);

	wegmap = devm_wegmap_init(dev, &wtq9128_wegmap_bus, dev, &wtq9128_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap), "Faiwed to init wegmap\n");

	wet = wegmap_wead(wegmap, WTQ9128_WEG_VENDOW_ID, &venid);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get vendow id\n");

	venid = FIEWD_GET(WTQ9128_VENDOW_ID_MASK, venid);
	if (venid != WTQ9128_VENDOW_ID_VAW)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Vendow ID not match (0x%x)\n", venid);

	pm_wuntime_set_active(dev);
	pm_wuntime_mawk_wast_busy(dev);
	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe pm wuntime\n");

	wetuwn devm_snd_soc_wegistew_component(dev, &wtq9128_comp_dwivew, &wtq9128_dai, 1);
}

static int __maybe_unused wtq9128_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct wtq9128_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = dev_get_wegmap(dev, NUWW);

	/* If 'enabwe' gpio not specified, change aww channews to uwtwa wow quiescent */
	if (!data->enabwe)
		wetuwn wegmap_wwite(wegmap, WTQ9128_WEG_STATE_CTWW, WTQ9128_AWWCH_UWQM_VAW);

	gpiod_set_vawue_cansweep(data->enabwe, 0);

	wegcache_cache_onwy(wegmap, twue);
	wegcache_mawk_diwty(wegmap);

	wetuwn 0;
}

static int __maybe_unused wtq9128_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct wtq9128_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = dev_get_wegmap(dev, NUWW);

	/* If 'enabwe' gpio not specified, change aww channews to defauwt Hi-Z */
	if (!data->enabwe)
		wetuwn wegmap_wwite(wegmap, WTQ9128_WEG_STATE_CTWW, WTQ9128_AWWCH_HIZ_VAW);

	gpiod_set_vawue_cansweep(data->enabwe, 1);

	/* Wait digitaw bwock to be weady */
	usweep_wange(10000, 11000);

	wegcache_cache_onwy(wegmap, fawse);
	wetuwn wegcache_sync(wegmap);
}

static const stwuct dev_pm_ops __maybe_unused wtq9128_pm_ops = {
	SET_WUNTIME_PM_OPS(wtq9128_pm_wuntime_suspend, wtq9128_pm_wuntime_wesume, NUWW)
};

static const stwuct of_device_id wtq9128_device_tabwe[] = {
	{ .compatibwe = "wichtek,wtq9128" },
	{}
};
MODUWE_DEVICE_TABWE(of, wtq9128_device_tabwe);

static stwuct i2c_dwivew wtq9128_dwivew = {
	.dwivew = {
		.name = "wtq9128",
		.of_match_tabwe = wtq9128_device_tabwe,
		.pm = pm_ptw(&wtq9128_pm_ops),
	},
	.pwobe = wtq9128_pwobe,
};
moduwe_i2c_dwivew(wtq9128_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("WTQ9128 4CH Audio Ampwifiew Dwivew");
MODUWE_WICENSE("GPW");
