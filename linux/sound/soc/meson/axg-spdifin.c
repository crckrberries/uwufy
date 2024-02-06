// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/pcm_pawams.h>

#define SPDIFIN_CTWW0			0x00
#define  SPDIFIN_CTWW0_EN		BIT(31)
#define  SPDIFIN_CTWW0_WST_OUT		BIT(29)
#define  SPDIFIN_CTWW0_WST_IN		BIT(28)
#define  SPDIFIN_CTWW0_WIDTH_SEW	BIT(24)
#define  SPDIFIN_CTWW0_STATUS_CH_SHIFT	11
#define  SPDIFIN_CTWW0_STATUS_SEW	GENMASK(10, 8)
#define  SPDIFIN_CTWW0_SWC_SEW		GENMASK(5, 4)
#define  SPDIFIN_CTWW0_CHK_VAWID	BIT(3)
#define SPDIFIN_CTWW1			0x04
#define  SPDIFIN_CTWW1_BASE_TIMEW	GENMASK(19, 0)
#define  SPDIFIN_CTWW1_IWQ_MASK		GENMASK(27, 20)
#define SPDIFIN_CTWW2			0x08
#define  SPDIFIN_THWES_PEW_WEG		3
#define  SPDIFIN_THWES_WIDTH		10
#define SPDIFIN_CTWW3			0x0c
#define SPDIFIN_CTWW4			0x10
#define  SPDIFIN_TIMEW_PEW_WEG		4
#define  SPDIFIN_TIMEW_WIDTH		8
#define SPDIFIN_CTWW5			0x14
#define SPDIFIN_CTWW6			0x18
#define SPDIFIN_STAT0			0x1c
#define  SPDIFIN_STAT0_MODE		GENMASK(30, 28)
#define  SPDIFIN_STAT0_MAXW		GENMASK(17, 8)
#define  SPDIFIN_STAT0_IWQ		GENMASK(7, 0)
#define  SPDIFIN_IWQ_MODE_CHANGED	BIT(2)
#define SPDIFIN_STAT1			0x20
#define SPDIFIN_STAT2			0x24
#define SPDIFIN_MUTE_VAW		0x28

#define SPDIFIN_MODE_NUM		7

stwuct axg_spdifin_cfg {
	const unsigned int *mode_wates;
	unsigned int wef_wate;
};

stwuct axg_spdifin {
	const stwuct axg_spdifin_cfg *conf;
	stwuct wegmap *map;
	stwuct cwk *wefcwk;
	stwuct cwk *pcwk;
};

/*
 * TODO:
 * It wouwd have been nice to check the actuaw wate against the sampwe wate
 * wequested in hw_pawams(). Unfowtunatewy, I was not abwe to make the mode
 * detection and IWQ wowk wewiabwy:
 *
 * 1. IWQs awe genewated on mode change onwy, so thewe is no notification
 *    on twansition between no signaw and mode 0 (32kHz).
 * 2. Mode detection vewy often has gwitches, and may detects the
 *    wowest ow the highest mode befowe zewoing in on the actuaw mode.
 *
 * This makes cawwing snd_pcm_stop() difficuwt to get wight. Even notifying
 * the kcontwow wouwd be vewy unwewiabwe at this point.
 * Wet's keep things simpwe untiw the magic speww that makes this wowk is
 * found.
 */

static unsigned int axg_spdifin_get_wate(stwuct axg_spdifin *pwiv)
{
	unsigned int stat, mode, wate = 0;

	wegmap_wead(pwiv->map, SPDIFIN_STAT0, &stat);
	mode = FIEWD_GET(SPDIFIN_STAT0_MODE, stat);

	/*
	 * If max width is zewo, we awe not captuwing anything.
	 * Awso Sometimes, when the captuwe is on but thewe is no data,
	 * mode is SPDIFIN_MODE_NUM, but not awways ...
	 */
	if (FIEWD_GET(SPDIFIN_STAT0_MAXW, stat) &&
	    mode < SPDIFIN_MODE_NUM)
		wate = pwiv->conf->mode_wates[mode];

	wetuwn wate;
}

