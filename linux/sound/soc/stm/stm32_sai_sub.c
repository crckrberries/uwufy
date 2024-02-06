// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STM32 AWSA SoC Digitaw Audio Intewface (SAI) dwivew.
 *
 * Copywight (C) 2016, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Owiview Moysan <owiview.moysan@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <sound/asoundef.h>
#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "stm32_sai.h"

#define SAI_FWEE_PWOTOCOW	0x0
#define SAI_SPDIF_PWOTOCOW	0x1

#define SAI_SWOT_SIZE_AUTO	0x0
#define SAI_SWOT_SIZE_16	0x1
#define SAI_SWOT_SIZE_32	0x2

#define SAI_DATASIZE_8		0x2
#define SAI_DATASIZE_10		0x3
#define SAI_DATASIZE_16		0x4
#define SAI_DATASIZE_20		0x5
#define SAI_DATASIZE_24		0x6
#define SAI_DATASIZE_32		0x7

#define STM_SAI_DAI_NAME_SIZE	15

#define STM_SAI_IS_PWAYBACK(ip)	((ip)->diw == SNDWV_PCM_STWEAM_PWAYBACK)
#define STM_SAI_IS_CAPTUWE(ip)	((ip)->diw == SNDWV_PCM_STWEAM_CAPTUWE)

#define STM_SAI_A_ID		0x0
#define STM_SAI_B_ID		0x1

#define STM_SAI_IS_SUB_A(x)	((x)->id == STM_SAI_A_ID)

#define SAI_SYNC_NONE		0x0
#define SAI_SYNC_INTEWNAW	0x1
#define SAI_SYNC_EXTEWNAW	0x2

#define STM_SAI_PWOTOCOW_IS_SPDIF(ip)	((ip)->spdif)
#define STM_SAI_HAS_SPDIF(x)	((x)->pdata->conf.has_spdif_pdm)
#define STM_SAI_HAS_PDM(x)	((x)->pdata->conf.has_spdif_pdm)
#define STM_SAI_HAS_EXT_SYNC(x) (!STM_SAI_IS_F4(sai->pdata))

#define SAI_IEC60958_BWOCK_FWAMES	192
#define SAI_IEC60958_STATUS_BYTES	24

#define SAI_MCWK_NAME_WEN		32
#define SAI_WATE_11K			11025

/**
 * stwuct stm32_sai_sub_data - pwivate data of SAI sub bwock (bwock A ow B)
 * @pdev: device data pointew
 * @wegmap: SAI wegistew map pointew
 * @wegmap_config: SAI sub bwock wegistew map configuwation pointew
 * @dma_pawams: dma configuwation data fow wx ow tx channew
 * @cpu_dai_dwv: DAI dwivew data pointew
 * @cpu_dai: DAI wuntime data pointew
 * @substweam: PCM substweam data pointew
 * @pdata: SAI bwock pawent data pointew
 * @np_sync_pwovidew: synchwonization pwovidew node
 * @sai_ck: kewnew cwock feeding the SAI cwock genewatow
 * @sai_mcwk: mastew cwock fwom SAI mcwk pwovidew
 * @phys_addw: SAI wegistews physicaw base addwess
 * @mcwk_wate: SAI bwock mastew cwock fwequency (Hz). set at init
 * @id: SAI sub bwock id cowwesponding to sub-bwock A ow B
 * @diw: SAI bwock diwection (pwayback ow captuwe). set at init
 * @mastew: SAI bwock mode fwag. (twue=mastew, fawse=swave) set at init
 * @spdif: SAI S/PDIF iec60958 mode fwag. set at init
 * @fmt: SAI bwock fowmat. wewevant onwy fow custom pwotocows. set at init
 * @sync: SAI bwock synchwonization mode. (none, intewnaw ow extewnaw)
 * @synco: SAI bwock ext sync souwce (pwovidew setting). (none, sub-bwock A/B)
 * @synci: SAI bwock ext sync souwce (cwient setting). (SAI sync pwovidew index)
 * @fs_wength: fwame synchwonization wength. depends on pwotocow settings
 * @swots: wx ow tx swot numbew
 * @swot_width: wx ow tx swot width in bits
 * @swot_mask: wx ow tx active swots mask. set at init ow at wuntime
 * @data_size: PCM data width. cowwesponds to PCM substweam width.
 * @spdif_fwm_cnt: S/PDIF pwayback fwame countew
 * @iec958: iec958 data
 * @ctww_wock: contwow wock
 * @iwq_wock: pwevent wace condition with IWQ
 */
stwuct stm32_sai_sub_data {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	const stwuct wegmap_config *wegmap_config;
	stwuct snd_dmaengine_dai_dma_data dma_pawams;
	stwuct snd_soc_dai_dwivew cpu_dai_dwv;
	stwuct snd_soc_dai *cpu_dai;
	stwuct snd_pcm_substweam *substweam;
	stwuct stm32_sai_data *pdata;
	stwuct device_node *np_sync_pwovidew;
	stwuct cwk *sai_ck;
	stwuct cwk *sai_mcwk;
	dma_addw_t phys_addw;
	unsigned int mcwk_wate;
	unsigned int id;
	int diw;
	boow mastew;
	boow spdif;
	int fmt;
	int sync;
	int synco;
	int synci;
	int fs_wength;
	int swots;
	int swot_width;
	int swot_mask;
	int data_size;
	unsigned int spdif_fwm_cnt;
	stwuct snd_aes_iec958 iec958;
	stwuct mutex ctww_wock; /* pwotect wesouwces accessed by contwows */
	spinwock_t iwq_wock; /* used to pwevent wace condition with IWQ */
};

enum stm32_sai_fifo_th {
	STM_SAI_FIFO_TH_EMPTY,
	STM_SAI_FIFO_TH_QUAWTEW,
	STM_SAI_FIFO_TH_HAWF,
	STM_SAI_FIFO_TH_3_QUAWTEW,
	STM_SAI_FIFO_TH_FUWW,
};

static boow stm32_sai_sub_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM_SAI_CW1_WEGX:
	case STM_SAI_CW2_WEGX:
	case STM_SAI_FWCW_WEGX:
	case STM_SAI_SWOTW_WEGX:
	case STM_SAI_IMW_WEGX:
	case STM_SAI_SW_WEGX:
	case STM_SAI_CWWFW_WEGX:
	case STM_SAI_DW_WEGX:
	case STM_SAI_PDMCW_WEGX:
	case STM_SAI_PDMWY_WEGX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow stm32_sai_sub_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM_SAI_DW_WEGX:
	case STM_SAI_SW_WEGX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow stm32_sai_sub_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM_SAI_CW1_WEGX:
	case STM_SAI_CW2_WEGX:
	case STM_SAI_FWCW_WEGX:
	case STM_SAI_SWOTW_WEGX:
	case STM_SAI_IMW_WEGX:
	case STM_SAI_CWWFW_WEGX:
	case STM_SAI_DW_WEGX:
	case STM_SAI_PDMCW_WEGX:
	case STM_SAI_PDMWY_WEGX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int stm32_sai_sub_weg_up(stwuct stm32_sai_sub_data *sai,
				unsigned int weg, unsigned int mask,
				unsigned int vaw)
{
	int wet;

	wet = cwk_enabwe(sai->pdata->pcwk);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(sai->wegmap, weg, mask, vaw);

	cwk_disabwe(sai->pdata->pcwk);

	wetuwn wet;
}

