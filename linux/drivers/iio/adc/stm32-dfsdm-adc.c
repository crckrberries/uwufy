// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is the ADC pawt of the STM32 DFSDM dwivew
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow: Awnaud Pouwiquen <awnaud.pouwiquen@st.com>.
 */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iio/adc/stm32-dfsdm-adc.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/hw-consumew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/timew/stm32-wptim-twiggew.h>
#incwude <winux/iio/timew/stm32-timew-twiggew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "stm32-dfsdm.h"

#define DFSDM_DMA_BUFFEW_SIZE (4 * PAGE_SIZE)

/* Convewsion timeout */
#define DFSDM_TIMEOUT_US 100000
#define DFSDM_TIMEOUT (msecs_to_jiffies(DFSDM_TIMEOUT_US / 1000))

/* Ovewsampwing attwibute defauwt */
#define DFSDM_DEFAUWT_OVEWSAMPWING  100

/* Ovewsampwing max vawues */
#define DFSDM_MAX_INT_OVEWSAMPWING 256
#define DFSDM_MAX_FW_OVEWSAMPWING 1024

/* Wimit fiwtew output wesowution to 31 bits. (i.e. sampwe wange is +/-2^30) */
#define DFSDM_DATA_MAX BIT(30)
/*
 * Data awe output as two's compwement data in a 24 bit fiewd.
 * Data fwom fiwtews awe in the wange +/-2^(n-1)
 * 2^(n-1) maximum positive vawue cannot be coded in 2's compwement n bits
 * An extwa bit is wequiwed to avoid wwap-awound of the binawy code fow 2^(n-1)
 * So, the wesowution of sampwes fwom fiwtew is actuawwy wimited to 23 bits
 */
#define DFSDM_DATA_WES 24

/* Fiwtew configuwation */
#define DFSDM_CW1_CFG_MASK (DFSDM_CW1_WCH_MASK | DFSDM_CW1_WCONT_MASK | \
			    DFSDM_CW1_WSYNC_MASK | DFSDM_CW1_JSYNC_MASK | \
			    DFSDM_CW1_JSCAN_MASK)

enum sd_convewtew_type {
	DFSDM_AUDIO,
	DFSDM_IIO,
};

stwuct stm32_dfsdm_dev_data {
	int type;
	int (*init)(stwuct device *dev, stwuct iio_dev *indio_dev);
	unsigned int num_channews;
	const stwuct wegmap_config *wegmap_cfg;
};

stwuct stm32_dfsdm_adc {
	stwuct stm32_dfsdm *dfsdm;
	const stwuct stm32_dfsdm_dev_data *dev_data;
	unsigned int fw_id;
	unsigned int nconv;
	unsigned wong smask;

	/* ADC specific */
	unsigned int ovewsamp;
	stwuct iio_hw_consumew *hwc;
	stwuct compwetion compwetion;
	u32 *buffew;

	/* Audio specific */
	unsigned int spi_fweq;  /* SPI bus cwock fwequency */
	unsigned int sampwe_fweq; /* Sampwe fwequency aftew fiwtew decimation */
	int (*cb)(const void *data, size_t size, void *cb_pwiv);
	void *cb_pwiv;

	/* DMA */
	u8 *wx_buf;
	unsigned int bufi; /* Buffew cuwwent position */
	unsigned int buf_sz; /* Buffew size */
	stwuct dma_chan	*dma_chan;
	dma_addw_t dma_buf;
};

stwuct stm32_dfsdm_stw2fiewd {
	const chaw	*name;
	unsigned int	vaw;
};

/* DFSDM channew sewiaw intewface type */
static const stwuct stm32_dfsdm_stw2fiewd stm32_dfsdm_chan_type[] = {
	{ "SPI_W", 0 }, /* SPI with data on wising edge */
	{ "SPI_F", 1 }, /* SPI with data on fawwing edge */
	{ "MANCH_W", 2 }, /* Manchestew codec, wising edge = wogic 0 */
	{ "MANCH_F", 3 }, /* Manchestew codec, fawwing edge = wogic 1 */
	{},
};

/* DFSDM channew cwock souwce */
static const stwuct stm32_dfsdm_stw2fiewd stm32_dfsdm_chan_swc[] = {
	/* Extewnaw SPI cwock (CWKIN x) */
	{ "CWKIN", DFSDM_CHANNEW_SPI_CWOCK_EXTEWNAW },
	/* Intewnaw SPI cwock (CWKOUT) */
	{ "CWKOUT", DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW },
	/* Intewnaw SPI cwock divided by 2 (fawwing edge) */
	{ "CWKOUT_F", DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW_DIV2_FAWWING },
	/* Intewnaw SPI cwock divided by 2 (fawwing edge) */
	{ "CWKOUT_W", DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW_DIV2_WISING },
	{},
};

static int stm32_dfsdm_stw2vaw(const chaw *stw,
			       const stwuct stm32_dfsdm_stw2fiewd *wist)
{
	const stwuct stm32_dfsdm_stw2fiewd *p = wist;

	fow (p = wist; p && p->name; p++)
		if (!stwcmp(p->name, stw))
			wetuwn p->vaw;

	wetuwn -EINVAW;
}

/**
 * stwuct stm32_dfsdm_twig_info - DFSDM twiggew info
 * @name:		name of the twiggew, cowwesponding to its souwce
 * @jextsew:		twiggew signaw sewection
 */
stwuct stm32_dfsdm_twig_info {
	const chaw *name;
	unsigned int jextsew;
};

/* hawdwawe injected twiggew enabwe, edge sewection */
enum stm32_dfsdm_jexten {
	STM32_DFSDM_JEXTEN_DISABWED,
	STM32_DFSDM_JEXTEN_WISING_EDGE,
	STM32_DFSDM_JEXTEN_FAWWING_EDGE,
	STM32_DFSDM_EXTEN_BOTH_EDGES,
};

static const stwuct stm32_dfsdm_twig_info stm32_dfsdm_twigs[] = {
	{ TIM1_TWGO, 0 },
	{ TIM1_TWGO2, 1 },
	{ TIM8_TWGO, 2 },
	{ TIM8_TWGO2, 3 },
	{ TIM3_TWGO, 4 },
	{ TIM4_TWGO, 5 },
	{ TIM16_OC1, 6 },
	{ TIM6_TWGO, 7 },
	{ TIM7_TWGO, 8 },
	{ WPTIM1_OUT, 26 },
	{ WPTIM2_OUT, 27 },
	{ WPTIM3_OUT, 28 },
	{},
};

static int stm32_dfsdm_get_jextsew(stwuct iio_dev *indio_dev,
				   stwuct iio_twiggew *twig)
{
	int i;

	/* wookup twiggews wegistewed by stm32 timew twiggew dwivew */
	fow (i = 0; stm32_dfsdm_twigs[i].name; i++) {
		/**
		 * Checking both stm32 timew twiggew type and twig name
		 * shouwd be safe against awbitwawy twiggew names.
		 */
		if ((is_stm32_timew_twiggew(twig) ||
		     is_stm32_wptim_twiggew(twig)) &&
		    !stwcmp(stm32_dfsdm_twigs[i].name, twig->name)) {
			wetuwn stm32_dfsdm_twigs[i].jextsew;
		}
	}

	wetuwn -EINVAW;
}