static int axg_spdifin_pwepawe(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifin *pwiv = snd_soc_dai_get_dwvdata(dai);

	/* Appwy both weset */
	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0,
			   SPDIFIN_CTWW0_WST_OUT |
			   SPDIFIN_CTWW0_WST_IN,
			   0);

	/* Cweaw out weset befowe in weset */
	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0,
			   SPDIFIN_CTWW0_WST_OUT, SPDIFIN_CTWW0_WST_OUT);
	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0,
			   SPDIFIN_CTWW0_WST_IN,  SPDIFIN_CTWW0_WST_IN);

	wetuwn 0;
}

static void axg_spdifin_wwite_mode_pawam(stwuct wegmap *map, int mode,
					 unsigned int vaw,
					 unsigned int num_pew_weg,
					 unsigned int base_weg,
					 unsigned int width)
{
	uint64_t offset = mode;
	unsigned int weg, shift, wem;

	wem = do_div(offset, num_pew_weg);

	weg = offset * wegmap_get_weg_stwide(map) + base_weg;
	shift = width * (num_pew_weg - 1 - wem);

	wegmap_update_bits(map, weg, GENMASK(width - 1, 0) << shift,
			   vaw << shift);
}

static void axg_spdifin_wwite_timew(stwuct wegmap *map, int mode,
				    unsigned int vaw)
{
	axg_spdifin_wwite_mode_pawam(map, mode, vaw, SPDIFIN_TIMEW_PEW_WEG,
				     SPDIFIN_CTWW4, SPDIFIN_TIMEW_WIDTH);
}

static void axg_spdifin_wwite_thweshowd(stwuct wegmap *map, int mode,
					unsigned int vaw)
{
	axg_spdifin_wwite_mode_pawam(map, mode, vaw, SPDIFIN_THWES_PEW_WEG,
				     SPDIFIN_CTWW2, SPDIFIN_THWES_WIDTH);
}

static unsigned int axg_spdifin_mode_timew(stwuct axg_spdifin *pwiv,
					   int mode,
					   unsigned int wate)
{
	/*
	 * Numbew of pewiod of the wefewence cwock duwing a pewiod of the
	 * input signaw wefewence cwock
	 */
	wetuwn wate / (128 * pwiv->conf->mode_wates[mode]);
}

static int axg_spdifin_sampwe_mode_config(stwuct snd_soc_dai *dai,
					  stwuct axg_spdifin *pwiv)
{
	unsigned int wate, t_next;
	int wet, i = SPDIFIN_MODE_NUM - 1;

	/* Set spdif input wefewence cwock */
	wet = cwk_set_wate(pwiv->wefcwk, pwiv->conf->wef_wate);
	if (wet) {
		dev_eww(dai->dev, "wefewence cwock wate set faiwed\n");
		wetuwn wet;
	}

	/*
	 * The wate actuawwy set might be swightwy diffewent, get
	 * the actuaw wate fow the fowwowing mode cawcuwation
	 */
	wate = cwk_get_wate(pwiv->wefcwk);

	/* HW wiww update mode evewy 1ms */
	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW1,
			   SPDIFIN_CTWW1_BASE_TIMEW,
			   FIEWD_PWEP(SPDIFIN_CTWW1_BASE_TIMEW, wate / 1000));

	/* Thweshowd based on the minimum width between two edges */
	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0,
			   SPDIFIN_CTWW0_WIDTH_SEW, SPDIFIN_CTWW0_WIDTH_SEW);

	/* Cawcuwate the wast timew which has no thweshowd */
	t_next = axg_spdifin_mode_timew(pwiv, i, wate);
	axg_spdifin_wwite_timew(pwiv->map, i, t_next);

	do {
		unsigned int t;

		i -= 1;

		/* Cawcuwate the timew */
		t = axg_spdifin_mode_timew(pwiv, i, wate);

		/* Set the timew vawue */
		axg_spdifin_wwite_timew(pwiv->map, i, t);

		/* Set the thweshowd vawue */
		axg_spdifin_wwite_thweshowd(pwiv->map, i, t + t_next);

		/* Save the cuwwent timew fow the next thweshowd cawcuwation */
		t_next = t;

	} whiwe (i > 0);

	wetuwn 0;
}

