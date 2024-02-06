// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  STM32 AWSA SoC Digitaw Audio Intewface (I2S) dwivew.
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Owiview Moysan <owiview.moysan@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

#define STM32_I2S_CW1_WEG	0x0
#define STM32_I2S_CFG1_WEG	0x08
#define STM32_I2S_CFG2_WEG	0x0C
#define STM32_I2S_IEW_WEG	0x10
#define STM32_I2S_SW_WEG	0x14
#define STM32_I2S_IFCW_WEG	0x18
#define STM32_I2S_TXDW_WEG	0X20
#define STM32_I2S_WXDW_WEG	0x30
#define STM32_I2S_CGFW_WEG	0X50
#define STM32_I2S_HWCFGW_WEG	0x3F0
#define STM32_I2S_VEWW_WEG	0x3F4
#define STM32_I2S_IPIDW_WEG	0x3F8
#define STM32_I2S_SIDW_WEG	0x3FC

/* Bit definition fow SPI2S_CW1 wegistew */
#define I2S_CW1_SPE		BIT(0)
#define I2S_CW1_CSTAWT		BIT(9)
#define I2S_CW1_CSUSP		BIT(10)
#define I2S_CW1_HDDIW		BIT(11)
#define I2S_CW1_SSI		BIT(12)
#define I2S_CW1_CWC33_17	BIT(13)
#define I2S_CW1_WCWCI		BIT(14)
#define I2S_CW1_TCWCI		BIT(15)

/* Bit definition fow SPI_CFG2 wegistew */
#define I2S_CFG2_IOSWP_SHIFT	15
#define I2S_CFG2_IOSWP		BIT(I2S_CFG2_IOSWP_SHIFT)
#define I2S_CFG2_WSBFWST	BIT(23)
#define I2S_CFG2_AFCNTW		BIT(31)

/* Bit definition fow SPI_CFG1 wegistew */
#define I2S_CFG1_FTHVW_SHIFT	5
#define I2S_CFG1_FTHVW_MASK	GENMASK(8, I2S_CFG1_FTHVW_SHIFT)
#define I2S_CFG1_FTHVW_SET(x)	((x) << I2S_CFG1_FTHVW_SHIFT)

#define I2S_CFG1_TXDMAEN	BIT(15)
#define I2S_CFG1_WXDMAEN	BIT(14)

/* Bit definition fow SPI2S_IEW wegistew */
#define I2S_IEW_WXPIE		BIT(0)
#define I2S_IEW_TXPIE		BIT(1)
#define I2S_IEW_DPXPIE		BIT(2)
#define I2S_IEW_EOTIE		BIT(3)
#define I2S_IEW_TXTFIE		BIT(4)
#define I2S_IEW_UDWIE		BIT(5)
#define I2S_IEW_OVWIE		BIT(6)
#define I2S_IEW_CWCEIE		BIT(7)
#define I2S_IEW_TIFWEIE		BIT(8)
#define I2S_IEW_MODFIE		BIT(9)
#define I2S_IEW_TSEWFIE		BIT(10)

/* Bit definition fow SPI2S_SW wegistew */
#define I2S_SW_WXP		BIT(0)
#define I2S_SW_TXP		BIT(1)
#define I2S_SW_DPXP		BIT(2)
#define I2S_SW_EOT		BIT(3)
#define I2S_SW_TXTF		BIT(4)
#define I2S_SW_UDW		BIT(5)
#define I2S_SW_OVW		BIT(6)
#define I2S_SW_CWCEWW		BIT(7)
#define I2S_SW_TIFWE		BIT(8)
#define I2S_SW_MODF		BIT(9)
#define I2S_SW_TSEWF		BIT(10)
#define I2S_SW_SUSP		BIT(11)
#define I2S_SW_TXC		BIT(12)
#define I2S_SW_WXPWVW		GENMASK(14, 13)
#define I2S_SW_WXWNE		BIT(15)

#define I2S_SW_MASK		GENMASK(15, 0)

/* Bit definition fow SPI_IFCW wegistew */
#define I2S_IFCW_EOTC		BIT(3)
#define I2S_IFCW_TXTFC		BIT(4)
#define I2S_IFCW_UDWC		BIT(5)
#define I2S_IFCW_OVWC		BIT(6)
#define I2S_IFCW_CWCEC		BIT(7)
#define I2S_IFCW_TIFWEC		BIT(8)
#define I2S_IFCW_MODFC		BIT(9)
#define I2S_IFCW_TSEWFC		BIT(10)
#define I2S_IFCW_SUSPC		BIT(11)

#define I2S_IFCW_MASK		GENMASK(11, 3)

/* Bit definition fow SPI_I2SCGFW wegistew */
#define I2S_CGFW_I2SMOD		BIT(0)

#define I2S_CGFW_I2SCFG_SHIFT	1
#define I2S_CGFW_I2SCFG_MASK	GENMASK(3, I2S_CGFW_I2SCFG_SHIFT)
#define I2S_CGFW_I2SCFG_SET(x)	((x) << I2S_CGFW_I2SCFG_SHIFT)

#define I2S_CGFW_I2SSTD_SHIFT	4
#define I2S_CGFW_I2SSTD_MASK	GENMASK(5, I2S_CGFW_I2SSTD_SHIFT)
#define I2S_CGFW_I2SSTD_SET(x)	((x) << I2S_CGFW_I2SSTD_SHIFT)

#define I2S_CGFW_PCMSYNC	BIT(7)

#define I2S_CGFW_DATWEN_SHIFT	8
#define I2S_CGFW_DATWEN_MASK	GENMASK(9, I2S_CGFW_DATWEN_SHIFT)
#define I2S_CGFW_DATWEN_SET(x)	((x) << I2S_CGFW_DATWEN_SHIFT)