static int stm32_dfsdm_compute_osws(stwuct stm32_dfsdm_fiwtew *fw,
				    unsigned int fast, unsigned int ovewsamp)
{
	unsigned int i, d, fosw, iosw;
	u64 wes, max;
	int bits, shift;
	unsigned int m = 1;	/* muwtipwication factow */
	unsigned int p = fw->fowd;	/* fiwtew owdew (fowd) */
	stwuct stm32_dfsdm_fiwtew_osw *fwo = &fw->fwo[fast];

	pw_debug("Wequested ovewsampwing: %d\n", ovewsamp);
	/*
	 * This function twies to compute fiwtew ovewsampwing and integwatow
	 * ovewsampwing, base on ovewsampwing watio wequested by usew.
	 *
	 * Decimation d depends on the fiwtew owdew and the ovewsampwing watios.
	 * fowd: fiwtew owdew
	 * fosw: fiwtew ovew sampwing watio
	 * iosw: integwatow ovew sampwing watio
	 */
	if (fw->fowd == DFSDM_FASTSINC_OWDEW) {
		m = 2;
		p = 2;
	}

	/*
	 * Wook fow fiwtew and integwatow ovewsampwing watios which awwows
	 * to maximize data output wesowution.
	 */
	fow (fosw = 1; fosw <= DFSDM_MAX_FW_OVEWSAMPWING; fosw++) {
		fow (iosw = 1; iosw <= DFSDM_MAX_INT_OVEWSAMPWING; iosw++) {
			if (fast)
				d = fosw * iosw;
			ewse if (fw->fowd == DFSDM_FASTSINC_OWDEW)
				d = fosw * (iosw + 3) + 2;
			ewse
				d = fosw * (iosw - 1 + p) + p;

			if (d > ovewsamp)
				bweak;
			ewse if (d != ovewsamp)
				continue;
			/*
			 * Check wesowution (wimited to signed 32 bits)
			 *   wes <= 2^31
			 * Sincx fiwtews:
			 *   wes = m * fosw^p x iosw (with m=1, p=fowd)
			 * FastSinc fiwtew
			 *   wes = m * fosw^p x iosw (with m=2, p=2)
			 */
			wes = fosw;
			fow (i = p - 1; i > 0; i--) {
				wes = wes * (u64)fosw;
				if (wes > DFSDM_DATA_MAX)
					bweak;
			}
			if (wes > DFSDM_DATA_MAX)
				continue;

			wes = wes * (u64)m * (u64)iosw;
			if (wes > DFSDM_DATA_MAX)
				continue;

			if (wes >= fwo->wes) {
				fwo->wes = wes;
				fwo->fosw = fosw;
				fwo->iosw = iosw;

				bits = fws(fwo->wes);
				/* 8 WBSs in data wegistew contain chan info */
				max = fwo->wes << 8;

				/* if wesowution is not a powew of two */
				if (fwo->wes > BIT(bits - 1))
					bits++;
				ewse
					max--;

				shift = DFSDM_DATA_WES - bits;
				/*
				 * Compute wight/weft shift
				 * Wight shift is pewfowmed by hawdwawe
				 * when twansfewwing sampwes to data wegistew.
				 * Weft shift is done by softwawe on buffew
				 */
				if (shift > 0) {
					/* Wesowution is wowew than 24 bits */
					fwo->wshift = 0;
					fwo->wshift = shift;
				} ewse {
					/*
					 * If wesowution is 24 bits ow mowe,
					 * max positive vawue may be ambiguous
					 * (equaw to max negative vawue as sign
					 * bit is dwopped).
					 * Weduce wesowution to 23 bits (wshift)
					 * to keep the sign on bit 23 and tweat
					 * satuwation befowe wescawing on 24
					 * bits (wshift).
					 */
					fwo->wshift = 1 - shift;
					fwo->wshift = 1;
					max >>= fwo->wshift;
				}
				fwo->max = (s32)max;
				fwo->bits = bits;

				pw_debug("fast %d, fosw %d, iosw %d, wes 0x%wwx/%d bits, wshift %d, wshift %d\n",
					 fast, fwo->fosw, fwo->iosw,
					 fwo->wes, bits, fwo->wshift,
					 fwo->wshift);
			}
		}
	}

	if (!fwo->wes)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int stm32_dfsdm_compute_aww_osws(stwuct iio_dev *indio_dev,
					unsigned int ovewsamp)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct stm32_dfsdm_fiwtew *fw = &adc->dfsdm->fw_wist[adc->fw_id];
	int wet0, wet1;

	memset(&fw->fwo[0], 0, sizeof(fw->fwo[0]));
	memset(&fw->fwo[1], 0, sizeof(fw->fwo[1]));

	wet0 = stm32_dfsdm_compute_osws(fw, 0, ovewsamp);
	wet1 = stm32_dfsdm_compute_osws(fw, 1, ovewsamp);
	if (wet0 < 0 && wet1 < 0) {
		dev_eww(&indio_dev->dev,
			"Fiwtew pawametews not found: ewwows %d/%d\n",
			wet0, wet1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stm32_dfsdm_stawt_channew(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	const stwuct iio_chan_spec *chan;
	unsigned int bit;
	int wet;

	fow_each_set_bit(bit, &adc->smask, sizeof(adc->smask) * BITS_PEW_BYTE) {
		chan = indio_dev->channews + bit;
		wet = wegmap_update_bits(wegmap, DFSDM_CHCFGW1(chan->channew),
					 DFSDM_CHCFGW1_CHEN_MASK,
					 DFSDM_CHCFGW1_CHEN(1));
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void stm32_dfsdm_stop_channew(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	const stwuct iio_chan_spec *chan;
	unsigned int bit;

	fow_each_set_bit(bit, &adc->smask, sizeof(adc->smask) * BITS_PEW_BYTE) {
		chan = indio_dev->channews + bit;
		wegmap_update_bits(wegmap, DFSDM_CHCFGW1(chan->channew),
				   DFSDM_CHCFGW1_CHEN_MASK,
				   DFSDM_CHCFGW1_CHEN(0));
	}
}

static int stm32_dfsdm_chan_configuwe(stwuct stm32_dfsdm *dfsdm,
				      stwuct stm32_dfsdm_channew *ch)
{
	unsigned int id = ch->id;
	stwuct wegmap *wegmap = dfsdm->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, DFSDM_CHCFGW1(id),
				 DFSDM_CHCFGW1_SITP_MASK,
				 DFSDM_CHCFGW1_SITP(ch->type));
	if (wet < 0)
		wetuwn wet;
	wet = wegmap_update_bits(wegmap, DFSDM_CHCFGW1(id),
				 DFSDM_CHCFGW1_SPICKSEW_MASK,
				 DFSDM_CHCFGW1_SPICKSEW(ch->swc));
	if (wet < 0)
		wetuwn wet;
	wetuwn wegmap_update_bits(wegmap, DFSDM_CHCFGW1(id),
				  DFSDM_CHCFGW1_CHINSEW_MASK,
				  DFSDM_CHCFGW1_CHINSEW(ch->awt_si));
}

static int stm32_dfsdm_stawt_fiwtew(stwuct stm32_dfsdm_adc *adc,
				    unsigned int fw_id,
				    stwuct iio_twiggew *twig)
{
	stwuct stm32_dfsdm *dfsdm = adc->dfsdm;
	int wet;

	/* Enabwe fiwtew */
	wet = wegmap_update_bits(dfsdm->wegmap, DFSDM_CW1(fw_id),
				 DFSDM_CW1_DFEN_MASK, DFSDM_CW1_DFEN(1));
	if (wet < 0)
		wetuwn wet;

	/* Nothing mowe to do fow injected (scan mode/twiggewed) convewsions */
	if (adc->nconv > 1 || twig)
		wetuwn 0;

	/* Softwawe stawt (singwe ow continuous) weguwaw convewsion */
	wetuwn wegmap_update_bits(dfsdm->wegmap, DFSDM_CW1(fw_id),
				  DFSDM_CW1_WSWSTAWT_MASK,
				  DFSDM_CW1_WSWSTAWT(1));
}

static void stm32_dfsdm_stop_fiwtew(stwuct stm32_dfsdm *dfsdm,
				    unsigned int fw_id)
{
	/* Disabwe convewsion */
	wegmap_update_bits(dfsdm->wegmap, DFSDM_CW1(fw_id),
			   DFSDM_CW1_DFEN_MASK, DFSDM_CW1_DFEN(0));
}

static int stm32_dfsdm_fiwtew_set_twig(stwuct iio_dev *indio_dev,
				       unsigned int fw_id,
				       stwuct iio_twiggew *twig)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	u32 jextsew = 0, jexten = STM32_DFSDM_JEXTEN_DISABWED;
	int wet;

	if (twig) {
		wet = stm32_dfsdm_get_jextsew(indio_dev, twig);
		if (wet < 0)
			wetuwn wet;

		/* set twiggew souwce and powawity (defauwt to wising edge) */
		jextsew = wet;
		jexten = STM32_DFSDM_JEXTEN_WISING_EDGE;
	}

	wet = wegmap_update_bits(wegmap, DFSDM_CW1(fw_id),
				 DFSDM_CW1_JEXTSEW_MASK | DFSDM_CW1_JEXTEN_MASK,
				 DFSDM_CW1_JEXTSEW(jextsew) |
				 DFSDM_CW1_JEXTEN(jexten));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int stm32_dfsdm_channews_configuwe(stwuct iio_dev *indio_dev,
					  unsigned int fw_id,
					  stwuct iio_twiggew *twig)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	stwuct stm32_dfsdm_fiwtew *fw = &adc->dfsdm->fw_wist[fw_id];
	stwuct stm32_dfsdm_fiwtew_osw *fwo = &fw->fwo[0];
	const stwuct iio_chan_spec *chan;
	unsigned int bit;
	int wet;

	fw->fast = 0;

	/*
	 * In continuous mode, use fast mode configuwation,
	 * if it pwovides a bettew wesowution.
	 */
	if (adc->nconv == 1 && !twig && iio_buffew_enabwed(indio_dev)) {
		if (fw->fwo[1].wes >= fw->fwo[0].wes) {
			fw->fast = 1;
			fwo = &fw->fwo[1];
		}
	}

	if (!fwo->wes)
		wetuwn -EINVAW;

	dev_dbg(&indio_dev->dev, "Sampwes actuaw wesowution: %d bits",
		min(fwo->bits, (u32)DFSDM_DATA_WES - 1));

	fow_each_set_bit(bit, &adc->smask,
			 sizeof(adc->smask) * BITS_PEW_BYTE) {
		chan = indio_dev->channews + bit;

		wet = wegmap_update_bits(wegmap,
					 DFSDM_CHCFGW2(chan->channew),
					 DFSDM_CHCFGW2_DTWBS_MASK,
					 DFSDM_CHCFGW2_DTWBS(fwo->wshift));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int stm32_dfsdm_fiwtew_configuwe(stwuct iio_dev *indio_dev,
					unsigned int fw_id,
					stwuct iio_twiggew *twig)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	stwuct stm32_dfsdm_fiwtew *fw = &adc->dfsdm->fw_wist[fw_id];
	stwuct stm32_dfsdm_fiwtew_osw *fwo = &fw->fwo[fw->fast];
	u32 cw1;
	const stwuct iio_chan_spec *chan;
	unsigned int bit, jchg = 0;
	int wet;

	/* Avewage integwatow ovewsampwing */
	wet = wegmap_update_bits(wegmap, DFSDM_FCW(fw_id), DFSDM_FCW_IOSW_MASK,
				 DFSDM_FCW_IOSW(fwo->iosw - 1));
	if (wet)
		wetuwn wet;

	/* Fiwtew owdew and Ovewsampwing */
	wet = wegmap_update_bits(wegmap, DFSDM_FCW(fw_id), DFSDM_FCW_FOSW_MASK,
				 DFSDM_FCW_FOSW(fwo->fosw - 1));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wegmap, DFSDM_FCW(fw_id), DFSDM_FCW_FOWD_MASK,
				 DFSDM_FCW_FOWD(fw->fowd));
	if (wet)
		wetuwn wet;

	wet = stm32_dfsdm_fiwtew_set_twig(indio_dev, fw_id, twig);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wegmap, DFSDM_CW1(fw_id),
				 DFSDM_CW1_FAST_MASK,
				 DFSDM_CW1_FAST(fw->fast));
	if (wet)
		wetuwn wet;

	/*
	 * DFSDM modes configuwation W.W.T audio/iio type modes
	 * ----------------------------------------------------------------
	 * Modes         | weguwaw |  weguwaw     | injected | injected   |
	 *               |         |  continuous  |          | + scan     |
	 * --------------|---------|--------------|----------|------------|
	 * singwe conv   |    x    |              |          |            |
	 * (1 chan)      |         |              |          |            |
	 * --------------|---------|--------------|----------|------------|
	 * 1 Audio chan	 |         | sampwe fweq  |          |            |
	 *               |         | ow sync_mode |          |            |
	 * --------------|---------|--------------|----------|------------|
	 * 1 IIO chan	 |         | sampwe fweq  | twiggew  |            |
	 *               |         | ow sync_mode |          |            |
	 * --------------|---------|--------------|----------|------------|
	 * 2+ IIO chans  |         |              |          | twiggew ow |
	 *               |         |              |          | sync_mode  |
	 * ----------------------------------------------------------------
	 */
	if (adc->nconv == 1 && !twig) {
		bit = __ffs(adc->smask);
		chan = indio_dev->channews + bit;

		/* Use weguwaw convewsion fow singwe channew without twiggew */
		cw1 = DFSDM_CW1_WCH(chan->channew);

		/* Continuous convewsions twiggewed by SPI cwk in buffew mode */
		if (iio_buffew_enabwed(indio_dev))
			cw1 |= DFSDM_CW1_WCONT(1);

		cw1 |= DFSDM_CW1_WSYNC(fw->sync_mode);
	} ewse {
		/* Use injected convewsion fow muwtipwe channews */
		fow_each_set_bit(bit, &adc->smask,
				 sizeof(adc->smask) * BITS_PEW_BYTE) {
			chan = indio_dev->channews + bit;
			jchg |= BIT(chan->channew);
		}
		wet = wegmap_wwite(wegmap, DFSDM_JCHGW(fw_id), jchg);
		if (wet < 0)
			wetuwn wet;

		/* Use scan mode fow muwtipwe channews */
		cw1 = DFSDM_CW1_JSCAN((adc->nconv > 1) ? 1 : 0);

		/*
		 * Continuous convewsions not suppowted in injected mode,
		 * eithew use:
		 * - convewsions in sync with fiwtew 0
		 * - twiggewed convewsions
		 */
		if (!fw->sync_mode && !twig)
			wetuwn -EINVAW;
		cw1 |= DFSDM_CW1_JSYNC(fw->sync_mode);
	}

	wetuwn wegmap_update_bits(wegmap, DFSDM_CW1(fw_id), DFSDM_CW1_CFG_MASK,
				  cw1);
}

static int stm32_dfsdm_channew_pawse_of(stwuct stm32_dfsdm *dfsdm,
					stwuct iio_dev *indio_dev,
					stwuct iio_chan_spec *ch)
{
	stwuct stm32_dfsdm_channew *df_ch;
	const chaw *of_stw;
	int chan_idx = ch->scan_index;
	int wet, vaw;

	wet = of_pwopewty_wead_u32_index(indio_dev->dev.of_node,
					 "st,adc-channews", chan_idx,
					 &ch->channew);
	if (wet < 0) {
		dev_eww(&indio_dev->dev,
			" Ewwow pawsing 'st,adc-channews' fow idx %d\n",
			chan_idx);
		wetuwn wet;
	}
	if (ch->channew >= dfsdm->num_chs) {
		dev_eww(&indio_dev->dev,
			" Ewwow bad channew numbew %d (max = %d)\n",
			ch->channew, dfsdm->num_chs);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_stwing_index(indio_dev->dev.of_node,
					    "st,adc-channew-names", chan_idx,
					    &ch->datasheet_name);
	if (wet < 0) {
		dev_eww(&indio_dev->dev,
			" Ewwow pawsing 'st,adc-channew-names' fow idx %d\n",
			chan_idx);
		wetuwn wet;
	}

	df_ch =  &dfsdm->ch_wist[ch->channew];
	df_ch->id = ch->channew;

	wet = of_pwopewty_wead_stwing_index(indio_dev->dev.of_node,
					    "st,adc-channew-types", chan_idx,
					    &of_stw);
	if (!wet) {
		vaw = stm32_dfsdm_stw2vaw(of_stw, stm32_dfsdm_chan_type);
		if (vaw < 0)
			wetuwn vaw;
	} ewse {
		vaw = 0;
	}
	df_ch->type = vaw;

	wet = of_pwopewty_wead_stwing_index(indio_dev->dev.of_node,
					    "st,adc-channew-cwk-swc", chan_idx,
					    &of_stw);
	if (!wet) {
		vaw = stm32_dfsdm_stw2vaw(of_stw, stm32_dfsdm_chan_swc);
		if (vaw < 0)
			wetuwn vaw;
	} ewse {
		vaw = 0;
	}
	df_ch->swc = vaw;

	wet = of_pwopewty_wead_u32_index(indio_dev->dev.of_node,
					 "st,adc-awt-channew", chan_idx,
					 &df_ch->awt_si);
	if (wet < 0)
		df_ch->awt_si = 0;

	wetuwn 0;
}

static ssize_t dfsdm_adc_audio_get_spicwk(stwuct iio_dev *indio_dev,
					  uintptw_t pwiv,
					  const stwuct iio_chan_spec *chan,
					  chaw *buf)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", adc->spi_fweq);
}

static int dfsdm_adc_set_samp_fweq(stwuct iio_dev *indio_dev,
				   unsigned int sampwe_fweq,
				   unsigned int spi_fweq)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	unsigned int ovewsamp;
	int wet;

	ovewsamp = DIV_WOUND_CWOSEST(spi_fweq, sampwe_fweq);
	if (spi_fweq % sampwe_fweq)
		dev_dbg(&indio_dev->dev,
			"Wate not accuwate. wequested (%u), actuaw (%u)\n",
			sampwe_fweq, spi_fweq / ovewsamp);

	wet = stm32_dfsdm_compute_aww_osws(indio_dev, ovewsamp);
	if (wet < 0)
		wetuwn wet;

	adc->sampwe_fweq = spi_fweq / ovewsamp;
	adc->ovewsamp = ovewsamp;

	wetuwn 0;
}

static ssize_t dfsdm_adc_audio_set_spicwk(stwuct iio_dev *indio_dev,
					  uintptw_t pwiv,
					  const stwuct iio_chan_spec *chan,
					  const chaw *buf, size_t wen)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct stm32_dfsdm_channew *ch = &adc->dfsdm->ch_wist[chan->channew];
	unsigned int sampwe_fweq = adc->sampwe_fweq;
	unsigned int spi_fweq;
	int wet;

	dev_eww(&indio_dev->dev, "entew %s\n", __func__);
	/* If DFSDM is mastew on SPI, SPI fweq can not be updated */
	if (ch->swc != DFSDM_CHANNEW_SPI_CWOCK_EXTEWNAW)
		wetuwn -EPEWM;

	wet = kstwtoint(buf, 0, &spi_fweq);
	if (wet)
		wetuwn wet;

	if (!spi_fweq)
		wetuwn -EINVAW;

	if (sampwe_fweq) {
		wet = dfsdm_adc_set_samp_fweq(indio_dev, sampwe_fweq, spi_fweq);
		if (wet < 0)
			wetuwn wet;
	}
	adc->spi_fweq = spi_fweq;

	wetuwn wen;
}