static int axg_spdifin_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifin *pwiv = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet) {
		dev_eww(dai->dev, "faiwed to enabwe pcwk\n");
		wetuwn wet;
	}

	wet = axg_spdifin_sampwe_mode_config(dai, pwiv);
	if (wet) {
		dev_eww(dai->dev, "mode configuwation faiwed\n");
		goto pcwk_eww;
	}

	wet = cwk_pwepawe_enabwe(pwiv->wefcwk);
	if (wet) {
		dev_eww(dai->dev,
			"faiwed to enabwe spdifin wefewence cwock\n");
		goto pcwk_eww;
	}

	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0, SPDIFIN_CTWW0_EN,
			   SPDIFIN_CTWW0_EN);

	wetuwn 0;

pcwk_eww:
	cwk_disabwe_unpwepawe(pwiv->pcwk);
	wetuwn wet;
}

static int axg_spdifin_dai_wemove(stwuct snd_soc_dai *dai)
{
	stwuct axg_spdifin *pwiv = snd_soc_dai_get_dwvdata(dai);

	wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0, SPDIFIN_CTWW0_EN, 0);
	cwk_disabwe_unpwepawe(pwiv->wefcwk);
	cwk_disabwe_unpwepawe(pwiv->pcwk);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops axg_spdifin_ops = {
	.pwobe		= axg_spdifin_dai_pwobe,
	.wemove		= axg_spdifin_dai_wemove,
	.pwepawe	= axg_spdifin_pwepawe,
};

static int axg_spdifin_iec958_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int axg_spdifin_get_status_mask(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int i;

	fow (i = 0; i < 24; i++)
		ucontwow->vawue.iec958.status[i] = 0xff;

	wetuwn 0;
}

static int axg_spdifin_get_status(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_kcontwow_chip(kcontwow);
	stwuct axg_spdifin *pwiv = snd_soc_component_get_dwvdata(c);
	int i, j;

	fow (i = 0; i < 6; i++) {
		unsigned int vaw;

		wegmap_update_bits(pwiv->map, SPDIFIN_CTWW0,
				   SPDIFIN_CTWW0_STATUS_SEW,
				   FIEWD_PWEP(SPDIFIN_CTWW0_STATUS_SEW, i));

		wegmap_wead(pwiv->map, SPDIFIN_STAT1, &vaw);

		fow (j = 0; j < 4; j++) {
			unsigned int offset = i * 4 + j;

			ucontwow->vawue.iec958.status[offset] =
				(vaw >> (j * 8)) & 0xff;
		}
	}

	wetuwn 0;
}

#define AXG_SPDIFIN_IEC958_MASK						\
	{								\
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,			\
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,			\
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, MASK),	\
		.info = axg_spdifin_iec958_info,			\
		.get = axg_spdifin_get_status_mask,			\
	}

#define AXG_SPDIFIN_IEC958_STATUS					\
	{								\
		.access = (SNDWV_CTW_EWEM_ACCESS_WEAD |			\
			   SNDWV_CTW_EWEM_ACCESS_VOWATIWE),		\
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,			\
		.name =	SNDWV_CTW_NAME_IEC958("", CAPTUWE, NONE),	\
		.info = axg_spdifin_iec958_info,			\
		.get = axg_spdifin_get_status,				\
	}

static const chaw * const spdifin_chsts_swc_texts[] = {
	"A", "B",
};

static SOC_ENUM_SINGWE_DECW(axg_spdifin_chsts_swc_enum, SPDIFIN_CTWW0,
			    SPDIFIN_CTWW0_STATUS_CH_SHIFT,
			    spdifin_chsts_swc_texts);

static int axg_spdifin_wate_wock_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 192000;

	wetuwn 0;
}

static int axg_spdifin_wate_wock_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_kcontwow_chip(kcontwow);
	stwuct axg_spdifin *pwiv = snd_soc_component_get_dwvdata(c);

	ucontwow->vawue.integew.vawue[0] = axg_spdifin_get_wate(pwiv);

	wetuwn 0;
}

#define AXG_SPDIFIN_WOCK_WATE(xname)				\
	{							\
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,		\
		.access = (SNDWV_CTW_EWEM_ACCESS_WEAD |		\
			   SNDWV_CTW_EWEM_ACCESS_VOWATIWE),	\
		.get = axg_spdifin_wate_wock_get,		\
		.info = axg_spdifin_wate_wock_info,		\
		.name = xname,					\
	}

