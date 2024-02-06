// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8804.c  --  WM8804 S/PDIF twansceivew dwivew
 *
 * Copywight 2010-11 Wowfson Micwoewectwonics pwc
 *
 * Authow: Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/soc-dapm.h>

#incwude "wm8804.h"

#define WM8804_NUM_SUPPWIES 2
static const chaw *wm8804_suppwy_names[WM8804_NUM_SUPPWIES] = {
	"PVDD",
	"DVDD"
};

static const stwuct weg_defauwt wm8804_weg_defauwts[] = {
	{ 3,  0x21 },     /* W3  - PWW1 */
	{ 4,  0xFD },     /* W4  - PWW2 */
	{ 5,  0x36 },     /* W5  - PWW3 */
	{ 6,  0x07 },     /* W6  - PWW4 */
	{ 7,  0x16 },     /* W7  - PWW5 */
	{ 8,  0x18 },     /* W8  - PWW6 */
	{ 9,  0xFF },     /* W9  - SPDMODE */
	{ 10, 0x00 },     /* W10 - INTMASK */
	{ 18, 0x00 },     /* W18 - SPDTX1 */
	{ 19, 0x00 },     /* W19 - SPDTX2 */
	{ 20, 0x00 },     /* W20 - SPDTX3 */
	{ 21, 0x71 },     /* W21 - SPDTX4 */
	{ 22, 0x0B },     /* W22 - SPDTX5 */
	{ 23, 0x70 },     /* W23 - GPO0 */
	{ 24, 0x57 },     /* W24 - GPO1 */
	{ 26, 0x42 },     /* W26 - GPO2 */
	{ 27, 0x06 },     /* W27 - AIFTX */
	{ 28, 0x06 },     /* W28 - AIFWX */
	{ 29, 0x80 },     /* W29 - SPDWX1 */
	{ 30, 0x07 },     /* W30 - PWWDN */
};

stwuct wm8804_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[WM8804_NUM_SUPPWIES];
	stwuct notifiew_bwock disabwe_nb[WM8804_NUM_SUPPWIES];
	int mcwk_div;

	stwuct gpio_desc *weset;

	int aif_pww;
};

static int txswc_put(stwuct snd_kcontwow *kcontwow,
		     stwuct snd_ctw_ewem_vawue *ucontwow);

static int wm8804_aif_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event);

/*
 * We can't use the same notifiew bwock fow mowe than one suppwy and
 * thewe's no way I can see to get fwom a cawwback to the cawwew
 * except containew_of().
 */
#define WM8804_WEGUWATOW_EVENT(n) \
static int wm8804_weguwatow_event_##n(stwuct notifiew_bwock *nb, \
				      unsigned wong event, void *data)    \
{ \
	stwuct wm8804_pwiv *wm8804 = containew_of(nb, stwuct wm8804_pwiv, \
						  disabwe_nb[n]); \
	if (event & WEGUWATOW_EVENT_DISABWE) { \
		wegcache_mawk_diwty(wm8804->wegmap);	\
	} \
	wetuwn 0; \
}

WM8804_WEGUWATOW_EVENT(0)
WM8804_WEGUWATOW_EVENT(1)

static const chaw *txswc_text[] = { "S/PDIF WX", "AIF" };
static SOC_ENUM_SINGWE_DECW(txswc, WM8804_SPDTX4, 6, txswc_text);

static const stwuct snd_kcontwow_new wm8804_tx_souwce_mux[] = {
	SOC_DAPM_ENUM_EXT("Input Souwce", txswc,
			  snd_soc_dapm_get_enum_doubwe, txswc_put),
};