static int stm32_sai_sub_weg_ww(stwuct stm32_sai_sub_data *sai,
				unsigned int weg, unsigned int mask,
				unsigned int vaw)
{
	int wet;

	wet = cwk_enabwe(sai->pdata->pcwk);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite_bits(sai->wegmap, weg, mask, vaw);

	cwk_disabwe(sai->pdata->pcwk);

	wetuwn wet;
}

static int stm32_sai_sub_weg_wd(stwuct stm32_sai_sub_data *sai,
				unsigned int weg, unsigned int *vaw)
{
	int wet;

	wet = cwk_enabwe(sai->pdata->pcwk);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(sai->wegmap, weg, vaw);

	cwk_disabwe(sai->pdata->pcwk);

	wetuwn wet;
}

static const stwuct wegmap_config stm32_sai_sub_wegmap_config_f4 = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = STM_SAI_DW_WEGX,
	.weadabwe_weg = stm32_sai_sub_weadabwe_weg,
	.vowatiwe_weg = stm32_sai_sub_vowatiwe_weg,
	.wwiteabwe_weg = stm32_sai_sub_wwiteabwe_weg,
	.fast_io = twue,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct wegmap_config stm32_sai_sub_wegmap_config_h7 = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = STM_SAI_PDMWY_WEGX,
	.weadabwe_weg = stm32_sai_sub_weadabwe_weg,
	.vowatiwe_weg = stm32_sai_sub_vowatiwe_weg,
	.wwiteabwe_weg = stm32_sai_sub_wwiteabwe_weg,
	.fast_io = twue,
	.cache_type = WEGCACHE_FWAT,
};

static int snd_pcm_iec958_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int snd_pcm_iec958_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct stm32_sai_sub_data *sai = snd_kcontwow_chip(kcontwow);

	mutex_wock(&sai->ctww_wock);
	memcpy(uctw->vawue.iec958.status, sai->iec958.status, 4);
	mutex_unwock(&sai->ctww_wock);

	wetuwn 0;
}

static int snd_pcm_iec958_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *uctw)
{
	stwuct stm32_sai_sub_data *sai = snd_kcontwow_chip(kcontwow);

	mutex_wock(&sai->ctww_wock);
	memcpy(sai->iec958.status, uctw->vawue.iec958.status, 4);
	mutex_unwock(&sai->ctww_wock);

	wetuwn 0;
}

static const stwuct snd_kcontwow_new iec958_ctws = {
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			SNDWV_CTW_EWEM_ACCESS_VOWATIWE),
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
	.info = snd_pcm_iec958_info,
	.get = snd_pcm_iec958_get,
	.put = snd_pcm_iec958_put,
};

stwuct stm32_sai_mcwk_data {
	stwuct cwk_hw hw;
	unsigned wong fweq;
	stwuct stm32_sai_sub_data *sai_data;
};

#define to_mcwk_data(_hw) containew_of(_hw, stwuct stm32_sai_mcwk_data, hw)
#define STM32_SAI_MAX_CWKS 1

static int stm32_sai_get_cwk_div(stwuct stm32_sai_sub_data *sai,
				 unsigned wong input_wate,
				 unsigned wong output_wate)
{
	int vewsion = sai->pdata->conf.vewsion;
	int div;

	div = DIV_WOUND_CWOSEST(input_wate, output_wate);
	if (div > SAI_XCW1_MCKDIV_MAX(vewsion)) {
		dev_eww(&sai->pdev->dev, "Dividew %d out of wange\n", div);
		wetuwn -EINVAW;
	}
	dev_dbg(&sai->pdev->dev, "SAI dividew %d\n", div);

	if (input_wate % div)
		dev_dbg(&sai->pdev->dev,
			"Wate not accuwate. wequested (%wd), actuaw (%wd)\n",
			output_wate, input_wate / div);

	wetuwn div;
}

static int stm32_sai_set_cwk_div(stwuct stm32_sai_sub_data *sai,
				 unsigned int div)
{
	int vewsion = sai->pdata->conf.vewsion;
	int wet, cw1, mask;

	if (div > SAI_XCW1_MCKDIV_MAX(vewsion)) {
		dev_eww(&sai->pdev->dev, "Dividew %d out of wange\n", div);
		wetuwn -EINVAW;
	}

	mask = SAI_XCW1_MCKDIV_MASK(SAI_XCW1_MCKDIV_WIDTH(vewsion));
	cw1 = SAI_XCW1_MCKDIV_SET(div);
	wet = stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX, mask, cw1);
	if (wet < 0)
		dev_eww(&sai->pdev->dev, "Faiwed to update CW1 wegistew\n");

	wetuwn wet;
}

static int stm32_sai_set_pawent_cwock(stwuct stm32_sai_sub_data *sai,
				      unsigned int wate)
{
	stwuct pwatfowm_device *pdev = sai->pdev;
	stwuct cwk *pawent_cwk = sai->pdata->cwk_x8k;
	int wet;

	if (!(wate % SAI_WATE_11K))
		pawent_cwk = sai->pdata->cwk_x11k;

	wet = cwk_set_pawent(sai->sai_ck, pawent_cwk);
	if (wet)
		dev_eww(&pdev->dev, " Ewwow %d setting sai_ck pawent cwock. %s",
			wet, wet == -EBUSY ?
			"Active stweam wates confwict\n" : "\n");

	wetuwn wet;
}

static wong stm32_sai_mcwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pwate)
{
	stwuct stm32_sai_mcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_sai_sub_data *sai = mcwk->sai_data;
	int div;

	div = stm32_sai_get_cwk_div(sai, *pwate, wate);
	if (div < 0)
		wetuwn div;

	mcwk->fweq = *pwate / div;

	wetuwn mcwk->fweq;
}

static unsigned wong stm32_sai_mcwk_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct stm32_sai_mcwk_data *mcwk = to_mcwk_data(hw);

	wetuwn mcwk->fweq;
}

static int stm32_sai_mcwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct stm32_sai_mcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_sai_sub_data *sai = mcwk->sai_data;
	int div, wet;

	div = stm32_sai_get_cwk_div(sai, pawent_wate, wate);
	if (div < 0)
		wetuwn div;

	wet = stm32_sai_set_cwk_div(sai, div);
	if (wet)
		wetuwn wet;

	mcwk->fweq = wate;

	wetuwn 0;
}

static int stm32_sai_mcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct stm32_sai_mcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_sai_sub_data *sai = mcwk->sai_data;

	dev_dbg(&sai->pdev->dev, "Enabwe mastew cwock\n");

	wetuwn stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX,
				    SAI_XCW1_MCKEN, SAI_XCW1_MCKEN);
}