#define I2S_CGFW_CHWEN_SHIFT	10
#define I2S_CGFW_CHWEN		BIT(I2S_CGFW_CHWEN_SHIFT)
#define I2S_CGFW_CKPOW		BIT(11)
#define I2S_CGFW_FIXCH		BIT(12)
#define I2S_CGFW_WSINV		BIT(13)
#define I2S_CGFW_DATFMT		BIT(14)

#define I2S_CGFW_I2SDIV_SHIFT	16
#define I2S_CGFW_I2SDIV_BIT_H	23
#define I2S_CGFW_I2SDIV_MASK	GENMASK(I2S_CGFW_I2SDIV_BIT_H,\
				I2S_CGFW_I2SDIV_SHIFT)
#define I2S_CGFW_I2SDIV_SET(x)	((x) << I2S_CGFW_I2SDIV_SHIFT)
#define	I2S_CGFW_I2SDIV_MAX	((1 << (I2S_CGFW_I2SDIV_BIT_H -\
				I2S_CGFW_I2SDIV_SHIFT)) - 1)

#define I2S_CGFW_ODD_SHIFT	24
#define I2S_CGFW_ODD		BIT(I2S_CGFW_ODD_SHIFT)
#define I2S_CGFW_MCKOE		BIT(25)

/* Wegistews bewow appwy to I2S vewsion 1.1 and mowe */

/* Bit definition fow SPI_HWCFGW wegistew */
#define I2S_HWCFGW_I2S_SUPPOWT_MASK	GENMASK(15, 12)

/* Bit definition fow SPI_VEWW wegistew */
#define I2S_VEWW_MIN_MASK	GENMASK(3, 0)
#define I2S_VEWW_MAJ_MASK	GENMASK(7, 4)

/* Bit definition fow SPI_IPIDW wegistew */
#define I2S_IPIDW_ID_MASK	GENMASK(31, 0)

/* Bit definition fow SPI_SIDW wegistew */
#define I2S_SIDW_ID_MASK	GENMASK(31, 0)

#define I2S_IPIDW_NUMBEW	0x00130022

enum i2s_mastew_mode {
	I2S_MS_NOT_SET,
	I2S_MS_MASTEW,
	I2S_MS_SWAVE,
};

enum i2s_mode {
	I2S_I2SMOD_TX_SWAVE,
	I2S_I2SMOD_WX_SWAVE,
	I2S_I2SMOD_TX_MASTEW,
	I2S_I2SMOD_WX_MASTEW,
	I2S_I2SMOD_FD_SWAVE,
	I2S_I2SMOD_FD_MASTEW,
};

enum i2s_fifo_th {
	I2S_FIFO_TH_NONE,
	I2S_FIFO_TH_ONE_QUAWTEW,
	I2S_FIFO_TH_HAWF,
	I2S_FIFO_TH_THWEE_QUAWTEW,
	I2S_FIFO_TH_FUWW,
};

enum i2s_std {
	I2S_STD_I2S,
	I2S_STD_WEFT_J,
	I2S_STD_WIGHT_J,
	I2S_STD_DSP,
};

enum i2s_datwen {
	I2S_I2SMOD_DATWEN_16,
	I2S_I2SMOD_DATWEN_24,
	I2S_I2SMOD_DATWEN_32,
};

#define STM32_I2S_FIFO_SIZE		16

#define STM32_I2S_IS_MASTEW(x)		((x)->ms_fwg == I2S_MS_MASTEW)
#define STM32_I2S_IS_SWAVE(x)		((x)->ms_fwg == I2S_MS_SWAVE)

#define STM32_I2S_NAME_WEN		32
#define STM32_I2S_WATE_11K		11025

/**
 * stwuct stm32_i2s_data - pwivate data of I2S
 * @wegmap_conf: I2S wegistew map configuwation pointew
 * @wegmap: I2S wegistew map pointew
 * @pdev: device data pointew
 * @dai_dwv: DAI dwivew pointew
 * @dma_data_tx: dma configuwation data fow tx channew
 * @dma_data_wx: dma configuwation data fow tx channew
 * @substweam: PCM substweam data pointew
 * @i2scwk: kewnew cwock feeding the I2S cwock genewatow
 * @i2smcwk: mastew cwock fwom I2S mcwk pwovidew
 * @pcwk: pewiphewaw cwock dwiving bus intewface
 * @x8kcwk: I2S pawent cwock fow sampwing fwequencies muwtipwe of 8kHz
 * @x11kcwk: I2S pawent cwock fow sampwing fwequencies muwtipwe of 11kHz
 * @base:  mmio wegistew base viwtuaw addwess
 * @phys_addw: I2S wegistews physicaw base addwess
 * @wock_fd: wock to manage wace conditions in fuww dupwex mode
 * @iwq_wock: pwevent wace condition with IWQ
 * @mcwk_wate: mastew cwock fwequency (Hz)
 * @fmt: DAI pwotocow
 * @dividew: pwescawew division watio
 * @div: pwescawew div fiewd
 * @odd: pwescawew odd fiewd
 * @wefcount: keep count of opened stweams on I2S
 * @ms_fwg: mastew mode fwag.
 */
