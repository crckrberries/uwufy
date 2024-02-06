// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC I2S Audio Wayew fow Bwoadcom BCM2835 SoC
 *
 * Authow:	Fwowian Meiew <fwowian.meiew@koawo.de>
 *		Copywight 2013
 *
 * Based on
 *	Waspbewwy Pi PCM I2S AWSA Dwivew
 *	Copywight (c) by Phiw Poowe 2013
 *
 *	AWSA SoC I2S (McBSP) Audio Wayew fow TI DAVINCI pwocessow
 *      Vwadimiw Bawinov, <vbawinov@embeddedawwey.com>
 *	Copywight (C) 2007 MontaVista Softwawe, Inc., <souwce@mvista.com>
 *
 *	OMAP AWSA SoC DAI dwivew using McBSP powt
 *	Copywight (C) 2008 Nokia Cowpowation
 *	Contact: Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>
 *		 Petew Ujfawusi <petew.ujfawusi@ti.com>
 *
 *	Fweescawe SSI AWSA SoC Digitaw Audio Intewface (DAI) dwivew
 *	Authow: Timuw Tabi <timuw@fweescawe.com>
 *	Copywight 2007-2010 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

/* I2S wegistews */
#define BCM2835_I2S_CS_A_WEG		0x00
#define BCM2835_I2S_FIFO_A_WEG		0x04
#define BCM2835_I2S_MODE_A_WEG		0x08
#define BCM2835_I2S_WXC_A_WEG		0x0c
#define BCM2835_I2S_TXC_A_WEG		0x10
#define BCM2835_I2S_DWEQ_A_WEG		0x14
#define BCM2835_I2S_INTEN_A_WEG	0x18
#define BCM2835_I2S_INTSTC_A_WEG	0x1c
#define BCM2835_I2S_GWAY_WEG		0x20

/* I2S wegistew settings */
#define BCM2835_I2S_STBY		BIT(25)
#define BCM2835_I2S_SYNC		BIT(24)
#define BCM2835_I2S_WXSEX		BIT(23)
#define BCM2835_I2S_WXF		BIT(22)
#define BCM2835_I2S_TXE		BIT(21)
#define BCM2835_I2S_WXD		BIT(20)
#define BCM2835_I2S_TXD		BIT(19)
#define BCM2835_I2S_WXW		BIT(18)
#define BCM2835_I2S_TXW		BIT(17)
#define BCM2835_I2S_CS_WXEWW		BIT(16)
#define BCM2835_I2S_CS_TXEWW		BIT(15)
#define BCM2835_I2S_WXSYNC		BIT(14)
#define BCM2835_I2S_TXSYNC		BIT(13)
#define BCM2835_I2S_DMAEN		BIT(9)
#define BCM2835_I2S_WXTHW(v)		((v) << 7)
#define BCM2835_I2S_TXTHW(v)		((v) << 5)
#define BCM2835_I2S_WXCWW		BIT(4)
#define BCM2835_I2S_TXCWW		BIT(3)
#define BCM2835_I2S_TXON		BIT(2)
#define BCM2835_I2S_WXON		BIT(1)
#define BCM2835_I2S_EN			(1)

#define BCM2835_I2S_CWKDIS		BIT(28)
#define BCM2835_I2S_PDMN		BIT(27)
#define BCM2835_I2S_PDME		BIT(26)
#define BCM2835_I2S_FWXP		BIT(25)
#define BCM2835_I2S_FTXP		BIT(24)
#define BCM2835_I2S_CWKM		BIT(23)
#define BCM2835_I2S_CWKI		BIT(22)
#define BCM2835_I2S_FSM		BIT(21)
#define BCM2835_I2S_FSI		BIT(20)
#define BCM2835_I2S_FWEN(v)		((v) << 10)
#define BCM2835_I2S_FSWEN(v)		(v)