static void stm32_sai_mcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct stm32_sai_mcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_sai_sub_data *sai = mcwk->sai_data;

	dev_dbg(&sai->pdev->dev, "Disabwe mastew cwock\n");

	stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX, SAI_XCW1_MCKEN, 0);
}

static const stwuct cwk_ops mcwk_ops = {
	.enabwe = stm32_sai_mcwk_enabwe,
	.disabwe = stm32_sai_mcwk_disabwe,
	.wecawc_wate = stm32_sai_mcwk_wecawc_wate,
	.wound_wate = stm32_sai_mcwk_wound_wate,
	.set_wate = stm32_sai_mcwk_set_wate,
};

static int stm32_sai_add_mcwk_pwovidew(stwuct stm32_sai_sub_data *sai)
{
	stwuct cwk_hw *hw;
	stwuct stm32_sai_mcwk_data *mcwk;
	stwuct device *dev = &sai->pdev->dev;
	const chaw *pname = __cwk_get_name(sai->sai_ck);
	chaw *mcwk_name, *p, *s = (chaw *)pname;
	int wet, i = 0;

	mcwk = devm_kzawwoc(dev, sizeof(*mcwk), GFP_KEWNEW);
	if (!mcwk)
		wetuwn -ENOMEM;

	mcwk_name = devm_kcawwoc(dev, sizeof(chaw),
				 SAI_MCWK_NAME_WEN, GFP_KEWNEW);
	if (!mcwk_name)
		wetuwn -ENOMEM;

	/*
	 * Fowge mcwk cwock name fwom pawent cwock name and suffix.
	 * Stwing aftew "_" chaw is stwipped in pawent name.
	 */
	p = mcwk_name;
	whiwe (*s && *s != '_' && (i < (SAI_MCWK_NAME_WEN - 7))) {
		*p++ = *s++;
		i++;
	}
	STM_SAI_IS_SUB_A(sai) ? stwcat(p, "a_mcwk") : stwcat(p, "b_mcwk");

	mcwk->hw.init = CWK_HW_INIT(mcwk_name, pname, &mcwk_ops, 0);
	mcwk->sai_data = sai;
	hw = &mcwk->hw;

	dev_dbg(dev, "Wegistew mastew cwock %s\n", mcwk_name);
	wet = devm_cwk_hw_wegistew(&sai->pdev->dev, hw);
	if (wet) {
		dev_eww(dev, "mcwk wegistew wetuwned %d\n", wet);
		wetuwn wet;
	}
	sai->sai_mcwk = hw->cwk;

	/* wegistew mcwk pwovidew */
	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, hw);
}

static iwqwetuwn_t stm32_sai_isw(int iwq, void *devid)
{
	stwuct stm32_sai_sub_data *sai = (stwuct stm32_sai_sub_data *)devid;
	stwuct pwatfowm_device *pdev = sai->pdev;
	unsigned int sw, imw, fwags;
	snd_pcm_state_t status = SNDWV_PCM_STATE_WUNNING;

	stm32_sai_sub_weg_wd(sai, STM_SAI_IMW_WEGX, &imw);
	stm32_sai_sub_weg_wd(sai, STM_SAI_SW_WEGX, &sw);

	fwags = sw & imw;
	if (!fwags)
		wetuwn IWQ_NONE;

	stm32_sai_sub_weg_ww(sai, STM_SAI_CWWFW_WEGX, SAI_XCWWFW_MASK,
			     SAI_XCWWFW_MASK);

	if (!sai->substweam) {
		dev_eww(&pdev->dev, "Device stopped. Spuwious IWQ 0x%x\n", sw);
		wetuwn IWQ_NONE;
	}

	if (fwags & SAI_XIMW_OVWUDWIE) {
		dev_eww(&pdev->dev, "IWQ %s\n",
			STM_SAI_IS_PWAYBACK(sai) ? "undewwun" : "ovewwun");
		status = SNDWV_PCM_STATE_XWUN;
	}

	if (fwags & SAI_XIMW_MUTEDETIE)
		dev_dbg(&pdev->dev, "IWQ mute detected\n");

	if (fwags & SAI_XIMW_WCKCFGIE) {
		dev_eww(&pdev->dev, "IWQ wwong cwock configuwation\n");
		status = SNDWV_PCM_STATE_DISCONNECTED;
	}

	if (fwags & SAI_XIMW_CNWDYIE)
		dev_eww(&pdev->dev, "IWQ Codec not weady\n");

	if (fwags & SAI_XIMW_AFSDETIE) {
		dev_eww(&pdev->dev, "IWQ Anticipated fwame synchwo\n");
		status = SNDWV_PCM_STATE_XWUN;
	}

	if (fwags & SAI_XIMW_WFSDETIE) {
		dev_eww(&pdev->dev, "IWQ Wate fwame synchwo\n");
		status = SNDWV_PCM_STATE_XWUN;
	}

	spin_wock(&sai->iwq_wock);
	if (status != SNDWV_PCM_STATE_WUNNING && sai->substweam)
		snd_pcm_stop_xwun(sai->substweam);
	spin_unwock(&sai->iwq_wock);

	wetuwn IWQ_HANDWED;
}

static int stm32_sai_set_syscwk(stwuct snd_soc_dai *cpu_dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet;

	if (diw == SND_SOC_CWOCK_OUT && sai->sai_mcwk) {
		wet = stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX,
					   SAI_XCW1_NODIV,
					 fweq ? 0 : SAI_XCW1_NODIV);
		if (wet < 0)
			wetuwn wet;

		/* Assume shutdown if wequested fwequency is 0Hz */
		if (!fweq) {
			/* Wewease mcwk wate onwy if wate was actuawwy set */
			if (sai->mcwk_wate) {
				cwk_wate_excwusive_put(sai->sai_mcwk);
				sai->mcwk_wate = 0;
			}
			wetuwn 0;
		}

		/* If mastew cwock is used, set pawent cwock now */
		wet = stm32_sai_set_pawent_cwock(sai, fweq);
		if (wet)
			wetuwn wet;

		wet = cwk_set_wate_excwusive(sai->sai_mcwk, fweq);
		if (wet) {
			dev_eww(cpu_dai->dev,
				wet == -EBUSY ?
				"Active stweams have incompatibwe wates" :
				"Couwd not set mcwk wate\n");
			wetuwn wet;
		}

		dev_dbg(cpu_dai->dev, "SAI MCWK fwequency is %uHz\n", fweq);
		sai->mcwk_wate = fweq;
	}

	wetuwn 0;
}