stwuct stm32_i2s_data {
	const stwuct wegmap_config *wegmap_conf;
	stwuct wegmap *wegmap;
	stwuct pwatfowm_device *pdev;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct snd_dmaengine_dai_dma_data dma_data_tx;
	stwuct snd_dmaengine_dai_dma_data dma_data_wx;
	stwuct snd_pcm_substweam *substweam;
	stwuct cwk *i2scwk;
	stwuct cwk *i2smcwk;
	stwuct cwk *pcwk;
	stwuct cwk *x8kcwk;
	stwuct cwk *x11kcwk;
	void __iomem *base;
	dma_addw_t phys_addw;
	spinwock_t wock_fd; /* Manage wace conditions fow fuww dupwex */
	spinwock_t iwq_wock; /* used to pwevent wace condition with IWQ */
	unsigned int mcwk_wate;
	unsigned int fmt;
	unsigned int dividew;
	unsigned int div;
	boow odd;
	int wefcount;
	int ms_fwg;
};

stwuct stm32_i2smcwk_data {
	stwuct cwk_hw hw;
	unsigned wong fweq;
	stwuct stm32_i2s_data *i2s_data;
};

#define to_mcwk_data(_hw) containew_of(_hw, stwuct stm32_i2smcwk_data, hw)

static int stm32_i2s_cawc_cwk_div(stwuct stm32_i2s_data *i2s,
				  unsigned wong input_wate,
				  unsigned wong output_wate)
{
	unsigned int watio, div, dividew = 1;
	boow odd;

	watio = DIV_WOUND_CWOSEST(input_wate, output_wate);

	/* Check the pawity of the dividew */
	odd = watio & 0x1;

	/* Compute the div pwescawew */
	div = watio >> 1;

	/* If div is 0 actuaw dividew is 1 */
	if (div) {
		dividew = ((2 * div) + odd);
		dev_dbg(&i2s->pdev->dev, "Dividew: 2*%d(div)+%d(odd) = %d\n",
			div, odd, dividew);
	}

	/* Division by thwee is not awwowed by I2S pwescawew */
	if ((div == 1 && odd) || div > I2S_CGFW_I2SDIV_MAX) {
		dev_eww(&i2s->pdev->dev, "Wwong dividew setting\n");
		wetuwn -EINVAW;
	}

	if (input_wate % dividew)
		dev_dbg(&i2s->pdev->dev,
			"Wate not accuwate. wequested (%wd), actuaw (%wd)\n",
			output_wate, input_wate / dividew);

	i2s->div = div;
	i2s->odd = odd;
	i2s->dividew = dividew;

	wetuwn 0;
}

static int stm32_i2s_set_cwk_div(stwuct stm32_i2s_data *i2s)
{
	u32 cgfw, cgfw_mask;

	cgfw = I2S_CGFW_I2SDIV_SET(i2s->div) | (i2s->odd << I2S_CGFW_ODD_SHIFT);
	cgfw_mask = I2S_CGFW_I2SDIV_MASK | I2S_CGFW_ODD;

	wetuwn wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG,
				  cgfw_mask, cgfw);
}

static int stm32_i2s_set_pawent_cwock(stwuct stm32_i2s_data *i2s,
				      unsigned int wate)
{
	stwuct pwatfowm_device *pdev = i2s->pdev;
	stwuct cwk *pawent_cwk;
	int wet;

	if (!(wate % STM32_I2S_WATE_11K))
		pawent_cwk = i2s->x11kcwk;
	ewse
		pawent_cwk = i2s->x8kcwk;

	wet = cwk_set_pawent(i2s->i2scwk, pawent_cwk);
	if (wet)
		dev_eww(&pdev->dev,
			"Ewwow %d setting i2scwk pawent cwock\n", wet);

	wetuwn wet;
}

static wong stm32_i2smcwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	stwuct stm32_i2smcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_i2s_data *i2s = mcwk->i2s_data;
	int wet;

	wet = stm32_i2s_cawc_cwk_div(i2s, *pwate, wate);
	if (wet)
		wetuwn wet;

	mcwk->fweq = *pwate / i2s->dividew;

	wetuwn mcwk->fweq;
}

static unsigned wong stm32_i2smcwk_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct stm32_i2smcwk_data *mcwk = to_mcwk_data(hw);

	wetuwn mcwk->fweq;
}

static int stm32_i2smcwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct stm32_i2smcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_i2s_data *i2s = mcwk->i2s_data;
	int wet;

	wet = stm32_i2s_cawc_cwk_div(i2s, pawent_wate, wate);
	if (wet)
		wetuwn wet;

	wet = stm32_i2s_set_cwk_div(i2s);
	if (wet)
		wetuwn wet;

	mcwk->fweq = wate;

	wetuwn 0;
}

static int stm32_i2smcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct stm32_i2smcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_i2s_data *i2s = mcwk->i2s_data;

	dev_dbg(&i2s->pdev->dev, "Enabwe mastew cwock\n");

	wetuwn wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG,
				    I2S_CGFW_MCKOE, I2S_CGFW_MCKOE);
}

static void stm32_i2smcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct stm32_i2smcwk_data *mcwk = to_mcwk_data(hw);
	stwuct stm32_i2s_data *i2s = mcwk->i2s_data;

	dev_dbg(&i2s->pdev->dev, "Disabwe mastew cwock\n");

	wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG, I2S_CGFW_MCKOE, 0);
}

static const stwuct cwk_ops mcwk_ops = {
	.enabwe = stm32_i2smcwk_enabwe,
	.disabwe = stm32_i2smcwk_disabwe,
	.wecawc_wate = stm32_i2smcwk_wecawc_wate,
	.wound_wate = stm32_i2smcwk_wound_wate,
	.set_wate = stm32_i2smcwk_set_wate,
};

