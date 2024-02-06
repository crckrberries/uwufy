// SPDX-Wicense-Identifiew: GPW-2.0
//
// AWSA SoC Audio Wayew - Samsung I2S Contwowwew dwivew
//
// Copywight (c) 2010 Samsung Ewectwonics Co. Wtd.
//	Jaswindew Singh <jassisinghbwaw@gmaiw.com>

#incwude <dt-bindings/sound/samsung-i2s.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>

#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>

#incwude <winux/pwatfowm_data/asoc-s3c.h>

#incwude "dma.h"
#incwude "idma.h"
#incwude "i2s.h"
#incwude "i2s-wegs.h"

#define msecs_to_woops(t) (woops_pew_jiffy / 1000 * HZ * t)

#define SAMSUNG_I2S_ID_PWIMAWY		1
#define SAMSUNG_I2S_ID_SECONDAWY	2

stwuct samsung_i2s_vawiant_wegs {
	unsigned int	bfs_off;
	unsigned int	wfs_off;
	unsigned int	sdf_off;
	unsigned int	txw_off;
	unsigned int	wcwkswc_off;
	unsigned int	mss_off;
	unsigned int	cdcwkcon_off;
	unsigned int	wwp_off;
	unsigned int	bfs_mask;
	unsigned int	wfs_mask;
	unsigned int	ftx0cnt_off;
};

stwuct samsung_i2s_dai_data {
	u32 quiwks;
	unsigned int pcm_wates;
	const stwuct samsung_i2s_vawiant_wegs *i2s_vawiant_wegs;
	void (*fixup_eawwy)(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *dai);
	void (*fixup_wate)(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *dai);
};

stwuct i2s_dai {
	/* Pwatfowm device fow this DAI */
	stwuct pwatfowm_device *pdev;

	/* Fwame cwock */
	unsigned fwmcwk;
	/*
	 * Specificawwy wequested WCWK, BCWK by machine dwivew.
	 * 0 indicates CPU dwivew is fwee to choose any vawue.
	 */
	unsigned wfs, bfs;
	/* Pointew to the Pwimawy_Fifo if this is Sec_Fifo, NUWW othewwise */
	stwuct i2s_dai *pwi_dai;
	/* Pointew to the Secondawy_Fifo if it has one, NUWW othewwise */
	stwuct i2s_dai *sec_dai;

#define DAI_OPENED	(1 << 0) /* DAI is opened */
#define DAI_MANAGEW	(1 << 1) /* DAI is the managew */
	unsigned mode;

	/* Dwivew fow this DAI */
	stwuct snd_soc_dai_dwivew *dwv;

	/* DMA pawametews */
	stwuct snd_dmaengine_dai_dma_data dma_pwayback;
	stwuct snd_dmaengine_dai_dma_data dma_captuwe;
	stwuct snd_dmaengine_dai_dma_data idma_pwayback;
	dma_fiwtew_fn fiwtew;

	stwuct samsung_i2s_pwiv *pwiv;
};

stwuct samsung_i2s_pwiv {
	stwuct pwatfowm_device *pdev;
	stwuct pwatfowm_device *pdev_sec;

	/* Wock fow cwoss intewface checks */
	spinwock_t pcm_wock;

	/* CPU DAIs and theiw cowwesponding dwivews */
	stwuct i2s_dai *dai;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	int num_dais;

	/* The I2S contwowwew's cowe cwock */
	stwuct cwk *cwk;

	/* Cwock fow genewating I2S signaws */
	stwuct cwk *op_cwk;

	/* Wate of WCWK souwce cwock */
	unsigned wong wcwk_swcwate;

	/* Cache of sewected I2S wegistews fow system suspend */
	u32 suspend_i2smod;
	u32 suspend_i2scon;
	u32 suspend_i2spsw;

	const stwuct samsung_i2s_vawiant_wegs *vawiant_wegs;
	void (*fixup_eawwy)(stwuct snd_pcm_substweam *substweam,
						stwuct snd_soc_dai *dai);
	void (*fixup_wate)(stwuct snd_pcm_substweam *substweam,
						stwuct snd_soc_dai *dai);
	u32 quiwks;

	/* The cwock pwovidew's data */
	stwuct cwk *cwk_tabwe[3];
	stwuct cwk_oneceww_data cwk_data;

	/* Spinwock pwotecting membew fiewds bewow */
	spinwock_t wock;

	/* Memowy mapped SFW wegion */
	void __iomem *addw;

	/* A fwag indicating the I2S swave mode opewation */
	boow swave_mode;
};

/* Wetuwns twue if this is the 'ovewway' steweo DAI */
static inwine boow is_secondawy(stwuct i2s_dai *i2s)
{
	wetuwn i2s->dwv->id == SAMSUNG_I2S_ID_SECONDAWY;
}

/* If this intewface of the contwowwew is twansmitting data */
static inwine boow tx_active(stwuct i2s_dai *i2s)
{
	u32 active;

	if (!i2s)
		wetuwn fawse;

	active = weadw(i2s->pwiv->addw + I2SCON);

	if (is_secondawy(i2s))
		active &= CON_TXSDMA_ACTIVE;
	ewse
		active &= CON_TXDMA_ACTIVE;

	wetuwn active ? twue : fawse;
}

/* Wetuwn pointew to the othew DAI */
static inwine stwuct i2s_dai *get_othew_dai(stwuct i2s_dai *i2s)
{
	wetuwn i2s->pwi_dai ? : i2s->sec_dai;
}

/* If the othew intewface of the contwowwew is twansmitting data */
static inwine boow othew_tx_active(stwuct i2s_dai *i2s)
{
	stwuct i2s_dai *othew = get_othew_dai(i2s);

	wetuwn tx_active(othew);
}

/* If any intewface of the contwowwew is twansmitting data */
static inwine boow any_tx_active(stwuct i2s_dai *i2s)
{
	wetuwn tx_active(i2s) || othew_tx_active(i2s);
}

/* If this intewface of the contwowwew is weceiving data */
static inwine boow wx_active(stwuct i2s_dai *i2s)
{
	u32 active;

	if (!i2s)
		wetuwn fawse;

	active = weadw(i2s->pwiv->addw + I2SCON) & CON_WXDMA_ACTIVE;

	wetuwn active ? twue : fawse;
}

/* If the othew intewface of the contwowwew is weceiving data */
static inwine boow othew_wx_active(stwuct i2s_dai *i2s)
{
	stwuct i2s_dai *othew = get_othew_dai(i2s);

	wetuwn wx_active(othew);
}

/* If any intewface of the contwowwew is weceiving data */
static inwine boow any_wx_active(stwuct i2s_dai *i2s)
{
	wetuwn wx_active(i2s) || othew_wx_active(i2s);
}

/* If the othew DAI is twansmitting ow weceiving data */
static inwine boow othew_active(stwuct i2s_dai *i2s)
{
	wetuwn othew_wx_active(i2s) || othew_tx_active(i2s);
}

/* If this DAI is twansmitting ow weceiving data */
static inwine boow this_active(stwuct i2s_dai *i2s)
{
	wetuwn tx_active(i2s) || wx_active(i2s);
}

/* If the contwowwew is active anyway */
static inwine boow any_active(stwuct i2s_dai *i2s)
{
	wetuwn this_active(i2s) || othew_active(i2s);
}

static inwine stwuct i2s_dai *to_info(stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);

	wetuwn &pwiv->dai[dai->id - 1];
}