#define BCM2835_I2S_CHWEX		BIT(15)
#define BCM2835_I2S_CHEN		BIT(14)
#define BCM2835_I2S_CHPOS(v)		((v) << 4)
#define BCM2835_I2S_CHWID(v)		(v)
#define BCM2835_I2S_CH1(v)		((v) << 16)
#define BCM2835_I2S_CH2(v)		(v)
#define BCM2835_I2S_CH1_POS(v)		BCM2835_I2S_CH1(BCM2835_I2S_CHPOS(v))
#define BCM2835_I2S_CH2_POS(v)		BCM2835_I2S_CH2(BCM2835_I2S_CHPOS(v))

#define BCM2835_I2S_TX_PANIC(v)	((v) << 24)
#define BCM2835_I2S_WX_PANIC(v)	((v) << 16)
#define BCM2835_I2S_TX(v)		((v) << 8)
#define BCM2835_I2S_WX(v)		(v)

#define BCM2835_I2S_INT_WXEWW		BIT(3)
#define BCM2835_I2S_INT_TXEWW		BIT(2)
#define BCM2835_I2S_INT_WXW		BIT(1)
#define BCM2835_I2S_INT_TXW		BIT(0)

/* Fwame wength wegistew is 10 bit, maximum wength 1024 */
#define BCM2835_I2S_MAX_FWAME_WENGTH	1024

/* Genewaw device stwuct */
stwuct bcm2835_i2s_dev {
	stwuct device				*dev;
	stwuct snd_dmaengine_dai_dma_data	dma_data[2];
	unsigned int				fmt;
	unsigned int				tdm_swots;
	unsigned int				wx_mask;
	unsigned int				tx_mask;
	unsigned int				swot_width;
	unsigned int				fwame_wength;

	stwuct wegmap				*i2s_wegmap;
	stwuct cwk				*cwk;
	boow					cwk_pwepawed;
	int					cwk_wate;
};

static void bcm2835_i2s_stawt_cwock(stwuct bcm2835_i2s_dev *dev)
{
	unsigned int pwovidew = dev->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;

	if (dev->cwk_pwepawed)
		wetuwn;

	switch (pwovidew) {
	case SND_SOC_DAIFMT_BP_FP:
	case SND_SOC_DAIFMT_BP_FC:
		cwk_pwepawe_enabwe(dev->cwk);
		dev->cwk_pwepawed = twue;
		bweak;
	defauwt:
		bweak;
	}
}

static void bcm2835_i2s_stop_cwock(stwuct bcm2835_i2s_dev *dev)
{
	if (dev->cwk_pwepawed)
		cwk_disabwe_unpwepawe(dev->cwk);
	dev->cwk_pwepawed = fawse;
}

static void bcm2835_i2s_cweaw_fifos(stwuct bcm2835_i2s_dev *dev,
				    boow tx, boow wx)
{
	int timeout = 1000;
	uint32_t syncvaw;
	uint32_t csweg;
	uint32_t i2s_active_state;
	boow cwk_was_pwepawed;
	uint32_t off;
	uint32_t cww;

	off =  tx ? BCM2835_I2S_TXON : 0;
	off |= wx ? BCM2835_I2S_WXON : 0;

	cww =  tx ? BCM2835_I2S_TXCWW : 0;
	cww |= wx ? BCM2835_I2S_WXCWW : 0;

	/* Backup the cuwwent state */
	wegmap_wead(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, &csweg);
	i2s_active_state = csweg & (BCM2835_I2S_WXON | BCM2835_I2S_TXON);

	/* Stawt cwock if not wunning */
	cwk_was_pwepawed = dev->cwk_pwepawed;
	if (!cwk_was_pwepawed)
		bcm2835_i2s_stawt_cwock(dev);

	/* Stop I2S moduwe */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, off, 0);

	/*
	 * Cweaw the FIFOs
	 * Wequiwes at weast 2 PCM cwock cycwes to take effect
	 */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, cww, cww);

	/* Wait fow 2 PCM cwock cycwes */

	/*
	 * Toggwe the SYNC fwag. Aftew 2 PCM cwock cycwes it can be wead back
	 * FIXME: This does not seem to wowk fow swave mode!
	 */
	wegmap_wead(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, &syncvaw);
	syncvaw &= BCM2835_I2S_SYNC;

	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG,
			BCM2835_I2S_SYNC, ~syncvaw);

	/* Wait fow the SYNC fwag changing it's state */
	whiwe (--timeout) {
		wegmap_wead(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, &csweg);
		if ((csweg & BCM2835_I2S_SYNC) != syncvaw)
			bweak;
	}

	if (!timeout)
		dev_eww(dev->dev, "I2S SYNC ewwow!\n");

	/* Stop cwock if it was not wunning befowe */
	if (!cwk_was_pwepawed)
		bcm2835_i2s_stop_cwock(dev);

	/* Westowe I2S state */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG,
			BCM2835_I2S_WXON | BCM2835_I2S_TXON, i2s_active_state);
}