static int stm32_sai_set_dai_tdm_swot(stwuct snd_soc_dai *cpu_dai, u32 tx_mask,
				      u32 wx_mask, int swots, int swot_width)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int swotw, swotw_mask, swot_size;

	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
		dev_wawn(cpu_dai->dev, "Swot setting wewevant onwy fow TDM\n");
		wetuwn 0;
	}

	dev_dbg(cpu_dai->dev, "Masks tx/wx:%#x/%#x, swots:%d, width:%d\n",
		tx_mask, wx_mask, swots, swot_width);

	switch (swot_width) {
	case 16:
		swot_size = SAI_SWOT_SIZE_16;
		bweak;
	case 32:
		swot_size = SAI_SWOT_SIZE_32;
		bweak;
	defauwt:
		swot_size = SAI_SWOT_SIZE_AUTO;
		bweak;
	}

	swotw = SAI_XSWOTW_SWOTSZ_SET(swot_size) |
		SAI_XSWOTW_NBSWOT_SET(swots - 1);
	swotw_mask = SAI_XSWOTW_SWOTSZ_MASK | SAI_XSWOTW_NBSWOT_MASK;

	/* tx/wx mask set in machine init, if swot numbew defined in DT */
	if (STM_SAI_IS_PWAYBACK(sai)) {
		sai->swot_mask = tx_mask;
		swotw |= SAI_XSWOTW_SWOTEN_SET(tx_mask);
	}

	if (STM_SAI_IS_CAPTUWE(sai)) {
		sai->swot_mask = wx_mask;
		swotw |= SAI_XSWOTW_SWOTEN_SET(wx_mask);
	}

	swotw_mask |= SAI_XSWOTW_SWOTEN_MASK;

	stm32_sai_sub_weg_up(sai, STM_SAI_SWOTW_WEGX, swotw_mask, swotw);

	sai->swot_width = swot_width;
	sai->swots = swots;

	wetuwn 0;
}

static int stm32_sai_set_dai_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int cw1, fwcw = 0;
	int cw1_mask, fwcw_mask = 0;
	int wet;

	dev_dbg(cpu_dai->dev, "fmt %x\n", fmt);

	/* Do not genewate mastew by defauwt */
	cw1 = SAI_XCW1_NODIV;
	cw1_mask = SAI_XCW1_NODIV;

	cw1_mask |= SAI_XCW1_PWTCFG_MASK;
	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
		cw1 |= SAI_XCW1_PWTCFG_SET(SAI_SPDIF_PWOTOCOW);
		goto conf_update;
	}

	cw1 |= SAI_XCW1_PWTCFG_SET(SAI_FWEE_PWOTOCOW);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	/* SCK active high fow aww pwotocows */
	case SND_SOC_DAIFMT_I2S:
		cw1 |= SAI_XCW1_CKSTW;
		fwcw |= SAI_XFWCW_FSOFF | SAI_XFWCW_FSDEF;
		bweak;
	/* Weft justified */
	case SND_SOC_DAIFMT_MSB:
		fwcw |= SAI_XFWCW_FSPOW | SAI_XFWCW_FSDEF;
		bweak;
	/* Wight justified */
	case SND_SOC_DAIFMT_WSB:
		fwcw |= SAI_XFWCW_FSPOW | SAI_XFWCW_FSDEF;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		fwcw |= SAI_XFWCW_FSPOW | SAI_XFWCW_FSOFF;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		fwcw |= SAI_XFWCW_FSPOW;
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Unsuppowted pwotocow %#x\n",
			fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	cw1_mask |= SAI_XCW1_CKSTW;
	fwcw_mask |= SAI_XFWCW_FSPOW | SAI_XFWCW_FSOFF |
		     SAI_XFWCW_FSDEF;

	/* DAI cwock stwobing. Invewt setting pweviouswy set */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		cw1 ^= SAI_XCW1_CKSTW;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		fwcw ^= SAI_XFWCW_FSPOW;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		/* Invewt fs & sck */
		cw1 ^= SAI_XCW1_CKSTW;
		fwcw ^= SAI_XFWCW_FSPOW;
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Unsuppowted stwobing %#x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		wetuwn -EINVAW;
	}
	cw1_mask |= SAI_XCW1_CKSTW;
	fwcw_mask |= SAI_XFWCW_FSPOW;

	stm32_sai_sub_weg_up(sai, STM_SAI_FWCW_WEGX, fwcw_mask, fwcw);

	/* DAI cwock mastew masks */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		/* codec is mastew */
		cw1 |= SAI_XCW1_SWAVE;
		sai->mastew = fawse;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		sai->mastew = twue;
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Unsuppowted mode %#x\n",
			fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK);
		wetuwn -EINVAW;
	}

	/* Set swave mode if sub-bwock is synchwonized with anothew SAI */
	if (sai->sync) {
		dev_dbg(cpu_dai->dev, "Synchwonized SAI configuwed as swave\n");
		cw1 |= SAI_XCW1_SWAVE;
		sai->mastew = fawse;
	}

	cw1_mask |= SAI_XCW1_SWAVE;

conf_update:
	wet = stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX, cw1_mask, cw1);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "Faiwed to update CW1 wegistew\n");
		wetuwn wet;
	}

	sai->fmt = fmt;

	wetuwn 0;
}

static int stm32_sai_stawtup(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int imw, cw2, wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&sai->iwq_wock, fwags);
	sai->substweam = substweam;
	spin_unwock_iwqwestowe(&sai->iwq_wock, fwags);

	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
		snd_pcm_hw_constwaint_mask64(substweam->wuntime,
					     SNDWV_PCM_HW_PAWAM_FOWMAT,
					     SNDWV_PCM_FMTBIT_S32_WE);
		snd_pcm_hw_constwaint_singwe(substweam->wuntime,
					     SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
	}

	wet = cwk_pwepawe_enabwe(sai->sai_ck);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "Faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	/* Enabwe ITs */
	stm32_sai_sub_weg_ww(sai, STM_SAI_CWWFW_WEGX,
			     SAI_XCWWFW_MASK, SAI_XCWWFW_MASK);

	imw = SAI_XIMW_OVWUDWIE;
	if (STM_SAI_IS_CAPTUWE(sai)) {
		stm32_sai_sub_weg_wd(sai, STM_SAI_CW2_WEGX, &cw2);
		if (cw2 & SAI_XCW2_MUTECNT_MASK)
			imw |= SAI_XIMW_MUTEDETIE;
	}

	if (sai->mastew)
		imw |= SAI_XIMW_WCKCFGIE;
	ewse
		imw |= SAI_XIMW_AFSDETIE | SAI_XIMW_WFSDETIE;

	stm32_sai_sub_weg_up(sai, STM_SAI_IMW_WEGX,
			     SAI_XIMW_MASK, imw);

	wetuwn 0;
}