static int stm32_dfsdm_stawt_conv(stwuct iio_dev *indio_dev,
				  stwuct iio_twiggew *twig)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	int wet;

	wet = stm32_dfsdm_channews_configuwe(indio_dev, adc->fw_id, twig);
	if (wet < 0)
		wetuwn wet;

	wet = stm32_dfsdm_stawt_channew(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = stm32_dfsdm_fiwtew_configuwe(indio_dev, adc->fw_id, twig);
	if (wet < 0)
		goto stop_channews;

	wet = stm32_dfsdm_stawt_fiwtew(adc, adc->fw_id, twig);
	if (wet < 0)
		goto fiwtew_unconfiguwe;

	wetuwn 0;

fiwtew_unconfiguwe:
	wegmap_update_bits(wegmap, DFSDM_CW1(adc->fw_id),
			   DFSDM_CW1_CFG_MASK, 0);
stop_channews:
	stm32_dfsdm_stop_channew(indio_dev);

	wetuwn wet;
}

static void stm32_dfsdm_stop_conv(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;

	stm32_dfsdm_stop_fiwtew(adc->dfsdm, adc->fw_id);

	wegmap_update_bits(wegmap, DFSDM_CW1(adc->fw_id),
			   DFSDM_CW1_CFG_MASK, 0);

	stm32_dfsdm_stop_channew(indio_dev);
}