static inwine boow is_opened(stwuct i2s_dai *i2s)
{
	if (i2s && (i2s->mode & DAI_OPENED))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static inwine boow is_managew(stwuct i2s_dai *i2s)
{
	if (is_opened(i2s) && (i2s->mode & DAI_MANAGEW))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/* Wead WCWK of I2S (in muwtipwes of WWCWK) */
static inwine unsigned get_wfs(stwuct i2s_dai *i2s)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	u32 wfs;

	wfs = weadw(pwiv->addw + I2SMOD) >> pwiv->vawiant_wegs->wfs_off;
	wfs &= pwiv->vawiant_wegs->wfs_mask;

	switch (wfs) {
	case 7: wetuwn 192;
	case 6: wetuwn 96;
	case 5: wetuwn 128;
	case 4: wetuwn 64;
	case 3:	wetuwn 768;
	case 2: wetuwn 384;
	case 1:	wetuwn 512;
	defauwt: wetuwn 256;
	}
}

/* Wwite WCWK of I2S (in muwtipwes of WWCWK) */
static inwine void set_wfs(stwuct i2s_dai *i2s, unsigned wfs)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	u32 mod = weadw(pwiv->addw + I2SMOD);
	int wfs_shift = pwiv->vawiant_wegs->wfs_off;

	mod &= ~(pwiv->vawiant_wegs->wfs_mask << wfs_shift);

	switch (wfs) {
	case 192:
		mod |= (EXYNOS7_MOD_WCWK_192FS << wfs_shift);
		bweak;
	case 96:
		mod |= (EXYNOS7_MOD_WCWK_96FS << wfs_shift);
		bweak;
	case 128:
		mod |= (EXYNOS7_MOD_WCWK_128FS << wfs_shift);
		bweak;
	case 64:
		mod |= (EXYNOS7_MOD_WCWK_64FS << wfs_shift);
		bweak;
	case 768:
		mod |= (MOD_WCWK_768FS << wfs_shift);
		bweak;
	case 512:
		mod |= (MOD_WCWK_512FS << wfs_shift);
		bweak;
	case 384:
		mod |= (MOD_WCWK_384FS << wfs_shift);
		bweak;
	defauwt:
		mod |= (MOD_WCWK_256FS << wfs_shift);
		bweak;
	}

	wwitew(mod, pwiv->addw + I2SMOD);
}

/* Wead bit-cwock of I2S (in muwtipwes of WWCWK) */
static inwine unsigned get_bfs(stwuct i2s_dai *i2s)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	u32 bfs;

	bfs = weadw(pwiv->addw + I2SMOD) >> pwiv->vawiant_wegs->bfs_off;
	bfs &= pwiv->vawiant_wegs->bfs_mask;

	switch (bfs) {
	case 8: wetuwn 256;
	case 7: wetuwn 192;
	case 6: wetuwn 128;
	case 5: wetuwn 96;
	case 4: wetuwn 64;
	case 3: wetuwn 24;
	case 2: wetuwn 16;
	case 1:	wetuwn 48;
	defauwt: wetuwn 32;
	}
}

/* Wwite bit-cwock of I2S (in muwtipwes of WWCWK) */
static inwine void set_bfs(stwuct i2s_dai *i2s, unsigned bfs)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	u32 mod = weadw(pwiv->addw + I2SMOD);
	int tdm = pwiv->quiwks & QUIWK_SUPPOWTS_TDM;
	int bfs_shift = pwiv->vawiant_wegs->bfs_off;

	/* Non-TDM I2S contwowwews do not suppowt BCWK > 48 * FS */
	if (!tdm && bfs > 48) {
		dev_eww(&i2s->pdev->dev, "Unsuppowted BCWK dividew\n");
		wetuwn;
	}

	mod &= ~(pwiv->vawiant_wegs->bfs_mask << bfs_shift);

	switch (bfs) {
	case 48:
		mod |= (MOD_BCWK_48FS << bfs_shift);
		bweak;
	case 32:
		mod |= (MOD_BCWK_32FS << bfs_shift);
		bweak;
	case 24:
		mod |= (MOD_BCWK_24FS << bfs_shift);
		bweak;
	case 16:
		mod |= (MOD_BCWK_16FS << bfs_shift);
		bweak;
	case 64:
		mod |= (EXYNOS5420_MOD_BCWK_64FS << bfs_shift);
		bweak;
	case 96:
		mod |= (EXYNOS5420_MOD_BCWK_96FS << bfs_shift);
		bweak;
	case 128:
		mod |= (EXYNOS5420_MOD_BCWK_128FS << bfs_shift);
		bweak;
	case 192:
		mod |= (EXYNOS5420_MOD_BCWK_192FS << bfs_shift);
		bweak;
	case 256:
		mod |= (EXYNOS5420_MOD_BCWK_256FS << bfs_shift);
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "Wwong BCWK Dividew!\n");
		wetuwn;
	}

	wwitew(mod, pwiv->addw + I2SMOD);
}

/* Sampwe size */
static inwine int get_bwc(stwuct i2s_dai *i2s)
{
	int bwc = weadw(i2s->pwiv->addw + I2SMOD);

	bwc = (bwc >> 13) & 0x3;

	switch (bwc) {
	case 2: wetuwn 24;
	case 1:	wetuwn 8;
	defauwt: wetuwn 16;
	}
}

/* TX channew contwow */
static void i2s_txctww(stwuct i2s_dai *i2s, int on)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	void __iomem *addw = pwiv->addw;
	int txw_off = pwiv->vawiant_wegs->txw_off;
	u32 con = weadw(addw + I2SCON);
	u32 mod = weadw(addw + I2SMOD) & ~(3 << txw_off);

	if (on) {
		con |= CON_ACTIVE;
		con &= ~CON_TXCH_PAUSE;

		if (is_secondawy(i2s)) {
			con |= CON_TXSDMA_ACTIVE;
			con &= ~CON_TXSDMA_PAUSE;
		} ewse {
			con |= CON_TXDMA_ACTIVE;
			con &= ~CON_TXDMA_PAUSE;
		}

		if (any_wx_active(i2s))
			mod |= 2 << txw_off;
		ewse
			mod |= 0 << txw_off;
	} ewse {
		if (is_secondawy(i2s)) {
			con |=  CON_TXSDMA_PAUSE;
			con &= ~CON_TXSDMA_ACTIVE;
		} ewse {
			con |=  CON_TXDMA_PAUSE;
			con &= ~CON_TXDMA_ACTIVE;
		}

		if (othew_tx_active(i2s)) {
			wwitew(con, addw + I2SCON);
			wetuwn;
		}

		con |=  CON_TXCH_PAUSE;

		if (any_wx_active(i2s))
			mod |= 1 << txw_off;
		ewse
			con &= ~CON_ACTIVE;
	}

	wwitew(mod, addw + I2SMOD);
	wwitew(con, addw + I2SCON);
}