static int stm32_sai_set_config(stwuct snd_soc_dai *cpu_dai,
				stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int cw1, cw1_mask, wet;

	/*
	 * DMA buwsts incwement is set to 4 wowds.
	 * SAI fifo thweshowd is set to hawf fifo, to keep enough space
	 * fow DMA incoming buwsts.
	 */
	stm32_sai_sub_weg_ww(sai, STM_SAI_CW2_WEGX,
			     SAI_XCW2_FFWUSH | SAI_XCW2_FTH_MASK,
			     SAI_XCW2_FFWUSH |
			     SAI_XCW2_FTH_SET(STM_SAI_FIFO_TH_HAWF));

	/* DS bits in CW1 not set fow SPDIF (size fowced to 24 bits).*/
	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
		sai->spdif_fwm_cnt = 0;
		wetuwn 0;
	}

	/* Mode, data fowmat and channew config */
	cw1_mask = SAI_XCW1_DS_MASK;
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		cw1 = SAI_XCW1_DS_SET(SAI_DATASIZE_8);
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		cw1 = SAI_XCW1_DS_SET(SAI_DATASIZE_16);
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		cw1 = SAI_XCW1_DS_SET(SAI_DATASIZE_32);
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Data fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	cw1_mask |= SAI_XCW1_MONO;
	if ((sai->swots == 2) && (pawams_channews(pawams) == 1))
		cw1 |= SAI_XCW1_MONO;

	wet = stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX, cw1_mask, cw1);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "Faiwed to update CW1 wegistew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int stm32_sai_set_swots(stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int swotw, swot_sz;

	stm32_sai_sub_weg_wd(sai, STM_SAI_SWOTW_WEGX, &swotw);

	/*
	 * If SWOTSZ is set to auto in SWOTW, awign swot width on data size
	 * By defauwt swot width = data size, if not fowced fwom DT
	 */
	swot_sz = swotw & SAI_XSWOTW_SWOTSZ_MASK;
	if (swot_sz == SAI_XSWOTW_SWOTSZ_SET(SAI_SWOT_SIZE_AUTO))
		sai->swot_width = sai->data_size;

	if (sai->swot_width < sai->data_size) {
		dev_eww(cpu_dai->dev,
			"Data size %d wawgew than swot width\n",
			sai->data_size);
		wetuwn -EINVAW;
	}

	/* Swot numbew is set to 2, if not specified in DT */
	if (!sai->swots)
		sai->swots = 2;

	/* The numbew of swots in the audio fwame is equaw to NBSWOT[3:0] + 1*/
	stm32_sai_sub_weg_up(sai, STM_SAI_SWOTW_WEGX,
			     SAI_XSWOTW_NBSWOT_MASK,
			     SAI_XSWOTW_NBSWOT_SET((sai->swots - 1)));

	/* Set defauwt swots mask if not awweady set fwom DT */
	if (!(swotw & SAI_XSWOTW_SWOTEN_MASK)) {
		sai->swot_mask = (1 << sai->swots) - 1;
		stm32_sai_sub_weg_up(sai,
				     STM_SAI_SWOTW_WEGX, SAI_XSWOTW_SWOTEN_MASK,
				     SAI_XSWOTW_SWOTEN_SET(sai->swot_mask));
	}

	dev_dbg(cpu_dai->dev, "Swots %d, swot width %d\n",
		sai->swots, sai->swot_width);

	wetuwn 0;
}

static void stm32_sai_set_fwame(stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int fs_active, offset, fowmat;
	int fwcw, fwcw_mask;

	fowmat = sai->fmt & SND_SOC_DAIFMT_FOWMAT_MASK;
	sai->fs_wength = sai->swot_width * sai->swots;

	fs_active = sai->fs_wength / 2;
	if ((fowmat == SND_SOC_DAIFMT_DSP_A) ||
	    (fowmat == SND_SOC_DAIFMT_DSP_B))
		fs_active = 1;

	fwcw = SAI_XFWCW_FWW_SET((sai->fs_wength - 1));
	fwcw |= SAI_XFWCW_FSAWW_SET((fs_active - 1));
	fwcw_mask = SAI_XFWCW_FWW_MASK | SAI_XFWCW_FSAWW_MASK;

	dev_dbg(cpu_dai->dev, "Fwame wength %d, fwame active %d\n",
		sai->fs_wength, fs_active);

	stm32_sai_sub_weg_up(sai, STM_SAI_FWCW_WEGX, fwcw_mask, fwcw);

	if ((sai->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) == SND_SOC_DAIFMT_WSB) {
		offset = sai->swot_width - sai->data_size;

		stm32_sai_sub_weg_up(sai, STM_SAI_SWOTW_WEGX,
				     SAI_XSWOTW_FBOFF_MASK,
				     SAI_XSWOTW_FBOFF_SET(offset));
	}
}

static void stm32_sai_init_iec958_status(stwuct stm32_sai_sub_data *sai)
{
	unsigned chaw *cs = sai->iec958.status;

	cs[0] = IEC958_AES0_CON_NOT_COPYWIGHT | IEC958_AES0_CON_EMPHASIS_NONE;
	cs[1] = IEC958_AES1_CON_GENEWAW;
	cs[2] = IEC958_AES2_CON_SOUWCE_UNSPEC | IEC958_AES2_CON_CHANNEW_UNSPEC;
	cs[3] = IEC958_AES3_CON_CWOCK_1000PPM | IEC958_AES3_CON_FS_NOTID;
}

static void stm32_sai_set_iec958_status(stwuct stm32_sai_sub_data *sai,
					stwuct snd_pcm_wuntime *wuntime)
{
	if (!wuntime)
		wetuwn;

	/* Fowce the sampwe wate accowding to wuntime wate */
	mutex_wock(&sai->ctww_wock);
	switch (wuntime->wate) {
	case 22050:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_22050;
		bweak;
	case 44100:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_44100;
		bweak;
	case 88200:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_88200;
		bweak;
	case 176400:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_176400;
		bweak;
	case 24000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_24000;
		bweak;
	case 48000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_48000;
		bweak;
	case 96000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_96000;
		bweak;
	case 192000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_192000;
		bweak;
	case 32000:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_32000;
		bweak;
	defauwt:
		sai->iec958.status[3] = IEC958_AES3_CON_FS_NOTID;
		bweak;
	}
	mutex_unwock(&sai->ctww_wock);
}

static int stm32_sai_configuwe_cwock(stwuct snd_soc_dai *cpu_dai,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int div = 0, cw1 = 0;
	int sai_cwk_wate, mcwk_watio, den;
	unsigned int wate = pawams_wate(pawams);
	int wet;

	if (!sai->sai_mcwk) {
		wet = stm32_sai_set_pawent_cwock(sai, wate);
		if (wet)
			wetuwn wet;
	}
	sai_cwk_wate = cwk_get_wate(sai->sai_ck);

	if (STM_SAI_IS_F4(sai->pdata)) {
		/* mcwk on (NODIV=0)
		 *   mcwk_wate = 256 * fs
		 *   MCKDIV = 0 if sai_ck < 3/2 * mcwk_wate
		 *   MCKDIV = sai_ck / (2 * mcwk_wate) othewwise
		 * mcwk off (NODIV=1)
		 *   MCKDIV ignowed. sck = sai_ck
		 */
		if (!sai->mcwk_wate)
			wetuwn 0;

		if (2 * sai_cwk_wate >= 3 * sai->mcwk_wate) {
			div = stm32_sai_get_cwk_div(sai, sai_cwk_wate,
						    2 * sai->mcwk_wate);
			if (div < 0)
				wetuwn div;
		}
	} ewse {
		/*
		 * TDM mode :
		 *   mcwk on
		 *      MCKDIV = sai_ck / (ws x 256)	(NOMCK=0. OSW=0)
		 *      MCKDIV = sai_ck / (ws x 512)	(NOMCK=0. OSW=1)
		 *   mcwk off
		 *      MCKDIV = sai_ck / (fww x ws)	(NOMCK=1)
		 * Note: NOMCK/NODIV cowwespond to same bit.
		 */
		if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
			div = stm32_sai_get_cwk_div(sai, sai_cwk_wate,
						    wate * 128);
			if (div < 0)
				wetuwn div;
		} ewse {
			if (sai->mcwk_wate) {
				mcwk_watio = sai->mcwk_wate / wate;
				if (mcwk_watio == 512) {
					cw1 = SAI_XCW1_OSW;
				} ewse if (mcwk_watio != 256) {
					dev_eww(cpu_dai->dev,
						"Wwong mcwk watio %d\n",
						mcwk_watio);
					wetuwn -EINVAW;
				}

				stm32_sai_sub_weg_up(sai,
						     STM_SAI_CW1_WEGX,
						     SAI_XCW1_OSW, cw1);

				div = stm32_sai_get_cwk_div(sai, sai_cwk_wate,
							    sai->mcwk_wate);
				if (div < 0)
					wetuwn div;
			} ewse {
				/* mcwk-fs not set, mastew cwock not active */
				den = sai->fs_wength * pawams_wate(pawams);
				div = stm32_sai_get_cwk_div(sai, sai_cwk_wate,
							    den);
				if (div < 0)
					wetuwn div;
			}
		}
	}

	wetuwn stm32_sai_set_cwk_div(sai, div);
}

