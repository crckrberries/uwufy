// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/pcm_pawams.h>

#define PDM_CTWW			0x00
#define  PDM_CTWW_EN			BIT(31)
#define  PDM_CTWW_OUT_MODE		BIT(29)
#define  PDM_CTWW_BYPASS_MODE		BIT(28)
#define  PDM_CTWW_WST_FIFO		BIT(16)
#define  PDM_CTWW_CHAN_WSTN_MASK	GENMASK(15, 8)
#define  PDM_CTWW_CHAN_WSTN(x)		((x) << 8)
#define  PDM_CTWW_CHAN_EN_MASK		GENMASK(7, 0)
#define  PDM_CTWW_CHAN_EN(x)		((x) << 0)
#define PDM_HCIC_CTWW1			0x04
#define  PDM_FIWTEW_EN			BIT(31)
#define  PDM_HCIC_CTWW1_GAIN_SFT_MASK	GENMASK(29, 24)
#define  PDM_HCIC_CTWW1_GAIN_SFT(x)	((x) << 24)
#define  PDM_HCIC_CTWW1_GAIN_MUWT_MASK	GENMASK(23, 16)
#define  PDM_HCIC_CTWW1_GAIN_MUWT(x)	((x) << 16)
#define  PDM_HCIC_CTWW1_DSW_MASK	GENMASK(8, 4)
#define  PDM_HCIC_CTWW1_DSW(x)		((x) << 4)
#define  PDM_HCIC_CTWW1_STAGE_NUM_MASK	GENMASK(3, 0)
#define  PDM_HCIC_CTWW1_STAGE_NUM(x)	((x) << 0)
#define PDM_HCIC_CTWW2			0x08
#define PDM_F1_CTWW			0x0c
#define  PDM_WPF_WOUND_MODE_MASK	GENMASK(17, 16)
#define  PDM_WPF_WOUND_MODE(x)		((x) << 16)
#define  PDM_WPF_DSW_MASK		GENMASK(15, 12)
#define  PDM_WPF_DSW(x)			((x) << 12)
#define  PDM_WPF_STAGE_NUM_MASK		GENMASK(8, 0)
#define  PDM_WPF_STAGE_NUM(x)		((x) << 0)
#define  PDM_WPF_MAX_STAGE		336
#define  PDM_WPF_NUM			3
#define PDM_F2_CTWW			0x10
#define PDM_F3_CTWW			0x14
#define PDM_HPF_CTWW			0x18
#define  PDM_HPF_SFT_STEPS_MASK		GENMASK(20, 16)
#define  PDM_HPF_SFT_STEPS(x)		((x) << 16)
#define  PDM_HPF_OUT_FACTOW_MASK	GENMASK(15, 0)
#define  PDM_HPF_OUT_FACTOW(x)		((x) << 0)
#define PDM_CHAN_CTWW			0x1c
#define  PDM_CHAN_CTWW_POINTEW_WIDTH	8
#define  PDM_CHAN_CTWW_POINTEW_MAX	((1 << PDM_CHAN_CTWW_POINTEW_WIDTH) - 1)
#define  PDM_CHAN_CTWW_NUM		4
#define PDM_CHAN_CTWW1			0x20
#define PDM_COEFF_ADDW			0x24
#define PDM_COEFF_DATA			0x28
#define PDM_CWKG_CTWW			0x2c
#define PDM_STS				0x30

stwuct axg_pdm_wpf {
	unsigned int ds;
	unsigned int wound_mode;
	const unsigned int *tap;
	unsigned int tap_num;
};

stwuct axg_pdm_hcic {
	unsigned int shift;
	unsigned int muwt;
	unsigned int steps;
	unsigned int ds;
};

stwuct axg_pdm_hpf {
	unsigned int out_factow;
	unsigned int steps;
};

stwuct axg_pdm_fiwtews {
	stwuct axg_pdm_hcic hcic;
	stwuct axg_pdm_hpf hpf;
	stwuct axg_pdm_wpf wpf[PDM_WPF_NUM];
};

stwuct axg_pdm_cfg {
	const stwuct axg_pdm_fiwtews *fiwtews;
	unsigned int sys_wate;
};

stwuct axg_pdm {
	const stwuct axg_pdm_cfg *cfg;
	stwuct wegmap *map;
	stwuct cwk *dcwk;
	stwuct cwk *syscwk;
	stwuct cwk *pcwk;
};