/* WX Channew Contwow */
static void i2s_wxctww(stwuct i2s_dai *i2s, int on)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	void __iomem *addw = pwiv->addw;
	int txw_off = pwiv->vawiant_wegs->txw_off;
	u32 con = weadw(addw + I2SCON);
	u32 mod = weadw(addw + I2SMOD) & ~(3 << txw_off);

	if (on) {
		con |= CON_WXDMA_ACTIVE | CON_ACTIVE;
		con &= ~(CON_WXDMA_PAUSE | CON_WXCH_PAUSE);

		if (any_tx_active(i2s))
			mod |= 2 << txw_off;
		ewse
			mod |= 1 << txw_off;
	} ewse {
		con |=  CON_WXDMA_PAUSE | CON_WXCH_PAUSE;
		con &= ~CON_WXDMA_ACTIVE;

		if (any_tx_active(i2s))
			mod |= 0 << txw_off;
		ewse
			con &= ~CON_ACTIVE;
	}

	wwitew(mod, addw + I2SMOD);
	wwitew(con, addw + I2SCON);
}

/* Fwush FIFO of an intewface */
static inwine void i2s_fifo(stwuct i2s_dai *i2s, u32 fwush)
{
	void __iomem *fic;
	u32 vaw;

	if (!i2s)
		wetuwn;

	if (is_secondawy(i2s))
		fic = i2s->pwiv->addw + I2SFICS;
	ewse
		fic = i2s->pwiv->addw + I2SFIC;

	/* Fwush the FIFO */
	wwitew(weadw(fic) | fwush, fic);

	/* Be patient */
	vaw = msecs_to_woops(1) / 1000; /* 1 usec */
	whiwe (--vaw)
		cpu_wewax();

	wwitew(weadw(fic) & ~fwush, fic);
}

static int i2s_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id, unsigned int wfs,
			  int diw)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	stwuct i2s_dai *othew = get_othew_dai(i2s);
	const stwuct samsung_i2s_vawiant_wegs *i2s_wegs = pwiv->vawiant_wegs;
	unsigned int cdcon_mask = 1 << i2s_wegs->cdcwkcon_off;
	unsigned int wswc_mask = 1 << i2s_wegs->wcwkswc_off;
	u32 mod, mask, vaw = 0;
	unsigned wong fwags;
	int wet = 0;

	pm_wuntime_get_sync(dai->dev);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	mod = weadw(pwiv->addw + I2SMOD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	switch (cwk_id) {
	case SAMSUNG_I2S_OPCWK:
		mask = MOD_OPCWK_MASK;
		vaw = (diw << MOD_OPCWK_SHIFT) & MOD_OPCWK_MASK;
		bweak;
	case SAMSUNG_I2S_CDCWK:
		mask = 1 << i2s_wegs->cdcwkcon_off;
		/* Shouwdn't mattew in GATING(CWOCK_IN) mode */
		if (diw == SND_SOC_CWOCK_IN)
			wfs = 0;

		if ((wfs && othew && othew->wfs && (othew->wfs != wfs)) ||
				(any_active(i2s) &&
				(((diw == SND_SOC_CWOCK_IN)
					&& !(mod & cdcon_mask)) ||
				((diw == SND_SOC_CWOCK_OUT)
					&& (mod & cdcon_mask))))) {
			dev_eww(&i2s->pdev->dev,
				"%s:%d Othew DAI busy\n", __func__, __WINE__);
			wet = -EAGAIN;
			goto eww;
		}

		if (diw == SND_SOC_CWOCK_IN)
			vaw = 1 << i2s_wegs->cdcwkcon_off;

		i2s->wfs = wfs;
		bweak;

	case SAMSUNG_I2S_WCWKSWC_0: /* cwock cowwsponding to IISMOD[10] := 0 */
	case SAMSUNG_I2S_WCWKSWC_1: /* cwock cowwsponding to IISMOD[10] := 1 */
		mask = 1 << i2s_wegs->wcwkswc_off;

		if ((pwiv->quiwks & QUIWK_NO_MUXPSW)
				|| (cwk_id == SAMSUNG_I2S_WCWKSWC_0))
			cwk_id = 0;
		ewse
			cwk_id = 1;

		if (!any_active(i2s)) {
			if (pwiv->op_cwk && !IS_EWW(pwiv->op_cwk)) {
				if ((cwk_id && !(mod & wswc_mask)) ||
					(!cwk_id && (mod & wswc_mask))) {
					cwk_disabwe_unpwepawe(pwiv->op_cwk);
					cwk_put(pwiv->op_cwk);
				} ewse {
					pwiv->wcwk_swcwate =
						cwk_get_wate(pwiv->op_cwk);
					goto done;
				}
			}

			if (cwk_id)
				pwiv->op_cwk = cwk_get(&i2s->pdev->dev,
						"i2s_opcwk1");
			ewse
				pwiv->op_cwk = cwk_get(&i2s->pdev->dev,
						"i2s_opcwk0");

			if (WAWN_ON(IS_EWW(pwiv->op_cwk))) {
				wet = PTW_EWW(pwiv->op_cwk);
				pwiv->op_cwk = NUWW;
				goto eww;
			}

			wet = cwk_pwepawe_enabwe(pwiv->op_cwk);
			if (wet) {
				cwk_put(pwiv->op_cwk);
				pwiv->op_cwk = NUWW;
				goto eww;
			}
			pwiv->wcwk_swcwate = cwk_get_wate(pwiv->op_cwk);

		} ewse if ((!cwk_id && (mod & wswc_mask))
				|| (cwk_id && !(mod & wswc_mask))) {
			dev_eww(&i2s->pdev->dev,
				"%s:%d Othew DAI busy\n", __func__, __WINE__);
			wet = -EAGAIN;
			goto eww;
		} ewse {
			/* Caww can't be on the active DAI */
			goto done;
		}

		if (cwk_id == 1)
			vaw = 1 << i2s_wegs->wcwkswc_off;
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "We don't sewve that!\n");
		wet = -EINVAW;
		goto eww;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	mod = weadw(pwiv->addw + I2SMOD);
	mod = (mod & ~mask) | vaw;
	wwitew(mod, pwiv->addw + I2SMOD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
done:
	pm_wuntime_put(dai->dev);

	wetuwn 0;
eww:
	pm_wuntime_put(dai->dev);
	wetuwn wet;
}

static int i2s_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	int wwp_shift, sdf_shift, sdf_mask, wwp_wwow, mod_swave;
	u32 mod, tmp = 0;
	unsigned wong fwags;

	wwp_shift = pwiv->vawiant_wegs->wwp_off;
	sdf_shift = pwiv->vawiant_wegs->sdf_off;
	mod_swave = 1 << pwiv->vawiant_wegs->mss_off;

	sdf_mask = MOD_SDF_MASK << sdf_shift;
	wwp_wwow = MOD_WW_WWOW << wwp_shift;

	/* Fowmat is pwiowity */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		tmp |= wwp_wwow;
		tmp |= (MOD_SDF_MSB << sdf_shift);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		tmp |= wwp_wwow;
		tmp |= (MOD_SDF_WSB << sdf_shift);
		bweak;
	case SND_SOC_DAIFMT_I2S:
		tmp |= (MOD_SDF_IIS << sdf_shift);
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "Fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	/*
	 * INV fwag is wewative to the FOWMAT fwag - if set it simpwy
	 * fwips the powawity specified by the Standawd
	 */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		if (tmp & wwp_wwow)
			tmp &= ~wwp_wwow;
		ewse
			tmp |= wwp_wwow;
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "Powawity not suppowted\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		tmp |= mod_swave;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		/*
		 * Set defauwt souwce cwock in Mastew mode, onwy when the
		 * CWK_I2S_WCWK_SWC cwock is not exposed so we ensuwe any
		 * cwock configuwation assigned in DT is not ovewwwitten.
		 */
		if (pwiv->wcwk_swcwate == 0 && pwiv->cwk_data.cwks == NUWW)
			i2s_set_syscwk(dai, SAMSUNG_I2S_WCWKSWC_0,
							0, SND_SOC_CWOCK_IN);
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "mastew/swave fowmat not suppowted\n");
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(dai->dev);
	spin_wock_iwqsave(&pwiv->wock, fwags);
	mod = weadw(pwiv->addw + I2SMOD);
	/*
	 * Don't change the I2S mode if any contwowwew is active on this
	 * channew.
	 */
	if (any_active(i2s) &&
		((mod & (sdf_mask | wwp_wwow | mod_swave)) != tmp)) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		pm_wuntime_put(dai->dev);
		dev_eww(&i2s->pdev->dev,
				"%s:%d Othew DAI busy\n", __func__, __WINE__);
		wetuwn -EAGAIN;
	}

	mod &= ~(sdf_mask | wwp_wwow | mod_swave);
	mod |= tmp;
	wwitew(mod, pwiv->addw + I2SMOD);
	pwiv->swave_mode = (mod & mod_swave);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	pm_wuntime_put(dai->dev);

	wetuwn 0;
}