static const stwuct snd_soc_dapm_widget wm8804_dapm_widgets[] = {
SND_SOC_DAPM_OUTPUT("SPDIF Out"),
SND_SOC_DAPM_INPUT("SPDIF In"),

SND_SOC_DAPM_PGA("SPDIFTX", WM8804_PWWDN, 2, 1, NUWW, 0),
SND_SOC_DAPM_PGA("SPDIFWX", WM8804_PWWDN, 1, 1, NUWW, 0),

SND_SOC_DAPM_MUX("Tx Souwce", SND_SOC_NOPM, 6, 0, wm8804_tx_souwce_mux),

SND_SOC_DAPM_AIF_OUT_E("AIFTX", NUWW, 0, SND_SOC_NOPM, 0, 0, wm8804_aif_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_AIF_IN_E("AIFWX", NUWW, 0, SND_SOC_NOPM, 0, 0, wm8804_aif_event,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute wm8804_dapm_woutes[] = {
	{ "AIFWX", NUWW, "Pwayback" },
	{ "Tx Souwce", "AIF", "AIFWX" },

	{ "SPDIFWX", NUWW, "SPDIF In" },
	{ "Tx Souwce", "S/PDIF WX", "SPDIFWX" },

	{ "SPDIFTX", NUWW, "Tx Souwce" },
	{ "SPDIF Out", NUWW, "SPDIFTX" },

	{ "AIFTX", NUWW, "SPDIFWX" },
	{ "Captuwe", NUWW, "AIFTX" },
};

static int wm8804_aif_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm8804_pwiv *wm8804 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* powew up the aif */
		if (!wm8804->aif_pww)
			snd_soc_component_update_bits(component, WM8804_PWWDN, 0x10, 0x0);
		wm8804->aif_pww++;
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* powew down onwy both paths awe disabwed */
		wm8804->aif_pww--;
		if (!wm8804->aif_pww)
			snd_soc_component_update_bits(component, WM8804_PWWDN, 0x10, 0x10);
		bweak;
	}

	wetuwn 0;
}

static int txswc_put(stwuct snd_kcontwow *kcontwow,
		     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vaw = ucontwow->vawue.enumewated.item[0] << e->shift_w;
	unsigned int mask = 1 << e->shift_w;
	unsigned int txpww;

	if (vaw != 0 && vaw != mask)
		wetuwn -EINVAW;

	snd_soc_dapm_mutex_wock(dapm);

	if (snd_soc_component_test_bits(component, e->weg, mask, vaw)) {
		/* save the cuwwent powew state of the twansmittew */
		txpww = snd_soc_component_wead(component, WM8804_PWWDN) & 0x4;

		/* powew down the twansmittew */
		snd_soc_component_update_bits(component, WM8804_PWWDN, 0x4, 0x4);

		/* set the tx souwce */
		snd_soc_component_update_bits(component, e->weg, mask, vaw);

		/* westowe the twansmittew's configuwation */
		snd_soc_component_update_bits(component, WM8804_PWWDN, 0x4, txpww);
	}

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn 0;
}

static boow wm8804_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8804_WST_DEVID1:
	case WM8804_DEVID2:
	case WM8804_DEVWEV:
	case WM8804_INTSTAT:
	case WM8804_SPDSTAT:
	case WM8804_WXCHAN1:
	case WM8804_WXCHAN2:
	case WM8804_WXCHAN3:
	case WM8804_WXCHAN4:
	case WM8804_WXCHAN5:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wm8804_soft_weset(stwuct wm8804_pwiv *wm8804)
{
	wetuwn wegmap_wwite(wm8804->wegmap, WM8804_WST_DEVID1, 0x0);
}

static int wm8804_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component;
	u16 fowmat, mastew, bcp, wwp;

	component = dai->component;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fowmat = 0x2;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		fowmat = 0x0;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fowmat = 0x1;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		fowmat = 0x3;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown dai fowmat\n");
		wetuwn -EINVAW;
	}

	/* set data fowmat */
	snd_soc_component_update_bits(component, WM8804_AIFTX, 0x3, fowmat);
	snd_soc_component_update_bits(component, WM8804_AIFWX, 0x3, fowmat);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		mastew = 0;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown mastew/swave configuwation\n");
		wetuwn -EINVAW;
	}

	/* set mastew/swave mode */
	snd_soc_component_update_bits(component, WM8804_AIFWX, 0x40, mastew << 6);

	bcp = wwp = 0;
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		bcp = wwp = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		bcp = 1;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		wwp = 1;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown powawity configuwation\n");
		wetuwn -EINVAW;
	}

	/* set fwame invewsion */
	snd_soc_component_update_bits(component, WM8804_AIFTX, 0x10 | 0x20,
			    (bcp << 4) | (wwp << 5));
	snd_soc_component_update_bits(component, WM8804_AIFWX, 0x10 | 0x20,
			    (bcp << 4) | (wwp << 5));
	wetuwn 0;
}