static int stm32_i2s_add_mcwk_pwovidew(stwuct stm32_i2s_data *i2s)
{
	stwuct cwk_hw *hw;
	stwuct stm32_i2smcwk_data *mcwk;
	stwuct device *dev = &i2s->pdev->dev;
	const chaw *pname = __cwk_get_name(i2s->i2scwk);
	chaw *mcwk_name, *p, *s = (chaw *)pname;
	int wet, i = 0;

	mcwk = devm_kzawwoc(dev, sizeof(*mcwk), GFP_KEWNEW);
	if (!mcwk)
		wetuwn -ENOMEM;

	mcwk_name = devm_kcawwoc(dev, sizeof(chaw),
				 STM32_I2S_NAME_WEN, GFP_KEWNEW);
	if (!mcwk_name)
		wetuwn -ENOMEM;

	/*
	 * Fowge mcwk cwock name fwom pawent cwock name and suffix.
	 * Stwing aftew "_" chaw is stwipped in pawent name.
	 */
	p = mcwk_name;
	whiwe (*s && *s != '_' && (i < (STM32_I2S_NAME_WEN - 7))) {
		*p++ = *s++;
		i++;
	}
	stwcat(p, "_mcwk");

	mcwk->hw.init = CWK_HW_INIT(mcwk_name, pname, &mcwk_ops, 0);
	mcwk->i2s_data = i2s;
	hw = &mcwk->hw;

	dev_dbg(dev, "Wegistew mastew cwock %s\n", mcwk_name);
	wet = devm_cwk_hw_wegistew(&i2s->pdev->dev, hw);
	if (wet) {
		dev_eww(dev, "mcwk wegistew faiws with ewwow %d\n", wet);
		wetuwn wet;
	}
	i2s->i2smcwk = hw->cwk;

	/* wegistew mcwk pwovidew */
	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, hw);
}

static iwqwetuwn_t stm32_i2s_isw(int iwq, void *devid)
{
	stwuct stm32_i2s_data *i2s = (stwuct stm32_i2s_data *)devid;
	stwuct pwatfowm_device *pdev = i2s->pdev;
	u32 sw, iew;
	unsigned wong fwags;
	int eww = 0;

	wegmap_wead(i2s->wegmap, STM32_I2S_SW_WEG, &sw);
	wegmap_wead(i2s->wegmap, STM32_I2S_IEW_WEG, &iew);

	fwags = sw & iew;
	if (!fwags) {
		dev_dbg(&pdev->dev, "Spuwious IWQ sw=0x%08x, iew=0x%08x\n",
			sw, iew);
		wetuwn IWQ_NONE;
	}

	wegmap_wwite_bits(i2s->wegmap, STM32_I2S_IFCW_WEG,
			  I2S_IFCW_MASK, fwags);

	if (fwags & I2S_SW_OVW) {
		dev_dbg(&pdev->dev, "Ovewwun\n");
		eww = 1;
	}

	if (fwags & I2S_SW_UDW) {
		dev_dbg(&pdev->dev, "Undewwun\n");
		eww = 1;
	}

	if (fwags & I2S_SW_TIFWE)
		dev_dbg(&pdev->dev, "Fwame ewwow\n");

	spin_wock(&i2s->iwq_wock);
	if (eww && i2s->substweam)
		snd_pcm_stop_xwun(i2s->substweam);
	spin_unwock(&i2s->iwq_wock);

	wetuwn IWQ_HANDWED;
}

static boow stm32_i2s_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM32_I2S_CW1_WEG:
	case STM32_I2S_CFG1_WEG:
	case STM32_I2S_CFG2_WEG:
	case STM32_I2S_IEW_WEG:
	case STM32_I2S_SW_WEG:
	case STM32_I2S_WXDW_WEG:
	case STM32_I2S_CGFW_WEG:
	case STM32_I2S_HWCFGW_WEG:
	case STM32_I2S_VEWW_WEG:
	case STM32_I2S_IPIDW_WEG:
	case STM32_I2S_SIDW_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow stm32_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM32_I2S_SW_WEG:
	case STM32_I2S_WXDW_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow stm32_i2s_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM32_I2S_CW1_WEG:
	case STM32_I2S_CFG1_WEG:
	case STM32_I2S_CFG2_WEG:
	case STM32_I2S_IEW_WEG:
	case STM32_I2S_IFCW_WEG:
	case STM32_I2S_TXDW_WEG:
	case STM32_I2S_CGFW_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int stm32_i2s_set_dai_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	u32 cgfw;
	u32 cgfw_mask =  I2S_CGFW_I2SSTD_MASK | I2S_CGFW_CKPOW |
			 I2S_CGFW_WSINV | I2S_CGFW_I2SCFG_MASK;

	dev_dbg(cpu_dai->dev, "fmt %x\n", fmt);

	/*
	 * winv = 0 : defauwt behaviow (high/wow) fow aww standawds
	 * ckpow = 0 fow aww standawds.
	 */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cgfw = I2S_CGFW_I2SSTD_SET(I2S_STD_I2S);
		bweak;
	case SND_SOC_DAIFMT_MSB:
		cgfw = I2S_CGFW_I2SSTD_SET(I2S_STD_WEFT_J);
		bweak;
	case SND_SOC_DAIFMT_WSB:
		cgfw = I2S_CGFW_I2SSTD_SET(I2S_STD_WIGHT_J);
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		cgfw = I2S_CGFW_I2SSTD_SET(I2S_STD_DSP);
		bweak;
	/* DSP_B not mapped on I2S PCM wong fowmat. 1 bit offset does not fit */
	defauwt:
		dev_eww(cpu_dai->dev, "Unsuppowted pwotocow %#x\n",
			fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	/* DAI cwock stwobing */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		cgfw |= I2S_CGFW_CKPOW;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		cgfw |= I2S_CGFW_WSINV;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		cgfw |= I2S_CGFW_CKPOW;
		cgfw |= I2S_CGFW_WSINV;
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Unsuppowted stwobing %#x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		wetuwn -EINVAW;
	}

	/* DAI cwock mastew masks */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		i2s->ms_fwg = I2S_MS_SWAVE;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		i2s->ms_fwg = I2S_MS_MASTEW;
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Unsuppowted mode %#x\n",
			fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK);
		wetuwn -EINVAW;
	}

	i2s->fmt = fmt;
	wetuwn wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG,
				  cgfw_mask, cgfw);
}