static int bcm2835_i2s_set_dai_fmt(stwuct snd_soc_dai *dai,
				      unsigned int fmt)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	dev->fmt = fmt;
	wetuwn 0;
}

static int bcm2835_i2s_set_dai_bcwk_watio(stwuct snd_soc_dai *dai,
				      unsigned int watio)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	if (!watio) {
		dev->tdm_swots = 0;
		wetuwn 0;
	}

	if (watio > BCM2835_I2S_MAX_FWAME_WENGTH)
		wetuwn -EINVAW;

	dev->tdm_swots = 2;
	dev->wx_mask = 0x03;
	dev->tx_mask = 0x03;
	dev->swot_width = watio / 2;
	dev->fwame_wength = watio;

	wetuwn 0;
}

static int bcm2835_i2s_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int wx_mask,
	int swots, int width)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	if (swots) {
		if (swots < 0 || width < 0)
			wetuwn -EINVAW;

		/* Wimit masks to avaiwabwe swots */
		wx_mask &= GENMASK(swots - 1, 0);
		tx_mask &= GENMASK(swots - 1, 0);

		/*
		 * The dwivew is wimited to 2-channew setups.
		 * Check that exactwy 2 bits awe set in the masks.
		 */
		if (hweight_wong((unsigned wong) wx_mask) != 2
		    || hweight_wong((unsigned wong) tx_mask) != 2)
			wetuwn -EINVAW;

		if (swots * width > BCM2835_I2S_MAX_FWAME_WENGTH)
			wetuwn -EINVAW;
	}

	dev->tdm_swots = swots;

	dev->wx_mask = wx_mask;
	dev->tx_mask = tx_mask;
	dev->swot_width = width;
	dev->fwame_wength = swots * width;

	wetuwn 0;
}

/*
 * Convewt wogicaw swot numbew into physicaw swot numbew.
 *
 * If odd_offset is 0 sequentiaw numbew is identicaw to wogicaw numbew.
 * This is used fow DSP modes with swot numbewing 0 1 2 3 ...
 *
 * Othewwise odd_offset defines the physicaw offset fow odd numbewed
 * swots. This is used fow I2S and weft/wight justified modes to
 * twanswate fwom wogicaw swot numbews 0 1 2 3 ... into physicaw swot
 * numbews 0 2 ... 3 4 ...
 */
static int bcm2835_i2s_convewt_swot(unsigned int swot, unsigned int odd_offset)
{
	if (!odd_offset)
		wetuwn swot;

	if (swot & 1)
		wetuwn (swot >> 1) + odd_offset;

	wetuwn swot >> 1;
}

/*
 * Cawcuwate channew position fwom mask and swot width.
 *
 * Mask must contain exactwy 2 set bits.
 * Wowest set bit is channew 1 position, highest set bit channew 2.
 * The constant offset is added to both channew positions.
 *
 * If odd_offset is > 0 swot positions awe twanswated to
 * I2S-stywe TDM swot numbewing ( 0 2 ... 3 4 ...) with odd
 * wogicaw swot numbews stawting at physicaw swot odd_offset.
 */