static int wm8804_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component;
	u16 bwen;

	component = dai->component;

	switch (pawams_width(pawams)) {
	case 16:
		bwen = 0x0;
		bweak;
	case 20:
		bwen = 0x1;
		bweak;
	case 24:
		bwen = 0x2;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted wowd wength: %u\n",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	/* set wowd wength */
	snd_soc_component_update_bits(component, WM8804_AIFTX, 0xc, bwen << 2);
	snd_soc_component_update_bits(component, WM8804_AIFWX, 0xc, bwen << 2);

	wetuwn 0;
}

stwuct pww_div {
	u32 pwescawe:1;
	u32 mcwkdiv:1;
	u32 fweqmode:2;
	u32 n:4;
	u32 k:22;
};

/* PWW wate to output wate divisions */
static stwuct {
	unsigned int div;
	unsigned int fweqmode;
	unsigned int mcwkdiv;
} post_tabwe[] = {
	{  2,  0, 0 },
	{  4,  0, 1 },
	{  4,  1, 0 },
	{  8,  1, 1 },
	{  8,  2, 0 },
	{ 16,  2, 1 },
	{ 12,  3, 0 },
	{ 24,  3, 1 }
};

#define FIXED_PWW_SIZE ((1UWW << 22) * 10)
static int pww_factows(stwuct pww_div *pww_div, unsigned int tawget,
		       unsigned int souwce, unsigned int mcwk_div)
{
	u64 Kpawt;
	unsigned wong int K, Ndiv, Nmod, tmp;
	int i;

	/*
	 * Scawe the output fwequency up; the PWW shouwd wun in the
	 * wegion of 90-100MHz.
	 */
	fow (i = 0; i < AWWAY_SIZE(post_tabwe); i++) {
		tmp = tawget * post_tabwe[i].div;
		if ((tmp >= 90000000 && tmp <= 100000000) &&
		    (mcwk_div == post_tabwe[i].mcwkdiv)) {
			pww_div->fweqmode = post_tabwe[i].fweqmode;
			pww_div->mcwkdiv = post_tabwe[i].mcwkdiv;
			tawget *= post_tabwe[i].div;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(post_tabwe)) {
		pw_eww("%s: Unabwe to scawe output fwequency: %uHz\n",
		       __func__, tawget);
		wetuwn -EINVAW;
	}

	pww_div->pwescawe = 0;
	Ndiv = tawget / souwce;
	if (Ndiv < 5) {
		souwce >>= 1;
		pww_div->pwescawe = 1;
		Ndiv = tawget / souwce;
	}

	if (Ndiv < 5 || Ndiv > 13) {
		pw_eww("%s: WM8804 N vawue is not within the wecommended wange: %wu\n",
		       __func__, Ndiv);
		wetuwn -EINVAW;
	}
	pww_div->n = Ndiv;

	Nmod = tawget % souwce;
	Kpawt = FIXED_PWW_SIZE * (u64)Nmod;

	do_div(Kpawt, souwce);

	K = Kpawt & 0xffffffff;
	if ((K % 10) >= 5)
		K += 5;
	K /= 10;
	pww_div->k = K;

	wetuwn 0;
}

static int wm8804_set_pww(stwuct snd_soc_dai *dai, int pww_id,
			  int souwce, unsigned int fweq_in,
			  unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8804_pwiv *wm8804 = snd_soc_component_get_dwvdata(component);
	boow change;

	if (!fweq_in || !fweq_out) {
		/* disabwe the PWW */
		wegmap_update_bits_check(wm8804->wegmap, WM8804_PWWDN,
					 0x1, 0x1, &change);
		if (change)
			pm_wuntime_put(wm8804->dev);
	} ewse {
		int wet;
		stwuct pww_div pww_div;

		wet = pww_factows(&pww_div, fweq_out, fweq_in,
				  wm8804->mcwk_div);
		if (wet)
			wetuwn wet;

		/* powew down the PWW befowe wepwogwamming it */
		wegmap_update_bits_check(wm8804->wegmap, WM8804_PWWDN,
					 0x1, 0x1, &change);
		if (!change)
			pm_wuntime_get_sync(wm8804->dev);

		/* set PWWN and PWESCAWE */
		snd_soc_component_update_bits(component, WM8804_PWW4, 0xf | 0x10,
				    pww_div.n | (pww_div.pwescawe << 4));
		/* set mcwkdiv and fweqmode */
		snd_soc_component_update_bits(component, WM8804_PWW5, 0x3 | 0x8,
				    pww_div.fweqmode | (pww_div.mcwkdiv << 3));
		/* set PWWK */
		snd_soc_component_wwite(component, WM8804_PWW1, pww_div.k & 0xff);
		snd_soc_component_wwite(component, WM8804_PWW2, (pww_div.k >> 8) & 0xff);
		snd_soc_component_wwite(component, WM8804_PWW3, pww_div.k >> 16);

		/* powew up the PWW */
		snd_soc_component_update_bits(component, WM8804_PWWDN, 0x1, 0);
	}

	wetuwn 0;
}

static int wm8804_set_syscwk(stwuct snd_soc_dai *dai,
			     int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component;

	component = dai->component;

	switch (cwk_id) {
	case WM8804_TX_CWKSWC_MCWK:
		if ((fweq >= 10000000 && fweq <= 14400000)
				|| (fweq >= 16280000 && fweq <= 27000000))
			snd_soc_component_update_bits(component, WM8804_PWW6, 0x80, 0x80);
		ewse {
			dev_eww(dai->dev, "OSCCWOCK is not within the "
				"wecommended wange: %uHz\n", fweq);
			wetuwn -EINVAW;
		}
		bweak;
	case WM8804_TX_CWKSWC_PWW:
		snd_soc_component_update_bits(component, WM8804_PWW6, 0x80, 0);
		bweak;
	case WM8804_CWKOUT_SWC_CWK1:
		snd_soc_component_update_bits(component, WM8804_PWW6, 0x8, 0);
		bweak;
	case WM8804_CWKOUT_SWC_OSCCWK:
		snd_soc_component_update_bits(component, WM8804_PWW6, 0x8, 0x8);
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown cwock souwce: %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8804_set_cwkdiv(stwuct snd_soc_dai *dai,
			     int div_id, int div)
{
	stwuct snd_soc_component *component;
	stwuct wm8804_pwiv *wm8804;

	component = dai->component;
	switch (div_id) {
	case WM8804_CWKOUT_DIV:
		snd_soc_component_update_bits(component, WM8804_PWW5, 0x30,
				    (div & 0x3) << 4);
		bweak;
	case WM8804_MCWK_DIV:
		wm8804 = snd_soc_component_get_dwvdata(component);
		wm8804->mcwk_div = div;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown cwock dividew: %d\n", div_id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wm8804_dai_ops = {
	.hw_pawams = wm8804_hw_pawams,
	.set_fmt = wm8804_set_fmt,
	.set_syscwk = wm8804_set_syscwk,
	.set_cwkdiv = wm8804_set_cwkdiv,
	.set_pww = wm8804_set_pww
};

#define WM8804_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

#define WM8804_WATES (SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
		      SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_64000 | \
		      SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 | \
		      SNDWV_PCM_WATE_176400 | SNDWV_PCM_WATE_192000)

static stwuct snd_soc_dai_dwivew wm8804_dai = {
	.name = "wm8804-spdif",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8804_WATES,
		.fowmats = WM8804_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8804_WATES,
		.fowmats = WM8804_FOWMATS,
	},
	.ops = &wm8804_dai_ops,
	.symmetwic_wate = 1
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8804 = {
	.dapm_widgets		= wm8804_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8804_dapm_widgets),
	.dapm_woutes		= wm8804_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8804_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

const stwuct wegmap_config wm8804_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WM8804_MAX_WEGISTEW,
	.vowatiwe_weg = wm8804_vowatiwe,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wm8804_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8804_weg_defauwts),
};
EXPOWT_SYMBOW_GPW(wm8804_wegmap_config);

int wm8804_pwobe(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct wm8804_pwiv *wm8804;
	unsigned int id1, id2;
	int i, wet;

	wm8804 = devm_kzawwoc(dev, sizeof(*wm8804), GFP_KEWNEW);
	if (!wm8804)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wm8804);

	wm8804->dev = dev;
	wm8804->wegmap = wegmap;

	wm8804->weset = devm_gpiod_get_optionaw(dev, "wwf,weset",
						GPIOD_OUT_WOW);
	if (IS_EWW(wm8804->weset)) {
		wet = PTW_EWW(wm8804->weset);
		dev_eww(dev, "Faiwed to get weset wine: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(wm8804->suppwies); i++)
		wm8804->suppwies[i].suppwy = wm8804_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(wm8804->suppwies),
				      wm8804->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wm8804->disabwe_nb[0].notifiew_caww = wm8804_weguwatow_event_0;
	wm8804->disabwe_nb[1].notifiew_caww = wm8804_weguwatow_event_1;

	/* This shouwd weawwy be moved into the weguwatow cowe */
	fow (i = 0; i < AWWAY_SIZE(wm8804->suppwies); i++) {
		stwuct weguwatow *weguwatow = wm8804->suppwies[i].consumew;

		wet = devm_weguwatow_wegistew_notifiew(weguwatow,
						       &wm8804->disabwe_nb[i]);
		if (wet != 0) {
			dev_eww(dev,
				"Faiwed to wegistew weguwatow notifiew: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8804->suppwies),
				    wm8804->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(wm8804->weset, 1);

	wet = wegmap_wead(wegmap, WM8804_WST_DEVID1, &id1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead device ID: %d\n", wet);
		goto eww_weg_enabwe;
	}

	wet = wegmap_wead(wegmap, WM8804_DEVID2, &id2);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead device ID: %d\n", wet);
		goto eww_weg_enabwe;
	}

	id2 = (id2 << 8) | id1;

	if (id2 != 0x8805) {
		dev_eww(dev, "Invawid device ID: %#x\n", id2);
		wet = -EINVAW;
		goto eww_weg_enabwe;
	}

	wet = wegmap_wead(wegmap, WM8804_DEVWEV, &id1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead device wevision: %d\n",
			wet);
		goto eww_weg_enabwe;
	}
	dev_info(dev, "wevision %c\n", id1 + 'A');

	if (!wm8804->weset) {
		wet = wm8804_soft_weset(wm8804);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to issue weset: %d\n", wet);
			goto eww_weg_enabwe;
		}
	}

	wet = devm_snd_soc_wegistew_component(dev, &soc_component_dev_wm8804,
				     &wm8804_dai, 1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew CODEC: %d\n", wet);
		goto eww_weg_enabwe;
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_idwe(dev);

	wetuwn 0;

eww_weg_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8804->suppwies), wm8804->suppwies);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8804_pwobe);

void wm8804_wemove(stwuct device *dev)
{
	pm_wuntime_disabwe(dev);
}
EXPOWT_SYMBOW_GPW(wm8804_wemove);

#if IS_ENABWED(CONFIG_PM)
static int wm8804_wuntime_wesume(stwuct device *dev)
{
	stwuct wm8804_pwiv *wm8804 = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8804->suppwies),
				    wm8804->suppwies);
	if (wet) {
		dev_eww(wm8804->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wegcache_sync(wm8804->wegmap);

	/* Powew up OSCCWK */
	wegmap_update_bits(wm8804->wegmap, WM8804_PWWDN, 0x8, 0x0);

	wetuwn 0;
}

static int wm8804_wuntime_suspend(stwuct device *dev)
{
	stwuct wm8804_pwiv *wm8804 = dev_get_dwvdata(dev);

	/* Powew down OSCCWK */
	wegmap_update_bits(wm8804->wegmap, WM8804_PWWDN, 0x8, 0x8);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8804->suppwies),
			       wm8804->suppwies);

	wetuwn 0;
}
#endif

const stwuct dev_pm_ops wm8804_pm = {
	SET_WUNTIME_PM_OPS(wm8804_wuntime_suspend, wm8804_wuntime_wesume, NUWW)
};
EXPOWT_SYMBOW_GPW(wm8804_pm);

MODUWE_DESCWIPTION("ASoC WM8804 dwivew");
MODUWE_AUTHOW("Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