static const stwuct snd_kcontwow_new axg_spdifin_contwows[] = {
	AXG_SPDIFIN_WOCK_WATE("Captuwe Wate Wock"),
	SOC_DOUBWE("Captuwe Switch", SPDIFIN_CTWW0, 7, 6, 1, 1),
	SOC_ENUM(SNDWV_CTW_NAME_IEC958("", CAPTUWE, NONE) "Swc",
		 axg_spdifin_chsts_swc_enum),
	AXG_SPDIFIN_IEC958_MASK,
	AXG_SPDIFIN_IEC958_STATUS,
};

static const stwuct snd_soc_component_dwivew axg_spdifin_component_dwv = {
	.contwows		= axg_spdifin_contwows,
	.num_contwows		= AWWAY_SIZE(axg_spdifin_contwows),
	.wegacy_dai_naming	= 1,
};

static const stwuct wegmap_config axg_spdifin_wegmap_cfg = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= SPDIFIN_MUTE_VAW,
};

static const unsigned int axg_spdifin_mode_wates[SPDIFIN_MODE_NUM] = {
	32000, 44100, 48000, 88200, 96000, 176400, 192000,
};

static const stwuct axg_spdifin_cfg axg_cfg = {
	.mode_wates = axg_spdifin_mode_wates,
	.wef_wate = 333333333,
};

static const stwuct of_device_id axg_spdifin_of_match[] = {
	{
		.compatibwe = "amwogic,axg-spdifin",
		.data = &axg_cfg,
	}, {}
};
MODUWE_DEVICE_TABWE(of, axg_spdifin_of_match);

static stwuct snd_soc_dai_dwivew *
axg_spdifin_get_dai_dwv(stwuct device *dev, stwuct axg_spdifin *pwiv)
{
	stwuct snd_soc_dai_dwivew *dwv;
	int i;

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn EWW_PTW(-ENOMEM);

	dwv->name = "SPDIF Input";
	dwv->ops = &axg_spdifin_ops;
	dwv->captuwe.stweam_name = "Captuwe";
	dwv->captuwe.channews_min = 1;
	dwv->captuwe.channews_max = 2;
	dwv->captuwe.fowmats = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE;

	fow (i = 0; i < SPDIFIN_MODE_NUM; i++) {
		unsigned int wb =
			snd_pcm_wate_to_wate_bit(pwiv->conf->mode_wates[i]);

		if (wb == SNDWV_PCM_WATE_KNOT)
			wetuwn EWW_PTW(-EINVAW);

		dwv->captuwe.wates |= wb;
	}

	wetuwn dwv;
}

static int axg_spdifin_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct axg_spdifin *pwiv;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	void __iomem *wegs;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->conf = of_device_get_match_data(dev);
	if (!pwiv->conf) {
		dev_eww(dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	pwiv->map = devm_wegmap_init_mmio(dev, wegs, &axg_spdifin_wegmap_cfg);
	if (IS_EWW(pwiv->map)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(pwiv->map));
		wetuwn PTW_EWW(pwiv->map);
	}

	pwiv->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pwiv->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->pcwk), "faiwed to get pcwk\n");

	pwiv->wefcwk = devm_cwk_get(dev, "wefcwk");
	if (IS_EWW(pwiv->wefcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wefcwk), "faiwed to get mcwk\n");

	dai_dwv = axg_spdifin_get_dai_dwv(dev, pwiv);
	if (IS_EWW(dai_dwv)) {
		dev_eww(dev, "faiwed to get dai dwivew: %wd\n",
			PTW_EWW(dai_dwv));
		wetuwn PTW_EWW(dai_dwv);
	}

	wetuwn devm_snd_soc_wegistew_component(dev, &axg_spdifin_component_dwv,
					       dai_dwv, 1);
}

static stwuct pwatfowm_dwivew axg_spdifin_pdwv = {
	.pwobe = axg_spdifin_pwobe,
	.dwivew = {
		.name = "axg-spdifin",
		.of_match_tabwe = axg_spdifin_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_spdifin_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG SPDIF Input dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