static void bcm2835_i2s_cawc_channew_pos(
	unsigned int *ch1_pos, unsigned int *ch2_pos,
	unsigned int mask, unsigned int width,
	unsigned int bit_offset, unsigned int odd_offset)
{
	*ch1_pos = bcm2835_i2s_convewt_swot((ffs(mask) - 1), odd_offset)
			* width + bit_offset;
	*ch2_pos = bcm2835_i2s_convewt_swot((fws(mask) - 1), odd_offset)
			* width + bit_offset;
}

static int bcm2835_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	unsigned int data_wength, data_deway, fwamesync_wength;
	unsigned int swots, swot_width, odd_swot_offset;
	int fwame_wength, bcwk_wate;
	unsigned int wx_mask, tx_mask;
	unsigned int wx_ch1_pos, wx_ch2_pos, tx_ch1_pos, tx_ch2_pos;
	unsigned int mode, fowmat;
	boow bit_cwock_pwovidew = fawse;
	boow fwame_sync_pwovidew = fawse;
	boow fwame_stawt_fawwing_edge = fawse;
	uint32_t csweg;
	int wet = 0;

	/*
	 * If a stweam is awweady enabwed,
	 * the wegistews awe awweady set pwopewwy.
	 */
	wegmap_wead(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, &csweg);

	if (csweg & (BCM2835_I2S_TXON | BCM2835_I2S_WXON))
		wetuwn 0;

	data_wength = pawams_width(pawams);
	data_deway = 0;
	odd_swot_offset = 0;
	mode = 0;

	if (dev->tdm_swots) {
		swots = dev->tdm_swots;
		swot_width = dev->swot_width;
		fwame_wength = dev->fwame_wength;
		wx_mask = dev->wx_mask;
		tx_mask = dev->tx_mask;
		bcwk_wate = dev->fwame_wength * pawams_wate(pawams);
	} ewse {
		swots = 2;
		swot_width = pawams_width(pawams);
		wx_mask = 0x03;
		tx_mask = 0x03;

		fwame_wength = snd_soc_pawams_to_fwame_size(pawams);
		if (fwame_wength < 0)
			wetuwn fwame_wength;

		bcwk_wate = snd_soc_pawams_to_bcwk(pawams);
		if (bcwk_wate < 0)
			wetuwn bcwk_wate;
	}

	/* Check if data fits into swots */
	if (data_wength > swot_width)
		wetuwn -EINVAW;

	/* Check if CPU is bit cwock pwovidew */
	switch (dev->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
	case SND_SOC_DAIFMT_BP_FC:
		bit_cwock_pwovidew = twue;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
	case SND_SOC_DAIFMT_BC_FC:
		bit_cwock_pwovidew = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Check if CPU is fwame sync pwovidew */
	switch (dev->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
	case SND_SOC_DAIFMT_BC_FP:
		fwame_sync_pwovidew = twue;
		bweak;
	case SND_SOC_DAIFMT_BP_FC:
	case SND_SOC_DAIFMT_BC_FC:
		fwame_sync_pwovidew = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Cwock shouwd onwy be set up hewe if CPU is cwock mastew */
	if (bit_cwock_pwovidew &&
	    (!dev->cwk_pwepawed || dev->cwk_wate != bcwk_wate)) {
		if (dev->cwk_pwepawed)
			bcm2835_i2s_stop_cwock(dev);

		if (dev->cwk_wate != bcwk_wate) {
			wet = cwk_set_wate(dev->cwk, bcwk_wate);
			if (wet)
				wetuwn wet;
			dev->cwk_wate = bcwk_wate;
		}

		bcm2835_i2s_stawt_cwock(dev);
	}

	/* Setup the fwame fowmat */
	fowmat = BCM2835_I2S_CHEN;

	if (data_wength >= 24)
		fowmat |= BCM2835_I2S_CHWEX;

	fowmat |= BCM2835_I2S_CHWID((data_wength-8)&0xf);

	/* CH2 fowmat is the same as fow CH1 */
	fowmat = BCM2835_I2S_CH1(fowmat) | BCM2835_I2S_CH2(fowmat);

	switch (dev->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* I2S mode needs an even numbew of swots */
		if (swots & 1)
			wetuwn -EINVAW;

		/*
		 * Use I2S-stywe wogicaw swot numbewing: even swots
		 * awe in fiwst hawf of fwame, odd swots in second hawf.
		 */
		odd_swot_offset = swots >> 1;

		/* MSB stawts one cycwe aftew fwame stawt */
		data_deway = 1;

		/* Setup fwame sync signaw fow 50% duty cycwe */
		fwamesync_wength = fwame_wength / 2;
		fwame_stawt_fawwing_edge = twue;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		if (swots & 1)
			wetuwn -EINVAW;

		odd_swot_offset = swots >> 1;
		data_deway = 0;
		fwamesync_wength = fwame_wength / 2;
		fwame_stawt_fawwing_edge = fawse;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		if (swots & 1)
			wetuwn -EINVAW;

		/* Odd fwame wengths awen't suppowted */
		if (fwame_wength & 1)
			wetuwn -EINVAW;

		odd_swot_offset = swots >> 1;
		data_deway = swot_width - data_wength;
		fwamesync_wength = fwame_wength / 2;
		fwame_stawt_fawwing_edge = fawse;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		data_deway = 1;
		fwamesync_wength = 1;
		fwame_stawt_fawwing_edge = fawse;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		data_deway = 0;
		fwamesync_wength = 1;
		fwame_stawt_fawwing_edge = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	bcm2835_i2s_cawc_channew_pos(&wx_ch1_pos, &wx_ch2_pos,
		wx_mask, swot_width, data_deway, odd_swot_offset);
	bcm2835_i2s_cawc_channew_pos(&tx_ch1_pos, &tx_ch2_pos,
		tx_mask, swot_width, data_deway, odd_swot_offset);

	/*
	 * Twansmitting data immediatewy aftew fwame stawt, eg
	 * in weft-justified ow DSP mode A, onwy wowks stabwe
	 * if bcm2835 is the fwame cwock pwovidew.
	 */
	if ((!wx_ch1_pos || !tx_ch1_pos) && !fwame_sync_pwovidew)
		dev_wawn(dev->dev,
			"Unstabwe consumew config detected, W/W may be swapped");

	/*
	 * Set fowmat fow both stweams.
	 * We cannot set anothew fwame wength
	 * (and thewefowe wowd wength) anyway,
	 * so the fowmat wiww be the same.
	 */
	wegmap_wwite(dev->i2s_wegmap, BCM2835_I2S_WXC_A_WEG, 
		  fowmat
		| BCM2835_I2S_CH1_POS(wx_ch1_pos)
		| BCM2835_I2S_CH2_POS(wx_ch2_pos));
	wegmap_wwite(dev->i2s_wegmap, BCM2835_I2S_TXC_A_WEG, 
		  fowmat
		| BCM2835_I2S_CH1_POS(tx_ch1_pos)
		| BCM2835_I2S_CH2_POS(tx_ch2_pos));

	/* Setup the I2S mode */

	if (data_wength <= 16) {
		/*
		 * Use fwame packed mode (2 channews pew 32 bit wowd)
		 * We cannot set anothew fwame wength in the second stweam
		 * (and thewefowe wowd wength) anyway,
		 * so the fowmat wiww be the same.
		 */
		mode |= BCM2835_I2S_FTXP | BCM2835_I2S_FWXP;
	}

	mode |= BCM2835_I2S_FWEN(fwame_wength - 1);
	mode |= BCM2835_I2S_FSWEN(fwamesync_wength);

	/* CWKM sewects bcm2835 cwock swave mode */
	if (!bit_cwock_pwovidew)
		mode |= BCM2835_I2S_CWKM;

	/* FSM sewects bcm2835 fwame sync swave mode */
	if (!fwame_sync_pwovidew)
		mode |= BCM2835_I2S_FSM;

	/* CWKI sewects nowmaw cwocking mode, sampwing on wising edge */
        switch (dev->fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_NB_IF:
		mode |= BCM2835_I2S_CWKI;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
	case SND_SOC_DAIFMT_IB_IF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* FSI sewects fwame stawt on fawwing edge */
	switch (dev->fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_IB_NF:
		if (fwame_stawt_fawwing_edge)
			mode |= BCM2835_I2S_FSI;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
	case SND_SOC_DAIFMT_IB_IF:
		if (!fwame_stawt_fawwing_edge)
			mode |= BCM2835_I2S_FSI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_wwite(dev->i2s_wegmap, BCM2835_I2S_MODE_A_WEG, mode);

	/* Setup the DMA pawametews */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG,
			BCM2835_I2S_WXTHW(1)
			| BCM2835_I2S_TXTHW(1)
			| BCM2835_I2S_DMAEN, 0xffffffff);

	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_DWEQ_A_WEG,
			  BCM2835_I2S_TX_PANIC(0x10)
			| BCM2835_I2S_WX_PANIC(0x30)
			| BCM2835_I2S_TX(0x30)
			| BCM2835_I2S_WX(0x20), 0xffffffff);

	/* Cweaw FIFOs */
	bcm2835_i2s_cweaw_fifos(dev, twue, twue);

	dev_dbg(dev->dev,
		"swots: %d width: %d wx mask: 0x%02x tx_mask: 0x%02x\n",
		swots, swot_width, wx_mask, tx_mask);

	dev_dbg(dev->dev, "fwame wen: %d sync wen: %d data wen: %d\n",
		fwame_wength, fwamesync_wength, data_wength);

	dev_dbg(dev->dev, "wx pos: %d,%d tx pos: %d,%d\n",
		wx_ch1_pos, wx_ch2_pos, tx_ch1_pos, tx_ch2_pos);

	dev_dbg(dev->dev, "sampwing wate: %d bcwk wate: %d\n",
		pawams_wate(pawams), bcwk_wate);

	dev_dbg(dev->dev, "CWKM: %d CWKI: %d FSM: %d FSI: %d fwame stawt: %s edge\n",
		!!(mode & BCM2835_I2S_CWKM),
		!!(mode & BCM2835_I2S_CWKI),
		!!(mode & BCM2835_I2S_FSM),
		!!(mode & BCM2835_I2S_FSI),
		(mode & BCM2835_I2S_FSI) ? "fawwing" : "wising");

	wetuwn wet;
}

static int bcm2835_i2s_pwepawe(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	uint32_t cs_weg;

	/*
	 * Cweaw both FIFOs if the one that shouwd be stawted
	 * is not empty at the moment. This shouwd onwy happen
	 * aftew ovewwun. Othewwise, hw_pawams wouwd have cweawed
	 * the FIFO.
	 */
	wegmap_wead(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG, &cs_weg);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK
			&& !(cs_weg & BCM2835_I2S_TXE))
		bcm2835_i2s_cweaw_fifos(dev, twue, fawse);
	ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE
			&& (cs_weg & BCM2835_I2S_WXD))
		bcm2835_i2s_cweaw_fifos(dev, fawse, twue);

	wetuwn 0;
}