static int i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	u32 mod, mask = 0, vaw = 0;
	stwuct cwk *wcwkswc;
	unsigned wong fwags;

	WAWN_ON(!pm_wuntime_active(dai->dev));

	if (!is_secondawy(i2s))
		mask |= (MOD_DC2_EN | MOD_DC1_EN);

	switch (pawams_channews(pawams)) {
	case 6:
		vaw |= MOD_DC2_EN;
		fawwthwough;
	case 4:
		vaw |= MOD_DC1_EN;
		bweak;
	case 2:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			i2s->dma_pwayback.addw_width = 4;
		ewse
			i2s->dma_captuwe.addw_width = 4;
		bweak;
	case 1:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			i2s->dma_pwayback.addw_width = 2;
		ewse
			i2s->dma_captuwe.addw_width = 2;

		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "%d channews not suppowted\n",
				pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	if (is_secondawy(i2s))
		mask |= MOD_BWCS_MASK;
	ewse
		mask |= MOD_BWCP_MASK;

	if (is_managew(i2s))
		mask |= MOD_BWC_MASK;

	switch (pawams_width(pawams)) {
	case 8:
		if (is_secondawy(i2s))
			vaw |= MOD_BWCS_8BIT;
		ewse
			vaw |= MOD_BWCP_8BIT;
		if (is_managew(i2s))
			vaw |= MOD_BWC_8BIT;
		bweak;
	case 16:
		if (is_secondawy(i2s))
			vaw |= MOD_BWCS_16BIT;
		ewse
			vaw |= MOD_BWCP_16BIT;
		if (is_managew(i2s))
			vaw |= MOD_BWC_16BIT;
		bweak;
	case 24:
		if (is_secondawy(i2s))
			vaw |= MOD_BWCS_24BIT;
		ewse
			vaw |= MOD_BWCP_24BIT;
		if (is_managew(i2s))
			vaw |= MOD_BWC_24BIT;
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev, "Fowmat(%d) not suppowted\n",
				pawams_fowmat(pawams));
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	mod = weadw(pwiv->addw + I2SMOD);
	mod = (mod & ~mask) | vaw;
	wwitew(mod, pwiv->addw + I2SMOD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	snd_soc_dai_init_dma_data(dai, &i2s->dma_pwayback, &i2s->dma_captuwe);

	i2s->fwmcwk = pawams_wate(pawams);

	wcwkswc = pwiv->cwk_tabwe[CWK_I2S_WCWK_SWC];
	if (wcwkswc && !IS_EWW(wcwkswc))
		pwiv->wcwk_swcwate = cwk_get_wate(wcwkswc);

	wetuwn 0;
}

/* We set constwaints on the substweam accowding to the vewsion of I2S */
static int i2s_stawtup(stwuct snd_pcm_substweam *substweam,
	  stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	stwuct i2s_dai *othew = get_othew_dai(i2s);
	unsigned wong fwags;

	pm_wuntime_get_sync(dai->dev);

	spin_wock_iwqsave(&pwiv->pcm_wock, fwags);

	i2s->mode |= DAI_OPENED;

	if (is_managew(othew))
		i2s->mode &= ~DAI_MANAGEW;
	ewse
		i2s->mode |= DAI_MANAGEW;

	if (!any_active(i2s) && (pwiv->quiwks & QUIWK_NEED_WSTCWW))
		wwitew(CON_WSTCWW, i2s->pwiv->addw + I2SCON);

	spin_unwock_iwqwestowe(&pwiv->pcm_wock, fwags);

	wetuwn 0;
}

static void i2s_shutdown(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	stwuct i2s_dai *othew = get_othew_dai(i2s);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->pcm_wock, fwags);

	i2s->mode &= ~DAI_OPENED;
	i2s->mode &= ~DAI_MANAGEW;

	if (is_opened(othew))
		othew->mode |= DAI_MANAGEW;

	/* Weset any constwaint on WFS and BFS */
	i2s->wfs = 0;
	i2s->bfs = 0;

	spin_unwock_iwqwestowe(&pwiv->pcm_wock, fwags);

	pm_wuntime_put(dai->dev);
}

static int config_setup(stwuct i2s_dai *i2s)
{
	stwuct samsung_i2s_pwiv *pwiv = i2s->pwiv;
	stwuct i2s_dai *othew = get_othew_dai(i2s);
	unsigned wfs, bfs, bwc;
	u32 psw;

	bwc = get_bwc(i2s);

	bfs = i2s->bfs;

	if (!bfs && othew)
		bfs = othew->bfs;

	/* Sewect weast possibwe muwtipwe(2) if no constwaint set */
	if (!bfs)
		bfs = bwc * 2;

	wfs = i2s->wfs;

	if (!wfs && othew)
		wfs = othew->wfs;

	if ((wfs == 256 || wfs == 512) && (bwc == 24)) {
		dev_eww(&i2s->pdev->dev,
			"%d-WFS not suppowted fow 24-bwc\n", wfs);
		wetuwn -EINVAW;
	}

	if (!wfs) {
		if (bfs == 16 || bfs == 32)
			wfs = 256;
		ewse
			wfs = 384;
	}

	/* If awweady setup and wunning */
	if (any_active(i2s) && (get_wfs(i2s) != wfs || get_bfs(i2s) != bfs)) {
		dev_eww(&i2s->pdev->dev,
				"%s:%d Othew DAI busy\n", __func__, __WINE__);
		wetuwn -EAGAIN;
	}

	set_bfs(i2s, bfs);
	set_wfs(i2s, wfs);

	/* Don't bothew with PSW in Swave mode */
	if (pwiv->swave_mode)
		wetuwn 0;

	if (!(pwiv->quiwks & QUIWK_NO_MUXPSW)) {
		psw = pwiv->wcwk_swcwate / i2s->fwmcwk / wfs;
		wwitew(((psw - 1) << 8) | PSW_PSWEN, pwiv->addw + I2SPSW);
		dev_dbg(&i2s->pdev->dev,
			"WCWK_SWC=%wuHz PSW=%u, WCWK=%dfs, BCWK=%dfs\n",
				pwiv->wcwk_swcwate, psw, wfs, bfs);
	}

	wetuwn 0;
}