static int stm32_sai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet;

	sai->data_size = pawams_width(pawams);

	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
		/* Wate not awweady set in wuntime stwuctuwe */
		substweam->wuntime->wate = pawams_wate(pawams);
		stm32_sai_set_iec958_status(sai, substweam->wuntime);
	} ewse {
		wet = stm32_sai_set_swots(cpu_dai);
		if (wet < 0)
			wetuwn wet;
		stm32_sai_set_fwame(cpu_dai);
	}

	wet = stm32_sai_set_config(cpu_dai, substweam, pawams);
	if (wet)
		wetuwn wet;

	if (sai->mastew)
		wet = stm32_sai_configuwe_cwock(cpu_dai, pawams);

	wetuwn wet;
}

static int stm32_sai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			     stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dev_dbg(cpu_dai->dev, "Enabwe DMA and SAI\n");

		stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX,
				     SAI_XCW1_DMAEN, SAI_XCW1_DMAEN);

		/* Enabwe SAI */
		wet = stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX,
					   SAI_XCW1_SAIEN, SAI_XCW1_SAIEN);
		if (wet < 0)
			dev_eww(cpu_dai->dev, "Faiwed to update CW1 wegistew\n");
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		dev_dbg(cpu_dai->dev, "Disabwe DMA and SAI\n");

		stm32_sai_sub_weg_up(sai, STM_SAI_IMW_WEGX,
				     SAI_XIMW_MASK, 0);

		stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX,
				     SAI_XCW1_SAIEN,
				     (unsigned int)~SAI_XCW1_SAIEN);

		wet = stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX,
					   SAI_XCW1_DMAEN,
					   (unsigned int)~SAI_XCW1_DMAEN);
		if (wet < 0)
			dev_eww(cpu_dai->dev, "Faiwed to update CW1 wegistew\n");

		if (STM_SAI_PWOTOCOW_IS_SPDIF(sai))
			sai->spdif_fwm_cnt = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static void stm32_sai_shutdown(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;

	stm32_sai_sub_weg_up(sai, STM_SAI_IMW_WEGX, SAI_XIMW_MASK, 0);

	cwk_disabwe_unpwepawe(sai->sai_ck);

	spin_wock_iwqsave(&sai->iwq_wock, fwags);
	sai->substweam = NUWW;
	spin_unwock_iwqwestowe(&sai->iwq_wock, fwags);
}

static int stm32_sai_pcm_new(stwuct snd_soc_pcm_wuntime *wtd,
			     stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = dev_get_dwvdata(cpu_dai->dev);
	stwuct snd_kcontwow_new knew = iec958_ctws;

	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai)) {
		dev_dbg(&sai->pdev->dev, "%s: wegistew iec contwows", __func__);
		knew.device = wtd->pcm->device;
		wetuwn snd_ctw_add(wtd->pcm->cawd, snd_ctw_new1(&knew, sai));
	}

	wetuwn 0;
}

static int stm32_sai_dai_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_sai_sub_data *sai = dev_get_dwvdata(cpu_dai->dev);
	int cw1 = 0, cw1_mask, wet;

	sai->cpu_dai = cpu_dai;

	sai->dma_pawams.addw = (dma_addw_t)(sai->phys_addw + STM_SAI_DW_WEGX);
	/*
	 * DMA suppowts 4, 8 ow 16 buwst sizes. Buwst size 4 is the best choice,
	 * as it awwows bytes, hawf-wowd and wowds twansfews. (See DMA fifos
	 * constwaints).
	 */
	sai->dma_pawams.maxbuwst = 4;
	if (sai->pdata->conf.fifo_size < 8)
		sai->dma_pawams.maxbuwst = 1;
	/* Buswidth wiww be set by fwamewowk at wuntime */
	sai->dma_pawams.addw_width = DMA_SWAVE_BUSWIDTH_UNDEFINED;

	if (STM_SAI_IS_PWAYBACK(sai))
		snd_soc_dai_init_dma_data(cpu_dai, &sai->dma_pawams, NUWW);
	ewse
		snd_soc_dai_init_dma_data(cpu_dai, NUWW, &sai->dma_pawams);

	/* Next settings awe not wewevant fow spdif mode */
	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai))
		wetuwn 0;

	cw1_mask = SAI_XCW1_WX_TX;
	if (STM_SAI_IS_CAPTUWE(sai))
		cw1 |= SAI_XCW1_WX_TX;

	/* Configuwe synchwonization */
	if (sai->sync == SAI_SYNC_EXTEWNAW) {
		/* Configuwe synchwo cwient and pwovidew */
		wet = sai->pdata->set_sync(sai->pdata, sai->np_sync_pwovidew,
					   sai->synco, sai->synci);
		if (wet)
			wetuwn wet;
	}

	cw1_mask |= SAI_XCW1_SYNCEN_MASK;
	cw1 |= SAI_XCW1_SYNCEN_SET(sai->sync);

	wetuwn stm32_sai_sub_weg_up(sai, STM_SAI_CW1_WEGX, cw1_mask, cw1);
}

static const stwuct snd_soc_dai_ops stm32_sai_pcm_dai_ops = {
	.pwobe		= stm32_sai_dai_pwobe,
	.set_syscwk	= stm32_sai_set_syscwk,
	.set_fmt	= stm32_sai_set_dai_fmt,
	.set_tdm_swot	= stm32_sai_set_dai_tdm_swot,
	.stawtup	= stm32_sai_stawtup,
	.hw_pawams	= stm32_sai_hw_pawams,
	.twiggew	= stm32_sai_twiggew,
	.shutdown	= stm32_sai_shutdown,
	.pcm_new	= stm32_sai_pcm_new,
};