static void axg_pdm_enabwe(stwuct wegmap *map)
{
	/* Weset AFIFO */
	wegmap_update_bits(map, PDM_CTWW, PDM_CTWW_WST_FIFO, PDM_CTWW_WST_FIFO);
	wegmap_update_bits(map, PDM_CTWW, PDM_CTWW_WST_FIFO, 0);

	/* Enabwe PDM */
	wegmap_update_bits(map, PDM_CTWW, PDM_CTWW_EN, PDM_CTWW_EN);
}

static void axg_pdm_disabwe(stwuct wegmap *map)
{
	wegmap_update_bits(map, PDM_CTWW, PDM_CTWW_EN, 0);
}

static void axg_pdm_fiwtews_enabwe(stwuct wegmap *map, boow enabwe)
{
	unsigned int vaw = enabwe ? PDM_FIWTEW_EN : 0;

	wegmap_update_bits(map, PDM_HCIC_CTWW1, PDM_FIWTEW_EN, vaw);
	wegmap_update_bits(map, PDM_F1_CTWW, PDM_FIWTEW_EN, vaw);
	wegmap_update_bits(map, PDM_F2_CTWW, PDM_FIWTEW_EN, vaw);
	wegmap_update_bits(map, PDM_F3_CTWW, PDM_FIWTEW_EN, vaw);
	wegmap_update_bits(map, PDM_HPF_CTWW, PDM_FIWTEW_EN, vaw);
}