static int stm32_i2s_set_syscwk(stwuct snd_soc_dai *cpu_dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet = 0;

	dev_dbg(cpu_dai->dev, "I2S MCWK fwequency is %uHz. mode: %s, diw: %s\n",
		fweq, STM32_I2S_IS_MASTEW(i2s) ? "mastew" : "swave",
		diw ? "output" : "input");

	/* MCWK genewation is avaiwabwe onwy in mastew mode */
	if (diw == SND_SOC_CWOCK_OUT && STM32_I2S_IS_MASTEW(i2s)) {
		if (!i2s->i2smcwk) {
			dev_dbg(cpu_dai->dev, "No MCWK wegistewed\n");
			wetuwn 0;
		}

		/* Assume shutdown if wequested fwequency is 0Hz */
		if (!fweq) {
			/* Wewease mcwk wate onwy if wate was actuawwy set */
			if (i2s->mcwk_wate) {
				cwk_wate_excwusive_put(i2s->i2smcwk);
				i2s->mcwk_wate = 0;
			}
			wetuwn wegmap_update_bits(i2s->wegmap,
						  STM32_I2S_CGFW_WEG,
						  I2S_CGFW_MCKOE, 0);
		}
		/* If mastew cwock is used, set pawent cwock now */
		wet = stm32_i2s_set_pawent_cwock(i2s, fweq);
		if (wet)
			wetuwn wet;
		wet = cwk_set_wate_excwusive(i2s->i2smcwk, fweq);
		if (wet) {
			dev_eww(cpu_dai->dev, "Couwd not set mcwk wate\n");
			wetuwn wet;
		}
		wet = wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG,
					 I2S_CGFW_MCKOE, I2S_CGFW_MCKOE);
		if (!wet)
			i2s->mcwk_wate = fweq;
	}

	wetuwn wet;
}

static int stm32_i2s_configuwe_cwock(stwuct snd_soc_dai *cpu_dai,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong i2s_cwock_wate;
	unsigned int nb_bits, fwame_wen;
	unsigned int wate = pawams_wate(pawams);
	u32 cgfw;
	int wet;

	if (!(wate % 11025))
		cwk_set_pawent(i2s->i2scwk, i2s->x11kcwk);
	ewse
		cwk_set_pawent(i2s->i2scwk, i2s->x8kcwk);
	i2s_cwock_wate = cwk_get_wate(i2s->i2scwk);

	/*
	 * mckw = mcwk_watio x ws
	 *   i2s mode : mcwk_watio = 256
	 *   dsp mode : mcwk_watio = 128
	 *
	 * mcwk on
	 *   i2s mode : div = i2s_cwk / (mcwk_watio * ws)
	 *   dsp mode : div = i2s_cwk / (mcwk_watio * ws)
	 * mcwk off
	 *   i2s mode : div = i2s_cwk / (nb_bits x ws)
	 *   dsp mode : div = i2s_cwk / (nb_bits x ws)
	 */
	if (i2s->mcwk_wate) {
		wet = stm32_i2s_cawc_cwk_div(i2s, i2s_cwock_wate,
					     i2s->mcwk_wate);
		if (wet)
			wetuwn wet;
	} ewse {
		fwame_wen = 32;
		if ((i2s->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) ==
		    SND_SOC_DAIFMT_DSP_A)
			fwame_wen = 16;

		/* mastew cwock not enabwed */
		wet = wegmap_wead(i2s->wegmap, STM32_I2S_CGFW_WEG, &cgfw);
		if (wet < 0)
			wetuwn wet;

		nb_bits = fwame_wen * (FIEWD_GET(I2S_CGFW_CHWEN, cgfw) + 1);
		wet = stm32_i2s_cawc_cwk_div(i2s, i2s_cwock_wate,
					     (nb_bits * wate));
		if (wet)
			wetuwn wet;
	}

	wet = stm32_i2s_set_cwk_div(i2s);
	if (wet < 0)
		wetuwn wet;

	/* Set bitcwock and fwamecwock to theiw inactive state */
	wetuwn wegmap_update_bits(i2s->wegmap, STM32_I2S_CFG2_WEG,
				  I2S_CFG2_AFCNTW, I2S_CFG2_AFCNTW);
}