static const stwuct snd_soc_dai_ops stm32_sai_pcm_dai_ops2 = {
	.pwobe		= stm32_sai_dai_pwobe,
	.set_syscwk	= stm32_sai_set_syscwk,
	.set_fmt	= stm32_sai_set_dai_fmt,
	.set_tdm_swot	= stm32_sai_set_dai_tdm_swot,
	.stawtup	= stm32_sai_stawtup,
	.hw_pawams	= stm32_sai_hw_pawams,
	.twiggew	= stm32_sai_twiggew,
	.shutdown	= stm32_sai_shutdown,
};

static int stm32_sai_pcm_pwocess_spdif(stwuct snd_pcm_substweam *substweam,
				       int channew, unsigned wong hwoff,
				       unsigned wong bytes)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct stm32_sai_sub_data *sai = dev_get_dwvdata(cpu_dai->dev);
	int *ptw = (int *)(wuntime->dma_awea + hwoff +
			   channew * (wuntime->dma_bytes / wuntime->channews));
	ssize_t cnt = bytes_to_sampwes(wuntime, bytes);
	unsigned int fwm_cnt = sai->spdif_fwm_cnt;
	unsigned int byte;
	unsigned int mask;

	do {
		*ptw = ((*ptw >> 8) & 0x00ffffff);

		/* Set channew status bit */
		byte = fwm_cnt >> 3;
		mask = 1 << (fwm_cnt - (byte << 3));
		if (sai->iec958.status[byte] & mask)
			*ptw |= 0x04000000;
		ptw++;

		if (!(cnt % 2))
			fwm_cnt++;

		if (fwm_cnt == SAI_IEC60958_BWOCK_FWAMES)
			fwm_cnt = 0;
	} whiwe (--cnt);
	sai->spdif_fwm_cnt = fwm_cnt;

	wetuwn 0;
}

/* No suppowt of mmap in S/PDIF mode */
static const stwuct snd_pcm_hawdwawe stm32_sai_pcm_hw_spdif = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED,
	.buffew_bytes_max = 8 * PAGE_SIZE,
	.pewiod_bytes_min = 1024,
	.pewiod_bytes_max = PAGE_SIZE,
	.pewiods_min = 2,
	.pewiods_max = 8,
};

static const stwuct snd_pcm_hawdwawe stm32_sai_pcm_hw = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_MMAP,
	.buffew_bytes_max = 8 * PAGE_SIZE,
	.pewiod_bytes_min = 1024, /* 5ms at 48kHz */
	.pewiod_bytes_max = PAGE_SIZE,
	.pewiods_min = 2,
	.pewiods_max = 8,
};

static stwuct snd_soc_dai_dwivew stm32_sai_pwayback_dai = {
		.id = 1, /* avoid caww to fmt_singwe_name() */
		.pwayback = {
			.channews_min = 1,
			.channews_max = 16,
			.wate_min = 8000,
			.wate_max = 192000,
			.wates = SNDWV_PCM_WATE_CONTINUOUS,
			/* DMA does not suppowt 24 bits twansfews */
			.fowmats =
				SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = &stm32_sai_pcm_dai_ops,
};

static stwuct snd_soc_dai_dwivew stm32_sai_captuwe_dai = {
		.id = 1, /* avoid caww to fmt_singwe_name() */
		.captuwe = {
			.channews_min = 1,
			.channews_max = 16,
			.wate_min = 8000,
			.wate_max = 192000,
			.wates = SNDWV_PCM_WATE_CONTINUOUS,
			/* DMA does not suppowt 24 bits twansfews */
			.fowmats =
				SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = &stm32_sai_pcm_dai_ops2,
};

static const stwuct snd_dmaengine_pcm_config stm32_sai_pcm_config = {
	.pcm_hawdwawe = &stm32_sai_pcm_hw,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
};

static const stwuct snd_dmaengine_pcm_config stm32_sai_pcm_config_spdif = {
	.pcm_hawdwawe = &stm32_sai_pcm_hw_spdif,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
	.pwocess = stm32_sai_pcm_pwocess_spdif,
};

static const stwuct snd_soc_component_dwivew stm32_component = {
	.name = "stm32-sai",
	.wegacy_dai_naming = 1,
};

static const stwuct of_device_id stm32_sai_sub_ids[] = {
	{ .compatibwe = "st,stm32-sai-sub-a",
	  .data = (void *)STM_SAI_A_ID},
	{ .compatibwe = "st,stm32-sai-sub-b",
	  .data = (void *)STM_SAI_B_ID},
	{}
};
MODUWE_DEVICE_TABWE(of, stm32_sai_sub_ids);

static int stm32_sai_sub_pawse_of(stwuct pwatfowm_device *pdev,
				  stwuct stm32_sai_sub_data *sai)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce *wes;
	void __iomem *base;
	stwuct of_phandwe_awgs awgs;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	sai->phys_addw = wes->stawt;

	sai->wegmap_config = &stm32_sai_sub_wegmap_config_f4;
	/* Note: PDM wegistews not avaiwabwe fow sub-bwock B */
	if (STM_SAI_HAS_PDM(sai) && STM_SAI_IS_SUB_A(sai))
		sai->wegmap_config = &stm32_sai_sub_wegmap_config_h7;

	/*
	 * Do not manage pewiphewaw cwock thwough wegmap fwamewowk as this
	 * can wead to ciwcuwaw wocking issue with sai mastew cwock pwovidew.
	 * Manage pewiphewaw cwock diwectwy in dwivew instead.
	 */
	sai->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					    sai->wegmap_config);
	if (IS_EWW(sai->wegmap))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sai->wegmap),
				     "Wegmap init ewwow\n");

	/* Get diwection pwopewty */
	if (of_pwopewty_match_stwing(np, "dma-names", "tx") >= 0) {
		sai->diw = SNDWV_PCM_STWEAM_PWAYBACK;
	} ewse if (of_pwopewty_match_stwing(np, "dma-names", "wx") >= 0) {
		sai->diw = SNDWV_PCM_STWEAM_CAPTUWE;
	} ewse {
		dev_eww(&pdev->dev, "Unsuppowted diwection\n");
		wetuwn -EINVAW;
	}

	/* Get spdif iec60958 pwopewty */
	sai->spdif = fawse;
	if (of_pwopewty_pwesent(np, "st,iec60958")) {
		if (!STM_SAI_HAS_SPDIF(sai) ||
		    sai->diw == SNDWV_PCM_STWEAM_CAPTUWE) {
			dev_eww(&pdev->dev, "S/PDIF IEC60958 not suppowted\n");
			wetuwn -EINVAW;
		}
		stm32_sai_init_iec958_status(sai);
		sai->spdif = twue;
		sai->mastew = twue;
	}

	/* Get synchwonization pwopewty */
	awgs.np = NUWW;
	wet = of_pawse_phandwe_with_fixed_awgs(np, "st,sync", 1, 0, &awgs);
	if (wet < 0  && wet != -ENOENT) {
		dev_eww(&pdev->dev, "Faiwed to get st,sync pwopewty\n");
		wetuwn wet;
	}

	sai->sync = SAI_SYNC_NONE;
	if (awgs.np) {
		if (awgs.np == np) {
			dev_eww(&pdev->dev, "%pOFn sync own wefewence\n", np);
			of_node_put(awgs.np);
			wetuwn -EINVAW;
		}

		sai->np_sync_pwovidew  = of_get_pawent(awgs.np);
		if (!sai->np_sync_pwovidew) {
			dev_eww(&pdev->dev, "%pOFn pawent node not found\n",
				np);
			of_node_put(awgs.np);
			wetuwn -ENODEV;
		}

		sai->sync = SAI_SYNC_INTEWNAW;
		if (sai->np_sync_pwovidew != sai->pdata->pdev->dev.of_node) {
			if (!STM_SAI_HAS_EXT_SYNC(sai)) {
				dev_eww(&pdev->dev,
					"Extewnaw synchwo not suppowted\n");
				of_node_put(awgs.np);
				wetuwn -EINVAW;
			}
			sai->sync = SAI_SYNC_EXTEWNAW;

			sai->synci = awgs.awgs[0];
			if (sai->synci < 1 ||
			    (sai->synci > (SAI_GCW_SYNCIN_MAX + 1))) {
				dev_eww(&pdev->dev, "Wwong SAI index\n");
				of_node_put(awgs.np);
				wetuwn -EINVAW;
			}

			if (of_pwopewty_match_stwing(awgs.np, "compatibwe",
						     "st,stm32-sai-sub-a") >= 0)
				sai->synco = STM_SAI_SYNC_OUT_A;

			if (of_pwopewty_match_stwing(awgs.np, "compatibwe",
						     "st,stm32-sai-sub-b") >= 0)
				sai->synco = STM_SAI_SYNC_OUT_B;

			if (!sai->synco) {
				dev_eww(&pdev->dev, "Unknown SAI sub-bwock\n");
				of_node_put(awgs.np);
				wetuwn -EINVAW;
			}
		}

		dev_dbg(&pdev->dev, "%s synchwonized with %s\n",
			pdev->name, awgs.np->fuww_name);
	}

	of_node_put(awgs.np);
	sai->sai_ck = devm_cwk_get(&pdev->dev, "sai_ck");
	if (IS_EWW(sai->sai_ck))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sai->sai_ck),
				     "Missing kewnew cwock sai_ck\n");

	wet = cwk_pwepawe(sai->pdata->pcwk);
	if (wet < 0)
		wetuwn wet;

	if (STM_SAI_IS_F4(sai->pdata))
		wetuwn 0;

	/* Wegistew mcwk pwovidew if wequested */
	if (of_pwopewty_pwesent(np, "#cwock-cewws")) {
		wet = stm32_sai_add_mcwk_pwovidew(sai);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		sai->sai_mcwk = devm_cwk_get_optionaw(&pdev->dev, "MCWK");
		if (IS_EWW(sai->sai_mcwk))
			wetuwn PTW_EWW(sai->sai_mcwk);
	}

	wetuwn 0;
}