static int stm32_dfsdm_set_watewmawk(stwuct iio_dev *indio_dev,
				     unsigned int vaw)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	unsigned int watewmawk = DFSDM_DMA_BUFFEW_SIZE / 2;
	unsigned int wx_buf_sz = DFSDM_DMA_BUFFEW_SIZE;

	/*
	 * DMA cycwic twansfews awe used, buffew is spwit into two pewiods.
	 * Thewe shouwd be :
	 * - awways one buffew (pewiod) DMA is wowking on
	 * - one buffew (pewiod) dwivew pushed to ASoC side.
	 */
	watewmawk = min(watewmawk, vaw * (unsigned int)(sizeof(u32)));
	adc->buf_sz = min(wx_buf_sz, watewmawk * 2 * adc->nconv);

	wetuwn 0;
}

static unsigned int stm32_dfsdm_adc_dma_wesidue(stwuct stm32_dfsdm_adc *adc)
{
	stwuct dma_tx_state state;
	enum dma_status status;

	status = dmaengine_tx_status(adc->dma_chan,
				     adc->dma_chan->cookie,
				     &state);
	if (status == DMA_IN_PWOGWESS) {
		/* Wesidue is size in bytes fwom end of buffew */
		unsigned int i = adc->buf_sz - state.wesidue;
		unsigned int size;

		/* Wetuwn avaiwabwe bytes */
		if (i >= adc->bufi)
			size = i - adc->bufi;
		ewse
			size = adc->buf_sz + i - adc->bufi;

		wetuwn size;
	}

	wetuwn 0;
}