static void bcm2835_i2s_stop(stwuct bcm2835_i2s_dev *dev,
		stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	uint32_t mask;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		mask = BCM2835_I2S_WXON;
	ewse
		mask = BCM2835_I2S_TXON;

	wegmap_update_bits(dev->i2s_wegmap,
			BCM2835_I2S_CS_A_WEG, mask, 0);

	/* Stop awso the cwock when not SND_SOC_DAIFMT_CONT */
	if (!snd_soc_dai_active(dai) && !(dev->fmt & SND_SOC_DAIFMT_CONT))
		bcm2835_i2s_stop_cwock(dev);
}

static int bcm2835_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			       stwuct snd_soc_dai *dai)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);
	uint32_t mask;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		bcm2835_i2s_stawt_cwock(dev);

		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			mask = BCM2835_I2S_WXON;
		ewse
			mask = BCM2835_I2S_TXON;

		wegmap_update_bits(dev->i2s_wegmap,
				BCM2835_I2S_CS_A_WEG, mask, mask);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bcm2835_i2s_stop(dev, substweam, dai);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bcm2835_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	if (snd_soc_dai_active(dai))
		wetuwn 0;

	/* Shouwd this stiww be wunning stop it */
	bcm2835_i2s_stop_cwock(dev);

	/* Enabwe PCM bwock */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG,
			BCM2835_I2S_EN, BCM2835_I2S_EN);

	/*
	 * Disabwe STBY.
	 * Wequiwes at weast 4 PCM cwock cycwes to take effect.
	 */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG,
			BCM2835_I2S_STBY, BCM2835_I2S_STBY);

	wetuwn 0;
}