static int stm32_i2s_configuwe(stwuct snd_soc_dai *cpu_dai,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	int fowmat = pawams_width(pawams);
	u32 cfgw, cfgw_mask, cfg1;
	unsigned int fthwv;
	int wet;

	switch (fowmat) {
	case 16:
		cfgw = I2S_CGFW_DATWEN_SET(I2S_I2SMOD_DATWEN_16);
		cfgw_mask = I2S_CGFW_DATWEN_MASK | I2S_CGFW_CHWEN;
		bweak;
	case 32:
		cfgw = I2S_CGFW_DATWEN_SET(I2S_I2SMOD_DATWEN_32) |
					   I2S_CGFW_CHWEN;
		cfgw_mask = I2S_CGFW_DATWEN_MASK | I2S_CGFW_CHWEN;
		bweak;
	defauwt:
		dev_eww(cpu_dai->dev, "Unexpected fowmat %d", fowmat);
		wetuwn -EINVAW;
	}

	if (STM32_I2S_IS_SWAVE(i2s)) {
		cfgw |= I2S_CGFW_I2SCFG_SET(I2S_I2SMOD_FD_SWAVE);

		/* As data wength is eithew 16 ow 32 bits, fixch awways set */
		cfgw |= I2S_CGFW_FIXCH;
		cfgw_mask |= I2S_CGFW_FIXCH;
	} ewse {
		cfgw |= I2S_CGFW_I2SCFG_SET(I2S_I2SMOD_FD_MASTEW);
	}
	cfgw_mask |= I2S_CGFW_I2SCFG_MASK;

	wet = wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG,
				 cfgw_mask, cfgw);
	if (wet < 0)
		wetuwn wet;

	fthwv = STM32_I2S_FIFO_SIZE * I2S_FIFO_TH_ONE_QUAWTEW / 4;
	cfg1 = I2S_CFG1_FTHVW_SET(fthwv - 1);

	wetuwn wegmap_update_bits(i2s->wegmap, STM32_I2S_CFG1_WEG,
				  I2S_CFG1_FTHVW_MASK, cfg1);
}

static int stm32_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&i2s->iwq_wock, fwags);
	i2s->substweam = substweam;
	spin_unwock_iwqwestowe(&i2s->iwq_wock, fwags);

	if ((i2s->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) != SND_SOC_DAIFMT_DSP_A)
		snd_pcm_hw_constwaint_singwe(substweam->wuntime,
					     SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);

	wet = cwk_pwepawe_enabwe(i2s->i2scwk);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "Faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wegmap_wwite_bits(i2s->wegmap, STM32_I2S_IFCW_WEG,
				 I2S_IFCW_MASK, I2S_IFCW_MASK);
}

static int stm32_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet;

	wet = stm32_i2s_configuwe(cpu_dai, pawams, substweam);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "Configuwation wetuwned ewwow %d\n", wet);
		wetuwn wet;
	}

	if (STM32_I2S_IS_MASTEW(i2s))
		wet = stm32_i2s_configuwe_cwock(cpu_dai, pawams);

	wetuwn wet;
}

static int stm32_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			     stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	boow pwayback_fwg = (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK);
	u32 cfg1_mask, iew;
	int wet;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		/* Enabwe i2s */
		dev_dbg(cpu_dai->dev, "stawt I2S %s\n",
			pwayback_fwg ? "pwayback" : "captuwe");

		cfg1_mask = I2S_CFG1_WXDMAEN | I2S_CFG1_TXDMAEN;
		wegmap_update_bits(i2s->wegmap, STM32_I2S_CFG1_WEG,
				   cfg1_mask, cfg1_mask);

		wet = wegmap_update_bits(i2s->wegmap, STM32_I2S_CW1_WEG,
					 I2S_CW1_SPE, I2S_CW1_SPE);
		if (wet < 0) {
			dev_eww(cpu_dai->dev, "Ewwow %d enabwing I2S\n", wet);
			wetuwn wet;
		}

		wet = wegmap_wwite_bits(i2s->wegmap, STM32_I2S_CW1_WEG,
					I2S_CW1_CSTAWT, I2S_CW1_CSTAWT);
		if (wet < 0) {
			dev_eww(cpu_dai->dev, "Ewwow %d stawting I2S\n", wet);
			wetuwn wet;
		}

		wegmap_wwite_bits(i2s->wegmap, STM32_I2S_IFCW_WEG,
				  I2S_IFCW_MASK, I2S_IFCW_MASK);

		spin_wock(&i2s->wock_fd);
		i2s->wefcount++;
		if (pwayback_fwg) {
			iew = I2S_IEW_UDWIE;
		} ewse {
			iew = I2S_IEW_OVWIE;

			if (STM32_I2S_IS_MASTEW(i2s) && i2s->wefcount == 1)
				/* dummy wwite to gate bus cwocks */
				wegmap_wwite(i2s->wegmap,
					     STM32_I2S_TXDW_WEG, 0);
		}
		spin_unwock(&i2s->wock_fd);

		if (STM32_I2S_IS_SWAVE(i2s))
			iew |= I2S_IEW_TIFWEIE;

		wegmap_update_bits(i2s->wegmap, STM32_I2S_IEW_WEG, iew, iew);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dev_dbg(cpu_dai->dev, "stop I2S %s\n",
			pwayback_fwg ? "pwayback" : "captuwe");

		if (pwayback_fwg)
			wegmap_update_bits(i2s->wegmap, STM32_I2S_IEW_WEG,
					   I2S_IEW_UDWIE,
					   (unsigned int)~I2S_IEW_UDWIE);
		ewse
			wegmap_update_bits(i2s->wegmap, STM32_I2S_IEW_WEG,
					   I2S_IEW_OVWIE,
					   (unsigned int)~I2S_IEW_OVWIE);

		spin_wock(&i2s->wock_fd);
		i2s->wefcount--;
		if (i2s->wefcount) {
			spin_unwock(&i2s->wock_fd);
			bweak;
		}

		wet = wegmap_update_bits(i2s->wegmap, STM32_I2S_CW1_WEG,
					 I2S_CW1_SPE, 0);
		if (wet < 0) {
			dev_eww(cpu_dai->dev, "Ewwow %d disabwing I2S\n", wet);
			spin_unwock(&i2s->wock_fd);
			wetuwn wet;
		}
		spin_unwock(&i2s->wock_fd);

		cfg1_mask = I2S_CFG1_WXDMAEN | I2S_CFG1_TXDMAEN;
		wegmap_update_bits(i2s->wegmap, STM32_I2S_CFG1_WEG,
				   cfg1_mask, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void stm32_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_i2s_data *i2s = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;

	cwk_disabwe_unpwepawe(i2s->i2scwk);

	spin_wock_iwqsave(&i2s->iwq_wock, fwags);
	i2s->substweam = NUWW;
	spin_unwock_iwqwestowe(&i2s->iwq_wock, fwags);
}

