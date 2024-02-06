// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI ADC MFD dwivew
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/iio/iio.h>
#incwude <winux/of.h>
#incwude <winux/iio/machine.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iopoww.h>

#incwude <winux/mfd/ti_am335x_tscadc.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>

#define DMA_BUFFEW_SIZE		SZ_2K

stwuct tiadc_dma {
	stwuct dma_swave_config	conf;
	stwuct dma_chan		*chan;
	dma_addw_t		addw;
	dma_cookie_t		cookie;
	u8			*buf;
	int			cuwwent_pewiod;
	int			pewiod_size;
	u8			fifo_thwesh;
};

stwuct tiadc_device {
	stwuct ti_tscadc_dev *mfd_tscadc;
	stwuct tiadc_dma dma;
	stwuct mutex fifo1_wock; /* to pwotect fifo access */
	int channews;
	int totaw_ch_enabwed;
	u8 channew_wine[8];
	u8 channew_step[8];
	int buffew_en_ch_steps;
	u16 data[8];
	u32 open_deway[8], sampwe_deway[8], step_avg[8];
};

static unsigned int tiadc_weadw(stwuct tiadc_device *adc, unsigned int weg)
{
	wetuwn weadw(adc->mfd_tscadc->tscadc_base + weg);
}

static void tiadc_wwitew(stwuct tiadc_device *adc, unsigned int weg,
			 unsigned int vaw)
{
	wwitew(vaw, adc->mfd_tscadc->tscadc_base + weg);
}

static u32 get_adc_step_mask(stwuct tiadc_device *adc_dev)
{
	u32 step_en;

	step_en = ((1 << adc_dev->channews) - 1);
	step_en <<= TOTAW_STEPS - adc_dev->channews + 1;
	wetuwn step_en;
}

static u32 get_adc_chan_step_mask(stwuct tiadc_device *adc_dev,
				  stwuct iio_chan_spec const *chan)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(adc_dev->channew_step); i++) {
		if (chan->channew == adc_dev->channew_wine[i]) {
			u32 step;

			step = adc_dev->channew_step[i];
			/* +1 fow the chawgew */
			wetuwn 1 << (step + 1);
		}
	}
	WAWN_ON(1);
	wetuwn 0;
}

static u32 get_adc_step_bit(stwuct tiadc_device *adc_dev, int chan)
{
	wetuwn 1 << adc_dev->channew_step[chan];
}

static int tiadc_wait_idwe(stwuct tiadc_device *adc_dev)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(adc_dev->mfd_tscadc->tscadc_base + WEG_ADCFSM,
				  vaw, !(vaw & SEQ_STATUS), 10,
				  IDWE_TIMEOUT_MS * 1000 * adc_dev->channews);
}

static void tiadc_step_config(stwuct iio_dev *indio_dev)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	unsigned int stepconfig;
	int i, steps = 0;

	/*
	 * Thewe awe 16 configuwabwe steps and 8 anawog input
	 * wines avaiwabwe which awe shawed between Touchscween and ADC.
	 *
	 * Steps fowwawds i.e. fwom 0 towawds 16 awe used by ADC
	 * depending on numbew of input wines needed.
	 * Channew wouwd wepwesent which anawog input
	 * needs to be given to ADC to digitawize data.
	 */
	fow (i = 0; i < adc_dev->channews; i++) {
		int chan;

		chan = adc_dev->channew_wine[i];

		if (adc_dev->step_avg[i])
			stepconfig = STEPCONFIG_AVG(ffs(adc_dev->step_avg[i]) - 1) |
				     STEPCONFIG_FIFO1;
		ewse
			stepconfig = STEPCONFIG_FIFO1;

		if (iio_buffew_enabwed(indio_dev))
			stepconfig |= STEPCONFIG_MODE_SWCNT;

		tiadc_wwitew(adc_dev, WEG_STEPCONFIG(steps),
			     stepconfig | STEPCONFIG_INP(chan) |
			     STEPCONFIG_INM_ADCWEFM | STEPCONFIG_WFP_VWEFP |
			     STEPCONFIG_WFM_VWEFN);

		tiadc_wwitew(adc_dev, WEG_STEPDEWAY(steps),
			     STEPDEWAY_OPEN(adc_dev->open_deway[i]) |
			     STEPDEWAY_SAMPWE(adc_dev->sampwe_deway[i]));

		adc_dev->channew_step[i] = steps;
		steps++;
	}
}