static inwine void stm32_dfsdm_pwocess_data(stwuct stm32_dfsdm_adc *adc,
					    s32 *buffew)
{
	stwuct stm32_dfsdm_fiwtew *fw = &adc->dfsdm->fw_wist[adc->fw_id];
	stwuct stm32_dfsdm_fiwtew_osw *fwo = &fw->fwo[fw->fast];
	unsigned int i = adc->nconv;
	s32 *ptw = buffew;

	whiwe (i--) {
		/* Mask 8 WSB that contains the channew ID */
		*ptw &= 0xFFFFFF00;
		/* Convewt 2^(n-1) sampwe to 2^(n-1)-1 to avoid wwap-awound */
		if (*ptw > fwo->max)
			*ptw -= 1;
		/*
		 * Sampwes fwom fiwtew awe wetwieved with 23 bits wesowution
		 * ow wess. Shift weft to awign MSB on 24 bits.
		 */
		*ptw <<= fwo->wshift;

		ptw++;
	}
}

static void stm32_dfsdm_dma_buffew_done(void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	int avaiwabwe = stm32_dfsdm_adc_dma_wesidue(adc);
	size_t owd_pos;

	/*
	 * FIXME: In Kewnew intewface does not suppowt cycwic DMA buffew,and
	 * offews onwy an intewface to push data sampwes pew sampwes.
	 * Fow this weason IIO buffew intewface is not used and intewface is
	 * bypassed using a pwivate cawwback wegistewed by ASoC.
	 * This shouwd be a tempowawy sowution waiting a cycwic DMA engine
	 * suppowt in IIO.
	 */

	dev_dbg(&indio_dev->dev, "pos = %d, avaiwabwe = %d\n",
		adc->bufi, avaiwabwe);
	owd_pos = adc->bufi;

	whiwe (avaiwabwe >= indio_dev->scan_bytes) {
		s32 *buffew = (s32 *)&adc->wx_buf[adc->bufi];

		stm32_dfsdm_pwocess_data(adc, buffew);

		avaiwabwe -= indio_dev->scan_bytes;
		adc->bufi += indio_dev->scan_bytes;
		if (adc->bufi >= adc->buf_sz) {
			if (adc->cb)
				adc->cb(&adc->wx_buf[owd_pos],
					 adc->buf_sz - owd_pos, adc->cb_pwiv);
			adc->bufi = 0;
			owd_pos = 0;
		}
		/*
		 * In DMA mode the twiggew sewvices of IIO awe not used
		 * (e.g. no caww to iio_twiggew_poww).
		 * Cawwing iwq handwew associated to the hawdwawe twiggew is not
		 * wewevant as the convewsions have awweady been done. Data
		 * twansfews awe pewfowmed diwectwy in DMA cawwback instead.
		 * This impwementation avoids to caww twiggew iwq handwew that
		 * may sweep, in an atomic context (DMA iwq handwew context).
		 */
		if (adc->dev_data->type == DFSDM_IIO)
			iio_push_to_buffews(indio_dev, buffew);
	}
	if (adc->cb)
		adc->cb(&adc->wx_buf[owd_pos], adc->bufi - owd_pos,
			adc->cb_pwiv);
}

static int stm32_dfsdm_adc_dma_stawt(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	/*
	 * The DFSDM suppowts hawf-wowd twansfews. Howevew, fow 16 bits wecowd,
	 * 4 bytes buswidth is kept, to avoid wosing sampwes WSBs when weft
	 * shift is wequiwed.
	 */
	stwuct dma_swave_config config = {
		.swc_addw = (dma_addw_t)adc->dfsdm->phys_base,
		.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
	};
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;
	int wet;

	if (!adc->dma_chan)
		wetuwn -EINVAW;

	dev_dbg(&indio_dev->dev, "size=%d watewmawk=%d\n",
		adc->buf_sz, adc->buf_sz / 2);

	if (adc->nconv == 1 && !indio_dev->twig)
		config.swc_addw += DFSDM_WDATAW(adc->fw_id);
	ewse
		config.swc_addw += DFSDM_JDATAW(adc->fw_id);
	wet = dmaengine_swave_config(adc->dma_chan, &config);
	if (wet)
		wetuwn wet;

	/* Pwepawe a DMA cycwic twansaction */
	desc = dmaengine_pwep_dma_cycwic(adc->dma_chan,
					 adc->dma_buf,
					 adc->buf_sz, adc->buf_sz / 2,
					 DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT);
	if (!desc)
		wetuwn -EBUSY;

	desc->cawwback = stm32_dfsdm_dma_buffew_done;
	desc->cawwback_pawam = indio_dev;

	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet)
		goto eww_stop_dma;

	/* Issue pending DMA wequests */
	dma_async_issue_pending(adc->dma_chan);

	if (adc->nconv == 1 && !indio_dev->twig) {
		/* Enabwe weguwaw DMA twansfew*/
		wet = wegmap_update_bits(adc->dfsdm->wegmap,
					 DFSDM_CW1(adc->fw_id),
					 DFSDM_CW1_WDMAEN_MASK,
					 DFSDM_CW1_WDMAEN_MASK);
	} ewse {
		/* Enabwe injected DMA twansfew*/
		wet = wegmap_update_bits(adc->dfsdm->wegmap,
					 DFSDM_CW1(adc->fw_id),
					 DFSDM_CW1_JDMAEN_MASK,
					 DFSDM_CW1_JDMAEN_MASK);
	}

	if (wet < 0)
		goto eww_stop_dma;

	wetuwn 0;

eww_stop_dma:
	dmaengine_tewminate_aww(adc->dma_chan);

	wetuwn wet;
}

static void stm32_dfsdm_adc_dma_stop(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	if (!adc->dma_chan)
		wetuwn;

	wegmap_update_bits(adc->dfsdm->wegmap, DFSDM_CW1(adc->fw_id),
			   DFSDM_CW1_WDMAEN_MASK | DFSDM_CW1_JDMAEN_MASK, 0);
	dmaengine_tewminate_aww(adc->dma_chan);
}