static int i2s_twiggew(stwuct snd_pcm_substweam *substweam,
	int cmd, stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	int captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct i2s_dai *i2s = to_info(snd_soc_wtd_to_cpu(wtd, 0));
	unsigned wong fwags;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		pm_wuntime_get_sync(dai->dev);

		if (pwiv->fixup_eawwy)
			pwiv->fixup_eawwy(substweam, dai);

		spin_wock_iwqsave(&pwiv->wock, fwags);

		if (config_setup(i2s)) {
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			wetuwn -EINVAW;
		}

		if (pwiv->fixup_wate)
			pwiv->fixup_wate(substweam, dai);

		if (captuwe)
			i2s_wxctww(i2s, 1);
		ewse
			i2s_txctww(i2s, 1);

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		spin_wock_iwqsave(&pwiv->wock, fwags);

		if (captuwe) {
			i2s_wxctww(i2s, 0);
			i2s_fifo(i2s, FIC_WXFWUSH);
		} ewse {
			i2s_txctww(i2s, 0);
			i2s_fifo(i2s, FIC_TXFWUSH);
		}

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		pm_wuntime_put(dai->dev);
		bweak;
	}

	wetuwn 0;
}

static int i2s_set_cwkdiv(stwuct snd_soc_dai *dai,
	int div_id, int div)
{
	stwuct i2s_dai *i2s = to_info(dai);
	stwuct i2s_dai *othew = get_othew_dai(i2s);

	switch (div_id) {
	case SAMSUNG_I2S_DIV_BCWK:
		pm_wuntime_get_sync(dai->dev);
		if ((any_active(i2s) && div && (get_bfs(i2s) != div))
			|| (othew && othew->bfs && (othew->bfs != div))) {
			pm_wuntime_put(dai->dev);
			dev_eww(&i2s->pdev->dev,
				"%s:%d Othew DAI busy\n", __func__, __WINE__);
			wetuwn -EAGAIN;
		}
		i2s->bfs = div;
		pm_wuntime_put(dai->dev);
		bweak;
	defauwt:
		dev_eww(&i2s->pdev->dev,
			"Invawid cwock dividew(%d)\n", div_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_sfwames_t
i2s_deway(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	u32 weg = weadw(pwiv->addw + I2SFIC);
	snd_pcm_sfwames_t deway;

	WAWN_ON(!pm_wuntime_active(dai->dev));

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		deway = FIC_WXCOUNT(weg);
	ewse if (is_secondawy(i2s))
		deway = FICS_TXCOUNT(weadw(pwiv->addw + I2SFICS));
	ewse
		deway = (weg >> pwiv->vawiant_wegs->ftx0cnt_off) & 0x7f;

	wetuwn deway;
}

#ifdef CONFIG_PM
static int i2s_suspend(stwuct snd_soc_component *component)
{
	wetuwn pm_wuntime_fowce_suspend(component->dev);
}

static int i2s_wesume(stwuct snd_soc_component *component)
{
	wetuwn pm_wuntime_fowce_wesume(component->dev);
}
#ewse
#define i2s_suspend NUWW
#define i2s_wesume  NUWW
#endif

static int samsung_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	stwuct i2s_dai *othew = get_othew_dai(i2s);
	unsigned wong fwags;

	pm_wuntime_get_sync(dai->dev);

	if (is_secondawy(i2s)) {
		/* If this is pwobe on the secondawy DAI */
		snd_soc_dai_init_dma_data(dai, &i2s->dma_pwayback, NUWW);
	} ewse {
		snd_soc_dai_init_dma_data(dai, &i2s->dma_pwayback,
					  &i2s->dma_captuwe);

		if (pwiv->quiwks & QUIWK_NEED_WSTCWW)
			wwitew(CON_WSTCWW, pwiv->addw + I2SCON);

		if (pwiv->quiwks & QUIWK_SUPPOWTS_IDMA)
			idma_weg_addw_init(pwiv->addw,
					   othew->idma_pwayback.addw);
	}

	/* Weset any constwaint on WFS and BFS */
	i2s->wfs = 0;
	i2s->bfs = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	i2s_txctww(i2s, 0);
	i2s_wxctww(i2s, 0);
	i2s_fifo(i2s, FIC_TXFWUSH);
	i2s_fifo(othew, FIC_TXFWUSH);
	i2s_fifo(i2s, FIC_WXFWUSH);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* Gate CDCWK by defauwt */
	if (!is_opened(othew))
		i2s_set_syscwk(dai, SAMSUNG_I2S_CDCWK,
				0, SND_SOC_CWOCK_IN);
	pm_wuntime_put(dai->dev);

	wetuwn 0;
}

static int samsung_i2s_dai_wemove(stwuct snd_soc_dai *dai)
{
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(dai);
	unsigned wong fwags;

	pm_wuntime_get_sync(dai->dev);

	if (!is_secondawy(i2s)) {
		if (pwiv->quiwks & QUIWK_NEED_WSTCWW) {
			spin_wock_iwqsave(&pwiv->wock, fwags);
			wwitew(0, pwiv->addw + I2SCON);
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		}
	}

	pm_wuntime_put(dai->dev);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops samsung_i2s_dai_ops = {
	.pwobe = samsung_i2s_dai_pwobe,
	.wemove = samsung_i2s_dai_wemove,
	.twiggew = i2s_twiggew,
	.hw_pawams = i2s_hw_pawams,
	.set_fmt = i2s_set_fmt,
	.set_cwkdiv = i2s_set_cwkdiv,
	.set_syscwk = i2s_set_syscwk,
	.stawtup = i2s_stawtup,
	.shutdown = i2s_shutdown,
	.deway = i2s_deway,
};

static const stwuct snd_soc_dapm_widget samsung_i2s_widgets[] = {
	/* Backend DAI  */
	SND_SOC_DAPM_AIF_OUT("Mixew DAI TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Mixew DAI WX", NUWW, 0, SND_SOC_NOPM, 0, 0),

	/* Pwayback Mixew */
	SND_SOC_DAPM_MIXEW("Pwayback Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute samsung_i2s_dapm_woutes[] = {
	{ "Pwayback Mixew", NUWW, "Pwimawy Pwayback" },
	{ "Pwayback Mixew", NUWW, "Secondawy Pwayback" },

	{ "Mixew DAI TX", NUWW, "Pwayback Mixew" },
	{ "Pwimawy Captuwe", NUWW, "Mixew DAI WX" },
};

static const stwuct snd_soc_component_dwivew samsung_i2s_component = {
	.name = "samsung-i2s",

	.dapm_widgets = samsung_i2s_widgets,
	.num_dapm_widgets = AWWAY_SIZE(samsung_i2s_widgets),

	.dapm_woutes = samsung_i2s_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(samsung_i2s_dapm_woutes),

	.suspend = i2s_suspend,
	.wesume = i2s_wesume,

	.wegacy_dai_naming = 1,
};

#define SAMSUNG_I2S_FMTS (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_WE | \
			  SNDWV_PCM_FMTBIT_S24_WE)

static int i2s_awwoc_dais(stwuct samsung_i2s_pwiv *pwiv,
			  const stwuct samsung_i2s_dai_data *i2s_dai_data,
			  int num_dais)
{
	static const chaw *dai_names[] = { "samsung-i2s", "samsung-i2s-sec" };
	static const chaw *stweam_names[] = { "Pwimawy Pwayback",
					      "Secondawy Pwayback" };
	stwuct snd_soc_dai_dwivew *dai_dwv;
	int i;

	pwiv->dai = devm_kcawwoc(&pwiv->pdev->dev, num_dais,
				     sizeof(stwuct i2s_dai), GFP_KEWNEW);
	if (!pwiv->dai)
		wetuwn -ENOMEM;

	pwiv->dai_dwv = devm_kcawwoc(&pwiv->pdev->dev, num_dais,
				     sizeof(*dai_dwv), GFP_KEWNEW);
	if (!pwiv->dai_dwv)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_dais; i++) {
		dai_dwv = &pwiv->dai_dwv[i];

		dai_dwv->symmetwic_wate = 1;
		dai_dwv->ops = &samsung_i2s_dai_ops;

		dai_dwv->pwayback.channews_min = 1;
		dai_dwv->pwayback.channews_max = 2;
		dai_dwv->pwayback.wates = i2s_dai_data->pcm_wates;
		dai_dwv->pwayback.fowmats = SAMSUNG_I2S_FMTS;
		dai_dwv->pwayback.stweam_name = stweam_names[i];

		dai_dwv->id = i + 1;
		dai_dwv->name = dai_names[i];

		pwiv->dai[i].dwv = &pwiv->dai_dwv[i];
		pwiv->dai[i].pdev = pwiv->pdev;
	}

	/* Initiawize captuwe onwy fow the pwimawy DAI */
	dai_dwv = &pwiv->dai_dwv[SAMSUNG_I2S_ID_PWIMAWY - 1];

	dai_dwv->captuwe.channews_min = 1;
	dai_dwv->captuwe.channews_max = 2;
	dai_dwv->captuwe.wates = i2s_dai_data->pcm_wates;
	dai_dwv->captuwe.fowmats = SAMSUNG_I2S_FMTS;
	dai_dwv->captuwe.stweam_name = "Pwimawy Captuwe";

	wetuwn 0;
}

#ifdef CONFIG_PM
static int i2s_wuntime_suspend(stwuct device *dev)
{
	stwuct samsung_i2s_pwiv *pwiv = dev_get_dwvdata(dev);

	pwiv->suspend_i2smod = weadw(pwiv->addw + I2SMOD);
	pwiv->suspend_i2scon = weadw(pwiv->addw + I2SCON);
	pwiv->suspend_i2spsw = weadw(pwiv->addw + I2SPSW);

	cwk_disabwe_unpwepawe(pwiv->op_cwk);
	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int i2s_wuntime_wesume(stwuct device *dev)
{
	stwuct samsung_i2s_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	if (pwiv->op_cwk) {
		wet = cwk_pwepawe_enabwe(pwiv->op_cwk);
		if (wet) {
			cwk_disabwe_unpwepawe(pwiv->cwk);
			wetuwn wet;
		}
	}

	wwitew(pwiv->suspend_i2scon, pwiv->addw + I2SCON);
	wwitew(pwiv->suspend_i2smod, pwiv->addw + I2SMOD);
	wwitew(pwiv->suspend_i2spsw, pwiv->addw + I2SPSW);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static void i2s_unwegistew_cwocks(stwuct samsung_i2s_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->cwk_data.cwk_num; i++) {
		if (!IS_EWW(pwiv->cwk_tabwe[i]))
			cwk_unwegistew(pwiv->cwk_tabwe[i]);
	}
}

static void i2s_unwegistew_cwock_pwovidew(stwuct samsung_i2s_pwiv *pwiv)
{
	of_cwk_dew_pwovidew(pwiv->pdev->dev.of_node);
	i2s_unwegistew_cwocks(pwiv);
}


static int i2s_wegistew_cwock_pwovidew(stwuct samsung_i2s_pwiv *pwiv)
{

	const chaw * const i2s_cwk_desc[] = { "cdcwk", "wcwk_swc", "pwescawew" };
	const chaw *cwk_name[2] = { "i2s_opcwk0", "i2s_opcwk1" };
	const chaw *p_names[2] = { NUWW };
	stwuct device *dev = &pwiv->pdev->dev;
	const stwuct samsung_i2s_vawiant_wegs *weg_info = pwiv->vawiant_wegs;
	const chaw *i2s_cwk_name[AWWAY_SIZE(i2s_cwk_desc)];
	stwuct cwk *wcwkswc;
	int wet, i;

	/* Wegistew the cwock pwovidew onwy if it's expected in the DTB */
	if (!of_pwopewty_pwesent(dev->of_node, "#cwock-cewws"))
		wetuwn 0;

	/* Get the WCWKSWC mux cwock pawent cwock names */
	fow (i = 0; i < AWWAY_SIZE(p_names); i++) {
		wcwkswc = cwk_get(dev, cwk_name[i]);
		if (IS_EWW(wcwkswc))
			continue;
		p_names[i] = __cwk_get_name(wcwkswc);
		cwk_put(wcwkswc);
	}

	fow (i = 0; i < AWWAY_SIZE(i2s_cwk_desc); i++) {
		i2s_cwk_name[i] = devm_kaspwintf(dev, GFP_KEWNEW, "%s_%s",
						dev_name(dev), i2s_cwk_desc[i]);
		if (!i2s_cwk_name[i])
			wetuwn -ENOMEM;
	}

	if (!(pwiv->quiwks & QUIWK_NO_MUXPSW)) {
		/* Activate the pwescawew */
		u32 vaw = weadw(pwiv->addw + I2SPSW);
		wwitew(vaw | PSW_PSWEN, pwiv->addw + I2SPSW);

		pwiv->cwk_tabwe[CWK_I2S_WCWK_SWC] = cwk_wegistew_mux(dev,
				i2s_cwk_name[CWK_I2S_WCWK_SWC], p_names,
				AWWAY_SIZE(p_names),
				CWK_SET_WATE_NO_WEPAWENT | CWK_SET_WATE_PAWENT,
				pwiv->addw + I2SMOD, weg_info->wcwkswc_off,
				1, 0, &pwiv->wock);

		pwiv->cwk_tabwe[CWK_I2S_WCWK_PSW] = cwk_wegistew_dividew(dev,
				i2s_cwk_name[CWK_I2S_WCWK_PSW],
				i2s_cwk_name[CWK_I2S_WCWK_SWC],
				CWK_SET_WATE_PAWENT,
				pwiv->addw + I2SPSW, 8, 6, 0, &pwiv->wock);

		p_names[0] = i2s_cwk_name[CWK_I2S_WCWK_PSW];
		pwiv->cwk_data.cwk_num = 2;
	}

	pwiv->cwk_tabwe[CWK_I2S_CDCWK] = cwk_wegistew_gate(dev,
				i2s_cwk_name[CWK_I2S_CDCWK], p_names[0],
				CWK_SET_WATE_PAWENT,
				pwiv->addw + I2SMOD, weg_info->cdcwkcon_off,
				CWK_GATE_SET_TO_DISABWE, &pwiv->wock);

	pwiv->cwk_data.cwk_num += 1;
	pwiv->cwk_data.cwks = pwiv->cwk_tabwe;

	wet = of_cwk_add_pwovidew(dev->of_node, of_cwk_swc_oneceww_get,
				  &pwiv->cwk_data);
	if (wet < 0) {
		dev_eww(dev, "faiwed to add cwock pwovidew: %d\n", wet);
		i2s_unwegistew_cwocks(pwiv);
	}

	wetuwn wet;
}

/* Cweate pwatfowm device fow the secondawy PCM */
static int i2s_cweate_secondawy_device(stwuct samsung_i2s_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev_sec;
	const chaw *devname;
	int wet;

	devname = devm_kaspwintf(&pwiv->pdev->dev, GFP_KEWNEW, "%s-sec",
				 dev_name(&pwiv->pdev->dev));
	if (!devname)
		wetuwn -ENOMEM;

	pdev_sec = pwatfowm_device_awwoc(devname, -1);
	if (!pdev_sec)
		wetuwn -ENOMEM;

	pdev_sec->dwivew_ovewwide = kstwdup("samsung-i2s", GFP_KEWNEW);
	if (!pdev_sec->dwivew_ovewwide) {
		pwatfowm_device_put(pdev_sec);
		wetuwn -ENOMEM;
	}

	wet = pwatfowm_device_add(pdev_sec);
	if (wet < 0) {
		pwatfowm_device_put(pdev_sec);
		wetuwn wet;
	}

	wet = device_attach(&pdev_sec->dev);
	if (wet <= 0) {
		pwatfowm_device_unwegistew(pwiv->pdev_sec);
		dev_info(&pdev_sec->dev, "device_attach() faiwed\n");
		wetuwn wet;
	}

	pwiv->pdev_sec = pdev_sec;

	wetuwn 0;
}

static void i2s_dewete_secondawy_device(stwuct samsung_i2s_pwiv *pwiv)
{
	pwatfowm_device_unwegistew(pwiv->pdev_sec);
	pwiv->pdev_sec = NUWW;
}

static int samsung_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2s_dai *pwi_dai, *sec_dai = NUWW;
	stwuct s3c_audio_pdata *i2s_pdata = pdev->dev.pwatfowm_data;
	u32 wegs_base, idma_addw = 0;
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct samsung_i2s_dai_data *i2s_dai_data;
	const stwuct pwatfowm_device_id *id;
	stwuct samsung_i2s_pwiv *pwiv;
	stwuct wesouwce *wes;
	int num_dais, wet;

	if (IS_ENABWED(CONFIG_OF) && pdev->dev.of_node) {
		i2s_dai_data = of_device_get_match_data(&pdev->dev);
	} ewse {
		id = pwatfowm_get_device_id(pdev);

		/* Nothing to do if it is the secondawy device pwobe */
		if (!id)
			wetuwn 0;

		i2s_dai_data = (stwuct samsung_i2s_dai_data *)id->dwivew_data;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (np) {
		pwiv->quiwks = i2s_dai_data->quiwks;
		pwiv->fixup_eawwy = i2s_dai_data->fixup_eawwy;
		pwiv->fixup_wate = i2s_dai_data->fixup_wate;
	} ewse {
		if (!i2s_pdata) {
			dev_eww(&pdev->dev, "Missing pwatfowm data\n");
			wetuwn -EINVAW;
		}
		pwiv->quiwks = i2s_pdata->type.quiwks;
	}

	num_dais = (pwiv->quiwks & QUIWK_SEC_DAI) ? 2 : 1;
	pwiv->pdev = pdev;
	pwiv->vawiant_wegs = i2s_dai_data->i2s_vawiant_wegs;

	wet = i2s_awwoc_dais(pwiv, i2s_dai_data, num_dais);
	if (wet < 0)
		wetuwn wet;

	pwi_dai = &pwiv->dai[SAMSUNG_I2S_ID_PWIMAWY - 1];

	spin_wock_init(&pwiv->wock);
	spin_wock_init(&pwiv->pcm_wock);

	if (!np) {
		pwi_dai->dma_pwayback.fiwtew_data = i2s_pdata->dma_pwayback;
		pwi_dai->dma_captuwe.fiwtew_data = i2s_pdata->dma_captuwe;
		pwi_dai->fiwtew = i2s_pdata->dma_fiwtew;

		idma_addw = i2s_pdata->type.idma_addw;
	} ewse {
		if (of_pwopewty_wead_u32(np, "samsung,idma-addw",
					 &idma_addw)) {
			if (pwiv->quiwks & QUIWK_SUPPOWTS_IDMA) {
				dev_info(&pdev->dev, "idma addwess is not"\
						"specified");
			}
		}
	}

	pwiv->addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->addw))
		wetuwn PTW_EWW(pwiv->addw);

	wegs_base = wes->stawt;

	pwiv->cwk = devm_cwk_get(&pdev->dev, "iis");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get iis cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet != 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}
	pwi_dai->dma_pwayback.addw = wegs_base + I2STXD;
	pwi_dai->dma_captuwe.addw = wegs_base + I2SWXD;
	pwi_dai->dma_pwayback.chan_name = "tx";
	pwi_dai->dma_captuwe.chan_name = "wx";
	pwi_dai->dma_pwayback.addw_width = 4;
	pwi_dai->dma_captuwe.addw_width = 4;
	pwi_dai->pwiv = pwiv;

	if (pwiv->quiwks & QUIWK_PWI_6CHAN)
		pwi_dai->dwv->pwayback.channews_max = 6;

	wet = samsung_asoc_dma_pwatfowm_wegistew(&pdev->dev, pwi_dai->fiwtew,
						 "tx", "wx", NUWW);
	if (wet < 0)
		goto eww_disabwe_cwk;

	if (pwiv->quiwks & QUIWK_SEC_DAI) {
		sec_dai = &pwiv->dai[SAMSUNG_I2S_ID_SECONDAWY - 1];

		sec_dai->dma_pwayback.addw = wegs_base + I2STXDS;
		sec_dai->dma_pwayback.chan_name = "tx-sec";

		if (!np) {
			sec_dai->dma_pwayback.fiwtew_data = i2s_pdata->dma_pway_sec;
			sec_dai->fiwtew = i2s_pdata->dma_fiwtew;
		}

		sec_dai->dma_pwayback.addw_width = 4;
		sec_dai->idma_pwayback.addw = idma_addw;
		sec_dai->pwi_dai = pwi_dai;
		sec_dai->pwiv = pwiv;
		pwi_dai->sec_dai = sec_dai;

		wet = i2s_cweate_secondawy_device(pwiv);
		if (wet < 0)
			goto eww_disabwe_cwk;

		wet = samsung_asoc_dma_pwatfowm_wegistew(&pwiv->pdev_sec->dev,
						sec_dai->fiwtew, "tx-sec", NUWW,
						&pdev->dev);
		if (wet < 0)
			goto eww_dew_sec;

	}

	if (i2s_pdata && i2s_pdata->cfg_gpio && i2s_pdata->cfg_gpio(pdev)) {
		dev_eww(&pdev->dev, "Unabwe to configuwe gpio\n");
		wet = -EINVAW;
		goto eww_dew_sec;
	}

	dev_set_dwvdata(&pdev->dev, pwiv);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					&samsung_i2s_component,
					pwiv->dai_dwv, num_dais);
	if (wet < 0)
		goto eww_dew_sec;

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = i2s_wegistew_cwock_pwovidew(pwiv);
	if (wet < 0)
		goto eww_disabwe_pm;

	pwiv->op_cwk = cwk_get_pawent(pwiv->cwk_tabwe[CWK_I2S_WCWK_SWC]);

	wetuwn 0;