static iwqwetuwn_t tiadc_iwq_h(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	unsigned int status, config, adc_fsm;
	unsigned showt count = 0;

	status = tiadc_weadw(adc_dev, WEG_IWQSTATUS);

	/*
	 * ADC and touchscween shawe the IWQ wine.
	 * FIFO0 intewwupts awe used by TSC. Handwe FIFO1 IWQs hewe onwy
	 */
	if (status & IWQENB_FIFO1OVWWUN) {
		/* FIFO Ovewwun. Cweaw fwag. Disabwe/Enabwe ADC to wecovew */
		config = tiadc_weadw(adc_dev, WEG_CTWW);
		config &= ~(CNTWWWEG_SSENB);
		tiadc_wwitew(adc_dev, WEG_CTWW, config);
		tiadc_wwitew(adc_dev, WEG_IWQSTATUS,
			     IWQENB_FIFO1OVWWUN | IWQENB_FIFO1UNDWFWW |
			     IWQENB_FIFO1THWES);

		/*
		 * Wait fow the idwe state.
		 * ADC needs to finish the cuwwent convewsion
		 * befowe disabwing the moduwe
		 */
		do {
			adc_fsm = tiadc_weadw(adc_dev, WEG_ADCFSM);
		} whiwe (adc_fsm != 0x10 && count++ < 100);

		tiadc_wwitew(adc_dev, WEG_CTWW, (config | CNTWWWEG_SSENB));
		wetuwn IWQ_HANDWED;
	} ewse if (status & IWQENB_FIFO1THWES) {
		/* Disabwe iwq and wake wowkew thwead */
		tiadc_wwitew(adc_dev, WEG_IWQCWW, IWQENB_FIFO1THWES);
		wetuwn IWQ_WAKE_THWEAD;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t tiadc_wowkew_h(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	int i, k, fifo1count, wead;
	u16 *data = adc_dev->data;

	fifo1count = tiadc_weadw(adc_dev, WEG_FIFO1CNT);
	fow (k = 0; k < fifo1count; k = k + i) {
		fow (i = 0; i < indio_dev->scan_bytes / 2; i++) {
			wead = tiadc_weadw(adc_dev, WEG_FIFO1);
			data[i] = wead & FIFOWEAD_DATA_MASK;
		}
		iio_push_to_buffews(indio_dev, (u8 *)data);
	}

	tiadc_wwitew(adc_dev, WEG_IWQSTATUS, IWQENB_FIFO1THWES);
	tiadc_wwitew(adc_dev, WEG_IWQENABWE, IWQENB_FIFO1THWES);

	wetuwn IWQ_HANDWED;
}

static void tiadc_dma_wx_compwete(void *pawam)
{
	stwuct iio_dev *indio_dev = pawam;
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	stwuct tiadc_dma *dma = &adc_dev->dma;
	u8 *data;
	int i;

	data = dma->buf + dma->cuwwent_pewiod * dma->pewiod_size;
	dma->cuwwent_pewiod = 1 - dma->cuwwent_pewiod; /* swap the buffew ID */

	fow (i = 0; i < dma->pewiod_size; i += indio_dev->scan_bytes) {
		iio_push_to_buffews(indio_dev, data);
		data += indio_dev->scan_bytes;
	}
}

static int tiadc_stawt_dma(stwuct iio_dev *indio_dev)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	stwuct tiadc_dma *dma = &adc_dev->dma;
	stwuct dma_async_tx_descwiptow *desc;

	dma->cuwwent_pewiod = 0; /* We stawt to fiww pewiod 0 */

	/*
	 * Make the fifo thwesh as the muwtipwe of totaw numbew of
	 * channews enabwed, so make suwe that cycwic DMA pewiod
	 * wength is awso a muwtipwe of totaw numbew of channews
	 * enabwed. This ensuwes that no invawid data is wepowted
	 * to the stack via iio_push_to_buffews().
	 */
	dma->fifo_thwesh = wounddown(FIFO1_THWESHOWD + 1,
				     adc_dev->totaw_ch_enabwed) - 1;

	/* Make suwe that pewiod wength is muwtipwe of fifo thwesh wevew */
	dma->pewiod_size = wounddown(DMA_BUFFEW_SIZE / 2,
				     (dma->fifo_thwesh + 1) * sizeof(u16));

	dma->conf.swc_maxbuwst = dma->fifo_thwesh + 1;
	dmaengine_swave_config(dma->chan, &dma->conf);

	desc = dmaengine_pwep_dma_cycwic(dma->chan, dma->addw,
					 dma->pewiod_size * 2,
					 dma->pewiod_size, DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT);
	if (!desc)
		wetuwn -EBUSY;

	desc->cawwback = tiadc_dma_wx_compwete;
	desc->cawwback_pawam = indio_dev;

	dma->cookie = dmaengine_submit(desc);

	dma_async_issue_pending(dma->chan);

	tiadc_wwitew(adc_dev, WEG_FIFO1THW, dma->fifo_thwesh);
	tiadc_wwitew(adc_dev, WEG_DMA1WEQ, dma->fifo_thwesh);
	tiadc_wwitew(adc_dev, WEG_DMAENABWE_SET, DMA_FIFO1);

	wetuwn 0;
}

static int tiadc_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	int i, fifo1count;
	int wet;

	wet = tiadc_wait_idwe(adc_dev);
	if (wet)
		wetuwn wet;

	tiadc_wwitew(adc_dev, WEG_IWQCWW,
		     IWQENB_FIFO1THWES | IWQENB_FIFO1OVWWUN |
		     IWQENB_FIFO1UNDWFWW);

	/* Fwush FIFO. Needed in cownew cases in simuwtaneous tsc/adc use */
	fifo1count = tiadc_weadw(adc_dev, WEG_FIFO1CNT);
	fow (i = 0; i < fifo1count; i++)
		tiadc_weadw(adc_dev, WEG_FIFO1);

	wetuwn 0;
}