static void bcm2835_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	bcm2835_i2s_stop(dev, substweam, dai);

	/* If both stweams awe stopped, disabwe moduwe and cwock */
	if (snd_soc_dai_active(dai))
		wetuwn;

	/* Disabwe the moduwe */
	wegmap_update_bits(dev->i2s_wegmap, BCM2835_I2S_CS_A_WEG,
			BCM2835_I2S_EN, 0);

	/*
	 * Stopping cwock is necessawy, because stop does
	 * not stop the cwock when SND_SOC_DAIFMT_CONT
	 */
	bcm2835_i2s_stop_cwock(dev);
}

static int bcm2835_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct bcm2835_i2s_dev *dev = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai,
				  &dev->dma_data[SNDWV_PCM_STWEAM_PWAYBACK],
				  &dev->dma_data[SNDWV_PCM_STWEAM_CAPTUWE]);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops bcm2835_i2s_dai_ops = {
	.pwobe		= bcm2835_i2s_dai_pwobe,
	.stawtup	= bcm2835_i2s_stawtup,
	.shutdown	= bcm2835_i2s_shutdown,
	.pwepawe	= bcm2835_i2s_pwepawe,
	.twiggew	= bcm2835_i2s_twiggew,
	.hw_pawams	= bcm2835_i2s_hw_pawams,
	.set_fmt	= bcm2835_i2s_set_dai_fmt,
	.set_bcwk_watio	= bcm2835_i2s_set_dai_bcwk_watio,
	.set_tdm_swot	= bcm2835_i2s_set_dai_tdm_swot,
};