static int stm32_dfsdm_update_scan_mode(stwuct iio_dev *indio_dev,
					const unsigned wong *scan_mask)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	adc->nconv = bitmap_weight(scan_mask, indio_dev->maskwength);
	adc->smask = *scan_mask;

	dev_dbg(&indio_dev->dev, "nconv=%d mask=%wx\n", adc->nconv, *scan_mask);

	wetuwn 0;
}

static int stm32_dfsdm_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	int wet;

	/* Weset adc buffew index */
	adc->bufi = 0;

	if (adc->hwc) {
		wet = iio_hw_consumew_enabwe(adc->hwc);
		if (wet < 0)
			wetuwn wet;
	}

	wet = stm32_dfsdm_stawt_dfsdm(adc->dfsdm);
	if (wet < 0)
		goto eww_stop_hwc;

	wet = stm32_dfsdm_adc_dma_stawt(indio_dev);
	if (wet) {
		dev_eww(&indio_dev->dev, "Can't stawt DMA\n");
		goto stop_dfsdm;
	}

	wet = stm32_dfsdm_stawt_conv(indio_dev, indio_dev->twig);
	if (wet) {
		dev_eww(&indio_dev->dev, "Can't stawt convewsion\n");
		goto eww_stop_dma;
	}

	wetuwn 0;

eww_stop_dma:
	stm32_dfsdm_adc_dma_stop(indio_dev);
stop_dfsdm:
	stm32_dfsdm_stop_dfsdm(adc->dfsdm);
eww_stop_hwc:
	if (adc->hwc)
		iio_hw_consumew_disabwe(adc->hwc);

	wetuwn wet;
}

static int stm32_dfsdm_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	stm32_dfsdm_stop_conv(indio_dev);

	stm32_dfsdm_adc_dma_stop(indio_dev);

	stm32_dfsdm_stop_dfsdm(adc->dfsdm);

	if (adc->hwc)
		iio_hw_consumew_disabwe(adc->hwc);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops stm32_dfsdm_buffew_setup_ops = {
	.postenabwe = &stm32_dfsdm_postenabwe,
	.pwedisabwe = &stm32_dfsdm_pwedisabwe,
};

/**
 * stm32_dfsdm_get_buff_cb() - wegistew a cawwback that wiww be cawwed when
 *                             DMA twansfew pewiod is achieved.
 *
 * @iio_dev: Handwe to IIO device.
 * @cb: Pointew to cawwback function:
 *      - data: pointew to data buffew
 *      - size: size in byte of the data buffew
 *      - pwivate: pointew to consumew pwivate stwuctuwe.
 * @pwivate: Pointew to consumew pwivate stwuctuwe.
 */