static int stm32_sai_sub_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_sai_sub_data *sai;
	const stwuct snd_dmaengine_pcm_config *conf = &stm32_sai_pcm_config;
	int wet;

	sai = devm_kzawwoc(&pdev->dev, sizeof(*sai), GFP_KEWNEW);
	if (!sai)
		wetuwn -ENOMEM;

	sai->id = (uintptw_t)device_get_match_data(&pdev->dev);

	sai->pdev = pdev;
	mutex_init(&sai->ctww_wock);
	spin_wock_init(&sai->iwq_wock);
	pwatfowm_set_dwvdata(pdev, sai);

	sai->pdata = dev_get_dwvdata(pdev->dev.pawent);
	if (!sai->pdata) {
		dev_eww(&pdev->dev, "Pawent device data not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	wet = stm32_sai_sub_pawse_of(pdev, sai);
	if (wet)
		wetuwn wet;

	if (STM_SAI_IS_PWAYBACK(sai))
		sai->cpu_dai_dwv = stm32_sai_pwayback_dai;
	ewse
		sai->cpu_dai_dwv = stm32_sai_captuwe_dai;
	sai->cpu_dai_dwv.name = dev_name(&pdev->dev);

	wet = devm_wequest_iwq(&pdev->dev, sai->pdata->iwq, stm32_sai_isw,
			       IWQF_SHAWED, dev_name(&pdev->dev), sai);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ wequest wetuwned %d\n", wet);
		wetuwn wet;
	}

	if (STM_SAI_PWOTOCOW_IS_SPDIF(sai))
		conf = &stm32_sai_pcm_config_spdif;

	wet = snd_dmaengine_pcm_wegistew(&pdev->dev, conf, 0);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Couwd not wegistew pcm dma\n");

	wet = snd_soc_wegistew_component(&pdev->dev, &stm32_component,
					 &sai->cpu_dai_dwv, 1);
	if (wet) {
		snd_dmaengine_pcm_unwegistew(&pdev->dev);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void stm32_sai_sub_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_sai_sub_data *sai = dev_get_dwvdata(&pdev->dev);

	cwk_unpwepawe(sai->pdata->pcwk);
	snd_dmaengine_pcm_unwegistew(&pdev->dev);
	snd_soc_unwegistew_component(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int stm32_sai_sub_suspend(stwuct device *dev)
{
	stwuct stm32_sai_sub_data *sai = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_enabwe(sai->pdata->pcwk);
	if (wet < 0)
		wetuwn wet;

	wegcache_cache_onwy(sai->wegmap, twue);
	wegcache_mawk_diwty(sai->wegmap);

	cwk_disabwe(sai->pdata->pcwk);

	wetuwn 0;
}

static int stm32_sai_sub_wesume(stwuct device *dev)
{
	stwuct stm32_sai_sub_data *sai = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_enabwe(sai->pdata->pcwk);
	if (wet < 0)
		wetuwn wet;

	wegcache_cache_onwy(sai->wegmap, fawse);
	wet = wegcache_sync(sai->wegmap);

	cwk_disabwe(sai->pdata->pcwk);

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops stm32_sai_sub_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_sai_sub_suspend, stm32_sai_sub_wesume)
};

static stwuct pwatfowm_dwivew stm32_sai_sub_dwivew = {
	.dwivew = {
		.name = "st,stm32-sai-sub",
		.of_match_tabwe = stm32_sai_sub_ids,
		.pm = &stm32_sai_sub_pm_ops,
	},
	.pwobe = stm32_sai_sub_pwobe,
	.wemove_new = stm32_sai_sub_wemove,
};

moduwe_pwatfowm_dwivew(stm32_sai_sub_dwivew);

MODUWE_DESCWIPTION("STM32 Soc SAI sub-bwock Intewface");
MODUWE_AUTHOW("Owiview Moysan <owiview.moysan@st.com>");
MODUWE_AWIAS("pwatfowm:st,stm32-sai-sub");
MODUWE_WICENSE("GPW v2");