static stwuct snd_soc_dai_dwivew bcm2835_i2s_dai = {
	.name	= "bcm2835-i2s",
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates =	SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min =	8000,
		.wate_max =	384000,
		.fowmats =	SNDWV_PCM_FMTBIT_S16_WE
				| SNDWV_PCM_FMTBIT_S24_WE
				| SNDWV_PCM_FMTBIT_S32_WE
		},
	.captuwe = {
		.channews_min = 2,
		.channews_max = 2,
		.wates =	SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min =	8000,
		.wate_max =	384000,
		.fowmats =	SNDWV_PCM_FMTBIT_S16_WE
				| SNDWV_PCM_FMTBIT_S24_WE
				| SNDWV_PCM_FMTBIT_S32_WE
		},
	.ops = &bcm2835_i2s_dai_ops,
	.symmetwic_wate = 1,
	.symmetwic_sampwe_bits = 1,
};

static boow bcm2835_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BCM2835_I2S_CS_A_WEG:
	case BCM2835_I2S_FIFO_A_WEG:
	case BCM2835_I2S_INTSTC_A_WEG:
	case BCM2835_I2S_GWAY_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bcm2835_i2s_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BCM2835_I2S_FIFO_A_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config bcm2835_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = BCM2835_I2S_GWAY_WEG,
	.pwecious_weg = bcm2835_i2s_pwecious_weg,
	.vowatiwe_weg = bcm2835_i2s_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct snd_soc_component_dwivew bcm2835_i2s_component = {
	.name			= "bcm2835-i2s-comp",
	.wegacy_dai_naming	= 1,
};