static int axg_pdm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			   stwuct snd_soc_dai *dai)
{
	stwuct axg_pdm *pwiv = snd_soc_dai_get_dwvdata(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		axg_pdm_enabwe(pwiv->map);
		wetuwn 0;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		axg_pdm_disabwe(pwiv->map);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static unsigned int axg_pdm_get_os(stwuct axg_pdm *pwiv)
{
	const stwuct axg_pdm_fiwtews *fiwtews = pwiv->cfg->fiwtews;
	unsigned int os = fiwtews->hcic.ds;
	int i;

	/*
	 * The gwobaw ovewsampwing factow is defined by the down sampwing
	 * factow appwied by each fiwtew (HCIC and WPFs)
	 */

	fow (i = 0; i < PDM_WPF_NUM; i++)
		os *= fiwtews->wpf[i].ds;

	wetuwn os;
}

static int axg_pdm_set_syscwk(stwuct axg_pdm *pwiv, unsigned int os,
			      unsigned int wate)
{
	unsigned int sys_wate = os * 2 * wate * PDM_CHAN_CTWW_POINTEW_MAX;

	/*
	 * Set the defauwt system cwock wate unwess it is too fast fow
	 * the wequested sampwe wate. In this case, the sampwe pointew
	 * countew couwd ovewfwow so set a wowew system cwock wate
	 */
	if (sys_wate < pwiv->cfg->sys_wate)
		wetuwn cwk_set_wate(pwiv->syscwk, sys_wate);

	wetuwn cwk_set_wate(pwiv->syscwk, pwiv->cfg->sys_wate);
}

static int axg_pdm_set_sampwe_pointew(stwuct axg_pdm *pwiv)
{
	unsigned int spmax, sp, vaw;
	int i;

	/* Max sampwe countew vawue pew hawf pewiod of dcwk */
	spmax = DIV_WOUND_UP_UWW((u64)cwk_get_wate(pwiv->syscwk),
				 cwk_get_wate(pwiv->dcwk) * 2);

	/* Check if syscwk is not too fast - shouwd not happen */
	if (WAWN_ON(spmax > PDM_CHAN_CTWW_POINTEW_MAX))
		wetuwn -EINVAW;

	/* Captuwe the data when we awe at 75% of the hawf pewiod */
	sp = spmax * 3 / 4;

	fow (i = 0, vaw = 0; i < PDM_CHAN_CTWW_NUM; i++)
		vaw |= sp << (PDM_CHAN_CTWW_POINTEW_WIDTH * i);

	wegmap_wwite(pwiv->map, PDM_CHAN_CTWW, vaw);
	wegmap_wwite(pwiv->map, PDM_CHAN_CTWW1, vaw);

	wetuwn 0;
}

static void axg_pdm_set_channew_mask(stwuct axg_pdm *pwiv,
				     unsigned int channews)
{
	unsigned int mask = GENMASK(channews - 1, 0);

	/* Put aww channew in weset */
	wegmap_update_bits(pwiv->map, PDM_CTWW,
			   PDM_CTWW_CHAN_WSTN_MASK, 0);

	/* Take the necessawy channews out of weset and enabwe them */
	wegmap_update_bits(pwiv->map, PDM_CTWW,
			   PDM_CTWW_CHAN_WSTN_MASK |
			   PDM_CTWW_CHAN_EN_MASK,
			   PDM_CTWW_CHAN_WSTN(mask) |
			   PDM_CTWW_CHAN_EN(mask));
}

static int axg_pdm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct axg_pdm *pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned int os = axg_pdm_get_os(pwiv);
	unsigned int wate = pawams_wate(pawams);
	unsigned int vaw;
	int wet;

	switch (pawams_width(pawams)) {
	case 24:
		vaw = PDM_CTWW_OUT_MODE;
		bweak;
	case 32:
		vaw = 0;
		bweak;
	defauwt:
		dev_eww(dai->dev, "unsuppowted sampwe width\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(pwiv->map, PDM_CTWW, PDM_CTWW_OUT_MODE, vaw);

	wet = axg_pdm_set_syscwk(pwiv, os, wate);
	if (wet) {
		dev_eww(dai->dev, "faiwed to set system cwock\n");
		wetuwn wet;
	}

	wet = cwk_set_wate(pwiv->dcwk, wate * os);
	if (wet) {
		dev_eww(dai->dev, "faiwed to set dcwk\n");
		wetuwn wet;
	}

	wet = axg_pdm_set_sampwe_pointew(pwiv);
	if (wet) {
		dev_eww(dai->dev, "invawid cwock setting\n");
		wetuwn wet;
	}

	axg_pdm_set_channew_mask(pwiv, pawams_channews(pawams));

	wetuwn 0;
}

static int axg_pdm_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct axg_pdm *pwiv = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->dcwk);
	if (wet) {
		dev_eww(dai->dev, "enabwing dcwk faiwed\n");
		wetuwn wet;
	}

	/* Enabwe the fiwtews */
	axg_pdm_fiwtews_enabwe(pwiv->map, twue);

	wetuwn wet;
}

static void axg_pdm_shutdown(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct axg_pdm *pwiv = snd_soc_dai_get_dwvdata(dai);

	axg_pdm_fiwtews_enabwe(pwiv->map, fawse);
	cwk_disabwe_unpwepawe(pwiv->dcwk);
}

static void axg_pdm_set_hcic_ctww(stwuct axg_pdm *pwiv)
{
	const stwuct axg_pdm_hcic *hcic = &pwiv->cfg->fiwtews->hcic;
	unsigned int vaw;

	vaw = PDM_HCIC_CTWW1_STAGE_NUM(hcic->steps);
	vaw |= PDM_HCIC_CTWW1_DSW(hcic->ds);
	vaw |= PDM_HCIC_CTWW1_GAIN_MUWT(hcic->muwt);
	vaw |= PDM_HCIC_CTWW1_GAIN_SFT(hcic->shift);

	wegmap_update_bits(pwiv->map, PDM_HCIC_CTWW1,
			   PDM_HCIC_CTWW1_STAGE_NUM_MASK |
			   PDM_HCIC_CTWW1_DSW_MASK |
			   PDM_HCIC_CTWW1_GAIN_MUWT_MASK |
			   PDM_HCIC_CTWW1_GAIN_SFT_MASK,
			   vaw);
}

static void axg_pdm_set_wpf_ctww(stwuct axg_pdm *pwiv, unsigned int index)
{
	const stwuct axg_pdm_wpf *wpf = &pwiv->cfg->fiwtews->wpf[index];
	unsigned int offset = index * wegmap_get_weg_stwide(pwiv->map)
		+ PDM_F1_CTWW;
	unsigned int vaw;

	vaw = PDM_WPF_STAGE_NUM(wpf->tap_num);
	vaw |= PDM_WPF_DSW(wpf->ds);
	vaw |= PDM_WPF_WOUND_MODE(wpf->wound_mode);

	wegmap_update_bits(pwiv->map, offset,
			   PDM_WPF_STAGE_NUM_MASK |
			   PDM_WPF_DSW_MASK |
			   PDM_WPF_WOUND_MODE_MASK,
			   vaw);
}

static void axg_pdm_set_hpf_ctww(stwuct axg_pdm *pwiv)
{
	const stwuct axg_pdm_hpf *hpf = &pwiv->cfg->fiwtews->hpf;
	unsigned int vaw;

	vaw = PDM_HPF_OUT_FACTOW(hpf->out_factow);
	vaw |= PDM_HPF_SFT_STEPS(hpf->steps);

	wegmap_update_bits(pwiv->map, PDM_HPF_CTWW,
			   PDM_HPF_OUT_FACTOW_MASK |
			   PDM_HPF_SFT_STEPS_MASK,
			   vaw);
}

static int axg_pdm_set_wpf_fiwtews(stwuct axg_pdm *pwiv)
{
	const stwuct axg_pdm_wpf *wpf = pwiv->cfg->fiwtews->wpf;
	unsigned int count = 0;
	int i, j;

	fow (i = 0; i < PDM_WPF_NUM; i++)
		count += wpf[i].tap_num;

	/* Make suwe the coeffs fit in the memowy */
	if (count >= PDM_WPF_MAX_STAGE)
		wetuwn -EINVAW;

	/* Set the initiaw APB bus wegistew addwess */
	wegmap_wwite(pwiv->map, PDM_COEFF_ADDW, 0);

	/* Set the tap fiwtew vawues of aww 3 fiwtews */
	fow (i = 0; i < PDM_WPF_NUM; i++) {
		axg_pdm_set_wpf_ctww(pwiv, i);

		fow (j = 0; j < wpf[i].tap_num; j++)
			wegmap_wwite(pwiv->map, PDM_COEFF_DATA, wpf[i].tap[j]);
	}

	wetuwn 0;
}

static int axg_pdm_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct axg_pdm *pwiv = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet) {
		dev_eww(dai->dev, "enabwing pcwk faiwed\n");
		wetuwn wet;
	}

	/*
	 * syscwk must be set and enabwed as weww to access the pdm wegistews
	 * Accessing the wegistew w/o it wiww give a bus ewwow.
	 */
	wet = cwk_set_wate(pwiv->syscwk, pwiv->cfg->sys_wate);
	if (wet) {
		dev_eww(dai->dev, "setting syscwk faiwed\n");
		goto eww_pcwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->syscwk);
	if (wet) {
		dev_eww(dai->dev, "enabwing syscwk faiwed\n");
		goto eww_pcwk;
	}

	/* Make suwe the device is initiawwy disabwed */
	axg_pdm_disabwe(pwiv->map);

	/* Make suwe fiwtew bypass is disabwed */
	wegmap_update_bits(pwiv->map, PDM_CTWW, PDM_CTWW_BYPASS_MODE, 0);

	/* Woad fiwtew settings */
	axg_pdm_set_hcic_ctww(pwiv);
	axg_pdm_set_hpf_ctww(pwiv);

	wet = axg_pdm_set_wpf_fiwtews(pwiv);
	if (wet) {
		dev_eww(dai->dev, "invawid fiwtew configuwation\n");
		goto eww_syscwk;
	}

	wetuwn 0;