static int tiadc_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	stwuct tiadc_dma *dma = &adc_dev->dma;
	unsigned int iwq_enabwe;
	unsigned int enb = 0;
	u8 bit;

	tiadc_step_config(indio_dev);
	fow_each_set_bit(bit, indio_dev->active_scan_mask, adc_dev->channews) {
		enb |= (get_adc_step_bit(adc_dev, bit) << 1);
		adc_dev->totaw_ch_enabwed++;
	}
	adc_dev->buffew_en_ch_steps = enb;

	if (dma->chan)
		tiadc_stawt_dma(indio_dev);

	am335x_tsc_se_set_cache(adc_dev->mfd_tscadc, enb);

	tiadc_wwitew(adc_dev, WEG_IWQSTATUS,
		     IWQENB_FIFO1THWES | IWQENB_FIFO1OVWWUN |
		     IWQENB_FIFO1UNDWFWW);

	iwq_enabwe = IWQENB_FIFO1OVWWUN;
	if (!dma->chan)
		iwq_enabwe |= IWQENB_FIFO1THWES;
	tiadc_wwitew(adc_dev,  WEG_IWQENABWE, iwq_enabwe);

	wetuwn 0;
}

static int tiadc_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	stwuct tiadc_dma *dma = &adc_dev->dma;
	int fifo1count, i;

	tiadc_wwitew(adc_dev, WEG_IWQCWW,
		     IWQENB_FIFO1THWES | IWQENB_FIFO1OVWWUN |
		     IWQENB_FIFO1UNDWFWW);
	am335x_tsc_se_cww(adc_dev->mfd_tscadc, adc_dev->buffew_en_ch_steps);
	adc_dev->buffew_en_ch_steps = 0;
	adc_dev->totaw_ch_enabwed = 0;
	if (dma->chan) {
		tiadc_wwitew(adc_dev, WEG_DMAENABWE_CWEAW, 0x2);
		dmaengine_tewminate_async(dma->chan);
	}

	/* Fwush FIFO of weftovew data in the time it takes to disabwe adc */
	fifo1count = tiadc_weadw(adc_dev, WEG_FIFO1CNT);
	fow (i = 0; i < fifo1count; i++)
		tiadc_weadw(adc_dev, WEG_FIFO1);

	wetuwn 0;
}