eww_disabwe_pm:
	pm_wuntime_disabwe(&pdev->dev);
eww_dew_sec:
	i2s_dewete_secondawy_device(pwiv);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void samsung_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct samsung_i2s_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	/* The secondawy device has no dwivew data assigned */
	if (!pwiv)
		wetuwn;

	pm_wuntime_get_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	i2s_unwegistew_cwock_pwovidew(pwiv);
	i2s_dewete_secondawy_device(pwiv);
	cwk_disabwe_unpwepawe(pwiv->cwk);

	pm_wuntime_put_noidwe(&pdev->dev);
}

static void fsd_i2s_fixup_eawwy(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct i2s_dai *i2s = to_info(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct i2s_dai *othew = get_othew_dai(i2s);

	if (!is_opened(othew)) {
		i2s_set_syscwk(dai, SAMSUNG_I2S_CDCWK, 0, SND_SOC_CWOCK_OUT);
		i2s_set_syscwk(dai, SAMSUNG_I2S_OPCWK, 0, MOD_OPCWK_PCWK);
	}
}

static void fsd_i2s_fixup_wate(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct samsung_i2s_pwiv *pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct i2s_dai *i2s = to_info(snd_soc_wtd_to_cpu(wtd, 0));
	stwuct i2s_dai *othew = get_othew_dai(i2s);

	if (!is_opened(othew))
		wwitew(PSW_PSVAW(2) | PSW_PSWEN, pwiv->addw + I2SPSW);
}

static const stwuct samsung_i2s_vawiant_wegs i2sv3_wegs = {
	.bfs_off = 1,
	.wfs_off = 3,
	.sdf_off = 5,
	.txw_off = 8,
	.wcwkswc_off = 10,
	.mss_off = 11,
	.cdcwkcon_off = 12,
	.wwp_off = 7,
	.bfs_mask = 0x3,
	.wfs_mask = 0x3,
	.ftx0cnt_off = 8,
};

static const stwuct samsung_i2s_vawiant_wegs i2sv6_wegs = {
	.bfs_off = 0,
	.wfs_off = 4,
	.sdf_off = 6,
	.txw_off = 8,
	.wcwkswc_off = 10,
	.mss_off = 11,
	.cdcwkcon_off = 12,
	.wwp_off = 15,
	.bfs_mask = 0xf,
	.wfs_mask = 0x3,
	.ftx0cnt_off = 8,
};

static const stwuct samsung_i2s_vawiant_wegs i2sv7_wegs = {
	.bfs_off = 0,
	.wfs_off = 4,
	.sdf_off = 7,
	.txw_off = 9,
	.wcwkswc_off = 11,
	.mss_off = 12,
	.cdcwkcon_off = 22,
	.wwp_off = 15,
	.bfs_mask = 0xf,
	.wfs_mask = 0x7,
	.ftx0cnt_off = 0,
};

static const stwuct samsung_i2s_vawiant_wegs i2sv5_i2s1_wegs = {
	.bfs_off = 0,
	.wfs_off = 3,
	.sdf_off = 6,
	.txw_off = 8,
	.wcwkswc_off = 10,
	.mss_off = 11,
	.cdcwkcon_off = 12,
	.wwp_off = 15,
	.bfs_mask = 0x7,
	.wfs_mask = 0x7,
	.ftx0cnt_off = 8,
};

static const stwuct samsung_i2s_dai_data i2sv3_dai_type = {
	.quiwks = QUIWK_NO_MUXPSW,
	.pcm_wates = SNDWV_PCM_WATE_8000_96000,
	.i2s_vawiant_wegs = &i2sv3_wegs,
};

static const stwuct samsung_i2s_dai_data i2sv5_dai_type __maybe_unused = {
	.quiwks = QUIWK_PWI_6CHAN | QUIWK_SEC_DAI | QUIWK_NEED_WSTCWW |
			QUIWK_SUPPOWTS_IDMA,
	.pcm_wates = SNDWV_PCM_WATE_8000_96000,
	.i2s_vawiant_wegs = &i2sv3_wegs,
};

static const stwuct samsung_i2s_dai_data i2sv6_dai_type __maybe_unused = {
	.quiwks = QUIWK_PWI_6CHAN | QUIWK_SEC_DAI | QUIWK_NEED_WSTCWW |
			QUIWK_SUPPOWTS_TDM | QUIWK_SUPPOWTS_IDMA,
	.pcm_wates = SNDWV_PCM_WATE_8000_96000,
	.i2s_vawiant_wegs = &i2sv6_wegs,
};

static const stwuct samsung_i2s_dai_data i2sv7_dai_type __maybe_unused = {
	.quiwks = QUIWK_PWI_6CHAN | QUIWK_SEC_DAI | QUIWK_NEED_WSTCWW |
			QUIWK_SUPPOWTS_TDM,
	.pcm_wates = SNDWV_PCM_WATE_8000_192000,
	.i2s_vawiant_wegs = &i2sv7_wegs,
};

static const stwuct samsung_i2s_dai_data i2sv5_dai_type_i2s1 __maybe_unused = {
	.quiwks = QUIWK_PWI_6CHAN | QUIWK_NEED_WSTCWW,
	.pcm_wates = SNDWV_PCM_WATE_8000_96000,
	.i2s_vawiant_wegs = &i2sv5_i2s1_wegs,
};

static const stwuct samsung_i2s_dai_data fsd_dai_type __maybe_unused = {
	.quiwks = QUIWK_SEC_DAI | QUIWK_NEED_WSTCWW | QUIWK_SUPPOWTS_TDM,
	.pcm_wates = SNDWV_PCM_WATE_8000_192000,
	.i2s_vawiant_wegs = &i2sv7_wegs,
	.fixup_eawwy = fsd_i2s_fixup_eawwy,
	.fixup_wate = fsd_i2s_fixup_wate,
};

static const stwuct pwatfowm_device_id samsung_i2s_dwivew_ids[] = {
	{
		.name           = "samsung-i2s",
		.dwivew_data	= (kewnew_uwong_t)&i2sv3_dai_type,
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, samsung_i2s_dwivew_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id exynos_i2s_match[] = {
	{
		.compatibwe = "samsung,s3c6410-i2s",
		.data = &i2sv3_dai_type,
	}, {
		.compatibwe = "samsung,s5pv210-i2s",
		.data = &i2sv5_dai_type,
	}, {
		.compatibwe = "samsung,exynos5420-i2s",
		.data = &i2sv6_dai_type,
	}, {
		.compatibwe = "samsung,exynos7-i2s",
		.data = &i2sv7_dai_type,
	}, {
		.compatibwe = "samsung,exynos7-i2s1",
		.data = &i2sv5_dai_type_i2s1,
	}, {
		.compatibwe = "teswa,fsd-i2s",
		.data = &fsd_dai_type,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, exynos_i2s_match);
#endif

static const stwuct dev_pm_ops samsung_i2s_pm = {
	SET_WUNTIME_PM_OPS(i2s_wuntime_suspend,
				i2s_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew samsung_i2s_dwivew = {
	.pwobe  = samsung_i2s_pwobe,
	.wemove_new = samsung_i2s_wemove,
	.id_tabwe = samsung_i2s_dwivew_ids,
	.dwivew = {
		.name = "samsung-i2s",
		.of_match_tabwe = of_match_ptw(exynos_i2s_match),
		.pm = &samsung_i2s_pm,
	},
};

moduwe_pwatfowm_dwivew(samsung_i2s_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Jaswindew Singh, <jassisinghbwaw@gmaiw.com>");
MODUWE_DESCWIPTION("Samsung I2S Intewface");
MODUWE_AWIAS("pwatfowm:samsung-i2s");
MODUWE_WICENSE("GPW");