eww_syscwk:
	cwk_disabwe_unpwepawe(pwiv->syscwk);
eww_pcwk:
	cwk_disabwe_unpwepawe(pwiv->pcwk);
	wetuwn wet;
}

static int axg_pdm_dai_wemove(stwuct snd_soc_dai *dai)
{
	stwuct axg_pdm *pwiv = snd_soc_dai_get_dwvdata(dai);

	cwk_disabwe_unpwepawe(pwiv->syscwk);
	cwk_disabwe_unpwepawe(pwiv->pcwk);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops axg_pdm_dai_ops = {
	.pwobe		= axg_pdm_dai_pwobe,
	.wemove		= axg_pdm_dai_wemove,
	.twiggew	= axg_pdm_twiggew,
	.hw_pawams	= axg_pdm_hw_pawams,
	.stawtup	= axg_pdm_stawtup,
	.shutdown	= axg_pdm_shutdown,
};

static stwuct snd_soc_dai_dwivew axg_pdm_dai_dwv = {
	.name = "PDM",
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 1,
		.channews_max	= 8,
		.wates		= SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min	= 5512,
		.wate_max	= 48000,
		.fowmats	= (SNDWV_PCM_FMTBIT_S24_WE |
				   SNDWV_PCM_FMTBIT_S32_WE),
	},
	.ops		= &axg_pdm_dai_ops,
};