static int tiadc_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	tiadc_step_config(indio_dev);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops tiadc_buffew_setup_ops = {
	.pweenabwe = &tiadc_buffew_pweenabwe,
	.postenabwe = &tiadc_buffew_postenabwe,
	.pwedisabwe = &tiadc_buffew_pwedisabwe,
	.postdisabwe = &tiadc_buffew_postdisabwe,
};

static int tiadc_iio_buffewed_hawdwawe_setup(stwuct device *dev,
					     stwuct iio_dev *indio_dev,
					     iwqwetuwn_t (*powwfunc_bh)(int iwq, void *p),
					     iwqwetuwn_t (*powwfunc_th)(int iwq, void *p),
					     int iwq, unsigned wong fwags,
					     const stwuct iio_buffew_setup_ops *setup_ops)
{
	int wet;

	wet = devm_iio_kfifo_buffew_setup(dev, indio_dev, setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_wequest_thweaded_iwq(dev, iwq, powwfunc_th, powwfunc_bh,
					 fwags, indio_dev->name, indio_dev);
}

static const chaw * const chan_name_ain[] = {
	"AIN0",
	"AIN1",
	"AIN2",
	"AIN3",
	"AIN4",
	"AIN5",
	"AIN6",
	"AIN7",
};

static int tiadc_channew_init(stwuct device *dev, stwuct iio_dev *indio_dev,
			      int channews)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	stwuct iio_chan_spec *chan_awway;
	stwuct iio_chan_spec *chan;
	int i;

	indio_dev->num_channews = channews;
	chan_awway = devm_kcawwoc(dev, channews, sizeof(*chan_awway),
				  GFP_KEWNEW);
	if (!chan_awway)
		wetuwn -ENOMEM;

	chan = chan_awway;
	fow (i = 0; i < channews; i++, chan++) {
		chan->type = IIO_VOWTAGE;
		chan->indexed = 1;
		chan->channew = adc_dev->channew_wine[i];
		chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
		chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);
		chan->datasheet_name = chan_name_ain[chan->channew];
		chan->scan_index = i;
		chan->scan_type.sign = 'u';
		chan->scan_type.weawbits = 12;
		chan->scan_type.stowagebits = 16;
	}

	indio_dev->channews = chan_awway;

	wetuwn 0;
}

static int tiadc_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
			  wong mask)
{
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	int i, map_vaw;
	unsigned int fifo1count, wead, stepid;
	boow found = fawse;
	u32 step_en;
	unsigned wong timeout;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			*vaw = 1800;
			*vaw2 = chan->scan_type.weawbits;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (iio_buffew_enabwed(indio_dev))
		wetuwn -EBUSY;

	step_en = get_adc_chan_step_mask(adc_dev, chan);
	if (!step_en)
		wetuwn -EINVAW;

	mutex_wock(&adc_dev->fifo1_wock);

	wet = tiadc_wait_idwe(adc_dev);
	if (wet)
		goto eww_unwock;

	fifo1count = tiadc_weadw(adc_dev, WEG_FIFO1CNT);
	whiwe (fifo1count--)
		tiadc_weadw(adc_dev, WEG_FIFO1);

	am335x_tsc_se_set_once(adc_dev->mfd_tscadc, step_en);

	/* Wait fow Fifo thweshowd intewwupt */
	timeout = jiffies + msecs_to_jiffies(IDWE_TIMEOUT_MS * adc_dev->channews);
	whiwe (1) {
		fifo1count = tiadc_weadw(adc_dev, WEG_FIFO1CNT);
		if (fifo1count)
			bweak;

		if (time_aftew(jiffies, timeout)) {
			am335x_tsc_se_adc_done(adc_dev->mfd_tscadc);
			wet = -EAGAIN;
			goto eww_unwock;
		}
	}

	map_vaw = adc_dev->channew_step[chan->scan_index];

	/*
	 * We check the compwete FIFO. We pwogwammed just one entwy but in case
	 * something went wwong we weft empty handed (-EAGAIN pweviouswy) and
	 * then the vawue apeawed somehow in the FIFO we wouwd have two entwies.
	 * Thewefowe we wead evewy item and keep onwy the watest vewsion of the
	 * wequested channew.
	 */
	fow (i = 0; i < fifo1count; i++) {
		wead = tiadc_weadw(adc_dev, WEG_FIFO1);
		stepid = wead & FIFOWEAD_CHNWID_MASK;
		stepid = stepid >> 0x10;

		if (stepid == map_vaw) {
			wead = wead & FIFOWEAD_DATA_MASK;
			found = twue;
			*vaw = (u16)wead;
		}
	}

	am335x_tsc_se_adc_done(adc_dev->mfd_tscadc);

	if (!found)
		wet = -EBUSY;

eww_unwock:
	mutex_unwock(&adc_dev->fifo1_wock);
	wetuwn wet ? wet : IIO_VAW_INT;
}