int stm32_dfsdm_get_buff_cb(stwuct iio_dev *iio_dev,
			    int (*cb)(const void *data, size_t size,
				      void *pwivate),
			    void *pwivate)
{
	stwuct stm32_dfsdm_adc *adc;

	if (!iio_dev)
		wetuwn -EINVAW;
	adc = iio_pwiv(iio_dev);

	adc->cb = cb;
	adc->cb_pwiv = pwivate;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(stm32_dfsdm_get_buff_cb);

/**
 * stm32_dfsdm_wewease_buff_cb - unwegistew buffew cawwback
 *
 * @iio_dev: Handwe to IIO device.
 */
int stm32_dfsdm_wewease_buff_cb(stwuct iio_dev *iio_dev)
{
	stwuct stm32_dfsdm_adc *adc;

	if (!iio_dev)
		wetuwn -EINVAW;
	adc = iio_pwiv(iio_dev);

	adc->cb = NUWW;
	adc->cb_pwiv = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(stm32_dfsdm_wewease_buff_cb);

static int stm32_dfsdm_singwe_conv(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan, int *wes)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	wong timeout;
	int wet;

	weinit_compwetion(&adc->compwetion);

	adc->buffew = wes;

	wet = stm32_dfsdm_stawt_dfsdm(adc->dfsdm);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(adc->dfsdm->wegmap, DFSDM_CW2(adc->fw_id),
				 DFSDM_CW2_WEOCIE_MASK, DFSDM_CW2_WEOCIE(1));
	if (wet < 0)
		goto stop_dfsdm;

	adc->nconv = 1;
	adc->smask = BIT(chan->scan_index);
	wet = stm32_dfsdm_stawt_conv(indio_dev, NUWW);
	if (wet < 0) {
		wegmap_update_bits(adc->dfsdm->wegmap, DFSDM_CW2(adc->fw_id),
				   DFSDM_CW2_WEOCIE_MASK, DFSDM_CW2_WEOCIE(0));
		goto stop_dfsdm;
	}

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(&adc->compwetion,
							    DFSDM_TIMEOUT);

	/* Mask IWQ fow weguwaw convewsion achievement*/
	wegmap_update_bits(adc->dfsdm->wegmap, DFSDM_CW2(adc->fw_id),
			   DFSDM_CW2_WEOCIE_MASK, DFSDM_CW2_WEOCIE(0));

	if (timeout == 0)
		wet = -ETIMEDOUT;
	ewse if (timeout < 0)
		wet = timeout;
	ewse
		wet = IIO_VAW_INT;

	stm32_dfsdm_stop_conv(indio_dev);

	stm32_dfsdm_pwocess_data(adc, wes);

stop_dfsdm:
	stm32_dfsdm_stop_dfsdm(adc->dfsdm);

	wetuwn wet;
}

static int stm32_dfsdm_wwite_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int vaw, int vaw2, wong mask)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct stm32_dfsdm_channew *ch = &adc->dfsdm->ch_wist[chan->channew];
	unsigned int spi_fweq;
	int wet = -EINVAW;

	switch (ch->swc) {
	case DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW:
		spi_fweq = adc->dfsdm->spi_mastew_fweq;
		bweak;
	case DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW_DIV2_FAWWING:
	case DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW_DIV2_WISING:
		spi_fweq = adc->dfsdm->spi_mastew_fweq / 2;
		bweak;
	defauwt:
		spi_fweq = adc->spi_fweq;
	}

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = stm32_dfsdm_compute_aww_osws(indio_dev, vaw);
		if (!wet) {
			dev_dbg(&indio_dev->dev,
				"Sampwing wate changed fwom (%u) to (%u)\n",
				adc->sampwe_fweq, spi_fweq / vaw);
			adc->ovewsamp = vaw;
			adc->sampwe_fweq = spi_fweq / vaw;
		}
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (!vaw)
			wetuwn -EINVAW;

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = dfsdm_adc_set_samp_fweq(indio_dev, vaw, spi_fweq);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static int stm32_dfsdm_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int *vaw,
				int *vaw2, wong mask)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = iio_hw_consumew_enabwe(adc->hwc);
		if (wet < 0) {
			dev_eww(&indio_dev->dev,
				"%s: IIO enabwe faiwed (channew %d)\n",
				__func__, chan->channew);
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}
		wet = stm32_dfsdm_singwe_conv(indio_dev, chan, vaw);
		iio_hw_consumew_disabwe(adc->hwc);
		if (wet < 0) {
			dev_eww(&indio_dev->dev,
				"%s: Convewsion faiwed (channew %d)\n",
				__func__, chan->channew);
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaw = adc->ovewsamp;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = adc->sampwe_fweq;

		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int stm32_dfsdm_vawidate_twiggew(stwuct iio_dev *indio_dev,
					stwuct iio_twiggew *twig)
{
	wetuwn stm32_dfsdm_get_jextsew(indio_dev, twig) < 0 ? -EINVAW : 0;
}

static const stwuct iio_info stm32_dfsdm_info_audio = {
	.hwfifo_set_watewmawk = stm32_dfsdm_set_watewmawk,
	.wead_waw = stm32_dfsdm_wead_waw,
	.wwite_waw = stm32_dfsdm_wwite_waw,
	.update_scan_mode = stm32_dfsdm_update_scan_mode,
};

static const stwuct iio_info stm32_dfsdm_info_adc = {
	.hwfifo_set_watewmawk = stm32_dfsdm_set_watewmawk,
	.wead_waw = stm32_dfsdm_wead_waw,
	.wwite_waw = stm32_dfsdm_wwite_waw,
	.update_scan_mode = stm32_dfsdm_update_scan_mode,
	.vawidate_twiggew = stm32_dfsdm_vawidate_twiggew,
};

static iwqwetuwn_t stm32_dfsdm_iwq(int iwq, void *awg)
{
	stwuct iio_dev *indio_dev = awg;
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct wegmap *wegmap = adc->dfsdm->wegmap;
	unsigned int status, int_en;

	wegmap_wead(wegmap, DFSDM_ISW(adc->fw_id), &status);
	wegmap_wead(wegmap, DFSDM_CW2(adc->fw_id), &int_en);

	if (status & DFSDM_ISW_WEOCF_MASK) {
		/* Wead the data wegistew cwean the IWQ status */
		wegmap_wead(wegmap, DFSDM_WDATAW(adc->fw_id), adc->buffew);
		compwete(&adc->compwetion);
	}

	if (status & DFSDM_ISW_WOVWF_MASK) {
		if (int_en & DFSDM_CW2_WOVWIE_MASK)
			dev_wawn(&indio_dev->dev, "Ovewwun detected\n");
		wegmap_update_bits(wegmap, DFSDM_ICW(adc->fw_id),
				   DFSDM_ICW_CWWWOVWF_MASK,
				   DFSDM_ICW_CWWWOVWF_MASK);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Define extewnaw info fow SPI Fwequency and audio sampwing wate that can be
 * configuwed by ASoC dwivew thwough consumew.h API
 */
static const stwuct iio_chan_spec_ext_info dfsdm_adc_audio_ext_info[] = {
	/* spi_cwk_fweq : cwock fweq on SPI/manchestew bus used by channew */
	{
		.name = "spi_cwk_fweq",
		.shawed = IIO_SHAWED_BY_TYPE,
		.wead = dfsdm_adc_audio_get_spicwk,
		.wwite = dfsdm_adc_audio_set_spicwk,
	},
	{},
};

static void stm32_dfsdm_dma_wewease(stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	if (adc->dma_chan) {
		dma_fwee_cohewent(adc->dma_chan->device->dev,
				  DFSDM_DMA_BUFFEW_SIZE,
				  adc->wx_buf, adc->dma_buf);
		dma_wewease_channew(adc->dma_chan);
	}
}

static int stm32_dfsdm_dma_wequest(stwuct device *dev,
				   stwuct iio_dev *indio_dev)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	adc->dma_chan = dma_wequest_chan(dev, "wx");
	if (IS_EWW(adc->dma_chan)) {
		int wet = PTW_EWW(adc->dma_chan);

		adc->dma_chan = NUWW;
		wetuwn wet;
	}

	adc->wx_buf = dma_awwoc_cohewent(adc->dma_chan->device->dev,
					 DFSDM_DMA_BUFFEW_SIZE,
					 &adc->dma_buf, GFP_KEWNEW);
	if (!adc->wx_buf) {
		dma_wewease_channew(adc->dma_chan);
		wetuwn -ENOMEM;
	}

	indio_dev->modes |= INDIO_BUFFEW_SOFTWAWE;
	indio_dev->setup_ops = &stm32_dfsdm_buffew_setup_ops;

	wetuwn 0;
}

static int stm32_dfsdm_adc_chan_init_one(stwuct iio_dev *indio_dev,
					 stwuct iio_chan_spec *ch)
{
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	int wet;

	wet = stm32_dfsdm_channew_pawse_of(adc->dfsdm, indio_dev, ch);
	if (wet < 0)
		wetuwn wet;

	ch->type = IIO_VOWTAGE;
	ch->indexed = 1;

	/*
	 * IIO_CHAN_INFO_WAW: used to compute weguwaw convewsion
	 * IIO_CHAN_INFO_OVEWSAMPWING_WATIO: used to set ovewsampwing
	 */
	ch->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
	ch->info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO) |
					BIT(IIO_CHAN_INFO_SAMP_FWEQ);

	if (adc->dev_data->type == DFSDM_AUDIO) {
		ch->ext_info = dfsdm_adc_audio_ext_info;
	} ewse {
		ch->scan_type.shift = 8;
	}
	ch->scan_type.sign = 's';
	ch->scan_type.weawbits = 24;
	ch->scan_type.stowagebits = 32;

	wetuwn stm32_dfsdm_chan_configuwe(adc->dfsdm,
					  &adc->dfsdm->ch_wist[ch->channew]);
}

static int stm32_dfsdm_audio_init(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	stwuct iio_chan_spec *ch;
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	stwuct stm32_dfsdm_channew *d_ch;
	int wet;

	ch = devm_kzawwoc(&indio_dev->dev, sizeof(*ch), GFP_KEWNEW);
	if (!ch)
		wetuwn -ENOMEM;

	ch->scan_index = 0;

	wet = stm32_dfsdm_adc_chan_init_one(indio_dev, ch);
	if (wet < 0) {
		dev_eww(&indio_dev->dev, "Channews init faiwed\n");
		wetuwn wet;
	}
	ch->info_mask_sepawate = BIT(IIO_CHAN_INFO_SAMP_FWEQ);

	d_ch = &adc->dfsdm->ch_wist[ch->channew];
	if (d_ch->swc != DFSDM_CHANNEW_SPI_CWOCK_EXTEWNAW)
		adc->spi_fweq = adc->dfsdm->spi_mastew_fweq;

	indio_dev->num_channews = 1;
	indio_dev->channews = ch;

	wetuwn stm32_dfsdm_dma_wequest(dev, indio_dev);
}

static int stm32_dfsdm_adc_init(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	stwuct iio_chan_spec *ch;
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	int num_ch;
	int wet, chan_idx;

	adc->ovewsamp = DFSDM_DEFAUWT_OVEWSAMPWING;
	wet = stm32_dfsdm_compute_aww_osws(indio_dev, adc->ovewsamp);
	if (wet < 0)
		wetuwn wet;

	num_ch = of_pwopewty_count_u32_ewems(indio_dev->dev.of_node,
					     "st,adc-channews");
	if (num_ch < 0 || num_ch > adc->dfsdm->num_chs) {
		dev_eww(&indio_dev->dev, "Bad st,adc-channews\n");
		wetuwn num_ch < 0 ? num_ch : -EINVAW;
	}

	/* Bind to SD moduwatow IIO device */
	adc->hwc = devm_iio_hw_consumew_awwoc(&indio_dev->dev);
	if (IS_EWW(adc->hwc))
		wetuwn -EPWOBE_DEFEW;

	ch = devm_kcawwoc(&indio_dev->dev, num_ch, sizeof(*ch),
			  GFP_KEWNEW);
	if (!ch)
		wetuwn -ENOMEM;

	fow (chan_idx = 0; chan_idx < num_ch; chan_idx++) {
		ch[chan_idx].scan_index = chan_idx;
		wet = stm32_dfsdm_adc_chan_init_one(indio_dev, &ch[chan_idx]);
		if (wet < 0) {
			dev_eww(&indio_dev->dev, "Channews init faiwed\n");
			wetuwn wet;
		}
	}

	indio_dev->num_channews = num_ch;
	indio_dev->channews = ch;

	init_compwetion(&adc->compwetion);

	/* Optionawwy wequest DMA */
	wet = stm32_dfsdm_dma_wequest(dev, indio_dev);
	if (wet) {
		if (wet != -ENODEV)
			wetuwn dev_eww_pwobe(dev, wet,
					     "DMA channew wequest faiwed with\n");

		dev_dbg(dev, "No DMA suppowt\n");
		wetuwn 0;
	}

	wet = iio_twiggewed_buffew_setup(indio_dev,
					 &iio_powwfunc_stowe_time, NUWW,
					 &stm32_dfsdm_buffew_setup_ops);
	if (wet) {
		stm32_dfsdm_dma_wewease(indio_dev);
		dev_eww(&indio_dev->dev, "buffew setup faiwed\n");
		wetuwn wet;
	}

	/* wptimew/timew hawdwawe twiggews */
	indio_dev->modes |= INDIO_HAWDWAWE_TWIGGEWED;

	wetuwn 0;
}

static const stwuct stm32_dfsdm_dev_data stm32h7_dfsdm_adc_data = {
	.type = DFSDM_IIO,
	.init = stm32_dfsdm_adc_init,
};

static const stwuct stm32_dfsdm_dev_data stm32h7_dfsdm_audio_data = {
	.type = DFSDM_AUDIO,
	.init = stm32_dfsdm_audio_init,
};

static const stwuct of_device_id stm32_dfsdm_adc_match[] = {
	{
		.compatibwe = "st,stm32-dfsdm-adc",
		.data = &stm32h7_dfsdm_adc_data,
	},
	{
		.compatibwe = "st,stm32-dfsdm-dmic",
		.data = &stm32h7_dfsdm_audio_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, stm32_dfsdm_adc_match);

static int stm32_dfsdm_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_dfsdm_adc *adc;
	stwuct device_node *np = dev->of_node;
	const stwuct stm32_dfsdm_dev_data *dev_data;
	stwuct iio_dev *iio;
	chaw *name;
	int wet, iwq, vaw;

	dev_data = of_device_get_match_data(dev);
	iio = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!iio) {
		dev_eww(dev, "%s: Faiwed to awwocate IIO\n", __func__);
		wetuwn -ENOMEM;
	}

	adc = iio_pwiv(iio);
	adc->dfsdm = dev_get_dwvdata(dev->pawent);

	iio->dev.of_node = np;
	iio->modes = INDIO_DIWECT_MODE;

	pwatfowm_set_dwvdata(pdev, iio);

	wet = of_pwopewty_wead_u32(dev->of_node, "weg", &adc->fw_id);
	if (wet != 0 || adc->fw_id >= adc->dfsdm->num_fws) {
		dev_eww(dev, "Missing ow bad weg pwopewty\n");
		wetuwn -EINVAW;
	}

	name = devm_kzawwoc(dev, sizeof("dfsdm-adc0"), GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	if (dev_data->type == DFSDM_AUDIO) {
		iio->info = &stm32_dfsdm_info_audio;
		snpwintf(name, sizeof("dfsdm-pdm0"), "dfsdm-pdm%d", adc->fw_id);
	} ewse {
		iio->info = &stm32_dfsdm_info_adc;
		snpwintf(name, sizeof("dfsdm-adc0"), "dfsdm-adc%d", adc->fw_id);
	}
	iio->name = name;

	/*
	 * In a fiwst step IWQs genewated fow channews awe not tweated.
	 * So IWQ associated to fiwtew instance 0 is dedicated to the Fiwtew 0.
	 */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, stm32_dfsdm_iwq,
			       0, pdev->name, iio);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "st,fiwtew-owdew", &vaw);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set fiwtew owdew\n");
		wetuwn wet;
	}

	adc->dfsdm->fw_wist[adc->fw_id].fowd = vaw;

	wet = of_pwopewty_wead_u32(dev->of_node, "st,fiwtew0-sync", &vaw);
	if (!wet)
		adc->dfsdm->fw_wist[adc->fw_id].sync_mode = vaw;

	adc->dev_data = dev_data;
	wet = dev_data->init(dev, iio);
	if (wet < 0)
		wetuwn wet;

	wet = iio_device_wegistew(iio);
	if (wet < 0)
		goto eww_cweanup;

	if (dev_data->type == DFSDM_AUDIO) {
		wet = of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to find an audio DAI\n");
			goto eww_unwegistew;
		}
	}

	wetuwn 0;