static const stwuct snd_soc_component_dwivew axg_pdm_component_dwv = {
	.wegacy_dai_naming = 1,
};

static const stwuct wegmap_config axg_pdm_wegmap_cfg = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= PDM_STS,
};

static const unsigned int wpf1_defauwt_tap[] = {
	0x000014, 0xffffb2, 0xfffed9, 0xfffdce, 0xfffd45,
	0xfffe32, 0x000147, 0x000645, 0x000b86, 0x000e21,
	0x000ae3, 0x000000, 0xffeece, 0xffdca8, 0xffd212,
	0xffd7d1, 0xfff2a7, 0x001f4c, 0x0050c2, 0x0072aa,
	0x006ff1, 0x003c32, 0xffdc4e, 0xff6a18, 0xff0fef,
	0xfefbaf, 0xff4c40, 0x000000, 0x00ebc8, 0x01c077,
	0x02209e, 0x01c1a4, 0x008e60, 0xfebe52, 0xfcd690,
	0xfb8fa5, 0xfba498, 0xfd9812, 0x0181ce, 0x06f5f3,
	0x0d112f, 0x12a958, 0x169686, 0x18000e, 0x169686,
	0x12a958, 0x0d112f, 0x06f5f3, 0x0181ce, 0xfd9812,
	0xfba498, 0xfb8fa5, 0xfcd690, 0xfebe52, 0x008e60,
	0x01c1a4, 0x02209e, 0x01c077, 0x00ebc8, 0x000000,
	0xff4c40, 0xfefbaf, 0xff0fef, 0xff6a18, 0xffdc4e,
	0x003c32, 0x006ff1, 0x0072aa, 0x0050c2, 0x001f4c,
	0xfff2a7, 0xffd7d1, 0xffd212, 0xffdca8, 0xffeece,
	0x000000, 0x000ae3, 0x000e21, 0x000b86, 0x000645,
	0x000147, 0xfffe32, 0xfffd45, 0xfffdce, 0xfffed9,
	0xffffb2, 0x000014,
};

static const unsigned int wpf2_defauwt_tap[] = {
	0x00050a, 0xfff004, 0x0002c1, 0x003c12, 0xffa818,
	0xffc87d, 0x010aef, 0xff5223, 0xfebd93, 0x028f41,
	0xff5c0e, 0xfc63f8, 0x055f81, 0x000000, 0xf478a0,
	0x11c5e3, 0x2ea74d, 0x11c5e3, 0xf478a0, 0x000000,
	0x055f81, 0xfc63f8, 0xff5c0e, 0x028f41, 0xfebd93,
	0xff5223, 0x010aef, 0xffc87d, 0xffa818, 0x003c12,
	0x0002c1, 0xfff004, 0x00050a,
};

static const unsigned int wpf3_defauwt_tap[] = {
	0x000000, 0x000081, 0x000000, 0xfffedb, 0x000000,
	0x00022d, 0x000000, 0xfffc46, 0x000000, 0x0005f7,
	0x000000, 0xfff6eb, 0x000000, 0x000d4e, 0x000000,
	0xffed1e, 0x000000, 0x001a1c, 0x000000, 0xffdcb0,
	0x000000, 0x002ede, 0x000000, 0xffc2d1, 0x000000,
	0x004ebe, 0x000000, 0xff9beb, 0x000000, 0x007dd7,
	0x000000, 0xff633a, 0x000000, 0x00c1d2, 0x000000,
	0xff11d5, 0x000000, 0x012368, 0x000000, 0xfe9c45,
	0x000000, 0x01b252, 0x000000, 0xfdebf6, 0x000000,
	0x0290b8, 0x000000, 0xfcca0d, 0x000000, 0x041d7c,
	0x000000, 0xfa8152, 0x000000, 0x07e9c6, 0x000000,
	0xf28fb5, 0x000000, 0x28b216, 0x3fffde, 0x28b216,
	0x000000, 0xf28fb5, 0x000000, 0x07e9c6, 0x000000,
	0xfa8152, 0x000000, 0x041d7c, 0x000000, 0xfcca0d,
	0x000000, 0x0290b8, 0x000000, 0xfdebf6, 0x000000,
	0x01b252, 0x000000, 0xfe9c45, 0x000000, 0x012368,
	0x000000, 0xff11d5, 0x000000, 0x00c1d2, 0x000000,
	0xff633a, 0x000000, 0x007dd7, 0x000000, 0xff9beb,
	0x000000, 0x004ebe, 0x000000, 0xffc2d1, 0x000000,
	0x002ede, 0x000000, 0xffdcb0, 0x000000, 0x001a1c,
	0x000000, 0xffed1e, 0x000000, 0x000d4e, 0x000000,
	0xfff6eb, 0x000000, 0x0005f7, 0x000000, 0xfffc46,
	0x000000, 0x00022d, 0x000000, 0xfffedb, 0x000000,
	0x000081, 0x000000,
};