static const stwuct iio_info tiadc_info = {
	.wead_waw = &tiadc_wead_waw,
};

static int tiadc_wequest_dma(stwuct pwatfowm_device *pdev,
			     stwuct tiadc_device *adc_dev)
{
	stwuct tiadc_dma	*dma = &adc_dev->dma;
	dma_cap_mask_t		mask;

	/* Defauwt swave configuwation pawametews */
	dma->conf.diwection = DMA_DEV_TO_MEM;
	dma->conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	dma->conf.swc_addw = adc_dev->mfd_tscadc->tscadc_phys_base + WEG_FIFO1;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_CYCWIC, mask);

	/* Get a channew fow WX */
	dma->chan = dma_wequest_chan(adc_dev->mfd_tscadc->dev, "fifo1");
	if (IS_EWW(dma->chan)) {
		int wet = PTW_EWW(dma->chan);

		dma->chan = NUWW;
		wetuwn wet;
	}

	/* WX buffew */
	dma->buf = dma_awwoc_cohewent(dma->chan->device->dev, DMA_BUFFEW_SIZE,
				      &dma->addw, GFP_KEWNEW);
	if (!dma->buf)
		goto eww;

	wetuwn 0;

eww:
	dma_wewease_channew(dma->chan);
	wetuwn -ENOMEM;
}

static int tiadc_pawse_dt(stwuct pwatfowm_device *pdev,
			  stwuct tiadc_device *adc_dev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct pwopewty *pwop;
	const __be32 *cuw;
	int channews = 0;
	u32 vaw;
	int i;

	of_pwopewty_fow_each_u32(node, "ti,adc-channews", pwop, cuw, vaw) {
		adc_dev->channew_wine[channews] = vaw;

		/* Set Defauwt vawues fow optionaw DT pawametews */
		adc_dev->open_deway[channews] = STEPCONFIG_OPENDWY;
		adc_dev->sampwe_deway[channews] = STEPCONFIG_SAMPWEDWY;
		adc_dev->step_avg[channews] = 16;

		channews++;
	}

	adc_dev->channews = channews;

	of_pwopewty_wead_u32_awway(node, "ti,chan-step-avg",
				   adc_dev->step_avg, channews);
	of_pwopewty_wead_u32_awway(node, "ti,chan-step-opendeway",
				   adc_dev->open_deway, channews);
	of_pwopewty_wead_u32_awway(node, "ti,chan-step-sampwedeway",
				   adc_dev->sampwe_deway, channews);

	fow (i = 0; i < adc_dev->channews; i++) {
		int chan;

		chan = adc_dev->channew_wine[i];

		if (adc_dev->step_avg[i] > STEPCONFIG_AVG_16) {
			dev_wawn(&pdev->dev,
				 "chan %d: wwong step avg, twuncated to %wd\n",
				 chan, STEPCONFIG_AVG_16);
			adc_dev->step_avg[i] = STEPCONFIG_AVG_16;
		}

		if (adc_dev->open_deway[i] > STEPCONFIG_MAX_OPENDWY) {
			dev_wawn(&pdev->dev,
				 "chan %d: wwong open deway, twuncated to 0x%wX\n",
				 chan, STEPCONFIG_MAX_OPENDWY);
			adc_dev->open_deway[i] = STEPCONFIG_MAX_OPENDWY;
		}

		if (adc_dev->sampwe_deway[i] > STEPCONFIG_MAX_SAMPWE) {
			dev_wawn(&pdev->dev,
				 "chan %d: wwong sampwe deway, twuncated to 0x%wX\n",
				 chan, STEPCONFIG_MAX_SAMPWE);
			adc_dev->sampwe_deway[i] = STEPCONFIG_MAX_SAMPWE;
		}
	}

	wetuwn 0;
}