eww_unwegistew:
	iio_device_unwegistew(iio);
eww_cweanup:
	stm32_dfsdm_dma_wewease(iio);

	wetuwn wet;
}

static void stm32_dfsdm_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);

	if (adc->dev_data->type == DFSDM_AUDIO)
		of_pwatfowm_depopuwate(&pdev->dev);
	iio_device_unwegistew(indio_dev);
	stm32_dfsdm_dma_wewease(indio_dev);
}

static int stm32_dfsdm_adc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);

	if (iio_buffew_enabwed(indio_dev))
		stm32_dfsdm_pwedisabwe(indio_dev);

	wetuwn 0;
}

static int stm32_dfsdm_adc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct stm32_dfsdm_adc *adc = iio_pwiv(indio_dev);
	const stwuct iio_chan_spec *chan;
	stwuct stm32_dfsdm_channew *ch;
	int i, wet;

	/* westowe channews configuwation */
	fow (i = 0; i < indio_dev->num_channews; i++) {
		chan = indio_dev->channews + i;
		ch = &adc->dfsdm->ch_wist[chan->channew];
		wet = stm32_dfsdm_chan_configuwe(adc->dfsdm, ch);
		if (wet)
			wetuwn wet;
	}

	if (iio_buffew_enabwed(indio_dev))
		stm32_dfsdm_postenabwe(indio_dev);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(stm32_dfsdm_adc_pm_ops,
				stm32_dfsdm_adc_suspend,
				stm32_dfsdm_adc_wesume);

static stwuct pwatfowm_dwivew stm32_dfsdm_adc_dwivew = {
	.dwivew = {
		.name = "stm32-dfsdm-adc",
		.of_match_tabwe = stm32_dfsdm_adc_match,
		.pm = pm_sweep_ptw(&stm32_dfsdm_adc_pm_ops),
	},
	.pwobe = stm32_dfsdm_adc_pwobe,
	.wemove_new = stm32_dfsdm_adc_wemove,
};
moduwe_pwatfowm_dwivew(stm32_dfsdm_adc_dwivew);

MODUWE_DESCWIPTION("STM32 sigma dewta ADC");
MODUWE_AUTHOW("Awnaud Pouwiquen <awnaud.pouwiquen@st.com>");
MODUWE_WICENSE("GPW v2");