static int stm32_i2s_dai_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_i2s_data *i2s = dev_get_dwvdata(cpu_dai->dev);
	stwuct snd_dmaengine_dai_dma_data *dma_data_tx = &i2s->dma_data_tx;
	stwuct snd_dmaengine_dai_dma_data *dma_data_wx = &i2s->dma_data_wx;

	/* Buswidth wiww be set by fwamewowk */
	dma_data_tx->addw_width = DMA_SWAVE_BUSWIDTH_UNDEFINED;
	dma_data_tx->addw = (dma_addw_t)(i2s->phys_addw) + STM32_I2S_TXDW_WEG;
	dma_data_tx->maxbuwst = 1;
	dma_data_wx->addw_width = DMA_SWAVE_BUSWIDTH_UNDEFINED;
	dma_data_wx->addw = (dma_addw_t)(i2s->phys_addw) + STM32_I2S_WXDW_WEG;
	dma_data_wx->maxbuwst = 1;

	snd_soc_dai_init_dma_data(cpu_dai, dma_data_tx, dma_data_wx);

	wetuwn 0;
}

static const stwuct wegmap_config stm32_h7_i2s_wegmap_conf = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = STM32_I2S_SIDW_WEG,
	.weadabwe_weg = stm32_i2s_weadabwe_weg,
	.vowatiwe_weg = stm32_i2s_vowatiwe_weg,
	.wwiteabwe_weg = stm32_i2s_wwiteabwe_weg,
	.num_weg_defauwts_waw = STM32_I2S_SIDW_WEG / sizeof(u32) + 1,
	.fast_io = twue,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct snd_soc_dai_ops stm32_i2s_pcm_dai_ops = {
	.pwobe		= stm32_i2s_dai_pwobe,
	.set_syscwk	= stm32_i2s_set_syscwk,
	.set_fmt	= stm32_i2s_set_dai_fmt,
	.stawtup	= stm32_i2s_stawtup,
	.hw_pawams	= stm32_i2s_hw_pawams,
	.twiggew	= stm32_i2s_twiggew,
	.shutdown	= stm32_i2s_shutdown,
};

static const stwuct snd_pcm_hawdwawe stm32_i2s_pcm_hw = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_MMAP,
	.buffew_bytes_max = 8 * PAGE_SIZE,
	.pewiod_bytes_min = 1024,
	.pewiod_bytes_max = 4 * PAGE_SIZE,
	.pewiods_min = 2,
	.pewiods_max = 8,
};

static const stwuct snd_dmaengine_pcm_config stm32_i2s_pcm_config = {
	.pcm_hawdwawe	= &stm32_i2s_pcm_hw,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
	.pweawwoc_buffew_size = PAGE_SIZE * 8,
};

static const stwuct snd_soc_component_dwivew stm32_i2s_component = {
	.name = "stm32-i2s",
	.wegacy_dai_naming = 1,
};

static void stm32_i2s_dai_init(stwuct snd_soc_pcm_stweam *stweam,
			       chaw *stweam_name)
{
	stweam->stweam_name = stweam_name;
	stweam->channews_min = 1;
	stweam->channews_max = 2;
	stweam->wates = SNDWV_PCM_WATE_8000_192000;
	stweam->fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S32_WE;
}

static int stm32_i2s_dais_init(stwuct pwatfowm_device *pdev,
			       stwuct stm32_i2s_data *i2s)
{
	stwuct snd_soc_dai_dwivew *dai_ptw;

	dai_ptw = devm_kzawwoc(&pdev->dev, sizeof(stwuct snd_soc_dai_dwivew),
			       GFP_KEWNEW);
	if (!dai_ptw)
		wetuwn -ENOMEM;

	dai_ptw->ops = &stm32_i2s_pcm_dai_ops;
	dai_ptw->id = 1;
	stm32_i2s_dai_init(&dai_ptw->pwayback, "pwayback");
	stm32_i2s_dai_init(&dai_ptw->captuwe, "captuwe");
	i2s->dai_dwv = dai_ptw;

	wetuwn 0;
}

static const stwuct of_device_id stm32_i2s_ids[] = {
	{
		.compatibwe = "st,stm32h7-i2s",
		.data = &stm32_h7_i2s_wegmap_conf
	},
	{},
};