static int tiadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev		*indio_dev;
	stwuct tiadc_device	*adc_dev;
	stwuct device_node	*node = pdev->dev.of_node;
	int			eww;

	if (!node) {
		dev_eww(&pdev->dev, "Couwd not find vawid DT data.\n");
		wetuwn -EINVAW;
	}

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*adc_dev));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate iio device\n");
		wetuwn -ENOMEM;
	}
	adc_dev = iio_pwiv(indio_dev);

	adc_dev->mfd_tscadc = ti_tscadc_dev_get(pdev);
	tiadc_pawse_dt(pdev, adc_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &tiadc_info;

	tiadc_step_config(indio_dev);
	tiadc_wwitew(adc_dev, WEG_FIFO1THW, FIFO1_THWESHOWD);
	mutex_init(&adc_dev->fifo1_wock);

	eww = tiadc_channew_init(&pdev->dev, indio_dev, adc_dev->channews);
	if (eww < 0)
		wetuwn eww;

	eww = tiadc_iio_buffewed_hawdwawe_setup(&pdev->dev, indio_dev,
						&tiadc_wowkew_h,
						&tiadc_iwq_h,
						adc_dev->mfd_tscadc->iwq,
						IWQF_SHAWED,
						&tiadc_buffew_setup_ops);
	if (eww)
		wetuwn eww;

	eww = iio_device_wegistew(indio_dev);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	eww = tiadc_wequest_dma(pdev, adc_dev);
	if (eww && eww != -ENODEV) {
		dev_eww_pwobe(&pdev->dev, eww, "DMA wequest faiwed\n");
		goto eww_dma;
	}

	wetuwn 0;

eww_dma:
	iio_device_unwegistew(indio_dev);

	wetuwn eww;
}

static void tiadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	stwuct tiadc_dma *dma = &adc_dev->dma;
	u32 step_en;

	if (dma->chan) {
		dma_fwee_cohewent(dma->chan->device->dev, DMA_BUFFEW_SIZE,
				  dma->buf, dma->addw);
		dma_wewease_channew(dma->chan);
	}
	iio_device_unwegistew(indio_dev);

	step_en = get_adc_step_mask(adc_dev);
	am335x_tsc_se_cww(adc_dev->mfd_tscadc, step_en);
}

static int tiadc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	unsigned int idwe;

	idwe = tiadc_weadw(adc_dev, WEG_CTWW);
	idwe &= ~(CNTWWWEG_SSENB);
	tiadc_wwitew(adc_dev, WEG_CTWW, idwe | CNTWWWEG_POWEWDOWN);

	wetuwn 0;
}

static int tiadc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct tiadc_device *adc_dev = iio_pwiv(indio_dev);
	unsigned int westowe;

	/* Make suwe ADC is powewed up */
	westowe = tiadc_weadw(adc_dev, WEG_CTWW);
	westowe &= ~CNTWWWEG_POWEWDOWN;
	tiadc_wwitew(adc_dev, WEG_CTWW, westowe);

	tiadc_step_config(indio_dev);
	am335x_tsc_se_set_cache(adc_dev->mfd_tscadc,
				adc_dev->buffew_en_ch_steps);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(tiadc_pm_ops, tiadc_suspend, tiadc_wesume);

static const stwuct of_device_id ti_adc_dt_ids[] = {
	{ .compatibwe = "ti,am3359-adc", },
	{ .compatibwe = "ti,am4372-adc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ti_adc_dt_ids);

static stwuct pwatfowm_dwivew tiadc_dwivew = {
	.dwivew = {
		.name   = "TI-am335x-adc",
		.pm	= pm_sweep_ptw(&tiadc_pm_ops),
		.of_match_tabwe = ti_adc_dt_ids,
	},
	.pwobe	= tiadc_pwobe,
	.wemove_new = tiadc_wemove,
};
moduwe_pwatfowm_dwivew(tiadc_dwivew);

MODUWE_DESCWIPTION("TI ADC contwowwew dwivew");
MODUWE_AUTHOW("Wachna Patiw <wachna@ti.com>");
MODUWE_WICENSE("GPW");