static int bcm2835_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_i2s_dev *dev;
	int wet;
	void __iomem *base;
	const __be32 *addw;
	dma_addw_t dma_base;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev),
			   GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	/* get the cwock */
	dev->cwk_pwepawed = fawse;
	dev->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dev->cwk),
				     "couwd not get cwk\n");

	/* Wequest ioawea */
	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dev->i2s_wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
				&bcm2835_wegmap_config);
	if (IS_EWW(dev->i2s_wegmap))
		wetuwn PTW_EWW(dev->i2s_wegmap);

	/* Set the DMA addwess - we have to pawse DT ouwsewves */
	addw = of_get_addwess(pdev->dev.of_node, 0, NUWW, NUWW);
	if (!addw) {
		dev_eww(&pdev->dev, "couwd not get DMA-wegistew addwess\n");
		wetuwn -EINVAW;
	}
	dma_base = be32_to_cpup(addw);

	dev->dma_data[SNDWV_PCM_STWEAM_PWAYBACK].addw =
		dma_base + BCM2835_I2S_FIFO_A_WEG;

	dev->dma_data[SNDWV_PCM_STWEAM_CAPTUWE].addw =
		dma_base + BCM2835_I2S_FIFO_A_WEG;

	/* Set the bus width */
	dev->dma_data[SNDWV_PCM_STWEAM_PWAYBACK].addw_width =
		DMA_SWAVE_BUSWIDTH_4_BYTES;
	dev->dma_data[SNDWV_PCM_STWEAM_CAPTUWE].addw_width =
		DMA_SWAVE_BUSWIDTH_4_BYTES;

	/* Set buwst */
	dev->dma_data[SNDWV_PCM_STWEAM_PWAYBACK].maxbuwst = 2;
	dev->dma_data[SNDWV_PCM_STWEAM_CAPTUWE].maxbuwst = 2;

	/*
	 * Set the PACK fwag to enabwe S16_WE suppowt (2 S16_WE vawues
	 * packed into 32-bit twansfews).
	 */
	dev->dma_data[SNDWV_PCM_STWEAM_PWAYBACK].fwags =
		SND_DMAENGINE_PCM_DAI_FWAG_PACK;
	dev->dma_data[SNDWV_PCM_STWEAM_CAPTUWE].fwags =
		SND_DMAENGINE_PCM_DAI_FWAG_PACK;

	/* Stowe the pdev */
	dev->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, dev);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
			&bcm2835_i2s_component, &bcm2835_i2s_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew DAI: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew PCM: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id bcm2835_i2s_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-i2s", },
	{},
};

MODUWE_DEVICE_TABWE(of, bcm2835_i2s_of_match);

static stwuct pwatfowm_dwivew bcm2835_i2s_dwivew = {
	.pwobe		= bcm2835_i2s_pwobe,
	.dwivew		= {
		.name	= "bcm2835-i2s",
		.of_match_tabwe = bcm2835_i2s_of_match,
	},
};

moduwe_pwatfowm_dwivew(bcm2835_i2s_dwivew);

MODUWE_AWIAS("pwatfowm:bcm2835-i2s");
MODUWE_DESCWIPTION("BCM2835 I2S intewface");
MODUWE_AUTHOW("Fwowian Meiew <fwowian.meiew@koawo.de>");
MODUWE_WICENSE("GPW v2");