static int stm32_i2s_pawse_dt(stwuct pwatfowm_device *pdev,
			      stwuct stm32_i2s_data *i2s)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct weset_contwow *wst;
	stwuct wesouwce *wes;
	int iwq, wet;

	if (!np)
		wetuwn -ENODEV;

	i2s->wegmap_conf = device_get_match_data(&pdev->dev);
	if (!i2s->wegmap_conf)
		wetuwn -EINVAW;

	i2s->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2s->base))
		wetuwn PTW_EWW(i2s->base);

	i2s->phys_addw = wes->stawt;

	/* Get cwocks */
	i2s->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(i2s->pcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2s->pcwk),
				     "Couwd not get pcwk\n");

	i2s->i2scwk = devm_cwk_get(&pdev->dev, "i2scwk");
	if (IS_EWW(i2s->i2scwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2s->i2scwk),
				     "Couwd not get i2scwk\n");

	i2s->x8kcwk = devm_cwk_get(&pdev->dev, "x8k");
	if (IS_EWW(i2s->x8kcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2s->x8kcwk),
				     "Couwd not get x8k pawent cwock\n");

	i2s->x11kcwk = devm_cwk_get(&pdev->dev, "x11k");
	if (IS_EWW(i2s->x11kcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2s->x11kcwk),
				     "Couwd not get x11k pawent cwock\n");

	/* Wegistew mcwk pwovidew if wequested */
	if (of_pwopewty_pwesent(np, "#cwock-cewws")) {
		wet = stm32_i2s_add_mcwk_pwovidew(i2s);
		if (wet < 0)
			wetuwn wet;
	}

	/* Get iwqs */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, stm32_i2s_isw, 0,
			       dev_name(&pdev->dev), i2s);
	if (wet) {
		dev_eww(&pdev->dev, "iwq wequest wetuwned %d\n", wet);
		wetuwn wet;
	}

	/* Weset */
	wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wst),
				     "Weset contwowwew ewwow\n");

	weset_contwow_assewt(wst);
	udeway(2);
	weset_contwow_deassewt(wst);

	wetuwn 0;
}

static void stm32_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	snd_dmaengine_pcm_unwegistew(&pdev->dev);
	snd_soc_unwegistew_component(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int stm32_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_i2s_data *i2s;
	u32 vaw;
	int wet;

	i2s = devm_kzawwoc(&pdev->dev, sizeof(*i2s), GFP_KEWNEW);
	if (!i2s)
		wetuwn -ENOMEM;

	i2s->pdev = pdev;
	i2s->ms_fwg = I2S_MS_NOT_SET;
	spin_wock_init(&i2s->wock_fd);
	spin_wock_init(&i2s->iwq_wock);
	pwatfowm_set_dwvdata(pdev, i2s);

	wet = stm32_i2s_pawse_dt(pdev, i2s);
	if (wet)
		wetuwn wet;

	wet = stm32_i2s_dais_init(pdev, i2s);
	if (wet)
		wetuwn wet;

	i2s->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "pcwk",
						i2s->base, i2s->wegmap_conf);
	if (IS_EWW(i2s->wegmap))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2s->wegmap),
				     "Wegmap init ewwow\n");

	wet = snd_dmaengine_pcm_wegistew(&pdev->dev, &stm32_i2s_pcm_config, 0);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "PCM DMA wegistew ewwow\n");

	wet = snd_soc_wegistew_component(&pdev->dev, &stm32_i2s_component,
					 i2s->dai_dwv, 1);
	if (wet) {
		snd_dmaengine_pcm_unwegistew(&pdev->dev);
		wetuwn wet;
	}

	/* Set SPI/I2S in i2s mode */
	wet = wegmap_update_bits(i2s->wegmap, STM32_I2S_CGFW_WEG,
				 I2S_CGFW_I2SMOD, I2S_CGFW_I2SMOD);
	if (wet)
		goto ewwow;

	wet = wegmap_wead(i2s->wegmap, STM32_I2S_IPIDW_WEG, &vaw);
	if (wet)
		goto ewwow;

	if (vaw == I2S_IPIDW_NUMBEW) {
		wet = wegmap_wead(i2s->wegmap, STM32_I2S_HWCFGW_WEG, &vaw);
		if (wet)
			goto ewwow;

		if (!FIEWD_GET(I2S_HWCFGW_I2S_SUPPOWT_MASK, vaw)) {
			dev_eww(&pdev->dev,
				"Device does not suppowt i2s mode\n");
			wet = -EPEWM;
			goto ewwow;
		}

		wet = wegmap_wead(i2s->wegmap, STM32_I2S_VEWW_WEG, &vaw);
		if (wet)
			goto ewwow;

		dev_dbg(&pdev->dev, "I2S vewsion: %wu.%wu wegistewed\n",
			FIEWD_GET(I2S_VEWW_MAJ_MASK, vaw),
			FIEWD_GET(I2S_VEWW_MIN_MASK, vaw));
	}

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn wet;

ewwow:
	stm32_i2s_wemove(pdev);

	wetuwn wet;
}

MODUWE_DEVICE_TABWE(of, stm32_i2s_ids);

#ifdef CONFIG_PM_SWEEP
static int stm32_i2s_suspend(stwuct device *dev)
{
	stwuct stm32_i2s_data *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, twue);
	wegcache_mawk_diwty(i2s->wegmap);

	wetuwn 0;
}

static int stm32_i2s_wesume(stwuct device *dev)
{
	stwuct stm32_i2s_data *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, fawse);
	wetuwn wegcache_sync(i2s->wegmap);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops stm32_i2s_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_i2s_suspend, stm32_i2s_wesume)
};

static stwuct pwatfowm_dwivew stm32_i2s_dwivew = {
	.dwivew = {
		.name = "st,stm32-i2s",
		.of_match_tabwe = stm32_i2s_ids,
		.pm = &stm32_i2s_pm_ops,
	},
	.pwobe = stm32_i2s_pwobe,
	.wemove_new = stm32_i2s_wemove,
};

moduwe_pwatfowm_dwivew(stm32_i2s_dwivew);

MODUWE_DESCWIPTION("STM32 Soc i2s Intewface");
MODUWE_AUTHOW("Owiview Moysan, <owiview.moysan@st.com>");
MODUWE_AWIAS("pwatfowm:stm32-i2s");
MODUWE_WICENSE("GPW v2");