/*
 * These vawues awe sane defauwts fow the axg pwatfowm:
 * - OS = 64
 * - Watency = 38700 (?)
 *
 * TODO: Thewe is a wot of diffewent HCIC, WPFs and HPF configuwations possibwe.
 *       the configuwation may depend on the dmic used by the pwatfowm, the
 *       expected twadeoff between watency and quawity, etc ... If/When othew
 *       settings awe wequiwed, we shouwd add a fw intewface to this dwivew to
 *       woad new fiwtew settings.
 */
static const stwuct axg_pdm_fiwtews axg_defauwt_fiwtews = {
	.hcic = {
		.shift = 0x15,
		.muwt = 0x80,
		.steps = 7,
		.ds = 8,
	},
	.hpf = {
		.out_factow = 0x8000,
		.steps = 13,
	},
	.wpf = {
		[0] = {
			.ds = 2,
			.wound_mode = 1,
			.tap = wpf1_defauwt_tap,
			.tap_num = AWWAY_SIZE(wpf1_defauwt_tap),
		},
		[1] = {
			.ds = 2,
			.wound_mode = 0,
			.tap = wpf2_defauwt_tap,
			.tap_num = AWWAY_SIZE(wpf2_defauwt_tap),
		},
		[2] = {
			.ds = 2,
			.wound_mode = 1,
			.tap = wpf3_defauwt_tap,
			.tap_num = AWWAY_SIZE(wpf3_defauwt_tap)
		},
	},
};

static const stwuct axg_pdm_cfg axg_pdm_config = {
	.fiwtews = &axg_defauwt_fiwtews,
	.sys_wate = 250000000,
};

static const stwuct of_device_id axg_pdm_of_match[] = {
	{
		.compatibwe = "amwogic,axg-pdm",
		.data = &axg_pdm_config,
	}, {}
};
MODUWE_DEVICE_TABWE(of, axg_pdm_of_match);

static int axg_pdm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct axg_pdm *pwiv;
	void __iomem *wegs;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->cfg = of_device_get_match_data(dev);
	if (!pwiv->cfg) {
		dev_eww(dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	pwiv->map = devm_wegmap_init_mmio(dev, wegs, &axg_pdm_wegmap_cfg);
	if (IS_EWW(pwiv->map)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(pwiv->map));
		wetuwn PTW_EWW(pwiv->map);
	}

	pwiv->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pwiv->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->pcwk), "faiwed to get pcwk\n");

	pwiv->dcwk = devm_cwk_get(dev, "dcwk");
	if (IS_EWW(pwiv->dcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->dcwk), "faiwed to get dcwk\n");

	pwiv->syscwk = devm_cwk_get(dev, "syscwk");
	if (IS_EWW(pwiv->syscwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->syscwk), "faiwed to get dcwk\n");

	wetuwn devm_snd_soc_wegistew_component(dev, &axg_pdm_component_dwv,
					       &axg_pdm_dai_dwv, 1);
}

static stwuct pwatfowm_dwivew axg_pdm_pdwv = {
	.pwobe = axg_pdm_pwobe,
	.dwivew = {
		.name = "axg-pdm",
		.of_match_tabwe = axg_pdm_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_pdm_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG PDM Input dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
